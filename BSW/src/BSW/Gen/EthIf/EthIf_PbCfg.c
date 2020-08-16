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


#include "EthIf.h"
#include "EthIf_PbCfg.h"

#if(( ETHIF_SWITCH_CONFIGURED == STD_ON ) || ( ETHIF_SWITCH_PORTGROUP_CONFIGURED == STD_ON ))
#include "EthSwt.h"
#endif

#include "TcpIp_Cbk.h"



#define ETHIF_START_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

 
  
#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"
 

#define ETHIF_START_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"

 


VAR(EthIf_ControllerConfig_tst, AUTOMATIC ) EthIfControllerConfig0_st[1]=
{
	{	/* EthIfControllerConfig 0 */
		0xffff,												/* VLAN Id is not configured */
		1500,												/* Specifies the maximum transmission unit (MTU) of the EthIfCtrl in bytes */
		0,													/* Reference to the controller in Ethernet driver on which this connection will be transmitted/received */
        0,                                               	/* Physical transceiver index.Set to invalid if EthIfCtrl does not refer a transceiver.  */
        0xff,                                               /* Switch is not referenced.Set to invalid if EthIfCtrl does not refer a switch. */
        NULL_PTR,                                           /* Switch Port Group not configured. Set to invalid */
        ETHIF_ETHIFCTRL_STATE_DOWN,							/* State of the EthIf Controller */
        ETHIF_ETHIFCTRL_LINKSTATE_DOWN,						/* Link status of the EthIf Controller */
        ETHIF_TRCV											/* Reference type of EthIf controller */
	},
};

#define ETHIF_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "EthIf_MemMap.h"


#define ETHIF_START_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

CONST(EthIf_FrameOwnerConfig_tst, ETHIF_CONST) EthIfFrameOwnerConfig0_st[2]=
{
	{
		0x800,                              /* Ethernet frame type */
		&TcpIp_RxIndication,                           /* RxIndication function for the configured frame type */
		NULL_PTR                              /* TxConfirmation function not configured  for the frame type */
	},
	{
		0x806,                              /* Ethernet frame type */
		&TcpIp_RxIndication,                           /* RxIndication function for the configured frame type */
		NULL_PTR                              /* TxConfirmation function not configured  for the frame type */
	},
};

#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_VAR_CLEARED_8
#include "EthIf_MemMap.h"

/* Flag to Store if TrcvInit is called */
VAR( uint8,                 AUTOMATIC )		EthIf_IsTrcvInit0[1];

#define ETHIF_STOP_SEC_VAR_CLEARED_8
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthIf_MemMap.h"

/* Aray to store EthCtrl state within EthIf context */
VAR( EthIf_EthCtrlStateType_ten,                 AUTOMATIC )        EthIf_EthCtrlState0[1];

/* Array to store the Current mode of EthIfCtrl */
VAR( Eth_ModeType,          AUTOMATIC )		EthIfCtrlMode0[1];

/* Array to store the requested mode of EthIfCtrl */
VAR( Eth_ModeType,          AUTOMATIC )     EthIfCtrlReqMode0[1];

/* Array to store the transceiver error flag per EthIfCtrl */
VAR( boolean,          AUTOMATIC )          EthIfCtrl_TrcvError0[1];

/* Array to store the requested mode of EthIfCtrl */
VAR( EthTrcv_ModeType,      AUTOMATIC )     EthIf_TrcvIndMode0[1];

#define ETHIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

CONST(EthIf_CtrlStateType_tst, ETHIF_CONST) EthIf_EthIfCtrlState0_st =
{
	&EthIf_EthCtrlState0[0],								/* Pointer to an array, to store EthCtrl state within EthIf context */
	&EthIfCtrlMode0[0],                                     /* Pointer to an array, to store the Current mode of an EthIf Controller */
	&EthIfCtrlReqMode0[0],                                  /* Pointer to an array, to store the requested mode of EthIf Controller  */
	&EthIf_TrcvIndMode0[0],                                 /* Pointer to an array, to store the mode indicated by the transceiver */
	&EthIf_IsTrcvInit0[0],									/* Pointer to TrcvInit Flag */
	NULL_PTR,                                               /* Semantic is not standalone. */
	1,														/* EthIf Ctrl Count */
	1,														/* EthCtrl Count */
	1,												    	/* Max Transceiver Count */
	1,                                               		/* Number of EthIfTransceivers configured in EthIf */
	0,                                                      /* Number of EthIf Switches configured in EthIf */
	0,                                                      /* No Switch related configuration in EthIf. Numbe of EthSwtes is generated as 0 */
	0,                                                 		/* Number of EthIf SwitchPortGroups configured */
	0,                                                 		/* Number of standalone EthIf SwitchPortGroups configured */
	2,                                           			/* Number of Frame Owners */
	&EthIfCtrl_TrcvError0[0],                               /* Pointer to an array, to store whether error occured in transceiver */
};

#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

#define ETHIF_START_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

CONST(EthIf_ConfigType, ETHIF_CONST) EthIf_ConfigSet[1]=
{
	{
		&EthIfControllerConfig0_st[0],						/* Pointer to EthIfControllerConfig structure */
		&EthIfFrameOwnerConfig0_st[0],						/* Pointer to EthIfFrameOwnerConfig structure */
		&EthIf_EthIfCtrlState0_st,							/* Pointer to EthIfCtrlStateType Structure */
        NULL_PTR,                                           /* EthIf Switch PortGroups are not configured */
		NULL_PTR                                            /* EthIf Switch/EthIf SwitchPortGroups not present/configured */
	},
};

#define ETHIF_STOP_SEC_CONST_UNSPECIFIED
#include "EthIf_MemMap.h"

