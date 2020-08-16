

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_TxConfirmation
 Syntax           : void Com_TxConfirmation(PduIdType TxPduId)
 Description      : Service called by the lower layer after the PDU has been transmitted on the network.
 Parameter        : TxPduId -> Id of the Tx Ipdu
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_TxConfirmation(VAR(PduIdType, AUTOMATIC) TxPduId)
{

    /* Start: Det */
    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_TxConfirmation, COM_E_UNINIT)

    COM_REPORT_ERROR((TxPduId >= COM_GET_NUM_TX_IPDU), COMServiceId_TxConfirmation, COM_E_PARAM)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */
    TxPduId = COM_GET_TX_IPDU_ID(TxPduId);

    /* Check if Ipdu Group is started / Stopped */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckTxIPduStatus(TxPduId))
    {

        /* Call the internal function Com_ProcessTxConfirmation, to process this TxConfirmation */
        Com_ProcessTxConfirmation(TxPduId);
    }
    /*End of Checking IpduGroup Started/Stopped */
}

/* Internal function is called to process the TxConfirmation */
/* MR12 RULE 8.7 VIOLATION: This warning is reported if TP-TxIPdu's are not configured.
 * If TP-TxIPdu's are also configured then below function is called from Com_TpTxConfirmation()
 * which is placed in a different file. So below function shall not be changed to static.
 * Hence this rule is suppressed here. */
