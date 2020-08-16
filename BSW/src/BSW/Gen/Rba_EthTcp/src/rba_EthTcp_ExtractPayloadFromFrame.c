

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
 * Local functions
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/*********************************************************************************************************************************/
/** rba_EthTcp_GetPayloadLenFromFrame()		- Returns the length of the payload in bytes (sequence number space occupied by SYN **/
/** 										or FIN is also counted by this function). Corresponds to SEG.LEN.        			**/
/**																																**/
/** Parameters (in):																											**/
/** RxData_cpu8 						    - The pointer to the beginning of the TCP Header									**/
/** LenByte_u16								- Total length of TCP frame															**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):						None																				**/
/**																																**/
/** Return value:							- uint16																			**/
/**												Length of the payload in the received frame	(in bytes)							**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetPayloadLenFromFrame(	P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 	RxData_cpu8,
																	VAR( uint16, AUTOMATIC ) 				LenByte_u16 )
{
	/* Declare local variables */
	VAR( uint16, AUTOMATIC ) 							lDataLen_u16;
	VAR( uint16, AUTOMATIC ) 							lPayloadLen_u16;
	VAR( uint8, AUTOMATIC ) 							lRcvdDataOffset_u8;
	VAR( uint8, AUTOMATIC ) 							lRcvdHdrFlags_u8;

    /* --------------------------------------- */
    /* Compute data length				   	   */
    /* --------------------------------------- */

	/* Extract data offset from Tcp header */
	lRcvdDataOffset_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_OFFSET_E) >> 4U;

	/* Extract header flags from Tcp header */
	lRcvdHdrFlags_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_FLAGS_E );

	/* Compute the length of the data in received frame (in bytes) */
	lDataLen_u16 = ( LenByte_u16 - (uint16)( (uint16)(lRcvdDataOffset_u8) << 2U ) );

    /* --------------------------------------- */
    /* Compute payload length				   */
    /* --------------------------------------- */

    /* Initialize the payload length to the data length */
	lPayloadLen_u16 = lDataLen_u16;

    /* If there is a SYN in the segment, increment the segment length by 1 */
    /* (SYN which consumes 1 byte in the sequence number space need to be counted in the segment length, see RFC793 p26) */
    if ( (lRcvdHdrFlags_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
    	lPayloadLen_u16 += 1U;
    }

    /* If there is a FIN in the segment, increment the segment length by 1 */
    /* (FIN which consumes 1 byte in the sequence number space need to be counted in the segment length, see RFC793 p26) */
    if ( (lRcvdHdrFlags_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK )
    {
    	lPayloadLen_u16 += 1U;
    }

	return lPayloadLen_u16;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_GetRepeatedPayloadLen()		- Get the repeated payload length in case of the segment text straddle the  		**/
/** 										boundary between old and new data (sequence number space occupied by SYN is also	**/
/**											counted by this function)         													**/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             		- Tcp dynamic socket table index                                             		**/
/** RcvdSeqNum_u32                  		- Sequence number received from remote node                                			**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):						None																				**/
/**																																**/
/** Return value:        					- uint16                                                                     		**/
/**                   							Repeated payload length                        									**/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetRepeatedPayloadLen( 	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
																	VAR( uint32, AUTOMATIC )	RcvdSeqNum_u32 )
{
	/* Declare local variables */
	VAR( uint32, AUTOMATIC )                    		lNxtExpctdSeqNum_u32;
	VAR( uint32, AUTOMATIC )                    		lWndRngEnd_u32;
	VAR( uint16, AUTOMATIC )                    		lSndWndSize_u16;
	VAR( uint16, AUTOMATIC )          					lRepeatedPayloadLen_u16;

	/* Initialize the repeated payload length to 0 */
	lRepeatedPayloadLen_u16 = 0U;

    /* ----------------------------------- */
    /* Get needed information              */
    /* ----------------------------------- */

	/* Get the next expected sequence number (corresponds to the send ack number) */
    lNxtExpctdSeqNum_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndAckNum_u32;

	/* Get the size of our Tcp window */
    lSndWndSize_u16 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndWndSize_u16;

	/* Compute the sequence number corresponding to the end of our Tcp window */
    lWndRngEnd_u32 = ( lNxtExpctdSeqNum_u32 + (uint32)lSndWndSize_u16 );

	/* ----------------------------------- */
	/* Compute the repeated payload length */
	/* ----------------------------------- */

    /* If the segment straddle the boundry between old and new data */
	/* (segment straddle the boundary between old and new if the received sequence number is out of the window) */
	if( ((lNxtExpctdSeqNum_u32 <= lWndRngEnd_u32)							&&		/* Normal case */
		 ((RcvdSeqNum_u32 < lNxtExpctdSeqNum_u32) || (RcvdSeqNum_u32 > lWndRngEnd_u32)))
		||
		((lNxtExpctdSeqNum_u32 > lWndRngEnd_u32)							&&		/* Wrap around */
		 ((RcvdSeqNum_u32 < lNxtExpctdSeqNum_u32) && (RcvdSeqNum_u32 > lWndRngEnd_u32))) )
	{
		lRepeatedPayloadLen_u16 = (uint16)( lNxtExpctdSeqNum_u32 - RcvdSeqNum_u32 );
	}

	return lRepeatedPayloadLen_u16;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_GetOutOfWindowPayloadLen()	- Get the out of window payload length in case of the segment exceed the window		**/
/**											(sequence number space occupied by FIN is also counted by this function)			**/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             		- Tcp dynamic socket table index                                             		**/
/** RcvdSeqNum_u32                  		- Sequence number received from remote node                                			**/
/** PayloadLenByte_u16						- Payload length (include sequence number space occupied by SYN or FIN)				**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):						None																				**/
/**																																**/
/** Return value:        					- uint16                                                                     		**/
/**                   							Out of window payload length                        							**/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( uint16, RBA_ETHTCP_CODE ) rba_EthTcp_GetOutOfWindowPayloadLen( 	VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo,
																		VAR( uint32, AUTOMATIC )	RcvdSeqNum_u32,
																		VAR( uint16, AUTOMATIC ) 	PayloadLenByte_u16 )
{
	/* Declare local variables */
	VAR( uint32, AUTOMATIC )                    		lNxtExpctdSeqNum_u32;
	VAR( uint32, AUTOMATIC )                    		lWndRngEnd_u32;
	VAR( uint16, AUTOMATIC )                    		lSndWndSize_u16;
	VAR( uint16, AUTOMATIC )          					lOutOfWindowPayloadLen_u16;

    /* Initialize the out of window payload length to 0 */
	lOutOfWindowPayloadLen_u16 = 0U;

    /* ----------------------------------- */
    /* Get needed information              */
    /* ----------------------------------- */

	/* Get the next expected sequence number (corresponds to the send ack number) */
    lNxtExpctdSeqNum_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndAckNum_u32;

	/* Get the size of our Tcp window */
    lSndWndSize_u16 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndWndSize_u16;

	/* Compute the sequence number corresponding to the end of our Tcp window */
    lWndRngEnd_u32 = ( lNxtExpctdSeqNum_u32 + (uint32)lSndWndSize_u16 );

    /* If the segment length is greater than 0 */
    if( PayloadLenByte_u16 > 0U )
    {
		/* ---------------------------------------- */
		/* Compute the out of window payload length */
		/* ---------------------------------------- */

    	/* If the segment exceed the window */
		/* (segment exceed the window if the sequence number of the last byte of the segment is out of the window) */
		if( ((lNxtExpctdSeqNum_u32 <= lWndRngEnd_u32)							&&		/* Normal case */
			 ((((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) >= lWndRngEnd_u32) || (((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) < lNxtExpctdSeqNum_u32)))
			||
			((lNxtExpctdSeqNum_u32 > lWndRngEnd_u32)							&&		/* Wrap around */
			 ((((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) >= lWndRngEnd_u32) && (((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) < lNxtExpctdSeqNum_u32))) )
		{
			lOutOfWindowPayloadLen_u16 = (uint16)( (((RcvdSeqNum_u32 + (uint32)PayloadLenByte_u16) - 1U) - lWndRngEnd_u32) + 1U );
		}
    }

	return lOutOfWindowPayloadLen_u16;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */























