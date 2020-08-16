

#ifndef RBA_ETHTCP_PRV_H
#define RBA_ETHTCP_PRV_H

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "rba_EthTcp_Prv_Domain.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/* Value for unused sockets */
#define 	RBA_ETHTCP_TCPSOCK_UNUSED			    0xFFFFU

/* Masks for the Tcp header */
#define 	RBA_ETHTCP_FIN_MSK 						0x01U
#define 	RBA_ETHTCP_SYN_MSK 						0x02U
#define 	RBA_ETHTCP_RST_MSK		 				0x04U
#define 	RBA_ETHTCP_PSH_MSK 						0x08U
#define 	RBA_ETHTCP_ACK_MSK 						0x10U
#define 	RBA_ETHTCP_URG_MSK 						0x20U
#define 	RBA_ETHTCP_SYN_ACK_MSK 					0x12U
#define		RBA_ETHTCP_PSH_ACK_MSK					0x18U
#define		RBA_ETHTCP_FIN_ACK_MSK					0x11U
#define		RBA_ETHTCP_RST_ACK_MSK					0x14U

/* Default Tcp header length (in bytes) */
#define 	RBA_ETHTCP_DFL_HDRLENGTH				20U

/* Kind of the Tcp options */
#define     RBA_ETHTCP_OPT_KIND_EOP          		0U
#define     RBA_ETHTCP_OPT_KIND_NOP          		1U
#define     RBA_ETHTCP_OPT_KIND_MSS          		2U
#define     RBA_ETHTCP_OPT_KIND_WSF          		3U
#define     RBA_ETHTCP_OPT_KIND_SACK_PERM         	4U
#define     RBA_ETHTCP_OPT_KIND_TIMESTAMP         	8U
#define     RBA_ETHTCP_OPT_KIND_UTO         		28U

/* Length of the Tcp options (in bytes) */
#define     RBA_ETHTCP_OPT_LENGTH_MSS          		4U
#define     RBA_ETHTCP_OPT_LENGTH_UTO              	4U


/*
 ***************************************************************************************************
 * Global variables
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_VAR_INIT_8
#include "rba_EthTcp_MemMap.h"
/* Flag to indicate if Tcp_Init has been executed or not since power ON */
extern VAR( boolean, RBA_ETHTCP_CODE )								rba_EthTcp_InitFlag_b;
#define RBA_ETHTCP_STOP_SEC_VAR_INIT_8
#include "rba_EthTcp_MemMap.h"

#define RBA_ETHTCP_START_SEC_VAR_INIT_16
#include "rba_EthTcp_MemMap.h"
/* TCP port range*/
extern VAR( uint16, RBA_ETHTCP_CODE )                               rba_EthTcp_PortAny_u16;
#define RBA_ETHTCP_STOP_SEC_VAR_INIT_16
#include "rba_EthTcp_MemMap.h"

#define RBA_ETHTCP_START_SEC_VAR_CLEARED_16
#include "rba_EthTcp_MemMap.h"
/* Total number of opened Tcp sockets */
extern VAR( uint16, RBA_ETHTCP_CODE )								rba_EthTcp_SockConnCntr_u16;
#define RBA_ETHTCP_STOP_SEC_VAR_CLEARED_16
#include "rba_EthTcp_MemMap.h"

#define RBA_ETHTCP_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"
/* Pointer to the currently used Tcp configuration */
extern P2CONST( rba_EthTcp_Config_to, AUTOMATIC, AUTOMATIC )		rba_EthTcp_CurrConfig_cpo;
#define RBA_ETHTCP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"

#if ( RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED == STD_ON || RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
#define RBA_ETHTCP_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"
/* Context used for the generation of the Initial Sequence Number */
extern VAR( rba_EthTcp_IsnGeneratorContext_tst, RBA_ETHTCP_CODE )   rba_EthTcp_IsnContext_st;
#define RBA_ETHTCP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthTcp_MemMap.h"
#endif


/*
 ***************************************************************************************************
 * Prototypes
 ***************************************************************************************************
 */

#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

/* CheckFrameAndCopyToSocket */

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE )	rba_EthTcp_CheckFrameAndCopyToSocket	( VAR( TcpIp_LocalAddrIdType, AUTOMATIC )	LocalAddrId_u8,
                                                                                          P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC ) PseudoHdr_cpst,
																						  P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 		RxData_pu8,
																						  VAR( uint16, AUTOMATIC ) 					LenByte_u16,
																						  P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC ) TcpDynSockTblIdx_puo );

/* ConnectionState */

extern FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_SetConnectionState           ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
                                                                                          VAR( rba_EthTcp_ConnState_ten, AUTOMATIC ) NewConnState_en );

/* CopyHdrToFrame */

extern FUNC( void, RBA_ETHTCP_CODE ) 	        rba_EthTcp_SetHdrToFrame			    ( VAR( TcpIp_SocketIdType, AUTOMATIC )    	TcpDynSockTblIdx_uo,
																				  	  	  P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 		TxEthDrvBuf_pu8 );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetOptionLength				( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo );

extern FUNC( void, RBA_ETHTCP_CODE ) 	        rba_EthTcp_SetOptionToFrame				( VAR( TcpIp_SocketIdType, AUTOMATIC )		TcpDynSockTblIdx_uo,
																				  	  	  P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 		TxEthDrvBuf_pu8 );

#if ( RBA_ETHTCP_SW_CHKSUM_TX == STD_ON )
extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_SetChecksumToFrame			( VAR( TcpIp_SocketIdType, AUTOMATIC )	    TcpDynSockTblIdx_uo,
																				  	  	  P2VAR( uint8, AUTOMATIC, AUTOMATIC ) 		TxEthDrvBuf_pu8,
																				  	  	  VAR( uint16, 	AUTOMATIC )					TotalLength_u16 );
#endif

/* CopyPayloadToFrame */

#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
extern FUNC( void, RBA_ETHTCP_CODE ) 	        rba_EthTcp_SetPayloadToFrame			( VAR( TcpIp_SocketIdType, AUTOMATIC )		TcpDynSockTblIdx_uo,
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )      TxEthDrvBuf_pu8,
																				  	  	  VAR( uint16, AUTOMATIC ) 					PayloadLength_u16 );
#endif

/* ExtractHdrFromFrame */

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetHdrFromFrame				( P2CONST( uint8, AUTOMATIC, AUTOMATIC )    RxData_cpu8,
																						  P2VAR( rba_EthTcp_HeaderFields_tst, AUTOMATIC, AUTOMATIC ) RcvdHdrFields_pst );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetOptionFromFrame			( P2CONST( uint8, AUTOMATIC, AUTOMATIC )    RxData_cpu8,
																						  P2VAR( rba_EthTcp_OptionFields_tst, AUTOMATIC, AUTOMATIC )  RcvdOptionFields_pst );

extern FUNC( rba_EthTcp_SeqVal_ten, RBA_ETHTCP_CODE ) rba_EthTcp_RcvdSeqNumValidity		( VAR( TcpIp_SocketIdType, AUTOMATIC )	    TcpDynSockTblIdx_uo,
																	 	 	 			  VAR( uint32, AUTOMATIC )					RcvdSeqNum_u32,
																	 	 	 			  VAR( uint16, AUTOMATIC ) 					PayloadLenByte_u16 );

extern FUNC( rba_EthTcp_AckVal_ten, RBA_ETHTCP_CODE ) rba_EthTcp_RcvdAckNumValidity	    ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
																					  	  VAR( uint32, AUTOMATIC )        			RcvdAckNum_u32 );

#if (( RBA_ETHTCP_SW_CHKSUM_RX == STD_ON ) || ( RBA_ETHTCP_REASSMBLY_RX_ENABLED == STD_ON ))
extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_RcvdChecksumValidity			( P2CONST( TcpIp_PseudoHdr_tst, AUTOMATIC, AUTOMATIC )    PseudoHdr_cpst,
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )      RxData_pu8,
                                                                                          VAR( uint16, AUTOMATIC )                  LenByte_u16 );
#endif

/* ExtractPayloadFromFrame */

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetPayloadLenFromFrame		( P2CONST( uint8, AUTOMATIC, AUTOMATIC )	RxData_cpu8,
																				  	  	  VAR( uint16, AUTOMATIC ) 					LenByte_u16 );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetRepeatedPayloadLen		( VAR( TcpIp_SocketIdType, AUTOMATIC )	    TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint32, AUTOMATIC )					RcvdSeqNum_u32 );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetOutOfWindowPayloadLen		( VAR( TcpIp_SocketIdType, AUTOMATIC )	    TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint32, AUTOMATIC )					RcvdSeqNum_u32,
																				  	  	  VAR( uint16, AUTOMATIC ) 					PayloadLenByte_u16 );

/* IsnGenerator */

#if ( RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED == STD_ON || RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
extern FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_InitIsnGenerator             ( void );

extern FUNC( void, RBA_ETHTCP_CODE )            rba_EthTcp_IncrIsnGenerator             ( void );
#endif

extern FUNC( uint32, RBA_ETHTCP_CODE )          rba_EthTcp_GenerateIsn                  ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo );

/* RxData */

FUNC( void, RBA_ETHTCP_CODE ) 					rba_EthTcp_RxData						( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
                                                    									  P2VAR( uint8, AUTOMATIC, AUTOMATIC )    	DataPtr_pu8,
                                                    									  VAR( uint16, AUTOMATIC )	            	DataLen_u16 );

/* RxDataAcknowledgment */

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_RxDataAcknowledgment	        ( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint16, AUTOMATIC )					ConfirmedLen_u16 );

/* SndData */

#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SndData						( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo);
#endif

/* SndFlag */

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SndFlag						( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo);

/* SocketTable */

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE )  rba_EthTcp_GetNewSock                   ( P2CONST( rba_EthTcp_NewSockInfo_tst, AUTOMATIC, AUTOMATIC )	NewSockInfo_cpst,
                                                                                          P2VAR( TcpIp_SocketIdType, AUTOMATIC, AUTOMATIC ) 			TcpDynSockTblIdx_puo );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_ReopenSock 					( VAR( TcpIp_SocketIdType, AUTOMATIC ) TcpDynSockTblIdx_uo );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_LinkToListeningSock			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_ResetSock					( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpDynSockTblIdx_uo,
																						  VAR( TcpIp_EventType, AUTOMATIC ) 		CloseType_en );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_ResetTcpTableEntry			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SetState						( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
																				  	  	  VAR( rba_EthTcp_ConnState_ten, AUTOMATIC )TcpState_en );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SetSeqNum					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint32, AUTOMATIC ) 					SeqNum_u32 );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SetAckNum					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint32, AUTOMATIC ) 					AckNum_u32 );

extern FUNC( Std_ReturnType, RBA_ETHTCP_CODE ) 	rba_EthTcp_SetNextSendFrame				( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																				  	  	  VAR( rba_EthTcp_Flag_ten, AUTOMATIC )		TcpFlag_en );

extern FUNC( void, RBA_ETHTCP_CODE) 			rba_EthTcp_SetRcvdWnd					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint32, AUTOMATIC ) 					SeqNum_u32,
																				  	  	  VAR( uint32, AUTOMATIC ) 					AckNum_u32,
																				  	  	  VAR( uint16, AUTOMATIC )					WinSize_u16	);

/* Tmr */

extern FUNC( void, RBA_ETHTCP_CODE )  			rba_EthTcp_StartTimer					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
																			  	  	  	  VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en );

extern FUNC( void, RBA_ETHTCP_CODE )  			rba_EthTcp_RestartTimer					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
																			  	  	  	  VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en );

extern FUNC( void, RBA_ETHTCP_CODE )  			rba_EthTcp_StopTimer					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																			  	  	  	  VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC ) 	TmrSt_en );

extern FUNC( void, RBA_ETHTCP_CODE )  			rba_EthTcp_ExpireTimer					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
																			  	  	  	  VAR( rba_EthTcp_TmrSt_ten, AUTOMATIC )	TmrSt_en );

extern FUNC( void, RBA_ETHTCP_CODE )  			rba_EthTcp_IncrTimer					( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo );

#if (RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON)
extern FUNC( void , RBA_ETHTCP_CODE ) 			rba_EthTcp_CalculateRto					( VAR ( TcpIp_SocketIdType , AUTOMATIC )    TcpDynSockTblIdx_uo );
#endif

/* TxBuffer */

#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SetTxBufBeforeTx				( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint16, AUTOMATIC ) 					Len_u16 );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SetTxBufBeforeReTx 			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 	    TcpDynSockTblIdx_uo );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SetTxBufAfterTx				( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint16, AUTOMATIC ) 					Len_u16 );

