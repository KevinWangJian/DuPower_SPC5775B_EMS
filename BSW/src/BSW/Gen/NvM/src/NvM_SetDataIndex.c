

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "NvM_Cfg_SchM.h"

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
Std_ReturnType NvM_SetDataIndex(NvM_BlockIdType BlockId, uint8 DataIndex)
{
    // TRACE[NVM448] Service for setting the DataIndex of a dataset NVRAM block
    // TRACE[NVM264] If the block management type is not NVM_BLOCK_DATASET, this function has no effect in production
    // TRACE[NVM146] The dataset index can also select ROM blocks in case the block is of type DATASET
    Std_ReturnType stReturn_u8 = E_NOT_OK;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Variables used to report DET errors
    boolean flgDetError_b = FALSE;
    uint8 idDetError_u8 = NVM_PRV_NO_DET_ERROR;
#endif

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM027] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_NOT_INITIALIZED;
#endif
    }
    else if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_SET_DATA_INDEX, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // TRACE[NVM601] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
    }
    else if (NvM_Prv_BlockDescriptors_acst[BlockId].BlockManagementType_en != NVM_BLOCK_DATASET)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM600] Report the DET error NVM_E_PARAM_BLOCK_TYPE when the request is not possible in conjunction with the configured block management type
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_PARAM_BLOCK_TYPE;
#endif
    }
    else if (DataIndex >= (NvM_Prv_BlockDescriptors_acst[BlockId].nrNvBlocks_u8 + NvM_Prv_BlockDescriptors_acst[BlockId].nrRomBlocks_u8))
    {
        // TRACE[NVM188] If the NvMDevErrorDetect switch is enabled API parameter checking is enabled
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM599] DataIndex parameter exceeds the total number of configured datasets
        // TRACE[NVM599] Report the DET error NVM_E_PARAM_BLOCK_DATA_IDX when DataIndex exceeds the number of configured datasets
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_PARAM_BLOCK_DATA_IDX;
#endif
    }
    else
    {
        // Parameters are valid
        // TRACE[NVM014] Set the data index of the selected block if its management type is NVM_BLOCK_DATASET
        // TRACE[NVM704] Prohibit administrative data block modifications while a single-block operation is pending or in progress
        // Note: The condition below also intentionally locks out those modifications if a multi-block operation
        //       is currently busy with the selected block (just for safety reasons)
        SchM_Enter_NvM_Main();
        if ((NvM_Prv_stRequests_rAMwAM_au16[BlockId] == 0) && (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 != BlockId))
        {
            NvM_Prv_idxDataSet_rAMwA_au8[BlockId] = DataIndex;
            stReturn_u8 = E_OK;
        }
        else
        {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
            // TRACE[NVM598] Report the DET error NVM_E_BLOCK_PENDING when NVRAM block identifier is already queued or currently in progress
            flgDetError_b = TRUE;
            idDetError_u8 = NVM_E_BLOCK_PENDING;
#endif
        }
        SchM_Exit_NvM_Main();
    }

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Calling foreign DET function is done out of the Schm lock
    if (flgDetError_b != FALSE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_SET_DATA_INDEX, idDetError_u8);
    }
#endif

    // TRACE[NVM263] The permanent RAM block contents are not modified here
    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
