/* BASDKey_start */

/* BASDKey_end */
/* Administrative Information (automatically filled in)
* $Domain____:BASD$
* $Namespace_:\Comp\Dcm$
* $Class_____:C$
* $Name______:DcmCore_Main_Init$
* $Variant___:AR40.11.0.0$
* $Revision__:0$
**********************************************************************************************************************
</BASDKey>*/

#include "DcmCore_Main_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_Init : Initialisation of DCM module
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Init(void)
{
    VAR(PduIdType,AUTOMATIC) idxPduIndex_u8;
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
    VAR(uint16_least,AUTOMATIC)                                     idxLoop_qu16;
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) && (DCM_CFG_NUM_IOCBI_DIDS != 0x00u))
    VAR(uint16  ,AUTOMATIC) idxDid_u16;
    VAR(uint16  ,AUTOMATIC) idxSig_u16;
    VAR(uint16  ,AUTOMATIC) cntrIocbiDid_u16 = 0;
#endif
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))
    VAR (Dcm_RestoreDddiReturn_ten, AUTOMATIC) dataRetValFromNvMStorage_u8;  /* Local variable to store the return value from the NvM storage/Clear */
    VAR (uint32, AUTOMATIC) nrNumOfDddIds;  /* Local variable to store the return value from the NvM storage/Clear */
    VAR (uint32,AUTOMATIC) idxLoop_u32; /* Local variable to loop through the DDDIs configured */
#endif

    #if((DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))

    #if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

    #endif
    #endif
    #if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;
    P2CONST(Dcm_Dsld_protocol_tableType, AUTOMATIC, DCM_INTERN_CONST) adrProtocol_pcst;
    #endif
    #if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_EcuStartModeType,AUTOMATIC) dataRetGetProgCond_u8;
    #endif
    VAR(uint8,AUTOMATIC)idxIndex_u8;
    #if((DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))

    #if(DCM_CFG_DSP_ROEDID_ENABLED!=DCM_CFG_OFF)

    #endif
    #endif


    /* get the pointer from configuration, then store them in global variable */
    Dcm_DsldProtocol_pcst      = Dcm_Dsld_Conf_cs.protocol_table_pcs;
    Dcm_DsldRxTable_pcu8       = Dcm_Dsld_Conf_cs.ptr_rxtable_pca;
    Dcm_DsldConnTable_pcst     = Dcm_Dsld_Conf_cs.ptr_conntable_pcs;
    Dcm_DsldSessionTable_pcu8 = Dcm_Dsld_Conf_cs.session_lookup_table_pcau8;
    /* set the session as default session */
    Dcm_DsldGlobal_st.idxActiveSession_u8 = 0x0u;
    Dcm_CC_ActiveSession_u8 =  DCM_DEFAULT_SESSION;

    /* set the default session time */
    /* Spin lock Dcm_DsldTimer_NoNest is not needed here as Dcm_Init is called in Init context */
    Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;
    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
    /* Set to active diagnostics mode*/
    Dcm_ActiveDiagnosticState_en = DCM_COMM_ACTIVE;
    /* Appl function to change the reference to the rx table*/
    DcmAppl_DcmUpdateRxTable();
    /*Initialize the variable to FALSE*/
    Dcm_isInitialised_b = FALSE;
    /* Initialize to  DCM_NO_ACTIVE_PROTOCOL (0x0C) as no protocol will be active */
    Dcm_CurProtocol_u8 = DCM_NO_ACTIVE_PROTOCOL;
    /* Inititalze this Flag to FALSE as no StopProtocol is called */
    Dcm_StopProtocolflag_b = FALSE;
    /* Call the API to reset the flag indicating a Reset To Default Session request by application */
    Dcm_DslDsdResetRTDRequestFlag();

    /* Initialize the service table pointer to the first service table. This is done only for initialization */
    Dcm_DsldSrvTable_pcst = Dcm_Dsld_Conf_cs.sid_table_pcs[0].ptr_service_table_pcs;

    /* Initialize the required global variables */
#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
    /* Initialise Security Access Global Timer */
    Dcm_Dsp_SecaGlobaltimer_u32 = 0x0;
#endif
#endif
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF))
    /*Initializing DcmDsp_RoutineStatusArray ;ie setting the status of all routines to default value. */
    for(idxLoop_qu16 = 0;idxLoop_qu16<DCM_CFG_RC_NUMRIDS;idxLoop_qu16++)
    {
        Dcm_RoutineStatus_aen[idxLoop_qu16] = DCM_ROUTINE_IDLE;
    }
#endif
    /*Initialising Dcm_DsldGlobal_st.active_commode_e.ComMState */
    for(idxIndex_u8 = 0;idxIndex_u8<DCM_NUM_COMM_CHANNEL;idxIndex_u8++)
    {
        Dcm_active_commode_e[idxIndex_u8].ComMState =   DCM_DSLD_NO_COM_MODE;
        Dcm_active_commode_e[idxIndex_u8].ComMChannelId= Dcm_Dsld_ComMChannelId_acu8[idxIndex_u8];
    }


    Dcm_DsldGlobal_st.stDsdState_en         =  DSD_IDLE;
    /* Multicore: No lock needed here as Dsl state is an atomic operation and there will not be any parallel access during INIT */
    Dcm_DsldGlobal_st.stDslState_en         =  DSL_READY_FOR_RECEPTION;
    /*Reset the Communication or protocol active status*/
    Dcm_DsldGlobal_st.flgCommActive_b       =  FALSE;
    Dcm_DsldGlobal_st.idxCurrentProtocol_u8 =  0x00u;
    Dcm_DsldGlobal_st.nrActiveConn_u8      =  0x00u;
    /*Reset the Application triggered wait pend status*/
    Dcm_DsldTransmit_st.flgApplWaitPend_b   =  FALSE;
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_DsldGlobal_st.adrBufferPtr_pu8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_buffer1_pa;
    /* Initializing the buffer index to 1 so that it indices to the first buffer */
    Dcm_QueueStructure_st.idxBufferIndex_u8 = 1;
    /* Setting the Queue state to IDLE */
    Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;
#endif

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
    if ( Dcm_ActiveConfigSet_Ptr != NULL_PTR )
    {   /*Check if the configsetid passed is  valid*/
        if((Dcm_ActiveConfigSet_Ptr->ConfigSetId) > DCM_PRV_MAXNUM_OF_CONFIG)
        {
            /* Invalid ConfigSetID switch to default config set which here is Dcm_ConfigType_dataSetName1*/
            Dcm_ActiveConfiguration_u8 = 1 ;
        }
        else
        {
            /* Initialize the Dcm_ActiveConfiguration_u8 variable which will hold the bit mask for current active config */
            Dcm_ActiveConfiguration_u8 = (1 << (Dcm_ActiveConfigSet_Ptr->ConfigSetId)) ;
        }
    }
    else
    {
        /* If Configptr is a null pointer,set active config Set global variable to be Default Config Set i.e. Dcm_ConfigType_dataSetName1 */
        Dcm_ActiveConfiguration_u8 = 1 ;
    }
#endif

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    /* Make these Rx pdu id invalid */
    Dcm_DsldGlobal_st.dataNewRxPduId_u8      =  0xff;
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    Dcm_DsldGlobal_st.dataPassRxPduId_u8     =  0xff;
#endif
    /* Reset the state */
    Dcm_DsldGlobal_st.stDslPreemptionState_en = DSL_READY_FOR_RECEPTION;
#endif

    /*Initialisation of timer variables */
#if (DCM_CFG_OSTIMER_USE != FALSE)
    Dcm_P2OrS3StartTick_u32 = 0x00u;
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    Dcm_RoerdpiStartTick_u32 = 0x00u;
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_PagedBufferStartTick_u32 = 0x00u;
#endif
    Dcm_CurrTick_u32 = 0x00u;
#endif

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    /* Paged buffer transmission is off */

    Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;
#endif

     /* Initialisation of ROE and RDPI  Part */
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    /* Get the pointer to protocol array */
    adrProtocol_pcst = Dcm_DsldProtocol_pcst;

    /* Call the service ini of all ROE and RDPI service table */
    for(idxIndex_qu8= DCM_CFG_NUM_PROTOCOL; idxIndex_qu8!=0x00u; idxIndex_qu8--)
    {
        #if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        if(adrProtocol_pcst->roe_info_pcs != NULL_PTR)
        {
            /* Call initialisation of all services */
            Dcm_DsldCallServiceIni(adrProtocol_pcst->roe_info_pcs->servicetable_Id_u8);
        }
        #endif

        #if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
        if(adrProtocol_pcst->rdpi_info_pcs != NULL_PTR)
        {
            Dcm_DsldPeriodicSchedulerIni();
        }
        #endif

        /* Go to next protocol */

        adrProtocol_pcst++;
    }

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)


#if(DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF)
    Dcm_RestoreROEEvents();
#endif
#endif

    #if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    Dcm_DsdRoe2State_en = DSD_IDLE;
    #endif
#endif

    /* Initialisation of structure used for cooperative scheduler */
    DCM_DSLD_COOPSCHEDULER_INIT()


#if ((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
    #if (DCM_CFG_OSTIMER_USE != FALSE)
    /* Reset the tick value */
    Dcm_SysPrevTick_u32 = 0x0;
    #endif
#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
    /* Call the API to restore the information for WARM start */
    dataRetGetProgCond_u8 = Dcm_GetProgConditions(&Dcm_ProgConditions_st);
    /* Check for the WARM START  */
    if(dataRetGetProgCond_u8 == DCM_WARM_START)
    {
        /*Initialize the variable to the value TRUE*/
        Dcm_ReadyForBoot_b = TRUE;

        if ( (( Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE ) || ( Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE )) && (Dcm_ReadyForBoot_b != FALSE) )
        {
            /* Api to check whether ComM_Dcm_ActiveDiagnostic needs to be called or not*/
            Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_GetActiveConnectionIdx_u8()].channel_idx_u8].ComMChannelId);
        }
    }
    else
    {
        /*Initialize the variable to the value FALSE*/
        Dcm_ReadyForBoot_b = FALSE;
        Dcm_ProgConditions_st.StoreType       = DCM_NOTVALID_TYPE;
    }
#endif

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF &&  (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
    /* Call DSP function to load the Delay count values of Security levels */
    Dcm_Dsp_RestoreDelayCount();
#if (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    Dcm_Dsp_SecaClearSeed();
#endif
#endif
#endif
    /* Restore the SECA timer for loading the SECA timers */
    Dcm_DslDsdRestoreSecaTimer();
#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_IOCBI_ENABLED != DCM_CFG_OFF) && (DCM_CFG_NUM_IOCBI_DIDS != 0x00u))
    /*Initialize the IOCBI DcmDsp_IocbiStatus_array */
    /*Loop through the complete DID structure to determine the index of all the IOCBI dids*/
for(idxDid_u16=0; idxDid_u16<Dcm_DIDcalculateTableSize_u16(); idxDid_u16++)
{
    for(idxSig_u16=0; idxSig_u16<Dcm_DIDConfig[idxDid_u16].nrSig_u16; idxSig_u16++)
    {
        /*  Checking if the DID is meant for IO Control by checking if the session configured is not 0x00 */
        if((Dcm_DIDConfig[idxDid_u16].adrExtendedConfig_pcst->dataSessBitMask_u32!=0x00u) && (Dcm_DspDid_ControlInfo_st[Dcm_DspDataInfo_st[Dcm_DIDConfig[idxDid_u16].adrDidSignalConfig_pcst[idxSig_u16].idxDcmDspDatainfo_u16].idxDcmDspControlInfo_u16].idxDcmDspIocbiInfo_u16>0))
        {
            break;
        }
    }
    if(idxSig_u16<Dcm_DIDConfig[idxDid_u16].nrSig_u16)
    {
/*Store the index of IOCBI did from Dcm_DIDConfig structure*/
        DcmDsp_IocbiStatus_array[cntrIocbiDid_u16].idxindex_u16 = idxDid_u16;
        DcmDsp_IocbiStatus_array[cntrIocbiDid_u16].IocbiStatus_en = DCM_IOCBI_IDLESTATE;
        cntrIocbiDid_u16++;
    }

}
/*By the end of this for loop it is expected that all the indexes of IOCBI DIDs are stored and status is saved.*/
#endif

    /* Initialisation of SID array and array to indicate if a Func TP request was received for each RXPDU */
    for(idxPduIndex_u8=0x0; idxPduIndex_u8 < DCM_CFG_NUM_RX_PDUID;idxPduIndex_u8++)
    {
        /* Default value is set */
        /* Multiocore: No lock needed as there cannot be parallel access during INIT */
        Dcm_DslDsdRxPduArray_ast[idxPduIndex_u8].Dcm_DsldSId_u16   = (uint16)0xFFFF;
        /*Func TP request was not received for each RXPDU */
        Dcm_DslDsdRxPduArray_ast[idxPduIndex_u8].Dcm_DsldFuncTp_b      = FALSE;
    }

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
    Dcm_isFirstReponseSent_b = FALSE;
#endif

#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DYNAMICALLYDEFINEIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DDDISTORINGTONVRAM_ENABLED != DCM_CFG_OFF))
    /*Check if Dcm is initialized or not */
    if(Dcm_isInitialised_b == FALSE)
    {
        /* restoring the DDDIDs from NvM */
        nrNumOfDddIds = Dcm_DddiCalculateTableSize_u16();
        /* restore the DDDIDs */
        for(idxLoop_u32 = 0; idxLoop_u32<nrNumOfDddIds; idxLoop_u32++)
        {
            dataRetValFromNvMStorage_u8 = DcmAppl_DcmReadDddiFromNvM(&Dcm_DDDIBaseConfig_cast[idxLoop_u32],
                                          Dcm_DDDIBaseConfig_cast[idxLoop_u32].dataDddId_u16);
            if(dataRetValFromNvMStorage_u8 == DCM_DDDI_READ_NOT_OK)
            {
                /* reporting the DET error as the read is not successful */
                DCM_DET_ERROR(DCM_DDDI_ID , DCM_E_NO_READ_ACCESS )
            }
        }
    }
#endif

    /* Variable Set to TRUE to indicate that Dcm is initialised and can accept tester requests */
    Dcm_acceptRequests_b= TRUE;
    /**Donot add any code below Dcm_acceptRequests_b=TRUE, whatever code needs to be added has to be done above this
     * statement, this is necessary since flag Dcm_acceptRequests_b is used in the Dcm_MainFunction() api to ensure
     * Dcm_Init and Dcm_Mainfunction does not run in parallel*/

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/* FC_VariationPoint_START */
/*<BASDKey>
**********************************************************************************************************************
* $History___:
*
* AR40.11.0.0; 0     19.10.2015 CRA4KOR
*   CSCRM00892537
*
* AR40.10.0.0; 7     14.07.2015 WUG3ABT
*   Checkout by wug3abt
*
* AR40.10.0.0; 6     07.07.2015 PJR4KOR
*   CSCRM00952156
*
* AR40.10.0.0; 5     02.07.2015 CRA4KOR
*   CSCRM00577882
*
* AR40.10.0.0; 4     01.07.2015 GET1COB
*   CSCRM00688177
*
* AR40.10.0.0; 3     17.06.2015 GET1COB
*   CSCRM00683208
*
* AR40.10.0.0; 2     14.05.2015 CRA4KOR
*   CSCRM00737827
*
* AR40.10.0.0; 1     24.04.2015 PJR4KOR
*   CSCRM00364395
*
* AR40.10.0.0; 0     13.02.2015 GET1COB
*   CSCRM00747026
*
* AR40.9.0.0; 4     30.12.2014 GET1COB
*   CSCRM00724044
*
* $
**********************************************************************************************************************
</BASDKey>*/

/* FC_VariationPoint_END */
