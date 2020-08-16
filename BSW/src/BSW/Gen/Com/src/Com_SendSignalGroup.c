

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/

#ifdef COM_TX_SIGNALGROUP
/***************************************************************************************************
 Function name    : Com_SendSignalGroup
 Syntax           : uint8 Com_SendSignalGroup(Com_SignalGroupIdType SignalGroupId)
 Description      : Service copies the content of the associated shadow buffer to the associated
                    I-PDU buffer.Prior to this call, all group signals should be updated in the
                    shadow buffer by the call of Com_UpdateShadowSignal.
 Parameter        : SignalGroupId -> Id of the SignalGroup
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE/COM_BUSY
 ***************************************************************************************************/
# define COM_START_SEC_CODE
# include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_SendSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{
    Com_TxSigGrpConstPtrType TxSigGrpConstPtr; /* Local pointer to Tx SignalGroup static configuration */
    Com_TxIpduRamPtrType     TxIpduRamPtr;     /* Local pointer to Tx IPdu        static configuration */
    VAR(uint8, AUTOMATIC)    Status;           /* Return status                                        */

    /* Start: Det */

    COM_REPORT_ERROR1((Com_Uninit_Flag == COM_UNINIT), COMServiceId_SendSignalGroup, COM_E_UNINIT)

    COM_REPORT_ERROR1((SignalGroupId >= COM_GET_NUM_TX_SIGNALGRP), COMServiceId_SendSignalGroup, COM_E_PARAM)

    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
    * to internal Id which is generated through configuration
    * If PC variant is selected, then no mapping table will be used. */
    SignalGroupId    = COM_GET_TXSIGNALGRP_ID(SignalGroupId);

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA( SignalGroupId );
    TxIpduRamPtr     = &COM_GET_TXPDURAM_S( TxSigGrpConstPtr->IpduRef );

    /* Proceed only if Large Data tranmission is not in Progress */
    if(Com_GetRamValue(TXIPDU,_LARGEDATAINPROG,TxIpduRamPtr->Com_TxFlags) != COM_TRUE)
    {
        Status = Com_InternalSendSignalGroup(SignalGroupId);
    }
    else
    {
        Status = COM_BUSY;
    }

    return (Status);
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

# define COM_START_SEC_CODE
# include "Com_MemMap.h"
/***************************************************************************************************
 Function name    : Com_InternalSendSignalGroup
 Syntax           : uint8 Com_InternalSendSignalGroup(Com_SignalGroupIdType SignalGroupId)
 Description      : Service copies the content of the associated shadow buffer to the associated
                    I-PDU buffer.Prior to this call, all group signals should be updated in the
                    shadow buffer by the call of Com_UpdateShadowSignal.
                    This is an internal function to update the signal group.
                    This function doesnt do DET checks, these checks are done in the API itself.
 Parameter        : SignalGroupId -> Internal Id of the SignalGroup (relevant for post-build)
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE
 ***************************************************************************************************/
FUNC(uint8, COM_CODE) Com_InternalSendSignalGroup(VAR(Com_SignalGroupIdType, AUTOMATIC) SignalGroupId)
{
#ifdef COM_SigGrpTriggeredOnChange
    Com_TxSigGrpRamPtrType TxSigGrpRamPtr;     /* Local pointer to hold the address of SignalGroup status structure */
#endif
    Com_TxSigGrpConstPtrType TxSigGrpConstPtr; /* Local pointer to hold the address of Tx SignalGroup static configuration */
#if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY)
    Com_TxIpduConstPtrType TxIPduConstPtr;     /* Local pointer to hold the address of Tx ipdu static configuration */
#endif /* #if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY) */
    Com_TxIpduRamPtrType TxIpduRamPtr;           /* Local pointer to hold the address of Tx ipdu status structure */
    VAR(uint16_least, AUTOMATIC) IpduId_ui;
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;
    VAR(uint8, AUTOMATIC) Status;              /* Return status */
    VAR(uint8, AUTOMATIC) transferProperty_u8;
    VAR(boolean, AUTOMATIC) TransProp_bool;
#ifdef COM_TxFilters
    /* To check if the current signal update has changed the TMS of the IPDU */
    VAR(boolean, AUTOMATIC) TMSChangeIndication;
#endif /* #ifdef COM_TxFilters */
#ifdef COM_TX_SIGNALGROUP_ARRAY
    VAR(boolean, AUTOMATIC) ConstIsSigGrpOfArrayType_b;
#endif

    Status         = E_OK;
    TransProp_bool = COM_FALSE;

    TxSigGrpConstPtr = COM_GET_TXSIGGRP_CONSTDATA(SignalGroupId);

    IpduId_ui = TxSigGrpConstPtr->IpduRef;
#if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY)

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(IpduId_ui);

#endif /* #if defined (COM_TxSigGrpUpdateBit) || defined (COM_SIGNALGROUPGATEWAY) */
    TxIpduRamPtr = &COM_GET_TXPDURAM_S(IpduId_ui);
    ConstByteValue_u8 = TxSigGrpConstPtr->txSignalGrpFields;
#ifdef COM_TxFilters
    TMSChangeIndication = COM_FALSE;
#endif/* #ifdef COM_TxFilters */
#ifdef COM_SigGrpTriggeredOnChange
    TxSigGrpRamPtr = &COM_GET_TXSIGGRPFLAG(SignalGroupId);
#endif

#ifdef COM_TX_SIGNALGROUP_ARRAY
    ConstIsSigGrpOfArrayType_b = Com_GetValue(TXSIGGRP,_ARRAYACCESS,TxSigGrpConstPtr->txSignalGrpFields);
#endif

    /* Pack: Shadow buffer to Ipdu Buffer */
    SchM_Enter_Com_TxIpduProtArea(SENDSIGNALGRP);

#ifdef COM_TX_SIGNALGROUP_ARRAY
    if ( ConstIsSigGrpOfArrayType_b == COM_FALSE )
#endif
    {
        Com_ShadowBuffToIpduBuff(SignalGroupId);
    }
#ifdef COM_TX_SIGNALGROUP_ARRAY
    else
    {
        /* GroupSignal's SignalInitValues are already updated into the IPduBuffer
         * in Com_SendSignalGroupArray() */
    }
#endif

#ifdef COM_TxSigGrpUpdateBit
    /* Update bit if this bit is configured */
    /* if(TxSigGrpConstPtr->txSignalGrpFields.UpdBitConf != COM_FALSE) */
    if(Com_GetValue(TXSIGGRP,_UPDBITCONF,TxSigGrpConstPtr->txSignalGrpFields))
    {
        VAR(PduLengthType, AUTOMATIC) ByteNo_u8;
        /*Find the Byte No, where the Update bit lies */
        ByteNo_u8 = (PduLengthType)((TxSigGrpConstPtr->Update_Bit_Pos)>>3u);
        /* This macro sets the update bit value at the Update bit position */
        Com_SetUpdateBitValue(TxIPduConstPtr,TxSigGrpConstPtr->Update_Bit_Pos,ByteNo_u8)
    }
#endif
    SchM_Exit_Com_TxIpduProtArea(SENDSIGNALGRP);

    transferProperty_u8 = Com_GetValue(TXSIGGRP,_TP,ConstByteValue_u8);

    /*if (TxSigGrpConstPtr->txSignalGrpFields.TransProp == (uint8)COM_TRIGGERED)*/
    if (transferProperty_u8 == (uint8)COM_TRIGGERED)
    {
        TransProp_bool = COM_TRUE;
    }
#ifdef COM_SigGrpTriggeredOnChange
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
     * to store and read here, may read obsolete value. Evaluation(or no evaluation) of 2nd operand
     * shall not impact the system behaviour. Hence suppressed. */
    /* if (TxSigGrpConstPtr->txSignalGrpFields.TransProp == (uint8)COM_TRIGGERED_ON_CHANGE) */
    else if ( ( transferProperty_u8 == (uint8)COM_TRIGGERED_ON_CHANGE ) &&
              ( Com_GetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr ->txSigGrpRAMFields) != COM_FALSE ) )
    {
        TransProp_bool = COM_TRUE;
        /* Reset the flag, so that next transmission is not triggered unless one of the group signal value
         * changes
         */
        /* TxSigGrpRamPtr ->txSigGrpRAMFields.TrigOnChange = COM_FALSE */
        Com_SetRamValue(TXSIGGRP,_TRIGONCHNG,TxSigGrpRamPtr->txSigGrpRAMFields,COM_FALSE);
    }
#endif /* #ifdef COM_SigGrpTriggeredOnChange */
    else
    {
        /* Transfer property = PENDING */
        /* Do nothing */
    }

    /* As per SWS_Com_00334: The AUTOSAR COM module shall update the values of its internal buffers
     * even for stopped I-PDUs.
     * So the IPDU Group status is checked only after SignalGroup packing is done. */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckTxIPduStatus(IpduId_ui))
    {
#if (defined(COM_SIGNALGROUPGATEWAY) || defined(COM_TxIPduTimeOut))
            VAR(boolean, AUTOMATIC) timeOutEnableStatus_b;
            timeOutEnableStatus_b = Com_GetValue(TXSIGGRP,_TOENABLED,ConstByteValue_u8);
#endif /* #if defined(COM_SIGNALGROUPGATEWAY) || defined(COM_TxIPduTimeOut) */

#ifdef COM_TxFilters
        /* Tx Filters are enabled and hence based on the TMC, TMS will be calculated.
         * Evaluate TMS only if IPDU doesnt have a fixed TM during configuration time and the signal contributes
         * to TMS calculation.
         */
        if (Com_GetValue(TXSIGGRP,_FILTEREVALREQ,TxSigGrpConstPtr->txSignalGrpFields) != COM_FALSE)
        {
            /* If TMS changes, Com_SigTxChangeMode() returns COM_TRUE */
            TMSChangeIndication = Com_SigTxChangeMode((Com_IpduIdType)IpduId_ui, (uint16)SignalGroupId,
                                                      (Com_SigMaxType)0, COM_TRUE);
        }
#endif /* #ifdef COM_TxFilters */


#ifdef COM_SIGNALGROUPGATEWAY
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
#endif /* #ifdef COM_SIGNALGROUPGATEWAY */
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
            if(((TransProp_bool != COM_FALSE) &&
                (Com_GetRamValue(TXIPDU,_LATESTMODE,TxIpduRamPtr->Com_TransMode) <= COM_TXMODE_MIXED))
#ifdef COM_TxFilters
                || (TMSChangeIndication == COM_TRUE)
#endif
              )
            {
                /* All unused flags are reset here */
                Com_SendIpduInfo sendIpduFlag_u16 = COM_CLEAR_SENDIPDU_FLAGS;

                /* this flag will be set,as call happens from Com_SendSignalGroup/Com_SendSignalGroupArray */
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
        Status = COM_SERVICE_NOT_AVAILABLE;
    }

    return (Status);
}
# define COM_STOP_SEC_CODE
# include "Com_MemMap.h"

#endif /* #ifdef COM_TX_SIGNALGROUP */


