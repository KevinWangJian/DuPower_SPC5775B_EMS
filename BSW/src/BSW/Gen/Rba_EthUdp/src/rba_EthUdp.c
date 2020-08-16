
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) )
#include "rba_EthUdp.h"
#include "rba_EthUdp_Cbk.h"

#include "SoAd_Cbk.h"

#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
#include "rba_EthDHCP.h"
#endif

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif

#if ( TCPIP_ICMP_ENABLED == STD_ON )
#include "rba_EthIcmp.h"
#endif

#if ( TCPIP_ICMPV6_ENABLED == STD_ON )
#include "rba_EthIcmpV6.h"
#endif

#include "TcpIp_Lib.h"
#include "TcpIp_Prv.h"
#include "rba_EthUdp_Prv.h"

#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "DET AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "DET AUTOSAR minor version undefined or mismatched"
#endif
#endif /* ( TCPIP_DEV_ERROR_DETECT != STD_OFF ) */

/*
 ***************************************************************************************************
 * Global Variables
 ***************************************************************************************************
 */

#define RBA_ETHUDP_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

P2CONST( rba_EthUdp_Config_to, AUTOMATIC, AUTOMATIC )    rba_EthUdp_Config_pco     = NULL_PTR;   /* Pointer will be initialized in the Init Function */
VAR( uint16,                              AUTOMATIC )    rba_EthUdp_UsedSocCnt_u16 = 0;
VAR( uint16,                              AUTOMATIC )    rba_EthUdp_PortAny_u16    = TCPIP_LOCAL_PORT_ANY_START;

#define RBA_ETHUDP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthUdp_MemMap.h"

#define RBA_ETHUDP_START_SEC_CODE
#include "rba_EthUdp_MemMap.h"

#if ( TCPIP_IPV4_ENABLED == STD_ON )
static FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_RxIndication_IPv4(
                                        P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )            PseudoHdr_pcst,
                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )                            RxData_pu8,
                                        VAR( uint16, AUTOMATIC )                                        RxDataSrcUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                        RxDataDestUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                        UdpBodyLen_u16,
                                        VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )               LocalAddrId_CtrlIdx_un,
                                        P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )       LocalAddrConfig_pcst,
                                        VAR( boolean, AUTOMATIC )                                       IsBroadcast_b );
#endif

#if ( TCPIP_ICMP_ENABLED == STD_ON )
static FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_SendIcmpPortNotReachable(
                                        P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )            PseudoHdr_pcst,
                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )                            RxData_pu8,
                                        VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )               LocalAddrId_CtrlIdx_un,
                                        P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )         RemoteAddrInet_pst );
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
static FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_RxIndication_IPv6(
                                        P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )            PseudoHdr_pcst,
                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )                            RxData_pu8,
                                        VAR( uint16, AUTOMATIC )                                        RxDataSrcUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                        RxDataDestUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                        UdpBodyLen_u16,
                                        VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )               LocalAddrId_CtrlIdx_un,
                                        P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )       LocalAddrConfig_pcst );
#endif

#if ( RBA_ETHUDP_SW_CHKSUM_RX_IPV6 == STD_ON )
static FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_VerifyUdpCksum_IPv6(
                                                    P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC) PseudoHdr_pcst,
                                                    P2CONST( uint8, AUTOMATIC, AUTOMATIC )             	RxData_pcu8,
                                                    VAR( uint16, AUTOMATIC )                            UdpBodyLen_u16 );
#endif

/********************************************************************************************************************/
/* rba_EthUdp_Init()            This function Initializes the rba_EthUdp module                                     */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* CurrConfig_pcst              Configuration data structure for rba_EthUdp module                                  */
/*                                                                                                                  */
/* Return type :                void                                                                                */
/********************************************************************************************************************/
FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_Init (
                                        P2CONST( rba_EthUdp_Config_to, AUTOMATIC, AUTOMATIC ) CurrConfig_pcst )
{

    VAR( TcpIp_SocketIdType, AUTOMATIC )                     lSocIdx_u16;

    /* Report DET if TcpIp_CurrConfig_pco is not intialized */
	RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == TcpIp_CurrConfig_pco ),                                  \
                                          RBA_ETHUDP_E_INIT_API_ID, RBA_ETHUDP_E_INIT_FAILED )

    /* Report DET if CurrConfig_pcst does not contain a valid configuration */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( ( CurrConfig_pcst != ( TcpIp_CurrConfig_pco->EthUdpConfig_pco) ),      \
                                          RBA_ETHUDP_E_INIT_API_ID, RBA_ETHUDP_E_INV_ARG )

   /* Initialize socket table */
   for(lSocIdx_u16 = 0; lSocIdx_u16 < TCPIP_UDPSOCKETMAX; lSocIdx_u16++)
   {
       rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].DomainType_u32   = TCPIP_AF_NONE;
       rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].LocalAddrId_u8   = (TcpIp_LocalAddrIdType) TCPIP_LOCALADDRID_INVALID;
       rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].LocalPort_u16    = TCPIP_PORT_ANY;
       rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].SockFramePrio_u8 = 0xFFu;
       rba_EthUdp_DynSockTbl_ast[lSocIdx_u16].SockState_en     = RBA_ETHUDP_SOCK_CLOSED;

   }

	/* Initialize global variables */
	rba_EthUdp_PortAny_u16       = TCPIP_LOCAL_PORT_ANY_START;
	rba_EthUdp_UsedSocCnt_u16    = 0;
    rba_EthUdp_Config_pco        = CurrConfig_pcst;
}

/********************************************************************************************************************/
/* rba_EthUdp_ProvideTxBuffer() This function is called from TcpIp or DHCP COMPs to UDP layer  to provide buffer    */
/*                              to copy payload and then transmit this data by calling rba_EthUdp_Transmit(). Add   */
/*                              UDP header length before requesting for buffer.                                     */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* SocketId_u16                Socket id on which data is to be transmitted                                         */
/* DestIPv4Addr_u32            IP address of the destination node to which this node wants to transmit data         */
/*                                                                                                                  */
/* Parameter IN-OUT: none                                                                                           */
/*                                                                                                                  */
/* Parameter OUT:                                                                                                   */
/* Buffer_ppu8                 Pointer to the granted buffer. A double pointer shall be passed and the address of   */
/*                             the granted buffer shall be updated into this.                                       */
/* BufIdx_pu8                  Index to the granted buffer resource. This shall be used during transmit request     */
/* GrantLength_pcu16           Requested buffer length. The lower layer can give a smaller buffer than requested.   */
/*                                                                                                                  */
/* Return type :                                                                                                    */
/* BufReq_ReturnType           BUFREQ_OK        : Buffer successfully provided                                      */
/*                             BUFREQ_E_NOT_OK  : Development error detected                                        */
/*                             BUFREQ_E_BUSY    : All buffers in use                                                */
/*																													*/
/* Notes :																											*/
/*	DD: This function adds the UDP header length to the incoming requested buffer length in order to allow for UDP  */
/*	protocol data.                                                                                                  */
/*	DD: Return error if the socket is not bound.                                                                    */
/*	DD: In case the lower layer returns "buffer overflow", return a "buffer not ok" error to upper layer.           */
/*	Reason:  The use case of re-trying an allocation in case of err code OVerflow is not used in case of UDP.       */
/* 		     It is also not re-entrant.                                                                             */
/*             + it complicates the code in some corner cases.                                                      */
/********************************************************************************************************************/
FUNC( BufReq_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_ProvideTxBuffer(
                                                VAR( TcpIp_SocketIdType, AUTOMATIC )            SocketId_u16,
                                                VAR( uint32, AUTOMATIC )                        DestIPv4Addr_u32,
                                                P2VAR( uint8, AUTOMATIC, AUTOMATIC )            BufIdx_pu8,
                                                P2VAR( uint8, AUTOMATIC, AUTOMATIC )            * Buffer_ppu8,
                                                P2CONST( uint16, AUTOMATIC, AUTOMATIC )			GrantLength_pcu16 )
{
    VAR( uint16, AUTOMATIC ) lGrantLength_u16;
    VAR( uint8, AUTOMATIC ) lBufferIdx_u8                       = 0;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC ) lBuffer_pu8            = NULL_PTR;
    VAR( BufReq_ReturnType, AUTOMATIC ) lProvideTxBuffRetVal_en = BUFREQ_E_NOT_OK; /* Pessimistic initialization */

    /* Checks: Report DET if rba_EthUdp module is uninitialised */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE((NULL_PTR == rba_EthUdp_Config_pco), RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID, RBA_ETHUDP_E_NOTINIT, BUFREQ_E_NOT_OK)
    /* Report DET if SocketId_u16 is not plausible*/
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE((TCPIP_UDPSOCKETMAX <= SocketId_u16), RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID, RBA_ETHUDP_E_INV_ARG, BUFREQ_E_NOT_OK)

    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE((NULL_PTR == GrantLength_pcu16), RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID, RBA_ETHUDP_E_NULL_PTR, BUFREQ_E_NOT_OK)
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE((NULL_PTR == BufIdx_pu8), RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID, RBA_ETHUDP_E_NULL_PTR, BUFREQ_E_NOT_OK)
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE((NULL_PTR == Buffer_ppu8), RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID, RBA_ETHUDP_E_NULL_PTR, BUFREQ_E_NOT_OK)

    /*DD: Add UDP header length to the buffer length requested by upper layer to allow space for the UDP protocol overhead*/
    lGrantLength_u16 = (*GrantLength_pcu16) + RBA_ETHUDP_HDRLENGTH;

    /* DD: return no buffer available if the socket is not bound. */
    /* Check whether the requested socket state is RBA_ETHUDP_SOCK_BOUND */
    if(RBA_ETHUDP_SOCK_BOUND == rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en)
    {
        switch (rba_EthUdp_DynSockTbl_ast[SocketId_u16].DomainType_u32)
        {
            #if (TCPIP_IPV4_ENABLED == STD_ON)
            case TCPIP_AF_INET:
			{
                /* Report DET if DestIPv4Addr_u32 is 0.0.0.0 and return BUFREQ_E_NOT_OK */
                RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( TCPIP_IPADDR_ANY == DestIPv4Addr_u32 ), RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID,  \
                                           RBA_ETHUDP_E_INV_ARG, BUFREQ_E_NOT_OK )
                lProvideTxBuffRetVal_en = rba_EthIPv4_ProvideTxBuffer(rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalAddrId_u8,
                                                                DestIPv4Addr_u32,
                                                                rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockFramePrio_u8,
                                                                &lBufferIdx_u8,
                                                                &lBuffer_pu8,
                                                                &lGrantLength_u16);
            break;
			}
            #endif

            #if (TCPIP_IPV6_ENABLED == STD_ON)
            case TCPIP_AF_INET6:
			{
			    (void) DestIPv4Addr_u32;
                lProvideTxBuffRetVal_en = rba_EthIPv6_ProvideTxBuffer(rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalAddrId_u8,
                                                                rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockFramePrio_u8,
                                                                &lBufferIdx_u8,
                                                                &lBuffer_pu8,
                                                                &lGrantLength_u16);
            break;
			}
            #endif

            default:
                /* Unknown domain. Throw DET report and break execution. */
                RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( RBA_ETHUDP_E_PROVIDE_TXBUFFER_API_ID, RBA_ETHUDP_E_NOPROTOOPT)
            break;
        }

        if (BUFREQ_OK == lProvideTxBuffRetVal_en)
        {
            /* Buffer size is OK, move the pointer to application payload start; substract the UDP header size */
            *Buffer_ppu8 = lBuffer_pu8 + RBA_ETHUDP_HDRLENGTH;
			*BufIdx_pu8 = lBufferIdx_u8;
			/* Grant length does not need to be assigned, because it is all ok, as requested by the caller. No change needed. */
        }
        else if(BUFREQ_E_OVFL == lProvideTxBuffRetVal_en)
        {
            /* DD: the use case of re-trying an allocation in case of error code Overflow is not used. It is also not re-entrant.
               Moreover, it complicates the code -> hence we do not support it. */
            lProvideTxBuffRetVal_en = BUFREQ_E_NOT_OK;
        }
        else
        {    /* Do nothing. Propagate the error code. */
        }
    }
    else
    {    /* Do nothing. Socket not bound. No buffer. */
    }

    return( lProvideTxBuffRetVal_en );
}


/********************************************************************************************************************/
/* rba_EthUdp_Transmit() This function is called from TcpIp or DHCP COMPs to transmit data over UDP. In this API    */
/*                        the UDP header is filled with source port, destination port, length and checksum.         */
/*                                                                                                                  */
/* Parameter IN:                                                                                                    */
/* SocketId_u16          Socket id on which data is to be transmitted                                               */
/* RemoteAddr_pst        Pointer to a structure containing remote IP address and remote port                        */
/* Buffer_pu8            Pointer to the buffer where data to be transmitted is copied.                              */
/* BufIdx_u8             Index to the buffer where the data is copied.                                              */
/* BufLength_u16         Length of data to be transmitted                                                           */
/*                                                                                                                  */
/* Return type :                                                                                                    */
/* TcpIp_ReturnType      TCPIP_OK                  : UDP datagram transmission successful                           */
/*                       TCPIP_E_NOT_OK            : UDP datagram transmission failed (general failure)             */
/*                       TCPIP_E_ARP_CACHE_MISS    : UDP datagram transmission failed because of ARP cache miss     */
/*                                                                                                                  */
/* Notes :                                                                                                          */
/* 	DD: Checksum field will be calculated in the IP transmit function because the src and dest IPs must be          */
/* 	calculated there anyway. (avoid two calls to resolve src IP)                                                    */
/*                                                                                                                  */
/* 	Implementation:                                                                                                 */
/* 	- fill the mandatory UDP header fields: src port, dest port, length, (cksum)*                                   */
/* 	- switch(AF domain)                                                                                             */
/* 		to decide what lower layer Transmit function to call.                                                       */
/********************************************************************************************************************/
FUNC(TcpIp_ReturnType, RBA_ETHUDP_CODE) rba_EthUdp_Transmit(
                                        VAR( TcpIp_SocketIdType, AUTOMATIC )                    SocketId_u16,
                                        P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )     RemoteAddr_pst,
                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )                    Buffer_pu8,
                                        VAR( uint8, AUTOMATIC )                                 BufIdx_u8,
                                        VAR( uint16, AUTOMATIC )                                BufLength_u16 )
{
    VAR( TcpIp_IpHeader_tst,    AUTOMATIC )     lIpHeader_st;
    VAR( uint16,                AUTOMATIC )     lPort_u16;
    VAR( TcpIp_LocalAddrIdType, AUTOMATIC )     lLocalAddrId_u8;    /* Will be retrieved from local socket configuration */
    VAR( uint16,                AUTOMATIC )     lTotUdpLength_u16   = 0;  /* Total Udp packet length; Will remain set to 0 if the buffer needs to be freed. */
	VAR( TcpIp_ReturnType,      AUTOMATIC )     lTcpIpRetVal_en     = TCPIP_OK; /* Optimistic initialization */

    /* Report DET if rba_EthUdp module is uninitialised */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == rba_EthUdp_Config_pco ), RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_NOTINIT, TCPIP_E_NOT_OK )
    /* Report DET if RemoteAddr_pst is NULL */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == RemoteAddr_pst ), RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_NULL_PTR, TCPIP_E_NOT_OK )
    /* Check whether socket handle is a plausible value */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( SocketId_u16 >= TCPIP_UDPSOCKETMAX ), RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_INV_ARG, TCPIP_E_NOT_OK )
    /* Report DET if Buffer_pu8 is NULL */
	RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == Buffer_pu8 ), RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_NULL_PTR, TCPIP_E_NOT_OK )

    /* Report DET: If rba_EthUdp_Transmit() is called on the socket which is not in state RBA_ETHUDP_SOCK_BOUND.
     * Runtime check of the socket state is performed in the rba_EthUdp_ProvideTxBuffer() API. Therefore, only DET check is sufficient here. */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( RBA_ETHUDP_SOCK_BOUND != rba_EthUdp_DynSockTbl_ast[SocketId_u16].SockState_en ), RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_INV_ARG, TCPIP_E_NOT_OK )

    /* Report DET: Local Domain not matching remote domain */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( RemoteAddr_pst->domain != rba_EthUdp_DynSockTbl_ast[SocketId_u16].DomainType_u32 ), RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_INV_ARG, TCPIP_E_NOT_OK )

	/* Common code: provide protocol and TTL/Hop Limit information to rba_EthIP layer. */
	lIpHeader_st.ProtoType_en = TCPIP_IPPROTO_UDP;
	lIpHeader_st.Ttl_u8 = rba_EthUdp_Config_pco->Ttl_u8; /* The TTL field specific for IPv4 is actually Hop Limit in the IPv6 protocol. */
	lLocalAddrId_u8 = rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalAddrId_u8; /* The local address is needed for lower layer call */

    /* AF domain specific code to fill header with required info (port, checksum) and to call the appropriate lower layer function */
    switch( rba_EthUdp_DynSockTbl_ast[SocketId_u16].DomainType_u32 )
    {
        #if (TCPIP_IPV4_ENABLED == STD_ON)
        case TCPIP_AF_INET:
        {
            /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 data. It is safe because of the switch before. */
            P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC ) lRemoteAdrIPv4_pst = (const TcpIp_SockAddrInetType*) RemoteAddr_pst;

            /* Report DET: If remote IP is 0.0.0.0  */
            /* MR12 RULE 10.4 VIOLATION: Type definition of wildcard IP address is according to AUTOSAR [SWS_TCPIP_00133]. */
            RBA_ETHUDP_DET_REPORT_ERROR_RET_VALUE( ( TCPIP_IPADDR_ANY == lRemoteAdrIPv4_pst->addr[0] ), RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_INV_ARG, TCPIP_E_NOT_OK )

            lPort_u16 = lRemoteAdrIPv4_pst->port;
        }
        break;
        #endif

        #if (TCPIP_IPV6_ENABLED == STD_ON)
        case TCPIP_AF_INET6:
        {
            /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv6 data. It is safe because of the switch before. */
            P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC ) lRemoteAdrIPv6_pst = (const TcpIp_SockAddrInet6Type*) RemoteAddr_pst;

            lPort_u16 = lRemoteAdrIPv6_pst->port;
        }
        break;
        #endif

        default:
            RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( RBA_ETHUDP_E_TRANSMIT_API_ID, RBA_ETHUDP_E_NOPROTOOPT )

            lTcpIpRetVal_en = TCPIP_E_NOT_OK;   /* Return value must be set to TCPIP_E_NOT_OK, because otherwise the unitialized port value will be written in the destination port field. */
        break;
    }

    if( lTcpIpRetVal_en == TCPIP_OK )   /* If the destination port has been successfully extracted */
    {
        if( 0 != BufLength_u16 ) /* 0 length means "free buffer". If not free, call the lower layer transmit API with specified length. */
        {
            /* Update the length of the UDP frame (UDP header + data size) */
            lTotUdpLength_u16 = BufLength_u16 + (uint16) RBA_ETHUDP_HDRLENGTH;

            /* Point to UDP header in the buffer pointer payload */
            Buffer_pu8 = ( Buffer_pu8 - RBA_ETHUDP_HDRLENGTH );

            /* UDP header:source port and length. The rest of the header is AF treated specific, below */
            TcpIp_WriteU16( &( Buffer_pu8[TCPIP_TP_SRCPORT_OFFSET] ) , rba_EthUdp_DynSockTbl_ast[SocketId_u16].LocalPort_u16 );

            /* UDP header: fill destination port. */
            TcpIp_WriteU16( &(Buffer_pu8[TCPIP_TP_DESTPORT_OFFSET]), lPort_u16 );

            /* Update the length of the UDP frame into the UDP header field */
            TcpIp_WriteU16( ( &( Buffer_pu8[RBA_ETHUDP_UDPFRAMELENGTH_UB] ) ), lTotUdpLength_u16 );

            /* Set checksum field to 0 to not influence the checksum calculation later in IP transmit function. */
            TcpIp_WriteU16( &(Buffer_pu8[RBA_ETHUDP_UDPCHKSUM_UB]), 0 );
        }

        switch( rba_EthUdp_DynSockTbl_ast[SocketId_u16].DomainType_u32 )
        {
            #if (TCPIP_IPV4_ENABLED == STD_ON)
            case TCPIP_AF_INET:
            {
                /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 data. It is safe because of the switch before. */
                P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC ) lRemoteAdrIPv4_pst = (const TcpIp_SockAddrInetType*) RemoteAddr_pst;

                lTcpIpRetVal_en = rba_EthIPv4_Transmit( lLocalAddrId_u8, lRemoteAdrIPv4_pst->addr[0], Buffer_pu8, BufIdx_u8, &lIpHeader_st, lTotUdpLength_u16 );
            }
            break;
            #endif

            #if (TCPIP_IPV6_ENABLED == STD_ON)
            case TCPIP_AF_INET6:
            {
                /* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv6 data. It is safe because of the switch before. */
                P2CONST( TcpIp_SockAddrInet6Type, AUTOMATIC, AUTOMATIC ) lRemoteAdrIPv6_pst = (const TcpIp_SockAddrInet6Type*) RemoteAddr_pst;

                lTcpIpRetVal_en = rba_EthIPv6_Transmit( lLocalAddrId_u8, &(lRemoteAdrIPv6_pst->addr[0]), Buffer_pu8, BufIdx_u8, &lIpHeader_st, lTotUdpLength_u16 );
            }
            break;
            #endif

            default:
                lTcpIpRetVal_en = TCPIP_E_NOT_OK;   /* Valid instruction must be present in the default case, even though the domain check has already been performed before. */
            break;
        }
    }

    return lTcpIpRetVal_en;
}

