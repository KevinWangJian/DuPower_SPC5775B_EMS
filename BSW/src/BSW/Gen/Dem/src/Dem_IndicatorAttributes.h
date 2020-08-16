



#ifndef DEM_INDICATORATTRIBUTES_H
#define DEM_INDICATORATTRIBUTES_H

#include "Dem_Types.h"
#include "Dem_Array.h"
#include "Dem_BitArray.h"
#include "rba_DiagLib_Bits8.h"
#include "rba_DiagLib_Bits16.h"
#include "rba_DiagLib_Bits32.h"
#include "Dem_Cfg_EventIndicators.h"
#include "Dem_ISO14229Byte.h"
#include "Dem_Mapping.h"
#include "Dem_Indicator.h"
#include "Dem_Nvm.h"

#if(DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_PROJECTSPECIFIC)


#include "Dem_PrjSpecificIndiHandling.h"


#elif (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_OFF)


#define Dem_isAnyIndicatorAttribOn(X)                                       (FALSE)
#define Dem_IndicatorAttributeInitCheckNvM()                                do {} while (0)
#define Dem_IndicatorAttributeMainFunction()                                do {} while (0)
#define Dem_IndicatorAttributeInit()                                        do {} while (0)
#define Dem_IndicatorAttributeShutdown()                                    do {} while (0)
#define Dem_SetIndicatorActivation(X,Y,Z)                                   do {} while (0)
#define Dem_SetIndicatorDeActivation(X,Y,Z)                                 do {} while (0)
#define Dem_ClearIndicatorAttributes(X,Y,Z)                                 do {} while (0)
#define Dem_IndicatorAttribute_ConsistencyCheck(X,Y)                        do {} while (0)
#define Dem_SetIndicatorDeActivation_OnEvMemSetStatusNotification(X,Y,Z)    do {} while (0)
#define Dem_SetIndicatorDeActivation_OnEvMemClearStatusNotification(X,Y,Z)  do {} while (0)
#define Dem_SetIndicatorDeActivation_OnOperationCycleChange(X,Y,Z)          do {} while (0)


#elif (DEM_CFG_EVT_INDICATOR == DEM_CFG_EVT_INDICATOR_ON)

#if !((DEM_INDICATOR_CONTINUOUS == 0x01) && (DEM_INDICATOR_BLINKING == 0x02) && (DEM_INDICATOR_BLINK_CONT == 0x03))
#error The implemetation of Dem_EvtIndicatorAttributeParam and Dem_IndicatorIncrementBehaviourCounter() and Dem_IndicatorResetBehaviourCounter() relies on the following definitions (DEM_INDICATOR_CONTINUOUS == 0x01 && DEM_INDICATOR_BLINKING == 0x02 && DEM_INDICATOR_BLINK_CONT == 0x03)
#endif

typedef struct
{
   /* Variable to represents event to Indicator Attribute */
   Dem_EvtIndicatorParamType attributes;
}Dem_EvtIndicatorAttributeParam;

typedef struct
{
    uint8 failureCycleCounterVal;
    uint8 healingCycleCounterVal;
} Dem_EvtIndicatorAttributeState;

#define DEM_EVTS_INDICATOR_ATTRIBUTE_INIT(BEHAVIOUR,        	\
		FAILURE_THRESHOLD,                    		\
		HEALING_THRESHOLD,                         	\
		INDICATOR_ID,								\
		APICONTROL                          \
		)                         							\
     {                                              		\
    (Dem_EvtIndicatorParamType)0u + (Dem_EvtIndicatorParamType)DEM_EVTINDICATOR_PARAMINI_BEHAVIOUR(BEHAVIOUR) 	\
       + (Dem_EvtIndicatorParamType)DEM_EVTINDICATOR_PARAMINI_FAILTHRESHOLD(FAILURE_THRESHOLD)             	\
       + (Dem_EvtIndicatorParamType)DEM_EVTINDICATOR_PARAMINI_HEALTHRESHOLD(HEALING_THRESHOLD)                 \
       + (Dem_EvtIndicatorParamType)DEM_EVTINDICATOR_PARAMINI_INDICATORID(INDICATOR_ID)						\
       + (Dem_EvtIndicatorParamType)DEM_EVTINDICATOR_PARAMINI_APICONTROL(APICONTROL)                     \
     }

#define Dem_IndicatorAttributeMainFunction()                                do {} while (0)
#define Dem_IndicatorAttributeShutdown()                                    do {} while (0)
#define Dem_IndicatorAttribute_ConsistencyCheck(X,Y)                        do {} while (0)
#define Dem_SetIndicatorDeActivation_OnEvMemSetStatusNotification(X,Y,Z)    do {} while (0)
#define Dem_SetIndicatorDeActivation_OnEvMemClearStatusNotification(X,Y,Z)  do {} while (0)
#define Dem_SetIndicatorDeActivation_OnOperationCycleChange(X,Y,Z)          do {} while (0)


#define DEM_START_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE_CONST(Dem_EvtIndicatorAttributeParam, Dem_AllEventsIndicatorParam, DEM_INDICATOR_ATTRIBUTE_ARRAYLENGTH);
#define DEM_STOP_SEC_ROM_CONST
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"
DEM_ARRAY_DECLARE(Dem_EvtIndicatorAttributeState, Dem_AllEventsIndicatorState, DEM_INDICATOR_ATTRIBUTE_ARRAYLENGTH);
#define DEM_STOP_SEC_SAVED_ZONE
#include "Dem_Cfg_MemMap.h"


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"


/* Collect indicator Attribute configured values from Flash */
DEM_INLINE uint8 Dem_IndicatorAttrib_GetIndicatorId(uint16_least indicatorIndex)
{
	return (uint8) DEM_EVTINDICATORPARAM_GETBITS(Dem_AllEventsIndicatorParam[indicatorIndex].attributes,
			DEM_EVTINDICATOR_BP_PARAM_INDICATORID,
			DEM_INDICATOR_ID_REQUIRED_BIT_SIZE);
}

DEM_INLINE uint8 Dem_IndicatorAttrib_GetBehaviour(uint16_least indicatorIndex)
{
#if(!DEM_CFG_EVTINDICATOR_IS_COMMON_BEHAVIOUR_USED)
	return (uint8) DEM_EVTINDICATORPARAM_GETBITS(Dem_AllEventsIndicatorParam[indicatorIndex].attributes,
			DEM_EVTINDICATOR_BP_PARAM_BEHAVIOUR,
			DEM_INDICATOR_ATTRIBUTE_REQUIRED_BIT_SIZE);
#else
	DEM_UNUSED_PARAM(indicatorIndex);
	return DEM_CFG_EVTINDICATOR_GLOBAL_DEFINE_BEHAVIOUR;
#endif
}

DEM_INLINE uint8 Dem_IndicatorAttrib_GetFailureCycleThreshold(uint16_least indicatorIndex)
{
#if ((DEM_CFG_EVTINDICATOR_FAILURETHRESHOLD == DEM_CFG_EVTINDICATOR_FAILURETHRESHOLD_ON) && (!DEM_CFG_EVTINDICATOR_IS_COMMON_FAILURETHRESHOLD_USED))
	return (uint8) DEM_EVTINDICATORPARAM_GETBITS(Dem_AllEventsIndicatorParam[indicatorIndex].attributes,
			DEM_EVTINDICATOR_BP_PARAM_FAILTHRESHOLD,
			DEM_INDICATOR_FAILURE_THRESHOLD_REQUIRED_BIT_SIZE);
#else
	DEM_UNUSED_PARAM(indicatorIndex);
	return DEM_CFG_DEFAULT_FAILURE_THRESHOLD;
#endif
}

DEM_INLINE uint8 Dem_IndicatorAttrib_GetHealingCycleThreshold(uint16_least indicatorIndex)
{
#if ((DEM_CFG_EVTINDICATOR_HEALINGTHRESHOLD == DEM_CFG_EVTINDICATOR_HEALINGTHRESHOLD_ON) && (!DEM_CFG_EVTINDICATOR_IS_COMMON_HEALINGTHRESHOLD_USED))
	return (uint8) DEM_EVTINDICATORPARAM_GETBITS(Dem_AllEventsIndicatorParam[indicatorIndex].attributes,
			DEM_EVTINDICATOR_BP_PARAM_HEALTHRESHOLD,
			DEM_INDICATOR_HEALING_THRESHOLD_REQUIRED_BIT_SIZE);
#else
	DEM_UNUSED_PARAM(indicatorIndex);
	return DEM_CFG_DEFAULT_HEALING_THRESHOLD;
#endif
}



DEM_INLINE boolean Dem_IndicatorAttrib_IsApiControl(uint16_least indicatorIndex)
{
   return DEM_EVTINDICATORPARAM_ISBITSET(Dem_AllEventsIndicatorParam[indicatorIndex].attributes, DEM_EVTINDICATOR_BP_PARAM_APICONTROL);
}

/*-- Failure Counter ----------------------------------------------------------*/

DEM_INLINE uint8 Dem_IndicatorAttribGetFailureCycCtr(uint16_least indicatorIndex)
{
   return Dem_AllEventsIndicatorState[indicatorIndex].failureCycleCounterVal;
}

DEM_INLINE void Dem_IndicatorAttribSetFailureCycCtr(uint16_least indicatorIndex, uint8 failureCtr)
{
	Dem_AllEventsIndicatorState[indicatorIndex].failureCycleCounterVal = failureCtr;
	Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
}

/*-- Healing Counter ----------------------------------------------------------*/

DEM_INLINE uint8 Dem_IndicatorAttribGetHealingCycCtr (uint16_least indicatorIndex)
{
   return Dem_AllEventsIndicatorState[indicatorIndex].healingCycleCounterVal;
}

DEM_INLINE void Dem_IndicatorAttribSetHealingCycCtr(uint16_least indicatorIndex, uint8 healingCtr)
{
	Dem_AllEventsIndicatorState[indicatorIndex].healingCycleCounterVal = healingCtr;
	Dem_NvMWriteBlockOnShutdown(DEM_NVM_ID_INDICATOR_ATTRIBUTES);
}



/*****************Indicator Attribute validator function ********************************/
DEM_INLINE Dem_boolean_least Dem_IsIndicatorAttributeValid(uint16_least indicatorIndex)
{
	return (Dem_AllEventsIndicatorParam[indicatorIndex].attributes != DEM_INDICATOR_ATTRIBUTE_INVALID);
}




void Dem_SetIndicatorDeActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew);
void Dem_SetIndicatorActivation(Dem_EventIdType EventId, Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew);
void Dem_IndicatorAttributeInit(void);
void Dem_IndicatorAttributeInitCheckNvM(void);
Dem_boolean_least Dem_isAnyIndicatorAttribOn (Dem_EventIdType EventId);



DEM_INLINE void Dem_ClearIndicatorAttributes(Dem_EventIdType EventId,Dem_UdsStatusByteType isoByteOld, Dem_UdsStatusByteType isoByteNew)
{

    Dem_EventIndicatorAttributeIterator it;
    uint16_least currentIndicAttrib = 0;
    uint8 indicatorId, indicatorBehaviour;

    DEM_ASSERT_ISLOCKED();

    if (!Dem_ISO14229ByteIsWarningIndicatorRequested(isoByteNew))
    {

        for (Dem_EventIndicatorAttributeIteratorNew(EventId, &it); Dem_EventIndicatorAttributeIsValid(EventId, &it);
                Dem_EventIndicatorAttributeNext(&it))
        {
            currentIndicAttrib = Dem_EventIndicatorAttributeCurrent(&it);
            if (Dem_IsIndicatorAttributeValid(currentIndicAttrib))
            {
                indicatorId = Dem_IndicatorAttrib_GetIndicatorId(currentIndicAttrib);
                indicatorBehaviour = Dem_IndicatorAttrib_GetBehaviour(currentIndicAttrib);
                if (Dem_IndicatorAttribGetFailureCycCtr(currentIndicAttrib) == 0xFF)
                {
                    Dem_IndicatorDecrementBehaviourCounter(indicatorId, indicatorBehaviour);
                }
                Dem_IndicatorAttribSetFailureCycCtr(currentIndicAttrib, 0);
                Dem_IndicatorAttribSetHealingCycCtr(currentIndicAttrib, 0);
            }
        }
    }

    DEM_UNUSED_PARAM(isoByteOld);
}

#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"

#endif

#endif

