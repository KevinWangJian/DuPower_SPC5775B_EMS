

#include "PduR_IpduM.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != IPDUM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != IPDUM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "IpduM_Priv.h"

/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define IPDUM_START_SEC_CODE
#include "IpduM_MemMap.h"
#if defined(IPDUM_CONTAINER_TX_PDU) && (IPDUM_CONTAINER_TX_PDU != STD_OFF)

LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_WriteHeaderToContainer(uint32 headerInfo, P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr);

/**************************************************************************************************/
/* Global functions (declared in header files )                                                   */
/**************************************************************************************************/
/***************************************************************************************************
 Function name    : IpduM_GetCurInstanceBaseAddress
 Syntax           : IpduM_GetCurInstanceBaseAddress(PduIdType TxCrPduId)
 Description      : This is the internal function for updating Current container instance base address.
 Parameter        : PduIdType TxCrPduId : Container Pdu Id

 Return value     : None.
 ***************************************************************************************************/
FUNC( void, IPDUM_CODE ) IpduM_GetCurInstanceBaseAddress(
        PduIdType TxCrPduId)
{
    /* Pointer to Container(Cr) Tx table*/
    P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCrPtr;

    /*Pointer to Tx ContainerPduDynamicType(CrDyn) table*/
    P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_CONST) TxCrDynptr;

    /*Get the container reference*/
    TxCrPtr = &IpduM_TxContainerPdu[TxCrPduId];

    /*Initilize the Tx Container RAM structure with respective container Pdu Id*/
    TxCrDynptr = &IpduM_TxContainerPduDynData[TxCrPduId];

    /*Deafult value of CurrentQueueInstance is initilized to 0 in init function*/
    /*Ensure that Current queue size never exceeds Max configured Queue size per container*/
    TxCrDynptr->CurrentQueueInstance = (TxCrDynptr->CurrentQueueInstance % TxCrPtr->InstancesInQueue);

    /*Update the address of the Current container Queue instance*/
    TxCrDynptr->WritePtr = (TxCrPtr->BufferPtr+((TxCrPtr->TxContainerPduLen)*(TxCrDynptr->CurrentQueueInstance))
            +(TxCrDynptr->CurrentQueueInstance));
}


/***************************************************************************************************
 Function name    : IpduM_HandlingLastIsBestSemantics
 Syntax           : IpduM_HandlingLastIsBestSemantics(PduIdType TxCdPduId,
                    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
 Description      : This is the internal function for handling Last Is Best Semantics
 Parameter        : PduIdType TxCrPduId : Container Pdu Id
                    P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr :
 Return value     : boolean.
 ***************************************************************************************************/
FUNC(boolean, IPDUM_CODE) IpduM_HandlingLastIsBestSemantics(PduIdType TxCdPduId,
        P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
    /* Pointer to Container(Cr) Tx table*/
    P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCrPtr;

    /*Pointer to Contained(Cd) Tx table*/
    P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCdPtr;

    /*Pointer to Tx ContainerPduDynamicType table*/
    P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_CONST) TxCrDynptr;

    /*Variable to hold the Container Pdu Id*/
    PduIdType TxCrPduId;
    P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) HeaderAddr;
    uint32 HeaderId;
    uint32 Index_u32;
    uint32 Dlc;

    VAR(boolean, AUTOMATIC) LastIsBestFound_b;
    LastIsBestFound_b = FALSE;


    Index_u32 = 0;
    TxCdPtr = &IpduM_TxContainedPdu[TxCdPduId];

    /*Get the contained Pdu's container reference*/
    TxCrPduId = TxCdPtr->ContainerTxPduId;
    TxCrPtr = &IpduM_TxContainerPdu[TxCrPduId];

    /*Initilize the Tx Container RAM structure with respective container Pdu Id*/
    TxCrDynptr = &IpduM_TxContainerPduDynData[TxCrPduId];

    while(Index_u32 < IPDUM_CUR_CNTNR_SDU_LEN(TxCrDynptr->WritePtr,TxCrPtr->TxContainerPduLen))
    {
        HeaderAddr = TxCrDynptr->WritePtr + Index_u32;
        HeaderId = IpduM_ReadIdFromHeader((TxCrPtr->HeaderSize),HeaderAddr);
        Dlc = IpduM_ReadDlcFromHeader((TxCrPtr->HeaderSize),HeaderAddr);
        /*Below condition is to check if contained Pdu already written into container Pdu */
        if(HeaderId == TxCdPtr->PduHeaderId)
        {
            IpduM_CopyBufferToContainer(TxCdPduId, PduInfoPtr->SduLength,
                    PduInfoPtr->SduDataPtr,HeaderAddr);
            LastIsBestFound_b = TRUE;
            break;
        }

        Index_u32 = (Index_u32 + (TxCrPtr->HeaderSize)+Dlc);
    }
    return LastIsBestFound_b;
}

/***************************************************************************************************
 Function name    : IpduM_CopyBufferToContainer
 Syntax           : IpduM_CopyBufferToContainer(PduIdType TxCdPduId,PduLengthType ContainedPduLength,
     P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcPtr,P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr)
 Description      : This is the internal function for copying contained pdu to container.
 Parameter        : PduIdType TxCdPduId: Pdu Id of the contained PDU.
                    PduLengthType ContainedPduLength : the length of the current contained PDU to be copied.
                    P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcPtr : PduInfoType SduDataPtr.
                    P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr : Address of contained where data need to be written.
 Return value     : Void.
 ***************************************************************************************************/

FUNC(void, IPDUM_CODE) IpduM_CopyBufferToContainer(
     PduIdType TxCdPduId,
     PduLengthType ContainedPduLength,
     P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcPtr,
     P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr)
{
    /* Pointer to Container(Cr) Tx table*/
    P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCrPtr;

    /*Pointer to Contained(Cd) Tx table*/
    P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCdPtr;

    /*Variable to hold the Container Pdu Id*/
    PduIdType TxCrPduId;
    uint8 index_u8;
    uint32 header_u32;

    index_u8 = 0;
    header_u32 = 0;

    TxCdPtr = &IpduM_TxContainedPdu[TxCdPduId];

    /*Get the contained Pdu's container reference*/
    TxCrPduId = TxCdPtr->ContainerTxPduId;
    TxCrPtr = &IpduM_TxContainerPdu[TxCrPduId];

    /*Container Buffer need to be */
    SchM_Enter_IpduM_LockTxContainerBuffer();
    if(TxCrPtr->HeaderSize == IPDUM_HEADERTYPE_SHORT_SIZE)
    {
        header_u32 = IPDUM_CREATE_SHORT_HEADER(TxCdPtr->PduHeaderId, ContainedPduLength);
        IpduM_WriteHeaderToContainer(header_u32,DestPtr);
        DestPtr+=IPDUM_FOUR_BYTES;
    }
    else/*If Header is of type LONG */
    {

        #if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN)
        {
            /*Write DLC*/
            IpduM_WriteHeaderToContainer(ContainedPduLength,DestPtr);
            DestPtr+=IPDUM_FOUR_BYTES;
            /*Write header Id */
            IpduM_WriteHeaderToContainer(TxCdPtr->PduHeaderId,DestPtr);
            DestPtr+=IPDUM_FOUR_BYTES;
        }
        #else
        {
            /*Write header Id */
            IpduM_WriteHeaderToContainer(TxCdPtr->PduHeaderId,DestPtr);
            DestPtr+=IPDUM_FOUR_BYTES;
            /*Write DLC*/
            IpduM_WriteHeaderToContainer(ContainedPduLength,DestPtr);
            DestPtr+=IPDUM_FOUR_BYTES;
        }
        #endif /* #if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN) */
    }

    for(index_u8 = 0; index_u8 < ContainedPduLength; index_u8++)
    {
        *DestPtr = *SrcPtr;
        SrcPtr++;
        DestPtr++;
    }
    SchM_Exit_IpduM_LockTxContainerBuffer();
}


/***************************************************************************************************
 Function name    : IpduM_WriteHeaderToContainer
 Syntax           : IpduM_WriteHeaderToContainer(uint32 headerInfo,
        P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr)
 Description      : This is the internal function for copying Header info to container before writing any contained pdu.
 Parameter        : uint32 headerInfo: Header Data either Pdu header-Id or DLC.
                    P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr : Address of contained where data need to be written.
 Return value     : Void.
 ***************************************************************************************************/
LOCAL_INLINE FUNC (void, IPDUM_CODE) IpduM_WriteHeaderToContainer(uint32 headerInfo,
        P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr)
{
    uint8 index_u8;
#if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN)
    {
        for(index_u8 = 0; index_u8 < IPDUM_FOUR_BYTES; index_u8++)
        {
            *DestPtr = *((uint8 *)&headerInfo + index_u8);
            DestPtr++;
        }
    }
#else
    {
        for(index_u8 = IPDUM_FOUR_BYTES; index_u8 > 0; index_u8--)
        {
            *DestPtr = *((uint8 *)&headerInfo + (index_u8 - 1));
            DestPtr++;
        }
    }
#endif /* #if(IPDUM_HEADER_BYTEORDER == IPDUM_LITTLEENDIAN) */
}

