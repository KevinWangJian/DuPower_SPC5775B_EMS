
/** Handle ProvideTxBuffer invocation for Tp layer gatewaying,
  * for the situation when using a FIFO
  */

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
 * PduR_GF_Tp_CopyTxData_Func - This function is called by the transport protocol module to query
 *                                the transmit data of an I-PDU segment. Each call to this function copies
 *                                the next part of the transmit data until TpDataState indicates TP_DATARETRY.
 *                                In this case the API restarts to copy the data beginning at the
 *                                location indicated by TpTxDataCnt.
 *
 * \param(in)       PduIdType    gwId             - Identification of the transmitted I-PDU.
 *                  pduInfoPtr   Info             - Provides destination buffer and the number of bytes to copy.
 *                                                    In case of gateway the PDU Router module will copy otherwise the source upper
 *                                                    layer module will copy the data. If no enough transmit data is available,
 *                                                    no data is copied. The transport protocol module will retry.
 *                                                    A size of copy size of 0 can be used to indicate state changes in the retry parameter.
 *                    RetryInfoType* retry          - This parameter is used to retransmit data because problems occurred in transmitting it the last time.
 *                                                    If the I-PDU is transmitted from a local module (e.g. DCM) the PDU router module will
 *                                                    just forward the parameter value without check. If the I-PDU is gatewayed from another bus the PDU Router
 *                                                    module will make the following interpretation: If the transmitted TP I-PDU does not support
 *                                                    the retry feature a NULL_PTR can be provided.
 *                                                    It indicates that the copied transmit data can be removed from the buffer after it has been copied.
 *                                                    If the retry feature is used by the Tx I-PDU, RetryInfoPtr must point to a valid RetryInfoType element.
 *                                                    If TpDataState indicates TP_CONFPENDING the previously copied data must remain in the TP buffer
 *                                                    to be available for error recovery. TP_DATACONF indicates that all data, that have been copied so far,
 *                                                    are confirmed and can be removed from the TP buffer. Data copied by this API call are excluded and will
 *                                                    be confirmed later. TP_DATARETRY indicates that this API call shall copy already copied data in order
 *                                                    to recover from an error. In this case TxTpDataCnt specifies the offset of the first byte to be copied by the API call.
 *
 * \param(out)      PduLengthType* availableDataPtr  - Indicates the remaining number of bytes that are available in the PduR Tx buffer.
 *                                                    AvailableTxDataCntPtr can be used by TP modules that support dynamic payload lengths
 *                                                    (e.g. Iso FrTp) to determine the size of the following CFs.
 *
 * \retval            BUFREQ_OK        : Data has been copied to the transmit buffer completely as requested.
 *                    BUFREQ_E_BUSY    : Request could not be fulfilled as the required amount of Tx data is not available.
 *                                      TP layer might retry later on. No data has been copied.
 *                    BUFREQ_E_NOT_OK    : Data has not been copied. Request failed.
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

/* MR12 RULE 8.13 VIOLATION: A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object.
   But AUTOSAR SWS specification signature is as below, Hence suppressed */
FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_GF_Tp_CopyTxData_Func( VAR(PduIdType, AUTOMATIC) gwId,
                                                               P2VAR(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
                                                               P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                               P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr)
{
    /* Start: Variable declaration */
    PduR_GT_TpPtr      gt;
    /* Fetch the fixed Buffer details */
    P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) fifo;
    /* Fetch the RAM structure details  */
    PduR_TpConnDynPtr ConnectionPtr;
    PduR_TpSessDynPtr  SessionPtr;
    VAR(BufReq_ReturnType, AUTOMATIC) rtn;
/* End: Variable declaration */

    /* Start: Variable Initialization */
    gt = PDUR_GW_TP_BASE+gwId;
    fifo = (gt->buffer);
    ConnectionPtr = fifo->connectionTable;
    /* Tx is always on primary session */
    SessionPtr = ConnectionPtr->primarySession;
    rtn = BUFREQ_OK;
    /* End: Variable Initialization */


    /*Check for RX and TX status of Session Ptr as both are expected to be in IN_PROGRESS state */
    if ((SessionPtr->Rx_Status == PDUR_SESSION_IDLE) || (SessionPtr->Tx_Status == PDUR_TX_IDLE))
    {
        /*RxIndication was received with negative result*/
        return  BUFREQ_E_NOT_OK;
    }

    if(info->SduLength == 0u)
    {
        /* Dest LoTp has requested with sdulength = 0, update the out parameter,availableDataPtr,
         * with available data in PduRTpbuffer i.e Received data - Transmitted data.
         * If availableDataPtr is 0 then return BUFREQ_E_BUSY.
         */
        *(availableDataPtr) = (SessionPtr->numRxLength - SessionPtr->numTxLength);
        if(*(availableDataPtr) != 0u)
        {
            return BUFREQ_OK;
        }
        else
        {
            return BUFREQ_E_BUSY;
        }

    }


    /*Check if requested length is greater than complete message length requested in PduR_<LoTp>StartOfReception call */
    if (info->SduLength > (SessionPtr->SduLength - SessionPtr->numTxLength))
    {
        return  BUFREQ_E_NOT_OK;
    }

    /* In case of Multicast gateway */
    if(gt->numOfLowerLayers > 1u)
    {
        /* check if the received data is more than requested data */
        /* And status flag is in PDUR_TX_INPROGRESS */
        if(info->SduLength == SessionPtr->SduLength)
        {
            if((retry == NULL_PTR) || (retry->TpDataState == TP_DATACONF))
            {

                /* Copy the data into the transmit buffer and update the read pointer */
                rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);


                /* Indicates the remaining number of bytes that are available in the PduR Tp buffer*/
                *(availableDataPtr) = 0;

            }   /* end of - if((retry == NULL_PTR) || (retry->TpDataState == TP_DATACONF)) */
            else
            {
                /* Because Dest LoTp has requested retransmission with state other than TP_DATACONF */
                /* PDU Router shall immediately stop further processing of this I-PDU */

                rtn = BUFREQ_E_NOT_OK;

            }
        }   /* end of - if(info->SduLength == SessionPtr->SduLength) */
        else
        {
            /* Because requested sdulength is more than the message length */
            rtn = BUFREQ_E_NOT_OK;

        }
        return rtn;

    }

    /* unicast gateway case */
    /* check if the received data is more than requested data */
    /* And status flag is in PDUR_TX_INPROGRESS */
    if(SessionPtr->numRxLength >= (info->SduLength + SessionPtr->numTxLength))
    {
        if((retry == NULL_PTR) || (retry->TpDataState == TP_DATACONF))
        {

            /* Copy the data into the transmit buffer and update the read pointer */
            rba_BswSrv_MemCopy8(info->SduDataPtr,SessionPtr->readPtr,info->SduLength);


            SessionPtr->readPtr += info->SduLength;
            /* Length of data received */
            SessionPtr->numTxLength = SessionPtr->numTxLength + info->SduLength;

            /* Indicates the remaining number of bytes that are available in the PduR Tp buffer */
            *(availableDataPtr) = SessionPtr->numRxLength - SessionPtr->numTxLength;

        }   /* end of - if((retry == NULL_PTR) || (retry->TpDataState == TP_DATACONF)) */
        else
        {
            /* Because Dest LoTp has requested retransmission with state other than TP_DATACONF */
            /* PDU Router shall immediately stop further processing of this I-PDU */

            rtn = BUFREQ_E_NOT_OK;
        }
    }   /* end of - if(SessionPtr->numRxLength >= (info->SduLength + SessionPtr->numTxLength)) */
    else
    {
        /* Reception in progress */
        rtn = BUFREQ_E_BUSY;

    }
    return rtn;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_TPGATEWAY_SUPPORT */

