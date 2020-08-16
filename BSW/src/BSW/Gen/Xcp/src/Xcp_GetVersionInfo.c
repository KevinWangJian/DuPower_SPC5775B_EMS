
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
#if (XCP_VERSION_INFO_API == STD_ON)
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function updates the version information of this module
\param[in]  versioninfo   version info pointer
\return     -
***************************************************************************************************/
void Xcp_GetVersionInfo( Std_VersionInfoType* versioninfo)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* If versioninfo is NULL_PTR, report to DET and exit the function */
  XCP_DET_REPORT_ERROR((versioninfo == NULL_PTR), XCP_GET_VERSION_INFO_SID, XCP_E_INV_POINTER);

  versioninfo->vendorID = XCP_VENDOR_ID;
  versioninfo->moduleID = XCP_MODULE_ID;
  versioninfo->sw_major_version = XCP_SW_MAJOR_VERSION;
  versioninfo->sw_minor_version = XCP_SW_MINOR_VERSION;
  versioninfo->sw_patch_version = XCP_SW_PATCH_VERSION;

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#endif

