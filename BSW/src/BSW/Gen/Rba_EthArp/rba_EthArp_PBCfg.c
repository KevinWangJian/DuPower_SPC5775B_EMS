/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/




/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( TCPIP_ARP_ENABLED == STD_ON )
#include "EthIf_Types.h"


#define RBA_ETHARP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"

/* ARP Component Configuration 0 */
/* ARP Table Entries per EthIfController */
VAR( rba_EthArp_ArpTable_tst, RBA_ETHARP_VAR ) rba_EthArp_Table_00_ast[20];   /*EthIfController*/

#define RBA_ETHARP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "rba_EthArp_MemMap.h"

#define RBA_ETHARP_START_SEC_CONST_UNSPECIFIED
#include "rba_EthArp_MemMap.h"
/* ARP Component Configuration 0 */

CONST ( rba_EthArp_SubConfig_to, RBA_ETHARP_CONST ) rba_EthArp_SubConfig_0_ast[1] =
{
	{   /* ARP Table Config for EthIfController */
			&rba_EthArp_Table_00_ast[0],                                           /* Pointer to ARP table */
			STD_OFF,                                                                /* Disable/Enable Ageing of Table entries */
			EthIfConf_EthIfController_EthIfController,    /* EthIfCtrl reference */
			0                                   /* Frame priority configured per TcpIpCtrl (TcpIpIpFramePrioDefault)  */                                                            /* Disable/Enable Ageing of Table entries */
	},
};
CONST ( rba_EthArp_Config_to, RBA_ETHARP_CONST ) rba_EthArp_Config_0_cst =
{	/* ARP configuration 0 */
	&rba_EthArp_SubConfig_0_ast[0],                                            /* Pointer to ARP SubConfig Struct */
	900000,                                                                    /* ARP Table Entry Timeout in milliseconds */
	2000,                                                                      /* ARP table pending entry timeout in milliseconds */
	20,                                                                       /* ARP Table Size Max */
	5,                                                                         /* Max ARP requests */
	1,                                                                         /* Number of ARP Tables */
	1                                                                          /* Number of Gratuitous ARP on Startup */
};

#define RBA_ETHARP_STOP_SEC_CONST_UNSPECIFIED
#include "rba_EthArp_MemMap.h"

#endif /* ( TCPIP_ARP_ENABLED == STD_ON ) */

