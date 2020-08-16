

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "SoAd.h"
#include "SoAd_Cbk.h" /* Required for SoAd call-back functions */

#include "TcpIp_Prv.h"

#include "rba_EthTcp.h"
#include "rba_EthTcp_Cbk.h"
#include "rba_EthTcp_Prv.h"

#if (!defined(SOAD_AR_RELEASE_MAJOR_VERSION) || (SOAD_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - TcpIp and SoAd"
#endif

#if (!defined(SOAD_AR_RELEASE_MINOR_VERSION) || (SOAD_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - TcpIp and SoAd"
#endif

#include "EthComm.h"

/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"
static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationListen       ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationSynSent      ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );

static FUNC( boolean, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationSynRcvd_AckProcessing ( VAR( TcpIp_SocketIdType, AUTOMATIC )                          TcpDynSockTblIdx_uo,
                                                                                       P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )  TcpDynSockTbl_pst );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationSynRcvd      ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )      RxData_pu8 );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationEstablished  ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )      RxData_pu8 );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationFinWait1     ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )      RxData_pu8 );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationFinWait2     ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )      RxData_pu8 );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationCloseWait    ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationClosing      ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationLastAck      ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_RxIndicationTimeWait     ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );
#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


/*
 ***************************************************************************************************
 * Interface functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndication	- By this API, the rba_EthTcp module gets an indication and the data of a received frame			**/
/**																																**/
/** Parameters (in):																											**/
/** PseudoHdr_cpst 			- Contains SrcIP and DestIp addresses																**/
/** LocalAddrId_u8 			- LocalAddrId on which the frame is received														**/
/** RxData_pu8 				- Pointer to the start of the Tcp frame																**/
/** LenByte_u16				- Total length of Tcp frame																			**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:			None																								**/
/**																																**/
/*********************************************************************************************************************************/
/* HIS METRIC v(G) and CALLS VIOLATION IN rba_EthTcp_RxIndication: For design purpose, the function cannot be further splitted (function is divided by connection state) */
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndication( 	P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )	PseudoHdr_cpst,
														VAR( TcpIp_LocalAddrIdType, AUTOMATIC )					LocalAddrId_u8,
														P2VAR( uint8, AUTOMATIC, AUTOMATIC )					RxData_pu8,
														VAR( uint16, AUTOMATIC ) 								LenByte_u16 )
{
	/* Declare local variables */
	VAR( TcpIp_SocketIdType, AUTOMATIC )								lTcpDynSockTblIdx_uo;
	VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_en;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                                           lDetErrorFlag_b;
#endif

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Check for DET errors */
    /* Report DET if rba_EthTcp module is uninitialized */
    rba_EthTcp_CheckDetError( ( rba_EthTcp_InitFlag_b == FALSE ), RBA_ETHTCP_E_RXINDICATION, RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if local address ID is invalid */
    rba_EthTcp_CheckDetError( ( LocalAddrId_u8 >= TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ), RBA_ETHTCP_E_RXINDICATION, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if PseudoHdr_cpst is NULL pointer */
    rba_EthTcp_CheckDetError( ( PseudoHdr_cpst == NULL_PTR ), RBA_ETHTCP_E_RXINDICATION, RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );
    /* Report DET if the local or remote IP address is IPADDR_ANY */
    rba_EthTcp_CheckDetError( ( ( PseudoHdr_cpst != NULL_PTR ) &&
                                ( RBA_ETHTCP_CHECK_PSEUDOHDR_IPADDR_ANY( PseudoHdr_cpst->IpDomainType_t, &(PseudoHdr_cpst->LocalIpAddr_un) ) ||
                                  RBA_ETHTCP_CHECK_PSEUDOHDR_IPADDR_ANY( PseudoHdr_cpst->IpDomainType_t, &(PseudoHdr_cpst->RemoteIpAddr_un) ) ) ),
                              RBA_ETHTCP_E_RXINDICATION, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if the ProtocolType is not TCP */
    rba_EthTcp_CheckDetError( ( ( PseudoHdr_cpst != NULL_PTR) && ( PseudoHdr_cpst->ProtoType_en != TCPIP_IPPROTO_TCP ) ),
                              RBA_ETHTCP_E_RXINDICATION, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if RxData_pu8 is NULL pointer */
    rba_EthTcp_CheckDetError( ( RxData_pu8 == NULL_PTR ), RBA_ETHTCP_E_RXINDICATION, RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* ------------------------------------------------- */
        /* Check frame validity and copy info in the socket  */
        /* ------------------------------------------------- */
        lRetVal_en = rba_EthTcp_CheckFrameAndCopyToSocket(	LocalAddrId_u8,
                                                            PseudoHdr_cpst,
                                                            RxData_pu8,
                                                            LenByte_u16,
                                                            &lTcpDynSockTblIdx_uo );

        if ( lRetVal_en == E_OK )
        {
            /* ------------------------------------------------- */
            /* Process by socket state                           */
            /* ------------------------------------------------- */
            switch ( rba_EthTcp_DynSockTbl_ast[lTcpDynSockTblIdx_uo].State_en )
            {
                /* ------------------------------------------------- */
                /* Process received frame for LISTEN state           */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_LISTEN_E:
                {
                    rba_EthTcp_RxIndicationListen( lTcpDynSockTblIdx_uo );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for SYN_SENT state 		 */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_SYN_SENT_E:
                {
                    rba_EthTcp_RxIndicationSynSent( lTcpDynSockTblIdx_uo );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for SYN_RCVD state 		 */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_SYN_RCVD_E:
                {
                    rba_EthTcp_RxIndicationSynRcvd( lTcpDynSockTblIdx_uo,
                                                    RxData_pu8 );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for ESTABLISHED state 	 */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_ESTABLISHED_E:
                {
                    rba_EthTcp_RxIndicationEstablished( lTcpDynSockTblIdx_uo,
                                                        RxData_pu8 );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for FIN_WAIT_1 state 	 	 */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_FIN_WAIT_1_E:
                {
                    rba_EthTcp_RxIndicationFinWait1(    lTcpDynSockTblIdx_uo,
                                                        RxData_pu8 );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for FIN_WAIT_2 state 	 	 */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_FIN_WAIT_2_E:
                {
                    rba_EthTcp_RxIndicationFinWait2(    lTcpDynSockTblIdx_uo,
                                                        RxData_pu8 );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for CLOSE_WAIT state       */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_CLOSE_WAIT_E:
                {
                    rba_EthTcp_RxIndicationCloseWait( lTcpDynSockTblIdx_uo );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for CLOSING state 	 	 */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_CLOSING_E:
                {
                    rba_EthTcp_RxIndicationClosing( lTcpDynSockTblIdx_uo );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for LAST_ACK state         */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_LAST_ACK_E:
                {
                    rba_EthTcp_RxIndicationLastAck( lTcpDynSockTblIdx_uo );
                }
                break;

                /* ------------------------------------------------- */
                /* Process received frame for TIME_WAIT state 	 	 */
                /* ------------------------------------------------- */
                case RBA_ETHTCP_CONN_TIME_WAIT_E:
                default:
                {
                    rba_EthTcp_RxIndicationTimeWait( lTcpDynSockTblIdx_uo );
                }
                break;
            }
        }
	}

	return;
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationListen           - Process the reception of a valid frame in LISTEN state                            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationListen ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Check the SYN bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
        /* Call generator for Initial Sequence Number selection */
        lTcpDynSockTbl_pst->IniSndSeqNum_u32 = rba_EthTcp_GenerateIsn( TcpDynSockTblIdx_uo );

        /* Set the sequence number and acknowledgment number of the next frame to be sent */
        rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->IniSndSeqNum_u32 );
        rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + 1U) );

        /* Send a SYN ACK in the next MainFunction (after that, we will go to the SYN RCVD state) */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_SYN_ACK_E );
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationSynSent          - Process the reception of a valid frame in SYN_SENT state                          **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationSynSent ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        /* Dynamic RETX management */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
        /* Calculate RTO if RTT measurement was in progress for our SYN transmission */
        rba_EthTcp_CalculateRto( TcpDynSockTblIdx_uo );
#endif

        /* Set the unacked sequence number to the received acknowledgment number */
        lTcpDynSockTbl_pst->UnAckedSeqNum_u32 = lTcpDynSockTbl_pst->RcvdAckNum_u32;
    }

    /* ----------------------------- */
    /* Check the SYN bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
        /* If the unacked sequence number > ISS (our SYN has been ACKed) */
        if( lTcpDynSockTbl_pst->UnAckedSeqNum_u32 > lTcpDynSockTbl_pst->IniSndSeqNum_u32 )
        {
            /* Set the acknowledgment number of the next frame to be sent */
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + 1U) );

            /* Send an ACK in the next MainFunction (after that, we will go to the ESTABLISHED state) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_SYN_ACK_E );
        }

        /* If we are in the simultaneous opening case */
        else
        {
            /* Set the sequence number and acknowledgment number of the next frame to be sent */
            rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->IniSndSeqNum_u32) );
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + 1U) );

            /* Send a SYN ACK in the next MainFunction (after that, we will go to the SYN RCVD state) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_SYN_ACK_E );
        }
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationSynRcvd_AckProcessing - Helper function called by rba_EthTcp_RxIndicationSynRcvd which processes the **/
/**                                                reception of a valid frame in SYN_RCVD state, only when the ACK bit is set.  **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** TcpDynSockTbl_pst                       - Pointer to Tcp dynamic socket table entry                                         **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return type:                            boolean                                                                             **/
/** Return value:                           - TRUE, if the processing has been performed successfully and the caller function   **/
/**                                                 can continue.                                                               **/
/**                                         - FALSE, if errors have occured and the caller function must interrupt further      **/
/**                                                  processing.                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( boolean, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationSynRcvd_AckProcessing ( VAR( TcpIp_SocketIdType, AUTOMATIC )                          TcpDynSockTblIdx_uo,
                                                                                       P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )  TcpDynSockTbl_pst )
{
    P2VAR( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   lRemoteAddr_pst;
    #if ( TCPIP_IPV4_ENABLED == STD_ON )
    VAR( TcpIp_SockAddrInetType, AUTOMATIC )            lRemoteAddrInet_st;
    #endif
    #if ( TCPIP_IPV6_ENABLED == STD_ON )
	VAR( TcpIp_SockAddrInet6Type, AUTOMATIC )           lRemoteAddrInet6_st;
    VAR( uint8, AUTOMATIC )                             lLoopIdx_u8;
    #endif
    VAR( Std_ReturnType, AUTOMATIC )                    lRetVal_en = E_NOT_OK;  /* Initialize to pessimistic value; will be overwritten by the internal function calls */
    VAR( boolean, AUTOMATIC )                           lContinueProcessing_b = TRUE; /* Start optimistic and assume successful processing */

    /* Dynamic RETX management */
    #if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
    /* Calculate RTO if RTT measurement was in progress for our SYN ACK transmission */
    rba_EthTcp_CalculateRto( TcpDynSockTblIdx_uo );
    #endif

    /* Set the unacked sequence number to the received acknowledgment number */
    TcpDynSockTbl_pst->UnAckedSeqNum_u32 = TcpDynSockTbl_pst->RcvdAckNum_u32;

    /* ------------------------------------ */
    /* Tcp connected / accepted callback    */
    /* ------------------------------------ */

    /* If the connection has been initiated with an active open (previous state is SYN SENT, corresponds to simultaneous open) */
    if( TcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_SYN_SENT_E )
    {
        /* Call SoAd API to indicate that the connection is now established */
        SoAd_TcpConnected( TcpDynSockTblIdx_uo );
    }

    /* If the connection has been initiated with a passive open (Normal case or reopening from TIME_WAIT) */
    else if ( (TcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_LISTEN_E)        ||
         (TcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_TIME_WAIT_E) )
    {
        /* Create remote address structure */
        switch( TcpDynSockTbl_pst->DomainType_u32 )
        {
            #if ( TCPIP_IPV4_ENABLED == STD_ON )
            case TCPIP_AF_INET:
            {
                lRemoteAddrInet_st.domain   = TCPIP_AF_INET;
                lRemoteAddrInet_st.port     = TcpDynSockTbl_pst->RemotePort_u16;
                lRemoteAddrInet_st.addr[0]  = TcpDynSockTbl_pst->RemoteIPAddr_un.IPv4Addr_u32;
				/* MR12 RULE 11.3 VIOLATION: Cast is required to respect the type definition of the calling function. */
                lRemoteAddr_pst             = ( (TcpIp_SockAddrType*) &lRemoteAddrInet_st );
            }
            break;
            #endif

            #if ( TCPIP_IPV6_ENABLED == STD_ON )
            case TCPIP_AF_INET6:
            {
                lRemoteAddrInet6_st.domain  = TCPIP_AF_INET6;
                lRemoteAddrInet6_st.port    = TcpDynSockTbl_pst->RemotePort_u16;
                for(lLoopIdx_u8 = 0; lLoopIdx_u8 < 4; lLoopIdx_u8++)
                {
                    lRemoteAddrInet6_st.addr[lLoopIdx_u8] = TcpDynSockTbl_pst->RemoteIPAddr_un.IPv6Addr_au32[lLoopIdx_u8];
                }
				/* MR12 RULE 11.3 VIOLATION: Cast is required to respect the type definition of the calling function. */
                lRemoteAddr_pst             = ( (TcpIp_SockAddrType*) &lRemoteAddrInet6_st );
            }
            break;
            #endif

            default:
            {
                /* If execution reaches here, then the IP support for the specified domain is not enabled; set return value to E_NOT_OK. */
                lContinueProcessing_b = FALSE;
                lRemoteAddr_pst = NULL_PTR;
            }
            break;
        }

        if( lContinueProcessing_b != FALSE )
        {
            /* Call the SoAd API to indicate that a new client is accepted */
            /* MR12 RULE 11.3 VIOLATION: Casting to different object pointer type */
            lRetVal_en = SoAd_TcpAccepted(  TcpDynSockTbl_pst->ListenTcpSockIdx_uo,
                                            TcpDynSockTblIdx_uo,
                                            lRemoteAddr_pst );
		#if (ENABLE_TCP_SERVER != 0U)
            lRetVal_en = Ethernet_TcpServer_Accepted(TcpDynSockTbl_pst->ListenTcpSockIdx_uo, TcpDynSockTblIdx_uo, lRemoteAddr_pst);
		#else
            lRetVal_en = E_OK;
		#endif
            /* If SoAd_TcpAccepted returned an error */
            if ( lRetVal_en == E_NOT_OK )
            {
                /* Send a RST-ACK in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

                /* No further processing should be done */
                lContinueProcessing_b = FALSE;
            }
        }
        else
        {
            /* Nothing to do. */
        }
    }

    /* If the connection has been initiated with a passive open (reopening from LAST_ACK) */
    else
    {
        /* No callback to SoAd is needed */
    }

    /* ----------------------------- */
    /* Change state                  */
    /* ----------------------------- */

    if(lContinueProcessing_b != FALSE )
    {
        /* Change the connection state of the socket to ESTABLISHED */
        rba_EthTcp_SetConnectionState( TcpDynSockTblIdx_uo, RBA_ETHTCP_CONN_ESTABLISHED_E );
    }

    return lContinueProcessing_b;
}



/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationSynRcvd          - Process the reception of a valid frame in SYN_RCVD state                          **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxData_pu8                              - Pointer to the start of the Tcp frame                                             **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationSynRcvd (   VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )        RxData_pu8 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( boolean, AUTOMATIC )                                           lContinueProcessing_b;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Set the continue processing flag to TRUE */
    lContinueProcessing_b = TRUE;

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        lContinueProcessing_b = rba_EthTcp_RxIndicationSynRcvd_AckProcessing( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst );
    }

    /* ----------------------------- */
    /* Check if any data is present  */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdDataLen_u16 > 0U)        &&
         (lContinueProcessing_b != FALSE) )
    {
    #if ( RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED == STD_OFF )
        /* Process newly received data */
        rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                            (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                            lTcpDynSockTbl_pst->RcvdDataLen_u16 );
    #else
        /* If the Close API has not been called yet */
        if( lTcpDynSockTbl_pst->PostponeFin_b != TRUE )
        {
            /* Process newly received data */
            rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                lTcpDynSockTbl_pst->RcvdDataLen_u16 );
        }
        else
        {
            /* The upper layer shall not be notified about the received data as the Close API has been called */
            /* We should send a reset to indicate to the remote that data are lost  */

            /* Send a RST-ACK in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

            /* No further processing should be done */
            lContinueProcessing_b = FALSE;
        }
    #endif
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( ((lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK)  &&
         (lContinueProcessing_b != FALSE) )
    {
        /* Handle the FIN only if all the data of the frame have been processed by SoAd */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
            /* Set the acknowledgment number of the next frame to be sent */
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

            /* Send ACK frame in the next MainFunction (after that, we will go to the CLOSE WAIT state) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );
        }
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationEstablished      - Process the reception of a valid frame in ESTABLISHED state                       **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxData_pu8                              - Pointer to the start of the Tcp frame                                             **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationEstablished (   VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )        RxData_pu8 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( rba_EthTcp_AckVal_ten, AUTOMATIC )                             lValidRcvdAckNum_en;
    VAR( uint16, AUTOMATIC )                                            lAckedLen_u16;
    VAR( boolean, AUTOMATIC )                                           lContinueProcessing_b;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Set the continue processing flag to TRUE */
    lContinueProcessing_b = TRUE;

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        /* Check if the received acknowledgment number is already received or not */
        /* (this function is used to check if ack number is new, not an old duplicate) */
        lValidRcvdAckNum_en = rba_EthTcp_RcvdAckNumValidity( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->RcvdAckNum_u32 );

        /* ----------------------------- */
        /* Complete or Partial ACK       */
        /* ----------------------------- */

        /* If the received acknowledgment number has not been already received */
        if ( lValidRcvdAckNum_en == RBA_ETHTCP_ACK_NEW_E )
        {
            /* Dynamic RETX management */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
            /* Calculate RTO if RTT measurement was in progress for our DATA / ZWP transmission */
            rba_EthTcp_CalculateRto( TcpDynSockTblIdx_uo );
#endif

            /* Compute the acknowledged data length */
            lAckedLen_u16 = (uint16)(lTcpDynSockTbl_pst->RcvdAckNum_u32 - lTcpDynSockTbl_pst->UnAckedSeqNum_u32);

            /* Execute the processing of the data acknowledgment */
            rba_EthTcp_RxDataAcknowledgment( TcpDynSockTblIdx_uo, lAckedLen_u16 );

            /* Set the unacked sequence number to the received acknowledgment number */
            lTcpDynSockTbl_pst->UnAckedSeqNum_u32 = lTcpDynSockTbl_pst->RcvdAckNum_u32;
        }

        /* ----------------------------- */
        /* Duplicate ACK                 */
        /* ----------------------------- */

        /* If the acknowledgment number has been already received (duplicate ACK) */
        else
        {
            /* Execute the processing of the data acknowledgment */
            rba_EthTcp_RxDataAcknowledgment( TcpDynSockTblIdx_uo, 0U );
        }
    }

    /* ----------------------------- */
    /* Check if any data is present  */
    /* ----------------------------- */
    if ( lTcpDynSockTbl_pst->RcvdDataLen_u16 > 0U )
    {
        /* If FIN has not been received yet */
        /* (the data can be handled only if we have not received the FIN from the remote) */
        if( lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E )
        {
            /* If the data are from a RST frame */
            if( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
            {
#if ( RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED == STD_OFF )
                /* Process newly received data */
                rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                    (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                    lTcpDynSockTbl_pst->RcvdDataLen_u16 );
#else
                /* If the Close API has not been called yet */
                if( (lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_FIN_ACK_E) && (lTcpDynSockTbl_pst->PostponeFin_b != TRUE) )
                {
                    /* Process newly received data */
                    rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                        (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                        lTcpDynSockTbl_pst->RcvdDataLen_u16 );
                }
#endif

                /* Reset the socket */
                rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );

                /* No further processing should be done */
                lContinueProcessing_b = FALSE;
            }

            /* If the data are from a normal data frame */
            else
            {
#if ( RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED == STD_OFF )
                /* Process newly received data */
                rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                    (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                    lTcpDynSockTbl_pst->RcvdDataLen_u16 );
#else
                /* If the Close API has not been called yet */
                if( (lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_FIN_ACK_E) && (lTcpDynSockTbl_pst->PostponeFin_b != TRUE) )
                {
                    /* Process newly received data */
                    rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                        (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                        lTcpDynSockTbl_pst->RcvdDataLen_u16 );
                }
                else
                {
                    /* The upper layer shall not be notified about the received data as the Close API has been called */
                    /* We should send a reset to indicate to the remote that data are lost  */

                    /* Send a RST-ACK in the next MainFunction */
                    (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

                    /* No further processing should be done */
                    lContinueProcessing_b = FALSE;
                }
#endif
            }
        }
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( ((lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK)  &&
          (lContinueProcessing_b != FALSE))
    {
        /* Handle the FIN only if all the data of the frame have been processed by SoAd */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
            /* Set the acknowledgment number of the next frame to be sent */
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

            /* Send ACK frame in the next MainFunction (after that, we will go to the CLOSE WAIT state) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );
        }
    }
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationFinWait1         - Process the reception of a valid frame in FIN_WAIT_1 state                        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxData_pu8                              - Pointer to the start of the Tcp frame                                             **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationFinWait1 (  VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )        RxData_pu8 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( boolean, AUTOMATIC )                                           lContinueProcessing_b;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Set the continue processing flag to TRUE */
    lContinueProcessing_b = TRUE;

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
        /* Restart the Keep Alive timer (if it is running) */
        /* (the connection has to remain open if ACK is received) */
        rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
#endif

        /* Check if the received ACK number acknowledge our FIN ACK */
        if( lTcpDynSockTbl_pst->RcvdAckNum_u32 == lTcpDynSockTbl_pst->SndSeqNum_u32 )
        {
            /* Update the unacked sequence number value */
            lTcpDynSockTbl_pst->UnAckedSeqNum_u32 = lTcpDynSockTbl_pst->RcvdAckNum_u32;

            /* Change the connection state of the socket to FIN WAIT 2 */
            rba_EthTcp_SetConnectionState( TcpDynSockTblIdx_uo, RBA_ETHTCP_CONN_FIN_WAIT_2_E );
        }
    }

    /* ----------------------------- */
    /* Check if any data is present  */
    /* ----------------------------- */
    if ( lTcpDynSockTbl_pst->RcvdDataLen_u16 > 0U )
    {
        /* If FIN has not been received yet */
        /* (the data can be handled only if we have not received the FIN from the remote) */
        if( lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E )
        {
            /* If the data are from a RST frame */
            if( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
            {
#if ( RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED == STD_OFF )
                /* Process newly received data */
                rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                    (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                    lTcpDynSockTbl_pst->RcvdDataLen_u16 );
#endif
                /* Reset the socket */
                rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );

                /* No further processing should be done */
                lContinueProcessing_b = FALSE;
            }

            /* If the data are from a normal data frame */
            else
            {

#if ( RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED == STD_OFF )
                /* Process newly received data */
                rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                    (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                    lTcpDynSockTbl_pst->RcvdDataLen_u16 );
#else
                /* The upper layer shall not be notified about the received data as the Close API has been called */
                /* We should send a reset to indicate to the remote that data are lost  */

                /* Send a RST-ACK in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

                /* No further processing should be done */
                lContinueProcessing_b = FALSE;
#endif
            }
        }
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( ((lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK)  &&
         (lContinueProcessing_b != FALSE))
    {
        /* Handle the FIN only if all the data of the frame have been processed by SoAd */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
            /* Set the acknowledgment number of the next frame to be sent */
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

            /* Send ACK frame in the next MainFunction (after that, we will go to the CLOSING or TIME WAIT state, it depends if we are in simultaneous closing or not) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );

        }
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationFinWait2         - Process the reception of a valid frame in FIN_WAIT_2 state                        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxData_pu8                              - Pointer to the start of the Tcp frame                                             **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationFinWait2 (  VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )        RxData_pu8 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( boolean, AUTOMATIC )                                           lContinueProcessing_b;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Set the continue processing flag to TRUE */
    lContinueProcessing_b = TRUE;

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
        /* Restart the Keep Alive timer (if it is running) */
        /* (the connection has to remain open if ACK is received) */
        rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
#endif
    }

    /* ----------------------------- */
    /* Check if any data is present  */
    /* ----------------------------- */
    if ( lTcpDynSockTbl_pst->RcvdDataLen_u16 > 0U )
    {
        /* If FIN has not been received yet */
        /* (the data can be handled only if we have not received the FIN from the remote) */
        if( lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E )
        {
            /* If the data are from a RST frame */
            if( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
            {
#if ( RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED == STD_OFF )
                /* Process newly received data */
                rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                    (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                    lTcpDynSockTbl_pst->RcvdDataLen_u16 );
#endif
                /* Reset the socket */
                rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );

                /* No further processing should be done */
                lContinueProcessing_b = FALSE;
            }

            /* If the data are from a normal data frame */
            else
            {
#if ( RBA_ETHTCP_HALFDUPLX_CLOSE_ENABLED == STD_OFF )
                /* Process newly received data */
                rba_EthTcp_RxData(  TcpDynSockTblIdx_uo,
                                    (RxData_pu8 + lTcpDynSockTbl_pst->RcvdDataOffset_u16),
                                    lTcpDynSockTbl_pst->RcvdDataLen_u16 );
#else
                /* The upper layer shall not be notified about the received data as the Close API has been called */
                /* We should send a reset to indicate to the remote that data are lost  */

                /* Send a RST-ACK in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

                /* No further processing should be done */
                lContinueProcessing_b = FALSE;
#endif
            }
        }
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( ((lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK)  &&
         (lContinueProcessing_b != FALSE) )
    {
        /* Handle the FIN only if all the data of the frame have been processed by SoAd */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
            /* Set the acknowledgment number of the next frame to be sent */
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

            /* Send ACK frame in the next MainFunction (after that, we will go to the TIME WAIT state) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );
        }
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationCloseWait        - Process the reception of a valid frame in CLOSE_WAIT state                        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationCloseWait ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( rba_EthTcp_AckVal_ten, AUTOMATIC )                             lValidRcvdAckNum_en;
    VAR( uint16, AUTOMATIC )                                            lAckedLen_u16;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        /* Check if the received acknowledgment number is already received or not */
        /* (this function is used to check if ack number is new, not an old duplicate) */
        lValidRcvdAckNum_en = rba_EthTcp_RcvdAckNumValidity( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->RcvdAckNum_u32 );

        /* ----------------------------- */
        /* Complete or Partial ACK       */
        /* ----------------------------- */

        /* If the received acknowledgment number has not been already received */
        if ( lValidRcvdAckNum_en == RBA_ETHTCP_ACK_NEW_E )
        {
            /* Dynamic RETX management */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
            /* Calculate RTO if RTT measurement was in progress for our DATA / ZWP transmission */
            rba_EthTcp_CalculateRto( TcpDynSockTblIdx_uo );
#endif

            /* Compute the acknowledged data length */
            lAckedLen_u16 = (uint16)(lTcpDynSockTbl_pst->RcvdAckNum_u32 - lTcpDynSockTbl_pst->UnAckedSeqNum_u32);

            /* Execute the processing of the data acknowledgment */
            rba_EthTcp_RxDataAcknowledgment( TcpDynSockTblIdx_uo, lAckedLen_u16 );

            /* Set the unacked sequence number to the received acknowledgment number */
            lTcpDynSockTbl_pst->UnAckedSeqNum_u32 = lTcpDynSockTbl_pst->RcvdAckNum_u32;
        }

        /* ----------------------------- */
        /* Duplicate ACK                 */
        /* ----------------------------- */

        /* If the acknowledgment number has been already received (duplicate ACK) */
        else
        {
            /* Execute the processing of the data acknowledgment */
            rba_EthTcp_RxDataAcknowledgment( TcpDynSockTblIdx_uo, 0U );
        }
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK )
    {
		/* Handle the FIN only if there is no unhandled data in the segment */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
			/* Set the acknowledgment number of the next frame to be sent */
			rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

			/* Send ACK frame in the next MainFunction (after that, we will go to the CLOSE WAIT state) */
			(void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );
		}
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationClosing          - Process the reception of a valid frame in CLOSING state                           **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationClosing ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
        /* Restart the Keep Alive timer (if it is running) */
        /* (the connection has to remain open if ACK is received) */
        rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
#endif

        /* Check if the received ACK number acknowledge our FIN ACK */
        if( lTcpDynSockTbl_pst->RcvdAckNum_u32 == lTcpDynSockTbl_pst->SndSeqNum_u32 )
        {
            /* Update the unacked sequence number value */
            lTcpDynSockTbl_pst->UnAckedSeqNum_u32 = lTcpDynSockTbl_pst->RcvdAckNum_u32 ;

            /* Enter TIME WAIT state */
            rba_EthTcp_SetConnectionState( TcpDynSockTblIdx_uo, RBA_ETHTCP_CONN_TIME_WAIT_E );
        }
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK )
    {
        /* Handle the FIN only if there is no unhandled data in the segment */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
            /* Set the acknowledgment number of the next frame to be sent */
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

            /* Send ACK frame in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );
        }
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationLastAck          - Process the reception of a valid frame in LAST_ACK state                          **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationLastAck ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( uint8, AUTOMATIC )                                             lRetry_u8;
    VAR( boolean, AUTOMATIC )                                           lContinueProcessing_b;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Set the continue processing flag to TRUE */
    lContinueProcessing_b = TRUE;

    /* ----------------------------- */
    /* Check the SYN bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
        /* A SYN received in LAST ACK state is used for fast reopening */

        /* Loop to find an Initial sequence number greater than the largest sequence number used on the previous connection */
        /* (see conditions to allow fast reopening - RFC1122 p88) */
        for( lRetry_u8 = 0U; lRetry_u8 < 5U; lRetry_u8++ )
        {
            /* Call generator for Initial Sequence Number selection */
            lTcpDynSockTbl_pst->IniSndSeqNum_u32 = rba_EthTcp_GenerateIsn( TcpDynSockTblIdx_uo );

            /* If generated number is valid */
            if( lTcpDynSockTbl_pst->IniSndSeqNum_u32 >= lTcpDynSockTbl_pst->SndSeqNum_u32 )
            {
                break;
            }
        }

        /* If a valid ISS cannot be found randomly */
        if(lRetry_u8 == 5U)
        {
            /* Choose an ISS equal to the sequence number following the largest sequence number used on the previous connection */
            lTcpDynSockTbl_pst->IniSndSeqNum_u32 = lTcpDynSockTbl_pst->SndSeqNum_u32;
        }

        /* Set the sequence number and acknowledgment number of the next frame to be sent */
        rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->IniSndSeqNum_u32 );
        rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + 1U) );

        /* Send a SYN ACK in the next MainFunction (after that, we will go to the SYN RCVD state) */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_SYN_ACK_E );
    }

    /* ----------------------------- */
    /* Check the ACK bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
        /* Restart the Keep Alive timer (if it is running) */
        /* (the connection has to remain open if ACK is received) */
        rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
#endif

        /* Check if the received ACK number acknowledge our FIN ACK */
        if( lTcpDynSockTbl_pst->RcvdAckNum_u32 == lTcpDynSockTbl_pst->SndSeqNum_u32 )
        {
            /* Connection is finished, we have to return to the CLOSED state */
            rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_CLOSED );

            /* No further processing should be done */
            lContinueProcessing_b = FALSE;
        }
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( ((lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK)  &&
         (lContinueProcessing_b != FALSE) )
    {
		/* Handle the FIN only if there is no unhandled data in the segment */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
			/* Set the acknowledgment number of the next frame to be sent */
			rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

			/* Send ACK frame in the next MainFunction */
			(void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );
		}
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RxIndicationTimeWait         - Process the reception of a valid frame in TIME_WAIT state                         **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxIndicationTimeWait ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( uint8, AUTOMATIC )                                             lRetry_u8;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Check the SYN bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
        /* A SYN received in TIME WAIT state is used for fast reopening */

        /* Loop to find an Initial sequence number greater than the largest sequence number used on the previous connection */
        /* (see conditions to allow fast reopening - RFC1122 p88) */
        for( lRetry_u8 = 0U; lRetry_u8 < 5U; lRetry_u8++ )
        {
            /* Call generator for Initial Sequence Number selection */
            lTcpDynSockTbl_pst->IniSndSeqNum_u32 = rba_EthTcp_GenerateIsn( TcpDynSockTblIdx_uo );

            /* If generated number is valid */
            if( lTcpDynSockTbl_pst->IniSndSeqNum_u32 >= lTcpDynSockTbl_pst->SndSeqNum_u32 )
            {
                break;
            }
        }

        /* If a valid ISS cannot be found randomly */
        if(lRetry_u8 == 5U)
        {
            /* Choose an ISS equal to the sequence number following the largest sequence number used on the previous connection */
            lTcpDynSockTbl_pst->IniSndSeqNum_u32 = lTcpDynSockTbl_pst->SndSeqNum_u32;
        }

        /* Set the sequence number and acknowledgment number of the next frame to be sent */
        rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->IniSndSeqNum_u32 );
        rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + 1U) );

        /* Send a SYN ACK in the next MainFunction (after that, we will go to the SYN RCVD state) */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_SYN_ACK_E );
    }

    /* ----------------------------- */
    /* Check the FIN bit             */
    /* ----------------------------- */
    if ( (lTcpDynSockTbl_pst->RcvdHdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK )
    {
		/* Handle the FIN only if there is no unhandled data in the segment */
        /* (RFC793 p26 : FIN is considered to occur after the last actual data octet in a segment) */
        if( lTcpDynSockTbl_pst->SndAckNum_u32 == (lTcpDynSockTbl_pst->RcvdSeqNum_u32 + lTcpDynSockTbl_pst->RcvdDataLen_u16) )
        {
			/* Restart the 2*MSL timeout */
			rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_TIMEWAIT_E );

			/* Set the acknowledgment number of the next frame to be sent */
			rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (lTcpDynSockTbl_pst->SndAckNum_u32 + 1U) );

			/* Send ACK frame in the next MainFunction */
			(void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E );
		}
    }

    return;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */




















