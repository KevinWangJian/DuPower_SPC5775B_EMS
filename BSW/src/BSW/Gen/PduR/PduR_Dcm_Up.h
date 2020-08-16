
#ifndef PDUR_DCM_UP_H
#define PDUR_DCM_UP_H

#include "PduR_Prv.h"

/**
 * @ingroup PDUR_DCM_H
 *
 * To ensure that the function declarations in this header are located in the code section.
 */
#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

#if defined(PDUR_CONFIG_SINGLE_TPTX_LO)
#define PduR_iDcmTransmitID(id)           (id)                                   /* PDUR_CUBAS 287 */
#define PduR_iDcmTransmitFunc(id)           (PDUR_CONFIG_SINGLE_TPTX_LO(Transmit)) /* PDUR_CUBAS 287 */
#else
#define PduR_iDcmTransmitID(id)           (PDUR_DCM_TX_BASE[(id)].loId)          /* PDUR_CUBAS 163 */
#define PduR_iDcmTransmitFunc(id)           (PduR_loTransmitTable[(PDUR_DCM_TX_BASE[(id)].loTransmitID)].PduR_loTransmitFunc)

#endif /* PDUR_CONFIG_SINGLE_TPTX_LO */



#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
 #define PduR_aDcmTransmit(id, ptr)        PduR_dDcmTransmit((id), (ptr))
#else

 #define PduR_aDcmTransmit(id, ptr)        PduR_iDcmTransmitFunc(id)(PduR_iDcmTransmitID(id), (ptr))
#endif /* PDUR_DEV_ERROR_DETECT */

#define PduR_rDcmTransmit(id, ptr)         PduR_aDcmTransmit((id), (ptr))

/* Multicast mapping ------------------------------------------------ */

/**
 * @ingroup PDUR_DCM_H
 *      Support function to handle multicast from PduR_DcmTransmit.\n
 *
 * @param in        id                      : multicast ID to be transmitted.\n
 * @param in        P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info  : Pointer to a structure with PDU related data that shall be transmitted:
 *                                            data length and pointer to buffer.\n
 * \n
 * @return          E_OK: Transmit request has been accepted.\n
 *                  E_NOT_OK: Transmit request has not been accepted.\n
 */
extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_MF_Dcm_Transmit_Func( VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info );

/* Invalid PDU id handlers ------------------------------------------ */
#define PDUR_IH_Dcm_Transmit_Func    PDUR_DET_API(PduR_invId_UpTransmit)



/* PDUR481: PduR Cancel Transmit Feature */



#if defined(PDUR_CONFIG_SINGLE_TPCANCELTX_LO)
#define PduR_iDcmCancelTransmitID(id)           (id)
#define PduR_iDcmCancelTransmitFunc(id)         (PDUR_CONFIG_SINGLE_TPCANCELTX_LO(CancelTransmit))
#else
#define PduR_iDcmCancelTransmitID(id)           (PDUR_DCM_TX_BASE[(id)].loId)
#define PduR_iDcmCancelTransmitFunc(id)         (PduR_loCancelTransmitTable[(PDUR_DCM_TX_BASE[(id)].loCancelTransmitID)].PduR_loCancelTransmitFunc)
#endif /* PDUR_CONFIG_SINGLE_TPCANCELTX_LO */





/**
 * @ingroup PDUR_DCM_H
 *
 * Anything after this point will not be placed in the code section.
 */
#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_DCM_UP_H */

