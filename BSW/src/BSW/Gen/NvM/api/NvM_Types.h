

// TRACE[NVM550] Header file specifying all public NvM types

#ifndef NVM_TYPES_H
#define NVM_TYPES_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "NvM_Cfg.h"   /*To get the value for generated  NVM_AR_RELEASE_MAJOR_VERSION */
#include "MemIf.h"
// TRACE[NVM089] Check version compatibility of included header files
#if (!defined(MEMIF_AR_RELEASE_MAJOR_VERSION) || (MEMIF_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
# error "AUTOSAR major version undefined or mismatched"
#endif

#if (!defined(MEMIF_AR_RELEASE_MINOR_VERSION) || ((MEMIF_AR_RELEASE_MINOR_VERSION != 0) && \
                                                      (MEMIF_AR_RELEASE_MINOR_VERSION != 2)))
# error "AUTOSAR minor version undefined or mismatched"
#endif

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */

// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3050] Enumeration for NvM migration status information
typedef enum
{
    NVM_RB_MIGRATION_RESULT_INIT_E              = 0,    // Initialization value, result not yet available
    NVM_RB_MIGRATION_RESULT_NOT_NECESSARY_E     = 1,    // RAM size == size on medium (migration not necessary)
    NVM_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E   = 2,    // RAM size < size on medium (remaining data discarded)
    NVM_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E    = 3,    // RAM size > size on medium (remaining data filled with zero)
    NVM_RB_MIGRATION_RESULT_NOT_DONE_E          = 4,    // Migration not done, because data were not read
    NVM_RB_MIGRATION_RESULT_DEACTIVATED_E       = 5     // Migrations is deactivated by configuration
}NvM_Rb_MigrationResult_ten;

// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2751] Enumeration for general NvM status information
typedef enum
{
    NVM_RB_STATUS_UNINIT = 0,   // NvM is not initialized yet
    NVM_RB_STATUS_IDLE = 1,     // NvM is currently idle
    NVM_RB_STATUS_BUSY = 2      // NvM is currently busy
} NvM_Rb_StatusType;

// TRACE[NVM137] Enumeration of block management types (public because the enum literal names are defined by AUTOSAR)
typedef enum
{
    NVM_BLOCK_NATIVE,     // TRACE[NVM557] Block is a standard block (no redundant storage, no dataset features)
    NVM_BLOCK_REDUNDANT,  // TRACE[NVM558] Like a native block, but with redundant storage on the memory media
    NVM_BLOCK_DATASET     // TRACE[NVM559] Allows several NV blocks and ROM blocks for one RAM block
} NvM_BlockManagementType;

// Enumeration of NvM activities
// TRACE[NVM507] Private type added to public NvM_Types.h to allow AUTOSAR debugging
typedef enum
{
    NVM_PRV_ACTIVITY_NOT_INIT = 0,  // NvM not initialized, job processing prohibited
    NVM_PRV_ACTIVITY_IDLE,          // Arbitrate incoming requests (last arbitration did not find any request)
    NVM_PRV_ACTIVITY_ARBITRATE,     // Arbitrate incoming requests (coming from a busy state)
    NVM_PRV_ACTIVITY_JOB_START,     // The job identified by NvM_Prv_Main_st.idActiveJob_rMwM_en shall be started
    NVM_PRV_ACTIVITY_POLL_RESULT,   // Wait for the termination of a MemIf job
    NVM_PRV_ACTIVITY_RESULT_EVAL    // Evaluate the result of an asynchronous operation
} NvM_Prv_Activities_ten;

// Enumeration of NvM-internal job IDs
// TRACE[NVM507] Private type added to public NvM_Types.h to allow AUTOSAR debugging
typedef enum
{
    NVM_PRV_JOB_ID_IDLE = 0,
    NVM_PRV_JOB_ID_READ,
    NVM_PRV_JOB_ID_WRITE,
    NVM_PRV_JOB_ID_INVALIDATE,
    NVM_PRV_JOB_ID_ERASE,
    NVM_PRV_JOB_ID_RESTORE,
    NVM_PRV_JOB_ID_MAINTAIN,
    NVM_PRV_JOB_ID_VALIDATE
} NvM_Prv_JobIds_ten;

/**
 * Definition of enumeration for the block request type.
 */
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3061] Enumeration for the block request type
typedef enum
{
    /// Block request type is not available, e.g. NvM not yet initialized.
    NvM_Rb_RequestType_NA_e     = 0,
    /// Multi block request is active.
    NvM_Rb_RequestType_Multi_e,
    /// Single block request is active.
    NvM_Rb_RequestType_Single_e

} NvM_Rb_RequestType_ten;

// Structure for holding all state information which is not block-specific
// (to have these variables gathered in one struct both optimizes resources and eases debugging)
// TRACE[NVM507] Private type added to public NvM_Types.h to allow AUTOSAR debugging
typedef struct
{
    // VARIABLES RELATED TO OVERALL STATE HANDLING:
    // CAUTION: These variables are not protected by SchM_Enter/Exit calls!
    // TRACE[NVM399] Flag indicating whether the NvM already has been initialized
    // TRACE[NVM510] This flag is available for debugging
    boolean                 isInitialized_rAM_b;
    // General NvM state
    NvM_Prv_Activities_ten  Activity_rAMwM_en;

    // VARIABLES RELATED TO BOTH SINGLE AND MULTI BLOCK OPERATIONS:
    // ID of the service which is currently ongoing (NVM_SERVICE_ID_INIT if no service is currently ongoing)
    uint8                   idActiveService_rAMwM_u8;
    // ID of the service which triggered the last Det_ReportError call within NvM (initialized to NVM_SERVICE_ID_INIT)
    uint8                   idLastDetErrorService_wAM_u8;
    // ID of the most previous error reported via Det_ReportError within NvM (initialized to NVM_PRV_NO_DET_ERROR)
    uint8                   idLastDetError_wAM_u8;

    // VARIABLES RELATED TO SINGLE BLOCK OPERATIONS (ALSO IF THEY ARE PART OF MULTI BLOCK OPERATIONS):
    // ID of the job which is currently ongoing (NVM_PRV_JOB_ID_IDLE if no job is currently ongoing)
    NvM_Prv_JobIds_ten      idActiveJob_rMwM_en;
    // ID of the block which is currently accessing the media (NvM ID, not MemIf ID; 0 if no access is currently ongoing)
    NvM_BlockIdType         idActiveBlockCfg_rMwM_u16;
    // Same as idActiveBlockCfg_rAMwM_u16 unless an auxiliary service is running (which uses its dedicated admin block)
    NvM_BlockIdType         idActiveBlockAdmin_rAMwM_u16;
    // Index of the currently active dataset
    uint8                   idxActiveDataset_rMwM_u8;
    // Pointer to the block data in RAM (destination for reads, source for writes)
    uint8 *                 adrActiveRamBlock_rMwM_pu8;
    // Variable that saves the result of the active job
    MemIf_JobResultType     stActiveJobResult_rMwM_en;

    // VARIABLES RELATED TO MULTI BLOCK OPERATIONS:
    // Flag indicating whether a multi block operation is currently active
    boolean                 isMultiBlockActive_rAMwM_b;
    // Flag indicating whether a multi block operation is currently suspended due to an immediate job
    boolean                 isMultiBlockServiceSuspended_rMwM_b;
    // ID of the block which is currently active as part of a multi block operation (0 if no multi block operation ongoing)
    NvM_BlockIdType         idActiveBlockMulti_rMwM_u16;
    // ID of the multiblock service which is currently suspended due to an immediate job (NVM_SERVICE_ID_INIT if no service is currently suspended)
    uint8                   idSuspendedService_rMwM_u8;
    // TRACE[NVM393] Separate variable for the final result of asynchronous multiblock requests
    NvM_RequestResultType   stFinalMultiBlockResult_rMwM_u8;
    // Variable used to check if WriteAll is cancelled
    boolean                 isWriteAllCanceled_rMwAM_b;

    // VARIABLES RELATED TO EXPLICIT SYNCHRONIZATION
    uint8                   cntrMirrorOperations_rMwM_u8;

} NvM_Prv_MainStates_tst;

// Structure for holding one single block queue entry
// TRACE[NVM507] Private type added to public NvM_Types.h to allow AUTOSAR debugging
typedef struct
{
    // Pointer to the buffer holding the block data
    // TRACE[NVM088] No assumptions can be made about alignment, hence a uint8 pointer
    uint8 *BlockData_pu8;

    // ID of the block for which an operation is requested
    NvM_BlockIdType idBlock_u16;

    // ID of the requested block service
    uint8 idService_u8;
} NvM_Prv_BlockQueueEntry_tst;

/* NVM_TYPES_H */
#endif
