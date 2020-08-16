/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/


#ifndef PDUR_SOADIF_LO_H
#define PDUR_SOADIF_LO_H

#include "PduR_Prv.h"

/* Ensure that the function declarations in this header are located in the code section. */
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/* ------------------------------------------------------------------- */
#if defined(PDUR_CONFIG_SINGLE_IFRX)
#define PduR_iSoAdIfRxIndicationID(id)        (id)
#define PduR_iSoAdIfRxIndicationFunc(id)        (PDUR_CONFIG_SINGLE_IFRX(RxIndication))
#else
#define PduR_iSoAdIfRxIndicationID(id)        (PDUR_SOADIF_RXIND_BASE[(id)].upId)
#define PduR_iSoAdIfRxIndicationFunc(id)      (PduR_upIfRxIndicationTable[(PDUR_SOADIF_RXIND_BASE[(id)].upRxIndicationID)].PduR_upIfRxIndicationFunc)

#endif /* PDUR_CONFIG_SINGLE_IFRX */



#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aSoAdIfRxIndication(id, ptr)     PduR_dSoAdIfRxIndication((id), (ptr))
#else
#define PduR_aSoAdIfRxIndication(id, ptr)     PduR_iSoAdIfRxIndicationFunc(id)(PduR_iSoAdIfRxIndicationID(id), (ptr))
#endif /* PDUR_DEV_ERROR_DETECT */

#define PduR_rSoAdIfRxIndication(id, ptr)      PduR_aSoAdIfRxIndication((id), (ptr))


/* ------------------------------------------------------------------- */
#if defined(PDUR_CONFIG_SINGLE_IFTX_UP)
#define PduR_iSoAdIfTxConfirmationID(id)      (id)
#define PduR_iSoAdIfTxConfirmationFunc(id)      (PDUR_CONFIG_SINGLE_IFTX_UP(TxConfirmation))
#else
#define PduR_iSoAdIfTxConfirmationID(id)      (PDUR_SOADIF_TXCONF_BASE[(id)].upId)
#define PduR_iSoAdIfTxConfirmationFunc(id)    (PduR_upIfTxConfirmationTable[(PDUR_SOADIF_TXCONF_BASE[(id)].upTxConfirmationID)].PduR_upIfTxConfirmationFunc)

#endif /* PDUR_CONFIG_SINGLE_IFTX_UP */



#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aSoAdIfTxConfirmation(id)        PduR_dSoAdIfTxConfirmation(id)
#else
#define PduR_aSoAdIfTxConfirmation(id)        PduR_iSoAdIfTxConfirmationFunc(id)(PduR_iSoAdIfTxConfirmationID(id))
#endif /* PDUR_DEV_ERROR_DETECT */

#define PduR_rSoAdIfTxConfirmation(id)         PduR_aSoAdIfTxConfirmation(id)

/* ------------------------------------------------------------------- */
#if defined(PDUR_CONFIG_SINGLE_IFTX_UP)
#define PduR_iSoAdIfTriggerTransmitID(id)     (id)
#define PduR_iSoAdIfTriggerTransmitFunc(id)     (PDUR_CONFIG_SINGLE_IFTX_UP(TriggerTransmit))
#else
#define PduR_iSoAdIfTriggerTransmitID(id)     (PDUR_SOADIF_TXCONF_BASE[(id)].upId)
#define PduR_iSoAdIfTriggerTransmitFunc(id)   (PduR_upIfTriggerTxTable[(PDUR_SOADIF_TXCONF_BASE[(id)].upTriggerTxID)].PduR_upIfTriggerTxFunc)

#endif /* PDUR_CONFIG_SINGLE_IFTX_UP */



#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#define PduR_aSoAdIfTriggerTransmit(id, ptr)  PduR_dSoAdIfTriggerTransmit((id), (ptr))
#else
#define PduR_aSoAdIfTriggerTransmit(id, ptr)  PduR_iSoAdIfTriggerTransmitFunc(id)(PduR_iSoAdIfTriggerTransmitID(id), (ptr))
#endif /* PDUR_DEV_ERROR_DETECT */

#define PduR_rSoAdIfTriggerTransmit(id, ptr)   PduR_aSoAdIfTriggerTransmit((id), (ptr))

/* Invalid PDU id handlers ------------------------------------------ */
#define PDUR_IH_SoAdIfRx_RxIndication_Func     PDUR_DET_API(PduR_invId_IfRxIndication)
#define PDUR_IH_SoAdIfTx_TxConfirmation_Func   PDUR_DET_API(PduR_invId_IfTxConfirmation)
#define PDUR_IH_SoAdIfTx_TriggerTransmit_Func  PDUR_DET_API(PduR_invId_IfTriggerTransmit)




/* Anything after this point will not be placed in the code section. */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_SOADIF_LO_H */

