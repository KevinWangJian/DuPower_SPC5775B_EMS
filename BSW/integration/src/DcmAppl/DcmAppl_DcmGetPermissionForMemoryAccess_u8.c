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

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Uds_Prot.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if ((DCM_CFG_DSP_WRITEMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF) || (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)\
		|| (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF))



#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *@ingroup DCM_TPL
 * DcmAppl_DcmGetPermissionForMemoryAccess_u8:-\n
 * This API is used to check the memory read and write access permission
 *
 *  @param[in]      adrMemoryAddress_u32    :   Starting address of the server memory address to be copied
 *  @param[in]      dataDataLength_u32      :   Number of bytes in memory data
 *  @param[in]      dataDirection_en        :   Read/Write Request
 *  @param[out]    None
 *  @retval        E_OK    : access to the address location permitted
 *  @retval        E_NOT_OK    : access to the address location denied
 *
 */
 FUNC(Std_ReturnType,DCM_APPL_CODE) DcmAppl_DcmGetPermissionForMemoryAccess_u8(
																	VAR(uint32,  AUTOMATIC) adrMemoryAddress_u32,
																	VAR(uint32,  AUTOMATIC) dataDataLength_u32,
																	VAR(Dcm_Direction_t,AUTOMATIC) dataDirection_en
																   )
 {
    VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;
	/* User / Application should add the necessary code to check the address location read and write access permissions */
    (void)(adrMemoryAddress_u32);
    (void)(dataDataLength_u32);
    (void)(dataDirection_en);

	/*TESTCODE-START
	retVal =  DcmTest_DcmAppl_DcmGetPermissionForMemoryAccess_u8(adrMemoryAddress_u32,dataDataLength_u32,dataDirection_en);
	TESTCODE-END*/

    return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif

