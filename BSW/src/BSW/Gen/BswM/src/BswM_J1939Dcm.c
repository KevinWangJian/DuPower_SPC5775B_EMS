

/*---------------------------------------------------------------------------------------*/
/*- Include files																		-*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_J1939Dcm.h"
#include "BswM_Prv.h"

#ifdef BSWM_J1939DCM_ENABLED
#if ( BSWM_J1939DCM_ENABLED == TRUE )

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name : BswM_J1939DcmBroadcastStatus (uint16 NetworkMask)
* Description   : The J1939Dcm reports communication state changes to the BswM.

* Parameters(in): NetworkMask : The user that requests the mode.
*
* Return value  : None
* Remarks       : The corresponding configuration container for this API is BswMJ1939DcmBroadcastStatus.
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_J1939DcmBroadcastStatus
(
    VAR(uint16, AUTOMATIC) NetworkMask
)
{
#if ( BSWM_NO_OF_J1939DCM_CHANNELS > 0 )

    /* Local variables defined for this function. */
    VAR(boolean, AUTOMATIC) flgJ1939DcmChnIdVld_b = FALSE;
    VAR(uint8, AUTOMATIC) idJ1939DcmAllChn_u8 = 0;
    VAR(uint16, AUTOMATIC) idx_u16 = 0;
    VAR(boolean, AUTOMATIC) J1939DcmChnState_b = FALSE;
    VAR(sint8, AUTOMATIC) J1939DcmChnState_u8 = 0;
    VAR(BswM_Cfg_MRPJ1939DcmType_tst, AUTOMATIC) dataJ1939DcmMRP_st;


#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
    if ( FALSE == BswM_Prv_isModuleInitialised_b )
    {
        /* DET if the BSW Mode Manager is not initialized.*/
        BSWM_DET_REPORT_ERROR(BSWM_API_ID_J1939DCM, BSWM_E_NO_INIT);
    }
    else
    {
        /*loop through all network channels*/
        for(idJ1939DcmAllChn_u8 = 0; idJ1939DcmAllChn_u8 <=15; idJ1939DcmAllChn_u8++ )
        {

            /* Check J1939Dcm Channel  is set? */
            J1939DcmChnState_b = (((NetworkMask) & ((uint32)(1uL << idJ1939DcmAllChn_u8))) != 0uL);

            /*Typecast boolean to integer */
            J1939DcmChnState_u8 = (J1939DcmChnState_b == TRUE) ? 1:0 ;

            /* Check whether passed Network Channel-Id is valid and get corresponding index */
            flgJ1939DcmChnIdVld_b = BswM_Prv_GetJ1939DcmIndex_b(idJ1939DcmAllChn_u8, &idx_u16);

            /* Check if no other request is in progress */
            if ( (FALSE != flgJ1939DcmChnIdVld_b)&&(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_J1939_DCM_BROADCAST_STATS, idJ1939DcmAllChn_u8, idx_u16, (uint16)J1939DcmChnState_u8)))
            {

                /* Process any requests that were delayed before this request */
                if (FALSE != BswM_Prv_isReqstDelayed_b)
                {
                    BswM_Prv_ProcessDelayedReqst();
                }

                /* J1939Dcm Request MRP RAM Buffer updated at required index */
                BswM_Cfg_J1939DcmBroadCastStatusInfo_ast[idx_u16].isValidModePresent_b = TRUE;

                BswM_Cfg_J1939DcmBroadCastStatusInfo_ast[idx_u16].dataMode_b = J1939DcmChnState_b;

                dataJ1939DcmMRP_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataJ1939Dcm_ast[idx_u16];

                /* Rules of the request will be stored if it is Deferred/ evaluated if it is Immediate */
                BswM_Prv_RuleEval( dataJ1939DcmMRP_st.dataReqProcessing_en, BSWM_MRP_J1939_DCM_BROADCAST_STATS, (uint16)idJ1939DcmAllChn_u8, dataJ1939DcmMRP_st.adrRulesRef_pu16, dataJ1939DcmMRP_st.nrAssociatedRules_u16 );

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_J1939DCM);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /*To avoid compiler warning of unused parameters*/
      (void)NetworkMask;
#endif  /* ( BSWM_NO_OF_J1939DCM_CHANNELS > 0 ) */

     return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_J1939DCM_ENABLED == TRUE ) */
#endif /* BSWM_J1939DCM_ENABLED */

/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
