

#ifndef DEM_ENVTRIGGER_H
#define DEM_ENVTRIGGER_H


typedef struct
{
	/* In Parameter */
	Dem_TriggerType currentTrigger;
	Dem_TriggerType storedTrigger;
	/* Out Parameter */
	Dem_TriggerType matchingTrigger;
} Dem_EnvTriggerParamType;


DEM_INLINE void Dem_EnvSetTrigger(Dem_TriggerType* trigger, Dem_TriggerType trigger2set)
{
	*trigger = (*trigger) | trigger2set;
}

DEM_INLINE Dem_boolean_least Dem_EnvIsAnyTriggerSet(Dem_TriggerType trigger2test)
{
	return (Dem_boolean_least)(trigger2test != 0);
}

DEM_INLINE Dem_boolean_least Dem_EnvIsTriggerSet(Dem_TriggerType trigger, Dem_TriggerType trigger2test)
{
	return Dem_EnvIsAnyTriggerSet(trigger & trigger2test);
}

DEM_INLINE Dem_TriggerType Dem_GetSmallerTrigger(Dem_TriggerType trigger)
{
    if ((trigger & DEM_TRIGGER_ON_TEST_FAILED) == DEM_TRIGGER_ON_TEST_FAILED )
    {
        return DEM_TRIGGER_ON_FDC_THRESHOLD;
    }
    else if((trigger & DEM_TRIGGER_ON_PENDING) == DEM_TRIGGER_ON_PENDING )
    {
        return (DEM_TRIGGER_ON_FDC_THRESHOLD | DEM_TRIGGER_ON_TEST_FAILED);
    }
    else if((trigger & DEM_TRIGGER_ON_CONFIRMED) == DEM_TRIGGER_ON_CONFIRMED )
    {
        return (DEM_TRIGGER_ON_FDC_THRESHOLD | DEM_TRIGGER_ON_TEST_FAILED | DEM_TRIGGER_ON_PENDING);
    }
    else
    {
        return DEM_TRIGGER_NONE;
    }

}

#endif /* DEM_ENVTRIGGER_H */

