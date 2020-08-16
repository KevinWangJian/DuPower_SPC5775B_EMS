


#ifndef DEM_OPERATIONCYCLE_H
#define DEM_OPERATIONCYCLE_H


#include "Dem_Cfg_OperationCycle.h"
#include "Dem_Types.h"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
extern Dem_OperationCycleList Dem_OperationCycleStates;
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

DEM_INLINE Dem_boolean_least Dem_isOperationCycleStarted (uint8 OperationCycleId)
{
    return DEM_OPERATIONCYCLE_ISBITSET(Dem_OperationCycleStates, OperationCycleId);
}

DEM_INLINE Dem_boolean_least Dem_IsOperationCycleIdValid (uint8 OperationCycleId)
{
	/* as id is of type uint8 it is always positiv and hence check against >= 0 not necessary
	 * return ((0 <= checkID) && (checkID < DEM_OPERATIONCYCLE_COUNT));
	 */
	return (OperationCycleId < DEM_OPERATIONCYCLE_COUNT);
}
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
void Dem_OperationCycleInit (void);

void Dem_OperationCyclesMainFunction(void);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif


