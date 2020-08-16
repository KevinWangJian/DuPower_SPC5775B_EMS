

#include "DcmDspUds_Uds_Inf.h"

#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )

#define DCM_DSP_CC_COMMTYPEMSK  0x0Fu        /* Mask to remove the higher nibble in Communication type */
#define DCM_DSP_CC_REQLEN       0x02u        /* Request length of Communication control service */
#define DCM_DSP_CC_RESLEN       0x01u        /* Response length of Communication control service */
#define DCM_DSP_CC_POSCTRLTYPE  0x00u        /*Index to get the sub-function from the request */
#define DCM_DSP_CC_POSCOMMTYPE  0x01u        /*Index to get the Communication type from the request */
#define DCM_DSP_CC_SUBNETMASK   0xF0u        /* Mask to remove the lower nibble in Communication Type */
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#define DCM_SUBNET_DISEN_SPECIFIED_COMTYPE 0x0 /* */
#define DCM_SUBNET_DISEN_REQUEST_RECIEVED_NODE 0xF/* */

#include "Dcm_Cfg_MemMap.h"

static VAR(Dcm_CCStateType_ten,DCM_VAR) Dcm_stCC_en;           /* State of CC state machine                     */
/* Variable to store the communication mode */
static VAR(Dcm_CommunicationModeType,DCM_VAR) Dcm_stCommunicationMode_u8 ;
/* Variable to store the index to ComM structure within Dcm */
static VAR(uint8,DCM_VAR) Dcm_idxCommChannel_u8 ;
/* Variable to store the current state of the Communication control state machine */
static VAR(NetworkHandleType,AUTOMATIC) Dcm_nrSubNet_u8;      /* Static variable to store the subnet number */
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
FUNC(void,DCM_CODE) Dcm_Dsp_CCIni(void)
{
    /* Set CC state machine to DCM_DSP_CC_INIT */
    Dcm_stCC_en = DCM_DSP_CC_INITIAL;

}
/**
 ***********************************************************************************************************
 *  Dcm_GetCommModeType_u8 :The function is used to derive the communication mode from the sub-function
 *  byte and the communication type (both from tester request)
 *
 *  The array adrComModeIndex_au8 gives the starting index to the array CommModeType for each of the valid
 *  communication type.The first element of adrComModeIndex_au8 is not valid . The second element
 *  gives the starting index to the array CommModeType corresponding to CommunicationType 0x01 (Normal
 *  Communication)and so on.The third element gives the starting index corresponding to 0x02(NM communication)
 *  and so on.The index obtained thus from the communication type (parameter of the function) is added
 *  with the control type(parameter of the function) to get the index of the CommunicationModeType from the
 *  array CommModeType corresponding to the control type and communication type passed to the function and this
 *  is returned back
 *
 *
 * \param           dataCommType_u8  : Communication type from the tester request
 *                  ControlType_u8 : COntrol type from tester request
 *
 * \retval          Dcm_CommunicationModeType
 * \seealso
 *
 ***********************************************************************************************************
 */
static FUNC(Dcm_CommunicationModeType,DCM_CODE) Dcm_Prv_GetCommModeType_u8(VAR(uint8,AUTOMATIC) ControlType_u8,
        VAR(uint8,AUTOMATIC) dataCommType_u8 )
{
    /* Array with index to the CommunicationModeType array for each communication type */
    VAR(uint8,AUTOMATIC) adrComModeIndex_au8[4]={0,0,4,8};

    /* Array of communication mode types */
    VAR(Dcm_CommunicationModeType,AUTOMATIC) CommModeType[12] =
    {
            DCM_ENABLE_RX_TX_NORM,
            DCM_ENABLE_RX_DISABLE_TX_NORM,
            DCM_DISABLE_RX_ENABLE_TX_NORM,
            DCM_DISABLE_RX_TX_NORMAL,
            DCM_ENABLE_RX_TX_NM,
            DCM_ENABLE_RX_DISABLE_TX_NM,
            DCM_DISABLE_RX_ENABLE_TX_NM,
            DCM_DISABLE_RX_TX_NM,
            DCM_ENABLE_RX_TX_NORM_NM,
            DCM_ENABLE_RX_DISABLE_TX_NORM_NM,
            DCM_DISABLE_RX_ENABLE_TX_NORM_NM,
            DCM_DISABLE_RX_TX_NORM_NM
    };

    /* Return the CommunicationModeType corresponding to the control type and the communication type */
    return(CommModeType[adrComModeIndex_au8[dataCommType_u8]+ControlType_u8]);

}

/**
 **************************************************************************************************
 *  Dcm_Dsp_ChkCommunicationModeEntry :The function is used to check if the mode entry notification is for
 *  the requested mode or not
 *
 * \param           CommunicationMode_Cbk_u8  : Mode for which the notification was received
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

#if ( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
static FUNC(uint8,DCM_CODE) Dcm_Prv_DspChkSubnetID_u8(VAR(NetworkHandleType,AUTOMATIC) dataSubnetID_u8,
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint8,AUTOMATIC) idxIndex_u8;
    VAR(uint8,AUTOMATIC) dataReturnVal_u8;

    for(idxIndex_u8 =0;idxIndex_u8<DCM_CFG_NUM_SPECIFIC_SUBNETS;idxIndex_u8++)
    {
        if(Dcm_specific_subnet_table[idxIndex_u8].SpecificSubNetId_u8 == dataSubnetID_u8)
        {
            break;
        }
    }
    if (idxIndex_u8 < DCM_CFG_NUM_SPECIFIC_SUBNETS)
    {
        dataReturnVal_u8 = idxIndex_u8;
    }
    else
    {
        dataReturnVal_u8 = DCM_CFG_NUM_SPECIFIC_SUBNETS;
        /*Set Negative response code */
        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
        /* Report development error "DCM_E_SUBNET_NOT_SUPPORTED " to DET module if the DET module is enabled */
        DCM_DET_ERROR(DCM_CC_ID , DCM_E_SUBNET_NOT_SUPPORTED )
        Dcm_stCC_en = DCM_DSP_CC_ERROR;
    }
    return(dataReturnVal_u8);
}

#endif

/**
 **************************************************************************************************
 *  Dcm_Prv_CC_Check :This function will check whether communication channel
 *
 *  \param[in]       pMsgContext  Pointer to message structure
 *  \param[out]      dataNegRespCode_u8  :   pointer to update the negative response code
 *  \retval          None
 *  \seealso
 *
 **************************************************************************************************
 */

static FUNC(void,DCM_CODE) Dcm_Prv_CC_Check(P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint8,AUTOMATIC) dataCommType_u8;    /* Local variable to get lower nibble of Communication Type */
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

    if (pMsgContext->reqDataLen== DCM_DSP_CC_REQLEN)
    {
        dataCommType_u8 = (pMsgContext->reqData[DCM_DSP_CC_POSCOMMTYPE] & DCM_DSP_CC_COMMTYPEMSK);
        if((dataCommType_u8 > 0x0) && (dataCommType_u8 < 0x4))
        {
            retVal_u8 = DcmAppl_DcmCommControlConditionCheck(pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE],
                dataCommType_u8,&pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE],((uint16)(pMsgContext->reqDataLen)),
                dataNegRespCode_u8);
            if(E_OK == retVal_u8)
            {
                *dataNegRespCode_u8=0x00;
                Dcm_stCC_en = DCM_DSP_CC_PROCESSSERVICE;
                /* Call the API to get the communication mode from the control type and communication type */
                Dcm_stCommunicationMode_u8 = Dcm_Prv_GetCommModeType_u8(pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE],
                    dataCommType_u8);
                /* Get the subnet id from the request */
                Dcm_nrSubNet_u8 = (uint8)(pMsgContext->reqData[DCM_DSP_CC_POSCOMMTYPE] & (uint8)DCM_DSP_CC_SUBNETMASK);
                Dcm_nrSubNet_u8 =  Dcm_nrSubNet_u8>>4u;
                /* Check if Bit 7 to Bit 4 are set */
                switch (Dcm_nrSubNet_u8)
                {
                    case DCM_SUBNET_DISEN_REQUEST_RECIEVED_NODE:
                    /* All bits from Bit 4 to Bit 7 are set, thus we need to handle this for the Active ComM Channel */
                    /* Set the subnet number to the Rx channel id of the received Pdu Id */
                    Dcm_idxCommChannel_u8 = Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId;
                         break;

                    case DCM_SUBNET_DISEN_SPECIFIED_COMTYPE:
                        /* SubNet is zero */\
                         break;

                    default :
#if ( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
                        /* SubNet is between 0x1 and 0xE */
                        Dcm_idxCommChannel_u8 = Dcm_Prv_DspChkSubnetID_u8(Dcm_nrSubNet_u8,dataNegRespCode_u8);
#endif
                        break;
                }
            }
            else
            {

                if (0x00 == *dataNegRespCode_u8)
                {
                    /*Set NRC ConditionsNotCorrect*/
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    Dcm_stCC_en = DCM_DSP_CC_ERROR;
                }
            }
        }
        else
        {
            /*Set Negative response code */
            *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
            Dcm_stCC_en = DCM_DSP_CC_ERROR;
        }
    }
    else
    {
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
        Dcm_stCC_en = DCM_DSP_CC_ERROR;
    }
}


