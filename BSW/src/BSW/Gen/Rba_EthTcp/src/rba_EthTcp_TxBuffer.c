

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
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_MoveTxBufPointer( 	VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpDynSockTblIdx_uo,
																	VAR( uint16, AUTOMATIC ) 				Len_u16,
																	P2VAR( uint8*, AUTOMATIC, AUTOMATIC ) 	TxBufPointer_ppu8 );
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
/** rba_EthTcp_SetTxBufBeforeTx() 	- This function is used to move the TxWndNxtFree pointer (points to the next free location	**/
/**									in the Tx buffer). This function should be called before the sending of new data (when the 	**/
/**									new data are added in the Tcp Tx buffer).													**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/** Len_u16							- Length of data that have been added														**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					None																						**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetTxBufBeforeTx( 	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
															VAR( uint16, AUTOMATIC ) Len_u16 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Move the TxWndNxtFree pointer by the length given in argument of the function */
	rba_EthTcp_MoveTxBufPointer( 	TcpDynSockTblIdx_uo,
									Len_u16,
									&lTcpDynSockTbl_pst->TxWndNxtFree_pu8 );

	/* Update the occupied size of the Tcp Tx buffer */
	lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 += Len_u16;

	return;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_SetTxBufBeforeReTx() - This function is used to move the TxWndNxtSend pointer (points to the location where next **/
/** 								data to be sent are stored in the Tx buffer). This function should be called before  		**/
/**									executing a retransmission.																	**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					None																						**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetTxBufBeforeReTx( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* To retransmit unacknowledged data, we need to move the TxWndNxtSnd pointer to the beginning of the unacknowledged data location in the Tcp Tx buffer */
	lTcpDynSockTbl_pst->TxWndNxtSnd_pu8 = lTcpDynSockTbl_pst->TxWndUnAckedData_pu8;

	/* Update the occupied size of the Tcp Tx buffer */
	lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 += lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16;
	lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16 = 0U;

	return;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_SetTxBufAfterTx() 	- This function is used to move the TxWndNxtSend pointer (points to the location where next **/
/** 								data to be sent are stored in the Tx buffer). This function should be called after some  	**/
/**									data have been sent. 																		**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/** Len_u16							- Length of data that have been sent														**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					None																						**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetTxBufAfterTx(	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
															VAR( uint16, AUTOMATIC ) Len_u16 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Move the TxWndNxtSnd pointer by the length given in argument of the function */
	rba_EthTcp_MoveTxBufPointer( 	TcpDynSockTblIdx_uo,
									Len_u16,
									&lTcpDynSockTbl_pst->TxWndNxtSnd_pu8 );

	/* Update the occupied size of the Tcp Tx buffer */
	lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 -= Len_u16;
	lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16 += Len_u16;

	return;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_SetTxBufAfterAcked() - This function is used to move the TxWndUnAckedData pointer (points to the location where 	**/
/** 								unacknowledged data are stored in the Tx buffer). This function should be called after some **/
/**									data have been acknowledged by the remote.													**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/** Len_u16							- Length of data that have been acknowledged												**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					None																						**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetTxBufAfterAcked(	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
																VAR( uint16, AUTOMATIC ) Len_u16 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Move the TxWndUnAckedData pointer by the length given in argument of the function */
	rba_EthTcp_MoveTxBufPointer( 	TcpDynSockTblIdx_uo,
									Len_u16,
									&lTcpDynSockTbl_pst->TxWndUnAckedData_pu8 );

	/* Update the occupied size of the Tcp Tx buffer */
	lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16 -= Len_u16;

	return;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_GetTxBufFreeLen()	- This function is used to get the total size of the free location in the Tx buffer			**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					- uint16																					**/
/** 									Total size of the free location 														**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetTxBufFreeLen( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( uint16, AUTOMATIC ) 										lTotalFreeLen_u16;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Compute the total free location in the Tcp Tx buffer */
	lTotalFreeLen_u16 = ( RBA_ETHTCP_TXWNDSIZE - lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 - lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16 );

	return lTotalFreeLen_u16;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_GetTxBufLnrFreeLen() - This function is used to get the size of the next linear free location in the Tx buffer	**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					- uint16																					**/
/** 									Total size of the next linear free location 											**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetTxBufLnrFreeLen( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( uint16, AUTOMATIC ) 										lLnrFreeLen_u16;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Initialize linear free length to 0 */
    lLnrFreeLen_u16 = 0U;

    /* If there is free length */
    if( (RBA_ETHTCP_TXWNDSIZE - lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 - lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16) > 0U )
    {
        /* No buffer boundary crossing case */
        /* (free location is composed of one block in the buffer) */
        if ( lTcpDynSockTbl_pst->TxWndUnAckedData_pu8 > lTcpDynSockTbl_pst->TxWndNxtFree_pu8 )
        {
            lLnrFreeLen_u16 = ( RBA_ETHTCP_TXWNDSIZE - lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 - lTcpDynSockTbl_pst->TxOccupiedSizeUnacked_u16 );
        }

        /* Buffer boundary crossing case */
        /* (free location is composed of two blocks in the buffer) */
        else
        {
            lLnrFreeLen_u16 = ( RBA_ETHTCP_TXWNDSIZE - (uint16)(lTcpDynSockTbl_pst->TxWndNxtFree_pu8 - lTcpDynSockTbl_pst->TxWndStrt_pu8) );
        }
    }

	return lLnrFreeLen_u16;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_GetTxBufSndLen() - This function is used to get the total size of the send location in the Tx buffer				**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo			- Tcp dynamic socket table index																**/
/**																																**/
/** Parameters (inout):			None																							**/
/**																																**/
/** Parameters (out):			None																							**/
/**																																**/
/** Return value:				- uint16																						**/
/** 								Total size of the send location 															**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetTxBufSndLen( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	VAR( uint16, AUTOMATIC ) 			lTotalSndLen_u16;

	/* Compute the total send location in the Tcp Tx buffer */
	lTotalSndLen_u16 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TxOccupiedSizeSnd_u16;

	return lTotalSndLen_u16;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_GetTxBufLnrSndLen() 	- This function is used to get the size of the next linear send location in the Tx buffer	**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/**																																**/
/** Parameters (inout):				  None																						**/
/**																																**/
/** Parameters (out):				  None																						**/
/**																																**/
/** Return value:					- uint16																					**/
/** 									Total size of the next linear send location 											**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetTxBufLnrSndLen( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( uint16, AUTOMATIC ) 										lLnrSndLen_u16;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	=	( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Initialize linear send length to 0 */
    lLnrSndLen_u16 = 0U;

    /* If there is send length */
    if( lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 > 0U )
    {
        /* No buffer boundary crossing case */
        /* (send location is composed of one block in the buffer) */
        if ( lTcpDynSockTbl_pst->TxWndNxtFree_pu8 > lTcpDynSockTbl_pst->TxWndNxtSnd_pu8 )
        {
            lLnrSndLen_u16 = lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16;
        }

        /* Buffer boundary crossing case */
        /* (send location is composed of two blocks in the buffer) */
        else
        {
            lLnrSndLen_u16 = ( lTcpDynSockTbl_pst->TxOccupiedSizeSnd_u16 - (uint16)(lTcpDynSockTbl_pst->TxWndNxtFree_pu8 - lTcpDynSockTbl_pst->TxWndStrt_pu8) );
        }
    }

	return lLnrSndLen_u16;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_GetTxBufUnackedLen() - This function is used to get the total size of the unacked location in the Tx buffer		**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo				- Tcp dynamic socket table index															**/
/**																																**/
/** Parameters (inout):				  None																						**/
/**																																**/
/** Parameters (out):				  None																						**/
/**																																**/
/** Return value:					- uint16																					**/
/** 								  Total size of the unacked location 														**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetTxBufUnackedLen( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	VAR( uint16, AUTOMATIC ) 									lTotalUnackedLen_u16;

	/* Compute the total unacked location in the Tcp Tx buffer */
	lTotalUnackedLen_u16 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TxOccupiedSizeUnacked_u16;

	return lTotalUnackedLen_u16;
}
#endif


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_MoveTxBufPointer() 	- This function is used to move a Tcp Tx buffer pointer (advance the pointer by the length 	**/
/**									  given in argument of the function)														**/
/**																																**/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo		        - Tcp dynamic socket table index															**/
/** Len_u16							- Length for the moving																		**/
/**																																**/
/** Parameters (inout):																											**/
/** TxBufPointer_ppu8				- Tcp Tx buffer pointer that need to be advanced											**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					None																						**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_MoveTxBufPointer(   VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
															        VAR( uint16, AUTOMATIC ) 				Len_u16,
															        P2VAR( uint8*, AUTOMATIC, AUTOMATIC ) 	TxBufPointer_ppu8 )
{
	/* Declare local variables */
	P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 					lPointerToMove_pu8;

	/* Get the pointer to move */
	lPointerToMove_pu8 = ( * (uint8 **)TxBufPointer_ppu8 );

	/* No buffer boundary crossing case */
	/* (the pointer stay in the buffer space) */
	if ( (lPointerToMove_pu8 + Len_u16) < (rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TxWndStrt_pu8 + RBA_ETHTCP_TXWNDSIZE) )
	{
		lPointerToMove_pu8 += Len_u16;
	}

	/* Buffer boundary crossing case */
	/* (the pointer goes out the buffer space) */
	else
	{
		lPointerToMove_pu8 = ( (lPointerToMove_pu8 + Len_u16) - RBA_ETHTCP_TXWNDSIZE );
	}

	/* Set the out argument of the function (advanced pointer) */
	( * (uint8 **)TxBufPointer_ppu8 ) = lPointerToMove_pu8;

	return;
}
#endif


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */


















