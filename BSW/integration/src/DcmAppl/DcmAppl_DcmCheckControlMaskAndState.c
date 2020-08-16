/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#include "DcmDspUds_Iocbi_Inf.h"
/*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) )

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 * @ingroup DCM_TPL
 * DcmAppl_DcmCheckControlMaskAndState :-\n
 * This api will be invoked from IOCBI service, if the control mask or control status bits are present in the request.\n
 * The application shall return E_OK, if the bits are valid.Nrc 0x31 will be triggered to the tester, if E_OK is not returned from the application
 * @param[in]  nrDID_u16: Currently active DID
 * @param[in]  dataIoParam_u8: Requeste IO parameter value
 * @param[in]  adrCtlStateAndMask_pcst: Control state and control mask bytes received from tester
 * @param[in]  dataCtlStateAndMaskLen_u16: Control state and control mask byte length
 * @retval     E_OK :       if control mask and control status bytes are valid
 * @retval     E_NOT_OK :   if control mask and control status bytes are not valid
 *
 */
FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckControlMaskAndState(VAR(uint16,AUTOMATIC) nrDID_u16, VAR(uint8,AUTOMATIC) dataIoParam_u8,
													P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrCtlStateAndMask_pcst,VAR(uint16,AUTOMATIC) dataCtlStateAndMaskLen_u16
													)
{

	VAR(Std_ReturnType,AUTOMATIC) retVal;
	/*Customer specific code can be added here*/


	/* Sample code for calculation of the size of control mask
	 * Customer can add his own algorithm for calculating the mask
	 */
	VAR(uint16,AUTOMATIC)                       dataControlMaskLen_u16;
	VAR (Dcm_DIDIndexType_tst,DCM_VAR) idxIocbiDidIndexType_st;
	retVal = E_OK;
	(void)nrDID_u16;
	(void)dataIoParam_u8;
	(void)adrCtlStateAndMask_pcst;
	(void)dataCtlStateAndMaskLen_u16;
	if (Dcm_GetIndexOfDID (nrDID_u16,&idxIocbiDidIndexType_st) == E_OK)
	{
		dataControlMaskLen_u16 = (uint16)((uint16)((uint32)(Dcm_DIDConfig[idxIocbiDidIndexType_st.idxIndex_u16].nrSig_u16-1u)/8u)+1u);
	}
	else
	{
		retVal = E_NOT_OK;
	}

	/*TESTCODE-START
	retVal=DcmTest_DcmAppl_DcmCheckControlMaskAndState(nrDID_u16,dataIoParam_u8,adrCtlStateAndMask_pcst,dataCtlStateAndMaskLen_u16);
	TESTCODE-END*/

	return(retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) */

