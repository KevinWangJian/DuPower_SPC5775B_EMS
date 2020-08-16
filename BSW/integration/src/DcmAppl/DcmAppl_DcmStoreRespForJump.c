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

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)



 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmStoreRespForJump :-\n
 * This API is invoked for Storing of Response information when user specific service is used for Jumping to Boot.\n
 * This API should fill in SID|0x40 and response bytes for response. Dcm will only pass the structure
 * for the user to update. It is the responsibility of the user to fill in the correct data.\n
 *     1. Fill ProgConditions->SubFncId     with Subfunc\n
 *     2. Fill ProgConditions->SID          with SID\n
 *     3. Fill ProgConditions.ReqResBuf[0]  with response bytes\n
 *     4. Fill ProgConditions->ReqResLen    with response length\n
 *
 *  Ex:  Response-> Fill SID|0x40, Subfunc, Request Bytes if any\n
 * Response Len needs to be filled. Response length also includes SID and Subfunc.\n
 * If the service has only SID then Response length is 1 byte.\n
 * If the service has only response SID and subfunction in response then Response length is 2 bytes etc.\n
 *
 * Note: This API will be called for every Jump To Boot transition. User needs to modify this API
 * only if User specific service is used for Jump to Boot.\n
 *
 * @param[inout]         ProgConditions : structure for the user to update.
 * @retval               None
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmStoreRespForJump
                                   (P2VAR(Dcm_ProgConditionsType,AUTOMATIC,DCM_INTERN_DATA) ProgConditions)
{

	/* Necessary code needs to be added here to store the information
	   1. Fill ProgConditions->SubFncId with Subfunc
	   2. ProgConditions->SID with SID
	   3. Dcm_ProgConditions_st.ReqResBuf[0] for response bytes
	   4. update response length ProgConditions->ReqResLen */


    (void)ProgConditions;
    /*TESTCODE-START
    DcmTest_DcmAppl_DcmStoreRespForJump(ProgConditions);
    TESTCODE-END*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif

