/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Seca_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )



 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmGetUpdatedDelayTime :-\n
 *  Request to application to provide the updated delay time in milliseconds.\n
 *  More Information :-When the delay count is exceeded the delay timer should be started for the corresponding security level.
 *  If the delay count is exceeded this API is called with input parameter DelayTime (configured in SECA configuration) so that the application can change the
 *  Delay time if needed, depending on the number of times delay timer is activated.\n
 *  Ex: Delay Timer value for Security level 0x01 is 100ms, Delay count configured is 0x03.
 *  If Number of attempts performed to unlock security level is 3 the delay timer should be started.
 *  Call the API DcmAppl_DcmGetUpdatedDelayTime(Delay Time) which can change the delay time value and returns the updated delay time (Delay Time * n) where n = 1,2,3 etc.
 *  This API will return the same value sent to this function if the time is not changed by user.
 *
 * @param[in]           SecurityLevel      :  Security level for which the updated delay count is requested.
 * @param[in]           Delaycount         :  Number of times delay timer is activated
 * @param[in]           DelayTime          :  Delay time (ms) introduced after failed access attempts
 * @param[out]          None
 * @retval              Updated Delay time or power on delay time in milliseconds
 *
 */
FUNC(uint32,DCM_APPL_CODE) DcmAppl_DcmGetUpdatedDelayTime(
                                                        VAR(uint8,AUTOMATIC) SecurityLevel,
                                                        VAR(uint8,AUTOMATIC) Delaycount,
                                                        VAR(uint32,AUTOMATIC) DelayTime
                                                    )
{
    /* dummy code to remove compiler warning */
    (void)(SecurityLevel);
    (void)(Delaycount);

	/*TESTCODE-START
	DelayTime = DcmTest_DcmAppl_DcmGetUpdatedDelayTime(SecurityLevel,Delaycount,DelayTime);
	TESTCODE-END*/
    return (DelayTime);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)*/
