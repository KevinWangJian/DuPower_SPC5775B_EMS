


#ifndef ETHTRCV_H_
# define ETHTRCV_H_
/*
***************************************************************************************************
* Includes
***************************************************************************************************
*/
#include "EthTrcv_Cfg.h"

#ifdef ETHTRCV_CONFIGURED

#include "Eth_GeneralTypes.h"
#include "EthTrcv_Cfg_SchM.h"

#if ETHTRCV_DIO_USED == STD_ON
# include "Dio.h"
#endif
#if (ETHTRCV_CFG_DEM_ENABLE == STD_ON)
# include "Dem.h"
#endif

/*
***************************************************************************************************
* defines
***************************************************************************************************
*/
#define ETHTRCV_AR_RELEASE_MAJOR_VERSION      4
#define ETHTRCV_AR_RELEASE_MINOR_VERSION      2
#define ETHTRCV_AR_RELEASE_REVISION_VERSION   2

#define ETHTRCV_SW_MAJOR_VERSION    4
#define ETHTRCV_SW_MINOR_VERSION    0
#define ETHTRCV_SW_PATCH_VERSION    0

#define ETHTRCV_EXPECTED_GEN_MAJOR_VERSION    4
#define ETHTRCV_EXPECTED_GEN_MINOR_VERSION    0

#define ETHTRCV_VENDOR_ID           6
#define ETHTRCV_MODULE_ID           73

#define ETHTRCV_POSTBUILD   3
#define ETHTRCV_LINKTIME    2
#define ETHTRCV_PRECOMPILE  1

#define ETHTRCV_FALSE_B     (TRUE == FALSE)     // for Misra sometimes TRUE should be type of boolean
#define ETHTRCV_TRUE_B      (TRUE == TRUE)      // for Misra sometimes TRUE should be type of boolean

#if(ETHTRCV_GET_VERSION_INFO == STD_ON)
# if(ETHTRCV_VERSION_INFO_API_MACRO == STD_ON)
/* MR12 RULE 20.4 VIOLATION: Requirement from Autosar to implement the GetVersion function as macro.*/
#  define EthTrcv_GetVersionInfo(VersionInfoPtr){ \
    ETHTRCV_CHECKDETNULLPTR_NORETURN(0,VersionInfoPtr,ETHTRCV_SID_GETVERSIONINFO); \
     if((VersionInfoPtr) != NULL_PTR){ \
        (VersionInfoPtr)->vendorID         = ETHTRCV_VENDOR_ID; \
        (VersionInfoPtr)->moduleID         = ETHTRCV_MODULE_ID; \
        (VersionInfoPtr)->sw_major_version = ETHTRCV_SW_MAJOR_VERSION;  \
        (VersionInfoPtr)->sw_minor_version = ETHTRCV_SW_MINOR_VERSION;  \
        (VersionInfoPtr)->sw_patch_version = ETHTRCV_SW_PATCH_VERSION;  \
    }\
}
# endif
#endif

/* Enum, Function IDs for DET */
enum
{
    ETHTRCV_SID_INIT                        = 0x01u,
    ETHTRCV_SID_TRANSCEIVERINIT             = 0x02u,
    ETHTRCV_SID_SETTRANSCEIVERMODE          = 0x03u,
    ETHTRCV_SID_GETTRANSCEIVERMODE          = 0x04u,
    ETHTRCV_SID_STARTAUTONEGOTIATION        = 0x05u,
    ETHTRCV_SID_GETLINKSTATE                = 0x06u,
    ETHTRCV_SID_GETBAUDRATE                 = 0x07u,
    ETHTRCV_SID_GETDUPLEXMODE               = 0x08u,
    ETHTRCV_SID_READMIIINDICATION           = 0x09u,
    ETHTRCV_SID_WRITEMIIINDICATION          = 0x0au,
    ETHTRCV_SID_MAINFUNCTION                = 0x0cu,
    ETHTRCV_SID_GETVERSIONINFO              = 0x0bu,
    ETHTRCV_SID_GETPHYSIGNALQUALITY         = 0x10u,
    ETHTRCV_SID_SETPHYTESTMODE              = 0x11u,
    ETHTRCV_SID_SETPHYLOOPBACKMODE          = 0x12u,
    ETHTRCV_SID_GETCABLEDIAGNOSTICSRESULT   = 0x14u,
    ETHTRCV_SID_GETPHYIDENTIFIER            = 0x15u,
    ETHTRCV_SID_WAITUS                      = 0x50u,
    ETHTRCV_SID_PRV_CHECKFORNEXTINIT        = 0x51u,
    ETHTRCV_SID_PRV_PRV_INITFCT2            = 0x52u,
    ETHTRCV_SID_WRITEPHYREGISTER            = 0x53u,
    ETHTRCV_SID_READPHYREGISTER             = 0x54u,
    ETHTRCV_SID_GETLINKSTATISTICS           = 0x55u
};

/* Enum, Error IDs for DET */
enum
{
    ETHTRCV_E_INV_TRCV_IDX                  =   0x01,
    ETHTRCV_E_NOT_INITIALIZED               =   0x02,
    ETHTRCV_E_INV_POINTER                   =   0x03,
    ETHTRCV_E_INV_CONFIG                    =   0x04,
    ETHTRCV_E_INVALID_TRANSCEIVER           =   0x05,
    ETHTRCV_E_INVALID_INDEX                 =   0x06,
    ETHTRCV_E_PARAM_TIMEOUT                 =   0x07,
    ETHTRCV_E_MII_COMMUNICATION             =   0x08,
    ETHTRCV_E_MII_TIMEOUT_READ              =   0x09,
    ETHTRCV_E_MII_TIMEOUT_WRITE             =   0x0A,
    ETHTRCV_E_INV_CONFIG_COMM_NOT_RUNNING   =   0x0B,
    ETHTRCV_E_INV_CONFIG_INV_POS            =   0x0C,
    ETHTRCV_E_INV_CONFIG_INV_PARAM          =   0x0D,
    ETHTRCV_E_NOT_SUPPORTED                 =   0x0E
};


// enum, initstate of each transceiver
typedef enum
{
    ETHTRCV_INITSTATE_UNINIT    = 0u,         // 0x00: Driver is not yet configured nor init requested
    ETHTRCV_INITSTATE_INITREQ   = 1u,         // 0x01: Driver INIT is requested
    ETHTRCV_INITSTATE_INITRUN   = 2u,         // 0x02: Driver initialized is ongoing (async)
    ETHTRCV_INITSTATE_INITFINISH= 3u          // 0x03: Driver initialisation finished
} EthTrcv_InitStateType;

// enum, commands for communication with transceiver. Values are written in config data
typedef enum {
    ETHTRCV_PRV_MII_COMMAND_IGNORE          = 0,   // Command is ignored (only function call)
    ETHTRCV_PRV_MII_COMMAND_READ            = 1,   // Read next Value and ignore value
    ETHTRCV_PRV_MII_COMMAND_WRITE_DIRECT    = 10,  // Write value with direct given confVal
    ETHTRCV_PRV_MII_COMMAND_WRITE_BUF1      = 11,  // Write value with buf1
    ETHTRCV_PRV_MII_COMMAND_END             = 128  // End
}EthTrcv_Prv_Cmd_ten;

// enum, state of used driver. Value is written in config data
typedef enum
{
    ETHTRCV_DRV_SYNC  = 0u,
    ETHTRCV_DRV_ASYNC = 1u
}EthTrcv_Prv_DrvMiiMode_ten;

// Configurable Flag to allow autonegatiation
typedef enum
{
    ETHTRCV_AUTONEGOTIATIONDISABLED = 0,
    ETHTRCV_AUTONEGOTIATIONENABLED  = 1
}EthTrcv_Prv_AutonegotiationType_ten;

// Config struct for each transceiver
typedef struct
{
    uint8                               EthTrcvIndex;       /* Autosar Parameter in general */
    uint8                               CfgNoStart;         /* points to configuration in EthTrcv_Cfg_CfgInit_ast */
    uint8                               CfgNoEnd;           /* amount of Configurations in Cfg_CfgInit_ast  - 1 */
    boolean                             PreambleSuppression;/* optional Allow possiblity for preamble suppression */
}EthTrcv_Cfg_TrcvInit_tst;

// Config Struct for each EthTrcv-Config-set
typedef struct
{
    uint8                                   HwType;                         /* defines the HW-Type configured */
    uint8                                   ethTrcvIdx;                     /* defines the index of the configured Trcv */
    uint8                                   EthTrcvCtrlIdx;                 /* defines the controller index to used for the configured Trcv */
    uint8                                   EthTrcvMiiIdx;                  /* defines the Mii index to used for the configured Trcv */
    EthTrcv_Prv_AutonegotiationType_ten     EthTrcvAutoNegotiationEnabled;  /* defines whether the Autonegotiation is enabled or disabled for the configured Trcv */
    EthTrcv_DuplexModeType                  EthTrcvDuplexMode;              /* defines the required Duplex mode for the configured Trcv */
    EthTrcv_BaudRateType                    ethTrcvSpeed;                   /* defines the required Baud rate for the configured Trcv */
    uint16                                  AdrNoInit;                      /* points to the Init commands of EthTrcv_Cfg_CfgData_ast */
    uint16                                  AdrNoMain;                      /* points to the Cyclic commands of EthTrcv_Cfg_CfgData_ast */
#if ETHTRCV_TJA1100_USED == STD_ON
    uint16                                  AdrNoEnTestMode;                /* points to the start of commands to enable Test Modes in EthTrcv_Cfg_CfgData_ast*/
    uint16                                  AdrNoDisTestMode;               /* points to the start of commands to disable Test Modes in EthTrcv_Cfg_CfgData_ast*/
    uint16                                  AdrNoCableTest;                 /* points to the Test Mode commmands of EthTrcv_Cfg_CfgData_ast*/
    uint16                                  AdrNoPhySignalQuality;          /* points to the GetSignalQuality commmands of EthTrcv_Cfg_CfgData_ast*/
    uint16                                  CommandPosEnPhyLoopbackMode;    /* points to the start of commands to enable Loopback Mode in EthTrcv_Cfg_CfgData_ast*/
    uint16                                  CommandPosDisPhyLoopbackMode;   /* points to the start of commands to disable Loopback Mode in EthTrcv_Cfg_CfgData_ast*/
    uint16                                  CommandPosGetLinkStatistics;    /* points to the start of commands to get the link statistics in EthTrcv_Cfg_CfgData_ast*/
#endif
#if ETHTRCV_CFG_DEM_ENABLE == STD_ON
    Dem_EventIdType                         EventId;                        /* DemEvent ID */
#endif
}EthTrcv_Cfg_CfgInit_tst;

typedef P2FUNC(void,   ETHTRCV_APPL_CODE, EthTrcv_Prv_InitFctP_t)(void);
typedef P2FUNC(void,   ETHTRCV_APPL_CODE, EthTrcv_CommFctP_t)(void);

// List of functions to accss the EthTrcv. It is separated in:
//   init-data: sequence processed in init-function
//   main-data: sequence processin in main-function
typedef struct
{
    EthTrcv_CommFctP_t      fct;
    uint16                  time;
    uint16                  data;
    uint8                   adr;
    EthTrcv_Prv_Cmd_ten     cmd;
    uint8                   TrcvIdx;
    EthTrcv_Prv_DrvMiiMode_ten SyncFlag;
}EthTrcv_Cfg_CfgData_tst;

// Tja1100 specific data.  used for HW-access to EthTrcv
#if ETHTRCV_TJA1100_USED == STD_ON
typedef struct
{
    Dio_ChannelType      EnablePin;       /* Enable input pin */
    Dio_ChannelType      WakePin;         /* Wake input pin */
    Dio_ChannelType      LinkPin;         /* LED output pin*/
}EthTrcv_Cfg_TJA1100_tst;

/* Phy Identifier Type */
typedef struct
{
    uint32     Phy_OrgUniqueId_u32;
    uint8      Phy_ModelNumber_u8;
    uint8      Phy_RevisionNumber_u8;
}EthTrcv_PhyIdentificationType_tst;
#endif

/* Main config struct for EthTrcv. Given in EthTrcv_Init */
typedef struct
{
    uint8                                   NumberOfEthTrcv;
    uint8                                   NumberOfConfSets_u8;
    uint16                                  NumberOfCfgData_u16;
    const EthTrcv_Cfg_TrcvInit_tst          *EthTrcv_Cfg_TrcvInit_ast;
    const EthTrcv_Cfg_CfgInit_tst           *EthTrcv_Cfg_CfgInit_ast;
# if ETHTRCV_TJA1100_USED == STD_ON
    const EthTrcv_Cfg_TJA1100_tst           *EthTrcv_Cfg_TJA1100_ast;
    const EthTrcv_PhyIdentificationType_tst *EthTrcv_Cfg_PhyIdentification_pco;
# endif
}EthTrcv_ConfigType;


/*  Extern Function Definitions */
/***************************************************************************************************
*
*
*               ETH TRANSCEIVER DRIVER SPECIFIC FUNCTIONS
*
*
***************************************************************************************************/
#define ETHTRCV_START_SEC_CODE
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"
extern FUNC (void,           ETHTRCV_CODE) EthTrcv_Init(const EthTrcv_ConfigType* CfgPtr);
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_TransceiverInit(uint8 TrcvIdx, uint8 CfgIdx);

#if ( ETHTRCV_CFG_SET_TRANSCEIVERMODE_API == STD_ON)
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetTransceiverMode(uint8 TrcvIdx, EthTrcv_ModeType CtrlMode);
#endif

#if ( ETHTRCV_CFG_GET_TRANSCEIVERMODE_API == STD_ON)
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetTransceiverMode(uint8 TrcvIdx,
                                        P2VAR(EthTrcv_ModeType, AUTOMATIC, ETHTRCV_APPL_DATA) TrcvModePtr);
#endif

#if ( ETHTRCV_CFG_START_AUTONEGOTIATION_API == STD_ON)
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_StartAutoNegotiation(uint8 TrcvIdx);
#endif

#if ( ETHTRCV_CFG_GET_LINKSTATE_API == STD_ON)
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetLinkState(uint8 TrcvIdx,
                                        P2VAR(EthTrcv_LinkStateType, AUTOMATIC, ETHTRCV_APPL_DATA) LinkStatePtr);
#endif

#if ( ETHTRCV_CFG_GET_BAUDRATE_API == STD_ON)
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetBaudRate(uint8 TrcvIdx,
                                        P2VAR(EthTrcv_BaudRateType, AUTOMATIC, ETHTRCV_APPL_DATA) BaudRatePtr);
#endif

#if ( ETHTRCV_CFG_GET_DUPLEXMODE_API == STD_ON)
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetDuplexMode(uint8 TrcvIdx,
                                        P2VAR(EthTrcv_DuplexModeType, AUTOMATIC, ETHTRCV_APPL_DATA) DuplexModePtr);
#endif

extern FUNC (void, ETHTRCV_CODE) EthTrcv_ReadMiiIndication(  uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx, uint16 RegVal);
extern FUNC (void, ETHTRCV_CODE) EthTrcv_WriteMiiIndication( uint8 CtrlIdx, uint8 TrcvIdx, uint8 RegIdx );


#if (ETHTRCV_ECUC_RB_RTE_IN_USE != STD_ON)
extern FUNC (void, ETHTRCV_CODE) EthTrcv_MainFunction( void );
#endif

#if defined(ETHTRCV_TJA1100_USED)
 #if (ETHTRCV_TJA1100_USED == STD_ON)
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyTestMode( uint8 TrcvIdx, EthTrcv_PhyTestModeType Mode );

extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_SetPhyLoopbackMode ( VAR( uint8,                       AUTOMATIC ) TrcvIdx,
                                                                        VAR( EthTrcv_PhyLoopbackModeType, AUTOMATIC ) Mode );

extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetCableDiagnosticsResult( uint8 TrcvIdx, EthTrcv_CableDiagResultType* ResultPtr );

extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_ReadPhyRegister( VAR(uint8, AUTOMATIC)               CtrlIdx_u8,
                                                                    VAR(uint8, AUTOMATIC)               TrcvIdx_u8,
                                                                    VAR(uint8, AUTOMATIC)               RegIdx_u8,
                                                                    P2VAR(uint16, AUTOMATIC, AUTOMATIC) RegValPtr_pu16 );

extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_WritePhyRegister( VAR(uint8, AUTOMATIC)               CtrlIdx_u8,
                                                                     VAR(uint8, AUTOMATIC)               TrcvIdx_u8,
                                                                     VAR(uint8, AUTOMATIC)               RegIdx_u8,
                                                                     VAR(uint16, AUTOMATIC)              RegVal_u16 );
extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetPhySignalQuality( uint8 TrcvIdx, uint8* SignalQualityPtr );

extern FUNC (Std_ReturnType, ETHTRCV_CODE) EthTrcv_GetPhyIdentifier(uint8 TrcvIdx, uint32* OrgUniqueIdPtr, uint8* ModelNrPtr, uint8* RevisionNrPtr);

extern FUNC(Std_ReturnType, ETH_CODE) EthTrcv_GetLinkStatistics( VAR(uint8, AUTOMATIC)                                    TrcvIdx_u8,
                                                                 P2VAR(EthTrcv_LinkStatisticsType, AUTOMATIC, AUTOMATIC)  LinkStats_pst );
 #endif
#endif

#if(ETHTRCV_GET_VERSION_INFO == STD_ON)
# if(ETHTRCV_VERSION_INFO_API_MACRO == STD_OFF)
FUNC (void,           ETHTRCV_CODE) EthTrcv_GetVersionInfo(Std_VersionInfoType* VersionInfoPtr);
# endif
#endif

#define ETHTRCV_STOP_SEC_CODE
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"


/*  Extern Data Definitions */
/***************************************************************************************************
*
*
*               ETH TRANSCEIVER DRIVER SPECIFIC Data
*
*
***************************************************************************************************/

#define ETHTRCV_START_SEC_CONFIG_DATA_POSTBUILD_HEADER
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"
extern CONST(EthTrcv_ConfigType,ETHTRCV_CFG) EthTrcv_Config;
#define ETHTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_HEADER
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"




#endif   // ETHTRCV_CFG_CONFIGURED
#endif  // ETHTRCV_H_

/*
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
*/


