

#ifndef DEM_ARRAY_H
#define DEM_ARRAY_H


#include "Dem_Cfg_Main.h"
#include "Dem_Types.h"


/* USAGE examples:

Array definitions with automatic bound-check during Simulation and Testsuite run.
Arrays have to be declared and defined as the following examples show:

in header:
==========
DEM_DECLARE_ARRAY(Monitoring_State, Dem_AllEventsState, C_NUMBER_OF_EVENTS+1);
DEM_DECLARE_ARRAY(const Monitoring, Dem_AllEventsParam, C_NUMBER_OF_EVENTS+1);

in source:
==========
DEM_DEFINE_ARRAY(Monitoring_State, Dem_AllEventsState, C_NUMBER_OF_EVENTS+1);
DEM_DEFINE_ARRAY(const Monitoring, Dem_AllEventsParam, C_NUMBER_OF_EVENTS+1) = {
    DEM_EVTS_INIT (C_SID_INVALID,                  0,      DEM_SENSITIVITY_BASE, DEM_SENSITIVITY_BASE, 0,         0,           RECOV,   DCYC,      NOWIR,    RESET_FL, NO_GC,     Dem_EventCategoryExternalFault,          (0),                                         (0))
   ,DEM_EVTS_INIT (C_SID_N01_N,                    1,      DEM_SENSITIVITY_BASE, DEM_SENSITIVITY_BASE, 0,         0,           RECOV,   DCYC,      NOWIR,    RESET_FL, NO_GC,     Dem_EventCategoryExternalFault,          SITUATIONFILTER_Monitoring_01,               ENABLECONDITION_Monitoring_01)
   ,DEM_EVTS_INIT (C_SID_N01_N,                    1,      DEM_SENSITIVITY_BASE, DEM_SENSITIVITY_BASE, 0,         0,           RECOV,   NODC,      NOWIR,    NO_RESET, NO_GC,     Dem_EventCategoryExternalFault,          SITUATIONFILTER_Monitoring_09,               ENABLECONDITION_Monitoring_09)
}

*/


#if (   (DEM_CFG_BUILDTARGET == DEM_CFG_BUILDTARGET_ECU) \
     || (defined DEM_TEST_FORCE_PLAIN_ARRAY))


/* MR12 RULE 20.7 VIOLATION : Macro parameter may not be enclosed in (). */
   #define DEM_ARRAY_DECLARE(TYPE,NAME,SIZE)                 extern TYPE NAME[SIZE]
/* MR12 RULE 20.7 VIOLATION : Macro parameter may not be enclosed in (). */
   #define DEM_ARRAY_DECLARE_CONST(TYPE,NAME,SIZE)           extern const TYPE NAME[SIZE]

/* MR12 RULE 20.7 VIOLATION : Macro parameter may not be enclosed in (). */
   #define DEM_ARRAY_DEFINE(TYPE,NAME,SIZE)                  TYPE NAME[SIZE]

/* MR12 RULE 20.7 VIOLATION : Macro parameter may not be enclosed in (). */
   #define DEM_ARRAY_DEFINE_CONST(TYPE,NAME,SIZE,INITVALUE)  const TYPE NAME[SIZE] = INITVALUE

/* MR12 RULE 20.7 VIOLATION : Macro parameter may not be enclosed in (). */
   #define DEM_ARRAY_FUNCPARAM(TYPE,NAME)                    TYPE NAME[]
/* MR12 RULE 20.7 VIOLATION : Macro parameter may not be enclosed in (). */
   #define DEM_ARRAY_CONSTFUNCPARAM(TYPE,NAME)               const TYPE NAME[]

   #define DEM_SIZEOF_VAR(x)                sizeof(x)
   #define DEM_SIZEOF_TYPE(x)               sizeof(x)


#else

#include "DemTest_Array.h"

#endif


#endif


