

#include "Dem.h"
#include "Rte_Dem.h"

#include "Dem_Events.h"

#include "Dem_Dependencies.h"
#include "Dem_EventRecheck.h"
#include "Dem_Deb.h"
#include "Dem_Cfg_ExtPrototypes.h"
#include "Dem_Cfg_EventsCallback.h"
#include "Dem_DTCs.h"
#include "Dem_EventStatus.h"
#include "Dem_Prv_CallEvtStChngdCbk.h"


#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

uint16 Dem_GlobalInitMonitoringCounter;

#if(DEM_CFG_EVTDISABLESTATUSUPDATE == DEM_CFG_EVTDISABLESTATUSUPDATE_ON)
boolean Dem_EvtGlobalStatusUpdateState;
#endif

DEM_ARRAY_DEFINE(Dem_EvtState, Dem_AllEventsState, DEM_EVENTID_ARRAYLENGTH);
DEM_ARRAY_DEFINE(Dem_EvtState8, Dem_AllEventsState8, DEM_EVENTID_ARRAYLENGTH);
DEM_BITARRAY_DEFINE(Dem_AllEventsResetDebouncerRequested, DEM_EVENTID_ARRAYLENGTH);
DEM_BITARRAY_DEFINE(Dem_EventWasPassedReported,DEM_EVENTID_ARRAYLENGTH);

uint32 Dem_EvtIsAnyInitMonitoringRequestedMask;

#if (DEM_CFG_BUILDTARGET == DEM_CFG_BUILDTARGET_DEMTESTSUITE)
    extern boolean TESTSUITE_ALLOW_INITIALIZE_EVENT_SUPPRESSION;
#endif

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
DEM_BITARRAY_DEFINE(Dem_AllEventsHistoryStatus, DEM_EVENTID_ARRAYLENGTH);
#endif

#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

#if (DEM_CFG_EVT_ATTRIBUTE == DEM_CFG_EVT_ATTRIBUTE_ON)
DEM_ARRAY_DEFINE_CONST(Dem_EventAttributeType, Dem_AllEventsUserAttributes, DEM_EVENTID_ARRAYLENGTH, DEM_CFG_EVTUSERATTRIBUTES);
#endif

#if (DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
DEM_ARRAY_DEFINE_CONST(Dem_EvtStatusChangeFncType, Dem_AllEventsStatusChangedFnc, DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS, DEM_EVT_ST_CH_CALLBACK_FUNCTIONS);
#endif

/* MR12 RULE 1.3 VIOLATION: A function-like macro shall not be invoked without all of its arguments, hence some of the arguments are optional based on configuration */
DEM_ARRAY_DEFINE_CONST(Dem_EvtParamFlags, Dem_AllEventsParamFlags, DEM_EVENTID_ARRAYLENGTH, DEM_CFG_EVENTPARAMS_FLAGS);
DEM_ARRAY_DEFINE_CONST(Dem_EvtParam, Dem_AllEventsParam, DEM_EVENTID_ARRAYLENGTH, DEM_CFG_EVENTPARAMS);
#if (DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)
DEM_ARRAY_DEFINE_CONST(Dem_EvtCategoryPriority, Dem_EvtCategoryPrio, DEM_EVENTCATPRIO_ARRAYLENGTH, DEM_CFG_EVTCATEGORYPRIO);
#endif

#if(DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED == TRUE)
DEM_ARRAY_DEFINE_CONST(Dem_InitMonitorForE, Dem_Cfg_Callback_InitMForE_List, DEM_CFG_CALLBACK_INITMFORE_LISTLENGTH, DEM_CFG_CALLBACK_INITMFORE_LIST);
#endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"



#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

DEM_DTC_ST_CH_CALLBACK_FUNCTION
DEM_EVT_ST_CH_CONTAINERCALLBACKS

/*----------------------------------------------------------------------------*/


void Dem_EvtSetCausal(Dem_EventIdType EventId, Dem_boolean_least causal)
{
	Dem_ComponentIdType nodeId = Dem_NodeIdFromEventId(EventId);

	DEM_ASSERT_ISLOCKED();

	Dem_EvtSetCausal_Flag(EventId, causal);
	if (Dem_NodeIdIsValid(nodeId))
	{
		Dem_NodeSetHasCausalFault(nodeId, causal);
	}
}

