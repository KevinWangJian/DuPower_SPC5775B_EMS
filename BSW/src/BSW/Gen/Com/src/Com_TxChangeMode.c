

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_TxChangeMode
 Syntax           : void Com_TxChangeMode(Com_IpduIdType TxIpduId)
 Description      : Internal function used for Transmission Mode Selector
 Parameter        : TxIpduId
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void,COM_CODE) Com_TxChangeMode(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId)
{
    Com_TxIpduConstPtrType TxIPduConstPtr; /* Local pointer to hold the address of Tx ipdu static configuration */
    VAR(uint8, AUTOMATIC) LatestTransMode_u8;
    VAR(boolean, AUTOMATIC) Mode;
    Com_TxIpduRamPtrType TxIpduRamPtr; /* Local pointer to hold the address of the Tx ipdu status structure */

#ifdef COM_TxFilters
    Com_TxSigConstPtrType TxSigConstPtr; /* Local pointer to Tx signal static configuration */
    Com_TxSigRamPtrType TxSigRamPtr;     /* Local pointer to Tx signal status structure */
    VAR(uint16_least, AUTOMATIC) Index_ui;
    VAR(Com_SigMaxType, AUTOMATIC) TxNewVal;
    VAR(boolean, AUTOMATIC) Filter_Val;
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;
    VAR(uint8, AUTOMATIC) FilterAlg_u8;  /* Filter type */
    VAR(uint8, AUTOMATIC) Type;   /* Signal Type */
#ifdef COM_TX_SIGNALGROUP
    Com_TxSigGrpConstPtrType    TxSigGrpConstPtr;     /* Local pointer to Tx SignalGroup static configuration */
    Com_TxGrpSigConstPtrType    TxGrpSigConstPtr;    /* Local pointer to Tx GroupSignal static configuration */
    VAR(uint16_least, AUTOMATIC) GrpSig_Index_ui;
    VAR(Com_TxGrpSigBuffIndexType, AUTOMATIC) GrpSigBuff_Index;
    Com_TxGrpSigRamPtrType TxGrpSigRamPtr;  /* Local pointer to Tx GroupSignal status structure */
#ifdef COM_TX_SIGNALGROUP_ARRAY
    VAR(boolean, AUTOMATIC) ConstIsSigGrpOfArrayType_b;
#endif
#endif /* #ifdef COM_TX_SIGNALGROUP */
#endif /* #ifdef COM_TxFilters */

    /* Initialise Mode as TRUE, it could be the most probable case */
    Mode = COM_TRUE;

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxIpduId);
    TxIpduRamPtr->Com_TMSTrueCounter_u8 = 0;


#ifdef COM_TxFilters
    TxNewVal = 0;
#endif
    /* Call Filter for all signals and Group Signals in the IPDU */
#ifdef COM_TxFilters
    /* Only the first byte of txIPduFields is needed */
    ConstByteValue_u8 = (uint8)TxIPduConstPtr->txIPduFields;
    /* Check if Transmission Mode switch is possible by signal filter mechanism */
    /* if (TxIPduConstPtr->txIPduFields.FilterEvalReq != 0) */
    if (Com_GetValue(TXIPDU,_FILTEREVALREQ,ConstByteValue_u8) != COM_FALSE )
    {
        /* First check for the Signals */

        TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);

        TxSigRamPtr = &COM_GET_TXSIGNALFLAG(TxIPduConstPtr->TxSigId_Index);
        for(Index_ui = TxIPduConstPtr->No_Of_Sig_Ref; Index_ui != 0u; Index_ui--)
        {
            ConstByteValue_u8 = TxSigConstPtr->txSignalFields;
            /* FilterAlg_u8 = TxSigConstPtr->txSignalFields.FilterAlgorithm; */
            FilterAlg_u8 = Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u8);

            /* Check if the filter is configured, NOTE: If filter is not configured, then the Value will be COM_ALWAYS
                in the configuration and this means that the signal will not contribute to TMS calculation */
            if(FilterAlg_u8 != (uint8)COM_NOTCONFIGURED)
            {
                ConstByteValue_u8 = TxSigConstPtr->General;
                /*     Type = TxSigConstPtr->General.Type; */
                Type = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);

                if(Type != (uint8)COM_UINT8_N)
                {
                    /* TxNewVal = Com_UnpackSignal(TxSigConstPtr->General.Endianess,TxSigConstPtr->Bit_Pos,TxSigConstPtr->BitSize,
                            TxIPduConstPtr ->BuffPtr); */
                    TxNewVal = Com_UnpackSignal( Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8),
                                                 TxSigConstPtr->Bit_Pos,
                                                 TxSigConstPtr->BitSize,
                                                 TxIPduConstPtr ->BuffPtr );
                }
                else
                {
                    TxNewVal = 0;
                    /* This variable will not be checked in Com_Filter, as the Algorithm for Uint8[n] will be only
                     * ALWAYS or NEVER */
                }
                /* The last parameter is Information from where the call to Com_Filter happens */
                /* NOTE on last parameter:
                 * 1.Currently the values for the parameter CallContext_b are COM_TRUE/COM_FALSE
                 * 2.It is used only for filter ONE_EVERYN */
                Filter_Val = Com_Filter((uint32)TxNewVal,FilterAlg_u8, TxSigConstPtr->Filter_Index, COM_FALSE);

                if (Filter_Val != COM_FALSE)
                {
                    /* Increment TRUE counter , based on filter condition */
                    TxIpduRamPtr ->Com_TMSTrueCounter_u8++;
                }
                /* Store the latest filter state of the signal */
                /* TxSigRamPtr->txSigRAMFields.SigTxChangeMode = Filter_Val */
                Com_SetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields,Filter_Val);
            }
            TxSigConstPtr++;
            TxSigRamPtr++ ;
        }

#ifdef COM_TX_SIGNALGROUP

        /* Secondly check for Group Signals */
        /* For Selection of the transmission mode the Group signals shall be treated as normal signals */

        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);

        for(Index_ui = TxIPduConstPtr->No_Of_SigGrp_Ref; Index_ui!= 0u; Index_ui--)
        {

# ifdef COM_TX_SIGNALGROUP_ARRAY
            ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
# endif
            /* if (TxSigGrpConstPtr->txSignalGrpFields.FilterEvalReq != 0) */
            if(Com_GetValue(TXSIGGRP,_FILTEREVALREQ,TxSigGrpConstPtr->txSignalGrpFields) != COM_FALSE)
            {
                /* Now check for each Group Signal of this signal group */
                TxGrpSigRamPtr = &COM_GET_TXGRPSIGFLAG(TxSigGrpConstPtr->FirstGrpSig_Index);

                TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);

                for(GrpSig_Index_ui = TxSigGrpConstPtr->No_Of_GrpSig; GrpSig_Index_ui != 0u; GrpSig_Index_ui--)
                {
                    /* Check if the filter is configured, NOTE: If filter is not configured,
                    then the Value will be COM_ALWAYS in the configuration */
                    if(TxGrpSigConstPtr->Filter_Algo != (uint8)COM_NOTCONFIGURED)
                    {
                        ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
                        /* Type = TxGrpSigConstPtr->txGrpSigFields.Type; */
                        Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
                        if(Type != (uint8)COM_UINT8_N)
                        {
# ifdef COM_TX_SIGNALGROUP_ARRAY
                            if ( ConstIsSigGrpOfArrayType_b )
                            {
                                /* Unpack GroupSignal data from SignalGroup with ArrayAccess */
                                /* MR12 RULE 10.3 VIOLATION: Endianess is just 1-bit wide, hence the warning.
                                 * So suppressed the warning. */
                                TxNewVal = Com_UnpackSignal( Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8),
                                                             TxGrpSigConstPtr->Bit_Pos,
                                                             TxGrpSigConstPtr->BitSize,
                                                             TxIPduConstPtr->BuffPtr );

                            }
                            else
# endif /* # ifdef COM_TX_SIGNALGROUP_ARRAY */
                            {
                                GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;

                                switch(Type >> 1u)
                                {
                                case 0x00u:
                                    /* UINT08 signal */
                                    TxNewVal = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU8_BUFF(GrpSigBuff_Index);
                                    break;

                                case 0x01u:
                                    /* UINT16 signal */
                                    TxNewVal = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU16_BUFF(GrpSigBuff_Index);
                                    break;

                                case 0x02u:
                                    /* UINT32 signal */
                                    TxNewVal = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU32_BUFF(GrpSigBuff_Index);
                                    break;

#ifdef COM_TXGRPSIG_INT64
                                case 0x08u:
                                    /* UINT64 signal */
                                    TxNewVal = COM_GET_TXGRPSIGTYPEU64_BUFF(GrpSigBuff_Index);
                                    break;
#endif /* #ifdef COM_TXGRPSIG_INT64 */

                                case 0x03u:
                                    /*Boolean Signal*/
                                    TxNewVal =  (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU8_BUFF(GrpSigBuff_Index);
                                    break;

                                default:
                                /**
                                 * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal
                                 * types are allowed to be configured, hence default case is intentionally left empty.
                                 */
                                    break;

                                }
                            }
                        }
                        else
                        {
                            /* For GroupSignal of array types(UINT8[n]), signal values are not used for
                             * filter(ALWAYS, NEVER, ONE_EVERY_N) evaluation */
                            TxNewVal = 0u;
                        }
                        /* The last parameter is Information from where the call to Com_Filter happens */
                        /* NOTE on last parameter:
                         * 1.Currently the values for the parameter CallContext_b are COM_TRUE/COM_FALSE
                         * 2.It is used only for filter ONE_EVERYN */
                        Filter_Val = Com_Filter((uint32)TxNewVal, TxGrpSigConstPtr->Filter_Algo,
                                                TxGrpSigConstPtr->Filter_Index,COM_FALSE);

                        if (Filter_Val != COM_FALSE)
                        {
                            /* Increment TRUE counter , based on filter condition */
                            TxIpduRamPtr ->Com_TMSTrueCounter_u8++;
                        }
                        /* Store the latest filter state of the signal */
                        /* TxGrpSigRamPtr->txGrpSigRAMFields.SigTxChangeMode = Filter_Val */
                        Com_SetRamValue(TXGRPSIG,_SIGCHNGMODE,TxGrpSigRamPtr->txGrpSigRAMFields,Filter_Val);
                    }
                    TxGrpSigConstPtr++;
                    TxGrpSigRamPtr++;
                }
            }

            TxSigGrpConstPtr++;
        }
#endif /*COM_TX_SIGNALGROUP*/
        if (TxIpduRamPtr ->Com_TMSTrueCounter_u8 != 0)
        {
            /* If any signal/signal group evaluates filter as TRUE, then TM TRUE is selected for IPDU */
            Mode = COM_TRUE;
        }
        else
        {
            /* If all signal/signal group evaluates filter as FALSE, then TM FALSE is selected for IPDU */
            Mode = COM_FALSE;
        }
    }
#endif /*COM_TxFilters*/

    /* If a change of the TMS causes a change of the transmission mode for one I-PDU, the timer for the cycle
    time of the periodic and the Mixed Tx Mode shall be retstarted */

    /* Update the TxModeState with the Mode */
    /* TxIpduRamPtr->Com_TransMode.TxModeState = Mode */
    Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);
    /* Update the CurrentTxModePtr */
    /*Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,TxIPduConstPtr->txIPduFields.TMSCalclation,Mode)*/
    Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,Com_GetValue(TXIPDU,_TMS,TxIPduConstPtr->txIPduFields),Mode);

    /* Update the Com_LatestTransMode[TxIpduId] */
    /* TxIpduRamPtr->Com_TransMode.LatestTransMode = TxIpduRamPtr->CurrentTxModePtr->Mode */
    Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);
    LatestTransMode_u8 = TxIpduRamPtr->CurrentTxModePtr->Mode;

    /* Reset the timers */
    /* This check is equivalent to
     * if(((LatestTransMode_u8 == COM_TXMODE_PERIODIC) ||
     *    (LatestTransMode_u8 == COM_TXMODE_MIXED)) )
     */
    if( 0u != ( LatestTransMode_u8 & COM_TXMODE_MIXED ) )
    {
        /* The function may be interrupted by Com_MainFunctionTx().This will lead to inconsistant data in
         * Com_MainFunctionTx(), So Interrupt is locked here. */
        /* FC_VariationPoint_START */
#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION
        TxIpduRamPtr->Com_Tick_Tx = COM_getTxIPduCyclePeriod((PduIdType)TxIpduId);
#else
        /* FC_VariationPoint_END */
        TxIpduRamPtr ->Com_Tick_Tx = Com_UpdateComTickTx_TMS(TxIpduRamPtr->CurrentTxModePtr);
        /* FC_VariationPoint_START */
#endif /* #ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION */
        /* FC_VariationPoint_END */
        /*Below Initialize is done if Com_TxChangeMode() is called by Ipdu_GroupStart()*/
        TxIpduRamPtr ->Com_n_Tick_Tx = 0;
        /*This means there is no n Transmission, This will be updated in Com_SendSignal()and Com_SendSignalGroup()*/
        TxIpduRamPtr ->Com_n = 0;
        /* FC_VariationPoint_START */
#ifdef COM_MIXEDPHASESHIFT
        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif /* #ifdef COM_MIXEDPHASESHIFT */
        /* FC_VariationPoint_END */

    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_SigTxChangeMode
 Syntax           : boolean Com_SigTxChangeMode(Com_IpduIdType TxIpduId, uint16 SignalId, uint32 TxNewVal, boolean IsSignalGroup)
 Description      : This function evaluates the current TMS of the IPDU, based on the corresponding signal or signal group which is updated.
 Parameter        : TxIpduId -> Id of the Tx ipdu
                  : SignalId -> Id of the signal
                  : TxNewVal -> New signal value
                  : IsSignalGroup -> boolean to check whether it is an SignalGroup or not
 Return value     : COM_TRUE/COM_FALSE
 ***************************************************************************************************/
#ifdef COM_TxFilters
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_SigTxChangeMode(VAR(Com_IpduIdType, AUTOMATIC) TxIpduId,VAR(uint16, AUTOMATIC) SignalId,VAR(Com_SigMaxType, AUTOMATIC) TxNewVal,VAR(boolean, AUTOMATIC) IsSignalGroup )
{
    Com_TxIpduConstPtrType  TxIPduConstPtr;    /* Local pointer to Tx ipdu   static  configuration */
    Com_TxIpduRamPtrType    TxIpduRamPtr;      /* Local pointer to Tx ipdu   dynamic configuration */
    Com_TxSigConstPtrType   TxSigConstPtr;     /* Local pointer to Tx signal static  configuration */
    Com_TxSigRamPtrType     TxSigRamPtr;       /* Local pointer to Tx signal dynamic configuration */
    VAR(uint8, AUTOMATIC)   ConstByteValue_u8;
    VAR(boolean, AUTOMATIC) sig_TMSState;
    VAR(boolean, AUTOMATIC) ReturnValue;
    VAR(boolean, AUTOMATIC) Mode;

#ifdef COM_TX_SIGNALGROUP
    Com_TxGrpSigRamPtrType   TxGrpSigRamPtr;    /* Local pointer to Tx GroupSignal dynamic configuration */
    Com_TxSigGrpConstPtrType TxSigGrpConstPtr;  /* Local pointer to Tx SignalGroup static configuration  */
    Com_TxGrpSigConstPtrType TxGrpSigConstPtr;  /* Local pointer to Tx GroupSignal static configuration  */
    VAR(Com_SigMaxType, AUTOMATIC) TxNewVal_GrpSig;
    VAR(Com_TxGrpSigBuffIndexType, AUTOMATIC) GrpSigBuff_Index;
    VAR(uint16_least, AUTOMATIC) GrpSig_Index_ui;
    VAR(uint8, AUTOMATIC)    Type;
#endif /* #ifdef COM_TX_SIGNALGROUP */

    Mode        = COM_FALSE;
    ReturnValue = COM_FALSE;
#ifdef COM_TX_SIGNALGROUP
    TxNewVal_GrpSig = (Com_SigMaxType)0;
#endif

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxIpduId);

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxIpduId);

    /* Call Filter for all signals and Group Signals in the IPDU */
    SchM_Enter_Com_TxIpduProtArea(SIGTXCHANGEMODE);
#ifdef COM_TX_SIGNALGROUP
    if(IsSignalGroup == COM_TRUE)
    {
# ifdef COM_TX_SIGNALGROUP_ARRAY
        boolean ConstIsSigGrpOfArrayType_b;
#endif
        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalId);

        /*Get the Bit field Byte value*/
        TxGrpSigRamPtr = &COM_GET_TXGRPSIGFLAG(TxSigGrpConstPtr->FirstGrpSig_Index);

        TxGrpSigConstPtr = COM_GET_TXGRPSIG_CONSTDATA(TxSigGrpConstPtr->FirstGrpSig_Index);
# ifdef COM_TX_SIGNALGROUP_ARRAY
        ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
# endif
        for(GrpSig_Index_ui = TxSigGrpConstPtr->No_Of_GrpSig; GrpSig_Index_ui != 0u; GrpSig_Index_ui-- )
        {
            /* Check if the filter is configured, NOTE: If filter is not configured,
               then the Value will be COM_ALWAYS in the configuration */
            if((TxGrpSigConstPtr->Filter_Algo != (uint8)COM_NOTCONFIGURED) && (TxGrpSigConstPtr->Filter_Algo > COM_NEVER))
            {
                ConstByteValue_u8 = TxGrpSigConstPtr->txGrpSigFields;
                /* Type = TxGrpSigConstPtr->txGrpSigFields.Type; */
                Type = Com_GetValue(TXGRPSIG,_TYPE,ConstByteValue_u8);
                if(Type != (uint8)COM_UINT8_N)
                {
# ifdef COM_TX_SIGNALGROUP_ARRAY
                    if ( ConstIsSigGrpOfArrayType_b )
                    {
                        /* Unpack GroupSignal data from SignalGroup with ArrayAccess */
                        TxNewVal_GrpSig = Com_UnpackSignal( Com_GetValue(TXGRPSIG,_ENDIANESS,ConstByteValue_u8),
                                                            TxGrpSigConstPtr->Bit_Pos,
                                                            TxGrpSigConstPtr->BitSize,
                                                            TxIPduConstPtr->BuffPtr );

                    }
                    else
# endif /* # ifdef COM_TX_SIGNALGROUP_ARRAY */
                    {
                        GrpSigBuff_Index = TxGrpSigConstPtr->TxGrpSigBuff_Index;

                        switch(Type >> 1u)
                        {
                        case 0x00u:
                            /* UINT08 signal */
                            TxNewVal_GrpSig = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU8_BUFF(GrpSigBuff_Index);
                            break;

                        case 0x01u:
                            /* UINT16 signal */
                            TxNewVal_GrpSig = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU16_BUFF(GrpSigBuff_Index);
                            break;

                        case 0x02u:
                            /* UINT32 signal */
                            TxNewVal_GrpSig = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU32_BUFF(GrpSigBuff_Index);
                            break;

#ifdef COM_TXGRPSIG_INT64
                        case 0x08u:
                            /* UINT64 signal */
                            TxNewVal_GrpSig = COM_GET_TXGRPSIGTYPEU64_BUFF(GrpSigBuff_Index);
                            break;
#endif /* #ifdef COM_TXGRPSIG_INT64 */

                        case 0x03u:
                            /*Boolean Signal*/
                            TxNewVal_GrpSig = (Com_SigMaxType)COM_GET_TXGRPSIGTYPEU8_BUFF(GrpSigBuff_Index);
                            break;

                        default:
                            /**
                             * Default case is mandatory in switch syntax. Moreover only AUTOSAR Com defined signal
                             * types are allowed to be configured, hence default case is intentionally left empty.
                             */
                            break;
                        }
                    }
                }
                else
                {
                    /* For GroupSignal of array types(UINT8[n]), signal values are not used for
                     * filter(ALWAYS, NEVER, ONE_EVERY_N) evaluation */
                    TxNewVal_GrpSig = 0u;
                }

                /* The last parameter is Information from where the call to Com_Filter happens */
                /* NOTE on last parameter:
                 * 1.Currently the values for the parameter CallContext_b are COM_TRUE/COM_FALSE
                 * 2.It is used only for filter ONE_EVERYN */
                sig_TMSState = Com_Filter((uint32)TxNewVal_GrpSig, TxGrpSigConstPtr->Filter_Algo,
                                          TxGrpSigConstPtr->Filter_Index,COM_TRUE);

                /* Update TMS TRUE counter , only if filter state of the signal changes.
                 * Otherwise, TMS TRUE counter value remains unchanged.
                 */
                /* if(TxGrpSigRamPtr->txGrpSigRAMFields.SigTxChangeMode != sig_TMSState) */
                if (Com_GetRamValue(TXGRPSIG,_SIGCHNGMODE,TxGrpSigRamPtr->txGrpSigRAMFields)!= sig_TMSState)
                {
                    if (sig_TMSState != COM_FALSE)
                    {
                        /* Signal has changed from FALSE to TRUE, hence increment TMS TRUE counter */
                        TxIpduRamPtr->Com_TMSTrueCounter_u8++;
                    }
                    else
                    {
                        /* Signal has changed from TRUE to FALSE, hence decrement TMS TRUE counter */
                        TxIpduRamPtr->Com_TMSTrueCounter_u8--;
                    }
                    /* TxGrpSigRamPtr->txGrpSigRAMFields.SigTxChangeMode = sig_TMSState */
                    Com_SetRamValue(TXGRPSIG,_SIGCHNGMODE,TxGrpSigRamPtr->txGrpSigRAMFields,sig_TMSState);
                }
            }
            TxGrpSigConstPtr++;
            TxGrpSigRamPtr++;
        }
    }
    else
#else
    (void)IsSignalGroup; /* Parameter will be unused in this case */
#endif /*COM_TX_SIGNALGROUP*/
    {
        TxSigRamPtr = &COM_GET_TXSIGNALFLAG(SignalId);

        TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(SignalId);

        ConstByteValue_u8 = TxSigConstPtr->txSignalFields;
        /* if(TxSigConstPtr->txSignalFields.FilterAlgorithm > (uint8)COM_NEVER) */
        if(Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u8) > (uint8)COM_NEVER)
        {
            /* Evaluate current filter state of the signal */
            /* The last parameter is Information from where the call to Com_Filter happens */
            /* NOTE on last parameter:
             * 1.Currently the values for the parameter CallContext_b are COM_TRUE/COM_FALSE
             * 2.It is used only for filter ONE_EVERYN */
            /*     sig_TMSState = Com_Filter(TxNewVal, TxSigConstPtr->txSignalFields.FilterAlgorithm,
                    TxSigConstPtr->Filter_Index,COM_TRUE); */
            sig_TMSState = Com_Filter((uint32)TxNewVal, Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u8),
                                      TxSigConstPtr->Filter_Index,COM_TRUE);
            /* Update TMS TRUE counter , only if filter state of the signal changes.
             * Otherwise, TMS TRUE counter value remains unchanged.
             */
            /* if(TxSigRamPtr->txSigRAMFields.SigTxChangeMode != sig_TMSState) */
            if (Com_GetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields)!= sig_TMSState)
            {
                if (sig_TMSState != COM_FALSE)
                {
                    /* Signal has changed from FALSE to TRUE, hence increment TMS TRUE counter */
                    TxIpduRamPtr ->Com_TMSTrueCounter_u8++;
                }
                else
                {
                    /* Signal has changed from TRUE to FALSE, hence decrement TMS TRUE counter */
                    TxIpduRamPtr ->Com_TMSTrueCounter_u8--;
                }
                /* Update the latest filter state of the signal, if the signal filter state changes */
                /* TxSigRamPtr->txSigRAMFields.SigTxChangeMode = sig_TMSState */
                Com_SetRamValue(TXSIG,_SIGCHNGMODE,TxSigRamPtr->txSigRAMFields,sig_TMSState);
            }
        }
    }

    if (TxIpduRamPtr ->Com_TMSTrueCounter_u8 != 0)
    {
        /* After evaluating filter for current signal/signal group, check if one of the signal/signal group filter
         * state is TRUE
         * Otherwise init value for Mode ie COM_FALSE is used
         */
        Mode = COM_TRUE;
    }

    /* if(TxIpduRamPtr->Com_TransMode.TxModeState != Mode) */
    /*If there is a Mode change detected for the IPdu */
    if((Com_GetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode) != Mode))
    {
        ReturnValue = COM_TRUE;
        /* Update the Com_TxModeState with the Mode */
        /* TxIpduRamPtr->Com_TransMode.TxModeState = Mode */
        Com_SetRamValue(TXIPDU,_TXMODESTATE,TxIpduRamPtr->Com_TransMode,Mode);
        /* Update the CurrentTxModePtr */
        /*Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,TxIPduConstPtr->txIPduFields.TMSCalclation,Mode)*/
        Com_SetCurrentTxModePtr(TxIpduRamPtr,TxIPduConstPtr,Com_GetValue(TXIPDU,_TMS,TxIPduConstPtr->txIPduFields),Mode);

        /* TxIpduRamPtr->Com_TransMode.LatestTransMode = TxIpduRamPtr->CurrentTxModePtr->Mode */
        Com_SetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->Mode);

        /* Note: Timer update because of mode change happens in Com_sendIpdu */
        /* FC_VariationPoint_START */
#ifdef COM_MIXEDPHASESHIFT
        /* Initialise MixedPhaseShift state, when IPdu tx mode is calculated in Com_IPduGroupStart() */
        Com_SetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode,TxIpduRamPtr->CurrentTxModePtr->MixedPhaseShift);
#endif /* #ifdef COM_MIXEDPHASESHIFT */
        /* FC_VariationPoint_END */
    }
    SchM_Exit_Com_TxIpduProtArea(SIGTXCHANGEMODE);
    return(ReturnValue);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #ifdef COM_TxFilters */


