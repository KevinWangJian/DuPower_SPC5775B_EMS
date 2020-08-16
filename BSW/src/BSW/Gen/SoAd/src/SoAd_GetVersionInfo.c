

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED

#include "Det.h"

#include "SoAd_Prv.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

/**
 ***************************************************************************************************
 * \Function Name : SoAd_GetVersionInfo()
 *
 * \function description
 * Service for passing the Information through a pointer "*VersionInfo".
 *
 * Parameters (in)      : None
 *
 * Parameters (inout)   : None
 *
 * Parameters (out)     :
 * \param   Std_VersionInfoType
 * \arg     versioninfo -Pointer to where to store the version information of this module.
 *
 * Return value         : None
 *
 *
 ***************************************************************************************************
 */
#if (SOAD_VERSION_INFO_API == STD_ON)

FUNC( void, SOAD_CODE ) SoAd_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, COM_APPL_DATA) versioninfo)
{
#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether versioninfo pointer is valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == versioninfo ), SOAD_GET_VERSION_INFO_API_ID, SOAD_E_PARAM_POINTER )

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        versioninfo->vendorID          = SOAD_VENDOR_ID;
        versioninfo->moduleID          = SOAD_MODULE_ID;
        versioninfo->sw_major_version  = SOAD_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version  = SOAD_SW_MINOR_VERSION;
        versioninfo->sw_patch_version  = SOAD_SW_PATCH_VERSION;
    }/*End of If condition: Check versioninfo should not be a NULL_PTR*/
}

#endif

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
