


#ifndef DEM_EVMEM_H
#define DEM_EVMEM_H


#include "Dem_Types.h"
#include "Dem_Cfg_EvMem.h"
#include "Dem_Cfg_EnvMain.h"
#include "Dem_OperationCycle.h"

#include "Dem_EvMemTypes.h"
#include "Dem_EvMemBase.h"

#include "Dem_EvMemApi.h"
#include "Dem_EvMemAging.h"
#if (DEM_CFG_EVMEM_AGING_METHOD == DEM_CFG_EVMEM_AGING_METHOD_USER)
#include "Dem_PrjEvMemAging.h"
#endif


typedef struct {
    uint8 evMemId;
    boolean originSupported;
} Dem_EvMemMapOrigin2IdType;

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE_CONST(Dem_EvMemMapOrigin2IdType, Dem_EvMemMapOrigin2Id, 5);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


DEM_INLINE boolean Dem_EvMemIsOriginSupported (Dem_DTCOriginType origin)
{
    return Dem_EvMemMapOrigin2Id[origin].originSupported;
}

DEM_INLINE uint8 Dem_EvMemGetEvMemIdFromOrigin (Dem_DTCOriginType origin)
{
    return Dem_EvMemMapOrigin2Id[origin].evMemId;
}


/* ----------------------------------------------------------------------------
   Interface Functions
   ----------------------------------------------------------------------------
*/
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
void          Dem_EvMemInit(void);
void          Dem_EvMemInitCausality(void);
void          Dem_EvMemMainFunction(void);

void          Dem_EvMemClearEvent(Dem_EventIdType EventId, uint16_least MemId);
void          Dem_EvMemEraseEventMemory(uint16_least MemId);

void          Dem_EvMemSetEventPassed(Dem_EventIdType EventId, uint16_least MemId, const uint8 *EnvData);
void          Dem_EvMemSetEventFailed(Dem_EventIdType EventId, uint16_least MemId, const uint8 *EnvData);
void          Dem_EvMemSetEventUnRobust(Dem_EventIdType EventId, uint16_least MemId, const uint8 *EnvData);
void          Dem_EvMemStartOperationCycle(Dem_OperationCycleList operationCycleList, uint16_least MemId);

uint16_least  Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility(Dem_DtcIdType DtcId, uint16_least MemId, Dem_boolean_least ShadowEntriesVisible);
uint16_least  Dem_EvMemGetEventMemoryStatusOfDtc(Dem_DtcIdType DtcId, uint16_least MemId);
uint16_least  Dem_EvMemGetEventMemoryStatusOfEvent(Dem_EventIdType EventId, uint16_least MemId);
uint16_least  Dem_EvMemGetEventMemoryLocIdOfEvent (Dem_EventIdType EventId, uint16_least MemId);
Std_ReturnType Dem_EvMemGetReaderCopyOfEvent(Dem_EvMemEventMemoryType* ReaderCopy, Dem_EventIdType EventId, uint16_least MemId);

#if DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
void          Dem_EvMemClearShadowMemory(Dem_EventIdType EventId, uint16_least MemId);
uint16_least  Dem_EvMemGetShadowMemoryLocIdOfDtc(Dem_DtcIdType DtcId, uint16_least MemId);
#endif

uint16_least  Dem_EvMemGetMemoryLocIdOfDtcAndOriginWithVisibility(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin, Dem_boolean_least ShadowEntriesVisible);


Dem_NvmBlockIdType     Dem_EvMemGetNvmIdFromLocId(uint16_least LocId);

#if (DEM_CFG_READDEM_MAX_FDC_DURING_CURRENT_CYCLE_SUPPORTED || DEM_CFG_READDEM_MAX_FDC_SINCE_LAST_CLEAR_SUPPORTED)
void            Dem_EvMemFdcUpdate(void);
#else
DEM_INLINE void Dem_EvMemFdcUpdate(void) {}
#endif
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
extern boolean Dem_EvMemIsLocked;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
/* ----------------------------------------------------------------------------
   Inline
   ----------------------------------------------------------------------------
*/

DEM_INLINE void Dem_EvMemSetEventFailedAllMem(Dem_EventIdType EventId, const uint8 *EnvData)
{
   if (Dem_EvtIsDestPrimaryMemory(EventId))
   {
      Dem_EvMemSetEventFailed(EventId,DEM_CFG_EVMEM_MEMID_PRIMARY,EnvData);
   }
#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
   if (Dem_EvtIsDestSecondaryMemory(EventId))
   {
      Dem_EvMemSetEventFailed(EventId,DEM_CFG_EVMEM_MEMID_SECONDARY,EnvData);
   }
#endif
}


DEM_INLINE void Dem_EvMemSetEventPassedAllMem(Dem_EventIdType EventId, const uint8 *EnvData)
{
   if (Dem_EvtIsDestPrimaryMemory(EventId))
   {
      Dem_EvMemSetEventPassed(EventId,DEM_CFG_EVMEM_MEMID_PRIMARY,EnvData);
   }
#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
   if (Dem_EvtIsDestSecondaryMemory(EventId))
   {
      Dem_EvMemSetEventPassed(EventId,DEM_CFG_EVMEM_MEMID_SECONDARY,EnvData);
   }
#endif
}


DEM_INLINE void Dem_EvMemSetEventUnRobustAllMem(Dem_EventIdType EventId, const uint8 *EnvData)
{
   if (Dem_EvtIsDestPrimaryMemory(EventId))
   {
      Dem_EvMemSetEventUnRobust(EventId,DEM_CFG_EVMEM_MEMID_PRIMARY,EnvData);
   }
#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
   if (Dem_EvtIsDestSecondaryMemory(EventId))
   {
      Dem_EvMemSetEventUnRobust(EventId,DEM_CFG_EVMEM_MEMID_SECONDARY,EnvData);
   }
#endif
}

DEM_INLINE void Dem_EvMemStartOperationCycleAllMem(Dem_OperationCycleList operationCycleList)
{
    Dem_EvMemStartOperationCycle(operationCycleList, DEM_CFG_EVMEM_MEMID_PRIMARY);
#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
    Dem_EvMemStartOperationCycle(operationCycleList, DEM_CFG_EVMEM_MEMID_SECONDARY);
#endif
}

DEM_INLINE uint16_least Dem_EvMemGetMemIdForDTCOrigin(Dem_DTCOriginType DTCOrigin)
{
    switch (DTCOrigin)
    {
        case DEM_DTC_ORIGIN_PRIMARY_MEMORY:
            return DEM_CFG_EVMEM_MEMID_PRIMARY;

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0)
        case DEM_DTC_ORIGIN_SECONDARY_MEMORY:
            return DEM_CFG_EVMEM_MEMID_SECONDARY;
#endif

#if (DEM_CFG_MAX_NUMBER_EVENT_ENTRY_MIRROR > 0)
        case DEM_DTC_ORIGIN_MIRROR_MEMORY:
            return DEM_CFG_EVMEM_MEMID_MIRROR;
#elif DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
        case DEM_DTC_ORIGIN_MIRROR_MEMORY:
            return DEM_CFG_EVMEM_MEMID_SHADOW;
#endif

        default:
            return DEM_EVMEM_INVALID_MEMID;
    }
}

DEM_INLINE void Dem_EvMemClearEventAndOrigin(Dem_EventIdType EventId, Dem_DTCOriginType DTCOrigin)
{
    uint16_least MemId = Dem_EvMemGetMemIdForDTCOrigin(DTCOrigin);
    if (!Dem_EvMemIsMemIdValid(MemId))
    {
        return;
    }

#if DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED
    if (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY)
    {
        Dem_EvMemClearShadowMemory(EventId, MemId);
        return;
    }
#endif

    Dem_EvMemClearEvent(EventId, MemId);


}

DEM_INLINE uint16_least  Dem_EvMemGetEventMemoryStatusOfDtcAndOrigin(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin)
{
    uint16_least MemId = Dem_EvMemGetMemIdForDTCOrigin(DTCOrigin);
    if (!Dem_EvMemIsMemIdValid(MemId) ||
            (Dem_LibGetParamBool(DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED) && (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY))
       )
    {
        return 0;
    }

    return Dem_EvMemGetEventMemoryStatusOfDtc(DtcId, MemId);
}

DEM_INLINE uint16_least  Dem_EvMemGetEventMemoryStatusOfEventAndOrigin(Dem_EventIdType EventId, Dem_DTCOriginType DTCOrigin)
{
    uint16_least MemId = Dem_EvMemGetMemIdForDTCOrigin(DTCOrigin);
    if (!Dem_EvMemIsMemIdValid(MemId) ||
            (Dem_LibGetParamBool(DEM_CFG_EVMEM_SHADOW_MEMORY_SUPPORTED) && (DTCOrigin == DEM_DTC_ORIGIN_MIRROR_MEMORY))
       )
    {
        return 0;
    }

    return Dem_EvMemGetEventMemoryStatusOfEvent(EventId, MemId);
}

DEM_INLINE uint16_least Dem_EvMemGetMemIdForEvent(Dem_EventIdType EventId)
{
    if(Dem_EvtIsDestPrimaryMemory(EventId))
    {
        return DEM_CFG_EVMEM_MEMID_PRIMARY;
    }

#if DEM_CFG_MAX_NUMBER_EVENT_ENTRY_SECONDARY > 0
    if(Dem_EvtIsDestSecondaryMemory(EventId))
    {
        return DEM_CFG_EVMEM_MEMID_SECONDARY;
    }
#endif

    return DEM_EVMEM_INVALID_MEMID;
}

DEM_INLINE uint16_least Dem_EvMemGetLocationOfEventFromEventMemory(Dem_EventIdType EventId)
{
    uint16_least MemId = Dem_EvMemGetMemIdForEvent(EventId);
    if (!Dem_EvMemIsMemIdValid(MemId))
    {
        return DEM_EVMEM_INVALID_LOCID;
    }

    return Dem_EvMemGetEventMemoryLocIdOfEvent(EventId, MemId);

}

DEM_INLINE Std_ReturnType Dem_EvMemGetReaderCopyOfEventFromEventMemory(
        Dem_EvMemEventMemoryType* ReaderCopy,
        Dem_EventIdType EventId
)
{
    uint16_least MemId = Dem_EvMemGetMemIdForEvent(EventId);
    if (!Dem_EvMemIsMemIdValid(MemId))
    {
        return E_NOT_OK;
    }

    return Dem_EvMemGetReaderCopyOfEvent(ReaderCopy, EventId, MemId);
}

DEM_INLINE boolean Dem_GetEvMemLockInternal(void)
{
    return Dem_EvMemIsLocked;
}
DEM_INLINE uint16_least Dem_EvMemGetMemoryLocIdOfDtcAndOrigin(Dem_DtcIdType DtcId, Dem_DTCOriginType DTCOrigin)
{
    /* do not report deleted DTCs */
    return Dem_EvMemGetMemoryLocIdOfDtcAndOriginWithVisibility(DtcId,DTCOrigin,FALSE);
}
DEM_INLINE uint16_least Dem_EvMemGetEventMemoryLocIdOfDtc(Dem_DtcIdType DtcId, uint16_least MemId)
{
    /* do not report deleted DTCs */
    return Dem_EvMemGetEventMemoryLocIdOfDtcWithVisibility(DtcId,MemId,FALSE);
}

DEM_INLINE void Dem_EvMemReaderCopiesEnterLock(void)
{
    /* We do not need to lock if we access the reader copy location only within the same task */
    if (Dem_LibGetParamBool(DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK))
    {
        DEM_ENTERLOCK_MON();
    }
}

DEM_INLINE void Dem_EvMemReaderCopiesExitLock(void)
{
    if (Dem_LibGetParamBool(DEM_CFG_EVMEM_READ_FROM_DIFFERENT_TASK))
    {
        DEM_EXITLOCK_MON();
    }
}

#endif
