

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"

#if(XCP_ON_CAN_ENABLED == STD_ON)
#include "CanIf.h"
#include "XcpOnCan_Cfg.h"
#include "XcpOnCan_Cbk.h"

/* Check versions */
#if (!defined(CANIF_AR_RELEASE_MAJOR_VERSION) || (CANIF_AR_RELEASE_MAJOR_VERSION != XCP_AR_RELEASE_MAJOR_VERSION))
  #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANIF_AR_RELEASE_MINOR_VERSION) || (CANIF_AR_RELEASE_MINOR_VERSION != XCP_AR_RELEASE_MINOR_VERSION))
  #error "AUTOSAR minor version undefined or mismatched"
#endif


/***************************************************************************************************
* Variables
***************************************************************************************************/

#if (XCP_CAN_DIRECT_TRANSMIT == STD_ON)
/* this section is needed for the CAN Direct Transmit */
/*********************** START PERIPHERAL_CORE_FAST_RAM ***********************/
#define XCP_START_PERIPHERAL_CORE_FAST_RAM
#include "Xcp_MemMap.h"
static rba_CanDirectHWInfo_o Xcp_CanDirectHWInfo_ao[XCP_CAN_NUMBER_OF_TX_PDUS];
#define XCP_STOP_PERIPHERAL_CORE_FAST_RAM
#include "Xcp_MemMap.h"
/*********************** STOP PERIPHERAL_CORE_FAST_RAM ***********************/
#endif

/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function is called by the lower layers when an AUTOSAR XCP PDU has been received
\param[in]  XcpRxPduId    PduId that has been received
\param[in]  XcpRxPduPtr   Pointer to received Pdu
\return     -
***************************************************************************************************/
void Xcp_CanIfRxIndication(PduIdType XcpRxPduId, const PduInfoType* XcpRxPduPtr)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_RX_INDICATION_SID, XCP_E_NOT_INITIALIZED);
  /* If XcpRxPduPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduPtr == NULL_PTR), XCP_RX_INDICATION_SID, XCP_E_NULL_POINTER);
  /* If SduDataPtr within XcpRxPduPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduPtr->SduDataPtr == NULL_PTR), XCP_RX_INDICATION_SID, XCP_E_NULL_POINTER);
  /* If Invalid RxPduId, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduId >= XCP_CAN_NUMBER_OF_RX_PDUS), XCP_RX_INDICATION_SID, XCP_E_INVALID_PDUID);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Check if there is at least one byte in received packet */
  if (XcpRxPduPtr->SduLength > 0u)
  {
    /* Resolve RxPduId to global TransportLayerId and call receive function from protocol layer */
    Xcp_Receive(XcpRxPduPtr, Xcp_CanCfgConst.RxPduId2TlId_u8[XcpRxPduId]);
  }
  else
  {
    XCP_DET_REPORT_ERROR_NO_RET(XCP_RX_INDICATION_SID, XCP_E_DATA_PACKET_EMPTY);
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
This function is called by protocol layer to transmit XcpPackets
\param[in]  XcpPacketPtr          Pointer to XcpPacket (with Length and data pointer)
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\param[in]  XcpTxPduId            XcpTxPduId (relevant for CAN only)
\return     status of the transmit request
***************************************************************************************************/
Std_ReturnType Xcp_CanTransmit(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId, Xcp_PduIdType XcpTxPduId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  PduIdType CanIfTxPduId;
  Std_ReturnType Status_u8;
#if (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON)
  Xcp_CanTxBuffer_t * TransportLayerCanBuffer;
  uint8_least i;
#endif

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TRANSMIT_SID, XCP_E_NOT_INITIALIZED, E_NOT_OK);
  /* If XcpPacketPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr == NULL_PTR), XCP_TRANSMIT_SID, XCP_E_NULL_POINTER, E_NOT_OK);
  /* Check if Packet length is zero, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr->SduLength == 0u), XCP_TRANSMIT_SID, XCP_E_DATA_PACKET_EMPTY, E_NOT_OK);
  /* Check if Packet length is too long, report to DET and exit the function  */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XCP_DET_REPORT_ERROR_RET((((XcpPacketPtr->SduDataPtr[0] <= XCP_PACKET_ID_DAQ_MAX)&&(XcpPacketPtr->SduLength > Xcp_CanCfgConst.CanTlCfg[XcpTransportLayerId-XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET].Max_Dto_u16))
                          ||((XcpPacketPtr->SduDataPtr[0] >  XCP_PACKET_ID_DAQ_MAX)&&(XcpPacketPtr->SduLength > Xcp_CanCfgConst.CanTlCfg[XcpTransportLayerId-XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET].Max_Cto_u8))),
                          XCP_TRANSMIT_SID, XCP_E_DATA_PACKET_TOO_LONG, E_NOT_OK);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* XcpTxPduId is set for DAQ Pdus */
  if (XcpTxPduId != XCP_PDU_ID_UNKNOWN)
  {
#if (XCP_CAN_DIRECT_TRANSMIT == STD_ON)
    /* fast CAN Direct Transmit */
    /* MR12 RULE 11.5, 1.1 VIOLATION: Pointers are 32-bit-aligned so casting is no problem
                                      Casting over void* is necessary as otherwise some compilers complain */
    Status_u8 = CanIf_DirectHw_Write( (uint32*) (void*) XcpPacketPtr->SduDataPtr, (uint32) XcpPacketPtr->SduLength, &Xcp_CanDirectHWInfo_ao[XcpTxPduId]);
#else
    /*--- DET reporting ----------------------------------------------------------------------------*/
    /* Check if valid TxPduId and if not report to DET and exit function */
    XCP_DET_REPORT_ERROR_RET((XcpTxPduId >= XCP_CAN_NUMBER_OF_TX_PDUS), XCP_TRANSMIT_SID, XCP_E_INVALID_PDUID, E_NOT_OK);
    /*--- / DET reporting --------------------------------------------------------------------------*/

    CanIfTxPduId = Xcp_CanCfgConst.CanTxPduCfg[XcpTxPduId].CanIfTxPduId;

    /* Send data packet by CAN interface function */
    Status_u8 = CanIf_Transmit(CanIfTxPduId, XcpPacketPtr);
#endif /* XCP_CAN_DIRECT_TRANSMIT == STD_ON */
  }
  /* XcpTxPduId is not set for RES_ERR_EV_SERV */
  else
  {
    /* Get PduId of first entry in CanTxPduCfg for CAN TransportLayer (the type is always RES_ERR_EV_SERV_DAQ - no other checks are needed) */
    /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
    XcpTxPduId = Xcp_CanCfgConst.CanTlCfg[XcpTransportLayerId-XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET].TxPduCfgOffset_u8;

    /*--- DET reporting ----------------------------------------------------------------------------*/
    /* Check if valid TxPduId and if not report to DET and exit function */
    XCP_DET_REPORT_ERROR_RET((XcpTxPduId >= XCP_CAN_NUMBER_OF_TX_PDUS), XCP_TRANSMIT_SID, XCP_E_INVALID_PDUID, E_NOT_OK);
    /*--- / DET reporting --------------------------------------------------------------------------*/

    CanIfTxPduId = Xcp_CanCfgConst.CanTxPduCfg[XcpTxPduId].CanIfTxPduId;

    /* Send data packet by CAN interface function */
    Status_u8 = CanIf_Transmit(CanIfTxPduId, XcpPacketPtr);
  }

#if (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON)
  /*--- Buffering --------------------------------------------------------------------------------*/
  /* Check if transmission was NOT successful */
  if (Status_u8 != E_OK)
  {
    /* Get pointer to buffer of this transport layer */
    /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
    TransportLayerCanBuffer = &(Xcp_CanTxBuffer[XcpTransportLayerId-XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET]);
    /* Store data of XcpPacket for later transmission */
    TransportLayerCanBuffer->CanIfTxPduId = CanIfTxPduId;
    TransportLayerCanBuffer->XcpPacket.SduLength = XcpPacketPtr->SduLength;

    /* Copy XcpPacket data */
    for (i = 0 ; i < XcpPacketPtr->SduLength ; i++)
    {
      TransportLayerCanBuffer->XcpPacket.SduDataPtr[i] = XcpPacketPtr->SduDataPtr[i];
    }
    /* Mark that buffer is filled in and ready for transmission */
    /* Must be set here and not before! */
    TransportLayerCanBuffer->DataInBuffer_b = TRUE;
    /* Set status to OK to prevent double-sending the same packet */
    Status_u8 = E_OK;
  }
  /*--- / Buffering ------------------------------------------------------------------------------*/
#endif /* (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON) */

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  /* Return status */
  return(Status_u8);
}


/**
****************************************************************************************************
This function is called by the lower layers when an AUTOSAR XCP PDU has been transmitted
\param[in]  XcpTxPduId  PduId that has been transmitted
\return     -
***************************************************************************************************/
void Xcp_CanIfTxConfirmation(PduIdType XcpTxPduId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TX_CONFIRMATION_SID, XCP_E_NOT_INITIALIZED);
  /* If Invalid TxPduId, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpTxPduId >= XCP_CAN_NUMBER_OF_TX_PDUS), XCP_TX_CONFIRMATION_SID, XCP_E_INVALID_PDUID);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Resolve global Transport Layer Id from TxPduId and confirm protocol layer of successful transmission */
  Xcp_TxConfirmation(Xcp_CanCfgConst.TxPduId2TlId_u8[XcpTxPduId]);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Xcp main function for buffered transmission
\param[in]  -
\return     -
***************************************************************************************************/
void Xcp_CanMainFunction(void)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

#if (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON)
  /* Local variables */
  uint8_least i;

  /* Check all CAN Transport Layers if there is anything buffered for transmission */
  for (i = 0 ; i < XCP_CAN_NUMBER_OF_TRANSPORT_LAYERS ; i++)
  {
    /* Check if data in buffer to transmit */
    if (Xcp_CanTxBuffer[i].DataInBuffer_b != FALSE)
    {
      /* Disable interrupts */
      SchM_Enter_Xcp_CanBuffering();

      /* Check if buffer is locked because another function/core tries to transmit */
      if (Xcp_CanTxBuffer[i].Locked_b == FALSE)
      {
        /* Inform other cores that buffering process is running */
        Xcp_CanTxBuffer[i].Locked_b = TRUE;

        /* Enable interrupts */
        SchM_Exit_Xcp_CanBuffering();

        /* Check if buffer is still filled with data and ready to send */
        if (Xcp_CanTxBuffer[i].DataInBuffer_b != FALSE)
        {
          /* Clear the flags before transmit, because TxConfirmation might start in parallel on different core */
          Xcp_CanTxBuffer[i].DataInBuffer_b = FALSE;

          /* Transmit and check if the transmission was not successful */
          if (E_OK != CanIf_Transmit(Xcp_CanTxBuffer[i].CanIfTxPduId, &Xcp_CanTxBuffer[i].XcpPacket))
          {
            /* Notify that transmission is still pending */
            Xcp_CanTxBuffer[i].DataInBuffer_b = TRUE;
          }
        }
        Xcp_CanTxBuffer[i].Locked_b = FALSE;
      }
      else
      {
        /* Enable interrupts */
        SchM_Exit_Xcp_CanBuffering();
      }
    }
  }
#else /* (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON) */
  /* Dummy statement to satisfy HIS metrics */
  do {} while (0);
#endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Initialization of the transport layer internal variables
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\param[in]  XcpInitStatus         was Xcp already initialized before or not
\return     -
***************************************************************************************************/
void Xcp_CanInit(uint8 XcpTransportLayerId, uint8 XcpInitStatus)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

