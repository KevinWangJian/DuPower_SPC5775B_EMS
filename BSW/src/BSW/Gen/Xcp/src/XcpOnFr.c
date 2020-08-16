

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"

#if (XCP_ON_FLEXRAY_ENABLED == STD_ON)
#include "FrIf.h"
#include "XcpOnFr_Types.h"
#include "XcpOnFr_Cfg.h"
#include "XcpOnFr_Cbk.h"

/* Check versions */
#if (!defined(FRIF_AR_RELEASE_MAJOR_VERSION) || (FRIF_AR_RELEASE_MAJOR_VERSION != XCP_AR_RELEASE_MAJOR_VERSION))
  #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FRIF_AR_RELEASE_MINOR_VERSION) || (FRIF_AR_RELEASE_MINOR_VERSION != XCP_AR_RELEASE_MINOR_VERSION))
  #error "AUTOSAR minor version undefined or mismatched"
#endif


/*
Design decisions:
Rx Pdus: PacketStart points always to start of new XcpPacket
Tx Pdus: Length points to the length for next frame (LEN). Reason for not pointing to start of new XcpPacket:
         FlexRay frame has maximum length of 254 byte. Start position of new XcpPacket would be 256.
         With uint8 this would be 0. To save RAM Length points to LEN and not to start of next XcpPacket
*/


/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/
/** Mark the given Pdu as blocked */
#define XCP_BLOCK_PDU(PduId)      do { Xcp_FrCfgCleared.TxPduBlocked_ab[PduId] = TRUE; } while (0)
/** Clear the given Pdu and mark it as free */
#define XCP_EMPTY_PDU(PduId)      do { Xcp_FrCfgCleared.TxPdu[PduId].SduLength = 1; Xcp_FrCfgCleared.TxPduBlocked_ab[PduId] = FALSE;} while (0) /* 1 because on position 0 is always NAX */
/** Is the given Pdu blocked? */
#define XCP_IS_PDU_BLOCKED(PduId) Xcp_FrCfgCleared.TxPduBlocked_ab[PduId]

/* Header and alignment definitions */
#if (XCP_FR_PACKET_ALIGNMENT == XCP_FR_PACKET_ALIGNMENT_8)
  #define XCP_FR_ALIGNMENT_MASK 0u
  #if ((XCP_FR_FRAME_CONCATENATION == STD_OFF) && (XCP_FR_SEQUENCE_CORRECTION == STD_OFF))
    #define XCP_FR_HEADER_SIZE 1u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_ON) && (XCP_FR_SEQUENCE_CORRECTION == STD_OFF))
    #define XCP_FR_HEADER_SIZE 2u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_OFF) && (XCP_FR_SEQUENCE_CORRECTION == STD_ON))
    #define XCP_FR_HEADER_SIZE 2u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_ON) && (XCP_FR_SEQUENCE_CORRECTION == STD_ON))
    #define XCP_FR_HEADER_SIZE 3u
  #endif
#elif (XCP_FR_PACKET_ALIGNMENT == XCP_FR_PACKET_ALIGNMENT_16)
  #define XCP_FR_ALIGNMENT_MASK 1u
  #if ((XCP_FR_FRAME_CONCATENATION == STD_OFF) && (XCP_FR_SEQUENCE_CORRECTION == STD_OFF))
    #define XCP_FR_HEADER_SIZE 2u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_ON) && (XCP_FR_SEQUENCE_CORRECTION == STD_OFF))
    #define XCP_FR_HEADER_SIZE 2u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_OFF) && (XCP_FR_SEQUENCE_CORRECTION == STD_ON))
    #define XCP_FR_HEADER_SIZE 2u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_ON) && (XCP_FR_SEQUENCE_CORRECTION == STD_ON))
    #define XCP_FR_HEADER_SIZE 4u
  #endif
#elif (XCP_FR_PACKET_ALIGNMENT == XCP_FR_PACKET_ALIGNMENT_32)
  #define XCP_FR_ALIGNMENT_MASK 3u
  #if ((XCP_FR_FRAME_CONCATENATION == STD_OFF) && (XCP_FR_SEQUENCE_CORRECTION == STD_OFF))
    #define XCP_FR_HEADER_SIZE 4u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_ON) && (XCP_FR_SEQUENCE_CORRECTION == STD_OFF))
    #define XCP_FR_HEADER_SIZE 4u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_OFF) && (XCP_FR_SEQUENCE_CORRECTION == STD_ON))
    #define XCP_FR_HEADER_SIZE 4u
  #elif ((XCP_FR_FRAME_CONCATENATION == STD_ON) && (XCP_FR_SEQUENCE_CORRECTION == STD_ON))
    #define XCP_FR_HEADER_SIZE 4u
  #endif
#endif


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"
/** Array for conversion from PacketId into PacketType - usage: PacketType = XcpFrPacketId2PacketType[0xff-PacketId]; */
static const Xcp_PacketType_t XcpFrPacketId2PacketType[] =
{
  XCP_PACKET_TYPE_RES_ERR,
  XCP_PACKET_TYPE_RES_ERR,
  XCP_PACKET_TYPE_EV_SERV,
  XCP_PACKET_TYPE_EV_SERV
};
#define XCP_STOP_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"
static Std_ReturnType   Xcp_FrTransmitInMainfunction(const PduInfoType* XcpPacketPtr, uint8 XcpFrTransportLayerId);
static Xcp_PacketType_t Xcp_FrPacketId2PacketType(uint8 XcpPacketId);
static Xcp_PduIdType    Xcp_FrGetFreeTxPduId(Xcp_PacketType_t XcpPacketType, uint8 XcpFrTransportLayerId);
static Std_ReturnType   Xcp_FrNoFreeTxPduId(Xcp_PacketType_t XcpPacketType, uint8 XcpFrTransportLayerId);
static PduLengthType    Xcp_FrInsertHeader(Xcp_PduIdType XcpTxPduId, uint8 XcpFrTransportLayerId);
#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
static void             Xcp_FrFinishFrame(Xcp_PduIdType XcpTxPduId);
#endif
#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
#if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON)
static Xcp_ErrorCode  Xcp_FrTransportLayerCmd_Assign(const PduInfoType* XcpCmdPacketPtr, uint8 XcpFrTransportLayerId);
static Xcp_ErrorCode  Xcp_FrTransportLayerCmd_Activate(const PduInfoType* XcpCmdPacketPtr, uint8 XcpFrTransportLayerId);
static Xcp_ErrorCode  Xcp_FrTransportLayerCmd_Deactivate(const PduInfoType* XcpCmdPacketPtr, uint8 XcpFrTransportLayerId);
#endif
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


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
void Xcp_FrIfRxIndication(PduIdType XcpRxPduId, const PduInfoType* XcpRxPduPtr)
{
  /* Local variables */
  PduInfoType XcpPacketPtr;
  uint8 XcpTransportLayerId;
  PduLengthType PacketStart;
  uint32 XcpBuffer4Alignment[(XCP_FR_RX_PDU_LEN_MAX + 3u) / 4u];

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_RX_INDICATION_SID, XCP_E_NOT_INITIALIZED);
  /* If XcpRxPduPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduPtr == NULL_PTR), XCP_RX_INDICATION_SID, XCP_E_NULL_POINTER);
  /* If SduDataPtr within XcpRxPduPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduPtr->SduDataPtr == NULL_PTR), XCP_RX_INDICATION_SID, XCP_E_NULL_POINTER);
  /* If Invalid RxPduId, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduId >= XCP_FR_NUMBER_OF_RX_PDUS), XCP_RX_INDICATION_SID, XCP_E_INVALID_PDUID);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Get TransportLayer Id related to received PduId */
  XcpTransportLayerId = Xcp_FrCfgConst.RxPduCfg[XcpRxPduId].TLId_u8;

  /* Check if the message is for this Transport Layer (compare NAX) */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  if (XcpRxPduPtr->SduDataPtr[0] == Xcp_FrCfgConst.TlCfg[XcpTransportLayerId-XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET].Nax_u8)
  {
    /* Set PacketStart after header */
    PacketStart = XCP_FR_HEADER_SIZE;
#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
    /* Check if any data to process (LEN > 0) && if packet data is in boundaries of RxPdu */
    while ((XcpRxPduPtr->SduDataPtr[PacketStart-1u] > 0) && ((PacketStart + XcpRxPduPtr->SduDataPtr[PacketStart-1u]) <= XcpRxPduPtr->SduLength))
    {
      /* Extract length of the XCP packet which will be sent to Protocol Layer */
      XcpPacketPtr.SduLength = XcpRxPduPtr->SduDataPtr[PacketStart-1u];
#else
    /* Check if any data to process */
    if (XcpRxPduPtr->SduLength > XCP_FR_HEADER_SIZE)
    {
      /* Calculate the length of the XCP packet which will be sent to Protocol Layer */
      XcpPacketPtr.SduLength = XcpRxPduPtr->SduLength - XCP_FR_HEADER_SIZE;
#endif
      /* Set pointer to PacketStart */
      XcpPacketPtr.SduDataPtr = XcpRxPduPtr->SduDataPtr + PacketStart;

      /* Align XCP packet to uint32 for protocol layer */
      /* MR12 RULE 11.4 VIOLATION: Cast from pointer to uint32 is OK as the addresses are 32bit long */
      if (((uint32)(XcpPacketPtr.SduDataPtr) & 0x3u) != 0u)
      {
        /* Pdu length can not be bigger than maximum configured for the corresponding TL */
        XcpPacketPtr.SduLength = XCP_MIN(XcpPacketPtr.SduLength, XCP_FR_RX_PDU_LEN_MAX);
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        Xcp_MemCopy(XcpBuffer4Alignment, XcpPacketPtr.SduDataPtr, XcpPacketPtr.SduLength);
        XcpPacketPtr.SduDataPtr = (uint8*)XcpBuffer4Alignment;
      }
      /* Call protocol layer receive function */
      Xcp_Receive(&XcpPacketPtr, XcpTransportLayerId);
#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
      /* Move PacketStart in received frame to beginning of next XcpPacket */
      PacketStart = ((PacketStart + XcpPacketPtr.SduLength) | XCP_FR_ALIGNMENT_MASK) + 1u;
#endif
    }
  } /* NAX check */
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
Std_ReturnType Xcp_FrTransmit(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId, Xcp_PduIdType XcpTxPduId)
{
  /* Local variables */
  Std_ReturnType RetVal;
  uint8 XcpFrTransportLayerId;

  /* Shift the Transport Layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpFrTransportLayerId = XcpTransportLayerId - XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET;

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TRANSMIT_SID, XCP_E_NOT_INITIALIZED, E_NOT_OK);
  /* If XcpPacketPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr == NULL_PTR), XCP_TRANSMIT_SID, XCP_E_NULL_POINTER, E_NOT_OK);
  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpFrTransportLayerId >= XCP_FR_NUMBER_OF_TRANSPORT_LAYERS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, E_NOT_OK);
  /* If this function is called before transmission in FrMainFunctionTx, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduLength != 0u), XCP_TRANSMIT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL, E_NOT_OK);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Used only in XcpOnCan */
  XCP_PARAM_UNUSED(XcpTxPduId);

#if (XCP_FR_TRANSMIT_IN_MAINFUNCTION == STD_ON)
  /* Store pointer to Xcp Packet and TransportLayer Id */
  Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduDataPtr = XcpPacketPtr->SduDataPtr;
  Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduLength  = XcpPacketPtr->SduLength;   /* Must be after SduDataPtr */
  RetVal = E_OK;
#else
  /* Lock interrupts */
  SchM_Enter_Xcp_FrTransmit();
  /* Call internal Transmit function */
  RetVal = Xcp_FrTransmitInMainfunction(XcpPacketPtr, XcpFrTransportLayerId);
  /* Internal transmission successful? */
  if (RetVal == E_OK)
  {
    /* Store pointer to Xcp Packet and TransportLayer Id */
    Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduDataPtr = XcpPacketPtr->SduDataPtr;
    Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduLength  = XcpPacketPtr->SduLength;   /* Must be after SduDataPtr */
  }
  /* Unlock interrupts */
  SchM_Exit_Xcp_FrTransmit();
#endif

  return RetVal;
}


/**
****************************************************************************************************
Local function for handling the frame transmission, called from Xcp_FrMainFunctionTx or Xcp_FrTransmit
\param[in]  XcpPacketPtr            Pointer to XcpPacket (with Length and data pointer)
\param[in]  XcpFrTransportLayerId   Local FlexRay Transport Layer Id
\return     status of the transmit request
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_FrTransmitInMainfunction: HIS metric compliance would decrease readability and maintainability. */
static Std_ReturnType Xcp_FrTransmitInMainfunction(const PduInfoType* XcpPacketPtr, uint8 XcpFrTransportLayerId)
{
  /* Local variables */
  Xcp_PduIdType PduId;
  PduLengthType PduLengthLocal;
  PduInfoType* TxPduPtr;
  Std_ReturnType RetVal;
  Xcp_PacketType_t XcpPacketType;

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TRANSMIT_SID, XCP_E_NOT_INITIALIZED, E_NOT_OK);
  /* If XcpPacketPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr == NULL_PTR), XCP_TRANSMIT_SID, XCP_E_NULL_POINTER, E_NOT_OK);
  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpFrTransportLayerId >= XCP_FR_NUMBER_OF_TRANSPORT_LAYERS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, E_NOT_OK);
  /* If this function is called before transmission in FrMainFunctionTx, report to DET and exit the function */
#if (XCP_FR_TRANSMIT_IN_MAINFUNCTION == STD_ON)
  XCP_DET_REPORT_ERROR_RET((Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduLength == 0u), XCP_TRANSMIT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL, E_NOT_OK);
#else
  XCP_DET_REPORT_ERROR_RET((Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduLength != 0u), XCP_TRANSMIT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL, E_NOT_OK);
#endif
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Initial value */
  RetVal = E_OK;
  /* Resolve packet type from Packet Id */
  XcpPacketType = Xcp_FrPacketId2PacketType(XcpPacketPtr->SduDataPtr[0]);
  /* Find Free XcpTxPduId */
  PduId = Xcp_FrGetFreeTxPduId(XcpPacketType, XcpFrTransportLayerId);

#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
  /* Pdu found? */
  if (PduId != XCP_PDU_ID_UNKNOWN)
  {
    /* Get pointer to TxPdu */
    TxPduPtr = &Xcp_FrCfgCleared.TxPdu[PduId];
    /* Insert XcpHeader and get new PduLength */
    PduLengthLocal = Xcp_FrInsertHeader(PduId, XcpFrTransportLayerId);

    /* Check if enough space in Pdu */
    if ((PduLengthLocal + 1u + XcpPacketPtr->SduLength) <= Xcp_FrCfgConst.TxPduCfg[PduId].PduSize_u8)
    {
      /* Store length before XcpPacket (LEN) */
      TxPduPtr->SduDataPtr[PduLengthLocal] = (uint8)XcpPacketPtr->SduLength;
      /* Copy data to PduBuffer buffer */
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(&(TxPduPtr->SduDataPtr[PduLengthLocal+1u]), XcpPacketPtr->SduDataPtr, XcpPacketPtr->SduLength);
      /* Update length of Pdu */
      TxPduPtr->SduLength = ((PduLengthLocal + 1u + XcpPacketPtr->SduLength) | XCP_FR_ALIGNMENT_MASK);
    }
    /* Check if Pdu contains header only (special case, e. g. RES_ERR doesn't fit into VARIABLE Pdu) */
    else if (PduLengthLocal == (XCP_FR_HEADER_SIZE - 1u))
    {
      RetVal = E_NOT_OK;
    }
    /* Not enough space in Pdu */
    else
    {
      /* Add zero length frame at the end, if needed */
      Xcp_FrFinishFrame(PduId);
      /* Block TxPdu */
      XCP_BLOCK_PDU(PduId);
      /* Call transmit function */
      if (FrIf_Transmit(Xcp_FrCfgConst.TxPduCfg[PduId].FrIfPduId, TxPduPtr) != E_OK)
      {
        /* Transmit error -> empty PDU */
        XCP_EMPTY_PDU(PduId);
        RetVal = E_NOT_OK;
        /* Increase DET counter */
        XCP_DEBUG_CTR_INC(Xcp_FrCfgCleared.Xcp_Debug_FrTxFrIfErrorCtr[XcpFrTransportLayerId]);
      }
      /* Transmit OK */
      else
      {
        /* Get next Pdu */
        PduId = Xcp_FrGetFreeTxPduId(XcpPacketType, XcpFrTransportLayerId);
        /* Pdu found? */
        if (PduId != XCP_PDU_ID_UNKNOWN)
        {
          /* Get pointer to TxPdu */
          TxPduPtr = &Xcp_FrCfgCleared.TxPdu[PduId];
          /* Insert XcpHeader and get new PduLength */
          PduLengthLocal = Xcp_FrInsertHeader(PduId, XcpFrTransportLayerId);

          /* Check if enough space in Pdu */
          if ((PduLengthLocal + 1u + XcpPacketPtr->SduLength) <= Xcp_FrCfgConst.TxPduCfg[PduId].PduSize_u8)
          {
            /* Store length before XcpPacket (LEN) */
            TxPduPtr->SduDataPtr[PduLengthLocal] = (uint8)XcpPacketPtr->SduLength;
            /* Copy data to PduBuffer buffer */
            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
            Xcp_MemCopy(&(TxPduPtr->SduDataPtr[PduLengthLocal+1u]), XcpPacketPtr->SduDataPtr, XcpPacketPtr->SduLength);
            /* Update length of Pdu */
            TxPduPtr->SduLength = ((PduLengthLocal + 1u + XcpPacketPtr->SduLength) | XCP_FR_ALIGNMENT_MASK);
          }
          else
          {
            RetVal = E_NOT_OK;
          }
        }
        else
        {
          RetVal = Xcp_FrNoFreeTxPduId(XcpPacketType, XcpFrTransportLayerId);
        }
      }
    }
  }
  else
  {
    RetVal = Xcp_FrNoFreeTxPduId(XcpPacketType, XcpFrTransportLayerId);
  }

#else   /* XCP_FR_FRAME_CONCATENATION == STD_OFF */

  /* Pdu found? */
  if ( (PduId != XCP_PDU_ID_UNKNOWN)
    && ((XCP_FR_HEADER_SIZE + XcpPacketPtr->SduLength) <= Xcp_FrCfgConst.TxPduCfg[PduId].PduSize_u8) )  /* Check if enough space in Pdu */
  {
    /* Get pointer to TxPdu */
    TxPduPtr = &Xcp_FrCfgCleared.TxPdu[PduId];
    /* Insert XcpHeader and get new PduLength */
    PduLengthLocal = Xcp_FrInsertHeader(PduId, XcpFrTransportLayerId);
    /* Copy data to PduBuffer buffer */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(&(TxPduPtr->SduDataPtr[PduLengthLocal+1u]), XcpPacketPtr->SduDataPtr, XcpPacketPtr->SduLength);
    /* Update length of Pdu */
    TxPduPtr->SduLength = PduLengthLocal + 1u + XcpPacketPtr->SduLength;
    /* Block TxPdu */
    XCP_BLOCK_PDU(PduId);
    /* Call transmit function */
    if (FrIf_Transmit(Xcp_FrCfgConst.TxPduCfg[PduId].FrIfPduId, TxPduPtr) != E_OK)
    {
      /* Transmit error -> empty PDU */
      XCP_EMPTY_PDU(PduId);
      /* Error */
      RetVal = E_NOT_OK;
      /* Increase DET counter */
      XCP_DEBUG_CTR_INC(Xcp_FrCfgCleared.Xcp_Debug_FrTxFrIfErrorCtr[XcpFrTransportLayerId]);
    }
  }
  else
  {
    RetVal = Xcp_FrNoFreeTxPduId(XcpPacketType, XcpFrTransportLayerId);
  }
#endif

  /* Return */
  return RetVal;
}


/**
****************************************************************************************************
This function is called by the lower layers when an AUTOSAR XCP PDU has been transmitted
\param[in]  XcpTxPduId  PduId that has been transmitted
\return     none
***************************************************************************************************/
void Xcp_FrIfTxConfirmation(PduIdType XcpTxPduId)
{
  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TX_CONFIRMATION_SID, XCP_E_NOT_INITIALIZED);
  /* If Invalid TxPduId, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpTxPduId >= XCP_FR_NUMBER_OF_TX_PDUS), XCP_TX_CONFIRMATION_SID, XCP_E_INVALID_PDUID);
  /* TxConfirmation called without previous Transmit, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XCP_IS_PDU_BLOCKED(XcpTxPduId) == FALSE), XCP_TX_CONFIRMATION_SID, XCP_E_UNEXPECTED_FUNCTION_CALL);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Unblock Pdu and release PduBuffer */
  XCP_EMPTY_PDU(XcpTxPduId);
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Xcp main function for transmission on Transport Layer
\param[in]  -
\return     -
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_FrMainFunctionTx: Function contains several necessary if statements. HIS metric compliance would decrease readability and maintainability. */
void Xcp_FrMainFunctionTx(void)
{
  uint8 i;
#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
  Xcp_PduIdType PduId;
#endif

  /* Check if at least one FR transport layer is connected */
  if (Xcp_FrCfgNoInit.ConnectedTLCtr_u8 > 0)
  {
    /* Check all FlexRay transport layers */
    for (i = 0 ; i < XCP_FR_NUMBER_OF_TRANSPORT_LAYERS ; i++)
    {
      /* Anything to transmit? */
      while ( (Xcp_FrCfgCleared.TxPacketPtr[i].SduLength != 0u)
#if (XCP_FR_TRANSMIT_IN_MAINFUNCTION == STD_ON)
           /* was transmit successful? */
           /* MR12 RULE 13.5 VIOLATION: Conditions are evaluated from left to right. The function call is only done if the first condition is TRUE - this is intended behavior; Redesign not possible as while loop and not if - change would decrease maintainability and increase runtime */
           && (Xcp_FrTransmitInMainfunction(&(Xcp_FrCfgCleared.TxPacketPtr[i]), i) == E_OK)
#endif
            )
      {
        Xcp_FrCfgCleared.TxPacketPtr[i].SduLength = 0;
        /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
        Xcp_TxConfirmation(i + XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET);
      }
    }

#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
  #if (XCP_FR_TRANSMIT_IN_MAINFUNCTION == STD_OFF)
    /* Lock interrupts */
    SchM_Enter_Xcp_FrTransmit();
  #endif
    /* Check all Pdus */
    for (PduId = 0 ; PduId < XCP_FR_NUMBER_OF_TX_PDUS ; PduId++)
    {
      /* Check if there is anything to transmit */
      if ( (XCP_IS_PDU_BLOCKED(PduId) == FALSE)
        && (Xcp_FrCfgCleared.TxPdu[PduId].SduLength > 1u))
      {
        Xcp_FrFinishFrame(PduId);
        /* Block TxPdu */
        XCP_BLOCK_PDU(PduId);
        /* Call transmit function */
        if (FrIf_Transmit(Xcp_FrCfgConst.TxPduCfg[PduId].FrIfPduId, &Xcp_FrCfgCleared.TxPdu[PduId]) != E_OK)
        {
          /* Transmit error -> empty PDU */
          XCP_EMPTY_PDU(PduId);
          /* Increase DET counter */
          XCP_DEBUG_CTR_INC(Xcp_FrCfgCleared.Xcp_Debug_FrTxFrIfErrorCtr[Xcp_FrCfgConst.TxPduCfg[PduId].TLId_u8]);
        }
      }
    }
  #if (XCP_FR_TRANSMIT_IN_MAINFUNCTION == STD_OFF)
    /* Unlock interrupts */
    SchM_Exit_Xcp_FrTransmit();
  #endif
#endif
  }
}


