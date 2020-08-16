

/*---------------------------------------------------------------------------------------*/
/*- Include files																		-*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_EcuM.h"
#include "BswM_Prv.h"

/*---------------------------------------------------------------------------------------*/
/*- Definition of Global Functions														-*/
/*---------------------------------------------------------------------------------------*/

#if (defined(BSWM_ECUM_ENABLED) && (BSWM_ECUM_ENABLED == TRUE))

#include "BswM_EcuM.h"

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name: void BswM_EcuM_CurrentState(EcuM_StateType CurrentState)
* Description: Function called by EcuM to indicate the current ECU Operation Mode.
* Parameter CurrentState : The requested ECU Operation Mode
* Return value  :   void
* Remarks       :
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_EcuM_CurrentState
(
        VAR(EcuM_StateType, AUTOMATIC) CurrentState
)
{
#if (defined(BSWM_NO_OF_ECUM_INDICATION) && (BSWM_NO_OF_ECUM_INDICATION > 0 ))
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(uint16, AUTOMATIC) idx_u16 = BSWM_MRP_WITH_NO_CHANNEL_SOURCE;
    VAR(BswM_Cfg_MRPEcuMIndType_tst, AUTOMATIC) dataEcuMInd_st;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMCRNTST, BSWM_E_NO_INIT);
    }
    else
    {

        if ((  CurrentState != ECUM_STATE_STARTUP)
        &&  (  CurrentState != ECUM_STATE_SHUTDOWN )
        &&  (  CurrentState != ECUM_STATE_SLEEP)
        &&  (  CurrentState != ECUM_STATE_APP_RUN)
        &&  (  CurrentState != ECUM_STATE_APP_POST_RUN))
        {
            /* DET if the Current State is not within the valid range.*/
            BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMCRNTST, BSWM_E_REQ_MODE_OUT_OF_RANGE);
        }
        else
        {
            flgDetChecksPassed_b = TRUE;
        }

        if(FALSE != flgDetChecksPassed_b)
        {
            /* Check if no other request is in progress */
            if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_ECUM_IND, BSWM_MRP_WITH_NO_CHANNEL_SOURCE, idx_u16, (uint16)CurrentState))
            {
                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }

                /*Update RAM buffer with current mode values*/

                BswM_Cfg_EcuMIndicationModeInfo_ast[idx_u16].isValidModePresent_b = TRUE;

                BswM_Cfg_EcuMIndicationModeInfo_ast[idx_u16].dataMode_u8 = CurrentState;

                dataEcuMInd_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMInd_ast[idx_u16];

                BswM_Prv_RuleEval(dataEcuMInd_st.dataReqProcessing_en, BSWM_MRP_ECUM_IND, BSWM_MRP_WITH_NO_CHANNEL_SOURCE, dataEcuMInd_st.adrRulesRef_pu16, dataEcuMInd_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_ECUMCRNTST);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /*To avoid compiler warning of unused parameters*/
    (void)CurrentState;
#endif /* (BSWM_NO_OF_ECUM_INDICATION ) */
    return;
}

/*****************************************************************************************
* Function name	: void BswM_EcuM_CurrentWakeup(EcuM_WakeupSourceType Source,EcuM_WakeupStatusType State)
* Description	: Function called by EcuM to indicate the current state of a wakeup source.
* Parameter  	: source - Wakeup source(s) that changed state.
*               : state  - The new state of the wakeup source(s)
* Return value	: None
* Remarks		:
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_EcuM_CurrentWakeup
(
	VAR(EcuM_WakeupSourceType, AUTOMATIC) source,
	VAR(EcuM_WakeupStatusType, AUTOMATIC) state
)
{
#if ( BSWM_NO_OF_ECUMWKP_SOURCES > 0 )
    /* Local variables defined for this function. */
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(uint16, AUTOMATIC) idxMRParray_u16 = 0;
    VAR(uint8, AUTOMATIC) idxEcuMAllWakSrc_u8 = 0;
    VAR(boolean, AUTOMATIC) ecuMWakSrcIdVld_b = FALSE;
    VAR(BswM_Cfg_MRPEcuMWakeUpSrcType_tst, AUTOMATIC) dataEcuMWkpMRP_st;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
   if ( FALSE == BswM_Prv_isModuleInitialised_b )
   {
       /* DET if the BSW Mode Manager is not initialized.*/
       BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMCURRWAKEUP,BSWM_E_NO_INIT);
   }
   else
   {
       /* Is state of the wakeup source invalid ?, ECUM_WKSTATUS_ENABLED stat is not considered since the state is removed from AR4.3 */
       if ( ( ECUM_WKSTATUS_NONE != state )
            && ( ECUM_WKSTATUS_PENDING != state )
            && ( ECUM_WKSTATUS_VALIDATED != state )
            && ( ECUM_WKSTATUS_EXPIRED != state )
          )
       {
           /* DET if the State is Invalid.*/
           BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMCURRWAKEUP, BSWM_E_REQ_MODE_OUT_OF_RANGE);
       }
       else
       /* state of the wakeup is valid and proceed mode request processing */
       {
           flgDetChecksPassed_b = TRUE;
       }
   }

   if( FALSE != flgDetChecksPassed_b )
   {

       /* Loop through all EcuM wakeup source */
       for( idxEcuMAllWakSrc_u8 = 0; idxEcuMAllWakSrc_u8 < 32; idxEcuMAllWakSrc_u8++ )
       {
           flgDetChecksPassed_b = FALSE;
           /* Check Wakeup source is set? */
           ecuMWakSrcIdVld_b = (((source) & ((uint32)(1uL << idxEcuMAllWakSrc_u8))) != 0uL);

            if( FALSE != ecuMWakSrcIdVld_b )
            {
               /* Check whether passed EcuM wakeup source is valid and get corresponding table index */
               /* Passed EcuM wakeup source valid? */
               if ( FALSE != BswM_Prv_GetEcuMWkpSrcMRPIndex_b( idxEcuMAllWakSrc_u8, &idxMRParray_u16 ) )
               {
                   flgDetChecksPassed_b = TRUE;
               }
               else
               {
                   /* DET if the wakeup source is Invalid.*/
                   BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMCURRWAKEUP, BSWM_E_REQ_USER_OUT_OF_RANGE);
               }
            }

            /* Check if no other request is in progress */
            if( (FALSE != flgDetChecksPassed_b ) && (FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_ECUM_WKUP_SOURCE, (uint16)idxEcuMAllWakSrc_u8, idxMRParray_u16, (uint16)state)))
            {
               /* Process requests that interrupted the processing of the previous mode request */
               if (FALSE != BswM_Prv_isReqstDelayed_b)
               {
                   BswM_Prv_ProcessDelayedReqst();
               }

               /* EcuM Wakeup Source type MRP RAM Buffer initialized at required index */
               BswM_Cfg_EcuMWkpSrcInfo_ast[idxMRParray_u16].isValidModePresent_b = TRUE;

               BswM_Cfg_EcuMWkpSrcInfo_ast[idxMRParray_u16].dataState = state;

               dataEcuMWkpMRP_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMWkpSrc_ast[idxMRParray_u16];

               /* Rules of the request will be stored if it is Deferred/ evaluated if it is Immediate */
               BswM_Prv_RuleEval(dataEcuMWkpMRP_st.dataReqProcessing_en,BSWM_MRP_ECUM_WKUP_SOURCE,(uint16)idxEcuMAllWakSrc_u8,dataEcuMWkpMRP_st.adrRulesRef_pu16,dataEcuMWkpMRP_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_ECUMCURRWAKEUP);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /* To avoid compiler warnings if no user is configured */
    (void)source;
    (void)state;
#endif  /* ( BSWM_NO_OF_ECUMWKP_SOURCES > 0 ) */
	return;
}



/*****************************************************************************************
* Function name	:BswM_EcuM_RequestedState(EcuM_StateType State,EcuM_RunStatusType CurrentStatus)
* Description	:Function called by EcuM to notify about current Status of the Run Request Protocol.
* Parameter State : The requested state by EcuMFlex.
* Parameter CurrentStatus : Result of the Run Request Protocol.
* Return value	:Void
* Remarks		:
*****************************************************************************************/

FUNC(void, BSWM_CODE) BswM_EcuM_RequestedState
(
	VAR(EcuM_StateType, AUTOMATIC) State,
	VAR(EcuM_RunStatusType, AUTOMATIC) CurrentStatus
)
{

#if (defined(BSWM_NO_OF_ECUMRUNREQ_STATES) && (BSWM_NO_OF_ECUMRUNREQ_STATES > 0))
    VAR(boolean, AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(BswM_Cfg_MRPEcuMRunReqType_tst, AUTOMATIC) dataEcuMRUNReq_st;
    VAR(boolean, AUTOMATIC) flgStateValid = FALSE;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMRUNREQ, BSWM_E_NO_INIT);
    }
    else
    {
        /* Check whether passed PNC is valid and get corresponding index */
        flgStateValid = BswM_Prv_GetEcuMRUNReqIndicationMRPIndex_b(State, &idx_u16);

        if(FALSE == flgStateValid)
        {
            /* DET if the Passed State is not within the valid range.*/
            BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMRUNREQ, BSWM_E_REQ_USER_OUT_OF_RANGE);
        }
        else if( ( ECUM_RUNSTATUS_UNKNOWN != CurrentStatus )
        && ( ECUM_RUNSTATUS_REQUESTED != CurrentStatus )
        && ( ECUM_RUNSTATUS_RELEASED  != CurrentStatus ))
        {
            /* DET if the Current Status is not within the valid range.*/
            BSWM_DET_REPORT_ERROR(BSWM_API_ID_ECUMRUNREQ, BSWM_E_REQ_MODE_OUT_OF_RANGE);
        }
        else
        {
            flgDetChecksPassed_b = TRUE;
        }

        /* Check if no other request is in progress */
        if((FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_ECUM_RUN_REQST_IND, State, idx_u16, (uint16)CurrentStatus)) && (FALSE != flgDetChecksPassed_b))
        {
            /* Process any requests that were delayed before this request */
            if (FALSE != BswM_Prv_isReqstDelayed_b)
            {
                BswM_Prv_ProcessDelayedReqst();
            }

            /*Update RAM buffer with current mode values*/
            BswM_Cfg_EcuMRUNReqIndicationModeInfo_ast[idx_u16].isValidModePresent_b = TRUE;

            BswM_Cfg_EcuMRUNReqIndicationModeInfo_ast[idx_u16].dataMode_u8 = CurrentStatus;

            dataEcuMRUNReq_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataEcuMRunReq_ast[idx_u16];

            BswM_Prv_RuleEval(dataEcuMRUNReq_st.dataReqProcessing_en, BSWM_MRP_ECUM_RUN_REQST_IND, State, dataEcuMRUNReq_st.adrRulesRef_pu16, dataEcuMRUNReq_st.nrAssociatedRules_u16);

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

#if ( BSWM_DEBUG == TRUE )
    BswM_Prv_InterruptHandler(BSWM_API_ID_ECUMRUNREQ);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /*To avoid compiler warning of unused parameters*/
    (void)State;
    (void)CurrentStatus;
#endif /* BSWM_NO_OF_ECUMRUNREQ_STATES */
	return;
}


#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_ECUM_ENABLED == TRUE ) */

/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
