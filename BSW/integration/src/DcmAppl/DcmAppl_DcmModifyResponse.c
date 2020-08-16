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
 * DcmAppl_DcmModifyResponse :\n
 *  This function is provided to allow the application to conditionally modify the responses from all the services.
 *  a) For negative response, the application can modify only the NRC value.
    b) For positive response, application can add only the additional bytes to the response. But modification of the contents filled by the service is not allowed.
    c) Application is not allowed to transform the positive response to  the negative response and vice versa.\n
    d) If the project does not want the modification of the response, the Appl function need not be modified and can be retained as it is. But the *nrBufSize_pu32 (modified response length)
       has to be made zero explicitly.

 *
 * @param[in]           dataSid_u8       :   Active Service Identifier
 * @param[in]           dataNRC_u8       :   Negative response code to indicate application about the type of response\n
 *                                           i.e. whether the response is positive or negative.
 * @param[in]        adrBufPtr_pu8       :   Buffer provided to application for filling the additional information in case of positive response.\n
 *                                           Buffer provided to application for modifying the NRC value alone in case of negative response.
 * @param[inout]        nrBufSize_pu32   :   [in] Available response buffer length\n
 *                                           [out] Response length filled by application
 *
 * @retval              None
 */
FUNC(void, DCM_APPL_CODE) DcmAppl_DcmModifyResponse (
									VAR(uint8,AUTOMATIC) dataSid_u8,
									VAR(uint8,AUTOMATIC) dataNRC_u8,
									P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) adrBufPtr_pu8,
									P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) nrBufSize_pu32
							   		)
{

    /* In case the application wants to modify the response bytes it should update this variable with the length
     * of bytes added , else response length is zero by default */
    *nrBufSize_pu32 = 0;
	/*TESTCODE-START
	DcmTest_DcmAppl_DcmModifyResponse (dataSid_u8, dataNRC_u8, adrBufPtr_pu8, nrBufSize_pu32);
	TESTCODE-END*/

}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