Dem_boolean_least Dem_EvtIsRecoverable(Dem_EventIdType EventId)
{
    /* resetting failure is only allowed, if failure is recoverable or failure is sequential */
    return (
            (   Dem_EvtIsRecoverable_Flag(EventId)
                    && Dem_NodeRecoveryAllowed(Dem_NodeIdFromEventId(EventId))
            )
            || (!Dem_EvtIsCausal(EventId))
            || (Dem_EvtIsRecheckedAndWaitingForMonResult(EventId)) /* in case the fault is rechecked and still in evbuffer */
            || (!Dem_EvtSt_GetTestFailedTOC(EventId))
    );
}


boolean Dem_EvtClearEventAllowed ( Dem_EventIdType eventId )
{
  boolean ret_val = TRUE;
  DEM_UNUSED_PARAM(eventId);

#if ( DEM_CFG_EVT_CLEARALLOWEDCALLBACK != DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF )
  if ( Dem_AllEventsParam[eventId].clrAllwdCBFnc != NULL_PTR )
  {
    (void) (Dem_AllEventsParam[eventId].clrAllwdCBFnc)(&ret_val);
  }
  else
#endif
  {
#if ( DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK != DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACK_OFF )
    (void) DEM_CFG_EVT_GLOBALCLEARALLOWEDCALLBACKFNC (eventId, &ret_val);
#endif
  }
  return (ret_val);
}


void Dem_EvtPreInitEvents(void)
{
	Dem_EventIdIterator eventIt;
	Dem_EventIdType eventId;

	for (Dem_EventIdIteratorNew(&eventIt); Dem_EventIdIteratorIsValid(&eventIt); Dem_EventIdIteratorNext(&eventIt))
	{
		eventId = Dem_EventIdIteratorCurrent(&eventIt);
		Dem_EvtSetLastReportedEvent(eventId, DEM_EVENT_STATUS_INVALIDREPORT);
		Dem_EvtSt_HandleInitialization(eventId);

		/**
		 * Function to update "DemEventSuppression" configuration value as intial value for availability of an event
		 * and may be changed dynamically via API Dem_SetEventSuppression().
		 */
#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
#if (DEM_CFG_BUILDTARGET == DEM_CFG_BUILDTARGET_DEMTESTSUITE)
		if (TESTSUITE_ALLOW_INITIALIZE_EVENT_SUPPRESSION)
#endif
		{
		    Dem_boolean_least initialSuppression = Dem_EvtGetInitialSuppressionStatus(eventId);
		    if (Dem_EvtIsSuppressed(eventId) != initialSuppression)
		    {
		        DEM_ENTERLOCK_MON();
		        Dem_EvtSetSuppression(eventId, initialSuppression);
		        DEM_EXITLOCK_MON();
		    }
		}
#endif
	}
}

void Dem_EvtInitEvents(void)
{
#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
    Dem_EventIdType EventId;
    Dem_EventIdIterator eventIt;

    for (Dem_EventIdIteratorNew(&eventIt); Dem_EventIdIteratorIsValid(&eventIt); Dem_EventIdIteratorNext(&eventIt))
    {
        EventId = Dem_EventIdIteratorCurrent(&eventIt);
        if(Dem_EvtIsSuppressed(EventId))
        {
            Dem_EvtSt_HandleEvtNotAvailable(EventId);
        }
    }
#endif
}

/* According to prototype "Std_ReturnType InitBlockCallbackFunction(void)" from NVM, this callback shall be called by
 * NVM, if the Iso-statusbytes may not be read from EEPROM. => enter in NvMInitBlockCallback
 */
Std_ReturnType Dem_EvtResetIsoByteCallback(void)
{
	Dem_EventIdIterator eventIt;

	for (Dem_EventIdIteratorNew(&eventIt); Dem_EventIdIteratorIsValid(&eventIt); Dem_EventIdIteratorNext(&eventIt))
	{
        Dem_EvtSt_HandleInitialization(Dem_EventIdIteratorCurrent(&eventIt));
	}
	return E_OK;
}


boolean Dem_IsInitMonitorForEventRequested(Dem_EventIdType EventId, Dem_InitMonitorReasonType* InitMonitorReason)
{
	uint8_least initMonitoring = Dem_EvtIsInitMonitoringRequested(EventId);

	if (initMonitoring != 0u)
	{
		DEM_ENTERLOCK_MON();

		*InitMonitorReason = Dem_EvtIsInitMonitoringRequested(EventId); /* has to be querried again here inside the lock! */
		Dem_EvtClearInitMonitoringRequests(EventId);

		DEM_EXITLOCK_MON();
		return TRUE;
	}
	return FALSE;
}



Std_ReturnType  Dem_GetEventTested(Dem_EventIdType  EventId,
                                   boolean*         EventTested)
{
    DEM_ENTRY_CONDITION_CHECK_INIT_EVTIDVALID_EVTAVAILABLE(EventId,DEM_DET_APIID_DEM_GETEVENTTESTED,E_NOT_OK);
    DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(EventTested,DEM_DET_APIID_DEM_GETEVENTTESTED,E_NOT_OK);

	*EventTested = (boolean) Dem_EvtSt_GetTestCompleteTOC(EventId);
	return E_OK;
}

Std_ReturnType  Dem_GetEventTested_GeneralEvtInfo(Dem_EventIdType  EventId,
                                   boolean*         EventTested)
{

    return Dem_GetEventTested(EventId, EventTested);
}



Std_ReturnType Dem_GetEventCategory( Dem_EventIdType EventId, Dem_EventCategoryType *EventCategory)
{
#if (DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)
	Dem_EventCategoryType evtCategory;

	if(!Dem_isEventIdValid(EventId))
	{
		return E_NOT_OK;
	}
	else
	{
		evtCategory = Dem_EvtGetCategory(EventId);

		if (( evtCategory <= DEM_CFG_CATEGORY_COUNT ) && ( evtCategory != DemConf_DemEventCategory_INVALIDCATEGORY ))
		{
			*EventCategory = evtCategory;
			return E_OK;
		}
		else
		{
			return E_NOT_OK;
		}
	}
#else
	(void) EventId;
	*EventCategory = 0;
	return E_NOT_OK;
#endif
}

/**********Event User Attribute **************************************************/
#if (DEM_CFG_EVT_ATTRIBUTE == DEM_CFG_EVT_ATTRIBUTE_ON)
const Dem_EventAttributeType* Dem_getEventUserAttributes(Dem_EventIdType EventId)
{
	return (&Dem_AllEventsUserAttributes[EventId]);
}
#endif


Std_ReturnType Dem_GetDtcKindOfEvent (Dem_EventIdType EventId, Dem_DTCKindType *DtcKind)
{
   if(!Dem_isEventIdValid(EventId))
   {
      return E_NOT_OK;
   }
   else
   {
      if (!Dem_isDtcIdValid(Dem_DtcIdFromEventId(EventId)))
      {
         return E_NOT_OK;
      }
      else
      {
         *DtcKind = Dem_DtcGetKind(Dem_DtcIdFromEventId(EventId));
         return E_OK;
      }
   }
}


#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
void Dem_EvtSetSuppression (Dem_EventIdType EventId, Dem_boolean_least newSuppressed)
{
    Dem_DtcIdType dtcId;

#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
    Dem_UdsStatusByteType isoByteOld, isoByteNew;
#endif

    if (Dem_EvtIsSuppressed(EventId) != newSuppressed)
    {
        DEM_ASSERT_ISLOCKED();

        dtcId = Dem_DtcIdFromEventId(EventId);

#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
        isoByteOld = Dem_EvtGetIsoByte(EventId);
#endif
        DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_NOTAVAILABLE, newSuppressed);
        if ( dtcId != DEM_DTCID_INVALID )
        {
            Dem_DtcHandleEventSuppression(dtcId, !newSuppressed);
        }

        if (newSuppressed)
        {
            Dem_EvtSt_HandleEvtNotAvailable(EventId);
        }
        else
        {
            Dem_EvtSt_HandleEvtAvailable(EventId);
            Dem_EvtSetInitMonitoring(EventId, DEM_INIT_MONITOR_REENABLED);
        }

#if (DEM_CFG_TRIGGERFIMREPORTS == DEM_CFG_TRIGGERFIMREPORTS_ON)
        isoByteNew = Dem_EvtGetIsoByte(EventId);
        FiM_DemTriggerOnEventStatus(EventId, isoByteOld, isoByteNew);
#endif
    }
}
#endif

//*****************************************************************************
Std_ReturnType Dem_IsAnyInitMonitorForEventRequested ( uint16 *localCounter, boolean *modified )
{
    Std_ReturnType retVal = E_NOT_OK;

    if( (localCounter!=NULL_PTR) && (modified!=NULL_PTR) )
    {
        retVal = E_OK;

        if( *localCounter==Dem_GlobalInitMonitoringCounter )
        {
            *modified = FALSE;
        }
        else
        {
            *localCounter = Dem_GlobalInitMonitoringCounter;
            *modified = TRUE;
        }
    }

    return retVal;
}


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
