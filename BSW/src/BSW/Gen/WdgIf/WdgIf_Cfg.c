



/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
 /*TRACE[WDGIF003] WdgIf shall not add functionality not abstract from properties from watchdog drivers*/
#include "WdgIf.h"

#if (WDGIF_DEV_ERROR_DETECT==STD_ON)
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error “AUTOSAR major version undefined or mismatched?
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error “AUTOSAR minor version undefined or mismatched?
#endif
#endif /*(WDGIF_DEV_ERROR_DETECT==STD_ON)*/



 /*
 ***************************************************************************************************
 * Constants
 ***************************************************************************************************
 */


 /*
 ***************************************************************************************************
 * Function Definitions
 ***************************************************************************************************
 */






#define WDGIF_START_SEC_CODE_SLOW
#include "WdgIf_MemMap.h"
/************************************************************************************************************************
* Name              :	WdgIf_GetVersionInfo
* Description       :   Returns the version information of the WdgIf module
* Parameters[in]    :	None
* Limitations       :   None
* Return Value      :	Pointer to where to store the version information of WdgIf module
************************************************************************************************************************/
/* TRACE[WDGIF046] Returns the version info of WdgIf module*/
FUNC(void, WDGIF_CODE_SLOW) WdgIf_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC, WDGIF_APPL_DATA)VersionInfoPtr)
{

    /* TRACE[WDGIF058] Check for NULL pointer */
    
    if (VersionInfoPtr == NULL_PTR)
    {
        /* TRACE[WDGIF032] Perform reporting of Detected development errors*/
        /* TRACE[WDGIF031] Perform checking of DET parameters*/
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGIF_MODULE_ID, WDGIF_INSTANCE_ID, WDGIF_GETVERSIONINFO_SERVICEID, WDGIF_E_INV_POINTER);
        return;
    }
	

    /* TRACE[WDGIF035] Return a fixed format or Version Info*/
    VersionInfoPtr->vendorID = WDGIF_VENDOR_ID;
    VersionInfoPtr->moduleID = WDGIF_MODULE_ID;
    VersionInfoPtr->sw_major_version = WDGIF_SW_MAJOR_VERSION;
    VersionInfoPtr->sw_minor_version = WDGIF_SW_MINOR_VERSION;
    VersionInfoPtr->sw_patch_version = WDGIF_SW_PATCH_VERSION;

    return;
}
#define WDGIF_STOP_SEC_CODE_SLOW
#include "WdgIf_MemMap.h"


