

#ifndef RBA_ETHTCP_H
#define RBA_ETHTCP_H

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )


/*
 ***************************************************************************************************
 * Common Published Information
 ***************************************************************************************************
 */

/* rba_EthTcp vendor Id */
#define RBA_ETHTCP_VENDOR_ID  					6U

/* rba_EthTcp module Id */
#define RBA_ETHTCP_MODULE_ID					255U

/* rba_EthTcp instance Id */
#define RBA_ETHTCP_INSTANCE_ID					174U

/* Software version information */
#define RBA_ETHTCP_SW_MAJOR_VERSION  			4U
#define RBA_ETHTCP_SW_MINOR_VERSION  			0U
#define RBA_ETHTCP_SW_PATCH_VERSION  			0U


/*
 ***************************************************************************************************
 * Prototypes
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_Init				( P2CONST( rba_EthTcp_Config_to, AUTOMATIC, AUTOMATIC ) TcpConfig_cpo );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_MainFunction		( void );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_GetSocket        ( VAR( TcpIp_DomainType, AUTOMATIC )                Domain_u32,
                                                                              P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC ) SocketIdPtr_puo );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_FindTcpSockId    ( P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   LocalAddr_cpst,
                                                                              P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddr_cpst,
                                                                              P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )     SocketIdPtr_puo );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_ChangeParameter	( VAR( TcpIp_SocketIdType, AUTOMATIC )  			TcpSockId_uo,
																		      VAR( TcpIp_ParamIdType, AUTOMATIC )  				ParamId_u8,
																		      P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 			ParamValue_cpu8 );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_Connect			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 				TcpSockId_uo,
																		      P2CONST(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC) RemoteAddr_cpst );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_Listen			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 				TcpSockId_uo,
																			  VAR( uint16, AUTOMATIC ) 							MaxChannels_u16 );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_Bind             ( VAR( TcpIp_SocketIdType, AUTOMATIC )              TcpSockId_uo,
                                                                              VAR( TcpIp_LocalAddrIdType, AUTOMATIC )           LocalAddrId_u8,
                                                                              P2VAR( uint16, AUTOMATIC, AUTOMATIC )             PortPtr_pu16,
                                                                              VAR( uint8, AUTOMATIC )                           FramePrio_u8 );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_Transmit			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 				TcpSockId_uo,
																			  P2CONST( uint8, AUTOMATIC, AUTOMATIC )		    TxData_cpu8,
																			  VAR( uint32, AUTOMATIC ) 					        AvlLen_u32,
																			  VAR( boolean, AUTOMATIC ) 					    ForceRetrieve_b );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_Received			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 				TcpSockId_uo,
																			  VAR( uint16, AUTOMATIC ) 							DataLen_u16 );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_Close			( VAR( TcpIp_SocketIdType, AUTOMATIC )				TcpSockId_uo,
																			  VAR( boolean, AUTOMATIC )					        Abort_b );

extern FUNC ( void, RBA_ETHTCP_CODE )           rba_EthTcp_AbortByLocalAddrId ( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )         LocalAddrId_u8 );

#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


#endif	/* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */
#endif /* RBA_ETHTCP_H */




























