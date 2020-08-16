

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/* Function Prototypes */
static Std_ReturnType Xcp_Transmit(const PduInfoType* XcpPacketPtr, uint8 protLayerId, Xcp_PduIdType XcpTxPduId);
static void Xcp_SendResTxConf(uint8 protLayerId);
static void Xcp_SendEvTxConf(uint8 protLayerId);
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
static void Xcp_SendDaqTxConf(Xcp_DaqList_t* DaqListPtr, uint8 protLayerId);
static Std_ReturnType Xcp_DaqQueFindNextOdtToSend(Xcp_DaqList_t** DaqListPtr, uint8 protLayerId);
#endif

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


/* Functions */
#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function calls the transmit function of the connected transport layer
\param[in]  XcpPacketPtr  pointer to packet data and length, which is meant to transmit
\param[in]  protLayerId   protocol layer id
\param[in]  XcpTxPduId    TX-Pdu Id
\return     State if transmit was successful (E_OK: transmit successful)
***************************************************************************************************/
static Std_ReturnType Xcp_Transmit(const PduInfoType* XcpPacketPtr, uint8 protLayerId, Xcp_PduIdType XcpTxPduId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Std_ReturnType Status; /* status of the process */
  uint8 tl_id; /* transport layer ID */

  /* get the connected transport layer */
  tl_id = XCP_ACTIVE_TL_ID(protLayerId);

  XCP_DET_REPORT_ERROR_RET((tl_id >= XCP_TL_IDS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, E_NOT_OK);

  /* call Transmit Function according to active transport layer id */
  Status = Xcp_PlCfgConst.TlCfg[tl_id].TLTransmit_pfct(XcpPacketPtr, tl_id, XcpTxPduId);
  if (Status == E_OK)
  {
    /* Transmit OK, nothing else to do */
    XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_TransmitOkCtr);
  }
  else
  {
    /* Transmit not successful, do not expect a tx_confirmation.
       txPending is set to TRUE by caller of this function (optional).
       Wait4TxConfCtr is set to 0 by caller of this function (required). */
    XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_TransmitNotOkCtr);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return(Status);
}


