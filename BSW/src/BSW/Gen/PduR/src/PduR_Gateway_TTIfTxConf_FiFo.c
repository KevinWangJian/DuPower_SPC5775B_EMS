
#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_TTIf_FIFO_TxConfirmation
 *      The signature must be compatible with <Up>_TxConfirmation()
 *  Handle TxConfirmation for gatewaying between If layers where a FIFO is in use
 *  Note that PDUR254 specifies that an item of state called TxIdx shall be
 *  associated with each FIFO. This is logically equivalent to the readPtr which
 *  we maintain for the FIFO anyway and so is not supplied separately.
 *
 * \param           PduIdType gwayId
 *
 * \retval          None
 * \seealso         PDUR252, PDUR256, PDUR196, PDUR198, PDUR178, Bugzilla 13110
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_GF_TTIf_FIFO_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwayId )
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + gwayId;
    /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
     * Hence Supressed.*/
    PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr) fifo->dyn;
    VAR(PduInfoType, AUTOMATIC) info;

    SchM_Enter_PduR_LockIFGatewayTriggerTxConf(); /* enter critical area */
    /*Check for txConfPending */
    if( 0 != dyn->txConfPending )
    {
        uint8 BreakFlag = 0;    /* When this flag is 1; break of the loop will be executed */
        /* Loop until a entry is transmitted from the FIFO, or until the FIFO is empty. */
        while( BreakFlag == 0 )
        {
            if( 1 == dyn->used )
            {
                /* The FIFO has a single entry */
                dyn->writePtr = dyn->readPtr;
                dyn->used = 0;
                dyn->txConfPending = 0;

                BreakFlag = 1;
            }
            else
            {
                /* The FIFO has at least two entries. We remove the first one and transmit the second one. */

                PDUR_FIFO_INC_AND_WRAP( fifo, dyn->readPtr );
                dyn->used--;

                info.SduDataPtr = dyn->readPtr;
                info.SduLength = dyn->actLen;

                /* Unlock the resource protecting the FIFO before the call <Lo>If_Transmit(),
                 * however if it is done so there is a risk that call to <Lo>If_Transmit() will be pre-empted
                 * by a call to PduR_GF_TTIf_FIFO_Transmit_Func() for the same PDU ID.If this occurs, and if the
                 * FIFO is full, the FIFO will be flushed from under our feet and <Lo>If_Transmit() will be
                 * called re-entrantly for the same PDU ID by PduR_GF_TTIf_FIFO_Transmit_Func(),
                 * hence the resource is locked for the duration of the call to <Lo>If_Transmit().
                 *
                 * A solution which avoids the need to lock the resource in this manner is available, but
                 * Autosar are shy of modifying the spec accordingly without further discussion.  */


                #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                if( E_OK == PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &info ))
                #else
                if( E_OK == PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &info ))
                #endif
                {
                    BreakFlag = 1;
                }
            }
        }  /* while loop */

    } /* if loop */

    SchM_Exit_PduR_LockIFGatewayTriggerTxConf(); /* exit the critical area */


}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IFGATEWAY_SUPPORT */

