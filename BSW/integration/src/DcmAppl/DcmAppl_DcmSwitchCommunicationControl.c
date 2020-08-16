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
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmSwitchCommunicationControl :-\n
 * This api will be called after sending the confirmation for the UDS service Communication control(0x28).\n
 * Dcm will pass the network ID of the channel and the new requested Communication mode to this api.Application can perform required actions if any.
 * @param[in]  NetworkID        : Channel Id for which the communication mode is requested.
 * @param[in]  RequestedMode    : Requested CommunicationMode
 * @retval     None
 */
FUNC (void, DCM_APPL_CODE) DcmAppl_DcmSwitchCommunicationControl( VAR(uint8,DCM_VAR) NetworkID ,Dcm_CommunicationModeType RequestedMode)
{
	(void)(NetworkID);
	(void)(RequestedMode);
	/*TESTCODE-START
	DcmTest_DcmAppl_DcmSwitchCommunicationControl(NetworkID,RequestedMode);
	TESTCODE-END*/
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */
