

#include "DcmCore_DslDsd_Inf.h"
#include "DcmCore_Main_Inf.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Definition of buffer which is used to send wait pend response */
VAR(uint8,DCM_VAR) Dcm_DsldWaitPendBuffer_au8[8];
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Definition of timing structure, which holds the current timing */
VAR(Dcm_DsldTimingsType_tst,DCM_VAR) Dcm_DsldTimer_st;
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
VAR(Dcm_QueueStructure_tst,DCM_VAR) Dcm_QueueStructure_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Definition of pointer to service table */
P2CONST(Dcm_Dsld_ServiceType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldSrvTable_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_Dsld_KwpTimerServerType,DCM_VAR) Dcm_DsldKwpReqTiming_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(boolean,DCM_VAR) Dcm_DsldGenRejectSent_b; /*Variable to indicate max number of configured NRC 0x78 is transmitted */
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

static VAR(uint8,DCM_VAR) s_TempNrc_u8; /* Variable used to send NegativeResponseCode Parameter in case of Dcm Cancellation */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(StatusType,DCM_VAR) Dcm_P2OrS3TimerStatus_uchr; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
/**
 **************************************************************************************************
 * Dcm_ProvideFreeBuffer : The function to provide the buffer when there is a new request. This function provides the buffer as the index if it is a normal request. If it is a queuing request, it will switch the index and provides the other buffer which is free. So that the queuing of the request can happen in this buffer
 *
 * \param           idxProtocolIndex_u8: Active protocol
                    isQueuedReq_b  : TRUE - This function is called while starting the queue
                                     FALSE -  This function is called during the reception of the normal request
 *
 *
 * \retval          uint8*   address of the free buffer
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA),DCM_CODE) Dcm_ProvideFreeBuffer(VAR(uint8,AUTOMATIC) idxProtocolIndex_u8,VAR(boolean,AUTOMATIC) isQueuedReq_b)
{
    /* It is for the queued request switch the buffer */
    if(isQueuedReq_b == TRUE)
    {
        if(Dcm_QueueStructure_st.idxBufferIndex_u8 == 1)
        {
            Dcm_QueueStructure_st.idxBufferIndex_u8 = 2;
        }
        else
        {
            Dcm_QueueStructure_st.idxBufferIndex_u8 = 1;
        }
    }
    /* return the buffer based on the index */
    if(Dcm_QueueStructure_st.idxBufferIndex_u8 ==1)
    {
        return (Dcm_DsldProtocol_pcst[idxProtocolIndex_u8].rx_buffer1_pa);
    }
    else
    {
        return (Dcm_DsldProtocol_pcst[idxProtocolIndex_u8].rx_buffer2_pa);
    }
}

/**
 **************************************************************************************************
 * Dcm_GetActiveBuffer : Function to retrieve the active buffer
 *
 * \param           adrReturnBuffer_pu8: The buffer pointer.
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA),DCM_CODE) Dcm_GetActiveBuffer(void)
{
    /* return the buffer pointer which has the request to be processed */
    return Dcm_DsldGlobal_st.adrBufferPtr_pu8;
}
#endif /* #if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF) */


/**
 **************************************************************************************************
 * Dcm_DsldFrameIntermediateResponse : Frame the wait pend or general reject response
 *
 * \param           dataNegativeResponse_u8: NRC
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_DsldFrameIntermediateResponse(VAR(uint8,AUTOMATIC) dataNegativeResponse_u8)
        {
    /* change the state to wait for tx confirmation */
    /* Multicore: No lock needed here as Dsl state is an atomic operation */
    /* Also if the state is changed here the changes to the Dsl state cannot happen from any other place */
    Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_CONFIRMATION;

    /* frame intermediate Negative response based on the NRC*/
    Dcm_DsldWaitPendBuffer_au8[0] = DCM_NEGRESPONSE_INDICATOR;
    Dcm_DsldWaitPendBuffer_au8[1] = Dcm_DsldGlobal_st.dataSid_u8;
    Dcm_DsldWaitPendBuffer_au8[2] = dataNegativeResponse_u8 ;

    /* update data in PDU structure */
    Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DsldWaitPendBuffer_au8;
    Dcm_DsldPduInfo_st.SduLength = 0x03;
        }


/**
 **************************************************************************************************
 * Dcm_DsldDslStateMachine : State machine of DSL. This function is called in Dcm_MainFunction()
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DsldDslStateMachine(void)
{
    P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA) adrRxBuffer_pu8;
    /* Pointer to service table */
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrServiceTable_pcst;
    VAR(uint8,AUTOMATIC) idxActiveSession_u8;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    VAR(uint16,AUTOMATIC) dataPageBufLen_u16; /* Local variable to calculate the available page length */
#endif
    VAR(Std_ReturnType,AUTOMATIC) stStartProtocol_u8; /* return value of Dcm_StartProtocol*/
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNrc_u8;          /* Variable to store error code */
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    /* Index of KWP timing structure */
    VAR(uint8,AUTOMATIC) idxKwpTiming_u8;
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(uint8,AUTOMATIC) idxProtocol_u8;
    VAR(uint8,AUTOMATIC) idxConnection_u8;
    VAR(Std_ReturnType,AUTOMATIC) stCancelTx_u8;
    VAR(boolean,AUTOMATIC) flgRoeRdpiOn_b;
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    /* Avoid STOP_PROTOCOL to STOP_ROE Fall through */
    VAR(boolean,AUTOMATIC) flgPersistRoe_b;
#endif
#endif

    VAR(Dcm_DsldDslStatesType_ten,AUTOMATIC) stDslState_en;
    VAR(Dcm_DsldDslStatesType_ten,AUTOMATIC) DslTempState_e;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    stCancelTx_u8 = E_NOT_OK;  /* Set the cancel transmit status to E_NOT_OK */
    /*Initialize the flag for Roe-Rdpi request to value False */
    flgRoeRdpiOn_b = FALSE;
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    /*initialize the flag PersistRoe to value false */
    flgPersistRoe_b = FALSE;
#endif
#endif


    /* Lock required here to prevent inconsistency due to reception of another high prio request */
    SchM_Enter_Dcm_Global_NoNest();
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

    /* Check whether the high priority protocol has arrived */
    if(Dcm_DsldGlobal_st.stDslPreemptionState_en == DSL_STOP_PROTOCOL)
    {
        /* Call the Cancel Transmit function to cancel ongoing transmission in Lower layers */
        /* Release lock temporarilty as there are external calls */
        SchM_Exit_Dcm_Global_NoNest();
        stCancelTx_u8 = Dcm_CancelTransmit_u8();
        /* Take back the lock */
        /* Multicore: Lock necessary for DSL state as there is a possible parallel update during protocol preemption */
        SchM_Enter_Dcm_Global_NoNest();

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
        if(Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED)
        {
            /* Roe-Rdpi request is under processing. DCM needs to call Tx confirmation for ROE */
            /*Set the flag for Roe-RdpiOn to True */
            flgRoeRdpiOn_b = TRUE;
        }
#else
        (void)flgRoeRdpiOn_b;
#endif

        /* High priority protocol arrived, start new protocol */
        Dcm_DsldGlobal_st.stDslState_en = DSL_STOP_PROTOCOL;

    }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
    else if(Dcm_DsldGlobal_st.stDslPreemptionState_en == DSL_STOP_ROE)
    {
        if(Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED)
        {
            /* Roe-Rdpi request is under processing. DCM needs to call Tx confirmation for ROE */
            /*initialize the flag Persist_Roe is set to value True*/
            flgPersistRoe_b = TRUE;

            /* Call the Cancel Transmit function to cancel ongoing transmission in Lower layers */
            SchM_Exit_Dcm_Global_NoNest();
            stCancelTx_u8 = Dcm_CancelTransmit_u8();
            SchM_Enter_Dcm_Global_NoNest();
        }

        /* If high priority protocol request is arrived, stop ROE */
        Dcm_DsldGlobal_st.stDslState_en = DSL_STOP_ROE;

    }
    else
    {
        /* Clearing MISRA violation */
    }
#endif
#endif /* End of DCM_CFG_PROTOCOL_PREMPTION_ENABLED */
    /* Multicore: No lock needed here as Dsl state is an atomic read operation */
    /* Also even if there is a request received when this code is running, there is no impact on functionality */
    stDslState_en   = Dcm_DsldGlobal_st.stDslState_en;
    SchM_Exit_Dcm_Global_NoNest();



    switch(stDslState_en)
    {
    case DSL_READY_FOR_RECEPTION:

    case DSL_ROETYPE1_RECIEVED:



    {
        /* S3 timer monitored only in non default session */
        /* P3 timer monitored in all session in case of KWP */
        /* Multicore: No lock needed here as Dsl state is an atomic read operation */
        /* Also even if there is a request received when this code is running, there is no impact on functionality */
        DslTempState_e=Dcm_DsldGlobal_st.stDslState_en;
        if((DslTempState_e==DSL_READY_FOR_RECEPTION)||(DslTempState_e==DSL_ROETYPE1_RECIEVED))
        {
            idxActiveSession_u8 = Dcm_DsldGlobal_st.idxActiveSession_u8;
            /*check if Current active session is not in default session and p3 timer is set*/
            if((idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX) || (Dcm_DsldGlobal_st.flgMonitorP3timer_b != FALSE))
            {
                /*Check if data Timeout Monitor flag is not set*/
                if((DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32))== FALSE)
                {

                    DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                }
                else
                {
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
                    /*Check if return value is TRUE*/
                    if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
                    {
                        /*initialize the DCM Comm Active flag to the value False*/
                        Dcm_DsldGlobal_st.flgCommActive_b     = FALSE;

                        /* Indicate to the application that the timeout has occurred*/
                        DcmAppl_P3TimeoutIndication();
                    }
#endif
                    /* Call ComM only during transition from non default session to default session */
                    if (idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX)
                    {
                        /* Indicate to Communication manager that the full communication mode is not required now onwards */
                        ComM_DCM_InactiveDiagnostic (Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
                    }
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
                    /* Call SchM_Switch function */
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                    (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif
                    (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif

                    /* Set the default session and default timing */
                    Dcm_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);

                    /* Reset the bit(P3 time monitoring is not required now onwards)  */

                    Dcm_DsldGlobal_st.flgMonitorP3timer_b = FALSE;

                }
            }
        }
    }
    break;

    case DSL_RECEIVING:
        /* TP is receiving the request */
        break;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    case DSL_STOP_PROTOCOL:

        /* Connection on which request is received */
        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
        there is no parallel writing due to DSL state machine handling */
        idxConnection_u8 = Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8];

        /* protocol of the received Rx PDU id */
        idxProtocol_u8 = Dcm_DsldConnTable_pcst[idxConnection_u8].protocol_num_u8;

#if ( (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) )
        if(Dcm_DsldGlobal_st.flgCommActive_b != FALSE)
        {
            Dcm_ControlDtcSettingExit();
        }
#endif

/* call initialisations of the running service to reset the service of the protocol going to be preempted */
		if((Dcm_DsldGlobal_st.stDsdState_en!=DSD_IDLE) && (Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp != NULL_PTR))
        {
            s_TempNrc_u8 =0x00;
			(void)(*Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].service_handler_fp)(DCM_CANCEL,&Dcm_DsldMsgContext_st,&s_TempNrc_u8);
			Dcm_SrvOpstatus_u8 = DCM_INITIAL;
        }

        /* If DSD calling the service and Paged buffer Tx is on then inform to application */
        if(Dcm_DsldGlobal_st.stDsdState_en == DSD_CALL_SERVICE)
        {
            /* Update this variable to TRUE as StopProtocol will be invoked is case of Protocol Premption */
            Dcm_StopProtocolflag_b = TRUE;
            /* Call API to inform application */
            (void)Dcm_StopProtocol(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8);
        }
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
        else
        {
            /*Check if the paged buffer active flag is set*/
            if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
            {
                /* Update this variable to TRUE as StopProtocol will be invoked is case of Protocol Premption */
                Dcm_StopProtocolflag_b = TRUE;
                (void)Dcm_StopProtocol(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8);

                /* Reset the status of paged buffer */
                /*Set the paged buffer status flag to false*/
                Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;

                Dcm_adrUpdatePage_pfct = NULL_PTR;
            }
        }
#endif

#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        /* This variable will be TRUE when either ROE type1 or RDPI type1 is under processing */
        /*Check if the flag Roe-Rdpi request is set*/
        if(flgRoeRdpiOn_b != FALSE)
        {
            if(Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
            {
                /* Call  ROE confirmation because DCM killing ROE requested service */
               DcmAppl_DcmConfirmation(Dcm_DsldGlobal_st.dataSid_u8,
                        Dcm_DsldMsgContext_st.dcmRxPduId,
                        Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_DsldMsgContext_st.dcmRxPduId].testsrcaddr_u16,
                        DCM_RES_POS_NOT_OK);
            }
        }
#else
        (void)flgRoeRdpiOn_b;
#endif

        /* Update active connection and protocol id */
        Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = idxProtocol_u8;
        Dcm_DsldGlobal_st.nrActiveConn_u8      = idxConnection_u8;


        if(Dcm_DsldGlobal_st.idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX)
        {
            /* Set the default session, default security level and default timing */
            Dcm_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);

        }



        /* Reset the bit to start the protocol */

        Dcm_DsldGlobal_st.flgCommActive_b = FALSE;
        /* Update the request length */
        Dcm_DsldGlobal_st.dataRequestLength_u16  = Dcm_DsldGlobal_st.dataNewdataRequestLength_u16;

        /* Go to next state to start protocol */
        /* Multicore: No lock needed here as Dsl state is written here when Dcm is free after protocol preemption */
        /* Also even if there is a request received when this code is running, there is no impact on functionality */
        Dcm_DsldGlobal_st.stDslState_en = DSL_REQUEST_RECEIVED;
        Dcm_DsldGlobal_st.stDsdState_en = DSD_IDLE;
        /* Reset the state */
        Dcm_DsldGlobal_st.stDslPreemptionState_en = DSL_READY_FOR_RECEPTION;



        /* If the ongoing transmission was cancelled in this state, the new request should not be processed in the
           current cycle as there is a chance that service can finish the processing in the same cycle and
           PduR_Transmit can return E_NOT_OK as transmission of old protocol is under progress */
        if((stCancelTx_u8 == E_OK) &&
                (Dcm_DsldGlobal_st.dataOldtxPduId_u8 == Dcm_DsldConnTable_pcst[idxConnection_u8].txpduid_num_u8))
        {

            DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                    /* Break out of the state machine and the request will be processed in the next DCM cycle */
                    break;
        }
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)
        /*MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3*/
    case DSL_STOP_ROE:
        /*Check if the Persist-Roe flag value is set*/
        if(flgPersistRoe_b != FALSE)
        {
            /* Connection on which request is received */
            /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
           there is no parallel writing due to DSL state machine handling */
            idxConnection_u8 = Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8];

            /* protocol of the received Rx PDU id */
            idxProtocol_u8 = Dcm_DsldConnTable_pcst[idxConnection_u8].protocol_num_u8;

            /* Call  ROE confirmation because DCM killing ROE requested service */
         DcmAppl_DcmConfirmation(Dcm_DsldGlobal_st.dataSid_u8,
                    Dcm_DsldMsgContext_st.dcmRxPduId,
                    Dcm_Dsld_RoeRxToTestSrcMappingTable[Dcm_DsldMsgContext_st.dcmRxPduId].testsrcaddr_u16,
                    DCM_RES_POS_NOT_OK);
            /* Update active connection and protocol id */
            Dcm_DsldGlobal_st.idxCurrentProtocol_u8 = idxProtocol_u8;
            Dcm_DsldGlobal_st.nrActiveConn_u8      = idxConnection_u8;
            /* Update the request length */
            Dcm_DsldGlobal_st.dataRequestLength_u16  = Dcm_DsldGlobal_st.dataPassdataRequestLength_u16;

            /* Go to next state to start protocol */
            /* Multicore: No lock needed here as Dsl state is an atomic operation *
            * Also if the state is changed here the changes to the Dsl state cannot happen from any other place
            * This code is reached during protocol preemption and so no parallel update.
            */
            Dcm_DsldGlobal_st.stDslState_en = DSL_REQUEST_RECEIVED;
            Dcm_DsldGlobal_st.stDsdState_en = DSD_IDLE;
            /* Reset the state */
            Dcm_DsldGlobal_st.stDslPreemptionState_en = DSL_READY_FOR_RECEPTION;


            /* If the ongoing transmission was cancelled in this state, the new request should not be processed in the
           current cycle as there is a chance that service can finish the processing in the same cycle and
           PduR_Transmit can return E_NOT_OK as transmission of old protocol is under progress */
            if((stCancelTx_u8 == E_OK) &&
                    (Dcm_DsldGlobal_st.dataOldtxPduId_u8 == Dcm_DsldConnTable_pcst[idxConnection_u8].txpduid_num_u8))
            {

                DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                    /* Break out of the state machine and the request will be processed in the next DCM cycle */
                    break;
            }
        }
#endif
#endif /* End of DCM_CFG_PROTOCOL_PREMPTION_ENABLED */
        /* MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3  */
    case DSL_REQUEST_RECEIVED:
        /*Check if the DCM Comm Active flag is set*/
        if(Dcm_DsldGlobal_st.flgCommActive_b != FALSE)
        {

        }
        else
        {
            /* Invoke StopProtocol only when there is already a protocol currently running and StopProtol is not already invoked */
            if( (Dcm_CurProtocol_u8 != DCM_NO_ACTIVE_PROTOCOL) && (!Dcm_StopProtocolflag_b))
            {
                /* Call API to inform application */
                (void)Dcm_StopProtocol(Dcm_CurProtocol_u8);
            }

            /* Activate the protocol because this is first request */
            stStartProtocol_u8=Dcm_StartProtocol(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8);
            if(stStartProtocol_u8 == E_OK )
            {

                /* Reset any pending cooperative scheduler request during protocol preemption */
                DCM_DSLD_COOPSCHEDULER_RESET()


                /* Set the service table from protocol table */
                Dcm_DsldGlobal_st.datActiveSrvtable_u8= Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].
                        sid_tableid_u8;

                /* Communication is started */
                /*Initialize the Comm Active Flag value to True*/
                Dcm_DsldGlobal_st.flgCommActive_b = TRUE;

                /* Get the active service table pointer from Sid table*/
                Dcm_DsldSrvTable_pcst = \
                        Dcm_Dsld_Conf_cs.sid_table_pcs[Dcm_DsldGlobal_st.datActiveSrvtable_u8].ptr_service_table_pcs;

                /* Call initialisations of all services */
                DCM_DSLD_COOPSCHEDULER_SHIFTINI(Dcm_DsldGlobal_st.datActiveSrvtable_u8)
                Dcm_DsldCallServiceIni(Dcm_DsldGlobal_st.datActiveSrvtable_u8);

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
                /* Lock is needed here to have P2Max, P3Max and P2StrMax to be consistent as a unit */
                SchM_Enter_Dcm_DsldTimer_NoNest();
                /*Check if retun value is TRUE*/
                if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
                {
                    /* KWP is active. Use KWP session table  */
                    Dcm_DsldSessionTable_pcu8 = Dcm_Dsld_KWPsupported_sessions_acu8;

                    idxKwpTiming_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].
                            timings_idx_u8;
                    /* Set the default timings */
                    Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P2_max_u32;

                    Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_Dsld_default_timings_acs[idxKwpTiming_u8].P3_max_u32;

                    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;
                }
                else
                {
                    /* UDS is active, use UDS session table  */
                    Dcm_DsldSessionTable_pcu8 = Dcm_Dsld_Conf_cs.session_lookup_table_pcau8;

                    /* Set the default session time */
                    Dcm_DsldTimer_st.dataTimeoutP2max_u32    =  DCM_CFG_DEFAULT_P2MAX_TIME;

                    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 =  DCM_CFG_DEFAULT_P2STARMAX_TIME;
                }
                SchM_Exit_Dcm_DsldTimer_NoNest();
#endif
#if(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED!=DCM_CFG_OFF)
                /* Call SchM_Switch function */
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
                (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(RTE_MODE_DcmDiagnosticSessionControl_DEFAULT_SESSION);
#endif
                /* Call the DcmAppl API to inform application regarding session change */
                (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
#endif
                /* Set the default session, default security level and default timing */
                Dcm_SetSesCtrlType(Dcm_DsldSessionTable_pcu8[DCM_DEFAULT_SESSION_IDX]);
                /* Update the variable with the id of the new Requested Protocol */
                Dcm_CurProtocol_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8;
            }
            else
            {
                /* Protocol cannot be started, nrc has to send, get the address of txbuffer*/
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8 = (&(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]))->tx_buffer_pa;

                /* Protocol cannot be started, send nrc 0x22*/
                dataNrc_u8= 0x22;

                /* Set response given by DSD to true */

                Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;
                /* Get Rx buffer*/
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
                adrRxBuffer_pu8 = Dcm_GetActiveBuffer();
#else
                adrRxBuffer_pu8 = (&(Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8]))->rx_buffer1_pa;
#endif
                /* Get the SID from request*/
                Dcm_DsldGlobal_st.dataSid_u8     = adrRxBuffer_pu8[0];
                /* Update Dcm_DsldMsgContext_st*/
                Dcm_DsldMsgContext_st.idContext  = Dcm_DsldGlobal_st.dataSid_u8;
                /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                                   there is no parallel writing due to DSL state machine handling */
                Dcm_DsldMsgContext_st.dcmRxPduId = Dcm_DsldGlobal_st.dataActiveRxPduId_u8;
                Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest = DCM_UDS_TESTER_SOURCE;
                Dcm_DsldMsgContext_st.resDataLen = 0;

                /* Get the request type */
                /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
                                   there is no parallel writing due to DSL state machine handling */
                if(Dcm_DsldGlobal_st.dataActiveRxPduId_u8 >= DCM_INDEX_FUNC_RX_PDUID)
                {
                    Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_FUNCTIONAL_REQUEST;
                }
                else
                {
                    Dcm_DsldMsgContext_st.msgAddInfo.reqType = DCM_PRV_PHYSICAL_REQUEST;
                }
                /* By default make the response type as Positive response */
                Dcm_DsldGlobal_st.stResponseType_en      = DCM_DSLD_POS_RESPONSE;
                /* Change the DSL state */
                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* Also if the state is changed here the changes to the Dsl state cannot happen from any other place due to state machine handling*/
                Dcm_DsldGlobal_st.stDslState_en          = DSL_WAIT_FOR_P2MAX;
                Dcm_DsldGlobal_st.dataActiveTxPduId_u8   = Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].txpduid_num_u8;
                Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0;
                /*Set Dcm application wait pending flag value to false*/
                Dcm_DsldTransmit_st.flgApplWaitPend_b    = FALSE;

                /* Set the negative response*/
                Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,dataNrc_u8);
                Dcm_ProcessingDone ( & Dcm_DsldMsgContext_st);
            }
            /* Update this variable to FALSE as the StopProtocol is already invoked */
            Dcm_StopProtocolflag_b = FALSE;
        }
        /* If communication is active fall into next state */

        if(Dcm_DsldGlobal_st.flgCommActive_b != FALSE)
        {

            /* Communication is active now for UDS request(subsequent requests)*/


            if((DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8)) && (!(DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32))))
            {

                /* Initialise the variable to FALSE */

                Dcm_DsldGenRejectSent_b = FALSE;

                /* Go to next state  */
                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* Also if the state is changed here the changes to the Dsl state cannot happen from any other place due to state machine handling*/
                Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_P2MAX;

                /* The following statement is moved from the case DSL_SEND_WAITPEND */
                Dcm_DsldTransmit_st.stDslNextState_en = DSL_WAIT_FOR_P2MAX;

                /* Indicate to DSD,change the DSD state machine to DSD_VERIFY_DIAGNOSTIC_DATA state */
                Dcm_DsldGlobal_st.stDsdState_en = DSD_VERIFY_DIAGNOSTIC_DATA ;

                /* Initialise the wait pend counter and bit which indicates the arrival of response from service*/
                Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

                /* Get the Tx PDU id */
                Dcm_DsldGlobal_st.dataActiveTxPduId_u8 = \
                        Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].txpduid_num_u8;

                /* Update the sid from the request buffer as the sid value if required to send BUSYREPEAT response from
               DSL_SEND_WAITPEND state even before processing of the request happens in DSD state machine */
                #if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
                Dcm_DsldGlobal_st.dataSid_u8 = *(Dcm_GetActiveBuffer());
#else
                Dcm_DsldGlobal_st.dataSid_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].rx_buffer1_pa[0];
#endif
            }
            /* Check non default session active or not */
            else if(Dcm_DsldGlobal_st.idxActiveSession_u8 != DCM_DEFAULT_SESSION_IDX)
            {
                /*DCM is not in FULL_COMM in NON_DEFAULT session,reject request*/
                DcmAppl_DcmComModeError(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
                /* Set the DSL and DSD state to default state */
                Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
                Dcm_DsldGlobal_st.stDsdState_en      = DSD_IDLE;
                Dcm_DsldGlobal_st.stDslState_en      = DSL_READY_FOR_RECEPTION;
                break;
            }
            /* Check P2 max expired or not */
            else if(DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32))
            {
                /*Trace [SWS_Dcm_01142] */
                /* Unable to move to FULL Communication mode, reject the request */
                DcmAppl_DcmComModeError(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
                /* Set the DSL and DSD state to default state */
                Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
                Dcm_DsldGlobal_st.stDsdState_en      = DSD_IDLE;
                Dcm_DsldGlobal_st.stDslState_en      = DSL_READY_FOR_RECEPTION;
                break;

            }
            /* P2 max not yet over. Stay in this state */
            else
            {

                DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
                /* Give another chance for ComM to go to FULL-COMM, check again in the next proc of Dcm_MainFunction */
                break;
            }
        }
        else
        {
            break;
        }
        /*MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3*/
    case  DSL_WAIT_FOR_P2MAX:


        DCM_TimerProcess(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)

        /* Check P2 max expired or not */
        if(DCM_TimerElapsed(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32))
        {
            /* Fall into next state */
        }
        else
        {
            /* P2 max not yet over. Stay in this state */
            break;
        }
        /* MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3  */
    case  DSL_SEND_WAITPEND:
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
        /* in case the KWP service is under process and if the split response feature is enabled,
         * then the below part shall be reached when the timeout has occured between 2 spilt responses i.e. the first response is sent already
         * and the next response has not been prepared within the time DCM_CFG_SPLITRESPONSETIMEFORKWP.
         * In this case, give the negative confirmation to the application and abort the transmission and free the Dcm state machines */
        if((DCM_IS_KWPPROT_ACTIVE() != FALSE)&&(Dcm_isFirstReponseSent_b!=FALSE))
        {
            Dcm_KWPConfirmationForSplitResp(DCM_RES_POS_NOT_OK);
            Dcm_isFirstReponseSent_b = FALSE;
            break;
        }
        else
#endif
        {
        /* If the request has arrived to trigger the waitpend even before first service call */
        if(Dcm_DsldGlobal_st.stDsdState_en == DSD_VERIFY_DIAGNOSTIC_DATA)
        {
            /* Set the DSL and DSD state to default state */
            Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
            Dcm_DsldGlobal_st.stDsdState_en      = DSD_IDLE;

            /* Frame the Busy repeat response */
            Dcm_DsldFrameIntermediateResponse(DCM_E_BUSYREPEATREQUEST);
            Dcm_DsldSendResponse(& Dcm_DsldPduInfo_st);
            break;
        }
        else
        {
#if (DCM_CFG_MAX_WAITPEND > 0)
            /* Check whether the wait pend count valid or not */
            if((Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < DCM_CFG_MAX_WAITPEND) || (DCM_CFG_MAX_WAITPEND == 0xFFu))
            {
                /* Frame wait pend response */
                Dcm_DsldFrameIntermediateResponse(DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING);

                if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 < 0xFF)
                {
                    /* increment wait pend counter to indicate one wait pend is sent */
                    Dcm_DsldGlobal_st.cntrWaitpendCounter_u8++;
                }

                /*
                 * The following statement was here
                 * Dcm_DsldTransmit_st.stDslNextState_en = DSL_WAIT_FOR_P2MAX;
                 * This is moved under the state DSL_REQUEST_RECEIVED.
                 * Reason : When Dcm_ProcessPage() is called to transmit the first page and SPRB in ON, then transmission
                 * of WAIT PEND is triggered.If PduR_DcmTransmit() gives NOT_OK then stDslState_en  is changed to
                 * DSL_WAIT_FOR_P2MAX. WAIT PEND will be triggered from this place next time , which will overwrite
                 * the stDslNextState_en with  DSL_WAIT_FOR_P2MAX. But the stDslNextState_en is set to DSL_SEND_FINAL_RESPONSE in
                 * Dcm_Processpage(), which should be retailed.
                 */

                /* Trigger wait pend response */
                Dcm_DsldSendResponse(& Dcm_DsldPduInfo_st);
                break;
            }
#endif
        }
       }
    /* MR12 RULE 16.3 VIOLATION: Controlling expression is not and does not end with a 'jump' statement. Execution will fall through. MISRA C:2012 Rule-16.3  */
    case  DSL_SEND_GENERAL_REJECT:

        /* Configured number of wait pend is sent, Now send general reject */
        if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == DCM_CFG_MAX_WAITPEND)
        {

            adrServiceTable_pcst = &Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8];
			if(adrServiceTable_pcst->service_handler_fp != NULL_PTR)
            {
			    s_TempNrc_u8 = 0;
                /* Call service initialisation function based on whether cooperative scheduler is configured */
                DCM_DSLD_COOPSCHEDULER_SHIFTSERVICEINI(adrServiceTable_pcst,&s_TempNrc_u8)
			    /* Re-assign the opstatus to DCM_INITIAL after cancellation */
			    Dcm_SrvOpstatus_u8 = DCM_INITIAL;
            }


            /* index of service table make it zero */
            Dcm_DsldGlobal_st.idxService_u8 = 0x00u;

            /* Response given by DSD itself */

            Dcm_DsldGlobal_st.dataResponseByDsd_b = TRUE;

            /* Reject application triggered response pend */

            Dcm_DsldTransmit_st.flgApplWaitPend_b = FALSE;

            /* Send negative response with NRC service not supported */
            Dcm_SetNegResponse( & Dcm_DsldMsgContext_st ,DCM_E_GENERALREJECT);

            /* Set the variable to indicate NRC 0x10 is set as max number of configured NRC 0x78 reached*/

            Dcm_DsldGenRejectSent_b = TRUE;

#if (DCM_CFG_RBA_DIAGADAPT_SUPPORT_ENABLED != DCM_CFG_OFF)
            /* Call the rba_DiagAdapt API to indicate the trigger of NRC 0x10 from DSL state machine to reset the rba_DiagAdapt */
            rba_DiagAdapt_Confirmation_GeneralReject(Dcm_DsldGlobal_st.dataSid_u8);
#endif
            Dcm_ProcessingDone ( & Dcm_DsldMsgContext_st );
        }
        break;

    case  DSL_SEND_FINAL_RESPONSE:

        /* update data in PDU structure */
        Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DsldTransmit_st.adrTxBuffer_tpu8;

        /* update data length in PDU structure */
        Dcm_DsldPduInfo_st.SduLength = (PduLengthType)Dcm_DsldTransmit_st.dataTxDataLength_u32;

        /* change the state to wait for Tx confirmation */
        /* Multicore: No lock needed here as Dsl state is an atomic operation */
        /* Also if the state is changed here the changes to the Dsl state cannot happen from any other place */
        Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_CONFIRMATION;

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

        /* This is to trigger the PduR for paged buffer transmission */

        if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
        {

            /* Change the state such that DCM should give this Page to TP for next call of Dcm_Provide_TxBuffer()  */
            /* Multicore: No lock needed here as Dsl state is an atomic operation */
            /* Also if the state is changed here the changes to the Dsl state cannot happen from any other place */
            Dcm_DsldGlobal_st.stDslState_en = DSL_DATA_READY;

        }
#endif

        /* This is final response. To indicate that cntrWaitpendCounter_u8 is made as zero */
        Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

        /* After getting the Tx confirmation DSL state changed to DSL_READY_FOR_RECEPTION state */
        Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;

        /* Trigger  response */
        Dcm_DsldSendResponse(& Dcm_DsldPduInfo_st);

        break;

    case  DSL_WAIT_FOR_CONFIRMATION:

        /* wait for Tx confirmation from  PduR */
        break;

    case DSL_DATA_READY:

        /* Service is given the filled page wait for next Dcm_ProvideTxbuffer call */
        break;

    case DSL_WAIT_FOR_DATA:

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
        if(Dcm_DsldGlobal_st.stDsdState_en == DSD_SEND)
        {
            /* Start Paged buffer timeout timer */
            DCM_TimerStart(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32, DCM_PAGEDBUFFER_TIMEOUT,
                    Dcm_PagedBufferStartTick_u32,Dcm_PagedBufferTimerStatus_uchr )

                    /* Call the service in DSD state machine  */
                    Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;

            /* Inform the service to fill the data into page */
            if(Dcm_adrUpdatePage_pfct != NULL_PTR)
            {
                /* Copy the paged buffer length to local variable */
                dataPageBufLen_u16 = (uint16)(Dcm_DsldMsgContext_st.resMaxDataLen+1uL);

                (*Dcm_adrUpdatePage_pfct)(&Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].tx_buffer_pa[2],
                        dataPageBufLen_u16);
            }
        }

#endif
        break;

    case DSL_WAIT_PAGE_TXCONFIRM:

        /* Current page is under TX wait for confirmation from lower layer */
        break;

    default:
         /*Since All the DSL states are handled already , there is nothing to do in Default */
        break;

    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

