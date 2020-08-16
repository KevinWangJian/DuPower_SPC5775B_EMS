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

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "ComStack_Types.h"
#include "TcpIp_Cfg.h"

#ifdef TCPIP_CONFIGURED

#include "EthIf_Types.h"
#include "TcpIp_Types.h"
#include "TcpIp_PbCfg.h"

/*
 ***************************************************************************************************
 * Local Address Configuration - Start
 ***************************************************************************************************
 */

#define TCPIP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "TcpIp_MemMap.h"

/*  Array of RAM IP address structures to store the current assigned IP address in an LocalAddrId */
VAR( TcpIp_CurrAsgnedAddr_tst, TCPIP_DATA_VAR )        	 	TcpIp_CurrAsgnedAddr_ast[1];

/* TcpIp state variable for each EthIf controller */
VAR( TcpIp_StateType, TCPIP_DATA_VAR )                     	TcpIp_EthIfCtrlSt_aen[1] ;
VAR( TcpIp_StateType, TCPIP_DATA_VAR )                     	TcpIp_EthIfCtrlReqSt_aen[1] ;

#define TCPIP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "TcpIp_MemMap.h"

#define TCPIP_START_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"
VAR( TcpIp_IPAddrParamType_tun, TCPIP_DATA_VAR )        	TcpIp_StaticIpAddr_0_un =
{
	{
		{ {
			0x00000000uL,				/* Static IPv4 Address initialized to default value */
			0x00000000uL,				/* DefaultRouter IPv4 Address initialized to default value */
			0x0uL,						/* NetMask IPv4 initialized to default value */
			0x0uL						/* Default initialization values for the rest of the union bytes */
		} },
		{ { 0x0uL, 0x0uL, 0x0uL, 0x0uL } },                 /* Default initialization values for the rest of the union bytes */
		0x0u                                            	/* Default initialization values for the rest of the union bytes */
	}
};


#define TCPIP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "TcpIp_MemMap.h"

#define TCPIP_START_SEC_CONST_UNSPECIFIED
#include "TcpIp_MemMap.h"

CONST( TcpIp_AddrAssignment_tst, TCPIP_DATA_CONST )      TcpIp_AddrAsgnment_0_acst[1] =
{
    {
        TCPIP_IPADDR_ASSIGNMENT_STATIC,                   /* TcpIp_IpAddrAssignmentType  - Static/Linklocal/DHCP */
        TCPIP_MANUAL,                                   /* TcpIp_AssignmentTrigger_ten - Manual / Automatic */
        1,                                                 /* TcpIp_AssignmentPriority_u8 - */
    },
};


/*********** Static configured IP address configuration table. Derived from TCPIP SWS ***********/

/* TcpIp_LocalIPv4Addr_acst configuration structure - 0 */
CONST( TcpIp_LocalAddrConfig_to, TCPIP_DATA_CONST )           TcpIp_LocalAddrConfig_0_acst[1] =
{
    /* Local address identifier - 0 */
    {
        TCPIP_AF_INET,                                     /* IpDomainType_en         - AF_NET/AF_NET6                                         */
        TCPIP_UNICAST,                                     /*  IpAddressType_en     - Unicast/Multicast/Broadcast                              */
        (&(TcpIp_CurrAsgnedAddr_ast[0])),                  /* Pointer to dynamic (RAM) IP structure - TcpIp_CurrAssignedAddr_tst               */
        (&(TcpIp_AddrAsgnment_0_acst[0])),                /* Structure pointer to IPv4 address assignment structure - TcpIp_AddrAssignment_tst*/
        (&TcpIp_StaticIpAddr_0_un),                       /* Pointer to static IP address union */
        EthIfConf_EthIfController_EthIfController,              /* EthIfCtrlRef */
        0,                                                 /* Frame priority configured per TcpIpCtrl (TcpIpIpFramePrioDefault)                 */
        1                                                  /* Number of IP address assignments within local address identifier - 0 - NumAddrAssignments_u8 */
    }
};


/*
 ***************************************************************************************************
 * Local Address Configuration - End
 ***************************************************************************************************
 */


/*
 ***************************************************************************************************
 * TcpIp Configuration - Start
 ***************************************************************************************************
 */

/* Static configured TcpIp address configuration table. Derived from TCPIP SWS */
CONST( TcpIp_ConfigType, TCPIP_DATA_CONST )                  TcpIp_ConfigSet[TCPIP_NUM_CONFIG] =
{

    /* Configuration 0 */
    {
        ( & ( rba_EthUdp_Config_0_cst ) ),                /* UDP configuration structure - 0  - rba_EthUdp_Config_to */

        ( & ( rba_EthTcp_Config_cst ) ),                  /* TCP configuration structure      - rba_EthTcp_Config_to */
        ( & ( rba_EthIPv4_Config_0_cst ) ),               /* IPv4 configuration structure - 0  - rba_EthIPv4_Config_to */
        ( & ( rba_EthArp_Config_0_cst ) ),                /* ARP configuration structure - 0 - rba_EthArp_Config_to */



        ( & ( rba_EthIcmp_Config_0_cst ) ),               /* ICMP configuration structure - 0 - rba_EthIcmp_Config_to */

        ( & ( TcpIp_LocalAddrConfig_0_acst[0] ) ),        /* Local address configuration structure - 0  - TcpIp_LocalAddrConfig_to */
        
        
        1,                                                /* Number of local address identifiers in Configuration 0 */
    }

};

#define TCPIP_STOP_SEC_CONST_UNSPECIFIED
#include "TcpIp_MemMap.h"

#endif /* TCPIP_CONFIGURED */

/*
 ***************************************************************************************************
 * TcpIp Configuration - End
 ***************************************************************************************************
 */


