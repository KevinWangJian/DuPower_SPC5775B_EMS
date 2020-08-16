

#ifndef NVM_PRV_H
#define NVM_PRV_H

#include "NvM_Prv_BlockData.h"
#include "NvM_Prv_ErrorDetection.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */

// Service IDs
// -----------

// Redundant block maintenance service ID
#define NVM_PRV_SERVICE_ID_MAINTAIN_BLOCK (249u)

// DET related macros
// ------------------

// Macro used to initialize the local DET error ID variable used in APIs
#define NVM_PRV_NO_DET_ERROR (0u)

// TRACE[NVM191] Development errors shall be reported to the Det_ReportError service
#if (NVM_DEV_ERROR_DETECT == STD_ON)
# define NVM_PRV_REPORT_DET_ERROR(ApiId, ErrorId)\
         (void) Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, (ApiId), (ErrorId));\
         NvM_Prv_Main_st.idLastDetErrorService_wAM_u8 = (ApiId);\
         NvM_Prv_Main_st.idLastDetError_wAM_u8 = (ErrorId)
#else
# define NVM_PRV_REPORT_DET_ERROR(ApiId, ErrorId)
#endif


// Miscellaneous
// -------------

// Queue identifiers
#define NVM_PRV_IMMEDIATE_QUEUE             (0u)
#define NVM_PRV_STANDARD_QUEUE              (1u)

// Magic value used with NvM_Prv_SavedZoneMarker_u32 to detect saved zone resets if NvMRbRamInitCheck is set to quick mode
#define NVM_PRV_SAVED_ZONE_MAGIC_VALUE      (0xABCDEFABuL)

/**
 * Maximum value for the number of written bytes, i.e. number of written bytes cannot exceed this value.
 */
#define NVM_PRV_NR_BYTES_WRITTEN_MAX_VALUE  (0xFFFFFFFFu)
/**
 * Maximum value for the accumulated number of all write requests,
 * i.e. number of written bytes cannot exceed this value.
 */
#define NVM_PRV_CNTR_WRITES_ABS_MAX_VALUE   (0xFFFFFFFFu)
/**
 * Maximum value for the number write requests since last power-on,
 * i.e. number of write requests cannot exceed this value.
 */
#define NVM_PRV_CNTR_WRITES_MAX_VALUE       (0xFFFFu)


/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */
// Enumeration of queue operation results
// TRACE[NVM507] This struct is only used for function-local data -> needs not to go to NvM_Types.h
typedef enum
{
    NVM_PRV_QUEUE_OP_OK = 0,    // Queue operation successful
    NVM_PRV_QUEUE_FULL,         // Queue operation failed because queue is full
    NVM_PRV_QUEUE_EMPTY         // Queue operation failed because queue is empty
} NvM_Prv_QueueOpResult_ten;

// Enumeration used for signalling the writing of the Config ID block
typedef enum
{
    NVM_PRV_DO_NOT_WRITE_CONFIG_ID,
    NVM_PRV_WRITE_CONFIG_ID_BLOCK_AFTER_READ_ALL,
    NVM_PRV_WRITE_CONFIG_ID_BLOCK_IN_WRITE_ALL
} NvM_Prv_ConfigIdBlockWriteTime_ten;

/// Type definition for services provided by NvM.
typedef uint8 NvM_Prv_idService_tuo;

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
 */
// Private code (defined in various NvM_*.c files)
// -----------------------------------------------

#define NVM_START_SEC_CODE
#include "NvM_MemMap.h"

// Main function sub-tasks (defined in NvM_MainFunction+.c)
extern void NvM_Prv_MainFunctionArbitrate(void);
extern void NvM_Prv_MainFunctionJobStart(void);
extern void NvM_Prv_MainFunctionPollResult(void);
extern void NvM_Prv_MainFunctionResultEval(void);

// Init-related functions (defined in NvM_Cfg.c)
#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
extern void NvM_Prv_InitRuntimeRamBlockProperties(void);
#endif

// Queue-related functions (defined in NvM_Queue.c)
extern NvM_Prv_QueueOpResult_ten NvM_Prv_QueueBlockRequest(uint8 idService_u8,
                                                           NvM_BlockIdType idBlock_u16,
                                                           uint8 *BlockData_pu8);
extern NvM_Prv_QueueOpResult_ten NvM_Prv_UnqueueBlockRequest(uint8 idQueue_u8);
#if (NVM_RB_AUX_INTERFACE == STD_ON)
extern void NvM_Prv_QueueAuxBlockRequest(uint8 idService_u8,
                                         NvM_BlockIdType idBlock_u16,
                                         uint8 *BlockData_pu8);
extern void NvM_Prv_UnqueueAuxBlockRequest(void);
#endif

#if (NVM_RB_REQ_MONITOR == NVM_RB_REQ_MON_WRITE)
extern void NvM_Prv_IncreaseWriteCounters(NvM_BlockIdType idBlock_uo,
                                          uint16 BlockLength_u16);
#endif

#define NVM_STOP_SEC_CODE
#include "NvM_MemMap.h"


// Private data (defined in NvM.c)
// -------------------------------

// TRACE[NVM506] Hint: All of the following variables are global and hence accessible via debugger
// TRACE[NVM508] The size of all the following variables can be determined via the standard C sizeof operator

// Common (i.e. not block-specific) states
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"
extern NvM_Prv_MainStates_tst NvM_Prv_Main_st;
#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
extern NvM_Rb_MigrationResult_ten NvM_Prv_AuxMigrationResult;
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
# define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
extern uint16 NvM_Prv_BlockLengths_au16[NVM_CFG_NR_BLOCKS];
extern void *NvM_Prv_RamBlockAdr_apv[NVM_CFG_NR_BLOCKS];
# define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
#else
# define NVM_START_SEC_CONST_UNSPECIFIED
# include "NvM_MemMap.h"
extern uint16 const NvM_Prv_BlockLengths_acu16[NVM_CFG_NR_BLOCKS];
extern void * const NvM_Prv_RamBlockAdr_acpv[NVM_CFG_NR_BLOCKS];
# define NVM_STOP_SEC_CONST_UNSPECIFIED
# include "NvM_MemMap.h"
#endif

// RAM mirror definition used in explicit synchronization
#if ((NVM_PRV_HAS_RAM_MIRROR == STD_ON) && (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_OFF))
# define NVM_START_SEC_VAR_CLEARED_8
# include "NvM_MemMap.h"
extern uint8 NvM_Prv_RamMirror_au8[NVM_PRV_SIZE_RAM_MIRROR];
# define NVM_STOP_SEC_VAR_CLEARED_8
# include "NvM_MemMap.h"
#elif ((NVM_PRV_HAS_RAM_MIRROR == STD_ON) && (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON))
#define BSW_START_SEC_VAR_CLEARED_32
#include "Bsw_MemMap.h"
extern uint8 *NvM_Prv_RamMirror_au8;
extern uint32 NvM_Prv_RntRamMirrorSize_u32;
#define BSW_STOP_SEC_VAR_CLEARED_32
#include "Bsw_MemMap.h"
#endif

// Variable used to check if saved zone is not lost after a reset
#if (NVM_RB_RAM_INIT_CHECK == NVM_RB_RAM_INIT_CHECK_QUICK)
# define NVM_START_SEC_VAR_SAVED_ZONE_32
# include "NvM_MemMap.h"
extern uint32 NvM_Prv_SavedZoneMarker_u32;
# define NVM_STOP_SEC_VAR_SAVED_ZONE_32
# include "NvM_MemMap.h"
#endif

// Dynamic configuration / Init at layout change variables
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
# define NVM_START_SEC_VAR_SAVED_ZONE_8
# include "NvM_MemMap.h"
extern boolean NvM_Prv_isConfigIdChanged_rMwM_b;
# define NVM_STOP_SEC_VAR_SAVED_ZONE_8
# include "NvM_MemMap.h"
#endif

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON))
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
//TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the potentially incompatible blocks after layout changes should be
//                                              sanitized by ReadAll at first
extern boolean NvM_Prv_isReadAllInitiated_b;
# define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
#endif

# define NVM_START_SEC_VAR_SAVED_ZONE_16
# include "NvM_MemMap.h"
extern uint16 NvM_Prv_idConfigStored_rMwM_u16;   // RAM block of the config ID block
# define NVM_STOP_SEC_VAR_SAVED_ZONE_16
# include "NvM_MemMap.h"

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
# define NVM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
# include "NvM_MemMap.h"
extern NvM_Prv_ConfigIdBlockWriteTime_ten NvM_Prv_ConfigIdBlockWriteTime_en;
# define NVM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
# include "NvM_MemMap.h"
#endif

// Queue head and tail indices
#define NVM_START_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"
extern uint16 NvM_Prv_idxBlockStdQueueHead_rAwA_u16;
extern uint16 NvM_Prv_idxBlockStdQueueTail_rAMwM_u16;
#if (NVM_JOB_PRIORITIZATION == STD_ON)
extern uint16 NvM_Prv_idxBlockImmQueueHead_rAwA_u16;
extern uint16 NvM_Prv_idxBlockImmQueueTail_rAMwM_u16;
#endif
#define NVM_STOP_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"

// Queue monitoring
#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
extern uint8 NvM_Prv_nrFreeStdQueueEntries_wAwM_u8;
# if (NVM_JOB_PRIORITIZATION == STD_ON)
extern uint8 NvM_Prv_nrFreeImmQueueEntries_wAwM_u8;
# endif
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "NvM_MemMap.h"
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Private variable to store block ID used in NvM service
//                                               which has caused the last DET error
extern NvM_BlockIdType NvM_Prv_idBlockCausingLastDetError_uo;
#define NVM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "NvM_MemMap.h"

/*
**********************************************************************************************************************
* Inline functions
**********************************************************************************************************************
*/

LOCAL_INLINE NvM_Prv_QueueOpResult_ten NvM_Prv_GetQueueState(uint8 idQueue_u8);
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the potentially incompatible blocks after layout changes should be
//                                               sanitized by ReadAll at first
LOCAL_INLINE boolean NvM_Prv_IsSanitizedByReadAll(uint16 stFlags_u16);
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] NvM private function to set block ID used in NvM service
//                                               which has caused the last DET error
LOCAL_INLINE void NvM_Prv_SetBlockIdCausingLastDetError(NvM_BlockIdType idBlock_uo);

LOCAL_INLINE NvM_Prv_QueueOpResult_ten NvM_Prv_GetQueueState(uint8 idQueue_u8)
{
    NvM_Prv_QueueOpResult_ten stResult_en = NVM_PRV_QUEUE_EMPTY;

    if (idQueue_u8 == NVM_PRV_IMMEDIATE_QUEUE)
    {
#if (NVM_JOB_PRIORITIZATION == STD_ON)
        // Check whether the immediate queue has entries
        if (NvM_Prv_idxBlockImmQueueHead_rAwA_u16 != NvM_Prv_idxBlockImmQueueTail_rAMwM_u16)
        {
            // Immediate queue has entries
            stResult_en = NVM_PRV_QUEUE_OP_OK;
        }
#endif
    }
    else
    {
        // Check whether the standard queue has entries
        if (NvM_Prv_idxBlockStdQueueHead_rAwA_u16 != NvM_Prv_idxBlockStdQueueTail_rAMwM_u16)
        {
            // Standard queue has entries
            stResult_en = NVM_PRV_QUEUE_OP_OK;
        }
    }
    return stResult_en;
}

/**
 * This function indicates whether a single block is sanitized or not by ReadAll after the layout changes.
 *
 * If the enhanced dynamic configuration is not activated, there is no need to sanitize the blocks, so the return
 * value is always TRUE.
 *
 * If the enhanced dynamic configuration is activated, after the layout changes, the blocks need to be sanitized
 * by ReadAll at first to avoid the incompatibility caused by changed layout. Therefore, before the ReadAll is
 * initiated, the single block requests which operate with Nv memory should not be accepted on the blocks, whose
 * compatiblility is not sanitized by the ReadAll. In this case, all of the blocks, which are chosen for ReadAll and
 * not resistant to changed software need to be sanitized by ReadAll. If they are not sanitized, the return value
 * is FALSE.
 *
 * \param[in] stFlags_u16
 * Variable shows special properties of this block, for example, whether the current block is chosen to ReadAll,
 * whether the current block is resistant to changed software and so on.
 *
 * \param[global in] NvM_Prv_isReadAllInitiated_b
 * Global variable shows whether NvM_ReadAll is already initiated or not.
 * TRUE:  the ReadAll is already initiated
 * FALSE: the ReadAll is not initiated yet
 *
 * \return
 * - TRUE:  If the enhanced dynamic configuration is activated,
 *          the current block is sanitized by ReadAll after the layout change.
 *          If the enhanced dynamic configuration is not activated,
 *          there is no need to sanitize the blocks in ReadAll, so the return value is always TRUE.
 * - FALSE: the current block is not sanitized by ReadAll after the layout change.
 *
 */
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the potentially incompatible blocks after layout changes should be
//                                               sanitized by ReadAll at first
LOCAL_INLINE boolean NvM_Prv_IsSanitizedByReadAll(uint16 stFlags_u16)
{
    //if the enhanced dynamic configuration is not activated, there is no incompatible problem for single blocks
    //therefore, the default return value is true
    boolean isReadAllInitiated_b = TRUE;

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON))
    //if the enhanced dynamic configuration is activated, check whether the current block has incompatible potential
    if (((stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL) != 0u) &&
        ((stFlags_u16 & (uint16)NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW) == 0u))
    {
        //if the current block is chosen as a block to ReadAll
        //and it is not resistant to changed software, then this block has incompatible potential,
        //it will check whether ReadAll is initiated, because the incompatible blocks should be sanitized by ReadAll.
        //if not, the single block requests(which operate on NV memory) on the current block will be blocked
        isReadAllInitiated_b = NvM_Prv_isReadAllInitiated_b;
    }
#else
    (void)stFlags_u16;
#endif

    return isReadAllInitiated_b;
}

/**
 * This function sets the block ID used in NvM service which has caused the last DET error.
 *
 * Everytime if a DET error has occured the NvM stores the block ID via this function.
 * If NvM service which has caused the last DET error does not use any block then pass 0 to this function.
 *
 * \param idBlock_uo
 * block ID used in NvM service which has caused the last DET error
 * \param[global in] NvM_Prv_idBlockCausingLastDetError_uo
 * Global variable to store block ID used in NvM service which has caused the last DET error
 */
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] NvM private function to set block ID used in NvM service
//                                               which has caused the last DET error
LOCAL_INLINE void NvM_Prv_SetBlockIdCausingLastDetError(NvM_BlockIdType idBlock_uo)
{
    NvM_Prv_idBlockCausingLastDetError_uo = idBlock_uo;
}

/* NVM_PRV_H */
#endif
