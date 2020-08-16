

#include "Dem.h"
#include "Rte_Dem.h"

#include "Dem_StorageCondition.h"

#include "Dem_EventFHandling.h"
#include "Dem_EventRecheck.h"

#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)


#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"

Dem_StoCoState Dem_StoCoAllStates = { DEM_CFG_STOCO_INITIALSTATE, 0,0,0
#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
    ,{0},{0}
#endif
};

#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"



#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

static const Dem_StoCoParam Dem_StoCoAllParams = DEM_CFG_STOCO_PARAMS;

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
#endif


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


Std_ReturnType Dem_SetStorageCondition (uint8 StorageConditionID, boolean ConditionFulfilled)
{
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)

  Dem_StoCoList storageConditionBitmask;

  if (StorageConditionID >= DEM_STORAGECONDITION_COUNT)
  {
    DEM_DET(DEM_DET_APIID_SETSTORAGECONDITION, DEM_E_WRONG_CONFIGURATION);
    DEM_ASSERT_ISNOTLOCKED();
    return E_NOT_OK;
  }

   storageConditionBitmask = (Dem_StoCoList)(1u << StorageConditionID);

   DEM_ENTERLOCK_MON();

   if (ConditionFulfilled)
   {
      Dem_StoCoAllStates.isActive |= storageConditionBitmask;
   }
   else
   {
      Dem_StoCoAllStates.isActive &= (Dem_StoCoList)(~(uint32)storageConditionBitmask);
   }

   DEM_EXITLOCK_MON();

   return E_OK;

#else
   DEM_UNUSED_PARAM(StorageConditionID);
   DEM_UNUSED_PARAM(ConditionFulfilled);
   return E_NOT_OK;
#endif
}

Std_ReturnType Dem_GetStorageCondition (uint8 StorageConditionID, boolean* ConditionFulfilled)
{
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)

    Dem_StoCoList storageConditionBitmask;

    storageConditionBitmask = (Dem_StoCoList)(1u << StorageConditionID);

    *ConditionFulfilled = (0 != (Dem_StoCoAllStates.isActive & storageConditionBitmask));

    return E_OK;

#else
   DEM_UNUSED_PARAM(StorageConditionID);
   DEM_UNUSED_PARAM(ConditionFulfilled);
   return E_NOT_OK;
#endif
}




#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
void Dem_StoCoMainFunction(void)
{
   uint16_least i;
   Dem_StoCoList stoco_mask;
   for (i=0; i<DEM_STORAGECONDITION_COUNT; i++)
   {
      stoco_mask = (Dem_StoCoList)(1u << i);
      if (Dem_StoCoAllParams.replacementEvent[i] != DEM_EVENTID_INVALID)
      {
         if( (stoco_mask & Dem_StoCoAllStates.isReplacementEventRequested) != 0u )
         {

            (void)Dem_SetEventStatusWithEnvData(Dem_StoCoAllParams.replacementEvent[i], DEM_EVENT_STATUS_FAILED
#if (DEM_CFG_DEBUGDATA != DEM_CFG_DEBUGDATA_OFF)
                /* if debugdata is only 8 bit: use lower 8 bits */
               ,(Dem_DebugDataType)(Dem_StoCoAllStates.eventId[i]), Dem_StoCoAllStates.debug1[i]
#else
               ,0,0
#endif
               );


            DEM_ENTERLOCK_MON();       /* DSM_D_212 */

            Dem_StoCoAllStates.isReplacementEventRequested &=    (Dem_StoCoList)(~(uint32)stoco_mask);
            Dem_StoCoAllStates.hasGoodCheckTrigger &=            (Dem_StoCoList)(~(uint32)stoco_mask);
            Dem_StoCoAllStates.isReplacementEventStored |= stoco_mask;

            DEM_EXITLOCK_MON();       /* DSM_D_212 */
         }

         if( (stoco_mask & Dem_StoCoAllStates.isReplacementEventStored & Dem_StoCoAllStates.isActive) != 0u )
         {
            (void)Dem_SetEventStatusWithEnvData (Dem_StoCoAllParams.replacementEvent[i], DEM_EVENT_STATUS_PASSED,0,0);

            DEM_ENTERLOCK_MON();       /* DSM_D_212 */

            Dem_StoCoAllStates.isReplacementEventRequested &= (Dem_StoCoList)(~(uint32)stoco_mask);
            Dem_StoCoAllStates.hasGoodCheckTrigger &=         (Dem_StoCoList)(~(uint32)stoco_mask);
            Dem_StoCoAllStates.isReplacementEventStored &=    (Dem_StoCoList)(~(uint32)stoco_mask);

            DEM_EXITLOCK_MON();       /* DSM_D_212 */
         }
      }
      else
      {
         if( (stoco_mask & Dem_StoCoAllStates.isActive) != 0u )
         {
            DEM_ENTERLOCK_MON();       /* DSM_D_212 */
            {
               Dem_StoCoAllStates.isReplacementEventRequested &= (Dem_StoCoList)(~(uint32)stoco_mask);
               Dem_StoCoAllStates.hasGoodCheckTrigger &=         (Dem_StoCoList)(~(uint32)stoco_mask);
               Dem_StoCoAllStates.isReplacementEventStored &=    (Dem_StoCoList)(~(uint32)stoco_mask);
            }
            DEM_EXITLOCK_MON();       /* DSM_D_212 */
         }
      }
   }
}

#endif



#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)

void Dem_StoCoRecheckReplacementStorage(Dem_StoCoList storageConditions)
{
    DEM_ASSERT_ISLOCKED();

    /* if (any storagecondition is disabled) AND (none of the disabled stoco has stored or requested the replacement failure) */
    if (    ((storageConditions & (Dem_StoCoList)(~Dem_StoCoAllStates.isActive)) > 0u)
         && ((storageConditions & (Dem_StoCoList)(~Dem_StoCoAllStates.isActive) & (Dem_StoCoAllStates.isReplacementEventRequested | Dem_StoCoAllStates.isReplacementEventStored)) == 0u)
       )
    {
        Dem_StoCoAllStates.isReplacementEventRequested |= (storageConditions & (Dem_StoCoList)(~Dem_StoCoAllStates.isActive));
    }
}

#endif


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


