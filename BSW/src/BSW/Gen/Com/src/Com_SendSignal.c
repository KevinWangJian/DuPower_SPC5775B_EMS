
/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_SendSignal
 Syntax           : uint8 Com_SendSignal(Com_SignalIdType SignalId, const void*   SignalDataPtr)
 Description      : Service updates the signal object identified by SignalId with the signal
                    referenced by the SignalDataPtr parameter.
 Parameter        : SignalId -> Id of the signal.
                  : SignalDataPtr -> The pointer to the address where the application data is available.
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE/COM_BUSY
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSignal( VAR(Com_SignalIdType, AUTOMATIC)        SignalId,
                                      P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr )
{
    Com_TxSigConstPtrType TxSigConstPtr; /* Local pointer to Tx Signal static configuration */
    Com_TxIpduRamPtrType  TxIpduRamPtr;  /* Local pointer to Tx IPdu   static configuration */
    VAR(uint8, AUTOMATIC) Status;        /* Return status                                   */

    /* Start: Det */

    COM_REPORT_ERROR1((Com_Uninit_Flag == COM_UNINIT), COMServiceId_SendSignal, COM_E_UNINIT)

    COM_REPORT_ERROR1((SignalId >= COM_GET_NUM_TX_SIGNALS), COMServiceId_SendSignal, COM_E_PARAM)

    COM_REPORT_ERROR1((SignalDataPtr == NULL_PTR), COMServiceId_SendSignal, COM_E_PARAM_POINTER)

    /* End: Det */

    /* Convert external HandleId to internal HandleId for Tx Signal
     * IMP : before accessing the tables, it is required to convert the IDs
     * For pre-compile , conversion is not required. Access Macro will return the same ID, which is passed to it */
    SignalId      = COM_GET_TXSIGNAL_ID(SignalId);

    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA( SignalId );
    TxIpduRamPtr  = &COM_GET_TXPDURAM_S( TxSigConstPtr->IpduRef );

    /* Proceed only if Large Data tranmission is not in Progress */
    if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
    {
        Status = Com_InternalSendSignal(SignalId,SignalDataPtr);
    }
    else
    {
        /* The TxIPdu transmission of large Data IPdu is in progress, hence no signal update is allowed.
         * Until the transmission is completed. */
        Status = COM_BUSY;
    }

    return Status;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_InternalSendSignal
 Syntax           : uint8 Com_InternalSendSignal(Com_SignalIdType SignalId, const void*   SignalDataPtr)
 Description      : Service updates the signal object identified by SignalId with the signal
                    referenced by the SignalDataPtr parameter.
                    This is an internal function to update the signal.
                    This function doesnt do DET checks, these checks are done in the API itself.
 Parameter        : SignalId -> Internal Id of the signal. (Relevant for post-build case)
                  : SignalDataPtr -> The pointer to the address where the application data is available.
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_InternalSendSignal( VAR(Com_SignalIdType, AUTOMATIC)        SignalId,
                                              P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{

    Com_TxIpduConstPtrType TxIPduConstPtr;
    Com_TxIpduRamPtrType TxIpduRamPtr;    /* Local pointer to hold the Tx ipdu status information */
    Com_TxSigConstPtrType TxSigConstPtr;
    VAR(Com_SigMaxType, AUTOMATIC) TxNewVal;
    VAR(uint16_least, AUTOMATIC) IpduId_ui;
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;
    VAR(uint8, AUTOMATIC) Status;  /* Return status */
    VAR(uint8, AUTOMATIC) Type;
    VAR(boolean, AUTOMATIC) TransProp_bool;
    VAR(PduLengthType, AUTOMATIC) ByteNo_u8;
#ifdef COM_TxFilters
    /* To check if the current signal update has changed the TMS of the IPDU */
    VAR(boolean, AUTOMATIC) TMSChangeIndication;
#endif /* #ifdef COM_TxFilters */

    TxNewVal = (Com_SigMaxType)0; /*To remove compiler warning might be used uninitialized in this function*/
#ifdef COM_TxFilters
    TMSChangeIndication = COM_FALSE;
#endif/* #ifdef COM_TxFilters */

    Status         = E_OK;
    TransProp_bool = COM_FALSE;

    TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(SignalId);

    ConstByteValue_u8 = TxSigConstPtr->General;

    /* The signal type of the signal is obtained by the macro Com_GetValue(GEN,_TYPE,ConstByteValue_u8)
     * The value of ConstByteValue_u8 must be loaded with TxSigConstPtr->General */
    /*     Type = TxSigConstPtr->General.Type; */
    Type = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
    IpduId_ui = TxSigConstPtr->IpduRef;

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(IpduId_ui);

    SchM_Enter_Com_TxIpduProtArea(SENDSIGNAL);
#ifdef COM_TxSigUpdateBit
    /* Update bit if this bit is configured */
    /* if(TxSigConstPtr->General.UpdBitConf != COM_FALSE) */
    if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
    {
        /* Find the ByteNo_u8 of the IPDU buffer */
        ByteNo_u8 = (PduLengthType)(TxSigConstPtr->Update_Bit_Pos >> 3u);
        /* This macro sets the update bit value at the Update bit position */
        Com_SetUpdateBitValue(TxIPduConstPtr,TxSigConstPtr->Update_Bit_Pos,ByteNo_u8)
    }
#endif

    if(Type != (uint8)COM_UINT8_N)
    {
        VAR(uint8, AUTOMATIC) SigEndianess;
        SigEndianess = Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8);

        /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in the AUTOSAR specification,
           so suppressing warning "Cast from a pointer to void to a pointer to object". */
        switch(Type)
        {
        case COM_SINT8:
        case COM_UINT8:
            /* Update the Src_Buf with the data i.e typecast the data to uint8*/
            TxNewVal = (Com_SigMaxType)(*(P2CONST(uint8,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            break;
        case COM_SINT16:
        case COM_UINT16:
            /* Update the Src_Buf with the data i.e typecast the data to uint16*/
            TxNewVal = (Com_SigMaxType)(*(P2CONST(uint16,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            break;
        case COM_BOOLEAN:
            /* Update the Src_Buf with the data i.e typecast the data to the boolean variable*/
            TxNewVal = (Com_SigMaxType)COM_BOOL_TO_UNSIGNED(*(P2CONST(boolean,AUTOMATIC,COM_APPL_DATA))SignalDataPtr);
            break;
        case COM_SINT32:
        case COM_UINT32:
            /* Update the Src_Buf with the data i.e typecast the data to the uint32 variable*/
            TxNewVal = (Com_SigMaxType)(*(P2CONST(uint32, AUTOMATIC, COM_APPL_DATA))SignalDataPtr);
            break;
#ifdef COM_TXSIG_INT64
        case COM_UINT64:
        case COM_SINT64:
            /* Update the Src_Buf with the data i.e typecast the data to the uint64 variable*/
            TxNewVal = *(P2CONST(uint64, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;
            break;
#endif /* #ifdef COM_TXSIG_INT64 */

            /* FC_VariationPoint_START */
#ifdef COM_FLOAT32SUPP
        case COM_FLOAT32:
            /* Convert the float value into 32 bit stream and then pack the value */
            /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
               But the void pointer is always deferenced to a type, based on the pointers address alignment.
               Hence the alignment warning can safely be ignored. */
            (void)rba_BswSrv_MemCopy( (void *)&TxNewVal, SignalDataPtr, 4 );
            break;
#endif /* #ifdef COM_FLOAT32SUPP */
            /* FC_VariationPoint_END */

        default:
            /**
             * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal types are allowed
             * to be configured, hence default case is intentionally left empty.
             */
            break;
        }
        /* The signal Endianess is obtained by this macro Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8)
         * The value of ConstByteValue_u8 must be loaded with TxSigConstPtr->General */
        ConstByteValue_u8 = TxSigConstPtr->General;
        /* FC_VariationPoint_START */
#ifdef COM_TXSIG_FLOAT64SUPP
        if(Type == COM_FLOAT64)
        {
            float64 TxNewVal_f64;

            /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in the AUTOSAR specification,
               so suppressing warning "Cast from a pointer to void to a pointer to object". */
            TxNewVal_f64 = *(P2CONST(float64, AUTOMATIC, COM_APPL_DATA))SignalDataPtr;

            /* Convert the float value into 32 bit stream and then pack the value */
/*            Com_PackFloatSignal(TxSigConstPtr->General.Endianess,TxSigConstPtr->Bit_Pos,
                    TxNewVal_f64, TxIPduConstPtr->BuffPtr); */
            Com_PackFloatSignal(SigEndianess, TxSigConstPtr->Bit_Pos, TxNewVal_f64, TxIPduConstPtr->BuffPtr);
        }
        else
#endif /* #ifdef COM_TXSIG_FLOAT64SUPP */
    /* FC_VariationPoint_END */
        {
/*             Com_PackSignal(TxSigConstPtr->General.Endianess,
                    TxSigConstPtr->Bit_Pos, TxSigConstPtr->BitSize,
                    TxNewVal,TxIPduConstPtr->BuffPtr); */
            Com_PackSignal(SigEndianess, TxSigConstPtr->Bit_Pos, TxSigConstPtr->BitSize, TxNewVal,
                           TxIPduConstPtr->BuffPtr);
        }
    }
    else
    {
        /* Find the ByteNo_u8 of the IPDU buffer */
        ByteNo_u8 = (PduLengthType)(TxSigConstPtr->Bit_Pos >> 3u);
        /* The locks inside the function Com_ByteCopy() are removed.
         * Hence locks are used here
         */
        /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in the AUTOSAR specification,
           so suppressing warning "Cast from a pointer to void to a pointer to object". */
        Com_ByteCopy((TxIPduConstPtr->BuffPtr + ByteNo_u8),(const uint8*)SignalDataPtr,(uint32)TxSigConstPtr->BitSize);

    }
    SchM_Exit_Com_TxIpduProtArea(SENDSIGNAL);

    /* To get the signal Transfer property,The value of ConstByteValue_u8 must be loaded with
     * TxSigConstPtr->txSignalFields. */
    ConstByteValue_u8 = TxSigConstPtr->txSignalFields;
    /*if (TxSigConstPtr->txSignalFields.TransProp == (uint8)COM_TRIGGERED)*/
    if (Com_GetValue(TXSIG,_TP,ConstByteValue_u8) == (uint8)COM_TRIGGERED)
    {
        TransProp_bool = COM_TRUE;
    }
#ifdef COM_SigTriggeredOnChange
    /*     else if((TxSigConstPtr->txSignalFields.TransProp == (uint8)COM_TRIGGERED_ON_CHANGE)&&
            (COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) != TxNewVal)) */
    else if((Com_GetValue(TXSIG,_TP,ConstByteValue_u8) == (uint8)COM_TRIGGERED_ON_CHANGE)&&
            (COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) != (Com_OldValTrigOnChngType)TxNewVal))
    {
        TransProp_bool = COM_TRUE;
        COM_GET_OLDVALTRIGONCHANGE(TxSigConstPtr->OldValue_Index) = (Com_OldValTrigOnChngType)TxNewVal;

    }
#endif
    else
    {
        /* Transfer property = PENDING */
        /* Do nothing */
    }

    /* As per SWS_Com_00334: The AUTOSAR COM module shall update the values of its internal buffers
     * even for stopped I-PDUs.
     * So the IPDU Group status is checked only after Signal packing is done. */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckTxIPduStatus(IpduId_ui))
    {
#if defined(COM_SIGNALGATEWAY) || defined(COM_TxIPduTimeOut)
        VAR(boolean, AUTOMATIC)   timeOutEnableStatus_b;
        timeOutEnableStatus_b = Com_GetValue(TXSIG,_TOENABLED,ConstByteValue_u8);
#endif /* #if defined(COM_SIGNALGATEWAY) || defined(COM_TxIPduTimeOut) */

#ifdef COM_TxFilters
        /* Tx Filters are enabled and hence based on the TMC, TMS will be calculated.
         * Evaluate TMS only if IPDU doesnt have a fixed TM during configuration time and the signal contributes
         * to TMS calculation.
         */
        if(Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u8) != (uint8)COM_NOTCONFIGURED)
        {
            /* If TMS changes, Com_SigTxChangeMode() returns COM_TRUE */
            TMSChangeIndication = Com_SigTxChangeMode((Com_IpduIdType)IpduId_ui,(uint16)SignalId,TxNewVal,COM_FALSE);
        }
#endif /* #ifdef COM_TxFilters */

#ifdef COM_SIGNALGATEWAY
        if(Com_GetValue(TXIPDU,_ISGWPDU,TxIPduConstPtr->txIPduFields) != COM_FALSE)
        {
            if ( TransProp_bool )
            {
                /* For Tx Ipdus with Gw signals the event transmissions are done from Com_MainfunctionRouteSignals.
                 * The below step will raise a trigger in the next call of Com_MainfunctionRouteSignals, and
                 * the Tx Ipdu is transmitted.
                 * The Gw Ipdus which are cyclically triggered are sent from Com_mainfunctionTx */
                Com_SetRamValue(TXIPDU,_ISGWTRIGGRD,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
            }

#ifdef COM_TxFilters
            /* If the TMS changes, set the global TMS flag to consolidate transmission mode change
             * for the Gw-Tx IPdu after its last transmission */
            if ( TMSChangeIndication )
            {
                /* Consolidate the TMS Changes */
                if ( Com_GetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags) )
                {
                    Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                }
                else
                {
                    /* Store the transmission mode change and shall be used while triggering the Tx-IPdu from
                     * Com_MainFunctionRouteSignals() */
                    Com_SetRamValue(TXIPDU,_GWIPDUTMSCHANGED,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
                }
            }
#endif /* #ifdef COM_TxFilters */

#ifdef COM_TxIPduTimeOut
            if (timeOutEnableStatus_b != COM_FALSE)
            {
                /* This flag is set to start Timeout monitoring in the next call of Com_MainfunctionRouteSignals */
                Com_SetRamValue(TXIPDU,_ISTOENABLED,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
            }
#endif /* #ifdef COM_TxIPduTimeOut */

        }
        else
#endif /* #ifdef COM_SIGNALGATEWAY */
        {
            /* Process Tx-IPdu Transmission.
             * If this signal TX request causes mode change to MIXED/PERIODIC TM & signal transfer property is PENDING,
             * then do not transmit the IPDU. Because IPDU will be transmitted immediately,
             * due to periodic part of MIXED/PERIODIC mode.
             */
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status.
             * Evaluation(or no evaluation) of the 2nd operand does not impact the system behaviour,
             * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
             * Hence the warning is suppressed. */
            if (((TransProp_bool != COM_FALSE) &&
                (Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) <= COM_TXMODE_MIXED))
#ifdef COM_TxFilters
                || (TMSChangeIndication == COM_TRUE)
#endif
               )
            {
                /* All unused flags are reset here */
                Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                /* this flag will be set,as call happens from Com_SendSignal  */
                sendIpduFlag_u16.isEventTrig      = COM_SET;
                /* Pass mode indication value to Com_SendIpdu */
#ifdef COM_TxFilters
                sendIpduFlag_u16.isModeChangd     = COM_BOOL_TO_UNSIGNED(TMSChangeIndication);
#endif

                /* Signal transfer property */
                sendIpduFlag_u16.sigTransProp     = COM_BOOL_TO_UNSIGNED(TransProp_bool);

                /* Set the timeout flag if the signal contributes for Timeout and the transmission mode is MIXED/DIRECT.
                 * For PERIODIC TM, it is handled from Com_MainFunctionTx().
                 */
#ifdef COM_TxIPduTimeOut
                if (timeOutEnableStatus_b != COM_FALSE)
                {
                    sendIpduFlag_u16.isTimeoutReq = COM_SET;
                }
#endif /* #ifdef COM_TxIPduTimeOut */

                Com_SendIpdu((PduIdType)IpduId_ui, sendIpduFlag_u16);
            }
        }

    }/* End of If IpduGroupStarted */
    else
    {
        Status = COM_SERVICE_NOT_AVAILABLE;  /* COM461: Table 9 */
    }

    return Status;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

