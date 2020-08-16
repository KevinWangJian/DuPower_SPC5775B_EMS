


#ifndef DEM_CLEAR_H
#define DEM_CLEAR_H

#include "Dem_Cfg_Clear.h"
#include "Dem_Types.h"
#include "Dem_Cfg_Events.h"
#include "Dem_Mapping.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_ClearMainFunction(void);
void Dem_ClearDtcInit(void);
boolean Dem_ClearIsInProgress (void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


#endif
