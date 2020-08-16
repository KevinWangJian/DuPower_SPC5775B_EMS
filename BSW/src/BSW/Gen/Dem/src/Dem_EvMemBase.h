

#ifndef DEM_EVMEMBASE_H
#define DEM_EVMEMBASE_H

#include "Dem_Helpers.h"
#include "Dem_Events.h"
#include "Dem_ISO14229Byte.h"
#include "Dem_OperationCycle.h"
#include "Dem_Nvm.h"
#include "Dem_EvMemTypes.h"
#include "Dem_EnvTrigger.h"
#include "Dem_Cfg_EnvDataElement.h"
#include "Dem_Deb.h"
#include "Dem_EvBuffEvent.h"
#include "Dem_Lib.h"
#include "Dem_DTCStatusByte.h"


typedef uint8 Dem_EvMemActionType;
#define DEM_EVMEM_ACTIONTYPE_CONFIRMATION   1
#define DEM_EVMEM_ACTIONTYPE_DISPLACEMENT   2
#define DEM_EVMEM_ACTIONTYPE_AGING          3
#define DEM_EVMEM_ACTIONTYPE_NONE           4
#define DEM_EVMEM_ACTIONTYPE_SETPENDING     5
#define DEM_EVMEM_ACTIONTYPE_RESETPENDING   6
#define DEM_EVMEM_ACTIONTYPE_IMMEDIATEAGING 7
#define DEM_EVMEM_ACTIONTYPE_AGINGOFCONFIRMED   8




/* ----------------------------------------------------------------------------
   Functions
   ----------------------------------------------------------------------------
*/
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
uint32       Dem_EvMemGetNewEventMemoryTimeId(uint16_least MemId);
void         Dem_EvMemCopyToMirrorMemory(uint16_least LocId);
void         Dem_EvMemForceClearEventMemoryLocation(uint16_least LocId, uint16_least WriteSts, Dem_EvMemActionType actionType);
uint16_least Dem_EvMemGetEventMemoryStorageLocation (Dem_EventIdType EventId, Dem_EvBuffEventType EventType, uint16_least MemId, Dem_boolean_least isDisplacementSupported, uint16_least displacementStrategy);
uint16_least Dem_EvMemGetMirrorMemoryStorageLocation(Dem_EventIdType EventId, uint16_least MemId, Dem_boolean_least isDisplacementSupported, uint16_least displacementStrategy);

#if (DEM_CFG_EVMEM_MEMORY_DISPLACEMENT_STRATEGY == DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_CUST) || (DEM_CFG_EVMEM_MIRROR_DISPLACEMENT_STRATEGY == DEM_CFG_EVMEM_DISPLACEMENT_STRATEGY_CUST)
uint16       Dem_EvMemGetEventMemoryDisplacementLocationCust(Dem_EventIdType EventId, Dem_EvBuffEventType EventType, uint16 MemId);
#endif

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"



/* ----------------------------------------------------------------------------
   Macros
   ----------------------------------------------------------------------------
*/

#define DEM_EVMEM_CLEAROBJ(obj)             DEM_MEMSET(&(obj),0,DEM_SIZEOF_VAR(obj))

#define DEM_EVMEM_BOOL2DEC(b)               ( (b) ? 1u : 0u )

#define DEM_EVMEM_USEVAR(var)               (void)(var)

/* ----------------------------------------------------------------------------
   Data
   ----------------------------------------------------------------------------
*/
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE_CONST(Dem_NvmBlockIdType,      Dem_EvMemNvmId,       DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

#if DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK
    /* If the evmem is read from a separate task we copy each location into a reader copy on every main cycle
     * and serve all read requests from the copy instead of the evmem location itself. The reader copies are stored
     * in the Dem_EvMemEventMemory array after the normal entries. */
    #define DEM_CFG_EVMEM_EVENTMEMORY_LENGTH    (2u * DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL)
#else
    #define DEM_CFG_EVMEM_EVENTMEMORY_LENGTH    DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL
#endif


#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE(Dem_EvMemEventMemoryType, Dem_EvMemEventMemory, DEM_CFG_EVMEM_EVENTMEMORY_LENGTH);
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE_CONST(uint16_least,       Dem_EvMemLocIdList,   DEM_CFG_EVMEM_MAX_MEMS+1u);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


/* ----------------------------------------------------------------------------
   Inline
   ----------------------------------------------------------------------------
*/

DEM_INLINE Dem_boolean_least Dem_EvMemIsMemIdValid(uint16_least MemId)
{
    return (Dem_boolean_least)(MemId < DEM_CFG_EVMEM_MAX_MEMS);
}

/* ----------------------------------------------------------------------------
   Event Memory Data
   ----------------------------------------------------------------------------
*/
DEM_INLINE Dem_boolean_least Dem_EvMemIsEventMemLocIdValid(uint16_least LocId)
{
    return (Dem_boolean_least)(LocId < DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL);
}

DEM_INLINE uint16_least Dem_EvMemLocId2ReaderCopyLocId(uint16_least LocId)
{
    DEM_ASSERT(Dem_EvMemIsEventMemLocIdValid(LocId), DEM_DET_APIID_EVMEMSETEVENTFAILED, 10);

#if DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK
    return LocId + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL;
#else
    return LocId;
#endif
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsReaderCopyLocIdValid(uint16_least LocId)
{
    return (Dem_boolean_least)(LocId < DEM_CFG_EVMEM_EVENTMEMORY_LENGTH);
}

/* --- Status --- */
DEM_INLINE uint16_least Dem_EvMemGetEventMemStatusByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return EventMemory->Hdr.Data.Status;
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemStatus(uint16_least LocId)
{
    return Dem_EvMemGetEventMemStatusByPtr(&Dem_EvMemEventMemory[LocId]);
}


DEM_INLINE void Dem_EvMemSetEventMemStatus(uint16_least LocId, uint16_least Status)
{
    Dem_EvMemEventMemory[LocId].Hdr.Data.Status = (uint16)Status;
}


/* --- EventId --- */
DEM_INLINE Dem_EventIdType Dem_EvMemGetEventMemEventIdByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return EventMemory->Hdr.Data.EventId;
}

DEM_INLINE Dem_EventIdType Dem_EvMemGetEventMemEventId(uint16_least LocId)
{
    return Dem_EvMemGetEventMemEventIdByPtr(&Dem_EvMemEventMemory[LocId]);
}


DEM_INLINE void Dem_EvMemSetEventMemEventId(uint16_least LocId, Dem_EventIdType EventId)
{
    Dem_EvMemEventMemory[LocId].Hdr.Data.EventId = (uint16)EventId;
}


/* --- TimeId --- */
DEM_INLINE uint32 Dem_EvMemGetEventMemTimeIdByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return EventMemory->TimeId;
}

DEM_INLINE uint32 Dem_EvMemGetEventMemTimeId(uint16_least LocId)
{
    return Dem_EvMemGetEventMemTimeIdByPtr(&Dem_EvMemEventMemory[LocId]);
}


DEM_INLINE void Dem_EvMemSetEventMemTimeId(uint16_least LocId, uint32 TimeId)
{
    Dem_EvMemEventMemory[LocId].TimeId = TimeId;
}


/* --- DTC Status --- */
DEM_INLINE uint8 Dem_EvMemGetEventMemDtcStatusByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED)
    return EventMemory->DTCStatus;
#else
    return 0;
#endif
}

DEM_INLINE uint8 Dem_EvMemGetEventMemDtcStatus(uint16_least LocId)
{
    return Dem_EvMemGetEventMemDtcStatusByPtr(&Dem_EvMemEventMemory[LocId]);
}


DEM_INLINE void Dem_EvMemSetEventMemDtcStatus(uint16_least LocId, uint8 DtcStatus)
{
    DEM_EVMEM_USEVAR(LocId);
    DEM_EVMEM_USEVAR(DtcStatus);

#if (DEM_CFG_EVMEM_MIRROR_MEMORY_DTC_STATUS_STORED)
    Dem_EvMemEventMemory[LocId].DTCStatus = DtcStatus;
#endif
}

/* --- FailureCounter --- */
DEM_INLINE uint8_least Dem_EvMemGetEventMemFailureCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    return EventMemory->FailureCounter;
}

DEM_INLINE uint8_least Dem_EvMemGetEventMemFailureCounter(uint16_least LocId)
{
    return Dem_EvMemGetEventMemFailureCounterByPtr(&Dem_EvMemEventMemory[LocId]);
}


DEM_INLINE void Dem_EvMemSetEventMemFailureCounter(uint16_least LocId, uint8 FailureCounter)
{
    Dem_EvMemEventMemory[LocId].FailureCounter = FailureCounter;
}

/* --- OccurrenceCounter --- */
DEM_INLINE uint16_least Dem_EvMemGetEventMemOccurrenceCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_EVMEM_OCCURRENCE_COUNTER_SUPPORTED)
    return (uint16_least)EventMemory->OccurrenceCounter;
#else
    return 0;
#endif
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemOccurrenceCounter(uint16_least LocId)
{
    return Dem_EvMemGetEventMemOccurrenceCounterByPtr(&Dem_EvMemEventMemory[LocId]);
}


DEM_INLINE void Dem_EvMemSetEventMemOccurrenceCounter(uint16_least LocId, uint16_least OccurrenceCounter)
{
    DEM_EVMEM_USEVAR(LocId);
    DEM_EVMEM_USEVAR(OccurrenceCounter);

#if (DEM_CFG_EVMEM_OCCURRENCE_COUNTER_SUPPORTED)
    Dem_EvMemEventMemory[LocId].OccurrenceCounter = (Dem_EvMemOccurrenceCounterType) OccurrenceCounter;
#endif
}

/* --- AgingCounter --- */
DEM_INLINE uint16_least Dem_EvMemGetEventMemAgingCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
   DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED)
      return (uint16_least)EventMemory->AgingCounter;
#else
    return 0;
#endif
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemAgingCounter(uint16_least LocId)
{
   return Dem_EvMemGetEventMemAgingCounterByPtr(&Dem_EvMemEventMemory[LocId]);

}

DEM_INLINE void Dem_EvMemSetEventMemAgingCounter(uint16_least LocId, uint16_least AgingCounter)
{
    DEM_EVMEM_USEVAR(LocId);
    DEM_EVMEM_USEVAR(AgingCounter);

#if (DEM_CFG_EVMEM_AGING_COUNTER_SUPPORTED)
    Dem_EvMemEventMemory[LocId].AgingCounter = (Dem_EvMemAgingCounterType) AgingCounter;
#endif
}

/* --- AgingCounterForTFSLC --- */
DEM_INLINE uint16_least Dem_EvMemGetEventMemAgingCounterForTFSLCByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
   DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
      return (uint16_least)EventMemory->AgingCounterForTFSLC;
#else
    return 0;
#endif
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemAgingCounterForTFSLC(uint16_least LocId)
{
   return Dem_EvMemGetEventMemAgingCounterForTFSLCByPtr(&Dem_EvMemEventMemory[LocId]);

}

DEM_INLINE void Dem_EvMemSetEventMemAgingCounterForTFSLC(uint16_least LocId, uint16_least AgingCounterForTFSLC)
{
    DEM_EVMEM_USEVAR(LocId);
    DEM_EVMEM_USEVAR(AgingCounterForTFSLC);

#if (DEM_CFG_TFSLC_RESET_AFTER_AGING_AND_DISPLACEMENT)
    Dem_EvMemEventMemory[LocId].AgingCounterForTFSLC = (Dem_EvMemAgingCounterType) AgingCounterForTFSLC;
#endif
}

/* --- Debouncer-Info: MaxFdcCurrentCycle / MaxFdcSinceLastClear --- */

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
DEM_INLINE void Dem_EvMemSetMaxFdcDuringCurrentCycleByPtr(Dem_EvMemEventMemoryType *EventMemory, sint8 fdc)
{
    DEM_EVMEM_USEVAR(EventMemory);
    DEM_EVMEM_USEVAR(fdc);

#if (DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED)
	EventMemory->MaxFdcDuringCurrentCycle = fdc;
#endif
}

/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is depending on compiler switch setting */
DEM_INLINE void Dem_EvMemSetMaxFdcSinceLastClearByPtr(Dem_EvMemEventMemoryType *EventMemory, sint8 fdc)
{
    DEM_EVMEM_USEVAR(EventMemory);
    DEM_EVMEM_USEVAR(fdc);

#if (DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED)
	EventMemory->MaxFdcSinceLastClear = fdc;
#endif
}


DEM_INLINE sint8 Dem_EvMemGetMaxFdcDuringCurrentCycleByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED)
	return EventMemory->MaxFdcDuringCurrentCycle;
#else
	return 0;
#endif
}

DEM_INLINE sint8 Dem_EvMemGetMaxFdcSinceLastClearByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
    DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED)
	return EventMemory->MaxFdcSinceLastClear;
#else
   	return 0;
#endif
}

DEM_INLINE void Dem_EvMemSetMaxFdcDuringCurrentCycle(uint16_least LocId, sint8 fdc)
{
	Dem_EvMemSetMaxFdcDuringCurrentCycleByPtr(&(Dem_EvMemEventMemory[LocId]), fdc);
}

DEM_INLINE void Dem_EvMemSetMaxFdcSinceLastClear(uint16_least LocId, sint8 fdc)
{
	Dem_EvMemSetMaxFdcSinceLastClearByPtr(&(Dem_EvMemEventMemory[LocId]), fdc);
}


DEM_INLINE sint8 Dem_EvMemGetMaxFdcDuringCurrentCycle(uint16_least LocId)
{
    return Dem_EvMemGetMaxFdcDuringCurrentCycleByPtr (&(Dem_EvMemEventMemory[LocId]));
}

DEM_INLINE sint8 Dem_EvMemGetMaxFdcSinceLastClear(uint16_least LocId)
{
	return Dem_EvMemGetMaxFdcSinceLastClearByPtr (&(Dem_EvMemEventMemory[LocId]));
}



/* --- Cycle-Info: CyclesSinceFirstFailed / CyclesSinceLastFailed  / FailedCycles --- */
DEM_INLINE uint8 Dem_EvMemGetCyclesSinceFirstFailedByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_FIRST_FAILED_SUPPORTED)
	return EventMemory->CyclesSinceFirstFailed;
#else
	DEM_UNUSED_PARAM(EventMemory);
   	return 0;
#endif
}

DEM_INLINE uint8 Dem_EvMemGetCyclesSinceLastFailedByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED)
	return EventMemory->CyclesSinceLastFailed;
#else
	DEM_UNUSED_PARAM(EventMemory);
	return 0;
#endif
}

DEM_INLINE uint8 Dem_EvMemGetCyclesSinceLastFailedExcludingTNCByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED)
   	return EventMemory->CyclesSinceLastFailedExcludingTNC;
#else
	DEM_UNUSED_PARAM(EventMemory);
	return 0;
#endif
}

DEM_INLINE uint8 Dem_EvMemGetFailedCyclesByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
#if (DEM_CFG_READDEM_FAILED_CYCLES_SUPPORTED)
	return EventMemory->FailedCycles;
#else
	DEM_UNUSED_PARAM(EventMemory);
	return 0;
#endif
}

DEM_INLINE void Dem_EvMemIncCyclesSinceFirstFailed(uint16_least LocId)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_FIRST_FAILED_SUPPORTED)
	if(Dem_EvMemEventMemory[LocId].CyclesSinceFirstFailed != 255)
	{
		Dem_EvMemEventMemory[LocId].CyclesSinceFirstFailed++;
	}
#else
	DEM_UNUSED_PARAM(LocId);
#endif
}

DEM_INLINE void Dem_EvMemIncCyclesSinceLastFailed(uint16_least LocId)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED)
	if(Dem_EvMemEventMemory[LocId].CyclesSinceLastFailed != 255)
	{
		Dem_EvMemEventMemory[LocId].CyclesSinceLastFailed++;
	}
#else
	DEM_UNUSED_PARAM(LocId);
#endif
}

DEM_INLINE void Dem_EvMemIncCyclesSinceLastFailedExcludingTNC(uint16_least LocId)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED)
	if(Dem_EvMemEventMemory[LocId].CyclesSinceLastFailedExcludingTNC != 255)
	{
		Dem_EvMemEventMemory[LocId].CyclesSinceLastFailedExcludingTNC++;
	}
#else
	DEM_UNUSED_PARAM(LocId);
#endif
}

DEM_INLINE void Dem_EvMemIncFailedCycles(uint16_least LocId)
{
#if (DEM_CFG_READDEM_FAILED_CYCLES_SUPPORTED)
	if(Dem_EvMemEventMemory[LocId].FailedCycles != 255)
	{
		Dem_EvMemEventMemory[LocId].FailedCycles++;
	}
#else
	DEM_UNUSED_PARAM(LocId);
#endif
}

DEM_INLINE void Dem_EvMemResetCyclesSinceLastFailed(uint16_least LocId)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_SUPPORTED)
	Dem_EvMemEventMemory[LocId].CyclesSinceLastFailed = 0;
#else
	DEM_UNUSED_PARAM(LocId);
#endif
}

DEM_INLINE void Dem_EvMemResetCyclesSinceLastFailedExcludingTNC(uint16_least LocId)
{
#if (DEM_CFG_READDEM_CYCLES_SINCE_LAST_FAILED_EXCLUDING_TNC_SUPPORTED)
   	Dem_EvMemEventMemory[LocId].CyclesSinceLastFailedExcludingTNC = 0;
#else
	DEM_UNUSED_PARAM(LocId);
#endif
}

/* --- FreezeFrameCounter --- */
DEM_INLINE uint16_least Dem_EvMemGetEventMemFreezeFrameCounterByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
   DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED)
   return (uint16_least)EventMemory->FreezeFrameCounter;
#else
   return 0;
#endif

}

DEM_INLINE uint16_least Dem_EvMemGetEventMemFreezeFrameCounter(uint16_least LocId)
{
   return Dem_EvMemGetEventMemFreezeFrameCounterByPtr(&Dem_EvMemEventMemory[LocId]);
}



DEM_INLINE void Dem_EvMemSetEventMemLocFreezeFrameCounter(uint16_least LocId, uint16_least FreezeFrameCounter)
{
   DEM_EVMEM_USEVAR(LocId);
   DEM_EVMEM_USEVAR(FreezeFrameCounter);

#if (DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED)
   Dem_EvMemEventMemory[LocId].FreezeFrameCounter = (uint8)FreezeFrameCounter;
#endif
}


/* --- Extended Data Trigger --- */
DEM_INLINE Dem_TriggerType Dem_EvMemGetEventMemTriggerByPtr(const Dem_EvMemEventMemoryType *EventMemory)
{
   DEM_EVMEM_USEVAR(EventMemory);

#if (DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED || DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED)
   return EventMemory->Trigger;
#else
   return 0;
#endif

}

DEM_INLINE Dem_TriggerType Dem_EvMemGetEventMemTrigger(uint16_least LocId)
{
   return Dem_EvMemGetEventMemTriggerByPtr(&Dem_EvMemEventMemory[LocId]);
}

DEM_INLINE void Dem_EvMemSetEventMemTrigger(uint16_least LocId, Dem_TriggerType Trigger)
{
   DEM_EVMEM_USEVAR(LocId);
   DEM_EVMEM_USEVAR(Trigger);

#if (DEM_CFG_EVMEM_EXTENDED_DATA_SUPPORTED || DEM_CFG_EVMEM_FREEZE_FRAME_SUPPORTED)
   Dem_EvMemEventMemory[LocId].Trigger = Trigger;
#endif
}

/* --- Data --- */
/* MR12 RULE 8.13 VIOLATION: parameter not made const, as it is used to get address of element data and to fill the data block */
DEM_INLINE uint8 *Dem_EvMemGetEventMemDataByPtr(Dem_EvMemEventMemoryType *EventMemory)
{
   return EventMemory->Data;
}

DEM_INLINE uint8 *Dem_EvMemGetEventMemData(uint16_least LocId)
{
   return Dem_EvMemGetEventMemDataByPtr(&Dem_EvMemEventMemory[LocId]);
}

DEM_INLINE Dem_EvMemEventMemoryType *Dem_EvMemGetEventMemLocation(uint16_least LocId)
{
   return (&Dem_EvMemEventMemory[LocId]);
}

DEM_INLINE uint16 Dem_EvMemGetEventMemDataSize(void)
{
   return DEM_SIZEOF_VAR(Dem_EvMemEventMemory[0].Data);
}

/* ----------------------------------------------------------------------------
   Event Memory Status
   ----------------------------------------------------------------------------
*/
/* the bits DEM_EVMEM_STSMASK_STORED and DEM_EVMEM_STSMASK_DELETED shall not be set at the same time */

DEM_INLINE Dem_boolean_least Dem_EvMemIsTestFailedSLC(uint16_least Status)
{
   return (Dem_boolean_least)((Status & (DEM_EVMEM_STSMASK_TESTFAILED_SLC | DEM_EVMEM_STSMASK_STORED)) == (DEM_EVMEM_STSMASK_TESTFAILED_SLC | DEM_EVMEM_STSMASK_STORED));
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsTestCompleteTFC(uint16_least Status)
{
    return ((Status & DEM_EVMEM_STSMASK_TESTCOMPLETE_TFC) == DEM_EVMEM_STSMASK_TESTCOMPLETE_TFC);
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsTestFailedTFC (uint16_least Status)
{
    return ((Status & DEM_EVMEM_STSMASK_TESTFAILED_TFC) == DEM_EVMEM_STSMASK_TESTFAILED_TFC);
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsStored(uint16_least Status)
{
   return (Dem_boolean_least)((Status & (DEM_EVMEM_STSMASK_STORED | DEM_EVMEM_STSMASK_DELETED)) == DEM_EVMEM_STSMASK_STORED);
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsEmpty(uint16_least Status)
{
   return (Dem_boolean_least)((Status & (DEM_EVMEM_STSMASK_STORED | DEM_EVMEM_STSMASK_DELETED)) == 0u);
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsDeleted(uint16_least Status)
{
   DEM_EVMEM_USEVAR(Status);

#if DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED
   return (Dem_boolean_least)((Status & DEM_EVMEM_STSMASK_DELETED) != 0u);
#else
   return FALSE;
#endif
}
DEM_INLINE uint16_least Dem_EvMemSetToEmpty(void)
{
	return 0u;
}

DEM_INLINE uint16_least Dem_EvMemSetToDelete(uint16_least Status)
{
	DEM_EVMEM_USEVAR(Status);

#if DEM_CFG_EVMEM_SHADOW_ENTRIES_SUPPORTED
	return (Status | DEM_EVMEM_STSMASK_DELETED) & (~DEM_EVMEM_STSMASK_STORED);
#else
    return Dem_EvMemSetToEmpty();
#endif
}

DEM_INLINE Dem_boolean_least Dem_EvMemGetShadowVisibility(void)
{
	return DEM_CFG_EVMEM_SHADOW_ENTRIES_VISIBLE;
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsVisible(uint16_least Status, Dem_boolean_least ShadowEntriesVisible)
{
	return (Dem_boolean_least)( ( Dem_EvMemIsStored(Status)) ||
			                    (!Dem_EvMemIsEmpty (Status) && Dem_EvMemGetShadowVisibility() && ShadowEntriesVisible));
}

/* ----------------------------------------------------------------------------
   Event Memory Iterators
   ----------------------------------------------------------------------------
*/


DEM_INLINE uint16_least Dem_EvMemGetEventMemStartLocId(uint16_least MemId)
{

	DEM_EVMEM_USEVAR(MemId);

#if (DEM_CFG_EVMEM_MAX_MEMS == 1)
	return 0;
#else
	return Dem_EvMemLocIdList[MemId];
#endif
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemEndLocId(uint16_least MemId)
{
	DEM_EVMEM_USEVAR(MemId);

#if (DEM_CFG_EVMEM_MAX_MEMS == 1)
	return DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY;
#else
	return Dem_EvMemLocIdList[MemId+1u];
#endif
}


DEM_INLINE void Dem_EvMemEventMemoryLocIteratorNew (uint16_least *LocId, uint16_least MemId)
{
    *LocId = Dem_EvMemGetEventMemStartLocId(MemId);
}


DEM_INLINE Dem_boolean_least Dem_EvMemEventMemoryLocIteratorIsValid (const uint16_least *LocId, uint16_least MemId)
{
    return (Dem_boolean_least)(*LocId < Dem_EvMemGetEventMemEndLocId(MemId));
}


DEM_INLINE void Dem_EvMemEventMemoryLocIteratorNext (uint16_least *LocId, uint16_least MemId)
{
    DEM_EVMEM_USEVAR(MemId);
    (*LocId)++;
}

DEM_INLINE void Dem_EvMemEventMemoryLocIteratorInvalidate (uint16_least *LocId, uint16_least MemId)
{
    *LocId = Dem_EvMemGetEventMemEndLocId(MemId);
}


DEM_INLINE void Dem_EvMemEventMemoryIteratorNew(uint16_least *MemId)
{
	*MemId = 0;
}

DEM_INLINE Dem_boolean_least Dem_EvMemEventMemoryIteratorIsValid(const uint16_least *MemId)
{
	return (Dem_boolean_least) (*MemId < DEM_CFG_EVMEM_MAX_MEMS);
}

DEM_INLINE void Dem_EvMemEventMemoryIteratorNext(uint16_least *MemId)
{
	(*MemId)++;
}

DEM_INLINE void Dem_EvMemEventMemoryAllLocIteratorNew (uint16_least *LocId)
{
    *LocId = 0;
}

DEM_INLINE Dem_boolean_least Dem_EvMemEventMemoryAllLocIteratorIsValid (const uint16_least *LocId)
{
    return (Dem_boolean_least)(*LocId < DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL);
}

DEM_INLINE void Dem_EvMemEventMemoryAllLocIteratorNext (uint16_least *LocId)
{
    (*LocId)++;
}

DEM_INLINE void Dem_EvMemEventMemoryPrimaryUserdefLocIteratorNew (uint16_least *LocId)
{
    *LocId = 0;
}

DEM_INLINE Dem_boolean_least Dem_EvMemEventMemoryPrimaryUserdefLocIteratorIsValid (const uint16_least *LocId)
{
    return (Dem_boolean_least)(*LocId < (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY));
}

DEM_INLINE void Dem_EvMemEventMemoryPrimaryUserdefLocIteratorNext (uint16_least *LocId)
{
    (*LocId)++;
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsOriginPrimary (uint16_least LocId)
{
   return (Dem_boolean_least) (LocId < DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY);
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsOriginSecondary (uint16_least LocId)
{
   return (Dem_boolean_least) ((LocId >=  DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY) &&
                               (LocId <  (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY)));
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsOriginMirror (uint16_least LocId)
{
   return (Dem_boolean_least) ((LocId >=  (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_PRIMARY + DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY)) &&
                               (LocId <    DEM_CFG_MAX_NUMBER_EVENT_ENTRY_ALL));
}


/* ----------------------------------------------------------------------------
   Helper
   ----------------------------------------------------------------------------
*/

DEM_INLINE Dem_boolean_least Dem_EvMemIsEdgeTrigger(uint16_least StatusOld, uint16_least StatusNew, uint16_least Trigger)
{
	return (Dem_boolean_least) (((StatusOld ^ StatusNew) & Trigger) != 0u);
}

DEM_INLINE uint16_least Dem_EvMemGetEventMemId(uint16_least LocId)
{
	uint16_least MemId;

	for (Dem_EvMemEventMemoryIteratorNew     (&MemId);
		 Dem_EvMemEventMemoryIteratorIsValid (&MemId);
		 Dem_EvMemEventMemoryIteratorNext    (&MemId))
	{
		if (LocId < Dem_EvMemGetEventMemEndLocId (MemId))
		{
			return MemId;
		}
	}
	/* should only be reached in case of an invalid LocId */
	DEM_ASSERT(Dem_LibGetParamBool(FALSE),DEM_DET_APIID_DEM_EVMEMGETEVENTMEMID,0);
	return DEM_EVMEM_INVALID_MEMID;

}

/* ----------------------------------------------------------------------------
   Functions
   ----------------------------------------------------------------------------
*/

DEM_INLINE Dem_boolean_least Dem_EvMemIsDisplaceEventMemoryLocAllowed(Dem_EventIdType NewEventId, uint16_least LocId)
{
   DEM_EVMEM_USEVAR(NewEventId);
   DEM_EVMEM_USEVAR(LocId);

   return TRUE;
}


DEM_INLINE Dem_boolean_least Dem_EvMemIsEventFailedAllowed(Dem_EventIdType EventId, uint16_least MemId)
{
   DEM_EVMEM_USEVAR(EventId);
   DEM_EVMEM_USEVAR(MemId);

   return(TRUE);
}


DEM_INLINE Dem_boolean_least Dem_EvMemIsEventPassedAllowed(Dem_EventIdType EventId, uint16_least MemId)
{
    uint8 DtcStatusByte = 0;

    DEM_EVMEM_USEVAR(EventId);
    DEM_EVMEM_USEVAR(MemId);
    DEM_EVMEM_USEVAR(DtcStatusByte);


#if (DEM_CFG_EVCOMB == DEM_CFG_EVCOMB_ONSTORAGE)
    DtcStatusByte = Dem_DtcStatusByteRetrieve(Dem_DtcIdFromEventId(EventId));
    /**
     * Checking TestFailed is set - The evmem location shall only be reset in case the dtc is passed
     * (To make sure that corresponding DTC already processed and available in Event memory)
     */
    return (! Dem_ISO14229ByteIsTestFailed(DtcStatusByte));
#else
    return(TRUE);
#endif
}


DEM_INLINE Dem_boolean_least Dem_EvMemIsEventUnRobustAllowed(Dem_EventIdType EventId, uint16_least MemId)
{
   DEM_EVMEM_USEVAR(EventId);
   DEM_EVMEM_USEVAR(MemId);

   return(TRUE);
}

DEM_INLINE Dem_boolean_least Dem_EvMemIsEventMemoryDisplacementSupported(uint16_least MemId)
{
   DEM_EVMEM_USEVAR(MemId);

   return (Dem_boolean_least)(Dem_LibGetParamBool(DEM_CFG_EVMEM_DISPLACEMENT_SUPPORTED));
}


DEM_INLINE Dem_boolean_least Dem_EvMemIsTriggerOccurrenceCounter(Dem_EventIdType EventId, uint16_least MemId, uint16_least StatusOld, uint16_least StatusNew)
{
	DEM_EVMEM_USEVAR(EventId);
	DEM_EVMEM_USEVAR(MemId);

	/* occurrence counter is triggered if */
	/* 1. TestFailed changes from 0 to 1 */
	/* 2. static flags defined by DEM_CFG_EVMEM_OCCCOUNTER_TRIGGER_STSMASK are set */
	return Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_TESTFAILED) && ((StatusNew & DEM_CFG_EVMEM_OCCCOUNTER_TRIGGER_STSMASK) == DEM_CFG_EVMEM_OCCCOUNTER_TRIGGER_STSMASK);
}

DEM_INLINE Dem_TriggerType Dem_EvMemGetTriggerOnFailed(uint16_least StatusOld, uint16_least StatusNew)
{
	Dem_TriggerType Trigger;
	Trigger = DEM_TRIGGER_NONE;
	if (Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_TESTFAILED))
	{
		Dem_EnvSetTrigger(&Trigger, DEM_TRIGGER_ON_TEST_FAILED);
	}
	if (Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_PENDING))
	{
		Dem_EnvSetTrigger(&Trigger, DEM_TRIGGER_ON_PENDING);
	}
	if (Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_CONFIRMED))
	{
		Dem_EnvSetTrigger(&Trigger, DEM_TRIGGER_ON_CONFIRMED);
	}

	return Trigger;
}


DEM_INLINE Dem_TriggerType Dem_EvMemGetTriggerOnPassed(uint16_least StatusOld, uint16_least StatusNew)
{
	Dem_TriggerType Trigger;
	Trigger = DEM_TRIGGER_NONE;
	if (Dem_EvMemIsEdgeTrigger (StatusOld, StatusNew, DEM_EVMEM_STSMASK_TESTFAILED))
	{
		Dem_EnvSetTrigger(&Trigger, DEM_TRIGGER_ON_PASSED);
	}
	return Trigger;
}


/* ----------------------------------------------------------------------------
   Mirror Memory
   ----------------------------------------------------------------------------
*/
#if (DEM_CFG_EVMEM_MIRROR_MEMORY_SUPPORTED)


DEM_INLINE Dem_boolean_least Dem_EvMemIsTriggerMirrorOnFailed(Dem_EventIdType EventId, uint16_least MemId, uint16_least StatusOld, uint16_least StatusNew)
{
   DEM_EVMEM_USEVAR(EventId);
   DEM_EVMEM_USEVAR(MemId);

   return (Dem_boolean_least)(Dem_EvMemIsEdgeTrigger(StatusOld, StatusNew, DEM_EVMEM_STSMASK_TESTFAILED));
}


DEM_INLINE Dem_boolean_least Dem_EvMemIsTriggerMirrorOnClear(Dem_EventIdType EventId, uint16_least LocId, uint16_least StatusOld, uint16_least StatusNew)
{
   DEM_EVMEM_USEVAR(EventId);
   DEM_EVMEM_USEVAR(LocId);
   DEM_EVMEM_USEVAR(StatusOld);
   DEM_EVMEM_USEVAR(StatusNew);

   return (Dem_boolean_least)((StatusOld & DEM_EVMEM_STSMASK_CONFIRMED) != 0u);
}

#endif


/* ----------------------------------------------------------------------------
   NV-RAM Optimizations
   ----------------------------------------------------------------------------
*/
/* ISO 14229 status bits which are only necessary in RAM not in NVM */
DEM_INLINE uint16_least Dem_EvMemGetRamStsMask(Dem_EventIdType EventId)
{
    uint16_least stsMask = DEM_EVMEM_STSMASK_READER_COPY_CURRENT;
    if (!Dem_EvtStoreTestFailedToNextOC(EventId))
    {
        stsMask |= DEM_EVMEM_STSMASK_TESTFAILED;
    }
    return stsMask;
}

/* ----------------------------------------------------------------------------
   Helper Functions
   ----------------------------------------------------------------------------
*/

DEM_INLINE Dem_boolean_least Dem_EvMemIsEqualEvent(Dem_EventIdType EventId1, Dem_EventIdType EventId2)
{
   if (Dem_LibGetParamUI8(DEM_CFG_EVCOMB) != Dem_LibGetParamUI8(DEM_CFG_EVCOMB_ONRETRIEVAL))
   {
        return (Dem_boolean_least)(Dem_DtcIdFromEventId(EventId1) == Dem_DtcIdFromEventId(EventId2));
   }
   else
   {
        return (Dem_boolean_least)(EventId1 == EventId2);
   }
}


DEM_INLINE Dem_boolean_least Dem_EvMemIsNvStatusChanged(Dem_EventIdType EventId, uint16_least StatusOld, uint16_least StatusNew)
{
   return (Dem_boolean_least)(Dem_EvMemIsEdgeTrigger(StatusOld, StatusNew, ~Dem_EvMemGetRamStsMask(EventId)));
}


/* ----------------------------------------------------------------------------
   Sanity Check
   ----------------------------------------------------------------------------
*/

#if (DEM_EVMEM_STSMASK_CONFIRMED != (1u << DEM_ISO14229_CONFIRMEDDTC))
   #error incompatible definition of ISO14229 status bit 'confirmedDtc'
#endif
#if (DEM_EVMEM_STSMASK_PENDING != (1u << DEM_ISO14229_PENDINGDTC))
   #error incompatible definition of ISO14229 status bit 'pendingDtc'
#endif


/* ----------------------------------------------------------------------------
   Include Protection
   ----------------------------------------------------------------------------
*/
#endif

