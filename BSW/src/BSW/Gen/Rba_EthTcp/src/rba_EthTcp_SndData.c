

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

#if ( TCPIP_IPV4_ENABLED == STD_ON )
#include "rba_EthIPv4.h"
#endif

#if ( TCPIP_IPV6_ENABLED == STD_ON )
#include "rba_EthIPv6.h"
#endif


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( uint16, RBA_ETHTCP_CODE )          rba_EthTcp_GetSendingDataLength     ( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo );

static FUNC( uint16, RBA_ETHTCP_CODE )          rba_EthTcp_SplitDataInSegments      ( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo,
                                                                                      VAR( uint16, AUTOMATIC )              SendingDataLen_u16 );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_SndDataSegment           ( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo,
                                                                                      VAR( uint16, AUTOMATIC )              DataLength_u16,
                                                                                      P2VAR( uint16, AUTOMATIC, AUTOMATIC ) SentDataLen_pu16 );

static FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_UpdateSocketAfterSndData ( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpDynSockTblIdx_uo,
                                                                                      VAR( uint16, AUTOMATIC )              SentDataLen_u16 );
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
/** rba_EthTcp_SndData()	- Send one or more Tcp frames containing header + payload									        **/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo		- Tcp dynamic socket table index																	**/
/**																																**/
/** Parameters (inout):		None																								**/
/**																																**/
/** Parameters (out):		None																								**/
/**																																**/
/** Return value:			None																								**/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_SndData ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 			lTcpDynSockTbl_pst;
	VAR( uint16, AUTOMATIC ) 												lUnackedDataLen_u16;
	VAR( uint16, AUTOMATIC ) 												lSendingDataLen_u16;
	VAR( uint16, AUTOMATIC )                  								lTotalSentDataLength_u16;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* --------------------------------------- */
    /* Decrement sequence number (RETX or ZWP) */
    /* --------------------------------------- */

    /* Get the length of unacked data in the Tcp Tx buffer */
    lUnackedDataLen_u16 = rba_EthTcp_GetTxBufUnackedLen( TcpDynSockTblIdx_uo );

#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
    /* If a retransmission of Data or the sending of a ZWP need to be done */
    if( ((lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_DATA_E) && (lTcpDynSockTbl_pst->RetransmissionFlg_b != FALSE))    ||
        (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ZWP_E) )
#else
    /* If the sending of a ZWP need to be done */
    if( lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ZWP_E )
#endif
    {
        /* Set the send sequence number to the sequence number of the oldest unacknowledged data */
        rba_EthTcp_SetSeqNum(   TcpDynSockTblIdx_uo,
                                (lTcpDynSockTbl_pst->SndSeqNum_u32 - (uint32)(lUnackedDataLen_u16)) );

        /* Move the TxWndNxtSnd pointer to the beginning of the unacknowledged data location in the Tcp Tx buffer */
        rba_EthTcp_SetTxBufBeforeReTx( TcpDynSockTblIdx_uo );
    }

    /* -------------------------------------- */
    /* Send data in one or more segments      */
    /* -------------------------------------- */

    /* Compute the sending data length according to the remote window size */
    lSendingDataLen_u16 = rba_EthTcp_GetSendingDataLength ( TcpDynSockTblIdx_uo );

    /* Execute Tcp data sending in multiple segments according to the MSS value */
    lTotalSentDataLength_u16 =rba_EthTcp_SplitDataInSegments(   TcpDynSockTblIdx_uo,
                                                                lSendingDataLen_u16 );

    /* ------------------------------------------------- */
    /* Increment back back sequence number (RETX or ZWP) */
    /* ------------------------------------------------- */
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
    /* If a retransmission of Data or the sending of a ZWP was needed */
    if( ((lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_DATA_E) && (lTcpDynSockTbl_pst->RetransmissionFlg_b != FALSE))    ||
        (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ZWP_E) )
#else
    /* If the sending of a ZWP was needed */
    if( lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ZWP_E )
#endif
    {
        /* If some unacked data have not been sent */
        if( lTotalSentDataLength_u16 < lUnackedDataLen_u16 )
        {
            /* Set back the next sequence number to be sent */
            rba_EthTcp_SetSeqNum(   TcpDynSockTblIdx_uo,
                                    (lTcpDynSockTbl_pst->SndSeqNum_u32 + (uint32)(lUnackedDataLen_u16 - lTotalSentDataLength_u16)) );

            /* Set back the unacked and send data locations in the Tcp Tx buffer */
            rba_EthTcp_SetTxBufAfterTx( TcpDynSockTblIdx_uo,
                                        (lUnackedDataLen_u16 - lTotalSentDataLength_u16) );
        }
    }

    /* -------------------------------------- */
    /* Update next frame to be sent           */
    /* -------------------------------------- */

    /* If some or all the data have been sent */
    if( lSendingDataLen_u16 > 0U )
    {
        /* Reset the Tcp flag to NOTHING */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_NOTHING_E );
    }

    /* If no data can be sent */
    else
    {
        /* Reset the frame to be sent */
        /* (This is needed to force the overwriting of SEND_DATA to SEND_ACK) */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_NOTHING_E );

        /* As the DATA frame cannot be sent, we have to send an ACK instead */
        /* (so that the acknowledgement number will be anyway transmitted to the remote even if data cannot be sent to the remote) */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_E );
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
/** rba_EthTcp_GetSendingDataLength()   - Compute the length of data the remote is able to receive depending on the remote      **/
/**                                     window size                                                                             **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index                                                        **/
/**                                                                                                                             **/
/** Parameters (inout):                 None                                                                                    **/
/**                                                                                                                             **/
/** Parameters (out):                   None                                                                                    **/
/**                                                                                                                             **/
/** Return value:                       - uint16                                                                                **/
/**                                         Length of data to send to the remote within this SndData call                       **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetSendingDataLength ( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
    VAR( uint16, AUTOMATIC )                                                lUnackedDataLen_u16;
    VAR( uint16, AUTOMATIC )                                                lAcceptableDataLenByRemote_u16;
    VAR( uint16, AUTOMATIC )                                                lRemainDataLen_u16;
    VAR( uint16, AUTOMATIC )                                                lSendingDataLen_u16;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* -------------------------------------------------------- */
    /* Compute the length of data the remote is able to receive */
    /* -------------------------------------------------------- */

    /* Get the length of unacked data in the Tcp Tx buffer */
    lUnackedDataLen_u16 = rba_EthTcp_GetTxBufUnackedLen( TcpDynSockTblIdx_uo );

#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
    /* If a ZWP needs to be sent */
    if( lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ZWP_E )
    {
        /* Remote is able to receive 1 byte of data as Zero Window Probe */
        lAcceptableDataLenByRemote_u16 = 1U;
    }
    else
#endif
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
    /* If a retransmission of data need to be done */
    if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_DATA_E) && (lTcpDynSockTbl_pst->RetransmissionFlg_b != FALSE) )
    {
        lAcceptableDataLenByRemote_u16 = lTcpDynSockTbl_pst->RcvdWndSize_u16;
    }
    else
#endif
    /* If normal data need to be sent and the remote window size is big enough to receive some new data */
    if ( lTcpDynSockTbl_pst->RcvdWndSize_u16 > lUnackedDataLen_u16 )
    {
        lAcceptableDataLenByRemote_u16 = ( lTcpDynSockTbl_pst->RcvdWndSize_u16 - lUnackedDataLen_u16 );
    }

    /* If the window size of the remote is not big enough */
    else
    {
        /* The remote is not able to receive some data */
        lAcceptableDataLenByRemote_u16 = 0U;
    }

    /* -------------------------------------- */
    /* Compute the length of data to be sent  */
    /* -------------------------------------- */

    /* Calculate how much data in TCP buffer is ready to send */
    lRemainDataLen_u16 = rba_EthTcp_GetTxBufSndLen( TcpDynSockTblIdx_uo );

    /* If the remaining data length in the Tcp Tx buffer is greater than the length of data that the remote can receive */
    if ( lRemainDataLen_u16 > lAcceptableDataLenByRemote_u16 )
    {
        /* Set the length of data to be sent to the length of data that the remote can receive */
        lSendingDataLen_u16 = lAcceptableDataLenByRemote_u16;
    }
    else
    {
        /* Set the length of data to be sent to the remaining data length in the Tcp Tx buffer */
        lSendingDataLen_u16 = lRemainDataLen_u16;
    }

    return lSendingDataLen_u16;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_SplitDataInSegments() - Execute the sending of the data in multiple Tcp segments whose length depend on the MSS  **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                            **/
/** SendingDataLen_u16              - Total length of data to be sent                                                           **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   - uint16                                                                                    **/
/**                                     Total length of data that has been really sent                                          **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_SplitDataInSegments ( VAR( TcpIp_SocketIdType, AUTOMATIC )    TcpDynSockTblIdx_uo,
                                                                        VAR( uint16, AUTOMATIC )                SendingDataLen_u16 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
    VAR( uint16, AUTOMATIC )                                                lCurrSegDataLength_u16;
    VAR( uint16, AUTOMATIC )                                                lTcpOptionLen_u16;
    VAR( uint16, AUTOMATIC )                                                lRemainDataLen_u16;
    VAR( uint16, AUTOMATIC )                                                lSentDataLen_u16;
    VAR( uint16, AUTOMATIC )                                                lTotalSentDataLength_u16;
    VAR( Std_ReturnType, AUTOMATIC )                                        lRetVal_en;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst  = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* -------------------------------------- */
    /* Send data in multiple segments         */
    /* -------------------------------------- */

    /* Initialize the total sent data length to 0 */
    lTotalSentDataLength_u16 = 0U;

    /* While there is some data to be sent */
    while( lTotalSentDataLength_u16 < SendingDataLen_u16 )
    {
        /* -------------------------------------- */
        /* Compute the current segment size       */
        /* -------------------------------------- */
        lCurrSegDataLength_u16 = ( SendingDataLen_u16 - lTotalSentDataLength_u16 );

        /* -------------------------------------- */
        /* Limit the current segment size         */
        /* -------------------------------------- */

        /* Limit the current segment size to the effective send maximum segment size */
        /* (for more information, see RFC1122 p85 and RFC879 p4) */

        /* Get the length of the Tcp options */
        lTcpOptionLen_u16 = rba_EthTcp_GetOptionLength( TcpDynSockTblIdx_uo );

        /* If the segment size is greater than the MSS of the remote minus TCP option length (Tcp option length is considered since Received MSS didnt consider it) */
        if ( lCurrSegDataLength_u16 > (lTcpDynSockTbl_pst->RcvdMss_u16 - lTcpOptionLen_u16) )
        {
            /* Limit the current segment size to the MSS of the remote minus TCP option */
            /* (this is needed in order to respect the limit imposed by the remote TCP) */
            lCurrSegDataLength_u16 = ( lTcpDynSockTbl_pst->RcvdMss_u16 - lTcpOptionLen_u16 );
        }

        /* If the segment size is greater than our local MSS minus Tcp option length (Tcp option length is considered since this was not considered while determining local MSS) */
        /* (Normally for this check, we should do a comparison with the maximum size permitted by the IP layer as explained in RFC1122 p85. */
        /* The maximum size permitted by the IP layer should be computed thanks to the MMS_S value which is given by IP. */
        /* MMS_S value is based on interface MTU and path MTU and is determined by IP to avoid fragmentation on the path. See RFC1122 p58. */
        /* As the IP layer does not implement this functionning, we do a comparison with calculated local MSS in order to, at least, be sure that the segment to send will not exceed the interface MTU) */
        if( lCurrSegDataLength_u16 > (lTcpDynSockTbl_pst->LocalMss_u16 - lTcpOptionLen_u16) )
        {
            /* Limit the current segment size to our local MSS minus Tcp option length */
            /* (this is needed in order to avoid fragmentation) */
            lCurrSegDataLength_u16 = ( lTcpDynSockTbl_pst->LocalMss_u16 - lTcpOptionLen_u16 );
        }

        /* -------------------------------------- */
        /* Handle PSH flag                        */
        /* -------------------------------------- */

        /* Calculate how much data in TCP buffer is ready to send */
        lRemainDataLen_u16 = rba_EthTcp_GetTxBufSndLen( TcpDynSockTblIdx_uo );

        /* If we are transmitting the last segment */
        /* (after this segment, there is no more data in the Tcp Tx buffer) */
        if( lCurrSegDataLength_u16 == lRemainDataLen_u16 )
        {
            /* We must set the PSH flag in the header of the segment */
            /* RFC1122 p83 : MUST set the PSH bit in the last buffered segment (i.e., when there is no more queued data to be sent) */
            lTcpDynSockTbl_pst->SndHdrFlag_u8 |= RBA_ETHTCP_PSH_MSK;
        }

        /* -------------------------------------- */
        /* Send Data segment                      */
        /* -------------------------------------- */

        /* Execute Tcp frame sending */
        lRetVal_en = rba_EthTcp_SndDataSegment (    TcpDynSockTblIdx_uo,
                                                    lCurrSegDataLength_u16,
                                                    &lSentDataLen_u16 );

        /* If the data segment has been successfully sent */
        if( lRetVal_en == E_OK )
        {
            /* Increase the total length of data that has been sent */
            lTotalSentDataLength_u16 += lSentDataLen_u16;

            /* -------------------------------------- */
            /* Update Tcp socket                      */
            /* -------------------------------------- */

            /* Execute the post processing needed after the sending of the Tcp data frame */
            rba_EthTcp_UpdateSocketAfterSndData( TcpDynSockTblIdx_uo, lSentDataLen_u16 );
        }

        /* If the flag frame has not been sent because of an error */
        else
        {
            /* Stop the sending of the data as one segment cannot be sent */
            break;
        }
    }

    return lTotalSentDataLength_u16;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_SndDataSegment() - Execute the sending of the Tcp data segment                                                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo         - Tcp dynamic socket table index                                                                **/
/** SentDataLen_u16             - Length of the data to be sent                                                                 **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** SentDataLen_pu16            - Length of the data that has been really sent                                                  **/
/**                                                                                                                             **/
/** Return value:               - Std_ReturnType                                                                                **/
/**                                 E_OK: The segment has been successfully transmitted                                         **/
/**                                 E_NOT_OK: The segment has not been sent                                                     **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_SndDataSegment (  VAR( TcpIp_SocketIdType, AUTOMATIC )    TcpDynSockTblIdx_uo,
                                                                            VAR( uint16, AUTOMATIC )                DataLength_u16,
                                                                            P2VAR( uint16, AUTOMATIC, AUTOMATIC )   SentDataLen_pu16 )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )            lTcpDynSockTbl_pst;
    VAR( BufReq_ReturnType, AUTOMATIC )                                     lRetBufReq_en;
    VAR( TcpIp_ReturnType, AUTOMATIC )                                      lIpTxRetType_en;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )                                    lIpProvidedBuf_pu8;
    VAR( TcpIp_IpHeader_tst, AUTOMATIC )                                    lIpHeader_st;
    VAR( uint16, AUTOMATIC )                                                lTcpOptionLen_u16;
    VAR( uint16, AUTOMATIC )                                                lTcpHdrLen_u16;
    VAR( uint16, AUTOMATIC )                                                lCurrSegDataLength_u16;
    VAR( uint16, AUTOMATIC )                                                lReqAndGrantedLen_u16;
    VAR( uint8, AUTOMATIC )                                                 lIpProvidedBufIdx_u8;
    VAR( Std_ReturnType, AUTOMATIC )                                        lFunctionRetVal_en;
#if ( RBA_ETHTCP_SW_CHKSUM_TX == STD_ON )
    VAR( Std_ReturnType, AUTOMATIC )                                        lRetVal_en;
#endif

	/* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* -------------------------------------- */
    /* Configure the IP header                */
    /* -------------------------------------- */
    lIpHeader_st.ProtoType_en = TCPIP_IPPROTO_TCP;
    lIpHeader_st.Ttl_u8       = rba_EthTcp_CurrConfig_cpo->TcpTtl_u8; /* Use Configured TTL */

    /* -------------------------------------- */
    /* Compute header length                  */
    /* -------------------------------------- */

    /* Get the length of the Tcp options */
    lTcpOptionLen_u16 = rba_EthTcp_GetOptionLength( TcpDynSockTblIdx_uo );

    /* Compute the length of the Tcp header */
    lTcpHdrLen_u16 = RBA_ETHTCP_DFL_HDRLENGTH + lTcpOptionLen_u16;

    /* -------------------------------------- */
    /* Request a buffer for the transmission  */
    /* -------------------------------------- */

    /* Set the current segment data length */
    lCurrSegDataLength_u16 = DataLength_u16;

    /* Compute the buffer size to request */
    lReqAndGrantedLen_u16 = ( lTcpHdrLen_u16 + lCurrSegDataLength_u16 );

    /* Ask the required buffer to the IP layer */
    lRetBufReq_en = RBA_ETHTCP_CALL_IP_LAYER_PROVIDE_TX_BUFFER_API( lTcpDynSockTbl_pst, &lIpProvidedBufIdx_u8, &lIpProvidedBuf_pu8, &lReqAndGrantedLen_u16 );

    /* If an overflow occured */
    /* (means that it is not possible to request a buffer with enough space) */
    if ( lRetBufReq_en == BUFREQ_E_OVFL )
    {
        /* Check whether the buffer length which IP can provide is big enough to contain the Tcp header and 1 byte of data */
        if( lReqAndGrantedLen_u16 >= (lTcpHdrLen_u16 + 1U) )
        {
            /* Recompute the current segment size */
            lCurrSegDataLength_u16 = ( lReqAndGrantedLen_u16 - lTcpHdrLen_u16 );

            /* Ask the required buffer to the IP layer again (with lower size this time) */
            lRetBufReq_en = RBA_ETHTCP_CALL_IP_LAYER_PROVIDE_TX_BUFFER_API( lTcpDynSockTbl_pst, &lIpProvidedBufIdx_u8, &lIpProvidedBuf_pu8, &lReqAndGrantedLen_u16 );
        }
    }

    /* Check if IP successfully provided the requested buffer */
    if ( lRetBufReq_en == BUFREQ_OK )
    {
        /* -------------------------------------- */
        /* Copy the Tcp frame into the buffer     */
        /* -------------------------------------- */

        /* Copy the Tcp header in the provided buffer */
        rba_EthTcp_SetHdrToFrame( TcpDynSockTblIdx_uo,
                                  lIpProvidedBuf_pu8 );

        /* Copy the Tcp options in the provided buffer */
        rba_EthTcp_SetOptionToFrame( TcpDynSockTblIdx_uo,
                                     lIpProvidedBuf_pu8 );

        /* Copy the payload in the provided buffer */
        rba_EthTcp_SetPayloadToFrame( TcpDynSockTblIdx_uo,
                                      lIpProvidedBuf_pu8,
                                      lCurrSegDataLength_u16 );

#if ( RBA_ETHTCP_SW_CHKSUM_TX == STD_ON )
		/* Update the Checksum field in the Tcp header (in EthDrv buffer) */
        lRetVal_en = rba_EthTcp_SetChecksumToFrame ( TcpDynSockTblIdx_uo,
                                                     lIpProvidedBuf_pu8,
                                                     (lTcpHdrLen_u16 + lCurrSegDataLength_u16) );

		/* If an error occured during the computation of the checksum */
        if( lRetVal_en == E_NOT_OK )
        {
			/* Call transmit with 0 length to free the driver buffer */
			/* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
            (void)RBA_ETHTCP_CALL_IP_LAYER_TRANSMIT_API( lTcpDynSockTbl_pst, lIpProvidedBuf_pu8, lIpProvidedBufIdx_u8, &lIpHeader_st, 0U );
		}
		else
#endif
        {
			/* -------------------------------------- */
			/* Transmission                           */
			/* -------------------------------------- */

			/* Ask the transmission of the frame */
			/* MR12 RULE 11.3 VIOLATION: Cast is the only way to dynamically interpret the data as IPv4 or IPv6 specific data. */
            lIpTxRetType_en = RBA_ETHTCP_CALL_IP_LAYER_TRANSMIT_API( lTcpDynSockTbl_pst, lIpProvidedBuf_pu8, lIpProvidedBufIdx_u8, &lIpHeader_st, ( lTcpHdrLen_u16 + lCurrSegDataLength_u16 ) );
			if( lIpTxRetType_en == TCPIP_OK )
			{
				/* Set the sent data length as out argument of the function */
				(*SentDataLen_pu16) = lCurrSegDataLength_u16;

				/* Set the return value of the function to E_OK */
				lFunctionRetVal_en = E_OK;
			}
        }
    }

    return lFunctionRetVal_en;
}
#endif


/*********************************************************************************************************************************/
/** rba_EthTcp_UpdateSocketAfterSndData()   - Execute the post processing after a Tcp data frame is sent						**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo					    - Tcp dynamic socket table index													**/
/** SentDataLen_u16      				    - Length of the data that has been sent												**/
/**																																**/
/** Parameters (inout):					    None																				**/
/**																																**/
/** Parameters (out):					    None																				**/
/**																																**/
/** Return value:						    None																			    **/
/**																																**/
/*********************************************************************************************************************************/
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_UpdateSocketAfterSndData (  VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpDynSockTblIdx_uo,
															                VAR( uint16, AUTOMATIC )	            SentDataLen_u16 )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 			lTcpDynSockTbl_pst;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst	= ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* -------------------------------------- */
	/* Update variables and pointers 	      */
	/* -------------------------------------- */

	/* Set the sequence number of the next frame that will be transmitted */
	/* (the sequence number is advanced by the length of the sent data) */
	rba_EthTcp_SetSeqNum( 	TcpDynSockTblIdx_uo,
							(lTcpDynSockTbl_pst->SndSeqNum_u32 + (uint32)(SentDataLen_u16)) );

	/* Advance the TxWndNxtSend pointer by the length of the current segment in the Tcp Tx buffer */
	/* (unacked data location is increased and send data location is decreased) */
	rba_EthTcp_SetTxBufAfterTx( TcpDynSockTblIdx_uo, SentDataLen_u16 );

	/* Set the total received data length since the last sending of ACK to 0 */
	/* (the sent data frame contained the acknowledgement number) */
	( lTcpDynSockTbl_pst->TotalRcvdDataLen_u16 ) = 0U;

	/* If there is no oldest unacked segment length actually saved */
	if( lTcpDynSockTbl_pst->OldestUnackedSegmentLength_u16 == 0U )
	{
		/* Save the sent data length as oldest unacked segment length */
		lTcpDynSockTbl_pst->OldestUnackedSegmentLength_u16 = SentDataLen_u16;
	}

	/* -------------------------------------- */
	/* Update timers 			   		      */
	/* -------------------------------------- */
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
	/* As the acknowledgement number was sent, we can stop the delayed ack timer */
	/* (DLYACK timer is stopped if it is running) */
	rba_EthTcp_StopTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_DLYACK_E );
#endif

	/* If we have sent a DATA segment (not a ZWP segment) */
	if( lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_DATA_E )
	{
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
		/* Start RETX timer after sending first segment */
		/* (RETX timer is started if it not already running) */
		rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_RETX_E );
#endif

#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
		/* Start the User Timeout timer after sending first segment */
		/* (UTO timer is started if it not already running) */
		rba_EthTcp_StartTimer( TcpDynSockTblIdx_uo, RBA_ETHTCP_TMR_UTO_E );
#endif
	}

	/* -------------------------------------- */
	/* Dynamic RETX 			   			  */
	/* -------------------------------------- */
#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
	/* If we have sent a DATA segment (with no RETX currently running) or if we have sent the first ZWP segment */
	if( ((lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_DATA_E) && (lTcpDynSockTbl_pst->GeneralRetryCntr_u8 == 0U))	||
		((lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_ZWP_E) && (lTcpDynSockTbl_pst->GeneralRetryCntr_u8 == 1U)) )
#else
	/* If we have sent a DATA segment (with no RETX currently running) */
	if( (lTcpDynSockTbl_pst->TcpFlag_en == RBA_ETHTCP_SEND_DATA_E) && (lTcpDynSockTbl_pst->GeneralRetryCntr_u8 == 0U) )
#endif
	{
		/* Start the RTT measurement */
		lTcpDynSockTbl_pst->RttInProgress_b = TRUE;
	}
#endif

	return;
}
#endif


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */



















