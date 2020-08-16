

// TRACE[NVM076] NvM module's main C file containing module-wide variables; the actual NvM code is in NvM_*.c

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
 * Variables
 **********************************************************************************************************************
 */

// Public
// ------

// Variable saving blocks' errors (useful for debugging)
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2811] public block specific production error array
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2812] public summary production errors' variable (index # 0)
#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_Rb_stBlockErrors_au8[NVM_CFG_NR_BLOCKS];
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

// Queue monitoring
#define NVM_START_SEC_VAR_SAVED_ZONE_8
#include "NvM_MemMap.h"
uint8 NvM_Rb_minNrFreeStdQueueEntries_u8;
# if (NVM_JOB_PRIORITIZATION == STD_ON)
uint8 NvM_Rb_minNrFreeImmQueueEntries_u8;
# endif
#define NVM_STOP_SEC_VAR_SAVED_ZONE_8
#include "NvM_MemMap.h"

// Private
// -------

// Common (i.e. not block-specific) states
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"
/**
 * Global NvM state information which is not block-specific.
 */
NvM_Prv_MainStates_tst NvM_Prv_Main_st;
#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
/**
 * TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3027]
 * Special handling for aux migration result
 *
 * Following request results are defined:
 * NVM_RB_MIGRATION_RESULT_INIT_E              (0) =   Initialization value, result not yet available
 * NVM_RB_MIGRATION_RESULT_NOT_NECESSARY_E     (1) =   RAM size == size on medium
 * NVM_RB_MIGRATION_RESULT_TO_SMALLER_SIZE_E   (2) =   RAM size < size on medium (remaining data discarded)
 * NVM_RB_MIGRATION_RESULT_TO_BIGGER_SIZE_E    (3) =   RAM size > size on medium (remaining data filled with zero)
 * NVM_RB_MIGRATION_RESULT_NOT_DONE_E          (4) =   Migration not done, because data were not read
 * NVM_RB_MIGRATION_RESULT_DEACTIVATED_E       (5) =   Migrations is deactivated by configuration
 */
NvM_Rb_MigrationResult_ten NvM_Prv_AuxMigrationResult;
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

// RAM mirror definition used in explicit synchronization
// TRACE[NVM512] No NvM mirror is allocated if no block uses explicit synchronization
// TRACE[NVM513] Only one mirror is allocated
#if ((NVM_PRV_HAS_RAM_MIRROR == STD_ON) && (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_OFF))
# define NVM_START_SEC_VAR_CLEARED_8
# include "NvM_MemMap.h"
uint8 NvM_Prv_RamMirror_au8[NVM_PRV_SIZE_RAM_MIRROR];
# define NVM_STOP_SEC_VAR_CLEARED_8
# include "NvM_MemMap.h"
#elif ((NVM_PRV_HAS_RAM_MIRROR == STD_ON) && (NVM_PRV_RUNTIME_RAM_BLOCK_CONFIG == STD_ON))
#define BSW_START_SEC_VAR_CLEARED_32
#include "Bsw_MemMap.h"
// Runtime RAM Block Configuration feature in combination with explicit synchronization needs definition of
// NvM mirror at runtime
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3028]
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3029]
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3030]
uint8 *NvM_Prv_RamMirror_au8;
uint32 NvM_Prv_RntRamMirrorSize_u32;
#define BSW_STOP_SEC_VAR_CLEARED_32
#include "Bsw_MemMap.h"
#endif

// Variable used to check if saved zone is not lost after a reset
#if (NVM_RB_RAM_INIT_CHECK == NVM_RB_RAM_INIT_CHECK_QUICK)
# define NVM_START_SEC_VAR_SAVED_ZONE_32
# include "NvM_MemMap.h"
uint32 NvM_Prv_SavedZoneMarker_u32;
# define NVM_STOP_SEC_VAR_SAVED_ZONE_32
# include "NvM_MemMap.h"
#endif

// Dynamic configuration / Init at layout change variables
#if (NVM_DYNAMIC_CONFIGURATION == STD_ON)
# define NVM_START_SEC_VAR_SAVED_ZONE_8
# include "NvM_MemMap.h"
boolean NvM_Prv_isConfigIdChanged_rMwM_b;
# define NVM_STOP_SEC_VAR_SAVED_ZONE_8
# include "NvM_MemMap.h"
#endif

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) && (NVM_RB_REMOVE_NON_RESISTANT_BLOCKS == STD_ON))
#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
//TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-2999] the potentially incompatible blocks after layout changes should be
//                                              sanitized by ReadAll at first
boolean NvM_Prv_isReadAllInitiated_b;
# define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "NvM_MemMap.h"
#endif

# define NVM_START_SEC_VAR_SAVED_ZONE_16
# include "NvM_MemMap.h"
uint16 NvM_Prv_idConfigStored_rMwM_u16;            // RAM block of the config ID block
# define NVM_STOP_SEC_VAR_SAVED_ZONE_16
# include "NvM_MemMap.h"

#if ((NVM_DYNAMIC_CONFIGURATION == STD_ON) || (NVM_RB_INIT_AT_LAYOUT_CHANGE == STD_ON))
# define NVM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
# include "NvM_MemMap.h"
NvM_Prv_ConfigIdBlockWriteTime_ten NvM_Prv_ConfigIdBlockWriteTime_en;
# define NVM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
# include "NvM_MemMap.h"
#endif

// Queue head and tail indices
#define NVM_START_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"
uint16 NvM_Prv_idxBlockStdQueueHead_rAwA_u16;
uint16 NvM_Prv_idxBlockStdQueueTail_rAMwM_u16;
#if (NVM_JOB_PRIORITIZATION == STD_ON)
uint16 NvM_Prv_idxBlockImmQueueHead_rAwA_u16;
uint16 NvM_Prv_idxBlockImmQueueTail_rAMwM_u16;
#endif
#define NVM_STOP_SEC_VAR_CLEARED_16
#include "NvM_MemMap.h"

// Queue monitoring
#define NVM_START_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"
uint8 NvM_Prv_nrFreeStdQueueEntries_wAwM_u8;
# if (NVM_JOB_PRIORITIZATION == STD_ON)
uint8 NvM_Prv_nrFreeImmQueueEntries_wAwM_u8;
# endif
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "NvM_MemMap.h"

#define NVM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "NvM_MemMap.h"
// TRACE[BSW_SWS_AR4_0_R2_NVRAMManager_Ext-3113] Private variable to store block ID used in NvM service
//                                               which has caused the last DET error
NvM_BlockIdType NvM_Prv_idBlockCausingLastDetError_uo;
#define NVM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "NvM_MemMap.h"

