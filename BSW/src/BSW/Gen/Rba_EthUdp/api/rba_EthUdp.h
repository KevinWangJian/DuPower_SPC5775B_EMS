

#ifndef RBA_ETHUDP_H
#define RBA_ETHUDP_H

#if ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) )

/* Length of UDP header */
#define RBA_ETHUDP_HDRLENGTH                    8U

/* Vendor Id */
#define RBA_ETHUDP_VENDOR_ID                    6U

/* rba_EthUdp module Id */
#define RBA_ETHUDP_MODULE_ID                    255U

/* rba_EthUdp instance Id */
#define RBA_ETHUDP_INSTANCE_ID                  173U

/* SOFTWARE VERSION INFORMATION */
#define RBA_ETHUDP_SW_MAJOR_VERSION                  4U
#define RBA_ETHUDP_SW_MINOR_VERSION                  0U
#define RBA_ETHUDP_SW_PATCH_VERSION                  0U
/*End: Common Published information*/


#define RBA_ETHUDP_START_SEC_CODE
#include "rba_EthUdp_MemMap.h"
extern FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_Init ( P2CONST( rba_EthUdp_Config_to, AUTOMATIC, AUTOMATIC ) CurrConfig_pcst );

extern FUNC( BufReq_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_ProvideTxBuffer( VAR( TcpIp_SocketIdType,   AUTOMATIC )         SocketId_u16,
                                                                              VAR( uint32,               AUTOMATIC )         DestIPv4Addr_u32,
                                                                              P2VAR( uint8,  AUTOMATIC,  AUTOMATIC )         BufIdx_pu8,
                                                                              P2VAR( uint8,  AUTOMATIC,  AUTOMATIC )         * Buffer_ppu8,
                                                                              P2CONST( uint16, AUTOMATIC,  AUTOMATIC )       GrantLength_pcu16 );

extern FUNC( TcpIp_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_Transmit( VAR( TcpIp_SocketIdType,                AUTOMATIC )     SocketId_u16,
                                                                      P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )     RemoteAddr_pst,
                                                                      P2VAR( uint8,                AUTOMATIC, AUTOMATIC )     Buffer_pu8,
                                                                      VAR( uint8,                             AUTOMATIC )     BufIdx_u8,
                                                                      VAR( uint16,                            AUTOMATIC )     BufLength_u16 );


extern FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_GetSocket(  VAR( TcpIp_DomainType,                AUTOMATIC )   Domain_u32,
                                                                      P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )   SocketIdPtr_pu16 );


extern FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_Bind( VAR( TcpIp_SocketIdType,               AUTOMATIC )          SocketId_u16,
                                                                VAR( TcpIp_LocalAddrIdType,            AUTOMATIC )          LocalAddrId_u8,
                                                                P2VAR( uint16,              AUTOMATIC, AUTOMATIC )          Port_pu16,
                                                                VAR( uint8,                            AUTOMATIC )          FramePrio_u8);

extern FUNC( void, RBA_ETHUDP_CODE )  rba_EthUdp_Close(    VAR( TcpIp_SocketIdType, AUTOMATIC )        SocketId_u16 );


extern FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_ChangeParameter( VAR( TcpIp_SocketIdType,             AUTOMATIC )   SocketId_u16,
                                                                           VAR( TcpIp_ParamIdType,              AUTOMATIC )   ParameterId_en,
                                                                           P2CONST( uint8,           AUTOMATIC, AUTOMATIC )   ParameterValue_pcu8 );


extern FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_TerminateSocUsingLocalAddr(VAR( TcpIp_LocalAddrIdType, AUTOMATIC )          LocalAddrId_u8);


#define RBA_ETHUDP_STOP_SEC_CODE
#include "rba_EthUdp_MemMap.h"

#endif /* ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHUDP_H */
