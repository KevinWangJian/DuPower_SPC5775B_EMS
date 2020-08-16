
/* Support for PduR_Comxxx() can be configured out entirely. */ /**/
#include "PduR_Prv.h"
#if defined(PDUR_COM_SUPPORT) && (PDUR_COM_SUPPORT != 0)
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)

#include "PduR_Com.h"
#include "PduR_Gw.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_Com_Transmit - Support function for combined gateway and reception
 *
 * \param           PduIdType id: ID of AUTOSAR COM I-PDU to be transmitted.
 *                  PduR_TxPduInfoPtr info: A pointer to a structure with I-PDU related data that shall be transmitted
 *                                         data length and pointer to I-SDU buffer
 *
 * \retval          E_OK Transmit request has been accepted
 *
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_Com_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    Com_RxIndication(id, info);
    return E_OK;
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_GATEWAY_SUPPORT */
#endif /* PDUR_COM_SUPPORT */

