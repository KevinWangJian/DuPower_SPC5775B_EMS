

#include "PduR_Prv.h"
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "PduR_BufferPool.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */


#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GetTpBuffer(  P2CONST( PduR_GT_Tp, TYPEDEF, PDUR_CONST ) gt,
                                                                    VAR(PduLengthType, AUTOMATIC) TpSduLength)
{
    /* Start: Variable declaration */

    /* Fetch the fixed Buffer details */
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    /* Initialise with primary session first */
    PduR_TpSessDynPtr  SessionPtr;
    VAR(BufReq_ReturnType, AUTOMATIC)  rtn;
    /* End: Variable declaration */

    /* Start: Variable Initialization */
    fifo = (gt->buffer);
    SessionPtr = fifo->connectionTable->primarySession;
    rtn = BUFREQ_OK;
    /* End: Variable Initialization */
#ifdef PDUR_BUFFERPOOL_SUPPORT
    /* Check if dedicated buffer is configured for this routing path */
    if((fifo->begin != NULL_PTR) && (fifo->buffPoolId == 0xFFFFu))
    {
        if (TpSduLength > fifo->eltSize)
        {
            rtn =  BUFREQ_E_OVFL;
        }
        else
        {
            fifo->connectionTable->primarySession->bufferPtr = fifo->begin;
            fifo->connectionTable->primarySession->bufferLength = fifo->eltSize;
        }
    }
    /* Buffer pool is configured for the routing path */
    else
    {
        /* Lock required for consistent operation of buffer pool manager */
        SchM_Enter_PduR_LockTpGatewayBuffer();
        /* Call the buffer pool, to get the appropriate buffer from the buffer pool */
        rtn = PduR_BufferPoolRequest(fifo->buffPoolId, TpSduLength, &SessionPtr->bufferLength, &SessionPtr->bufferPtr);
        /* FC_VariationPoint_START */
#ifdef PDUR_QUEUEING_SUPPORT
        /* If first buffer is obtained suscessfully and queue is configiured , get the second buffer */
        if ((rtn == BUFREQ_OK) && (gt->TpGwQueueSize == 2u))
        {
            /* Move to secondary session */
            SessionPtr = fifo->connectionTable->secondarySession;
            rtn = PduR_BufferPoolRequest(fifo->buffPoolId, TpSduLength, &SessionPtr->bufferLength, &SessionPtr->bufferPtr);
            /* For queuing to work properly , I need both the buffers*/
            if (rtn != BUFREQ_OK)
            {
                /* Second buffer request is failed, so release the first buffer as well. */
                PduR_ReleaseTpBuffer(gt);
            }
        }
#endif /* PDUR_QUEUEING_SUPPORT */
        /* FC_VariationPoint_END */
        SchM_Exit_PduR_LockTpGatewayBuffer();
    }
#else
    /* Buffer pool is not configured, So Just update the dedicated buffer */
    if (TpSduLength > fifo->eltSize)
    {
        rtn =  BUFREQ_E_OVFL;
    }
    else
    {
        fifo->connectionTable->primarySession->bufferPtr = fifo->begin;
        fifo->connectionTable->primarySession->bufferLength = fifo->eltSize;
    }
#endif /* PDUR_BUFFERPOOL_SUPPORT */
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

FUNC( void, PDUR_CODE ) PduR_ReleaseTpBuffer(  P2CONST( PduR_GT_Tp, TYPEDEF, PDUR_CONST ) gt)
{
#ifdef PDUR_BUFFERPOOL_SUPPORT
    /* Initialise with primary session first */
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    PduR_TpSessDynPtr  SessionPtr;

    fifo = (gt->buffer);
    /* Buffer pool is used for the connection */
    if (fifo->buffPoolId != 0xFFFFu)
    {
        /* Lock required for consistent operation of buffer pool manager */
        SchM_Enter_PduR_LockTpGatewayBuffer();
        /* Release the primary session buffer first */
        SessionPtr = fifo->connectionTable->primarySession;
        PduR_BufferPoolRelease(fifo->buffPoolId, SessionPtr->bufferPtr);
        SessionPtr->bufferPtr = NULL_PTR;
        /* FC_VariationPoint_START */
#ifdef PDUR_QUEUEING_SUPPORT
        /* In case of queue, release the second buffer as well */
        if (gt->TpGwQueueSize == 2u)
        {
            SessionPtr = fifo->connectionTable->secondarySession;
            PduR_BufferPoolRelease(fifo->buffPoolId, SessionPtr->bufferPtr);
            SessionPtr->bufferPtr = NULL_PTR;
        }
#endif /* PDUR_QUEUEING_SUPPORT */
        /* FC_VariationPoint_END */
        SchM_Exit_PduR_LockTpGatewayBuffer();
    }
#endif /* PDUR_BUFFERPOOL_SUPPORT */
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_TPGATEWAY_SUPPORT */

