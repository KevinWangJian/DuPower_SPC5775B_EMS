


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
 * PduR_GF_TTIf_Buf_TriggerTransmit_Func - Handle gatewaying between If layers where the destination layer
 *      uses Trigger Transmit data provision, and is configured to use  a FIFO
 *      Note that PDUR254 specifies that an item of state called TxIdx shall be
 *      associated with each FIFO. This is logically equivalent to the readPtr which
 *      we maintain for the FIFO anyway and so is not supplied separately.
 *
 *
 * \param           PduIdType gwayId - GatewayID that is requested to be transmitted.
 *                  uint8 *  dataPtr - Pointer to place inside the transmit buffer of the L-PDU where data shall be
 *                                     copied to.
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* The signature needs to be compatible with <Up>_TriggerTransmit */
FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_FIFO_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC) gwayId,
                                                                P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) dataPtr)
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + gwayId;
    /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
     * Hence Supressed.*/
    PduR_FifoType         fifo = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr     dyn  = (PduR_FifoDynIfPtr)(fifo->dyn);


    VAR(uint16, AUTOMATIC)  i;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest(); /* enter the critical area */

    /* We must copy the data into the buffer */

    for(i = 0 ; i < dyn->actLen ; i++)
    {
        *((dataPtr->SduDataPtr)+i) = *((dyn->readPtr)+i);
    }
    /* Copy actual Length to SduLength */
    dataPtr->SduLength = dyn->actLen;
    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest();  /* exit the critical area */
    return E_OK;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"


#endif /* PDUR_IFGATEWAY_SUPPORT */

