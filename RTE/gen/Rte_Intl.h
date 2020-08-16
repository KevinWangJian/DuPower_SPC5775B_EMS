/** @file         Rte_Intl.h
  *
  * @brief        RTE internal header file
  *
  * @copyright    Copyright 2007-2008 ETAS Engineering Tools Application and Services Ltd.
  *               Copyright 2008-2015 ETAS GmbH.
  *
  * @note         PLATFORM DEPENDENT [yes/no]: no
  *
  * @note         TO BE CHANGED BY USER [yes/no]: no
  *
  * Template:     Id: Rte_Intl_h.template 54608 2016-06-01 16:39:45Z ren1yok
  */

#ifndef RTE_INTL_H
#define RTE_INTL_H

#include "Rte.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "Rte_Const.h" /* Must be included before os.h */
#include <Os.h>

/*---------------------------------------------------------------------------*/
/* OS abstraction layer */

/* [$Satisfies $SWS 2250] RTE limited to AUTOSAR OS and COM APIs
 * Note that OS-vendor-specific extensions may be used but only when protected
 * with pre-processor guards on the appropriate OSENV_<name> symbol.
 */
/* [$Satisfies $SWS40 7519] SchM limited to AUTOSAR OS APIs
 * Note that OS-vendor-specific extensions may be used but only when protected
 * with pre-processor guards on the appropriate OSENV_<name> symbol.
 */

/* OS Tasks */

#if defined(OSENV_RTAOSEK) || defined(OSENV_ERCOSEK) || defined(RTE_TASKTYPE_IS_GLOBALCONST)
 #ifndef RTE_TASKREFTYPE
 #define RTE_TASKREFTYPE                P2CONST(TaskType, AUTOMATIC, RTE_OS_CDATA)
 #endif /* RTE_TASKREFTYPE */

 #ifndef RTE_TASK_FROM_REF
 #define RTE_TASK_FROM_REF(ref)         (*(ref))
 #endif /* RTE_TASK_FROM_REF */

 #ifndef RTE_REF_FROM_TASK
 #define RTE_REF_FROM_TASK(t)           (&(t))
 #endif /* RTE_TASK_FROM_REF */

 #define RTE_TASK_REF_NO_TASK           (0)

#else /* task type global const */
 #ifndef RTE_TASKREFTYPE
 #define RTE_TASKREFTYPE                TaskType
 #endif /* RTE_TASKREFTYPE */

 #define RTE_TASK_FROM_REF(ref)         (ref)
 #define RTE_REF_FROM_TASK(ref)         (ref)

 #ifndef RTE_TASK_REF_NO_TASK
 /* Warning: We use 0 here under the assumption that this is an invalid TaskType.
  * This is true for RTAOS but may not be true for other operating systems. */
 #define RTE_TASK_REF_NO_TASK           (0)
 #endif /* RTE_TASK_REF_NO_TASK */

#endif /* task type global const */

/* OS Events */

#if defined(OSENV_RTAOSEK) || defined(OSENV_ERCOSEK) || defined(RTE_EVENTTYPE_IS_GLOBALCONST)
 #ifndef RTE_EVENTREFTYPE
 #define RTE_EVENTREFTYPE                P2CONST(EventMaskType, AUTOMATIC, RTE_OS_CDATA)
 #endif /* RTE_EVENTREFTYPE */

 #ifndef RTE_EVENT_FROM_REF
 #define RTE_EVENT_FROM_REF(ref)         (*(ref))
 #endif /* RTE_EVENT_FROM_REF */

 #ifndef RTE_REF_FROM_EVENT
 #define RTE_REF_FROM_EVENT(t)           (&(t))
 #endif /* RTE_EVENT_FROM_REF */
#else /* event type global const */
 #ifndef RTE_EVENTREFTYPE
 #define RTE_EVENTREFTYPE                EventMaskType
 #endif /* RTE_EVENTREFTYPE */

 #define RTE_EVENT_FROM_REF(ref)         (ref)
 #define RTE_REF_FROM_EVENT(ref)         (ref)
#endif /* event type global const */

/* OS Alarms */
#define RTE_START_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(Rte_AlarmRefType, RTE_CONST) Rte_TimeoutAlarms[];
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

#if defined(OSENV_RTAOSEK) || defined(OSENV_ERCOSEK) || defined(RTE_ALARMTYPE_IS_GLOBALCONST)
 #ifndef RTE_ALARM_FROM_REF
 #define RTE_ALARM_FROM_REF(ref)        (*((P2CONST(AlarmType,AUTOMATIC,RTE_OS_CDATA))ref))
 #endif /* RTE_ALARM_FROM_REF */

 #ifndef RTE_REF_FROM_ALARM
 #define RTE_REF_FROM_ALARM(a)          (Rte_AlarmRefType)(&(a))
 #endif /* RTE_ALARM_FROM_REF */

 #ifndef RTE_NULL_ALARM_REF
 #define RTE_NULL_ALARM_REF             ((Rte_AlarmRefType)0)
 #endif /* RTE_NULL_ALARM_REF */

#else /* alarm type global const */
 #ifndef RTE_ALARM_FROM_REF
 #define RTE_ALARM_FROM_REF(ref)        ((AlarmType)ref)
 #endif /* RTE_ALARM_FROM_REF */

 #ifndef RTE_REF_FROM_ALARM
 #define RTE_REF_FROM_ALARM(a)          ((Rte_AlarmRefType)a)
 #endif /* RTE_REF_FROM_ALARM */

 #ifndef RTE_NULL_ALARM_REF
 /* Warning: We use -1 here under the assumption that AlarmType values are
  * indicies into an array and hence no alarm ever has value -1. This is true
  * for RTAOS 3.0 but may not be true for other operating systems. */
 #define RTE_NULL_ALARM_REF             ((Rte_AlarmRefType)-1)
 #endif /* RTE_NULL_ALARM_REF */

#endif /* alarm type global const */

#ifndef RTE_ALARM_FROM_INDEX
#define RTE_ALARM_FROM_INDEX(idx)          ( RTE_ALARM_FROM_REF( Rte_TimeoutAlarms[idx] ) )
#endif /* RTE_ALARM_FROM_INDEX */

#if defined(OSENV_ERCOSEK)
 #ifndef RTE_MS_TO_TICKS
 #define RTE_MS_TO_TICKS(X) ((TickType)MILLISECONDS_TO_TICKS(X))
 #endif
#else
 #ifndef RTE_MS_TO_TICKS
 #define RTE_MS_TO_TICKS(X) ((TickType)(X))
 #endif
#endif

/* OS Resources */

#if defined(OSENV_RTAOSEK) || defined(OSENV_ERCOSEK) || defined(RTE_RESOURCETYPE_IS_GLOBALCONST)
 #ifndef RTE_RESOURCE_FROM_REF
 #define RTE_RESOURCE_FROM_REF(ref)     (*((P2CONST(ResourceType,AUTOMATIC,RTE_OS_CDATA))ref))
 #endif /* RTE_RESOURCE_FROM_REF */

 #ifndef RTE_REF_FROM_RESOURCE
 #define RTE_REF_FROM_RESOURCE(r)       (Rte_ResourceRefType)(&(r))
 #endif /* RTE_RESOURCE_FROM_REF */

# ifndef RTE_NULL_RESOURCE_REF
#  define RTE_NULL_RESOURCE_REF         ((Rte_ResourceRefType)0)
# endif /* RTE_NULL_RESOURCE_REF */

#else /* resource type global const */
 #ifndef RTE_RESOURCE_FROM_REF
 #define RTE_RESOURCE_FROM_REF(ref)     ((ResourceType)ref)
 #endif /* RTE_RESOURCE_FROM_REF */

 #ifndef RTE_REF_FROM_RESOURCE
 #define RTE_REF_FROM_RESOURCE(r)       ((Rte_ResourceRefType)r)
 #endif /* RTE_RESOURCE_FROM_REF */

# ifndef RTE_NULL_RESOURCE_REF
   /* Warning: We use -1 here under the assumption that ResourceType values are
    * indicies into an array and hence no resource ever has value -1. */
#  define RTE_NULL_RESOURCE_REF         ((Rte_ResourceRefType)(-1))
# endif /* RTE_NULL_RESOURCE_REF */
#endif /* resource type global const */

typedef RTE_TASKREFTYPE        Rte_TaskRefType;
typedef RTE_EVENTREFTYPE       Rte_EventRefType;
typedef uint32                 Rte_EventType;
typedef uint8                  Rte_NrSetEvents;

/*---------------------------------------------------------------------------*/
/* RTE concurrency control */

#if defined(RTE_OSAPI_OSEK) || defined(RTE_OSAPI_AUTOSAR_R10) || defined(RTE_OSAPI_ERCOSEK) || defined(RTE_OSAPI_AUTOSAR_R30) || defined(RTE_OSAPI_AUTOSAR_R40)

#ifndef RTE_RESOURCE_DEFINED
/* [$Satisfies $SRD 97812] RTE_RESOURCE used by master core in a multi-core system */
DeclareResource(RTE_RESOURCE);
/* [$Satisfies $SRD 97813] RTE_RESOURCE_CORE<n> used by slave core with core ID <n> in a multi-core system */
#define RTE_RESOURCE_DEFINED
#endif


/* [$Satisfies $rte_swaddr 097] */
#define RTE_START_SEC_VAR_CLEARED_16
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern VAR(uint16, RTE_DATA) Rte_ResourceCount;
#define RTE_STOP_SEC_VAR_CLEARED_16
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */


#ifndef Rte_GetResource
#define Rte_GetResource() { if ( !Rte_ResourceCount ) { (void)GetResource(RTE_RESOURCE); } /* resource locked */ ++Rte_ResourceCount; }
#endif
#ifndef Rte_ReleaseResource
#define Rte_ReleaseResource() { if ( 0u == --Rte_ResourceCount ) { (void)ReleaseResource(RTE_RESOURCE); } }
#endif


#ifndef Rte_SuspendOSInterrupts
#define Rte_SuspendOSInterrupts()          SuspendOSInterrupts()
#endif

#ifndef Rte_ResumeOSInterrupts
#define Rte_ResumeOSInterrupts()           ResumeOSInterrupts()
#endif
#else
#error Undefined OS API
#endif

#ifndef Rte_SuspendAllInterrupts
#define Rte_SuspendAllInterrupts()         SuspendAllInterrupts()
#endif

#ifndef Rte_ResumeAllInterrupts
#define Rte_ResumeAllInterrupts()          ResumeAllInterrupts()
#endif

/*---------------------------------------------------------------------------*/
/* Activation of runnable entity */

typedef uint8 Rte_REActCounterType;
typedef P2VAR(Rte_REActCounterType, AUTOMATIC, RTE_DATA) Rte_REActCounterRefType;

typedef struct {
   Rte_TaskRefType         task;
   Rte_REActCounterRefType acnt;
} Rte_REContainerType;

typedef P2CONST(Rte_REContainerType, AUTOMATIC, RTE_CONST) Rte_REContainerRefType;

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern FUNC(Std_ReturnType, RTE_CODE) Rte_ActivateRE(Rte_REContainerRefType c);
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

#if defined(RTE_OSAPI_OSEK) || defined(RTE_OSAPI_AUTOSAR_R10) || defined(RTE_OSAPI_AUTOSAR_R30) || defined(RTE_OSAPI_AUTOSAR_R40)
typedef struct
{
   Rte_AlarmRefType        osAlarm;
   TickType                increment;
   TickType                period;
} Rte_AlarmTable;
#endif /* defined(RTE_OSAPI_OSEK) || defined(RTE_OSAPI_AUTOSAR_R10) || defined(RTE_OSAPI_AUTOSAR_R30) || defined(RTE_OSAPI_AUTOSAR_R40)*/

typedef uint16 Rte_MSICounterType;
typedef P2VAR(Rte_MSICounterType, AUTOMATIC, RTE_DATA) Rte_MSICounterRefType;

typedef boolean Rte_MSIPendingFlagType;
typedef P2VAR(Rte_MSIPendingFlagType, AUTOMATIC, RTE_DATA) Rte_MSIPendingFlagRefType;

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern FUNC(boolean, RTE_CODE) Rte_MSITest(Rte_MSICounterType,
                                              Rte_MSIPendingFlagRefType,
                                              Rte_MSICounterType);
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

typedef struct
{
   Rte_MSICounterRefType      counter;
   boolean                    incCounter;
   Rte_MSIPendingFlagRefType  pending;
   Rte_TaskRefType            osTask;
   Rte_REActCounterRefType    acnt;
   Rte_EventRefType           osEvent;
   Rte_MSICounterType         MSIInit;
} Rte_MSITableEntry;

typedef P2CONST(Rte_MSITableEntry, AUTOMATIC, RTE_CONST) Rte_MSITableEntryRef;

/*---------------------------------------------------------------------------*/
/* Wait with timeout */

typedef uint8  Rte_TaskArrayIndex;
typedef uint8  Rte_NrWaitingTasks;

typedef struct {
   uint8              pending;
   Rte_NrWaitingTasks count;            /* the number of tasks waiting for this datum */
   Rte_TaskArrayIndex firstWaitingTask; /* the index of the task that first started waiting for this datum */
} Rte_WaitableDatum;

typedef struct {
   Rte_TaskRefType                                 task;
   Rte_AlarmIndexType                              alarm;
   P2VAR(Rte_EventType, AUTOMATIC, RTE_DATA) waitingEv;
} Rte_TaskInfo;

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern FUNC(Std_ReturnType, RTE_CODE) Rte_WaitWithTimeout(P2VAR(Rte_WaitableDatum, AUTOMATIC, RTE_DATA) datum,
                                                             Rte_EventType event,
                                                             const TickType timeout);

extern FUNC(Std_ReturnType, RTE_CODE) Rte_SetEvent(P2VAR(Rte_WaitableDatum, AUTOMATIC, RTE_DATA) datum,
                                                      Rte_EventType event);

extern FUNC(void, RTE_CODE) Rte_DecrementWaitingCount( P2VAR(Rte_WaitableDatum, AUTOMATIC, RTE_DATA) datum,
                                                          Rte_TaskArrayIndex idx,
                                                          Rte_EventType event );

extern FUNC(Rte_TaskArrayIndex, RTE_CODE) Rte_GetCurrentTaskIndex( P2VAR(TaskType, AUTOMATIC, RTE_DATA) taskRef );
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

/*---------------------------------------------------------------------------*/
/* Queues */

typedef struct {
   Rte_EventType                                    event_id;
   P2VAR(Rte_WaitableDatum, AUTOMATIC, RTE_DATA)    wd;
   TickType                                         timeout;
} Rte_WOWP_NotificationType;

typedef P2CONST(Rte_WOWP_NotificationType, AUTOMATIC, RTE_CONST) Rte_WOWP_NotificationRefType;

typedef Rte_REContainerType Rte_ARE_NotificationType;

typedef P2CONST(Rte_ARE_NotificationType, AUTOMATIC, RTE_CONST) Rte_ARE_NotificationRefType;

typedef struct Rte_QDRAType {
   Rte_QCmnType                                   cmn;
   /* Nothing else necessary for DRA */
} Rte_QDRAType;

typedef struct Rte_QTaskType {
   Rte_QCmnType                                   cmn;
   Rte_TaskRefType                                task;
} Rte_QTaskType;

typedef P2CONST(Rte_QTaskType, AUTOMATIC, RTE_CONST) Rte_QRefTaskType;

typedef struct Rte_QREType {
   Rte_QCmnType                                   cmn;
   Rte_REContainerRefType                         re;
} Rte_QREType;

typedef P2CONST(Rte_QREType, AUTOMATIC, RTE_CONST) Rte_QRefREType;

typedef struct Rte_QWWPType {
   Rte_QCmnType                                   cmn;
   Rte_WOWP_NotificationRefType                   wwp;
} Rte_QWWPType;

typedef P2CONST(Rte_QWWPType, AUTOMATIC, RTE_CONST) Rte_QRefWWPType;

typedef struct Rte_QEvType {
   Rte_QCmnType                                   cmn;
   Rte_TaskRefType                                task;
   Rte_EventRefType                               mask;
   Rte_REActCounterRefType                        acnt;
} Rte_QEvType;

typedef P2CONST(Rte_QEvType, AUTOMATIC, RTE_CONST) Rte_QRefEvType;

typedef struct Rte_QMSIType {
   Rte_QCmnType                                   cmn;
   Rte_TaskRefType                                task;
   Rte_EventRefType                               mask;
   Rte_REActCounterRefType                        acnt;
   Rte_MSICounterRefType                          msiCounter;
   Rte_MSIPendingFlagRefType                      msiPending;
   uint16                                         msiLimit;
} Rte_QMSIType;

typedef P2CONST(Rte_QMSIType, AUTOMATIC, RTE_CONST) Rte_QRefMSIType;

typedef P2VAR(void, AUTOMATIC, RTE_DATA)   Rte_VarDataPtr;
typedef P2CONST(void, AUTOMATIC, RTE_DATA) Rte_ConstDataPtr;

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern FUNC(Std_ReturnType, RTE_CODE) Rte_WriteQueue(Rte_QCmnRefType q,
                                                        Rte_ConstDataPtr data);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_ReadQueue(Rte_QCmnRefType q,
                                                       Rte_VarDataPtr  data);
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

/*---------------------------------------------------------------------------*/
/* Modes and Mode switches */

typedef P2FUNC(boolean, RTE_CODE, Rte_MddGuard)(void);

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */


#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

/*---------------------------------------------------------------------------*/
/* Declaration of variables/constants emitted by configuration tool */

#if defined(RTE_WOWP_EVENTS)
#if (RTE_WOWP_EVENTS > 0 )
#define RTE_START_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(Rte_TaskInfo, RTE_CONST) Rte_Tasks[];
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
#endif /* ( RTE_WOWP_EVENTS > 0 ) */
#endif /* defined(RTE_WOWP_EVENTS) */

#if defined(RTE_NUM_INIT_RES)
#if ( RTE_NUM_INIT_RES > 0 )
#define RTE_START_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(Rte_REActList, RTE_CONST) Rte_InitREs[RTE_NUM_INIT_RES];
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
#endif /* ( RTE_NUM_INIT_RES > 0 ) */
#endif /* defined(RTE_NUM_INIT_RES) */

#if defined(RTE_OSAPI_OSEK) || defined(RTE_OSAPI_AUTOSAR_R10) || defined(RTE_OSAPI_AUTOSAR_R30) || defined(RTE_OSAPI_AUTOSAR_R40)
#if defined(RTE_NUM_ALARMS)
#define RTE_START_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(Rte_AlarmTable, RTE_CONST) Rte_Alarms[RTE_NUM_ALARMS];
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
#endif /* defined(RTE_NUM_ALARMS) */
#endif /* defined(RTE_OSAPI_OSEK) || defined(RTE_OSAPI_AUTOSAR_R10) || defined(RTE_OSAPI_AUTOSAR_R30) || defined(RTE_OSAPI_AUTOSAR_R40) */

#if defined(RTE_MODESWITCHCONTROL_SIZE)
#define RTE_START_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern CONST(Rte_ModeSwitchTable, RTE_CONST) Rte_ModeSwitchControl[RTE_MODESWITCHCONTROL_SIZE];
#define RTE_STOP_SEC_CONST_UNSPECIFIED
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
#endif /* defined(RTE_MODESWITCHCONTROL_SIZE) */

/*---------------------------------------------------------------------------*/
/* Other internal global variables */

/* [$Satisfies $rte_swaddr 097] */
#define RTE_START_SEC_VAR_CLEARED_BOOLEAN
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
extern VAR(boolean, RTE_DATA) Rte_Initialized;
extern VAR(boolean, RTE_DATA) Rte_Initializing;
extern VAR(boolean, RTE_DATA) SchM_Initialized;
#define RTE_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RTE_INTL_H */

