

#ifndef RBA_ETHICMP_H
#define RBA_ETHICMP_H

#if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) )

/*
****************************************************************************************************
*                                   Includes
****************************************************************************************************
*/

/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

/* Vendor Id */
#define RBA_ETHICMP_VENDOR_ID                   6U

/* rba_EthIcmp module Id */
#define RBA_ETHICMP_MODULE_ID                   255U

/* rba_EthIcmp instance Id */
#define RBA_ETHICMP_INSTANCE_ID                 172U

/* SOFTWARE VERSION INFORMATION */
#define RBA_ETHICMP_SW_MAJOR_VERSION                4U
#define RBA_ETHICMP_SW_MINOR_VERSION                0U
#define RBA_ETHICMP_SW_PATCH_VERSION                0U
/*End: Common Published information*/

/*****************************************************************************************************
*                                   Prototypes
*****************************************************************************************************/
#define RBA_ETHICMP_START_SEC_CODE
#include "rba_EthIcmp_MemMap.h"
extern FUNC( void, RBA_ETHICMP_CODE )   rba_EthIcmp_Init(
                                P2CONST( rba_EthIcmp_Config_to, AUTOMATIC, AUTOMATIC ) IcmpConfig_pco );

extern  FUNC( Std_ReturnType, RBA_ETHICMP_CODE ) rba_EthIcmp_Transmit (
                                VAR( TcpIp_LocalAddrIdType, AUTOMATIC )             LocalAddrId_u8,
                                P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )   RemoteAddr_cpst,
                                VAR( uint8, AUTOMATIC )                             Ttl_u8,
                                VAR( uint8, AUTOMATIC )                             Type_u8,
                                VAR( uint8, AUTOMATIC )                             Code_u8,
                                VAR( uint16, AUTOMATIC )                            DataLength_u16,
                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )                TxData_cpu8 );

#define RBA_ETHICMP_STOP_SEC_CODE
#include "rba_EthIcmp_MemMap.h"

#endif /* #if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHICMP_H */
