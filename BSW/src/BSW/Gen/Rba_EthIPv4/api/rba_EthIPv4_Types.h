

#ifndef RBA_ETHIPV4_TYPES_H
#define RBA_ETHIPV4_TYPES_H

#if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) )

/* This structure holds information about amount of buffer available per controller */
typedef struct
{
        VAR( uint32,                                 AUTOMATIC )   FreeBufPos_u32;          /* Index pointing to the available buffer   */
        VAR( uint32,                                 AUTOMATIC )   FreeBufLength_u32;       /* Number of bytes available from the index */
} rba_EthIPv4_FragBufTbl_tst;

/* This structure contains information about reassembly resources */
typedef struct{
    CONSTP2VAR( uint16,         AUTOMATIC, AUTOMATIC )    ReassemblyBuf_cpu16;              /* Pointer to reassembly buffer                                                                              */
    VAR( TcpIp_ProtocolType,              AUTOMATIC )     ProtoType_en;                     /* TP layer protocol of the received fragment                                                                */
    VAR( uint32,                          AUTOMATIC )     SrcIp_u32;                        /* Source IP of the received fragment                                                                        */
    VAR( uint32,                          AUTOMATIC )     DstIp_u32;                        /* Destination IP of the received fragment                                                                   */
    VAR( uint32,                          AUTOMATIC )     TimerCurrentValue_u32;            /* Pending time out value for the current reassembly buffer in ticks (1 tick = TcpIp main function period)   */
    #if ( TCPIP_ICMP_ENABLED == STD_ON )
    VAR( uint8,                           AUTOMATIC )     IcmpTimeExceededPayload_au8[68];  /* IPv4 header of the first fragment + first eight octets of the IPv4 payload                                */
    #endif /* #if ( TCPIP_ICMP_ENABLED == STD_ON ) */
    VAR( uint16,                          AUTOMATIC )     FrameId_u16;                      /* Frame identifier of the received frame                                                                    */
    VAR( uint16,                          AUTOMATIC )     FirstHolePos_u16;                 /* Index of the first free hole in the reassembly buffer                                                     */
    VAR( uint16,                          AUTOMATIC )     TotalPalyloadLen_u16;             /* Total length of IPv4 payload before frame undergoing fragmentation                                        */
}rba_EthIPv4_ReassemblyBufDescriptor_tst;


/* This structure contains IPv4 configuration per Ctrl */
typedef struct
{
#if ( RBA_ETHIPV4_REASSEMBLY_ENABLED == STD_ON )
    CONSTP2VAR( rba_EthIPv4_ReassemblyBufDescriptor_tst, AUTOMATIC,  AUTOMATIC )     ReassemblyBufDescriptor_cpst; /* Pointer to reassembly buffer descriptor                                               */
    CONST( uint32,                                                   AUTOMATIC )     ReassemblyTimeout_cu32;       /* Reassembly time out value configured, in ticks (1 tick = TcpIp main function period) */
    CONST( uint16,                                                   AUTOMATIC )     ReassemblyBufSize_cu16;       /* Reassembly buffer size                                                                */
    CONST( uint8,                                                    AUTOMATIC )     ReassemblyBufCnt_cu8;         /* Reassembly buffer count                                                               */
#endif

#if ( RBA_ETHIPV4_FRAG_ENABLED == STD_ON )
    CONSTP2VAR( uint8,                       AUTOMATIC,  AUTOMATIC )     TxFragBuf_cpu8;         /* Pointer to fragmentation buffer. NULL_PTR indicates fragmentation is disabled for the Ctrl  */
    CONST( uint32,                                       AUTOMATIC )     TxFragBufSize_cu32;     /* Size of the fragmentation buffer for the controller. In addition to configured Size it includes additional bytes required to store hidden header  */
    CONSTP2VAR( rba_EthIPv4_FragBufTbl_tst,  AUTOMATIC,  AUTOMATIC )     TxFragBufTbl_cpst;      /* Pointer to buffer handle table. NULL_PTR indicates fragmentation is disabled for the Ctrl   */
    CONST( uint16,                                       AUTOMATIC )     TxFragBufTblSize_cu16;  /* Size of table rba_EthIPv4_FragBufTbl_tst. Table size is defined sufficient enough to handle all fragmentation buffer request.*/
#endif

    CONST( uint16,                                       AUTOMATIC )     EthIfCtrlMtu_cu16;      /* Specifies the maximum transmission unit (MTU) of the EthIfCtrl in bytes */
    CONST( boolean,                                      AUTOMATIC )     TtlEnabled_cb;          /* Enable/Disable TTL                                                      */
}rba_EthIPv4_CtrlCfg_tst;

/* IPv4 configuration structure */
typedef struct
{
    CONSTP2CONST ( rba_EthIPv4_CtrlCfg_tst, RBA_ETHIPV4_CONST, AUTOMATIC ) *IPv4CtrlCfg_pco;                    /* Pointer to Ctrl configuration structure         */
}rba_EthIPv4_Config_to;

#endif /* #if ( defined(TCPIP_IPV4_ENABLED) && ( TCPIP_IPV4_ENABLED == STD_ON ) ) */

#endif /* RBA_ETHIPV4_TYPES_H */