/**
 **************************************************************************************************
 *  Dcm_DcmCommunicationControl :The purpose of Communication Control service is to switch on/off the
 *  transmission and/or the reception of certain messages of one or many servers (e.g. application
 *  communication messages). For example: To decrease Flash programming times, it shall be possible
 *  to disable the normal bus communication by means of the Communication Control diagnostic service.
 *  On reception of this service (SID 0x28) DSD will invoke Dcm_DcmCommunicationControl function.
 *  Communication control service is allowed only in non default session and suppresses positive response
 *  is supported by this service.
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmCommunicationControl (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,
        P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,
        P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    *dataNegRespCode_u8 = 0x00;
    retVal_u8 = E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    if(OpStatus == DCM_CANCEL)
    {
        Dcm_Dsp_CCIni();
        retVal_u8 = E_OK;
    }
    else
    {
        if (Dcm_stCC_en == DCM_DSP_CC_INITIAL)
        {
            Dcm_Prv_CC_Check(pMsgContext,dataNegRespCode_u8);
        }
        if (Dcm_stCC_en == DCM_DSP_CC_PROCESSSERVICE)
        {
            retVal_u8 = E_OK;
            /* Set length of response */
            pMsgContext->resDataLen   = DCM_DSP_CC_RESLEN;
            /* Fill the sub function into the response */
            pMsgContext->resData[DCM_DSP_CC_POSCTRLTYPE] = pMsgContext->reqData[DCM_DSP_CC_POSCTRLTYPE];
            Dcm_stCC_en = DCM_DSP_CC_INITIAL;
        }
        if(Dcm_stCC_en == DCM_DSP_CC_ERROR)
        {
            retVal_u8 = E_NOT_OK;
            Dcm_stCC_en = DCM_DSP_CC_INITIAL;
        }
    }
    return retVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_DspCommunicationControlSwitchMode : The function will inform the BswM and the SchM/ application
 * regarding the change of mode for CommunicationControl Modes owned by Dcm
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_Prv_DspCommunicationControlSwitchMode(void)
{
    VAR(uint8,AUTOMATIC)idxIndex_u8;
    if ( Dcm_nrSubNet_u8 == 0)
    {
        for(idxIndex_u8=0;idxIndex_u8 < DCM_CFG_NUM_ALLCHANNELS_MODE_INFO;idxIndex_u8++)
        {
#if (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
            BswM_Dcm_CommunicationMode_CurrentState(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId,
                    Dcm_stCommunicationMode_u8);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
            (Std_ReturnType)((*(Dcm_AllChannels_ForModeInfo[idxIndex_u8].switch_fp))(Dcm_stCommunicationMode_u8));
#endif
            DcmAppl_DcmSwitchCommunicationControl(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId,
                    Dcm_stCommunicationMode_u8);
        }
    }
#if ( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
    else if (( Dcm_nrSubNet_u8 != 0 ) && ( Dcm_nrSubNet_u8 != 0xF ))
    {
#if (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
        BswM_Dcm_CommunicationMode_CurrentState(Dcm_specific_subnet_table[Dcm_idxCommChannel_u8].SpecificComMChannelId,
                Dcm_stCommunicationMode_u8);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
        (Std_ReturnType)((*(Dcm_specific_subnet_table[Dcm_idxCommChannel_u8].switch_fp))(Dcm_stCommunicationMode_u8));
#endif
        DcmAppl_DcmSwitchCommunicationControl(Dcm_specific_subnet_table[Dcm_idxCommChannel_u8].SpecificComMChannelId,
                Dcm_stCommunicationMode_u8);
    }
#endif
    else
    {
        /*Subnet ID is 0xF*/
        for(idxIndex_u8=0; idxIndex_u8 < DCM_CFG_NUM_ALLCHANNELS_MODE_INFO;idxIndex_u8++)
        {
            if(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId == Dcm_idxCommChannel_u8)
            {
#if (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
                BswM_Dcm_CommunicationMode_CurrentState(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId,
                        Dcm_stCommunicationMode_u8);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
                (Std_ReturnType)((*(Dcm_AllChannels_ForModeInfo[idxIndex_u8].switch_fp))(Dcm_stCommunicationMode_u8));
#endif
                DcmAppl_DcmSwitchCommunicationControl(Dcm_AllChannels_ForModeInfo[idxIndex_u8].AllComMChannelId,
                        Dcm_stCommunicationMode_u8);
                break;
            }
        }
    }
}

/**
 *******************************************************************************
 * Dcm_Prv_DspCommCntrlConfirmation : API used for confirmation of response sent
 *                                      for CommunicationControl (0x28) service.
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
FUNC(void, DCM_CODE) Dcm_Prv_DspCommCntrlConfirmation(
    VAR(Dcm_IdContextType ,AUTOMATIC)dataIdContext_u8,
    VAR(PduIdType,AUTOMATIC)dataRxPduId_u8,
    VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC)status_u8)
{
    if((status_u8 == DCM_RES_POS_OK)||(status_u8 == DCM_RES_POS_NOT_OK))
    {
        Dcm_Prv_DspCommunicationControlSwitchMode();
    }
    DcmAppl_DcmConfirmation(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,status_u8);
}
/**
 **************************************************************************************************
 * Dcm_Prv_CCMmodeStatusCheck : The function will check whether the configured mode rule is TRUE .
 * If the mode rule fails, it will reset the mode of the communication channels back to the default mode
 * and inform BswM and SchM/ application regarding the change in mode.
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

static FUNC(boolean, DCM_CODE) Dcm_Prv_CCMmodeStatusCheck(void)
{

    VAR(uint8,AUTOMATIC)    dataNRC_u8;
    VAR(boolean,AUTOMATIC)  flgStatus_b;
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    /*Initialize the flag status value to TRUE*/
    flgStatus_b = TRUE;
    dataNRC_u8 = 0x00;
    /* Call the DcmAppl callback to check for conditions for re-enabling communication control */
    if(Dcm_ComMUserReEnableModeRuleRef !=NULL_PTR)
    {
        retVal_u8 = (*Dcm_ComMUserReEnableModeRuleRef)();
        /* If the mode rule returns any value other than E_OK */
        if((retVal_u8!=E_OK))
        {
            /*Reset the flag status to false*/
            flgStatus_b = FALSE;
        }
    }

#if(DCM_CFG_DSP_MODERULEFORCC!=DCM_CFG_OFF)
    /*If flag status is set and check for conditions for re-enabling communication control*/
    if ((flgStatus_b!=FALSE) && (Dcm_ComMReEnableModeRuleRef != NULL_PTR))
    {
        flgStatus_b = (*Dcm_ComMReEnableModeRuleRef)(&dataNRC_u8);
    }
#endif

    if(dataNRC_u8 != 0u)
    {
        /*Reset the flag status to false*/
        flgStatus_b = FALSE;

    }

    return flgStatus_b;
}

/**
 **************************************************************************************************
 *  Dcm_Prv_ResetCommunicationMode :This function will check whether communication channel is in the default
 *  mode(DCM_ENABLE_RX_TX_NORM_NM) by calling the Appl function / generated function.
 *  If the channel is not in the default mode  then it will call
 *  BswM_Dcm_CommunicationMode_CurrentState and DcmAppl_DcmSwitchCommunicationControl/corresponding
 *  SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_XXX with  DCM_ENABLE_RX_TX_NORM_NM.
 *
 *  \param           None
 *  \retval          None
 *  \seealso
 *
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_Prv_ResetCommunicationMode(void)
{
    VAR(uint8,AUTOMATIC)    idxLoop_u8;
    VAR(boolean,AUTOMATIC)  stStatus_b;

    for(idxLoop_u8=0;idxLoop_u8 < DCM_CFG_NUM_ALLCHANNELS_MODE_INFO;idxLoop_u8++)
    {

        /*Check whether the channel is in Default communication mode ie, DCM_ENABLE_RX_TX_NORM_NM*/
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
        stStatus_b = (*(Dcm_AllChannels_ForModeInfo[idxLoop_u8].checkmode_fp))();
#else
        stStatus_b = DcmAppl_DcmIsComModeDefault(Dcm_AllChannels_ForModeInfo[idxLoop_u8].AllComMChannelId);
#endif
        /*Check if stStatus flag is set to FALSE*/
        if (stStatus_b == FALSE)
        {
            /* Channel is  not in Default communication mode.Call  BswM_Dcm_CommunicationMode_CurrentState and
             * DcmAppl_DcmSwitchCommunicationControl/corresponding
             SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_XXX with  DCM_ENABLE_RX_TX_NORM_NM */
#if (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
            BswM_Dcm_CommunicationMode_CurrentState(Dcm_AllChannels_ForModeInfo[idxLoop_u8].AllComMChannelId,
                    DCM_ENABLE_RX_TX_NORM_NM);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
            (Std_ReturnType)((*(Dcm_AllChannels_ForModeInfo[idxLoop_u8].switch_fp))(DCM_ENABLE_RX_TX_NORM_NM));
#endif
            DcmAppl_DcmSwitchCommunicationControl(Dcm_AllChannels_ForModeInfo[idxLoop_u8].AllComMChannelId,
                    DCM_ENABLE_RX_TX_NORM_NM);
        }
        else
        {
            /*Channel is alredy in the default mode;Do nothing*/
        }
    }
    /*Check the  communication mode of channels associated with specific subnets*/
#if ( DCM_CFG_NUM_SPECIFIC_SUBNETS != 0 )
    for(idxLoop_u8=0;idxLoop_u8 < DCM_CFG_NUM_SPECIFIC_SUBNETS;idxLoop_u8++)
    {

        /*Check whether the channel is in Default communication mode ie, DCM_ENABLE_RX_TX_NORM_NM*/
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
        stStatus_b = (*(Dcm_specific_subnet_table[idxLoop_u8].checkmode_fp))();
#else
        stStatus_b = DcmAppl_DcmIsComModeDefault(Dcm_specific_subnet_table[idxLoop_u8].SpecificComMChannelId);
#endif
        /*Check if stStatus flag is set to FALSE*/
        if (stStatus_b == FALSE)
        {
            /* Channel is  not in Default communication mode.Call  BswM_Dcm_CommunicationMode_CurrentState and
             * DcmAppl_DcmSwitchCommunicationControl/corresponding
               SchM_Switch_Dcm_DcmCommunicationControl_ComMChannel_XXX with  DCM_ENABLE_RX_TX_NORM_NM */
#if (DCM_CFG_DSP_BSWMDCM_ENABLED != DCM_CFG_OFF)
            BswM_Dcm_CommunicationMode_CurrentState(Dcm_specific_subnet_table[idxLoop_u8].SpecificComMChannelId,
                    DCM_ENABLE_RX_TX_NORM_NM);
#endif
#if(DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
            (Std_ReturnType)((*(Dcm_specific_subnet_table[idxLoop_u8].switch_fp))(DCM_ENABLE_RX_TX_NORM_NM));
#endif
            DcmAppl_DcmSwitchCommunicationControl(Dcm_specific_subnet_table[idxLoop_u8].SpecificComMChannelId,
                    DCM_ENABLE_RX_TX_NORM_NM);
        }
        else
        {
            /*Channel is alredy in the default mode;Do nothing*/
        }
    }
#endif
}

/**
 **************************************************************************************************
 *  Dcm_Prv_CC_Mainfunction :This function will check session changes and if transitioning to default session or
 *  upon any diagnostic session change where the new session do not support UDS Service CommunicationControl
 *  it will reset the mode of the communication channels back to the default mode
 *
 *  \param           None
 *  \retval          None
 *  \seealso
 *
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Prv_CC_Mainfunction (void)
{

    VAR(Dcm_SesCtrlType,DCM_VAR) ActiveSession_u8;
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;

    VAR(boolean,AUTOMATIC)  CC_Resetmoderuleflg_b;
    VAR(boolean,AUTOMATIC)  CC_Resetsessionflg_b;

    CC_Resetsessionflg_b = TRUE;
    CC_Resetmoderuleflg_b = Dcm_Prv_CCMmodeStatusCheck();

    /* Get the currently active session in the server */
    retVal_u8 = Dcm_GetSesCtrlType(&ActiveSession_u8);

    if((retVal_u8 == E_OK)&&(Dcm_CC_ActiveSession_u8 != ActiveSession_u8))
    {
        // session changed and new session stored
        Dcm_CC_ActiveSession_u8 =  ActiveSession_u8;
        if ( ActiveSession_u8 != DCM_DEFAULT_SESSION )
        {
            CC_Resetsessionflg_b = Dcm_Prv_CC_IsSupportedInSession(ActiveSession_u8);
        }
        else
        {
            CC_Resetsessionflg_b = FALSE;
        }
    }
    if((CC_Resetsessionflg_b == FALSE)||(CC_Resetmoderuleflg_b == FALSE ))
    {
        Dcm_Prv_ResetCommunicationMode();
    }

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

