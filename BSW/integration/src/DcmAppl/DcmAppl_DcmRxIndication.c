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

#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 *  DcmAppl_TpRxIndication :-\n
 *  This API is called to inform the application regarding the the completion of copying of the request into the Dcm buffer.
 *  The RXPduId and the status  of reception is passed to the application.
 *  In case the reception is not successful, the  the application can do necessary steps to cancel the processing in the application
 *  @param[in]     idContext : SID of the service which is running.
 *  @param[in]     Result    : Status of reception.
 *  @param[out]    None
 *  @retval        None
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_TpRxIndication( VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                                  VAR(Std_ReturnType, AUTOMATIC) Result)
{
    (void)DcmRxPduId;
    (void)Result;

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* #if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF) */

