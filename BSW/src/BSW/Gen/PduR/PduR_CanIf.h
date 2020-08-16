
#ifndef PDUR_CANIF_H
#define PDUR_CANIF_H

#include "PduR.h"

#include "CanIf.h"
#if (!defined(CANIF_AR_RELEASE_MAJOR_VERSION) || (CANIF_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANIF_AR_RELEASE_MINOR_VERSION) || (CANIF_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif


/* Interface translation layers ------------------------------------- */
#define PduR_RF_CanIf_Transmit_Func   CanIf_Transmit

/* PduR_CanIfRxIndication  */
extern FUNC( void, PDUR_CODE ) PduR_CanIfRxIndication( VAR(PduIdType, AUTOMATIC) id,
                                                      P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );
/* PduR_CanIfTxConfirmation  */
extern FUNC( void, PDUR_CODE ) PduR_CanIfTxConfirmation(VAR(PduIdType, AUTOMATIC) id);


#endif /* PDUR_CANIF_H    */
