

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "TcpIp.h"

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

#include "SoAd.h"
#include "SoAd_Cbk.h"		/* Required for SoAd call-back functions */

#include "TcpIp_Prv.h"

#include "rba_EthTcp.h"
#include "rba_EthTcp_Prv.h"
#include "rba_BswSrv.h"

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
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_CopyDataValidPointer     ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                                      P2CONST( uint8, AUTOMATIC, AUTOMATIC )    TxData_cpu8,
                                                                                      VAR( uint16, AUTOMATIC )                  AvlLen_u16,
                                                                                      P2VAR( uint16, AUTOMATIC, AUTOMATIC )     CopiedLength_pu16 );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_CopyDataNullPointer      ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                                      VAR( uint16, AUTOMATIC )                  AvlLen_u16,
                                                                                      VAR( boolean, AUTOMATIC )                 ForceRetrieve_b,
                                                                                      P2VAR( uint16, AUTOMATIC, AUTOMATIC )     CopiedLength_pu16 );

static FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_UpdateSocketAfterCopy    ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                                      VAR( uint16, AUTOMATIC )                  CopiedLen_u16 );
#endif
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
/** rba_EthTcp_Transmit()	- This service requests transmission of TCP data to a remote node. The transmission of the data is 	**/
/**							decoupled. The parameter AvailableLength indicates the length of data to be transmitted. Tcp shall	**/
/** 						retrieve data from SoAd via one or more subsequent SoAd_CopyTxData() calls within the context of	**/
/**							this transmit function call. Tcp shall retrieve exactly AvailableLength bytes from the SoAd if the 	**/
/**							parameter ForceRetrieve_b is TRUE, otherwise the Tcp may retrieve less data. Note: The Tcp 			**/
/**							segment(s) are sent dependent on runtime factors e.g. receive window) and configuration parameter	**/
/**							(e.g. Nagle algorithm) . If the socket has not been bound to a local resource via a previous call 	**/
/**							to TcpIp_Bind() the local IP address and port used for transmission is selected by TcpIp 			**/
/**																																**/
/** Parameters (in):																											**/
/** TcpSockId_uo			- Tcp socket id       																			    **/
/** TxData_cpu8      	   	- Pointer to a linear buffer containing the data to be transmitted									**/
/** AvlLen_u32	 		   	- Available data for transmission in bytes															**/
/** ForceRetrieve_b   		- This parameter is only valid if TxData_pu8 is a NULL_PTR											**/
/** 						Indicates how the TCP/IP stack retrieves data from SoAd if TxData_pu8 is a NULL_PTR					**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:			Std_ReturnType																						**/
/** 							E_OK: The request has been accepted																**/
/** 							E_NOT_OK: The request has not been accepted														**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_Transmit( 	VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpSockId_uo,
																P2CONST( uint8, AUTOMATIC, AUTOMATIC )		TxData_cpu8,
																VAR( uint32, AUTOMATIC ) 					AvlLen_u32,
																VAR( boolean, AUTOMATIC ) 					ForceRetrieve_b )
{
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 	    lTcpDynSockTbl_pst;
	VAR( uint16, AUTOMATIC ) 										    lCopiedLength_u16;
	VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;
	VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_en;
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
    rba_EthTcp_CheckDetError( ( rba_EthTcp_InitFlag_b == FALSE ), RBA_ETHTCP_E_TRANSMIT, RBA_ETHTCP_E_NOTINIT, &lDetErrorFlag_b );
    /* Report DET if TcpSockId_u16 is invalid */
    rba_EthTcp_CheckDetError( (TcpSockId_uo >= TCPIP_TCPSOCKETMAX), RBA_ETHTCP_E_TRANSMIT, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );
    /* Report DET if AvlLen_u32 is equal to 0 */
    rba_EthTcp_CheckDetError( (AvlLen_u32 == 0U), RBA_ETHTCP_E_TRANSMIT, RBA_ETHTCP_E_INV_ARG, &lDetErrorFlag_b );

    /* In case no DET error occured */
    if( lDetErrorFlag_b == FALSE )
#endif
    {
        /* Get Tcp dynamic table entry from Tcp socket index */
        lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpSockId_uo] ) );

        /* If the current state of the Tcp socket allow the Transmit call */
        /* In SYN_RCVD, ESTABLISHED and CLOSE_WAIT states, we also check that the Upper Layer has not closed the connection yet (there is no FIN ACK going to be sent and no FIN ACK postponed to be sent) */
        if ( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_SYN_SENT_E)       ||
             ((lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_SYN_RCVD_E) && (lTcpDynSockTbl_pst->PostponeFin_b == FALSE))                                                                     ||
             ((lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_ESTABLISHED_E) && (lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_FIN_ACK_E) && (lTcpDynSockTbl_pst->PostponeFin_b == FALSE)) ||
             ((lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSE_WAIT_E) && (lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_FIN_ACK_E) && (lTcpDynSockTbl_pst->PostponeFin_b == FALSE)) )
        {
            /* If no RESET is going to be sent by the Tcp socket and received MSS is greater than 0 */
            /* (once a reset is prepared to be sent it is not possible to call the Transmit API anymore) */
            /* (in case the received MSS is equal to 0 that means the the remote is not able to receive frames with data) */
            if( (lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_RST_E)       &&
                (lTcpDynSockTbl_pst->TcpFlag_en != RBA_ETHTCP_SEND_RST_ACK_E)   &&
                (lTcpDynSockTbl_pst->RcvdMss_u16 > 0U) )
            {
                /* ---------------------------- */
                /* Copy data (valid pointer)    */
                /* ---------------------------- */
                if ( TxData_cpu8 != NULL_PTR )
                {
                    /* Copy data to transmit from SoAd to Tcp with MemCopy */
                    lRetVal_en = rba_EthTcp_CopyDataValidPointer(   TcpSockId_uo,
                                                                    TxData_cpu8,
                                                                    (uint16)(AvlLen_u32),
                                                                    &lCopiedLength_u16 );
                }

                /* ---------------------------- */
                /* Copy data (NULL pointer)     */
                /* ---------------------------- */
                else
                {
                    /* Copy data to transmit from SoAd to Tcp by calling SoAd_CopyTxData */
                    lRetVal_en = rba_EthTcp_CopyDataNullPointer(    TcpSockId_uo,
                                                                    (uint16)(AvlLen_u32),
                                                                    ForceRetrieve_b,
                                                                    &lCopiedLength_u16 );
                }

                /* ---------------------------- */
                /* Update socket                */
                /* ---------------------------- */

                /* If data have been successfully copied to Tcp Tx Buffer */
                if ( lRetVal_en == E_OK )
                {
                    /* Update the variables, pointers and timers */
                    rba_EthTcp_UpdateSocketAfterCopy(   TcpSockId_uo,
                                                        lCopiedLength_u16 );

                    /* Set the return value of the function to E_OK */
                    lFunctionRetVal_en = E_OK;
                }
            }
        }
    }

    return lFunctionRetVal_en;
#else
    (void)TcpSockId_uo;
    (void)TxData_cpu8;
    (void)AvlLen_u32;
    (void)ForceRetrieve_b;

    return E_NOT_OK;
