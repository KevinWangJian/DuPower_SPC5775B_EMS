

#ifndef COMM_PRIV_H
#define COMM_PRIV_H

/**
 * \defgroup COMM_PRIV_H    ComM_Priv - Private Function of ComM.
 * \n
 */

/* Includes */
#include "ComM.h"
#include "ComM_Cfg_Internal.h"
#include "Rte_ComM.h"
#include "BswM_ComM.h"
#include "ComM_Cfg_SchM.h"
#include "EcuM.h"

#include "Bfx.h"

#if (COMM_PNC_ENABLED != STD_OFF)
#include "Com.h"
#endif

#if(COMM_NM_SUPPORT != STD_OFF)
#include "Nm.h"
#endif

#if (COMM_DCM_SUPPORT == STD_ON)
#include "Dcm_Cbk.h"
#endif

/* COMM_DEV_ERROR_DETECT  */
#if (COMM_DEV_ERROR_DETECT==STD_ON)
#include "Det.h"
#endif

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

// Interface API IDs for DET interface
/*
 * Instance Id refers to an ID assigned by Autosar to identify every unique instance of one Module/Component, used to indicate
 * that module instance which is reporting the error during the call of Det_ReportError()\n
 */
#define  COMM_INSTANCE_ID                                               ((uint8)0x00)

#define  COMM_INIT_APIID                                                ((uint8)0x01)

#define  COMM_DEINIT_APIID                                              ((uint8)0x02)

#define  COMM_GET_STATUS_APIID                                          ((uint8)0x03)

#define  COMM_GET_INHIBITION_STATUS_APIID                               ((uint8)0x04)

#define  COMM_REQ_COMMODE_APIID                                         ((uint8)0x05)

#define  COMM_GET_MAX_COMMODE_APIID                                     ((uint8)0x06)

#define  COMM_GET_REQ_COMMODE_APIID                                     ((uint8)0x07)

#define  COMM_GET_CUR_COMMODE_APIID                                     ((uint8)0x08)

#define  COMM_PREVENT_WAKEUP_APIID                                      ((uint8)0x09)

#define  COMM_LIMIT_CHNLTO_NOCOMMODE_APIID                              ((uint8)0x0b)

#define  COMM_LIMIT_ECUTO_NOCOMMODE_APIID                               ((uint8)0x0c)

#define  COMM_READ_INHIBIT_COUNTER_APIID                                ((uint8)0x0d)

#define  COMM_RESET_INHIBIT_COUNTER_APIID                               ((uint8)0x0e)

#define  COMM_SET_ECUGROUPCLASS_APIID                                   ((uint8)0x0f)

#define  COMM_GETVERINFO_APIID                                          ((uint8)0x10)

#define  COMM_MAINFNC_APIID                                             ((uint8)0x60)

#define  COMM_NM_BUS_SLEEPMODE                                          ((uint8)0x1a)

#define  COMM_NM_NETWORKMODE                                            ((uint8)0x18)

#define  COMM_NM_NETWORKSTART_INDICATION                                ((uint8)0x15)

#define  COMM_NM_PREPARE_BUSSLEEPMODE                                   ((uint8)0x19)

#define  COMM_NM_RESTARTINDICATION                                      ((uint8)0x1b)

#define  COMM_DCM_ACTIVEDIAG                                            ((uint8)0x1f)

#define  COMM_DCM_INACTIVEDIAG                                          ((uint8)0x20)

#define  COMM_COMMUNICATION_ALLOWED                                     ((uint8)0x29)

#define  COMM_ECUM_WAKEUP_INDICATION                                    ((uint8)0x2a)

#define  COMM_ECUM_PNCWAKEUP_INDICATION                                 ((uint8)0x38)

#define  COMM_BUSSM_MODEINDICATION                                      ((uint8)0x33)

#define  COMM_GET_STATE_APIID                                            ((uint8)0x34)

#define COMM_EIRA_CBK_APIID                                                ((uint8)0x35)

#define COMM_ERA_CBK_APIID                                                ((uint8)0x36)

#define COMM_PNC_MAINFNC_APIID                                          ((uint8)0x37)

// Module specific Return values
#define COMM_E_MODE_LIMITATION                  2

#define E_NOT_INITIALIZED                       3

// DET error ID's

#define  COMM_E_NOT_INITED                 ((uint8)(0x1))

#define  COMM_E_WRONG_PARAMETERS           ((uint8)(0x2))

#define  COMM_E_ERROR_IN_PROV_SERVICE      ((uint8)(0x3))

#define COMM_E_CNTR_UNDERFLW                ((uint8)0x04)

// Macro for Active diagnosis
#define COMM_ACTIVE_DIAGNOSTICS                    TRUE

// Macro for Inactive diagnosis
#define COMM_INACTIVE_DIAGNOSTICS                  FALSE

/*Macro for ComM NM Vaiant*/
#define COMM_NM_VARIANT_FULL                 TRUE

/*Macro for ComM NM Vaiant*/
#define COMM_NM_VARIANT_PASSIVE              FALSE


/* Macro Functions */

// Macro to set limit to no com in ComM_InhibitionStatusType
#define  COMM_SET_LIMIT_TO_NO_COM(Reg)          (void)(Bfx_SetBit_u8u8(&(Reg), 0x01))

// Macro to set prevent wake up in ComM_InhibitionStatusType
#define  COMM_SET_PREVENT_WAKEUP(Reg)           (void)(Bfx_SetBit_u8u8(&(Reg), 0x00))

// Macro to clear limit to no com in ComM_InhibitionStatusType
#define  COMM_CLR_LIMIT_TO_NO_COM(Reg)          (void)(Bfx_ClrBit_u8u8(&(Reg), 0x01))

// Macro to clear prevent wake up in ComM_InhibitionStatusType
#define  COMM_CLR_PREVENT_WAKEUP(Reg)           (void)(Bfx_ClrBit_u8u8(&(Reg), 0x00))

// Macro to get limit to no com in ComM_InhibitionStatusType
#define  COMM_GET_LIMIT_TO_NO_COM(Reg)          (Bfx_GetBit_u8u8_u8((Reg),0x01))

//Macro to get prevent wake up in ComM_InhibitionStatusType
#define  COMM_GET_PREVENT_WAKEUP(Reg)           (Bfx_GetBit_u8u8_u8((Reg),0x00))

//Macro to set bit
#define  COMM_SET_BIT(Reg,Position)             (void)(Bfx_SetBit_u8u8(&(Reg),Position))
/* Constants */

#ifndef  C_ZERO
#define  C_ZERO  ((uint8)0x00)
#endif

#ifndef  C_ONE
#define  C_ONE   ((uint8)0x01)
#endif

/* Mask for WakeUp inhibition */
#define COMM_WAKEUP_INHIBITION  ((uint8)0x01)

/* Mask for Limit to no com */
#define COMM_LIMIT_TO_NOCOM  ((uint8)0x02)

/* Macro for ComSignal invalid value */
#define COMM_COMSIGNAL_INVALID_ID    ((uint16)0xFFFF)

/* Macro for max value of u16 variable */
#define COMM_MAX_U16  ((uint16)0xFFFF)


/* Access macros to keep PC and PB variants same */
#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

/* Access macros for Post build */

/* If the variant is Post build, then get the actual value of PNC switch from configuration*/
#define COMM_GET_FEATURE_PNC_ENABLED  (ComM_GlobalConfigPtr_pgcs->ComMPncEnabled_b)

/* Access macros for config data for PB variant-- through global cfg ptrs */
#define COMM_GET_CHANNEL_LIST     (ComM_GlobalConfigPtr_pgcs->ChannelConfig_pcs)
#define COMM_GET_USER_LIST        (ComM_GlobalConfigPtr_pgcs->UserConfig_pcs)
#define COMM_GET_PNC_LIST         (ComM_GlobalConfigPtr_pgcs->PncConfig_pcs)
#define COMM_GET_EIRASIG_TABLE    (ComM_GlobalConfigPtr_pgcs->EiraSignalTable_pcs)
#define COMM_GET_ERASIG_TABLE     (ComM_GlobalConfigPtr_pgcs->EraSignalTable_pcs)

#define ComM_Config     ComM_Config

#else

/* Access macros for Pre compile */

/* If the variant is Pre compile, this always returns TRUE,
 * (because the code is switched off through compiler switch itself.
 * Runtime check will be optimsied by compiler as it it always true
 */
#define COMM_GET_FEATURE_PNC_ENABLED  (TRUE)

/* Access macro for cfg data for precompile variant-- access directly w/o pointers
 * to keep the code optimised for Pre compile variant */

#define COMM_GET_CHANNEL_LIST     ComM_ChanelList
#define COMM_GET_USER_LIST       ComM_UserList
#define COMM_GET_PNC_LIST        ComM_PncList
#define COMM_GET_EIRASIG_TABLE    ComM_EIRA_RxSig
#define COMM_GET_ERASIG_TABLE     ComM_ERA_RxSig

#define ComM_Config     NULL_PTR

#endif

/* boolean variable to check Diagnostic type of channel */
typedef boolean ComM_DiagnosticType;

/* to differentiate between inhibitions */
typedef enum
{
  COMM_PREVENTWAKEUP = 0,
  COMM_LIMITTONOCOM
}ComM_InhibitionType;

/* Global RAM structure to store variables at ComM level
typedef struct
{
    VAR(ComM_InitStatusType,COMM_VAR) ComM_InitStatus;      Holds ComM init status
#if(COMM_INHIBITION_ENABLED)
    VAR(uint16,COMM_VAR) ComM_InhibitCounter_u16;           Holds count of full com requests inhibited
    VAR(ComM_InhibitionStatusType,COMM_VAR) ComM_EcuGroupClassification_u8; Holds group classification status value
#endif        COMM_INHIBITION_ENABLED compiler switch ends here
#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
    VAR(boolean,COMM_VAR) ComM_LimitECUToNoCom_b;           Holds limit ECU to No Com status
#endif       COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF compiler switch ends here
}ComM_GlobalVarType;  */

typedef struct
{
    VAR(ComM_InitStatusType,COMM_VAR) ComM_InitStatus;
#if(COMM_INHIBITION_ENABLED)
    VAR(uint16,COMM_VAR) ComM_InhibitCounter_u16;
    VAR(ComM_InhibitionStatusType,COMM_VAR) ComM_EcuGroupClassification_u8;
#endif      /* #if(COMM_INHIBITION_ENABLED)  */
#if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
    VAR(boolean,COMM_VAR) ComM_LimitECUToNoCom_b;
#endif      /* #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */
}ComM_GlobalVarType;


/*
ComM_ChannelVarType
typedef struct
    {
    VAR(ComM_StateType,AUTOMATIC) ChannelState_e;        Holds the current state of the channel
    VAR(uint32,AUTOMATIC) LightTimeoutCtr_u32;            Holds Light time out counter value
    VAR(uint16,AUTOMATIC) MinFullComTimeoutCtr_u16;        Holds minimum full com duration counter value
    VAR(ComM_ModeType,AUTOMATIC) ChannelMode_u8;        Holds the current mode of the channel
    VAR(ComM_ModeType,AUTOMATIC) BusSmMode_u8;            Holds the current mode of BusSM
    VAR(uint8,AUTOMATIC) UserRequestCtr_u8;                Holds the count of full com requests of users assigned to this channel
    VAR(uint8,AUTOMATIC) PassiveRequestState_u8;        Holds the passive request state of channel
    VAR(uint8,AUTOMATIC) PncRequestCtr_u8;                Holds the count of PNC's in requested state that are assigned to this channel
    VAR(ComM_InhibitionStatusType,AUTOMATIC) InhibitionReqStatus_u8; Holds the current inhibition status of the channel
    VAR(ComM_DiagnosticType,AUTOMATIC) DiagnosticRequestState_b;    Indicates if DCM request is present or not
    VAR(boolean,AUTOMATIC) BusSmRequestedModeAchieved_b;        Indicates if BusSm is in the same mode as requested mode by ComM
    VAR(boolean,AUTOMATIC) CommunicationAllowed_b;        Holds the value of Communication allowed for the particular channel
    VAR(boolean,AUTOMATIC) NmBusSleepIndicationStatus_b;        Indicates if Bus sleep is indicated by Nm
    VAR(boolean,AUTOMATIC) NmPrepareBusSleepIndicationStatus_b;    Indicates if prepare bus sleep is indicated by Nm
    VAR(boolean,AUTOMATIC) NmNetworkModeStatus_b;        Indicates if Network mode is indicated by Nm
    VAR(boolean,AUTOMATIC) NmNetworkRequestStatus_b;    Indicates if Network request has to be called
   } ComM_ChannelVarType;
 */
typedef struct
   {
    VAR(ComM_StateType,AUTOMATIC) ChannelState_e;
    VAR(uint32,AUTOMATIC) LightTimeoutCtr_u32;
    VAR(uint16,AUTOMATIC) MinFullComTimeoutCtr_u16;
    VAR(ComM_ModeType,AUTOMATIC) ChannelMode_u8;
    VAR(ComM_ModeType,AUTOMATIC) BusSmMode_u8;
    VAR(uint8,AUTOMATIC) UserRequestCtr_u8;
    VAR(uint8,AUTOMATIC) PassiveRequestState_u8;
    VAR(uint8,AUTOMATIC) PncRequestCtr_u8;
    VAR(ComM_InhibitionStatusType,AUTOMATIC) InhibitionReqStatus_u8;
    VAR(boolean,AUTOMATIC) NmNetworkRequestStatus_b;
    VAR(ComM_DiagnosticType,AUTOMATIC) DiagnosticRequestState_b;
    VAR(boolean,AUTOMATIC) CommunicationAllowed_b;
    VAR(boolean,AUTOMATIC) NmBusSleepIndicationStatus_b;
    VAR(boolean,AUTOMATIC) NmPrepareBusSleepIndicationStatus_b;
    VAR(boolean,AUTOMATIC) NmNetworkModeStatus_b;
   } ComM_ChannelVarType;


/*
ComM_UserVarType
 * Structure to hold all user related information
 * typedef struct
    {
     VAR(uint16, AUTOMATIC) WakeUpInhibitionCtr_u16;  Holds the wake up inhibition count of inhibited direct channels and PNC's of this user
     VAR(uint16, AUTOMATIC) LimitToNoComCtr_u16;  Holds the limit to no com count of inhibited direct channels and PNC's of this user
     VAR(ComM_ModeType,AUTOMATIC) RequestedUserMode_t; Holds the latest requested mode of the user
     VAR(ComM_ModeType,AUTOMATIC) IndicatedUserMode_t; Holds the latest indicated user mode to RTE
     VAR(uint8, AUTOMATIC) numChannelsInFullCom_u8; Holds the count of all channels(direct and through PNC) in Full com mode
     VAR(uint8, AUTOMATIC) numChannelsInSilentCom_u8; Holds the count of all channels(direct and through PNC) in silent com mode
     VAR(uint8, AUTOMATIC) numChannelsInNoCom_u8;  Holds the count of all channels(direct and through PNC) in No com mode
    }ComM_UserVarType;
 */
typedef struct
    {
     VAR(uint16, AUTOMATIC) WakeUpInhibitionCtr_u16;
     VAR(uint16, AUTOMATIC) LimitToNoComCtr_u16;
     VAR(ComM_ModeType,AUTOMATIC) RequestedUserMode_t;
     VAR(ComM_ModeType,AUTOMATIC) IndicatedUserMode_t;
     VAR(uint8, AUTOMATIC) numChannelsInFullCom_u8;
     VAR(uint8, AUTOMATIC) numChannelsInSilentCom_u8;
     VAR(uint8, AUTOMATIC) numChannelsInNoCom_u8;
    }ComM_UserVarType;


/*
ComM_PncRamStructType
   typedef struct
   {
       VAR(ComM_PncModeType,AUTOMATIC) PncState_e;        Holds the current PNC state
       VAR(uint16,AUTOMATIC) PrepareSleepTimer_u16;    Holds prepare sleep timer value
       VAR(uint8,AUTOMATIC) UserRequestCnt_u8;            Holds the count of full com requests of users assigned to this PNC
       VAR(uint8,AUTOMATIC) EIRACnt_u8;                Holds EIRA count of all channels of this PNC
       VAR(uint16, AUTOMATIC) LimitToNoComCtr_u16;     Holds the count of limit to no com inhibited channels of this PNC
       VAR(uint16, AUTOMATIC) WakeUpInhibitionCtr_u16; Holds the count of wake up inhibited channels of this PNC
       VAR(uint8,AUTOMATIC) ERACnt_u8;                    Holds ERA count of all channels of this PNC
       VAR(uint8,AUTOMATIC) ActiveERACnt_u8;            Holds the count of all Active channels of this PNC
    VAR(uint8,AUTOMATIC) ActiveERACntOld_u8;        Holds the old value of ActiveERACnt_u8
       VAR(boolean,AUTOMATIC) WakeUpStatus_b;            Indicates if Wakeup is indicated on this channel
   }ComM_PncRamStructType;
*/

typedef struct
{
    VAR(ComM_PncModeType,AUTOMATIC) PncState_e;
    VAR(uint16,AUTOMATIC) PrepareSleepTimer_u16;
    VAR(uint8,AUTOMATIC) UserRequestCnt_u8;
    VAR(uint8,AUTOMATIC) EIRACnt_u8;
    #if(COMM_INHIBITION_ENABLED)
    VAR(uint16, AUTOMATIC) LimitToNoComCtr_u16;
    VAR(uint16, AUTOMATIC) WakeUpInhibitionCtr_u16;
    #endif
    #if(COMM_PNC_GW_ENABLED != STD_OFF)
    VAR(uint8,AUTOMATIC) ERACnt_u8;
    VAR(uint8,AUTOMATIC) ActiveERACnt_u8;
    VAR(boolean,AUTOMATIC) ActiveERAStateOld_b;
    #endif
    VAR(boolean,AUTOMATIC) WakeUpStatus_b;
}ComM_PncRamStructType;

/*typedef struct
{
VAR(boolean,AUTOMATIC) ActiveRequest_b; Holds the active request state of the channel
VAR(boolean,AUTOMATIC) PassiveRequest_b; Holds the passive  request state of the channel
ComM_NMVariantType  ComMNmVariant;Holds the nm variant of the channel
} ComM_EventStructType;
*/

typedef struct
{
    VAR(boolean,AUTOMATIC) ActiveRequest_b;
    VAR(boolean,AUTOMATIC) PassiveRequest_b;
} ComM_RequestStructType;



/*typedef struct
{
    VAR(boolean,AUTOMATIC)activeRequestState_b;
    VAR(boolean,AUTOMATIC)wakeupRequestState_b;
    VAR(boolean,AUTOMATIC)passiveRequestState_b;
    VAR(boolean,AUTOMATIC) activeERAState_b;
} ComM_RequestStructType;
*/


typedef struct
{
    VAR(boolean,AUTOMATIC) activeRequestState_b;
    VAR(boolean,AUTOMATIC) wakeupRequestState_b;
    VAR(boolean,AUTOMATIC) passiveRequestState_b;
    #if (COMM_PNC_GW_ENABLED != STD_OFF)
    VAR(boolean,AUTOMATIC) activeERAState_b;
    #endif  /*  #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
} ComM_PncEventStructType;



/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */

/* RAM Variables */

/**
 * @ingroup COMM_PRIV_H
 *
 * Macro for COMM_START_SEC_VAR_NOINIT_UNSPECIFIED
 */

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

/* extern variable declaration */

/* global structure */
extern VAR(ComM_GlobalVarType,COMM_VAR) ComM_GlobalStruct;

/* Channel RAM structure */
extern VAR(ComM_ChannelVarType,COMM_VAR) ComM_ChannelStruct[];

/* User RAM structure */
extern VAR(ComM_UserVarType,COMM_VAR) ComM_UserStruct[];
#if (COMM_PNC_ENABLED != STD_OFF)

extern VAR(ComM_PncRamStructType,COMM_VAR) ComM_PncRamStruct[];

extern VAR(boolean,COMM_VAR) ComM_EIRA_RxSigVal[][COMM_NO_OF_PNCS];

#if (COMM_PNC_GW_ENABLED == STD_ON)

extern VAR(boolean,COMM_VAR) ComM_ERA_RxSigVal[][COMM_NO_OF_PNCS];

#endif      /* #if (COMM_PNC_GW_ENABLED == STD_ON) */
#endif      /* #if (COMM_PNC_ENABLED != STD_OFF) */

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
extern P2CONST(ComM_GlobalConfigType,AUTOMATIC,COMM_APPL_CONST) ComM_GlobalConfigPtr_pgcs;
#endif


/* Extern declarations for local functions */

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/* Internal function to keep track of all channel states of a user */
extern FUNC(void, COMM_CODE) ComM_LUpdateChannelModes(NetworkHandleType Channel,
                                ComM_ModeType PreviousMode, ComM_ModeType CurrentMode);

/* Internal function to translate inhibition request on a channel to linked PNC's and Users */
extern FUNC(void, COMM_CODE) ComM_LTranslateInhibitionStatus(NetworkHandleType Channel,
                                            ComM_InhibitionType InhibitionType, boolean Status);

/* Interface function between PNC state machine and channel state machine */
extern FUNC(void,COMM_CODE) ComM_LPncToChannelInterface(PNCHandleType PncIndex,ComM_PncModeType PncState,ComM_PncModeType PncPreviousState);


/* PNC main function to handle PNC state machine */
extern FUNC( void, COMM_CODE) ComM_LPncMainFunction (VAR(PNCHandleType,AUTOMATIC) PncIndex);

extern FUNC(void,COMM_CODE) ComM_EIRA_CallBack(uint8 PnBusId);

extern FUNC(void,COMM_CODE) ComM_ERA_CallBack(uint8 PnBusId,ComM_PncGatewayType channelGwType);

/* Channel main function */
extern FUNC(void,COMM_CODE) ComM_LChannelMainFunction (VAR(NetworkHandleType,AUTOMATIC) ChannelIndex);

/* Internal function to evaluate the least BusSm mode of a User */
extern FUNC(ComM_ModeType, COMM_CODE) ComM_LgetLeastBusSmMode(ComM_UserHandleType UserIndex);

/* Internal function to notify RTE if the least BusSm mode of a user changes */
extern FUNC( void, COMM_CODE) ComM_LRteNotifyLowestComMode (ComM_UserHandleType UserIndex);

/* Internal function to set wakeup indication for all channels and PNC's, used only if synchronous wake feature is enabled*/
extern FUNC(void, COMM_CODE) ComM_LSyncWakeUpIndication(void);


/* Function called from Init upon detection of incompatible generator */
extern FUNC(void, COMM_CODE) ComMAppl_IncompatibleGenerator(void);

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /*COMM_PRIV_H*/

