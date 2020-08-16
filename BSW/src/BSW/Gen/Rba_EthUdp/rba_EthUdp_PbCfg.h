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
 * $Generator__: rba_EthUdp / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4          	  ECU Parameter Definition Version
 ***************************************************************************************************
 </VersionHead>*/

#ifndef RBA_ETHUDP_PBCFG_H
#define RBA_ETHUDP_PBCFG_H

#if ( TCPIP_UDP_ENABLED == STD_ON )

/*
 *************************************************************************************************
 * Extern declarations
 *************************************************************************************************
 */

#define RBA_ETHUDP_START_SEC_CONST_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

extern CONST ( rba_EthUdp_Config_to, RBA_ETHUDP_CONST )		rba_EthUdp_Config_0_cst;

#define RBA_ETHUDP_STOP_SEC_CONST_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

#define RBA_ETHUDP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

extern VAR( rba_EthUdp_DynSockTblType_tst, RBA_ETHUDP_DATA_VAR )     rba_EthUdp_DynSockTbl_ast[TCPIP_UDPSOCKETMAX];           /* Dynamic Udp socket table */

#define RBA_ETHUDP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

#define RBA_ETHUDP_START_SEC_CONST_8
#include "rba_EthUdp_MemMap.h"

extern CONST( uint8, RBA_ETHUDP_CONST )           rba_EthUdp_LocalAddressToCtrlMap_au8[1];

#define RBA_ETHUDP_STOP_SEC_CONST_8
#include "rba_EthUdp_MemMap.h"

#endif /* ( TCPIP_UDP_ENABLED == STD_ON ) */

#endif  /* RBA_ETHUDP_PBCFG_H */

