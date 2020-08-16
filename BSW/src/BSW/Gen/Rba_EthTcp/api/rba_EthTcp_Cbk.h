

#ifndef RBA_ETHTCP_CBK_H
#define RBA_ETHTCP_CBK_H

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )


/*
 ***************************************************************************************************
 * Prototypes
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

extern FUNC( void, RBA_ETHTCP_CODE ) 	rba_EthTcp_RxIndication	( P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC ) 	PseudoHdr_cpst,
																  VAR( TcpIp_LocalAddrIdType, AUTOMATIC)				LocalAddrId_u8,
																  P2VAR( uint8, AUTOMATIC, AUTOMATIC )					RxData_pu8,
																  VAR( uint16, AUTOMATIC ) 								LenByte_u16 );

#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


#endif	/* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */
#endif /* RBA_ETHTCP_CBK_H */


