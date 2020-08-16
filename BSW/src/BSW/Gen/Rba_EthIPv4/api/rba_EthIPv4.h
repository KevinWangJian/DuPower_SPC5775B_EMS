

#ifndef RBA_ETHIPV4_H
#define RBA_ETHIPV4_H

#if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) )

/*
****************************************************************************************************
*                                   Defines
****************************************************************************************************
*/

/* Vendor Id */
#define RBA_ETHIPV4_VENDOR_ID                   6U

/* rba_EthIPv4 module Id */
#define RBA_ETHIPV4_MODULE_ID                   255U

/* rba_EthIPv4 instance Id */
#define RBA_ETHIPV4_INSTANCE_ID                 170U

#define RBA_ETHIPV4_SW_MAJOR_VERSION                4U
#define RBA_ETHIPV4_SW_MINOR_VERSION                0U
#define RBA_ETHIPV4_SW_PATCH_VERSION                0U

#define RBA_ETHIPV4_HDRLENGTH                       20U

/* Multicast IP address area: Start 224.0.0.0 */
#define     RBA_ETHIPV4_MULTICASTADDR_MIN               0xE0000000UL

/* Multicast IP address area: End   239.255.255.255 */
#define     RBA_ETHIPV4_MULTICASTADDR_MAX               0xEFFFFFFFUL

/* Position of upper layer transport protocol value in IPv4 header */
#define     RBA_ETHIPV4_TP_PROTOCOL                     9U
/* Position of source IPv4 address in IPv4 header */
#define     RBA_ETHIPV4_SRCIPV4ADDR_OFFSET              12U
/* Position of destination IPv4 address in IPv4 header */
#define     RBA_ETHIPV4_DESTIPV4ADDR_OFFSET             16U

/*
****************************************************************************************************
*                                   Prototypes
****************************************************************************************************
*/
#define RBA_ETHIPV4_START_SEC_CODE
#include "rba_EthIPv4_MemMap.h"


/* Function declaration*/
extern FUNC( void, RBA_ETHIPV4_CODE ) rba_EthIPv4_Init (
                                            P2CONST( rba_EthIPv4_Config_to, AUTOMATIC, AUTOMATIC ) CurrConfig_pco );

extern FUNC( void, TCPIP_CODE ) rba_EthIPv4_MainFunction( void );


extern FUNC( TcpIp_ReturnType, RBA_ETHIPV4_CODE ) rba_EthIPv4_Transmit(
                                            VAR( uint8,                  AUTOMATIC )                    LocalAddrId_u8,
                                            VAR( uint32,                 AUTOMATIC )                    DestIpAddr_u32,
                                            P2VAR( uint8,                AUTOMATIC, AUTOMATIC )         Buffer_pu8,
                                            VAR( uint8,                  AUTOMATIC )                    BufIdx_u8,
                                            P2CONST( TcpIp_IpHeader_tst, AUTOMATIC, AUTOMATIC )         IpHeader_pcst,
                                            VAR( uint16,                 AUTOMATIC )                    TotLength_u16 );



extern FUNC( BufReq_ReturnType, RBA_ETHIPV4_CODE ) rba_EthIPv4_ProvideTxBuffer(
                                            VAR( uint8, AUTOMATIC )                 LocalAddrId_u8,
                                            VAR( uint32, AUTOMATIC )                DestIpAddr_u32,
                                            VAR( uint8, AUTOMATIC )                 FramePrio_u8,
                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    BufIdx_pu8,
                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    * Buffer_ppu8,
                                            P2VAR( uint16, AUTOMATIC, AUTOMATIC )   ReqLengthIn_pu16 );

extern FUNC( TcpIp_AddressType, RBA_ETHIPV4_CODE ) rba_EthIPv4_ChkIPv4AddrType(
                                            VAR( uint32,        AUTOMATIC )                 DestIpAddr_u32,
                                            VAR( uint32,        AUTOMATIC )                 SrcIpAddr_u32,
                                            VAR( uint32,        AUTOMATIC )                 NetMask_u32 );

extern FUNC( void, RBA_ETHIPV4_CODE ) rba_EthIPv4_GetIPMulticastDestEthAddr(
                                            VAR( uint32,        AUTOMATIC )                 DestMultiCastIpAddr_u32,
                                            P2VAR( uint8,       AUTOMATIC, AUTOMATIC )      DestEthAddr_pau8 );

#define RBA_ETHIPV4_STOP_SEC_CODE
#include "rba_EthIPv4_MemMap.h"

#endif /* #if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHIPV4_H */

