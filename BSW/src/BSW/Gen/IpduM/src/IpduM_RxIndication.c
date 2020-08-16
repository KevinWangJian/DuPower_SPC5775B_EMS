
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
 Function name    : Ipdum_RxIndication
 Syntax           : void Ipdum_RxIndication(PduIdType RxPduId, PduInfoType PduInfoPtr)
 Description      : Indication of a received I-PDU from a lower layer communication module.
 Parameter        : PduIdType RxPduId  : ID of the received I-PDU.
                    PduInfoType PduInfoPtr : Contains the length (SduLength) of the received I-PDU
                                             and a pointer to a buffer (SduDataPtr) containing the I-PDU.
 Return value     : None.
 ***************************************************************************************************/

FUNC(void, IPDUM_CODE) IpduM_RxIndication(
                                            VAR(PduIdType, AUTOMATIC) PdumRxPduId,
                                            P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr
                                         )
                                         {
    /* Start: Det*/
    /* Return Type: void */
    IPDUM_REPORT_ERROR((IpduM_Uninit_Flag == IPDUM_UNINIT), IPDUMServiceId_RxIndication, IPDUM_E_UNINIT)

    IPDUM_REPORT_ERROR((PduInfoPtr == NULL_PTR), IPDUMServiceId_RxIndication, IPDUM_E_PARAM_POINTER)
            /* End: Det */

     /*Process for the regular PDU's */
    if(PdumRxPduId < IPDUM_NUM_RX_MPDUS)
    {
#if defined(IPDUM_RX_PATHWAY) && (IPDUM_RX_PATHWAY != STD_OFF)
        {
            /* pointer to Rx MPdu configuration data */
            P2CONST(IpduM_RxMPduType, AUTOMATIC, IPDUM_APPL_CONST)  RxMpduPtr;

            /* pointer to Rx PDU configuration data */
            P2CONST(IpduM_RxUpPduType, AUTOMATIC, IPDUM_APPL_CONST) RxUpPduPtr;

            /* pointer to Rx SubPart configuration data */
            P2CONST(IpduM_SubPartType, AUTOMATIC, IPDUM_APPL_CONST) SubPartPtr;

            /* pointer to Rx Pdu Buffer */
            P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA)  RxUpPduBuffPtr;

            /* variable to hold PduInfo */
            PduInfoType                 RxUpPduInfo;

            /* Index */
            uint16_least                LoopIndex;

            /* number of subparts */
            uint16_least                RxNumOfSubParts;

            /* loop count */
            PduIdType                   LoopCount;

            /* pointer to Rx Static PDU configuration data */
            P2CONST(IpduM_RxUpPduType, AUTOMATIC, IPDUM_APPL_CONST) RxStatUpPduPtr;

            /* pointer to Rx dynamic PDU configuration data */
            P2CONST(IpduM_RxUpPduType, AUTOMATIC, IPDUM_APPL_CONST) RxDynUpPduPtr;

            /* selector value in received MPdu */
            uint8                       RxSelector;

            /**** End Of Declarations ****/

            RxMpduPtr = &IpduM_RxMPduTable[PdumRxPduId];
            RxUpPduPtr = RxMpduPtr->RxUpPduBaseAddr;
            LoopCount = RxMpduPtr->TotalNumOfIPdus;
            /*  If there are no Dynamic part, then the RxDynUpPduPtr will have NULL_PTR.
        If there are Dynamic part, then the RxDynUpPduPtr will point to RxUpPduPtr when it is identified*/
            RxDynUpPduPtr = NULL_PTR;
            /*  If there are no Static part, then the RxStatUpPduPtr will have NULL_PTR.
        If there are Static part, then the RxStatUpPduPtr will point to RxUpPduPtr when it is identified*/
            RxStatUpPduPtr = NULL_PTR;

            RxSelector = (PduInfoPtr->SduDataPtr[RxMpduPtr->SelectorByte] & RxMpduPtr->SelectorMask);
            for(LoopIndex = 0; LoopIndex < LoopCount; LoopIndex++)
            {
                if(RxUpPduPtr->SelectorValue == IPDUM_INVALID_SELECTOR)
                {
                    /* Identified the Static part. Copy the "pointer to Rx PDU conf" into RxStatUpPduPtr */
                    RxStatUpPduPtr = RxUpPduPtr;
                }

                if(RxUpPduPtr->SelectorValue == RxSelector)
                {
                    /* Identified the dynamic part. Copy the "pointer to Rx PDU conf" into RxDynUpPduPtr */
                    RxDynUpPduPtr = RxUpPduPtr;
                    break;
                }

                RxUpPduPtr++;
            }

            if(RxDynUpPduPtr != NULL_PTR)
            {   /* Dynamic Part exists */
                RxNumOfSubParts = RxDynUpPduPtr->NumOfSubParts;
                SubPartPtr      = RxDynUpPduPtr->RxBaseSubPart;
                RxUpPduBuffPtr  = RxDynUpPduPtr->RxBuffPtr;

                for(LoopIndex = 0; LoopIndex < RxNumOfSubParts; LoopIndex++)
                {
                    IpduM_CopyBuffer(RxMpduPtr->byteOrder,SubPartPtr, PduInfoPtr->SduDataPtr, RxUpPduBuffPtr);
                    SubPartPtr++;
                }

                RxUpPduInfo.SduDataPtr = RxUpPduBuffPtr;
                RxUpPduInfo.SduLength = RxDynUpPduPtr->RxIPduLen;

                IPDUM_UPL_RXINDICATION(RxDynUpPduPtr->RxUpHandleId,&RxUpPduInfo);
            }

            if(RxStatUpPduPtr != NULL_PTR)
            {   /* Static Part exists */
                RxNumOfSubParts = RxStatUpPduPtr->NumOfSubParts;
                SubPartPtr = RxStatUpPduPtr->RxBaseSubPart;
                RxUpPduBuffPtr = RxStatUpPduPtr->RxBuffPtr;

                for(LoopIndex = 0; LoopIndex < RxNumOfSubParts; LoopIndex++)
                {
                    IpduM_CopyBuffer(RxMpduPtr->byteOrder,SubPartPtr, PduInfoPtr->SduDataPtr, RxUpPduBuffPtr);
                    SubPartPtr++;
                }

                RxUpPduInfo.SduDataPtr = RxUpPduBuffPtr;
                RxUpPduInfo.SduLength = RxStatUpPduPtr->RxIPduLen;

                IPDUM_UPL_RXINDICATION(RxStatUpPduPtr->RxUpHandleId,&RxUpPduInfo);
            }
            else
            {
                /* If static part doesn't exists then static part MpdU buffer is left empty */
            }
        }
#endif /* #if defined(IPDUM_RX_PATHWAY) && (IPDUM_RX_PATHWAY != STD_OFF) */
    }
    /*Process the Container PDU's*/
    else if((PdumRxPduId >= IPDUM_NUM_RX_MPDUS) && (PdumRxPduId < IPDUM_TOTAL_NUM_RX_IPDUS))
    {
#if (defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF))
        {
            /*Variable to hold the Container Rx Pdu Id's*/
            PduIdType RxCrPduId;

            /* Pointer to Container(Cr) Rx table*/
            P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainerPduConstPtr_pst;

            /*Pointer to Rx ContainerPduDynamicType table*/
            P2VAR(IpduM_RxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_VAR) RxContainerPduRAMPtr_pst;

            /**** End Of Declarations ****/

            /*As the Container Rx Pdu table is generated based on the index '0' , received Pdu ID should be subtracted
            from the total number of regular Tx Pdu ID's */
            RxCrPduId = PdumRxPduId - IPDUM_NUM_RX_MPDUS;

            /*Initialise the pointer with Rx Container Pdu table*/
            RxContainerPduConstPtr_pst = &IpduM_RxContainerPdu[RxCrPduId];

            /*Initailise the pointer with Rx container Pdu RAM variables */
            RxContainerPduRAMPtr_pst = &IpduM_RxContainerPduDynData[RxCrPduId];


            /*Check the received Sdulength is not exceeding the configured container Pdu length*/
            if(PduInfoPtr->SduLength <= RxContainerPduConstPtr_pst->RxContainerPduLen)
            {
                /*Check if the Pdu Procesing of the received Rx Container is of type immediate*/
                if(RxContainerPduConstPtr_pst->PduProcessing == (boolean)IPDUM_PROCESSING_IMMEDIATE)
                {
                    /*Process the received Container Rx PDU immediately*/
                    IpduM_ProcessRxContainerPdu(PdumRxPduId,PduInfoPtr,RxContainerPduConstPtr_pst);

                    /* Reset current container RAM pdu length after processing this container Pdu */
                    IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->ReadPtr,RxContainerPduConstPtr_pst->RxContainerPduLen) = 0;
                }
                else
                {
                    


                    /*Get the current container queue instance base address*/
                    IpduM_GetRxCurInstanceBaseAddress(RxContainerPduConstPtr_pst,RxContainerPduRAMPtr_pst);

                    /*Copy the length of the received Pdu into the RAM variable*/
                    (IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->WritePtr,RxContainerPduConstPtr_pst->RxContainerPduLen)) = (uint8)PduInfoPtr->SduLength;
                    /* Copy the data into Container's Buffer */
                    rba_BswSrv_MemCopy8(RxContainerPduRAMPtr_pst->WritePtr,PduInfoPtr->SduDataPtr,
                        (IPDUM_CUR_CNTNR_SDU_LEN(RxContainerPduRAMPtr_pst->WritePtr,RxContainerPduConstPtr_pst->RxContainerPduLen)));

                    /*Increment the Current queue size , so that current container queue instance base address should be shifted to next address*/
                    RxContainerPduRAMPtr_pst->CurrentQueueInstance = (( RxContainerPduRAMPtr_pst->CurrentQueueInstance + 1) % (RxContainerPduConstPtr_pst->InstancesInQueue)) ;

                }
            }
            else
            {
                /*As the received length is more than configured container pdu length nothing will be processed.*/
            }
        }
#endif/* #if (defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF)) */
    }
    else
    {
        IPDUM_REPORT_ERROR((PdumRxPduId >= IPDUM_TOTAL_NUM_RX_IPDUS), IPDUMServiceId_RxIndication, IPDUM_E_PARAM)
    }

}

#if (defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF))
/***************************************************************************************************
 Function name    : IpduM_ProcessRxContainerPdu
 Syntax           : IpduM_ProcessRxContainerPdu(  VAR(PduIdType, AUTOMATIC) PdumRxPduId,
                                            P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr,
                                            P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainerPduConstPtr_pst

 Description      : This is the internal function for Processing the received Container Rx PDU.
 Parameter        : PduIdType PdumRxPduId : Received Container Rx PDU ID.
                    PduInfoType PduInfoPtr : Contains the length (SduLength) of the received I-PDU
                                             and a pointer to a buffer (SduDataPtr) containing the I-PDU.
                    IpduM_RxContainerPduType RxContainerPduConstPtr_pst : Pointer to the Container Rx table.
 Return value     : None.
 ***************************************************************************************************/

FUNC(void, IPDUM_CODE) IpduM_ProcessRxContainerPdu(
                                            VAR(PduIdType, AUTOMATIC) PdumRxPduId,
                                            P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr,
                                            P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxContainerPduConstPtr_pst
                                         )
{

    /* pointer to Rx Pdu Buffer */
    P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA)  ContainedRxPduBuffPtr;

    /*Pointer to Contained(Cd) Rx table*/
    P2CONST(IpduM_RxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) RxCdPtr_pst;

    /*local variable to the structure PduInfoType */
    PduInfoType pduInfoPtr_l;

    /*Index Variable to loop through all the contained Rx PDu's*/
    VAR(uint16, AUTOMATIC) index_u16;

    VAR(boolean, AUTOMATIC) proceedFurther_b;

    /*Variable to hold the received Header Id*/
    VAR(uint32, AUTOMATIC) PduHeaderId;

    /*Variable to hold the received Header Id*/
    VAR(uint32, AUTOMATIC) PduDlcValue;

    /* Variable to hold the current byte location in the container buffer */
    VAR(uint32, AUTOMATIC) CurrentByteLocation_u32;

    ContainedRxPduBuffPtr = &IpduM_ContainedRxBuffer_u8[0];

    /* Intialise this local variable to zero, for every container pdu processing */
    CurrentByteLocation_u32 = 0;

    /**** End Of Declarations ****/

    while(CurrentByteLocation_u32 < PduInfoPtr->SduLength)
    {
        proceedFurther_b = FALSE;

        /* Get the Header Id*/
        PduHeaderId = IpduM_ReadIdFromHeader(RxContainerPduConstPtr_pst->HeaderSize, &PduInfoPtr->SduDataPtr[CurrentByteLocation_u32]);

        PduDlcValue = IpduM_ReadDlcFromHeader(RxContainerPduConstPtr_pst->HeaderSize, &PduInfoPtr->SduDataPtr[CurrentByteLocation_u32]);

        /* SWS_IpduM_00210: Check if the PduHeaderId equals to 0x00
         * If Yes, stop processing this complete RxContainerPdu */
        if(PduHeaderId == 0x00u)
        {
            /* CurrentByteLocation_u32 is updated to exit from the while loop */
            CurrentByteLocation_u32 = PduInfoPtr->SduLength;
            return;
        }
        /*Loop through all the contained Rx Pdu's */
        for(index_u16 = 0; (index_u16 < IPDUM_NUM_CONTAINED_RX_PDUS); index_u16++)
        {
            /*Initialise the pointer with Rx Container Pdu table*/
            RxCdPtr_pst = &IpduM_RxContainedPdu[index_u16];

            /*Check if the received Header Id is matching with the Configured Contained Pdu's header Id*/
            if(PduHeaderId ==  RxCdPtr_pst->PduHeaderId )
            {
                /* Global array variable to hold the status of the matching header ID */
                /*Check if the Container's IpduMContainerRxAcceptContainedPdu is ACCEPT_ALL*/
                if(RxContainerPduConstPtr_pst->RxAcceptContainedPdu == IPDUM_ACCEPT_ALL)
                {
                    proceedFurther_b = TRUE;
                }
                else
                {
                    /* If the Container's IpduMContainerRxAcceptContainedPdu is IPDUM_ACCEPT_CONFIGURED ,
                     *  then check if the received container's RxPduID is referred by the contained PDU's*/
                    if(PdumRxPduId == RxCdPtr_pst->ContainerRxPduId)
                    {
                        proceedFurther_b = TRUE;
                    }
                }
            }
            if(proceedFurther_b == TRUE)
            {
                /*[SWS_IpduM_00213] : Check if the DLC received in the header is proper.
                 * The DLC should be less than remaining bytes in the container buffer */
                if(PduDlcValue <= (PduInfoPtr->SduLength - (CurrentByteLocation_u32 + RxContainerPduConstPtr_pst->HeaderSize)))
                {
                    /*Copy the data from the received pointer to the local buffer*/
                    rba_BswSrv_MemCopy8(ContainedRxPduBuffPtr,&(PduInfoPtr->SduDataPtr[CurrentByteLocation_u32 + RxContainerPduConstPtr_pst->HeaderSize]),
                            PduDlcValue);
                    pduInfoPtr_l.SduDataPtr = ContainedRxPduBuffPtr;
                    pduInfoPtr_l.SduLength  = PduDlcValue;
                    IPDUM_UPL_RXINDICATION(RxCdPtr_pst->TargetPduId,&pduInfoPtr_l);
                }
                else
                {
                    /*Report to DET if DLC is gretaer than available buffer in the corresponding Rx container*/
                    IPDUM_REPORT_ERROR((PduDlcValue > (PduInfoPtr->SduLength - (CurrentByteLocation_u32 + RxContainerPduConstPtr_pst->HeaderSize))),
                            IPDUMServiceId_RxIndication, IPDUM_E_HEADER)
                    /* CurrentByteLocation_u32 is updated to maximum value(in this case PduInfoPtr->SduLength) to exit from the while loop */
                    CurrentByteLocation_u32 = PduInfoPtr->SduLength;
                }
                break;
            }
         }

        CurrentByteLocation_u32 += RxContainerPduConstPtr_pst->HeaderSize + PduDlcValue;
    }
}
#endif/* #if (defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF)) */


/* ------------------------------------------------------------------------ */
/* End section for code */

#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

