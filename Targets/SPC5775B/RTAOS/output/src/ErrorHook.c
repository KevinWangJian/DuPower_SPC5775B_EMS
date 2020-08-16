/*
 * Sample code showing how to determine what error has occurred, and
 * the source of the error.
 */
#include <Os.h>
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_START_SEC_ERRORHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */

FUNC(void, OS_ERRORHOOK_CODE) ErrorHook(StatusType Error) {
  ISRType ISRInError;
  TaskType TaskInError;

  /*
   * This code sample shows how to determine which Task or
   * ISR was running when the error occurred.
   */
  ISRInError = GetISRID();
  if (ISRInError != INVALID_ISR) {
    /* The error occurred when ISR 'ISRInError' was running */
  } else {
    (void)GetTaskID(&TaskInError);
    if (TaskInError != INVALID_TASK) {
      /* The error occurred when Task 'TaskInError' was running */
    } else {
      /* The error occurred during StartOS, Os_Cbk_Idle or ShutdownOS */
    }
  }

  /*
   * This code sample shows how to determine which error
   * was detected.
   */
  switch (Error) {
    case E_OS_ACCESS:
      /* Handle E_OS_ACCESS */
      break;
    case E_OS_CALLEVEL:
      /* Handle E_OS_CALLEVEL */
      break;
    case E_OS_ID:
      /* Handle E_OS_ID */
      break;
    case E_OS_LIMIT:
      /* Handle E_OS_LIMIT */
      break;
    case E_OS_NOFUNC:
      /* Handle E_OS_NOFUNC */
      break;
    case E_OS_RESOURCE:
      /* Handle E_OS_RESOURCE */
      break;
    case E_OS_STATE:
      /* Handle E_OS_STATE */
      break;
    case E_OS_VALUE:
      /* Handle E_OS_VALUE */
      break;
    case E_OS_SERVICEID:
      /* Handle E_OS_SERVICEID */
      break;
    case E_OS_ILLEGAL_ADDRESS:
      /* Handle E_OS_ILLEGAL_ADDRESS */
      break;
    case E_OS_MISSINGEND:
      /* Handle E_OS_MISSINGEND */
      break;
    case E_OS_DISABLEDINT:
      /* Handle E_OS_DISABLEDINT */
      break;
    case E_OS_STACKFAULT:
      /* Handle E_OS_STACKFAULT */
      break;
    case E_OS_CORE:
      /* Handle E_OS_CORE */
      break;
    case E_OS_SPINLOCK:
      /* Handle E_OS_SPINLOCK */
      break;
    case E_OS_INTERFERENCE_DEADLOCK:
      /* Handle E_OS_INTERFERENCE_DEADLOCK */
      break;
    case E_OS_NESTING_DEADLOCK:
      /* Handle E_OS_NESTING_DEADLOCK */
      break;
    case E_OS_SYS_NO_RESTART:
      /* Handle E_OS_SYS_NO_RESTART */
      break;
    case E_OS_SYS_RESTART:
      /* Handle E_OS_SYS_RESTART */
      break;
    case E_OS_SYS_OVERRUN:
      /* Handle E_OS_SYS_OVERRUN */
      break;
    case E_OS_XCORE_QFULL:
      /* Handle E_OS_XCORE_QFULL */
      break;
    default:
      /* Never here */
      break;
  }

#ifdef OSErrorGetServiceId
  /*
   * With Service ID logging enabled, it is possible to
   * determine which API was running when the error was
   * detected through OSErrorGetServiceId().
   * If Parameter logging is enabled, it is also possible
   * to use the OSError_ macros to see the parameter
   * values passed to the API.
   */
  switch (OSErrorGetServiceId()) {
    case OSServiceId_None:
      /* Handle ISR termination errors */
      break;
    case OSServiceId_ActivateTask:
      /* Handle error from ActivateTask */
      /* OSError_ActivateTask_TaskID() contains the TaskType 'TaskID' passed to ActivateTask */
      break;
    case OSServiceId_Os_AdvanceCounter:
      /* Handle error from Os_AdvanceCounter */
      /* OSError_Os_AdvanceCounter_CounterID() contains the CounterType 'CounterID' passed to Os_AdvanceCounter */
      break;
    case OSServiceId_CancelAlarm:
      /* Handle error from CancelAlarm */
      /* OSError_CancelAlarm_AlarmID() contains the AlarmType 'AlarmID' passed to CancelAlarm */
      break;
    case OSServiceId_CallTrustedFunction:
      /* Handle error from CallTrustedFunction */
      /* OSError_CallTrustedFunction_FunctionIndex() contains the TrustedFunctionIndexType 'FunctionIndex' passed to CallTrustedFunction */
      /* OSError_CallTrustedFunction_FunctionParams() contains the TrustedFunctionParameterRefType 'FunctionParams' passed to CallTrustedFunction */
      break;
    case OSServiceId_CheckISRMemoryAccess:
      /* Handle error from CheckISRMemoryAccess */
      break;
    case OSServiceId_CheckObjectAccess:
      /* Handle error from CheckObjectAccess */
      break;
    case OSServiceId_CheckObjectOwnership:
      /* Handle error from CheckObjectOwnership */
      break;
    case OSServiceId_CheckTaskMemoryAccess:
      /* Handle error from CheckTaskMemoryAccess */
      break;
    case OSServiceId_ChainTask:
      /* Handle error from ChainTask */
      /* OSError_ChainTask_TaskID() contains the TaskType 'TaskID' passed to ChainTask */
      break;
    case OSServiceId_ClearEvent:
      /* Handle error from ClearEvent */
      /* OSError_ClearEvent_Mask() contains the EventMaskType 'Mask' passed to ClearEvent */
      break;
    case OSServiceId_ControlIdle:
      /* Handle error from ControlIdle */
      /* OSError_ControlIdle_CoreID() contains the CoreIdType 'CoreID' passed to ControlIdle */
      /* OSError_ControlIdle_IdleMode() contains the IdleModeType 'IdleMode' passed to ControlIdle */
      break;
    case OSServiceId_DisableAllInterrupts:
      /* Handle error from DisableAllInterrupts */
      break;
    case OSServiceId_EnableAllInterrupts:
      /* Handle error from EnableAllInterrupts */
      break;
    case OSServiceId_GetActiveApplicationMode:
      /* Handle error from GetActiveApplicationMode */
      break;
    case OSServiceId_GetAlarm:
      /* Handle error from GetAlarm */
      /* OSError_GetAlarm_AlarmID() contains the AlarmType 'AlarmID' passed to GetAlarm */
      /* OSError_GetAlarm_Tick() contains the TickRefType 'Tick' passed to GetAlarm */
      break;
    case OSServiceId_GetAlarmBase:
      /* Handle error from GetAlarmBase */
      /* OSError_GetAlarmBase_AlarmID() contains the AlarmType 'AlarmID' passed to GetAlarmBase */
      /* OSError_GetAlarmBase_Info() contains the AlarmBaseRefType 'Info' passed to GetAlarmBase */
      break;
    case OSServiceId_GetApplicationID:
      /* Handle error from GetApplicationID */
      break;
    case OSServiceId_GetCurrentApplicationID:
      /* Handle error from GetCurrentApplicationID */
      break;
    case OSServiceId_GetCounterValue:
      /* Handle error from GetCounterValue */
      /* OSError_GetCounterValue_CounterID() contains the CounterType 'CounterID' passed to GetCounterValue */
      /* OSError_GetCounterValue_Value() contains the TickRefType 'Value' passed to GetCounterValue */
      break;
    case OSServiceId_GetElapsedCounterValue:
      /* Handle error from GetElapsedCounterValue */
      /* OSError_GetElapsedCounterValue_CounterID() contains the CounterType 'CounterID' passed to GetElapsedCounterValue */
      /* OSError_GetElapsedCounterValue_Value() contains the TickRefType 'Value' passed to GetElapsedCounterValue */
      /* OSError_GetElapsedCounterValue_ElapsedValue() contains the TickRefType 'ElapsedValue' passed to GetElapsedCounterValue */
      break;
    case OSServiceId_GetEvent:
      /* Handle error from GetEvent */
      /* OSError_GetEvent_TaskID() contains the TaskType 'TaskID' passed to GetEvent */
      /* OSError_GetEvent_Event() contains the EventMaskRefType 'Event' passed to GetEvent */
      break;
    case OSServiceId_GetISRID:
      /* Handle error from GetISRID */
      break;
    case OSServiceId_GetResource:
      /* Handle error from GetResource */
      /* OSError_GetResource_ResID() contains the ResourceType 'ResID' passed to GetResource */
      break;
    case OSServiceId_GetScheduleTableStatus:
      /* Handle error from GetScheduleTableStatus */
      /* OSError_GetScheduleTableStatus_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to GetScheduleTableStatus */
      /* OSError_GetScheduleTableStatus_ScheduleStatus() contains the ScheduleTableStatusRefType 'ScheduleStatus' passed to GetScheduleTableStatus */
      break;
    case OSServiceId_GetTaskID:
      /* Handle error from GetTaskID */
      /* OSError_GetTaskID_TaskID() contains the TaskRefType 'TaskID' passed to GetTaskID */
      break;
    case OSServiceId_GetTaskState:
      /* Handle error from GetTaskState */
      /* OSError_GetTaskState_TaskID() contains the TaskType 'TaskID' passed to GetTaskState */
      /* OSError_GetTaskState_State() contains the TaskStateRefType 'State' passed to GetTaskState */
      break;
    case OSServiceId_GetVersionInfo:
      /* Handle error from GetVersionInfo */
      break;
    case OSServiceId_IncrementCounter:
      /* Handle error from IncrementCounter */
      /* OSError_IncrementCounter_CounterID() contains the CounterType 'CounterID' passed to IncrementCounter */
      break;
    case OSServiceId_NextScheduleTable:
      /* Handle error from NextScheduleTable */
      /* OSError_NextScheduleTable_ScheduleTableID_From() contains the ScheduleTableType 'ScheduleTableID_From' passed to NextScheduleTable */
      /* OSError_NextScheduleTable_ScheduleTableID_To() contains the ScheduleTableType 'ScheduleTableID_To' passed to NextScheduleTable */
      break;
    case OSServiceId_Os_GetExecutionTime:
      /* Handle error from Os_GetExecutionTime */
      break;
    case OSServiceId_Os_GetISRMaxExecutionTime:
      /* Handle error from Os_GetISRMaxExecutionTime */
      /* OSError_Os_GetISRMaxExecutionTime_ISRID() contains the ISRType 'ISRID' passed to Os_GetISRMaxExecutionTime */
      break;
    case OSServiceId_Os_GetTaskActivationTime:
      /* Handle error from Os_GetTaskActivationTime */
      /* OSError_Os_GetTaskActivationTime_TaskID() contains the TaskType 'TaskID' passed to Os_GetTaskActivationTime */
      /* OSError_Os_GetTaskActivationTime_Value() contains the Os_StopwatchTickRefType 'Value' passed to Os_GetTaskActivationTime */
      break;
    case OSServiceId_Os_GetTaskMaxExecutionTime:
      /* Handle error from Os_GetTaskMaxExecutionTime */
      /* OSError_Os_GetTaskMaxExecutionTime_TaskID() contains the TaskType 'TaskID' passed to Os_GetTaskMaxExecutionTime */
      break;
    case OSServiceId_Os_ResetISRMaxExecutionTime:
      /* Handle error from Os_ResetISRMaxExecutionTime */
      /* OSError_Os_ResetISRMaxExecutionTime_ISRID() contains the ISRType 'ISRID' passed to Os_ResetISRMaxExecutionTime */
      break;
    case OSServiceId_Os_ResetTaskMaxExecutionTime:
      /* Handle error from Os_ResetTaskMaxExecutionTime */
      /* OSError_Os_ResetTaskMaxExecutionTime_TaskID() contains the TaskType 'TaskID' passed to Os_ResetTaskMaxExecutionTime */
      break;
    case OSServiceId_Os_GetElapsedTime:
      /* Handle error from Os_GetElapsedTime */
      break;
    case OSServiceId_Os_GetTaskElapsedTime:
      /* Handle error from Os_GetTaskElapsedTime */
      /* OSError_Os_GetTaskElapsedTime_TaskID() contains the TaskType 'TaskID' passed to Os_GetTaskElapsedTime */
      break;
    case OSServiceId_Os_GetISRElapsedTime:
      /* Handle error from Os_GetISRElapsedTime */
      /* OSError_Os_GetISRElapsedTime_ISRID() contains the ISRType 'ISRID' passed to Os_GetISRElapsedTime */
      break;
    case OSServiceId_Os_GetIdleElapsedTime:
      /* Handle error from Os_GetIdleElapsedTime */
      /* OSError_Os_GetIdleElapsedTime_IdleID() contains the Os_IdleType 'IdleID' passed to Os_GetIdleElapsedTime */
      break;
    case OSServiceId_Os_ResetTaskElapsedTime:
      /* Handle error from Os_ResetTaskElapsedTime */
      /* OSError_Os_ResetTaskElapsedTime_TaskID() contains the TaskType 'TaskID' passed to Os_ResetTaskElapsedTime */
      break;
    case OSServiceId_Os_ResetISRElapsedTime:
      /* Handle error from Os_ResetISRElapsedTime */
      /* OSError_Os_ResetISRElapsedTime_ISRID() contains the ISRType 'ISRID' passed to Os_ResetISRElapsedTime */
      break;
    case OSServiceId_Os_ResetIdleElapsedTime:
      /* Handle error from Os_ResetIdleElapsedTime */
      /* OSError_Os_ResetIdleElapsedTime_IdleID() contains the Os_IdleType 'IdleID' passed to Os_ResetIdleElapsedTime */
      break;
    case OSServiceId_Os_GetStackSize:
      /* Handle error from Os_GetStackSize */
      /* OSError_Os_GetStackSize_Base() contains the StackValueType 'Base' passed to Os_GetStackSize */
      /* OSError_Os_GetStackSize_Sample() contains the StackValueType 'Sample' passed to Os_GetStackSize */
      break;
    case OSServiceId_Os_GetStackUsage:
      /* Handle error from Os_GetStackUsage */
      break;
    case OSServiceId_Os_GetStackValue:
      /* Handle error from Os_GetStackValue */
      break;
    case OSServiceId_Os_GetISRMaxStackUsage:
      /* Handle error from Os_GetISRMaxStackUsage */
      /* OSError_Os_GetISRMaxStackUsage_ISRID() contains the ISRType 'ISRID' passed to Os_GetISRMaxStackUsage */
      break;
    case OSServiceId_Os_GetTaskMaxStackUsage:
      /* Handle error from Os_GetTaskMaxStackUsage */
      /* OSError_Os_GetTaskMaxStackUsage_TaskID() contains the TaskType 'TaskID' passed to Os_GetTaskMaxStackUsage */
      break;
    case OSServiceId_Os_ResetISRMaxStackUsage:
      /* Handle error from Os_ResetISRMaxStackUsage */
      /* OSError_Os_ResetISRMaxStackUsage_ISRID() contains the ISRType 'ISRID' passed to Os_ResetISRMaxStackUsage */
      break;
    case OSServiceId_Os_ResetTaskMaxStackUsage:
      /* Handle error from Os_ResetTaskMaxStackUsage */
      /* OSError_Os_ResetTaskMaxStackUsage_TaskID() contains the TaskType 'TaskID' passed to Os_ResetTaskMaxStackUsage */
      break;
    case OSServiceId_ReleaseResource:
      /* Handle error from ReleaseResource */
      /* OSError_ReleaseResource_ResID() contains the ResourceType 'ResID' passed to ReleaseResource */
      break;
    case OSServiceId_Restart:
      /* Handle error from Restart */
      break;
    case OSServiceId_ResumeAllInterrupts:
      /* Handle error from ResumeAllInterrupts */
      break;
    case OSServiceId_ResumeOSInterrupts:
      /* Handle error from ResumeOSInterrupts */
      break;
    case OSServiceId_Schedule:
      /* Handle error from Schedule */
      break;
    case OSServiceId_SetEvent:
      /* Handle error from SetEvent */
      /* OSError_SetEvent_TaskID() contains the TaskType 'TaskID' passed to SetEvent */
      /* OSError_SetEvent_Mask() contains the EventMaskType 'Mask' passed to SetEvent */
      break;
    case OSServiceId_SetAbsAlarm:
      /* Handle error from SetAbsAlarm */
      /* OSError_SetAbsAlarm_AlarmID() contains the AlarmType 'AlarmID' passed to SetAbsAlarm */
      /* OSError_SetAbsAlarm_start() contains the TickType 'start' passed to SetAbsAlarm */
      /* OSError_SetAbsAlarm_cycle() contains the TickType 'cycle' passed to SetAbsAlarm */
      break;
    case OSServiceId_SetRelAlarm:
      /* Handle error from SetRelAlarm */
      /* OSError_SetRelAlarm_AlarmID() contains the AlarmType 'AlarmID' passed to SetRelAlarm */
      /* OSError_SetRelAlarm_increment() contains the TickType 'increment' passed to SetRelAlarm */
      /* OSError_SetRelAlarm_cycle() contains the TickType 'cycle' passed to SetRelAlarm */
      break;
    case OSServiceId_SetRestartPoint:
      /* Handle error from SetRestartPoint */
      break;
    case OSServiceId_ShutdownOS:
      /* Handle error from ShutdownOS */
      break;
    case OSServiceId_StartOS:
      /* Handle error from StartOS */
      break;
    case OSServiceId_StartScheduleTableAbs:
      /* Handle error from StartScheduleTableAbs */
      /* OSError_StartScheduleTableAbs_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to StartScheduleTableAbs */
      /* OSError_StartScheduleTableAbs_Start() contains the TickType 'Start' passed to StartScheduleTableAbs */
      break;
    case OSServiceId_StartScheduleTableRel:
      /* Handle error from StartScheduleTableRel */
      /* OSError_StartScheduleTableRel_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to StartScheduleTableRel */
      /* OSError_StartScheduleTableRel_Offset() contains the TickType 'Offset' passed to StartScheduleTableRel */
      break;
    case OSServiceId_StartScheduleTableSynchron:
      /* Handle error from StartScheduleTableSynchron */
      /* OSError_StartScheduleTableSynchron_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to StartScheduleTableSynchron */
      break;
    case OSServiceId_SyncScheduleTable:
      /* Handle error from SyncScheduleTable */
      /* OSError_SyncScheduleTable_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to SyncScheduleTable */
      /* OSError_SyncScheduleTable_Value() contains the TickType 'Value' passed to SyncScheduleTable */
      break;
    case OSServiceId_SyncScheduleTableRel:
      /* Handle error from SyncScheduleTableRel */
      /* OSError_SyncScheduleTableRel_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to SyncScheduleTableRel */
      /* OSError_SyncScheduleTableRel_RelativeValue() contains the SignedTickType 'RelativeValue' passed to SyncScheduleTableRel */
      break;
    case OSServiceId_SetScheduleTableAsync:
      /* Handle error from SetScheduleTableAsync */
      /* OSError_SetScheduleTableAsync_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to SetScheduleTableAsync */
      break;
    case OSServiceId_StopScheduleTable:
      /* Handle error from StopScheduleTable */
      /* OSError_StopScheduleTable_ScheduleTableID() contains the ScheduleTableType 'ScheduleTableID' passed to StopScheduleTable */
      break;
    case OSServiceId_SuspendAllInterrupts:
      /* Handle error from SuspendAllInterrupts */
      break;
    case OSServiceId_SuspendOSInterrupts:
      /* Handle error from SuspendOSInterrupts */
      break;
    case OSServiceId_TerminateApplication:
      /* Handle error from TerminateApplication */
      /* OSError_TerminateApplication_Application() contains the ApplicationType 'Application' passed to TerminateApplication */
      /* OSError_TerminateApplication_RestartOption() contains the RestartType 'RestartOption' passed to TerminateApplication */
      break;
    case OSServiceId_TerminateTask:
      /* Handle error from TerminateTask */
      break;
    case OSServiceId_WaitEvent:
      /* Handle error from WaitEvent */
      /* OSError_WaitEvent_Mask() contains the EventMaskType 'Mask' passed to WaitEvent */
      break;
    case OSServiceId_AllowAccess:
      /* Handle error from AllowAccess */
      break;
    case OSServiceId_GetApplicationState:
      /* Handle error from GetApplicationState */
      /* OSError_GetApplicationState_Application() contains the ApplicationType 'Application' passed to GetApplicationState */
      /* OSError_GetApplicationState_Value() contains the ApplicationStateRefType 'Value' passed to GetApplicationState */
      break;
    default:
      /* Never here */
      break;
  }
#endif /* OSErrorGetServiceId */
}
/* [MISRA 2012 Rule 20.1] */ /*lint -save -estring(9019, *) */
#define OS_STOP_SEC_ERRORHOOK_CODE
#include "Os_MemMap.h" /* [MISRA 2012 Dir 4.10] */ /*lint !e537 !e451 */
/*lint -restore */


