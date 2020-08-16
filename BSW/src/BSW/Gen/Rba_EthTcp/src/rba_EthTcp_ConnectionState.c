

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
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_StopTimerBeforeChangeState      ( VAR( TcpIp_SocketIdType, AUTOMATIC )       TcpDynSockTblIdx_uo,
                                                                                  VAR( rba_EthTcp_ConnState_ten, AUTOMATIC ) NewConnState_en );

static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_StartTimerAfterChangeState      ( VAR( TcpIp_SocketIdType, AUTOMATIC )       TcpDynSockTblIdx_uo,
                                                                                  VAR( rba_EthTcp_ConnState_ten, AUTOMATIC ) NewConnState_en );
#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


/*
 ***************************************************************************************************
 * Local functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_SetConnectionState() - Set the connection state of a Tcp socket												    **/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		    - Tcp dynamic socket table index														    **/
/** NewConnState_en   		 	    - New Tcp connection state																    **/
/**																																**/
/** Parameters (inout):			    None																				        **/
/**																																**/
/** Parameters (out):			    None																						**/
/**																																**/
/** Return value:        		    None                                                                                  	    **/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetConnectionState (   VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
													            VAR( rba_EthTcp_ConnState_ten, AUTOMATIC ) 	NewConnState_en )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ---------------------------------------- */
    /* Stop current timer                       */
    /* ---------------------------------------- */

    /* Stop timer before the changing of the connection state */
    rba_EthTcp_StopTimerBeforeChangeState( TcpDynSockTblIdx_uo, NewConnState_en );

    /* ---------------------------------------- */
    /* Change connection state                  */
    /* ---------------------------------------- */

    /* Set the previous state */
    lTcpDynSockTbl_pst->PrevState_en = lTcpDynSockTbl_pst->State_en;

    /* Set the state in the Tcp dynamic table entry of the socket */
    lTcpDynSockTbl_pst->State_en = NewConnState_en;

    /* ---------------------------------------- */
    /* Start timer                              */
    /* ---------------------------------------- */

    /* Start timer after the changing of the connection state */
    rba_EthTcp_StartTimerAfterChangeState( TcpDynSockTblIdx_uo, NewConnState_en );

	return;
}


/*
***************************************************************************************************
* Static functions
***************************************************************************************************
*/

/*********************************************************************************************************************************/
/** rba_EthTcp_StopTimerBeforeChangeState() - Stop the currently running timer before changing the Tcp connection state         **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** NewConnState_en                         - New Tcp connection state                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_StopTimerBeforeChangeState (    VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                                VAR( rba_EthTcp_ConnState_ten, AUTOMATIC )  NewConnState_en )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ---------------------------------------- */
    /* Stop current timer                       */
    /* ---------------------------------------- */
    switch ( lTcpDynSockTbl_pst->State_en )
    {
        /* ---------------------------------------- */
        /* Actual state is SYN_SENT                 */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_SYN_SENT_E:
        {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            /* Stop the SynSent timer before changing of state */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_SYNSENT_E );
#endif
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is SYN_RCVD                 */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_SYN_RCVD_E:
        {
            /* Stop the SynRcvd timer before changing of state */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_SYNRCVD_E );
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is FIN_WAIT_1               */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_FIN_WAIT_1_E:
        {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            /* If the new connection state is FIN_WAIT_2 */
            if( NewConnState_en == RBA_ETHTCP_CONN_FIN_WAIT_2_E )
            {
                /* Stop the FinWait1_Closing timer before changing of state */
                rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E );
            }

            /* When the new state is CLOSING state, it is not necessary to stop the current timer */
            /* (FIN_WAIT_1 and CLOSING states are sharing the same timer) */
#endif
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is CLOSING                  */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_CLOSING_E:
        {
            /* Stop the KeepAlive timer */
            /* (In TIME_WAIT state the Keep Alive should not run) */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
#endif

#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            /* Stop the FinWait1_Closing timer before changing of state */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E );
#endif
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is FIN_WAIT2                */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_FIN_WAIT_2_E:
        {
            /* Stop the KeepAlive timer */
            /* (In TIME_WAIT state the Keep Alive should not run) */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
#endif

            /* Stop the FinWait2 timer before changing of state */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_FINWAIT2_E );
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is LAST_ACK                 */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_LAST_ACK_E:
        {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            /* Stop the LastAck timer before changing of state */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_LASTACK_E );
#endif
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is TIME_WAIT                */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_TIME_WAIT_E:
        {
            /* Stop the TimeWait timer before changing of state */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_TIMEWAIT_E );
        }
        break;

        /* ---------------------------------------- */
        /* Other state                              */
        /* ---------------------------------------- */
        default:
        {
            /* No timer to stop before changing of state */
        }
        break;
    }

    return;
}

/*********************************************************************************************************************************/
/** rba_EthTcp_StartTimerAfterChangeState() - Start timer after the changing of connection state                                **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** NewConnState_en                         - New Tcp connection state                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_StartTimerAfterChangeState (    VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                                VAR( rba_EthTcp_ConnState_ten, AUTOMATIC )  NewConnState_en )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
    VAR( uint16, AUTOMATIC )                                                lRemainDataLen_u16;
#endif

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ---------------------------------------- */
    /* Start timer                              */
    /* ---------------------------------------- */
    switch ( NewConnState_en )
    {
        /* ---------------------------------------- */
        /* New state is SYN_SENT                    */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_SYN_SENT_E:
        {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            /* Start SynSent timer */
            rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_SYNSENT_E );
#endif
        }
        break;

        /* ---------------------------------------- */
        /* New state is SYN_RCVD                    */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_SYN_RCVD_E:
        {
            /* Start SynRcvd timer */
            rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_SYNRCVD_E );
        }
        break;

        /* ---------------------------------------- */
        /* New state is ESTABLISHED                 */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_ESTABLISHED_E:
        {
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
            /* If Keep-Alive is enabled for this socket */
            if ( lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvEnad_u8 == STD_ON )
            {
                /* Start the Keep Alive timer */
                rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
            }
#endif

#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
            /* Calculate how much data in TCP buffer is ready to send */
            lRemainDataLen_u16 = rba_EthTcp_GetTxBufSndLen( TcpDynSockTblIdx_uo );

            /* Check if the starting of the ZWP timer is needed */
            if ( (lRemainDataLen_u16 > 0U)                   &&     /* DATA pending to be sent */
                 (lTcpDynSockTbl_pst->RcvdWndSize_u16 == 0U) )      /* RCV.WND == 0 */
            {
                /* Start Zero Window Probe Timer */
                rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_ZWP_E );
            }
#endif
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is FIN_WAIT_1               */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_FIN_WAIT_1_E:
        {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            /* Start the FinWait1_Closing timer before changing of state */
            rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E );
#endif
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is FIN_WAIT2                */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_FIN_WAIT_2_E:
        {
            /* Start the FinWait2 timer */
            rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_FINWAIT2_E );
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is LAST_ACK                 */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_LAST_ACK_E:
        {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
            /* Start the LastAck timer */
            rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_LASTACK_E );
#endif
        }
        break;

        /* ---------------------------------------- */
        /* Actual state is TIME_WAIT                */
        /* ---------------------------------------- */
        case RBA_ETHTCP_CONN_TIME_WAIT_E:
        {
            /* Start the TimeWait timer */
            rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_TIMEWAIT_E );
        }
        break;

        /* ---------------------------------------- */
        /* Other state                              */
        /* ---------------------------------------- */
        default:
        {
            /* No timer to start */
        }
        break;
    }

    return;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */























