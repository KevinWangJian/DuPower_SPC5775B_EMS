/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_CC_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_UserCommCtrlReEnableModeRuleService :-\n
 * This API is invoked to check if communication control state needs to be re-enabled back to the default state DCM_ENABLE_RX_TX_NORM_NM
 *
 * @param[in]     None
 * @param[out]    None
 * @retval                E_OK   : Check to decide if the communication control state needs to be reenabled passed successfully \n
 * @retval                E_NOT_OK  : Check to decide if the communication control state needs to be reenabled  failed \n
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserCommCtrlReEnableModeRuleService(void)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
	/*TESTCODE-START
	retVal_u8=DcmTest_DcmAppl_UserCommCtrlReEnableModeRuleService();
	TESTCODE-END*/
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

