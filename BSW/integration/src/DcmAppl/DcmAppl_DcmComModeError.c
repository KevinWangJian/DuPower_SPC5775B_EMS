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

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmComModeError :-\n
 * This api is called by DCM to inform application that DCM is not in FULL COMMUNICATION or unable to move to
 * FULL COMMUNICATION MODE for the channel which is having the passed NetworkId.\n
 *
 *  @param[in]         NetworkId : Identifies the channel for which the error has ocured.\n
 *  @param[out]        None
 *  @retval            None\n
 *
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmComModeError (VAR(uint8, AUTOMATIC) NetworkId)
{
    /*DCM is not in FULL COMMUNICATION or unable to move to FULL COMMUNICATION MODE */
    (void) (NetworkId);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
