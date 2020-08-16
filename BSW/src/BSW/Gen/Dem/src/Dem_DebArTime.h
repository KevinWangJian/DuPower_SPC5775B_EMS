


#ifndef DEM_DEBARTIME_H
#define DEM_DEBARTIME_H



#include "Dem_Types.h"
#include "Dem_DebSharing.h"


typedef struct
{
   sint16 TimeFailedThreshold;
   sint16 TimePassedThreshold;
   sint16 FDCThreshold;
   sint16 SuspiciousThreshold;
} Dem_DebArTime_ParamSet;

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

uint8_least Dem_DebArTime_Filter (Dem_EventIdType EventId, Dem_EventStatusType* status, const void* paramSet, uint16 paramIndex DEM_DEB_LOCAL_CALC_PARAMS);
void        Dem_DebArTime_GetLimits (const void* paramSet, uint16 paramIndex, sint16_least* MinThreshold, sint16_least* MaxThreshold);
void        Dem_DebArTime_Cyclic (Dem_EventIdType EventId, const void* paramSet, uint16 paramIndex DEM_DEB_LOCAL_CALC_PARAMS);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

