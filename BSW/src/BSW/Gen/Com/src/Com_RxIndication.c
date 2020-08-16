

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Com_Priv.h"
/**************************************************************************************************/
/* defines                                                                                        */
/**************************************************************************************************/
/* The following defines are applicable only within this file */
#define UPDATEBIT_NOT_APPLICABLE    0x00u
#define UPDATEBIT_APPLICABLE        0x01u
#define UPDATEBIT_SET               0x02u
#define UPDATEBIT_RESET             0x03u


static INLINE FUNC(void, COM_CODE) Com_ProcessSignal(VAR(PduIdType, AUTOMATIC) ComRxPduId,P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)PduInfoPtr );
#ifdef COM_RX_SIGNALGROUP
static INLINE FUNC(void, COM_CODE) Com_ProcessSignalGroup(VAR(PduIdType, AUTOMATIC) ComRxPduId,P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)PduInfoPtr);
#endif

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Com_RxIndication
 Syntax           : void Com_RxIndication(PduIdType RxPduId,const PduInfoType *PduInfoPtr)
 Description      : Service called by the lower layer after an I-PDU has been received.
 Parameter        : RxPduId,PduInfoPtr
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_RxIndication(VAR(PduIdType, AUTOMATIC) RxPduId,P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{
    /* To Remove Compiler Warning */
    Com_RxIpduConstPtrType RxIPduConstPtr;
    Com_RxIpduRamPtrType RxIPduRamPtr;
    VAR(uint8, AUTOMATIC) ConstByteValue_u8;

    /* Start: Det */
    COM_REPORT_ERROR((Com_Uninit_Flag == COM_UNINIT), COMServiceId_RxIndication, COM_E_UNINIT)

    COM_REPORT_ERROR((RxPduId >= COM_GET_NUM_RX_IPDU), COMServiceId_RxIndication, COM_E_PARAM)

    COM_REPORT_ERROR((PduInfoPtr == NULL_PTR), COMServiceId_RxIndication, COM_E_PARAM_POINTER)
    /* End: Det */

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */
    RxPduId = COM_GET_RX_IPDU_ID(RxPduId);

    RxIPduConstPtr    = COM_GET_RX_IPDU_CONSTDATA(RxPduId);

    RxIPduRamPtr      = &COM_GET_RXPDURAM_S(RxPduId);
    ConstByteValue_u8 = RxIPduConstPtr->rxIPduFields;

    /* Check if the Ipdu group containing this IPDU is started */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(COM_CheckRxIPduStatus(RxPduId))
    {
        VAR(boolean, AUTOMATIC) IPduSigProcessing_b;

        IPduSigProcessing_b = Com_GetValue(RXIPDU,_SIGPROC,ConstByteValue_u8);

        SchM_Enter_Com_RxPduBuffer();

        /* The AUTOSAR COM module does not copy or handle additional received data for not configured signals in case
         * the received data length is greater than expected. */
        if ( PduInfoPtr->SduLength <= RxIPduConstPtr->Size )
        {
            RxIPduRamPtr->RxIPduLength = PduInfoPtr->SduLength;
        }
        else
        {
            RxIPduRamPtr->RxIPduLength = RxIPduConstPtr->Size;
        }

#ifdef COM_RxIPduDeferredProcessing
        if (IPduSigProcessing_b != COM_IMMEDIATE)
        {
            /* Now Copy the received Data into the RxIPDU buffer */
            Com_ByteCopy(RxIPduConstPtr->BuffPtr,(uint8*)(PduInfoPtr ->SduDataPtr),RxIPduRamPtr->RxIPduLength);
        }
#endif /* #ifdef COM_RxIPduDeferredProcessing */
        /* RxIPduRamPtr ->RxFlags.RxIndicationFlag = COM_SET */
        Com_SetRamValue(RXIPDU,_INDICATION,RxIPduRamPtr ->RxFlags,COM_TRUE);
        SchM_Exit_Com_RxPduBuffer();

        /* if(RxIPduConstPtr->rxIPduFields.Signal_Processing == COM_IMMEDIATE) */
        if (IPduSigProcessing_b == COM_IMMEDIATE)
        {
            Com_ProcessRxIPdu(RxPduId,PduInfoPtr);
        }
    }
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

/***************************************************************************************************
 Function name    : Com_ProcessRxIPdu
 Syntax           : void Com_ProcessRxIPdu(PduIdType ComRxPduId,const uint8 *PduInfoPtr)
 Description      : Service called by the lower layer after an I-PDU has been received.
 Parameter        : ComRxPduId -> Id of the Rx ipdu
                  : PduInfoPtr -> Pointer to the buffer +sdu length where the received data is stored
 Return value     : None
 ***************************************************************************************************/
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(void, COM_CODE) Com_ProcessRxIPdu(VAR(PduIdType, AUTOMATIC) ComRxPduId,P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr)
{

    Com_RxIpduConstPtrType RxIPduConstPtr;
#if defined(COM_RxSignalNotify)    || defined(COM_RxSignalGrpNotify)
    VAR(uint32, AUTOMATIC) SigOrSigGrpId;
#endif
#ifdef COM_RxSignalGrpNotify
    Com_RxSigGrpConstPtrType RxSigGrpConstPtr;
    Com_RxSigGrpRamPtrType RxSigGrpRamPtr;
#endif
#ifdef COM_RxSignalNotify
    Com_RxSigConstPtrType RxSigConstPtr;
    Com_RxSigRamPtrType RxSigRamPtr;
#endif

    /* Initialisation of local variables */

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(ComRxPduId);

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    /* Initialize the counter only if the RxIPdu has gateway signals or signal groups */
    if ( COM_TRUE == Com_GetValue( RXIPDU, _ISGWPDU, RxIPduConstPtr->rxIPduFields ) )
    {
        COM_GET_NUM_OF_GWSIG_UPDATED( ComRxPduId ) = 0;
    }
#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)*/

    /* if IPdu callout is configured for the Pdu, Callout is called,
     * if it returns false,no further processing is done */
#ifdef COM_RxIPduCallOuts
    if(RxIPduConstPtr->CallOut != NULL_PTR)
    {
        if(COM_FALSE == RxIPduConstPtr->CallOut(ComRxPduId,(const uint8 *)(PduInfoPtr->SduDataPtr)))
        {
            return;
        }
    }
#endif /* #ifdef COM_RxIPduCallOuts */

    /* Process all the Signals in the IPdu
     * 1. Update bit validation for signals with Update bit configured
     * 2. Timeout monitoring for Signals with Update bit
     * 3. Data Invalid value validation
     * 4. Validation of filters for Signals with filter configured */
    if(RxIPduConstPtr->No_Of_Sig_Ref > 0)
    {
        Com_ProcessSignal(ComRxPduId,PduInfoPtr);
    }


#ifdef COM_RX_SIGNALGROUP

    /* Process all the Signal groups in the IPdu
     * 1. Update bit validation for signal groups with Update bit configured
     * 2. Timeout monitoring for signal groups with Update bit
     * 3. Data Invalid value validation for group signals with Invalid value configured */
    if(RxIPduConstPtr->No_Of_SigGrp_Ref >0)
    {
        Com_ProcessSignalGroup(ComRxPduId,PduInfoPtr);
    }

#endif /* #ifdef COM_RX_SIGNALGROUP */

#if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY)
    /* Check if the RxIPdu has gateway signals or signal groups */
    if ( COM_TRUE == Com_GetValue( RXIPDU, _ISGWPDU, RxIPduConstPtr->rxIPduFields ) )
    {
        /* This part of code updates the Rx Gateway queue If
         * 1. Any Gw signal in the Ipdu is updated in the signal buffer
         * 2. Already an entry into the queue does not exist
         */
        /* MR12 RULE 13.5 VIOLATION:  */
        if( (COM_GET_NUM_OF_GWSIG_UPDATED(ComRxPduId) > 0u) &&
            (Com_GetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(ComRxPduId).RxFlags) != COM_TRUE))
        {

            SchM_Enter_Com_RxSigGwQueueProtArea();
            /* There is a new reception of Ipdu caused a new update on the Signal, Hence set the flag to process in next
             * Com_MainfunctionRouteSignals
             * Once the Ipdu is processed, this flag will hold COM_TRUE in Com_MainfunctionRouteSignals
             * If any new receptions are invoked on the same Ipdu before the next processing is done,
             * 1. Signal buffers are updated
             * 2. Queue is not updated */
            (void)Com_WriteSigGwReceiveQueue(ComRxPduId);
            /* There is a new reception of Ipdu/ Ipdu timeout caused a new update on the Signal, Hence set the flag to
             *  process in next Com_MainfunctionRouteSignals
             * Once the Ipdu is processed, this flag will hold COM_TRUE in Com_MainfunctionRouteSignals
             * If any new receptions are invoked on the same Ipdu before the next processing is done,
             * 1. Signal buffers are updated
             * 2. Queue is not updated */
            Com_SetRamValue(RXIPDU,_GWPDU_TOBEPROCESSED,COM_GET_RXPDURAM_S(ComRxPduId).RxFlags,COM_TRUE);
            SchM_Exit_Com_RxSigGwQueueProtArea();
        }
    }
#endif /* #if defined (COM_SIGNALGATEWAY) || defined (COM_SIGNALGROUPGATEWAY) */


    /* Ipdu notification is called for the Ipdu */
#ifdef COM_RxIPduNotification
    if(RxIPduConstPtr->RxNotification_Cbk != NULL_PTR)
    {
        RxIPduConstPtr->RxNotification_Cbk();
    }
#endif

    /* Signal notifications are called for all the signals with notifications configured */
    /* if(RxIPduConstPtr->rxIPduFields.Notify_Cbk == (uint8)COM_SET) */
    if(Com_GetValue(RXIPDU,_NOTIFCBK,RxIPduConstPtr->rxIPduFields) == COM_TRUE)
    {
#ifdef COM_RxSignalNotify

        RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);


        RxSigRamPtr      = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
        for(SigOrSigGrpId = RxIPduConstPtr->No_Of_Sig_Ref; SigOrSigGrpId != 0u; SigOrSigGrpId--)
        {
            /* if((RxSigConstPtr->Notification_Cbk != NULL_PTR)&&
             * (RxSigConstPtr ->rxSigRAMFields.SigNotify_Flag == COM_TRUE)) */
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
             * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
             * system behaviour. Hence suppressed. */
            if((RxSigConstPtr->Notification_Cbk != NULL_PTR)
                    && (Com_GetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields) == COM_TRUE) )
            {

                RxSigConstPtr->Notification_Cbk();
                /* RxSigConstPtr ->rxSigRAMFields.SigNotify_Flag = COM_RESET */
                Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr->rxSigRAMFields,COM_FALSE);
            }

            RxSigConstPtr++;
            RxSigRamPtr++;
        }
#endif /* COM_RxSignalNotify */

        /* Signal group notifications are called for all the signal groups with notifications configured */
#ifdef COM_RxSignalGrpNotify

        RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);

        RxSigGrpRamPtr = &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);
        for(SigOrSigGrpId = RxIPduConstPtr->No_Of_SigGrp_Ref;SigOrSigGrpId !=0u;SigOrSigGrpId--)
        {
            /* if((RxSigGrpConstPtr->Notification_Cbk != NULL_PTR)&&
             * (RxSigGrpRamPtr->rxSigGrpRAMFields.SigGrpNotify_Flag == COM_TRUE)) */
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
             * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
             * system behaviour. Hence suppressed. */
            if((RxSigGrpConstPtr->Notification_Cbk != NULL_PTR)
                    && (Com_GetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields)== COM_TRUE) )
            {

                RxSigGrpConstPtr->Notification_Cbk();
                /* RxSigGrpRamPtr->rxSigGrpRAMFields.SigGrpNotify_Flag = COM_FALSE */
                Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_FALSE);
            }
            RxSigGrpConstPtr++;
            RxSigGrpRamPtr++;
        }
#endif /* #ifdef COM_RxSignalGrpNotify */
    } /* if(RxIPduConstPtr->rxIPduFields.Notify_Cbk == (uint8)COM_SET) */

}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"

static INLINE FUNC(void, COM_CODE) Com_ProcessSignal(VAR(PduIdType, AUTOMATIC) ComRxPduId, P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA) PduInfoPtr )
{

#ifdef COM_RxSigUpdateTimeout
    P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST) SigTimeOutConfigPtr;
    P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) SigTimeOutTicksPtr;
    VAR(uint8, AUTOMATIC) UpdateBitStatus;
#endif /* #ifdef COM_RxSigUpdateTimeout */

    Com_RxIpduConstPtrType RxIPduConstPtr;
    Com_RxSigConstPtrType RxSigConstPtr;
    Com_RxSigRamPtrType RxSigRamPtr;
    VAR(Com_SignalIdType, AUTOMATIC) SigId_u32;
    VAR(uint16_least, AUTOMATIC) limit_ui;
    VAR(boolean, AUTOMATIC) copySignal_b;   /* This variable is used to decide whether to copy the new value of the signal into signal buffer or not */
    VAR(boolean, AUTOMATIC) ProcessSignal_b;

    RxSigConstPtr = (Com_RxSigConstPtrType) NULL_PTR;

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(ComRxPduId);

#ifdef COM_RxSigUpdateTimeout
    SigTimeOutConfigPtr = NULL_PTR;
    SigTimeOutTicksPtr = NULL_PTR;
    UpdateBitStatus = UPDATEBIT_NOT_APPLICABLE;
#endif /* #if (defined(COM_RxSigUpdateTimeout) || defined(COM_RxSigGrpUpdateTimeout)) */

#ifdef COM_RxSigUpdateTimeout
    /* If this IPDU has signals with update-bits , initialise the pointers
     * Separate deadline monitoring should be performed for signals with update-bit
     * Deadline monitoring should not be done if it is disabled
     */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
     * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
     * system behaviour. Hence suppressed. */
    if ((RxIPduConstPtr->SignalTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(ComRxPduId)) )
    {

        /* Update the variable UpdateBitStatus with value UPDATEBIT_APPLICABLE
         * ie atleast one of the signal has configured both update-bit and deadline monitoring.
         */
        UpdateBitStatus = UPDATEBIT_APPLICABLE;
        SigTimeOutConfigPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutInfo_Ref;
        SigTimeOutTicksPtr = RxIPduConstPtr->SignalTimeout_Ref->TimeoutTicks_p;
    }
#endif /* #ifdef COM_RxSigUpdateTimeout */


    limit_ui       = (uint32)RxIPduConstPtr->RxSigId_Index + (uint32)RxIPduConstPtr->No_Of_Sig_Ref;
    RxSigRamPtr   = &COM_GET_RXSIGNALFLAG(RxIPduConstPtr->RxSigId_Index);
    RxSigConstPtr = COM_GET_RXSIG_CONSTDATA(RxIPduConstPtr->RxSigId_Index);

    for(SigId_u32 = RxIPduConstPtr->RxSigId_Index; SigId_u32 < limit_ui; SigId_u32++)
    {
        /* Initialise to TRUE ie copy the new value of the signal into signal buffer */
        copySignal_b    = COM_TRUE;
        ProcessSignal_b = COM_TRUE;

#ifdef COM_RxSigUpdateBit
        /* Check for the update bit if configured */
        /* if(RxSigConstPtr->General.UpdBitConf != COM_FALSE) */
        if(Com_GetValue(GEN,_UPDBITCONF,RxSigConstPtr->General))
        {
            VAR(PduLengthType, AUTOMATIC) ByteNo_u8;
            VAR(boolean, AUTOMATIC)       updateBitValue_b;

            ByteNo_u8 = (PduLengthType)(RxSigConstPtr->Update_Bit_Pos >>3u);
            updateBitValue_b = Com_GetUpdateBitValue(PduInfoPtr->SduDataPtr,RxSigConstPtr->Update_Bit_Pos,ByteNo_u8);
            /* The data byte containing update bit is not received */
            /* This macro will get the Update bit status */
            /* Start: Check if the Update bit is SET or NOT */
            if( ((ByteNo_u8+1u) <= PduInfoPtr->SduLength) && (updateBitValue_b == COM_FALSE) )
            {
                /* Since update bit is not SET Discard the signal but return Old value */
                copySignal_b    = COM_FALSE;
                ProcessSignal_b = COM_FALSE;
                /* RxSigConstPtr ->rxSigRAMFields.SigNotify_Flag = COM_RESET */
                Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr ->rxSigRAMFields,COM_FALSE);

            }
            /* If the update bit is not received with the Rx Ipdu, Assume that the update bit is set
             * AR421 requirement - [SWS_Com_00794] */
#ifdef COM_RxSigUpdateTimeout
            /* Update-bit set */
            else
            {
                /* Check if deadline monitoring needs to be performed for signals with update-bit, within
                 * this IPDU.
                 * This variable would be set UBDATEBIT_APPLICABLE only if at least one the signal within
                 * the IPDU has configured update-bit & timeout value and deadline monitoring for IPDU
                 * is not disabled.
                 */
                if (UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE)
                {
                    /* update-bit is set for the signal */
                    UpdateBitStatus = UPDATEBIT_SET;
                }
            }/* End of Check if the Update bit is SET or NOT */
#endif /* #ifdef COM_RxSigUpdateTimeout */

#ifdef COM_RxSigUpdateTimeout
            /* Check if deadline monitoring needs to be performed for signals with update-bit, within
             * this IPDU.
             * This variable would be set UBDATEBIT_APPLICABLE only if atleast one the signal within
             * the IPDU has configured update-bit & timeout value and deadline monitoring for IPDU
             * is not disabled.
             */
            if (UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE)
            {
                /* check if present signal with update-bit has configured time out.
                 * Only the signals with update-bit and configured timeout will be present in structure
                 * Com_SignalTimeoutInfo.
                 */

                if (SigTimeOutConfigPtr->SigId == SigId_u32)
                {
                    if (UpdateBitStatus == UPDATEBIT_SET)
                    {
                        /* Reload the timer for signal with TimeOut value
                         * Timer should be reloaded only if corresponding update-bit is set for the signal
                         * It is ensured by the code generator that if TimeOut value is zero, then the
                         * signal is not considered for deadline monitoring and hence an entry is the
                         * structure Com_SignalTimeoutInfo is not present.
                         * Hence there is no need to check for zero value of TimeOut.
                         */
                        SchM_Enter_Com_RxSigToTicks();
/* FC_VariationPoint_START */
#if (COM_ENABLE_JITTERFLITER == STD_ON)
                        /* CC requirements:
                         * An extra cycle is added to the timeout value after a PDU has been received incase filter is ON
                         * Provides a chance incase of jitter( extra cycle is added in normal case and hence
                         if JITTERFILTER is enabled extra two cycles are added)
                         */

                        (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 2;
#else
 /* FC_VariationPoint_END */
                        /* Extra cycle is added to prevent early timeouts */
                        (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 1;
/* FC_VariationPoint_START */
#endif /* #ifdef COM_ENABLE_JITTERFLITER */
/* FC_VariationPoint_END */
                        SchM_Exit_Com_RxSigToTicks();
                    }
                    /* Increment pointers to refer next signal with update-bit & configured timeout
                     * (within this IPDU)
                     */
                    SigTimeOutTicksPtr++;
                    SigTimeOutConfigPtr++;
                }
                /* Reset the status, after processing it.
                 * It will be set accordingly, in the next iteration of the loop.
                 */
                UpdateBitStatus = UPDATEBIT_RESET;

            } /* if (UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE) */
#endif /* #ifdef COM_RxSigUpdateTimeout */

        }
#endif /* #ifdef COM_RxSigUpdateBit */

        {
            VAR(Com_SigMaxType, AUTOMATIC) RxNewVal;
            VAR(PduLengthType, AUTOMATIC) SigLastByteNo;
            VAR(uint8, AUTOMATIC)         Type;
            VAR(uint8, AUTOMATIC)         ConstByteValue_u8;
            VAR(Com_BitsizeType, AUTOMATIC) Size;
            VAR(uint8, AUTOMATIC)  SigEndianess;

            ConstByteValue_u8 = RxSigConstPtr->General;

            SigEndianess = Com_GetValue(GEN,_ENDIANESS,ConstByteValue_u8);

            /* Type = RxSigConstPtr->General.Type */
            Type = Com_GetValue(GEN,_TYPE,ConstByteValue_u8);
            RxNewVal = 0;

#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            if ( Type != COM_UINT8_DYN )
#endif
            {
                Size = RxSigConstPtr->BitSize;
            }
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
            else
            {
                PduLengthType StartByteNo;

                /* Calculate Dynamic Signal Start Position */
                StartByteNo = ( RxSigConstPtr->Bit_Pos >> 3u );

                /* Check if Dynamic Signal has been received with atleast one byte */
                if ( COM_GET_RXPDURAM_S(ComRxPduId).RxIPduLength > StartByteNo )
                {
                    /* Calculate its received length */
                    Size = (Com_BitsizeType)( COM_GET_RXPDURAM_S(ComRxPduId).RxIPduLength - StartByteNo );
                }
                else
                {
                    /* If it is not received, neither extract nor copy Dynamic Signal */
                    Size = 0u;
                }
            }
#endif

            /* get the byte till where the signal value is spanning in the Rx IPdu
             * LITTLE-ENDIAN: MSB > LSB
             * BIG-ENDIAN: LSB > MSB
             */
            if (SigEndianess == COM_LITTLEENDIAN)
            {
                if((Type == (uint8)COM_UINT8_N) || (Type == (uint8)COM_UINT8_DYN))
                {
                    SigLastByteNo = (PduLengthType)(((RxSigConstPtr->Bit_Pos+(RxSigConstPtr->BitSize*8)) -1) >> 3u);
                }
                else
                {
                    SigLastByteNo = (PduLengthType)(((RxSigConstPtr->Bit_Pos+RxSigConstPtr->BitSize) -1) >> 3u);
                }
            }
            /* Big endian, Array type signals will always be Big endian */
            else
            {
                SigLastByteNo = (PduLengthType)(RxSigConstPtr->Bit_Pos >> 3u);
            }
            /* Check if the Signal is part of the received rx pdu length */
            if ( (Type != (uint8)COM_UINT8_DYN) && ((SigLastByteNo + 1u) > PduInfoPtr->SduLength) )
            {
                /* Signal is not received or received partially, Ignore further processing */
                ProcessSignal_b = COM_FALSE;
                copySignal_b    = COM_FALSE;
                /* RxSigConstPtr ->rxSigRAMFields.SigNotify_Flag = COM_FALSE */
                Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr ->rxSigRAMFields,COM_FALSE);
            }
            /* 1. For signals with update bit;this part will be executed when the Update bit is SET
             * 2. For signals without update bit,process the signal further */
            if (ProcessSignal_b != COM_FALSE)
            {
                /* Unpack the signal value */
                /* Only UINT8_N and UINT8_DYN signals have type value greater than 8*/
                if(!((Type == (uint8)COM_UINT8_N) || (Type == (uint8)COM_UINT8_DYN)))
                {
                /* FC_VariationPoint_START */
#ifdef COM_RXSIG_FLOAT64SUPP
                    if(Type == COM_FLOAT64)
                    {
                        float64 RxNewVal_f64;
                        /* RxNewVal_f64 = Com_UnPackFloatSignal(RxSigConstPtr->General.Endianess,
                                                RxSigConstPtr->Bit_Pos,PduInfoPtr->SduDataPtr); */
                        RxNewVal_f64 = Com_UnPackFloatSignal(SigEndianess,RxSigConstPtr->Bit_Pos,PduInfoPtr->SduDataPtr);
                        SchM_Enter_Com_RxSigBuff(RXINDICATION);
                        /* Update the data into the signal buffer */
                        COM_GET_SIGTYPEFLOAT64_BUFF(RxSigConstPtr->SigBuff_Index) = RxNewVal_f64;
                        SchM_Exit_Com_RxSigBuff(RXINDICATION);
                    }
                    else
#endif
                    /* FC_VariationPoint_END */
                    {
                        /*    RxNewVal = Com_UnpackSignal(RxSigConstPtr->General.Endianess,
                                RxSigConstPtr->Bit_Pos, Size,
                                PduInfoPtr->SduDataPtr); */
                        RxNewVal = Com_UnpackSignal(SigEndianess,RxSigConstPtr->Bit_Pos, Size,PduInfoPtr->SduDataPtr);
                    }
                }
                else
                {
                    RxNewVal = (Com_SigMaxType)Com_UnpackOpaqueSignal(RxSigConstPtr->Bit_Pos,Size,PduInfoPtr->SduDataPtr);
                }

                /* Check Sign type, perform sign extension if the signal is of Negative */
                if( ((Type & 0x01u) == 0x01u) &&
                     ((RxNewVal & ((Com_SigMaxType)0x1u << (RxSigConstPtr->BitSize - 1))) != 0u) )
                {
                    RxNewVal = Com_PerformSignExtension(RxNewVal,RxSigConstPtr->BitSize);
                }
#if (defined(COM_RxSigInvalid) || defined (COM_RxFilters))
                /* FC_VariationPoint_START */
#if defined(COM_RXSIG_FLOAT64SUPP)
                if(Type != COM_FLOAT64)
#endif /* #if defined(COM_RXSIG_FLOAT64SUPP) */
                /* FC_VariationPoint_END */
                {
                    /* In the following function
                     * 1. Perform data Invalidation processing (REPLACE or NOTIFY)
                     * 2. Signal filter processing
                     */
                    copySignal_b = Com_ValidateRxSignal((Com_SignalIdType)SigId_u32,&RxNewVal);
                }

#endif /* #if (defined(COM_RxSigInvalid) || defined (COM_RxFilters)) */
            }
            /* Update the signal buffer,
             * For signals with update bit;Signal update bit set + signal validation pass
             * For signals without update bit;signal validation pass
             */
            if (copySignal_b != COM_FALSE)
            {
                VAR(Com_SigBuffIndexType, AUTOMATIC) SigBuff_Index;

                SigBuff_Index = RxSigConstPtr->SigBuff_Index;
                /* NOTE on Exclusive area COM_RXINDICATION:
                 * If there is a possibility that COM_RXINDICATION() can be interrupted by Com_ReciveSignal() function or Com_Init function
                 * for any IPdu , then this exclusive area needs to be defined
                 * in Com_Cfg_SchM.h file.
                 */
                /* Copy the new value of the signal into signal buffer */
                if(!(Type == (uint8)COM_UINT8_DYN))
                {
                    SchM_Enter_Com_RxSigBuff(RXINDICATION);
                    /* RxSigConstPtr ->rxSigRAMFields.SigNotify_Flag = COM_TRUE */
                    Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr ->rxSigRAMFields,COM_TRUE);
                    /* FC_VariationPoint_START */
                    /* Signal copy is done above for FLOAT64 type signals, so below step is not needed */
                    if(Type != (uint8)COM_FLOAT64)
                    /* FC_VariationPoint_END */
                    {
                        if(Type != (uint8)COM_UINT8_N)
                        {
                            /* Signal copy is done rx signals */
                            Com_UpdateRxSignalBuffer(RxSigConstPtr,RxNewVal);
                        }
                        else
                        {
                            /* UINT8_N signal */
                            Com_ByteCopy( &COM_GET_SIGTYPEUINT8_BUFF(SigBuff_Index),
                                          (PduInfoPtr->SduDataPtr + (RxSigConstPtr->Bit_Pos >> 3u)), Size);
                        }
                    }

                    SchM_Exit_Com_RxSigBuff(RXINDICATION);
                }
#ifdef COM_RX_DYNAMIC_SIGNAL_SUPPORT
                else
                {
                        SchM_Enter_Com_RxSigDynBuff();
                        /* RxSigConstPtr ->rxSigRAMFields.SigNotify_Flag = COM_TRUE */
                        Com_SetRamValue(RXSIG,_SIGNOTIF,RxSigRamPtr ->rxSigRAMFields,COM_TRUE);
                        /* UINT8_N signal */
                        Com_ByteCopy( &COM_GET_SIGTYPEUINT8DYN_BUFF(SigBuff_Index),
                                      (PduInfoPtr->SduDataPtr + (RxSigConstPtr->Bit_Pos >> 3u)), Size);
                        SchM_Exit_Com_RxSigDynBuff();
                }
#endif

#ifdef COM_SIGNALGATEWAY
                /* This part of code updates the Rx Gateway queue If the signal is updated in the signal buffer by one
                 * of the below means
                 * 1. Reception of Ipdu and thereby signal update after update bit processing
                 */
                if(Com_GetValue(RXSIG,_ISGWSIG,RxSigConstPtr->rxSignalFields) != COM_FALSE)
                {
                    /* If the signal is recieved first time after the last call of Com_MainfunctionRouteSignals then
                     * 1. The fill bit per signal has to be set
                     * 2. Queue entry has to be done for the signal
                     * For the further receptions of the signal, Queue and signal fill bit are not set */
                    Com_SetRamValue(RXSIG,_SIGNALFILLBIT,RxSigRamPtr ->rxSigRAMFields,COM_TRUE);
                    /* This counter will tell if any GW signals in the Ipdu are updated */
                    COM_GET_NUM_OF_GWSIG_UPDATED( ComRxPduId )++;
                }
#endif /* #ifdef COM_SIGNALGATEWAY */
            } /* if (copySignal_b != COM_FALSE) */
        }
        RxSigConstPtr++;
        RxSigRamPtr++;
    } /* End of for loop */

}

#ifdef COM_RX_SIGNALGROUP
static INLINE FUNC(void, COM_CODE) Com_ProcessSignalGroup( VAR(PduIdType, AUTOMATIC) ComRxPduId,
                                                           P2CONST(PduInfoType, AUTOMATIC, COM_APPL_DATA)PduInfoPtr)
{
#ifdef COM_RxSigGrpUpdateTimeout
    P2CONST(Com_SignalTimeoutInfo, AUTOMATIC, COM_APPL_CONST) SigTimeOutConfigPtr;
    P2VAR(uint16, AUTOMATIC, COM_APPL_DATA) SigTimeOutTicksPtr;
    VAR(uint8, AUTOMATIC) UpdateBitStatus;
#endif /* #ifdef COM_RxSigUpdateTimeout */

    Com_RxIpduConstPtrType RxIPduConstPtr;
    Com_RxSigGrpConstPtrType RxSigGrpConstPtr;
    Com_RxSigGrpRamPtrType RxSigGrpRamPtr;
    VAR(Com_RxIntSignalGroupIdType, AUTOMATIC) Idx_SigGrp_ui;
    VAR(uint16_least, AUTOMATIC) limit_ui;
    VAR(boolean, AUTOMATIC) ProcessSignalGrp_b;
    VAR(uint8, AUTOMATIC) ValidateSigGrp_u8;

    RxIPduConstPtr = COM_GET_RX_IPDU_CONSTDATA(ComRxPduId);

#ifdef COM_RxSigGrpUpdateTimeout
    /* Start processing for signal groups.
     * Reset the variable to default value ie UPDATEBIT_NOT_APPLICABLE
     */
    UpdateBitStatus = UPDATEBIT_NOT_APPLICABLE;
    /* If this IPDU has signal groups with update-bits , initialise the pointers
     * Separate deadline monitoring should be performed for signal groups with update-bit
     * Deadline monitoring should not be done if it is disabled
     */
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
     * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
     * system behaviour. Hence suppressed. */
    if ((RxIPduConstPtr->SignalGrpTimeout_Ref != NULL_PTR) && (COM_CheckRxIPduDMStatus(ComRxPduId)))
    {

        /* Update the variable UpdateBitStatus with value UPDATEBIT_APPLICABLE
         * ie atleast one of the signal has configured both update-bit and deadline monitoring.
         */
        UpdateBitStatus = UPDATEBIT_APPLICABLE;
        SigTimeOutConfigPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutInfo_Ref;
        SigTimeOutTicksPtr = RxIPduConstPtr->SignalGrpTimeout_Ref->TimeoutTicks_p;
    }
#endif /* #ifdef COM_RxSigGrpUpdateTimeout */

    limit_ui = (uint32)RxIPduConstPtr->FirstRxSigGrp_Index + (uint32)RxIPduConstPtr->No_Of_SigGrp_Ref;

    RxSigGrpConstPtr = COM_GET_RXSIGGRP_CONSTDATA(RxIPduConstPtr->FirstRxSigGrp_Index);

    RxSigGrpRamPtr =  &COM_GET_RXSIGGRPFLAG(RxIPduConstPtr->FirstRxSigGrp_Index);
    for(Idx_SigGrp_ui = RxIPduConstPtr->FirstRxSigGrp_Index; Idx_SigGrp_ui < limit_ui; Idx_SigGrp_ui++)
    {
        ProcessSignalGrp_b = COM_TRUE;
        ValidateSigGrp_u8   = COM_SET;
#ifdef COM_RxSigGrpUpdateBit
        /* Check if the signal group contained within this IPDU has update-bit configured */
        /* if(RxSigGrpConstPtr->rxSignalGrpFields.UpdBitConf != COM_FALSE) */
        if(Com_GetValue(RXSIGGRP,_UPDBITCONF,RxSigGrpConstPtr->rxSignalGrpFields))
        {
            VAR(PduLengthType, AUTOMATIC) ByteNo_u8;
            VAR(boolean, AUTOMATIC)       updateBitValue_b;

            /*Find the byte No of this Update bit*/
            ByteNo_u8 = (PduLengthType)(RxSigGrpConstPtr->Update_Bit_Pos>>3u);
            updateBitValue_b = Com_GetUpdateBitValue(PduInfoPtr->SduDataPtr,RxSigGrpConstPtr->Update_Bit_Pos,ByteNo_u8);
            /* This macro will get the Update bit status */
            /* Start: Check if the Update bit is SET or NOT */
            if(( (ByteNo_u8+1u) <= PduInfoPtr->SduLength) && (updateBitValue_b == COM_FALSE))
            {
                ProcessSignalGrp_b = COM_FALSE;
                /* RxSigGrpRamPtr ->rxSigGrpRAMFields.SigGrpNotify_Flag = COM_FALSE */
                Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr ->rxSigGrpRAMFields,COM_FALSE);
                /* Data should not be copied into the Grp signal buffer,reset the flag*/
                ValidateSigGrp_u8 = COM_RESET;
            } /* if (update-bit is not set)*/
#ifdef COM_RxSigGrpUpdateTimeout
            else
            {
                if (UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE)
                {
                    UpdateBitStatus = UPDATEBIT_SET;
                }
            }
#endif /* #ifdef COM_RxSigGrpUpdateTimeout */

#ifdef COM_RxSigGrpUpdateTimeout
            /* Check if deadline monitoring needs to be performed for signal groups with update-bit, wthin
             * this IPDU.
             * This variable would be set UBDATEBIT_APPLICABLE only if atleast one the signal group within
             * the IPDU has configured update-bit & timeout value and deadline monitoring for IPDU
             * is not disabled.
             */
            if (UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE)
            {
                /* check if present signal group with update-bit has configured time out.
                 * Only the signals with update-bit and configured timeout will be present in structure
                 * Com_SignalTimeoutInfo.
                 */
                if (SigTimeOutConfigPtr->SigId == Idx_SigGrp_ui)
                {
                    if (UpdateBitStatus == UPDATEBIT_SET)
                    {
                        /* Reload the timer for signal with TimeOut value
                         * Timer should be reloaded only if corresponding update-bit is set for the signal group
                         * It is ensured by the code generator that if TimeOut value is zero, then the
                         * signal group is not considered for deadline monitoring and hence an entry is the
                         * structure Com_SignalTimeoutInfo is not present.
                         * Hence there is no need to check for zero value of TimeOut.
                         */
                        SchM_Enter_Com_RxSigGrpToTicks();
/* FC_VariationPoint_START */
#if (COM_ENABLE_JITTERFLITER == STD_ON)
                        /* CC requirements:
                         * An extra cycle is added to the timeout value after a PDU has been received incase filter is ON
                         * Provides a chance incase of jitter( extra cycle is added in normal case and hence
                         if JITTERFILTER is enabled extra two cycles are added)
                         */

                        (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 2;
#else
/* FC_VariationPoint_END */
                        /* Extra cycle is added to prevent early timeouts */

                        (*SigTimeOutTicksPtr) = SigTimeOutConfigPtr->Timeout + 1;
/* FC_VariationPoint_START */
#endif /* #ifdef COM_ENABLE_JITTERFLITER */
/* FC_VariationPoint_END */
                        SchM_Exit_Com_RxSigGrpToTicks();
                    }
                    /* Increment pointers to refer next signal with update-bit & configured timeout
                     * (within this IPDU)
                     */
                    SigTimeOutTicksPtr++;
                    SigTimeOutConfigPtr++;
                } /* if (SigTimeOutConfigPtr->SigId == Idx_SigGrp_ui) */

                /* Reset the status, after processing it.
                 * It will be set accordingly, in the next iteration of the loop.
                 */
                UpdateBitStatus = UPDATEBIT_RESET;


            } /* if (UpdateBitStatus != UPDATEBIT_NOT_APPLICABLE) */
#endif /* #ifdef COM_RxSigGrpUpdateTimeout */
        } /* if(RxSigGrpConstPtr->rxSignalGrpFields.UpdBitConf != COM_FALSE) */
#endif /* #ifdef COM_RxSigGrpUpdateBit */
        /* If the byte of the signal group is not received, some of the group signals might not have been received.
        Reject the data, even if other group signals are received  */
        if (RxSigGrpConstPtr->lastByte_u8 > PduInfoPtr->SduLength)
        {
            ProcessSignalGrp_b = COM_FALSE;
            ValidateSigGrp_u8  = COM_RESET;
            /* Set signal notification flag */
            /* RxSigGrpRamPtr ->rxSigGrpRAMFields.SigGrpNotify_Flag = COM_TRUE */
            Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr ->rxSigGrpRAMFields,COM_FALSE);
        }

        if (ProcessSignalGrp_b != COM_FALSE)
        {
            /* Data should not be copied into the Grp signal buffer,reset the flag*/
            ValidateSigGrp_u8 = COM_SET;
            /* Set signal notification flag */
            /* RxSigGrpRamPtr ->rxSigGrpRAMFields.SigGrpNotify_Flag = COM_TRUE */
            Com_SetRamValue(RXSIGGRP,_SIGNOTIF,RxSigGrpRamPtr ->rxSigGrpRAMFields,COM_TRUE);
#if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters)
            /* if (RxSigGrpConstPtr->rxSignalGrpFields.GrpSigInvalid != (uint8)COM_NONE) */
            /* For Gw signal groups, it is ensured that the Invalid action is not configured (COM_NONE)
             * This step is needed because Gw signal groups cannot have invalid value processing */
            /* MR12 RULE 13.5 VIOLATION: Below conditional statement access RAM, use of intermediate variables
             * to store and read here, may read obsolete value. Evaluation(or no evaluation) shall not impact the
             * system behaviour. Hence suppressed. */
            if ( (Com_GetValue(RXSIGGRP,_INVACTION,RxSigGrpConstPtr->rxSignalGrpFields) != (uint8)COM_NONE)
#ifdef COM_RxFilters
                || (Com_GetValue(RXSIGGRP,_FILTEREVALREQ,RxSigGrpConstPtr->rxSignalGrpFields) != COM_FALSE)
#endif
                )

            {
                ValidateSigGrp_u8 = Com_ValidateRxSignalGroup((Com_RxIntSignalGroupIdType)Idx_SigGrp_ui,
                                                                                 PduInfoPtr->SduDataPtr);
            }
#endif /* #if defined(COM_RxSigGrpInvalid) || defined(COM_RxFilters) */
        }
        /* The processed data is copied to a second buffer because, If the API Com_Recivesignalgroup() is not interrupt
         * safe there can be data corruption on the group Signal values.
         */
        if (ValidateSigGrp_u8 != (uint8)COM_RESET)
        {
            Com_IpduBuffToSecondBuff( RxSigGrpConstPtr, PduInfoPtr->SduDataPtr, ValidateSigGrp_u8 );

#ifdef COM_SIGNALGROUPGATEWAY
            /* This part of code updates the Rx Gateway queue If the signal group is to be updated into signalgroup
             * buffer by one of the below means
             * 1. Reception of Ipdu and thereby signal update after update bit processing
             */
            /* If the signal is recieved first time after the last call of Com_MainfunctionRouteSignals then
             * 1. The fill bit per signal has to be set
             * 2. Queue entry has to be done for the signal
             * For the further receptions of the signal, Queue and signal fill bit are not set */
            Com_SetRamValue(RXSIGGRP,_SIGNALFILLBIT,RxSigGrpRamPtr->rxSigGrpRAMFields,COM_TRUE);
            /* This counter will tell if any GW signal groups in the Ipdu are updated */
            COM_GET_NUM_OF_GWSIG_UPDATED( ComRxPduId )++;
#endif /* #ifdef COM_SIGNALGROUPGATEWAY */

        }

        RxSigGrpConstPtr++;
        RxSigGrpRamPtr++;
    }/* End of for loop */
}
#endif  /* #ifdef COM_RX_SIGNALGROUP */

