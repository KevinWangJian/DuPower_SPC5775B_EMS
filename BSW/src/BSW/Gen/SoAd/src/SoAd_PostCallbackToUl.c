

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

#if (SOAD_TP_PRESENT != STD_OFF)
static FUNC( void, SOAD_CODE )                 SoAd_TerminateActiveTpTxSession                     ( VAR(SoAd_SoConIdType, AUTOMATIC)    DynSocketId_uo );

static FUNC( void, SOAD_CODE )                 SoAd_TerminateActiveTpRxSession                     ( VAR(SoAd_SoConIdType, AUTOMATIC)    DynSocketId_uo );
#endif /* SOAD_TP_PRESENT != STD_OFF */

/**
 ***********************************************************************************************************************
 * \Function Name : SoAd_ModeChgCallbackToUl()
 *
 * \Function description
 * This service shall invoke a call back to inform the upper layer about the mode change of the socket connection .
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - static socket id whose mode change to be informed to UL.
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo  - Index of Dynamic socket connection table.
 * \param   SoAd_SoConModeType
 * \arg     ModeType- The mode which shall be informed to the upper layer
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 ***********************************************************************************************************************
 */

FUNC( void, SOAD_CODE ) SoAd_ModeChgCallbackToUl( VAR( SoAd_SoConIdType, AUTOMATIC )    StaticSocketId_uo,\
                                                  VAR( SoAd_SoConIdType, AUTOMATIC )    DynSocketId_uo,
                                                  VAR( SoAd_SoConModeType, AUTOMATIC )  Mode_en )
{
    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)     lSoAdStaticSocConfig_cpst;

    /* Local pointer to store the Dynamic array one by one */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)           lSoAdDyncSocConfig_pst ;

    /* Initialize the flag to FALSE*/
    /* Extract pointer to Dynamic structrue for given index */
    lSoAdDyncSocConfig_pst            = &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

    if(lSoAdDyncSocConfig_pst->socConMode_en != Mode_en)
    {
        /*change the socket state to SOAD_SOCON_ONLINE */
        lSoAdDyncSocConfig_pst->socConMode_en  = Mode_en ;

        /* copy the global array index address to local pointer for further processing */
        lSoAdStaticSocConfig_cpst   = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

        /* Condition check: mode change notification is enabled and call back should be  configured in upper layer */
        if( ( TRUE == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].socModeChgNotifyEnable_b ) && \
            ( NULL_PTR != SoAd_CurrConfig_cpst->SoAd_SoConModeChgCallbacks_cpst[lSoAdStaticSocConfig_cpst->idxSocModeChgCallback_u8].SoConModeChgCallback_pfn) )
        {
            /* Notify the upper layer about the soc connection state change */
            SoAd_CurrConfig_cpst->SoAd_SoConModeChgCallbacks_cpst[lSoAdStaticSocConfig_cpst->idxSocModeChgCallback_u8].SoConModeChgCallback_pfn(StaticSocketId_uo ,\
                                                                                                                                                Mode_en );
        }
    }
}

#if (SOAD_TP_PRESENT != STD_OFF)
/**
 ***************************************************************************************************
 * \Function Name : SoAd_InformTpStartOfReception()
 *
 * \Function description
 * This service shall call start of reception to upper layer
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - Index of static socket connection table.
 * \param   PduIdType
 * \arg     RxPduId_uo- Index of Rx Pdu table.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 ***************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_InformTpStartOfReception( VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo,\
                                                       VAR( PduIdType,         AUTOMATIC)  RxPduId_uo )
{
    /* Local pointer to store the Dynamic array one by one */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Local pointer to store the Rx Pdu array for given index */
    P2CONST(SoAd_RxPduConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdRxPduConfig_cpst ;

    /* Variable to hold ret val of function call of startofreception*/
    VAR(BufReq_ReturnType, AUTOMATIC)                       lRetValTpStartOfReception_en;

    /* Variable to store the length of pdu */
    VAR(PduLengthType, AUTOMATIC)                           lTpSduLength_uo;

    /* Variable to hold the lBufferSize_uo for the function call start of reception */
    VAR(PduLengthType, AUTOMATIC)                           lBufferSize_uo;

    /* variable to store the dynamic socket connection table index */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
    /* Routing Group Status */
    VAR(boolean, AUTOMATIC)                                 lRgStatus_b;
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

    /*Initialization of variables */
    lRetValTpStartOfReception_en    = BUFREQ_E_NOT_OK;
    lTpSduLength_uo                 = 0;
    lBufferSize_uo                  = 0;

    /* Get the index of the dynamic soc table */
    lIdxDynSocket_uo                = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo].SoAd_Prv_idxDynSocTable_puo);

    /* Extract pointer to Dynamic structrue for given index */
    lSoAdDyncSocConfig_pst          = &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

    /* Extract the pointer to Rx Pdu table address for given index */
    lSoAdRxPduConfig_cpst           = &(SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[RxPduId_uo]);

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF )
    /* call the internal function to retrieve the Routing Group status for the combination of RG's Id and associated SoCon Id */
    /* Check Routing Group is enabled for the fetched socket */
    lRgStatus_b = (0U < lSoAdRxPduConfig_cpst->numOfRxRoutingGroups_uo) ? \
                        ( SoAd_GetRoutingGroupsEnabledStatus( lSoAdRxPduConfig_cpst->rxRoutingGroupConf_cpuo, \
                                                              lSoAdRxPduConfig_cpst->numOfRxRoutingGroups_uo, \
                                                              StaticSocketId_uo ) ) : \
                                                              TRUE;

    /* According to : SWS_SoAd_00600: If Routing group is disabled for any PDU then discard the corresponding PDU's packet */
    /* If Routing group is enabled for the socket */
    if( FALSE != lRgStatus_b )
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */
    {
        /*Check StartOfReception callback is valid */
        if (NULL_PTR != SoAd_CurrConfig_cpst->SoAdTp_StartOfReceptionCallbacks_cpst[lSoAdRxPduConfig_cpst->idxTpStartReceptionCbk_u8].StartOfReception_pfn)
        {
            /* According to : SWS_SoAd_00595: RxCallback function to the Upper layer*/
            lRetValTpStartOfReception_en = SoAd_CurrConfig_cpst->SoAdTp_StartOfReceptionCallbacks_cpst[lSoAdRxPduConfig_cpst->idxTpStartReceptionCbk_u8].StartOfReception_pfn (\
                    lSoAdRxPduConfig_cpst->ulRxPduId_uo,NULL_PTR,lTpSduLength_uo,&lBufferSize_uo);

            /* If the UL is not ready with its buffer */
            if( BUFREQ_E_NOT_OK == lRetValTpStartOfReception_en )
            {
                /* set the global variables to skip the further transmission and reception */
                lSoAdDyncSocConfig_pst->discardNewTxRxReq_b     = TRUE;

                /* set the state such that, the socket shall be closed in next main function */
                lSoAdDyncSocConfig_pst->socConRequestedMode_en  = SOAD_EVENT_OFFLINEREQ_SOAD ;
            }
            else
            {
                /* Set the flag for TP reception ongoing */
                lSoAdDyncSocConfig_pst->tpReceptionOngoing_b = TRUE ;

                /*Update the RxPdu Id in dynamic table, it indicates which rx pdu Id is current active in the coressponding socket connection*/
                lSoAdDyncSocConfig_pst->idxRxPduTable_uo     = RxPduId_uo;
            }
        }
    }
}

/**
 **********************************************************************************************************************
 * \Function Name : SoAd_TerminateActiveTpTxSession()
 *
 * \Function description
 * This service shall stop the current TP tx ongoing if any
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo  - Index of Dynamic socket connection table.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 **********************************************************************************************************************
 */

static FUNC( void, SOAD_CODE ) SoAd_TerminateActiveTpTxSession( VAR(SoAd_SoConIdType, AUTOMATIC)    DynSocketId_uo )
{
    /* Local pointer to store the Dynamic array for given Index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Local pointer to store the Tx Pdu table for given index */
    P2CONST(SoAd_TxPduConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdTxPduConfig_cpst ;

    /* Index of TxPduConfig table */
    VAR(PduIdType, AUTOMATIC)                               lIdxTxPdu_uo;

    /* variable to hold the return value */
    VAR ( Std_ReturnType, AUTOMATIC )                      lResult_u8;

    /*Initialization of local variables */
    /* Copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

    /* Get the index of the TxPdu table from the dynamic socket table */
    lIdxTxPdu_uo            = lSoAdDyncSocConfig_pst->idxTxPduTable_uo;

    /* Get the Tx Pdu pointer for given index */
    lSoAdTxPduConfig_cpst   = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lIdxTxPdu_uo]);

    lResult_u8              = E_NOT_OK;

    /*Note: swg2kor: If the TcpIp_Close returns E_NOT_OK, then if socket was in ACTIVE state and already informed upper layer
     * about TP session close, then again in next main function, upper layer shall be called again: process needs to be improved
     * this current design kept in mind that TcpIp_Close has only 1% of chance to get E_NOT_OK */

    /****************************************************************************************************************/
    /****************************************** [SWS_SoAd_00640]: step(1)********************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /** E_OK if disconnect is caused by SoAd_CloseSoCon() and all data was correctly transmitted                  ***/
    /****************************************************************************************************************/
    /****************************************************************************************************************/

    /* If socket is requested to close by upper layer */
    if( ( FALSE == lSoAdDyncSocConfig_pst->tpTransmitRequest_b ) &&\
        ( ( SOAD_EVENT_OFFLINEREQ_UL == lSoAdDyncSocConfig_pst->socConRequestedMode_en ) ||\
          ( lSoAdDyncSocConfig_pst->socConCloseReqCnt_u16 > lSoAdDyncSocConfig_pst->socConOpenReqCnt_u16 ) ) )
    {
        lResult_u8 = E_OK;
    }

    /****************************************************************************************************************/
    /****************************************** [SWS_SoAd_00640]: step(2)********************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /**                                      E_NOT_OK for any other cause                                         ***/
    /****************************************************************************************************************/
    /****************************************************************************************************************/

    /* check for :  TP Transmission is going on */
    else
    {
        /* Stop the TP transmission */
        lSoAdDyncSocConfig_pst->tpTransmitRequest_b = FALSE ;
    }

    /* Condition check: upper layer call back should be configured */
    if( NULL_PTR != SoAd_CurrConfig_cpst->SoAdTp_TxCallbacks_cpst[lSoAdTxPduConfig_cpst->idxTpTxConfirm_u8].TxCallback_pfn )
    {
        /* Call back the upper layer with txPduId to inform about TpTxConfirmation */
        SoAd_CurrConfig_cpst->SoAdTp_TxCallbacks_cpst[lSoAdTxPduConfig_cpst->idxTpTxConfirm_u8].TxCallback_pfn(\
                lSoAdTxPduConfig_cpst->ulTxPduId_uo, lResult_u8);

    }/* End for: condition check for upper layer call back is configured  */

}

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TerminateActiveTpRxSession()
 *
 * \Function description
 * This service shall stop the current TP rx ongoing if any
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo  - Index of Dynamic socket connection table.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TerminateActiveTpRxSession( VAR(SoAd_SoConIdType, AUTOMATIC) DynSocketId_uo )
{
    /* Local pointer to store the Dynamic array for given Index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst;
    VAR(Std_ReturnType, AUTOMATIC)                                      lResult_u8;
    VAR(boolean, AUTOMATIC)                                             lULRxIndicationNeeded_b;
#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    P2CONST( SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC )       lSoAdStaticSocConfig_cpst;
#endif

    /* Copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst  =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

    /* Init result to E_NOT_OK */
    lResult_u8 = E_NOT_OK;
    lULRxIndicationNeeded_b = TRUE;

#if ( SOAD_RX_BUFF_ENABLE != STD_OFF )
    /* --------------------------------------------- */
    /* Terminate active TP Rx session from Rx buffer */
    /* --------------------------------------------- */

    /* Get static socket configuration pointer */
    lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lSoAdDyncSocConfig_pst->idxStaticSoc_uo]);

    /* If Rx buffer is configured */
    if( lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst != NULL_PTR )
    {
        /* Call a function to execute the copying of the rest of the TP data from Rx buffer to UL for the current TP reception */
        /* (function is called with TRUE because it is required to do not start further TP session that can be present in the buffer) */
        /* (if all the data can be correctly transmitted for header enabled, then UL Rx_Indication will be called with E_OK within this function call) */
        SoAd_CopyTpDataFromRxBufferToUl( lSoAdDyncSocConfig_pst->idxStaticSoc_uo, TRUE );

        /* If there is no more TP reception in progress from Rx buffer to UL (header enabled) */
        if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == TRUE) && (lSoAdDyncSocConfig_pst->tpReceptionOngoing_b == FALSE) )
        {
            /* UL_RxIndication is not needed because it has already been given in the call of SoAd_CopyTpDataFromRxBufferToUl with E_OK because the Tp reception sessions has been finished */
            lULRxIndicationNeeded_b = FALSE;
        }

        /* If there is no more TP reception in progress from Rx buffer to UL (header disabled) */
        else if( (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == FALSE) && (lSoAdStaticSocConfig_cpst->dynRxBuffTableEntry_pst->TpDataCurrentSize_u16 == 0U))
        {
            /* Set the result to E_OK as there remaining data present in the buffer has been transfered */
            lResult_u8 = E_OK;
        }

        /* The data of the current TP Rx session was not completely transmitted */
        else
        {
            /* Result remain to E_NOT_OK */
        }

        /* Reset the complete content of the SoAd Rx buffer because close was requested ([SWS_SoAd_00641]) */
        /* 1. Active TP session is terminated  */
        /* 2. Further reception or transmission on the socket are terminated */
        SoAd_ResetRxBuffer( lSoAdDyncSocConfig_pst->idxStaticSoc_uo );
    }
    else
#endif

    /* ----------------------------------------------------- */
    /* Terminate active TP Rx session when no buffer present */
    /* ----------------------------------------------------- */
    {
        /* Here the result is E_OK because when Rx buffer is disabled, a TP reception ongoing is possible only with header disabled */
        /* With header disabled and with no buffer to store some data, we are always in the case that all data was correctly transmitted to UL */

        /* Set the result to E_OK */
        lResult_u8 = E_OK;
    }


    /* --------------------------------------------- */
    /* Call UL RxIndication                          */
    /* --------------------------------------------- */

    /* [SWS_SoAd_00640] */
    /* To notify the upper layer about the termination of an active TP transmission on closing a socket connection within SoAd_MainFunction(), SoAd shall call <Up>_[SoAd][Tp]TxConfirmation() with parameter result set to */
    /* (1) E_OK if disconnect is caused by SoAd_CloseSoCon() and all data was correctly transmitted, and */
    /* (2) E_NOT_OK for any other cause. */

    /* If UL RxIndication is needed to be given and callback is configured */
    if( (lULRxIndicationNeeded_b == TRUE)   &&
        (SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].idxTpRxIndication_u8].RxCallback_pfn != NULL_PTR) )
    {
        /* If socket was requested to be closed by upper layer within MainFunction */
        if( lSoAdDyncSocConfig_pst->socConRequestedMode_en == SOAD_EVENT_OFFLINEREQ_UL )
        {
            /* Call UL RxIndication with the result (E_OK or E_NOT_OK) determined previously */
            SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].idxTpRxIndication_u8].RxCallback_pfn(
                                            SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].ulRxPduId_uo,
                                            lResult_u8);
        }
        else
        {
            /* Call UL RxIndication with E_NOT_OK */
            SoAd_CurrConfig_cpst->SoAdTp_RxCallbacks_cpst[SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].idxTpRxIndication_u8].RxCallback_pfn(
                                            SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[lSoAdDyncSocConfig_pst->idxRxPduTable_uo].ulRxPduId_uo,
                                            E_NOT_OK);
        }
    }

    return;
}


/**
 **********************************************************************************************************************
 * \Function Name : SoAd_TpTxConfirmationToUl()
 *
 * \Function description
 * This service shall invoke a call back to inform the upper layer about the mode change of the socket connection .
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     StaticSocketId_uo - static socket id whose tp tx confirmation to be informed to UL.
 * \param   PduIdType
 * \arg     TxPduId_uo  - Index of Tx Pdu table.
 * \param   PduLengthType
 * \arg     PduLength_uo  - No of bytes transmitted.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 **********************************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_TpTxConfirmationToUl( VAR( SoAd_SoConIdType, AUTOMATIC )  StaticSocketId_uo,   \
                                                   VAR(PduIdType, AUTOMATIC)           TxPduId_uo,          \
                                                   VAR( PduLengthType, AUTOMATIC )     PduLength_uo )
{

    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSoConGrpConfigType_tst, AUTOMATIC, AUTOMATIC)    lSoAdStaticSoConGrpConfig_cpst;

    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;

    /* Local pointer to store the Dynamic array for given Index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst ;

    /* variable to store the dynamic socket connection table index */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

    /*Initialization of variables */
    /* copy the global array index address to local pointer for further processing */
    lSoAdStaticSocConfig_cpst   = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[StaticSocketId_uo]);

    /* Get static socket Group configuration pointers */
    lSoAdStaticSoConGrpConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo]);

    /* Get the index of the dynamic soc table */
    lIdxDynSocket_uo         = (*lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo);

    /* Get the index of related socket connection group */
    lSoAdDyncSocConfig_pst   =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

#if ( SOAD_TP_TCP_PRESENT != STD_OFF )
    /*SoAdSocketTcpImmediateTpTxConfirmation  is TRUE and protocol TCP and upper layer TP*/
    if( ( TCPIP_IPPROTO_TCP == lSoAdStaticSoConGrpConfig_cpst->soConGrpProtocol_en ) && \
        ( STD_ON == lSoAdStaticSoConGrpConfig_cpst->tcpProtocolConf_cpst->tcpImmediateTpTxConfirm_u8 ) )
    {
        /* Reset the length to zero */
        lSoAdDyncSocConfig_pst->tpTcpCopyTxDataLength_uo = 0;
    }
#endif /* SOAD_TP_TCP_PRESENT != STD_OFF */

    /* Condition check: Transmitted length should be greater than zero */
    if( ( (FALSE != lSoAdStaticSoConGrpConfig_cpst->headerEnable_b ) && \
          (((lSoAdDyncSocConfig_pst->tpTransmittedLength_uo == 0) && (PduLength_uo >= SOAD_PDUHDR_SIZE)) || \
           ((lSoAdDyncSocConfig_pst->tpTransmittedLength_uo != 0) && (PduLength_uo > 0)))) \
          || ( (FALSE == lSoAdStaticSoConGrpConfig_cpst->headerEnable_b ) && \
               (PduLength_uo > 0)))
    {
        /* Update the transmitted length with the information given by txconfirmation */
        lSoAdDyncSocConfig_pst->tpTransmittedLength_uo += PduLength_uo;

#ifdef SOAD_DEBUG_AND_TEST
        SoAd_TpTransmittedLength_tst = lSoAdDyncSocConfig_pst->tpTransmittedLength_uo;
#endif

        /* Condition check: If transmitted length is greater than total length of the pdu data */
        if(lSoAdDyncSocConfig_pst->tpTransmittedLength_uo >= lSoAdDyncSocConfig_pst->tpTxTotPduLen_uo)
        {
#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
            /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
             * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
             * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
             * for the same function.
             */
            SoAd_DetErrFlag_u8 = E_NOT_OK;

            SOAD_DET_REPORT_ERROR( (lSoAdDyncSocConfig_pst->tpTransmittedLength_uo > lSoAdDyncSocConfig_pst->tpTxTotPduLen_uo), SOAD_TP_TX_CONFIRMATION_TO_UL_API_ID, SOAD_E_INV_ARG )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF  */

            /* call a function which resets all dynamic table parameters related to TP and inform upper layer */
            SoAd_ResetTpTxDyncParameters(lIdxDynSocket_uo, TxPduId_uo, E_OK);
        }/* End If: if(lSoAdDyncSocConfig_pst->tpTransmittedLength_uo >= lSoAdDyncSocConfig_pst->tpTxTotPduLen_uo)*/

    }
    /* Confirmed length is zero, means some error in transmission */
    else
    {
        /* As the confirmation is given for the length of zero, means there shall be no further data,
         * or some error in data transmission, so reset all dynamic variables */
        /* call a function which resets all dynamic table parameters related to TP and inform upper layer */
        SoAd_ResetTpTxDyncParameters(lIdxDynSocket_uo, TxPduId_uo, E_NOT_OK);

    }/*End for: if( PduLength_uo > 0 ) */
}
#endif /* SOAD_TP_PRESENT != STD_OFF */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TerminateActiveSession()
 *
 * \Function description
 * This service shall trigger the internal function to stop the current TP/IF tx/rx ongoing if any.
 * It has no return value .
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo  - Index of dynamic socket connection table.
 *
 * Parameters (inout): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 ***************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_TerminateActiveSession( VAR( SoAd_SoConIdType, AUTOMATIC )  DynSocketId_uo )
{
    /* Local pointer to store the Dynamic array one by one */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* variable to store the static socket connection table index */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticSocket_uo;

    /* Variable to store the TxPdu id */
    VAR(PduIdType, AUTOMATIC)                               lTxPduId_uo;

    /* Initialization local variables that are declared above */
    lSoAdDyncSocConfig_pst  = &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);
    lIdxStaticSocket_uo     = lSoAdDyncSocConfig_pst->idxStaticSoc_uo;
    lTxPduId_uo             = lSoAdDyncSocConfig_pst->idxTxPduTable_uo;

    /****************************************************************************************************************/
    /****************************************** [SWS_SoAd_00637]: step(1) *******************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /** SoAd shall perform the following actions within SoAd_MainFunction() to close a socket connection:         ***/
    /** 1. Terminate active TP sessions (if any) and notify the upper layer about the termination                 ***/
    /****************************************************************************************************************/
    /****************************************************************************************************************/

#if (SOAD_TP_PRESENT != STD_OFF)
    /* --------------------------------------------- */
    /* Stop TP Tx ongoing                            */
    /* --------------------------------------------- */

    /* check for tpTransmissionOnGoing_b is TRUE, It will be TRUE only for TP type */
    if( TRUE == lSoAdDyncSocConfig_pst->tpTransmissionOnGoing_b )
    {
        /* cal the function to stop the ongoing transmission */
        SoAd_TerminateActiveTpTxSession(DynSocketId_uo);

        lSoAdDyncSocConfig_pst->tpTransmissionOnGoing_b = FALSE;

        /*Reset the remaining length to 0 if socket is requested to close by UL/SoAd */
        lSoAdDyncSocConfig_pst->tpTxRemainingLength_uo = 0;

#ifdef SOAD_DEBUG_AND_TEST
        SoAd_TpTransmissionOnGoing_tst = lSoAdDyncSocConfig_pst->tpTransmissionOnGoing_b;
#endif
    }


    /* --------------------------------------------- */
    /* Stop TP Rx ongoing                            */
    /* --------------------------------------------- */

    /* Check for tpReceptionOngoing_b is TRUE, It will be TRUE only for TP type */
    if( TRUE == lSoAdDyncSocConfig_pst->tpReceptionOngoing_b )
    {
        /* Call the function to stop the ongoing reception */
        SoAd_TerminateActiveTpRxSession(DynSocketId_uo);

        lSoAdDyncSocConfig_pst->tpReceptionOngoing_b = FALSE;
    }
#endif /* SOAD_TP_PRESENT != STD_OFF */

#if ( SOAD_NUM_TX_IF_TCP_PDU > 0 )
    /* --------------------------------------------- */
    /* Pending Tcp Tx confirmation                   */
    /* --------------------------------------------- */

    /*Check if TxConfirmation is pending for the Pdu mapped to the socket if TCP.*/
    if( ( TCPIP_IPPROTO_TCP == (SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].soConGrpId_uo].soConGrpProtocol_en) ) &&\
        ( SoAd_CurrConfig_cpst->SoAd_noTxPdus_cuo > lTxPduId_uo ) &&\
        ( SOAD_IF == SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[lTxPduId_uo].txUpperLayerType_en) )
    {
        /* while passing the length, just subtract the already acked length by remote */
        SoAd_IfTcpTxConfirmationToUl(DynSocketId_uo, lTxPduId_uo, (lSoAdDyncSocConfig_pst->ifTxTcpPduLenReqByUL_uo - lSoAdDyncSocConfig_pst->ifTxTcpAckedDataLen_uo), TRUE );
    }
#ifdef SOAD_DEBUG_AND_TEST
    else
    {
        SoAd_IfTcpRemLenArrAccessChkForTpPkt = FALSE;
    }
#endif /*SOAD_DEBUG_AND_TEST*/
#endif /* SOAD_NUM_TX_IF_TCP_PDU > 0 */

#if ( SOAD_NUM_nPDU_UDP_TX_SOCKET > 0 )
    /* --------------------------------------------- */
    /* nPdu Termination                              */
    /* --------------------------------------------- */

    if( SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticSocket_uo].nPduUdpTxTableIndex_uo < SOAD_CFG_nPDU_UDP_TX_DEFAULT_VALUE )
    {
        /* Execute the sending of all Pdus stored in nPdu */
        SoAd_nPduUdpTxSendAllPdus(lIdxStaticSocket_uo);
    }
#endif

    return;
}

#if (SOAD_NUM_TX_IF_TCP_PDU > 0)
/**
 **********************************************************************************************************************
 * \Function Name : SoAd_IfTcpTxConfirmationToUl()
 *
 * \Function description
 *  This function is called from SoAd_TxConfirmation to handle the TxConfirmation for IF TCP path and post the
 *  TxConfirmation callback to corresponding UL.
 *
 *  Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     DynSocketId_uo - Dynamic socket no of SoAd table.
 * \param   PduIdType
 * \arg     TxPduId_uo - Tx Pdu Id.
 * \param   uint16
 * \arg     Length_u16 - Number of transmitted data bytes.
 * \param   boolean
 * \arg     CloseReq_b - Close request has been triggerd or not.
 *                       If function is called from SoAd_TerminateActiveSession() means close req has been triggered,
 *                       else not.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 **********************************************************************************************************************
 */
