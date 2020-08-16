

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
#if (XCP_CMD_SET_DAQ_LIST_MODE_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to set the information on the current mode of the specified DAQ list.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_CmdSetDaqListMode: Function contains very simple "else if" statements. HIS metric compliance would decrease readability and maintainability. */
void Xcp_CmdSetDaqListMode(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdSetDaqListMode_t* const CmdPtr = (const Xcp_CmdSetDaqListMode_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;
  Xcp_DaqList_t* DaqListPtr;
  uint8 ActiveTLId;

  /* initialization */
  Error = XCP_NO_ERROR;

  /* Check if DAQ list is running. */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)
  {
    Error = XCP_ERR_DAQ_ACTIVE;
  }
  /* Check if the command parameters are valid */
  else if ( (CmdPtr->DaqListNum_u16 >= Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16)
         || (CmdPtr->TransmissionRatePrescaler_u8 == 0) )
  {
    Error = XCP_ERR_OUT_OF_RANGE;
  }
  /* Check for not supported Modes */
  else if ((CmdPtr->Mode_u8 & ((uint8) (~(XCP_DAQLISTMODE_DIRECTION|XCP_DAQLISTMODE_TIMESTAMP)))) != 0u)
  {
    Error = XCP_ERR_MODE_NOT_VALID;
  }
  /* Command allowed once per DaqList only */
  else if ((XCP_DAQ_FLAGS(CmdPtr->DaqListNum_u16, protLayerId) & XCP_DAQFLAG_RECEIVED_DAQ_LIST_MODE) != 0u)
  {
    Error = XCP_ERR_SEQUENCE;
  }
  /* Checks for direction STIM */
  else if ((CmdPtr->Mode_u8 & XCP_DAQLISTMODE_DIRECTION_STIM) == XCP_DAQLISTMODE_DIRECTION_STIM)
  {
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_OFF)
    /* STIM feature disabled, mode not valid */
    Error = XCP_ERR_MODE_NOT_VALID;
# else   /* XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON */
    /* Check if STIM is disabled */
    if ((Xcp_GlobalNoInit.EnabledResources_u8 & XCP_RESOURCE_STIM) == 0u)
    {
      Error = XCP_ERR_MODE_NOT_VALID;
    }
#  if(XCP_SEED_AND_KEY == STD_ON)
    /* Check if STIM is locked */
    else if ((Xcp_NoInit[protLayerId].Session.ResourceProtStatus_u8 & XCP_RESOURCE_STIM) == XCP_RESOURCE_STIM)
    {
      Error = XCP_ERR_ACCESS_LOCKED;
    }
#  endif  /* XCP_SEED_AND_KEY == STD_ON */
    else
    {
      /* Update the Total ODTs allocated count for STIM */
      Xcp_NoInit[protLayerId].DaqConfig.OdtStimCnt_u16 += XCP_DAQ_ODTCNT(CmdPtr->DaqListNum_u16, protLayerId);

      /* Check if sufficient memory is available for the DAQ list with direction STIM */
      if (Xcp_DaqRamCheck(0, 0, 0, protLayerId) == FALSE)
      {
        Error = XCP_ERR_MEMORY_OVERFLOW;
        /* Reduce already allocated count for STIM */
        Xcp_NoInit[protLayerId].DaqConfig.OdtStimCnt_u16 -= XCP_DAQ_ODTCNT(CmdPtr->DaqListNum_u16, protLayerId);
      }
    }
# endif    /* XCP_SYNCHRONOUS_DATA_STIMULATION_STIM */
  }
  /* Checks for direction DAQ */
  else
  {
    /* Check if sufficient memory is available for the DAQ list with direction DAQ */
    if (Xcp_DaqRamCheck(0, 0, 0, protLayerId) == FALSE)
    {
      Error = XCP_ERR_MEMORY_OVERFLOW;
    }
  }

  if (Error == XCP_NO_ERROR)
  {
    DaqListPtr = &(XCP_DAQ(CmdPtr->DaqListNum_u16, protLayerId));
    /* set flag Received status  */
    DaqListPtr->Flags_u8 = (DaqListPtr->Flags_u8 | XCP_DAQFLAG_RECEIVED_DAQ_LIST_MODE);
    /* Update the parameter of the DAQ list */
    DaqListPtr->Mode_u8             = CmdPtr->Mode_u8;
    /* Unconfigured event channel can also be set to the daq list, hence received event channel
     * number is not checked against total number of event channel (XCP_MAX_EVENT_CHANNEL) */
    DaqListPtr->EventChannelNum_u16 = CmdPtr->EventChannelNum_u16 ;
    DaqListPtr->Prescaler_u8        = CmdPtr->TransmissionRatePrescaler_u8;
    DaqListPtr->Priority_u8         = CmdPtr->DaqListPriority_u8;
    /* ask TL for XcpTxPduId for faster transmission */
    ActiveTLId = XCP_ACTIVE_TL_ID(protLayerId);
    DaqListPtr->XcpTxPduId = Xcp_PlCfgConst.TlCfg[ActiveTLId].TLGetTxPduId_pfct(XCP_PACKET_ID_DAQ_MAX, CmdPtr->EventChannelNum_u16, ActiveTLId);

    /* Send positive response */
    Xcp_SendPosRes(protLayerId);
  }
  else
  {
    /* Send negative response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdSetDaqListMode.c: The command is not enabled - no code is needed in this file */
#endif



