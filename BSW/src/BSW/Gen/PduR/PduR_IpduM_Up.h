
#ifndef PDUR_IPDUM_UP_H
#define PDUR_IPDUM_UP_H

#include "PduR_Prv.h"

/**
 * @ingroup PDUR_IPDUM_H
 *
 * To ensure that the function declarations in this header are located in the code section.
 */
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_CONFIG_SINGLE_IFTX_LO)
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM Transmit ID
 */
#define PduR_iIpduMTransmitID(id)           (id)                                   /* PDUR_CUBAS 287 */

/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM Transmit function ID
 */
#define PduR_iIpduMTransmitFunc(id)           (PDUR_CONFIG_SINGLE_IFTX_LO(Transmit)) /* PDUR_CUBAS 287 */

#else
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM Transmit ID
 */
#define PduR_iIpduMTransmitID(id)           (PDUR_IPDUM_TX_BASE[(id)].loId)          /* PDUR_CUBAS 163 */

/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM Transmit function ID
 */
#define PduR_iIpduMTransmitFunc(id)           (PduR_loTransmitTable[(PDUR_IPDUM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)

#endif /* PDUR_CONFIG_SINGLE_IFTX_LO */



#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)   /* PDUR_CUBAS 227 */
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IPDUM Transmit for PduR DEV Error Detect
 */
 #define PduR_rIpduMTransmit(id, ptr)        PduR_dIpduMTransmit((id), (ptr))
#else
 /* PDUR_CUBAS 142 */ /* PDUR_CUBAS 143 */ /* PDUR_CUBAS 169 */
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IPDUM Transmit for PduR DEV Error Detect
 */
 #define PduR_rIpduMTransmit(id, ptr)        PduR_iIpduMTransmitFunc(id)(PduR_iIpduMTransmitID(id), (ptr))
#endif /* PDUR_DEV_ERROR_DETECT */


/*------------------------------------------------------------------------------- Multicast mapping ------------------------------------------------ */

/**
 * @ingroup PDUR_IPDUM_H
 *
 *  This function is called by AUTOSAR IPDUM to request a transmission for multicast mapping. \n
 *
 *  @param  In:      id - multicast ID to be transmitted. \n
 *  @param  In:      info - Pointer to a structure with PDU related data that shall be transmitted
 *                           data length and pointer to buffer \n
 *
 *  @return          E_OK: if the request is accepted \n
 *                   E_NOT_OK: if the request is not accepted  just for testing \n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_IpduM_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

/*-------------------------------------------------------------------------------End of Multicast mapping func------------------------------------------------ */





/*------------------------------------------------------------------------------------------- Null functions --------------------------------------------------- */
/**
 * @ingroup PDUR_IPDUM_H
 *
 *  Null functions to discard any unnecessary notification \n
 *
 *  @param  In:      id - multicast ID to be transmitted. \n
 *  @param  In:      info - Pointer to a structure with PDU related data that shall be transmitted
 *                           data length and pointer to buffer \n
 *
 *  @return None \n
 */
extern FUNC( void, PDUR_CODE ) PduR_null_IpduMTxConfirmation_Func( VAR(PduIdType, AUTOMATIC) id);
/*--------------------------------------------------------------------------------------END of Null functions --------------------------------------------------- */

/*-------------------------------------------------------------------------------------- Invalid PDU id handlers ------------------------------------------ */
#define PDUR_IH_IpduM_Transmit_Func    PDUR_DET_API(PduR_invId_UpTransmit)
/**
 * @ingroup PDUR_IPDUM_H
 *
 * Invalid PDU ID handlers for IPDUM Rx Indication
 */
#define PDUR_IH_IpduMRx_RxIndication_Func   PDUR_DET_API(PduR_invId_IfRxIndication)

/**
 * @ingroup PDUR_IPDUM_H
 *
 * Invalid PDU ID handlers for IPDUM Tx Confirmation
 */
#define PDUR_IH_IpduMTx_TxConfirmation_Func PDUR_DET_API(PduR_invId_IfTxConfirmation)

/**
 * @ingroup PDUR_IPDUM_H
 *
 * Invalid PDU ID handlers for IPDUM Tx Confirmation
 */
#define PDUR_IH_IpduMTx_TriggerTransmit_Func  PDUR_DET_API(PduR_invId_IfTriggerTransmit)



/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM RxIndication Id
 */
#define PduR_iIpduMRxIndicationID(id)        (PDUR_IPDUM_RXIND_BASE[(id)].upId)              /* PDUR_CUBAS 163 */

/**
 * @ingroup PDUR_IPDUM_H
 *
 * IPDUM RxIndication function Id
 */
#define PduR_iIpduMRxIndicationFunc(id)      (PduR_upIfRxIndicationTable[(PDUR_IPDUM_RXIND_BASE[(id)].upRxIndicationID)].PduR_upIfRxIndicationFunc)


#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)   /* PDUR_CUBAS 227 */
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IPDUM RxConfirmation Indication
 */
 #define PduR_rIpduMRxIndication(id, ptr)     PduR_dIpduMRxIndication((id), (ptr))
#else
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM RxConfirmation Indication
 */
 #define PduR_rIpduMRxIndication(id, ptr)     PduR_iIpduMRxIndicationFunc(id)(PduR_iIpduMRxIndicationID(id), (ptr))
#endif /* PDUR_DEV_ERROR_DETECT */


/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM TxConfirmation Id
 */
#define PduR_iIpduMTxConfirmationID(id)      (PDUR_IPDUM_TXCONF_BASE[(id)].upId)                /* PDUR_CUBAS 163 */
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM TxConfirmation Function Id
 */
#define PduR_iIpduMTxConfirmationFunc(id)    (PduR_upIfTxConfirmationTable[(PDUR_IPDUM_TXCONF_BASE[(id)].upTxConfirmationID)].PduR_upIfTxConfirmationFunc)


#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)   /* PDUR_CUBAS 227 */
/**
 * @ingroup PDUR_IPDUM_H
 *
 *  IpduM TxConfirmation Id
 */
 #define PduR_rIpduMTxConfirmation(id)        PduR_dIpduMTxConfirmation(id)
#else
/**
 * @ingroup PDUR_IPDUM_H
 *
 * IpduM TxConfirmation Function Id
 */
 #define PduR_rIpduMTxConfirmation(id)        PduR_iIpduMTxConfirmationFunc(id)(PduR_iIpduMTxConfirmationID(id))
#endif /* PDUR_DEV_ERROR_DETECT */




#if defined(PDUR_CONFIG_SINGLE_IFTX_UP)
#define PduR_iIpduMTriggerTransmitID(id)     (id)
#define PduR_iIpduMTriggerTransmitFunc(id)     (PDUR_CONFIG_SINGLE_IFTX_UP(TriggerTransmit))
#else
#define PduR_iIpduMTriggerTransmitID(id)     (PDUR_IPDUM_TXCONF_BASE[(id)].upId)
#define PduR_iIpduMTriggerTransmitFunc(id)   (PduR_upIfTriggerTxTable[(PDUR_IPDUM_TXCONF_BASE[(id)].upTriggerTxID)].PduR_upIfTriggerTxFunc)

#endif /* PDUR_CONFIG_SINGLE_IFTX_UP */



#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aIpduMTriggerTransmit(id, ptr)  PduR_dIpduMTriggerTransmit((id), (ptr))
#else
#define PduR_aIpduMTriggerTransmit(id, ptr)  PduR_iIpduMTriggerTransmitFunc(id)(PduR_iIpduMTriggerTransmitID(id), (ptr))
#endif /* PDUR_DEV_ERROR_DETECT */

#define PduR_rIpduMTriggerTransmit(id, ptr)   PduR_aIpduMTriggerTransmit((id), (ptr))




/**
 * @ingroup PDUR_IPDUM_H
 *
 * Anything after this point will not be placed in the code section.
 */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IPDUM_UP_H */

