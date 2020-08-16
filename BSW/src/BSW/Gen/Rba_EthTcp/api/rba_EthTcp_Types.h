

#ifndef RBA_ETHTCP_TYPES_H
#define RBA_ETHTCP_TYPES_H

#if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) )


/*
 ***************************************************************************************************
 * Type Definitions
 ***************************************************************************************************
 */

/* -------------------------------------------- */
/* Enumerations 								*/
/* -------------------------------------------- */

/* Enumeration of the Tcp states */
typedef enum
{
	RBA_ETHTCP_CONN_CLOSED_E      		= 0U,   /* No connection at all */
	RBA_ETHTCP_CONN_LISTEN_E      		= 1U,   /* Wait for a Connection Request from any remote TCP*/
	RBA_ETHTCP_CONN_SYN_SENT_E    		= 2U, 	/* Wait for a SYN-ACK after having sent a connection request.*/
	RBA_ETHTCP_CONN_SYN_RCVD_E    		= 3U,	/* Wait for a Connection Request ACK after having both received and sent a connection request.*/
	RBA_ETHTCP_CONN_ESTABLISHED_E 		= 4U,	/* Data can transmitted and received only in this state */
	RBA_ETHTCP_CONN_FIN_WAIT_1_E  		= 5U,	/* FIN frame has been sent, waiting for an ACK or Connection Termination Request from the Remote TCP */
	RBA_ETHTCP_CONN_FIN_WAIT_2_E  		= 6U,	/* Wait for Connection Termination Request from the Remote TCP */
	RBA_ETHTCP_CONN_CLOSE_WAIT_E 		= 7U,   /* Server TCP is waiting for Application to Close*/
	RBA_ETHTCP_CONN_CLOSING_E     		= 8U,   /* Wait for a connection termination request acknowledgment from the remote TCP */
	RBA_ETHTCP_CONN_LAST_ACK_E    		= 9U,   /* Wait for Connection Termination request Ack from Client TCP  */
	RBA_ETHTCP_CONN_TIME_WAIT_E   		= 10U	/* Time to wait before closing TCP Connection */
}rba_EthTcp_ConnState_ten;

/* Enumeration of the Socket state   */
typedef enum
{
    RBA_ETHTCP_SOCK_CLOSED_E            = 0U,  /* Socket is Closed i.e. socket is not in use */
    RBA_ETHTCP_SOCK_RESERVED_E          = 1U,  /* Socket is reserved by Tcp to send an immediate frame in reply */
    RBA_ETHTCP_SOCK_ALLOCATED_E         = 2U,  /* Socket is allocated i.e. socket is reserved for use */
    RBA_ETHTCP_SOCK_BOUND_E             = 3U,  /* Socket is bound i.e. when local address is assigned to socket */
    RBA_ETHTCP_SOCK_OPENED_E            = 4U   /* Socket is opened for communication i.e. when Listen and Connect functions is called */
}rba_EthTcp_SocketState_ten;


/* Enumeration of the Tcp flags */
/* (the values of the enum correspond to the priorities for Tcp flag overwriting) */
typedef enum
{
	RBA_ETHTCP_NOTHING_E         		= 0U,   /* Do Nothing in the next main function */
	RBA_ETHTCP_SEND_RST_E				= 1U,	/* (Priority 1) Send a RST frame in the next main function */
	RBA_ETHTCP_SEND_RST_ACK_E			= 2U,	/* (Priority 2) Send a RST ACK frame in the next main function */
	RBA_ETHTCP_SEND_ACK_FOR_FIN_ACK_E  	= 3U,   /* (Priority 3) Send an ACK for the received FIN ACK in the next main function */
	RBA_ETHTCP_SEND_FIN_ACK_E      		= 4U,   /* (Priority 4) Send a FIN ACK in the next main function */
	RBA_ETHTCP_SEND_ACK_FOR_SYN_ACK_E   = 5U,   /* (Priority 5) Send ACK for the received SYN ACK in the next main function */
	RBA_ETHTCP_SEND_SYN_ACK_E  			= 6U,   /* (Priority 6) Send a SYN ACK for the received SYN in the next main function */
	RBA_ETHTCP_SEND_SYN_E      			= 7U,   /* (Priority 7) Send a SYN in the next main function */
	RBA_ETHTCP_SEND_ZWP_E				= 8U,   /* (Priority 8) Send a Zero Window Probe in the next main function */
	RBA_ETHTCP_SEND_DATA_E     			= 9U,   /* (Priority 9) Send data in the next main function */
	RBA_ETHTCP_SEND_ACK_E 				= 10U,  /* (Priority 10) Send ACK for the data in the next main function */
	RBA_ETHTCP_SEND_KEEP_ALIVE_E		= 11U   /* (Priority 11) Send a Keep Alive in the next main function */
}rba_EthTcp_Flag_ten;

/* TCP header positions */
typedef enum
{
	RBA_ETHTCP_POS_SRCPORT_E			= 0U,	/* Position of source port in TCP header */
	RBA_ETHTCP_POS_DESTPORT_E			= 2U,	/* Position of destination port in TCP header */
	RBA_ETHTCP_POS_SEQNUM_E				= 4U,	/* Position of sequence number in TCP header */
	RBA_ETHTCP_POS_ACKNUM_E				= 8U,	/* Position of acknowledge number in TCP header */
	RBA_ETHTCP_POS_OFFSET_E				= 12U,	/* Position of offset in TCP header */
	RBA_ETHTCP_POS_FLAGS_E				= 13U,	/* Position of header flags like SYN, ACK, URG, FIN, RST in TCP header */
	RBA_ETHTCP_POS_WNDSIZE_E			= 14U,	/* Position of window size in TCP header */
	RBA_ETHTCP_POS_CHKSUM_E				= 16U,	/* Position of checksum in TCP header */
	RBA_ETHTCP_POS_URGPTR_E				= 18U	/* Position of urgent pointer in TCP header */
}rba_EthTcp_HdrPos_ten;

/* Tcp option positions */
typedef enum
{
    RBA_ETHTCP_POS_OPT_KIND_E        	= 0U,	/* Position of Kind field in TCP option */
    RBA_ETHTCP_POS_OPT_LEN_E           	= 1U,	/* Position of Length field in TCP option */
    RBA_ETHTCP_POS_OPT_VAL_E          	= 2U	/* Position of Value in TCP option */
}rba_EthTcp_HdrOpt_ten;

/* Enumeration of the Tcp timers */
typedef enum
{
    RBA_ETHTCP_TMR_STOPPED_E    		= 0U,   /* No timer running */
	RBA_ETHTCP_TMR_SYNSENT_E			= 1U,	/* Timer running in SYN SENT state */
	RBA_ETHTCP_TMR_SYNRCVD_E			= 2U,	/* Timer running in SYN RCVD state */
	RBA_ETHTCP_TMR_RETX_E				= 3U,	/* Retransmission timer */
	RBA_ETHTCP_TMR_ZWP_E	            = 4U,   /* Zero Window Probe timer  */
	RBA_ETHTCP_TMR_FINWAIT1_CLOSING_E  	= 5U,   /* Timer running in FIN WAIT 1 or CLOSING state  */
	RBA_ETHTCP_TMR_FINWAIT2_E			= 6U,	/* Timer running in FIN WAIT 2 state */
    RBA_ETHTCP_TMR_LASTACK_E            = 7U,   /* Timer running in LAST ACK state */
	RBA_ETHTCP_TMR_TIMEWAIT_E           = 8U,   /* Timer running in TIME WAIT state */
	RBA_ETHTCP_TMR_KEEPALIVE_E          = 9U,	/* Keep Alive timer */
	RBA_ETHTCP_TMR_DLYACK_E          	= 10U,  /* Delayed Ack timer */
	RBA_ETHTCP_TMR_UTO_E          		= 11U   /* User Timeout timer */
}rba_EthTcp_TmrSt_ten;

/* Socket type */
typedef enum
{
    RBA_ETHTCP_SOC_UNSPECIFIED_REMOTE_E	= 0U,	/* Socket with unspecified remote IP and Port (ANY) */
    RBA_ETHTCP_SOC_SPECIFIED_REMOTE_E 	= 1U,	/* Socket with specified remote IP and Port */
    RBA_ETHTCP_SOC_NONE_E       		= 2U	/* No socket */
}rba_EthTcp_SocketType_ten;

/* Type of sequence number validity */
typedef enum
{
    RBA_ETHTCP_SEQ_VALID_E              = 0U,	/* Received sequence number is valid */
    RBA_ETHTCP_SEQ_SPECIAL_ALLOWANCE_E  = 1U,	/* Received sequence number is valid (special allowance) */
    RBA_ETHTCP_SEQ_OUT_OF_ORDER_E       = 2U,	/* Received sequence number is out of order */
    RBA_ETHTCP_SEQ_INVALID_E           	= 3U	/* Received sequence number is invalid (out of the window) */
}rba_EthTcp_SeqVal_ten;

/* Type of acknowledgment number validity */
typedef enum
{
    RBA_ETHTCP_ACK_NEW_E                = 0U,   /* Received acknowledgment number is new */
    RBA_ETHTCP_ACK_DUPLICATE_E          = 1U,   /* Received acknowledgment number is an old duplicate */
    RBA_ETHTCP_ACK_INVALID_E            = 2U    /* Received acknowledgment number is invalid (ack for data which is not sent yet) */
}rba_EthTcp_AckVal_ten;


/* -------------------------------------------- */
/* Unions 										*/
/* -------------------------------------------- */

/* IP address union (for storing either an IPv4 or an IPv6 address) */
typedef union
{
	#if (TCPIP_IPV6_ENABLED == STD_ON)
	uint32                      IPv6Addr_au32[4]; /* IPv6 Address */
	#endif
	#if (TCPIP_IPV4_ENABLED == STD_ON)
    uint32                      IPv4Addr_u32;     /* IPv4 Address */
	#endif
}rba_EthTcp_IPAddr_tun;


/* -------------------------------------------- */
/* Structures 									*/
/* -------------------------------------------- */

/* Tcp standard header fields */
typedef struct
{
	uint32						SeqNum_u32;			/* Sequence number */
	uint32						AckNum_u32;			/* Acknowledgment number */
	uint16						SrcPort_u16;		/* Source port */
	uint16						DestPort_u16;		/* Destination port */
	uint16						HdrLen_u16;			/* Header length */
	uint16						WndSize_u16;		/* Window size */
	uint8						HdrFlag_u8;			/* Header flags */
}rba_EthTcp_HeaderFields_tst;

/* Tcp option fields */
typedef struct
{
	uint16						Mss_u16;			/* MSS value */
}rba_EthTcp_OptionFields_tst;

/* Tcp new socket info */
typedef struct
{
	TcpIp_LocalAddrIdType		LocalAddrId_u8;		/* Local address id which contains the local IP address for the new socket */
	uint16						LocalPort_u16;		/* Local Port number */
	uint16                      RemotePort_u16;		/* Remote Port number */
	TcpIp_DomainType            DomainType_u32;     /* Domain Type (INET or INET6) */
	rba_EthTcp_IPAddr_tun       RemoteIPAddr_un;	/* Remote address union */
	uint8						FramePrio_u8;		/* Frame priority for the new socket */
}rba_EthTcp_NewSockInfo_tst;

/* Tcp frame content */
typedef struct
{
	TcpIp_LocalAddrIdType		LocalAddrId_u8;		/* Local address id on which the frame is received */
	TcpIp_DomainType            DomainType_u32;     /* Domain Type (INET or INET6) */
    rba_EthTcp_IPAddr_tun       RemoteIPAddr_un;    /* Remote IP address on which the frame is received */
    uint16                      LocalPort_u16;      /* Local Port number on which the frame is received */
    uint16                      RemotePort_u16;     /* Remote Port number on which the frame is received */
	rba_EthTcp_HeaderFields_tst Header_st;			/* Tcp standard header fields */
	rba_EthTcp_OptionFields_tst	Options_st;			/* Tcp options */
	uint16 						PayloadLen_u16;		/* Payload length (counts the data and the sequence number space occupied by SYN or FIN) */
	uint16						DataOffset_u16;		/* From where the data starts */
	uint16						DataLen_u16;		/* Data length */
}rba_EthTcp_Frame_tst;

#if ( RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED == STD_ON || RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
/* Context for ISN generation */
typedef struct
{
    uint32  					IsnClock_u32;      		/* Clock used for CLOCK_DRIVEN and CLOCK_HASH_BASED generation of the ISN */
#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
    uint32  					IsnSecret_u32;        	/* Current secret used for CLOCK_HASH_BASED generation of the ISN */
    uint16  					IsnSecretTimer_u16;   	/* Timer for the regeneration of the secret after a predefined time */
    uint8   					IsnSecretUsageCntr_u8; 	/* Number of time the secret has been used without changing */
#endif
}rba_EthTcp_IsnGeneratorContext_tst;
#endif


/* -------------------------------------------- */
/* Configuration structure 					    */
/* -------------------------------------------- */
typedef struct
{
	/* ---------------------- Timeouts (32b) --------------------------------------- */
	/* Timeout in multiple of tcpIpMainFunctionPeriod to receive an ACK for our sent SYN-ACK from the remote node, i.e. maximum time */
	/* waiting in SYN-RCVD for confirming connection request acknowledgment after having both received and sent a connection request */
	uint32										SynRcvdTimeOut_u32;

#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
	/* Timeout in multiple of tcpIpMainFunctionPeriod before an unacknowledged TCP segment is sent again */
	uint32										ReTxTimeOut_u32;
#endif
#if ( RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON )
    /* Lower Boundary in multiple of tcpIpMainFunctionPeriod for the dynamic retransmission timeout */
    uint32                                      ReTxTimerLwrBound_u32;

	/* Upper Boundary in multiple of tcpIpMainFunctionPeriod for the dynamic retransmission timeout */
	uint32										ReTxTimerUprBound_u32;
#endif
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
    /* Specifies the time in multiple of tcpIpMainFunctionPeriod to wait before sending the first Keep Alive probe */
    uint32                                      KeepAlvTime_u32;

	/* Specifies the interval in multiple of tcpIpMainFunctionPeriod between subsequent Keep Alive probes */
	uint32										KeepAlvIntl_u32;
#endif
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
	/*  Maximum amount of time in multiple of tcpIpMainFunctionPeriod that transmitted data may remain unacknowledged before TCP forcefully closes the connection */
	uint32                                		UserTimeOut_u32;
#endif
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
    /*  Timeout in multiple of tcpIpMainFunctionPeriod before sending a delayed acknowledgment */
    uint32                                      DlyAckTimeOut_u32;
#endif

	/* Timeout in multiple of tcpIpMainFunctionPeriod to receive a FIN from the remote node (after this node has initiated connection termination), i.e. maximum time */
	/* waiting in FINWAIT-2 for a connection termination request from the remote TCP */
	uint32										FinWait2TimeOut_u32;

	/* Maximum segment lifetime in multiple of tcpIpMainFunctionPeriod. (Note: TIME-WAIT = 2 x TcpIpTcpMsl to ensure that the remote node received the acknowledgment to */
	/* its connection termination request.) */
	uint32										TcpMsl_u32;

    /* ---------------------- Isn Generation (32b) ------------------------------------- */
#if ( RBA_ETHTCP_ISN_CLOCK_DRIVEN_ENABLED == STD_ON || RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
    /* Clock factor for the Initial Sequence Number generation (needed for the equivalant of the incrementation of the current ISN timer every 4 microseconds) */
	/* This is used for Clock Driven or Cryptographic methods */
    uint32                                      IsnClockFactor_u32;
#endif
#if ( RBA_ETHTCP_ISN_CLOCK_HASH_BASED_ENABLED == STD_ON )
    /* Timeout in multiple of tcpIpMainFunctionPeriod for the ISN secret */
    /* This is used for Cryptographic method */
    uint32                                      IsnSecretTimeOut_u32;
#endif

    /* ---------------------- Rx Window (16b) --------------------------------------- */
    /* Default Rx Window size advertised by TCP (size of virtual RX buffer) */
    uint16                                      RxWindowMax_u16;

	/* ---------------------- Max retries (16b) ------------------------------------- */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
    /* Maximum number of times that Keep Alive Probe is retransmitted when there is no response from the remote */
    uint16                                      KeepAlvProbesMax_u16;
#endif

	/* ---------------------- Max retries (8b) --------------------------------------*/
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
	/* Maximum number of times that a TCP SYN is retransmitted */
	uint8										SynMaxRtx_u8;

	/* Maximum number of times that a TCP segment is retransmitted */
	uint8										TcpMaxRtx_u8;
#endif
#if ( RBA_ETHTCP_ZWP_ENABLED == STD_ON )
	/* Maximum number of times that Zero Window Probe is retransmitted when there is no response from the remote */
	uint8 										ZWPMaxRetries_u8;
#endif

	/* ---------------------- Time To Live (8b) ------------------------------------ */
	/* Default Time-to-live value of outgoing TCP packets */
	uint8										TcpTtl_u8;

}rba_EthTcp_Config_to;


/* -------------------------------------------- */
/* Socket options structure						*/
/* -------------------------------------------- */
typedef struct
{
    /* ---------------------- Option Configuration ------------------------------- */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
    /* Specifies the time in multiple of tcpIpMainFunctionPeriod to wait before sending the first Keep Alive probe */
    uint32                                      SOKeepAlvTime_u32;

    /* Specifies the interval in multiple of tcpIpMainFunctionPeriod between subsequent Keep Alive probes */
    uint32                                      SOKeepAlvIntl_u32;

    /* Maximum number of times that Keep Alive Probe is retransmitted when there is no response from the remote */
    uint16                                      SOKeepAlvProbesMax_u16;
#endif
    /* Specifies the default local window size */
    uint16                                      SORxWindowMax_u16;

    /* ---------------------- Option activation ---------------------------------- */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
    /* Socket Option : Keep Alive Enable/Disable */
      uint8                                     SOKeepAlvEnad_u8;
#endif
#if ( RBA_ETHTCP_NAGLE_ENABLED == STD_ON )
    /* Socket Option : Nagle's Algorithm Enable/Disable */
    uint8                                       SONaglesEnad_u8;
#endif

}rba_EthTcp_SockOpt_tst;


/* -------------------------------------------- */
/* Dynamic socket table structure				*/
/* -------------------------------------------- */
typedef struct
{
	/* ---------------------- Socket options (struct pointer) ---------------------- */
	/* Pointer to the Tcp socket options */
	rba_EthTcp_SockOpt_tst						*TcpSockOpt_pst;

	/* ---------------------- Tcp Tx buffer pointers (pointer) --------------------- */
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
	/* Pointer to the beginning of the Tx buffer per rba_EthTcp socket */
	uint8										* TxWndStrt_pu8;
	/* Pointer to the start of already available Tx data in Tcp buffer */
	uint8										* TxWndUnAckedData_pu8;
	/* Pointer to next data to be send -> there could be data in the buffer which is already sent, but not yet acknowledged */
	uint8										* TxWndNxtSnd_pu8;
	/* Pointer to the start of next Tcp free buffer behind the available already available Tx Data in buffer*/
	uint8										* TxWndNxtFree_pu8;
#endif

	/* ---------------------- States and Tcp flag (enum) --------------------------- */
    /* Flag to indicate in which state socket is */
    rba_EthTcp_SocketState_ten                  SockState_en;
	/* Tcp socket state */
	rba_EthTcp_ConnState_ten					State_en;
	/* Previous state of the Tcp socket, used for unexpected flag handling */
	rba_EthTcp_ConnState_ten					PrevState_en;
	/* Flag to indicate what is to be done in next MainFunction */
	rba_EthTcp_Flag_ten							TcpFlag_en;

	/* ---------------------- General timer (enum) --------------------------------- */
	/* Flag to indicate which General timer is currently running */
	rba_EthTcp_TmrSt_ten                    	GeneralTmrSt_en;

	/* ---------------------- Keep alive (enum) ------------------------------------ */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
	/* Flag to indicate if Keep Alive timer is currently running */
	rba_EthTcp_TmrSt_ten                    	KeepAlvTmrSt_en;
#endif

	/* ---------------------- Delayed ack (enum) ----------------------------------- */
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
	/* Flag to indicate if Delayed Ack timer is currently running */
	rba_EthTcp_TmrSt_ten                    	DlyAckTmrSt_en;
#endif

	/* ---------------------- User Timeout (enum) ---------------------------------- */
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
	/* Flag to indicate if User Timeout timer is currently running */
	rba_EthTcp_TmrSt_ten                    	UtoTmrSt_en;
#endif

	/* ----------------------- Addresses (32b) ------------------------------------- */
	/* Domain Type (INET or INET6) */
	TcpIp_DomainType                            DomainType_u32;
	/* Remote IP address union (IPv4 or IPv6) */
	rba_EthTcp_IPAddr_tun                       RemoteIPAddr_un;

	/* ---------------------- Transmission information (32b) ----------------------- */
	/* Initial Send Sequence Number */
    uint32                                      IniSndSeqNum_u32;
	/* Next sequence number to be sent */
	uint32 										SndSeqNum_u32;
	/* Next Ack number to be sent */
	uint32 										SndAckNum_u32;

	/* ---------------------- Reception information (32b) -------------------------- */
	/* Initial Receive Sequence Number */
    uint32                                      IniRcvdSeqNum_u32;
	/* Seq Num in the latest received Rx frame */
	uint32 										RcvdSeqNum_u32;
	/* Ack Num in the latest received Rx frame */
	uint32 										RcvdAckNum_u32;

	/* ---------------------- Current unacknowledged data (32b) -------------------- */
	/* Oldest sequence number for which ack is not yet received */
	uint32										UnAckedSeqNum_u32;

	/* ---------------------- Last window update (32b) ----------------------------- */
	/*Segment Sequence Number with last window update*/
    uint32                                      WndUpdSeqNum_u32;
    /*Segment Acknowledgment Number with last window update*/
    uint32                                      WndUpdAckNum_u32;

	/* ---------------------- General timer (32b) ---------------------------------- */
	/* General timer for this socket */
    uint32                                      GeneralTmr_u32;

	/* ---------------------- Dynamic retransmission (32b) ------------------------- */
#if ( RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON )
	/* SRTT value used for RTO calculation */
	uint32										SRtt_u32;
	/* RTTVAR value used for RTO calculation */
	uint32										RttVar_u32;
	/* Calculated RTO (ReTransmission Timeout) */
	uint32										Rto_u32;
#endif

	/* ---------------------- Keep alive (32b) ------------------------------------- */
#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
	/* Keep alive timer	*/
	uint32										KeepAlvTmr_u32;
#endif

	/* ---------------------- User Timeout (32b) ----------------------------------- */
#if ( RBA_ETHTCP_USER_TIMEOUT_ENABLED == STD_ON )
	/*  User Timeout timer */
	uint32                              		UtoTmr_u32;
#endif

	/* ----------------------- Addresses (16b) ------------------------------------- */
    /* Local port number */
    uint16                                      LocalPort_u16;
    /* Remote port number */
    uint16                                      RemotePort_u16;

    /*------------------------ Local data (16b) ------------------------------------ */
    /* Remaining channels in case the present socket is listening (remaining Tcp sockets that can be forked from this socket) */
    uint16                                      RemainChannels_u16;
    /* Locam Maximum Segment Size */
    uint16                                      LocalMss_u16;

	/* ---------------------- Occupied sizes in the Tcp Tx buffer (16b) ------------ */
#if ( RBA_ETHTCP_TXWNDSIZE > 0 )
	/* Size of data to be sent location in the Tcp Tx buffer */
	uint16                                      TxOccupiedSizeSnd_u16;
	/* Size of unacknowledged data location in the Tcp Tx buffer */
	uint16                                      TxOccupiedSizeUnacked_u16;
#endif

	/* ---------------------- Transmission information (16b) ----------------------- */
	/* Advertised window size by this socket */
	uint16 										SndWndSize_u16;

	/* ---------------------- Reception information (16b) -------------------------- */
	/* Advertised window size in the Rx frame */
	uint16 										RcvdWndSize_u16;
	/* Received Maximum Segment Size */
	uint16                                      RcvdMss_u16;
	/* Received data length */
	uint16										RcvdDataLen_u16;
	/* Received data offset */
	uint16										RcvdDataOffset_u16;
	/* Total received data length since the last sending of ack number */
	uint16 										TotalRcvdDataLen_u16;

	/* ---------------------- Oldest unacknowledged segment length (16b) ----------- */
	/* Oldest segment length for which the full acknowledgement has not been received yet */
	uint16										OldestUnackedSegmentLength_u16;

	/* ----------------------- Keep alive (16b) ------------------------------------ */
	#if ( RBA_ETHTCP_KEEP_ALIVE_ENABLED == STD_ON )
	    /* Retry counter */
	uint16                                       KeepAlvRetryCntr_u16;
	#endif
	/* ----------------------- Addresses (8b) -------------------------------------- */
    /* Local address id */
    TcpIp_LocalAddrIdType                       LocalAddrId_u8;

    /* ---------------------- Link to listening socket (8b)------------------------- */
    /* Tcp socket index of the listening socket in case the present socket is forked */
    TcpIp_SocketIdType                           ListenTcpSockIdx_uo;

    /*------------------------ Local data (8b) ------------------------------------- */
    /* Frame priority */
    uint8                                       SockFramePrio_u8;

	/* ---------------------- Transmission information (8b) ------------------------ */
	/* Header flags in the Tx frame to be sent */
	uint8  										SndHdrFlag_u8;

	/* ---------------------- Reception information (8b) --------------------------- */
	/* Header flags in the received Rx frame */
	uint8  										RcvdHdrFlag_u8;

	/* ---------------------- Received duplicate ACK counter (8b) ------------------ */
	/* Received duplicate ACK counter since the last retransmission */
	uint8  										DuplicateAckCntr_u8;

	/* ---------------------- General timer (8b) ----------------------------------- */
	/* Retry counter */
	uint8  										GeneralRetryCntr_u8;

	/* ---------------------- Delayed ack (8b) ------------------------------------- */
#if ( RBA_ETHTCP_DLYACK_ENABLED == STD_ON )
	/* Delay ACK timer	*/
	uint8										DlyAckTmr_u8;
#endif

	/* ---------------------- Postpone flags (boolean) ----------------------------- */
	/* Flag indicating if a SYN needs to be postponed */
	boolean										PostponeSyn_b;
	/* Flag indicating if a FIN needs to be postponed */
	boolean										PostponeFin_b;

	/* ---------------------- General timer (boolean) ------------------------------ */
#if ( RBA_ETHTCP_RETX_ENABLED == STD_ON )
	/* Flag indicating if a retransmission is running */
	boolean										RetransmissionFlg_b;
#endif

	/* ---------------------- Dynamic retransmission (boolean) --------------------- */
#if ( RBA_ETHTCP_DYNAMIC_RETX_TIMER == STD_ON )
	/* Flag indicating if an RTT measurement is in progress */
	boolean										RttInProgress_b;
#endif

}rba_EthTcp_DynSockTblType_tst;


#endif	/* #if ( defined(TCPIP_TCP_ENABLED) && ( TCPIP_TCP_ENABLED == STD_ON ) ) */
#endif /* RBA_ETHTCP_TYPES_H */






























