


#ifndef ECUM_H
#define ECUM_H

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/

#include "Std_Types.h" /*Rule BSW_HeaderInc_004:*/


#include "EcuM_Types.h" /* Required for EcuM exported data types */
#include "EcuM_Generated_Types.h" /* specified in SWS. */

#include "EcuM_Cfg_Version.h" /*Version details for the implementation*/

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE != FALSE)
#include "SchM_EcuM.h"  /*Includes declaration for Main Function */
#include "Rte_EcuM_Type.h" /*Rule BSW_ServiceRTE_002 for rte generated EcuM types*/
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE

#include "EcuM_Cfg_RbExt.h" /*Required for including user configured file */
#include "EcuM_Cfg_RbMo.h" /*For Monitoring relevent api's*/
#include "EcuM_Cfg_PbExt.h"

#include "EcuM_Cbk.h" /*Callback headers*/

/***************************************************************************************************
 * Fix Type declarations
 ***************************************************************************************************/

/* wakeup status modes */
#define ECUM_WKSTATUS_NONE      0
#define ECUM_WKSTATUS_PENDING   1
#define ECUM_WKSTATUS_VALIDATED 2
#define ECUM_WKSTATUS_EXPIRED   3
#define ECUM_WKSTATUS_DISABLED  4

/* EcuM_RunStatusType*/

#define ECUM_RUNSTATUS_UNKNOWN                           (EcuM_RunStatusType)(0U)
#define ECUM_RUNSTATUS_REQUESTED                         (EcuM_RunStatusType)(1U)
#define ECUM_RUNSTATUS_RELEASED                           (EcuM_RunStatusType)(2U)

/*EcuM_StateType*/

#define ECUM_SUBSTATE_MASK                   (EcuM_StateType)(0x0fU)
#define ECUM_STATE_STARTUP                   (EcuM_StateType)(0x10U)
#define ECUM_STATE_RUN                       (EcuM_StateType)(0x30U)
#define ECUM_STATE_APP_RUN                   (EcuM_StateType)(0x32U)
#define ECUM_STATE_APP_POST_RUN              (EcuM_StateType)(0x33U)
#define ECUM_STATE_SHUTDOWN                  (EcuM_StateType)(0x40U)
#define ECUM_STATE_SLEEP                     (EcuM_StateType)(0x50U)


#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)

#define Rte_Switch_currentMode_EcuM_Mode(data) ( ((VAR(Std_ReturnType, AUTOMATIC))RTE_E_OK) )

#define Rte_Mode_currentMode_EcuM_Mode()  (RTE_MODE_EcuM_Mode_STARTUP)

#define RTE_E_OK               ((Std_ReturnType)0u)
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE
/*
**********************************************************************************************************************
* Variables
**********************************************************************************************************************
*/
#if (ECUM_STARTUP_DURATION == TRUE) /*will activate the Run time measurement*/
#define ECUM_START_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"
/*To store the time taken for shutdown / reset*/
extern VAR( uint32, ECUM_VAR ) EcuM_Shutdown_delta_us_u32;
#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
extern VAR( EcuM_TimeTicks_tu64, ECUM_VAR ) EcuM_Shutdown_begin_ticks_u64;
extern VAR( EcuM_TimeTicks_tu64, ECUM_VAR ) EcuM_Shutdown_end_ticks_u64;
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
#endif//ECUM_STARTUP_DURATION

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#define ECUM_START_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
/* Structure array block of shutdown info. This is stored in RAM */
extern VAR( EcuM_ShutdownTargetInfoType, ECUM_VAR_SAVED_ZONE0_UNSPECIFIED ) EcuM_Rb_dataShutdownInfo_st;
#define ECUM_STOP_SEC_VAR_SAVED_ZONE0_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
/***************************************************************************************************
 * Function Prototypes
 ***************************************************************************************************/

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

extern FUNC(void, ECUM_CODE) EcuM_MainFunction(void);

#else//ECUM_CFG_ECUC_RB_RTE_IN_USE


/***************************************************************************************************
 * Function Prototypes
 ***************************************************************************************************/

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE

extern FUNC(void, ECUM_CODE) EcuM_Init(void);

extern FUNC(void, ECUM_CODE) EcuM_StartupTwo(void);

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDown(VAR(uint16, AUTOMATIC) caller);

extern FUNC(void , ECUM_CODE) EcuM_Shutdown(void );

extern FUNC(EcuM_WakeupSourceType,ECUM_CODE) EcuM_GetValidatedWakeupEvents(void);

extern FUNC( EcuM_WakeupSourceType, ECUM_CODE ) EcuM_GetExpiredWakeupEvents( void );

extern FUNC( EcuM_WakeupSourceType, ECUM_CODE ) EcuM_GetPendingWakeupEvents( void );

#if (ECUM_SLEEP_SUPPORT_ENABLE != FALSE)
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoHalt(void);
#endif//ECUM_SLEEP_SUPPORT_ENABLE

extern FUNC(void , ECUM_CODE) EcuM_ClearWakeupEvent (VAR(EcuM_WakeupSourceType, AUTOMATIC) sources);

extern  FUNC(void, ECUM_CODE) EcuM_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, ECUM_APPL_DATA) versioninfo);

extern  FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectBootTarget(VAR(EcuM_BootTargetType, AUTOMATIC) target);

extern  FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetBootTarget(P2VAR(EcuM_BootTargetType, AUTOMATIC, ECUM_APPL_DATA)target);

extern FUNC( Std_ReturnType, ECUM_CODE ) EcuM_GetShutdownTarget(
                                        P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
                                        P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode);

extern FUNC( Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownTarget(
                                        VAR(EcuM_ShutdownTargetType, AUTOMATIC) shutdownTarget,
                                        VAR(EcuM_ShutdownModeType, AUTOMATIC) shutdownMode );

extern FUNC( Std_ReturnType, ECUM_CODE ) EcuM_SelectShutdownCause( VAR(EcuM_ShutdownCauseType, AUTOMATIC) shutdownCause );

extern FUNC( Std_ReturnType, ECUM_CODE ) EcuM_GetShutdownCause(
                                        P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause );

extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetLastShutdownTarget(
                                        P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
                                        P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode );

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
extern FUNC(Std_ReturnType, ECUM_CODE) EcuM_Rb_NvMSingleBlockCallbackFunction (
                                        VAR(uint8, AUTOMATIC) ServiceId,
                                        VAR(uint8, AUTOMATIC) JobResult);
FUNC( Std_ReturnType, ECUM_CODE ) EcuM_Rb_GetLastShutdownInfo(
        P2VAR(EcuM_ShutdownInfoType, AUTOMATIC, ECUM_APPL_DATA) shutdownCauseInfo);
#endif

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

extern FUNC( Std_ReturnType, ECUM_CODE ) EcuM_RequestRUN( VAR(EcuM_UserType, AUTOMATIC) user );

extern FUNC( Std_ReturnType, ECUM_CODE ) EcuM_ReleaseRUN( VAR(EcuM_UserType, AUTOMATIC) user );

extern FUNC( Std_ReturnType, ECUM_CODE ) EcuM_RequestPOST_RUN( VAR(EcuM_UserType, AUTOMATIC) user );

extern FUNC( Std_ReturnType, ECUM_CODE ) EcuM_ReleasePOST_RUN( VAR(EcuM_UserType, AUTOMATIC) user );

extern FUNC(void , ECUM_CODE) EcuM_SetState(VAR(EcuM_StateType, AUTOMATIC) state);

extern FUNC( void, ECUM_CODE ) EcuM_KillAllRUNRequests( void );

extern FUNC( void, ECUM_CODE ) EcuM_KillAllPostRUNRequests( void );

extern FUNC( void, ECUM_CODE ) EcuM_Rb_KillAllRequests( void );

extern FUNC( void , ECUM_CODE ) EcuM_Rb_CurrentState ( void );

#endif//ECUM_CFG_MODE_HANDLING

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"


#endif /*ECUM_H*/
