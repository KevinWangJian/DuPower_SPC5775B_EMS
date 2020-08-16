
/* It is possible to configure out support for PduR_GetVersionInfo() entirely. */
#include "PduR_Prv.h"
/* Check for version info support during pre-compile time*/
#if defined(PDUR_VERSION_INFO_API) && (PDUR_VERSION_INFO_API != STD_OFF)

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"


/**
 **************************************************************************************************
 * PduR_GetVersionInfo - PDU Router version information. Called for DET Enabled
 *    This service returns the version information of this module. The version information includes
 *    : - Module Id
 *      - Vendor Id
 *      - Vendor specific version numbers.
 *
 * \param           Std_VersionInfoType *versionInfo - Pointer to where to store the version
 *                  information of this module.
 *
 * \retval          None
 * \seealso
 * \usedresources   PDUR234
 **************************************************************************************************
 */
/* PDUR_RTA-BSW_begin  */
FUNC( void, PDUR_CODE ) PduR_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, AUTOMATIC ) versionInfo )
{
    /* checking for NULL or void pointer */
    PDUR_CHECK_PTR_VOID(PDUR_SID_GETVERINFO, versionInfo)

    (versionInfo)->vendorID = PDUR_VENDOR_ID;
    (versionInfo)->moduleID = PDUR_MODULE_ID;
    (versionInfo)->sw_major_version = PDUR_SW_MAJOR_VERSION;
    (versionInfo)->sw_minor_version = PDUR_SW_MINOR_VERSION;
    (versionInfo)->sw_patch_version = PDUR_SW_PATCH_VERSION;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_VERSION_INFO_API */

