
#ifndef PDUR_DCM_H
#define PDUR_DCM_H

#include "PduR.h"

#include "Dcm.h"
#if (!defined(DCM_AR_RELEASE_MAJOR_VERSION) || (DCM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DCM_AR_RELEASE_MINOR_VERSION) || (DCM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "Dcm_Cbk.h"


/* Interface translation layers ------------------------------------- */
/**
 * @ingroup PDUR_DCM_H
 *
 *This Macro gets generated through code generation which will be mapped to actual API
 */
#define PduR_RF_Dcm_StartOfReception_Func        Dcm_StartOfReception
#define PduR_RF_Dcm_CopyRxData_Func              Dcm_CopyRxData
#define PduR_RF_Dcm_CopyTxData_Func              Dcm_CopyTxData
#define PduR_RF_Dcm_TpRxIndication_Func          Dcm_TpRxIndication
#define PduR_RF_Dcm_TpTxConfirmation_Func        Dcm_TpTxConfirmation

/**
 * @ingroup PDUR_DCM_H
 *
 *  This function is called by the DCM to request a transmission.
 *\n
 * @param in          id -  ID of DCM I-PDU to be transmitted.\n
 * @param out         P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr -   Pointer to a structure with I-PDU related data that shall be transmitted:
 *                                         data length and pointer to I-SDU buffer\n
 *\n
 * @return            E_OK: Transmit request has been accepted.\n
 *                    E_NOT_OK: Transmit request has not been accepted.\n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmTransmit( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );


/* ------------------------------------------------------------------- */
/**
 * @ingroup PDUR_DCM_H
 *      This function is called by the DCM to request a transmission cancellation.\n
 *\n
 * @param in        id: ID of DCM I-PDU to be cancelled the transmission.\n
 *\n
 * @return          E_OK: Cancellation request has been accepted.\n
 *                  E_NOT_OK: Cancellation request has not been accepted.\n
 *
 **************************************************************************************************
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmCancelTransmit( VAR(PduIdType,AUTOMATIC) id);



 /**
 * @ingroup PDUR_DCM_H
 *
 * This service primitive is used to request the change of the value of the PDUR_STMIN parameter.\n
 *\n
 * @param in         parameter - Specify the parameter to which the value has to be changed (BS or STmin). \n
 * @param in         Id - Gives the ID of the connection (message) for whose channel the change shall be done.\n
 * @param in         value - The new value of the parameter. \n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmChangeParameter(VAR(PduIdType, AUTOMATIC) id,
                                                           VAR(TPParameterType, AUTOMATIC) parameter,
                                                           VAR(uint16, AUTOMATIC) value);

/**
 * @ingroup PDUR_DCM_H
 *      This service primitive is used to request the change of the value of the PDUR_STMIN parameter.\n
 *\n
 * @param in          parameter - Specify the parameter to which the value has to be read (BS or STmin).\n
 * @param in          id        - Gives the ID of the connection (message).\n
 * @param in          value     - Pointer where the parameter value is stored\n
 *\n
 * @return            E_OK: The STmin value is updated in the buffer provided.\n
 *                    E_NOT_OK: Invalid request / NULL_PTR passed etc.\n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_DcmReadParameter(VAR(PduIdType, AUTOMATIC) id,
                                                          VAR(TPParameterType, AUTOMATIC) parameter,
                                                          P2VAR(uint16, AUTOMATIC, PDUR_APPL_DATA) value);
#endif /* PDUR_DCM_H    */
