

/*---------------------------------------------------------------------------------------*/
/*- Include files																		-*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_LinTp.h"
#include "BswM_Prv.h"

#ifdef BSWM_LINTP_ENABLED
#if ( BSWM_LINTP_ENABLED == TRUE )

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/***********************************************************
* Function name: void BswM_LinTp_RequestMode(NetworkHandleType Network, LinTp_Mode LinTpRequestedMode)
* Description: Function called by LinTP to request a mode for the corresponding LIN channel. The LinTp_Mode
*              mainly correlates to the LIN schedule table that should be used.
* Parameter Network : The LIN channel that the LinTp mode request relates to.
* Parameter LinTpRequestedMode : The requested LIN TP mode.
* Return value: None
* Remarks:
***********************************************************/
FUNC(void, BSWM_CODE) BswM_LinTp_RequestMode
(
    VAR(NetworkHandleType, AUTOMATIC) Network,
    VAR(LinTp_Mode, AUTOMATIC) LinTpRequestedMode
)
{

#if ( BSWM_NO_OF_LINTP_CHANNELS > 0 )
    /* Local variables defined for this function. */
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPLinTpType_tst, AUTOMATIC) dataLinTpReqMode_st;
    VAR(boolean, AUTOMATIC) flgNetworkIdValid = FALSE;


#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_LINTPREQMD, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed LinTp Network-Id is valid and get corresponding index */
        flgNetworkIdValid = BswM_Prv_GetLinTpModeReqChnIndex_b(Network, &idx_u16);

        if(FALSE != flgNetworkIdValid)
        {

            /* Check if the RequestedMode is within the valid range.*/
            if((LinTpRequestedMode != LINTP_APPLICATIVE_SCHEDULE) &&
                (LinTpRequestedMode != LINTP_DIAG_REQUEST) &&
                (LinTpRequestedMode != LINTP_DIAG_RESPONSE))
            {
                /* DET if the RequestedMode is not within the valid range.*/
                BSWM_DET_REPORT_ERROR(BSWM_API_ID_LINTPREQMD, BSWM_E_REQ_MODE_OUT_OF_RANGE);
            }
            else
            {
                flgDetChecksPassed_b = TRUE;
            }
        }

        if(FALSE != flgDetChecksPassed_b)
        {
            /* Check if no other request is in progress */
            if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_LINTP_MODE_REQST, Network, idx_u16, (uint16)LinTpRequestedMode))
            {
                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }

                /*Update RAM buffer with current mode values*/
                BswM_Cfg_LinTpModeReqInfo_ast[idx_u16].isValidModePresent_b = TRUE;
                BswM_Cfg_LinTpModeReqInfo_ast[idx_u16].dataMode_en = LinTpRequestedMode;

                dataLinTpReqMode_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinTpReq_ast[idx_u16];

                BswM_Prv_RuleEval(dataLinTpReqMode_st.dataReqProcessing_en, BSWM_MRP_LINTP_MODE_REQST, Network, dataLinTpReqMode_st.adrRulesRef_pu16, dataLinTpReqMode_st.nrAssociatedRules_u16);

                /* Check Whether deferred request processing was delayed */
                if( FALSE != BswM_Prv_flgDelayDeferredReqst_b )
                {
                    /* Call the deferred request processing function */
                    BswM_Prv_ProcessDeferredReqst();
                }

                /* Reset request in progress flag    */
                BswM_Prv_flgNewReqstProgress_b = FALSE;

            }
        }
    }


#if ( BSWM_DEBUG == TRUE )
    BswM_Prv_InterruptHandler(BSWM_API_ID_LINTPREQMD);
#endif /* ( BSWM_DEBUG == TRUE ) */
#else
    /* To avoid compiler warnings if no LinTp channel is configured */
    (void)Network;
    (void)LinTpRequestedMode;
#endif /* ( BSWM_NO_OF_LINTP_CHANNELS > 0 ) */

    return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_LINTP_ENABLED == TRUE )*/
#endif /* BSWM_LINTP_ENABLED */
/*
<BASDKey>
 **********************************************************************************************************************
 * Administrative Information (automatically filled in)
 * $History___:$
 **********************************************************************************************************************
</BASDKey>
*/
