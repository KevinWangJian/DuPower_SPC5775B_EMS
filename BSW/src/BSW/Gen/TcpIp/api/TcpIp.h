

#ifndef TCPIP_H
#define TCPIP_H

#include "TcpIp_Cfg.h"				/* Required for TCPIP_DEV_ERROR_DETECT */

#ifdef TCPIP_CONFIGURED

#include "TcpIp_Types.h"
#include "TcpIp_PbCfg.h"

/* The below macros should be moved to compiler_Cfg.h */
#define RBA_ETH_COMMON_CODE

/* Vendor ID */
#define TCPIP_VENDOR_ID 			 			6u
/* Module ID */
#define TCPIP_MODULE_ID 						170u

#define TCPIP_INSTANCE_ID                       0u

/* AUTOSAR SPECIFICATION VERSION */
#define TCPIP_AR_RELEASE_MAJOR_VERSION 			4u
#define TCPIP_AR_RELEASE_MINOR_VERSION  		2u
#define TCPIP_AR_RELEASE_REVISION_VERSION 	 	2u

/* SOFTWARE VERSION INFORMATION */
#define TCPIP_SW_MAJOR_VERSION  				4u
#define TCPIP_SW_MINOR_VERSION  				0u
#define TCPIP_SW_PATCH_VERSION  				1u
/*End: Common Published information*/

#define TCPIP_TYPE_ARP							0x0806u
#define TCPIP_TYPE_IPV4							0x0800u
#define TCPIP_TYPE_IPV6							0x86DDu

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
extern void TcpIp_Init(	P2CONST( TcpIp_ConfigType, AUTOMATIC, AUTOMATIC )						ConfigPtr );

#if( TCPIP_VERSION_INFO_API == STD_ON )
extern FUNC( void, TCPIP_CODE ) TcpIp_GetVersionInfo( P2VAR( Std_VersionInfoType, AUTOMATIC, AUTOMATIC ) 	versioninfo );
#endif

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_GetSocket(
										VAR( TcpIp_DomainType, AUTOMATIC )						Domain,
										VAR( TcpIp_ProtocolType, AUTOMATIC )					Protocol,
										P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )		SocketIdPtr);

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_Bind(
										VAR( TcpIp_SocketIdType, AUTOMATIC ) 					SocketId,
										VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) 				LocalAddrId,
										P2VAR( uint16, AUTOMATIC, AUTOMATIC )					PortPtr );

extern FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_Close(	VAR( TcpIp_SocketIdType, AUTOMATIC )	SocketId,
														VAR( boolean, AUTOMATIC )				Abort );

#if ( TCPIP_UDP_ENABLED == STD_ON )
extern FUNC( TcpIp_ReturnType, TCPIP_CODE ) TcpIp_UdpTransmit (
										VAR( TcpIp_SocketIdType, AUTOMATIC )					SocketId,
										P2CONST( uint8, AUTOMATIC, AUTOMATIC )					DataPtr,
										P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )		RemoteAddrPtr,
										VAR( uint16, AUTOMATIC )					 			TotalLength );
#endif /* ( TCPIP_UDP_ENABLED == STD_ON ) */


#if ( TCPIP_TCP_ENABLED == STD_ON )
extern FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_TcpTransmit(
											VAR( TcpIp_SocketIdType, AUTOMATIC )  				SocketId,
											P2CONST( uint8, AUTOMATIC, AUTOMATIC )				DataPtr,
											VAR( uint32, AUTOMATIC )	 						AvailableLength,
											VAR( boolean, AUTOMATIC ) 							ForceRetrieve );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_TcpReceived(
											VAR( TcpIp_SocketIdType, AUTOMATIC ) 				SocketId,
											VAR( uint16, AUTOMATIC ) 							Length );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_TcpConnect(
										VAR( TcpIp_SocketIdType, AUTOMATIC ) 					SocketId,
										P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC ) 	RemoteAddrPtr );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_TcpListen(
											VAR( TcpIp_SocketIdType, AUTOMATIC ) 				SocketId,
											VAR( uint16, AUTOMATIC )	 						MaxChannels );
#endif /* ( TCPIP_TCP_ENABLED == STD_ON ) */

#if ( TCPIP_ICMP_ENABLED == STD_ON )

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_IcmpTransmit(
											VAR( TcpIp_LocalAddrIdType, AUTOMATIC )  			LocalIpAddrId,
											P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC ) RemoteAddrPtr,
											VAR( uint8, AUTOMATIC )  							Ttl,
											VAR( uint8, AUTOMATIC )  							Type,
											VAR( uint8, AUTOMATIC )  							Code,
											VAR( uint16, AUTOMATIC )  							DataLength,
											P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 				DataPtr );
#endif /* ( TCPIP_ICMP_ENABLED == STD_ON ) */


#if ( TCPIP_ARP_ENABLED == STD_ON )

extern FUNC( Std_ReturnType, TCPIP_CODE )TcpIp_ReadArpTable(
	 										VAR( TcpIp_LocalAddrIdType, 	AUTOMATIC )					LocalAddrId_u8 ,
	 										CONSTP2VAR( uint8, 				AUTOMATIC, AUTOMATIC )		ArpTable_cpu8,
	 										CONSTP2VAR( uint16, 			AUTOMATIC, AUTOMATIC )		NumberEntries_cpu16 );
#endif /* ( TCPIP_ARP_ENABLED == STD_ON ) */


extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_ChangeParameter(
												VAR( TcpIp_SocketIdType, AUTOMATIC )  			SocketId,
												VAR( TcpIp_ParamIdType, AUTOMATIC )  			ParameterId,
												P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 			ParameterValue );


extern FUNC( void, TCPIP_CODE )	TcpIp_MainFunction( void );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_RequestIpAddrAssignment(
									VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) 				    LocalAddrId,
									VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC ) 		        Type,
	 	 	 						P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )	        LocalIpAddrPtr,
	 	 	 						VAR( uint8,                             AUTOMATIC )         Netmask,
                                    P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )         DefaultRouterPtr );


extern FUNC( Std_ReturnType, TCPIP_CODE ) 	TcpIp_ReleaseIpAddrAssignment(
											CONST( TcpIp_LocalAddrIdType, AUTOMATIC ) 	        LocalAddrId );

extern void TcpIp_LocalIpAddrAssignmentChg(
						        VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) 					    LocalAddrId_u8,
						        VAR( TcpIp_IpAddrStateType, AUTOMATIC )						    State_en,
						        P2CONST( TcpIp_IPAddrParamType_tun, AUTOMATIC, AUTOMATIC )    	IPAddrParam_pcun,
						        VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )				    IPAddrAssignMethod_en,
								CONST(TcpIp_DomainType, AUTOMATIC )			                    IpDomainType_cu32);

extern FUNC( Std_ReturnType, TCPIP_CODE )  	TcpIp_GetIpAddr(
							    VAR( TcpIp_LocalAddrIdType, AUTOMATIC )	 					    LocalAddrId,
							    P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )			    IpAddrPtr,
							    P2VAR( uint8, AUTOMATIC, AUTOMATIC )						    NetmaskPtr,
							    P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )			    DefaultRouterPtr );

extern FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_GetPhysAddr(
									        VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) 			LocalAddrId,
									        P2VAR( uint8, AUTOMATIC, AUTOMATIC )				PhysAddrPtr );

#if (  TCPIP_DHCP_CLIENT_ENABLED == STD_ON  )

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_DhcpWriteOption(
											VAR( TcpIp_LocalAddrIdType, AUTOMATIC )             LocalIpAddrId,
		 	 	 	 	 	 	 	 	 	VAR( uint8, AUTOMATIC ) 				            Option,
		 	 	 	 	 	 	 	 	 	VAR( uint8, AUTOMATIC ) 				            DataLength,
		 	 	 	 	 	 	 	 	 	P2CONST( uint8, AUTOMATIC, AUTOMATIC  )             DataPtr );

extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_DhcpReadOption(
											VAR( TcpIp_LocalAddrIdType, AUTOMATIC )             LocalIpAddrId,
		 	 	 	 	 	 	 	 	 	VAR( uint8, AUTOMATIC ) 				            Option,
		 	 	 	 	 	 	 	 	 	P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 	            DataLength,
		 	 	 	 	 	 	 	 	 	P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 	            DataPtr );

#endif /* ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON ) */

extern FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_AllocBaseIpAddr(
											VAR( TcpIp_LocalAddrIdType, AUTOMATIC )				LocalAddrId_u8,
											VAR( TcpIp_IpAddrAssignmentType, AUTOMATIC )		IpAddrAsgnMethType_en,
											P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )	LocalIpAddr_pst );

extern FUNC( Std_ReturnType, TCPIP_CODE )  TcpIp_GetCtrlIdx(
                                            VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                   LocalAddrId,
                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )                      CtrlIdxPtr );


#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"

#endif /* #ifdef TCPIP_CONFIGURED */

#endif /* TCPIP_H */

/*<BASDKey>
*********************************************************************************************************
* $History___:$
*********************************************************************************************************
</BASDKey>*/
