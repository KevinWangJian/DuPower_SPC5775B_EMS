

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

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command handles the connect request and his response processing.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdConnect(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdConnect_t* const CmdPtr = (const Xcp_CmdConnect_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResConnect_t* ResPtr = (Xcp_ResConnect_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* check if the requested mode is normal, user defined mode not supported */
  if( CmdPtr->Mode_u8 == 0x00 )
  {
    /* set the connect status to CONNECTED */
    Xcp_NoInit[protLayerId].Session.XcpState_en = XCP_STATE_CONNECTED;

    /* prepare positive response */
    /* set length response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_CONNECT_LENGTH;
    /* Set Pid */
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;

    /* Set RESOURCE byte */
    ResPtr->Resource_u8 = Xcp_GlobalNoInit.EnabledResources_u8;

    /* Initialize COMM_MODE_BASIC */
    ResPtr->CommModeBasic_u8 = 0x00u;

#if (XCP_CMD_GET_COMM_MODE_INFO_AVAILABLE == STD_ON)
    /* Set COMM_MODE_BASIC byte */
    /* Bit 7: optional -> GET_COMM_MODE_INFO command is supported */
    ResPtr->CommModeBasic_u8 |= 0x80u;
#endif

    /* Bit 6: Slave Block Mode */
#if (XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
    ResPtr->CommModeBasic_u8 |= 0x40u;
#endif
    /* Bits 5-3 reserved */
    /* Bits 2-1 Address Granularity: Byte always 0-> (0,0) */
    /* Bit 0 Byte order */
#if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    ResPtr->CommModeBasic_u8 |= 0x01u;
#endif

    /* Set CTO size in bytes */
    ResPtr->MaxCto_u8 = XCP_MAXCTO(protLayerId);

    /* Set DTO size in bytes */
    ResPtr->MaxDto_u16 = XCP_MAXDTO(protLayerId);

    /* Set protocol layer major version number */
    ResPtr->XcpProtocolLayerVersion_u8 = XCP_ASAM_MAJOR_VERSION;

    /* Set transport layer major version number */
    ResPtr->XcpTransportLayerVersion_u8 = XCP_ASAM_MAJOR_VERSION;

    /* call TransportLayer connect function */
    Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TLConnect_pfct(XCP_ACTIVE_TL_ID(protLayerId));

    /* Send positive response */
    Xcp_SendRes(protLayerId);
  }
  else /* user defined or invalid mode (mode not in specification) */
  {
    /* not supported */
    /* disconnect protocol layer */
    Xcp_Disconnect(protLayerId);
    /* Send error response */
    Xcp_SendErrRes(XCP_ERR_OUT_OF_RANGE, protLayerId);
    /* Set Xcp state to disconnecting to disconnect the transport layer. */
    /* The DISCONNECTING state is set at the end after sending the response to avoid disconnecting the TL(in MainFunction) before sending. */
    Xcp_NoInit[protLayerId].Session.XcpState_en = XCP_STATE_DISCONNECTING;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



