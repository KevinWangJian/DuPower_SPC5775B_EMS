/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/






#ifndef RBA_ETHICMP_PBCFG_H
#define RBA_ETHICMP_PBCFG_H

#if ( TCPIP_ICMP_ENABLED == STD_ON )

/*
 *************************************************************************************************
 * Extern Declarations
 *************************************************************************************************
 */

#define RBA_ETHICMP_START_SEC_CONST_UNSPECIFIED
#include "rba_EthIcmp_MemMap.h"

/* ICMP Component Configuration 0 */
extern CONST ( rba_EthIcmp_Config_to, RBA_ETHICMP_CONST )   rba_EthIcmp_Config_0_cst;

extern CONST ( rba_EthIcmp_SubConfig_to, RBA_ETHICMP_CONST ) rba_EthIcmp_SubConfig_0_ast[]; 

#define RBA_ETHICMP_STOP_SEC_CONST_UNSPECIFIED
#include "rba_EthIcmp_MemMap.h"
#endif /* ( TCPIP_ICMP_ENABLED == STD_ON ) */

#endif  /* RBA_ETHICMP_PBCFG_H */


