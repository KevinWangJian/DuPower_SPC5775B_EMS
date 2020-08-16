/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Rc_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_UserRIDModeRuleService :-\n
 * Function to do specific checks on the RID in  the routine control requests before processing the service.The ErrorCode parameter(Nrc_u8) needs to be updated by the application in case of failed checks.
 *
 * @param[in]     rid_u16 : RID under processing
 * @param[in]     Subfunc_u8 : Subfunction of the service under process
 * @param[out]    Nrc_u8 : NRC to be set by the application
 * @retval               E_OK   : RID specific checks passed successfully \n
 * @retval               E_NOT_OK  : RID specific checks failed\n
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserRIDModeRuleService(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8, VAR(uint16,AUTOMATIC) rid_u16, VAR(uint8,AUTOMATIC) subfunction_u8)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
	*Nrc_u8= 0x00;
	/*TESTCODE-START
	retVal_u8=DcmTest_DcmAppl_UserRIDModeRuleService(Nrc_u8,rid_u16,subfunction_u8);
	TESTCODE-END*/
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