extern FUNC( void, RBA_ETHTCP_CODE ) 			rba_EthTcp_SetTxBufAfterAcked			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo,
																				  	  	  VAR( uint16, AUTOMATIC ) 					Len_u16 );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetTxBufFreeLen				( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetTxBufLnrFreeLen			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetTxBufSndLen				( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetTxBufLnrSndLen			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo );

extern FUNC( uint16, RBA_ETHTCP_CODE ) 			rba_EthTcp_GetTxBufUnackedLen			( VAR( TcpIp_SocketIdType, AUTOMATIC ) 		TcpDynSockTblIdx_uo );
#endif

#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"


/*
 ***************************************************************************************************
 * Macros
 ***************************************************************************************************
 */

/* Macro for reading at given address */

/* Read 32 bits at position */
#define RBA_ETHTCP_READ_32BITS_AT_POS( BaseAddress, BytePos )   						        \
		(uint32)( (uint32)( * ( (BaseAddress) + (BytePos) ) ) << 24U ) 		|			        \
		(uint32)( (uint32)( * ( (BaseAddress) + (BytePos) + 1 ) ) << 16U ) 	|			        \
		(uint32)( (uint32)( * ( (BaseAddress) + (BytePos) + 2 ) ) << 8U ) 	|			        \
		(uint32)( * ( (BaseAddress) + (BytePos) + 3U ) )						    	        \

/* Read 16 bits at position */
#define RBA_ETHTCP_READ_16BITS_AT_POS( BaseAddress, BytePos )   						        \
		(uint16)( (uint16)( * ( (BaseAddress) + (BytePos) ) ) << 8U ) 		|			        \
		(uint16)( * ( (BaseAddress) + (BytePos) + 1U ) )								        \

/* Read 8 bits at position */
#define RBA_ETHTCP_READ_8BITS_AT_POS( BaseAddress, BytePos )   							        \
		(uint8)( * ( (BaseAddress) + (BytePos) ) )										        \

/* Read 1 bit at position */
#define RBA_ETHTCP_READ_BIT_AT_POS( BaseAddress, BytePos, BitPos )   					        \
		( (uint8)( * ( (BaseAddress) + (BytePos) ) ) & ( 0x01U << (BitPos) ) ) >> (BitPos)      \


/* Macro for writing at given address */

/* Write 32 bits at position */
#define RBA_ETHTCP_WRITE_32BITS_AT_POS( BaseAddress, BytePos, Value )   				        \
		( * ( (BaseAddress) + (BytePos) ) ) = ( (uint8)( (Value) >> 24U ) );			        \
		( * ( (BaseAddress) + (BytePos) + 1U ) ) = ( (uint8)( (Value) >> 16U ) );		        \
		( * ( (BaseAddress) + (BytePos) + 2U ) ) = ( (uint8)( (Value) >> 8U ) );		        \
		( * ( (BaseAddress) + (BytePos) + 3U ) ) = ( (uint8)( (Value) ) );				        \

/* Write 16 bits at position */
#define RBA_ETHTCP_WRITE_16BITS_AT_POS( BaseAddress, BytePos, Value )   				        \
		( * ( (BaseAddress) + (BytePos) ) ) = ( (uint8)( (Value) >> 8U ) );				        \
		( * ( (BaseAddress) + (BytePos) + 1U ) ) = ( (uint8)( (Value) ) );				        \

/* Write 8 bits at position */
#define RBA_ETHTCP_WRITE_8BITS_AT_POS( BaseAddress, BytePos, Value )   					        \
		( * ( (BaseAddress) + (BytePos) ) ) = ( (uint8)( (Value) ) );					        \

/* Write 1 bit at position */
#define RBA_ETHTCP_WRITE_BIT_AT_POS( BaseAddress, BytePos, BitPos, Value )   			        \
		( * ( (BaseAddress) + (BytePos) ) ) |= ( (uint8)( ( (Value) & 0x01U ) << (BitPos) ) );  \
		( * ( (BaseAddress) + (BytePos) ) ) &= ( (uint8)( ( (Value) | 0xFEU ) << (BitPos) ) );	\


/* Macros for ISN generation (MD4 hash) */

/* F, G and H functions defined as per RFC1320 p4 */
#define RBA_ETHTCP_MD4_F(X, Y, Z)       (((X) & (Y)) | ((~(X)) & (Z)))
#define RBA_ETHTCP_MD4_G(X, Y, Z)       (((X) & (Y)) | ((X) & (Z)) | ((Y) & (Z)))
#define RBA_ETHTCP_MD4_H(X, Y, Z)       (((X) ^ (Y)) ^ (Z))

/* Rotate function */
#define RBA_ETHTCP_MD4_ROTATE(A, S)     ((uint32)( (A) << (S) ) | (uint32)( (A) >> (32U - (S)) ))

/* MD4 transformation functions for the 3 rounds */
#define RBA_ETHTCP_MD4_STEP_F(A, B, C, D, X, S)                                              	\
        (A) = (A) + RBA_ETHTCP_MD4_F( (B), (C), (D) ) + (X);                                    \
        (A) = RBA_ETHTCP_MD4_ROTATE( (A), (S) );                      							\

#define RBA_ETHTCP_MD4_STEP_G(A, B, C, D, X, S)                                              	\
        (A) = (A) + RBA_ETHTCP_MD4_G( (B), (C), (D) ) + (X);                                    \
        (A) = RBA_ETHTCP_MD4_ROTATE( (A), (S) );                      							\

#define RBA_ETHTCP_MD4_STEP_H(A, B, C, D, X, S)                                              	\
        (A) = (A) + RBA_ETHTCP_MD4_H( (B), (C), (D) ) + (X);                                    \
        (A) = RBA_ETHTCP_MD4_ROTATE( (A), (S) );                      							\


/*
 ***************************************************************************************************
 * DET Defines
 ***************************************************************************************************
 */

/* API IDs for DET Support */

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_Init() */
#define RBA_ETHTCP_E_INIT                         	(0x01U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_MainFunction() */
#define RBA_ETHTCP_E_MAINFUNCTION	             	(0x02U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_SetSocketId() */
#define RBA_ETHTCP_E_GETSOCKET                  	(0x03U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_ChangeParameter() */
#define RBA_ETHTCP_E_CHANGEPARAMETER	           	(0x04U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_Connect() */
#define RBA_ETHTCP_E_CONNECT                       	(0x05U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_Listen() */
#define RBA_ETHTCP_E_LISTEN           				(0x06U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_Transmit() */
#define RBA_ETHTCP_E_TRANSMIT						(0x07U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_RxIndication() */
#define RBA_ETHTCP_E_RXINDICATION					(0x08U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_Received() */
#define RBA_ETHTCP_E_RECEIVED			         	(0x09U)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_Close() */
#define RBA_ETHTCP_E_CLOSE	                      	(0x0AU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_Bind()  */
#define RBA_ETHTCP_E_BIND                           (0x0BU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_FindTcpSockId()  */
#define RBA_ETHTCP_FINDTCPSOCKID                    (0x0CU)

/* Indicates that Api Id passed in the call of Det_ReportError corresponds to rba_EthTcp_AbortByLocalAddrId()  */
#define RBA_ETHTCP_ABORTBYLOCALADDRID               (0x0DU)

/* Development Error Codes for DET Support */

/* API service used without rba_EthTcp_Init module initialization */
#define RBA_ETHTCP_E_NOTINIT                        TCPIP_E_NOTINIT

/* Invalid argument received */
#define RBA_ETHTCP_E_INV_ARG                        TCPIP_E_INV_ARG

/* API service called with NULL pointer as an argument */
#define RBA_ETHTCP_E_NULL_PTR		                TCPIP_E_NULL_PTR

/* Invalid Destination IP address */
#define RBA_ETHTCP_E_INV_SOCKADDR                  	TCPIP_E_INV_SOCKADDR

/* Address already in use */
#define RBA_ETHTCP_E_ADDRINUSE                      TCPIP_E_ADDRINUSE

/* Can't assign requested address */
#define RBA_ETHTCP_E_ADDRNOTAVAIL                   TCPIP_E_ADDRNOTAVAIL


/*
 ***************************************************************************************************
 * DET Check
 ***************************************************************************************************
 */
#define RBA_ETHTCP_START_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#if( TCPIP_DEV_ERROR_DETECT == STD_ON )
/* Prototype : Inline function to check DET error */
LOCAL_INLINE FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_CheckDetError (   VAR( boolean, AUTOMATIC )                  Condition_b,
                                                                        VAR( uint8, AUTOMATIC )                    ApiId_u8,
                                                                        VAR( uint8, AUTOMATIC )                    ErrorId_u8,
                                                                        P2VAR( boolean, AUTOMATIC, AUTOMATIC )     ErrorFlag_pb );

/* Definition : Inline function to check DET error */
LOCAL_INLINE FUNC( void, RBA_ETHTCP_CODE ) rba_EthTcp_CheckDetError (   VAR( boolean, AUTOMATIC )                  Condition_b,
                                                                        VAR( uint8, AUTOMATIC )                    ApiId_u8,
                                                                        VAR( uint8, AUTOMATIC )                    ErrorId_u8,
                                                                        P2VAR( boolean, AUTOMATIC, AUTOMATIC )     ErrorFlag_pb )
{
    /* Check the condition */
    if( Condition_b != FALSE )
    {
        /* Report the DET error */
        (void)Det_ReportError( RBA_ETHTCP_MODULE_ID, RBA_ETHTCP_INSTANCE_ID, ApiId_u8, ErrorId_u8 );

        /* Set the error flag to TRUE in out argument of the function */
        (*ErrorFlag_pb) = TRUE;
    }

    return;
}
#endif

#define RBA_ETHTCP_STOP_SEC_CODE
#include "rba_EthTcp_MemMap.h"

#endif /* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */
#endif /* #ifndef RBA_ETHTCP_PRIV_H */












