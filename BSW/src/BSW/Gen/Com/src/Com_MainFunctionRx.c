

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"

/**************************************************************************************************/
/* defines                                                                                        */
/**************************************************************************************************/

#if (defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))
#define COM_LocalVarRequired
#endif

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_MainFunctionRx
 Syntax           : void Com_MainFunctionRx(void)
 Description      : Service to perform the processing of the AUTOSAR COM receive processing that
                    are not directly initiated by the calls from the RTE and PDU-R.
 Parameter        : void
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_MainFunctionRx(void)
{

    Com_RxIpduConstPtrType RxIPduConstPtr; /* Local pointer holds the address of Rx ipdu static configuration */
    Com_RxIpduRamPtrType RxIpduRamPtr;     /* Local pointer holds the address of Rx ipdu status structure */
#if defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout)
    Com_RxSigConstPtrType         RxSigConstPtr;
#endif /* #if defined (COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout) */

#if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout))
    P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST) SigTimeOutConfigPtr;
    P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) SigTimeOutTicksPtr;
    VAR(uint16_least, AUTOMATIC) NoOfSigOrSigGrp_ui;
#endif/* #if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)) */

#if defined(COM_RX_SIGNALGROUP) && ( defined(COM_RxIPduTimeout) || defined(COM_RxSigGrpUpdateTimeout) )
    Com_RxSigGrpConstPtrType RxSigGrpConstPtr;
#endif /* #if defined(COM_RX_SIGNALGROUP) && ( defined(COM_RxIPduTimeout) || defined(COM_RxSigGrpUpdateTimeout) ) */

    VAR(uint16_least, AUTOMATIC) Idx_ui;
#ifdef COM_LocalVarRequired
    VAR(uint16_least, AUTOMATIC) Idx_Sig_ui;
#endif
#if defined COM_SIGNALGATEWAY || defined COM_SIGNALGROUPGATEWAY
    VAR(uint16_least, AUTOMATIC) l_NumOfGwSignalUpdtd_ui;
#endif /* #if defined COM_SIGNALGATEWAY || defined COM_SIGNALGROUPGATEWAY */
#ifdef COM_RxIPduTimeoutNotify
    VAR(boolean, AUTOMATIC) CallTONotify_b;

    /* Initialise the CallTONotify_b flag to false */
    CallTONotify_b = COM_FALSE;
#endif /* #ifdef COM_RxIPduTimeoutNotify */


    /* Start: Det */

    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_MainFunctionRx, COM_E_UNINIT)

    /* End: Det */

    if(Com_Uninit_Flag == COM_INIT)
    {
        RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(0);
        RxIpduRamPtr = &COM_GET_RXPDURAM_S(0);

        /* Note: Here dont take care of MDT as it is mentioned in Page number 54, of V2.1.5 */
        for(Idx_ui = 0; Idx_ui < COM_GET_NUM_RX_IPDU; Idx_ui++)
        {
#if defined COM_SIGNALGATEWAY || defined COM_SIGNALGROUPGATEWAY
            l_NumOfGwSignalUpdtd_ui = 0;
#endif /* #if defined COM_SIGNALGATEWAY || defined COM_SIGNALGROUPGATEWAY */
            /*Check for Ipdu Group is Started/Stopped*/
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
             * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
             * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
             * Hence the warning is suppressed. */
            if(COM_CheckRxIPduStatus(Idx_ui))
            {
                VAR(boolean,AUTOMATIC)  IPduSigProcessing_b;
#if defined (COM_RxIPduDeferredProcessing) || defined (COM_RxIPduTimeout)
                VAR(boolean,AUTOMATIC)  RxIndication_b;
                /* RxIndication_b = RxIPduRamPtr ->RxFlags.RxIndicationFlag */
                RxIndication_b = Com_GetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr ->RxFlags);
#endif
                IPduSigProcessing_b = Com_GetValue(RXIPDU,_SIGPROC,RxIPduConstPtr->rxIPduFields);
                /* if(RxIPduConstPtr->rxIPduFields.Signal_Processing == COM_IMMEDIATE) */
                if (IPduSigProcessing_b == COM_IMMEDIATE)
                {
                    /* For an Ipdu with Immediate Signal processing, the flag will be reset here */
                    /* RxIPduRamPtr ->RxFlags.RxIndicationFlag = COM_RESET */
                    Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr ->RxFlags,COM_FALSE);
                }
#ifdef COM_RxIPduDeferredProcessing
                /* Check if the IPdu has configured signal processing as DEFERRED and
                 * check for the reception of the IPdu
                 */
                /* if((RxIndication_b!= COM_RESET)&&(RxIPduConstPtr->rxIPduFields.Signal_Processing == COM_IMMEDIATE)) */
                if ((RxIndication_b != COM_FALSE) && (IPduSigProcessing_b != COM_IMMEDIATE))
                {

                    PduInfoType pduInfoPtr_l;
                    /* Copy the data from IPdu buffer to another buffer
                     * This is required for data consistency as it is possible that IPdu buffer is updated
                     * by Com_RxIndication(), when it is being processed
                     * Since all the IPdus are processed sequentially, only one common buffer is sufficient
                     */
                    SchM_Enter_Com_RxPduBuffer();
                    Com_ByteCopy(COM_GET_DEFERREDBUFFER, RxIPduConstPtr->BuffPtr,RxIpduRamPtr->RxIPduLength);
                    /*Reset the flag after checking the flag
                     * In case of defered processing, the flag should be reset under protection */
                    /* RxIPduRamPtr ->RxFlags.RxIndicationFlag = COM_RESET */
                    Com_SetRamValue(RXIPDU,_INDICATION,RxIpduRamPtr ->RxFlags,COM_FALSE);
                    pduInfoPtr_l.SduDataPtr = COM_GET_DEFERREDBUFFER;
                    pduInfoPtr_l.SduLength = RxIpduRamPtr->RxIPduLength;
                    SchM_Exit_Com_RxPduBuffer();
                    Com_ProcessRxIPdu((PduIdType)Idx_ui, &pduInfoPtr_l);
                }
#endif /* #ifdef COM_RxIPduDeferredProcessing */

                /* Check if deadline monitoring is enabled for IpduGroup & configured for IPdu. */
                if(COM_CheckRxIPduDMStatus(Idx_ui))
                {
#if ((defined(COM_RxIPduTimeout) || defined(COM_RxSigUpdateTimeout)) && (defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))))
                    Com_RxSigRamPtrType RxSigRamPtr;
#endif

#if (defined (COM_RX_SIGNALGROUP) && (defined(COM_RxIPduTimeout) || defined(COM_RxSigGrpUpdateTimeout)) && (defined (COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))))
                    Com_RxSigGrpRamPtrType RxSigGrpRamPtr;
#endif

#ifdef COM_RxIPduTimeout
                    VAR(uint16, AUTOMATIC) rxTimeOutFact_u16;
                    /* FC_VariationPoint_START */
#ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION
                    rxTimeOutFact_u16 = Com_GetRxIPduTimeoutCalibration((PduIdType)Idx_ui);
#else
                    /* FC_VariationPoint_END */
                    rxTimeOutFact_u16 = RxIPduConstPtr->Timeout_Fact;
                    /* FC_VariationPoint_START */
#endif /* #ifdef COM_RXPDU_TIMEOUT_VIA_CALIBRATION */
                    /* FC_VariationPoint_END */

                    if(RxIndication_b != COM_FALSE)
                    {
                        /* Ipdu timeout factor is reloaded on reception of IPdu */
#if (COM_ENABLE_JITTERFLITER == STD_ON)
                        /* CC requirements:
                         * An extra cycle is added to the timeout value after a PDU has been received incase filter is ON
                         * Provides a chance incase of jitter( extra cycle is added in normal case and hence
                         * if JITTERFILTER is enabled extra two cycles are added)
                         */
                        RxIpduRamPtr->RxTicks_u16 = (rxTimeOutFact_u16 == 0)? COM_RXTIMER_MAX :
                        (rxTimeOutFact_u16 + 2u);
#else
                        /* Extra cycle is added to prevent early timeouts */
                        RxIpduRamPtr->RxTicks_u16 = (rxTimeOutFact_u16 == 0)? COM_RXTIMER_MAX :
                        (rxTimeOutFact_u16 + 1u);
#endif /* #ifdef COM_ENABLE_JITTERFLITER */
                    }
                    /* If timeout is disabled for an IPdu (either ComTimeOutFactor or ComFirstTimeOutFactor) then
                     * RxTicks will be loaded with COM_RXTIMER_MAX(0xFFFF)
                     * Reduce Tick Timeout
                     */
                    SchM_Enter_Com_RxSigBuff(MAINFUNCTIONRX);
                    if((RxIpduRamPtr->RxTicks_u16 != 0) && (RxIpduRamPtr->RxTicks_u16 != COM_RXTIMER_MAX))
                        /*Not to go less than ZERO */
                    {
                        --RxIpduRamPtr->RxTicks_u16;
                    }
                    /* IPDU has timed out */
                    if (RxIpduRamPtr->RxTicks_u16 == 0x00)
                    {
                        /* Reload the timer upon time out */
                        RxIpduRamPtr->RxTicks_u16 = rxTimeOutFact_u16;
                        /* Set the signal flags to indicate timeout
                         * When the signal is read using function Com_ReceiveSignal() , if signal is timed out then
                         * either previous value or init value is returned based on the action configured
                         */
                        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

#if defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
                        RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
#endif
                        for (Idx_Sig_ui = RxIPduConstPtr->No_Of_Sig_Ref; Idx_Sig_ui !=0u; Idx_Sig_ui--)
                        {
                            /* Signal with update-bit have seperate timeout handling
                             * Signals without update-bit are marked as timed out, when IPdu times out.
                             */
#ifdef COM_RxSigUpdateBit
                            /* if(RxSigConstPtr->General.UpdBitConf != COM_FALSE) */
                            if(Com_GetValue(GEN,_UPDBITCONF,RxSigConstPtr->General) == COM_FALSE)
#endif
                            {
                                /* Now check if the RxTimeout Substitution is = REPLACE */
                                /*if(RxSigConstPtr->rxSignalFields.DataTimeoutType)*/
                                if(Com_GetValue(RXSIG,_TOACTION,RxSigConstPtr->rxSignalFields))
                                {
                                    VAR(Com_SigMaxType, AUTOMATIC) RxSigVal;
#if (defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP ))
                                    VAR(uint8,AUTOMATIC)           Type;

                                    Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif
                                    RxSigVal = (Com_SigMaxType)RxSigConstPtr->Init_Val;

                                    /* FC_VariationPoint_START */
#ifdef COM_RXSIG_FLOAT64SUPP
                                    /* if(RxSigConstPtr->General.Type == COM_FLOAT64) */
                                    if(Type == COM_FLOAT64)
                                    {
                                        /* For float64 signals, RxSigConstPtr->Init_Val holds index to float array holding init values.*/
                                        COM_GET_SIGTYPEFLOAT64_BUFF(RxSigConstPtr->SigBuff_Index) = Com_getfloat64InitValue(RxSigVal);
                                    }
                                    else
#endif /* #ifdef COM_RXSIG_FLOAT64SUPP */
                                    /* FC_VariationPoint_END */
                                    {

#ifdef COM_RXSIG_INT64
                                        /* [SWS_Com_00723] The AUTOSAR COM module shall extend the init value
                                         * (ComSignalInitValue) of a signal to the size of its ComSignalType.
                                         * Init_Val by default will be sign extended only for 32bits.
                                         * Currently for COM_SINT64 signal types, if the signal is of Negative,
                                         * it is required to perform the sign extension till 64bits explicitly. */
                                        if ( Type == COM_SINT64 )
                                        {
                                            RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
                                        }
                                        else
                                        {
                                            /* do nothing for other signal types */
                                        }
#endif /* #ifdef COM_RXSIG_INT64 */

                                        Com_UpdateRxSignalBuffer(RxSigConstPtr,RxSigVal);
                                    }
                                }
#ifdef COM_SIGNALGATEWAY
                                /* This part of code updates the Rx Gateway queue If the signal/Ipdu is timed out */
                                if(Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields) != COM_FALSE)
                                {
                                    /* If the signal is updated after the last call of Com_MainfunctionRouteSignals
                                     * because of the Ipdu Timeout
                                     * 1. The fill bit per signal has to be set
                                     * 2. Queue entry has to be done for the signal
                                     * For the further receptions of the signal, Queue and signal fill bit are not set*/
                                    Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields,COM_TRUE);
                                    /* This counter will tell if any signals in the Ipdu are updated */
                                    l_NumOfGwSignalUpdtd_ui++;
                                }
#endif /* #ifdef COM_SIGNALGATEWAY */
                            }

#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)
                            /* [SWS_Com_00793] For a signal with a configured reception filter
                             * MASKED_NEW_DIFFERS_MASKED_OLD, the AUTOSAR COM module shall treat the
                             * first value received for this signal after a reception deadline monitoring timeout
                             * occurred for this signal the same way as if the value has passed the filter criteria.*/
                            Com_SetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields,COM_TRUE);
#endif /* #if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD) */
                            RxSigConstPtr++;
#if defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
                            RxSigRamPtr++;
#endif
                        }
#ifdef COM_RX_SIGNALGROUP
                        /* Set the signal group flags to indicate timeout
                         * When the signal group is read using function Com_ReceiveSignalGroup(), if signal group is timed
                         * out then either previous value or init value is returned based on the action configured
                         */
                        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);

#if defined(COM_SIGNALGROUPGATEWAY) || (defined COM_RxFilters && defined COM_F_MASKEDNEWDIFFERSOLD)
                        RxSigGrpRamPtr   = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);
#endif
                        for (Idx_Sig_ui = RxIPduConstPtr->No_Of_SigGrp_Ref; Idx_Sig_ui != 0u; Idx_Sig_ui--)
                        {
                            /* Signal Groups with update-bit have seperate timeout handling
                             * Signal Groups without update-bit are marked as timed out, when IPdu times out.
                             */
#ifdef COM_RxSigGrpUpdateBit
                            /* if(RxSigGrpConstPtr->rxSignalGrpFields.UpdBitConf != COM_FALSE) */
                            if(Com_GetValue(RXSIGGRP,_UPDBITCONF,RxSigGrpConstPtr->rxSignalGrpFields) == COM_FALSE)
#endif
                            {
                                /* Mark the SignalGroup without update-bit as times out,
                                 * if the SignalGroup TimeoutAction is configured as REPLACE, replace its GroupSignal
                                 * shadow buffers with SignalInitValues */
                                /* if (RxSigGrpConstPtr ->rxSignalGrpFields.DataTimeoutType != (uint8)COM_NONE) */
                                if (Com_GetValue(RXSIGGRP,_TOACTION,RxSigGrpConstPtr ->rxSignalGrpFields))
                                {
                                    /* At timeout,Replace group signals in the signal group with Initial values */
                                    Com_InternalSigGrpReplaceToInit( RxSigGrpConstPtr );
                                }
#ifdef COM_SIGNALGROUPGATEWAY
                                /* This part of code updates the Rx Gateway queue If the signal group is to be updated
                                 * into signalgroup buffer by one of the below means
                                 * 1. Reception of Ipdu and thereby signal update after update bit processing
                                 */
                                if(Com_GetValue(RXSIGGRP,_ISGWSIGGRP,RxSigGrpConstPtr->rxSignalGrpFields) != COM_FALSE)
                                {
                                    /* If the signal is recieved first time after the last call of
                                     * Com_MainfunctionRouteSignals then
                                     * 1. The fill bit per signal has to be set
                                     * 2. Queue entry has to be done for the signal
                                     * For the further receptions of the signal, Queue and signal fill bit are not set*/
                                    Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
                                    /* This counter will tell if any signals in the Ipdu are updated */
                                    l_NumOfGwSignalUpdtd_ui++;
                                }
#endif /* #ifdef COM_SIGNALGROUPGATEWAY */
                            }
#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)
                                    /* [SWS_Com_00793] For a signal with a configured reception filter MASKED_NEW_DIFFERS_MASKED_OLD,
                                     * the AUTOSAR COM module shall treat the first value received for this signal after a reception deadline monitoring
                                     * timeout occurred for this signal the same way as if the value has passed the filter criteria.*/
                                    Com_SetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
#endif /* #if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD) */

                            RxSigGrpConstPtr++;
#if defined(COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
                            RxSigGrpRamPtr++;
#endif
                        }

#endif /* #ifdef COM_RX_SIGNALGROUP */

#ifdef COM_RxIPduTimeoutNotify
                        /* Set the Timeout notification flag to TRUE, as the Rx Ipdu timer as elapsed.
                         * But call the TO notification callback from outside the SchM_Enter_Com_RxSigBuff() lock  */
                        CallTONotify_b = COM_TRUE;
#endif /* #ifdef COM_RxIPduTimeoutNotify */

                    } /* if (RxIpduRamPtr->RxTicks_u16 == 0x00) */
                    SchM_Exit_Com_RxSigBuff(MAINFUNCTIONRX);

#ifdef COM_RxIPduTimeoutNotify
                        /* Call the notification function for IPDU, signals & signal groups (without update-bit) */
                        if (CallTONotify_b != COM_FALSE)
                        {
                            CallTONotify_b = COM_FALSE;

                            if(RxIPduConstPtr->TimeOutNotification_Cbk != NULL_PTR)
                            {
                            /* The following function is generated function in com_cfg.c file
                             * This function calls the error notification functions of IPDU, signals & signal groups
                             * (without update-bit)
                             */
                                RxIPduConstPtr->TimeOutNotification_Cbk();
                            }
                        }
#endif /* #ifdef COM_RxIPduTimeoutNotify */
#endif /* #ifdef COM_RxIPduTimeout */

                    /* Start timeout monitoring for signals with update-bit */
#ifdef COM_RxSigUpdateTimeout
{
#ifdef COM_RxUpdateTimeoutNotify
        VAR(boolean, AUTOMATIC) CallTOSigNotify_b;

        /* Initialise the CallTOSigNotify_b flag before processing any signal */
        CallTOSigNotify_b = COM_FALSE;
#endif /* #ifdef COM_RxUpdateTimeoutNotify */
                    /* Handle time out for signals with update-bit */
                    /* Do further processing only if this number is non zero */
                    if (RxIPduConstPtr->SignalTimeout_Ref != NULL_PTR)
                    {
                        /* Get the number of signals with update-bit & configured timeout , within this IPDU */
                        NoOfSigOrSigGrp_ui = RxIPduConstPtr->SignalTimeout_Ref->numWithUpdateBit;
                        /* Initialise pointer to Com_SignalTimeoutInfo */
                        SigTimeOutConfigPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref;
                        /* Initialise pointer to timer */
                        SigTimeOutTicksPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutTicks_p;
                        for (Idx_Sig_ui = NoOfSigOrSigGrp_ui; Idx_Sig_ui != 0u; Idx_Sig_ui--)
                        {
                            RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(SigTimeOutConfigPtr->SigId);

#if (defined(COM_SIGNALGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)))
                            RxSigRamPtr      = &COM_GET_RXSIGNALFLAG(SigTimeOutConfigPtr->SigId);
#endif

                            /* Decrement the timer , if time out is enabled
                             * If FirstTimeOut for signal is disabled then timer will be loaded with COM_RXTIMER_MAX
                             * (0xFFFF).
                             * Hence do not decrement the timer if timer is 0xFFFF.
                             */
                            SchM_Enter_Com_RxSigToTicks();
                            if (((*SigTimeOutTicksPtr) != 0) && ((*SigTimeOutTicksPtr) != COM_RXTIMER_MAX))
                            {
                                --(*SigTimeOutTicksPtr);
                            }
                            /* Signal has timed out */
                            if ((*SigTimeOutTicksPtr) == 0x00)
                            {
                                /* Reload the timer */
                                (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout;
                                /* Now check if the RxTimeout Substitution is = REPLACE */
                                /*if(RxSigConstPtr->rxSignalFields.DataTimeoutType)*/
                                if(Com_GetValue(RXSIG,_TOACTION,RxSigConstPtr->rxSignalFields))
                                {
                                    VAR(Com_SigMaxType, AUTOMATIC) RxSigVal;
#if (defined( COM_RXSIG_INT64 ) || defined( COM_RXSIG_FLOAT64SUPP ))
                                    VAR(uint8,AUTOMATIC)           Type;

                                    Type = Com_GetValue(GEN,_TYPE,RxSigConstPtr->General);
#endif
                                    RxSigVal = (Com_SigMaxType)RxSigConstPtr->Init_Val;

                                    /* FC_VariationPoint_START */
#ifdef COM_RXSIG_FLOAT64SUPP
                                    /* if(RxSigConstPtr->General.Type == COM_FLOAT64) */
                                    if(Type == COM_FLOAT64)
                                    {
                                        /* For float64 signals, RxSigConstPtr->Init_Val holds index to float array
                                         * holding init values.*/
                                        COM_GET_SIGTYPEFLOAT64_BUFF(RxSigConstPtr->SigBuff_Index) =
                                                                       Com_getfloat64InitValue(RxSigVal);
                                    }
                                    else
#endif /* #ifdef COM_RXSIG_FLOAT64SUPP*/
                                    /* FC_VariationPoint_END */
                                    {

#ifdef COM_RXSIG_INT64
                                        /* [SWS_Com_00723] The AUTOSAR COM module shall extend the init value
                                         * (ComSignalInitValue) of a signal to the size of its ComSignalType.
                                         * Init_Val by default will be sign extended only for 32bits.
                                         * Currently for COM_SINT64 signal types, if the signal is of Negative,
                                         * it is required to perform the sign extension till 64bits explicitly. */
                                        if ( Type == COM_SINT64 )
                                        {
                                            RxSigVal = (Com_SigMaxType)((sint64)((sint32)RxSigVal));
                                        }
                                        else
                                        {
                                            /* do nothing for other signal types */
                                        }
#endif /* #ifdef COM_RXSIG_INT64 */

                                        /* Set the signal with Init value as signal timed out */
                                        Com_UpdateRxSignalBuffer(RxSigConstPtr,RxSigVal);
                                    }
                                }

#ifdef COM_RxUpdateTimeoutNotify
                 /* Set the signal timeout notification flag, and call TO notification callback outside the lock */
                 CallTOSigNotify_b = COM_TRUE;
#endif /* #ifdef COM_RxUpdateTimeoutNotify */

#ifdef COM_SIGNALGATEWAY
                                /* This part of code updates the Rx Gateway queue If the signal/Ipdu is timed out */
                                if(Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields) != COM_FALSE)
                                {
                                    /* If the signal is updated after the last call of Com_MainfunctionRouteSignals
                                     * because of the signal timeout
                                     * 1. The fill bit per signal has to be set
                                     * 2. Queue entry has to be done for the signal
                                     * For the further receptions of the signal, Queue and signal fill bit are not set*/
                                    Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields,COM_TRUE);
                                    /* This counter will tell if any signals in the Ipdu are updated */
                                    l_NumOfGwSignalUpdtd_ui++;
                                }
#endif /* #ifdef COM_SIGNALGATEWAY */

#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)
                                    /* [SWS_Com_00793] For a signal with a configured reception filter MASKED_NEW_DIFFERS_MASKED_OLD,
                                     * the AUTOSAR COM module shall treat the first value received for this signal after a reception deadline monitoring
                                     * timeout occurred for this signal the same way as if the value has passed the filter criteria.*/
                                    Com_SetRamValue(RXSIG,_DMFILTERING,RxSigRamPtr->rxSigRAMFields,COM_TRUE);
#endif /* #if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD) */
                            }
                            SchM_Exit_Com_RxSigToTicks();

#ifdef COM_RxUpdateTimeoutNotify
                            /*if signal has timed out,Call the timeout notification for the signal */
                            if (CallTOSigNotify_b != COM_FALSE)
                            {
                                /* Reset the CallTOSigNotify_b flag before processing next signal */
                                CallTOSigNotify_b = COM_FALSE;

                                if(SigTimeOutConfigPtr->TimeOutNotification_Cbk != NULL_PTR)
                                {
                                    SigTimeOutConfigPtr->TimeOutNotification_Cbk();
                                }
                            }
#endif /* #ifdef COM_RxUpdateTimeoutNotify */

                            SigTimeOutConfigPtr++;
                            SigTimeOutTicksPtr++;
                        }/* End for loop */

                    }/* if (NoOfSigOrSigGrp_ui != 0) */
}
#endif /* #ifdef COM_RxSigUpdateTimeout */

                    /* Start timeout monitoring for signal groups with update-bit */
#ifdef COM_RxSigGrpUpdateTimeout
{
#ifdef COM_RxUpdateTimeoutNotify
    /* Local variable which is used as flag to call the callback functions when the SigGrp times out */
            VAR(boolean, AUTOMATIC) CallTOSigGrpNotify_b;

            /* Initialise the flag which is used to call the TO notification callback functions */
            CallTOSigGrpNotify_b = COM_FALSE;
#endif /* #ifdef COM_RxUpdateTimeoutNotify */
                    /* Handle time out for signal groups with update-bit */
                    /* Do further processing only if this number is non zero */
                    if (RxIPduConstPtr->SignalGrpTimeout_Ref != NULL_PTR)
                    {
                        /* Get the number of signal groups with update-bit & configured timeout, within this IPDU */
                        NoOfSigOrSigGrp_ui = RxIPduConstPtr->SignalGrpTimeout_Ref->numWithUpdateBit;
                        /* Initialise pointer to Com_SignalTimeoutInfo */
                        SigTimeOutConfigPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref;
                        /* Initialise pointer to timer */
                        SigTimeOutTicksPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p;
                        for (Idx_Sig_ui = NoOfSigOrSigGrp_ui; Idx_Sig_ui != 0u; Idx_Sig_ui--)
                        {
#if (defined(COM_SIGNALGROUPGATEWAY) || defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD))
                            RxSigGrpRamPtr      = &COM_GET_RXSIGGRPFLAG(SigTimeOutConfigPtr->SigId);
#endif
                            /* Decrement the timer, if time out is enabled
                             * If FirstTimeOut for signal group is disabled then timer will be loaded with
                             * COM_RXTIMER_MAX(0xFFFF). Hence do not decrement the timer if timer is 0xFFFF.
                             */
                            SchM_Enter_Com_RxSigGrpToTicks();
                            if (((*SigTimeOutTicksPtr) != 0) && ((*SigTimeOutTicksPtr) != COM_RXTIMER_MAX))
                            {
                                --(*SigTimeOutTicksPtr);
                            }
                            /* Signal group has timed out */
                            if ((*SigTimeOutTicksPtr) == 0x00)
                            {
                                /* Reload the timer */
                                (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout;

                                RxSigGrpConstPtr      = COM_GET_RXSIGGRP_CONSTDATA(SigTimeOutConfigPtr->SigId);

                                /* Once SignalGroup with configured update-bit times out and
                                 * if the SignalGroup TimeoutAction is configured as REPLACE, replace its GroupSignal
                                 * shadow buffers with SignalInitValues */
                                /* if (Com_RxSigGrp[SigTimeOutConfigPtr->SigId].rxSignalGrpFields.DataTimeoutType != (uint8)COM_NONE) */
                                if (Com_GetValue(RXSIGGRP,_TOACTION,RxSigGrpConstPtr->rxSignalGrpFields))
                                {
                                    /* At timeout,Replace group signals in the signal group with Initial values */
                                    Com_InternalSigGrpReplaceToInit( RxSigGrpConstPtr );
                                }
#ifdef COM_RxUpdateTimeoutNotify
                                /* Set the flag which is used to call callback notifications signal group with
                                 * update bit times out*/
                                  CallTOSigGrpNotify_b = COM_TRUE;
#endif /* #ifdef COM_RxUpdateTimeoutNotify */
#ifdef COM_SIGNALGROUPGATEWAY
                                /* This part of code updates the Rx Gateway queue If the signal group is to be updated
                                 *  into signalgroup buffer by one of the below means
                                 * 1. Reception of Ipdu and thereby signal update after update bit processing
                                 */
                                if(Com_GetValue(RXSIGGRP,_ISGWSIGGRP,RxSigGrpConstPtr->rxSignalGrpFields) != COM_FALSE)
                                {
                                    /* If the signal is recieved first time after the last call of
                                     * Com_MainfunctionRouteSignals then
                                     * 1. The fill bit per signal has to be set
                                     * 2. Queue entry has to be done for the signal
                                     * For the further receptions of the signal, Queue and signal fill bit are not set*/
                                    Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
                                    /* This counter will tell if any signals in the Ipdu are updated */
                                    l_NumOfGwSignalUpdtd_ui++;
                                }
#endif /* #ifdef COM_SIGNALGROUPGATEWAY */

#if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)
                                    /* [SWS_Com_00793] For a signal with a configured reception filter MASKED_NEW_DIFFERS_MASKED_OLD,
                                     * the AUTOSAR COM module shall treat the first value received for this signal after a reception deadline monitoring
                                     * timeout occurred for this signal the same way as if the value has passed the filter criteria.*/
                                    Com_SetRamValue(RXSIGGRP,_DMFILTERING,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
#endif /* #if defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD) */
                            }
                            SchM_Exit_Com_RxSigGrpToTicks();
#ifdef COM_RxUpdateTimeoutNotify
                                /*if signal group has timed out,Call the timeout notification for the signal */
                                if (CallTOSigGrpNotify_b != COM_FALSE)
                                {
                                    /* Reset the flag which is used to call the TO notification callback functions */
                                    CallTOSigGrpNotify_b = COM_FALSE;

                                    if(SigTimeOutConfigPtr->TimeOutNotification_Cbk != NULL_PTR)
                                    {
                                        SigTimeOutConfigPtr->TimeOutNotification_Cbk();
                                    }
                                }
#endif /* #ifdef COM_RxUpdateTimeoutNotify */
                            SigTimeOutConfigPtr++;
                            SigTimeOutTicksPtr++;
#if (defined(COM_SIGNALGROUPGATEWAY) || (defined (COM_RxFilters) && defined (COM_F_MASKEDNEWDIFFERSOLD)))
                            RxSigGrpRamPtr++;
#endif
                        }/* End for loop */
                    }/* if (NoOfSigOrSigGrp_ui != 0) */
}
#endif /* #ifdef COM_RxSigGrpUpdateTimeout */
                }/* if(COM_CheckRxIPduDMStatus(Idx_ui)) */


            }/* END of: Check for Ipdu Group is Started/Stopped and Check if EnableRxDM is enabled/disabled*/

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
            /* This part of code updates the Rx Gateway queue If any signal in the Ipdu were updated by one of the
             * below means
             * 1. Rx Ipdu timeout leading to a signal update
             * 2. Signal timeout leading to a signal update
             */
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
             * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
             * system behaviour. Hence suppressed. */
            if( (l_NumOfGwSignalUpdtd_ui > 0u) &&
                (Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags) != COM_TRUE))
            {

                SchM_Enter_Com_RxSigGwQueueProtArea();
                /* There is a new reception of Ipdu caused a new update on the Signal, Hence set the flag to process
                 * in next Com_MainfunctionRouteSignals
                 * Once the Ipdu is processed, this flag will hold COM_TRUE in Com_MainfunctionRouteSignals
                 * If any new receptions are invoked on the same Ipdu before the next processing is done,
                 * 1. Signal buffers are updated
                 * 2. Queue is not updated */
                (void)Com_WriteSigGwReceiveQueue((PduIdType)Idx_ui);
                /* There is a new reception of Ipdu/ Ipdu timeout caused a new update on the Signal, Hence set the flag
                 * to process in next Com_MainfunctionRouteSignals
                 * Once the Ipdu is processed, this flag will hold COM_TRUE in Com_MainfunctionRouteSignals
                 * If any new receptions are invoked on the same Ipdu before the next processing is done,
                 * 1. Signal buffers are updated
                 * 2. Queue is not updated */
                Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,RxIpduRamPtr->RxFlags,COM_TRUE);
                SchM_Exit_Com_RxSigGwQueueProtArea();
            }
#endif /* #if defined COM_SIGNALGATEWAY || defined COM_SIGNALGROUPGATEWAY */

            RxIPduConstPtr++;
            RxIpduRamPtr++;

        }
    }

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

#ifdef COM_PROVIDE_IPDU_STATUS
/***************************************************************************************************
 Function name    : COM_ProvideRxIpduStatus
 Syntax           : boolean COM_ProvideRxIpduStatus(PduId)
 Description      : The service COM_ProvideRxIpduStatus returns the status of Rx I-PDU referenced by PduId.
 Parameter        : PduId
 Return value     : boolean
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean,COM_CODE) Com_ProvideRxIpduStatus(VAR(PduIdType, AUTOMATIC) PduId)
{
    VAR(boolean, AUTOMATIC) pduStatus_b;

    /* If the Pdu Id passed is not an Rx Ipdu Id or Ipdu is not started, then status false is returned */
    if (PduId < COM_GET_NUM_RX_IPDU)
    {
        /* If PB variant is selected, then PduId which is passed to this function will be changed
         * to internal Id which is generated through configuration
         * If PC variant is selected, then no mapping table will be used. */

        PduId = COM_GET_RX_IPDU_ID(PduId);

        /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
         * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
         * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
         * Hence the warning is suppressed. */
        pduStatus_b = COM_CheckRxIPduStatus(PduId);
    }
    else
    {
        pduStatus_b  = COM_FALSE;
    }

    return(pduStatus_b);

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #ifdef COM_PROVIDE_IPDU_STATUS */


