

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
 * Inline declarations
 **********************************************************************************************************************
 */

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

LOCAL_INLINE void NvM_Prv_MainFunctionJobStart_ExplicitSyncCheck(void);
LOCAL_INLINE void NvM_Prv_MainFunctionJobStart_Execute(void);

#if (NVM_PRV_HAS_RAM_MIRROR == STD_ON)
LOCAL_INLINE void NvM_Prv_MainFunctionJobStart_ExplicitSyncWriteRetry(void);
#endif

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

/*
 **********************************************************************************************************************
 * NvM-private code
 **********************************************************************************************************************
 */

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

void NvM_Prv_MainFunctionJobStart(void)
{
    // Start the job identified by idActiveJob_rMwM_en

    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3055] Invoke block-start callback function if configured
    if ((NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].SingleBlockStartCallback_pfct != NULL_PTR) &&
        (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 == NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16))
    {
        (*NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].SingleBlockStartCallback_pfct)
                (NvM_Prv_Main_st.idActiveService_rAMwM_u8);
    }

    NvM_Prv_MainFunctionJobStart_ExplicitSyncCheck();

    // Determine the next state depending on the job start result
    if (NvM_Prv_Main_st.stActiveJobResult_rMwM_en == MEMIF_JOB_OK)
    {
        // Execute the actual job start
        NvM_Prv_MainFunctionJobStart_Execute();

        // Determine the next state depending on the job start result
        if (NvM_Prv_Main_st.stActiveJobResult_rMwM_en == MEMIF_JOB_PENDING)
        {
            // Polling needed
            NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_POLL_RESULT;
        }
        else
        {
            // Job either failed or successfully finished -> no polling needed
            NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_RESULT_EVAL;
        }
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

/*
 **********************************************************************************************************************
 * Inline code
 **********************************************************************************************************************
 */

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

LOCAL_INLINE void NvM_Prv_MainFunctionJobStart_ExplicitSyncCheck(void)
{
    // Initialize result of the active job (might be revised below)
    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_OK;

    #if (NVM_PRV_HAS_RAM_MIRROR == STD_ON)
    {
        boolean isExplicitSyncUsed_b = FALSE;
        if ( (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].stFlags_u16 &
                (uint16)NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM ) == NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM
           )
        {
            isExplicitSyncUsed_b = TRUE;
        }

        // Check whether the currently active RAM block is the RAM mirror and explicit synchronization is enabled for this block
        if ( (NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 == NvM_Prv_RamMirror_au8) &&
             (isExplicitSyncUsed_b)
            )
        {
            // Check whether a read, write or restore operation shall be started
            // Notes:
            // - Calling NvM_ReadBlock/WriteBlock/RestoreBlockDefaults with RAM address parameter != NULL_PTR
            //   does not trigger the corresponding callback
            // - A usual operation is performed in this case even if the block is configured to use explicit sync
            // - TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2930] No explicit sync callback is triggered for auxiliary
            //   accesses because always a temporary RAM block is used in this case

            if ( (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_RESTORE)    ||
                 (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_WRITE)      ||
                 (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ)
               )
            {
                #if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3049]
                // Only needed if Runtime Block Configuration feature is active
                // In this case RAM mirror length is configured by user and not automatically by BCT
                // => a length missmatch could occurs
                // Check whether the currently NV block length does not exceeds the RAM mirror length
                if ( *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrBlockBytes_pu16 >
                NvM_Prv_RntRamMirrorSize_u32
                    )
                {
                    #if (NVM_DEV_ERROR_DETECT == STD_ON)
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service
                    //                                               causing last DET error
                    NvM_Prv_SetBlockIdCausingLastDetError(NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16);
                    // Calling foreign DET function is done out of the Schm lock
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3049] NV block length greater then explicit RAM mirror size
                    NVM_PRV_REPORT_DET_ERROR(NvM_Prv_Main_st.idActiveService_rAMwM_u8, NVM_E_RAM_MIRROR_SIZE);
                    #endif
                    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
                }
                else
                #endif
                {
                    NvM_Prv_MainFunctionJobStart_ExplicitSyncWriteRetry();
                }
            }

            if (NvM_Prv_Main_st.stActiveJobResult_rMwM_en == MEMIF_JOB_FAILED)
            {
                NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_RESULT_EVAL;
            }
        }
    }
    #endif
}


// ====================================================================================================================

#if (NVM_PRV_HAS_RAM_MIRROR == STD_ON)
LOCAL_INLINE void NvM_Prv_MainFunctionJobStart_ExplicitSyncWriteRetry(void)
{
    // Check again whether a read operation shall be started
    if (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_WRITE)
    {
        // TRACE[NVM514] The NvM mirror is used only by the blocks configured to use explicit synchronization
        // TRACE[NVM515] Call NvMWriteRamBlockToNvM to copy the data from the RAM block to the NvM mirror
        /* MR12 DIR 1.1 VIOLATION: The original pointer is a byte pointer so casting to void pointer can always be done safely */
        if ((*NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].WriteRamBlockToNvm_pfct)(NvM_Prv_RamMirror_au8) == E_OK)
        {
            NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8 = 0; // Reset counter for the next explicit sync operation
        }
        else
        {
            // Explicit synchronization failed
            // -> Increment mirror operations counter
            NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8++;
            // TRACE[NVM579] The maximal number of mirror operation retries is NVM_REPEAT_MIRROR_OPERATIONS
            if(NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8 > NVM_REPEAT_MIRROR_OPERATIONS)
            {
                NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
                NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8 = 0; // Reset counter for the next explicit sync operation
            }
            else
            {
                // TRACE[NVM579] Explicit sync write callback was not successful but did not finally fail
                // -> Retry mirror operation in next invocation of job start
                NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_PENDING;
            }
        }
    }
}
#endif

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionJobStart_Execute(void)
{
    // Execute the actual job start

    // Set the MemIf block ID with which the MemIf service will be called
    uint16 idBlockMemIf_u16 = NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idBlockMemIf_u16;

    // Initialize result of the active job (might be revised below)
    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_PENDING;

    // TRACE[NVM338] The job of NvM_WriteBlock writes to the NV block which is selected by the data index when the block is of type DATASET
    // TRACE[NVM339] Same as NVM338, applied to NvM_WriteAll
    // TRACE[NVM340] The job of NvM_ReadBlock reads only the NV block selected by the data index for a block of type DATASET
    // (Fee/Ea block-ID for an NV-block of an NvM-block of type DATASET) = (Fee/Ea block-ID) + (NV-index)
    if (NVM_BLOCK_DATASET == NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en)
    {
        idBlockMemIf_u16 += NvM_Prv_Main_st.idxActiveDataset_rMwM_u8;
    }

    // Start the MemIf job identified by NvM_Prv_Main_st.idActiveJob_rMwM_en
    switch (NvM_Prv_Main_st.idActiveJob_rMwM_en)
    {
        case NVM_PRV_JOB_ID_VALIDATE:
        {
            // Note: Setting the job result to MEMIF_JOB_OK is done to simplify implementation.
            //       MemIf is not required for an auto validation operation.
            // The actual auto validation operation is done during result evaluation
            NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_OK;
        }
        break;
        case NVM_PRV_JOB_ID_READ:
        {
            // Start a MemIf_Read job
            if ( (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].stFlags_u16 &
                    (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_MIGRATION) == NVM_PRV_BLOCK_FLAG_SELECT_FOR_MIGRATION
               )
            {
                // Reads all blocks where Migration or variable block length feature is active
                // Migration feature can be active without variable block length feature
                // Variable block length feature neeads activation of Migration feature
                if (E_OK != MemIf_Rb_VarLenRead(NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8,
                                   idBlockMemIf_u16,
                                   0,
                                   NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8,
                                   *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrBlockBytes_pu16))
                {
                    // Starting the read job failed
                    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
                }
            }
            else
            {
                // Reads a normal block without Migration or variable block length feature active
                if (E_OK != MemIf_Read(NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8,
                                   idBlockMemIf_u16,
                                   0,
                                   NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8,
                                   *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrBlockBytes_pu16))
                {
                    // Starting the read job failed
                    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
                }
            }
            break;
        }

        case NVM_PRV_JOB_ID_WRITE:
        {
            // Start a MemIf_Write job
            if ( (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].stFlags_u16 &
                    (uint16)NVM_PRV_BLOCK_FLAG_USE_VARIABLE_BLOCK_LENGTH) == NVM_PRV_BLOCK_FLAG_USE_VARIABLE_BLOCK_LENGTH
               )
            {
                // Write blocks where the block length is variable (defined in NvMRbNvBlockLengthString)
                // Migration feature must be active here
                if (E_OK != MemIf_Rb_VarLenWrite(NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8,
                                                 idBlockMemIf_u16,
                                                 NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8,
                                                 *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrBlockBytes_pu16))
                {
                    // Starting the write job failed
                    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
                }
            }
            else
            {
                // Write blocks where the length is defined as numeric literal in NvMNvBlockLength
                // Migration feature could be active here
                if (E_OK != MemIf_Write(NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8,
                                        idBlockMemIf_u16,
                                        NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8))
                {
                    // Starting the write job failed
                    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
                }
            }

#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)
            NvM_Prv_IncreaseWriteCounters(NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16,
                                          *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrBlockBytes_pu16);
#endif
            break;
        }

        case NVM_PRV_JOB_ID_INVALIDATE:
        case NVM_PRV_JOB_ID_ERASE:
        {
            // Start a MemIf_InvalidateBlock job
            if (E_OK != MemIf_InvalidateBlock(NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8, idBlockMemIf_u16))
            {
                // Starting the invalidate job failed
                NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
            }
            break;
        }

        case NVM_PRV_JOB_ID_RESTORE:
        {
            // TRACE[NVM392] Restore job is done without any MemIf interaction
            // TRACE[NVM392] Leave the NV block untouched
            // Determine the source of the block defaults
            if (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].adrRomBlock_pcv != NULL_PTR)
            {
                // A ROM block is configured for this block
                // TRACE[NVM267] Fill the block data buffer with ROM block data
                uint8 *adrDest_pu8 = NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8;
                /* MR12 RULE 11.5 VIOLATION: The actual type of the ROM block varies from block to block (not under control of NvM) */
                const uint8 *adrSource_pcu8 = (const uint8 *) NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].adrRomBlock_pcv;
                uint16 nrRemainingBlockBytes_u16 = *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrBlockBytes_pu16;

                if (NVM_BLOCK_DATASET == NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en)
                {
                    // This DATASET block has its dataset-index pointing to a ROM block
                    // (otherwise it wouldn't have been queued by NvM_RestoreBlockDefaults or by NvM_ReadBlock)
                    // -> Move the source pointer to the start address of the indexed ROM block
                    adrSource_pcu8 += *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrBlockBytes_pu16 *
                                      (NvM_Prv_idxDataSet_rAMwA_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] -
                                       NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrNvBlocks_u8);
                }

                // Perform the restore job by copying data from the ROM-block to the RAM-block
                while (nrRemainingBlockBytes_u16 > 0)
                {
                    *adrDest_pu8 = *adrSource_pcu8;
                    adrDest_pu8++;
                    adrSource_pcu8++;
                    nrRemainingBlockBytes_u16--;
                }
            }

            // Note: Setting the job result to MEMIF_JOB_OK is done to simplify implementation; MemIf is not required for a restore operation
            NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_OK;
            break;
        }

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
        case NVM_PRV_JOB_ID_MAINTAIN:
        {
            // Start a MemIf_Rb_BlockMaintenance job
            if (E_OK != MemIf_Rb_BlockMaintenance(NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8,
                                                  idBlockMemIf_u16))
            {
                // Starting the read job failed
                NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
            }
            break;
        }
#endif

        default:
        {
            // This function may only be called with a known NvM_Prv_Main_st.idActiveJob_rMwM_en
            // (we should actually never get into this branch; it's just there for robustness)
            NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
            NvM_Prv_SetBlockIdCausingLastDetError(NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16);
            NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_MAIN_FUNCTION, NVM_E_PRV_JOB_ID);
            break;
        }
    }
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
