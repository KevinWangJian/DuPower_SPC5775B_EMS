

#include "Dem_DebCtrBaseClass.h"
#include "Dem_Deb.h"
#include "Dem_Events.h"
#include "Dem_EventStatus.h"
#include "Dem_Lib.h"


#if(DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON)
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#if(DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON)
void Dem_DebCounterBaseClass_GetLimits(const void* paramSet, uint16 paramIndex,sint16_least* MinThreshold,sint16_least* MaxThreshold)
{
    *MaxThreshold = Dem_getDebCtrBaseClassFailedThreshold(paramSet,paramIndex);
    *MinThreshold = Dem_getDebCtrBaseClassPassedThreshold(paramSet,paramIndex);
}
#endif

uint8_least Dem_DebCounterBaseClass_Filter(Dem_EventIdType EventId, Dem_EventStatusType* status, const void* paramSet, uint16 paramIndex
                                           DEM_DEB_LOCAL_CALC_PARAMS)
{
	sint32 maxThreshold = 0;
	sint32 minThreshold = 0;
	sint32 stepDown = 0;
	sint32 stepUp = 0;
	sint32 jumpUpValue = 0;
	sint32 jumpDownValue = 0;
	boolean isJumpUpEnabled = FALSE;
	boolean isJumpDownEnabled = FALSE;
	sint32 debLevel = 0;
	uint8_least debAction = DEM_DEBACTION_NOOP;
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
   (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
	sint32 FDCThreshold = 0;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
    sint32 SuspiciousThreshold = 0;
#endif

    minThreshold = Dem_getDebCtrBaseClassPassedThreshold(paramSet, paramIndex);
    maxThreshold = Dem_getDebCtrBaseClassFailedThreshold(paramSet, paramIndex);
    jumpDownValue = Dem_getDebCtrBaseClassJumpDownValue(paramSet, paramIndex);
    jumpUpValue = Dem_getDebCtrBaseClassJumpUpValue(paramSet, paramIndex);
    isJumpDownEnabled = Dem_getDebCtrBaseClassIsJumpDown(paramSet, paramIndex);
    isJumpUpEnabled = Dem_getDebCtrBaseClassIsJumpUp(paramSet, paramIndex);
    /* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
    stepDown = ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].stepDown;
    /* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
    stepUp = ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].stepUp;
    debLevel = Dem_EvtGetDebounceLevel(EventId);
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
		FDCThreshold = ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].FDCThreshold;
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
		/* MR12 RULE 11.5 VIOLATION: a fast and resource optimized support of different debounce startegies is only possible through this mechanism  */
	SuspiciousThreshold = ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].SuspiciousThreshold;
#endif

	if (Dem_EvtIsResetFailureFilterRequested(EventId))
	{
		debLevel = 0;
		DEM_ENTERLOCK_MON();
		Dem_EvtRequestResetFailureFilter(EventId, FALSE);
		DEM_EXITLOCK_MON();
	}

#if (DEM_CFG_DISTURBANCE_MEMORY == DEM_CFG_DISTURBANCE_MEMORY_ON)
	if ((*status == DEM_EVENT_STATUS_PASSED) || (*status == DEM_EVENT_STATUS_PREPASSED))
	{
		if ((debLevel < maxThreshold) && (Dem_EvtGetLastReportedEvent(EventId) == DEM_EVENT_STATUS_PREFAILED))
		{
		    Dem_DistMemReportPassed(EventId);
		}
	}
#endif


	switch (*status)
	{
	case DEM_EVENT_STATUS_PREPASSED:
	{
		if (debLevel == minThreshold)
		{
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
        if (SuspiciousThreshold != DEM_MAXSINT16)
        {
            debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
        }
#endif
#if (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
        debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
			*status = DEM_EVENT_STATUS_PASSED;
			return debAction;
		}

            if (isJumpDownEnabled && (debLevel > jumpDownValue)	&&
                    ((debLevel == maxThreshold) || (DEM_CFG_LIMIT_RELEVANTFOR_JUMPING != DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_ON)))
		{
			debLevel = (jumpDownValue + stepDown);
		}
		else
		{
			debLevel = (debLevel + stepDown);
		}

		if (debLevel <= minThreshold)
		{
			debLevel = minThreshold;
			*status = DEM_EVENT_STATUS_PASSED;
		}

#if (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
        if ( debLevel < FDCThreshold)
        {
            debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
        }
#endif
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
		if ((SuspiciousThreshold != DEM_MAXSINT16) && (debLevel < SuspiciousThreshold))
		{
		    debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
		}
#endif
		break;
	}

	case DEM_EVENT_STATUS_PREFAILED:
	{

		if (debLevel == maxThreshold)
		{
#if(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
            debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
			*status = DEM_EVENT_STATUS_FAILED;
			return debAction;
		}


            if ((isJumpUpEnabled && (debLevel < jumpUpValue)) &&
                    ((debLevel == minThreshold)  || (DEM_CFG_LIMIT_RELEVANTFOR_JUMPING != DEM_CFG_LIMIT_RELEVANTFOR_JUMPING_ON)))
		{
			debLevel = (jumpUpValue + stepUp);
		}
		else
		{
			debLevel = (debLevel + stepUp);
		}

		if (debLevel >= maxThreshold)
		{
			debLevel = maxThreshold;
			*status = DEM_EVENT_STATUS_FAILED;
		}

#if ((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
	(DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
		if ( debLevel >= FDCThreshold)
		{
			debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#if(DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)
			if(*status != DEM_EVENT_STATUS_FAILED)
			{
				debAction |= DEM_DEBACTION_ALLOW_BUFFER_INSERT;
			}
#endif
		}
#endif

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
            if ((SuspiciousThreshold != DEM_MAXSINT16) && (debLevel < maxThreshold))
            {
                if (debLevel >= SuspiciousThreshold)
                {
                    debAction |= DEM_DEBACTION_SETSUSPICIOUS;
                }
            }
#endif
		break;
	}

	case DEM_EVENT_STATUS_PASSED:
	{
#if(DEM_CFG_SUSPICIOUS_SUPPORT)
        if (SuspiciousThreshold != DEM_MAXSINT16)
        {
            debAction |= DEM_DEBACTION_RESETSUSPICIOUS;
        }
#endif
#if (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED)
        debAction |= DEM_DEBACTION_RESETFDCTHRESHOLDREACHED;
#endif
		if (debLevel == minThreshold)
		{
			return debAction;
		}
		debLevel = minThreshold;
		break;
	}

	case DEM_EVENT_STATUS_FAILED:
	{
#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
            debAction |= DEM_DEBACTION_SETFDCTHRESHOLDREACHED;
#endif
		if (debLevel == maxThreshold)
		{
			return debAction;
		}
		debLevel = maxThreshold;
		break;
	}

	default:
	{
		return debAction;
	}
	}




	Dem_EvtSetDebounceLevel (EventId, (sint16) debLevel);

	return debAction;
}
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif
