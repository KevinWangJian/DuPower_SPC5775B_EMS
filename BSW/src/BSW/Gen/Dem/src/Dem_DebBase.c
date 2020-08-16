


#include "Dem.h"
#include "Rte_Dem.h" /* For the callbacks */

#include "Dem_DebBase.h"

#include "Dem_DebSharing.h"
#include "Dem_DebArTime.h"
#include "Dem_DebCtrBaseClass.h"
#include "Dem_DebMonInternal.h"
#include "Dem_Cfg_ExtPrototypes.h"
#include "Dem_Lib.h"


#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_CFG_DEB_DEFINE_ALL_PARAMSETS
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"



#if ( (DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON) && (!defined DEM_DEB_FORCE_CONST_CONFIG) )
#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
Dem_DebClass Dem_Cfg_DebClasses[DEM_CFG_DEB_NUMBEROFCLASSES] = DEM_CFG_DEB_CLASSES;
#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"
#else
#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
const Dem_DebClass Dem_Cfg_DebClasses[DEM_CFG_DEB_NUMBEROFCLASSES] = DEM_CFG_DEB_CLASSES;
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
#endif



#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
void Dem_DebSwitchToAlternativeParameters(void)
{
#if ( (DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON) && (!defined DEM_DEB_FORCE_CONST_CONFIG) )
    Dem_Cfg_DebClasses[DEM_DEBMETH_IDX_ARCTRBASECLASS].paramSet = &Dem_Cfg_DebCounterBaseClass_Paramsets[DemConf_DemRbDebounceCounterSet_Alternative];
#endif
}


Std_ReturnType Dem_DebSwitchToParameters(uint8 CounterParamSetId)
{
    Std_ReturnType ReturnValue = E_NOT_OK;

#if ( ((DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON) && (DEMRB_DEBOUNCECOUNTERSETS_SIZE != 0))\
    && (!defined DEM_DEB_FORCE_CONST_CONFIG) )

   if(CounterParamSetId < DEMRB_DEBOUNCECOUNTERSETS_SIZE)
   {
         Dem_Cfg_DebClasses[DEM_DEBMETH_IDX_ARCTRBASECLASS].paramSet = &Dem_Cfg_DebCounterBaseClass_Paramsets[CounterParamSetId];
        ReturnValue = E_OK;
   }
   else
   {
          /* To avoid warning */
   }
#endif

   return ReturnValue;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
