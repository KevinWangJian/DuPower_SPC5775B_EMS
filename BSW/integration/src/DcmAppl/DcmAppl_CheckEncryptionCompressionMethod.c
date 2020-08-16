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

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&((DCM_CFG_DSP_REQUESTUPLOAD_ENABLED != DCM_CFG_OFF)||(DCM_CFG_DSP_REQUESTDOWNLOAD_ENABLED!= DCM_CFG_OFF)))

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *  @ingroup DCM_TPL
 *  DcmAppl_CheckEncryptionCompressionMethod :-\n
 *  This API provides the compression and encryption method from the tester request to the application
 *
 *  @param[in]       Sid_u8             : SID to differntiate between request upload/download \n
 *  @param[in]       CompressionMethod  : Compression method from the tester \n
 *  @param[in]       EncryptionMethod   : Encryption method from the tester  \n
 *
 *  @retval          E_OK : Processing is successfull
 *  @retval          DCM_E_PENDING : Application needs some more time
 *  @retval          E_NOT_OK :Processing is unsuccessfull
 */
FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_CheckEncryptionCompressionMethod(
                                            VAR(uint8,AUTOMATIC) Sid_u8,
                                            VAR(uint8,AUTOMATIC) CompressionMethod,
                                            VAR(uint8,AUTOMATIC) EncryptionMethod )
{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    retVal_u8 = E_OK;
    /*TESTCODE-START
    retVal_u8 = DcmTest_DcmAppl_CheckEncryptionCompressionMethod(Sid_u8,CompressionMethod,EncryptionMethod);
    TESTCODE-END*/
    (void)Sid_u8;
    (void)CompressionMethod;
    (void)EncryptionMethod;
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
