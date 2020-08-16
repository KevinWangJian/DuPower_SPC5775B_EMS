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
 * DcmAppl_DcmGetNRCForMinLengthCheck :-\n
 * The API is used by application to get the NRC to be returned as minimum length check has failed for vendor specific service supporting sub function\n
 *
 * @param[in]  dataProtocolId_u8   : Protocol identifier of the protocol on which the request was received
 * @param[in]  dataSid_u8          : Service Identifier of the service in the request
 * @param[out] dataErrorCode_u8    : Pointer to Negative Response Code, OUT Parameter
 *
 * @retval     None
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmGetNRCForMinLengthCheck (
                                    VAR(Dcm_ProtocolType, AUTOMATIC) dataProtocolId_u8,
				    VAR(uint8,AUTOMATIC) dataSid_u8,
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
                                                                )
{
	(void)dataProtocolId_u8;
	(void)dataSid_u8;
	*dataErrorCode_u8 =0x00;

	/*TESTCODE-START
	DcmTest_DcmAppl_DcmGetNRCForMinLengthCheck(dataProtocolId_u8,dataSid_u8,dataErrorCode_u8);
	TESTCODE-END*/

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
