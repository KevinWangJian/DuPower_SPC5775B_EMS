

/*
 * IpduM_GetVersionInfo.c
 *
 *  Created on: 4 May 2012
 *      Author: mus5kor
 */
/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "IpduM.h"
#include "IpduM_Priv.h"
#include "IpduM_Types.h"

#if (IPDUM_VERSION_INFO_API == STD_ON)

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/***************************************************************************************************
 Function name    : IpduM_GetVersionInfo
 Syntax           : void IpduM_GetVersionInfo(Std_VersionInfoType *versioninfo)
 Description      : Service for passing the Information through a pointer "*VersionInfo"
 Parameter        : versioninfo
 Return value     : None
***************************************************************************************************/

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"

FUNC(void, IPDUM_CODE) IpduM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, IPDUM_APPL_DATA) versioninfo)
{

    /* Report DET : Development Error for Invalid  Pointer */
    IPDUM_REPORT_ERROR((versioninfo == NULL_PTR), IPDUMServiceId_GetVersionInfo, IPDUM_E_PARAM_POINTER)

    versioninfo->vendorID = IPDUM_VENDOR_ID;
    versioninfo->moduleID = IPDUM_MODULE_ID;
    versioninfo->sw_major_version = IPDUM_SW_MAJOR_VERSION;
    versioninfo->sw_minor_version = IPDUM_SW_MINOR_VERSION;
    versioninfo->sw_patch_version = IPDUM_SW_PATCH_VERSION;


}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

#endif

