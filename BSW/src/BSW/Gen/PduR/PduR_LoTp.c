


 
/*<VersionHead>
 * This Configuration File is generated using versions (automatically filled in) as listed below.
 *
 * $Generator__: PduR  / AR42.4.0.1                Module Package Version
 * $Editor_____: 9.0                Tool Version
 * $Model______: 2.3.0.4                ECU Parameter Definition Version
 *
 
 </VersionHead>*/



#include "PduR_Prv.h"

#include "PduR_Cfg.h"
/* Appropriate header files are included to declare the prototypes
 */
#include "PduR_LoTp.h"



/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_CanTpRxIndication - PDU Router CanTpRxIndication.
 *
 * This function is called by the CanTp TP.
 * with Result = E_OK after the complete CanTp TP data have successfully been
 * received, i.e. at the very end of the segmented TP receive cycle or after
 * receiving an unsegemented N-PDU.
 *
 * with Result != E_OK if an error (e.g. timeout) has occurred during the TP reception.
 * This enables unlocking of the receive buffer. It is undefined which part of the buffer
 * contains valid data in this case.
 *
 *
 * \param           PduIdType id -  ID of CanTp N-PDU that has been received.
 *                                  Range: 0..(maximum number of N-PDU IDs which may be received by CanTp TP) - 1
 *                  Std_ReturnType  std - Result of the TP reception.
 *
 * \retval          None
 * \seealso         PDUR184
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_CanTpRxIndication( VAR(PduIdType, AUTOMATIC) id, VAR(Std_ReturnType, AUTOMATIC) std)
{
    PduR_rCanTpRxIndication((id), (std));
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
 * PduR_CanTpTxConfirmation
 *                  This function is called by the CanTp Transport Protocol:
 *
 *   with Result  =  E_OK after the complete CanTp TP data have successfully been transmitted,
 *                  i.e. at the very end of the segmented TP transmission cycle.
 *   with Result != E_OK if an error (e.g. timeout) has occurred during the TP transmission.
 *                  This enables unlocking of the transmit buffer.
 *
 *
 * \param           PduIdType id       :ID of CanTp N-PDU that has been transmitted.
 *                  Std_ReturnType std:Result of the TP reception.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( void, PDUR_CODE ) PduR_CanTpTxConfirmation( VAR(PduIdType, AUTOMATIC) id,
                                                  VAR(Std_ReturnType, AUTOMATIC) std)
{
    PduR_rCanTpTxConfirmation( (id), (std));
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
 * PduR_CanTpCopyRxData - This service is called by the CanTp for requesting a new buffer (pointer to a
 *                             PduInfoStructure containing a pointer to a SDU buffer and the buffer length) for the CanTp
 *                             TP to fill in the received data..
 *
 *
 * \param(In)       PduIdType id                      :Identification of the received I-PDU.
 *                  P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr            :Pointer to the buffer (SduDataPtr) and its length
 *                                                  (SduLength) containing the data to be copied by PDU Router
 *                                                  module in case of gateway or upper layer module in case of reception
 *
 * \param(Out)      PduLengthType bufferSizePtr     :Available receive buffer after data has been copied
 *
 * \retval          BUFREQ_OK       - Buffer request accomplished successful
 *                  BUFREQ_E_NOT_OK - Buffer request not successful, no buffer provided.
 *
 * \seealso         PDUR181
 * \usedresources
 **************************************************************************************************
 */

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpCopyRxData( VAR(PduIdType, AUTOMATIC) id,
                                                                P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{
    return (PduR_rCanTpCopyRxData( (id), (ptr), (bufferSizePtr)));
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
 * PduR_CanTpStartOfReception - This service is called by the CanTp for requesting a new buffer (pointer to a
 *                             PduInfoStructure containing a pointer to a SDU buffer and the buffer length) for the CanTp
 *                             TP to fill in the received data..
 *
 *
 * \param(In)       PduIdType id                    :Identification of the received I-PDU.
                    PduInfoType* info               :Pointer to a structure containing content and length of the first frame or
                                                     single frame including MetaData.
 *                  P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr            :Pointer to the buffer (SduDataPtr) and its length
 *                                                  (SduLength) containing the data to be copied by PDU Router
 *                                                  module in case of gateway or upper layer module in case of reception
 *
 * \param(Out)      PduLengthType bufferSizePtr     :Available receive buffer after data has been copied
 *
 * \retval          BUFREQ_OK       - Buffer request accomplished successful
 *                  BUFREQ_E_NOT_OK - Buffer request not successful, no buffer provided.
 *
 * \seealso         PDUR181
 * \usedresources
 **************************************************************************************************
 */

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpStartOfReception( VAR(PduIdType, AUTOMATIC) id,
                                                                P2VAR(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
                                                                VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr)
{
    return (PduR_rCanTpStartOfReception( (id), (info),(TpSduLength), (bufferSizePtr)));
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
 * PduR_CanTpCopyTxData - This function is called by the CanTp TP for requesting a transmit buffer.
 *
 *
 * \param(In)       PduIdType id                      :ID of CanTp N-PDU to be transmitted
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
 * \retval          BUFREQ_OK       - Buffer request accomplished successful
 *                  BUFREQ_E_BUSY   - Currently no buffer of the requested size is available
 *                  BUFREQ_E_NOT_OK - Buffer request not successful, no buffer provided.
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpCopyTxData( VAR(PduIdType, AUTOMATIC) id,
                                                                    P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                    P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                    P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr )
{
    return (PduR_rCanTpCopyTxData( (id), (ptr), (retry), (availableDataPtr)));

}


/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"


