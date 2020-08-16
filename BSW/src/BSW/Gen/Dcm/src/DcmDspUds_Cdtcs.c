

#include "DcmDspUds_Cdtcs_Inf.h"

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( boolean, DCM_VAR )  Dcm_DspCDTCStatus_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_CDTCSIni : Initialisation function for Control Diagnostic Trouble Code Setting Service
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsp_CDTCSIni(void)
{
    /* Set CDTC state to TRUE */

    Dcm_DspCDTCStatus_b = TRUE;
}

/**
 **************************************************************************************************
 * Dcm_DcmControlDTCSetting :
 * This service is used to enable or disable the setting of DTCs
 * This function is called by DSD, when SID is 0x85,
 * this service is provided in DSP module and configured in DCM identifier table.
 * When the DSP receives such a request it executes DEM function Dem_DisableDTCSetting/
 * Dem_EnableDTCSetting to disable/enable the setting of DTCs
 *
 * \param           pMsgContext    Pointer to message structure
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmControlDTCSetting (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(uint32,                         AUTOMATIC) dataDTC_u32;            /* Variable to store DTC */
    VAR(uint16,                         AUTOMATIC) nrReqLen_u16;           /* Variable to store request length         */
    VAR(uint8,                          AUTOMATIC) dataDtcSettingType_u8;    /* DTC Setting type                         */
    VAR(Dem_ReturnControlDTCSettingType,AUTOMATIC) dataDemRetVal_u8;             /* DEM return value                         */
    VAR(Std_ReturnType,              AUTOMATIC) dataRetSetCtrlOpRectype_u8;
    VAR(Std_ReturnType,                   AUTOMATIC)  dataServRetval_u8;

    /* initialise local variables */
    *dataNegRespCode_u8 = 0;
    dataDemRetVal_u8 = DEM_CONTROL_DTC_SETTING_N_OK;
    dataDtcSettingType_u8 = 0x0;
    dataRetSetCtrlOpRectype_u8 = E_OK;
    nrReqLen_u16 = DCM_PRV_CDTC_REQUEST_LENGTH;
    dataDTC_u32  = DEM_DTC_GROUP_ALL_DTCS;
    /* Get the sub-function from the request */
    dataDtcSettingType_u8 = pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC];
    dataServRetval_u8=E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    /* If OpStatus is set to DCM_CANCEL then call the Ini function for Re-Setting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_CDTCSIni();
        /* Return E_OK as Ini function is always serviced */
        dataServRetval_u8 = E_OK;
    }
    else
    {
        /* Check if subfunction configured is 0x01 or 0x02 */
        if((dataDtcSettingType_u8 == DCM_PRV_CDTC_OFF) || (dataDtcSettingType_u8 == DCM_PRV_CDTC_ON))
        {
            /* Check if DTCSettingCtrlOpRecLen is configured greater than 0 */
#if(DCM_CFG_DSP_SUPPORTCDTCRECORD != FALSE)
            /* Set request length to length of DTCSetCtrlOpRec and subfunction */
            nrReqLen_u16 = DCM_PRV_CDTC_RECORD_LENGTH  + DCM_PRV_CDTC_REQUEST_LENGTH ;
            dataDTC_u32 =((((uint32) pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC+1u]) << 16u) |
                                     (((uint32) pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC+2u]) << 8u) |
                                      ((uint32) pMsgContext->reqData[DCM_PRV_CDTC_POSITION_SUBFUNC+3u]));
#endif
            /* Check the length of the request message */
            if(pMsgContext->reqDataLen == nrReqLen_u16)
            {
                /* Call the application function if DTCSettingControlOptionRecord is present in request */
                if(nrReqLen_u16 > DCM_PRV_CDTC_REQUEST_LENGTH)
                {
                    dataRetSetCtrlOpRectype_u8 = DcmAppl_DcmCheckCDTCRecord(&pMsgContext->reqData[1], DCM_PRV_CDTC_RECORD_LENGTH, dataNegRespCode_u8);
                }
                if(dataRetSetCtrlOpRectype_u8 == E_OK)
                {
                    *dataNegRespCode_u8 = 0x00;
                    /* Sub-function parameter indicates server to stop the setting of DTCs */
                    if(dataDtcSettingType_u8 == DCM_PRV_CDTC_OFF)
                    {
                        /*Call Application function to get permission to disable DTC Storage*/
                        DcmAppl_DisableDTCSetting(dataNegRespCode_u8);

                        /* No error is reported from application */
                        if (*dataNegRespCode_u8 == 0x00)
                        {
                            /* Request DEM to disable the DTC settings */
                            dataDemRetVal_u8 = Dem_DisableDTCSetting(dataDTC_u32, DEM_DTC_KIND_ALL_DTCS);
                            if(dataDemRetVal_u8 == DEM_CONTROL_DTC_SETTING_OK)
                            {
                                /*Set CDTC state to FALSE*/
                                Dcm_DspCDTCStatus_b = FALSE;
#if (DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
                                (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_DISABLEDTCSETTING);
#endif
                                DcmAppl_DcmControlDtcSettingEnableStatus(Dcm_DspCDTCStatus_b);
                            }
                            /* If the DTC group is invalid */
                            else if(dataDemRetVal_u8 == DEM_CONTROL_DTC_WRONG_DTCGROUP)
                            {
                                /* Send negative response code: Request Out Of Range */
                                *dataNegRespCode_u8  = DCM_E_REQUESTOUTOFRANGE;
                                dataServRetval_u8=E_NOT_OK;
                            }
                            /* If request is rejected by the DEM */
                            else
                            {
                                /* Send negative response code: Condition Not Correct */
                                *dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
                                dataServRetval_u8=E_NOT_OK;
                            }
                        }
                    }
                    /* Sub-function parameter indicates server to resume the setting of DTCs */
                    else
                    {
                        /* request the DEM to enable the DTC settings */
                        dataDemRetVal_u8 = Dem_EnableDTCSetting (dataDTC_u32, DEM_DTC_KIND_ALL_DTCS);
                        /*Call application function to pass the status of DTC enabling*/
                        DcmAppl_EnableDTCSetting(dataDemRetVal_u8);

                        if(dataDemRetVal_u8 == DEM_CONTROL_DTC_SETTING_OK)
                        {
                            /*Set CDTC state to TRUE*/
                            Dcm_DspCDTCStatus_b = TRUE;
#if (DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
                            (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
                            DcmAppl_DcmControlDtcSettingEnableStatus(Dcm_DspCDTCStatus_b);
                        }
                        /* If the DTC group is invalid */
                        else if(dataDemRetVal_u8 == DEM_CONTROL_DTC_WRONG_DTCGROUP)
                        {
                            /* Send negative response code: Request Out Of Range */
                            *dataNegRespCode_u8  = DCM_E_REQUESTOUTOFRANGE;
                            dataServRetval_u8=E_NOT_OK;
                        }
                        /* If request is rejected by the DEM */
                        else
                        {
                            /* Send negative response code: Condition Not Correct */
                            *dataNegRespCode_u8  = DCM_E_CONDITIONSNOTCORRECT;
                            dataServRetval_u8=E_NOT_OK;
                        }
                    }
                }
                else
                {
                    if(*dataNegRespCode_u8 == 0x00)
                   {
                      *dataNegRespCode_u8  = DCM_E_REQUESTOUTOFRANGE;
                      dataServRetval_u8=E_NOT_OK;
                   }
                }
            }
            /* Sub-function not supported */
            else
            {
                /* Send negative response code: Invalid message length */
                *dataNegRespCode_u8  = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
                dataServRetval_u8=E_NOT_OK;
            }
        }
        /* Sub-function not supported */
        else
        {
            /* Send negative response code: Sub function not supported */
            *dataNegRespCode_u8  = DCM_E_SUBFUNCTIONNOTSUPPORTED;
            dataServRetval_u8=E_NOT_OK;
        }

        /* Is Negative response code found? */
        if(*dataNegRespCode_u8 == 0)
        {
            /* Set the positive response length */
            pMsgContext->resDataLen = 0x01;
            /* Fill the sub function in response buffer */
            pMsgContext->resData[DCM_PRV_CDTC_POSITION_SUBFUNC] = dataDtcSettingType_u8;
            dataServRetval_u8=E_OK;
        }
        else
        {
            dataServRetval_u8=E_NOT_OK;
        }
    }
    return dataServRetval_u8;
}

#if ( DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF )

/**
 **************************************************************************************************
 * Dcm_GetControlDTCSetting_EnableStatus : Function to get the status of control Dtc setting
 * Returns true, if Dtc setting is enabled and returns false if Dtc setting is disabled
 * Can be used by other SWCs and BSW modules in case RTE is not supported.
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(boolean,DCM_CODE) Dcm_GetControlDTCSetting_EnableStatus(void)
{
    return (Dcm_DspCDTCStatus_b);
}
#endif


/**
 **************************************************************************************************
 * Dcm_ControlDtcSettingExit : The function has to be called when there is a session change.
 * If the control Dtc setting is disabled, the function will re-enable the same, if there
 * is a session change to DEFAULT session or to a session in which the Dtc setting is not supported
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_ControlDtcSettingExit(void)
{
    VAR(uint8,AUTOMATIC) idxCdtc_u8;
    VAR(Dem_ReturnControlDTCSettingType,AUTOMATIC) dataDemRetVal_u8;    /* DEM return value  */
    VAR(uint32,AUTOMATIC) session_active_u32;  /* Variable to store the requested session */
    VAR(uint32,AUTOMATIC) allowed_session_u32; /* Variable to hold the current active session*/
    /* Get the index of the control Dtc setting service index from the service table*/
    idxCdtc_u8 = Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].cdtc_index_u8;
    /* Get the allowed sessions for the control Dtc setting*/
    if(idxCdtc_u8 != 0xFFu)
    {
        allowed_session_u32=Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs[idxCdtc_u8].allowed_session_b32;
    }
    else
    {
        allowed_session_u32=0xffffffffu;
    }
    /* Get the current active session*/
    session_active_u32 = (uint32)(0x00000001uL << Dcm_DsldGlobal_st.idxActiveSession_u8);
    /* check whether the session is default, or the new session is allowed for control Dtc setting*/
    if((session_active_u32 == ((uint32)DCM_DEFAULT_SESSION))||((allowed_session_u32 & session_active_u32) != session_active_u32))
    {
        /*If CDTC state is set to FALSE*/
        if(Dcm_DspCDTCStatus_b == FALSE)
        {
            /* Call the Dem function to enable the Dtc setting*/
            dataDemRetVal_u8 =Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
            if(dataDemRetVal_u8 == DEM_CONTROL_DTC_SETTING_OK)
            {
                /*Set CDTC state to TRUE*/
                Dcm_DspCDTCStatus_b = TRUE;
                /* Inform schm or application about the session change*/
#if (DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
                (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
                DcmAppl_DcmControlDtcSettingEnableStatus(Dcm_DspCDTCStatus_b);
            }
        }
    }
}


/**
 **************************************************************************************************
 * Dcm_CDTCModeStatusCheck : The function will check whether the check in configured mode rule/DcmAppl API
 * passes if the control Dtc setting is disabled.If the mode rule fails, it will re-enable the Dtc setting.
 * The function has to be cyclically called from the main function.
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_CDTCModeStatusCheck(void)
{
    VAR( boolean, DCM_VAR ) flgModeRetval_b;
    VAR(uint8,AUTOMATIC) dataNegRespCode_u8;
    VAR(Dem_ReturnControlDTCSettingType,AUTOMATIC) dataDemRetVal_u8;
    dataNegRespCode_u8 =0x00;

    /* Control Dtc setting disabled?*/
    /*IfCDTC state is set to FALSE*/
    if(Dcm_DspCDTCStatus_b == FALSE)
    {
        /* Call the mode function to check the mode rule status*/
        flgModeRetval_b=Dcm_ControlDtcSettingModecheck_b(&dataNegRespCode_u8);
        /* If the mode rule returns false, enable the Dtc setting*/

        if((flgModeRetval_b == FALSE) || (dataNegRespCode_u8 != 0u))
        {
            /* Call the Dem function to enable Dtc setting*/
            dataDemRetVal_u8 = Dem_EnableDTCSetting(DEM_DTC_GROUP_ALL_DTCS, DEM_DTC_KIND_ALL_DTCS);
            DcmAppl_EnableDTCSetting(dataDemRetVal_u8);
            if(dataDemRetVal_u8 == DEM_CONTROL_DTC_SETTING_OK)
            {
                /*Set CDTC state to TRUE*/
                Dcm_DspCDTCStatus_b = TRUE;
                /* Inform schm or application about the enabling of Dtc setting*/
#if (DCM_CFG_RTESUPPORT_ENABLED!=DCM_CFG_OFF)
                (void)SchM_Switch_Dcm_DcmControlDTCSetting(RTE_MODE_DcmControlDTCSetting_ENABLEDTCSETTING);
#endif
                DcmAppl_DcmControlDtcSettingEnableStatus(Dcm_DspCDTCStatus_b);
            }
        }
    }

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif /* (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) */
