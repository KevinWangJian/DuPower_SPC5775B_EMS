



#include "Dem_Cfg_EnvExtendedData.h"
#include "Dem_Cfg_EnvExtendedDataRec.h"
#include "Dem_EnvExtendedData.h"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
const uint8 Dem_Cfg_EnvExtData2ExtDataRec[] = DEM_CFG_ENVEXTDATA2EXTDATAREC;

const Dem_EnvExtData Dem_Cfg_EnvExtData[DEM_CFG_ENVEXTDATA_ARRAYLENGTH] = DEM_CFG_ENVEXTDATA;
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
