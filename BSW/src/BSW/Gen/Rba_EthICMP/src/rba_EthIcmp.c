

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "TcpIp.h"

#if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) )

#include "rba_EthIcmp.h"
#include "rba_EthIcmp_Cbk.h"

#if (TCPIP_TCP_ENABLED == STD_ON)
#include "rba_EthTcp.h"
#endif

#if (TCPIP_IPV4_ENABLED == STD_ON)
#include "rba_EthIPv4.h"
#endif

#include "TcpIp_Prv.h"
#include "TcpIp_Lib.h"
#include "rba_EthIcmp_Prv.h"

#if ( TCPIP_DEV_ERROR_DETECT != STD_OFF )
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#error "DET AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#error "DET AUTOSAR minor version undefined or mismatched"
#endif
#endif /* ( TCPIP_DEV_ERROR_DETECT != STD_OFF ) */

/* DEM AR version check */
# if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != TCPIP_AR_RELEASE_MAJOR_VERSION))
#  error "DEM AUTOSAR major version undefined or mismatched."
# endif
# if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != TCPIP_AR_RELEASE_MINOR_VERSION))
#  error "DEM AUTOSAR major version undefined or mismatched."
# endif

/*
 ***************************************************************************************************
 * Global Variables
 ***************************************************************************************************
 */

#define RBA_ETHICMP_START_SEC_VAR_CLEARED_16
#include "rba_EthIcmp_MemMap.h"
static VAR( uint16, RBA_ETHICMP_VAR ) rba_EthIcmp_SeqNumCnt_u16 = 0;
#define RBA_ETHICMP_STOP_SEC_VAR_CLEARED_16
#include "rba_EthIcmp_MemMap.h"

#define RBA_ETHICMP_START_SEC_VAR_INIT_8
#include "rba_EthIcmp_MemMap.h"
/* Flag to indicate whether rba_EthIcmp_Init has been executed or not since power ON */
VAR( boolean,     RBA_ETHICMP_CODE )   rba_EthIcmp_InitFlag_b = FALSE;
#define RBA_ETHICMP_STOP_SEC_VAR_INIT_8
#include "rba_EthIcmp_MemMap.h"

#define RBA_ETHICMP_START_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIcmp_MemMap.h"
/* ICMP configuration pointer */
P2CONST( rba_EthIcmp_Config_to, AUTOMATIC, AUTOMATIC )      rba_EthIcmp_CurrConfig_pco = NULL_PTR;
#define RBA_ETHICMP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "rba_EthIcmp_MemMap.h"

/********************************************************************************************************************************/
/* rba_EthTcp_Init()    - By this API service the rba_EthIcmp module is initialised if the configuration pointer is valid       */
/*                                                                                                                              */
/* Parameters (in):                                                                                                             */
/* IcmpConfig_pco       - Pointer to the configuration data of the rba_EthIcmp module.                                          */
/*                                                                                                                              */
/* Parameters (inout):  None                                                                                                    */
/*                                                                                                                              */
/* Parameters (out):    None                                                                                                    */
/*                                                                                                                              */
/* Return value:        None                                                                                                    */
/*                                                                                                                              */
/********************************************************************************************************************************/
#define RBA_ETHICMP_START_SEC_CODE
#include "rba_EthIcmp_MemMap.h"
FUNC( void, RBA_ETHICMP_CODE )  rba_EthIcmp_Init( P2CONST(rba_EthIcmp_Config_to, AUTOMATIC, AUTOMATIC) IcmpConfig_pco )
{

    /* Initialise the Init flag */
    rba_EthIcmp_InitFlag_b    =   FALSE;
    rba_EthIcmp_CurrConfig_pco =   NULL_PTR;

    /* Report DET if TcpIp_CurrConfig_pco is not intialized */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == TcpIp_CurrConfig_pco ),                                  \
    		                               RBA_ETHICMP_E_INIT_API_ID, RBA_ETHICMP_E_INIT_FAILED )

    /* Report DET if TcpIp module is uninitialised */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID( ( IcmpConfig_pco != ( TcpIp_CurrConfig_pco->EthIcmpConfig_pco) ),      \
                                           RBA_ETHICMP_E_INIT_API_ID, RBA_ETHICMP_E_INV_ARG )

    /* Update the ICMP config pointer */
    rba_EthIcmp_CurrConfig_pco = IcmpConfig_pco;

    /* Set a flag, to indicate that the rba_EthIcmp_Init() has been called */
    rba_EthIcmp_InitFlag_b = TRUE;

    return;
}


/********************************************************************************************************************/
/* TcpIp_IcmpTransmit() - By this API service TCP/IP stack sends an ICMP message according to specified parameters. */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/*  LocalAddrId_u8 - IP address identifier representing the local IP address and EthIf controller which shall be    */
/*                   used for transmission of the ICMP message.                                                     */
/*  RemoteAddr_cpst- Pointer to structure representing the remote address.                                           */
/*  Ttl_u8        - Time to live value to be used for the ICMP message. If 0 is specified the default value shall   */
/*                  be used.                                                                                        */
/*  Type_u8       - Type field value to be used in the ICMP message                                                 */
/*                  Note: the value of the type field determines the format of the remaining ICMP message data      */
/*  Code_u8       - Code field value to be used in the ICMP message                                                 */
/*  DataLength_u16- Length of ICMP message                                                                          */
/*  TxData_cpu8    - Pointer to data which shall be sent as ICMP message data                                        */
/*                                                                                                                  */
/* Return   - Result of operation :                                                                                 */
/*               E_OK The request has been accepted                                                                 */
/*               E_NOT_OK The request has not been accepted                                                         */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( Std_ReturnType, RBA_ETHICMP_CODE ) rba_EthIcmp_Transmit (
                                                VAR( TcpIp_LocalAddrIdType, AUTOMATIC )             LocalAddrId_u8,
                                                P2CONST( TcpIp_SockAddrInetType, AUTOMATIC, AUTOMATIC )  RemoteAddr_cpst,
                                                VAR( uint8, AUTOMATIC )                             Ttl_u8,
                                                VAR( uint8, AUTOMATIC )                             Type_u8,
                                                VAR( uint8, AUTOMATIC )                             Code_u8,
                                                VAR( uint16, AUTOMATIC )                            DataLength_u16,
                                                P2CONST( uint8, AUTOMATIC, AUTOMATIC )              TxData_cpu8 )
{
    /* Local variable declaration */
    VAR( BufReq_ReturnType, AUTOMATIC )             lBufReqRetVal_en;
    VAR( TcpIp_ReturnType, AUTOMATIC )              lIPv4TxRetVal_en;
    VAR( Std_ReturnType, AUTOMATIC )                lRetVal_en;
    VAR( TcpIp_IpHeader_tst, AUTOMATIC )            lIpHeader_st;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )            lTxDatBuf_pu8;
    VAR( uint16, AUTOMATIC )                        lIdx_u16;
    VAR( uint16, AUTOMATIC )                        lLength_u16;
    VAR( uint16, AUTOMATIC )                        lDataOffset_u16;
    VAR( uint8, AUTOMATIC )                         lBufIdx_u8;
    VAR( uint8, AUTOMATIC )                         lFramePrio_u8;


    /* Local variable initialisation */
    lRetVal_en                  = E_NOT_OK;
    lBufReqRetVal_en            = BUFREQ_E_NOT_OK;
    lIpHeader_st.ProtoType_en   = TCPIP_IPPROTO_NONE;
    lIpHeader_st.Ttl_u8         = 0;

    /* Report DET if rba_EthIcmp module is uninitialised */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VALUE( ( FALSE == rba_EthIcmp_InitFlag_b ), RBA_ETHICMP_E_TRANSMIT_API_ID,      \
                                            RBA_ETHICMP_E_NOTINIT, E_NOT_OK )

    /* Report DET if local address ID is invalid */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VALUE( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),   \
                                            RBA_ETHICMP_E_TRANSMIT_API_ID, RBA_ETHICMP_E_INV_ARG, E_NOT_OK )

    /* Report DET if RemoteAddr_cpst is a Null Pointer */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == RemoteAddr_cpst ), RBA_ETHICMP_E_TRANSMIT_API_ID,           \
                                            RBA_ETHICMP_E_NULL_PTR, E_NOT_OK )

    /* Report DET if TxData_cpu8 is a Null Pointer */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VALUE( ( NULL_PTR == TxData_cpu8 ), RBA_ETHICMP_E_TRANSMIT_API_ID,               \
                                            RBA_ETHICMP_E_NULL_PTR, E_NOT_OK )

    /* Increment the message length by Icmp header length */
    lLength_u16 = ( RBA_ETHICMP_PRV_HDR_LENGTH + DataLength_u16 );

    /* Get the statically configured frame priority (TcpIpIpFramePrioDefault) */
    lFramePrio_u8 = rba_EthIcmp_CurrConfig_pco->IcmpSubConfig_pco[LocalAddrId_u8].TcpIpCtrlFramePrio_cu8;

    /* Call the rba_EthIPv4_ProvideTxBuffer() to allocate memory for the data to be transmitted */
    lBufReqRetVal_en = rba_EthIPv4_ProvideTxBuffer(
                                        LocalAddrId_u8,
                                        ( RemoteAddr_cpst->addr[0] ),
                                        lFramePrio_u8,
                                        &lBufIdx_u8,
                                        &lTxDatBuf_pu8,
                                        &lLength_u16 );

    /* If buffer of requested length is allocated */
    if( BUFREQ_OK == lBufReqRetVal_en )
    {
        /* Prepare the ICMP header */
        ( lTxDatBuf_pu8[ RBA_ETHICMP_PRV_TYPE_OFFSET ] )        = Type_u8;
        ( lTxDatBuf_pu8[ RBA_ETHICMP_PRV_CODE_OFFSET ] )        = Code_u8;
        /* Initialise the checksum fields to zero for checksum calculation */
        ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_CHKSUM_OFFSET] )        = 0x00U;
        ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_CHKSUM_OFFSET + 1U] )   = 0x00U;

        switch ( Type_u8 )
        {
             case (uint8) RBA_ETHICMP_ECHO_REQ_E:
            {
                /* Increment sequence number for echo transmit request */
                ( rba_EthIcmp_SeqNumCnt_u16++ );
                TcpIp_WriteU16( &lTxDatBuf_pu8[RBA_ETHICMP_PRV_IDENTIFIER_OFFSET],  RBA_ETHICMP_PRV_IDENTIFIER_FIELD );
                TcpIp_WriteU16( &lTxDatBuf_pu8[RBA_ETHICMP_PRV_SEQNUM_OFFSET],      rba_EthIcmp_SeqNumCnt_u16 );
                lDataOffset_u16 = 0;
                break;
            }

            case (uint8) RBA_ETHICMP_ECHO_REPLY_E:
            {   /* Move the pointer to identifier offset */
                TxData_cpu8 = ( TxData_cpu8 - RBA_ETHICMP_PRV_HDR_LENGTH_PARTIAL );
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_IDENTIFIER_OFFSET] )        = TxData_cpu8[0];
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_IDENTIFIER_OFFSET + 1U] )   = TxData_cpu8[1];
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_SEQNUM_OFFSET] )            = TxData_cpu8[2];
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_SEQNUM_OFFSET + 1U] )       = TxData_cpu8[3];
                /* The received ICMP header should be copied into the transmit buffer. Hence add offset of 4 */
                lDataOffset_u16                                             = RBA_ETHICMP_PRV_HDR_LENGTH_PARTIAL;
                break;
            }

            case (uint8) RBA_ETHICMP_DEST_UNREACH_E:
            default:
            {   /* Identifier field and Sequence are unused for Destination Unreachable ICMP frame */
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_IDENTIFIER_OFFSET] )        = 0;
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_IDENTIFIER_OFFSET + 1U] )   = 0;
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_SEQNUM_OFFSET] )            = 0;
                ( lTxDatBuf_pu8[RBA_ETHICMP_PRV_SEQNUM_OFFSET + 1U] )       = 0;
                lDataOffset_u16                                             = 0;
                break;
            }
        } /* end - if( ( RBA_ETHICMP_PRV_HDR_LENGTH + DataLength_u16 ) <= lLength_u16 ) */

        /* Copy data into the transmit buffer */
        for( lIdx_u16 = 0; lIdx_u16 < DataLength_u16; lIdx_u16++ )
        {
            ( lTxDatBuf_pu8[ lIdx_u16 + RBA_ETHICMP_PRV_HDR_LENGTH ] ) = ( TxData_cpu8[ lIdx_u16 + lDataOffset_u16 ] );
        }

        /* Update the protocol type to ICMP in the IP header content structure */
        lIpHeader_st.ProtoType_en = TCPIP_IPPROTO_ICMP;

        if( 0 == Ttl_u8 )
        {
            /* If the passed Time-to-live value is 0, configured default value is used */
            lIpHeader_st.Ttl_u8 = rba_EthIcmp_CurrConfig_pco->Ttl_u8;
        }
        else
        {
            /* Pass the Time-to-live value as it is, if it is not 0 */
            lIpHeader_st.Ttl_u8 = Ttl_u8;
        }

        /* Send the ICMP packet */
        lIPv4TxRetVal_en = rba_EthIPv4_Transmit (   LocalAddrId_u8,
                                                    ( RemoteAddr_cpst->addr[0] ),
                                                    lTxDatBuf_pu8,
                                                    lBufIdx_u8,
                                                    &lIpHeader_st,
                                                    lLength_u16 );

        if( TCPIP_OK == lIPv4TxRetVal_en )
        {
            lRetVal_en = E_OK;
        }
    } /* end - if( BUFREQ_OK == lBufReqRetVal_en ) */

    return ( lRetVal_en );
}

/********************************************************************************************************************/
/* rba_EthIcmp_RxIndication() - Function called when an ICMP is received. A response is sent according to the ICMP  */
/*                              frame type.                                                                         */
/*                                                                                                                  */
/* Input Parameters :                                                                                               */
/* RmtIPAddr_u32       - (Source IP) needed in SoAd optional RX Filter and in ICMP                                  */
/* localAddrId_u32     - Contains EthIfCtrl and local IP address derived in IPv4 module from IP                     */
/*                       header                                                                                     */
/* RxData_pu8          - Pointer to received data behind IPv4 header                                                */
/* RxDataLen_u16       - Length of the pointer received in parameter                                                */
/* IsBroadcast_b       - Indicates whether received frame is a broadcast frame or not                               */
/*                                                                                                                  */
/* Return   - Result of operation :  void                                                                           */
/*                                                                                                                  */
/********************************************************************************************************************/
FUNC( void, RBA_ETHICMP_CODE ) rba_EthIcmp_RxIndication(    VAR( uint32, AUTOMATIC )                RmtIPAddr_u32,
                                                            VAR( uint8, AUTOMATIC )                 LocalAddrId_u8,
                                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    RxData_pu8,
                                                            VAR( uint16, AUTOMATIC )                RxDataLen_u16,
                                                            VAR( boolean, AUTOMATIC)                IsBroadcast_b )
{
    /* Local variable declaration */
    VAR( Std_ReturnType, AUTOMATIC )                lRetVal_en;
    VAR( TcpIp_SockAddrInetType, AUTOMATIC )        lIPAddrPort_st;
    VAR( TcpIp_SockAddrInetType, AUTOMATIC )        lLocalIPAddrPort_st;
    VAR( TcpIp_SockAddrInetType, AUTOMATIC )        lRemoteIPAddrPort_st;
    VAR( TcpIp_SocketIdType, AUTOMATIC )            lTcpIpSockId_u16;
    VAR( uint16, AUTOMATIC )                        lTempVal_u16;
    VAR( uint8 , AUTOMATIC )                        lProtType_u8;
    VAR( boolean, AUTOMATIC )                       lUpperLayerCbkReqd_b;

    P2VAR( uint8, AUTOMATIC, AUTOMATIC )            lRxData_pu8;
    P2CONST( rba_EthIcmp_SubConfig_to, AUTOMATIC, AUTOMATIC )   lIcmpSubConfig_pcst;

    /* Local variable initialisation */
    lUpperLayerCbkReqd_b    = FALSE;
    lRxData_pu8             = NULL_PTR;
    lTcpIpSockId_u16        = 0;
    lIcmpSubConfig_pcst     = ( &(rba_EthIcmp_CurrConfig_pco->IcmpSubConfig_pco[LocalAddrId_u8] ) );

	/* Initialize local and remote address domain to TCPIP_AF_INET */
    lLocalIPAddrPort_st.domain  = TCPIP_AF_INET;
    lRemoteIPAddrPort_st.domain = TCPIP_AF_INET;


    /* Report DET if rba_EthIcmp module is uninitialised */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID( ( FALSE == rba_EthIcmp_InitFlag_b ), RBA_ETHICMP_E_RX_INDICATION_API_ID,      \
                                           RBA_ETHICMP_E_NOTINIT )


    /* Report DET if local address ID is invalid */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID( ( LocalAddrId_u8 >= ( TcpIp_CurrConfig_pco->NumLocalAddrConfig_u8 ) ),        \
                                           RBA_ETHICMP_E_RX_INDICATION_API_ID, RBA_ETHICMP_E_INV_ARG )

    /* Report DET if RxData_pu8 is a Null Pointer */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID( ( NULL_PTR == RxData_pu8 ), RBA_ETHICMP_E_RX_INDICATION_API_ID,               \
                                           RBA_ETHICMP_E_NULL_PTR )

    /* Report DET if RxDataLen_u16 is invalid */
    RBA_ETHICMP_DET_REPORT_ERROR_RET_VOID( ( RxDataLen_u16 < RBA_ETHICMP_PRV_HDR_LENGTH ), RBA_ETHICMP_E_RX_INDICATION_API_ID,  \
                                           RBA_ETHICMP_E_INV_ARG )


        /* Check the type of the ICMP Frame */
        switch ( RxData_pu8[ RBA_ETHICMP_PRV_TYPE_OFFSET ] )
        {
            /* If echo reply is received */
            case (uint8) RBA_ETHICMP_ECHO_REPLY_E:
            {
                /* Check if the identifier field is correct */
                TcpIp_ReadU16 ( &RxData_pu8[RBA_ETHICMP_PRV_IDENTIFIER_OFFSET], &lTempVal_u16 );

                if ( RBA_ETHICMP_PRV_IDENTIFIER_FIELD == lTempVal_u16 )
                {   /* Call configured callback function - TcpIpIcmpMsgHandlerName */
                    lUpperLayerCbkReqd_b = TRUE;
                }
            }
            break;

            /* If echo request is received  */
            case (uint8) RBA_ETHICMP_ECHO_REQ_E:
            {
                /* Send echo reply if the received echo request is broadcast and */
                /* reply to Broadcast request is enabled for the particular LocalAddrId. */
                /* Send echo reply if its a unicast request */
                if((( TCPIP_FRAME_IS_BROADCAST == IsBroadcast_b ) &&
                    ( rba_EthIcmp_CurrConfig_pco->IcmpSubConfig_pco[LocalAddrId_u8].EchoBroadcastEn_cu8 == (STD_ON) )) ||
                    ( TCPIP_FRAME_IS_NOTBROADCAST == IsBroadcast_b ))
                {
                     ( lIPAddrPort_st.addr[0] )  = RmtIPAddr_u32;
                     /* Send ICMP Echo reply frame */
                     /* Transmit the received identifier field, sequence number and data back to the sending node */
                     /* So Frame data length is - ( identifier field length + sequence number length + receive data length )*/
                     (void)rba_EthIcmp_Transmit( LocalAddrId_u8,
                                               ( &lIPAddrPort_st ) ,             /* Remote node IP address and port */
                                               0U,                               /* TTL = 0 indicates default value will be used */
                                               (uint8)RBA_ETHICMP_ECHO_REPLY_E,  /* ICMP Control Message Type */
                                               0U,                               /* ICMP Control Message Code - 0 */
                                               ( RxDataLen_u16 - RBA_ETHICMP_PRV_HDR_LENGTH ), /* DataLength */
                                               ( &( RxData_pu8[RBA_ETHICMP_PRV_HDR_LENGTH] ) ) );  /* Pointer to ICMP data field */
                }
            }
            break;

            /* If received information request */
            /* case RBA_ETHICMP_INFO_REQ: */
            /* lUpperLayerCbkReqd_b = TRUE; */
            /* break; */

            /* If received Time Stamp */
            /* case RBA_ETHICMP_TIMESTAMP: */
            /* lUpperLayerCbkReqd_b = TRUE; */
            /* break; */

            /* If received Destination unreachable */
            case  (uint8) RBA_ETHICMP_DEST_UNREACH_E:
            {
                /* If ICMP port unreachable frame is received */
                if ( RxData_pu8[RBA_ETHICMP_PRV_CODE_OFFSET] ==  (uint8) RBA_ETHICMP_DEST_UNREACH_PORT_E )
                {
                    /* Report DEM error if TCPIP_E_CONNREFUSED is configured */
                    if( 0 != lIcmpSubConfig_pcst->DemEventId_ConRefused_u16 )
                    {
                        Dem_ReportErrorStatus( lIcmpSubConfig_pcst->DemEventId_ConRefused_u16,
                                               DEM_EVENT_STATUS_FAILED );
                    }

                    /* Upper layer call back not required */
                    lUpperLayerCbkReqd_b = FALSE;

                    /* Move the RX buffer pointer to the ICMP data field */
                    lRxData_pu8 = &( RxData_pu8[RBA_ETHICMP_PRV_HDR_LENGTH] );

                    /* Extract the transport layer protocol type */
                    lProtType_u8 = lRxData_pu8[RBA_ETHIPV4_TP_PROTOCOL];

                    /* If protocol type is TCP, close the socket with abort value true */
                    if ( (uint8) TCPIP_IPPROTO_TCP == lProtType_u8 )
                    {
                    #if ( TCPIP_TCP_ENABLED == STD_ON )
                        /* Extract the local and remote IP addresses from the IP header in the ICMP data field */
                        TcpIp_ReadU32 ( &( lRxData_pu8[RBA_ETHIPV4_SRCIPV4ADDR_OFFSET] ),
                                                  &( lLocalIPAddrPort_st.addr[0] ) );

                        TcpIp_ReadU32 ( &( lRxData_pu8[RBA_ETHIPV4_DESTIPV4ADDR_OFFSET] ),
                                                  &( lRemoteIPAddrPort_st.addr[0] ) );

                        /* Move the RX buffer pointer to the TP header in the ICMP data field */
                        lRxData_pu8 = ( lRxData_pu8 + RBA_ETHIPV4_HDRLENGTH );

                        /* Extract the local and remote port numbers from the TP header */
                        TcpIp_ReadU16 ( &( lRxData_pu8[TCPIP_TP_SRCPORT_OFFSET] ),
                                                   &( lLocalIPAddrPort_st.port ) );

                        TcpIp_ReadU16 ( &( lRxData_pu8[TCPIP_TP_DESTPORT_OFFSET] ),
                                                   &( lRemoteIPAddrPort_st.port ) );


                        /* Call rba_EthTcp_FindTcpSockId API to retrieve the Id of the socket that has to be closed. */
                        /* The input parameters to the API are obtained from the IPv4 header present in the ICMP data field */
                        /* MR12 RULE 11.3 VIOLATION: typecasted to TcpIp_SockAddrType to match the function parameter Type definition */
                        lRetVal_en=  rba_EthTcp_FindTcpSockId( (const TcpIp_SockAddrType*)&lLocalIPAddrPort_st,
                                                               (const TcpIp_SockAddrType*)&lRemoteIPAddrPort_st,
                                                                &lTcpIpSockId_u16);


                        /* A socket has been found that shall be closed */
                        if (( E_OK == lRetVal_en ) && ( lTcpIpSockId_u16 < TCPIP_TCPSOCKETMAX ))
                        {
                                (void)rba_EthTcp_Close( lTcpIpSockId_u16,
                                                   TRUE );
                        }
                        /* Socket to be closed was not found in the TcpIp dynamic socket table */
                        else
                        {
                        /* Do nothing */
                        }
                    #endif
                    }
                    else
                    {
                        /* If protocol is UDP, do not close the socket */
                    }
                }/* end - if ( RxData_pu8[RBA_ETHICMP_PRV_CODE_OFFSET] == RBA_ETHICMP_DEST_UNREACH_PORT_E ) */
            }
            break;

            default:
                /*Nothing to do*/
            break;
        }

        /* Call configured callback function defined in upper layer. */
        /* If Echo request is received, the reply is sent by rba_EthIcmp. No need to inform upper layer about reception of Echo Request */
        if( ( NULL_PTR != ( rba_EthIcmp_CurrConfig_pco->IcmpRxIndication_pfct ) ) &&
            ( FALSE != lUpperLayerCbkReqd_b ) )
        {
            ( lIPAddrPort_st.addr[0] )  = RmtIPAddr_u32;

            (void)( rba_EthIcmp_CurrConfig_pco->IcmpRxIndication_pfct )(
                                                LocalAddrId_u8,
                                                ( (TcpIp_SockAddrInetType*)&( lIPAddrPort_st ) ),   /* Remote node IP address */
                                                0,                          /* TTL = 0 indicates default value will be used */
                                                RxData_pu8[ RBA_ETHICMP_PRV_TYPE_OFFSET ],  /* ICMP Control Message Type */
                                                RxData_pu8[ RBA_ETHICMP_PRV_CODE_OFFSET ],  /* ICMP Control Message Code */
                                                ( RxDataLen_u16 - RBA_ETHICMP_PRV_HDR_LENGTH ),     /* DataLength */
                                                ( &( RxData_pu8[RBA_ETHICMP_PRV_HDR_LENGTH] ) ) );  /* Pointer to ICMP data field */
        }

    return;
}
#define RBA_ETHICMP_STOP_SEC_CODE
#include "rba_EthIcmp_MemMap.h"

#endif  /* #if ( defined(TCPIP_ICMP_ENABLED) && ( TCPIP_ICMP_ENABLED == STD_ON ) ) */



