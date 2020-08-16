

#ifndef RBA_ETHICMP_CBK_H_
#define RBA_ETHICMP_CBK_H_

#if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) )

/*****************************************************************************************************
*                                   Prototypes
*****************************************************************************************************/
#define RBA_ETHICMP_START_SEC_CODE
#include "rba_EthIcmp_MemMap.h"

extern FUNC( void, RBA_ETHICMP_CODE ) rba_EthIcmp_RxIndication(
                                VAR( uint32, AUTOMATIC )                            RmtIPAddr_u32,
                                VAR( uint8, AUTOMATIC )                             LocalAddrId_u8,
                                P2VAR( uint8, AUTOMATIC, AUTOMATIC )                RxData_pu8,
                                VAR( uint16, AUTOMATIC )                            RxDataLen_u16,
                                VAR( boolean, AUTOMATIC)                            IsBroadcast_b );

#define RBA_ETHICMP_STOP_SEC_CODE
#include "rba_EthIcmp_MemMap.h"

#endif /* #if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHICMP_CBK_H_ */





