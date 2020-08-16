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
 *  DcmAppl_StartOfReception :-\n
 *  This API is invoked to inform the application regarding the the reception of a new request.\n
 *  The SID and RXPduId is passed to the application which can be used for checking the request received and the
 *  PduId on which the request was received.
 *  @param[in]           idContext     : SID of the service which is running.\n
 *  @param[in]           DcmRxPduId    : RxPduId on which the Dcm_CopyRxData is called from the lower layer.\n
 *  @param[in]           RequestLength : Total Length of the request(inclusing the SID)\n
 *  @param[in]           RxBufferPtr   : Rx buffer where the request data is copied. The buffer will point to SID value\n
 *  @param[out]          None
 *  @retval              None
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_StartOfReception(VAR(Dcm_IdContextType,AUTOMATIC) idContext ,
                                                     VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                                     VAR(PduLengthType, AUTOMATIC) RequestLength,
                                                     VAR(uint32, AUTOMATIC) RxBufferPtr)
{
    (void)idContext;
    (void)DcmRxPduId;
    (void)RequestLength;
    (void)RxBufferPtr;

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* #if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF) */

