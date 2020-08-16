

#ifndef DEM_EVENTS_H
#define DEM_EVENTS_H

#include "Dem.h"

#include "Dem_Array.h"
#include "Dem_BitArray.h"
#include "rba_DiagLib_Bits8.h"
#include "rba_DiagLib_Bits16.h"
#include "rba_DiagLib_Bits32.h"
#include "Dem_ISO14229Byte.h"

#include "Dem_Clear.h"
#include "Dem_Cfg_Events.h"
#include "Dem_Cfg_Deb.h"
#include "Dem_Cfg_EvBuff.h"
#include "Dem_Cfg_Nodes.h"
#include "Dem_EventCategory.h"
#include "Dem_StorageCondition.h"       // -> situationfilterCFG
#include "Dem_EnableCondition.h"         // -> enableconditionCFG
#include "Dem_Cfg_Main.h"
#include "Dem_Cfg_OperationCycle.h"
#include "Dem_Cfg_DistMem.h"
#include "Dem_Cfg_StorageCondition.h"
#include "Dem_Nvm.h"
#include "Dem_IndicatorAttributes.h"
#include "Dem_Indicator.h"

#if (DEM_CFG_EVT_ATTRIBUTE == DEM_CFG_EVT_ATTRIBUTE_ON)
#include "Dem_EventAttribute.h"
#endif


typedef Std_ReturnType (* Dem_InitMForEAllowedFncType) (Dem_InitMonitorReasonType InitMonitorReason);
typedef struct
{
/* Pointer to InitMonitorForEvent Callback */
  uint16 Eventid;
  Dem_InitMForEAllowedFncType InitMForEAllwdCBFnc;
}Dem_InitMonitorForE;

typedef struct
{
    Dem_EvtStateType  state;
    sint16 debounceLevel;
} Dem_EvtState;

typedef struct
{
    Dem_EventStatusType lastReportedEvent;
} Dem_EvtState8;

typedef void (* Dem_EvtStatusChangeFncType) ( Dem_EventIdType EventId, Dem_UdsStatusByteType EventStatusOld, Dem_UdsStatusByteType EventStatusNew );
typedef Std_ReturnType (* const Dem_EvtClearAllowedFncType) ( boolean* Allowed );

#define DEM_EVTPARAM_DEBPARAM_SHIFT   4u
#define DEM_EVTPARAM_DEBMETHOD_MASK   0x0Fu

/*----------------------------------------------------------------------------*/

typedef struct
{
  Dem_EvtParamType configFlags;
} Dem_EvtParamFlags;

#if (DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)
typedef struct
{
    Dem_EvtCategoryPrioType evtcatprio;
} Dem_EvtCategoryPriority;
#endif
typedef struct
{
   uint8 agingThreshold;   /* for EvMem -> EventAgingCycleCounterThreshold */
   uint8 agingThresholdForTFSLC;   /* for EvMem -> EventAgingCycleCounterThresholdForTFSLC */
   uint8 failureThreshold; /* for EvMem -> EventFailureCycleCounterThreshold */
   uint8 eventPrio;        /* for EvMem -> EventPriority */
   uint8 maxNumberOfFF;    /* for EvMem */
#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
   uint8 bufferTimeSFB;
#endif

#if (DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
   uint8 eventCBIdx;       /* Index for the associated call back for this event */
#endif

#if (DEM_CFG_EVT_CLEARALLOWEDCALLBACK != DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF)
   Dem_EvtClearAllowedFncType clrAllwdCBFnc;       /* Pointer to Configured ClearAllowed Callback Function for this event */
   uint8 ClearAllowedBehavior;  /* DemClearEventAllowedBehavior */
#endif

#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
  Dem_StoCoList storageConditionMask;
#endif

#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
  Dem_EnCoList enableConditionMask;
#endif

  uint16 debounceParameter;
} Dem_EvtParam;


/*----------------------------------------------------------------------------*/

#if(DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
#define DEM_EVTS_INIT_SEQUENTIALFAILURBUFFER(X)    ,(X)
#else
#define DEM_EVTS_INIT_SEQUENTIALFAILURBUFFER(X)
#endif

#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
#define DEM_EVTS_INIT_STORAGECONDITION(X)          ,(X)
#else
#define DEM_EVTS_INIT_STORAGECONDITION(X)
#endif

#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
#define DEM_EVTS_INIT_ENABLECONDITION(X)           ,(X)
#else
#define DEM_EVTS_INIT_ENABLECONDITION(X)
#endif

#if (DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
#define DEM_EVTS_INIT_CALLBACKEVENTSTATUSCHANGED(X)                ,(X)
#else
#define DEM_EVTS_INIT_CALLBACKEVENTSTATUSCHANGED(X)
#endif

#if (DEM_CFG_EVT_CLEARALLOWEDCALLBACK != DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF)
#define DEM_EVTS_INIT_CALLBACKCLEARALLOWED(X)                ,(X)
#else
#define DEM_EVTS_INIT_CALLBACKCLEARALLOWED(X)
#endif

#if (DEM_CFG_EVT_CLEARALLOWEDCALLBACK != DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF)
#define DEM_EVTS_INIT_CLEARALLOWEDBEHAVIOR(X)                ,(X)
#else
#define DEM_EVTS_INIT_CLEARALLOWEDBEHAVIOR(X)
#endif

#define DEM_EVTS_INIT_FLAGS(DEBOUNCEBEHAVIOR,                         \
        ISRECOVERABLE,                            \
        STOREFAILURETONEXTOC,                     \
        WARNINGINDICATOR,                         \
        CATEGORY,                                 \
        EVTDEST_PRIMARY,                          \
        EVTDEST_SECONDARY,                        \
        EVTDEST_MIRROR,                           \
        AGINGALLOWED,                             \
        ISANY_GLOBALFDCCALLBACK_CONFIGURED,       \
        ISANY_CALLBACKEVTDATACHANGED_CONFIGURED,  \
        SIGNIFICANCE,                             \
        OPERATIONCYCLEID,                         \
        AGINGCYCLEID,                             \
        FAILURECYCLEID,                           \
        SUPPRESSION      )       \
   {                                                                                        \
    (Dem_EvtParamType)0 + DEM_EVT_PARAMINI_ISRECOVERABLE(ISRECOVERABLE)                     \
       + DEM_EVT_PARAMINI_STOREFAILURETONEXTOC(STOREFAILURETONEXTOC)                        \
       + DEM_EVT_PARAMINI_WARNINGINDICATOR(WARNINGINDICATOR)                                \
       + DEM_EVT_PARAMINI_MONITORING_CATEGORY(CATEGORY)                                     \
       + DEM_EVT_PARAMINI_EVTDEST_PRIMARY(EVTDEST_PRIMARY)                                  \
       + DEM_EVT_PARAMINI_EVTDEST_SECONDARY(EVTDEST_SECONDARY)                              \
       + DEM_EVT_PARAMINI_EVTDEST_MIRROR(EVTDEST_MIRROR)                                    \
       + DEM_EVT_PARAMINI_AGING_ALLOWED(AGINGALLOWED)                                       \
       + DEM_EVT_PARAMINI_ISEVENTHAS_GLOBALFDCCALLBACK(ISANY_GLOBALFDCCALLBACK_CONFIGURED)         \
       + DEM_EVT_PARAMINI_ISEVENTHAS_DATACHANGEDCALLBACK(ISANY_CALLBACKEVTDATACHANGED_CONFIGURED)         \
       + DEM_EVT_PARAMINI_SIGNIFICANCE(SIGNIFICANCE)                                        \
       + DEM_EVT_PARAMINI_OPERATIONCYCLEID(OPERATIONCYCLEID)                                \
       + DEM_EVT_PARAMINI_AGINGCYCLEID(AGINGCYCLEID)                                        \
       + DEM_EVT_PARAMINI_FAILURECYCLEID(FAILURECYCLEID)                                    \
       + DEM_EVT_PARAMINI_SUPPRESSIONINIT(SUPPRESSION)                                      \
       + DEM_EVT_PARAMINI_DEBOUNCEBEHAVIOR(DEBOUNCEBEHAVIOR)                                \
    }

#define DEM_EVTS_INIT(DEBOUNCEMETHODINDEX,        \
        DEBOUNCEPARAMSETINDEX,                    \
        BUFFERTIMESFB,                            \
        AGINGTHRESHOLD,                           \
        AGINGTHRESHOLDFORTFSLC,                   \
        FAILURETHRESHOLD,                         \
        EVENTPRIO,                                \
        MAXNUMBER_OF_FF,                          \
        STORAGECONDITION,                         \
        ENABLECONDITION,                          \
        CALLBACKEVENTSTATUSCHANGED,               \
        CALLBACKCLEARALLOWED,                     \
        CLEARALLOWEDBEHAVIOR )                    \
   {                                                                                        \
    (AGINGTHRESHOLD)                                                                        \
    ,(AGINGTHRESHOLDFORTFSLC)                                                               \
    ,(FAILURETHRESHOLD)                                                                     \
    ,(EVENTPRIO)                                                                            \
    ,(MAXNUMBER_OF_FF)                                                                      \
    DEM_EVTS_INIT_SEQUENTIALFAILURBUFFER(BUFFERTIMESFB)                                     \
    DEM_EVTS_INIT_CALLBACKEVENTSTATUSCHANGED(CALLBACKEVENTSTATUSCHANGED)                    \
    DEM_EVTS_INIT_CALLBACKCLEARALLOWED(CALLBACKCLEARALLOWED)                                \
    DEM_EVTS_INIT_CLEARALLOWEDBEHAVIOR(CLEARALLOWEDBEHAVIOR)                                \
    DEM_EVTS_INIT_STORAGECONDITION(STORAGECONDITION)                                        \
    DEM_EVTS_INIT_ENABLECONDITION(ENABLECONDITION)                                          \
    ,((DEBOUNCEPARAMSETINDEX) << (DEM_EVTPARAM_DEBPARAM_SHIFT))                             \
      + ((DEBOUNCEMETHODINDEX) & (DEM_EVTPARAM_DEBMETHOD_MASK))                             \
    }




#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

DEM_ARRAY_DECLARE_CONST(Dem_EvtParamFlags, Dem_AllEventsParamFlags, DEM_EVENTID_ARRAYLENGTH);
DEM_ARRAY_DECLARE_CONST(Dem_EvtParam, Dem_AllEventsParam, DEM_EVENTID_ARRAYLENGTH);

#if (DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)
DEM_ARRAY_DECLARE_CONST(Dem_EvtCategoryPriority,Dem_EvtCategoryPrio,DEM_EVENTCATPRIO_ARRAYLENGTH);
#endif

#if(DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED == TRUE)
DEM_ARRAY_DECLARE_CONST(Dem_InitMonitorForE, Dem_Cfg_Callback_InitMForE_List, DEM_CFG_CALLBACK_INITMFORE_LISTLENGTH);
#endif

#if (DEM_CFG_EVT_ATTRIBUTE == DEM_CFG_EVT_ATTRIBUTE_ON)
DEM_ARRAY_DECLARE_CONST(Dem_EventAttributeType, Dem_AllEventsUserAttributes, DEM_EVENTID_ARRAYLENGTH);
#endif

#if (DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0)
DEM_ARRAY_DECLARE_CONST(Dem_EvtStatusChangeFncType, Dem_AllEventsStatusChangedFnc, DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS);
#endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
DEM_BITARRAY_DECLARE  (Dem_AllEventsHistoryStatus, DEM_EVENTID_ARRAYLENGTH);
#endif

#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

extern uint32 Dem_EvtIsAnyInitMonitoringRequestedMask;
DEM_ARRAY_DECLARE(Dem_EvtState, Dem_AllEventsState, DEM_EVENTID_ARRAYLENGTH);
DEM_ARRAY_DECLARE(Dem_EvtState8, Dem_AllEventsState8, DEM_EVENTID_ARRAYLENGTH);
DEM_BITARRAY_DECLARE(Dem_AllEventsResetDebouncerRequested, DEM_EVENTID_ARRAYLENGTH);
DEM_BITARRAY_DECLARE(Dem_EventWasPassedReported,DEM_EVENTID_ARRAYLENGTH);

#if (DEM_CFG_EVTDISABLESTATUSUPDATE == DEM_CFG_EVTDISABLESTATUSUPDATE_ON)
/* global variable to control the update of events and debounce counters. backend to Dem_Disable/EnableEventStatusUpdate() */
extern boolean Dem_EvtGlobalStatusUpdateState;
#endif

extern uint16 Dem_GlobalInitMonitoringCounter;

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"



/*** FUNCTIONS ****************************************************************/
DEM_INLINE Dem_boolean_least Dem_EvtGetHistoryStatus(Dem_EventIdType EventId)
{
#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
    return Dem_BitArrayIsBitSet(Dem_AllEventsHistoryStatus, EventId);
#else
    DEM_UNUSED_PARAM(EventId);
    return FALSE;
#endif
}


DEM_INLINE void Dem_EvtSetHistoryStatus(Dem_EventIdType EventId, boolean newStatus)
{
#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
    Dem_BitArrayOverwriteBit(Dem_AllEventsHistoryStatus, EventId, newStatus);
    Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_HISTORY_STATUS_BYTE);
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(newStatus);
#endif
}


DEM_INLINE uint8 Dem_EvtGetBufferTime (Dem_EventIdType EventId)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
   return Dem_AllEventsParam[EventId].bufferTimeSFB;
#else
   DEM_UNUSED_PARAM(EventId);
   return 0;
#endif
}


/*-- DEBOUNCE LEVEL ----------------------------------------------------------*/

DEM_INLINE sint16 Dem_EvtGetDebounceLevel (Dem_EventIdType EventId)
{
   return Dem_AllEventsState[EventId].debounceLevel;
}


DEM_INLINE void Dem_EvtSetDebounceLevel (Dem_EventIdType EventId, sint16 debounceLevel)
{
   Dem_AllEventsState[EventId].debounceLevel = debounceLevel;
}


DEM_INLINE void Dem_EvtIncDebounceLevel (Dem_EventIdType EventId)
{
   Dem_AllEventsState[EventId].debounceLevel++;
}

DEM_INLINE void Dem_EvtDecDebounceLevel (Dem_EventIdType EventId)
{
   Dem_AllEventsState[EventId].debounceLevel--;
}



/*-- LAST REPORTED EVENT -----------------------------------------------------*/

DEM_INLINE Dem_EventStatusType Dem_EvtGetLastReportedEvent (Dem_EventIdType EventId)
{
   return Dem_AllEventsState8[EventId].lastReportedEvent;
}


DEM_INLINE void Dem_EvtSetLastReportedEvent (Dem_EventIdType EventId, Dem_EventStatusType EventStatus)
{
   Dem_AllEventsState8[EventId].lastReportedEvent = EventStatus;
}




/*-- RECOVERABLE -------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsRecoverable_Flag (Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_ISRECOVERABLE);
}

Dem_boolean_least Dem_EvtIsRecoverable (Dem_EventIdType EventId);

DEM_INLINE Dem_boolean_least Dem_EvtIsNotRecoverableTOC(Dem_EventIdType EventId)
{
    return (! Dem_EvtIsRecoverable(EventId));
}

/*-- CAUSAL ------------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsCausal (Dem_EventIdType EventId)
{
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_CAUSALFAULT);
}


DEM_INLINE void Dem_EvtSetCausal_Flag (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
    DEM_ASSERT_ISLOCKED();
   DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_CAUSALFAULT, setBit);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsRecheckedAndWaitingForMonResult (Dem_EventIdType EventId)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_RECHECKEDANDWAITING_FOR_MONRES);
#else
    DEM_UNUSED_PARAM(EventId);
    return FALSE;
#endif
}


DEM_INLINE void Dem_EvtSetIsRecheckedAndWaitingForMonResult (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
#if (DEM_CFG_DEPENDENCY == DEM_CFG_DEPENDENCY_ON)
    DEM_ASSERT_ISLOCKED();
    DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_RECHECKEDANDWAITING_FOR_MONRES, setBit);
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(setBit);
#endif
}


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

boolean Dem_EvtClearEventAllowed ( Dem_EventIdType eventId );
void Dem_EvtSetCausal (Dem_EventIdType EventId, Dem_boolean_least causal);
Std_ReturnType Dem_EvtResetIsoByteCallback(void);
void Dem_EvtPreInitEvents (void);
void Dem_EvtInitEvents(void);

#if((DEM_CFG_SUPPRESSION == DEM_EVENT_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))
void Dem_EvtSetSuppression (Dem_EventIdType EventId, Dem_boolean_least newSuppressed);
#endif

#if (DEM_CFG_CHECKAPICONSISTENCY == TRUE)
/* Duplicate of Dem_GetEventTested to make it also available in the GeneralDiagnosticInfo RTE interface */
Std_ReturnType Dem_GetEventTested_GeneralEvtInfo(Dem_EventIdType EventId, boolean* EventTested);
#endif /* DEM_CFG_CHECKAPICONSISTENCY */

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#if(DEM_CFG_ALLOW_HISTORY == DEM_CFG_ALLOW_HISTORY_ON)
//Function to Validate the Nv Blocks after startup
DEM_INLINE void Dem_EvtHistoryStatusInitCheckNvM(void)
{
    Dem_NvmResultType NvmResult;

    if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
    {
        /* Set the EventStatus to its default value */
        DEM_MEMSET( &Dem_AllEventsHistoryStatus, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsHistoryStatus));
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_HISTORY_STATUS_BYTE);
    }
    else
    {
        /* Get the Result of the NvM-Read (NvM_ReadAll) */
        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_HISTORY_STATUS_BYTE);

        /* Data read successfully */
        if (NvmResult != DEM_NVM_SUCCESS)
        {
            /* Zero the content of event history status */
            DEM_MEMSET( &Dem_AllEventsHistoryStatus, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsHistoryStatus));
            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_HISTORY_STATUS_BYTE);
        }
    }

}
#endif

/*-- SUSPICION ---------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsSuspicious (Dem_EventIdType EventId)
{
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_SUSPICIONLEVEL);
}


DEM_INLINE void Dem_EvtSetSuspicionLevel (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_SUSPICIONLEVEL, setBit);
}



/*-- ROBUSTNESS --------------------------------------------------------------*/
#if(DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)
DEM_INLINE Dem_boolean_least Dem_EvtGetFDCThresholdReachedTOC (Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHEDTOC);
}

DEM_INLINE void Dem_EvtSetFDCThresholdReachedTOC (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHEDTOC, setBit);
}
#endif


#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
DEM_INLINE Dem_boolean_least Dem_EvtGetFDCThresholdReached (Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHED);
}
#endif

DEM_INLINE void Dem_EvtSetFDCThresholdReached (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_FDCTHRESHOLDREACHED, setBit);
#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(setBit);
#endif
}


/*-- DRIVECYCLE, WARNINGINDICATOR, SID ---------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtStoreTestFailedToNextOC (Dem_EventIdType EventId)
{
#if (DEM_CFG_EVMEM_STORAGE_TESTFAILED_SUPPORTED)
    DEM_UNUSED_PARAM(EventId);
    return TRUE;
#else
    return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_STOREFAILURETONEXTOC);
#endif
}

#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
DEM_INLINE Dem_boolean_least Dem_EvtRequestsWarningIndicator (Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_WARNINGINDICATOR);
}
#elif(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_OFF)
#define Dem_EvtRequestsWarningIndicator(X)  (FALSE)
#else
/*Handling is project specific*/
#endif


/*-- CATEGORY ----------------------------------------------------------------*/

#if (DEM_CFG_EVTCATEGORY == DEM_CFG_EVTCATEGORY_ON)

DEM_INLINE Dem_EventCategoryType  Dem_EvtGetCategory (Dem_EventIdType EventId)
{
   return (Dem_EventCategoryType) DEM_EVTPARAM_GETBITS(Dem_AllEventsParamFlags[EventId].configFlags,
                                                   DEM_EVT_BP_PARAM_MONITORING_CATEGORY,
                                                   DEM_EVT_BP_PARAM_MONITORING_CATEGORY_SIZE);
}

DEM_INLINE Dem_EvtCategoryPriorityType Dem_GetEventCategoryPriority (Dem_EventCategoryType Category)
{
    return (Dem_EvtCategoryPriorityType) Dem_EvtCategoryPrio[Category].evtcatprio;
}
#endif



/*-- EVENT DESTINATION -------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsDestPrimaryMemory (Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_EVTDEST_PRIMARY);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsDestSecondaryMemory (Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_EVTDEST_SECONDARY);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsDestMirrorMemory (Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_EVTDEST_MIRROR);
}



/*-- EVENT MEMORY CONFIGURATION ----------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsAgingAllowed (Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_AGING_ALLOWED);
}

DEM_INLINE uint8 Dem_EvtGetAgingThreshold (Dem_EventIdType EventId)
{
   return Dem_AllEventsParam[EventId].agingThreshold;
}

DEM_INLINE uint8 Dem_EvtGetAgingThresholdForTFSLC (Dem_EventIdType EventId)
{
   return Dem_AllEventsParam[EventId].agingThresholdForTFSLC;
}

DEM_INLINE uint8 Dem_EvtGetFailureConfirmationThreshold (Dem_EventIdType EventId)
{
   return Dem_AllEventsParam[EventId].failureThreshold;
}

DEM_INLINE uint8 Dem_EvtGetEventPriority (Dem_EventIdType EventId)
{
   return Dem_AllEventsParam[EventId].eventPrio;
}

DEM_INLINE uint8 Dem_EvtGetMaxNumberOfFreezeFrames(Dem_EventIdType EventId)
{
  return Dem_AllEventsParam[EventId].maxNumberOfFF;
}

DEM_INLINE uint8 Dem_EvtGetClearAllowedBehavior(Dem_EventIdType EventId)
{
#if (DEM_CFG_EVT_CLEARALLOWEDCALLBACK != DEM_CFG_EVT_CLEARALLOWEDCALLBACK_OFF)
    return Dem_AllEventsParam[EventId].ClearAllowedBehavior;
#else
    DEM_UNUSED_PARAM(EventId);
    return NO_STATUS_BYTE_CHANGE ;
#endif
}

DEM_INLINE Dem_boolean_least Dem_EvtIsTriggersGlobalFDCCallback (Dem_EventIdType EventId)
{
#ifdef DEM_CFG_GENERAL_GETFDC
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_EVENTHAS_GLOBALFDCCALLBACK);
#else
   DEM_UNUSED_PARAM(EventId);
  return FALSE;
#endif
}

DEM_INLINE Dem_boolean_least Dem_EvtTriggersDataChangedCallback (Dem_EventIdType EventId)
{
#if(DEM_CFG_EVT_DATACHANGEDCALLBACK != DEM_CFG_EVT_DATACHANGEDCALLBACK_OFF)
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_EVENTHAS_DATACHANGEDCALLBACK);
#else
   DEM_UNUSED_PARAM(EventId);
  return FALSE;
#endif
}

/*--Event Significance-------------------------------*/
DEM_INLINE Dem_boolean_least Dem_EvtIsSignificanceOccurrence(Dem_EventIdType EventId)
{
   return !DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_SIGNIFICANCE);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsSignificanceFault(Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_SIGNIFICANCE);
}


/*--Debounce Behavior-------------------------------*/

DEM_INLINE Dem_boolean_least Dem_IsEvtDebBehaviorReset(Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_DEBOUNCEBEHAVIOR);
}

DEM_INLINE Dem_boolean_least Dem_IsEvtDebBehaviorFreeze(Dem_EventIdType EventId)
{
   return !DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_DEBOUNCEBEHAVIOR);
}

/*-- STORAGECONDITION --------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsStorageFiltered (Dem_EventIdType EventId)
{
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_ISSTORAGEFILTERED);
#else
   DEM_UNUSED_PARAM(EventId);
   return FALSE;
#endif
}


DEM_INLINE void Dem_EvtSetStorageFiltered (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_ISSTORAGEFILTERED, setBit);
#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(setBit);
#endif
}


DEM_INLINE Dem_StoCoList Dem_EvtGetStorageConditions (Dem_EventIdType EventId)
{
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
   return Dem_AllEventsParam[EventId].storageConditionMask;
#else
   DEM_UNUSED_PARAM(EventId);
   return 0;
#endif
}



/*-- ENABLECONDITION ---------------------------------------------------------*/

DEM_INLINE Dem_EnCoList Dem_EvtGetEnableConditions (Dem_EventIdType EventId)
{
#if (DEM_CFG_ENABLECONDITION == DEM_CFG_ENABLECONDITION_ON)
   return Dem_AllEventsParam[EventId].enableConditionMask;
#else
   DEM_UNUSED_PARAM(EventId);
   return 0;
#endif
}



/*-- GLOBAL ENABLECONDITION --------------------------------------------------*/

#if(DEM_CFG_EVTDISABLESTATUSUPDATE == DEM_CFG_EVTDISABLESTATUSUPDATE_ON)

/**
 * @ingroup DIA_MONITORING_PUBLIC
 *
 * This function allows to disable any kind of event updates for testing or end-of-line purposes.
 * If the event update is disabled, no monitoring results (with or without CDB) will reach the MFT.
 */
DEM_INLINE void Dem_EvtDisableGlobalStatusUpdate(void)
{
   Dem_EvtGlobalStatusUpdateState = TRUE;
}

/**
 * @ingroup DIA_MONITORING_PUBLIC
 *
 * This function will enable previously disabled event updates. Disabling the event updates can be done
 * for testing or end-of-line purposes. If the event update is disabled, no monitoring results (with or without CDB)
 * will reach the MFT.
 */
DEM_INLINE void Dem_EvtEnableGlobalStatusUpdate(void)
{
   Dem_EvtGlobalStatusUpdateState = FALSE;
}

#endif

DEM_INLINE Dem_boolean_least Dem_EvtIsGlobalStatusUpdateEnabled(void)
{
#if(DEM_CFG_EVTDISABLESTATUSUPDATE == DEM_CFG_EVTDISABLESTATUSUPDATE_ON)
   return !Dem_EvtGlobalStatusUpdateState;
#else
   return (TRUE);
#endif
}

DEM_INLINE Dem_boolean_least Dem_EvtAllEnableConditionsFulfilled (Dem_EventIdType EventId)
{
   return (   Dem_EnCoAreAllFulfilled(Dem_EvtGetEnableConditions(EventId))
           && Dem_EvtIsGlobalStatusUpdateEnabled()
          );
}



/*-- DEBOUNCER ACCESS --------------------------------------------------------*/

DEM_INLINE uint8 Dem_EvtGetDebounceMethodIndex(Dem_EventIdType EventId)
{
   return ((uint8)(Dem_AllEventsParam[EventId].debounceParameter & DEM_EVTPARAM_DEBMETHOD_MASK));
}


DEM_INLINE uint16 Dem_EvtGetDebounceParamSetIndex(Dem_EventIdType EventId)
{
   return (Dem_AllEventsParam[EventId].debounceParameter >> DEM_EVTPARAM_DEBPARAM_SHIFT);
}



/*-- RESET CDB ---------------------------------------------------------------*/

DEM_INLINE void Dem_EvtRequestResetFailureFilter(Dem_EventIdType EventId, Dem_boolean_least setBit)
{
    DEM_ASSERT_ISLOCKED();
    Dem_BitArrayOverwriteBit(Dem_AllEventsResetDebouncerRequested, EventId, setBit);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsResetFailureFilterRequested(Dem_EventIdType EventId)
{
    return Dem_BitArrayIsBitSet(Dem_AllEventsResetDebouncerRequested, EventId);
}

/*-- Reset Debounce counter requested for Control DTC Setting-----------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsResetFailureFilterRequestedAfterDtcSetting (Dem_EventIdType EventId)
{


#if (!DEM_CFG_DTCSETTINGBLOCKSREPORTING)
    return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_DEBCOUNTER_RESET_REQUESTED);
#else
    DEM_UNUSED_PARAM(EventId);
    return FALSE;
#endif
}


DEM_INLINE void Dem_EvtRequestResetFailureFilterAfterDtcSetting (Dem_EventIdType EventId, Dem_boolean_least setBit)
{

    DEM_ASSERT_ISLOCKED();

#if (!DEM_CFG_DTCSETTINGBLOCKSREPORTING)
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_DEBCOUNTER_RESET_REQUESTED, setBit);
#else
   DEM_UNUSED_PARAM(EventId);
   DEM_UNUSED_PARAM(setBit);
#endif
}

/*-- Reset Debounce counter requested for Storage Condition-----------------*/

DEM_INLINE void Dem_EvtRequestResetFailureFilterAfterStorageCondition (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
	DEM_ASSERT_ISLOCKED();
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
    DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_STORAGEFILTERED_EVENT_REPORTED, setBit);
#else
    DEM_UNUSED_PARAM(EventId);
    DEM_UNUSED_PARAM(setBit);
#endif
}

DEM_INLINE Dem_boolean_least Dem_EvtIsResetFailureFilterRequestedAfterStorageCondition (Dem_EventIdType EventId)
{
#if (DEM_CFG_STORAGECONDITION == DEM_CFG_STORAGECONDITION_ON)
    return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_IS_STORAGEFILTERED_EVENT_REPORTED);
#else
    DEM_UNUSED_PARAM(EventId);
	return FALSE;
#endif
}

DEM_INLINE void Dem_EvtIncreaseGlobalInitMonitoringCounter(void)
{
    Dem_GlobalInitMonitoringCounter++;
}


DEM_INLINE void Dem_EvtSetAnyInitMonitoring (Dem_InitMonitorReasonType reason) { rba_DiagLib_Bit32SetBit(&Dem_EvtIsAnyInitMonitoringRequestedMask, reason); }
DEM_INLINE void Dem_EvtResetAnyInitMonitoring (void) { Dem_EvtIsAnyInitMonitoringRequestedMask = 0u; }
DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequested (void) { return (Dem_EvtIsAnyInitMonitoringRequestedMask != 0u); }
DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequestedClear (void) { return rba_DiagLib_Bit32IsBitSet(Dem_EvtIsAnyInitMonitoringRequestedMask, DEM_INIT_MONITOR_CLEAR); }
//DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequestedRestart (void) { return rba_DiagLib_Bit32IsBitSet(Dem_EvtIsAnyInitMonitoringRequestedMask, DEM_INIT_MONITOR_RESTART); }
//DEM_INLINE boolean Dem_EvtIsAnyInitMonitoringRequestedRecheck (void) { return rba_DiagLib__Bit32IsBitSet(Dem_EvtIsAnyInitMonitoringRequestedMask, DEM_INIT_MONITOR_STORAGE_REENABLED); }


DEM_INLINE void Dem_EvtSetInitMonitoring (Dem_EventIdType EventId, Dem_InitMonitorReasonType newReason)
{
    Dem_InitMonitorReasonType oldReason = (Dem_InitMonitorReasonType)DEM_EVTSTATE_GETBITS (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE);

    DEM_ASSERT_ISLOCKED();
    if ((oldReason == 0u) || (oldReason > newReason))
    {
        DEM_EVTSTATE_OVERWRITEBITS (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE, newReason);
    }
    Dem_EvtIncreaseGlobalInitMonitoringCounter();
    Dem_EvtSetAnyInitMonitoring (newReason);
}


/* if return value is != 0 an InitMon is requested; return value does not match the AR values DEM_INIT_MONITOR_* */
DEM_INLINE uint8 Dem_EvtIsInitMonitoringRequested (Dem_EventIdType EventId)
{
  return ((uint8)(DEM_EVTSTATE_GETBITS (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE )));
}

DEM_INLINE void Dem_EvtClearInitMonitoringRequests (Dem_EventIdType EventId)
{
  DEM_EVTSTATE_CLEARBITS (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_INITMONITORING, DEM_EVT_BP_STATE_INITMONITORING_SIZE);
}


#if(DEM_CFG_CALLBACK_INIT_MON_FOR_EVENT_SUPPORTED == TRUE)

DEM_INLINE void Dem_InitMonitorForEFnc (void)
{
    Dem_InitMonitorReasonType InitMonitorReason;
    uint16_least i;
    if(Dem_EvtIsAnyInitMonitoringRequested())
    {
        DEM_ENTERLOCK_MON();

        Dem_EvtResetAnyInitMonitoring();

        DEM_EXITLOCK_MON();
        for (i=0u; i<DEM_CFG_CALLBACK_INITMFORE_LISTLENGTH; i++)
        {
            if(Dem_IsInitMonitorForEventRequested(Dem_Cfg_Callback_InitMForE_List[i].Eventid, &InitMonitorReason))
            {
                Dem_Cfg_Callback_InitMForE_List[i].InitMForEAllwdCBFnc(InitMonitorReason);
            }
        }
    }
}

#endif


#if ( DEM_CFG_EVT_STATUS_CHANGE_NUM_CALLBACKS > 0 )
DEM_INLINE void Dem_CallEventStatusChangedCallBack (Dem_EventIdType EventId, Dem_UdsStatusByteType EventStatusOld, Dem_UdsStatusByteType EventStatusNew )
{
  if (Dem_AllEventsParam[EventId].eventCBIdx > 0)
  {
    (*Dem_AllEventsStatusChangedFnc[Dem_AllEventsParam[EventId].eventCBIdx])(EventId, EventStatusOld, EventStatusNew);
  }
  else
  {
    /* No Call-back has been configured for this Event */
  }
}
#endif

/*WIRStatus set by External Source*/

#if(DEM_CFG_EVT_INDICATOR != DEM_CFG_EVT_INDICATOR_PROJECTSPECIFIC)
DEM_INLINE void Dem_EvtSetWIRExtern(Dem_EventIdType EventId, Dem_boolean_least newState)
{
  DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_WIRSTATUS_EXTERNAL,newState);
}


DEM_INLINE Dem_boolean_least Dem_EvtIsWIRExternal(Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_WIRSTATUS_EXTERNAL);
}
#else
#define Dem_EvtSetWIRExtern(X,Y)    do{}while(0);
#define Dem_EvtIsWIRExternal(X)     (FALSE)
#endif




/*-- OPERATION CYCLE ---------------------------------------------------------*/
DEM_INLINE uint8 Dem_EvtGetOperationCycleId (Dem_EventIdType EventId)
{
  return ((uint8)(DEM_EVTPARAM_GETBITS(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_OPERATIONCYCLEID, DEM_OPERATIONCYCLE_BITSIZE)));
}

DEM_INLINE Dem_boolean_least Dem_isEventAffectedByOperationCycleList (Dem_EventIdType EventId, Dem_OperationCycleList operationCycleList)
{
  return ((operationCycleList & (Dem_OperationCycleList)(1u<<Dem_EvtGetOperationCycleId(EventId))) != 0u);
}

DEM_INLINE uint8 Dem_EvtGetAgingCycleId (Dem_EventIdType EventId)
{
   return ((uint8)(DEM_EVTPARAM_GETBITS(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_AGINGCYCLEID, DEM_AGINGCYCLE_BITSIZE)));
}

DEM_INLINE Dem_boolean_least Dem_isEventAffectedByAgingCycleList (Dem_EventIdType EventId, Dem_OperationCycleList agingCycleList)
{
  return ((agingCycleList & (Dem_OperationCycleList)(1u<<Dem_EvtGetAgingCycleId(EventId))) != 0u);
}

DEM_INLINE uint8 Dem_EvtGetFailureCycleId (Dem_EventIdType EventId)
{
   return ((uint8)(DEM_EVTPARAM_GETBITS(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_FAILURECYCLEID, DEM_FAILURECYCLE_BITSIZE)));
}

DEM_INLINE Dem_boolean_least Dem_isEventAffectedByFailureCycleList (Dem_EventIdType EventId, Dem_OperationCycleList failureCycleList)
{
   return ((failureCycleList & (Dem_OperationCycleList)(1u<<Dem_EvtGetFailureCycleId(EventId))) != 0u);
}


/*-- DISTURBANCE MEMORY ---------------------------------------------------------------*/
#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)

#define DEM_DIST_MEM_IND_SET_BIT_MASK   (Dem_EvtStateType)(((Dem_EvtStateType)DEM_EVT_BP_STATE_DIST_MEM_IDX_MASK) << DEM_EVT_BP_STATE_DIST_MEM_IDX)
#define DEM_DIST_MEM_IND_CLEAR_BIT_MASK (Dem_EvtStateType)(~((Dem_EvtStateType)DEM_DIST_MEM_IND_SET_BIT_MASK))

DEM_INLINE Dem_boolean_least Dem_EvtIsEventStoredInDistMem (Dem_EventIdType EventId)
{
  return ((Dem_AllEventsState[EventId].state & DEM_DIST_MEM_IND_SET_BIT_MASK) != 0u);
}

DEM_INLINE void Dem_EvtSetEventsDistMemIndex (Dem_EventIdType EventId , uint8 idx)
{
	Dem_AllEventsState[EventId].state = ((Dem_AllEventsState[EventId].state & DEM_DIST_MEM_IND_CLEAR_BIT_MASK) |   \
			((Dem_EvtStateType)(((Dem_EvtStateType)(idx & DEM_EVT_BP_STATE_DIST_MEM_IDX_MASK)) << DEM_EVT_BP_STATE_DIST_MEM_IDX)));
}

DEM_INLINE uint8 Dem_EvtGetEventsDistMemIndex (Dem_EventIdType EventId)
{
	return ((uint8)((Dem_AllEventsState[EventId].state & DEM_DIST_MEM_IND_SET_BIT_MASK) >> DEM_EVT_BP_STATE_DIST_MEM_IDX));
}

#endif

/*------EventSuppression-------------------------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtGetInitialSuppressionStatus (Dem_EventIdType EventId)
{
   return DEM_EVTPARAM_ISBITSET(Dem_AllEventsParamFlags[EventId].configFlags, DEM_EVT_BP_PARAM_SUPPRESSIONINIT);
}

DEM_INLINE Dem_boolean_least Dem_EvtIsSuppressed (Dem_EventIdType EventId)
{
  return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_NOTAVAILABLE);
}

/*------NextReportRelevantForMemories----------------------------------------------------------------------*/

DEM_INLINE Dem_boolean_least Dem_EvtIsNextReportRelevantForMemories (Dem_EventIdType EventId)
{
   return DEM_EVTSTATE_ISBITSET (Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_NXT_REPORT_IS_RELEVANT);
}


DEM_INLINE void Dem_EvtSetNextReportRelevantForMemories (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
   DEM_EVTSTATE_OVERWRITEBIT (&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_NXT_REPORT_IS_RELEVANT, setBit);
}


/*------ Failure Cycle Event Status Bits -----------------------------------------------------------------------------*/
#if DEM_CFG_OBD == DEM_CFG_OBD_ON
/*
 * Whether the event was reported as failed in this failure cycle, not respecting reports before startup of the ECU
 *
 * This status information is needed for OBD permanent memory handling and is stored only in RAM. If ever move the
 * TestFailedTFC state handling from EvMem to an "extended event status byte", then we can use that instead and also
 * simplify some code in OBD.
 */
DEM_INLINE Dem_boolean_least Dem_EvtGetTestFailedTFCSincePreinit(Dem_EventIdType EventId)
{
    return DEM_EVTSTATE_ISBITSET(Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TFTFC_SINCE_PREINIT);
}

/*
 * Whether the event was reported as failed in this failure cycle, not respecting reports before startup of the ECU
 *
 * This status information is needed for OBD permanent memory handling and is stored only in RAM. If ever move the
 * TestFailedTFC state handling from EvMem to an "extended event status byte", then we can use that instead and also
 * simplify some code in OBD.
 */
DEM_INLINE void Dem_EvtSetTestFailedTFCSincePreinit(Dem_EventIdType EventId, Dem_boolean_least newState)
{
    DEM_ASSERT_ISLOCKED();
    DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TFTFC_SINCE_PREINIT, newState);
}

/*
 * Whether the event was tested in this failure cycle, not respecting reports before startup of the ECU
 *
 * This status information is needed for OBD permanent memory handling and is stored only in RAM. If ever move the
 * TestCompleteTFC state handling from EvMem to an "extended event status byte", then we can use that instead and also
 * simplify some code in OBD.
 */
DEM_INLINE Dem_boolean_least Dem_EvtGetTestCompleteTFCSincePreinit(Dem_EventIdType EventId)
{
    return DEM_EVTSTATE_ISBITSET(Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TCTFC_SINCE_PREINIT);
}

/*
 * Whether the event was tested in this failure cycle, not respecting reports before startup of the ECU
 *
 * This status information is needed for OBD permanent memory handling and is stored only in RAM. If ever move the
 * TestCompleteTFC state handling from EvMem to an "extended event status byte", then we can use that instead and also
 * simplify some code in OBD.
 */
DEM_INLINE void Dem_EvtSetTestCompleteTFCSincePreinit(Dem_EventIdType EventId, Dem_boolean_least newState)
{
    DEM_ASSERT_ISLOCKED();
    DEM_EVTSTATE_OVERWRITEBIT(&Dem_AllEventsState[EventId].state, DEM_EVT_BP_STATE_TCTFC_SINCE_PREINIT, newState);
}
#endif

/*-- COMBINED FUNCTIONS 4 DTC ------------------------------------------------*/


/* checks if the failure is set and may not be reset, used for DTC status calc *
DEM_INLINE Dem_boolean_least Dem_EvtIsActiveFailure (Dem_EventIdType EventId)
{
   return (Dem_EvtSt_GetTestFailed (EventId)
           && (   !Dem_EvtIsGoodCheckRequested(EventId)
               || !Dem_EvtIsGoodCheckTriggerSupported(EventId))
          );
}
*/

/*-- REPORTING STATE ---------------------------------------------------------*/

DEM_INLINE void Dem_EvtSetPassedWasReported (Dem_EventIdType EventId, Dem_boolean_least setBit)
{
    DEM_ASSERT_ISLOCKED();
    Dem_BitArrayOverwriteBit (Dem_EventWasPassedReported, EventId, setBit);
}

DEM_INLINE Dem_boolean_least Dem_EvtWasPassedReported (DEM_BITARRAY_CONSTFUNCPARAM(buffer), Dem_EventIdType EventId)
{
    return Dem_BitArrayIsBitSet (buffer, EventId);
}

#endif

