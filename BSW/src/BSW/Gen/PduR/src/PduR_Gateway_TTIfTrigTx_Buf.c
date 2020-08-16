
#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "PduR.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_TTIf_Buf_TriggerTransmit_Func -   Handle gatewaying between If layers where the destination layer
 *            uses Trigger Transmit data provision, and is configured to use  a single entry buffer
 *
 * \param           PduIdType gwayId - GatewayID of FlexRay that is requested to be transmitted.
 *                  uint8 *  dataPtr - Pointer to place inside the transmit buffer of the L-PDU where data shall be
 *                                     copied to.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

/* The signature needs to be compatible with <Up>_TriggerTransmit */
FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_Buf_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC) gwayId,
                                                               P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) dataPtr )
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST )       gt;
    P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )       dyn;
    P2VAR( PduInfoType, AUTOMATIC, PDUR_APPL_DATA )  infoBuf;
    VAR(uint16, AUTOMATIC)  i;
    gt      = PDUR_GW_IF_BASE + gwayId;
    /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
     * Hence Supressed.*/
    dyn     = (P2CONST( PduR_Buf_If_dynamic, AUTOMATIC, PDUR_CONST )) gt->buffer;
    infoBuf = dyn->gwBuf;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest();

    /* Retrieve the PDU from the buffer and hand it out. */

    for(i = 0 ; i < infoBuf->SduLength ; i++)
    {
        *((dataPtr->SduDataPtr)+i) = *((infoBuf->SduDataPtr)+i);
    }

    dataPtr->SduLength = infoBuf->SduLength;
    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();
    return E_OK;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"

#endif /* PDUR_IFGATEWAY_SUPPORT */

