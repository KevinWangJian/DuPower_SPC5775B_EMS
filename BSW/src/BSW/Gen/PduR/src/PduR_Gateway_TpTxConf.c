
#include "PduR_Prv.h"
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#ifdef PDUR_BUFFERPOOL_SUPPORT
#include "PduR_BufferPool.h"
#endif /* PDUR_BUFFERPOOL_SUPPORT */

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_Tp_TxConfirmation_Func - This function is called by a transport protocol module after the I-PDU has been transmitted
 *                                    on its network, the result will reveal if the transmission was successful or not.
 *
 * \param           PduIdType gwId            - Identification of the transmitted I-PDU.
 *                  Std_ReturnType result    - Result of the transmission of the I-PDU.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_GF_Tp_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwId,
                                                   VAR(Std_ReturnType, AUTOMATIC) result)
{
    /* Start: Variable declaration */
    PduR_GT_TpPtr      gt;
    /* Fetch the fixed Buffer details */
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    /* Fetch the RAM structure details  */
    PduR_TpSessDynPtr  SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;
    /* End: Variable declaration */

    /* Start: Variable Initialization */
    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = fifo->connectionTable;
    SessionPtr = ConnectionPtr->primarySession;
    /* End: Variable Initialization */

    /* Check if the RX and TX status of the Session Ptr , it shouldn't be IDLE during TxConfirmation */
    if ((SessionPtr->Rx_Status == PDUR_SESSION_IDLE) || (SessionPtr->Tx_Status == PDUR_TX_IDLE))
    {
        return;
    }
    /* FC_VariationPoint_START */
#ifdef PDUR_QUEUEING_SUPPORT
    /* Check the value of activeSessionCount, at this stage it shouldn't be 0 */
    if ( ConnectionPtr->activeSessionCount != 0)
    {
        /* Close the session */
        ConnectionPtr->activeSessionCount--;
        /* Transmission on primary session finished */
        /* Clear the session states */
        PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);
    }
    else
    {
        /* active session count is zero, so return!!*/
        return;
    }
    /* After closing this session, if another active session is found , then switch the sessions */
    if(ConnectionPtr->activeSessionCount == 1)
    {
        /* The present secondary session becomes the primary session */
        ConnectionPtr->primarySession =  ConnectionPtr->secondarySession;
        /* Just closed session, becomes secondary session */
        ConnectionPtr->secondarySession = SessionPtr;

        /* Check for pending operations on the new primary session */
        SessionPtr = ConnectionPtr->primarySession;

        if((SessionPtr->Tx_Status == PDUR_TX_IDLE) && (SessionPtr->numRxLength == SessionPtr->SduLength))
        {
            VAR(PduInfoType,AUTOMATIC) readerPduInfo;
            VAR(Std_ReturnType, AUTOMATIC)  Ret_val;

            /* Ensure that the reader's PduInfo object is initialized */
            readerPduInfo.SduDataPtr = SessionPtr->readPtr;
            /* 1st time call, the complete length should be transmitted to lower layer when TpTransmit is called */
            readerPduInfo.SduLength  = SessionPtr->SduLength;

            /* Change the TxStatus to in-progress and then invoke <LoTp>_Transmit function */
            SessionPtr->Tx_Status = PDUR_TX_INPROGRESS;

            /* Call DestLoTp transmit once the TpThreshold is reached*/
            #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
            Ret_val = PDUR_BASE_RPTBL(loTxTablePtr)[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
            #else
            Ret_val = PduR_loTransmitTable[(gt->loTransmitID)].PduR_loTransmitFunc(gt->loId, &readerPduInfo);
            #endif

            /* check the return value of the LoTp Transmit API */
            if(Ret_val != E_OK)
            {
                /* If Dest LoTP Transmit function returns E_NOT_OK, immediately cancel the reception*/
                ConnectionPtr->activeSessionCount--;
                /* Clear the session states */
                PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);
            }
        }

    }
    if(ConnectionPtr->activeSessionCount == 0)
    {
         /* Release the acquired buffers . The below function will release buffer only if buffer pool is used */
        PduR_ReleaseTpBuffer(gt);
    }
#else
    /* FC_VariationPoint_END */
    /* Release the acquired buffers . The below function will release buffer only if buffer pool is used */
    PduR_ReleaseTpBuffer(gt);
    /* Clear the session states */
    PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);
    /* FC_VariationPoint_START */
#endif /* #ifdef PDUR_QUEUEING_SUPPORT */
    /* FC_VariationPoint_END */

    (void) result;
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_TPGATEWAY_SUPPORT */

