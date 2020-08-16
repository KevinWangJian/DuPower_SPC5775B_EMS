

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/***************************************************************************************************
 Function name    : Com_UpdateShadowSignal
 Syntax           : void Com_UpdateShadowSignal(Com_SignalIdType  SignalId,const void*   SignalDataPtr)
 Description      : Service updates a group signal with the data, referenced by SignalDataPtr
                    The update of the group signal data is done in the shadow buffer
 Parameter        : SignalId -> Id of the GroupSignal
                  : SignalDataPtr -> Pointer to the address where application data is available
 Return value     : None
 ***************************************************************************************************/

#ifdef COM_TX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_UpdateShadowSignal(VAR(Com_SignalIdType, AUTOMATIC)  SignalId,P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{
#ifdef COM_SigGrpTriggeredOnChange
    Com_TxSigGrpRamPtrType TxSigGrpRamPtr;      /* Local pointer to hold the status of the SignalGroup */
#endif
    Com_TxGrpSigConstPtrType  TxGrpSigConstPtr; /* Local pointer to hold the address of Tx GroupSignal static configuration */
    VAR(Com_SigMaxType, AUTOMATIC) TxNewVal;    /* Local variable to store the new value */
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;
    VAR(uint8, AUTOMATIC) Type;                 /* Type of the GroupSignal */

    /* Start: Det */

    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_UpdateShadowSignal, COM_E_UNINIT)

    COM_REPORT_ERROR((SignalId >= COM_GET_NUM_TX_GRPSIGNALS), COMServiceId_UpdateShadowSignal, COM_E_PARAM)

    COM_REPORT_ERROR((SignalDataPtr == NULL_PTR), COMServiceId_UpdateShadowSignal, COM_E_PARAM_POINTER)

    /* End: Det */

    SignalId = COM_GET_TXGRPSIGNAL_ID(SignalId);

    TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(SignalId);

    /*Get the Bit field Byte value*/
    ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
    /*     Type = TxGrpSigConstPtr->txGrpSigFields.Type; */
    Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
    TxNewVal = 0;
    /* Even if the IPDU Group is stopped this API will update the data in the Internal Buffer */
    if(Type != (uint8)COM_UINT8_N)
    {
        SchM_Enter_Com_TxGrpSigBuffer();
        switch(Type)
        {
        /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in AUTOSAR specification,
           so suppressing warning "Cast from a pointer to void to a pointer to object". */
        case COM_UINT8:
        case COM_SINT8:
            /* Update the Src_Buf with the data i.e typecast the data to uint8*/
            TxNewVal = (Com_SigMaxType)(*(P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr);
            COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint8)TxNewVal;
            break;
        case COM_UINT16:
        case COM_SINT16:
            /* Update the Src_Buf with the data i.e typecast the data to uint16*/
            TxNewVal = (Com_SigMaxType)(*(P2CONST(uint16, AUTOMATIC, COM_APPL_DATA))SignalDataPtr);
            COM_GET_TXGRPSIGTYPEU16_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint16)TxNewVal;
            break;
        case COM_BOOLEAN:
            /* Update the Src_Buf with the data i.e typecast the data to the boolean variable*/
            TxNewVal = (Com_SigMaxType)COM_BOOL_TO_UNSIGNED(*(P2CONST(boolean,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint8)TxNewVal;
            break;
        case COM_UINT32:
        case COM_SINT32:
            /* Update the Src_Buf with the data i.e typecast the data to the uint32 variable*/
            TxNewVal = (Com_SigMaxType)(*(P2CONST(uint32,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            COM_GET_TXGRPSIGTYPEU32_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = (uint32)TxNewVal;
            break;
#ifdef COM_TXGRPSIG_INT64
        case COM_UINT64:
        case COM_SINT64:
            /* Update the Src_Buf with the data i.e typecast the data to the uint64 variable*/
            TxNewVal = *(P2CONST(uint64, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;
            COM_GET_TXGRPSIGTYPEU64_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)  = TxNewVal;
            break;
#endif /* #ifdef COM_TXGRPSIG_INT64 */

            /* FC_VariationPoint_START */
#ifdef COM_GRPSIGFLOAT32SUPP
        case COM_FLOAT32:
            /* Convert the float value into 32 bit stream and then pack the value into shadow buffer */
            /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
               But the void pointer is always deferenced to a type, based on the pointers alignment.
               Hence the alignment warning can safely be ignored. */
            (void)rba_BswSrv_MemCopy( (void *)(&COM_GET_TXGRPSIGTYPEU32_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index)),
                                      (const void *)SignalDataPtr, 4 );
            break;
#endif /* #ifdef COM_GRPSIGFLOAT32SUPP */

#ifdef COM_TXGRPSIG_FLOAT64SUPP
        case COM_FLOAT64:
            /* Pack the float value into float64 shadow buffer */
            /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in AUTOSAR specification,
               so suppressing warning "Cast from a pointer to void to a pointer to object". */
            COM_GET_TXGRPSIGTYPEFLOAT64_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index) =
                                                            *(P2CONST(float64,AUTOMATIC,COM_APPL_DATA))SignalDataPtr;
            break;
#endif
        /* FC_VariationPoint_END */

        default:
            /**
             * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal types are allowed
             * to be configured, hence default case is intentionally left empty.
             */
            break;
        }
        SchM_Exit_Com_TxGrpSigBuffer();
        /* Before updating endianess conversion should be performed */
        /* Update the Signal in the Shadow buffer, here you have to find the bitposition in the shadow
        buffer for this signal  */
#ifdef COM_SigGrpTriggeredOnChange
        TxSigGrpRamPtr = &COM_GET_TXSIGGRPFLAG(TxGrpSigConstPtr->SigGrpRef);
        /* Check if the group signal contributes to evaluation of transfer property of signal group */
        /* if((TxGrpSigConstPtr->txGrpSigFields.TransProp != (uint8)COM_FALSE)  && (COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) != TxNewVal)) */
        if((Com_GetValue(TXGRPSIG,_TP,ConstByteValue_u8) != COM_FALSE)  &&
           (COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) != (Com_OldValTrigOnChngType)TxNewVal))
        {
            /* Update the old value */
            COM_GET_OLDVALTRIGONCHANGE(TxGrpSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxNewVal;
            /* TxSigGrpRamPtr ->txSigGrpRAMFields.TrigOnChange = COM_TRUE */
            Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr ->txSigGrpRAMFields,COM_TRUE);
        }
#endif
    }
    else
    {
        /* The locks inside the function Com_ByteCopy() are removed.
         * Hence locks are used here
         * Copy the *SignalDataPtr to all the Bytes of this signal in Shadow buffer */
        SchM_Enter_Com_TxGrpSigBuffer();

        /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in AUTOSAR specification,
           so suppressing warning "Cast from a pointer to void to a pointer to object". */
        Com_ByteCopy(&COM_GET_TXGRPSIGTYPEU8_BUFF(TxGrpSigConstPtr->TxGrpSigBuff_Index),
                (P2CONST(uint8, AUTOMATIC, COM_APPL_DATA))SignalDataPtr,(uint32)TxGrpSigConstPtr->BitSize);

        SchM_Exit_Com_TxGrpSigBuffer();
    }

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif

