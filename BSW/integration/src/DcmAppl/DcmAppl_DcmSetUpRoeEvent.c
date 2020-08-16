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

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
#if((DCM_CFG_DSP_ROEONDTCSTATUSCHANGE_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_ROEDID_ENABLED != DCM_CFG_OFF))

/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmSetUpRoeEvent:-\n
 * The API will be called for UDS Setup request (OnDTCStatusChange or OnChangeOfDataIdentifier).
 * Since eventWindowTime is monitored in Application and cycle monitoring in Dcm.
 * Through the API DcmAppl_DcmSetUpRoeEvent(), we can send the eventWindowTime information to application.
 *
 * @param[in]            RoeeventID                 : Event Id of Roe Event
 * @param[in]            eventType                  : Event Type of the ROE request
 * @param[in]            storageState               : Status of the storage bit
 * @param[in]            eventWindowTime            : Value of the event window time
 * @param[in]            eventTypeRecord            : The pointer to the buffer which contains the event record bytes
 * @param[in]            serviceToRespondToRecord   : The pointer to the buffer which contains the
 *                                                    service to respond to record bytes
 * @param[in]            OpStatus                   : Information of OpStatus
 *
 * @param[out]           ErrorCode: Reason for not setting up the requested event
 *
 * @retval               E_OK: Setting up the requested Event type is successful\n
 *                       E_NOT_OK: The requested event type cannot be setup\n
 *                       DCM_E_PENDING: Need more time to setup the requested event\n
 */
 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
 #include "Dcm_Cfg_MemMap.h"
 FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmSetUpRoeEvent (VAR(uint8,AUTOMATIC) RoeeventID,
                                                              VAR(uint8,AUTOMATIC) eventType,
                                                              VAR(boolean,AUTOMATIC) storageState,
                                                              VAR(uint8,AUTOMATIC) eventWindowTime,
                                                              P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) eventTypeRecord,
                                                              P2CONST(uint8,AUTOMATIC,DCM_INTERN_CONST) serviceToRespondToRecord,
                                                              VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	*ErrorCode = 0x0;
	(void)(RoeeventID);
	(void)(eventType);
    (void)(storageState);
    (void)(eventWindowTime);
    (void)(eventTypeRecord);
    (void)(serviceToRespondToRecord);
    (void)(OpStatus);
    /*TESTCODE-START
	retVal = DcmTest_DcmAppl_DcmSetUpRoeEvent(RoeeventID,eventType,storageState,eventWindowTime,eventTypeRecord,serviceToRespondToRecord,OpStatus,ErrorCode);
	TESTCODE-END*/
    return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
#endif
