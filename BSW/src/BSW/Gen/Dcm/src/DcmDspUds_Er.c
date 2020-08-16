

#include "DcmDspUds_Er_Inf.h"


#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF) )
#include "DcmDspUds_Er_Priv.h"
/* Definition of global variables */
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF))
static VAR(uint8,                 DCM_VAR) Dcm_idxReset_u8;   /* Index variable for looping */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_EcuResetStateType_ten,       DCM_VAR  ) Dcm_stEcuResetState_en; /*State machine control variable for ECU Reset service*/
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8            ,           DCM_VAR  ) Dcm_dataEcuRType_u8;     /* Variable to store the received reset type */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_EcuReset_Ini :
 * This function initialises the ECU Reset service to DCM_ECURESET_IDLE.
 * This function is to be called every time when a new protocol starts.
 *
 * \param           :None
 * \return          :None
 * \retval          :Not Applicable
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsp_EcuReset_Ini (void)
{
    /* Initialise EcuR Service state machine to IDLE state */
    Dcm_stEcuResetState_en = DCM_ECURESET_IDLE;
    /* Initialise the reset mode to DCM_NO_RESET */
    Dcm_dataEcuRType_u8 = DCM_NO_RESET;
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
    /* Reset Boot loader */
    Dcm_ResetBootLoader();
#endif
}

/**
 *******************************************************************************
 * Dcm_Prv_DspEcuResetConfirmation : API used for confirmation of response sent  
 *                                               for ECUReset (0x11) service.
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
FUNC(void, DCM_CODE) Dcm_Prv_DspEcuResetConfirmation(
  VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
  VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
  VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
  VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
        if((status_u8 == DCM_RES_POS_OK)||(status_u8 == DCM_RES_POS_NOT_OK))
        {
			#if(DCM_CFG_APPLTXCONF_REQ != DCM_CFG_OFF)
			/* Give application tx confirmation before the reset happens */
			DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,
			                        dataSourceAddress_u16,status_u8);
			#else
			(void)dataIdContext_u8;
			(void)dataRxPduId_u8;
			(void)dataSourceAddress_u16;
			#endif
			#if(DCM_CFG_RESPOND_REQ_AFTERECURESET == DCM_CFG_OFF)
			/*Update the value of Dcm_acceptRequests_b is to FALSE*/
			Dcm_acceptRequests_b = FALSE;
			#endif
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
			if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)
			{
				Dcm_ResetBootLoader();
			}
#endif
			#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
			(void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
			#endif
			(void)DcmAppl_Switch_DcmExecuteEcuReset(Dcm_dataEcuRType_u8);
			(void)DcmAppl_Switch_DcmExecuteReset();
        }
}


/**
 *****************************************************************************************************
 * Dcm_DcmEcuReset :
 *  EcuReset service interpreter function.
 *  This service is used by client (tester) to do a server reset.
 *  This service has supports the following sub functions - 0x01-0x05
 *
 * \param           pMsgContext    Pointer to message structure
 *                                 (parameter in : RequestLength, Response buffer size, request bytes)
 *                                 (parameter out: Response bytes and Response length )
 *
 * \retval          None
 * \seealso
 *
 *****************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmEcuReset (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType,AUTOMATIC) dataRetVal_u8;
    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;
    /* Initialize the local variables */
    *dataNegRespCode_u8 = 0x00;
    dataRetVal_u8=E_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_EcuReset_Ini();
        /* Set the return value to E_OK (explicitly again) as the Ini function will always be serviced  */
        dataRetVal_u8 = E_OK;
    }
    else
    {
        /* Process the request received, Check for the state machine */
        if(Dcm_stEcuResetState_en == DCM_ECURESET_IDLE)
        {
            /* Store the sub function byte */
            Dcm_dataEcuRType_u8 = pMsgContext->reqData[0];

            /* Check whether the requested reset type is supported */
            for(idxIndex_qu8 = 0; idxIndex_qu8 < DCM_CFG_DSP_NUMRESETTYPE; idxIndex_qu8++)
            {
                if(Dcm_dataEcuRType_u8 == Dcm_DspEcuResetType_cast[idxIndex_qu8].dataResetLevel_u8)
                {
                    break;  /* Reset type  found */
                }
            }
            /* Reset type requested is configured */
            if(idxIndex_qu8 < DCM_CFG_DSP_NUMRESETTYPE)
            {
                if(pMsgContext->reqDataLen == DCM_ECUR_REQ_LEN)
                {
#if((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF) || (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF))
                    /* Store the index of the reset type */
                    Dcm_idxReset_u8 = (uint8)idxIndex_qu8 ;
#endif
                    /* Move the state to to check for permission */
                    Dcm_stEcuResetState_en = DCM_ECURESET_REQPERMISSION;
                }
                else
                {
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                }
            }
            else
            {
                /* Set negative response code */
                *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            }

            if(*dataNegRespCode_u8 != 0x0)
            {
                Dcm_stEcuResetState_en = DCM_ECURESET_ERROR;
                dataRetVal_u8=E_NOT_OK;
            }
        }

        if(Dcm_stEcuResetState_en == DCM_ECURESET_REQPERMISSION)
        {
            /* Call DcmAppl function to prepare the reset */
            dataRetVal_u8 = DcmAppl_DcmEcuResetPreparation(Dcm_dataEcuRType_u8,dataNegRespCode_u8);
            if (E_OK == dataRetVal_u8)
            {
                *dataNegRespCode_u8=0x00;
                /* Do nothing */
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
                /* If Session is mapped to perform Jump to Boot Loader, move the state to prepare for the Jump to Boot */
                if((Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_OEM_BOOT)||
                   (Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_SYS_BOOT)||
                   (Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_DRIVE_TO_DRIVE))
                {
                    Dcm_stEcuResetState_en = DCM_ECURESET_WAIT;
                }
                /* Move the state to send the positive response */
                else
#endif
                {
                   Dcm_stEcuResetState_en = DCM_ECURESET_SENDRESPONSE;
                }
            }
            else if(dataRetVal_u8 == DCM_E_PENDING)
            {
                *dataNegRespCode_u8=0x00;
                /* Do nothing */
            }
            else
            {
                if(*dataNegRespCode_u8 == 0x00)
                {
                    /* Set negative response code */
                    *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
                }
                Dcm_stEcuResetState_en = DCM_ECURESET_ERROR;
                dataRetVal_u8=E_NOT_OK;
            }
        }
#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
        if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)
        {
            if(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_OEM_BOOT )
            {   /* Call the API to perform Jump to Boot Loader */
                Dcm_JumpToBootLoader(DCM_JUMPTOOEMBOOTLOADER,dataNegRespCode_u8);
            }
            else if(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].resetForBoot == DCM_RESET_SYS_BOOT)
            {   /* Call the API to perform Jump to Boot Loader */
                Dcm_JumpToBootLoader(DCM_JUMPTOSYSSUPPLIERBOOTLOADER,dataNegRespCode_u8);
            }
            else
            {   /* Call the API to perform Jump to Boot Loader */
                Dcm_JumpToBootLoader(DCM_JUMPDRIVETODRIVE,dataNegRespCode_u8);
            }
        }
#endif
        /* State for transmitting postive response ( normal reset case and warm init case )*/
        if(Dcm_stEcuResetState_en == DCM_ECURESET_SENDRESPONSE)
        {
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            /* Call SchM_Switch function */
            if((Dcm_dataEcuRType_u8 != DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET) &&
               (Dcm_dataEcuRType_u8 != DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET))
            {
                (void)SchM_Switch_Dcm_DcmEcuReset(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].dataResetMode_u8);
            }
#if (DCM_CFG_RAPIDPOWERSHUTDOWNRESET!=DCM_CFG_OFF)
            else
            {
                (void)SchM_Switch_Dcm_DcmModeRapidPowerShutDown(Dcm_DspEcuResetType_cast[Dcm_idxReset_u8].dataResetMode_u8);
            }
#endif
#endif
            /* Call the DcmAppl API to inform regarding the reset */
            DcmAppl_Switch_DcmEcuReset(Dcm_dataEcuRType_u8);
            /* Fill the response buffer with the subfunction */
            pMsgContext->resData[0] = Dcm_dataEcuRType_u8;

            /* Fill the response length as 0x01 if reset type is not enableRapidPowerShutDown */
            if(Dcm_dataEcuRType_u8 != DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET)
            {
                pMsgContext->resDataLen = 1;
            }
            else
            {
                /* Fill the power down time if reset type is enableRapidPowerShutDown  */
                pMsgContext->resData[1] = DCM_CFG_DSP_POWER_DOWN_TIME;
                /* Fill the response length 0x02 if reset type is enableRapidPowerShutDown(0x04)  */
                pMsgContext->resDataLen = 2;
            }

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            /* To remove Misra warning */
            (void)Dcm_idxReset_u8;
#endif
            /* Bring the state to IDLE */
            Dcm_stEcuResetState_en = DCM_ECURESET_IDLE;
            dataRetVal_u8=E_OK;
        }
        /* Request length error or reset cannot be realized */
        if(Dcm_stEcuResetState_en == DCM_ECURESET_ERROR)
        {
            if(*dataNegRespCode_u8==0x00)
            {
                *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
            }

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            /* To remove Misra warning */
            (void)Dcm_idxReset_u8;
#endif
            /* Bring the state to IDLE */
            Dcm_stEcuResetState_en = DCM_ECURESET_IDLE;
            dataRetVal_u8=E_NOT_OK;
        }
    }
    return dataRetVal_u8;
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /*(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && ((DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)*/
