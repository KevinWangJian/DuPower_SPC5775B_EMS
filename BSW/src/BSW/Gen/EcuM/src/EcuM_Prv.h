

#ifndef ECUM_PRV_H
#define ECUM_PRV_H

/*
 ***************************************************************************************************
 * Preprocessor includes
 ***************************************************************************************************
 */

#include "EcuM_Cfg_Startup.h"
/*
 ***************************************************************************************************
 * Preprocessor Defines
 ***************************************************************************************************
 */

/* Interface API IDs for DET interface*/
#define ECUM_MODULE_ID                  (10U)
#define ECUM_INSTANCE_ID                (0U)
#define ECUM_GETVERINFO_APIID           (0x00U)
#define ECUM_GODOWN_APIID               (0x1fU)
#define ECUM_INIT_APIID                 (0x01U)
#define ECUM_START_TWO_APIID            (0x1aU)
#define ECUM_SHUTDOWN_APIID             (0x02U)
#define ECUM_SELECT_SHUT_TAR_APIID      (0x06U)
#define ECUM_GET_SHUT_TAR_APIID         (0x09U)
#define ECUM_SELECT_SHUT_CAUSE_APIID    (0x1bU)
#define ECUM_GET_SHUT_CAUSE_APIID       (0x1cU)
#define ECUM_LAST_SHUT_TAR_APIID        (0x08U)
#define ECUM_GET_PEND_APIID             (0x0dU)
#define ECUM_CLEAR_WKEVENT_APIID        (0x16U)
#define ECUM_GET_VALIDATE_APIID         (0x15U)
#define ECUM_GET_EXPIRED_APIID          (0x19U)
#define ECUM_SEL_BOOT_APIID             (0x12U)
#define ECUM_GET_BOOT_APIID             (0x13U)
#define ECUM_MAIN_FUNC_APIID            (0x18U)
#define ECUM_SET_WKEVENT_APIID          (0x0cU)
#define ECUM_VAL_WKEVENT_APIID          (0x14U)
#define ECUM_GOHALT_APIID               (0x20U)
#define ECUM_GOPOLL_APIID               (0x21U)
#define ECUM_RB_MO_GETACTIVEPBINDEX_APIID   (0x22U)
#define ECUM_RB_MO_INITCHECK_APIID      (0x23U)
#define ECUM_RB_MO_INITCHECKINV_APIID   (0x24U)
#define ECUM_LAST_SHUT_CAUSE_APIID      (0x30U)

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
#define ECUM_SETSTATE_APIID             (0x2BU)
#define ECUM_RB_CURRENTSTATE_APIID             (0x30U)
#define ECUM_REQUESTRUN_APIID           (0x03U)
#define ECUM_RELEASERUN_APIID           (0x04U)
#define ECUM_REQUESTPOST_RUN_APIID      (0x0aU)
#define ECUM_RELEASEPOST_RUN_APIID      (0x0bU)
#define ECUM_KILL_ALL_RUN_REQUESTS_APIID      (0x05U)
#define ECUM_KILL_ALL_POST_RUN_REQUESTS_APIID      (0x2aU)
#endif//ECUM_CFG_MODE_HANDLING

/*---------------------------Det error ids--------------------------------------------*/
/*(Non-AR) Error for GetResource api*/
#define ECUM_E_OS_GET_RESOURCE_FAILED                                   (0x05U)

/*(Non-AR) Error for ReleaseResource api*/
#define ECUM_E_OS_RELEASE_RESOURCE_FAILED                               (0x06U)
#define ECUM_E_UNINIT                                                   (0x10U)
#define ECUM_E_SERVICE_DISABLED                                         (0x11U)
#define ECUM_E_NULL_POINTER                                             (0x12U)
#define ECUM_E_INVALID_PAR                                              (0x13U)
/*Error ID for indicating failed read operation of NvM*/
#define ECUM_E_NVM_READ_FAILED                                          (0x1AU)
#define ECUM_E_PARAM_POINTER                                            (0x1BU)



#define ECUM_E_STATE_PAR_OUT_OF_RANGE                                   (0x16U)
#define ECUM_E_UNKNOWN_WAKEUP_SOURCE                                    (0x17U)
/*Error code for RAM hash check fail, during wakeup from sleep mode*/
#define ECUM_E_RAM_CHECK_FAILED                                         (0x19U)
#define ECUM_E_COREREADY_TIMEOUT_EXPIRED                                (0x04U)
/*Error if Shutdown service API's called after GoDown,GoHalt or GoPoll is initiated*/
#define ECUM_E_SHUTDOWN_INFO_UPDATED                                   (0xFEU)
/*Error code for Post build selected pointer, if it is inconsistent*/
#define ECUM_E_CONFIGURATION_DATA_INCONSISTENT                          (0x18U)
/*Error code for post build selected pointer, if it is NULL*/
#define ECUM_E_NULL_PTR_RETURNED                                        (0x30U)
/*Error code for post build selected pointer, if it is invalid. ie.) the pointer which is not generated from EcuM configset*/
#define ECUM_E_INVALID_PTR_RETURNED                                     (0x31U)
/*Error code for any core failed to start during EcuM Startup*/
#define ECUM_E_START_CORE_FAILED                                        (0x32U)

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
#define ECUM_E_MULTIPLE_RUN_REQUESTS                                    (0x14U)
#define ECUM_E_MISMATCHED_RUN_RELEASE                                   (0x15U)
#define ECUM_RB_E_ALL_RUN_REQUESTS_KILLED                               (0xffU)
#endif//ECUM_CFG_MODE_HANDLING

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
/*To distinguish between the singlecore and multicore operation*/
#define ECUM_SINGLE_CORE 0x00
#define ECUM_SLAVE_CORE  0x01
#define ECUM_MASTER_CORE 0x02
#endif//ECUM_SLEEP_SUPPORT_ENABLE

/* Phases of EcuM4.0 flex*/
#define ECUM_PRV_PHASE_START_PREOS                                       (0x01U)
#define ECUM_PRV_PHASE_START_POSTOS                                      (0x02U)
#define ECUM_PRV_PHASE_UP                                                (0x03U)
#define ECUM_PRV_PHASE_OFF_PREOS                                         (0x04U)
#define ECUM_PRV_PHASE_OFF_POSTOS                                        (0x05U)
#define ECUM_PRV_PHASE_SLEEP                                             (0x06U)


/*
 *
**************************************************************************************************
* Type Declarations
**************************************************************************************************
*/
#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
typedef enum
{
    ECUM_PRV_NO_SLEEP_E = 0,
    ECUM_PRV_GOPOLL_E =1,
    ECUM_PRV_GOHALT_E=2
} EcuM_Prv_SleepType_Enum_ten;

typedef enum
{
    ECUM_PRV_NORMAL_E = 0,
    ECUM_PRV_RESOURCE_NOT_ACQUIRED_E =1,
    ECUM_PRV_WAKEUP_REQUEST_E=2
} EcuM_Prv_WakeupRestartReason_Enum_ten;

typedef enum
{
    ECUM_PRV_HALT_SEQUENCE_E = 0,
    ECUM_PRV_RESTART_SEQUENCE_E =1,
    ECUM_PRV_CLEAR_SLEEP_E=2
} EcuM_Prv_OperationType_Enum_ten;


typedef struct
{
    uint8  CurrentCore;
    uint16 CurrentCoreID;
}EcuM_CurrentCoreInfoType;
#endif
/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************/
#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_Cfg_MemMap.h"
/* Variable to store the Selected Boot target*/
extern VAR(EcuM_BootTargetType,ECUM_VAR_POWER_ON_CLEARED_8)  EcuM_Prv_dataSelectedBootTarget_u8;
/* Variable which stores the informaition if EcuM_Prv_dataSelectedBootTarget_u8 has been set with EcuM_SelectBootTarget
 * This is needed because ECUM_START_SEC_VAR_POWER_ON_INIT_8 does not exist */
extern VAR(uint8,ECUM_VAR_POWER_ON_CLEARED_8)  EcuM_Prv_dataSelectedBootTargetInit_u8;

#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_VAR_CLEARED_8
#include "EcuM_Cfg_MemMap.h"

/*Tells the present Phase of the EcuM*/
extern VAR(uint8,ECUM_VAR_CLEARED_8)  EcuM_Prv_dataPresentPhase_u8;
extern VAR( uint8, ECUM_VAR_CLEARED_8 )  EcuM_Prv_SlaveCoreTimeoutCtr_u8;/*Timeout counter slave core during shutdown synchronization*/
/* Variable to store the selected Shutdown cause*/
extern VAR( EcuM_ShutdownCauseType, ECUM_VAR )  EcuM_Prv_dataSelectedShutdownCause_u8;

#if( ECUM_CFG_MODE_HANDLING == STD_ON)
/*Variable used to hold the status of Run Request/Release to notify the BswM as per Run handling protocol*/
extern VAR(uint8, ECUM_VAR_CLEARED_8) EcuM_Prv_RunRequested_u8;
/*Variable used to hold the status of Post_Run Request/Release to notify the BswM as per Run handling protocol*/
extern VAR(uint8, ECUM_VAR_CLEARED_8) EcuM_Prv_Post_Run_Requested_u8;

#endif //ECUM_CFG_MODE_HANDLING

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern VAR(EcuM_Prv_SleepType_Enum_ten, ECUM_VAR_CLEARED_8) EcuM_Prv_SleepReqType_en;
extern VAR(EcuM_Prv_WakeupRestartReason_Enum_ten, ECUM_VAR_CLEARED_8) EcuM_Prv_WakeupRestartReason_en;
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_VAR_CLEARED_8
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
/* Variable to store the selected Shutdown target*/
extern VAR(EcuM_ShutdownTargetInfoType, ECUM_VAR_CLEARED_UNSPECIFIED)   EcuM_Prv_dataSelectedShutdownTarget_st;

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern VAR( EcuM_CurrentCoreInfoType, ECUM_VAR ) EcuM_Prv_CoreStatus_st;
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"
/* Variable to store the Pending Wakeup Events*/
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 )  EcuM_Prv_dataPendingWakeupEvents_u32;
/*Variable to store the Old Pending Wakeup Events*/
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 )  EcuM_Prv_dataOldPendingWakeupEvents_u32;
/* Variable to store the Validated Wakeup Events*/
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 )  EcuM_Prv_dataValidatedWakeupEvents_u32;
/* Variable to store the Expired Wakeup Events*/
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 )  EcuM_Prv_dataExpiredWakeupEvents_u32;
/* Variable to store the Cleared Wakeup Events*/
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataClrWkpEventsInd_u32;
/* Variable to store the Pending Wakeup Events for BswM indincation*/
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataPndWkpEventsInd_u32;
/* Variable to store the Validated Wakeup Events for BswM indincation*/
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataValWkpEventsInd_u32;
/* Variable to store the Clear Wakeup Events */
extern VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 )EcuM_Prv_dataExpWkpEventsInd_u32;

#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_16
#include "EcuM_Cfg_MemMap.h"
/* Variable to store the wake up validation Timeout Timer */
extern VAR( uint16, ECUM_VAR_CLEARED_16 )  EcuM_Prv_WkpSrcValidationTimeoutCtr_u16;
#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern VAR( EcuM_ShutdownModeType, ECUM_VAR ) EcuM_Prv_SleepMode_u16;
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_VAR_CLEARED_16
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"

/*array used to hold the initalization status of startupTwo*/
extern VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_flgIsStartupTwoCalled_ab[ECUM_CFG_NUM_OS_CORES];
/*EcuM_Init is called or not*/
extern VAR(boolean,ECUM_VAR_CLEARED_BOOLEAN)  EcuM_Prv_flgIsModuleInitialised_b ;

extern VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_flgCoreReady_ab[ECUM_CFG_NUM_OS_CORES];
/* EcuM_Prv_isEcuMGoDownFailed_b -->to enable or disable shutdown info update.
 * If TRUE updating the shutdown info stack is not possible
If FALSE we are allowed to update the shutdown info stack  --> EcuM_Rb_dataShutdownInfo_st*/
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_isEcuMGoDownFailed_b;
/*Flag to indicate the updatability of shutdown info*/
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgShutdownInfoDoNotUpdate_b;
/*To indicate whether shutdown process can be started*/
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgGoDown_b;

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
/*Array of flag to maintain the RUN reuqest status of each user */
extern VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_userRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];

/*Array of flag to maintain the POST_RUN reuqest status of each user */
extern VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_userPostRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];

/*Variable used to hold the status of EcuM_KillAllRUNRequests*/
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_KillAllRUNRequests_b;
/*Variable used to hold the status of EcuM_KillAllPostRUNRequests*/
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_KillAllPostRUNRequests_b;
#endif//ECUM_CFG_MODE_HANDLING


#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
/*flag to determine whether the previous shutdown information has been copied successfully from NV RAM to EcuM
 * prv variable*/
extern VAR(boolean,ECUM_VAR_CLEARED_BOOLEAN)  EcuM_Prv_flgNvMReadStatus_b;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgwakeupRestart_b;
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgClearWakeupRestart_b;
extern VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_AllCoreSleepReady_b;
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
extern volatile VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_flgSleepReady_ab[ECUM_CFG_NUM_OS_CORES];
extern volatile VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_RAMCheckPassed_b;
#endif //ECUM_CFG_MULTICORE_ENABLED
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_INIT_16
#include "EcuM_Cfg_MemMap.h"

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
extern VAR( uint16, ECUM_VAR_INIT_16 ) EcuM_Prv_RunMinDuration_u16;
#endif//ECUM_CFG_MODE_HANDLING

#define  ECUM_STOP_SEC_VAR_INIT_16
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
/*The ptr to the EcuM whole config pb structure*/
extern P2CONST(EcuM_ConfigType, ECUM_VAR_POWER_ON_CLEARED_UNSPECIFIED, ECUM_APPL_CONST) EcuM_Rb_adrConfigPtr_st;
/* variable to hold the previous shutdown information */
extern VAR( EcuM_ShutdownTargetInfoType, ECUM_VAR_POWER_ON_CLEARED_UNSPECIFIED ) EcuM_Prv_dataShutdownInfo_st;
#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

extern FUNC( boolean, ECUM_CODE ) EcuM_Prv_hasCheckWakeupSourceGetHandle_b(
        VAR(EcuM_WakeupSourceType, AUTOMATIC) datasource_u32);
extern FUNC( void, ECUM_CODE ) EcuM_Prv_WakeupIndication(
        VAR(EcuM_WakeupSourceType, AUTOMATIC) dataPendingWakeupEvents_u32  );
extern FUNC( void, ECUM_CODE ) EcuM_Prv_DecValidationCtr( void );
extern FUNC( void, ECUM_CODE ) EcuM_Prv_PBPointerConsistencyCheck( void );
extern FUNC( void, ECUM_CODE ) EcuM_Prv_SetDefinedMcuWakeupSource( void );
extern FUNC( void, ECUM_CODE ) EcuM_Prv_StartOS(void);
extern FUNC(uint32, ECUM_CODE)EcuM_Prv_ComMWakeupHandling(VAR(EcuM_WakeupSourceType,AUTOMATIC )dataPendingWakeupEvents);

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
extern FUNC( boolean, ECUM_CODE ) EcuM_Prv_IsUserHandlingPossible_b(
        P2VAR(EcuM_UserType, AUTOMATIC, ECUM_APPL_DATA) user, VAR(uint8, AUTOMATIC) apiid);
#endif//ECUM_CFG_MODE_HANDLING

#if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
extern FUNC( void, ECUM_CODE ) EcuM_Prv_StartSlaveCores(void);
#endif//ECUM_CFG_MULTICORE_ENABLED

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
extern FUNC( void, ECUM_CODE ) EcuM_Prv_GoSleepSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16);
extern FUNC( void, ECUM_CODE ) EcuM_Prv_WakeupRestartSequence ( VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16 );
extern FUNC(StatusType, ECUM_CODE)EcuM_Prv_GetResource(VAR(CoreIdType, AUTOMATIC) core_ID);
extern FUNC(StatusType, ECUM_CODE)EcuM_Prv_ReleaseResource(VAR(CoreIdType, AUTOMATIC) core_ID);
#endif// ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"
#endif /*ECUM_PRV_H*/

