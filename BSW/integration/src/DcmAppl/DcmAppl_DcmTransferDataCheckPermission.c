/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_TransferData_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/


#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_Dcm_CheckPermissionForTransferData :-\n
 * DCM shall call this callout function to allow application to do checks before calling DcmAppl_Dcm_ReadMemory/DcmAppl_Dcm_WriteMemory to read/write the data in the TransferData service.\n
 * The application can do the below checks and update the ErrorCode parameter accordingly if the checks fail -\n
 * a) If the length of TransferRequestParameterRecord is correct and contents of TransferRequestParameterRecord are valid\n
 * b) If data is correctly altered\n
 * c) Voltage conditions are ok\n
 * d) Manufacturer/Supplier Specific Check\n
 *
 * Dcm shall return NRC 0x22 in case error code is not updated by application , but the return type is E_NOT_OK.
 *
 * @param[in]            BlockSequenceCounter : The received block sequence counter from the tester request
 * @param[in]            memoryId             : The memoryIdentifier of the memory block being read, requested in the RequestUpload service
 * @param[in]            memoryAddress        : The memory address from where the data is read in this TransferData request
 * @param[inout]         memorySize           : The  memory size requested to be transfered in this TransferData request.
 *                                              The application can modify this value in case if RequestUpload is active.
 *
 * @param[in]            TransferRequestParameterRecord : Pointer to buffer with TransferRequestParameterRecord present in the request.\n
 *                                                         Will be passed as NULL_PTR in case no data is present in the request(Applicable if the previous request is RequestUpload)
 *
 * @param[in]            TransferRequestParameterRecordLength : The length of the transferRequestParameterRecord in the request.\n
 *                                                               Will be passed as 0 in case TransferRequestParameterRecord is not present in the request
 *
 * @param[inout]         ErrorCode            : The Errorcode to be updated by the application if there are any error
 *
 * @retval   E_OK          : If all permission checks are successful
 * @retval   DCM_E_PENDING : If more time is needed to complete the operation
 * @retval   E_NOT_OK      : If permission checks are not successful
 *
 *
 *
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_CheckPermissionForTransferData(
                                                    VAR(uint8,AUTOMATIC) BlockSequenceCounter,
                                                    VAR(uint8,AUTOMATIC) memoryId,
                                                    VAR(uint32,AUTOMATIC) memoryAddress,
                                                    P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) memorySize,
                                                    P2VAR(uint8,AUTOMATIC,DCM_INTERN_DATA) TransferRequestParameterRecord,
                                                    VAR(uint32,AUTOMATIC) TransferRequestParameterRecordLength,
                                                    VAR(Dcm_TrasferDirection_en,AUTOMATIC) dataTransferDirection_ten,
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode
                                                    )
{
    VAR(uint8,AUTOMATIC) dataReturnValue_u8;
    dataReturnValue_u8 = E_OK;
    (void)BlockSequenceCounter;
    (void)memoryId;
    (void)memoryAddress;
    (void)memorySize;
    (void)TransferRequestParameterRecord;
    (void)TransferRequestParameterRecordLength;
    (void)dataTransferDirection_ten;
    (void)ErrorCode;
    /*TESTCODE-START
    dataReturnValue_u8 = DcmTest_DcmAppl_Dcm_CheckPermissionForTransferData(BlockSequenceCounter,
                                                                            memoryId,
                                                                            memoryAddress,
                                                                            memorySize,
                                                                            TransferRequestParameterRecord,
                                                                            TransferRequestParameterRecordLength,
                                                                            ErrorCode);
    TESTCODE-END*/
    return dataReturnValue_u8;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


