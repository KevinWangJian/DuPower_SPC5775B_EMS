

#ifndef DEM_PRV_J1939DCM_H
#define DEM_PRV_J1939DCM_H

#include "Dem_Types.h"

#if(DEM_CFG_J1939DCM != DEM_CFG_J1939DCM_OFF)

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#if(DEM_CFG_J1939DCM_CLEAR_SUPPORT != DEM_CFG_J1939DCM_OFF)
Dem_ReturnClearDTCType Dem_J1939DcmClearDTCBody(Dem_J1939DcmSetClearFilterType DTCTypeFilter , uint8 node);
void Dem_J1939DcmClearDTCMainFunction(void);
#endif  /* DEM_CFG_J1939DCM_CLEAR_SUPPORT */

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif  /* DEM_CFG_J1939DCM */

#endif
