

#ifndef  CANSM_H
#define  CANSM_H

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Cfg.h"
#include "ComM.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/*********************************** DET Related error code *****************************************/

/* DET error definition for CanSM uninitialised */
#define CANSM_E_UNINIT                    0x01u

/* DET error definition for NULL POINTER is passed */
#define CANSM_E_PARAM_POINTER             0x02u

/* DET error definition for invalid network handle */
#define CANSM_E_INVALID_NETWORK_HANDLE    0x03u

/* DET error definition for invalid  Controller ID */
#define CANSM_E_PARAM_CONTROLLER          0x04u

/* DET error definition for invalid  tranceiver ID */
#define CANSM_E_PARAM_TRANSCEIVER         0x05u

/* DET error definition for error due to network request during pending indication */
#define CANSM_E_WAIT_MODE_INDICATION      0x07u

/* FC_VariationPoint_START */

/* DET error definition for invalid Baudrate Configuration */
#define CANSM_E_PARAM_INVALID_BAUDRATE    0x09u

/* FC_VariationPoint_END */

/* DET error definition for invalid  Mode request for a network failed */
#define CANSM_E_MODE_REQUEST_TIMEOUT      0x0Au

/* DET error definition for Null pointer in case of PBS */
#define CANSM_E_INIT_FAILED               0x0Cu

/*As per 4.0.2*/
/* DET error definition for error due to network mode request during bus off recovery */
#define CANSM_E_BUSOFF_RECOVERY_ACTIVE    0x06u

/* DET error definition for communication mode request */
#define CANSM_E_INVALID_COMM_REQUEST      0x08u

/*************************************Service Id's for the Api's***************************/

/* Service Id for CanSM_Init API */
#define CANSM_INIT_SID                       0x00u

/*Service Id for CanSM_GetVersionInfo API */
#define CANSM_GETVERSIONINFO_SID             0x01u

/* Service Id for CanSM_RequestComMode API */
#define CANSM_REQUESTCOMMODE_SID             0x02u

/* Service Id for CanSM_GetCurrentComMode API */
#define CANSM_GETCURRENTCOMMODE_SID          0x03u

/* Service Id for CanSM_ControllerBusOff API */
#define CANSM_CONTROLLERBUSOFF_SID           0x04u

/*Service Id for CanSM_MainFunction API */
#define CANSM_MAINFUNCTION_SID               0x05u

/* Service Id for CanSM_ConfirmPnAvailability API */
#define CANSM_CONFIRMPNAVAILABILITY_SID      0x06

/* Service Id for CanSM_ControllerModeIndication API */
#define CANSM_CTRLMODEINDICATION_SID         0x07u

/* Service Id for CanSM_CheckTransceiverWakeFlagIndication API */
#define CANSM_CLEARTRCVWUFFLAGIND_SID        0x08u

/* Service Id for CanSM_TransceiverModeIndication API */
#define CANSM_TRCVMODEINDICATION_SID         0x09u

/* Service Id for CanSM_CheckTransceiverWakeFlagIndication */
#define CANSM_CHECKTRCVWAKEFLAGIND_SID       0x0au

/* Service Id for CanSM_TxTimeoutException API */
#define CANSM_TXTIMEOUTEXCEPTION_SID         0x0bu

#if (CANSM_CHANGE_BAUDRATE_API == STD_ON)

/* Service Id for CanSM_CheckBaudrate API */
#define CANSM_CHECKBAUDRATE_SID              0x0cu

/* Service Id for CanSM_ChangeBaudrate API */
#define CANSM_CHANGEBAUDRATE_SID             0x0eu

#endif

/*Service Id for CanSM_StartWakeupSource API */
#define CANSM_STARTWAKEUPVALIDATION_SID      0x11u

/*Service Id for CanSM_StoptWakeupSource API */
#define CANSM_STOPWAKEUPVALIDATION_SID       0x12u

/*Service Id for CanSM_SetEcuPassive API */
#define CANSM_ECUPASSIVE_SID                 0x13u

#if (CANSM_SET_BAUDRATE_API == STD_ON)

/*Service Id for CanSM_SetBaudrate API */
#define CANSM_SETBAUDRATE_SID                0x0du

#endif

#define CANSM_GETBUSOFFDELAY_SID            0x0fu

/* Service Id for CanSM_GetBusoff_Substate API */
#define CANSM_GETBUSOFFSUBSTATE_SID          0x0Fu

/*Service Id for CanSM_GetNetworkMode_Substate API */
#define CANSM_GETNETWORKMODESUBSTATE_SID     0x11u


/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */
/* FC_VariationPoint_START */
#if (CANSM_DSM_REINIT_ENABLED != STD_OFF)
typedef struct
{
    VAR(uint8, TYPEDEF)                 DEMReinitFlag_u8;
    Dem_EventStatusType                 CanSM_DEM_Eventstatus_u8;
} CanSM_NetworkConf_DEM_tst;
#endif
/* FC_VariationPoint_END */

/*Network Configuration*/
typedef struct
{
    P2CONST(uint8, TYPEDEF, CANSM_APPL_DATA)Cntrl_startidx_pu8;
    VAR(Dem_EventIdType, TYPEDEF)BusOffEventId_uo;                      /* Dem EventID for a bus-off for a CanSM Network handle */

#if (CANSM_CALIBRATION == STD_ON)
    P2FUNC(uint16, TYPEDEF,pBorTimeL1_pfct)(void);                     /* address of Count Value for Bus-Off Recovery time in Level 1 */
    P2FUNC(uint16, TYPEDEF,pBorTimeL2_pfct)(void);                     /* address of Count Value for Bus-Off Recovery time in Level 2 */
#else
    VAR(uint16, TYPEDEF)                BorTimeL1_u16;                 /* Count Value for Bus-Off Recovery time in Level 1 */
    VAR(uint16, TYPEDEF)                BorTimeL2_u16;                 /* Count Value for Bus-Off Recovery time in Level 2 */
#endif
    VAR(uint16, TYPEDEF)                BorTimeTxEnsured_u16;          /* Value in Counts for No Bus Off Event Check */
    VAR(uint8, TYPEDEF)                 Trcv_hndle_u8;                 /* CAN Tranceiver Handle index */                /* Start Index of the Controllers */
    VAR(uint8, TYPEDEF)                 SizeofController_u8;           /* The number of Controllers present in the CanSM Network*/
    VAR(uint8, TYPEDEF)                 BorCntL1L2_u8;                 /* Count Value at which bus-off recovery state machine switches from level 1 to level 2 */
    VAR(NetworkHandleType, TYPEDEF)     ComM_channelId_uo;             /* ComM channel Id  */
#if (CANSM_BOR_TX_CONFIRMATION_POLLING != STD_OFF)
    VAR(boolean, TYPEDEF)               BorTxConfPolling_b;            /* Bus Off recovery based on Tx confirmation with polling*/
#endif
    VAR(boolean, TYPEDEF)               BusOffDelayConfig_b;           /*Boolean value to enable/disable bus off delay */
    VAR(boolean, TYPEDEF)               TrcvPnConfig_b;                /*partial Network enabled/disabled for Transceiver configured to CanSM Network*/
} CanSM_NetworkConf_tst;

/* Values of CANSM states for a Network  */
typedef enum
{
    CANSM_BSM_S_NOCOM = (ComM_ModeType)COMM_NO_COMMUNICATION,
    CANSM_BSM_S_SILENTCOM = (ComM_ModeType)COMM_SILENT_COMMUNICATION,
    CANSM_BSM_S_FULLCOM = (ComM_ModeType)COMM_FULL_COMMUNICATION,
    CANSM_BSM_S_NOT_INITIALIZED,
    CANSM_BSM_S_PRE_NOCOM,
    CANSM_BSM_WUVALIDATION,
    CANSM_BSM_S_PRE_FULLCOM,
    CANSM_BSM_S_CHANGE_BAUDRATE,
    CANSM_BSM_S_SILENTCOM_BOR,
    CANSM_BSM_S_TX_TIMEOUT_EXCEPTION
}CanSM_NetworkModeStateType_ten;

/*This enum is used for Bus off  substates*/
typedef enum
{
    CANSM_BOR_IDLE                  = 1,
    CANSM_S_BUS_OFF_CHECK           = 2,
    CANSM_S_NO_BUS_OFF              = 3,
    CANSM_S_BUS_OFF_RECOVERY_L1     = 4,
    CANSM_S_RESTART_CC              = 5,
    CANSM_S_RESTART_CC_WAIT         = 6,
    CANSM_S_BUS_OFF_RECOVERY_L2     = 7
}CanSM_BusOffRecoveryStateType_ten;

/* CanSMConfiguration Structure */
typedef struct
{
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC,CANSM_CONST) CanSM_NetworkConf_pcst;                           /* Pointer to Network Configuration structure */
    /* FC_VariationPoint_START */
    #if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
    P2VAR (CanSM_NetworkConf_DEM_tst, AUTOMATIC, CANSM_CONST ) CanSMNetworkConfDEM_pst;                         /* Pointer to DEM configuration structure based on CANSM_DSM_REINIT_ENABLED macro */
    #endif
    /* FC_VariationPoint_END */
    P2CONST (uint8, AUTOMATIC, CANSM_CONST ) CanSM_NetworktoCtrlConf_pcu8;                                      /* CanSm Network Index mapped to corresponding CAN controller */
    CONST(uint8, CANSM_CONST) CanSMModeRequestRepetitionMax_u8;                                                 /* Holds Maximal amount of mode request repetitions without a respective mode indication */
    CONST(uint16, CANSM_CONST) CanSMModeRequestRepetitionTime_u16;                                              /* Specifies in which time duration the CanSM module shall repeat mode change requests by using the API of the CanIf module*/
    VAR(uint8, CANSM_VAR)  CanSM_SizeOfCanSMNetworks_u8;                                                        /* Holds the number of Networks */
    VAR(uint8, CANSM_VAR)  CanSM_ActiveConfigset_u8;                                                            /* Active configset index */
}CanSM_ConfigType;

#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"
extern const CanSM_ConfigType CanSM_ConfigSet[];
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "CanSM_MemMap.h"
/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */
#define CANSM_START_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
extern VAR(uint8, CANSM_VAR) CanSM_GetBusOffDelay_Value_u8[CANSM_NUM_CAN_NETWORKS];
#define CANSM_STOP_SEC_VAR_CLEARED_8
#include "CanSM_MemMap.h"
/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"


#if (CANSM_ECUC_RB_RTE_IN_USE == STD_OFF)
extern FUNC(void, CANSM_CODE) CanSM_MainFunction(void);
#endif
extern FUNC(void, CANSM_CODE) CanSM_Init( const CanSM_ConfigType* ConfigPtr );
extern FUNC(void, CANSM_CODE) CanSM_GetVersionInfo( P2VAR(Std_VersionInfoType, AUTOMATIC, CANSM_APPL_CODE) VersionInfo );

#if (CANSM_SET_BAUDRATE_API == STD_ON)
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetBaudrate(VAR(NetworkHandleType, AUTOMATIC) Network,CONST(uint16,AUTOMATIC) BaudRateConfigID);
#endif

/* FC_VariationPoint_START */
#if (CANSM_CHANGE_BAUDRATE_API == STD_ON)
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_ChangeBaudrate(VAR(NetworkHandleType, AUTOMATIC) network,CONST(uint32,AUTOMATIC) Baudrate);
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckBaudrate(VAR(NetworkHandleType, AUTOMATIC) network, CONST(uint32,AUTOMATIC) Baudrate);
#endif
/* FC_VariationPoint_END */

extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_StartWakeupSource(VAR(NetworkHandleType, AUTOMATIC) network);
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_StopWakeupSource(VAR(NetworkHandleType, AUTOMATIC) network);

extern FUNC(void, CANSM_CODE) CanSM_Rb_DisableBusOffRecovery(VAR(NetworkHandleType, AUTOMATIC) network);

extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetNetworkMode_Substate(VAR(NetworkHandleType, AUTOMATIC) network,
        P2VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC, CANSM_APPL_DATA) NetworkMode_SubstatePtr
        );
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetBusoff_Substate(uint8 ControllerId, CanSM_BusOffRecoveryStateType_ten* BORStatePtr);


#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT != STD_OFF)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetEcuPassive( boolean CanSM_Passive );
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

#endif /*CANSM_H*/




