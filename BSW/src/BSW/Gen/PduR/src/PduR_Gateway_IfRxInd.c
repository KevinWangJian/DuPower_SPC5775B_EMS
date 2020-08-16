
#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_If_RxIndication_Func
 *    Performs signature translation between RxIndication() and Transmit() during interface-to-interface gatewaying.
 *    The signature needs to be compatible with <Up>_RxIndication
 *
 * \param           PduIdType Id    : ID of gateway PDU that has been received.
 *                  const uint8 *ptr: Pointer to rx SDU (buffer of received payload)
 *
 * \retval          None
 * \seealso         PDUR195
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_GF_If_RxIndication_Func( VAR(PduIdType, AUTOMATIC) gwayId, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) data)
{
    P2CONST( PduR_GT_IfTx, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_TX_BASE + gwayId;

    /* Transmit function may point to one of:
     * - PduR_GwMcTx_Transmit_Func() for multicast
     * - Lower layer, for DD non-FIFO transmission.
     * - PduR_GF_DDIf_FIFO_Transmit_Func() for DD-FIFO gateway.
     * - PduR_GF_TTIf_FIFO_Transmit_Func() for TT-FIFO gateway.
     * - PduR_GF_TTIf_Buf_Transmit_Func() for single-buffer TT gateway. */
    /*Ignore the result of this function call. */
    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
    (void)PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc(gt->loId, data);
    #else
    (void)PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc(gt->loId, data);
    #endif
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IFGATEWAY_SUPPORT */

