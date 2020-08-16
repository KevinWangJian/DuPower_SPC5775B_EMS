

/* This file contains all the helper macros that deal with IP address domain */

#ifndef SOAD_PRV_DOMAIN_H
#define SOAD_PRV_DOMAIN_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "SoAd.h"


/*******************************************************************************
**                      Macro definitions                                 	  **
*******************************************************************************/

/* If IPv6 support is enabled, then define the helper macros to support both domain type structures. */
#if ( ( SOAD_IPv4_SUPPORT_ENABLE == STD_ON ) && ( SOAD_IPv6_SUPPORT_ENABLE == STD_ON ) )

	/* Get the port from a TcpIp_SockAddrType structure. */
	#define SOAD_GET_PORT_FROM_SOCK_ADDR( SockAddr_pst ) \
		( ( (SockAddr_pst)->domain == TCPIP_AF_INET ) ? ( ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->port ) : ( ( (const TcpIp_SockAddrInet6Type *)(SockAddr_pst) )->port ) )

	/* Set the port in a TcpIp_SockAddrType structure. */
	#define SOAD_SET_PORT_TO_SOCK_ADDR( SockAddr_pst, Port_u16 ) \
	{ \
		if( (SockAddr_pst)->domain == TCPIP_AF_INET ) \
		{ \
			( (TcpIp_SockAddrInetType *) (SockAddr_pst) )->port = (Port_u16); \
		} \
		else \
		{ \
			( (TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->port = (Port_u16); \
		} \
	}

	/* Get the remote port from a static socket. */
	#define SOAD_GET_REMOTE_PORT_FROM_STATIC_SOC_CONFIG( StaticSocConfig_cpst ) \
		( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[(StaticSocConfig_cpst)->soConGrpId_uo].domain_en == TCPIP_AF_INET ) ? \
			( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16 ) : \
			( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16 ) )

	/* Get the remote port from a dynamic socket. */
	#define SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG( DyncSocConfig_pst ) \
		( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[(DyncSocConfig_pst)->idxStaticSoc_uo].soConGrpId_uo].domain_en == TCPIP_AF_INET ) ? \
			( SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16 ) : \
			( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16 ) )

	/* Check if a TcpIp_SockAddrType structure has a wildcard (ANY) IP address. */
	#define SOAD_SOCK_ADDR_HAS_WILDCARD_IPADDR( SockAddr_pst ) \
		( ( (SockAddr_pst)->domain == TCPIP_AF_INET ) ? \
			( ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0] == TCPIP_IPADDR_ANY ) : \
			( ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0] == TCPIP_IP6ADDR_ANY ) && ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1] == TCPIP_IP6ADDR_ANY ) && ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2] == TCPIP_IP6ADDR_ANY ) && ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3] == TCPIP_IP6ADDR_ANY ) ) )

	/* Check if a static socket has a wildcard (ANY) remote IP address. */
	#define SOAD_STATIC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( StaticSocConfig_cpst ) \
		( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[(StaticSocConfig_cpst)->soConGrpId_uo].domain_en == TCPIP_AF_INET ) ? \
			( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32 == TCPIP_IPADDR_ANY ) : \
			( ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[0] ) == TCPIP_IP6ADDR_ANY ) && ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[1] ) == TCPIP_IP6ADDR_ANY ) && ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[2] ) == TCPIP_IP6ADDR_ANY ) && ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[3] ) == TCPIP_IP6ADDR_ANY ) ) )

	/* Check if a dynamic socket has a wildcard (ANY) remote IP address. */
	#define SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( DyncSocConfig_pst ) \
		( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[(DyncSocConfig_pst)->idxStaticSoc_uo].soConGrpId_uo].domain_en == TCPIP_AF_INET ) ? \
			( SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32 == TCPIP_IPADDR_ANY ) : \
			( ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0] == TCPIP_IP6ADDR_ANY ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1] == TCPIP_IP6ADDR_ANY ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2] == TCPIP_IP6ADDR_ANY ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3] == TCPIP_IP6ADDR_ANY ) ) )

	/* Set the remote IP address for a dynamic socket to default values. */
	#define	SOAD_SET_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_DEFAULT( DyncSocConfig_pcst ) \
	{ \
		if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[(DyncSocConfig_pcst)->idxStaticSoc_uo].soConGrpId_uo].domain_en == TCPIP_AF_INET ) \
		{ \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = SOAD_DEFAULT_IP; \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = SOAD_DEFAULT_PORT; \
		} \
		else \
		{ \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = SOAD_DEFAULT_IP; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = SOAD_DEFAULT_IP; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = SOAD_DEFAULT_IP; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = SOAD_DEFAULT_IP; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 	 = SOAD_DEFAULT_PORT; \
		} \
	}

	/* Copy the IP address and port from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_ADDR( SockAddr_pst, DyncSocConfig_pcst ) \
	{ \
		if( (SockAddr_pst)->domain == TCPIP_AF_INET ) \
		{ \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0]; \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->port; \
		} \
		else \
		{ \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16    = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->port; \
		} \
	}

	/* Copy only the IP address from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR( SockAddr_pst, DyncSocConfig_pcst ) \
	{ \
		if( (SockAddr_pst)->domain == TCPIP_AF_INET ) \
		{ \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0]; \
		} \
		else \
		{ \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3]; \
		} \
	}

	/* Copy only the port number from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_PORT( SockAddr_pst, DyncSocConfig_pcst ) \
	{ \
		if( (SockAddr_pst)->domain == TCPIP_AF_INET ) \
		{ \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->port; \
		} \
		else \
		{ \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->port; \
		} \
	}

	/* Copy the remote IP address and port of a dynamic socket to a TcpIp_SockAddrType structure */
	#define SOAD_COPY_FROM_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_SOCK_ADDR( DyncSocConfig_pst, SockAddr_pst ) \
	{ \
		if( (SockAddr_pst)->domain == TCPIP_AF_INET ) \
		{ \
			( (TcpIp_SockAddrInetType*) (SockAddr_pst) )->addr[0] = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32; \
			( (TcpIp_SockAddrInetType*) (SockAddr_pst) )->port 	  = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16; \
		} \
		else \
		{ \
			( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[0] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0]; \
			( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[1] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1]; \
			( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[2] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2]; \
			( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[3] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3]; \
			( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->port 	  = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16; \
		} \
	}

	/* Copy the remote IP address and port from a static socket to a dynamic socket. */
	#define SOAD_COPY_REMOTE_ADDR_FROM_STATIC_SOC_CONFIG_TO_DYNC_SOC_CONFIG( StaticSocConfig_cpst, DyncSocConfig_pcst ) \
	{ \
		if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[(StaticSocConfig_cpst)->soConGrpId_uo].domain_en == TCPIP_AF_INET ) \
		{ \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32; \
			SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16; \
		} \
		else \
		{ \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[0]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[1]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[2]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[3]; \
			SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16	 = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16; \
		} \
	}

	/* Check if the IP address from a TcpIp_SockAddrType structure is equal to the remote IP address for a dynamic socket. */
	#define SOAD_SOCK_IPADDR_IS_EQUAL_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR( SockAddr_pst, DyncSocConfig_pst ) \
		( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[(DyncSocConfig_pst)->idxStaticSoc_uo].soConGrpId_uo].domain_en != (SockAddr_pst)->domain ) ? ( FALSE ) : \
			( ( (SockAddr_pst)->domain == TCPIP_AF_INET ) ? \
				( SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32 == ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0] ) : \
				( ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0] ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1] ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2] ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3] ) ) ) )

	/* This macro gets the range of indexes in the dynamic socket table which have the same domain as a given static socket
	 * (all dynamic sockets represented by the index range [*(StartIdx_puo), *(EndIdx_puo)) have the same domain as the static socket). */
	#define SOAD_GET_DYNC_SOC_CONFIG_TABLE_RANGE_WITH_SAME_DOMAIN( StaticSocConfig_cpst, StartIdx_puo, EndIdx_puo ) \
	{ \
		if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[(StaticSocConfig_cpst)->soConGrpId_uo].domain_en == TCPIP_AF_INET ) \
		{ \
			*(StartIdx_puo) = 0; \
			*(EndIdx_puo)   = SoAd_CurrConfig_cpst->SoAd_noInetActiveSockets_uo; \
		} \
		else \
		{ \
			*(StartIdx_puo) = SoAd_CurrConfig_cpst->SoAd_noInetActiveSockets_uo; \
			*(EndIdx_puo)   = SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo; \
		} \
	}

	/* Check if a given TcpIp_SockAddrType structure is large enough to store an address for a given connection. */
	#define SOAD_SOCK_ADDR_CAN_STORE_CON_ADDR( SockAddr_pst, SoConId_uo ) \
		( ( (SockAddr_pst)->domain == TCPIP_AF_INET6 ) || ( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[(SoConId_uo)].soConGrpId_uo].domain_en ) == TCPIP_AF_INET ) )

	/* This macro returns a pointer to a TcpIp_SockAddrType structure which has the IP address and port equal to the remote IP address and port of a given dynamic socket. */
	#define	SOAD_BUILD_SOCK_ADDR( DyncSocConfig_pst, Domain_en, SockAddrInet_pst, SockAddrInet6_pst, SockAddr_pst ) \
	{ \
		if ( (Domain_en) == TCPIP_AF_INET ) \
		{ \
			(SockAddrInet_pst)->domain  = (Domain_en); \
			(SockAddrInet_pst)->addr[0] = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32; \
			(SockAddrInet_pst)->port    = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16; \
			(SockAddr_pst) 				= ( (TcpIp_SockAddrType *) (SockAddrInet_pst) ); \
			\
		} \
		else \
		{ \
			(SockAddrInet6_pst)->domain  = (Domain_en); \
			(SockAddrInet6_pst)->addr[0] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0]; \
			(SockAddrInet6_pst)->addr[1] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1]; \
			(SockAddrInet6_pst)->addr[2] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2]; \
			(SockAddrInet6_pst)->addr[3] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3]; \
			(SockAddrInet6_pst)->port    = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16; \
			(SockAddr_pst) 				 = ( (TcpIp_SockAddrType *) (SockAddrInet6_pst) ) ; \
		} \
	}

#elif ( SOAD_IPv4_SUPPORT_ENABLE == STD_ON )	/* Only IPv4 specific code is enabled; define the same macros but without the domain check and IPv6 specific branch. */

	/* Get the port from a TcpIp_SockAddrType structure. */
	#define SOAD_GET_PORT_FROM_SOCK_ADDR( SockAddr_pst ) \
		( ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->port )

	/* Set the port in a TcpIp_SockAddrType structure. */
	#define SOAD_SET_PORT_TO_SOCK_ADDR( SockAddr_pst, Port_u16 ) \
	{ ( (TcpIp_SockAddrInetType *) (SockAddr_pst) )->port = (Port_u16); }

	/* Get the remote port from a static socket. */
	#define SOAD_GET_REMOTE_PORT_FROM_STATIC_SOC_CONFIG( StaticSocConfig_cpst ) \
		( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16 )

	/* Get the remote port from a dynamic socket. */
	#define SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG( DyncSocConfig_pst ) \
		( SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16 )

	/* Check if a TcpIp_SockAddrType structure has a wildcard (ANY) IP address. */
	#define SOAD_SOCK_ADDR_HAS_WILDCARD_IPADDR( SockAddr_pst ) \
		( ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0] == TCPIP_IPADDR_ANY )

	/* Check if a static socket has a wildcard (ANY) remote IP address. */
	#define SOAD_STATIC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( StaticSocConfig_cpst ) \
		( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32 == TCPIP_IPADDR_ANY )

	/* Check if a dynamic socket has a wildcard (ANY) remote IP address. */
	#define SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( DyncSocConfig_pst ) \
		( SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32 == TCPIP_IPADDR_ANY )

	/* Set the remote IP address for a dynamic socket to default values. */
	#define	SOAD_SET_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_DEFAULT( DyncSocConfig_pcst ) \
	{ \
		SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = SOAD_DEFAULT_IP; \
		SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = SOAD_DEFAULT_PORT; \
	}

	/* Copy the IP address and port from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_ADDR( SockAddr_pst, DyncSocConfig_pcst ) \
	{ \
		SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0]; \
		SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->port; \
	}

	/* Copy only the IP address from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR( SockAddr_pst, DyncSocConfig_pcst ) \
	{ SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0]; }

	/* Copy only the port number from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_PORT( SockAddr_pst, DyncSocConfig_pcst ) \
	{ SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->port; }

	/* Copy the remote IP address and port of a dynamic socket to a TcpIp_SockAddrType structure */
	#define SOAD_COPY_FROM_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_SOCK_ADDR( DyncSocConfig_pst, SockAddr_pst ) \
	{ \
		( (TcpIp_SockAddrInetType*) (SockAddr_pst) )->addr[0] = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32; \
		( (TcpIp_SockAddrInetType*) (SockAddr_pst) )->port 	  = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16; \
	}

	/* Copy the remote IP address and port from a static socket to a dynamic socket. */
	#define SOAD_COPY_REMOTE_ADDR_FROM_STATIC_SOC_CONFIG_TO_DYNC_SOC_CONFIG( StaticSocConfig_cpst, DyncSocConfig_pcst ) \
	{ \
		SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32 = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32; \
		SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16; \
	}

	/* Check if the IP address from a TcpIp_SockAddrType structure is equal to the remote IP address for a dynamic socket. */
	#define SOAD_SOCK_IPADDR_IS_EQUAL_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR( SockAddr_pst, DyncSocConfig_pst ) \
		( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[(DyncSocConfig_pst)->idxStaticSoc_uo].soConGrpId_uo].domain_en != (SockAddr_pst)->domain ) ? \
			( FALSE ) : \
			( SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32 == ( (const TcpIp_SockAddrInetType *) (SockAddr_pst) )->addr[0] ) )

	/* This macro gets the range of indexes in the dynamic socket table which have the same domain as a given static socket
	 * (all dynamic sockets represented by the index range [*(StartIdx_puo), *(EndIdx_puo)) have the same domain as the static socket). */
	#define SOAD_GET_DYNC_SOC_CONFIG_TABLE_RANGE_WITH_SAME_DOMAIN( StaticSocConfig_cpst, StartIdx_puo, EndIdx_puo ) \
	{ \
		*(StartIdx_puo) = 0; \
		*(EndIdx_puo)   = SoAd_CurrConfig_cpst->SoAd_noInetActiveSockets_uo; \
	}

	/* Check if a given TcpIp_SockAddrType structure is large enough to store an address for a given connection. */
	#define SOAD_SOCK_ADDR_CAN_STORE_CON_ADDR( SockAddr_pst, SoConId_uo ) \
		( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[(SoConId_uo)].soConGrpId_uo].domain_en ) == TCPIP_AF_INET )

	/* This macro returns a pointer to a TcpIp_SockAddrType structure which has the IP address and port equal to the remote IP address and port of a given dynamic socket. */
	#define	SOAD_BUILD_SOCK_ADDR( DyncSocConfig_pst, Domain_en, SockAddrInet_pst, SockAddrInet6_pst, SockAddr_pst ) \
	{ \
		(void)(SockAddrInet6_pst); \
		(SockAddrInet_pst)->domain  = (Domain_en); \
		(SockAddrInet_pst)->addr[0] = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32; \
		(SockAddrInet_pst)->port    = SoAd_DynSoConRemoteAddrInet_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16; \
		(SockAddr_pst) 				= ( (TcpIp_SockAddrType *) (SockAddrInet_pst) ); \
	}

#elif ( SOAD_IPv6_SUPPORT_ENABLE == STD_ON )	/* Only IPv6 specific code is enabled; define the same macros but without the domain check and IPv4 specific branch. */

	/* Get the port from a TcpIp_SockAddrType structure. */
	#define SOAD_GET_PORT_FROM_SOCK_ADDR( SockAddr_pst ) \
		( ( (const TcpIp_SockAddrInet6Type *)(SockAddr_pst) )->port )

	/* Set the port in a TcpIp_SockAddrType structure. */
	#define SOAD_SET_PORT_TO_SOCK_ADDR( SockAddr_pst, Port_u16 ) \
	{ ( (TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->port = (Port_u16); }

	/* Get the remote port from a static socket. */
	#define SOAD_GET_REMOTE_PORT_FROM_STATIC_SOC_CONFIG( StaticSocConfig_cpst ) \
		( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16 )

	/* Get the remote port from a dynamic socket. */
	#define SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG( DyncSocConfig_pst ) \
		( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16 )

	/* Check if a TcpIp_SockAddrType structure has a wildcard (ANY) IP address. */
	#define SOAD_SOCK_ADDR_HAS_WILDCARD_IPADDR( SockAddr_pst ) \
		( ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0] == TCPIP_IP6ADDR_ANY ) && ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1] == TCPIP_IP6ADDR_ANY ) && ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2] == TCPIP_IP6ADDR_ANY ) && ( ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3] == TCPIP_IP6ADDR_ANY ) )

	/* Check if a static socket has a wildcard (ANY) remote IP address. */
	#define SOAD_STATIC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( StaticSocConfig_cpst ) \
		( ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[0] ) == TCPIP_IP6ADDR_ANY ) && ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[1] ) == TCPIP_IP6ADDR_ANY ) && ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[2] ) == TCPIP_IP6ADDR_ANY ) && ( ( SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[3] ) == TCPIP_IP6ADDR_ANY ) )

	/* Check if a dynamic socket has a wildcard (ANY) remote IP address. */
	#define SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( DyncSocConfig_pst ) \
		( ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0] == TCPIP_IP6ADDR_ANY ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1] == TCPIP_IP6ADDR_ANY ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2] == TCPIP_IP6ADDR_ANY ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3] == TCPIP_IP6ADDR_ANY ) )

	/* Set the remote IP address for a dynamic socket to default values. */
	#define	SOAD_SET_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_DEFAULT( DyncSocConfig_pcst ) \
	{ \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = SOAD_DEFAULT_IP; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = SOAD_DEFAULT_IP; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = SOAD_DEFAULT_IP; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = SOAD_DEFAULT_IP; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 	 = SOAD_DEFAULT_PORT; \
	}

	/* Copy the IP address and port from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_ADDR( SockAddr_pst, DyncSocConfig_pcst ) \
	{ \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16    = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->port; \
	}

	/* Copy only the IP address from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR( SockAddr_pst, DyncSocConfig_pcst ) \
	{ \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3]; \
	}

	/* Copy only the port number from a TcpIp_SockAddrType structure to the remote address for a dynamic socket. */
	#define SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_PORT( SockAddr_pst, DyncSocConfig_pcst ) \
	{ SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16 = ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->port; }

	/* Copy the remote IP address and port of a dynamic socket to a TcpIp_SockAddrType structure */
	#define SOAD_COPY_FROM_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_SOCK_ADDR( DyncSocConfig_pst, SockAddr_pst ) \
	{ \
		( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[0] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0]; \
		( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[1] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1]; \
		( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[2] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2]; \
		( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->addr[3] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3]; \
		( (TcpIp_SockAddrInet6Type*)(SockAddr_pst) )->port 	  = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16; \
	}

	/* Copy the remote IP address and port from a static socket to a dynamic socket. */
	#define SOAD_COPY_REMOTE_ADDR_FROM_STATIC_SOC_CONFIG_TO_DYNC_SOC_CONFIG( StaticSocConfig_cpst, DyncSocConfig_pcst ) \
	{ \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[0] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[0]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[1] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[1]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[2] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[2]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].addr_u32[3] = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].addr_u32[3]; \
		SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pcst)->idxDynSoConRemoteAddr_uo].port_u16	 = SoAd_CurrConfig_cpst->statSoConRemoteAddrInet6_cpst[(StaticSocConfig_cpst)->idxStatSoConRemoteAddr_uo].port_u16; \
	}

	/* Check if the IP address from a TcpIp_SockAddrType structure is equal to the remote IP address for a dynamic socket. */
	#define SOAD_SOCK_IPADDR_IS_EQUAL_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR( SockAddr_pst, DyncSocConfig_pst ) \
		( ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[0] ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[1] ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[2] ) && ( SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3] == ( (const TcpIp_SockAddrInet6Type *) (SockAddr_pst) )->addr[3] ) )

	/* This macro gets the range of indexes in the dynamic socket table which have the same domain as a given static socket
	 * (all dynamic sockets represented by the index range [*(StartIdx_puo), *(EndIdx_puo)) have the same domain as the static socket). */
	#define SOAD_GET_DYNC_SOC_CONFIG_TABLE_RANGE_WITH_SAME_DOMAIN( StaticSocConfig_cpst, StartIdx_puo, EndIdx_puo ) \
	{ \
		*(StartIdx_puo) = SoAd_CurrConfig_cpst->SoAd_noInetActiveSockets_uo; \
		*(EndIdx_puo)   = SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo; \
	}

	/* Check if a given TcpIp_SockAddrType structure is large enough to store an address for a given connection. */
	#define SOAD_SOCK_ADDR_CAN_STORE_CON_ADDR( SockAddr_pst, SoConId_uo ) \
		( (SockAddr_pst)->domain == TCPIP_AF_INET6 )

	/* This macro returns a pointer to a TcpIp_SockAddrType structure which has the IP address and port equal to the remote IP address and port of a given dynamic socket. */
	#define	SOAD_BUILD_SOCK_ADDR( DyncSocConfig_pst, Domain_en, SockAddrInet_pst, SockAddrInet6_pst, SockAddr_pst ) \
	{ \
		(void)(SockAddrInet_pst); \
		(SockAddrInet6_pst)->domain  = (Domain_en); \
		(SockAddrInet6_pst)->addr[0] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[0]; \
		(SockAddrInet6_pst)->addr[1] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[1]; \
		(SockAddrInet6_pst)->addr[2] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[2]; \
		(SockAddrInet6_pst)->addr[3] = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].addr_u32[3]; \
		(SockAddrInet6_pst)->port    = SoAd_DynSoConRemoteAddrInet6_pst[(DyncSocConfig_pst)->idxDynSoConRemoteAddr_uo].port_u16 ); \
		(SockAddr_pst) 				 = ( (TcpIp_SockAddrType *) (SockAddrInet6_pst) ); \
	}

#endif 	/* ( ( SOAD_IPv4_SUPPORT_ENABLE == STD_ON ) && ( SOAD_IPv6_SUPPORT_ENABLE == STD_ON ) ) */


#endif /* SOAD_PRV_DOMAIN_H */
