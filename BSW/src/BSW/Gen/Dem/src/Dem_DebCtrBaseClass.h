

#ifndef DEM_DEBCTRBASECLASS_H
#define DEM_DEBCTRBASECLASS_H

#include "Dem_Types.h"
#include "Dem_Deb.h"
#include "Dem_Cfg_Deb.h"
#include "Dem_DebSharing.h"


#if(DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON)

typedef struct
{
#if(DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN == DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_ON)
	boolean isJumpDownEnabled;
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP == DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_ON)
	boolean isJumpUpEnabled;
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD == DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_ON)
	sint16 passedThreshold;
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD == DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_ON)
	sint16 failedThreshold;
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE == DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_ON)
    sint16 jumpDownValue;
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE == DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_ON)
	sint16 jumpUpValue;
#endif

#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
    sint16 FDCThreshold;
#endif

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
    sint16 SuspiciousThreshold;
#endif

	sint16 stepUp;
	sint16 stepDown;
} Dem_DebCounterBaseClass_ParamSet;

#if(DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD == DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_ON)
#define DEM_DEB_MAXLIMIT(X)          (X),
#else
#define DEM_DEB_MAXLIMIT(X)
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD == DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_ON)
#define DEM_DEB_MINLIMIT(X)          (X),
#else
#define DEM_DEB_MINLIMIT(X)
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE == DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_ON)
#define DEM_DEB_JUPVALUE(X)         (X),
#else
#define DEM_DEB_JUPVALUE(X)
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE == DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_ON)
#define DEM_DEB_JDOWNVALUE(X)          (X),
#else
#define DEM_DEB_JDOWNVALUE(X)
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN == DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_ON)
#define DEM_DEB_ISJDOWN(X)          (X),
#else
#define DEM_DEB_ISJDOWN(X)
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP == DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_ON)
#define DEM_DEB_ISJUMPUP(X)          (X),
#else
#define DEM_DEB_ISJUMPUP(X)
#endif

#if((DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD == DEM_CFG_SUPPORTEVENTMEMORYENTRY_ONFDCTHRESHOLD_ON)||\
    (DEM_CFG_SUPPORT_EVENT_FDCTHRESHOLDREACHED))
#define DEM_DEB_FDCTHRESHOLD(X)          (X),
#else
#define DEM_DEB_FDCTHRESHOLD(X)
#endif

#if(DEM_CFG_SUSPICIOUS_SUPPORT)
#define DEM_DEB_SUSPICIOUSTHRESHOLD(X)          (X),
#else
#define DEM_DEB_SUSPICIOUSTHRESHOLD(X)
#endif

#define DEM_DEBCOUNTERBASECLASS_INIT(ISJDOWN,	\
		ISJUP,                  				\
		MINLIMIT, 	\
		MAXLIMIT,                          		\
		JDOWN,                          		\
		JUP,									\
        FDCTHRESHOLD,                           \
        SUSPICIOUSTHRESHOLD,                    \
		STEPUP,									\
		STEPDOWN )                              \
	{                                       	\
		DEM_DEB_ISJDOWN(ISJDOWN)         		\
		DEM_DEB_ISJUMPUP(ISJUP)        			\
		DEM_DEB_MINLIMIT(MINLIMIT)          	\
		DEM_DEB_MAXLIMIT(MAXLIMIT)          	\
		DEM_DEB_JDOWNVALUE(JDOWN) 				\
		DEM_DEB_JUPVALUE(JUP) 					\
        DEM_DEB_FDCTHRESHOLD(FDCTHRESHOLD)      \
        DEM_DEB_SUSPICIOUSTHRESHOLD(SUSPICIOUSTHRESHOLD)                   \
		(STEPUP),              					\
		(STEPDOWN)                          	\
	}											\

/*** FUNCTIONS ****************************************************************/


/*-- FAILED THRESHOLD -------------------------------------------------------------*/

DEM_INLINE sint16 Dem_getDebCtrBaseClassFailedThreshold (const void* paramSet, uint16 paramIndex)
{
#if(DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD == DEM_CFG_DEBCOUNTERBASECLASS_MAXTHRESHOLD_ON)
   return ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].failedThreshold;
#else
   DEM_UNUSED_PARAM(paramSet);
   DEM_UNUSED_PARAM(paramIndex);
   return DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MAXLIMIT;
#endif
}

/*-- PASSED THRESHOLD -------------------------------------------------------------*/

DEM_INLINE sint16 Dem_getDebCtrBaseClassPassedThreshold (const void* paramSet, uint16 paramIndex)
{
#if(DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD == DEM_CFG_DEBCOUNTERBASECLASS_MINTHRESHOLD_ON)
   return ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].passedThreshold;
#else
   DEM_UNUSED_PARAM(paramSet);
   DEM_UNUSED_PARAM(paramIndex);
   return DEM_CFG_DEFAULT_DEBCOUNTERCLASS_MINLIMIT;
#endif
}

/*-- JUMPUP VALUE -------------------------------------------------------------*/

DEM_INLINE sint16 Dem_getDebCtrBaseClassJumpUpValue (const void* paramSet, uint16 paramIndex)
{
#if(DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE == DEM_CFG_DEBCOUNTERBASECLASS_JUMPUPVALUE_ON)
   return ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].jumpUpValue;
#else
   DEM_UNUSED_PARAM(paramSet);
   DEM_UNUSED_PARAM(paramIndex);
   return DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_VALUE;
#endif
}

/*-- JUMPDOWN VALUE -------------------------------------------------------------*/

DEM_INLINE sint16 Dem_getDebCtrBaseClassJumpDownValue (const void* paramSet, uint16 paramIndex)
{
#if(DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE == DEM_CFG_DEBCOUNTERBASECLASS_JUMPDOWNVALUE_ON)
   return ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].jumpDownValue;
#else
   DEM_UNUSED_PARAM(paramSet);
   DEM_UNUSED_PARAM(paramIndex);
   return DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_VALUE;
#endif
}

/*-- IS JUMPDOWN -------------------------------------------------------------*/

DEM_INLINE boolean Dem_getDebCtrBaseClassIsJumpDown (const void* paramSet, uint16 paramIndex)
{
#if(DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN == DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPDOWN_ON)
   return ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].isJumpDownEnabled;
#else
   DEM_UNUSED_PARAM(paramSet);
   DEM_UNUSED_PARAM(paramIndex);
   return DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPDOWN_ENABLED;
#endif
}

/*-- IS JUMPUP -------------------------------------------------------------*/

DEM_INLINE boolean Dem_getDebCtrBaseClassIsJumpUp (const void* paramSet, uint16 paramIndex)
{
#if(DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP == DEM_CFG_DEBCOUNTERBASECLASS_ISJUMPUP_ON)
   return ((const Dem_DebCounterBaseClass_ParamSet*) paramSet)[paramIndex].isJumpUpEnabled;
#else
   DEM_UNUSED_PARAM(paramSet);
   DEM_UNUSED_PARAM(paramIndex);
   return DEM_CFG_DEFAULT_DEBCOUNTERCLASS_JUMPUP_ENABLED;
#endif
}


#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
void        Dem_DebCounterBaseClass_GetLimits (const void* paramSet, uint16 paramIndex, sint16_least* MinThreshold, sint16_least* MaxThreshold);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif

#if(DEM_CFG_DEBCOUNTERBASECLASS == DEM_CFG_DEBCOUNTERBASECLASS_ON)
#define DEM_START_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
/* Dem_DebCounterBaseClass_Filter() function used by ARcounterBase and CounterBaseClass debouncing method */
uint8_least Dem_DebCounterBaseClass_Filter (Dem_EventIdType EventId, Dem_EventStatusType* status, const void* paramSet, uint16 paramIndex DEM_DEB_LOCAL_CALC_PARAMS);
#define DEM_STOP_SEC_ROM_CODE
#include "Dem_Cfg_MemMap.h"
#endif

#endif


