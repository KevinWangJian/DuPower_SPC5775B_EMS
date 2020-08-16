

#ifndef SOAD_CBK_H
#define SOAD_CBK_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "ComStack_Types.h"
#include "SoAd.h"

/**************************************************************************************************/
/*  Common Published Information                                                                  */
/**************************************************************************************************/

/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************/

/****************************************************************************************************************
**                                   Global Callback Function Prototypes                                       **
****************************************************************************************************************/
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

extern FUNC( void, SOAD_CODE )                  SoAd_RxIndication                   ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  SocketId, \
													                                  P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddrPtr, \
													                                  P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  BufPtr, \
													                                  VAR( uint16, AUTOMATIC )                              Length );

extern FUNC( BufReq_ReturnType, SOAD_CODE )     SoAd_CopyTxData                     ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  SocketId, \
															                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  BufPtr, \
                                                                                      VAR( uint16, AUTOMATIC )                              BufLength);

extern FUNC( void, SOAD_CODE )                  SoAd_TxConfirmation                 ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  SocketId, \
													                                  VAR( uint16, AUTOMATIC )                              Length );

extern FUNC( Std_ReturnType, SOAD_CODE )        SoAd_TcpAccepted                    ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  SocketId, \
												                                      VAR( TcpIp_SocketIdType, AUTOMATIC )                  SocketIdConnected, \
												                                      P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddrPtr );

extern FUNC( void, SOAD_CODE )                  SoAd_TcpConnected                   ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  SocketId);

extern FUNC( void, SOAD_CODE )                  SoAd_TcpIpEvent                     ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  SocketId, \
												                                      VAR( TcpIp_EventType, AUTOMATIC )  	                Event );

extern FUNC( void, SOAD_CODE )                  SoAd_LocalIpAddrAssignmentChg       ( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )               IpAddrId, \
																                      VAR( TcpIp_IpAddrStateType, AUTOMATIC )               State );

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif
