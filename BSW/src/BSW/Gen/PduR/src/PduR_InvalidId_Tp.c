
/* Functions to be invoked when an invalid ID is encountered.
 */

#include "PduR_Prv.h"
/* Include appropriate header files to declare the
 * prototypes with which we must comply
 */
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_invId_TpCopyRxData
 *            Functions to be invoked when an invalid ID is encountered
 *
 * \param           PduIdType Id:     ID of L-PDU that has been received.
 *                  PduLengthType len:length identifies the overall number of bytes to be received.
 *                  P2VAR( P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), TYPEDEF, PDUR_APPL_DATA ) ptr: Pointer to pointer to PduInfoStructure containing SDU data pointer and
 *                                              SDU length of a receive buffer.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

/* MR12 RULE 8.13 VIOLATION: As per AUTOSAR SWS specification signature is as made as P2VAR. So this warning can be ignored. */
FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyRxData(VAR(PduIdType, AUTOMATIC) id,
                                                                P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{
    /* ptr = ptr;Introduced for MISRA sake. Will be removed by Optimiser anyway */
    /* to remove warning */
    (void)id;
    (void)ptr;
    (void)bufferSizePtr;

    /* nothing - DET not enabled */
    return BUFREQ_E_NOT_OK;
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
 * PduR_invId_TpCopyRxData
 *            Functions to be invoked when an invalid ID is encountered
 *
 * \param           PduIdType Id:     ID of L-PDU that has been received.
 *                  PduLengthType len:length identifies the overall number of bytes to be received.
 *                  P2VAR( P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), TYPEDEF, PDUR_APPL_DATA ) ptr: Pointer to pointer to PduInfoStructure containing SDU data pointer and
 *                                              SDU length of a receive buffer.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

/* MR12 RULE 8.13 VIOLATION: As per AUTOSAR SWS specification signature is as made as P2VAR. So this warning can be ignored. */
FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpStartOfReception(VAR(PduIdType, AUTOMATIC) id,
                                                                    VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                    P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{
    /* ptr = ptr;Introduced for MISRA sake. Will be removed by Optimiser anyway */
    /* to remove warning */
    (void)id;
    (void)TpSduLength;
    (void)bufferSizePtr;

    /* nothing - DET not enabled */
    return BUFREQ_E_NOT_OK;
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
 * PduR_invId_TpRxIndication
 *            Functions to be invoked when an invalid ID is encountered
 *
 * \param           PduIdType Id:     ID of L-PDU that has been received.
 *                  Std_ReturnType  result - Result of the TP reception.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_invId_TpRxIndication(VAR(PduIdType, AUTOMATIC) id,
                                                  VAR(Std_ReturnType, AUTOMATIC) result)
{
    /* nothing - DET not enabled */
    /* to remove MISRA warning */
    (void)id;
    (void)result;

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
 * PduR_invId_TpCopyTxData
 *      Functions to be invoked when an invalid ID is encountered.
 *
 * \param(In)       PduIdType id                      :ID of CAN N-PDU to be transmitted
 *                  P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr            :Pointer to PduInfoStructure containing SDU data pointer and
 *                                                      SDU length of a transmit buffer.
 *                  RetryInfoType retry              :This parameter is used to retransmit data because
 *                                                   problems occurred in transmitting it the last time.
 *                                                   If the I-PDU is transmitted from a local module (e.g. DCM)
 *                                                   the PDU router module will just forward the parameter value
 *                                                   without check. If the I-PDU is gatewayed from another bus
 *                                                   the PDU Router module will make the following interpretation:
 *                                                   If the transmitted TP I-PDU does not support the retry feature
 *                                                   a NULL_PTR can be provided. Alternatively TpDataState can
 *                                                   indicate TP_NORETRY. Both indicate that the copied transmit
 *                                                   data can be removed from the buffer after it has been copied.
 *                                                   If the retry feature is used by the Tx I-PDU, RetryInfoPtr must
 *                                                   point to a valid RetryInfoType element. If TpDataState
 *                                                   indicates TP_CONFPENDING the previously copied data must
 *                                                   remain in the TP buffer to be available for error recovery.
 *                                                   TP_DATACONF indicates that all data, that have been copied
 *                                                   so far, are confirmed and can be removed from the TP buffer.
 *                                                   Data copied by this API call are excluded and will be confirmed
 *                                                   later. TP_DATARETRY indicates that this API call shall copy
 *                                                   already copied data in order to recover from an error. In
 *                                                   this case TxTpDataCnt specifies the offset of the first byte
 *                                                   to be copied by the API call.
 * \param(Out)      PduLengthType availableDataPtr    :Indicates the remaining number of bytes that are available in the
 *                                                      PduR Tx buffer. AvailableTxDataCntPtr can be used by TP
 *                                                      modules that support dynamic payload lengths (e.g. Iso FrTp)
 *                                                      to determine the size of the following CFs.
 *
 * \retval          E_NOT_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* MR12 RULE 8.13 VIOLATION: As per AUTOSAR SWS specification signature is as made as P2VAR. So this warning can be ignored. */
FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyTxData( VAR(PduIdType, AUTOMATIC) id,
                                                                P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr )
{

    ptr = ptr;/* Introduced for MISRA sake. Will be removed by Optimiser anyway */
    /* to remove warning */
    (void)id;
    (void)ptr;
    (void)retry;
    (void)availableDataPtr;

    /* nothing - DET not enabled */
    return BUFREQ_E_NOT_OK;
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
 * PduR_invId_TpTxConfirmation
 *      Functions to be invoked when an invalid ID is encountered.
 *
 * \param           PduIdType id          :ID of I-PDU to be transmitted.
 *                  Std_ReturnType result:Result of the TP reception.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_invId_TpTxConfirmation(VAR(PduIdType, AUTOMATIC) id,
                                                    VAR(Std_ReturnType, AUTOMATIC) result)
{
    /* nothing - DET not enabled */
    /* to remove warning */
    (void)id;
    (void)result;
}


/**
 **************************************************************************************************
 * PduR_invId_UpCancelTransmit
 *      Functions to be invoked when an invalid ID is encountered.
 *
 * \param           PduIdType id: ID of UpTp I-PDU to be cancelled the reception.
 *
 *
 * \retval          E_NOT_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* MR12 RULE 8.13 VIOLATION: As per AUTOSAR SWS specification signature is as made as P2VAR. So this warning can be ignored. */
FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpCancelReceive(VAR(PduIdType, AUTOMATIC) id)
{
    /* to remove warning */
    (void)id;
    /* nothing - DET not enabled */
    return E_NOT_OK;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

