/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/





#ifndef RBA_ETHARP_PBCFG_H
#define RBA_ETHARP_PBCFG_H

#if ( TCPIP_ARP_ENABLED == STD_ON )

/*
 *************************************************************************************************
 * Extern Declarations
 *************************************************************************************************
 */


#define RBA_ETHARP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"
/* ARP Component Configuration 0 */
/* ARP Table Entries per EthIfController */
extern VAR( rba_EthArp_ArpTable_tst, RBA_ETHARP_VAR ) rba_EthArp_Table_00_ast[20]; /*EthIfController*/

#define RBA_ETHARP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"

#define RBA_ETHARP_START_SEC_CONST_UNSPECIFIED
#include "rba_EthArp_MemMap.h"
/* ARP Component Configuration 0 */
extern CONST ( rba_EthArp_SubConfig_to, RBA_ETHARP_CONST ) rba_EthArp_SubConfig_0_ast[1];

/* Extern declaration of ARP configuration structures in ROM */
extern CONST ( rba_EthArp_Config_to, RBA_ETHARP_CONST ) 	rba_EthArp_Config_0_cst;

#define RBA_ETHARP_STOP_SEC_CONST_UNSPECIFIED
#include "rba_EthArp_MemMap.h"

#endif /* ( TCPIP_ARP_ENABLED == STD_ON ) */
#endif  /* RBA_ETHARP_PBCFG_H */
