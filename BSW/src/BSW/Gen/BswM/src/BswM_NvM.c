

/*---------------------------------------------------------------------------------------*/
/*- Include files																		-*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_Prv.h"
#include "BswM_NvM.h"

/*---------------------------------------------------------------------------------------*/
/*- Definition of Global Functions														-*/
/*---------------------------------------------------------------------------------------*/

#ifdef BSWM_NVM_ENABLED
#if ( BSWM_NVM_ENABLED == TRUE )

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*****************************************************************************************
* Function name	: void BswM_NvM_CurrentBlockMode( NvM_BlockIdType Block, NvM_RequestResultType CurrentBlockMode )
* Description	: Function called by NvM to indicate the current block mode of an NvM block.
*                 To use this function integration code will be needed.
* Parameter  	: Block - The Block that the new NvM Mode corresponds to.
*               : CurrentBlockMode - The current block mode of the NvM block.
* Return value	: None
* Remarks		:
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_NvM_CurrentBlockMode
(
    VAR(NvM_BlockIdType, AUTOMATIC) Block,
    VAR(NvM_RequestResultType, AUTOMATIC) CurrentBlockMode
)
{
#if ( BSWM_NO_OF_NVM_REQUESTS > 0 )

    VAR(boolean,AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(boolean,AUTOMATIC) isValidBlockId_b = FALSE;
    VAR(BswM_Cfg_MRPNvMReqType_tst, AUTOMATIC) dataNvMReq_st;
    VAR(uint16, AUTOMATIC) idxBlk_u16 = 0;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
   if ( FALSE == BswM_Prv_isModuleInitialised_b )
   {
       /* DET if the BSW Mode Manager is not initialized.*/
       BSWM_DET_REPORT_ERROR(BSWM_API_ID_NVMCURRBLOCKMODE, BSWM_E_NO_INIT);
   }
   else
   {
       if( NVM_REQ_RESTORED_FROM_ROM < CurrentBlockMode )
       {
           /* DET if CurrentBlockMode is not in range.*/
           BSWM_DET_REPORT_ERROR(BSWM_API_ID_NVMCURRBLOCKMODE, BSWM_E_REQ_MODE_OUT_OF_RANGE );
       }
       else
       {
            isValidBlockId_b = BswM_Prv_GetNvMBlockModeMRPIndex_b(Block,&idxBlk_u16);
            if(FALSE == isValidBlockId_b)
            {
               /* DET if Block ID is not in range.*/
                BSWM_DET_REPORT_ERROR(BSWM_API_ID_NVMCURRBLOCKMODE, BSWM_E_REQ_USER_OUT_OF_RANGE );
            }
            else
            {
                flgDetChecksPassed_b = TRUE;
            }
       }
   }

   if(FALSE != flgDetChecksPassed_b)
   {
       /* Check if no other request is in progress */
      if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_NVM_REQST, Block, idxBlk_u16, (uint16)CurrentBlockMode ))
      {
          /* Process requests that interrupted the processing of the previous mode request */
          if (FALSE != BswM_Prv_isReqstDelayed_b)
          {
              BswM_Prv_ProcessDelayedReqst();
          }

          /*Update RAM buffer with current mode values*/

          BswM_Cfg_NvMReqInfo_ast[idxBlk_u16].isValidModePresent_b = TRUE;

          BswM_Cfg_NvMReqInfo_ast[idxBlk_u16].dataMode_en = CurrentBlockMode;

          dataNvMReq_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMReq_ast[idxBlk_u16];

          BswM_Prv_RuleEval(dataNvMReq_st.dataReqProcessing_en,BSWM_MRP_NVM_REQST,Block,dataNvMReq_st.adrRulesRef_pu16,dataNvMReq_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_NVMCURRBLOCKMODE);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else
    /*To avoid compiler warning of unused parameters*/
    (void)Block;
    (void)CurrentBlockMode;
#endif  /* (BSWM_NO_OF_NVM_REQUESTS > 0) */
	return;
}


/*****************************************************************************************
* Function name	: void BswM_NvM_CurrentJobMode( uint8 ServiceId, NvM_RequestResultType CurrentJobMode )
* Description	: Function called by NvM to inform the BswM about the current state of a multi block job.
* Parameter  	: ServiceId - Indicates whether the callback refers to multi block services NvM_ReadAll or NvM_WriteAll.
*               : CurrentJobMode - Current state of the multi block job indicated by parameter ServiceId.
* Return value	: None
* Remarks		:
*****************************************************************************************/
FUNC(void, BSWM_CODE) BswM_NvM_CurrentJobMode
(
    VAR(uint8, AUTOMATIC) ServiceId,
    VAR(NvM_RequestResultType, AUTOMATIC) CurrentJobMode
)
{
#if (BSWM_NO_OF_NVM_SERVICE_IDS > 0)

    VAR(boolean,AUTOMATIC) flgDetChecksPassed_b = FALSE;
    VAR(boolean,AUTOMATIC) isValidServiceId_b = FALSE;
    VAR(BswM_Cfg_MRPNvMJobModeIndType_tst, AUTOMATIC) dataNvMJobMode_st;
    VAR(uint16, AUTOMATIC) idxBlk_u16 = 0;

#if ( BSWM_DEBUG == TRUE )
    /*BswM_Prv_ctrInterrupt_u8 used for counting how many times BswM is getting interrupted*/
    BswM_Prv_ctrInterrupt_u8++;
#endif /* ( BSWM_DEBUG == TRUE ) */

    /* Is BswM initialized ? */
   if ( FALSE == BswM_Prv_isModuleInitialised_b )
   {
       /* DET if the BSW Mode Manager is not initialized.*/
       BSWM_DET_REPORT_ERROR(BSWM_API_ID_NVMCURRJOBMODE, BSWM_E_NO_INIT);
   }
   else
   {
       if( NVM_REQ_RESTORED_FROM_ROM < CurrentJobMode )
       {
           /* DET if CurrentJobMode is not in range.*/
           BSWM_DET_REPORT_ERROR(BSWM_API_ID_NVMCURRJOBMODE, BSWM_E_REQ_MODE_OUT_OF_RANGE);
       }
       else
       {
            /* Get the service  */
            isValidServiceId_b = BswM_Prv_GetNvMJobModeMRPIndex_b(ServiceId,&idxBlk_u16);

            if(FALSE == isValidServiceId_b)
            {
               /* DET if Service ID is not in range.*/
                BSWM_DET_REPORT_ERROR(BSWM_API_ID_NVMCURRJOBMODE, BSWM_E_REQ_USER_OUT_OF_RANGE );
            }
            else
            {
                flgDetChecksPassed_b = TRUE;
            }
       }
   }

    if(FALSE != flgDetChecksPassed_b)
    {
        /* Check if no other request is in progress */
        if(FALSE != BswM_Prv_ReqProcessOrQueue_b(BSWM_MRP_NVM_JOB_MODE_IND, (uint16)ServiceId, idxBlk_u16, (uint16)CurrentJobMode ))
        {
            /* Process requests that interrupted the execution of the current request */
            if (FALSE != BswM_Prv_isReqstDelayed_b)
            {
                BswM_Prv_ProcessDelayedReqst();
            }

            /*Update RAM buffer with current mode values*/
            BswM_Cfg_NvMJobModeInfo_ast[idxBlk_u16].isValidModePresent_b = TRUE;

            BswM_Cfg_NvMJobModeInfo_ast[idxBlk_u16].dataMode_en = CurrentJobMode;

            dataNvMJobMode_st = BswM_Prv_adrSelectedConfig_pcst->dataModeArbitration_st.dataModeRequestPorts_st.dataNvMJobMode_ast[idxBlk_u16];

            BswM_Prv_RuleEval(dataNvMJobMode_st.dataReqProcessing_en,BSWM_MRP_NVM_JOB_MODE_IND,ServiceId,dataNvMJobMode_st.adrRulesRef_pu16,dataNvMJobMode_st.nrAssociatedRules_u16);

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
    BswM_Prv_InterruptHandler(BSWM_API_ID_NVMCURRJOBMODE);
#endif /* ( BSWM_DEBUG == TRUE ) */

#else /* (BSWM_NO_OF_NVM_SERVICE_IDS > 0) */
    /*To avoid compiler warning of unused parameters*/
    (void)ServiceId;
    (void)CurrentJobMode;
#endif /* (BSWM_NO_OF_NVM_SERVICE_IDS > 0) */
	return;
}

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_NVM_ENABLED == TRUE ) */
#endif /* BSWM_NVM_ENABLED */
/**********************************************************************************************************************
 * End of source file
 **********************************************************************************************************************/
