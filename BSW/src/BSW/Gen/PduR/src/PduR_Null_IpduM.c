

#include "PduR_Prv.h"
#if defined(PDUR_IPDUM_SUPPORT) && (PDUR_IPDUM_SUPPORT != 0)
#include "PduR_IpduM.h"
#include "PduR_IpduM_Up.h"
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_null_IpdumTxConfirmation_Func
 *        Null functions - to discard any unnecessary notification
 *
 * \param           PduIdType gwayId  :ID of multiplexed I-PDU that has been transmitted.
 *
 * \retval          None
 *
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_null_IpduMTxConfirmation_Func( VAR(PduIdType, AUTOMATIC) id )
{
    /* Nothing */
    (void)id;  /* To temove warning */
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_IPDUM_SUPPORT */


