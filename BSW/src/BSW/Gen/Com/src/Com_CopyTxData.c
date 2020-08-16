

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

#ifdef COM_TP_IPDUTYPE

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_CopyTxData
 Syntax           : BufReq_ReturnType Com_CopyTxData( PduIdType PduId, PduInfoType* PduInfoPtr, RetryInfoType* RetryInfoPtr, PduLengthType* TxDataCntPtr )
 Description      : At invocation of Com_CopyTxData the AUTOSAR COM module copies the re-quested transmit data of the
                    large IPDU with ID PduId from its internal transmit buffer to the location specified by the PduInfoPtr.
                    The function Com_CopyTxData also calculates and sets the TxDataCntPtr to the amount of remaining
                    bytes for the transmission of this large I-PDU. When TpDataState is TP_DATARETRY,
                    Com_CopyTxData copies previously transmitted data again.
 Parameter        : PduId,PduInfoPtr,RetryInfoPtr,TxDataCntPtr(out)
 Return value     : BufReq_ReturnType
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* MR12 RULE 8.13 VIOLATION: A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object.
 But AUTOSAR SWS specification signature is as below, Hence suppressed */
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyTxData( PduIdType PduId, PduInfoType* PduInfoPtr, RetryInfoType* RetryInfoPtr, PduLengthType* TxDataCntPtr )
{
    Com_TxIpduConstPtrType TxIPduConstPtr;      /* Local pointer to the Tx ipdu static configuration */
    Com_TxIpduRamPtrType TxIpduRamPtr;          /* Local pointer to the Tx ipdu status structure */
    VAR(BufReq_ReturnType, AUTOMATIC) return_value;

    /* Start: Det */
    COM_REPORT_ERROR3((Com_Uninit_Flag == COM_UNINIT), COMServiceId_CopyTxData, COM_E_UNINIT)

    COM_REPORT_ERROR3((PduId >= COM_GET_NUM_TX_IPDU), COMServiceId_CopyTxData, COM_E_PARAM)

    COM_REPORT_ERROR3((PduInfoPtr == NULL_PTR), COMServiceId_CopyTxData, COM_E_PARAM_POINTER)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
    * to internal Id which is generated through configuration
    * If PC variant is selected, then no mapping table will be used. */

    PduId = COM_GET_TX_IPDU_ID(PduId);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(PduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(PduId);
    return_value = BUFREQ_OK;

    /* Currently Retransmission feature is not supported */
    (void)RetryInfoPtr;

    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckTxIPduStatus(PduId))
    {
        /* Check whether the large data pdu flag has been set */
        if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags))
        {
            /* Ensure that this is not query request */
            if(PduInfoPtr->SduLength != 0u)
            {
                /* Requested length should be less than the PduLength */
                if((PduInfoPtr->SduLength + TxIpduRamPtr->TxTPIPduLength) <= COM_GET_PDUINFO_S(PduId).SduLength)
                {

                    /* Now Copy the Data from the IPDU buffer to SduDataPointer */
                    Com_ByteCopy((uint8*)(PduInfoPtr ->SduDataPtr),(TxIPduConstPtr->BuffPtr + TxIpduRamPtr->TxTPIPduLength),PduInfoPtr->SduLength);

                    /* Keep track of how many bytes of data has been copied into the lower layer buffer,
                     * which is used as an offset for Ipdu buffer */
                    TxIpduRamPtr->TxTPIPduLength += PduInfoPtr->SduLength;

                    /* Update the out parameter TxDataCntPtr, with the number of bytes remaining */
                    *TxDataCntPtr = COM_GET_PDUINFO_S(PduId).SduLength - TxIpduRamPtr->TxTPIPduLength;

                }
                else
                {
                    return_value = BUFREQ_E_NOT_OK;
                }
            }
            else
            {
                /* Update the out parameter TxDataCntPtr, with the number of bytes remaining */
                *TxDataCntPtr = COM_GET_PDUINFO_S(PduId).SduLength - TxIpduRamPtr->TxTPIPduLength;
            }

        }
        else
        {
            return_value = BUFREQ_E_NOT_OK;
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

