

#ifndef DEM_CHRONOSORT_H
#define DEM_CHRONOSORT_H

#include "Dem_Cfg_DTCs.h"

#if (DEM_CFG_REPORT_CHRONOLOGICAL_ORDER_HOOKS_ENABLED)

#include "Dem_DTCFilter.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

boolean Dem_IsChronoSortEnabled(void);

void Dem_ChronoSortDTCFilterInit(void);

void Dem_ChronoSortEvMemUpdateSortId(uint16_least LocId,uint16_least MemId,uint16_least StatusOld,uint16_least StatusNew,uint16_least *WriteSts);

boolean Dem_ChronoSortSetDTCFilter(const Dem_DTCFilterState* DTCFilter);

void Dem_ChronoSortMainFunction(const Dem_DTCFilterState* DTCFilter);

Dem_ReturnGetNextFilteredDTCType Dem_ChronoSortGetNextFilteredDTCID (Dem_DtcIdType* dtcId, uint32* DTC, uint8* DTCStatus);

Dem_ReturnGetNumberOfFilteredDTCType Dem_ChronoSortGetNumberOfFilteredDTC(uint16* NumberOfFilteredDTC);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

#endif
