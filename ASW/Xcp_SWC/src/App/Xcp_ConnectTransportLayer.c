
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

#if (XCP_CONNECT_TRANSPORT_LAYER_CALLOUT == STD_ON)
/**
****************************************************************************************************
Function is called to check the connection is allowed to TransportLayer or not
\attention  XcpTransportLayerId is used and not XcpProtocolLayerId!
\param[in]  XcpTransportLayerId   Transport Layer Id
\return     State if connection is allowed
\retval     E_OK      Connection is allowed
\retval     E_NOT_OK  Connection is not allowed
***************************************************************************************************/
Std_ReturnType XcpAppl_ConnectTransportLayer(uint8 XcpTransportLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(XcpTransportLayerId);

  /* Return actual status based on implementation */
  return(E_OK);
}
#endif /* (XCP_CONNECT_TRANSPORT_LAYER_CALLOUT == STD_ON) */

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"


