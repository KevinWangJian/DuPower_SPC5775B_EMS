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

#if (((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_UserMemoryRangeModeRuleService :-\n
 * This API is used to do specific checks on the DID read/write/control operation before processing the service.The ErrorCode parameter(Nrc_u8) needs to be updated by the application in case of failed checks.
 *
 * @param[in]     adrMemoryAddress_u32 : Address location from which data should be read/written
 * @param[in]     dataDataLength_u32 :length of the data to be read/written
 * @param[in]     dataDirection_en: Indicates whether the memory location is being read/written (DCM_SUPPORT_READ/DCM_SUPPORT_WRITE)
 * @param[out]    Nrc_u8 : NRC to be set by the application
 * @retval               E_OK   : Memory location specific checks passed successfully \n
 * @retval               E_NOT_OK  : Memory location specific checks failed\n
 *
 */
FUNC(Std_ReturnType,DCM_CODE) DcmAppl_UserMemoryRangeModeRuleService(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) Nrc_u8,VAR(uint32,AUTOMATIC) adrMemoryAddress_u32,VAR(uint32,AUTOMATIC) dataDataLength_u32,VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
	*Nrc_u8= 0x00;
	/*TESTCODE-START
	retVal_u8=DcmTest_DcmAppl_UserMemoryRangeModeRuleService(Nrc_u8,adrMemoryAddress_u32,dataDataLength_u32,dataDirection_en);
	TESTCODE-END*/
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

