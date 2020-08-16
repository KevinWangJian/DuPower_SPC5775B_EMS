

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

#if ( (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
static FUNC( void, SOAD_CODE ) SoAd_TpCancelTransmitDetChk( VAR( PduIdType, AUTOMATIC )  TxPduId_uo );
#endif /* (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TpCancelTransmit()
 *
 * \Function description
 * Requests cancellation of the transmission via TP for a specific I-PDU
 *
 * Parameters (in):
 * \param   PduIdType
 * \arg     PduId - Identifiaction of the I-PDU to be cancelled.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):

 * Return value :Std_ReturnType
 * \retval  E_OK :      The request was successful
 *          E_NOT_OK:   The request was not successful
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_TpCancelTransmit( VAR( PduIdType, AUTOMATIC )  PduId)
{
#if ( (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
    /* pointer to store the pduroutedest information */
    P2CONST(PduRouteDestType_tst, AUTOMATIC, AUTOMATIC)     lPduRRouteDest_cpst;

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* Variable to hold the index of PduRouteDests configured for this PduRoute*/
    VAR(PduIdType, AUTOMATIC)                               lIdxOfPduRouteDest_uo;

    /* Variable to hold the index of the static soc table */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxstaticsocket_uo;

    /* Variable to hold the index of the dynamic socket connection table*/
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /*Variable to store the number of pdu route destinations*/
    VAR(PduIdType, AUTOMATIC)                               lNumberofPduRouteDests_uo;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_TpCancelTransmitDetChk(PduId);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        /* Get the number of PduRouteDests configured with this PduRoute */
        lNumberofPduRouteDests_uo = SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[PduId].PduRouteDestNum_uo ;

        /* Extract pointer to first element of Pdu route destination structure */
        lPduRRouteDest_cpst = ( SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[PduId].PduRouteDestConf_cpst );

        /* Loop through all the route dests to transmit the Pdu */
        for( lIdxOfPduRouteDest_uo =0; lIdxOfPduRouteDest_uo < lNumberofPduRouteDests_uo; lIdxOfPduRouteDest_uo++)
        {
            /* Get the static socket index value for the associated TxPdu  */
            lIdxstaticsocket_uo = ( lPduRRouteDest_cpst[lIdxOfPduRouteDest_uo].txStaticSocketOrGroupIdx_uo );

            /* Get "the dynamic socket index value" from the static socket table  */
            lIdxDynSocket_uo =   (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxstaticsocket_uo].SoAd_Prv_idxDynSocTable_puo) ;
#ifdef SOAD_DEBUG_AND_TEST
            SoAd_DynSocket_tst = lIdxDynSocket_uo;
#endif

            /* Condition check: Dynamic socket shall be valid */
            if(lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo )
            {
                /* Condition check: Dynamic socket shall be valid and the socket connection shall be ONLINE */
                /*                      and Socket is not requested to close (not in a position which blocks Tx and Rx )
                 * Cancel transmit request is called for a particular PduId, so SoAd shall check whether the requested PduId
                 * related transmission is going on? or for example 4 TxPdus linked with same socket, TpTransmission is going on related
                 * with the 1st TxPdu, and cancel transmit request comes for 3rd TxPdu, then SoAd should not cancel the transmission of
                 * 1st TxPdu.*/
                if( ( SOAD_SOCON_ONLINE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConMode_en ) && \
                    ( TRUE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpTransmissionOnGoing_b ) )
                {
                    /* set a request to cancel it in next main function */
                    SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD ;

                    /* set lFunctionRetVal_u8 to E_OK */
                    lFunctionRetVal_u8 = E_OK;

                }
            }
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
#else
    (void)PduId;

    return(E_NOT_OK);
#endif /* SOAD_TP_CANCEL_COM_ENABLED != STD_OFF &&  && SOAD_TP_PRESENT != STD_OFF*/
}


#if ( (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TpCancelTransmitDetChk()
 *
 * \function description
 * This function is called from SoAd_TpCancelTransmit to handle the DET error for function arguments.
 * It covers SWS_SoAd_00605 & SWS_SoAd_00606 requirements
 *
 *  Parameters (in):
 * \param   PduIdType
 * \arg     TxPduId_uo - Identifiaction of the I-PDU to be cancelled.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TpCancelTransmitDetChk( VAR( PduIdType, AUTOMATIC )  TxPduId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_TP_CANCEL_TRANSMIT_API_ID, SOAD_E_NOTINIT )

    /* Check whether PduId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noTxPdus_cuo <= TxPduId_uo ), SOAD_TP_CANCEL_TRANSMIT_API_ID, SOAD_E_INV_PDUID )

}
#endif /* (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
