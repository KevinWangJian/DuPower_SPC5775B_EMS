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

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmRespWarmInit :-\n
 * This API will be called for every Jump To Boot transition.User needs to modify this API only if User specific service is used for Jump to Boot.
 * If the user specific service is used for Jump to Boot using Warm Init, the necessary state changes for the service needs to be changed in this api to transmit
 * the final response before performing the reset operation.
 *
 * @param[in]       None
 * @param[out]      None
 * @retval          None
 */
FUNC(void, DCM_APPL_CODE) DcmAppl_DcmRespWarmInit(void)
{
	/* If the user specific service is used for Jump to Boot using Warm Init, the necessary
	 * state changes for the service needs to be changed here to transmit the final response
	 * before performing the reset operation.
	 */
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