/***************************************************************************************************
 Function name    : IpduM_PreparePduRTransmit
 Syntax           : IpduM_PreparePduRTransmit(PduIdType TxCntnrPduId) : Container PduId
 Description      : This is the internal function for transmitting the container to Lower layer
 Parameter        : PduIdType TxCdPduId : Contained Pdu Id
 Return value     : Std_ReturnType.
 ***************************************************************************************************/
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_PreparePduRTransmit(
        PduIdType TxCntnrPduId)
{
    /* Pointer to Container(Cr) Tx table*/
    P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCntnrPtr;

    /*Pointer to Tx ContainerPduDynamicType table*/
    P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_CONST) TxCntnrDynptr;

    Std_ReturnType RetVal;
    /* Structure to hold the data and length of container*/
    PduInfoType CrPduInfo;

    TxCntnrPtr = &IpduM_TxContainerPdu[TxCntnrPduId];

    /*Initilize the Tx Container RAM structure with respective container Pdu Id*/
    TxCntnrDynptr = &IpduM_TxContainerPduDynData[TxCntnrPduId];

    RetVal = E_OK;

    /*[SWS_IpduM_00189]: Wait till the TxConfirmation for the previous Transmission instance is received.
     * During init TxConfRAMTicks is set to 0 for all containers*/
    if(TxCntnrDynptr->TxConfRAMTicks == 0)
    {
        /*ReadPtr will be pointing to Queue instance starting address which is ready to transmit*/
        CrPduInfo.SduLength = IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->ReadPtr , TxCntnrPtr->TxContainerPduLen);
        CrPduInfo.SduDataPtr = TxCntnrDynptr->ReadPtr;

        RetVal = PduR_IpduMTransmit(TxCntnrPtr->TargetPduId, &CrPduInfo);
        if(RetVal != E_NOT_OK)
        {
            /*Set the RAM Sendout Timer to INVALID(0xFFFFu) so that main function Triggers transmit function for valid
             *container instance. The RAM sendTimeout Timer is set after a contained Pdu is written into container*/
            TxCntnrDynptr->TxSendTimeOutTicks = 0xFFFFu;

            if(TxCntnrPtr->ContainerTxTriggerMode == IPDUM_DIRECT)
            {
                /* Start TxConfirmationTimeout timer only for Direct Container.
                 * For TT container it will be loaded in IpduM_TriggerTransmit API*/
                if(TxCntnrPtr->TxConfConstTicks > 0u)
                {
                    TxCntnrDynptr->TxConfRAMTicks = TxCntnrPtr->TxConfConstTicks;
                }
                /*The TxConfirmation RAM pointer is loaded only for Direct mode,
                 * and for TT it is loaded in IpduM_TriggerTransmit api.*/
                TxCntnrDynptr->TxConfPtr = TxCntnrDynptr->ReadPtr;
                /* Increment the readPtr only if the trigger mode is direct,
                 * or else this will be incremented in IpduM_TriggerTransmit API */
                TxCntnrDynptr->ReadPtr =  (TxCntnrDynptr->ReadPtr + ((uint8)(TxCntnrPtr->TxContainerPduLen)+1u));

                /*At anytime if the readPtr reaches last address in the buffer then reset it to starting address*/
                if(TxCntnrDynptr->ReadPtr == ((TxCntnrPtr->BufferPtr) + IPDUM_TOTAL_CNTNR_LEN(TxCntnrPtr->TxContainerPduLen,
                        TxCntnrPtr->InstancesInQueue)))
                {
                    TxCntnrDynptr->ReadPtr = TxCntnrPtr->BufferPtr;
                }
            }
            /* Do not retry this message in the mainfunction as the requested transmit is accepted by the lower,
             * hence reset the RetransmissionRequired flag */
            TxCntnrDynptr->RetransmissionRequired = FALSE;
        }
        else
        {
            /* SWS_IpduM_00195 :The same container should be called in the next main function.
             * If at any point the length in the currentbyte location is greater than the configured container Pdu length,
             * then flush the container data and allow new requests in this instance */
            if(IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr , TxCntnrPtr->TxContainerPduLen) > TxCntnrPtr->TxContainerPduLen)
            {
                IPDUM_CUR_CNTNR_SDU_LEN(TxCntnrDynptr->WritePtr , TxCntnrPtr->TxContainerPduLen) = 0;
                TxCntnrDynptr->TxSendTimeOutTicks = 0xFFFFu;
            }
            else
            {
                TxCntnrDynptr->RetransmissionRequired = TRUE;
            }
        }
    }

    return RetVal;
}

/***************************************************************************************************
 Function name    : IpduM_UpdateTxSendTimeOutTimer
 Syntax           : IpduM_UpdateTxSendTimeOutTimer(PduIdType TxCdPduId, VAR(uint32, AUTOMATIC) CurPduLength)
 Description      : This is the internal function for loading timer to transmit the container
 Parameter        : PduIdType TxCdPduId : Contained Pdu Id
                  : VAR(uint32, AUTOMATIC) CurPduLength) : Current Container Sdu length
 Return value     : Void.
 ***************************************************************************************************/
