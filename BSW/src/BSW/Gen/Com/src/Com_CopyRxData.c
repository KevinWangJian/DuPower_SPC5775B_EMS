

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

#ifdef COM_TP_IPDUTYPE

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_CopyRxData
 Syntax           : BufReq_ReturnType Com_CopyRxData( PduIdType PduId, const PduInfoType* PduInfoPointer, PduLengthType* RxBufferSizePtr )
 Description      : Called once upon reception of each segment. Within this call, the received data is copied to the
                    receive TP buffer. The API should only be called with an SduLength greater 0 if the RxBufferSizePtr
                    returned by the previous API call indicates sufficient receive buffer (SduLength = RxBufferSizePtr).
                    The function must only be called if the connection has been accepted by an initial call to
                    Com_StartOfReception.
 Parameter        : PduId,PduInfoPointer,RxBufferSizePtr(out)
 Return value     : BufReq_ReturnType
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/* MR12 RULE 8.13 VIOLATION: A pointer parameter in a function prototype should be declared as pointer to const if the pointer is not used to modify the addressed object.
 But AUTOSAR SWS specification signature is as below, Hence suppressed */
FUNC(BufReq_ReturnType, COM_CODE) Com_CopyRxData( PduIdType PduId, const PduInfoType* PduInfoPointer, PduLengthType* RxBufferSizePtr )
{

    /* Start: Variable declarations */
    Com_RxIpduConstPtrType RxIPduConstPtr;
    Com_RxIpduRamPtrType RxIPduRamPtr;
    VAR(BufReq_ReturnType, AUTOMATIC) return_value;
    /* End: Variable declarations */

    /* Start: Det */
    COM_REPORT_ERROR3((Com_Uninit_Flag == COM_UNINIT), COMServiceId_CopyRxData, COM_E_UNINIT)

    COM_REPORT_ERROR3((PduId >= COM_GET_NUM_RX_IPDU), COMServiceId_CopyRxData, COM_E_PARAM)

    COM_REPORT_ERROR3((PduInfoPointer == NULL_PTR), COMServiceId_CopyRxData, COM_E_PARAM_POINTER)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */

    PduId = COM_GET_RX_IPDU_ID(PduId);


    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(PduId);

    RxIPduRamPtr = &COM_GET_RXPDURAM_S(PduId);
    return_value = BUFREQ_OK;

    /* Check whether RxPdu flag is set, which will be done in Com_StartOfReception */
        if(Com_GetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr->RxFlags))
        {
            /* Check whether the requested length fits the Ipdu */
            /* This check is to protect from RAM corruption when TP recieves more than what was expected */
            if((RxIPduRamPtr->RxTPIPduLength + PduInfoPointer->SduLength) <= RxIPduConstPtr->Size)
            {
                /*Check if the requested length is a non-zero value*/
                if(PduInfoPointer->SduLength != 0u)
                {
                    /* Now Copy the Data into the IPDU buffer */
                     Com_ByteCopy((RxIPduConstPtr->BuffPtr + RxIPduRamPtr->RxTPIPduLength),(uint8*)(PduInfoPointer ->SduDataPtr),PduInfoPointer->SduLength);
                     RxIPduRamPtr->RxTPIPduLength += PduInfoPointer->SduLength ;
                }
                    /* Update the out parameter with the remaining buffer length */
                    *RxBufferSizePtr = RxIPduConstPtr->Size - RxIPduRamPtr->RxTPIPduLength;

            } /* if((RxIPduRamPtr->RxTPIPduLength + PduInfoPointer->SduLength) <= RxIPduConstPtr->Size) */
            else
            {
                /* If the TP request more than the available RxBuffer size */
                return_value = BUFREQ_E_OVFL;
            }

        }/* if(Com_GetRamValue(RXIPDU,_LARGEDATAINPROG,RxIPduRamPtr->RxFlags)) */

        else
        {
            /*This flag(_LARGEDATAINPROG) will be reset, when IpduGroup is stopped
             * Hence no explicit check for IpduGroup is required*/
            return_value = BUFREQ_E_NOT_OK;
        }

   return return_value;
}

#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#endif /* COM_TP_IPDUTYPE */

