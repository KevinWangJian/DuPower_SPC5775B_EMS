

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
#ifdef COM_CANCELTRANSMITSUPPORT
#include "PduR_Com.h"
#endif
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

/***************************************************************************************************
 Function name    : Com_MainFunctionTx
 Syntax           : void Com_MainFunctionTx(void)
 Description      : Service to perform the processing of the AUTOSAR COM transmission activities
                    that are not directly initiated by the calls from the RTE and PDU-R.
 Parameter        : void
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_MainFunctionTx(void)
{

#ifdef COM_TxIPduTimeOutNotify
    VAR(boolean, AUTOMATIC) Timeout_Flag;       /*Values it can hold COM_SET/COM_RESET*/
#endif /* #ifdef COM_TxIPduTimeOutNotify */
#ifdef COM_TxIPduNotification
    VAR(boolean, AUTOMATIC) Notify_Flag;        /*Values it can hold COM_SET/COM_RESET*/
#endif /* #ifdef COM_TxIPduNotification */
    VAR(boolean, AUTOMATIC) SendIPdu;
    VAR(boolean, AUTOMATIC) MDT_Flag_b;
    VAR(uint8, AUTOMATIC) LatestTransMode_u8;
    VAR(uint16_least, AUTOMATIC) Index_ui;
    Com_TxIpduConstPtrType TxIPduConstPtr;    /* Local pointer to hold tha address of the Tx ipdu static configuration */
    Com_TxIpduRamPtrType TxIpduRamPtr;        /* Local pointer to hold the address of the Tx ipdu status structure */

#ifdef COM_TxIPduTimeOutNotify
    Timeout_Flag = COM_FALSE;   /*Initializing to COM_RESET*/
#endif /* #ifdef COM_TxIPduTimeOutNotify */
#ifdef COM_TxIPduNotification
    Notify_Flag  = COM_FALSE;    /*Initializing to COM_RESET*/
#endif /* #ifdef COM_TxIPduNotification */
    SendIPdu     = COM_FALSE;

    /* Start: Det */
    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_MainFunctionTx, COM_E_UNINIT)
    /* End: Det */

    if(Com_Uninit_Flag == COM_INIT)
    {

        /* START: Check the count, if the count has become 0 and if the transmission mode is
           Periodic/Mixed/Direct-N times then reset the time to the one configured */
         TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(0);

        TxIpduRamPtr = &COM_GET_TXPDURAM_S(0);

        for(Index_ui = 0; Index_ui < COM_GET_NUM_TX_IPDU; Index_ui++)
        {
            /* Check if IPdu group is started */
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
             * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
             * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
             * Hence the warning is suppressed. */
            if(COM_CheckTxIPduStatus(Index_ui))
            {
#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)
                VAR(boolean, AUTOMATIC)    TxConfirFlag;
#endif /* #if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification) */

                SchM_Enter_Com_TxIpduProtArea(MAINFUNCTIONTX);
                /* Handling if Tx timeout is enabled */
#if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification)
                /*Start: Tx Timeout Check*/
                /* TxConfirFlag = TxIpduRamPtr->Com_TxFlags.TxConfirFlag */
                TxConfirFlag = Com_GetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags);
                if (TxConfirFlag == COM_TRUE)
                {
                    /* TxIpduRamPtr->Com_TxFlags.TxConfirFlag = COM_RESET */
                    Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
#ifdef COM_TxIPduNotification
                    /* if(TxIPduConstPtr->txIPduFields.Signal_Processing == COM_DEFERRED) */
                    if(Com_GetValue(TXIPDU,_SIGPROC,TxIPduConstPtr->txIPduFields) == COM_DEFERRED)
                    {
                        Notify_Flag = COM_TRUE;  /*Deffered Notification need to be called for this Ipdu*/

                    }
#endif /* #ifdef COM_TxIPduNotification */
                }

                /*Start: Tx Timeout Check*/
#ifdef COM_TxIPduTimeOut
                if(TxConfirFlag != COM_TRUE)
                {
                    /* if(TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag == COM_START) */
                    if (Com_GetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags) == COM_START)
                    {
                        /*Reduce Tick Timeout*/
                        if(TxIpduRamPtr->Com_TickTxTimeout != 0) /*Not to go less than ZERO */
                        {
                            --(TxIpduRamPtr->Com_TickTxTimeout); /*Decrement the Tick*/
                        }
                        if(TxIpduRamPtr->Com_TickTxTimeout == 0 )
                        {
                            /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_STOP */
                            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);
                            /*This Flag has to be set to START only in SendIpdu()i.e just before Sending IPDU*/

                            /*When there is Timeout we dont care the value of TxIpduRamPtr->Com_n, So RESETING it*/
                            /*If a transmission deadline monitoring timeout occurs before the N-Times
                            transmission is complete, the N-Times transmission shall be abandoned.*/
                            TxIpduRamPtr->Com_n = 0;

                            TxIpduRamPtr->Com_MinDelayTick = 0;

#ifdef COM_TxIPduTimeOutNotify
                            Timeout_Flag = COM_TRUE; /*Timeout Notification need to be called for this Ipdu*/
#endif /* #ifdef COM_TxIPduTimeOutNotify */

#ifdef COM_CANCELTRANSMITSUPPORT
                            {
                                VAR( boolean, AUTOMATIC ) isCancelTransmitSupported;

                                isCancelTransmitSupported =
                                          Com_GetValue(TXIPDU,_ISCANCELTRANSMITSUPPORTED,TxIPduConstPtr->txIPduFields);
                                /* If the Pdu is of TP type and cancel transmit is supported for this pdu */
                                if((Com_GetValue(TXIPDU,_ISLARGEDATAPDU,TxIPduConstPtr->txIPduFields) != COM_FALSE) &&
                                   (isCancelTransmitSupported != COM_FALSE))
                                {
                                    /* Check is there ongoing transmission, then only call the cancel transmit */
                                    if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
                                    {
                                        /* Timeout occurred cancel the ongoing transmission.
                                         * As per the specification, the AUTOSAR COM ignores the return code */
                                        ( void )PduR_ComCancelTransmit(TxIPduConstPtr->PdurId);
                                    }
                                }
                            }
#endif /* #ifdef COM_CANCELTRANSMITSUPPORT */

                        }
                    }
                }
#endif/* #ifdef COM_TxIPduTimeOut */
#endif /* #if defined(COM_TxIPduTimeOut) || defined(COM_TxIPduNotification) */

                /*End: Tx Timeout Check*/
                /* Decrement the MDT timer, if timer is not already zero and also Transmission is not blocked because of
                 * non receipt of Com_TxConfirmation().
                 */
                /* MDT_Flag_b = TxIpduRamPtr->Com_TxFlags.MDT_Flag */
                MDT_Flag_b = Com_GetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags);
                /* LatestTransMode_u8 = TxIpduRamPtr->Com_TransMode.LatestTransMode */
                LatestTransMode_u8 = Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode);
                /* Decrement the MDT timer, if timer is not already zero */
                if(TxIpduRamPtr->Com_MinDelayTick != 0)
                {
                    --TxIpduRamPtr->Com_MinDelayTick;
                }

                switch(LatestTransMode_u8)
                {
                case COM_TXMODE_DIRECT:
                    if(TxIpduRamPtr->Com_n_Tick_Tx != 0)
                    {
                        --TxIpduRamPtr->Com_n_Tick_Tx;
                    }
                    if(TxIpduRamPtr->Com_MinDelayTick == 0 )
                        /*This condition is for the DIRECT && N=0 && Triggered and Com_TriggerIPDUSend()*/
                    {
                        if( MDT_Flag_b == COM_TRUE)
                        {
                            /*Call SendIpdu*/
                            SendIPdu = COM_TRUE;
                            /* Com_SendIpdu((PduIdType)Index_ui); */

                            /*This has to be RESET as soon as it is entered into this condition*/
                            /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_RESET */
                            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

                        }
                        else
                        {
#ifdef COM_TXPDU_DEFERREDPROCESSING
                            /* the first check is for event transmissions triggered from Com_SendSignal/Com_SendSignalGroup/Com_SendDynSignal/Com_TriggerIpduSend*/
                            /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of
                             * intermediate variables to store and read here, may read obsolete value.
                             * Evaluation(or no evaluation) shall not impact the system behaviour.
                             * Hence suppressed. */
                            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE))
                            {
                                /*Call SendIpdu*/ /*This Send IPDU is for Direct frames of MIXED mode*/
                                SendIPdu = COM_TRUE;
                                Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                            }
                                /* Regular N-times transmission */
                            else if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (TxIpduRamPtr->Com_n != 0))
                            {
                                SendIPdu = COM_TRUE;
                                /*Call SendIpdu*/
                            }
                            else
                            {
                                /* Do nothing */
                            }
#else
                            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (TxIpduRamPtr->Com_n != 0))
                             {
                                SendIPdu = COM_TRUE;
                                /*Call SendIpdu*/
                             }
#endif/* #ifdef COM_TXPDU_DEFERREDPROCESSING */

                        }
                        if (TxIpduRamPtr->Com_n != 0)
                        {
                            if (TxIpduRamPtr->Com_n_Tick_Tx == 0)
                            {
                                TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;

                            }
                        }

                    }
                    break;

                case COM_TXMODE_MIXED:

                    if(TxIpduRamPtr->Com_Tick_Tx != 0)
                    {
                        --TxIpduRamPtr->Com_Tick_Tx;

                    }

                    if(TxIpduRamPtr->Com_n_Tick_Tx != 0)
                    {
                        /*For the first load of the timer, the ticks should be decremented*/
                        --TxIpduRamPtr ->Com_n_Tick_Tx;
                    }
                    if(TxIpduRamPtr->Com_MinDelayTick == 0)
                    {
                        if(MDT_Flag_b == COM_TRUE)
                        {
                            /*Call SendIpdu*/
                            SendIPdu = COM_TRUE;
                            /* Com_SendIpdu((PduIdType)Index_ui); */

                            /*This has to be RESET as soon as it is entered into this condition*/
                            /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_RESET */
                            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                        }
                        else
                        {
#ifdef COM_TXPDU_DEFERREDPROCESSING
                            /* the first check if for event transmissions triggered from Com_SendSignal/Com_SendSignalGroup/Com_SendDynSignal/Com_TriggerIpduSend*/
                            /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
                             * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
                             * system behaviour. Hence suppressed. */
                            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE))
                            {
                                /*Call SendIpdu*/ /*This Send IPDU is for Direct frames of MIXED mode*/
                                SendIPdu = COM_TRUE;
                                Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                            }
                            /* Regular N-times transmission */
                            else if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (TxIpduRamPtr->Com_n != 0))
#else
                            if((TxIpduRamPtr->Com_n_Tick_Tx == 0) && (TxIpduRamPtr->Com_n != 0))
#endif /* #ifdef COM_TXPDU_DEFERREDPROCESSING */
                            {
                                SendIPdu = COM_TRUE;
                                /*Call SendIpdu*/ /*This Send IPDU is for Direct frames of MIXED mode*/
                                /* Com_SendIpdu((PduIdType)Index_ui); */

                            }
                            else
                            {
                                if((TxIpduRamPtr->Com_Tick_Tx == 0)&&(TxIpduRamPtr->Com_n == 0))
                                {
                                    SendIPdu = COM_TRUE;
                                    /*Call SendIpdu*/ /*This Send IPDU is for Periodic Frames of MIXED mode */
                                    /* Com_SendIpdu((PduIdType)Index_ui); */
                                }
                            }

                        }
                        if (TxIpduRamPtr->Com_n != 0)
                        {
                            if (TxIpduRamPtr->Com_n_Tick_Tx == 0)
                            {
                                TxIpduRamPtr->Com_n_Tick_Tx = TxIpduRamPtr->CurrentTxModePtr->RepetitionPeriodFact;

                            }
                        }

                    }/*if(Com_MinDelayTick[Index_ui] == 0)*/

                    else
                    {
                        if((TxIpduRamPtr->Com_Tick_Tx == 0) && (TxIpduRamPtr->Com_n == 0))
                        {
                            /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_RESET */
                            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);  /*Usecase diagram 5b in */
                        }
                    }
                    if(TxIpduRamPtr->Com_Tick_Tx == 0)
                    {
                        /* FC_VariationPoint_START */
#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION
                        TxIpduRamPtr->Com_Tick_Tx = COM_getTxIPduCyclePeriod((PduIdType)Index_ui);
#else
                        /* FC_VariationPoint_END */
                        TxIpduRamPtr->Com_Tick_Tx = Com_UpdateComTickTx_TMS(TxIpduRamPtr->CurrentTxModePtr);
                        /* FC_VariationPoint_START */
#endif /* #ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION */
                        /* FC_VariationPoint_END */
                    }
                    break;

                case COM_TXMODE_NONE:
#ifdef COM_TXPDU_DEFERREDPROCESSING
                    /* This part of code is executed when Com_TriggerIpduSend triggers transmission from NONE Ipdus */
                    if(Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
                    {
                        if(TxIpduRamPtr->Com_n_Tick_Tx != 0)
                        {
                            TxIpduRamPtr->Com_n_Tick_Tx--;
                        }
                        if(TxIpduRamPtr->Com_n_Tick_Tx == 0)
                        {
                            /* Trigger transmission for Ipdu */
                            SendIPdu = COM_TRUE;
                        }
                        /* Reset the flag */
                        Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                    }
#endif /* #ifdef COM_TXPDU_DEFERREDPROCESSING */
                    break;

                case COM_TXMODE_PERIODIC:

                    if(TxIpduRamPtr->Com_Tick_Tx != 0)
                    {
                        --TxIpduRamPtr->Com_Tick_Tx;
                    }
                    if(TxIpduRamPtr->Com_MinDelayTick == 0 )
                    {
                        if (MDT_Flag_b == COM_TRUE)
                        {
                            /*This condition is for the DIRECT && N=0 && Triggered and Com_TriggerIPDUSend()*/
                            /*Call SendIpdu*/
                            SendIPdu = COM_TRUE;

                            /*This has to be RESET as soon as it is entered into this condition*/
                            /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_RESET */
                            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_FALSE);

                        }
                        /* the first check if for event transmissions triggered from Com_SendSignal/Com_SendSignalGroup/Com_SendDynSignal/Com_TriggerIpduSend*/
                        else
                        {
                            if(TxIpduRamPtr->Com_Tick_Tx == 0 )
                            {
                                SendIPdu = COM_TRUE;
                                /*Call SendIpdu*/ /*This Send IPDU is for Periodic Frames */
                            }
#ifdef COM_TXPDU_DEFERREDPROCESSING
                            /* This part of code is executed when Com_TriggerIpduSend triggers transmission from Periodic Ipdus */
                            else if(Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) == COM_TRUE)
                            {
                                if(TxIpduRamPtr->Com_n_Tick_Tx != 0)
                                {
                                    TxIpduRamPtr->Com_n_Tick_Tx--;
                                }
                                if(TxIpduRamPtr->Com_n_Tick_Tx == 0)
                                {
                                    /* Trigger transmission for Ipdu */
                                    SendIPdu = COM_TRUE;
                                }
                                /* Reset the flag */
                                Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                            }
                            else
                            {

                            }
#endif /* #ifdef COM_TXPDU_DEFERREDPROCESSING */
                        }
                    }
                    else
                    {
                        if( TxIpduRamPtr->Com_Tick_Tx == 0 )
                        {
                            /* TxIpduRamPtr->Com_TxFlags.MDT_Flag = COM_RESET */
                            Com_SetRamValue(TXIPDU,_MDT,TxIpduRamPtr->Com_TxFlags,COM_TRUE);  /*Usecase diagram 5b in */
                        }
                    }
                    /*the Timer is started only if the timer is already not running */
                    if( TxIpduRamPtr->Com_Tick_Tx == 0)
                    {
                        /*For the first load of the timer, the ticks should be decremented*/
                        /* FC_VariationPoint_START */
#ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION
                        TxIpduRamPtr->Com_Tick_Tx = COM_getTxIPduCyclePeriod((PduIdType)Index_ui);
#else
                        /* FC_VariationPoint_END */
                        TxIpduRamPtr ->Com_Tick_Tx = Com_UpdateComTickTx_TMS(TxIpduRamPtr->CurrentTxModePtr);
                        /* FC_VariationPoint_START */
#endif /* #ifdef COM_TXPDU_TIMEPERIOD_VIA_CALIBRATION */
                        /* FC_VariationPoint_END */
                    }
                    break;
                default:
                    /* Validations and code generation shall take care to generate the valid transmission mode.
                     * In case, if the program control reach here, nothing shall be done
                     * Hence it is left empty. */
                    break;
                }
                SchM_Exit_Com_TxIpduProtArea(MAINFUNCTIONTX);

                /*Check if Timeout Notification function need to be called */
#ifdef COM_TxIPduTimeOutNotify
                if(Timeout_Flag == COM_TRUE)
                {
                    Timeout_Flag = COM_FALSE; /*Reseting the Timeout_Flag*/
                    /* Call Ipdu Error Notification if configured
                     * This generated function will call the timeout notification callback functions of all signals and
                     * signal groups within this IPdu.
                     */
                    if(TxIPduConstPtr->TimeOutNotification_Cbk != NULL_PTR)
                    {
                        TxIPduConstPtr->TimeOutNotification_Cbk();
                    }
                }

#endif /* #ifdef COM_TxIPduTimeOutNotify */

#ifdef COM_TxIPduNotification
                /*Check if Deffered Notification function need to be called */
                if(Notify_Flag == COM_TRUE)
                {
                    Notify_Flag = COM_FALSE;    /*Reseting the Notify_Flag*/

                    /* Notification callback function for IPDU.
                     * This function is generated through code generator.
                     * Individual signal and signal group notifications functions are called from within this function.
                     * If IPDU has configured TX notification callback funcion, this function
                     * is also called from the generated function
                     */
                    if(TxIPduConstPtr->Notification_Cbk != NULL_PTR)
                    {
                        TxIPduConstPtr->Notification_Cbk();
                    }
                }
#endif /* #ifdef COM_TxIPduNotification */

                /* Send the IPdu , if there has been a condition for the same */
                if ( SendIPdu == COM_TRUE)
                {
                    /* All unused flags are reset here */
                    Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;
                    /* RESET the flag, as this IPdu is triggered from the cyclic task */
                    /* TxIpduRamPtr->Com_TxFlags.EvenTriggeredTx = COM_RESET */
                    Com_SetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
                    SendIPdu = COM_FALSE;
                    /* The bit field is loaded as below
                     * 1. Call is from proc function,so COM_RESET
                     * 2. No mode change happens from Com_mainfunctionTx ,so COM_RESET
                     * 3. Signal transfer property information is not used, so COM_RESET
                     * 4. Timeout monitoring is done for PERIODIC and MIXED frames.
                     * */
                    sendIpduFlag_u16.isEventTrig      =  COM_RESET;
#ifdef COM_TxIPduTimeOut
                    /* MODE is PERIODIC or MIXED and timeout factor is configured */
                    if(((LatestTransMode_u8 & COM_TXMODE_MIXED) > (uint8)0) && (TxIPduConstPtr->Timeout_Fact != 0u ))
                    {
                        sendIpduFlag_u16.isTimeoutReq = COM_SET;
                    }
#endif
                    /* In case of Tp large pdu: If already a transmission request has been place, then do not trigger new request
                     * In case of Normal pdu: Then this flag will never be set, so always Com_SendIpdu() will be called */
                    if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
                    {
                        Com_SendIpdu((PduIdType)Index_ui,sendIpduFlag_u16);
                    }
                }
            } /* end of IPdu group started check */

            TxIPduConstPtr++ ;
            TxIpduRamPtr++;

        } /* end of for loop */

    }

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_START */

/***************************************************************************************************
 Function name    : Com_IsTxScheduled
 Syntax           : boolean Com_MainFunctionTx(ComTxPduId)
 Description      : this function checks whether the Tx frame is scheduled to be sent in the coming cycle
 To Be considered before using this function
 --------------------------------------------
 1. this function shall be used for only Periodic type Ipdu and not for other Pdu types

When Com_IsTxScheduled is called in different task cycle as compared to Com_mainfucntionTx:
In this scenario, the API signature is changed and an additional parameter is to be passed by the caller.
Tb : Time raster of Com_mainfunctionTx
Tc : Time raster of caller of Com_IsTxScheduled

Time raster passed by the caller is in ms, hence the ticks are converted into time in ms,
Multiplying ticks by Tb will serve the purpose.
After the conversion, the value hence obtained,is remaining time for Ipdu transmission in ms

There are three cases observed in this scenario, presented below
Case 1: (Tb = Tc)
If Com_IsTxScheduled is called in the same raster as Com_mainfunctionTx,
then if Remaining time is greater than Caller time, the caller can wait for another raster to update IPdu data.
else Ipdu data update can happen in current raster.

Case 2: (Tb < Tc)
If Com_IsTxScheduled is called slower than Com_mainfunctionTx,
then if Remaining time is greater than Caller time, the caller can wait for another raster to update IPdu data.
else Ipdu data update can happen in current raster.

Case 3: (Tb > Tc)
If Com_IsTxScheduled is called faster than Com_mainfunctionTx,
Here the Com internal ticks would not have enough resolution to acknowledge the last raster before transmission.
Hence when the Com ticks reach value 1, the caller can do Ipdu data update in the current raster.

Scenarios analysed:
1. For 10ms frame, the Com_Tick_Tx will be always 1 as the com_mainfunction_tx (function above) loads the
value at the end of the function. hence the If condition will fail and function will always return TRUE
2. For >10ms frame, the Com_Tick_Tx will never have 0 value as the value is loaded at the end of the
Com_Mainfunction_Tx. When the Tick value becomes 1, this function will return true and SCL processing
will happen.
3. for >10ms Frame, if minimum delay is configured, then whever the value of Mindelay is 1, this function
will return TRUE as the frame can have request for transmission and the next transmission criteria of minimum delay
will be over in the subsequent call of mainfunction_Tx (min delay becomes 0 and can have any transmission based on signal
or transmission mode)
4. For any Cycletime Frame, if they have transmission mode change enabled (COM_TMS_VARIABLE) then
this function will return TRUE always to be on the safer side.



 Parameter        : ComTxPduId
 ComCallerTaskCycle , this parameter is the value of caller's task cycle in ms.
 i.e : if the Caller is in 1ms, then the ComCallerTaskCycle = 1
 Return value     : boolean
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(boolean, COM_CODE) Com_IsTxScheduled(VAR(PduIdType, AUTOMATIC) ComTxPduId, VAR(uint16, AUTOMATIC)ComCallerTaskCycle)
{
    VAR(boolean, AUTOMATIC) IsTxScheduled ;
    Com_TxIpduRamPtrType TxIpduRamPtr;
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
    VAR(uint16, AUTOMATIC) ticksinMs_u16 ;
#endif

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */

    ComTxPduId = COM_GET_TX_IPDU_ID(ComTxPduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(ComTxPduId);

    /*if COM_TXSCHEDULED_DIFF_TIMEBASE is disabled then ComCallerTaskCycle will be considered to be null  */
  #ifndef COM_TXSCHEDULED_DIFF_TIMEBASE
    (void)ComCallerTaskCycle;
  #endif


#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
    /* The ticks are multiplies by the time in ms to get the remaining time in ms
     * Time base is multiplied by 1000, to get the time value in ms.(i.e 1ms = 1) */
    ticksinMs_u16 = ((TxIpduRamPtr->Com_Tick_Tx)*(COM_TX_TIME_BASE_IN_MS));
#endif

   /* if the Pdu has varied Transmission mode, then it is safe to return TRUE always */
   /* as Transmission mode selecion happens based on the signal filter algo and if the  */
   /* function returns true at wrong time there could be chances that the signal update */
   /* could be missed and transmission mode cannot happen (Autosar Com Use case 3)      */
   /* This check has to the first check as this has the highest priority */
    /* this part checks whether the configured Pdu is Periodic and it is scheduled to be Transmitted in the coming cycle */
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
    /* In normal scenario, it is not intended that caller of Com_IsTxScheduled is called in lesser task cycle than Com_MainfunctionTx
     * But if this is the case, then Com_IsTxScheduled returns true when TxIpduRamPtr->Com_Tick_Tx = 2, 1 or 0,
     * Hence Caller has to update the data a few cycles earlier */
    if (ComCallerTaskCycle < (COM_TX_TIME_BASE_IN_MS))
#endif
    {
        /* if(TxIpduRamPtr->Com_TransMode.LatestTransMode == COM_TXMODE_PERIODIC) */
        if((Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) == (uint8)COM_TXMODE_PERIODIC) && (TxIpduRamPtr->Com_Tick_Tx > 1 ) )
        {
            IsTxScheduled = COM_FALSE;
        }
        else
        {
            IsTxScheduled = COM_TRUE;
        }
    }
#ifdef COM_TXSCHEDULED_DIFF_TIMEBASE
    else
    {
        /* if(TxIpduRamPtr->Com_TransMode.LatestTransMode == COM_TXMODE_PERIODIC) */
        if((Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) == (uint8)COM_TXMODE_PERIODIC) && (ticksinMs_u16 > ComCallerTaskCycle ) )

        {
            IsTxScheduled = COM_FALSE;
        }
        else
        {
            IsTxScheduled = COM_TRUE;
        }
    }
#endif
return IsTxScheduled;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
/* FC_VariationPoint_END */

#ifdef COM_PROVIDE_IPDU_STATUS
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
/***************************************************************************************************
 Function name    : COM_ProvideTxIpduStatus
 Syntax           : boolean COM_ProvideTxIpduStatus(PduId)
 Description      : The service Com_ProvideTxIpduStatus returns the status of Tx I-PDU referenced by PduId.
 Parameter        : PduId
 Return value     : boolean
 ***************************************************************************************************/
FUNC(boolean,COM_CODE) Com_ProvideTxIpduStatus(VAR(PduIdType, AUTOMATIC) PduId)
{
    VAR(boolean, AUTOMATIC) pduStatus_b;

    /* If the Pdu Id passed is not an Tx Ipdu Id or Ipdu is not started, then status false is returned */
    if (PduId < COM_GET_NUM_TX_IPDU)
    {
        /* If PB variant is selected, then PduId which is passed to this function will be changed
         * to internal Id which is generated through configuration
         * If PC variant is selected, then no mapping table will be used. */
        PduId = COM_GET_TX_IPDU_ID(PduId);

        /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
         * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
         * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
         * Hence the warning is suppressed. */
        pduStatus_b = COM_CheckTxIPduStatus(PduId);
    }
    else
    {
        pduStatus_b = COM_FALSE;
    }

    return(pduStatus_b);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /* #ifdef COM_PROVIDE_IPDU_STATUS */

