/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



 #include "DcmDspUds_Rc_Inf.h"
 /*TESTCODE-START
#include "DcmTest.h"
TESTCODE-END*/
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))

 #define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /**
 *  @ingroup DCM_TPL
 *  DcmAppl_DcmCheckRoutineControlOptionRecord:-\n
 *  This API is called by Dcm_DcmRoutineControl(service handler for RC service) incase a received request contains a control option record. \n
 *  The application shall check the validity of the control option record in this function and it shall return E_OK if the record is valid.\n
 *  For an invalid record application shall return E_NOT_OK.
 *
 * @param[in]     nrRID_u16 : This is the routine identifier.
 * @param[in]     dataSubFunc_u8 :This parameter gives the requested subfunction value.(start/stop/RequestResults)
 * @param[in]     adrRoutineCtrlOptRec_pcst : This is a poniter to the control option record received.
 * @param[in]     dataRoutineCtrlOptRecSize_u16 : This parameter gives the length of the control option record.
 * @param[out]    None
 *
 * @retval        E_OK      : Indicates that the request can be accepted and processed\n
 * @retval        E_NOT_OK  : Indicates that the request shall be rejected with NRC 0x31\n
 *
 */
FUNC (Std_ReturnType, DCM_APPL_CODE) DcmAppl_DcmCheckRoutineControlOptionRecord(VAR(uint16,AUTOMATIC) nrRID_u16,
                                           VAR(uint8,AUTOMATIC) dataSubFunc_u8,P2CONST(uint8, AUTOMATIC, DCM_APPL_DATA) adrRoutineCtrlOptRec_pcst,VAR(uint16,AUTOMATIC) dataRoutineCtrlOptRecSize_u16)
{
	VAR(Std_ReturnType,AUTOMATIC) retVal = E_OK;


		(void)(nrRID_u16);
		(void)(adrRoutineCtrlOptRec_pcst);
		(void)(dataRoutineCtrlOptRecSize_u16);
		(void)(dataSubFunc_u8);
		/*TESTCODE-START
		 retVal = DcmTest_DcmAppl_DcmCheckRoutineControlOptionRecord(nrRID_u16,dataSubFunc_u8,adrRoutineCtrlOptRec_pcst,dataRoutineCtrlOptRecSize_u16);
		 TESTCODE-END*/
		return (retVal);
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
