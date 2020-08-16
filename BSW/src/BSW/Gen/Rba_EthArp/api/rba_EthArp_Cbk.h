
#ifndef RBA_ETHARP_CBK_H_
#define RBA_ETHARP_CBK_H_

#if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) )

#define RBA_ETHARP_START_SEC_CODE
#include "rba_EthArp_MemMap.h"
extern FUNC( Std_ReturnType, 	RBA_ETHARP_CODE ) 	rba_EthArp_RxIndication			(
																VAR( uint8, AUTOMATIC )		lCtrlIdx_u8,
																P2CONST( uint8, AUTOMATIC, AUTOMATIC )  	lRxDataPtr,
																VAR( uint16, AUTOMATIC )  	lRxDataLen_u16  );
#define RBA_ETHARP_STOP_SEC_CODE
#include "rba_EthArp_MemMap.h"

#endif /* #if ( defined(TCPIP_ARP_ENABLED) && ( TCPIP_ARP_ENABLED == STD_ON ) ) */
#endif /* RBA_ETHARP_CBK_H_ */


