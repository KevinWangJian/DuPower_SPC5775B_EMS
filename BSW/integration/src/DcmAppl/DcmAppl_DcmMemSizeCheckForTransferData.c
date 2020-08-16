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
 * DcmAppl_DcmMemSizeCheckForTransferData :-\n
 * DCM shall call this callout function to allow application to do checks before calling DcmAppl_Dcm_ReadMemory/DcmAppl_Dcm_WriteMemory to read/write the data in the TransferData service.\n
 * The application can do the below checks and update the ErrorCode parameter accordingly if the checks fail -\n
 * a) The requestSequenceError(NRC 0x24) check for both Uplaod and Download of data in case the data is compressed.\n
 * b) The transferDataSuspended(NRC 0x71)check only for download of data in case the data is compressed.\n
 * c) The transferDataSuspended(NRC 0x71)check only for download of data in case the data is not compressed but the parameter in the configuration DcmDspTransferDataMaxLenChkRequired is set to FALSE.
 *
 * @param[in]            dataCompressionMethod_u8             : Compression Method received in the previous RequestUplaod/RequestDownload request.
 * @param[in]            memoryId                             : The memoryIdentifier of the memory block being read, requested in the RequestUpload service
 * @param[in]            TransferRequestParameterRecordLength : The length of the transferRequestParameterRecord in the request.
 *                                                              Will be passed as 0 in case TransferRequestParameterRecord is not present in the request
 * @param[in]            dataTransferDirection_ten            -: The direction of transfer. Possible values : DCM_UPLOAD, DCM_DOWNLOAD
 *
 * @param[inout]         ErrorCode            : The Errorcode to be updated by the application if there are any error
 *
 * @retval               None
 *
 */
FUNC(void,DCM_APPL_CODE) DcmAppl_DcmMemSizeCheckForTransferData    (
                                                    VAR(uint8,AUTOMATIC) dataCompressionMethod_u8,
                                                    VAR(uint8,AUTOMATIC) dataMemoryId_u8,
                                                    VAR(uint32,AUTOMATIC) dataTransferRequestParameterRecordLength_u32,
                                                    VAR(Dcm_TrasferDirection_en, AUTOMATIC) dataTransferDirection_ten,
                                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataErrorCode_u8
                                                    )
{
    (void)dataCompressionMethod_u8;
    (void)dataMemoryId_u8;
    (void)dataTransferRequestParameterRecordLength_u32;
    (void)dataTransferDirection_ten;
    *dataErrorCode_u8 = 0;
    /*TESTCODE-START
    (void)DcmTest_DcmAppl_DcmMemSizeCheckForTransferData(dataCompressionMethod_u8,
                                                                            dataMemoryId_u8,
                                                                            dataTransferRequestParameterRecordLength_u32,
                                                                            dataTransferDirection_ten,
                                                                            dataErrorCode_u8);
    TESTCODE-END*/
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


