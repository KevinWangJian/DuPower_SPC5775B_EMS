

#ifndef RBA_ETHUDP_CBK_H
#define RBA_ETHUDP_CBK_H

#if ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) )

#define RBA_ETHUDP_START_SEC_CODE
#include "rba_EthUdp_MemMap.h"
extern FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_RxIndication(
										P2CONST( TcpIp_PseudoHdr_tst, 	AUTOMATIC, AUTOMATIC )    	  	PseudoHdr_pcst,
										VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )			    LocalAddrId_CtrlIdx_un,
										P2VAR( uint8,		 				AUTOMATIC, AUTOMATIC )		RxData_pu8,
										VAR( uint16, 						AUTOMATIC )					RxDataLen_u16,
										VAR( boolean, 						AUTOMATIC )               	IsBroadcast_b );
#define RBA_ETHUDP_STOP_SEC_CODE
#include "rba_EthUdp_MemMap.h"

#endif	/* ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHUDP_CBK_H */

