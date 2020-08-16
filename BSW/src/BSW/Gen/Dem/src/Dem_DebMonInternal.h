

#ifndef DEM_DEBMONINTERNAL_H
#define DEM_DEBMONINTERNAL_H


#include "Dem_Types.h"


typedef Std_ReturnType(*Dem_GetFaultDetectionCounterOfIntDebMonitors)(sint8 * faultDetCtr);


typedef struct
{
  /* Pointer to DemCallBackGetFaultDetectionCounter Function */
    Dem_GetFaultDetectionCounterOfIntDebMonitors funcPointer_GetFDC;
}Dem_DebounceMonitorInternal;



#endif

