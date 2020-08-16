
/* Provides a single buffer for gatewaying to an IF layer which uses trigger transmit */

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
 * PduR_GF_TTIf_Buf_Transmit_Func - Provides a single buffer for gatewaying to an IF layer which uses trigger transmit
 *                  Forward the PDU to the configured lower layer
 *
 * \param           PduIdType gwayId - Gateway ID
 *                  P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info - pointer to tx buffer
 *
 *
 * \retval          Std_ReturnType - E_OK
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
/* The signature needs to be compatible with <Lo>_Transmit */
FUNC( Std_ReturnType, PDUR_CODE ) PduR_GF_TTIf_Buf_Transmit_Func(VAR(PduIdType, AUTOMATIC) gwayId,
                                                                 P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) info)
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

    /*This should be NoNest critical section*/
    SchM_Enter_PduR_LockIFGatewayTriggerTxNoNest(); /* enter critical area */
    /*check if sdulength is greater than conf length*/
    if(info->SduLength > dyn->confLen)
    {
        infoBuf->SduLength = dyn->confLen;
    }
    else
    {
        infoBuf->SduLength = info->SduLength;
    }

    /* Store the PDU in the buffer, overwrite the current contents if necessary. */


    for(i = 0 ; i < infoBuf->SduLength ; i++)
    {
        *((infoBuf->SduDataPtr)+i) = *((info->SduDataPtr)+i);
    }

    SchM_Exit_PduR_LockIFGatewayTriggerTxNoNest(); /* exit critical area */


    /* Forward the PDU to the configured lower layer. */
    /* Ignore the result of this function call. */
    #if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
    (void)PDUR_BASE_RPTBL(loTxTablePtr)[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, infoBuf );
    #else
    (void)PduR_loTransmitTable[(gt->transmitID)].PduR_loTransmitFunc( gt->loId, infoBuf );
    #endif

    /* This return code will always be discarded by one of our callers. */
    return E_OK;
}
/* ------------------------------------------------------------------------ */
/* End section for code */

#define PDUR_STOP_SEC_CODE
#include "PduR_MemMap.h"
#endif /* PDUR_IFGATEWAY_SUPPORT */

