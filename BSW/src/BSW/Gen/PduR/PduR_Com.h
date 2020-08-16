
#ifndef PDUR_COM_H
#define PDUR_COM_H

#include "PduR.h"

#include "Com.h"
#if (!defined(COM_AR_RELEASE_MAJOR_VERSION) || (COM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COM_AR_RELEASE_MINOR_VERSION) || (COM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif


/* Interface translation layers ------------------------------------- */
/**
 * @ingroup PDUR_COM_H
 *
 *This Macro gets generated through code generation which will be mapped to actual API
 */

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COMTp Tx Confirmation
 */
#define PduR_RF_Com_TpTxConfirmation_Func        Com_TpTxConfirmation

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COM Start Of Reception
 */
#define PduR_RF_Com_StartOfReception_Func        Com_StartOfReception

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COMTp Rx Indication
 */
#define PduR_RF_Com_TpRxIndication_Func          Com_TpRxIndication

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COM Copy Rx Data
 */
#define PduR_RF_Com_CopyRxData_Func              Com_CopyRxData

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COM Copy Tx Data
 */
#define PduR_RF_Com_CopyTxData_Func              Com_CopyTxData

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COM Trigger Transmit
 */
#define PduR_RF_Com_TriggerTransmit_Func       Com_TriggerTransmit

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COM Rx Indication
 */
#define PduR_RF_Com_RxIndication_Func          Com_RxIndication

/**
 * @ingroup PDUR_COM_H
 *
 * Interface translation layers for COM Tx Confirmation
 */
#define PduR_RF_Com_TxConfirmation_Func        Com_TxConfirmation

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"
/**
 * @ingroup PDUR_COM_H
 *
 *  This function is called by the COM to request a transmission.
 *\n
 * @param in          id -  ID of COM I-PDU to be transmitted.\n
 * @param out         P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr -   Pointer to a structure with I-PDU related data that shall be transmitted:
 *                                         data length and pointer to I-SDU buffer\n
 *\n
 * @return            E_OK: Transmit request has been accepted.\n
 *                    E_NOT_OK: Transmit request has not been accepted.\n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_ComTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );






/**
 * @ingroup PDUR_COM_H
 *
 * Anything after this point will not be placed in the code section.
 */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_COM_H    */
