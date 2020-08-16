
#include "PduR_Prv.h"

#if defined(PDUR_COM_SUPPORT) && (PDUR_COM_SUPPORT != 0)
#include "PduR_Com.h"
#include "PduR_Com_Up.h"
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_null_ComTxConfirmation_Func
 *        Null functions - to discard any unnecessary notification
 *
 * \param           PduIdType gwayId  :ID of N-PDU that shall be received
 *
 * \retval          None
 *
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_null_ComTxConfirmation_Func( VAR(PduIdType, AUTOMATIC) id )
{

    (void)id;   /* To remove warning */
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* #if defined(PDUR_COM_SUPPORT) && (PDUR_COM_SUPPORT != 0) */


