

#include "Dem_DebArTime.h"
#include "Dem_Deb.h"
#include "Dem_Events.h"
#include "Dem_EventStatus.h"
#include "Dem_EventFHandling.h"
#include "Dem_DisturbanceMemory.h"
#include "Dem_DTCs.h"
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_DebArTime_GetLimits(const void* paramSet,
        uint16 paramIndex,
        sint16_least* MinThreshold,
        sint16_least* MaxThreshold)
{
	/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
	*MinThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;
	/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
	*MaxThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;
}

#if (DEM_CFG_DEBARTIMEBASE == DEM_CFG_DEBARTIMEBASE_ON)

uint8_least Dem_DebArTime_Filter(Dem_EventIdType EventId,
        Dem_EventStatusType* status,
        const void* paramSet,
        uint16 paramIndex
        DEM_DEB_LOCAL_CALC_PARAMS)
{
	uint8_least debAction = DEM_DEBACTION_NOOP;
	sint16_least TimePassedThreshold, TimeFailedThreshold;
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
    /* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
    sint16_least SuspiciousThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].SuspiciousThreshold;
#endif

#if (DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
	if ((*status == DEM_EVENT_STATUS_PASSED) || (*status == DEM_EVENT_STATUS_PREPASSED))
	{
		/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
		TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;

		if ( (Dem_EvtGetDebounceLevel(EventId) < TimeFailedThreshold) && (Dem_EvtGetLastReportedEvent(EventId) == DEM_EVENT_STATUS_PREFAILED) )
		{
		    Dem_DistMemReportPassed(EventId);
		}
	}
#endif


   /* MR12 RULE 8.13 VIOLATION: A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object */
   *status = *status;

#if 0
=> REMOVED setting debouncelevel to ensure that the cyclic task checks the debouncelevel once again and probably sets the eventstatus once again
		(Background: concurrent tasks for reporting eventstatus and Dem_Mainfunction)
#endif



   if ((*status == DEM_EVENT_STATUS_PASSED) || (*status == DEM_EVENT_STATUS_FAILED))
   {
	   DEM_ENTERLOCK_MON();
	   /* Could not be removed from event-based function as a FAILED report could be not correctly considered, if another report
	    * is following before the mainfunction runs.
	    */

	   switch (*status)
	   {

	   case DEM_EVENT_STATUS_PASSED:
	   {
            /* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
            TimePassedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;
            Dem_EvtSetDebounceLevel (EventId, (sint16) TimePassedThreshold);
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if (SuspiciousThreshold != DEM_MAXSINT16)
                {
                    debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
                }
#endif
            Dem_EvtRequestResetFailureFilterAfterDtcSetting(EventId, FALSE);
            Dem_EvtRequestResetFailureFilter(EventId, FALSE);
#if (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
            debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
            break;
	   }

	   case DEM_EVENT_STATUS_FAILED:
	   {
            /* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
            TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;
            Dem_EvtSetDebounceLevel (EventId, (sint16) TimeFailedThreshold);
            Dem_EvtRequestResetFailureFilterAfterDtcSetting(EventId, FALSE);
            Dem_EvtRequestResetFailureFilter(EventId, FALSE);
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
			debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
		   break;
	   }
	   default:
	   {
	       /* Comment to avoid MISRA warning for Empty Default clause */
		   break;
	   }
	   }
	   DEM_EXITLOCK_MON();
	}


	return debAction;
}


void Dem_DebArTime_Cyclic(Dem_EventIdType EventId, const void* paramSet, uint16 paramIndex
                          DEM_DEB_LOCAL_CALC_PARAMS)
{
	sint16_least TimePassedThreshold, TimeFailedThreshold;
	Dem_EventStatusType status2report = DEM_EVENT_STATUS_INVALIDREPORT;
	uint8_least debAction = DEM_DEBACTION_NOOP;
	Dem_boolean_least insertUnrobustToEvBuffer;

#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
	/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
	sint16_least FDCThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].FDCThreshold;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
    /* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
    sint16_least SuspiciousThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].SuspiciousThreshold;
#endif

	DEM_ENTERLOCK_MON();

	(void)Dem_DebHandleResetConditions(EventId);

	switch (Dem_EvtGetLastReportedEvent (EventId))
	{
		case DEM_EVENT_STATUS_PREPASSED:
		{
			/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
			TimePassedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;
			/* if (Dem_EvtGetDebounceLevel (EventId) == TimePassedThreshold)
			{
				 return; INT-LOCK
			} => check not necessary, because it is the else-case of the next statement which also returns directly */

			if (Dem_EvtGetDebounceLevel (EventId) > TimePassedThreshold)
			{
				if (Dem_EvtGetDebounceLevel (EventId) > 0)
				{
					Dem_EvtSetDebounceLevel (EventId, 0);
				}
				Dem_EvtDecDebounceLevel (EventId);


				if (Dem_EvtGetDebounceLevel (EventId) == TimePassedThreshold)
				{
					status2report = DEM_EVENT_STATUS_PASSED;
				}
			}
			else
			{
				if (!Dem_EvtSt_GetTestCompleteTOC(EventId))
				{
					status2report = DEM_EVENT_STATUS_PASSED;
				}
			}
#if (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
			    debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if (SuspiciousThreshold != DEM_MAXSINT16)
                {
                    debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
                }
#endif
			break;
		}

		case DEM_EVENT_STATUS_PREFAILED:
		{
			/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
			TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;
			/* if (Dem_EvtGetDebounceLevel (EventId) == TimeFailedThreshold)
			{
				 return; INT-LOCK
			} => check not necessary, because it is the else-case of the next statement which also returns directly */

			if (Dem_EvtGetDebounceLevel (EventId) < TimeFailedThreshold)
			{
				if (Dem_EvtGetDebounceLevel (EventId) < 0)
				{
					Dem_EvtSetDebounceLevel (EventId, 0);
				}
				Dem_EvtIncDebounceLevel (EventId);

				if (Dem_EvtGetDebounceLevel (EventId) == TimeFailedThreshold)
				{
					status2report = DEM_EVENT_STATUS_FAILED;
				}

#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
				if ( Dem_EvtGetDebounceLevel (EventId) >= FDCThreshold)
				{
					debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#if(DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)
					if(status2report != DEM_EVENT_STATUS_FAILED)
					{
						status2report = DEM_EVENT_STATUS_PREFAILED;
						debAction |= DEM_DEBACTION_ALLOW_BUFFER_INSERT;
					}
#endif
				}
#endif

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if (SuspiciousThreshold != DEM_MAXSINT16)
                {
                    if (Dem_EvtGetDebounceLevel(EventId) >= SuspiciousThreshold)
                    {
                        debAction |= DEM_DEBACTION_SETSUSPICIOUS;
                    }
                }
#endif
			}

			else
			{
				if (!Dem_EvtSt_GetTestFailed(EventId))
				{
					status2report = DEM_EVENT_STATUS_FAILED;
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
					debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
				}
			}

			break;
		}

		case DEM_EVENT_STATUS_PASSED:
		{
			/* setEventStatus is handled in Dem_DebArTime_Filter */
			/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
			TimePassedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimePassedThreshold;
/* FC_VariationPoint_START */


/* FC_VariationPoint_END */
			{

				Dem_EvtSetDebounceLevel (EventId, (sint16) TimePassedThreshold);

				if (Dem_EvtSt_GetTestFailed(EventId))
				{
					status2report = DEM_EVENT_STATUS_PASSED;
				}
#if (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
			debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
                if (SuspiciousThreshold != DEM_MAXSINT16)
                {
                    debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
                }
#endif
			}
			break;
		}

		case DEM_EVENT_STATUS_FAILED:
		{
			/* setEventStatus is handled in Dem_DebArTime_Filter */
			/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
			TimeFailedThreshold = ((const Dem_DebArTime_ParamSet*) paramSet)[paramIndex].TimeFailedThreshold;
/* FC_VariationPoint_START */


/* FC_VariationPoint_END */
			{
				Dem_EvtSetDebounceLevel (EventId, (sint16) TimeFailedThreshold);
				if (!Dem_EvtSt_GetTestFailed(EventId))
				{
					status2report = DEM_EVENT_STATUS_FAILED;
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
			debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
				}
			}
			break;
		}
		default:
		{
		    /* Comment to avoid MISRA warning for Empty Default clause */
			break;
		}
	}

	insertUnrobustToEvBuffer = Dem_DebHandleDebounceAction_4_TimeBasedDeb(EventId, debAction);
	DEM_EXITLOCK_MON();

	if (insertUnrobustToEvBuffer)
	{
	    (void)Dem_EvBuffInsert(C_EVENTTYPE_UNROBUST, EventId DEM_DEBUGDATA_PARAM(0, 0));
	}


	#if(DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
	if (Dem_DistMemIsReportFailedNecessary(EventId, status2report))
	{
		Dem_DistMemReportFailed(EventId
								DEM_DEBUGDATA_PARAM(0 ,0));
	}
	#endif

	if ((status2report == DEM_EVENT_STATUS_PASSED) || (status2report == DEM_EVENT_STATUS_FAILED))
	{
		Dem_EvtProcessPassedAndFailed(EventId, status2report
							   DEM_DEBUGDATA_PARAM(0 ,0));
	}

}
#endif
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


