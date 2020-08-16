/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Rmba_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)


#if ((DCM_CFG_DSP_READMEMORYBYADDRESS_ENABLED != DCM_CFG_OFF)           ||  \
    (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)    ||  \
    (DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF)           || \
    (DCM_CFG_DSP_TRANSFERDATA_ENABLED!= DCM_CFG_OFF))


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 * @ingroup DCM_TPL
 * DcmAppl_Dcm_ReadMemory:-\n
 * This api will implement Memory read functionality.User Application should add the necessary code to Read the data from the  memory address specified by the tester.\n
 *
 *
 * @param[in]      Rmba_Opstatus : Information on the opstatus\n
 * @param[in]      memoryid  : Identifier of the memory block\n
 * @param[in]      memoryaddress : Starting address of the server memory address from which data is to be read\n
 * @param[in]      datalength    : Number of bytes in memory data\n
 * @param[out]     respbuf   : Data to be read(points to the diagnostic buffer)\n
 * @param[out]     ErrorCode : The negative response code to be updated by the application\n
 *                      In case the Rmba_Opstatus value is passed as DCM_CANCEL, then the ErrorCode parameter shall be a NULL_PTR.
 *
 * @retval                DCM_READ_OK      :   Read was successful
 * @retval                DCM_READ_FAILED  :   Read was not successful
 * @retval                DCM_READ_PENDING :   Read is not yet finished
 * @retval                DCM_READ_FORCE_RCRRP : If the Pending response (0x78) has to be triggered by Dcm immediately.
 */
 FUNC(Dcm_ReturnReadMemoryType,DCM_APPL_CODE) DcmAppl_Dcm_ReadMemory(VAR(Dcm_OpStatusType,  AUTOMATIC) Rmba_Opstatus,
 														VAR(uint8,  AUTOMATIC) memoryid,
 														VAR(uint32,  AUTOMATIC) memoryaddress,
 														VAR(uint32,  AUTOMATIC) datalength,
 														P2VAR (uint8,AUTOMATIC,DCM_INTERN_DATA) respbuf,
 														P2VAR (Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) ErrorCode)
 {
	/* User Application should add the necessary code to Read the data from the memory address specified by the tester */
    VAR(Dcm_ReturnReadMemoryType,AUTOMATIC) retVal = DCM_READ_OK;
	/*TESTCODE-START
	retVal =  DcmTest_DcmAppl_Dcm_ReadMemory(Rmba_Opstatus,memoryid,memoryaddress,datalength,respbuf,ErrorCode);
	TESTCODE-END*/

	return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif
