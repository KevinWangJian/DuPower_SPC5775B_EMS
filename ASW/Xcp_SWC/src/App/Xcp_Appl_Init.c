
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"
#include "Xcp_Priv.h"
#include "Xcp_Integration.h"

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

#if (   (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
     || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)) )
/**
****************************************************************************************************
Function to do specific initialization or cancel pending background process
\param[in]  XcpInitStatus     Xcp Initialization status: XCP_INIT or XCP_UNINIT
\param[in]  ProtocolLayerId   protocol layer id
\return     Was initialization successful
\retval     E_OK              Initialization is finished
\retval     E_NOT_OK          Initialization is not finished, this function will be called
                              in next Xcp_MainFunction() again until it returns E_OK
***************************************************************************************************/
Std_ReturnType XcpAppl_Init(uint8 XcpInitStatus, uint8 ProtocolLayerId)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(XcpInitStatus);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Do checks here... */

  return(E_OK);
}
#endif

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"


