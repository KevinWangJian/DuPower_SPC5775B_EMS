

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_CONFIGURED

#include "Det.h"
#include "TcpIp.h"

#include "SoAd_Prv.h"

#if (!defined(TCPIP_AR_RELEASE_MAJOR_VERSION) || (TCPIP_AR_RELEASE_MAJOR_VERSION != SOAD_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched  - SoAd and TcpIp"
#endif

#if (!defined(TCPIP_AR_RELEASE_MINOR_VERSION) || (TCPIP_AR_RELEASE_MINOR_VERSION != SOAD_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched - SoAd and TcpIp"
#endif

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

static FUNC( void, SOAD_CODE )      SoAd_ResetDynSockCommonParamByEntry     ( VAR( SoAd_SoConIdType, AUTOMATIC )    DynSocketId_uo );

/**
 ***********************************************************************************************************************
 * \Function Name : SoAd_ReserveFreeDynSocket()
 *
 * \Function description
 * This service shall get a dynamic socket from the available dynamic sockets list and linked up with static
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - static socket id whose Tcp config table or Udp config table is to be initiated
 *
 * Parameters (inout): None
 *
 * Parameters (out):
 * \param   SoAd_SoConIdType*
 * \arg     DynSocketId_puo - Dynamic socket id mapped to static socket id
 *
 * Return value: None
 *
 ***********************************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_ReserveFreeDynSocket ( VAR( SoAd_SoConIdType, AUTOMATIC )             StaticSocketId_uo,\
                                                    P2VAR(SoAd_SoConIdType, AUTOMATIC, AUTOMATIC)  DynSocketId_puo )
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;

    /* Local pointer to store the Dynamic array one by one */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)           lSoAdDyncSocConfig_pst ;

    /* Index for looping across Dynamic sockets*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lIdxDynSocket_uo ;

    /* Index of the first Dynamic socket with the same domain as the static socket */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lStartIdx_uo ;

    /* Index of the last Dynamic socket with the same domain as the static socket */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                lEndIdx_uo ;

    /* copy the global array index address to local pointer for further processing */
    lSoAdStaticSocConfig_cpst   = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* DD: In the dynamic socket table, we will first put all IPv4 sockets and then all IPv6 sockets.
           In this way, when we try to find an available dynamic socket to link with a specified static socket, we will only loop through dynamic sockets with the same domain. */
    SOAD_GET_DYNC_SOC_CONFIG_TABLE_RANGE_WITH_SAME_DOMAIN( lSoAdStaticSocConfig_cpst, ((SoAd_SoConIdType *) &lStartIdx_uo), ((SoAd_SoConIdType *) &lEndIdx_uo) )

    /* loop through all entries of the dynamic socket table for the processing */
    for ( lIdxDynSocket_uo = lStartIdx_uo; lIdxDynSocket_uo < lEndIdx_uo; lIdxDynSocket_uo++ )
    {
        /* copy the global array index address to local pointer for further processing */
        lSoAdDyncSocConfig_pst      =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

        /* Get a socket from dynamic socket table from the available sockets */
        if( SOAD_CFG_SOCON_ID_DEFAULT_VALUE   == lSoAdDyncSocConfig_pst->idxStaticSoc_uo )
        {
            /* update the "index of dynamic soc config table" in Static soc table */
            ( *lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo ) = lIdxDynSocket_uo;

            /* Update the variable: "index of the static soc table" in dynamic socket table */
            lSoAdDyncSocConfig_pst->idxStaticSoc_uo = StaticSocketId_uo;

            /* set the socket sub mode state to SOAD_SOCON_CLOSE to identify link between static and dynamic is present */
            lSoAdDyncSocConfig_pst->socConSubMode_en = SOAD_SOCON_CLOSE;

            /* Update the Output paremeter with matched Dynamic socket Id */
            ( *DynSocketId_puo ) = lIdxDynSocket_uo;

            /* Update the dynamic socket config remote address with the static configured address */
            SOAD_COPY_REMOTE_ADDR_FROM_STATIC_SOC_CONFIG_TO_DYNC_SOC_CONFIG(lSoAdStaticSocConfig_cpst, lSoAdDyncSocConfig_pst)

            /* Break from the loop as the socket is obtained successfully*/
            break;

        }
    }
}

