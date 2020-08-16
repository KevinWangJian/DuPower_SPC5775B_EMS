

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "Rte_NvM.h"

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

void NvM_Init(void)
{
    // TRACE[NVM447] Service for resetting all internal variables
    NvM_BlockIdType idBlock_u16;

    // TRACE [BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3031] Runtime calculation of NV block lengths
    // TRACE [BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3038] Runtime calculation of RAM block addresses
    // TRACE [BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3047] Runtime calculation of explicit synchronization buffer
#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
    NvM_Prv_InitRuntimeRamBlockProperties();
#endif

    // TRACE[NVM399] Reset all internal variables to their initial values
    // We initialize most variables in the same order as defined in NvM.c (only to avoid unnecessary ambiguities)

    // Variables in cleared RAM
    // ------------------------

    // Variable saving blocks' errors (useful for debugging)
    for (idBlock_u16 = NVM_PRV_MULTI_BLOCK; idBlock_u16 < NVM_CFG_NR_BLOCKS; idBlock_u16++)
    {
        NvM_Rb_stBlockErrors_au8[idBlock_u16] = 0; // No errors
    }

    // Common (i.e. not block-specific) states
    NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_ARBITRATE; // We could get requests before first MainFunction call
    NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_SERVICE_ID_INIT;
    NvM_Prv_Main_st.idLastDetErrorService_wAM_u8 = NVM_SERVICE_ID_INIT;
    NvM_Prv_Main_st.idLastDetError_wAM_u8 = NVM_PRV_NO_DET_ERROR;
    NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_IDLE;
    NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = 0;
    NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = 0;
    NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
    NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
    NvM_Prv_Main_st.stActiveJobResult_rMwM_en = MEMIF_JOB_OK;
    NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b = FALSE;
    NvM_Prv_Main_st.isMultiBlockServiceSuspended_rMwM_b = FALSE;
    NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 = 0;
    NvM_Prv_Main_st.idSuspendedService_rMwM_u8 = NVM_SERVICE_ID_INIT;
    NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8 = NVM_REQ_OK;
    NvM_Prv_Main_st.isWriteAllCanceled_rMwAM_b = FALSE;
    NvM_Prv_Main_st.cntrMirrorOperations_rMwM_u8 = 0;
    NvM_Prv_AuxMigrationResult = NVM_RB_MIGRATION_RESULT_INIT_E;

    //TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] Initialize the variable to show the potentially incompatible
    //     blocks after layout changes are not sanitized by ReadAll function
    #if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON))
    NvM_Prv_isReadAllInitiated_b = FALSE;
    #endif

    // Administrative block
    for (idBlock_u16 = NVM_PRV_MULTI_BLOCK; idBlock_u16 < NVM_PRV_NR_BLOCKS_ADMIN; idBlock_u16++)
    {
        NvM_Prv_stRequests_rAMwAM_au16[idBlock_u16] = 0; // No request pending
        NvM_Prv_stRequestResult_rAwAM_au8[idBlock_u16] = NVM_REQ_OK; // TRACE[NVM470] The default value after reset is NVM_REQ_OK
        NvM_Prv_idxDataSet_rAMwA_au8[idBlock_u16] = 0; // TRACE[NVM192] The dataset index is initialized to zero during init
    }

    // Queue head and tail indices, queue monitoring
    NvM_Prv_idxBlockStdQueueHead_rAwA_u16 = 0;
    NvM_Prv_idxBlockStdQueueTail_rAMwM_u16 = 0;
    NvM_Prv_nrFreeStdQueueEntries_wAwM_u8 = NVM_SIZE_STANDARD_JOB_QUEUE;
#if (NVM_JOB_PRIORITIZATION == STD_ON)
    NvM_Prv_idxBlockImmQueueHead_rAwA_u16 = 0;
    NvM_Prv_idxBlockImmQueueTail_rAMwM_u16 = 0;
    NvM_Prv_nrFreeImmQueueEntries_wAwM_u8 = NVM_SIZE_IMMEDIATE_JOB_QUEUE;
#endif

    // Variables in saved zone
    // -----------------------

    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2785] Initialize saved-zone only if it is lost after a reset
#if (NVM_RB_RAM_INIT_CHECK == NVM_RB_RAM_INIT_CHECK_QUICK)
    if (NvM_Prv_SavedZoneMarker_u32 != NVM_PRV_SAVED_ZONE_MAGIC_VALUE)
#endif
    {
        // Queue monitoring
        NvM_Rb_minNrFreeStdQueueEntries_u8 = NVM_SIZE_STANDARD_JOB_QUEUE;
#if (NVM_JOB_PRIORITIZATION == STD_ON)
        NvM_Rb_minNrFreeImmQueueEntries_u8 = NVM_SIZE_IMMEDIATE_JOB_QUEUE;
#endif

        // Administrative block
        for (idBlock_u16 = NVM_PRV_MULTI_BLOCK; idBlock_u16 < NVM_PRV_NR_BLOCKS_ADMIN; idBlock_u16++)
        {
            // Standard RAM state: INVALID/UNCHANGED, not write protected
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2980] Also reset WriteAllTrigger flag
            NvM_Prv_stBlock_rAwAM_au8[idBlock_u16] = 0;

            // TRACE[NVM326] Enable write protection flag if configured accordingly
            if ((idBlock_u16 < NVM_CFG_NR_BLOCKS) &&
                ((NvM_Prv_BlockDescriptors_acst[idBlock_u16].stFlags_u16 &
                  (uint16)NVM_PRV_BLOCK_FLAG_WRITE_PROTECTED) != 0u))
            {
                NvM_Prv_stBlock_rAwAM_au8[idBlock_u16] |= NVM_BLOCK_STATE_WRITE_PROT;
            }
        }

        // Dynamic configuration / Init at layout change variables
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
        NvM_Prv_isConfigIdChanged_rMwM_b = FALSE;
#endif
#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
        // TRACE[NVM400] NvM_Prv_idConfigStored_rMwM_u16 not initialized here
        NvM_Prv_ConfigIdBlockWriteTime_en = NVM_PRV_DO_NOT_WRITE_CONFIG_ID;
#endif

        NvM_Prv_idBlockCausingLastDetError_uo = 0u;

#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)
        // Write request monitoring
        NvM_Rb_cntrWrites_u16 = 0u;
        NvM_Rb_nrBytesWritten_u32 = 0u;
        NvM_Rb_idLastWrittenBlock_uo = 0u;
#endif

    }

    // TRACE[NVM157] Initialization of the underlying memory drivers is not done here
    // TRACE[NVM193] Also don't initialize any other modules here
    // TRACE[NVM091] We also don't do an automatic loading of permanent RAM blocks here
    // TRACE[NVM158] The loading of permanent RAM blocks has to be triggered by the user via NvM_ReadAll
    // TRACE[NVM400] The permanent RAM block contents are not modified here

    // Final initialization actions
    // ----------------------------

    // Save a pattern to the saved zone marker (which will be checked after a reset)
#if (NVM_RB_RAM_INIT_CHECK == NVM_RB_RAM_INIT_CHECK_QUICK)
    NvM_Prv_SavedZoneMarker_u32 = NVM_PRV_SAVED_ZONE_MAGIC_VALUE;
#endif

    // TRACE[NVM399] Indicate finished initialization
    NvM_Prv_Main_st.isInitialized_rAM_b = TRUE;

#if ((NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON) && (NVM_PRV_HAS_RAM_MIRROR == STD_ON))
    for (idBlock_u16 = NVM_CFG_FIRST_USED_BLOCK; idBlock_u16 < NVM_CFG_NR_BLOCKS; idBlock_u16++)
    {

        if ( (NvM_Prv_BlockDescriptors_acst[idBlock_u16].stFlags_u16 &
              NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM) == NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM
           )
        {
            if (NvM_Prv_BlockLengths_au16[idBlock_u16] > NvM_Prv_RntRamMirrorSize_u32)
            {
                // BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3100 Indicate bad initialization
                NvM_Prv_Main_st.isInitialized_rAM_b = FALSE;
            }
        }
    }
#endif
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
