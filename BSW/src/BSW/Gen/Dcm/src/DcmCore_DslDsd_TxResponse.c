

#include "DcmCore_DslDsd_Inf.h"


#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(boolean,DCM_VAR) Dcm_DsldSessionflag_b;/*Flag for session change*/
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
VAR(boolean,DCM_VAR) Dcm_isFirstReponseSent_b;  /* flag for KWP first response sent when the split response feature is enabled */
static VAR(boolean,DCM_VAR) s_isApplCalled_b;   /* flag to indicate whether DcmAppl_DcmConfirmation has been called or not in case of splitting of responses */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Definition of Tx structure */
VAR(Dcm_DsldTxType_tst,DCM_VAR) Dcm_DsldTransmit_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Prototype of static function */
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
static void Dcm_QueueTransfer(void);
#endif
static FUNC(boolean,DCM_CODE) Dcm_DsldCheckP2Timer_b(void);

/* This API should only be included when DSPUDS support is enabled and  Session control service is enabled */
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
/*
***********************************************************************************************************
*  Dcm_DslDsd_SessionHandling: In this function the session is changed immediately to avoid delays in setting
*  a new session there by ensuring that the new request coming in with lower priority or same priority
*  is not accepted for reception. Also this function shall be called only from the DSC confirmation results
*
*  \param   None
*  \retval  None
*  \seealso
***********************************************************************************************************/
static FUNC(void,DCM_CODE) Dcm_DslDsd_SessionHandling(void);
static FUNC(void,DCM_CODE) Dcm_DslDsd_SessionHandling(void)
{
    VAR(uint8,AUTOMATIC) nrSessions_u8;
    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;

    /* Check if the processed service is tester triggered DSC with positive response */
    if((Dcm_DsldGlobal_st.dataSid_u8==0x10)&&
       (Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)&&
       (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE))
    {
        /* store old session for invoking the session change later in next MainFunction to get new timings */
        Dcm_DsldGlobal_st.PreviousSessionIndex = Dcm_DsldGlobal_st.idxActiveSession_u8;

        /* Calculate the number  of sessions configured in ECU for particular protocol*/
    #if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
        if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
        {
            nrSessions_u8 = DCM_CFG_NUM_KWP_SESSIONS;
        }
        else
        {
            nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
        }
    #else
        nrSessions_u8 = DCM_CFG_NUM_UDS_SESSIONS;
    #endif
        /* get the index of requested session id in session look up table */
        for(idxIndex_qu8 = 0x0; idxIndex_qu8 < nrSessions_u8 ; idxIndex_qu8++)
        {
            if(Dcm_DsldSessionTable_pcu8[idxIndex_qu8]== Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level)
            {
                /* session found - Set the new session to ensure that there are no requests of lower/same priority protocol received*/
                Dcm_DsldGlobal_st.idxActiveSession_u8  = (uint8)idxIndex_qu8;
                break;
            }
        }
        /* Update the status flag to identify that the session is stored in confirmation */
        Dcm_DsldSessionflag_b =  TRUE;
    }
}
#endif
/*
***********************************************************************************************************
*  Dcm_DslDsd_ComMChannelUpdate: In this function the after the reception of confirmation
*  ComM channel is released if the active session is default session and there is no protocol preemption
*  triggered from the tester request of higher priority protocol
*
*  \param   None
*  \retval  None
*  \seealso
***********************************************************************************************************/
static FUNC(void,DCM_CODE) Dcm_DslDsd_ComMChannelUpdate(void);
static FUNC(void,DCM_CODE) Dcm_DslDsd_ComMChannelUpdate(void)
{
    VAR ( boolean, AUTOMATIC ) callComMInActDiag_b;
    callComMInActDiag_b = FALSE;

    SchM_Enter_Dcm_Global_NoNest();
    /* Deactivate the ComM channel if the confirmation is received for tester request and in Default session */
    if((Dcm_DsldGlobal_st.stDsdState_en == DSD_TX_CONFIRMATION) &&
       (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)&&
       (Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX))
    {
        #if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        /* No need to deactivate ComM channel in case protocol premption is activated */
        /* As this step is done in Dcm_TpRxIndication during Protocol preemption */
        if(Dcm_DsldGlobal_st.stDslPreemptionState_en!=DSL_STOP_PROTOCOL)
        #endif
        {
            callComMInActDiag_b = TRUE;
        }
    }
    SchM_Exit_Dcm_Global_NoNest();
    /* Deactivate the ComM channel in case of timeout between the split responses in KWP services has occured. This shall be done do abort the transmission */
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
    if((DCM_IS_KWPPROT_ACTIVE() != FALSE)&&
       (Dcm_isFirstReponseSent_b!=FALSE)&&
       ((Dcm_DsldGlobal_st.stDsdState_en == DSD_CALL_SERVICE)||(Dcm_DsldGlobal_st.stDsdState_en == DSD_SEND))&&
       (Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX))
     {
        callComMInActDiag_b = TRUE;
     }
#endif

    if ( callComMInActDiag_b != FALSE )
    {
        /* Release the ComM channel */
        ComM_DCM_InactiveDiagnostic(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8].ComMChannelId);
    }
}
/*
***********************************************************************************************************
*  Dcm_SetNegResponse: If this function is called, a negative response will be sent instead of a positive response.
*  The negative response code is taken from the first call duplicate calls are allowed but the
*  errorCode transmitted is ignored.
*  The transmission of the negative response will be performed after calling Dcm_ProcessingDone.
*
*  \param   pMsgContext    Message-related information for one diagnostic protocol identifier.
*            ErrorCode      Error code to be set. This error code will be taken as negative response code (NRC).
*  \retval
*  \seealso
***********************************************************************************************************/

FUNC(void,DCM_CODE) Dcm_SetNegResponse ( P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,
                                         VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) ErrorCode
                                       )
{

    #if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF))
    P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA) adrResponseBuf_pu8;
    #endif

    /* Multicore: No lock needed here as Dsl state is an atomic operation */
    /* DSL state machine handling ensures that there is no data consistency issues */
    if((pMsgContext->msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)
        ||(Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED))
    {
        /* multicore: This request needs to be rejected if the Protocol pre-emption is already started */
        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
           there is no parallel writing due to DSL state machine handling */
        if(pMsgContext->dcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8)
        {
            /* check if this is the first call of Dcm_SetNegResponse() response */
            /* Multicore: Lock is necessary to ensure that the protocol preemption is not started when the below code is bein executed */
            SchM_Enter_Dcm_Global_NoNest();
            if(Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)
            {
                Dcm_DsldGlobal_st.stResponseType_en = DCM_DSLD_NEG_RESPONSE;

                /* frame the negative response */
                /* format of Neg. response is 0x7f, sid, NRC */
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0]= DCM_NEGRESPONSE_INDICATOR;
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[1]= Dcm_DsldGlobal_st.dataSid_u8;
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2]= ErrorCode;
            }
            SchM_Exit_Dcm_Global_NoNest();
        }
    }
    #if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    else if(pMsgContext->msgAddInfo.sourceofRequest==DCM_ROE_SOURCE)
    {
        /* Check whether this is the first call */
        if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE)
        {
            /* Set the negative response type  */
            Dcm_Roe2ResponseType_en = DCM_DSLD_NEG_RESPONSE;
            adrResponseBuf_pu8 = Dcm_DsldRoe2_pcst->txbuffer_ptr;

            /* Frame the negative response */
            adrResponseBuf_pu8[0] = DCM_NEGRESPONSE_INDICATOR;
            adrResponseBuf_pu8[1] = pMsgContext->idContext;
            adrResponseBuf_pu8[2] = ErrorCode;
        }
    }
    #endif
    #if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
    else if(pMsgContext->msgAddInfo.sourceofRequest==DCM_RDPI_SOURCE)
    {
        /* Check if this is the first call */
        if(Dcm_Rdpi2ResponseType_en == DCM_DSLD_POS_RESPONSE)
        {
            /* Set the negative response type  */
            Dcm_Rdpi2ResponseType_en = DCM_DSLD_NEG_RESPONSE;
        }
    }
    #endif
    else
    {
        /* Do nothing */
    }
}





/**
 **************************************************************************************************
 * Dcm_ProcessingDone :  When this function is called, a response will be sent based on the data contained in
                         pMsgContext. If Dcm_SetNegResponse was called before, a negative response is sent,
 *                       otherwise a positive response will be sent.
 *                       The application does not have to care about any timing requirement to process a request.
 * \param           pMsgContext   Message-related information for one one diagnostic protocol identifier.
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_ProcessingDone (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{
    VAR(uint8,AUTOMATIC) dataNrc_u8;
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
    VAR(Std_ReturnType,AUTOMATIC) dataReturnType_u8;
    VAR(PduIdType,AUTOMATIC) dataRdpiTxPduId_u8;
    VAR(uint8,AUTOMATIC) idxIndex_u8;
#endif

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
#endif

    VAR(uint32,AUTOMATIC) nrBufSize_u32;
    /* Initializing the NRC value */
    dataNrc_u8 = 0x00;
    nrBufSize_u32= 0x00;

    /* Multicore: No lock needed here as Dsl state is an atomic operation */
    /* DSL state machine handling ensures that there is no data consistency issues */
    if((pMsgContext->msgAddInfo.sourceofRequest == DCM_UDS_TESTER_SOURCE)||
            (Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED))
    {
        /* Ignore this call from service if DCM is doing the protocol preemption */
        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
           there is no parallel writing due to DSL state machine handling */
        if(pMsgContext->dcmRxPduId == Dcm_DsldGlobal_st.dataActiveRxPduId_u8)
        {
            /*Check if response is given by DSD and for Consecutive call of the service */
            if((Dcm_DsldGlobal_st.stDsdState_en == DSD_CALL_SERVICE)||(Dcm_DsldGlobal_st.dataResponseByDsd_b != FALSE))
            {
                /* Change the DSD state to next state */
                Dcm_DsldGlobal_st.stDsdState_en = DSD_SEND;
            }

            if(Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE)
            {
                /*Check if  negative response is given by DSD*/
                if(Dcm_DsldGlobal_st.dataResponseByDsd_b == FALSE )
                {
                    /* Application can add extra bytes to the service response */
                    nrBufSize_u32 = pMsgContext->resMaxDataLen - pMsgContext->resDataLen;
                    DcmAppl_DcmModifyResponse(Dcm_DsldGlobal_st.dataSid_u8, dataNrc_u8, &(pMsgContext->resData[pMsgContext->resDataLen]), &nrBufSize_u32);
                }
                /* This is positive response */
                /* Check whether the Suppress POS bit is enabled or not and wait pend is sent or not*/
                if(((pMsgContext->msgAddInfo).suppressPosResponse!=FALSE) &&(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0x00u))
                {
                    /* Suppress the POS response */
                    /* Reset the P2 timer and DSL state machine and get the confirmation */
                    Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = NULL_PTR ;

                    Dcm_DsldTransmit_st.dataTxDataLength_u32 = 0x00u;

                }
                else
                {
                    /* Frame the positive response. For positive response 0x40 is red with Sid */
                    Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2] = Dcm_DsldGlobal_st.dataSid_u8 | 0x40u;

                    /* Give the response buffer */
                    Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = & Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2] ;

                    /* fill the response length including Sid */
                    Dcm_DsldTransmit_st.dataTxDataLength_u32 = pMsgContext->resDataLen + 1u + nrBufSize_u32;
                }
            }
            else
            {
                /* This is negative response */

                if(Dcm_DsldGlobal_st.dataResponseByDsd_b == FALSE )
                {
                    /* Application can add extra bytes to the service response */
                    nrBufSize_u32 = pMsgContext->resMaxDataLen - pMsgContext->resDataLen;
                    DcmAppl_DcmModifyResponse(Dcm_DsldGlobal_st.dataSid_u8, Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2], &(Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2]), &nrBufSize_u32);
                }
                /*Check if the Rx pdu id index is greater than or equal to 6 and if the return value of KWP type is FALSE */
                if((pMsgContext->dcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID) && (DCM_IS_KWPPROT_ACTIVE() == FALSE))
                {

                    dataNrc_u8 = Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2];
                    /*
                     * This is functional UDS request, suppress the response for NRCs which are  configured for suppression in the generated MACRO DCM_CFG_SUPPRESS_NRC(dataNrc_u8)
                     * These NRCs are suppressed only if a previous wait pend response is not sent
                     * For KWP request below suppression is not allowed
                     */

                    /*Check for the negative response code  and Wait pend counter is set to 0*/
                    if((DCM_CFG_SUPPRESS_NRC( dataNrc_u8 ))
                            &&(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0x00u))

                    {

                        /* reset the P2 timer and DSL state machine and get the confirmation */
                        /* suppress the Negative response */
                        Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = NULL_PTR ;

                        Dcm_DsldTransmit_st.dataTxDataLength_u32 = 0x00u;
                    }
                    else
                    {

                        /* give the Tx pointer from the starting of the tx buffer */
                        Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8;

                        Dcm_DsldTransmit_st.dataTxDataLength_u32 = 0x03u;
                    }
                }
                else
                {
                    /* This is Physical request. Send Negative response */
                    Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8;
                    /* response data length including 0x7f, Sid, NRC */
                    Dcm_DsldTransmit_st.dataTxDataLength_u32 = 0x03u;
                }
            }

            /* Multicore: Check if there is no intervention from protocol preemption resulting in DSD state change */
            /* This could happen if there is a protocol preemption is triggered after entry into this API */
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
            /* Multicore: When the protocol preemption has been initiated then this request should not be accepted */
            if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&& (stDslPreemptionState_en != DSL_STOP_ROE))
#endif
            {
                if(Dcm_DsldGlobal_st.stDsdState_en == DSD_SEND)
                {
                    /* Send response */
                    Dcm_Dsld_triggerTransmit();
                }
            }
        }
    }
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    /* Check whether the call is for ROE type2 activated service */
    else if(pMsgContext->msgAddInfo.sourceofRequest == DCM_ROE_SOURCE)
    {

#if(DCM_CFG_ROE_QUEUE_ENABLED == DCM_CFG_OFF)
        /* ROE state machine is changed to send the response */
        Dcm_DsdRoe2State_en = DSD_SEND;


        /* Check if the response is positive */
        if(Dcm_Roe2ResponseType_en == DCM_DSLD_POS_RESPONSE)
        {
            /* Is suppress positive bit is enabled for this service? */

            if(Dcm_Roe2MesContext_st.msgAddInfo.suppressPosResponse == FALSE)
            {
                /* Fill the SID info in positive response */
                Dcm_DsldRoe2_pcst->txbuffer_ptr[2] = Dcm_Roe2MesContext_st.idContext|0x40u;

                /* Fill the pdu info structure */
                Dcm_DsldRoe2PduInfo_st.SduLength = (PduLengthType) Dcm_Roe2MesContext_st.resDataLen + 1u ;
                Dcm_DsldRoe2PduInfo_st.SduDataPtr = &Dcm_DsldRoe2_pcst->txbuffer_ptr[2];
            }
            else
            {
                /* Suppress the response */
                Dcm_DsldRoe2PduInfo_st.SduLength = 0x00;

            }

        }
        else
        {
            dataNrc_u8 = Dcm_DsldRoe2_pcst->txbuffer_ptr[2];

            /*
             * This is functional UDS request, suppress the response for NRCs which are  configured for suppression in the generated MACRO DCM_CFG_SUPPRESS_NRC(dataNrc_u8)
             * These NRCs are suppressed only if a previous wait pend response is not sent
             * For KWP request below suppression is not allowed
             */
            if((Dcm_Roe2MesContext_st.dcmRxPduId >= DCM_INDEX_FUNC_RX_PDUID)&&
                    (DCM_CFG_SUPPRESS_NRC( dataNrc_u8 )))
            {
                /* No need to send response*/
                Dcm_DsldRoe2PduInfo_st.SduLength = 0x00;
            }
            else
            {
                /* Fill negative response length and buffer */
                Dcm_DsldRoe2PduInfo_st.SduLength = (PduLengthType) ( Dcm_Roe2MesContext_st.resDataLen + 3u ) ;
                Dcm_DsldRoe2PduInfo_st.SduDataPtr = &Dcm_DsldRoe2_pcst->txbuffer_ptr[0];

            }

        }

        /* Check if the response is suppressed or not */
        if(Dcm_DsldRoe2PduInfo_st.SduLength != 0x00u)
        {
            /* Check if the ComM is in full communication mode */
            if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].channel_idx_u8))
            {
                /* Trigger the Tx in PduR */
                if(PduR_DcmTransmit(Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_Roe2MesContext_st.dcmRxPduId]].
                        roetype2_txpdu_u8,&Dcm_DsldRoe2PduInfo_st) == E_NOT_OK)

                {
                    /* Tx failed in PduR. Give confirmation */
                    Dcm_Roe2TxResult_u8 = E_NOT_OK;
                    Dcm_DsdRoe2State_en = DSD_TX_CONFIRMATION;
                    /* Report development error "DCM_E_RET_E_NOT_OK " to DET module if the DET module is enabled */
                    DCM_DET_ERROR(DCM_PROCESSINGDONE_ID , DCM_E_RET_E_NOT_OK )
                }
            }
            else
            {
                /* ComM is not in full communication mode. No need to trigger Tx in PduR. Give confirmation */
                Dcm_Roe2TxResult_u8 = E_NOT_OK;
                Dcm_DsdRoe2State_en = DSD_TX_CONFIRMATION;
                /* Report development error "DCM_E_FULLCOMM_DISABLED " to DET module if the DET module is enabled */
                DCM_DET_ERROR(DCM_PROCESSINGDONE_ID , DCM_E_FULLCOMM_DISABLED )
            }
        }
        else
        {
            /* No need to trigger Tx in PduR. Give confirmation */
            Dcm_Roe2TxResult_u8 = E_OK;
            Dcm_DsdRoe2State_en = DSD_TX_CONFIRMATION;
        }
#else
        Dcm_DslDsdRoeQueueResponse();
        /* Set the state of ROE Type2 state machine to IDLE state */
        Dcm_DsdRoe2State_en = DSD_IDLE;
#endif

    }
#endif
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
    else if(pMsgContext->msgAddInfo.sourceofRequest == DCM_RDPI_SOURCE)
    {
        /* Fill the default value */
        dataReturnType_u8 = E_OK;

        /* Is this positive response */
        if(Dcm_Rdpi2ResponseType_en == DCM_DSLD_POS_RESPONSE)
        {
            /* Fill the pdu info structure. No need to fill SID info */
            /* Check for COM mode */
            if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8))
            {
                /*Obtain the index ofr TYpe2 TxPduId on which the response is to be triggered*/
                Dcm_GetRdpiType2Index(&idxIndex_u8);
                dataRdpiTxPduId_u8 = Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].txpduid_num_u8;
                Dcm_DsldRdpi2pduinfo_ast[idxIndex_u8].SduDataPtr = &Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].txbuffer_ptr[0];
                Dcm_DsldRdpi2pduinfo_ast[idxIndex_u8].SduLength = (PduLengthType) (Dcm_Rdpi2MesContext_st.resDataLen);
                /*Initialize Roe type TxPduId on which the response is to be triggered*/
                Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy=TRUE;
                /* Trigger the Tx in CanIf or FrIf via PduR */
                dataReturnType_u8 = PduR_DcmTransmit(dataRdpiTxPduId_u8,&Dcm_DsldRdpi2pduinfo_ast[idxIndex_u8]);
            }
            else
            {
                /* COM MODE failed */
                dataReturnType_u8 = E_NOT_OK;
                /* Report development error "DCM_E_FULLCOMM_DISABLED " to DET module if the DET module is enabled */
                DCM_DET_ERROR(DCM_PROCESSINGDONE_ID , DCM_E_FULLCOMM_DISABLED )
            }

        }

        if(dataReturnType_u8 == E_OK)
        {
            /* Give the confirmation to application */
            DcmAppl_DcmConfirmationRDPI(0x2A,Dcm_Rdpi2MesContext_st.dcmRxPduId,DCM_RES_POS_OK);

        }
        else
        {
            /* Give the confirmation to application */
            DcmAppl_DcmConfirmationRDPI(0x2A,Dcm_Rdpi2MesContext_st.dcmRxPduId,DCM_RES_POS_NOT_OK);
        }
    }
#endif
    else
    {
        /* Do nothing */
    }
}


/**
 **************************************************************************************************
 * Dcm_Dsld_triggerTransmit : Triggering the Tx to PduR. During Suppression of responses DSL state machine
 *                           is reseted.
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 *
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_Dsld_triggerTransmit(void)
{
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) dataResult_u8;
    VAR(boolean,AUTOMATIC) dataSendResponse_b;
    VAR(boolean,AUTOMATIC) flgCheckP2max_b;

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
#endif

    /* Set the default value */
    dataResult_u8 = 0xffu;
    /*Initialize the send data response to value false so that no response send */
    dataSendResponse_b = FALSE;

    /* Check if the call is for application triggered wait pend response */

    if(Dcm_DsldTransmit_st.flgApplWaitPend_b == FALSE)
    {
        /* Check if the call is for suppression of responses */
        if(Dcm_DsldTransmit_st.dataTxDataLength_u32 != 0x0u )
        {
            /* Multicore: Lock necessary here to block DSL/DSD state changes when parallel Rx or Dcm_MainFunction is running */
            SchM_Enter_Dcm_Global_NoNest();
            /* Multicore: Check if there is no intervention from protocol preemption resulting in DSD state change */
            /* This could happen if there is a protocol preemption is triggered after entry into this API */
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
            /* Multicore: When the protocol preemption has been initiated then this request should not be accepted */
            if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&& (stDslPreemptionState_en != DSL_STOP_ROE))
#endif
            {
                /* check DSL state machine is waiting for Tx confirmation for wait pend response or not */
                if((Dcm_DsldGlobal_st.stDslState_en == DSL_WAIT_FOR_P2MAX)||
                   (Dcm_DsldGlobal_st.stDslState_en == DSL_SEND_GENERAL_REJECT)||
                   (Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED))
                {
                    /* update data in pdu structure */
                    Dcm_DsldPduInfo_st.SduDataPtr = Dcm_DsldTransmit_st.adrTxBuffer_tpu8;

                    Dcm_DsldPduInfo_st.SduLength = (PduLengthType) Dcm_DsldTransmit_st.dataTxDataLength_u32;

                    /* final response comes now. reset the wait pend counter */
                    Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

                    if(Dcm_DsldGlobal_st.stDslState_en != DSL_ROETYPE1_RECIEVED)
                    {
                        /* change the state to wait for Tx confirmation */
                        Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_CONFIRMATION;

                        /* after getting the Tx confirmation DSL state changed to DSL_READY_FOR_RECEPTION  state */
                        Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;
                    }
                    /* Send the response */

                    dataSendResponse_b = TRUE;

                }
                else
                {
                    if(Dcm_DsldGlobal_st.stDslState_en == DSL_WAIT_FOR_CONFIRMATION)
                    {
                        /* After getting the TX confirmation for wait pend DSL state machine state change to */
                        /* DSL_SEND_FINAL_RESPONSE state */
                        Dcm_DsldTransmit_st.stDslNextState_en = DSL_SEND_FINAL_RESPONSE;
                    }
                }
            }
            SchM_Exit_Dcm_Global_NoNest();
            /*if response is send or not*/
            if(dataSendResponse_b != FALSE)
            {
                /* Trigger  response */
                Dcm_DsldSendResponse(&Dcm_DsldPduInfo_st);
            }
        }
        else
        {

/* This API should only be included when DSPUDS support is enabled and  Session control service is enabled */
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
            Dcm_DslDsd_SessionHandling();
#endif

            /* simulate successful transmission of response */
            Dcm_DsldGlobal_st.dataResult_u8 = E_OK;

            /* indicate to DSD  */
            Dcm_DsldDataConfirmation();
            /* In case of Suppress positive Response, no case of confirmation, so Queue should be freed. Thus Dcm_QueueTransfer is called to change the queue state to DCM_QUEUE_IDLE */
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
            Dcm_QueueTransfer();
#else
            /* ready for receiving the next request, No need to send any response */
            /* Multicore: No lock needed here as Dsl state is an atomic operation */
            /* DSL state machine handling ensures that there is no data consistency issues */
            Dcm_DsldGlobal_st.stDslState_en = DSL_READY_FOR_RECEPTION;
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
            /* Multicore: No lock needed here as Dsl state is an atomic operation */
            /* DSL state machine handling ensures that there is no data consistency issues */
            Dcm_DsldGlobal_st.stDslPreemptionState_en=DSL_READY_FOR_RECEPTION;
#endif
#endif

        }
    }
    else
    {
        flgCheckP2max_b = Dcm_DsldCheckP2Timer_b();

        /* Time difference between two response pend should be greater the half of P2* max  */
        /*Check if the time gap betwen p2 and p2* max is valid */
        if(flgCheckP2max_b != FALSE )
        {
            /* check the max number of wait pend is sent already or not */
            if( Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 != DCM_CFG_MAX_WAITPEND )
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
                /* Already configured no. of response pend is sent */
                dataResult_u8 = DCM_RES_NEG_NOT_OK;

                /* Multicore: No lock needed here as Dsl state is an atomic operation */
                /* DSL state machine handling ensures that there is no data consistency issues */
                /* Now send general reject in next cycle */
                Dcm_DsldGlobal_st.stDslState_en = DSL_SEND_GENERAL_REJECT;
            }
        }
        else
        {
            /* Time difference between last triggered Response pend and now less than P2* max value */
            /* Give the positive confirmation to application. No need to change DSL state.               */
            dataResult_u8 = DCM_RES_NEG_OK;
        }
        if(dataResult_u8 != 0xffu)
        {
            /* Reset the flag that indicated application triggered response pend */

            Dcm_DsldTransmit_st.flgApplWaitPend_b = FALSE;

                        /* Call the DSLDSD API to evaluate the confirmation results */
                        Dcm_DslDsdConfirmRespPend(Dcm_DsldGlobal_st.dataSid_u8, dataResult_u8);

                        /* indicate to application regarding the wait pend sent  */
                        (void)Dcm_ConfirmationRespPend(dataResult_u8);
        }
    }
}


/**
 **************************************************************************************************
 * Dcm_DsldCheckP2Timer_b : Function to check whether half of the P2* time is over after sending the
 *                        last response pend.
 *
 * \param           None
 *
 *
 * \retval          TRUE : Half of the P2* time is over. FALSE: Half of the P2* time is not yet over.
 * \seealso
 *
 **************************************************************************************************
 */

static FUNC(boolean,DCM_CODE) Dcm_DsldCheckP2Timer_b(void)
{

    VAR(boolean,AUTOMATIC) dataReturnValue_b;
    VAR(uint32,AUTOMATIC) dataHalfP2timer_u32;
    #if(DCM_CFG_OSTIMER_USE != FALSE)
    VAR(uint32,AUTOMATIC) nrCurrentTicks_u32;
    #endif

    if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 != 0x0)
    {
        /* set the default value */

        dataReturnValue_b = FALSE;

        /* get half of P2* max */
        /* Spin lock Dcm_DsldTimer_NoNest is not needed here as there is no issue of inconsistency within the Dcm Timings data group
         * where P2, P3 and P2Star is involved, this is case where only P2StrMax_u32 is being accessed */
        dataHalfP2timer_u32 = Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 >> 1u;

        #if(DCM_CFG_OSTIMER_USE != FALSE)

        /* Get the current ticks from system timer  */

        Dcm_P2OrS3TimerStatus_uchr = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&nrCurrentTicks_u32));

        /* Check the Status. If status is wrong, go to checking of OS raster count method */
        if (Dcm_P2OrS3TimerStatus_uchr == E_OK )
        {
            /* Compare with half of the P2* max value */
            if((DCM_CFG_TICKS2US_COUNTER(nrCurrentTicks_u32 - Dcm_P2OrS3StartTick_u32)) >= (dataHalfP2timer_u32))
            {
                /* Time is elapsed */
                /*Data return value is set to true*/
                dataReturnValue_b = TRUE;
            }
        }
        else
        {
            /* Check the OS raster count which is decremented in DSL state machine */
            if(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32 < (dataHalfP2timer_u32/DCM_CFG_TASK_TIME_US))
            {
                /* Time is elapsed */
                /*Data return value is set to true*/
                dataReturnValue_b = TRUE;
            }
        }
        #else
        /* Check the OS raster count which is decremented in DSL state machine */
        if(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32 < (dataHalfP2timer_u32/DCM_CFG_TASK_TIME_US))
        {
            /* Time is elapsed */
            /*Data return value is set to true*/
            dataReturnValue_b = TRUE;
        }
        #endif
    }
    else
    {
        /* No need to check timer because this is first response pend */
        /*Data return value is set to true*/
        dataReturnValue_b = TRUE;
    }
    return(dataReturnValue_b);
}



/**
 **************************************************************************************************
 * Dcm_DsldSendResponse : This Function called by  DSLD to trigger the Tx in PduR
 *
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(void,DCM_CODE) Dcm_DsldSendResponse(P2CONST(PduInfoType,AUTOMATIC,DCM_INTERN_DATA) adrPduStrucutre_pcst)
{
    VAR(boolean,AUTOMATIC) dataResult_b;

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
#endif
#endif

    /* By default result made TRUE */

    dataResult_b = TRUE;

    /* Multicore: No lock needed here as Dsl state is an atomic operation */
    /* DSL state machine handling ensures that there is no data consistency issues */
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    if(Dcm_DsldGlobal_st.stDslState_en == DSL_ROETYPE1_RECIEVED)
    {
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
        stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
        /* Multicore: When the protocol preemption has been initiated then this request should not be accepted to avoid transmission on invalid TxPdu*/
        if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&& (stDslPreemptionState_en != DSL_STOP_ROE))
        {
            /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
               there is no parallel writing due to DSL state machine handling */
            /* Re write Tx pdu Id for ROE  */
            Dcm_DsldGlobal_st.dataActiveTxPduId_u8 =
                    Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;
        }
        else
        {
            /*Data result made FALSE*/
            dataResult_b = FALSE;
        }
#else
        /* Multicore: No locking necessary as Dcm_DsldGlobal_st.dataActiveRxPduId_u8 is an atomic variable and
               there is no parallel writing due to DSL state machine handling */
        /* Re write Tx pdu Id for ROE  */
        Dcm_DsldGlobal_st.dataActiveTxPduId_u8 =
                Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_DsldGlobal_st.dataActiveRxPduId_u8]].txpduid_num_u8;
#endif
    }
#endif

    /* ComM should be in FULL COM mode to sending the response */
    if((DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_DsldGlobal_st.nrActiveConn_u8].channel_idx_u8)) && (dataResult_b))
    {
        /* Trigger response in PduR */
        if(PduR_DcmTransmit(Dcm_DsldGlobal_st.dataActiveTxPduId_u8, adrPduStrucutre_pcst) == E_NOT_OK)
        {
            /* Unable to transmit response */
            /*Data result made False*/
            dataResult_b = FALSE;
        }
    }
    else
    {
        /* COMM not in Full Communication Mode */
        /*Data result made FALSE*/
        dataResult_b = FALSE;
    }
    /*Check if Data result made FALSE*/
    if(dataResult_b == FALSE)
    {
        {
            /*
             * Earlier the below line was  if(Dcm_DsldTransmit_st.stDslNextState_en == DSL_WAIT_FOR_P2MAX)
             * This is used to check if this function is called to transmit WAIT PEND response(either normal or
             * Forced).In both the cases is set to DSL_WAIT_FOR_P2MAX, before transmitting WAIT PEND
             * With SPRB support for paged buffer , next state can also be DSL_SEND_FINAL_RESPONSE.
             * The state stDslNextState_en to DSL_SEND_FINAL_RESPONSE , when DSL has to trigger the WAIT PEND response
             * before triggering the positive response, though P2Max is not over(This is to overcome suppressing the
             * positive response).
             * With the introduction of this change the previous check fails as stDslNextState_en is
             * DSL_SEND_FINAL_RESPONSE but WAIT PEND response has to be sent.
             * Hence the new check is introduced as below.
             */
            if(Dcm_DsldTransmit_st.stDslNextState_en != DSL_READY_FOR_RECEPTION)
            {
                /* Unable to send wait pend, again go to P2 max monitoring */
                Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_P2MAX;

                /* Check this is for forced wait pend or not */

                if(Dcm_DsldTransmit_st.flgApplWaitPend_b != FALSE)
                {
                    /* Reset the bit */
                    /*Reset the wait pend flag to FALSE*/
                    Dcm_DsldTransmit_st.flgApplWaitPend_b = FALSE;

                        /* Call the DSLDSD API to evaluate the confirmation results */
                        Dcm_DslDsdConfirmRespPend(Dcm_DsldGlobal_st.dataSid_u8, DCM_RES_NEG_NOT_OK);

                        /* indicate to application regarding the wait pend sent  */
                        (void)Dcm_ConfirmationRespPend(DCM_RES_NEG_NOT_OK);

                }
            }
            else
            {

                /* Triggering of Tx fails */
                Dcm_DsldGlobal_st.dataResult_u8 = E_NOT_OK;

                /* Reset the variable to FALSE */

                Dcm_DsldGenRejectSent_b = FALSE;

                /* Indicate to DSD */
                Dcm_DsldDataConfirmation();
                /* In case of Failed transmission when PduR returns E_NOT_OK, Queue should be freed. Thus Dcm_QueueTransfer is called to change the queue state to DCM_QUEUE_IDLE */
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
                Dcm_QueueTransfer();
#else
                /* Unable to send final response or general reject, go to default state */
                Dcm_DsldGlobal_st.stDslState_en = DSL_READY_FOR_RECEPTION;
#endif

            }
        }
    }
}

/*
***********************************************************************************************************
*  Dcm_TxConfirmation:This function is called by the lower layer (in general the PDU Router):
*  - with Result = E_OK after the complete DCM I-PDU has successfully been transmitted, i.e. at the very
*    end of the segmented TP transmit cycle. Within this function, the DCM shall unlock the transmit buffer.
*  - with Result = E_NOT_OK if an error (e.g. timeout) has occurred during the transmission of the DCM
*    I-PDU. This enables unlocking of the transmit buffer and error handling.
*
*  \param   DcmRxPduId     ID of DCM I-PDU that has been transmitted.
*            Result         Result of the N-PDU transmission:
*                           E_OK if the complete N-PDU has been transmitted.
*                           E_NOT_OK if an error occurred during transmission, used to enable
*                           unlocking of the transmission buffer.
*  \retval:    None
*  \seealso
*
***********************************************************************************************************/
FUNC(void,DCM_CODE) Dcm_TxConfirmation ( VAR(PduIdType,AUTOMATIC) DcmTxPduId)
{
    Dcm_TpTxConfirmation(DcmTxPduId,E_OK);
}

/*
***********************************************************************************************************
*  Dcm_TriggerTransmit :  The lower layer communication module requests the buffer of the SDU
*                         for transmission from the upper layer module.
*
*  \param   DcmRxPduId     ID of DCM I-PDU that has been transmitted.
*            PduInfoPtr    Contains a pointer to a buffer (SduDataPtr)
*                          to where the SDU shall be copied to. On return,
*                          the service will indicate the length of
*                          the copied SDU data in SduLength.
*  \retval:    None
*  \seealso
*
***********************************************************************************************************/
/*MR12 RULE 8.13 VIOLATION:The object addressed by the pointer parameter 'PduInfoPtr' is not modified and so the pointer could be of type 'pointer to const'. MISRA C:2012 Rule-8.13*/
FUNC(void,DCM_CODE) Dcm_TriggerTransmit(VAR(PduIdType,AUTOMATIC) TxPduId,P2VAR(PduInfoType,AUTOMATIC,DCM_INTERN_DATA) PduInfoPtr )
{
    /*Do Nothing, this function is not used by Dcm and is provided only to solve compilation issues*/
    (void)TxPduId;
    (void)PduInfoPtr;
}

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
/*
***********************************************************************************************************
*  Dcm_QueueTransfer :  The function to take up the queued request for processing, in case it is received completely
                        or to continue the request being queued as the main request.
*
*  \param       None
*  \retval:     None
*  \seealso
*
***********************************************************************************************************/
static void Dcm_QueueTransfer(void)
{
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
    VAR(boolean,AUTOMATIC) iscallApplication_b;
    VAR(boolean,AUTOMATIC) iscallApplAfterQueueComplete_b;
    iscallApplication_b = FALSE;
    iscallApplAfterQueueComplete_b = FALSE;
#endif
    SchM_Enter_Dcm_Global_NoNest();
    if(Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_IDLE)
    {
        Dcm_DsldGlobal_st.stDslState_en = DSL_READY_FOR_RECEPTION ;
    }
    /* copying of the second request is taking place- Receiving is not complete */
    else if(Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_RUNNING)
    {
        /* move all the special variable to active variable */
        Dcm_DsldGlobal_st.dataActiveRxPduId_u8 = Dcm_QueueStructure_st.dataQueueRxPduId_u8;
        Dcm_DsldGlobal_st.dataRequestLength_u16 = Dcm_QueueStructure_st.dataQueueReqLength_u16;
        Dcm_DslDsdRxPduArray_ast[Dcm_DsldGlobal_st.dataActiveRxPduId_u8].adrBufferPtr_pu8 = Dcm_QueueStructure_st.adrBufferPtr_pu8;
        /* Set the queue state to IDLE as one buffer is free now */
        Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;
        /* Queuing is going on. Its is in Copy Rx Data stage. hence, move the DSL state to Receiving */
        Dcm_DsldGlobal_st.stDslState_en = DSL_RECEIVING;
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
        /* Tx confirmation of the first request has come while queuing the second request. Hence call the application */
        iscallApplication_b = TRUE;
#endif
    }
    else
    {
         /* dummy else block */
    }
    SchM_Exit_Dcm_Global_NoNest();
    /* Second request is already available in the other buffer - Rx indication for the second request has come already */
    if(Dcm_QueueStructure_st.Dcm_QueHandling_en == DCM_QUEUE_COMPLETED)
    {
        if (Dcm_DsldGlobal_st.idxActiveSession_u8 == DCM_DEFAULT_SESSION_IDX)
        {

             /* Api to check whether ComM_Dcm_ActiveDiagnostic needs to be called or not*/
             Dcm_CheckActiveDiagnosticStatus(Dcm_active_commode_e[Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[Dcm_QueueStructure_st.dataQueueRxPduId_u8]].channel_idx_u8].ComMChannelId);
        }
        SchM_Enter_Dcm_Global_NoNest();
        /* move all the special variable to active variable */
        Dcm_DsldGlobal_st.dataActiveRxPduId_u8 = Dcm_QueueStructure_st.dataQueueRxPduId_u8;
        Dcm_DsldGlobal_st.dataRequestLength_u16 = Dcm_QueueStructure_st.dataQueueReqLength_u16;
        Dcm_DsldGlobal_st.adrBufferPtr_pu8 = Dcm_QueueStructure_st.adrBufferPtr_pu8;
        /* as one of the buffers is free, make the queue as IDLE to receive the next request */
        Dcm_QueueStructure_st.Dcm_QueHandling_en = DCM_QUEUE_IDLE;
        /* Queuing is completed. Hence, move the DSL state to Received */
        Dcm_DsldGlobal_st.stDslState_en = DSL_REQUEST_RECEIVED;
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
        iscallApplication_b = FALSE;
        iscallApplAfterQueueComplete_b = TRUE;
#endif
        SchM_Exit_Dcm_Global_NoNest();
        /* Start P2 timer */
        /* MR12 RULE 11.3 VIOLATION: Casting to different object pointer type. */
        DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
        (Dcm_DsldTimer_st.dataTimeoutP2max_u32 - Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].dataP2TmrAdjust),
        Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
    }
#if(DCM_CALLAPPLICATIONONREQRX_ENABLED!=DCM_CFG_OFF)
    if(iscallApplication_b == TRUE)
    {
        /* the applications shall be called when the copying of the queue is still happening and the first request gets over.
        * If the queued request is completely received when the first request is over, the applications shall not be called */
        (void)DcmAppl_StartOfReception(Dcm_DslDsdRxPduArray_ast[Dcm_DsldGlobal_st.dataActiveRxPduId_u8].adrBufferPtr_pu8[0],Dcm_DsldGlobal_st.dataActiveRxPduId_u8,Dcm_DsldGlobal_st.dataRequestLength_u16,(uint32)(Dcm_DslDsdRxPduArray_ast[Dcm_DsldGlobal_st.dataActiveRxPduId_u8].adrBufferPtr_pu8));
        /* calling the application with the already received data in while queuing. For the remaining data, the application will be called from the CopyRxData function directly as the Queue goes IDLE here */
        (void)DcmAppl_CopyRxData(Dcm_DsldGlobal_st.dataActiveRxPduId_u8,((Dcm_QueueStructure_st.dataQueueReqLength_u16 - Dcm_DslDsdRxPduArray_ast[Dcm_DsldGlobal_st.dataActiveRxPduId_u8].Dcm_DsldRxPduBuffer_st.SduLength)));
    }
    if( iscallApplAfterQueueComplete_b == TRUE)
    {
        /* the applications shall be called when the copying of the queue is still happening and the first request gets over.
        * If the queued request is completely received when the first request is over, the applications shall not be called */
        (void)DcmAppl_StartOfReception(Dcm_DsldGlobal_st.adrBufferPtr_pu8[0],Dcm_DsldGlobal_st.dataActiveRxPduId_u8,Dcm_DsldGlobal_st.dataRequestLength_u16,(uint32)(Dcm_DsldGlobal_st.adrBufferPtr_pu8));
        /* calling the application with the already received data in while queuing. For the remaining data, the application will be called from the CopyRxData function directly as the Queue goes IDLE here */
        (void)DcmAppl_CopyRxData(Dcm_DsldGlobal_st.dataActiveRxPduId_u8,Dcm_DsldGlobal_st.dataRequestLength_u16);
        /* calling Rx indication */
        (void)DcmAppl_TpRxIndication(Dcm_DsldGlobal_st.dataActiveRxPduId_u8,E_OK);
        iscallApplAfterQueueComplete_b = FALSE;
    }
#endif
}
#endif
/*
********************************************************************************
*  Dcm_Prv_KWPConfirmation:This function is used to handle KWP protocol related
*																confirmation.
*  \param
*            Result         Result of the N-PDU transmission:
*                           E_OK if the complete N-PDU has been transmitted.
*                           E_NOT_OK if an error occurred during transmission,
*                           used to enable unlocking of the transmission buffer.
*  \retval:    isKwpEn_b
*  \seealso
*
*******************************************************************************/
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&& \
							(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
static FUNC(boolean,DCM_CODE) Dcm_Prv_KWPConfirmation (
	VAR(Std_ReturnType,AUTOMATIC) Result
												      )
{
  VAR(PduLengthType,AUTOMATIC) dataResponseLength = 0u;
  VAR(boolean,AUTOMATIC) isKwpEn_b = TRUE;

    /* In case the split response feature is enabled and the active service is
							KWP, then call the application confirmation here */
    if((Result==E_OK)&&
        (DCM_IS_KWPPROT_ACTIVE() != FALSE)&&
            (Dcm_DsldGlobal_st.dataResponseByDsd_b == FALSE )&&
            (Dcm_DsldGlobal_st.stResponseType_en == DCM_DSLD_POS_RESPONSE))
    {
			isKwpEn_b = TRUE;
			DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,
					Dcm_DsldMsgContext_st.dcmRxPduId,
					Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8
							[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
					DCM_RES_POS_OK);
			/* call the application to know if some more response bytes are to
									be sent yet by splitting of responses. */
			DcmAppl_DcmGetRemainingResponseLength(Dcm_DsldMsgContext_st.
												idContext,&dataResponseLength);

			if(dataResponseLength!=0u)
			{
				/* If the KWP service has some responses to be sent, then
				call the service again in the next main cycle if it
													is scheduled by Dcm */
				if(Dcm_isFirstReponseSent_b == FALSE)
				{
					/* set the below flag to TRUE when the Confirmation for
									the first split response is received */
					Dcm_isFirstReponseSent_b = TRUE;
				}
				/* start the split response timer -
								DCM_CFG_SPLITRESPONSETIMEFORKWP (configured) */
				DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
						(DCM_CFG_SPLITRESPONSETIMEFORKWP),
						Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)
				/* Multicore: No lock needed here as Dsl state is an atomic
				operation and at this point the DCM statemachine is
					already blocked so there is no question of accepting
									a parallel request thus no locks needed*/

				Dcm_DsldGlobal_st.stDslState_en = DSL_WAIT_FOR_P2MAX;
				Dcm_DsldGlobal_st.stDsdState_en = DSD_CALL_SERVICE;
			}
			else
			{
				s_isApplCalled_b = TRUE; /* in this case,
				DcmAppl_DcmConfirmation is already called above.
													Hence do not call again. */
				Dcm_KWPConfirmationForSplitResp(DCM_RES_POS_OK);
				/* in case of negative Tx confirmation or if all
										the split responses have been sent */
				Dcm_isFirstReponseSent_b = FALSE;
				s_isApplCalled_b = FALSE;
			}
    }
	else
	{
		isKwpEn_b = FALSE;
	}

	return isKwpEn_b;
}
#endif

/*
********************************************************************************
*  Dcm_Prv_PendRespConfirmation:This function is used to handle Pending Response
*													confirmation functionality
*  \param
*            Result         Result of the N-PDU transmission:
*                           E_OK if the complete N-PDU has been transmitted.
*                           E_NOT_OK if an error occurred during transmission,
*                           used to enable unlocking of the transmission buffer.
*  \retval:    None
*  \seealso
*
*******************************************************************************/
static FUNC(void,DCM_CODE) Dcm_Prv_PendRespConfirmation (
	VAR(Std_ReturnType,AUTOMATIC) Result
													    )
{
	/* confirmation status of result */
    VAR(Dcm_ConfirmationStatusType,AUTOMATIC) stStatus_u8;
        if(Result == E_OK )
        {
            /* extend the time to Spl p2max, start SplP2 timer */

            DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,
                (Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 -
				Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].
														dataP2StarTmrAdjust),
                    Dcm_P2OrS3StartTick_u32,Dcm_P2OrS3TimerStatus_uchr)

            /* result of wait pend */
            stStatus_u8 = DCM_RES_NEG_OK;
        }
        else
        {
            stStatus_u8 = DCM_RES_NEG_NOT_OK;
        }
                    /*Check this is for forced wait pend or not*/
        if(Dcm_DsldTransmit_st.flgApplWaitPend_b != FALSE)
        {
           /* Call the DSLDSD API to evaluate the confirmation results */
           Dcm_DslDsdConfirmRespPend(Dcm_DsldGlobal_st.dataSid_u8, stStatus_u8);

           /* indicate to application regarding the wait pend sent  */
           (void)Dcm_ConfirmationRespPend(stStatus_u8);

           /*Reset the wait pend flag to FALSE*/
           Dcm_DsldTransmit_st.flgApplWaitPend_b = FALSE;
        }
        Dcm_DsldGlobal_st.stDslState_en = Dcm_DsldTransmit_st.stDslNextState_en;
}

/*
********************************************************************************
*  Dcm_Prv_CurrResConfirmation:This function is used to handle functionalaties
										to perform for Positive confirmation.
*  \param
*            Result         Result of the N-PDU transmission:
*                           E_OK if the complete N-PDU has been transmitted.
*                           E_NOT_OK if an error occurred during transmission,
*                           used to enable unlocking of the transmission buffer.
*  \retval:    None
*  \seealso
*
*******************************************************************************/
static FUNC(void,DCM_CODE) Dcm_Prv_CurrResConfirmation (
		VAR(Std_ReturnType,AUTOMATIC) Result
												        )
{
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&\
							(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))

    if(Dcm_Prv_KWPConfirmation(Result)== FALSE)
#endif
    {

         /* Store result */
         Dcm_DsldGlobal_st.dataResult_u8 = Result;
/* This API should only be included when DSPUDS support
						is enabled and  Session control service is enabled */
#if ((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && \
				(DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) )
         Dcm_DslDsd_SessionHandling();
#endif
         /* Indicate to DSD */
         Dcm_DsldDataConfirmation();
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
                    /* In case of Positive confirmation, Queue should be freed.
Thus Dcm_QueueTransfer is called to change the queue state to DCM_QUEUE_IDLE */
         Dcm_QueueTransfer();
#else
    #if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
                    /*Move the next DSL state to ready for reception only when
												the no pre-emption has occured*/
            if(!(((Dcm_DsldGlobal_st.stDslPreemptionState_en==
				  DSL_STOP_PROTOCOL_RECEIVING)||
				(Dcm_DsldGlobal_st.stDslPreemptionState_en==DSL_STOP_PROTOCOL))
					           && (Dcm_DsldGlobal_st.stDsdState_en==DSD_SEND)))

                {
                    Dcm_DsldGlobal_st.stDslState_en =
										Dcm_DsldTransmit_st.stDslNextState_en ;
                }
    #else
       Dcm_DsldGlobal_st.stDslState_en = Dcm_DsldTransmit_st.stDslNextState_en ;
    #endif
        #endif

    }

}

/*
********************************************************************************
*  Dcm_TpTxConfirmation:This function is called by the lower layer (in general
																the PDU Router):
*  - with Result = E_OK after the complete DCM I-PDU has successfully been
*	 transmitted, i.e. at the very end of the segmented TP transmit cycle.
*     Within this function, the DCM shall unlock the transmit buffer.
*  - with Result = E_NOT_OK if an error (e.g. timeout) has occurred during
*     the transmission of the DCM  I-PDU. This enables unlocking
*   of the transmit buffer and error handling.
*
*  \param   DcmRxPduId     ID of DCM I-PDU that has been transmitted.
*            Result         Result of the N-PDU transmission:
*                           E_OK if the complete N-PDU has been transmitted.
*                           E_NOT_OK if an error occurred during transmission,
*                        used to enable   unlocking of the transmission buffer.
*  \retval:    None
*  \seealso
*
*******************************************************************************/
FUNC(void,DCM_CODE) Dcm_TpTxConfirmation (
	VAR(PduIdType,AUTOMATIC) DcmTxPduId,
	VAR(Std_ReturnType,AUTOMATIC) Result
	)
{

    VAR(uint8,AUTOMATIC) idxIndex_u8; /* Variable to store the index */
    /* Multicore: This API is called from Tp in Interrupt context*/
    if ( DcmTxPduId < DCM_NUM_TX_PDUID )
    {
#if((DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)&& \
										(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
        for(idxIndex_u8=0;idxIndex_u8<DCM_CFG_NUM_RDPITYPE2_TXPDU;idxIndex_u8++)
        {
            if(Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].txpduid_num_u8 ==
								Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId])
            {
                /* Reset the status of the TxPduId */

                Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].isTxPduId_Busy= FALSE;
                /*Reload the TxPdu counter*/
                Dcm_Dsld_RDPIType2tx_table[idxIndex_u8].cntFreeTxPduRdpi2Cntr_u8
											=DCM_CFG_RDPITYPE2FREETXPDUCOUNTER;
                break;
            }
        }
#endif

    /* Reset the SID for which NRC 0x21 was sent to 0xFFFF */
    for (idxIndex_u8 = 0; idxIndex_u8 < DCM_CFG_NUM_RX_PDUID ; idxIndex_u8++ )
    {
        /*Check if SID is not equal to 0xFFFF and NRC-21 is supported for the
															TxPduId number */
        if (( Dcm_DslDsdRxPduArray_ast[idxIndex_u8].Dcm_DsldSId_u16!= 0xFFFFu )
				&& ( Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8[idxIndex_u8]].
				txpduid_num_u8 == Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId] )
				&&( Dcm_DsldProtocol_pcst[(Dcm_DsldConnTable_pcst
				[Dcm_DsldRxTable_pcu8[idxIndex_u8]].protocol_num_u8)].nrc21_b !=
																		FALSE ))
        {
            Dcm_DslDsdRxPduArray_ast[idxIndex_u8].Dcm_DsldSId_u16 = 0xFFFF;
            break;
        }
    }

        /* If this Tx confirmation is for the response which was cancelled by
										Dcm using PduR_DcmCancelTransmit API */
        if(Dcm_flgCancelTransmit_b != TRUE)
        {
            if(Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId] ==
										Dcm_DsldGlobal_st.dataActiveTxPduId_u8)
            {
                /* Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 would be non-zero
					only in case of Tx Confirmation of a NRC 78, in case
                of positive response the same would have been reset to zero */
                 if(Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 > 0x0u)
                {
                  Dcm_Prv_PendRespConfirmation(Result);

                }
                else
                {
                    Dcm_Prv_CurrResConfirmation(Result);

                }
            }
#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF))
            else if((Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8
			[Dcm_Roe2MesContext_st.dcmRxPduId]].roetype2_txpdu_u8 ==
								Dcm_Dsld_Conf_cs.ptr_txtable_pca[DcmTxPduId])
											&&(Dcm_DsdRoe2State_en == DSD_SEND))
            {
                /* This call is for ROE type 2 response.
										Store the result and change the state */
                Dcm_Roe2TxResult_u8 = Result;
                Dcm_DsdRoe2State_en = DSD_TX_CONFIRMATION;
            }
#endif
            else
            {

            }
        }
        /* In case the TxConfirmation is due to CancelTransmit issued by Dcm */
        else
        {
            /* Set this flag to FALSE as the TxConfirmation for the
										CancelTransmit issued is identified */
           Dcm_flgCancelTransmit_b = FALSE;
        }
    }
    else
    {   /* Ignore the received Dcm_TpTxConfirmation as the TxConfirmationId
												(DcmTxPduId)is out of bounds */
        DCM_DET_ERROR(DCM_TPTXCONFIRMATION_ID ,DCM_E_DCMRXPDUID_RANGE_EXCEED)
    }
}




/**
 *******************************************************************************
 * Dcm_DsldDataConfirmation : response is sent. Change the DSD state machine
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 *******************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DsldDataConfirmation (void)
{
    /* No need to start S3 timer if event response get suppressed */
    if(Dcm_DsldGlobal_st.stDslState_en != DSL_ROETYPE1_RECIEVED)
    {
        /* start S3 timer */
        Dcm_StartS3MaxMonitoring();
    }

    if(Dcm_DsldGlobal_st.stDsdState_en == DSD_SEND)
    {
       /* response is sent, change the DSD state to DSD_TX_CONFIRMATION      */
      /* next call of Dcm_MainFunction() confirmation is called to Application*/
        Dcm_DsldGlobal_st.stDsdState_en = DSD_TX_CONFIRMATION ;
    }
    #if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    else
    {
        /*Check if this is to trigger the PduR for paged buffer transmission*/
        if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
        {
            /* If paged buffer Tx is on and Tx confirmation comes change the DSD
										state to DSD_TX_CONFIRMATION */
            Dcm_DsldGlobal_st.stDsdState_en = DSD_TX_CONFIRMATION ;
        }
    }
    #endif
#if((DCM_CFG_DSP_DIAGNOSTICSESSIONCONTROL_ENABLED != DCM_CFG_OFF) && \
 (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
    if (Dcm_SesChgOnWarmResp_b == TRUE)
    {
        Dcm_SesChgOnWarmResp_b = FALSE;
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
        (void)SchM_Switch_Dcm_DcmDiagnosticSessionControl(Dcm_Dsp_Session
												[Dcm_ctDiaSess_u8].SessionMode);
#endif
        (void)DcmAppl_Switch_DcmDiagnosticSessionControl(Dcm_Dsp_Session
											[Dcm_ctDiaSess_u8].session_level);
       /* Update the P2 Timer values */
       Dcm_DsldSetsessionTiming(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2str_max_u32,
                Dcm_Dsp_Session[Dcm_ctDiaSess_u8].P2_max_u32);

        /* Activate New Session requested */
        Dcm_SetSesCtrlType(Dcm_Dsp_Session[Dcm_ctDiaSess_u8].session_level);
    }
#endif
    Dcm_DslDsd_ComMChannelUpdate();
}

#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&\
							(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
/**
 *******************************************************************************
 * Dcm_KWPConfirmationForSplitResp :The handling of DSL,DSD states, Timer and
 *									the ComM channel when either the entire
 *									response is sent or when the timeout between
 *                                  the responses occurs in the KWP split
 *                                    response feature
 *
 * \param           status         : The status to be given to the application
									 as a confirmation
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 *******************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_KWPConfirmationForSplitResp(
							VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status)
{
    /* start the S3 timer */
        Dcm_StartS3MaxMonitoring();
    /* ComM channel update */
        Dcm_DslDsd_ComMChannelUpdate();
    /* In case the queue is enabled, handle the queued request,
				else free the DSL state machine */
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
        Dcm_QueueTransfer();
#else
        /* Lock required here to keep a consistency between DSL and DSD state */
        SchM_Enter_Dcm_Global_NoNest();
        Dcm_DsldGlobal_st.stDslState_en      = DSL_READY_FOR_RECEPTION;
        SchM_Exit_Dcm_Global_NoNest();
#endif
        /* s_isApplCalled_b == TRUE indicates that this function is called
					after the positive confirmation of the last split response
         * s_isApplCalled_b == FALSE indicates that this function is called when
											the split response timeout occurs */
        if(s_isApplCalled_b == FALSE)
        {
           /* Call the application confirmation functions */
           DcmAppl_DcmConfirmation(Dcm_DsldMsgContext_st.idContext,
                                   Dcm_DsldMsgContext_st.dcmRxPduId,
                                   Dcm_DsldConnTable_pcst[Dcm_DsldRxTable_pcu8
							[Dcm_DsldMsgContext_st.dcmRxPduId]].testaddr_u16,
                                    status);
        }
#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
            Dcm_CallRTEConfirmation(status);
#endif
        /* make DSD state as IDLE */
            Dcm_DsldGlobal_st.stDsdState_en      = DSD_IDLE;
}
#endif /*#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&
							(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))*/

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

