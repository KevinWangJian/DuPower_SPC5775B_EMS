

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

#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
# include "BswM_NvM.h"
// TRACE[NVM089] Check version compatibility of included header files
# if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
#  error "AUTOSAR major version undefined or mismatched"
# endif
# if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || ((BSWM_AR_RELEASE_MINOR_VERSION != 0) && (BSWM_AR_RELEASE_MINOR_VERSION != 2)))
#  error "AUTOSAR minor version undefined or mismatched"
# endif
#endif

#include "NvM_Prv.h"

/*
 **********************************************************************************************************************
 * Inline declarations
 **********************************************************************************************************************
 */

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

#if (NVM_JOB_PRIORITIZATION == STD_ON)
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckSingleImmediate(void);
LOCAL_INLINE void    NvM_Prv_MainFunctionArbitrate_MultiBlockResume(void);
#endif
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckSingleStandard(void);
#if (NVM_RB_AUX_INTERFACE == STD_ON)
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckSingleAux(void);
#endif
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckMultiAny(void);
LOCAL_INLINE NvM_Prv_idService_tuo NvM_Prv_GetServiceMultiBlock(uint16 MultiBlockRequest_uo);
LOCAL_INLINE NvM_BlockIdType NvM_Prv_GetFirstBlockForMultiBlockRequest(NvM_Prv_idService_tuo idService_uo);
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckMultiCurrent(NvM_BlockIdType idActiveBlock_uo);
#if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)
LOCAL_INLINE void    NvM_Prv_MainFunctionArbitrate_CheckRemoveMultiCurrent(void);
#endif
#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckWriteConfigId(void);
#endif
LOCAL_INLINE void    NvM_Prv_MainFunctionArbitrate_NotifyMultiStart(void);
LOCAL_INLINE void    NvM_Prv_MainFunctionArbitrate_NotifyMultiEnd(void);
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckMultiSecondPass(void);

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

/*
 **********************************************************************************************************************
 * NvM-private code
 **********************************************************************************************************************
 */

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

/**
 * This function determines the next request to be executed by checking all queues for entries to be started.
 *
 * All prioritizations of requests is done here.
 * This function will be invoked by NvM_Mainfunction only if no other request is currently active.
 *
 * \param[global in,out] NvM_Prv_Main_st
 * Global structure with all state information which is not block-specific.
 *
 */
