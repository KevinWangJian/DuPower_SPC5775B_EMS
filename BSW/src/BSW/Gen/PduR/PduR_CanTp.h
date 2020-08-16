
#ifndef PDUR_CANTP_H
#define PDUR_CANTP_H

#include "PduR.h"

#include "CanTp.h"
#if (!defined(CANTP_AR_RELEASE_MAJOR_VERSION) || (CANTP_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANTP_AR_RELEASE_MINOR_VERSION) || (CANTP_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/* Interface translation layers ------------------------------------- */
#define PduR_RF_CanTp_Transmit_Func             CanTp_Transmit
#define PduR_RF_CanTp_CancelTransmit_Func       CanTp_CancelTransmit


/* PduR_CanTpRxIndication  */
extern FUNC( void, PDUR_CODE ) PduR_CanTpRxIndication( VAR(PduIdType, AUTOMATIC) id,
                                                      VAR(Std_ReturnType, AUTOMATIC) std );

/* PduR_CanTpTxConfirmation  */
extern FUNC( void, PDUR_CODE ) PduR_CanTpTxConfirmation( VAR(PduIdType, AUTOMATIC) id,
                                                        VAR(Std_ReturnType, AUTOMATIC) std );

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpProvideTxBuffer( VAR(PduIdType, AUTOMATIC) id,
                                                                     P2VAR( P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                     VAR(uint16, AUTOMATIC) len );

extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpProvideRxBuffer( VAR(PduIdType, AUTOMATIC) id,
                                                                     VAR(PduLengthType, AUTOMATIC) len,
                                                                     P2VAR( P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), TYPEDEF, PDUR_APPL_DATA ) ptr );

/* PduR_CanTpCopyRxData  */
extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpCopyRxData( VAR(PduIdType, AUTOMATIC) id,
                                                                    P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                    P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);

/* PduR_CanTpStartOfReception */
extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpStartOfReception( VAR(PduIdType, AUTOMATIC) id,
                                                                        P2VAR(PduInfoType,TYPEDEF,PDUR_APPL_DATA) info,
                                                                        VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                        P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);
/* PduR_CanTpCopyTxData  */
extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_CanTpCopyTxData( VAR(PduIdType, AUTOMATIC) id,
                                                                    P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                    P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry,
                                                                      P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr );

#endif /* PDUR_CANTP_H    */


