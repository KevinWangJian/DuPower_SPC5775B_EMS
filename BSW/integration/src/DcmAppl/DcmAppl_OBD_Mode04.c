/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspObd_Mode4_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if (DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_OBDMODE4_ENABLED != DCM_CFG_OFF)
#include "DcmDspObd_Mode4_Priv.h"
#include "DcmAppl.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_OBD_Mode04 :-\n
 * This API is used for check conditions for OBD Service 0x04.In this function, conditions like ignition is ON, engine is not running is checked if the conditions are
 * satisfied then returns E_OK state to service handler 0x04.
 *
 * @param[in]     None
 * @param[out]    None
 * @retval               E_OK : check the conditions 'ignition is ON' and 'Engine is not running 'then return E_OK.\n
 * @retval               E_NOT_OK : if any of the condition (ignition ON,engine is not running) fails then return E_NOT_OK.\n
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_OBD_Mode04(void)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	/*TESTCODE-START
	retVal = DcmTest_DcmAppl_OBD_Mode04();
	TESTCODE-END*/

	return retVal;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#endif
