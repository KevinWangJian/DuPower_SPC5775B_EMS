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
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF))
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 *  @ingroup DCM_TPL
 *  DcmAppl_Switch_DcmExecuteEcuReset :-\n
 *  Inform the application to execute reset where the reset is triggered due to EcuReset service
 *  when used for jump to boot/drive
 *
 * @param[in]  ResetType_u8 : ResetType used for the EcuReset(e.g. DCM_NO_RESET,DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET or DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET)
 * @param[out] None
 * @retval     None
 *
 */
 FUNC(void,DCM_APPL_CODE)  DcmAppl_Switch_DcmExecuteEcuReset(VAR(uint8,AUTOMATIC) ResetType_u8)
 {
     (void) ResetType_u8;
	/*TESTCODE-START
	//DcmTest_DcmAppl_Switch_DcmExecuteEcuReset();
	TESTCODE-END*/
 }

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
