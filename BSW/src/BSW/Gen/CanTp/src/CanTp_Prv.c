
#include "CanTp.h"
#include "CanTp_Cbk.h"
#include "CanTp_Prv.h"

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"
CanTp_ChannelType CanTp_Channel[CANTP_MAX_CHANNEL_SIZE];
CanTp_ChannelIdType CanTp_TxConfirmationChannel[CANTP_MAX_TX_NPDU_SIZE];
#if(CANTP_TX_BURST_MODE == CANTP_ON)
CanTp_QType CanTp_BurstQ;
#endif
#if(CANTP_CHANGE_PARAMETER_API == STD_ON)
CanTp_ParamPairType CanTp_ParamPair[CANTP_MAX_RX_CONNECTION_SIZE];                 /* Parameter pair is STMin and BS */
#endif
#if(CANTP_CYCLE_COUNTER == CANTP_ON)
volatile CanTp_TickType CanTp_MainFunctionTicks;
#endif
const CanTp_ConfigType *CanTp_CfgPtr;
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"
uint8 CanTp_SubState[CANTP_MAX_CHANNEL_SIZE];
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "CanTp_MemMap.h"
const uint8 CanTp_State[CANTP_NUMBER_OF_SUBSTATES] = {0, 1, 1, 1, 1, 2, 2, 2, 2};   /* Channel SubState-State Mapping */
const uint8 CanTp_AddressSize[CANTP_ADDRESS_ARRAY_SIZE] = {0, 1, 1, 1, 0};          /* STANDARD-EXTENDED-MIXED */
const uint8 CanTp_PciFrameType[CANTP_PCI_ARRAY_SIZE] = {0, 0, 1, 1, 2, 3};          /* PCI Frame Type Mapping */
const uint8 CanTp_PciSize[CANTP_PCI_ARRAY_SIZE] = {1, 2, 2, 6, 1, 3};               /* PCI Size Mapping */
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
const uint8 CanTp_CanDlTable[CANTP_CANDL_ARRAY_SIZE] =
{
	0x08,
	0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x08,0x0c,0x0c,0x0c,0x0c,0x10,0x10,0x10,0x10,
	0x14,0x14,0x14,0x14,0x18,0x18,0x18,0x18,0x20,0x20,0x20,0x20,0x20,0x20,0x20,0x20,
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40,0x40
}; /* CANFD Data Length Mapping table */
#endif
#define CANTP_STOP_SEC_CONST_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.h"

/***********************************************************************************************************************
 Function name    : CanTp_Prv_Transmit
 Syntax           : CanTp_Prv_Transmit(&Context, &SduInfo, &CanIfTxInfo)
 Description      : This is a wrapper function to FF/CF/SF Transmission.
 Parameter        : const CanTp_TxContextType*, PduInfoType*, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_Transmit(const CanTp_TxContextType *Context, PduInfoType* SduInfoPtr,
                               const PduInfoType* CanIfTxInfoPtr)
{
    PduLengthType RemBufSize;

    if(Context->ElapsedValue <= Context->CsTicks)
    {
        switch(PduR_CanTpCopyTxData(Context->PduRPduHandleId, SduInfoPtr, NULL_PTR, &RemBufSize))
        {
            case BUFREQ_OK: /* Register message for transmission with CanIf */
                if(RemBufSize >= Context->PayLoadLength)
                {
                    CanTp_Channel[Context->ChannelId].InitialTicks = Context->Value;
                    CanTp_SubState[Context->ChannelId] = CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION;
                    CanTp_Prv_CanIfTransmit(Context, CanIfTxInfoPtr);
                }
                break;
            case BUFREQ_E_BUSY:
                /* TRACE[SWS_CanTp_00184][SWS_CanTp_00089] If PduR returns E_BUSY, CanTp module retry to copy data. */
                break;
            default:  /* TRACE[SWS_CanTp_00087] */
                CanTp_Prv_PduRConfirmation(Context->PduRApiId, Context->PduRPduHandleId, E_NOT_OK);
                CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_COM);
                CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
                break;
        }
    }
    else
    {   /* TRACE[SWS_CanTp_00167][SWS_CanTp_00280][SWS_CanTp_00229][SWS_CanTp_00205] */
        CanTp_Prv_PduRConfirmation(Context->PduRApiId, Context->PduRPduHandleId, E_NOT_OK);
        CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_TX_COM);
        CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_ProcessRxSingleFrame
 Syntax           : CanTp_Prv_ProcessRxSingleFrame(&Context, &PduInfo)
 Description      : Library function to process single frame reception in RxIndication from CanIf.
 Parameter        : const CanTp_RxContextType*, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_ProcessRxSingleFrame(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    Std_ReturnType Result;
	PduInfoType SduInfo;
	PduLengthType RemBufSize;
    BufReq_ReturnType RetValue;
    CanTp_TickType ElapsedValue;
    CanTp_TickType Value = 0;
    CanTp_ChannelType *Channel = &CanTp_Channel[Context->ChannelId];

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	SduInfo.SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset; /* TRACE[SWS_CanTp_00116] */
    SduInfo.SduLength = Context->SduLength;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

	/* Accept the request for reception if old state is idle or reception(in reception case kill older one.) */
    if(CanTp_Prv_GetConnectionAcceptance(Context, PduInfoPtr) == E_OK)
    {
        Channel->ActiveSduId = Context->SduId;
        Channel->SduLength = Context->SduLength;
        Channel->SduLengthRemaining = Context->SduLength;

        /* RX_DL is set to have valid value to be used in CanTp_CancelReceive */
        CanTp_Prv_SetRxDl(Context->ChannelId, ((uint8)(PduInfoPtr->SduLength)));

        Channel->InitialTicks = Value;

        /* Request is accepted. indicate to upper layer and ask for buffer. check for sufficient
         * buffer availability. copy data. change state to idle. */
        /* TRACE[SWS_CanTp_00079][SWS_CanTp_00329] */
        RetValue = PduR_CanTpStartOfReception(Context->PduRPduHandleId, &SduInfo, Context->SduLength, &RemBufSize);

        switch(RetValue)
        {
            case BUFREQ_OK:
                if(RemBufSize >= Context->SduLength)
                {
                    RetValue = PduR_CanTpCopyRxData(Context->PduRPduHandleId, &SduInfo, &RemBufSize);
                    Result = (RetValue != BUFREQ_OK) ?  E_NOT_OK: E_OK;
                    CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, Result);
                }
                else
                {   /* TRACE[SWS_CanTp_00339] */
                    CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
                }
                break;
            case BUFREQ_E_OVFL: /* TRACE[SWS_CanTp_00353] */
                CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
                break;
            default: /* TRACE[SWS_CanTp_00081] */
                break;
        }

        CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_ProcessRxFirstFrame
 Syntax           : CanTp_Prv_ProcessRxFirstFrame(&Context, &PduInfo)
 Description      : Library function to process first frame reception in RxIndication from CanIf.
 Parameter        : const CanTp_RxContextType*, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_ProcessRxFirstFrame(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    CanTp_ChannelType *Channel = &CanTp_Channel[Context->ChannelId];
    PduInfoType SduInfo;
    PduLengthType RemBufSize;
    uint8 NewSubState = CANTP_IDLE;
    uint8 FlowStatus = CANTP_FC_WAIT;
    uint8 PayLoadLength;
    CanTp_TickType Value = 0;
    CanTp_TickType ElapsedValue;
    BufReq_ReturnType RetValue;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

    PayLoadLength = (uint8)(PduInfoPtr->SduLength - Context->DataOffset);

	SduInfo.SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset; /* TRACE[SWS_CanTp_00116] */
    SduInfo.SduLength = (PduLengthType)PayLoadLength;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    /* Accept the request for reception if old state is idle or reception(in reception case kill older one.) */
    if(CanTp_Prv_GetConnectionAcceptance(Context, PduInfoPtr) == E_OK)
    {
        Channel->ActiveSduId = Context->SduId;
        Channel->SduLength = Context->SduLength;
        CanTp_Prv_SetRxDl(Context->ChannelId, ((uint8)(PduInfoPtr->SduLength)));

        Channel->InitialTicks = Value; /* TRACE[SWS_CanTp_00166] */

        /* Request is accepted. indicate to upper layer and ask for buffer.
         * check for sufficient buffer availability. copy data. change state to idle. */
        /* TRACE[SWS_CanTp_00079][SWS_CanTp_00329][SWS_CanTp_00277] */
        RetValue = PduR_CanTpStartOfReception(Context->PduRPduHandleId, &SduInfo, Context->SduLength, &RemBufSize);


        switch(RetValue) /* TRACE[SWS_CanTp_00064] */
        {
            case BUFREQ_OK:
                if(RemBufSize >= PayLoadLength) /* TRACE[SWS_CanTp_00080] */
                {
                    if(PduR_CanTpCopyRxData(Context->PduRPduHandleId, &SduInfo, &RemBufSize) != BUFREQ_OK)
                    {
                        CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
                        CanTp_Prv_ReportRunTimeError(CANTP_RXINDICATION, CANTP_E_COM);
                        NewSubState = CANTP_IDLE;
                    }
                    else
                    {
                        NewSubState = CANTP_RX_SEND_FC;
                        Channel->SduLengthRemaining = Context->SduLength - PayLoadLength;
                        Channel->BS = 0;
                        Channel->STminTicks = CANTP_INVALID_STMIN_TICKS;
                        Channel->FcWait = 0;
                        Channel->SN = 1;
                    }

                }
                else
                {   /* TRACE[SWS_CanTp_00339] */
                    CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
                    NewSubState = CANTP_IDLE;
                }
                break;
            case BUFREQ_E_OVFL: /* TRACE[SWS_CanTp_00318] */
                FlowStatus = CANTP_FC_OVERFLOW; /* Set FC status to OVFLW. The FC will be sent from the main function */
                NewSubState = CANTP_RX_SEND_FC;
                Channel->BS = 0;
                break;
            default:
                NewSubState = CANTP_IDLE; /* TRACE[SWS_CanTp_00081] */
                break;
        }

        if(CanTp_SubState[Context->ChannelId] == CANTP_RX_RECEPTION_REQUEST_ACCEPTED)
        {
            Channel->FlowStatus = FlowStatus;
            CanTp_SubState[Context->ChannelId] = NewSubState;
        }
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_ProcessRxConsecutiveFrame
 Syntax           : CanTp_Prv_ProcessRxConsecutiveFrame(&Context, &PduInfo)
 Description      : Library function to process consecutive frame reception in RxIndication from CanIf.
 Parameter        : const CanTp_RxContextType*, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_ProcessRxConsecutiveFrame(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
	PduInfoType SduInfo;
	PduLengthType RemBufSize;
	uint8 PayloadLength;
    CanTp_TickType ElapsedValue;
    BufReq_ReturnType RetValue;
    CanTp_ChannelPtrType Channel = &CanTp_Channel[Context->ChannelId];
    CanTp_TickType Value = Channel->InitialTicks; /* Channel objects access outside lock is certified in State check */
    Std_ReturnType NotifyValue = CANTP_INVALID_NOTIFY_VALUE;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

    PayloadLength = Context->CAN_DL - Context->DataOffset;

	SduInfo.SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset; /* TRACE[SWS_CanTp_00116] */

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

	if((CanTp_SubState[Context->ChannelId] == CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME) &&
	   (Context->SduId == Channel->ActiveSduId) && (Channel->BlockCfsRemaining > 0))
	{
		#if(CANTP_STRICT_BSCRTIMEOUT_CHECK == CANTP_ON)
		if(ElapsedValue > CanTp_Prv_GetCfgCsCrTicks(CanTp_CfgPtr->RxSdu + Context->SduId))
		{ /* This time out check is only allowed if OS/Mcu supports the call of there Api in interrupt context */
			CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
			CanTp_Prv_ReportRunTimeError(CANTP_RXINDICATION, CANTP_E_RX_COM);
			CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
		}
		else
		#endif
		{
			NotifyValue = E_NOT_OK; /* TRACE[SWS_CanTp_00271][SWS_CanTp_00314] */

			if(Context->SN == Channel->SN) /* Received Sequence number should be expected Sequence Number else Error */
			{  /* TRACE[SWS_CanTp_00166][SWS_CanTp_00325][SWS_CanTp_00312] */
				Channel->InitialTicks = Value; /* This storage of time stamp is for next CF or FC initiation */

			    SduInfo.SduLength = (Channel->SduLengthRemaining > PayloadLength) ? PayloadLength :
			                         (uint8)Channel->SduLengthRemaining;
			    /* TRACE[SWS_CanTp_00269] */
				RetValue = PduR_CanTpCopyRxData(Context->PduRPduHandleId, &SduInfo, &RemBufSize);

				if(RetValue == BUFREQ_OK)
				{
					Channel->SN++;
					Channel->SN &= CANTP_LOWERNIBBLE_MASK;
					Channel->SduLengthRemaining -= SduInfo.SduLength;
					Channel->BlockCfsRemaining--;

					CanTp_Prv_PrepareFcTransmit(Context->ChannelId); /* If last CF of a block then prepare for FC */

                    NotifyValue = (Channel->SduLengthRemaining != 0) ? CANTP_INVALID_NOTIFY_VALUE : E_OK;
				}
			}

			if(NotifyValue != CANTP_INVALID_NOTIFY_VALUE)
			{ /* TRACE[SWS_CanTp_00084] Terminate Transfer for invalid SN, completion of last CF or Rx not success. */
                CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, NotifyValue);
                CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
			}
		}
	}

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_ProcessRxFlowControlFrame
 Syntax           : CanTp_Prv_ProcessRxFlowControlFrame(&Context, &PduInfo)
 Description      : Library function to process Flow Control frame reception in RxIndication from CanIf.
 Parameter        : const CanTp_RxContextType*, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_ProcessRxFlowControlFrame(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
	CanTp_ChannelPtrType Channel;
    CanTp_TickType Value;
    CanTp_TickType ElapsedValue;

	/* Select the Active channel which is waiting for Flow Control from normal or shared  */
    Channel = &CanTp_Channel[Context->ChannelId];
    Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */
    CanTp_GetElapsedValue(&Value, &ElapsedValue);

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    /* check for the state to avoid unintentional reception.  */
    if(CanTp_SubState[Context->ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME)
    {
        #if(CANTP_STRICT_BSCRTIMEOUT_CHECK == CANTP_ON)
        if(ElapsedValue > CanTp_Prv_GetCfgBsBrTicks(CanTp_CfgPtr->TxSdu + Channel->ActiveSduId))
        {  /* TRACE[SWS_CanTp_00229] timeout has happened so kill the reception  */
			CanTp_Prv_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
			CanTp_Prv_ReportRunTimeError(CANTP_RXINDICATION, CANTP_E_TX_COM);
			CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
        }
        else
        #endif
        {   /* TRACE[SWS_CanTp_00315] Restart the timer. Transmission side there is no FcWaitMax !!! */
            Channel->InitialTicks = Value; /* Store current time stamp to measure the Time Out. */

            switch(Context->FlowStatus)
            {
                case CANTP_FC_WAIT:
                    Channel->FlowStatus = CANTP_FC_WAIT;
                    break;
                case CANTP_FC_CTS:
                    Channel->FlowStatus = CANTP_FC_CTS;
                    CanTp_Prv_SetTxBlockInfo(Context, PduInfoPtr);
                    CanTp_SubState[Context->ChannelId] = CANTP_TX_SEND_CONSECUTIVE_FRAME;
                    break;
                default: /* TRACE[SWS_CanTp_00317][SWS_CanTp_00309][SWS_CanTp_00205] */
                    /* If Flow Control status is not FC_WAIT or FC_CTS then it is time to kill the Transmission */
                    CanTp_Prv_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
                    CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
                    break;
            }
        }
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_CreateTxSingleFrame
 Syntax           : CanTp_Prv_CreateTxSingleFrame(ChannelId, &PduInfo)
 Description      : Library function to assemble Single Frame in TriggerTransmit function from CanIf.
 Parameter        : CanTp_ChannelIdType, const PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
static Std_ReturnType CanTp_Prv_CreateTxSingleFrame(CanTp_ChannelIdType ChannelId, PduInfoType *PduInfoPtr)
{
	PduInfoType SduInfo;
	PduLengthType RemBufSize;
	uint8 *SduDataPtr;
	uint8 DataOffset;
    uint8 PaddingOffset;
    uint8 CAN_DL;
    uint8 PciId;
    uint32 SduLength;
    uint32 SduLengthRemaining;
    Std_ReturnType Status = E_NOT_OK;
	CanTp_ChannelPtrType Channel = CanTp_Channel + ChannelId;
	const CanTp_TxSduType *Connection;

	if(CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION)
	{
	    Connection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
	    PciId = Channel->PciId;
	    SduLength = Channel->SduLength;
	    SduLengthRemaining = Channel->SduLengthRemaining;

		DataOffset = CanTp_AddressSize[Connection->AddressFormatId] + CanTp_PciSize[PciId];
	    CAN_DL = CanTp_Prv_GetTxDl(Connection);

	    SduDataPtr = PduInfoPtr->SduDataPtr + DataOffset;
	    SduInfo.SduDataPtr = SduDataPtr;
	    SduInfo.SduLength = (uint8)SduLengthRemaining;
	    PduInfoPtr->SduLength = 0;

	    /* Step1: TRACE[SWS_CanTp_00086][SWS_CanTp_00272]take the data bytes from PduR */
        if(PduR_CanTpCopyTxData(Connection->PduRPduHandleId, &SduInfo, NULL_PTR, &RemBufSize) != BUFREQ_OK)
        {
            CanTp_Prv_ReportRunTimeError(CANTP_TRIGGERTRANSMIT, CANTP_E_COM);
        }
        else
        {
            /* Step2: if padding is ON then assemble Padding bytes. */
            if(CanTp_Prv_GetBit(Connection->BitFields, CANTP_PADDINGON))
            {   /* TRACE[SWS_CanTp_00351] If data length which shall be transmitted via CanIf_Transmit() does not */
                CAN_DL = CanTp_Prv_GetCanDl(DataOffset + SduInfo.SduLength); /* TRACE[SWS_CanTp_00351] */
                PaddingOffset = (uint8)(DataOffset + SduInfo.SduLength);
                SduDataPtr = PduInfoPtr->SduDataPtr + PaddingOffset; /* TRACE[SWS_CanTp_00059][SWS_CanTp_00348] */
                CanTp_Prv_ArrayInit(SduDataPtr, CAN_DL - PaddingOffset, CANTP_PADDING_BYTE);
            }
            else
            {
                CAN_DL = (uint8)(DataOffset + SduInfo.SduLength);
            }

            SduDataPtr = PduInfoPtr->SduDataPtr;
            if(Connection->AddressFormatId != 0)
            {/* Step3: TRACE[SWS_CanTp_00281] Prepend the Address byte if extended addressing or Mixed addressing */
                *SduDataPtr = Connection->Address;
                SduDataPtr++;
            }

            /* Step4: PCI bytes calculation and assembly */
            if(PciId == CANTP_NPCI_SFCAN)
            {	/* SingleFrame (SF) (CAN_DL <= 8)  */
                *SduDataPtr = (uint8)SduLength;
            }
            else
            {
                #if(CANTP_CANFD_SUPPORT == CANTP_ON)
                if(PciId == CANTP_NPCI_SFCANFD)
                {   /* SingleFrame (SF) (CAN_DL > 8)  */
                    SduDataPtr[0] = 0x00;
                    SduDataPtr[1] = (uint8)SduLength;
                }
                #endif
            }

            PduInfoPtr->SduLength = CAN_DL;
            Status = E_OK;
        }
	}

	return Status;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_CreateTxFirstFrame
 Syntax           : CanTp_Prv_CreateTxFirstFrame(ChannelId, &PduInfo)
 Description      : Library function to assemble First frame in TriggerTransmit function from CanIf.
 Parameter        : CanTp_ChannelIdType, const PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
static Std_ReturnType CanTp_Prv_CreateTxFirstFrame(CanTp_ChannelIdType ChannelId, PduInfoType *PduInfoPtr)
{
	PduInfoType SduInfo;
	PduLengthType RemBufSize;
    uint32 SduLength;
	uint8 *SduDataPtr;
	uint8 DataOffset;
	uint8 CAN_DL;
	uint8 PciId;
	CanTp_ChannelPtrType Channel = CanTp_Channel + ChannelId;
    Std_ReturnType Status = E_NOT_OK;
	const CanTp_TxSduType *Connection;

    if(CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION)
    {
        Connection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
        PciId = Channel->PciId;
        DataOffset = CanTp_AddressSize[Connection->AddressFormatId] + CanTp_PciSize[PciId];
        CAN_DL = CanTp_Prv_GetTxDl(Connection);
        SduLength = Channel->SduLength;

        SduDataPtr = PduInfoPtr->SduDataPtr + DataOffset;
        SduInfo.SduDataPtr = SduDataPtr;
        SduInfo.SduLength = CAN_DL - DataOffset;
        PduInfoPtr->SduLength = 0;

        /* Step1: TRACE[SWS_CanTp_00086][SWS_CanTp_00272]take the data bytes from PduR */
        if(PduR_CanTpCopyTxData(Connection->PduRPduHandleId, &SduInfo, NULL_PTR, &RemBufSize) != BUFREQ_OK)
        {
            CanTp_Prv_ReportRunTimeError(CANTP_TRIGGERTRANSMIT, CANTP_E_COM);
        }
        else
        {
            SduDataPtr = PduInfoPtr->SduDataPtr;
            if(Connection->AddressFormatId != CANTP_STANDARD)
            {/* Step2: TRACE[SWS_CanTp_00281] Prepend the Address byte if extended addressing or Mixed addressing */
                *SduDataPtr = Connection->Address;
                SduDataPtr++;
            }

            /* Step3: PCI bytes calculation and assembly */
            if(PciId == CANTP_NPCI_FFCAN)
            {   /* FirstFrame (FF) (FF_DL <= 4095)  */
                SduDataPtr[0] = 0x10 + (uint8)(SduLength >> 0x08u);
                SduDataPtr[1] = (uint8)SduLength;
            }
            else
            {
                #if(CANTP_CANFD_SUPPORT == CANTP_ON)
                if(PciId == CANTP_NPCI_FFCANFD)
                {   /* FirstFrame (FF) (FF_DL > 4095)  */
                    SduDataPtr[0] = 0x10;
                    SduDataPtr[1] = 0x00;
                    SduDataPtr[2] = (uint8)(SduLength >> 0x18u);
                    SduDataPtr[3] = (uint8)(SduLength >> 0x10u);
                    SduDataPtr[4] = (uint8)(SduLength >> 0x08u);
                    SduDataPtr[5] = (uint8)SduLength;
                }
                #endif
            }

            PduInfoPtr->SduLength = CAN_DL;
            Status = E_OK;
        }
    }

    return Status;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_CreateTxConsecutiveFrame
 Syntax           : CanTp_Prv_CreateTxConsecutiveFrame(ChannelId, &PduInfo)
 Description      : Library function to assemble consecutive Frame in TriggerTransmit function from CanIf.
 Parameter        : CanTp_ChannelIdType, const PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
static Std_ReturnType CanTp_Prv_CreateTxConsecutiveFrame(CanTp_ChannelIdType ChannelId, PduInfoType *PduInfoPtr)
{
	PduLengthType RemBufSize;
	PduInfoType SduInfo;
    uint8 PaddingOffset;
	uint8 *SduDataPtr;
	uint8 DataOffset;
	uint8 CAN_DL;
    uint8 SN;
	uint8 MaxCopyLength;
	uint32 SduLengthRemaining;
	CanTp_ChannelPtrType Channel = CanTp_Channel + ChannelId;
    Std_ReturnType Status = E_NOT_OK;
	const CanTp_TxSduType *Connection;

    if(CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION)
    {
        Connection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
        SN = Channel->SN;
        SduLengthRemaining = Channel->SduLengthRemaining;

        DataOffset = CanTp_AddressSize[Connection->AddressFormatId] + CANTP_CF_PCISIZE;
        CAN_DL = CanTp_Prv_GetTxDl(Connection);
        MaxCopyLength = CAN_DL - DataOffset;
        SduInfo.SduDataPtr = PduInfoPtr->SduDataPtr + DataOffset;
        SduInfo.SduLength = (SduLengthRemaining > MaxCopyLength) ? MaxCopyLength : (uint8)SduLengthRemaining;
        PduInfoPtr->SduLength = 0;

        /* Step1: TRACE[SWS_CanTp_00086][SWS_CanTp_00272]take the data bytes from PduR */
        if(PduR_CanTpCopyTxData(Connection->PduRPduHandleId, &SduInfo, NULL_PTR, &RemBufSize) != BUFREQ_OK)
        {
            CanTp_Prv_ReportRunTimeError(CANTP_TRIGGERTRANSMIT, CANTP_E_COM);
        }
        else
        {
            if(SduLengthRemaining < MaxCopyLength)
            {   /* Step2: if padding is ON then assemble Padding bytes. */
                if(CanTp_Prv_GetBit(Connection->BitFields, CANTP_PADDINGON))
                {   /* TRACE[SWS_CanTp_00351] If data length which shall be transmitted via CanIf_Transmit() does not */
                    CAN_DL = CanTp_Prv_GetCanDl(DataOffset + SduInfo.SduLength); /* TRACE[SWS_CanTp_00351] */
                    PaddingOffset = (uint8)(DataOffset + SduInfo.SduLength);
                    SduDataPtr = PduInfoPtr->SduDataPtr + PaddingOffset; /* TRACE[SWS_CanTp_00059] */
                    CanTp_Prv_ArrayInit(SduDataPtr, CAN_DL - PaddingOffset, CANTP_PADDING_BYTE);
                }
                else
                {
                    CAN_DL = (uint8)(DataOffset + SduInfo.SduLength);
                }
            }

            SduDataPtr = PduInfoPtr->SduDataPtr;

            if(Connection->AddressFormatId != CANTP_STANDARD)
            {   /* Step3: TRACE[SWS_CanTp_00281] if Addressing is mixed or extended then assemble Addressing byte */
                *SduDataPtr = Connection->Address;
                SduDataPtr++;
            }

            *SduDataPtr = (CANTP_CF_HIGHNIBBLE | SN); /* Step4: assemble Sequence number */
            PduInfoPtr->SduLength = CAN_DL;
            Status = E_OK;
        }
    }

    return Status;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_CreateTxFlowControlFrame
 Syntax           : CanTp_Prv_CreateTxFlowControlFrame(ChannelId, &PduInfo)
 Description      : TRACE[SWS_CanTp_00282] Library function to assemble flow control Frame in TriggerTransmit function
                    from CanIf. TxPduId is same as Channel Id (also TxFcNpduId)
 Parameter        : CanTp_ChannelIdType, const PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
static Std_ReturnType CanTp_Prv_CreateTxFlowControlFrame(CanTp_ChannelIdType ChannelId, PduInfoType *PduInfoPtr)
{
	uint8 *SduDataPtr = PduInfoPtr->SduDataPtr;
    uint8 PaddingOffset;
	PduLengthType SduLength = CANTP_FC_PCISIZE;
    CanTp_ChannelPtrType Channel = CanTp_Channel + ChannelId;
    Std_ReturnType Status = E_NOT_OK;
    uint8 BS;
    uint8 STMin;
    uint8 FlowStatus;
    const CanTp_RxSduType *Connection;

	PduInfoPtr->SduLength = 0;

    if(CanTp_SubState[ChannelId] == CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION)
    {
        Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
        STMin = CanTp_Prv_GetRxParam(Channel->ActiveSduId, TP_STMIN);
        FlowStatus = Channel->FlowStatus;
        BS = Channel->BS;

        if(Connection->AddressFormatId != CANTP_STANDARD)
        {   /* Step1: TRACE[SWS_CanTp_00281][SWS_CanTp_00283] addressing byte for extended or mixed addressing. */
            *SduDataPtr = Connection->Address;
            SduDataPtr++;
            SduLength++;
        }

        *SduDataPtr =  (uint8)(CANTP_FC_HIGHNIBBLE | FlowStatus);
        SduDataPtr++;

        /* Step2: assemble block size from configuration */
        *SduDataPtr = BS;

        SduDataPtr++;
        /* Step3: assemble STMin value from configuration */
        *SduDataPtr = STMin;
        SduDataPtr++;

        if(CanTp_Prv_GetBit(Connection->BitFields, CANTP_PADDINGON)) /* Step4: assemble padding bytes if enabled. */
        {   /* TRACE[SWS_CanTp_00351] If the data length which shall be transmitted via CanIf_Transmit() does not */
            PaddingOffset = CanTp_AddressSize[Connection->AddressFormatId] + CANTP_FC_PCISIZE;
            /* TRACE[SWS_CanTp_00059][SWS_CanTp_00347] */
            CanTp_Prv_ArrayInit(SduDataPtr, CANTP_DEFAULT_CAN_DL - PaddingOffset, CANTP_PADDING_BYTE);
            SduLength = CANTP_DEFAULT_CAN_DL;
        }

        PduInfoPtr->SduLength = SduLength;
        Status = E_OK;
    }

    return Status;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_TxSendConsecutiveFrame
 Syntax           : CanTp_Prv_TxSendConsecutiveFrame(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_TX_SEND_CONSECUTIVE_FRAME.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_TxSendConsecutiveFrame(CanTp_ChannelIdType ChannelId)
{
	uint8 CAN_DL;
    PduInfoType SduInfo;
	PduInfoType PduInfo;
    CanTp_ChannelIdType TxConfirmationChannel;
    const CanTp_TxSduType *Connection;
	uint8 MaxLength;
	CanTp_TxContextType Context;
    CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];

    Context.ChannelId = ChannelId;
    Context.PduRApiId = CANTP_TX_PDUR_CONFIRMATION;

    Context.Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */

    CanTp_GetElapsedValue(&(Context.Value), &(Context.ElapsedValue));

    SduInfo.SduLength = 0;
    SduInfo.SduDataPtr = NULL_PTR;

    PduInfo.SduDataPtr = NULL_PTR;

	SchM_Enter_CanTp_EXCLUSIVE_AREA();

	Connection = (CanTp_SubState[ChannelId] == CANTP_TX_SEND_CONSECUTIVE_FRAME) ?
	             (CanTp_CfgPtr->TxSdu + Channel->ActiveSduId) : NULL_PTR;
	TxConfirmationChannel = (Connection != NULL_PTR) ? CanTp_TxConfirmationChannel[Connection->TxConfirmationId] : 0;

	if(TxConfirmationChannel == CANTP_INVALID_CHANNEL) /* It means confirmation is not pending for this Pdu. */
	{
        Context.PduRPduHandleId = Connection->PduRPduHandleId;
        Context.PduId = Connection->TxPduId;
        Context.TxConfirmationId = Connection->TxConfirmationId;
        CAN_DL = CanTp_Prv_GetTxDl(Connection);
        PduInfo.SduLength = CAN_DL;
        Context.CsTicks = CanTp_Prv_GetCfgCsCrTicks(Connection);

        MaxLength = CAN_DL - CANTP_CF_PCISIZE - CanTp_AddressSize[Connection->AddressFormatId];
        Context.PayLoadLength = (Channel->SduLengthRemaining < MaxLength) ?
                                (uint8)(Channel->SduLengthRemaining) : MaxLength;

        if((Context.ElapsedValue >= Channel->STminTicks) || (Channel->PciId != CANTP_NPCI_CF))
        {
            Channel->PciId = CANTP_NPCI_CF;

            CanTp_Prv_Transmit(&Context, &SduInfo, &PduInfo);
        }
	}

	SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_TxWaitForFlowControlFrame
 Syntax           : CanTp_Prv_TxWaitForFlowControlFrame(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_TxWaitForFlowControlFrame(CanTp_ChannelIdType ChannelId)
{
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    const CanTp_TxSduType *Connection;
    CanTp_TickType Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */
    CanTp_TickType ElapsedValue;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if(CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME)
    {
        Connection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
        if(ElapsedValue > CanTp_Prv_GetCfgBsBrTicks(Connection)) /* TRACE[SWS_CanTp_00315] */
        { /* TRACE[SWS_CanTp_00316][SWS_CanTp_00229][SWS_CanTp_00205][SWS_CanTp_00205] */
            CanTp_Prv_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
            CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_TX_COM);
            CanTp_SubState[ChannelId] = CANTP_IDLE;
        }
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_TxWaitForTransmitConfirmation
 Syntax           : CanTp_Prv_TxWaitForTransmitConfirmation(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_TxWaitForTransmitConfirmation(CanTp_ChannelIdType ChannelId)
{
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    const CanTp_TxSduType *Connection;
    CanTp_TickType Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */
    CanTp_TickType ElapsedValue;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if(CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION)
    {
        Connection = CanTp_CfgPtr->TxSdu + Channel->ActiveSduId;
        if(ElapsedValue > CanTp_Prv_GetCfgAsArTicks(Connection))
        {   /* TRACE[SWS_CanTp_00310][SWS_CanTp_00075][SWS_CanTp_00229][SWS_CanTp_00205] In case of N_As timeout Stop
               connection  */
            CanTp_Prv_PduRConfirmation(CANTP_TX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
            CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_TX_COM);
            /* TRACE[SWS_CanTp_00248] */
            CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
            CanTp_SubState[ChannelId] = CANTP_IDLE;
        }
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_TxTransmissionRequestAccepted
 Syntax           : CanTp_Prv_TxTransmissionRequestAccepted(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_TxTransmissionRequestAccepted(CanTp_ChannelIdType ChannelId)
{
	uint8 CAN_DL;
	uint8 DataOffset;
    PduInfoType SduInfo;
	PduInfoType PduInfo;
    CanTp_ChannelIdType TxConfirmationChannel;
	CanTp_ChannelType *Channel = &CanTp_Channel[ChannelId];
    const CanTp_TxSduType *Connection;
    CanTp_TxContextType Context;

    Context.ChannelId = ChannelId;
    Context.PduRApiId = CANTP_TX_PDUR_CONFIRMATION;

    Context.Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */

    CanTp_GetElapsedValue(&(Context.Value), &(Context.ElapsedValue));

	SduInfo.SduLength = 0;
	SduInfo.SduDataPtr = NULL_PTR;

    PduInfo.SduDataPtr = NULL_PTR;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    Connection = (CanTp_SubState[ChannelId] == CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED) ?
                 (CanTp_CfgPtr->TxSdu + Channel->ActiveSduId) : NULL_PTR;
    TxConfirmationChannel = (Connection != NULL_PTR) ? CanTp_TxConfirmationChannel[Connection->TxConfirmationId] : 0;

    if(TxConfirmationChannel == CANTP_INVALID_CHANNEL) /* It means confirmation is not pending for this Pdu. */
    {
        Context.PduRPduHandleId = Connection->PduRPduHandleId;
        Context.PduId = Connection->TxPduId;
        Context.TxConfirmationId = Connection->TxConfirmationId;
        Channel->BlockCfsRemaining = 0;
        Channel->SduLengthRemaining = Channel->SduLength;
        Channel->SN = 1;

        DataOffset = CanTp_AddressSize[Connection->AddressFormatId] + CanTp_PciSize[Channel->PciId];
        CAN_DL = CanTp_Prv_GetTxDl(Connection);
        PduInfo.SduLength = CAN_DL;
        Context.PayLoadLength = (Channel->PciId >= CANTP_NPCI_FFCAN) ? (CAN_DL - DataOffset) :
                                                                       (uint8)(Channel->SduLength);
        Context.CsTicks = CanTp_Prv_GetCfgCsCrTicks(Connection);

        CanTp_Prv_Transmit(&Context, &SduInfo, &PduInfo);
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_Idle
 Syntax           : CanTp_Prv_Idle(ChannelId)
 Description      : Dummy State function to handle for CanTp Channel w.r.t. State CANTP_IDLE.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_Idle(CanTp_ChannelIdType ChannelId)
{
	(void)ChannelId; /* Great to see you here. */
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_RxReceptionRequestAccepted
 Syntax           : CanTp_Prv_RxReceptionRequestAccepted(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_RX_RECEPTION_REQUEST_ACCEPTED.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_RxReceptionRequestAccepted(CanTp_ChannelIdType ChannelId)
{
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    const CanTp_RxSduType *Connection;
    CanTp_TickType Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */
    CanTp_TickType ElapsedValue;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if(CanTp_SubState[ChannelId] == CANTP_RX_RECEPTION_REQUEST_ACCEPTED)
    {
        Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
        if(ElapsedValue > CanTp_Prv_GetCfgBsBrTicks(Connection))
        {  /* TRACE[SWS_CanTp_00166][SWS_CanTp_00229] */
            CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
            CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_RX_COM);
            CanTp_SubState[ChannelId] = CANTP_IDLE;
        }
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_RxSendFlowControlFrame
 Syntax           : CanTp_Prv_RxSendFlowControlFrame(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_RX_SEND_FC.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_RxSendFlowControlFrame(CanTp_ChannelIdType ChannelId)
{
	PduInfoType PduInfo;
    PduInfoType SduInfo;
    CanTp_TickType ElapsedValue;
    CanTp_ChannelIdType TxConfirmationChannel;
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    const CanTp_RxSduType *Connection;
	CanTp_TickType Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */
    boolean IsFcReady = (Channel->FlowStatus > CANTP_FC_WAIT) ? TRUE : FALSE;
    CanTp_TxContextType Context;

    Context.ChannelId = ChannelId;
    Context.PduRApiId = CANTP_RX_PDUR_CONFIRMATION;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	SduInfo.SduLength = 0;
	SduInfo.SduDataPtr = NULL_PTR;

    PduInfo.SduLength = CANTP_DEFAULT_CAN_DL;
    PduInfo.SduDataPtr = NULL_PTR;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    Connection = (CanTp_SubState[ChannelId] == CANTP_RX_SEND_FC) ?
                 (CanTp_CfgPtr->RxSdu + Channel->ActiveSduId) : NULL_PTR;
    TxConfirmationChannel = (Connection != NULL_PTR) ? CanTp_TxConfirmationChannel[Connection->TxConfirmationId] : 0;

    if(TxConfirmationChannel == CANTP_INVALID_CHANNEL) /* It means confirmation is not pending for this Pdu. */
    {
        Channel->BlockCfsRemaining = 0;
        Context.PduRPduHandleId = Connection->PduRPduHandleId;
        Context.PduId = Connection->TxPduId;
        Context.TxConfirmationId = Connection->TxConfirmationId;

        if(Channel->FlowStatus != CANTP_FC_OVERFLOW)
        {   /* TRACE[SWS_CanTp_00222] */
            if(PduR_CanTpCopyRxData(Context.PduRPduHandleId, &SduInfo, &(Context.RemBufSize)) != BUFREQ_OK)
            {
                CanTp_Prv_PduRConfirmation(Context.PduRApiId, Context.PduRPduHandleId, E_NOT_OK);
                CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_COM);
                CanTp_SubState[Context.ChannelId] = CANTP_IDLE;
                IsFcReady = FALSE;
            }
			else
			{
				if(Channel->FlowStatus != CANTP_FC_CTS)
				{
					/* TRACE[SWS_CanTp_00325] Preparation for N_Br Timer if required. */
					CanTp_Prv_SetRxBlockInfo(ChannelId, Context.RemBufSize);
					IsFcReady = (Channel->FlowStatus != CANTP_FC_CTS) ? IsFcReady : TRUE; /* TRACE[SWS_CanTp_00224] */
				}
			}

			if((Channel->FlowStatus == CANTP_FC_WAIT) && ((ElapsedValue >= CanTp_Prv_GetCfgBsBrTicks(Connection)) ||
			   (Channel->FcWait == 0)))
            {
                if(Channel->FcWait < CanTp_Prv_GetRxCfgFcWaitMax(Channel->ActiveSduId))
                {    /* TRACE[SWS_CanTp_00082][SWS_CanTp_00325][SWS_CanTp_00341]If N_Br timer expires reload N_Br */
                     Channel->FcWait++;
                     Channel->InitialTicks = Value;
                     IsFcReady = TRUE;
                }
                else
                {   /* TRACE[SWS_CanTp_00223] */
                    CanTp_Prv_PduRConfirmation(Context.PduRApiId, Context.PduRPduHandleId, E_NOT_OK);
                    CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_RX_COM);
                    CanTp_SubState[Context.ChannelId] = CANTP_IDLE;
                }
            }
        }

        CanTp_Prv_FcTransmit(&Context, &PduInfo, IsFcReady, Value);
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_RxWaitForFcTransmitConfirmation
 Syntax           : CanTp_Prv_RxWaitForFcTransmitConfirmation(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_RxWaitForFcTransmitConfirmation(CanTp_ChannelIdType ChannelId)
{
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    const CanTp_RxSduType *Connection;
    CanTp_TickType Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */
    CanTp_TickType ElapsedValue;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if(CanTp_SubState[ChannelId] == CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION)
    {
        Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
        if(ElapsedValue > CanTp_Prv_GetCfgAsArTicks(Connection))
        {   /* TRACE[SWS_CanTp_00311][SWS_CanTp_00229] */
            CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
            CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_RX_COM);
            /* TRACE[SWS_CanTp_00248] */
            CanTp_TxConfirmationChannel[Connection->TxConfirmationId] = CANTP_INVALID_CHANNEL;
            CanTp_SubState[ChannelId] = CANTP_IDLE;
        }
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_RxWaitForConsecutiveFrame
 Syntax           : CanTp_Prv_RxWaitForConsecutiveFrame(ChannelId)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
static void CanTp_Prv_RxWaitForConsecutiveFrame(CanTp_ChannelIdType ChannelId)
{
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    const CanTp_RxSduType *Connection;
	CanTp_TickType Value = Channel->InitialTicks;  /* Channel objects access outside lock is certified in State check */
	CanTp_TickType ElapsedValue;

    CanTp_GetElapsedValue(&Value, &ElapsedValue);

	SchM_Enter_CanTp_EXCLUSIVE_AREA();

	if(CanTp_SubState[ChannelId] == CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME)
	{
	    Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
        if(ElapsedValue > CanTp_Prv_GetCfgCsCrTicks(Connection))
        {   /* TRACE[SWS_CanTp_00313][SWS_CanTp_00229] */
            CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Connection->PduRPduHandleId, E_NOT_OK);
            CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_RX_COM);
            CanTp_SubState[ChannelId] = CANTP_IDLE;
        }
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();
}

#if(CANTP_TX_BURST_MODE == CANTP_ON)
/***********************************************************************************************************************
 Function name    : CanTp_Prv_BurstMainFunction
 Syntax           : CanTp_Prv_BurstMainFunction(ChannelId, TriggerPoint)
 Description      : State function to process and manipulate the state variables for CanTp Channel w.r.t. State
                    CANTP_TX_SEND_CONSECUTIVE_FRAME in burst mode.
 Parameter        : CanTp_ChannelIdType, uint8
 Return value     : None
***********************************************************************************************************************/
void CanTp_Prv_BurstMainFunction(CanTp_ChannelIdType ChannelId, uint8 TriggerPoint)
{
    if(ChannelId < CanTp_CfgPtr->NumberOfChannels)
    {
        if((CanTp_Channel[ChannelId].STminTicks == 0u)&&(CanTp_SubState[ChannelId] == CANTP_TX_SEND_CONSECUTIVE_FRAME))
        {
            if(CanTp_Prv_PutInQ(ChannelId) == E_OK)
            {
                #if(CANTP_SCHM_SUPPORT == CANTP_ON)
                CanTp_Prv_ActivateMainFunction(TriggerPoint);
                #else
                CanTp_MainFunction();
                (void)TriggerPoint;
                #endif
            }
        }
    }
}
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.h"

/***********************************************************************************************************************
Private Export Function Array definitions [not to be used outside CanTp Module]
***********************************************************************************************************************/

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

/* Chanel State Structure Array containing the MainState and sub StateFunction */
const CanTp_StateFuncType CanTp_StateFunctions[CANTP_NUMBER_OF_SUBSTATES] =
{
    &CanTp_Prv_Idle,
    &CanTp_Prv_TxTransmissionRequestAccepted,
    &CanTp_Prv_TxWaitForTransmitConfirmation,
    &CanTp_Prv_TxWaitForFlowControlFrame,
	&CanTp_Prv_TxSendConsecutiveFrame,
	&CanTp_Prv_RxReceptionRequestAccepted,
	&CanTp_Prv_RxSendFlowControlFrame,
	&CanTp_Prv_RxWaitForFcTransmitConfirmation,
	&CanTp_Prv_RxWaitForConsecutiveFrame
};

/* Processing function Array to be used in RxIndication */
const CanTp_ProcessFrameType  CanTp_ProcessFrame[CANTP_NUMBER_OF_FRAME_TYPES] =
{
	&CanTp_Prv_ProcessRxSingleFrame,
	&CanTp_Prv_ProcessRxFirstFrame,
	&CanTp_Prv_ProcessRxConsecutiveFrame,
	&CanTp_Prv_ProcessRxFlowControlFrame
};

/* Frame Assembly function Array to be used in TriggerTransmit */
const CanTp_CreateFrameType  CanTp_CreateFrame[CANTP_NUMBER_OF_FRAME_TYPES] =
{
	&CanTp_Prv_CreateTxSingleFrame,
	&CanTp_Prv_CreateTxFirstFrame,
	&CanTp_Prv_CreateTxConsecutiveFrame,
	&CanTp_Prv_CreateTxFlowControlFrame
};

/* PduR Confirmation/Indication Api */
const CanTp_PduRConfirmationApiType  CanTp_PduRConfirmationApis[CANTP_NUMBER_OF_PDUR_CONFIRMATION_TYPES] =
{
    &PduR_CanTpTxConfirmation,
    &PduR_CanTpRxIndication     /* PduR_<User:Lo>RxConfirmation as per Harmonized Api specification of ComStack */
};

#if((CANTP_SCHM_SUPPORT == CANTP_ON) && (CANTP_TX_BURST_MODE == CANTP_ON))
/* Trigger Api */
const CanTp_SchMTriggerApiType  CanTp_SchMTriggerApis[CANTP_NUMBER_OF_TRIGGER_POINTS] =
{
    &SchM_ActMainFunction_CanTp_RxIndication,
    &SchM_ActMainFunction_CanTp_TxConfirmation
};
#endif

#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
