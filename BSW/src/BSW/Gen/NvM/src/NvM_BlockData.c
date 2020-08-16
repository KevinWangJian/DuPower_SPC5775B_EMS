

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "NvM.h"

#include "NvM_Prv_BlockData.h"

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */
// Administrative block (as separate arrays for memory mapping, debugging, and struct packing reasons)
// TRACE[NVM134]

#define NVM_START_SEC_VAR_SAVED_ZONE_8
#include "NvM_MemMap.h"
/**
 * Global private array of bit-fields which represents the current attribute/status informations of each NVRAM-block.
 * This part of administrative data is located in saved zone RAM due to requirements for quick RAM initialization.
 * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2786]
 *
 * The current state is part of administrative-block as it is required by AUTOSAR.
 * Following states are combined here as a bit-field:
 * - bit 0 = state of the block validness (access mask = NVM_BLOCK_STATE_RAM_VALID)
 *   TRACE[NVM128]
 *   TRACE[NVM132]
 *   TRACE[NVM133]
 * - bit 1 = state of the block change (access mask = NVM_BLOCK_STATE_RAM_CHANGED)
 *   TRACE[NVM344]
 *   TRACE[NVM345]
 *   TRACE[NVM696]
 *   TRACE[NVM472]
 * - bit 2 = state of the WriteAll trigger (access mask = NVM_RB_BLOCK_STATE_MASK_TRG_WRITEALL)
 *   TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2978]
 * - bit 3 = state of the block write protection (access mask = NVM_BLOCK_STATE_WRITE_PROT)
 *   TRACE[NVM054]
 * - bits 4-7 not used
 *
 * TRACE[NVM134]
 * TRACE[NVM135]
 */
uint8 NvM_Prv_stBlock_rAwAM_au8[NVM_PRV_NR_BLOCKS_ADMIN];

#define NVM_STOP_SEC_VAR_SAVED_ZONE_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"
/**
 * Global private array of bit-fields which represents all requests pending on each NVRAM-block.
 *
 * Pending requests are part of administrative-block as it is required by AUTOSAR.
 * There are user initiated requests and internally initiated requests.
 * Mapping of pending requests to single bits is defined as follows:
 * - bit  0 = user request ReadAll
 *            (access mask = NVM_PRV_BLOCK_REQ_READ_ALL)
 * - bit  1 = internal request to remove non-resistant blocks after ReadAll
 *            (access mask = NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT)
 * - bit  2 = user request WriteAll
 *            (access mask = NVM_PRV_BLOCK_REQ_WRITE_ALL)
 * - bit  3 = user request FirstInitAll
 *            (access mask = NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL)
 * - bit  4 = internal request to maintain redundant blocks
 *            (access mask = NVM_PRV_BLOCK_REQ_MAINTAIN)
 * - bit  5 = internal request to initialize blocks upon layout change
 *            (access mask = NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE)
 * - bit  6 = user request ValidateAll
 *            (access mask = NVM_PRV_BLOCK_REQ_VALIDATE_ALL)
 * - bit  7 = not used
 * - bit  8 = user request ReadBlock
 *            (access mask = NVM_PRV_BLOCK_REQ_READ)
 * - bit  9 = user request WriteBlock
 *            (access mask = NVM_PRV_BLOCK_REQ_WRITE)
 * - bit 10 = user request RestoreBlock
 *            (access mask = NVM_PRV_BLOCK_REQ_RESTORE)
 * - bit 11 = user request InvalidateBlock
 *            (access mask = NVM_PRV_BLOCK_REQ_INVALIDATE)
 * - bit 12 = user request EraseBlock
 *            (access mask = NVM_PRV_BLOCK_REQ_ERASE)
 *
 * TRACE[NVM134]
 */
uint16 NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_NR_BLOCKS_ADMIN];
#define NVM_STOP_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
/**
 * Global private array with results of last request for each NVRAM-block.
 *
 * Request results are part of administrative-block as it is required by AUTOSAR.
 * Following request results are defined:
 * - NVM_REQ_OK                (0) = Last asynchronous request finished successfully
 * - NVM_REQ_NOT_OK            (1) = Last asynchronous request finished unsuccessfully
 * - NVM_REQ_PENDING           (2) = An asynchronous request is currently pending
 * - NVM_REQ_INTEGRITY_FAILED  (3) = Data integrity failure for last read operation
 * - NVM_REQ_BLOCK_SKIPPED     (4) = Referenced block skipped in NvM_ReadAll or NvM_WriteAll
 * - NVM_REQ_NV_INVALIDATED    (5) = Referenced block invalidated
 * - NVM_REQ_CANCELED          (6) = Multiblock write request canceled
 * - NVM_REQ_REDUNDANCY_FAILED (7) = Required redundancy of the referenced block lost
 * - NVM_REQ_RESTORED_FROM_ROM (8) = Referenced block restored from ROM
 *
 * TRACE[NVM134]
 * TRACE[NVM136]
 */
NvM_RequestResultType NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_NR_BLOCKS_ADMIN];
/**
 * Global private array with indexes of the dataset blocks to get data from the corresponding data array.
 *
 * Request results are part of administrative-block as it is required by AUTOSAR.
 * TRACE[NVM134]
 * TRACE[NVM144]
 * TRACE[NVM160]
 */
uint8 NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_NR_BLOCKS_ADMIN];
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

/*
 **********************************************************************************************************************
 * Code
 **********************************************************************************************************************
*/
#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

/**
 * \brief
 * This function returns the type of NVRAM storage for given block.
 * \details
 * If passed block ID is invalid then this function returns NVM_BLOCK_NATIVE.
 *
 * \param BlockId
 * Block ID for which the type of NVRAM storage shall be returned.
 * \param[global in] NvM_Prv_BlockDescriptors_acst
 * Global constant NVRAM block descriptor table from which this function gets the NVRAM storage type.
 *
 * \return
 * NVRAM storage type for given block.
 *
 * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3169]
 */
NvM_BlockManagementType NvM_Rb_GetBlockType(NvM_BlockIdType BlockId)
{
    NvM_BlockManagementType BlockType_uo = NVM_BLOCK_NATIVE;

    if ((BlockId >= NVM_CFG_FIRST_USED_BLOCK) && (BlockId < NVM_CFG_NR_BLOCKS))
    {
        BlockType_uo = NvM_Prv_BlockDescriptors_acst[BlockId].BlockManagementType_en;
    }

    return BlockType_uo;
}
/**
 * \brief
 * This function returns whether the initialization at layout change is enqueued into the queue
 * for multi block requests but is not yet in progress.
 *
 * \param[global in] NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK]
 * Element of the global array which contains all pending multi block requests.
 *
 * \return
 * Information whether the initialization at layout change is enqueued:
 * - TRUE = initialization at layout change is enqueued and NOT in progress
 * - FALSE = initialization at layout change is NOT enqueued or is already in progress
 *
 * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3167]
 */
boolean NvM_Rb_IsInitAtLayoutChangeEnqueued(void)
{
    return ((NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_MULTI_BLOCK] &
            (uint16)NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE) != 0u);
}
/**
 * \brief
 * This function returns whether a block is selected for initialization at layout change.
 * \details
 * If passed block ID is invalid then this function returns FALSE, i.e. a block with invalid ID is never selected
 * for initialization at layout change.
 *
 * \param BlockId
 * Block ID for which the selection status for initialization at layout change shall be returned.
 * \param[global in] NvM_Prv_BlockDescriptors_acst
 * Global constant NVRAM block descriptor table from which this function gets the selection status.
 *
 * \return
 * Selection status for initialization at layout:
 * - TRUE = given block is selected for initialization at layout change
 * - FALSE = given block is NOT selected for initialization at layout change
 *
 * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3164]
 */
boolean NvM_Rb_IsBlockSelectedForInitAtLayoutChange(NvM_BlockIdType BlockId)
{
    boolean isBlockSelected_b = FALSE;

    if ((BlockId >= NVM_CFG_FIRST_USED_BLOCK) && (BlockId < NVM_CFG_NR_BLOCKS))
    {
        isBlockSelected_b = (NvM_Prv_BlockDescriptors_acst[BlockId].stFlags_u16 &
                             (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_INIT_AT_LAYOUT_CHANGE) != 0u;
    }
    return isBlockSelected_b;
}
/**
 * \brief
 * This function returns whether a block is selected for first initialization.
 * \details
 * If passed block ID is invalid then this function returns FALSE, i.e. a block with invalid ID is never selected
 * for first initialization.
 *
 * \param BlockId
 * Block ID for which the selection status for first initialization shall be returned.
 * \param[global in] NvM_Prv_BlockDescriptors_acst
 * Global constant NVRAM block descriptor table from which this function gets the selection status.
 *
 * \return
 * Selection status for first initialization:
 * - TRUE = given block is selected for first initialization
 * - FALSE = given block is NOT selected for first initialization
 *
 * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3162]
 */
boolean NvM_Rb_IsBlockSelectedForFirstInitAll(NvM_BlockIdType BlockId)
{
    boolean isBlockSelected_b = FALSE;

    if ((BlockId >= NVM_CFG_FIRST_USED_BLOCK) && (BlockId < NVM_CFG_NR_BLOCKS))
    {
        isBlockSelected_b = (NvM_Prv_BlockDescriptors_acst[BlockId].stFlags_u16 &
                             (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_FIRST_INIT_ALL) != 0u;
    }
    return isBlockSelected_b;
}

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"
