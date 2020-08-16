

#ifndef DEM_ENVFFRECNUMERATION_H
#define DEM_ENVFFRECNUMERATION_H


#include "Dem_Types.h"
#include "Dem_Cfg_EnvFFRecNumeration.h"
#include "Dem_Events.h"
#include "Dem_EvMem.h"

#if (DEM_CFG_FFRECNUM == DEM_CFG_FFRECNUM_CALCULATED)


DEM_INLINE Dem_boolean_least Dem_EnvIsFFRecNumValid(Dem_EventIdType EventId, uint8 RecNumber)
{
	return ((RecNumber > 0) && (RecNumber <= Dem_EvtGetMaxNumberOfFreezeFrames(EventId)));
}

DEM_INLINE uint8 Dem_EnvGetIndexFromFFRecNum(Dem_EventIdType EventId, uint8 RecNumber)
{
	DEM_UNUSED_PARAM(EventId);
	return (RecNumber - 1);
}


DEM_INLINE uint8 Dem_EnvGetFFRecNumFromIndex(Dem_EventIdType EventId, uint8 idx)
{
	DEM_UNUSED_PARAM(EventId);
	return (idx + 1);
}

DEM_INLINE Dem_TriggerType Dem_EnvGetFFRecordTrigger (uint8 RecNumber)
{
    DEM_UNUSED_PARAM(RecNumber);
    return 0;
}

DEM_INLINE void Dem_EnvGetFFRecordTriggerAndUpdate (uint8 RecNumber, Dem_TriggerType* Trigger, boolean* Update)
{
    DEM_UNUSED_PARAM(RecNumber);
    *Trigger = 0;
    *Update = FALSE;
}

DEM_INLINE Dem_boolean_least Dem_EnvIsFFRecNumStored(const Dem_EvMemEventMemoryType *EventMemory, uint8 RecNumber)
{
    Dem_EventIdType EventId;

    EventId = Dem_EvMemGetEventMemEventIdByPtr(EventMemory);
    return (Dem_EnvGetIndexFromFFRecNum(EventId, RecNumber) < Dem_EvMemGetEventMemFreezeFrameCounterByPtr(EventMemory));
}

#else

#define DEM_ENV_FFRECNUM_INDEX_INVALID   0xFF

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const uint8 Dem_Cfg_EnvFFRecNumConf[DEM_CFG_FFRECCLASS_NUMBEROF_FFRECCLASSES][DEM_CFG_FFRECCLASS_MAXNUMBEROF_FFFRECNUMS];
#if DEM_CFG_FFRECCLASS_NUMBEROF_FFRECCLASSES > 1
DEM_ARRAY_DECLARE_CONST(uint8, Dem_Cfg_EnvEventId2FrecNumClass, DEM_EVENTID_ARRAYLENGTH);
#endif
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
uint8 Dem_EnvGetIndexOfFFRecConf(Dem_EventIdType EventId, uint8 RecNumber);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

typedef struct
{
   uint8 recordNumber;
   Dem_TriggerType trigger;
   boolean update;
} Dem_EnvFFRec;

extern const Dem_EnvFFRec Dem_Cfg_EnvFFRec[DEM_CFG_ENVFFREC_ARRAYLENGTH];

DEM_INLINE uint8 Dem_EnvGetFFRecNumClassIndex (Dem_EventIdType EventId)
{
#if DEM_CFG_FFRECCLASS_NUMBEROF_FFRECCLASSES > 1
	return Dem_Cfg_EnvEventId2FrecNumClass[EventId];
#else
	return 0;
#endif
}

DEM_INLINE Dem_boolean_least Dem_EnvIsFFRecNumValid(Dem_EventIdType EventId, uint8 RecNumber)
{
	uint8 RecNumberIndex;

	RecNumberIndex = Dem_EnvGetIndexOfFFRecConf(EventId,RecNumber);
	return (Dem_boolean_least)((RecNumber > 0) && (RecNumberIndex != DEM_ENV_FFRECNUM_INDEX_INVALID));
}

DEM_INLINE uint8 Dem_EnvGetIndexFromFFRecNum(Dem_EventIdType EventId, uint8 RecNumber)
{
	uint8 RecNumberIndex;

	RecNumberIndex = Dem_EnvGetIndexOfFFRecConf(EventId,RecNumber);
	DEM_ASSERT(RecNumberIndex != DEM_ENV_FFRECNUM_INDEX_INVALID,DEM_DET_APIID_ENVGETINDEXFROMFFRECNUM,0x0);
    return RecNumberIndex;
}


DEM_INLINE uint8 Dem_EnvGetFFRecNumFromIndex(Dem_EventIdType EventId, uint8 idx)
{
   DEM_ASSERT(idx < Dem_EvtGetMaxNumberOfFreezeFrames(EventId),DEM_DET_APIID_ENVGETFFRECNUMFROMINDEX,0x0);
   return Dem_Cfg_EnvFFRecNumConf [Dem_EnvGetFFRecNumClassIndex(EventId)][idx];
}

DEM_INLINE Dem_TriggerType Dem_EnvGetFFRecordTrigger (uint8 RecNumber)
{
    uint8 indx;

    for(indx = 1 ; indx < DEM_CFG_ENVFFREC_ARRAYLENGTH ; indx++)
    {
        if(Dem_Cfg_EnvFFRec[indx].recordNumber == RecNumber)
        {
            return Dem_Cfg_EnvFFRec[indx].trigger;
        }
    }
    return 0;
}

DEM_INLINE void Dem_EnvGetFFRecordTriggerAndUpdate (uint8 RecNumber, Dem_TriggerType* Trigger, boolean* Update)
{
    uint8 indx;

   for(indx = 1 ; indx < DEM_CFG_ENVFFREC_ARRAYLENGTH ; indx++)
   {
       if(Dem_Cfg_EnvFFRec[indx].recordNumber == RecNumber)
       {
           *Trigger = Dem_Cfg_EnvFFRec[indx].trigger;
           *Update = Dem_Cfg_EnvFFRec[indx].update;
           return;
       }
   }
   *Trigger = 0;
   *Update = FALSE;
}

DEM_INLINE Dem_boolean_least Dem_EnvIsFFRecNumStored(const Dem_EvMemEventMemoryType *EventMemory, uint8 RecNumber)
{
    uint8 indx;

    for(indx = 1 ; indx < DEM_CFG_ENVFFREC_ARRAYLENGTH ; indx++)
    {
        if(Dem_Cfg_EnvFFRec[indx].recordNumber == RecNumber)
        {
            return (Dem_EnvIsTriggerSet(Dem_Cfg_EnvFFRec[indx].trigger , Dem_EvMemGetEventMemTriggerByPtr(EventMemory)));
        }
    }
    return FALSE;

}

#endif
#endif
