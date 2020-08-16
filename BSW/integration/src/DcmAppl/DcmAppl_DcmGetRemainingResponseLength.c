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
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmGetRemainingResponseLength :-\n
 * This API shall be effective only for the KWP2000 services and when the splitting responses feature is enabled in the configuration by enabling the container DcmDslKWPSplitResponseFeatureRB.\n
 * This API shall be called by Dcm_TpTxConfirmation function in case the confirmation given from the lower layer is positive, to check if there are any more responses to be sent.\n
 * In case, there are any non zero length of response to be transmitted, then the service has to be called again in the next main cycle.
 * The same continues until this Application interface returns 0 length.\n
 * This API shall be called only from the Tx confirmation of the final response (not 0x78).
 * In case, the Tx confirmation is negative, then the API DcmAppl_DcmGetRemainingResponseLength shall not be called.
 * Also, if previously sent response (not 0x78), results in negative Tx confir-mation, then the further transmission if any shall be aborted.


 * @param[in]  dataSID_u8    : Service ID of the KWP service under process
 * @param[out] dataResponseLength  : The length of the next response to be transmitted.
 *
 * @retval     None
 *
 */
FUNC(void, DCM_APPL_CODE) DcmAppl_DcmGetRemainingResponseLength(
                                        VAR(uint8, AUTOMATIC) dataSID_u8,
                                        P2VAR(PduLengthType,AUTOMATIC,DCM_INTERN_DATA) dataResponseLength
                                        )
{

	(void)dataSID_u8;
	*dataResponseLength = 0;
	/*TESTCODE-START
	   if(dataSID_u8 == 0xA8)
         {
            DcmTest_DcmAppl_DcmGetRemainingResponseLength(dataResponseLength);
         }
       else
        {
            *dataResponseLength = 0;
        }

	TESTCODE-END*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif /* #if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF)) */
