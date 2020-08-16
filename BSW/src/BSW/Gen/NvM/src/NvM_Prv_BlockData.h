
#ifndef NVM_PRV_BLOCKDATA_H
#define NVM_PRV_BLOCKDATA_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */
// Definitions for giving special block IDs some semantics
// ------------------------------------------------------------------------------------------------
/**
 * Definition of the reserved block ID used for multi block operations.
 * TRACE[NVM471]
 */
#define NVM_PRV_MULTI_BLOCK         (0u)

#if (NVM_RB_AUX_INTERFACE == STD_ON)
/**
 * Definition of the block ID used for administrative information related to operations triggered by auxiliary users
 * (for this use case, an additional admin block has been reserved behind all "regular" admin blocks)
 */
# define NVM_PRV_AUX_ADMIN_BLOCK    NVM_CFG_NR_BLOCKS
#endif

/**
 * Definition of the immediate job priority for a NVRAM block.
 * TRACE[ECUC_NvM_00477]
 */
#define NVM_PRV_JOB_PRIORITY_IMMEDIATE      (0u)


/**
 * Definition of different bit masks to access different configuration flags withis block descriptors
 * Definition of bit masks as anonymous enumeration instead of several prepocessor defines is done
 * to get better structuring to show that all these bit masks belongs together.
 */
enum
{
    /// Bit mask definition to get information whether a block shall be processed during NvM_ReadAll.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[NVM117_Conf] Parameter NvMBlockDescriptor:NvMSelectBlockForReadAll
    NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL              = 0x0001,
    /// Bit mask definition to get information whether the block shall be processed during NvM_WriteAll.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[NVM549_Conf] Parameter NvMBlockDescriptor:NvMSelectBlockForWriteAll
    NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL             = 0x0002,
    /// Bit mask definition to get information whether the block shall be processed during NvM_Rb_FirstInitAll.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2828] Parameter NvMBlockDescriptor:NvMRbSelectBlockForFirstInitAll
    NVM_PRV_BLOCK_FLAG_SELECT_FOR_FIRST_INIT_ALL        = 0x0004,
    /// Bit mask definition to get information whether the block shall be initialized when a layout change is detected.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2881] Parameter NvMBlockDescriptor:NvMRbInitBlockAtLayoutChange
    NVM_PRV_BLOCK_FLAG_SELECT_FOR_INIT_AT_LAYOUT_CHANGE = 0x0008,
    /// Bit mask definition to get information whether the block is initially write protected.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[NVM033_Conf] Parameter NvMBlockDescriptor:NvMBlockWriteProt
    NVM_PRV_BLOCK_FLAG_WRITE_PROTECTED                  = 0x0010,
    /// Bit mask definition to get information whether the block shall be written only once.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[NVM072_Conf] Parameter NvMBlockDescriptor:NvMWriteBlockOnce
    NVM_PRV_BLOCK_FLAG_WRITE_ONCE                       = 0x0020,
    /// Bit mask definition to get information whether the block shall be resistant to block layout changes.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[NVM483_Conf] ParameterNvMBlockDescriptor:NvMResistantToChangedSw
    NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW          = 0x0040,
    /// Bit mask definition to get information whether the block shall use explicit synchronization mechanism.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[NVM519_Conf] Parameter NvMBlockDescriptor:NvMBlockUseSyncMechanism
    NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM               = 0x0080,
    /// Bit mask definition to get information whether the block shall be processed during NvM_ValidateAll.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[NVM557_Conf] Parameter NvMBlockDescriptor:NvMBlockUseAutoValidation
    NVM_PRV_BLOCK_FLAG_USE_AUTO_VALIDATION              = 0x0100,
    /// Bit mask definition to get information whether the block is using a variable block length.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2996] Parameter NvMBlockDescriptor:NvMRbNvBlockLengthString
    NVM_PRV_BLOCK_FLAG_USE_VARIABLE_BLOCK_LENGTH        = 0x0200,
    /// Bit mask definition to get information whether the block is configured for migration.
    /// This information is stored in the NVRAM block descriptor, see NvM_Prv_BlockDescriptor_tst.stFlags_u16
    /// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3027] Parameter NvMBlockDescriptor:NvMRbFirstReadDataMigration
    NVM_PRV_BLOCK_FLAG_SELECT_FOR_MIGRATION             = 0x0400
};

/**
 * Definition of different bit masks to access different request flags in the administrative blocks.
 * All these bits signal that the operation indicated by the name has been requested but did not start yet.
 * Definition of bit masks as anonymous enumeration instead of several prepocessor defines is done
 * to get better structuring to show that all these bit masks belongs together.
 */
enum
{
    /// Bit mask definition for ReadAll.
    NVM_PRV_BLOCK_REQ_READ_ALL              = 0x0001,
    /// Bit mask definition for InitAfterReadAll.
    NVM_PRV_BLOCK_REQ_REMOVE_NON_RESISTANT  = 0x0002,
    /// Bit mask definition for WriteAll.
    NVM_PRV_BLOCK_REQ_WRITE_ALL             = 0x0004,
    /// Bit mask definition for FirstInitAll.
    NVM_PRV_BLOCK_REQ_FIRST_INIT_ALL        = 0x0008,
    /// Bit mask definition for redundant block maintenance.
    NVM_PRV_BLOCK_REQ_MAINTAIN              = 0x0010,
    /// Bit mask definition for InitAtLayoutChange.
    NVM_PRV_BLOCK_REQ_INIT_AT_LAYOUT_CHANGE = 0x0020,
    /// Bit mask definition for ValidateAll.
    NVM_PRV_BLOCK_REQ_VALIDATE_ALL          = 0x0040,
    /// Bit mask definition for ReadBlock.
    NVM_PRV_BLOCK_REQ_READ                  = 0x0100,
    /// Bit mask definition for WriteBlock.
    NVM_PRV_BLOCK_REQ_WRITE                 = 0x0200,
    /// Bit mask definition for RestoreBlock.
    NVM_PRV_BLOCK_REQ_RESTORE               = 0x0400,
    /// Bit mask definition for InvalidateBlock.
    NVM_PRV_BLOCK_REQ_INVALIDATE            = 0x0800,
    /// Bit mask definition for EraseBlock.
    NVM_PRV_BLOCK_REQ_ERASE                 = 0x1000
};
/**
 * Bit mask definition any single-block request.
 */
#define NVM_PRV_BLOCK_REQ_ANY_SINGLE             ((uint16)NVM_PRV_BLOCK_REQ_READ        |   \
                                                  (uint16)NVM_PRV_BLOCK_REQ_WRITE       |   \
                                                  (uint16)NVM_PRV_BLOCK_REQ_RESTORE     |   \
                                                  (uint16)NVM_PRV_BLOCK_REQ_INVALIDATE  |   \
                                                  (uint16)NVM_PRV_BLOCK_REQ_ERASE)

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */
/**
 * Definition of the structure for common configuration options of the NvM used during the runtime.
 * TRACE[NVM028_Conf]
 */
typedef struct
{
    /**
     * Pointer to a callback function which shall be invoked on termination of each asynchronous multi-block request.
     * TRACE[NVM468]
     * TRACE[NVM331]
     * TRACE[NVM500_Conf] Parameter NvMCommon:NvMMultiBlockCallback
     */
    void (*MultiBlockCallback_pfct)(uint8 ServiceId, NvM_RequestResultType JobResult);
    /**
     * Pointer to a callback function which shall be invoked on start of each asynchronous multi-block request.
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2762] Parameter NvMCommon:NvMRbMultiBlockStartCallback
     */
    void (*RbMultiBlockStartCallback_pfct)(uint8 ServiceId);
    /**
     * Pointer to a callback function which shall be invoked on termination of each asynchronous single-block request.
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2842]
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2843] Parameter NvMCommon:NvMRbObserverCallback
     */
    Std_ReturnType (*ObserverCallback_pfct)(NvM_BlockIdType BlockId,
                                            uint8 ServiceId,
                                            NvM_RequestResultType JobResult);
} NvM_Prv_Common_tst;

/**
 * Definition of the structure for a NVRAM block descriptor.
 * A NVRAM block descriptor contains all information about a single NVRAM block needed during the runtime.
 * The NVRAM block descriptors are condensed in the NVRAM block descriptor table.
 * TRACE[NVM061_Conf]
 */
typedef struct
{
    /**
     * Block ID to be passed to the MemIf.
     * Do not confuse this ID with NVRAM block ID used within NvM.
     */
    uint16 idBlockMemIf_u16;
    /**
     * Pointer to the block legth in bytes.
     * If runtime calculation of block lengths is enabled by the NvM configuration then block lengths will be located
     * in RAM so pointer points to a variable with block length calculated during runtime.
     * Otherwise if runtime calculation is disabled by the NvM configuration then block legths will be located
     * in ROM so pointer points to a constant with block length configured during compile time.
     * TRACE[NVM479_Conf] Parameter NvMBlockDescriptor:NvMNvBlockLength
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3028] Parameter NvMCommon:NvMRbRuntimeRamBlockConfiguration
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2996] Parameter NvMBlockDescriptor:NvMRbNvBlockLengthString
     */
#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
    uint16* nrBlockBytes_pu16;
#else
    uint16 const* nrBlockBytes_pu16;
#endif
    /**
     * Device index where the block is located (Fee / Ea).
     * TRACE[NVM035_Conf] Parameter NvMBlockDescriptor:NvMNvramDeviceId
     */
    uint8 idxDevice_u8;
    /**
     * Number of non-volatile blocks in a contiguous area according to the given block management type.
     * TRACE[NVM480_Conf] Parameter NvMBlockDescriptor:NvMNvBlockNum
     */
    uint8 nrNvBlocks_u8;
    /**
     * Number of multiple ROM blocks in a contiguous area according to the given block management type.
     * TRACE[NVM485_Conf] Parameter NvMBlockDescriptor:NvMRomBlockNum
     */
    uint8 nrRomBlocks_u8;
    /**
     * Pointer to the permanent RAM block data.
     * If this pointer is NULL_PTR then no permanent RAM block data has been configured by the user.
     * If runtime calculation of RAM block data addresses is enabled by the NvM configuration
     * then RAM block data addresses will be located in RAM and pointer points to a void pointer
     * calculated during runtime.
     * Otherwise if runtime calculation is disabled by the NvM configuration then RAM block data addresses
     * will be located in ROM and pointer points to a constant void pointer configured during compile time.
     * TRACE[NVM126]
     * TRACE[NVM482_Conf] Parameter NvMBlockDescriptor:NvMRamBlockDataAddress
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3028] Parameter NvMCommon:NvMRbRuntimeRamBlockConfiguration
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3086] Parameter NvMBlockDescriptor:NvMRbRamBlockDataAddressString
     */
#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
    void** adrRamBlock_ppv;
#else
    void* const* adrRamBlock_ppv;
#endif
    /**
     * Pointer to the ROM block data.
     * If this pointer is NULL_PTR then no ROM block data has been configured by the user.
     * TRACE[NVM020]
     * TRACE[NVM484_Conf] Parameter NvMBlockDescriptor:NvMRomBlockDataAddress
     */
    void const* adrRomBlock_pcv;
    /**
     * Pointer to the block specific callback function which shall be invoked on termination
     * of each asynchronous single-block request.
     * If this pointer is NULL_PTR then no callback has been configured by the user.
     * TRACE[NVM113]
     * TRACE[NVM467]
     * TRACE[NVM330]
     * TRACE[NVM506_Conf] Parameter NvMBlockDescriptor:NvMSingleBlockCallback
     */
    Std_ReturnType (*SingleBlockCallback_pfct)(uint8 ServiceId, NvM_RequestResultType JobResult);
    /**
     * Pointer to the block specific callback function which shall be invoked on start
     * of each asynchronous single-block request.
     * If this pointer is NULL_PTR then no callback has been configured by the user.
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3056]
     * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3062] Parameter NvMBlockDescriptor:NvMRbSingleBlockStartCallback
     */
    Std_ReturnType (*SingleBlockStartCallback_pfct)(uint8 ServiceId);
    /**
     * Pointer to the block specific callback function which shall be invoked if no ROM block data is available
     * for initialization of the block.
     * If this pointer is NULL_PTR then no callback has been configured by the user.
     * TRACE[NVM469]
     * TRACE[NVM352]
     * TRACE[NVM116_Conf] Parameter NvMBlockDescriptor:NvMInitBlockCallback
     */
    Std_ReturnType (*InitBlockCallback_pfct)(void);
    /**
     * Pointer to the block specific callback function to let the application copy data from the NvM mirror
     * to application's RAM block.
     * If this pointer is NULL_PTR then no callback has been configured by the user.
     * TRACE[NVM540]
     * TRACE[NVM542]
     * TRACE[NVM521_Conf] Parameter NvMBlockDescriptor:NvMReadRamBlockFromNvCallback
     */
    Std_ReturnType (*ReadRamBlockFromNvm_pfct)(void* NvMBuffer);
    /**
     * Pointer the block specific callback function to let the application copy data from the application's RAM block
     * to the NvM mirror.
     * If this pointer is NULL_PTR then no callback has been configured by the user.
     * TRACE[NVM539]
     * TRACE[NVM541]
     * TRACE[NVM520_Conf] Parameter NvMBlockDescriptor:NvMWriteRamBlockToNvCallback
     */
    Std_ReturnType (*WriteRamBlockToNvm_pfct)(void* NvMBuffer);
    /**
     * Block management type.
     * TRACE[NVM062_Conf] Parameter NvMBlockDescriptor:NvMBlockManagementType
     */
    NvM_BlockManagementType BlockManagementType_en;
    /**
     * Block job priority.
     * TRACE[NVM477_Conf] Parameter NvMBlockDescriptor:NvMBlockJobPriority
     */
    uint8 JobPriority_u8;
    /**
     * Bit-field containing several configuration parameter which can be represented by a bit.
     * NvM provides special bit mask to access individual bits from this bit-field:
     * - NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL
     *   TRACE[NVM117_Conf] Parameter NvMBlockDescriptor:NvMSelectBlockForReadAll
     * - NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL
     *   TRACE[NVM549_Conf] Parameter NvMBlockDescriptor:NvMSelectBlockForWriteAll
     * - NVM_PRV_BLOCK_FLAG_SELECT_FOR_FIRST_INIT_ALL
     *   TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2828] Parameter NvMBlockDescriptor:NvMRbSelectBlockForFirstInitAll
     * - NVM_PRV_BLOCK_FLAG_SELECT_FOR_INIT_AT_LAYOUT_CHANGE
     *   TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2881] Parameter NvMBlockDescriptor:NvMRbInitBlockAtLayoutChange
     * - NVM_PRV_BLOCK_FLAG_WRITE_PROTECTED
     *   TRACE[NVM033_Conf] Parameter NvMBlockDescriptor:NvMBlockWriteProt
     * - NVM_PRV_BLOCK_FLAG_WRITE_ONCE
     *   TRACE[NVM072_Conf] Parameter NvMBlockDescriptor:NvMWriteBlockOnce
     * - NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW
     *   TRACE[NVM483_Conf] Parameter NvMBlockDescriptor:NvMResistantToChangedSw
     * - NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM
     *   TRACE[NVM519_Conf] Parameter NvMBlockDescriptor:NvMBlockUseSyncMechanism
     * - NVM_PRV_BLOCK_FLAG_USE_AUTO_VALIDATION
     *   TRACE[NVM557_Conf] Parameter NvMBlockDescriptor:NvMBlockUseAutoValidation
     * - NVM_PRV_BLOCK_FLAG_USE_VARIABLE_BLOCK_LENGTH
     *   TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2996] Parameter NvMBlockDescriptor:NvMRbNvBlockLengthString
     * - NVM_PRV_BLOCK_FLAG_SELECT_FOR_MIGRATION
     *   TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3027] Parameter NvMBlockDescriptor:NvMRbFirstReadDataMigration
     */
    uint16 stFlags_u16;

} NvM_Prv_BlockDescriptor_tst;

