
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
 Function name    : Ipdum_TriggerTransmit
 Syntax           : Std_ReturnType Ipdum_TriggerTransmit( PduIdType PdumTxPduId, PduInfoType PduInfoPtr)
 Description      : This is the AUTOSAR interface for transmission of MPdus through trigger transmit mechanism.
 Parameter        : PduIdType PdumTxPduId  : ID of the SDU that is requested to be transmitted.
                    PduInfoType PduInfoPtr : Contains a pointer to a buffer (SduDataPtr) to where the SDU shall be copied to.
                                             On return, the service will indicate the length of the copied SDU data in SduLength.
 Return value     : Std_ReturnType
                    E_OK : SDU has been copied and SduLength indicates the num-ber of copied bytes
 ***************************************************************************************************/

FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTransmit(
                                                VAR(PduIdType, AUTOMATIC) PdumTxPduId,
                                                P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
                                            )
                                            {
    Std_ReturnType RetVal_Dyn;
    RetVal_Dyn = E_OK;

    /* Start: Det */
    /* Return Type: void */
    IPDUM_REPORT_ERROR1((IpduM_Uninit_Flag == IPDUM_UNINIT), IPDUMServiceId_TriggerTransmit, IPDUM_E_UNINIT)

    IPDUM_REPORT_ERROR1((PduInfoPtr == NULL_PTR), IPDUMServiceId_TriggerTransmit, IPDUM_E_PARAM_POINTER)
    /* End: Det */

    if(PdumTxPduId < IPDUM_NUM_TX_MPDUS)
    {
#if defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)
        /* pointer to Tx MPdu table */
        P2CONST(IpduM_TxMPduType, AUTOMATIC, IPDUM_APPL_CONST) TxMpduPtr;

        /* pointer to MPdu buffer */
        P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA)  TxMpduBuffPtr;

        /* pointer to RAM data */
        P2VAR(IpduM_TxRamType, AUTOMATIC, IPDUM_APPL_DATA) TxRamPtr;

        uint8_least LoopIdx;

        Std_ReturnType RetVal_Sta;
        VAR(PduInfoType, IPDUM_VAR) IpduM_BuffValues;
        VAR(uint8,IPDUM_VAR) IpduM_InitValueBuff[MAX_COM_IPDU_SIZE];
        P2CONST(IpduM_SubPartType, AUTOMATIC, IPDUM_APPL_CONST) SubPartLocalPtr;

        RetVal_Sta = E_OK;

        /**** End Of Declarations ****/

        TxMpduPtr = &IpduM_TxMPduTable[PdumTxPduId];
        TxRamPtr = &IpduM_TxRamData[PdumTxPduId];

        if(IpduM_TxReqTable[TxRamPtr->PrevDynPartPduId].ipduMJITUpdate != FALSE)
        {
            PduIdType TxDynPduId;
            TxDynPduId = TxRamPtr->PrevDynPartPduId;
            IpduM_BuffValues.SduDataPtr= &IpduM_InitValueBuff[0];
            IpduM_BuffValues.SduLength = TxMpduPtr->TxMPduLen;

            SubPartLocalPtr = IpduM_TxReqTable[TxDynPduId].TxBaseSubPart;

            TxDynPduId = IpduM_TxConfTable[TxDynPduId];
            RetVal_Dyn = IPDUM_UPL_TRIGGERTRANSMIT(TxDynPduId,&IpduM_BuffValues);
            /*update the MPDU buffer for this dynamic part only if TriggerTransmit call returns E_OK */
            if(RetVal_Dyn == E_OK)
            {
                /*Update the Tx RAM pointer for Dynamicpart handle Id for which Tx confirmation need to be given */
                TxRamPtr->DynPartPduId = TxDynPduId;
                for(LoopIdx = 0; LoopIdx < IpduM_TxReqTable[TxRamPtr->PrevDynPartPduId].NumOfSubParts; LoopIdx++)
                {
            IpduM_CopyBuffer(TxMpduPtr->byteOrder,SubPartLocalPtr, &IpduM_InitValueBuff[0], TxMpduPtr->MPduBuffPtr);
                    SubPartLocalPtr++;
                }
            }
        }

        if((TxMpduPtr->StaticPduId != IPDUM_INVALID_INDEX) && (IpduM_TxReqTable[TxMpduPtr->StaticPduId].ipduMJITUpdate != FALSE))
        {
            PduIdType TxStaPduId;
            TxStaPduId = TxMpduPtr->StaticPduId;

            IpduM_BuffValues.SduDataPtr= &IpduM_InitValueBuff[0];
            IpduM_BuffValues.SduLength = TxMpduPtr->TxMPduLen;

            SubPartLocalPtr = IpduM_TxReqTable[TxStaPduId].TxBaseSubPart;

            TxStaPduId = IpduM_TxConfTable[TxStaPduId];
            RetVal_Sta = IPDUM_UPL_TRIGGERTRANSMIT(TxStaPduId,&IpduM_BuffValues);
            /*update the MPDU buffer for this Static part only if TriggerTransmit call returns E_OK */
            if(RetVal_Sta == E_OK)
            {
                /* Update the Tx RAM pointer for Static Part handle Id for which Tx confirmation need to be given*/
                TxRamPtr->StaticPartPduId = TxStaPduId;
                for(LoopIdx = 0; LoopIdx < IpduM_TxReqTable[TxMpduPtr->StaticPduId].NumOfSubParts; LoopIdx++)
                {
            IpduM_CopyBuffer(TxMpduPtr->byteOrder,SubPartLocalPtr, &IpduM_InitValueBuff[0], TxMpduPtr->MPduBuffPtr);
                    SubPartLocalPtr++;
                }
            }
        }

        if((RetVal_Dyn != E_NOT_OK) && (RetVal_Sta != E_NOT_OK))
        {
            TxMpduBuffPtr = TxMpduPtr->MPduBuffPtr;
            /* Each byte of the MPdu buffer is copied to the buffer pointed to by SduDataPtr */
            for(LoopIdx = 0; LoopIdx < TxMpduPtr->TxMPduLen; LoopIdx++)
            {
                PduInfoPtr->SduDataPtr[LoopIdx] = TxMpduBuffPtr[LoopIdx];
            }
            /* Update Sdulength with the length of the Mpdu */
            PduInfoPtr->SduLength = TxMpduPtr->TxMPduLen;
            RetVal_Dyn = E_OK;
        }
        else
        {
            RetVal_Dyn = E_NOT_OK;
        }
#endif /*defined(IPDUM_TX_PATHWAY) && (IPDUM_TX_PATHWAY != STD_OFF)*/
    }
    else if((PdumTxPduId >= IPDUM_NUM_TX_MPDUS) && (PdumTxPduId < IPDUM_TOTAL_NUM_TX_MPDUS))
    {
#if defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)
        {
            /*Variable to hold the Container Pdu Id*/
            PduIdType TxCntnrPduId;

            /* Pointer to Container(Cr) Tx table*/
            P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCntnrPtr;

            /*Pointer to Tx ContainerPduDynamicType table*/
            P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_CONST) TxCntnrRAMptr;

            TxCntnrPduId = PdumTxPduId - IPDUM_NUM_TX_MPDUS;

            /*Get the container reference*/
            TxCntnrPtr = &IpduM_TxContainerPdu[TxCntnrPduId];

            /*Initilize the Tx Container RAM structure with respective container Pdu Id*/
            TxCntnrRAMptr = &IpduM_TxContainerPduDynData[TxCntnrPduId];

            /* If there is no queue configured and data has been already into the IpduM buffer, then copy the data into
             * the destination buffer */
            if((IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrRAMptr->ReadPtr,TxCntnrPtr->TxContainerPduLen)) > 0u)
            {
                /*write the current instance of the container into the buffer*/
                rba_BswSrv_MemCopy8( PduInfoPtr->SduDataPtr,TxCntnrRAMptr->ReadPtr,
                        IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrRAMptr->ReadPtr,TxCntnrPtr->TxContainerPduLen));
                /* Update the sdulength with the overall size of the Container PDU.
                 * The total size builds up by the total of all payloads of the contained I-PDUs plus the total length
                 * of the corresponding headers.  */
                PduInfoPtr->SduLength = IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrRAMptr->ReadPtr,TxCntnrPtr->TxContainerPduLen);
                /* After the data is fetched by the lower layer, we can update the TxConfPtr */
                TxCntnrRAMptr->TxConfPtr = TxCntnrRAMptr->ReadPtr;
                /*Set the TxCOnf timer for this container*/
                if(TxCntnrPtr->TxConfConstTicks > 0u)
                {
                    TxCntnrRAMptr->TxConfRAMTicks = TxCntnrPtr->TxConfConstTicks;
                }

                /* Update the ReadPtr only if the Queue is configured and is incremented to next container
                 *  else it will be always pointing to starting address of BufferPtr */
                if(TxCntnrRAMptr->WritePtr != TxCntnrRAMptr->ReadPtr)
                {
                    TxCntnrRAMptr->ReadPtr =  (TxCntnrRAMptr->ReadPtr + ((TxCntnrPtr->TxContainerPduLen)+1u));
                    /*At anytime if the readPtr reaches last address in the buffer then reset it to starting address*/
                    if(TxCntnrRAMptr->ReadPtr == ((TxCntnrPtr->BufferPtr) +
                            IPDUM_TOTAL_CNTNR_LEN(TxCntnrPtr->TxContainerPduLen,TxCntnrPtr->InstancesInQueue)))
                    {
                        TxCntnrRAMptr->ReadPtr = TxCntnrPtr->BufferPtr;
                    }
                }
            }
            else
            {
                /*Check if Queue is empty: No instance is ready to transmit*/
                RetVal_Dyn = E_NOT_OK;
            }
        }
#endif /*defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)*/
    }
    else
    {
        IPDUM_REPORT_ERROR1((PdumTxPduId >= IPDUM_TOTAL_NUM_TX_MPDUS), IPDUMServiceId_TriggerTransmit, IPDUM_E_PARAM)
    }
    /*If both macros are disabled then default return value need to be returned.*/
    return RetVal_Dyn;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

