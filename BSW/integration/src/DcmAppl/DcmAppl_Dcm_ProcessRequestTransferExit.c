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

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTTRANSFEREXIT_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_Dcm_ProcessRequestTransferExit :-\n
 *  This API is to terminate a download or upload process. This callout is needed for the implementation of UDS service RequestTransferExit.
 *
 *  @param[in]       OpStatus                           : Opstatus passed  \n
 *  @param[in]       transferRequestParameterRecord     : TransferRequestParameterRecord from the request  \n
 *  @param[in]       transferRequestParameterRecordSize : Size of transferRequestParameterRecord in the request  \n
 *  @param[out]      transferResponseParameterRecord    : TransferResponsetParameterRecord from the request  \n
 *  @param[out]      transferResponseParameterRecordSize : Size of transferResponseParameterRecord in the request  \n
 *  @param[out]      ErrorCode            : Used to update negative response code in case of errors   \n
 *
 *  @retval          E_OK : If the upload process is successfully terminated \n
 *  @retval          E_NOT_OK : If upload process is not terminated successfully\n
 *  @retval          DCM_E_PENDING : If the termination process needs more time\n
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestTransferExit(
                                                                VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                                                P2CONST(uint8,DCM_INTERN_DATA,AUTOMATIC) transferRequestParameterRecord,
                                                                VAR(uint32,AUTOMATIC) transferRequestParameterRecordSize,
                                                                P2VAR(uint8,DCM_INTERN_DATA,AUTOMATIC) transferResponseParameterRecord,
                                                                P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) transferResponseParameterRecordSize,
                                                                P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode)

{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8 = E_OK;
    /*TESTCODE-START
    retVal_u8 = DcmTest_DcmAppl_Dcm_ProcessRequestTransferExit(OpStatus,transferRequestParameterRecord,transferRequestParameterRecordSize,transferResponseParameterRecord,transferResponseParameterRecordSize,ErrorCode);
    TESTCODE-END*/
    (void)OpStatus;
    (void)transferRequestParameterRecord;
    (void)transferRequestParameterRecordSize;
    (void)transferResponseParameterRecord;
    (void)transferResponseParameterRecordSize;
    (void)ErrorCode;
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
