

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

#include "rba_BswSrv.h"

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

/****************************************************************************************************
 * local functions
 ****************************************************************************************************/
/*
 ***************************************************************************************************
 * Prototype for Static functions
 ***************************************************************************************************
 */
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
static FUNC( Std_ReturnType, SOAD_CODE )                SoAd_IdentifyPduRouteSocketFromUdpGrp      ( VAR( TcpIp_SocketIdType, AUTOMATIC )             TcpIpSocketId_uo, \
                                                                                                     P2VAR(SoAd_SoConIdType, AUTOMATIC, AUTOMATIC)    StaticSocketId_puo, \
                                                                                                     P2VAR(SoAd_SoConIdType, AUTOMATIC, AUTOMATIC)    DynSocketId_uo);
#endif /* SOAD_UDP_GRP_PRESENT != STD_OFF */

static FUNC( BufReq_ReturnType, SOAD_CODE )             SoAd_CopyPduToTcpIpBuffer                  ( VAR( SoAd_SoConIdType, AUTOMATIC )         StaticSocketId_uo,
                                                                                                     P2VAR( uint8, AUTOMATIC, AUTOMATIC )       Buffer_pu8,
                                                                                                     VAR( uint16, AUTOMATIC )                   BufferLength_u16 );

static FUNC( void, SOAD_CODE )                          SoAd_CopyPduHdrToTcpIpBuffer                ( VAR(SoAd_SoConIdType, AUTOMATIC)          DynSocketId_uo, \
                                                                                                      VAR(PduIdType, AUTOMATIC)                 TxPduId_uo, \
                                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )      Buffer_pu8);

static FUNC( BufReq_ReturnType, SOAD_CODE )             SoAd_CopyPduDataToTcpIpBuffer               ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo, \
                                                                                                      VAR(SoAd_SoConIdType, AUTOMATIC)          DynSocketId_uo, \
                                                                                                      VAR(PduIdType, AUTOMATIC)                 TxPduId_uo, \
                                                                                                      VAR( PduLengthType, AUTOMATIC )           BufLength_uo, \
                                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )      Buffer_pu8);

#if (SOAD_TP_PRESENT != STD_OFF)
static FUNC( BufReq_ReturnType, SOAD_CODE )             SoAd_CopyTpPduDataToTcpIpBuffer             ( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo, \
                                                                                                      VAR(SoAd_SoConIdType, AUTOMATIC)          DynSocketId_uo, \
                                                                                                      VAR(PduIdType, AUTOMATIC)                 TxPduId_uo, \
                                                                                                      VAR( PduLengthType, AUTOMATIC )           BufLength_uo, \
                                                                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )      Buffer_pu8);
#endif /* SOAD_TP_PRESENT != STD_OFF */

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE )                          SoAd_CopyTxDataDetChk                       ( VAR( TcpIp_SocketIdType, AUTOMATIC )      TcpIpSocketId_uo , \
                                                                                                      P2CONST( uint8, AUTOMATIC, AUTOMATIC )    BufPtr_cpu8);
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */


/**
 **********************************************************************************************************************
 * \Function Name : SoAd_CopyTxData()
 *
 * \Function description
 *  This API  requests to copy data for transmission to the buffer indicated.
 *  This call is triggered by TcpIp_Transmit().
 *  Note: The call to SoAd_CopyTxData() may happen in the context of TcpIp_Transmit().
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     SocketId - Socket identifier of the related local socket resource
 * \param   uint8*
 * \arg     BufPtr - Pointer to buffer for transmission data.
 * \param   uint16
 * \arg     BufLength - Length of provided data buffer
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  BufReq_ReturnType
 * \retval   BUFREQ_OK: Data has been copied to the transmit buffer completely as requested.
 *          BUFREQ_E_BUSY: Request could not be fulfilled as the required amount of Tx data is not available.
 *                          TP layer might retry later on. No data has been copied.
 *          BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
 *
 **********************************************************************************************************************
 */
/* This function shall be called by TcpIp layer, if NULL_PTR is passed in place of data pointer when TcpIp_UdpTransmit or
 * TcpIp_TcpTransmit is called. This shall happen in case of (Header enabled for IF case) and for (TP-irrespective of header enabled)
 *  as Tx buffers are not available in SoAd, SoAd cannot store the data, so it depends on upper layer copyTxData function  */
FUNC( BufReq_ReturnType, SOAD_CODE ) SoAd_CopyTxData( VAR( TcpIp_SocketIdType, AUTOMATIC )  SocketId , \
                                                      P2VAR( uint8, AUTOMATIC, AUTOMATIC )  BufPtr, \
                                                      VAR( uint16, AUTOMATIC )  BufLength)
{
    /* Variable to store the retval */
    VAR(BufReq_ReturnType, AUTOMATIC)                                   lBufReqRetVal_en;

#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
    /* variable to store the group index of the socket*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxSoConGroup_uo;
#endif /* SOAD_UDP_GRP_PRESENT != STD_OFF */

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                                      lRetVal_u8;

    /* variable to store the static socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxStaticSocket_uo;

    /* variable to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

    /* Initialization of return variable */
    lBufReqRetVal_en    = BUFREQ_E_NOT_OK;
    lRetVal_u8          = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    SoAd_CopyTxDataDetChk(SocketId, (const uint8*)BufPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialization of local variables */
        lIdxStaticSocket_uo     = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
        lIdxDynSocket_uo        = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;

#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
        lIdxSoConGroup_uo       = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
#endif /* SOAD_UDP_GRP_PRESENT != STD_OFF */

        /* Get the index of dynamic config table from the given SocketId by using array */
        lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[SocketId];

        /* Condition Check: Dynamic socket index is valid */
        if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
        {
#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
            /* Condition Check: TcpIp socket is is fall in the UDP range, As per the TcpIp design TCP socket id will
             * be in the range of 0 to TCPIP_TCPSOCKETMAX abd UDP socket id will be in the range of TCPIP_TCPSOCKETMAX to TCPIP_SOCKETMAX */
            if( TCPIP_TCPSOCKETMAX <= SocketId )
            {
                /* Get the static socket index from dynamic socket table */
                lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo;

                /* Get the static group socket index from static socket table */
                lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo ;

                /* Condition Check: It is a UDP group socket */
                if( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].maxSoConChannel_uo > 1U ) &&  \
                    ( TCPIP_IPPROTO_UDP == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].soConGrpProtocol_en ) )
                {
                    /* call the below function to get the best match socket id for transmission triggered socket */
                    lRetVal_u8 = SoAd_IdentifyPduRouteSocketFromUdpGrp( SocketId, &lIdxStaticSocket_uo, &lIdxDynSocket_uo );
                }
            }
#endif /* SOAD_UDP_GRP_PRESENT != STD_OFF */

            /* The socket id given by TcpIp layer is not matched with Udp group sockets.
             * So, it can be a part of either Tcp client/server socket or Udp single socket.*/
            if( E_NOT_OK == lRetVal_u8 )
            {
                /* Get the "index of the static socket table" from the dynamic socket table */
                lIdxStaticSocket_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo ;
            }
        }

        /* Condition checks: static socket id is valid */
        /* Condition check: lIdxStaticSocket_uo and lTxPduId_uo should be valid and socket is ONLINE*/
        if( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo  > lIdxStaticSocket_uo )
        {
            /* check Buflength is passed by '0', if it is '0' then set the tpTxTcpBufferAvailable_b flag to FALSE and
             * do the retry from next main function */
            if( 0U == BufLength )
            {
#if (SOAD_TP_TCP_PRESENT != STD_OFF)
                /*set the tcpip buffer busy flag so that retry is enabled in main function.*/
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTxTcpBufferAvailable_b = FALSE;
#endif /* SOAD_TP_TCP_PRESENT != STD_OFF */
            }
            else
            {
#if ( SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 )
                /* --------------------------------------------- */
                /* CopyTxData for nPdu (LAST_IS_BEST)            */
                /* --------------------------------------------- */

                /* If nPduUdpTxTriggered_b in dynamic socket is TRUE, that means that the tranmission is for nPdu */
                /* This is for the case of nPdu with LAST_IS_BEST for which the Pdu data need to be received in SoAd_CopyTxData via UL_TriggerTransmit calls */
                if( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].nPduUdpTxTriggered_b == TRUE )
                {
                    /* Execute the copying of LAST_IS_BEST Puds in TcpIp buffer */
                    lBufReqRetVal_en = SoAd_nPduUdpTxCopyPdusToTcpIpBuffer( lIdxStaticSocket_uo, BufPtr, BufLength );
                }

                /* --------------------------------------------- */
                /* CopyTxData for single Pdu                     */
                /* --------------------------------------------- */

                /* If idxTxPduTable_uo is defined with the value of a single TxPdu */
                else
#endif
                {
                    /* Execute the copying of the single Pdu in TcpIp buffer */
                    lBufReqRetVal_en = SoAd_CopyPduToTcpIpBuffer( lIdxStaticSocket_uo, BufPtr, BufLength );
                }
            }
        }

    }/*End of If condition: Check SoAd Module should be Initialized */

    return lBufReqRetVal_en;
}


#if (SOAD_UDP_GRP_PRESENT != STD_OFF)
/********************************************************************************************************************************
 * \Function Name : SoAd_IdentifyPduRouteSocketFromUdpGrp()
 *
 * \Function description
 *  This function is used to find out the SoAd socket information(static and dynamic socket id's) for the matched
 *  UDP socket Id(TcpIpSocketId_uo) from UDP socket connection Groups.
 *  Note: This is an internal function shall be called from SoAd_CopyTxData() in the context of TcpIp_Transmit().
 *
 *  Parameters (in):
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpSocketId_uo - TcpIp Socket identifier of the related local socket resource
 *
 * Parameters (inout): None
 *
 * Parameters (out):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - SoAd Static Socket identifier of the related local socket resource
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo    - SoAd Dynamic Socket identifier table
 *
 * Return value:
 * \return  boolean
 * \retval  E_OK: If SoAd socket information(static and dynamic socket Id's) is able to be identified from the UDP Group socket.
 *          E_NOT_OK: If TcpIpSocketId_uo is not mapped to any of the UDP Group socket Id .
 *
 **********************************************************************************************************************************
 */
static FUNC( Std_ReturnType, SOAD_CODE ) SoAd_IdentifyPduRouteSocketFromUdpGrp( VAR( TcpIp_SocketIdType, AUTOMATIC )             TcpIpSocketId_uo, \
                                                                                P2VAR(SoAd_SoConIdType, AUTOMATIC, AUTOMATIC)    StaticSocketId_puo, \
                                                                                P2VAR(SoAd_SoConIdType, AUTOMATIC, AUTOMATIC)    DynSocketId_uo)
{
    /* variable to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                    lIdxDynSocket_uo;

    /* variable to store index of the socket connection Group */
    VAR(SoAd_SoConIdType, AUTOMATIC)                    lIdxSoConGroup_uo;

    VAR(SoAd_SoConIdType, AUTOMATIC)                    lStaticSocketIdLoop_uo ;

    /* Variable to hold the index in for loop, only used if TCP server or UDP group configured*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                    lIdxForLoop_uo ;

    /* variable to store Index txpdu table */
    VAR(PduIdType, AUTOMATIC)                           lTxPduId_uo;

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                      lFunctionRetVal_u8;

    /* Initialization of local variables */
    lFunctionRetVal_u8      = E_NOT_OK;

    /* Get the index of dynamic config table from the given SocketId by using array */
    lIdxDynSocket_uo = SoAd_TcpIpSocHandleToDynSockIdx_auo[TcpIpSocketId_uo];

    /* Get the static group socket index from static socket table */
    lIdxSoConGroup_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxStaticSoc_uo].soConGrpId_uo ;

    /* fetch the start socket id from Group table and loop through for max socket couent */
    lStaticSocketIdLoop_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].startSoConIdx_uo;

    for( lIdxForLoop_uo = 0; lIdxForLoop_uo < SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lIdxSoConGroup_uo].maxSoConChannel_uo; lIdxForLoop_uo++)
    {
        /* Get the index of the dynamic soc table */
        lIdxDynSocket_uo             = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lStaticSocketIdLoop_uo].SoAd_Prv_idxDynSocTable_puo);

        /* check dynamic socket index and tcpip socket id are valid */
        if( ( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo ) && \
            ( SOAD_NUM_TCPIP_SOCKETS > SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo ) )
        {
            /* get the TxPdu id from dynamic table and it will be valid if there was transmit request for UL via IF/TP Transmit */
            lTxPduId_uo         =  SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxTxPduTable_uo;

            /* A Udp sockets group contains multiple sockets, so a correct socket to be identified,
            * on which transmission is going on, So check for whose txpduindex is valid*/
            if( (( SoAd_CurrConfig_cpst->SoAd_noTxPdus_cuo >  lTxPduId_uo )
#if ( ( SOAD_IF_PRESENT != STD_OFF ) || (SOAD_TP_UDP_PRESENT != STD_OFF ) )
             && (
#if ( SOAD_IF_PRESENT != STD_OFF )
                   ( SOAD_IF == SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lTxPduId_uo].txUpperLayerType_en )
#endif /* SOAD_IF_PRESENT != STD_OFF */

#if ( ( SOAD_IF_PRESENT != STD_OFF ) && (SOAD_TP_UDP_PRESENT != STD_OFF ) )
                   ||
#endif /* (SOAD_IF_PRESENT != STD_OFF ) && (SOAD_TP_UDP_PRESENT != STD_OFF ) */

#if ( SOAD_TP_UDP_PRESENT != STD_OFF )
                   ( ( SOAD_TP == SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lTxPduId_uo].txUpperLayerType_en )
                  && ( TRUE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpUdpTxTriggered_b ) )
#endif /* SOAD_TP_UDP_PRESENT != STD_OFF */

                )
#endif /* (SOAD_IF_PRESENT != STD_OFF ) || (SOAD_TP_UDP_PRESENT != STD_OFF ) */
                )
#if ( SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 )
                ||
                (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].nPduUdpTxTriggered_b == TRUE)
#endif
             )
            {
                /* load the found socket id's to output parameter */
                *StaticSocketId_puo = lStaticSocketIdLoop_uo;
                *DynSocketId_uo     = lIdxDynSocket_uo;
                lFunctionRetVal_u8  = E_OK;
                /* come out of the loop as the correct socket is recognized */
                break;
            }
        }

        ++lStaticSocketIdLoop_uo;
    }

    return lFunctionRetVal_u8;
}
#endif /* SOAD_UDP_GRP_PRESENT != STD_OFF */


/**********************************************************************************************************************
 * \Function Name : SoAd_CopyPduToTcpIpBuffer()
 *
 * \Function description
 *  This function shall copy the SoAd PDU to requested TCPIP buffer.
 *  Note: This is an internal function shall be called from SoAd_CopyTxData() in the context of TcpIp_Transmit().
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo   - SoAd Static Socket identifier table
 * \param   uint8*
 * \arg     Buffer_pu8          - Pointer to buffer for transmission data
 * \param   uint16
 * \arg     BufLength_uo        - Length of provided data buffer
 *
 * Parameters (inout):
 * \param   uint8*
 * \arg     Buffer_pu8          - Pointer to buffer for transmission data.
 *
 * Parameters (out): None
 *
 * Return value:
 * \return  BufReq_ReturnType
 * \retval   BUFREQ_OK: Data has been copied to the transmit buffer completely as requested.
 *           BUFREQ_E_BUSY: Request could not be fulfilled as the required amount of Tx data is not available.
 *                          TP layer might retry later on. No data has been copied.
 *           BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
 *
 **********************************************************************************************************************
 */
static FUNC( BufReq_ReturnType, SOAD_CODE ) SoAd_CopyPduToTcpIpBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )     StaticSocketId_uo,
                                                                       P2VAR( uint8, AUTOMATIC, AUTOMATIC )   Buffer_pu8,
                                                                       VAR( uint16, AUTOMATIC )               BufferLength_u16 )
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;

    /* Local pointer to store the Dynamic array for given index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst;

    /* Variable to store the retval */
    VAR(BufReq_ReturnType, AUTOMATIC)                                   lBufReqRetVal_en;

    /* variable to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

    /* variable to store Index txpdu table */
    VAR(PduIdType, AUTOMATIC)                                           lTxPduId_uo;

    /* Get static socket Group configuration pointers */
    lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].soConGrpId_uo]);

    /* Get the index of the dynamic soc table */
    lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

    /* Get the "index of the txpdu config table" from the dynamic socket table */
    lTxPduId_uo = lSoAdDyncSocConfig_pst->idxTxPduTable_uo;

    /* Initialization of return variable */
    lBufReqRetVal_en    = BUFREQ_E_NOT_OK;

    /* Condition checks:
     * 1. SoAd header flag is enabled for the socket.
     * 2. Buffer length passed by TcpIp module should be atleast 8 bytes if hesder enabled.
     * 3. check header is not yet copied for same packet(ifTxCopiedLength_uo is zero for IF and
     *    tpTxRemainingLength_uo & tpTxTotPduLen_uo will be same for TP
     */
    if( ( TRUE == lSoAdStaticSoConGrpConfig_cpst->headerEnable_b ) && \
        ( SOAD_PDUHDR_SIZE <= BufferLength_u16 ) && \
        ( FALSE == lSoAdDyncSocConfig_pst->ifTpTxSoAdHdrCopied_b ) )
    {
        /* call the function to copy the SoAd header into TcpIp buffer provided by TcpIp module */
        SoAd_CopyPduHdrToTcpIpBuffer(lIdxDynSocket_uo, lTxPduId_uo, Buffer_pu8);

        /* set ifTpTxSoAdHdrCopied_b flag to TRUE in dynamic table, so that whenever SoAd_copyxTxData()
         * function is called from TcpIp module for the single TcpIp_Tcp/Udp_Transmit(), wecan get to know
         * that header was already copied or not */
        lSoAdDyncSocConfig_pst->ifTpTxSoAdHdrCopied_b = TRUE;

        /* Move the BufPtr to next postion to copy the pduLength*/
        Buffer_pu8 = (Buffer_pu8 + SOAD_PDUHDR_SIZE);

        /* As the SOAD_PDUHDR_SIZE bytes of data is already put in Buffer,
         * we have to subtract the length from the available buffer size*/
        BufferLength_u16 = (BufferLength_u16 - SOAD_PDUHDR_SIZE);

#if ( SOAD_TP_TCP_PRESENT != STD_OFF )
        /*SoAdSocketTcpImmediateTpTxConfirmation  is TRUE and protocol TCP and upper layer TP, means SoAd shall not wait till it gets
         * TxConfirmation from TcpIp layer. It shall update its dynamic table variables now only*/

        /* store the length to be copied in the variable, which shall be used in next main function */
        lSoAdDyncSocConfig_pst->tpTcpCopyTxDataLength_uo = ( ( TCPIP_IPPROTO_TCP == lSoAdStaticSoConGrpConfig_cpst->soConGrpProtocol_en ) && \
                                                             ( STD_ON == lSoAdStaticSoConGrpConfig_cpst->tcpProtocolConf_cpst->tcpImmediateTpTxConfirm_u8 ) ) ? SOAD_PDUHDR_SIZE : 0U;

#endif /* SOAD_TP_TCP_PRESENT != STD_OFF */

        lBufReqRetVal_en = BUFREQ_OK;
    }

    /* SoAd_CopyPduDataToTcpIpBuffer function will be called in the following scenario,
     * 1. if header is disabled
     * 2. If Header is enabled and SoAd header was copied already */
    if( ( FALSE == lSoAdStaticSoConGrpConfig_cpst->headerEnable_b ) || \
        ( ( BufferLength_u16 > 0U ) && \
          ( TRUE == lSoAdDyncSocConfig_pst->ifTpTxSoAdHdrCopied_b ) ) )
    {
        /* call the function to copy the payload into TcpIp buffer provided by TcpIp module */
        lBufReqRetVal_en = SoAd_CopyPduDataToTcpIpBuffer(StaticSocketId_uo, lIdxDynSocket_uo, lTxPduId_uo, (PduLengthType)BufferLength_u16, Buffer_pu8);
    }

    return lBufReqRetVal_en;
}


/**********************************************************************************************************************
 * \Function Name : SoAd_CopyPduHdrToTcpIpBuffer()
 *
 * \Function description
 *  This function shall copy the SoAd PDU Header to requested TCPIP buffer.
 *  Note: This is an internal function shall be called from SoAd_CopyTxData() in the context of TcpIp_Transmit().
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo    - SoAd Dynamic Socket identifier table
 * \param   PduIdType
 * \arg     TxPduId_uo        - Tx PduId(unique identifier referencing to the PDU Routing Table)
 *
 * Parameters (inout):
 * \param   uint8*
 * \arg     Buffer_pu8 - Pointer to buffer for transmission data.
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 **********************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_CopyPduHdrToTcpIpBuffer( VAR(SoAd_SoConIdType, AUTOMATIC)       DynSocketId_uo, \
                                                             VAR(PduIdType, AUTOMATIC)              TxPduId_uo, \
                                                             P2VAR( uint8, AUTOMATIC, AUTOMATIC )   Buffer_pu8)
{
    /* Local pointer to store the Tx Pdu table for given index */
    P2CONST(SoAd_TxPduConfigType_tst, SOAD_VAR, SOAD_VAR)         lSoAdTxPduConfig_cpst ;

    /* Local pointer to store the Dynamic array for given index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)       lSoAdDyncSocConfig_pst ;

    /* Variable to hold the uint32 pdu Header info */
    VAR(uint32, AUTOMATIC)              lPduHeaderId_u32;

    /* Variable to hold the uint32 pdulength info */
    VAR(uint32, AUTOMATIC)              lDataLength_u32;

    /* Initialization of local variables */
    /* Get the Tx Pdu pointer for given index */
    lSoAdTxPduConfig_cpst    = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[TxPduId_uo]);

    /* copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

    /* Endian conversion before putting onto the network */
    lPduHeaderId_u32 = lSoAdDyncSocConfig_pst->txPduHeaderId_u32;

#if (SOAD_TP_PRESENT != STD_OFF )
    /* Condition check: Check for upper layer type hould be TP type*/
    if( SOAD_TP == lSoAdTxPduConfig_cpst->txUpperLayerType_en )
    {
        /* calculate the remaining length to be transmitted except the PDU header */
        lSoAdDyncSocConfig_pst->tpTxRemainingLength_uo -= (PduLengthType)SOAD_PDUHDR_SIZE;

        /* Update the Transmitted pdu length information into the variable lDataLength_u32, this information
         * is stored previously when SoAd_TpTransmit is called along with header length
         * So tpTxRemainingLength_uo has to be subtracted by 8 bytes before copying the length field */
        lDataLength_u32 = ( uint32 )lSoAdDyncSocConfig_pst->tpTxRemainingLength_uo;
    }
    /*If the upper layer of type IF*/
    else
#endif /* SOAD_TP_PRESENT != STD_OFF */
    {
        /* Update the Transmitted pdu length information into the variable lDataLength_u32 */
        lDataLength_u32 = ( uint32 )lSoAdDyncSocConfig_pst->txPduInfoPtr_cpst->SduLength ;
    }/* End for: Condition check for the upper layer type */

    SoAd_InsertPduHdrToBuffer(lPduHeaderId_u32, lDataLength_u32, Buffer_pu8);
}

/***********************************************************************************************************************
 * \Function Name : SoAd_CopyPduDataToTcpIpBuffer()
 *
 * \Function description
 *  This function shall copy the SoAd PDU data to requested TCPIP buffer.
 *  Note: This is an internal function shall be called from SoAd_CopyTxData() in the context of TcpIp_Transmit().
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - SoAd Static Socket identifier of the related local socket resource
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo    - SoAd Dynamic Socket identifier table
 * \param   PduIdType
 * \arg     TxPduId_uo        - Tx PduId(unique identifier referencing to the PDU Routing Table)
 * \param   PduLengthType
 * \arg     BufLength_uo - Length of provided data buffer
 *
 * Parameters (inout):
 * \param   uint8*
 * \arg     Buffer_pu8 - Pointer to buffer for transmission data.
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  BufReq_ReturnType
 * \retval   BUFREQ_OK: Data has been copied to the transmit buffer completely as requested.
 *           BUFREQ_E_BUSY: Request could not be fulfilled as the required amount of Tx data is not available.
 *                          TP layer might retry later on. No data has been copied.
 *           BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
 *
 ***********************************************************************************************************************
 */
static FUNC( BufReq_ReturnType, SOAD_CODE ) SoAd_CopyPduDataToTcpIpBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )   StaticSocketId_uo, \
                                                                           VAR(SoAd_SoConIdType, AUTOMATIC)     DynSocketId_uo, \
                                                                           VAR(PduIdType, AUTOMATIC)            TxPduId_uo, \
                                                                           VAR( PduLengthType, AUTOMATIC )      BufLength_uo, \
                                                                           P2VAR( uint8, AUTOMATIC, AUTOMATIC ) Buffer_pu8)
{
    /* Local pointer to store the Tx Pdu table for given index */
    P2CONST(SoAd_TxPduConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdTxPduConfig_cpst ;

    /* Local pointer to store the Dynamic array for given index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst ;

#if ( SOAD_IF_PRESENT != STD_OFF )
    /* Local pointer to store the TxPduInfo pointer */
    P2CONST(PduInfoType, SOAD_VAR, SOAD_VAR)                            lTxPduInfoPtr_cpst ;
#endif /* SOAD_IF_PRESENT != STD_OFF */

    /* Variable to store the retval */
    VAR(BufReq_ReturnType, AUTOMATIC)                                   lBufReqRetVal_en;

    /*Initialization of variables */
    /* Get the Tx Pdu pointer for given index */
    lSoAdTxPduConfig_cpst           = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[TxPduId_uo]);

    /* copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst          =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

#if ( SOAD_IF_PRESENT != STD_OFF )
    /* copy the global pointer to local pointer fro further processing */
    lTxPduInfoPtr_cpst              = lSoAdDyncSocConfig_pst->txPduInfoPtr_cpst;
#endif /* SOAD_IF_PRESENT != STD_OFF */

    lBufReqRetVal_en                = BUFREQ_E_NOT_OK;

#if ( SOAD_IF_PRESENT != STD_OFF )
    /* Condition check : Upper layer type should be IF */
    /* Condition check : if the upper layer type is IF, then SoAd shall not call the upper layer to copy the data,
     * As SoAd already has buffer pointer given by upper layer, it uses SoAd_MemCpy for copying data */
    if( SOAD_IF == lSoAdTxPduConfig_cpst->txUpperLayerType_en )
    {
        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00543]*****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** The TcpIp module will retrieve the PDU data within the context of the TcpIp transmit call by using        ***/
        /** SoAd_CopyTxData() where the SoAd shall copy (the requested part of) the PDU to the memory specified       ***/
        /**             by parameter BufPtr                                                                           ***/
        /****************************************************************************************************************/
        /****************************************************************************************************************/

        /* Condition check: Buffer size provided by the lower layer should be greater than
         * the data size to be copied */
        if( BufLength_uo >= lTxPduInfoPtr_cpst->SduLength )
        {
            /* Load the pdu data into buffer of the Lower layer*/
            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
            (void)rba_BswSrv_MemCopy( Buffer_pu8 , ( lTxPduInfoPtr_cpst->SduDataPtr ), \
                                                    (uint16)lTxPduInfoPtr_cpst->SduLength );

        }
        else
        {
            /* Load the pdu data into buffer of the Lower layer*/
            /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
            (void)rba_BswSrv_MemCopy( Buffer_pu8 , \
                          lTxPduInfoPtr_cpst->SduDataPtr + lSoAdDyncSocConfig_pst->ifTxCopiedLength_uo, \
                          BufLength_uo );

            /* Update the buffer length*/
            lSoAdDyncSocConfig_pst->ifTxCopiedLength_uo += BufLength_uo;
        }

        /* update the return value with BUFREQ_OK */
        lBufReqRetVal_en = BUFREQ_OK;
    }
    else
#endif /* SOAD_IF_PRESENT != STD_OFF */

    /* Condition check: upper layer type is TP, then SoAd shall call upper layer to copy the data into TcpIp given buffer*/
    {
#if (SOAD_TP_PRESENT != STD_OFF)

        lBufReqRetVal_en = SoAd_CopyTpPduDataToTcpIpBuffer(StaticSocketId_uo,
                                                           DynSocketId_uo,
                                                           TxPduId_uo,
                                                           BufLength_uo,
                                                           Buffer_pu8);
#endif /* SOAD_TP_PRESENT != STD_OFF */
    }

    return lBufReqRetVal_en;
}

#if (SOAD_TP_PRESENT != STD_OFF)
/***********************************************************************************************************************
 * \Function Name : SoAd_CopyPduDataToTcpIpBuffer()
 *
 * \Function description
 *  This function shall copy the SoAd TP PDU data to requested TCPIP buffer.
 *  Note: This is an internal function shall be called from SoAd_CopyTxData() in the context of TcpIp_Transmit().
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - SoAd Static Socket identifier of the related local socket resource
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo    - SoAd Dynamic Socket identifier table
 * \param   PduIdType
 * \arg     TxPduId_uo        - Tx PduId(unique identifier referencing to the PDU Routing Table)
 * \param   PduLengthType
 * \arg     BufLength_uo - Length of provided data buffer
 *
 * Parameters (inout):
 * \param   uint8*
 * \arg     Buffer_pu8 - Pointer to buffer for transmission data.
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  BufReq_ReturnType
 * \retval   BUFREQ_OK: Data has been copied to the transmit buffer completely as requested.
 *           BUFREQ_E_BUSY: Request could not be fulfilled as the required amount of Tx data is not available.
 *                          TP layer might retry later on. No data has been copied.
 *           BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
 *
 ***********************************************************************************************************************
 */
static FUNC( BufReq_ReturnType, SOAD_CODE ) SoAd_CopyTpPduDataToTcpIpBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )   StaticSocketId_uo, \
                                                                             VAR(SoAd_SoConIdType, AUTOMATIC)     DynSocketId_uo, \
                                                                             VAR(PduIdType, AUTOMATIC)            TxPduId_uo, \
                                                                             VAR( PduLengthType, AUTOMATIC )      BufLength_uo, \
                                                                             P2VAR( uint8, AUTOMATIC, AUTOMATIC ) Buffer_pu8)
{
#if ( (SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0) || ( SOAD_TP_TCP_PRESENT != STD_OFF ) )
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;
#endif /* (SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0) || ( SOAD_TP_TCP_PRESENT != STD_OFF ) */

    /* Local pointer to store the Tx Pdu table for given index */
    P2CONST(SoAd_TxPduConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdTxPduConfig_cpst ;

    /* Local pointer to store the Dynamic array for given index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst ;

#if (SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0)
    P2CONST(uint8, SOAD_CONST, SOAD_CONST)                              lSoAdTpUdpTxSocketBuffer_cpu8;
#endif /* SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0 */

#if (SOAD_TP_PRESENT != STD_OFF)
    /* Local pointer to store the TP Copy TxData callback pointer for given index */
    P2CONST(SoAd_TpcopyTxDataCallbacks_tst, SOAD_VAR, SOAD_VAR)         lSoAdTpCopyTxDataCallbacks_cpst ;

    /* Structure variable to store destination buffer and the number of bytes to copy*/
    VAR(PduInfoType, AUTOMATIC)                                         lPduInfo_st;

    /* Indicates the remaining number of bytes that are available in the PduR Tx buffer */
    VAR(PduLengthType, AUTOMATIC)                                       lAvailableLen_uo;
#endif /* SOAD_TP_PRESENT != STD_OFF */

    /* Variable to store the retval */
    VAR(BufReq_ReturnType, AUTOMATIC)                                   lBufReqRetVal_en;

    /*Initialization of variables */
#if ( (SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0) || ( SOAD_TP_TCP_PRESENT != STD_OFF ) )
    /* Get static socket Group configuration pointers */
    lSoAdStaticSoConGrpConfig_cpst  = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].soConGrpId_uo]);
#endif /* (SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0) || ( SOAD_TP_TCP_PRESENT != STD_OFF ) */

    /* Get the Tx Pdu pointer for given index */
    lSoAdTxPduConfig_cpst           = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[TxPduId_uo]);

    /* copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst          =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

#if (SOAD_TP_PRESENT != STD_OFF)
    /* copy the callback function address to local pointer for local access */
    lSoAdTpCopyTxDataCallbacks_cpst = &(SoAd_CurrConfig_cpst->SoAdTp_copyTxDataCallbacks_cpst[lSoAdTxPduConfig_cpst->idxTpCopyTxDataCallback_u8]);
    lAvailableLen_uo                = 0 ;
#endif /* SOAD_TP_PRESENT != STD_OFF */

    lBufReqRetVal_en                = BUFREQ_E_NOT_OK;

#if (SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0)
    /****************************************************************************************************************/
    /****************************************** [SWS_SoAd_00555] ****************************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /** In case of a UDP socket connection the SoAd shall copy (the requested part of) the PDU from the SoAd TP   ***/
    /**************** transmit buffer to the memory specified by parameter BufPtr within SoAd_CopyTxData(). *********/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /* If protocol is UDP, copy the data from TP UDP Transmit buffer to TcpIp buffer */
    if( ( TCPIP_IPPROTO_UDP == lSoAdStaticSoConGrpConfig_cpst->soConGrpProtocol_en) && \
        ( SOAD_CFG_TP_UDP_TXBUFFER_DEFAULT_VALUE > SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoAd_DyncSocConfig_ast[DynSocketId_uo].idxStaticSoc_uo].tpUdpTxBuffIdx_uo ) )
    {
        /* Copy the TP UDP Transit buffer pointer to local pointer for further use */
        lSoAdTpUdpTxSocketBuffer_cpu8 = (SoAd_CurrConfig_cpst->SoAdTp_UdpTransmitBufferInfo_cpu8)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoAd_DyncSocConfig_ast[DynSocketId_uo].idxStaticSoc_uo].tpUdpTxBuffIdx_uo].tpUdpTxBuffer_pu8;

        /* Copy the data from TP UDP Transmit buffer to TcpIp buffer */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        (void)rba_BswSrv_MemCopy(Buffer_pu8,
                     &(lSoAdTpUdpTxSocketBuffer_cpu8[0]),
                     (PduLengthType)BufLength_uo);

        lSoAdDyncSocConfig_pst->tpTxRemainingLength_uo = 0;

        lBufReqRetVal_en = BUFREQ_OK;
    }
    else
#endif /* SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0 */

    {
        lPduInfo_st.SduDataPtr  = Buffer_pu8;
        lPduInfo_st.SduLength   = BufLength_uo;

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00556] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** In case of a TCP socket connection the SoAd shall forward the request to the related upper layer by *********/
        /** calling <Up>_[SoAd][Tp]CopyTxData() to copy (the requested part of) the PDU to the memory specified *********/
        /************************************* by parameter BufPtr within SoAd_CopyTxData(). ****************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/

        /* Condition check: Upper layer should provide a valid function for copy Tx data */
        if( NULL_PTR != lSoAdTpCopyTxDataCallbacks_cpst->soAdCopyTxDataCbk_pfn)
        {
        /* Currently SoAd not using ReTry feature in the upper layer.
         * As TP_NORETRY is removed from Autosar 4.0 Rev 3, no need of setting the state TpDataState to NO-RETRY
         * SWS_SoAd_00137: retry : Parameter is always set to NULL_PTR as SoAd does not support re-transmit.
         * Re-transmission on TCP level is backed with data already buffered in the SoAd, so there is no need to re-query the upper layer. */
            /* call upper layer to get the data to be copied into the buffer given by TCPIP layer */

            lBufReqRetVal_en = lSoAdTpCopyTxDataCallbacks_cpst->soAdCopyTxDataCbk_pfn( \
                                                        lSoAdTxPduConfig_cpst->ulTxPduId_uo,(const PduInfoType*)&lPduInfo_st,NULL_PTR,&lAvailableLen_uo);

            /* Condition check: The buffer request is NOT_OK, then terminate the transmission */
            if( BUFREQ_E_NOT_OK == lBufReqRetVal_en )
            {
                /****************************************************************************************************************/
                /********************************* [SWS_SoAd_00651] && [SWS_SoAd_00652] *****************************************/
                /****************************************************************************************************************/
                /* call a function which resets all dynamic table parameters related to TP and inform upper layer */
                /* If the protocol is UDP : SWS_SoAd_00652: the related socket connection is not closed in this case*/
                SoAd_ResetTpTxDyncParameters(DynSocketId_uo, TxPduId_uo, E_NOT_OK);

#if ( SOAD_TP_TCP_PRESENT != STD_OFF )
                /* If the protocol is TCP : SWS_SoAd_00651: socket shall be closed */
                if( TCPIP_IPPROTO_TCP == lSoAdStaticSoConGrpConfig_cpst->soConGrpProtocol_en )
                {
                    /* set the flag to process the requriment SWS_SoAd_00651 and SWS_SoAd_006544 */
                    /* a. disable further transmission or reception for this socket connection */
                    /* b. close the socket connection in the next SoAd_MainFunction() */

                    /****************************************************************************************************************/
                    /********************************[SWS_SoAd_00651]: Step(a)*******************************************************/
                    /****************************************************************************************************************/
                    /****************************************************************************************************************/
                    /****************** SoAd shall disable further transmission or reception for this socket connection *************/
                    /****************************************************************************************************************/

                    /* set the global variables to skip the further transmission and reception */
                    lSoAdDyncSocConfig_pst->discardNewTxRxReq_b  = TRUE;

                    /****************************************************************************************************************/
                    /********************************[SWS_SoAd_00651]: Step(b)*******************************************************/
                    /****************************************************************************************************************/
                    /****************************************************************************************************************/
                    /****************** SoAd shall close the socket connection in the next SoAd_MainFunction() **********************/
                    /****************************************************************************************************************/

                    /* set the state such that, the socket shall be closed in next main function */
                    lSoAdDyncSocConfig_pst->socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD ;
                }
#endif /* SOAD_TP_TCP_PRESENT != STD_OFF */

            }/* End for : Condition check for request NOT_OK from upper layer side */
            else
            {
                /* calculate the remaining length to be transmitted */
                lSoAdDyncSocConfig_pst->tpTxRemainingLength_uo -= BufLength_uo;

#if ( SOAD_TP_TCP_PRESENT != STD_OFF )
                /*SoAdSocketTcpImmediateTpTxConfirmation  is TRUE and protocol TCP and upper layer TP, means SoAd shall not wait till it gets
                 * TxConfirmation from TcpIp layer. It shall update its dynamic table variables now only*/
                if( ( TCPIP_IPPROTO_TCP == lSoAdStaticSoConGrpConfig_cpst->soConGrpProtocol_en ) && \
                    ( STD_ON == lSoAdStaticSoConGrpConfig_cpst->tcpProtocolConf_cpst->tcpImmediateTpTxConfirm_u8 ) )
                {
                    /* store the length to be copied in the variable, which shall be used in next main function */
                    lSoAdDyncSocConfig_pst->tpTcpCopyTxDataLength_uo += BufLength_uo;
                }
#endif /* SOAD_TP_TCP_PRESENT != STD_OFF */
            }

        }

    }/* End for : Condition check Upper layer should provide a valid function for copy Tx data */

    return lBufReqRetVal_en;
}
#endif /* SOAD_TP_PRESENT != STD_OFF */

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_CopyTxDataDetChk()
 *
 * \Function description
 *  This function is called from SoAd_CopyTxData to handle the DET error for function arguments
 * It covers SWS_SoAd_00632 & SWS_SoAd_00633 requirements
 *
 * \param   TcpIp_SocketIdType
 * \arg     TcpIpSocketId_uo - Socket identifier of the related local socket resource
 * \param   const uint8*
 * \arg     BufPtr_cpu8 - Pointer to buffer for transmission data.
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
static FUNC( void, SOAD_CODE ) SoAd_CopyTxDataDetChk( VAR( TcpIp_SocketIdType, AUTOMATIC )    TcpIpSocketId_uo , \
                                                      P2CONST( uint8, AUTOMATIC, AUTOMATIC )  BufPtr_cpu8)
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_COPY_TX_DATA_API_ID, SOAD_E_NOTINIT )

    /* Check whether SocketId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SOAD_NUM_TCPIP_SOCKETS <= TcpIpSocketId_uo ), SOAD_COPY_TX_DATA_API_ID, SOAD_E_INV_SOCKETID )

    /* Check whether BufPtr pointer is valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == BufPtr_cpu8 ), SOAD_COPY_TX_DATA_API_ID, SOAD_E_PARAM_POINTER )
}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
