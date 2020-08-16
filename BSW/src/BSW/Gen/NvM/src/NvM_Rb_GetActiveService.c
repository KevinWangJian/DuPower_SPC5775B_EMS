

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

Std_ReturnType NvM_Rb_GetActiveService(uint8 *ServiceIdPtr)
{
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2827] Service to read the ID of the currently active service of the NVRAM manager
    Std_ReturnType stReturn_u8 = E_NOT_OK;

    if (ServiceIdPtr == NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3114] Set block ID to 0 if NvM service does not use any block ID
        NvM_Prv_SetBlockIdCausingLastDetError(0u);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_RB_GET_ACTIVE_SERVICE, NVM_E_PARAM_DATA);
    }

    else
    {
        // Use the local var idActiveService_u8 so that even if NvM_Prv_Main_st.idActiveService_rAMwM_u8 is changed by the main function to
        // NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK after the "if" but before the "else", NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK is not returned.
        uint8 idActiveService_u8 = NvM_Prv_Main_st.idActiveService_rAMwM_u8;

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
        // The maintenance phase shall not be visible for an NvM user.
        // CAUTION: The following assignment has to be changed in the future if it is decided to make the maintenance operation visible for an NvM user.
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2865] NvM_Rb_GetActiveService indicates that the active service is WRITE_ALL if the maintenance operation is currently being executed.
        if (idActiveService_u8 == NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK)
        {
            *ServiceIdPtr = NVM_SERVICE_ID_WRITE_ALL;
        }
        else
#endif
        {
            *ServiceIdPtr = idActiveService_u8 ;
        }

        stReturn_u8 = E_OK;
    }

    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
