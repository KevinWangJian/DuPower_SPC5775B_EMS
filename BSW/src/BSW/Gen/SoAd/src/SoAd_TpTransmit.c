

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
#ifdef SOAD_DEBUG_AND_TEST
#include "TestSoAdApplication.h"
#endif
#ifdef SOAD_CONFIGURED
#include "Det.h"

#include "SoAd_Prv.h"

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

#if ( (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
static FUNC( void, SOAD_CODE )          SoAd_TpTransmitDetChk        ( VAR( PduIdType, AUTOMATIC )                   SoAdSrcPduId_uo , \
                                                                       P2CONST( PduInfoType, AUTOMATIC, AUTOMATIC )  SoAdSrcPduInfoPtr_cpuo );
#endif /* (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TpTransmit()
 *
 * \function description
 * This service is utilized to request the transfer of data. It sets a flag for indicating that a transmit request is present.
 * This function has to be called with the PDU-ID of the SoAd,
 * i.e. the upper layer has to translate its own PDU-ID into the one of the SoAd for the corresponding message.
 * This call shall fail if no entry for the PDU-ID can be found in the socket connection table.
 * Within the provided SoAdSrcPduInfoPtr only SduLength is valid (no data)!
 * If this function returns E_OK then there will arise a call of <Ul>_SoAdCopyTxData in order to get data for sending.
 *
 * Parameters (in):
 * \param   PduIdType
 * \arg     SoAdSrcPduId        - This parameter contains a unique identifier referencing to the PDU Routing Table
 *                                 and thereby specifying the socket to be used for transmission of the data.
 * \param   const PduInfoType*
 * \arg     SoAdSrcPduInfoPtr   - A pointer to a structure with socket related data: data length and pointer to a data buffer.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval   E_OK             - The request has been accepted
 *           E_NOT_OK         - The request has not been accepted,
 *                              e.g. due to a still ongoing transmission in the corresponding socket or the to be transmitted message is too long.
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_TpTransmit( VAR( PduIdType, AUTOMATIC )  SoAdSrcPduId , \
                                                   P2CONST( PduInfoType, AUTOMATIC, AUTOMATIC )  SoAdSrcPduInfoPtr )
{
#if (SOAD_TP_PRESENT != STD_OFF)
    /* Pointer to hold the Pdu route destination structure*/
    P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)     lPduRouteDest_cpst;

    /* Local pointer to store the Static array for given index*/
    P2CONST(SoAd_StaticSocConfigType_tst, AUTOMATIC, AUTOMATIC)         lSoAdStaticSocConfig_cpst;

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* Variable to hold the index of the static socket connection table */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxStaticsocket_uo;

    /* Variable to hold the index of the dynamic socket connection table*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Variable to hold the number of PduRouteDests configured for this PduRoute*/
    VAR(PduIdType, AUTOMATIC)                               lNumberOfPduRouteDests_uo;

    /* Variable to hold the index of PduRouteDests configured for this PduRoute*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxOfPduRouteDest_uo;

    /* variable to hold the total pdu length of the SoAd Frame */
    VAR(PduLengthType, AUTOMATIC)                           lTotalPduLength_uo;

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
    /* Routing Group Status */
    VAR(boolean, AUTOMATIC)                                 lRgStatus_b;
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    SoAd_TpTransmitDetChk(SoAdSrcPduId, SoAdSrcPduInfoPtr);

    /****************************************************************************************************************/
    /****************************************** [SWS_SoAd_00551]: Step (1) ******************************************/
    /****************************************************************************************************************/
    /****************************************************************************************************************/
    /******************** Skip further processing and return with E_NOT_OK if the PDU length is 0 *******************/
    /****************************************************************************************************************/

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     * 2. UL of the Pdu should be type TP.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialization of the local variables */
        lIdxDynSocket_uo            = SOAD_CFG_SOCON_ID_DEFAULT_VALUE;

        /* Get the number of PduRouteDests configured with this PduRoute */
        lNumberOfPduRouteDests_uo = SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[SoAdSrcPduId].PduRouteDestNum_uo ;

        /* Extract pointer to first element of Pdu route destination structure */
        lPduRouteDest_cpst = ( SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[SoAdSrcPduId].PduRouteDestConf_cpst );

        /* Loop through all the route dests to transmit the Pdu If socket is ONLINE*/
        for( lIdxOfPduRouteDest_uo = 0; lIdxOfPduRouteDest_uo < lNumberOfPduRouteDests_uo; lIdxOfPduRouteDest_uo++ )
        {
            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00551]: Step (2)*******************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /*Identify the related socket connection and PDU route by using the SoAdSrcPduId provided at SoAd_TpTransmit(). */
            /****************************************************************************************************************/

            /* Get "index of the static socket table" from TxPduconfig Table */
            lIdxStaticsocket_uo = lPduRouteDest_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo;

            /* Get static socket configuration pointers */
            lSoAdStaticSocConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxStaticsocket_uo]);

            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00561] ****************************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /*** If SoAd_TpTransmit() is called with SoAdSrcPduId specifying a SoAdPduRouteDest which belongs only to     ***/
            /*** inactive RoutingGroups, SoAd shall always skip the transmission for this SoAdPduRouteDest and shall      ***/
            /*** consider the transmission as successful unless all SoAdPduRouteDest of a SoAdPduRoute belong only to     ***/
            /*** inactive RoutingGroups. In the latter case SoAd shall return E_NOT_OK.                                   ***/
            /****************************************************************************************************************/

#if (SOAD_ROUTING_GROUPS_ENABLE != STD_OFF)
            /* call the internal function to retrieve the Routing Group status for the combination of RG's Id and associated SoCon Id */
            /* Check Routing Group is enabled for the fetched socket */
            lRgStatus_b = ( 0U < lPduRouteDest_cpst[lIdxOfPduRouteDest_uo].numOfTxRoutingGroups_uo ) ? \
                           ( SoAd_GetRoutingGroupsEnabledStatus( \
                                   lPduRouteDest_cpst[lIdxOfPduRouteDest_uo].txRoutingGroupConf_cpuo, \
                                   lPduRouteDest_cpst[lIdxOfPduRouteDest_uo].numOfTxRoutingGroups_uo, \
                                   lIdxStaticsocket_uo) ): \
                                   TRUE;

            /* Condition check : Routing group of the corresponding Socket should be enabled */
            if( FALSE != lRgStatus_b )
#endif /* SOAD_ROUTING_GROUPS_ENABLE != STD_OFF */

            {
                /* Get "index of the dynamic socket table" from static socket table */
                lIdxDynSocket_uo = ( *lSoAdStaticSocConfig_cpst->SoAd_Prv_idxDynSocTable_puo );
            }/*End of If condition: Routing Group is enabled*/

            /* Condition checks:
             * 1. Check Dynamic socket index is valid.
             * 2. Check for socket connection is ONLINE.
             * 3. Check socket is not requested to close by UL.
             */
            if ( ( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
              && ( SOAD_SOCON_ACTIVE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConSubMode_en )
              && ( ( 0U == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConCloseReqCnt_u16 )
              ||   ( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConCloseReqCnt_u16 < SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConOpenReqCnt_u16 ) )

              /****************************************************************************************************************/
              /*************************************** [SWS_SoAd_00650 ] ******************************************************/
              /****************************************************************************************************************/
              /****************************************************************************************************************/
              /*** The service SoAd_If/TpTransmit() shall skip the transmit request and return E_NOT_OK if there is already ***/
              /*** an IF or TP transmission ongoing on the related socket connection identified by SoAdSrcPduId             ***/
              /****************************************************************************************************************/

              /* Condition checks:
               * 1. Check socket is requested to close by SoAd.
               * 2. Check TP Transmission is ongoing.
               * 3. Check IF Transmission is ongoing
               * 4. Check any of the pdu transmission is still ongoing, it means no TxConfirmation from lower layer
               */

              && ( FALSE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].discardNewTxRxReq_b )
              && ( FALSE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTransmissionOnGoing_b )
#if (SOAD_IF_PRESENT != STD_OFF )
              && ( FALSE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].ifTransmissionOnGoing_b )
#endif /* SOAD_IF_PRESENT != STD_OFF */
              && ( SOAD_CFG_PDU_ID_DEFAULT_VALUE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxTxPduTable_uo ) )

            {
                /* Get the additional length 8 bytes(Header(4) + Length(4)) if headerEnable_b for TxPDU is enabled,
                 * extra  SOAD_PDUHDR_SIZE shall be added in front of the PDU if header is enabled */
                lTotalPduLength_uo = ( PduLengthType ) ( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoAdStaticSocConfig_cpst->soConGrpId_uo].headerEnable_b == TRUE ) ? SOAD_PDUHDR_SIZE : 0U );

#if ( ( SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0 ) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
                /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
                 * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
                 * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
                 * for the same function.
                 */
                SoAd_DetErrFlag_u8 = E_NOT_OK;

                /* Check whether SoAd Init function was already called or not */
                SOAD_DET_REPORT_ERROR( ( ( SOAD_CFG_TP_UDP_TXBUFFER_DEFAULT_VALUE > lSoAdStaticSocConfig_cpst->tpUdpTxBuffIdx_uo ) &&
                                         ( ( SoAdSrcPduInfoPtr->SduLength + lTotalPduLength_uo ) >
                                           ( SoAd_CurrConfig_cpst->SoAdTp_UdpTransmitBufferInfo_cpu8)[lSoAdStaticSocConfig_cpst->tpUdpTxBuffIdx_uo].tpUdpTxBufferSize_u16 ) ), SOAD_TP_TRANSMIT_API_ID, SOAD_E_INV_ARG )

                /* Condition checks:
                 * If there is no DET error if DET is switch On.
                 */
                if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* ( SOAD_NUM_TP_UDP_TX_BUFFER_SOCKET > 0 ) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )  */
                {
                    /* Update the variable "index of txpdu config table" in dynamic socket connection table
                     * so that no other Tx Pdu's can be trnamitted via the smae socket */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].idxTxPduTable_uo   = SoAdSrcPduId ;

                    /* Load the txPduHeaderId_u32 to dynamic table to use it in SoAd_CopyTxData( ) function */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].txPduHeaderId_u32  = lPduRouteDest_cpst[lIdxOfPduRouteDest_uo].txPduHeaderId_u32;

                    /****************************************************************************************************************/
                    /****************************************** [SWS_SoAd_00551]: Step (3)*******************************************/
                    /****************************************************************************************************************/
                    /****************************************************************************************************************/
                    /*****************Store the TP transmission request for further processing in the SoAd_Main-Function()***********/
                    /****************************************************************************************************************/

                    /* Set the tpTransmitReq of the dynamic soc connection to TRUE to process it in MainFunction */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTransmitRequest_b     = TRUE;

                    /* Set the tpTransmissionOnGoing_b of the dynamic soc connection to TRUE to ignore the
                     * new transmission request on both TP and IF path
                     */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTransmissionOnGoing_b = TRUE;

#ifdef SOAD_DEBUG_AND_TEST
                    SoAd_DynSocket_tst = lIdxDynSocket_uo;
#endif

                    /* Copy the requested pdu length into tpTxTotPduLen_uo variable and it is used to identify the whole requested data's are tranmitted on Ethernet or not */
                    ( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTxTotPduLen_uo )      = SoAdSrcPduInfoPtr->SduLength + lTotalPduLength_uo;

                    /* Load the variable tpTxRemainingLength_uo with the length info given by the upper layer,
                     * this variable will be used to trigger the transmission from MainFunction() for the length */
                    ( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTxRemainingLength_uo ) = ( SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTxTotPduLen_uo ) ;

                    /* Set the retval to E_OK */
                    lFunctionRetVal_u8 = E_OK;
                }/*End of If condition: TP/IF packet is ongoing for the same socket */
            }/*End of If condition: PDU mapped socket is ONLINE */
        }/*End of for loop: PDU Route Dest looping */
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);

#else
    (void)SoAdSrcPduId;
    (void)SoAdSrcPduInfoPtr;

    return(E_NOT_OK);
#endif /* SOAD_TP_PRESENT != STD_OFF */
}

#if ( (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
/**
 **********************************************************************************************************************************
 * \Function Name : SoAd_TpTransmitDetChk()
 *
 * \Function description
 *  This function is called from SoAd_TpTransmit to handle the DET error for function arguments
 * It covers SWS_SoAd_00224 & SWS_SoAd_00237 requirements
 *
 * Parameters (in):
 * \param   PduIdType
 * \arg     SoAdSrcPduId_uo - This parameter contains a unique identifier referencing to the PDU Routing Table
 *                            and thereby specifying the socket to be used for transmission of the data.
 * \param   const PduInfoType*
 * \arg     SoAdSrcPduInfoPtr_cpuo : A pointer to a structure with socket related data: data length and pointer to a data buffer.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:        None
 *
 *
 ***********************************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TpTransmitDetChk( VAR( PduIdType, AUTOMATIC )  SoAdSrcPduId_uo , \
                                                      P2CONST( PduInfoType, AUTOMATIC, AUTOMATIC )  SoAdSrcPduInfoPtr_cpuo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_TP_TRANSMIT_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoAdSrcPduInfoPtr & SduDataPtr pointers are valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == SoAdSrcPduInfoPtr_cpuo) , SOAD_TP_TRANSMIT_API_ID, SOAD_E_PARAM_POINTER )

    /* Check whether lTxPduId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noTxPdus_cuo <= SoAdSrcPduId_uo ), SOAD_TP_TRANSMIT_API_ID, SOAD_E_INV_PDUID )

    /* Check whether pdu length is valid or not */
    SOAD_DET_REPORT_ERROR( ( ( 0 == SoAdSrcPduInfoPtr_cpuo->SduLength ) || \
                             ( SoAdSrcPduInfoPtr_cpuo->SduLength > SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[SoAdSrcPduId_uo].txPduLength_uo ) || \
                             ( SOAD_TP != SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[SoAdSrcPduId_uo].txUpperLayerType_en ) ) , \
                                 SOAD_TP_TRANSMIT_API_ID, SOAD_E_INV_ARG )
}
#endif /* (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */


#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
