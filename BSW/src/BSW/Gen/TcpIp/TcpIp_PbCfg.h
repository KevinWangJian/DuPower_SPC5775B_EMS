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
 ***************************************************************************************************
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: TcpIp/ AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4          	  ECU Parameter Definition Version
 ***************************************************************************************************
 </VersionHead>*/

#ifndef TCPIP_PBCFG_H
#define TCPIP_PBCFG_H


#include "TcpIp_Cfg.h"

#include "rba_EthIPv4_PbCfg.h"
#include "rba_EthArp_PbCfg.h"
#include "rba_EthTcp_PbCfg.h"
#include "rba_EthUdp_PbCfg.h"
#include "rba_EthIcmp_PbCfg.h"

/**************************************************************************************************/
/************************************** Extern declarations	***************************************/
/**************************************************************************************************/
#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "TcpIp_MemMap.h"

extern CONST( TcpIp_ConfigType, TCPIP_DATA_CONST ) 				TcpIp_ConfigSet[1];
extern CONST( TcpIp_AddrAssignment_tst, TCPIP_DATA_CONST )  	TcpIp_AddrAsgnment_0_acst[1];

extern CONST( TcpIp_LocalAddrConfig_to, TCPIP_DATA_CONST )		TcpIp_LocalAddrConfig_0_acst[1];

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "TcpIp_MemMap.h"
#define TCPIP_START_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"

extern VAR( TcpIp_IPAddrParamType_tun, TCPIP_DATA_VAR )       	TcpIp_StaticIpAddr_0_un;
#define TCPIP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"

#define TCPIP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "TcpIp_MemMap.h"

extern VAR( TcpIp_CurrAsgnedAddr_tst, TCPIP_DATA_VAR ) 			TcpIp_CurrAsgnedAddr_ast[1];

/* TcpIp state variable for each EthIf controller */
extern VAR( TcpIp_StateType, TCPIP_DATA_VAR )					TcpIp_EthIfCtrlSt_aen[1];
extern VAR( TcpIp_StateType, TCPIP_DATA_VAR )					TcpIp_EthIfCtrlReqSt_aen[1];

#define TCPIP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "TcpIp_MemMap.h"

#endif  /* TCPIP_PBCFG_H */


