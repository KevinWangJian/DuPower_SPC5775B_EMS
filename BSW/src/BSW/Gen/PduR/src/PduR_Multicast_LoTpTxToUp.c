
/* Support functions for mapping TpTx callbacks to the upper layer  */

#include "PduR_Prv.h"
#include "PduR_Mc.h"

/* Only enabled if Multicast to Tp support is enabled */
/* This macro has to be generated in PduR_Cfg.h if TP Multicast is required */
#if defined(PDUR_MULTICAST_TO_TP_SUPPORT) && (PDUR_MULTICAST_TO_TP_SUPPORT != 0)
/* ------------------------------------------------------------------------ */

/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_MF_McTpTx_ProvideTxBuffer
 *                  Provide the support functions for mapping TpTx callbacks to the upper layer
 *
 *
 *
 * \param           PduIdType mcId        :multicast ID that has to be transmitted.
 *                  P2VAR( P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), TYPEDEF, PDUR_APPL_DATA ) ptr:Pointer to pointer to PduInfoStructure containing SDU data pointer and
 *                                             SDU length of a transmit buffer.
 *                  uint16 len                :length of the requested transmit buffer.
 *
 * \retval          BUFREQ_OK       - Buffer request accomplished successful
 *                  BUFREQ_E_BUSY   - Currently no buffer of the requested size is available
 *                  BUFREQ_E_NOT_OK - Buffer request not successful, no buffer provided.
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_MF_McTpTx_CopyTxData( VAR(PduIdType, AUTOMATIC) mcId,
                                                                     P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                     P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr )
{
    VAR(BufReq_ReturnType, AUTOMATIC) r;


    P2CONST( PduR_MT_LoTpTxToUp, AUTOMATIC, PDUR_CONST ) mcTable = PDUR_LOTP_TX_MC_BASE + mcId;
    P2VAR( PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state = PDUR_LOTP_TX_STATE_BASE + mcId;

    SchM_Enter_PduR_LockMcTpTxCopyTxData();

    if (state->pduPtr == NULL_PTR)
    {
        /* If I-PDU is invoked or a previous request failed,forward the request to the upper layer */

        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        state->allocError = PDUR_BASE_RPTBL(upTpTxDataTablePtr)[mcTable->toUp.upProvideTxBufID].PduR_upTpCopyTxDataFunc(mcTable->toUp.upId, state->pduPtr, retry, availableDataPtr);
        #else
        state->allocError = PduR_upTpCopyTxDataTable[mcTable->toUp.upProvideTxBufID].PduR_upTpCopyTxDataFunc(mcTable->toUp.upId, state->pduPtr, retry, availableDataPtr);
        #endif
        if (state->allocError != BUFREQ_OK)
        {
            /* Request failed: ensure retry */
            state->pduPtr = NULL_PTR;
        }
    }
    if(ptr != NULL_PTR)
    {
    }

/*    *ptr = state->pduPtr; */
    ptr = state->pduPtr;
    r = state->allocError;
    /* exit critical area */
    SchM_Exit_PduR_LockMcTpTxCopyTxData();

    return r;

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
 * PduR_MF_McTpTx_TxConfirmation
 *                  Provide the support functions for mapping TpTx callbacks to the upper layer
 *
 *   with Result  =  E_OK after the complete TP data have successfully been transmitted,
 *   with Result != E_OK if an error (e.g. timeout) has occurred during the TP transmission.
 *                  This enables unlocking of the transmit buffer.
 *
 *
 * \param           PduR_LayerType layerId:Not used
 *                  PduIdType mcId        :multicast ID that has been transmitted.
 *                  Std_ReturnType result:Result of the TP reception.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( void, PDUR_CODE ) PduR_MF_McTpTx_TxConfirmation( VAR(PduR_LayerType, AUTOMATIC) layerId,
                                                       VAR(PduIdType, AUTOMATIC) mcId,
                                                       VAR(Std_ReturnType, AUTOMATIC) result)
{

    P2CONST( PduR_MT_LoTpTxToUp, AUTOMATIC, PDUR_CONST ) mcTable = PDUR_LOTP_TX_MC_BASE + mcId;
    P2VAR(   PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state = PDUR_LOTP_TX_STATE_BASE + mcId;

    (void)layerId; /* To remove warning */
     /*enter critical area */
    SchM_Enter_PduR_LockMcTpTxConf();

    /* Latch the first transmission error reported by a lower layer */
    if (state->txFailure == E_OK)
    {
        state->txFailure = result;
    }


    /* Wait until all (expected) layers have finished with the buffer */
    /* increment the counter for destination PDUs */
    state->txConf += 1;
    if (state->txConf == mcTable->destLowerLayers)
    {
        /* Notify the upper layer */
        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        PDUR_BASE_RPTBL(upTpTxConfTablePtr)[mcTable->toUp.upTxConfirmationID].PduR_upTpTxConfirmationFunc (mcTable->toUp.upId, state->txFailure);        
        #else
        PduR_upTpTxConfirmationTable[mcTable->toUp.upTxConfirmationID].PduR_upTpTxConfirmationFunc (mcTable->toUp.upId, state->txFailure);        
        #endif

        /* Reset all state for this IPDU */
        PduR_iInit_multicast(state);
    }

    /* exit critical area */
    SchM_Exit_PduR_LockMcTpTxConf();
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif

