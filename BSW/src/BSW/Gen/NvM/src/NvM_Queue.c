

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
 * Constants
 **********************************************************************************************************************
*/

// Actual number of queue entries for the standard job queue (+ 1 due to implementation)
#define NVM_PRV_SIZE_STANDARD_JOB_QUEUE (NVM_SIZE_STANDARD_JOB_QUEUE + 1u)
#define NVM_PRV_SIZE_IMMEDIATE_JOB_QUEUE (NVM_SIZE_IMMEDIATE_JOB_QUEUE + 1u)

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

// Array of queue entries
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"
static NvM_Prv_BlockQueueEntry_tst NvM_Prv_StdRequestQueue_ast[NVM_PRV_SIZE_STANDARD_JOB_QUEUE];
#if (NVM_JOB_PRIORITIZATION == STD_ON)
static NvM_Prv_BlockQueueEntry_tst NvM_Prv_ImmRequestQueue_ast[NVM_PRV_SIZE_IMMEDIATE_JOB_QUEUE];
#endif
#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"

// Auxiliary queue
#if (NVM_RB_AUX_INTERFACE == STD_ON)
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2933] Auxiliary queue shall have only one entry
static NvM_Prv_BlockQueueEntry_tst NvM_Prv_AuxRequest_st;
#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"
#endif

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/

// Note: The queue is implemented as a regular circular/FIFO buffer. The distinction between an empty and completely
//       filled buffer is done by the "always keep one slot open" approach which is a bit faster than the "use a fill
//       count" approach at the expense of one additional buffer entry which is always empty.

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

NvM_Prv_QueueOpResult_ten NvM_Prv_QueueBlockRequest(uint8 idService_u8,
                                                    NvM_BlockIdType idBlock_u16,
                                                    uint8 *BlockData_pu8)
{
    NvM_Prv_QueueOpResult_ten stResult_en = NVM_PRV_QUEUE_OP_OK;

    // TRACE[NVM564] NvMJobPrioritization enables/disables immediate job processing
#if (NVM_JOB_PRIORITIZATION == STD_ON)
    // TRACE[NVM378] Only single block write requests for immediate blocks are queued in the immediate queue
    //               All other single block requests are queued in the standard queue.
    if ((NvM_Prv_BlockDescriptors_acst[idBlock_u16].JobPriority_u8 == NVM_PRV_JOB_PRIORITY_IMMEDIATE) &&
        (idService_u8 == NVM_SERVICE_ID_WRITE_BLOCK))
    {
        // Queue request in the immediate queue
        // ------------------------------------

        // Check whether the immediate queue is full
        uint16 idxNextHead = (NvM_Prv_idxBlockImmQueueHead_rAwA_u16 + 1u) % ((uint16) NVM_PRV_SIZE_IMMEDIATE_JOB_QUEUE);
        if (idxNextHead == NvM_Prv_idxBlockImmQueueTail_rAMwM_u16)
        {
            // Immediate queue is full
            // -> queueing another entry is not possible
            stResult_en = NVM_PRV_QUEUE_FULL;

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2815] Report a production error by setting the block error flag
            //                                               if a queueing is attempted and the queue is full
            NvM_Rb_stBlockErrors_au8[idBlock_u16] |= NVM_E_QUEUE_OVERFLOW;
            // Set write-protected error flag
            NvM_Rb_stBlockErrors_au8[NVM_PRV_MULTI_BLOCK] |= NVM_E_QUEUE_OVERFLOW;
        }
        else
        {
            // Immediate queue can take another entry
            // TRACE[NVM386] Put the request into the queue
            NvM_Prv_ImmRequestQueue_ast[NvM_Prv_idxBlockImmQueueHead_rAwA_u16].idService_u8 = idService_u8;
            NvM_Prv_ImmRequestQueue_ast[NvM_Prv_idxBlockImmQueueHead_rAwA_u16].idBlock_u16 = idBlock_u16;
            NvM_Prv_ImmRequestQueue_ast[NvM_Prv_idxBlockImmQueueHead_rAwA_u16].BlockData_pu8 = BlockData_pu8;
            NvM_Prv_idxBlockImmQueueHead_rAwA_u16 = idxNextHead;
            // Decrement the number of free entries after a successful enqueuing of the immediate queue
            NvM_Prv_nrFreeImmQueueEntries_wAwM_u8--;
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2809] Update the minimum number of immediate queue free entries
            if(NvM_Prv_nrFreeImmQueueEntries_wAwM_u8 < NvM_Rb_minNrFreeImmQueueEntries_u8)
            {
                NvM_Rb_minNrFreeImmQueueEntries_u8 = NvM_Prv_nrFreeImmQueueEntries_wAwM_u8;
            }
        }
    }
    else
