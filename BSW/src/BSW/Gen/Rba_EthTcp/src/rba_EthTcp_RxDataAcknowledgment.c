

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "TcpIp_Prv.h"

#include "SoAd.h"
#include "SoAd_Cbk.h" /* Required for SoAd call-back functions */

#include "rba_EthTcp.h"
#include "rba_EthTcp_Prv.h"

#if (!defined(SOAD_AR_RELEASE_MAJOR_VERSION) || (SOAD_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - TcpIp and SoAd"
#endif

#if (!defined(SOAD_AR_RELEASE_MINOR_VERSION) || (SOAD_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - TcpIp and SoAd"
#endif


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_UpdateTimerAfterDataAcknowledgment( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpDynSockTblIdx_uo,
																					VAR( boolean, AUTOMATIC )				NeedTimerRestart_b,
																					VAR( boolean, AUTOMATIC )				NeedTimerExpiration_b );
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
/** rba_EthTcp_RxDataAcknowledgment() 	    - Execute the processing of a received data acknowledgment							**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 					- Tcp dynamic socket table index													**/
/** ConfirmedLen_u16                 		- Length of confirmed data by the remote (acknowledged data)                        **/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):						None																				**/
/**																																**/
/** Return value:							None																				**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RxDataAcknowledgment(  VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpDynSockTblIdx_uo,
																VAR( uint16, AUTOMATIC )	            ConfirmedLen_u16 )
{
	/* Declare local variables */
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( uint16, AUTOMATIC ) 											lUnackedDataLen_u16;
#endif
	VAR( boolean, AUTOMATIC )											lNeedTimerRestart_b;
	VAR( boolean, AUTOMATIC )											lNeedTimerExpiration_b;

	/* Initialize the timer restart flag to FALSE */
	lNeedTimerRestart_b = FALSE;

	/* Initialize the timer expiration flag to FALSE */
	lNeedTimerExpiration_b = FALSE;

#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* ------------------------- */
	/* Complete or Partial ACK 	 */
	/* ------------------------- */

	/* If the data length confirmed by the remote is greater than 0 (complete or partial ACK) */
	if( ConfirmedLen_u16 > 0U )
	{
		/* ------------------------- */
		/* Update variables 	 	 */
		/* ------------------------- */

		/* Reset the duplicate ACK counter */
		/* (we have received an ACK that acknowledge some data so we can reset the duplicate ACK counter) */
		lTcpDynSockTbl_pst->DuplicateAckCntr_u8 = 0U;

		/* Update the acknowledged data location in the Tcp Tx buffer */
		rba_EthTcp_SetTxBufAfterAcked( TcpDynSockTblIdx_uo, ConfirmedLen_u16 );

		/* Get the new length of unacked data in the Tcp Tx buffer */
		lUnackedDataLen_u16 = rba_EthTcp_GetTxBufUnackedLen( TcpDynSockTblIdx_uo );

		/* -------------------------------------------- */
		/* Oldest unacked segment length handling 		*/
		/* -------------------------------------------- */

		/* If the oldest unacked segment is now acknowledged */
		if( ConfirmedLen_u16 >= lTcpDynSockTbl_pst->OldestUnackedSegmentLength_u16 )
		{
			/* Set the oldest unacked segment length to 0 */
			lTcpDynSockTbl_pst->OldestUnackedSegmentLength_u16 = 0U;

			/* If there are still unacked data */
			if( lUnackedDataLen_u16 > 0U )
			{
				/* Set the oldest unacked segment length to the length of unacked data */
				lTcpDynSockTbl_pst->OldestUnackedSegmentLength_u16 = lUnackedDataLen_u16;

#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON || RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
				/* Set a flag to indicate that the RETX and UTO timers need to be restarted */
				/* (we are going to begin a new retransmission procedure for the next unacknowledged data) */
				lNeedTimerRestart_b = TRUE;
#endif
			}
		}

		/* The oldest unacked segment is not fully acknowledged yet */
		else
		{
			/* Decrement the oldest unacked segment length by the length of acknowledged data */
			lTcpDynSockTbl_pst->OldestUnackedSegmentLength_u16 -= ConfirmedLen_u16;
		}

		/* ------------------------- */
		/* Partial Ack handling 	 */
		/* ------------------------- */

		/* If we have a partial ACK (all our data have not been fully acknowledged) */
		if( lUnackedDataLen_u16 > 0U )
		{
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
			/* When a partial ACK is received, we can do an intermediate retransmission (expire RETX timer) */
			/* (See congestion control algorithms - RFC3782 p8) */
			lNeedTimerExpiration_b = TRUE;
#endif
		}

		/* ------------------------- */
		/* Upper layer confirmation  */
		/* ------------------------- */

		/* Call the SoAd API to indicate that the transmission of some data has succeeded (the acknowledgment has been received for these data) */
		SoAd_TxConfirmation( 	TcpDynSockTblIdx_uo,
								ConfirmedLen_u16 );
	}

	/* ------------------------- */
	/* Duplicate ACK 	 		 */
	/* ------------------------- */

	/* If the data length confirmed by the remote is equal to 0 (duplicate ACK) */
	else
	{
		/* Get the length of unacked data in the Tcp Tx buffer */
		lUnackedDataLen_u16 = rba_EthTcp_GetTxBufUnackedLen( TcpDynSockTblIdx_uo );

		/* If there are unacked data */
		if( lUnackedDataLen_u16 > 0U )
		{
			/* Increment the duplicate ack counter */
			/* (duplicate ack counting should be done only in case we have some unacked data that might need retransmission) */
			lTcpDynSockTbl_pst->DuplicateAckCntr_u8++;

	        /* If we have received 3 duplicate ACK */
	        if( lTcpDynSockTbl_pst->DuplicateAckCntr_u8 >= 3U )
	        {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
	            /* When 3 duplicate ACK are received, we can do an intermediate retransmission (expire RETX timer) */
	            /* (See fast retransmit algorithm - RFC5681 p8) */
	            lNeedTimerExpiration_b = TRUE;
#endif

	            /* Reset the duplicate ACK counter */
	            lTcpDynSockTbl_pst->DuplicateAckCntr_u8 = 0U;
	        }
		}
	}
#endif

	/* ------------------------- */
	/* Timer management 	 	 */
	/* ------------------------- */

	/* Update the Tcp timers */
	rba_EthTcp_UpdateTimerAfterDataAcknowledgment( 	TcpDynSockTblIdx_uo,
													lNeedTimerRestart_b,
													lNeedTimerExpiration_b );

	return;
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_UpdateTimerAfterDataAcknowledgment() - Execute the timers update after the reception of a data acknowledgment	**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 							- Tcp dynamic socket table index											**/
/** NeedTimerRestart_b                 				- Flag indicating if the ReTx and UTO timers need to be restarted   		**/
/** NeedTimerExpiration_b                 			- Flag indicating if the ReTx timer need to be expired                 		**/
/**																																**/
/** Parameters (inout):								None																		**/
/**																																**/
/** Parameters (out):								None																		**/
/**																																**/
/** Return value:									None																		**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_UpdateTimerAfterDataAcknowledgment( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpDynSockTblIdx_uo,
																					VAR( boolean, AUTOMATIC )				NeedTimerRestart_b,
																					VAR( boolean, AUTOMATIC )				NeedTimerExpiration_b )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
#if ( (RBA_ETHTCP_RETX_ENABLED == STD_ON) || (RBA_ETHTCP_ZWP_ENABLED == STD_ON) || (RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON) )
    VAR( uint16, AUTOMATIC )                                            lUnackedDataLen_u16;
#endif
#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
	VAR( uint16, AUTOMATIC ) 											lRemainDataLen_u16;
#endif

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

#if ( (RBA_ETHTCP_RETX_ENABLED == STD_ON) || (RBA_ETHTCP_ZWP_ENABLED == STD_ON) || (RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON) )
	/* Get the length of unacked data in the Tcp Tx buffer */
	lUnackedDataLen_u16 = rba_EthTcp_GetTxBufUnackedLen( TcpDynSockTblIdx_uo );
#endif

#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
    /* ------------------------- */
    /* Keep Alive timer          */
    /* ------------------------- */

	/* Restart the Keep Alive timer (if it is running) */
	/* (the connection has to remain open if ACK is received) */
	rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
#endif

#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
    /* ------------------------- */
    /* ReTx timer                */
    /* ------------------------- */

	/* Check if the starting / restarting / expiration of the RETX timer is needed */
	/* (there are unacked data and window size is greater than 0) */
	if ( (lUnackedDataLen_u16 > 0U) 						&&
		 (lTcpDynSockTbl_pst->RcvdWndSize_u16 > 0U) )
	{
		/* Start the Retransmission timer (if it is not already running) */
		rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_RETX_E );

		/* Check if the restart flag is set */
	    if( NeedTimerRestart_b != FALSE )
	    {
	        /* Restart the Retransmission timer */
	        rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_RETX_E );
	    }

	    /* Check if the expiration flag is set */
	    if( NeedTimerExpiration_b != FALSE )
	    {
	        /* Expire the Retransmission timer */
	        /* (In the next MainFunction a retransmission will occur) */
	        rba_EthTcp_ExpireTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_RETX_E );
	    }
	}

	/* Check if the stopping of the RETX timer is needed */
	/* (all the data are acknowledged or zero window is advertised by the remote) */
	else
	{
		/* Stop the Retransmission timer (if it is running) */
		rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_RETX_E );
	}
#endif

#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
    /* ------------------------- */
    /* ZWP timer                 */
    /* ------------------------- */

    /* Get how much data in Tcp Tx buffer is ready to be sent */
    lRemainDataLen_u16 = rba_EthTcp_GetTxBufSndLen( TcpDynSockTblIdx_uo );

	/* Check if the starting / restarting of ZWP timer is needed */
	/* (some data are unacked or pending to be sent and remote window size is equal to 0) */
	if( ((lUnackedDataLen_u16 > 0U) || (lRemainDataLen_u16 > 0U))	&&
		(lTcpDynSockTbl_pst->RcvdWndSize_u16 == 0U) )
	{
		/* Start the Zero Window Probe Timer (if it is not already running) */
		rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_ZWP_E );

		/* Restart the Zero Window Probe Timer */
		/* (the connection has to stay open if remote window size remain equal to 0 - RFC1122 p92) */
		rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_ZWP_E );
	}

	/* Check if the stopping of ZWP timer is needed */
	/* (no more data are unacked or pending to be sent or remote window size is greater than 0) */
	else
	{
		/* Stop the Zero Window Probe Timer (if it is running) */
		rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_ZWP_E );
	}
#endif

#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
    /* ------------------------- */
    /* User Timeout timer        */
    /* ------------------------- */

    /* Check if the restarting of the UTO timer is needed */
    /* (there are unacked data) */
    if ( lUnackedDataLen_u16 > 0U )
    {
        /* Check if the restart flag is set */
        if( NeedTimerRestart_b != FALSE )
        {
            /* Restart the User Timeout timer (if it is running) */
            rba_EthTcp_RestartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_UTO_E );
        }
    }

	/* Check if the stopping of UTO timer is needed */
	/* (all the data are acknowledged) */
	else
	{
		/* Stop the User Timeout timer */
		rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_UTO_E );
	}
#endif

	return;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */















