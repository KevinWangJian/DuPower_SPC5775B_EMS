/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/

        

#ifndef RBA_ETHTCP_PBCFG_H
#define RBA_ETHTCP_PBCFG_H


#if ( TCPIP_TCP_ENABLED == STD_ON )

/*
 *************************************************************************************************
 * Extern declarations
 *************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CONST_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"
extern CONST( rba_EthTcp_Config_to, RBA_ETHTCP_DATA_CONST )         rba_EthTcp_Config_cst;

extern CONST( uint16, RBA_ETHTCP_DATA_CONST )                       rba_EthTcp_MSS_cau16[RBA_ETHTCP_MAX_LOCALADDRID];
#define RBA_ETHTCP_STOP_SEC_CONST_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"

#define RBA_ETHTCP_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"
extern VAR( rba_EthTcp_SockOpt_tst, RBA_ETHTCP_VAR )  				rba_EthTcp_SockOpt_ast[TCPIP_TCPSOCKETMAX];

extern VAR( rba_EthTcp_DynSockTblType_tst, RBA_ETHTCP_VAR )  		rba_EthTcp_DynSockTbl_ast[TCPIP_TCPSOCKETMAX];
#define RBA_ETHTCP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"

#endif /* ( TCPIP_TCP_ENABLED == STD_ON ) */

#endif  /* RBA_ETHTCP_PBCFG_H */

