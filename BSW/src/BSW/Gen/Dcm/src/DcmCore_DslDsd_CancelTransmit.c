


#include "DcmCore_DslDsd_Inf.h"

#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) || (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_CancelTransmit_u8 : Function to cancel the ongoing transmission of the response during
 *                      protocol preemption.
 *
 * \param           None
 *
 *
 * \retval          E_NOT_OK  Ongoing transmission is not canceled
 *                  E_OK      Ongoing transmission is canceled
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_CancelTransmit_u8(void)
{
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    VAR(boolean,AUTOMATIC)  flgPagedBufferTxOn_b;
#endif
    VAR(Dcm_DsldDslStatesType_ten,AUTOMATIC) dataDslState_en; /* Local variable to store DSL state */
    VAR(Dcm_DsldDsdStatesType_ten,AUTOMATIC) stDsdState_en;
    VAR(Std_ReturnType,AUTOMATIC) stCancelTx_u8; /* Status of cancel transmit function */

    stCancelTx_u8 = E_NOT_OK;             /* Set the state to E_NOT_OK */
    Dcm_flgCancelTransmit_b = FALSE;     /* Set this value to FALSE */

    /* Multicore: Lock added here to ensure that the DSL, DSD states are updated together here.
     * The active request should not modify the state machine variables separately only during
     * this protocol pre-emption scenario
     */
    SchM_Enter_Dcm_Global_NoNest();

    dataDslState_en = Dcm_DsldGlobal_st.stDslState_en; /* Copy the DSL state to local variable */
    stDsdState_en        = Dcm_DsldGlobal_st.stDsdState_en;

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    flgPagedBufferTxOn_b = Dcm_DsldGlobal_st.flgPagedBufferTxOn_b;
#endif

    SchM_Exit_Dcm_Global_NoNest();

    /* If Normal Positive/Negative Response is under transmission, DSL state is DSL_WAIT_FOR_CONFIRMATION */
    /* If ROE/RDPI Type1 response is under transmission, DSL state is DSL_ROETYPE1_RECIEVED and DSD in DSD_SEND */
    if((dataDslState_en == DSL_WAIT_FOR_CONFIRMATION) ||
       ((dataDslState_en == DSL_ROETYPE1_RECIEVED) && (stDsdState_en == DSD_SEND)))
    {
        /* Set the status to Cancel the transmission */
        /*Set the cancel transmit status flag to True */
        Dcm_flgCancelTransmit_b = TRUE;
    }

    #if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    /* If paged buffer is active then the following cases can occur */
    /* 1. First page is not sent yet as there is ongoing waitpend response */
    /* 2. Consecutive pages are being sent */
    /* 3. All pages are sent to PduR and waiting for Tx confirmation */
    /*Check if the paged buffer flag is active*/
    if(flgPagedBufferTxOn_b != FALSE)
    {
        /* Set the status to Cancel the transmission */
        /*Set the cancel transmit status flag to True*/
        Dcm_flgCancelTransmit_b = TRUE;

        /* Cancel the paged buffer processing for the active Service */
        DcmAppl_DcmCancelPagedBufferProcessing(Dcm_DsldGlobal_st.dataSid_u8);
    }
    #endif
    /* If Cancellation of transmission is needed */
    /*Check if the cancel transmit status flag is set to True*/
    if(Dcm_flgCancelTransmit_b != FALSE)
    {
        /* Call the PduR API to cancel the initiated Transmission */
        stCancelTx_u8 = PduR_DcmCancelTransmit(Dcm_DsldGlobal_st.dataOldtxPduId_u8);

        /* If cancellation is not successfull */
        if(stCancelTx_u8 != E_OK)
        {
            /* Set this flag to False as Cancellation was unsuccessful by lower layer , so a Txconfirmation call cannot be expected for cancelled transmit */
            (void)Dcm_StopProtocol(Dcm_CurProtocol_u8);
            Dcm_StopProtocolflag_b = TRUE;
            Dcm_flgCancelTransmit_b = FALSE;
        }
    }
    return(stCancelTx_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


