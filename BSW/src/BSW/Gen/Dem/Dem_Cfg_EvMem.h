/********************************************************************************************************************/
/*                                                                                                                  */
/* TOOL-GENERATED SOURCECODE, DO NOT CHANGE                                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/

#ifndef DEM_CFG_EVMEM_H
#define DEM_CFG_EVMEM_H

#include "Dem_Cfg_Main.h"
#include "Dem_Cfg_DtcId.h"
#include "Dem_Cfg_Events.h"

/* ----------------------------------------------------------------------------
 Dynamic Configuration (BCT)
 ----------------------------------------------------------------------------
 */

/* Displacement Support */
#define DEM_CFG_EVMEM_DISPLACEMENT_SUPPORTED                 TRUE
/* definition of displacement strategies */
#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_AUTOSAR          1u
#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_FIFO             2u
#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_CUST             3u
#define DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_NONE             4u
/* event memory displacement strategy */
#define DEM_CFG_EVMEM_MEMORY_DISPLACEMENT_STRATEGY           DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_AUTOSAR
/* mirror memory displacement strategy */
#define DEM_CFG_EVMEM_MIRROR_DISPLACEMENT_STRATEGY           DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_AUTOSAR

/* Storage TestFailed */
#define DEM_CFG_EVMEM_STORAGE_TESTFAILED_SUPPORTED           FALSE

/* Status Byte Consistency Check Preference */
#define DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE_STATUS_BYTE_BLOCK    1u
#define DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE_EVENT_MEMORY         2u
#define DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE                      DEM_CFG_EVMEM_STATUS_BYTE_CONSISTENCY_PREFERENCE_STATUS_BYTE_BLOCK

/* Occurrence Counter Processing */
#define DEM_CFG_EVMEM_OCCCOUNTER_TRIGGER_STSMASK             0u

/* Support of Extended Data */
#define DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED                TRUE
#define DEM_CFG_EVMEM_EXTENDED_DATA_ON_MIRROR_SUPPORTED      FALSE
#define DEM_CFG_EVMEM_EXTENDED_DATA_ON_PASSED_SUPPORTED      FALSE
#define DEM_CFG_EVMEM_TRIGGER_ON_FDC_SUPPORTED               FALSE

/* Support of Freeze Frame Data */
#define DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED                 TRUE

/* Support of Test Failed This Failure Cycle */
#define DEM_CFG_EVMEM_TESTCOMPLETE_TFC_SUPPORTED             FALSE

/* Immediate NV Storage */
#define DEM_CFG_IMMEDIATE_NV_STORAGE_SUPPORTED               FALSE
#define DEM_CFG_IMMEDIATE_NV_STORAGE_LIMIT_SUPPORTED         FALSE
#define DEM_CFG_IMMEDIATE_NV_STORAGE_LIMIT                   0

/* Primary Memory */
#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY               10u

/* Secondary Memory */
#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY             0u

#define DEM_DTC_ORIGIN_USERDEFINED_MEMORY                    0x0u

/* Mirror Memory */
#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR                0u

/* Mirror Memory Type */
/* support of mirror memory method */
#define DEM_CFG_EVMEM_MIRROR_ON_FAILED                       1u
#define DEM_CFG_EVMEM_MIRROR_ON_CLEAR                        2u
#define DEM_CFG_EVMEM_MIRROR                                 DEM_CFG_EVMEM_MIRROR_ON_CLEAR
/* Mirror Memory Dtc Status */
#define DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED        FALSE

/* Shadow Memory */
#define DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED                FALSE
#define DEM_CFG_EVMEM_MEMID_SHADOW                           DEM_CFG_EVMEM_MEMID_PRIMARY
/* Shadow Entries */
#define DEM_CFG_EVMEM_SHADOW_ENTRIES_VISIBLE                 FALSE
/* support & time-stamp for shadow entries */
#if (DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED || DEM_CFG_EVMEM_SHADOW_ENTRIES_VISIBLE)
#define DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED               TRUE
#else
#define DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED               FALSE
#endif
#define DEM_CFG_EVMEM_SHADOW_ENTRIES_TIMEID_SUPPORTED        DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED

/* AgingCounter Type */
/* Aging counter method */
#define DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP                  1u
#define DEM_CFG_EVMEM_AGING_METHOD_COUNT_DOWN                2u
#define DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_STORE            3u
#define DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_UP          4u
#define DEM_CFG_EVMEM_AGING_METHOD_AGINGCYC_DIFF_DOWN        5u
#define DEM_CFG_EVMEM_AGING_METHOD_USER                      6u
/* support of aging counter for confirmed bit */
#define DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED                TRUE
#define DEM_CFG_EVMEM_AGING_METHOD                           DEM_CFG_EVMEM_AGING_METHOD_COUNT_UP
/* test failed this aging cycle supported */
#define DEM_CFG_EVMEM_TESTFAILED_TAC_SUPPORTED               FALSE
/* test complete this aging cycle supported */
#define DEM_CFG_EVMEM_TESTCOMPLETE_TAC_SUPPORTED             FALSE
/* aging counter max value (0x0001 ... 0xFFFF) */
#define DEM_CFG_EVMEM_AGING_COUNTER_MAX                      0xFF

/* OccurrenceCounter Type */
#define DEM_CFG_EVMEM_OCCURRENCE_COUNTER_SUPPORTED           TRUE

/* user defined storage & displacement strategy in event memory (primary and secondary) */
#define DEM_CFG_EVMEM_USERDEF_EVENT_MEM_STORAGE_STRATEGY     FALSE
/* user defined storage & displacement strategy in mirror memory */
#define DEM_CFG_EVMEM_USERDEF_MIRROR_MEM_STORAGE_STRATEGY    FALSE

/* reset confirmed bit on overflow in event memory */
#define DEM_CFG_EVMEM_RESET_CONFIRMED_BIT_ON_OVERFLOW        FALSE

#define DEM_CFG_EVMEM_PROJECT_EXTENSION                      FALSE

/* Enable additional synchronisation needed when event-related data is read synchronously from a different task */
#define DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK               FALSE

/* ----------------------------------------------------------------------------
 Debug Configuration
 ----------------------------------------------------------------------------
 */
#if (DEM_CFG_BUILDTARGET == DEM_CFG_BUILDTARGET_DEMTESTSUITE)
#define DEM_CFG_EVMEM_DEBUG_BITFIELDS                     TRUE
#else
#define DEM_CFG_EVMEM_DEBUG_BITFIELDS                     FALSE
#endif

/* ----------------------------------------------------------------------------
 Static Configuration (may be changed manually)
 ----------------------------------------------------------------------------
 */
/* Service ReadDtcInformation - Subfunction 0x03: ReportDtcSnapshot Information  */
#define DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x03      TRUE
/* Service ReadDtcInformation - Subfunction 0x04: ReportDtcSnapshotRecordByDtcNumber  */
#define DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x04      TRUE
/* Service ReadDtcInformation - Subfunction 0x06: ReportDtcExtendedDataByDtcNumber */
#define DEM_CFG_SERVICE_READDTCINFORMATION_SUBFUNC_0x06      TRUE

/* event search strategy (effective for type 2) first <--> most recent */
#define DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT                1u
#define DEM_CFG_EVMEM_EVENTSEARCH1_FIRST                     2u
#define DEM_CFG_EVMEM_EVENTSEARCH1                           DEM_CFG_EVMEM_EVENTSEARCH1_MOSTRECENT

/* occurrence counter max value (0x0001 ... 0xFFFF) */
#define DEM_CFG_EVMEM_OCCURRENCE_COUNTER_MAX                 0xFFu

/* NV Storage */
#define DEM_CFG_EVMEM_SHUTDOWN_NV_STORAGE_SUPPORTED          TRUE

/* ----------------------------------------------------------------------------
 NVRAM - Ids
 ----------------------------------------------------------------------------
 */
#define DEM_CFG_EVMEMNVMIDS \
{ \
   DEM_NVM_ID_EVMEM_LOC_0,\
   DEM_NVM_ID_EVMEM_LOC_1,\
   DEM_NVM_ID_EVMEM_LOC_2,\
   DEM_NVM_ID_EVMEM_LOC_3,\
   DEM_NVM_ID_EVMEM_LOC_4,\
   DEM_NVM_ID_EVMEM_LOC_5,\
   DEM_NVM_ID_EVMEM_LOC_6,\
   DEM_NVM_ID_EVMEM_LOC_7,\
   DEM_NVM_ID_EVMEM_LOC_8,\
   DEM_NVM_ID_EVMEM_LOC_9\
}

/* ----------------------------------------------------------------------------
 Event Memory IDs (Auto-Config)
 ----------------------------------------------------------------------------
 */

#define DEM_EVMEM_MEMCOUNTER0                               0u

#define DEM_CFG_EVMEM_MEMID_PRIMARY                         (DEM_EVMEM_MEMCOUNTER0)
#define DEM_EVMEM_MEMCOUNTER1                               (DEM_EVMEM_MEMCOUNTER0+1u)

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0)
#define DEM_CFG_EVMEM_MEMID_SECONDARY                       (DEM_EVMEM_MEMCOUNTER1)
#define DEM_EVMEM_MEMCOUNTER2                               (DEM_EVMEM_MEMCOUNTER1+1u)
#define DEM_CFG_EVMEM_SECONDARY_MEMORY_SUPPORTED             TRUE
#else
#define DEM_CFG_EVMEM_MEMID_SECONDARY                        DEM_EVMEM_INVALID_MEMID
#define DEM_EVMEM_MEMCOUNTER2                               (DEM_EVMEM_MEMCOUNTER1)
#define DEM_CFG_EVMEM_SECONDARY_MEMORY_SUPPORTED             FALSE
#endif

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
#define DEM_CFG_EVMEM_MEMID_MIRROR                          (DEM_EVMEM_MEMCOUNTER2)
#define DEM_EVMEM_MEMCOUNTER3                               (DEM_EVMEM_MEMCOUNTER2+1u)
#define DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED                TRUE
#else
#define DEM_CFG_EVMEM_MEMID_MIRROR                           DEM_EVMEM_INVALID_MEMID
#define DEM_EVMEM_MEMCOUNTER3                               (DEM_EVMEM_MEMCOUNTER2)
#define DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED                FALSE

#endif

#define DEM_CFG_EVMEM_MAX_MEMS                               DEM_EVMEM_MEMCOUNTER3

#define DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL                  (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR)

/* ----------------------------------------------------------------------------
 sanity checks
 ----------------------------------------------------------------------------
 */

/* Support of Failure Counter: 0 Failure Cycle Counter(s) Threshold larger than 1 */
#define DEM_CFG_EVMEM_FAILURE_COUNTER_SUPPORTED              FALSE

#if (DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED && DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED)
#error only mirror memory OR shadow memory is supported
#endif

/* end of include protection */
#endif

