

#ifndef XCPONFR_H
#define XCPONFR_H

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cfg.h"

/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/


/***************************************************************************************************
* Type definitions
***************************************************************************************************/


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Function prototypes
***************************************************************************************************/
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
extern Std_ReturnType Xcp_FrTransmit(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId, Xcp_PduIdType XcpTxPduId);

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
extern void Xcp_FrMainFunctionTx(void);

/**
****************************************************************************************************
Initialization of the transport layer internal variables
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\param[in]  XcpInitStatus         was Xcp already initialized before or not
\return     -
***************************************************************************************************/
extern void Xcp_FrInit(uint8 XcpTransportLayerId, uint8 XcpInitStatus);

/**
****************************************************************************************************
Connect command related handling for the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
extern void Xcp_FrConnect(uint8 XcpTransportLayerId);

/**
****************************************************************************************************
Disconnects the transport layer
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     result of disconnect request
***************************************************************************************************/
extern Std_ReturnType Xcp_FrDisconnect(uint8 XcpTransportLayerId);

/**
****************************************************************************************************
This function handles specific Transport Layer Commands
\param[in]  XcpCmdPacketPtr       Pointer to XcpPacket with received command
\param[out] XcpResPacketPtr       Pointer to XcpPacket where the response shall be stored
\param[in]  XcpTransportLayerId   Global Transport Layer Id
\return     -
***************************************************************************************************/
extern void Xcp_FrTransportLayerCmd(const PduInfoType* XcpCmdPacketPtr, PduInfoType* XcpResPacketPtr, uint8 XcpTransportLayerId);

/**
****************************************************************************************************
This function is called by protocol layer to find a XcpTxPduId for a given EventChannel
\param[in]  XcpPacketId             Type of the packet (1st byte of packets to transmit)
\param[in]  XcpEventChannelNumber   Event channel number (relevant for CAN only)
\param[in]  XcpTransportLayerId     Id if Transport Layer given by Protocol layer
\return     XcpTxPduId
***************************************************************************************************/
extern Xcp_PduIdType Xcp_FrGetTxPduId(uint8 XcpPacketId, uint16 XcpEventChannelNumber, uint8 XcpTransportLayerId);

#if ((XCP_RESUME_MODE == STD_ON) && (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON))
/**
****************************************************************************************************
This function is called to copy transport layer needed data for Resume Mode
\param[in]  DaqRamPtr             Pointer to Daq RAM address where data is saved
\param[in]  XcpDaqRamEndPtr       Last DAQ RAM address for requested Protocol Layer
\param[in]  XcpTransportLayerId   Id if Transport Layer given by Protocol layer
\return     Error code in case is not enough space to save the data
***************************************************************************************************/
extern Xcp_ErrorCode Xcp_FrResumeModeData(Xcp_AdrPtr DaqRamPtr, Xcp_AdrPtrConst XcpDaqRamEndPtr, uint8 XcpTransportLayerId);
#endif

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


#endif   /* #ifndef XCPONFR_H */