#if (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON)
  /* Local variables */
  uint8 XcpCanTlId;

  /* Shift the transport layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpCanTlId = XcpTransportLayerId - XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET;

  /* Initialize specific CAN Transport Layers */
  /* Reset flag, that anything is in the buffer */
  Xcp_CanTxBuffer[XcpCanTlId].DataInBuffer_b = FALSE;
  /* Reset flag, that buffer is in use */
  Xcp_CanTxBuffer[XcpCanTlId].Locked_b = FALSE;
  /* Reset length of buffered data */
  Xcp_CanTxBuffer[XcpCanTlId].XcpPacket.SduLength = 0;
  /* Init XcpPacket data pointer with address of existing data buffer */
  Xcp_CanTxBuffer[XcpCanTlId].XcpPacket.SduDataPtr = Xcp_CanTxBuffer[XcpCanTlId].DataBuffer_au8;

#else
  XCP_PARAM_UNUSED(XcpTransportLayerId);
#endif /* (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON) */

#if (XCP_CAN_DIRECT_TRANSMIT == STD_ON)
  {
    uint8_least i;

    /* fetch CAN Direct Transmit Information for all Tx PDUs*/
    for (i = 0; i < XCP_CAN_NUMBER_OF_TX_PDUS; i++)
    {
      if ( CanIf_Get_DirectHw_Info(Xcp_CanCfgConst.CanTxPduCfg[i].CanIfTxPduId, &(Xcp_CanDirectHWInfo_ao[i])) != E_OK )
      {
        /* received E_NOT_OK from CanIf */
        /* This leads to NULL_PTR-error lateron. But DET is sufficient here, as the error is a configuration error */
        XCP_DET_REPORT_ERROR_NO_RET(XCP_INITIALIZE_SID, XCP_E_INIT_FAILED);
      }
    }
  }
#endif /* (XCP_CAN_DIRECT_TRANSMIT == STD_ON) */
  XCP_PARAM_UNUSED(XcpInitStatus);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Connect command related handling for the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
void Xcp_CanConnect(uint8 XcpTransportLayerId)
{
  XCP_PARAM_UNUSED(XcpTransportLayerId);
  /* Nothing to do in XcpOnCan */
}


/**
****************************************************************************************************
Disconnects the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     result of disconnect request
***************************************************************************************************/
Std_ReturnType Xcp_CanDisconnect(uint8 XcpTransportLayerId)
{
  XCP_PARAM_UNUSED(XcpTransportLayerId);
  /* Nothing to do in XcpOnCan */
  return E_OK;
}


/**
****************************************************************************************************
This function handles specific Transport Layer Commands
\param[in]  XcpCmdPacketPtr       Pointer to XcpPacket with received command
\param[out] XcpResPacketPtr       Pointer to XcpPacket where the response shall be stored
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
/* MR12 RULE 8.13 VIOLATION: content of XcpResPacketPtr will be changed, when function is used */
void Xcp_CanTransportLayerCmd(const PduInfoType* XcpCmdPacketPtr, PduInfoType* XcpResPacketPtr, uint8 XcpTransportLayerId)
{
  /* Remove when params used */
  XCP_PARAM_UNUSED(XcpCmdPacketPtr);
  XCP_PARAM_UNUSED(XcpResPacketPtr);
  XCP_PARAM_UNUSED(XcpTransportLayerId);
  /* Nothing to do in XcpOnCan */
}


/**
****************************************************************************************************
This function is called by protocol layer to find a XcpTxPduId for a given EventChannel
\param[in]  XcpPacketId             Type of the packet (1st byte of packets to transmit)
\param[in]  XcpEventChannelNumber   Event channel number (relevant for CAN only)
\param[in]  XcpTransportLayerId     Id if Transport Layer given by Protocol layer
\return     XcpTxPduId
***************************************************************************************************/
Xcp_PduIdType Xcp_CanGetTxPduId(uint8 XcpPacketId, uint16 XcpEventChannelNumber, uint8 XcpTransportLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  const Xcp_CanTlCfgConst_t * TransportLayerCfgPtr = &(Xcp_CanCfgConst.CanTlCfg[XcpTransportLayerId-XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET]);
  Xcp_PduIdType XcpTxPduId;

  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XCP_DET_REPORT_ERROR_RET(((XcpTransportLayerId-XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET) >= XCP_CAN_NUMBER_OF_TRANSPORT_LAYERS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, XCP_PDU_ID_UNKNOWN);

#if (XCP_CAN_TL_ONLY_ONE_TX_PDU == STD_OFF)
  /*
  Algorithm explanation:
  if only one TxPdu
    use always this Pdu (because it must be RES_ERR_EV_SERV_DAQ)
  else
    if DAQ -> search for corresponding EventChannelNr in all Pdus starting from end
      if not found use default one (first is RES_ERR_EV_SERV_DAQ)
    else -> RES_ERR_EV_SERV get PduId of 1st entry in the proper TxPduConfig
  */

  /* Check if more then one TxPdu for this CAN Transport Layer */
  if (TransportLayerCfgPtr->TxPduCfgCount_u8 > 1u)
  {
    sint16_least i;
    /* Start with default PduId for Event Channel */
    XcpTxPduId = XCP_PDU_ID_UNKNOWN;

    /* Check if PacketType is DAQ */
    if (XcpPacketId <= XCP_PACKET_ID_DAQ_MAX)
    {
      /* Find PduId where XcpEventChannelNumber is matching */
      for (i = TransportLayerCfgPtr->TxPduCfgOffset_u8 + (TransportLayerCfgPtr->TxPduCfgCount_u8 - 1u) ; i >= (sint16_least)(TransportLayerCfgPtr->TxPduCfgOffset_u8) ; i--)
      {
        /* Check if EventChannel Nr is matching */
        if ( (Xcp_CanCfgConst.CanTxPduCfg[i].EventChannelNr_u16 == XcpEventChannelNumber) ||
        /* Or check if it is the default XcpEventChannelNumber - it will be the first (RES_ERR_EV_SERV) or second (DAQ without EventChannelRef) */
             (Xcp_CanCfgConst.CanTxPduCfg[i].EventChannelNr_u16 == XCP_EVENT_CHANNEL_NOT_USED)
           )
        {
          /* Get the PduId */
          XcpTxPduId = (Xcp_PduIdType)i;
          /* And leave the loop */
          break;
        }
      }
    }

    /* PacketType is RES_ERR_EV_SERV or RES_ERR_EV_SERV_DAQ */
    else
    {
      /* Get PduId of first entry in TxPduConfig table for CAN TransportLayer */
       XcpTxPduId = TransportLayerCfgPtr->TxPduCfgOffset_u8;
    }
  }
  else
#else
  XCP_PARAM_UNUSED(XcpEventChannelNumber);
  XCP_PARAM_UNUSED(XcpPacketId);
#endif /* (XCP_CAN_TL_ONLY_ONE_TX_PDU == STD_OFF) */
  {
    /* Get PduId of first entry in CanTxPduCfg for (the type is always RES_ERR_EV_SERV_DAQ - no other checks are needed) */
    XcpTxPduId = TransportLayerCfgPtr->TxPduCfgOffset_u8;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return XcpTxPduId;
}

#if ((XCP_RESUME_MODE == STD_ON) && (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON))
/**
****************************************************************************************************
This function is called to copy transport layer needed data for Resume Mode
\param[in]  DaqRamPtr             Pointer to Daq RAM address where data is saved
\param[in]  XcpDaqRamEndPtr       Last DAQ RAM address for requested Protocol Layer
\param[in]  XcpTransportLayerId   Id if Transport Layer given by Protocol layer
\return     Error code in case is not enough space to save the data
***************************************************************************************************/
/* MR12 RULE 8.13 VIOLATION: The pointer is for reference only and cannot be constant. Same function definition must be used for all transport layers. */
Xcp_ErrorCode Xcp_CanResumeModeData(Xcp_AdrPtr DaqRamPtr, Xcp_AdrPtrConst XcpDaqRamEndPtr, uint8 XcpTransportLayerId)
{
  XCP_PARAM_UNUSED(DaqRamPtr);
  XCP_PARAM_UNUSED(XcpDaqRamEndPtr);
  XCP_PARAM_UNUSED(XcpTransportLayerId);

  return XCP_NO_ERROR;
}
#endif

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


#endif
/* HIS METRIC COMF VIOLATION IN XcpOnCan.c: If Xcp on CAN is disabled, this file is empty. */


