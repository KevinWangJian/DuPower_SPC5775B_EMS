
#ifndef PDUR_IPDUM_H
#define PDUR_IPDUM_H

#include "PduR.h"

#include "IpduM.h"
#if (!defined(IPDUM_AR_RELEASE_MAJOR_VERSION) || (IPDUM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(IPDUM_AR_RELEASE_MINOR_VERSION) || (IPDUM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif


/* Interface translation layers ------------------------------------- */
/**
 * @ingroup PDUR_IPDUM_H
 *
 *This Macro gets generated through code generation which will be mapped to actual API
 */


/**
 * @ingroup PDUR_IPDUM_H
 *
 * Interface translation layers for IPDUM Trigger Transmit
 */
#define PduR_RF_IpduM_TriggerTransmit_Func       IpduM_TriggerTransmit

/**
 * @ingroup PDUR_IPDUM_H
 *
 * Interface translation layers for IPDUM Rx Indication
 */
#define PduR_RF_IpduM_RxIndication_Func          IpduM_RxIndication

/**
 * @ingroup PDUR_IPDUM_H
 *
 * Interface translation layers for IPDUM Tx Confirmation
 */
#define PduR_RF_IpduM_TxConfirmation_Func        IpduM_TxConfirmation

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
/**
 * @ingroup PDUR_IPDUM_H
 *
 *  This function is called by the IPDUM to request a transmission.
 *\n
 * @param in          id -  ID of IPDUM I-PDU to be transmitted.\n
 * @param out         P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr -   Pointer to a structure with I-PDU related data that shall be transmitted:
 *                                         data length and pointer to I-SDU buffer\n
 *\n
 * @return            E_OK: Transmit request has been accepted.\n
 *                    E_NOT_OK: Transmit request has not been accepted.\n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_IpduMTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );






/**
 * @ingroup PDUR_IPDUM_H
 *
 * Interface translation layers for IpduM RF transmit
 */
#define PduR_RF_IpduM_Transmit_Func          IpduM_Transmit

/**
 * @ingroup PDUR_IPDUM_H
 *
 *  This function is called by the IpduM after the PDU has been received. \n
 *
 *  @param  In:      id - ID of IpduM I-PDU that has been received. \n
 *  @param  Out:     ptr - Pointer to IPDUM SDU (buffer of received payload) \n
 *
 *  @return None \n
 */
/* PduR_IpduMRxIndication PDUR_CUBAS 166 */

extern FUNC( void, PDUR_CODE ) PduR_IpduMRxIndication( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr);

/* ------------------------------------------------------------------- */
/* PduR_IpduMTxConfirmation PDUR_CUBAS 194 */
/**
 * @ingroup PDUR_IPDUM_H
 *
 *  This function is called by the FlexRay Interface after the PDU has been transmitted on the FlexRay network. \n
 *
 *  @param  In:      id - ID of IPDUM I-PDU to be transmitted. \n
 *
 *  @return None \n
 */
extern FUNC( void, PDUR_CODE ) PduR_IpduMTxConfirmation( VAR(PduIdType, AUTOMATIC) id);


/**
 * @ingroup IPDUM_H
 *
 *  This function is used for PDUR_IPDUM buffer initialization to get IpduM Init Values\n
 *
 *  @param  In:      PdumTxPduId - Pdu ID type \n
 *  @param  In:      Ptr -  Pdu Info type for Buffer Init values\n
 *
 *  @return          E_OK: if the request is accepted \n
 *                   E_NOT_OK: if the request is not accepted \n
 */
 /* PduR_IpduMTriggerTransmit  */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_IpduMTriggerTransmit( VAR(PduIdType, AUTOMATIC) id, P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA)   ptr );

/**
 * @ingroup PDUR_IPDUM_H
 *
 * Anything after this point will not be placed in the code section.
 */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IPDUM_H    */
