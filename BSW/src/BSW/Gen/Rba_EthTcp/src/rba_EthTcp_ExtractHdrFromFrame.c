

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
static FUNC( uint8, RBA_ETHTCP_CODE ) rba_EthTcp_ReadMssOption( P2CONST( uint8, AUTOMATIC, AUTOMATIC )  OptionPtr_cpu8,
																VAR( uint16, AUTOMATIC )       			RemainingOptionLen_u16,
																P2VAR( uint16, AUTOMATIC, AUTOMATIC ) 	MssValue_pu16 );
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
/** rba_EthTcp_GetHdrFromFrame()			- This function extract the header fields of a received TCP frame					**/
/**																																**/
/** Parameters (in):																											**/
/** RxData_cpu8 							- The pointer to the beginning of the TCP Header									**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):																											**/
/** RcvdHdrFields_pst 						- Structure containing the Tcp header fields										**/
/**																																**/
/** Return value:							None																				**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_GetHdrFromFrame( 	P2CONST( uint8, AUTOMATIC, AUTOMATIC )                      RxData_cpu8,
															P2VAR( rba_EthTcp_HeaderFields_tst, AUTOMATIC, AUTOMATIC )  RcvdHdrFields_pst )
{
	/* Declare local variables */
	VAR( uint8, AUTOMATIC )       						lRcvdDataOffset_u8;

	/* Extract source port from Tcp header */
	RcvdHdrFields_pst->SrcPort_u16 = RBA_ETHTCP_READ_16BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_SRCPORT_E );

	/* Extract destination port from Tcp header */
	RcvdHdrFields_pst->DestPort_u16 = RBA_ETHTCP_READ_16BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_DESTPORT_E );

	/* Extract sequence number from Tcp header */
	RcvdHdrFields_pst->SeqNum_u32 = RBA_ETHTCP_READ_32BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_SEQNUM_E );

	/* Extract acknowledgment number from Tcp header */
	RcvdHdrFields_pst->AckNum_u32 = RBA_ETHTCP_READ_32BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_ACKNUM_E );

	/* Extract data offset from Tcp header */
	lRcvdDataOffset_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_OFFSET_E) >> 4U;

	/* Compute header length (in bytes) */
	/* (HeaderLen =  4 * DataOffset) */
	RcvdHdrFields_pst->HdrLen_u16 = (uint16)( (uint16)(lRcvdDataOffset_u8) << 2U );

	/* Extract header flags from Tcp header */
	RcvdHdrFields_pst->HdrFlag_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_FLAGS_E );

	/* Extract window size from Tcp header */
	RcvdHdrFields_pst->WndSize_u16 = RBA_ETHTCP_READ_16BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_WNDSIZE_E );

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_GetOptionFromFrame()			- This function extract the options of a received Tcp frame							**/
/**																																**/
/** Parameters (in):																											**/
/** RxData_pu8 							    - The pointer to the beginning of the TCP Header									**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):																											**/
/** RcvdOptionFields_pst 					- Structure containing the Tcp option fields										**/
/**																																**/
/** Return value:							None																				**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_GetOptionFromFrame( 	P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 						RxData_cpu8,
																P2VAR( rba_EthTcp_OptionFields_tst, AUTOMATIC, AUTOMATIC )  RcvdOptionFields_pst )
{
	/* Declare local variables */
	VAR( uint16, AUTOMATIC )       						lRcvdHdrLen_u16;
	VAR( uint16, AUTOMATIC )                            lOptionIndex_u16;
	VAR( uint8, AUTOMATIC )       						lRcvdDataOffset_u8;
	VAR( uint8, AUTOMATIC )       						lKindField_u8;
	VAR( uint8, AUTOMATIC )                   			lCurrentOptionLen_u8;
	VAR( boolean, AUTOMATIC )       					lFlagToBreak_b;

    /* ------------------------------------ */
	/* Initialize options to default values */
    /* ------------------------------------ */
	RcvdOptionFields_pst->Mss_u16 = RBA_ETHTCP_DFL_MSS;

	/* ------------------------------------ */
	/* Compute complete header length       */
	/* ------------------------------------ */

	/* Extract data offset from Tcp header */
	lRcvdDataOffset_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( RxData_cpu8, (uint8)RBA_ETHTCP_POS_OFFSET_E) >> 4U;

	/* Compute received header length (in bytes) */
	/* (HeaderLen =  4 * DataOffset) */
	lRcvdHdrLen_u16 = (uint16)( (uint16)(lRcvdDataOffset_u8) << 2U );

    /* ------------------------------------- */
    /* Loop through options within the frame */
    /* ------------------------------------- */

    /* Initialize the option index to the default header length */
	/* (the Tcp options begins after the default Tcp header) */
	lOptionIndex_u16 = RBA_ETHTCP_DFL_HDRLENGTH;

    /* Initialize the break flag */
    lFlagToBreak_b = FALSE;

    /* While the option index is lower than the header length */
    /* (means that there are still option to process in the frame) */
    while ( (lOptionIndex_u16 < lRcvdHdrLen_u16) && (lFlagToBreak_b == FALSE) )
    {
        /* Reset the current option length to 0 */
        lCurrentOptionLen_u8 = 0U;

        /* Read Kind field */
        lKindField_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( (RxData_cpu8 + lOptionIndex_u16), (uint8)RBA_ETHTCP_POS_OPT_KIND_E );

        switch ( lKindField_u8 )
        {
            /* ------------------------------------- */
            /* NOP option                            */
            /* ------------------------------------- */

            /* Check if NOP is present (special option) */
            /* (NOP is a 1 byte long and means "no operation") */
            case RBA_ETHTCP_OPT_KIND_NOP:
            {
                /* Jump after NOP option */
                lCurrentOptionLen_u8 = 1U;
                lOptionIndex_u16 += lCurrentOptionLen_u8;
            }
            break;

            /* ------------------------------------- */
            /* EOP option                            */
            /* ------------------------------------- */

            /* Check if EOP is present (special option) */
            /* (EOP is 1 byte long and means "end of option list") */
            case RBA_ETHTCP_OPT_KIND_EOP:
            {
                /* Stop option parsing */
                lFlagToBreak_b = TRUE;
            }
            break;

            /* ------------------------------------- */
            /* MSS option                            */
            /* ------------------------------------- */

            /* Check if MSS option is present */
            case RBA_ETHTCP_OPT_KIND_MSS:
            {
                /* Extract MSS option */
                lCurrentOptionLen_u8 = rba_EthTcp_ReadMssOption( (RxData_cpu8 + lOptionIndex_u16),
                                                                 (lRcvdHdrLen_u16 - lOptionIndex_u16),
                                                                 &(RcvdOptionFields_pst->Mss_u16) );

                /* Jump after MSS option */
                lOptionIndex_u16 += lCurrentOptionLen_u8;
            }
            break;

            /* ------------------------------------- */
            /* Unsupported option                    */
            /* ------------------------------------- */

            /* Unsupported option is present */
            default:
            {
                /* If there are enough remaining bytes to read the Length field */
                if( (uint16)(lRcvdHdrLen_u16 - lOptionIndex_u16) >= 2U )
                {
                    /* Read the Length field */
                    lCurrentOptionLen_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( (RxData_cpu8 + lOptionIndex_u16), (uint8)RBA_ETHTCP_POS_OPT_LEN_E );

                    /* Jump after unsupported option */
                    lOptionIndex_u16 += lCurrentOptionLen_u8;
                }
            }
            break;
        }

        /* ------------------------------------- */
        /* Illegal option 		 	             */
        /* ------------------------------------- */

        /* If the current option length is equal to 0 */
        /* (means the option is illegal) */
        if( lCurrentOptionLen_u8 == 0U )
        {
            /* Stop further option parsing */
            lFlagToBreak_b = TRUE;
        }
    }

	return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RcvdSeqNumValidity()		- Check whether the received sequence number is valid (see p69 of RFC793)             	**/
/**                                                                                                                           	**/
/** Parameters (in):                                                                                                          	**/
/** TcpDynSockTblIdx_uo             	- Tcp dynamic socket table index                                                        **/
/** RcvdSeqNum_u32                  	- Sequence number received from remote node                                             **/
/** PayloadLenByte_u16					- Payload length (SEG.LEN)																**/
/**																																**/
/** Parameters (inout):					None																					**/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:        				rba_EthTcp_SeqVal_ten                                                                   **/
/**                          				RBA_ETHTCP_SEQ_VALID_E: Sequence number is valid                                    **/
/**                          				RBA_ETHTCP_SEQ_SPECIAL_ALLOWANCE_E: Sequence number is valid only for special 		**/
/**																				allowance                                     	**/
/**                          				RBA_ETHTCP_SEQ_OUT_OF_ORDER_E: Sequence number is out of order                      **/
/**                          				RBA_ETHTCP_SEQ_INVALID_E: Sequence number is invalid                     			**/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( rba_EthTcp_SeqVal_ten, RBA_ETHTCP_CODE ) rba_EthTcp_RcvdSeqNumValidity(	VAR( TcpIp_SocketIdType, AUTOMATIC ) 	TcpDynSockTblIdx_uo,
																	 	 	 	VAR( uint32, AUTOMATIC )				RcvdSeqNum_u32,
																	 	 	 	VAR( uint16, AUTOMATIC ) 				PayloadLenByte_u16 )
{
	/* Declare local variables */
	VAR( rba_EthTcp_SeqVal_ten, AUTOMATIC )          	lSeqNumValidity_en;
	VAR( uint32, AUTOMATIC )                    		lNxtExpctdSeqNum_u32;
	VAR( uint32, AUTOMATIC )                    		lWndRngEnd_u32;
	VAR( uint16, AUTOMATIC )                    		lSndWndSize_u16;

	/* Get the next expected sequence number (corresponds to the send ack number) */
    lNxtExpctdSeqNum_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndAckNum_u32;

	/* Get the size of our Tcp window */
    lSndWndSize_u16 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndWndSize_u16;

	/* Compute the sequence number corresponding to the end of our Tcp window */
    lWndRngEnd_u32 = ( lNxtExpctdSeqNum_u32 + (uint32)(lSndWndSize_u16) );

	/* -------------------------------------------- */
    /* Check Seq number validity (local Window = 0)	*/
    /* -------------------------------------------- */
	if( lSndWndSize_u16 == 0U )
	{
		/*----------|--------------*/
		/*          ^              */
		if( (PayloadLenByte_u16 == 0U) 						&&
			(RcvdSeqNum_u32 == lNxtExpctdSeqNum_u32) )
		{
			/* The segment is valid because it is the next expected */
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_VALID_E;
		}

		/*----------|--------------*/
		/*          ^--^           */
		else if( (PayloadLenByte_u16 > 0U) 					&&
				 (RcvdSeqNum_u32 == lNxtExpctdSeqNum_u32) )
		{
			/* When window is equal to 0, no segment is acceptable but special allowance must be made to process valid ACK and RST (see RFC793 p69) */
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_SPECIAL_ALLOWANCE_E;
		}

		/*----------|--------------*/
		/*        ^----^           */
		else if( (PayloadLenByte_u16 > 0U) 												&&
				 (((RcvdSeqNum_u32 <= ((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U))		&&		/* Normal case */
				   ((RcvdSeqNum_u32 < lNxtExpctdSeqNum_u32) && (((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) >= lNxtExpctdSeqNum_u32)))
				  ||
				  ((RcvdSeqNum_u32 > ((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U))		&&		/* Segment wrap around */
				   ((RcvdSeqNum_u32 < lNxtExpctdSeqNum_u32) || (((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) >= lNxtExpctdSeqNum_u32)))) )
		{
			/* When window is equal to 0, no segment is acceptable but special allowance must be made to process valid ACK and RST (see RFC793 p69) */
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_SPECIAL_ALLOWANCE_E;
		}

		/* Other cases (segment is out of the window) */
		else
		{
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_INVALID_E;
		}
	}

	/* -------------------------------------------- */
    /* Check Seq number validity (local Window > 0)	*/
    /* -------------------------------------------- */
	else
	{
		/*----------|****|---------*/		/*---------|******|--------*/		/*---------|******|--------*/
		/*          ^              */		/*         ^--^            */		/*         ^---------^     */
		if( RcvdSeqNum_u32 == lNxtExpctdSeqNum_u32 )
		{
			/* The segment is valid because it is the next expected */
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_VALID_E;
		}

		/*---------|******|--------*/		/*---------|******|--------*/
		/*       ^----^            */		/*       ^----------^      */
		else if( (PayloadLenByte_u16 > 0U) 												&&
				 (((RcvdSeqNum_u32 <= ((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U))		&&		/* Normal case */
				   ((RcvdSeqNum_u32 < lNxtExpctdSeqNum_u32) && (((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) >= lNxtExpctdSeqNum_u32)))
				  ||
				  ((RcvdSeqNum_u32 > ((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U))		&&		/* Segment wrap around */
				   ((RcvdSeqNum_u32 < lNxtExpctdSeqNum_u32) || (((RcvdSeqNum_u32 + PayloadLenByte_u16) - 1U) >= lNxtExpctdSeqNum_u32)))) )
		{
			/* The segment is valid because there is boundary straddling (only the new part will be processed further) */
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_VALID_E;
		}

		/*----------|****|---------*/		/*---------|******|--------*/		/*---------|******|--------*/
		/*            ^            */		/*           ^--^          */		/*            ^------^     */
		else if( ((lNxtExpctdSeqNum_u32 <= lWndRngEnd_u32)							&&		/* Normal case */
				  ((RcvdSeqNum_u32 > lNxtExpctdSeqNum_u32) && (RcvdSeqNum_u32 < lWndRngEnd_u32)))
				 ||
				 ((lNxtExpctdSeqNum_u32 > lWndRngEnd_u32)							&&		/* Window wrap around */
				  ((RcvdSeqNum_u32 > lNxtExpctdSeqNum_u32) || (RcvdSeqNum_u32 < lWndRngEnd_u32))) )
		{
			/* The segment is out of order because it is inside our local window but it is not the next expected */
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_OUT_OF_ORDER_E;
		}

		/* Other cases (segment is out of the window) */
		else
		{
			lSeqNumValidity_en = RBA_ETHTCP_SEQ_INVALID_E;
		}
	}

    return lSeqNumValidity_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_RcvdAckNumValidity()	- Check whether the received Ack number is valid                                            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                       		**/
/** RcvdAckNum_u32                 	- Ack number received from remote node                                            			**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:        			rba_EthTcp_AckVal_ten                                                                       **/
/**                                         RBA_ETHTCP_ACK_NEW_E: Acknowledgment number is new                                  **/
/**                                         RBA_ETHTCP_ACK_DUPLICATE_E: Acknowledgment number is an old duplicate               **/
/**                                         RBA_ETHTCP_ACK_INVALID_E: Acknowledgment number is invalid                          **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( rba_EthTcp_AckVal_ten, RBA_ETHTCP_CODE ) rba_EthTcp_RcvdAckNumValidity(   VAR( TcpIp_SocketIdType, AUTOMATIC )  	TcpDynSockTblIdx_uo,
                                                                                VAR( uint32, AUTOMATIC )                RcvdAckNum_u32 )
{
	/* Declare local variables */
    VAR( rba_EthTcp_AckVal_ten, AUTOMATIC )             lAckNumValidity_en;
    VAR( uint32, AUTOMATIC )                            lIniSndSeqNum_u32;
	VAR( uint32, AUTOMATIC )                    		lSndSeqNum_u32;
	VAR( uint32, AUTOMATIC )                    		lUnAckedSeqNum_u32;

	/* Get the initial send sequence number */
	lIniSndSeqNum_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].IniSndSeqNum_u32;

	/* Get the send sequence number */
    lSndSeqNum_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].SndSeqNum_u32;

    /* Get the unacked sequence number */
    lUnAckedSeqNum_u32 = rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].UnAckedSeqNum_u32;

    /* -------------------------------------------- */
    /* Check Ack number validity                    */
    /* -------------------------------------------- */

	/* Check if the acknowledgment number is valid and new */
	/* (SND.UNA < SEG.ACK =< SND.NXT) */
	if( ((lUnAckedSeqNum_u32 <= lSndSeqNum_u32)				&&		/* Normal case */
		 ((RcvdAckNum_u32 > lUnAckedSeqNum_u32) && (RcvdAckNum_u32 <= lSndSeqNum_u32)))
		||
		((lUnAckedSeqNum_u32 > lSndSeqNum_u32)				&&		/* Wrap around */
		 ((RcvdAckNum_u32 > lUnAckedSeqNum_u32) || (RcvdAckNum_u32 <= lSndSeqNum_u32))) )
	{
	    lAckNumValidity_en = RBA_ETHTCP_ACK_NEW_E;
	}

    /* Check if the acknowledgment number is a duplicated ACK for SYN_SENT state */
	/* (ISS < SEG.ACK <= SND.UNA) */
    else if ( (rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].State_en == RBA_ETHTCP_CONN_SYN_SENT_E)   &&
              (((lIniSndSeqNum_u32 <= lUnAckedSeqNum_u32)             &&      /* Normal case */
                ((RcvdAckNum_u32 > lIniSndSeqNum_u32) && (RcvdAckNum_u32 <= lUnAckedSeqNum_u32)))
               ||
               ((lIniSndSeqNum_u32 > lUnAckedSeqNum_u32)              &&      /* Wrap around */
                ((RcvdAckNum_u32 > lIniSndSeqNum_u32) || (RcvdAckNum_u32 <= lUnAckedSeqNum_u32)))) )
    {
        lAckNumValidity_en = RBA_ETHTCP_ACK_DUPLICATE_E;
    }

    /* Check if the acknowledgment number is a duplicated ACK for other states */
	/* (SEG.ACK <= SND.UNA) */
	else if ( (rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo].State_en != RBA_ETHTCP_CONN_SYN_SENT_E)   &&
	          (RcvdAckNum_u32 <= lUnAckedSeqNum_u32) )
    {
	    lAckNumValidity_en = RBA_ETHTCP_ACK_DUPLICATE_E;
    }

    /* Check if the acknowledgment number is for DATA which is not sent yet */
	/* For SYN_SENT state : (SEG.ACK <= ISS) or (SEG.ACK > SND.NXT) */
	/* For other state : (SEG.ACK > SND.NXT) */
    else
    {
        lAckNumValidity_en = RBA_ETHTCP_ACK_INVALID_E;
    }

    return lAckNumValidity_en;
}



/*********************************************************************************************************************************/
/** rba_EthTcp_RcvdChecksumValidity()	- Check for checksum validity                                     						**/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** PseudoHdr_cpst                      - Pointer to pusedo header structure                                                    **/
/** RxData_pu8                          - Pointer to the Tcp header                                                             **/
/** LenByte_u16                         - Total length of Tcp frame (in bytes)                                                  **/
/**																																**/
/** Parameters (inout):					None																					**/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:        				Std_ReturnType                                                                        	**/
/**                          				E_OK: Received checksum is valid                                                    **/
/**                          				E_NOT_OK: Received checksum is invalid                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if (( RBA_ETHTCP_SW_CHKSUM_RX == STD_ON ) || ( RBA_ETHTCP_REASSMBLY_RX_ENABLED == STD_ON ))
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_RcvdChecksumValidity( P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )   PseudoHdr_cpst,
																		 P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 	 	            RxData_pu8,
																		 VAR( uint16, AUTOMATIC )                	            LenByte_u16 )
{
    VAR( uint16, AUTOMATIC )                            lRcvdChksum_u16;
    VAR( uint16, AUTOMATIC )                            lCalculatedChksum_u16;
    VAR( Std_ReturnType, AUTOMATIC )                    lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                    lRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

	/* ------------------------------ */
	/* Checksum computation           */
	/* ------------------------------ */

	/* Read the checksum in the received frame */
	lRcvdChksum_u16 = RBA_ETHTCP_READ_16BITS_AT_POS( RxData_pu8, (uint8)RBA_ETHTCP_POS_CHKSUM_E );

	/* Set the checksum field in the received frame to 0 */
	RBA_ETHTCP_WRITE_16BITS_AT_POS( RxData_pu8, (uint8)RBA_ETHTCP_POS_CHKSUM_E, 0U )

	/* Call the checksum calculation function */
	/* MR12 DIR 1.1 VIOLATION: The input parameters of TcpIp_OnesComplChkSum() are declared as (void*) for generic implementation. */
	lRetVal_en = TcpIp_OnesComplChkSum( RxData_pu8,
										PseudoHdr_cpst,
										LenByte_u16,
										&lCalculatedChksum_u16);

	/* ------------------------------ */
	/* Verify received checksum       */
	/* ------------------------------ */

	/* If the checksum is correct */
	if( ( lRetVal_en == E_OK ) && ( lCalculatedChksum_u16 == lRcvdChksum_u16 ) )
	{
		lFunctionRetVal_en = E_OK;
	}

    return lFunctionRetVal_en;
}
#endif


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_ReadMssOption()		- Extract the Maximum Segment Size value from the MSS option								**/
/**																																**/
/** Parameters (in):																											**/
/** OptionPtr_cpu8 					- The pointer to the MSS option																**/
/** RemainingOptionLen_u16 			- Remaining number of bytes for the Tcp options												**/
/**																																**/
/** Parameters (inout):				None																						**/
/**																																**/
/** Parameters (out):																											**/
/** MssValue_pu16 					- MSS value advertised by the remote in the received TCP segment							**/
/**																																**/
/** Return value:					- uint8																						**/
/**										Number of bytes processed during the extracting of the MSS option						**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( uint8, RBA_ETHTCP_CODE ) rba_EthTcp_ReadMssOption( P2CONST( uint8, AUTOMATIC, AUTOMATIC ) 	OptionPtr_cpu8,
																VAR( uint16, AUTOMATIC )       			RemainingOptionLen_u16,
																P2VAR( uint16, AUTOMATIC, AUTOMATIC ) 	MssValue_pu16 )
{
	/* Declare local variables */
	VAR( uint8, AUTOMATIC )       						lProcessedBytes_u8;
	VAR( uint8, AUTOMATIC )       						lLengthField_u8;

	/* Initialize the processed bytes to 0 */
	lProcessedBytes_u8 = 0U;

	/* Check if it remains sufficient bytes in the Tcp options for an MSS option */
	if( RemainingOptionLen_u16 >= RBA_ETHTCP_OPT_LENGTH_MSS )
	{
		/* Read the Length field */
		lLengthField_u8 = RBA_ETHTCP_READ_8BITS_AT_POS( OptionPtr_cpu8, (uint8)RBA_ETHTCP_POS_OPT_LEN_E );

		/* Check if MSS option is valid */
		/* (means the length of the MSS option is not illegal) */
		if( lLengthField_u8 == RBA_ETHTCP_OPT_LENGTH_MSS )
		{
			/* Read MSS value and set as out agrument of the function */
			(*MssValue_pu16) = RBA_ETHTCP_READ_16BITS_AT_POS( OptionPtr_cpu8, (uint8)RBA_ETHTCP_POS_OPT_VAL_E );

			/* Set the number of processed bytes */
			lProcessedBytes_u8 = lLengthField_u8;
		}
	}

    return lProcessedBytes_u8;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */






















