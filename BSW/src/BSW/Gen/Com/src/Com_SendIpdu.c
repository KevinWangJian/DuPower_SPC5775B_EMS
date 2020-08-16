

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
#include "PduR_Com.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != COM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != COM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/* Below table details the transmission behavior in combination with Mode change
------------------------------------------------------------------------------
    TxMode        ModeChange    Other Cases            Flag value  N - Number of repetitions
------------------------------------------------------------------------------
    None            No              NA                    : 00 -- No transmission
    None            Yes             NA                    : 00 -- No transmission
    Periodic        No              NA                    : 00 -- No transmission
    Periodic        Yes             NA                    : 01 -- COM_TRANS_IN_PROC
    Direct          No              N>0                   : 01 -- N-times transmission+COM_TRANS_IN_PROC
    Direct          No              N=0                   : 00 -- COM_RESET
    Direct          Yes             N>0                   : 01 -- N-times transmission+COM_TRANS_IN_PROC
    Direct          Yes             N=0                   : 00 -- COM_RESET
    Mixed           No         Pending signal             : 00 -- No transmission
    Mixed           No         Trig signal,N=0            : 00 -- COM_RESET
    Mixed           No         Trig signal,N>0            : 01 -- N-times transmission+COM_TRANS_IN_PROC
    Mixed           Yes        Pending signal             : 02 -- COM_MIXED_PENDING
    Mixed           Yes        Trig signal,N=0            : 03 -- COM_MIXED_TRIG
    Mixed           Yes        Trig signal,N>0            : 03 -- COM_MIXED_TRIG
    COM_RESET            : Transmission will happen in Com_SendIpdu immediately
    COM_TRANS_IN_PROC    : Transmission will be initiated in Com_MainFunctionTx
    COM_MIXED_PENDING    : N-times transmission should be cancelled + periodic Transmission should be started
    COM_MIXED_TRIG       : Periodic transmission should be cancelled + N-times transmission should be initiated.
*/
/***************************************************************************************************
 Function name    : Com_SendIpdu
 Syntax           : void Com_SendIpdu(PduIdType ComTxPduId)
 Description      : Internal function used for Transmitting Tx Ipdu's
 Parameter        : ComTxPduId-> Id of the Tx ipdu,Timeouts
 Return value     : Void
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_SendIpdu(VAR(PduIdType, AUTOMATIC) ComTxPduId, VAR(Com_SendIpduInfo, AUTOMATIC) sendIpduFlag_u16)
{
    Com_TxIpduConstPtrType TxIPduConstPtr;        /* Local pointer to the Tx ipdu static configuration */
    Com_TxIpduRamPtrType TxIpduRamPtr;          /* Local pointer to the Tx ipdu status structure */
    VAR(boolean,AUTOMATIC) SendIpdu_b;

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(ComTxPduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);
    SendIpdu_b = COM_FALSE;

    /* This flag is to check if the Call to Com_SendIpdu happened from
     * 1. Com_SendSignal()
     * 2. Com_SendSignalGroup()
     * 3. Com_SwitchIpduTxMode()
     * 4. Com_TriggerIPduSend()
     * 5. Com_SendDynSignal()
     * 6. Com_TriggerIPDUSendWithMetaData()
     * 7. Com_MainFunctionRouteSignals()
     * 8. Com_SendSignalGroupArray()
     */
    SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
    if (sendIpduFlag_u16.isEventTrig != COM_RESET)
    {
        boolean proceedFurthur_b;
        proceedFurthur_b = COM_FALSE;

        TxIpduRamPtr ->Com_n_Tick_Tx = 0;
        /* As There was a mode change for the periodic IPdu,Load the timer */
        if (sendIpduFlag_u16.isModeChangd == COM_SET)
        {
            VAR(uint8, AUTOMATIC) LatestTransMode_u8;

            TxIpduRamPtr->Com_n = 0;
            /* LatestTransMode_u8 = TxIpduRamPtr->Com_TransMode.LatestTransMode ) */
            LatestTransMode_u8 = Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode);

            switch (LatestTransMode_u8)
            {
            case COM_TXMODE_PERIODIC:
                 /* The below counter will be decremented in the next call of Com_MainFunctionTx() and IPDU will be
                 * transmitted if IPDU tx mode is PERIODIC or MIXED */
                TxIpduRamPtr->Com_Tick_Tx = 1;
                break;

            case COM_TXMODE_DIRECT:
                /* The CurrentTxModePtr points to the structure information of the current TxModeState
                 * COM279: Update the counter for number of repetition,If TMS changes to DIRECT,
                 * then send the IPDU immediately respecting MDT */
                TxIpduRamPtr->Com_n = TxIpduRamPtr->CurrentTxModePtr->NumOfRepetitions;
                proceedFurthur_b = COM_TRUE;
                break;

            case COM_TXMODE_MIXED:
                /* The CurrentTxModePtr points to the structure information of the current TxModeState */
                /* COM279: Update the counter for number of repetition, even if number of repetition is not equal to ZERO
                 * If TMS changes to MIXED mode because of a PENDING signal, then IPDU will be sent in
                 * periodic mode immediately, respecting MDT.*/
                if(sendIpduFlag_u16.sigTransProp == COM_RESET)
                {
                    /* This below step is done on the smo2cob */
                    /*TxIpduRamPtr->Com_n = 0;*/
                    TxIpduRamPtr ->Com_Tick_Tx = 1;
                }
                else
                {
                    TxIpduRamPtr->Com_n = TxIpduRamPtr->CurrentTxModePtr->NumOfRepetitions;
                    /* FC_VariationPoint_START */
#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION
                    TxIpduRamPtr->Com_Tick_Tx = COM_getTxIPduCyclePeriod((PduIdType)ComTxPduId);
#else
                    /* FC_VariationPoint_END */
                    TxIpduRamPtr->Com_Tick_Tx = Com_UpdateComTickTx_TMS(TxIpduRamPtr->CurrentTxModePtr);
                    /* FC_VariationPoint_START */
#endif /* #ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION */
                    /* FC_VariationPoint_END */
                    TxIpduRamPtr->Com_Tick_Tx++;
                    proceedFurthur_b = COM_TRUE;
                }
                break;

            case COM_TXMODE_NONE:
                break;

            default:
                /* Validations and code generation shall take care to generate the valid transmission mode.
                 * In case, if the program control reach here, nothing shall be done */
                break;
            }
        }
        /* If there is no mode change, then Com_SendIpdu is called for transmission of event message */
        else
        {
            TxIpduRamPtr->Com_n = TxIpduRamPtr->CurrentTxModePtr->NumOfRepetitions;
            proceedFurthur_b = COM_TRUE;
        }
        /* This part will be executed, Only for the event transmissions for Ipdus with
         * 1. Direct Mode
         * 2. Mixed mode with the signal transfer property Triggered
         * In case of mode change, Ipdus with tx mode :
         * 1. Direct mode
         * 2. Mixed mode with the signal triggered transfer property
         * */
        if (proceedFurthur_b == COM_TRUE)
        {
            /* Check if the call to Com_SendIpdu is from Com_TriggerIpduSend() or Com_TriggerIPDUSendWithMetaData() */
            if ( ( sendIpduFlag_u16.isTriggerIpduSend             == COM_SET ) ||
                 ( sendIpduFlag_u16.isTriggerIpduSendWithMetadata == COM_SET ) )
            {
                /* The outstanding transmissions for the direct/Mixed mode with N>0 should be cancelled  */
                TxIpduRamPtr->Com_n = 0;
            }

#ifdef COM_TxIPduTimeOut
            /* The Transmission mode is Mixed /Direct */
            if (sendIpduFlag_u16.isTimeoutReq == COM_SET)
            {
                /*The timer is started only in case the signal/signal group has configured timeout*/
                /*Start the TxConfirmation Timer now i.e Set the Timer value to the one configured*/
                /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_START */
                Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
                /*Note 1: If the transmission deadline monitoring timer runs out,there shall be an error notification,
                 * regardless of the reason.Even if it was postponed because of the MDT or it was filtered out via an I-PDU callout
                 *Note 2: Timeout_Fact + 1,because in the immediate call to Com_MainfunctionTx(), this Tick will be decremented */
                TxIpduRamPtr->Com_TickTxTimeout = (TxIPduConstPtr->Timeout_Fact + 1);
            }
#endif
            /* 1. Check for Min Delay Timer of this IPDU,If MDT is not ZERO, SET a Flag, so that as soon as MDT becomes Zero
                  in Com_MainfunctionTx(), this IPDU Can be transmitted.
               2. The Mentioned Sentence can be supported if MDT required for DIRECT Frames */
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
             * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
             * system behaviour. Hence suppressed. */
            if((TxIpduRamPtr ->Com_MinDelayTick == 0)
               /* (TxIpduRamPtr->Com_TxFlags.MDT_Flag == COM_RESET) */
               && (Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags) == COM_FALSE))
            {

                if(TxIpduRamPtr->Com_n == 0)
                {
                    /* FC_VariationPoint_START */
#ifdef COM_MIXEDPHASESHIFT
                    {
                        /* Check if MixedPhaseShift is enabled.
                         * NOTE : PhaseShift is applicable for COM_MIXED mode only.If mode is COM_PERIODIC then this
                         * bitfield is initialised to COM_FALSE.
                         * If enabled, then periodic timer has to be reloaded here.
                         * If Common Tx Period feature is enabled and active, then periodic timer will be loaded with
                         * Com_ReducedPeriod_u16
                         */
                        /* if(TxIpduRamPtr->Com_TransMode.MixedPhaseShift != COM_FALSE) */
                        if (Com_GetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode) != COM_FALSE)
                        {
#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION

                            TxIpduRamPtr->Com_Tick_Tx = COM_getTxIPduCyclePeriod((PduIdType)ComTxPduId);
#else
                            TxIpduRamPtr ->Com_Tick_Tx = Com_UpdateComTickTx_TMS(TxIpduRamPtr->CurrentTxModePtr);

#endif /* #ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION */

                            TxIpduRamPtr ->Com_Tick_Tx++;
                        }
                    }
#endif /* #ifdef COM_MIXEDPHASESHIFT */
                    /* FC_VariationPoint_END */

                    /* Trigger immediate transmission only for Gw Ipdus */
                    if (sendIpduFlag_u16.isGwIpduSend != COM_RESET)
                    {
                        SendIpdu_b = COM_TRUE;
                        /* When an event Ipdu is triggered from Com_MainfunctionRouteSignals(), Ipdu has to be sent
                         * immedietaly. But the Ipdu transmission will be asynchronous with Com_MainfunctionTx, so flag
                         * handles that use case
                         */
                        Com_SetRamValue(TXIPDU,_GWPDUTRANS,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
                    }
                    /* Com Design and optimisation requirement: The transmissions are never done event based;
                    * Whenever there is an event transmission, Com flags it and initiates the transmission in the Next Mainfunction
                    * Please note this holds good for Ipdus transmitted from API Com_TriggerIpduSend()
                    * Effectively there are two transmission paths in Com
                    * 1. Com_MainfucntionTx
                    * 2. Event transmission for Com Gw Pdus */
                    else
                    {
#ifdef COM_TXPDU_DEFERREDPROCESSING
                        /* Com Design and optimisation requirement: The transmissions are never done event based;
                         * Whenever there is an event transmission, Com flags it and initiates the transmission in the Next Mainfunction
                         * Please note this holds good for Ipdus transmitted from API Com_TriggerIpduSend()
                         * Effectively there are two transmission paths in Com
                         * 1. Com_MainfucntionTx
                         * 2. Event transmission for Com Gw Pdus */
                        TxIpduRamPtr ->Com_n_Tick_Tx = 1;
                        /* This flag does multiple operations:
                         * When an event Ipdu is triggered from Com_SendSignal/Com_SendSignalGroup/Com_SendDynSignal/Com_TriggerIpduSend
                         * then the flag will initiate a transmission in the next call of Com_MainfunctionTx
                         * Because these two are mutually exclusive, the flag is common.
                         */
                        Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
#else
                        /* In case of IPdu with DIRECT/MIXED transmission mode and if the updated signal is TRIGGERED/
                         * TRIGGERED_ON_CHANGE(signal value is different), then immediately trigger for transmission */
                        SendIpdu_b = COM_TRUE;
#endif /*COM_TXPDU_DEFERREDPROCESSING*/
                    }
                }
                else
                {
                /* Com Design and optimisation requirement: The transmissions are never done event based;
                 * Whenever there is an event transmission, Com flags it and initiates the transmission in the Next Mainfunction
                 * Please note this holds good for Ipdus transmitted from API Com_TriggerIpduSend()
                 * Effectively there are two transmission paths in Com
                 * 1. Com_MainfucntionTx
                 * 2. Event transmission for Com Gw Pdus */
                    TxIpduRamPtr ->Com_n_Tick_Tx = 1;
                }
                /*END of if(MDT[IpduId_ui] == 0)*/
            }
            else
            {
                /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_SET */
                Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
                /*This Flag has to be RESET in MainFunctionTx() just before calling Com_SendIpdu( )*/

                /* Periodic timer update for mixed phase shift when msg triggered within ComMinimumDelayTime */
                #ifdef COM_MIXEDPHASESHIFT
                if (Com_GetRamValue(TXIPDU,_MIXEDPHASESHIFT,TxIpduRamPtr->Com_TransMode) != COM_FALSE)
                {
                    /* FC_VariationPoint_START */
#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION
                    TxIpduRamPtr->Com_Tick_Tx = COM_getTxIPduCyclePeriod((PduIdType)ComTxPduId) +
                                                TxIpduRamPtr->Com_MinDelayTick;
#else
                    /* FC_VariationPoint_END */
                    TxIpduRamPtr->Com_Tick_Tx = Com_UpdateComTickTx_TMS(TxIpduRamPtr->CurrentTxModePtr) +
                                                TxIpduRamPtr->Com_MinDelayTick;
                    /* FC_VariationPoint_START */
#endif /* #ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION */
                    /* FC_VariationPoint_END */
                }
                #endif

            }
        }

    }
    /* If the call is from Com_MainfunctionTx */
    /* if (sendIpduFlag_u16.isEventTrig != COM_RESET) */
    else
    {
        /* MDT checks happen in Com_MainFucntionTx,hence no MDT related checks here */
        SendIpdu_b = COM_TRUE;
#ifdef COM_TxIPduTimeOut
        /* MODE is PERIODIC or MIXED */
        if(sendIpduFlag_u16.isTimeoutReq == COM_SET)
        {
            /* if (TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag != COM_START) */
            if(Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) != COM_START)
            {
                /*Start the TxConfirmation Timer now i.e Set the Timer value to the one configured*/
                /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_START */
                Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
                TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact  ;
            }
        }
#endif /* #ifdef COM_TxIPduTimeOut */

    }
    SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
    if(SendIpdu_b == COM_TRUE)
    {
        VAR(Std_ReturnType, AUTOMATIC) ipduTransStatus_ui;
#if (defined(COM_TxIPduCallOuts) || defined(COM_TXDOUBLEBUFFER) || defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT))
        VAR(boolean, AUTOMATIC) txIpduFields_b;
#endif /* #if defined(COM_TxIPduCallOuts) || defined(COM_TXDOUBLEBUFFER) */
#ifdef COM_TxIPduCallOuts
        VAR(boolean, AUTOMATIC) CalloutCheck_b;
        CalloutCheck_b = COM_TRUE;
#endif

#ifdef COM_TxIPduCallOuts
        txIpduFields_b = Com_GetValue(TXIPDU,_ISCALLOUTFRMTRIGTRANS,TxIPduConstPtr->txIPduFields);
        /* Check for Ipdu Callout configured for this IPDU
         * If not configured Continue and if Configured and callout returns TRUE Continue.
         * If Callout Returns FALSE, Dont call the PduR_ComTransmit()
         * If the callout is configured to be called from Com_TriggerTransmit, dont call here */
        if( (TxIPduConstPtr->CallOut != NULL_PTR) && (txIpduFields_b != COM_TRUE))
        {
            SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA);
            CalloutCheck_b = TxIPduConstPtr->CallOut(ComTxPduId,TxIPduConstPtr->BuffPtr);
            SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA);
        }
        if(CalloutCheck_b == COM_TRUE)
#endif /* #ifdef COM_TxIPduCallOuts */
        {

            /* Assign the Address and the length to the Global variable */
            COM_GET_PDUINFO_S(ComTxPduId).SduDataPtr = TxIPduConstPtr->BuffPtr;
            COM_GET_PDUINFO_S(ComTxPduId).SduLength = TxIPduConstPtr->Size;

#if (defined(COM_TXDOUBLEBUFFER) || defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT))
            txIpduFields_b = Com_GetRamValue(TXIPDU,_ISDYNIPDU,TxIPduConstPtr->txIPduFields);
#endif /* #if (defined(COM_TXDOUBLEBUFFER) || defined(COM_TX_DYNAMIC_SIGNAL_SUPPORT)) */

#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
            /* The total Ipdu size will be sum of Ipdu static length and dynamic length for a dynamic IPdu.
             * The Dynamic length of the Ipdu is updated in the call to Com_SendDynSignal.*/
            /* if(COM_SET == TxIPduConstPtr->txIPduFields.IsDynPdu) */
            if(COM_TRUE == txIpduFields_b)
            {
                COM_GET_PDUINFO_S(ComTxPduId).SduLength = TxIPduConstPtr->Size + TxIpduRamPtr->Com_DynLength;
            }
#endif /* #ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT */

#ifdef COM_METADATA_SUPPORT
            /* If IPdu supports MetaData then the total IPdu size will be sum of IPdu static length and MetaData
             * length */
            if ( Com_GetValue( TXIPDU, _ISMETADATASUPPORTED, TxIPduConstPtr->txIPduFields ) )
            {
                COM_GET_PDUINFO_S(ComTxPduId).SduLength =
                                         TxIPduConstPtr->Size + TxIPduConstPtr->MetaDataPtr->MetaDataLength;
            }
#endif /* #ifdef COM_METADATA_SUPPORT */

#ifdef COM_TXDOUBLEBUFFER
            /* a dynamic Pdu cannot have double buffer mechanism */
            /* if((TxIpduRamPtr->Com_TransMode.LatestTransMode != COM_TXMODE_NONE) && (COM_RESET == TxIPduConstPtr->txIPduFields.IsDynPdu)) */
            if ((Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) != COM_TXMODE_NONE)&&
                (COM_FALSE == txIpduFields_b))
            {
                SchM_Enter_Com_TxPduDoubleBuffer();
                /*Call Com_ByteCopy() for Copying the Data of IPDU buffer into Tx Local Buffer */
                Com_ByteCopy(TxIPduConstPtr->LocalBuffPtr,TxIPduConstPtr->BuffPtr,
                        (uint32)COM_GET_PDUINFO_S(ComTxPduId).SduLength);
                SchM_Exit_Com_TxPduDoubleBuffer();
            }
#ifdef COM_MULTICORE_SUPPORT
            SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA);
#endif  /* #ifdef COM_MULTICORE_SUPPORT */

            /*Call PDUR_Transmit()*/
            ipduTransStatus_ui = PduR_ComTransmit(TxIPduConstPtr->PdurId,&COM_GET_PDUINFO_S(ComTxPduId));

#ifdef COM_MULTICORE_SUPPORT
            SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA);
#endif  /* #ifdef COM_MULTICORE_SUPPORT */
#else
#ifdef COM_MULTICORE_SUPPORT
            SchM_Enter_Com_TxIpduProtArea(SENDIPDU_DATA);
#endif  /* #ifdef COM_MULTICORE_SUPPORT */
            /*Call PDUR_Transmit()*/
            ipduTransStatus_ui = PduR_ComTransmit(TxIPduConstPtr->PdurId,&COM_GET_PDUINFO_S(ComTxPduId));
#ifdef COM_MULTICORE_SUPPORT
            SchM_Exit_Com_TxIpduProtArea(SENDIPDU_DATA);
#endif  /* #ifdef COM_MULTICORE_SUPPORT */
#endif  /* #ifdef COM_TXDOUBLEBUFFER */
        }
#ifdef COM_TxIPduCallOuts
        else
        {
            /* As specified in OSEK COM, if the I-PDU callout returns false
             * the I-PDU will not be processed any further */
            ipduTransStatus_ui = E_NOT_OK;
        }
#endif
#ifdef COM_METADATA_SUPPORT
        /* If IPdu has MetaDataDefault configured and request transmit from Com_TriggerIPDUWithMetaData() */
        if(sendIpduFlag_u16.isTriggerIpduSendWithMetadata == COM_SET)
        {
        	/* Restore default metadata in Tx Buffer */
			Com_ByteCopy(
				   ( P2VAR( uint8, AUTOMATIC, COM_APPL_DATA ) )( TxIPduConstPtr->BuffPtr + TxIPduConstPtr->Size ),
				( P2CONST( uint8, AUTOMATIC, COM_APPL_CONST ) )(  &TxIPduConstPtr->MetaDataPtr->MetaDataDefaultValue[0] ),
															   ( TxIPduConstPtr->MetaDataPtr->MetaDataLength ) );
        }
#endif /*COM_METADATA_SUPPORT*/
        if(ipduTransStatus_ui == E_OK)
        {
            SchM_Enter_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
            /* If ComMinimumDelayTime of an I-PDU is configured greater than 0, the AUTOSAR COM module shall load and start
             * the MDT counter upon transmission of that I PDU to the PDU Router via PduR_ComTransmit.
             * NOTE : Check (TxIpduRamPtr ->Com_MinDelayTick == 0) is done because of the below reasons.
             * If interrupts are enabled, then interrupt could be called between the call of  PduR_ComTransmit() above and
             * Com_TxConfirmation(). In this case Com_MinDelayTick will be overwritten here, leading to deadlock.
             */

            if ((TxIPduConstPtr->Min_Delay_Time_Fact != 0) && (TxIpduRamPtr ->Com_MinDelayTick == 0))
            {
                TxIpduRamPtr ->Com_MinDelayTick = TxIPduConstPtr->Min_Delay_Time_Fact;
            }

            /*If the parameter ComTxIPduClearUpdateBit of an I-PDU is configured to Transmit, the AUTOSAR COM module
             * shall clear all update-bits of all contained signals and signal groups
             *  after this I-PDU was sent out via PduR_ComTransmit and PduR_ComTransmit returned E_OK.*/
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
            /*    if(TxIPduConstPtr->txIPduFields.ClearUpdBit == (uint8)COM_CLRUPDATEBIT_TRANSMIT)*/
            if (Com_GetValue(TXIPDU,_CLRUPDBIT,TxIPduConstPtr->txIPduFields) == (uint16)COM_CLRUPDATEBIT_TRANSMIT)
            {
                Com_ClearUpdateBits(TxIPduConstPtr);
            }
#endif /* #if defined ((COM_TxSigUpdateBit)||defined(COM_TxSigGrpUpdateBit)) */

#ifdef COM_TP_IPDUTYPE
            if((Com_GetValue(TXIPDU,_ISLARGEDATAPDU,TxIPduConstPtr->txIPduFields) != COM_FALSE))
            {
                Com_SetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags,COM_TRUE);
                TxIpduRamPtr->TxTPIPduLength = 0;
            }

#endif /* #ifdef COM_TP_IPDUTYPE */

            SchM_Exit_Com_TxIpduProtArea(SENDIPDU_TXFLAGS);
        } /*End of ipduTransStatus_ui check*/
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_ClearUpdateBits
 Syntax           : void Com_ClearUpdateBits(Com_TxIpduConstPtrType TxIPduConstPtr)
 Description      : Internal function used for clearing the update bits of signals and signal groups in the IPdu
 Parameter        : TxIPduConstPtr -> Pointer to Tx ipdu static configuration
                  : BuffPtr -> Pointer to the buffer
 Return value     : None
***************************************************************************************************/
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
    FUNC (void,COM_CODE) Com_ClearUpdateBits(Com_TxIpduConstPtrType TxIPduConstPtr)
{
        VAR(uint16_least, AUTOMATIC) index_ui;
        VAR(PduLengthType, AUTOMATIC) ByteNo_u8;
#ifdef COM_TxSigUpdateBit
        Com_TxSigConstPtrType  TxSigConstPtr;    /* Local pointer to Tx signal static configuration */
#endif
#ifdef COM_TxSigGrpUpdateBit
        Com_TxSigGrpConstPtrType TxSigGrpConstPtr;  /* Local pointer to Tx signalGroup static configuration */
#endif /* #ifdef COM_TxSigGrpUpdateBit */

#ifdef COM_TxSigUpdateBit
        /* After an I-PDU is sent to lower layers and no synchronous error is returned
    by the lower layer the update-bits of all signals and signal groups belonging
    to the I-PDU sent shall be cleared.*/
        /*Clear  all Update Bits if configured in IPDU buffer*/
        TxSigConstPtr = COM_GET_TXSIG_CONSTDATA(TxIPduConstPtr->TxSigId_Index);

        for(index_ui = TxIPduConstPtr->No_Of_Sig_Ref; index_ui != 0u; index_ui--)
        {
            /* if(TxSigConstPtr->General.UpdBitConf != COM_FALSE) */
            if(Com_GetValue(GEN,_UPDBITCONF,TxSigConstPtr->General))
            {
                /*Find the Byte No, where the Update bit lies */
                ByteNo_u8 = (PduLengthType)((TxSigConstPtr->Update_Bit_Pos)>>3u);
                /* This macro clears the update bit value at the Update bit position */
                Com_ClearUpdateBitValue(TxIPduConstPtr,TxSigConstPtr->Update_Bit_Pos,ByteNo_u8)

            }
            TxSigConstPtr++;
        }
#endif /* #ifdef COM_TxSigUpdateBit*/
#ifdef COM_TxSigGrpUpdateBit
        TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(TxIPduConstPtr->FirstTxSigGrp_Index);

        for(index_ui = TxIPduConstPtr->No_Of_SigGrp_Ref; index_ui != 0u; index_ui--)
        {
            /* if(TxSigGrpConstPtr->txSignalGrpFields.UpdBitConf != COM_FALSE) */
            if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
            {
                /*Find the Byte No, where the Update bit lies */
                ByteNo_u8 = (PduLengthType)((TxSigGrpConstPtr->Update_Bit_Pos)>>3u);
                /* This macro clears the update bit value at the Update bit position */
                Com_ClearUpdateBitValue(TxIPduConstPtr,TxSigGrpConstPtr->Update_Bit_Pos,ByteNo_u8)
            }
            TxSigGrpConstPtr++;
        }
#endif /* #ifdef COM_TxSigGrpUpdateBit*/
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif/* #if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) */

