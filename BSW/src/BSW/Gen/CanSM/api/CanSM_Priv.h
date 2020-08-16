
#ifndef  CANSM_PRIV_H
#define  CANSM_PRIV_H

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Cfg_SchM.h"
#include "CanSM.h"
#include "BswM_CanSM.h"
#include "Dem.h"
#include "CanSM_Cbk.h"
#include "CanSM_ComM.h"
#include "CanSM_GetBusOffDelay_Cbk.h"
#include "CanSM_TxTimeoutException.h"
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#include "CanNM.h"
#endif
#if(CANSM_DEV_ERROR_DETECT != STD_OFF)
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != CANSM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != CANSM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/* Indicates busoff recovery process is allowed */
#define CANSM_RECOVERY_ENABLED   1u

/* Indicates busoff recovery process is not allowed */
#define CANSM_RECOVERY_DISABLED  2u

/* Mutex Macros */
#define CANSM_MUTEX_FREE  1u

#define CANSM_MUTEX_BUSY  2u

/* Invalid Network index */
#define CANSM_NETWORKIDX_ERROR  255u

/*Indicates the zero value*/
#define CANSM_ZERO   0u

/*Indicates the initialization*/
#define CANSM_INITED  0x0u

/*Indicates the uninitialization*/
#define CANSM_UNINITED  0x1u

/*Macro for internal use*/
#define CANSM_FALSE  0x0u

/*Macro for internal use*/
#define CANSM_TRUE   0x01u

#define CANSM_DEM_DISABLED  0xffff

/* Check whether given condition is satisfied, call Det_ReportError() */
#if CANSM_DEV_ERROR_DETECT != STD_OFF
     /*Macro For functions with return type as 'void'*/
    #define CANSM_REPORT_ERROR(CONDITION, API, ERROR)                                                       \
                                   if(CONDITION)                                                            \
                                   {                                                                        \
                                        (void)Det_ReportError((CANSM_MODULE_ID), (0u), (API), (ERROR));     \
                                        return;                                                             \
                                   }


     /*Macro For functions with return type as 'Std_ReturnType'*/
    #define CANSM_REPORT_ERROR_NOK(CONDITION, API, ERROR)                                                   \
                                   if(CONDITION)                                                            \
                                   {                                                                        \
                                        (void)Det_ReportError((CANSM_MODULE_ID), (0u), (API), (ERROR));     \
                                        return E_NOT_OK;                                                    \
                                   }

#else
    #define CANSM_REPORT_ERROR(CONDITION, API, ERROR)

    #define CANSM_REPORT_ERROR_NOK(CONDITION, API, ERROR)

#endif

/* Macro for Releasing Mutex. No Interrupt Protection required for Releasing the Mutex beacuse the Thread(Process) has already accquired the Mutex*/
#define CanSM_ReleaseMutex(Indx_Network)           \
/* Set Mutex to FREE */                            \
CanSM_MutexMode_au8[Indx_Network] = CANSM_MUTEX_FREE;  \


/*********************Timer Related Macros*********************************************************/

/* Init Timer Macro for all Networks */
#define CanSM_InitTimer(Indx_Network)                                 \
do                                                                    \
{                                                                     \
    /* Initilaize the Timer Count */                                  \
    CanSM_TimerConfig_ast[Indx_Network].cntTick_u16 = 0;                \
    /* Set the State to INIT Mode */                                  \
    CanSM_TimerConfig_ast[Indx_Network].stTimer = CANSM_TIMER_INIT;     \
}while(0)


/* Start Timer Macro for all Networks */
#define CanSM_StartTimer(Indx_Network)                                \
do                                                                    \
{                                                                     \
    /* Initilaize the Timer Count */                                  \
    CanSM_TimerConfig_ast[Indx_Network].cntTick_u16 = 0;                \
    /* Set the State to RUNNING Mode */                               \
    CanSM_TimerConfig_ast[Indx_Network].stTimer = CANSM_TIMER_RUNNING;  \
}while(0)
/******************************/

/*Pointer to the active config set*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern P2CONST(CanSM_ConfigType, CANSM_VAR, CANSM_APPL_CONST) CanSM_ConfigSet_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"


/* FC_VariationPoint_START */
/*Pointer to the DSM Configuration*/
#if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern P2VAR(CanSM_NetworkConf_DEM_tst, CANSM_VAR, CANSM_APPL_DATA) CanSM_NetworkDem_pst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif
/* FC_VariationPoint_END */

/*Pointer to the Active network configuration*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern P2CONST(CanSM_NetworkConf_tst, CANSM_VAR, CANSM_APPL_CONST) CanSM_Network_pcst;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */
/*This enum is used for PRE_NOCOM (with and without PN support) substates*/
typedef enum
{
    CANSM_DEFAULT,
    CANSM_S_CC_STOPPED ,
    CANSM_S_PN_CC_STOPPED ,
    CANSM_S_CC_STOPPED_WAIT,
    CANSM_S_PN_CC_STOPPED_WAIT,
    CANSM_S_CC_SLEEP,
    CANSM_S_PN_CC_SLEEP,
    CANSM_S_CC_SLEEP_WAIT,
    CANSM_S_PN_CC_SLEEP_WAIT,
    CANSM_S_TRCV_NORMAL,
    CANSM_S_PN_TRCV_NORMAL,
    CANSM_S_TRCV_NORMAL_WAIT,
    CANSM_S_PN_TRCV_NORMAL_WAIT,
    CANSM_S_TRCV_STANDBY,
    CANSM_S_PN_TRCV_STANDBY,
    CANSM_S_TRCV_STANDBY_WAIT,
    CANSM_S_PN_TRCV_STANDBY_WAIT,
    CANSM_S_PN_CLEAR_WUF ,
    CANSM_S_PN_CLEAR_WUF_WAIT,
    CANSM_S_CHECK_WFLAG_IN_CC_SLEEP,
    CANSM_S_CHECK_WFLAG_IN_CC_SLEEP_WAIT,
    CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP,
    CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP_WAIT
}CanSM_PreNoCom_Substates_ten;

/* To keep the track of stopping controllers in BOR*/
typedef enum
{
    CANSM_BOR_CONTROLLER_STOPPED_REQUEST  = 0,
    CANSM_BOR_CONTROLLER_STOPPED_WAIT     = 1,
    CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED = 2
}CanSM_BOR_Controller_Stopped_stateType_ten;

/*This enum is used for PRE_FULLCOM substates*/
typedef enum
{
    CANSM_PRE_FULLCOM_DEFAULT,
    CANSM_PRE_FULLCOM_S_TRCV_NORMAL,
    CANSM_PRE_FULLCOM_S_TRCV_NORMAL_WAIT,
    CANSM_PRE_FULLCOM_S_CC_STOPPED,
    CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT,
    CANSM_PRE_FULLCOM_S_CC_STARTED,
    CANSM_PRE_FULLCOM_S_CC_STARTED_WAIT

}CanSM_PreFullCom_Substates_ten;

/*This enum is used for WakeUpValidation substates*/
typedef enum
{
    CANSM_WAKEUP_VALIDATION_DEFAULT,
    CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL,
    CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL_WAIT,
    CANSM_WAKEUP_VALIDATION_S_CC_STOPPED,
    CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT,
    CANSM_WAKEUP_VALIDATION_S_CC_STARTED,
    CANSM_WAKEUP_VALIDATION_S_CC_STARTED_WAIT

}CanSM_WakeUpValidation_Substates_ten;

#if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
/*This enum is used for Baudrate substates*/
typedef enum
{
    CANSM_BR_DEFAULT,
    CANSM_BR_S_CC_STOPPED,
    CANSM_BR_S_CC_STOPPED_WAIT,
    CANSM_BR_S_CC_STARTED,
    CANSM_BR_S_CC_STARTED_WAIT,
    CANSM_BSM_CHANGE_BR_SYNC

}CanSM_ChangeBR_Substates_ten;
#endif

typedef enum
{
    CANSM_TxTimeoutException_DEFAULT,
    CANSM_TxTimeoutException_S_CC_STOPPED,
    CANSM_TxTimeoutException_S_CC_STOPPED_WAIT,
    CANSM_TxTimeoutException_S_CC_STARTED,
    CANSM_TxTimeoutException_S_CC_STARTED_WAIT

}CanSM_TxTimeoutException_Substates_ten;

/* Types of CAN Controller states */
typedef enum
{
    CANSM_ControllerState_UNINIT = 0,
    CANSM_ControllerState_STOPPED,
    CANSM_ControllerState_STARTED,
    CANSM_ControllerState_SLEEP
}CanSM_CANControllerStateType_ten;


/* Timer State Types */
typedef enum
{
    CANSM_TIMER_INIT        = 1,
    CANSM_TIMER_RUNNING     = 2,
    CANSM_TIMER_ELAPSED     = 3,
    CANSM_TIMER_CANCELLED   = 4

}CanSM_TimerStateType_ten;

typedef struct
{
    VAR(uint16, TYPEDEF)                 cntTick_u16;         /*Current Timer Tick Value*/
    VAR(CanSM_TimerStateType_ten, TYPEDEF)   stTimer;             /*State of the Timer*/

}CanSM_TimerConfig_tst;

/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */
/*Extern declaration at precompile time*/
#if(CANSM_VARIANT_INFO == CANSM_VARIANT_PRE_COMPILE)
#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"
extern const CanSM_NetworkConf_tst CanSM_Network_Config_acst[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"

#if (CANSM_DSM_REINIT_ENABLED != STD_OFF)
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern CanSM_NetworkConf_DEM_tst CanSM_Network_Dem_Config_ast[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
#endif

#define CANSM_START_SEC_CONST_8
#include "CanSM_MemMap.h"
extern const uint8 CanSM_NetworktoCtrl_Config_acu8[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_CONST_8
#include "CanSM_MemMap.h"

#endif

/*Timer Configuration*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_TimerConfig_tst, CANSM_VAR)  CanSM_TimerConfig_ast[CANSM_NUM_CAN_NETWORKS] ;
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*CanSM initialization indication flag*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_Init_ab;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/* Current Network Mode State */
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_NetworkModeStateType_ten, CANSM_VAR) CanSM_CurrNw_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/* Current BOR State */
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_BusOffRecoveryStateType_ten, CANSM_VAR) CanSM_currBOR_State_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*Busoff counter*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern VAR(uint8, CANSM_VAR) CanSM_BusOff_Cntr_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*Bus-Off State Machine Mode - Enable Recovery or Disable Recovery*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern VAR(uint8, CANSM_VAR) CanSM_BORMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*To track Bus Off Indications for the network*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_BusOff_Indicated_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"


/* Mutex Support for CanSM*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern VAR(uint8, CANSM_VAR) CanSM_MutexMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*Requested ComM Mode */

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(ComM_ModeType, CANSM_VAR) CanSM_ReqComM_Mode_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*Requested Ecum Mode */
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_Wuvalidation_Start_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/* Pending BusOff Recovery ISR*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_BusOffISRPend_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

#if (CANSM_CHANGE_BAUDRATE_API == STD_ON)
/*To hold the recent baudrate of the network*/
#define CANSM_START_SEC_VAR_CLEARED_32
#include "CanSM_MemMap.h"
extern VAR(uint32, CANSM_VAR) CanSM_ChangeBaudRate_Value_au32[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_32
#include "CanSM_MemMap.h"

/*To keep track of the status returned by CanSM_CheckBaudrate(), for each network*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_CheckBR_Status_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
#endif


#if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
/*To keep track of the substates in Change Baudrate, for each network*/
extern VAR(CanSM_ChangeBR_Substates_ten, CANSM_VAR) CanSM_ChangeBR_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#endif

/*To keep track of the the Baudrate Config Id for each network*/
#if(CANSM_SET_BAUDRATE_API == STD_ON)
/*To hold the BaudrateConfigID*/
#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
extern VAR(uint16, CANSM_VAR) CanSM_BaudRateConfigID_Value_au16[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

#endif

/*To keep track of unsuccessful attempts for mode change request received for each network ie T_REPEAT_MAX counter*/
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern VAR(uint8, CANSM_VAR) CanSM_Num_Unsuccessful_ModeReq_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

/*To keep track of Transceiver mode indication received*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_Trcv_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*To keep track of Controller mode indication received*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_Ctrl_ModeInd_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*To keep track of the substates in Prepare to NOCOM for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_PreNoCom_Substates_ten, CANSM_VAR) CanSM_PreNoCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the call backs checkwakeupflag() and clearwakeupflag() have happened or not . Nothing to do with any PN indications*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_PN_Substate_Ind_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*Array to hold the last value notified to ComM_BusSM_ModeIndication()*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(ComM_ModeType, CANSM_VAR) CanSM_BusSMMode_au8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the substates in Prepare to FULL COM for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_PreFullCom_Substates_ten, CANSM_VAR) CanSM_PreFullCom_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the substates in Wake Up Validation for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_WakeUpValidation_Substates_ten, CANSM_VAR) CanSM_WakeUpValidation_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*To keep track of the substates in Tx Timeout exception, for each network*/
#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_TxTimeoutException_Substates_ten, CANSM_VAR) CanSM_TxTimeoutexception_Substates_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/* Specifies in which time duration the CanSM module shall repeat mode change requests by using the API of the CanIf module*/
#define CANSM_START_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"
extern VAR(uint16, CANSM_VAR)  CanSM_ModeRepeatReq_Time_u16;
#define CANSM_STOP_SEC_VAR_CLEARED_16
#include "CanSM_MemMap.h"

/* Holds Maximal amount of mode request repetitions without a respective mode indication */
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern VAR(uint8, CANSM_VAR)   CanSM_ModeRepeatReq_Max_u8;
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_CANControllerStateType_ten, CANSM_VAR)CanSM_ControllerState_en[CANSM_NUM_CAN_CONTROLLERS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

/*CanSM initialization indication flag*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_Network_Init_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

/*CAN ontrollers mode indications*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_ControllerIndications_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"

#define CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"
extern VAR(CanSM_BOR_Controller_Stopped_stateType_ten, CANSM_VAR)CanSM_BOR_Controller_Stopped_state_en[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanSM_MemMap.h"

#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
/*Variable to hold the value of input parameter*/
#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean , AUTOMATIC) CanSM_Passive_b;
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
#endif

/* FC_VariationPoint_START */

#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_Rb_DisableBusOffRecovery_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
/* FC_VariationPoint_END */

#define CANSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
extern VAR(boolean, CANSM_VAR) CanSM_BOR_SilentCom_ab[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "CanSM_MemMap.h"
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
extern FUNC(void, CANSM_CODE) CanSM_DeInitPnSupported(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_CheckWakeUpFlagInSleep(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_CheckWakeUpFlagNotInSleep(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_PN_ClearWufTrcv(VAR(NetworkHandleType, AUTOMATIC) network);
#endif

#if(CANSM_CHANGE_BAUDRATE_API == STD_ON)
extern FUNC(void, CANSM_CODE) CanSM_ChangeBaudrate_StateMachine(VAR(NetworkHandleType, AUTOMATIC) network);
#endif

#if(CANSM_SET_BAUDRATE_API == STD_ON)
extern FUNC(void, CANSM_CODE) CanSM_SetBaudrate_StateMachine(VAR(NetworkHandleType, AUTOMATIC) network);
#endif
extern FUNC(void, CANSM_CODE) CanSM_DeInitPnNotSupported(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_StopCtrl(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_StartCtrl(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_SleepCtrl(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_NormalTrcv(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_StandbyTrcv(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_NO2FULL_COM(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_FULL2SILENT_COM(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_SILENT2FULL_COM(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_TxTimeoutException_StateMachine(VAR(NetworkHandleType, AUTOMATIC) Channel);
extern FUNC(void, CANSM_CODE) CanSM_NetworkModeTrans( VAR(NetworkHandleType, AUTOMATIC) network,VAR(ComM_ModeType, AUTOMATIC) ComM_Mode);
#if (CANSM_BOR_TX_CONFIRMATION_POLLING != STD_OFF)
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckTxRxNotification(VAR(NetworkHandleType, AUTOMATIC) network);
#endif
extern FUNC(NetworkHandleType, CANSM_CODE) CanSM_GetHandle(VAR(NetworkHandleType, AUTOMATIC) ComMChannelId);
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetMutex(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_BusOffTransitions(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_BOR_MultipleCtrlsStop(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_BOR_CtrlsStart(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_ChangeBR_Exit(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_BOR_CtrlsStart_SilentCom(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(void, CANSM_CODE) CanSM_WakeUpValidation_StateMachine(VAR(NetworkHandleType, AUTOMATIC) network);

#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif  /*CANSM_PRIV_H*/
