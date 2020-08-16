



#ifndef DEM_INDICATOR_H
#define DEM_INDICATOR_H

#include "Dem_Types.h"


#if (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)
typedef struct
{
	uint16 blinkingCtr;
	uint16 continousCtr;
} Dem_IndicatorStatus;


#define DEM_START_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE(Dem_IndicatorStatus, Dem_AllIndicatorStatus, DEM_INDICATORID_ARRAYLENGTH);
#define DEM_STOP_SEC_RAM_CLEARED
#include "Dem_Cfg_MemMap.h"

DEM_INLINE uint16 Dem_IndicatorGetBlinkingCounter(uint8 indicatorId)
{
	return (Dem_AllIndicatorStatus[indicatorId].blinkingCtr);
}

DEM_INLINE uint16 Dem_IndicatorGetContinuousCounter(uint8 indicatorId)
{
	return (Dem_AllIndicatorStatus[indicatorId].continousCtr);
}

DEM_INLINE void Dem_IndicatorSetContinuousCtr(uint8 indicatorId, uint16 continuousCtr)
{
	Dem_AllIndicatorStatus[indicatorId].continousCtr = continuousCtr;
}

DEM_INLINE void Dem_IndicatorSetBlinkingCtr(uint8 indicatorId, uint16 blinkingCtr)
{
	Dem_AllIndicatorStatus[indicatorId].blinkingCtr = blinkingCtr;
}

DEM_INLINE void Dem_IndicatorIncrementBehaviourCounter(uint8 indicatorId, uint8 indicatorBehaviour)
{
	uint16 blinkingCounter = Dem_IndicatorGetBlinkingCounter(indicatorId);
	uint16 countinuousCounter = Dem_IndicatorGetContinuousCounter(indicatorId);

	if((DEM_INDICATOR_CONTINUOUS & indicatorBehaviour)!=0u)
	{
		countinuousCounter++;
		Dem_IndicatorSetContinuousCtr(indicatorId, countinuousCounter);
	}

	if((DEM_INDICATOR_BLINKING & indicatorBehaviour)!=0u)
	{
		blinkingCounter++;
		Dem_IndicatorSetBlinkingCtr(indicatorId, blinkingCounter);
	}
}

DEM_INLINE void Dem_IndicatorDecrementBehaviourCounter(uint8 indicatorId, uint8 indicatorBehaviour)
{
	uint16 blinkingCounter = Dem_IndicatorGetBlinkingCounter(indicatorId);
	uint16 countinuousCounter = Dem_IndicatorGetContinuousCounter(indicatorId);

	if (((DEM_INDICATOR_CONTINUOUS & indicatorBehaviour) != 0u)  && (countinuousCounter > 0u))
	{
		countinuousCounter--;
		Dem_IndicatorSetContinuousCtr(indicatorId, countinuousCounter);
	}

	if (((DEM_INDICATOR_BLINKING & indicatorBehaviour) != 0u) && (blinkingCounter > 0u))
	{
		blinkingCounter--;
		Dem_IndicatorSetBlinkingCtr(indicatorId, blinkingCounter);
	}
}

DEM_INLINE uint8 Dem_EvtGetIndicatorStatus(uint8 indicatorId)
{
    uint8 IndicatorStatus;

    DEM_ENTERLOCK_MON();

	if((Dem_IndicatorGetBlinkingCounter(indicatorId) > 0u) && (Dem_IndicatorGetContinuousCounter(indicatorId) == 0u))
	{
	    IndicatorStatus = DEM_INDICATOR_BLINKING;
	}
	else if((Dem_IndicatorGetBlinkingCounter(indicatorId) == 0u) && (Dem_IndicatorGetContinuousCounter(indicatorId) > 0u))
	{
	    IndicatorStatus = DEM_INDICATOR_CONTINUOUS;
	}
	else if((Dem_IndicatorGetBlinkingCounter(indicatorId) > 0u) && (Dem_IndicatorGetContinuousCounter(indicatorId) > 0u))
	{
	    IndicatorStatus = DEM_INDICATOR_BLINK_CONT;
	}
	else
	{
	    IndicatorStatus = DEM_INDICATOR_OFF;
	}

	DEM_EXITLOCK_MON();

	return IndicatorStatus;
}

#endif /* DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON */


void Dem_UpdateISO14229WIRStatus (Dem_EventIdType EventId);


#endif
