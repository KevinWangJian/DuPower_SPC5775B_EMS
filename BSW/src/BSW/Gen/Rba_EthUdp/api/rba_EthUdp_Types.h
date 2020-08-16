

#ifndef RBA_ETHUDP_TYPES_H
#define RBA_ETHUDP_TYPES_H

#if ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) )

#include "TcpIp_GeneralTypes.h"

/* Socket state in socket table */
typedef enum
{
    RBA_ETHUDP_SOCK_CLOSED             = 0x00U,             /* Socket is free                                                                  */
    RBA_ETHUDP_SOCK_OPEN               = 0x01U,             /* Socket is reserved by upper layer. (rba_EthUdp_GetSocket() is called )          */
    RBA_ETHUDP_SOCK_BOUND              = 0x02U             /* Socket is bound to particular localAddress ( rba_EthUdp_GetSocket() is called)  */
}rba_EthUdp_SocketState_ten;


/* This container is a subcontainer of TcpIpConfig and specifies the configuration parameters of the UDP (User Datagram Protocol) sub-module */
typedef struct
{
	/* Default Time-to-live value of outgoing UDP packets. */
	uint8							Ttl_u8;
}rba_EthUdp_Config_to;


/* Structure template for Udp sockets */
typedef struct
{
    TcpIp_DomainType                DomainType_u32;     /* Domain - IPv4/IPv6                                                       */
    rba_EthUdp_SocketState_ten      SockState_en;      /* Socket state                                                             */
    uint16                          LocalPort_u16;     /* Local port used for the communication on the cuurent socket              */
    TcpIp_LocalAddrIdType           LocalAddrId_u8;    /* LocalAddrId used for the communication on the current socket             */
    uint8                           SockFramePrio_u8;  /* Frame priority to be used for all the transmission on the current socket */
} rba_EthUdp_DynSockTblType_tst;


#endif	/* ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHUDP_TYPES_H */