#endif
    {
        // Queue request in the standard queue
        // -----------------------------------

        // Check whether the standard queue is full
        uint16 idxNextHead = (NvM_Prv_idxBlockStdQueueHead_rAwA_u16 + 1u) % ((uint16) NVM_PRV_SIZE_STANDARD_JOB_QUEUE);
        if (idxNextHead == NvM_Prv_idxBlockStdQueueTail_rAMwM_u16)
        {
            // Standard queue is full
            // -> queueing another entry is not possible
            stResult_en = NVM_PRV_QUEUE_FULL;

            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2815] Report a production error by setting the block error flag
            //                                               if a queueing is attempted and the queue is full
            NvM_Rb_stBlockErrors_au8[idBlock_u16] |= NVM_E_QUEUE_OVERFLOW;
            // Set write-protected error flag
            NvM_Rb_stBlockErrors_au8[NVM_PRV_MULTI_BLOCK] |= NVM_E_QUEUE_OVERFLOW;
        }
        else
        {
            // Standard queue can take another entry
            // TRACE[NVM386] Put the request into the queue
            NvM_Prv_StdRequestQueue_ast[NvM_Prv_idxBlockStdQueueHead_rAwA_u16].idService_u8 = idService_u8;
            NvM_Prv_StdRequestQueue_ast[NvM_Prv_idxBlockStdQueueHead_rAwA_u16].idBlock_u16 = idBlock_u16;
            NvM_Prv_StdRequestQueue_ast[NvM_Prv_idxBlockStdQueueHead_rAwA_u16].BlockData_pu8 = BlockData_pu8;
            NvM_Prv_idxBlockStdQueueHead_rAwA_u16 = idxNextHead;
            // Decrement the number of free entries after a successful enqueuing of the standard queue
            NvM_Prv_nrFreeStdQueueEntries_wAwM_u8--;
            // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2808] Update the minimum number of standard queue free entries
            if(NvM_Prv_nrFreeStdQueueEntries_wAwM_u8 < NvM_Rb_minNrFreeStdQueueEntries_u8)
            {
                NvM_Rb_minNrFreeStdQueueEntries_u8 = NvM_Prv_nrFreeStdQueueEntries_wAwM_u8;
            }
        }
    }

    return stResult_en;
}

NvM_Prv_QueueOpResult_ten NvM_Prv_UnqueueBlockRequest(uint8 idQueue_u8)
{
    NvM_Prv_QueueOpResult_ten stResult_en = NVM_PRV_QUEUE_OP_OK;

    // The following test is done even if job prioritization is disabled to avoid an "unused variable" compiler warning
    if (idQueue_u8 == NVM_PRV_IMMEDIATE_QUEUE)
    {
        // TRACE[NVM564] NvMJobPrioritization enables/disables immediate job processing
#if (NVM_JOB_PRIORITIZATION == STD_ON)
        // Unqueue request from the immediate queue
        // ----------------------------------------

        // Check whether the immediate queue is empty
        if (NvM_Prv_idxBlockImmQueueHead_rAwA_u16 == NvM_Prv_idxBlockImmQueueTail_rAMwM_u16)
        {
            // Immediate queue is empty
            // -> there is nothing to be unqueued
            stResult_en = NVM_PRV_QUEUE_EMPTY;
        }
        else
        {
            // Immediate queue has at least one entry
            // -> read the corresponding queue entry and advance the tail index
            NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NvM_Prv_ImmRequestQueue_ast[NvM_Prv_idxBlockImmQueueTail_rAMwM_u16].idService_u8;
            NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = NvM_Prv_ImmRequestQueue_ast[NvM_Prv_idxBlockImmQueueTail_rAMwM_u16].idBlock_u16;
            NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16;
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NvM_Prv_ImmRequestQueue_ast[NvM_Prv_idxBlockImmQueueTail_rAMwM_u16].BlockData_pu8;
            NvM_Prv_idxBlockImmQueueTail_rAMwM_u16 = (NvM_Prv_idxBlockImmQueueTail_rAMwM_u16 + 1u) % ((uint16) NVM_PRV_SIZE_IMMEDIATE_JOB_QUEUE);
            // Increment the number of free entries after a successful dequeuing of the immediate queue
            NvM_Prv_nrFreeImmQueueEntries_wAwM_u8++;
        }
#endif
    }
    else
    {
        // Unqueue request from the standard queue
        // ---------------------------------------

        // Check whether the standard queue is empty
        if (NvM_Prv_idxBlockStdQueueHead_rAwA_u16 == NvM_Prv_idxBlockStdQueueTail_rAMwM_u16)
        {
            // Standard queue is empty
            // -> there is nothing to be unqueued
            stResult_en = NVM_PRV_QUEUE_EMPTY;
        }
        else
        {
            // Standard queue has at least one entry
            // -> read the corresponding queue entry and advance the tail index
            NvM_Prv_Main_st.idActiveService_rAMwM_u8 = NvM_Prv_StdRequestQueue_ast[NvM_Prv_idxBlockStdQueueTail_rAMwM_u16].idService_u8;
            NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16 = NvM_Prv_StdRequestQueue_ast[NvM_Prv_idxBlockStdQueueTail_rAMwM_u16].idBlock_u16;
            NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16;
            NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8 = NvM_Prv_StdRequestQueue_ast[NvM_Prv_idxBlockStdQueueTail_rAMwM_u16].BlockData_pu8;
            NvM_Prv_idxBlockStdQueueTail_rAMwM_u16 = (NvM_Prv_idxBlockStdQueueTail_rAMwM_u16 + 1u) % ((uint16) NVM_PRV_SIZE_STANDARD_JOB_QUEUE);
            // Increment the number of free entries after a successful dequeuing of the standard queue
            NvM_Prv_nrFreeStdQueueEntries_wAwM_u8++;
        }
    }

    return stResult_en;
}

#if (NVM_RB_AUX_INTERFACE == STD_ON)
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2932] Own queue for auxiliary jobs
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2933] This queue has only one single entry
// Note: No "queue used/full" detection is necessary because enqueueing is done only if no aux request is pending or active
void NvM_Prv_QueueAuxBlockRequest(uint8 idService_u8, NvM_BlockIdType idBlock_u16, uint8 *BlockData_pu8)
{
    NvM_Prv_AuxRequest_st.idService_u8  = idService_u8;
    NvM_Prv_AuxRequest_st.idBlock_u16   = idBlock_u16;
    NvM_Prv_AuxRequest_st.BlockData_pu8 = BlockData_pu8;
}

void NvM_Prv_UnqueueAuxBlockRequest(void)
{
    NvM_Prv_Main_st.idActiveService_rAMwM_u8     = NvM_Prv_AuxRequest_st.idService_u8;
    NvM_Prv_Main_st.idActiveBlockCfg_rMwM_u16    = NvM_Prv_AuxRequest_st.idBlock_u16;
    NvM_Prv_Main_st.idActiveBlockAdmin_rAMwM_u16 = NVM_PRV_AUX_ADMIN_BLOCK;
    NvM_Prv_Main_st.adrActiveRamBlock_rMwM_pu8   = NvM_Prv_AuxRequest_st.BlockData_pu8;
}
#endif


#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"

/*<BASDKey>
 **********************************************************************************************************************
 * $History__:$
 **********************************************************************************************************************
 </BASDKey>*/
