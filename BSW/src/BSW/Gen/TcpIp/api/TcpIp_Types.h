

#ifndef TCPIP_TYPES_H
#define TCPIP_TYPES_H

#include "TcpIp_Cfg.h"		/* Required for TCPIP_CONFIGURED */

#ifdef TCPIP_CONFIGURED

#include "TcpIp_GeneralTypes.h"

#include "Eth_GeneralTypes.h"

#if (TCPIP_IPV4_ENABLED == STD_ON)
#include "rba_EthIPv4_Types.h"
#endif

#if (TCPIP_IPV6_ENABLED == STD_ON)
#include "rba_EthIPv6_Types.h"
#endif

#if (TCPIP_TCP_ENABLED == STD_ON)
#include "rba_EthTcp_Types.h"
#endif

#if (TCPIP_UDP_ENABLED == STD_ON)
#include "rba_EthUdp_Types.h"
#endif

#if (TCPIP_ARP_ENABLED == STD_ON)
#include "rba_EthArp_Types.h"
#endif

#if (TCPIP_AUTOIP_ENABLED == STD_ON)
#include "rba_EthAutoIp_Types.h"
#endif

#if (TCPIP_ICMP_ENABLED == STD_ON)
#include "rba_EthIcmp_Types.h"
#endif

#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP_Types.h"
#endif

#if ( TCPIP_ICMPV6_ENABLED == STD_ON )
#include "rba_EthIcmpV6_Types.h"
#endif

#if ( TCPIP_NDP_ENABLED == STD_ON )
#include "rba_EthNdp_Types.h"
#endif

/* This container is a sub-container of TcpIpLocalAddr and specifies the assignment policy for the IP address. */
typedef struct
{
    TcpIp_IpAddrAssignmentType					AddrAsgnmentMeth_en;        /* Configured IP assignment Type (TcpIp_IpAddrAssignmentType)                                   */
	TcpIp_AssignmentTrigger_ten					AddrAsgnmentTrig_en;        /* Configured IP assignment trigger  (TcpIpAssignmentTrigger)                               */
	TcpIp_AssignmentPrio_tu8				    AsgnmentPrio_u8;            /* Configured IP assignment priority (tcpIpAssignmentPriority). If a new address from an assignment method */
	                                                                        /* with a higher priority is available,  it overwrites the IP address previously assigned by */
	                                                                        /* an assignment method with a lower priority. Priority range - 1 .. 3   (1 is highest)      */
} TcpIp_AddrAssignment_tst;


/* This container is a sub-container of TcpIpLocalAddr and specifies a static IP address including directly related parameters. */
typedef struct
{
	uint32										IpAddr_u32;                 /* Assigned IPv4 address                                                                      */
	uint32					                    DftRtr_u32;                 /* Assigned IP address of default router (gateway)                                            */
	uint32							            NetMask_u32;                /* Network mask of IPv4 address                                                               */
} TcpIp_IPv4AddrParamType_tst;


/** Structure to hold IPv6 addresses.*/
typedef struct
{
    uint32 Addr_au32[4];
} TcpIp_IPv6Addr_tst;


typedef struct
{
	TcpIp_IPv6Addr_tst                          IpAddr_st;                  /* Assigned  address                                                                  */
	TcpIp_IPv6Addr_tst                          DftRtr_st;                  /* Assigned IP address of default router (gateway)                                    */
	uint8                                       NetMask_u8;                 /* Prefix lenght of IPv6 (in CIDR notation)                                           */
} TcpIp_IPv6AddrParamType_tst;


/**
	IPversion specific IP addr parameters storage type.
	DD: use an union to allow both, IPv6 and IPv4 to be stored at the same time
		AND still to benefit from strong type checks of the C language.
	Alternative: use a void* which can be casted as needed. (less safe)
*/
typedef union
{
	TcpIp_IPv6AddrParamType_tst                 IPv6Par_st;
	TcpIp_IPv4AddrParamType_tst                 IPv4Par_st;
} TcpIp_IPAddrParamType_tun;


typedef struct
{
    TcpIp_IpAddrAssignmentType                  CurrAsgnedAddrMeth_en;      /* IP address method assigned is enabled in TcpIp_ReqComMode() and only then                */
                                                                            /*  API calls are accepted.                                                                 */
	TcpIp_AssignmentPrio_tu8				    CurrAsgnedAddrPrio_u8;      /* Current assigned IP address priority.                                                    */
	uint8                                       ReqAddrAssgnMeth_u8;        /* Set by TcpIp_RequestIpAddrAssignment() for MANUAL IP assignment trigger, set before IP assignment */
                                                                            /* process for AUTOMATIC IP assignment trigger and cleared after IP assignment is successfully initiated. */
	TcpIp_IPAddrParamType_tun				    IpAddrParams_un;            /* Stores the IP address, the default router address and the netmask value.                 */
} TcpIp_CurrAsgnedAddr_tst;


/* This container is a sub-container of TcpIpConfig and specifies the local IP (Internet Protocol) addresses used for IP communication. */
typedef struct
{
    TcpIp_DomainType                            IpDomainType_u32;           /* Address family                                                                             */
    TcpIp_AddressType                           IpAddressType_en;           /* Address type                                                                               */
    TcpIp_CurrAsgnedAddr_tst                    * CurrAsgnedAddr_pst;       /* Specifies a dynamic IP address including directly related parameters                       */
    const TcpIp_AddrAssignment_tst              * AddrAsgnment_pcst;        /* Specifies the assignment policy for the IP address                                         */
    TcpIp_IPAddrParamType_tun					* StaticIpAddr_pun;         /* Pointer to static IP address structure                                                     */
	uint8									    EthIfCtrlRef_u8;            /* Reference to a TcpIpCtrl specifying the EthIf Controller where the IP address shall be     */
	                                                                        /* assigned and DEM errors that shall be reported in case of an error on this controller.     */
	uint8                                       TcpIpCtrlFramePrio_u8;      /* Frame priority configured per TcpIpCtrl (TcpIpIpFramePrioDefault)                          */
	uint8								        NumAddrAsgnment_u8;         /* Number of IP address assignments in a TcpIpAddrAssignments container                       */
} TcpIp_LocalAddrConfig_to;


/* Configuration data structure of the TcpIp module. */
typedef struct
{
	#if (TCPIP_UDP_ENABLED == STD_ON)
	const rba_EthUdp_Config_to					* EthUdpConfig_pco;         /* Pointer to configuration data structure of the UDP module.                                 */
	#endif

	#if (TCPIP_TCP_ENABLED == STD_ON)
	const rba_EthTcp_Config_to					* EthTcpConfig_pco;         /* Pointer to configuration data structure of the TCP module.                                 */
	#endif

	#if (TCPIP_IPV4_ENABLED == STD_ON)
	const rba_EthIPv4_Config_to					* EthIPv4Config_pco;        /* Pointer to configuration data structure of the IPv4 module.                                */
	#endif

	#if (TCPIP_IPV6_ENABLED == STD_ON)
	const rba_EthIPv6_Config_to					* EthIPv6Config_pco;        /* Pointer to configuration data structure of the IPv6 module.                                */
	#endif

	#if (TCPIP_ARP_ENABLED == STD_ON)
	const rba_EthArp_Config_to					* EthArpConfig_pco;         /* Pointer to configuration data structure of the ARP module.                                  */
	#endif

	#if (TCPIP_AUTOIP_ENABLED == STD_ON)
	const rba_EthAutoIp_Config_to				* EthAutoIpConfig_pco;      /* Pointer to configuration data structure of the AUTOIP module.                              */
	#endif

	#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
	const rba_EthDHCP_Config_to					* EthDHCPConfig_pco;        /* Pointer to configuration data structure of the DHCP module.                                */
	#endif

    #if (TCPIP_ICMP_ENABLED == STD_ON)
	const rba_EthIcmp_Config_to				    * EthIcmpConfig_pco;
	#endif

    const TcpIp_LocalAddrConfig_to              * EthLocalAddrConfig_paco;  /* Pointer to configuration data structure of the local IPv4 addresses.                       */

    #if ( TCPIP_ICMPV6_ENABLED == STD_ON )
    const rba_EthIcmpV6_Config_to               * EthIcmpV6Config_pco;      /* Pointer to configuration data structure of the ICMPv6 module.                              */
    #endif

    #if ( TCPIP_NDP_ENABLED == STD_ON )
    const rba_EthNdp_Config_to                  * EthNdpConfig_pco;			/* Pointer to configuration data structure of the NDP module.                              */
    #endif

    const TcpIp_LocalAddrIdType                 NumLocalAddrConfig_u8;      /* Number of localAddress configured                                                          */
} TcpIp_ConfigType;


typedef struct
{
	uint32										TcpIpMainFunctionPeriod;
} TcpIp_GeneralConfig_to;


/* Structure used by APIs to specify IPv4 header content */
typedef struct
{
	TcpIp_ProtocolType			                ProtoType_en;		        /* protocol type: Udp/Tcp/Icmp                                                                */
	uint8						                Ttl_u8		;		        /* time to live value                                                                         */
} TcpIp_IpHeader_tst;


/* Union to store either an IPv4 address or a pointer to an IPv6 address. */
typedef union
{
    uint32	                                    IPv4Addr_u32;
    const uint32*	                            IPv6Addr_pcu32;
} TcpIp_IpAddr_tun;


/* Structure contains pseudo header information ( protocol type, local IP and Remote IP in Tx/Rx buffer) required for Udp and Tcp checksum calculation */
typedef struct
{
	TcpIp_DomainType							IpDomainType_t;				/* AF_INET or AF_INET6                                                                      */
	TcpIp_ProtocolType			                ProtoType_en;               /* Transport layer protocol                                                                 */
    uint8						                IPv4HdrLen_u8;                /* IP header length                                                                         */
	TcpIp_IpAddr_tun                            LocalIpAddr_un;             /* The local IP address (IPv4 or IPv6).                                                     */
	TcpIp_IpAddr_tun                            RemoteIpAddr_un;             /* The local IP address (IPv4 or IPv6).                                                     */
	boolean                                     IsRxFragmented_b;           /* Indication from IPv4 layer to transport layer that the received frame is reassembled one.
                                                                               This is currently used only by rba_EthTcp for checksum verification.                     */
} TcpIp_PseudoHdr_tst;

/* Union to hold the index of either local AddrId or EthIf controller */
typedef union
{
    TcpIp_LocalAddrIdType                       LocalAddrId_u8;             /* Local Address Id */
    uint8                                       EthIfCtrlIdx_u8;            /* EthIf controller index */
} TcpIp_LocalAddrId_EthIfCtrl_tun;

#endif /* #ifdef TCPIP_CONFIGURED */

#endif /* TCPIP_TYPES_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
