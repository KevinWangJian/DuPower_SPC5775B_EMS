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
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
/*
#include "FrIf.h"
#include "FrSM.h"
#include "ComM.h"
*/



#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * Dcm_GetProgConditions :-\n
 * This API is used for restoring the Programming Information by the application.\n
 * This API should  restore the Programming conditions from the Non volatile memory which was stored during Jump To Boot.\n
 * In this API user has to restore the protocol information required to start Dcm\n
 *
 *  @param[in] ProgConditions \n
 *  The following information needs to be filled by the user in ProgConditions\n
 *     1. ProtocolID - protocol which needs to be started as default\n
 *     2. Tester Source address - Connection will be derived from this input\n
 *     3. SID - service identifier (In case of Warm request/Warm response)\n
 *     4. SubFncId - Subfunction ID\n
 *     5. StoreType - Storage Type used for restoring, Warm Request/Warm Response/Warm Init\n
 *     6. SessionLevel - Session level which needs to be started\n
 *     7. SecurityLevel - Security level which needs to be started\n
 *     8. ReqResLen - Total request/response length including SID and Subfunc\n
 *     9. Request/Response bytes which follows the SID and Subfunc\n
 *     10.Number of Response pending 0x78 triggered before the jump\n
 *     11.Elapsed time in Drive or Boot\n
 *     12. NumOfSecurityLevels - Number of security levels configured,
 *           If the configuration parameter DcmDspSecurityStoreDelayCountAndTimerOnJump  is set to True, then the below information has to be stored
 *     13. SecurityInformation[].SecurityLevel = Security level\n
 *     14.SecurityInformation[].DelayCount = The failed attempt count per SecurityLevel\n
 *     15.SecurityInformation[].ResidualDelay = Remaining delay (either remaining powerOndelay/remaining delay time) per SecurityLevel which will be started in Dcm per security level\n
 *     16.freeForProjectUse 6 bytes of free space is provided for projects to store additional information like CAN ID, BAUD Rate, etc..\n
 *
 * @param[out]      ProgConditions : Pointer to the location where the programming conditions  to be stored.
 *
 *
 * @retval                 DCM_WARM_START : The ECU starts from a bootloader jump\n
 * @retval                 DCM_COLD_START : Start ECU Normally\n
 *
 */
FUNC(Dcm_EcuStartModeType,DCM_APPL_CODE) Dcm_GetProgConditions
                                   (P2VAR(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions)
{
	VAR(Dcm_EcuStartModeType,AUTOMATIC) retVal = DCM_COLD_START;

	/*TESTCODE-START
	retVal = DcmTest_Dcm_GetProgConditions(ProgConditions);
	TESTCODE-END*/

	/* Restoring the protocol information from NvRAM */
	return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
