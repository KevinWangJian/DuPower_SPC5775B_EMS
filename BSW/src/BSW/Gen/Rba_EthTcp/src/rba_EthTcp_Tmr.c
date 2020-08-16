

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
static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_IncrGeneralTimer     ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );

#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_IncrKeepAliveTimer   ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );
#endif

#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_IncrDlyAckTimer      ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );
#endif

#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_IncrUtoTimer         ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );
#endif

static FUNC( uint32, RBA_ETHTCP_CODE )  rba_EthTcp_GetTimerTimeout      ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
																	      VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC )    TmrSt_en );

static FUNC( uint16, RBA_ETHTCP_CODE )   rba_EthTcp_GetTimerMaxRetry     ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                          VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC )    TmrSt_en );

static FUNC( void, RBA_ETHTCP_CODE )    rba_EthTcp_ActionAfterMaxRetry  ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                          VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC )    TmrSt_en );

#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
static FUNC( void , RBA_ETHTCP_CODE )   rba_EthTcp_BackOffRto           ( VAR( TcpIp_SocketIdType , AUTOMATIC )     TcpDynSockTblIdx_uo,
													  	  		          VAR( uint32, AUTOMATIC )                  CurrentTimeOut_u32 );
#endif
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
/** rba_EthTcp_StartTimer() - By this function, a Tcp timer can be started														**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 	- Tcp dynamic socket table index																	**/
/** ConnTmrSt_en		   	- Timer that should be started																		**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:			None																								**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_StartTimer(    VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpDynSockTblIdx_uo,
														VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	switch( TmrSt_en )
	{
		/* ----------------------------- */
		/* General timer starting 	     */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_SYNSENT_E:
		case RBA_ETHTCP_TMR_SYNRCVD_E:
		case RBA_ETHTCP_TMR_RETX_E:
		case RBA_ETHTCP_TMR_ZWP_E:
		case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
		case RBA_ETHTCP_TMR_FINWAIT2_E:
		case RBA_ETHTCP_TMR_LASTACK_E:
		case RBA_ETHTCP_TMR_TIMEWAIT_E:
		{
			/* If the General timer to start is not already running */
			if( lTcpDynSockTbl_pst->GeneralTmrSt_en != TmrSt_en )
			{
				/* Set the currently running timer */
				lTcpDynSockTbl_pst->GeneralTmrSt_en = TmrSt_en;

				/* Reset the timer counter and the retry counter to 0 */
				lTcpDynSockTbl_pst->GeneralTmr_u32 = 0U;
				lTcpDynSockTbl_pst->GeneralRetryCntr_u8 = 0U;

                /* As the General timer has been started, any RTT measurement need to be stopped */
                /* (RTT measurement relies on the current value of the General timer counter, if the timer counter is reset, RTT measurement cannot continue)  */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
                /* Stop RTT measurement */
                lTcpDynSockTbl_pst->RttInProgress_b = FALSE;
#endif
			}
		}
		break;

		/* ----------------------------- */
		/* Keep Alive timer starting     */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_KEEPALIVE_E:
		{
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
			/* If the Keep Alive timer is not already running */
			if( lTcpDynSockTbl_pst->KeepAlvTmrSt_en != RBA_ETHTCP_TMR_KEEPALIVE_E )
			{
				/* Set the Keep Alive timer as running */
				lTcpDynSockTbl_pst->KeepAlvTmrSt_en = RBA_ETHTCP_TMR_KEEPALIVE_E;

				/* Reset the timer counter and the retry counter to 0 */
				lTcpDynSockTbl_pst->KeepAlvTmr_u32 = 0U;
				lTcpDynSockTbl_pst->KeepAlvRetryCntr_u16 = 0U;
			}
#endif
		}
		break;

		/* ----------------------------- */
		/* Delayed Ack timer starting    */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_DLYACK_E:
		{
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
			/* If the Delayed Ack timer is not already running */
			if( lTcpDynSockTbl_pst->DlyAckTmrSt_en != RBA_ETHTCP_TMR_DLYACK_E )
			{
				/* Set the Delayed Ack timer as running */
				lTcpDynSockTbl_pst->DlyAckTmrSt_en = RBA_ETHTCP_TMR_DLYACK_E;

				/* Reset the timer counter to 0 */
				lTcpDynSockTbl_pst->DlyAckTmr_u8 = 0U;
			}
#endif
		}
		break;

		/* ----------------------------- */
		/* User Timeout timer starting   */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_UTO_E:
		default:
		{
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
			/* If the User Timeout timer is not already running */
			if( lTcpDynSockTbl_pst->UtoTmrSt_en != RBA_ETHTCP_TMR_UTO_E )
			{
				/* Set the User Timeout timer as running */
				lTcpDynSockTbl_pst->UtoTmrSt_en = RBA_ETHTCP_TMR_UTO_E;

				/* Reset the timer counter to 0 */
				lTcpDynSockTbl_pst->UtoTmr_u32 = 0U;
			}
#endif
		}
		break;
	}

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RestartTimer()	- By this function, a Tcp timer can be restarted												**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		- Tcp dynamic socket table index																**/
/** ConnTmrSt_en		   		- Timer that should be restarted																**/
/**																																**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):			None																							**/
/**																																**/
/** Return value:				None																							**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_RestartTimer(  VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo,
														VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	switch( TmrSt_en )
	{
		/* ----------------------------- */
		/* General timer restarting 	 */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_SYNSENT_E:
		case RBA_ETHTCP_TMR_SYNRCVD_E:
		case RBA_ETHTCP_TMR_RETX_E:
		case RBA_ETHTCP_TMR_ZWP_E:
		case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
		case RBA_ETHTCP_TMR_FINWAIT2_E:
		case RBA_ETHTCP_TMR_LASTACK_E:
		case RBA_ETHTCP_TMR_TIMEWAIT_E:
		{
			/* If the General timer to restart is already running */
			if( lTcpDynSockTbl_pst->GeneralTmrSt_en == TmrSt_en )
			{
				/* Reset the timer counter to 0 */
				lTcpDynSockTbl_pst->GeneralTmr_u32 = 0U;

				/* Reset the retry counter */
				lTcpDynSockTbl_pst->GeneralRetryCntr_u8 = 0U;

                /* As the General timer has been restarted, any RTT measurement need to be stopped */
                /* (RTT measurement relies on the current value of the General timer counter, if the timer counter is reset, RTT measurement cannot continue)  */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
                /* Stop RTT measurement */
                lTcpDynSockTbl_pst->RttInProgress_b = FALSE;
#endif
			}
		}
		break;

		/* ----------------------------- */
		/* Keep Alive timer restarting   */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_KEEPALIVE_E:
		{
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
			/* If the Keep Alive timer is already running */
			if( lTcpDynSockTbl_pst->KeepAlvTmrSt_en == RBA_ETHTCP_TMR_KEEPALIVE_E )
			{
				/* Reset the timer counter and the retry counter to 0 */
				lTcpDynSockTbl_pst->KeepAlvTmr_u32 = 0U;
				lTcpDynSockTbl_pst->KeepAlvRetryCntr_u16 = 0U;
			}
#endif
		}
		break;

		/* ----------------------------- */
		/* User Timeout timer restarting */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_UTO_E:
		{
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
			/* If the User Timeout timer is already running */
			if( lTcpDynSockTbl_pst->UtoTmrSt_en == RBA_ETHTCP_TMR_UTO_E )
			{
				/* Reset the timer counter to 0 */
				lTcpDynSockTbl_pst->UtoTmr_u32 = 0U;
			}
#endif
		}
		break;

        /* ----------------------------- */
        /* Other timers                  */
        /* ----------------------------- */

		case RBA_ETHTCP_TMR_DLYACK_E:
		default:
		{
		    /* Other timer cannot be restarted */
		}
		break;
	}

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_StopTimer() 	- By this function, a Tcp timer can be stopped														**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 	- Tcp dynamic socket table index																	**/
/** ConnTmrSt_en		   	- Timer that should be stopped																		**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:			None																								**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_StopTimer( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo,
													VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	switch( TmrSt_en )
	{
		/* ----------------------------- */
		/* General timer stopping 		 */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_SYNSENT_E:
		case RBA_ETHTCP_TMR_SYNRCVD_E:
		case RBA_ETHTCP_TMR_RETX_E:
		case RBA_ETHTCP_TMR_ZWP_E:
		case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
		case RBA_ETHTCP_TMR_FINWAIT2_E:
		case RBA_ETHTCP_TMR_LASTACK_E:
		case RBA_ETHTCP_TMR_TIMEWAIT_E:
		{
			/* If the General timer to stop is already running */
			if( lTcpDynSockTbl_pst->GeneralTmrSt_en == TmrSt_en )
			{
				/* Stop the currently running timer */
				lTcpDynSockTbl_pst->GeneralTmrSt_en = RBA_ETHTCP_TMR_STOPPED_E;

				/* Reset the timer counter and the retry counter to 0 */
				lTcpDynSockTbl_pst->GeneralTmr_u32 = 0U;
				lTcpDynSockTbl_pst->GeneralRetryCntr_u8 = 0U;

                /* As the General timer has been stopped, any RTT measurement need to be stopped */
                /* (RTT measurement relies on the current value of the General timer counter, if the timer counter is reset, RTT measurement cannot continue)  */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
                /* Stop RTT measurement */
                lTcpDynSockTbl_pst->RttInProgress_b = FALSE;
#endif
			}
		}
		break;

		/* ----------------------------- */
		/* Keep Alive timer stopping     */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_KEEPALIVE_E:
		{
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
			/* If the Keep Alive timer is already running */
			if( lTcpDynSockTbl_pst->KeepAlvTmrSt_en == RBA_ETHTCP_TMR_KEEPALIVE_E )
			{
				/* Set the Keep Alive timer as stopped */
				lTcpDynSockTbl_pst->KeepAlvTmrSt_en = RBA_ETHTCP_TMR_STOPPED_E;

				/* Reset the timer counter and the retry counter to 0 */
				lTcpDynSockTbl_pst->KeepAlvTmr_u32 = 0U;
				lTcpDynSockTbl_pst->KeepAlvRetryCntr_u16 = 0U;
			}
#endif
		}
		break;

		/* ----------------------------- */
		/* Delayed Ack timer stopping    */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_DLYACK_E:
		{
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
			/* If the Delayed Ack timer is already running */
			if( lTcpDynSockTbl_pst->DlyAckTmrSt_en == RBA_ETHTCP_TMR_DLYACK_E )
			{
				/* Set the Delayed Ack timer as stopped */
				lTcpDynSockTbl_pst->DlyAckTmrSt_en = RBA_ETHTCP_TMR_STOPPED_E;

				/* Reset the timer counter to 0 */
				lTcpDynSockTbl_pst->DlyAckTmr_u8 = 0U;
			}
#endif
		}
		break;

		/* ----------------------------- */
		/* User Timeout timer stopping   */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_UTO_E:
		default:
		{
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
			/* If the User Timeout timer is already running */
			if( lTcpDynSockTbl_pst->UtoTmrSt_en == RBA_ETHTCP_TMR_UTO_E )
			{
				/* Set the User Timeout timer as stopped */
				lTcpDynSockTbl_pst->UtoTmrSt_en = RBA_ETHTCP_TMR_STOPPED_E;

				/* Reset the timer counter to 0 */
				lTcpDynSockTbl_pst->UtoTmr_u32 = 0U;
			}
#endif
		}
		break;
	}

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ExpireTimer() - By this function, a Tcp timer can be expired manually											**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 	- Tcp dynamic socket table index																	**/
/** ConnTmrSt_en		   	- Timer that should be expired																		**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:			None																								**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_ExpireTimer(	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
														VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 			lTcpDynSockTbl_pst;
	VAR( uint32, AUTOMATIC ) 												lTimeOut_u32;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Get timeout value of the timer to expire */
	lTimeOut_u32 = rba_EthTcp_GetTimerTimeout( 	TcpDynSockTblIdx_uo, TmrSt_en );

	switch( TmrSt_en )
	{
		/* ----------------------------- */
		/* General timer expiration	     */
		/* ----------------------------- */
		case RBA_ETHTCP_TMR_SYNSENT_E:
		case RBA_ETHTCP_TMR_SYNRCVD_E:
		case RBA_ETHTCP_TMR_RETX_E:
		case RBA_ETHTCP_TMR_ZWP_E:
		case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
		case RBA_ETHTCP_TMR_FINWAIT2_E:
		case RBA_ETHTCP_TMR_LASTACK_E:
		case RBA_ETHTCP_TMR_TIMEWAIT_E:
		{
			/* If the General timer to expire is already running */
			if( lTcpDynSockTbl_pst->GeneralTmrSt_en == TmrSt_en )
			{
				/* Expire the timer counter */
				lTcpDynSockTbl_pst->GeneralTmr_u32 = lTimeOut_u32;

                /* As the General timer has been expired, any RTT measurement need to be stopped */
                /* (RTT measurement relies on the current value of the General timer counter, if the timer counter is expired, RTT measurement cannot continue)  */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
                /* Stop RTT measurement */
                lTcpDynSockTbl_pst->RttInProgress_b = FALSE;
#endif
			}
		}
		break;

        /* ----------------------------- */
        /* Other timers                  */
        /* ----------------------------- */
		case RBA_ETHTCP_TMR_KEEPALIVE_E:
		case RBA_ETHTCP_TMR_DLYACK_E:
		case RBA_ETHTCP_TMR_UTO_E:
		default:
		{
		    /* Other timer cannot be expired */
		}
		break;
	}

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_IncrTmr() 	- Function to increment the currently running Tcp timers											**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 	- Tcp dynamic socket table index																	**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None    																							**/
/**																																**/
/** Return value:			None																								**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_IncrTimer( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 			lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* ----------------------------- */
	/* General timer incrementation  */
	/* ----------------------------- */

	/* If a General timer is running */
	if( lTcpDynSockTbl_pst->GeneralTmrSt_en != RBA_ETHTCP_TMR_STOPPED_E )
	{
	    /* Execute the General timer incrementation */
	    rba_EthTcp_IncrGeneralTimer( TcpDynSockTblIdx_uo );
	}

	/* -------------------------------- */
	/* Keep Alive timer incrementation  */
	/* -------------------------------- */

	/* KeepAlive timer works only if KEEP_ALIVE feature is enabled */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )

	/* KeepAlive timer is running */
	if( lTcpDynSockTbl_pst->KeepAlvTmrSt_en != RBA_ETHTCP_TMR_STOPPED_E )
	{
	    /* Execute the Keep Alive timer incrementation */
	    rba_EthTcp_IncrKeepAliveTimer( TcpDynSockTblIdx_uo );
	}

#endif

	/* --------------------------------- */
	/* Delayed Ack timer incrementation  */
	/* --------------------------------- */

	/* DelayedAck timer works only if DLYACK feature is enabled */
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )

	/* DelayedAck timer is running */
	if( lTcpDynSockTbl_pst->DlyAckTmrSt_en != RBA_ETHTCP_TMR_STOPPED_E )
	{
	    rba_EthTcp_IncrDlyAckTimer( TcpDynSockTblIdx_uo );
	}

#endif

	/* ---------------------------------- */
	/* User Timeout timer incrementation  */
	/* ---------------------------------- */

	/* UserTimeout timer works only if USER_TIMEOUT feature is enabled */
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )

	/* UserTimeout timer is running */
	if( lTcpDynSockTbl_pst->UtoTmrSt_en != RBA_ETHTCP_TMR_STOPPED_E )
	{
	    rba_EthTcp_IncrUtoTimer( TcpDynSockTblIdx_uo );
	}

#endif

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_CalculateRto() 	- This function calculates retransmission timeout (RTO) as per Jacobson's and Karn's Algorithm. **/
/**								The RTO calculation is needed when the dynamic retransmission feature is enabled (see RFC6298).	**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		- Tcp dynamic socket table index																**/
/**																																**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):			None																							**/
/**																																**/
/** Return value:				None																							**/
/**																																**/
/*********************************************************************************************************************************/
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
FUNC( void , RBA_ETHTCP_CODE ) rba_EthTcp_CalculateRto( VAR ( TcpIp_SocketIdType , AUTOMATIC ) TcpDynSockTblIdx_uo )

{
	/* Declare local variables */
	VAR( uint32, AUTOMATIC )		lRtt_u32;
	VAR( uint32, AUTOMATIC )     	lSRtt_u32;
	VAR( uint32, AUTOMATIC )    	lRttVar_u32;
	VAR( uint32, AUTOMATIC )   		lSErr_u32;
	VAR( uint32, AUTOMATIC )     	lRto_u32;

    /* If RTT measurement is in progress for the Tcp socket */
    if( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].RttInProgress_b != FALSE )
    {
        /* --------------------------- */
        /* Compute RTT				   */
        /* --------------------------- */

        /* The value of RTT corresponds to the actual value of the timer */
        lRtt_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].GeneralTmr_u32;

        /* ------------------------------------- */
        /* Compute new values of SRTT and RTTVAR */
        /* ------------------------------------- */

        /* Get the previous values of SRTT and RTTVAR */
        lSRtt_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SRtt_u32;
        lRttVar_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].RttVar_u32;


        /* If SRTT and RTTVAR are equal to 0 */
        if( (lSRtt_u32 == 0U) && (lRttVar_u32 == 0U) )
        {
            /* SRTT and RTTVAR have not been calculated yet so use initial values */
            lSRtt_u32 = lRtt_u32;
            lRttVar_u32 = lRtt_u32/2U;
        }

        /* If previous values of SRTT and RTTVAR have already been calculated (they are different from 0) */
        else
        {
            /* Compute the new values of SRTT and RTTVAR */
            lSErr_u32 = (( lRtt_u32 >= lSRtt_u32)?(lRtt_u32 - lSRtt_u32):(lSRtt_u32 - lRtt_u32));
            lRttVar_u32 = ( (((1000U - RBA_ETHTCP_WEIGHT_RTTVAR) * lRttVar_u32) + (RBA_ETHTCP_WEIGHT_RTTVAR * lSErr_u32))/1000U );
            lSRtt_u32 = ( (((1000U - RBA_ETHTCP_WEIGHT_SRTT) * lSRtt_u32) + (RBA_ETHTCP_WEIGHT_SRTT * lRtt_u32))/1000U );
        }

        /* --------------------------- */
        /* Compute new value of RTO	   */
        /* --------------------------- */

        /* If K*RTTVAR is greater than or equal to the clock granularity */
        if( (4U * lRttVar_u32) >= 1U )
        {
            lRto_u32 = ( lSRtt_u32 + (4U * lRttVar_u32) );
        }
        /* If K*RTTVAR is lower than the clock granularity */
        else
        {
            lRto_u32 = ( lSRtt_u32 + 1U );
        }

        /* Limit RTO to lower bound */
        /* Acording to RFC6298 : Lower Boundary should be 1s */
        if( lRto_u32 < rba_EthTcp_CurrConfig_cpo->ReTxTimerLwrBound_u32 )
        {
            lRto_u32 = rba_EthTcp_CurrConfig_cpo->ReTxTimerLwrBound_u32;
        }

        /* Limit RTO to upper bound */
        /* Acording to RFC6298 : Upper Boundary should be at least 60s */
        if( lRto_u32 > rba_EthTcp_CurrConfig_cpo->ReTxTimerUprBound_u32 )
        {
            lRto_u32 = rba_EthTcp_CurrConfig_cpo->ReTxTimerUprBound_u32;
        }

        /* --------------------------- */
        /* Update dynamic table	   	   */
        /* --------------------------- */

        /* Update Tcp dynamic table entry of the socket */
        rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SRtt_u32 = lSRtt_u32;
        rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].RttVar_u32 = lRttVar_u32;
        rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].Rto_u32 = lRto_u32;

        /* Reset the flag indicating that an RTT measurement is in progress */
        rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].RttInProgress_b = FALSE;
    }

	return;
}
#endif


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_IncrGeneralTmr() - Function to increment the currently running General Tcp timer (SynSent, SynRcvd, ReTx, Zwp,   **/
/**                             FinWait1_Closing, FinWait2, LastAck or TimeWait timer)                                          **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo         - Tcp dynamic socket table index                                                                **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               None                                                                                            **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_IncrGeneralTimer( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
    VAR( uint32, AUTOMATIC )                                                lTimeOut_u32;
    VAR( uint8, AUTOMATIC )                                                 lMaxRetry_u8;
    VAR( Std_ReturnType, AUTOMATIC )                                        lRetVal_en;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Extract TimeOut and MaxRetry  */
    /* ----------------------------- */
    lTimeOut_u32  = rba_EthTcp_GetTimerTimeout( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->GeneralTmrSt_en );
    lMaxRetry_u8 = (uint8)( rba_EthTcp_GetTimerMaxRetry( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->GeneralTmrSt_en ) );

    /* ----------------------------- */
    /* Increment the timer counter   */
    /* ----------------------------- */
    lTcpDynSockTbl_pst->GeneralTmr_u32++;

    /* ----------------------------- */
    /* Check timer expiration        */
    /* ----------------------------- */

    /* If the timeout is not set to Inf and timer is expired */
    /* (when timeout is infinity, then the timer shall never expire) */
    if( (lTimeOut_u32 != 0xFFFFFFFFU) && (lTcpDynSockTbl_pst->GeneralTmr_u32 >= lTimeOut_u32) )
    {
        /* If max retries is set to Inf or max retries value is not reached */
        if( (lMaxRetry_u8 == 0xFFU) || (lTcpDynSockTbl_pst->GeneralRetryCntr_u8 < lMaxRetry_u8) )
        {
            /* ----------------------------- */
            /* Frame retransmission          */
            /* ----------------------------- */

            /* Initialize RetVal to E_OK */
            lRetVal_en = E_OK;

            /* Determine the frame to retransmit on timer expiration */
            switch( lTcpDynSockTbl_pst->GeneralTmrSt_en )
            {
                case RBA_ETHTCP_TMR_SYNSENT_E:
                {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
                    /* Send SYN in the next MainFunction */
                    lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_SYN_E );
#endif
                }
                break;

                case RBA_ETHTCP_TMR_SYNRCVD_E:
                {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
                    /* Send SYN-ACK in the next MainFunction */
                    lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_SYN_ACK_E );
#endif
                }
                break;

                case RBA_ETHTCP_TMR_RETX_E:
                {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
                    /* Send DATA in the next MainFunction */
                    lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_DATA_E );
#endif
                }
                break;

                case RBA_ETHTCP_TMR_ZWP_E:
                {
#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
                    /* Send ZWP in the next MainFunction */
                    lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ZWP_E );
#endif
                }
                break;

                case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
                case RBA_ETHTCP_TMR_LASTACK_E:
                {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
                    /* Send FIN-ACK in the next MainFunction */
                    lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_FIN_ACK_E );
#endif
                }
                break;

                default:
                {
                    /* Nothing to do */
                }
                break;
            }

            /* If the retransmission is successfully prepared for the next MainFunction */
            if( lRetVal_en == E_OK )
            {
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
                /* Set the flag indicating that this is a retransmission */
                lTcpDynSockTbl_pst->RetransmissionFlg_b = TRUE;
#endif

                /* ----------------------------- */
                /* Dynamic ReTx management       */
                /* ----------------------------- */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
                /* Karn's Algorithm : Do not measure RTT in case of retransmission */
                lTcpDynSockTbl_pst->RttInProgress_b = FALSE;

                /* Exponential back off */
                rba_EthTcp_BackOffRto( TcpDynSockTblIdx_uo, lTimeOut_u32 );
#endif

                /* ----------------------------- */
                /* Reset the timer               */
                /* ----------------------------- */

                /* Relaunch the timer counter */
                lTcpDynSockTbl_pst->GeneralTmr_u32 = 0U;

                /* Increment the retry counter */
                lTcpDynSockTbl_pst->GeneralRetryCntr_u8++;
            }

            /* If the retransmission cannot be prepared for the next MainFunction */
            else
            {
                /* Decrement the timer counter so that it will expire again in next MainFunction */
                lTcpDynSockTbl_pst->GeneralTmr_u32--;
            }
        }

        /* ----------------------------- */
        /* Max retry reached             */
        /* ----------------------------- */
        else
        {
            /* Execute the actions after max retry is reached */
            rba_EthTcp_ActionAfterMaxRetry( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->GeneralTmrSt_en );

            /* Stop the timer */
            /* (now that max retry is reached, timer execution is terminated) */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, lTcpDynSockTbl_pst->GeneralTmrSt_en );
        }
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_IncrKeepAliveTmr()   - Function to increment the KeepAlive Tcp timer                                             **/
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
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_IncrKeepAliveTimer( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
    VAR( uint32, AUTOMATIC )                                                lTimeOut_u32;
    VAR( uint16, AUTOMATIC )                                                lMaxRetry_u16;
    VAR( Std_ReturnType, AUTOMATIC )                                        lRetVal_en;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Extract TimeOut and MaxRetry  */
    /* ----------------------------- */
    lTimeOut_u32  = rba_EthTcp_GetTimerTimeout( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
    lMaxRetry_u16 = rba_EthTcp_GetTimerMaxRetry( TcpDynSockTblIdx_uo,  RBA_ETHTCP_TMR_KEEPALIVE_E );

    /* --------------------------- */
    /* Increment the timer counter */
    /* --------------------------- */
    lTcpDynSockTbl_pst->KeepAlvTmr_u32++;

    /* ----------------------------- */
    /* Check timer expiration        */
    /* ----------------------------- */

    /* If the timeout is not set to Inf and timer is expired */
    /* (when timeout is infinity, then the timer shall never expire) */
    if( (lTimeOut_u32 != 0xFFFFFFFFU) && (lTcpDynSockTbl_pst->KeepAlvTmr_u32 >= lTimeOut_u32) )
    {
        /* If max retries is set to Inf or max retries value is not reached */
        if( (lMaxRetry_u16 == 0xFFFFU) || (lTcpDynSockTbl_pst->KeepAlvRetryCntr_u16 < lMaxRetry_u16) )
        {
            /* Send a Keep Alive in the next MainFunction */
            lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_KEEP_ALIVE_E );

            /* If the Keep Alive is successfully prepared for the next MainFunction */
            if( lRetVal_en == E_OK )
            {
                /* --------------------------- */
                /* Reset the timer             */
                /* --------------------------- */

                /* Relaunch the timer counter */
                lTcpDynSockTbl_pst->KeepAlvTmr_u32 = 0U;

                /* Increment the retry counter */
                lTcpDynSockTbl_pst->KeepAlvRetryCntr_u16++;
            }

            /* If the Keep Alive cannot be prepared for the next MainFunction */
            else
            {
                /* Decrement the timer counter so that it will expire again in next MainFunction */
                lTcpDynSockTbl_pst->KeepAlvTmr_u32--;
            }
        }

        /* ----------------------------- */
        /* Max retry reached             */
        /* ----------------------------- */
        else
        {
            /* Execute the actions after max retry is reached */
            rba_EthTcp_ActionAfterMaxRetry( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );

            /* Stop the timer */
            /* (now that max retry is reached, timer execution is terminated) */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
        }
    }

    return;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_IncrDlyAckTimer()    - Function to increment the DelayedAck Tcp timer                                            **/
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
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_IncrDlyAckTimer( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
    VAR( uint32, AUTOMATIC )                                                lTimeOut_u32;
    VAR( Std_ReturnType, AUTOMATIC )                                        lRetVal_en;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Extract TimeOut               */
    /* ----------------------------- */
    lTimeOut_u32 = rba_EthTcp_GetTimerTimeout( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_DLYACK_E );

    /* --------------------------- */
    /* Increment the timer counter */
    /* --------------------------- */
    lTcpDynSockTbl_pst->DlyAckTmr_u8++;

    /* ----------------------------- */
    /* Check timer expiration        */
    /* ----------------------------- */

    /* If the timeout is not set to Inf and timer is expired */
    /* (when timeout is infinity, then the timer shall never expire) */
    if( (lTimeOut_u32 != 0xFFFFFFFFU) && (lTcpDynSockTbl_pst->DlyAckTmr_u8 >= lTimeOut_u32) )
    {
        /* Send an ACK in the MainFunction */
        lRetVal_en = rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_E );

        /* If the ACK is successfully prepared for the next MainFunction */
        if( lRetVal_en == E_OK )
        {
            /* Stop the timer */
            /* (now that Delayed ACK is prepared, timer execution is terminated) */
            rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_DLYACK_E );
        }

        /* If the ACK cannot be prepared for the next MainFunction */
        else
        {
            /* Decrement the timer counter so that it will expire again in next MainFunction */
            lTcpDynSockTbl_pst->DlyAckTmr_u8--;
        }
    }
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_IncrUtoTimer()       - Function to increment the UserTimeout Tcp timer                                           **/
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
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_IncrUtoTimer( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
    VAR( uint32, AUTOMATIC )                                                lTimeOut_u32;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* Extract TimeOut               */
    /* ----------------------------- */
    lTimeOut_u32 = rba_EthTcp_GetTimerTimeout( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_UTO_E );

    /* --------------------------- */
    /* Increment the timer counter */
    /* --------------------------- */
    lTcpDynSockTbl_pst->UtoTmr_u32++;

    /* ----------------------------- */
    /* Check timer expiration        */
    /* ----------------------------- */

    /* If the timeout is not set to Inf and timer is expired */
    /* (when timeout is infinity, then the timer shall never expire) */
    if( (lTimeOut_u32 != 0xFFFFFFFFU) && (lTcpDynSockTbl_pst->UtoTmr_u32 >= lTimeOut_u32) )
    {
        /* Reset the socket */
        /* (RFC793 p76 : For any state if user timeout expires, [...] delete TCP, enter CLOSED state and return) */
        rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );
    }
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_GetTimerTimeout()	- By this function, the timeout value of a Tcp timer can be get								**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 			- Tcp dynamic socket table index															**/
/** TmrSt_en		   			    - Timer for which the timeout value should be get											**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					- uint32																					**/
/**										Timeout value																			**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( uint32, RBA_ETHTCP_CODE ) rba_EthTcp_GetTimerTimeout(  VAR( TcpIp_SocketIdType, AUTOMATIC )    TcpDynSockTblIdx_uo,
																    VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 			lTcpDynSockTbl_pst;
	VAR( uint32, AUTOMATIC ) 												lTimeOut_u32;

	/* Initialize timeout value to 0 */
	lTimeOut_u32 = 0U;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	switch( TmrSt_en )
	{
		/* --------------------------- */
		/* SynRcvd timers  			   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_SYNRCVD_E:
		{
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON && RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
			/* If RTO has not been calculated yet */
			if( lTcpDynSockTbl_pst->Rto_u32 == 0U )
			{
				/* Use statically configured timeout */
				lTimeOut_u32 = rba_EthTcp_CurrConfig_cpo->SynRcvdTimeOut_u32;
			}
			else
			{
				/* Use calculated RTO */
				lTimeOut_u32 = lTcpDynSockTbl_pst->Rto_u32;
			}
#else
			/* Use statically configured timeout */
			/* (in SYN_RCVD state there is a timeout for both RETX enabled or disabled) */
			lTimeOut_u32 = rba_EthTcp_CurrConfig_cpo->SynRcvdTimeOut_u32;
#endif
		}
		break;

		/* ------------------------------------------------------- */
		/* SynSent, ReTx, Zwp, FinWait1_Closing or LastAck timers  */
		/* ------------------------------------------------------- */
		case RBA_ETHTCP_TMR_SYNSENT_E:
		case RBA_ETHTCP_TMR_RETX_E:
		case RBA_ETHTCP_TMR_ZWP_E:
		case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
		case RBA_ETHTCP_TMR_LASTACK_E:
		{
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
			/* If RTO has not been calculated yet */
			if( lTcpDynSockTbl_pst->Rto_u32 == 0U )
			{
				/* Use statically configured timeout */
				lTimeOut_u32 = rba_EthTcp_CurrConfig_cpo->ReTxTimeOut_u32;
			}
			else
			{
				/* Use calculated RTO */
				lTimeOut_u32 = lTcpDynSockTbl_pst->Rto_u32;
			}
#else
			/* Use statically configured timeout */
			lTimeOut_u32 = rba_EthTcp_CurrConfig_cpo->ReTxTimeOut_u32;
#endif
#endif
		}
		break;

		/* --------------------------- */
		/* FinWait2 timer 	   		   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_FINWAIT2_E:
		{
			/* Use statically configured timeout */
			lTimeOut_u32 = rba_EthTcp_CurrConfig_cpo->FinWait2TimeOut_u32;
		}
		break;

		/* --------------------------- */
		/* TimeWait timer 	   		   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_TIMEWAIT_E:
		{
			/* TimeWait TimeOut = 2*MSL */
			lTimeOut_u32 = (uint32)( rba_EthTcp_CurrConfig_cpo->TcpMsl_u32 << 1U );
		}
		break;

		/* --------------------------- */
		/* Keep Alive timer    		   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_KEEPALIVE_E:
		{
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
		    if( lTcpDynSockTbl_pst->KeepAlvRetryCntr_u16 == 0U )
		    {
		        /* KeepAlive Time as timeout for the first probe */
		        lTimeOut_u32 = lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvTime_u32;
		    }
		    else
		    {
		        /* KeepAlive Interval as timeout for successive probes */
		        lTimeOut_u32 = lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvIntl_u32;
		    }
#endif
		}
		break;

		/* --------------------------- */
		/* Delayed Ack timer 		   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_DLYACK_E:
		{
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
			lTimeOut_u32 = rba_EthTcp_CurrConfig_cpo->DlyAckTimeOut_u32;
#endif
		}
		break;

		/* --------------------------- */
		/* User Timeout timer 		   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_UTO_E:
		default:
		{
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
			lTimeOut_u32 = rba_EthTcp_CurrConfig_cpo->UserTimeOut_u32;
#else
			{
		    /*  nothing to do  */
	        }
#endif
		}
		break;
	}

	return lTimeOut_u32;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_GetTimerMaxRetry() 	- By this function, the max retry value of a Tcp timer can be get							**/
/**																																**/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo			    - Tcp dynamic socket table index                                                            **/
/** TmrSt_en		   			    - Timer for which the max retry value should be get											**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					- uint16																				    **/
/**										Max retry value																			**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetTimerMaxRetry(  VAR( TcpIp_SocketIdType, AUTOMATIC )   TcpDynSockTblIdx_uo,
                                                                    VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) TmrSt_en )
{
	/* Declare local variables */
     P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
     VAR( uint16, AUTOMATIC )                                        lMaxRetry_u16;

    /* Get Tcp dynamic table entry from Tcp socket index */
     lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Initialize max retry value to 0 */
     lMaxRetry_u16 = 0U;

	switch( TmrSt_en )
	{
		/* --------------------------- */
		/* SynSent or SynRcvd timer    */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_SYNSENT_E:
		case RBA_ETHTCP_TMR_SYNRCVD_E:
		{
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
		    lMaxRetry_u16 = rba_EthTcp_CurrConfig_cpo->SynMaxRtx_u8;
#endif
		}
		break;

		/* ----------------------------------------- */
		/* ReTx, FinWait1_Closing or LastAck timers  */
		/* ----------------------------------------- */
		case RBA_ETHTCP_TMR_RETX_E:
		case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
		case RBA_ETHTCP_TMR_LASTACK_E:
		{
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
		    lMaxRetry_u16 = rba_EthTcp_CurrConfig_cpo->TcpMaxRtx_u8;
#endif
		}
		break;

		/* --------------------------- */
		/* Zwp timer  				   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_ZWP_E:
		{
#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
		    lMaxRetry_u16 = rba_EthTcp_CurrConfig_cpo->ZWPMaxRetries_u8;
#endif
		}
		break;

		/* --------------------------- */
		/* Keep Alive timer    		   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_KEEPALIVE_E:
		{
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
			lMaxRetry_u16 = lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvProbesMax_u16;
#endif
		}
		break;

		/* --------------------------- */
		/* Other timers	   		   	   */
		/* --------------------------- */
		case RBA_ETHTCP_TMR_FINWAIT2_E:
		case RBA_ETHTCP_TMR_TIMEWAIT_E:
		case RBA_ETHTCP_TMR_DLYACK_E:
		case RBA_ETHTCP_TMR_UTO_E:
		default:
		{
			/* nothing to do */
		}
		break;
	}

	return lMaxRetry_u16;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ActionAfterMaxRetry()    - Execute actions after max retry of the timer is reached                               **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index                                                        **/
/** TmrSt_en                            - Timer for which the max retry value is reached                                        **/
/**                                                                                                                             **/
/** Parameters (inout):                 None                                                                                    **/
/**                                                                                                                             **/
/** Parameters (out):                   None                                                                                    **/
/**                                                                                                                             **/
/** Return value:                       None                                                                                    **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_ActionAfterMaxRetry(    VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                        VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC )      TmrSt_en )
{
    switch( TmrSt_en )
    {
        /* --------------------------- */
        /* SynSent timer               */
        /* --------------------------- */
        case RBA_ETHTCP_TMR_SYNSENT_E:
        {
            /* Send a RST in the next MainFunction */
            /* (the ACK cannot be set in the reset frame because we are in SYN SENT state, no frame have been received from the remote yet) */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_E );
        }
        break;

        /* -------------------------------------------------------------------------- */
        /* SynRcvd, ReTx, Zwp, FinWait1_Closing, FinWait2, LastAck or KeepAlive timer */
        /* -------------------------------------------------------------------------- */
        case RBA_ETHTCP_TMR_SYNRCVD_E:
        case RBA_ETHTCP_TMR_RETX_E:
        case RBA_ETHTCP_TMR_ZWP_E:
        case RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E:
        case RBA_ETHTCP_TMR_FINWAIT2_E:
        case RBA_ETHTCP_TMR_LASTACK_E:
        case RBA_ETHTCP_TMR_KEEPALIVE_E:
        {
            /* Send a RST ACK in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );
        }
        break;

        /* --------------------------- */
        /* TimeWait timer              */
        /* --------------------------- */
        case RBA_ETHTCP_TMR_TIMEWAIT_E:
        default:
        {
            /* Connection is finished, we have to return to the CLOSED state */
            rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_CLOSED );
        }
        break;
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_BackOffRto() 	- This function execute the exponential backing off of the retransmission timeout (RTO). The 	**/
/**								backing off is needed when the dynamic retransmission feature is enabled (see RFC6298).			**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		- Tcp dynamic socket table index																**/
/** CurrentTimeOut_u32 			- Current retransmission timeout value															**/
/**																																**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):			None																							**/
/**																																**/
/** Return value:				None																							**/
/**																																**/
/*********************************************************************************************************************************/
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
static FUNC( void , RBA_ETHTCP_CODE ) rba_EthTcp_BackOffRto(    VAR( TcpIp_SocketIdType , AUTOMATIC ) 	TcpDynSockTblIdx_uo,
                                                                VAR( uint32, AUTOMATIC ) 	            CurrentTimeOut_u32 )

{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 			lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Exponential back off */
	/* (Rto = 2 * CurrentTimeOut) */
	lTcpDynSockTbl_pst->Rto_u32 = (uint32)( CurrentTimeOut_u32 << 1U );

	/* Limit the RTO below configured upper boundary seconds */
	if( lTcpDynSockTbl_pst->Rto_u32 > rba_EthTcp_CurrConfig_cpo->ReTxTimerUprBound_u32 )
	{
		lTcpDynSockTbl_pst->Rto_u32 = rba_EthTcp_CurrConfig_cpo->ReTxTimerUprBound_u32;
	}

	/* Check if the timer has been backed off multiple times*/
	if( lTcpDynSockTbl_pst->GeneralRetryCntr_u8 > 1U )
	{
		/* As explained in RFC6298, SRTT and RTTVAR should be reset */
		lTcpDynSockTbl_pst->SRtt_u32 = 0U;
		lTcpDynSockTbl_pst->RttVar_u32 = 0U;
	}

	return;
}
#endif


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */


















