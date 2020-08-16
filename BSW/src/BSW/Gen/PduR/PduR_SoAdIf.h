/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/


#ifndef PDUR_SOADIF_H
#define PDUR_SOADIF_H

#include "PduR.h"

#include "SoAd.h"
#if (!defined(SOAD_AR_RELEASE_MAJOR_VERSION) || (SOAD_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(SOAD_AR_RELEASE_MINOR_VERSION) || (SOAD_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif


/* Interface translation layers ------------------------------------- */

#define PduR_RF_SoAdIf_Transmit_Func   SoAd_IfTransmit
/* PduR_SoAdIfRxIndication  */
extern FUNC( void, PDUR_CODE ) PduR_SoAdIfRxIndication( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );
//
///* PduR_SoAdIfTxConfirmation  */
extern FUNC( void, PDUR_CODE ) PduR_SoAdIfTxConfirmation( VAR(PduIdType, AUTOMATIC) pduId_u8 );
//
///* PduR_SoAdIfTriggerTransmit  */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_SoAdIfTriggerTransmit( VAR(PduIdType, AUTOMATIC) id, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );

#endif /* PDUR_SOADIF_H    */