FUNC( void, SOAD_CODE ) SoAd_IfTcpTxConfirmationToUl(VAR(SoAd_SoConIdType, AUTOMATIC)    DynSocketId_uo, \
                                                     VAR(PduIdType, AUTOMATIC)           TxPduId_uo, \
                                                     VAR(uint16, AUTOMATIC)              Length_u16, \
                                                     VAR(boolean, AUTOMATIC)             CloseReq_b)
{
    /* Local pointer to store the Tx Pdu table for given index */
    P2CONST(SoAd_TxPduConfigType_tst, SOAD_VAR, SOAD_VAR)       lSoAdTxPduConfig_cpst ;

    /* local pointer to store the IfTcpPduTxPendingStatus array for given index */
    P2VAR(SoAd_IfTcpPduTxPendingStatus_tst, SOAD_VAR, SOAD_VAR) lSoAdIfTcpPduTxPendingStatus_pst;

    /* Local pointer to store the Dynamic array for given Index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)       lSoAdDyncSocConfig_pst ;

    /*Initialization of local variables */
    /* Get the Tx Pdu pointer for given index */
    lSoAdTxPduConfig_cpst   = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[TxPduId_uo]);

    lSoAdIfTcpPduTxPendingStatus_pst = &(SoAd_IfTcpPduTxPendingStatus_ast[lSoAdTxPduConfig_cpst->txIfTcpPduIndex_u8]);

    /* copy the global array index address to local pointer for further processing */
    lSoAdDyncSocConfig_pst   =  &(SoAd_DyncSocConfig_ast[DynSocketId_uo]);

    /*Check if the pending TxConfimration length is greater than zero and can be decremetned*/
    if((lSoAdIfTcpPduTxPendingStatus_pst->ifTcpTxConfRemainingLen_au32 > 0u) && \
       (lSoAdIfTcpPduTxPendingStatus_pst->ifTcpTxConfRemainingLen_au32 >= Length_u16))
    {
        /*decrement the pending TxConfirmation length for the Pdu */
        lSoAdIfTcpPduTxPendingStatus_pst->ifTcpTxConfRemainingLen_au32 -= Length_u16;

        /* increment the ifTxTcpAckedDataLen_uo with Length_u16 to check whether whole transmitted packets has been acked by remote */
        lSoAdDyncSocConfig_pst->ifTxTcpAckedDataLen_uo += Length_u16;

        /* Check if whole packet has been acked by remote */
        if(lSoAdDyncSocConfig_pst->ifTxTcpAckedDataLen_uo >= lSoAdDyncSocConfig_pst->ifTxTcpPduLenReqByUL_uo)
        {
            /* CloseReq_b will be FALSE, if this function is called from SoAd_TxConfirmation(), otherwise TRUE */
            if( FALSE == CloseReq_b )
            {
                /* set the ifTcpTxConfReceivedStatus_b flag to TRUE to indicate that pdu has been transmitted and Acked by atleast one remote */
                /* Ideally Main intension of this Flag is
                 * Suppose if 2 remotes are active, PDU data will be transmitted to both the remote and wait for ACK from both.
                 * In some scenarios, lower layer can close the SoAd socket conection due to remote can terminate the connection or retransmission time out or some other scenarios,
                 * USECASE for this Flag:
                 *      SoAd has sent the data to 2 remote and TxConfirmation has come from 1 remote and socket for other remote has been close by lower layer.
                 *      During this scenario, SoAd has to give the TxConfirmation to UL or not?
                 *
                 * Design :
                 *      1. If SoAd receives atleast 1 complete TxConfirmation from any one of the remote and other sockets are closed, then SoAd has to give TxConfimation to UL.
                 *         Ideally SoAd has to wait for atleast one notification either TxConfirmation or close notification.
                 *      2. suppose if all sockets are closed by lower layer, then SoAd should not give TxConfirmation to UL.
                 */
                lSoAdIfTcpPduTxPendingStatus_pst->ifTcpTxConfReceivedStatus_b = TRUE;
            }
            /* Reset the txpduid, acked length and UL req pdulen in dynamic config table */
            lSoAdDyncSocConfig_pst->idxTxPduTable_uo        = SOAD_CFG_PDU_ID_DEFAULT_VALUE ;
            lSoAdDyncSocConfig_pst->ifTxTcpAckedDataLen_uo     = 0;
            lSoAdDyncSocConfig_pst->ifTxTcpPduLenReqByUL_uo = 0;
        }

        /*If pending TxConfirmation length is zero it measn that all data has be confirmed
         * and UL_TxConfirmation can be given if configured*/
        if( 0u == lSoAdIfTcpPduTxPendingStatus_pst->ifTcpTxConfRemainingLen_au32 )
        {
            /* If transmitted packet has been acked by atleast 1 remote if fan-out is configured*/
            if( TRUE == lSoAdIfTcpPduTxPendingStatus_pst->ifTcpTxConfReceivedStatus_b )
            {
                /* check TxConfirmation has to be given to UL
                 * there are two scenarios, SoAd wont give UL_TxConfirmation
                 * 1. No callback function has been configured
                 * 2. SoAd_IfTransmit() function returns E_NOT_OK
                 */
                if(NULL_PTR != SoAd_CurrConfig_cpst->SoAdIf_TxCallbacks_cpst[lSoAdTxPduConfig_cpst->idxIfTxConfirm_u8].TxCallback_pfn)
                {
                    /* Call back the upper layer with txPduId to inform about IfTxConfirmation  */
                    SoAd_CurrConfig_cpst->SoAdIf_TxCallbacks_cpst[lSoAdTxPduConfig_cpst->idxIfTxConfirm_u8].TxCallback_pfn(
                                                                    lSoAdTxPduConfig_cpst->ulTxPduId_uo);
                }

                /* Reset it to FALSE if TxConfirmation is received from all the remotes if pdu fan-out is confirgured */
                lSoAdIfTcpPduTxPendingStatus_pst->ifTcpTxConfReceivedStatus_b    = FALSE;
            }

#ifdef SOAD_DEBUG_AND_TEST
            Soad_TxConfirmationFlag_tst = 1;
#endif
        }
    }
    else
    {
        /* Reset the txpduid, acked length and UL req pdulen in dynamic config table since the TxConfirmation was invalid*/
        lSoAdDyncSocConfig_pst->idxTxPduTable_uo        = SOAD_CFG_PDU_ID_DEFAULT_VALUE ;
        lSoAdDyncSocConfig_pst->ifTxTcpAckedDataLen_uo  = 0;
        lSoAdDyncSocConfig_pst->ifTxTcpPduLenReqByUL_uo = 0;
    }
}
#endif /* SOAD_NUM_TX_IF_TCP_PDU > 0 */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
