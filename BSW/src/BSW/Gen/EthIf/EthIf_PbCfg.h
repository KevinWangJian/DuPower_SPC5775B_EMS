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
 * $Generator__: EthIf/ AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.0.2.1          	  ECU Parameter Definition Version
 *
 
 </VersionHead>*/


#ifndef ETHIF_PBCFG_H
#define ETHIF_PBCFG_H

/*Macro to define number of EthIf configuration sets */
#define ETHIF_NUM_CONFIGSETS                (1UL)

/* Macro to define whether Standalone EthIfSwitchPortGroups are enabled or not */

#define ETHIF_STANDALONE_PORTGRPS_CONFIGURED        STD_OFF         /* Standalone port groups are not configured */

/* Macro to define whether EthIfSwitch is configured or not */

#define ETHIF_SWITCH_CONFIGURED        STD_OFF         /* EthIfSwitch is not configured */

/* Macro to define whether EthIfSwitchPortGroup is configured or not */

#define ETHIF_SWITCH_PORTGROUP_CONFIGURED        STD_OFF         /* EthIfSwitchPortGroup is not configured */

/* Macro to define whether a physical transceiver is referred by any EthIf controller */
#define ETHIF_TRANSCEIVER_CONFIGURED             STD_ON          /* A physical transceiver is referred by an EthIf controller */


#define ETHIF_START_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

extern CONST( EthIf_ConfigType, ETHIF_CONST ) EthIf_ConfigSet[1];

#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"


#define ETHIF_START_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"



extern	CONST( EthIf_FrameOwnerConfig_tst, ETHIF_CONST ) EthIfFrameOwnerConfig0_st[2];						/* Pointer to EthIfFrameOwnerConfig structure */

extern CONST( EthIf_CtrlStateType_tst,     ETHIF_CONST ) EthIf_EthIfCtrlState0_st;						    /* Pointer to EthIfCtrlStateType Structure */

#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_VAR_CLEARED_8
#include "EthIf_MemMap.h"

extern VAR( uint8,                         AUTOMATIC ) EthIf_IsTrcvInit0[1];								/* Array to store TrcvInit Flag */

#define ETHIF_STOP_SEC_VAR_CLEARED_8
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"





extern VAR( EthIf_ControllerConfig_tst,  AUTOMATIC ) EthIfControllerConfig0_st[ 1 ];                        /* Pointer to EthIfControllerConfig structure */

#define ETHIF_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthIf_MemMap.h"

/* Aray to store EthCtrl state within EthIf context */
extern VAR( EthIf_EthCtrlStateType_ten,         AUTOMATIC ) EthIf_EthCtrlState0[1];                              /* Array to store EthCtrl state within EthIf context */

/* Array to store the requested mode of EthIfCtrl */
extern VAR( Eth_ModeType,          AUTOMATIC )     EthIfCtrlReqMode0[1];

/* Array to store the transceiver error flag per EthIfCtrl */
extern VAR( boolean,          AUTOMATIC )          EthIfCtrl_TrcvError0[1];

/* Array to store the mode indicated for a physical transceiver */
extern VAR( EthTrcv_ModeType,      AUTOMATIC )     EthIf_TrcvIndMode0[1];

/* Array to store the Current mode of EthIfCtrl */
extern VAR( Eth_ModeType,                  AUTOMATIC ) EthIfCtrlMode0[1];									/* Array to store the Current mode of EthIfCtrl */

#define ETHIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthIf_MemMap.h"


#endif /* ETHIF_PBCFG_H */



