

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
Function used to perform transport Layer specific actions
\param[in]  XcpPacket     pointer to the received XcpPacket
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_CmdTransportLayerCmd(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  PduInfoType XcpResPacket;
  uint8 TransportLayerId;

  /* Initial values */
  TransportLayerId = XCP_ACTIVE_TL_ID(protLayerId);

  XCP_DET_REPORT_ERROR((TransportLayerId >= XCP_TL_IDS), XCP_TRANSMIT_SID, XCP_E_INVALID_TRANSPORT_LAYER_ID);

  XcpResPacket.SduDataPtr = XCP_RES_BUFFER_PTR(protLayerId);
  XcpResPacket.SduLength  = 0;

  /* Call the function */
  Xcp_PlCfgConst.TlCfg[TransportLayerId].TLTransportLayerCmd_pfct(XcpPacket, &XcpResPacket, TransportLayerId);

  /* Any response to send? */
  if (XcpResPacket.SduLength > 0u)
  {
    /* Copy the length from PduInfoType into response packet */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XcpResPacket.SduLength;

    /* Send response */
    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Send error response */
#if ((XCP_ASAM_MAJOR_VERSION <= 1u) && (XCP_ASAM_MINOR_VERSION <= 2u))
    /* Unknown command */
    Xcp_SendErrRes(XCP_ERR_CMD_UNKNOWN, protLayerId);
#else
    /* Unknown subcommand for Xcp 1.3 version and beyond */
    Xcp_SendErrRes(XCP_ERR_SUBCMD_UNKNOWN, protLayerId);
#endif
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



