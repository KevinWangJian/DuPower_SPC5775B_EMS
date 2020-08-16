

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
 * Interface functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_Listen() - By this API, the rba_EthTcp module is requested to listen on the TCP socket specified by the Tcp  	**/
/**						  socket id																				                **/
/**																																**/
/**	Parameters (in):																											**/
/** TcpSockId_uo		- Tcp socket id																				            **/
/** MaxChannels_u16 	- Maximum number of new parallel connections established on this listen connection						**/
/**																																**/
/** Parameters (inout):	None																									**/
/**																																**/
/** Parameters (out):	None																									**/
/**																																**/
/** Return value:		- Std_ReturnType																						**/
/** 						E_OK: The request has been accepted																	**/
/** 						E_NOT_OK: The request has not been accepted															**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_Listen( 	VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpSockId_uo,
															VAR( uint16, AUTOMATIC ) 				MaxChannels_u16 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	    lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 								    lFunctionRetVal_en;
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
    rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_E_LISTEN, RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if TcpSockId_uo is invalid */
    rba_EthTcp_CheckDetError( (TcpSockId_uo >= TCPIP_TCPSOCKETMAX), RBA_ETHTCP_E_LISTEN, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if MaxChannels_u16 is not in the right range */
    rba_EthTcp_CheckDetError( ((MaxChannels_u16 == 0U) || (MaxChannels_u16 >= TCPIP_TCPSOCKETMAX)) , RBA_ETHTCP_E_LISTEN, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Get Tcp dynamic table entry from Tcp socket index */
	    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpSockId_uo] ) );

	    /* Check if the Tcp socket is bound */
        if ( lTcpDynSockTbl_pst->SockState_en == RBA_ETHTCP_SOCK_BOUND_E )
        {
            /* -------------------------------------------- */
            /* Listen for Tcp socket in CLOSED state		*/
            /* -------------------------------------------- */
            if ( lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSED_E )
            {
                /* Check if requested number of client connections (MaxChannels_u16) is available */
                if ( MaxChannels_u16 <= (TCPIP_TCPSOCKETMAX - rba_EthTcp_SockConnCntr_u16) )
                {
                    /* Set the connection state of the Tcp socket to LISTEN */
                    rba_EthTcp_SetConnectionState( TcpSockId_uo, RBA_ETHTCP_CONN_LISTEN_E );

                    /* Now socket is ready to accept incoming connection requests */
                    lTcpDynSockTbl_pst->SockState_en = RBA_ETHTCP_SOCK_OPENED_E;

                    /* Set the number of remaining channels in the Tcp dynamic table entry of the listening socket */
                    lTcpDynSockTbl_pst->RemainChannels_u16 = MaxChannels_u16;

                    /* Set the return value of the function to E_OK */
                    lFunctionRetVal_en = E_OK;
                }
            }
        }
	}

	return lFunctionRetVal_en;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */



















