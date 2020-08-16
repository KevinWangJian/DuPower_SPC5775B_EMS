/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */




#include "DcmDspUds_Er_Inf.h"
#include "DcmAppl.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 * @ingroup DCM_TPL
 *  DcmAppl_DcmEcuResetPreparation :-\n
 *  This API prepares for reset.Integrator should add the code for the actions to be performed before Ecu Reset.\n
 * @param[in]         ResetType : The value can be DCM_NO_RESET ,DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET or DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET
 * @param[out]        ErrorCode : Error code to be updated.
 *
 * @retval            E_OK : Reset preparation is successfull
 * @retval            E_NOT_OK : Reset preparation is unsuccessfull
 * @retval            DCM_E_PENDING : The application needs more time for the operation
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmEcuResetPreparation(
                                                                VAR(uint8,AUTOMATIC) ResetType,
                                                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                )
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	*ErrorCode = 0x00;
    (void)(ResetType);

    /*This dummy code is just for reference */
	/*TESTCODE-START
	retVal = DcmTest_DcmAppl_DcmEcuResetPreparation(ResetType,ErrorCode);
	TESTCODE-END*/

    return retVal;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) */
