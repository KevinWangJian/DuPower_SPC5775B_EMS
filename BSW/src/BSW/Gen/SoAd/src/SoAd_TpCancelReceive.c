

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "SoAd.h"
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
static FUNC( void, SOAD_CODE ) SoAd_TpCancelReceiveDetChk( VAR( PduIdType, AUTOMATIC )  RxPduId_uo );
#endif /* (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_TpCancelReceive()
 *
 * \Function description
 * Requests cancellation of the reception for a specific I-PDU
 *
 * Parameters (in):
 * \param   PduIdType
 * \arg     PduId - Identifiaction of the I-PDU to be cancelled.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):

 * Return value :Std_ReturnType
 * \retval  E_OK:       request accepted (but not yet performed).
 *          E_NOT_OK:   request not accepted (e.g. cancellation not possible).
 *
 ***************************************************************************************************
 */

FUNC( Std_ReturnType, SOAD_CODE ) SoAd_TpCancelReceive( VAR( PduIdType, AUTOMATIC )  PduId)
{
#if ( (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) )
    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)      lFunctionRetVal_u8;

    /* Variable to hold the index of the static soc table */
    VAR(SoAd_SoConIdType, AUTOMATIC)    lIdxstaticsocket_uo;

    /* Variable to hold the index of the dynamic socket connection table*/
    VAR(SoAd_SoConIdType, AUTOMATIC)    lIdxDynSocket_uo;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_TpCancelReceiveDetChk(PduId);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        /* get the static socket id from the RxPdu */
        lIdxstaticsocket_uo = SoAd_CurrConfig_cpst->SoAd_RxPduConfig_cpst[PduId].rxStaticSocketOrGroupIdx_uo;

        /* Get "the dynamic socket index value" from the static socket table  */
        lIdxDynSocket_uo =   (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[lIdxstaticsocket_uo].SoAd_Prv_idxDynSocTable_puo) ;

        /*Internal Check: lIdxDynSocket_uo shall be within the range*/
        if(lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo )
        {
            /* condition check: if TP Reception is going on */
             /*Cancel receive request is called for a particular PduId, so SoAd shall check whether the requested PduId
             * related reception is going on? or for example 4 RxPdus linked with same socket, TpReception is going on related
             * with the 1st RxPdu, and cancel Receive request comes for 3rd RxPdu, then SoAd should not cancel the Reception of
             * 1st RxPdu.*/
            if( ( SOAD_SOCON_ONLINE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConMode_en ) && \
                ( TRUE == SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].tpReceptionOngoing_b ) )
            {
                /* set a request to cancel it in next main function: as per SWS_SoAd_00581 */
                SoAd_DyncSocConfig_ast[lIdxDynSocket_uo].socConRequestedMode_en = SOAD_EVENT_OFFLINEREQ_SOAD ;

                /* set lFunctionRetVal_u8 to E_OK */
                lFunctionRetVal_u8          = E_OK;

            }
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
#else
    (void)PduId;

    return(E_NOT_OK);
#endif /* SOAD_TP_CANCEL_COM_ENABLED != STD_OFF && SOAD_TP_PRESENT != STD_OFF */
}


#if ( (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) )
/**
 ***************************************************************************************************
 * \Function Name : SoAd_TpCancelReceiveDetChk()
 *
 * \function description
 * This function is called from SoAd_TpCancelReceive to handle the DET error for function arguments.
 * It covers SWS_SoAd_00607 & SWS_SoAd_00608 requirements
 *
 *  Parameters (in):
 * \param   PduIdType
 * \arg     RxPduId_uo - Identifiaction of the I-PDU to be cancelled.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ***************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_TpCancelReceiveDetChk( VAR( PduIdType, AUTOMATIC )  RxPduId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_TP_CANCEL_RECEIVE_API_ID, SOAD_E_NOTINIT )

    /* Check whether PduId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noRxPdus_uo <= RxPduId_uo ), SOAD_TP_CANCEL_RECEIVE_API_ID, SOAD_E_INV_PDUID )

}
#endif /* (SOAD_TP_CANCEL_COM_ENABLED != STD_OFF) && (SOAD_TP_PRESENT != STD_OFF) && ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF ) */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
