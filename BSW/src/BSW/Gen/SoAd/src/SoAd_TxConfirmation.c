

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

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_TxConfirmationDetChk( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpIpSocketId_uo , \
                                                          VAR( uint16, AUTOMATIC )  Length_u16 );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TxConfirmation()
 *
 * \Function description
 * The TCP/IP stack calls this function after the data has been acknowledged by the peer for TCP
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     SocketId - Socket identifier of the related local socket resource.
 * \param   uint16
 * \arg     Length - Number of transmitted data bytes.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_TxConfirmation( VAR( TcpIp_SocketIdType, AUTOMATIC )  SocketId , \
                                             VAR( uint16, AUTOMATIC )  Length )
{
    /* variable to store the index of static socket connection table */
    VAR(SoAd_SoConIdType, AUTOMATIC)    lIdxstatsock_uo;

    /* variable to store index of TxPdu config table  */
    VAR(PduIdType, AUTOMATIC)           lIdxTxPdu_uo;

    /* variable to store the index of dynamic socket connection table */
    VAR(SoAd_SoConIdType, AUTOMATIC)    lIdxDynSocket_uo;

    /* variable to store the Protocol type of socket group */
    VAR(TcpIp_ProtocolType, AUTOMATIC)  lSoConGrpProtocol_en;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    SoAd_TxConfirmationDetChk(SocketId, Length);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialization of Local variables */
        lIdxTxPdu_uo            = SOAD_CFG_PDU_ID_DEFAULT_VALUE;
        lIdxstatsock_uo         = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
        lSoConGrpProtocol_en    = TCPIP_IPPROTO_NONE;

        /* Get the index of dynamic config table by using array and SocketId as index */
        lIdxDynSocket_uo        = SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId];

        /* Condition check: the dynamic socket id should be valid  */
        if( lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo )
        {
            /* Get the "index of the static socket table" from the dynamic socket table  */
            lIdxstatsock_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo ;

            /*Condition check: Index of the static socket should be valid*/
            if(lIdxstatsock_uo < SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo)
            {
                /*Get the protocol type to local variable to access it in multiple places*/
                lSoConGrpProtocol_en = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxstatsock_uo].soConGrpId_uo].soConGrpProtocol_en;

                /* Report DET error if SoAd_TxConfirmation is not called from TCP component, may be called from UDP */
                SOAD_DET_REPORT_ERROR ( (lSoConGrpProtocol_en != TCPIP_IPPROTO_TCP), SOAD_TX_CONFIRMATION_API_ID, SOAD_E_INV_ARG );
            }

            /* Get the "index of the tx pdu config table" from dynamic table */
            lIdxTxPdu_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxTxPduTable_uo;
        }

        /* Condition checks:
         * 1. Confirmation to be called only for TCP sockets, since for UDP sockets, confirmation would be given from SoAd_MainFunction itself
         * 2. Index of the Txpdu config table should be valid*/
        if( ( TCPIP_IPPROTO_TCP == lSoConGrpProtocol_en ) && \
            ( SoAd_CurrConfig_cpst->SoAd_noTxPdus_cuo > lIdxTxPdu_uo ) )
        {
#if (SOAD_NUM_TX_IF_TCP_PDU > 0)
            /* Condition check: The upper layer type should be of type IF */
            if( SOAD_IF == SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lIdxTxPdu_uo].txUpperLayerType_en )
            {
                /****************************************************************************************************************/
                /****************************************** [SWS_SoAd_00545] ****************************************************/
                /****************************************************************************************************************/
                /****************************************************************************************************************/
                /*** In case of a TCP socket connection the SoAd shall call the upper layer with the configured transmit      ***/
                /*** confirmation function (<Up>_[SoAd][If]TxConfirmation>()) within the SoAd_TxConfirmation() callback       ***/
                /*** function after all PDU data (from one or multiple transmit requests) have been confirmed for transmission **/
                /****************************************************************************************************************/
                /****************************************************************************************************************/

                SoAd_IfTcpTxConfirmationToUl(lIdxDynSocket_uo, lIdxTxPdu_uo, Length, FALSE);
            }/* End for: condition check for upper layer type is IF */
            /* If Upper layer Type is TP */
            else
#endif /* SOAD_NUM_TX_IF_TCP_PDU > 0 */
            {
#if (SOAD_TP_TCP_PRESENT != STD_OFF)
                /*condition check: Inform to upper layer only if (socket is TCP AND tcpImmediateTpTxConfirm_u8 is disabled)
                 * if tcpImmediateTpTxConfirm_u8 is enabled, then SoAd has already informed to upper layer before getting SoAd_TxConfirmation.
                 * So, no need to inform again to upper layer */
                if( STD_OFF == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxstatsock_uo].soConGrpId_uo].tcpProtocolConf_cpst->tcpImmediateTpTxConfirm_u8 )
                {
                    /****************************************************************************************************************/
                    /****************************************** [SWS_SoAd_00558] ****************************************************/
                    /****************************************************************************************************************/
                    /****************************************************************************************************************/
                    /*** In case of a TCP socket connection configured with SoAdSocketTcpImmediateTpTxConfirmation set to FALSE   ***/
                    /*** theSoAd shall call the upper layer with the configured transmit confirmation function and E_OK as result ***/
                    /*** within SoAd_TxConfirmation() callback function after all TP PDU data have been confirmed for transmission **/
                    /****************************************************************************************************************/
                    /****************************************************************************************************************/

                    /* call a function to do the calculations of remaining length and inform to upper layer*/
                    SoAd_TpTxConfirmationToUl(lIdxstatsock_uo, lIdxTxPdu_uo, (PduLengthType)Length );
                }
#endif /* (SOAD_TP_TCP_PRESENT != STD_OFF) */
            }
        }/*End of If condition: Check TxConfirmation received for TCP Protocol */
    }/*End of If condition: Check SoAd Module should be Initialized */
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TxConfirmationDetChk()
 *
 * \Function description
 *  This function is called from SoAd_TxConfirmation to handle the DET error for function arguments
 * It covers SWS_SoAd_00269, SWS_SoAd_00270 & SWS_SoAd_00271 requirements
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpSocketId_uo - Socket identifier of the related local socket resource.
 * \param   uint16
 * \arg     Length_u16 - Number of transmitted data bytes.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TxConfirmationDetChk( VAR( TcpIp_SocketIdType, AUTOMATIC )  TcpIpSocketId_uo ,
                                                          VAR( uint16, AUTOMATIC )  Length_u16 )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_TX_CONFIRMATION_API_ID, SOAD_E_NOTINIT )

    /* Check whether TcpIpSocketId_uo is valid or not */
    SOAD_DET_REPORT_ERROR( ( SOAD_TCPIP_TCPSOCKET_MAX <= TcpIpSocketId_uo ), \
                            SOAD_TX_CONFIRMATION_API_ID, SOAD_E_INV_SOCKETID )

    /* Check whether Length_u16 is valid or not */
    SOAD_DET_REPORT_ERROR( ( 0 == Length_u16 ), \
                            SOAD_TX_CONFIRMATION_API_ID, SOAD_E_INV_ARG )
}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
