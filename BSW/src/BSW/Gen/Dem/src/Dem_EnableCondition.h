


#ifndef DEM_ENABLECONDITION_H
#define DEM_ENABLECONDITION_H


#include "Dem_Types.h"
#include "Dem_Cfg_EnableCondition.h"


#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)

typedef struct {
   Dem_EnCoList isActive;
} Dem_EnCoState;

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
extern Dem_EnCoState Dem_EnCoAllStates;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"

#endif

/* Dem449: If one enable condition is not fulfilled, all status reports from SW-Cs
   (Dem_SetEventStatus and Dem_ResetEventStatus) and BSW modules (Dem_ReportErrorStatus)
   for those events being assigned to this condition shall be ignored (no change of
   UDS DTC status byte) by the DEM.
 */

DEM_INLINE Dem_boolean_least Dem_EnCoAreAllFulfilled (Dem_EnCoList enableConditionList)
{
#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
   return ((enableConditionList & Dem_EnCoAllStates.isActive) == enableConditionList);
#else
   DEM_UNUSED_PARAM(enableConditionList);
   return TRUE;
#endif
}

DEM_INLINE Dem_boolean_least Dem_EnCoFulfilled (Dem_EnCoList enableConditionBitmask)
{
    return Dem_EnCoAreAllFulfilled (enableConditionBitmask);
}

#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
void Dem_EnCoCallbacks(void);
#endif

#endif

