

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

#ifdef NVM_CFG_API_ERASE_NV_BLOCK
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2917] Declaration of the overloading function shall be done here, not in a header file
    /* MR12 RULE 8.5 VIOLATION: Not using a header file for this declaration is a customer requirement */
    extern Std_ReturnType NVM_CFG_API_ERASE_NV_BLOCK(NvM_BlockIdType BlockId);

    /* MR12 RULE 8.3 VIOLATION: The parameter identifiers in Rte's generated declaration of this depend on Rte vendor */
    Std_ReturnType NvM_EraseNvBlock(NvM_BlockIdType BlockId)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2920] Call the overloading function
        return NVM_CFG_API_ERASE_NV_BLOCK(BlockId);
    }

    Std_ReturnType NvM_Rb_EraseNvBlockBase(NvM_BlockIdType BlockId)
#else
    /* MR12 RULE 8.3 VIOLATION: The parameter identifiers in Rte's generated declaration of this depend on Rte vendor */
    Std_ReturnType NvM_EraseNvBlock(NvM_BlockIdType BlockId)
#endif
{
    // TRACE[NVM457] Service to erase a NV block
    Std_ReturnType stReturn_u8 = E_NOT_OK;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Variables used to report DET errors
    boolean flgDetError_b = FALSE;
    uint8 idDetError_u8 = NVM_PRV_NO_DET_ERROR;
#endif

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM631] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_NOT_INITIALIZED;
#endif
    }
    else if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_ERASE_NV_BLOCK, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // TRACE[NVM635] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
    }
    else if (!NvM_Prv_IsSanitizedByReadAll(NvM_Prv_BlockDescriptors_acst[BlockId].stFlags_u16))
    {
        //TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the potentially incompatible blocks after layout changes
        //     should be sanitized by ReadAll at first, then the current single block request
        //     is allowed to be accepted and executed
    }
    else if (NvM_Prv_BlockDescriptors_acst[BlockId].JobPriority_u8 != NVM_PRV_JOB_PRIORITY_IMMEDIATE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM636] Report the DET error NVM_E_BLOCK_CONFIG when the NVRAM block has not immediate priority
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_BLOCK_CONFIG;
#endif
        // TRACE[NVM357] Return with E_NOT_OK, when development error detection is enabled and the referenced NVRAM
        // block is configured with standard priority
        // E_NOT_OK is returned even if development error detection is not enabled.
    }
	// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3032] Ignore blocks with length null
    else if (*NvM_Prv_BlockDescriptors_acst[BlockId].nrBlockBytes_pu16 == 0)
    {
        // Block length is Null
        // Block is pre-defined but not used
        // Job shall never start
        // return E_NOT_OK
    }
    else
    {
        // TRACE[NVM231] The actual erase operation is not done here, just the request for doing it is queued
        SchM_Enter_NvM_Main();

        // TRACE[NVM418] Queuing this request is done in case write-protection is disabled
        // TRACE[NVM273] Check the write protection before queuing the request and report an error if the block is write-protected
        // Check that the dataset index does not point to a ROM block if the NvM block is of type DATASET
        if (((NvM_Prv_stBlock_rAwAM_au8[BlockId] & NVM_BLOCK_STATE_WRITE_PROT) == 0u) &&
            ((NVM_BLOCK_DATASET != NvM_Prv_BlockDescriptors_acst[BlockId].BlockManagementType_en) ||
             (NvM_Prv_idxDataSet_rAMwA_au8[BlockId] < NvM_Prv_BlockDescriptors_acst[BlockId].nrNvBlocks_u8)))
        {
            // TRACE[NVM385] Only queue this request if no operation on this block is requested or in progress
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2866] Exception to NVM385: NvM_EraseNvBlock can be queued for a block whose the only pending operation is a a maintenance operation.
            if (((NvM_Prv_stRequests_rAMwAM_au16[BlockId] == 0) && (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 != BlockId))
#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
                || (NvM_Prv_stRequests_rAMwAM_au16[BlockId] == NVM_PRV_BLOCK_REQ_MAINTAIN)
                || (
                    (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK) &&
                    (NvM_Prv_stRequests_rAMwAM_au16[BlockId] == 0) &&
                    (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 == BlockId)
                   )
#endif
               )
            {
                // TRACE[NVM181] Queue this request to allow multiple concurrent single block requests
                if (NvM_Prv_QueueBlockRequest(NVM_SERVICE_ID_ERASE_NV_BLOCK, BlockId, NULL_PTR) == NVM_PRV_QUEUE_OP_OK)
                {
                    // TRACE[NVM185] Set single block request result to NVM_REQ_PENDING on successful enqueuing
                    NvM_Prv_stRequestResult_rAwAM_au8[BlockId] = NVM_REQ_PENDING;

                    // Internally signal that this block has been requested to be erased
                    NvM_Prv_stRequests_rAMwAM_au16[BlockId] |= (uint16) NVM_PRV_BLOCK_REQ_ERASE;

                    stReturn_u8 = E_OK;
                }
                // TRACE[NVM184] In case of a queue overflow, the return value is E_NOT_OK
            }
            else
            {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
                // TRACE[NVM632] Report the DET error NVM_E_BLOCK_PENDING when the NVRAM block identifier is already queued or currently in progress
                flgDetError_b = TRUE;
                idDetError_u8 = NVM_E_BLOCK_PENDING;
#endif
            }
        }

        else
        {
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2818] Report an error by setting a block error flag if an erase is attempted for a write protected block
            // To be compliant with NVM377, do the same if an erase of a ROM block of an NvM-block of type DATASET is attempted
            NvM_Rb_stBlockErrors_au8[BlockId] |= NVM_E_WRITE_PROTECTED;
            // Set write-protected error flag
            NvM_Rb_stBlockErrors_au8[NVM_PRV_MULTI_BLOCK] |= NVM_E_WRITE_PROTECTED;

            // TRACE[NVM262] If a write protected block is attempted to be erased, E_NOT_OK is returned
            // TRACE[NVM661] If the dataset-index points to a ROM-block (in case the NvM-block is of type DATASET) and an erase is attempted, E_NOT_OK is returned
        }

        SchM_Exit_NvM_Main();
    }

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Calling foreign DET function is done out of the Schm lock
    if (flgDetError_b != FALSE)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
        NvM_Prv_SetBlockIdCausingLastDetError(BlockId);
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_ERASE_NV_BLOCK, idDetError_u8);
    }
#endif

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
