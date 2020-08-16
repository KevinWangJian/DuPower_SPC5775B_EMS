

#include "PduR_Prv.h"
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_invId_IfRxIndication
 *                Functions to be invoked when an invalid ID is encountered
 *
 * \param           PduIdType Id:     ID of L-PDU that has been received.
 *                  const uint8 *ptr: Pointer to L-SDU (buffer of received payload)
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_invId_IfRxIndication(VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr)
{
    /* nothing - DET not enabled */
    /* to remove warning */
    (void)id;
    (void)ptr;
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
 * PduR_FrIfTriggerTransmit
 *            Functions to be invoked when an invalid ID is encountered
 *
 *
 * \param          PduIdType id:ID of L-PDU that is requested to be transmitted.
 *                 uint8 *  ptr:Pointer to place inside the transmit buffer of the L-PDU where data shall be copied to.
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* MR12 RULE 8.13 VIOLATION: As per AUTOSAR SWS specification signature is as made as P2VAR. So this warning can be ignored.*/
FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_IfTriggerTransmit( VAR(PduIdType, AUTOMATIC) id, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) data )
{
    /* nothing - DET not enabled */
    /* to remove warning */
     /* data = data; Introduced for MISRA sake. Will be removed by Optimiser anyway */
    (void)id;
    (void)data;
    return E_NOT_OK;
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
 * PduR_invId_IfTxConfirmation
 *           Functions to be invoked when an invalid ID is encountered.
 *
 *
 * \param           PduIdType id -  ID of FlexRay L-PDU that has been transmitted.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_invId_IfTxConfirmation( VAR(PduIdType, AUTOMATIC) id)
{
    /* nothing - DET not enabled */
    /* to remove warning */
    (void)id;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

