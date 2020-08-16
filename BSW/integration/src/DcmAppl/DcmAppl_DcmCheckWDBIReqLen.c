/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Wdbi_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/



#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 * @ingroup DCM_TPL
 *  DcmAppl_DcmCheckWDBIReqLen :-\n
 *  This function is used by the application to perform the exact length checkfor the request in case variable length signals are configured for the requested DID.\n
 *  As per the current implementation of WDBI service in Dcm, if there is one variable length signal configured, then no other signals are allowed to be configured for that DID.\n
 *  So, the passed length parameter to this callback function shall include the request length of only one variable length signal.
 *
 * @param[in]        nrDID_u16  : Received DID in the request \n
 * @param[in]        dataReqLen_u32 : Length of the received request excluding the DID(length of the variable length signal in the request).\n
 * @param[out]       None
 * @retval           E_OK:     If the request length is correct.\n
 * @retval           E_NOT_OK: If the request length is incorrect.In this case, Dcm shall trigger NRC 0x13(DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT) in the response
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmCheckWDBIReqLen(VAR(uint16,AUTOMATIC) nrDID_u16, VAR(uint32,AUTOMATIC) dataReqLen_u32)
{

    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
    (void)nrDID_u16;
    (void)dataReqLen_u32;

    /*TESTCODE-START
    retVal=DcmTest_DcmAppl_DcmCheckWDBIReqLen(nrDID_u16,dataReqLen_u32);
    TESTCODE-END*/

    return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* #if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) */
