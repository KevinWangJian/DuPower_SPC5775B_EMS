
#ifndef PDUR_COM_UP_H
#define PDUR_COM_UP_H

#include "PduR_Prv.h"

/**
 * @ingroup PDUR_COM_H
 *
 * To ensure that the function declarations in this header are located in the code section.
 */
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_CONFIG_SINGLE_IFTX_LO)
/**
 * @ingroup PDUR_COM_H
 *
 * Com Transmit ID
 */
#define PduR_iComTransmitID(id)           (id)                                   /* PDUR_CUBAS 287 */

/**
 * @ingroup PDUR_COM_H
 *
 * Com Transmit function ID
 */
#define PduR_iComTransmitFunc(id)           (PDUR_CONFIG_SINGLE_IFTX_LO(Transmit)) /* PDUR_CUBAS 287 */

#else
/**
 * @ingroup PDUR_COM_H
 *
 * Com Transmit ID
 */
#define PduR_iComTransmitID(id)           (PDUR_COM_TX_BASE[(id)].loId)          /* PDUR_CUBAS 163 */

/**
 * @ingroup PDUR_COM_H
 *
 * Com Transmit function ID
 */
#define PduR_iComTransmitFunc(id)           (PduR_loTransmitTable[(PDUR_COM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)

#endif /* PDUR_CONFIG_SINGLE_IFTX_LO */



#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)   /* PDUR_CUBAS 227 */
/**
 * @ingroup PDUR_COM_H
 *
 * COM Transmit for PduR DEV Error Detect
 */
 #define PduR_rComTransmit(id, ptr)        PduR_dComTransmit((id), (ptr))
#else
 /* PDUR_CUBAS 142 */ /* PDUR_CUBAS 143 */ /* PDUR_CUBAS 169 */
/**
 * @ingroup PDUR_COM_H
 *
 * COM Transmit for PduR DEV Error Detect
 */
 #define PduR_rComTransmit(id, ptr)        PduR_iComTransmitFunc(id)(PduR_iComTransmitID(id), (ptr))
#endif /* PDUR_DEV_ERROR_DETECT */


/*------------------------------------------------------------------------------- Multicast mapping ------------------------------------------------ */

/**
 * @ingroup PDUR_COM_H
 *
 *  This function is called by AUTOSAR COM to request a transmission for multicast mapping. \n
 *
 *  @param  In:      id - multicast ID to be transmitted. \n
 *  @param  In:      info - Pointer to a structure with PDU related data that shall be transmitted
 *                           data length and pointer to buffer \n
 *
 *  @return          E_OK: if the request is accepted \n
 *                   E_NOT_OK: if the request is not accepted  just for testing \n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_Com_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

/*-------------------------------------------------------------------------------End of Multicast mapping func------------------------------------------------ */





/*------------------------------------------------------------------------------------------- Null functions --------------------------------------------------- */
/**
 * @ingroup PDUR_COM_H
 *
 *  Null functions to discard any unnecessary notification \n
 *
 *  @param  In:      id - multicast ID to be transmitted. \n
 *  @param  In:      info - Pointer to a structure with PDU related data that shall be transmitted
 *                           data length and pointer to buffer \n
 *
 *  @return None \n
 */
extern FUNC( void, PDUR_CODE ) PduR_null_ComTxConfirmation_Func( VAR(PduIdType, AUTOMATIC) id);
/*--------------------------------------------------------------------------------------END of Null functions --------------------------------------------------- */

/*-------------------------------------------------------------------------------------- Invalid PDU id handlers ------------------------------------------ */
#define PDUR_IH_Com_Transmit_Func    PDUR_DET_API(PduR_invId_UpTransmit)

/**
 * @ingroup PDUR_COM_H
 *
 * Anything after this point will not be placed in the code section.
 */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_COM_UP_H */

