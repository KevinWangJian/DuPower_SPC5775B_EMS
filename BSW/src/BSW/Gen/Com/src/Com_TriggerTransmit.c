

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_TriggerTransmit
 Syntax           : Std_ReturnType Com_TriggerTransmit(PduIdType TxPduId,PduInfoType* PduInfoPtr)
 Description      : Service called by the lower layer when an AUTOSAR COM I-PDU shall be transmitted.
                    Within this function, AUTOSAR COM shall copy the contents of its I-PDU transmit
                    buffer to the L-PDU buffer given by PduInfoPtr.
 Parameter        : TxPduId -> id of the Tx ipdu
                  : PduInfoPtr -> Pointer to the address where the COM module shall copy the ipdu data and length information.
 Return value     : E_OK/E_NOT_OK
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(Std_ReturnType, COM_CODE) Com_TriggerTransmit(VAR(PduIdType, AUTOMATIC) TxPduId,P2VAR(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{

    Com_TxIpduConstPtrType TxIPduConstPtr;
    VAR(uint16_least, AUTOMATIC) Size;
    VAR(Std_ReturnType, AUTOMATIC) Status;
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;
#endif
#if ( defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TXDOUBLEBUFFER) || defined(COM_TxIPduCallOuts) )
    VAR(boolean, AUTOMATIC) byteValue_b;
#endif /* #if ( defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TXDOUBLEBUFFER) || defined(COM_TxIPduCallOuts) ) */
#if defined (COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined (COM_TXDOUBLEBUFFER)
    Com_TxIpduRamPtrType TxIpduRamPtr;
#endif
    /* Start: Det */

    COM_REPORT_ERROR4((Com_Uninit_Flag == COM_UNINIT), COMServiceId_TriggerTransmit, COM_E_UNINIT)

    COM_REPORT_ERROR4((TxPduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TriggerTransmit, COM_E_PARAM)

    COM_REPORT_ERROR4((PduInfoPtr == NULL_PTR), COMServiceId_TriggerTransmit, COM_E_PARAM_POINTER)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
    * to internal Id which is generated through configuration
    * If PC variant is selected, then no mapping table will be used. */

    TxPduId = COM_GET_TX_IPDU_ID(TxPduId);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxPduId);


#if defined (COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined (COM_TXDOUBLEBUFFER)
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
#endif
    Status = E_OK;
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
    /* Only the first byte of txIPduFields is needed */
    ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;
#endif
    Size = (uint32)TxIPduConstPtr->Size;

    /*Check if Ipdu Group is started*/
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(!(COM_CheckTxIPduStatus(TxPduId)))
    {
        /*This part will be executed when IPDU Group is Stopped (old value will be returned)*/
        Status = E_NOT_OK;
    }

#if ( defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TXDOUBLEBUFFER) )
    byteValue_b = Com_GetRamValue(TXIPDU,_ISDYNIPDU,TxIPduConstPtr->txIPduFields);
#endif /* #if ( defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT) || defined(COM_TXDOUBLEBUFFER) ) */

    /* No MDT monitoring is required*/
    /* Dont check for Ipdu Group Stopped/Started i.e Normal reaction on Com_TriggerTransmit( )*/
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
    /* The total Ipdu size will be sum of Ipdu static length and dynamic length for a dynamic IPdu.
     * The Dynamic length of the Ipdu is updated in the call to Com_SendDynSignal.*/
    /* if(COM_SET == TxIPduConstPtr->txIPduFields.IsDynPdu) */
    if(COM_TRUE == byteValue_b)
    {
        Size = TxIPduConstPtr->Size + TxIpduRamPtr->Com_DynLength;
    }
#endif/*#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT */

#ifdef COM_TXDOUBLEBUFFER
    {
        /* Call Com_ByteCopy() for Copying the Data of Tx Local buffer into the dataptr passed
         * The locks inside the function Com_ByteCopy() are removed.
         * Hence locks are used here
         */
        /* if((TxIpduRamPtr->Com_TransMode.LatestTransMode == COM_TXMODE_NONE) || (COM_SET == TxIPduConstPtr->txIPduFields.IsDynPdu)) */
        if ((Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) == COM_TXMODE_NONE)
            ||(COM_TRUE == byteValue_b))
        {
            /* First copy the data to the IF buffer to avoid other core changing the data between */
            /* Enter critical section to prevent other processor writing to this buffer while it is being copied */
            SchM_Enter_Com_TxIpduProtArea(TRIGGERTRANSMIT);
            Com_ByteCopy(PduInfoPtr ->SduDataPtr,TxIPduConstPtr->BuffPtr,Size);

            /* Trigger Transmit is processed even if the IPDU Group is STOPPED*/
            /* If the parameter ComTxIPduClearUpdateBit of an I-PDU is configured to TriggerTransmit, the AUTOSAR COM module
             * shall clear all update-bits of all contained signals and signal groups
             * after the contents of this I-PDU was requested by a call to Com_TriggerTransmit.*/
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
            /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit == (uint8)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)*/
            if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) == (uint16)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)
            {
                Com_ClearUpdateBits(TxIPduConstPtr);
            }
#endif /* #if defined ((COM_TxSigUpdateBit)||defined(COM_TxSigGrpUpdateBit)) */
            SchM_Exit_Com_TxIpduProtArea(TRIGGERTRANSMIT);
        }
        else
        {
            SchM_Enter_Com_TxPduDoubleBuffer();
            Com_ByteCopy(PduInfoPtr ->SduDataPtr,TxIPduConstPtr->LocalBuffPtr,Size);
            /* Trigger Transmit is processed even if the IPDU Group is STOPPED*/
            /* If the parameter ComTxIPduClearUpdateBit of an I-PDU is configured to TriggerTransmit, the AUTOSAR COM module
             * shall clear all update-bits of all contained signals and signal groups
             * after the contents of this I-PDU was requested by a call to Com_TriggerTransmit.*/
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
            /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit == (uint8)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)*/
            if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) == (uint16)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)
            {
                Com_ClearUpdateBits(TxIPduConstPtr);
            }
#endif /* #if defined ((COM_TxSigUpdateBit)||defined(COM_TxSigGrpUpdateBit)) */
            SchM_Exit_Com_TxPduDoubleBuffer();

        }
        PduInfoPtr ->SduLength = (PduLengthType)Size;
    }

#else   /*Else of COM_TXDOUBLEBUFFER*/

    SchM_Enter_Com_TxIpduProtArea(TRIGGERTRANSMIT);
    Com_ByteCopy(PduInfoPtr->SduDataPtr,TxIPduConstPtr->BuffPtr,Size);
    PduInfoPtr ->SduLength = (PduLengthType)Size;
    /* Trigger Transmit is processed even if the IPDU Group is STOPPED*/
    /* If the parameter ComTxIPduClearUpdateBit of an I-PDU is configured to TriggerTransmit, the AUTOSAR COM module
     * shall clear all update-bits of all contained signals and signal groups
     * after the contents of this I-PDU was requested by a call to Com_TriggerTransmit.*/
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
    /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit == (uint8)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)*/
    if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u8) == (uint16)COM_CLRUPDATEBIT_TRIGGERTRANSMIT)
    {
        Com_ClearUpdateBits(TxIPduConstPtr);
    }
#endif /* #if defined ((COM_TxSigUpdateBit)||defined(COM_TxSigGrpUpdateBit)) */
    SchM_Exit_Com_TxIpduProtArea(TRIGGERTRANSMIT);

#endif  /*End of COM_TXDOUBLEBUFFER*/

    /* The callout is processed over the data given to the IF buffer
     * Note: As the data pointer given to application is a Pointer to variable, There are chances that application layer can update the data.
     * Any data update from application which happens over this target buffer are passed to the lower layer,
     * How ever this updated data is not stored in the local buffers of Com.
     * Impact: Application cannot assume that the data updates done in one Com Callout function will be preserved across different calls of Com callout. */
#ifdef COM_TxIPduCallOuts
    byteValue_b = Com_GetValue(TXIPDU,_ISCALLOUTFRMTRIGTRANS,TxIPduConstPtr->txIPduFields);
    /*Call Ipdu_Callout*/
    if((Status != E_NOT_OK)&& (TxIPduConstPtr->CallOut != NULL_PTR) && (byteValue_b != COM_FALSE))
    {
        /* The Return Value from IPDU Callout shall be ignored */
        (void)TxIPduConstPtr->CallOut(TxPduId,PduInfoPtr->SduDataPtr);
    }
#endif


    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

