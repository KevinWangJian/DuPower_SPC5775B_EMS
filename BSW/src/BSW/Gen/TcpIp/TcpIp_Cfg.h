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

#ifndef TCPIP_CFG_H
#define TCPIP_CFG_H


#include "ComStack_Types.h"
#include "rba_EthIPv4_Cfg.h"
#include "rba_EthTcp_Cfg.h"
#include "rba_EthUdp_Cfg.h"
#include "rba_EthArp_Cfg.h"
#include "rba_EthIcmp_Cfg.h"


/*
 *************************************************************************************************
 * Defines
 *************************************************************************************************
 */

/* If macro is not defined APIs defined in TcpIp.c file will not be compiled */
#define TCPIP_CONFIGURED

/* Number of TCP-IP General Configurations. */
#define TCPIP_NUM_CONFIG									(1UL)

/* If true then TCP/IP will enable the error-reporting to the Development Error Tracer (DET). */
#define TCPIP_DEV_ERROR_DETECT   							(STD_ON)

/* If true the TcpIp_GetVersionInfo API is available.*/
#define TCPIP_VERSION_INFO_API 								(STD_OFF)

/* If configured Scalability Class is 1, then enable IPv4 specific code. */
#define TCPIP_IPV4_ENABLED									(STD_ON)

/* If configured Scalability Class is 2 then enable IPv6 specific code. */
#define TCPIP_IPV6_ENABLED									(STD_OFF)

/* Enables (TRUE) or disabled (FALSE) support of ICMP (Internet Control Message Protocol) */
#define TCPIP_ICMP_ENABLED 									(STD_ON)

/* Enables (TRUE) or disabled (FALSE) support of ICMPv6 (Internet Control Message Protocol for IPv6) */
/* (ICMPv6 is implicitly enabled if IPv6 is enabled) */
#define TCPIP_ICMPV6_ENABLED 								(STD_OFF)

/* Enables (TRUE) or disabled (FALSE) support of TCP (Transmission Control Protocol) */
#define TCPIP_TCP_ENABLED 									(STD_ON)

/* Enables (TRUE) or disabled (FALSE) support of UDP (User Datagram Protocol) */
#define TCPIP_UDP_ENABLED 									(STD_ON)

/* Enables (TRUE) or disables (FALSE) the DHCP (Dynamic Host Configuration Protocol) Client. */
#define TCPIP_DHCP_CLIENT_ENABLED							(STD_OFF)

/* Enables (TRUE) or disables (FALSE) the DHCPv6 (Dynamic Host Configuration Protocol for IPv6) Client. */
#define TCPIP_DHCPV6_CLIENT_ENABLED							(STD_OFF)

/* Enables (TRUE) or disables (FALSE) the Auto-IP (automatic private IP addressing) sub-module. */
#define TCPIP_AUTOIP_ENABLED								(STD_OFF)

/* Enables (TRUE) or disabled (FALSE) support of ARP (Address Resolution Protocol) */
#define TCPIP_ARP_ENABLED 									(STD_ON)

/* Enables (TRUE) or disabled (FALSE) support of NDP (Neighbout Discovery Protocol) */
#define TCPIP_NDP_ENABLED 									(STD_OFF)

/* Enables (TRUE) or disabled (FALSE) support of IP Addr. Conflict detection for the ARP frames*/
#define TCPIP_IP_ADDR_CONFLICT_DETECTION_ARP_FRAMES 		(STD_ON)


/* Enables (TRUE) or disabled (FALSE) support of IP Addr. Conflict detection for the IPV4 frames*/
#define TCPIP_IP_ADDR_CONFLICT_DETECTION_IP_FRAMES          (STD_ON)


/* Period of TcpIp_MainFunction in milli seconds */
#define TCPIP_MAIN_FUNCTIONPERIOD_US						(10)


/* Maximum number of TCP sockets */
#define TCPIP_TCPSOCKETMAX									(5)

/* Maximum number of UDP sockets */
#define TCPIP_UDPSOCKETMAX									(5)


/* Total number of sockets */
#define TCPIP_SOCKETMAX										(10)

/* Maximum configured EthIf controllers */
#define TCPIP_NUMETHIFCTRL									1

/* Definition of supported module variant. */
#define TCPIP_CFG_VARIANT_PRE_COMPILE     0U

/* Macro to hold configured module variant. Hardcoded to pre-compile since Post build is not yet supported. */
#define TCPIP_CFG_CONFIGURATION_VARIANT                     TCPIP_CFG_VARIANT_PRE_COMPILE

/*****************************************************************************************/
/*                           TcpIpLocalAddr Symbolic Names                               */
/*****************************************************************************************/

#define TcpIpConf_TcpIpLocalAddr_TcpIpLocalAddr       ((uint8)0)

/*****************************************************************************************/

#define TcpIp_Config (TcpIp_ConfigSet[0])

#endif  /* TCPIP_CFG_H */

