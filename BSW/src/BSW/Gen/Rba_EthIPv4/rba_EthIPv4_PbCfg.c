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

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "ComStack_Types.h"
#include "rba_EthIPv4_Cfg.h"
#include "TcpIp_Cfg.h"

#if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) )
#include "TcpIp_Types.h"
#include "rba_EthIPv4_Types.h"
#include "rba_EthIPv4_PbCfg.h"


    

#define RBA_ETHIPV4_START_SEC_CONST_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"

/* Controller 0 configuration */    
CONST ( rba_EthIPv4_CtrlCfg_tst, RBA_ETHIPV4_CONST )      rba_EthIPv4_Ctrl0Cfg_cst =
{
    1500U,                                               /* Specifies the maximum transmission unit (MTU) of the EthIfCtrl in bytes */
    TRUE                                                 /* Enable/Disable TTL                                                      */
};


/* This structure contains IPv4 controller configuration per EthIfCtrl. EthIf controllers which are not IPv4 controllers will have NULL_PTR */
CONSTP2CONST ( rba_EthIPv4_CtrlCfg_tst, RBA_ETHIPV4_CONST, RBA_ETHIPV4_CONST )      rba_EthIPv4_CtrlCfg_acpcst[TCPIP_NUMETHIFCTRL] =
{
    &rba_EthIPv4_Ctrl0Cfg_cst,                           /* IPv4 configuration for EthIfCtrl0     */   
};

/* IPv4 configuration structure */
CONST ( rba_EthIPv4_Config_to, RBA_ETHIPV4_CONST )      rba_EthIPv4_Config_0_cst =
{   
    ( &rba_EthIPv4_CtrlCfg_acpcst[0] ),    /* Pointer to Ctrl configuration structure         */
};

#define RBA_ETHIPV4_STOP_SEC_CONST_UNSPECIFIED
#include "rba_EthIPv4_MemMap.h"

#endif /* #if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) ) */
