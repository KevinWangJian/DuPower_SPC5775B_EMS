

/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_Sd.h"
#include "BswM_Prv.h"


/*---------------------------------------------------------------------------------------*/
/*- Definition of Global Functions                                                       -*/
/*---------------------------------------------------------------------------------------*/

#ifdef BSWM_SD_ENABLED
#if (BSWM_SD_ENABLED == TRUE)

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name :BswM_Sd_ClientServiceCurrentState(uint16 SdClientServiceHandleId, Sd_ClientServiceCurrentStateType CurrentClientState)
* Description   :Function called by Service Discovery to indicate current state of the Client Service (available/down).
* Parameter     :SdClientServiceHandleId. CurrentClientState
* Return value  :None
* Remarks       :The corresponding configuration container for this API is BswMSdClientServiceCurrentState.
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Sd_ClientServiceCurrentState
(
        VAR (uint16, AUTOMATIC )SdClientServiceHandleId,
        VAR (Sd_ClientServiceCurrentStateType, AUTOMATIC) CurrentClientState
)
{
#if (defined(BSWM_NO_OF_SDCLIENTSRV_CS) && (BSWM_NO_OF_SDCLIENTSRV_CS > 0 ))
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPSdClientServType_tst, AUTOMATIC) dataSdClientSrvCS_st;
    VAR(boolean, AUTOMATIC) flgSdClientServiceHandleIdValid = FALSE;
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;

#if ( BSWM_DEBUG == TRUE )

    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;

#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_SD_CLINTSERVCS, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed  SdClientServiceHandleId is valid and get corresponding index */
        flgSdClientServiceHandleIdValid = BswM_Prv_GetSdclientSrvCSMRPIndex_b(SdClientServiceHandleId, &idx_u16);
        /* if the Passed flgSdClientServiceHandleId is not within the valid range.*/
        if(FALSE !=flgSdClientServiceHandleIdValid)
        {
            if((CurrentClientState != SD_CLIENT_SERVICE_DOWN) && (CurrentClientState != SD_CLIENT_SERVICE_AVAILABLE) )
            {
                /* DET if the Current State is not within the valid range.*/
                BSWM_DET_REPORT_ERROR(BSWM_API_SD_CLINTSERVCS, BSWM_E_REQ_MODE_OUT_OF_RANGE);
            }
            else
            {
                flgDetChecksPassed_b = TRUE;
            }
        }

        if(FALSE != flgDetChecksPassed_b)
        {
            /* Check if no other request is in progress */
            if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_SD_CLNT_SERV_CURR_STATE, SdClientServiceHandleId, idx_u16, (uint16)CurrentClientState))
            {
                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }
                /*Update RAM buffer with current mode values*/
                BswM_Cfg_SdClientSrvCSModeInfo_ast[idx_u16].isValidModePresent_b = TRUE;
                BswM_Cfg_SdClientSrvCSModeInfo_ast[idx_u16].dataMode_en = CurrentClientState;
                dataSdClientSrvCS_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdClientSrv_ast[idx_u16];
                BswM_Prv_RuleEval(dataSdClientSrvCS_st.dataReqProcessing_en, BSWM_MRP_SD_CLNT_SERV_CURR_STATE, SdClientServiceHandleId, dataSdClientSrvCS_st.adrRulesRef_pu16, dataSdClientSrvCS_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_SD_CLINTSERVCS);
#endif /* ( BSWM_DEBUG == TRUE ) */
#else
    /*To avoid compiler warning of unused parameters*/
    (void)SdClientServiceHandleId;
    (void)CurrentClientState;

#endif /* (BSWM_NO_OF_SDCLIENTSRV_CS > 0) */
    return;
}

/*****************************************************************************************
* Function name :BswM_Sd_ConsumedEventGroupCurrentState( uint16 SdConsumedEventGroupHandleId, Sd_ConsumedEventGroupCurrentStateType ConsumedEventGroupState
* Description   :Function called by Service Discovery to indicate current status of the Consumed Eventgroup (available/down).
* Parameter     :SdConsumedEventGroupHandleId, ConsumedEventGroupState
* Return value  :None
* Remarks       :The corresponding configuration container for this API is BswMSdConsumedEventGroupCurrentState.
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_Sd_ConsumedEventGroupCurrentState
(
        VAR(uint16, AUTOMATIC) SdConsumedEventGroupHandleId,
        VAR(Sd_ConsumedEventGroupCurrentStateType, AUTOMATIC) ConsumedEventGroupState
)
{
#if (defined(BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS) && (BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0))
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPSdConsEventGrpType_tst, AUTOMATIC) dataSdConsEvntGrpCS_st;
    VAR(boolean, AUTOMATIC) flgSdConsumedEventGroupHandleIdValid = FALSE;
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_SD_CONSEVNTGRPCS, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed Sd ConsumedEventGroupHandleId is valid and get corresponding index */
        flgSdConsumedEventGroupHandleIdValid = BswM_Prv_GetSdConsEvntGrpCSMRPIndex_b(SdConsumedEventGroupHandleId, &idx_u16);

        /* if the Passed SdConsumedEventGroupHandleId is not within the valid range.*/
        if(FALSE != flgSdConsumedEventGroupHandleIdValid)
        {
            if( (ConsumedEventGroupState != SD_CONSUMED_EVENTGROUP_DOWN) && (ConsumedEventGroupState != SD_CONSUMED_EVENTGROUP_AVAILABLE) )
            {
                /* DET if the Current State is not within the valid range.*/
                BSWM_DET_REPORT_ERROR(BSWM_API_SD_CONSEVNTGRPCS, BSWM_E_REQ_MODE_OUT_OF_RANGE);
            }
            else
            {
                flgDetChecksPassed_b = TRUE;
            }
        }

        if(FALSE != flgDetChecksPassed_b)
        {
            /* Check if no other request is in progress */
            if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_SD_CNSMD_EVNT_GRP_CURR_STATE, SdConsumedEventGroupHandleId, idx_u16, (uint16)ConsumedEventGroupState))
            {
                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }

                /*Update RAM buffer with current mode values*/
                BswM_Cfg_SdCnsEvntGrpCSModeInfo_ast[idx_u16].isValidModePresent_b = TRUE;

                BswM_Cfg_SdCnsEvntGrpCSModeInfo_ast[idx_u16].dataMode_en = ConsumedEventGroupState;

                dataSdConsEvntGrpCS_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdCnsEvnt_ast[idx_u16];

                BswM_Prv_RuleEval(dataSdConsEvntGrpCS_st.dataReqProcessing_en, BSWM_MRP_SD_EVNT_HNDLR_CURR_STATE, SdConsumedEventGroupHandleId, dataSdConsEvntGrpCS_st.adrRulesRef_pu16, dataSdConsEvntGrpCS_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_SD_CONSEVNTGRPCS);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /*To avoid compiler warning of unused parameters*/
    (void)SdConsumedEventGroupHandleId;
    (void)ConsumedEventGroupState;

#endif /* (BSWM_NO_OF_SDCNSEVGRP_HANDLE_CS > 0) */
    return;
}


/*****************************************************************************************
* Function name :BswM_Sd_EventHandlerCurrentState( uint16 SdEventHandlerHandleId, Sd_EventHandlerCurrentStateType EventHandlerStatus
* Description   :Function called by Service Discovery to indicate current status of the EventHandler (requested/released).
* Parameter     :SdEventHandlerHandleId, EventHandlerStatus
* Return value  :None
* Remarks       :The corresponding configuration container for this API is BswMSdEventHandlerCurrentState.
*****************************************************************************************/

FUNC(void, BSWM_CODE) BswM_Sd_EventHandlerCurrentState
(
        VAR(uint16, AUTOMATIC) SdEventHandlerHandleId,
        VAR(Sd_EventHandlerCurrentStateType, AUTOMATIC) EventHandlerStatus
)

{
#if (defined(BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS) && (BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0))
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPSdEventType_tst, AUTOMATIC) dataSdEvntHndrCS_st;
    VAR(boolean, AUTOMATIC) flgEventHandlerHandleIdValid = FALSE;
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_SD_EVNTHNDRCS, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed SdEventHandlerHandleId is valid and get corresponding index */
        flgEventHandlerHandleIdValid = BswM_Prv_GetSdEvntHndrCSMRPIndex_b(SdEventHandlerHandleId, &idx_u16);

        if(FALSE != flgEventHandlerHandleIdValid)
        {
            if( (EventHandlerStatus != SD_EVENT_HANDLER_RELEASED) && (EventHandlerStatus != SD_EVENT_HANDLER_REQUESTED) )
            {
                /* DET if the Current State is not within the valid range.*/
                BSWM_DET_REPORT_ERROR(BSWM_API_SD_EVNTHNDRCS, BSWM_E_REQ_MODE_OUT_OF_RANGE);
            }
            else
            {
                flgDetChecksPassed_b = TRUE;
            }
        }

        if(FALSE != flgDetChecksPassed_b)
        {
            /* Check if no other request is in progress */
            if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_SD_EVNT_HNDLR_CURR_STATE, SdEventHandlerHandleId, idx_u16, (uint16)EventHandlerStatus))
            {
                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }

                /*Update RAM buffer with current mode values*/
                BswM_Cfg_SdEvntHndrCSModeInfo_ast[idx_u16].isValidModePresent_b = TRUE;

                BswM_Cfg_SdEvntHndrCSModeInfo_ast[idx_u16].dataMode_en = EventHandlerStatus;

                dataSdEvntHndrCS_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataSdEvntHndlr_ast[idx_u16];

                BswM_Prv_RuleEval(dataSdEvntHndrCS_st.dataReqProcessing_en, BSWM_MRP_SD_EVNT_HNDLR_CURR_STATE, SdEventHandlerHandleId, dataSdEvntHndrCS_st.adrRulesRef_pu16, dataSdEvntHndrCS_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_SD_EVNTHNDRCS);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /*To avoid compiler warning of unused parameters*/
    (void)SdEventHandlerHandleId;
    (void)EventHandlerStatus;

#endif /* (BSWM_NO_OF_SDEVNTHNDLR_HANDLE_CS > 0) */
    return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif

#endif //BSWM_SD_ENABLED

/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
