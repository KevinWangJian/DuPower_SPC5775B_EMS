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
 * @ingroup DCM_TPL
 * DcmAppl_DcmCheckCDTCRecord:-\n
 * This api should check the validity of the controlOptionRecord passed in the CDTC request.
 * @param[in]   ControlOptionRecord : Constant pointer to DTCSessionControlOptionRecord in request\n
 * @param[in]   Length              : Variable to hold length of contrl option record in request\n
 * @param[out]  ErrorCode           : Pointer to Negative Response Code, OUT Parameter\n
 *
 * @retval      E_OK : If contents of ControlOptionRecord is valid.\n
 * @retval      E_NOT_OK : If contents of ControlOptionRecord is invalid.\n
 */
FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckCDTCRecord (
                                    P2CONST(uint8,AUTOMATIC,DCM_INTERN_DATA) ControlOptionRecord,
                                    VAR(uint8,AUTOMATIC) Length,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                                )
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	(void)ControlOptionRecord;
    (void)Length;
    *ErrorCode = 0x00;

	/*TESTCODE-START
	retVal = DcmTest_DcmAppl_DcmCheckCDTCRecord(ControlOptionRecord,Length,ErrorCode);
	TESTCODE-END*/

    return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */

