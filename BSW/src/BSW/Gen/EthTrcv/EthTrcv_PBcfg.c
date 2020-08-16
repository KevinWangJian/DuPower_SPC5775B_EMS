/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: EthTrcv/ AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.0.2.1                ECU Parameter Definition Version
 *

 </VersionHead>*/

#include "EthTrcv_Prv.h"
#include "EthTrcv_PBcfg.h"

/* Declaration for Postbuild struct */
//CONST(EthTrcv_ConfigType,ETHTRCV_CFG) EthTrcv_Config;



#define ETHTRCV_START_SEC_CONFIG_DATA_POSTBUILD_HEADER
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"

CONST(EthTrcv_ConfigType,ETHTRCV_PB_CONST) EthTrcv_Config=
{
    1u,      /* ETHTRCV_CFG_NUMBER_OF_ETHTRCV */
    1u,      /* NumberOfConfSets_u8;*/
    20u,    /* NumberOfCfgData_u16 */
    EthTrcv_Cfg_TrcvInit_ast,
    EthTrcv_Cfg_CfgInit_ast,
};

#define ETHTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_HEADER
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"

#define ETHTRCV_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"

/* Includes Trcv config and points to Cfg */
CONST(EthTrcv_Cfg_TrcvInit_tst,ETHTRCV_PB_CONST) EthTrcv_Cfg_TrcvInit_ast[]=
{    /* EthTrcvIndex, CfgNoStart, CfgNoEnd=size, PreambleSuppressionSupport */
/* Transceiver: DP83822 EthTrcv_0 : */
{0, 0, 0, TRUE}
};

/* Includes Cfg values and points Cfg data*/
CONST(EthTrcv_Cfg_CfgInit_tst,ETHTRCV_PB_CONST) EthTrcv_Cfg_CfgInit_ast[]=
{    /* HwType, ethTrcvIdx, EthTrcvCtrlIdx, EthTrcvMiiIdx, EthTrcvAutoNegotiationEnabled, EthTrcvDuplexMode, EthTrcvSpeed, AdrNoInit, AdrNoMain, (AdrNoEnTestMode), (AdrNoDisTestMode), (AdrNoCableTest), (CommandPosPhySignalQuality), (CommandPosEnPhyLoopbackMode), (CommandPosDisPhyLoopbackMode), (CommandPosGetLinkStatistics), (Dem EventId) */
    /* EthTrcv_0 EthTrcvConfig_0 */
    { ETHTRCV_PRV_DP83822, 0, 0, 0, ETHTRCV_AUTONEGOTIATIONENABLED, ETHTRCV_DUPLEX_MODE_FULL, ETHTRCV_BAUD_RATE_100MBIT, 0, 3},
    { ETHTRCV_PRV_NO_PHY,  0, 0, 0, ETHTRCV_AUTONEGOTIATIONENABLED, ETHTRCV_DUPLEX_MODE_FULL, ETHTRCV_BAUD_RATE_100MBIT, 0, 3} /* End */
};




// 0   = nothing to do
// 1   = write direct
// 2   = write buf1
// 16  = read to buf0
// 17  = read to buf1
// 127 = internal function only
// Bit7 = next command: last command = end

CONST (EthTrcv_Cfg_CfgData_tst, ETHTRCV_PB_CONST) EthTrcv_Cfg_CfgData_ast[]=
{
/* Config Data for Initialization of DP83822 Eth Phy */
/* fct,                          time, data  , adr ,  cmd                                   , TrcvIdx, A/Sync.     For Trcv= EthTrcv_0, CfgSet:EthTrcvConfig_0 */
{NULL_PTR                      ,    0, 0x0000, 0x00,  ETHTRCV_PRV_MII_COMMAND_IGNORE        , 0, ETHTRCV_DRV_SYNC },    /* 0    Start of Initdata for EthTrcv_0 EthTrcvConfig_0 */
{NULL_PTR                      ,    0, 0xb300, 0x00,  ETHTRCV_PRV_MII_COMMAND_WRITE_DIRECT  , 0, ETHTRCV_DRV_SYNC },    /* 1    Reset, Auto-Negotiation, Speed & Duplex operation */
{&EthTrcv_Prv_CheckForNextInit ,    0, 0x0000, 0x00,  ETHTRCV_PRV_MII_COMMAND_END           , 0, ETHTRCV_DRV_SYNC },    /* 2    End for Initdata. ------------ */

/* Config Data Of DP83822 for Main Function */
/* fct                         , time, data  , adr , cmd                                    ,TrcvIdx, A/Sync.     For Trcv= EthTrcv_0, CfgSet:EthTrcvConfig_0 */
{&EthTrcv_Prv_Fct_CheckExec    ,    0, 0x0000, 0x00, ETHTRCV_PRV_MII_COMMAND_END            , 0, ETHTRCV_DRV_SYNC },    /* 3    Check if another Phy needs to be initialized */

/* fct                         , time, data  , adr , cmd                                    ,TrcvIdx, A/Sync. SetTransceiverModeDown for Trcv= EthTrcv_0, CfgSet:EthTrcvConfig_0 */
{&EthTrcv_Prv_Fct_ModeDown     ,    0, 0x0000, 0x03, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 4    Check if Phy needs to be switched off else skip the next commands. (Adr=Offset if no change) */
{&EthTrcv_Prv_Fct_Clr1         ,    0, 0x0000, 0x00, ETHTRCV_PRV_MII_COMMAND_READ           , 0, ETHTRCV_DRV_SYNC },    /* 5    Read Reg 0, Bit 11 : IEEE Power Down */
{&EthTrcv_Prv_Fct_Or           ,    0, 0x0800, 0x00, ETHTRCV_PRV_MII_COMMAND_WRITE_BUF1     , 0, ETHTRCV_DRV_SYNC },    /* 6    Enable Power down for Phy. */
{NULL_PTR                      ,    0, 0x0000, 0x00, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 7    End of commands required for Switching off the Phy. */

/* fct                         , time, data  , adr , cmd                                    ,TrcvIdx, A/Sync. SetTransceiverModeUp for Trcv= EthTrcv_0, CfgSet:EthTrcvConfig_0 */
{&EthTrcv_Prv_Fct_ModeActive   ,    0, 0x0000, 0x03, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 8    Check if Phy needs to be switched on else skip the next commands. (Adr=Offset if no change) */
{&EthTrcv_Prv_Fct_Clr1         ,    0, 0x0000, 0x00, ETHTRCV_PRV_MII_COMMAND_READ           , 0, ETHTRCV_DRV_SYNC },    /* 9    Read Reg 0, Bit 11. */
{&EthTrcv_Prv_Fct_And          ,    0, 0xF7FF, 0x00, ETHTRCV_PRV_MII_COMMAND_WRITE_BUF1     , 0, ETHTRCV_DRV_SYNC },    /* 10    Disable Power down for Phy(~0x0800) */
{NULL_PTR                      ,    0, 0x0000, 0x00, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 11    End of commands required for switching on the Phy. */

/* fct                         , time, data  , adr , cmd                                    ,TrcvIdx, A/Sync. StartAutoNegotiation for Trcv= EthTrcv_0, CfgSet:EthTrcvConfig_0 */
{&EthTrcv_Prv_Fct_StartAutoNeg ,    0, 0x0000, 0x03, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 12    Check if Auto-negotiation shall be started else skip the next commadnds. (Adr=Offset if no change) */
{&EthTrcv_Prv_Fct_Clr1         ,    0, 0x0000, 0x00, ETHTRCV_PRV_MII_COMMAND_READ           , 0, ETHTRCV_DRV_SYNC },    /* 13    Read Reg 0. Bit 12 & 9 */
{&EthTrcv_Prv_Fct_Or           ,    0, 0x1200, 0x00, ETHTRCV_PRV_MII_COMMAND_WRITE_BUF1     , 0, ETHTRCV_DRV_SYNC },    /* 14    Enable Bit12 and 9 */
{NULL_PTR                      ,    0, 0x0000, 0x00, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 15    End of commands required for auto-negotiation */

/* fct                         , time, data  , adr , cmd                                    ,TrcvIdx, A/Sync. GetMode DP83822 for Trcv= EthTrcv_0, CfgSet:EthTrcvConfig_0 */
{&EthTrcv_Prv_Fct_Clr1         ,    0,      0, 0x00, ETHTRCV_PRV_MII_COMMAND_READ           , 0, ETHTRCV_DRV_SYNC },    /* 16    Read Reg 0. Bit 12 : IEEE Power Down */
{&EthTrcv_Prv_Fct_GetMode      ,    0, 0x0800, 0x00, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 17    Update current mode of EthTrcv */

/* fct                         , time, data  , adr , cmd                                    ,TrcvIdx, A/Sync. GetLinkState DP83822 for Trcv= EthTrcv_0, CfgSet:EthTrcvConfig_0 */
{&EthTrcv_Prv_Fct_Clr1         ,    0,      0, 0x01, ETHTRCV_PRV_MII_COMMAND_READ           , 0, ETHTRCV_DRV_SYNC },    /* 18    Read Reg 1. Bit 3 : Link Status */
{&EthTrcv_Prv_Fct_GetLink      ,    0, 0x0004, 0x00, ETHTRCV_PRV_MII_COMMAND_IGNORE         , 0, ETHTRCV_DRV_SYNC },    /* 19    Update current link status of EthTrcv */

/* fct,                                     time, data,   adr,    cmd                                    ,TrcvIdx, A/Sync */
{NULL_PTR,                                     0, 0x0000, 0x00,   ETHTRCV_PRV_MII_COMMAND_END              , 0, ETHTRCV_DRV_ASYNC}   /* 20 End of all commands */
};



#define ETHTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
/* MR12 RULE 20.1 VIOLATION: Required by Autosar memmap strategy */
#include "EthTrcv_MemMap.h"


