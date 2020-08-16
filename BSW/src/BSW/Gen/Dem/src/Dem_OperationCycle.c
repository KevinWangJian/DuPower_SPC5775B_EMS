

#include "Dem.h"
#include "Rte_Dem.h"

#include "Dem_OperationCycle.h"
#include "Dem_Events.h"
#include "Dem_Main.h"
#include "Dem_Lock.h"
#include "Dem_Mapping.h"
#include "Dem_EventStatus.h"
#include "Dem_ISO14229Byte.h"
#include "Dem_EvMem.h"
#include "Dem_EventRecheck.h"
#include "Dem_Obd.h"
#include "Dem_GenericNvData.h"

#include "Dem_Bfm.h"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
Dem_OperationCycleList Dem_OperationCycleStates;
static Dem_OperationCycleList Dem_StartOperationCycleCollectedTriggers;
/* static Dem_OperationCycleList Dem_StopOperationCycleCollectedTriggers; */
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

Std_ReturnType Dem_SetOperationCycleState (uint8 OperationCycleId, Dem_OperationCycleStateType CycleState)
{
    Std_ReturnType retVal = E_OK;
    Dem_OperationCycleList operationCycleBitmask;

    if (!Dem_IsOperationCycleIdValid(OperationCycleId))
    {
        DEM_DET(DEM_DET_APIID_DEM_SETOPERATIONCYCLESTATE , DEM_E_WRONG_CONFIGURATION);
        DEM_ASSERT_ISNOTLOCKED();
        return E_NOT_OK;
    }

    operationCycleBitmask = DEM_OPERATIONCYCLE_BITMASK(OperationCycleId, 1);

    DEM_ENTERLOCK_MON();
    /* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
    rba_DemObdBasic_SetOperationCycleState(&operationCycleBitmask, CycleState);
#endif
    /* FC_VariationPoint_END */
    if (CycleState == DEM_CYCLE_STATE_START)
    {
        DEM_OPERATIONCYCLE_SETBITMASK(&Dem_OperationCycleStates, operationCycleBitmask);
        DEM_OPERATIONCYCLE_SETBITMASK(&Dem_StartOperationCycleCollectedTriggers, operationCycleBitmask);
    }
    else if (CycleState == DEM_CYCLE_STATE_END)
    {
        DEM_OPERATIONCYCLE_CLEARBITMASK(&Dem_OperationCycleStates, operationCycleBitmask);
    }
    else
    {
        DEM_DET(DEM_DET_APIID_DEM_SETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
        retVal = E_NOT_OK;
    }

    DEM_EXITLOCK_MON();
    return retVal;
}



DEM_INLINE Dem_OperationCycleStateType Dem_GetOpcycStatus(uint8 OperationCycleId)
{
    Dem_OperationCycleList operationCycleBitmask = (Dem_OperationCycleList) (1u << OperationCycleId);
    if ((Dem_OperationCycleStates & operationCycleBitmask) != 0u)
    {
        return DEM_CYCLE_STATE_START;
    }
    else
    {
        return DEM_CYCLE_STATE_END;
    }
}

Std_ReturnType Dem_GetOperationCycleState(uint8 OperationCycleId, Dem_OperationCycleStateType* CycleState)
{
    /*  Entry Condition Check   */
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(CycleState,DEM_DET_APIID_DEM_GETOPERATIONCYCLESTATE,E_NOT_OK);
    if (!Dem_IsOperationCycleIdValid(OperationCycleId))
    {
        DEM_DET(DEM_DET_APIID_DEM_GETOPERATIONCYCLESTATE, DEM_E_WRONG_CONFIGURATION);
        return E_NOT_OK;
    }

    *CycleState = Dem_GetOpcycStatus(OperationCycleId);
    return E_OK;
}

void Dem_OperationCyclesMainFunction(void)
{
   Dem_OperationCycleList currentTriggers;

   if (Dem_StartOperationCycleCollectedTriggers != 0)
   {
	  DEM_ENTERLOCK_MON();
      currentTriggers = Dem_StartOperationCycleCollectedTriggers;
      Dem_StartOperationCycleCollectedTriggers = 0;
      DEM_EXITLOCK_MON();
/* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
      /* check mil state before update of event status to get the state from last driving cycle! */
      rba_DemObdBasic_StartOperationCycle(currentTriggers);
#endif
/* FC_VariationPoint_END */
/* FC_VariationPoint_START */
#if( DEM_BFM_ENABLED == DEM_BFM_ON )
      rba_DemBfm_CounterAdvanceOperationCycle( currentTriggers );
#endif
/* FC_VariationPoint_END */
      Dem_EvMemStartOperationCycleAllMem(currentTriggers);
      Dem_EvtAdvanceOperationCycle(currentTriggers);
      Dem_RecheckNodeNotRecoverableRequest();
      /* trigger NvM storage */
#if (DEM_CFG_OPERATIONCYCLESTATUSSTORAGE == DEM_CFG_OPERATIONCYCLESTATUSSTORAGE_ON)
      Dem_GenericNvData.OperationCycleStates = Dem_OperationCycleStates;

      /* notify to store in NVM */
      Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_DEM_GENERIC_NV_DATA);
#endif
   }
   else
   {
#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
       Dem_EnCoCallbacks();
#endif
   }
}

void Dem_OperationCycleInit (void)
{
#if (DEM_CFG_OPERATIONCYCLESTATUSSTORAGE == DEM_CFG_OPERATIONCYCLESTATUSSTORAGE_ON)
   DEM_ENTERLOCK_MON();
   Dem_OperationCycleStates |= Dem_GenericNvData.OperationCycleStates;
   DEM_EXITLOCK_MON();
#endif
}


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
