
#include "PduR_IpduM.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != IPDUM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != IPDUM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "IpduM.h"
#include "IpduM_Priv.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : Ipdum_Transmit
 Syntax           : Std_ReturnType Ipdum_Transmit(PduIdType PdumTxPduId, PduInfoType PduInfoPtr)
 Description      : Service is called by the PDU-Router to request for a transmission.
 Parameter        : PduIdType PdumTxPduId  : ID of I-PDU to be transmitted.
                                             Range: 0..(maximum number of I-PDU IDs which are multiplexed) - 1.
                    PduInfoType PduInfoPtr : A pointer to a structure with I-PDU related data that shall be
                                             transmitted, data length and pointer to I-SDU buffer
 Return value     : Std_ReturnType
                    E_OK        : Transmit request is accepted
                    E_NOT_OK    : Transmit request is not accepted.
 ***************************************************************************************************/

FUNC(Std_ReturnType, IPDUM_CODE) IpduM_Transmit(
                                                VAR(PduIdType, AUTOMATIC) PdumTxPduId,
                                                P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
                                               )
                                               {
    /*Common declarations for Regular and contained pdus*/
    Std_ReturnType RetVal;
    RetVal = E_NOT_OK;

    /* Start: Det*/
    /* Return Type: Std_ReturnType */
    IPDUM_REPORT_ERROR1((IpduM_Uninit_Flag == IPDUM_UNINIT), IPDUMServiceId_Transmit, IPDUM_E_UNINIT)

    IPDUM_REPORT_ERROR1((PduInfoPtr == NULL_PTR), IPDUMServiceId_Transmit, IPDUM_E_PARAM_POINTER)
    /* End: Det */

    /*Process for regular Pdus*/
    if(PdumTxPduId < IPDUM_NUM_TX_IPDUS)
    {
#if defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)
        /* pointer to Tx Request table */
        P2CONST(IpduM_TxRequestType, AUTOMATIC, IPDUM_APPL_CONST) TxReqPtr;

        /* pointer to SubPart table */
        P2CONST(IpduM_SubPartType, AUTOMATIC, IPDUM_APPL_CONST) SubPartPtr;

        /* pointer to SW Timer */
        P2VAR(IpduM_TimerType, AUTOMATIC, IPDUM_APPL_DATA) TimerPtr;

        /* pointer to Tx MPdu table */
        P2CONST(IpduM_TxMPduType, AUTOMATIC, IPDUM_APPL_CONST) TxMpduPtr;

        /* pointer to RAM data */
        P2VAR(IpduM_TxRamType, AUTOMATIC, IPDUM_APPL_DATA) TxRamPtr;

        /* pointer to MPdu buffer */
        P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) MpduBufferPtr;

        /* Local variable for loopIndex */
        uint8_least LoopIdx;

        /* Structure to hold the data and length */
        PduInfoType MpduInfo;

        /* To store the number of sub-parts */
        uint16 TxNumOfSubParts;

        /* Structure to hold the Transmission PDU-Id's*/
        PduIdType TxMPduId;

        /* To get the IpduM trigger value */
        IpduM_TriggType TriggerMode;
        boolean DynamicIPdu;

        VAR(PduInfoType, IPDUM_VAR) IpduM_BuffValues;
        VAR(uint8,IPDUM_VAR) IpduM_InitValueBuff[MAX_COM_IPDU_SIZE];
        P2CONST(IpduM_SubPartType, AUTOMATIC, IPDUM_APPL_CONST) SubPartLocalPtr;

        /**** End Of Declarations ****/

        TxReqPtr = &IpduM_TxReqTable[PdumTxPduId];
        TxMPduId = TxReqPtr->MPduId;
        TxRamPtr = &IpduM_TxRamData[TxMPduId];
        TimerPtr = &IpduM_SwTimer;

        /* Check if previous Tx is confirmed or TxConfirmTimeout */
        if(TxRamPtr->TxState == IPDUM_TX_READY)
        {
            TxNumOfSubParts = TxReqPtr->NumOfSubParts;
            TxMpduPtr = &IpduM_TxMPduTable[TxMPduId];
            MpduBufferPtr = TxMpduPtr->MPduBuffPtr;
            TriggerMode = TxMpduPtr->TxTriggMode;

            /* Get Subpart details for PdumTxPduId */

            /*RfC  65613: In case the IpduM shall update the dynamic part just-in-time,
             the latest dynamic part sent by the upper layer shall be updated or
             the dynamic part referenced by IpduMInitialDynamicPart if no dynamic part was sent before. */

            /* The requirements of section 'Just-In-Time update of parts' do not specify which of the dynamic parts has to be updated if a dynamic part has to be updated.
             From my point of view two cases are to be distinguished, the one where an IpduM_Transmit was called for a dynamic part already and the other one where no IpduM_Transmit was called before.
             For the case the IpduM_Transmit was called already, the update shall happen for the dynamic part called at last if related IpduMJitUpdate is configured to true.
             For the other case, the update shall happen for the initial dynamic part, referenced by IpduMinitialDynamicPart, if related IpduMJitUpdate is configured to true.
             Please clarify and update section/requirements accordingly. */

            /* Check if it is static or dynamic PDU (IPduType) */
            if (TxReqPtr->IPduType == IPDUM_PDUTYPE_STATIC)
            {
                /* IpduMJITUpdate: Only used if IpduMJITUpdate is set dynamic parts */
                PduIdType TxDynPduId;
                TxDynPduId = TxRamPtr->PrevDynPartPduId;

                if((IpduM_TxReqTable[TxDynPduId].ipduMJITUpdate != FALSE) && (TriggerMode != IPDUM_NONE))
                {

                    IpduM_BuffValues.SduDataPtr= &IpduM_InitValueBuff[0];
                    IpduM_BuffValues.SduLength = TxMpduPtr->TxMPduLen;

                    SubPartLocalPtr = IpduM_TxReqTable[TxDynPduId].TxBaseSubPart;

                    TxDynPduId = IpduM_TxConfTable[TxDynPduId];
                    RetVal = IPDUM_UPL_TRIGGERTRANSMIT(TxDynPduId,&IpduM_BuffValues);
                    /*update the MPDU buffer for this dynamic part only if TriggerTransmit call returns E_OK */
                    if(RetVal == E_OK)
                    {
                        /*Update the Tx RAM pointer for Dynamicpart handle Id for which Tx confirmation need to be given */
                        TxRamPtr->DynPartPduId = TxDynPduId;
                        for(LoopIdx = 0; LoopIdx < IpduM_TxReqTable[TxRamPtr->PrevDynPartPduId].NumOfSubParts; LoopIdx++)
                        {
        	            IpduM_CopyBuffer(TxMpduPtr->byteOrder,SubPartLocalPtr, &IpduM_InitValueBuff[0], MpduBufferPtr);
                            SubPartLocalPtr++;
                        }
                    }
                }
                else
                {
                    RetVal = E_OK;
                }
                TxRamPtr->StaticPartPduId = IpduM_TxConfTable[PdumTxPduId];
                DynamicIPdu = FALSE;
            }
            else
            {
                /* IpduMJITUpdate: Only used if IpduMJITUpdate is set static parts */
                PduIdType TxStaPduId;
                TxStaPduId = TxMpduPtr->StaticPduId;

                if((TxStaPduId != IPDUM_INVALID_INDEX) && (IpduM_TxReqTable[TxStaPduId].ipduMJITUpdate != FALSE) && (TriggerMode != IPDUM_NONE))
                {
                    IpduM_BuffValues.SduDataPtr= &IpduM_InitValueBuff[0];
                    IpduM_BuffValues.SduLength = TxMpduPtr->TxMPduLen;

                    SubPartLocalPtr = IpduM_TxReqTable[TxStaPduId].TxBaseSubPart;

                    TxStaPduId = IpduM_TxConfTable[TxStaPduId];
                    RetVal = IPDUM_UPL_TRIGGERTRANSMIT(TxStaPduId,&IpduM_BuffValues);
                    /*update the MPDU buffer for this Static part only if TriggerTransmit call returns E_OK */
                    if(RetVal == E_OK)
                    {
                        /* Update the Tx RAM pointer for Static Part handle Id for which Tx confirmation need to be given*/
                        TxRamPtr->StaticPartPduId = TxStaPduId;
                        for(LoopIdx = 0; LoopIdx < IpduM_TxReqTable[TxMpduPtr->StaticPduId].NumOfSubParts; LoopIdx++)
                        {
        	            IpduM_CopyBuffer(TxMpduPtr->byteOrder,SubPartLocalPtr, &IpduM_InitValueBuff[0], MpduBufferPtr);
                            SubPartLocalPtr++;
                        }
                    }
                }
                else
                {
                    RetVal = E_OK;
                }
                /* Update the Tx RAM pointer for Dynamicpart handle Id for which Tx confirmation need to be given */
                TxRamPtr->DynPartPduId = IpduM_TxConfTable[PdumTxPduId];
                /* Update PrevDynPartPduId RAM pointer which is used to store previous transmitted TxPdu */
                TxRamPtr->PrevDynPartPduId = PdumTxPduId;
                DynamicIPdu = TRUE;
            }

            SubPartPtr = TxReqPtr->TxBaseSubPart;
            for(LoopIdx = 0; LoopIdx < TxNumOfSubParts; LoopIdx++)
            {
            IpduM_CopyBuffer(TxMpduPtr->byteOrder,SubPartPtr, PduInfoPtr->SduDataPtr, MpduBufferPtr);
                SubPartPtr++;
            }
            /* The multiplexed I-PDU shall not be send if the
             * JIT-update request via PduR_IpduMTriggerTransmit returns E_NOT_OK. */
            if(RetVal != E_NOT_OK)
            {
                /*Below return value is commented because returning E_NOT_OK for IPDUM_NONE mode will casue inappropriate behaviour in Com*/
                /*RetVal = E_NOT_OK;*/
                /* Checking for Trigger mode */
                if (TriggerMode != IPDUM_NONE)
                {
                    /* Checking for pdu type */
                    if(
                            ((DynamicIPdu != FALSE) && (TriggerMode == IPDUM_DYNAMIC_PART_TRIGGER)) ||
                            ((DynamicIPdu == FALSE) && (TriggerMode == IPDUM_STATIC_PART_TRIGGER)) ||
                            (TriggerMode == IPDUM_STATIC_OR_DYNAMIC_PART_TRIGGER)
                    )
                    {
                        MpduInfo.SduDataPtr = TxMpduPtr->MPduBuffPtr;
                        MpduInfo.SduLength = TxMpduPtr->TxMPduLen;
                        RetVal = PduR_IpduMTransmit(TxMpduPtr->TargetPduId, &MpduInfo);
                        if(RetVal != E_NOT_OK)
                        {
                            /* Start TxConfirmationTimeout timer and it will not be monitored when Trigger Transmit is used for transmission*/
                            if(TxMpduPtr->TxConfirmTimeout > 0u)
                            {
                                TxRamPtr->TxConfirmTimer = TimerPtr->SwFRTimer;
                                TxRamPtr->TxState = IPDUM_TX_REQUESTED;
                            }
                            else
                            {
                                /* New transmission request from Com is allowed unconditionally if TxTimeout is configured Zero
                            because IpduM cannot wait eternity for TxConfirmation */
                            }
                        }
                        else
                        {
                            /* Reset the Tx request IDs to avoid unexpected Tx confirmaitons to the upper layer */
                            TxRamPtr->DynPartPduId = IPDUM_INVALID_INDEX;
                            TxRamPtr->StaticPartPduId = IPDUM_INVALID_INDEX;
                        }
                    }
                }
            }
        }
#endif /*defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)*/
    }
    /*Below code will execute only for contained Tx pdu*/
    else if((PdumTxPduId >= IPDUM_NUM_TX_IPDUS) && (PdumTxPduId < IPDUM_TOTAL_NUM_TX_IPDUS))
    {
#if defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)
        {
            /* Pointer to Container(Cr) Tx table*/
            P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCrPtr;

            /*Pointer to Contained(Cd) Tx table*/
            P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCdPtr;

            /*Pointer to Tx ContainerPduDynamicType table*/
            P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_CONST) TxCntnrDynptr;

            /*Variable to hold the Container Pdu Id*/
            PduIdType TxCrPduId;

            /*Variable to hold the Contained Pdu Id*/
            PduIdType TxCdPduId;

            /* To get the IpduM Tx Contained Pdu semantics Type*/
            ContainedTxPduSemanticsType CdTxPduSemanticsMode;

            /*Boolean to specify that the container is ready to Transmit*/
            VAR(boolean, AUTOMATIC) TransmitFlag_b;

            /*Boolean to specify that the container is ready to Transmit*/
            VAR(boolean, AUTOMATIC) WriteToContainerFlag_b;
            VAR(boolean, AUTOMATIC) WriteToNextContainerFlag_b;

            VAR(boolean, AUTOMATIC) LastIsBestFound_b;

            TransmitFlag_b = FALSE;
            WriteToContainerFlag_b = FALSE;
            WriteToNextContainerFlag_b = FALSE;
            LastIsBestFound_b = FALSE;

            /*Default retval is set to E_OK.*/
            RetVal = E_OK;

            /*As the TxContainedPdu table is based on 0 base index whereas id's to contained Pdu is assigned linearly after
             * regular pdu. So it should be accessed according to the contained Pdu entry in the table.  */
            TxCdPduId =  PdumTxPduId - IPDUM_NUM_TX_IPDUS;
            TxCdPtr = &IpduM_TxContainedPdu[TxCdPduId];

            /*Get the contained Pdu's container reference*/
            TxCrPduId = TxCdPtr->ContainerTxPduId;
            TxCrPtr = &IpduM_TxContainerPdu[TxCrPduId];

            /*Initilize the Tx Container RAM structure with respective container Pdu Id*/
            TxCntnrDynptr = &IpduM_TxContainerPduDynData[TxCrPduId];

            /*Get the current container queue instance base address*/
            IpduM_GetCurInstanceBaseAddress(TxCrPduId);

            /*Check if same instance is already transmitted and waiting for the TxConf .
             * In this case set the TxConf pointer to NULL_PTR so that TX_CONF is ignored for the previous instance.
             * See req : [SWS_IpduM_00199]*/
            if(TxCntnrDynptr->WritePtr == TxCntnrDynptr->TxConfPtr)
            {
                /*Flush this container instance data. I,e set the byte(Container Sdu len) to 0 */
                IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen) = 0;
                /*Set TxConfPtr to NULL_PTR to block the TxConf for discarded container instance.*/
                TxCntnrDynptr->TxConfPtr = NULL_PTR;

                /* Along with TxConfPtr, TxConfRAMTicks also have to be reset to 0,
                 * because that controls the triggerring of new request in IpduM_PreparePduRTransmit API. */
                TxCntnrDynptr->TxConfRAMTicks = 0;
            }

            /*Get the Contained pdu Semantics mode*/
            CdTxPduSemanticsMode = TxCdPtr->ContainedTxPduSemantics;

            /* If requested TxContainedPdu is not fitting in the current instance of the TxContainerPdu then trigger
             * the transmission first and then write this TxContainedPdu data into next instance of the queue */
            if(((TxCrPtr->TxContainerPduLen) - IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr , TxCrPtr->TxContainerPduLen))
                    < (TxCrPtr->HeaderSize + PduInfoPtr->SduLength))
            {
                /*Check if the Semantics of contained Pdu*/
                if(CdTxPduSemanticsMode == IPDUM_COLLECT_LAST_IS_BEST)
                {
                    LastIsBestFound_b = IpduM_HandlingLastIsBestSemantics(TxCdPduId,PduInfoPtr);
                    /*If RetVal returns E_NOT_OK, it means that there was no previous instance of this contained Pdu.
                     * So this contained Pdu need to written into the next container instance*/
                    if(LastIsBestFound_b != TRUE)
                    {
                        /*Set a flag to write contained pdu into container*/
                        WriteToNextContainerFlag_b = TRUE;
                    }
                }
                else
                {
                    /*Set a flag to write contained pdu into container*/
                    WriteToNextContainerFlag_b = TRUE;
                }
                /*Transmit should be set to TRUE only for DIRECT Transmision. */
                /* SWS_IpduM_00182 : According to this req only DIRECT container PDU's need to be Transmitted */
                if(TxCrPtr->ContainerTxTriggerMode == IPDUM_DIRECT)
                {
                    TransmitFlag_b = TRUE;
                }
                else/* SWS_IpduM_00183 : According to this req TriggerTransmit container PDU's need to be just Queued */
                {
                    /*Here if the container instance is 0 then current instance will be discarded*/
                    TxCntnrDynptr->CurrentQueueInstance = ((TxCntnrDynptr->CurrentQueueInstance + 1) % (TxCrPtr->InstancesInQueue)) ;
                    IpduM_GetCurInstanceBaseAddress(TxCrPduId);
                }

            }
            else /*Container can accommodate the contained Pdu*/
            {
                if(CdTxPduSemanticsMode == IPDUM_COLLECT_QUEUED)
                {
                    /*Set a flag to write contained pdu into container*/
                    WriteToContainerFlag_b = TRUE;
                }
                else
                {
                    LastIsBestFound_b = IpduM_HandlingLastIsBestSemantics(TxCdPduId,PduInfoPtr);
                    if(LastIsBestFound_b != TRUE)
                    {
                        /*Set a flag to write contained pdu into container*/
                        WriteToContainerFlag_b = TRUE;
                    }
                    else
                    {
                        /*Contained Pdu already exists in the container Pdu so writing contained Pdu into the container
                         * is handled in IpduM_HandlingLastIsBestSemantics function itself.*/
                        /*Send timer need to be updated for container*/
                        IpduM_UpdateTxSendTimeOutTimer(TxCdPduId, PduInfoPtr->SduLength);
                    }
                }
            }

            /*The below write operation need to be performed before checking the transmit criteria's */
            if(WriteToContainerFlag_b == TRUE)
            {

                IpduM_CopyBufferToContainer(TxCdPduId, PduInfoPtr->SduLength, PduInfoPtr->SduDataPtr,
                        (TxCntnrDynptr->WritePtr + IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr, TxCrPtr->TxContainerPduLen)));

                /*Update CurrentByteLocation cumulatively*/
                IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen) += (uint8)(TxCrPtr->HeaderSize + PduInfoPtr->SduLength);

                /*Send timer need to be updated for container*/
                IpduM_UpdateTxSendTimeOutTimer(TxCdPduId, PduInfoPtr->SduLength);
            }

            /*If TxFirstContainedpduTrigger is configured to true and
             * this is first Contained Pdu in this instance of the container Pdu then transmit the container*/
            if((TxCrPtr->TxFirstContainedpduTrigger == TRUE) &&
                (IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen) == (uint8)(TxCrPtr->HeaderSize + PduInfoPtr->SduLength)))
            {
                TransmitFlag_b = TRUE;
            }
            else
            {
                /*Check for Threshold value*/
                if((TxCrPtr->TxThresholdSize != 0u) && ((IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen)) > (TxCrPtr->TxThresholdSize)))
                {
                    TransmitFlag_b = TRUE;
                }
                else
                {
                    if(TxCdPtr->ContainedTxPduTrigger == IPDUM_TRIGGER_ALWAYS)
                    {
                        TransmitFlag_b = TRUE;
                    }
                }
            }

            /*First transmit need to done, then data should be written into container*/
            if(TransmitFlag_b == TRUE)
            {
                /* Only if the ContainerTxTriggerMode is IPDUM_DIRECT, update the write pointer, CurrentByteLocation and CurrentQueueInstance
                 * In case IPDUM_TRIGGERTRANSMIT, these varaibles will be updated after the data is fetched by a call to IpduM_TriggerTransmit  */
                if(TxCrPtr->ContainerTxTriggerMode == IPDUM_DIRECT)
                {
                    /*Before calling  : means current container cannot accommodate further contained Pdus
                     * 1) Queue size need to be incremented.
                     * 2) Write pointer should be pointing to next queue instance base Address.
                     */
                    TxCntnrDynptr->CurrentQueueInstance = ((TxCntnrDynptr->CurrentQueueInstance + 1) % (TxCrPtr->InstancesInQueue)) ;
                    IpduM_GetCurInstanceBaseAddress(TxCrPduId);
                }
                /*Irrespective of RetVal and Semantics type, transmit the container*/
                RetVal = IpduM_PreparePduRTransmit(TxCrPduId);
            }

            /*The below code is dependent on the Transmit Flag, it should be called after Queue is incremented.
             *The below flag is set only if the contained PDU is not fitting into the current container instance.
             *Before writing the contained PDU into the new container instance, previous instance is handeld in two ways
             *1. Direct -> Transmit the previous container instance and write into new one.
             *2. TriggerTransmit -> Just Queue the previous instance and write into new one*/
            if(WriteToNextContainerFlag_b == TRUE)
            {
                /*At this place we are writing a contained pdu into the new container instance so reset the current
                 * buffer and write the contained pdu into the container.*/
                IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen) = 0;
                /* If TxConf for previously transmitted container is Pending according to req [SWS_IpduM_00199]
                 * then the TxConfirmation for the previously transmitted container instance is discarded.
                 * Along with TxConfPtr, TxConfRAMTicks also have to be reset to 0, because this
                 * controls the triggerring of new request in IpduM_PreparePduRTransmit API. */
                if(TxCntnrDynptr->WritePtr == TxCntnrDynptr->TxConfPtr)
                {
                    TxCntnrDynptr->TxConfPtr = NULL_PTR;
                    TxCntnrDynptr->TxConfRAMTicks = 0;
                }
                IpduM_CopyBufferToContainer(TxCdPduId, PduInfoPtr->SduLength, PduInfoPtr->SduDataPtr,
                        (TxCntnrDynptr->WritePtr + (IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen))));

                /*Update CurrentByteLocation cumulatively */
                IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen) += (uint8)(TxCrPtr->HeaderSize + PduInfoPtr->SduLength);

                /*Send timer need to be updated for container*/
                IpduM_UpdateTxSendTimeOutTimer(TxCdPduId, PduInfoPtr->SduLength);
                /*After the first contained Pdu is written into new container instance, the Transmit criteria for the
                 *container need to be checked. Based on the container PDU Tx Trigger mode, handling of the container
                 *queue is varied.
                 *1. Direct -> Increment the container Queue instance and then Transmit.
                 *2. TriggerTransmit -> Transmit the container PDU without incrementing the Queue instance.*/
                if((TxCrPtr->TxFirstContainedpduTrigger == TRUE) || (TxCdPtr->ContainedTxPduTrigger == IPDUM_TRIGGER_ALWAYS)
                        || ((TxCrPtr->TxThresholdSize != 0u) && (IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr,TxCrPtr->TxContainerPduLen) > (TxCrPtr->TxThresholdSize))))
                {
                    if(TxCrPtr->ContainerTxTriggerMode == IPDUM_DIRECT)
                    {
                        TxCntnrDynptr->CurrentQueueInstance = ((TxCntnrDynptr->CurrentQueueInstance + 1) % (TxCrPtr->InstancesInQueue)) ;
                        IpduM_GetCurInstanceBaseAddress(TxCrPduId);
                    }
                    /*Irrespective of RetVal and Semantics type, transmit the container*/
                    RetVal = IpduM_PreparePduRTransmit(TxCrPduId);
                }
            }
        }
#endif /* defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF) */
    }
    else
    {
        IPDUM_REPORT_ERROR1((PdumTxPduId >= IPDUM_TOTAL_NUM_TX_IPDUS), IPDUMServiceId_Transmit, IPDUM_E_PARAM)
    }
    return RetVal;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