FUNC(void, IPDUM_CODE) IpduM_UpdateTxSendTimeOutTimer(PduIdType TxCdPduId,
        VAR(uint32, AUTOMATIC) CurPduLength)
{
    /* Pointer to Container(Cr) Tx table*/
    P2CONST(IpduM_TxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCrPtr;

    /*Pointer to Contained(Cd) Tx table*/
    P2CONST(IpduM_TxContainedPduType, AUTOMATIC, IPDUM_APPL_CONST) TxCdPtr;

    /*Pointer to Tx ContainerPduDynamicType table*/
    P2VAR(IpduM_TxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_CONST) TxCrDynptr;

    /*Variable to hold the Container Pdu Id*/
    PduIdType TxCrPduId;

    TxCdPtr = &IpduM_TxContainedPdu[TxCdPduId];

    /*Get the contained Pdu's container reference*/
    TxCrPduId = TxCdPtr->ContainerTxPduId;
    TxCrPtr = &IpduM_TxContainerPdu[TxCrPduId];

    /*Initilize the Tx Container RAM structure with respective container Pdu Id*/
    TxCrDynptr = &IpduM_TxContainerPduDynData[TxCrPduId];


    /*Load the Tx Send time Out timer into the RAM variable.*/
    /*Check if the Tx send time out is configured for Contained or Container*/
    if((TxCdPtr->TxPduSendTimeOut != 0xFFFFu) || (TxCrPtr->TxSendTimeOut != 0xFFFFu))
    {
        /* Check if first contained Pdu is written into the container*/
        if((TxCrPtr->HeaderSize + CurPduLength) == IPDUM_CUR_CNTNR_SDU_LEN(TxCrDynptr->WritePtr,TxCrPtr->TxContainerPduLen))
        {
            /*Compare value with less than or equal, as both may have same value*/
            TxCrDynptr->TxSendTimeOutTicks = (TxCrPtr->TxSendTimeOut <= TxCdPtr->TxPduSendTimeOut) ?
                            ( TxCrPtr->TxSendTimeOut) : (TxCdPtr->TxPduSendTimeOut);
        }
        /*For the Pdu which are not written for first time*/
        else
        {
            if(TxCdPtr->TxPduSendTimeOut < TxCrDynptr->TxSendTimeOutTicks)
            {
                TxCrDynptr->TxSendTimeOutTicks = TxCdPtr->TxPduSendTimeOut;
            }
        }

    }
    /*For the Pdu's which have not configured Tx send time out */
    else
    {
        /* Do nothing. As no TxSendTimeout is configured */
    }
}
#endif

#if defined(IPDUM_CONTAINER_RX_PDU) && (IPDUM_CONTAINER_RX_PDU != STD_OFF)
/***************************************************************************************************
 Function name    : IpduM_GetRxCurInstanceBaseAddress
 Syntax           : IpduM_GetRxCurInstanceBaseAddress( P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxCrPtr_pst,
                                       P2VAR(IpduM_RxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_VAR) RxCrDynptr_pst)
 Description      : This is the internal function for updating Current container instance base address.
 Parameter        :  RxCrPtr_pst : Pointer to the RxContainer Pdu
                     RxCrDynptr_pst : Pointer to the RxContainer RAM table
 Return value     : None.
 ***************************************************************************************************/
FUNC( void, IPDUM_CODE ) IpduM_GetRxCurInstanceBaseAddress(
        P2CONST(IpduM_RxContainerPduType, AUTOMATIC, IPDUM_APPL_CONST) RxCrPtr_pst,
        P2VAR(IpduM_RxContainerPduDynamicType, AUTOMATIC, IPDUM_APPL_VAR) RxCrDynptr_pst)
{

    /*Deafult value of CurrentQueueInstance is initilized to 0 in init function*/
    /*Ensure that Current queue size never exceeds Max configured Queue size per container*/
    /*If the maximum queue size is reached , then it will point the initial starting address*/
    RxCrDynptr_pst->CurrentQueueInstance = (RxCrDynptr_pst->CurrentQueueInstance % RxCrPtr_pst->InstancesInQueue);

    /*Update the address of the Current container Queue instance*/
    RxCrDynptr_pst->WritePtr = (RxCrPtr_pst->BufferPtr+((RxCrPtr_pst->RxContainerPduLen)*(RxCrDynptr_pst->CurrentQueueInstance))
            +( RxCrDynptr_pst->CurrentQueueInstance));

}

/* ------------------------------------------------------------------------ */
/* End section for code */
#endif


#define IPDUM_STOP_SEC_CODE
#include "IpduM_MemMap.h"

