

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
static FUNC( void, SOAD_CODE ) SoAd_OpenSoConDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

/**
 ***************************************************************************************************
 * \Function Name : SoAd_OpenSoCon()
 *
 * \Function description
 * This API opens the socket connection specified by SoConId.
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId -socket connection index specifying the socket connection which shall be opened
 *
 * Parameters (inout):  None
 *
 * Parameters (out):    None
 *
 * Return value:
 * \return  Std_ReturnType
 * \retval  E_OK            The request was successful
 *          E_NOT_OK        The request was not successful.
 *
 ***************************************************************************************************
 */
FUNC( Std_ReturnType, SOAD_CODE ) SoAd_OpenSoCon( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId )
{
    /* Local pointer to store the Dynamic array for given index */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)   lSoAdDyncSocConfig_pst ;

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                          lFunctionRetVal_u8;

    /* Index to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                        lIdxDynSocket_uo;

    /* Initialize the funtion return variable to E_NOT_OK */
    lFunctionRetVal_u8  = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_OpenSoConDetChk(SoConId);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        /* Get the index of the dynamic socket table which is linked with this static socket*/
        lIdxDynSocket_uo = ( *SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].SoAd_Prv_idxDynSocTable_puo) ;

        /*Condition check: If the dynamic socket is not linked or allocated to the static socket
         * There is a possibility that SoAd_OpenSoCon shall be called just after SoAd_SetRemoteAddress.
         * So, already a link to dynamic socket table is established at that time. So the same dync socket shall be used now*/
        if(SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo <= lIdxDynSocket_uo )
        {
            /* Get the available dynamic socket from the list by calling a function */
            SoAd_ReserveFreeDynSocket(SoConId, &lIdxDynSocket_uo);
        }

        /* If dynamic socket is valid
         * usecase: SoAd_SetRemoteAddr is called before SoAd_OpenSoCon is called */
        if(lIdxDynSocket_uo < SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo)
        {
            /* copy the global array index address to local pointer for further processing */
            lSoAdDyncSocConfig_pst =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00588] ****************************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /** SoAd shall store a request to open or close a socket connection when called with SoAd_OpenSoCon() and     ***/
            /** SoAd_CloseSoCon() respectively, but handle the request only in the SoAd_MainFunction() respecting the     ***/
            /**             connection setup and shutdown policy.                                                         ***/
            /****************************************************************************************************************/
            /****************************************************************************************************************/

            /* Increment the socConOpenReqCnt_u16 variable by 1 and compare the socConOpenReqCnt_u16 with socConCloseReqCnt_u16 in next MainFunction*/
            /* if no of open req is greater than close req, then set the event to onlinereq, such that open req action shall be taken place in the same main function */
            lSoAdDyncSocConfig_pst->socConOpenReqCnt_u16++;

            lFunctionRetVal_u8 = E_OK;
        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    /* Return the value  */
    return(lFunctionRetVal_u8);
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 *************************************************************************************************************
 * \Function Name : SoAd_OpenSoConDetChk()
 *
 * \function description
 * This function is called from SoAd_OpenSoCon to handle the DET error for function arguments.
 * It covers SWS_SoAd_00615, SWS_SoAd_00611 & SWS_SoAd_00528 requirements
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index specifying the socket connection which shall be opened
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 ************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_OpenSoConDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_OPEN_SOCON_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId is valid & socket is configured as automatic or not */
    SOAD_DET_REPORT_ERROR( ( ( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ) || \
                             ( ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId_uo].soConGrpId_uo].soConGrpAutoConSetup_b ) == TRUE ) ), \
                                        SOAD_OPEN_SOCON_API_ID, \
                                        SOAD_E_INV_ARG )

}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
