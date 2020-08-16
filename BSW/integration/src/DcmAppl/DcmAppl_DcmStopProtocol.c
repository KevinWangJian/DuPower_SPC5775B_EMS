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

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStopProtocol :-\n
 * This API is invoked if a running diagnostic requested is preempted by a higher priority request (of an other protocol, e.g. OBD),
 * application is requested to abort further processing of running request and finish with Dcm_ProcessingDone().\n
 * With this callback function, application can shutdown during protocol preemption.
 * @param[in]         ProtocolID   :  Name of the protocol (IDs configured within DCM_PROTOCOL_ID)
 * @param[out]        None
 * @retval            E_OK : Always it will return this value.
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmStopProtocol(VAR(Dcm_ProtocolType,AUTOMATIC) ProtocolID)
{
#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
    rba_DiagAdapt_StopProtocol(ProtocolID);
#else
    /* dummy code to remove compiler warning. Actual code to be written by user */
    (void)(ProtocolID);
#endif
    /*TESTCODE-START
   (void)DcmTest_DcmAppl_DcmStopProtocol(ProtocolID);
    TESTCODE-END*/
    return(E_OK);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
