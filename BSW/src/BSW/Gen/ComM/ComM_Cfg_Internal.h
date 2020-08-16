


/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * Generator__: ComM / AR42.4.0.0                Module Package Version
 * Editor_____: 9.0                Tool Version
 * Model______: 2.3.0.4             ECU Parameter Definition Version
 *
 </VersionHead>*/




#ifndef  COMM_CFG_INTERNAL_H
#define  COMM_CFG_INTERNAL_H


/***********************************************************************************/
/*                                        INCLUDES                                 */
/***********************************************************************************/
#include "ComM_Cfg.h"




#define COMM_CAN                STD_ON
#define COMM_LIN                STD_OFF
#define COMM_FLXRY              STD_OFF
#define COMM_ETH                STD_ON

#define COMM_NO_OF_USERS        6
#define COMM_NO_OF_CHANNELS     6

#define COMM_DEV_ERROR_DETECT               STD_OFF
#define COMM_SYNCHRONOUS_WAKE_UP            STD_OFF

#define COMM_VERSION_INFO_API               STD_OFF

/* Configure Nm Support */
#define COMM_NM_SUPPORT                     STD_OFF

/* Configure DCM support */
#define COMM_DCM_SUPPORT                    STD_ON

/* Configure RTE support */
#define COMM_RTE_SUPPORT                    STD_ON

/* PNC SUPPORT */
#define COMM_PNC_ENABLED        STD_OFF

/* PNC ERA SUPPORT */
#define COMM_PNC_GW_ENABLED     STD_OFF

/* LIMIT TO NOCOM SUPPORT */
#define COMM_LIMIT_TO_NOCOM_ENABLED    STD_OFF

/* PREVENT WAKEUP SUPPORT */
#define COMM_PREVENT_WAKEUP_ENABLED      STD_OFF

#if(COMM_NM_SUPPORT!= STD_OFF)
/* If Nm is used, this switch determines the Nm Variant */
#define COMM_NM_VARIANT   COMM_NM_VARIANT_FULL
#endif

/* Common inhibition switch */
#define COMM_INHIBITION_ENABLED     ((COMM_PREVENT_WAKEUP_ENABLED != STD_OFF) || (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF))

/* Reset After forcing to No Com */
#define COMM_RESET_AFTER_NO_COM             STD_OFF

#define COMM_MAX_NO_OF_PNCS                 (48)

#define COMM_NO_OF_PNCS         (0)

/* Number of channels with ERA signals configured */
#define COMM_NO_OF_CH_WITH_ERA     (0)

/* Number of possible Bus types which have EIRA configured.
   The Const and RAM structures to store EIRA information is based on the ComMChannels configured rather than the actual EIRA
   Signals present. This is done to keep the implementation common for both pre-compile and post-build variants.
*/
#define COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA      (2)






/* BusSm API structure  */

typedef struct
{
     P2FUNC(Std_ReturnType, COMM_APPL_CODE, BusSm_RequestComMode)(NetworkHandleType, ComM_ModeType);
     P2FUNC(Std_ReturnType, COMM_APPL_CODE, BusSm_GetCurrentComMode)(NetworkHandleType,
                    P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) ComM_ModePtr);
}ComM_BusSmApiType;


/****************************************Users structure type**************************/
typedef struct
{
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) DirectChannels_p;
#if (COMM_PNC_ENABLED != STD_OFF)
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Pncs_p;
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
    uint8 NumDirectChannels_u8;
    uint8 NumAllChannels_u8;
#if (COMM_PNC_ENABLED != STD_OFF)
    uint8 NumPnc_u8;
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
}ComM_UsersType;

/****************************************Channels structure type**************************/
typedef struct ComM_ChannelTypeStruct
{
#if (COMM_PNC_ENABLED != STD_OFF)
    P2CONST(uint16,COMM_CONST,COMM_APPL_CONST) TxSigIdList_p;
#endif /* #if (COMM_PNC_ENABLED != STD_OFF)  */
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Pncs_p;
#endif
#if (COMM_INHIBITION_ENABLED)
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) DirectUsers_p;
#endif
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) AllUsers_p;
    ComM_BusType BusType_e;
    ComM_NMVariantType ComMNmVariant_e;
#if (COMM_PNC_GW_ENABLED != STD_OFF)
    ComM_PncGatewayType PncGwType;
#endif    /* #if (COMM_PNC_GW_ENABLED != STD_OFF)  */
    uint32 NmLightTimeout_u32;
    uint16 TMinFullComModeDuration_u16;
    NetworkHandleType ComMChannelId_u8;
#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))
    uint8 numPncs_u8;
#endif /*#if ((COMM_INHIBITION_ENABLED) &&(COMM_PNC_ENABLED != STD_OFF))  */
#if (COMM_INHIBITION_ENABLED)
    uint8 numDirectUsers_u8;
    uint8 InhibitionInitValue_u8;
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    uint8 numAllUsers_u8;
#if(COMM_PNC_ENABLED != STD_OFF)
    boolean PncNmRequest;
#endif /* #if (COMM_PNC_ENABLED == STD_ON)  */
}ComM_ChannelType;

/****************************************Pncs structure type**************************/
typedef struct ComM_PncStructType
{
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Channels; /* Channels Per PNC */
#if(COMM_INHIBITION_ENABLED)
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Users_p; /* Users per PNC */
#endif /* #if (COMM_INHIBITION_ENABLED)  */
    uint16 PrepareSleepTimer;
#if(COMM_INHIBITION_ENABLED)
    uint8 NumUsers_u8;
#endif /*#if(COMM_INHIBITION_ENABLED)  */
    uint8 NumChannels;
}ComM_PncConfigStruct_t;


/* ComM global config type structure */
#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

#if(COMM_PNC_ENABLED != STD_OFF)
// For Signal array type for ERA and EIRA Rx signals of PNC
typedef const uint16 ComM_SignalArrayType[COMM_NO_OF_PNCS];
#endif      /* #if(COMM_PNC_ENABLED != STD_OFF) */

/* Definition of Global config structure of ComM  */
// Global config structure to store pointers to all config tables
/*typedef struct
{
    P2CONST(ComM_ChannelType,COMM_CONST,COMM_APPL_CONST) ChannelConfig_pcs;     Holds pointer to channel list
    P2CONST(ComM_UsersType,COMM_CONST,COMM_APPL_CONST) UserConfig_pcs;          Holds pointer to user list
#if(COMM_PNC_ENABLED != STD_OFF)
    P2CONST(ComM_PncConfigStruct_t,COMM_CONST,COMM_APPL_CONST) PncConfig_pcs;   Holds pointer to PNc list
    P2CONST(ComM_SignalArrayType,COMM_CONST,COMM_APPL_CONST) EiraSignalTable_pcs; Holds pointer to EIRA signal table
#if(COMM_PNC_GW_ENABLED != STD_OFF)
    P2CONST(ComM_SignalArrayType,COMM_CONST,COMM_APPL_CONST) EraSignalTable_pcs;    Holds pointer to ERA signla table
#endif
    VAR(boolean,COMM_VAR) ComMPncEnabled_b;                                         Holds actual status of PNC switch
#endif
}ComM_GlobalConfigType;*/

typedef struct
{
    P2CONST(ComM_ChannelType,COMM_CONST,COMM_APPL_CONST) ChannelConfig_pcs;
    P2CONST(ComM_UsersType,COMM_CONST,COMM_APPL_CONST) UserConfig_pcs;
#if(COMM_PNC_ENABLED != STD_OFF)
    P2CONST(ComM_PncConfigStruct_t,COMM_CONST,COMM_APPL_CONST) PncConfig_pcs;
    P2CONST(ComM_SignalArrayType,COMM_CONST,COMM_APPL_CONST) EiraSignalTable_pcs;
#if(COMM_PNC_GW_ENABLED != STD_OFF)
    P2CONST(ComM_SignalArrayType,COMM_CONST,COMM_APPL_CONST) EraSignalTable_pcs;
#endif
    VAR(boolean,COMM_VAR) ComMPncEnabled_b;
#endif
}ComM_GlobalConfigType;

#endif  /* #if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE) */

#if (COMM_RTE_SUPPORT != STD_OFF)
extern FUNC(void, COMM_CODE) ComM_Rte_Switch_UM_currentMode(VAR(ComM_UserHandleType, AUTOMATIC) UserId, VAR(uint8, AUTOMATIC) lowestMode);
#endif




/*************************************** *Extern Definitions **************************/

#define COMM_START_SEC_CONST_8
#include "ComM_Cfg_MemMap.h"
#if (COMM_INHIBITION_ENABLED)
extern CONST(ComM_InhibitionStatusType, COMM_CONST) ComM_EcuGroupClassification_Init;
#endif
#define COMM_STOP_SEC_CONST_8
#include "ComM_Cfg_MemMap.h"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
extern CONST(ComM_BusSmApiType, COMM_CONST) ComM_BusSmApi[];
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

#define COMM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"
extern CONST(ComM_ChannelType,COMM_CONST) ComM_ChanelList[];
extern CONST(ComM_UsersType,COMM_CONST) ComM_UserList[];

#if (COMM_PNC_ENABLED != STD_OFF)

extern CONST(ComM_PncConfigStruct_t,COMM_CONST) ComM_PncList[];
extern CONST(uint16, COMM_CONST) ComM_EIRA_RxSig[][COMM_NO_OF_PNCS];

#if(COMM_PNC_GW_ENABLED != STD_OFF)
extern CONST(uint16, COMM_CONST) ComM_ERA_RxSig[][COMM_NO_OF_PNCS];
#endif  /*  (COMM_PNC_GW_ENABLED != STD_OFF)  */

#endif  /* COMM_PNC_ENABLED != STD_OFF) */
#define COMM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"




#endif  /* #ifndef  COMM_CFG_H  */
