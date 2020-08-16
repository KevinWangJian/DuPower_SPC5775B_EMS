

#ifndef DCM_CBK_H
#define DCM_CBK_H

/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/
#define DCM_START_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#include "Dcm_Cfg_DslDsd.h"

/*
 ***************************************************************************************************
 *    Function prototypes                                                                          */
/**************************************************************************************************/


/**
 * @ingroup DCM_H
 *
 * Dcm093: The function Dcm_TpRxIndication (refer to chapter 8.4.3) is called by PduR to
 * indicate the completion of the reception.
 *
 * @param[in]  DcmRxPduId  ID of the DCM-IPDU that has been recieved.Identifies the data that has been received.
 *                         Range 0..(maximum number of IPDU ids received by DCM).1
 *
 * @param[in]  Result      E_OK The complete NPDU has been received and is stored in the receive buffer.
                           any other value  The NPDU has not been received;the receive buffer can be unlocked by  the DCM.
 * @return     None.
 */

extern FUNC(void, DCM_CODE) Dcm_TpRxIndication (
                                                VAR(PduIdType, AUTOMATIC) DcmRxPduId,
                                                VAR(Std_ReturnType, AUTOMATIC) Result
                                             );
/**
* @ingroup DCM_H
*  Dcm_TriggerTransmit:The lower layer communication module requests the buffer of the SDU
*                       for transmission from the upper layer module.This function is delivered only to solve
*                       compilation issues, otherwise Dcm does not use this function.
*
*  @param[in]   DcmTxPduId  ID of DCM I-PDU that has been transmitted.
* @param[in]         PduInfoPtr         Pointer to a PduInfoType which indicates the number of bytes to be copied (SduLength) and the location of the source data (SduDataPtr).
*  @retval:    None
*/
extern FUNC(void,DCM_CODE) Dcm_TriggerTransmit(VAR(PduIdType,AUTOMATIC) TxPduId,P2VAR(PduInfoType,AUTOMATIC,DCM_INTERN_DATA) PduInfoPtr );

/**
* @ingroup DCM_H
*  Dcm_TxConfirmation:This function is called by the lower layer (in general the IF layer and in only case of RDPI type2):
*
*  @param[in]   DcmTxPduId  ID of DCM I-PDU that has been transmitted.
*  @retval:    None
*/
extern FUNC(void,DCM_CODE) Dcm_TxConfirmation ( VAR(PduIdType,AUTOMATIC) DcmTxPduId);

/**
* @ingroup DCM_H
*  Dcm_TpTxConfirmation:This function is called by the lower layer (in general the PDU Router):
*  - with Result = E_OK after the complete DCM I-PDU has successfully been transmitted, i.e. at the very
*    end ofthe segmented TP transmit cycle. Within this function, the DCM shall unlock the transmit buffer.
*  - with Result = E_NOT_OK if an error (e.g. timeout) has occurred during the transmission of the DCM
*    I-PDU. This enables unlocking of the transmit buffer and error handling.
*
*  @param[in]   DcmTxPduId  ID of DCM I-PDU that has been transmitted.
*  @param[in]   Result      Result of the N-PDU transmission:
*                           E_OK if the complete N-PDU has been transmitted.
*                           E_NOT_OK Error Occured during transmission
*  @retval:    None
*/

extern FUNC(void, DCM_CODE) Dcm_TpTxConfirmation (
                                                 VAR(PduIdType, AUTOMATIC) DcmTxPduId,
                                                 VAR(Std_ReturnType, AUTOMATIC) Result
                                               );
/**
 * @ingroup DCM_H
 * Dcm_StartOfReception : This call-back function is invoked by medium specific TP (CanTp/FrTp) via PduR to inform the
 * start of reception (i.e. receiving a Single Frame or First Frame indication)
 *
 * @param[in]           DcmRxPduId (in)       Pdu Id corresponding to the received Pdu.Identifies the DCM data to be received.
 *                                            This information is used within the DCM to distinguish two or more receptions at the same time.
 * @param[in]			TpSduLength (in)      Total message length of the request to be received.
 * @param[out]			RxBufferSizePtr (out) Dcm shall need to fill in the buffer capability while providing BUFREQ_OK.
 * @retval              BufReq_ReturnType     BUFREQ_E_NOT_OK - Dcm does not intend to receive this request.
 *					                          BUFREQ_OK - Dcm can process this request, requesting CanTp/FrTp via PduR to trigger Dcm_CopyRxData.
 *					                          BUFREQ_E_OVFL - Available buffer with Dcm is less than requested buffer to receive this request.
 *
 */
extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_StartOfReception
(
	VAR(PduIdType, AUTOMATIC) DcmRxPduId,
	P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) info,
	VAR(PduLengthType, AUTOMATIC) TpSduLength,
	P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
);
/**
 * @ingroup DCM_H
 * Dcm_CopyRxData : This call-back function is invoked by medium specific TP (CanTp/FrTp) via PduR to inform the
 * Dcm once upon reception of each segment. Within this call, the received data is copied from the receive TP buffer
 * to the DCM receive buffer.The function must only be called if the connection has been accepted by an initial call to Dcm_StartOfReception.
 *
 * @param[in]           DcmRxPduId         Identifies the DCM data to be received. This information is used within the DCM to distinguish two or more receptions at the same time.
 * @param[in]		    PduInfoPtr         Pointer to a constant PduInfoType which indicates the number of bytes to be copied (SduLength) and the location of the source data (SduDataPtr).
 *                                         An SduLength of 0 is possible in order to poll the available receive buffer size. In this case no data are to be copied and PduInfoPtr might be invalid.
 * @param[out]		    RxBufferSizePtr    Remaining free place in receive buffer after completion of this call.
 * @retval              BufReq_ReturnType  BUFREQ_OK: Data has been copied to the receive buffer completely as requested.
 *                                         BUFREQ_E_NOT_OK: Data has not been copied. Request failed.
 */
/* Prototype updated as per AR4.2.2*/
extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyRxData
(
	VAR(PduIdType, AUTOMATIC) DcmRxPduId,
	P2CONST(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
	P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) RxBufferSizePtr
);
/**
 * @ingroup DCM_H
 * Dcm_CopyTxData : This call-back function is invoked by medium specific TP (CanTp/FrTp) via PduR to inform the
 * Dcm once upon reception of each segment. Within this call, the received data is copied from the receive TP buffer
 * to the DCM receive buffer.At invocation of Dcm_CopyTxData the DCM module copy the requested transmit data with ID PduId
 * from its internal transmit buffer to the location specified by the PduInfoPtr. The function Dcm_CopyTxData also calculates
 * and sets the TxDataCntPtr to the amount of remaining bytes for the transmission of this data.
 *
 * @param[in]           DcmTxPduId          Identifies the DCM data to be sent. This information is used to derive the PCI information within the transport protocol.
 *                                          The value has to be same as in the according service call PduR_DcmTransmit().
 * @param[in]			PduInfoPtr          Pointer to a PduInfoType, which indicates the number of bytes to be copied (SduLength) and the location where the data have to be copied to (SduDataPtr).
 *                                          An SduLength of 0 is possible in order to poll the available transmit data count. In this case no data are to be copied and SduDataPtr might be invalid.
 * @param[in]			RetryInfoPtr        If the transmitted TP I-PDU does not support the retry feature a NULL_PTR can be provided.
 *                                          Alternatively, TpDataState can indicate TP_NORETRY. Both indicate that the copied trans-mit data can be removed from the buffer after it has been copied.
 * @param[out]			TxDataCntPtr        Remaining Tx data after completion of this call.
 *
 * @retval              BufReq_ReturnType   BUFREQ_OK: Data has been copied to the transmit buffer completely as requested.
 *                                          BUFREQ_E_NOT_OK: Data has not been copied. Request failed, in case the corresponding I-PDU was stopped.
 */

extern FUNC(BufReq_ReturnType,DCM_CODE) Dcm_CopyTxData
(
	VAR(PduIdType, AUTOMATIC) DcmTxPduId,
	P2VAR(PduInfoType, AUTOMATIC, DCM_APPL_DATA) PduInfoPtr,
	P2VAR(RetryInfoType, AUTOMATIC, DCM_APPL_DATA) RetryInfoPtr,
	P2VAR(PduLengthType, AUTOMATIC, DCM_APPL_DATA) TxDataCntPtr
);

/* Called by ComM module */
/**
 * @ingroup DCM_H
 * All kind of transmissions (receive and transmit) shall be stopped . This means that the ResponseOnEvent
 * and PeriodicId and also the transmission of the normal communication (PduR_DcmTransmit) shall be disabled.
 * It will be a dummy function in boot as ComM is not available in boot.
 * @param[in]       NetworkId  Identifies the Channel for which the Communication mode changed.
 * @retval          None
 */
extern FUNC(void, DCM_CODE) Dcm_ComM_NoComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);
/**
 * @ingroup DCM_H
 * Dcm_ComM_SilentComModeEntered: All outgoing transmissions shall be stopped immediately. This means that the
 * ResponseOnEvent and PeriodicId and also the transmission of the normal communication (PduR_DcmTransmit)
 * shall be disabled.
 * It will be a dummy function in boot as ComM is not available in boot.
 * @param[in]       NetworkId  Identifies the Channel for which the Communication mode changed.
 * @retval          None
 */
extern FUNC(void, DCM_CODE) Dcm_ComM_SilentComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);
/**
 * @ingroup DCM_H
 * Dcm_ComM_FullComModeEntered - All kind of transmissions shall be enabled immediately. This means that
 * the ResponseOnEvent and PeriodicId. It will be a dummy function in boot as ComM is not available in boot.
 * @param[in]       NetworkId  Identifies the Channel for which the Communication mode changed.
 * @retval          None
 */
extern FUNC(void, DCM_CODE) Dcm_ComM_FullComModeEntered(VAR(uint8, AUTOMATIC) NetworkId);

#if(DCM_CFG_RTESUPPORT_ENABLED == DCM_CFG_OFF)
/**
 * @ingroup DCM_H
 * Dcm_SetActiveDiagnostic - The call of this function allows to activate and deactivate the call of ComM_DCM_ActiveDiagnostic() function
 *  @param[in]    dataactive_b:  True Dcm will call ComM_DCM_ActiveDiagnostic() \n
 *                           False Dcm shall not call ComM_DCM_ActiveDiagnostic()
 *  @retval    E_OK : this value is always returned.
 */
extern FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveDiagnostic(VAR(boolean, AUTOMATIC) dataactive_b);
#endif

#define DCM_STOP_SEC_CODE
#include "Dcm_Cfg_MemMap.h"
#endif
/* DCM_CBK_H_ */
