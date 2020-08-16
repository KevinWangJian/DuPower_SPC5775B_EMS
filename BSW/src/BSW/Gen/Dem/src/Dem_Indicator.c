

#include "Dem.h"
#include "Rte_Dem.h"

#include "Dem_EventStatus.h"
#include "Dem_Prv_CallEvtStChngdCbk.h"
#include "Dem_Obd.h"

#if (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

DEM_ARRAY_DEFINE(Dem_IndicatorStatus, Dem_AllIndicatorStatus, DEM_INDICATORID_ARRAYLENGTH);

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

#endif



#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


Std_ReturnType Dem_SetIndicatorStatusForEvent (Dem_EventIdType EventId, Dem_IndicatorIdType IndicatorId, boolean IndicatorActivation)
{
#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)

    Std_ReturnType retVal = E_NOT_OK;
    Dem_EventIndicatorAttributeIterator it;
    uint16_least currentIndicAttrib = 0;
    uint8 indicatorBehaviour;
    Dem_UdsStatusByteType statusOld, statusNew, dtcStByteOld;

    if (!Dem_isIndicatorIdValid(IndicatorId) || !(Dem_isEventIdValid(EventId)))
    {
        return E_NOT_OK;
    }

    for ( Dem_EventIndicatorAttributeIteratorNew(EventId, &it);
            Dem_EventIndicatorAttributeIsValid(EventId, &it);
            Dem_EventIndicatorAttributeNext(&it)
    )
    {
        currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);

        if (Dem_IsIndicatorAttributeValid(currentIndicAttrib))
        {
            if (   (Dem_IndicatorAttrib_GetIndicatorId(currentIndicAttrib) == IndicatorId)
                    && (Dem_IndicatorAttrib_IsApiControl(currentIndicAttrib) == TRUE)
            )
            {

                DEM_ENTERLOCK_MON();
                indicatorBehaviour = Dem_IndicatorAttrib_GetBehaviour(currentIndicAttrib);

                if (IndicatorActivation == TRUE)
                {
                    Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, 0);
                    Dem_IndicatorAttribSetFailureCycCtr(currentIndicAttrib, 0xFF);
                    Dem_IndicatorIncrementBehaviourCounter(IndicatorId, indicatorBehaviour);
                }
                else
                {
                    Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, 0xFF);
                    Dem_IndicatorAttribSetFailureCycCtr(currentIndicAttrib, 0);
                    Dem_IndicatorDecrementBehaviourCounter(IndicatorId, indicatorBehaviour);
                }
                retVal = E_OK;
                DEM_EXITLOCK_MON();

                break;
            }
        }
    }

    DEM_ENTERLOCK_MON();
    Dem_StatusChange_GetOldStatus(EventId, &statusOld, &dtcStByteOld);
    statusNew = Dem_EvtGetIsoByte(EventId);

    if (IndicatorActivation)
    {
        Dem_EvtSt_HandleIndicatorOn(EventId);
    }
    else
    {
        Dem_UpdateISO14229WIRStatus(EventId);
    }

    statusNew = Dem_EvtGetIsoByte(EventId);

    DEM_EXITLOCK_MON();

    if (statusNew != statusOld )
    {
        Dem_CallBackTriggerOnEventStatus(EventId, statusOld, statusNew, dtcStByteOld);
    }

    return retVal;

#else /* DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON */
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(IndicatorId);
    DEM_UNUSED_PARAM(IndicatorActivation);
    return E_NOT_OK;
#endif /* DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON */
}


#if (DEM_CFG_EVT_INDICATOR != DEM_CFG_EVT_INDICATOR_PROJECTSPECIFIC)

#if (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
/* MR12 RULE 8.13 VIOLATION: Function defined according to AR Spec IndicatorStatus not changed if OBD is OFF */
Std_ReturnType Dem_GetIndicatorStatus(uint8 IndicatorId, Dem_IndicatorStatusType* IndicatorStatus)
{

	DEM_ENTRY_CONDITION_CHECK_DEM_INITIALIZED(DEM_DET_APIID_DEM_GETINDICATORSTATUS,E_NOT_OK);
	DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(IndicatorStatus,DEM_DET_APIID_DEM_GETINDICATORSTATUS,E_NOT_OK);

/* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
   if (IndicatorId == DEM_OBD_CFG_MIL_INDICATOR_ID)
   {
      *IndicatorStatus = rba_DemObdBasic_Mil_GetIndicatorStatusExternal();
      return E_OK;
   }
#endif
 /* FC_VariationPoint_END */

	if(!Dem_isIndicatorIdValid(IndicatorId))
	{
	    DEM_DET(DEM_DET_APIID_DEM_GETINDICATORSTATUS,DEM_E_WRONG_CONFIGURATION);
	    DEM_ASSERT_ISNOTLOCKED();
	    return E_NOT_OK;
	}

	*IndicatorStatus = Dem_EvtGetIndicatorStatus(IndicatorId);
	return E_OK;
}
#endif

FUNC(Std_ReturnType, Dem_CODE) Dem_SetWIRStatus (
        VAR(Dem_EventIdType, AUTOMATIC) EventId,
        VAR(boolean, AUTOMATIC) WIRStatus
)
{
    Std_ReturnType ret_val = E_OK;

    Dem_UdsStatusByteType statusOld, statusNew, dtcStByteOld;


    statusOld = DEM_ISO14229BYTE_INITVALUE;
    statusNew = DEM_ISO14229BYTE_INITVALUE;
    dtcStByteOld = DEM_ISO14229BYTE_INITVALUE;

    DEM_ENTRY_CONDITION_CHECK_INIT_EVTIDVALID_EVTAVAILABLE(EventId,DEM_DET_APIID_DEM_SETWIRSTATUS,E_NOT_OK);

    DEM_ENTERLOCK_MON();

    if (       Dem_EvtIsSuppressed(EventId)
            || !Dem_IsEventReportingEnabledByDtcSetting(EventId)
            || !Dem_EvtRequestsWarningIndicator(EventId)
    )
    {
        ret_val = E_NOT_OK;
    }
    else
    {
        if (WIRStatus)
        {
            /*Set Bit corresponding to WIRStatus as TRUE within Dem_AllEventsState[EventId].state
                Invoke Dem_EvtSetWIR to set WIRStatus bit for that event*/

            Dem_StatusChange_GetOldStatus(EventId, &statusOld, &dtcStByteOld);
            statusNew = statusOld;
            Dem_EvtSetWIRExtern(EventId, TRUE);
            if (!Dem_ISO14229ByteIsWarningIndicatorRequested(statusOld))
            {
                Dem_EvtSt_HandleIndicatorOn(EventId);
                statusNew = Dem_EvtGetIsoByte(EventId);
#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
                FiM_DemTriggerOnEventStatus (EventId, statusOld, statusNew);
#endif
            }
        }
        else
        {
            /*Set Bit corresponding to WIRStatus as FALSE within Dem_AllEventsState[EventId].state*/
            Dem_EvtSetWIRExtern(EventId, FALSE);
            Dem_StatusChange_GetOldStatus(EventId, &statusOld, &dtcStByteOld);
            statusNew = statusOld;
            if (Dem_ISO14229ByteIsWarningIndicatorRequested(statusOld))
            {
					Dem_UpdateISO14229WIRStatus(EventId);
                    statusNew = Dem_EvtGetIsoByte(EventId);
#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
                    FiM_DemTriggerOnEventStatus (EventId, statusOld, statusNew);
#endif
            }
            else
            {
                //nothing to do
            }
        }
    }

    DEM_EXITLOCK_MON();

    if (statusNew != statusOld )
    {
        Dem_CallBackTriggerOnEventStatus(EventId, statusOld, statusNew, dtcStByteOld);
    }

    return ret_val;
}

#endif



void Dem_UpdateISO14229WIRStatus (Dem_EventIdType EventId)
{
    if (        (!Dem_EvtIsWIRExternal(EventId))
            &&  (!Dem_isAnyIndicatorAttribOn(EventId))
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
            &&  (!rba_DemObdBasic_Event_IsRequestingMil(EventId))
#endif
    )
    {
        Dem_EvtSt_HandleIndicatorOff(EventId);
    }
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


