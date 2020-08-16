

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(StatusType,DCM_VAR) Dcm_PagedBufferTimerStatus_uchr; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"



/**
 **************************************************************************************************
 * Dcm_adrUpdatePage_pfct : This function pointer that stores the function for update page .
 *
 * \param           PageBufPtr: pointer to buffer where service fills the data
 *                  PageLen     Length of the buffer
 *
 *                  idContext   SID of the service.
 * \retval          None
 *
 * \seealso
 **************************************************************************************************/
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
P2FUNC(void,TYPEDEF,Dcm_adrUpdatePage_pfct) (
                                          VAR(Dcm_MsgType,AUTOMATIC) PageBufPtr,
                                          VAR(Dcm_MsgLenType,AUTOMATIC) PageLen
                                        );

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_StartPagedProcessing : With this API, the application gives the complete response length to DCM
 *                          and starts PagedBuffer handling. Complete response length information
 *                          (in bytes) is given in pMsgContext-> resDataLen Callback functions are used
 *                          to provide paged buffer handling in DSP and RTE. More information can be found
 *                          in the sequence chart in chapter 9.3.6 Process Service Request with PagedBuffer.
 *
 * \param           pMsgContext: message context table given by the service
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* Violation of AUTOSAR to over come MISRA warning */
FUNC(void,DCM_CODE) Dcm_StartPagedProcessing (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext )
{
    /* Check whether the service is sending less than maximum allowed paged buffer response buffer size for the protocol and this function is called only once*/

    if( (Dcm_Dsld_CheckTotalResponseLength(pMsgContext->resDataLen)!=FALSE)&&(Dcm_DsldTransmit_st.dataTxDataLength_u32 == 0x00uL))
    {
        /* Store the total number of bytes that can be transmitted on paged buffer info to the global variable */
        Dcm_DsldTransmit_st.dataTxDataLength_u32 = pMsgContext->resDataLen+1uL;
        /* Inform the service to fill the data into page */
        if(Dcm_adrUpdatePage_pfct != NULL_PTR)
        {
            (*Dcm_adrUpdatePage_pfct)(&Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].tx_buffer_pa[3],
                             Dcm_DsldMsgContext_st.resMaxDataLen);
        }
    }
	else
	{
        /* Report development error "Buffer overflow" to DET module if the DET module is enabled */
        DCM_DET_ERROR(DCM_PROCESSINGDONE_ID, DCM_E_INTERFACE_BUFFER_OVERFLOW)
	}
}




/**
 **************************************************************************************************
 * Dcm_ProcessPage:Application requests transmission of filled page More information can be found
 *                 in the sequence chart in chapter 9.3.6 Process Service Request with PagedBuffer.
 *
 *
 *
 *
 *
 * \param           FilledPageLen: Filled data length in current page
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ProcessPage(VAR(Dcm_MsgLenType, AUTOMATIC) FilledPageLen )
{

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    VAR(Dcm_DsldDslStatesType_ten, AUTOMATIC) stDslPreemptionState_en;
    stDslPreemptionState_en = Dcm_DsldGlobal_st.stDslPreemptionState_en;
    /* Multicore: When the protocol preemption has been initiated then this request should not be accepted */
    if((stDslPreemptionState_en != DSL_STOP_PROTOCOL)&&(stDslPreemptionState_en != DSL_STOP_ROE))
#endif
    {
        VAR(boolean,AUTOMATIC) flgSendResponse_b;

        /* Set default value */
        /*Flag for sending Response is set to false*/
        flgSendResponse_b = FALSE ;
        /* Check current page length is less than total buffer size */
        if((FilledPageLen <= (Dcm_DsldMsgContext_st.resMaxDataLen+1uL)) &&
                (Dcm_DsldGlobal_st.stDsdState_en == DSD_CALL_SERVICE))
        {
            /* Store the current page response length in global variable */
            Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32 = FilledPageLen;

            /* Check paged buffer transmission is started or not */

            if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
            {

                if (FilledPageLen != 0u)
                {
                    /* Change the DSD state to DSD_SEND */
                    /* Multicore: DSD state is changed only in MainFunction context OR
                     * in ROE/TxConfirmation APIs when DSD is IDLE/DSD is in SEND state. So there is no parallel writing when DSD is set to DSD_CALL_SERVICE
                     */

                    Dcm_DsldGlobal_st.stDsdState_en = DSD_SEND;

                    /* This call is for sending the consecutive pages */
                    /* In next call of Dcm_provideTxBuffer this page will be sent */
                    /* Multicore: No lock needed here as Dsl state is an atomic operation */
                    /* Also when this part of code is reached there is no chance that there is a parallel update to DSL state as the state machine is blocked by paged buffer*/
                    Dcm_DsldGlobal_st.stDslState_en = DSL_DATA_READY;
                }
                else
                {
                    /* Start Paged buffer timeout timer */
                    DCM_TimerStart(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32, 0x00u,
                                   Dcm_PagedBufferStartTick_u32, Dcm_PagedBufferTimerStatus_uchr)
                    /* Paged buffer timeout monitoring */
                    Dcm_DsldPagedBufferTimeout();
                }


            }
            else
            {
                /* This first call of Dcm_ProcessPage function. Frame positive response */
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2] = Dcm_DsldGlobal_st.dataSid_u8 | 0x40u;

                /* Active buffer pointer starts from first element in buffer */
                Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8    = &Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[2];

                /* Including Sid current page length increment by one */
                Dcm_DsldGlobal_st.dataCurrentPageRespLength_u32++;

                /* Set the flag to indicate start of paged buffer */

                Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = TRUE;

                /* Change the DSD state to DSD_SEND */
                Dcm_DsldGlobal_st.stDsdState_en = DSD_SEND;

                /* Trigger response in DSL_SEND_FINAL_RESPONSE state */
                /* Multicore: No Lock needed here as if Dcm gets Tx confirmation of waitpend before this line DSL will be WaitForTxCOnfirm and will transmit the page immediately */
                /* And if the confirmation is received after this line then page is transmitted in the next DSL state machine */

                Dcm_DsldTransmit_st.stDslNextState_en = DSL_SEND_FINAL_RESPONSE;

                /* Check whether DSL is sending the wait pend or not */
                /* Multicore: No lock needed here as Dsl state is an atomic read operation */
                /* When this code is reached and paged buffer is actve there are no chances of parallel update to DSL state */

                if(Dcm_DsldGlobal_st.stDslState_en == DSL_WAIT_FOR_CONFIRMATION)
                {
                    /* Empty if statement, intended here */
                }
                /*Check if positive response is sent and wait pending counter is set to Zero  */
                else if ((Dcm_DsldMsgContext_st.msgAddInfo.suppressPosResponse !=FALSE) &&
                    (Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 == 0))
                {
                    /* Start P2 Timer with timer value as zero , so that 0x78 can be sent in the next immediate proc. */
                    DCM_TimerStart(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32, 0x00u, Dcm_P2OrS3StartTick_u32, Dcm_P2OrS3TimerStatus_uchr)

                }
                else
                {

                    /* Update data in PDU structure to register total number bytes can send on paged buffer */
                    Dcm_DsldPduInfo_st.SduDataPtr = &Dcm_DsldGlobal_st.adrActiveTxBuffer_tpu8[0];

                    Dcm_DsldPduInfo_st.SduLength  = (PduLengthType) Dcm_DsldTransmit_st.dataTxDataLength_u32;

                    /* change the DSL such that in next call of Dcm_provideTxBuffer page should be transmitted */
                    /* Multicore: No Lock needed here because when this code is reached, paged buffer is active hence
                     * there are no chances of parallel update to DSL state */
                    Dcm_DsldGlobal_st.stDslState_en = DSL_DATA_READY;

                    Dcm_DsldGlobal_st.cntrWaitpendCounter_u8 = 0x0u;

                    /* after getting the Tx confirmation DSL state changed to DSL_READY_FOR_RECEPTION state */
                    Dcm_DsldTransmit_st.stDslNextState_en = DSL_READY_FOR_RECEPTION;

                    /* Response can be sent */

                    flgSendResponse_b = TRUE;
                }
                /*Check if the Response is sent*/
                if(flgSendResponse_b != FALSE)
                {
                    /* Send the response */
                    Dcm_DsldSendResponse(&Dcm_DsldPduInfo_st);
                }
            }
        }
    }
}

/**
 **************************************************************************************************
 * Dcm_DsldPagedBufferTimeout : Static function to monitor the Paged buffer timeout
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void, DCM_CODE) Dcm_DsldPagedBufferTimeout(void)
{
    /*This is to trigger the PduR for paged buffer transmission */
    if(Dcm_DsldGlobal_st.flgPagedBufferTxOn_b != FALSE)
    {
        /* Check paged buffer timer */
        DCM_TimerProcess(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32,Dcm_PagedBufferStartTick_u32,Dcm_PagedBufferTimerStatus_uchr)

        if(DCM_TimerElapsed(Dcm_DsldGlobal_st.dataPagedBufferTimeout_u32))
        {
			/* Report development error "DCM_E_INTERFACE_TIMEOUT " to DET module if the DET module is enabled */
        	DCM_DET_ERROR(DCM_PAGEDBUFFER_ID , DCM_E_INTERFACE_TIMEOUT )
            /* Paged buffer time is elapsed, Reset the DCM */
            /* Lock required here to keep a consistency between DSL and DSD state */
            SchM_Enter_Dcm_Global_NoNest();
            /* Multicore: Lock necessary to avoid parallel access in Dcm_ResponseOnOneEvent API */

            Dcm_DsldGlobal_st.stDsdState_en = DSD_IDLE;

            /* Multicore: No Lock needed here as the parallel update to DSL state is not possible when Dcm
             * is busy with the request on which paged buffer is triggered. */
            Dcm_DsldGlobal_st.stDslState_en = DSL_READY_FOR_RECEPTION;
            SchM_Exit_Dcm_Global_NoNest();

            /* To reset the service, call the callback application */
            DcmAppl_DcmCancelPagedBufferProcessing(Dcm_DsldGlobal_st.dataSid_u8);

            /* Reset the flag */

            Dcm_DsldGlobal_st.flgPagedBufferTxOn_b = FALSE;
        }
    }
}

/**
 **************************************************************************************************
 * Dcm_Dsld_CheckTotalResponseLength : API called to check if the total response length has exceeded the
 * maximum possible response length for the API.
 *
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(boolean,DCM_CODE) Dcm_Dsld_CheckTotalResponseLength(VAR(Dcm_MsgLenType,AUTOMATIC) TotalResLen_u32 )
{
    VAR(boolean,AUTOMATIC) returnVal_b;   /* Variable to store the return value */

    /* If the total response length is less than or equal to the maximum response lnegth configured for paged buffer response -1( considering the SID), return TRUE else return FALSE */
    if(TotalResLen_u32<=((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].maxResponseLength_u32)-1uL))
    {
        /*Initialize the return value to True*/
        returnVal_b = TRUE;
    }
    else
    {
        /*Set the return value to false*/
        returnVal_b = FALSE;
    }
    return (returnVal_b);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

