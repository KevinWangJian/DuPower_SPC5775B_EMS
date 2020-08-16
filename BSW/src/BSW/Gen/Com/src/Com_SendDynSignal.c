
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
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE
 ***************************************************************************************************/
#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_SendDynSignal(VAR(Com_SignalIdType, AUTOMATIC) SignalId, P2CONST(void, AUTOMATIC, COM_APPL_DATA) SignalDataPtr,
        VAR(uint16, AUTOMATIC) Length)
{
    Com_TxIpduRamPtrType TxIpduRamPtr;    /* Local pointer to hold the Tx ipdu status information */
    Com_TxIpduConstPtrType TxIPduConstPtr;
    Com_TxSigConstPtrType TxSigConstPtr;
    VAR(uint16_least, AUTOMATIC) IpduId_ui;
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;
    VAR(uint8, AUTOMATIC) Status;  /* Return status */
    VAR(uint8, AUTOMATIC) Type;
    VAR(boolean, AUTOMATIC) TransProp_bool;

#ifdef COM_TxFilters
    /* To check if the current signal update has changed the TMS of the IPDU */
    VAR(boolean, AUTOMATIC) TMSChangeIndication;
#endif /* #ifdef COM_TxFilters */

    /* Start: Det */

    COM_REPORT_ERROR1((Com_Uninit_Flag == COM_UNINIT), COMServiceId_SendDynSignal, COM_E_UNINIT)

    COM_REPORT_ERROR1((SignalId >= COM_GET_NUM_TX_SIGNALS), COMServiceId_SendDynSignal, COM_E_PARAM)

    COM_REPORT_ERROR1((SignalDataPtr == NULL_PTR), COMServiceId_SendDynSignal, COM_E_PARAM_POINTER)

    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */

    SignalId = COM_GET_TXSIGNAL_ID(SignalId);
#ifdef COM_TxFilters
    TMSChangeIndication = COM_FALSE;
#endif/* #ifdef COM_TxFilters */
    Status              = E_OK;
    TransProp_bool      = COM_FALSE;

    TxSigConstPtr       = COM_GET_TXSIG_CONSTDATA(SignalId);

    ConstByteValue_u8   = TxSigConstPtr->General;
    /* Type = TxSigConstPtr->General.Type; */
    Type                = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);

    IpduId_ui           = TxSigConstPtr->IpduRef;

    TxIPduConstPtr      = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

    TxIpduRamPtr        = &COM_GET_TXPDURAM_S(IpduId_ui);

    /* Check whether the large data pdu flag has been reset */
    if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
    {

    /* If the application requests with length greater than the maximum length of the signal */
    if((Length <= TxSigConstPtr->BitSize) && ((uint8)COM_UINT8_DYN == Type))
    {
        VAR(PduLengthType, AUTOMATIC) ByteNo_u8;

        /* Find the ByteNo_u8 of the IPDU buffer */
        /* The locks here is to protect 1. The Tx Ipdu buffer data update, 2. Dynamic signal length update */
        SchM_Enter_Com_TxIpduProtArea(SENDDYNSIGNAL);

#ifdef COM_TxSigUpdateBit
        /*As per COM334: the signal has to be updated in Internal buffer even if IPDU Group is STOPPED*/
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
        if(Length != 0)
        {
            /* Find the ByteNo_u8 of the IPDU buffer */
            ByteNo_u8 = (PduLengthType)(TxSigConstPtr->Bit_Pos >> 3u);
            /* MR12 RULE 11.5 VIOLATION: For SignalDataPtr is defined as void pointer in the AUTOSAR specification,
               so suppressing warning "Cast from a pointer to void to a pointer to object" */
            Com_ByteCopy((TxIPduConstPtr->BuffPtr + ByteNo_u8),(const uint8*)SignalDataPtr,(uint32)Length);
        }

        /* The dynamic Length of the Ipdu, is updated here */
        TxIpduRamPtr->Com_DynLength= Length;
        SchM_Exit_Com_TxIpduProtArea(SENDDYNSIGNAL);

        /* Load txSignalFields value to get the signal transfer property */
        ConstByteValue_u8 = TxSigConstPtr->txSignalFields;
        /* if (TxSigConstPtr->txSignalFields.TransProp == (uint8)COM_TRIGGERED) */
        if (Com_GetValue(TXSIG,_TP,ConstByteValue_u8) == (uint8)COM_TRIGGERED)
        {
            TransProp_bool = COM_TRUE;
        }
        else
        {
            /* Transfer property = PENDING */
            /* Do nothing */
        }

        /* As per SWS_Com_00334: The AUTOSAR COM module shall update the values of its internal buffers
         * even for stopped I-PDUs.
         * So the IPDU Group status is checked only after Signal packing is done. */
        /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
         * calibration object which doesn't change in the course of the Ecu RunTime, so this warning is
         * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
         * suppressed here. */
        if(COM_CheckTxIPduStatus(IpduId_ui))
        {
#if defined(COM_SIGNALGATEWAY) || defined(COM_TxIPduTimeOut)
            VAR(boolean, AUTOMATIC)   timeOutEnableStatus_b;
            timeOutEnableStatus_b = Com_GetValue(TXSIG,_TOENABLED,ConstByteValue_u8);
#endif /* #if defined(COM_SIGNALGATEWAY) || defined(COM_TxIPduTimeOut) */

#ifdef COM_TxFilters
            /* The Dynamic signal can have ALWAYS/NEVER as filter algorithm.
             * Evaluate TMS only if IPDU doesnt have a fixed Transmission Mode during configuration time and
             * the signal contributes to TMS calculation
             */
            /*     if(TxSigConstPtr->txSignalFields.FilterAlgorithm != (uint8)COM_NOTCONFIGURED) */
            if(Com_GetValue(TXSIG,_FILTRALG,ConstByteValue_u8) != (uint8)COM_NOTCONFIGURED)
            {
                /* Com_SigTxChangeMode() returns COM_TRUE, if TMS changes,
                 * Here the value sent is '0' as filter algorithm can only be always/never/One_every_n */
                TMSChangeIndication = Com_SigTxChangeMode((Com_IpduIdType)IpduId_ui,(uint16)SignalId,0,COM_FALSE);
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

                    /* this flag will be set,as call happens from Com_SendDynSignal */
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

                    Com_SendIpdu((PduIdType)IpduId_ui,sendIpduFlag_u16);
                }
            }

        }/*End of If IpduGroupStarted*/
        else
        {
            Status = COM_SERVICE_NOT_AVAILABLE;  /*COM461: Table 9*/
        }
    }
    else
    {
        Status = E_NOT_OK;
    }

    }/* if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != (uint8)COM_TRUE) */
    else
    {
        Status = COM_BUSY;
    }

    return Status;
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif /*#ifdef COM_TX_DYNAMIC_SIGNAL_SUPPORT*/

