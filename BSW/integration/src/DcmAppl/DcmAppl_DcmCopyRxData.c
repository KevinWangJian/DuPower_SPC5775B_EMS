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
 *  DcmAppl_CopyRxData :-\n
 *  This API is called to inform the application regarding the data received in each call.
 *  The application can use the data for processing  The application should monitor and copy the valid contents from the buffer passed to the API during DcmAppl_StartOfReception call(ehere the request bytes are copied)
 *  from the RxBufferSize passed to it in each call which provided the buffer size copied in each call into the buffer.
 *
 *  @param[in]           RxBufferSize :   Size of the data copied in this call
 *  @param[in]           DcmRxPduId   :   RxPduId on which the Dcm_CopyRxData is called from the lower layer
 *  @retval              None
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_CopyRxData(VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                            VAR(PduLengthType, AUTOMATIC) RxBufferSize)
{
    (void)DcmRxPduId;
    (void)RxBufferSize;

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* #if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF) */

