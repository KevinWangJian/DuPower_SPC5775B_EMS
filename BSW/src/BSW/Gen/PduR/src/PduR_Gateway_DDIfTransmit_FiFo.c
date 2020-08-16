
/* Provides a FIFO for gatewaying to an IF layer which uses data direct transmission.  */

#include "PduR_Prv.h"

/* Check for Gatewaying support during pre-compile time */
#if defined(PDUR_IFGATEWAY_SUPPORT) && (PDUR_IFGATEWAY_SUPPORT != STD_OFF)
#include "PduR_Gw.h"
#include "Dem.h"           /* For Dem_ReportErrorStatus */
#if (!defined(DEM_AR_RELEASE_MAJOR_VERSION) || (DEM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DEM_AR_RELEASE_MINOR_VERSION) || (DEM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define PDUR_START_SEC_CODE
#include "PduR_MemMap.h"

/* The signature needs to be compatible with <Lo>_Transmit */

FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_DDIf_FIFO_Transmit_Func(VAR(PduIdType, AUTOMATIC) id, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
{
    VAR(Std_ReturnType, AUTOMATIC) RetVal;
    VAR(PduInfoType, AUTOMATIC)    infoBuf;
    P2CONST( PduR_GT_If, AUTOMATIC, PDUR_CONST ) gt = PDUR_GW_IF_BASE + id;
    /* MR12 RULE 11.5 VIOLATION : 'pointer-to-void' is being cast to a 'pointer-to-object' type and this conversion will not result in any misalignment.
     * Hence Supressed.*/
    PduR_FifoType        fifo   = (PduR_FifoType)(gt->buffer);
    PduR_FifoDynIfPtr    dyn    = (PduR_FifoDynIfPtr)(fifo->dyn);


    VAR(uint16_least, AUTOMATIC)  i;

    /*  MEDC17 Core Adaptation */
    /* Enter Critical Section */


    SchM_Enter_PduR_LockIFGatewayTx();

    /* At various points in this function we call <Lo>If_Transmit().
     * We do not need to keep the resource protecting the FIFO locked for the duration of the
     * call to <Lo>If_Transmit() since, for the following reasons, we can be sure that we will not
     * re-enter <Lo>If_Transmit() preemptively (for the same PDU ID) from another task:
     * - This function is not re-entrant for the same PDU ID, so it cannot cause a re-entrant call
     *   to <Lo>If_Tranmsit().
     * - The only other place where we could call <Lo>If_Transmit() is from PduR_GF_DDIf_FIFO_TxConfirmation_Func(),
     *   but this will only occur if the FIFO is non-empty, and, when we call <Lo>If_Transmit() from this function,
     *   we can be sure the FIFO *is* empty (and it cannot be re-filled, since this function is not re-entrant
     *   for the same PDU ID).
     * See Bugzilla 13110 for further discussion of these matters.
     */

     /**/

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
    infoBuf.SduDataPtr = info->SduDataPtr;

    /* Check for Tx Confirmation pending*/
    if( 0 == dyn->txConfPending )
    {
        /* There is no TX confirmation pending, so forward the PDU. */
        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        RetVal = PDUR_BASE_RPTBL(loTxTablePtr)[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
        #else
        RetVal = PduR_loTransmitTable[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
        #endif
        /* Retval gives the status about the transmitted data */
        if(RetVal == E_OK)
        {
            dyn->txConfPending = 1;
        }
        else
        {
            /* Error occured during transmission */
            #if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
             Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
            #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
             PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
            #endif
            #endif /* PDUR_DEM_PDU_INSTANCE_LOST */
        }
    }
    /* There is a TX confirmation pending. Is the FIFO not full yet? */
    else if( dyn->used != fifo->nrElts )
    {
        /* Store our PDU in the FIFO. */
        /*  memcpy( dyn->writePtr, info->SduDataPtr, fifo->eltSize );        */
        /*  MEDC17 Core Adaptation, since we are not including string.h file */

        /* START: MEDC17 Core Adaptation, as memcpy( ) is present in string.h file which we are not including  */
        /* Copy the SduDataPtr into Temp */

        for(i = 0 ; i < infoBuf.SduLength ; i++)
        {
            *( (dyn->writePtr) + i) = *( (info->SduDataPtr) + i );

        }

        /* END: MEDC17 Core Adaptation, as memcpy( ) is present in string.h file which we are not including  */
        /* FIFO Routines */
        PDUR_FIFO_INC_AND_WRAP( fifo, dyn->writePtr );
        dyn->used++;

    }
    /* There is a TX confirmation pending, and the FIFO is full. */
    else
    {
        /* We assume that the TX confirmation which we are waiting for has got lost. Therefore
         * we flush the FIFO and force another transmission in an attempt to unblock things. */

        /* Remove all elements from the FIFO; do not reset txConfPending. */
        dyn->writePtr = dyn->readPtr;
        dyn->used = 0;


        /* Report the loss of the FIFO contents to the DEM:.
        * See Bugzilla 12468 for reasons why we deviate from the spec by not checking the size of the
        * FIFO before calling the DEM. */
        #if defined(PDUR_DEM_PDU_INSTANCE_LOST) && (PDUR_DEM_PDU_INSTANCE_LOST != 0)
         Dem_ReportErrorStatus( PDUR_E_PDU_INSTANCE_LOST, DEM_EVENT_STATUS_FAILED );
        #if(PDUR_DSM_REINT_SUPPORT != STD_OFF)
         PduR_DsmReInitStruct.instanceLostErrorStatus =  DEM_EVENT_STATUS_FAILED;
        #endif
        #endif /* PDUR_DEM_PDU_INSTANCE_LOST */

        /* See note above about re-entrancy of this function call. */
        #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
        (void)PDUR_BASE_RPTBL(loTxTablePtr)[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
        #else
        (void)PduR_loTransmitTable[gt->transmitID].PduR_loTransmitFunc( gt->loId, &infoBuf );
        #endif
    }
    /* PDUR_RTA-BSW_end 258 */

    /* MEDC17 Core Adaptation */
    SchM_Exit_PduR_LockIFGatewayTx();
    /* Exit Critical Section */
    /* This return code will always be discarded by one of our callers. */
    return E_OK;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IFGATEWAY_SUPPORT */

