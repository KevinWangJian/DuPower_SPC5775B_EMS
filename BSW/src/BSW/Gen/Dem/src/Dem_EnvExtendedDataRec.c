


#include "Dem_Cfg_EnvExtendedDataRec.h"
#include "Dem_Cfg_EnvDataElement.h"
#include "Dem_EnvExtendedDataRec.h"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
const uint8 Dem_Cfg_EnvExtData2DataElement[] = DEM_CFG_ENVEXTDATA2DATAELEMENT;

const Dem_EnvExtDataRec Dem_Cfg_EnvExtDataRec[DEM_CFG_ENVEXTDATAREC_ARRAYLENGTH] = DEM_CFG_ENVEXTDATAREC;
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
