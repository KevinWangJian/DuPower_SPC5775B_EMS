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


#if (DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmNotification :-\n
 *  This API indicates the successful reception of a new request to application and it is called right before processing the diagnostic service XXX_Dcm<DiagnosticService>.\n
 *  Within this function application can examine the permission of the diagnostic service / environment (e.g. ECU state after run).\n
 *  Return of application will lead to an acceptance of diagnostic request,reject of diagnostic request (-> no response will be send) or to an NRC 0x22 (ConditionsNotCorrect).\n
 *
 * @param[in]           SID          : Value of service identifier
 * @param[in]           RequestData  : Pointer to the request data buffer.
 * @param[in]           RequestLength : Request data length
 * @param[in]           RequestType : It says whether the request is FUNCTIONAL/PHYSICAL
 * @param[in]           DcmRxPduId :  RxPduId on which the request is received
 * @param[in]           SourceAddress : This variable gives the source address
 * @param[out]          ErrorCode : Ponter to the variable to update the error code
 *
 * @retval          DCM_E_OK : Diagnostic request accepted
 * @retval          DCM_E_REQUEST_NOT_ACCEPTED : Application rejects diagnostic request -> DSD will ignore
 *                  diagnostic request, no further processing of request, no response will be send
 * @retval          DCM_E_PENDING : Application need more time to respond.
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmNotification (
                                                VAR(uint8,AUTOMATIC) SID,
                                                CONSTP2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) RequestData,
                                                VAR(uint16,AUTOMATIC) RequestLength,
                                                VAR(uint8,AUTOMATIC) RequestType,
                                                VAR(PduIdType,AUTOMATIC) DcmRxPduId,
                                                VAR(uint16,AUTOMATIC) SourceAddress,
                                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                         )
{
	VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
    /* dummy code to remove compiler warning */
    (void)(RequestData);
    (void)(SID);
    (void)(RequestLength);
    (void)(RequestType);
    (void)(DcmRxPduId);
    (void)(SourceAddress);

	/*TESTCODE-START
	retVal = DcmTest_DcmAppl_DcmNotification(SID,RequestData,RequestLength,RequestType,DcmRxPduId,SourceAddress,ErrorCode);
	TESTCODE-END*/

    return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

