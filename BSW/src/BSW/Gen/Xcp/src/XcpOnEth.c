

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"

#if(XCP_ON_ETHERNET_ENABLED == STD_ON)
#include "SoAd.h"
#include "XcpOnEth_Cfg.h"
#include "XcpOnEth_Cbk.h"

/* Check versions */
#if (!defined(SOAD_AR_RELEASE_MAJOR_VERSION) || (SOAD_AR_RELEASE_MAJOR_VERSION != XCP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif


/***************************************************************************************************
* Type definitions
***************************************************************************************************/
/** XCP on Ethernet socket connection info */
/* MR12 RULE 5.6 VIOLATION: Type declaration is needed only for Xcp on ETH. Declaration in any api will cause compiler errors for projects that use only Xcp on CAN. */
typedef struct
{
  SoAd_SoConIdType        SoConId;
  TcpIp_SockAddrInet6Type RemoteIpAddr; /* the Ipv6 type was used because it can accomodate both IPv4 and IPv6 addresses */
} Xcp_SoConInfo_t;


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
/** Structure with data for Ethernet Transport Layer channels */
static Xcp_TransportLayerEthData_t Xcp_TransportLayerEthData[XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS];
#if (XCP_ETH_ON_TCP_ENABLED == STD_ON)
/** TCP received data for each Transport Layer. */
static Xcp_TcpEthRxData_t Xcp_TcpEthRxData[XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS];
#endif
#define XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
/** Eth XCP packet counter has to stay in protected RAM */
static uint16          Xcp_EthCtr_u16[XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS];
static Xcp_SoConInfo_t Xcp_SoConData[XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS];
#define XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"
static Std_ReturnType Xcp_EthTransmitInMainfunction(const PduInfoType* XcpPacketPtr, uint8 XcpEthTransportLayerId);
/* Function Xcp_EthResetTxBuffer is used for resetting the buffer with XCP message. */
static void Xcp_EthResetTxBuffer(uint8 XcpEthTransportLayerId);
/* Function Xcp_EthCopyPacketToBuffer will copy the XCP packet to the transmit pointer and attach the XCP header.
  The function is used to avoid same code in multiple places. */
static void Xcp_EthCopyPacketToBuffer(const PduInfoType* XcpPacketPtr, uint8 XcpEthTransportLayerId);
#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
/* Function Xcp_EthGetPacketLength for calculating XCP packet length from XCP header. */
static PduLengthType Xcp_EthGetPacketLength(const uint8* XcpLengthPtr);
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
/* HIS METRIC LEVEL VIOLATION IN Xcp_SoAdIfRxIndication: Function contains several necessary if statements. HIS metric compliance would decrease readability and maintainability. */
void Xcp_SoAdIfRxIndication(PduIdType XcpRxPduId, const PduInfoType* XcpRxPduPtr)
{
  PduInfoType XcpPacketPtr;
  PduLengthType ReadPos;
  PduLengthType TLPduLength;
  uint32 XcpBuffer4Alignment[(XCP_ETH_RX_PDU_LEN_MAX + 3u)/4u];
  uint8 TransportLayerId;
#if (XCP_ETH_ON_TCP_ENABLED == STD_ON)
  uint8 XcpEthTransportLayerId;
  PduLengthType XcpPacketLength;
#endif

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_RX_INDICATION_SID, XCP_E_NOT_INITIALIZED);
  /* If XcpRxPduPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduPtr == NULL_PTR), XCP_RX_INDICATION_SID, XCP_E_NULL_POINTER);
  /* If Invalid RxPduId, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpRxPduId >= XCP_ETH_NUMBER_OF_RX_PDU), XCP_RX_INDICATION_SID, XCP_E_INVALID_PDUID);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Calculate Transport Layer Id and Eth Transport Layer Id. */
  TransportLayerId = Xcp_TransportLayerConfigEth.RxPduId2TransportLayerId[XcpRxPduId];
  /* Read position inside the received packet. */
  ReadPos = 0;
  /* To avoid writing over the RxBuffer length the length of the RxPdu will be limited to the Transport Layer Rx PduLength. */
  TLPduLength = XCP_MIN(XcpRxPduPtr->SduLength, XCP_ETH_RX_PDU_LEN_MAX);

#if (XCP_ETH_ON_TCP_ENABLED == STD_ON)
  XcpEthTransportLayerId = (uint8)XcpRxPduId;

  if (Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].ProtocolType == XCP_ETH_PROTOCOL_TCP)
  {
    /* Previous message contained only the first byte from XCP packet length. */
    if (Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength == 1u)
    {
      /* Calculate the length of the XCP packet. */
      Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength = Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength + (PduLengthType)((PduLengthType)XcpRxPduPtr->SduDataPtr[0] << 8u) + XCP_ETH_PACKET_HEADER_LEN;
    }

    /* Previous RxIndication had a segmented data and in the new received segment should be the rest of the XCP packet. */
    XcpPacketLength = Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength - Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength;

    /* Calculated XCP packet length to be copied is bigger than 0 and not bigger than the buffer length. */
    if ((XcpPacketLength > 0u) && (Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength <= (XCP_ETH_TCP_MAX_CTO_DTO + XCP_ETH_PACKET_HEADER_LEN)))
    {
      if (XcpPacketLength <= TLPduLength)
      {
        /* This segment contains the complete rest of the XCP packet. Copy the received data in the Rx buffer from the current position. */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        Xcp_MemCopy(Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_RxBuffer_au32 + Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength, XcpRxPduPtr->SduDataPtr, XcpPacketLength);
        /* Set the length for the receive packet pointer to complete XCP packet length. */
        XcpPacketPtr.SduLength = Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength - XCP_ETH_PACKET_HEADER_LEN;
        /* Data pointer points to XCP packet data. */
        XcpPacketPtr.SduDataPtr = (uint8*)Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_RxBuffer_au32 + XCP_ETH_PACKET_HEADER_LEN;
        /* Resolve RxPduId to global TransportLayerId and call receive function from protocol layer */
        Xcp_Receive(&XcpPacketPtr, TransportLayerId);
        /* Reset both packet length and available length. */
        Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength = 0;
        Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength = 0;
        /* Calculate new read position in received frame. */
        ReadPos = XcpPacketLength;
      }
      else
      {
        /* The received segment doesn't contain the complete XCP packet. Copy the received data in the Rx buffer from the current position. */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        Xcp_MemCopy(Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_RxBuffer_au32 + Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength, XcpRxPduPtr->SduDataPtr, TLPduLength);
        /* Increment the current number of bytes received from the XCP packet. */
        Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength = Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength + TLPduLength;
        /* Calculate new read position in received frame. */
        ReadPos = TLPduLength;
      }
    }
    else
    {
      /* Reset both packet length and available length. */
      Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength = 0;
      Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength = 0;
      XCP_DET_REPORT_ERROR_NO_RET(XCP_RX_INDICATION_SID, XCP_E_DATA_PACKET_NOK);
    }
  }
#endif

#if (XCP_ETH_FRAME_CONCATENATION == STD_ON)
  while (
#else
  if (
#endif
       (Xcp_EthGetPacketLength(&XcpRxPduPtr->SduDataPtr[ReadPos]) > 0u)
       /* MR12 RULE 13.5 VIOLATION: The function after the && returns the calculated packet-length - no side effects; Redesign not possible as while loop instead of if possible - change would decrease maintainability and increase runtime */
    && ((ReadPos + XCP_ETH_PACKET_HEADER_LEN + Xcp_EthGetPacketLength(&XcpRxPduPtr->SduDataPtr[ReadPos])) <= TLPduLength)
  )
  {
    /* Calculate the length of the XCP packet which will be sent to Protocol Layer. */
    XcpPacketPtr.SduLength = Xcp_EthGetPacketLength(&XcpRxPduPtr->SduDataPtr[ReadPos]);
    /* XCP command pointer will point to the command start in the initial UDP frame. */
    XcpPacketPtr.SduDataPtr = XcpRxPduPtr->SduDataPtr + XCP_ETH_PACKET_HEADER_LEN + ReadPos;
    /* Align XCP packet to uint32 for protocol layer */
    /* MR12 RULE 11.4 VIOLATION: Cast from pointer to uint32 is OK as the addresses are 32bit long */
    if (((uint32)XcpPacketPtr.SduDataPtr & 0x3u) != 0u)
    {
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(XcpBuffer4Alignment, XcpPacketPtr.SduDataPtr, XcpPacketPtr.SduLength);
      XcpPacketPtr.SduDataPtr = (uint8*)XcpBuffer4Alignment;
    }
    /* Resolve RxPduId to global TransportLayerId and call receive function from protocol layer */
    Xcp_Receive(&XcpPacketPtr, TransportLayerId);
    /* Calculate new read position in received frame. */
    ReadPos = ReadPos + XCP_ETH_PACKET_HEADER_LEN + XcpPacketPtr.SduLength;
  }

#if (XCP_ETH_ON_TCP_ENABLED == STD_ON)
  /* TcpIp segment was received and XCP packet is split between two TCP segments. */
  if (Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].ProtocolType == XCP_ETH_PROTOCOL_TCP)
  {
    if ((ReadPos + 1u) == TLPduLength)
    {
      /* The complete XCP packet length was not received in XCP header. */
      Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength = 1;
      Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength = XcpRxPduPtr->SduDataPtr[ReadPos];
      /* Copy the first byte from XCP packet length. */
      Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_RxBuffer_au32[0] = XcpRxPduPtr->SduDataPtr[ReadPos];
    }
    else
    {
      /* Check that in the received segment there are still bytes left after processing and that resulted XCP packet length is not 0. */
      if ((Xcp_EthGetPacketLength(&XcpRxPduPtr->SduDataPtr[ReadPos]) > 0u) && ((ReadPos + 1u) < TLPduLength))
      {
        XcpPacketPtr.SduDataPtr = XcpRxPduPtr->SduDataPtr + ReadPos;
        /* XCP packet length extracted from received segment. */
        Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_PacketLength = Xcp_EthGetPacketLength(&XcpRxPduPtr->SduDataPtr[ReadPos]) + XCP_ETH_PACKET_HEADER_LEN;
        /* Number of bytes that can be copied from current segment for the XCP packet. */
        Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength = TLPduLength - ReadPos;
        /* Copy the available bytes to the RxBuffer. The length must not be bigger than the buffer length. */
        if (Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength <= (XCP_ETH_TCP_MAX_CTO_DTO + XCP_ETH_PACKET_HEADER_LEN))
        {
          /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
          Xcp_MemCopy(Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_RxBuffer_au32, XcpPacketPtr.SduDataPtr, Xcp_TcpEthRxData[XcpEthTransportLayerId].Xcp_CurrentLength);
        }
      }
    }
  }
#endif
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
Std_ReturnType Xcp_EthTransmit(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId, Xcp_PduIdType XcpTxPduId)
{
  /* Local variables */
  Std_ReturnType RetVal;
  uint8 XcpEthTransportLayerId;

  /* Shift the Transport Layer Id */
  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpEthTransportLayerId = XcpTransportLayerId - XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET;

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TRANSMIT_SID, XCP_E_NOT_INITIALIZED, E_NOT_OK);
  /* If XcpPacketPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr == NULL_PTR), XCP_TRANSMIT_SID, XCP_E_NULL_POINTER, E_NOT_OK);
  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET(((XcpEthTransportLayerId) >= XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, E_NOT_OK);
  /* Check if Packet length is zero, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr->SduLength == 0u), XCP_TRANSMIT_SID, XCP_E_DATA_PACKET_EMPTY, E_NOT_OK);
  /* If this function is called before transmission in EthMainFunctionTx, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduLength != 0u), XCP_TRANSMIT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL, E_NOT_OK);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Used only in XcpOnCan */
  XCP_PARAM_UNUSED(XcpTxPduId);

#if (XCP_ETH_TRANSMIT_IN_MAINFUNCTION == STD_ON)
  /* Store pointer to Xcp Packet and TransportLayer Id */
  Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduDataPtr = XcpPacketPtr->SduDataPtr;
  Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduLength  = XcpPacketPtr->SduLength;   /* Must be after SduDataPtr */
  RetVal = E_OK;
#else
  /* Lock interrupts */
  SchM_Enter_Xcp_EthMainFunc();
  /* Call internal Transmit function */
  RetVal = Xcp_EthTransmitInMainfunction(XcpPacketPtr, XcpEthTransportLayerId);
  /* Internal transmission successful? */
  if (RetVal == E_OK)
  {
    /* Store pointer to Xcp Packet and TransportLayer Id */
    Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduDataPtr = XcpPacketPtr->SduDataPtr;
    Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduLength  = XcpPacketPtr->SduLength;   /* Must be after SduDataPtr */
  }
  /* Unlock interrupts */
  SchM_Exit_Xcp_EthMainFunc();
#endif

  return RetVal;
}


/**
****************************************************************************************************
Local function for handling the frame transmission, called from Xcp_EthMainFunctionTx or Xcp_EthTransmit
\param[in]  XcpPacketPtr            Pointer to XcpPacket (with Length and data pointer)
\param[in]  XcpEthTransportLayerId  Local Ethernet Transport Layer Id
\return     status of the transmit request
***************************************************************************************************/
static Std_ReturnType Xcp_EthTransmitInMainfunction(const PduInfoType* XcpPacketPtr, uint8 XcpEthTransportLayerId)
{
  /* Local variables */
  Std_ReturnType RetVal;
#if (XCP_ETH_FRAME_CONCATENATION == STD_ON)
  PduLengthType XcpFrameLen;
#endif

  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TRANSMIT_SID, XCP_E_NOT_INITIALIZED, E_NOT_OK);
  /* If XcpPacketPtr is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr == NULL_PTR), XCP_TRANSMIT_SID, XCP_E_NULL_POINTER, E_NOT_OK);
  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpEthTransportLayerId >= XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, E_NOT_OK);
  /* Check if Packet length is zero, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET((XcpPacketPtr->SduLength == 0u), XCP_TRANSMIT_SID, XCP_E_DATA_PACKET_EMPTY, E_NOT_OK);
  /* Check if Packet length is the expected one, report to DET and exit the function  */
#if (XCP_ETH_TRANSMIT_IN_MAINFUNCTION == STD_ON)
  XCP_DET_REPORT_ERROR_RET((Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduLength == 0u), XCP_TRANSMIT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL, E_NOT_OK);
#else
  XCP_DET_REPORT_ERROR_RET((Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduLength != 0u), XCP_TRANSMIT_SID, XCP_E_UNEXPECTED_FUNCTION_CALL, E_NOT_OK);
#endif
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Initial value */
  RetVal = E_OK;

#if (XCP_ETH_FRAME_CONCATENATION == STD_OFF)
  /* Check if enough space in Pdu */
  if ((XCP_ETH_PACKET_HEADER_LEN + XcpPacketPtr->SduLength) <= Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].Xcp_PduLength)
  {
    /* Copy the packet to the buffer. */
    Xcp_EthCopyPacketToBuffer(XcpPacketPtr, XcpEthTransportLayerId);
    /* Transmit the packet */
    RetVal = SoAd_IfTransmit(Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].SoAdTxPduId, &Xcp_TransportLayerEthData[XcpEthTransportLayerId].Xcp_EthDataPacket);
    /* Reset TxBuffer */
    Xcp_EthResetTxBuffer(XcpEthTransportLayerId);
  }
  else
  {
    RetVal = E_NOT_OK;
  }

#else

  /* Get PduLength */
  XcpFrameLen = Xcp_TransportLayerEthData[XcpEthTransportLayerId].Xcp_EthDataPacket.SduLength;
  /* First check if is enough space in the ETH frame for the packet to be transmitted.
     In case there is space copy the received packet into the buffer.
     If not enough space in the buffer then first make a transmit and in case transmit is successful, reset the buffer and copy the received
     packet into the now empty buffer. */
  if ((XcpFrameLen + XCP_ETH_PACKET_HEADER_LEN + XcpPacketPtr->SduLength) <= Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].Xcp_PduLength)
  {
    /* Copy the packet to the buffer. */
    Xcp_EthCopyPacketToBuffer(XcpPacketPtr, XcpEthTransportLayerId);
  }
  else
  {
      /* No more space available in the frame: Transmit the packet, reset the buffer then copy the new received packet. */
    if (SoAd_IfTransmit(Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].SoAdTxPduId, &Xcp_TransportLayerEthData[XcpEthTransportLayerId].Xcp_EthDataPacket) == E_OK)
    {
      Xcp_EthResetTxBuffer(XcpEthTransportLayerId);
      /* Check if enough space in Pdu */
      if ((XCP_ETH_PACKET_HEADER_LEN + XcpPacketPtr->SduLength) <= Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].Xcp_PduLength)
      {
        Xcp_EthCopyPacketToBuffer(XcpPacketPtr, XcpEthTransportLayerId);
      }
      else
      {
        RetVal = E_NOT_OK;
      }
    }
    else
    {
      /* Transmission failed, return E_NOT_OK. */
      RetVal = E_NOT_OK;
    }
  }
#endif
  return RetVal;
}


/**
****************************************************************************************************
This function is called by the lower layers when an AUTOSAR XCP PDU has been transmitted
\param[in]  XcpTxPduId  PduId that has been transmitted
\return     -
***************************************************************************************************/
void Xcp_SoAdIfTxConfirmation(PduIdType XcpTxPduId)
{
  /*--- DET reporting ----------------------------------------------------------------------------*/
  /* If Xcp is uninitialized, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((Xcp_GlobalNoInit.InitStatus_u8 != XCP_INIT), XCP_TX_CONFIRMATION_SID, XCP_E_NOT_INITIALIZED);
  /* If Invalid TxPduId, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((XcpTxPduId >= XCP_ETH_NUMBER_OF_TX_PDU), XCP_TX_CONFIRMATION_SID, XCP_E_INVALID_PDUID);
  /*--- / DET reporting --------------------------------------------------------------------------*/

  /* Used only in XcpOnCan */
  XCP_PARAM_UNUSED(XcpTxPduId);

  /* Call of Xcp_TxConfirmation takes place in Xcp_EthMainFunctionTx.
  Inside Xcp_SoAdTxConfirmation only DET reports are issued. */
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
void Xcp_EthMainFunctionTx( void )
{
  uint8 i;

  /* Check all Ethernet transport layers */
  for (i = 0; i < XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS; i++)
  {
    /* Anything to transmit? */
    while ( (Xcp_TransportLayerEthData[i].TxPacketPtr.SduLength != 0u)
#if (XCP_ETH_TRANSMIT_IN_MAINFUNCTION == STD_ON)
          /* was transmit successful? */
          /* MR12 RULE 13.5 VIOLATION: Conditions are evaluated from left to right. The function call is only done if the first condition is TRUE - this is intended behavior; Redesign not possible as while loop instead of if possible - change would decrease maintainability and increase runtime */
          && (Xcp_EthTransmitInMainfunction(&Xcp_TransportLayerEthData[i].TxPacketPtr, i) == E_OK)
#endif
          )
    {
      Xcp_TransportLayerEthData[i].TxPacketPtr.SduLength = 0;
      /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
      Xcp_TxConfirmation(i + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET);
    }

#if (XCP_ETH_FRAME_CONCATENATION == STD_ON)
  #if (XCP_ETH_TRANSMIT_IN_MAINFUNCTION == STD_OFF)
    /* Lock interrupts */
    SchM_Enter_Xcp_EthMainFunc();
  #endif
    /* Check if at the end of Xcp_EthMainFunctionTx the buffer is filled */
    if (Xcp_TransportLayerEthData[i].Xcp_EthDataPacket.SduLength > 0u)
    {
      if(SoAd_IfTransmit(Xcp_TransportLayerConfigEth.TransportLayerEthConfig[i].SoAdTxPduId, &Xcp_TransportLayerEthData[i].Xcp_EthDataPacket) == E_OK)
      {
        /* Clear transmission buffer and reset transmission flag */
        Xcp_EthResetTxBuffer(i);
      }
    }
  #if (XCP_ETH_TRANSMIT_IN_MAINFUNCTION == STD_OFF)
    /* Unlock interrupts */
    SchM_Exit_Xcp_EthMainFunc();
  #endif
#endif
  }
}


/**
****************************************************************************************************
Initialization of the transport layer internal variables
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\param[in]  XcpInitStatus         was Xcp already initialized before or not
\return     -
***************************************************************************************************/
void Xcp_EthInit(uint8 XcpTransportLayerId, uint8 XcpInitStatus)
{
  PduIdType TxPduId;
  Std_ReturnType soConRetVal;
  uint8 XcpEthTransportLayerId;

  soConRetVal = E_NOT_OK;

  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpEthTransportLayerId = XcpTransportLayerId - XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET;

  Xcp_TransportLayerEthData[XcpEthTransportLayerId].Xcp_EthDataPacket.SduDataPtr = Xcp_TransportLayerEthData[XcpEthTransportLayerId].Xcp_DataBuffer_pu8;
  /* Extract TxPduId for socket connection Id calculation. */
  TxPduId = Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].SoAdTxPduId;
  /* Find out the SoConId based on TxPduId. */
  soConRetVal = SoAd_GetSoConId(TxPduId, &Xcp_SoConData[XcpEthTransportLayerId].SoConId);
  /* Open Socket connection with corresponding SoConId. */
  (void)SoAd_OpenSoCon(Xcp_SoConData[XcpEthTransportLayerId].SoConId);
  /* The parameter is not used */
  XCP_PARAM_UNUSED(XcpInitStatus);
}


/**
****************************************************************************************************
Connect command related handling for the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
void Xcp_EthConnect(uint8 XcpTransportLayerId)
{
  uint8 XcpEthTransportLayerId;

  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpEthTransportLayerId = XcpTransportLayerId - XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET;
  /* Return in IpAddr the Remote Address of XCP for further usage in case of socket OFFLINE. */
  Xcp_SoConData[XcpEthTransportLayerId].RemoteIpAddr.domain = Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].SoConDomain;
  /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrType to match the AUTOSAR API Definition  */
  (void)SoAd_GetRemoteAddr(Xcp_SoConData[XcpEthTransportLayerId].SoConId, (TcpIp_SockAddrType *)&Xcp_SoConData[XcpEthTransportLayerId].RemoteIpAddr);
}


/**
****************************************************************************************************
Disconnects the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     result of disconnect request
***************************************************************************************************/
Std_ReturnType Xcp_EthDisconnect(uint8 XcpTransportLayerId)
{
  uint8 XcpEthTransportLayerId;
  Std_ReturnType soConRetVal;

  soConRetVal = E_NOT_OK;

  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpEthTransportLayerId = XcpTransportLayerId - XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET;

  if (Xcp_TransportLayerEthData[XcpEthTransportLayerId].TxPacketPtr.SduLength == 0u)
  {
    if (Xcp_TransportLayerConfigEth.TransportLayerEthConfig[XcpEthTransportLayerId].ProtocolType == XCP_ETH_PROTOCOL_TCP)
    {
      /* For TCP at the moment no close socket request from XCP is needed because the TCP will perform
      the disconnect once the FIN is received from the Remote. */
      soConRetVal = E_OK;
    }
    else
    {
      /* UDP is configured. Close socket connection. */
      soConRetVal = SoAd_CloseSoCon(Xcp_SoConData[XcpEthTransportLayerId].SoConId, TRUE);
    }
  }

  return soConRetVal;
}


/**
****************************************************************************************************
This function handles specific Transport Layer Commands
\param[in]  XcpCmdPacketPtr       Pointer to XcpPacket with received command
\param[out] XcpResPacketPtr       Pointer to XcpPacket where the response shall be stored
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
/* MR12 RULE 8.13 VIOLATION: All transport layers have a functions with this signature. Only in XcpOnEth it is not used and thus empty. Pointer cannot be constant to keep signature identical. */
void Xcp_EthTransportLayerCmd(const PduInfoType* XcpCmdPacketPtr, PduInfoType* XcpResPacketPtr, uint8 XcpTransportLayerId)
{
  XCP_PARAM_UNUSED(XcpCmdPacketPtr);
  XCP_PARAM_UNUSED(XcpResPacketPtr);
  XCP_PARAM_UNUSED(XcpTransportLayerId);
  /* Nothing to do in XcpOnEth */
}


/**
****************************************************************************************************
This function is called by protocol layer to find a XcpTxPduId for a given EventChannel
\param[in]  XcpPacketId             Type of the packet (1st byte of packets to transmit)
\param[in]  XcpEventChannelNumber   Event channel number (relevant for CAN only)
\param[in]  XcpTransportLayerId     Id if Transport Layer given by Protocol layer
\return     XcpTxPduId
***************************************************************************************************/
Xcp_PduIdType Xcp_EthGetTxPduId(uint8 XcpPacketId, uint16 XcpEventChannelNumber, uint8 XcpTransportLayerId)
{
  XCP_PARAM_UNUSED(XcpEventChannelNumber);
  XCP_PARAM_UNUSED(XcpTransportLayerId);
  XCP_PARAM_UNUSED(XcpPacketId);

  return XCP_PDU_ID_UNKNOWN;
}


/**
****************************************************************************************************
This function is called by the lower layers when SoConMode changes
\param[in]  SoConId   Id of the socket connection
\param[in]  Mode      new socket connection mode
\return     -
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_SoConModeChg: Function contains several necessary if statements. HIS metric compliance would decrease readability and maintainability. */
void Xcp_SoConModeChg(SoAd_SoConIdType SoConId, SoAd_SoConModeType Mode)
{
  uint8 Index_u8;

  Index_u8 = 0u;

  while(Index_u8 < XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS)
  {
    if (SoConId == Xcp_SoConData[Index_u8].SoConId)
    {
      switch (Mode)
      {
        case SOAD_SOCON_RECONNECT:
        {
          if(Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET] != XCP_INVALID_PROTLAYER_ID)
          {
            if (Xcp_TransportLayerConfigEth.TransportLayerEthConfig[Index_u8].ProtocolType == XCP_ETH_PROTOCOL_UDP)
            {
              #if (XCP_RESUME_MODE == STD_ON)
              /* When RESUME mode is active the saved address friom the previous connection has to be set */
              /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
              if (Xcp_NoInit[Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET]].Session.XcpState_en == XCP_STATE_RESUME)
              {
                /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrType to match the AUTOSAR API Definition  */
                if (SoAd_SetRemoteAddr(Xcp_SoConData[Index_u8].SoConId, (TcpIp_SockAddrType *)&Xcp_SoConData[Index_u8].RemoteIpAddr) == E_OK)
                {
                  (void)SoAd_OpenSoCon(SoConId);
                }
              }
              #endif
            }
            else
            {
              /* The Protocol type is TCP */
              /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
              if (Xcp_NoInit[Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET]].Session.XcpState_en != XCP_STATE_RESUME)
              {
                /* Disconnect Protocol layer */
                /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
                Xcp_Disconnect(Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET]);
                /* Set XCP state to disconnecting to start the disconnection */
                /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
                Xcp_NoInit[Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET]].Session.XcpState_en = XCP_STATE_DISCONNECTING;
                /* Clear the transmit buffers from Xcp on Eth if the disconnect takes place to avoid sending data from the previous connect session with a new connect. */
                Xcp_TransportLayerEthData[Index_u8].Xcp_EthDataPacket.SduLength = 0u;
              }
              else
              {
                /* Do nothing. The Master has to try to open the Socket with the handshake SYN -> SYN + ACK -> ACK */
              }
            }
          }
        }
        break;
        case SOAD_SOCON_ONLINE:
          /* do nothing */
        break;
        case SOAD_SOCON_OFFLINE:
        {
          if (Xcp_TransportLayerConfigEth.TransportLayerEthConfig[Index_u8].ProtocolType == XCP_ETH_PROTOCOL_UDP)
          {
            /* Clear the transmit buffers from Xcp on Eth if the disconnect takes place to avoid sending data from the previous connect session with a new connect. */
            Xcp_TransportLayerEthData[Index_u8].Xcp_EthDataPacket.SduLength = 0u;
            /* Reopen the socket connection. In case of UDP */
            (void)SoAd_OpenSoCon(Xcp_SoConData[Index_u8].SoConId);
          }
          else
          {
            if(Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET] != XCP_INVALID_PROTLAYER_ID)
            {
              /* The Protocol type is TCP */
              /* Disconnect Protocol layer */
              /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
              Xcp_Disconnect(Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET]);
              /* Set XCP state to disconnecting to start the disconnection */
              /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
              Xcp_NoInit[Xcp_GlobalNoInit.Tl2PlRef_au8[Index_u8 + XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET]].Session.XcpState_en = XCP_STATE_DISCONNECTING;
              /* Clear the transmit buffers from Xcp on Eth if the disconnect takes place to avoid sending data from the previous connect session with a new connect. */
              Xcp_TransportLayerEthData[Index_u8].Xcp_EthDataPacket.SduLength = 0u;
            }
          }
        }
        break;
        default:
        /* Nothing to do */
        break;
      }
      break; /* break to exit the while loop */
    }
    Index_u8++;
  }
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
Xcp_ErrorCode Xcp_EthResumeModeData(Xcp_AdrPtr DaqRamPtr, Xcp_AdrPtrConst XcpDaqRamEndPtr, uint8 XcpTransportLayerId)
{
  uint8 XcpEthTransportLayerId;
  Xcp_ErrorCode Error;

  /* MR12 RULE 2.2 VIOLATION: XCP_*_TRANSPORT_LAYER_INDEX_OFFSET changes depending on the configuration thus the calculation is necessary if the value is not 0 (0 raises the MISRA violation) */
  XcpEthTransportLayerId = XcpTransportLayerId - XCP_ETH_TRANSPORT_LAYER_INDEX_OFFSET;
  /* Check if Transport Layer Id is invalid, report to DET and exit the function  */
  XCP_DET_REPORT_ERROR_RET(((XcpEthTransportLayerId) >= XCP_ETH_NUMBER_OF_TRANSPORT_LAYERS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID, XCP_ERR_GENERIC);

  Error = XCP_NO_ERROR;

  /* If the XcpDaqRamEndPtr is NULL_PTR means that the function is currently used to set back the saved NvM data for the Transport Layer */
  if (XcpDaqRamEndPtr != NULL_PTR)
  {
    /* If enough space to save the remote IP address to NvM then copy the data at the given place otherwise return ERR_MEMORY_OVERFLOW */
    if ((DaqRamPtr + sizeof(TcpIp_SockAddrInet6Type)) <= XcpDaqRamEndPtr)
    {
      /* Copy SoAd Remote IP address to which XCP is connected */
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(DaqRamPtr, &Xcp_SoConData[XcpEthTransportLayerId].RemoteIpAddr, sizeof(TcpIp_SockAddrInet6Type));
    }
    else
    {
      Error = XCP_ERR_MEMORY_OVERFLOW;
    }
  }
  else
  {
    /* It is requested to read the remote IP address from NvM block */
    /* Set the previous remote IP address read from NvM into the Xcp_SoConData for further use */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(&Xcp_SoConData[XcpEthTransportLayerId].RemoteIpAddr, DaqRamPtr, sizeof(TcpIp_SockAddrInet6Type));
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
This function will reset the transmission buffer.
\param[in]  XcpPacketPtr            Pointer to XcpPacket (with Length and data pointer)
\param[in]  XcpEthTransportLayerId  transport layer id
\return     -
***************************************************************************************************/
static void Xcp_EthCopyPacketToBuffer(const PduInfoType* XcpPacketPtr, uint8 XcpEthTransportLayerId)
{
  /* Local variables */
  PduInfoType*  TxPduPtr;
  PduLengthType WritePos;

  /* Get pointer to TxPdu */
  TxPduPtr = &Xcp_TransportLayerEthData[XcpEthTransportLayerId].Xcp_EthDataPacket;
  /* Get PduLength */
  WritePos = TxPduPtr->SduLength;

  /* Ethernet header is always little endian. Same implementation for IFX and JDP. */
  TxPduPtr->SduDataPtr[WritePos]      = (uint8)(XcpPacketPtr->SduLength);
  TxPduPtr->SduDataPtr[WritePos + 1u] = (uint8)(XcpPacketPtr->SduLength >> 8u);
  TxPduPtr->SduDataPtr[WritePos + 2u] = (uint8)(Xcp_EthCtr_u16[XcpEthTransportLayerId]);
  TxPduPtr->SduDataPtr[WritePos + 3u] = (uint8)(Xcp_EthCtr_u16[XcpEthTransportLayerId] >> 8u);

  /* Copy the packet data into the XCP packet after the header data. */
  /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
  Xcp_MemCopy(&TxPduPtr->SduDataPtr[WritePos + XCP_ETH_PACKET_HEADER_LEN], XcpPacketPtr->SduDataPtr, XcpPacketPtr->SduLength);
  /* Store new packet length*/
  TxPduPtr->SduLength = WritePos + XCP_ETH_PACKET_HEADER_LEN + XcpPacketPtr->SduLength;

  /* Increment for next transmission */
  Xcp_EthCtr_u16[XcpEthTransportLayerId]++;
}


/**
****************************************************************************************************
This function will reset the transmission buffer.
\param[in]  XcpEthTransportLayerId  transport layer id
\return     -
***************************************************************************************************/
static void Xcp_EthResetTxBuffer(uint8 XcpEthTransportLayerId)
{
  Xcp_TransportLayerEthData[XcpEthTransportLayerId].Xcp_EthDataPacket.SduLength = 0;
}

#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function will return the XCP packet length from XCP header.
\param[in]  XcpLengthPtr  Pointer to XcpPacket (with Length and data pointer)
\return     length of the XCP packet
***************************************************************************************************/
static PduLengthType Xcp_EthGetPacketLength(const uint8* XcpLengthPtr)
{
  PduLengthType XcpPacketLength;

  XcpPacketLength = XcpLengthPtr[0] + (PduLengthType)((PduLengthType)XcpLengthPtr[1]<<8u);

  return XcpPacketLength;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#endif

/* HIS METRIC COMF VIOLATION IN XcpOnEth.c: If Xcp on Ethernet is disabled, this file is empty. */




