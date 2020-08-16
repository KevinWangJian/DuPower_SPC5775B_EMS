

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

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
static FUNC( void, SOAD_CODE ) SoAd_GetSoConIdDetChk( VAR( PduIdType, AUTOMATIC )                        TxPduId_uo ,\
                                                      P2CONST( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )  SoConId_cpuo );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 *************************************************************************************************************************************
 * \Function Name : SoAd_GetSoConId()
 *
 * \Function description
 * Returns socket connection index related to specified transmit PduId.
 * In case a fan-out is configured for TxPduId (i.e. multiple SoAdPduRouteDest specified) E_NOT_OK shall be returned
 *
 * Parameters (in):
 * \param   PduIdType
 * \arg     TxPduId - Transmit PduId specifying the SoAd socket connection for which the socket connection index shall be returned.
 *
 * Parameters (inout):  None
 *
 * Parameters (out):
 * \param   SoAd_SoConIdType *
 * \arg     SoConIdPtr - Pointer to memory receiving the socket connection index asked for.
 *
 * Return value :
 * \retval  E_OK :      The request was successful
 *          E_NOT_OK:   The request was not successful
 *
 ***************************************************************************************************************************************
 */

FUNC( Std_ReturnType, SOAD_CODE ) SoAd_GetSoConId( VAR( PduIdType, AUTOMATIC )                      TxPduId ,\
                                                   P2VAR( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )  SoConIdPtr )

{
    /* Local pointer to store the Tx Pdu table for given index */
    P2CONST(SoAd_TxPduConfigType_tst, SOAD_VAR, SOAD_VAR)       lSoAdTxPduConfig_cpst ;

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                              lFunctionRetVal_u8;

#if ( SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF )
    /* Variable to store the SoconGroupId if BundleGroup is Refering to the Socket Connection Group */
    VAR(SoAd_SoConIdType,AUTOMATIC)                             lSoConGrpId;
#endif /* SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF */

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_GetSoConIdDetChk(TxPduId, (const SoAd_SoConIdType*)SoConIdPtr);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Get the Tx Pdu pointer for given index */
        lSoAdTxPduConfig_cpst = &(SoAd_CurrConfig_cpst->SoAd_TxPduConfig_cpst[TxPduId]);

        /****************************************************************************************************************/
        /****************************************** [SWS_SoAd_00724] ****************************************************/
        /****************************************************************************************************************/
        /****************************************************************************************************************/
        /** In case SoAd_GetSoConId() is called with a TxPduId related to a SoAdPduRoute with a fan-out (i.e. multiple **/
        /** SoAdPduRouteDest specified), SoAd_GetSoConId() shall skip further processings and return E_NOT_OK          **/
        /****************************************************************************************************************/

        /* Enter only If fanout (multiple PduRouteDests)NOT configured)*/
        if( 1U == lSoAdTxPduConfig_cpst->PduRouteDestNum_uo )
        {
#if ( SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF )
            /*Check if the Bundle reference is mapped to the socket connection */
            if( SOAD_SOCKET_BUNDLE_REFERENCE == lSoAdTxPduConfig_cpst->PduRouteDestConf_cpst->identifyTxSocketConnOrGroupRef_b )
            {
                /* The local variable is updated with the Socket Connection Group Id  */
                lSoConGrpId = (lSoAdTxPduConfig_cpst->PduRouteDestConf_cpst->txStaticSocketOrGroupIdx_uo) ;

                /* For the Socket connnection Group find the number of socket connections ,Enter only if there is one socket connection*/
                if(1U == SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoConGrpId].maxSoConChannel_uo  )
                {
                    /*The socket Id associated with the given PduId shall be updated in the pointer given by the upper layer*/
                    (* SoConIdPtr) = SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[lSoConGrpId].startSoConIdx_uo ;

                    /* retVal is set to E_OK */
                    lFunctionRetVal_u8 = E_OK;
                }
            }
            else
#endif /* SOAD_SOCON_TX_BUNDLE_REF_ENABLE != STD_OFF */
            {
                /* The socket Id associated with the given PduId shall be updated in the pointer given by the upper layer */
                (* SoConIdPtr) = lSoAdTxPduConfig_cpst->PduRouteDestConf_cpst->txStaticSocketOrGroupIdx_uo  ;

                /* retVal is set to E_OK */
                lFunctionRetVal_u8 = E_OK;
            }
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 ****************************************************************************************************************************************
 * \Function Name : SoAd_GetSoConIdDetChk()
 *
 * \function description
 * This function is called from SoAd_GetSoConId to handle the DET error for function arguments.
 * It covers SWS_SoAd_00609 & SWS_SoAd_00610 requirements
 *
 *  Parameters (in):
 * \param   PduIdType
 * \arg     TxPduId_uo - Transmit PduId specifying the SoAd socket connection for which the socket connection index shall be returned.
 * \param   const SoAd_SoConIdType *
 * \arg     SoConId_cpuo - Pointer to memory receiving the socket connection index asked for.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 *****************************************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_GetSoConIdDetChk( VAR( PduIdType, AUTOMATIC )                        TxPduId_uo ,\
                                                      P2CONST( SoAd_SoConIdType, AUTOMATIC, AUTOMATIC )  SoConId_cpuo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_GET_SOCON_API_ID, SOAD_E_NOTINIT )

    /* Check whether TxPduId is valid or not */
    SOAD_DET_REPORT_ERROR( ( SoAd_CurrConfig_cpst->SoAd_noTxPdus_cuo <= TxPduId_uo ), SOAD_GET_SOCON_API_ID, SOAD_E_INV_PDUID )

    /* Check whether SoConIdPtr pointer is valid or not */
    SOAD_DET_REPORT_ERROR( ( NULL_PTR == SoConId_cpuo ), SOAD_GET_SOCON_API_ID, SOAD_E_PARAM_POINTER )

}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
