


/**
 **********************************************************************************************************************
 * \moduledescription
 *           AUTOSAR FEE
 *           According to Document Version 3.0.0, Part of Release 4.0, Revision 2
 * \scope    INTERN
 **********************************************************************************************************************
 */


/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "Fee.h"
#include "rba_FeeFs1_Prv.h"

#if(defined(FEE_PRV_CFG_SELECTED_FS) && (1 == FEE_PRV_CFG_SELECTED_FS))

#if(STD_ON == FEE_DEV_ERROR_DETECT)
#include "Det.h"
/* Version check deactivated due to incompatabality with CC-AS (AR3.1)
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != FEE_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
*/
#endif


#if (STD_ON == FEE_VERSION_INFO_API)
/**
 *********************************************************************
 * Fee_GetVersionInfo(): Return version information
 *
 * This function returns general and SW version information
 *
 * \param   VersioninfoPtr: Pointer to return the version
 *                          information of this module.
 * \return  None
 * \retval
 * \seealso
 * \usedresources
 *********************************************************************
 */
#define FEE_START_SEC_CODE
#include "Fee_MemMap.h"
FUNC(void, FEE_CODE) Fee_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, FEE_APPL_DATA) VersionInfoPtr)
{

    #if(STD_ON == FEE_DEV_ERROR_DETECT)
    if(VersionInfoPtr == NULL_PTR)
    {
        /* Report error to DET */
        /* MR12 RULE 17.7 VIOLATION: Return value is not required */
        (void)Det_ReportError(FEE_MODULE_ID, FEE_INSTANCE_ID, FEE_SID_GETVERSIONINFO, FEE_E_INVALID_DATA_PTR);

        /* Return to prevent the system from traps */
        return;
    }
    /* FEE_DEV_ERROR_DETECT */
    #endif

    VersionInfoPtr->vendorID            = FEE_VENDOR_ID;
    VersionInfoPtr->moduleID            = FEE_MODULE_ID;
    VersionInfoPtr->sw_major_version    = FEE_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version    = FEE_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version    = FEE_SW_PATCH_VERSION;
}
#define FEE_STOP_SEC_CODE
#include "Fee_MemMap.h"
/* FEE_VERSION_INFO_API == TRUE */
#endif
/* 1 == FEE_PRV_CFG_SELECTED_FS */
#endif

/*<BASDKey>
**********************************************************************************************************************
* $History__:$
**********************************************************************************************************************
</BASDKey>*/
