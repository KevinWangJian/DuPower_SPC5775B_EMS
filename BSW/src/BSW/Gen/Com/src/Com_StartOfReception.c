

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

#ifdef COM_TP_IPDUTYPE

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_StartOfReception
 Syntax           : BufReq_ReturnType Com_StartOfReception( PduIdType ComRxPduId, const PduInfoType* TpSduInfoPtr, PduLengthType TpSduLength, PduLengthType* RxBufferSizePtr )
 Description      : Com_StartOfReception initiates reception of the TP I-PDU with ID ComRxPduId. It returns the size of the internal receive buffer for the I-PDU via RxBufferSizePtr.
 Parameter        : ComRxPduId,TpSduInfoPtr,TpSduLength,RxBufferSizePtr(out)
 Return value     : BufReq_ReturnType
 ***************************************************************************************************/

#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* MR12 RULE 8.13 VIOLATION: A pointer parameter(TpSduInfoPtr) in a function prototype should be declared as pointer to
   const if the pointer is not used to modify the addressed object. But AUTOSAR SWS specification signature is as below,
   Hence suppressed */
FUNC(BufReq_ReturnType, COM_CODE) Com_StartOfReception(PduIdType ComRxPduId, const PduInfoType* TpSduInfoPtr, PduLengthType TpSduLength, PduLengthType* RxBufferSizePtr )
{

    /* Start: Variable declarations */
    Com_RxIpduConstPtrType RxIPduConstPtr;
    Com_RxIpduRamPtrType RxIPduRamPtr;
    VAR(BufReq_ReturnType, AUTOMATIC) return_value;
    /* End: Variable declarations */

    /* Start: Det */
    COM_REPORT_ERROR3((Com_Uninit_Flag == COM_UNINIT), COMServiceId_StartOfReception, COM_E_UNINIT)

    COM_REPORT_ERROR3((ComRxPduId >= COM_GET_NUM_RX_IPDU), COMServiceId_StartOfReception, COM_E_PARAM)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
       * to internal Id which is generated through configuration
       * If PC variant is selected, then no mapping table will be used. */

    ComRxPduId = COM_GET_RX_IPDU_ID(ComRxPduId);


    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(ComRxPduId);

    RxIPduRamPtr = &COM_GET_RXPDURAM_S(ComRxPduId);
    return_value = BUFREQ_OK;

    /*Currently this parameter is not used*/
    (void)TpSduInfoPtr;

    /* Check if the Ipdu group containing this IPDU is started */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckRxIPduStatus(ComRxPduId))
    {
        /* Check if the reception requests fits Ipdu size,
         * else return overflow as we cannot accomodate this */
        if(TpSduLength <= RxIPduConstPtr->Size)
        {
            /* As all the checks are passed, then we accept this reception and
             * set flag which will be monitored in CopyRxData calls */
            Com_SetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr ->RxFlags,COM_TRUE);
            /* Initialise the received length RAM variable to zero here,
             * This length variable will be incremented in the Com_CopyRxData API */
            RxIPduRamPtr->RxTPIPduLength = 0;

            /* Update the TP with Ipdu size for buffer size out parameter */
           *RxBufferSizePtr = RxIPduConstPtr->Size;
        }
        else
        {
            return_value = BUFREQ_E_OVFL;
        }
    }
    else
    {
        return_value = BUFREQ_E_NOT_OK;
    }

    return return_value;

}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif /* COM_TP_IPDUTYPE */

