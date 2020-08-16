

#ifndef RBA_ETHIPV4_CBK_H
#define RBA_ETHIPV4_CBK_H

#if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) )

#define RBA_ETHIPV4_START_SEC_CODE
#include "rba_EthIPv4_MemMap.h"
extern FUNC( void, RBA_ETHIPV4_CODE ) rba_EthIPv4_RxIndication(
                                        VAR( uint8, AUTOMATIC )					EthIfCtrlIdx_u8,
                                        VAR( boolean, AUTOMATIC )               IsBroadcast_b,
										P2VAR( uint8, AUTOMATIC, AUTOMATIC )	RmtPhysAddr_pu8,
										P2VAR( uint8, AUTOMATIC, AUTOMATIC )	RxData_pu8,
										VAR( uint16, AUTOMATIC )	 			RxDataLen_u16  );
#define RBA_ETHIPV4_STOP_SEC_CODE
#include "rba_EthIPv4_MemMap.h"

#endif /* #if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHIPV4_CBK_H */

