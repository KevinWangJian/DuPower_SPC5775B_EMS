/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Roe_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)

#if((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStoreROEcycleCounter :-\n
 * The API will be invoked to store the CycleValue in NvM
 *
 * @param[in]	  RoeeventID : Event Id of Roe Event.
 * @param[in]     CycleValue : CycleValue of eventWindowTime.
 *                CycleValue=0x02 (EventWindowTime is Infinity)
 *                CycleValue=0x03 (EventWindowTime is CurrentCycle)
 *                CycleValue=0x04 (EventWindowTime is CurrentAndFollowingCycle)
 *                CycleValue=0x00 (EventWindowTime is not set)
 * @param[in]     OpStatus:  Information of the opstatus
 * @param[out]    ErrorCode: Reason for not setting up the requested event
 *
 * @retval        E_OK: Setting up the requested Event type is successful\n
 *                E_NOT_OK: The requested event type cannot be setup\n
 *                DCM_E_PENDING: Need more time to setup the requested event\n
  *
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
FUNC(void,DCMAPPL_CODE) DcmAppl_DcmStoreROEcycleCounter(VAR(uint8,AUTOMATIC) RoeeventID,
                                                                  VAR(uint8,AUTOMATIC) CycleValue
                                                                  )
{

    (void)(RoeeventID);
    (void)(CycleValue);


	/*TESTCODE-START
	DcmTest_DcmAppl_DcmStoreROEcycleCounter(RoeeventID,CycleValue);
	TESTCODE-END*/
    return ;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
#endif
