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

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF) )


 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 *  DcmAppl_DcmSecurityLevelLocked:-\n
 *  For each security level the number of unsuccessful attempts after which the security level is locked will be configured (Lock Count).
 *  If this Lock count is reached, the corresponding security level will be locked and a notification is given to application is given using this API.
 *  Integrator can perform required operations based on the notification.\n
 *
 *  Ex: Lock count configured for Security Level 0x01 is 0x02.\n
 *  Tester sends to ECU, 2 key request with invalid Key. ECU sees that the number of attempts has been reached and locks the security level.
 *  A notification will be given to application using the API DcmAppl_DcmSecurityLevelLocked.
 *
 * @param[in]       SecTabIdx : Index of the Security Table in configuration(Security level)\n
 * @param[out]      None
 * @retval          None
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmSecurityLevelLocked(VAR(uint8,AUTOMATIC) SecTabIdx)
{
    /* dummy code to remove compiler warning */
    (void)(SecTabIdx);

    return;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)*/
