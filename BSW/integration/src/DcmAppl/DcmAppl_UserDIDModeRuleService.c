/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Uds_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if (((DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_UserDIDModeRuleService :-\n
 * This API is invoked to do specific checks on the DID read/write/control operation before processing the service.The ErrorCode parameter(Nrc_u8) needs to be updated by the application in case of failed checks.
 *
 * @param[in]     did_u16 : Did under processing
 * @param[in]     dataDirection_en: Indicates whether the DID is read/written/controlled (DCM_SUPPORT_READ/DCM_SUPPORT_WRITE/DCM_SUPPORT_IOCONTROL)
 * @param[out]    Nrc_u8 : NRC to be set by the application
 * @retval               E_OK   : DID specific checks passed successfully \n
 * @retval               E_NOT_OK  : DID specific checks failed\n
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_UserDIDModeRuleService(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8, VAR(uint16,AUTOMATIC) did_u16,VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
	*Nrc_u8= 0x00;
	/*TESTCODE-START
	retVal_u8=DcmTest_DcmAppl_UserDIDModeRuleService(Nrc_u8,did_u16,dataDirection_en);
	TESTCODE-END*/
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

