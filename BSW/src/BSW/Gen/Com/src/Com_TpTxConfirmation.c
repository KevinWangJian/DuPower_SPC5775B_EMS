

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

#ifdef COM_TP_IPDUTYPE

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_TpTxConfirmation
 Syntax           : void Com_TpTxConfirmation( PduIdType PduId, Std_ReturnType Result )
 Description      : This function is called by the PduR after a large I-PDU has been transmitted via the transport protocol on its network.
 Parameter        : PduId,Result
 Return value     : Void
 ***************************************************************************************************/

#define COM_START_SEC_CODE
#include "Com_MemMap.h"

FUNC(void, COM_CODE) Com_TpTxConfirmation( PduIdType PduId, Std_ReturnType Result )
{

    /* Start: Variable declarations */
    Com_TxIpduRamPtrType TxIPduRamPtr;
    /* End: Variable declarations */

    /* Start: Det */
    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_TpTxConfirmation, COM_E_UNINIT)

    COM_REPORT_ERROR((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TpTxConfirmation, COM_E_PARAM)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
    * to internal Id which is generated through configuration
    * If PC variant is selected, then no mapping table will be used. */

    PduId = COM_GET_TX_IPDU_ID(PduId);

    TxIPduRamPtr = &COM_GET_TXPDURAM_S(PduId);

    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckTxIPduStatus(PduId))
    {
        /* Check whether the large data pdu flag has been set */
        if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIPduRamPtr->Com_TxFlags))
        {
            Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIPduRamPtr->Com_TxFlags,COM_FALSE);

            /* Proceed further to process the TxConfirmation only if the transmission result was successfull  */
            if(Result == E_OK)
            {

                /* Call the internal function Com_ProcessTxConfirmation, to process this TxConfirmation */
                Com_ProcessTxConfirmation(PduId);

            }
        }
    }
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif /* COM_TP_IPDUTYPE */

