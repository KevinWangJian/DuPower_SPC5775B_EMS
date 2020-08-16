/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmCore_DslDsd_Inf.h"


#if(DCM_CFG_NR_CONF_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmConfirmation_DcmNegResp :-\n
 * This API is invoked as an indication called by DSD after sending the DSD generated Neg response and after sending the General rejectresponse by DSL.\n
 *
 * @param[in]     idContext   :  Current context identifier which can be used to retrieve the relation between request and confirmation.Within the confirmation, the Dcm_MsgContext\n
 *                               is no more available, so the idContext can be used to represent this relation.
 * @param[in]     dcmRxPduId  :  DcmRxPduId on which the request was received. The source of the request can have consequences for message processing.The idContext is also part of the Dcm_MsgContext.\n
 * @param[in]     status      :  Status indication about confirmation (differentiate failure indication and normal confirmation) / The parameter "Result" of "Dcm_TpTxConfirmation" shall be forwarded\n
 *                               to status depending if a positive or negative responses was sent before.\n
 * @param[out]    None
 * @retval        None
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmConfirmation_DcmNegResp(
                                                        VAR(Dcm_IdContextType,AUTOMATIC) idContext,
                                                        VAR(PduIdType,AUTOMATIC) dcmRxPduId,
                                                        VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status
                                                      )
{
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_Confirmation(idContext, dcmRxPduId, status);
#else
    /* dummy code to remove compiler warning. Actual code to be written by user. */
    (void)(status);
    (void)(dcmRxPduId);
    (void)(idContext);
#endif
    /*TESTCODE-START
   (void)DcmTest_DcmAppl_DcmConfirmation_DcmNegResp(idContext,dcmRxPduId,status);
    TESTCODE-END*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

