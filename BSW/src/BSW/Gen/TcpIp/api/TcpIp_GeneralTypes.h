

#ifndef TCPIP_GENERAL_TYPES_H
#define TCPIP_GENERAL_TYPES_H

#ifdef TCPIP_CONFIGURED

/* Macros to define Endianness */
#define TCPIP_LITTLE_ENDIAN                     LOW_BYTE_FIRST
#define TCPIP_BIG_ENDIAN                        HIGH_BYTE_FIRST
#define TCPIP_ENDIANESS                         CPU_BYTE_ORDER

#define TCPIP_IPADDR_BROADCAST                  0xFFFFFFFFUL

#define TCPIP_IPADDR_ZERO                       0x00000000UL

#define TCPIP_IPV4_NETMASK_INVALID              0x00000000UL

#define TCPIP_IPADDR_ASSIGNPRIO_INVALID         0xFFU

#define TCPIP_LOCALADDRID_INVALID               0xFFU

#define TCPIP_FRAME_IS_BROADCAST                TRUE

#define TCPIP_FRAME_IS_NOTBROADCAST             FALSE

#define TCPIP_IPV6_CIDR_MASK_128                (128u)

#define TCPIP_TYPE_LENGTH_UINT32                (32u)

/* In case port parameter is specified as TCPIP_PORT_ANY, the TCP/IP stack shall choose the local port automatically */
/* from the range 49152(0xC000) to 65535(0xFFFF) and shall update the parameter to the chosen value */
#define TCPIP_LOCAL_PORT_ANY_START              49152U
#define TCPIP_LOCAL_PORT_ANY_END                65535U

/* TcpIp address families */
#define TCPIP_AF_NONE                           0x00UL
#define TCPIP_AF_INET                           0x02UL
#define TCPIP_AF_INET6                          0x1CUL

/* defines the value used as IPv4 address wildcard. */
#define TCPIP_IPADDR_ANY                        0x00000000UL

/* defines the value used as IPv6 address wildcard. */
#define TCPIP_IP6ADDR_ANY						0x00000000UL

/* defines the value used as port wildcard */
#define TCPIP_PORT_ANY                          0U

/* Protocol type used by a socket. */
typedef enum
{
	TCPIP_IPPROTO_NONE							= 0x00U, 	/* None. Init value */
	TCPIP_IPPROTO_ICMP							= 0x01U, 	/* Use ICMP         */
	TCPIP_IPPROTO_TCP							= 0x06U, 	/* Use TCP          */
	TCPIP_IPPROTO_UDP							= 0x11U,  	/* Use UDP          */
	TCPIP_IPPROTO_ICMPV6                        = 0x3AU     /* Use ICMPV6 */
}TcpIp_ProtocolType;


/* Trigger of address assignment. */
typedef enum
{
	TCPIP_MANUAL								= 0x01U,    /* IP assignment begins after TcpIp_RequestComMode(TCPIP_STATE_ONLINE) and TcpIp_RequestIpAddrAssignment() call */
	TCPIP_AUTOMATIC								= 0x02U     /* IP assignment begins immediately after TcpIp_RequestComMode(TCPIP_STATE_ONLINE)                              */
}TcpIp_AssignmentTrigger_ten;


/* IP address type */
typedef enum
{
    TCPIP_NONE  								= 0x00U,  	/* For initialization */
    TCPIP_UNICAST  								= 0x01U,  	/* IP Unicast */
    TCPIP_MULTICAST 							= 0x02U,   	/* IP Multicast */
    TCPIP_BROADCAST 							= 0x03U  	/* IP Broadcast */
}TcpIp_AddressType;


/* Specifies the TcpIp state for a specific EthIf controller. */
typedef enum
{
	TCPIP_STATE_ONLINE 							= 0x01U,  /* IP assignment process is complete for atleast one of the localAddress mapped to TcpIpCtrl  */
	TCPIP_STATE_ONHOLD 							= 0x02U,  /* Trcv link is down                                                                          */
	TCPIP_STATE_OFFLINE 						= 0x03U,  /* No IP assigned to the localAddress mapped to the TcpIpCtrl                                 */
	TCPIP_STATE_STARTUP 						= 0x04U,  /* IP  assignment process is ongoing                                                          */
	TCPIP_STATE_SHUTDOWN 						= 0x05U   /* IP release process is ongoing because of TcpIp_RequestComMode(TCPIP_STATE_OFFLINE)         */
}TcpIp_StateType;


/* Specifies the state of local IP address assignment */
typedef enum
{
	TCPIP_IPADDR_STATE_INIT						= 0x00U,   /* Local IP address state is in Init state. Required for TcpIp_Init()            */
	TCPIP_IPADDR_STATE_ASSIGNED					= 0x01U,   /* Local IP address is assigned                                                  */
	TCPIP_IPADDR_STATE_ONHOLD					= 0x02U,   /* Local IP address is assigned, but cannot be used as the network is not active */
	TCPIP_IPADDR_STATE_UNASSIGNED				= 0x03U    /* Local IP address is unassigned                                                */
}TcpIp_IpAddrStateType;


/* Events reported by TcpIp */
typedef enum
{
	TCPIP_TCP_RESET 							= 0x01U,   /* TCP connection was reset, TCP socket and all related resources have been released                */
	TCPIP_TCP_CLOSED							= 0x02U,   /* TCP connection was closed successfully, TCP socket and all related resources have been released. */
	TCPIP_TCP_FIN_RECEIVED						= 0x03U,   /* A FIN signal was received on the TCP connection, TCP socket is still valid.                      */
	TCPIP_UDP_CLOSED							= 0x04U    /* UDP socket and all related resources have been released.                                         */
}TcpIp_EventType;


/* Specification of IP address assignment policy. */
typedef enum
{
	TCPIP_IPADDR_ASSIGNMENT_INVALID				= 0x00U, 	/* Invalid value for initialisation                             */
	TCPIP_IPADDR_ASSIGNMENT_STATIC 				= 0x01U, 	/* Static address assignment                                    */
    TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL_DOIP      = 0x02U,    /* Linklocal Address assignment using DoIp Parameters           */
    TCPIP_IPADDR_ASSIGNMENT_DHCP                = 0x03U,    /* Address assignment via DHCP                                  */
    TCPIP_IPADDR_ASSIGNMENT_LINKLOCAL           = 0x04U,    /* Linklocal Address assignment                                 */
    TCPIP_IPADDR_ASSIGNMENT_IPV6_ROUTER         = 0x05U     /* Dynamic configured IPv4/IPv6 address by Router Advertisement */

}TcpIp_IpAddrAssignmentType;


/* TcpIp specific return type. */
typedef enum
{
	TCPIP_OK,						/* Operation completed successfully.              */
	TCPIP_E_NOT_OK,					/* Operation failed.                              */
	TCPIP_E_ARP_CACHE_MISS			/* Operation failed because of an ARP cache miss. */
}TcpIp_ReturnType;


/* Type for the specification of all supported Parameter IDs. */
typedef enum
{
	TCPIP_PARAMID_TCP_RXWND_MAX					= 0x00U,		/* Specifies the maximum TCP receive window for the socket.                      */
	TCPIP_PARAMID_FRAMEPRIO						= 0x01U,		/* Specifies the frame priority for outgoing frames on the socket.               */
	TCPIP_PARAMID_TCP_NAGLE						= 0x02U,		/* Specifies if the Nagle Algorithm according to IETF RFC 896 is enabled or not. */
	TCPIP_PARAMID_TCP_KEEPALIVE					= 0x03U,		/* Specifies if TCP Keep Alive Probes are sent on the socket connection.         */
	TCPIP_PARAMID_TTL							= 0x04U,		/* Specifies the time to live value for outgoing frames on the socket.           */
	TCPIP_PARAMID_TCP_KEEPALIVE_TIME            = 0x05U,        /* Specifies the time in[s] between the last data packet sent(simple ACKs are not considered data) and the first Kepp Alive probe. */
    TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX      = 0x06U,        /* specifies the number of Keepalive Probes allowed on the socket connection     */
    TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL        = 0x07U,        /* Specifies the interval in [s] between subsequent Keepalive probes             */
	TCPIP_PARAMID_VENDOR_SPECIFIC				= 0x80U 		/* Start of vendor specific range of parameter IDs.                              */
} TcpIp_ParamIdType;

typedef enum
{
	TCPIP_SUBNET_EXT_IPV4ADDR 					= 1U,
	TCPIP_SUBNET_INT_IPV4ADDR 					= 2U
}TcpIp_IPv4AddrType_ten;


/* TcpIp address families */
typedef uint32                                  TcpIp_DomainType;

/* Socket identifier type for unique identification of a TcpIp stack socket. TCPIP_SOCKETID_INVALID shall specify an */
/* invalid socket handle */
typedef uint16									TcpIp_SocketIdType;


typedef uint8									TcpIp_LocalAddrIdType;


/* Network mask of IPv4 address */
typedef uint32									TcpIp_Netmask_tu32;


/* Priority of assignment (1 is highest). If a new address from an assignment method with a higher priority is available, */
/* it overwrites the IP address previously assigned by an assignment method with a lower priority. */
typedef uint8									TcpIp_AssignmentPrio_tu8;

/* IP address wildcard type. */
typedef uint32                                  TcpIpIpAddrWildcardType;

/* IP6 address wildcard. */
typedef uint32                                  TcpIpIp6AddrWildcardType;

/* LocalAddrId wildcard type. */
typedef TcpIp_LocalAddrIdType                   TcpIpLocalAddrIdWildcardType;

/* In case port parameter is specified as TCPIP_PORT_ANY, the TCP/IP stack shall choose the local port automatically */
/* from the range 49152(0xC000) to 65535(0xFFFF) and shall update the parameter to the chosen value */
typedef uint16                                  TcpIpPortWildcardType;

/* Generic structure used by APIs to specify an IP address. (A specific address type can be derived from
   this structure via a cast to the specific structure type.) */
typedef struct
{
	TcpIp_DomainType	domain;          /* This is the code for the address format of this address */
}TcpIp_SockAddrType;


/* This structure defines an IPv4 address type which can be derived from the generic address structure
   via cast. */
typedef struct
{
    TcpIp_DomainType	domain;         /* This is the code for the address format of this address */
	uint32				addr[1];        /* IPv4 address in network byte order                      */
    uint16              port;           /* UDP or TCP port number                                  */
}TcpIp_SockAddrInetType;


/* This structure defines a IPv6 address type which can be derived from the generic address structure
   via cast. */
typedef struct
{
    TcpIp_DomainType	domain;         /* This is the code for the address format of this address */
	uint32				addr[4];        /* IPv6 address in network byte order                      */
    uint16              port;           /* UDP or TCP port number                                  */
}TcpIp_SockAddrInet6Type;


#endif /* #ifdef TCPIP_CONFIGURED */

#endif /* TCPIP_GENERAL_TYPES_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
