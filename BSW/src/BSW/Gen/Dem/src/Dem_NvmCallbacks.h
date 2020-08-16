 


#ifndef DEM_NVMCALLBACKS_H
#define DEM_NVMCALLBACKS_H

#include "Dem_Cfg_NvmCallbacks.h"

#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
#include "rba_DemObdBasic_NvmCallbacks.h"
#endif

#if( DEM_BFM_ENABLED == DEM_BFM_ON )
#include "rba_DemBfm_Nvm.h"
#endif

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

Std_ReturnType Dem_EvMemNvMWriteRamBlockToNvCallback(void* NvMBuffer, uint16_least LocId);
Std_ReturnType Dem_EvMemNvmReadRamBlockFromNvCallback(void* NvMBuffer, uint16_least LocId);

Std_ReturnType Dem_PreStoredFFWriteRamBlockToNvCallback(void* NvMBuffer, uint16_least LocId);
Std_ReturnType Dem_PreStoredFFReadRamBlockFromNvCallback(void* NvMBuffer, uint16_least LocId);

Std_ReturnType Dem_EventStatusByteWriteRamBlockToNvCallback(void* NvMBuffer);
Std_ReturnType Dem_EventStatusByteReadRamBlockFromNvCallback(void* NvMBuffer);

Std_ReturnType Dem_HistoryStatusByteWriteRamBlockToNvCallback(void* NvMBuffer);
Std_ReturnType Dem_HistoryStatusByteReadRamBlockFromNvCallback(void* NvMBuffer);

Std_ReturnType Dem_DistMemWriteRamBlockToNvCallback(void* NvMBuffer);
Std_ReturnType Dem_DistMemReadRamBlockFromNvCallback(void* NvMBuffer);

Std_ReturnType Dem_GenericNVDataWriteRamBlockToNvCallback(void* NvMBuffer);
Std_ReturnType Dem_GenericNVDataReadRamBlockFromNvCallback(void* NvMBuffer);

Std_ReturnType Dem_EventIndicatorWriteRamBlockToNvCallback(void* NvMBuffer);
Std_ReturnType Dem_EventIndicatorReadRamBlockFromNvCallback(void* NvMBuffer);

Std_ReturnType Dem_HashIdWriteRamBlockToNvCallback(void* NvMBuffer);
Std_ReturnType Dem_HashIdReadRamBlockFromNvCallback(void* NvMBuffer);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

