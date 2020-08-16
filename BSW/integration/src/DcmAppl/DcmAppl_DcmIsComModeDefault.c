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
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )

#if((DCM_CFG_RTESUPPORT_ENABLED==DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmIsComModeDefault :-\n
 * This api is called to check whether the ComM channel identified by the passed Network ID is in default ComMode(DCM_ENABLE_RX_TX_NORM_NM).
 *
 * @param[in]   NetworkHandleType : NetworkID
 * @param[out]  None
 * @retval      TRUE : ComMode is default.
 * @retval      FALSE : ComMode is not default.
 *
 */
FUNC (boolean, DCM_APPL_CODE) DcmAppl_DcmIsComModeDefault( VAR(uint8,DCM_VAR) NetworkID )
{

	VAR(boolean,AUTOMATIC) retVal = TRUE;
	(void)(NetworkID);

	/*TESTCODE-START
	retVal = DcmTest_DcmAppl_DcmIsComModeDefault(NetworkID);
	TESTCODE-END*/

	return (retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) */
