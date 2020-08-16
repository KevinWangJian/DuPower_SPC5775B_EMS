/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Cdtcs_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *@ingroup DCM_TPL
 * DcmAppl_DisableDTCSetting:-\n
 * This api is called to get permission to disable DTC Setting.
 *
 * @param[inout]   ErrorCode: Pointer to Negative Response Code.
 * @retval      None
 *
 *
 */
FUNC (void, DCM_APPL_CODE) DcmAppl_DisableDTCSetting (
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                   )
{
    *ErrorCode = 0x00;
	/*TESTCODE-START
	DcmTest_DcmAppl_DisableDTCSetting(ErrorCode);
	TESTCODE-END*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */

