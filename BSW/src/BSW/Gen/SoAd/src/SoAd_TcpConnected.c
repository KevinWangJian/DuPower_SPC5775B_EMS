

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED
#include "SoAd_Cbk.h"
#include "Det.h"
#include "TcpIp.h"

#include "SoAd_Prv.h"

#if (!defined(TCPIP_AR_RELEASE_MAJOR_VERSION) || (TCPIP_AR_RELEASE_MAJOR_VERSION != SOAD_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - SoAd and TcpIp"
#endif

#if (!defined(TCPIP_AR_RELEASE_MINOR_VERSION) || (TCPIP_AR_RELEASE_MINOR_VERSION != SOAD_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
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

#if ( (SOAD_TCP_CLIENT_PRESENT != FALSE) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
static FUNC( void, SOAD_CODE ) SoAd_TcpConnectedDetChk( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpIpSocketId_uo );
#endif /* (SOAD_TCP_CLIENT_PRESENT != FALSE) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TcpConnected()
 *
 * \Function description
 * The TCP/IP stack calls this function after a socket was requested to connect with
 * TcpIp_TcpConnect() and a TCP connection is confirmed by the peer.
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     Socket identifier of the related local socket resource.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 * \return  void
 * \retval
 *
 ***************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_TcpConnected( VAR( TcpIp_SocketIdType, AUTOMATIC )  SocketId )
{
#if (SOAD_TCP_CLIENT_PRESENT != FALSE)

    /* variable to store index of static soc table */
    VAR(SoAd_SoConIdType, AUTOMATIC)    lIdxStaticSocket_uo;

    /* variable to store index of dynamic soc table */
    VAR(SoAd_SoConIdType, AUTOMATIC)    lIdxDynSocket_uo;

    /* variable to store the Protocol type of socket group */
    VAR(TcpIp_ProtocolType, AUTOMATIC)  lProtocol_en;

    /* variable to store the type of Tcp socket */
    VAR(uint8, AUTOMATIC)               lTcpInitiate_u8;

#if (SOAD_TP_PRESENT != STD_OFF)
    /* Variable to store the index of RxPduTable */
    VAR(PduIdType, AUTOMATIC)           lIdxRxPdu_uo;
#endif  /*SOAD_TP_PRESENT != STD_OFF*/

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    SoAd_TcpConnectedDetChk(SocketId);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /*Initialization of local variables */
        lIdxStaticSocket_uo     = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
        lProtocol_en            = TCPIP_IPPROTO_NONE;
        lTcpInitiate_u8         = STD_OFF;

        /* Get the index of dynamic config table by using array and SocketId as index */
        lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId];

        /* Condition check: the dynamic socket id should be valid  */
        if( lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo )
        {
            /* Get the "index of the static socket table" from the dynamic socket table  */
            lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo ;

            /*Condition check: Index of the static socket should be valid*/
            if(lIdxStaticSocket_uo < SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo)
            {
                /*Get the protocol type to local variable to access it in multiple places*/
                lProtocol_en = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo].soConGrpProtocol_en;

                /*Get the Tcp socket type to local variable to access it in multiple places*/
                lTcpInitiate_u8      = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo].tcpProtocolConf_cpst->tcpInitiate_u8;
            }
        }

        /* process only if protocol is TCP and initiateTCP is enabled (client)*/
        if(( lProtocol_en == TCPIP_IPPROTO_TCP ) && \
           ( lTcpInitiate_u8 == STD_ON ) )
        {
            /* process only if socket state is SOAD_SOCON_RECONNECT and socket substate is SOAD_SOCON_TCPWAITFORREMOTE.
             * if socConSubMode_en is SOAD_SOCON_TCPWAITFORREMOTE, then socConMode_en will be SOAD_SOCON_RECONNECT in all the scenario,
             * so no need of checking the socConMode_en state to SOAD_SOCON_RECONNECT in the below condition */
            if( SOAD_SOCON_TCPWAITFORREMOTE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en )
            {
                /****************************************************************************************************************/
                /****************************************** [SWS_SoAd_00593] ****************************************************/
                /****************************************************************************************************************/
                /****************************************************************************************************************/
                /*** Within SoAd_TcpConnected() SoAd shall change the state of the socket connection to SOAD_SOCON_ONLINE     ***/
                /***                    in case all of the following conditions are true                                      ***/
                /***            (1) Current connection state is not SOAD_SOCON_ONLINE                                         ***/
                /***            (2) TCP socket                                                                                ***/
                /***            (3) SoAdSocketTcpInitiate is set to TRUE                                                      ***/
                /****************************************************************************************************************/

                /* set the socConStatus to SOAD_SOCON_ONLINE,
                 * so that it blocks the using of this socket by other pdus  */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en    = SOAD_SOCON_ACTIVE ;

                /* call a function which shall invoke the upper layer call back for mode change */
                SoAd_ModeChgCallbackToUl(lIdxStaticSocket_uo, lIdxDynSocket_uo, SOAD_SOCON_ONLINE );

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
            }/*End of If condition: Check Socket connection state is not SOAD_SOCON_ONLINE*/
        }
    }/*End of If condition: Check SoAd Module should be Initialized */
#else

    (void)SocketId;

#endif /* SOAD_TCP_CLIENT_PRESENT != STD_OFF */
}

#if ( (SOAD_TCP_CLIENT_PRESENT != FALSE) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TcpConnectedDetChk()
 *
 * \Function description
 *  This function is called from SoAd_TcpConnected to handle the DET error for function arguments
 * It covers SWS_SoAd_00274 & SWS_SoAd_00275 requirements
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpSocketId_uo - Socket identifier of the related local socket resource.
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
static FUNC( void, SOAD_CODE ) SoAd_TcpConnectedDetChk( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpIpSocketId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_TCP_CONNECTED_API_ID, SOAD_E_NOTINIT )

    /* Check whether TcpIpSocketId_uo is valid or not */
    SOAD_DET_REPORT_ERROR( ( SOAD_TCPIP_TCPSOCKET_MAX <= TcpIpSocketId_uo ), SOAD_TCP_CONNECTED_API_ID, SOAD_E_INV_SOCKETID )

}
#endif /* (SOAD_TCP_CLIENT_PRESENT != FALSE) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
