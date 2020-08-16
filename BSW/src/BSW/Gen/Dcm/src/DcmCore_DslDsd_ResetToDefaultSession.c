

#include "DcmCore_DslDsd_Inf.h"


#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(boolean,DCM_VAR) s_Dcm_ProcessResetToDefault_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
 /*
**********************************************************************************************************************************
*  Dcm_ResetToDefaultSession: The call to this function allows the application to request for the reset of the current session to Default Session.
*  \param
*  \retval 					: E_OK - The request for resetting the session to default session is accepted.The session transition will be processed in the next Dcm main function
*                             E_NOT_OK - If Dcm is not free and processing some other request.The application has to call the service again in this case to Reset the session to Default
*  \seealso
**********************************************************************************************************************************/

FUNC(Std_ReturnType,DCM_CODE) Dcm_ResetToDefaultSession(void)
{
	/* Set the variable to TRUE to process the request in the next Dcm main function to avoid long runtime in an interrupt context */
    
    s_Dcm_ProcessResetToDefault_b = TRUE;
		return (E_OK);
}

/*
***********************************************************************************************************
*  Dcm_DslDsdProcessResetToDefault: The call to this process request to Reset To Default Session (done from
*  Main function context)
*  \param
*  \retval 					: void
*  \seealso
***********************************************************************************************************/

FUNC(void, DCM_CODE) Dcm_DslDsdProcessResetToDefault(void)
{
	/* If the request to reset to default session is already accepted */
    
	if(s_Dcm_ProcessResetToDefault_b !=FALSE)
	{
		/* set the default session and default timing */
		Dcm_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
		#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
		#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
		/* Call SchM_Switch function/DcmAppl_Switch API to inform regarding the jump to default session */
		#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
		(void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
		#endif
		/* Call the DcmAppl API to inform application regarding session change */
		(void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
		#endif
		#endif
		/* Call the API to reset the flag to FALSE to indicate that the session transition to default is complete */
		Dcm_DslDsdResetRTDRequestFlag();
	}
	else
	{
		/* Do nothing */
	}
}

/*
***********************************************************************************************************
*  Dcm_DslDsdResetRTDRequestFlag: The API called to reset the flag indicating a RTD request
*  Main function context)
*  \param
*  \retval 					: void
*  \seealso
***********************************************************************************************************/
FUNC(void, DCM_CODE) Dcm_DslDsdResetRTDRequestFlag(void)
{
	/* Reset the flag to FALSE */
    
    s_Dcm_ProcessResetToDefault_b = FALSE;

}



#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

