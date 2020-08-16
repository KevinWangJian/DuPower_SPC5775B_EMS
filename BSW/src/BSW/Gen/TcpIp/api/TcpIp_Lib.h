

#ifndef TCPIP_LIB_H
#define TCPIP_LIB_H

#include "TcpIp_Cfg.h"

#ifdef TCPIP_CONFIGURED
#include "TcpIp_Types.h"

/* Compiler switch for TcpIp_OnesComplChkSum() */
/* TcpIp_OnesComplChkSum() shall be available if software checksum offload or verification needs to be done for IPv4, Udp, Tcp or Icmp */

/* To avoid MISRA warning where macro will be replaced with token 'defined'-a preprocessing operator (Rule 1.3) */
#if ( ( ( ( defined(RBA_ETHIPV4_SW_CHKSUM_RX_UDP)  && ( RBA_ETHIPV4_SW_CHKSUM_RX_UDP  == STD_ON ) ) || ( defined(RBA_ETHIPV4_SW_CHKSUM_TX_UDP)  && ( RBA_ETHIPV4_SW_CHKSUM_TX_UDP  == STD_ON ) ) ) && ( TCPIP_UDP_ENABLED    == STD_ON ) ) || \
                                              ( ( ( defined(RBA_ETHUDP_SW_CHKSUM_RX_IPV6)  && ( RBA_ETHUDP_SW_CHKSUM_RX_IPV6  == STD_ON ) ) || ( defined(RBA_ETHIPV6_SW_CHKSUM_TX_UDP)  && ( RBA_ETHIPV6_SW_CHKSUM_TX_UDP  == STD_ON ) ) ) && ( TCPIP_UDP_ENABLED    == STD_ON ) ) || \
                                              ( ( ( defined(RBA_ETHIPV4_SW_CHKSUM_RX_ICMP) && ( RBA_ETHIPV4_SW_CHKSUM_RX_ICMP == STD_ON ) ) || ( defined(RBA_ETHIPV4_SW_CHKSUM_TX_ICMP) && ( RBA_ETHIPV4_SW_CHKSUM_TX_ICMP == STD_ON ) ) ) && ( TCPIP_ICMP_ENABLED   == STD_ON ) ) || \
                                              ( ( ( defined(RBA_ETHICMPV6_SW_CHKSUM_RX)    && ( RBA_ETHICMPV6_SW_CHKSUM_RX    == STD_ON ) ) || ( defined(RBA_ETHICMPV6_SW_CHKSUM_TX)    && ( RBA_ETHICMPV6_SW_CHKSUM_TX    == STD_ON ) ) ) && ( TCPIP_ICMPV6_ENABLED == STD_ON ) ) || \
                                              ( ( ( defined(RBA_ETHTCP_SW_CHKSUM_RX)       && ( RBA_ETHTCP_SW_CHKSUM_RX       == STD_ON ) ) || ( defined(RBA_ETHTCP_SW_CHKSUM_TX)       && ( RBA_ETHTCP_SW_CHKSUM_TX       == STD_ON ) ) ) && ( TCPIP_TCP_ENABLED    == STD_ON ) ) || \
                                              ( defined(RBA_ETHIPV4_SW_CHKSUM_RX) && ( RBA_ETHIPV4_SW_CHKSUM_RX == STD_ON ) ) || ( defined(RBA_ETHIPV4_SW_CHKSUM_TX_IPV4)  && ( RBA_ETHIPV4_SW_CHKSUM_TX_IPV4  == STD_ON ) ) || \
                                              ( defined(RBA_ETHIPV4_FRAG_ENABLED) && ( RBA_ETHIPV4_FRAG_ENABLED == STD_ON ) ) || ( defined(RBA_ETHIPV4_REASSEMBLY_ENABLED) && ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON ) ) )

#define TCPIP_ONES_COMPL_CHKSUM_ENABLED             ( STD_ON )
#else
#define TCPIP_ONES_COMPL_CHKSUM_ENABLED             ( STD_OFF )
#endif

#define TCPIP_START_SEC_CODE
#include "TcpIp_MemMap.h"
extern FUNC( uint32, TCPIP_CODE ) TcpIp_RandNumXor64( void );

#if ( TCPIP_ONES_COMPL_CHKSUM_ENABLED == STD_ON )
extern FUNC( Std_ReturnType, TCPIP_CODE ) TcpIp_OnesComplChkSum (
                                P2CONST( void, AUTOMATIC, AUTOMATIC )                   Data_pcv,
                                P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )    PseudoHdr_pcst,
                                VAR( uint16, AUTOMATIC )                                Length_u16,
								P2VAR( uint16, AUTOMATIC, AUTOMATIC )                   OutputChkSum_pu16 );
#endif

extern FUNC( void, TCPIP_CODE ) TcpIp_ReadU16(
                                       P2CONST( uint8, AUTOMATIC, AUTOMATIC )   Data_pu8,
                                       P2VAR( uint16, AUTOMATIC, AUTOMATIC )    Data_pu16 );


extern FUNC( void, TCPIP_CODE ) TcpIp_ReadU32(
                                       P2CONST( uint8, AUTOMATIC, AUTOMATIC )   Data_pu8,
                                       P2VAR( uint32, AUTOMATIC, AUTOMATIC )    Data_pu32 );

extern FUNC( void, TCPIP_CODE ) TcpIp_WriteU16(
                                       P2VAR( uint8, AUTOMATIC, AUTOMATIC )     Data_pu8,
                                       CONST( uint16, AUTOMATIC )               Data_u16 );

extern FUNC( void, TCPIP_CODE ) TcpIp_WriteU32(
                                       P2VAR( uint8, AUTOMATIC, AUTOMATIC )     Data_pu8,
                                       CONST( uint32, AUTOMATIC )               Data_u32 );

#define TCPIP_STOP_SEC_CODE
#include "TcpIp_MemMap.h"
#endif /* #ifdef TCPIP_CONFIGURED */

#endif /* TCPIP_LIB_H */

/*<BASDKey>
**********************************************************************************************************************
* $History___:$
**********************************************************************************************************************
</BASDKey>*/
