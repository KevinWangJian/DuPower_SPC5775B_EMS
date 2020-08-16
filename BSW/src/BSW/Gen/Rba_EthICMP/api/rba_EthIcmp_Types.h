
#ifndef RBA_ETHICMP_TYPES_H
#define RBA_ETHICMP_TYPES_H

#if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) )

#include "TcpIp_GeneralTypes.h"

#include "Dem.h"

/*
****************************************************************************************************
*                                   Structures
****************************************************************************************************
*/

typedef enum
{
    RBA_ETHICMP_DEST_UNREACH_NET_E                  = 0U,   /* Destination network unreachable */
    RBA_ETHICMP_DEST_UNREACH_HOST_E                 = 1U,   /* Destination host unreachable */
    RBA_ETHICMP_DEST_UNREACH_PROTO_E                = 2U,   /* Destination protocol unreachable */
    RBA_ETHICMP_DEST_UNREACH_PORT_E                 = 3U,   /* Destination port unreachable */
    RBA_ETHICMP_DEST_UNREACH_FRAG_E                 = 4U,   /* Fragmentation required, and DF flag set */
    RBA_ETHICMP_DEST_UNREACH_SRC_FAIL_E             = 5U    /* Source route failed */
}rba_EthIcmp_DestUnreach_ten;

typedef enum
{
    RBA_ETHICMP_TIME_EXCEED_TTL_E                   = 0U,   /* TTL expired in transit */
    RBA_ETHICMP_TIME_EXCEED_FRAG_E                  = 1U    /* Fragment reassembly time exceeded */
}rba_EthIcmp_TimeExceed_ten;

typedef enum
{
    RBA_ETHICMP_ECHO_REPLY_E                        = 0U,   /* Echo Reply */
    RBA_ETHICMP_RESERVED_1_E                        = 1U,   /* Reserved */
    RBA_ETHICMP_RESERVED_2_E                        = 2U,   /* Reserved */
    RBA_ETHICMP_DEST_UNREACH_E                      = 3U,   /* Destination Unreachable */
    RBA_ETHICMP_SRC_QUENCH_E                        = 4U,   /* Source Quench */
    RBA_ETHICMP_REDIRECT_MSG_E                      = 5U,   /* Redirect Message */
    RBA_ETHICMP_ALT_HOST_ADDR_E                     = 6U,   /* Alternate Host Address */
    RBA_ETHICMP_RESERVED_7_E                        = 7U,   /* Reserved */
    RBA_ETHICMP_ECHO_REQ_E                          = 8U,   /* Echo Request */
    RBA_ETHICMP_ROUTER_ADVRTMNT_E                   = 9U,   /* Router Advertisement*/
    RBA_ETHICMP_ROUTER_SOLICIT_E                    = 10U,  /* Router Solicitation */
    RBA_ETHICMP_TIME_EXCEED_E                       = 11U,  /* Time Exceeded */
    RBA_ETHICMP_PRM_PRBLM_E                         = 12U,  /* Parameter Problem: Bad IP header */
    RBA_ETHICMP_TIMESTAMP_E                         = 13U,  /* Timestamp */
    RBA_ETHICMP_TIMESTAMP_RPLY_E                    = 14U,  /* Timestamp Reply */
    RBA_ETHICMP_INFO_REQ_E                          = 15U,  /* Information Request */
    RBA_ETHICMP_INFO_RPLY_E                         = 16U,  /* Information Reply */
    RBA_ETHICMP_ADDR_MSK_REQ_E                      = 17U,  /* Address Mask Request */
    RBA_ETHICMP_ADDR_MSK_RPLY_E                     = 18U,  /* Address Mask Reply */
    RBA_ETHICMP_TRACE_ROUTE_E                       = 30U,  /* Traceroute */
    RBA_ETHICMP_DATA_CONV_ERR_E                     = 31U,  /* Datagram Conversion Error */
    RBA_ETHICMP_WHERE_ARE_YOU_E                     = 33U,  /* Where-Are-You */
    RBA_ETHICMP_HERE_I_AM_E                         = 34U,  /* Here-I-Am */
    RBA_ETHICMP_DOMAIN_NAME_REQ_E                   = 37U,  /* Domain Name Request */
    RBA_ETHICMP_DOMAIN_NAME_RPLY_E                  = 38U   /* Domain Name Reply */
}rba_EthIcmp_CtrlMsgTyp_ten;

/*
 * This container is a sub-container of rba_EthIcmp_Config_to and defines the
 * specific configuration parameters of the ICMP (Internet Control Message Protocol) sub-module
 */
typedef struct
{
	CONST( Dem_EventIdType,               AUTOMATIC )                DemEventId_ConRefused_u16;       /* Holds Id for TCPIP_E_CONNREFUSED if TCPIP_E_CONNREFUSED is configured. Holds 0 if TCPIP_E_CONNREFUSED is not configured */
	CONST( uint8,                         AUTOMATIC )                EchoBroadcastEn_cu8;             /* Reply to Broadcast echo requests is enabled or not for each LocalAddrId */
	CONST( uint8,                         AUTOMATIC )                TcpIpCtrlFramePrio_cu8;          /* Frame priority configured per TcpIpCtrl (TcpIpIpFramePrioDefault)       */
}rba_EthIcmp_SubConfig_to;

/*
 * This container is a sub-container of TcpIpConfig and specifies the
 * configuration parameters of the ICMP sub-module
 */
typedef struct
{
    /* Pointer to ICMP SubConfig Structure */
    const rba_EthIcmp_SubConfig_to  * IcmpSubConfig_pco;

    P2FUNC( Std_ReturnType, AUTOMATIC,  IcmpRxIndication_pfct )(    VAR  ( TcpIp_LocalAddrIdType , AUTOMATIC )                LocalAddrId_u8,
                                                                    P2VAR( TcpIp_SockAddrInetType, AUTOMATIC , AUTOMATIC )    RemoteAddr_pst,
                                                                    VAR  ( uint8,                  AUTOMATIC )                Ttl_u8,
                                                                    VAR  ( uint8,                  AUTOMATIC )                Type_u8,
                                                                    VAR  ( uint8,                  AUTOMATIC )                Code_u8,
                                                                    VAR  ( uint16,                 AUTOMATIC )                DataLength_u16,
                                                                    P2VAR( uint8,                  AUTOMATIC , AUTOMATIC )    Data_pu8 );

    VAR( uint8, AUTOMATIC )                                         Ttl_u8;
}rba_EthIcmp_Config_to;

/* Size of data in port unreachable frame is ( IPv4 header length ) + ( 8 bytes of transport layer header ) */
#define RBA_ETHICMP_DEST_UNREACH_DATASIZE           8U

/****************************************************************************************************************
**                                   Global Function Prototypes                                                **
****************************************************************************************************************/

#endif /* #if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHICMP_TYPES_H */
