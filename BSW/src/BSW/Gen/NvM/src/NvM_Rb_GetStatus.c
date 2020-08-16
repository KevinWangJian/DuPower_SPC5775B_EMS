

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

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

Std_ReturnType NvM_Rb_GetStatus(NvM_Rb_StatusType *StatusPtr)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2750] Service to read the overall status of the NVRAM manager
    Std_ReturnType stReturn_u8 = E_NOT_OK;

    // Check provided parameter
    if (StatusPtr == NULL_PTR)
    {
        // Invalid parameter supplied
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3114] Set block ID to 0 if NvM service does not use any block ID
        NvM_Prv_SetBlockIdCausingLastDetError(0u);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_GET_STATUS, NVM_E_PARAM_DATA);
    }

    else
    {
        // Parameter is valid
        // -> translate internal activity status into public NvM status
        // No SchM lock can and should be done here to allow calling this function from NvM callbacks without deadlocks
        NvM_Prv_Activities_ten Activity_en = NvM_Prv_Main_st.Activity_rAMwM_en;
        switch (Activity_en)
        {
            case NVM_PRV_ACTIVITY_NOT_INIT:
                *StatusPtr = NVM_RB_STATUS_UNINIT;
                break;
            case NVM_PRV_ACTIVITY_IDLE:
                *StatusPtr = NVM_RB_STATUS_IDLE;
                break;
            default:
                *StatusPtr = NVM_RB_STATUS_BUSY;
                break;
        }
        stReturn_u8 = E_OK;
    }

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