/**
****************************************************************************************************
This function sends a response out of a tx confirmation.\n
It runs in TxConfirmation --> interrupt context. It cannot be interrupted by another TxConfirmation
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
static void Xcp_SendResTxConf(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  PduInfoType XcpPacket;

  /* Prepare XcpPacket for transmission */
  SchM_Enter_Xcp_SendingShort();
  XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendResTxConfCtr);

  XcpPacket.SduDataPtr = XCP_RES_BUFFER_PTR(protLayerId);
  XcpPacket.SduLength  = (PduLengthType) XCP_RES_BUFFER_LENGTH(protLayerId);
  SchM_Exit_Xcp_SendingShort();

  /* Call transmission request */
  if (Xcp_Transmit(&XcpPacket, protLayerId, XCP_PDU_ID_UNKNOWN) == E_OK)
  {
    /* transmit successful */
    XCP_RES_BUFFER_LENGTH(protLayerId) = 0;
  }
  else
  {
    /* transmit not successful, will be retriggered by Xcp_RetriggerTransmit */
    Xcp_Cleared[protLayerId].TxPending_b = TRUE;
    SchM_Enter_Xcp_SendingShort();
    Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
    SchM_Exit_Xcp_SendingShort();
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function sends a response which is called by the protocol layer
\param[in]  protLayerId       protocol layer id
\return     -
***************************************************************************************************/
void Xcp_SendRes(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  PduInfoType XcpPacket;

  /* Long spin lock including complete transmit */
  SchM_Enter_Xcp_SendingLong();

  SchM_Enter_Xcp_SendingShort();
  XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendResCtr);

  /* Can XcpPacket be transmitted now? */
  if (Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 == 0)
  {
    Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = XCP_WAIT4TXCONFCTR;
    SchM_Exit_Xcp_SendingShort();

    /* Prepare XcpPacket for transmission */
    XcpPacket.SduDataPtr = XCP_RES_BUFFER_PTR(protLayerId);
    XcpPacket.SduLength  = (PduLengthType) XCP_RES_BUFFER_LENGTH(protLayerId);

    /* empty the buffer, so it will not be transmitted again */
    XCP_RES_BUFFER_LENGTH(protLayerId) = 0;

    /* Call transmission request */
    if (Xcp_Transmit(&XcpPacket, protLayerId, XCP_PDU_ID_UNKNOWN) == E_OK)
    {
      /* transmit successful */
    }
    else
    {
      /* transmit not successful */
      XCP_RES_BUFFER_LENGTH(protLayerId) = XcpPacket.SduLength;

      /* transmit not successful, will be retriggered by Xcp_RetriggerTransmit */
      Xcp_Cleared[protLayerId].TxPending_b = TRUE;
      SchM_Enter_Xcp_SendingShort();
      Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
      SchM_Exit_Xcp_SendingShort();
    }
  }
  else
  {
    SchM_Exit_Xcp_SendingShort();
    /* Wait4TxConfCtr != 0, XcpPacket is transmitted in one of next Xcp_TxConfirmation */
  }
  /* Long spin lock including complete transmit */
  SchM_Exit_Xcp_SendingLong();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Function sends error response which is called by the protocol layer
\param[in]  ErrorCode     error response to send
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_SendErrRes(Xcp_ErrorCode ErrorCode, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* length of error response */
  XCP_RES_BUFFER_LENGTH(protLayerId) = 2;
  /* Error Pid */
  XCP_RES_BUFFER_PTR(protLayerId)[0] = XCP_PACKET_ID_ERR;
  /* Error Code */
  XCP_RES_BUFFER_PTR(protLayerId)[1] = (uint8)ErrorCode;
  /* Store data in Queue and transmit if possible */
  Xcp_SendRes(protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Function sends positive response which is called by the protocol layer
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_SendPosRes(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* length of error response */
  XCP_RES_BUFFER_LENGTH(protLayerId) = 1;
  /* Response Pid */
  XCP_RES_BUFFER_PTR(protLayerId)[0] = XCP_PACKET_ID_RES;
  /* Store data in Queue and transmit if possible */
  Xcp_SendRes(protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function sends an event out of a tx confirmation. \n
It runs in TxConfirmation --> interrupt context. It cannot be interrupted by another TxConfirmation
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
static void Xcp_SendEvTxConf(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  PduInfoType XcpPacket;

  /* Prepare XcpPacket for transmission */
  SchM_Enter_Xcp_SendingShort();
  XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendEvTxConfCtr);

  XcpPacket.SduDataPtr = XCP_EV_BUFFER_PTR(protLayerId);
  XcpPacket.SduLength  = (PduLengthType) XCP_EV_BUFFER_LENGTH(protLayerId);
  SchM_Exit_Xcp_SendingShort();

  /* Call transmission request */
  if (Xcp_Transmit(&XcpPacket, protLayerId, XCP_PDU_ID_UNKNOWN) == E_OK)
  {
    /* transmit successful */
    XCP_EV_BUFFER_LENGTH(protLayerId) = 0;
  }
  else
  {
    /* transmit not successful, will be retriggered by Xcp_RetriggerTransmit */
    Xcp_Cleared[protLayerId].TxPending_b = TRUE;
    SchM_Enter_Xcp_SendingShort();
    Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
    SchM_Exit_Xcp_SendingShort();
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function sends out an event
\param[in]  XcpPacketCtoPtr   pointer to event data and length
\param[in]  protLayerId       protocol layer id
\return     -
***************************************************************************************************/
void Xcp_SendEv(const Xcp_Cto8_t* XcpPacketCtoPtr, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  PduInfoType XcpPacket;

  /* Long spin lock including complete transmit */
  SchM_Enter_Xcp_SendingLong();

  SchM_Enter_Xcp_SendingShort();
  XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendEvCtr);

  /* copy event data to global buffer */
  XCP_EV_BUFFER_LENGTH(protLayerId) = XcpPacketCtoPtr->Length_u32;
  /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
  Xcp_MemCopy8(XCP_EV_BUFFER_PTR(protLayerId), XcpPacketCtoPtr->Buffer_au8, XcpPacketCtoPtr->Length_u32);

  /* Can XcpPacket be transmitted now? */
  if (Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 == 0)
  {
    Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = XCP_WAIT4TXCONFCTR;
    XCP_EV_BUFFER_LENGTH(protLayerId) = 0;
    SchM_Exit_Xcp_SendingShort();

    /* Prepare XcpPacket for transmission */
    XcpPacket.SduDataPtr = XCP_EV_BUFFER_PTR(protLayerId);
    XcpPacket.SduLength  = (PduLengthType) XcpPacketCtoPtr->Length_u32;

    /* Call transmission request */
    if (Xcp_Transmit(&XcpPacket, protLayerId, XCP_PDU_ID_UNKNOWN) == E_OK)
    {
      /* transmit successful */
    }
    else
    {
      /* transmit not successful */
      SchM_Enter_Xcp_SendingShort();
      /* check if buffer is still free */
      if (XCP_EV_BUFFER_LENGTH(protLayerId) == 0u)
      {
        XCP_EV_BUFFER_LENGTH(protLayerId) = XcpPacketCtoPtr->Length_u32;
      }
      /* else: other event packet is in buffer, do nothing */

      /* transmit not successful, will be retriggered by Xcp_RetriggerTransmit */
      Xcp_Cleared[protLayerId].TxPending_b = TRUE;
      Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
      SchM_Exit_Xcp_SendingShort();
    }
  }
  else
  {
    SchM_Exit_Xcp_SendingShort();
    /* Wait4TxConfCtr != 0, XcpPacket is transmitted in one of next Xcp_TxConfirmation */
  }
  /* Long spin lock including complete transmit */
  SchM_Exit_Xcp_SendingLong();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

/**
****************************************************************************************************
This function prepares event packet for the requested event id and calls Xcp_SendEv function
\param[in]  EventCode_u8    event code
\param[in]  protLayerId     protocol layer id
\return     -
***************************************************************************************************/
void Xcp_SendEv_Code(uint8 EventCode_u8, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables*/
  Xcp_Cto8_t XcpEvPacket;
  Xcp_Ev_t*  EvPtr;
  /* initialize event packet */
  /* Event packet length is same for events: Store Daq, Clear Daq, Daq Overload, Command Pending */
  XcpEvPacket.Length_u32 = XCP_EV_LENGTH;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  EvPtr = (Xcp_Ev_t*) (void*) XcpEvPacket.Buffer_au8;
  /* prepare and send event */
  EvPtr->PacketId_u8  = XCP_PACKET_ID_EV;
  EvPtr->EventCode_u8 = EventCode_u8;

  Xcp_SendEv(&XcpEvPacket, protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)

#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function is called by the protocol layer to trigger sending. \n
It runs in TxConfirmation --> interrupt context. It cannot be interrupted by another TxConfirmation
\param[in]  DaqListPtr    pointer to the daq list
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
static void Xcp_SendDaqTxConf(Xcp_DaqList_t* DaqListPtr, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint16      ReadPos;
  PduInfoType XcpPacket;
  XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendDaqTxConfCtr);

  /* fetch read position from daq */
  ReadPos = DaqListPtr->DaqListQuePos.ReadPos_u16;
  /* each read pos represents a specific ODT, thus DTOLen can be fetched there */
  XcpPacket.SduLength = (PduLengthType) XCP_ODT_LENGTH(DaqListPtr->DaqListQuePos.ReadPos_OdtNum_u16, protLayerId);
  /* set data pointer to the queue */
  XcpPacket.SduDataPtr = &(DaqListPtr->DaqListQue_p[ReadPos * XCP_MAXDTO_4ALIGNED(protLayerId)]);
#if (XCP_DAQ_OVERLOAD_INDICATION_PID_ENABLED == STD_ON)
  if ( (Xcp_NoInit[protLayerId].DaqConfig.OverloadOccurred_b == TRUE)
    && (Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].OverloadType_en == XCP_DAQ_OVERLOAD_INDICATION_PID) )
  {
    /* indicate overload by setting MSB of PID */
    XcpPacket.SduDataPtr[0] = (uint8) (XcpPacket.SduDataPtr[0] | XCP_OVERLOAD_INDICATION_PID_BIT);
    /* reset overload */
    Xcp_NoInit[protLayerId].DaqConfig.OverloadOccurred_b = FALSE;
  }
#endif
  /* Call transmission request */
  if (Xcp_Transmit(&XcpPacket, protLayerId, DaqListPtr->XcpTxPduId) == E_OK)
  {
    Xcp_QueReadNext(DaqListPtr);
  }
  else
  {
    /* transmit not successful, will be retriggered by Xcp_RetriggerTransmit */
    Xcp_Cleared[protLayerId].TxPending_b = TRUE;
    SchM_Enter_Xcp_SendingShort();
    Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
    SchM_Exit_Xcp_SendingShort();
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function sends daq packets for the protocol layer
\param[in]  daqListNo_u16   absolute daq list number
\param[in]  protLayerId     protocol layer id
\return     -
***************************************************************************************************/
void Xcp_SendDaq(uint16 daqListNo_u16, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  PduInfoType    XcpPacket;
  Xcp_DaqList_t* DaqListPtr;
  uint16         ReadPos;
  Std_ReturnType retval;

  DaqListPtr = &(XCP_DAQ(daqListNo_u16, protLayerId));
  /* Long spin lock including complete transmit */
  SchM_Enter_Xcp_SendingLong();

  SchM_Enter_Xcp_SendingShort();
  XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendDaqCtr);

  /* fetch read/write position from daq */
  ReadPos  = DaqListPtr->DaqListQuePos.ReadPos_u16;

  /* Queue could be already transmitted by TxConfirmation --> check if queue is still contains data and daq is still running */
  if (   (ReadPos != DaqListPtr->DaqListQuePos.WritePos_u16)
      && ( (DaqListPtr->Mode_u8 & XCP_DAQLISTMODE_RUNNING) == XCP_DAQLISTMODE_RUNNING )
     )
  {
    /* Can XcpPacket be transmitted now? */
    if (Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 == 0)
    {
      /* Queue contains data, transmission can be triggered */
      Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = XCP_WAIT4TXCONFCTR;
      Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16 = daqListNo_u16;
#if (XCP_CAN_DIRECT_TRANSMIT == STD_OFF)
      SchM_Exit_Xcp_SendingShort();
#endif

      /* each read pos represents a specific ODT, thus DTOLen can be fetched there */
      XcpPacket.SduLength = (PduLengthType) ( XCP_ODT_LENGTH(DaqListPtr->DaqListQuePos.ReadPos_OdtNum_u16, protLayerId) );
      /* set data pointer to the queue */
      XcpPacket.SduDataPtr = &(DaqListPtr->DaqListQue_p[ReadPos * XCP_MAXDTO_4ALIGNED(protLayerId)]);
#if (XCP_DAQ_OVERLOAD_INDICATION_PID_ENABLED == STD_ON)
      if ( (Xcp_NoInit[protLayerId].DaqConfig.OverloadOccurred_b == TRUE)
        && (Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].OverloadType_en == XCP_DAQ_OVERLOAD_INDICATION_PID) )
      {
        /* indicate overload by setting MSB of PID */
        XcpPacket.SduDataPtr[0] = (uint8) (XcpPacket.SduDataPtr[0] | XCP_OVERLOAD_INDICATION_PID_BIT);
        Xcp_NoInit[protLayerId].DaqConfig.OverloadOccurred_b = FALSE;
      }
#endif
      /* update indexes for next data in que */
      /* !!! Be careful here: The sequence is intended.
       * The obvious order would be to first call Xcp_Transmit and then set the que one step further.
       * But in this case we cannot have a spin lock around the two actions (Xcp_Transmit is simply to long).
       * Hence we face the situation, that a higher prior action can interrupt the execution between sending the message and
       * incrementing the position in the Que. By this the Receive Interrupt gets triggered
       * before we increment the position in the Que and the same object gets send twice.
       * */
      Xcp_QueReadNext(DaqListPtr);
      /* transmit request */
      /* use stored  transport layer Information for faster transmission */
      retval = Xcp_Transmit(&XcpPacket, protLayerId, DaqListPtr->XcpTxPduId);
#if (XCP_CAN_DIRECT_TRANSMIT == STD_ON)
      SchM_Exit_Xcp_SendingShort();
#endif

      if (retval != E_OK)
      {
        /* Transmit not successful */
        /* reset indexes to last data in que */
        Xcp_QueSetBack(DaqListPtr);
        /* transmit not successful, will be retriggered by Xcp_RetriggerTransmit */
        Xcp_Cleared[protLayerId].TxPending_b = TRUE;
        SchM_Enter_Xcp_SendingShort();
        Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
        SchM_Exit_Xcp_SendingShort();
      }
    }
    else
    /* Wait4TxConfCtr != 0, XcpPacket is transmitted in one of next Xcp_TxConfirmation */
    {
      uint16 DaqListSending_u16;
      DaqListSending_u16 = Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16;

      if (DaqListSending_u16 != XCP_DAQLIST_UNDEF)
      {
        /* check priority of sending DAQ */
        if (Xcp_NoInit[protLayerId].DaqConfig.DaqList_p[DaqListSending_u16].Priority_u8 < DaqListPtr->Priority_u8)
        {
          /* overwrite sending DAQ with this DAQ, so it will send out next */
          Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16 = daqListNo_u16;
        }
      }
      else
      {
        /* set sending DAQ, so it will send out next */
        Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16 = daqListNo_u16;
      }
      SchM_Exit_Xcp_SendingShort();
    }
  }
  else
  {
    /* Queue data already sent by TxConfirmation, transmit not necessary */
    SchM_Exit_Xcp_SendingShort();
  }
  /* Long spin lock including complete transmit */
  SchM_Exit_Xcp_SendingLong();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function looks for daq lists in given protocol layer considering the priority. \n
If a daq list wants to send something, the pointer to daqlist pointer is changed to the found daq.
\param[out] DaqListPtr    pointer to daq list pointer
\param[in]  protLayerId   protocol layer id
\return     E_OK: daq found, DaqListPtr is valid
***************************************************************************************************/
static Std_ReturnType Xcp_DaqQueFindNextOdtToSend(Xcp_DaqList_t** DaqListPtr, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Std_ReturnType Status;
  uint16_least i;
  Xcp_DaqList_t* daqListPtr_local;
  Xcp_DaqList_t* SendingDaqListPtr;
  uint16 daqlist_u16;

  /* Initial values */
  Status = E_NOT_OK;

  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)
  {
    if (Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16 != XCP_DAQLIST_UNDEF)
    {
      /* store pointer for fast access */
      SendingDaqListPtr = &(XCP_DAQ(Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16, protLayerId));

      /* check whether last queue has something to send */
      if (SendingDaqListPtr->DaqListQuePos.WritePos_u16 != SendingDaqListPtr->DaqListQuePos.ReadPos_u16)
      {
        /* continue sending previous daq */
        *DaqListPtr = SendingDaqListPtr;
        Status = E_OK;
      }
    }

    if (Status == E_NOT_OK)
    {
      /* reset active daq sending pointer */
      Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16 = XCP_DAQLIST_UNDEF;
      /* Loop through all DAQs */
      for (i = 0; i < Xcp_NoInit[protLayerId].DaqConfig.DaqListSendingCnt_u16; i++)
      {
        daqlist_u16 = Xcp_NoInit[protLayerId].DaqConfig.PriorityList_p[i];
        daqListPtr_local = &(XCP_DAQ(daqlist_u16, protLayerId));

        if (daqListPtr_local->DaqListQuePos.WritePos_u16 != daqListPtr_local->DaqListQuePos.ReadPos_u16)
        {
          /* DaqPacket found to send */
          *DaqListPtr = daqListPtr_local;
          Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16 = daqlist_u16;
          Status = E_OK;
          /* Break from for-loop of all DAQs */
          break;
        }
        else
        {
          /* No DaqPacket found */
        }
      }
    }
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return Status;
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"

#endif


#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function retriggers a transmit by calling a pseudo tx confirmation, which looks for a packet to send.
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_RetriggerTransmit(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Check if transmit is pending without spin lock
     Reason: Save runtime for this not normal case */
  if (Xcp_Cleared[protLayerId].TxPending_b == TRUE)
  {
    /* Long spin lock in case short is not used */
    SchM_Enter_Xcp_SendingLong();
    SchM_Enter_Xcp_SendingShort();
    /* Check if transmit is transmission is possible and transmission pending */
    if ( (Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 == 0) && (Xcp_Cleared[protLayerId].TxPending_b == TRUE) )
    {
      Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = XCP_WAIT4TXCONFCTR;
      Xcp_Cleared[protLayerId].TxPending_b = FALSE;
      SchM_Exit_Xcp_SendingShort();
      /* Long spin lock in case short is not used */
      SchM_Exit_Xcp_SendingLong();

      /* generate a pseudo TxConfirmation to send out pending packets */
      

      Xcp_TxConfirmation(XCP_ACTIVE_TL_ID(protLayerId));
    }
    else
    {
      SchM_Exit_Xcp_SendingShort();
      /* Long spin lock in case short is not used */
      SchM_Exit_Xcp_SendingLong();
    }
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function is called by the different transport layers, when they receive the information, that
a packet is sent. This function looks for a new packet to send.
\param[in]  XcpTransportLayerId   transport layer id
\return     -
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_TxConfirmation: Function contains very simple "else if" statements. HIS metric compliance would decrease readability and maintainability. */
/* HIS METRIC CALLS VIOLATION IN Xcp_TxConfirmation: Long and short SchM locks are still needed. It is planned combine the calls -> metric no longer violated */
void Xcp_TxConfirmation(uint8 XcpTransportLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint8 protLayerId;
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  Xcp_DaqList_t* DaqListPtr;
#endif

  protLayerId = Xcp_GlobalNoInit.Tl2PlRef_au8[XcpTransportLayerId];

  /* abort, if a tx confirmation comes after disconnect is finished */
  if (protLayerId != XCP_INVALID_PROTLAYER_ID)
  {
    /* Long spin lock including complete transmit */
    SchM_Enter_Xcp_SendingLong();

    /* Check for XcpPackets under spin lock because new XcpPackets might be inserted during processing */
    SchM_Enter_Xcp_SendingShort();
    XCP_DEBUG_CTR_INC(Xcp_Cleared[protLayerId].Debug.Xcp_Debug_TxConfCtr);

    /* TxConfirmation is here, reset Wait4TxConfCtr to start value */
    Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = XCP_WAIT4TXCONFCTR;

    /* RES and ERR */
    if (XCP_RES_BUFFER_LENGTH(protLayerId) > 0u)
    {
      SchM_Exit_Xcp_SendingShort();
      Xcp_SendResTxConf(protLayerId);
    }

    /* EV and SERV */
    else if (XCP_EV_BUFFER_LENGTH(protLayerId) > 0u)
    {
      SchM_Exit_Xcp_SendingShort();
      Xcp_SendEvTxConf(protLayerId);
    }

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
    /* DAQ, function Xcp_DaqQueContainsOdt must run under spin lock */
    else if (Xcp_DaqQueFindNextOdtToSend(&DaqListPtr, protLayerId) == E_OK)
    {
  #if (XCP_CAN_DIRECT_TRANSMIT == STD_ON)
      Xcp_SendDaqTxConf(DaqListPtr, protLayerId);
      SchM_Exit_Xcp_SendingShort();
  #else
      SchM_Exit_Xcp_SendingShort();
      Xcp_SendDaqTxConf(DaqListPtr, protLayerId);
  #endif
    }
#endif

#if(XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
    /* Block upload */
    else if (Xcp_Cleared[protLayerId].Mem.UploadRunning_b == TRUE)
    {
      SchM_Exit_Xcp_SendingShort();
      Xcp_BlockUpload(protLayerId);
      /* Wait4TxConfCtr != 0. Xcp_CmdUpload cannot trigger a new transmission,
         only ResBuffer is updated. Transmission must be triggered here */
      Xcp_SendResTxConf(protLayerId);
    }
#endif

    else
    {
      /* nothing more to send, reset transmit counter
         Important: Must be set to 0 before disable spin lock.
         So other Xcp_SendXxx functions wait to check if they can transmit */
      Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
      SchM_Exit_Xcp_SendingShort();
    }
    /* Long spin lock including complete transmit */
    SchM_Exit_Xcp_SendingLong();
  }
  else /* protLayerId != XCP_INVALID_PROTLAYER_ID */
  {
    /* Xcp_TxConfirmation after DISCONNECT - this is ok */
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