void NvM_Prv_MainFunctionArbitrate(void)
{
    // Perform request arbitration

    // TRACE[NVM564] NvMJobPrioritization enables/disables immediate job processing
#if (NVM_JOB_PRIORITIZATION == STD_ON)
    if (!NvM_Prv_MainFunctionArbitrate_AckSingleImmediate())
#endif
    {
        // TRACE[NVM381] Don't let singleblock operations interrupt NvM_ReadAll operations
        // TRACE[NVM567] Same as NVM381, applied to NvM_WriteAll
        // Note: If a singleblock request is queued for a redundant block after it was signalled to be maintained
        //       and the maintenance operation has not been started yet, then the singleblock request is processed
        //       before starting the maintenance operation.
        /* MR12 RULE 13.5 VIOLATION: The side effect of the function call inside the condition expression is intended */
        if (!NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b &&
            !NvM_Prv_MainFunctionArbitrate_AckSingleStandard() &&
#if (NVM_RB_AUX_INTERFACE == STD_ON)
            !NvM_Prv_MainFunctionArbitrate_AckSingleAux() &&
#endif
            TRUE)
        {
            // No multiblock operation running and no singleblock requests pending
            // TRACE[NVM243] Now (and only now) check whether a multiblock read operation has been queued
            // TRACE[NVM254] Same as NVM243, but for NvM_WriteAll instead of NvM_ReadAll
            // TRACE[NVM858] Same as NVM243, but for NvM_ValidateAll instead of NvM_ValidateAll
            if (!NvM_Prv_MainFunctionArbitrate_AckMultiAny())
            {
                // No multiblock request pending either
                // -> NvM is completely idle
                NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_IDLE;
            }
            else
            {
                // Multiblock request acknowledged
                // -> notify the user that the multiblock operation is being started
                NvM_Prv_MainFunctionArbitrate_NotifyMultiStart();
            }
        }

        // The arbitration for new requests is finished
        // -> now look for the next block to be processed if a multi block operation is currently ongoing
        if (NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b)
        {
            boolean flgFindNextBlock_b = TRUE;

#if (NVM_JOB_PRIORITIZATION == STD_ON)
            // Resume multiblock operation if previously suspended by an immediate request
            NvM_Prv_MainFunctionArbitrate_MultiBlockResume();
#endif

            // TRACE[NVM244] Search for next block which has a read request (ascending)
            // Of course, we also do the same thing for write requests (although this is not explicitly requested)
            // and for all other multi-block requests
            while (flgFindNextBlock_b)
            {
                NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16++;
                if (NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 < NVM_CFG_NR_BLOCKS)
                {
                    // Determine whether and how NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 participates
                    // in the current multiblock operation
                    if (NvM_Prv_MainFunctionArbitrate_AckMultiCurrent(NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16))
                    {
                        flgFindNextBlock_b = FALSE;
                    }

#if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)
                    // Check whether the removal of the currently active block is necessary
                    NvM_Prv_MainFunctionArbitrate_CheckRemoveMultiCurrent();
#endif
                }
                else if (NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 == NVM_CFG_NR_BLOCKS)
                {
#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
                    // Last block of the multiblock operation has been processed
                    // -> check whether the config ID shall be written
                    if (NvM_Prv_MainFunctionArbitrate_AckWriteConfigId())
                    {
                        flgFindNextBlock_b = FALSE;
                    }
#endif
                }
                else
                {
                    // Multiblock operation finished
                    // -> notify users (if configured accordingly)
                    NvM_Prv_MainFunctionArbitrate_NotifyMultiEnd();

                    // Check whether a second pass of multiblock operations is necessary
                    if (!NvM_Prv_MainFunctionArbitrate_AckMultiSecondPass())
                    {
                        // Nothing more to be done for this multiblock operation
                        NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_SERVICE_ID_INIT;
                        NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b = FALSE;
                        NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 = 0;

                        // Leave the search for the next block to be activated
                        flgFindNextBlock_b = FALSE;
                    }
                }
            }
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

#if (NVM_JOB_PRIORITIZATION == STD_ON)

LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckSingleImmediate(void)
{
    // TRACE[NVM032] NvM supports priority based job processing

    // Local variables
    uint8 idCurrentService_u8;                  // Service which was active before acknowledging an immediate request
    NvM_Prv_QueueOpResult_ten stQueueStatus;    // Queue status

    // Save the ID of the currently active service before possibly unqueuing an immediate request
    // (which sets NvM_Prv_Main_st.idActiveService_rAMwM_u8 upon unqueuing)
    idCurrentService_u8 = NvM_Prv_Main_st.idActiveService_rAMwM_u8;

    // TRACE[NVM259] Check the status of the immediate queue and unqueue one request if not empty
    // (we do this first without locking to reduce the runtime impact caused by locking)
    stQueueStatus = NvM_Prv_GetQueueState(NVM_PRV_IMMEDIATE_QUEUE);
    if (NVM_PRV_QUEUE_EMPTY != stQueueStatus)
    {
        // TRACE[NVM162] Fetch the next request from the singleblock request queue
        SchM_Enter_NvM_Main();
        stQueueStatus = NvM_Prv_UnqueueBlockRequest(NVM_PRV_IMMEDIATE_QUEUE);
        SchM_Exit_NvM_Main();
    }

    // Check whether we acknowledged a request by unqueuing
    if (NVM_PRV_QUEUE_EMPTY != stQueueStatus)
    {
        // Check whether we have to suspend a multiblock operation
        if (NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b && (!NvM_Prv_Main_st.isMultiBlockServiceSuspended_rMwM_b))
        {
            // Signal that a multiblock operation is to be suspended
            NvM_Prv_Main_st.isMultiBlockServiceSuspended_rMwM_b = TRUE;

            // If a multiblock operation is running save the service ID before starting the immediate job
            NvM_Prv_Main_st.idSuspendedService_rMwM_u8 = idCurrentService_u8;
        }

        // Start the requested immediate singleblock operation
        if (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_WRITE_BLOCK)
        {
            // Signal that the write request has been unqueued
            // Concurrency note: At this level, the block has already become active
            //                   -> NvM_Prv_stRequests_rAMwAM_au16[blockId] cannot be written by the APIs
            //                   -> it does not need to be protected by the SchM lock.
            // Write protection has already been checked before enqueueing, it's not repeated here (analogously to NVM662 and NVM665)
            NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_WRITE);

            // Set the data index (needed in case of DATASET blocks)
            if (NVM_BLOCK_DATASET == NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en)
            {
                NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = NvM_Prv_idxDataSet_rAMwA_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16];
            }

            // Set the job to be started
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_WRITE;

            // Start the requested immediate singleblock write
            NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
        }
        else
        {
            // Unknown/invalid immediate singleblock service ID
            // (we should actually never get here; it's just there for robustness)
            // -> clear current request, stay in arbitration

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
            // save block ID before reset it here
            NvM_Prv_SetBlockIdCausingLastDetError(NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16);

            NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_SERVICE_ID_INIT;
            NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = 0;
            NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = 0;
            NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
            NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_MAIN_FUNCTION, NVM_E_SINGLE_BLOCK_SERVICE_ID);
        }
    }

    // Return whether this function started a job
    return (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START);
}

#endif

// ====================================================================================================================

#if (NVM_JOB_PRIORITIZATION == STD_ON)

LOCAL_INLINE void NvM_Prv_MainFunctionArbitrate_MultiBlockResume(void)
{
    // Resume multiblock operation if previously suspended by an immediate request
    if (NvM_Prv_Main_st.isMultiBlockServiceSuspended_rMwM_b)
    {
        // Update service ID
        NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NvM_Prv_Main_st.idSuspendedService_rMwM_u8;
        // Reset multiblock operation suspending variables for next suspend
        NvM_Prv_Main_st.isMultiBlockServiceSuspended_rMwM_b = FALSE;
        NvM_Prv_Main_st.idSuspendedService_rMwM_u8 = NVM_SERVICE_ID_INIT;
    }
}

#endif

// ====================================================================================================================

LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckSingleStandard(void)
{
    // Local variables
    NvM_Prv_QueueOpResult_ten stQueueStatus;    // Queue status

    // Check the status of the standard queue and unqueue one request if not empty
    // (we do this first without locking to reduce the runtime impact caused by locking)
    stQueueStatus = NvM_Prv_GetQueueState(NVM_PRV_STANDARD_QUEUE);
    if (NVM_PRV_QUEUE_EMPTY != stQueueStatus)
    {
        // TRACE[NVM162] Fetch the next request from the singleblock request queue
        SchM_Enter_NvM_Main();
        stQueueStatus = NvM_Prv_UnqueueBlockRequest(NVM_PRV_STANDARD_QUEUE);
        SchM_Exit_NvM_Main();
    }

    // Check whether we acknowledged a request by unqueuing
    if (NVM_PRV_QUEUE_EMPTY != stQueueStatus)
    {
        // Determine the job ID corresponding to the requested service and acknowledge the corresponding request
        switch (NvM_Prv_Main_st.idActiveService_rAMwM_u8)
        {
            // Concurrency note: At this level, the block has already become active
            //                   -> NvM_Prv_stRequests_rAMwAM_au16[blockId] cannot be written by the APIs
            //                   -> it does not need to be protected by the Schm lock.
            case NVM_SERVICE_ID_READ_BLOCK:
                NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_READ);
                NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_READ;
                break;
            case NVM_SERVICE_ID_WRITE_BLOCK:
                // Write protection has already been checked before enqueueing, it's not repeated here (analogously to NVM662 and NVM665)
                NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_WRITE);
                NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_WRITE;
                break;
            case NVM_SERVICE_ID_INVALIDATE_NV_BLOCK:
                // TRACE[NVM665] Write protection has already been checked before enqueueing, it's not repeated here
                NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_INVALIDATE);
                NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_INVALIDATE;
                break;
            case NVM_SERVICE_ID_ERASE_NV_BLOCK:
                // TRACE[NVM662] Write protection has already been checked before enqueueing, it's not repeated here
                NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_ERASE);
                NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_ERASE;
                break;
            case NVM_SERVICE_ID_RESTORE_BLOCK_DEFAULTS:
                NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_RESTORE);
                NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_RESTORE;
                break;
            default:
                NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_IDLE;
                break;
        }

        // Determine the next activity based on the job ID
        if (NvM_Prv_Main_st.idActiveJob_rMwM_en != NVM_PRV_JOB_ID_IDLE)
        {
            // Service ID is valid for singleblock operations
            // -> Set the data index (needed in case of DATASET blocks)
            if (NVM_BLOCK_DATASET == NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en)
            {
                NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = NvM_Prv_idxDataSet_rAMwA_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16];
            }

            // Start the requested singleblock operation
            NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
        }
        else
        {
            // Unknown/invalid singleblock service ID
            // (we should actually never get here; it's just there for robustness)
            // -> clear current request, stay in arbitration

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
            // save block ID before reset it here
            NvM_Prv_SetBlockIdCausingLastDetError(NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16);

            NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_SERVICE_ID_INIT;
            NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = 0;
            NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = 0;
            NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
            NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_MAIN_FUNCTION, NVM_E_SINGLE_BLOCK_SERVICE_ID);
        }
    }

    // Return whether this function started a job
    return (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START);
}

// ====================================================================================================================

#if (NVM_RB_AUX_INTERFACE == STD_ON)

LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckSingleAux(void)
{
    // Check the status of the auxiliary "queue" and unqueue it if not empty
    // (we do this first without locking to reduce the runtime impact caused by locking)
    if (NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] != 0u)
    {
        SchM_Enter_NvM_Main();
        if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_READ) != 0u)
        {
            NvM_Prv_UnqueueAuxBlockRequest();
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_READ);
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_READ;
        }
        else if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_WRITE) != 0u)
        {
            NvM_Prv_UnqueueAuxBlockRequest();
            // Write protection has already been checked before enqueueing, it's not repeated here (analogously to NVM662 and NVM665)
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_WRITE);
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_WRITE;
        }
        else if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_INVALIDATE) != 0u)
        {
            NvM_Prv_UnqueueAuxBlockRequest();
            // TRACE[NVM665] Write protection has already been checked before enqueueing, it's not repeated here
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] &= (uint16) ~((uint16)NVM_PRV_BLOCK_REQ_INVALIDATE);
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_INVALIDATE;
        }
        else
        {
            // (we can only come here if an unknown request has been added to the auxiliary queue; should never be the case)
            // -> Kill this unknown request
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_AUX_ADMIN_BLOCK] = 0u;
        }
        SchM_Exit_NvM_Main();

        // Determine the next activity based on the job ID
        if (NvM_Prv_Main_st.idActiveJob_rMwM_en != NVM_PRV_JOB_ID_IDLE)
        {
            // Service ID is valid for singleblock operations
            // -> Set the data index (needed in case of DATASET blocks)
            if (NVM_BLOCK_DATASET == NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16].BlockManagementType_en)
            {
                NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_AUX_ADMIN_BLOCK];
            }

            // Start the requested singleblock operation
            NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
        }
        else
        {
            // Unknown/invalid singleblock service ID
            // (we should actually never get here; it's just there for robustness)
            // -> clear current request, stay in arbitration

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Set block ID used in NvM service causing last DET error
            // save block ID before reset it here
            NvM_Prv_SetBlockIdCausingLastDetError(NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16);

            NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_SERVICE_ID_INIT;
            NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = 0;
            NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = 0;
            NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
            NVM_PRV_REPORT_DET_ERROR(NVM_SERVICE_ID_MAIN_FUNCTION, NVM_E_SINGLE_BLOCK_SERVICE_ID);
        }
    }

    // Return whether this function started a job
    return (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START);
}

#endif

// ====================================================================================================================

/**
 * This function starts the execution of a multiblock request.
 *
 * To start a multiblock request the global variable NvM_Prv_Main_st.idActiveService_rAMwM_u8 must be set
 * to corresponding value and the request bit must be cleared in global variable
 * NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] to acknowledge the multiblock request.
 * In addition the global flag NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b must be set to signal
 * that a multiblock request is started.
 * Also this function determines the block ID which will be processed first by the current multiblock request and
 * presets the result of the multiblock request to NVM_REQ_OK.
 *
 * \attention
 * This function starts only multiblock requests coming from API user. Only one such requests can be requested at once.
 * For following multiblock requests there is an API:
 * - ReadAll
 * - WriteAll
 * - ValidateAll
 * - FirstInitAll
 * All other multiblock requests are "internal" requests and will be handled separately.
 *
 * \param[in,out] NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK]
 * Global bit field with enqueued multiblock requests. To acknowledge started multiblock request the corresponding bit
 * in this bit field will be cleared.
 *
 * \param[out] NvM_Prv_Main_st.idActiveService_rAMwM_u8
 * Global variable to which the started multiblock request(service) will be written.
 *
 * \param[out] NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b
 * Global flag which signals that a multiblock request has been started.
 *
 * \param[out] NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16
 * Global ID of the block which will be processed first by started multiblock request.
 *
 * \param[out] NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8
 * Global result of the multiblock request.
 *
 * \return
 * Indicator whether a multiblock request has been started.
 */
LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckMultiAny(void)
{
    // TRACE[NVM380] The "queue" for multi block requests has only one entry
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] Requests for the removal of non-resistant blocks are not
    //   started here. Instead, they are directly appended to the ReadAll service execution (isMultiBlockActive_rAMwM_b
    //   is always TRUE during this service change to lock out any intermediate singleblock processing)
    // Check the status of the multiblock "queue" and unqueue it if not empty
    // (we do this first without locking to reduce the runtime impact caused by locking)
    if (NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] != 0u)
    {
        uint16 MultiBlockRequestToStart_uo;
        // This mask contains bit masks of all multiblock requests which can be started by API user.
        uint16 const maskUserMultiBlockRequests_uo = ((uint16)NVM_PRV_BLOCK_REQ_READ_ALL       |
                                                      (uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL      |
                                                      (uint16)NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL |
                                                      (uint16)NVM_PRV_BLOCK_REQ_VALIDATE_ALL);

        // Concurrency notes 1:
        // - The corresponding request bit in NvM_Prv_stRequests_rAMwAM_au16 is cleared ("acknowledge")
        //   *after* setting NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b to TRUE
        // - Before a new multiblock operation can be queued, *both* indicators must be cleared
        // -> No multiblock operation can be queued concurrently even without locking
        // Concurrency notes 2:
        // - NvM_Prv_Main_st.idActiveService_rAMwM_u8 is consistently set *before* doing the actual
        //   acknowledge operation
        // - This is particularly important for the CancelWriteAll operation which would otherwise not take any effect
        //   when called at the moment when WriteAll is acknowledged but NvM_Prv_Main_st.idActiveService_rAMwM_u8
        //   is not set yet
        // Concurreny conclusion: we pull the lock here only to be on the safe side also for the other state variables
        SchM_Enter_NvM_Main();

        // Determine the multiblock request to be started and acknowledged
        // In NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] only 1 bit for API user requests can be set at once.
        // With maskUserMultiBlockRequests_uo we mask out all internal requests and in result only 1 of 4 possible
        // API user bits is set.
        MultiBlockRequestToStart_uo =
                NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & maskUserMultiBlockRequests_uo;

        // Determine service ID for the pending multiblock request
        NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NvM_Prv_GetServiceMultiBlock(MultiBlockRequestToStart_uo);

        // Set the multiblock activity indicator to TRUE if any multiblock request is pending
        // If no multiblock request is pending the multiblock activity indicator will be set to FALSE
        NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b = (NvM_Prv_Main_st.idActiveService_rAMwM_u8 != 0);

        // Acknowledge the pending multiblock request (reset corresponding bit)
        NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] &= (uint16)(~MultiBlockRequestToStart_uo);

        // Determine the id of the start block for the active multiblock request
        NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 =
                NvM_Prv_GetFirstBlockForMultiBlockRequest(NvM_Prv_Main_st.idActiveService_rAMwM_u8);

        // TRACE[NVM395] Maintain overall result of the multiblock operation
        NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8 = NVM_REQ_OK;

        SchM_Exit_NvM_Main();
    }

    // Return the value of the acknowledge indicator
    return NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b;
}

// ====================================================================================================================

LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckMultiCurrent(NvM_BlockIdType idActiveBlock_uo)
{
    // NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 is a possible multiblock operation candidate
    // -> check block-specific request flag whether it has been selected for multiblock operation

    // Note on request results:
    // If a singleblock request was queued but not finished for this block before the current multiblock
    // service was triggered, the PENDING request result is cleared upon finishing the singleblock operation
    // although the multiblock service is still pending
    // -> for all user-visible multiblock operations, the PENDING request result is set again when starting
    //    the processing of this block in the multiblock operation

    // Concurrency notes:
    // - NvM_Prv_stRequests_rAMwAM_au16[BlockId] and NvM_Prv_Main_st.idActiveBlock_rAMwM_u16 are checked in
    //   singleblock APIs before queuing a singleblock request
    // - The (i) acknowledgment of the multiblock request for a block and (ii) setting of the active block
    //   need to be done under SchM lock so that no singleblock request is queued between (i) and (ii) for a
    //   block which is already queued for a multiblock operation

    // User-triggered multiblock operations
    // ------------------------------------

    // ReadAll
    if ((NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] & (uint16)NVM_PRV_BLOCK_REQ_READ_ALL) != 0u)
    {
        SchM_Enter_NvM_Main();

        // Acknowledge the read request
        NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_READ_ALL));

#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
        // If dynamic config is enabled, NvM_Prv_isConfigIdChanged_rMwM_b is set after reading block #1 in ReadAll
        // In case the configuration ID changed, check whether the current block is configured to be robust against this
        if (NvM_Prv_isConfigIdChanged_rMwM_b &&
            ((NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW) == 0u))
        {
            // The current block is not resistant to changed SW
# if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)
            // The block-specific request result should not be set to NVM_REQ_BLOCK_SKIPPED in this case
            // because this scenario triggers a removal of this block if this feature has been enabled
            // (which will almost immediately set the request result back to NVM_REQ_PENDING again)
# else
            // TRACE[NVM287] Set job result to NVM_REQ_BLOCK_SKIPPED if not read
            NvM_Prv_stRequestResult_rAwAM_au8[idActiveBlock_uo] = NVM_REQ_BLOCK_SKIPPED;
# endif

            // No job is started in this case
        }
        else
#endif
        {
            // For consistency with NVM198, we set the status of the permanent RAM block to INVALID also here
            NvM_Prv_stBlock_rAwAM_au8[idActiveBlock_uo] &= (uint8) ~(NVM_BLOCK_STATE_RAM_VALID);

            // Start a read job
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_READ;
            NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = idActiveBlock_uo;
            NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = idActiveBlock_uo;
            NvM_Prv_stRequestResult_rAwAM_au8[idActiveBlock_uo] = NVM_REQ_PENDING;
            // TRACE[NVM245] DATASET blocks can't participate in ReadAll
            NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
            /* MR12 RULE 11.5 VIOLATION: The actual type of the RAM block varies from block to block (not under control of NvM) */
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = (uint8*)
                                                         *NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].adrRamBlock_ppv;
            NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
        }

        SchM_Exit_NvM_Main();
    }

    // WriteAll
    else if ((NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] & (uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL) != 0u)
    {
        SchM_Enter_NvM_Main();

        // Acknowledge the write request
        NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL));

        // For consistency with NVM303, we set the status of the permanent RAM block to VALID also here
        NvM_Prv_stBlock_rAwAM_au8[idActiveBlock_uo] |= NVM_BLOCK_STATE_RAM_VALID;

        // Start a write job
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_WRITE;
        NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = idActiveBlock_uo;
        NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = idActiveBlock_uo;
        NvM_Prv_stRequestResult_rAwAM_au8[idActiveBlock_uo] = NVM_REQ_PENDING;
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = NvM_Prv_idxDataSet_rAMwA_au8[idActiveBlock_uo];
        /* MR12 RULE 11.5 VIOLATION: The actual type of the RAM block varies from block to block (not under control of NvM) */
        NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = (uint8*)
                                                     *NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].adrRamBlock_ppv;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;

        SchM_Exit_NvM_Main();
    }

    // FirstInitAll
    else if ((NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] & (uint16)NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL) != 0u)
    {
        SchM_Enter_NvM_Main();

        // Acknowledge the initialization request
        NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL));

        // Determine whether a restore or an invalidation job shall be started
        if ((NVM_BLOCK_DATASET != NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].BlockManagementType_en) &&
            (NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].adrRomBlock_pcv ||
             NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].InitBlockCallback_pfct))
        {
            // The current block is not of type DATASET and has a ROM block or init callback
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2833] Do a restore if ROM block or InitBlockCallback present
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2831] Only blocks with permanent RAM block/explicit sync
            //                                               are selected for FirstInit
            // -> we don't have to check for this condition again as this is already done in the ECUC processor

            // For consistency with NVM227, we set the status of the permanent RAM block to INVALID also here
            NvM_Prv_stBlock_rAwAM_au8[idActiveBlock_uo] &= (uint8) ~(NVM_BLOCK_STATE_RAM_VALID);

            // Start a restore job (part 1)
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_RESTORE;
            /* MR12 RULE 11.5 VIOLATION: The actual type of the RAM block varies from block to block (not under control of NvM) */
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = (uint8*)
                                                         *NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].adrRamBlock_ppv;
        }
        else
        {
            // The current block is of type DATASET or neither has a ROM block nor an init callback
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2835] Do invalidation if No ROM block and no InitBlockCallback

            // Start an invalidation job (part 1)
            NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_INVALIDATE;
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
        }

        // Start the job (part 2)
        NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = idActiveBlock_uo;
        NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = idActiveBlock_uo;
        NvM_Prv_stRequestResult_rAwAM_au8[idActiveBlock_uo] = NVM_REQ_PENDING;
        // For DATASET blocks, it is important to initialize the active dataset to 0 here to prepare
        // for the invalidation of all NV blocks
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;

        SchM_Exit_NvM_Main();
    }

    // ValidateAll
    else if ((NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] & (uint16)NVM_PRV_BLOCK_REQ_VALIDATE_ALL) != 0u)
    {
        SchM_Enter_NvM_Main();

        // Acknowledge the validation request
        NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_VALIDATE_ALL));

        // Start a validation job
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_VALIDATE;
        NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = idActiveBlock_uo;
        NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = idActiveBlock_uo;
        NvM_Prv_stRequestResult_rAwAM_au8[idActiveBlock_uo] = NVM_REQ_PENDING;
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
        NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;

        SchM_Exit_NvM_Main();
    }

    // Automatically triggered multiblock background operations
    // --------------------------------------------------------

#if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)
    // Removal of non-resistant blocks after ReadAll
    else if ((NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] & (uint16)NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT) != 0u)
    {
        SchM_Enter_NvM_Main();

        // Acknowledge the removal request
        NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT));

        // Block removal on the memory media has no effect on the RAM block -> RAM validity is not changed

        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] Start an invalidation job
        // Note: Actually, a true removal of this block from the memory media would be desired but is
        //       not supported by the lower mem stack layers yet
        // Caution: Once this is changed to something other than NVM_PRV_JOB_ID_INVALIDATE, the special
        //       request result created in this case (in result evaluation) probably also has to be changed
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_INVALIDATE;
        NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = idActiveBlock_uo;
        NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = idActiveBlock_uo;
        NvM_Prv_stRequestResult_rAwAM_au8[idActiveBlock_uo] = NVM_REQ_PENDING;
        // For DATASET blocks, it is important to initialize the active dataset to 0 here to prepare
        // for the invalidation of all NV blocks
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
        NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;

        SchM_Exit_NvM_Main();
    }
#endif

#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
    // Initialization of blocks upon layout change
    else if ((NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] & (uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE) != 0u)
    {
        SchM_Enter_NvM_Main();

        // Acknowledge the initialization request
        NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE));

        // For consistency with NVM303, we set the status of the permanent RAM block to VALID also here
        NvM_Prv_stBlock_rAwAM_au8[idActiveBlock_uo] |= NVM_BLOCK_STATE_RAM_VALID;

        // Start a write job
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_WRITE;
        NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = idActiveBlock_uo;
        NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = idActiveBlock_uo;
        NvM_Prv_stRequestResult_rAwAM_au8[idActiveBlock_uo] = NVM_REQ_PENDING;
        // A block of type DATASET cannot be selected for initialization at a layout change
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
        /* MR12 RULE 11.5 VIOLATION: The actual type of the RAM block varies from block to block (not under control of NvM) */
        NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = (uint8*)
                                                     *NvM_Prv_BlockDescriptors_acst[idActiveBlock_uo].adrRamBlock_ppv;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;

        SchM_Exit_NvM_Main();
    }
#endif

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
    // Maintenance of redundant blocks
    // Note: As the maintenance request flag is set in NvM_WriteAll (in parallel to the write request flag),
    //       the additional idActiveService_rAMwM_u8 check is done here in order to ensure that this case is not entered
    //       if the maintenance has not been started by the main function yet
    else if (((NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] & (uint16)NVM_PRV_BLOCK_REQ_MAINTAIN) != 0u) &&
             (NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK))
    {
        // Concurrency note: In case of maintenance, a singleblock request can be queued when the block is waiting to be
        // maintained or it is currently being maintained -> lock is also required here
        SchM_Enter_NvM_Main();

        // Acknowledge the maintenance request
        NvM_Prv_stRequests_rAMwAM_au16[idActiveBlock_uo] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_MAINTAIN));

        // Start a maintenance job
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_MAINTAIN;
        NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = idActiveBlock_uo;
        NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = idActiveBlock_uo;
        // Maintenance shall be invisible to the user -> NvM_Prv_stRequestResult_rAwAM_au8 remains untouched
        // A block of type DATASET is never maintained because it is never redundant
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
        NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NULL_PTR;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;

        SchM_Exit_NvM_Main();
    }
#endif

    // No operation
    else
    {
        // The block was not selected to participate in a multi-block operation
    }

    // Return whether this function started a job
    return (NvM_Prv_Main_st.Activity_rAMwM_en == NVM_PRV_ACTIVITY_JOB_START);
}

// ====================================================================================================================

#if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)

LOCAL_INLINE void NvM_Prv_MainFunctionArbitrate_CheckRemoveMultiCurrent(void)
{
    // Check whether the removal of the currently active block is necessary
    if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_READ_ALL) && NvM_Prv_isConfigIdChanged_rMwM_b)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] We need multiblock removal directly after ReadAll
        if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT) == 0u)
        {
            // No multiblock removal triggered yet -> put a request for multiblock removal to the multiblock queue
            // Concurrency note: NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] cannot be concurrently written
            //                   by a multiblock API because NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b is set
            NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT;

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] Trigger the writing of the configuration ID
            // Note: We already passed the handling of the config ID block in ReadAll processing
            //       -> the request for removal of the config ID block is interpreted as a write request for this block
            //          after all ReadAll is through with all its blocks
            SchM_Enter_NvM_Main();
            NvM_Prv_stRequestResult_rAwAM_au8[NVM_RB_CONFIG_ID_BLOCK] = NVM_REQ_PENDING;
            NvM_Prv_stRequests_rAMwAM_au16[NVM_RB_CONFIG_ID_BLOCK] |= (uint16) NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT;
            SchM_Exit_NvM_Main();
        }

        // Check whether the current block is configured to be non-resistant to changed software
        if ((NvM_Prv_BlockDescriptors_acst[NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16].stFlags_u16 &
             (uint16)NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW) == 0u)
        {
            // The current block is not resistant to changed SW
            // Note: The config ID block is configured to be resistant to changed SW, so it is not covered here again
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] Trigger the removal of this particular block
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2790] We do this even if write protection is enabled for this block
            // Note: The current block's request flag for removal will not be evaluated in the ReadAll loop anymore
            SchM_Enter_NvM_Main();
            NvM_Prv_stRequestResult_rAwAM_au8[NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16] = NVM_REQ_PENDING;
            NvM_Prv_stRequests_rAMwAM_au16[NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16] |= (uint16) NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT;
            SchM_Exit_NvM_Main();
        }
    }
}

#endif

// ====================================================================================================================

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))

LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckWriteConfigId(void)
{
    // Check whether the config ID shall be written

    // Local variables
    boolean flgWriteConfigID_b = FALSE;

    SchM_Enter_NvM_Main();

    // TRACE[NVM733] Write the configuration ID (as a final step in WriteAll) if it has been marked to be written
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2901] Same as NVM733 applied for "init at layout change" feature
    if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_WRITE_ALL) &&
        ((NvM_Prv_stRequests_rAMwAM_au16[NVM_RB_CONFIG_ID_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL) != 0u))
    {
        // Acknowledge the write request and locally indicate the need for writing
        NvM_Prv_stRequests_rAMwAM_au16[NVM_RB_CONFIG_ID_BLOCK] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_WRITE_ALL));
        flgWriteConfigID_b = TRUE;
    }

#if (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON)
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] Write the configuration ID as a final step in removal
    // Note: The check for the active service is needed because otherwise we would trigger the write
    //       after the ReadAll already, not after the multiblock removal as requested
    if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_RB_REMOVE_NON_RESISTANT) &&
        ((NvM_Prv_stRequests_rAMwAM_au16[NVM_RB_CONFIG_ID_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT) != 0u))
    {
        // Acknowledge the write request and locally indicate the need for writing
        NvM_Prv_stRequests_rAMwAM_au16[NVM_RB_CONFIG_ID_BLOCK] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT));
        flgWriteConfigID_b = TRUE;
    }
#endif

#if (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON)
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2890] Write the configuration ID as a final step in initialization phase (after ReadAll)
    // Note: The check for the active service is needed because otherwise we would trigger the write
    //       after the ReadAll already, not after the multiblock initilization as requested
    if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_RB_INIT_AFTER_READ_ALL) &&
        ((NvM_Prv_stRequests_rAMwAM_au16[NVM_RB_CONFIG_ID_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE) != 0u))
    {
        // Acknowledge the write request and locally indicate the need for writing
        NvM_Prv_stRequests_rAMwAM_au16[NVM_RB_CONFIG_ID_BLOCK] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE));
        flgWriteConfigID_b = TRUE;
    }
#endif

    if (flgWriteConfigID_b)
    {
        // Start a write job
        NvM_Prv_Main_st.idActiveJob_rMwM_en = NVM_PRV_JOB_ID_WRITE;
        NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = NVM_RB_CONFIG_ID_BLOCK;
        NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = NVM_RB_CONFIG_ID_BLOCK;
        NvM_Prv_stRequestResult_rAwAM_au8[NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16] = NVM_REQ_PENDING;
        // The config ID block is not of type DATASET
        NvM_Prv_Main_st.idxActiveDataset_rMwM_u8 = 0;
        /* MR12 RULE 11.5 VIOLATION: The actual type of the RAM block varies from block to block (not under control of NvM) */
        NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = (uint8*) *NvM_Prv_BlockDescriptors_acst[NVM_RB_CONFIG_ID_BLOCK].adrRamBlock_ppv;
        NvM_Prv_Main_st.Activity_rAMwM_en = NVM_PRV_ACTIVITY_JOB_START;
    }

    SchM_Exit_NvM_Main();

    // Return whether this function started a write job for the config ID block
    return flgWriteConfigID_b;
}

#endif

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionArbitrate_NotifyMultiStart(void)
{
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
    //If BswMMultiBlockJobStatusInformation is enabled, the multiblock start callback is not invoked
#else
    if (NvM_Prv_Common_cst.RbMultiBlockStartCallback_pfct != NULL_PTR)
    {
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2771] Invoke multiblock start callback (if configured).
        (*NvM_Prv_Common_cst.RbMultiBlockStartCallback_pfct)(NvM_Prv_Main_st.idActiveService_rAMwM_u8);
    }
#endif
}

// ====================================================================================================================

LOCAL_INLINE void NvM_Prv_MainFunctionArbitrate_NotifyMultiEnd(void)
{
    // TRACE[NVM395] Determine overall result of the multiblock operation
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2857] The maintenance operation is performed as part of the execution of the NvM_WriteAll job
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2867] WriteAll operation finishes when the writing of the suitable blocks and the maintenance of the redundant blocks are done
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2873] In case of WriteAll, the multiblock callback is called after that the subsequent maintenance phase is finished
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2875] In case of WriteAll, the BswM-notification is done after that the subsequent maintenance phase is finished
#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
    if ((NvM_Prv_Main_st.idActiveService_rAMwM_u8 == NVM_SERVICE_ID_WRITE_ALL) &&
        ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_MAINTAIN) != 0u))
    {
        // The multiblock callback is called after the overall WriteAll operation including the maintenance phase has
        // finished; the same applies to the BswM notification
        // -> we have to skip any notification here in this case
        // -> we come back once also maintenance is finished (then with NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK as the active service)
    }
    else
#endif
    {
        // Determine the active service as indicated to the notification receiver
        uint8 idActiveService = NvM_Prv_Main_st.idActiveService_rAMwM_u8;
#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
        if (idActiveService == NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK)
        {
            // Maintenance shall be an "invisible" operation after WriteAll, so we indicate WriteAll to the notification receiver
            idActiveService = NVM_SERVICE_ID_WRITE_ALL;
        }
#endif

        // Determine the final multiblock result
        if ((idActiveService == NVM_SERVICE_ID_WRITE_ALL) && (NvM_Prv_Main_st.isWriteAllCanceled_rMwAM_b != FALSE))
        {
            // TRACE[NVM237] In case CancelWriteAll was invoked while WriteAll had been pending, the request result of block #0 is set to CANCELED
            // TRACE[NVM235] The request result of CancelWriteAll is implicitly given by the request result of the canceled WriteAll
            NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8 = NVM_REQ_CANCELED;

            // Reset isWriteAllCanceled_rMwAM_b
            NvM_Prv_Main_st.isWriteAllCanceled_rMwAM_b = FALSE;
        }
        // Concurrency note: NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b is still active so
        //                   NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_MULTI_BLOCK] cannot be written concurrently
        //                   by a multiblock API
        //                -> no locking necessary here
        NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_MULTI_BLOCK] = NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8;

        // Now trigger the actual (BswM or multiblock callback) notification
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, provide the muliblock request result to BswM
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2810] If BswMMultiBlockJobStatusInformation is enabled, the multiblock callback if configured is not invoked
#if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        BswM_NvM_CurrentJobMode(idActiveService, NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8);
#else
        // TRACE[NVM347] Invoke multiblock callback if callback routine is configured
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2839] This also applies to the first init case
        if (NvM_Prv_Common_cst.MultiBlockCallback_pfct != NULL_PTR)
        {
            // TRACE[NVM686] Supply the ID of the just finished multiblock operation to the callback owner
            (*NvM_Prv_Common_cst.MultiBlockCallback_pfct)(idActiveService, NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8);
        }
#endif
    }
}

// ====================================================================================================================

LOCAL_INLINE boolean NvM_Prv_MainFunctionArbitrate_AckMultiSecondPass(void)
{
    // Check whether a second pass of multiblock operations is necessary
    boolean isSecondPassNeeded_b = FALSE;

#if ((NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] If at least one block has been found during the current
    //   multiblock operation (this search is only done during ReadAll) which is not resistant to changed SW
    //   and a SW change has been detected, then start the multiblock removal sequence here
    // Initialization and removal are done in the same phase after ReadAll
    if (((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT) != 0u) ||
        ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE) != 0u))
    {
        // Multiblock removal request pending
        // -> acknowledge this request
        // Concurrency note: NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b is still set so
        //                   NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] cannot be written concurrently
        //                   by a multiblock API
        //                -> no locking necessary here
        NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT));
        NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE));
        NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_MULTI_BLOCK] = NVM_REQ_PENDING;
        NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8 = NVM_REQ_OK;
        NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_SERVICE_ID_RB_INIT_AFTER_READ_ALL;
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2804] If BswMMultiBlockJobStatusInformation is enabled, notify BswM about the state change of the multiblock operation
# if (NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION == STD_ON)
        BswM_NvM_CurrentJobMode(NVM_SERVICE_ID_RB_INIT_AFTER_READ_ALL, NVM_REQ_PENDING);
# endif
        // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2787] Start initialization/removal with block 2
        NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 = (NvM_BlockIdType) NVM_RB_FIRST_USER_BLOCK - 1u;

        // Second pass of multiblock operations needed
        isSecondPassNeeded_b = TRUE;
    }
    else // CAUTION: This is an "else if" case separated by the NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS switch.
#endif

#if (NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS)
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2858] Start the maintenance operation for all redundant blocks after that the writing of the blocks in WriteAll finished
    // CAUTION: This is an "else if" case separated by the NVM_PRV_MAINTAIN_REDUNDANT_BLOCKS switch.
    if ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] & (uint16)NVM_PRV_BLOCK_REQ_MAINTAIN) != 0u)
    {
        // Multiblock maintenance request pending
        // -> acknowledge this request
        // Concurrency note: NvM_Prv_Main_st.isMultiBlockActive_rAMwM_b is still set so
        //                   NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] cannot be written concurrently
        //                   by a multiblock API
        //                -> no locking necessary here
        NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] &= (uint16)(~((uint16)NVM_PRV_BLOCK_REQ_MAINTAIN));
        // The request result of block #0 is already set to PENDING when the maintenance operations starts
        // NvM_Prv_Main_st.stFinalMultiBlockResult_rMwM_u8 is not used for the maintenance operation
        NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK;
        // Start the maintenance with block #1/#2 if dynamic config is enabled/disabled
        NvM_Prv_Main_st.idActiveBlockMulti_rMwM_u16 = (NvM_BlockIdType) NVM_CFG_FIRST_USED_BLOCK - 1u;

        // Second pass of multiblock operations needed
        isSecondPassNeeded_b = TRUE;
    }
    else
#endif
    {
        // Nothing more to be done for this multiblock operation
        isSecondPassNeeded_b = FALSE;
    }

    // Return whether a second pass of multiblock operations is needed
    return isSecondPassNeeded_b;
}

// ====================================================================================================================

/**
 * This function returns the service ID of the required multiblock request.
 *
 * Passed parameter MultiBlockRequest_uo is a bit field where each bit corresponds to a multiblock request.
 * and this function maps set bits to a service ID.
 *
 * \attention
 * Only one bit may be set in the passed parameter. If more than 1 bit is set this function returns 0.
 * The caller has to make sure that only 1 bit is set in passed parameter.
 *
 * \param[in] MultiBlockRequest_uo
 * Bit field with only 1 bit set for required multiblock request.
 */
LOCAL_INLINE NvM_Prv_idService_tuo NvM_Prv_GetServiceMultiBlock(uint16 MultiBlockRequest_uo)
{
    NvM_Prv_idService_tuo idService_uo;

    switch (MultiBlockRequest_uo)
    {
        case NVM_PRV_BLOCK_REQ_READ_ALL:
        {
            // Multiblock read request pending
            idService_uo = NVM_SERVICE_ID_READ_ALL;
        }
        break;

        case NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT:
        case NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE:
        {
            // Multiblock request to remove all non-resistant blocks after ReadAll or
            // initilization of blocks upon layout change
            idService_uo = NVM_SERVICE_ID_RB_INIT_AFTER_READ_ALL;
        }
        break;

        case NVM_PRV_BLOCK_REQ_WRITE_ALL:
        {
            // Multiblock write request pending
            idService_uo = NVM_SERVICE_ID_WRITE_ALL;
        }
        break;

        case NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL:
        {
            // Multiblock initialization request pending
            idService_uo = NVM_SERVICE_ID_RB_FIRST_INIT_ALL;
        }
        break;

        case NVM_PRV_BLOCK_REQ_MAINTAIN:
        {
            // Multiblock request to maintain redundant blocks
            idService_uo = NVM_PRV_BLOCK_REQ_MAINTAIN;
        }
        break;

        case NVM_PRV_BLOCK_REQ_VALIDATE_ALL:
        {
            // Multiblock validate request pending
            idService_uo = NVM_SERVICE_ID_VALIDATE_ALL;
        }
        break;

        default:
        {
            // Either an unknown bit set or 2 bits set.
            // In both cases no multiblock request may be started and returning 0 will kill unknown request
            // or 2 illegal multiblock requests.
            idService_uo = 0;
        }
        break;
    }

    return idService_uo;
}

// ====================================================================================================================

/**
 * This function returns the ID of the first block to be processed during passed multiblock service.
 *
 * All multiblock requests starts execution with block containing configuration ID (1).
 * Only WriteAll multiblock request starts execution with first user block (2).
 *
 * \attention
 * The returned block ID is decremented by 1. The reason for it is the weird implementation of the whlie-loop
 * in MainFunctionArbitrate.

 *
 * \param idService_uo
 * ID of the service for which the first block is required.
 */
LOCAL_INLINE NvM_BlockIdType NvM_Prv_GetFirstBlockForMultiBlockRequest(NvM_Prv_idService_tuo idService_uo)
{
    // Exception to NVM244: Start with block 1 if dynamic configuration is enabled (more efficient implementation)
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2830] Start with block 1 if dynamic configuration is enabled
    NvM_BlockIdType idBlockType_uo = (NvM_BlockIdType)(NVM_CFG_FIRST_USED_BLOCK - 1u);

    if (NVM_SERVICE_ID_WRITE_ALL == idService_uo)
    {
        // TRACE[NVM733] Start with block 2
        idBlockType_uo = (NvM_BlockIdType)(NVM_RB_FIRST_USER_BLOCK - 1u);
    }

    return idBlockType_uo;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
