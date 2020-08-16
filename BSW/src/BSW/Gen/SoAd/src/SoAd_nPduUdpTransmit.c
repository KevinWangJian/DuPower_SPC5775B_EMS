

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED

#if ( SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 )
#include "TcpIp.h"
#include "Det.h"

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
 * Static function declaration
 ***************************************************************************************************
 */
#define SOAD_START_SEC_CODE
#include "SoAd_MemMap.h"

static FUNC( SoAd_IfTransmitReqStatus_ten, SOAD_CODE ) SoAd_nPduUdpTransmitTriggerNeverQueued    ( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                                   P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRouteDest_cpst );

static FUNC( SoAd_IfTransmitReqStatus_ten, SOAD_CODE ) SoAd_nPduUdpTransmitTriggerAlways         ( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                                   VAR(PduLengthType, AUTOMATIC)                         PduLength_uo,
                                                                                                   P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRouteDest_cpst );

static FUNC( void, SOAD_CODE )                  SoAd_StoreCurrentPdu                    ( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                          P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRouteDest_cpst );

static FUNC( void, SOAD_CODE )                  SoAd_SavePduToPduDescriptor             ( VAR(SoAd_SoConIdType, AUTOMATIC)      StaticSocketId_uo,
                                                                                          P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC) PduRouteDest_cpst);

static FUNC( uint16, SOAD_CODE )                SoAd_GetTotalTxLengthFromPduDescriptor  ( VAR(SoAd_SoConIdType, AUTOMATIC)      StaticSocketId_uo );

static FUNC( void, SOAD_CODE )                  SoAd_nPduUdpTxDataTransmitPostAction    ( VAR(SoAd_SoConIdType, AUTOMATIC)      StaticSocketId_uo,
                                                                                          VAR(boolean, AUTOMATIC)               TransmissionFinished_b);

static FUNC( boolean, SOAD_CODE )               SoAd_ValidatePduTransmittedViaAllDest   ( VAR(SoAd_SoConIdType, AUTOMATIC)      StaticSocketId_uo,
                                                                                          VAR(PduIdType, AUTOMATIC)             NumberOfPduRouteDests_uo,
                                                                                          P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRouteDests_cpst);

static FUNC( void, SOAD_CODE )                  SoAd_nPduUdpTxCleanPduDescriptor        ( VAR(SoAd_SoConIdType, AUTOMATIC)      StaticSocketId_uo );


/*
 ***************************************************************************************************
 * Local functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** SoAd_ResetnPduUdpTx()   - This function reset all the fields of the nPdu Udp Tx Table                                       **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           None                                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( void, SOAD_CODE ) SoAd_ResetnPduUdpTx( VAR(SoAd_SoConIdType, AUTOMATIC) StaticSocketId_uo )
{
    /* Declare local variables */
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)           lnPduUdpTransmitInfo_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                            lIdxnPduIdFieldLoop_u8;

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* --------------------------------------------- */
    /* Reset all fields                              */
    /* --------------------------------------------- */

    lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 = 0xFFFFFFFFU;
    lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16 = 0U;

    /* loop through for each entry in the mapped Pdu descriptor to reset it */
    for( lIdxnPduIdFieldLoop_u8 = 0; lIdxnPduIdFieldLoop_u8 < lnPduUdpTransmitInfo_pst->nPduUdpTxPduIdSize_cu8; lIdxnPduIdFieldLoop_u8++ )
    {
        /* Reset the Pdu descriptor entry with default values */
        lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lIdxnPduIdFieldLoop_u8].nPduUdpTxPduId_uo = SOAD_CFG_PDU_ID_DEFAULT_VALUE;
        lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lIdxnPduIdFieldLoop_u8].nPduUdpTxPduDataLength_uo = 0U;
        lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lIdxnPduIdFieldLoop_u8].nPduUdpTxPduHeaderId_u32 = 0U;
    }
}


/*********************************************************************************************************************************/
/** SoAd_nPduUdpTransmit()   - This function shall store the PDU in nPdu table and calls TcpIp_UdpTransmit() if required        **/
/** This function is called in the context of SoAd_IfTransmit()                                                                 **/
/** If SoAd_IfTransmit is called with SOAD_TRIGGER_NEVER configuration, then it shall copy the pdu data to                      **/
/** socket specicific buffer if buffer was available, else it shall call the TcpIp_UdpTransmit( ) api to send the               **/
/** buffered data to Udp. Suppose If there was no data stored in buffer and buffer is not enough to store the                   **/
/** new request, then it will return SOAD_IF_TRANSMISSION_E_NOT_OK to caller till UL.                                           **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/** PduLength_uo            - No of bytes to be transmitted                                                                     **/
/** PduRouteDest_cpst       - A pointer to a structure of PduRouteDest to which packet needs to be transmitted                  **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           SOAD_IF_TRANSMISSION_OK        - The request has been accepted and transmitted to lower layer       **/
/**                                                        successfully,                                                        **/
/**                         SOAD_IF_TRANSMISSION_E_NOT_OK  - The request has not been accepted                                  **/
/**                                                        (not able to transmit as well as to buffer)                          **/
/**                         SOAD_IF_NPDU_BUFFERING_OK      - The request has been accepted, but is is not transmitted to        **/
/**                                                        lower layer, instead it is stored since pdu is TRIGGER_NEVER         **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( SoAd_IfTransmitReqStatus_ten, SOAD_CODE ) SoAd_nPduUdpTransmit( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                      VAR(PduLengthType, AUTOMATIC)                         PduLength_uo,
                                                                      P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRouteDest_cpst )
{
    /* Declare local variables */
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(SoAd_IfTransmitReqStatus_ten, AUTOMATIC)                        lIfTransmitReqStatus_en;

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* Initialization local variables declared above */
    lIfTransmitReqStatus_en = SOAD_IF_TRANSMISSION_E_NOT_OK;

    /* --------------------------------------------- */
    /* nPdu TRIGGER_NEVER                            */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00547] */
    /* In case the nPdu feature is used for a socket connection and TriggerMode is set to TRIGGER_NEVER for the actual PDU (SoAdPduRouteDest), */
    /* SoAd shall store the PDU for the socket connection (instead of calling TcpIp_UdpTransmit()). (SRS_Eth_00116) */

    /* Check triggerTransmission_en is configured as SOAD_TRIGGER_NEVER for the PduRouteDest */
    /* If so, Pdu request or Pdu data would be stored depending of the semantics */
    if( PduRouteDest_cpst->triggerTransmission_en == SOAD_TRIGGER_NEVER )
    {
        /* --------------------------------------------- */
        /* Semantics is SOAD_COLLECT_QUEUED              */
        /* --------------------------------------------- */

        /* Semantics QUEUED is configured when nPduUdpTxBuffer_cpu8 is a valid pointer */
        /* (with the semantics QUEUED, it is mandatory to have a configured nPdu buffer to store the sequence of Pdus to transmit) */
        if( lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8 != NULL_PTR )
        {
            /* Call sub function to execute processing for TRIGGER_NEVER with Semantics QUEUED */
            lIfTransmitReqStatus_en = SoAd_nPduUdpTransmitTriggerNeverQueued(StaticSocketId_uo, PduRouteDest_cpst);
        }

        /* --------------------------------------------- */
        /* Semantics is SOAD_COLLECT_LAST_IS_BEST        */
        /* --------------------------------------------- */

        /* [SWS_SoAd_00747] */
        /* In case the nPdu feature is used for a socket connection and the related PDU parameter SoAdTxPduCollectionSemantics is set to SOAD_COLLECT_LAST_IS_BEST, */
        /* SoAd shall only store the transmission request instead of the PDU data. When SoAd needs to provide the PDU data, SoAd shall retrieve the data from the upper layer */
        /* by calling <Up>_[SoAd][If]TriggerTransmit(). (SRS_Eth_00116) */

        /* Semantics LAST_IS_BEST is configured when nPduUdpTxBuffer_cpu8 is a NULL_PTR */
        /* (with Semantics LAST_IS_BEST, only the trnamission request need to be stored) */
        else
        {
            /* The only thing to do is to store the current Pdu in Pdu descriptor */
            SoAd_StoreCurrentPdu(StaticSocketId_uo, PduRouteDest_cpst);

            /* Set the return value to indicate that the Pdu is stored */
            lIfTransmitReqStatus_en = SOAD_IF_NPDU_BUFFERING_OK;
        }
    }

    /* --------------------------------------------- */
    /* nPdu TRIGGER_ALWAYS                           */
    /* --------------------------------------------- */

    /* If triggerTransmission_en is configured as SOAD_TRIGGER_ALWAYS for the PduRouteDest */
    else
    {
        /* Call sub function to execute processing for TRIGGER_ALWAYS */
        lIfTransmitReqStatus_en = SoAd_nPduUdpTransmitTriggerAlways(StaticSocketId_uo, PduLength_uo, PduRouteDest_cpst);
    }

    return lIfTransmitReqStatus_en;
}


#if ( SOAD_TIMEOUT_HANDLING_ENABLED == STD_ON )
/*********************************************************************************************************************************/
/** SoAd_nPduUdpTxSendAllPdus()   - This function shall call the TcpIp_UdpTransmit() api to tranmit the buffer pdu              **/
/** data to lower layer and update the globals tables accordingly                                                               **/
/** This function is called in the context of SoAd_MainFunction()                                                               **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           None                                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( void, SOAD_CODE ) SoAd_nPduUdpTxSendAllPdus( VAR( SoAd_SoConIdType, AUTOMATIC ) StaticSocketId_uo )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(TcpIp_SockAddrInetType, AUTOMATIC)                              lRemoteSockAddrInet_st;
    VAR(TcpIp_SockAddrInet6Type, AUTOMATIC)                             lRemoteSockAddrInet6_st;
    P2VAR(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)                     lRemoteSockAddr_pst;
    VAR(TcpIp_ReturnType, AUTOMATIC)                                    lRetVal_UdpTransmit_en;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;
    VAR(uint16, AUTOMATIC)                                              lTotalLength_u16;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get the index of the dynamic soc table */
    lIdxDynSocket_uo = (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo);

    /* Get static socket Group configuration pointers */
    lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo]);

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* --------------------------------------------- */
    /* Check if Pdus are stored in nPdu descriptor   */
    /* --------------------------------------------- */

    /* If there is a Pdu id in the first entry of the descriptor */
    if( lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[0].nPduUdpTxPduId_uo != SOAD_CFG_PDU_ID_DEFAULT_VALUE )
    {
        /* --------------------------------------------- */
        /* Check Tx allowed                              */
        /* --------------------------------------------- */

        /* If Tx are allowed on the socket connection */
        /* (means there is no IF or TP transmission ongoing) */
        if( (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b == FALSE)         &&
#if (SOAD_TP_PRESENT != STD_OFF )
            (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTransmissionOnGoing_b == FALSE)     &&
#endif /* (SOAD_TP_PRESENT != STD_OFF ) */
#if (SOAD_IF_PRESENT != STD_OFF )
            (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].ifTransmissionOnGoing_b == FALSE)     &&
#endif
            (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxTxPduTable_uo == SOAD_CFG_PDU_ID_DEFAULT_VALUE) )
        {
            /* Load the remoteAddr structure values from the socket connections */
            /* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            SOAD_BUILD_SOCK_ADDR( ((SoAd_DyncSocConfigType_tst *) &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo])),
                                  lSoAdStaticSoConGrpConfig_cpst->domain_en,
                                  ((TcpIp_SockAddrInetType *) &lRemoteSockAddrInet_st),
                                  ((TcpIp_SockAddrInet6Type *) &lRemoteSockAddrInet6_st),
                                  lRemoteSockAddr_pst )

            /* [SWS_SoAd_00690] */
            /* SoAd shall preserve the order of PDUs transmitted via a socket connection that uses the nPdu feature. Pdus collected on the sender side first shall be extracted */
            /* and indicated to the receivers on the receiving side first as well. (SRS_Eth_00116) */

            /* --------------------------------------------- */
            /* Semantics is SOAD_COLLECT_QUEUED              */
            /* --------------------------------------------- */

            /* Semantics QUEUED is configured when nPduUdpTxBuffer_cpu8 is a valid pointer */
            /* (with the semantics QUEUED, the content of the nPduUdpTx buffer will be transmitted) */
            if( lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8 != NULL_PTR )
            {
                /* Call to initiate the transmission by TcpIp_UdpTransmit */
                /* Transmit all the data present in the nPduUdpTx buffer */
                lRetVal_UdpTransmit_en = TcpIp_UdpTransmit( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                                            &(lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8[0]),
                                                            lRemoteSockAddr_pst,
                                                            lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16 );

                /* Check the return value of TcpIp_UdpTransmit() */
                if(  lRetVal_UdpTransmit_en == TCPIP_OK )
                {
                    /* Transmission terminated */
                    /* (TxConfirmation flag will be set in that sub function for all the TxPdu that have been transmitted from nPdu) */
                    /* (Function is called with argument TRUE because the actions for SWS_SoAd_00582 and SWS_SoAd_00644 need to be done) */
                    SoAd_nPduUdpTxDataTransmitPostAction(StaticSocketId_uo, TRUE);
                }
                else
                {
                    /* It was not possible to transmit the content of the nPduUdpTx buffer */
                    /* Nothing more is done and the Pdus remains in the buffer so that the sending can be tried again when nPdu timer will expire in next MainFunction */
                }
            }

            /* --------------------------------------------- */
            /* Semantics is SOAD_COLLECT_LAST_IS_BEST        */
            /* --------------------------------------------- */

            /* [SWS_SoAd_00747] */
            /* In case the nPdu feature is used for a socket connection and the related PDU parameter SoAdTxPduCollectionSemantics is set to SOAD_COLLECT_LAST_IS_BEST, */
            /* SoAd shall only store the transmission request instead of the PDU data. When SoAd needs to provide the PDU data, SoAd shall retrieve the data from the upper layer */
            /* by calling <Up>_[SoAd][If]TriggerTransmit(). (SRS_Eth_00116) */

            /* Semantics LAST_IS_BEST is configured when nPduUdpTxBuffer_cpu8 is a NULL_PTR */
            /* (with Semantics LAST_IS_BEST, The content of each Pdu will be get via <Up>_[SoAd][If]TriggerTransmit()) */
            else
            {
                /* Get the total length that need to be transmitted by reading the Pdu descriptor */
                lTotalLength_u16 = SoAd_GetTotalTxLengthFromPduDescriptor( StaticSocketId_uo );

                /* Set a flag in the dynamic socket to indicate to the SoAd_CopyTxData that the data from UL need to be get for nPdu feature (via UL_TriggerTransmit calls) */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].nPduUdpTxTriggered_b = TRUE;

                /* Call to initiate the transmission by TcpIp_UdpTransmit */
                /* Call TcpIp layer with NULL pointer. So, SoAd_CopyTxData function will be called to insert the SoAd header and to get the UL data via <Up>_[SoAd][If]TriggerTransmit() */
                lRetVal_UdpTransmit_en = TcpIp_UdpTransmit( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                                            NULL_PTR,
                                                            lRemoteSockAddr_pst,
                                                            lTotalLength_u16 );

                /* Reset the nPduUdpTx triggered flag to FALSE */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].nPduUdpTxTriggered_b = FALSE;

                /* Check the return value of TcpIp_UdpTransmit() */
                if(  lRetVal_UdpTransmit_en == TCPIP_OK )
                {
                    /* Transmission terminated */
                    /* (TxConfirmation flag will be set in that sub function for all the TxPdu that have been transmitted from nPdu) */
                    /* (Function is called with argument TRUE because the actions for SWS_SoAd_00582 and SWS_SoAd_00644 need to be done) */
                    SoAd_nPduUdpTxDataTransmitPostAction(StaticSocketId_uo, TRUE);
                }
                else
                {
                    /* [SWS_SoAd_00734] */
                    /* In case the nPdu feature is used for a socket connection, the related PDU parameter SoAdTxPduCollectionSemantics is set to SOAD_COLLECT_LAST_IS_BEST and */
                    /* the upper layer doesn't provide all the requested data via <Up>_[SoAd][If]TriggerTransmit() in the context of SoAd_CopyTxData, SoAd shall abort the */
                    /* transmission and return E_NOT_OK. (SRS_Eth_00116) */

                    /* It was not possible to transmit the content of the nPduUdpTx table so SoAd need to abort the transmission (flush all the stored Pdus and reset timer)*/
                    /* TxConfirmation will not be given to UL for the stored Pdus */
                    SoAd_nPduUdpTxCleanPduDescriptor(StaticSocketId_uo);
                    lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 = 0xFFFFFFFFU;
                }
            }
        }
    }

    return;
}
#endif  /*  SOAD_TIMEOUT_HANDLING_ENABLED == STD_ON ) */


/*********************************************************************************************************************************/
/** SoAd_nPduUdpTxCopyPdusToTcpIpBuffer()   - This function shall copy the LAST_IS_BEST Pdus to the TcpIp buffer                **/
/** This function is called in the context of SoAd_CopyTxData()                                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/** Buffer_pu8              - Pointer to Lower Layer buffer where the Pdus shall be copied                                      **/
/** BufferLength_u16        - Length of the Lower Layer buffer                                                                  **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           BufReq_ReturnType                                                                                   **/
/**                             BUFREQ_OK: Data has been copied to the transmit buffer completely as requested.                 **/
/**                             BUFREQ_E_NOT_OK: Data has not been copied. Request failed.                                      **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
FUNC( BufReq_ReturnType, SOAD_CODE ) SoAd_nPduUdpTxCopyPdusToTcpIpBuffer( VAR( SoAd_SoConIdType, AUTOMATIC )        StaticSocketId_uo,
                                                                          P2VAR( uint8, AUTOMATIC, AUTOMATIC )      Buffer_pu8,
                                                                          VAR( uint16, AUTOMATIC )                  BufferLength_u16 )
{
    /* Declare local variables */
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)           lnPduUdpTransmitInfo_pst;
    P2CONST(SoAd_TxPduConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdTxPduConfig_cpst;
    VAR(BufReq_ReturnType, AUTOMATIC)                           lBufReqRetVal_en;
    VAR(PduInfoType, AUTOMATIC)                                 lPduInfo_st;
    VAR(PduIdType, SOAD_VAR)                                    lPduId_uo;
    VAR(uint8, SOAD_VAR)                                        lPduIdLoopIdx_u8;
    VAR( Std_ReturnType, AUTOMATIC )                            lRetVal_u8;
    VAR( boolean, AUTOMATIC )                                   lErrorFlag_b;

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* Initialization of return variable */
    lBufReqRetVal_en = BUFREQ_E_NOT_OK;

    /* Initialize the error flag to FALSE */
    lErrorFlag_b = FALSE;

    /* [SWS_SoAd_00747] */
    /* In case the nPdu feature is used for a socket connection and the related PDU parameter SoAdTxPduCollectionSemantics is set to SOAD_COLLECT_LAST_IS_BEST, */
    /* SoAd shall only store the transmission request instead of the PDU data. When SoAd needs to provide the PDU data, SoAd shall retrieve the data from the upper layer */
    /* by calling <Up>_[SoAd][If]TriggerTransmit(). (SRS_Eth_00116) */

    /* Loop through for all PduId loaded in the descriptor while no error occurs */
    for(lPduIdLoopIdx_u8 = 0U; ((lPduIdLoopIdx_u8 < lnPduUdpTransmitInfo_pst->nPduUdpTxPduIdSize_cu8) && (lErrorFlag_b == FALSE)); lPduIdLoopIdx_u8++)
    {
        /* Fetch the Tx Pdu Id from nPduUdpTx descriptor one by one */
        lPduId_uo = lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduId_uo;

        /* If the slot is occupied by a PduId and TriggerTransmit is configured */
        if( (lPduId_uo != SOAD_CFG_PDU_ID_DEFAULT_VALUE)    &&
            (SoAd_CurrConfig_cpst->SoAd_IfTriggerTransmitCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lPduId_uo].idxTriggerTransmitCallback_u8].TriggerTransmit_pfn != NULL_PTR) )
        {
            /* [SWS_SoAd_00735] */
            /* In case the nPdu feature is used for a socket connection and all PDUs are configured with SoAdTxPduCollectionSemantics set to */
            /* SOAD_COLLECT_LAST_IS_BEST, SoAd shall only transmit the last instance of each PDU with the same PduId in the sequence their first */
            /* instances were requested for transmission. (SRS_Eth_00116) */

            /* If the remaining length is big enough to copy the Pdu header and the Pdu data */
            if( (uint32)(BufferLength_u16) >= (uint32)(SOAD_PDUHDR_SIZE + lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo) )
            {
                /* --------------------------------------------- */
                /* Copy Pdu header to TcpIp buffer               */
                /* --------------------------------------------- */

                /* Call the internal function to insert the SoAd Header Id and length to the buffer which shall be transmitted later */
                SoAd_InsertPduHdrToBuffer( lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduHeaderId_u32,
                                           lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo,
                                           Buffer_pu8 );

                /* Move the BufPtr to next postion */
                Buffer_pu8 += SOAD_PDUHDR_SIZE;

                /* As the SOAD_PDUHDR_SIZE bytes is put in Buffer,
                 * we have to subtract the length from the available buffer size */
                BufferLength_u16 -= SOAD_PDUHDR_SIZE;


                /* --------------------------------------------- */
                /* Copy Pdu data to TcpIp buffer                 */
                /* --------------------------------------------- */

                /* Get the Tx Pdu config */
                lSoAdTxPduConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lPduId_uo]);

                /* Initialize the PduInfo structure */
                lPduInfo_st.SduDataPtr = Buffer_pu8;
                lPduInfo_st.SduLength = lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo;

                /* TriggerTranmit callback is used to get the UL data for the Pdu */
                lRetVal_u8 = SoAd_CurrConfig_cpst->SoAd_IfTriggerTransmitCallbacks_cpst[lSoAdTxPduConfig_cpst->idxTriggerTransmitCallback_u8].TriggerTransmit_pfn(
                                                                           lSoAdTxPduConfig_cpst->ulTxPduId_uo, &lPduInfo_st);

                /* Check if TriggerTransmit suceded and provided all the requested data */
                if( (lRetVal_u8 == E_OK) && (lPduInfo_st.SduLength == lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo) )
                {
                    /* Move the BufPtr to next postion */
                    Buffer_pu8 += lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo;

                    /* As the PduData bytes is put in Buffer,
                    * we have to subtract the length from the available buffer size */
                    BufferLength_u16 -= lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo;
                }

                /* If an error occured or TriggerTransmit did not provide all the requested data */
                else
                {
                    /* [SWS_SoAd_00734] */
                    /* In case the nPdu feature is used for a socket connection, the related PDU parameter SoAdTxPduCollectionSemantics is set to SOAD_COLLECT_LAST_IS_BEST and */
                    /* the upper layer doesn't provide all the requested data via <Up>_[SoAd][If]TriggerTransmit() in the context of SoAd_CopyTxData, SoAd shall abort the transmission and */
                    /* return E_NOT_OK. (SRS_Eth_00116) */

                    /* Set the error flag */
                    lErrorFlag_b = TRUE;
                }
            }
            else
            {
                /* Set error flag */
                /* Buffer which is given by TcpIp layer is not big enough */
                lErrorFlag_b = TRUE;
            }
        }
    }

    /* --------------------------------------------- */
    /* Check for success                             */
    /* --------------------------------------------- */

    /* If no error occured and the remaining length of the TcpIp buffer is 0 (that means all Pdus have been received from UL) */
    if( (lErrorFlag_b == FALSE) && (BufferLength_u16 == 0U) )
    {
        lBufReqRetVal_en = BUFREQ_OK;
    }

    return lBufReqRetVal_en;
}


/*
 ***************************************************************************************************
 * Static functions
 ***************************************************************************************************
 */

/*********************************************************************************************************************************/
/** SoAd_nPduUdpTransmitTriggerNeverQueued()   - This function shall store the PDU in nPdu table and calls TcpIp_UdpTransmit()  **/
/**                                            if required                                                                      **/
/** This function is called in the context of SoAd_IfTransmit()                                                                 **/
/** If SoAd_IfTransmit is called with SOAD_TRIGGER_NEVER configuration and Semantics is QUEUED, then SoAd need to save in       **/
/** in nPduUdpTx buffer the Pdu header + Pdu data to be transmitted                                                             **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/** PduLength_uo            - No of bytes to be transmitted                                                                     **/
/** PduRouteDest_cpst       - A pointer to a structure of PduRouteDest to which packet needs to be transmitted                  **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           SOAD_IF_TRANSMISSION_OK        - The request has been accepted and transmitted to lower layer       **/
/**                                                        successfully,                                                        **/
/**                         SOAD_IF_TRANSMISSION_E_NOT_OK  - The request has not been accepted                                  **/
/**                                                        (not able to transmit as well as to buffer)                          **/
/**                         SOAD_IF_NPDU_BUFFERING_OK      - The request has been accepted, but is is not transmitted to        **/
/**                                                        lower layer, instead it is stored since pdu is TRIGGER_NEVER         **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( SoAd_IfTransmitReqStatus_ten, SOAD_CODE ) SoAd_nPduUdpTransmitTriggerNeverQueued( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                               P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRouteDest_cpst )
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(TcpIp_ReturnType, AUTOMATIC)                                    lRetVal_UdpTransmit_en;
    VAR(SoAd_IfTransmitReqStatus_ten, AUTOMATIC)                        lIfTransmitReqStatus_en;
    VAR(TcpIp_SockAddrInetType, AUTOMATIC)                              lRemoteSockAddrInet_st;
    VAR(TcpIp_SockAddrInet6Type, AUTOMATIC)                             lRemoteSockAddrInet6_st;
    P2VAR(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)                     lRemoteSockAddr_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;
    VAR(uint16, AUTOMATIC)                                              lFreeBuffSize_u16;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get "the dynamic socket index value" from the static socket table  */
    lIdxDynSocket_uo = ( *lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo );

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* Initialization local variables declared above */
    lIfTransmitReqStatus_en = SOAD_IF_TRANSMISSION_E_NOT_OK;

    /* --------------------------------------------- */
    /* Free length is available                      */
    /* --------------------------------------------- */

    /* Get the free buffer size which can be used to copy the pdu data for the given length */
    lFreeBuffSize_u16 = (lnPduUdpTransmitInfo_pst->nPduUdpTxBufferSize_cu16 - lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16);

    /* Check enough buffer is available to copy the entire requested pdu data into nPduUdpTxBuffer */
    if( lFreeBuffSize_u16 >= (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength + SOAD_PDUHDR_SIZE) )
    {
        /* Call the below internal function to store the Pdu header + data into nPduUdpTx buffer */
        SoAd_StoreCurrentPdu(StaticSocketId_uo, PduRouteDest_cpst);

        /* Set the return value to indicate that the Pdu is stored */
        lIfTransmitReqStatus_en = SOAD_IF_NPDU_BUFFERING_OK;
    }

    /* --------------------------------------------- */
    /* Not enough free length                        */
    /* --------------------------------------------- */
    else
    {
        /* --------------------------------------------- */
        /* Pdu already present in buffer                 */
        /* --------------------------------------------- */

        /* [SWS_SoAd_00549] */
        /* In case the nPdu feature is used for a socket connection and TriggerMode is set to TRIGGER_NEVER for the current PDU (SoAdPduRouteDest) */
        /* and the resulting PDU data and headers would exceed SoAdSocketnPduUdpTxBufferMin, SoAd shall first transmit all PDUs stored for the socket */
        /* connection by calling TcpIp_UdpTransmit() and then store the PDU for the socket connection.  (SRS_Eth_00116) */

        /* Check already some pdu data is available in buffer, if so, then SoAd has to transmit the buffered data as 1st step and then new pdu data shall be stored into the buffer. */
        if(0U < lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16)
        {
            /* [SWS_SoAd_00690] */
            /* SoAd shall preserve the order of PDUs transmitted via a socket connection that uses the nPdu feature. */
            /* Pdus collected on the sender side first shall be extracted and indicated to the receivers on the receiving */
            /* side first as well. (SRS_Eth_00116) */

            /* Get static socket Group configuration pointers */
            lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo]);

            /* Load the remoteAddr structure values from the socket connections */
            /* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
            SOAD_BUILD_SOCK_ADDR( ((SoAd_DyncSocConfigType_tst *) &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo])),
                                  lSoAdStaticSoConGrpConfig_cpst->domain_en,
                                  ((TcpIp_SockAddrInetType *) &lRemoteSockAddrInet_st),
                                  ((TcpIp_SockAddrInet6Type *) &lRemoteSockAddrInet6_st),
                                  lRemoteSockAddr_pst )

            /* Call to initiate the transmission by TcpIp_UdpTransmit */
            lRetVal_UdpTransmit_en = TcpIp_UdpTransmit( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo, \
                                                        &(lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8[0]), \
                                                        lRemoteSockAddr_pst, \
                                                        lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16 );

            /* Check buffered data was transmitted successfully */
            if( TCPIP_OK == lRetVal_UdpTransmit_en )
            {
                /* Post Pdu transmission for the stored Pdu */
                /* (TxConfirmation flag will be set in that sub function for all the TxPdu that have been transmitted from nPdu) */
                /* (Function is called with argument FALSE because the actions for SWS_SoAd_00582 and SWS_SoAd_00644 shall not be done here, they will be done in SoAd_IfTransmit() itself) */
                SoAd_nPduUdpTxDataTransmitPostAction(StaticSocketId_uo, FALSE);

                /* --------------------------------------------- */
                /* Try again to store Pdu                        */
                /* --------------------------------------------- */

                /* Get the free buffer size which can be used to copy the pdu data for the given length */
                lFreeBuffSize_u16 = (lnPduUdpTransmitInfo_pst->nPduUdpTxBufferSize_cu16 - lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16);

                /* Check enough buffer is available to copy the entire requested pdu data into nPduUdpTxBuffer */
                if( lFreeBuffSize_u16 >= (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength + SOAD_PDUHDR_SIZE) )
                {
                    /* call the below internal function to store the new Pdu header + data into nPduUdpTx buffer */
                    SoAd_StoreCurrentPdu(StaticSocketId_uo, PduRouteDest_cpst);

                    /* Set the return value to indicate that the Pdu is stored */
                    lIfTransmitReqStatus_en = SOAD_IF_NPDU_BUFFERING_OK;
                }
                else
                {
                    /* If enough buffer is not availble to store the pdu data into nPduUdpTxBuffer */
                    /* Suppose, if buffer is not available to store the single pdu at all, then SoAd shall report DET with
                     * SOAD_E_NOBUFS. As a action item for this DET, integrator has to configure the enough buffer for the particular
                     * socket.
                     */
                    SOAD_DET_REPORT_ERROR( (TRUE), SOAD_IF_TRANSMIT_API_ID, SOAD_E_NOBUFS )
                }
            }
            else
            {
                /* It was not possible to transmit the content of the nPduUdpTx buffer */
                /* Nothing more is done and the Pdus remains in the buffer so that the sending can be tried again when nPdu timer will expire */
                /* Returns SOAD_IF_TRANSMISSION_E_NOT_OK so that IfTransmit will know that the current transmission is a failure and will return E_NOT_OK to UL */
            }
        }

        /* --------------------------------------------- */
        /* No Pdu present in buffer                      */
        /* --------------------------------------------- */
        else
        {
            /* If buffer is not available to store the single pdu at all, then SoAd shall report DET with
             * SOAD_E_NOBUFS. As a action item for this DET, integrator has to configure the enough buffer for the particular
             * socket.
             */
            SOAD_DET_REPORT_ERROR( (TRUE), SOAD_IF_TRANSMIT_API_ID, SOAD_E_NOBUFS )
        }
    }

    return lIfTransmitReqStatus_en;
}


/*********************************************************************************************************************************/
/** SoAd_nPduUdpTransmitTriggerAlways()   - This function shall execute the transmission of the Pdu stored in nPdu table and    **/
/**                                       the current Pdu                                                                       **/
/** This function is called in the context of SoAd_IfTransmit()                                                                 **/
/** If SoAd_IfTransmit is called with SOAD_TRIGGER_ALWAYS configuration, then SoAd need to execute the transmission to Udp      **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/** PduLength_uo            - No of bytes to be transmitted                                                                     **/
/** PduRouteDest_cpst       - A pointer to a structure of PduRouteDest to which packet needs to be transmitted                  **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           SOAD_IF_TRANSMISSION_OK        - The request has been accepted and transmitted to lower layer       **/
/**                                                        successfully,                                                        **/
/**                         SOAD_IF_TRANSMISSION_E_NOT_OK  - The request has not been accepted                                  **/
/**                                                        (not able to transmit as well as to buffer)                          **/
/**                         SOAD_IF_NPDU_BUFFERING_OK      - The request has been accepted, but is is not transmitted to        **/
/**                                                        lower layer, instead it is stored since pdu is TRIGGER_NEVER         **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( SoAd_IfTransmitReqStatus_ten, SOAD_CODE ) SoAd_nPduUdpTransmitTriggerAlways( VAR(SoAd_SoConIdType, AUTOMATIC)                      StaticSocketId_uo,
                                                                                          VAR(PduLengthType, AUTOMATIC)                         PduLength_uo,
                                                                                          P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)   PduRouteDest_cpst )
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(TcpIp_ReturnType, AUTOMATIC)                                    lRetVal_UdpTransmit_en;
    VAR(SoAd_IfTransmitReqStatus_ten, AUTOMATIC)                        lIfTransmitReqStatus_en;
    VAR(TcpIp_SockAddrInetType, AUTOMATIC)                              lRemoteSockAddrInet_st;
    VAR(TcpIp_SockAddrInet6Type, AUTOMATIC)                             lRemoteSockAddrInet6_st;
    P2VAR(TcpIp_SockAddrType, AUTOMATIC, AUTOMATIC)                     lRemoteSockAddr_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;
    VAR(uint16, AUTOMATIC)                                              lFreeBuffSize_u16;
    VAR(uint16, AUTOMATIC)                                              lTotalLength_u16;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get "the dynamic socket index value" from the static socket table  */
    lIdxDynSocket_uo = ( *lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo );

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* Initialization local variables declared above */
    lIfTransmitReqStatus_en = SOAD_IF_TRANSMISSION_E_NOT_OK;

    /* --------------------------------------------- */
    /* Build remote address                          */
    /* --------------------------------------------- */

    /* Get static socket Group configuration pointers */
    lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo]);

    /* Load the remoteAddr structure values from the socket connections */
    /* MR12 RULE 11.3 VIOLATION: The cast is safe because the generic type is used by the caller function and extracts the info depending on the domain. */
    SOAD_BUILD_SOCK_ADDR( ((SoAd_DyncSocConfigType_tst *) &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo])),
                          lSoAdStaticSoConGrpConfig_cpst->domain_en,
                          ((TcpIp_SockAddrInetType *) &lRemoteSockAddrInet_st),
                          ((TcpIp_SockAddrInet6Type *) &lRemoteSockAddrInet6_st),
                          lRemoteSockAddr_pst )


    /* --------------------------------------------- */
    /* Semantics is SOAD_COLLECT_QUEUED              */
    /* --------------------------------------------- */

    /* Semantics QUEUED is configured when nPduUdpTxBuffer_cpu8 is a valid pointer */
    /* (with the semantics QUEUED, the content of the nPduUdpTx buffer will be transmitted) */
    if( lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8 != NULL_PTR )
    {
        /* --------------------------------------------- */
        /* Free length is available                      */
        /* --------------------------------------------- */

        /* Get the free buffer size which can be used to copy the pdu data for the given length */
        lFreeBuffSize_u16 = (lnPduUdpTransmitInfo_pst->nPduUdpTxBufferSize_cu16 - lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16);

        /* Check enough buffer is available to copy the entire requested pdu data into nPduUdpTxBuffer */
        if( lFreeBuffSize_u16 >= (SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength + SOAD_PDUHDR_SIZE) )
        {
            /* [SWS_SoAd_00548] */
            /* In case the nPdu feature is used for a socket connection and TriggerMode is set to TRIGGER_ALWAYS for the current PDU (SoAdPduRouteDest) and */
            /* the resulting PDU data and headers don't exceed SoAdSocketnPduUdpTxBufferMin, SoAd shall transmit all PDUs stored for the socket connection (if any) and */
            /* the current PDU by calling TcpIp_UdpTransmit(). (SRS_Eth_00116) */

            /* Call the below internal function to store the Pdu data into nPduUdpTxBuffer */
            SoAd_StoreCurrentPdu(StaticSocketId_uo, PduRouteDest_cpst);

            /* Call to initiate the transmission by TcpIp_UdpTransmit */
            lRetVal_UdpTransmit_en = TcpIp_UdpTransmit( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                                        &(lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8[0]),
                                                        lRemoteSockAddr_pst,
                                                        lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16 );
            if(TCPIP_OK == lRetVal_UdpTransmit_en )
            {
                /* Post Pdu transmission for the stored Pdu */
                /* (TxConfirmation flag will be set in that sub function for all the TxPdu that have been transmitted from nPdu) */
                /* (Function is called with argument FALSE because the actions for SWS_SoAd_00582 and SWS_SoAd_00644 shall not be done here, they will be done in SoAd_IfTransmit() itself) */
                SoAd_nPduUdpTxDataTransmitPostAction(StaticSocketId_uo, FALSE);

                /* Transmission is successful */
                lIfTransmitReqStatus_en = SOAD_IF_TRANSMISSION_OK;
            }
            else
            {
                /* It was not possible to transmit the content of the nPduUdpTx buffer */
                /* Nothing more is done and the Pdus remains in the buffer so that the sending can be tried again when nPdu timer will expire */
                /* Returns SOAD_IF_TRANSMISSION_E_NOT_OK so that IfTransmit will know that the current transmission is a failure and will return E_NOT_OK to UL */
            }
        }

        /* --------------------------------------------- */
        /* Not enough free length                        */
        /* --------------------------------------------- */
        else
        {
            /* [SWS_SoAd_00685] */
            /* In case the nPdu feature is used for a socket connection and TriggerMode is set to TRIGGER_ALWAYS for the current PDU (SoAdPduRouteDest) and */
            /* the resulting PDU data and headers would exceed SoAdSocketnPduUdpTxBufferMin, SoAd shall first transmit all PDUs stored for the socket connection */
            /* (if any) by calling TcpIp_UdpTransmit() and then the current PDU by calling TcpIp_UdpTransmit() once more. (SRS_Eth_00116) */

            /* Call to initiate the transmission by TcpIp_UdpTransmit */
            lRetVal_UdpTransmit_en = TcpIp_UdpTransmit( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                                        &(lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8[0]),
                                                        lRemoteSockAddr_pst,
                                                        lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16 );
            if(TCPIP_OK == lRetVal_UdpTransmit_en )
            {
                /* Post Pdu transmission for the stored Pdu */
                /* (TxConfirmation flag will be set in that sub function for all the TxPdu that have been transmitted from nPdu) */
                /* (Function is called with argument FALSE because the actions for SWS_SoAd_00582 and SWS_SoAd_00644 shall not be done here, they will be done in SoAd_IfTransmit() itself) */
                SoAd_nPduUdpTxDataTransmitPostAction(StaticSocketId_uo, FALSE);

                /* [SWS_SoAd_00540] */
                /* In case of a UDP socket connection the SoAd shall (if not specified otherwise) call TcpIp_UdpTransmit() with SocketId and remote address */
                /* specified in the SocketConnection and the PDU length specified in the SoAd_IfTransmit()call as TotalLength. */

                /* If header is enabled call TcpIp layer with NULL pointer. So, SoAd_CopyTxData function will be called to insert the SoAd header */
                /* call to initiate the transmission by TcpIp_UdpTransmit */
                lRetVal_UdpTransmit_en = TcpIp_UdpTransmit( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                                           NULL_PTR,
                                                           lRemoteSockAddr_pst,
                                                           (uint16)PduLength_uo );

                if(TCPIP_OK == lRetVal_UdpTransmit_en )
                {
                    /* Transmission is successful */
                    lIfTransmitReqStatus_en = SOAD_IF_TRANSMISSION_OK;
                }
                else
                {
                    /* It is not possible to execute the current If transmission */
                    /* Returns SOAD_IF_TRANSMISSION_E_NOT_OK so that IfTransmit will know that the current transmission is a failure and will return E_NOT_OK to UL */
                }
            }
            else
            {
                /* It was not possible to transmit the content of the nPduUdpTx buffer */
                /* Nothing more is done and the Pdus remains in the buffer so that the sending can be tried again when nPdu timer will expire */
                /* Returns SOAD_IF_TRANSMISSION_E_NOT_OK so that IfTransmit will know that the current transmission is a failure and will return E_NOT_OK to UL */
            }
        }
    }

    /* --------------------------------------------- */
    /* Semantics is SOAD_COLLECT_LAST_IS_BEST        */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00747] */
    /* In case the nPdu feature is used for a socket connection and the related PDU parameter SoAdTxPduCollectionSemantics is set to SOAD_COLLECT_LAST_IS_BEST, */
    /* SoAd shall only store the transmission request instead of the PDU data. When SoAd needs to provide the PDU data, SoAd shall retrieve the data from the upper layer */
    /* by calling <Up>_[SoAd][If]TriggerTransmit(). (SRS_Eth_00116) */

    /* Semantics LAST_IS_BEST is configured when nPduUdpTxBuffer_cpu8 is a NULL_PTR */
    /* (with Semantics LAST_IS_BEST, The content of each Pdu will be get via <Up>_[SoAd][If]TriggerTransmit()) */
    else
    {
        /* --------------------------------------------- */
        /* Store current Pdu                             */
        /* --------------------------------------------- */

        /* Store the current Pdu in the Pdu descriptor */
        SoAd_StoreCurrentPdu(StaticSocketId_uo, PduRouteDest_cpst);

        /* --------------------------------------------- */
        /* Execute Transmit                              */
        /* --------------------------------------------- */

        /* Get the total length that need to be transmitted by reading the Pdu descriptor */
        lTotalLength_u16 = SoAd_GetTotalTxLengthFromPduDescriptor( StaticSocketId_uo );

        /* Set a flag in the dynamic socket to indicate to the SoAd_CopyTxData that the data from UL need to be get for nPdu feature (via UL_TriggerTransmit calls) */
        SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].nPduUdpTxTriggered_b = TRUE;

        /* [SWS_SoAd_00540] */
        /* In case of a UDP socket connection the SoAd shall (if not specified otherwise) call TcpIp_UdpTransmit() with SocketId and remote address */
        /* specified in the SocketConnection and the PDU length specified in the SoAd_IfTransmit()call as TotalLength. */

        /* Call TcpIp layer with NULL pointer. So, SoAd_CopyTxData function will be called to insert the SoAd header and to get the UL data via <Up>_[SoAd][If]TriggerTransmit() */
        /* Call to initiate the transmission by TcpIp_UdpTransmit */
        lRetVal_UdpTransmit_en = TcpIp_UdpTransmit( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socketHandleTcpIp_uo,
                                                   NULL_PTR,
                                                   lRemoteSockAddr_pst,
                                                   lTotalLength_u16 );

        /* Reset the nPduUdpTx triggered flag to FALSE */
        SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].nPduUdpTxTriggered_b = FALSE;

        if(TCPIP_OK == lRetVal_UdpTransmit_en )
        {
            /* Post Pdu transmission for the stored Pdu */
            /* (TxConfirmation flag will be set in that sub function for all the TxPdu that have been transmitted from nPdu) */
            /* (Function is called with argument FALSE because the actions for SWS_SoAd_00582 and SWS_SoAd_00644 shall not be done here, they will be done in SoAd_IfTransmit() itself) */
            SoAd_nPduUdpTxDataTransmitPostAction(StaticSocketId_uo, FALSE);

            /* Transmission is successful */
            lIfTransmitReqStatus_en = SOAD_IF_TRANSMISSION_OK;
        }
        else
        {
            /* [SWS_SoAd_00734] */
            /* In case the nPdu feature is used for a socket connection, the related PDU parameter SoAdTxPduCollectionSemantics is set to SOAD_COLLECT_LAST_IS_BEST and */
            /* the upper layer doesn't provide all the requested data via <Up>_[SoAd][If]TriggerTransmit() in the context of SoAd_CopyTxData, SoAd shall abort the */
            /* transmission and return E_NOT_OK. (SRS_Eth_00116) */

            /* It was not possible to transmit the content of the nPduUdpTx table so SoAd need to abort the transmission (flush all the stored Pdus and reset timer)*/
            /* TxConfirmation will not be given to UL for the stored Pdus */
            SoAd_nPduUdpTxCleanPduDescriptor(StaticSocketId_uo);
            lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 = 0xFFFFFFFFU;

            /* Returns SOAD_IF_TRANSMISSION_E_NOT_OK so that IfTransmit will know that the current transmission is a failure and will return E_NOT_OK to UL */
        }
    }

    return lIfTransmitReqStatus_en;
}


/*********************************************************************************************************************************/
/** SoAd_StoreCurrentPdu()   - This function shall store the current Pdu in nPdu table                                          **/
/**                          and also start the timer for nPduUdpTxBuffer after pdu is copied to buffer.                        **/
/** This function is called in the context of SoAd_IfTransmit()                                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/** PduRouteDest_cpst       - A pointer to a structure of PduRouteDest to which packet needs to be transmitted                  **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           None                                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, SOAD_CODE ) SoAd_StoreCurrentPdu( VAR(SoAd_SoConIdType, AUTOMATIC)                       StaticSocketId_uo,
                                                     P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)    PduRouteDest_cpst )

{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get static socket Group configuration pointers */
    lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo]);

    /* Get "the dynamic socket index value" from the static socket table  */
    lIdxDynSocket_uo = ( *lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo );

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* [SWS_SoAd_00547] */
    /* In case the nPdu feature is used for a socket connection and TriggerMode is set to TRIGGER_NEVER for the actual PDU (SoAdPduRouteDest), */
    /* SoAd shall store the PDU for the socket connection (instead of calling TcpIp_UdpTransmit()). (SRS_Eth_00116) */

    /* --------------------------------------------- */
    /* Copy Pdu header + data in nPduUdpTx buffer    */
    /* --------------------------------------------- */

    /* If the nPduUdpTx buffer is configured (the semantics is QUEUED) */
    /* (for the semantics LAST_IS_BEST, no need to save the Pdu header + data, only the transmission request need to be stored in the Pdu descriptor) */
    if( lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8 != NULL_PTR )
    {
        /* [SWS_SoAd_00691] */
        /* In case the nPdu feature is used for a socket connection and and all PDUs are configured with SoAdTxPduCollectionSemantics set to SOAD_COLLECT_QUEUED, */
        /* SoAd shall transmit all PDUs individually, also PDUs with the same PduId. (SRS_Eth_00116) */

        /* Call the internal function to insert the SoAd Header Id and length to the buffer which shall be transmitted later */
        SoAd_InsertPduHdrToBuffer(PduRouteDest_cpst->txPduHeaderId_u32,
                                  SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength,
                                  &(lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8[lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16]) );

        /* Increment the nPduUdpTxBuffCopiedLen_u16 by SOAD_PDUHDR_SIZE(8 bytes) after copying the soad header to nPdu buffer */
        lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16 += SOAD_PDUHDR_SIZE;

        /* Copy the entire pdu data to nPdu buffer by doing the memcpy for the given length */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        (void)rba_BswSrv_MemCopy( &(lnPduUdpTransmitInfo_pst->nPduUdpTxBuffer_cpu8[lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16]),
                                  SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduDataPtr,
                                  SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength );

        /* Increment the nPduUdpTxBuffCopiedLen_u16 by Pdu length after copying the pdu data to nPdu buffer */
        lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16 += SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength;
    }


    /* --------------------------------------------- */
    /* Maintain timer                                */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00696] */
    /* SoAd shall maintain a nPdu specific timer for each socket connection using the nPdu feature. (SRS_Eth_00116) */

    /* If TxUdpTriggerTimeout is set in the configureation */
    if( 0U != PduRouteDest_cpst->txUdpTriggerTimeout_32 )
    {
        /*[SWS_SoAd_00697] */
        /* If a PDU with TriggerMode set to TRIGGER_NEVER with a specific SoAdTxUdpTriggerTimeout is transmitted SoAd shall set the nPdu specific timer to */
        /* the value of SoAdTxUdpTriggerTimeout if the timer is not running or if it is lower than the current nPdu specific timer value. (SRS_Eth_00116) */
        lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 = \
                        ((0xFFFFFFFFU == lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32) || (lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 > PduRouteDest_cpst->txUdpTriggerTimeout_32)) ? \
                         PduRouteDest_cpst->txUdpTriggerTimeout_32 : \
                         lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32;
    }
    else
    {
        /* [SWS_SoAd_00683] */
        /* If a PDU with TriggerMode set to TRIGGER_NEVER without a specific SoAdTxUdpTriggerTimeout is transmitted SoAd shall set the the nPdu specific timer */
        /* to the value of SoAdSocketUdpTriggerTimeout if the timer is not running or if it is lower than the current nPdu specific timer value. (SRS_Eth_00116) */
        lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 = \
                ((0xFFFFFFFFU == lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 ) || (lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 > lSoAdStaticSoConGrpConfig_cpst->udpProtocolConf_cpst->socketUdpTriggerTimeout_u32)) ? \
                 lSoAdStaticSoConGrpConfig_cpst->udpProtocolConf_cpst->socketUdpTriggerTimeout_u32 : \
                 lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32;
    }


    /* --------------------------------------------- */
    /* Save Pdu in descriptor                        */
    /* --------------------------------------------- */

    /* Main use case of nPduUdpTxBufferedSocketCnt_pu8 is bundleref
     * Configuration:- PduRoutedest is mapped to socket connection group and which has 3 sockets.
     *               - TriggerTransmission_en is SOAD_TRIGGER_NEVER
     *
     * Whenever IF Udp pdu is transmitted to lower layer, SoAd has to provide the TxConfirmation to UL if its successful.
     * Since Pdu is mapped to bundle ref which has 3 sockets, SoAd has to provide the TxConfirmation to UL if it is
     * transmitted via all 3 sockets successfully, otherwise it will wait for successful transmission via all 3.
     *
     * nPduUdpTxBufferedSocketCnt_pu8 member shall be increamented by 1 whenever pdu data is stored in nPduUdpTxBuffer.
     * In this case, Pdu Data shall be stored in 3 diff nPduUdpTxBuffer and it shall be reached to 3.
     *
     * Whenever, timer is expired or SoAd_IfTransmit is called with triggerTransmission_en as SOAD_TRIGGER_ALWAYS
     * for pdu mapped to same socket, then nPduUdpTxBufferedSocketCnt_pu8 shall be decremented by 1 after the
     * successful transmission. once it reaches to 0, we can identify that pdu data which was buffered in 3 diff
     * socket specific buffer got transmitted successfully via all 3.
     */
    (*PduRouteDest_cpst->nPduUdpTxBufferedSocketCnt_pu8)++;

    /* If pdu data was stored into nPduUdpTxBuffer, then store the Pdu Id in the same buffer,
     * it would be used to provide the TxConfirmation.
     *
     * SoAd shall transmit the buffered data from main function and provide the txconfirmation to UL.
     * To provide the txconfirmation, SoAd needs the PduId's. To get the bunch of pduid's it should be stored somewhere.
     * SoAd design: it would be stored along with pdu data but beginning of the buffer.
     */
    SoAd_SavePduToPduDescriptor( StaticSocketId_uo, PduRouteDest_cpst );

    return;
}


/*********************************************************************************************************************************/
/** SoAd_SavePduToPduDescriptor()   - This function shall load the TxPduId into the descriptor for given socket and hence       **/
/**                                it can be used to provide the TxConfirm flag once buffered data is transmitted successfully. **/
/** This function is called in the context of SoAd_IfTransmit()                                                                 **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/** PduRouteDest_cpst       - A pointer to a structure of PduRouteDest to which packet needs to be transmitted                  **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           None                                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, SOAD_CODE ) SoAd_SavePduToPduDescriptor( VAR(SoAd_SoConIdType, AUTOMATIC)                        StaticSocketId_uo,
                                                            P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)     PduRouteDest_cpst )
{
    /* Declare local variables */
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(uint8, AUTOMATIC)                                               lPduIdLoopIdx_u8;
    VAR(uint8, AUTOMATIC)                                               lIdxFreeSlot_u8;
    VAR(boolean, AUTOMATIC)                                             lPduIdStored_b;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get "the dynamic socket index value" from the static socket table  */
    lIdxDynSocket_uo = ( *lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo );

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* Initialization local variables declared above */
    lIdxFreeSlot_u8 = 0xFF;
    lPduIdStored_b = FALSE;

    /* Loop through for all PduId loaded in the buffer to identify whether PduId is already loaded or not,
     * Suppose if pduid was already loaded, dont add the duplicate entry for the same Pdu.
     * If there was no entry present for the pdu, get the free slot and load the PduId
     */
    for(lPduIdLoopIdx_u8 = 0U; lPduIdLoopIdx_u8 < lnPduUdpTransmitInfo_pst->nPduUdpTxPduIdSize_cu8; lPduIdLoopIdx_u8++)
    {
        /* If a free slot in the Pdu descriptor list has been found */
        if( (lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduId_uo == SOAD_CFG_PDU_ID_DEFAULT_VALUE) && (lIdxFreeSlot_u8 == 0xFF) )
        {
            /* Save the free slot index */
            lIdxFreeSlot_u8 = lPduIdLoopIdx_u8;
        }

        /* If slot which is busy by the same PduId */
        /* In the dynamic table, the field idxTxPduTable_uo is valid because we are in the context of IfTransmit */
        else if( lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduId_uo == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxTxPduTable_uo )
        {
            /* Set a flag to TRUE to remember that the PduId is already stored in the descriptor */
            lPduIdStored_b = TRUE;
            break;
        }

        /* If slot which is busy by another PduId */
        else
        {
            /* Nothing to do, go to next loop iteration to try to find a free slot or a slot which has the same PduId */
        }
    }

    /* If the PduId is not already stored in the descriptor list */
    if( lPduIdStored_b == FALSE )
    {
        /* If a free slot is available */
        if( lIdxFreeSlot_u8 != 0xFF )
        {
            /* Load the Tx PduId and Pdu length in the descriptor */
            lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lIdxFreeSlot_u8].nPduUdpTxPduId_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxTxPduTable_uo;
            lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lIdxFreeSlot_u8].nPduUdpTxPduDataLength_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength;
            lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lIdxFreeSlot_u8].nPduUdpTxPduHeaderId_u32 = PduRouteDest_cpst->txPduHeaderId_u32;
        }

        /* If no free slot is available */
        else
        {
            /* Report DET error if no slot is available */
            SOAD_DET_REPORT_ERROR( (TRUE), SOAD_IF_TRANSMIT_API_ID, SOAD_E_NOBUFS )
        }
    }

    /* If Pdu is already stored in the descriptor */
    else
    {
        /* [SWS_SoAd_00735] */
        /* In case the nPdu feature is used for a socket connection and all PDUs are configured with SoAdTxPduCollectionSemantics set to */
        /* SOAD_COLLECT_LAST_IS_BEST, SoAd shall only transmit the last instance of each PDU with the same PduId in the sequence their first */
        /* instances were requested for transmission. (SRS_Eth_00116) */

        /* Reload the length of the Pdu only */
        /* (this is important for Semantics LAST_IS_BEST, because SoAd need always to sent the last instance of each Pdu) */
        lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo = SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduInfoPtr_cpst->SduLength;
    }

    return;
}


/*********************************************************************************************************************************/
/** SoAd_GetTotalTxLengthFromPduDescriptor()   - This function shall return the total length the be transmitted based on the    **/
/**                                            content of the Pdu descriptor                                                    **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           - uint16                                                                                            **/
/**                             Return the total length of the frame to be transmitted                                          **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( uint16, SOAD_CODE ) SoAd_GetTotalTxLengthFromPduDescriptor( VAR(SoAd_SoConIdType, AUTOMATIC) StaticSocketId_uo )
{
    /* Declare local variables */
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(uint16, AUTOMATIC)                                              lTotalTxLength_u16;
    VAR(uint8, AUTOMATIC)                                               lPduIdLoopIdx_u8;

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* Initialize total Tx length to 0 */
    lTotalTxLength_u16 = 0U;

    /* Loop through for all PduId loaded in the descriptor */
    for(lPduIdLoopIdx_u8 = 0U; lPduIdLoopIdx_u8 < lnPduUdpTransmitInfo_pst->nPduUdpTxPduIdSize_cu8; lPduIdLoopIdx_u8++)
    {
        /* If the slot is occupied by a PduId */
        if( lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduId_uo != SOAD_CFG_PDU_ID_DEFAULT_VALUE )
        {
            /* Increment the total Tx length */
            lTotalTxLength_u16 += (uint16)(SOAD_PDUHDR_SIZE + lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo);
        }
    }

    return lTotalTxLength_u16;
}


/*********************************************************************************************************************************/
/** SoAd_nPduUdpTxDataTransmitPostAction()   - This function shall set the SoAd_ULIfUdpTxConfirmFlag_ab[] flag for the all pdus **/
/**                                which are transmitted from nPduUdpTx successfully and flush the PduId's from descriptor and  **/
/**                                calls SoAd_PerformPostPduTransmissionAction() if required.                                   **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo       - SoAd static socket index                                                                          **/
/** TransmissionFinished_b  - Flag indicating is transmission is finished and SoAd shall act for                                **/
/**                         SWS_SoAd_00582 and SWS_SoAd_00644                                                                   **/
/**                                                                                                                             **/
/** Parameters (inout):     None                                                                                                **/
/**                                                                                                                             **/
/** Parameters (out):       None                                                                                                **/
/**                                                                                                                             **/
/** Return value:           None                                                                                                **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, SOAD_CODE ) SoAd_nPduUdpTxDataTransmitPostAction( VAR(SoAd_SoConIdType, AUTOMATIC)       StaticSocketId_uo,
                                                                     VAR(boolean, AUTOMATIC)                TransmissionFinished_b )
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)                   lnPduUdpTransmitInfo_pst;
    VAR(uint8, SOAD_VAR)                                                lPduIdLoopIdx_u8;
    VAR(PduIdType, SOAD_VAR)                                            lPduId_uo;
    VAR(PduIdType, AUTOMATIC)                                           lNumberOfPduRouteDests_uo;
    VAR(boolean, AUTOMATIC)                              				lStaticSocConfigHasWildcardAnyAddr_b;
    VAR(uint16, AUTOMATIC)                               				lStaticSocPort_u16;

    /* Get static socket configuration pointers */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* --------------------------------------------- */
    /* Reset nPdu copied length and timer            */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00684] */
    /* SoAd shall stop the nPdu specific timer when the PDUs stored for the socket connection have been sent (SRS_Eth_00116) */

    /* Reset the nPdu timer to default value */
    lnPduUdpTransmitInfo_pst->nPduUdpTxTimer_u32 = 0xFFFFFFFFU;

    /* If buffered data was transmitted successfully, then all global variables related to the buffer has to be reseted */
    lnPduUdpTransmitInfo_pst->nPduUdpTxBuffCopiedLen_u16  = 0;


    /* --------------------------------------------- */
    /* Confirmation flag for transmitted Pdu         */
    /* --------------------------------------------- */

    /* loop through for each entry in the mapped Pdu descriptor to reset it */
    for( lPduIdLoopIdx_u8 = 0; lPduIdLoopIdx_u8 < lnPduUdpTransmitInfo_pst->nPduUdpTxPduIdSize_cu8; lPduIdLoopIdx_u8++ )
    {
        /* fetch the Tx Pdu Id from nPduUdpTxBuffer one by one */
        lPduId_uo = lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduId_uo;

        if( (lPduId_uo != SOAD_CFG_PDU_ID_DEFAULT_VALUE)    &&
            (SoAd_CurrConfig_cpst->SoAdIf_TxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lPduId_uo].idxIfTxConfirm_u8].TxCallback_pfn != NULL_PTR) )
        {
            /* Get the number of PduRouteDests configured with this PduRoute */
            lNumberOfPduRouteDests_uo = SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lPduId_uo].PduRouteDestNum_uo ;

            /* If Buffered data was transmitted successfully, then SoAd has to provide the TxConfirmation to Ul */
            /* call the below internal function to Set the SoAd_ULIfUdpTxConfirmFlag_ab[] flag to TRUE if pdu
             * was transmitted via all socket if any */

            /* Set the SoAd_ULIfUdpTxConfirmFlag_ab flag with return value of SoAd_ValidatePduTransmittedViaAllDest() */
            SoAd_ULIfUdpTxConfirmFlag_ab[lPduId_uo] = SoAd_ValidatePduTransmittedViaAllDest(StaticSocketId_uo,
                                                                                            lNumberOfPduRouteDests_uo,
                                                                                            SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lPduId_uo].PduRouteDestConf_cpst);
        }
    }

    /* If Buffered data was transmitted successfully, then flush the PduId's stored in the buffer */
    SoAd_nPduUdpTxCleanPduDescriptor(StaticSocketId_uo);


    /* --------------------------------------------- */
    /* Post Pdu transmission                         */
    /* --------------------------------------------- */

    /* Get IP and Port information from SoAd static socket table */
	lStaticSocConfigHasWildcardAnyAddr_b = SOAD_STATIC_SOC_CONFIG_HAS_WILDCARD_REMOTE_IPADDR( ((const SoAd_StaticSocConfigType_tst *) &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo])) );
    lStaticSocPort_u16                   = SOAD_GET_REMOTE_PORT_FROM_STATIC_SOC_CONFIG( ((const SoAd_StaticSocConfigType_tst *) &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo])) );

    /* If the transmission is successful and socket is Automatic, do as per SWS_SoAd_00582 and SWS_SoAd_00644 */
    if( ( TRUE == TransmissionFinished_b ) &&
        ( TRUE == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].soConGrpAutoConSetup_b ) &&
        ( ( TCPIP_PORT_ANY == lStaticSocPort_u16 ) || lStaticSocConfigHasWildcardAnyAddr_b ) )
    {
        /* Call the internal function to do as per SWS_SoAd_00582 and SWS_SoAd_00644 */
        SoAd_PerformPostPduTransmissionAction(StaticSocketId_uo);
    }

    return;
}


/*********************************************************************************************************************************/
/** SoAd_ValidatePduTransmittedViaAllDest()   - This function shall set the loop through for all pdu route dests to identify    **/
/**                                           Ul_TxConfirmation callback has to be triggered or not.                            **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo         - SoAd static socket index                                                                        **/
/** NumberOfPduRouteDests_uo  - Number of PduRouteDest available in PduRouteDests pointer                                       **/
/** PduRouteDests_cpst        - PduRouteDests pointer                                                                           **/
/**                                                                                                                             **/
/** Parameters (inout):       None                                                                                              **/
/**                                                                                                                             **/
/** Parameters (out):         None                                                                                              **/
/**                                                                                                                             **/
/** Return value:             None                                                                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( boolean, SOAD_CODE ) SoAd_ValidatePduTransmittedViaAllDest(VAR(SoAd_SoConIdType, AUTOMATIC)                        StaticSocketId_uo,
                                                                        VAR(PduIdType, AUTOMATIC)                               NumberOfPduRouteDests_uo,
                                                                        P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)     PduRouteDests_cpst)
{
    /* Declare local variables */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxOfPduRouteDest_uo;
    VAR(boolean, AUTOMATIC)                                             lPduTxConfirmFlag_b;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxStaticSocket_uo;
#if ( SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF )
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxSocketForLoop_uo;
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxEndSocket_uo;
#endif

    /* Initialize the confirmation flag to TRUE */
    lPduTxConfirmFlag_b = TRUE;

    /* Loop through all the route dests to transmit the Pdu */
    for( lIdxOfPduRouteDest_uo = 0; ( lIdxOfPduRouteDest_uo < NumberOfPduRouteDests_uo ); lIdxOfPduRouteDest_uo++ )
    {
#if ( SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF )
        /* --------------------------------------------- */
        /* Validate BUNDLE Destination                   */
        /* --------------------------------------------- */

        /* If Socket reference is linked to socket connection group and more than one socket connections are configured for the group */
        if( ( SOAD_SOCKET_BUNDLE_REFERENCE == PduRouteDests_cpst[lIdxOfPduRouteDest_uo].identifyTxSocketConnOrGroupRef_b ) &&
            ( 1U < SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[PduRouteDests_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo].maxSoConChannel_uo ) )
        {
            /* Calculate the lIdxEndSocket_uo from startSoConIdx_uo and maxSoConChannel_uo of group table */
            lIdxEndSocket_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[PduRouteDests_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo].startSoConIdx_uo + \
                               SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[PduRouteDests_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo].maxSoConChannel_uo;

            /* Loop through for all the sockets for group */
            for(lIdxSocketForLoop_uo = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[PduRouteDests_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo].startSoConIdx_uo;
                lIdxSocketForLoop_uo < lIdxEndSocket_uo;
                lIdxSocketForLoop_uo++)
            {
                /* If given socket id is matched with socket id in loops, then decrement the nPduUdpTxBufferedSocketCnt_pu8 by one to confirm pdu was transmitted via 1 socket */
                if(StaticSocketId_uo == lIdxSocketForLoop_uo)
                {
                    (*PduRouteDests_cpst[lIdxOfPduRouteDest_uo].nPduUdpTxBufferedSocketCnt_pu8)--;
                    break;
                }
            }
        }
        else
#endif
        {
            /* --------------------------------------------- */
            /* Validate SOCKET Destination                   */
            /* --------------------------------------------- */

#if ( SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF )
            /* Fetch the static socket id from table */
            lIdxStaticSocket_uo = (SOAD_SOCKET_BUNDLE_REFERENCE == PduRouteDests_cpst[lIdxOfPduRouteDest_uo].identifyTxSocketConnOrGroupRef_b) ? \
                                    SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[PduRouteDests_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo].startSoConIdx_uo: \
                                    PduRouteDests_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo;
#else
            /* Fetch the static socket id from table */
            lIdxStaticSocket_uo = PduRouteDests_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo;
#endif

            /* If socket match is true, assume that pdu data was transmitted succesfuuly, so reset the
             * nPduUdpTxBufferedSocketCnt_pu8 to 0 since PduRoute is mapped to only one socket either via
             * socket connection group or socket connection.
             */
            if( StaticSocketId_uo == lIdxStaticSocket_uo)
            {
                (*PduRouteDests_cpst[lIdxOfPduRouteDest_uo].nPduUdpTxBufferedSocketCnt_pu8) = 0;
            }
        }

        /* Update the lPduTxConfirmFlag_b to TRUE if pdu data was transmitted via all PduRouteDests
         * and via all sockets of each PduRouteDest if BundleRef is configured */
        lPduTxConfirmFlag_b = ( ( 0U != (*PduRouteDests_cpst[lIdxOfPduRouteDest_uo].nPduUdpTxBufferedSocketCnt_pu8 ) ) || \
                                ( FALSE == lPduTxConfirmFlag_b) )? \
                                        FALSE: TRUE;
    }

    return lPduTxConfirmFlag_b;
}


/*********************************************************************************************************************************/
/** SoAd_nPduUdpTxCleanPduDescriptor()   - This function shall flush TxPduId's which are stored in descriptor for given socket  **/
/**                                                                                                                             **/
/** Parameters (in):                                                                                                            **/
/** StaticSocketId_uo         - SoAd static socket index                                                                        **/
/**                                                                                                                             **/
/** Parameters (inout):       None                                                                                              **/
/**                                                                                                                             **/
/** Parameters (out):         None                                                                                              **/
/**                                                                                                                             **/
/** Return value:             None                                                                                              **/
/**                                                                                                                             **/
/*********************************************************************************************************************************/
static FUNC( void, SOAD_CODE ) SoAd_nPduUdpTxCleanPduDescriptor( VAR(SoAd_SoConIdType, AUTOMATIC) StaticSocketId_uo )
{
    /* Declare local variables */
    P2VAR(SoAd_nPduUdpTxInfo_tst, SOAD_VAR, SOAD_VAR)           lnPduUdpTransmitInfo_pst;
    VAR(uint8, SOAD_VAR)                                        lPduIdLoopIdx_u8;

    /* Get nPdu Udp Tx table */
    lnPduUdpTransmitInfo_pst = &((SoAd_CurrConfig_cpst->SoAdIf_nPduUdpTransmitInfo_pst)[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].nPduUdpTxTableIndex_uo]);

    /* loop through for each entry in the mapped Pdu descriptor to reset it */
    for( lPduIdLoopIdx_u8 = 0; lPduIdLoopIdx_u8 < lnPduUdpTransmitInfo_pst->nPduUdpTxPduIdSize_cu8; lPduIdLoopIdx_u8++ )
    {
        /* Reset the Pdu descriptor entry with default values */
        lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduId_uo = SOAD_CFG_PDU_ID_DEFAULT_VALUE;
        lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduDataLength_uo = 0U;
        lnPduUdpTransmitInfo_pst->nPduUdpTxPduDescriptor_cpst[lPduIdLoopIdx_u8].nPduUdpTxPduHeaderId_u32 = 0U;
    }

    return;
}


#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 */
#endif /* SOAD_CONFIGURED */
