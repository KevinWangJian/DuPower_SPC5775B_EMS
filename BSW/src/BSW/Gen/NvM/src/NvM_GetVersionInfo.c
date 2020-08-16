

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "Rte_NvM.h"

#if (NVM_DEV_ERROR_DETECT == STD_ON)
# include "Det.h"    // TRACE[NVM556] NvM module shall include Det.h
// TRACE[NVM089] Check version compatibility of included header files
# if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
#  error "AUTOSAR major version undefined or mismatched"
# endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || ((DET_AR_RELEASE_MINOR_VERSION != 0) && (DET_AR_RELEASE_MINOR_VERSION != 2)))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "NvM_Prv.h"


/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/

#if (NVM_VERSION_INFO_API == STD_ON)

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

// TRACE[NVM286] The function NvM_GetVersionInfo shall be pre compile time configurable by the configuration parameter
// NvMVersionInfoApi.
// TRACE[NVM650] The function NvM_GetVersionInfo shall be configurable On/Off by the configuration parameter
// NvMVersionInfoApi.

void NvM_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr)
{
    // TRACE[NVM452] Service to get the version information of the NvM module

    if (VersionInfoPtr == NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3114] Set block ID to 0 if NvM service does not use any block ID
        NvM_Prv_SetBlockIdCausingLastDetError(0u);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        // TRACE[NVM613] Report the DET error NVM_E_PARAM_POINTER when a NULL pointer is passed via the parameter VersionInfo
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_GET_VERSION_INFO, NVM_E_PARAM_POINTER);
    }

    else
    {
        // TRACE[NVM285] The function NvM_GetVersionInfo shall return the version information of this module.
        // The version information includes:
        //      - Module Id
        //      - Vendor Id
        //      - Software version
        VersionInfoPtr->vendorID            = NVM_VENDOR_ID;
        VersionInfoPtr->moduleID            = NVM_MODULE_ID;
        VersionInfoPtr->sw_major_version    = NVM_SW_MAJOR_VERSION;
        VersionInfoPtr->sw_minor_version    = NVM_SW_MINOR_VERSION;
        VersionInfoPtr->sw_patch_version    = NVM_SW_PATCH_VERSION;
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#endif
