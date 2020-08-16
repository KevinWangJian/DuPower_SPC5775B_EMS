

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED

#include "Det.h"
#include "TcpIp.h"

#include "SoAd_Cbk.h"
#include "SoAd_Prv.h"

#ifdef SOAD_DEBUG_AND_TEST
#include "TestSoAdApplication.h"
#endif
#if (!defined(TCPIP_AR_RELEASE_MAJOR_VERSION) || (TCPIP_AR_RELEASE_MAJOR_VERSION != SOAD_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - SoAd and TcpIp"
#endif

#if (!defined(TCPIP_AR_RELEASE_MINOR_VERSION) || (TCPIP_AR_RELEASE_MINOR_VERSION != SOAD_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
#endif


/*
 ***************************************************************************************************
 * Static function declaration
 ***************************************************************************************************
 */

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

static FUNC( Std_ReturnType, SOAD_CODE )            SoAd_IdentifySocketRouteSocket     (  VAR( TcpIp_SocketIdType, AUTOMATIC )                  TcpIpSocketId_uo,
                                                                                          P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddrPtr_cpst,
                                                                                          P2CONST( uint8, AUTOMATIC, AUTOMATIC )                Buffer_cpu8,
                                                                                          VAR( uint16, AUTOMATIC )                              Length_u16,
                                                                                          P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )       StaticSocketId_puo);

static FUNC( Std_ReturnType, SOAD_CODE )            SoAd_MsgAcceptancePolicy            (  VAR( SoAd_SoConIdType, AUTOMATIC )                   StaticSocketId_uo,
                                                                                           P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddrPtr_cpst );

#if (SOAD_UDP_PRESENT != STD_OFF)
static FUNC( boolean, SOAD_CODE )                   SoAd_MakeUdpSocketOnline            ( VAR( SoAd_SoConIdType, AUTOMATIC )                    StaticSocketId_uo,
                                                                                          P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddrPtr_cpst );
#endif /* SOAD_UDP_PRESENT != STD_OFF */

static FUNC( boolean, SOAD_CODE )                   SoAd_ProcessRcvdMessage             ( VAR( SoAd_SoConIdType, AUTOMATIC )                    StaticSocketId_uo,
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  MessagePtr_pu8,
                                                                                          VAR( uint16, AUTOMATIC )                              MessageLength_u16 );

static FUNC( uint16, SOAD_CODE )                    SoAd_DiscardPdu                     ( VAR( SoAd_SoConIdType, AUTOMATIC )                    StaticSocketId_uo,
                                                                                          VAR( uint32, AUTOMATIC )                              TotalPduDataLength_u32,
                                                                                          VAR( uint16, AUTOMATIC )                              RemainingLength_u16 );


static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE )  SoAd_ConvertMessageToPdu            ( VAR( SoAd_SoConIdType, AUTOMATIC )                    StaticSocketId_uo,
                                                                                          P2CONST( uint8, AUTOMATIC, AUTOMATIC )                CurrentPointer_cpu8,
                                                                                          VAR( uint16, AUTOMATIC )                              RemainingLength_u16,
                                                                                          P2VAR( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC )     RxPduDesc_pst,
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  PresentHeaderLength_pu8 );

static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ExtractPduHeader                ( VAR( SoAd_SoConIdType, AUTOMATIC )                    StaticSocketId_uo,
                                                                                          P2CONST( uint8, AUTOMATIC, AUTOMATIC )                CurrentPointer_cpu8,
                                                                                          P2VAR( uint16, AUTOMATIC, AUTOMATIC )                 RemainingAndPresentLength_pu16,
                                                                                          P2VAR( uint32, AUTOMATIC, AUTOMATIC )                 PduHeaderId_pu32,
                                                                                          P2VAR( uint32, AUTOMATIC, AUTOMATIC )                 PduDataLength_pu32 );

static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE )  SoAd_ProcessPduData                 ( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  PduData_pu8,
                                                                                          VAR( uint16, AUTOMATIC )                              RemainingLength_u16,
                                                                                          VAR( SoAd_RxPduDesc_tst, AUTOMATIC )                  RxPduDesc_st,
                                                                                          P2VAR( uint16, AUTOMATIC, AUTOMATIC )                 CopiedDataToUl_pu16 );

#if ( SOAD_IF_PRESENT != STD_OFF )
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE )  SoAd_ProcessPduDataIF               (
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
                                                                                          VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                          VAR( uint16, AUTOMATIC )                              RemainingLength_u16,
#endif
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  PduData_pu8,
                                                                                          VAR( SoAd_RxPduDesc_tst, AUTOMATIC )                  RxPduDesc_st,
                                                                                          P2VAR( uint16, AUTOMATIC, AUTOMATIC )                 CopiedDataToUl_pu16 );
#endif

#if ( SOAD_TP_PRESENT != STD_OFF )
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE )  SoAd_ProcessPduDataTPHeaderDisabled ( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  PduData_pu8,
                                                                                          VAR( uint16, AUTOMATIC )                              RemainingLength_u16,
                                                                                          VAR( SoAd_RxPduDesc_tst, AUTOMATIC )                  RxPduDesc_st,
                                                                                          P2VAR( uint16, AUTOMATIC, AUTOMATIC )                 CopiedDataToUl_pu16 );

static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE )  SoAd_ProcessPduDataTPHeaderEnabled ( VAR(SoAd_SoConIdType, AUTOMATIC)                       StaticSocketId_uo,
                                                                                         P2VAR( uint8, AUTOMATIC, AUTOMATIC )                   PduData_pu8,
                                                                                         VAR( uint16, AUTOMATIC )                               RemainingLength_u16,
                                                                                         VAR( SoAd_RxPduDesc_tst, AUTOMATIC )                   RxPduDesc_st,
                                                                                         P2VAR( uint16, AUTOMATIC, AUTOMATIC )                  CopiedDataToUl_pu16 );

static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE )  SoAd_ProcessPduDataTPExecCopy       ( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )                  PduData_pu8,
                                                                                          VAR( SoAd_RxPduDesc_tst, AUTOMATIC )                  RxPduDesc_st,
                                                                                          VAR( PduLengthType, AUTOMATIC )                       InitialDataLenUpperLayer_uo,
                                                                                          P2VAR( uint16, AUTOMATIC, AUTOMATIC )                 AvailableAndCopiedDataToUl_pu16 );
#endif

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE )                      SoAd_RxIndicationDetChk             ( VAR( TcpIp_SocketIdType, AUTOMATIC )                 TcpIpSocketId_uo,
                                                                                          P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddr_cpst,
                                                                                          P2CONST( uint8, AUTOMATIC, AUTOMATIC )               Buffer_cpu8,
                                                                                          VAR( uint16, AUTOMATIC )                             Length_u16 );
#endif

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"


/*
 ***************************************************************************************************
 * Interface functions
 ***************************************************************************************************
 */

#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

/*********************************************************************************************************************************/
/** SoAd_RxIndication()     - The TCP/IP stack calls this primitive after the reception of data on a socket.                    **/
/**                         The socket identifier along with configuration information determines which module is to be called. **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** SocketId                - TcpIp socket identifier of the related local socket resource                                      **/
/** RemoteAddrPtr           - Pointer to memory containing IP address and port of the remote host which sent the data           **/
/** BufPtr                  - Pointer to the received data                                                                      **/
/** Length                  - Data length of the received TCP segment or UDP datagram                                           **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           None                                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( void, SOAD_CODE ) SoAd_RxIndication(  VAR( TcpIp_SocketIdType, AUTOMATIC )                SocketId,
                                            P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC ) RemoteAddrPtr,
                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )                BufPtr,
                                            VAR( uint16, AUTOMATIC )                            Length )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst;
    VAR( Std_ReturnType, AUTOMATIC )                                    lRetVal_u8;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxStaticSocket_uo;
    VAR( SoAd_SoConIdType, AUTOMATIC )                                  lIdxDynSocket_uo;
    VAR( boolean, AUTOMATIC )                                           lRemoteAddressOverwritten_b;
    VAR( boolean, AUTOMATIC )                                           lDataForwrdedToUl_b;
#if ( SOAD_CONFIG_NUM_OF_UDP_SUPERVISION_TIMEOUT > 0U )
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;
#endif

    /* Initialization of local variables declared above */
    lRemoteAddressOverwritten_b = FALSE;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Check for API call errors */
    SoAd_RxIndicationDetChk( SocketId,
                             RemoteAddrPtr,
                             BufPtr,
                             Length );

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif
    {
        /* Initialization local variables which are declared above */
        lIdxStaticSocket_uo = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
        lIdxDynSocket_uo    = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;

        /* --------------------------------------------- */
        /* Identify related socket Route                 */
        /* --------------------------------------------- */

        /* Step (1) of [SWS_SoAd_00562] */
        /* For the reception of a message from an UDP or TCP socket and forwarding of the received data as PDU to the related upper layer the SoAd shall */
        /* (1) Identify the related socket connection and socket routes by using the SocketId provided at SoAd_RxIndication() */

        /* Get SoAd static socket from TcpIp SocketId provided at RxIndication */
        lRetVal_u8 = SoAd_IdentifySocketRouteSocket( SocketId,
                                                     RemoteAddrPtr,
                                                     BufPtr,
                                                     Length,
                                                     &lIdxStaticSocket_uo );

        /* Continue processing only if the SoAd socket was successfully identified */
        /* (If E_OK is returned, that means that the static and dynamic socket index are valid) */
        if( E_OK == lRetVal_u8 )
        {
            /* --------------------------------------------- */
            /* Message Acceptance Policy                     */
            /* --------------------------------------------- */

            /* Step (2) of [SWS_SoAd_00562] */
            /* For the reception of a message from an UDP or TCP socket and forwarding of the received data as PDU to the related upper layer the SoAd shall */
            /* (2) Filter messages according to the message acceptance policy */

            /* Execute SoAd message acceptance policy */
            lRetVal_u8 = SoAd_MsgAcceptancePolicy( lIdxStaticSocket_uo,
                                                   RemoteAddrPtr );

            /* Continue processing only if message is accepted */
            if( E_OK == lRetVal_u8 )
            {
                /* Get static socket configuration pointers */
                lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo]);

                /* Get dynamic socket from static socket */
                lIdxDynSocket_uo = (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo);

                /* Copy the global array index address to local pointer for further processing */
                lSoAdDyncSocConfig_pst = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

#if (SOAD_UDP_PRESENT != STD_OFF)
                /* --------------------------------------------- */
                /* Make UDP socket online                        */
                /* --------------------------------------------- */

                /* [SWS_SoAd_00592] */
                /* Within SoAd_RxIndication() and before analyzing or forwarding of any message data, SoAd shall */
                /* (a) overwrite the remote address parts specified with wildcards (e.g. remote IP address set to TCPIP_IPADDR_ANY) with the related source */
                /*     address parts of the received message and */
                /* (b) change the state of the socket connection to SOAD_SOCON_ONLINE in case all of the following conditions are true */

                /* Change the socket state to online when the conditions of [SWS_SoAd_00592] are verified */
                lRemoteAddressOverwritten_b = SoAd_MakeUdpSocketOnline( lIdxStaticSocket_uo,
                                                                        RemoteAddrPtr );

#if ( SOAD_CONFIG_NUM_OF_UDP_SUPERVISION_TIMEOUT > 0U )
                /* --------------------------------------------- */
                /* Udp Supervision timeout                       */
                /* --------------------------------------------- */

                /* Get static socket Group configuration pointers */
                lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo]);

                /* [SWS_SoAd_00694] */
                /* If a UDP socket connection is configured with a SoAdSocketUdpAliveSupervisionTimeout and the remote address was overwritten, as described in [SWS_SoAd_00592] */
                /* and the alive supervision timer for this socket connection shall be started with the value specified by the configuration parameter SoAdSocketUdpAliveSupervisionTimeout */
                /* and every further reception from the same remote node shall reset the timer back to the initial value at SoAd_RxIndication()     */

                if( (NULL_PTR != lSoAdStaticSoConGrpConfig_cpst->udpProtocolConf_cpst)                                                                          &&
                    (SOAD_CFG_UDPALIVESUPERVISION_DEFAULT_VALUE != lSoAdStaticSoConGrpConfig_cpst->udpProtocolConf_cpst->udpAliveSupervisionTimeoutIdx_uo)      &&
                    ((TRUE == lRemoteAddressOverwritten_b)                                   ||
                     ((0xFFFFFFFFU > lSoAdDyncSocConfig_pst->UdpAliveSupervisionTimer_u32 )  &&
                      (0U < lSoAdDyncSocConfig_pst->UdpAliveSupervisionTimer_u32))) )
                {
                    /* Load the configured UdpAliveSuperVision timeout value into the dynamic socket structure */
                    lSoAdDyncSocConfig_pst->UdpAliveSupervisionTimer_u32 = \
                            SoAd_CurrConfig_cpst->SoAd_Config_UdpAliveSupervisionTimeOut_cpu32 \
                                [lSoAdStaticSoConGrpConfig_cpst->udpProtocolConf_cpst->udpAliveSupervisionTimeoutIdx_uo];
                }
#endif
#endif

                /* --------------------------------------------- */
                /* Process received message                      */
                /* --------------------------------------------- */

                /* Process the received message further */
                lDataForwrdedToUl_b = SoAd_ProcessRcvdMessage( lIdxStaticSocket_uo,
                                                               BufPtr,
                                                               Length );

                /* --------------------------------------------- */
                /* Reconnect in case no valid PDU forwarded      */
                /* --------------------------------------------- */

                /* [SWS_SoAd_00710] */
                /* In case no valid PDU data was forwarded to an upper layer and the remote address of the socket connection was overwritten */
                /* according to [SWS_SoAd_00592] in context of the same SoAd_RxIndication(), SoAd shall revert the remote address change and set the state of */
                /* the socket connection back to SOAD_SOCON_RECONNECT. */

                /* If no data has been forwrded to the UL and reomte address was overwritten */
                if( ( FALSE == lDataForwrdedToUl_b ) && ( TRUE == lRemoteAddressOverwritten_b ) )
                {
#if ( SOAD_CONFIG_NUM_OF_UDP_SUPERVISION_TIMEOUT > 0U )
                    /* Reset the configured UdpAliveSuperVision timeout value into the dynamic socket structure */
                    lSoAdDyncSocConfig_pst->UdpAliveSupervisionTimer_u32 = 0xFFFFFFFFU;
#endif

                    /* Set the connection request state to reconnect such that it shall be tried in next main function */
                    lSoAdDyncSocConfig_pst->socConSubMode_en = SOAD_SOCON_BOUND;

                    SOAD_COPY_REMOTE_ADDR_FROM_STATIC_SOC_CONFIG_TO_DYNC_SOC_CONFIG( ((const SoAd_StaticSocConfigType_tst *) &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo])), lSoAdDyncSocConfig_pst)

                    /* Call a function which shall invoke the upper layer call back for mode change */
                    SoAd_ModeChgCallbackToUl( lIdxStaticSocket_uo, lIdxDynSocket_uo, SOAD_SOCON_RECONNECT );
                }
            }
        }
    }

    return;
}

/**************************************************************************************************************************************/
/** SoAd_IdentifySocketRouteSocket() - This function shall determine the SoAd static socket index corresponding the the TcpIp socket **/
/**                                    id given in argument                                                                          **/
/**                                                                                                                                  **/
/** Parameters (in):                                                                                                                 **/
/** TcpIpSocketId_uo            - TcpIp socket id for which the SoAd socket should be found                                          **/
/** RemoteAddrPtr_cpst          - Pointer to memory containing IP address and port of the remote host which sent the data            **/
/** Buffer_cpu8                 - Rx buffer received from TcpIp                                                                      **/
/** Length_u16                  - Length of the Rx Buffer                                                                            **/
/**                                                                                                                                  **/
/** Parameters (inout):         None                                                                                                 **/
/**                                                                                                                                  **/
/** Parameters (out):                                                                                                                **/
/** StaticSocketId_puo          - Identified static socket id                                                                        **/
/**                                                                                                                                  **/
/** Return value:               - Std_ReturnType                                                                                     **/
/**                                 E_OK: SoAd socket has been identified                                                            **/
/**                                 E_NOT_OK: SoAd socket has not been identified                                                    **/
/**                                                                                                                                  **/
/**************************************************************************************************************************************/
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_IdentifySocketRouteSocket (  VAR( TcpIp_SocketIdType, AUTOMATIC )                TcpIpSocketId_uo,
                                                                           P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC ) RemoteAddrPtr_cpst,
                                                                           P2CONST( uint8, AUTOMATIC, AUTOMATIC )              Buffer_cpu8,
                                                                           VAR( uint16, AUTOMATIC )                            Length_u16,
                                                                           P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )     StaticSocketId_puo )
{
    /* Declare local variables */
    VAR(SoAd_SoConIdType, AUTOMATIC)        lIdxStaticSocket_uo;
    VAR(SoAd_SoConIdType, AUTOMATIC)        lIdxDynSocket_uo;
    VAR( Std_ReturnType, AUTOMATIC )        lFunctionRetVal_en;
    VAR(boolean, AUTOMATIC)                 lRxHeaderstatus_b;
#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
    VAR(SoAd_SoConIdType, AUTOMATIC)        lIdxSoConGroup_uo;
    VAR(uint32, AUTOMATIC)                  lRxHeaderExtracted_32;
    VAR(boolean, AUTOMATIC)                 lSocketMatchForUdpGrp_b;
#endif

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en      = E_NOT_OK;

#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
    /* Initialize the extracted header to 0 */
	lRxHeaderExtracted_32   = 0;
#endif

    /* [SWS_SoAd_00562] */
    /* For the reception of a message from an UDP or TCP socket and forwarding of the received data as PDU to the related upper layer the SoAd shall */
    /* (1) Identify the related socket connection and socket routes by using the SocketId provided at SoAd_RxIndication() */

    /* Get the index of dynamic config table from the given SocketId by using array */
    lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo];

    if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
    {
#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
		/* --------------------------------------------- */
		/* Case of Udp multi socket                      */
		/* --------------------------------------------- */

        /* Reset the lSocketMatchForUdpGrp_b to FALSE as default value */
        lSocketMatchForUdpGrp_b = FALSE;

        /* Condition Check: TcpIp socket is is fall in the UDP range, As per the TcpIp design TCP socket id will
         * be in the range of 0 to TCPIP_TCPSOCKETMAX abd UDP socket id will be in the range of TCPIP_TCPSOCKETMAX to TCPIP_SOCKETMAX */
        if( TCPIP_TCPSOCKETMAX <= TcpIpSocketId_uo )
        {
            /* Get the static socket index from dynamic socket table */
            lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo;

            /* Get the static group socket index from static socket table */
            lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo ;

            /* Check if it is UDP Group socket, If so get the group id belongs to the static socket and apply best match algorithm
             * to get the best matched socket as per autosar
             */
            if( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].maxSoConChannel_uo > 1U ) &&  \
                ( TCPIP_IPPROTO_UDP == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].soConGrpProtocol_en ) )
            {
                /* Set the lSocketMatchForUdpGrp_b to TRUE to identify Tcpip socket id is belongs to UDP group socket */
                lSocketMatchForUdpGrp_b = TRUE;

                /* Get the status of Header whether it is enabled or disabled*/
                lRxHeaderstatus_b = ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].headerEnable_b );

                /* Check Rx Frame Length as passed in parameter is atleast greater than the Pdu header length*/
                if( ( lRxHeaderstatus_b != FALSE ) && ( Length_u16 >= SOAD_PDUHDR_SIZE ) )
                {
                    /* Reading Pdu Id from Ethernet header which shall be used for de-multiplexing and finding out Pdu owner*/
                    /* converting the data from Big Endian to controller specific Endianness*/
                    lRxHeaderExtracted_32 = (Buffer_cpu8[3]) |(((uint32)Buffer_cpu8[2])<<8u) |\
                                                                (((uint32)Buffer_cpu8[1])<<16u) |(((uint32)Buffer_cpu8[0])<<24u);
                }

                /* [SWS_SoAd_00657] */
                /* In case more than one socket connection belongs to a UDP socket connection group, a UDP socket is shared between all socket */
                /* connections of the group and the related socket connection shall be selected according to the best match algorithm (see [SWS_SoAd_00680]). */

                /* Get the socket id with the help of best match algorithm */
                lFunctionRetVal_en = SoAd_BestMatchAlgorithm( SOAD_CFG_SOCON_ID_DEFAULT_VALUE,
                                                              lIdxSoConGroup_uo,
                                                              lRxHeaderExtracted_32,
                                                              RemoteAddrPtr_cpst,
                                                              StaticSocketId_puo );
            }
        }

        if( FALSE == lSocketMatchForUdpGrp_b )
#endif
        {

            /* ------------------------------------------------------ */
            /* Case of Tcp client/server sockets or Udp single socket */
            /* ------------------------------------------------------ */

            /* The socket id given by TcpIp layer is not matched with Tcp Server sockets, Udp group sockets. */
            /* So, it can be a part of either Tcp client socket or Udp single socket. */

            /* Set the static socket index as out argument of the function */
            (*StaticSocketId_puo) = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo;

            /* SoAd socket is found so return E_OK */
            lFunctionRetVal_en = E_OK;
        }
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** SoAd_MsgAcceptancePolicy()  - This function shall check whether received message (TCP connections or UDP datagrams) shall   **/
/**                             be accepted according to the messsage acceptance policy from remote nodes with an remote        **/
/**                             address that matches the remote address specified in the socket connection                      **/
/**                             id given in argument                                                                            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** RemoteAddrPtr_pst           - Pointer to memory containing IP address and port of the remote host which sent the data       **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - Std_ReturnType                                                                                **/
/**                                 E_OK: Received message is accepted according to the message acceptance policy               **/
/**                                 E_NOT_OK: Received message isn't accepted according to the message acceptance policy        **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_MsgAcceptancePolicy ( VAR( SoAd_SoConIdType, AUTOMATIC )                      StaticSocketId_uo,
                                                                    P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )     RemoteAddrPtr_cpst )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_DyncSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdDyncSocConfig_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;
    VAR(Std_ReturnType, AUTOMATIC)                                  lFunctionRetVal_en;

    /* Variable to store if two IP addresses are equal */
    VAR(boolean, AUTOMATIC)                                         lAreIpAddrEqual_b;

    /* Variable to store if the remote address of dynamic socket is wildcard (ANY)  */
    VAR(boolean, AUTOMATIC)                                         lDyncSocConfigHasWildcardAnyAddr_b;

    /* Variable to store the port for dynamic socket */
    VAR(uint16, AUTOMATIC)                                          lDyncSocPort_u16;

    /* Variable to store the port for remote address */
    VAR(uint16, AUTOMATIC)                                          lRemoteAddrPort_u16;


    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo);

    /* Get dynamic socket configuration pointers */
    lSoAdDyncSocConfig_pst = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

    /* [SWS_SoAd_00524] */
    /* If SoAdSocketMsgAcceptanceFilterEnabled is TRUE, SoAd shall only accept TCP connections or UDP datagrams from remote nodes with a source address that */
    /* matches the remote address specified in the socket connection (either via configuration parameters SoAdSocketRemoteIpAddress and SoAdSocketRemotePort */
    /* or set online with SoAd_SetRemoteAddr() API). */

    /* -------------------- */
    /* Udp socket           */
    /* -------------------- */

    /* Socket Group Protocol is UDP */
    if ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_UDP )
    {
        /* Message acceptance policy is done on reception of UDP message */
#if (SOAD_MSG_ACCEPT_POLICY_ENABLED != STD_OFF)
        /* Check if the MsgAcceptedFilter is TRUE for static group id */
        if  (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].socMsgAcceptanceFiletEnable_b == TRUE )
        {
            /* [SWS_SoAd_00525] */
            /* A remote address matches if both IP address and port match. The IP addresses match if they are identical or if the specified IP address is set to */
            /* TCPIP_IPADDR_ANY (TCPIP_IP6ADDR_ANY). The port matches if they are identical or if the specified port is set to TCPIP_PORT_ANY. */

			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            lAreIpAddrEqual_b                  = SOAD_SOCK_IPADDR_IS_EQUAL_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR(RemoteAddrPtr_cpst, lSoAdDyncSocConfig_pst);
            lDyncSocConfigHasWildcardAnyAddr_b = SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR(lSoAdDyncSocConfig_pst);
			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            lRemoteAddrPort_u16                = SOAD_GET_PORT_FROM_SOCK_ADDR(RemoteAddrPtr_cpst);
            lDyncSocPort_u16                   = SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG(lSoAdDyncSocConfig_pst);

            /* When remote address equal to wildcard or message remote address */
            if ( ( lAreIpAddrEqual_b || lDyncSocConfigHasWildcardAnyAddr_b) &&
                 ( ( lRemoteAddrPort_u16 == lDyncSocPort_u16)   ||
                   ( TCPIP_PORT_ANY == lDyncSocPort_u16 ) ) )
            {
                /* Set the return value of the function to E_OK */
                lFunctionRetVal_en = E_OK;
            }
        }
        /* Message acceptance filter is disabled */
        else
#endif
        {
            /* [SWS_SoAd_00635] */
            /* If SoAdSocketMsgAcceptanceFilterEnabled is FALSE, SoAd shall accept all UDP datagrams from remote nodes. */

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;
        }
    }

    /* -------------------- */
    /* Tcp socket           */
    /* -------------------- */

    /* Socket Group Protocol is TCP */
    else
    {
        /* Message acceptance policy does not apply on the reception of Tcp data segments */
        lFunctionRetVal_en = E_OK;
    }

#ifdef SOAD_DEBUG_AND_TEST
    SoAd_MsgAccept_tst = (uint8)lFunctionRetVal_en;
#endif
    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** SoAd_MakeUdpSocketOnline()  - This function is used to put the Udp socket online according to SWS_SoAd_00592                **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** RemoteAddrPtr_cpst          - Pointer to memory containing IP address and port of the remote host which sent the data       **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - Boolean                                                                                       **/
/**                                 TRUE: Remote address of the socket has been overwritten                                     **/
/**                                 FALSE: Remote address of the socket has not been overwritten                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if (SOAD_UDP_PRESENT != STD_OFF)
static FUNC( boolean, SOAD_CODE ) SoAd_MakeUdpSocketOnline (    VAR( SoAd_SoConIdType, AUTOMATIC )                      StaticSocketId_uo,
                                                                P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )     RemoteAddrPtr_cpst )
{

    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_DyncSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdDyncSocConfig_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;
    VAR( boolean, AUTOMATIC )                                       lRemoteAddressOverwritten_b;

#if (SOAD_TP_PRESENT != STD_OFF)
    VAR(PduIdType, AUTOMATIC)                                       lIdxRxPdu_uo;
#endif /* (SOAD_TP_PRESENT != STD_OFF) */

    VAR(boolean, AUTOMATIC)                                         lDyncSocConfigHasWildcardAnyAddr_b;
    VAR(uint16, AUTOMATIC)                                          lDyncSocPort_u16;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo);

    /* Get dynamic socket configuration pointers */
    lSoAdDyncSocConfig_pst = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

    /* Initialize the flag indicating if the remote address has been overwritten to FALSE */
    lRemoteAddressOverwritten_b = FALSE;

    /* Read remote address in dynamic socket */
	lDyncSocConfigHasWildcardAnyAddr_b = SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR(lSoAdDyncSocConfig_pst);
	lDyncSocPort_u16                   = SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG(lSoAdDyncSocConfig_pst);

    /* --------------------------------------------- */
    /* Modify remote address                         */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00592] */
    /* Within SoAd_RxIndication() and before analyzing or forwarding of any message data, SoAd shall */
    /* (a) overwrite the remote address parts specified with wildcards (e.g. remote IP address set to TCPIP_IPADDR_ANY) with the related source */
    /*     address parts of the received message and */

    /* Modify the Remote Ip address, if remote Ip address contains wildcard*/
    if ( TRUE == lDyncSocConfigHasWildcardAnyAddr_b )
    {
        /* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
        SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR(RemoteAddrPtr_cpst, lSoAdDyncSocConfig_pst)

        /* Set a flag to remember that remote address has been overwritten in the dynamic socket */
        lRemoteAddressOverwritten_b = TRUE;
    }

    /* Modify the Remote port address, if remote port address contains wildcard*/
    if ( TCPIP_PORT_ANY == lDyncSocPort_u16 )
    {
        /* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
        SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_PORT(RemoteAddrPtr_cpst, lSoAdDyncSocConfig_pst)

        /* Set a flag to remember that remote address has been overwritten in the dynamic socket */
        lRemoteAddressOverwritten_b = TRUE;
    }

    /* --------------------------------------------- */
    /* Change socket state                           */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00592] */
    /* Within SoAd_RxIndication() and before analyzing or forwarding of any message data, SoAd shall */
    /* (b) change the state of the socket connection to SOAD_SOCON_ONLINE */
    /* in case all of the following conditions are true */
    /* (1) Current connection state is not SOAD_SOCON_ONLINE */
    /* (2) UDP socket */
    /* (3) SoAdSocketUdpListenOnly is set to FALSE (Socket state goes to online even if SoAdSocketUdpListenOnly is True to avoid packet drop in below cases:*/
    /*     SoAd_SetRemoteAddr( ) with Wildcard address - Socket shall goes to RECONNECT state*/
    /*     SoAd_RxIndication( ) for the same socket - Packet could be dropped since socket is not ONLINE) */
    /* (4) SoAdSocketMsgAcceptanceFilterEnabled is set to TRUE */
    /* (5) Remote address is set, but contains wildcards */
    /* (6) Received message is accepted according to the message acceptance policy */

    if( (( SOAD_SOCON_RECONNECT == lSoAdDyncSocConfig_pst->socConMode_en ) && ( SOAD_SOCON_BOUND == lSoAdDyncSocConfig_pst->socConSubMode_en ))             &&
        (TCPIP_IPPROTO_UDP == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en)           &&
        (TRUE == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].socMsgAcceptanceFiletEnable_b)              &&
        ((TRUE == lDyncSocConfigHasWildcardAnyAddr_b) || (TCPIP_PORT_ANY == lDyncSocPort_u16)) )
    {
        /* Change the state of the socket connection to SOAD_SOCON_ACTIVE */
        lSoAdDyncSocConfig_pst->socConSubMode_en = SOAD_SOCON_ACTIVE;

        /* Call a function which shall invoke the upper layer call back for mode change */
        SoAd_ModeChgCallbackToUl( StaticSocketId_uo, lIdxDynSocket_uo, SOAD_SOCON_ONLINE );

#if (SOAD_TP_PRESENT != STD_OFF)
        /* If header is not enabled for the socket connection group, call the UL startOfReception as per SWS_SoAd_00595*/
        /* start of reception shall be called for upper layer of a socket only if the type is TP */
        if( (FALSE == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].soConGrpId_uo].headerEnable_b) && \
            ( 1U == SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].numberOfRxPdusConfigured_u8 ) )
        {
            /* get the first RxPduId mapped to socket */
            lIdxRxPdu_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].rxPduIds_pcuo[0];

            if( SOAD_TP == SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lIdxRxPdu_uo].rxUpperLayerType_en )
            {
                /* call start of reception related to all Rx pdus*/
                SoAd_InformTpStartOfReception(StaticSocketId_uo, lIdxRxPdu_uo);
            }
        }
#endif
    }

    return lRemoteAddressOverwritten_b;
}
#endif /* SOAD_UDP_PRESENT != STD_OFF */


/*********************************************************************************************************************************/
/** SoAd_ProcessRcvdMessage()   - This function execute the processing of a received message (loop through all Pdus packed in   **/
/**                             the received message)                                                                           **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** MessagePtr_pu8              - Pointer to beginning of the received message                                                  **/
/** MessageLength_u16           - Length in bytes of the received message                                                       **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - Boolean                                                                                       **/
/**                                 TRUE: All data or a part of the data have been forwarded to the Upper Layer                 **/
/**                                 FALSE: No data have been Forwarded to the Upper Layer                                       **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( boolean, SOAD_CODE ) SoAd_ProcessRcvdMessage ( VAR( SoAd_SoConIdType, AUTOMATIC )      StaticSocketId_uo,
                                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    MessagePtr_pu8,
                                                            VAR( uint16, AUTOMATIC )                MessageLength_u16 )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_DyncSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdDyncSocConfig_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;
    VAR( SoAd_RxPduDesc_tst, AUTOMATIC )                            lRxPduDesc_st;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )                            lMessageCurrentPointer_pu8;
    VAR( uint16, AUTOMATIC )                                        lMessageParsedLength_u16;
    VAR( uint16, AUTOMATIC )                                        lDiscardedLength_u16;
    VAR( uint8, AUTOMATIC )                                         lPresentHeaderLength_u8;
    VAR( uint16, AUTOMATIC )                                        lCopiedDataToUl_u16;
    VAR( boolean, AUTOMATIC )                                       lDataForwrdedToUl_b;

    /* Initialization of local variables declared above */
    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo);

    /* Get dynamic socket configuration pointers */
    lSoAdDyncSocConfig_pst = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

    /* Initialize the flag indicating of data have been forwarded to the Upper Layer to FALSE */
    lDataForwrdedToUl_b = FALSE;

    /* --------------------------------------------- */
    /* Initialize message pointer and parsed length  */
    /* --------------------------------------------- */

    /* Initialize variables before processing Pdu packed inside the message */
    lMessageCurrentPointer_pu8 = MessagePtr_pu8;
    lMessageParsedLength_u16 = 0U;


    /* --------------------------------------------- */
    /* Remaining length to be discarded              */
    /* --------------------------------------------- */
#if (SOAD_TCP_PRESENT != STD_OFF)
    /* Check if upper layer type is TCP */
    if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP) &&
        (lSoAdDyncSocConfig_pst->rxTcpRemainingPduLengthToDicard_u32 > 0U) )
    {
        /* Discard if there is remaining length to be discarded from a previous Pdu */
        lDiscardedLength_u16 = SoAd_DiscardPdu( StaticSocketId_uo,
                                                lSoAdDyncSocConfig_pst->rxTcpRemainingPduLengthToDicard_u32,
                                                MessageLength_u16 );

        /* Increment message pointer by the discarded length */
        lMessageCurrentPointer_pu8 += lDiscardedLength_u16;
        lMessageParsedLength_u16 += lDiscardedLength_u16;
    }
#endif


    /* --------------------------------------------- */
    /* Process PDUs within the message               */
    /* --------------------------------------------- */

    /* While there are Pdus to process inside the message */
    while( lMessageParsedLength_u16 < MessageLength_u16 )
    {
        /* --------------------------------------------- */
        /* Initialize Rx Pdu desc                        */
        /* --------------------------------------------- */
        lRxPduDesc_st.PduDataLength_u32 = (uint32)( MessageLength_u16 - lMessageParsedLength_u16 );
        lRxPduDesc_st.RxPduId_uo = 0U;


        /* --------------------------------------------- */
        /* Initialize loop variables                     */
        /* --------------------------------------------- */
        lPduAcceptance_en = SOAD_PDU_DISCARD;
        lPresentHeaderLength_u8 = 0U;
        lCopiedDataToUl_u16 = 0U;


        /* --------------------------------------------- */
        /* Convert message into Pdu                      */
        /* --------------------------------------------- */

        /* Step (3) of [SWS_SoAd_00562] */
        /* For the reception of a message from an UDP or TCP socket and forwarding of the received data as PDU to the related upper layer the SoAd shall */
        /* (3) Convert the message into a PDU */

        /* Call a function to extract the current Pdu */
        /* (if Pdu header is present and completely processed by SoAd (header not fragmented and not saved in buffer), then processed length will be set to SOAD_PDUHDR_SIZE) */
        lPduAcceptance_en = SoAd_ConvertMessageToPdu( StaticSocketId_uo,
                                                      lMessageCurrentPointer_pu8,
                                                      (MessageLength_u16 - lMessageParsedLength_u16),
                                                      &lRxPduDesc_st,
                                                      &lPresentHeaderLength_u8 );

        /* Set the current pointer after the present Pdu header length */
        lMessageCurrentPointer_pu8 += lPresentHeaderLength_u8;
        lMessageParsedLength_u16 += lPresentHeaderLength_u8;

        /* If the Pdu is accepted for further processing (complete Pdu data is present or Pdu data is fragmented) */
        if( (lPduAcceptance_en == SOAD_PDU_OK) || (lPduAcceptance_en == SOAD_PDU_FRAGMENTED_DATA) )
        {
            /* --------------------------------------------- */
            /* Check socket state                            */
            /* --------------------------------------------- */

            /* If the socket is active and not requested to be closed (by UL or SoAd) */
            if( (lSoAdDyncSocConfig_pst->socConSubMode_en == SOAD_SOCON_ACTIVE) &&
                (lSoAdDyncSocConfig_pst->discardNewTxRxReq_b == FALSE) )
            {
                /* --------------------------------------------- */
                /* Check if Pdu length is valid                  */
                /* --------------------------------------------- */

                /* Step (4) of [SWS_SoAd_00562] */
                /* For the reception of a message from an UDP or TCP socket and forwarding of the received data as PDU to the related upper layer the SoAd shall */
                /* (4) Skip further processing if PDU length is 0 and (SoAdPduHeaderEnable is FALSE or SoAdRxUpperLayerType is TP) */

                /* Check if the Pdu length is invalid */
                if ( (lRxPduDesc_st.PduDataLength_u32 == 0U)    &&
                     ((SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == FALSE) || (SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lRxPduDesc_st.RxPduId_uo].rxUpperLayerType_en == SOAD_TP)) )
                {
                    /* Raise DET Error */
                    /* To notify about Length error in PDU */
                    SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_INV_ARG )

                    /* Discard Pdu when length does not pass */
                    lPduAcceptance_en = SOAD_PDU_DISCARD;
                }

                /* If the Pdu length is valid */
                else
                {
                    /* --------------------------------------------- */
                    /* Process Pdu data (complete or fragment)       */
                    /* --------------------------------------------- */

                    /* Step (5) of [SWS_SoAd_00562] */
                    /* For the reception of a message from an UDP or TCP socket and forwarding of the received data as PDU to the related upper layer the SoAd shall */
                    /* (5) Call the upper layer type related reception functions of the configured upper layer module depending on the SoAdRxUpperLayerType specified */
                    /*     in SocketRouteDest configuration */

                    /* Execute the Pdu data processing (IF / TP) */
                    lPduAcceptance_en = SoAd_ProcessPduData( StaticSocketId_uo,
                                                             lMessageCurrentPointer_pu8,
                                                             (MessageLength_u16 - lMessageParsedLength_u16),
                                                             lRxPduDesc_st,
                                                             &lCopiedDataToUl_u16 );
                }
            }
            else
            {
                /* Discard Pdu when close is requested */
                lPduAcceptance_en = SOAD_PDU_DISCARD;
            }
        }


        /* --------------------------------------------- */
        /* Check Pdu acceptance                          */
        /* --------------------------------------------- */
        switch(lPduAcceptance_en)
        {
            /* In case the current Pdu was fully present or Pdu data fragmented */
            case SOAD_PDU_OK:
            case SOAD_PDU_FRAGMENTED_DATA:
            {
                /* If some data have been forwarded to the Upper Layer */
                if( lCopiedDataToUl_u16 > 0U )
                {
                    /* Set a flag to remember that some data have been forwrded to the UL */
                    lDataForwrdedToUl_b = TRUE;

#if (SOAD_TCP_PRESENT != STD_OFF)
                    /* --------------------------------------------- */
                    /* Confirm TCP reception (UL data)               */
                    /* --------------------------------------------- */

                    /* [SWS_SoAd_00564] */
                    /* In case of a TCP socket connection the SoAd shall confirm the reception of all data either forwarded to the upper layer or finally handled */
                    /* by SoAd (e.g. discarded data or processed PDU Header) by calling TcpIp_TcpReceived() within SoAd_RxIndication() or SoAd_MainFunction() respectively. */

                    /* Check if upper layer type is TCP */
                    if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP )
                    {
                        /* The reception of socket data is confirmed to the TCP/IP stack */
                        (void)TcpIp_TcpReceived( SoAd_DyncSocConfig_ast[(*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo)].socketHandleTcpIp_uo,
                                                 lCopiedDataToUl_u16 );
                    }
#endif
                }

                /* Increment the current pointer after the current Pdu data to go to the next Pdu in the message */
                lMessageCurrentPointer_pu8 += ( ((uint32)(MessageLength_u16 - lMessageParsedLength_u16) < lRxPduDesc_st.PduDataLength_u32)? (MessageLength_u16 - lMessageParsedLength_u16) : (uint16)(lRxPduDesc_st.PduDataLength_u32) );
                lMessageParsedLength_u16 +=  ( ((uint32)(MessageLength_u16 - lMessageParsedLength_u16) < lRxPduDesc_st.PduDataLength_u32)? (MessageLength_u16 - lMessageParsedLength_u16) : (uint16)(lRxPduDesc_st.PduDataLength_u32) );
            }
            break;

            /* In case the current Pdu header is fragmented */
            case SOAD_PDU_FRAGMENTED_HEADER:
            {
                /* Nothing to do */
                /* (message pointer and message parsed length already incremented) */
            }
            break;

            /* In case the current Pdu is discarded */
            case SOAD_PDU_DISCARD:
            default:
            {
                /* Request the discarding of the Pdu */
                lDiscardedLength_u16 = SoAd_DiscardPdu( StaticSocketId_uo,
                                                        lRxPduDesc_st.PduDataLength_u32,
                                                        (MessageLength_u16 - lMessageParsedLength_u16) );

                /* Increment the current pointer after the discarded length */
                lMessageCurrentPointer_pu8 += lDiscardedLength_u16;
                lMessageParsedLength_u16 += lDiscardedLength_u16;
            }
            break;
        }
    }

    return lDataForwrdedToUl_b;
}


/*********************************************************************************************************************************/
/** SoAd_DiscardPdu()           - This function discard a Pdu                                                                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** TotalPduDataLength_u32      - Total Pdu data length of the Pdu that need to be discarded                                    **/
/** RemainingLength_u16         - Remaining length in the message                                                               **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):           None                                                                                            **/
/**                                                                                                                             **/
/** Return value:               - Length that has been effectively discarded                                                    **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( uint16, SOAD_CODE ) SoAd_DiscardPdu (  VAR( SoAd_SoConIdType, AUTOMATIC )      StaticSocketId_uo,
                                                    VAR( uint32, AUTOMATIC )                TotalPduDataLength_u32,
                                                    VAR( uint16, AUTOMATIC )                RemainingLength_u16 )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;
    VAR(uint32, AUTOMATIC)                                          lRemainingPduDataLengthToDiscard_u32;
    VAR(uint16, AUTOMATIC)                                          lDiscardedLength_u16;
    VAR(uint16, AUTOMATIC)                                          lEffectiveDiscardLength_u16;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Initialize Pdu data length to discard */
    lRemainingPduDataLengthToDiscard_u32 = TotalPduDataLength_u32;

    /* Initialize the discarded length to 0 */
    lDiscardedLength_u16 = 0U;

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    /* ------------------------------------- */
    /* Discard fragments in Rx buffer        */
    /* ------------------------------------- */

    /* If Rx buffer is configured */
    if( SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].dynRxBuffTableEntry_pst != NULL_PTR )
    {
        /* Clear fragmented header from Rx buffer */
        SoAd_ClearFragmentedHeaderFromRxBuffer( StaticSocketId_uo );

        /* Clear fragmented data from Rx buffer and update remaining Pdu data length to discard accordingly */
        lDiscardedLength_u16 = SoAd_ClearFragmentedDataFromRxBuffer( StaticSocketId_uo, &lRemainingPduDataLengthToDiscard_u32 );
    }
#endif


    /* --------------------------------------------- */
    /* Compute effective discard length              */
    /* --------------------------------------------- */

    /* If remaining length to discard is lower or equal to the the remaining length in the message */
    if( lRemainingPduDataLengthToDiscard_u32 <= (uint32)(RemainingLength_u16) )
    {
        /* Complete remaining Pdu length can be discarded */
        /* (the complete remaining Pdu length is contained in the message itself) */
        lEffectiveDiscardLength_u16 = (uint16)( lRemainingPduDataLengthToDiscard_u32 );
    }
    else
    {
        /* Only remaining length in the message can be discarded */
        lEffectiveDiscardLength_u16 = RemainingLength_u16;
    }


#if (SOAD_TCP_PRESENT != STD_OFF)
    /* --------------------------------------------- */
    /* Save remaining length to discard for Tcp      */
    /* --------------------------------------------- */

    /* If we are in case of Tcp, we need to remember how many byte still need to be discarded */
    /* (fragmentation can occur for Tcp but not Udp and if there is fragmentation the following fragments of the current Pdu to discard need to be discarded in following RxIndication) */
    if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP)   &&
        ((lRemainingPduDataLengthToDiscard_u32 - (uint32)(lEffectiveDiscardLength_u16)) > 0U) )
    {
        /* Save remaining length to be discarded in dynamic socket */
        SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].rxTcpRemainingPduLengthToDicard_u32 = ( lRemainingPduDataLengthToDiscard_u32 - (uint32)(lEffectiveDiscardLength_u16) );
    }
#endif


#if (SOAD_TCP_PRESENT != STD_OFF)
    /* --------------------------------------------- */
    /* Confirm TCP reception (discard)               */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00564] */
    /* In case of a TCP socket connection the SoAd shall confirm the reception of all data either forwarded to the upper layer or finally handled */
    /* by SoAd (e.g. discarded data or processed PDU Header) by calling TcpIp_TcpReceived() within SoAd_RxIndication() or SoAd_MainFunction() respectively. */

    /* Check if upper layer type is TCP */
    if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP )
    {
        /* The reception of socket data is confirmed to the TCP/IP stack */
        (void)TcpIp_TcpReceived(    SoAd_DyncSocConfig_ast[(*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo)].socketHandleTcpIp_uo,
                                    (uint16)(lDiscardedLength_u16 + lEffectiveDiscardLength_u16) );
    }
#endif

    return lEffectiveDiscardLength_u16;
}


/*********************************************************************************************************************************/
/** SoAd_ConvertMessageToPdu()  - This function convert the current part of the received message into a Pdu as per              **/
/**                             [SWS_SoAd_00562]                                                                                **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** CurrentPointer_pu8          - Pointer to the received message from which it is needed to extract Pdu                        **/
/** RemainingLength_u16         - Length in bytes of the remaining part of the received message                                 **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** RxPduDesc_pst               - Detected Pdu description                                                                      **/
/** PresentHeaderLength_pu8     - Present header length                                                                         **/
/**                                                                                                                             **/
/** Return value:               - SoAd_RxPduAcceptance_ten                                                                      **/
/**                                 SOAD_PDU_OK: The Pdu is valid for further processing                                        **/
/**                                 SOAD_PDU_FRAGMENTED_HEADER: Received Pdu header is fragmented                               **/
/**                                 SOAD_PDU_DISCARD: The Pdu need to be discarded                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ConvertMessageToPdu ( VAR( SoAd_SoConIdType, AUTOMATIC )                StaticSocketId_uo,
                                                                              P2CONST( uint8, AUTOMATIC, AUTOMATIC )            CurrentPointer_cpu8,
                                                                              VAR( uint16, AUTOMATIC )                          RemainingLength_u16,
                                                                              P2VAR( SoAd_RxPduDesc_tst, AUTOMATIC, AUTOMATIC ) RxPduDesc_pst,
                                                                              P2VAR( uint8, AUTOMATIC, AUTOMATIC )              PresentHeaderLength_pu8 )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;
    VAR( uint32, AUTOMATIC )                                        lPduHeaderId_u32;
    VAR( uint32, AUTOMATIC )                                        lPduDataLength_u32;
    VAR( uint16, AUTOMATIC )                                        lRemainingAndPresentLength_u16;
    VAR( PduIdType, AUTOMATIC )                                     lRxPduId_uo;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
    VAR( boolean, AUTOMATIC )                                       lHeaderEnableFlag_b;
#if (SOAD_TCP_PRESENT != STD_OFF)
    VAR( boolean, AUTOMATIC )                                       lHeaderSavedInBuff_b;
#endif

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Initialize the Pdu acceptance flag to DISCARD */
    lPduAcceptance_en = SOAD_PDU_DISCARD;

    /* Get the PDU header flag enabling from socket connection Group configuration table */
    lHeaderEnableFlag_b = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b;

#if (SOAD_TCP_PRESENT != STD_OFF)
    /* Set the flag indicating if header has been saved in buffer to FALSE */
    lHeaderSavedInBuff_b = FALSE;
#endif

    /* Rx buffer and Tcp enabled (fragmentation can be handled only in that case) */
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
    /* ------------------------------------------------ */
    /* Check fragmented Pdu data reception in progress  */
    /* ------------------------------------------------ */

    /* If Rx buffer is configured and fragmented Pdu data reception is in progress in the SoAd Rx buffer */
    if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR)                            &&
        (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragReceptionInProgress_b == TRUE) )
    {
        /* Set the Rx Pdu desc in out argument of the function */
        RxPduDesc_pst->PduDataLength_u32 = lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragCurrentRxPduDesc_st.PduDataLength_u32;
        RxPduDesc_pst->RxPduId_uo = lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragCurrentRxPduDesc_st.RxPduId_uo;

        /* Set the present header length in out argument of the function */
        (*PresentHeaderLength_pu8) = 0U;

        /* The Pdu data is fragmented */
        /* (Pdu header has already been extracted in the previously received message) */
        /* (we need to terminate the reception of the fragmented data before extracting again a Pdu header) */
        lPduAcceptance_en = SOAD_PDU_FRAGMENTED_DATA;
    }

    /* No Pdu data fragmentation in progress */
    else
#endif
    {
        /* --------------------------------------------- */
        /* SoAd header disabled                          */
        /* --------------------------------------------- */

        /* [SWS_SoAd_00563] */
        /* In case PDU header option is disabled (SoAdPduHeader-Enable is FALSE) for a socket connection, SoAd shall convert the received UDP or TCP message 1:1 into a PDU within */
        /* SoAd_RxIndication(), i.e. each TCP segment and UDP message forms a separate PDU. */

        /* In case SoAd header option is disabled */

        /* Set Pdu header id to default value as no header is present */
        lPduHeaderId_u32 = 0U;

        /* Set Pdu data length to the total length of the message for header disabled case */
        lPduDataLength_u32 = (uint32)( RemainingLength_u16 );

        if( lHeaderEnableFlag_b == FALSE )
        {
            /* --------------------------------------------- */
            /* Convert UDP or TCP message 1:1                */
            /* --------------------------------------------- */

            /* Set the present header length in out argument of the function to 0 for header disabled case */
            (*PresentHeaderLength_pu8) = 0U;

            /* The Pdu is accepted for further processing */
            lPduAcceptance_en = SOAD_PDU_OK;
        }

        /* --------------------------------------------- */
        /* SoAd header enabled                           */
        /* --------------------------------------------- */

        /* [SWS_SoAd_00559] */
        /* In case PDU header option is enabled (SoAdPduHeaderEnable is TRUE) for a socket connection, SoAd shall convert the message into a PDU within */
        /* SoAd_RxIndication() according to the following: */
        /* (1) assemble the PDU Header into a SoAd receive buffer if it is fragmented in multiple TCP segments */
        /* (2) extract the PDU Header from the received message */
        /* (3) select the related socket route according to the received PDU Header ID (SoAdRxPduHeaderId); if no socket route can be found, simply discard the PDU and if development */
        /*     error detection is enabled: raise the error SOAD_E_INV_PDUHEADER_ID. */
        /* (4) use the length field of the PDU Header to identify the length of the actual PDU and the start of the next PDU to proceed with (2) until the end of the message is reached. */
        /* If the remainder is smaller than a PDU Header or the indicated length within the header SoAd shall stop processing and ignore the rest of the message. */

        /* In case SoAd header option is enabled */
        else
        {
            /* --------------------------------------------- */
            /* Assemble and extract header                   */
            /* --------------------------------------------- */

            /* Set remaining length in the message needed by SoAd_ExtractPduHeader */
            lRemainingAndPresentLength_u16 = RemainingLength_u16;

            /* Extract information from the Pdu header */
            lPduAcceptance_en = SoAd_ExtractPduHeader( StaticSocketId_uo,
                                                       CurrentPointer_cpu8,
                                                       &lRemainingAndPresentLength_u16,
                                                       &lPduHeaderId_u32,
                                                       &lPduDataLength_u32 );

            /* Set the present header length in out argument of the function now that this value has been identified */
            (*PresentHeaderLength_pu8) = (uint8)( lRemainingAndPresentLength_u16 );
        }


        /* If Pdu is valid for further processing (means the message has been converted to PDU) */
        /* (when Pdu header is enabled and Pdu is valid for further processing, that means that the complete header has been received, we can now confirm it to Tcp) */
        if( lPduAcceptance_en == SOAD_PDU_OK )
        {
            /* --------------------------------------------- */
            /* Select related socket route                   */
            /* --------------------------------------------- */

            /* Get the socket route according to the received Pdu header Id */
            lRetVal_en = SoAd_SelectRxSocketRoute( StaticSocketId_uo,
                                                   lPduHeaderId_u32,
                                                   lHeaderEnableFlag_b,
                                                   &lRxPduId_uo );

            /* In case the socket route is found */
            if( lRetVal_en == E_OK )
            {
                /* Set the out arguments of the function */
                /* (decoding of the header and selecting of the socket route is a success, Pdu is accepted for further processing) */
                RxPduDesc_pst->RxPduId_uo = lRxPduId_uo;
                RxPduDesc_pst->PduDataLength_u32 = lPduDataLength_u32;
            }

            /* In case the socket route is not found */
            else
            {
                /* Raise DET Error */
                /* To notify about the Invalid Rx Pdu Id */
                SOAD_DET_REPORT_ERROR( (lHeaderEnableFlag_b == FALSE), SOAD_RX_INDICATION_API_ID, SOAD_E_INV_PDUID )

                /* Raise DET Error */
                /* To notify about the Invalid Rx Pdu Id */
                SOAD_DET_REPORT_ERROR(  (lHeaderEnableFlag_b == TRUE), SOAD_RX_INDICATION_API_ID, SOAD_E_INV_PDUHEADER_ID )

                /* Set the Pdu acceptance flag to DISCARD */
                lPduAcceptance_en = SOAD_PDU_DISCARD;
            }

            /* --------------------------------------------- */
            /* Handle the starting of fragmented data        */
            /* --------------------------------------------- */

            /* If Pdu is valid for further processing and Pdu data is not complete in the message */
            if( (lPduAcceptance_en == SOAD_PDU_OK)   &&
                 ((uint32)(RemainingLength_u16 - (*PresentHeaderLength_pu8)) < RxPduDesc_pst->PduDataLength_u32) )
            {
                /* Rx buffer and Tcp enabled (fragmentation can be handled only in that case) */
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
                /* If Rx buffer is configured for the socket and protocol is Tcp */
                /* (saving of fragments is only possible for Tcp, order of Udp frames is not guarenteed) */
                if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR)                                            &&
                    (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP) )
                {
                    /* Start the fragmented Pdu reception in the SoAd Rx buffer */
                    lRetVal_en = SoAd_StartFragmentedDataInRxBuffer( StaticSocketId_uo, RxPduDesc_pst, &(lHeaderSavedInBuff_b) );

                    /* Set the Pdu acceptance to PDU_FRAGMENTED_DATA or PDU_DISCARD depending of the return code */
                    lPduAcceptance_en = ( (lRetVal_en == E_OK)? (SOAD_PDU_FRAGMENTED_DATA) : (SOAD_PDU_DISCARD) );
                }
                else
#endif
                {
                    /*Raise DET Error*/
                    /* To notify about Length error in PDU (reassembly is not supported for Tcp without Rx buffer and for Udp) */
                    SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_INV_ARG )

                    /* Set the Pdu acceptance flag to DISCARD */
                    lPduAcceptance_en = SOAD_PDU_DISCARD;
                }
            }

#if (SOAD_TCP_PRESENT != STD_OFF)
            /* --------------------------------------------- */
            /* Confirm TCP reception (header)                */
            /* --------------------------------------------- */

            /* [SWS_SoAd_00564] */
            /* In case of a TCP socket connection the SoAd shall confirm the reception of all data either forwarded to the upper layer or finally handled */
            /* by SoAd (e.g. discarded data or processed PDU Header) by calling TcpIp_TcpReceived() within SoAd_RxIndication() or SoAd_MainFunction() respectively. */

            /* Check if the following conditions are true */
            /* 1. Upper layer type is TCP */
            /* 3. Header is enabled and header is not saved in the SoAd Rx buffer (if header is in buffer that means that it is not processed by SoAd yet and TcpReceived shall not be called) */
            if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP)   &&
                ((lHeaderEnableFlag_b == TRUE) && (lHeaderSavedInBuff_b == FALSE)) )
            {
                /* The reception of socket data is confirmed to the TCP/IP stack */
                (void)TcpIp_TcpReceived( SoAd_DyncSocConfig_ast[(*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo)].socketHandleTcpIp_uo,
                                         SOAD_PDUHDR_SIZE );
            }
#endif
        }
    }

    return lPduAcceptance_en;
}


/*********************************************************************************************************************************/
/** SoAd_ExtractPduHeader()     - This function assemble and extract the Pdu header                                             **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** CurrentPointer_pu8          - Pointer to the received message from which it is needed to extract Pdu                        **/
/** RemainingLength_u16         - Length in bytes of the remaining part of the received message                                 **/
/**                                                                                                                             **/
/** Parameters (inout):                                                                                                         **/
/** RemainingAndPresentLength_pu16 - Length in bytes of the remaining part of the received message as in argument, present      **/
/**                                  Header length in out argument (set when SOAD_PDU_FRAGMENTED_HEADER or SOAD_PDU_OK)         **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** PduHeaderId_pu32            - Extracted Pdu header Id (set when SOAD_PDU_OK)                                                **/
/** PduDataLength_pu32          - Extracted Pdu header length (set when SOAD_PDU_OK)                                            **/
/**                                                                                                                             **/
/** Return value:               - SoAd_RxPduAcceptance_ten                                                                      **/
/**                                 SOAD_PDU_OK: The Pdu is valid for further processing                                        **/
/**                                 SOAD_PDU_FRAGMENTED_HEADER: Received Pdu header is fragmented                               **/
/**                                 SOAD_PDU_DISCARD: The Pdu need to be discarded                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ExtractPduHeader ( VAR( SoAd_SoConIdType, AUTOMATIC )                   StaticSocketId_uo,
                                                                              P2CONST( uint8, AUTOMATIC, AUTOMATIC )            CurrentPointer_cpu8,
                                                                              P2VAR( uint16, AUTOMATIC, AUTOMATIC )             RemainingAndPresentLength_pu16,
                                                                              P2VAR( uint32, AUTOMATIC, AUTOMATIC )             PduHeaderId_pu32,
                                                                              P2VAR( uint32, AUTOMATIC, AUTOMATIC )             PduDataLength_pu32 )
{
    /* Declare local variables */
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;
    VAR( SoAd_SoConIdType, AUTOMATIC )                              lIdxDynSocket_uo;
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
    P2CONST( SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC )   lSoAdStaticSocConfig_cpst;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )                            lPduHeaderPointer_pu8;
    VAR(uint8, AUTOMATIC)                                           lPresentHeaderLength_u8;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
    VAR( boolean, AUTOMATIC )                                       lErrorFlag_b;
#endif

#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);
#endif

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Initialize the Pdu acceptance flag to DISCARD */
    lPduAcceptance_en = SOAD_PDU_DISCARD;

    /* Rx buffer and Tcp enabled (fragmentation of headercan be handled only in that case) */
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )

    /* Initialize present header length */
    lPresentHeaderLength_u8 = SOAD_PDUHDR_SIZE;

    /* Initialize the error flag to FALSE */
    lErrorFlag_b = FALSE;

    /* --------------------------------------------- */
    /* Case of Tcp with Rx buffer                    */
    /* --------------------------------------------- */

    /* Check if Rx buffer is configured for the socket and protocol is Tcp */
    /* (saving of fragments is only possible for Tcp, order of Udp frames is not guarenteed) */
    if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR)    &&
        (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP) )
    {
        /* --------------------------------------------- */
        /* Save fragmented header                        */
        /* --------------------------------------------- */

        /* If there is already a fragmented header in progress in the Rx buffer */
        /* Or if there is no fragmented header in progress in the Rx buffer but the remaining length of the message is not big enough for a complete header */
        if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->HeaderFragReceptionInProgress_b == TRUE) ||
            ((lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->HeaderFragReceptionInProgress_b == FALSE) && ((*RemainingAndPresentLength_pu16) < SOAD_PDUHDR_SIZE)) )
        {
            /* Save it in SoAd Rx buffer */
            lRetVal_en = SoAd_AddFragmentedHeaderInRxBuffer( StaticSocketId_uo,
                                                             CurrentPointer_cpu8,
                                                             (*RemainingAndPresentLength_pu16),
                                                             &lPresentHeaderLength_u8 );

            /* If error occured (no space in the buffer) */
            if( lRetVal_en == E_NOT_OK )
            {
                /* When header is not complete and fragment cannot be saved then the communication cannot continue */
                /* Socket need to be closed because all the following message will be wrongly interpreted as beginning of SoAd header */

                /* Set the global variables to skip the further transmission and reception */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b = TRUE;

                /* As an error occurred, so request need to be taken to abort the socket connection */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD;

                /* Set the present header length in out argument of the function */
                (*RemainingAndPresentLength_pu16) = 0U;

                /* Set a flag to indicate that there is an error */
                lErrorFlag_b = TRUE;

                /* Remaining bytes in the message will be discarded and fragments in rx buffer deleted */
            }
        }


        /* --------------------------------------------- */
        /* Extract Pdu header if possible                */
        /* --------------------------------------------- */

        /* No error occured previously */
        if( lErrorFlag_b == FALSE )
        {
            /* If fragmentation is in progress */
            if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->HeaderFragReceptionInProgress_b == TRUE )
            {
                /* Set the present header length in out argument of the function */
                (*RemainingAndPresentLength_pu16) = lPresentHeaderLength_u8;

                /* Set the acceptance flag to indicate that the header is fragmented and not complete for the moment */
                lPduAcceptance_en = SOAD_PDU_FRAGMENTED_HEADER;
            }

            /* No fragmentation in progress */
			/* (this means we have access to the complete data) */
            else
            {
                /* Complete header is present in the Rx buffer */
                if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->HeaderFragCurrentSize_u8 == SOAD_PDUHDR_SIZE )
                {
                    /* Get complete header from Rx buffer */
                    SoAd_GetFragmentedHeaderFromRxBuffer( StaticSocketId_uo, &lPduHeaderPointer_pu8 );

                    /* Reading Pdu Id from Ethernet header which shall be used for de-multiplexing and finding out Pdu owner*/
                    /*converting the data from Big Endian to controller specific Endianness*/
                    (*PduHeaderId_pu32) = (lPduHeaderPointer_pu8[3]) | (((uint32)lPduHeaderPointer_pu8[2])<<8U) |
                                      (((uint32)lPduHeaderPointer_pu8[1])<<16U) |(((uint32)lPduHeaderPointer_pu8[0])<<24U);

                    /* Reading Pdu length from Ethernet header which shall be used for finding out Pdu length*/
                    /*converting the data from Big Endian to controller specific Endianness*/
                    (*PduDataLength_pu32) = (lPduHeaderPointer_pu8[7]) | (((uint32)lPduHeaderPointer_pu8[6])<<8U) |
                                         (((uint32)lPduHeaderPointer_pu8[5])<<16U) | (((uint32)lPduHeaderPointer_pu8[4])<<24U);

                    /* Set the present header length in out argument of the function */
                    (*RemainingAndPresentLength_pu16) = lPresentHeaderLength_u8;

                    /* Clear header from Rx buffer */
                    SoAd_ClearFragmentedHeaderFromRxBuffer( StaticSocketId_uo );

                    /* The Pdu is accepted for further processing */
                    lPduAcceptance_en = SOAD_PDU_OK;
                }

                /* If not, means complete header is present in the message itself */
                else
                {
                    /* Reading Pdu Id from Ethernet header which shall be used for de-multiplexing and finding out Pdu owner*/
                    /*converting the data from Big Endian to controller specific Endianness*/
                    (*PduHeaderId_pu32) = (CurrentPointer_cpu8[3]) | (((uint32)CurrentPointer_cpu8[2])<<8U) |
                                      (((uint32)CurrentPointer_cpu8[1])<<16U) |(((uint32)CurrentPointer_cpu8[0])<<24U);

                    /* Reading Pdu length from Ethernet header which shall be used for finding out Pdu length*/
                    /*converting the data from Big Endian to controller specific Endianness*/
                    (*PduDataLength_pu32) = (CurrentPointer_cpu8[7]) | (((uint32)CurrentPointer_cpu8[6])<<8U) |
                                         (((uint32)CurrentPointer_cpu8[5])<<16U) | (((uint32)CurrentPointer_cpu8[4])<<24U);

                    /* Set the present header length in out argument of the function */
                    (*RemainingAndPresentLength_pu16) = lPresentHeaderLength_u8;

                    /* The Pdu is accepted for further processing */
                    lPduAcceptance_en = SOAD_PDU_OK;
                }
            }
        }
    }
    else
#endif
    /* --------------------------------------------- */
    /* Case of Udp or Tcp without Rx buffer          */
    /* --------------------------------------------- */
    {
        /* --------------------------------------------- */
        /* Extract Pdu header                            */
        /* --------------------------------------------- */

        /* Check Rx Frame Length as passed in parameter is at least greater than the Pdu header length*/
        if ( (*RemainingAndPresentLength_pu16) >= SOAD_PDUHDR_SIZE )
        {
            /* Reading Pdu Id from Ethernet header which shall be used for de-multiplexing and finding out Pdu owner*/
            /*converting the data from Big Endian to controller specific Endianness*/
            (*PduHeaderId_pu32) = (CurrentPointer_cpu8[3]) | (((uint32)CurrentPointer_cpu8[2])<<8U) |
                              (((uint32)CurrentPointer_cpu8[1])<<16U) |(((uint32)CurrentPointer_cpu8[0])<<24U);

            /* Reading Pdu length from Ethernet header which shall be used for finding out Pdu length*/
            /*converting the data from Big Endian to controller specific Endianness*/
            (*PduDataLength_pu32) = (CurrentPointer_cpu8[7]) | (((uint32)CurrentPointer_cpu8[6])<<8U) |
                                 (((uint32)CurrentPointer_cpu8[5])<<16U) | (((uint32)CurrentPointer_cpu8[4])<<24U);

            /* Set the present header length in out argument of the function */
            (*RemainingAndPresentLength_pu16) = SOAD_PDUHDR_SIZE;

            /* The Pdu is accepted for further processing */
            lPduAcceptance_en = SOAD_PDU_OK;
        }

        /* Not enough bytes in the message */
        else
        {
            /* When header is not complete and fragment cannot be saved then the communication cannot continue */
            /* Socket need to be closed because all the following message will be wrongly interpreted as beginning of SoAd header */

            /*Raise DET Error*/
            /* To notify about Length error in PDU */
            SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_INV_ARG )

            /* Set the global variables to skip the further transmission and reception */
            SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b = TRUE;

            /* As an error occurred, so request need to be taken to abort the socket connection */
            SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD;

            /* Set the present header length in out argument of the function */
            (*RemainingAndPresentLength_pu16) = 0U;

            /* Remaining bytes in the message will be discarded */
        }
    }

    return lPduAcceptance_en;
}


/*********************************************************************************************************************************/
/** SoAd_SelectRxSocketRoute()  - This function convert the current part of the received message into a Pdu as per              **/
/**                             [SWS_SoAd_00562]                                                                                **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** RxHeaderId_32               - Rx Pdu Header Id to be used to find the SoAd socket route                                     **/
/** HeaderEnableFlag_b          - Header to be used to find the SoAd socket route                                               **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** RxPduId_puo                 - Found Rx socket route (Rx Pdu id)                                                             **/
/**                                                                                                                             **/
/** Return value:               - SoAd_RxPduAcceptance_ten                                                                      **/
/**                                 E_OK: The socket route has been found                                                       **/
/**                                 E_NOT_OK: The socket route has not been found or there is multiple socket routes configured **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_SelectRxSocketRoute (    VAR(SoAd_SoConIdType, AUTOMATIC)            StaticSocketId_uo,
                                                                VAR( uint32, AUTOMATIC )                    RxHeaderId_32,
                                                                VAR( boolean, AUTOMATIC )                   HeaderEnableFlag_b,
                                                                P2VAR( PduIdType, AUTOMATIC, AUTOMATIC )    RxPduId_puo )
{
    /* Declare local variables */
    P2CONST( SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC )   lSoAdStaticSocConfig_cpst;
    VAR( PduIdType, AUTOMATIC)                                      lIdxRxPdu_uo;
    VAR( Std_ReturnType, AUTOMATIC )                                lFunctionRetVal_en;
    /* Index for looping across all Rx Pdu's afor particular socket */
    VAR(PduIdType, AUTOMATIC)                                       lIdxRxPduLoop_uo ;

    /* Initialize the return value of the function to E_NOT_OK */
    lFunctionRetVal_en = E_NOT_OK;

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Loop to search the socket route */
    for( lIdxRxPduLoop_uo = 0; \
             lIdxRxPduLoop_uo < lSoAdStaticSocConfig_cpst->numberOfRxPdusConfigured_u8; \
                lIdxRxPduLoop_uo++ )
    {
        lIdxRxPdu_uo = lSoAdStaticSocConfig_cpst->rxPduIds_pcuo[lIdxRxPduLoop_uo];

        /* Condition Check:
         * The static socket id given in argument is matching with the static socket id of the current route
         * Header is disabled or header is enabled and header id is exactly matching
         */
        if( ( FALSE == HeaderEnableFlag_b ) || \
            ( SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lIdxRxPdu_uo].rxPduHeaderId_u32 == RxHeaderId_32 ) )
        {
            /* Set the found Rx Pdu Id in the out argument of the function */
            (* RxPduId_puo) = lIdxRxPdu_uo;

            /* Set the return value of the function to E_OK */
            lFunctionRetVal_en = E_OK;

            break;
        }
    }

    return lFunctionRetVal_en;
}


/*********************************************************************************************************************************/
/** SoAd_ProcessPduData()       - This function process the data contained in a received Pdu and pass it to the Upper Layer     **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** PduData_pu8                 - Pointer to memory containing Pdu data                                                         **/
/** RemainingLength_u16         - Remaining length f the message                                                                **/
/** RxPduDesc_st                - Description of the received Pdu to be handled                                                 **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** CopiedDataToUl_pu16         - Length of data that has been copied to the Upper Layer buffer                                 **/
/**                                                                                                                             **/
/** Return value:               - SoAd_RxPduAcceptance_ten                                                                      **/
/**                                 SOAD_PDU_OK: The Pdu data have been forwarded to UL                                         **/
/**                                 SOAD_PDU_FRAGMENTED_DATA: The Pdu data is fragmented, processing need to continue later     **/
/**                                 SOAD_PDU_DISCARD: The Pdu need to be discarded                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ProcessPduData (    VAR(SoAd_SoConIdType, AUTOMATIC)        StaticSocketId_uo,
                                                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    PduData_pu8,
                                                                            VAR( uint16, AUTOMATIC )                RemainingLength_u16,
                                                                            VAR( SoAd_RxPduDesc_tst, AUTOMATIC )    RxPduDesc_st,
                                                                            P2VAR( uint16, AUTOMATIC, AUTOMATIC )   CopiedDataToUl_pu16 )
{
    /* Declare local variables */
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
    VAR( boolean, AUTOMATIC)                                        lRgStatus_b;
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

#if (SOAD_TP_PRESENT != STD_OFF)
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
#endif /* SOAD_TP_PRESENT != STD_OFF */

    /* Initialize the Pdu acceptance flag to DISCARD */
    lPduAcceptance_en = SOAD_PDU_DISCARD;

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
    lRgStatus_b       = TRUE;
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

    /* --------------------------------------------- */
    /* Get routing group status                      */
    /* --------------------------------------------- */

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
    /* Check Routing Group is enabled for the fetched socket */
    lRgStatus_b = ( 0U < SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].numOfRxRoutingGroups_uo ) ? \
                            ( SoAd_GetRoutingGroupsEnabledStatus( \
                                    SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].rxRoutingGroupConf_cpuo, \
                                    SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].numOfRxRoutingGroups_uo, \
                                    StaticSocketId_uo ) ):
                                    TRUE;
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

    /* --------------------------------------------- */
    /* Reception for IF type                         */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00565] */
    /* SoAd shall process TP- and IF-PDUs independently and within each type according to the received order per socket connection. */

#if ( SOAD_IF_PRESENT != STD_OFF )
    /* If upper layer type is IF type */
    if( SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].rxUpperLayerType_en == SOAD_IF )
    {
        /* If pointers to upper layer callbacks are valid */
        if( SoAd_CurrConfig_cpst->SoAdIf_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxIfRxIndication_u8].RxCallback_pfn != NULL_PTR )
        {
            /* --------------------------------------------- */
            /* Check routing                                 */
            /* --------------------------------------------- */

            /* [SWS_SoAd_00600] */
            /* If a PDU is received according to SoAdSocketRouteDest which belongs only to inactive RoutingGroups, SoAd shall simply discard the PDU. */

            /* If the routing is possible */
            /* (for IF, header enabled: if routing is disabled, then SoAd shall discard the complete Pdu (even if the routing group is disabled between 2 fragments of the Pdu, the complete Pdu shall be discarded because for IF a Pdu is not considered as in active reception by UL)) */
            /* (for IF, header disabled: if routing is disabled then SoAd shall discard because according to [SWS_SoAd_00563] each meassge shall be considered as a Pdu) */
#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
            if( FALSE != lRgStatus_b )
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */
            {
                /* Process for IF */
                lPduAcceptance_en = SoAd_ProcessPduDataIF(
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
                                                            StaticSocketId_uo,
                                                            RemainingLength_u16,
#endif
                                                            PduData_pu8,
                                                            RxPduDesc_st,
                                                            &(*CopiedDataToUl_pu16) );
            }
        }
    }
    else
#endif

    /* --------------------------------------------- */
    /* Reception for TP type                         */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00565] */
    /* SoAd shall process TP- and IF-PDUs independently and within each type according to the received order per socket connection. */

    /* If upper layer type is IF type */
    {
#if (SOAD_TP_PRESENT != STD_OFF)

        /* Get static socket configuration pointers */
        lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

        /* -------------------- */
        /* Header disabled      */
        /* -------------------- */
        if( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == FALSE )
        {
            /* If pointers to upper layer callbacks are valid */
            if( SoAd_CurrConfig_cpst->SoAdTp_copyRxDataCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpCopyRxDataCbk_u8].soAdCopyRxDataCbk_pfn != NULL_PTR )
            {
                /* --------------------------------------------- */
                /* Check routing                                 */
                /* --------------------------------------------- */

                /* [SWS_SoAd_00600] */
                /* If a PDU is received according to SoAdSocketRouteDest which belongs only to inactive RoutingGroups, SoAd shall simply discard the PDU. */

                /* If the routing is possible */
                /* (for TP, header disabled: if routing is disabled then SoAd shall discard because according to [SWS_SoAd_00563] each meassge shall be considered as a Pdu) */
#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
                if( lRgStatus_b != FALSE )
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */
                {
                    /* Process for TP with header disabled */
                    lPduAcceptance_en = SoAd_ProcessPduDataTPHeaderDisabled(    StaticSocketId_uo,
                                                                                PduData_pu8,
                                                                                RemainingLength_u16,
                                                                                RxPduDesc_st,
                                                                                &(*CopiedDataToUl_pu16) );
                }
            }
        }

        /* -------------------- */
        /* Header enabled       */
        /* -------------------- */
        else
        {
            /* If pointers to upper layer callbacks are valid */
            if( (SoAd_CurrConfig_cpst->SoAdTp_copyRxDataCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpCopyRxDataCbk_u8].soAdCopyRxDataCbk_pfn != NULL_PTR)           &&
                (SoAd_CurrConfig_cpst->SoAdTp_StartOfReceptionCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpStartReceptionCbk_u8].StartOfReception_pfn != NULL_PTR ) &&
                (SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpRxIndication_u8].RxCallback_pfn != NULL_PTR ) )
            {
                /* --------------------------------------------- */
                /* Check routing status                          */
                /* --------------------------------------------- */

                /* [SWS_SoAd_00600] */
                /* If a PDU is received according to SoAdSocketRouteDest which belongs only to inactive RoutingGroups, SoAd shall simply discard the PDU. */

                /* Note */
                /* Activation/deactivation of a routing group only affects new PDUs, i.e. PDUs which are already in an active reception or transmission process */
                /* by an upper layer (e.g. long TP-PDU which is received via a multiple CopyRxData calls) are not affected. */

                /* If routing group is enabled or there is a TP Pdu transfer form Rx buffer to UL for which we do not have all data */
                /* (It is needed to wait for the end of the TP reception ongoing because the end of the current Pdu shall be received before the disabling of the routing can be taken into account) */
#if ( (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) || ( SOAD_RX_BUFF_ENABLE != STD_OFF ) )
                if(
#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
                   (lRgStatus_b != FALSE)
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

#if ( (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) && ( SOAD_RX_BUFF_ENABLE != STD_OFF ) )
                   ||
#endif /* (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) && ( SOAD_RX_BUFF_ENABLE != STD_OFF ) */

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
                    ((lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR)   && \
                     (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->TpDataRemainingLenToTransfer_u32 > (uint32)(lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->TpDataCurrentSize_u16 + lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragCurrentSize_u16)))
#endif /* SOAD_RX_BUFF_ENABLE != STD_OFF */
                   )
#endif /* (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF) || ( SOAD_RX_BUFF_ENABLE != STD_OFF ) */
                {
                    /* Process for TP with header enabled */
                    lPduAcceptance_en = SoAd_ProcessPduDataTPHeaderEnabled( StaticSocketId_uo,
                                                                            PduData_pu8,
                                                                            RemainingLength_u16,
                                                                            RxPduDesc_st,
                                                                            &(*CopiedDataToUl_pu16) );
                }
            }
        }
#endif
    }

    return lPduAcceptance_en;
}


/*********************************************************************************************************************************/
/** SoAd_ProcessPduDataIF()     - This function process the data contained in a received Pdu and pass it to the Upper Layer     **/
/**                             (case of Upper Layer type IF)                                                                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo           - SoAd static socket index                                                                      **/
/** PduData_pu8                 - Pointer to memory containing Pdu data                                                         **/
/** RemainingLength_u16         - Remaining length in the message                                                               **/
/** RxPduDesc_st                - Description of the received Pdu to be handled                                                 **/
/**                                                                                                                             **/
/** Parameters (inout):         None                                                                                            **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** CopiedDataToUl_pu16         - Length of data that has been copied to the Upper Layer buffer                                 **/
/**                                                                                                                             **/
/** Return value:               - SoAd_RxPduAcceptance_ten                                                                      **/
/**                                 SOAD_PDU_OK: The Pdu data have been completely forwarded to UL                              **/
/**                                 SOAD_PDU_FRAGMENTED_DATA: The Pdu data is fragmented, processing need to continue later     **/
/**                                 SOAD_PDU_DISCARD: The Pdu need to be discarded                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_IF_PRESENT != STD_OFF )
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ProcessPduDataIF (
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
                                                                            VAR(SoAd_SoConIdType, AUTOMATIC)        StaticSocketId_uo,
                                                                            VAR( uint16, AUTOMATIC )                RemainingLength_u16,
#endif
                                                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    PduData_pu8,
                                                                            VAR( SoAd_RxPduDesc_tst, AUTOMATIC )    RxPduDesc_st,
                                                                            P2VAR( uint16, AUTOMATIC, AUTOMATIC )   CopiedDataToUl_pu16 )
{
    /* Declare local variables */
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;
    P2VAR( uint8, AUTOMATIC, AUTOMATIC )                            CompletePduData_pu8;
    VAR(PduInfoType, AUTOMATIC)                                     lPduInfo_st;
    VAR(boolean, AUTOMATIC)                                         lStopProcessing_b;
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
    VAR( uint32, AUTOMATIC )                                        lRemainingPduDataLength_u32;
#endif

#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);
#endif

    /* Initialize the Pdu acceptance flag to DISCARD */
    lPduAcceptance_en = SOAD_PDU_DISCARD;

    /* Initialize the stop processing flag to FALSE */
    lStopProcessing_b = FALSE;

    /* Set the pointer to the complete Pdu data at the beginning itself */
    CompletePduData_pu8 = PduData_pu8;

    /* [SWS_SoAd_00567] */
    /* SoAd shall perform the following further actions within the SoAd_RxIndication() function for reception of a PDU to an upper layer using the IF-API: */
    /* (1) assemble all data of a fragmented IF-PDU into a SoAd receive buffer if PDU Header is used */
    /* (2) call <Up>_[SoAd][If]RxIndication() of the related upper layer module (with RxPduId set to the ID specified by the upper layer module for the PDU */
    /*     referenced by SoAdRxPduRef) for each completely received PDU */
    /* (3) dispatch the next IF-PDU (if any) if PDU Header mode is used */

    /* Case of Rx buffer and Tcp enabled (fragmentation can occurs only in that case) */
#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )

    /* --------------------------------------------- */
    /* Handle fragmentation for Tcp with Rx buffer   */
    /* --------------------------------------------- */

    /* Check if Rx buffer is configured for the socket and protocol is Tcp */
    /* (saving of fragments is only possible for Tcp, order of Udp frames is not guarenteed) */
    if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR)    &&
        (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpProtocol_en == TCPIP_IPPROTO_TCP) )
    {
        /* --------------------------------------------- */
        /* Save fragmented data                          */
        /* --------------------------------------------- */

        /* If there is already fragmented data in progress in the Rx buffer */
        if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragReceptionInProgress_b == TRUE )
        {
            /* Save it in SoAd Rx buffer */
            lRetVal_en = SoAd_AddFragmentedDataInRxBuffer( StaticSocketId_uo,
                                                           PduData_pu8,
                                                           RemainingLength_u16 );

            /* If error occured (no space in the buffer) */
            if( lRetVal_en == E_NOT_OK )
            {
                /* Set a flag to indicate that the processing need to be stopped */
                lStopProcessing_b = TRUE;

                /* Pdu will be discarded and fragments in Rx buffer deleted */
            }
        }


        /* --------------------------------------------- */
        /* Assemble and extract Pdu data                 */
        /* --------------------------------------------- */

        /* No error occured previously */
        if( lStopProcessing_b == FALSE )
        {
            /* If fragmentation is in progress */
            if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragReceptionInProgress_b == TRUE )
            {
                /* Set a flag to indicate that the processing need to be stopped */
                /* (as the Pdu is not complete, it is not possible to pass it to the UL for the moment, we have to wait for the next message) */
                lStopProcessing_b = TRUE;

                /* Set the acceptance flag to indicate that the Pdu data is fragmented and not complete for the moment */
                lPduAcceptance_en = SOAD_PDU_FRAGMENTED_DATA;
            }

            /* No fragmentation in progress */
            /* (this means we have access to the complete data) */
            else
            {
                /* Complete data is present in the Rx buffer */
                if( (uint32)(lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragCurrentSize_u16) == RxPduDesc_st.PduDataLength_u32 )
                {
                    /* Get complete Pdu from Rx buffer */
                    SoAd_GetFragmentedDataFromRxBuffer( StaticSocketId_uo, &CompletePduData_pu8 );
                }
            }
        }
    }
#endif

    /* No error occured previously */
    if( lStopProcessing_b == FALSE )
    {
        /* --------------------------------------------- */
        /* Copy Rx Data                                  */
        /* --------------------------------------------- */

        /* Data pointer is at starting of the Buffer pointer */
        lPduInfo_st.SduDataPtr = CompletePduData_pu8;

        /* Pdu length shall be equal to the length extracted from received frame (if header is enabled) OR
         * Length information given as the parameter in SoAd_RxIndication (If header is disabled) */
        lPduInfo_st.SduLength = (PduLengthType)RxPduDesc_st.PduDataLength_u32;

        /*RxCallback function to the Upper layer*/
        SoAd_CurrConfig_cpst->SoAdIf_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxIfRxIndication_u8].RxCallback_pfn ( \
                                        SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].ulRxPduId_uo, \
                                        (const PduInfoType *)&lPduInfo_st );

        /* For IF Rx packet, set the CopiedDataToUl_pu16 variable to Pdu length, so that we can assume that PDU is processed */
        (*CopiedDataToUl_pu16) = (uint16)( RxPduDesc_st.PduDataLength_u32 );

#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
        /* Check if Rx buffer is configured */
        if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR )
        {
            /* Clear data fragments from Rx buffer if any */
            (void)SoAd_ClearFragmentedDataFromRxBuffer( StaticSocketId_uo, &lRemainingPduDataLength_u32 );
        }
#endif

        /* The Pdu is fully forwarded to the Upper Layer */
        lPduAcceptance_en = SOAD_PDU_OK;
    }

    return lPduAcceptance_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_ProcessPduDataTPHeaderDisabled()   - This function process the data contained in a received Pdu and pass it to the     **/
/**                                         Upper Layer (case of Upper Layer type TP with header disabled)                      **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** PduData_pu8                             - Pointer to memory containing Pdu data                                             **/
/** RemainingLength_u16                     - Remaining length in the message                                                   **/
/** RxPduDesc_st                            - Description of the received Pdu to be handled                                     **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** CopiedDataToUl_pu16                     - Length of data that has been copied to the Upper Layer buffer                     **/
/**                                                                                                                             **/
/** Return value:                           - SoAd_RxPduAcceptance_ten                                                          **/
/**                                             SOAD_PDU_OK: The Pdu data have been completely processed (UL or Rx buffer)      **/
/**                                             SOAD_PDU_DISCARD: The Pdu need to be discarded                                  **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_TP_PRESENT != STD_OFF )
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ProcessPduDataTPHeaderDisabled (    VAR(SoAd_SoConIdType, AUTOMATIC)        StaticSocketId_uo,
                                                                                            P2VAR( uint8, AUTOMATIC, AUTOMATIC )    PduData_pu8,
                                                                                            VAR( uint16, AUTOMATIC )                RemainingLength_u16,
                                                                                            VAR( SoAd_RxPduDesc_tst, AUTOMATIC )    RxPduDesc_st,
                                                                                            P2VAR( uint16, AUTOMATIC, AUTOMATIC )   CopiedDataToUl_pu16 )
{
    /* Declare local variables */
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;
    VAR( BufReq_ReturnType, AUTOMATIC )                             lBufferRetVal_en;
    VAR(PduInfoType, AUTOMATIC)                                     lPduInfo_st;
    VAR( uint16, AUTOMATIC )                                        lAvailablePduDataLength_u16;
    VAR( uint16, AUTOMATIC )                                        lAvailableAndCopiedDataToUl_u16;
    VAR( PduLengthType, AUTOMATIC )                                 lDataLenUpperLayer_uo;
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
    VAR( uint16, AUTOMATIC )                                        lRxBuffFreeLen_u16;
#endif

#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);
#endif

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Initialize the Pdu acceptance flag to DISCARD */
    lPduAcceptance_en = SOAD_PDU_DISCARD;

    /* Initialize the available and copied length to 0 */
    lAvailableAndCopiedDataToUl_u16 = 0U;

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    /* --------------------------------------------- */
    /* Check reception in progress                   */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00568] */
    /* SoAd shall perform the following further actions within the SoAd_RxIndication() function for reception of a PDU from a socket connection with PDU Header mode */
    /* disabled to an upper layer using the TP-API: */
    /* (1) if the SoAd receive buffer does not contain any TP data for this socket connection */

    /* Check if Rx buffer is not configured for the socket or if it is configured and it does not contain TP data */
    if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst == NULL_PTR)                                                                                            ||
        ((lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR) && (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->TpDataCurrentSize_u16 == 0U)) )
#endif
    {
        /* --------------------------------------------- */
        /* Query UL buffer size                          */
        /* --------------------------------------------- */

        /* Step (a) of [SWS_SoAd_00568] */
        /* (a) Query the available amount of data at the upper layer by calling the configurable callback function <Up>_[SoAd][Tp]CopyRxData() with PduInfoType.SduLength = 0. */

        /* Initialization of data length available at Upper layer to 0 */
        lDataLenUpperLayer_uo = 0;

        /* To get the available length from UL, call the CopyRxData function with SduLength set to 0 and SduDataPtr set to NULL */
        lPduInfo_st.SduDataPtr = NULL_PTR;
        lPduInfo_st.SduLength  = 0;

        /* RxCallback function to the Upper layer to get the available length */
        lBufferRetVal_en = SoAd_CurrConfig_cpst->SoAdTp_copyRxDataCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpCopyRxDataCbk_u8].soAdCopyRxDataCbk_pfn ( \
                                    SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].ulRxPduId_uo, \
                                    (const PduInfoType*)&lPduInfo_st, \
                                    &lDataLenUpperLayer_uo );

        /* In case of success */
        if( lBufferRetVal_en == BUFREQ_OK )
        {
            /* --------------------------------------------- */
            /* Check length                                  */
            /* --------------------------------------------- */

            /* Step (b) of [SWS_SoAd_00568] */
            /* (b) If not all data can be processed (i.e. forwarded to an upper layer or stored in a SoAd receive buffer), discard all received data and skip further processing. */

            /* Compute available Pdu data length */
            /* (when header is disabled, the Pdu data length is equal to the remaining length of the message) */
            lAvailablePduDataLength_u16 = RemainingLength_u16;

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
            /* Get linear free length in SoAd Rx buffer */
            lRxBuffFreeLen_u16 = SoAd_GetRxBufLnrFreeLen( StaticSocketId_uo );
#endif

            /* If there is sufficient space to handle the data */
#if ( SOAD_RX_BUFF_ENABLE == STD_OFF )
            if( (uint32)(lDataLenUpperLayer_uo) >= (uint32)(lAvailablePduDataLength_u16) )
#else
            if( ((uint32)(lDataLenUpperLayer_uo) + (uint32)(lRxBuffFreeLen_u16)) >= (uint32)(lAvailablePduDataLength_u16) )
#endif
            {
                lPduAcceptance_en = SOAD_PDU_OK;
            }

            /* If there is not sufficient space to handle the data */
            else
            {
                /* Report DET error as per [SWS_SoAd_00693]*/
                SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_NOBUFS )
            }
        }

        /*In case of error */
        else
        {
            /* [SWS_SoAd_00570] */
            /* If <Up>_[SoAd][Tp]StartOfReception()or <Up>_[SoAd][Tp]CopyRxData() return with BUFREQ_E_NOT_OK for a socket connection with PDU Header mode disabled, SoAd shall */
            /* (a) disable further transmission or reception for this socket connection (i.e. new transmit requests shall be rejected with E_NOT_OK and received messages shall simply be discarded) and */
            /* (b) close the socket connection in the next SoAd_MainFunction(). */

            if( lBufferRetVal_en == BUFREQ_E_NOT_OK )
            {
                /* Set the global variables to skip the further transmission and reception */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b  = TRUE;

                /* As an error occurred, so request need to be taken to abort the socket connection */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD;
            }
        }


        /* --------------------------------------------- */
        /* Copy Rx Data                                  */
        /* --------------------------------------------- */

        /* Step (c) of [SWS_SoAd_00568] */
        /* (c) Copy all received data which can be accepted by the upper layer module determined at (a) to the upper layer by calling <Up>_[SoAd][Tp]Copy-RxData() */

        /* No error occured previously */
        if( lPduAcceptance_en == SOAD_PDU_OK )
        {
            /* Compute length to be copied to UL */
            lAvailableAndCopiedDataToUl_u16 = lAvailablePduDataLength_u16;

            /* Copy data to UL */
            lPduAcceptance_en = SoAd_ProcessPduDataTPExecCopy(  StaticSocketId_uo,
                                                                PduData_pu8,
                                                                RxPduDesc_st,
                                                                lDataLenUpperLayer_uo,
                                                                &lAvailableAndCopiedDataToUl_u16 );
        }
    }

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    /* Rx buffer is configured and some TP data are already present in it */
    else
    {
        /* [SWS_SoAd_00568] */
        /* (2) if the SoAd receive buffer already contains TP data for this socket connection and is able to store all (newley) received data: */
        /* copy all received data to the SoAd receive buffer for later processing by SoAd_MainFunction() */

        /* Add the Pdu data in Rx buffer */
        lRetVal_en = SoAd_AddExtraTpDataInRxBuffer( StaticSocketId_uo,
                                                    &RxPduDesc_st,
                                                    PduData_pu8,
                                                    RemainingLength_u16 );

        /* If error occured (no space in the buffer) */
        /* Pdu will be discarded and fragments in Rx buffer deleted */
        lPduAcceptance_en = ( (lRetVal_en == E_OK)? (SOAD_PDU_OK) : (SOAD_PDU_DISCARD) );
    }
#endif

    /* --------------------------------------------- */
    /* Finalisation                                  */
    /* --------------------------------------------- */

    /* If no error occured during the copy and all data have been copied to the UL and to the buffer */
    if( lPduAcceptance_en == SOAD_PDU_OK )
    {
        /* Set the out argument of the function with the length of copied data to the UL */
        (*CopiedDataToUl_pu16) = lAvailableAndCopiedDataToUl_u16;
    }

    return lPduAcceptance_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_ProcessPduDataTPHeaderEnabled()    - This function process the data contained in a received Pdu and pass it to the     **/
/**                                         Upper Layer (case of Upper Layer type TP with header enabled)                       **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** PduData_pu8                             - Pointer to memory containing Pdu data                                             **/
/** RemainingLength_u16                     - Remaining length in the message                                                   **/
/** RxPduDesc_st                            - Description of the received Pdu to be handled                                     **/
/**                                                                                                                             **/
/** Parameters (inout):                     None                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):                                                                                                           **/
/** CopiedDataToUl_pu16                     - Length of data that has been copied to the Upper Layer buffer                     **/
/**                                                                                                                             **/
/** Return value:                           - SoAd_RxPduAcceptance_ten                                                          **/
/**                                             SOAD_PDU_OK: The Pdu data have been completely processed (UL or Rx buffer)   	**/
/**                                             SOAD_PDU_FRAGMENTED_DATA: The Pdu data is fragmented, processing need to        **/
/**                                                                       continue later (fragment saved in buffer)             **/
/**                                             SOAD_PDU_DISCARD: The Pdu need to be discarded                                  **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_TP_PRESENT != STD_OFF )
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ProcessPduDataTPHeaderEnabled ( VAR(SoAd_SoConIdType, AUTOMATIC)        StaticSocketId_uo,
                                                                                        P2VAR( uint8, AUTOMATIC, AUTOMATIC )    PduData_pu8,
                                                                                        VAR( uint16, AUTOMATIC )                RemainingLength_u16,
                                                                                        VAR( SoAd_RxPduDesc_tst, AUTOMATIC )    RxPduDesc_st,
                                                                                        P2VAR( uint16, AUTOMATIC, AUTOMATIC )   CopiedDataToUl_pu16 )
{
    /* Declare local variables */
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;
    VAR( BufReq_ReturnType, AUTOMATIC )                             lBufferRetVal_en;
    VAR( uint16, AUTOMATIC )                                        lAvailablePduDataLength_u16;
    VAR( uint16, AUTOMATIC )                                        lAvailableAndCopiedDataToUl_u16;
    VAR( PduLengthType, AUTOMATIC )                                 lDataLenUpperLayer_uo;
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
    VAR( uint16, AUTOMATIC )                                        lRxBuffFreeLen_u16;
#endif

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);
#endif

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Initialize the Pdu acceptance flag to DISCARD */
    lPduAcceptance_en = SOAD_PDU_DISCARD;

    /* Initialize the available and copied length to 0 */
    lAvailableAndCopiedDataToUl_u16 = 0U;

    /* --------------------------------------------- */
    /* Check reception in progress                   */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00571] */
    /* SoAd shall perform the following further actions within the SoAd_RxIndication() function for reception of a PDU from a socket connection with PDU Header mode */
    /* enabled to an upper layer using the TP-API: */
    /* (1) if no TP reception is in progress for the related socket connection */

    /* With header enabled, there should be no TP reception ongoing */
    if( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b == FALSE )
    {
        /* --------------------------------------------- */
        /* Call StartOfReception                         */
        /* --------------------------------------------- */

        /* Step (a) of [SWS_SoAd_00571] */
        /* (a) After reception of a complete PDU Header, call <Up>_[SoAd][Tp]StartOfReception() of the related upper layer module with RxPduId set to the ID specified by */
        /*     the upper layer module for the PDU referenced by SoAdRxPduRef, set TpSduLength to the length specified in the PDU Header, and set PduInfoType.SduDataPtr and */
        /*     PduInfoType.SduLength to provide already received PDU data to the upper layer. */

        /* Initialization of data length available at Upper layer to 0 */
        lDataLenUpperLayer_uo = 0;

        /* Start of reception function to the Upper layer */
        lBufferRetVal_en = SoAd_CurrConfig_cpst->SoAdTp_StartOfReceptionCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpStartReceptionCbk_u8].StartOfReception_pfn (
                                    SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].ulRxPduId_uo,
                                    NULL_PTR,
                                    0U,
                                    &lDataLenUpperLayer_uo );

        /* In case of success */
        if( lBufferRetVal_en == BUFREQ_OK )
        {
            /* TP reception is now ongoing */
            SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b = TRUE;
            SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxRxPduTable_uo = RxPduDesc_st.RxPduId_uo;

#ifdef SOAD_DEBUG_AND_TEST
            SoAd_tpReceptionOngoing_Start_tst = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b;
#endif

            /* --------------------------------------------- */
            /* Check length                                  */
            /* --------------------------------------------- */

            /* Step (b) of [SWS_SoAd_00571] */
            /* (b) if not all data can be processed (i.e. forwarded to an upper layer or stored in a SoAd receive buffer), discard all received data, */
            /*     call <Up>_[SoAd][Tp]RxIndication()with the same RxPduId as used at <Up>_[SoAd][Tp]StartOfReception() and result set to E_NOT_OK and skip further processing */

            /* Compute available Pdu data length */
            lAvailablePduDataLength_u16 = ( (RxPduDesc_st.PduDataLength_u32 < (uint32)(RemainingLength_u16))? (uint16)(RxPduDesc_st.PduDataLength_u32) : (RemainingLength_u16) );

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
            /* Get linear free length in SoAd Rx buffer */
            lRxBuffFreeLen_u16 = SoAd_GetRxBufLnrFreeLen( StaticSocketId_uo );
#endif

            /* If there is sufficient space to handle the data */
#if ( SOAD_RX_BUFF_ENABLE == STD_OFF )
            if( (uint32)(lDataLenUpperLayer_uo) >= (uint32)(lAvailablePduDataLength_u16) )
#else
            if( ((uint32)(lDataLenUpperLayer_uo) + (uint32)(lRxBuffFreeLen_u16)) >= (uint32)(lAvailablePduDataLength_u16) )
#endif
            {
                lPduAcceptance_en = SOAD_PDU_OK;
            }

            /* If there is not sufficient space to handle the data */
            else
            {
                /* Report DET error as per [SWS_SoAd_00693]*/
                SOAD_DET_REPORT_ERROR( TRUE, SOAD_RX_INDICATION_API_ID, SOAD_E_NOBUFS )
            }
        }


        /* --------------------------------------------- */
        /* Copy Rx Data                                  */
        /* --------------------------------------------- */

        /* Step (c) of [SWS_SoAd_00571] */
        /* (c) call <Up>_[SoAd][Tp]CopyRxData() of the related upper layer module with the same RxPduId as used at <Up>_[SoAd][Tp]StartOf-Reception() and PduInfoType.SduDataPtr pointing to the PDU data provided by SoAd_RxIndication() */
        /* and PduInfoType.SduLength set to minimum of the received PDU data and the available receive buffer in the upper layer module specified by bufferSizePtr at <Up>_[SoAd][Tp]-StartOfReception()) */

        /* No error occured previously */
        if( lPduAcceptance_en == SOAD_PDU_OK )
        {
            /* Compute length to be copied to UL */
            lAvailableAndCopiedDataToUl_u16 = lAvailablePduDataLength_u16;

            /* Copy data to UL */
            lPduAcceptance_en = SoAd_ProcessPduDataTPExecCopy(  StaticSocketId_uo,
                                                                PduData_pu8,
                                                                RxPduDesc_st,
                                                                lDataLenUpperLayer_uo,
                                                                &lAvailableAndCopiedDataToUl_u16 );
        }
    }

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    /* TP reception in progress */
    else
    {
        /* [SWS_SoAd_00571] */
        /* (2) if a TP reception is in progress for the related socket connection and the related SoAd receive buffer is able to store all received data: */
        /* copy all received data to the related SoAd receive buffer for later processing by SoAd_MainFunction() */

        /* If Rx buffer is configured */
        if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR )
        {
            /* If data fragmentation is in progress */
            if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragReceptionInProgress_b == TRUE )
            {
                /* Save fragment in SoAd Rx buffer */
                lRetVal_en = SoAd_AddFragmentedDataInRxBuffer( StaticSocketId_uo,
                                                               PduData_pu8,
                                                               RemainingLength_u16 );
            }

            /* No fragmentation in progress */
            else
            {
                /* Add the complete new extra Pdu data in Rx buffer */
                lRetVal_en = SoAd_AddExtraTpDataInRxBuffer( StaticSocketId_uo,
                                                            &RxPduDesc_st,
                                                            PduData_pu8,
                                                            (uint16)RxPduDesc_st.PduDataLength_u32 );
            }

            /* If error occured (no space in the buffer) */
            /* Pdu will be discarded and fragments in Rx buffer deleted */
            lPduAcceptance_en = ( (lRetVal_en == E_NOT_OK)? (SOAD_PDU_DISCARD) : (SOAD_PDU_OK) );
        }
    }
#endif

    /* --------------------------------------------- */
    /* Finalisation                                  */
    /* --------------------------------------------- */

    /* No error occured previously */
    if( lPduAcceptance_en == SOAD_PDU_OK )
    {
        /* Set the out argument of the function with the length of copied data to the UL */
        (*CopiedDataToUl_pu16) = lAvailableAndCopiedDataToUl_u16;

#if ( (SOAD_RX_BUFF_ENABLE != STD_OFF) && (SOAD_TCP_PRESENT != STD_OFF) )
        /* If Rx buffer is configured and fragmented Pdu data reception is in progress in the SoAd Rx buffer */
        if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR)                            &&
            (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragReceptionInProgress_b == TRUE) )
        {
            /* The Pdu is data are not completely received yet, overwrite Pdu acceptance to SOAD_PDU_FRAGMENTED_DATA */
            /* (first part has been handled and now TpReceptionOngoing is true, new fragments will be received later) */
            lPduAcceptance_en = SOAD_PDU_FRAGMENTED_DATA;
        }
#endif
    }

    /* In case an error occured (it was not possible to forward data to UL or to store them in SoAd Rx buffer) */
    else
    {
        /* [SWS_SoAd_00572] */
        /* If <Up>_[SoAd][Tp]StartOfReception() does not return BUFREQ_OK for a socket connection with PDU Header mode enabled, SoAd shall simply discard all data of the PDU. */

        /* [SWS_SoAd_00573] */
        /* If <Up>_[SoAd][Tp]CopyRxData() does not return BUFREQ_OK for a socket connection with PDU Header mode enabled, */
        /* SoAd shall terminate the TP receive session, simply discard all data of the PDU and call <Up>_[SoAd][Tp]RxIndication() with E_NOT_OK */

        /* If TP reception was ongoing */
        if( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b == TRUE )
        {
            /* Terminate the TP reception session */
            SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b = FALSE;
            SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxRxPduTable_uo = (PduIdType)0xFFFF;
#ifdef SOAD_DEBUG_AND_TEST
            SoAd_tpReceptionOngoing_Stop_tst = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b;
#endif

            /* Call the upper layer with notify reslut type E_NOT_OK */
            SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpRxIndication_u8].RxCallback_pfn(
                                            SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].ulRxPduId_uo,
                                            E_NOT_OK);
        }
    }

    return lPduAcceptance_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_ProcessPduDataTPExecCopy()    - This function executes the copying of the Pdu data to the UL and to the SoAd Rx buffer **/
/**                                      (case of Upper Layer type TP with header enabled or disabled)                          **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo                       - SoAd static socket index                                                          **/
/** PduData_pu8                             - Pointer to memory containing Pdu data                                             **/
/** RxPduDesc_st                            - Description of the received Pdu to be handled                                     **/
/** InitialDataLenUpperLayer_uo             - Initial available buffer size at Upper Layer                                      **/
/**                                                                                                                             **/
/** Parameters (inout):                                                                                                         **/
/** AvailableAndCopiedDataToUl_pu16         - Total available length to be copied as in argument and copied length as out       **/
/**                                                                                                                             **/
/** Parameters (out):                       None                                                                                **/
/**                                                                                                                             **/
/** Return value:                           - SoAd_RxPduAcceptance_ten                                                          **/
/**                                             SOAD_PDU_OK: The Pdu data have been copied                                      **/
/**                                             SOAD_PDU_DISCARD: The Pdu need to be discarded                                  **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_TP_PRESENT != STD_OFF )
static FUNC( SoAd_RxPduAcceptance_ten, SOAD_CODE ) SoAd_ProcessPduDataTPExecCopy (  VAR(SoAd_SoConIdType, AUTOMATIC)            StaticSocketId_uo,
                                                                                    P2VAR( uint8, AUTOMATIC, AUTOMATIC )        PduData_pu8,
                                                                                    VAR( SoAd_RxPduDesc_tst, AUTOMATIC )        RxPduDesc_st,
                                                                                    VAR( PduLengthType, AUTOMATIC )             InitialDataLenUpperLayer_uo,
                                                                                    P2VAR( uint16, AUTOMATIC, AUTOMATIC )       AvailableAndCopiedDataToUl_pu16 )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;
    VAR( SoAd_RxPduAcceptance_ten, AUTOMATIC )                      lPduAcceptance_en;
    VAR( BufReq_ReturnType, AUTOMATIC )                             lBufferRetVal_en;
    VAR(PduInfoType, AUTOMATIC)                                     lPduInfo_st;
    VAR( uint16, AUTOMATIC )                                        lRemainingDataToBeCopiedToUL_u16;
    VAR( uint16, AUTOMATIC )                                        lCopiedDataToUL_u16;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;
    VAR( PduLengthType, AUTOMATIC )                                 lDataLenUpperLayer_uo;
    VAR( boolean, AUTOMATIC )                                       lCopyError_b;
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    VAR( Std_ReturnType, AUTOMATIC )                                lRetVal_en;
#endif

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get dynamic socket from static socket */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Initialize the Pdu acceptance flag to DISCARD */
    lPduAcceptance_en = SOAD_PDU_DISCARD;

    /* Initialize the error flag to FALSE */
    lCopyError_b = FALSE;

    /* Initialize the copied length to the UL to 0 */
    lCopiedDataToUL_u16 = 0U;

    /* --------------------------------------------- */
    /* Copy data to UL                               */
    /* --------------------------------------------- */

	/* Step (c) of [SWS_SoAd_00568] */
	/* (c) Copy all received data which can be accepted by the upper layer module determined at (a) to the upper layer by calling <Up>_[SoAd][Tp]Copy-RxData() */

	/* Step (c) of [SWS_SoAd_00571] */
	/* (c) call <Up>_[SoAd][Tp]CopyRxData() of the related upper layer module with the same RxPduId as used at <Up>_[SoAd][Tp]StartOf-Reception() and PduInfoType.SduDataPtr pointing to the PDU data provided by SoAd_RxIndication() */
	/* and PduInfoType.SduLength set to minimum of the received PDU data and the available receive buffer in the upper layer module specified by bufferSizePtr at <Up>_[SoAd][Tp]-StartOfReception()) */

    /* Initialize the data length at UL */
    lDataLenUpperLayer_uo = InitialDataLenUpperLayer_uo;

    /* Compute the remaining length of data to be copied */
    lRemainingDataToBeCopiedToUL_u16 = (*AvailableAndCopiedDataToUl_pu16);

    /* Initialize Pdu Info */
    lPduInfo_st.SduDataPtr = PduData_pu8;
    lPduInfo_st.SduLength = (PduLengthType)( ((uint32)(lDataLenUpperLayer_uo) < (uint32)(lRemainingDataToBeCopiedToUL_u16))? (uint16)(lDataLenUpperLayer_uo) : (lRemainingDataToBeCopiedToUL_u16) );

    /* While there is some data to forward to the UL and there is available size in the UL buffer */
    while( (lRemainingDataToBeCopiedToUL_u16 > 0U) && (lDataLenUpperLayer_uo > 0U) )
    {
        /* RxCallback function to the Upper layer to copy the data */
        lBufferRetVal_en = SoAd_CurrConfig_cpst->SoAdTp_copyRxDataCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpCopyRxDataCbk_u8].soAdCopyRxDataCbk_pfn (
                                        SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].ulRxPduId_uo,
                                        &lPduInfo_st,
                                        &lDataLenUpperLayer_uo);

        /* In case of success */
        if( lBufferRetVal_en == BUFREQ_OK )
        {
            /* Increment the copied length to the UL */
            lCopiedDataToUL_u16 += lPduInfo_st.SduLength;

            /* Calculate the remaining data to be copied */
            lRemainingDataToBeCopiedToUL_u16 -= lPduInfo_st.SduLength;

            /* Update the Pdu Info for next iteration */
            lPduInfo_st.SduDataPtr = PduData_pu8 + lCopiedDataToUL_u16;
            lPduInfo_st.SduLength = (PduLengthType)( ((uint32)(lDataLenUpperLayer_uo) < (uint32)(lRemainingDataToBeCopiedToUL_u16))? (uint16)(lDataLenUpperLayer_uo) : (lRemainingDataToBeCopiedToUL_u16) );
        }

        /* In case of error */
        else
        {
            /* [SWS_SoAd_00570] */
            /* If <Up>_[SoAd][Tp]StartOfReception()or <Up>_[SoAd][Tp]CopyRxData() return with BUFREQ_E_NOT_OK for a socket connection with PDU Header mode disabled, SoAd shall */
            /* (a) disable further transmission or reception for this socket connection (i.e. new transmit requests shall be rejected with E_NOT_OK and received messages shall simply be discarded) and */
            /* (b) close the socket connection in the next SoAd_MainFunction(). */

            /* If the header is disabled and we get BUFREQ_E_NOT_OK */
            if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == FALSE)    &&
                (lBufferRetVal_en == BUFREQ_E_NOT_OK) )
            {
                /* Set the global variables to skip the further transmission and reception */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b = TRUE;

                /* As an error occurred, so request need to be taken to abort the socket connection */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD;
            }

            /* Set the error flag to TRUE */
            lCopyError_b = TRUE;

            /* Stop the copying of the data */
            break;
        }
    }

    /* If no error occured during copy to UL */
    if( lCopyError_b == FALSE )
    {
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
        /* ----------------------------------------------- */
        /* Check for starting of Tp reception in Rx buffer */
        /* ----------------------------------------------- */

        /* If the buffer is configured and not all Pdu data have been copied or received for the moment */
        if( (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR)    &&
            ((lRemainingDataToBeCopiedToUL_u16 > 0U) || (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->DataFragReceptionInProgress_b == TRUE)) )
        {
            /* Execute the starting of the Tp reception in the SoAd Rx buffer */
            SoAd_StartTpDataInRxBuffer(  StaticSocketId_uo,
                                         &RxPduDesc_st,
                                         lCopiedDataToUL_u16 );
        }
#endif


        /* --------------------------------------------- */
        /* Available data fully copied to UL             */
        /* --------------------------------------------- */
        if( lRemainingDataToBeCopiedToUL_u16 == 0U )
        {
            /* If header is enabled and complete Pdu data have been copied to UL */
            if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == TRUE) &&
                ((uint32)(lCopiedDataToUL_u16) == RxPduDesc_st.PduDataLength_u32) )
            {
                /* Step (d) of [SWS_SoAd_00571] */
                /* (d) call <Up>_[SoAd][Tp]RxIndication() if the complete PDU has been forwarded to the upper layer, otherwise copy all received data which could not be forwarded */
                /*     to the upper layer to a SoAd receive buffer for later processing by SoAd_MainFunction() */

                /* Call the upper layer with notify reslut type E_OK */
                SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].idxTpRxIndication_u8].RxCallback_pfn(
                                                SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduDesc_st.RxPduId_uo].ulRxPduId_uo,
                                                E_OK);

                /* Terminate the TP reception session */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b = FALSE;
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxRxPduTable_uo = (PduIdType)0xFFFF;
#ifdef SOAD_DEBUG_AND_TEST
                SoAd_tpReceptionOngoing_Stop_tst = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b;
#endif
            }

            /* Set the out argument of the function */
            (*AvailableAndCopiedDataToUl_pu16) = lCopiedDataToUL_u16;

            /* Set the return value of the function to SOAD_PDU_OK */
            /* (No more processing is required because all the available data have been given to UL) */
            lPduAcceptance_en = SOAD_PDU_OK;
        }


        /* --------------------------------------------- */
        /* Available data partly copied to UL            */
        /* --------------------------------------------- */
        else
        {
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
            /* --------------------------------------------- */
            /* Save remaining data in Rx buffer              */
            /* --------------------------------------------- */

			/* Step (d) of [SWS_SoAd_00568] */
			/* (d) Copy all remaining data (i.e. data which are received but not delivered to the upper layer) to a SoAd receive buffer for later processing by SoAd_MainFunction() */

            /* Step (d) of [SWS_SoAd_00571] */
            /* otherwise copy all received data which could not be forwarded to the upper layer to a SoAd receive buffer for later processing by SoAd_MainFunction() */

            /* Check if Rx buffer is configured */
            if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR )
            {
                /* Add the remaining data in Rx buffer */
                lRetVal_en = SoAd_AddTpDataInRxBuffer(  StaticSocketId_uo,
                                                        (PduData_pu8 + lCopiedDataToUL_u16),
                                                        lRemainingDataToBeCopiedToUL_u16 );

                /* If no error occured */
                if( lRetVal_en == E_OK )
                {
                    /* Set the out argument of the function */
                    (*AvailableAndCopiedDataToUl_pu16) = lCopiedDataToUL_u16;

                    /* Set the return value of the function to SOAD_PDU_OK */
                    /* (not all data have been given to the UL but the remaining part is successfully saved in the SoAd Rx buffer) */
                    lPduAcceptance_en = SOAD_PDU_OK;
                }
            }
#endif
        }
    }

    return lPduAcceptance_en;
}
#endif


/*********************************************************************************************************************************/
/** SoAd_RxIndicationDetChk() - This function check calling errors for the RxIndication API                                     **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** TcpIpSocketId_uo                - TcpIp socket identifier of the related local socket resource                              **/
/** RemoteAddrPtr_pst               - Pointer to memory containing IP address and port of the remote host which sent the data   **/
/** Buffer_cpu8                     - Pointer to the received data                                                              **/
/** Length_u16                      - Data length of the received TCP segment or UDP datagram                                   **/
/**                                                                                                                             **/
/** Parameters (inout):             None                                                                                        **/
/**                                                                                                                             **/
/** Parameters (out):               None                                                                                        **/
/**                                                                                                                             **/
/** Return value:                   None                                                                                        **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_RxIndicationDetChk ( VAR( TcpIp_SocketIdType, AUTOMATIC )                 TcpIpSocketId_uo,
                                                         P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddr_cpst,
                                                         P2CONST( uint8, AUTOMATIC, AUTOMATIC )               Buffer_cpu8,
                                                         VAR( uint16, AUTOMATIC )                             Length_u16 )
{
    /* Variable to store the port for remote address */
    VAR(uint16, AUTOMATIC) lRemoteAddrPort_u16;

    /* Variable to hold if remote IP address is null (all zeros) */
    VAR(boolean, AUTOMATIC) lIsNullAddr_b;

    /* Variable to store index of the socket connection Group */
    VAR(SoAd_SoConIdType, AUTOMATIC)  lIdxSoConGroup_uo;

    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
             * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
             * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
             * for the same function.
             */
            SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* Check whether BufPtr & RemoteAddrPtr pointers are valid or not */
    SOAD_DET_REPORT_ERROR( ( ( NULL_PTR == Buffer_cpu8 ) || ( NULL_PTR == RemoteAddr_cpst )), SOAD_RX_INDICATION_API_ID, SOAD_E_PARAM_POINTER )

    /* check here for DET error as the variable is used after this */
    /* check that DET was not called */
    if(SoAd_DetErrFlag_u8 == E_NOT_OK)
    {
		/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
        lRemoteAddrPort_u16 = SOAD_GET_PORT_FROM_SOCK_ADDR(RemoteAddr_cpst);
		/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
        lIsNullAddr_b       = SOAD_SOCK_ADDR_HAS_WILDCARD_IPADDR(RemoteAddr_cpst);

        /* Get the static group socket index from static socket table */
        lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoAd_DyncSocConfig_ast[SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo]].idxStaticSoc_uo].soConGrpId_uo ;

        /* Check for DET errors */
        /* Check whether SoAd Init function was already called or not */
        SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_RX_INDICATION_API_ID, SOAD_E_NOTINIT )

        /* Check whether SocketId is valid or not */
        SOAD_DET_REPORT_ERROR( (TcpIpSocketId_uo >= SOAD_NUM_TCPIP_SOCKETS), SOAD_RX_INDICATION_API_ID, SOAD_E_INV_SOCKETID )

        /* Check whether Length & RemoteAddrPtr parameters are valid or not */
        SOAD_DET_REPORT_ERROR( ( ( 0U == Length_u16 )                ||
                                 lIsNullAddr_b                       ||
                                 ( SOAD_DEFAULT_PORT == lRemoteAddrPort_u16 )  ||
                                 ( SOAD_NULL == lRemoteAddrPort_u16 )  ||
                                 ( !((RemoteAddr_cpst->domain == TCPIP_AF_INET)||(RemoteAddr_cpst->domain == TCPIP_AF_INET6))) ) , SOAD_RX_INDICATION_API_ID, SOAD_E_INV_ARG )

        /* Check whether RemoteAddr_cpst and connection domain are equal */
        SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].domain_en != RemoteAddr_cpst->domain ), SOAD_RX_INDICATION_API_ID, SOAD_E_INV_ARG )
    }
}
#endif


#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