/**
 **********************************************************************************************************************************************
 * \Function Name : SoAd_ResetDynSockTblByEntry()
 *
 * \Function description
 * This service reset all variables of a dynamic configurations of Socket connection (for a given socket id only) which are specific to
 * socket state SOAD_SOCON_RECONNECT and SOAD_SOCON_OFFLINE.
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - SoAd_Prv_idxDynSocTable_puo pointer of static socket id linked to dynamic socket index needs to be resetted .
 * \param  SoAd_SoConIdType
 * \arg     DynSocketId_uo  - Index of Dynamic socket connection table.
 * \param   SoAd_SoConModeType
 * \arg     Mode_en- based on the Mode, dynamic socket config will be resetted
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 *************************************************************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_ResetDynSockTblByEntry( VAR( SoAd_SoConIdType, AUTOMATIC )    StaticSocketId_uo, \
                                                     VAR( SoAd_SoConIdType, AUTOMATIC )    DynSocketId_uo, \
                                                     VAR( SoAd_SoConModeType, AUTOMATIC )  Mode_en )
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;

    /* Local pointer to store the Dynamic array */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst ;

    /* Initialization of local variables */
    /* copy the global array index address to local pointer for further processing */
    lSoAdStaticSocConfig_cpst   = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

	/* Extract pointer to Dynamic structrue for given index */
    lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    /* --------------------------------------------- */
    /* Reset Rx buffer dynamic table                 */
    /* --------------------------------------------- */

    /* Reset the dynamic Rx buffer table if configured for the static socket configured */
    if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR )
    {
        /* Reset the SoAd Rx buffer to its default state */
        SoAd_ResetRxBuffer( StaticSocketId_uo );
    }
#endif

#if ( SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 )
    /* --------------------------------------------- */
    /* Reset nPdu Udp Tx dynamic table               */
    /* --------------------------------------------- */
    /* Reset the dynamic nPdu Udp Tx table if configured for the static socket configured */
    if( lSoAdStaticSocConfig_cpst->nPduUdpTxTableIndex_uo < SOAD_CFG_nPDU_UDP_TX_DEFAULT_VALUE )
    {
        /* Reset the SoAd nPdu Udp Tx table to its default state */
        SoAd_ResetnPduUdpTx( StaticSocketId_uo );
    }
#endif /* SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 */


    /* --------------------------------------------- */
    /* Reset dynamic socket table                    */
    /* --------------------------------------------- */

    SoAd_ResetDynSockCommonParamByEntry(DynSocketId_uo);

    /* If the requested mode is RECONNECT or an UL wanted to keep the socket connection open */
    if( ( SOAD_SOCON_RECONNECT == Mode_en ) ||
        (lSoAdDyncSocConfig_pst->socConOpenReqCnt_u16 > lSoAdDyncSocConfig_pst->socConCloseReqCnt_u16) )
    {
        lSoAdDyncSocConfig_pst->socConSubMode_en            = SOAD_SOCON_CLOSE;
        lSoAdDyncSocConfig_pst->socConRequestedMode_en      = SOAD_EVENT_ONLINEREQ;
        SOAD_COPY_REMOTE_ADDR_FROM_STATIC_SOC_CONFIG_TO_DYNC_SOC_CONFIG(lSoAdStaticSocConfig_cpst, lSoAdDyncSocConfig_pst)

    }
    else
    {
        /* Reset the Dynamic table entries */
        lSoAdDyncSocConfig_pst->socConSubMode_en             = SOAD_SOCON_IDLE;
        lSoAdDyncSocConfig_pst->socConRequestedMode_en       = SOAD_EVENT_IDLE;
        SOAD_SET_DYNC_SOC_CONFIG_REMOTE_ADDR_TO_DEFAULT(lSoAdDyncSocConfig_pst)

        /* Reset the number of open and close requests as the socket goes OFFLINE */
        lSoAdDyncSocConfig_pst->socConOpenReqCnt_u16        = 0;
        lSoAdDyncSocConfig_pst->socConCloseReqCnt_u16       = 0;

        /* link from dynamic socket table to static socket table shall be reset */
        lSoAdDyncSocConfig_pst->idxStaticSoc_uo              = SOAD_CFG_SOCON_ID_DEFAULT_VALUE ;

        /* link from static socket table to dynamic tables also shall be reset */
        (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo) = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;
    }
}

/**
 **********************************************************************************************************************************************
 * \Function Name : SoAd_ResetDynSockCommonParamByEntry()
 *
 * \Function description
 * This service reset all variables of a dynamic configurations of Socket connection (for a given socket id only) common for
 * SOAD_SOCON_RECONNECT and SOAD_SOCON_OFFLINE state .
 * It has no return value .
 *
 * Parameters (in):
 * \param  SoAd_SoConIdType
 * \arg    DynSocketId_uo  - Index of Dynamic socket connection table.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 *************************************************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_ResetDynSockCommonParamByEntry( VAR( SoAd_SoConIdType, AUTOMATIC )    DynSocketId_uo )
{
    /* Local pointer to store the Dynamic array */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)       lSoAdDyncSocConfig_pst ;

    /* Initialization of local variables */
    /* Extract pointer to Dynamic structrue for given index */
    lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

    /* Reset the common parameters */
    lSoAdDyncSocConfig_pst->rxPduInfoPtr_cpst           = NULL_PTR ;
    lSoAdDyncSocConfig_pst->txPduInfoPtr_cpst           = NULL_PTR ;
    lSoAdDyncSocConfig_pst->soConDynLocalPort_u16       = SOAD_DEFAULT_PORT ;

#if (SOAD_TP_PRESENT != STD_OFF )
    lSoAdDyncSocConfig_pst->tpTxRemainingLength_uo      = 0 ;
    lSoAdDyncSocConfig_pst->tpTransmittedLength_uo      = 0 ;
    lSoAdDyncSocConfig_pst->tpTcpCopyTxDataLength_uo    = 0 ;
    lSoAdDyncSocConfig_pst->tpTxTotPduLen_uo            = 0 ;
    lSoAdDyncSocConfig_pst->tpReceptionOngoing_b        = FALSE;
    lSoAdDyncSocConfig_pst->tpTransmissionOnGoing_b     = FALSE;
    lSoAdDyncSocConfig_pst->tpTransmitRequest_b         = FALSE;
#endif /* SOAD_TP_PRESENT != STD_OFF */

#if ( SOAD_CONFIG_NUM_OF_UDP_SUPERVISION_TIMEOUT > 0 )
    lSoAdDyncSocConfig_pst->UdpAliveSupervisionTimer_u32 = 0xFFFFFFFFU;
#endif /* SOAD_CONFIG_NUM_OF_UDP_SUPERVISION_TIMEOUT > 0 */

    lSoAdDyncSocConfig_pst->txPduHeaderId_u32           = SOAD_DEFAULT_PDU_HDR_ID;

#if (SOAD_NUM_TX_IF_TCP_PDU > 0)
    lSoAdDyncSocConfig_pst->ifTxTcpPduLenReqByUL_uo     = 0 ;
    lSoAdDyncSocConfig_pst->ifTxTcpAckedDataLen_uo      = 0 ;
#endif /* SOAD_NUM_TX_IF_TCP_PDU > 0 */

    lSoAdDyncSocConfig_pst->ifTxCopiedLength_uo         = 0 ;

    lSoAdDyncSocConfig_pst->idxTxPduTable_uo            = SOAD_CFG_PDU_ID_DEFAULT_VALUE ;
    lSoAdDyncSocConfig_pst->idxRxPduTable_uo            = SOAD_CFG_PDU_ID_DEFAULT_VALUE ;

    lSoAdDyncSocConfig_pst->socketHandleTcpIp_uo        = SOAD_CFG_SOCKET_ID_DEFAULT_VALUE ;

#if (SOAD_TCP_PRESENT != STD_OFF)
    lSoAdDyncSocConfig_pst->rxTcpRemainingPduLengthToDicard_u32 = 0U;
#endif

#if (SOAD_IF_PRESENT != STD_OFF )
    lSoAdDyncSocConfig_pst->ifTransmissionOnGoing_b     = FALSE ;
#endif /* SOAD_IF_PRESENT != STD_OFF */

#if (SOAD_TP_TCP_PRESENT != STD_OFF)
    lSoAdDyncSocConfig_pst->tpTxTcpTransmitRetryCnt_u16 = 0 ;
    lSoAdDyncSocConfig_pst->tpTxTcpBufferAvailable_b    = TRUE ;
#endif /* SOAD_TP_TCP_PRESENT != STD_OFF */

#if (SOAD_TP_UDP_PRESENT != STD_OFF)
	lSoAdDyncSocConfig_pst->tpUdpTxTriggered_b      = FALSE;
#endif /* SOAD_TP_UDP_PRESENT != STD_OFF */

#if ( SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 )
    lSoAdDyncSocConfig_pst->nPduUdpTxTriggered_b    = FALSE;
#endif /* SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 */

#if ( SOAD_IF_FANOUT_ENABLED != STD_OFF )
    lSoAdDyncSocConfig_pst->ifSkipFanOutTransmission_b   = FALSE ;
#endif /* SOAD_IF_FANOUT_ENABLED != STD_OFF */

    lSoAdDyncSocConfig_pst->statusAbort_b               = FALSE ;
    lSoAdDyncSocConfig_pst->discardNewTxRxReq_b         = FALSE ;
    lSoAdDyncSocConfig_pst->ifTpTxSoAdHdrCopied_b       = FALSE ;
}

#if (SOAD_TP_PRESENT != STD_OFF)
/**
 **********************************************************************************************************************
 * \Function Name : SoAd_ResetTpTxDyncParameters()
 *
 * \Function description
 * This service shall reset the dynamic table entries for TP tranmission and informs upper layer about it.
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo  - Index of Dynamic socket connection table.
 * \param   PduIdType
 * \arg     TxPduId_uo  - Index of Tx Pdu table.
 * \param   Std_ReturnType
 * \arg     Result_u8  - status of previous transmission need to be informed to UL.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 **********************************************************************************************************************
 */

FUNC( void, SOAD_CODE ) SoAd_ResetTpTxDyncParameters( VAR(SoAd_SoConIdType, AUTOMATIC)    DynSocketId_uo,\
                                                      VAR(PduIdType, AUTOMATIC)           TxPduId_uo,\
                                                      VAR(Std_ReturnType, AUTOMATIC)      Result_u8 )
{
    /* Local pointer to store the Dynamic array for given Index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Local pointer to store the Tx Pdu table for given index */
    P2CONST(SoAd_TxPduConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdTxPduConfig_cpst ;

    /*Initialization of local variables */
    /* Copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

    /* Get the Tx Pdu pointer for given index */
    lSoAdTxPduConfig_cpst   = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[TxPduId_uo]);

    /* As the data transmission is done successfully,we have to reset the dynamic variables */
    /* Reset the txpduid in dynamic config table */
    lSoAdDyncSocConfig_pst->idxTxPduTable_uo = SOAD_CFG_PDU_ID_DEFAULT_VALUE ;

    /* set the tpTxRemainingLength_uo to zero */
    lSoAdDyncSocConfig_pst->tpTxRemainingLength_uo = 0;

    /* Reset the transmitted length to zero */
    lSoAdDyncSocConfig_pst->tpTransmittedLength_uo = 0;

    /* Reset the copied length to zero */
    lSoAdDyncSocConfig_pst->tpTcpCopyTxDataLength_uo = 0;

    /* Reset the total length to zero */
    lSoAdDyncSocConfig_pst->tpTxTotPduLen_uo = 0;

    /* Set the tpTransmit request to FALSE, as all data is copied from the upper layer */
    lSoAdDyncSocConfig_pst->tpTransmissionOnGoing_b = FALSE;

    /* Set the tpTransmit request to FALSE, as all data is copied from the upper layer */
    lSoAdDyncSocConfig_pst->tpTransmitRequest_b = FALSE;

    /* Reset the ifTpTxSoAdHdrCopied_b flag to FALSE */
    lSoAdDyncSocConfig_pst->ifTpTxSoAdHdrCopied_b = FALSE;

#if (SOAD_TP_UDP_PRESENT != STD_OFF)
    lSoAdDyncSocConfig_pst->tpUdpTxTriggered_b    = FALSE;
#endif /* SOAD_TP_UDP_PRESENT != STD_OFF */

#if (SOAD_TP_TCP_PRESENT != STD_OFF)
    /* set the tpTxTcpTransmitRetryCnt_u16 to zero */
    lSoAdDyncSocConfig_pst->tpTxTcpTransmitRetryCnt_u16 = 0;

    /* set the tpTxTcpBufferAvailable_b to TRUE which means available */
    lSoAdDyncSocConfig_pst->tpTxTcpBufferAvailable_b    = TRUE;
#endif /* SOAD_TP_TCP_PRESENT != STD_OFF */

    /* Condition check : Index of the Txpdu config table should be valid*/
    /* Condition check: upper layer call back should be configured */
    if( NULL_PTR != SoAd_CurrConfig_cpst->SoAdTp_TxCallbacks_cpst[lSoAdTxPduConfig_cpst->idxTpTxConfirm_u8].TxCallback_pfn )
    {
        /* Call back the upper layer with txPduId to inform about TpTxConfirmation */
        SoAd_CurrConfig_cpst->SoAdTp_TxCallbacks_cpst[lSoAdTxPduConfig_cpst->idxTpTxConfirm_u8].TxCallback_pfn(\
                lSoAdTxPduConfig_cpst->ulTxPduId_uo, Result_u8);
    }
}

#endif /* SOAD_TP_PRESENT != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
