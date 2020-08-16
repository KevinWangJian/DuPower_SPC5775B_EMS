

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

/* MR12 RULE 8.3 VIOLATION: The parameter identifiers in Rte's generated declaration of this depend on Rte vendor */
Std_ReturnType NvM_GetErrorStatus(NvM_BlockIdType BlockId, NvM_RequestResultType *RequestResultPtr)
{
    // TRACE[NVM451] Service to read the block dependent error/status information
    Std_ReturnType stReturn_u8 = E_NOT_OK;

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        // TRACE[NVM610] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_GET_ERROR_STATUS, NVM_E_NOT_INITIALIZED);
    }

    // Check provided parameters
    else if (BlockId >= NVM_CFG_NR_BLOCKS)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        // TRACE[NVM311] Also allow applications to send requests for block ID 1
        // TRACE[NVM611] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_GET_ERROR_STATUS, NVM_E_PARAM_BLOCK_ID);
    }

    else if (RequestResultPtr == NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
        // TRACE[NVM612] Report the DET error NVM_E_PARAM_DATA when a NULL pointer is passed via the parameter RequestResultPtr
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_GET_ERROR_STATUS, NVM_E_PARAM_DATA);
    }

    else
    {
        // Parameters are valid
        // TRACE[NVM015] Read out the selected block's state from the administrative block
        // TRACE[NVM394] NvM_Prv_stRequestResult_rAwAM_au8[0] contains the status of multiblock operations
        // No SchM lock can and should be done here to allow calling this function from NvM callbacks without deadlocks
        *RequestResultPtr = NvM_Prv_stRequestResult_rAwAM_au8[BlockId];
        stReturn_u8 = E_OK;
    }

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
