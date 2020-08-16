

/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_Nm.h"
#include "BswM_Prv.h"


#ifdef BSWM_NM_ENABLED
#if ( BSWM_NM_ENABLED == TRUE )

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name : void BswM_NmIf_CarWakeUpIndication(NetworkHandleType Network)
* Description   : Function called by NmIf to indicate a CarWakeup.
* Parameter     : Network - Identification of the Nm-Channel
* Return value  : None
* Remarks       :
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_NmIf_CarWakeUpIndication
(
    VAR(NetworkHandleType, AUTOMATIC) Network
)
{
#if (BSWM_NO_OF_NM_CHANNELS > 0)
    /* Local variables defined for this function. */
    VAR(uint16, AUTOMATIC) idxMRParray_u16 = 0;
    VAR(boolean, AUTOMATIC) flgValidChannelId_b = FALSE;
    VAR(boolean, AUTOMATIC) flgDetCheckPassed_b = FALSE;
    VAR(BswM_Cfg_MRPNmIfCarWakeupIndType_tst, AUTOMATIC) dataNmIfWKupIndMRP_st;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_NMIFCARWKUPIND,BSWM_E_NO_INIT);
    }
    else
    {
        flgValidChannelId_b = BswM_Prv_GetNmIfWkupIndMRPIndex_b(Network,&idxMRParray_u16);

        if(FALSE == flgValidChannelId_b)
        {
            /* DET if the channel ID is invalid.*/
            BSWM_DET_REPORT_ERROR(BSWM_API_ID_NMIFCARWKUPIND,BSWM_E_REQ_USER_OUT_OF_RANGE);
        }
        else
        {
            flgDetCheckPassed_b = TRUE;
        }
    }

    if(FALSE != flgDetCheckPassed_b)
    {
        if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_NM_CAR_WKUP_IND, Network, idxMRParray_u16, (uint16)BSWM_NO_SOURCE_STATUS_TRUE ))
        {
            /* Process requests that interrupted the execution of the current request */
            if (FALSE != BswM_Prv_isReqstDelayed_b)
            {
                BswM_Prv_ProcessDelayedReqst();
            }

            /* Prv function to update the buffer variable for rule evaluation */
            dataNmIfWKupIndMRP_st.dataReqProcessing_en = BswM_Prv_GetNmIfWkupIndInfo_en(idxMRParray_u16,(uint16)BSWM_NO_SOURCE_STATUS_TRUE,&(dataNmIfWKupIndMRP_st.nrAssociatedRules_u16),&(dataNmIfWKupIndMRP_st.adrRulesRef_pu16));

            /* Rules of the request will be stored if it is Deferred/ evaluated if it is Immediate */
            BswM_Prv_RuleEval(dataNmIfWKupIndMRP_st.dataReqProcessing_en,BSWM_MRP_NM_CAR_WKUP_IND,Network,dataNmIfWKupIndMRP_st.adrRulesRef_pu16,dataNmIfWKupIndMRP_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_NMIFCARWKUPIND);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    (void)Network;
#endif  /* (BSWM_NO_OF_NM_CHANNELS > 0) */

    return;

}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_NM_ENABLED == TRUE ) */
#endif /* BSWM_NM_ENABLED */

/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