/* FC_VariationPoint_START */
/***************************************************************************************************
 Function name    : Com_ReadRxIPduLength
 Syntax           : uint8 Com_ReadRxIPduLength( VAR(PduIdType, AUTOMATIC) ComRxPduId,
                                                P2VAR(PduLengthType, AUTOMATIC, COM_APPL_DATA) RxIPduLengthPtr)
 Description      : Service for Reading the length of the received IPdu
                    The API returns COM_SERVICE_NOT_AVAILABLE in case the ComRxPduId is not in range or
                    the corresponding IPdu Group is not started and updates the RxIPdu length with Zero
                    In normal case it returns E_OK by updating the RxIPdu length.
 Parameter        : ComRxPduId,RxIPduLengthPtr
 Return value     : E_OK/COM_SERVICE_NOT_AVAILABLE
 ***************************************************************************************************/
#ifdef COM_ENABLE_READRXIPDULENGTH
#define COM_START_SEC_CODE
#include "Com_MemMap.h"
FUNC(uint8, COM_CODE) Com_ReadRxIPduLength(VAR( PduIdType, AUTOMATIC) ComRxPduId,
                                                P2VAR(PduLengthType, AUTOMATIC, COM_APPL_DATA) RxIPduLengthPtr)
{
    Com_RxIpduRamPtrType RxIpduRamPtr;
    VAR(PduLengthType ,AUTOMATIC) RxIPduLength;
    VAR(uint8, AUTOMATIC) Status;


    COM_REPORT_ERROR1((ComRxPduId >= COM_GET_NUM_RX_IPDU), COMServiceId_ReceiveSignal, COM_E_PARAM)

    /* If PB variant is selected, then PduId which is passed to this function will be changed
     * to internal Id which is generated through configuration
     * If PC variant is selected, then no mapping table will be used. */

    ComRxPduId = COM_GET_RX_IPDU_ID(ComRxPduId);

    RxIPduLength = 0;
    Status = E_OK;

    /*Check if Ipdu Group is started*/
    /* MR12 RULE 13.5 VIOLATION: Below conditional statement reads flag status. Evaluation(or no evaluation)
     * of the 2nd or 3rd operands does not impact the system behaviour even though of volatile-qualified,
     * moreover HIS-LEVEL parameter will be violated if more conditional statements are added.
     * Hence the warning is suppressed. */
    if(!(COM_CheckRxIPduStatus(ComRxPduId)))
    {
        /* This part will be executed when IPDU Group is Stopped (Zero is returned as IPdu length) */
        Status = COM_SERVICE_NOT_AVAILABLE;
    }
    else
    {
        RxIpduRamPtr = &COM_GET_RXPDURAM_S(ComRxPduId);
        RxIPduLength = RxIpduRamPtr->RxIPduLength;
    }

    *RxIPduLengthPtr = RxIPduLength;

    return(Status);
}
#define COM_STOP_SEC_CODE
#include "Com_MemMap.h"
#endif
/* FC_VariationPoint_END */

