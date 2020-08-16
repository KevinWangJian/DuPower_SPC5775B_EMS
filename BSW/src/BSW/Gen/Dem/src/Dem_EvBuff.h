

#ifndef DEM_EVBUFF_H
#define DEM_EVBUFF_H


#include "Dem_Cfg_EvBuff.h"
#include "Dem_Cfg_Nodes.h"
#include "Dem_EvBuffEvent.h"
#include "Dem_Types.h"
#include "Dem_Mapping.h"
#include "Dem_Events.h"

typedef struct
{
    uint16 OverflowCounter;
    uint16 OverflowCounterSet;
    Dem_EvBuffEvent  Locations[DEM_CFG_EVBUFF_SIZE];
} Dem_EvtBufferState;


/************************************
 * DEM-internal interfaces
 ************************************/
#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"
extern Dem_EvtBufferState Dem_EvtBuffer;
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"

#if (DEM_CFG_FFPRESTORAGE_NONVOLATILE == DEM_CFG_FFPRESTORAGE_NONVOLATILE_ON)
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE_CONST(Dem_NvmBlockIdType, Dem_PreStoredFFNvmId, DEM_CFG_PRESTORED_FF_SIZE);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
#endif

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


void Dem_EvBuffRemoveAllPrestored (void);

void Dem_EvBuffMainFunction(void);


#if (DEM_CFG_FFPRESTORAGESUPPORT == DEM_CFG_FFPRESTORAGESUPPORT_ON)
void Dem_PreStoredFFInitCheckNvM(void);
void Dem_PreStoredFFShutdown(void);
#endif


Dem_boolean_least Dem_EvBuffInsert (Dem_EvBuffEventType eventType,
        Dem_EventIdType eventId
        DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0,Dem_DebugDataType debug1));

const Dem_EvBuffEvent* Dem_EvBuffGetEvent (uint32* locationIndex);

void Dem_EvBuffRemoveEvent (uint32 locationIndex);

void Dem_EvBuffEnvCaptureData(
    Dem_EventIdType EventId,
    uint8 *EnvData
    DEM_DEBUGDATA_PARAM(Dem_DebugDataType debug0,Dem_DebugDataType debug1));


#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
uint8_least Dem_EvBuffClearSequentialFailures (Dem_EventIdType EventId, Dem_ComponentIdType nodeID, uint8 counterInit);
#else

DEM_INLINE uint8_least Dem_EvBuffClearSequentialFailures (Dem_EventIdType EventId, Dem_ComponentIdType nodeID, uint8 counterInit) {
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(nodeID);
    DEM_UNUSED_PARAM(counterInit);
    return 0;
}

#endif


void Dem_EvBuffClear (Dem_EventIdType EventId);

Dem_boolean_least Dem_EvBuffIsEventPending (Dem_EventIdType EventId);

DEM_INLINE Dem_boolean_least Dem_EvBuffIsAnyEventPending (void)
{
    return Dem_EvBuffIsEventPending (DEM_EVENTID_INVALID);
}


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif
