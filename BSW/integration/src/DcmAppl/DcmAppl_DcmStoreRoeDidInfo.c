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

#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)

#if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)


 /**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStoreRoeDidInfo :-\n
 * Function to do specific checks on the subfunction parameter before processing the service.The ErrorCode parameter(Nrc_u8) needs to be updated by the application in case of failed checks.
 *
 * @param[in]       DID : DID to be monitored by ROE
 * @param[in]	    RoeeventID : Event Id of Roe Event
 * @param[in]       RoeEventStatus : Status of Roe Event. The possible values of RoeEventStatus is DCM_ROE_CLEARED, DCM_ROE_STOPPED and DCM_ROE_STARTED
 * @param[in]       SourceAddress : Tester Source Address.Source of the address value is from configuration parameter DcmDslProtocolRxTesterSourceAddr.
 * @param[in]       dspRoeStorageState_b : Storage bit information
 * @param[in]       OpStatus : Information of the opstatus
 * @param[in]       dspRoeSessionIsDefault_b : If the current session is Default session, than this parameter will be  true
 * @param[inout]    None
 * @param[out]      ErrorCode: Reason for not setting up the requested event
 * @retval          Std_ReturnType
 *                  E_OK   :    storing event successful.
 *	                E_NOT_OK  : Storing event not ok.
 *                  DCM_E_PENDING: Need more time to store the event
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStoreRoeDidInfo( VAR(uint16,AUTOMATIC)  Did,
                                                               VAR(uint8,AUTOMATIC)  RoeeventID,
                                                               VAR(Dcm_DspRoeEventState_ten,AUTOMATIC) RoeEventStatus,
                                                               VAR(uint16,AUTOMATIC)  SourceAddress,
                                                               VAR(boolean,AUTOMATIC)  dspRoeStorageState_b,
                                                               VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                               VAR(boolean,AUTOMATIC) dspRoeSessionIsDefault_b,
                                                               P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
	*ErrorCode = 0x0;
    (void)(Did);
    (void)(RoeeventID);
    (void)(RoeEventStatus);
    (void)(SourceAddress);
    (void)(dspRoeStorageState_b);
    (void)(OpStatus);
    (void)(dspRoeSessionIsDefault_b);
	/*TESTCODE-START
	retVal_u8=DcmTest_DcmAppl_DcmStoreRoeDidInfo( Did, RoeeventID, RoeEventStatus, SourceAddress, dspRoeStorageState_b, OpStatus, dspRoeSessionIsDefault_b, ErrorCode);
	TESTCODE-END*/
	return (retVal_u8);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
#endif
#endif
