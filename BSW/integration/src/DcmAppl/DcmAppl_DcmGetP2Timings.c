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

#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED == DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmGetP2Timings :-\n
 * This API is used to get the values of P2ServerMax and P2StarServer Max
 * when the vendor specific DiagnosticSessionControl service is configured.
 *
 * @param[in]  dataSessionId_u8  : active session level
 * @param[out] adrP2Timing_pu32  : Pointer to P2ServerMax value
 * @param[out] adrP2StarTiming_pu32 : Pointer to P2StarServerMax value
 *
 * @retval     None
 *
 */
FUNC(void, DCM_APPL_CODE) DcmAppl_DcmGetP2Timings(
                                        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrP2Timing_pu32,
                                        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) adrP2StarTiming_pu32,
                                        VAR(Dcm_SesCtrlType, AUTOMATIC) dataSessionId_u8
                                     )
{
	/*TESTCODE-START
		if(dataSessionId_u8 == 0x01)
	{
		*adrP2Timing_pu32 = 50000;
		*adrP2StarTiming_pu32= 5000000;
	}
	else
	{
		*adrP2Timing_pu32= 40000;
		*adrP2StarTiming_pu32= 4000000;
	}

	TESTCODE-END*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
