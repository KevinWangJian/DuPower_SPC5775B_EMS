

#include "DcmDspUds_Rdpi_Inf.h"

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READDATABYPERIODICIDENTIFIER_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(Dcm_DspRdpiState_ten, DCM_VAR) Dcm_stDspRdpiState_en;      /* State for RDPI state machine */
static VAR (Dcm_OpStatusType, DCM_VAR) s_Dcm_DspCondChkRdOpStatus_u8;  /* Variable to store the opstatus*/
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static VAR(uint8,                DCM_VAR) s_nrPeriodicId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Dsp_RdpiIni:
 * Initialization function for Read Data By Periodic Identifier Service.
 *
 * \parameters           None
 * \return value         None
 *
 **************************************************************************************************
 */
FUNC(void,DCM_CODE)Dcm_Dsp_RdpiIni   (void)
{
    /* Reset the RDPI service state to default state */
    Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
    s_Dcm_DspCondChkRdOpStatus_u8=DCM_INITIAL;

}


/**
 **************************************************************************************************
 * Dcm_RdpiIsTransmissionModeSupported : This function indicates if the data transmission mode
 *                                       requested by the tester is supported or not
 *
 * \parameters           dataTransmissionMode_u8
 *
 * \return value         Std_ReturnType :   If return value is E_NOT_OK the transmission mode requested by tester
 *                                          is not supported, if E_OK tx mode is supported
 *
 **************************************************************************************************
 */
static FUNC(Std_ReturnType,DCM_CODE)Dcm_RdpiIsTransmissionModeSupported(VAR(uint8,AUTOMATIC) dataTransmissionMode_u8);
static FUNC(Std_ReturnType,DCM_CODE)Dcm_RdpiIsTransmissionModeSupported(VAR(uint8,AUTOMATIC) dataTransmissionMode_u8)
{
    VAR(Std_ReturnType,              AUTOMATIC) dataRetVal_u8;

    dataRetVal_u8=E_NOT_OK; /*If set to E_NOT_OK the transmission mode is not supported, if E_OK tx mode is supported*/

    if((dataTransmissionMode_u8 > 0x00) && (dataTransmissionMode_u8 < 0x04))
    {
        /* Check if the Transmission mode in request is supported by the server */
        if(((dataTransmissionMode_u8 == DCM_DSP_RDPI_SLOW_RATE)   && (DCM_CFG_PERIODICTX_SLOWRATE  !=0x00u)) ||
           ((dataTransmissionMode_u8 == DCM_DSP_RDPI_MEDIUM_RATE) && (DCM_CFG_PERIODICTX_MEDIUMRATE!=0x00u)) ||
           ((dataTransmissionMode_u8 == DCM_DSP_RDPI_FAST_RATE)   && (DCM_CFG_PERIODICTX_FASTRATE  !=0x00u)))
        {
            dataRetVal_u8=E_OK;
        }
    }
    else if(dataTransmissionMode_u8 == 0x04u)
    {
        dataRetVal_u8=E_OK;
    }
    else
    {
        /*Do nothing here, since E_NOT_OK return value is already set*/
    }

    return dataRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_RdpiIsDidCondtionChkReadSupported : This function checks if the condition check read for
 *                                         the DID is supported or not.
 *
 * \parameters          idxDidIndexType_st: index in Dcm_DIDConfig trcture
 *  * \return value     Std_ReturnType :   E_OK : Condition checkread successful
 *                                         E_NOT_OK : Condition checkread failed
 *                                         E_PENDING : Need more time, call again
 *
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_RdpiIsDidCondtionChkReadSupported(P2VAR(Dcm_DIDIndexType_tst ,AUTOMATIC,DCM_INTERN_DATA) idxDidIndexType_st)
{
    VAR(uint16,                      AUTOMATIC) idxIndex_u16;
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    P2CONST(Dcm_DataInfoConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrSigConfig;
    P2CONST(Dcm_SignalDIDSubStructConfig_tst,AUTOMATIC, DCM_INTERN_DATA ) ptrControlSigConfig;
    P2VAR(void,AUTOMATIC, DCM_INTERN_DATA)  ptrDIDFnc;
    dataCondChkRetVal_u8=E_OK;
    ptrDIDFnc=NULL_PTR;
    ptrDidConfig = &Dcm_DIDConfig[idxDidIndexType_st->idxIndex_u16];
    /*Check if the DID currently under process is a normal DID*/
    if(idxDidIndexType_st->dataRange_b==FALSE)
    {
        /*Loop throush all the signals of DID*/
        for(idxIndex_u16=0;((idxIndex_u16<ptrDidConfig->nrSig_u16)&&(dataCondChkRetVal_u8!=E_OK)&&(idxDidIndexType_st->dataNegRespCode_u8!=0));idxIndex_u16++)
        {
            ptrSigConfig  = &Dcm_DspDataInfo_st[ptrDidConfig->adrDidSignalConfig_pcst[idxIndex_u16].idxDcmDspDatainfo_u16];
            ptrControlSigConfig = &Dcm_DspDid_ControlInfo_st[ptrSigConfig->idxDcmDspControlInfo_u16];

            /*Check if condition check read function is configured or not*/
            if(ptrControlSigConfig->adrCondChkRdFnc_cpv!= NULL_PTR)
            {
                ptrDIDFnc=ptrControlSigConfig->adrCondChkRdFnc_cpv;
                /* Call function to check if conditions are fulfilled to read the DID */
               if((ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_FNC) ||             \
                   (ptrSigConfig->usePort_u8 == USE_DATA_SYNCH_CLIENT_SERVER))
               {
                   /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                   dataCondChkRetVal_u8 = (*(CondChkReadFunc1_pfct)(ptrDIDFnc))(&idxDidIndexType_st->dataNegRespCode_u8);
               }
               else
               {
                   if((ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_FNC) ||
    #if(DCM_CFG_RDBIPAGEDBUFFERSUPPORT != DCM_CFG_OFF)
                  (ptrSigConfig->usePort_u8 == USE_DATA_RDBI_PAGED_FNC) ||
    #endif
                  (ptrSigConfig->usePort_u8 == USE_DATA_ASYNCH_CLIENT_SERVER))
                   {
                       /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - Required for efficient RAM usage by using single void function pointer */
                       dataCondChkRetVal_u8 = (*(CondChkReadFunc2_pfct)(ptrDIDFnc))(idxDidIndexType_st->dataopstatus_b, &idxDidIndexType_st->dataNegRespCode_u8);
                   }
               }

            }
        }
    }
    else
    {
        /*Return E_OK, since no condition check exist for range DID*/
        dataCondChkRetVal_u8=E_OK;
    }

    return dataCondChkRetVal_u8;
}

/**
 **************************************************************************************************
 * Dcm_RdpiIsDidCondtionChkReadSupported : This function to reset a periodic DID
 *
 * \parameters          idxDidIndexType_st: index in Dcm_DIDConfig trcture
 * \return value     void
 *
 **************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_ResetRdpiStateVariables(VAR(uint8,AUTOMATIC)idxIndex_u8, VAR(Dcm_RdpiTxModeType_ten, AUTOMATIC) dataOverflowValue_en,
                                                       VAR(uint16,AUTOMATIC)dataId_u16, VAR(uint16, AUTOMATIC) idxPeriodicId_u16,
                                                       VAR(uint32,AUTOMATIC) cntrTime_u32,VAR(boolean,AUTOMATIC) dataRange_b);
static FUNC(void,DCM_CODE) Dcm_ResetRdpiStateVariables(VAR(uint8,AUTOMATIC)idxIndex_u8, VAR(Dcm_RdpiTxModeType_ten, AUTOMATIC) dataOverflowValue_en,
                                                      VAR(uint16,AUTOMATIC)dataId_u16, VAR(uint16, AUTOMATIC) idxPeriodicId_u16,
                                                      VAR(uint32,AUTOMATIC) cntrTime_u32,VAR(boolean,AUTOMATIC) dataRange_b)
{
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en= dataOverflowValue_en;
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16=dataId_u16;
                    Dcm_PeriodicInfo_st[idxIndex_u8].idxPeriodicId_u16=idxPeriodicId_u16;
                    Dcm_PeriodicInfo_st[idxIndex_u8].cntrTime_u32=cntrTime_u32;
                    Dcm_PeriodicInfo_st[idxIndex_u8].dataRange_b=dataRange_b;
}
/**
 **************************************************************************************************
 * Dcm_DcmReadDataByPeriodicIdentifier : The ReadDataByPeriodicIdentifier Service requests a server to periodically transmit
 * transmission of responses.
 * This service provides the possibility of scheduling an identifier to be periodically transmitted in the requested transmission rate.
 *
 * \parameters           pMsgContext Pointer to message structure
 *                                   (input : RequestLength, Response buffer size, request bytes)
 *                                   (output: Response bytes and Response length )
 * \return value         None
 *
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmReadDataByPeriodicIdentifier(VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR (Dcm_DIDIndexType_tst,       AUTOMATIC) s_Dcm_idxDidIndexType_st;                   /* Variable to store the idxIndex_u8 of the Periodic identifier */
    VAR (uint32,AUTOMATIC) dataSessionMask_u32;   /* Variable to hold the configured sessions value */
    VAR (uint32,AUTOMATIC) dataSecurityMask_u32;  /* Variable to hold the configured security value */
    P2CONST(Dcm_ExtendedDIDConfig_tst,AUTOMATIC,DCM_INTERN_CONST) adrExtendedConfig_pcst; /* Pointer to extended configuration */
    VAR(uint8,                       AUTOMATIC) idxIndex_u8;
    VAR(uint8,                       AUTOMATIC) dataTransmissionMode_u8;          /* Local variable to transmission mode */
    VAR(Dcm_RdpiTxModeType_ten,              AUTOMATIC) dataOverflowValue_en;
    VAR(boolean,                     AUTOMATIC) isValidId_b;
    VAR(Std_ReturnType,AUTOMATIC) retVal_u8;
    VAR (Std_ReturnType,   AUTOMATIC) dataCondChkRetVal_u8; /* Return value of Condition check API */
    P2CONST(Dcm_DIDConfig_tst,AUTOMATIC, DCM_INTERN_DATA )ptrDidConfig;
    static VAR(uint32,DCM_VAR) s_idxLoop_qu32;                   /* Index for loop counter */
    VAR (Std_ReturnType,AUTOMATIC) IsDIDAvailFnc_u8 = E_NOT_OK;
    /* Local variable initialization */
    *dataNegRespCode_u8        = 0x00;
    /*Initialize the variable to FALSE*/
    isValidId_b             = FALSE;
    s_nrPeriodicId_u8 = 0x00;
    s_Dcm_idxDidIndexType_st.idxIndex_u16   =   0;
    /*Initialize the variable to indicate  did is a range did or not to FALSE*/
    s_Dcm_idxDidIndexType_st.dataRange_b    =   FALSE;
    s_Dcm_idxDidIndexType_st.dataNegRespCode_u8=0;
    dataCondChkRetVal_u8=E_OK;
    dataSessionMask_u32=0;
    dataSecurityMask_u32=0;
    adrExtendedConfig_pcst=NULL_PTR;
    ptrDidConfig=NULL_PTR;
    retVal_u8 = E_NOT_OK;
    /*Opstatus possed by the central statemachine is unused currently, opstatus variables related to service needs to be
     * removed and the one passed by the central statemachine needs to be used, this would be taken care with task XXXXX*/

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_RdpiIni();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        retVal_u8 = E_OK;
    }
    else
    {
        /* Initialized state */
        if(Dcm_stDspRdpiState_en == DCM_DSP_RDPI_INIT)
        {
         /* Check for minimum request length */
            if(((pMsgContext->reqDataLen)!=0u)&&(DCMRDPIMINLENGTHCHECK((pMsgContext->reqDataLen),(pMsgContext->reqData[DCM_DSP_RDPI_POSTXMODE]))))
            {
                /* Check for maximum request length */
                if(DCMRDPIMAXLENGTHCHECK( pMsgContext->reqDataLen ))
                {
                    /* Copy transmission mode to local variable */
                    dataTransmissionMode_u8 = pMsgContext->reqData[DCM_DSP_RDPI_POSTXMODE];
                    /* Check if the transmission mode requested by the tester is supported by the ECU*/
                    if(E_OK==Dcm_RdpiIsTransmissionModeSupported(dataTransmissionMode_u8))
                    {
                        /* If Transmission mode is 0x04, move the state to DCM_DSP_RDPI_CHECKPERMISSION to process the request */
                        if(dataTransmissionMode_u8==DCM_DSP_RDPI_STOP_SENDING)
                        {
                            /* Change the state to check for permissions for the PDIDs in the request */
                            Dcm_stDspRdpiState_en = DCM_DSP_RDPI_CHECKPERMISSION;
                        }
                        else
                        {
                            /*Is the scheduler free at all???*/
                            if(Dcm_NumOfActivePeriodicId_u8<DCM_CFG_MAX_DID_SCHEDULER)
                            {
                                /* Loop through the identifiers in the request and find the number of periodic identifiers which is not in the scheduler table*/
                                for(s_idxLoop_qu32=1u;((s_idxLoop_qu32 < (pMsgContext->reqDataLen)) && (*dataNegRespCode_u8 ==0x00));s_idxLoop_qu32++)
                                {
                                    /* Check if the DID sent from tester is configured in Server */
                                    if(E_OK == Dcm_GetIndexOfDID((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u), &s_Dcm_idxDidIndexType_st))
                                    {
                                        /*Is the DID range DID or not*/

                                        if(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE)
                                        {
                                            ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16];
                                            adrExtendedConfig_pcst=Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
                                        }
#if ( DCM_CFG_DIDRANGE_EXTENSION != DCM_CFG_OFF)
                                        /*Control comes here for range DIDS*/
                                        else
                                        {
                                            adrExtendedConfig_pcst=Dcm_DIDRangeConfig_cast[s_Dcm_idxDidIndexType_st.idxIndex_u16].adrExtendedConfig_pcst;
                                        }
#endif

                                        /*Obtain the session and security mask based on the type of DID*/
                                        dataSessionMask_u32  = adrExtendedConfig_pcst->dataAllowedSessRead_u32;
                                        dataSecurityMask_u32 = adrExtendedConfig_pcst->dataAllowedSecRead_u32;

#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)
                                       if(*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR)
									   {
                                        IsDIDAvailFnc_u8 = (*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u));
									   }
                                        /* Check if the DID is supported in current variant */
                                        if((s_Dcm_idxDidIndexType_st.dataRange_b==TRUE) ||
                                           ((s_Dcm_idxDidIndexType_st.dataRange_b==FALSE) &&
                                             ((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] == NULL_PTR)||
                                              ((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR) &&
                                               (IsDIDAvailFnc_u8 == E_OK)))))
#endif
                                        {
                                            /* If the identifier is supported in the current session level */
                                            if ((Dcm_DsldGetActiveSessionMask_u32() & dataSessionMask_u32) != 0x0uL)
                                            {
                                                /* If the identifier is supported in the current security level */
                                                if ((Dcm_DsldGetActiveSecurityMask_u32() & dataSecurityMask_u32) != 0x0uL)
                                                {
                                                    /*Check if condition read for the DID is fine*/
                                                    s_Dcm_idxDidIndexType_st.dataopstatus_b=s_Dcm_DspCondChkRdOpStatus_u8;

                                                    dataCondChkRetVal_u8=Dcm_RdpiIsDidCondtionChkReadSupported(&s_Dcm_idxDidIndexType_st);

                                                    if(E_OK==dataCondChkRetVal_u8)
                                                    {
#if (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF)
                                                     /*Check if the DID is range or not, if range do not check for Dynamic did*/
                                                        if(s_Dcm_idxDidIndexType_st.dataRange_b!=TRUE)
                                                        {
                                                            /*Check if the Did is Dynamically Defined DID or not*/
                                                            if( ptrDidConfig->dataDynamicDid_b!=FALSE)
                                                            {
                                                                if(E_OK==Dcm_DspGetIndexOfDDDI_u8((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u),&(s_Dcm_idxDidIndexType_st.idxIndex_u16)))
                                                                {
                                                                    if(Dcm_DDDIBaseConfig_cast[s_Dcm_idxDidIndexType_st.idxIndex_u16].dataDDDIRecordContext_pst->nrCurrentlyDefinedRecords_u16==0)
                                                                    {
                                                                        *dataNegRespCode_u8=DCM_E_REQUESTOUTOFRANGE;
                                                                    }
                                                                }
                                                            }
                                                        }
#endif

                                                        if(*dataNegRespCode_u8==0x00)
                                                        {
                                                            /* Loop through the scheduler table to identify if the periodic identifier is already active */
                                                            for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER ;idxIndex_u8++)
                                                            {
                                                                /* If the requested identifier is already an active identifier scheduled in the scheduler table, do nothing */
                                                                if((Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16 == (pMsgContext->reqData[s_idxLoop_qu32]|0xF200u)) && (Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION))
                                                                {
                                                                    /*Set the flag for valid Id is to TRUE*/
                                                                    isValidId_b=TRUE;
                                                                    break;
                                                                }
                                                            }
                                                            /* If the identifier is not currently active */
                                                            if(idxIndex_u8==DCM_CFG_MAX_DID_SCHEDULER)
                                                            {
                                                                /* Increment the counter indicating the number of supported identifiers not present in the scheduler table */
                                                                s_nrPeriodicId_u8++;
                                                                /*Set the flag for valid Id is to TRUE*/
                                                                isValidId_b=TRUE;
                                                            }
                                                        }
                                                        /*Set the opstatus variable to initial*/
                                                        s_Dcm_DspCondChkRdOpStatus_u8=DCM_INITIAL;
                                                    }
                                                    else if(DCM_E_PENDING==dataCondChkRetVal_u8)
                                                    {
                                                        /*Do nothing here*/
                                                        s_Dcm_DspCondChkRdOpStatus_u8=DCM_PENDING;
                                                        retVal_u8=DCM_E_PENDING;
                                                    }
                                                    /*Conditions not correct for read**/
                                                    else
                                                    {
                                                        if(s_Dcm_idxDidIndexType_st.dataNegRespCode_u8==0x00)
                                                        {
                                                            /*Conditions not correct*/
                                                            *dataNegRespCode_u8=DCM_E_CONDITIONSNOTCORRECT;
                                                        }
                                                        else
                                                        {
                                                            /*Application has already set the NRC, transmit the same NRC*/
                                                            *dataNegRespCode_u8=s_Dcm_idxDidIndexType_st.dataNegRespCode_u8;
                                                        }
                                                        /*Set the opstatus variable to initial*/
                                                        s_Dcm_DspCondChkRdOpStatus_u8=DCM_INITIAL;
                                                    }
                                                }
                                                /* Set NRC 0x33 if any of the supported identifier is not allowed in the current security level */
                                                else
                                                {
                                                    *dataNegRespCode_u8 = DCM_E_SECURITYACCESSDENIED;
                                                    break;
                                                }
                                            }
                                        }
                                    }
                                }
                                if(*dataNegRespCode_u8 ==0x00)
                                {
                                    /* Check if atleast one PID is supported in active session and  number of active
                                     * identifiers + number of new supported identifiers does not exceed the maximum allowed scheduler limit */
                                     /*Check if the flag for ValidId is set to TRUE*/
                                    if((isValidId_b!=FALSE) && ((s_nrPeriodicId_u8+Dcm_NumOfActivePeriodicId_u8)<=DCM_CFG_MAX_DID_SCHEDULER))
                                    {
                                        Dcm_stDspRdpiState_en = DCM_DSP_RDPI_CHECKPERMISSION;
                                        s_nrPeriodicId_u8 = 0x00;
                                    }
                                    /* Send NRC 0x31 since no pid is supported in active session or the supported PID
                                     * cannot be scheduled since scheduler is busy */
                                    else
                                    {
                                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                                    }
                                }
                            }
                            /*Scheduler is not free, send NRC0x31*/
                            else
                            {
                                *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                            }
                        }
                    }
                    /* Transmission mode requested by the ECU is not supported, trigger NRC31 */
                    else
                    {
                        *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                    }
                }
                else
                {
                    /* maximum length is incorrect , NRC0x13 is triggered in case of ISO14229-01 2013-03 edition, else NRC0x31*/
#if(DCM_CFG_RDPIISOVERSION==DCM_ISO14229_1_2013_03)
                    *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
#else
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
#endif
                }
            }
            else
            {   /* minimum length is incorrect */
                *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
            }
        }
        /* Check for permissions from application to process the eventType sent from tester */
        if(Dcm_stDspRdpiState_en == DCM_DSP_RDPI_CHECKPERMISSION)
        {
            /* Copy transmission mode to local variable */
            dataTransmissionMode_u8 = pMsgContext->reqData[DCM_DSP_RDPI_POSTXMODE];
            /* If the transmission mode is sendAtSlowRate */
            if(dataTransmissionMode_u8 == DCM_DSP_RDPI_SLOW_RATE)
            {
                dataOverflowValue_en=DCM_RDPI_SLOW_RATE;
            }
            /* If the transmission mode is sendAtMediumRate */
            else if(dataTransmissionMode_u8 == DCM_DSP_RDPI_MEDIUM_RATE)
            {
                dataOverflowValue_en=DCM_RDPI_MEDIUM_RATE;
            }
            /* If the transmission mode is sendAtFastRate */
            else if(dataTransmissionMode_u8 == DCM_DSP_RDPI_FAST_RATE)
            {
                dataOverflowValue_en=DCM_RDPI_FAST_RATE;
            }
            /* If the transmission mode is stopSending */
            else
            {
                dataOverflowValue_en = DCM_RDPI_NO_TRANMISSION;
            }
            /* If the transmission mode is stopSending */
            if(dataTransmissionMode_u8 == DCM_DSP_RDPI_STOP_SENDING)
            {
                /* If there are no identifiers in the request,i.e, to stop all the transmissions */
                if(pMsgContext->reqDataLen == 0x01u)
                {
                    for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                    {
                        /*Reset the RDPI state variables*/
                        Dcm_ResetRdpiStateVariables(idxIndex_u8,DCM_RDPI_NO_TRANMISSION,(uint16)0x00,(uint16)0x00,(uint32)0x00,FALSE);
                    }
                    Dcm_NumOfActivePeriodicId_u8=0x00;
                }
                /* If there is at least one identifier in the request */
                else
                {
                    /* Loop through the identifiers in the request */
                    for(s_idxLoop_qu32=1;s_idxLoop_qu32 < (pMsgContext->reqDataLen);s_idxLoop_qu32++)
                    {
                        /* Loop through the identifiers in the periodic scheduler */
                        for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                        {
                            if((Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16 == ((pMsgContext->reqData[s_idxLoop_qu32]|0xF200u))) && (Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en!=DCM_RDPI_NO_TRANMISSION))
                            {
                                /*Reset the RDPI state variables*/
                                Dcm_ResetRdpiStateVariables(idxIndex_u8,DCM_RDPI_NO_TRANMISSION,(uint16)0x00,(uint16)0x00,(uint32)0x00,FALSE);
                                Dcm_NumOfActivePeriodicId_u8--;
                                break;
                            }
                        }
                    }
                }
                /* Reset the state machine */
                Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
            }
            else
            {
                /* Loop through the identifiers in the request */
                for(s_idxLoop_qu32=1;s_idxLoop_qu32 < (pMsgContext->reqDataLen);s_idxLoop_qu32++)
                {
                    /* Check if the DID sent from tester is configured in Server */
                    if(E_OK == Dcm_GetIndexOfDID((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u), &s_Dcm_idxDidIndexType_st))
                    {
                        /*Check if Did is range did or not*/
                        if(s_Dcm_idxDidIndexType_st.dataRange_b==FALSE)
                        {
                            /*DID is normal DID and not range DID*/
                            ptrDidConfig = &Dcm_DIDConfig[s_Dcm_idxDidIndexType_st.idxIndex_u16];
                        }
#if(DCM_CFG_DSP_NUMISDIDAVAIL>0)

						if(*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR)
						{
							  IsDIDAvailFnc_u8 = (*(IsDIDAvailFnc_pf)(Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16]))((uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u));
						}
                      
                        /* Check if the DID is supported in current variant */

                        if(((s_Dcm_idxDidIndexType_st.dataRange_b==FALSE))&&((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] == NULL_PTR)||((*Dcm_DIDIsAvail[ptrDidConfig->idxDIDSupportedFnc_u16] != NULL_PTR) && (IsDIDAvailFnc_u8==E_OK))))
#endif
                        {
                            s_nrPeriodicId_u8++;
                            /* Loop through the identifiers in the periodic scheduler */
                            for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                            {

                                /* If the identifier is already added in the scheduler table */
                                if(Dcm_PeriodicInfo_st[idxIndex_u8].dataId_u16 == (pMsgContext->reqData[s_idxLoop_qu32]|0xF200u))
                                {
                                    /* If the identifier is currently not active */
                                    if(Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en==DCM_RDPI_NO_TRANMISSION)
                                    {
                                        Dcm_NumOfActivePeriodicId_u8++;
                                    }
                                    /* Update the overflow counter,idxIndex_u8 of the identifier and reset the timer counter */
                                    Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en= dataOverflowValue_en;
                                    Dcm_PeriodicInfo_st[idxIndex_u8].cntrTime_u32=1;
                                    break;
                                }
                            }
                            /* If the identifier is not found in the scheduler table */
                            if(idxIndex_u8==DCM_CFG_MAX_DID_SCHEDULER)
                            {
                                /* Loop through the entire scheduler table and find the first inactive identifier and update the new identifier */
                                for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_MAX_DID_SCHEDULER;idxIndex_u8++)
                                {
                                    if(Dcm_PeriodicInfo_st[idxIndex_u8].dataOverflowValue_en==DCM_RDPI_NO_TRANMISSION)
                                    {
                                        /* Update the identifier, idxIndex_u8 to the configuration table, overflow counter and timer counter */
                                        /* Update the number of active periodic identifiers in the scheduler table */
                                        Dcm_ResetRdpiStateVariables(idxIndex_u8,dataOverflowValue_en,(uint16)(pMsgContext->reqData[s_idxLoop_qu32]|0xF200u),
                                                                    s_Dcm_idxDidIndexType_st.idxIndex_u16,(uint32)0x01,s_Dcm_idxDidIndexType_st.dataRange_b);
                                        Dcm_NumOfActivePeriodicId_u8++;
                                        break;
                                    }
                                }
                            }
                        }
                    }
                    else
                    {
                        /* Do nothing.Proceed to the next identifier in the request */
                    }
                }
                /* If none of the identifiers in the request are valid in the current conditions */
                if(s_nrPeriodicId_u8 ==0x00)
                {
                    *dataNegRespCode_u8 = DCM_E_REQUESTOUTOFRANGE;
                }
                if((s_idxLoop_qu32 == pMsgContext->reqDataLen)&& (*dataNegRespCode_u8==0x00))
                {
                    /* Reset the state machine */
                    Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
                }
            }
            /* If State machine is in the INIT state  */
            if(Dcm_stDspRdpiState_en == DCM_DSP_RDPI_INIT)
            {
                /* Set the response data length to 0 as response consists of only the response identifier */
                pMsgContext->resDataLen=0x00;
                retVal_u8=E_OK;
            }
        }
        /* If negative response code is set */
        if(*dataNegRespCode_u8 != 0x0)
        {
            /* Reset RDPI state machine */
            Dcm_stDspRdpiState_en = DCM_DSP_RDPI_INIT;
            retVal_u8=E_NOT_OK;
        }
    }
    return retVal_u8;
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
