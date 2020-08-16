

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_ReceiveShadowSignal
 Syntax           : void Com_ReceiveShadowSignal(Com_SignalIdType  SignalId, void*  SignalDataPtr)
 Description      : Service for receiving the shadow Signal
 Parameter        : SignalId -> Id of the signal
                  : SignalDataPtr -> Pointer to the the signal data
 Return value     : None
 ***************************************************************************************************/
#ifdef COM_RX_SIGNALGROUP
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ReceiveShadowSignal( VAR(Com_SignalIdType, AUTOMATIC)      SignalId,
                                              P2VAR(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr)
{
    Com_RxGrpSigConstPtrType RxGrpSigConstPtr;
    VAR(Com_RxGrpSigBuffIndexType, AUTOMATIC) GrpSigBuff_Index;
    VAR(uint8, AUTOMATIC)    SigType;

    /* Start: Det */
    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_ReceiveShadowSignal, COM_E_UNINIT)

    COM_REPORT_ERROR((SignalId >= COM_GET_NUM_RX_GRPSIGNALS), COMServiceId_ReceiveShadowSignal, COM_E_PARAM)

    COM_REPORT_ERROR((SignalDataPtr == NULL_PTR), COMServiceId_ReceiveShadowSignal, COM_E_PARAM_POINTER)
    /* End: Det */

    SignalId = COM_GET_RXGRPSIGNAL_ID(SignalId);

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(SignalId);

    SigType = Com_GetValue(RXGRPSIG,_TYPE,RxGrpSigConstPtr->rxGrpSigFields);
    GrpSigBuff_Index = RxGrpSigConstPtr->RxGrpSigBuff_Index;

    /* The last known value has to be given back even if IPDU Group is stopped
     * So No need of checking Ipdu Group Status */

    /* If Signal Type is not UINT8[n] */
    if ( SigType != (uint8)COM_UINT8_N )
    {
        VAR(Com_SigMaxType, AUTOMATIC) RxNewVal_GrpSig;

        /* Copy Com_RxNewVal to the SignalDataPtr*/
        switch( SigType )
        {
        /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in the AUTOSAR specification, to support
         * different groupsignal types. On call to this api, application has to pass a valid datatype pointer address.
         * Hence this warning can safely be ignored. */
        case COM_UINT8:
        {
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT8_BUFF(GrpSigBuff_Index);
            *(uint8*)SignalDataPtr  =  (uint8)RxNewVal_GrpSig;
        }
            break;
        case COM_UINT16:
        {
            #if (CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT16_BUFF(GrpSigBuff_Index);
            #if (CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
            *(uint16*)SignalDataPtr =  (uint16)RxNewVal_GrpSig;
        }
            break;
        case COM_UINT32:
        {
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT32_BUFF(GrpSigBuff_Index);
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
            *(uint32*)SignalDataPtr =  (uint32)RxNewVal_GrpSig;
        }
            break;
        case COM_SINT8:
        {
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT8_BUFF(GrpSigBuff_Index);
            *(sint8*)SignalDataPtr  =  (sint8)RxNewVal_GrpSig;
        }
            break;
        case COM_SINT16:
        {
            #if (CPU_TYPE == CPU_TYPE_8)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT16_BUFF(GrpSigBuff_Index);
            #if (CPU_TYPE == CPU_TYPE_8)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
            *(sint16*)SignalDataPtr =  (sint16)RxNewVal_GrpSig;
        }
            break;
        case COM_SINT32:
        {
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT32_BUFF(GrpSigBuff_Index);
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
            *(sint32*)SignalDataPtr =  (sint32)RxNewVal_GrpSig;
        }
            break;
#ifdef COM_RXGRPSIG_INT64
        case COM_UINT64:
        {
            SchM_Enter_Com_RxGrpSigBuff();
            RxNewVal_GrpSig = COM_GET_RXGRPSIGTYPEUINT64_BUFF(GrpSigBuff_Index);
            SchM_Exit_Com_RxGrpSigBuff();
            *(uint64*)SignalDataPtr =  (uint64)RxNewVal_GrpSig;
        }
            break;
        case COM_SINT64:
        {
            SchM_Enter_Com_RxGrpSigBuff();
            RxNewVal_GrpSig = COM_GET_RXGRPSIGTYPEUINT64_BUFF(GrpSigBuff_Index);
            SchM_Exit_Com_RxGrpSigBuff();
            *(sint64*)SignalDataPtr =  (sint64)RxNewVal_GrpSig;
        }
            break;
#endif /* #ifdef COM_RXGRPSIG_INT64 */
        case COM_BOOLEAN:
        {
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT8_BUFF(GrpSigBuff_Index);
            *(boolean*)SignalDataPtr =  (boolean)(RxNewVal_GrpSig != 0u);
        }
            break;

/* FC_VariationPoint_START */
#ifdef COM_GRPSIGFLOAT32SUPP
        case COM_FLOAT32:
        {
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Enter_Com_RxGrpSigBuff();
            #endif
            RxNewVal_GrpSig = (Com_SigMaxType)COM_GET_RXGRPSIGTYPEUINT32_BUFF(GrpSigBuff_Index);
            #if (CPU_TYPE != CPU_TYPE_32)
            SchM_Exit_Com_RxGrpSigBuff();
            #endif
            /* Convert the 32 bit stream into float value */
            /* MR12 DIR 1.1 VIOLATION: Explicit cast is provided in line with rba_BswSrv_MemCopy() definition.
               But the void pointer is always deferenced to a type, based on the pointers alignment.
               Hence the alignment warning can safely be ignored. */
           (void)rba_BswSrv_MemCopy(SignalDataPtr,(const void *)&RxNewVal_GrpSig,4);
        }
            break;
#endif /* COM_GRPSIGFLOAT32SUPP */

#ifdef COM_RXGRPSIG_FLOAT64SUPP
        case COM_FLOAT64:
        {
            VAR(float64, AUTOMATIC) RxNewVal_GrpSig_f64;
            SchM_Enter_Com_RxGrpSigBuff();
            RxNewVal_GrpSig_f64 =  (float64)COM_GET_RXGRPSIGTYPEFLOAT64_BUFF(GrpSigBuff_Index);
            SchM_Exit_Com_RxGrpSigBuff();
            /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in the AUTOSAR specification, to support
               different groupsignal types. On call to this api, application has to pass a valid datatype pointer address.
               Hence this warning can safely be ignored. */
            *(float64*)SignalDataPtr =  (float64)RxNewVal_GrpSig_f64;

        }
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
    }
    else
    {
        /* UINT8[n] Signal */
        SchM_Enter_Com_RxGrpSigBuff();

        /* MR12 RULE 11.5 VIOLATION: SignalDataPtr is defined as void pointer in the AUTOSAR specification, to support
           different groupsignal types. On call to this api, application has to pass a valid datatype pointer address.
           Hence this warning can safely be ignored. */
        Com_ByteCopy( (uint8*)SignalDataPtr, &(COM_GET_RXGRPSIGTYPEUINT8_BUFF(GrpSigBuff_Index)),
                      (uint32)RxGrpSigConstPtr->BitSize);

        SchM_Exit_Com_RxGrpSigBuff();
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif


#if defined(COM_RX_SIGNALGROUP) && (defined(COM_RxSigGrpInvalid) || defined (COM_RxFilters))

/***************************************************************************************************
 Function name    : Com_ValidateRxSignalGroup
 Syntax           : void Com_ValidateRxSignalGroup(Com_RxIntSignalGroupIdType SignalGrpId, const uint8 *Src)
 Description      : Internal function for checking invalid values for given signal group
 Parameter        : SignalGrpId - Signal Group Id to be validated
                    Src         - IPdu buffer pointer
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8,COM_CODE) Com_ValidateRxSignalGroup( VAR(Com_RxIntSignalGroupIdType, AUTOMATIC) SignalGrpId,
                                                P2CONST(uint8, AUTOMATIC, COM_APPL_DATA) Src)
{
    Com_RxGrpSigConstPtrType RxGrpSigConstPtr; /* Local pointer to Rx GroupSignal static configuration */
    Com_RxSigGrpConstPtrType RxSigGrpConstPtr; /* Local pointer to Rx SignalGroup static configuration */
    Com_RxSigGrpRamPtrType   RxSigGrpRamPtr;    /* Local RAM pointer to SignalGroup RAM structure */
    VAR(uint16_least, AUTOMATIC) Idx_GrpSig_ui;
    VAR(Com_SigMaxType, AUTOMATIC) RxNewVal_GrpSig;
    VAR(uint8, AUTOMATIC)    ConstByteValue_u8;
    VAR(uint8, AUTOMATIC)    ValidateSigGrp_u8;
#ifdef COM_RxFilters
    VAR(uint8, AUTOMATIC)    filterAlgo_u8;
#endif
    VAR(boolean, AUTOMATIC)  InvAction_b;
    VAR(boolean, AUTOMATIC)  breakFromLoop_b;

    breakFromLoop_b   = COM_FALSE;
    ValidateSigGrp_u8 = COM_SET;
    RxNewVal_GrpSig   = 0;

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(SignalGrpId);

    RxGrpSigConstPtr = COM_GET_RXGRPSIG_CONSTDATA(RxSigGrpConstPtr->FirstGrpSig_Index);

    RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(SignalGrpId);

    for( Idx_GrpSig_ui = RxSigGrpConstPtr->No_Of_GrpSig;
         ((breakFromLoop_b != COM_TRUE) && (Idx_GrpSig_ui != 0u)); Idx_GrpSig_ui-- )
    {
        ConstByteValue_u8 = RxGrpSigConstPtr->rxGrpSigFields;
#ifdef COM_RxFilters
        filterAlgo_u8 = RxGrpSigConstPtr->Filter_Algo;
#endif
        InvAction_b   = Com_GetValue(RXGRPSIG,_INVACTION,ConstByteValue_u8);

        /* if(RxGrpSigConstPtr->rxGrpSigFields.GrpSigInvalid != COM_NONE) */
        if((InvAction_b != COM_FALSE)
#ifdef COM_RxFilters
                || (filterAlgo_u8 != COM_NOTCONFIGURED)
#endif
                )
        {
            VAR(uint8, AUTOMATIC) SigType;
            /* SigType = RxGrpSigConstPtr->rxGrpSigFields.Type */
            SigType = Com_GetValue(RXGRPSIG,_TYPE,ConstByteValue_u8);

            /*Unpack the group signal value */
            if(SigType == (uint8)COM_UINT8_N)
            {
                RxNewVal_GrpSig = (Com_SigMaxType)
                                   Com_UnpackOpaqueSignal(RxGrpSigConstPtr->Bit_Pos, RxGrpSigConstPtr->BitSize, Src);
            }
            /* FC_VariationPoint_START */
            else if(SigType == COM_FLOAT64)
            {
                /* Do nothing */
            }
            /* FC_VariationPoint_END */
            else
            {
                RxNewVal_GrpSig = Com_UnpackSignal( Com_GetValue(RXGRPSIG,_ENDIANESS,ConstByteValue_u8),
                                                    RxGrpSigConstPtr->Bit_Pos ,RxGrpSigConstPtr->BitSize, Src);
            }

            /* The fact that this function is called indicates that invalid value is configured for
             * one of the group signal
             */
            /* Check Sign type, perform sign extension if the signal is of Negative */
            if(((SigType & 0x01u) == 0x01u) &&
                ((RxNewVal_GrpSig & ((Com_SigMaxType)0x1u << (RxGrpSigConstPtr->BitSize - 1))) != 0u))
            {
                RxNewVal_GrpSig = Com_PerformSignExtension(RxNewVal_GrpSig, RxGrpSigConstPtr->BitSize);
            }

#if defined(COM_RxSigGrpInvalid)
            /* For Float signals the invalid value is type casted to UNIT32 before comparing */
            if ((InvAction_b != COM_FALSE) && ((Com_SigMaxType)RxGrpSigConstPtr->DataInvalid_Val == RxNewVal_GrpSig)
                    /* FC_VariationPoint_START */
                    && (SigType != COM_FLOAT64)
                    /* FC_VariationPoint_END */
                    )
            {
                ConstByteValue_u8 = RxSigGrpConstPtr->rxSignalGrpFields;

                /* if ( RxSigGrpConstPtr->rxSignalGrpFields.GrpSigInvalid == (uint8)COM_REPLACE) */
                if ( Com_GetValue(RXSIGGRP,_INVACTION,ConstByteValue_u8) == (uint8)COM_REPLACE)
                {
                    /*  set the flag to Replace all the Group Signals(Com_RxNewVal_GrpSig) which is under
                     * the same Signal Group with Initial value */
                    ValidateSigGrp_u8 = COM_REPLACE_TO_INIT;
                }
#ifdef COM_RxSigGrpInvalidNotify
                else
                {
                    /* If invalid action is NOTIFY */
                    /* Check for invalid notification, only if SigGrpNotify_Flag is TRUE ie invalid notifcation
                     * function not called yet..
                     * The invalid notification function should be called only once for signal group
                     */
                    ValidateSigGrp_u8 = COM_RESET;
                    /* if(RxSigGrpRamPtr ->rxSigGrpRAMFields.SigGrpNotify_Flag != COM_FALSE) */
                    if (Com_GetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr ->rxSigGrpRAMFields) != COM_FALSE)
                    {
                        /* RxSigGrpRamPtr ->rxSigGrpRAMFields.SigGrpNotify_Flag = COM_FALSE */
                        Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr ->rxSigGrpRAMFields,COM_FALSE);

                        /* Call Invalid notification for the whole Signal Group as soon as the
                         * first group signal with invalid value is encountered
                         */
                        if(RxSigGrpConstPtr->DataInvalid_Indication_Cbk != NULL_PTR)
                        {
                            RxSigGrpConstPtr->DataInvalid_Indication_Cbk();
                        }
                    }
                }
#endif /* #ifdef COM_RxSigGrpInvalidNotify */
                /* [SWS_Com_00680] SignalGroup is invalid, so no filtering process has to be done for this signal group
                 * Break out of the for loop, as no more processing of group signals is required  */
                breakFromLoop_b = COM_TRUE;
            }
            else
#endif /* #if defined(COM_RxSigGrpInvalid) */
            {
#ifdef COM_RxFilters

                /* Proceed only if the GroupSignal is configured with a filter */
                if ( filterAlgo_u8 != COM_NOTCONFIGURED )
                {
                    /* The Groupsignal is valid, hence perform filtering */
                    /* Get The Return value of the Filter which need not be returned if signal is invalid */
                    /* The last parameter is Information from where the call to Com_Filter happens */
                    /* NOTE on last parameter:
                    * 1.Currently the values for the parameter callContext_u8 are COM_TRUE/COM_FALSE
                    * 2.It is used only for filter ONE_EVERYN */
#if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined (COM_RxSigGrpUpdateTimeout))
                    if(!((Com_GetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields) == COM_TRUE) &&
                         (COM_MASKED_NEW_DIFFERS_MASKED_OLD == filterAlgo_u8)))
#endif /* #if defined (COM_F_MASKEDNEWDIFFERSOLD) && (defined (COM_RxIPduTimeout) || defined (COM_RxSigGrpUpdateTimeout)) */
                    {
                        VAR(boolean, AUTOMATIC)  filterVal_b;

                        /* Call the Com_Filter API only if the conditions meet:
                         * 1. If the GroupSignal is not invalidated
                         * 2. This SignalGroup was not timed out */
                        filterVal_b = Com_Filter((uint32)RxNewVal_GrpSig,filterAlgo_u8,RxGrpSigConstPtr->Filter_Index,COM_TRUE);

                        if(COM_TRUE != filterVal_b)
                        {
                            /* [SWS_Com_00836]: Break out of the for loop, as no more processing of group signals is
                             * required And discard the whole signal group */
                            ValidateSigGrp_u8 = COM_RESET;
                            /* Even the SignalGroup notification shall not be invoked */
                            Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr ->rxSigGrpRAMFields,COM_FALSE);
                            breakFromLoop_b = COM_TRUE;
                        }
                    }
                }
#endif /* #ifdef COM_RxFilters   */

            }
        }

        RxGrpSigConstPtr++;
    }

#if (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)) && (defined (COM_RxIPduTimeout) || defined (COM_RxSigGrpUpdateTimeout))
    /* Reset the DM filtering flag only if it was set during the previous timeout session */
    if(ValidateSigGrp_u8 != COM_RESET)
    {
        /* Resetting this flag which is maintained at SignalGroup level,
        * for further reception of the signal, if Rx deadline monitoring timer elapses,
        * again this flag shall be set in Com_MainFunctionRx()
        * This flag is resetted after processing all the ComGroupSignal inside this SignalGroup */
        Com_SetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_FALSE);
    }
#endif /* #if (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)) && (defined (COM_RxIPduTimeout) || defined (COM_RxSigGrpUpdateTimeout)) */

    return(ValidateSigGrp_u8);

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #if defined(COM_RX_SIGNALGROUP) && (defined(COM_RxSigGrpInvalid) || defined (COM_RxFilters)) */

