

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "TcpIp_Prv.h"

#include "rba_EthTcp.h"
#include "rba_EthTcp_Prv.h"


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_GracefulClose        ( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo );

static FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_AbortClose           ( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo );

static FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_AbortRelatedChannels ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo );
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
/** rba_EthTcp_Close()  - By this API, the rba_EthTcp module is requested to close socket and release all related resources     **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpSockId_uo        - Tcp Socket id                                                                                         **/
/** Abort_b             - This parameter specifies if the connection should be terminated immediately by sending a RST segment  **/
/**                     or be terminated after performing a regular connection termination handshake                            **/
/**                                                                                                                             **/
/** Parameters (inout): None                                                                                                    **/
/**                                                                                                                             **/
/** Parameters (out):   None                                                                                                    **/
/**                                                                                                                             **/
/** Return value:       - Std_ReturnType                                                                                        **/
/**                         E_OK: The request has been accepted                                                                 **/
/**                         E_NOT_OK: The request has not been accepted                                                         **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_Close(   VAR( TcpIp_SocketIdType, AUTOMATIC )    TcpSockId_uo,
                                                            VAR( boolean, AUTOMATIC )               Abort_b )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                                           lDetErrorFlag_b;
#endif

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Check for DET errors */
    /* Report DET if rba_EthTcp module is uninitialized */
    rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_E_CLOSE , RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if TcpSockId_uo is invalid */
    rba_EthTcp_CheckDetError( (TcpSockId_uo >= TCPIP_TCPSOCKETMAX), RBA_ETHTCP_E_CLOSE, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Get Tcp dynamic table entry from Tcp socket index */
        lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpSockId_uo] ) );

        /* Process only when the socket is not CLOSED and not RESERVED */
        /* (UL does not have access to a socket which is CLOSED or RESERVED) */
        /* (see RFC793 p60, 62 : If the user does not have access to such a connection, return "error:  connection illegal for this process") */
        if( (lTcpDynSockTbl_pst->SockState_en != RBA_ETHTCP_SOCK_CLOSED_E) && (lTcpDynSockTbl_pst->SockState_en != RBA_ETHTCP_SOCK_RESERVED_E) )
        {
            /* ------------------------------------------ */
            /* Close related channels for LISTEN socket   */
            /* ------------------------------------------ */
            if( lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_LISTEN_E )
            {
                /* Abort all the channel sockets which are not yet established */
                rba_EthTcp_AbortRelatedChannels( TcpSockId_uo );
            }

            /* ------------------------------------------ */
            /* Graceful closing                           */
            /* ------------------------------------------ */
            if( Abort_b == FALSE )
            {
                /* Abort argument is set to FALSE so execute the Graceful closing */
                lFunctionRetVal_en = rba_EthTcp_GracefulClose( TcpSockId_uo );
            }

            /* ------------------------------------------ */
            /* Abort closing                              */
            /* ------------------------------------------ */
            else
            {
                /* Abort argument is set to TRUE so execute the Abort closing */
                rba_EthTcp_AbortClose( TcpSockId_uo );

                /* Set the return value of the function to E_OK */
                lFunctionRetVal_en = E_OK;
            }
        }
    }

    return lFunctionRetVal_en;
}

/*********************************************************************************************************************************/
/** rba_EthTcp_AbortByLocalAddrId() - By this API, Tcp is requested to terminate the connection using local address id          **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** LocalAddrId_u8                  - Local address Id                                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   None                                                                                        **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_AbortByLocalAddrId ( VAR( TcpIp_LocalAddrIdType, AUTOMATIC ) LocalAddrId_u8 )
{
    /* Local Variable declaration */
    VAR( TcpIp_SocketIdType, AUTOMATIC )                            lSocIdx_uo;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                                       lDetErrorFlag_b;
#endif

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Report DET if rba_EthTcp module is uninitialized */
    rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_ABORTBYLOCALADDRID, RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Loop through Tcp socket table and close all the sockets mapped to the requested local address */
        for(lSocIdx_uo = 0; lSocIdx_uo < TCPIP_TCPSOCKETMAX; lSocIdx_uo++)
        {
            /* Process only when local address id match and the socket is not CLOSED */
            if( ((LocalAddrId_u8 == rba_EthTcp_DynSockTbl_ast[lSocIdx_uo].LocalAddrId_u8) || (LocalAddrId_u8 == (uint8)TCPIP_LOCALADDRID_INVALID))  &&
                (rba_EthTcp_DynSockTbl_ast[lSocIdx_uo].SockState_en != RBA_ETHTCP_SOCK_CLOSED_E) )
            {
                /* ------------------------------------------ */
                /* Close related channels for LISTEN socket   */
                /* ------------------------------------------ */
                if( rba_EthTcp_DynSockTbl_ast[lSocIdx_uo].State_en == RBA_ETHTCP_CONN_LISTEN_E )
                {
                    /* Abort all the channel sockets which are not yet established */
                    rba_EthTcp_AbortRelatedChannels( lSocIdx_uo );
                }

                /* ------------------------------------------ */
                /* Abort closing                              */
                /* ------------------------------------------ */

                /* Execute Abort closing of the socket */
                rba_EthTcp_AbortClose( lSocIdx_uo );
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
/** rba_EthTcp_GracefulClose()      - This function execute the Graceful closing as described in RFC793 p60, 61                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                            **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   - Std_ReturnType                                                                            **/
/**                                     E_OK: The Graceful closing has been executed                                            **/
/**                                     E_NOT_OK: The Graceful closing has not been executed                                    **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_GracefulClose( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
    VAR( uint16, AUTOMATIC )                                        lRemainDataLen_u16;
    VAR( uint16, AUTOMATIC )                                        lUnackedDataLen_u16;
#endif

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    switch ( lTcpDynSockTbl_pst->State_en )
    {
        /* --------------------------------------------------- */
        /* Graceful close for CLOSED, LISTEN or SYN_SENT state */
        /* --------------------------------------------------- */
        case RBA_ETHTCP_CONN_CLOSED_E:
        case RBA_ETHTCP_CONN_LISTEN_E:
        case RBA_ETHTCP_CONN_SYN_SENT_E:
        {
            /* Reset the socket */
            rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_CLOSED );

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
        break;

        /* ------------------------------------------ */
        /* Graceful close in SYN_RCVD state           */
        /* ------------------------------------------ */
        case RBA_ETHTCP_CONN_SYN_RCVD_E:
        {
            /* Postponed our FIN ACK */
            /* (The FIN ACK will be sent after the ESTABLISHED state will be reached) */
            lTcpDynSockTbl_pst->PostponeFin_b = TRUE;

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
        break;

        /* ------------------------------------------------- */
        /* Graceful close in ESTABLISHED or CLOSE_WAIT state */
        /* ------------------------------------------------- */
        case RBA_ETHTCP_CONN_ESTABLISHED_E:
        case RBA_ETHTCP_CONN_CLOSE_WAIT_E:
        {
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
            /* Get how much data in Tcp Tx buffer is ready to be sent */
            lRemainDataLen_u16 = rba_EthTcp_GetTxBufSndLen( TcpDynSockTblIdx_uo );

            /* Get the length of unacked data in the Tcp Tx buffer */
            lUnackedDataLen_u16 = rba_EthTcp_GetTxBufUnackedLen( TcpDynSockTblIdx_uo );

            /* Check if the FIN ACK can be sent in the next MainFunction or need to be postponed after data */
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            if ( (lRemainDataLen_u16 > 0U) || (lUnackedDataLen_u16 > 0U) )
#else
            if ( (lRemainDataLen_u16 > 0U) )
#endif
            {
                /* Postponed our FIN ACK after data */
                /* (we have not finished to send our data or some of them are not acknowledged yet) */
                lTcpDynSockTbl_pst->PostponeFin_b = TRUE;
            }
            else
#endif
            {
                /* Send a FIN ACK in the next MainFunction */
                lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_FIN_ACK_E );

                /* If a frame with higher priority needs to be sent before */
                if( lRetVal_en == E_NOT_OK )
                {
                    /* Postpone our FIN ACK */
                    lTcpDynSockTbl_pst->PostponeFin_b = TRUE;
                }
            }

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
        break;

        /* ------------------------------------------ */
        /* Graceful close in other state              */
        /* ------------------------------------------ */
        default:
        {
            /* Tcp state doesn't allow a graceful closing so return E_NOT_OK */
            /* (see RFC793 p60,61 : FIN-WAIT-1, FIN-WAIT-2, CLOSING, LAST-ACK, TIME-WAIT STATE, respond with "error:  connection closing") */
        }
        break;
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_AbortClose()         - This function execute the Abort closing as described in RFC793 p62                        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                            **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   None                                                                                        **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_AbortClose( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    switch ( lTcpDynSockTbl_pst->State_en )
    {
        /* --------------------------------------------------------------------------------- */
        /* Abort close for SYN_RCVD, ESTABLISHED, FIN_WAIT_1, FIN_WAIT_2 or CLOSE_WAIT state */
        /* --------------------------------------------------------------------------------- */
        case RBA_ETHTCP_CONN_SYN_RCVD_E:
        case RBA_ETHTCP_CONN_ESTABLISHED_E:
        case RBA_ETHTCP_CONN_FIN_WAIT_1_E:
        case RBA_ETHTCP_CONN_FIN_WAIT_2_E:
        case RBA_ETHTCP_CONN_CLOSE_WAIT_E:
        {
            /* We are in a state where a reset need to be sent to abort the connection */

            /* Send a RST ACK */
            /* (We have to send RST ACK and not RST in order to be sure that the remote will be able to process the reset if its state is SYN_SENT state, see RFC793 p36, 37) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

            /* During an abort closing, we have to send directly the RST-ACK frame (we do not wait for the next MainFunction) */
            /* (For example, if Tcp_Close is called when the network goes offline (ETHSM_STATE_OFFLINE), the RST have to be sent immediately) */
            rba_EthTcp_SndFlag( TcpDynSockTblIdx_uo );

            /* If reset frame is not succesfully sent, forcefully close the socket */
            if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_RST_E)       ||
                (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_RST_ACK_E) )
            {
                /* Reset the socket */
                rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );
            }
        }
        break;

        /* ------------------------------------------ */
        /* Abort close for other states               */
        /* ------------------------------------------ */
        default:
        {
            /* Reset the socket */
            rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );
        }
        break;
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_AbortRelatedChannels()   - This function abort all the channel sockets which are currently in opening phase      **/
/**                                      (ESTABLISHED state has not been reached yet)                                           **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index of the listening socket whose channels need to be      **/
/**                                     aborted                                                                                 **/
/**                                                                                                                             **/
/** Parameters (inout):                 None                                                                                    **/
/**                                                                                                                             **/
/** Parameters (out):                   None                                                                                    **/
/**                                                                                                                             **/
/** Return value:                       None                                                                                    **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_AbortRelatedChannels( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    VAR( TcpIp_SocketIdType, AUTOMATIC )                                lIdxTcpSock_uo;

    /* ------------------------------------------ */
    /* Abort channels in LISTEN or SYN_RCVD state */
    /* ------------------------------------------ */

    /* Reset all the channel sockets in LISTEN or SYN_RCVD state which are related to the listening socket */
    for( lIdxTcpSock_uo=0U; lIdxTcpSock_uo < TCPIP_TCPSOCKETMAX; lIdxTcpSock_uo++ )
    {
        /* If the current Tcp socket is a channel of the listening Tcp socket and its state is LISTEN or SYN_RCVD */
        if( (rba_EthTcp_DynSockTbl_ast[lIdxTcpSock_uo].ListenTcpSockIdx_uo == TcpDynSockTblIdx_uo)  &&
            ((rba_EthTcp_DynSockTbl_ast[lIdxTcpSock_uo].State_en == RBA_ETHTCP_CONN_LISTEN_E)       ||
            (rba_EthTcp_DynSockTbl_ast[lIdxTcpSock_uo].State_en == RBA_ETHTCP_CONN_SYN_RCVD_E)) )
        {
            /* Execute an Abort close of the current channel */
            rba_EthTcp_AbortClose( lIdxTcpSock_uo );
        }
    }

    return;
}



#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */














