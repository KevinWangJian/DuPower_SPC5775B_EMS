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
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * Dcm_SetProgConditions :-\n
 * This API is used for Setting the Programming Information in the application.This API should take a copy of the Programming conditions given by Dcm to the Non volaitile memory.\n
 * This information will be restored again during Jump from Boot.\n
 *
 ** @param[in]       ProgConditions  : Pointer to the location where the programming conditions are stored.\n
 *  The information available to this API which needs to be stored are\n
 *     1. ProtocolID - protocol which needs to be started as default\n
 *     2. Tester Source address - Connection will be derived from this input\n
 *     3. SID - service identifier (In case of Warm request/Warm response)\n
 *     4. SubFncId - Sub function ID\n
 *     5. StoreType - Storage Type used for restoring, Warm Request/Warm Response/Warm Init\n
 *     6. SessionLevel - Session level which needs to be started\n
 *     7. SecurityLevel - Security level which needs to be started\n
 *     8. ReqResLen - Total request/response length including SID and Sub func\n
 *     9. Request/Response bytes which follows the SID and Sub func\n
 *     10.Number of Response pending 0x78 triggered before the jump\n
 *     11.Elapsed time in Drive or Boot\n
 *     12. NumOfSecurityLevels - Number of security levels configured
 *           If the configuration parameter DcmDspSecurityStoreDelayCountAndTimerOnJump  is set to True, then the below information has to be stored
 *     13. SecurityInformation[].SecurityLevel = Security level
 *     14.SecurityInformation[].DelayCount = The failed attempt count per SecurityLevel
 *     15.SecurityInformation[].ResidualDelay = Remaining delay (either remaining powerOndelay/remaining delay time) per SecurityLevel which will be started in Dcm per security level
 *     16.freeForProjectUse 6 bytes of free space is provided for projects to store additional information like CAN ID, BAUD Rate, etc..\n
 *
 * @param[in]       Opstatus        : Information on the opstatus\n
 * @param[out]      None
 * @retval          E_OK            : Storing is sucessful\n
 * @retval          DCM_E_PENDING   : Need more time for Storing\n
 * @retval          E_NOT_OK        : Storing is unsucessful\n
 * @retval          DCM_E_FORCE_RCRRP : Application requests the transmission of a response Response Pending (NRC 0x78)\n
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) Dcm_SetProgConditions(VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                        P2CONST(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions)
{

	/* User / Application should add the necessary code to copy the contents to Non volatile RAM */
    /* The information available to this API which needs to be stored are
       1. ProtocolID - protocol on which Jumping is initiated
	   2. Tester Source address on which the request is sent
	   3. SID - service identifier (In case of Warm request/Warm response)
	   4. SubFncId - Subfunction ID
	   5. StoreType - Storage Type used for restoring, Warm Request/Warm Response/Warm Init
	   6. SessionLevel - active Session level which needs to be stored
	   7. SecurityLevel - active Security level which needs to be stored
	   8. ReqResLen - Total request/response length including SID and Subfunc
	   9. Request/Response bytes which follows the SID and Subfunc
	   10.Number of Response pending 0x78 triggered before jumping
	   11. 6 byte array is provided to store additional information like CAN NODE ID, baud rate etc..Projects can use this if necessary*/

	VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	/*TESTCODE-START
	retVal= DcmTest_Dcm_SetProgConditions(OpStatus,ProgConditions);
	TESTCODE-END*/
	return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif

