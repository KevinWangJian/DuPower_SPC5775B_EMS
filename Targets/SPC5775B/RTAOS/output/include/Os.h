/*
 * This is Os.h, auto-generated for:
 *   Project: RTAOS
 *   Target:  PPCe200WR
 *   Variant: MPC5777C
 *   Version: 5.1.14
 *   [$UKS 648]
 */
 
#ifndef OS_H
#define OS_H
/* -- Start expansion of <OsMinusConfig.h> -- */
/* File version information [BSW00402] */
#define OS_MODULE_ID (1U)
#define OS_VENDOR_ID (11U)
#define OS_AR_MAJOR_VERSION (4U)
#define OS_AR_MINOR_VERSION (2U)
#define OS_AR_PATCH_VERSION (2U)
#define OS_AR_RELEASE_MAJOR_VERSION (4U)
#define OS_AR_RELEASE_MINOR_VERSION (2U)
#define OS_AR_RELEASE_REVISION_VERSION (2U)
#define OS_SW_MAJOR_VERSION (5U)
#define OS_SW_MINOR_VERSION (5U)
#define OS_SW_PATCH_VERSION (8U)
#define OS_TARGET_PORT "PPCe200WR"
#define OS_TARGET_PORT_PPCe200WR
#define OS_TARGET_MAJOR_VERSION (5U)
#define OS_TARGET_MINOR_VERSION (1U)
#define OS_TARGET_PATCH_VERSION (14U)

#include <Std_Types.h>  /* [$UKS 649] : Includes Std_Types.h EHI 93361 */
#ifndef STD_TYPES_H
  #error "STD_TYPES_H is not defined. This should appear in Std_Types.h (AUTOSAR requirement STD014). Is Std_Types.h in the include path? (try --samples:[Includes]overwrite -ISamples\Includes)"
#endif
#ifndef OS_APPL_CODE
  #define OS_APPL_CODE /* Used prior to AUTOSAR 4 */
#endif
#ifndef OS_CALLOUT_CODE
  #define OS_CALLOUT_CODE OS_APPL_CODE  /* [$UKS 1325] [$UKS 1326] OS_CALLOUT_CODE should be defined in AUTOSAR R4.1, but may not be present in earlier versions */
#endif
#ifndef OS_VAR_CLEARED
  #define OS_VAR_CLEARED OS_VAR_POWER_ON_INIT /* OS_VAR_CLEARED is used for RTA-OS 5.4 */
#endif
#ifndef OS_VAR_NO_INIT
  #define OS_VAR_NO_INIT OS_VAR_NOINIT /* OS_VAR_NO_INIT is used in AUTOSAR 4.1 */
#endif
/* -- Start expansion of <OsTargetTypes.h> -- */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CAT1_ISR, OS_MAIN, OS_MBAR, OS_MSYNC, OS_MTMSR, OS_MFMSR, OS_ISYNC, OS_NOP, OS_MTSPR, OS_MFSPR, OS_SYSTRAP, OS_GETSP, OS_SETSP, OS_SET_EE, OS_CLEAR_EE, OS_REGISTER, OS_REGISTER_ADDR, OS_CLZ, OS_MTPMR, OS_MFPMR) */

#ifdef _lint
  extern uint32 dummy_lint_var;
  extern void OS_NOP(void);
  #define OS_MBAR() /* nil for lint */
  #define OS_MSYNC() /* nil for lint */
  #define OS_ISYNC() /* nil for lint */
  #define OS_MTMSR(value) /* nil for lint */
  #define OS_MFMSR() (dummy_lint_var) /* for lint */
  #define OS_MTSPR(spr, value) /* nil for lint */
  #define OS_MFSPR(spr) (dummy_lint_var) /* nil for lint */
  #define OS_SYSTRAP(value) (dummy_lint_var) /* for lint */
  #define OS_SET_EE()  /* nil for lint */
  #define OS_CLEAR_EE()  /* nil for lint */
  #define OS_GETSP() (dummy_lint_var) /* for lint */
  #define OS_SETSP(value) /* nil for lint */
  #define OS_CLZ(value) (dummy_lint_var) /* for lint */
  #define OS_MTPMR(pmr, value) /* nil for lint */
  #define OS_MFPMR(pmr) (dummy_lint_var) /* for lint */
#else
  extern void __nop(void) __attribute__((intrinsic_function(8, 0, "nop")));
  extern void __mbar(const unsigned int) __attribute__((intrinsic_function(7, 4, "mbar")));
  extern void __msync(void) __attribute__((intrinsic_function(8, 4, "msync")));
  extern void __isync(void) __attribute__((intrinsic_function(8, 4, "isync")));
  extern void __mtmsr(int) __attribute__((intrinsic_function(2091, 4, "mtmsr")));
  extern int __mfmsr(void) __attribute__((intrinsic_function(2083, 1, "mfmsr")));
  extern void __mtspr(const unsigned int,  int) __attribute__((intrinsic_function(2090, 0, "mtspr")));
  extern int __mfspr(const unsigned int) __attribute__((intrinsic_function(2016, 0, "mfspr")));
  extern void __wrteei(const unsigned int) __attribute__((intrinsic_function(7, 0, "wrteei")));
  extern int __cntlzw(int) __attribute__((intrinsic_pseudo(1, "cntlzw")));
  extern void __mtpmr(const unsigned int,  int) __attribute__((intrinsic_function(2090, 0, "mtpmr")));
  extern int __mfpmr(const unsigned int) __attribute__((intrinsic_function(2016, 0, "mfpmr")));
  #define OS_NOP() __asm volatile("nop")
  #define OS_MBAR() __mbar(0U)
  #define OS_MSYNC() __msync()
  #define OS_ISYNC() __isync()
  #define OS_MTMSR(value) __mtmsr(value)
  #define OS_MFMSR() (volatile uint32) __mfmsr()
  #define OS_MTSPR(spr, value) __mtspr(spr, value)
  #define OS_MFSPR(spr) __mfspr(spr)
  #define OS_SET_EE() __wrteei(1U)
  #define OS_CLEAR_EE() __wrteei(0U)
  #define OS_GETSP() Os_GetSP()
  #define OS_SETSP(value) Os_SetSP(value)
  #define OS_CLZ(value) __cntlzw(value)
  #define OS_MTPMR(pmr, value) __mtpmr(pmr, value)
  #define OS_MFPMR(pmr) __mfpmr(pmr)
  #define OS_SYSTRAP(value) Os_SysTrap(value)
#endif


#ifdef _lint
#define CAT1_ISR(x) void x(void)
#else
#define CAT1_ISR(x) __inline__ static void Os_inline_##x(OS_ARGS_##x); OS_HANDLERTYPE_##x void OS_ENTRY_##x(OS_ARGS_##x) {   uint32 prev_isr;   if (OS_SET_EE_##x) { OS_SET_EE(); }   prev_isr = OS_CAT1_TRACKER_##x;   OS_CAT1_TRACKER_##x = OS_CAT1_ID_##x;   Os_inline_##x(OS_ARG_##x);   OS_CAT1_TRACKER_##x = prev_isr;   if (OS_SET_EE_##x) { OS_CLEAR_EE(); } } __inline__ static void Os_inline_##x(OS_ARGS_##x) /* [$TgtCore 55] */
#endif /* _lint */

#ifdef _lint
  extern void * dummy_lint_reg(uint32 addr);
  #define OS_REGISTER(kind, addr) (*(kind *)dummy_lint_reg(addr))
  #define OS_REGISTER_ADDR(kind, addr) (&dummy_lint_var)
#else
  #define OS_REGISTER(kind, addr) (*(volatile kind *) addr)
  #define OS_REGISTER_ADDR(kind, addr) ((volatile kind *) addr)
#endif

#define OS_MAIN()   void main(void) /* [$TgtCore 56] */
#define OS_INTC_PSR_BASE OS_REGISTER(uint32, 0xFFF48040UL)
#define OS_INTC_PSR0     OS_REGISTER(uint8, 0xFFF48040UL)
#define OS_INTC_BCR     OS_REGISTER(uint32, 0xFFF48000UL)
#define OS_INTC_CPR     OS_REGISTER(Os_imaskType, 0xFFF48008UL)
#define OS_INTC_EOIR    OS_REGISTER(uint32, 0xFFF48018UL)
#define OS_INTC_IACKR   (*(volatile Os_imaskType  *) 0xFFF48010UL)
#define OS_INTC_HVEN    (0x101)
#define OS_INTC_SVEN    (0U)
#define OS_EE_BIT       (0x8000U)

/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE_LIB
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_CODE) Os_InitializeVectorTable(void);
extern uint32 Os_SysTrap(uint32 value);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE_LIB
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_STARTCORE_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(StatusType, OS_OS_CBK_STARTCORE_CODE) Os_Cbk_StartCore(uint16 CoreID);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_STARTCORE_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern VAR(uint32, OS_VAR_NO_INIT) Os_RunningCat1ISR;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

/* -- End expansion of <OsTargetTypes.h> -- */
#ifndef OS_VOLATILE
  #define OS_VOLATILE volatile
#endif
typedef int Os_SetJmpType;
typedef uint32 Os_jump_buf[24];
extern Os_SetJmpType Os_setjmp(Os_jump_buf *env);
#ifdef _lint
extern void Os_longjmp(Os_jump_buf *env, Os_SetJmpType val);
#else
extern void __attribute__((noreturn)) Os_longjmp(Os_jump_buf *env, Os_SetJmpType val);
#endif /*_lint*/


#ifndef OS_CONST
//  #error "OS_CONST is not defined. This normally appears in Compiler_Cfg.h or Os_Compiler_Cfg.h"
#endif
#ifndef OS_CONST_FAST
  #define OS_CONST_FAST OS_CONST
#endif

#define OS_MEMMAP_DECLARATIONS (TRUE)
#define OS_MEMMAP_DEFINITIONS  (TRUE)

typedef unsigned long Os_ResourceCountType;
typedef uint32 Os_StackTraceType;
typedef uint32 Os_StackValueType;
typedef uint32 Os_StackSizeType;

#ifdef _lint
  extern volatile Os_StackValueType Os_GetSP(void);
  extern volatile void Os_SetSP(Os_StackValueType value);
#else
/* [$TargetWR 259] */
__asm volatile Os_StackValueType Os_GetSP(void)
{
.set noreorder
!"r3"
  mr  r3, r1
$$noadjust
.set reorder
}

/* [$TargetWR 259] */
__asm volatile void Os_SetSP(Os_StackValueType value)
{
.set noreorder
%reg value
!"r1"
  mr  r1, value
$$noadjust
.set reorder
}
#endif
typedef void (*Os_VoidVoidFunctionType)(void);
typedef Os_VoidVoidFunctionType Os_TaskEntryFunctionType; /* backwards compatible */
typedef Os_VoidVoidFunctionType Os_IsrEntryFunctionType; /* backwards compatible */

typedef enum {OS_BUDGET = 0U, OS_ECC_START, OS_ECC_RESUME, OS_ECC_WAIT} Os_StackOverrunType; /* [$UKS 1236] [$UKS 1228] [$UKS 1235] */

#define OS_NOAPPMODE ((AppModeType)0U)
#define OSDEFAULTAPPMODE ((AppModeType)1U)  /* [$UKS 381] [$UKS 383] */
#define OS_STANDARD_STATUS  /* [$UKS 7] [$UKS 760] */
#define OS_ORTI_BUILD
#define OS_SCALABILITY_CLASS_1 /* [$UKS 762] [$UKS 763] [$UKS 764] [$UKS 765] */

/* OSApplications */
typedef unsigned long ApplicationType; /* [$UKS 411] */
#define INVALID_OSAPPLICATION ((ApplicationType)0U)  /* [$UKS 413] */

typedef void (*Os_AppErrorHookFunctionType)(StatusType e); /* [$UKS 450] */
typedef uint32 Os_tmaskType; /* [$UKS 2047] */


/* Timing */
typedef unsigned int TickType; /* [$UKS 276] */
typedef signed int SignedTickType;
typedef P2VAR(TickType, TYPEDEF, OS_VAR) TickRefType; /* [$UKS 277] */
typedef uint32 PhysicalTimeType; /* [$UKS  842] */
typedef unsigned int Os_StopwatchTickType; /* [$UKS 535] */
typedef P2VAR(Os_StopwatchTickType, TYPEDEF, OS_VAR) Os_StopwatchTickRefType;
typedef signed int Os_TimeLimitType;

typedef enum {PRO_IGNORE = 0U, PRO_TERMINATETASKISR, PRO_TERMINATEAPPL, PRO_TERMINATEAPPL_RESTART, PRO_SHUTDOWN} ProtectionReturnType; /* [$UKS 589] [$UKS 590] [$UKS 591] */

typedef uint32 IdleModeType; /* [$UKS 1910] */
#define IDLE_NO_HALT ((IdleModeType)0U)
#define OS_CURRENT_IDLEMODE Os_CurrentIdleMode /* [$UKS 1914] */
typedef uint16 CoreIdType;  /* [$UKS 1608] */
typedef uint16 SpinlockIdType;  /* [$UKS 1605] */
#define INVALID_SPINLOCK ((SpinlockIdType)0) /* [$UKS 1606] */
#ifndef STATUSTYPEDEFINED
  #define STATUSTYPEDEFINED
  typedef unsigned char StatusType; /* [$UKS 468] */
  #define E_OK ((StatusType)0U)
#endif /* STATUSTYPEDEFINED */
#define E_OS_ACCESS ((StatusType)1U)
#define E_OS_CALLEVEL ((StatusType)2U)
#define E_OS_ID ((StatusType)3U)
#define E_OS_LIMIT ((StatusType)4U)
#define E_OS_NOFUNC ((StatusType)5U)
#define E_OS_RESOURCE ((StatusType)6U)
#define E_OS_STATE ((StatusType)7U)
#define E_OS_VALUE ((StatusType)8U)
#define E_OS_SERVICEID ((StatusType)9U)
#define E_OS_ILLEGAL_ADDRESS ((StatusType)10U)
#define E_OS_MISSINGEND ((StatusType)11U)
#define E_OS_DISABLEDINT ((StatusType)12U)
#define E_OS_STACKFAULT ((StatusType)13U)
#define E_OS_PROTECTION_MEMORY ((StatusType)14U)
#define E_OS_PROTECTION_TIME ((StatusType)15U)
#define E_OS_PROTECTION_ARRIVAL ((StatusType)16U)
#define E_OS_PROTECTION_LOCKED ((StatusType)17U)
#define E_OS_PROTECTION_EXCEPTION ((StatusType)18U)
#define E_OS_CORE ((StatusType)19U)
#define E_OS_SPINLOCK ((StatusType)20U)
#define E_OS_INTERFERENCE_DEADLOCK ((StatusType)21U)
#define E_OS_NESTING_DEADLOCK ((StatusType)22U)
#define E_OS_SYS_NO_RESTART ((StatusType)23U)
#define E_OS_SYS_RESTART ((StatusType)24U)
#define E_OS_SYS_OVERRUN ((StatusType)25U)
#define E_OS_XCORE_QFULL ((StatusType)26U)
typedef P2VAR(StatusType, TYPEDEF, OS_VAR) Os_StatusRefType;

/* AppModes */
typedef unsigned long AppModeType; /* [$UKS 382] */

/* Memory Partitioning */
typedef unsigned long AccessType;  /* [$UKS 594] */
#define OS_ACCESS_READ    (1U)
#define OS_ACCESS_WRITE   (2U)
#define OS_ACCESS_EXECUTE (4U)
#define OS_ACCESS_STACK   (8U)
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OSMEMORY_IS_READABLE, OSMEMORY_IS_WRITEABLE, OSMEMORY_IS_EXECUTABLE, OSMEMORY_IS_STACKSPACE) */
#define OSMEMORY_IS_READABLE(x)   (0U != ((x) & OS_ACCESS_READ))    /* [$UKS 597] */
#define OSMEMORY_IS_WRITEABLE(x)  (0U != ((x) & OS_ACCESS_WRITE))   /* [$UKS 598] */
#define OSMEMORY_IS_EXECUTABLE(x) (0U != ((x) & OS_ACCESS_EXECUTE)) /* [$UKS 599] */
#define OSMEMORY_IS_STACKSPACE(x) (0U != ((x) & OS_ACCESS_STACK))   /* [$UKS 600] */
typedef P2CONST(uint8, TYPEDEF, OS_VAR) MemoryStartAddressType; /* [$UKS 971] */
typedef unsigned int MemorySizeType; /* [$UKS 972] */

typedef enum {RESTART = 1U, NO_RESTART} RestartType;  /* [$UKS 414] */
typedef enum {APPLICATION_ACCESSIBLE = 0U, APPLICATION_RESTARTING, APPLICATION_TERMINATED} ApplicationStateType;  /* [$UKS 1314] */
typedef P2VAR(ApplicationStateType, TYPEDEF, OS_VAR) ApplicationStateRefType;  /* [$UKS 1315] */
typedef enum {ACCESS = 0U, NO_ACCESS} ObjectAccessType;  /* [$UKS 415] */
typedef enum {OBJECT_TASK = 0U, OBJECT_ISR, OBJECT_ALARM, OBJECT_RESOURCE, OBJECT_COUNTER, OBJECT_SCHEDULETABLE} ObjectTypeType;  /* [$UKS 416] */
typedef CONSTP2CONST(void, TYPEDEF, OS_VAR) Os_AnyType;

typedef unsigned long TrustedFunctionIndexType; /* [$UKS 969] */
typedef P2VAR(void, TYPEDEF, OS_VAR) TrustedFunctionParameterRefType; /* [$UKS 970] */
#define INVALID_FUNCTION ((TrustedFunctionIndexType)-1)
typedef void (*Os_FunctionEntryType)(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams);
typedef struct Os_TrustedFunctionType_s {
  Os_FunctionEntryType function;  /* [$UKS 1268] */
} Os_TrustedFunctionType;

typedef unsigned long Os_IdleType;
#define OS_CORE_CURRENT (255U) /* [$UKS 1869] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareEvent) */
#define DeclareEvent(x) /* [$UKS 143] */ /*lint -e(19) : DeclareEvent has no content */
typedef uint8 EventMaskType;  /* [$UKS 141] */
typedef P2VAR(EventMaskType, TYPEDEF, OS_VAR) EventMaskRefType; /* [$UKS 142] */


/* ISRs [$UKS 94] */
typedef uint32 Os_imaskType;

typedef struct Os_ISRType_s {
  Os_VoidVoidFunctionType entry_function;
  Os_imaskType imask;
} Os_ISRType;
typedef P2CONST(Os_ISRType, TYPEDEF, OS_VAR) ISRType;  /* [$UKS 107] */
#define INVALID_ISR ((ISRType)0)  /* [$UKS 108] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_ISRTYPE_TO_INDEX) */
#define OS_ISRTYPE_TO_INDEX(isrtype) (isrtype - &Os_const_isrs[0])
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_INDEX_TO_ISRTYPE) */
#define OS_INDEX_TO_ISRTYPE(index) ((ISRType)&Os_const_isrs[index])
typedef P2VAR(ISRType, TYPEDEF, OS_VAR) ISRRefType;

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, ISR, DeclareISR) */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, ISR) */
#define ISR(x) void Os_Entry_##x(void) /* [$UKS 106] [$UKS 98] */
#define DeclareISR(x) /* [$UKS  1185] */ /*lint -e(19) : DeclareISR has no content */
#define OS_IPL (15U)

/* Tasks */
typedef unsigned int Os_bitmask;
typedef Os_bitmask Os_pset0Type;
typedef union {
  Os_pset0Type p0;
} Os_psetType; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */

typedef union {
  Os_bitmask t0;
} Os_tpmaskType; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */
typedef unsigned long Os_ActivationCountType;

typedef struct Os_TaskDynType_s {
  VAR(Os_jump_buf, OS_VAR_NOINIT) terminate_jump_buf;
  Os_ActivationCountType activation_count;
} Os_TaskDynType;

typedef struct Os_TaskType_s {
  CONSTP2VAR(Os_TaskDynType, OS_VAR, OS_CONST) dynamic;
  Os_VoidVoidFunctionType entry_function;
  Os_psetType pset;
  Os_tpmaskType base_tpmask;
  Os_tpmaskType tpmask;
  Os_ActivationCountType activation_count;
} Os_TaskType;
typedef P2CONST(Os_TaskType, TYPEDEF, OS_VAR) TaskType;  /* [$UKS 55] */
#define INVALID_TASK  (TaskType)0 /* [$UKS 92] */
#define OS_INVALID_TPL (0xFFFFU)  /* [$UKS 2014] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_TASKTYPE_TO_INDEX) */
#define OS_TASKTYPE_TO_INDEX(tasktype) (tasktype - &Os_const_tasks0[0])
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_INDEX_TO_TASKTYPE) */
#define OS_INDEX_TO_TASKTYPE(index) ((TaskType)(Os_const_tasks[index]))
typedef P2VAR(TaskType, TYPEDEF, OS_VAR) TaskRefType; /* [$UKS 56] */
enum Os_TaskStateType {SUSPENDED = 0U, READY, WAITING, RUNNING};  /* [$UKS 43] [$UKS 47] */
typedef enum Os_TaskStateType TaskStateType;  /* [$UKS 57] */
typedef P2VAR(TaskStateType, TYPEDEF, OS_VAR) TaskStateRefType; /* [$UKS 58] */


/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, TASK, DeclareTask) */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, TASK) */
#define TASK(x) void Os_Entry_##x(void) /* [$UKS 50] */
#define DeclareTask(x) /* [$UKS 60] */ /*lint -e(19) : DeclareTask has no content */

/* Resources */
typedef struct Os_ResourceDynType_s {
  TaskType locker;  /* [$UKS 614] */
  union {
    Os_tpmaskType tpmask;
  } saved_priority; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */
} Os_ResourceDynType;
typedef struct Os_ResourceType_s {
  CONSTP2VAR(Os_ResourceDynType, OS_VAR, OS_CONST) dynamic;
  Os_tpmaskType tpmask;
} Os_ResourceType;
typedef P2CONST(Os_ResourceType, TYPEDEF, OS_CONST) ResourceType;  /* [$UKS 202] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareResource) */
#define DeclareResource(x) /* [$UKS 203] */ /*lint -e(19) : DeclareResource has no content */

/* Alarms */
typedef struct {
  TickType maxallowedvalue;
  TickType ticksperbase;
  TickType mincycle;
} AlarmBaseType;  /* [$UKS 278] */
typedef P2VAR(AlarmBaseType, TYPEDEF, OS_VAR) AlarmBaseRefType; /* [$UKS 279] */
typedef struct Os_AlarmDynType_s {
  boolean running;
  TickType match;
  TickType period;
} Os_AlarmDynType;
typedef struct Os_AlarmType_s {
  uint8 config;
} Os_AlarmType;
typedef unsigned long AlarmType;  /* [$UKS 280] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareAlarm, ALARMCALLBACK) */
#define DeclareAlarm(x) /* [$UKS 281] */ /*lint -e(19) : DeclareAlarm has no content */

typedef void (*Os_AlarmCallbackType)(void);
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, ALARMCALLBACK) */
#define ALARMCALLBACK(x) FUNC(void, OS_CODE) Os_Cbk_Alarm_##x(void) /* [$UKS 274] */

/* Counters */
typedef struct {
  boolean Running;
  boolean Pending;
  TickType Delay;
} Os_CounterStatusType;  /* [$UKS 249] */
typedef P2VAR(Os_CounterStatusType, TYPEDEF, OS_VAR) Os_CounterStatusRefType; /* [$UKS 250] */

typedef TickType (*Os_HwCounterNowType)(void);  /* [$UKS 260] */
typedef void (*Os_HwCounterSetType)(TickType Value);  /* [$UKS 261] */
typedef void (*Os_HwCounterStateType)(Os_CounterStatusRefType State); /* [$UKS 262] */
typedef void (*Os_HwCounterCancelType)(void); /* [$UKS 263] */
typedef StatusType (*Os_CounterIncrAdvType)(void);
typedef FUNC(void, OS_CODE) (*Os_CounterStartType)(Os_AnyType ctr, TickType requested, TickType relative, TickRefType match_value);

typedef struct Os_CounterDynType_s {
  union {
    struct s_swd { /* [$UKS 211] */
      TickType count;
    } sw;
  } type_dependent; /* [MISRA 2012 Rule 19.2] */ /*lint !e9018 */
} Os_CounterDynType;
typedef struct Os_CounterType_s {
  CONSTP2VAR(Os_CounterDynType, OS_VAR, OS_CONST) dynamic;
  Os_CounterIncrAdvType advincr;
  AlarmBaseType base;
} Os_CounterType;
typedef P2CONST(Os_CounterType, TYPEDEF, OS_CONST) CounterType;  /* [$UKS 223] */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareCounter) */
#define DeclareCounter(x) /* [$UKS  1183] */ /*lint -e(19) : DeclareCounter has no content */

/* ScheduleTables */
enum Os_ScheduleTableStatusType {SCHEDULETABLE_STOPPED = 0U, SCHEDULETABLE_NEXT, SCHEDULETABLE_WAITING, SCHEDULETABLE_RUNNING, SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS};
typedef enum Os_ScheduleTableStatusType ScheduleTableStatusType; /* [$UKS 327] */
typedef P2VAR(ScheduleTableStatusType, TYPEDEF, OS_VAR) ScheduleTableStatusRefType;  /* [$UKS 328] */
typedef enum {OS_SYNC_NONE, OS_SYNC_IMPLICIT, OS_SYNC_EXPLICIT} Os_ScheduleTableSyncType;
typedef enum {OS_SYNC_ASYNC, OS_SYNC_ADVANCING, OS_SYNC_RETARDING, OS_SYNC_INSYNC} Os_ScheduleTableSyncStateType;

struct Os_ScheduleTableDynType_s;
typedef struct Os_ScheduleTableType_s {
  CONSTP2VAR(struct Os_ScheduleTableDynType_s, OS_VAR, OS_CONST) dynamic;
  CounterType counter;
  boolean repeat;
  uint32 config;
  uint8 initial;
} Os_ScheduleTableType;
typedef P2CONST(Os_ScheduleTableType, TYPEDEF, OS_CONST) ScheduleTableType;  /* [$UKS 326] */
typedef P2VAR(ScheduleTableType, TYPEDEF, OS_VAR) ScheduleTableRefType;
typedef struct Os_ScheduleTableDynType_s {
  TickType match;
  ScheduleTableType next;
  ScheduleTableStatusType state;
  uint32 config;
} Os_ScheduleTableDynType;

/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, DeclareScheduleTable) */
#define DeclareScheduleTable(x) /* [$UKS 1184] */ /*lint -e(19) : DeclareScheduleTable has no content */

/* Service IDs [$UKS 476] */
typedef unsigned long OSServiceIdType;  /* [$UKS 475] */
#define OSServiceId_None ((OSServiceIdType)0U)
#define OSServiceId_ActivateTask ((OSServiceIdType)1)
#define OSServiceId_Os_AdvanceCounter ((OSServiceIdType)2)
#define OSServiceId_CancelAlarm ((OSServiceIdType)3)
#define OSServiceId_CallTrustedFunction ((OSServiceIdType)4)
#define OSServiceId_CheckISRMemoryAccess ((OSServiceIdType)5)
#define OSServiceId_CheckObjectAccess ((OSServiceIdType)6)
#define OSServiceId_CheckObjectOwnership ((OSServiceIdType)7)
#define OSServiceId_CheckTaskMemoryAccess ((OSServiceIdType)8)
#define OSServiceId_ChainTask ((OSServiceIdType)9)
#define OSServiceId_ClearEvent ((OSServiceIdType)10)
#define OSServiceId_ControlIdle ((OSServiceIdType)11)
#define OSServiceId_DisableAllInterrupts ((OSServiceIdType)12)
#define OSServiceId_EnableAllInterrupts ((OSServiceIdType)13)
#define OSServiceId_GetActiveApplicationMode ((OSServiceIdType)14)
#define OSServiceId_GetAlarm ((OSServiceIdType)15)
#define OSServiceId_GetAlarmBase ((OSServiceIdType)16)
#define OSServiceId_GetApplicationID ((OSServiceIdType)17)
#define OSServiceId_GetCurrentApplicationID ((OSServiceIdType)18)
#define OSServiceId_GetCounterValue ((OSServiceIdType)19)
#define OSServiceId_GetElapsedCounterValue ((OSServiceIdType)20)
#define OSServiceId_GetEvent ((OSServiceIdType)21)
#define OSServiceId_GetISRID ((OSServiceIdType)22)
#define OSServiceId_GetResource ((OSServiceIdType)23)
#define OSServiceId_GetScheduleTableStatus ((OSServiceIdType)24)
#define OSServiceId_GetTaskID ((OSServiceIdType)25)
#define OSServiceId_GetTaskState ((OSServiceIdType)26)
#define OSServiceId_GetVersionInfo ((OSServiceIdType)27)
#define OSServiceId_IncrementCounter ((OSServiceIdType)28)
#define OSServiceId_NextScheduleTable ((OSServiceIdType)29)
#define OSServiceId_Os_GetExecutionTime ((OSServiceIdType)30)
#define OSServiceId_Os_GetISRMaxExecutionTime ((OSServiceIdType)31)
#define OSServiceId_Os_GetTaskActivationTime ((OSServiceIdType)32)
#define OSServiceId_Os_GetTaskMaxExecutionTime ((OSServiceIdType)33)
#define OSServiceId_Os_ResetISRMaxExecutionTime ((OSServiceIdType)34)
#define OSServiceId_Os_ResetTaskMaxExecutionTime ((OSServiceIdType)35)
#define OSServiceId_Os_GetElapsedTime ((OSServiceIdType)36)
#define OSServiceId_Os_GetTaskElapsedTime ((OSServiceIdType)37)
#define OSServiceId_Os_GetISRElapsedTime ((OSServiceIdType)38)
#define OSServiceId_Os_GetIdleElapsedTime ((OSServiceIdType)39)
#define OSServiceId_Os_ResetTaskElapsedTime ((OSServiceIdType)40)
#define OSServiceId_Os_ResetISRElapsedTime ((OSServiceIdType)41)
#define OSServiceId_Os_ResetIdleElapsedTime ((OSServiceIdType)42)
#define OSServiceId_Os_GetStackSize ((OSServiceIdType)43)
#define OSServiceId_Os_GetStackUsage ((OSServiceIdType)44)
#define OSServiceId_Os_GetStackValue ((OSServiceIdType)45)
#define OSServiceId_Os_GetISRMaxStackUsage ((OSServiceIdType)46)
#define OSServiceId_Os_GetTaskMaxStackUsage ((OSServiceIdType)47)
#define OSServiceId_Os_ResetISRMaxStackUsage ((OSServiceIdType)48)
#define OSServiceId_Os_ResetTaskMaxStackUsage ((OSServiceIdType)49)
#define OSServiceId_ReleaseResource ((OSServiceIdType)50)
#define OSServiceId_Restart ((OSServiceIdType)51)
#define OSServiceId_ResumeAllInterrupts ((OSServiceIdType)52)
#define OSServiceId_ResumeOSInterrupts ((OSServiceIdType)53)
#define OSServiceId_Schedule ((OSServiceIdType)54)
#define OSServiceId_SetEvent ((OSServiceIdType)55)
#define OSServiceId_SetAbsAlarm ((OSServiceIdType)56)
#define OSServiceId_SetRelAlarm ((OSServiceIdType)57)
#define OSServiceId_SetRestartPoint ((OSServiceIdType)58)
#define OSServiceId_ShutdownOS ((OSServiceIdType)59)
#define OSServiceId_StartOS ((OSServiceIdType)60)
#define OSServiceId_StartScheduleTableAbs ((OSServiceIdType)61)
#define OSServiceId_StartScheduleTableRel ((OSServiceIdType)62)
#define OSServiceId_StartScheduleTableSynchron ((OSServiceIdType)63)
#define OSServiceId_SyncScheduleTable ((OSServiceIdType)64)
#define OSServiceId_SyncScheduleTableRel ((OSServiceIdType)65)
#define OSServiceId_SetScheduleTableAsync ((OSServiceIdType)66)
#define OSServiceId_StopScheduleTable ((OSServiceIdType)67)
#define OSServiceId_SuspendAllInterrupts ((OSServiceIdType)68)
#define OSServiceId_SuspendOSInterrupts ((OSServiceIdType)69)
#define OSServiceId_TerminateApplication ((OSServiceIdType)70)
#define OSServiceId_TerminateTask ((OSServiceIdType)71)
#define OSServiceId_WaitEvent ((OSServiceIdType)72)
#define OSServiceId_AllowAccess ((OSServiceIdType)73)
#define OSServiceId_GetApplicationState ((OSServiceIdType)74)
/* Error logging  */
typedef unsigned int Os_BiggestType; /* Used in error logging */
typedef unsigned long Os_OrtiIdType;

#ifndef OS_NAMESPACE_PURE
  #define GetExecutionTime Os_GetExecutionTime
  #define GetTaskMaxExecutionTime Os_GetTaskMaxExecutionTime
  #define GetISRMaxExecutionTime Os_GetISRMaxExecutionTime
  #define ResetTaskMaxExecutionTime Os_ResetTaskMaxExecutionTime
  #define ResetISRMaxExecutionTime Os_ResetISRMaxExecutionTime
  #define GetStackUsage Os_GetStackUsage
  #define GetTaskMaxStackUsage Os_GetTaskMaxStackUsage
  #define GetISRMaxStackUsage Os_GetISRMaxStackUsage
  #define ResetTaskMaxStackUsage Os_ResetTaskMaxStackUsage
  #define ResetISRMaxStackUsage Os_ResetISRMaxStackUsage
  #define GetStackValue Os_GetStackValue
  #define GetStackSize Os_GetStackSize
  #define AdvanceCounter Os_AdvanceCounter
  #define Restart Os_Restart
  #define SetRestartPoint Os_SetRestartPoint
#endif
#define ActivateTask Os_ActivateTask
#define GetTaskID Os_GetTaskID
#define GetTaskState Os_GetTaskState
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Schedule) */
#define Schedule() Os_Schedule()
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, ChainTask) */
#define ChainTask Os_ChainTask
#define TerminateTask Os_TerminateTask
#define SetEvent   Os_SetEvent
#define ClearEvent Os_ClearEvent
#define GetEvent   Os_GetEvent
#define WaitEvent  Os_WaitEvent
#define GetResource  Os_GetResource
#define ReleaseResource  Os_ReleaseResource
#define DisableAllInterrupts Os_DisableAllInterrupts
#define EnableAllInterrupts Os_EnableAllInterrupts
#define SuspendAllInterrupts Os_SuspendAllInterrupts
#define ResumeAllInterrupts Os_ResumeAllInterrupts
#define SuspendOSInterrupts Os_SuspendOSInterrupts
#define ResumeOSInterrupts Os_ResumeOSInterrupts
#define GetISRID Os_GetISRID
#define GetActiveApplicationMode Os_GetActiveApplicationMode
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CheckObjectOwnership, CheckObjectAccess) */
#define CheckObjectOwnership(x,y) Os_CheckObjectOwnership(x,(Os_AnyType)y)
#define CheckObjectAccess(x,y,z) Os_CheckObjectAccess(x,y,(Os_AnyType)z)
#define GetApplicationID Os_GetApplicationID
#define GetCurrentApplicationID Os_GetCurrentApplicationID
#define CallTrustedFunction Os_CallTrustedFunction
#define GetApplicationState Os_GetApplicationState
#define AllowAccess Os_AllowAccess
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, CheckTaskMemoryAccess, CheckISRMemoryAccess) */
#define CheckTaskMemoryAccess(x,y,z) Os_CheckTaskMemoryAccess(x,(MemoryStartAddressType)y,z)
#define CheckISRMemoryAccess(x,y,z) Os_CheckISRMemoryAccess(x,(MemoryStartAddressType)y,z)
#define GetCounterValue Os_GetCounterValue
#define GetElapsedCounterValue Os_GetElapsedCounterValue /* AUTOSAR 3.x */
#define GetElapsedValue Os_GetElapsedCounterValue  /* AUTOSAR 4.x */
#define IncrementCounter Os_IncrementCounter
#define GetAlarmBase Os_GetAlarmBase
#define CancelAlarm Os_CancelAlarm
#define GetAlarm Os_GetAlarm
#define SetRelAlarm Os_SetRelAlarm
#define SetAbsAlarm Os_SetAbsAlarm
#define StopScheduleTable Os_StopScheduleTable
#define StartScheduleTableRel Os_StartScheduleTableRel
#define StartScheduleTableAbs Os_StartScheduleTableAbs
#define StartScheduleTableSynchron Os_StartScheduleTableSynchron
#define SyncScheduleTable Os_SyncScheduleTable
#define SetScheduleTableAsync Os_SetScheduleTableAsync
#define GetScheduleTableStatus Os_GetScheduleTableStatus
#define NextScheduleTable Os_NextScheduleTable
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Os_SetRestartPoint) */
#define Os_SetRestartPoint() ( (OS_NOAPPMODE == Os_CurrentAppMode) ? (Os_setjmp(&(Os_RestartJumpBuf)), Os_Restartable = TRUE, E_OK) : E_OS_SYS_NO_RESTART) /* [$UKS  770] [$UKS  771] */ /*lint !e545 Address of what might be an array */
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, StartOS) */
#define StartOS(x) {if (Os_StartOS(x)) {while(Os_Cbk_Idle()) {} /* [$UKS 161] */; while((1)) {OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();OS_NOP();} /* [$UKS 16] */}}
#define ShutdownOS Os_ShutdownOS
#define ControlIdle Os_ControlIdle
/* -- Start expansion of <OsTrace.h> -- */
typedef StatusType   Os_TraceStatusType;
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, OS_TRACE*, Os_Log*, Os_Set*, Os_Clear*, Os_Trigger*, OSTRACE_*) */

#ifndef OS_TRACE
/* [MISRA 2012 Dir 4.9] */ /*lint -estring(9026, Os_*Trace*, Os_*Trigger*) */
  #define Os_EnableTraceClasses(x) /* empty */
  #define Os_DisableTraceClasses(x) /* empty */
  #define Os_EnableTraceCategories(x) /* empty */
  #define Os_DisableTraceCategories(x) /* empty */
  #define Os_StartFreeRunningTrace() /* empty */
  #define Os_StartBurstingTrace() /* empty */
  #define Os_StartTriggeringTrace() /* empty */
  #define Os_StopTrace() /* empty */
  #define Os_CheckTraceOutput() /* empty */
  #define Os_SetTraceRepeat(x) /* empty */
  #define Os_TraceCommInit() /* empty */
  #define Os_UploadTraceData() /* empty */
  #define Os_TraceDumpAsync(x) /* empty */
  #define Os_SetTriggerConditions(x,y) /* empty */
  #define Os_SetTriggerConditionsN(x,y) /* empty */
  #define Os_SetTriggerConditionsTII(x,y) /* empty */
  #define Os_SetTriggerWindow(x,y) /* empty */
  #define Os_TriggerNow() /* empty */
#endif /* OS_TRACE */

/* Triggering */
#define Os_ClearTrigger()              Os_SetTriggerConditions(OS_TRACE_TRIGGER, 0)               /* [$UKS 1042] [$UKS 1043] [$UKS 1044] */

#define OS_TRACE_TRIGGER_ANY (&Os_TraceDummy)
#define Os_Cat1_OS_TRACE_TRIGGER_ANY (0)
#define Os_Tr_OS_TRACE_TRIGGER_ANY (0)
#define Os_TriggerOnActivation(x)      Os_SetTriggerConditions(OS_TRACE_ACTIVATION,     (x)->id) /* [$UKS 1050] [$UKS 1051] [$UKS 1266] */
#define Os_TriggerOnChain(x)           Os_SetTriggerConditions(OS_TRACE_CHAINACTIVATION,(x)->id) /* [$UKS 1052] [$UKS 1053] [$UKS 1179] */
#define Os_TriggerOnTaskStart(x)       Os_SetTriggerConditions(OS_TRACE_TASKSTART,      (x)->id) /* [$UKS 1054] [$UKS 1055] [$UKS 1056] */
#define Os_TriggerOnTaskStop(x)        Os_SetTriggerConditions(OS_TRACE_TASKEND,        (x)->id) /* [$UKS 1057] [$UKS 1058] [$UKS 1059] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnCat1ISRStart) */
#define Os_TriggerOnCat1ISRStart(x)    Os_SetTriggerConditions(OS_TRACE_TASKSTART,(Os_Cat1_##x)) /* [$UKS 1066] [$UKS 1067] [$UKS 1068] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnCat1ISRStop) */
#define Os_TriggerOnCat1ISRStop(x)     Os_SetTriggerConditions(OS_TRACE_TASKEND,  (Os_Cat1_##x)) /* [$UKS 1069] [$UKS 1070] [$UKS 1071] */
#define Os_TriggerOnCat2ISRStart(x)    Os_SetTriggerConditions(OS_TRACE_TASKSTART,      (x)->id) /* [$UKS 1072] [$UKS 1073] [$UKS 1074] */
#define Os_TriggerOnCat2ISRStop(x)     Os_SetTriggerConditions(OS_TRACE_TASKEND,        (x)->id) /* [$UKS 1075] [$UKS 1076] [$UKS 1077] */
#define Os_TriggerOnGetResource(x)     Os_SetTriggerConditions(OS_TRACE_GETRESOURCE,    (x)->id) /* [$UKS 1082] [$UKS 1083] [$UKS 1084] */
#define Os_TriggerOnReleaseResource(x) Os_SetTriggerConditions(OS_TRACE_RELEASERESOURCE,(x)->id) /* [$UKS 1085] [$UKS 1086] [$UKS 1087] */
#define Os_TriggerOnSetEvent(x)        Os_SetTriggerConditions(OS_TRACE_SETEVENT,       (x)->id) /* [$UKS 1088] [$UKS 1089] [$UKS 1090] */
#define Os_TriggerOnTracepoint(x)      Os_SetTriggerConditionsTII(OS_TRACE_POINT,       (x))     /* [$UKS 1091] [$UKS 1092] */
#define Os_TriggerOnTaskTracepoint(x,y) Os_SetTriggerConditions(OS_TRACE_TASKPOINT+(x),(y)->id)  /* [$UKS 1093] [$UKS 1094] [$UKS 1095] */
#define Os_TriggerOnIntervalStart(x)   Os_SetTriggerConditionsTII(OS_TRACE_STARTINTERVAL,(x))    /* [$UKS 1096] [$UKS 1097] */
#define Os_TriggerOnIntervalEnd(x)     Os_SetTriggerConditionsTII(OS_TRACE_ENDINTERVAL,  (x))    /* [$UKS 1098] [$UKS 1099] */
#define Os_TriggerOnIntervalStop(x)    Os_TriggerOnIntervalEnd(x)                                /* [$UKS 1100] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnAlarmExpiry) */
#define Os_TriggerOnAlarmExpiry(x)     Os_SetTriggerConditions(OS_TRACE_ALARM_EXPIRY, (Os_Tr_##x)) /* [$UKS 1106] [$UKS 1107] [$UKS 1108] */
#define Os_TriggerOnError(x)           Os_SetTriggerConditionsN(OS_TRACE_ERROR, (x))             /* [$UKS 1109] [$UKS 1110] [$UKS 1181] */
#define Os_TriggerOnShutdown(x)        Os_SetTriggerConditionsN(OS_TRACE_SHUTDOWN, (x))          /* [$UKS 1111] [$UKS 1112] [$UKS 1199] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnScheduleTableExpiry) */
#define Os_TriggerOnScheduleTableExpiry(x) Os_SetTriggerConditions(OS_TRACE_ALARM_EXPIRY, (Os_Tr_##x))  /* [$UKS 1200] [$UKS 1201] [$UKS 1202] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnIncrementCounter) */
#define Os_TriggerOnIncrementCounter(x) Os_SetTriggerConditions(OS_TRACE_TICK_COUNTER, (Os_Tr_##x)) /* [$UKS 1203] [$UKS 1204] [$UKS 1208] */
/* [MISRA 2012 Rule 20.10] */ /*lint -estring(9024, Os_TriggerOnAdvanceCounter) */
#define Os_TriggerOnAdvanceCounter(x)   Os_SetTriggerConditions(OS_TRACE_TICK_COUNTER, (Os_Tr_##x)) /* [$UKS 1205] [$UKS 1206] [$UKS 1207] */

#ifndef OS_TRACE_NAMESPACE_PURE /* [$UKS 1154] */
  #define EnableTraceClasses Os_EnableTraceClasses
  #define DisableTraceClasses Os_DisableTraceClasses
  #define EnableTraceCategories Os_EnableTraceCategories
  #define DisableTraceCategories Os_DisableTraceCategories
  #define StartFreeRunningTrace Os_StartFreeRunningTrace
  #define StartBurstingTrace Os_StartBurstingTrace
  #define StartTriggeringTrace Os_StartTriggeringTrace
  #define StopTrace Os_StopTrace
  #define CheckTraceOutput Os_CheckTraceOutput
  #define SetTraceRepeat Os_SetTraceRepeat
  #define SetTriggerConditions Os_SetTriggerConditions
  #define TraceCommInit Os_TraceCommInit
  #define TraceCommInitTarget Os_Cbk_TraceCommInitTarget
  #define TraceCommDataReady Os_Cbk_TraceCommDataReady
  #define UploadTraceData Os_UploadTraceData
  #define SetTriggerWindow Os_SetTriggerWindow
  #define ClearTrigger Os_ClearTrigger
  #define TriggerNow  Os_TriggerNow

  #define TriggerOnActivation Os_TriggerOnActivation
  #define TriggerOnChain Os_TriggerOnChain
  #define TriggerOnTaskStart Os_TriggerOnTaskStart
  #define TriggerOnTaskStop Os_TriggerOnTaskStop
  #define TriggerOnCat1ISRStart Os_TriggerOnCat1ISRStart
  #define TriggerOnCat1ISRStop Os_TriggerOnCat1ISRStop
  #define TriggerOnCat2ISRStart Os_TriggerOnCat2ISRStart
  #define TriggerOnCat2ISRStop Os_TriggerOnCat2ISRStop
  #define TriggerOnGetResource Os_TriggerOnGetResource
  #define TriggerOnReleaseResource Os_TriggerOnReleaseResource
  #define TriggerOnSetEvent Os_TriggerOnSetEvent
  #define TriggerOnTracepoint Os_TriggerOnTracepoint
  #define TriggerOnIntervalStart Os_TriggerOnIntervalStart
  #define TriggerOnIntervalEnd Os_TriggerOnIntervalEnd
  #define TriggerOnIntervalStop Os_TriggerOnIntervalStop
  #define TriggerOnTaskTracepoint Os_TriggerOnTaskTracepoint
  #define TriggerOnAlarmExpiry Os_TriggerOnAlarmExpiry
  #define TriggerOnScheduleTableExpiry Os_TriggerOnScheduleTableExpiry
  #define TriggerOnIncrementCounter Os_TriggerOnIncrementCounter
  #define TriggerOnAdvanceCounter Os_TriggerOnAdvanceCounter
  #define TriggerOnError Os_TriggerOnError
  #define TriggerOnShutdown Os_TriggerOnShutdown
#endif





/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_TRACECOMMDATAREADY_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_TRACECOMMDATAREADY_CODE) Os_Cbk_TraceCommDataReady(void) /* [$UKS 1212] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_TRACECOMMDATAREADY_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_TRACECOMMINITTARGET_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(Os_TraceStatusType, OS_OS_CBK_TRACECOMMINITTARGET_CODE) Os_Cbk_TraceCommInitTarget(void) /* [$UKS 1209]*/;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_TRACECOMMINITTARGET_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_TRACECOMMTXBYTE_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_TRACECOMMTXBYTE_CODE) Os_Cbk_TraceCommTxByte(uint8 val) /* [$UKS 1211] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXBYTE_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_TRACECOMMTXEND_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_TRACECOMMTXEND_CODE) Os_Cbk_TraceCommTxEnd(void) /* [$UKS 1213] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXEND_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_TRACECOMMTXREADY_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(boolean, OS_OS_CBK_TRACECOMMTXREADY_CODE) Os_Cbk_TraceCommTxReady(void) /* [$UKS 1215] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXREADY_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_TRACECOMMTXSTART_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_TRACECOMMTXSTART_CODE) Os_Cbk_TraceCommTxStart(void) /* [$UKS 1214] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_TRACECOMMTXSTART_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

/* -- End expansion of <OsTrace.h> -- */

















/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CODE_LIB
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_CODE) Os_GetVersionInfo(Std_VersionInfoType *versioninfo) /* [$UKS 731] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetExecutionTime(void) /* [$UKS 538] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetTaskMaxExecutionTime(TaskType TaskID) /* [$UKS 543] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetISRMaxExecutionTime(ISRType ISRID) /* [$UKS 548] */;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskMaxExecutionTime(TaskType TaskID) /* [$UKS 553] */;
extern FUNC(StatusType, OS_CODE) Os_ResetISRMaxExecutionTime(ISRType ISRID) /* [$UKS 555] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetElapsedTime(void) /* [$UKS 1855] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetTaskElapsedTime(TaskType TaskID) /* [$UKS 1859] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetISRElapsedTime(ISRType ISRID) /* [$UKS 1863] */;
extern FUNC(Os_StopwatchTickType, OS_CODE) Os_GetIdleElapsedTime(Os_IdleType IdleID) /* [$UKS 1867] */;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskElapsedTime(TaskType TaskID) /* [$UKS 1871] */;
extern FUNC(StatusType, OS_CODE) Os_ResetISRElapsedTime(ISRType ISRID) /* [$UKS 1876] */;
extern FUNC(StatusType, OS_CODE) Os_ResetIdleElapsedTime(Os_IdleType IdleID) /* [$UKS 1881] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetStackUsage(void) /* [$UKS 1238] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetTaskMaxStackUsage(TaskType TaskID) /* [$UKS 1242] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetISRMaxStackUsage(ISRType ISRID) /* [$UKS 1247] */;
extern FUNC(StatusType, OS_CODE) Os_ResetTaskMaxStackUsage(TaskType TaskID) /* [$UKS 1252] */;
extern FUNC(StatusType, OS_CODE) Os_ResetISRMaxStackUsage(ISRType ISRID) /* [$UKS 1257] */;
extern FUNC(Os_StackValueType, OS_CODE) Os_GetStackValue(void) /* [$UKS 1263] */;
extern FUNC(Os_StackSizeType, OS_CODE) Os_GetStackSize(Os_StackValueType Base, Os_StackValueType Sample) /* [$UKS 1264] */;
extern FUNC(StatusType, OS_CODE) Os_ActivateTask(TaskType TaskID) /* $UKS 61 */;
extern FUNC(StatusType, OS_CODE) Os_GetTaskID(TaskRefType TaskID) /* [$UKS 86] */;
extern FUNC(StatusType, OS_CODE) Os_GetTaskState(TaskType TaskID, TaskStateRefType State) /* [$UKS 89] */;
extern FUNC(StatusType, OS_CODE) Os_Schedule(void) /* [$UKS 83] */;
extern FUNC(StatusType, OS_CODE) Os_SetEvent(TaskType TaskID, EventMaskType Mask) /* [$UKS 144] */;
extern FUNC(StatusType, OS_CODE) Os_ClearEvent(EventMaskType Mask) /* [$UKS 148] */;
extern FUNC(StatusType, OS_CODE) Os_GetEvent(TaskType TaskID, EventMaskRefType Mask) /* [$UKS 150] */;
extern FUNC(StatusType, OS_CODE) Os_WaitEvent(EventMaskType Mask) /* [$UKS 153] */;
extern FUNC(StatusType, OS_CODE) Os_GetResource(ResourceType ResID) /* [$UKS 204] */;
extern FUNC(StatusType, OS_CODE) Os_ReleaseResource(ResourceType ResID) /* [$UKS 207] */;
extern FUNC(void, OS_CODE) Os_DisableAllInterrupts(void) /* [$UKS 113] */;
extern FUNC(void, OS_CODE) Os_EnableAllInterrupts(void) /* [$UKS 110] */;
extern FUNC(void, OS_CODE) Os_SuspendAllInterrupts(void) /* [$UKS 121] */;
extern FUNC(void, OS_CODE) Os_ResumeAllInterrupts(void) /* [$UKS 116] */;
extern FUNC(void, OS_CODE) Os_SuspendOSInterrupts(void) /* [$UKS 128] */;
extern FUNC(void, OS_CODE) Os_ResumeOSInterrupts(void) /* [$UKS 124] */;
extern FUNC(ISRType, OS_CODE) Os_GetISRID(void) /* [$UKS 130] */;
extern FUNC(AppModeType, OS_CODE) Os_GetActiveApplicationMode(void) /* [$UKS 384] */;
extern FUNC(ApplicationType, OS_CODE) Os_CheckObjectOwnership(ObjectTypeType ObjectType, Os_AnyType Object) /* $UKS 438 */;
extern FUNC(ObjectAccessType, OS_CODE) Os_CheckObjectAccess(ApplicationType ApplID, ObjectTypeType ObjectType, Os_AnyType Object) /* $UKS 425 */;
extern FUNC(ApplicationType, OS_CODE) Os_GetApplicationID(void) /* [$UKS 417] */;
extern FUNC(ApplicationType, OS_CODE) Os_GetCurrentApplicationID(void) /* [$UKS 2004] */;
extern FUNC(StatusType, OS_CODE) Os_TerminateTask(void) /* [$UKS 66] */;
extern FUNC(AccessType, OS_CODE) Os_CheckTaskMemoryAccess(TaskType TaskID, MemoryStartAddressType Address, MemorySizeType Size) /* [$UKS 595] */;
extern FUNC(AccessType, OS_CODE) Os_CheckISRMemoryAccess(ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size) /* [$UKS 596] */;
extern FUNC(StatusType, OS_CODE) Os_GetCounterValue(CounterType CounterID, TickRefType Value) /* [$UKS 226] */;
extern FUNC(StatusType, OS_CODE) Os_GetElapsedCounterValue(CounterType CounterID, TickRefType Value, TickRefType ElapsedValue) /* [$UKS 231] */;
extern FUNC(StatusType, OS_CODE) Os_IncrementCounter(CounterType CounterID) /* [$UKS 238] */;
extern FUNC(StatusType, OS_CODE) Os_AdvanceCounter(CounterType CounterID) /* [$UKS 858] */;
extern FUNC(StatusType, OS_CODE) Os_GetAlarmBase(AlarmType AlarmID, AlarmBaseRefType Info) /* [$UKS 282] */;
extern FUNC(StatusType, OS_CODE) Os_CancelAlarm(AlarmType AlarmID) /* [$UKS 300] */;
extern FUNC(StatusType, OS_CODE) Os_GetAlarm(AlarmType AlarmID, TickRefType Tick) /* [$UKS 285] */;
extern FUNC(StatusType, OS_CODE) Os_SetRelAlarm(AlarmType AlarmID, TickType increment, TickType cycle) /* [$UKS 288] */;
extern FUNC(StatusType, OS_CODE) Os_SetAbsAlarm(AlarmType AlarmID, TickType start, TickType cycle) /* [$UKS 294] */;
extern FUNC(StatusType, OS_CODE) Os_StopScheduleTable(ScheduleTableType ScheduleTableID) /* [$UKS 341] */;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableRel(ScheduleTableType ScheduleTableID, TickType Offset) /* [$UKS 329] */;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableAbs(ScheduleTableType ScheduleTableID, TickType Start) /* [$UKS 336] */;
extern FUNC(StatusType, OS_CODE) Os_StartScheduleTableSynchron(ScheduleTableType ScheduleTableID) /* [$UKS 362] */;
extern FUNC(StatusType, OS_CODE) Os_SyncScheduleTable(ScheduleTableType ScheduleTableID, TickType Value) /* [$UKS 368] */;
extern FUNC(StatusType, OS_CODE) Os_SyncScheduleTableRel(ScheduleTableType ScheduleTableID, SignedTickType RelativeValue) /* [$UKS 1885] */;
extern FUNC(StatusType, OS_CODE) Os_SetScheduleTableAsync(ScheduleTableType ScheduleTableID) /* [$UKS 376] */;
extern FUNC(StatusType, OS_CODE) Os_GetScheduleTableStatus(ScheduleTableType ScheduleTableID, ScheduleTableStatusRefType ScheduleStatus) /* [$UKS 354] */;
extern FUNC(StatusType, OS_CODE) Os_NextScheduleTable(ScheduleTableType ScheduleTableID_From, ScheduleTableType ScheduleTableID_To) /* [$UKS 345] */;
extern FUNC(boolean, OS_CODE) Os_StartOS(AppModeType Mode) /* [$UKS 19] */;
extern FUNC(void, OS_CODE) Os_ShutdownOS(StatusType Error) /* [$UKS 20] */;
extern FUNC(void, OS_CODE) Os_ProtectionLog(StatusType os_status);
extern FUNC(StatusType, OS_CODE) Os_ControlIdle(CoreIdType CoreID, IdleModeType IdleMode) /* [$UKS 1911] */;
extern FUNC(IdleModeType, OS_CODE) Os_CurrentIdleMode(void);
extern FUNC(uint32, OS_CODE) Os_GetCurrentTPL(void) /* [$UKS 2012] */;
extern FUNC(Os_imaskType, OS_CODE) Os_GetCurrentIMask(void) /* [$UKS 2016] */;
extern FUNC(StatusType, OS_CODE) Os_Restart(void) /* [$UKS 772] */;
extern FUNC(StatusType, OS_CODE) Os_ChainTask(TaskType TaskID) /* [$UKS 73] */;
extern FUNC(StatusType, OS_CODE) Os_GetApplicationState(ApplicationType Application, ApplicationStateRefType Value) /* [$UKS 1301] */;
extern FUNC(StatusType, OS_CODE) Os_AllowAccess(void) /* [$UKS 1305] */;
extern FUNC(StatusType, OS_CODE) Os_CallTrustedFunction(TrustedFunctionIndexType FunctionIndex, TrustedFunctionParameterRefType FunctionParams) /* [$UKS 601] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CODE_LIB
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_CONST_FAST_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern CONST(CoreIdType, OS_CONST_FAST) TotalNumberOfCores;
extern CONST(Os_ISRType, OS_CONST_FAST) Os_const_isrs[];
extern CONST(TaskType, OS_CONST_FAST) Os_const_tasks[];
extern CONST(Os_ResourceType, OS_CONST_FAST) Os_const_resources[];
extern CONST(Os_CounterType, OS_CONST_FAST) Os_const_counters[];
extern CONST(Os_ScheduleTableType, OS_CONST_FAST) Os_const_scheduletables[];
extern CONST(Os_TaskType, OS_CONST_FAST) Os_const_tasks0[];
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_CONST_FAST_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_ERRORHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_ERRORHOOK_CODE) ErrorHook(StatusType Error) /* [$UKS 479] [$UKS 1943] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_ERRORHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_CHECKMEMORYACCESS_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(AccessType, OS_OS_CBK_CHECKMEMORYACCESS_CODE) Os_Cbk_CheckMemoryAccess(ApplicationType Application, TaskType TaskID, ISRType ISRID, MemoryStartAddressType Address, MemorySizeType Size);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_CHECKMEMORYACCESS_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_CHECKSTACKDEPTH_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_CHECKSTACKDEPTH_CODE) Os_Cbk_CheckStackDepth(CoreIdType Core_id, Os_StackSizeType Depth, Os_StackSizeType CurrentPos);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_CHECKSTACKDEPTH_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_GETSTOPWATCH_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
#ifndef Os_Cbk_GetStopwatch
 extern FUNC(Os_StopwatchTickType, OS_OS_CBK_GETSTOPWATCH_CODE) Os_Cbk_GetStopwatch(void) /* [$UKS 536] */;
#endif
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_GETSTOPWATCH_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_IDLE_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(boolean, OS_OS_CBK_IDLE_CODE) Os_Cbk_Idle(void) /* [$UKS 161] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_IDLE_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_INSHUTDOWN_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_INSHUTDOWN_CODE) Os_Cbk_InShutdown(void) /* internal use */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_INSHUTDOWN_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_STACKOVERRUNHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_STACKOVERRUNHOOK_CODE) Os_Cbk_StackOverrunHook(Os_StackSizeType Overrun, Os_StackOverrunType Reason);
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_STACKOVERRUNHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_OS_CBK_TIMEOVERRUNHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_OS_CBK_TIMEOVERRUNHOOK_CODE) Os_Cbk_TimeOverrunHook(Os_StopwatchTickType Overrun) /* [$UKS 537] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_OS_CBK_TIMEOVERRUNHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_POSTTASKHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_POSTTASKHOOK_CODE) PostTaskHook(void) /* [$UKS 176] [$UKS 180] [$UKS 1943] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_POSTTASKHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_PRETASKHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_PRETASKHOOK_CODE) PreTaskHook(void) /* [$UKS 175] [$UKS 179]  [$UKS 1943] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_PRETASKHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_PROTECTIONHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(ProtectionReturnType, OS_PROTECTIONHOOK_CODE) ProtectionHook(StatusType FatalError) /* [$UKS 1943] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_PROTECTIONHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_SHUTDOWNHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_SHUTDOWNHOOK_CODE) ShutdownHook(StatusType Error) /* [$UKS 18] [$UKS 1943] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_SHUTDOWNHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_STARTUPHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern FUNC(void, OS_STARTUPHOOK_CODE) StartupHook(void) /* [$UKS 24] [$UKS 1943] */;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_STARTUPHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern VAR(uint32, OS_VAR_CLEARED) Os_DisableAllCount;
extern VAR(uint32, OS_VAR_CLEARED) Os_SuspendAllCount;
extern VAR(uint32, OS_VAR_CLEARED) Os_SuspendOSCount;
extern VAR(boolean, OS_VAR_CLEARED) Os_Restartable;
extern OS_VOLATILE VAR(AppModeType, OS_VAR_CLEARED) Os_CurrentAppMode;
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
/* ------------------------------------------------- */
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */
extern OS_VOLATILE VAR(Os_psetType, OS_VAR_NO_INIT) Os_ReadyTasks /*lint --e(9018) A union type */;
extern OS_VOLATILE VAR(ISRType, OS_VAR_NO_INIT) Os_RunningISR;
extern OS_VOLATILE VAR(TaskType, OS_VAR_NO_INIT) Os_RunningTask;
extern OS_VOLATILE VAR(Os_tpmaskType, OS_VAR_NO_INIT) Os_RunningTPMask /*lint --e(9018) A union type */;
extern VAR(Os_imaskType, OS_VAR_NO_INIT) Os_DisableAllImask;
extern VAR(Os_imaskType, OS_VAR_NO_INIT) Os_SuspendAllImask;
extern VAR(Os_imaskType, OS_VAR_NO_INIT) Os_SuspendOSImask;
extern OS_VOLATILE VAR(Os_OrtiIdType, OS_VAR_NO_INIT) Os_OrtiApiID;
extern VAR(StatusType, OS_VAR_NO_INIT) Os_OrtiLastError;
extern VAR(Os_jump_buf, OS_VAR_NO_INIT) Os_RestartJumpBuf;
extern VAR(Os_TaskDynType, OS_VAR_NO_INIT) Os_dyn_tasks[];
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

/* -- End expansion of <OsMinusConfig.h> -- */
#include <Os_Cfg.h> /* [$UKS 649] */
#endif /* OS_H */