FUNC(void, COM_CODE) Com_ProcessTxConfirmation(VAR(PduIdType, AUTOMATIC) TxPduId)
{

    Com_TxIpduRamPtrType TxIpduRamPtr;
    Com_TxIpduConstPtrType TxIPduConstPtr;
    VAR(uint16, AUTOMATIC) ConstByteValue_u16;
#ifdef COM_TxIPduNotification
    VAR(boolean, AUTOMATIC) notifyFlag_b;
#endif /* #ifdef COM_TxIPduNotification */

#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
    VAR(boolean, AUTOMATIC) updBitFlag_b;
#endif /* #if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) */

#ifdef COM_TxIPduNotification
    notifyFlag_b = COM_FALSE;    /* Initializing to COM_FALSE */
#endif /* #ifdef COM_TxIPduNotification */

#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
    updBitFlag_b = COM_FALSE;    /* Initializing to COM_FALSE */
#endif /* #if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) */

    TxIPduConstPtr = COM_GET_TX_IPDU_CONSTDATA(TxPduId);

    TxIpduRamPtr = &COM_GET_TXPDURAM_S(TxPduId);
    ConstByteValue_u16 = TxIPduConstPtr->txIPduFields;

    /*Update the Min Delay Time has to be updated in Com_TxConfirmation() as page number 49 of V3.0 (7.4.5.4)*/
    /* Load the MDT timer, if
     * 1)MDT is configured for the IPdu.
     * 2)MDT is not set to zero, because of Tx timeout.(If Tx timeout happens then MDT timer is set to zero in
     *  cyclic task. In this case,delayed confirmation should not set the MDT again.  )
     */
    SchM_Enter_Com_TxIpduProtArea(TXCONFIRMATION);
    if ((TxIPduConstPtr->Min_Delay_Time_Fact != 0) && (TxIpduRamPtr ->Com_MinDelayTick != 0))
    {
        VAR(boolean, AUTOMATIC) IsGwTxIPdu_b;
#ifdef COM_TXPDU_DEFERREDPROCESSING
        /* If IPdu is transmitted due to event triggered request, then add an offset of 1 from Com_MainfunctionRouteSignals
         * This is required because TxConrimation can come immediately , which loads MDT timer.
         * Now this would be reduced by 1 immediately in next cyclic task, leading to early timeout of MDT timer.
         */
        /* TxIpduRamPtr ->Com_MinDelayTick = TxIPduConstPtr->Min_Delay_Time_Fact + TxIpduRamPtr->Com_TxFlags.EvenTriggeredTx */
        TxIpduRamPtr ->Com_MinDelayTick = TxIPduConstPtr->Min_Delay_Time_Fact ;
#else
    /* If IPdu is transmitted due to event triggered request, then add an offset of 1.
     * This is required because TxConrimation can come immediately , which loads MDT timer.
     * Now this would be reduced by 1 immediately in next cyclic task, leading to early timeout of MDT timer.
     */
    TxIpduRamPtr ->Com_MinDelayTick = (TxIPduConstPtr->Min_Delay_Time_Fact) +
                                      (Com_GetRamValue(TXIPDU,_EVENTTRIG,TxIpduRamPtr->Com_TxFlags) ? 1u : 0u);
#endif /* COM_TXPDU_DEFERREDPROCESSING */

        IsGwTxIPdu_b = Com_GetValue(TXIPDU,_ISGWPDU,ConstByteValue_u16);
        /* As the event transmission from Com_mainfunctionrouteSignals could be asyncrhonous with Com_MainfunctionTx,
         * the MDT value is loaded with an offset 1 to protect counter from early expiry */
        /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
         * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
         * system behaviour. Hence suppressed. */
        if ( ( IsGwTxIPdu_b != COM_FALSE ) &&
             ( Com_GetRamValue(TXIPDU,_GWPDUTRANS,TxIpduRamPtr->Com_TxFlags) == COM_TRUE) )
        {

            TxIpduRamPtr ->Com_MinDelayTick++;
            /* TxIpduRamPtr->Com_TxFlags.EvenTriggeredTx = COM_RESET */
            Com_SetRamValue(TXIPDU,_GWPDUTRANS,TxIpduRamPtr->Com_TxFlags,COM_FALSE);
        }
    }

    if(TxIpduRamPtr->Com_n != 0)
    {
        --TxIpduRamPtr->Com_n;
    }
    if(TxIpduRamPtr->Com_n == 0)
    {
        /* TxIpduRamPtr->Com_TxFlags.TxConfirFlag = COM_SET */
        Com_SetRamValue(TXIPDU,_CONFIR,TxIpduRamPtr->Com_TxFlags,COM_TRUE);  /*This is checked in Com_MainFunctionTx()*/
        /*This Flag has to be set to START only in SendIpdu() i,e just before Sending the IPDU*/
        /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_STOP */
        Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_STOP);
#ifdef COM_TxIPduNotification
        /* if(TxIPduConstPtr->txIPduFields.Signal_Processing == COM_IMMEDIATE) */
        if(Com_GetValue(TXIPDU,_SIGPROC,ConstByteValue_u16) == COM_IMMEDIATE)
        {
            notifyFlag_b = COM_TRUE;
        }
#endif /* #ifdef COM_TxIPduNotification */
#ifdef COM_TxIPduTimeOut
        /* if(TxIPduConstPtr->txIPduFields.NoneModeTimeOut != (uint8)COM_FALSE) */
        if(Com_GetValue(TXIPDU,_NONETOSTATUS,ConstByteValue_u16) != COM_FALSE)
        {
            /* The timer is reset at the TX confirmation for the IPdu with only None mode configured */
            TxIpduRamPtr->Com_TickTxTimeout = TxIPduConstPtr->Timeout_Fact;
            /* TxIpduRamPtr->Com_TxFlags.TickTxTimeout_Flag = COM_START */
            Com_SetRamValue(TXIPDU,_TICKTXTO,TxIpduRamPtr->Com_TxFlags,COM_START);
        }
#endif
        /* If the parameter ComTxIPduClearUpdateBit of an I-PDU is configured to Confirma-tion, the AUTOSAR COM module
         * shall clear all update-bits of all contained signals and signal groups after this I-PDU was sent out
         *  via PduR_ComTransmit, PduR_ComTransmit returned E_OK and the I-PDU was successfully confirmed*/
#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
        /*  if(TxIPduConstPtr->txIPduFields.ClearUpdBit == (uint8)COM_CLRUPDATEBIT_CONFIRMATION)*/
        if(Com_GetValue(TXIPDU,_CLRUPDBIT,ConstByteValue_u16) == (uint16)COM_CLRUPDATEBIT_CONFIRMATION)
        {
            updBitFlag_b = COM_TRUE;
        }
#endif /* #if defined ((COM_TxSigUpdateBit)||defined(COM_TxSigGrpUpdateBit)) */
    }

#if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit))
    if(updBitFlag_b == COM_TRUE)
    {
        Com_ClearUpdateBits(TxIPduConstPtr);
    }
#endif /* #if (defined(COM_TxSigUpdateBit) || defined(COM_TxSigGrpUpdateBit)) */
    SchM_Exit_Com_TxIpduProtArea(TXCONFIRMATION);


#ifdef COM_TxIPduNotification
    if(notifyFlag_b == COM_TRUE)
    {
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

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

