

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

#ifdef NVM_CFG_API_READ_BLOCK
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2917] Declaration of the overloading function shall be done here, not in a header file
    /* MR12 RULE 8.5 VIOLATION: Not using a header file for this declaration is a customer requirement */
    extern Std_ReturnType NVM_CFG_API_READ_BLOCK(NvM_BlockIdType BlockId, void *NvM_DstPtr);

    /* MR12 RULE 8.3 VIOLATION: The parameter identifiers in Rte's generated declaration of this depend on Rte vendor */
    Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId, void *NvM_DstPtr)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2920] Call the overloading function
        return NVM_CFG_API_READ_BLOCK(BlockId, NvM_DstPtr);
    }

    Std_ReturnType NvM_Rb_ReadBlockBase(NvM_BlockIdType BlockId, void *NvM_DstPtr)
#else
    /* MR12 RULE 8.3 VIOLATION: The parameter identifiers in Rte's generated declaration of this depend on Rte vendor; typedef is generated by Rte instead of using void pointer (but is compatible) */
    Std_ReturnType NvM_ReadBlock(NvM_BlockIdType BlockId, void *NvM_DstPtr)
#endif
{
    // TRACE[NVM454] Service to copy the data of the NV block to its corresponding RAM block
    void *adrRamBlock_pv = NvM_DstPtr;
    Std_ReturnType stReturn_u8 = E_NOT_OK;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
    // Variables used to report DET errors
    boolean flgDetError_b = FALSE;
    uint8 idDetError_u8 = NVM_PRV_NO_DET_ERROR;
#endif

    if (NvM_Prv_Main_st.isInitialized_rAM_b != TRUE)
    {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
        // TRACE[NVM614] Report the DET error NVM_E_NOT_INITIALIZED when the NVM is not yet initialized
        flgDetError_b = TRUE;
        idDetError_u8 = NVM_E_NOT_INITIALIZED;
#endif
    }
    else if (!NvM_Prv_IsBlockIdValid(NVM_SERVICE_ID_READ_BLOCK, BlockId, BlockId))
    {
        // block ID is invalid so this service does not start and returns E_NOT_OK
        // TRACE[NVM618] Report the DET error NVM_E_PARAM_BLOCK_ID when the passed BlockID is out of range
    }
    else if (!NvM_Prv_IsSanitizedByReadAll(NvM_Prv_BlockDescriptors_acst[BlockId].stFlags_u16))
    {
        //TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the potentially incompatible blocks after layout changes
        //     should be sanitized by ReadAll at first, then the current single block request
        //     is allowed to be accepted and executed
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
        // Parameters are valid
        // TRACE[NVM010] Trigger a read of the block data from NV memory to RAM
        // TRACE[NVM195] The actual read operation is not done here, just the request for doing it is queued
        SchM_Enter_NvM_Main();

        // TRACE[NVM385] Only queue this request if no operation on this block is requested or in progress
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2866] Exception to NVM385: NvM_ReadBlock can be queued for a block whose the only pending operation is a a maintenance operation.
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
            // No operation pending
            // TRACE[NVM278] Only take the permanent RAM block if no temporary RAM block has been specified
            if (!adrRamBlock_pv)
            {
                adrRamBlock_pv = *NvM_Prv_BlockDescriptors_acst[BlockId].adrRamBlock_ppv;
            }

            // Now queue the read request and additionally set the read request flag of this block if we have a RAM block to read to
            if (adrRamBlock_pv != NULL_PTR)
            {
                // Read block contents to the given destination or restore from ROM if the block is of type DATASET and the index points to a ROM block
                uint8 idService_u8 = (uint8) NVM_SERVICE_ID_READ_BLOCK;
                uint16 stRequest_u16 = (uint16) NVM_PRV_BLOCK_REQ_READ;

                if ((NVM_BLOCK_DATASET == NvM_Prv_BlockDescriptors_acst[BlockId].BlockManagementType_en) &&
                    (NvM_Prv_idxDataSet_rAMwA_au8[BlockId] >= NvM_Prv_BlockDescriptors_acst[BlockId].nrNvBlocks_u8))
                {
                    // TRACE[NVM354] The block is of type DATASET and the index is pointing to an ROM block -> prepare to queue a RESTORE request
                    // TRACE[NVM376] Reading ROM blocks for blocks of type DATASET is possible
                    idService_u8 = NVM_SERVICE_ID_RESTORE_BLOCK_DEFAULTS;
                    stRequest_u16 = (uint16) NVM_PRV_BLOCK_REQ_RESTORE;
                }

                // TRACE[NVM374] Any assigned NV block is allowed to be read when the block is of type DATASET
                // TRACE[NVM181] Queue this request to allow multiple concurrent single block requests
                // In case of explicit sync the reference to NvM mirror is passed implicitly as parameter to the queueing function
                /* MR12 RULE 11.5 VIOLATION: The actual type of the RAM block varies from block to block (not under control of NvM) */
                if (NvM_Prv_QueueBlockRequest(idService_u8, BlockId, (uint8 *) adrRamBlock_pv) == NVM_PRV_QUEUE_OP_OK)
                {
                    // TRACE[NVM185] Set single block request result to NVM_REQ_PENDING on successful enqueuing
                    NvM_Prv_stRequestResult_rAwAM_au8[BlockId] = NVM_REQ_PENDING;

                    // TRACE[NVM198] Set the status of the permanent RAM block to INVALID before processing starts in case of a READ request
                    // TRACE[NVM227] Set the status of the permanent RAM block to INVALID before processing starts in case of a block of type DATASET and a restore from ROM is to be performed
                    if (adrRamBlock_pv == *NvM_Prv_BlockDescriptors_acst[BlockId].adrRamBlock_ppv)
                    {
                        NvM_Prv_stBlock_rAwAM_au8[BlockId] &= (uint8) ~(NVM_BLOCK_STATE_RAM_VALID);
                    }

                    // Internally signal that this block has been requested to be read or to be restored from ROM if it's of type DATASET and the index points to a ROM block
                    NvM_Prv_stRequests_rAMwAM_au16[BlockId] |= stRequest_u16;

                    stReturn_u8 = E_OK;
                }
                // TRACE[NVM184] In case of a queue overflow, the return value is E_NOT_OK
            }
            else
            {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
                // TRACE[NVM616] Report the DET error NVM_E_PARAM_ADDRESS when no permanent RAM block is configured and a NULL pointer is passed via the parameter NvM_DstPtr
                // TRACE[NVM196] Same as NVM616. It includes the case where explicit synchronization is configured for this block and no NvM mirror exists
                flgDetError_b = TRUE;
                idDetError_u8 = NVM_E_PARAM_ADDRESS;
#endif
            }
        }

        else
        {
#if (NVM_DEV_ERROR_DETECT == STD_ON)
            // TRACE[NVM615] Report the DET error NVM_E_BLOCK_PENDING when NVRAM block identifier is already queued or currently in progress
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
        NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_READ_BLOCK, idDetError_u8);
    }
#endif

    // Return whether this operation was successful
    return stReturn_u8;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"