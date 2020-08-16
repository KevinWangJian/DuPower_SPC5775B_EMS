/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */

/* BASDKey_start */



#include "DcmDspUds_Roe_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/

#if ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF)))

 /**
 * @ingroup DCM_TPL
 * DcmAppl_Switch_DcmResponseOnEvent :-\n
 * This api is called to notify the application regarding change in event status of  Roe DID or Roe DTC
 *
 * @param[in]     RoeEventId_u8 : Event Identifier of the DID/DTC
 *                RoeEventStatus_en : Event Status (DCM_ROE_STARTED/DCM_ROE_STOPPED/DCM_ROE_CLEARED)
 * @retval        None
 *
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 FUNC(void,DCM_APPL_CODE)  DcmAppl_Switch_DcmResponseOnEvent(VAR(uint8,AUTOMATIC) RoeEventId_u8 , VAR(Dcm_DspRoeEventState_ten,AUTOMATIC) RoeEventStatus_en)
 {
     (void)RoeEventId_u8;
     (void)RoeEventStatus_en;

     /*TESTCODE-START
          DcmTest_DcmAppl_Switch_DcmResponseOnEvent(RoeEventId_u8,RoeEventStatus_en);
          TESTCODE-END*/

 }

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#endif /* ((DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)&& ((DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF) || (DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF))) */
