


/* This file contains all the helper macros that deal with IP address domain. */

#ifndef RBA_ETHTCP_PRV_DOMAIN_H
#define RBA_ETHTCP_PRV_DOMAIN_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "TcpIp.h"


/*******************************************************************************
**                      Macro definitions                                 	  **
*******************************************************************************/

/* If both IPv4 and IPv6 support is enabled, then define the helper macros to support both domain type structures. */
#if ( ( TCPIP_IPV4_ENABLED == STD_ON ) && ( TCPIP_IPV6_ENABLED == STD_ON ) )

    /* Check if a socket address structure has invalid IP address (equal to 0 or 0xFF...FF). */
    #define RBA_ETHTCP_SOCKADDR_HAS_INVALID_IP( SockAddr_cpst ) \
        ( ( (SockAddr_cpst)->domain == TCPIP_AF_INET ) ? \
            ( ( ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] == TCPIP_IPADDR_ANY ) || ( ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] == 0xFFFFFFFFUL ) ) : \
            ( ( ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] == TCPIP_IPADDR_ANY ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] == TCPIP_IPADDR_ANY ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] == TCPIP_IPADDR_ANY ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] == TCPIP_IPADDR_ANY ) ) || \
              ( ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] == 0xFFFFFFFFUL ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] == 0xFFFFFFFFUL ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] == 0xFFFFFFFFUL ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] == 0xFFFFFFFFUL ) ) ) )

    /* Check if the remote IP address from the dynamic TCP socket table entry is equal to 0. */
    #define RBA_ETHTCP_IS_IPADDR_ANY( DomainType_u32, IPAddr_pun ) \
        ( ( (DomainType_u32) == TCPIP_AF_INET ) ? \
            ( (IPAddr_pun)->IPv4Addr_u32 == TCPIP_IPADDR_ANY ) : \
            ( ( (IPAddr_pun)->IPv6Addr_au32[0] == TCPIP_IPADDR_ANY ) && ( (IPAddr_pun)->IPv6Addr_au32[1] == TCPIP_IPADDR_ANY ) && ( (IPAddr_pun)->IPv6Addr_au32[2] == TCPIP_IPADDR_ANY ) && ( (IPAddr_pun)->IPv6Addr_au32[3] == TCPIP_IPADDR_ANY ) ) )

    /* Copy the remote IP address from a socket address structure to a dynamic TCP socket table entry. */
    #define RBA_ETHTCP_COPY_SOCKADDR_TO_IP( IPAddr_pun, SockAddr_cpst ) \
	{ \
		if( (SockAddr_cpst)->domain == TCPIP_AF_INET ) \
		{ \
			(IPAddr_pun)->IPv4Addr_u32 = ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0]; \
		} \
		else \
		{ \
			(IPAddr_pun)->IPv6Addr_au32[0] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0]; \
			(IPAddr_pun)->IPv6Addr_au32[1] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1]; \
			(IPAddr_pun)->IPv6Addr_au32[2] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2]; \
			(IPAddr_pun)->IPv6Addr_au32[3] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3]; \
		} \
	}

	/* Copy the remote port number from a socket address structure to a dynamic TCP socket table entry. */
	#define RBA_ETHTCP_COPY_SOCKADDR_TO_PORT( TcpDynSockTbl_pst, SockAddr_cpst ) \
	{ \
		if( (TcpDynSockTbl_pst)->DomainType_u32 == TCPIP_AF_INET ) \
		{ \
			(TcpDynSockTbl_pst)->RemotePort_u16 = ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->port; \
		} \
		else \
		{ \
			(TcpDynSockTbl_pst)->RemotePort_u16 = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->port; \
		} \
	}

    /* Copy the remote IP address from pseudo-header structure to the RX frame TCP specific structure. */
    #define RBA_ETHTCP_COPY_PSEUDOHDR_TO_IP( IPAddr_pun, PseudoHdr_cpst ) \
	{ \
		if( (PseudoHdr_cpst)->IpDomainType_t == TCPIP_AF_INET ) \
		{ \
			(IPAddr_pun)->IPv4Addr_u32 = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv4Addr_u32; \
		} \
		else \
		{ \
			(IPAddr_pun)->IPv6Addr_au32[0] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[0]; \
			(IPAddr_pun)->IPv6Addr_au32[1] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[1]; \
			(IPAddr_pun)->IPv6Addr_au32[2] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[2]; \
			(IPAddr_pun)->IPv6Addr_au32[3] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[3]; \
		} \
	}

    /* Check if local IP address from a TCP dynamic socket table entry is equal to the IP address from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_IP_EQUAL( IPAddrParamType_pun, SockAddr_cpst ) \
        ( ( (SockAddr_cpst)->domain == TCPIP_AF_INET ) ? \
            ( (IPAddrParamType_pun)->IPv4Par_st.IpAddr_u32 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] ) : \
            ( ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[0] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] ) && ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[1] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] ) && ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[2] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] ) && ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[3] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] ) ) )

    /* Check if remote IP address from a TCP dynamic socket table entry is equal to the IP address from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_IP_EQUAL( IPAddr_pun, SockAddr_cpst ) \
        ( ( (SockAddr_cpst)->domain == TCPIP_AF_INET ) ? \
            ( (IPAddr_pun)->IPv4Addr_u32 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] ) : \
            ( ( (IPAddr_pun)->IPv6Addr_au32[0] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] ) && ( (IPAddr_pun)->IPv6Addr_au32[1] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] ) && ( (IPAddr_pun)->IPv6Addr_au32[2] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] ) && ( (IPAddr_pun)->IPv6Addr_au32[3] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] ) ) )

    /* Check if local port number from a TCP dynamic socket table entry is equal to the port number from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_PORT_EQUAL( TcpDynSockTbl_pst, SockAddr_cpst ) \
        ( ( (TcpDynSockTbl_pst)->DomainType_u32 == TCPIP_AF_INET ) ? \
            ( (TcpDynSockTbl_pst)->LocalPort_u16 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->port ) : \
            ( (TcpDynSockTbl_pst)->LocalPort_u16 == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->port ) )

    /* Check if remote port number from a TCP dynamic socket table entry is equal to the port number from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_PORT_EQUAL( TcpDynSockTbl_pst, SockAddr_cpst ) \
        ( ( (TcpDynSockTbl_pst)->DomainType_u32 == TCPIP_AF_INET ) ? \
            ( (TcpDynSockTbl_pst)->RemotePort_u16 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->port ) : \
            ( (TcpDynSockTbl_pst)->RemotePort_u16 == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->port ) )

    /* Check if remote IP address from a TCP dynamic socket table entry is equal to the IP address from an RX frame structure. */
    #define RBA_ETHTCP_CHECK_IPADDR_EQUAL( DomainType_u32, IPAddrDest_pun, IPAddrSrc_pun ) \
        ( ( (DomainType_u32) == TCPIP_AF_INET ) ? \
            ( (IPAddrDest_pun)->IPv4Addr_u32 == (IPAddrSrc_pun)->IPv4Addr_u32 ) : \
            ( ( (IPAddrDest_pun)->IPv6Addr_au32[0] == (IPAddrSrc_pun)->IPv6Addr_au32[0] ) && ( (IPAddrDest_pun)->IPv6Addr_au32[1] == (IPAddrSrc_pun)->IPv6Addr_au32[1] ) && ( (IPAddrDest_pun)->IPv6Addr_au32[2] == (IPAddrSrc_pun)->IPv6Addr_au32[2] ) && ( (IPAddrDest_pun)->IPv6Addr_au32[3] == (IPAddrSrc_pun)->IPv6Addr_au32[3] ) ) )

    /* Copy the remote IP address from an RX frame structure to a TCP dynamic socket table entry. */
    #define RBA_ETHTCP_COPY_IPADDR( DomainType_u32, IPAddrDest_pun, IPAddrSrc_pun ) \
	{ \
		if( (DomainType_u32) == TCPIP_AF_INET ) \
		{ \
			(IPAddrDest_pun)->IPv4Addr_u32 = (IPAddrSrc_pun)->IPv4Addr_u32; \
		} \
		else \
		{ \
			(IPAddrDest_pun)->IPv6Addr_au32[0] = (IPAddrSrc_pun)->IPv6Addr_au32[0]; \
			(IPAddrDest_pun)->IPv6Addr_au32[1] = (IPAddrSrc_pun)->IPv6Addr_au32[1]; \
			(IPAddrDest_pun)->IPv6Addr_au32[2] = (IPAddrSrc_pun)->IPv6Addr_au32[2]; \
			(IPAddrDest_pun)->IPv6Addr_au32[3] = (IPAddrSrc_pun)->IPv6Addr_au32[3]; \
		} \
	}

    /* Reset the remote IP address for a TCP dynamic socket table entry. */
    #define RBA_ETHTCP_RESET_REMOTE_IP( IPAddr_pun ) \
        ( ( (IPAddr_pun)->IPv6Addr_au32[0] = TCPIP_IPADDR_ANY ), ( (IPAddr_pun)->IPv6Addr_au32[1] = TCPIP_IPADDR_ANY ), ( (IPAddr_pun)->IPv6Addr_au32[2] = TCPIP_IPADDR_ANY ), ( (IPAddr_pun)->IPv6Addr_au32[3] = TCPIP_IPADDR_ANY ) )

    /* Check if either the local or the remote IP address from a pseudo-header structure is equal to 0. */
    #define RBA_ETHTCP_CHECK_PSEUDOHDR_IPADDR_ANY( IpDomainType_t, IpAddr_pun ) \
        ( ( (IpDomainType_t) == TCPIP_AF_INET ) ? \
            ( (IpAddr_pun)->IPv4Addr_u32 == TCPIP_IPADDR_ANY ) : \
            ( ( (IpAddr_pun)->IPv6Addr_pcu32[0] == TCPIP_IPADDR_ANY ) && ( (IpAddr_pun)->IPv6Addr_pcu32[1] == TCPIP_IPADDR_ANY ) && ( (IpAddr_pun)->IPv6Addr_pcu32[2] == TCPIP_IPADDR_ANY ) && ( (IpAddr_pun)->IPv6Addr_pcu32[3] == TCPIP_IPADDR_ANY ) ) )

    /* Call the corresponding IP layer Provide Tx Buffer API based on the socket domain. */
    #define RBA_ETHTCP_CALL_IP_LAYER_PROVIDE_TX_BUFFER_API( TcpDynSockTbl_pst, IpProvidedBufIdx_pu8, IpProvidedBuf_ppu8, ReqAndGrantedLen_pu16 ) \
        ( ( (TcpDynSockTbl_pst)->DomainType_u32 == TCPIP_AF_INET ) ? \
            ( rba_EthIPv4_ProvideTxBuffer( (TcpDynSockTbl_pst)->LocalAddrId_u8, (TcpDynSockTbl_pst)->RemoteIPAddr_un.IPv4Addr_u32, (TcpDynSockTbl_pst)->SockFramePrio_u8, (IpProvidedBufIdx_pu8), (IpProvidedBuf_ppu8), (ReqAndGrantedLen_pu16) ) ) : \
            ( rba_EthIPv6_ProvideTxBuffer( (TcpDynSockTbl_pst)->LocalAddrId_u8, (TcpDynSockTbl_pst)->SockFramePrio_u8, (IpProvidedBufIdx_pu8), (IpProvidedBuf_ppu8), (ReqAndGrantedLen_pu16) ) ) )

    /* Call the corresponding IP layer Transmit API based on the socket domain. */
    #define RBA_ETHTCP_CALL_IP_LAYER_TRANSMIT_API( TcpDynSockTbl_pst, IpProvidedBuf_pu8, IpProvidedBufIdx_u8, IpHeader_pst, TcpSegLength_u16 ) \
        ( ( (TcpDynSockTbl_pst)->DomainType_u32 == TCPIP_AF_INET ) ? \
            ( rba_EthIPv4_Transmit( (TcpDynSockTbl_pst)->LocalAddrId_u8, (TcpDynSockTbl_pst)->RemoteIPAddr_un.IPv4Addr_u32, (IpProvidedBuf_pu8), (IpProvidedBufIdx_u8), (IpHeader_pst), (TcpSegLength_u16) ) ) : \
            ( rba_EthIPv6_Transmit( (TcpDynSockTbl_pst)->LocalAddrId_u8, ( (const uint32*) &((TcpDynSockTbl_pst)->RemoteIPAddr_un.IPv6Addr_au32)), (IpProvidedBuf_pu8), (IpProvidedBufIdx_u8), (IpHeader_pst), (TcpSegLength_u16) ) ) )

#elif ( TCPIP_IPV4_ENABLED == STD_ON )	/* Only IPv4 specific code is enabled; define the same macros but without the domain check and IPv6 specific branch. */

    /* Check if a socket address structure has invalid IP address (equal to 0 or 0xFF...FF). */
    #define RBA_ETHTCP_SOCKADDR_HAS_INVALID_IP( SockAddr_cpst ) \
		( ( ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] == TCPIP_IPADDR_ANY ) || ( ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] == 0xFFFFFFFFUL ) )

    /* Check if the remote IP address from the dynamic TCP socket table entry is equal to 0. */
    #define RBA_ETHTCP_IS_IPADDR_ANY( DomainType_u32, IPAddr_pun ) \
        ( (IPAddr_pun)->IPv4Addr_u32 == TCPIP_IPADDR_ANY )

    /* Copy the remote IP address from a socket address structure to a dynamic TCP socket table entry. */
	#define RBA_ETHTCP_COPY_SOCKADDR_TO_IP( IPAddr_pun, SockAddr_cpst ) \
	{ (IPAddr_pun)->IPv4Addr_u32 = ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0]; }

	/* Copy the remote port number from a socket address structure to a dynamic TCP socket table entry. */
	#define RBA_ETHTCP_COPY_SOCKADDR_TO_PORT( TcpDynSockTbl_pst, SockAddr_cpst ) \
	{ (TcpDynSockTbl_pst)->RemotePort_u16 = ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->port; }

    /* Copy the remote IP address from pseudo-header structure to the RX frame TCP specific structure. */
    #define RBA_ETHTCP_COPY_PSEUDOHDR_TO_IP( IPAddr_pun, PseudoHdr_cpst ) \
    { (IPAddr_pun)->IPv4Addr_u32 = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv4Addr_u32; }

    /* Check if local IP address from a TCP dynamic socket table entry is equal to the IP address from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_IP_EQUAL( IPAddrParamType_pun, SockAddr_cpst ) \
        ( (IPAddrParamType_pun)->IPv4Par_st.IpAddr_u32 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] )

    /* Check if remote IP address from a TCP dynamic socket table entry is equal to the IP address from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_IP_EQUAL( IPAddr_pun, SockAddr_cpst ) \
        ( (IPAddr_pun)->IPv4Addr_u32 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->addr[0] )

    /* Check if local port number from a TCP dynamic socket table entry is equal to the port number from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_PORT_EQUAL( TcpDynSockTbl_pst, SockAddr_cpst ) \
		( (TcpDynSockTbl_pst)->LocalPort_u16 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->port )

    /* Check if remote port number from a TCP dynamic socket table entry is equal to the port number from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_PORT_EQUAL( TcpDynSockTbl_pst, SockAddr_cpst ) \
		( (TcpDynSockTbl_pst)->RemotePort_u16 == ((const TcpIp_SockAddrInetType*) (SockAddr_cpst))->port )

    /* Check if remote IP address from a TCP dynamic socket table entry is equal to the IP address from an RX frame structure. */
    #define RBA_ETHTCP_CHECK_IPADDR_EQUAL( DomainType_u32, IPAddrDest_pun, IPAddrSrc_pun ) \
        ( (IPAddrDest_pun)->IPv4Addr_u32 == (IPAddrSrc_pun)->IPv4Addr_u32 )

    /* Copy the remote IP address from an RX frame structure to a TCP dynamic socket table entry. */
    #define RBA_ETHTCP_COPY_IPADDR( DomainType_u32, IPAddrDest_pun, IPAddrSrc_pun ) \
    { (IPAddrDest_pun)->IPv4Addr_u32 = (IPAddrSrc_pun)->IPv4Addr_u32; }

    /* Reset the remote IP address for a TCP dynamic socket table entry. */
    #define RBA_ETHTCP_RESET_REMOTE_IP( IPAddr_pun ) \
        ( ( (IPAddr_pun)->IPv4Addr_u32 = TCPIP_IPADDR_ANY ) )

    /* Check if either the local or the remote IP address from a pseudo-header structure is equal to 0. */
    #define RBA_ETHTCP_CHECK_PSEUDOHDR_IPADDR_ANY( IpDomainType_t, IpAddr_pun ) \
        ( (IpAddr_pun)->IPv4Addr_u32 == TCPIP_IPADDR_ANY )

    /* Call the corresponding IP layer Provide Tx Buffer API based on the socket domain. */
    #define RBA_ETHTCP_CALL_IP_LAYER_PROVIDE_TX_BUFFER_API( TcpDynSockTbl_pst, IpProvidedBufIdx_pu8, IpProvidedBuf_ppu8, ReqAndGrantedLen_pu16 ) \
		( rba_EthIPv4_ProvideTxBuffer( (TcpDynSockTbl_pst)->LocalAddrId_u8, (TcpDynSockTbl_pst)->RemoteIPAddr_un.IPv4Addr_u32, (TcpDynSockTbl_pst)->SockFramePrio_u8, (IpProvidedBufIdx_pu8), (IpProvidedBuf_ppu8), (ReqAndGrantedLen_pu16) ) )

    /* Call the corresponding IP layer Transmit API based on the socket domain. */
    #define RBA_ETHTCP_CALL_IP_LAYER_TRANSMIT_API( TcpDynSockTbl_pst, IpProvidedBuf_pu8, IpProvidedBufIdx_u8, IpHeader_pst, TcpSegLength_u16 ) \
		( rba_EthIPv4_Transmit( (TcpDynSockTbl_pst)->LocalAddrId_u8, (TcpDynSockTbl_pst)->RemoteIPAddr_un.IPv4Addr_u32, (IpProvidedBuf_pu8), (IpProvidedBufIdx_u8), (IpHeader_pst), (TcpSegLength_u16) ) )

#elif ( TCPIP_IPV6_ENABLED == STD_ON )      /* Only IPv6 specific code is enabled; define the same macros but without the domain check and IPv4 specific branch. */

    /* Check if a socket address structure has invalid IP address (equal to 0 or 0xFF...FF). */
    #define RBA_ETHTCP_SOCKADDR_HAS_INVALID_IP( SockAddr_cpst ) \
        ( ( ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] == TCPIP_IPADDR_ANY ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] == TCPIP_IPADDR_ANY ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] == TCPIP_IPADDR_ANY ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] == TCPIP_IPADDR_ANY ) ) || \
          ( ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] == 0xFFFFFFFFUL ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] == 0xFFFFFFFFUL ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] == 0xFFFFFFFFUL ) && ( ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] == 0xFFFFFFFFUL ) ) )

    /* Check if the remote IP address from the dynamic TCP socket table entry is equal to 0. */
    #define RBA_ETHTCP_IS_IPADDR_ANY( DomainType_u32, IPAddr_pun ) \
        ( ( (IPAddr_pun)->IPv6Addr_au32[0] == TCPIP_IPADDR_ANY ) && ( (IPAddr_pun)->IPv6Addr_au32[1] == TCPIP_IPADDR_ANY ) && ( (IPAddr_pun)->IPv6Addr_au32[2] == TCPIP_IPADDR_ANY ) && ( (IPAddr_pun)->IPv6Addr_au32[3] == TCPIP_IPADDR_ANY ) )

    /* Copy the remote IP address from a socket address structure to a dynamic TCP socket table entry. */
	#define RBA_ETHTCP_COPY_SOCKADDR_TO_IP( IPAddr_pun, SockAddr_cpst ) \
	{ \
		(IPAddr_pun)->IPv6Addr_au32[0] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0]; \
		(IPAddr_pun)->IPv6Addr_au32[1] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1]; \
		(IPAddr_pun)->IPv6Addr_au32[2] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2]; \
		(IPAddr_pun)->IPv6Addr_au32[3] = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3]; \
	}

	/* Copy the remote port number from a socket address structure to a dynamic TCP socket table entry. */
	#define RBA_ETHTCP_COPY_SOCKADDR_TO_PORT( TcpDynSockTbl_pst, SockAddr_cpst ) \
	{ (TcpDynSockTbl_pst)->RemotePort_u16 = ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->port; }

    /* Copy the remote IP address from pseudo-header structure to the RX frame TCP specific structure. */
    #define RBA_ETHTCP_COPY_PSEUDOHDR_TO_IP( IPAddr_pun, PseudoHdr_cpst ) \
	{ \
		(IPAddr_pun)->IPv6Addr_au32[0] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[0]; \
		(IPAddr_pun)->IPv6Addr_au32[1] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[1]; \
		(IPAddr_pun)->IPv6Addr_au32[2] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[2]; \
		(IPAddr_pun)->IPv6Addr_au32[3] = (PseudoHdr_cpst)->RemoteIpAddr_un.IPv6Addr_pcu32[3]; \
	}

    /* Check if local IP address from a TCP dynamic socket table entry is equal to the IP address from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_IP_EQUAL( IPAddrParamType_pun, SockAddr_cpst ) \
        ( ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[0] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] ) && ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[1] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] ) && ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[2] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] ) && ( (IPAddrParamType_pun)->IPv6Par_st.IpAddr_st.Addr_au32[3] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] ) )

    /* Check if remote IP address from a TCP dynamic socket table entry is equal to the IP address from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_IP_EQUAL( IPAddr_pun, SockAddr_cpst ) \
        ( ( (IPAddr_pun)->IPv6Addr_au32[0] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[0] ) && ( (IPAddr_pun)->IPv6Addr_au32[1] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[1] ) && ( (IPAddr_pun)->IPv6Addr_au32[2] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[2] ) && ( (IPAddr_pun)->IPv6Addr_au32[3] == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->addr[3] ) )

    /* Check if local port number from a TCP dynamic socket table entry is equal to the port number from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_LOCAL_PORT_EQUAL( TcpDynSockTbl_pst, SockAddr_cpst ) \
        ( (TcpDynSockTbl_pst)->LocalPort_u16 == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->port )

    /* Check if remote port number from a TCP dynamic socket table entry is equal to the port number from a socket address structure. */
    #define RBA_ETHTCP_CHECK_SOCKADDR_REMOTE_PORT_EQUAL( TcpDynSockTbl_pst, SockAddr_cpst ) \
        ( (TcpDynSockTbl_pst)->RemotePort_u16 == ((const TcpIp_SockAddrInet6Type*) (SockAddr_cpst))->port )

    /* Check if remote IP address from a TCP dynamic socket table entry is equal to the IP address from an RX frame structure. */
    #define RBA_ETHTCP_CHECK_IPADDR_EQUAL( DomainType_u32, IPAddrDest_pun, IPAddrSrc_pun ) \
        ( ( (IPAddrDest_pun)->IPv6Addr_au32[0] == (IPAddrSrc_pun)->IPv6Addr_au32[0] ) && ( (IPAddrDest_pun)->IPv6Addr_au32[1] == (IPAddrSrc_pun)->IPv6Addr_au32[1] ) && ( (IPAddrDest_pun)->IPv6Addr_au32[2] == (IPAddrSrc_pun)->IPv6Addr_au32[2] ) && ( (IPAddrDest_pun)->IPv6Addr_au32[3] == (IPAddrSrc_pun)->IPv6Addr_au32[3] ) )

    /* Copy the remote IP address from an RX frame structure to a TCP dynamic socket table entry. */
    #define RBA_ETHTCP_COPY_IPADDR( DomainType_u32, IPAddrDest_pun, IPAddrSrc_pun ) \
	{ \
		(IPAddrDest_pun)->IPv6Addr_au32[0] = (IPAddrSrc_pun)->IPv6Addr_au32[0]; \
		(IPAddrDest_pun)->IPv6Addr_au32[1] = (IPAddrSrc_pun)->IPv6Addr_au32[1]; \
		(IPAddrDest_pun)->IPv6Addr_au32[2] = (IPAddrSrc_pun)->IPv6Addr_au32[2]; \
		(IPAddrDest_pun)->IPv6Addr_au32[3] = (IPAddrSrc_pun)->IPv6Addr_au32[3]; \
	} \

    /* Reset the remote IP address for a TCP dynamic socket table entry. */
    #define RBA_ETHTCP_RESET_REMOTE_IP( IPAddr_pun ) \
        ( ( (IPAddr_pun)->IPv6Addr_au32[0] = TCPIP_IPADDR_ANY ), ( (IPAddr_pun)->IPv6Addr_au32[1] = TCPIP_IPADDR_ANY ), ( (IPAddr_pun)->IPv6Addr_au32[2] = TCPIP_IPADDR_ANY ), ( (IPAddr_pun)->IPv6Addr_au32[3] = TCPIP_IPADDR_ANY ) )

    /* Check if either the local or the remote IP address from a pseudo-header structure is equal to 0. */
    #define RBA_ETHTCP_CHECK_PSEUDOHDR_IPADDR_ANY( IpDomainType_t, IpAddr_pun ) \
        ( ( (IpAddr_pun)->IPv6Addr_pcu32[0] == TCPIP_IPADDR_ANY ) && ( (IpAddr_pun)->IPv6Addr_pcu32[1] == TCPIP_IPADDR_ANY ) && ( (IpAddr_pun)->IPv6Addr_pcu32[2] == TCPIP_IPADDR_ANY ) && ( (IpAddr_pun)->IPv6Addr_pcu32[3] == TCPIP_IPADDR_ANY ) )

    /* Call the corresponding IP layer Provide Tx Buffer API based on the socket domain. */
    #define RBA_ETHTCP_CALL_IP_LAYER_PROVIDE_TX_BUFFER_API( TcpDynSockTbl_pst, IpProvidedBufIdx_pu8, IpProvidedBuf_ppu8, ReqAndGrantedLen_pu16 ) \
        ( rba_EthIPv6_ProvideTxBuffer( (TcpDynSockTbl_pst)->LocalAddrId_u8, (TcpDynSockTbl_pst)->SockFramePrio_u8, (IpProvidedBufIdx_pu8), (IpProvidedBuf_ppu8), (ReqAndGrantedLen_pu16) ) )

    /* Call the corresponding IP layer Transmit API based on the socket domain. */
    #define RBA_ETHTCP_CALL_IP_LAYER_TRANSMIT_API( TcpDynSockTbl_pst, IpProvidedBuf_pu8, IpProvidedBufIdx_u8, IpHeader_pst, TcpSegLength_u16 ) \
        ( rba_EthIPv6_Transmit( (TcpDynSockTbl_pst)->LocalAddrId_u8, ( (const uint32*) &((TcpDynSockTbl_pst)->RemoteIPAddr_un.IPv6Addr_au32)), (IpProvidedBuf_pu8), (IpProvidedBufIdx_u8), (IpHeader_pst), (TcpSegLength_u16) ) )

#endif 	/* ( TCPIP_IPV4_ENABLED == STD_ON ) && ( TCPIP_IPV6_ENABLED == STD_ON ) */


#endif /* RBA_ETHTCP_PRV_DOMAIN_H */


