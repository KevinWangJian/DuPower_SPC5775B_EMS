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

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_Dcm_ProcessRequestUpload :-\n
 *  This function provides the compression and encryption method from the tester request to the application. The application can also
 *  do teh checks like ConditionCheck/uploadFaultCondition check/Manufacturer/Supplier check in the same function according to the ISO sequence
 *  The application should in this case update the error code accordingly in case the checks fail.
 *
 *  @param[in]       OpStatus            :  Opstatus passed  \n
 *  @param[in]       DataFormatIdentifier:  DataFormatIdentifier from the tester request. Will contain encryption and compression method  \n
 *  @param[in]       MemoryAddress       :  MemoryAddress from the tester request  \n
 *  @param[in]       MemorySize          :  MemorySize to be uploaded from the tester request  \n
 *  @param[out]      BlockLength         :  Length of each TransferData request including response SID and sequence number   \n
 *  @param[out]      ErrorCode           :  Used to update negative response code in case of errors   \n
 *
 *  @retval          E_OK : All the condition checks are successfull
 *  @retval          E_PENDING : Application needs more time to do the functionality
 *  @retval          E_NOT_OK : The condition checks are unsuccessfull
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_Dcm_ProcessRequestUpload(
                                            VAR(Dcm_OpStatusType,AUTOMATIC) OpStatus,
                                            VAR(uint8,AUTOMATIC) DataFormatIdentifier,
                                            VAR(uint32,AUTOMATIC) MemoryAddress,
                                            VAR(uint32,AUTOMATIC) MemorySize,
                                            P2VAR(uint32,DCM_INTERN_DATA,AUTOMATIC) BlockLength,
                                            P2VAR(Dcm_NegativeResponseCodeType,DCM_INTERN_DATA,AUTOMATIC) ErrorCode)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8 = E_OK;
    /*TESTCODE-START
    retVal_u8 = DcmTest_DcmAppl_Dcm_ProcessRequestUpload(OpStatus,DataFormatIdentifier,MemoryAddress,MemorySize,BlockLength,ErrorCode);
    TESTCODE-END*/
    (void)OpStatus;
    (void)DataFormatIdentifier;
    (void)MemoryAddress;
    (void)MemorySize;
    (void)BlockLength;
    (void)ErrorCode;
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
