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
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmGetRxPermission:-\n
 *  This API is called by Dcm_StartOfReception before processing the new request. The use case for such an API is rejection/accepting Rx Requests arriving from particular protocols,
 *  for different variants of the same software.Integrator has to add code to check the receiving protocol based on the passed ProtocolId.\n
 *  The user may return E_NOT_OK if the request is to be rejected. Else, E_OK must be returned.It must be noted that all return values other than E_OK (Including DCM_E_PENDING) are treated alike,
 *  and the request will be rejected for all return values other than E_OK.If no info data is given, that the user might get here a NULL pointer.
 *
 * @param[in]     ProtocolId : The protocol id
 * @param[in]     DcmRxPduId : Pdu Id corresponding to the received Pdu
 * @param[in]     TpSduLength : Total message length of the request to be received
 * @param[in]     info : Contains the information about received message
 * @param[out]    None
 * @retval            E_OK      : The Rx Request can be accepted and processed
 * @retval            E_NOT_OK  : The Rx Request is rejected
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetRxPermission (
		VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolId,
		VAR(PduIdType, AUTOMATIC) DcmRxPduId,
		P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
		VAR(PduLengthType, AUTOMATIC) TpSduLength)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	/*User has to add code here to check the receiving protocol based on the passed ProtocolId
	  The user may return E_NOT_OK if the request is to be rejected. Else, E_OK must be returned.
	  It must be noted that all return values other than E_OK (Including DCM_E_PENDING) are treated
	  alike, and the request will be rejected for all return values other than E_OK*/

	/* FC_VariationPoint_START */
	/*  CODE EXAMPLE
		if(ProtocolId == DCM_OBD_ON_CAN)
		{
			return (E_NOT_OK);
		}
		*/
	/* FC_VariationPoint_END */
	/*TESTCODE-START
	retVal = DcmTest_DcmAppl_DcmGetRxPermission(ProtocolId,DcmRxPduId,info,TpSduLength);
	TESTCODE-END*/
		(void)(ProtocolId);
		(void)(DcmRxPduId);
		(void)(TpSduLength);
		(void)(info);
		return (retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