/********************************************************************************************************************/
/* rba_EthUdp_RxIndication() This function is called from IP COMPs to UDP layer after reception of a UDP datagram.  */
/*                                                                                                                  */
/* Input parameters:                                                                                                */
/* PseudoHdr_pcst    		Pointer to pseudo structure provided by IPv4. Contains destination IP, source IP        */
/*                          and IPv4 header length                                                                  */
/* LocalAddrId_CtrlIdx_un   Provides the local addrId or EthIf CtrlIdx (if broadcast ) of the received frame        */
/* RxData_pu8               Pointer to the received UDP datagram                                                    */
/* RxDataLen_u16            Length of the UDP datagram                                                              */
/* IsBroadcast_b            Indicates whether received frame is a broadcast frame or not                            */
/*                                                                                                                  */
/* Return type :            void                                                                                    */
/*                                                                                                              	*/
/* Notes:                                                                                                           */
/*	DD: Drop the frame if Udp checksum is not set by the remote node. Only UDP with checksum is supported. 			*/
/*  Processing steps:                                                                                               */
/*  - DET checks                                                                                                    */
/*  - Extract UDP protocol header info                                                                              */
/*  - Verify checksum                                                                                               */
/*  - Search for configured sockets that match the following conditions:                                            */
/*      1. Destination port mentioned in the frame matches with the local port of the socket                        */
/*      2. If the socket state is BOUND                                                                             */
/*      3a. If the received frame is unicast/multicast and localAddressId on which frame was received matches with  */
/*  localAddressId of the socket                                                                                    */
/*      3b. If the received frame is broadcast and EthIfCtrlIdx on which frame was received matches with            */
/*  EthIfCtrlIdx of the socket                                                                                      */
/*  - Call the SoAd Callback for the socket found.                                                                  */
/*  	                                                                                                            */
/*  Note: Callback EXCEPTION: Call DHCP layer callback if the packet matches DHCP port                              */
/********************************************************************************************************************/
FUNC(void, RBA_ETHUDP_CODE) rba_EthUdp_RxIndication(
                                P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )    PseudoHdr_pcst,
                                VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )       LocalAddrId_CtrlIdx_un,
                                P2VAR( uint8, AUTOMATIC, AUTOMATIC )                    RxData_pu8,
                                VAR( uint16, AUTOMATIC )                                RxDataLen_u16,
                                VAR( boolean, AUTOMATIC )                               IsBroadcast_b )
{
    VAR(uint16, AUTOMATIC)                                      lRxDataSrcUdpPort_u16;
    VAR(uint16, AUTOMATIC)                                      lRxDataDestUdpPort_u16;
    VAR(uint16, AUTOMATIC)                                      lUdpHdrTotLen_u16;
    P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   lLocalAddrConfig_pcst;

    /* Report DET if rba_EthUdp module is uninitialised */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == rba_EthUdp_Config_pco ), RBA_ETHUDP_E_RX_INDICATION_API_ID, RBA_ETHUDP_E_NOTINIT )
    /* Report DET if local address ID is invalid */
    RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( ( ( FALSE == IsBroadcast_b ) && ( LocalAddrId_CtrlIdx_un.LocalAddrId_u8 >= TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ), RBA_ETHUDP_E_RX_INDICATION_API_ID , RBA_ETHUDP_E_INV_ARG )
 	/* Report DET: RxData_pu8 is a null pointer */
	RBA_ETHUDP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == RxData_pu8 ), RBA_ETHUDP_E_RX_INDICATION_API_ID, RBA_ETHUDP_E_NULL_PTR )

	do /* processing steps. Each step may fail. Failure leads to packet drop. */
	{
		/* Check that RxDataLen_u16 is not less then Udp header length BEFORE reading data from buffer. */
		if( RxDataLen_u16 < RBA_ETHUDP_HDRLENGTH )
		{
		    RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( RBA_ETHUDP_E_RX_INDICATION_API_ID, RBA_ETHUDP_E_INV_ARG )
			/* MR12 RULE 15.4 VIOLATION: The break statements in case of processing failure signficantly improve the code readability at this point */
			break;
		}

		/* Read source and destination port from the buffer */
		TcpIp_ReadU16( &(RxData_pu8[TCPIP_TP_SRCPORT_OFFSET]),  &lRxDataSrcUdpPort_u16 );
		TcpIp_ReadU16( &(RxData_pu8[TCPIP_TP_DESTPORT_OFFSET]), &lRxDataDestUdpPort_u16 );

		/* Obtain total UDP datagram length in number of bytes */
		TcpIp_ReadU16( &(RxData_pu8[RBA_ETHUDP_UDPFRAMELENGTH_UB]), &lUdpHdrTotLen_u16 );

		/* Drop the frame if, UDP datagram length is greater than the received frame length or UDP datagram length is less than UDP header length */
		if( ( lUdpHdrTotLen_u16 > RxDataLen_u16 ) || ( lUdpHdrTotLen_u16 < RBA_ETHUDP_HDRLENGTH ) )
		{
		    RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( RBA_ETHUDP_E_RX_INDICATION_API_ID, RBA_ETHUDP_E_INV_ARG )
			/* MR12 RULE 15.4 VIOLATION: The break statements in case of processing failure signficantly improve the code readability at this point. */
			break;
		}

		/* If the received frame is unicast, fetch local address properties from TcpIp */
        if( FALSE == IsBroadcast_b )
        {
            VAR( Std_ReturnType, AUTOMATIC ) lRetVal_en =  TcpIp_GetLocalAddrIdProperties( LocalAddrId_CtrlIdx_un.LocalAddrId_u8, (&lLocalAddrConfig_pcst) );
			if( E_OK != lRetVal_en ) /* Exit loop if TcpIp_GetLocalAddrIdProperties returns E_NOT_OK. */
	    	{
				/* MR12 RULE 15.4 VIOLATION: The break statements in case of processing failure signficantly improve the code readability at this point.  */
				break;
			}
        }
        else
        {
			lLocalAddrConfig_pcst  = NULL_PTR; /* not applicable for Broadcast packets */
        }

		/* Domain specific processing: Update the IP address and port of the remote host, check cksum,...*/
		switch( PseudoHdr_pcst->IpDomainType_t )
		{
			#if (TCPIP_IPV4_ENABLED == STD_ON)
			case TCPIP_AF_INET:
			{
				/* Move the payload pointer before IPv4 specific processing -> Payload without UDP and IP headers is passed to SoAd.
				 * Also, update the Udp packet length (subtract the Udp header length). */
				rba_EthUdp_RxIndication_IPv4( PseudoHdr_pcst, ( RxData_pu8 + RBA_ETHUDP_HDRLENGTH ), lRxDataSrcUdpPort_u16, lRxDataDestUdpPort_u16,
					( lUdpHdrTotLen_u16 - RBA_ETHUDP_HDRLENGTH ), LocalAddrId_CtrlIdx_un, lLocalAddrConfig_pcst, IsBroadcast_b );
			}
			break;
			#endif

			#if (TCPIP_IPV6_ENABLED == STD_ON)
			case TCPIP_AF_INET6:
			{
				/* Pass the RxData_pu8 buffer WITH the UDP header length to the IPv6 specific processing function.
			     * The UDP header is needed here to validate the UDP checksum (is SW checksum is enabled) -> only for UDP-over-IPv6 RX packets.
				 * Therefore, the passed Udp packet length must include the header length as well. */
				rba_EthUdp_RxIndication_IPv6( PseudoHdr_pcst, RxData_pu8, lRxDataSrcUdpPort_u16, lRxDataDestUdpPort_u16,
					lUdpHdrTotLen_u16, LocalAddrId_CtrlIdx_un, lLocalAddrConfig_pcst );
			}
			break;
			#endif

			default: /* Unknown domain. Report to DET. */
			    RBA_ETHUDP_DET_REPORT_ERROR_TRUE_NO_RET( RBA_ETHUDP_E_RX_INDICATION_API_ID, RBA_ETHUDP_E_AFNOSUPPORT );
				break;
		}
	}
	while(FALSE); /* DD: this construction is not a loop. It is used only to permit usage of break; at any point where the processing encounters a failure. */
}

#if ( TCPIP_IPV4_ENABLED == STD_ON )
/********************************************************************************************************************/
/* rba_EthUdp_RxIndication_IPv4() This is a helper function called by rba_EthUdp_RxIndication and it performs only  */
/*                          IPv4 specific processing steps before RX indication to upper layer.                     */
/*                                                                                                                  */
/* Input parameters:                                                                                                */
/* PseudoHdr_pcst    		Pointer to pseudo structure provided by IPv4. Contains destination IP, source IP        */
/*                          and IPv4 header length                                                                  */
/* RxData_pu8               Pointer to the received UDP datagram                                                    */
/* RxDataSrcUdpPort_u16     Source port of the received UDP datagram                                                */
/* RxDataDestUdpPort_u16    Destination port of the received UDP datagram                                           */
/* UdpBodyLen_u16           UDP datagram body length (not including the UDP header)                                 */
/* LocalAddrId_CtrlIdx_un   Provides the local addrId or EthIf CtrlIdx (if broadcast ) of the received frame        */
/* LocalAddrConfig_pcst     Pointer to local IPv4 address configuration if received UDP datagram is of unicast type.*/
/*                          Can be NULL if received UDP datagram is of broadcast type.                              */
/* IsBroadcast_b            Indicates whether received frame is a broadcast frame or not                            */
/*                                                                                                                  */
/* Return type :            void                                                                                    */
/*                                                                                                              	*/
/* Notes:                                                                                                           */
/*  Processing steps:                                                                                               */
/*  - Search for configured sockets that match the following conditions:                                            */
/*      1. Destination port mentioned in the frame matches with the local port of the socket                        */
/*      2. If the socket state is BOUND                                                                             */
/*      3a. If the received frame is unicast/multicast and localAddressId on which frame was received matches with  */
/*  localAddressId of the socket                                                                                    */
/*      3b. If the received frame is broadcast and EthIfCtrlIdx on which frame was received matches with            */
/*  EthIfCtrlIdx of the socket                                                                                      */
/*  - Callback EXCEPTION: Call DHCP layer callback if the packet matches DHCP port                                  */
/*  - Call the SoAd Callback for the socket found                                                                   */
/*  - Send ICMP port unreachable errors if no matching socket is found                                              */
/********************************************************************************************************************/
static FUNC(void, RBA_ETHUDP_CODE) rba_EthUdp_RxIndication_IPv4(
                                        P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )        PseudoHdr_pcst,
                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )                        RxData_pu8,
                                        VAR( uint16, AUTOMATIC )                                    RxDataSrcUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                    RxDataDestUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                    UdpBodyLen_u16,
                                        VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )           LocalAddrId_CtrlIdx_un,
                                        P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst,
                                        VAR( boolean, AUTOMATIC )                                   IsBroadcast_b )
{
	VAR( uint16, AUTOMATIC )                    lSocketId_u16;
    VAR( TcpIp_SockAddrInetType, AUTOMATIC )    lRemoteAddrInet_st;
	VAR( Std_ReturnType, AUTOMATIC )            lRetVal_en = E_NOT_OK;

	/* Update the IP address and port of the remote host which sent the data */
	lRemoteAddrInet_st.domain   = PseudoHdr_pcst->IpDomainType_t;
	lRemoteAddrInet_st.port     = RxDataSrcUdpPort_u16;
	lRemoteAddrInet_st.addr[0]  = PseudoHdr_pcst->RemoteIpAddr_un.IPv4Addr_u32;

	/* Find the socket matching to destination IP(LocalAddrId) and destination port. See above the conditions */
	for ( lSocketId_u16 = 0; lSocketId_u16 < TCPIP_UDPSOCKETMAX; lSocketId_u16++ )
	{
		P2VAR( rba_EthUdp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC) lDynSockTblEntry_pst = &(rba_EthUdp_DynSockTbl_ast[lSocketId_u16]);

		if( ( RxDataDestUdpPort_u16 == lDynSockTblEntry_pst->LocalPort_u16 ) &&    /* Check for condition 1 as mentioned above  */
			( RBA_ETHUDP_SOCK_BOUND == lDynSockTblEntry_pst->SockState_en ) &&      /* Check for condition 2 as mentioned above  */
			( ( ( FALSE == IsBroadcast_b ) && ( LocalAddrId_CtrlIdx_un.LocalAddrId_u8 == lDynSockTblEntry_pst->LocalAddrId_u8 ) ) ||  /* Check for condition 3a as mentioned above  */
			( ( FALSE != IsBroadcast_b ) && ( LocalAddrId_CtrlIdx_un.EthIfCtrlIdx_u8 == rba_EthUdp_LocalAddressToCtrlMap_au8[lDynSockTblEntry_pst->LocalAddrId_u8] ) ) ) )  /* Check for condition 3b as mentioned above  */
		{
			lRetVal_en = E_OK; /* socket found -> this is a success criteria! */

			#if ( TCPIP_DHCP_CLIENT_ENABLED == STD_ON )
			/* If the frame is of Dhcp type rba_EthDHCP_RxIndication() shall be called as SoAd_RxIndication() shall be called */
			if( ( RxDataDestUdpPort_u16 == TCPIP_DHCPCLIENT_PORT ) &&
				( RxDataSrcUdpPort_u16 == TCPIP_DHCPSERVER_PORT ) )
			{
                /* MR12 RULE 11.3 VIOLATION: Typecasted to TcpIp_SockAddrType* to be used in domain agnostic function call. It is safe because of the domain switch. */
				rba_EthDHCP_RxIndication( lSocketId_u16, ( (TcpIp_SockAddrType*) (&lRemoteAddrInet_st) ), RxData_pu8, UdpBodyLen_u16, IsBroadcast_b );
				/* DD: No multiple indications possible if DHCP -> so exit the search loop. */
				break;
			}
			#endif /* DHCP */

			/* Normal processing: assume a SoAd socket -> call SoAd callback */
            /* MR12 RULE 11.3 VIOLATION: Typecasted to TcpIp_SockAddrType* to be used in domain agnostic function call. It is safe because of the domain switch. */
			SoAd_RxIndication( ( lSocketId_u16 + TCPIP_UDP_SOCKET_OFFSET ), ( (TcpIp_SockAddrType*) (&lRemoteAddrInet_st) ), RxData_pu8, UdpBodyLen_u16 );

			/* If the received frame is unicast there can be only one UL_RxIndication() possible and loop can be terminated. */
			/* In case of multicast and broadcast, frames shall be forwarded to ALL sockets matching destination port and localAddressId/EthIfCtrlIdx */
			if( ( NULL_PTR != LocalAddrConfig_pcst ) && ( TCPIP_UNICAST == LocalAddrConfig_pcst->IpAddressType_en ) )
			{
				/* MR12 RULE 15.4 VIOLATION: The break statement is used for stopping the processing loop for speed optimization purposes. */
				break; /* Unicast -> processing is finished */
			}
		}
	}

	/* Send ICMP port unreachable frame if there is no socket match and the received frame is unicast */
	#if ( TCPIP_ICMP_ENABLED == STD_ON )
	if( ( lRetVal_en != E_OK ) && /* no socket match */
		( NULL_PTR != LocalAddrConfig_pcst ) && ( TCPIP_UNICAST == LocalAddrConfig_pcst->IpAddressType_en ) ) /* valid unicast */
	{
		rba_EthUdp_SendIcmpPortNotReachable( PseudoHdr_pcst, RxData_pu8, LocalAddrId_CtrlIdx_un, &lRemoteAddrInet_st );
	}
	#endif /* #if ( TCPIP_ICMP_ENABLED == STD_ON ) */
}
#endif  /* #if ( TCPIP_IPV4_ENABLED == STD_ON ) */

#if ( TCPIP_ICMP_ENABLED == STD_ON )
/********************************************************************************************************************/
/* rba_EthUdp_SendIcmpPortNotReachable() This is a helper function called from rba_EthUdp_RxIndication_IPv4, which  */
/*                          sends an ICMP port unreachable frame if there is no socket match and the received frame */
/*                          is unicast.                                                                             */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* PseudoHdr_pcst    		Pointer to pseudo structure provided by IPv4. Contains destination IP, source IP        */
/*                          and IPv4 header length                                                                  */
/* RxData_pu8               Pointer to the received UDP datagram                                                    */
/* LocalAddrId_CtrlIdx_un   Provides the local addrId or EthIf CtrlIdx (if broadcast ) of the received frame        */
/* RemoteAddrInet_pst       Pointer to structure containing the remote address info of the UDP frame transmitter    */
/*                                                                                                                  */
/* Return type :            void                                                                                    */
/********************************************************************************************************************/
static FUNC( void, RBA_ETHUDP_CODE ) rba_EthUdp_SendIcmpPortNotReachable(
                                        P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )      PseudoHdr_pcst,
                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )                      RxData_pu8,
                                        VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )         LocalAddrId_CtrlIdx_un,
                                        P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )   RemoteAddrInet_pst )
{
	VAR( uint16, AUTOMATIC ) lUdpHdrTotLen_u16 = ( RBA_ETHICMP_DEST_UNREACH_DATASIZE + PseudoHdr_pcst->IPv4HdrLen_u8 );

	/* ICMP payload/message contains IP header followed by 8 bytes of UDP/TCP header */
	/* Move the pointer back to IP header */
	RxData_pu8 = ( RxData_pu8 - ( PseudoHdr_pcst->IPv4HdrLen_u8 + RBA_ETHUDP_HDRLENGTH ) );

	(void)rba_EthIcmp_Transmit( LocalAddrId_CtrlIdx_un.LocalAddrId_u8,
						RemoteAddrInet_pst,
						0,                                         /* TTL = 0 indicates default value will be used */
						(uint8)RBA_ETHICMP_DEST_UNREACH_E,
						(uint8)RBA_ETHICMP_DEST_UNREACH_PORT_E,
						lUdpHdrTotLen_u16,
						RxData_pu8 );
}
#endif  /* #if ( TCPIP_ICMP_ENABLED == STD_ON ) */

#if ( TCPIP_IPV6_ENABLED == STD_ON )
/********************************************************************************************************************/
/* rba_EthUdp_RxIndication_IPv6() This is a helper function called by rba_EthUdp_RxIndication and it performs only  */
/*                          IPv6 specific processing steps before RX indication to upper layer.                     */
/*                                                                                                                  */
/* Input parameters:                                                                                                */
/* PseudoHdr_pcst    		Pointer to pseudo structure provided by IPv6. Contains destination IP, source IP        */
/*                          and IPv6 header length                                                                  */
/* RxData_pu8               Pointer to the received UDP datagram                                                    */
/* RxDataSrcUdpPort_u16     Source port of the received UDP datagram                                                */
/* RxDataDestUdpPort_u16    Destination port of the received UDP datagram                                           */
/* UdpBodyLen_u16           The whole UDP datagram length -> including the UDP header length                        */
/* LocalAddrId_CtrlIdx_un   Provides the local addrId or EthIf CtrlIdx (if broadcast ) of the received frame        */
/* LocalAddrConfig_pcst     Pointer to local IPv4 address configuration if received UDP datagram is of unicast type.*/
/*                          Can be NULL if received UDP datagram is of broadcast type.                              */
/*                                                                                                                  */
/* Return type :            void                                                                                    */
/*                                                                                                              	*/
/* Notes:                                                                                                           */
/*  Processing steps:                                                                                               */
/*  - Verifies the checksum of the received UDP frame                                                               */
/*    Note: UDP handles the checksum validation only for IPv6 Rx frames (due to UDP protocol specific processing for*/
/*          IPv6). The checksum validation for IPv6 Tx is handled in the IPv6 layer for better performance.         */
/*  - Search for configured sockets that match the following conditions:                                            */
/*      1. Destination port mentioned in the frame matches with the local port of the socket                        */
/*      2. If the socket state is BOUND                                                                             */
/*      3a. If the received frame is unicast/multicast and localAddressId on which frame was received matches with  */
/*  localAddressId of the socket                                                                                    */
/*  - Call the SoAd Callback for the socket found                                                                   */
/*                                                                                                                  */
/*  Differences from IPv4 specific processing:                                                                      */
/*  1. It does not support DHCP Rx indication call                                                                  */
/*  2. It does not reply with ICMP frame in case of port unreachable                                                */
/********************************************************************************************************************/
static FUNC(void, RBA_ETHUDP_CODE) rba_EthUdp_RxIndication_IPv6(
                                        P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )        PseudoHdr_pcst,
                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )                        RxData_pu8,
                                        VAR( uint16, AUTOMATIC )                                    RxDataSrcUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                    RxDataDestUdpPort_u16,
                                        VAR( uint16, AUTOMATIC )                                    UdpBodyLen_u16,
                                        VAR( TcpIp_LocalAddrId_EthIfCtrl_tun, AUTOMATIC )           LocalAddrId_CtrlIdx_un,
                                        P2CONST( TcpIp_LocalAddrConfig_to, AUTOMATIC, AUTOMATIC )   LocalAddrConfig_pcst )
{
	VAR( uint32, AUTOMATIC )                    idx_u32;
	VAR( TcpIp_SockAddrInet6Type, AUTOMATIC )   lRemoteAddrInet6_st;

	/* Update the IP address and port of the remote host which sent the data */
	lRemoteAddrInet6_st.domain	= PseudoHdr_pcst->IpDomainType_t;
	lRemoteAddrInet6_st.port	= RxDataSrcUdpPort_u16;
	for (idx_u32 = 0; idx_u32 < 4u; idx_u32++) /* Address copy loop */
	{
		lRemoteAddrInet6_st.addr[idx_u32] = PseudoHdr_pcst->RemoteIpAddr_un.IPv6Addr_pcu32[idx_u32];
	}

	do /* Actual processing: checksum, match socket, call upper layers, send error frames (if applicable). */
	{
		VAR( uint16, AUTOMATIC )   lSocketId_u16;

		#if ( RBA_ETHUDP_SW_CHKSUM_RX_IPV6 == STD_ON ) /* Verify checksum (only if it is not already performed by the HW) */
		{
            /* DD: Checksum for IPv6 Rx frames is performed by UDP component. The IPv4 implementation implements checksums checks at IP layer stage. */
			VAR( Std_ReturnType, AUTOMATIC ) lRetVal_en = rba_EthUdp_VerifyUdpCksum_IPv6( PseudoHdr_pcst, RxData_pu8, UdpBodyLen_u16 );
			if( lRetVal_en != E_OK )
			{
				/* MR12 RULE 15.4 VIOLATION: The break statements in case of processing failure signficantly improve the code readability at this point */
				break;
			}
		}
		#endif

		/* Move the payload pointer AFTER validating the checksum for RX UDP packet. Payload without UDP and IP headers is passed to SoAd */
		RxData_pu8 = ( RxData_pu8 + RBA_ETHUDP_HDRLENGTH );
		/* Remove the UDP header length from the received data length before passing it to the upper layer */
		UdpBodyLen_u16 = ( (uint16)( UdpBodyLen_u16 - RBA_ETHUDP_HDRLENGTH ) );

		/* Find the socket matching to destination IP(LocalAddrId) and destination port. See above the conditions */
		for ( lSocketId_u16 = 0; lSocketId_u16 < TCPIP_UDPSOCKETMAX; lSocketId_u16++ )
		{
			if( ( RxDataDestUdpPort_u16 == rba_EthUdp_DynSockTbl_ast[lSocketId_u16].LocalPort_u16 ) &&    /* Check for condition 1 as mentioned above  */
				( RBA_ETHUDP_SOCK_BOUND == rba_EthUdp_DynSockTbl_ast[lSocketId_u16].SockState_en ) &&      /* Check for condition 2 as mentioned above  */
				( LocalAddrId_CtrlIdx_un.LocalAddrId_u8 == rba_EthUdp_DynSockTbl_ast[lSocketId_u16].LocalAddrId_u8 ) )  /* Check for condition 3a as mentioned above */
			{
				/* Normal processing: assume a SoAd socket -> call SoAd callback */
                /* MR12 RULE 11.3 VIOLATION: Typecasted to TcpIp_SockAddrType* to be used in domain agnostic function call. It is safe because of the domain switch. */
				SoAd_RxIndication( ( lSocketId_u16 + TCPIP_UDP_SOCKET_OFFSET ), ( (TcpIp_SockAddrType*) (&lRemoteAddrInet6_st) ), RxData_pu8, UdpBodyLen_u16 );

				/* If the received frame is unicast there can be only one UL_RxIndication() possible and loop can be terminated. */
				/* In case of multicast and broadcast, frames shall be forwarded to ALL sockets matching destination port  and localAddressId/EthIfCtrlIdx */
				if( ( NULL_PTR != LocalAddrConfig_pcst ) && ( TCPIP_UNICAST == LocalAddrConfig_pcst->IpAddressType_en ) )
				{
					break; /* unicast -> processing is finished */
				}
			}
		}
	}
	while (FALSE); /* DD: this is not a loop. This construct allows code simplification in case early abort of processing is needed, by means of break statements. */
}
#endif /* #if ( TCPIP_IPV6_ENABLED == STD_ON ) */

#if ( RBA_ETHUDP_SW_CHKSUM_RX_IPV6 == STD_ON )
/********************************************************************************************************************/
/* rba_EthUdp_VerifyUdpCksum_IPv6() This is a helper function called from rba_EthUdp_RxIndication_IPv6, which       */
/*                          verifies the checksum of the received UDP datagram.                                     */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* PseudoHdr_pcst    		Pointer to pseudo structure provided by IPv4. Contains destination IP, source IP        */
/*                          and IPv4 header length                                                                  */
/* RxData_pcu8             	Pointer to the received UDP datagram                                                    */
/* UdpBodyLen_u16           UDP datagram body length (not including the UDP header)                                 */
/*                                                                                                                  */
/* Return type :            Std_ReturnType                                                                          */
/*                          - E_OK, if checksum is correct                                                          */
/*                          - E_NOT_OK, if checksum is wrong or it is not set (UDP checksum is mandatory for IPv6)  */
/*                                                                                                                  */
/* Note :   UDP handles the checksum validation only for IPv6 Rx frames (due to UDP protocol specific processing for*/
/*          IPv6). The checksum validation for IPv6 Tx is handled in the IPv6 layer for better performance.         */
/********************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHUDP_CODE ) rba_EthUdp_VerifyUdpCksum_IPv6(
                                                    P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )    PseudoHdr_pcst,
                                                    P2CONST( uint8, AUTOMATIC, AUTOMATIC )                	RxData_pcu8,
                                                    VAR( uint16, AUTOMATIC )                                UdpBodyLen_u16 )
{
	VAR( uint16, AUTOMATIC )            lUdpChksum_u16;
	VAR( uint16, AUTOMATIC )            lTPLayerChksum_u16;
	VAR( Std_ReturnType, AUTOMATIC )    lRetVal_en = E_NOT_OK;

	/* Read the Udp checksum value in the received buffer */
	TcpIp_ReadU16( &(RxData_pcu8[RBA_ETHUDP_UDPCHKSUM_UB]), &lTPLayerChksum_u16 );

	/* The Udp checksum validation is implemented according to RFC 2460 specifications:
	 * "Unlike IPv4, when UDP packets are originated by an IPv6 node, the UDP checksum is not optional."
	 * "IPv6 receivers must discard UDP packets containing a zero checksum, and should log the error." */
	if( 0 != lTPLayerChksum_u16 )
	{
	    /* MR12 DIR 1.1 VIOLATION: The input parameter of TcpIp_OnesComplChkSum() is declared as (void*) for faster implmentation of checksum calculation. Low Risk */
		lRetVal_en = TcpIp_OnesComplChkSum( RxData_pcu8, PseudoHdr_pcst, UdpBodyLen_u16, &lUdpChksum_u16 );
		if( ( lRetVal_en == E_OK ) && ( 0 != lUdpChksum_u16 ) )
		{
			lRetVal_en = E_NOT_OK;
		}
	}
	else
	{
		/* The rba_EthUdp_RxIndication() API has no return value. Therefore report at least to DET that the checksum is invalid (if DET is enabled). */
	    RBA_ETHUDP_DET_REPORT_ERROR_TRUE_RET_VALUE( RBA_ETHUDP_E_RX_INDICATION_API_ID, RBA_ETHUDP_E_ZERO_CHECKSUM_IPV6, E_NOT_OK );
	}

	return lRetVal_en;
}
#endif  /* #if ( RBA_ETHUDP_SW_CHKSUM_RX_IPV6 == STD_ON ) */


#define RBA_ETHUDP_STOP_SEC_CODE
#include "rba_EthUdp_MemMap.h"

#endif /* #if ( defined(TCPIP_UDP_ENABLED) && ( TCPIP_UDP_ENABLED == STD_ON ) ) */
