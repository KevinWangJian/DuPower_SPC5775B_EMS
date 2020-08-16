

#ifndef ETHIF_H
#define ETHIF_H

#include "EthIf_Types.h"
#include "EthIf_PbCfg.h"

#ifdef ETHIF_CONFIGURED

/* Vendor Id */
#define ETHIF_VENDOR_ID  					6U

/* EthIf module Id */
#define ETHIF_MODULE_ID						65U

/* EthIf instance Id */
#define ETHIF_INSTANCE_ID					0x0U

/* Software Version Info */
#define ETHIF_SW_MAJOR_VERSION  			4U
#define ETHIF_SW_MINOR_VERSION  			0U
#define ETHIF_SW_PATCH_VERSION  			0U

/* AUTOSAR Version Info */
#define ETHIF_AR_RELEASE_MAJOR_VERSION 	 	4
#define ETHIF_AR_RELEASE_MINOR_VERSION  	2
#define ETHIF_AR_RELEASE_REVISION_VERSION 	2

/*  Frame types */
#define ETHIF_FRAMETYP_ARP        			0x0806U
#define ETHIF_FRAMETYP_IPv4       			0x0800U
#define ETHIF_FRAMETYP_IPv6       			0x86DDU
#define ETHIF_FRAMETYP_VLAN       			0x8100U
#define ETHIF_FRAMETYP_AVB          		0x88B5U     /* Audio Video Bridge Protocol type */
#define ETHIF_FRAMETYP_PTP          		0x88F7U     /* Precision Time Protocol type */

#define RBA_ETHIF_CODE

#define ETHIF_START_SEC_CODE
#include "EthIf_MemMap.h"
/* ETHIF024: Initializes the Ethernet Interface */
FUNC(void, RBA_ETHIF_CODE) EthIf_Init( P2CONST(EthIf_ConfigType,AUTOMATIC, AUTOMATIC) CfgPtr );

/* ETHIF034: Enables / disables the indexed controller */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_SetControllerMode(   VAR(uint8, AUTOMATIC)           CtrlIdx,
                                                                VAR(Eth_ModeType, AUTOMATIC)    CtrlMode );

/* ETHIF039: Obtains the state of the indexed controller */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_GetControllerMode( 	VAR(uint8, AUTOMATIC) 						CtrlIdx,
																P2VAR(Eth_ModeType, AUTOMATIC, AUTOMATIC) 	CtrlModePtr );

/* ETHIF061: Obtains the physical source address used by the indexed controller */
FUNC(void, RBA_ETHIF_CODE) EthIf_GetPhysAddr( 		VAR(uint8, AUTOMATIC) 				CtrlIdx,
													P2VAR(uint8, AUTOMATIC, AUTOMATIC) 	PhysAddrPtr );

/* ETHIF067: Provides access to a transmit buffer of the specified Ethernet controller */
FUNC(BufReq_ReturnType, RBA_ETHIF_CODE) EthIf_ProvideTxBuffer(	VAR( uint8,			AUTOMATIC )				                       CtrlIdx,
																VAR( Eth_FrameType,	AUTOMATIC )				                       FrameType,
																VAR( uint8,			AUTOMATIC )				                       Priority,
																P2VAR( uint8,		AUTOMATIC, AUTOMATIC )	                       BufIdxPtr,
																P2VAR(P2VAR(uint8,  AUTOMATIC, AUTOMATIC), AUTOMATIC, AUTOMATIC)   BufPtr,
																P2VAR( uint16,		AUTOMATIC, AUTOMATIC )	                       LenBytePtr );

/* ETHIF075: Triggers transmission of a previously filled transmit buffer */
FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_Transmit(	VAR( uint8,			AUTOMATIC )				CtrlIdx,
														VAR( uint8,			AUTOMATIC )				BufIdx,
														VAR( Eth_FrameType,	AUTOMATIC )				FrameType,
														VAR( boolean,		AUTOMATIC )				TxConfirmation,
														VAR( uint16,		AUTOMATIC )				LenByte,
														P2VAR( uint8,		AUTOMATIC, AUTOMATIC )	PhysAddrPtr );

#if( ETHIF_ENABLE_GLOBAL_TIME_SUPPORT == STD_ON )

FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_GetCurrentTime(    VAR  ( uint8,                   AUTOMATIC)             CtrlIdx,
                                                              P2VAR( Eth_TimeStampQualType,   AUTOMATIC, AUTOMATIC ) timeQualPtr,
                                                              P2VAR( Eth_TimeStampType,       AUTOMATIC, AUTOMATIC ) timeStampPtr );

FUNC( void, RBA_ETHIF_CODE ) EthIf_EnableEgressTimeStamp(   VAR( uint8,     AUTOMATIC )             CtrlIdx,
		                                                    VAR( uint8,     AUTOMATIC )             BufIdx  );

FUNC( void, RBA_ETHIF_CODE ) EthIf_GetEgressTimeStamp(   VAR( uint8,     AUTOMATIC )                            CtrlIdx,
		                                                 VAR( uint8,     AUTOMATIC )                            BufIdx,
		                                                 P2VAR( Eth_TimeStampQualType,  AUTOMATIC, AUTOMATIC )  timeQualPtr,
		                                                 P2VAR( Eth_TimeStampType,  AUTOMATIC, AUTOMATIC )      timeStampPtr );

FUNC(void, RBA_ETHIF_CODE) EthIf_GetIngressTimeStamp( VAR    ( uint8,                 AUTOMATIC )            CtrlIdx,
                                                      P2VAR( Eth_DataType,          AUTOMATIC, AUTOMATIC ) DataPtr,
                                                      P2VAR  ( Eth_TimeStampQualType, AUTOMATIC, AUTOMATIC ) timeQualPtr,
                                                      P2VAR  ( Eth_TimeStampType,     AUTOMATIC, AUTOMATIC ) timeStampPtr );

#endif

/* ETHIF082: Returns the version information of this module */
FUNC(void, RBA_ETHIF_CODE) EthIf_GetVersionInfo( 				P2VAR(Std_VersionInfoType, AUTOMATIC, AUTOMATIC) VersionInfoPtr );

extern FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_UpdatePhysAddrFilter( 	VAR(uint8, AUTOMATIC) 					CtrlIdx,
																			P2CONST(uint8, AUTOMATIC, AUTOMATIC) 	PhysAddrPtr,
																			VAR(Eth_FilterActionType, AUTOMATIC) 	Action );

extern FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_SwitchPortGroupRequestMode( EthIf_SwitchPortGroupIdxType PortGroupIdx,
                                                                              EthTrcv_ModeType PortMode );

extern FUNC(Std_ReturnType, RBA_ETHIF_CODE) EthIf_StartAllPorts( void );

#if( ETHIF_ENABLE_ETHIF_GET_VLANID == STD_ON )

extern FUNC( Std_ReturnType, TCPIP_CODE )  EthIf_GetVlanId(   VAR( uint8, AUTOMATIC )                                 CtrlIdx,
                                                              P2VAR( uint16, AUTOMATIC, AUTOMATIC )                   VlanIdPtr );

#endif

/*
 ***************************************************************************************************
 * Scheduled
 ***************************************************************************************************
 */


/* ETHIF097: The function checks for new received frames and issues transmission confirmations in polling mode. It checks also for transceiver state changes. */
FUNC(void, RBA_ETHIF_CODE) EthIf_MainFunctionRx( void );

/* ETHIF113: The function issues transmission confirmations in polling mode. It checks also for transceiver state changes. */
FUNC(void, RBA_ETHIF_CODE) EthIf_MainFunctionTx( void );

/* The function is polling the link state of the used communication hardware (Ethernet transceiver, Ethernet switch ports). */
FUNC(void, RBA_ETHIF_CODE) EthIf_MainFunctionState( void );

#define ETHIF_STOP_SEC_CODE
#include "EthIf_MemMap.h"

#endif /* ETHIF_CONFIGURED */

#endif /* ETHIF_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