/**
 * Definition of the structure to assign the persistent ID to the block ID for a NVRAM block.
 */
typedef struct
{
    uint16          PersistentId_u16;   // Persistent Id
    NvM_BlockIdType BlockId_u16;        // Block Id
} NvM_Prv_PersId_BlockId_tst;

/*
 **********************************************************************************************************************
 * Constants
 **********************************************************************************************************************
 */
// Declaration of different configuration-dependent data.
// Definition of all this data is done in NvM_Cfg.c.
// ------------------------------------------------------------------------------------------------
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "NvM_MemMap.h"

/**
 * Declaration of the container with all common configuration data.
 * TRACE[NVM028_Conf]
 */
extern const NvM_Prv_Common_tst             NvM_Prv_Common_cst;
/**
 * Declaration of the NVRAM block descriptor table.
 * TRACE[NVM061_Conf]
 */
extern const NvM_Prv_BlockDescriptor_tst    NvM_Prv_BlockDescriptors_acst[NVM_CFG_NR_BLOCKS];
/**
 * Declaratiion of the table to get the NvM block ID using the persistent ID.
 */
extern const NvM_Prv_PersId_BlockId_tst     NvM_Prv_PersId_BlockId_acst[NVM_PRV_NR_PERSISTENT_IDS];
/**
 * Declaration of the table with all persistant IDs.
 */
extern const uint16                         NvM_Prv_PersIds_acu16[NVM_CFG_NR_BLOCKS];

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "NvM_MemMap.h"

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */
// Declaration of variables containing administrative data for all NVRAM blocks.
// ------------------------------------------------------------------------------------------------
// TRACE[NVM135] Administrative block is private
#define NVM_START_SEC_VAR_SAVED_ZONE_8
#include "NvM_MemMap.h"

/**
 * Declaration of the array containing attribute/status information of all NVRAM blocks.
 */
extern uint8 NvM_Prv_stBlock_rAwAM_au8[NVM_PRV_NR_BLOCKS_ADMIN];

#define NVM_STOP_SEC_VAR_SAVED_ZONE_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"

/**
 * Declaration of the array containing all requests pending on each NVRAM block.
 */
extern uint16 NvM_Prv_stRequests_rAMwAM_au16[NVM_PRV_NR_BLOCKS_ADMIN];

#define NVM_STOP_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

/**
 * Declaration of the array containing results of the last asynchronous request for all NVRAM blocks.
 */
extern NvM_RequestResultType NvM_Prv_stRequestResult_rAwAM_au8[NVM_PRV_NR_BLOCKS_ADMIN];
/**
 * Declaration of the array containing indexes for all NVRAM block.
 */
extern uint8 NvM_Prv_idxDataSet_rAMwA_au8[NVM_PRV_NR_BLOCKS_ADMIN];

#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
 */

/* NVM_PRV_BLOCKDATA_H */
#endif
