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
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 *  @ingroup DCM_TPL
 *  DcmAppl_Switch_DcmExecuteReset :-\n
 *  This API is invoked to notify the application that Dcm shall trigger Ecu Reset soon after this API is called.The application may
 *  do the necessary actions required before reset in this function.The API is called only if RTE is disabled.
 *
 * @param[in]     None
 * @param[out]    None
 * @retval        None
 *
 */
 FUNC(void,DCM_APPL_CODE)  DcmAppl_Switch_DcmExecuteReset(void)
 {
	/*TESTCODE-START
	DcmTest_DcmAppl_Switch_DcmExecuteReset();
	TESTCODE-END*/
 }

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


