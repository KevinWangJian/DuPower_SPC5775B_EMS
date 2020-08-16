
/* Provides a FIFO for gatewaying to an IF layer which uses trigger transmit
 * transmission. Note also that PDUR254 specifies that an item of state called TxIdx shall be
 * associated with each FIFO. This is logically equivalent to the readPtr which
 * we maintain for the FIFO anyway and so is not supplied separately.
 */

#include "PduR_Prv.h"
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"

#include "Dem.h"           /* Dem_ReportErrorStatus */
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "PduR.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/**
 **************************************************************************************************
 * PduR_GF_TTIf_FIFO_Transmit_Func -
 *  Provides a FIFO for gatewaying to an IF layer which uses trigger transmit
 *  transmission. Note also that PDUR254 specifies that an item of state called TxIdx shall be
 *  associated with each FIFO. This is logically equivalent to the readPtr which
 *  we maintain for the FIFO anyway and so is not supplied separately.
 *
 *
 * \param           PduIdType gwayId          : Gateway ID that has been received
 *                  PduR_TxPduInfoPtr info: A pointer to a structure with PDU related data that shall be transmitted:
 *                                          data length and pointer to buffer
 * \retval          Std_ReturnType  - E_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* The signature needs to be compatible with <Lo>_Transmit */



FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_FIFO_Transmit_Func( VAR(PduIdType, AUTOMATIC) gwayId,
                                                                   P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + gwayId;
    /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
     * Hence Suppressed.*/
    PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr)(fifo->dyn);
    VAR(PduInfoType, AUTOMATIC)    infoBuf;
    VAR(uint8, AUTOMATIC)  callTx   = 0u;
    VAR(uint8, AUTOMATIC)  logError = 0u;


    VAR(uint16, AUTOMATIC)  i;

    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest(); /* Enter critical area */

    /* At various points in this function we call <Lo>If_Transmit().
     * We do not need to keep the resource protecting the FIFO locked for the duration of the
     * call to <Lo>If_Transmit() since, for the following reasons, we can be sure that we will not
     * re-enter <Lo>If_Transmit() preemptively (for the same PDU ID) from another task:
     * - This function is not re-entrant for the same PDU ID, so it cannot cause a re-entrant call
     *   to <Lo>If_Tranmsit().
     * - The only other place where we could call <Lo>If_Transmit() is from PduR_GF_TTIf_FIFO_TxConfirmation(),
     *   but this will only occur if the FIFO contains >1 element, and, when we call <Lo>If_Transmit() from
     *   this function, we can be sure the FIFO has 1 element (and it cannot be filled further, since
     *   this function is not re-entrant for the same PDU ID).
     * See Bugzilla 13110 for further discussion of these matters.
     */

    /*check if sdu length is greater than fifo size*/
    if(info->SduLength > fifo->eltSize)
    {
        infoBuf.SduLength = fifo->eltSize;
    }
    else
    {
        infoBuf.SduLength = info->SduLength;
    }
    /* Update the Actual length in the Dyn*/
    dyn->actLen = infoBuf.SduLength;

    /* Check if there is TX confirmation pending */
    if( 0 == dyn->txConfPending )
    {
        /* If There is no TX confirmation pending,so forward the PDU immediately. */
        dyn->txConfPending = 1;
        callTx = 1;

        /* Fall through and enqueue the PDU. */
    }
    /* There is a TX confirmation pending. Is the FIFO full? */
    else
    {
        if( dyn->used == fifo->nrElts )
        {
            /* If The TX confirmation is lost flush the FIFO and force another transmission in an attempt to unblock things. */

            /* Remove all elements from the FIFO; do not reset txConfPending. */
            dyn->writePtr = dyn->readPtr;
            dyn->used = 0;

            /* Forward the PDU immediately. */
            callTx = 1;

            /* Report the loss of the FIFO contents to the DEM*/

            logError = 1;

            /* Fall through and enqueue the PDU. */
        }
        else
        {
            /* To remove MISRA */
        }

    }

    /* Store the PDU in the FIFO. */

    for(i = 0 ; i < infoBuf.SduLength ; i++)
    {
        *((dyn->writePtr)+i) = *((info->SduDataPtr)+i);
    }
    /*MR12 RULE 1.3,13.2 VIOLATION : No issue in code.*/
    PDUR_FIFO_INC_AND_WRAP( fifo, dyn->writePtr );
    dyn->used++; /* increment the number of bytes used */

    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest(); /* exit critical resource */

    /* Call other APIs after we have unlocked our resource */

    if( 1 == logError )
    {
        #if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
         Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
        #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
         PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
        #endif
        #endif /* PDUR_DEM_PDU_INSTANCE_LOST */
    }

    if( 1 == callTx )
    {
        /* Forward the PDU to the configured lower layer. */
        
        infoBuf.SduDataPtr = info->SduDataPtr;

        /* See note above about re-entrancy of this function call. */
        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        if( E_OK != PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &infoBuf ))
        #else
        if( E_OK != PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, &infoBuf ))
        #endif
        {
            /* The lower layer failed to accept the PDU for transmission (and ought to have logged an
             * error). We must remove the PDU from the FIFO.
             *
             * PDUR255 states that we should only set TxConfP if transmission is successful;
             * we do it slightly differently by setting TxConfP before transmission and unsetting
             * it again if transmission fails. Our approach is necessary in case the lower layer calls
             * TxConfirmation() before we have a chance to set TxConfP.
             *
             * The note above about the re-entrancy of <Lo>If_Transmit() also implies that no-one else
             * has been manipulating the FIFO since we unlocked it, so it is safe for us to remove the
             * failed PDU from the FIFO. */
            dyn->writePtr = fifo->begin;
            dyn->readPtr = dyn->writePtr;
            dyn->used = 0;
            dyn->txConfPending = 0;

            #if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
             Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
            #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
             PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
            #endif
            #endif /* PDUR_DEM_PDU_INSTANCE_LOST */

        }
    }



    /* This return code will always be discarded by one of our callers. */
    return E_OK;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IFGATEWAY_SUPPORT */

