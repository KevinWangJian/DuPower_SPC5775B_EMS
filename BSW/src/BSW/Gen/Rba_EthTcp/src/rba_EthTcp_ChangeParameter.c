

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "TcpIp_Lib.h"
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
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeWindowSizeParameter	( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																					  P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 	ParamValue_cpu8 );

#if ( RBA_ETHTCP_NAGLE_ENABLED == STD_ON )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeNagleParameter		( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																					  P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 	ParamValue_cpu8 );
#endif

#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeKeepAliveParameter	( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
                                                                                      VAR( TcpIp_ParamIdType, AUTOMATIC )       ParamId_u8,
																					  P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 	ParamValue_cpu8 );
#endif

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeFramePrioParameter	( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																					  P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 	ParamValue_cpu8 );
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
/** rba_EthTcp_ChangeParameter() 	- By this API, the rba_EthTcp module is requested to change a parameter of a socket.		**/
/** 								E.g. the Nagle algorithm may be controlled by this API.										**/
/**																																**/
/** Parameters (in):																											**/
/**  TcpSockId_uo				    - Tcp Socket id															                    **/
/**  ParamId_u8						- Identifier of the parameter to be changed													**/
/**  ParamValue_cpu8				- Pointer to memory containing the new parameter value                                      **/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					- Std_ReturnType																			**/
/** 									E_OK : The parameter has been changed successfully										**/
/** 									E_NOT_OK : The parameter could not be changed.											**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeParameter(	VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpSockId_uo,
																	VAR( TcpIp_ParamIdType, AUTOMATIC )  	    ParamId_u8,
																	P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 	    ParamValue_cpu8 )
{
	/* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )    lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 								lFunctionRetVal_en;
#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    VAR( boolean, AUTOMATIC )                                       lDetErrorFlag_b;
#endif

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
    /* Set DET error flag to FALSE */
    lDetErrorFlag_b = FALSE;

    /* Check for DET errors */
    /* Report DET if rba_EthTcp module is uninitialized */
    rba_EthTcp_CheckDetError( (rba_EthTcp_InitFlag_b == FALSE), RBA_ETHTCP_E_CHANGEPARAMETER, RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if TcpSockId_uo is invalid */
    rba_EthTcp_CheckDetError( (TcpSockId_uo >= TCPIP_TCPSOCKETMAX), RBA_ETHTCP_E_CHANGEPARAMETER, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if ParamValue_cpu8 is NULL pointer */
    rba_EthTcp_CheckDetError( (ParamValue_cpu8 == NULL_PTR), RBA_ETHTCP_E_CHANGEPARAMETER, RBA_ETHTCP_E_NULL_PTR, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Get Tcp dynamic table entry from Tcp socket index */
        lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpSockId_uo] ) );

        /* Process only when the socket is not CLOSED and not RESERVED */
        /* (UL does not have access to a socket which is CLOSED or RESERVED) */
        if( (lTcpDynSockTbl_pst->SockState_en != RBA_ETHTCP_SOCK_CLOSED_E) && (lTcpDynSockTbl_pst->SockState_en != RBA_ETHTCP_SOCK_RESERVED_E) )
        {
            switch(ParamId_u8)
            {
                /* ------------------------------------ */
                /* Change the Window size parameter 	*/
                /* ------------------------------------ */
                case TCPIP_PARAMID_TCP_RXWND_MAX :
                {
					lFunctionRetVal_en = rba_EthTcp_ChangeWindowSizeParameter( TcpSockId_uo, ParamValue_cpu8 );
                }
                break;

                /* ------------------------------------ */
                /* Change the Nagle Algorithm parameter */
                /* ------------------------------------ */
                case TCPIP_PARAMID_TCP_NAGLE :
                {
#if ( RBA_ETHTCP_NAGLE_ENABLED == STD_ON )
					lFunctionRetVal_en = rba_EthTcp_ChangeNagleParameter( TcpSockId_uo, ParamValue_cpu8 );
#endif
                }
                break;

                /* ------------------------------------ */
                /* Change the Keep Alive parameter 		*/
                /* ------------------------------------ */
                case TCPIP_PARAMID_TCP_KEEPALIVE :
                case TCPIP_PARAMID_TCP_KEEPALIVE_TIME :
                case TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX :
                case TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL :
                {
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
					lFunctionRetVal_en = rba_EthTcp_ChangeKeepAliveParameter( TcpSockId_uo,ParamId_u8, ParamValue_cpu8 );
#endif
                }
                break;

                /* ------------------------------------ */
                /* Change the Frame priority            */
                /* ------------------------------------ */
                case TCPIP_PARAMID_FRAMEPRIO :
                {
					lFunctionRetVal_en = rba_EthTcp_ChangeFramePrioParameter( TcpSockId_uo, ParamValue_cpu8 );
                }
                break;

                /* ------------------------------------ */
                /* Invalid param id 					*/
                /* ------------------------------------ */
                default :
                {
			        /* nothing to do */
                }
                break;
            }
        }

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
        /* Report DET error in case the parameter has not been changed successfully */
        /* (this occurs when argument is invalid) */
        rba_EthTcp_CheckDetError( (lFunctionRetVal_en == E_NOT_OK), RBA_ETHTCP_E_CHANGEPARAMETER, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
#endif
	}

	return lFunctionRetVal_en;
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_ChangeWindowSizeParameter	- Execute the changing of the TCPIP_PARAMID_TCP_RXWND_MAX parameter					**/
/**																																**/
/**	Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 					- Tcp dynamic socket table index													**/
/** ParamValue_cpu8							- Pointer to memory containing the new parameter value                   			**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):						None																				**/
/**																																**/
/** Return value:                			- Std_ReturnType                                                                    **/
/**                                 			E_OK: Parameter is changed                                               		**/
/**                                 			E_NOT_OK: Socket is not changed                                              	**/
/**                                                                                                                  			**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeWindowSizeParameter( 	VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																						P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 		ParamValue_cpu8 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 								lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry at index lIdx_u8 */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Check if the Tcp socket is CLOSED or LISTEN state */
	/* (the changing of the default window size is allowed before socket is in communication) */
	/* (when the socket is in communication, it is not possible to change the default window size anymore) */
    if( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSED_E)     ||
        (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_LISTEN_E) )
    {
        /* ------------------------------------ */
        /* Change default local window size     */
        /* ------------------------------------ */

        /* Overwrite statically configured default local window size with the value provided by SoAd */
        TcpIp_ReadU16( ParamValue_cpu8, &( lTcpDynSockTbl_pst->TcpSockOpt_pst->SORxWindowMax_u16 ) );

        /* ------------------------------------ */
        /* Change current local window size     */
        /* ------------------------------------ */

        /* Update the initial send window size in the Tcp socket */
        TcpIp_ReadU16( ParamValue_cpu8, &(lTcpDynSockTbl_pst->SndWndSize_u16) );

        /* Set the return value of the function to E_OK */
        lFunctionRetVal_en = E_OK;
	}

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_ChangeNagleParameter		- Execute the changing of the TCPIP_PARAMID_TCP_NAGLE parameter							**/
/**																																**/
/**	Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 				- Tcp dynamic socket table index														**/
/** ParamValue_cpu8						- Pointer to memory containing the new parameter value       	            			**/
/**																																**/
/** Parameters (inout):					None																					**/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:                		- Std_ReturnType                                                                    	**/
/**                                 		E_OK: Parameter is changed                                               			**/
/**                                 		E_NOT_OK: Socket is not changed                                              		**/
/**                                                                                                                  			**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_NAGLE_ENABLED == STD_ON )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeNagleParameter( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																				P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 		ParamValue_cpu8 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 								lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry at index lIdx_u8 */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Check if the Param Value is valid */
	if( ((*ParamValue_cpu8) == STD_ON) || ((*ParamValue_cpu8) == STD_OFF) )
	{
		/* Enable/Disable Nagle Algorithm of the socket */
		lTcpDynSockTbl_pst->TcpSockOpt_pst->SONaglesEnad_u8 = (*ParamValue_cpu8);

		/* Set the return value of the function to E_OK */
		lFunctionRetVal_en = E_OK;
	}

	return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_ChangeKeepAliveParameter	- Execute the changing of the TCPIP_PARAMID_TCP_KEEPALIVE parameter						**/
/**																																**/
/**	Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 				- Tcp dynamic socket table index                                                        **/
/** ParamId_u8							- Identifier of the parameter to be changed                                             **/
/** ParamValue_cpu8						- Pointer to memory containing the new parameter value       	            			**/
/**																																**/
/** Parameters (inout):					None																					**/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:                		- Std_ReturnType                                                                    	**/
/**                                 		E_OK: Parameter is changed                                               			**/
/**                                 		E_NOT_OK: Socket is not changed                                              		**/
/**                                                                                                                  			**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeKeepAliveParameter( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
                                                                                    VAR( TcpIp_ParamIdType, AUTOMATIC )         ParamId_u8,
																					P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 		ParamValue_cpu8 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 								lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry at index lIdx_u8 */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	switch(ParamId_u8)
	{
        /* ------------------------------------ */
        /* Change the Keep Alive parameter      */
        /* ------------------------------------ */
        case TCPIP_PARAMID_TCP_KEEPALIVE :

        /* Check if the Param Value is valid */
        if( ((*ParamValue_cpu8) == STD_ON) || ((*ParamValue_cpu8) == STD_OFF) )
        {
            /* -------------------------------------------- */
            /* Enable or disabled Keep Alive for the socket */
            /* -------------------------------------------- */

            /* Enable/Disable Keep Alive feature of the socket */
            lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvEnad_u8 = (*ParamValue_cpu8);

            /* ------------------------------------ */
            /* Start stop Keep Alive timer          */
            /* ------------------------------------ */

            /* If Keep Alive is now enabled for this socket */
            if ( lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvEnad_u8 == STD_ON )
            {
                /* If we are in a state where the Keep Alive timer is able to run */
                if( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_ESTABLISHED_E) 	||
                    (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_FIN_WAIT_1_E)		||
                    (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_FIN_WAIT_2_E)		||
                    (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSING_E)			||
                    (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSE_WAIT_E)		||
                    (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_LAST_ACK_E) )
                {
                    /* Start the Keep Alive timer */
                    rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
                }
            }
            else
            {
                /* Stop the Keep Alive timer */
                rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_KEEPALIVE_E );
            }

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
        break;

        /* ------------------------------------ */
        /* Change the keep alive time           */
        /* ------------------------------------ */
        case TCPIP_PARAMID_TCP_KEEPALIVE_TIME :
        {
           /* Overwrite statically configured maximum KeepAliveTime (KeepAlvTime_u32) with the value provided by SoAd */
            TcpIp_ReadU32( ParamValue_cpu8, &( lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvTime_u32 ) );

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
        break;

        /* ------------------------------------ */
        /* Change the keep alive probes allowed */
        /* ------------------------------------ */
        case TCPIP_PARAMID_TCP_KEEPALIVE_PROBES_MAX :
        {
            /* Overwrite statically configured maximum probes (KeepAlvProbesMax_u16) with the value provided by SoAd */
            TcpIp_ReadU16( ParamValue_cpu8, &( lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvProbesMax_u16 ) );

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
        break;

        /* ------------------------------------ */
        /* Change the keep alive interval       */
        /* ------------------------------------ */
        case TCPIP_PARAMID_TCP_KEEPALIVE_INTERVAL :
        default :
        {
            /* Overwrite statically configured keepAliveInterVal(KeepAlvIntl_u32) with the value provided by SoAd */
            TcpIp_ReadU32( ParamValue_cpu8, &( lTcpDynSockTbl_pst->TcpSockOpt_pst->SOKeepAlvIntl_u32 ) );

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
        break;
	}

	return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_ChangeFramePrioParameter		- Execute the changing of the TCPIP_PARAMID_TCP_FRAMEPRIO parameter					**/
/**																																**/
/**	Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 					- Tcp dynamic socket table index													**/
/** ParamValue_cpu8							- Pointer to memory containing the new parameter value                   			**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):						None																				**/
/**																																**/
/** Return value:                			- Std_ReturnType                                                                    **/
/**                                 			E_OK: Parameter is changed                                               		**/
/**                                 			E_NOT_OK: Socket is not changed                                              	**/
/**                                                                                                                  			**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ChangeFramePrioParameter( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																					P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 		ParamValue_cpu8 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 								lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry at index lIdx_u8 */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* Check if the Param Value is valid */
	/* (FramePrio is a 3 bit field in Vlan header, it's maximum value is 7) */
	if( (*ParamValue_cpu8) <= TCPIP_FRAMEPRIO_MAXVAL )
	{
	   /* Overwrite statically configured FramePrio (TcpIpIpFramePrioDefault) with the value provided by SoAd */
	   lTcpDynSockTbl_pst->SockFramePrio_u8 =  (*ParamValue_cpu8);

	   /* Set the return value of the function to E_OK */
	   lFunctionRetVal_en = E_OK;
	}

	return lFunctionRetVal_en;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */














