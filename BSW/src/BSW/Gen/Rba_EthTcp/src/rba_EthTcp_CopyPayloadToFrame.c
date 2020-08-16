

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
#include "rba_BswSrv.h"


 /*
 ***************************************************************************************************
 * Local functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_SetPayloadToFrame()  - Copy the payload into the Tx buffer provided by EthDrv									**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo 		    - Tcp dynamic socket table index														    **/
/** TxEthDrvBuf_pu8                 - Pointer to the Tx buffer, from where the TCP header starts                                **/
/** PayloadLength_u16				- Length of the payload that needs to be sent											    **/
/**																																**/
/** Parameters (inout):			    None																					    **/
/**																																**/
/** Parameters (out):			    None																					    **/
/**																																**/
/** Return value:				    None                                                                                        **/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SetPayloadToFrame(	VAR( TcpIp_SocketIdType, AUTOMATIC )	TcpDynSockTblIdx_uo,
                                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    TxEthDrvBuf_pu8,
														    VAR( uint16, AUTOMATIC ) 				PayloadLength_u16 )
{
    /* Declare local variables */
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )                                lTxEthDrvPayloadBuf_pu8;
    VAR( uint16, AUTOMATIC )                                            lOptionLen_u16;
    VAR( uint16, AUTOMATIC )                                            lHdrLen_u16;
    VAR( uint16, AUTOMATIC )                                            lLnrDataLen_u16;

    /* -------------------------------------- */
    /* Compute the Tcp header length          */
    /* -------------------------------------- */

    /* Get the length of the Tcp options */
    lOptionLen_u16 = rba_EthTcp_GetOptionLength( TcpDynSockTblIdx_uo );

    /* Compute the length of the Tcp header */
    lHdrLen_u16 = RBA_ETHTCP_DFL_HDRLENGTH + lOptionLen_u16;

    /* ------------------------------------------- */
    /* Compute pointer to the beginning of payload */
    /* ------------------------------------------- */
    lTxEthDrvPayloadBuf_pu8 = ( TxEthDrvBuf_pu8 + lHdrLen_u16 );

    /* -------------------------------------- */
    /* Copy payload                           */
    /* -------------------------------------- */

    /* Get the size of the next linear send location in the Tcp Tx buffer */
    lLnrDataLen_u16 = rba_EthTcp_GetTxBufLnrSndLen( TcpDynSockTblIdx_uo );

    /* If data are stored into two blocks in the Tcp Tx buffer */
    if ( lLnrDataLen_u16 < PayloadLength_u16 )
    {
        /* Copy Tx data of the first buffer block (end of the Tcp Tx buffer) into EthDrv buffer */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        (void)rba_BswSrv_MemCopy( lTxEthDrvPayloadBuf_pu8,
                                  rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TxWndNxtSnd_pu8,
                                  lLnrDataLen_u16 );

        /* Copy Tx data of the second buffer block (beginning of the Tcp Tx buffer) into EthDrv buffer */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        (void)rba_BswSrv_MemCopy( (lTxEthDrvPayloadBuf_pu8 + lLnrDataLen_u16),
                                  rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TxWndStrt_pu8,
                                  (PayloadLength_u16 - lLnrDataLen_u16) );
    }

    /* If data are stored in a linear block in the Tcp Tx buffer */
    else
    {
        /* Copy data from Tcp Tx buffer into EthDrv buffer */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        (void)rba_BswSrv_MemCopy( lTxEthDrvPayloadBuf_pu8,
                                  rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].TxWndNxtSnd_pu8,
                                  PayloadLength_u16 );
    }

    return;
}
#endif


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */

















