

#include "Dem_IndicatorAttributes.h"
#include "Dem_EventStatus.h"
#include "Dem_Nvm.h"

#if (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)

#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
/* MR12 RULE 1.3 VIOLATION: A function-like macro shall not be invoked without all of its arguments, hence some of the arguments are optional based on configuration */
DEM_ARRAY_DEFINE_CONST(Dem_EvtIndicatorAttributeParam, Dem_AllEventsIndicatorParam, DEM_INDICATOR_ATTRIBUTE_ARRAYLENGTH, DEM_CFG_EVENT_INDICATOR_ATTRIBUTE_PARAMS);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DEFINE(Dem_EvtIndicatorAttributeState, Dem_AllEventsIndicatorState, DEM_INDICATOR_ATTRIBUTE_ARRAYLENGTH);
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"

#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

void Dem_IndicatorAttributeInitCheckNvM(void)
{
    Dem_NvmResultType NvmResult;

    if(Dem_NvMIsInvalidateAllNVMBlocksRequested())
    {
        /* Set the indicator state to its default value */
        DEM_MEMSET( &Dem_AllEventsIndicatorState, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsIndicatorState));
        Dem_NvMClearBlockByInvalidate(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
    }
    else
    {
        /* Get the Result of the NvM-Read (NvM_ReadAll) */
        NvmResult = Dem_NvmGetStatus (DEM_NVM_ID_INDICATOR_ATTRIBUTES);

        /* Data read successfully */
        if (NvmResult != DEM_NVM_SUCCESS)
        {
            /* Set the indicator state to its default value */
            DEM_MEMSET( &Dem_AllEventsIndicatorState, 0x00, DEM_SIZEOF_VAR(Dem_AllEventsIndicatorState));
            Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
        }
    }
}


void Dem_IndicatorAttributeInit(void)
{
    uint32 i;

    for(i = 0u; DEM_INDICATOR_ATTRIBUTE_COUNT > i; i++)
    {
        if(Dem_IsIndicatorAttributeValid(i))
        {
            if(Dem_IndicatorAttribGetFailureCycCtr(i) == 0xFF)
            {
                Dem_IndicatorIncrementBehaviourCounter(Dem_IndicatorAttrib_GetIndicatorId(i), Dem_IndicatorAttrib_GetBehaviour(i));
            }
        }
    }
}


/*
 * Dem_SetIndicatorDeActivation is returning TRUE if no indicator is ON and condition to deactivate WIR is fulfilled.
 * i.e, If DeaActivationTrigger( Transition for TF, TFTOC and CONFIRM bit) and HealingThreshold is not reached, indicator is still ON.
 */
void Dem_SetIndicatorDeActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{

    /* Variable for Indicator Attribute */
    uint8 healingCycCtr;
    uint8 healingCycCtrThreshold;
    uint8 indicatorBehaviour;

    /* Variable for Iteration Function */
    uint16_least currentIndicAttrib = 0;
    Dem_EventIndicatorAttributeIterator it;

    /* Variable for Indicator */
    uint8 indicatorId;

    for(Dem_EventIndicatorAttributeIteratorNew(EventId, &it); Dem_EventIndicatorAttributeIsValid(EventId, &it);
            Dem_EventIndicatorAttributeNext(&it))
    {
        currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);

        if ((Dem_IsIndicatorAttributeValid(currentIndicAttrib)) && (Dem_IndicatorAttrib_IsApiControl(currentIndicAttrib) == FALSE))
        {

            /* Get the internal healing counter value*/
            healingCycCtr = Dem_IndicatorAttribGetHealingCycCtr(currentIndicAttrib);

            /* Get the configured indicator attribute values(FLASH) */
            indicatorBehaviour = Dem_IndicatorAttrib_GetBehaviour(currentIndicAttrib);
            indicatorId = Dem_IndicatorAttrib_GetIndicatorId(currentIndicAttrib);
            healingCycCtrThreshold = Dem_IndicatorAttrib_GetHealingCycleThreshold(currentIndicAttrib);

            /* Indicator Attribute triggers the Indicator */
            if (Dem_IndicatorAttribGetFailureCycCtr(currentIndicAttrib) == 0xFF)
            {
                /* Increment healing counter when its configured and global define is not used(global value defined as zero, so no need to increment healing counter)*/
#if (DEM_CFG_EVTINDICATOR_HEALINGTHRESHOLD == DEM_CFG_EVTINDICATOR_HEALINGTHRESHOLD_ON)
                if((healingCycCtr < healingCycCtrThreshold) && (!Dem_ISO14229ByteIsTestFailedTOC(isoByteOld)) && (!Dem_ISO14229ByteIsTestCompleteTOC(isoByteOld)))
                {
                    healingCycCtr++;
                    Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, healingCycCtr);
                }
#else
                DEM_UNUSED_PARAM(isoByteOld);
#endif

                if (healingCycCtr >= healingCycCtrThreshold)
                {
                    /* checking healing cycle counter value for indicators attributes which is mapped per event
                     * and the if the below conditions are satisfied update warning indicator bit for the event and resetting healing counter value to zero.
                     */
                    /* Indicator Attribute healed the behaviour counter shall be decremented */
                    Dem_IndicatorDecrementBehaviourCounter(indicatorId, indicatorBehaviour);

                    /* Resetting healing counter when it reaches threshold */
                    Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, 0);

                    /* reset failure counter */
                    Dem_IndicatorAttribSetFailureCycCtr(currentIndicAttrib, 0);
                }

            }
        }
    }
    Dem_UpdateISO14229WIRStatus(EventId);
    DEM_UNUSED_PARAM(isoByteNew);
}


/* Function called whenever monitor reports failed */
void Dem_SetIndicatorActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{

	/* Variable for Indicator Attribute */
	uint8 failureCycCtr;
	uint8 failureCycCtrThreshold;
	uint8 indicatorBehaviour;

	/* Variable for Indicator */
	uint8 indicatorId;
	Dem_boolean_least anyIndicatorOn = FALSE;

	/* Variable for Iteration Function */
	uint16_least currentIndicAttrib = 0;
	Dem_EventIndicatorAttributeIterator it;

	for(Dem_EventIndicatorAttributeIteratorNew(EventId, &it); Dem_EventIndicatorAttributeIsValid(EventId, &it);
			Dem_EventIndicatorAttributeNext(&it))
	{
		currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);

		if ((Dem_IsIndicatorAttributeValid(currentIndicAttrib)) && (Dem_IndicatorAttrib_IsApiControl(currentIndicAttrib) == FALSE))
		{

			/* Get indicator attribute failure internal counter value */
			failureCycCtr = Dem_IndicatorAttribGetFailureCycCtr(currentIndicAttrib);

			/* if indicator is not triggered */
			if (failureCycCtr < 0xFF)
			{
				/* Get the configured indicator attribute values(FLASH) */
				failureCycCtrThreshold = Dem_IndicatorAttrib_GetFailureCycleThreshold(currentIndicAttrib);
				indicatorId = Dem_IndicatorAttrib_GetIndicatorId(currentIndicAttrib);
				indicatorBehaviour = Dem_IndicatorAttrib_GetBehaviour(currentIndicAttrib);

				/* Increment failure counter when its configured */
#if(DEM_CFG_EVTINDICATOR_FAILURETHRESHOLD == DEM_CFG_EVTINDICATOR_FAILURETHRESHOLD_ON)
				if ((failureCycCtr < failureCycCtrThreshold) && Dem_ISO14229ByteIsTestFailedTOC(isoByteNew) && (!Dem_ISO14229ByteIsTestFailedTOC(isoByteOld)))
				{
					failureCycCtr++;
				}
#else
				DEM_UNUSED_PARAM(isoByteOld);
				DEM_UNUSED_PARAM(isoByteNew);
#endif

				/* checking failure cycle counter value for indicator Attribute which is mapped per event
				 * and if this condition satisfies update WIR Status for Event and resetting failure counter value.
				 */
				if(failureCycCtr >= failureCycCtrThreshold)
				{
					/* Function to process corresponding behaviour counters [If indicator behaviour is Blinking : blinkingCounter++
					 * If behaviour is Continuos : countinuousCounter++, If behaviour is BLINK_CONT increment both counters]*/
					Dem_IndicatorIncrementBehaviourCounter(indicatorId, indicatorBehaviour);

					/* Resetting failure counter when it reaches threshold */
					failureCycCtr = 0xFF;
					anyIndicatorOn = TRUE;
				}

				/* Set the latest failure cycle counter value*/
				Dem_IndicatorAttribSetFailureCycCtr(currentIndicAttrib, failureCycCtr);
			}
			else
			{
				anyIndicatorOn = TRUE;
			}

			Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, 0);
		}
	}

    if(anyIndicatorOn)
    {
        Dem_EvtSt_HandleIndicatorOn(EventId);
    }

}

Dem_boolean_least Dem_isAnyIndicatorAttribOn (Dem_EventIdType EventId)
{

   Dem_EventIndicatorAttributeIterator it;
   uint16_least currentIndicAttrib = 0;
   Dem_boolean_least retVal = FALSE;

   for ( Dem_EventIndicatorAttributeIteratorNew(EventId, &it);
         Dem_EventIndicatorAttributeIsValid(EventId, &it);
         Dem_EventIndicatorAttributeNext(&it)
   )
   {
       currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);

       if (Dem_IsIndicatorAttributeValid(currentIndicAttrib))
       {
           if (Dem_IndicatorAttribGetFailureCycCtr(currentIndicAttrib) == 0xFF)
           {
               retVal = TRUE;
               break;
           }
       }
   }

   return retVal;
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif




