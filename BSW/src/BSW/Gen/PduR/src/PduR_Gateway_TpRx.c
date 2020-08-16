
/* StartOfReception, CopyRxData and RxIndication to support gatewaying between TP layers, when using a FIFO */

#include "PduR_Prv.h"
#include "Dem.h"             /* For Dem_ReportErrorStatus */
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
//#error "AUTOSAR minor version undefined or mismatched"
#endif


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
 * PduR_GF_Tp_StartOfReception_Func - Handle StartOfReception for TP gatewaying, for those cases where a
 *                                    FIFO buffer is in use
 *
 * Note that the v2 PDUR specification:
 * - does not appear to allow a FIFO to be configured for store-and-forward TP
 * gatewaying (i.e. for concurrent operation of a TP gateway).
 * - does not specify that a FIFO must be provided for
 * store-and-forward TP gatewaying. Therefore, although our implementation allows a FIFO to be used
 * for store-and- forward TP gatewaying, this cannot actually be configured and will never occur
 * Store-and-forward gatewaying will always use a single buffer.
 * A FIFO will only be used for routing-on-the-fly, when the multiple chunks of a PDU must be stored
 * separately (i.e. each in its own FIFO entry).
 *
 * \param           PduIdType gwId  :ID of N-PDU that has been received
 *                  PduLengthType  len:This length identifies the overall number of bytes to be received.
 *                  PduR_TpRxPduInfoPtrPtr pduInfoPtr:  Pointer to pointer to PduInfoStructure containing SDU data
 *                  pointer and SDU length of a receive buffer.
 *
 * \retval          BufReq_ReturnType r
 *                  BUFREQ_OK - Buffer request accomplished successful.
 *                  BUFREQ_E_OVFL - Receiver is not able to receive number of TpSduLength bytes; no buffer provided.
 *                  BUFREQ_E_NOT_OK - Buffer request not successful, no buffer provided.
 * \seealso
 * \usedresources   PDUR172
 **************************************************************************************************
 */

/* MR12 RULE 8.13 VIOLATION: A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object.
 But AUTOSAR SWS specification signature is as below, Hence suppressed */
FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_StartOfReception_Func( VAR(PduIdType, AUTOMATIC) gwId,
        P2VAR(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
        VAR(PduLengthType, AUTOMATIC) TpSduLength,
        P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{

    /* Start: Variable declaration */
    PduR_GT_TpPtr gt;
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    VAR(BufReq_ReturnType, AUTOMATIC) rtn;
    PduR_TpSessDynPtr SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;
    /* End: Variable declaration */

    /* Start: Variable Initialization */
    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    rtn = BUFREQ_OK;
    ConnectionPtr = fifo->connectionTable;
    /* Working on primary session by default*/
    SessionPtr = ConnectionPtr->primarySession;
    /* End: Variable Initialization */


    /* FC_VariationPoint_START */
#ifdef PDUR_QUEUEING_SUPPORT
    if (ConnectionPtr->activeSessionCount == 0)
    {
        /* The below function handles requesting two buffers in case of queuing is enabled */
        rtn = PduR_GetTpBuffer(gt,TpSduLength);
        if (rtn != BUFREQ_OK)
        {
            return rtn;
        }

    }
    /* One session is already in progress */
    else if((ConnectionPtr->activeSessionCount == 1) && (gt->TpGwQueueSize == 2u))

    {
        /* Second reception has to be accepted, only if the first reception is completed
         * There is no need to request the buffer here, as it is already requested
         * Actually the check for Reception finished on primary session not required here, as TP itself wouldnt accept
         * the second request on the same handle
         * If there is no queue configured for the connection , then there is no point in considering the backup
         * session
         * If total PDU length of second SOR is more than allocated buffer, return with buffer overflow. */
        if((SessionPtr->Rx_Status != PDUR_RX_FINISHED) || (TpSduLength > fifo->connectionTable->secondarySession->bufferLength))
        {
            return BUFREQ_E_NOT_OK;
        }

        /* Working on secondary session now */
        SessionPtr = ConnectionPtr->secondarySession;

    }

    else
    {
        /* More than 2 reception requests will not be handled, hence E_NOT_OK is returned to the TP
         * Or if the first session's reception was not completed yet */
        return BUFREQ_E_NOT_OK;
    }
    /* Increment active session count as a new session is acquired */
    ConnectionPtr->activeSessionCount++;

#else
    /* FC_VariationPoint_END */
    /* Queuing not supported */
    /* It should be FREE for reception */
    if (SessionPtr->Rx_Status != PDUR_SESSION_IDLE)
    {
        return BUFREQ_E_NOT_OK;
    }
    rtn = PduR_GetTpBuffer(gt,TpSduLength);
    /* Check if requested buffer is successfully allocated */
    if (rtn != BUFREQ_OK)
    {
        return rtn;
    }
    /* FC_VariationPoint_START */
#endif /* #ifdef PDUR_QUEUEING_SUPPORT */
    /* FC_VariationPoint_END */
    /* Buffer is allocated, initilize the session pointer variables */

    /* Update read ptr and write ptr to the buffer pointer */
    SessionPtr->readPtr = SessionPtr->bufferPtr;
    SessionPtr->writePtr = SessionPtr->bufferPtr;
    /* Update the alloted buffer size to buffer size pointer  */
    *bufferSizePtr = SessionPtr->bufferLength;
    /* Store the Complete Message Length Received */
    SessionPtr->SduLength = TpSduLength;

    /* This PduInfoType info is not used, because the same pointer maybe provided in the first CopyRxData call
     * Hence ignored  */
    (void) info ;
    /* Set a flag indicating that the reception is started */
    SessionPtr->Rx_Status = PDUR_RX_INPROGRESS;

    return rtn;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_Tp_CopyRxData_Func - Handle CopyRxData for TP gatewaying, for those cases where a
 *                                    FIFO buffer is in use
 *
 * Note that the v2 PDUR specification:
 * - does not appear to allow a FIFO to be configured for store-and-forward TP
 * gatewaying (i.e. for concurrent operation of a TP gateway).
 * - does not specify that a FIFO must be provided for
 * store-and-forward TP gatewaying. Therefore, although our implementation allows a FIFO to be used
 * for store-and- forward TP gatewaying, this cannot actually be configured and will never occur
 * Store-and-forward gatewaying will always use a single buffer.
 * A FIFO will only be used for routing-on-the-fly, when the multiple chunks of a PDU must be stored
 * separately (i.e. each in its own FIFO entry).
 *
 * \param           PduIdType gwId  :ID of N-PDU that has been received
 *                  PduLengthType  len:This length identifies the overall number of bytes to be received.
 *                  PduR_TpRxPduInfoPtrPtr pduInfoPtr:  Pointer to pointer to PduInfoStructure containing SDU data
 *                  pointer and SDU length of a receive buffer.
 *
 * \retval          BufReq_ReturnType r
 *                  BUFREQ_OK - Buffer request accomplished successful.
 *                  BUFREQ_E_OVFL - Receiver is not able to receive number of TpSduLength bytes; no buffer provided.
 *                  BUFREQ_E_NOT_OK - Buffer request not successful, no buffer provided.
 * \seealso
 * \usedresources   PDUR172
 **************************************************************************************************
 */

/* MR12 RULE 8.13 VIOLATION: A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object.
 But AUTOSAR SWS specification signature is as below, Hence suppressed */
FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_CopyRxData_Func( VAR(PduIdType, AUTOMATIC) gwId,
        P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info,
        P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{
    /* Start: Variable declaration */
    PduR_GT_TpPtr gt;
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    /*By default tx status flag is set to false */
    boolean PduRTransmitFlag = FALSE;
    PduR_TpSessDynPtr SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;
    /* End: Variable declaration */

    /* Start: Variable Initialization */
    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = fifo->connectionTable;
    /* End: Variable Initialization */

    PduR_LoadActiveSession(&SessionPtr,ConnectionPtr);

    /* This check ensures that StartOfReception API is called before CopyRxData call*/
    if ((SessionPtr == NULL_PTR) || (SessionPtr->Rx_Status != PDUR_RX_INPROGRESS) || (info->SduLength > (SessionPtr->SduLength - SessionPtr->numRxLength)))
    {
        return BUFREQ_E_NOT_OK;
    }

    if ( info->SduLength == 0u )
    {
        /* Update outpointer with remaining free buffer length */
        *bufferSizePtr = SessionPtr->bufferLength - SessionPtr->numRxLength;
        return BUFREQ_OK;
    }


    /* Copy the data into the receive buffer and update the write pointer */
    rba_BswSrv_MemCopy8(SessionPtr->writePtr,info->SduDataPtr,info->SduLength);


    /* Increment the write pointer to the length of sdulength */
    SessionPtr->writePtr += info->SduLength;
    /* Length of data received */
    SessionPtr->numRxLength = SessionPtr->numRxLength + info->SduLength;

    /* Update remaining buffer size info to underlying TP layer */
    *(bufferSizePtr) = SessionPtr->bufferLength - SessionPtr->numRxLength;
        /* FC_VariationPoint_START */
#ifdef PDUR_QUEUEING_SUPPORT
    /* The transmission for primary session is ongoing, So do not trigger the transmission for the secondary session
     * Just copy the secondary session's data into the buffer and return */
    if(SessionPtr == ConnectionPtr->secondarySession)
    {
        return BUFREQ_OK;
    }
#endif /* PDUR_QUEUEING_SUPPORT */
    /* FC_VariationPoint_END */
    /* In case of Multicast gateway */
    if(gt->numOfLowerLayers > 1u)
    {
        /* If it is a multicast gateway, then this function should be called only once
         * All the data should be copied in one single function call , as we take only single frame requests here
         * */
        if((info->SduLength != SessionPtr->SduLength) || (SessionPtr->Tx_Status != PDUR_TX_IDLE))
        {
            /* Because requested sdulength is more than the message length */
            return BUFREQ_E_NOT_OK;

        } /* end of - ((info->SduLength == SessionPtr->SduLength) && (SessionPtr->Tx_Status == PDUR_TX_IDLE)) */
        else
        {
            /*Set the TX flag to call transmit function*/
            PduRTransmitFlag = TRUE;
        }
    }
    /* Unicast gateway */
    else
    {
        /* Check if TpTransmit API is called or not */
        /* Call LoTp transmit if received length in PduRTp buffer is more than TpThreshold OR
         * requested message length is less than TpThreshold */
        if(!((SessionPtr->Tx_Status == PDUR_TX_IDLE) && ((SessionPtr->numRxLength >= gt->TpThreshold) || \
                                ((SessionPtr->SduLength <= gt->TpThreshold) && (SessionPtr->numRxLength == SessionPtr->SduLength)))))
        {
            /* Either the LoTp Transmit is already called or
             * the PduR doesn't have enough data to trigger for the transmission */
            return BUFREQ_OK;

        }
        else
        {
            /*Set the TX flag to call transmit function*/
            PduRTransmitFlag = TRUE;
        }
    }

    /* Check if the Tx flag is set? If set then all the conditions to transmit are met*/
    if(PduRTransmitFlag)
    {
        VAR(PduInfoType,AUTOMATIC) readerPduInfo;
        VAR(Std_ReturnType, AUTOMATIC) Ret_val = E_OK;

        /* Ensure that the reader's PduInfo object is initialized */
        readerPduInfo.SduDataPtr = SessionPtr->readPtr;
        /*At the first time the complete length should be transmitted to lower layer when TpTransmit is called */
        readerPduInfo.SduLength = SessionPtr->SduLength;

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
            /* Change the TxStatus back to TxIdle if <LoTp>_Transmit function returns E_NOT_OK */
            SessionPtr->Tx_Status = PDUR_TX_IDLE;

            /* If Dest LoTP Transmit function returns E_NOT_OK, immediately cancel the ongoing reception*/
            return BUFREQ_E_NOT_OK;
        }
    }

    return BUFREQ_OK;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_Tp_RxIndication_Func - Called by the transport protocol module after an I-PDU has been received successfully or
 *                                   when an error occurred. It is also used to confirm cancellation of an I-PDU.
 *
 * \param           PduIdType gwId              :        ID of  N-PDU that has been received
 *                  Std_ReturnType  result     : Result of the reception.
 *                  E_OK in case TP reception completed successfully
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_GF_Tp_RxIndication_Func( VAR(PduIdType, AUTOMATIC) gwId,
        VAR(Std_ReturnType, AUTOMATIC) result)
{
    /* Start: Variable declaration */
    PduR_GT_TpPtr gt;
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    PduR_TpSessDynPtr SessionPtr;
    PduR_TpConnDynPtr ConnectionPtr;
    /* End: Variable declaration */

    /* Start: Variable Initialization */
    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = (PduR_TpConnDynPtr)(fifo->connectionTable);
    /* End: Variable Initialization */

    PduR_LoadActiveSession(&SessionPtr,ConnectionPtr);
    if (SessionPtr == NULL_PTR)
    {
        /* Session is not found */
        return;
    }
    /*At this stage Session ptr Rx status should be in PDUR_RX_INPROGRESS */
    if (SessionPtr->Rx_Status != PDUR_RX_INPROGRESS)
    {
        return;
    }

    /*If Rx Indication result is OK, then set Session ptr TRX status to FINISHED*/
    if (result == E_OK)
    {
        SessionPtr->Rx_Status = PDUR_RX_FINISHED;
    }
    else
    {
        /* FC_VariationPoint_START */
        /*If Rx Indication result is NOT OK, then release and reset respective buffer */
#ifdef PDUR_QUEUEING_SUPPORT
        /* Close the current session as it has reported error during reception */
        if(ConnectionPtr->activeSessionCount != 0)
        {
            ConnectionPtr->activeSessionCount--;
            /* If there are no active sessions , then release the buffers */
            if(ConnectionPtr->activeSessionCount == 0)
            {
                PduR_ReleaseTpBuffer(gt);
            }
        }
#else
        /* FC_VariationPoint_END */
        /* Release the acquired buffers . The below function will release buffer only if buffer pool is used */
        PduR_ReleaseTpBuffer(gt);
        /* FC_VariationPoint_START */
#endif
        /* FC_VariationPoint_END */
        /* Clear the session states */
        PduR_ResetPduR_FIFO_Tp_dynamic_Structure(SessionPtr);

    }

}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_TPGATEWAY_SUPPORT */