#endif
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_CopyDataValidPointer - Execute the copying of the data to transmit from SoAd to Tcp when valid pointer is given  **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                            **/
/** TxData_cpu8                     - Pointer to a linear buffer containing the data to be copied                               **/
/** AvlLen_u16                      - Available data to be copied in bytes                                                      **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** CopiedLength_pu16               - Length of data copied in the Tcp Tx Buffer                                                **/
/**                                                                                                                             **/
/** Return value:                   - Std_ReturnType                                                                            **/
/**                                     E_OK: Data have been successfully copied from SoAd to Tcp                               **/
/**                                     E_NOT_OK: No data have been copied                                                      **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_CopyDataValidPointer (    VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                                    P2CONST( uint8, AUTOMATIC, AUTOMATIC )      TxData_cpu8,
                                                                                    VAR( uint16, AUTOMATIC )                    AvlLen_u16,
                                                                                    P2VAR( uint16, AUTOMATIC, AUTOMATIC )       CopiedLength_pu16 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( uint16, AUTOMATIC )                                            lFreeLen_u16;
    VAR( uint16, AUTOMATIC )                                            lLnrFreeLen_u16;
    VAR( uint16, AUTOMATIC )                                            lLenToCopy_u16;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* -------------------------------------------------- */
    /* Check if there is free space in the Tcp Tx buffer  */
    /* -------------------------------------------------- */

    /* Get the total free location in the Tcp Tx buffer */
    lFreeLen_u16 = rba_EthTcp_GetTxBufFreeLen( TcpDynSockTblIdx_uo );

    /* If the free location is greater than 0 */
    if ( lFreeLen_u16 > 0U )
    {
        /* ---------------------------------------- */
        /* Compute the size of data to copy         */
        /* ---------------------------------------- */

        /* If all the data from SoAd can be copied in the Tcp Tx buffer */
        if ( AvlLen_u16 <= lFreeLen_u16 )
        {
            lLenToCopy_u16 = AvlLen_u16;
        }

        /* There is not enough free space in the Tcp Tx buffer for all the data */
        else
        {
            lLenToCopy_u16 = 0U;
        }

        /* ------------------------------ */
        /* Execute the copying            */
        /* ------------------------------ */

        /* If there are some data to be copied */
        if ( lLenToCopy_u16 > 0U )
        {
            /* Get the size of the next linear free location in the Tcp Tx buffer */
            lLnrFreeLen_u16 = rba_EthTcp_GetTxBufLnrFreeLen( TcpDynSockTblIdx_uo );

            /* If data should be stored into two blocks in the Tcp Tx buffer */
            if ( lLnrFreeLen_u16 < lLenToCopy_u16 )
            {
                /* Copy first part of SoAd data at the end of the Tcp Tx buffer */
                /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
                (void)rba_BswSrv_MemCopy( lTcpDynSockTbl_pst->TxWndNxtFree_pu8,
                                          TxData_cpu8,
                                          lLnrFreeLen_u16 );

                /* The rest data is copied at the beginning of the Tcp Tx buffer */
                /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
                (void)rba_BswSrv_MemCopy( lTcpDynSockTbl_pst->TxWndStrt_pu8,
                                          TxData_cpu8 + lLnrFreeLen_u16,
                                          (lLenToCopy_u16 - lLnrFreeLen_u16) );
            }

            /* If data should be stored in a linear block in the Tcp Tx buffer */
            else
            {
                /* Copy SoAd data into the Tcp Tx buffer */
                /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
                (void)rba_BswSrv_MemCopy( lTcpDynSockTbl_pst->TxWndNxtFree_pu8,
                                          TxData_cpu8,
                                          lLenToCopy_u16 );
            }

            /* Set the length of copied data in out argument of the function */
            ( * CopiedLength_pu16 ) = lLenToCopy_u16;

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_CopyDataNullPointer  - Execute the copying of the data to transmit from SoAd to Tcp when NULL pointer is given   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                            **/
/** AvlLen_u16                      - Available data to be copied in bytes                                                      **/
/** ForceRetrieve_b                 - Indicates if the complete length need to be copied or partial copy is allowed             **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** CopiedLength_pu16               - Length of data copied in the Tcp Tx Buffer                                                **/
/**                                                                                                                             **/
/** Return value:                   - Std_ReturnType                                                                            **/
/**                                     E_OK: Data have been successfully copied from SoAd to Tcp                               **/
/**                                     E_NOT_OK: No data have been copied                                                      **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_CopyDataNullPointer ( VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                                VAR( uint16, AUTOMATIC )                    AvlLen_u16,
                                                                                VAR( boolean, AUTOMATIC )                   ForceRetrieve_b,
                                                                                P2VAR( uint16, AUTOMATIC, AUTOMATIC )       CopiedLength_pu16 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( BufReq_ReturnType, AUTOMATIC )                                 lRetBufReq_en;
    VAR( uint16, AUTOMATIC )                                            lFreeLen_u16;
    VAR( uint16, AUTOMATIC )                                            lLnrFreeLen_u16;
    VAR( uint16, AUTOMATIC )                                            lLenToCopy_u16;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* -------------------------------------------------- */
    /* Check if there is free space in the Tcp Tx buffer  */
    /* -------------------------------------------------- */

    /* Get the total free location in the Tcp Tx buffer */
    lFreeLen_u16 = rba_EthTcp_GetTxBufFreeLen( TcpDynSockTblIdx_uo );

    /* If the free location is greater than 0 */
    if ( lFreeLen_u16 > 0U )
    {
        /* ---------------------------------------- */
        /* Compute the size of data to copy         */
        /* ---------------------------------------- */

        /* If Force Retrieve is FALSE */
        /* (a part of the data to be transmitted can to be retrieved within this function call) */
        if ( ForceRetrieve_b == FALSE )
        {
            /* If all the data from SoAd can be copied in the Tcp Tx buffer */
            if ( AvlLen_u16 <= lFreeLen_u16 )
            {
                lLenToCopy_u16 = AvlLen_u16;
            }

            /* There is not enough free space in the Tcp Tx buffer for all the data */
            else
            {
                lLenToCopy_u16 = lFreeLen_u16;
            }
        }

        /* If Force Retrieve is TRUE */
        /* (all data to be transmitted shall be retrieved within this function call) */
        else
        {
            /* If all the data from SoAd can be copied in the Tcp Tx buffer */
            if ( AvlLen_u16 <= lFreeLen_u16 )
            {
                lLenToCopy_u16 = AvlLen_u16;
            }

            /* There is not enough free space in the Tcp Tx buffer for all the data */
            else
            {
                lLenToCopy_u16 = 0U;
            }

        }

        /* ------------------------------ */
        /* Execute the copying            */
        /* ------------------------------ */

        /* If there are some data to be copied */
        if ( lLenToCopy_u16 > 0U )
        {
            /* Get the size of the next linear free location in the Tcp Tx buffer */
            lLnrFreeLen_u16 = rba_EthTcp_GetTxBufLnrFreeLen( TcpDynSockTblIdx_uo );

            /* If data should be stored into two blocks in the Tcp Tx buffer */
            if ( lLnrFreeLen_u16 < lLenToCopy_u16 )
            {
                /* Copy first part of SoAd data at the end of the Tcp Tx buffer */
                lRetBufReq_en = SoAd_CopyTxData(    TcpDynSockTblIdx_uo,
                                                    lTcpDynSockTbl_pst->TxWndNxtFree_pu8,
                                                    lLnrFreeLen_u16 );

                if ( lRetBufReq_en == BUFREQ_OK )
                {
                    /* The rest data is copied at the beginning of the Tcp Tx buffer */
                    lRetBufReq_en = SoAd_CopyTxData(    TcpDynSockTblIdx_uo,
                                                        lTcpDynSockTbl_pst->TxWndStrt_pu8,
                                                        lLenToCopy_u16 - lLnrFreeLen_u16 );
                }
            }

            /* If data should be stored in a linear block in the Tcp Tx buffer */
            else
            {
                /* Copy SoAd data into the Tcp Tx buffer */
                lRetBufReq_en = SoAd_CopyTxData(    TcpDynSockTblIdx_uo,
                                                    lTcpDynSockTbl_pst->TxWndNxtFree_pu8,
                                                    lLenToCopy_u16 );
            }

            /* If no error occured during the copying of the data using SoAd_CopyTxData */
            if ( lRetBufReq_en == BUFREQ_OK )
            {
                /* Set the length of copied data in out argument of the function */
                ( * CopiedLength_pu16 ) = lLenToCopy_u16;

                /* Set the return value of the function to E_OK */
                lFunctionRetVal_en = E_OK;
            }
        }
    }

    /* If there is no free space in the Tcp Tx buffer */
    else
    {
        /* If no free memory is available then inform SoAd to wait until Tx buffer memory is available */
        /* SoAd shall not terminate the session if SoAd_CopyTxData() is called with length of 0 */
        (void)SoAd_CopyTxData( TcpDynSockTblIdx_uo,
                               lTcpDynSockTbl_pst->TxWndNxtFree_pu8,
                               0U );
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_UpdateSocketAfterCopy    - Update the Tcp socket after the data have been copied in the Tcp Tx Buffer            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index                                                        **/
/** CopiedLen_u16                       - Length of data that has been copied in the Tcp Tx Buffer                              **/
/**                                                                                                                             **/
/** Parameters (inout):                 None                                                                                    **/
/**                                                                                                                             **/
/** Parameters (out):                   None                                                                                    **/
/**                                                                                                                             **/
/** Return value:                       None                                                                                    **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_UpdateSocketAfterCopy ( VAR( TcpIp_SocketIdType, AUTOMATIC )        TcpDynSockTblIdx_uo,
                                                                        VAR( uint16, AUTOMATIC )                    CopiedLen_u16 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( uint16, AUTOMATIC )                                            lUnackedDataLen_u16;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ---------------------------------------- */
    /* Update Tx Buffer pointer                 */
    /* ---------------------------------------- */

    /* Advance the TxWndNxtFree pointer by the length of the copied data */
    rba_EthTcp_SetTxBufBeforeTx( TcpDynSockTblIdx_uo, CopiedLen_u16 );

    /* ---------------------------------------- */
    /* Update next frame and timer              */
    /* ---------------------------------------- */

    /* If we are in ESTABLISHED or CLOSE WAIT state (states for which it is possible to execute the sending of data) */
    if ( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_ESTABLISHED_E)        ||
         (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_CLOSE_WAIT_E) )
    {
        /* Get the length of unacked data in the Tcp Tx buffer */
        lUnackedDataLen_u16 = rba_EthTcp_GetTxBufUnackedLen( TcpDynSockTblIdx_uo );

        /* The window size of the remote is greater than the length of unacknowledged data */
        if ( lTcpDynSockTbl_pst->RcvdWndSize_u16 > lUnackedDataLen_u16 )
        {
            /* Send DATA in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_DATA_E );
        }

#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
        if ( lTcpDynSockTbl_pst->RcvdWndSize_u16 == 0U )
        {
            /* Start Zero Window Probe Timer  */
            rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_ZWP_E );
        }
#endif
    }
}
#endif


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */



















