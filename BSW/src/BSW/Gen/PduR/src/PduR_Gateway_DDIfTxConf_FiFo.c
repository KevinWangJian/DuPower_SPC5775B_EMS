
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
 *  Handle TxConfirmation from a lower interface layer which uses
 *  data direct transmission and which is configured with a DD-FIFO.
 *
 * \param           PduIdType gwayId
 *
 * \retval          None
 * \seealso         PDUR252, PDUR259, PDUR196, PDUR198, PDUR194, Bugzilla 13110
 * \usedresources
 **************************************************************************************************
 */

FUNC( void, PDUR_CODE ) PduR_GF_DDIf_FIFO_TxConfirmation_Func( VAR(PduIdType, AUTOMATIC) gwayId )
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + gwayId;
    /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
     * Hence Supressed.*/
    PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr)(fifo->dyn);
    VAR(PduInfoType, AUTOMATIC)          info;
    VAR(Std_ReturnType, AUTOMATIC)       txResult;

    /* Enter Critical Section*/
    SchM_Enter_PduR_LockIFGatewayTxConf();

     /**/
    if( 0 != dyn->txConfPending )  /* MEDC17 Core Adaptation */
    {
        uint8 BreakFlag = 0;    /*When this flag is 1; break of the loop will be executed*/
        /* Loop until we have transmitted an entry from the FIFO, or until the FIFO is empty. */
        while( BreakFlag == 0 )
        {
            if( 0 == dyn->used )
            {
                /* The FIFO is empty */
                dyn->txConfPending = 0;
                BreakFlag = 1;
            }
            else
            {
                /* The FIFO is non-empty, so we must transmit the next pending PDU. */
                info.SduDataPtr = dyn->readPtr;
                info.SduLength = dyn->actLen;

                /* We really ought to unlock the resource protecting the FIFO before we call <Lo>If_Transmit(),
                 * however if we do so there is a risk that our call to <Lo>If_Transmit() will be pre-empted
                 * by a call to PduR_GF_DDIf_FIFO_Transmit_Func() for the same PDU ID. If this occurs, and if the
                 * FIFO is full, the FIFO will be flushed from under our feet and <Lo>If_Transmit() will be
                 * called re-entrantly for the same PDU ID by PduR_GF_DDIf_FIFO_Transmit_Func().
                 *
                 * We cannot allow either of these things to happen, so we keep the resource locked for the
                 * duration of the call to <Lo>If_Transmit().
                 *
                 * A solution which avoids the need to lock the resource in this manner is available, but
                 * Autosar are shy of modifying the spec accordingly without further discussion. See
                 * Bugzilla 13110 for a complete discussion. */

                #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
                txResult = PDUR_BASE_RPTBL(loTxTablePtr)[gt->transmitID].PduR_loTransmitFunc( gt->loId, &info );
                #else
                txResult = PduR_loTransmitTable[gt->transmitID].PduR_loTransmitFunc( gt->loId, &info );
                #endif

                /* Remove the transmitted PDU from the FIFO. */
                /*IGNORE RULE 402: Operation holds good */
                PDUR_FIFO_INC_AND_WRAP( fifo, dyn->readPtr );
                dyn->used--;

                /* Stop looping if we have successfully transmitted a PDU. */

                if( E_OK == txResult )
                {
                    BreakFlag = 1;
                }
            }
        }    /* end of while loop */

    } /* End of if block */

    SchM_Exit_PduR_LockIFGatewayTxConf();
    /* Exit Critical Section*/


}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IFGATEWAY_SUPPORT */

