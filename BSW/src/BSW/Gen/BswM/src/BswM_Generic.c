

/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_Generic.h"
#include "BswM_Prv.h"


#ifdef BSWM_GENERIC_REQUEST_ENABLED
#if ( BSWM_GENERIC_REQUEST_ENABLED == TRUE )

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name : BswM_RequestMode (BswM_UserType requesting_user, BswM_ModeType requested_mode)
* Description   : Generic function call to request modes. This function shall only be used by other BSW modules that
*                 do not have a specific mode request interface.
* Parameters(in): requesting_user : The user that requests the mode.
*               : requested_mode : The requested mode.
* Return value  : None
* Remarks       : The corresponding configuration container for this API is BswMGenericRequest.
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_RequestMode
(
   VAR(BswM_UserType, AUTOMATIC) requesting_user,
   VAR(BswM_ModeType, AUTOMATIC) requested_mode
)
{
#if ( BSWM_NO_OF_GENREQ_TOTAL > 0 )
    /* Local variables defined for this function. */
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPGenericReqType_tst, AUTOMATIC) dataGenReq_st;
    VAR(boolean, AUTOMATIC) flgUserIdValid = FALSE;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_REQSTMODE, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed user ID is valid and get corresponding index */
        flgUserIdValid = BswM_Prv_GetGenReqMRPIndex_b(requesting_user, &idx_u16);
        if(FALSE == flgUserIdValid)
        {
            /* DET if the Passed UserId is not within the valid range.*/
            BSWM_DET_REPORT_ERROR(BSWM_API_ID_REQSTMODE, BSWM_E_REQ_USER_OUT_OF_RANGE);
        }
        else if(requested_mode > BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataGenericReq_ast[idx_u16].dataModeMax_u16)
        {
            /* DET if the Requested Mode is not within the valid range.*/
            BSWM_DET_REPORT_ERROR(BSWM_API_ID_REQSTMODE, BSWM_E_REQ_MODE_OUT_OF_RANGE );
        }
        else
        {
            flgDetChecksPassed_b = TRUE;
        }

        if(FALSE != flgDetChecksPassed_b)
        {
            /* Check if no other request is in progress */
            if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_GENERIC_REQST, requesting_user, idx_u16, requested_mode ))
            {
                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }

                /*Update RAM buffer with current mode values*/
                BswM_Cfg_GenericReqModeInfo_ast[idx_u16].isValidModePresent_b = TRUE;

                BswM_Cfg_GenericReqModeInfo_ast[idx_u16].dataMode_u16 = requested_mode;
                dataGenReq_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataGenericReq_ast[idx_u16];

                BswM_Prv_RuleEval(dataGenReq_st.dataReqProcessing_en, BSWM_MRP_GENERIC_REQST, requesting_user, dataGenReq_st.adrRulesRef_pu16, dataGenReq_st.nrAssociatedRules_u16);

                /* Check Whether deferred request processing was delayed */
                if( FALSE != BswM_Prv_flgDelayDeferredReqst_b )
                {
                    /* Call the deferred request processing function */
                    BswM_Prv_ProcessDeferredReqst();
                }

				/* Reset request in progress flag */
                BswM_Prv_flgNewReqstProgress_b = FALSE;
            }
       }
    }

#if ( BSWM_DEBUG == TRUE )
    BswM_Prv_InterruptHandler(BSWM_API_ID_REQSTMODE);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /* To avoid compiler warnings if no user is configured */
    (void)requesting_user;
    (void)requested_mode;
#endif  /* ( BSWM_NO_OF_GENREQ_TOTAL > 0 ) */

     return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_GENERIC_REQUEST_ENABLED == TRUE ) */
#endif /* BSWM_GENERIC_REQUEST_ENABLED */

/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
