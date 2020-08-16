

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED
#include "SoAd_Cbk.h"
#include "Det.h"

#include "SoAd_Prv.h"

#ifdef SOAD_DEBUG_AND_TEST
#include "TestSoAdApplication.h"
#endif
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */

/*
 ***************************************************************************************************
 * Prototype for Static functions: Start
 ***************************************************************************************************
 */
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

#if (SOAD_TCP_SERVER_GRP_PRESENT != FALSE)
static FUNC( Std_ReturnType, SOAD_CODE )        SoAd_FindBestMatchSoConId                   ( VAR(SoAd_SoConIdType, AUTOMATIC)                      TcpServerGrpId_uo , \
                                                                                              P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddr_cpst, \
                                                                                              P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )       StaticSocketIdx_puo );

static FUNC( void, SOAD_CODE )                  SoAd_ModifyRemoteAddr                       ( VAR( SoAd_SoConIdType, AUTOMATIC )                   StaticSocketId_uo, \
                                                                                              P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddrPtr_cpst );
#endif /* SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF */

#if ( ( SOAD_TCP_SERVER_GRP_PRESENT != FALSE ) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
static FUNC( void, SOAD_CODE )                  SoAd_TcpAcceptedDetChk                      ( VAR( TcpIp_SocketIdType, AUTOMATIC )                TcpIpListenSocketId_uo, \
                                                                                              VAR( TcpIp_SocketIdType, AUTOMATIC )                TcpIpConnectedSocketId_uo , \
                                                                                              P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC ) RemoteAddr_cpst );
#endif /* ( SOAD_TCP_SERVER_GRP_PRESENT != FALSE ) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

/**
 **********************************************************************************************************************
 * \Function Name : SoAd_TcpAccepted()
 *
 * \Function description
 * The TCP/IP stack calls this function after a socket was set into the listen state with TcpIp_TcpListen() and a TCP
 * connection is requested by the peer.
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     SocketId : Socket identifier of the related local socket resource.
 * \param   TcpIp_SocketIdType
 * \arg     SocketIdConnected : Socket identifier of the local socket resource used for the established connection.
 * \param   TcpIp_SockAddrType
 * \arg     RemoteAddrPtr: pointer to IP address and port of the remote host.
 *
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  Std_ReturnType
 * \lRetVal_u8 E_OK :       SoAd accepts the established connection
 *          E_NOT_OK:   SoAd refuses the established connection, TcpIp stack shall close the connection.
 *
 **********************************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_TcpAccepted( VAR( TcpIp_SocketIdType, AUTOMATIC )                 SocketId , \
                                                    VAR( TcpIp_SocketIdType, AUTOMATIC )                 SocketIdConnected , \
                                                    P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddrPtr )
{

#if (SOAD_TCP_SERVER_GRP_PRESENT != FALSE)

    /* Local pointer to store the Dynamic array one by one */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /*variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* variable to store the return value of internal function */
    VAR( Std_ReturnType, AUTOMATIC )                        lRetVal_u8;

    /* variable to hold index of static soc table */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticSocket_uo;

    /* variable to store the dynamic config table id*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo ;

    /* variable to store the TcpServerGroupId */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lTcpServerGrpId_uo ;

    /* variable to store the Protocol type of socket group */
    VAR(TcpIp_ProtocolType, AUTOMATIC)                      lSoConGrpProtocol_en;

    /* variable to store the type of Tcp socket */
    VAR(uint8, AUTOMATIC)                                   lTcpInitiate_u8;

#if (SOAD_TP_PRESENT != STD_OFF)
    /* Variable to store the index of RxPduTable */
    VAR(PduIdType, AUTOMATIC)                               lIdxRxPdu_uo;
#endif  /*SOAD_TP_PRESENT != STD_OFF*/

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8      = E_NOT_OK ;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    SoAd_TcpAcceptedDetChk(SocketId, SocketIdConnected, (const TcpIp_SockAddrType*)RemoteAddrPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        lIdxStaticSocket_uo     = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
        lTcpServerGrpId_uo      = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
        lSoConGrpProtocol_en    = TCPIP_IPPROTO_NONE;
        lTcpInitiate_u8         = STD_ON;

#if (SOAD_TP_PRESENT != STD_OFF)
        lIdxRxPdu_uo = SOAD_CFG_PDU_ID_DEFAULT_VALUE;
#endif  /*SOAD_TP_PRESENT != STD_OFF*/

        /* Get the index of dynamic config table by using array and SocketId as index */
        lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId];

        /* Condition check: the dynamic socket id should be valid  */
        if( lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo )
        {
            /* Get the "index of the static socket table" from the dynamic socket table  */
            lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo ;

            /*Condition check: Index of the static socket should be valid*/
            if(SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo > lIdxStaticSocket_uo)
            {
                /*Get the Index of the Group from static socket table and lIdxStaticSocket_uo as index */
                lTcpServerGrpId_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo;

                /*Get the protocol type to local variable to access it in multiple places*/
                lSoConGrpProtocol_en = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lTcpServerGrpId_uo].soConGrpProtocol_en;

                /*Get the Tcp socket type to local variable to access it in multiple places*/
                lTcpInitiate_u8      = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lTcpServerGrpId_uo].tcpProtocolConf_cpst->tcpInitiate_u8;
            }
        }

        /* reset the dynamic index for further processing */
        lIdxDynSocket_uo      = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00594] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /*** At SoAd_TcpAccepted(), SoAd shall perform the following actions if the TCP SoAdSocketConnectionGroup     ***/
        /***  related to SocketId has SoAdSocketTcpInitiate set to FALSE                                              ***/
        /****************************************************************************************************************/
        /* process only if protocol is TCP and initiateTCP is disabled (server)*/
       if( ( TCPIP_IPPROTO_TCP == lSoConGrpProtocol_en ) && \
           ( STD_OFF == lTcpInitiate_u8 ) )
        {
           /* Get the socket index by applying the Best Match Algorithm as per SWS_SoAd_00680 */
           lRetVal_u8 = SoAd_FindBestMatchSoConId( lTcpServerGrpId_uo,
                                                   (const TcpIp_SockAddrType*)RemoteAddrPtr,
                                                   &lIdxStaticSocket_uo );

           if(E_OK == lRetVal_u8)
           {
               /****************************************************************************************************************/
               /****************************************** [SWS_SoAd_00594]:step(3) ********************************************/
               /****************************************** [SWS_SoAd_00636]:step(1) ********************************************/
               /****************************************************************************************************************/
               /****************************************************************************************************************/
               /*** assign the TcpIp socket used for the established connection and provided as parameter SocketIdConnected  ***/
               /***                         to the chosen socket connection                                                  ***/
               /****************************************************************************************************************/

                /* Get the dynamic socketId of the static socketId */
                lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].SoAd_Prv_idxDynSocTable_puo);
           }
        }

       /*Condition check: Index of the dynamic socket should be valid*/
       if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
       {
           /* Extract pointer to Dynamic structrue for given index */
           lSoAdDyncSocConfig_pst  = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

           /* The below If condition belongs to CSCRM00787600 */
           /* SoAd socket goes to RECONNECT state when SoAd_TcpIpEvent( SocketId , TCP_CLOSED) is called from TCP.
            * If SoAd_TcpAcepted is called from different remote at the same time(immediately after SoAd_TcpIpEvent before SoAd_Mainfunction,
            * then SoAd SoAd_TcpAcepted will return E_NOT_OK. To handle this scenario, SoAd will make the socket state to SOAD_SOCON_TCPWAITFORREMOTE.
            */
           if( ( SOAD_SOCON_RECONNECT   == lSoAdDyncSocConfig_pst->socConMode_en ) && \
               ( SOAD_SOCON_CLOSE       == lSoAdDyncSocConfig_pst->socConSubMode_en ) && \
               ( SOAD_TCPIP_TCPSOCKET_MAX > (*SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lTcpServerGrpId_uo].groupTcpIpSocketId_puo ) ) )
           {
              /* Set the sub state of the socket to SOAD_SOCON_TCPWAITFORREMOTE to accept the parallel connection from remote */
              lSoAdDyncSocConfig_pst->socConSubMode_en  = SOAD_SOCON_TCPWAITFORREMOTE;
           }

           /* process only if socket state is SOAD_SOCON_RECONNECT and socket substate is SOAD_SOCON_TCPWAITFORREMOTE.
            * if socConSubMode_en is SOAD_SOCON_TCPWAITFORREMOTE, then socConMode_en will be SOAD_SOCON_RECONNECT in all the scenario,
            * so no need of checking the socConMode_en state to SOAD_SOCON_RECONNECT in the below condition */
           if( SOAD_SOCON_TCPWAITFORREMOTE == lSoAdDyncSocConfig_pst->socConSubMode_en )
           {
                /****************************************************************************************************************/
                /****************************************** [SWS_SoAd_00594]:step(4) ********************************************/
                /****************************************** [SWS_SoAd_00636]:step(2) ********************************************/
                /****************************************************************************************************************/
                /****************************************************************************************************************/
                /*** change the state of this socket connection to SOAD_SOCON_ONLINE and return E_OK                          ***/
                /****************************************************************************************************************/

               /* set the socConStatus to SOAD_SOCON_ONLINE */
               lSoAdDyncSocConfig_pst->socConSubMode_en    = SOAD_SOCON_ACTIVE ;

               /* call a function which shall invoke the upper layer call back for mode change */
               SoAd_ModeChgCallbackToUl(lIdxStaticSocket_uo, lIdxDynSocket_uo, SOAD_SOCON_ONLINE );

               /* Update the established TcpIp handle Id in the dynamic table */
               lSoAdDyncSocConfig_pst->socketHandleTcpIp_uo = SocketIdConnected;

               /* index of the array is socket handle give by tcpip layer and element of the array is dyanamic index */
               SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketIdConnected] = lIdxDynSocket_uo;

#if (SOAD_TP_PRESENT != STD_OFF)
               /* If header is not enabled for the socket connection group, call the UL startOfReception as per SWS_SoAd_00595*/
               /* start of reception shall be called for upper layer of a socket only if the type is TP */
               if( ( FALSE == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo].headerEnable_b ) && \
                   ( 1U == SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].numberOfRxPdusConfigured_u8 ) )
               {
                   /* Get the RxPdu Id from static socket table for posting the start of reception callback to UL if header is disabled and type is TP*/
                   lIdxRxPdu_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].rxPduIds_pcuo[0];

                    if( SOAD_TP == SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lIdxRxPdu_uo].rxUpperLayerType_en )
                    {
                        /* call start of reception related to all Rx pdus*/
                        SoAd_InformTpStartOfReception(lIdxStaticSocket_uo, lIdxRxPdu_uo);
                    }
               }
#endif  /*SOAD_TP_PRESENT != STD_OFF*/

               /* As SoAd accepts the established connection, so lFunctionRetVal_u8 is E_OK */
               lFunctionRetVal_u8 = E_OK;
           }

       }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);

#else

    (void)SocketId;
    (void)SocketIdConnected;
    (void)RemoteAddrPtr;

    return(E_NOT_OK);

#endif /* SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF */

}

#if (SOAD_TCP_SERVER_GRP_PRESENT != FALSE)
/**
 ***************************************************************************************************
 * \Function Name : SoAd_FindBestMatchSoConId()
 *
 * \Function description
 * To get the SoConId from TcpServer table for the matching listen socket id.
 * If Msg Acceptance policy is enabled then it will go for Best Match Algorithm or else
 * directly fetches the any available socket which were waiting for client to be established
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     lTcpServerGrpId_uo : Socket identifier of the Group.
 * \param   const TcpIp_SockAddrType*
 * \arg     RemoteAddr_cpst - pointer to IP address and port of the remote host.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):
 * \param   SoAd_SoConIdType*
 * \arg     StaticSocketIdx_puo : Index of the socket connection table matched to listen socket id.
 *
 * Return value:
 * \return  Std_ReturnType
 * \lRetVal_u8  E_OK :      SoAd gets the static soconid from the listen socket id.
 *          E_NOT_OK:   Unable to get the static soconid from the listen socket id.
 *
 ***************************************************************************************************
 */
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_FindBestMatchSoConId( VAR( SoAd_SoConIdType, AUTOMATIC )                    TcpServerGrpId_uo , \
                                                                    P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )   RemoteAddr_cpst, \
                                                                    P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )       StaticSocketIdx_puo )
{
    /*variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* variable to hold index of static soc table */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticSocket_uo;

    /*Initialization of local variables */
    lFunctionRetVal_u8          = E_OK;

#if (SOAD_MSG_ACCEPT_POLICY_ENABLED != STD_OFF)

    /* Condition check for message acceptance filter is enabled */
    if( TRUE == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[TcpServerGrpId_uo].socMsgAcceptanceFiletEnable_b )
    {
        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00594]:step(1) ********************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /*** choose one of the socket connections using the best match algorithm (see [SWS_SoAd_00680]), and either   ***/
        /***  proceed with the selected socket connection or skip further processing and return with E_NOT_OK         ***/
        /***                                 if no match can be found                                                 ***/
        /****************************************************************************************************************/

        /* Get the socket id with the help of best match algorithm */
        lFunctionRetVal_u8 = SoAd_BestMatchAlgorithm( SOAD_CFG_SOCON_ID_DEFAULT_VALUE, TcpServerGrpId_uo, 0, RemoteAddr_cpst, &lIdxStaticSocket_uo );
    }
    else
#endif /* SOAD_MSG_ACCEPT_POLICY_ENABLED != STD_OFF */
    {
        /* fetch the start socket id from Group table and loop through for max socket couent */
        lIdxStaticSocket_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[TcpServerGrpId_uo].startSoConIdx_uo;
    }

    if( E_OK == lFunctionRetVal_u8 )
    {
        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00594]:step(2) ********************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /*** overwrite the remote address parts specified with wildcards (e.g. remote IP address set to               ***/
        /***  TCPIP_IPADDR_ANY) with the related source address parts of the received message if the remote address   ***/
        /***                         set for the socket connection contains wildcards                                 ***/
        /****************************************************************************************************************/

        /* Call to SoAd_ModifyRemoteAddr to overwrite the remote address */
        SoAd_ModifyRemoteAddr(lIdxStaticSocket_uo, RemoteAddr_cpst);

        /*assign the socket index to out variable*/
        *StaticSocketIdx_puo     = lIdxStaticSocket_uo;
    }

    return lFunctionRetVal_u8;
}

/**
 **************************************************************************************************************************
 * \Function Name : SoAd_ModifyRemoteAddr()
 *
 * \Function description
 * This service will modify the remote address of Socket connection depend on MsgAcceptancePolicy Enabled/Disabled.
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     lSocketId_uo - static socket id.
 * \param   TcpIp_SockAddrType*
 * \arg     lRemoteAddrPtr_cpst - Pointer to memory containing IP address and port of the remote host which sent the data.
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 **************************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_ModifyRemoteAddr( VAR( SoAd_SoConIdType, AUTOMATIC )                   StaticSocketId_uo, \
                                                      P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC )  RemoteAddrPtr_cpst )
{
    /* Local pointer to store the Dynamic array for given Index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)           lSoAdDyncSocConfig_pst ;

    /* variable to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo;

    /* Variable to store if the remote address of dynamic socket is wildcard (ANY)  */
    VAR(boolean, AUTOMATIC)                                         lDyncSocConfigHasWildcardAnyAddr_b;

    /* Variable to store the port for dynamic socket */
    VAR(uint16, AUTOMATIC)                                          lDyncSocPort_u16;

    /* Initialize the local variable idxstatsock_uo */
    /* Get the dynamic socketId of the static socketId */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* check: dynamic socket is valid or not */
    if(lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo)
    {
        /* Get the index of related socket connection group */
        lSoAdDyncSocConfig_pst   =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

        lDyncSocConfigHasWildcardAnyAddr_b = SOAD_DYNC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR(lSoAdDyncSocConfig_pst);
        lDyncSocPort_u16                   = SOAD_GET_REMOTE_PORT_FROM_DYNC_SOC_CONFIG(lSoAdDyncSocConfig_pst);

		/* Modify the Remote Ip address, if remote Ip address contains wildcard*/
        if ( TRUE == lDyncSocConfigHasWildcardAnyAddr_b )
        {
			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_IPADDR(RemoteAddrPtr_cpst, lSoAdDyncSocConfig_pst)
        }

        /* Modify the Remote port address, if remote port address contains wildcard*/
        if ( TCPIP_PORT_ANY == lDyncSocPort_u16 )
        {
			/* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            SOAD_COPY_FROM_SOCK_ADDR_TO_DYNC_SOC_CONFIG_REMOTE_PORT(RemoteAddrPtr_cpst, lSoAdDyncSocConfig_pst)
        }
    }
}
#endif /* SOAD_TCP_SERVER_GRP_PRESENT != STD_OFF */

#if ( ( SOAD_TCP_SERVER_GRP_PRESENT != FALSE ) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TcpAcceptedDetChk()
 *
 * \Function description
 *  This function is called from SoAd_TcpAccepted to handle the DET error for function arguments
 * It covers SWS_SoAd_00272 & SWS_SoAd_00273 requirements
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpListenSocketId_uo - Socket identifier of the related local socket resource(Listen socket).
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpConnectedSocketId_uo - Socket identifier of the local socket resource used for the established connection(Established socket).
 * \param   const TcpIp_SockAddrType*
 * \arg     RemoteAddr_cpst - pointer to IP address and port of the remote host.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TcpAcceptedDetChk( VAR( TcpIp_SocketIdType, AUTOMATIC )                TcpIpListenSocketId_uo, \
                                                       VAR( TcpIp_SocketIdType, AUTOMATIC )                TcpIpConnectedSocketId_uo , \
                                                       P2CONST( TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC ) RemoteAddr_cpst )
{
    /* Variable to store index of the socket connection Group */
    VAR(SoAd_SoConIdType, AUTOMATIC)  lIdxSoConGroup_uo;

    /* Get the static group socket index from static socket table */
    lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoAd_DyncSocConfig_ast[SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpListenSocketId_uo]].idxStaticSoc_uo].soConGrpId_uo ;

    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_TCP_ACCEPTED_API_ID, SOAD_E_NOTINIT)

    /* Check whether TcpIpListenSocketId_uo and TcpIpConnectedSocketId_uo are valid or not */
    SOAD_DET_REPORT_ERROR( (( SOAD_TCPIP_TCPSOCKET_MAX <= TcpIpListenSocketId_uo ) || ( SOAD_TCPIP_TCPSOCKET_MAX <= TcpIpConnectedSocketId_uo )), SOAD_TCP_ACCEPTED_API_ID, SOAD_E_INV_SOCKETID )

    /* Check whether RemoteAddr_cpst pointer is valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == RemoteAddr_cpst ), SOAD_TCP_ACCEPTED_API_ID, SOAD_E_PARAM_POINTER )

    /* Check whether RemoteAddr_cpst and connection domain are equal */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].domain_en != RemoteAddr_cpst->domain ), SOAD_TCP_ACCEPTED_API_ID, SOAD_E_INV_ARG )
}
#endif /* ( SOAD_TCP_SERVER_GRP_PRESENT != FALSE ) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /*SOAD_CONFIGURED*/
