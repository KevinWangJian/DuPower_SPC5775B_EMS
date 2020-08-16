

/**
 **************************************************************************************************
 * FiM_Version.c
 * version API for Function Inhibition Manager
 * Design specification: AUTOSAR_SWS_FunctionInhibitionManager.pdf Version 4.0 Rev0002
 **************************************************************************************************
 */
#include "FiM.h"
#include "FiM_Det.h"
#include "Dem.h"

#if (FIM_CFG_DEV_ERROR_DETECT == FIM_CFG_ON) /* if the modul DET is not existed, it is no need to check and report the error to DET */

/**
 **************************************************************************************************
 * version compatibility check for Det according to [AR402:FIM023]
 **************************************************************************************************
 */
#ifndef DET_AR_RELEASE_MAJOR_VERSION
#error DET_AR_RELEASE_MAJOR_VERSION is not defined or not visible via Det.h   !
#else
#if (DET_AR_RELEASE_MAJOR_VERSION != FIM_AR_RELEASE_MAJOR_VERSION)
#error DET_AR_RELEASE_MAJOR_VERSION is not compatible to the FiM version   !
#endif
#endif

#ifndef DET_AR_RELEASE_MINOR_VERSION
#error DET_AR_RELEASE_MINOR_VERSION is not defined or not visible via Det.h   !
#else
#if (DET_AR_RELEASE_MINOR_VERSION != FIM_AR_RELEASE_MINOR_VERSION)
#error DET_AR_RELEASE_MINOR_VERSION is not compatible to the FiM version   !
#endif
#endif

#endif
/**
 **************************************************************************************************
 * version compatibility check for Dem [AR402:FIM023]
 **************************************************************************************************
 */
#ifndef DEM_AR_RELEASE_MAJOR_VERSION
#error DEM_AR_RELEASE_MAJOR_VERSION is not defined or not visible via Dem.h   !
#else
#if (DEM_AR_RELEASE_MAJOR_VERSION != FIM_AR_RELEASE_MAJOR_VERSION)
#error DEM_AR_RELEASE_MAJOR_VERSION is not compatible to the FiM version   !
#endif
#endif

#ifndef DEM_AR_RELEASE_MINOR_VERSION
#error DEM_AR_RELEASE_MINOR_VERSION is not defined or not visible via Dem.h   !
#else
#if (DEM_AR_RELEASE_MINOR_VERSION != FIM_AR_RELEASE_MINOR_VERSION)
#error DEM_AR_RELEASE_MINOR_VERSION is not compatible to the FiM version   !
#endif
#endif

/**
 **************************************************************************************************
 * FiM_GetVersionInfo (public API)
 **************************************************************************************************
 */
#if (FIM_CFG_VERSION_INFO_API == FIM_CFG_ON)
#define FIM_START_SEC_ROM_CODE
#include "FiM_MemMap.h"

void FiM_GetVersionInfo(Std_VersionInfoType* versioninfo)
{
    if (versioninfo != NULL_PTR)
    {
        versioninfo->vendorID = FIM_VENDOR_ID;
        versioninfo->moduleID = FIM_MODULE_ID;
        versioninfo->sw_major_version = FIM_SW_MAJOR_VERSION;
        versioninfo->sw_minor_version = FIM_SW_MINOR_VERSION;
        versioninfo->sw_patch_version = FIM_SW_PATCH_VERSION;
    }
    else
    {
        FIM_PRIV_DET_ERROR(FIM_GETVERSIONINFO_ID, FIM_E_PARAM_POINTER);
    }
}

#define FIM_STOP_SEC_ROM_CODE
#include "FiM_MemMap.h"
#endif

