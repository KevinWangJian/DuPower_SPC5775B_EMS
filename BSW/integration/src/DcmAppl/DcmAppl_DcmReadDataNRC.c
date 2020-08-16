/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Rdbi_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if ( (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmReadDataNRC :-\n
 * If ReadData function has returned E_NOT_OK, Invoke the DcmAppl_DcmReadDataNRC to obtain the NRC from the application.
 *
 * @param[in]     Did : DID for which readdata has returned E_NOT_OK
 * @param[in]     DidSignalPosn : Signalposition within the DID whose readdata function has returned E_NOT_OK
 * @param[out]    ErrorCode     : NRC to be set by the application
 * @retval        E_OK      : The application has set the NRC successfully\n
 * @retval        E_NOT_OK  : The application has not set the NRC successfully\n
 *
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE)  DcmAppl_DcmReadDataNRC(VAR(uint16,AUTOMATIC)Did, VAR(uint32,AUTOMATIC)DidSignalPosn, P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	/*TESTCODE-START
	(void)DcmTest_DcmAppl_Switch_DcmReadDataNRC(Did,DidSignalPosn,ErrorCode);
	TESTCODE-END*/

	return (retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

