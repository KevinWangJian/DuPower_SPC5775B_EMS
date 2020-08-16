

#include "DcmDspUds_Dsc_Inf.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
#include "DcmDspUds_Dsc_Priv.h"
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_DscStateType_ten,DCM_VAR) Dcm_stDsc_en;           /* State of DSC state machine                     */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,           DCM_VAR) Dcm_ctDiaSess_u8;      /* Index for the current session in session table */
VAR(uint8,           DCM_VAR) Dcm_ReqSess_u8;        /* Requested session in the tester request        */

static VAR(Dcm_SesCtrlType,DCM_VAR) s_stDspDscActiveSession_u8; /* Static variable to store the active session    */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_DscIni : Initialization function for DSC Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_Dsp_DscIni(void)
{
    /* Set DSC state machine to DCM_DSP_DSC_INIT */
    Dcm_stDsc_en = DCM_DSP_DSC_INIT;
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
    /* Reset Boot loader */
    Dcm_ResetBootLoader();
#endif
}

/**
 **************************************************************************************************
 * Dcm_DcmDiagnosticSessionControl :
 *  The DiagnosticSessionControl service is used to enable different diagnostic sessions in the server.
 *  A diagnostic session enables a specific set of diagnostic services and/or functionality in the server.
 *  Function is called by DSD, when DiagnosticSessionControl service is recognised (SID set to 0x10),
 *  this service provided in DSP module and configured in DCM identifier table.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmDiagnosticSessionControl (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
    VAR(uint16,AUTOMATIC) dataTimingValue_u16;                   /* Variable to store the P2 Timer values */
#endif
    VAR(uint8_least,                 AUTOMATIC) idxLoop_qu8;         /* Index variable for looping */
    VAR(Std_ReturnType,              AUTOMATIC) dataRetVal_u8;           /* Variable to store the return value of API */
    /* Initialization of local variables */
    *dataNegRespCode_u8 = 0x00;
    dataRetVal_u8 = E_NOT_OK;

    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    if(OpStatus == DCM_CANCEL)
    {
        Dcm_Dsp_DscIni();
        dataRetVal_u8 = E_OK;
    }
    else
    {
        /* Default state of DSC */
        if (Dcm_stDsc_en == DCM_DSP_DSC_INIT)
        {
            /* Copy the requested session level in variable */
            Dcm_ReqSess_u8 = pMsgContext->reqData[DCM_DSP_DSC_POSITION_SUBFUNC];

            /* Check whether the requested session is supported */
            for(idxLoop_qu8 = 0; idxLoop_qu8 < DCM_CFG_DSP_NUMSESSIONS; idxLoop_qu8++)
            {
                if(Dcm_ReqSess_u8 == Dcm_Dsp_Session[idxLoop_qu8].session_level)
                {
                    break;  /* Session found */
                }
            }
            /* If session requested is configured */
            if(idxLoop_qu8 < DCM_CFG_DSP_NUMSESSIONS)
            {
                /* Check for the exact request length */
                if(pMsgContext->reqDataLen == DCM_DSP_DSC_REQ_LEN)
                {
                    /* Get the currently active session in the server */
                    dataRetVal_u8 = Dcm_GetSesCtrlType(&s_stDspDscActiveSession_u8);

                    /* If the active session is read without errors */
                    if(dataRetVal_u8 == E_OK)
                    {
                        /* Store the index in global variable */
                        Dcm_ctDiaSess_u8 = (uint8)idxLoop_qu8;

                        /* Set the DSC state machine to check for permissions for session transition */
                        Dcm_stDsc_en     = DCM_DSP_DSC_CHECK_PERMISSION;

                    }
                    else
                    {
                        /* If current active session was not read correctly  */
                        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
                }
                /* Request length is incorrect */
                else
                {
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
            }
            else
            {
                /* Invalid session */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
                /* Report development error "DCM_E_SESSION_NOT_CONFIGURED " to DET module if the DET module is enabled */
                DCM_DET_ERROR(DCM_DSC_ID , DCM_E_SESSION_NOT_CONFIGURED )
            }

            /* if negative response code is set , move the state to send the NRC to the tester */
            if(*dataNegRespCode_u8 != 0x0)
            {
                Dcm_stDsc_en     = DCM_DSP_DSC_ERROR;
            }
        }

        /* If the state is set to check for the permissions for session transition */
        if(Dcm_stDsc_en == DCM_DSP_DSC_CHECK_PERMISSION)
        {
            /* Call the Application function to check if session can be activated */
            dataRetVal_u8 = DcmAppl_DcmGetSesChgPermission(s_stDspDscActiveSession_u8,
                    Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level,
                    dataNegRespCode_u8);

            /* Processing is finished */
            if(dataRetVal_u8 == E_OK)
            {
                *dataNegRespCode_u8=0x00;
    #if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
                /* If Session is mapped to perform Jump to Boot Loader, move the state to prepare for the Jump to Boot */
                if((Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_OEM_BOOT)||
                        (Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_SYS_BOOT))
                {
                    Dcm_stDsc_en = DCM_DSP_DSC_WAIT;
                }
                /* Move the state to send the positive response */
                else
    #endif
                {
                    Dcm_stDsc_en = DCM_DSP_DSC_SEND_RESP;
                }
            }
            /* If the port needs more time to get the permission */
            else if(dataRetVal_u8 == DCM_E_PENDING)
            {
                *dataNegRespCode_u8=0x00;
                /* The application will be called again in the next cycle */
            }
            /* For any other return types */
            else
            {   /* Set negative response code */
                if(*dataNegRespCode_u8 == 0)
                {
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
            /* If NRC is set */
            if(*dataNegRespCode_u8 != 0x0)
            {
                Dcm_stDsc_en     = DCM_DSP_DSC_ERROR;
            }
        }

        if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
        {
    #if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
            if(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_OEM_BOOT )
            {   /* Call the API to perform Jump to Boot Loader */
                Dcm_JumpToBootLoader(DCM_JUMPTOOEMBOOTLOADER,dataNegRespCode_u8);
            }
            if(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].sessionForBoot == DCM_SYS_BOOT)
            {   /* Call the API to perform Jump to Boot Loader */
                Dcm_JumpToBootLoader(DCM_JUMPTOSYSSUPPLIERBOOTLOADER,dataNegRespCode_u8);
            }
    #endif
            dataRetVal_u8 = DCM_E_PENDING;
        }

        /* State to send positive response */
        if(Dcm_stDsc_en == DCM_DSP_DSC_SEND_RESP)
        {
            /* Update response data length */
            pMsgContext->resDataLen = DCM_DSP_DSC_RESP_LEN;
            /* Fill the requested diagnostic session in response buffer */
            pMsgContext->resData[0] = Dcm_ReqSess_u8;

    #if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
            /* Convert P2Max in microseconds seconds to milliseconds by dividing the value by 1000 */
            dataTimingValue_u16         = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32 / 1000u);
            pMsgContext->resData[1] = (uint8)(dataTimingValue_u16 >> 8u);
            pMsgContext->resData[2] = (uint8)(dataTimingValue_u16 & 0x00ffu);
            /* Convert P2StrMax in microseconds to 10 milliseconds resolution by dividing the value by 10000 */
            dataTimingValue_u16         = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32/10000u);
            pMsgContext->resData[3] = (uint8)(dataTimingValue_u16 >> 8u);
            pMsgContext->resData[4] = (uint8)(dataTimingValue_u16 & 0x00ffu);
    #endif
            dataRetVal_u8 = E_OK;
        }

        /* State to send negative response */
        if(Dcm_stDsc_en == DCM_DSP_DSC_ERROR)
        {
            /* If negative response code is not set, send NRC 0x22 */
            if(*dataNegRespCode_u8==0x00)
            {
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
            /* Reset the DSC state machine */
            Dcm_stDsc_en = DCM_DSP_DSC_INIT;
            dataRetVal_u8 = E_NOT_OK;
        }
    }
    return dataRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_Dsp_DscChgSession : This function performs the following
 *                     1. Check for Session transitions default - Non default etc
 *                     2. Updating the Session Timers
 *                     3. Activate New Session using Dcm_SetSessCtrlType.
 *                     4. Change the state of DSC state machine to DCM_DSP_DSC_INIT.
 *
 * \param           status    Status of Tx confirmation function
 *
 *
 * \dataRetVal_u8          None
 * \seealso
 *
 **************************************************************************************************
 */

static FUNC(void,DCM_CODE) Dcm_Dsp_DscChgSession(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status)
{
    VAR(uint8,AUTOMATIC) dataReqSess_u8;  /* Variable to store the requested session */

    if ( (status == DCM_RES_POS_OK) || (status == DCM_RES_POS_NOT_OK) )
    {
        /* The requested session is activated for positive as well as negative confirmations of a positive response.
       This is to avoid a situation of instability if the Application has already prepared for a change in security,
       but the Tx confirmation of positive response to tester is negative*/
        if(Dcm_stDsc_en == DCM_DSP_DSC_SEND_RESP)
        {
            /* Store the requested session from array index Dcm_ctDiaSess_u8 */
            dataReqSess_u8  = Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level;

            /* Update the P2 Timer values */
            Dcm_DsldSetsessionTiming(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32,
                    Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32);

            /* Activate New Session requested */
            Dcm_SetSesCtrlType(dataReqSess_u8);
        }
    }
    /* Call the initialization function of DSC service to reset the DSC state */
    Dcm_Dsp_DscIni();
    return;
}

/**
 **************************************************************************************************
 * Dcm_GetP2Timings :
 *  This API is used to get the timings of a particular session. This API is used in jump to boot
 *  feature implementation to retrieve the same session timings.
 *
 * \param           dP2Timing_pu32: Pointer to P2max timings of the session requested
 * \param           dP2StarTiming_pu32: Pointer to P2Starmax timings of the session requested
 * \param           dSessionId_u8: Session Id for which timings have to be retrieved
 *
 * \dataRetVal_u8          None
 * \seealso
 *
 **************************************************************************************************
 */
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
FUNC(void, DCM_CODE) Dcm_GetP2Timings(
        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2Timing_pu32,
        P2VAR(uint32,AUTOMATIC,DCM_INTERN_DATA) dP2StarTiming_pu32,
        VAR(Dcm_SesCtrlType, AUTOMATIC) dSessionId
)
{
    VAR(uint8_least,AUTOMATIC)  idxSessionId_qu8;
    /* Find the matching session ID */
    for(idxSessionId_qu8 = 0; idxSessionId_qu8 < DCM_CFG_DSP_NUMSESSIONS; idxSessionId_qu8++)
    {
        if (dSessionId == Dcm_Dsp_Session[idxSessionId_qu8].session_level)
        {
            /* Matching session ID found, get the timing values */
            SchM_Enter_Dcm_DsldTimer_NoNest();
            *dP2Timing_pu32 = Dcm_Dsp_Session[idxSessionId_qu8].P2_max_u32;
            *dP2StarTiming_pu32 = Dcm_Dsp_Session[idxSessionId_qu8].P2str_max_u32;
            SchM_Exit_Dcm_DsldTimer_NoNest();
            /* Break the search for session ID as it is already found */
            break;
        }
        else
        {
            /*do nothing*/
        }
    }
    if(idxSessionId_qu8 == DCM_CFG_DSP_NUMSESSIONS)
    {
        /* This session is not matching */
        /* Report development error "DCM_E_SESSION_NOT_CONFIGURED " to DET module if the DET module is enabled */
        DCM_DET_ERROR(DCM_GETP2TIMINGS_ID , DCM_E_SESSION_NOT_CONFIGURED )
    }

    return;
}
#endif

/**
 *******************************************************************************
 * Dcm_Prv_DspDscConfirmation : API used for confirmation of response sent for 
 *                                      DiagnosticSessionControl (0x10) service.
 * \param           dataIdContext_u8    Service Id 
 * \param           dataRxPduId_u8      PDU Id on which request is Received
 * \param           dataSourceAddress_u16    Tester Source address id
 * \param           status_u8                Status of Tx confirmation function
 *
 * \retval          None
 * \seealso
 *
 *******************************************************************************
 */

FUNC(void, DCM_CODE) Dcm_Prv_DspDscConfirmation(
	VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
	VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
	VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
	if ( (status_u8 == DCM_RES_POS_OK) || (status_u8 == DCM_RES_POS_NOT_OK) )
	{
		#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
		(void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(Dcm_Dsp_Session
												[Dcm_ctDiaSess_u8].SessionMode);
		#endif
		(void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_Dsp_Session
											[Dcm_ctDiaSess_u8].session_level);
		#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
		if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)
		{   /* Perform reset by calling the SchM/DcmAppl API */
			#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
			(void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
			#endif
			(void)DcmAppl_Switch_DcmExecuteDscReset(Dcm_Dsp_Session
											[Dcm_ctDiaSess_u8].session_level);
			(void)DcmAppl_Switch_DcmExecuteReset();
			/*Update the accept request flag to false to block all the requests
					until the boot reset is carried out*/
				Dcm_acceptRequests_b = FALSE;
		}
		#endif
	}
	/* Call DSC function to change session */
	Dcm_Dsp_DscChgSession(status_u8);
	/*Session change occurred,reset the ROE events*/
    #if DCM_ROE_ENABLED != DCM_CFG_OFF
     Dcm_ResetROEEvents();
    #endif

DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,
																	status_u8);   
}


#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

