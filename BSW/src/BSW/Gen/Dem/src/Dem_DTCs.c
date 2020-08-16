

#include "Dem.h"
#include "Dem_Dcm.h"
#include "Rte_Dem.h"

#include "Dem_DTCs.h"

#include "Dem_Deb.h"
#include "Dem_Events.h"
#include "Dem_EventStatus.h"
#include "Dem_Nvm.h"
#include "Dem_Mapping.h"
#include "Dem_Obd.h"
#include "Dem_DTCGroup.h"
#include "Dem_Cfg_ExtPrototypes.h"


#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

    DEM_ARRAY_DEFINE(Dem_DtcState, Dem_AllDTCsState, DEM_DTCID_ARRAYLENGTH);

#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"

    #if (DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
    boolean Dem_AlternativeDTCEnabled = FALSE;
    #endif

#define DEM_STOP_SEC_RAM_INIT
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

    DEM_ARRAY_DEFINE_CONST(Dem_DtcParam8, Dem_AllDTCsParam8, DEM_DTCID_ARRAYLENGTH, DEM_CFG_DTCPARAMS8);
    /* FC_VariationPoint_START */
    #if (DEM_CFG_OBD == DEM_CFG_OBD_ON) && (DEM_CFG_OBD_DTC_CONFIG != DEM_CFG_OBD_DTC_CONFIG_OFF)
    DEM_ARRAY_DEFINE_CONST(Dem_DtcParam16, Dem_AllDTCsParam16, DEM_DTCID_ARRAYLENGTH, DEM_CFG_DTCPARAMS16);
    #endif
    /* FC_VariationPoint_END */
    DEM_ARRAY_DEFINE_CONST(Dem_DtcParam32, Dem_AllDTCsParam32, DEM_DTCID_ARRAYLENGTH, DEM_CFG_DTCPARAMS32);
    #if (DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
    DEM_ARRAY_DEFINE_CONST(Dem_DtcAltParam, Dem_AllAlternativeDTCsParam, DEM_ALTERNATIVE_DTCCODE_ARRAYLENGTH, DEM_CFG_ALTERNATIVE_DTCPARAMS);
    #endif

#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#if (DEM_CFG_ALTERNATIVEDTC == DEM_CFG_ALTERNATIVEDTC_ON)
void Dem_SwitchToAlternativeDtc(void)
{
	Dem_AlternativeDTCEnabled = TRUE;
}
#endif


/*************************CheckDTCSettingStatus****************************************************/

Dem_boolean_least Dem_IsEventEnabledByDtcSetting(Dem_EventIdType EventId)
{
    if (Dem_EventIdIsDtcAssigned(EventId))
    {
        if(!Dem_DtcIsDTCSettingEnabled(Dem_DtcIdFromEventId(EventId)))
        {
#if(DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED == DEM_DTC_DTCSETTING_CALLBACK_SUPPORTED_ON)
            //invoke the global config callback to get the DTC Disable status
            if(DEM_DTC_CALLBACK_FUNCTION_DISABLE_DTCSETTING_ALLOWED(EventId))
#endif
            {
                return FALSE;
            }
        }
    }
    return TRUE;
}



/*-- DTC CODE ----------------------------------------------------------------*/

Dem_DtcIdType Dem_DtcIdFromDtcCode (Dem_DtcCodeType dtcCode)
{
	Dem_DtcIdIterator dtcId;

	for (Dem_DtcIdIteratorNew(&dtcId);
			Dem_DtcIdIteratorIsValid(&dtcId);
			Dem_DtcIdIteratorNext(&dtcId))
	{
		if (Dem_DtcGetCode(Dem_DtcIdIteratorCurrent(&dtcId)) == dtcCode)
		{
			return Dem_DtcIdIteratorCurrent(&dtcId);
		}
	}
	return DEM_DTCID_INVALID;
}

/*-- PUBLIC INTERFACES -------------------------------------------------------*/

Std_ReturnType Dem_GetDTCOfEvent(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
{
   Dem_DtcIdType dtcId;

   DEM_ENTRY_CONDITION_CHECK_INIT_EVTIDVALID_EVTAVAILABLE(EventId,DEM_DET_APIID_DEM_GETDTCOFEVENT,E_NOT_OK);
   DEM_ENTRY_CONDITION_CHECK_NOT_NULL_PTR(DTCOfEvent,DEM_DET_APIID_DEM_GETDTCOFEVENT,E_NOT_OK);

   if (!Dem_EventIdIsDtcAssigned(EventId))
   {
      return DEM_E_NO_DTC_AVAILABLE;
   }

   dtcId = Dem_DtcIdFromEventId(EventId);

   if (DTCFormat == DEM_DTC_FORMAT_UDS)
   {
      *DTCOfEvent = Dem_DtcGetCode(dtcId);
      return E_OK;
   }
   else if (DTCFormat == DEM_DTC_FORMAT_OBD)
   {
/* FC_VariationPoint_START */
#if (DEM_CFG_OBD != DEM_CFG_OBD_OFF)
      *DTCOfEvent = rba_DemObdBasic_Dtc_GetCode(dtcId);
      return E_OK;
#else
/* FC_VariationPoint_END */
      return E_NOT_OK;
/* FC_VariationPoint_START */
#endif
/* FC_VariationPoint_END */
   }
   else
   {
      DEM_ASSERT_ISNOTLOCKED(); //To ensure that early return does not exit from within lock
      DEM_DET(DEM_DET_APIID_DEM_GETDTCOFEVENT,DEM_E_WRONG_CONFIGURATION);
      return E_NOT_OK;
   }
}

Std_ReturnType Dem_GetDTCOfEvent_GeneralEvtInfo(Dem_EventIdType EventId, Dem_DTCFormatType DTCFormat, uint32* DTCOfEvent)
{
    return Dem_GetDTCOfEvent(EventId, DTCFormat, DTCOfEvent);

}

Dem_DTCTranslationFormatType Dem_GetTranslationType(void)
{
   return DEM_CFG_DTC_TRANSLATION_TYPE;
}


Std_ReturnType Dem_GetDTCStatusAvailabilityMask(uint8* DTCStatusMask)
{
   *DTCStatusMask = DEM_CFG_DTCSTATUS_AVAILABILITYMASK;
   return E_OK;
}


Dem_ReturnGetSeverityOfDTCType Dem_GetSeverityOfDTC(uint32 DTC, Dem_DTCSeverityType* DTCSeverity)
{
   Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode(DTC);

   if (!Dem_DtcIsSupported(dtcId))
   {
      return DEM_GET_SEVERITYOFDTC_WRONG_DTC;
   }

   *DTCSeverity = Dem_DtcGetSeverity(dtcId);
   return DEM_GET_SEVERITYOFDTC_OK;
/* FC_VariationPoint_START */
   

/* FC_VariationPoint_END */
}


Dem_ReturnGetFunctionalUnitOfDTCType Dem_GetFunctionalUnitOfDTC (uint32 DTC, uint8* DTCFunctionalUnit)
{
   Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode(DTC);

   if (!Dem_DtcIsSupported(dtcId))
   {
      return DEM_GET_FUNCTIONALUNITOFDTC_WRONG_DTC;
   }

   *DTCFunctionalUnit = Dem_DtcGetFuncUnit(dtcId);
   return DEM_GET_FUNCTIONALUNITOFDTC_OK;
}

Std_ReturnType Dem_SetDTCSuppression (uint32 DTC, Dem_DTCFormatType DTCFormat, boolean SuppressionStatus)
{
#if ((DEM_CFG_SUPPRESSION == DEM_DTC_SUPPRESSION) || (DEM_CFG_SUPPRESSION == DEM_EVENT_AND_DTC_SUPPRESSION))

	Dem_DtcIdType dtcId = Dem_DtcIdFromDtcCode(DTC);

    DEM_ENTRY_CONDITION_CHECK_DEM_PREINITIALIZED(DEM_DET_APIID_DEM_SETDTCSUPPRESSION,E_NOT_OK);

   if (DTCFormat == DEM_DTC_FORMAT_UDS)
   {
      dtcId = Dem_DtcIdFromDtcCode(DTC);
   }
   else /* DEM_DTC_FORMAT_OBD */
   {
      /* not implemented, DEM specification not clear eg: regarding handling of readiness */
	  	DEM_ASSERT_ISNOTLOCKED();	//to ensure that early return does not exit from within lock
	  	//DET reported incase DTC FOrmat is neither OBD nor UDS
	    DEM_DET(DEM_DET_APIID_DEM_SETDTCSUPPRESSION,DEM_E_WRONG_CONFIGURATION);
	  return E_NOT_OK;
   }

	/**
	 * Dem588: The API Dem_SetDTCSuppression shall reject the request and return E_NOT_OK,
	 * if the event memory entry exists already.
	 */
	if ((!Dem_isDtcIdValid(dtcId)) || (Dem_IsEventMemoryEntryExistForDTC(dtcId)))
	{
	    DEM_ASSERT_ISNOTLOCKED();   //to ensure that early return does not exit from within lock
	    DEM_DET(DEM_DET_APIID_DEM_SETDTCSUPPRESSION,DEM_E_WRONG_CONFIGURATION);
		return E_NOT_OK;
	}
	else
	{
		Dem_DtcSuppressionApply(dtcId, SuppressionStatus);
		return E_OK;
	}
#else
	DEM_UNUSED_PARAM(DTC);
	DEM_UNUSED_PARAM(DTCFormat);
	DEM_UNUSED_PARAM(SuppressionStatus);
	return E_NOT_OK;
#endif
}




/***************************************************/
/* DtcLevel Fault Detection Counter */
/***************************************************/

sint8 Dem_DtcFaultDetectionRetrieve (Dem_DtcIdType dtcId)
{
	Dem_EventIdListIterator eventIt;
	Dem_EventIdType eventId;
	sint8 faultDetectionCtrVal=0;
	sint8 maxFaultDetectionCtrVal = -128;
	sint8 returnValue = 0;

	if (Dem_DtcIsSupported(dtcId))
	{
		for (Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
				Dem_EventIdListIteratorIsValid(&eventIt);
				Dem_EventIdListIteratorNext(&eventIt))
		{
			eventId = Dem_EventIdListIteratorCurrent(&eventIt);
			if (Dem_GetFaultDetectionCounter(eventId, &faultDetectionCtrVal) == E_OK)
			{
			    DEM_A_MAX_AB(maxFaultDetectionCtrVal, faultDetectionCtrVal);
			                    returnValue=maxFaultDetectionCtrVal;
			}

		}
	}
	return returnValue;
}
/***************************************************/
/* DtcFault Detection Counter based on dtcCode */
/***************************************************/

Std_ReturnType Dem_GetDtcFaultDetectionCounter(Dem_DtcCodeType dtcCode, sint8* FaultDetectionCounter)
{
    Dem_DtcIdType dtcId;

    if( FaultDetectionCounter != NULL_PTR )
    {
        dtcId = Dem_DtcIdFromDtcCode(dtcCode);

        if( Dem_isDtcIdValid(dtcId) )
        {
            *FaultDetectionCounter = Dem_DtcFaultDetectionRetrieve(dtcId);
            return E_OK;
        }
    }

    return E_NOT_OK;
}



void Dem_DtcSetDTCSetting (Dem_DtcIdType dtcId, Dem_boolean_least setBit)
{
    Dem_EventIdListIterator eventIt;

    DEM_ENTERLOCK_MON();
    DEM_DTCSTATE_OVERWRITEBIT (&Dem_AllDTCsState[dtcId].state, DEM_DTC_BP_GROUP_DTCSETTING_DISABLED, setBit);

    if (!setBit)
    {
        for (Dem_EventIdListIteratorNewFromDtcId(&eventIt, dtcId);
                Dem_EventIdListIteratorIsValid(&eventIt);
                Dem_EventIdListIteratorNext(&eventIt))
        {
            Dem_EvtSt_HandleDTCSettingOn(Dem_EventIdListIteratorCurrent(&eventIt));
            Dem_EvtSetInitMonitoring((Dem_EventIdListIteratorCurrent(&eventIt)), DEM_INIT_MONITOR_REENABLED);
        }
    }

    DEM_EXITLOCK_MON();
}


#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
