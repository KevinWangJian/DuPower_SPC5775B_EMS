

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
This command brings Xcp slave to DISCONNECTED state and handles response processing
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdDisconnect(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  XCP_PARAM_UNUSED(XcpPacket);
  /* Disconnect Protocol layer */
  Xcp_Disconnect(protLayerId);


  /* prepare pos. response */
  Xcp_SendPosRes(protLayerId);

  /* Disconnect request was received and transport layer disconnect functions must be called. */
  /* The DISCONNECTING state is set at the end after sending the response to avoid disconnecting the TL(in MainFunction) before sending. */
  Xcp_NoInit[protLayerId].Session.XcpState_en = XCP_STATE_DISCONNECTING;

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



