

#ifndef DEM_DEBBASE_H
#define DEM_DEBBASE_H


#include "Dem_Types.h"
#include "Dem_Cfg_Deb.h"
#include "Dem_DebSharing.h"


typedef uint8_least (*Dem_DebFilter) (Dem_EventIdType EventId, Dem_EventStatusType* status, const void* paramSet, uint16 paramIndex DEM_DEB_LOCAL_CALC_PARAMS);
typedef void        (*Dem_DebGetLimits) (const void* paramSet, uint16 paramIndex, sint16_least* MinThreshold, sint16_least* MaxThreshold);
typedef void (*Dem_DebCyclic) (Dem_EventIdType EventId, const void* paramSet, uint16 paramIndex DEM_DEB_LOCAL_CALC_PARAMS);


typedef struct
{
   Dem_DebGetLimits funcPointer_GetLimits;
   Dem_DebCyclic funcPointer_Cyclic;
   const void* paramSet;
   uint16 paramCount;
   Dem_DebFilter funcPointer_Filter;
} Dem_DebClass;



#define  DEM_DEB_DEBLEVEL_MAXTHRESHOLD   (127)
#define  DEM_DEB_DEBLEVEL_MINTHRESHOLD   (-128)


/*
 * Identifier of a Debounce Action
 */
typedef uint8_least Dem_DebouncedActionType;
#define  DEM_DEBACTION_NOOP                        0x00u
#define  DEM_DEBACTION_SETFDCTHRESHOLDREACHED      0x01u
#define  DEM_DEBACTION_ALLOW_BUFFER_INSERT         0x02u
#define  DEM_DEBACTION_SETSUSPICIOUS               0x04u
#define  DEM_DEBACTION_RESETSUSPICIOUS             0x08u
#define  DEM_DEBACTION_INC_DISTURBANCECTR          0x10u
#define  DEM_DEBACTION_RESETFDCTHRESHOLDREACHED    0x20u



#if ( (DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON) && (!defined DEM_DEB_FORCE_CONST_CONFIG) )
#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
extern Dem_DebClass Dem_Cfg_DebClasses[DEM_CFG_DEB_NUMBEROFCLASSES];
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
#else
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
extern const Dem_DebClass Dem_Cfg_DebClasses[DEM_CFG_DEB_NUMBEROFCLASSES];
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
#endif


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_DebSwitchToAlternativeParameters(void);

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


#endif