/**
****************************************************************************************************
Within this API, the upper layer module (called module) shall copy its data into the buffer provided
by PduInfoPtr->SduDataPtr and update the length of the actual copied data in PduInfoPtr->SduLength.
\param[in]  TxPduId     PduId that is requested to be transmitted
\param[in]  PduInfoPtr  Pointer to XcpPacket (with Length and data pointer)
\return     status of the transmit request
***************************************************************************************************/
Std_ReturnType Xcp_FrIfTriggerTransmit(PduIdType TxPduId, PduInfoType* PduInfoPtr)
{
  /* Local variables */
  PduLengthType PduLength;

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TRIGGER_TRANSMIT_SID, XCP_E_NOT_INITIALIZED, E_NOT_OK);
  /* If XcpRxPduPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((PduInfoPtr == NULL_PTR), XCP_TRIGGER_TRANSMIT_SID, XCP_E_NULL_POINTER, E_NOT_OK);
  /* If Invalid TxPduId, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((TxPduId >= XCP_FR_NUMBER_OF_TX_PDUS), XCP_TRIGGER_TRANSMIT_SID, XCP_E_INVALID_PDUID, E_NOT_OK);
  /* TriggerTransmit called without previous Transmit, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((XCP_IS_PDU_BLOCKED(TxPduId) == FALSE), XCP_TRIGGER_TRANSMIT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL, E_NOT_OK);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Get PduLenth */
  PduLength = Xcp_FrCfgCleared.TxPdu[TxPduId].SduLength;
  /* Copy whole PduBuffer to FrIf */
  /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
  Xcp_MemCopy(PduInfoPtr->SduDataPtr, Xcp_FrCfgCleared.TxPdu[TxPduId].SduDataPtr, PduLength);
  /* Copy length of the data */
  PduInfoPtr->SduLength = PduLength;
  /* Return */
  return(E_OK);
}


/**
****************************************************************************************************
Initialization of the transport layer internal variables
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\param[in]  XcpInitStatus         was Xcp already initialized before or not
\return     -
***************************************************************************************************/
void Xcp_FrInit(uint8 XcpTransportLayerId, uint8 XcpInitStatus)
{
  /* Local variables */
  uint8  XcpFrTransportLayerId;
  uint32 TLId;
  uint32 PduId;
  uint32 Offset;

  XCP_PARAM_UNUSED(XcpInitStatus);

  /* Shift the Transport Layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpFrTransportLayerId = XcpTransportLayerId - XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET;

  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR((XcpFrTransportLayerId >= XCP_FR_NUMBER_OF_TRANSPORT_LAYERS), XCP_INITIALIZE_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID);

  /*--------------------------------------------------------------------------------------------------
    No-init RAM - Initialization only for first time
  --------------------------------------------------------------------------------------------------*/
  /* At this time no initialization for No-Init RAM needed
  if (XcpInitStatus == XCP_UNINIT)
  {
  } */

  /*--------------------------------------------------------------------------------------------------
    Cleared RAM - Initialization always necessary
  --------------------------------------------------------------------------------------------------*/

  /* ----- The part below must be executed for all Transport layers together to preserve proper offsets ----- */

#if (XCP_FR_RECEIVE_IN_MAINFUNCTION == STD_ON)
  /* Initialize all reception Pdus */
  Offset = 0;
  for (TLId = 0 ; TLId < XCP_FR_NUMBER_OF_TRANSPORT_LAYERS ; TLId++)
  {
    for (PduId = Xcp_FrCfgConst.TlCfg[TLId].RxPduCfgOffset_u8 ; PduId < (Xcp_FrCfgConst.TlCfg[TLId].RxPduCfgOffset_u8 + Xcp_FrCfgConst.TlCfg[TLId].RxPduCfgCount_u8) ; PduId++)
    {
      /* Is FrInit called for this transport layer? */
      if (XcpFrTransportLayerId == TLId)
      {
        /* Set pointer of the PduData to proper position in PduBuffer */
        Xcp_FrCfgCleared.RxPdu[PduId].SduDataPtr = &(Xcp_FrCfgCleared.RxPduBuffer_au8[Offset]);
        /* Fill the buffer with Nax */
        Xcp_FrCfgCleared.RxPdu[PduId].SduDataPtr[0] = Xcp_FrCfgConst.TlCfg[TLId].Nax_u8;
        /* Set the position just after Nax */
        Xcp_FrCfgCleared.RxPdu[PduId].SduLength = 1u;
      }
      /* Shift offset in the PduBuffer */
      Offset += XCP_4BYTE_ALIGN(Xcp_FrCfgConst.RxPduCfg[PduId].PduSize_u8);
    }
  }
#endif
  /* Initialize all transmission Pdus */
  Offset = 0;
  for (TLId = 0 ; TLId < XCP_FR_NUMBER_OF_TRANSPORT_LAYERS ; TLId++)
  {
    for (PduId = Xcp_FrCfgConst.TlCfg[TLId].TxPduCfgOffset_u8 ; PduId < (Xcp_FrCfgConst.TlCfg[TLId].TxPduCfgOffset_u8 + Xcp_FrCfgConst.TlCfg[TLId].TxPduCfgCount_u8) ; PduId++)
    {
      /* Is FrInit called for this transport layer? */
      if (XcpFrTransportLayerId == TLId)
      {
        /* Set pointer of the PduData to proper position in PduBuffer */
        Xcp_FrCfgCleared.TxPdu[PduId].SduDataPtr = &(Xcp_FrCfgCleared.TxPduBuffer_au8[Offset]);
        /* Fill the buffer with Nax */
        Xcp_FrCfgCleared.TxPdu[PduId].SduDataPtr[0] = Xcp_FrCfgConst.TlCfg[TLId].Nax_u8;
        /* Set the position just after Nax */
        Xcp_FrCfgCleared.TxPdu[PduId].SduLength = 1u;
      }
      /* Shift offset in the PduBuffer */
      Offset += XCP_4BYTE_ALIGN(Xcp_FrCfgConst.TxPduCfg[PduId].PduSize_u8);
    }
  }
}


/**
****************************************************************************************************
Connect command related handling for the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
void Xcp_FrConnect(uint8 XcpTransportLayerId)
{
  /* Local variables */
  uint32 PduId;
  uint32 XcpFrTransportLayerId;

  /* Shift the Transport Layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpFrTransportLayerId = XcpTransportLayerId - XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET;

  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR((XcpFrTransportLayerId >= XCP_FR_NUMBER_OF_TRANSPORT_LAYERS), XCP_CONNECT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID);

  /* Check if transport layer already not connected */
  if (Xcp_FrCfgNoInit.Connected_ab[XcpFrTransportLayerId] == FALSE)
  {
    /* Lock interrupts */
    SchM_Enter_Xcp_FrTransmit();
    /* Configure all Transmit Pdus */
    for (PduId = Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8 ; PduId < (Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8 + Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgCount_u8) ; PduId++)
    {
      /* Set initial allowed packet type */
      Xcp_FrCfgNoInit.TxPduType_a[PduId] = Xcp_FrCfgConst.TxPduCfg[PduId].AllowedType;
#if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON)
      /* Deactivate Pdu for EV_SERV */
      Xcp_FrCfgNoInit.TxPduEvServActivated_ab[PduId] = FALSE;
#endif
    }
    /* Set flag that connected */
    Xcp_FrCfgNoInit.Connected_ab[XcpFrTransportLayerId] = TRUE;
    /* Increase counter of connected transport layers */
    Xcp_FrCfgNoInit.ConnectedTLCtr_u8++;
    /* Unlock interrupts */
    SchM_Exit_Xcp_FrTransmit();
  }
}


/**
****************************************************************************************************
Disconnects the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     result of disconnect request
***************************************************************************************************/
Std_ReturnType Xcp_FrDisconnect(uint8 XcpTransportLayerId)
{
  /* Local variables */
  Std_ReturnType RetVal;
  uint32 XcpFrTransportLayerId;

  /* Initial values */
  RetVal = E_OK;

  /* Shift the Transport Layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpFrTransportLayerId = XcpTransportLayerId - XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET;

  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpFrTransportLayerId >= XCP_FR_NUMBER_OF_TRANSPORT_LAYERS), XCP_DISCONNECT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, E_NOT_OK);

  /* Check if transport layer already connected */
  if (Xcp_FrCfgNoInit.Connected_ab[XcpFrTransportLayerId] != FALSE)
  {
    /* All Pdus sent? */
    if (Xcp_FrCfgCleared.TxPacketPtr[XcpFrTransportLayerId].SduLength == 0u)
    {
      /* Lock interrupts */
      SchM_Enter_Xcp_FrTransmit();
      /* Set flag that disconnected */
      Xcp_FrCfgNoInit.Connected_ab[XcpFrTransportLayerId] = FALSE;
      /* Decrease counter of connected transport layers */
      Xcp_FrCfgNoInit.ConnectedTLCtr_u8--;
      /* Unlock interrupts */
      SchM_Exit_Xcp_FrTransmit();
    }
    /* Pdus must be transmitted, not ready to disconnect */
    else
    {
      RetVal = E_NOT_OK;
    }
  }
  else
  {
    /* Unexpected case */
    XCP_DET_REPORT_ERROR_NO_RET(XCP_DISCONNECT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL);
  }
  return RetVal;
}


/**
****************************************************************************************************
This function handles specific Transport Layer Commands
\param[in]  XcpCmdPacketPtr       Pointer to XcpPacket with received command
\param[out] XcpResPacketPtr       Pointer to XcpPacket where the response shall be stored
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
void Xcp_FrTransportLayerCmd(const PduInfoType* XcpCmdPacketPtr, PduInfoType* XcpResPacketPtr, uint8 XcpTransportLayerId)
{
#if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON)
  uint8 XcpFrTransportLayerId;
  Xcp_ErrorCode Error;

  /* Shift the Transport Layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpFrTransportLayerId = XcpTransportLayerId-XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET;

  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR((XcpFrTransportLayerId >= XCP_FR_NUMBER_OF_TRANSPORT_LAYERS), XCP_TRANSPORT_LAYER_CMD_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID);

  /* Default return value if not valid command length */
  Error = XCP_ERR_CMD_SYNTAX;

  /* Check TransportLayer Command code */
  switch(XcpCmdPacketPtr->SduDataPtr[1])
  {
    /* Assign/deassign FlexRay LPDU identifiers to buffers */
    case XCP_FR_TLCMD_FLX_ASSIGN:
    {
      /* Check command length */
      if (XcpCmdPacketPtr->SduLength >= XCP_CMD_FR_ASSIGN_LENGTH)
      {
        Error = Xcp_FrTransportLayerCmd_Assign(XcpCmdPacketPtr, XcpFrTransportLayerId);
      }
    }
    break;

    /* Activate communication of a FlexRay buffer */
    case XCP_FR_TLCMD_FLX_ACTIVATE:
    {
      /* Check command length */
      if (XcpCmdPacketPtr->SduLength >= XCP_CMD_FR_ACTIVATE_LENGTH)
      {
        Error = Xcp_FrTransportLayerCmd_Activate(XcpCmdPacketPtr, XcpFrTransportLayerId);
      }
    }
    break;

    /* Deactivate communication of a FlexRay buffer */
    case XCP_FR_TLCMD_FLX_DEACTIVATE:
    {
      /* Check command length */
      if (XcpCmdPacketPtr->SduLength >= XCP_CMD_FR_DEACTIVATE_LENGTH)
      {
        Error = Xcp_FrTransportLayerCmd_Deactivate(XcpCmdPacketPtr, XcpFrTransportLayerId);
      }
    }
    break;

    default:
    {
      /* If GET/SET_DAQ_BUF shall be implemented, use following function prototypes.
      Error = Xcp_FrTransportLayerCmd_GetDaqBuf(XcpCmdPacketPtr, XcpResPacketPtr, XcpFrTransportLayerId);
      Error = Xcp_FrTransportLayerCmd_SetDaqBuf(XcpCmdPacketPtr, XcpFrTransportLayerId);
      */
# if ((XCP_ASAM_MAJOR_VERSION <= 1u) && (XCP_ASAM_MINOR_VERSION <= 2u))
     /* Unknown command */
     Error = XCP_ERR_CMD_UNKNOWN;
# else
     /* Unknown subcommand for Xcp 1.3 version and beyond */
     Error = XCP_ERR_SUBCMD_UNKNOWN;
# endif

    }
    break;
  }

  /* Check if no error */
  if (Error == XCP_NO_ERROR)
  {
    /* Positive response */
    XcpResPacketPtr->SduDataPtr[0] = 0xFFu;
    XcpResPacketPtr->SduLength = 1;
  }
  else
  {
    /* Negative response */
    XcpResPacketPtr->SduDataPtr[0] = 0xFEu;
    XcpResPacketPtr->SduDataPtr[1] = (uint8) Error;
    XcpResPacketPtr->SduLength = 2;
  }
#else
  XCP_PARAM_UNUSED(XcpCmdPacketPtr);
  XCP_PARAM_UNUSED(XcpResPacketPtr);
  XCP_PARAM_UNUSED(XcpTransportLayerId);
#endif
}


/**
****************************************************************************************************
This function is called by protocol layer to find a XcpTxPduId for a given EventChannel
\param[in]  XcpPacketId             Type of the packet (1st byte of packets to transmit)
\param[in]  XcpEventChannelNumber   Event channel number (relevant for CAN only)
\param[in]  XcpTransportLayerId     Id if Transport Layer given by Protocol layer
\return     XcpTxPduId
***************************************************************************************************/
Xcp_PduIdType Xcp_FrGetTxPduId(uint8 XcpPacketId, uint16 XcpEventChannelNumber, uint8 XcpTransportLayerId)
{
  XCP_PARAM_UNUSED(XcpEventChannelNumber);
  XCP_PARAM_UNUSED(XcpTransportLayerId);
  XCP_PARAM_UNUSED(XcpPacketId);

  return XCP_PDU_ID_UNKNOWN;
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
Xcp_ErrorCode Xcp_FrResumeModeData(Xcp_AdrPtr DaqRamPtr, Xcp_AdrPtrConst XcpDaqRamEndPtr, uint8 XcpTransportLayerId)
{
  uint8 XcpFrTransportLayerId;
  Xcp_ErrorCode Error;

  /* Shift the Transport Layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpFrTransportLayerId = XcpTransportLayerId - XCP_FR_TRANSPORT_LAYER_INDEX_OFFSET;

  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpFrTransportLayerId >= XCP_FR_NUMBER_OF_TRANSPORT_LAYERS), XCP_CMD_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, XCP_ERR_GENERIC);

  Error = XCP_NO_ERROR;
  /* If the XcpDaqRamEndPtr is NULL_PTR means that the function is currently used to set back the saved NvM data for the Transport Layer */
  if (XcpDaqRamEndPtr != NULL_PTR)
  {
    /* If enough space to Fr transport layer configuration to NvM then copy the data at the given place otherwise return ERR_MEMORY_OVERFLOW */
    if ((DaqRamPtr + sizeof(Xcp_FrCfgNoInit.TxPduType_a) + sizeof(Xcp_FrCfgNoInit.TxPduEvServActivated_ab)) <= XcpDaqRamEndPtr)
    {
      /* Copy the configured TxPduType */
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(DaqRamPtr, &Xcp_FrCfgNoInit.TxPduType_a, sizeof(Xcp_FrCfgNoInit.TxPduType_a));
#   if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON)
      /* Copy the TxPduEvServActivated configuration */
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(DaqRamPtr + sizeof(Xcp_FrCfgNoInit.TxPduType_a), &Xcp_FrCfgNoInit.TxPduEvServActivated_ab, sizeof(Xcp_FrCfgNoInit.TxPduEvServActivated_ab));
#   endif
    }
    else
    {
      Error = XCP_ERR_MEMORY_OVERFLOW;
    }
  }
  else
  {
    /* Set connected status for Transport Layer */
    Xcp_FrCfgNoInit.Connected_ab[XcpFrTransportLayerId] = TRUE;
    /* Copy the configured TxPduType */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(&Xcp_FrCfgNoInit.TxPduType_a, DaqRamPtr, sizeof(Xcp_FrCfgNoInit.TxPduType_a));
# if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON)
    /* Copy the TxPduEvServActivated configuration */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(&Xcp_FrCfgNoInit.TxPduEvServActivated_ab, DaqRamPtr + sizeof(Xcp_FrCfgNoInit.TxPduType_a), sizeof(Xcp_FrCfgNoInit.TxPduEvServActivated_ab));
# endif
    Xcp_FrCfgNoInit.ConnectedTLCtr_u8++;
  }

  return Error;
}
#endif

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Local functions
***************************************************************************************************/

#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Convert PacketId to PacketType
\param[in]  XcpPacketId   PacketId of XcpPacket (first byte)
\return     PacketType of given PacketId
***************************************************************************************************/
static Xcp_PacketType_t Xcp_FrPacketId2PacketType(uint8 XcpPacketId)
{
  /* Local variables */
  Xcp_PacketType_t RetVal;

  /* Resolve Packet Type from Packet Id */
  if (XcpPacketId <= XCP_PACKET_ID_DAQ_MAX)
  {
    RetVal = XCP_PACKET_TYPE_DAQ;
  }
  else
  {
    RetVal = XcpFrPacketId2PacketType[0xFF-XcpPacketId];
  }
  return RetVal;
}


/**
****************************************************************************************************
Find free Tx Pdu for given Packet Type
\param[in]  XcpPacketType           Packet Type
\param[in]  XcpFrTransportLayerId   Local FlexRay Transport Layer Id
\return     PduId which can be used for transmission, XCP_PDU_ID_UNKNOWN if free Pdu is not found
***************************************************************************************************/
static Xcp_PduIdType Xcp_FrGetFreeTxPduId(Xcp_PacketType_t XcpPacketType, uint8 XcpFrTransportLayerId)
{
  /* Local variables */
  Xcp_PduIdType PduId;

#if (XCP_FR_ONLY_ONE_TX_PDU == STD_ON)
  XCP_PARAM_UNUSED(XcpPacketType);

  /* Initial value */
  PduId = XCP_PDU_ID_UNKNOWN;

  /* Check if is not reserved for Tx */
  if (XCP_IS_PDU_BLOCKED(Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8) == FALSE)
  {
    PduId = Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8;
  }
#else
  const uint8 PduFirst = Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8;
  const uint8 PduLast  = Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8 + Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgCount_u8;
  uint8 i;

  /* Initial value */
  PduId = XCP_PDU_ID_UNKNOWN;

  /* Search for Pdu with requested type */
  for (i = PduFirst ; i < PduLast ; i++)
  {
    /* Allowed type? */
    if ( ((Xcp_FrCfgNoInit.TxPduType_a[i] & XcpPacketType) == XcpPacketType)
    /* Is Pdu available? */
      && (XCP_IS_PDU_BLOCKED(i) == FALSE) )
    {
  #if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON)
      /* EV_SERV needs additional check */
      if (XcpPacketType == XCP_PACKET_TYPE_EV_SERV)
      {
        /* Check if EV_SERV allowed for transmission */
        if (Xcp_FrCfgNoInit.TxPduEvServActivated_ab[i] != FALSE)
        {
          PduId = i;
          break;
        }
      }
      /* RES_ERR and DAQ are always allowed */
      else
  #endif
      {
        PduId = i;
        /* MR12 RULE 15.4 VIOLATION: more than one break is needed to avoid additional local breakloop variable  */
        break;
      }
    }
  }
#endif /* #if (XCP_FR_ONLY_ONE_TX_PDU == STD_ON) */
  return(PduId);
}


/**
****************************************************************************************************
Function is called if transmission failed. Finds correct return value for Transmit function.
\param[in]  XcpPacketType           Type of XcpPacket which transmission failed
\param[in]  XcpFrTransportLayerId   Local FlexRay Transport Layer Id
\return     status for transmit request
***************************************************************************************************/
static Std_ReturnType Xcp_FrNoFreeTxPduId(Xcp_PacketType_t XcpPacketType, uint8 XcpFrTransportLayerId)
{
  /* Local variables */
  Std_ReturnType RetVal;

  XCP_PARAM_UNUSED(XcpFrTransportLayerId);

#if (XCP_FR_TRANSPORT_LAYER_CMD == STD_OFF)
  XCP_PARAM_UNUSED(XcpPacketType);
#else
  if (XcpPacketType == XCP_PACKET_TYPE_EV_SERV)
  {
    /* Do not inform protocol layer, just don't send the packet */
    RetVal = E_OK;
    XCP_DEBUG_CTR_INC(Xcp_FrCfgCleared.Xcp_Debug_FrTxEvServPduIgnoredCtr[XcpFrTransportLayerId]);
  }
  else
#endif
  {
    /* Error */
    RetVal = E_NOT_OK;
    XCP_DEBUG_CTR_INC(Xcp_FrCfgCleared.Xcp_Debug_FrTxNoFreePduCtr[XcpFrTransportLayerId]);
  }
  return RetVal;
}


/**
****************************************************************************************************
Generate FlexRay frame header
\param[in]  XcpTxPduId              Id of Pdu
\param[in]  XcpFrTransportLayerId   Local FlexRay Transport Layer Id
\return     Position after the header - 1
***************************************************************************************************/
static PduLengthType Xcp_FrInsertHeader(Xcp_PduIdType XcpTxPduId, uint8 XcpFrTransportLayerId)
{
#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
  /* In case of frame concatenation, header shall be added if Pdu is empty */
  if (Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduLength == 1u)
#endif
  {
#if (XCP_FR_SEQUENCE_CORRECTION == STD_OFF)
    XCP_PARAM_UNUSED(XcpFrTransportLayerId);
#else
    /* Set value of the counter (always in second byte)*/
    Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduDataPtr[1] = Xcp_FrCfgNoInit.TxCounter_au8[XcpFrTransportLayerId];
    /* Update counter */
    Xcp_FrCfgNoInit.TxCounter_au8[XcpFrTransportLayerId]++;
#endif
    /* Set position where length (LEN) will be stored (1 byte before XcpPacket starts) */
    Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduLength = XCP_FR_HEADER_SIZE - 1u;
  }
  return (Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduLength);
}


#if (XCP_FR_FRAME_CONCATENATION == STD_ON)
/**
****************************************************************************************************
Finish FlexRay frame
\param[in]  XcpTxPduId  Id of Pdu
\return     -
***************************************************************************************************/
static void Xcp_FrFinishFrame(Xcp_PduIdType XcpTxPduId)
{
  /* Local variables */
  PduLengthType PduLengthLocal;

  /* Get PduLength */
  PduLengthLocal = Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduLength;

  /* Can next packet length (LEN) be inserted? */
  if (PduLengthLocal < Xcp_FrCfgConst.TxPduCfg[XcpTxPduId].PduSize_u8)
  {
    /* Set next packet length (LEN) to 0 */
    Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduDataPtr[PduLengthLocal] = 0;
    /* LEN shall also be transmitted --> Add 1 to PduLength */
    Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduLength = PduLengthLocal + 1u;
  }
  else
  {
    /* Reduce to maximum Pdu length */
    Xcp_FrCfgCleared.TxPdu[XcpTxPduId].SduLength = Xcp_FrCfgConst.TxPduCfg[XcpTxPduId].PduSize_u8;
  }
}
#endif

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

#if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON)
/**
****************************************************************************************************
This function handles specific Transport Layer Command: ASSIGN FlexRay LPDU identifiers to buffers
\param[in]  XcpCmdPacketPtr         Pointer to XcpPacket with received command
\param[in]  XcpFrTransportLayerId   Local FlexRay Transport Layer Id
\return     Response error code or XCP_NO_ERROR
***************************************************************************************************/
static Xcp_ErrorCode Xcp_FrTransportLayerCmd_Assign(const PduInfoType* XcpCmdPacketPtr, uint8 XcpFrTransportLayerId)
{
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdFrAssign_t* const CmdPtr = (const Xcp_CmdFrAssign_t*) (void*) XcpCmdPacketPtr->SduDataPtr;
  Xcp_ErrorCode Error;
  Xcp_PduIdType PduId;

  XCP_PARAM_UNUSED(XcpFrTransportLayerId);

  /* Initial value */
  Error = XCP_ERR_OUT_OF_RANGE;

  /* Check if valid FlexRay buffer number - Reception PDU */
  if (CmdPtr->FlxBuf_u8 < XCP_FR_NUMBER_OF_RX_PDUS)
  {
    /* Get PduId */
    PduId = CmdPtr->FlxBuf_u8;

    /* Check if new buffer type is allowed (Reconfiguration allowed & given Type allowed) */
    if (   ((Xcp_FrCfgConst.RxPduCfg[PduId].AllowedType & XCP_PACKET_TYPE_VARIABLE) == XCP_PACKET_TYPE_VARIABLE)
        && ((Xcp_FrCfgConst.RxPduCfg[PduId].AllowedType & CmdPtr->PacketType_u8)    == CmdPtr->PacketType_u8)   )
    {
      /* OK */
      Error = XCP_NO_ERROR;
    }
  }
  /* Check if valid FlexRay buffer number - Transmission PDU */
  /* else if not possible because of HIS metric LEVEL compliance */
  if ((CmdPtr->FlxBuf_u8 >= XCP_FR_NUMBER_OF_RX_PDUS) && (CmdPtr->FlxBuf_u8 < (XCP_FR_NUMBER_OF_RX_PDUS + XCP_FR_NUMBER_OF_TX_PDUS)))
  {
    PduId = CmdPtr->FlxBuf_u8 - XCP_FR_NUMBER_OF_RX_PDUS;

    /* Check if new buffer type is allowed (Reconfiguration allowed & given Type allowed) */
    if (   ((Xcp_FrCfgConst.TxPduCfg[PduId].AllowedType & XCP_PACKET_TYPE_VARIABLE) == XCP_PACKET_TYPE_VARIABLE)
        && ((Xcp_FrCfgConst.TxPduCfg[PduId].AllowedType & CmdPtr->PacketType_u8)    == CmdPtr->PacketType_u8)   )
    {
      /* Update buffer type */
      Xcp_FrCfgNoInit.TxPduType_a[PduId] = (Xcp_PacketType_t)CmdPtr->PacketType_u8;
      /* Deactivate Pdu for EV_SERV */
      Xcp_FrCfgNoInit.TxPduEvServActivated_ab[PduId] = FALSE;
      /* OK */
      Error = XCP_NO_ERROR;
    }
  }
  /* Check if reset for all VARIABLE FlexRay buffer shall be done */
  /* else if not possible because of HIS metric LEVEL compliance */
  if ((CmdPtr->FlxBuf_u8 == 0xFFu) && (CmdPtr->PacketType_u8 == 0x00u))
  {
    /* Lock interrupts */
    SchM_Enter_Xcp_FrTransmit();
    /* Reset all VARIABLE buffers to their initial states */
    for (PduId = Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8; PduId < (Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgOffset_u8 + Xcp_FrCfgConst.TlCfg[XcpFrTransportLayerId].TxPduCfgCount_u8); PduId++)
    {
      /* Is it VARIABLE buffer? */
      if ((Xcp_FrCfgConst.TxPduCfg[PduId].AllowedType & XCP_PACKET_TYPE_VARIABLE) == XCP_PACKET_TYPE_VARIABLE)
      {
        /* Set type initial state */
        Xcp_FrCfgNoInit.TxPduType_a[PduId] = Xcp_FrCfgConst.TxPduCfg[PduId].AllowedType;
        /* Deactivate Pdu for EV_SERV */
        Xcp_FrCfgNoInit.TxPduEvServActivated_ab[PduId] = FALSE;
      }
    }
    /* Unlock interrupts */
    SchM_Exit_Xcp_FrTransmit();
    /* OK */
    Error = XCP_NO_ERROR;
  }
  else
  {
    /* Error = XCP_ERR_OUT_OF_RANGE already set */
  }
  /* Return Error Code */
  return(Error);
}


/**
****************************************************************************************************
This function handles specific Transport Layer Command: ACTIVATE EV_SERV Pdus of a FlexRay buffer
\param[in]  XcpCmdPacketPtr         Pointer to XcpPacket with received command
\param[in]  XcpFrTransportLayerId   Local FlexRay Transport Layer Id
\return     Response error code or XCP_NO_ERROR
***************************************************************************************************/
static Xcp_ErrorCode Xcp_FrTransportLayerCmd_Activate(const PduInfoType* XcpCmdPacketPtr, uint8 XcpFrTransportLayerId)
{
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdFrActivate_t* const CmdPtr = (const Xcp_CmdFrActivate_t*) (void*) XcpCmdPacketPtr->SduDataPtr;
  Xcp_ErrorCode Error;
  Xcp_PduIdType PduId;

  XCP_PARAM_UNUSED(XcpFrTransportLayerId);

  /* Initial value */
  Error = XCP_ERR_OUT_OF_RANGE;

  /* Check if valid FlexRay buffer number - Transmission PDU */
  if ( (CmdPtr->FlxBuf_u8 >= XCP_FR_NUMBER_OF_RX_PDUS)
    && (CmdPtr->FlxBuf_u8 < (XCP_FR_NUMBER_OF_RX_PDUS + XCP_FR_NUMBER_OF_TX_PDUS))
     )
  {
    /* Shift the PduId to match in the TxPdus array */
    PduId = CmdPtr->FlxBuf_u8 - XCP_FR_NUMBER_OF_RX_PDUS;
    /* Check if EV_SERV - only for that type this command is valid */
    if (   ((Xcp_FrCfgConst.TxPduCfg[PduId].AllowedType & XCP_PACKET_TYPE_VARIABLE) == XCP_PACKET_TYPE_VARIABLE)
        && ((Xcp_FrCfgNoInit.TxPduType_a[PduId] & XCP_PACKET_TYPE_EV_SERV) == XCP_PACKET_TYPE_EV_SERV))
    {
      /* Activate Pdu for EV_SERV */
      Xcp_FrCfgNoInit.TxPduEvServActivated_ab[PduId] = TRUE;
      /* OK */
      Error = XCP_NO_ERROR;
    }
  }
  /* Return Error Code */
  return(Error);
}


/**
****************************************************************************************************
This function handles specific Transport Layer Command: DEACTIVATE EV_SERV Pdus of a FlexRay buffer
\param[in]  XcpCmdPacketPtr         Pointer to XcpPacket with received command
\param[in]  XcpFrTransportLayerId   Local FlexRay Transport Layer Id
\return     Response error code or XCP_NO_ERROR
***************************************************************************************************/
static Xcp_ErrorCode Xcp_FrTransportLayerCmd_Deactivate(const PduInfoType* XcpCmdPacketPtr, uint8 XcpFrTransportLayerId)
{
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdFrDeactivate_t* const CmdPtr = (const Xcp_CmdFrDeactivate_t*) (void*) XcpCmdPacketPtr->SduDataPtr;
  Xcp_ErrorCode Error;
  Xcp_PduIdType PduId;

  XCP_PARAM_UNUSED(XcpFrTransportLayerId);

  /* Initial value */
  Error = XCP_ERR_OUT_OF_RANGE;

  /* Check if valid FlexRay buffer number - Transmission PDU */
  if ( (CmdPtr->FlxBuf_u8 >= XCP_FR_NUMBER_OF_RX_PDUS)
    && (CmdPtr->FlxBuf_u8 < (XCP_FR_NUMBER_OF_RX_PDUS + XCP_FR_NUMBER_OF_TX_PDUS))
     )
  {
    /* Shift the PduId to match in the TxPdus array */
    PduId = CmdPtr->FlxBuf_u8 - XCP_FR_NUMBER_OF_RX_PDUS;
    /* Check if EV_SERV - only for that type this command is valid */
    if (   ((Xcp_FrCfgConst.TxPduCfg[PduId].AllowedType & XCP_PACKET_TYPE_VARIABLE) == XCP_PACKET_TYPE_VARIABLE)
        && ((Xcp_FrCfgNoInit.TxPduType_a[PduId] & XCP_PACKET_TYPE_EV_SERV) == XCP_PACKET_TYPE_EV_SERV))
    {
      /* Deactivate Pdu for EV_SERV */
      Xcp_FrCfgNoInit.TxPduEvServActivated_ab[PduId] = FALSE;
      /* OK */
      Error = XCP_NO_ERROR;
    }
  }
  /* Return Error Code */
  return(Error);
}

#endif /* #if (XCP_FR_TRANSPORT_LAYER_CMD == STD_ON) */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


#endif /* #if (XCP_ON_FLEXRAY_ENABLED == STD_ON) */
/* HIS METRIC COMF VIOLATION IN XcpOnFr.c: If Xcp on Flexray is disabled, this file is empty. */


