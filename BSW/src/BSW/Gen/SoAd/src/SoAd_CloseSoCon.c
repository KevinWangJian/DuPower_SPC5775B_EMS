

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
static FUNC( void, SOAD_CODE ) SoAd_CloseSoConDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo );
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
/**
 ***********************************************************************************************************************
 * \Function Name : SoAd_CloseSoCon()
 *
 * \Function description
 * This API This service closes the socket connection specified by SoConId
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId - socket connection index specifying the socket connection which shall be closed
 * \param   boolean
 * \arg     Abort - TRUE: socket connection will immediately be terminated.
 *                  FALSE: socket connection will be terminated if no other upper layer is using this socket connection.
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 *  Return value:
 * \retval  E_OK :      The request was successful
 *          E_NOT_OK:   The request was not successful
 *
 ***********************************************************************************************************************
 */

/* Use case: This function shall be called by upper layer, when it wants to close the socket.
 * SoAd shall take the action to change the state to OFFLINE, in next main functions. This function is valid
 * only for the manual sockets.
 *
 * Assumption: Each socket is controlled by only one upper layer, support for multiple upper layers shall be done in future, as
 * requirement for ABORT = FALSE says "socket connection will be terminated if no other upper layer is using this socket connection" */

FUNC( Std_ReturnType, SOAD_CODE ) SoAd_CloseSoCon( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId ,
                                                   VAR( boolean, AUTOMATIC ) Abort )
{
    /* Local pointer to store the Dynamic array one by one */
    P2VAR(SoAd_DyncSocConfigType_tst, SOAD_VAR, SOAD_VAR)               lSoAdDyncSocConfig_pst ;

    /* Variable to store the return value */
    VAR(Std_ReturnType, AUTOMATIC)                                      lFunctionRetVal_u8;

    /* Index to store the dynamic socket connection */
    VAR(SoAd_SoConIdType, AUTOMATIC)                                    lIdxDynSocket_uo;

    /* Initialize the function return variable to E_NOT_OK */
    lFunctionRetVal_u8          = E_NOT_OK;

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
    /* Function call to do the DET check */
    SoAd_CloseSoConDetChk(SoConId);

    /* Condition checks:
     * 1. If there is no DET error if DET is switch On.
     */
    if( E_NOT_OK == SoAd_DetErrFlag_u8 )
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */
    {
        /* Initialize the local variables which are declared above */
        /* Get the "dynamic socket connection index" from Static socket table */
        lIdxDynSocket_uo = (*SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId].SoAd_Prv_idxDynSocTable_puo) ;

        /* Condition check: the dynamic socket id should be valid  */
        if( SoAd_CurrConfig_cpst->SoAd_noActiveSockets_uo > lIdxDynSocket_uo )
        {
            /* copy the global array index address to local pointer for further processing */
            lSoAdDyncSocConfig_pst =  &(SoAd_DyncSocConfig_ast[lIdxDynSocket_uo]);

            /****************************************************************************************************************/
            /****************************************** [SWS_SoAd_00604] ****************************************************/
            /****************************************************************************************************************/
            /****************************************************************************************************************/
            /** 1. Current connection state is not SOAD_SOCON_OFFLINE                                                     ***/
            /** 2. Close is explicitly requested by a previous SoAd_CloseSoCon() call                                     ***/
            /** 3. No upper layer requested to keep the socket connection open at the time of the SoAd_CloseSoCon() call  ***/
            /**    (i.e. SoAd_CloseSoCon() has been called as often as SoAd_OpenSoCon()) or SoAd_CloseSoCon() has been    ***/
            /**     called with abort set to TRUE.                                                                        ***/
            /****************************************************************************************************************/
            /****************************************************************************************************************/

            /* Check: If socket connection is not yet closed
             * socket requested mode is at SOAD_EVENT_IDLE, when the socket is completely gone OFFLINE,
             * so, no need to again call for closing of a socket if socConRequestedMode_e is SOAD_EVENT_IDLE
             * if socConRequestedMode_e is already SOAD_EVENT_OFFLINEREQ_UL, then also no need to store request*/
            if( ( SOAD_SOCON_IDLE < lSoAdDyncSocConfig_pst->socConSubMode_en ) ||
                ( 0 < lSoAdDyncSocConfig_pst->socConOpenReqCnt_u16 ) )
            {
                /****************************************************************************************************************/
                /****************************************** [SWS_SoAd_00588] ****************************************************/
                /****************************************************************************************************************/
                /****************************************************************************************************************/
                /** SoAd shall store a request to open or close a socket connection when called with SoAd_OpenSoCon() and     ***/
                /** SoAd_CloseSoCon() respectively, but handle the request only in the SoAd_MainFunction() respecting the     ***/
                /**             connection setup and shutdown policy.                                                         ***/
                /****************************************************************************************************************/
                /****************************************************************************************************************/

                /* Increment the socConCloseReqCnt_u16 variable by 1 and compare the socConCloseReqCnt_u16 with socConOpenReqCnt_u16 in next MainFunction*/
                /* if no of close req is greater than open req, then set the event to offlinereq, such that close req action shall be taken place in the same main function */
                lSoAdDyncSocConfig_pst->socConCloseReqCnt_u16++;

                /* Store the Abort value in dynamic table */
                lSoAdDyncSocConfig_pst->statusAbort_b = Abort;

            }
            /* Set the return value to E_OK, as request is stored if socket is still ACTIVE or OFFLINEREQ_SOAD
             * No need to store the request again, if already socket is in the process of going to OFFLINE or already in OFFLINE
             * so return value is set to E_OK, in these cases */
            lFunctionRetVal_u8 = E_OK ;

        }
    }/*End of If condition: Check SoAd Module should be Initialized */

    return(lFunctionRetVal_u8);
}

#if ( SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF )
/**
 **********************************************************************************************************************
 * \Function Name : SoAd_CloseSoConDetChk()
 *
 * \function description
 * This function is called from SoAd_CloseSoCon to handle the DET error for function arguments.
 * It covers SWS_SoAd_00616, SWS_SoAd_00612 & SWS_SoAd_00529 requirements
 *
 * Parameters (in):
 * \param   SoAd_SoConIdType
 * \arg     SoConId_uo - socket connection index specifying the socket connection which shall be closed
 *
 *  Parameters (inout): None
 *
 *  Parameters (out):   None
 *
 * Return value:        None
 *
 **********************************************************************************************************************
 */
static FUNC( void, SOAD_CODE ) SoAd_CloseSoConDetChk( VAR( SoAd_SoConIdType, AUTOMATIC )  SoConId_uo )
{
    /* Reset the SoAd_DetErrFlag_u8 to E_NOT_OK before executing the DET for each interface function.
     * If SoAd_DetErrFlag_u8 is E_NOT_OK, then it will allow to check the first DET error,
     * suppose, if first DET error reports error, then this flag will be set it to E_OK and it will ignore next DET check
     * for the same function.
     */
    SoAd_DetErrFlag_u8 = E_NOT_OK;

    /* DET error reporting */
    /* Check whether SoAd Init function was already called or not */
    SOAD_DET_REPORT_ERROR( ( FALSE == SoAd_InitFlag_b ), SOAD_CLOSE_SOCON_API_ID, SOAD_E_NOTINIT )

    /* Check whether SoConId is valid & socket is configured as automatic or not */
    SOAD_DET_REPORT_ERROR( ( ( SoAd_CurrConfig_cpst->SoAd_noStaticSockets_uo <= SoConId_uo ) || \
                               ( SoAd_CurrConfig_cpst->SoAd_StaticSocGroupConfig_cpst[SoAd_CurrConfig_cpst->SoAd_StaticSocConfig_cpst[SoConId_uo].soConGrpId_uo].soConGrpAutoConSetup_b == TRUE ) ), \
                                 SOAD_CLOSE_SOCON_API_ID, SOAD_E_INV_ARG )

}
#endif /* SOAD_DEV_ERROR_DETECT_ENABLE != STD_OFF */

#define SOAD_STOP_SEC_CODE
#include "SoAd_MemMap.h"

#endif /* SOAD_CONFIGURED */
