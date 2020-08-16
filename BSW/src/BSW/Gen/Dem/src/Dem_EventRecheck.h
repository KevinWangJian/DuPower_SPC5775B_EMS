


#ifndef DEM_DEPENDENCY_H
#define DEM_DEPENDENCY_H


#include "Dem_Cfg_Nodes.h"
#include "Dem_Cfg_StorageCondition.h"
#include "Dem_Cfg_Main.h"
#include "Dem_Dependencies.h"
#include "Dem_Mapping.h"


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"



#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)

void Dem_DependencyInit(void);
void Dem_RecheckNodeNotRecoverableRequest(void);
void Dem_DependencyMainFunction(void);


#else

DEM_INLINE void Dem_DependencyInit(void) {}
DEM_INLINE void Dem_RecheckNodeNotRecoverableRequest(void) {}
DEM_INLINE void Dem_DependencyMainFunction(void) {}

#endif




#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


#endif

