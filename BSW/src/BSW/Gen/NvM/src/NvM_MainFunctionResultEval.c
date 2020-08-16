

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
 * Inline declarations
 **********************************************************************************************************************
 */

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

LOCAL_INLINE boolean               NvM_Prv_MainFunctionResultEval_ImplicitRecoveryFromRom(void);
LOCAL_INLINE boolean               NvM_Prv_MainFunctionResultEval_InvalidateNextDatasetBlock(void);
#if (NVM_PRV_HAS_RAM_MIRROR == STD_ON)
LOCAL_INLINE boolean               NvM_Prv_MainFunctionResultEval_ExplicitSyncReadRetry(Std_ReturnType *stExplicitSyncResult_pu8);
#endif
LOCAL_INLINE boolean               NvM_Prv_MainFunctionResultEval_FirstInitWriteAfterRestore(void);
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_InitBlockCallback(Std_ReturnType stExplicitSyncResult_u8);
LOCAL_INLINE NvM_RequestResultType NvM_Prv_MainFunctionResultEval_CalculateRequestResult(MemIf_JobResultType JobResult_en);
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_CalculateAuxMigrationResult(void);
LOCAL_INLINE uint8                 NvM_Prv_MainFunctionResultEval_GetProductionErrors(MemIf_JobResultType JobResult_en);
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_CalculateRamBlockStatus(MemIf_JobResultType JobResult_en,
                                                                                          uint8 *stBlock_pu8);
#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_SpecialConfigIdActions(MemIf_JobResultType JobResult_en,
                                                                                         boolean *initBlocksAtLayoutChange_pb);
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_TriggerWriteConfigId(uint8 *stBlock_pu8);
#endif
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_FinalBlockCallbacks(NvM_RequestResultType stRequestResult_u8,
                                                                                      NvM_BlockIdType idActiveBlock_u16,
                                                                                      uint8 idActiveService_u8,
                                                                                      boolean isAuxServiceActive);
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_TriggerInitAtLayoutChange(boolean initBlocksAtLayoutChange_b,
                                                                                            NvM_RequestResultType stRequestResult_u8);
#endif
LOCAL_INLINE void                  NvM_Prv_MainFunctionResultEval_ResetMainStates(void);

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

/*
 **********************************************************************************************************************
 * NvM-private code
 **********************************************************************************************************************
 */

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

void NvM_Prv_MainFunctionResultEval(void)
{
    // Evaluate the result of the job identified by idActiveJob_rMwM_en

    // Local variables
    Std_ReturnType stExplicitSyncReadResult = E_OK; // Result of the explicit sync read callback (if called at all)

    // Check whether implicit recovery from ROM is required -> NVM_PRV_ACTIVITY_JOB_START if yes
    // Check whether the next DATASET block needs to be invalidated -> NVM_PRV_ACTIVITY_JOB_START if yes
    // Check whether an explicit sync read callback shall be called and needs a retry
    //   (needs to come before WriteAfterRestore and also before InitBlockCallback)
    // Check whether a restore job from FirstInitAll succeeded and shall be turned into a write job -> NVM_PRV_ACTIVITY_JOB_START if yes
    /* MR12 RULE 13.5 VIOLATION: The side effects of the function calls inside the condition expression are intended */
    if (!NvM_Prv_MainFunctionResultEval_ImplicitRecoveryFromRom() &&
        !NvM_Prv_MainFunctionResultEval_InvalidateNextDatasetBlock() &&
#if (NVM_PRV_HAS_RAM_MIRROR == STD_ON)
        !NvM_Prv_MainFunctionResultEval_ExplicitSyncReadRetry(&stExplicitSyncReadResult) &&
#endif
        !NvM_Prv_MainFunctionResultEval_FirstInitWriteAfterRestore())
    {
        boolean isResultEvaluated_b = FALSE;
        uint8 idActiveService_u8 = NvM_Prv_Main_st.idActiveService_rAMwM_u8;
        NvM_BlockIdType idActiveBlock_u16 = NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16;
        boolean isAuxServiceActive =
                NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 != NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16;
        // Concurrency notes:
        // - Singleblock APIs, block is still active:
        //   - NvM_Prv_stRequestResult_rAwAM_au8 cannot be written
        //   - NvM_Rb_stBlockErrors_au8 CAN be written -> changes to it must be done under lock
        // - Multiblock APIs, isMultiBlockActive_rAMwM_b is still set:
        //   - NvM_Prv_stRequestResult_rAwAM_au8 CAN be written -> changes to it must be done under lock
        //   - NvM_Rb_stBlockErrors_au8 is not written at all
        NvM_RequestResultType stRequestResult_u8;
        uint8 stProductionErrors_u8;
        boolean initBlocksAtLayoutChange_b = FALSE;

        // Invoke the init block callback if applicable
        NvM_Prv_MainFunctionResultEval_InitBlockCallback(stExplicitSyncReadResult);

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2863] The request result is not evaluated nor set in case of a maintenance job
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2871] The single block callback of a redundant block is not invoked when its maintenance job finishes
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2872] The observer callback of a redundant block is not invoked when its maintenance job finishes
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2874] The multiblock callback provides the WriteAll operation result, not the maintenance operation result
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2876] The BswM notification provides the WriteAll operation result, not the maintenance operation result
        if (NvM_Prv_Main_st.idActiveJob_rMwM_en != NVM_PRV_JOB_ID_MAINTAIN)
#endif
        {
            // Get the MemIf result of the current job
            MemIf_JobResultType JobResult_en = NvM_Prv_Main_st.stActiveJobResult_rMwM_en;

#if (NVM_DEV_ERROR_DETECT == STD_ON)
            // We rely heavily on the fact that we know really all possible job results
            // -> check this assumption if development error detection is enabled
            if ((JobResult_en != MEMIF_JOB_OK) &&
                (JobResult_en != MEMIF_JOB_FAILED) &&
                (JobResult_en != MEMIF_JOB_CANCELED) &&
                (JobResult_en != MEMIF_BLOCK_INVALID) &&
                (JobResult_en != MEMIF_BLOCK_INCONSISTENT))
            {
                stRequestResult_u8 = NVM_REQ_NOT_OK;
                stProductionErrors_u8 = 0;
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
                NvM_Prv_SetBlockIdCausingLastDetError(NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16);
                NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_MAIN_FUNCTION, NVM_E_MEMIF_JOB_RESULT);
            }
            else
#endif
            {
                // Determine the request result value
                stRequestResult_u8 = NvM_Prv_MainFunctionResultEval_CalculateRequestResult(JobResult_en);

                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3027] Calculate migration result
                NvM_Prv_MainFunctionResultEval_CalculateAuxMigrationResult();

                // Determine the production errors to be triggered by this job
                stProductionErrors_u8 = NvM_Prv_MainFunctionResultEval_GetProductionErrors(JobResult_en);

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
                // Finally perform special actions related to the configuration ID block
                NvM_Prv_MainFunctionResultEval_SpecialConfigIdActions(JobResult_en, &initBlocksAtLayoutChange_b);
#else
                (void)initBlocksAtLayoutChange_b;
#endif
            }

            isResultEvaluated_b = TRUE;

            // TRACE[NVM128] Maintain RAM block status
            {
                uint8 stBlock_u8 = NvM_Prv_stBlock_rAwAM_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16];
                NvM_Prv_MainFunctionResultEval_CalculateRamBlockStatus(JobResult_en, &stBlock_u8);

                // Trigger the writing of the config ID block in WriteAll if applicable
#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
                NvM_Prv_MainFunctionResultEval_TriggerWriteConfigId(&stBlock_u8);
#endif
                // Write back the locally cached RAM block status to the admin block
                // Concurrency note: since the current block is still marked as active, singleblock APIs cannot modify
                //                   the RAM block status (and multiblock APIs only read it)
                NvM_Prv_stBlock_rAwAM_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] = stBlock_u8;
            }

            // Signal the initialization of blocks at layout change
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
            NvM_Prv_MainFunctionResultEval_TriggerInitAtLayoutChange(initBlocksAtLayoutChange_b, stRequestResult_u8);
#endif

            // Internally signal that this block has finished the operation, go back to arbitration
            if (!NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b)
            {
                // Single block operation finished
                // -> internally signal that the service has been finished
                NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_SERVICE_ID_INIT;
            }
        }

        // Set scheduling lock
        SchM_Enter_NvM_Main();

        // Part to be done after result evaluation WITHIN scheduling lock
        if (isResultEvaluated_b)
        {
            // Set global variables from local copies to update results/states for the user
            // TRACE[NVM175] Indicate the request result to the user
            NvM_Prv_stRequestResult_rAwAM_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16]  = stRequestResult_u8;
            NvM_Rb_stBlockErrors_au8[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16]             |= stProductionErrors_u8;
            NvM_Rb_stBlockErrors_au8[NVM_PRV_MULTI_BLOCK]                                   |= stProductionErrors_u8;
        }

        // Reset the states of NvM's main state machine because the current job is now completely finished
        NvM_Prv_MainFunctionResultEval_ResetMainStates();

        // Reset scheduling lock
        SchM_Exit_NvM_Main();

        // Part to be done after result evaluation WITHOUT scheduling lock
        if (isResultEvaluated_b)
        {
            // Invoke observer and singleblock callbacks if applicable
            NvM_Prv_MainFunctionResultEval_FinalBlockCallbacks(stRequestResult_u8,
                                                               idActiveBlock_u16,
                                                               idActiveService_u8,
                                                               isAuxServiceActive);
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

LOCAL_INLINE boolean NvM_Prv_MainFunctionResultEval_ImplicitRecoveryFromRom(void)
{
    // Check whether a read job for an NvM block having a ROM block did not finish successfully
    // -> if so, turn the read job into a restore job and start it ("implicit recovery")
    // Note: Implicit recovery from init callback is not performed here
    // Note: As opposed to NVM389, implicit recovery is (currently?) not supported for DATASET blocks
    if ((NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ) &&
        (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].adrRomBlock_pcv) &&
        (NvM_Prv_Main_st.stActiveJobResult_rMwM_en != MEMIF_JOB_OK) &&
        (NvM_Prv_Main_st.stActiveJobResult_rMwM_en != MEMIF_BLOCK_INVALID) &&
        (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en != NVM_BLOCK_DATASET))
    {
        // TRACE[NVM389] Recover an unsuccessful read operation by performing a Restore operation for all NvM block types
        // TRACE[NVM390] Same as NVM389 but for redundant NvM blocks
        // TRACE[NVM171] Provide implicit recovery to restore data from ROM to RAM if read data is found inconsistent
        // TRACE[NVM388] Same as NVM171 in case of NvM_ReadAll
        // TRACE[NVM172] The NV block is not modified during implicit recovery
        // TRACE[NVM657] Load default data if the read request fails in the underlying layers by doing the same actions as a restore operation
        // TRACE[NVM679] Same as NVM657 applied to NvM_ReadAll
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_RESTORE;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
    }

    // Return whether this function started implicit recovery
    return (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START);
}

// ====================================================================================================================

LOCAL_INLINE boolean NvM_Prv_MainFunctionResultEval_InvalidateNextDatasetBlock(void)
{
    // Check whether the next DATASET block needs to be invalidated
    // -> if so, advance the current dataset index to the next DATASET instance and start another invalidation
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2850] Invalidate all the NV blocks of an NvM block of type DATASET which is selected for FirstInitAll
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2852] Remove all the NV blocks of a non-resistant NvM block of type DATASET during the removal phase
    if (((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_RB_FIRST_INIT_ALL) || (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_RB_REMOVE_NON_RESISTANT)) &&
        (NVM_BLOCK_DATASET == NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en) &&
        (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_INVALIDATE) &&
        (NvM_Prv_Main_st.stActiveJobResult_rMwM_en == MEMIF_JOB_OK) &&
        (NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 < (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].nrNvBlocks_u8 - 1)))
    {
        // The next NV block of this block of type DATASET needs to be invalidated during FirstInitAll or removal phase
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8++;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
    }

    // Return whether this function started the next invalidation
    return (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START);
}

// ====================================================================================================================

#if (NVM_PRV_HAS_RAM_MIRROR == STD_ON)

LOCAL_INLINE boolean NvM_Prv_MainFunctionResultEval_ExplicitSyncReadRetry(Std_ReturnType *stExplicitSyncResult_pu8)
{
    // Check whether an explicit sync read callback shall be called and needs a retry

    // Local variables
    boolean isRetryNeeded_b = FALSE;

    // If explicit synchronization is enabled for this block, the currently active RAM block is the RAM mirror,
    // and a read or restore operation succeeded, then trigger the read callback
    // Notes:
    // - Calling NvM_ReadBlock/RestoreBlockDefaults with RAM address parameter != NULL_PTR does not trigger the explicit read callback
    // - A usual Read/Restore operation is performed in this case even if the block is configured to use explicit sync
    // - TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2930] No explicit sync read callback is triggered for auxiliary read
    //   accesses because always a temporary RAM block is used in this case
    *stExplicitSyncResult_pu8 = E_OK;
    if (((NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].stFlags_u16 &
          (uint16)NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM) != 0u) &&
        (NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 == NvM_Prv_RamMirror_au8) &&
        (NvM_Prv_Main_st.stActiveJobResult_rMwM_en == MEMIF_JOB_OK))
    {
        if ((NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ) ||
            ((NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_RESTORE) && (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].adrRomBlock_pcv)))
        {
            // TRACE[NVM514] The NvM mirror is used only by the blocks configured to use explicit synchronization
            // TRACE[NVM516] Call NvMReadRamBlockFromNvM to copy the data from the NvM mirror to the RAM block
            /* MR12 DIR 1.1 VIOLATION: The original pointer is a byte pointer so casting to void pointer can always be done safely */
            *stExplicitSyncResult_pu8 = (*NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].ReadRamBlockFromNvm_pfct)(NvM_Prv_RamMirror_au8);
            if (*stExplicitSyncResult_pu8 == E_OK)
            {
                // Explicit synchronization successful
                // -> Reset counter for the next explicit sync operation
                NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8 = 0;
            }
            else
            {
                // Explicit synchronization failed
                // -> Increment mirror operations counter
                NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8++;
                // TRACE[NVM517] The maximal number of mirror operation retries is NVM_REPEAT_MIRROR_OPERATIONS
                if (NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8 > NVM_REPEAT_MIRROR_OPERATIONS)
                {
                    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_FAILED;
                    NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8 = 0; // Reset counter for the next explicit sync operation
                }
                else
                {
                    // TRACE[NVM517] Explicit sync read callback was not successful but did not finally fail
                    // -> Retry mirror operation in next invocation of result evaluation
                    isRetryNeeded_b = TRUE;
                }
            }
        }
    }

    // Return whether this function needs a retry of explicit sync read callback invocation
    return isRetryNeeded_b;
}

#endif

// ====================================================================================================================

LOCAL_INLINE boolean NvM_Prv_MainFunctionResultEval_FirstInitWriteAfterRestore(void)
{
    // Check whether a restore job from FirstInitAll succeeded and shall be turned into a write job
    if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_RB_FIRST_INIT_ALL) &&
        (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_RESTORE))
    {
        // Check if the restore job succeeded, which is the case if
        // - the copy operation from ROM to RAM was successful or
        // - the NvM block has no ROM block
        // Notes:
        // - A finally failed explicit sync read callback sets the job result to MEMIF_JOB_FAILED,
        //   so we neither trigger an init block callback nor a write job in this case
        // - The init block callback doesn't need to be prohibited for jobs triggered by an auxiliary user here
        //   because we only come here if the current service is FirstInitAll
        if (NvM_Prv_Main_st.stActiveJobResult_rMwM_en == MEMIF_JOB_OK)
        {
            if (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].InitBlockCallback_pfct != NULL_PTR)
            {
                (*NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].InitBlockCallback_pfct)();
            }

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2834] If this restore job was part of a first initialization, trigger a write job
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_WRITE;
            NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
        }

        // Note: In case where the explicit sync read callback did not succeed and the block has no init callback, no initialization is possible
    }

    // Return whether this function started a write job
    return (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START);
}

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_InitBlockCallback(Std_ReturnType stExplicitSyncResult_u8)
{
    // Invoke the init block callback if applicable

    // The following conditions apply for init block callback invocation (all conditions must be TRUE):
    // - There is an init block callback configured for the current block
    // - If the preceding recovery operation involved an explicit sync read callback, this shall not have finally failed
    // - TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2930] The current job has not been triggered by an auxiliary user
    // (
    //   - TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2757] The current job is an explicit recovery   OR
    //   - TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2757] The current job is an implicit recovery
    // )
    // Notes:
    // - TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2896] An implicit recovery fom the init block callback is also
    //   performed if the block has no ROM block
    // - As opposed to NVM389, implicit recovery and therefore also init block callback invocation is (currently?)
    //   not supported for DATASET blocks, hence we explicitly exclude this case here for implicit recovery without
    //   a ROM block (implicit recovery with ROM block is excluded for DATASET blocks inside the
    //   NvM_Prv_MainFunctionResultEval_ImplicitRecoveryFromRom function)
    if ((NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].InitBlockCallback_pfct != NULL_PTR) &&
        (stExplicitSyncResult_u8 == E_OK) &&
        (NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 == NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16) &&
        (
         (
          // Explicit recovery or implicit recovery with ROM block:
          NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_RESTORE
         ) ||
         (
          // Implicit recovery without a ROM block:
          (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ) &&
          (NvM_Prv_Main_st.stActiveJobResult_rMwM_en != MEMIF_JOB_OK) &&
          (NvM_Prv_Main_st.stActiveJobResult_rMwM_en != MEMIF_BLOCK_INVALID) &&
          (NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en != NVM_BLOCK_DATASET)
         )
        )
       )
    {
        // Invoke the init block callback
        (*NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].InitBlockCallback_pfct)();

        // Set the active job to NVM_PRV_JOB_ID_RESTORE and the the job result to MEMIF_JOB_OK
        // This is needed in result/state maintenance to set the request result to NVM_REQ_RESTORED_FROM_ROM
        // and the RAM block state to VALID/CHANGED
        NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_OK;
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_RESTORE;
    }
}

// ====================================================================================================================

LOCAL_INLINE NvM_RequestResultType NvM_Prv_MainFunctionResultEval_CalculateRequestResult(MemIf_JobResultType JobResult_en)
{
    // Determine the request result value

    // Local variables
    NvM_RequestResultType stRequestResult_u8 = 0;

    // TRACE[NVM396] Result handling is identically for multiblock and single block operations
    // Note: This is achieved by only taking the active job ID as the basis for all decisions related
    //       to single blocks, not the active service ID
    if (JobResult_en == MEMIF_JOB_OK)
    {
        // TRACE[NVM270] Set request result to NVM_REQ_OK
        // TRACE[NVM290] Same as NVM270, applied to NvM_ReadAll
        // TRACE[NVM206] Same as NVM270, applied to NvM_ReadBlock
        // TRACE[NVM670] The request result of config ID block is set to REQ_OK by ReadAll in case of config ID match
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2836] NVM_REQ_OK is one of the two possible request results of first init
        stRequestResult_u8 = NVM_REQ_OK;

        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2878] Set the request result to NVM_REQ_RESTORED_FROM_ROM
        //                                               if an implicit recovery occured during the execution
        //                                               of a Read operation
        // Note: In contrast to an implicit restore (which can occur in case of read operations),
        //       explicit restore shall set the request result to NVM_REQ_OK when the restore operation is successful
        if (((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_BLOCK) ||
             (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL))
            &&
            (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_RESTORE))
        {
            stRequestResult_u8 = NVM_REQ_RESTORED_FROM_ROM;
        }

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
        if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL) &&
            (NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 == NVM_RB_CONFIG_ID_BLOCK))
        {
            // Config ID block successfully read
            // TRACE[NVM246] Check whether the stored config ID differs from the current layout's config ID
            // TRACE[NVM073] Comparing stored config ID and compiled config ID is the first step in ReadAll
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2886] Same as NVM073 applied to "init at layout change" feature
            if (NvM_Prv_idConfigStored_rMwM_u16 != NVM_COMPILED_CONFIG_ID)
            {
                // TRACE[NVM307] ReadAll sets the request result of config ID block to REQ_NOT_OK in case of config ID mismatch
                stRequestResult_u8 = NVM_REQ_NOT_OK;
            }
        }
#endif

#if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)
        if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_RB_REMOVE_NON_RESISTANT) &&
            (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_INVALIDATE) &&
            (NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 >= NVM_RB_FIRST_USER_BLOCK))
        {
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2789] Set request result to the same value as if a successful read would have been performed
            stRequestResult_u8 = NVM_REQ_NV_INVALIDATED;
        }
#endif
    }
    else
    {
        if (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ)
        {
            if (JobResult_en == MEMIF_BLOCK_INVALID)
            {
                // TRACE[NVM342] Set request result to NVM_REQ_NV_INVALIDATED (applies to NvM_ReadAll)
                // TRACE[NVM341] Same as NVM342, applied to NvM_ReadBlock
                // TRACE[NVM651] The job of NvM_ReadBlock does not load the RAM block of an NvM block of type DATASET with data from the media if the selected NV block is found invalidated.
                // TRACE[NVM672] The Config ID request result is set to REQ_NV_INVALIDATED by ReadAll if this block is found invalidated on the medium
                stRequestResult_u8 = NVM_REQ_NV_INVALIDATED;
            }
            else if (JobResult_en == MEMIF_BLOCK_INCONSISTENT)
            {
                // TRACE[NVM360] Set request result to NVM_REQ_INTEGRITY_FAILED (applies to NvM_ReadAll)
                // TRACE[NVM358] Same as NVM360, applied to NvM_ReadBlock
                // TRACE[NVM651] The job of NvM_ReadBlock does not load the RAM block of an NvM block of type DATASET with inconsistent data from the selected NV block.
                stRequestResult_u8 = NVM_REQ_INTEGRITY_FAILED;

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
                if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL) &&
                    (NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 == NVM_RB_CONFIG_ID_BLOCK))
                {
                    // Config ID block is empty or corrupted
                    // TRACE[NVM672] ReadAll sets the Config ID request result to REQ_NV_INVALIDATED if this block is empty or corrupted
                    stRequestResult_u8 = NVM_REQ_NV_INVALIDATED;
                }
#endif
            }
            else if (JobResult_en == MEMIF_JOB_FAILED)
            {
                // TRACE[NVM361] Set request result to NVM_REQ_NOT_OK (applies to NvM_ReadAll)
                // TRACE[NVM359] Same as NVM361, applied to NvM_ReadBlock
                stRequestResult_u8 = NVM_REQ_NOT_OK;

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
                if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL) &&
                    (NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 == NVM_RB_CONFIG_ID_BLOCK))
                {
                    // Config ID block could not be read due to an error detected by one of the lower SW layers
                    // TRACE[NVM671] ReadAll sets the Config ID request result to REQ_INTEGRITY_FAILED if an error occured in the lower layers when reading this block
                    stRequestResult_u8 = NVM_REQ_INTEGRITY_FAILED;
                }
#endif
            }
            else // MEMIF_JOB_CANCELED
            {
                // Set request result to NVM_REQ_NOT_OK
                stRequestResult_u8 = NVM_REQ_NOT_OK;
            }
        }
        else
        {
            // TRACE[NVM271] Set request result to NVM_REQ_NOT_OK (applies to NvM_EraseNvBlock)
            // TRACE[NVM275] Same as NVM271, applied to NvM_InvalidateNvBlock
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2836] NVM_REQ_NOT_OK is one of the two possible request results of first init
            // We apply these rules also to write and restore operations
            stRequestResult_u8 = NVM_REQ_NOT_OK;
        }
    }

    // TRACE[NVM395] Maintain overall result of the multiblock operation
    if (NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b && ((JobResult_en == MEMIF_BLOCK_INCONSISTENT) || (JobResult_en == MEMIF_JOB_FAILED)))
    {
        // TRACE[NVM301] Set final multiblock result to NVM_REQ_NOT_OK (applies to NvM_ReadAll)
        // TRACE[NVM318] Same as NVM301, applied to NvM_WriteAll
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2836] NVM_REQ_NOT_OK is one of the two possible request results of first init
        NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8 = NVM_REQ_NOT_OK;
    }

    // Return the calculated request result
    return stRequestResult_u8;
}

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_CalculateAuxMigrationResult(void)
{
	// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3027] Calculate aux migration result
    MemIf_Rb_MigrationResult_ten migrationResult_en;

    // Check if a aux read job is active
    if (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_RB_AUX_READ_BLOCK)
    {
        migrationResult_en = MemIf_Rb_GetMigrationResult(
                NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idxDevice_u8,
                NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].idBlockMemIf_u16
                );

        switch(migrationResult_en)
        {
            case MEMIF_RB_MIGRATION_RESULT_INIT_E:
                NvM_Prv_AuxMigrationResult = NVM_RB_MIGRATION_RESULT_INIT_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_NOT_NECESSARY_E:
                NvM_Prv_AuxMigrationResult = NVM_RB_MIGRATION_RESULT_NOT_NECESSARY_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E:
                NvM_Prv_AuxMigrationResult = NVM_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E:
                NvM_Prv_AuxMigrationResult = NVM_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_NOT_DONE_E:
                NvM_Prv_AuxMigrationResult = NVM_RB_MIGRATION_RESULT_NOT_DONE_E;
            break;

            case MEMIF_RB_MIGRATION_RESULT_DEACTIVATED_E:
                NvM_Prv_AuxMigrationResult = NVM_RB_MIGRATION_RESULT_DEACTIVATED_E;
            break;

            default:
                /* MR12 RULE 16.4 VIOLATION: Default can not be reached and has no effect here */
            break;
        }
    }
}

// ====================================================================================================================

LOCAL_INLINE uint8 NvM_Prv_MainFunctionResultEval_GetProductionErrors(MemIf_JobResultType JobResult_en)
{
    // Determine the production errors to be triggered by this job

    // Local variables
    uint8 stProductionErrors_u8 = 0;

    // TRACE[NVM305] Error reporting to production error also applies to the block holding the config ID
    // TRACE[NVM302] Error reporting to production error always applies in this case regardless of CRC configuration
    if (JobResult_en == MEMIF_JOB_OK)
    {
        // No error occured -> no production error to be reported
    }
    else
    {
        if (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ)
        {
            if (JobResult_en == MEMIF_BLOCK_INVALID)
            {
                // TRACE[NVM676] Don't report a production error if MemIf reports MEMIF_BLOCK_INVALID (applies to NvM_ReadAll)
                // TRACE[NVM652] Same as NVM676, applied to NvM_ReadBlock
            }
            else if (JobResult_en == MEMIF_BLOCK_INCONSISTENT)
            {
#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
                if ((NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 == NVM_RB_CONFIG_ID_BLOCK) && (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL))
                {
                    // TRACE[NVM306] ReadAll does not report a production error if the configuration Id block is empty
                }
                else
#endif
                {
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2820] Set the block error flag indicating an integrity-failed error
                    stProductionErrors_u8 |= NVM_E_INTEGRITY_FAILED;
                }
            }
            else if (JobResult_en == MEMIF_JOB_FAILED)
            {
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2816] Set the block status flag indicating a request-failed error
                stProductionErrors_u8 |= NVM_E_REQ_FAILED;
            }
            else // MEMIF_JOB_CANCELED
            {
                // Current job canceled -> no production error to be reported
            }
        }
        else
        {
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2816] Set the block status flag indicating a request-failed error
            stProductionErrors_u8 |= NVM_E_REQ_FAILED;
        }
    }

    // Return the collected production errors related to the current job
    return stProductionErrors_u8;
}

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_CalculateRamBlockStatus(MemIf_JobResultType JobResult_en, uint8 *stBlock_pu8)
{
    // TRACE[NVM128] Maintain RAM block status (only if permanent RAM block is used)
    // Also do write once handling here because the conditions are very similar to RAM block status maintenance
    if (JobResult_en == MEMIF_JOB_OK)
    {
        if ((NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ) || (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_WRITE))
        {
            // TRACE[NVM251] Set the RAM block state to VALID/UNCHANGED if reading succeeded (applies to NvM_ReadAll)
            // TRACE[NVM472] Set the RAM block state to VALID/UNCHANGED if writing succeeded
            // TRACE[NVM200] Same as NVM472, applied to NvM_ReadBlock
            // TRACE[NVM416] NvM_EraseNvBlock leaves the contents of the RAM block untouched
            // TRACE[NVM422] NvM_InvalidateNvBlock leaves the contents of the RAM block untouched
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2837] Set the RAM block state to VALID/UNCHANGED in case of first init if write job was involved
            // Note: In case of explicit synchronization NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 points to the NvM mirror
            if (NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 == *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].adrRamBlock_ppv)
            {
                *stBlock_pu8 &= (uint8) ~NVM_BLOCK_STATE_RAM_CHANGED;
                *stBlock_pu8 |= NVM_BLOCK_STATE_RAM_VALID;
            }
            // TRACE[NVM680] Invalid RAM blocks remain invalid if no ROM replacement values exist (applies to NvM_ReadAll)
            // TRACE[NVM658] Same as NVM680, applied to NvM_ReadBlock

            // TRACE[NVM314] Enable write protection if the block is configured as write once (applies to NvM_ReadAll)
            // TRACE[NVM316] Same as NVM314, applied to NvM_ReadBlock
            // TRACE[NVM329] Same as NVM314, applied to NvM_WriteAll
            // TRACE[NVM328] Same as NVM314, applied to NvM_WriteBlock
            if ((NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].stFlags_u16 &
                 (uint16)NVM_PRV_BLOCK_FLAG_WRITE_ONCE) != 0u)
            {
                *stBlock_pu8 |= NVM_BLOCK_STATE_WRITE_PROT;
            }
        }
        else if (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_RESTORE)
        {
            // TRACE[NVM228] Set the RAM block state to VALID/CHANGED if the block data is the permanent RAM block of this block
            // TRACE[NVM366] Same as NVM228 applied in case of implicit recovery of data from ROM when read operation fails
            // TRACE[NVM367] Same as NVM366 applied in case of NvM_ReadAll
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2837] In case of first init, we don't get here after the restore part (which is OK)
            if (NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 == *NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].adrRamBlock_ppv)
            {
                *stBlock_pu8 |= NVM_BLOCK_STATE_RAM_VALID_CHANGED;
            }
        }
        else if (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_VALIDATE)
        {
            // TRACE[NVM856] Set RAM block status to VALID/CHANGED
            *stBlock_pu8 |= NVM_BLOCK_STATE_RAM_CHANGED;
        }
        else
        {
            // Setting the RAM block state does not apply for other jobs
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2838] This is particularly true for first init not involving write or restore
        }
    }
}

// ====================================================================================================================

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))

LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_SpecialConfigIdActions(MemIf_JobResultType JobResult_en, boolean *initBlocksAtLayoutChange_pb)
{
    // Perform all special actions related to the configuration ID block
    if (NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 == NVM_RB_CONFIG_ID_BLOCK)
    {
        if (JobResult_en == MEMIF_JOB_OK)
        {
            if (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ)
            {
                // Config ID block successfully read
                // TRACE[NVM246] Check whether the stored config ID differs from the current layout's config ID
                // TRACE[NVM073] Comparing stored config ID and compiled config ID is the first step in ReadAll
                // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2886] Same as NVM073 applied to "init at layout change" feature
                if (NvM_Prv_idConfigStored_rMwM_u16 == NVM_COMPILED_CONFIG_ID)
                {
                    // Indicate that the config ID did not change
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
                    NvM_Prv_isConfigIdChanged_rMwM_b = FALSE;
#endif
                    // Indicate that the blocks do not need to be initialized
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
                    *initBlocksAtLayoutChange_pb = FALSE;
#else
                    // Parameter initBlocksAtLayoutChange_pb unused if NVM_RB_INIT_AT_LAYOUT_CHANGE is disabled
                    (void) initBlocksAtLayoutChange_pb;
#endif
                    // Indicate that the Config ID block is not to be written
                    NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_DO_NOT_WRITE_CONFIG_ID;

                    // TRACE[NVM313] Don't write the config ID back to the NV block in case of an ID match
                }
                else
                {
                    // Indicate that the config ID changed
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
                    NvM_Prv_isConfigIdChanged_rMwM_b = TRUE;
#endif

                    if (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL)
                    {
                        // Indicate that the blocks need to be initialized
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
                        *initBlocksAtLayoutChange_pb = TRUE;
#else
                        // Parameter initBlocksAtLayoutChange_pb unused if NVM_RB_INIT_AT_LAYOUT_CHANGE is disabled
                        (void) initBlocksAtLayoutChange_pb;
#endif

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_OFF))
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2901] Signal the writing of the Config ID block in WriteAll when dynamic conf is active and extended dynamic conf is inactive
                        NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_WRITE_CONFIG_ID_BLOCK_IN_WRITE_ALL;
#else
                        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2890] Signal the writing of the Config ID block in the init phase when dynamic conf is inactive or extended dynamic conf is active
                        NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_WRITE_CONFIG_ID_BLOCK_AFTER_READ_ALL;
#endif
                    }

                    // TRACE[NVM547] Update the RAM block to the current layout's config ID so that a subsequent write stores it on the memory media
                    NvM_Prv_idConfigStored_rMwM_u16 = NVM_COMPILED_CONFIG_ID;

                    // TRACE[NVM312] Don't invalidate the config ID in the NV block unless the user explicitly requests it
                }
            }
            else if (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_WRITE)
            {
                // Config ID block successfully written
                // -> Indicate that the config ID stored on the media is identical to the current ID
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
                NvM_Prv_isConfigIdChanged_rMwM_b = FALSE;
#endif
                // Reset initialization variables after writing the Config ID block
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
                *initBlocksAtLayoutChange_pb = FALSE;
#else
                // Parameter initBlocksAtLayoutChange_pb unused if NVM_RB_INIT_AT_LAYOUT_CHANGE is disabled
                (void) initBlocksAtLayoutChange_pb;
#endif
                NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_DO_NOT_WRITE_CONFIG_ID;
            }
            else
            {
                // No actions for other jobs
            }
        }
        else // MEMIF_JOB_OK
        {
            if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL) &&
                    (NvM_Prv_Main_st.idActiveJob_rMwM_en == NVM_PRV_JOB_ID_READ))
            {
                if (JobResult_en == MEMIF_BLOCK_INVALID)
                {
                    // Config ID block has been invalidated
                    // TRACE[NVM673] Behave as if the config ID matched and update the RAM block to the current layout's config ID
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
                    NvM_Prv_isConfigIdChanged_rMwM_b = FALSE;
#endif
                    // Indicate that the blocks need to be initialized
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
                    *initBlocksAtLayoutChange_pb = TRUE;
#else
                    // Parameter initBlocksAtLayoutChange_pb unused if NVM_RB_INIT_AT_LAYOUT_CHANGE is disabled
                    (void) initBlocksAtLayoutChange_pb;
#endif
                    // Indicate that the Config ID block is not to be written when found invalidated
                    NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_DO_NOT_WRITE_CONFIG_ID;
                    // Assign the compiled ID to the RAM block of block #1
                    NvM_Prv_idConfigStored_rMwM_u16 = NVM_COMPILED_CONFIG_ID;
                }
                else if (JobResult_en == MEMIF_BLOCK_INCONSISTENT)
                {
                    // TRACE[NVM673] Behave as if the config ID matched and update the RAM block to the current layout's config ID
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
                    NvM_Prv_isConfigIdChanged_rMwM_b = FALSE;
#endif
                    // Indicate that the blocks need to be initialized
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
                    *initBlocksAtLayoutChange_pb = TRUE;
#else
                    // Parameter initBlocksAtLayoutChange_pb unused if NVM_RB_INIT_AT_LAYOUT_CHANGE is disabled
                    (void) initBlocksAtLayoutChange_pb;
#endif

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_OFF))
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2901] Signal the writing of the Config ID block in WriteAll when dynamic conf is active and extended dynamic conf is inactive
                    NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_WRITE_CONFIG_ID_BLOCK_IN_WRITE_ALL;
#else
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2890] Signal the writing of the Config ID block in the init phase when dynamic conf is inactive or extended dynamic conf is active
                    NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_WRITE_CONFIG_ID_BLOCK_AFTER_READ_ALL;
#endif

                    // Assign the compiled ID to the RAM block of block #1
                    NvM_Prv_idConfigStored_rMwM_u16 = NVM_COMPILED_CONFIG_ID;
                }
                else if (JobResult_en == MEMIF_JOB_FAILED)
                {
                    // Config ID block could not be read due to an error detected by one of the lower SW layers
                    // TRACE[NVM671] Behave as if the config ID has changed
                    // TRACE[NVM547] Update the RAM block to the current layout's config ID so that a subsequent write stores it on the memory media
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
                    NvM_Prv_isConfigIdChanged_rMwM_b = TRUE;
#endif
                    // Indicate that the blocks need to be initialized
#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
                    *initBlocksAtLayoutChange_pb = TRUE;
#else
                    // Parameter initBlocksAtLayoutChange_pb unused if NVM_RB_INIT_AT_LAYOUT_CHANGE is disabled
                    (void) initBlocksAtLayoutChange_pb;
#endif

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_OFF))
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2901] Signal the writing of the Config ID block in WriteAll when dynamic conf is active and extended dynamic conf is inactive
                    NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_WRITE_CONFIG_ID_BLOCK_IN_WRITE_ALL;
#else
                    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2890] Signal the writing of the Config ID block in the init phase when dynamic conf is inactive or extended dynamic conf is active
                    NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_WRITE_CONFIG_ID_BLOCK_AFTER_READ_ALL;
#endif

                    // Assign the compiled ID to the RAM block of block #1
                    NvM_Prv_idConfigStored_rMwM_u16 = NVM_COMPILED_CONFIG_ID;
                }
                else // MEMIF_JOB_CANCELED
                {
                }
            }
        }
    }
}

#endif

// ====================================================================================================================

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))

/* MR12 RULE 8.13 VIOLATION: The stBlock_pu8 pointer target is modified depending on pre-compile conditions, so it cannot be a pointer to const */
LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_TriggerWriteConfigId(uint8 *stBlock_pu8)
{
    // Trigger the writing of the config ID block in WriteAll if applicable
#if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)
    // Enhanced dynamic configuration: config ID is written during removal phase (after removing all non-resistant blocks)
    // Parameter stBlock_pu8 is unused in this case
    (void) stBlock_pu8;
#else
    // Standard AUTOSAR dynamic configuration: check if a config ID change has been detected during ReadAll
    if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL) &&
        (NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 == NVM_RB_CONFIG_ID_BLOCK) &&
        (NvM_Prv_ConfigIdBlockWriteTime_en == NVM_PRV_WRITE_CONFIG_ID_BLOCK_IN_WRITE_ALL))
    {
        // TRACE[NVM310] Mark the config ID block as VALID/CHANGED to enable its writing during WriteAll
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2901] Signal the writing of the config ID block in WriteAll when dynamic conf is active and extended dynamic conf is inactive
        *stBlock_pu8 |= NVM_BLOCK_STATE_RAM_VALID_CHANGED;
    }
#endif
}

#endif

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_FinalBlockCallbacks(NvM_RequestResultType stRequestResult_u8,
                                                                     NvM_BlockIdType idActiveBlock_u16,
                                                                     uint8 idActiveService_u8,
                                                                     boolean isAuxServiceActive)
{
    // Invoke observer and singleblock callbacks if applicable
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2842] Invoke the observer callback if this callback routine is configured
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2844] Invoke the observer callback before the singleblock callback
    if (NvM_Prv_Common_cst.ObserverCallback_pfct != NULL_PTR)
    {
        (*NvM_Prv_Common_cst.ObserverCallback_pfct)(idActiveBlock_u16,
                                                    idActiveService_u8,
                                                    stRequestResult_u8);
    }

    // TRACE[NVM347] Invoke singleblock callback if callback routine is configured
    // TRACE[NVM281] Processing of this block finished -> invoke callback function (applies to NvM_ReadAll)
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2839] Same as NVM281, but applied to first init
    // TRACE[NVM740] The callback is invoked upon termination of the block operation
    // TRACE[NVM742] The caller is only actively notified if a callback has been configured
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2930]
    // Don't invoke the singleblock callback if the current service is triggered by an auxiliary user
    if (!isAuxServiceActive &&
        (NvM_Prv_BlockDescriptors_acst[idActiveBlock_u16].SingleBlockCallback_pfct != NULL_PTR))
    {
        // TRACE[NVM741] Supply the ID of the just finished block operation to the callback owner
        (*NvM_Prv_BlockDescriptors_acst[idActiveBlock_u16].SingleBlockCallback_pfct)(idActiveService_u8,
                                                                                     stRequestResult_u8);
    }
}

// ====================================================================================================================

#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)

LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_TriggerInitAtLayoutChange(boolean initBlocksAtLayoutChange_b, NvM_RequestResultType stRequestResult_u8)
{
    // Signal the initialization of blocks at layout change
    // Notes:
    // - Signalling to block #0 indicates that an init phase is to be carried out
    // - Unlike the removal, signalling the initialization of the block is done in ResultEval because this needs
    //   to be done while the block is still active and after failing to read it from the medium
    if (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL)
    {
        // Concurrency note: At this level, the current block is still active and multiblock is also still active
        // -> NvM_Prv_stRequests_rAMwAM_au16 cannot be written by the APIs
        // -> it does not need to be protected by the SchM lock.
        if (initBlocksAtLayoutChange_b)
        {
            // Multiblock initialization after ReadAll
            if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE) == 0u)
            {
                // This is the first block which has to be initialized after ReadAll
                // -> Put a request for multiblock initialization to the (single-entry) multiblock queue
                NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE;
            }
        }

        if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE) != 0u)
        {
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2890] Signal the writing of the config ID block in the init phase when dynamic configuration is inactive or extended dynamic configuration is active
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2887] After its implicit recovery, signal the writing after ReadAll of the active block
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2888] Initialize the active block if a layout change is detected or the reading of the config ID block failed
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2892] Initialize the active block even if it is write protected
            if (((NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 == NVM_RB_CONFIG_ID_BLOCK) &&
                 (NvM_Prv_ConfigIdBlockWriteTime_en == NVM_PRV_WRITE_CONFIG_ID_BLOCK_AFTER_READ_ALL)) ||
                ((stRequestResult_u8 == NVM_REQ_RESTORED_FROM_ROM) &&
                 ((NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].stFlags_u16 &
                   (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_INIT_AT_LAYOUT_CHANGE) != 0u)))
            {
                SchM_Enter_NvM_Main();
                NvM_Prv_stRequestResult_rAwAM_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] = NVM_REQ_PENDING;
                NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] |= (uint16) NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE;
                SchM_Exit_NvM_Main();
            }
        }
    }
}

#endif

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionResultEval_ResetMainStates(void)
{
    // Reset the states of NvM's main state machine because the current job is now completely finished
    NvM_Prv_Main_st.idActiveJob_rMwM_en          = NVM_PRV_JOB_ID_IDLE;
    NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16    = 0;
    NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = 0;
    NvM_Prv_Main_st.idxActiveDataset_rMwM_u8     = 0;
    NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8   = NULL_PTR;
    NvM_Prv_Main_st.stActiveJobResult_rMwM_en    = MEMIF_JOB_OK;
    NvM_Prv_Main_st.Activity_rAMwM_en            = NVM_PRV_ACTIVITY_ARBITRATE;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
