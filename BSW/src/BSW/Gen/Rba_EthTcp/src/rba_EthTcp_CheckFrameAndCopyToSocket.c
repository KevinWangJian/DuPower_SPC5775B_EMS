

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
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_ExtractFromFrame 			( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )               LocalAddrId_u8,
                                                                                          P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )  PseudoHdr_cpst,
																						  P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 					RxData_pu8,
																						  VAR( uint16, AUTOMATIC ) 								LenByte_u16,
																						  P2VAR( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_pst );

static FUNC( rba_EthTcp_SocketType_ten, RBA_ETHTCP_CODE ) rba_EthTcp_BestMatchAlgorithm ( P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst,
																						  P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )  	TcpDynSockTblIdx_puo );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_FrameClosedState 			( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_FrameListenState 			( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          VAR( rba_EthTcp_SocketType_ten, RBA_ETHTCP_CODE )     SocketType_en,
																						  P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )	RxFrame_pcst,
																						  P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC ) 	ForkedSockTblIdx_puo );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_FrameListenStateFork         ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )	RxFrame_pcst,
                                                                                          P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )     ForkedSockTblIdx_puo );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_FrameSynSentState 			( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_FrameOtherState 				( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2VAR( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_pst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_FrameOtherStateReopen        ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_FrameOtherStateSeqInvalid    ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_FrameOtherStateSeqOutOfOrder ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst );

static FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_FrameOtherStateIdealize      ( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          VAR( rba_EthTcp_SeqVal_ten, AUTOMATIC )               ValidRcvdSeqNum_en,
                                                                                          P2VAR( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )   RxFrame_pst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_FrameOtherStateSeqValid 		( VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpDynSockTblIdx_uo,
                                                                                          P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_FrameOtherStateSeqValidAckPresent ( VAR( TcpIp_SocketIdType, AUTOMATIC )             TcpDynSockTblIdx_uo,
                                                                                               P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_cpst );

static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameNoConn 					( P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_pcst );
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
/** rba_EthTcp_CheckFrameAndCopyToSocket()	- This function find the Tcp socket index for the received Tcp frame and copy the  	**/
/**											received information into the socket table (if the frame is valid)					**/
/**																																**/
/** Parameters (in):																											**/
/** LocalAddrId_u8                          - LocalAddrId on which the frame is received                                        **/
/** PseudoHdr_cpst                          - Pointer to pusedo header structure                                                **/
/** RxData_pu8 	    						- Pointer to the Tcp header															**/
/** LenByte_u16	    						- Total length of Tcp frame	(in bytes)												**/
/**																																**/
/** Parameters (inout):						None																				**/
/**																																**/
/** Parameters (out):																											**/
/** TcpDynSockTblIdx_puo             		- rba_EthTcp dynamic table index                                                    **/
/**																																**/
/** Return value:							- Std_ReturnType																	**/
/** 											E_OK: The request was processed													**/
/** 											E_NOT_OK: The request was canceled due to errors								**/
/**																																**/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_CheckFrameAndCopyToSocket ( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )              LocalAddrId_u8,
                                                                               P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC ) PseudoHdr_cpst,
                                                                               P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 			    RxData_pu8,
                                                                               VAR( uint16, AUTOMATIC ) 						    LenByte_u16,
                                                                               P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )    TcpDynSockTblIdx_puo )
{
	/* Declare local variables */
    VAR( rba_EthTcp_SocketType_ten, AUTOMATIC )                         lFoundSocketType_en;
	VAR( rba_EthTcp_Frame_tst, AUTOMATIC ) 								lRxFrame_st;
	VAR( TcpIp_SocketIdType, AUTOMATIC ) 								lTcpDynSockTblIdx_uo;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;
	/* -------------------------------------------- */
	/* Extract from received frame 					*/
	/* -------------------------------------------- */
	/* initialisation of lRxFrame_st to avoid MISRA C:2012 Rule-9.1 violation*/
	lRxFrame_st.DataLen_u16 = 0;
	lRxFrame_st.DataOffset_u16 = 0;
	lRxFrame_st.DomainType_u32 = 0;
	lRxFrame_st.Header_st.AckNum_u32 = 0;
	lRxFrame_st.Header_st.DestPort_u16 = 0;
	lRxFrame_st.Header_st.HdrFlag_u8 = 0;
	lRxFrame_st.Header_st.HdrLen_u16 = 0;
	lRxFrame_st.Header_st.SeqNum_u32 = 0;
	lRxFrame_st.Header_st.SrcPort_u16 = 0;
	lRxFrame_st.Header_st.WndSize_u16 = 0;
	lRxFrame_st.LocalAddrId_u8 = 0;
	lRxFrame_st.Options_st.Mss_u16 = 0;
	lRxFrame_st.PayloadLen_u16 = 0;

#if (TCPIP_IPV6_ENABLED == STD_ON)
    lRxFrame_st.RemoteIPAddr_un.IPv6Addr_au32[0] = 0;
    lRxFrame_st.RemoteIPAddr_un.IPv6Addr_au32[1] = 0;
    lRxFrame_st.RemoteIPAddr_un.IPv6Addr_au32[2] = 0;
    lRxFrame_st.RemoteIPAddr_un.IPv6Addr_au32[3] = 0;
#endif

#if (TCPIP_IPV4_ENABLED == STD_ON)
    lRxFrame_st.RemoteIPAddr_un.IPv4Addr_u32 = 0;
#endif

	lRxFrame_st.RemotePort_u16 = 0;

	/* Verify if the received frame is not malformed and extract all needed fields */
	lRetVal_en = rba_EthTcp_ExtractFromFrame( 	LocalAddrId_u8,
	                                            PseudoHdr_cpst,
												RxData_pu8,
												LenByte_u16,
												&lRxFrame_st );

	if( lRetVal_en == E_OK )
	{
		/* --------------------------------- */
		/* Execute Tcp Best Match Algorithm	 */
		/* --------------------------------- */

        /* Initialize the dynamic socket table index */
        lTcpDynSockTblIdx_uo = RBA_ETHTCP_TCPSOCK_UNUSED;

		/* Find the socket that match with the received frame */
		lFoundSocketType_en = rba_EthTcp_BestMatchAlgorithm (	&lRxFrame_st,
																&lTcpDynSockTblIdx_uo );

		/* ---------------------------------------- */
		/* Matching socket found					*/
		/* ---------------------------------------- */
		if ( lFoundSocketType_en != RBA_ETHTCP_SOC_NONE_E )
		{
	        /* Set the out argument of the function */
	        /* (index of the matching Tcp socket) */
	        ( * TcpDynSockTblIdx_puo ) = lTcpDynSockTblIdx_uo;

			/* If no RESET is going to be sent by the Tcp socket */
			if( (rba_EthTcp_DynSockTbl_ast[lTcpDynSockTblIdx_uo].TcpFlag_en != RBA_ETHTCP_SEND_RST_E)		&&
				(rba_EthTcp_DynSockTbl_ast[lTcpDynSockTblIdx_uo].TcpFlag_en != RBA_ETHTCP_SEND_RST_ACK_E) )
			{
				switch ( rba_EthTcp_DynSockTbl_ast[lTcpDynSockTblIdx_uo].State_en )
				{
					/* -------------------------------- */
					/* Check and copy for CLOSED state	*/
					/* -------------------------------- */
					case RBA_ETHTCP_CONN_CLOSED_E:
					{
						lFunctionRetVal_en = rba_EthTcp_FrameClosedState( 	lTcpDynSockTblIdx_uo,
						                                                    &lRxFrame_st );
					}
					break;

					/* -------------------------------- */
					/* Check and copy for LISTEN state	*/
					/* -------------------------------- */
					case RBA_ETHTCP_CONN_LISTEN_E:
					{
						lFunctionRetVal_en = rba_EthTcp_FrameListenState( 	lTcpDynSockTblIdx_uo,
						                                                    lFoundSocketType_en,
																			&lRxFrame_st,
																			&lTcpDynSockTblIdx_uo );

                        /* Update the out argument of the function */
                        /* (index of the forked Tcp socket) */
                        ( * TcpDynSockTblIdx_puo ) = lTcpDynSockTblIdx_uo;
					}
					break;

					/* --------------------------------- */
					/* Check and copy for SYN SENT state */
					/* --------------------------------- */
					case RBA_ETHTCP_CONN_SYN_SENT_E:
					{
						lFunctionRetVal_en = rba_EthTcp_FrameSynSentState( 	lTcpDynSockTblIdx_uo,
						                                                    &lRxFrame_st );
					}
					break;

					/* ------------------------------------------------------------------------------------------------------------------------ */
					/* Check and copy for SYN RECEIVED, ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING, LAST ACK or TIME WAIT state	*/
					/* ------------------------------------------------------------------------------------------------------------------------ */
					case RBA_ETHTCP_CONN_SYN_RCVD_E:
					case RBA_ETHTCP_CONN_ESTABLISHED_E:
					case RBA_ETHTCP_CONN_FIN_WAIT_1_E:
					case RBA_ETHTCP_CONN_FIN_WAIT_2_E:
					case RBA_ETHTCP_CONN_CLOSE_WAIT_E:
					case RBA_ETHTCP_CONN_CLOSING_E:
					case RBA_ETHTCP_CONN_LAST_ACK_E:
					case RBA_ETHTCP_CONN_TIME_WAIT_E:
					default:
					{
						lFunctionRetVal_en = rba_EthTcp_FrameOtherState(	lTcpDynSockTblIdx_uo,
						                                                    &lRxFrame_st );
					}
					break;
				}
			}
		}

		/* ---------------------------------------- */
		/* No matching socket found					*/
		/* ---------------------------------------- */
		else
		{
			/* The connection does not exist (CLOSED) - See RFC793 p36 */
			lFunctionRetVal_en = rba_EthTcp_FrameNoConn( &lRxFrame_st );
		}
	}

	return lFunctionRetVal_en;
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** rba_EthTcp_ExtractFromFrame()		- This function extracts all the necessary fields from the received Tcp frame			**/
/**																																**/
/** Parameters (in):																											**/
/** LocalAddrId_u8 						- Local address on which the frame is received										    **/
/** PseudoHdr_cpst                      - Pointer to pusedo header structure                                                    **/
/** RxData_pu8 	    					- Pointer to the Tcp header																**/
/** LenByte_u16	    					- Total length of Tcp frame	(in bytes)													**/
/**																																**/
/** Parameters (inout):					None																					**/
/**																																**/
/** Parameters (out):																											**/
/** RxFrame_pst             			- Tcp frame structure containing all the necessary information                   		**/
/**																																**/
/** Return value:                       - Std_ReturnType                                                                        **/
/**                                         E_OK: Content of received frame has been extracted                                  **/
/**                                         E_NOT_OK: Received frame is malformed                                               **/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_ExtractFromFrame (    VAR( TcpIp_LocalAddrIdType, AUTOMATIC )                 LocalAddrId_u8,
                                                                                P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )    PseudoHdr_cpst,
																	            P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 					RxData_pu8,
																	            VAR( uint16, AUTOMATIC ) 								LenByte_u16,
																	            P2VAR( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_pst )
{
	/* Declare local variables */
	VAR( Std_ReturnType, AUTOMATIC ) 									lFunctionRetVal_en;
	VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK and lRetVal_en to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;
	lRetVal_en         = E_NOT_OK;

    /* -------------------------------------------- */
    /* Frame length verification 					*/
    /* -------------------------------------------- */

    /* Check if the total length of the frame is greater or equal to the default Tcp header length (20 bytes) */
    if( LenByte_u16 >= RBA_ETHTCP_DFL_HDRLENGTH )
    {
        /* -------------------------------------------- */
        /* Checksum verification 						*/
        /* -------------------------------------------- */

#if ( RBA_ETHTCP_SW_CHKSUM_RX == STD_ON )
        /* Check the validity of the checksum in the received frame if H/w is not capabled of doing it*/
        lRetVal_en = rba_EthTcp_RcvdChecksumValidity(PseudoHdr_cpst,
                                                     RxData_pu8,
                                                     LenByte_u16 );

#elif( RBA_ETHTCP_REASSMBLY_RX_ENABLED == STD_ON )
        /* Check the validity of the checksum in the received frame if it is reassembled */
        if( TRUE == PseudoHdr_cpst->IsRxFragmented_b )
        {
            lRetVal_en = rba_EthTcp_RcvdChecksumValidity(PseudoHdr_cpst,
                                                         RxData_pu8,
                                                         LenByte_u16 );
        }
        else
        {
            /* Set return value to TRUE as checksum is calculated by H/W and frame is not reassembled(no need to recalculate checksum again in this case)*/
            lRetVal_en = E_OK;
        }
#else
        /* H/w has already calculated checksum and reassemby feature is not supported so set lRetVal_en to E_OK */
        lRetVal_en = E_OK;
#endif
        /* If Rx Checksum is valid */
        if ( lRetVal_en == E_OK )
        {
            /* -------------------------------------------- */
            /* Extract default header						*/
            /* -------------------------------------------- */

            /* Extract the default header fields */
            rba_EthTcp_GetHdrFromFrame( RxData_pu8, &(RxFrame_pst->Header_st) );

            /* Received Tcp header length shall be greater than or equal to 20 bytes and shall be lower than or equal to the total frame length */
            if( (RxFrame_pst->Header_st.HdrLen_u16 >= RBA_ETHTCP_DFL_HDRLENGTH) 		&&
                (RxFrame_pst->Header_st.HdrLen_u16 <= LenByte_u16) )
            {
                /* -------------------------------------------- */
                /* Extract options								*/
                /* -------------------------------------------- */

                /* Extract all the present options */
                rba_EthTcp_GetOptionFromFrame( RxData_pu8, &(RxFrame_pst->Options_st) );

                /* -------------------------------------------- */
                /* Extract payload and data length  			*/
                /* -------------------------------------------- */

                /* Extract payload length (SEG.LEN) */
                /* (The payload length counts the real data and the sequence number space occupied by SYN or FIN bit) */
                RxFrame_pst->PayloadLen_u16 = rba_EthTcp_GetPayloadLenFromFrame( RxData_pu8, LenByte_u16 );

                /* Compute data offset */
                /* (Indicated from where the data begin in the received frame) */
                RxFrame_pst->DataOffset_u16 = RxFrame_pst->Header_st.HdrLen_u16;

                /* Compute data length */
                /* (The data length counts only the real data) */
                RxFrame_pst->DataLen_u16 = ( LenByte_u16 - RxFrame_pst->Header_st.HdrLen_u16 );

                RxFrame_pst->DomainType_u32 = PseudoHdr_cpst->IpDomainType_t;    /* Received domain type */

                /* Local address */
                RxFrame_pst->LocalAddrId_u8 = LocalAddrId_u8;    /* Local address idx */
                RxFrame_pst->LocalPort_u16 = RxFrame_pst->Header_st.DestPort_u16;

                /* Remote address */
                RBA_ETHTCP_COPY_PSEUDOHDR_TO_IP( &(RxFrame_pst->RemoteIPAddr_un), PseudoHdr_cpst )
                RxFrame_pst->RemotePort_u16 = RxFrame_pst->Header_st.SrcPort_u16;

                /* Set the return value of the function to E_OK */
                /* (Extracting of the fields is a success) */
                lFunctionRetVal_en = E_OK;
            }
        }
    }

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_BestMatchAlgorithm()		- This function find the corresponding Tcp socket for the received frame : 				**/
/**											1) Try to find a socket with specified remote IP and Port  							**/
/**											2) Try to find a socket with unspecified remote IP and Port (ANY)					**/
/**																																**/
/** Parameters (in):																											**/
/** RxFrame_cpst 						- Pointer to the content of the received Tcp frame										**/
/**																																**/
/** Parameters (inout):					None																					**/
/**																																**/
/** Parameters (out):																											**/
/** TcpDynSockTblIdx_puo             	- Found rba_EthTcp dynamic table index                                              	**/
/**																																**/
/** Return value:						- rba_EthTcp_SocketType_ten																**/
/** 										RBA_ETHTCP_SOC_UNSPECIFIED_REMOTE_E: Received frame is aimed to a socket with 		**/
/** 																			 unspecified remote IP and Port (ANY) 			**/
/** 										RBA_ETHTCP_SOC_SPECIFIED_REMOTE_E: Received frame is aimed to a socket with 		**/
/** 																		   specified remote IP and Port 					**/
/** 										RBA_ETHTCP_SOC_NONE_E: No socket found for the received frame						**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( rba_EthTcp_SocketType_ten, RBA_ETHTCP_CODE ) rba_EthTcp_BestMatchAlgorithm (	P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_cpst,
																							P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )  		TcpDynSockTblIdx_puo )
{
	/* Declare local variables */
	VAR( rba_EthTcp_SocketType_ten, AUTOMATIC )          			lSocketType_en;
	VAR( TcpIp_SocketIdType, AUTOMATIC )                            lIdx_uo;

	/* Initialize the found socket type to NONE */
	lSocketType_en = RBA_ETHTCP_SOC_NONE_E;

	/* Loop through all Tcp sockets */
	for ( lIdx_uo = 0U; lIdx_uo < TCPIP_TCPSOCKETMAX; lIdx_uo++ )
	{
	    /* Get socket only when it is OPENED already */
	    if ( rba_EthTcp_DynSockTbl_ast[lIdx_uo].SockState_en == RBA_ETHTCP_SOCK_OPENED_E )
	    {
            /* --------------------------------------------- */
            /* Check if local address id and Port match	 	 */
            /* --------------------------------------------- */
            if ( ( rba_EthTcp_DynSockTbl_ast[lIdx_uo].LocalAddrId_u8 == RxFrame_cpst->LocalAddrId_u8 ) &&
                  (rba_EthTcp_DynSockTbl_ast[lIdx_uo].LocalPort_u16  == RxFrame_cpst->LocalPort_u16 ) )
            {
                /* --------------------------------------------- */
                /* Check if remote IP and Port match 	 		 */
                /* --------------------------------------------- */
                if ( RBA_ETHTCP_CHECK_IPADDR_EQUAL( rba_EthTcp_DynSockTbl_ast[lIdx_uo].DomainType_u32, &(rba_EthTcp_DynSockTbl_ast[lIdx_uo].RemoteIPAddr_un), &(RxFrame_cpst->RemoteIPAddr_un) ) &&
                     ( rba_EthTcp_DynSockTbl_ast[lIdx_uo].RemotePort_u16 == RxFrame_cpst->RemotePort_u16 ) )
                {
                    /* Set the out argument of the function (index of the found Tcp socket) */
                    ( * TcpDynSockTblIdx_puo ) = lIdx_uo;

                    /* Set the flag to indicate that a socket with specified remote IP and Port is found */
                    lSocketType_en = RBA_ETHTCP_SOC_SPECIFIED_REMOTE_E;

                    /* Stop the loop because the exactly matching socket has been found */
                    break;
                }

                /* --------------------------------------------- */
                /* Check if remote IP and Port are equal to ANY  */
                /* --------------------------------------------- */
                if ( RBA_ETHTCP_IS_IPADDR_ANY( rba_EthTcp_DynSockTbl_ast[lIdx_uo].DomainType_u32, &(rba_EthTcp_DynSockTbl_ast[lIdx_uo].RemoteIPAddr_un) ) &&
                     ( rba_EthTcp_DynSockTbl_ast[lIdx_uo].RemotePort_u16 == TCPIP_PORT_ANY ) )
                {
                    /* Set the out argument of the function (index of the found Tcp socket) */
                    ( * TcpDynSockTblIdx_puo ) = lIdx_uo;

                    /* Set the flag to indicate that a socket with unspecified remote IP and Port is found */
                    lSocketType_en = RBA_ETHTCP_SOC_UNSPECIFIED_REMOTE_E;

                    /* Continue to loop in order to give the chance to find a socket with specified remote IP and Port */
                }
            }
        }
	}

	return lSocketType_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_CheckFrameClosedState()	- This function check the received frame when the socket is in CLOSED state. If the 	**/
/**										frame is valid, then the information are copied into the Tcp socket for further 		**/
/**										processing.																				**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index                                                        **/
/** RxFrame_cpst 						- Pointer to the content of the received Tcp frame										**/
/**																																**/
/** Parameters (inout):	                None																					**/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:						- Std_ReturnType																		**/
/** 										E_OK: The received frame is valid and copied into the socket						**/
/** 										E_NOT_OK: The received frame is not valid for further processing					**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameClosedState (	VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_cpst )
{
    /* ----------------------------- */
    /* RST bit set                   */
    /* ----------------------------- */
	if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
    {
        /* Drop the segment */
	    /* (RFC793 p65 : An incoming segment containing RST is discarded) */
    }

    /* ----------------------------- */
    /* ACK bit set (with no RST bit) */
    /* ----------------------------- */
	else if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        /* Send a RST frame */
        /* (As there is an ACK bit in the received frame, send RST - see RFC793 p36/37) */

        /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
        /* (seq number of the RST frame will be same as the received ack number) */
        rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, RxFrame_cpst->Header_st.AckNum_u32 );
        rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, 0U );

        /* Send a RST in the next MainFunction */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_E );

        /* Drop the segment */
    }

    /* ----------------------------- */
    /* No RST and no ACK bit 	 	 */
    /* ----------------------------- */
	else
    {
        /* Send a RST ACK frame */
        /* (As there is no ACK bit in the received frame, send RST ACK - see RFC793 p36/37) */

        /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
        /* (seq number of the RST-ACK frame will be 0, ack number will be (Received SeqNum + Segment length)) */
        rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, 0U );
        rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, ( RxFrame_cpst->Header_st.SeqNum_u32 + ( (uint32)RxFrame_cpst->PayloadLen_u16 ) ) );

        /* Send a RST ACK in the next MainFunction */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

        /* Drop the segment */
    }

    /* Drop the segment */
    return E_NOT_OK;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_CheckFrameListenState()	- This function check the received frame when the socket is in LISTEN state. If the 	**/
/**										frame is valid, then the information are copied into the Tcp socket for further 		**/
/**										processing.																				**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index                                                        **/
/** SocketType_en                       - Type of socket on which the frame is received (SOC_SPECIFIED_REMOTE or                **/
/**                                     SOC_UNSPECIFIED_REMOTE)                                                                 **/
/** RxFrame_pcst 						- Pointer to the content of the received Tcp frame										**/
/**																																**/
/** Parameters (inout):				    None																					**/
/**																																**/
/** Parameters (out):																										    **/
/** ForkedSockTblIdx_puo                - Tcp dynamic socket table index of the forked socket when valid SYN is received        **/
/**																																**/
/** Return value:						- Std_ReturnType																		**/
/** 										E_OK: The received frame is valid and copied into the socket						**/
/** 										E_NOT_OK: The received frame is not valid for further processing					**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameListenState (	VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                VAR( rba_EthTcp_SocketType_ten, RBA_ETHTCP_CODE )       SocketType_en,
																				P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_pcst,
																				P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC ) 		ForkedSockTblIdx_puo )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( TcpIp_SocketIdType, AUTOMATIC )                                lNewSockTblIdx_uo;
	VAR( rba_EthTcp_NewSockInfo_tst, AUTOMATIC )						lNewSockInfo_st;
	VAR( Std_ReturnType, AUTOMATIC ) 									lFunctionRetVal_en;
	VAR( Std_ReturnType, AUTOMATIC ) 									lRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* RST bit set 					 */
    /* ----------------------------- */
    if ( (RxFrame_pcst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
    {
        /* Drop the segment */
        /* (RFC793 p65 : An incoming RST should be ignored) */
    }

    /* ----------------------------- */
    /* ACK bit set (with no RST bit) */
    /* ----------------------------- */
    else if ( (RxFrame_pcst->Header_st.HdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        /* Socket with unspecified remote : get a new socket for the sending of a reset */
        if ( SocketType_en == RBA_ETHTCP_SOC_UNSPECIFIED_REMOTE_E )
        {
			/* Build a new socket info variable */
			lNewSockInfo_st.LocalAddrId_u8		= RxFrame_pcst->LocalAddrId_u8;
			lNewSockInfo_st.LocalPort_u16		= RxFrame_pcst->LocalPort_u16;
			lNewSockInfo_st.RemotePort_u16		= RxFrame_pcst->RemotePort_u16;
			lNewSockInfo_st.DomainType_u32		= RxFrame_pcst->DomainType_u32;
			lNewSockInfo_st.RemoteIPAddr_un	    = RxFrame_pcst->RemoteIPAddr_un;
			lNewSockInfo_st.FramePrio_u8		= lTcpDynSockTbl_pst->SockFramePrio_u8;

            /* Get a new Tcp socket (for the sending of a reset) */
            lRetVal_en = rba_EthTcp_GetNewSock ( &lNewSockInfo_st,
                                                 &lNewSockTblIdx_uo );
        }
        /* Socket with specified remote */
        else
        {
            /* There is no need to get a new socket because current socket is fully specified */
            lNewSockTblIdx_uo = TcpDynSockTblIdx_uo;
            lRetVal_en = E_OK;
        }

        /* If no error occured previously */
        if ( lRetVal_en == E_OK )
        {
            /* Send a RST frame */
            /* (As there is an ACK bit in the received frame, send RST - see RFC793 p36/37) */

            /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
            /* (seq number of the RST frame will be same as the received ack number) */
            rba_EthTcp_SetSeqNum( lNewSockTblIdx_uo, RxFrame_pcst->Header_st.AckNum_u32 );
            rba_EthTcp_SetAckNum( lNewSockTblIdx_uo, 0U );

            /* Send a RST in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( lNewSockTblIdx_uo, RBA_ETHTCP_SEND_RST_E );

            /* Drop the segment */
        }
    }

    /* ---------------------------------------- */
    /* SYN bit set (with no RST and no ACK bit) */
    /* ---------------------------------------- */
    else if ( (RxFrame_pcst->Header_st.HdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
        /* The frame is valid (we received a [SYN])*/

        /* Socket with unspecified remote : create a forked socket linked to the listening socket */
        if ( SocketType_en == RBA_ETHTCP_SOC_UNSPECIFIED_REMOTE_E )
        {
            /* Execute the creation of a forked socket to handle the new connection request */
            lRetVal_en = rba_EthTcp_FrameListenStateFork(   TcpDynSockTblIdx_uo,
                                                            RxFrame_pcst,
                                                            &lNewSockTblIdx_uo );
        }

        /* Socket with specified remote */
        else
        {
            /* There is no need to get a new socket because current socket is fully specified */
            lNewSockTblIdx_uo = TcpDynSockTblIdx_uo;
            lRetVal_en = E_OK;
        }

        /* If no error occured */
        if ( lRetVal_en == E_OK )
        {
            /* Set the out argument of the function (index of the forked socket) */
            ( * ForkedSockTblIdx_puo ) = lNewSockTblIdx_uo;

            /* Get Tcp dynamic table entry from Tcp socket index */
            lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[lNewSockTblIdx_uo] ) );

            /* Copy the received header in the Tcp dynamic table entry */
            lTcpDynSockTbl_pst->IniRcvdSeqNum_u32   = RxFrame_pcst->Header_st.SeqNum_u32;
            lTcpDynSockTbl_pst->RcvdSeqNum_u32      = RxFrame_pcst->Header_st.SeqNum_u32;
            lTcpDynSockTbl_pst->RcvdAckNum_u32      = 0U;                           /* 0 as the ACK bit is not set in the received frame */
            lTcpDynSockTbl_pst->RcvdHdrFlag_u8      = RxFrame_pcst->Header_st.HdrFlag_u8;
            lTcpDynSockTbl_pst->RcvdMss_u16         = RxFrame_pcst->Options_st.Mss_u16;
            lTcpDynSockTbl_pst->RcvdDataLen_u16     = RxFrame_pcst->DataLen_u16;
            lTcpDynSockTbl_pst->RcvdDataOffset_u16  = RxFrame_pcst->DataOffset_u16;

            /* Set the return value of the function to E_OK */
            /* (segment is accepted) */
            lFunctionRetVal_en = E_OK;
        }
    }

    /* ----------------------------- */
    /* No RST, no ACK and no SYN bit */
    /* ----------------------------- */
    else
    {
        /* Drop the segment */
    }

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameListenStateFork()   - This function create a forked socket which will be used to handle the connection      **/
/**                                     request                                                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index                                                        **/
/** RxFrame_pcst                         - Pointer to the content of the received Tcp frame                                      **/
/**                                                                                                                             **/
/** Parameters (inout):                 None                                                                                    **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** ForkedSockTblIdx_puo                - Tcp dynamic socket table index of the forked socket                                   **/
/**                                                                                                                             **/
/** Return value:                       - Std_ReturnType                                                                        **/
/**                                         E_OK: Forked socket has been created and linked to the listening socket             **/
/**                                         E_NOT_OK: Forked socket cannot be created                                           **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameListenStateFork (    VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                    P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )	RxFrame_pcst,
                                                                                    P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC )       ForkedSockTblIdx_puo )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
	VAR( rba_EthTcp_NewSockInfo_tst, AUTOMATIC )						lNewSockInfo_st;
    VAR( TcpIp_SocketIdType, AUTOMATIC )                                lForkedSockTblIdx_uo;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ------------------------------- */
    /* Open new socket                 */
    /* ------------------------------- */

	/* Build a new socket info variable */
	lNewSockInfo_st.LocalAddrId_u8		= RxFrame_pcst->LocalAddrId_u8;
	lNewSockInfo_st.LocalPort_u16		= RxFrame_pcst->LocalPort_u16;
	lNewSockInfo_st.RemotePort_u16		= RxFrame_pcst->RemotePort_u16;
	lNewSockInfo_st.DomainType_u32		= RxFrame_pcst->DomainType_u32;
	lNewSockInfo_st.RemoteIPAddr_un	    = RxFrame_pcst->RemoteIPAddr_un;
	lNewSockInfo_st.FramePrio_u8		= lTcpDynSockTbl_pst->SockFramePrio_u8;

    /* Get a new Tcp socket (will be used as forked socket) */
    lRetVal_en = rba_EthTcp_GetNewSock ( &lNewSockInfo_st,
                                         &lForkedSockTblIdx_uo );
    if ( lRetVal_en == E_OK )
    {
        /* ------------------------------- */
        /* Link to listening socket        */
        /* ------------------------------- */

        /* Link the new socket to the listening socket (the new socket should be a forked socket) */
        lRetVal_en = rba_EthTcp_LinkToListeningSock( lForkedSockTblIdx_uo );

        if ( lRetVal_en == E_OK )
        {
            /* Set the out argument of the function (index of the forked socket) */
            ( * ForkedSockTblIdx_puo ) = lForkedSockTblIdx_uo;

            /* Set the connection state of the forked socket to LISTEN */
            rba_EthTcp_SetConnectionState( lForkedSockTblIdx_uo, RBA_ETHTCP_CONN_LISTEN_E );

            /* Now this socket is OPENED for communication */
            rba_EthTcp_DynSockTbl_ast[lForkedSockTblIdx_uo].SockState_en = RBA_ETHTCP_SOCK_OPENED_E;

            /* Set the return value of the function to E_OK */
            /* (creation of a forked socket is a success) */
            lFunctionRetVal_en = E_OK;
        }

        /* If the linking is a failure */
        else
        {
            /* Send a RST ACK frame */
            /* (As there is no ACK bit in the received frame, send RST ACK - see RFC793 p36/37) */

            /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
            /* (seq number of the RST-ACK frame will be 0, ack number will be (Received SeqNum + Segment length)) */
            rba_EthTcp_SetSeqNum( lForkedSockTblIdx_uo, 0U );
            rba_EthTcp_SetAckNum( lForkedSockTblIdx_uo, (RxFrame_pcst->Header_st.SeqNum_u32 + ((uint32)RxFrame_pcst->PayloadLen_u16)) );

            /* Send a RST ACK in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( lForkedSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

            /* Drop the segment */
        }
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_CheckFrameSynSentState()	- This function check the received frame when the socket is in SYN_SENT state. 			**/
/**										If the frame is valid, then the information are copied into the Tcp socket for 			**/
/**										further processing.																		**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo                 - Tcp dynamic socket table index                                                        **/
/** RxFrame_cpst 						- Pointer to the content of the received Tcp frame										**/
/**																																**/
/** Parameters (inout):		            None																				    **/
/**																																**/
/** Parameters (out):					None																					**/
/**																																**/
/** Return value:						- Std_ReturnType																		**/
/** 										E_OK: The received frame is valid and copied into the socket						**/
/** 										E_NOT_OK: The received frame is not valid for further processing					**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameSynSentState (	VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_cpst )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( rba_EthTcp_AckVal_ten, AUTOMATIC )							    lValidRcvdAckNum_en;
	VAR( Std_ReturnType, AUTOMATIC ) 									lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* ACK bit set                   */
    /* ----------------------------- */
    if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        /* Check acknowledgment number validity */
        lValidRcvdAckNum_en = rba_EthTcp_RcvdAckNumValidity( TcpDynSockTblIdx_uo, RxFrame_cpst->Header_st.AckNum_u32 );

        /* ----------------------------- */
        /* Unacceptable ACK 			 */
        /* ----------------------------- */

        /* Ack number is unacceptable if it is invalid (SEG.ACK =< ISS or SEG.ACK > SND.NXT) */
        if ( lValidRcvdAckNum_en == RBA_ETHTCP_ACK_INVALID_E )
        {
            /* If RST bit is set */
            if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
            {
                /* Drop the segment */
                /* (RFC793 p66 : unless the RST bit is set, if so drop the segment and return) */
            }

            /* If RST bit is not set */
            else
            {
                /* Send a RST frame */
                /* (As there is an ACK bit in the received frame, send RST - see RFC793 p36/37) */

                /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
                /* (seq number of the RST frame will be same as the received ack number) */
                rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, RxFrame_cpst->Header_st.AckNum_u32 );
                rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, 0U );

                /* Send a RST in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_E );

                /* Drop the segment */
            }
        }

        /* ----------------------------- */
        /* Acceptable ACK	 			 */
        /* ----------------------------- */

        /* Ack number is acceptable if it is duplicate or new (ISS < SEG.ACK <= SND.NXT) */
        else
        {
            /* If the RST bit is set */
            if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
            {
                /* Reset the socket */
                rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );

                /* Drop the segment */
            }

            /* If RST bit is not set */
            else
            {
                /* The frame is valid (we received an [ACK] or a [SYN, ACK])*/
                /* Copy the received header in the Tcp dynamic table entry */
                lTcpDynSockTbl_pst->IniRcvdSeqNum_u32	= RxFrame_cpst->Header_st.SeqNum_u32;
                lTcpDynSockTbl_pst->RcvdSeqNum_u32 	 	= RxFrame_cpst->Header_st.SeqNum_u32;
                lTcpDynSockTbl_pst->RcvdAckNum_u32 	 	= RxFrame_cpst->Header_st.AckNum_u32;
                lTcpDynSockTbl_pst->RcvdHdrFlag_u8 		= RxFrame_cpst->Header_st.HdrFlag_u8;
                lTcpDynSockTbl_pst->RcvdMss_u16 		= RxFrame_cpst->Options_st.Mss_u16;
                lTcpDynSockTbl_pst->RcvdDataLen_u16		= RxFrame_cpst->DataLen_u16;
                lTcpDynSockTbl_pst->RcvdDataOffset_u16	= RxFrame_cpst->DataOffset_u16;

                /* Rcvd Wnd Update - see RFC1122 p94 */
                rba_EthTcp_SetRcvdWnd( 	TcpDynSockTblIdx_uo,
                                        RxFrame_cpst->Header_st.SeqNum_u32,
                                        RxFrame_cpst->Header_st.AckNum_u32,
                                        RxFrame_cpst->Header_st.WndSize_u16 );

                /* Set the return value of the function to E_OK */
                /* (segment is accepted) */
                lFunctionRetVal_en = E_OK;
            }
        }
    }

    /* ----------------------------- */
    /* RST bit set (with no ACK bit) */
    /* ----------------------------- */
    else if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
    {
        /* Drop the segment */
        /* (RFC793 p67 : Otherwise (no ACK) drop the segment and return) */
    }

    /* ---------------------------------------- */
    /* SYN bit set (with no ACK and no RST bit) */
    /* ---------------------------------------- */
    else if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
        /* The frame is valid (we received a [SYN] -> simultaneous open)*/
        /* Copy the received header in the Tcp dynamic table entry */
        lTcpDynSockTbl_pst->IniRcvdSeqNum_u32	= RxFrame_cpst->Header_st.SeqNum_u32;
        lTcpDynSockTbl_pst->RcvdSeqNum_u32		= RxFrame_cpst->Header_st.SeqNum_u32;
        lTcpDynSockTbl_pst->RcvdAckNum_u32		= 0U;							/* 0 as the ACK bit is not set in the received frame */
        lTcpDynSockTbl_pst->RcvdHdrFlag_u8		= RxFrame_cpst->Header_st.HdrFlag_u8;
        lTcpDynSockTbl_pst->RcvdMss_u16 		= RxFrame_cpst->Options_st.Mss_u16;
        lTcpDynSockTbl_pst->RcvdDataLen_u16		= RxFrame_cpst->DataLen_u16;
        lTcpDynSockTbl_pst->RcvdDataOffset_u16	= RxFrame_cpst->DataOffset_u16;

        /* Set the return value of the function to E_OK */
        /* (segment is accepted) */
        lFunctionRetVal_en = E_OK;
    }

    /* ----------------------------- */
    /* No ACK, no RST and no SYN bit */
    /* ----------------------------- */
    else
    {
        /* Drop the segment */
    }

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameOtherState()	- This function check the received frame when the connection state is SYN RECEIVED,  		**/
/**									ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING, LAST ACK or TIME WAIT. If the     **/
/**									frame is valid, then the information are copied into the Tcp socket for further processing.	**/
/**											 																					**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo             - Tcp dynamic socket table index                                                            **/
/**																																**/
/** Parameters (inout):	            None																						**/
/**																																**/
/** Parameters (out):                                                                                                           **/
/** TcpFrame_pst                    - Pointer to the content of the received Tcp frame                                          **/
/**																																**/
/** Return value:					- Std_ReturnType																			**/
/** 									E_OK: The received frame is valid and copied into the socket							**/
/** 									E_NOT_OK: The received frame is not valid for further processing						**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameOtherState (	VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                            P2VAR( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_pst )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( rba_EthTcp_SeqVal_ten, AUTOMATIC )								lValidRcvdSeqNum_en;
	VAR( Std_ReturnType, AUTOMATIC ) 									lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

	/* ------------------------------- */
	/* Check sequence number validity  */
	/* ------------------------------- */

	/* Check sequence number validity as per RFC793 p69 */
	lValidRcvdSeqNum_en = rba_EthTcp_RcvdSeqNumValidity( 	TcpDynSockTblIdx_uo,
															RxFrame_pst->Header_st.SeqNum_u32,
															RxFrame_pst->PayloadLen_u16 );

	/* ------------------------------- */
	/* SYN bit set for fast reopening  */
	/* ------------------------------- */

	/* Fast reopening is possible if a valid SYN is received while we are in TIME_WAIT or LAST_ACK - see RFC1122 p88 */
	/* (SYN segment is valid if it is not an old duplicate) */
	if( ((lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_TIME_WAIT_E) ||  (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_LAST_ACK_E))	&&
		((RxFrame_pst->Header_st.HdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK)													&&	/* SYN bit set */
		((RxFrame_pst->Header_st.HdrFlag_u8 & RBA_ETHTCP_ACK_MSK) != RBA_ETHTCP_ACK_MSK)													&&	/* No ACK bit set */
		((RxFrame_pst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) != RBA_ETHTCP_RST_MSK)													&&	/* No RST bit set */
		(RxFrame_pst->Header_st.SeqNum_u32 != lTcpDynSockTbl_pst->IniRcvdSeqNum_u32) )															/* Not old duplicate */
	{
		/* Execute the reopening of the socket */
        lFunctionRetVal_en = rba_EthTcp_FrameOtherStateReopen( TcpDynSockTblIdx_uo, RxFrame_pst );
	}

	/* ----------------------------- */
	/* Invalid sequence number       */
	/* ----------------------------- */
	else if ( lValidRcvdSeqNum_en == RBA_ETHTCP_SEQ_INVALID_E )
	{
        /* Execute processing when incoming segment is outside of the window */
	    lFunctionRetVal_en = rba_EthTcp_FrameOtherStateSeqInvalid( TcpDynSockTblIdx_uo, RxFrame_pst );
	}

	/* ----------------------------- */
	/* Out of order sequence number  */
	/* ----------------------------- */
	else if ( lValidRcvdSeqNum_en == RBA_ETHTCP_SEQ_OUT_OF_ORDER_E )
	{
	    /* Execute further processing when incoming segment is inside the window but out of order */
	    lFunctionRetVal_en = rba_EthTcp_FrameOtherStateSeqOutOfOrder( TcpDynSockTblIdx_uo, RxFrame_pst );
	}

	/* ----------------------------- */
	/* Valid sequence number  	     */
	/* ----------------------------- */
	else
	{
		/* Idealize the received segment - see RFC793 p70 */
	    rba_EthTcp_FrameOtherStateIdealize( TcpDynSockTblIdx_uo, lValidRcvdSeqNum_en, RxFrame_pst );

		/* Execute further processing when incoming segment is the next expected */
		lFunctionRetVal_en = rba_EthTcp_FrameOtherStateSeqValid( TcpDynSockTblIdx_uo, RxFrame_pst );
	}

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameOtherStateReopen()      - This function check the received frame when the connection state is               **/
/**                                         SYN RECEIVED, ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING, LAST ACK    **/
/**                                         or TIME WAIT and when reopening of socket is required                               **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxFrame_cpst                            - Pointer to the content of the received Tcp frame                                  **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: The received frame is valid and copied into the socket                    **/
/**                                             E_NOT_OK: The received frame is not valid for further processing                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameOtherStateReopen (   VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                    P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )   RxFrame_cpst )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ------------------------------- */
    /* Fast reopening                  */
    /* ------------------------------- */

    /* Execute socket reopening */
    lRetVal_en = rba_EthTcp_ReopenSock( TcpDynSockTblIdx_uo );

    /* If the reopening is a success */
    if ( lRetVal_en == E_OK )
    {
        /* The frame is valid (we received a [SYN] for fast reopening)*/
        /* Copy the received header in the Tcp dynamic table entry */
        lTcpDynSockTbl_pst->IniRcvdSeqNum_u32   = RxFrame_cpst->Header_st.SeqNum_u32;
        lTcpDynSockTbl_pst->RcvdSeqNum_u32      = RxFrame_cpst->Header_st.SeqNum_u32;
        lTcpDynSockTbl_pst->RcvdAckNum_u32      = 0U;                           /* 0 as the ACK bit is not set in the received frame */
        lTcpDynSockTbl_pst->RcvdHdrFlag_u8      = RxFrame_cpst->Header_st.HdrFlag_u8;
        lTcpDynSockTbl_pst->RcvdMss_u16         = RxFrame_cpst->Options_st.Mss_u16;
        lTcpDynSockTbl_pst->RcvdDataLen_u16     = RxFrame_cpst->DataLen_u16;
        lTcpDynSockTbl_pst->RcvdDataOffset_u16  = RxFrame_cpst->DataOffset_u16;

        /* Set the return value of the function to E_OK */
        /* (segment is accepted) */
        lFunctionRetVal_en = E_OK;
    }

    /* If the reopening is a failure */
    else
    {
        /* Send a RST ACK frame */
        /* (As there is no ACK bit in the received frame, send RST ACK - see RFC793 p36/37) */

        /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
        /* (seq number of the RST-ACK frame will be 0, ack number will be (Received SeqNum + Segment length)) */
        rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, 0U );
        rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (RxFrame_cpst->Header_st.SeqNum_u32 + ((uint32)RxFrame_cpst->PayloadLen_u16 )));

        /* Send a RST ACK in the next MainFunction */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

        /* Drop the segment */
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameOtherStateSeqInvalid()  - This function check the received frame when the connection state is               **/
/**                                         SYN RECEIVED, ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING, LAST ACK    **/
/**                                         or TIME WAIT and when the sequence number is invalid (outside the window)           **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxFrame_cpst                            - Pointer to the content of the received Tcp frame                                  **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: The received frame is valid and copied into the socket                    **/
/**                                             E_NOT_OK: The received frame is not valid for further processing                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameOtherStateSeqInvalid (   VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                        P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )   RxFrame_cpst )
{
    /* If RST bit is not set */
    if( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) != RBA_ETHTCP_RST_MSK )
    {
        /* Send ACK frame in the next MainFunction */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_E );
    }

    /* Drop the segment */
    return E_NOT_OK;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameOtherStateSeqOutOfOrder()   - This function check the received frame when the connection state is           **/
/**                                             SYN RECEIVED, ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING,         **/
/**                                             LAST ACK or TIME WAIT and when the sequence number is out of order              **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                         - Tcp dynamic socket table index                                                **/
/** RxFrame_cpst                                - Pointer to the content of the received Tcp frame                              **/
/**                                                                                                                             **/
/** Parameters (inout):                         None                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                           None                                                                            **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: The received frame is valid and copied into the socket                    **/
/**                                             E_NOT_OK: The received frame is not valid for further processing                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameOtherStateSeqOutOfOrder (    VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                            P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )   RxFrame_cpst )
{
    /* Cast unused argument */
    /* (RxFrame_pst argument will be used when reorder feature will be implemented) */
    (void)RxFrame_cpst;

    /* Send ACK frame in the next MainFunction */
    (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_E );

    /* Drop the segment */
    return E_NOT_OK;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameOtherStateIdealize()    - This function idealize the received Tcp segment before further processing in      **/
/**                                         SYN RECEIVED, ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING, LAST ACK or **/
/**                                         TIME WAIT when the sequence number is valid. This is according to RFC793 p70        **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** ValidRcvdSeqNum_en                      - Sequence number validity                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (inout):                                                                                                         **/
/** TcpFrame_pst                            - Pointer to the content of the received Tcp frame (will be idealized)              **/
/**                                                                                                                             **/
/** Return value:                           None                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_FrameOtherStateIdealize (   VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                            VAR( rba_EthTcp_SeqVal_ten, AUTOMATIC )                 ValidRcvdSeqNum_en,
                                                                            P2VAR( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )     RxFrame_pst )
{
    /* Declare local variables */
    VAR( uint16, AUTOMATIC )                                            lRepeatedLen_u16;
    VAR( uint16, AUTOMATIC )                                            lOutOfWindowLen_u16;

    /* If the payload length (SEG.LEN) is greater than 0 */
    if( RxFrame_pst->PayloadLen_u16 > 0U )
    {
        /* ----------------------------- */
        /* Handle repeated part          */
        /* ----------------------------- */

        /* Compute the repeated length of the segment */
        lRepeatedLen_u16 = rba_EthTcp_GetRepeatedPayloadLen(    TcpDynSockTblIdx_uo,
                                                                RxFrame_pst->Header_st.SeqNum_u32 );

        /* Idealize segment : erase repeated part */
        if( lRepeatedLen_u16 > 0U )
        {
            /* If SYN is present, it should be erased */
            /* RFC793 p26 : For sequence number purposes, the SYN is considered to occur before the first actual data octet of the segment in which it occurs */
            if ( (RxFrame_pst->Header_st.HdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
            {
                RxFrame_pst->Header_st.SeqNum_u32 += 1U;
                RxFrame_pst->Header_st.HdrFlag_u8 &= (uint8)(~RBA_ETHTCP_SYN_MSK);
                RxFrame_pst->PayloadLen_u16 -= 1U;
                lRepeatedLen_u16 -= 1U;
            }

            /* Adjust received sequence number */
            RxFrame_pst->Header_st.SeqNum_u32 += lRepeatedLen_u16;

            /* Cut off the portion of segment outside the window */
            RxFrame_pst->PayloadLen_u16 -= lRepeatedLen_u16;
            RxFrame_pst->DataOffset_u16 += lRepeatedLen_u16;
            RxFrame_pst->DataLen_u16 -= lRepeatedLen_u16;
        }

        /* ----------------------------- */
        /* Handle out of window part     */
        /* ----------------------------- */

        /* Compute the out of window length of the segment */
        lOutOfWindowLen_u16 = rba_EthTcp_GetOutOfWindowPayloadLen(  TcpDynSockTblIdx_uo,
                                                                    RxFrame_pst->Header_st.SeqNum_u32,
                                                                    RxFrame_pst->PayloadLen_u16 );

        /* Idealize segment : erase out of window part */
        if( lOutOfWindowLen_u16 > 0U )
        {
            /* If FIN is present, it should be erased */
            /* RFC793 p26 : For sequence number purposes, the FIN is considered to occur after the last actual data octet in a segment in which it occurs */
            if ( (RxFrame_pst->Header_st.HdrFlag_u8 & RBA_ETHTCP_FIN_MSK) == RBA_ETHTCP_FIN_MSK )
            {
                RxFrame_pst->Header_st.HdrFlag_u8 &= (uint8)(~RBA_ETHTCP_FIN_MSK);
                RxFrame_pst->PayloadLen_u16 -= 1U;
                lOutOfWindowLen_u16 -= 1U;
            }

            /* Cut off the portion of segment outside the window */
            RxFrame_pst->PayloadLen_u16 -= lOutOfWindowLen_u16;
            RxFrame_pst->DataLen_u16 -= lOutOfWindowLen_u16;
        }
    }

    /* ----------------------------- */
    /* Handle special allowance      */
    /* ----------------------------- */

    /* Idealize segment : special allowance case */
    if( ValidRcvdSeqNum_en == RBA_ETHTCP_SEQ_SPECIAL_ALLOWANCE_E )
    {
        /* A special allowance is made to process only the ACK, URG and RST carried by the segment */
        /* (it is therefore needed to erase the other controls and payload of the segment) */
        RxFrame_pst->Header_st.HdrFlag_u8 &= (uint8)(~RBA_ETHTCP_SYN_MSK);
        RxFrame_pst->Header_st.HdrFlag_u8 &= (uint8)(~RBA_ETHTCP_PSH_MSK);
        RxFrame_pst->Header_st.HdrFlag_u8 &= (uint8)(~RBA_ETHTCP_FIN_MSK);
        RxFrame_pst->DataLen_u16 = 0U;

        /* For special allowance, it is needed to send an ACK */
        (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_E );
    }

    return;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameOtherStateSeqValid()	- This function check the received frame when the connection state is  				**/
/**											SYN RECEIVED, ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING, LAST ACK  	**/
/**											or TIME WAIT and when the sequence number is valid									**/
/**																																**/
/** Parameters (in):																											**/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxFrame_cpst 							- Pointer to the content of the received Tcp frame									**/
/**																																**/
/** Parameters (inout):			            None    																			**/
/**																																**/
/** Parameters (out):						None																				**/
/**																																**/
/** Return value:							- Std_ReturnType																	**/
/** 											E_OK: The received frame is valid and copied into the socket					**/
/** 											E_NOT_OK: The received frame is not valid for further processing				**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameOtherStateSeqValid ( VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                    P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) 	RxFrame_cpst )
{
	/* Declare local variables */
	P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC ) 		lTcpDynSockTbl_pst;
	VAR( Std_ReturnType, AUTOMATIC ) 									lFunctionRetVal_en;

	/* Initialize the return value of the function to E_NOT_OK */
	lFunctionRetVal_en = E_NOT_OK;

	/* Get Tcp dynamic table entry from Tcp socket index */
	lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* ----------------------------- */
    /* RST bit set                   */
    /* ----------------------------- */
    if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
    {
        /* If the reset contains data and we are in ESTABLISHED, FIN_WAIT1 or FIN_WAIT2 state */
        /* (states where it is possible to receive data) */
        if( (RxFrame_cpst->DataLen_u16 > 0U)									&&
            ((lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_ESTABLISHED_E) 	||
            (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_FIN_WAIT_1_E)		||
            (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_FIN_WAIT_2_E)) )
        {
            /* The frame is valid (we received a [RST] with some data - see RFC1122 p88) */
            /* Copy the received header in the Tcp dynamic table entry */
            lTcpDynSockTbl_pst->RcvdSeqNum_u32 	 	= RxFrame_cpst->Header_st.SeqNum_u32;
            lTcpDynSockTbl_pst->RcvdAckNum_u32 	 	= RxFrame_cpst->Header_st.AckNum_u32;
            lTcpDynSockTbl_pst->RcvdHdrFlag_u8 		= RxFrame_cpst->Header_st.HdrFlag_u8;
            lTcpDynSockTbl_pst->RcvdDataLen_u16		= RxFrame_cpst->DataLen_u16;
            lTcpDynSockTbl_pst->RcvdDataOffset_u16	= RxFrame_cpst->DataOffset_u16;

            /* Set the return value of the function to E_OK */
            /* (segment is accepted) */
            lFunctionRetVal_en = E_OK;
        }

        /* If we are in TIME_WAIT state */
        else if( lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_TIME_WAIT_E )
        {
            /* Drop the segment */
            /* (RFC1337 : Ignore RST segments in TIME-WAIT state) */
        }

        /* If we are in other case */
        else
        {
            /* Reset the socket (see RFC793 p70)*/
            rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );

            /* Drop the segment */
        }
    }

    /* ----------------------------- */
    /* SYN bit set (with no RST bit) */
    /* ----------------------------- */
    else if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_SYN_MSK) == RBA_ETHTCP_SYN_MSK )
    {
        /* If we are in SYN_RCVD and the previous state is LISTEN, TIME_WAIT or LAST_ACK */
        /* (the connection has been initiated with a passive open) */
        if ( (lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_SYN_RCVD_E) 		    &&
             ((lTcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_LISTEN_E) 	    ||
              (lTcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_TIME_WAIT_E)	    ||
              (lTcpDynSockTbl_pst->PrevState_en == RBA_ETHTCP_CONN_LAST_ACK_E)) )
        {
            /* Reset the socket (see RFC1122 p94) */
            rba_EthTcp_ResetSock( TcpDynSockTblIdx_uo, TCPIP_TCP_RESET );

            /* Drop the segment */
        }

        /* In other cases */
        else
        {
            /* If the received frame has the ACK bit set */
            if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
            {
                /* Send a RST frame */
                /* (As there is an ACK bit in the received frame, send RST - see RFC793 p36/37) */

                /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
                /* (seq number of the RST frame will be same as the received ack number) */
                rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, RxFrame_cpst->Header_st.AckNum_u32 );
                rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, 0U );

                /* Send a RST in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_E );

                /* Drop the segment */
            }
            else
            {
                /* Send a RST ACK frame */
                /* (As there is no ACK bit in the received frame, send RST ACK - see RFC793 p36/37) */

                /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
                /* (seq number of the RST-ACK frame will be 0, ack number will be (Received SeqNum + Segment length)) */
                rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, 0U );
                rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, (RxFrame_cpst->Header_st.SeqNum_u32 + ((uint32)RxFrame_cpst->PayloadLen_u16)) );

                /* Send a RST ACK in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

                /* Drop the segment */
            }
        }
    }

    /* ---------------------------------------- */
    /* ACK bit set (with no RST and no SYN bit) */
    /* ---------------------------------------- */
    else if ( (RxFrame_cpst->Header_st.HdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
    {
        /* Execute processing when incoming segment has an ACK */
        lFunctionRetVal_en = rba_EthTcp_FrameOtherStateSeqValidAckPresent( TcpDynSockTblIdx_uo, RxFrame_cpst );
    }

    /* ----------------------------- */
    /* No RST, no SYN and no ACK bit */
    /* ----------------------------- */
    else
    {
        /* Drop the segment */
    }

	return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameOtherStateSeqValidAckPresent() - This function check the received frame when the connection state is        **/
/**                                         SYN RECEIVED, ESTABLISHED, FIN WAIT 1, FIN WAIT 2, CLOSE WAIT, CLOSING, LAST ACK    **/
/**                                         or TIME WAIT, when the sequence number is valid and when acknowledgment number is   **/
/**                                         present                                                                             **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpDynSockTblIdx_uo                     - Tcp dynamic socket table index                                                    **/
/** RxFrame_cpst                            - Pointer to the content of the received Tcp frame                                  **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           - Std_ReturnType                                                                    **/
/**                                             E_OK: The received frame is valid and copied into the socket                    **/
/**                                             E_NOT_OK: The received frame is not valid for further processing                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameOtherStateSeqValidAckPresent (   VAR( TcpIp_SocketIdType, AUTOMATIC )                    TcpDynSockTblIdx_uo,
                                                                                                P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC )   RxFrame_cpst )
{
    /* Declare local variables */
    P2VAR( rba_EthTcp_DynSockTblType_tst, AUTOMATIC, AUTOMATIC )        lTcpDynSockTbl_pst;
    VAR( rba_EthTcp_AckVal_ten, AUTOMATIC )                             lValidRcvdAckNum_en;
    VAR( Std_ReturnType, AUTOMATIC )                                    lFunctionRetVal_en;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get Tcp dynamic table entry from Tcp socket index */
    lTcpDynSockTbl_pst = ( & ( rba_EthTcp_DynSockTbl_ast[TcpDynSockTblIdx_uo] ) );

    /* Check acknowledgment number validity */
    lValidRcvdAckNum_en = rba_EthTcp_RcvdAckNumValidity( TcpDynSockTblIdx_uo, RxFrame_cpst->Header_st.AckNum_u32 );

    /* ----------------------------- */
    /* Acceptable ACK                */
    /* ----------------------------- */

    /* In SYN_RCVD, Ack number is acceptable if it is new (SND.UNA < SEG.ACK =< SND.NXT) */
    /* In other states, Ack number is acceptable if is duplicate or new (SEG.ACK =< SND.NXT) */
    if ( ((lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_SYN_RCVD_E) && (lValidRcvdAckNum_en == RBA_ETHTCP_ACK_NEW_E))                                                            ||
         ((lTcpDynSockTbl_pst->State_en != RBA_ETHTCP_CONN_SYN_RCVD_E) && ((lValidRcvdAckNum_en == RBA_ETHTCP_ACK_DUPLICATE_E) || (lValidRcvdAckNum_en == RBA_ETHTCP_ACK_NEW_E))))
    {
        /* The frame is valid (we received an [ACK] or [FIN, ACK]) */
        /* Copy the received header in the Tcp dynamic table entry */
        lTcpDynSockTbl_pst->RcvdSeqNum_u32      = RxFrame_cpst->Header_st.SeqNum_u32;
        lTcpDynSockTbl_pst->RcvdAckNum_u32      = RxFrame_cpst->Header_st.AckNum_u32;
        lTcpDynSockTbl_pst->RcvdHdrFlag_u8      = RxFrame_cpst->Header_st.HdrFlag_u8;
        lTcpDynSockTbl_pst->RcvdDataLen_u16     = RxFrame_cpst->DataLen_u16;
        lTcpDynSockTbl_pst->RcvdDataOffset_u16  = RxFrame_cpst->DataOffset_u16;

        /* Rcvd Wnd Update - see RFC1122 p94 */
        rba_EthTcp_SetRcvdWnd(  TcpDynSockTblIdx_uo,
                                RxFrame_cpst->Header_st.SeqNum_u32,
                                RxFrame_cpst->Header_st.AckNum_u32,
                                RxFrame_cpst->Header_st.WndSize_u16 );

        /* Set the return value of the function to E_OK */
        /* (segment is accepted) */
        lFunctionRetVal_en = E_OK;
    }

    /* ----------------------------- */
    /* Unacceptable ACK              */
    /* ----------------------------- */

    /* In SYN_RCVD, Ack number is unacceptable if it is duplicate or invalid (SEG.ACK <= SND.UNA or SEG.ACK > SND.NXT) */
    /* In other states, Ack number is unacceptable if is invalid (SEG.ACK > SND.NXT) */
    else
    {
        /* Acknowledgment number unacceptable in SYN_RCVD state */
        if ( lTcpDynSockTbl_pst->State_en == RBA_ETHTCP_CONN_SYN_RCVD_E )
        {
            /* Send a RST frame */
            /* (As there is an ACK bit in the received frame, send RST - see RFC793 p36/37) */

            /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
            /* (seq number of the RST frame will be same as the received ack number) */
            rba_EthTcp_SetSeqNum( TcpDynSockTblIdx_uo, RxFrame_cpst->Header_st.AckNum_u32 );
            rba_EthTcp_SetAckNum( TcpDynSockTblIdx_uo, 0U );

            /* Send a RST in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_RST_E );

            /* Drop the segment */
        }

        /* Acknowledgment number invalid in other states */
        else
        {
            /* Send an ACK in the next MainFunction */
            (void)rba_EthTcp_SetNextSendFrame( TcpDynSockTblIdx_uo, RBA_ETHTCP_SEND_ACK_E );

            /* Drop the segment */
        }
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** rba_EthTcp_FrameNoConn()		- This function check the received frame when there is no connection at all					**/
/**																																**/
/** Parameters (in):																											**/
/** RxFrame_pcst 					- Pointer to the content of the received Tcp frame											**/
/**																																**/
/** Parameters (inout):		        None																						**/
/**																																**/
/** Parameters (out):				None																						**/
/**																																**/
/** Return value:					- Std_ReturnType																			**/
/** 									E_OK: The received frame is valid and copied into the socket							**/
/** 									E_NOT_OK: The received frame is not valid for further processing						**/
/**																																**/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) rba_EthTcp_FrameNoConn ( P2CONST( rba_EthTcp_Frame_tst, AUTOMATIC, AUTOMATIC ) RxFrame_pcst )
{
	/* Declare local variables */
	VAR( TcpIp_SocketIdType, AUTOMATIC ) 								lNewSockTblIdx_uo;
	VAR( rba_EthTcp_NewSockInfo_tst, AUTOMATIC )						lNewSockInfo_st;
	VAR( Std_ReturnType, AUTOMATIC )									lRetVal_en;
	VAR( uint8,  AUTOMATIC )                                            lFramePrio_u8;

	/* ----------------------------- */
	/* Fetch frame priority			 */
	/* ----------------------------- */

	/* Get the frame priority from local address id */
	lRetVal_en = TcpIp_GetFramePrioFrmLocalAddrId( RxFrame_pcst->LocalAddrId_u8, &lFramePrio_u8 );

	/* Frame priority has been successfully get */
	if ( lRetVal_en == E_OK )
	{
		/* Build a new socket info variable */
		lNewSockInfo_st.LocalAddrId_u8		= RxFrame_pcst->LocalAddrId_u8;
		lNewSockInfo_st.LocalPort_u16		= RxFrame_pcst->LocalPort_u16;
		lNewSockInfo_st.RemotePort_u16		= RxFrame_pcst->RemotePort_u16;
		lNewSockInfo_st.DomainType_u32		= RxFrame_pcst->DomainType_u32;
		lNewSockInfo_st.RemoteIPAddr_un	    = RxFrame_pcst->RemoteIPAddr_un;
		lNewSockInfo_st.FramePrio_u8		= lFramePrio_u8;

        /* ----------------------------- */
        /* RST bit set                   */
        /* ----------------------------- */
	    if ( (RxFrame_pcst->Header_st.HdrFlag_u8 & RBA_ETHTCP_RST_MSK) == RBA_ETHTCP_RST_MSK )
        {
            /* Drop the segment */
        }

        /* ----------------------------- */
        /* ACK bit set (with no RST bit) */
        /* ----------------------------- */
        else if ( (RxFrame_pcst->Header_st.HdrFlag_u8 & RBA_ETHTCP_ACK_MSK) == RBA_ETHTCP_ACK_MSK )
        {
            /* Get a new TcpIp and Tcp socket for the sending of a reset */
            lRetVal_en = rba_EthTcp_GetNewSock ( &lNewSockInfo_st,
                                                 &lNewSockTblIdx_uo );

            if ( lRetVal_en == E_OK )
            {
                /* Send a RST frame */
                /* (As there is an ACK bit in the received frame, send RST - see RFC793 p36/37) */

                /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
                /* (seq number of the RST frame will be same as the received ack number) */
                rba_EthTcp_SetSeqNum( lNewSockTblIdx_uo, RxFrame_pcst->Header_st.AckNum_u32 );
                rba_EthTcp_SetAckNum( lNewSockTblIdx_uo, 0U );

                /* Send a RST in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( lNewSockTblIdx_uo, RBA_ETHTCP_SEND_RST_E );

                /* Drop the segment */
            }
        }

        /* ----------------------------- */
        /* No RST and no ACK bit 	 	 */
        /* ----------------------------- */
        else
        {
            /* Get a new TcpIp and Tcp socket for the sending of a reset */
            lRetVal_en = rba_EthTcp_GetNewSock ( &lNewSockInfo_st,
                                                 &lNewSockTblIdx_uo );

            if ( lRetVal_en == E_OK )
            {
                /* Send a RST ACK frame */
                /* (As there is no ACK bit in the received frame, send RST ACK - see RFC793 p36/37) */

                /* Set sequence number and acknowledgment number of the reset segment as per RFC793 */
                /* (seq number of the RST-ACK frame will be 0, ack number will be (Received SeqNum + Segment length)) */
                rba_EthTcp_SetSeqNum( lNewSockTblIdx_uo, 0U );
                rba_EthTcp_SetAckNum( lNewSockTblIdx_uo, (RxFrame_pcst->Header_st.SeqNum_u32 + ((uint32)RxFrame_pcst->PayloadLen_u16)) );

                /* Send a RST ACK in the next MainFunction */
                (void)rba_EthTcp_SetNextSendFrame( lNewSockTblIdx_uo, RBA_ETHTCP_SEND_RST_ACK_E );

                /* Drop the segment */
            }
        }
	}

    /* Drop the segment */
    return E_NOT_OK;
}


#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */















