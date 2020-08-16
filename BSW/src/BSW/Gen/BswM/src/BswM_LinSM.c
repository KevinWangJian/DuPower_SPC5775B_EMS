

/*---------------------------------------------------------------------------------------*/
/*- Include files																		-*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_LinSM.h"
#include "BswM_Prv.h"

#ifdef BSWM_LINSM_ENABLED
#if ( BSWM_LINSM_ENABLED == TRUE )

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*--------------------------------------------------------------------------*/
/*- definition of global functions                                             -*/
/*--------------------------------------------------------------------------*/

/***********************************************************
* Function name: void BswM_LinSM_CurrentState( NetworkHandleType Network, LinSM_ModeType CurrentState )
* Description: Function called by LinSM to indicate its current state.
* Parameter Network : The LIN channel that the indicated state corresponds to.
* Parameter CurrentState : The current state of the LIN channel.
* Return value: None
* Remarks:
***********************************************************/
FUNC(void, BSWM_CODE) BswM_LinSM_CurrentState
(
   VAR(NetworkHandleType, AUTOMATIC) Network,
   VAR(LinSM_ModeType, AUTOMATIC) CurrentState
)
{

#if (defined(BSWM_NO_OF_LINSM_CHANNELS) && (BSWM_NO_OF_LINSM_CHANNELS > 0))
    /* Local variables defined for this function. */
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPLinSMType_tst, AUTOMATIC) dataLinSmCurrentState_st;
    VAR(boolean, AUTOMATIC) flgNetworkIdValid = FALSE;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_LINSMCRNTST, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed CurrentState is valid and get corresponding index */
        flgNetworkIdValid = BswM_Prv_GetLinSmCurrentStateIndex_b(Network , &idx_u16);

        /* Proceed if it valid index */
        if(FALSE != flgNetworkIdValid)
        {
            /* Check if the Current State is within the valid range.*/
            if((CurrentState != LINSM_NO_COM) &&
                (CurrentState != LINSM_FULL_COM))
            {
                /* DET if the Current State is not within the valid range.*/
                BSWM_DET_REPORT_ERROR(BSWM_API_ID_LINSMCRNTST, BSWM_E_REQ_MODE_OUT_OF_RANGE);
            }
            else
            {
                flgDetChecksPassed_b = TRUE;
            }
        }

        if(FALSE != flgDetChecksPassed_b)
        {
            /* Check if no other request is in progress */
            if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_LINSM_IND, Network, idx_u16, (uint16)CurrentState))
            {
                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }

                /*Update RAM buffer with current mode values*/
                BswM_Cfg_LinSmCurrentStateInfo_ast[idx_u16].isValidModePresent_b = TRUE;
                BswM_Cfg_LinSmCurrentStateInfo_ast[idx_u16].dataMode_en = CurrentState;

                dataLinSmCurrentState_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSMInd_ast[idx_u16];

                BswM_Prv_RuleEval(dataLinSmCurrentState_st.dataReqProcessing_en, BSWM_MRP_LINSM_IND, Network, dataLinSmCurrentState_st.adrRulesRef_pu16, dataLinSmCurrentState_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_LINSMCRNTST);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /* To avoid compiler warnings if no LinSM channel is configured */
    (void)Network;
    (void)CurrentState;
#endif /* ( BSWM_NO_OF_LINSM_CHANNELS > 0 ) */

    return;
}


/***********************************************************
* Function name: void BswM_LinSM_CurrentSchedule( NetworkHandleType Network, LinIf_SchHandleType CurrentSchedule )
* Description: Function called by LinSM to indicate the currently active schedule table for a specific LIN channel.
* Parameter Network : The LIN channel that the schedule table switch have occurred on.
* Parameter CurrentSchedule : The currently active schedule table of the LIN channel.
* Return value: None
* Remarks:
***********************************************************/
FUNC(void, BSWM_CODE) BswM_LinSM_CurrentSchedule
(
   VAR(NetworkHandleType, AUTOMATIC) Network,
   VAR(LinIf_SchHandleType, AUTOMATIC) CurrentSchedule
)
{
#if (defined(BSWM_NO_OF_LINSMSCH_CHANNELS) && (BSWM_NO_OF_LINSMSCH_CHANNELS > 0))

    /* Local variables defined for this function. */
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPLinSchdType_tst, AUTOMATIC) dataLinSmCurrentSch_st ;
    VAR(boolean, AUTOMATIC) flgNetworkIdValid = FALSE;
    VAR(boolean, AUTOMATIC) flgInputChecksPassed_b = FALSE;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_LINSMCRNTSCD, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed Lin Channel is valid and get corresponding index */
        flgNetworkIdValid = BswM_Prv_GetLinSmCurrentScheduleChnIndex_b(Network, &idx_u16);

        /* Proceed if it valid index */
        if(FALSE != flgNetworkIdValid)
        {

            /* Check if max no of schedules are greater than than passed current schedule */
            if(BswM_Prv_idLinSMMaxSchTab_cau8[idx_u16] > CurrentSchedule)
            {
                flgInputChecksPassed_b = TRUE;
            }
        }

        if(flgInputChecksPassed_b != FALSE)
        {

            /* Check if no other request is in progress */
                if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_LINSM_SCHEDULE_IND, idx_u16, idx_u16, (uint16)CurrentSchedule))
                {
                    /* Process any requests that were delayed before this request */
                    if (FALSE != BswM_Prv_isReqstDelayed_b)
                    {
                        BswM_Prv_ProcessDelayedReqst();
                    }

                    /*Update RAM buffer with current mode values*/
                    BswM_Cfg_LinSmCurrentSchInfo_ast[idx_u16].isValidModePresent_b = TRUE;
                    BswM_Cfg_LinSmCurrentSchInfo_ast[idx_u16].dataMode_u8 = CurrentSchedule;

                    dataLinSmCurrentSch_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataLinSchInd_ast[idx_u16];

                    BswM_Prv_RuleEval(dataLinSmCurrentSch_st.dataReqProcessing_en, BSWM_MRP_LINSM_SCHEDULE_IND, idx_u16, dataLinSmCurrentSch_st.adrRulesRef_pu16, dataLinSmCurrentSch_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_LINSMCRNTSCD);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /* To avoid compiler warnings if no LinSM channel is configured */
    (void)Network;
    (void)CurrentSchedule;
#endif /* ( BSWM_NO_OF_LINSMSCH_CHANNELS > 0 ) */

    return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_LINSM_ENABLED == TRUE ) */
#endif /* BSWM_LINSM_ENABLED */

/*
<BASDKey>
 **********************************************************************************************************************
 * Administrative Information (automatically filled in)
 * $History___:$
 **********************************************************************************************************************
</BASDKey>
*/
