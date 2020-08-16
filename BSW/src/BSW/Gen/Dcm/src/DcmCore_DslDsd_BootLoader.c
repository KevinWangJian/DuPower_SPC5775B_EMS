

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* State machine for Boot Loader */
VAR(Dcm_BootLoaderStates_ten,DCM_VAR) Dcm_BootLoaderState_en;
static VAR(Dcm_OpStatusType,     AUTOMATIC) s_Dcm_SetProgCondOpstatus_u8;
static VAR(Std_ReturnType,DCM_VAR) Dcm_StoreReturnValue_u8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static FUNC(Std_ReturnType,DCM_CODE) Dcm_TimerRemaining(VAR(uint32,AUTOMATIC)timer,VAR(uint32,AUTOMATIC)startTime,P2VAR(Std_ReturnType,DCM_INTERN_DATA,AUTOMATIC)timerStatus);
static FUNC(Std_ReturnType, DCM_CODE) Dcm_SendForcedResponsePend(void);
static FUNC(void, DCM_CODE) Dcm_InvokeSetProgCondition(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) flag_b, P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
/**
 **************************************************************************************************
 * Dcm_JumpToBootLoader : This function is responsible for performing a sequence of operations
 * before performing the Jump to Boot Reset. The performed actions are
 * 1. Calling of BswM_RequestResetMode with the appropriate Reset Mode
 * 2. Getting the Storage Type for Storing
 * 3. Storing the protocol information into the structure
 * 4. Calling of BswM_RequestResetMode to perform Reset
 *
 * \param           dataBootType_u8    : Parameter with the type of boot
 *                  dataNegRespCode_u8 : Parameter to update the NRC value
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_JumpToBootLoader(VAR(uint8,AUTOMATIC) dataBootType_u8, P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /* Local Variables to store data */
    VAR(uint8,            AUTOMATIC) dataProtocolId_u8;
    VAR(Dcm_SesCtrlType,  AUTOMATIC) dataSessionId_u8;
    VAR(Dcm_SecLevelType, AUTOMATIC) dataSecurityLevel_u8;
    VAR(Std_ReturnType,   AUTOMATIC) dataReturnValue_u8;
    VAR(boolean,          AUTOMATIC) flgProcessSrv_b;
#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
    VAR(uint8,            AUTOMATIC) idxSeca_qu8;
#endif
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
    VAR(uint16,           AUTOMATIC) dataTimingValue_u16;
#endif

    /* Initialize local variables */
    /* errorIndn_u8    = FALSE; */
    /*Set the Process flag to False*/
    flgProcessSrv_b  = FALSE;
    Dcm_StoreReturnValue_u8 = E_OK;

    if(Dcm_BootLoaderState_en == DCM_BOOT_IDLE)
    {   /* Call the DcmAppl function to get the Storage Type - Warm Request/Warm Init/ Warm Response */
        Dcm_ProgConditions_st.StoreType = DcmAppl_DcmGetStoreType(dataBootType_u8);

        /* If Storing Type is WarmRequest/WarmResponse/WarmInit */
        if((Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE)||
                (Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE)||
                (Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE))
        {
                /* Call the SchM Switch function with the BOOTLOADER RESET */
                if(dataBootType_u8 == DCM_JUMPTOOEMBOOTLOADER)
                {   /* Call the API to perform Jump to Boot Loader */
    #if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_JUMPTOBOOTLOADER);
    #endif
                    (void)DcmAppl_Switch_DcmBootLoaderReset();
                }
                /* If Session/resetType is mapped to perform Jump to System Supplier Boot Loader */
                else if(dataBootType_u8 == DCM_JUMPTOSYSSUPPLIERBOOTLOADER)
                {   /* Call the API to perform Jump to Boot Loader */
    #if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_JUMPTOSYSSUPPLIERBOOTLOADER);
    #endif
                    (void)DcmAppl_Switch_DcmSysSupplierReset();
                }
                /* If resetType is mapped to perform drive to drive jump */
                else if(dataBootType_u8 == DCM_JUMPDRIVETODRIVE)
                {
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                    if(Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE)
                    {
                        /* Call the API to perform Jump to Boot Loader */
                        (void)DcmAppl_Switch_DcmDriveToDriveReset();
                    }
                    else
                    {
                        Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                    }
#endif
                }
                else
                { /* Dummy Else */
                }
                if(Dcm_BootLoaderState_en != DCM_BOOT_ERROR)
                {
                    /* Trigger Resp Pend if allowed while jumping to boot */
                    if(Dcm_Dsld_Conf_cs.protocol_table_pcs[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].sendRespPendTransToBoot)
                    {
                        Dcm_BootLoaderState_en = DCM_BOOT_SENDFORCEDRESPPEND;
                    }
                    /* Move the state to store the protocol information prior to jump to boot */
                    else
                    {
                        if(Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE)
                        {
                            /* Move the state to Store Protocol Information */
                            Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMREQ;
                        }
                        else if(Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE)
                        {
                            /* Move the state to Store Protocol Information */
                            Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMRESP;
                        }
                        else
                        {
                            /* Move the state to Store Protocol Information */
                            Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMINIT;
                        }
                    }
            }
        }
        else
        {
            /*Set the Process flag to True*/
            flgProcessSrv_b  = TRUE;
        }
    }

    if((Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ) ||
            (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP)||
            (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT))
    {
        if(DCM_INITIAL==s_Dcm_SetProgCondOpstatus_u8)
        {
            /* Read the active protocol, active session and active security level */
            dataReturnValue_u8 = Dcm_GetActiveProtocol(&dataProtocolId_u8);

            if(dataProtocolId_u8 != DCM_NO_ACTIVE_PROTOCOL)
            {
                dataReturnValue_u8 = Dcm_GetSesCtrlType(&dataSessionId_u8);
                if(dataReturnValue_u8 == E_OK)
                {
                    dataReturnValue_u8 = Dcm_GetSecurityLevel(&dataSecurityLevel_u8);
                    if (dataReturnValue_u8 == E_OK)
                    {
                        /* Fill the structure with active protocol information */
                        Dcm_ProgConditions_st.Sid              = Dcm_DsldGlobal_st.dataSid_u8;
                        Dcm_ProgConditions_st.SecurityLevel    = dataSecurityLevel_u8;
                        Dcm_ProgConditions_st.SessionLevel     = dataSessionId_u8;
                        Dcm_ProgConditions_st.ProtocolId       = dataProtocolId_u8;
                        Dcm_ProgConditions_st.TesterSourceAddr = Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16;
                        Dcm_ProgConditions_st.ReqResLen        = 0x1;
                        Dcm_ProgConditions_st.NumWaitPend      = Dcm_DsldGlobal_st.cntrWaitpendCounter_u8;
#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
                        Dcm_ProgConditions_st.ElapsedTime      = (uint32)(Dcm_Dsp_SecaGlobaltimer_u32 * (uint32)(DCM_CFG_TASK_TIME_US/1000u));
#else
                        Dcm_ProgConditions_st.ElapsedTime      = 0x0;
#endif
#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF) && (DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF))
                        Dcm_ProgConditions_st.NumOfSecurityLevels = DCM_CFG_DSP_NUMSECURITY;
                        for(idxSeca_qu8 = 0x0; idxSeca_qu8 < DCM_CFG_DSP_NUMSECURITY; idxSeca_qu8++)
                        {
                            /* store the security level configured */
                            Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].SecurityLevel = Dcm_Dsp_Security[idxSeca_qu8].Security_level_u8;
                            /* store the failed attempt count for each security level */
                            Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].DelayCount = Dcm_Dsp_Seca[idxSeca_qu8].FailedAtm_cnt_u8;
                            /* store the delay timer for each security level */
                            if(Dcm_Dsp_Seca[idxSeca_qu8].Residual_delay_u32>Dcm_Dsp_SecaGlobaltimer_u32)
                            {
                                /* if the delay timer is active still, store the delay time in milli seconds */
                                Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].ResidualDelay = (Dcm_Dsp_Seca[idxSeca_qu8].Residual_delay_u32 - Dcm_Dsp_SecaGlobaltimer_u32)*DCM_CFG_TASK_TIME_MS;
                            }
                            else
                            {
                                /* if the delay timer is expired before jump to boot */
                                Dcm_ProgConditions_st.SecurityInformation[idxSeca_qu8].ResidualDelay = 0;
                            }
                        }
#endif
                        /* Set the response required flag in case of warm response or warm request */
                        if((Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP)||
                                (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ))
                        {
                            /*Set the response required flag to True*/
                            Dcm_ProgConditions_st.ResponseRequired=TRUE;
                        }
                        /* Clear the response required flag in case of warm init */
                        else
                        {
                          if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)
                          {
                              /*Set the response required flag to False*/
                              Dcm_ProgConditions_st.ResponseRequired= FALSE;
                          }
                        }

                        if(Dcm_ProgConditions_st.Sid == DCM_DSP_SID_DIAGNOSTICSESSIONCONTROL)
                        {
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
                            {
                                /* Set the reprogramming flag to TRUE */

                                Dcm_ProgConditions_st.ReprogramingRequest = TRUE;
                            }
#endif
                        }

                        if(Dcm_ProgConditions_st.Sid == DCM_DSP_SID_ECURESET)
                        {
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                            if((Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)&& (dataBootType_u8 != DCM_JUMPDRIVETODRIVE))
                            {
                                /* Set the reprogramming flag to TRUE */

                                Dcm_ProgConditions_st.ReprogramingRequest = TRUE;
                            }
                            else
                            {
                                /* Set the reprogramming flag to False */

                                Dcm_ProgConditions_st.ReprogramingRequest = FALSE;
                            }
#endif
                        }

                        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ)
                        {
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            /* DSC service is used for Jump to BootLoader */
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
                            {   /* Store the request */
                                Dcm_ProgConditions_st.SubFncId  = Dcm_ReqSess_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;
                            }
#endif
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)
                            {
                                /* Store the request */
                                Dcm_ProgConditions_st.SubFncId  = Dcm_dataEcuRType_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;
                            }
#endif

                        }

                        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP)
                        {   /* Store Response SID */
                            Dcm_ProgConditions_st.Sid = Dcm_DsldGlobal_st.dataSid_u8|0x40u;
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            /* DSC service is used for Jump to BootLoader */
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
                            {   /* Store the request */
                                Dcm_ProgConditions_st.SubFncId  = Dcm_ReqSess_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;

#if(DCM_CFG_DSP_DSC_SESRECINRESP != DCM_CFG_OFF)
                                /* Fill P2 Max Time */
                                dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32 / 1000u);
                                Dcm_ProgConditions_st.ReqResBuf[0] = (uint8)(dataTimingValue_u16 >> 8u);
                                Dcm_ProgConditions_st.ReqResBuf[1] = (uint8)(dataTimingValue_u16 & 0x00ffu);
                                /* Fill P2 Star Max Time */
                                dataTimingValue_u16 = (uint16)(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32/10000u);
                                Dcm_ProgConditions_st.ReqResBuf[2] = (uint8)(dataTimingValue_u16 >> 8u);
                                Dcm_ProgConditions_st.ReqResBuf[3] = (uint8)(dataTimingValue_u16 & 0x00ffu);
                                Dcm_ProgConditions_st.ReqResLen += 0x4;
#endif
                            }
#endif
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
                            if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)
                            {
                                /* Store the request */
                                Dcm_ProgConditions_st.SubFncId  = Dcm_dataEcuRType_u8;
                                Dcm_ProgConditions_st.ReqResLen = 0x2;
                                /* If reset type is not enableRapidPowerShutDown */
                                if(Dcm_dataEcuRType_u8 == DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET)
                                {
                                    /* Fill the power down time if reset type is enableRapidPowerShutDown  */
                                    Dcm_ProgConditions_st.ReqResBuf[0] = DCM_CFG_DSP_POWER_DOWN_TIME;
                                    /* Fill the response length 0x03 if reset type is enableRapidPowerShutDown(0x04)  */
                                    Dcm_ProgConditions_st.ReqResLen += 0x1;
                                }
                                if(dataBootType_u8 == DCM_JUMPDRIVETODRIVE)
                                {
                                    /* Set the session level to default session and security level to 0x00 ( locked security level) as only protocol related information needs to be restored in this case  */
                                    Dcm_ProgConditions_st.SessionLevel     = 0x01;
                                    Dcm_ProgConditions_st.SecurityLevel    = 0x00;
                                }
                            }
#endif
                            /* Call the DcmAppl API to store response bytes */
                            DcmAppl_DcmStoreRespForJump(&Dcm_ProgConditions_st);
                        }

                        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)
                        {
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                            /* DSC service is used for Jump to BootLoader */
                            if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
                            {   /* Store the session level after setting the requested session */
                                Dcm_ProgConditions_st.SessionLevel = Dcm_ReqSess_u8;
                                Dcm_ProgConditions_st.SecurityLevel= 0x0;
                                Dcm_ProgConditions_st.ReqResLen = 0x0;
                            }
#endif
                        }
                        /*Invoke the SetProg condition API*/
                        Dcm_InvokeSetProgCondition(&flgProcessSrv_b, dataNegRespCode_u8);
                    }
                }
            }

            if((dataProtocolId_u8 == DCM_NO_ACTIVE_PROTOCOL) || (dataReturnValue_u8 != E_OK))
            {
                /* Set the state to DCM_BOOT_ERROR */
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
        }
        else
        {
            /*Invoke the SetProg condition API, this portion is entered only when SetProg conditions API retursn
             * DCM_PENDING or DCM_FORCE_RCRRP*/
            Dcm_InvokeSetProgCondition(&flgProcessSrv_b, dataNegRespCode_u8);
        }
    }

    if(Dcm_BootLoaderState_en == DCM_BOOT_SENDFORCEDRESPPEND)
    {
        /* If Dcm is waiting for a Tx Confirmation of a response pending triggered from Dcm */
        /* Multicore: No lock needed here as Dsl state is an atomic read operation.
         * When this part of the code is reached when active request is being processed, so there is no chance that the DSL state is
         * modified in parallel as new requests are accepted only when DCM is free. Also the DSL states transitions only happens in
         * Dcm_MainFunction when there is a request active.*/
        if(Dcm_DsldGlobal_st.stDslState_en!= DSL_WAIT_FOR_CONFIRMATION)
        {
            /* Change the state to DCM_BOOT_WAIT before calling ForceRespPend operation */
            Dcm_BootLoaderState_en = DCM_BOOT_WAIT;
            /* Trigger of Response Pending is successful*/
            if(Dcm_ForceRespPend() == E_OK)
            {
                /* Do nothing.State is already changed */
            }
            /* If transmission of WaitPend response is not successful */
            else
            {
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
            }
            /* Set NRC to trigger NRC 0x10 from DSC service as the DSL state is set to trigger NRC 0x10
             * in the next main function and the DSC service needs to be completed in the current main function */
            /* Multicore: No lock needed here as Dsl state is an atomic read operation.
             * When this part of the code is reached when active request is being processed, so there is no chance that the DSL state is
             * modified in parallel as new requests are accepted only when DCM is free. Also the DSL states transitions only happens in
             * Dcm_MainFunction when there is a request active.*/
            if(Dcm_DsldGlobal_st.stDslState_en== DSL_SEND_GENERAL_REJECT)
            {
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            }
        }
        else
        {
            /* Do nothing.Remain in the state till the Tx Confirmation for the triggered wait pend is received */
        }
    }
    if(Dcm_BootLoaderState_en == DCM_BOOT_WAIT)
    {
        /* Do nothing , Wait for confirmation of response pending */
    }

    if(Dcm_BootLoaderState_en== DCM_BOOT_PREPARE_RESET)
    {
        if(Dcm_DsldGlobal_st.stDslState_en== DSL_WAIT_FOR_P2MAX)
        {
            Dcm_BootLoaderState_en = DCM_BOOT_WAIT_FOR_RESET;
#if (DCM_CFG_OSTIMER_USE != FALSE)
            if(E_NOT_OK==Dcm_TimerRemaining(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,&Dcm_StoreReturnValue_u8))
#else
            if(E_NOT_OK==Dcm_TimerRemaining(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,0,&Dcm_StoreReturnValue_u8))
#endif
            {
                if(E_OK!=Dcm_SendForcedResponsePend())
                {
                    Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
                    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
                }
            }
            else
            {
                Dcm_BootLoaderState_en = DCM_BOOT_PERFORM_RESET;
            }
        }
        else
        {
            /* Do nothing */
        }
    }
    if(Dcm_BootLoaderState_en == DCM_BOOT_WAIT_FOR_RESET)
    {
        /* Do nothing */
    }
    if(Dcm_BootLoaderState_en == DCM_BOOT_PERFORM_RESET)
    {
#if(DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                /* Call the SchM Switch function with the BOOTLOADER RESET */
                (void)SchM_Switch_Dcm_DcmEcuReset(RTE_MODE_DcmEcuReset_EXECUTE);
                /* May be immediately or after one cycle delay call the SchM Switch API to do reset */
#endif
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF))
                if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)
                {
                    DcmAppl_Switch_DcmExecuteEcuReset(Dcm_dataEcuRType_u8);
                }
#endif
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
                if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
                {
                    DcmAppl_Switch_DcmExecuteDscReset(Dcm_ReqSess_u8);
                }
#endif
                (void)DcmAppl_Switch_DcmExecuteReset();

                Dcm_BootLoaderState_en = DCM_BOOT_WAIT_FOR_RESET;
    }
    /* Check if any errors */
    if(Dcm_BootLoaderState_en == DCM_BOOT_ERROR)
    {
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
        /* DSC service is used for Jump to BootLoader */
        if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
        {   /* Set DSC service state to send Negative response */
            Dcm_stDsc_en = DCM_DSP_DSC_ERROR;
        }
#endif
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
        /* ER service is used for Jump to BootLoader */
        if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)
        {   /* Set ER service state to send Negative response */
            Dcm_stEcuResetState_en = DCM_ECURESET_ERROR;
        }
#endif
        /* Reset the reprograming request flag*/
        Dcm_ProgConditions_st.ReprogramingRequest = FALSE;
        /* Clear the response required flag*/
        Dcm_ProgConditions_st.ResponseRequired=FALSE;
        /* For user specific services the error handling will be done in DcmAppl Call back */
        Dcm_ResetBootLoader();
    }

    if(flgProcessSrv_b != FALSE)
    {
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF)
        /* DSC service is used for Jump to BootLoader */
        if(Dcm_stDsc_en == DCM_DSP_DSC_WAIT)
        {   /* Set DSC service state to send Final response */
            Dcm_stDsc_en = DCM_DSP_DSC_SEND_RESP;
        }
#endif
#if(DCM_CFG_DSP_ECURESET_ENABLED != DCM_CFG_OFF)
        /* DSC service is used for Jump to BootLoader */
        if(Dcm_stEcuResetState_en == DCM_ECURESET_WAIT)
        {   /* Set DSC service state to send Negative response */
            Dcm_stEcuResetState_en = DCM_ECURESET_SENDRESPONSE;
        }
#endif
        /* Call DcmAppl API to send the final response to tester before Reset */
        if(Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE)
        {
            DcmAppl_DcmRespWarmInit();
        }
    }
}

/**
 **************************************************************************************************
 * Dcm_ResetBootLoader : Reset the Boot Loader State machine.
 * This initializaes the boot loader state to IDLE state
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ResetBootLoader(void)
{
    /*Is Dcm_SetProgConditions operation pending and it needs to be cancelled?*/
    if((DCM_BOOT_WAIT==Dcm_BootLoaderState_en)||(DCM_BOOT_SENDFORCEDRESPPEND==Dcm_BootLoaderState_en))
    {
        /*Cancel the pending SetProgConditions operation*/
        (void)Dcm_SetProgConditions(DCM_CANCEL,NULL_PTR);
    }
    /* Reset Boot loader state machine */
    Dcm_BootLoaderState_en = DCM_BOOT_IDLE;
    /*Update the opstatus to indicate DCM_INITIAL*/
    s_Dcm_SetProgCondOpstatus_u8=DCM_INITIAL;

}

/**
 *********************************************************************************************************************
 * Dcm_TimerRemaining : Function to check if there is sufficient time remaining for EcuReset after the last wait pend
 * \param           timer             :
 *                  startTime         :
 *                  timerStatus       :
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */
static FUNC(Std_ReturnType,DCM_CODE) Dcm_TimerRemaining(VAR(uint32,AUTOMATIC)timer,VAR(uint32,AUTOMATIC)startTime,P2VAR(Std_ReturnType,DCM_INTERN_DATA,AUTOMATIC)timerStatus)
{
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8 = E_OK;
#if ( DCM_CFG_OSTIMER_USE != FALSE )
    VAR(uint32,AUTOMATIC) Dcm_GetCurrentTime_u32;
    Dcm_GetCurrentTime_u32 =0x00u;

    if ( *timerStatus == E_OK )
    {
        *timerStatus = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&Dcm_GetCurrentTime_u32));
        if ( *timerStatus == E_OK )
        {
            if(( (DCM_CFG_TICKS2US_COUNTER(Dcm_GetCurrentTime_u32 - (startTime))) +DCM_CFG_ECURESET_TIME) >=(timer) )
            {
                retVal_u8 = E_NOT_OK;
            }
        }
        else
        {
            retVal_u8 = E_NOT_OK;
        }
    }
    else
    {
        if(timer <= (DCM_CFG_ECURESET_TIME/DCM_CFG_TASK_TIME_US))
        {
            retVal_u8 =E_NOT_OK;
        }
    }
#else
    if(timer <= (DCM_CFG_ECURESET_TIME/DCM_CFG_TASK_TIME_US))
    {
        retVal_u8 =E_NOT_OK;
    }
    startTime =0x00;
    /*Typecasted to avoid any misra/compiler warnings*/
    (void)startTime;
    *timerStatus = E_OK;
#endif
       return (retVal_u8);
}

/*********************************************************************************************************************
* Dcm_SendForcedResponsePend : Function to trigger NRC 0x78
* \param           None
*
*
* \retval          Std_ReturnType : E_OK, E_NOT_OK
* \seealso
* \usedresources
**********************************************************************************************************************
*/

static FUNC(Std_ReturnType, DCM_CODE) Dcm_SendForcedResponsePend(void)
{
    VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8;
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
#endif

    dataRetValue_u8 = E_NOT_OK;
    /*Do not Proceed further if the call is triggered by ROE/RDPI ,or if the call is from application and none of the Dcm service is active */
    if((Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_ROE_SOURCE) && (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_RDPI_SOURCE) && (DSD_CALL_SERVICE  == Dcm_DsldGlobal_st.stDsdState_en))
    {
        /* If DCM is already sending response pend then this API returns E_NOT_OK */
        /*Check if DCM is not sending response pend */
        if(Dcm_DsldTransmit_st.flgApplWaitPend_b == FALSE)
        {
            /* This application triggered wait pend */
            /*Set the Wait Pending NRC flag to True*/
            Dcm_DsldTransmit_st.flgApplWaitPend_b = TRUE;

            /* no need to frame the response. It is done in separate function */
            Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = NULL_PTR;

            /* while framing the response proper length info is filled */
            Dcm_DsldTransmit_st.dataTxDataLength_u32 = 0x00;

            if( Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 != DCM_CFG_MAX_WAITPEND)
            {
                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* DSL state machine handling ensures that there is no data consistency issues */
                if( Dcm_DsldGlobal_st.stDslState_en == DSL_WAIT_FOR_P2MAX )
                {
            #if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                    stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
                    /* Multicore: When the protocol preemption has been initiated then this request should not be accepted */
                    if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&& (stDslPreemptionState_en != DSL_STOP_ROE))
            #endif
                    {
                        /* Multicore: Locking is necessary here to delay parallel Rx and buffer tampering- protocol prremption */
                        SchM_Enter_Dcm_Global_NoNest();
                        /* Frame intermediate Negative response based on the NRC */
                        Dcm_DsldWaitPendBuffer_au8[0] = DCM_NEGRESPONSE_INDICATOR;
                        Dcm_DsldWaitPendBuffer_au8[1] = Dcm_DsldGlobal_st.dataSid_u8;
                        Dcm_DsldWaitPendBuffer_au8[2] = DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING ;

                        /* update data in pdu structure */
                        Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DsldWaitPendBuffer_au8;
                        Dcm_DsldPduInfo_st.SduLength = 0x03;

                        /* increment wait pend counter to indicate one wait pend is sent */
                        Dcm_DsldGlobal_st.cntrWaitpendCounter_u8++;

                        /* Multicore: No lock needed here as Dsl state is an atomic operation */
                        /* DSL state machine handling ensures that there is no data consistency issues */
                        Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_CONFIRMATION;

                        /* after getting the Tx confirmation DSL state changed to DSL_WAIT_FOR_P2MAX  state */
                        Dcm_DsldTransmit_st.stDslNextState_en = DSL_WAIT_FOR_P2MAX;

                        SchM_Exit_Dcm_Global_NoNest();
                        /* Trigger  response */
                        Dcm_DsldSendResponse(&Dcm_DsldPduInfo_st);
                    }
                }
            }
            else
            {
                Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
            }
            /* Update return value */
            dataRetValue_u8 = E_OK;

        }
    }
    return(dataRetValue_u8);
    /* check the max number of wait pend is sent already or not */
}

/*********************************************************************************************************************
* Dcm_SendForcedResponsePend : Function to invoke Dcm_SetProgConditions api
* \param           [out]    flag_b  :  flag to monitor if jump is due to WARMINIT store type
*                           dataNegRespCode_u8 : Parameter to update the NRC value
*
*
* \retval          void
* \seealso
* \usedresources
**********************************************************************************************************************
*/

static FUNC(void, DCM_CODE) Dcm_InvokeSetProgCondition(P2VAR(boolean,AUTOMATIC,DCM_INTERN_DATA) flag_b, P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Std_ReturnType,   AUTOMATIC) dataRetProgCond_u8;

    /* Call the API to inform application about the information to be stored */
    dataRetProgCond_u8 = Dcm_SetProgConditions(s_Dcm_SetProgCondOpstatus_u8,&Dcm_ProgConditions_st);
    /* The information is stored in Comstate descriptor? */

    if(dataRetProgCond_u8 == E_OK)
    {
        if((Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMREQ) ||
                (Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMRESP))
        {
            Dcm_BootLoaderState_en= DCM_BOOT_PREPARE_RESET;
        }
        if(Dcm_BootLoaderState_en == DCM_BOOT_STORE_WARMINIT)
        {   /* Process the service - Reset will be called from confirmation function */
            /*Set the flag to True*/
            *flag_b = TRUE;
        }
        /*Update the opstatus to indicate DCM_INITIAL*/
        s_Dcm_SetProgCondOpstatus_u8=DCM_INITIAL;
    }
    else if(dataRetProgCond_u8 == DCM_E_PENDING)
    {
        /* Storing the data takes more time - Wait */
        /*Update the opstatus to indicate PENDING operation*/
        s_Dcm_SetProgCondOpstatus_u8=DCM_PENDING;
    }
    else if(dataRetProgCond_u8 == DCM_E_FORCE_RCRRP)
    {
        /* Application requests the transmission of a response Response Pending NRC 0x78 */
        /*Update the bootloader state variable to SendforceRespPend to trigger NRC78*/
        Dcm_BootLoaderState_en= DCM_BOOT_SENDFORCEDRESPPEND;
        /*Update the opstatus to indicate FORCE RESP PEND*/
        s_Dcm_SetProgCondOpstatus_u8=DCM_FORCE_RCRRP_OK;
    }
    else
    {
        /* Set the state to DCM_BOOT_ERROR */
        Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
        /*Update the opstatus to indicate DCM_INITIAL*/
        s_Dcm_SetProgCondOpstatus_u8=DCM_INITIAL;
        /* DET ERROR REPORT */
        DCM_DET_ERROR(DCM_BOOTLOADER_ID, DCM_E_SET_PROG_CONDITIONS_FAIL);
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
