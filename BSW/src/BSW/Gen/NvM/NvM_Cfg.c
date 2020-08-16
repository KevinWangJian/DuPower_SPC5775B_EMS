

// TRACE[NVM321]
// NvM file containing all configuration parameters which are to be implemented as constants

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "NvM.h"

#include "Rte_NvM.h"

#include "MemIf.h"
// TRACE[NVM089]
// Check version compatibility of included header files
#if (!defined(MEMIF_AR_RELEASE_MAJOR_VERSION) || (MEMIF_AR_RELEASE_MAJOR_VERSION != NVM_AR_RELEASE_MAJOR_VERSION))
    #error "AUTOSAR major version undefined or mismatched"
#endif

#if (!defined(MEMIF_AR_RELEASE_MINOR_VERSION) || ((MEMIF_AR_RELEASE_MINOR_VERSION != 0) && \
                                                      (MEMIF_AR_RELEASE_MINOR_VERSION != 2)))
# error "AUTOSAR minor version undefined or mismatched"
#endif

#include "NvM_Prv.h"

#include "Ea_Cfg.h"

// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2997]
// Include custumer/user specific declarations

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

// Single block callback of NVRAM block ECUM_CFG_NVM_BLOCK
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType EcuM_Rb_NvMSingleBlockCallbackFunction(uint8 ServiceId, NvM_RequestResultType JobResult);

// RAM block of NVRAM block ECUM_CFG_NVM_BLOCK
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern uint8 EcuM_Rb_dataShutdownInfo_st[];

// RAM block of NVRAM block NVDataBlock1
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern uint8 gaucNVData1[];

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_GenericNvData
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_GenericNVDataReadRamBlockFromNvCallback(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_GenericNvData
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_GenericNVDataWriteRamBlockToNvCallback(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_AllEventsStatusByte
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EventStatusByteReadRamBlockFromNvCallback(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_AllEventsStatusByte
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EventStatusByteWriteRamBlockToNvCallback(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory0
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback0(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory0
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback0(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory1
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback1(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory1
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback1(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory2
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback2(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory2
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback2(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory3
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback3(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory3
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback3(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory4
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback4(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory4
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback4(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory5
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback5(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory5
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback5(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory6
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback6(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory6
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback6(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory7
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback7(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory7
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback7(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory8
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback8(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory8
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback8(void* NvMBuffer);

// Explicit sync read callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory9
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback9(void* NvMBuffer);

// Explicit sync write callback of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory9
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback9(void* NvMBuffer);

// RAM block of NVRAM block DiagDataBlock1
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern uint8 DiagData1[];

// RAM block of NVRAM block EOLDataBlock
/* MR12 RULE 8.5 VIOLATION: If we declared this in NvM_Cfg.h,
                            we would effectively re-export this to all NvM users */
extern uint8 gaucEOLData[];

/*
 **********************************************************************************************************************
 * Constants
 **********************************************************************************************************************
*/

#define NVM_START_SEC_CONST_UNSPECIFIED
#include "NvM_MemMap.h"

// Array containing (persistent Id, block Id) couples sorted by ascendant persistent Ids
const NvM_Prv_PersId_BlockId_tst NvM_Prv_PersId_BlockId_acst[NVM_PRV_NR_PERSISTENT_IDS] =
{
    //{PersId, BlockId}
    {2, 3}, // NvMConf_NvMBlockDescriptor_NVDataBlock1
    {3, 16}, // NvMConf_NvMBlockDescriptor_DiagDataBlock1
    {123, 17}, // NvMConf_NvMBlockDescriptor_EOLDataBlock
    {4527, 10}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory4
    {5527, 11}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory5
    {6527, 12}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory6
    {7527, 13}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory7
    {8527, 14}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory8
    {8704, 4}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_GenericNvData
    {9527, 15}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory9
    {17922, 7}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory1
    {20411, 5}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_AllEventsStatusByte
    {22411, 6}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory0
    {25872, 9}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory3
    {29849, 8}, // NvMConf_NvMBlockDescriptor_NvMBlockDescriptor_Dem_EvMemEventMemory2
    {62203, 2}, // NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK
};

// TRACE[NVM028_Conf]
// Structure containing common configuration options
const NvM_Prv_Common_tst NvM_Prv_Common_cst = {NULL_PTR, NULL_PTR, NULL_PTR};

// TRACE[NVM061_Conf]
// Array containing block descriptors
// TRACE[NVM140]
// The block descriptor contents are completely determined by configuration
const NvM_Prv_BlockDescriptor_tst NvM_Prv_BlockDescriptors_acst[NVM_CFG_NR_BLOCKS] =
{
    {
        // Block descriptor of NVRAM block NvM_MultiBlock (NvM block ID: 0):
        0, // MemIf block ID (this block is not stored on any memory device)
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[0]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[0]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        NULL_PTR, // Explicit sync read callback
        NULL_PTR, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        0 // Block flags
    },
    {
        // Block descriptor of NVRAM block NvM_ConfigId (NvM block ID: 1):
        0, // MemIf block ID (this block is not stored on any memory device)
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[1]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[1]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        NULL_PTR, // Explicit sync read callback
        NULL_PTR, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        0 // Block flags
    },
    {
        // Block descriptor of NVRAM block ECUM_CFG_NVM_BLOCK (NvM block ID: 2, persistent ID: 62203):
        EaConf_EaBlockConfiguration_ECUM_CFG_NVM_BLOCK, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[2]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[2]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        &EcuM_Rb_NvMSingleBlockCallbackFunction, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        NULL_PTR, // Explicit sync read callback
        NULL_PTR, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NVDataBlock1 (NvM block ID: 3, persistent ID: 2):
        EaConf_EaBlockConfiguration_NVDataBlock1, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[3]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[3]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        &Rte_Call_NVDataBlock1_Finished_JobFinished, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        NULL_PTR, // Explicit sync read callback
        NULL_PTR, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_GenericNvData (NvM block ID: 4, persistent ID: 8704):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_GenericNvData, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[4]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[4]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_GenericNVDataReadRamBlockFromNvCallback, // Explicit sync read callback
        &Dem_GenericNVDataWriteRamBlockToNvCallback, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_AllEventsStatusByte (NvM block ID: 5, persistent ID: 20411):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_AllEventsStatusByte, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[5]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[5]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EventStatusByteReadRamBlockFromNvCallback, // Explicit sync read callback
        &Dem_EventStatusByteWriteRamBlockToNvCallback, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory0 (NvM block ID: 6, persistent ID: 22411):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory0, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[6]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[6]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback0, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback0, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory1 (NvM block ID: 7, persistent ID: 17922):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory1, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[7]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[7]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback1, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback1, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory2 (NvM block ID: 8, persistent ID: 29849):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory2, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[8]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[8]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback2, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback2, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory3 (NvM block ID: 9, persistent ID: 25872):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory3, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[9]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[9]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback3, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback3, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory4 (NvM block ID: 10, persistent ID: 4527):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory4, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[10]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[10]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback4, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback4, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory5 (NvM block ID: 11, persistent ID: 5527):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory5, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[11]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[11]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback5, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback5, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory6 (NvM block ID: 12, persistent ID: 6527):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory6, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[12]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[12]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback6, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback6, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory7 (NvM block ID: 13, persistent ID: 7527):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory7, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[13]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[13]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback7, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback7, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory8 (NvM block ID: 14, persistent ID: 8527):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory8, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[14]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[14]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback8, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback8, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory9 (NvM block ID: 15, persistent ID: 9527):
        EaConf_EaBlockConfiguration_NvMBlockDescriptor_Dem_EvMemEventMemory9, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[15]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[15]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        NULL_PTR, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        &Dem_EvMemNvmReadRamBlockFromNvCallback9, // Explicit sync read callback
        &Dem_EvMemNvMWriteRamBlockToNvCallback9, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_USE_SYNC_MECHANISM | NVM_PRV_BLOCK_FLAG_RESISTANT_TO_CHANGED_SW | NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block DiagDataBlock1 (NvM block ID: 16, persistent ID: 3):
        EaConf_EaBlockConfiguration_DiagDataBlock1, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[16]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[16]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        &Rte_Call_DiagDataBlock1_Finished_JobFinished, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        NULL_PTR, // Explicit sync read callback
        NULL_PTR, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
    {
        // Block descriptor of NVRAM block EOLDataBlock (NvM block ID: 17, persistent ID: 123):
        EaConf_EaBlockConfiguration_EOLDataBlock, // MemIf block ID
        (const uint16 *) &(NvM_Prv_BlockLengths_acu16[17]), // Block length calculated on compile time
        1, // Device index (0: Fee, 1..254: Ea)
        1, // Number of NV blocks
        0, // Number of ROM blocks
        (void * const *) &(NvM_Prv_RamBlockAdr_acpv[17]), // RAM block data address calculated on compile time
        (const void *) NULL_PTR, // ROM block data address
        &Rte_Call_EOLDataBlock_Finished_JobFinished, // Single block callback
        NULL_PTR, // Single block start callback
        NULL_PTR, // Initialization callback
        NULL_PTR, // Explicit sync read callback
        NULL_PTR, // Explicit sync write callback
        NVM_BLOCK_NATIVE, // Block management type
        1, // Job priority (0: Immediate, 1: Standard)
        NVM_PRV_BLOCK_FLAG_SELECT_FOR_READ_ALL | NVM_PRV_BLOCK_FLAG_SELECT_FOR_WRITE_ALL // Block flags
    },
};

// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3028]
// Runtime Calculation feature disabled
#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_OFF)
// Used to calculate the NV block lengths on compile time
// This variable is mapped into the block descriptor NvM_Prv_BlockDescriptors_acst
const uint16 NvM_Prv_BlockLengths_acu16[NVM_CFG_NR_BLOCKS] =
{
    // Block length of NVRAM block NvM_MultiBlock (NvM block ID: 0)
    1,
    // Block length of NVRAM block NvM_ConfigId (NvM block ID: 1)
    2,
    // Block length of NVRAM block ECUM_CFG_NVM_BLOCK (NvM block ID: 2)
    8,
    // Block length of NVRAM block NVDataBlock1 (NvM block ID: 3)
    1024,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_GenericNvData (NvM block ID: 4)
    16,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_AllEventsStatusByte (NvM block ID: 5)
    208,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory0 (NvM block ID: 6)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory1 (NvM block ID: 7)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory2 (NvM block ID: 8)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory3 (NvM block ID: 9)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory4 (NvM block ID: 10)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory5 (NvM block ID: 11)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory6 (NvM block ID: 12)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory7 (NvM block ID: 13)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory8 (NvM block ID: 14)
    164,
    // Block length of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory9 (NvM block ID: 15)
    164,
    // Block length of NVRAM block DiagDataBlock1 (NvM block ID: 16)
    512,
    // Block length of NVRAM block EOLDataBlock (NvM block ID: 17)
    2048,
};
// Used to calculate the RAM block data addresses on compile runtime
// This variable is mapped into the block descriptor NvM_Prv_BlockDescriptors_acst
void * const NvM_Prv_RamBlockAdr_acpv[NVM_CFG_NR_BLOCKS] =
{
    // Permanent RAM address of NVRAM block NvM_MultiBlock (NvM block ID: 0)
    (void *) NULL_PTR,
    // Permanent RAM address of NVRAM block NvM_ConfigId (NvM block ID: 1)
    (void *) NULL_PTR,
    // Permanent RAM address of NVRAM block ECUM_CFG_NVM_BLOCK (NvM block ID: 2)
    (void *) &(EcuM_Rb_dataShutdownInfo_st),
    // Permanent RAM address of NVRAM block NVDataBlock1 (NvM block ID: 3)
    (void *) &(gaucNVData1),
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_GenericNvData (NvM block ID: 4)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_AllEventsStatusByte (NvM block ID: 5)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory0 (NvM block ID: 6)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory1 (NvM block ID: 7)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory2 (NvM block ID: 8)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory3 (NvM block ID: 9)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory4 (NvM block ID: 10)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory5 (NvM block ID: 11)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory6 (NvM block ID: 12)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory7 (NvM block ID: 13)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory8 (NvM block ID: 14)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block NvMBlockDescriptor_Dem_EvMemEventMemory9 (NvM block ID: 15)
    (void *) NvM_Prv_RamMirror_au8,
    // Permanent RAM address of NVRAM block DiagDataBlock1 (NvM block ID: 16)
    (void *) &(DiagData1),
    // Permanent RAM address of NVRAM block EOLDataBlock (NvM block ID: 17)
    (void *) &(gaucEOLData),
};
#endif

#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "NvM_MemMap.h"
/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/

// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3028]
// Runtime Calculation feature enabled
#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
# define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
// Used to calculate the NV block lengths and RAM block data addresses on runtime
// These variables are mapped into the block descriptor NvM_Prv_BlockDescriptors_acst
uint16 NvM_Prv_BlockLengths_au16[NVM_CFG_NR_BLOCKS];
void *NvM_Prv_RamBlockAdr_apv[NVM_CFG_NR_BLOCKS];
# define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
#endif

/*
 **********************************************************************************************************************
 * Functions
 **********************************************************************************************************************
*/
#if (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON)
# define NvM_START_SEC_CODE
# include "NvM_MemMap.h"
/********************************************************************************************
 * Initialization of NV block length and RAM block data address (permanent RAM address)     *
 *                                                                                          *
 * In this case NvMRbRuntimeRamBlockConfiguration is enabled                                *
 * + NV block length is defined either by NvMRbNvBlockLengthString or NvMNvBlockLength      *
 * + RAM block data address is still defined by NvMRamBlockDataAddress but now              *
 *   NvMRamBlockDataAddress can also contain C expressions                                  *
 *                                                                                          *
 * Furthermore if explicit sync feature is enabled the explicit sync buffer is defined here *
 * by setting the start address and calculating the buffer size                             *
 * Start address and end address is defined by user in common options with the parameters   *
 * + NvMRbRuntimeRamBufferAddressStart                                                      *
 * + NvMRbRuntimeRamBufferAddressEnd                                                        *
 *                                                                                          *
 * ******************************************************************************************
*/
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3028]
// Runtime Calculation feature enabled
void NvM_Prv_InitRuntimeRamBlockProperties(void)
{
#if (NVM_PRV_HAS_RAM_MIRROR == STD_ON)
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3029] Calculate explicit synchronization RAM buffer
    // TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3030] Calculate explicit synchronization RAM buffer
    // Set explicit synchronization RAM buffer start address
    NvM_Prv_RamMirror_au8        = (uint8 *) (0);
    // Calculate explicit synchronization RAM buffer size
    NvM_Prv_RntRamMirrorSize_u32 = (uint32) (0) - (uint32) (0);
#endif


}
# define NVM_STOP_SEC_CODE
# include "NvM_MemMap.h"
#endif
