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
 * $Generator__: rba_EthIPv4 / AR42.4.0.0                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4          	  ECU Parameter Definition Version
 ***************************************************************************************************
 </VersionHead>*/

#ifndef RBA_ETHIPV4_PBCFG_H
#define RBA_ETHIPV4_PBCFG_H


/*
 *************************************************************************************************
 * Extern declarations
 *************************************************************************************************
 */

#if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) )
#define RBA_ETHIPV4_START_SEC_CONST_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"

extern CONST ( rba_EthIPv4_Config_to, RBA_ETHIPV4_CONST )		rba_EthIPv4_Config_0_cst;

extern CONST ( rba_EthIPv4_CtrlCfg_tst, RBA_ETHIPV4_CONST )      rba_EthIPv4_Ctrl0Cfg_cst;

extern CONSTP2CONST ( rba_EthIPv4_CtrlCfg_tst, RBA_ETHIPV4_CONST, RBA_ETHIPV4_CONST )      rba_EthIPv4_CtrlCfg_acpcst[TCPIP_NUMETHIFCTRL];

#define RBA_ETHIPV4_STOP_SEC_CONST_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"


    



#endif /* #if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) ) */

#endif  /* RBA_ETHIPV4_PBCFG_H */


