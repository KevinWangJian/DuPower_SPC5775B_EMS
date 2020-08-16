
/* Support for PduR_Ipdumxxx() can be configured out entirely. */ /**/
#include "PduR_Prv.h"
/* Chek for IPDUM and Gateway support during pre-compile time*/
#if defined(PDUR_IPDUM_SUPPORT) && (PDUR_IPDUM_SUPPORT != 0)
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)

#include "PduR_IpduM.h"
#include "PduR_Gw.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_IpdumTransmit - Support function for combined gateway and reception
 *
 * \param           PduIdType id: ID of IPDUM I-PDU to be transmitted.
 *                  P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info: A pointer to a structure with I-PDU related data that shall be transmitted:
 *                                         data length and pointer to I-SDU buffer
 *
 *
 * \retval          E_OK Transmit request has been accepted
 *
 *
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_IpduM_Transmit_Func(VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    IpduM_RxIndication(id, info);
    return E_OK;
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_IFGATEWAY_SUPPORT */
#endif /* PDUR_IPDUM_SUPPORT */

