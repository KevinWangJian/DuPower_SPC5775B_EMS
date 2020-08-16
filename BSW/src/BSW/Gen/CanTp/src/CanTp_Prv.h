

#ifndef CANTP_PRV_H
#define CANTP_PRV_H

#include "CanTp.h" /* CanTp.h must be included before CanTp_Types.h */
#if(CANTP_CYCLE_COUNTER != CANTP_ON)
#include "CanTp_Timer.h"              /*  External Timer Handling */
#endif
#include "CanTp_Types.h" /* TRACE[SWS_CanTp_00264] Indirect inclusion of ComStack_Types.h  */
#if(CANTP_SCHM_SUPPORT != CANTP_ON)
#include "CanTp_SchM.h"
#else
#include "SchM_CanTp.h"  /* SchM version not checked as it is not provided in SchM_CanTp.h file */
#endif
#include "PduR_CanTp.h"
#if (!defined(PDUR_AR_RELEASE_MAJOR_VERSION) || (PDUR_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(PDUR_AR_RELEASE_MINOR_VERSION) || (PDUR_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "CanIf.h"
#if (!defined(CANIF_AR_RELEASE_MAJOR_VERSION) || (CANIF_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANIF_AR_RELEASE_MINOR_VERSION) || (CANIF_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
#include "Det.h" /* TRACE[SWS_CanTp_00264] */
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

 /**********************************************************************************************************************
 *    Internal Defines
 **********************************************************************************************************************/

/* Frame Types of CanTp Module */
#define CANTP_SF_HIGHNIBBLE                          (0x00u)
#define CANTP_FF_HIGHNIBBLE                          (0x10u)
#define CANTP_CF_HIGHNIBBLE                          (0x20u)
#define CANTP_FC_HIGHNIBBLE                          (0x30u)

#define CANTP_DEFAULT_CAN_DL                         (8u)
#define CANTP_DLCERROR                               (0xFFu)
#define CANTP_NO_ERROR                               (0u)

/* PCI Size of SF and FF are not fixed. they vary based on FD and SduLength. */
#define CANTP_CF_PCISIZE                             (1u)
#define CANTP_FC_PCISIZE                             (3u)

/* Table 9 - Summary of N_PCI bytes. This is used as PciId */
#define CANTP_NPCI_SFCAN                             (0u)
#define CANTP_NPCI_SFCANFD                           (1u)
#define CANTP_NPCI_FFCAN                             (2u)
#define CANTP_NPCI_FFCANFD                           (3u)
#define CANTP_NPCI_CF                                (4u)
#define CANTP_NPCI_FC                                (5u)
#define CANTP_NPCI_INVALID                           (6u)

/* Maximum Payload Supported by CanTp for Transfer */
#define CANTP_MAXFFDL                                (0xFFFu)
#define CANTP_MAXFDFFDL                              (0xFFFFu)  /* Warning: configure less than 0xFFFFFFFA */
#define CANTP_MAXBLOCKSIZE                           (0xFFu)    /* Maximum Block Size on the bus */

#define CANTP_CANDL_ARRAY_SIZE                       (65u)      /* CAN_DL Table size for mapping */
#define CANTP_PCI_ARRAY_SIZE                         (6u)       /* PCI Table size for mapping */
#define CANTP_ADDRESS_ARRAY_SIZE                     (5u)       /* ADDRESS Table size for mapping */

/* Address Type Format */
#define CANTP_STANDARD                               (0u)
#define CANTP_EXTENDED                               (1u)
#define CANTP_MIXED                                  (2u)

/* STMin and BS range of values */
#define CANTP_MILLISEC_MAX_RANGE                     (0x7Fu)
#define CANTP_MICROSEC_MIN_RANGE                     (0xF1u)
#define CANTP_MICROSEC_MAX_RANGE                     (0xF9u)
#define CANTP_MAX_BS_VALUE                           (0xFFu)

/* BitFields Mask */
#define CANTP_TC_DISABLED                            (0x10u)
#define CANTP_PADDINGON                              (0x08u)
#define CANTP_FUNCTIONAL                             (0x04u)
#define CANTP_FC_DISABLED                            (0x02u)
#define CANTP_FD_ENABLED                             (0x01u)

/* Frame related defines */
#define CANTP_SINGLE_FRAME                           (0x00u)
#define CANTP_FIRST_FRAME                            (0x01u)
#define CANTP_CONSECUTIVE_FRAME                      (0x02u)
#define CANTP_FLOWCONTROL_FRAME                      (0x03u)
#define CANTP_NUMBER_OF_FRAME_TYPES                  (0x04u)
#define CANTP_FRAMETYPE_OFFSET                       (0x04u)
#define CANTP_LOWERNIBBLE_MASK                       (0x0Fu)

#define CANTP_INVALID_DL                             (0xFFu)
#define CANTP_INVALID_NOTIFY_VALUE                   (0xFFu)
#define CANTP_INVALID_CHANNEL                        (CANTP_MAX_CHANNEL_SIZE)

/* Idle Channel State */
#define CANTP_IDLE                                   (0u)
/* Transmission Channel States */
#define CANTP_TRANSMISSION                           (1u)
#define CANTP_TX_TRANSMISSION_REQUEST_ACCEPTED       (1u)
#define CANTP_TX_WAIT_FOR_TRANSMIT_CONFIRMATION      (2u)
#define CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME          (3u)
#define CANTP_TX_SEND_CONSECUTIVE_FRAME              (4u)
/* Reception Channel States */
#define CANTP_RECEPTION                              (2u)
#define CANTP_RX_RECEPTION_REQUEST_ACCEPTED          (5u)
#define CANTP_RX_SEND_FC                             (6u)
#define CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION    (7u)
#define CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME          (8u)

#define CANTP_NUMBER_OF_SUBSTATES                    (9u)

#define CANTP_TX_PDUR_CONFIRMATION                   (0u)
#define CANTP_RX_PDUR_CONFIRMATION                   (1u)
#define CANTP_NUMBER_OF_PDUR_CONFIRMATION_TYPES      (2u)

#define CANTP_TRIGGER_TX_CONFIRMATION                (0u)
#define CANTP_TRIGGER_RX_INDICATION                  (1u)
#define CANTP_NUMBER_OF_TRIGGER_POINTS               (2u)

/* Flow Control States */
#define CANTP_FC_CTS                                 (0u)
#define CANTP_FC_WAIT                                (1u)
#define CANTP_FC_OVERFLOW                            (2u)

/* Function like Macros */
#define CanTp_Prv_PduRConfirmation(Api, id, result)  CanTp_PduRConfirmationApis[Api](id, result)
#define CanTp_Prv_ActivateMainFunction(TriggerPoint) CanTp_SchMTriggerApis[TriggerPoint]()
#define CanTp_Prv_ProcessFrame(Context, PduInfoPtr)  CanTp_ProcessFrame[(Context)->FrameType](Context, PduInfoPtr)
#define CanTp_Prv_FrameType(id)                      CanTp_PciFrameType[CanTp_Channel[id].PciId]
#define CanTp_Prv_CreateFrame(id, PduInfoPtr)        CanTp_CreateFrame[CanTp_Prv_FrameType(id)](id, PduInfoPtr)
#define CanTp_Prv_ExecuteState(ChannelId)            CanTp_StateFunctions[CanTp_SubState[ChannelId]](ChannelId)
#define CanTp_Prv_GetTxChannelId(id)                 CanTp_CfgPtr->TxSdu[id].ChannelId
#define CanTp_Prv_GetRxChannelId(id)                 CanTp_CfgPtr->RxSdu[id].ChannelId
#define CanTp_Prv_GetState(ChannelId)           	 CanTp_State[CanTp_SubState[ChannelId]]
#define CanTp_Prv_GetRxCfgParam(id, param)           CanTp_CfgPtr->Param[CanTp_CfgPtr->RxSdu[id].ParamId].Param[param]
#define CanTp_Prv_GetRxCfgFcWaitMax(id)              CanTp_CfgPtr->Param[CanTp_CfgPtr->RxSdu[id].ParamId].FcWaitMax
#define CanTp_Prv_GetCfgAsArTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].AsArTicks
#define CanTp_Prv_GetCfgBsBrTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].BsBrTicks
#define CanTp_Prv_GetCfgCsCrTicks(Connection)        CanTp_CfgPtr->TimeOut[(Connection)->TimeOutId].CsCrTicks
#define CanTp_Prv_GetTxActiveBits(id)                CanTp_CfgPtr->TxSdu[CanTp_Channel[id].ActiveSduId].BitFields
#define CanTp_Prv_GetRxActiveBits(id)                CanTp_CfgPtr->RxSdu[CanTp_Channel[id].ActiveSduId].BitFields
#if(CANTP_DEV_ERROR_DETECT == CANTP_ON)
#define CanTp_Prv_ReportError(Api, Err)              (void)Det_ReportError(CANTP_MODULE_ID, CANTP_INSTANCE_ID, Api, Err)
#define CanTp_Prv_ReportRunTimeError(Api, Err)       (void)Det_ReportRuntimeError(CANTP_MODULE_ID, CANTP_INSTANCE_ID, \
                                                      Api, Err)
#else
#define CanTp_Prv_ReportError(Api, Err)
#define CanTp_Prv_ReportRunTimeError(Api, Err)
#endif
#if(CANTP_CHANGE_PARAMETER_API != STD_ON)
#define CanTp_Prv_RxParamInit()
#endif
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
#define CanTp_Prv_GetTxDl(Connection)                ((Connection)->TX_DL)
#define CanTp_Prv_GetCanDl(FrameLength)              (CanTp_CanDlTable[FrameLength])
#define CanTp_Prv_GetRxDl(ChannelId)                 (CanTp_Channel[ChannelId].RX_DL)
#define CanTp_Prv_SetRxDl(ChannelId, Value)          (CanTp_Channel[ChannelId].RX_DL = (Value))
#define CanTp_Prv_IsRxDlInValid(RX_DL)               (((RX_DL) != 0x08) && ((RX_DL) != 0x0C) && ((RX_DL) != 0x10) &&\
                                                      ((RX_DL) != 0x14) && ((RX_DL) != 0x18) && ((RX_DL) != 0x20) &&\
                                                      ((RX_DL) != 0x30) && ((RX_DL) != 0x40))
#else
#define CanTp_Prv_GetTxDl(Connection)                (CANTP_DEFAULT_CAN_DL)
#define CanTp_Prv_GetCanDl(FrameLength)              (CANTP_DEFAULT_CAN_DL)
#define CanTp_Prv_GetRxDl(ChannelId)                 (CANTP_DEFAULT_CAN_DL)
#define CanTp_Prv_SetRxDl(ChannelId, Value)
#define CanTp_Prv_IsRxDlInValid(RX_DL)               (((RX_DL) != 0x08))
#endif
#if(CANTP_TX_BURST_MODE != CANTP_ON)
#define CanTp_Prv_QInit()
#define CanTp_Prv_PutInQ(ChannelId)
#define CanTp_Prv_GetFromQ(ChannelId)
#define CanTp_Prv_BurstMainFunction(Id, Point)
#endif
#if(CANTP_CYCLE_COUNTER == CANTP_ON)
#define CanTp_IncrementCounter()                      (CanTp_MainFunctionTicks++)
#else
#define CanTp_IncrementCounter()
#endif
#define CanTp_Prv_BuildBugOn(condition)              ((void)sizeof(char[1 - 2*!!(condition)]))

/***********************************************************************************************************************
 *    Internal Type definitions
 **********************************************************************************************************************/

typedef Std_ReturnType (*CanTp_CreateFrameType)(CanTp_ChannelIdType ChannelId, PduInfoType *PduInfoPtr);

typedef struct /* To be used in CanTp_RxIndication context */
{
	boolean IsFunctional;
	boolean IsPaddingOn;
	boolean IsFdEnabled;
    uint8 Address;
    uint8 FrameType;
	uint8 FlowStatus;
	uint8 SN;
    uint8 DataOffset;
	uint8 AddressFormatId;
	uint8 AddressSize;
	uint8 CAN_DL;
    CanTp_ChannelIdType ChannelId;
	CanTp_SduIdType SduId;
    PduIdType PduId;
    PduIdType PduRPduHandleId;
    PduLengthType SduLength;
}CanTp_RxContextType;

typedef struct  /* To be used in CanTp_MainFunction CanIf Transmission context */
{
    uint8 PduRApiId;
    uint8 PayLoadLength;
    CanTp_ChannelIdType ChannelId;
    PduIdType TxConfirmationId;
    PduIdType PduId;
    PduIdType PduRPduHandleId;
    PduLengthType RemBufSize;
    CanTp_TickType Value;
    CanTp_TickType ElapsedValue;
    CanTp_TickType CsTicks;
}CanTp_TxContextType;

typedef void (*CanTp_ProcessFrameType)(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr);

#if(CANTP_TX_BURST_MODE == CANTP_ON)
typedef struct
{
    uint8 Head_u8;
    uint8 Tail_u8;
    CanTp_ChannelIdType Queue[CANTP_BURST_QUEUE_SIZE];
}CanTp_QType;
#endif

typedef struct
{
    uint8 Param[2];
}CanTp_ParamPairType;

typedef void (*CanTp_StateFuncType)(CanTp_ChannelIdType ChannelId);

typedef struct
{
    #if(CANTP_CANFD_SUPPORT == CANTP_ON)
    uint8 RX_DL;                                    /* CanFd Support: Receive Data Length */
    #endif
    uint8 PciId;                                    /* PCI mapping Id for Frame type under progress */
    uint8 FlowStatus;                               /* Flow Status of Flow Control Frames */
    uint8 SN;                                       /* Current Sequence Number */
    uint8 BS;                                       /* Block Size for transfer */
    CanTp_SduIdType ActiveSduId;                    /* Index of the currently active connection */
    uint16 FcWait;                                  /* No of FC WT Frames sent */
    PduLengthType BlockCfsRemaining;                /* Total no of CF before waiting/sending another FC */
    PduLengthType SduLengthRemaining;               /* Total no of CF required to be transferred */
    PduLengthType SduLength;                        /* Total Transfer Length during Transfer (Rx/Tx) */
    CanTp_TickType InitialTicks;                    /* Timestamp of Free Running Timer during events */
    CanTp_TickType STminTicks;                      /* STmin for this channel */
}CanTp_ChannelType;

typedef CanTp_ChannelType *CanTp_ChannelPtrType;
typedef void (*CanTp_PduRConfirmationApiType)(PduIdType id, Std_ReturnType result);
typedef void (*CanTp_SchMTriggerApiType)(void);
typedef Std_ReturnType (*CanTp_CanIfTransmitApiType)(PduIdType TxPduId, const PduInfoType* PduInfoPtr);

/***********************************************************************************************************************
 *    Module Specific External data
***********************************************************************************************************************/

#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"
extern CanTp_ChannelType CanTp_Channel[CANTP_MAX_CHANNEL_SIZE];
extern CanTp_ChannelIdType CanTp_TxConfirmationChannel[CANTP_MAX_TX_NPDU_SIZE];
#if(CANTP_TX_BURST_MODE == CANTP_ON)
extern CanTp_QType CanTp_BurstQ;
#endif
#if(CANTP_CHANGE_PARAMETER_API == STD_ON)
extern CanTp_ParamPairType CanTp_ParamPair[CANTP_MAX_RX_CONNECTION_SIZE];        /* Parameter pair is STMin and BS */
#endif
#if(CANTP_CYCLE_COUNTER == CANTP_ON)
extern volatile CanTp_TickType CanTp_MainFunctionTicks;
#endif
extern const CanTp_ConfigType *CanTp_CfgPtr;
#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"
extern uint8 CanTp_SubState[CANTP_MAX_CHANNEL_SIZE];
#define CANTP_STOP_SEC_VAR_CLEARED_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "CanTp_MemMap.h"
extern const uint8 CanTp_State[CANTP_NUMBER_OF_SUBSTATES];
extern const uint8 CanTp_AddressSize[CANTP_ADDRESS_ARRAY_SIZE]; /* [0->STANDARD][1->EXTENDED][2->MIXED] */
extern const uint8 CanTp_PciFrameType[CANTP_PCI_ARRAY_SIZE];
extern const uint8 CanTp_PciSize[CANTP_PCI_ARRAY_SIZE];
#if(CANTP_CANFD_SUPPORT == CANTP_ON)
extern const uint8 CanTp_CanDlTable[CANTP_CANDL_ARRAY_SIZE];
#endif
#define CANTP_STOP_SEC_CONST_8
#include "CanTp_MemMap.h"

#define CANTP_START_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"
extern const CanTp_ProcessFrameType CanTp_ProcessFrame[CANTP_NUMBER_OF_FRAME_TYPES];
extern const CanTp_CreateFrameType CanTp_CreateFrame[CANTP_NUMBER_OF_FRAME_TYPES];
extern const CanTp_StateFuncType CanTp_StateFunctions[CANTP_NUMBER_OF_SUBSTATES];
extern const CanTp_PduRConfirmationApiType  CanTp_PduRConfirmationApis[CANTP_NUMBER_OF_PDUR_CONFIRMATION_TYPES];
#if((CANTP_SCHM_SUPPORT == CANTP_ON) && (CANTP_TX_BURST_MODE == CANTP_ON))
extern const CanTp_SchMTriggerApiType  CanTp_SchMTriggerApis[CANTP_NUMBER_OF_TRIGGER_POINTS];
#endif
#define CANTP_STOP_SEC_CONST_UNSPECIFIED
#include "CanTp_MemMap.h"

/***********************************************************************************************************************
 *    Module Specific External(private) functions
***********************************************************************************************************************/

#define CANTP_START_SEC_CODE
#include "CanTp_MemMap.h"

#if(CANTP_TX_BURST_MODE == CANTP_ON)
extern void CanTp_Prv_BurstMainFunction(CanTp_ChannelIdType ChannelId, uint8 TriggerPoint);
#endif

#define CANTP_STOP_SEC_CODE
#include "CanTp_MemMap.h"

/***********************************************************************************************************************
 *    Module Specific Inline functions
***********************************************************************************************************************/

#if(CANTP_CYCLE_COUNTER == CANTP_ON)
/***********************************************************************************************************************
 Function name    : CanTp_GetElapsedValue
 Syntax           : CanTp_GetElapsedValue(&Value, &ElapsedValue)
 Description      : Library function to emulate GetElapsedValue Api of Os.
 Parameter        : CanTp_TickType*, CanTp_TickType*
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_GetElapsedValue(CanTp_TickType *Value, CanTp_TickType *ElapsedValue)
{
    CanTp_TickType ValueIn = *Value;

    *Value = CanTp_MainFunctionTicks;

    *ElapsedValue = *Value - ValueIn;  /* As both are positive, wrap-around case will be taken care automatically. */

}
#endif

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetBit
 Syntax           : CanTp_Prv_GetBit(Value, Mask)
 Description      : Library function check whether particular Value bit pattern is same as to Mask.
 Parameter        : uint8, uint8
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE boolean CanTp_Prv_GetBit(uint8 Value, uint8 Mask)
{
    return ((Value & Mask) == Mask) ? TRUE : FALSE;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_ArrayInit
 Syntax           : CanTp_Prv_ArrayInit(&Array[0], Length, Item)
 Description      : Library function to initilize array.
 Parameter        : uint8*, uint32, uint8
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_ArrayInit(uint8 *ArrayPtr, uint32 Length, uint8 Item)
{
    uint32 i;

    for(i = 0; i < Length; i++)
    {
        ArrayPtr[i] = Item;
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_IsNoDevError
 Syntax           : CanTp_Prv_IsNoDevError(id, TotalIds, ApiId, CanTpEInvalidId)
 Description      : Library function to check InitState and Invalid Id passed in CanTp Api by CanIf/PduR.
 Parameter        : uint32, uint32, uint8, uint8
 Return value     : boolean
***********************************************************************************************************************/
LOCAL_INLINE boolean CanTp_Prv_IsNoDevError(uint32 id, uint8 ApiId, uint8 CanTpEInvalidId)
{
    uint8 ErrorId;
    uint32 TotalIds = 0;
    boolean Status = TRUE;

    if(CanTp_MainState != CANTP_ON)
    {   /* TRACE[SWS_CanTp_00031] */
        ErrorId = CANTP_E_UNINIT;
    }
    else
    {
        switch(ApiId)
        {
            case CANTP_CHANGEPARAMETER:
			case CANTP_READPARAMETER:
            case CANTP_CANCELRECEIVE:
                TotalIds = CanTp_CfgPtr->NumberOfRxSdus;
                break;
            case CANTP_TRANSMIT:
            case CANTP_CANCELTRANSMIT:
                TotalIds = CanTp_CfgPtr->NumberOfTxSdus; /* TRACE[SWS_CanTp_00254] */
                break;
			case CANTP_TXCONFIRMATION:
			case CANTP_TRIGGERTRANSMIT:
                TotalIds = CanTp_CfgPtr->NumberOfTxPdus;
				break;
			case CANTP_RXINDICATION:
                TotalIds = CanTp_CfgPtr->NumberOfRxPdus;
				break;
            default:    /* Wrong API ID */
                break;
        }

        if(id >= TotalIds)
        {
            ErrorId = CanTpEInvalidId;
        }
        else
        {
            ErrorId = CANTP_NO_ERROR;
        }
    }

    if(ErrorId != CANTP_NO_ERROR)
    {
        CanTp_Prv_ReportError(ApiId, ErrorId);
        Status = FALSE;
    }

    return Status;
}

#if(CANTP_CHANGE_PARAMETER_API == STD_ON)
/***********************************************************************************************************************
 Function name    : CanTp_Prv_IsChangeParameterOk
 Syntax           : CanTp_Prv_IsChangeParameterOk(parameter, value)
 Description      : Function to do parameter check in CanTp_ChangeParameter Api.
 Parameter        : TPParameterType, uint16
 Return value     : boolean
***********************************************************************************************************************/
LOCAL_INLINE boolean CanTp_Prv_IsChangeParameterOk(TPParameterType parameter, uint16 value)
{
    uint8 ErrorId;
    boolean Status = TRUE;

    if((parameter != TP_BS) && (parameter != TP_STMIN))
    {
        ErrorId = CANTP_E_PARAM_ID;
    } /* MILLISEC_MAX_RANGE=0x7F , MICROSEC_MIN_RANGE = F1, MICROSEC_MAX_RANGE = F9 */
    else if((parameter == TP_STMIN) && (!(( value <= CANTP_MILLISEC_MAX_RANGE) || ((value >= CANTP_MICROSEC_MIN_RANGE)
            && ( value <= CANTP_MICROSEC_MAX_RANGE)))))
    {
        ErrorId = CANTP_E_PARAM_CONFIG;
    }
    else if((parameter == TP_BS) && (value > CANTP_MAX_BS_VALUE))  /*MAX_BS_VALUE = 0xFF*/
    {
        ErrorId = CANTP_E_PARAM_CONFIG;
    }
    else
    {
        ErrorId = CANTP_NO_ERROR;
    }

    if(ErrorId != CANTP_NO_ERROR)
    {
        CanTp_Prv_ReportRunTimeError(CANTP_CHANGEPARAMETER, ErrorId); /* TRACE[SWS_CanTp_00305] */
        Status = FALSE;
    }

    return Status;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_RxParamInit
 Syntax           : CanTp_Prv_RxParamInit()
 Description      : Initialize STMin and BS for all the RX connections from configuration.
 Parameter        : None
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_RxParamInit(void)
{
    CanTp_SduIdType SduId;

    for(SduId = 0; SduId < CanTp_CfgPtr->NumberOfRxSdus; SduId++)
    {
        CanTp_ParamPair[SduId].Param[0] = CanTp_Prv_GetRxCfgParam(SduId, 0);
        CanTp_ParamPair[SduId].Param[1] = CanTp_Prv_GetRxCfgParam(SduId, 1);
    }
}
#endif

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetTxBlockCfs
 Syntax           : CanTp_Prv_GetTxBlockCfs(ChannelId)
 Description      : Initialize Total number of Consecutive Frames in a Block for Tx Connection.
 Parameter        : CanTp_ChannelIdType
 Return value     : PduLengthType
***********************************************************************************************************************/
LOCAL_INLINE PduLengthType CanTp_Prv_GetTxBlockCfs(CanTp_ChannelIdType ChannelId)
{
    uint8 PayLoadLength;
	const CanTp_TxSduType *Connection = CanTp_CfgPtr->TxSdu + CanTp_Channel[ChannelId].ActiveSduId;
    uint8 TX_DL = CanTp_Prv_GetTxDl(Connection);
    uint8 AddressSize = CanTp_AddressSize[Connection->AddressFormatId];
    PduLengthType SduLength = CanTp_Channel[ChannelId].SduLengthRemaining;

    PayLoadLength = TX_DL - CANTP_CF_PCISIZE - AddressSize;
    return ((SduLength % PayLoadLength) == 0) ? (SduLength / PayLoadLength) : ((SduLength / PayLoadLength) + 1);
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetRxBlockCfs
 Syntax           : CanTp_Prv_GetRxBlockCfs(ChannelId)
 Description      : Initialize Total number of Consecutive Frames in a Block for Rx Connection.
 Parameter        : CanTp_ChannelIdType
 Return value     : PduLengthType
***********************************************************************************************************************/
LOCAL_INLINE PduLengthType CanTp_Prv_GetRxBlockCfs(CanTp_ChannelIdType ChannelId)
{
    uint8 PayLoadLength;
	const CanTp_RxSduType *Connection = CanTp_CfgPtr->RxSdu + CanTp_Channel[ChannelId].ActiveSduId;
    uint8 RX_DL = CanTp_Prv_GetRxDl(ChannelId);
    uint8 AddressSize = CanTp_AddressSize[Connection->AddressFormatId];
    PduLengthType SduLength = CanTp_Channel[ChannelId].SduLengthRemaining;

    PayLoadLength = RX_DL - CANTP_CF_PCISIZE - AddressSize;
    return ((SduLength % PayLoadLength) == 0) ? (SduLength / PayLoadLength) : ((SduLength / PayLoadLength) + 1);
}

#if(CANTP_TX_BURST_MODE == CANTP_ON)
/***********************************************************************************************************************
 Function name    : CanTp_Prv_QInit
 Syntax           : CanTp_Prv_QInit()
 Description      : Initialize Burst Queue by making its Head and Tail equal.
 Parameter        : None
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_QInit(void)
{
    CanTp_BurstQ.Tail_u8 = 0;
    CanTp_BurstQ.Head_u8 = 0;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_PutInQ
 Syntax           : CanTp_Prv_PutInQ(ChannelId)
 Description      : This function puts in queue the ChannelId later to be retrieved.
 Parameter        : CanTp_ChannelIdType
 Return value     : Std_ReturnType
***********************************************************************************************************************/
LOCAL_INLINE Std_ReturnType CanTp_Prv_PutInQ(CanTp_ChannelIdType ChannelId)
{
    Std_ReturnType Status = E_NOT_OK;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if((CanTp_BurstQ.Tail_u8 - CanTp_BurstQ.Head_u8) != CANTP_BURST_QUEUE_SIZE) /* only put into Q if it is not full */
    {
        Status = E_OK;
        CanTp_BurstQ.Tail_u8++;
        CanTp_BurstQ.Queue[CanTp_BurstQ.Tail_u8 % CANTP_BURST_QUEUE_SIZE] = ChannelId;
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();

    return Status;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetFromQ
 Syntax           : CanTp_Prv_GetFromQ(ChannelId)
 Description      : This function gets the ChannelId from queue which was entered by CanTp_Prv_PutInQ.
 Parameter        : CanTp_ChannelIdType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
LOCAL_INLINE Std_ReturnType CanTp_Prv_GetFromQ(CanTp_ChannelIdType *ChannelId)
{
    Std_ReturnType Status = E_NOT_OK;

    SchM_Enter_CanTp_EXCLUSIVE_AREA();

    if((CanTp_BurstQ.Tail_u8 - CanTp_BurstQ.Head_u8) != 0) /* only take from Q if it is not empty */
    {
        Status = E_OK;
        CanTp_BurstQ.Head_u8++;
        *ChannelId = CanTp_BurstQ.Queue[CanTp_BurstQ.Head_u8 % CANTP_BURST_QUEUE_SIZE];
    }

    SchM_Exit_CanTp_EXCLUSIVE_AREA();

    return Status;
}
#endif

/***********************************************************************************************************************
 Function name    : CanTp_Prv_TxPciInit
 Syntax           : CanTp_Prv_TxPciInit(PciId, CanTpTxSduId, CanTpTxInfoPtr)
 Description      : This function initializes the Protocol Control Information type. To be called in CanTp_Transmit Api.
 Parameter        : uint8*, PduIdType, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_TxPciInit(uint8 *PciId, PduIdType CanTpTxSduId, const PduInfoType *CanTpTxInfoPtr)
{
    const CanTp_TxSduType *Connection = CanTp_CfgPtr->TxSdu + CanTpTxSduId;
    uint8 AddressLength;
    #if(CANTP_CANFD_SUPPORT == CANTP_ON)
    uint8 TX_DL = CanTp_Prv_GetTxDl(Connection);
    #endif

    AddressLength = CanTp_AddressSize[Connection->AddressFormatId];

    if((CanTpTxInfoPtr->SduLength + AddressLength + 1u) <= CANTP_DEFAULT_CAN_DL)
    {
        *PciId = CANTP_NPCI_SFCAN;
    }
    #if(CANTP_CANFD_SUPPORT == CANTP_ON)
    else if((TX_DL > CANTP_DEFAULT_CAN_DL) && ((CanTpTxInfoPtr->SduLength + AddressLength + 2u) <= TX_DL))
    {
        *PciId = CANTP_NPCI_SFCANFD;
    }
    else if((TX_DL > CANTP_DEFAULT_CAN_DL) && (CanTpTxInfoPtr->SduLength > CANTP_MAXFFDL))
    {
        *PciId = CANTP_NPCI_FFCANFD;
    }
    #endif
    else
    {
        *PciId = CANTP_NPCI_FFCAN;
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_CanIfTransmit
 Syntax           : CanTp_Prv_CanIfTransmit(&Context, &CanIfTxInfo)
 Description      : This is a wrapper function to CanIf_Transmit. It also abstracts negative reporting to PduR/DET and
                    provides internal stack buffer in case Trigger Transmit feature is disabled.
 Parameter        : const CanTp_TxContextType*, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_CanIfTransmit(const CanTp_TxContextType *Context, const PduInfoType *CanIfTxInfoPtr)
{
    PduInfoType CanIfTxInfo;
    #if(CANTP_TRIGGER_TRANSMIT_API != CANTP_ON)
    uint8 SduBuffer[CANTP_MAX_NPDU_LENGTH];
    #endif

    CanIfTxInfo.SduLength = CanIfTxInfoPtr->SduLength;
    CanIfTxInfo.SduDataPtr = CanIfTxInfoPtr->SduDataPtr;

    #if(CANTP_TRIGGER_TRANSMIT_API != CANTP_ON)
    CanIfTxInfo.SduDataPtr = SduBuffer;
    if(CanTp_Prv_CreateFrame(Context->ChannelId, &CanIfTxInfo) == E_OK)
    #endif
    {
        CanTp_TxConfirmationChannel[Context->TxConfirmationId] = Context->ChannelId; /* TRACE[SWS_CanTp_00248] */
        if(CanIf_Transmit(Context->PduId, &CanIfTxInfo) != E_OK)
        {   /*TRACE[SWS_CanTp_00342][SWS_CanTp_00343]CanTp shall terminate connection if E_NOT_OK */
            CanTp_Prv_PduRConfirmation(Context->PduRApiId, Context->PduRPduHandleId, E_NOT_OK);
            CanTp_Prv_ReportRunTimeError(CANTP_MAINFUNCTION, CANTP_E_COM);
            CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
            CanTp_TxConfirmationChannel[Context->TxConfirmationId] = CANTP_INVALID_CHANNEL;
        }
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_FcTransmit
 Syntax           : CanTp_Prv_FcTransmit(&Context, &CanIfTxInfo, IsFcTransmitReady, Value)
 Description      : This is a wrapper function to FC Transmission. It abstracts the case of FC deactivation by moving
                    state to next level.
 Parameter        : const CanTp_TxContextType*, const PduInfoType*, boolean, CanTp_TickType
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_FcTransmit(const CanTp_TxContextType *Context, const PduInfoType* CanIfTxInfoPtr,
                                       boolean IsFcTransmitReady, CanTp_TickType Value)
{
    if(IsFcTransmitReady && (CanTp_SubState[Context->ChannelId] == CANTP_RX_SEND_FC))
    {   /* TRACE[SWS_CanTp_00341]If N_Br timer expires then reload the N_Br timer. */
        CanTp_Channel[Context->ChannelId].InitialTicks = Value;
        CanTp_Channel[Context->ChannelId].PciId = CANTP_NPCI_FC;
        CanTp_SubState[Context->ChannelId] = CANTP_RX_WAIT_FOR_FCTRANSMIT_CONFIRMATION;

        #if(CANTP_FC_DISABLE_SUPPORT == CANTP_ON)
        if(CanTp_Prv_GetBit(CanTp_Prv_GetRxActiveBits(Context->ChannelId), CANTP_FC_DISABLED))
        {
            if((CanTp_Channel[Context->ChannelId].FlowStatus != CANTP_FC_OVERFLOW) &&
               (CanTp_Channel[Context->ChannelId].SduLengthRemaining <= Context->RemBufSize))
            {
                CanTp_Channel[Context->ChannelId].BlockCfsRemaining = CanTp_Prv_GetRxBlockCfs(Context->ChannelId);
                CanTp_Channel[Context->ChannelId].STminTicks = CANTP_DEFAULT_STMIN_TICKS;
                CanTp_SubState[Context->ChannelId] = CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME;
            }
            else
            {
                CanTp_Prv_PduRConfirmation(Context->PduRApiId, Context->PduRPduHandleId, E_NOT_OK);
                CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
            }
        }
        else
        #endif
        {
            CanTp_Prv_CanIfTransmit(Context, CanIfTxInfoPtr);
        }
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetFcActiveChannel
 Syntax           : CanTp_Prv_GetFcActiveChannel(&Context)
 Description      : This function sets the context by extracting the relavant Channel attribute for RxConnection.
 Parameter        : CanTp_RxContextType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
LOCAL_INLINE Std_ReturnType CanTp_Prv_GetFcActiveChannel(CanTp_RxContextType *Context)
{
    Std_ReturnType Status = E_NOT_OK;
    const CanTp_TxSduType *TxConnection;

    if(Context->SduId < CanTp_CfgPtr->NumberOfTxSdus)
    {
        TxConnection = CanTp_CfgPtr->TxSdu + Context->SduId;

        if(CanTp_SubState[TxConnection->ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME)
        {  /* Context->ChannelId is to correspond to the intended Channel */
            Context->ChannelId = TxConnection->ChannelId;
            Status = E_OK;
        }
    }

    #if(CANTP_LEGACY_SHARED_FC_SUPPORT == STD_ON)
    if(Status == E_NOT_OK)
    {  /* This is for UDS-OBD shared FC case */
        uint8 i;
        CanTp_ChannelIdType ChannelId;
        CanTp_SduIdType SduId;
        const CanTp_SharedFcType *SharedFc = CanTp_CfgPtr->SharedFc;

        for(i = 0; i < CanTp_CfgPtr->NumberOfSharedFc; i++)
        {
            if((SharedFc[i].RxFcPduId == Context->PduId) && (SharedFc[i].TxSduId != Context->SduId))
            {
                ChannelId = CanTp_Prv_GetTxChannelId(SharedFc[i].TxSduId);
                /* Channel objects access outside lock is certified in State check inside CanTp_Prv_ProcessFrame() */
                SduId = CanTp_Channel[ChannelId].ActiveSduId;
                if((CanTp_SubState[ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME) && (SharedFc[i].TxSduId == SduId))
                { /* Context->ChannelId is to correspond to the intended Channel */
                    Context->ChannelId = ChannelId;
                    Context->SduId = SduId;
                    Status = E_OK;
                    break;
                }
            }
        }

    }
    #endif

    return Status;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetRxContext
 Syntax           : CanTp_Prv_GetRxContext(&Context, &PduInfo)
 Description      : This function sets the context by extracting the relavant attributes for RxConnection.
 Parameter        : CanTp_RxContextType*, const PduInfoType*
 Return value     : uint8
***********************************************************************************************************************/
LOCAL_INLINE uint8 CanTp_Prv_GetRxContext(CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    uint8 ErrorId = CANTP_E_PARAM_CONFIG;
    CanTp_SduIdType TxSduId;
    CanTp_SduIdType RxSduId;
    uint8 FrameType;
    uint8 *SduDataPtr;
	const CanTp_TxSduType *TxConnection;
	const CanTp_RxSduType *RxConnection;
    const CanTp_RxPduType *RxPdu = CanTp_CfgPtr->RxPdu + Context->PduId;

    if(PduInfoPtr->SduDataPtr == NULL_PTR)
    {
        ErrorId = CANTP_E_PARAM_POINTER;
    }
    else
    {
        SduDataPtr = PduInfoPtr->SduDataPtr;
        Context->Address = 0;
        RxSduId = RxPdu->RxSduId;
        TxSduId = RxPdu->TxSduId;

        if(RxPdu->GetSduPair != NULL_PTR)
        {  /* Check if Address Format is EXTENDED. if so then FrameType is not at 0th byte */
            Context->Address = *SduDataPtr;
            SduDataPtr++;
            RxPdu->GetSduPair(&TxSduId, &RxSduId, Context->Address); /* TRACE[SWS_CanTp_00284][SWS_CanTp_00095] */
        }

        FrameType = *SduDataPtr >> CANTP_FRAMETYPE_OFFSET;

        if(FrameType < CANTP_NUMBER_OF_FRAME_TYPES)
        {
            Context->FrameType = FrameType;

            if(FrameType == CANTP_FLOWCONTROL_FRAME)
            {
                Context->SduId = TxSduId;
                if(CanTp_Prv_GetFcActiveChannel(Context) == E_OK)
                {
                    TxConnection = CanTp_CfgPtr->TxSdu + Context->SduId;
                    Context->PduRPduHandleId = TxConnection->PduRPduHandleId;
                    Context->AddressSize = CanTp_AddressSize[TxConnection->AddressFormatId];
                    Context->IsPaddingOn = CanTp_Prv_GetBit(TxConnection->BitFields, CANTP_PADDINGON);
                    ErrorId = CANTP_NO_ERROR;
                }
            }
            else
            {
                Context->SduId = RxSduId;
                if(Context->SduId < CanTp_CfgPtr->NumberOfRxSdus)
                {
                    RxConnection = CanTp_CfgPtr->RxSdu + RxSduId;
                    Context->ChannelId = RxConnection->ChannelId;
                    Context->PduRPduHandleId = RxConnection->PduRPduHandleId;
                    Context->AddressSize = CanTp_AddressSize[RxConnection->AddressFormatId];
                    Context->IsPaddingOn = CanTp_Prv_GetBit(RxConnection->BitFields, CANTP_PADDINGON);
                    Context->IsFdEnabled = CanTp_Prv_GetBit(RxConnection->BitFields, CANTP_FD_ENABLED);
                    Context->IsFunctional = CanTp_Prv_GetBit(RxConnection->BitFields, CANTP_FUNCTIONAL);
                    ErrorId = ((Context->IsFunctional) && (FrameType != CANTP_SINGLE_FRAME)) ?
                            CANTP_E_INVALID_TATYPE : CANTP_NO_ERROR; /* TRACE[SWS_CanTp_00093] */
                }
            }
        }
    }

    return ErrorId;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_RxSduLengthCheck
 Syntax           : CanTp_Prv_RxSduLengthCheck(&Context, &PduInfo)
 Description      : Function to process SduLength check as per ISO_15765-2_2016-04.
                    Figure 9 - State flow - Verifying received CAN frames.
 Parameter        : const CanTp_RxContextType*, const PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
LOCAL_INLINE Std_ReturnType CanTp_Prv_RxSduLengthCheck(CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    uint8 CAN_DL = CANTP_INVALID_DL;
    uint8 PciLowerNibble;
    uint8 *Data;
    uint8 DataOffset = 0;
    uint8 SF_DL = 0;                     /* Will be used only in case of SF */
    uint32 FF_DL = 0;                    /* Will be used only in case of FF */
    PduLengthType FF_DLmin;
    PduLengthType FfDlValue12bit;
	uint8 MaxCfSduLength;
	PduLengthType SduLengthRemaining;
	uint8 RX_DL;

	Data = PduInfoPtr->SduDataPtr + Context->AddressSize;
	PciLowerNibble = Data[0] & CANTP_LOWERNIBBLE_MASK;

	switch(Context->FrameType)
	{
		case CANTP_SINGLE_FRAME:
			if(PduInfoPtr->SduLength <= CANTP_DEFAULT_CAN_DL)
			{
				DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_SFCAN];
				SF_DL = PciLowerNibble;

				if((PciLowerNibble != 0u) && ((PciLowerNibble <= (CANTP_DEFAULT_CAN_DL - DataOffset))))
				{
					CAN_DL = ((Context->IsPaddingOn)) ? CANTP_DEFAULT_CAN_DL : (DataOffset + (uint8)PciLowerNibble);
				}
			}
			else
			{
                #if(CANTP_CANFD_SUPPORT == CANTP_ON)
				DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_SFCANFD];
				SF_DL = Data[1];

				if((PciLowerNibble == 0u) &&
				   (SF_DL > (7u - Context->AddressSize)) &&
				   (SF_DL <=  (PduInfoPtr->SduLength - DataOffset)) &&
				   ((Context->AddressSize + 2u + SF_DL) <= CANTP_MAX_NPDU_LENGTH))
				{   /* TRACE[SWS_CanTp_00344] */
					CAN_DL = ((Context->IsPaddingOn)) ? CanTp_Prv_GetCanDl(DataOffset + SF_DL) : (DataOffset + SF_DL);
				}
                #endif
			}
			break;

		case CANTP_FIRST_FRAME:/* To satisfy "Table 14-FF_DLmin" of ISO_15765-2 */
			CAN_DL = (uint8)(PduInfoPtr->SduLength);
			RX_DL = CanTp_Prv_IsRxDlInValid(CAN_DL) ? CANTP_INVALID_DL : CAN_DL; /* TRACE[SWS_CanTp_00350] */
			/* All 4 cases of "Table 14-FF_DLmin" of ISO_15765-2"Table 14-FF_DLmin" of ISO_15765-2  */
			FF_DLmin = RX_DL - Context->AddressSize - ((CAN_DL > CANTP_DEFAULT_CAN_DL) ? 1u : 0u);

			FfDlValue12bit = ((Data[0] & CANTP_LOWERNIBBLE_MASK) * 0x100u) + Data[1];

            if(FfDlValue12bit == 0)
            {
                FF_DL = (Data[2] * 0x1000000u) + (Data[3] * 0x10000u) + (Data[4] * 0x100u) + Data[5];
                DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_FFCANFD];
                RX_DL = ((FF_DL > CANTP_MAXFDFFDL) || (FF_DL <= CANTP_MAXFFDL)) ? CANTP_INVALID_DL : RX_DL;
            }
            else
            {
                FF_DL = FfDlValue12bit;
                DataOffset = Context->AddressSize + CanTp_PciSize[CANTP_NPCI_FFCAN];
            }

			/* To satisfy "Table 14-FF_DLmin" of ISO_15765-2 and Physical Addressing need for Segmented Transfer */
			RX_DL = ((Context->IsFunctional) || (FF_DL < FF_DLmin)) ? CANTP_INVALID_DL : RX_DL;
			CAN_DL = RX_DL;
			break;

		case CANTP_CONSECUTIVE_FRAME:
			SduLengthRemaining = CanTp_Channel[Context->ChannelId].SduLengthRemaining;
			Context->SN = PciLowerNibble;
			RX_DL = CanTp_Prv_GetRxDl(Context->ChannelId);
			DataOffset = Context->AddressSize + CANTP_CF_PCISIZE;
			MaxCfSduLength = RX_DL - DataOffset;
			CAN_DL = (SduLengthRemaining < MaxCfSduLength) ? (uint8)(SduLengthRemaining + DataOffset) : RX_DL;
			CAN_DL = (Context->IsPaddingOn) ? CanTp_Prv_GetCanDl(CAN_DL) : CAN_DL;
			break;

		case CANTP_FLOWCONTROL_FRAME:
			Context->FlowStatus = PciLowerNibble;
            DataOffset = Context->AddressSize + 1; /* Offset for STMin/BS or for CF Data in CanTp_Prv_SetTxBlockInfo */
			CAN_DL = (Context->IsPaddingOn) ? CANTP_DEFAULT_CAN_DL : (CANTP_FC_PCISIZE  + Context->AddressSize);
			break;

		default:    /* Wrong Frame Type */
			break;
	}

	Context->CAN_DL = CAN_DL;
	Context->DataOffset = DataOffset;
	Context->SduLength = (Context->FrameType == CANTP_SINGLE_FRAME) ? SF_DL : (PduLengthType)FF_DL;

	return CanTp_Cfg_DlcCheck(PduInfoPtr->SduLength, Context->CAN_DL);
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetConnectionAcceptance
 Syntax           : CanTp_Prv_GetConnectionAcceptance(&Context, &PduInfo)
 Description      : Function to process first or single frame reception acceptance criteria in RxIndication
                    from Can Interface.
 Parameter        : const CanTp_RxContextType*, const PduInfoType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
LOCAL_INLINE Std_ReturnType CanTp_Prv_GetConnectionAcceptance(const CanTp_RxContextType *Context,
                                                              const PduInfoType *PduInfoPtr)
{
    Std_ReturnType RetValue = E_NOT_OK;
    uint8 NewChannelState = CANTP_IDLE;
    uint8 OldChannelState = CanTp_Prv_GetState(Context->ChannelId);

    #if(CANTP_FD_CALLOUT_SUPPORT == STD_ON)/* indicate to application Flexible Data rate supported info */
    if((CanTp_FdCallOut(Context->PduId, PduInfoPtr, Context->IsFdEnabled)) == E_OK) /* FD supported ? */
    #else
    (void)PduInfoPtr;
    #endif
    {
        if(OldChannelState == CANTP_IDLE)
        {
            NewChannelState = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
        }
        else
        {
            if((OldChannelState == CANTP_RECEPTION)&&(CanTp_Channel[Context->ChannelId].ActiveSduId == Context->SduId))
            {   /* TRACE[SWS_CanTp_00124] Reject older and accept new one and free application buffer with E_NOT_OK  */
                NewChannelState = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
                CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, Context->PduRPduHandleId, E_NOT_OK);
            }/* TRACE[SWS_CanTp_00287][SWS_CanTp_00288] */
        }

        if(NewChannelState == CANTP_RX_RECEPTION_REQUEST_ACCEPTED)
        {
            CanTp_SubState[Context->ChannelId] = CANTP_RX_RECEPTION_REQUEST_ACCEPTED;
            RetValue = E_OK;
        }
    }

    return RetValue;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_SetTxBlockInfo
 Syntax           : CanTp_Prv_SetTxBlockInfo(&Context, &PduInfo)
 Description      : Function to initialize the block related parameters for the Tx connection Channel which is recieved
                    in FC Frame.
 Parameter        : const CanTp_RxContextType*, const PduInfoType*
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_SetTxBlockInfo(const CanTp_RxContextType *Context, const PduInfoType *PduInfoPtr)
{
    uint8 *SduDataPtr;
    CanTp_ChannelPtrType Channel = &CanTp_Channel[Context->ChannelId];
    PduLengthType BlockCfsRemaining;

    SduDataPtr = PduInfoPtr->SduDataPtr + Context->DataOffset;

    #if(CANTP_DYNAMIC_FC_SUPPORT != CANTP_ON)
    if(Channel->STminTicks == CANTP_INVALID_STMIN_TICKS)
    #endif
    { /* FC-CTS received set Block Size and STmin */

        Channel->BS = *SduDataPtr;
        SduDataPtr++;

        if(*SduDataPtr <= CANTP_MILLISEC_MAX_RANGE) /* Adapt the STmin received in the FC frame to local */
        {
            Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks(*SduDataPtr * 1000u);
        }
        else if((*SduDataPtr < CANTP_MICROSEC_MIN_RANGE) || (*SduDataPtr > CANTP_MICROSEC_MAX_RANGE))
        {
            Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks(127000u);
        }
        else
        {
            Channel->STminTicks = (CanTp_TickType)CanTp_Cfg_GetUsToTicks((*SduDataPtr & CANTP_LOWERNIBBLE_MASK) * 100u);
        }
    }

    BlockCfsRemaining = CanTp_Prv_GetTxBlockCfs(Context->ChannelId); /* Estimated total block size in terms of Cfs */

    if((Channel->BS == 0u) || (Channel->BS > BlockCfsRemaining))
    {   /* If Block size is zero or greater than remaining CFs, then no more FCs */
        Channel->BlockCfsRemaining = BlockCfsRemaining;
    }
    else
    {
        Channel->BlockCfsRemaining = (uint16)Channel->BS; /* Wait for FC until block size */
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_GetRxParam
 Syntax           : CanTp_Prv_GetRxParam(id, parameter)
 Description      : Function to return the STMin and/or BS type.
 Parameter        : CanTp_SduIdType, TPParameterType
 Return value     : uint8
***********************************************************************************************************************/
LOCAL_INLINE uint8 CanTp_Prv_GetRxParam(CanTp_SduIdType id, TPParameterType parameter)
{
    uint8 value;

    value = (parameter == TP_STMIN)? (0u) : (1u);

    #if(CANTP_CHANGE_PARAMETER_API != STD_ON)
    return CanTp_Prv_GetRxCfgParam(id, value);
    #else
    return CanTp_ParamPair[id].Param[value];
    #endif
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_SetRxBlockInfo
 Syntax           : CanTp_Prv_SetRxBlockInfo(ChannelId, RemBufSize)
 Description      : Function to initialize the block related parameters for the Rx connection Channel based on the
                    Buffer Availability in PduR and configuration.
 Parameter        : CanTp_ChannelIdType, const PduLengthType
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_SetRxBlockInfo(CanTp_ChannelIdType ChannelId, const PduLengthType RemBufSize)
{
    uint8 BSMax;
    PduLengthType BlockCfsRemaining;
	CanTp_ChannelPtrType Channel = &CanTp_Channel[ChannelId];
    uint8 BS = Channel->BS;
    const CanTp_RxSduType *Connection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;
    PduLengthType OneFramePayloadLength = CanTp_Prv_GetRxDl(ChannelId) -
                                          CanTp_AddressSize[Connection->AddressFormatId] - CANTP_CF_PCISIZE;

    /* This invalid value of STminTicks case is possible according to [SWS_CanTp_00082] */
    #if(CANTP_DYNAMIC_FC_SUPPORT != CANTP_ON)
    if(Channel->STminTicks == CANTP_INVALID_STMIN_TICKS) /* TRACE[SWS_CanTp_00067] */
    #endif
    {
        BSMax = CanTp_Prv_GetRxParam(Channel->ActiveSduId, TP_BS);

        if(RemBufSize >= Channel->SduLengthRemaining)
        {   /* Enough buffer to recieve all frames. */
            BS = BSMax;
        }
        else
        {   /* Enough buffer to recieve Block frames. */
            BS = (uint8)(RemBufSize/OneFramePayloadLength);
            BS = ((BSMax != 0u) && (BS > BSMax)) ? BSMax : BS;
        }
    }

    if(((BS == 0) && (RemBufSize < Channel->SduLengthRemaining)) ||
	   ((BS != 0) && (RemBufSize < (BS * OneFramePayloadLength)) && (RemBufSize < Channel->SduLengthRemaining)))
    {
        Channel->FlowStatus = CANTP_FC_WAIT;
    }
    else
    {
		BlockCfsRemaining = CanTp_Prv_GetRxBlockCfs(ChannelId);
        Channel->BlockCfsRemaining = (BS != 0u) ? BS : BlockCfsRemaining;
	    Channel->FlowStatus = CANTP_FC_CTS;
        #if(CANTP_DYNAMIC_FC_SUPPORT != CANTP_ON)
        Channel->STminTicks = 0;  /* BS locking for CANTP_DYNAMIC_FC_SUPPORT Disabled case  */
        #endif
    }

    Channel->BS = BS;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_FcTxConfirmation
 Syntax           : CanTp_Prv_FcTxConfirmation(ChannelId)
 Description      : Function to change channel state at confirmation recieved for FC in CanTp_TxConfirmation.
 Parameter        : PduIdType
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_FcTxConfirmation(CanTp_ChannelIdType ChannelId)
{
    const CanTp_ChannelType *Channel = CanTp_Channel + ChannelId;
    const CanTp_RxSduType *RxConnection = CanTp_CfgPtr->RxSdu + Channel->ActiveSduId;

    switch(Channel->FlowStatus)
    {
        case CANTP_FC_CTS:
            CanTp_SubState[ChannelId] = CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME;
            break;
        case CANTP_FC_WAIT:
            CanTp_SubState[ChannelId] = (Channel->SduLengthRemaining > 0) ? CANTP_RX_SEND_FC : CANTP_IDLE;
            break;
        case CANTP_FC_OVERFLOW:
            CanTp_Prv_PduRConfirmation(CANTP_RX_PDUR_CONFIRMATION, RxConnection->PduRPduHandleId, E_NOT_OK);
            CanTp_SubState[ChannelId] = CANTP_IDLE;
            break;
        default:    /* Wrong FlowStatus */
            break;
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_PrepareFcTransmit
 Syntax           : CanTp_Prv_PrepareFcTransmit(ChannelId)
 Description      : This function sets the context w.r.t. FC transmission for RxConnection of Active Channel.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_PrepareFcTransmit(CanTp_ChannelIdType ChannelId)
{
    if(CanTp_Channel[ChannelId].BlockCfsRemaining == 0)
    { /* TRACE[SWS_CanTp_00082][SWS_CanTp_00278] */
        CanTp_Channel[ChannelId].FcWait = 0;
        CanTp_Channel[ChannelId].FlowStatus = CANTP_FC_WAIT;
        CanTp_SubState[ChannelId] = CANTP_RX_SEND_FC;
    }
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_PrepareFcRecieve
 Syntax           : CanTp_Prv_PrepareFcRecieve(Channel)
 Description      : Function to advance the Channel to Next State from Flow control related State in case FC is
                    deactivated.
 Parameter        : CanTp_ChannelIdType
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_PrepareFcRecieve(CanTp_ChannelIdType ChannelId)
{
	#if(CANTP_FC_DISABLE_SUPPORT == CANTP_ON)
    if(CanTp_Prv_GetBit(CanTp_Prv_GetTxActiveBits(ChannelId), CANTP_FC_DISABLED))
    {
        CanTp_Channel[ChannelId].BlockCfsRemaining = CanTp_Prv_GetTxBlockCfs(ChannelId);
        CanTp_Channel[ChannelId].STminTicks = CANTP_DEFAULT_STMIN_TICKS;
        CanTp_SubState[ChannelId] = CANTP_TX_SEND_CONSECUTIVE_FRAME;
    }
    else
    #endif
    {
        CanTp_SubState[ChannelId] = CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME;
    }

	CanTp_Channel[ChannelId].PciId = CANTP_NPCI_FC;
}

/***********************************************************************************************************************
 Function name    : CanTp_Prv_LengthError
 Syntax           : CanTp_Prv_LengthError(&Context)
 Description      : Library function to abort connection in case dlc check failed.
 Parameter        : const CanTp_RxContextType*
 Return value     : None
***********************************************************************************************************************/
LOCAL_INLINE void CanTp_Prv_LengthError(const CanTp_RxContextType *Context)
{
    uint8 Api;

    Api = (Context->FrameType == CANTP_FLOWCONTROL_FRAME) ? CANTP_TX_PDUR_CONFIRMATION : CANTP_RX_PDUR_CONFIRMATION;
    SchM_Enter_CanTp_EXCLUSIVE_AREA();
    if((CanTp_SubState[Context->ChannelId] == CANTP_TX_WAIT_FOR_FLOWCONTROL_FRAME) ||
       (CanTp_SubState[Context->ChannelId] == CANTP_RX_WAIT_FOR_CONSECUTIVE_FRAME))
    {   /* TRACE[SWS_CanTp_00346][SWS_CanTp_00349] */
        CanTp_Prv_PduRConfirmation(Api, Context->PduRPduHandleId, E_NOT_OK);
        CanTp_SubState[Context->ChannelId] = CANTP_IDLE;
    }
    SchM_Exit_CanTp_EXCLUSIVE_AREA();

    if(Context->IsPaddingOn)
    {   /* TRACE[SWS_CanTp_00344][SWS_CanTp_00345] */
        CanTp_Prv_ReportError(CANTP_RXINDICATION, CANTP_E_PADDING);
    }
    else
    {  /* Implementation specific error just to indicate Length check failed. */
        CanTp_Prv_ReportRunTimeError(CANTP_RXINDICATION, CANTP_E_COM);
    }

}


#if((CANTP_DEV_ERROR_DETECT == CANTP_ON) && (CANTP_VARIANT == CANTP_POST_BUILD_SELECTABLE))
/***********************************************************************************************************************
 Function name    : CanTp_Prv_PbCfgCheck
 Syntax           : CanTp_Prv_PbCfgCheck(CfgPtr)
 Description      : Function to check PostBuild Configuration Pointer validity.
 Parameter        : const CanTp_ConfigType*
 Return value     : Std_ReturnType
***********************************************************************************************************************/
LOCAL_INLINE Std_ReturnType CanTp_Prv_PbCfgCheck(const CanTp_ConfigType *CfgPtr)
{
    Std_ReturnType retval = E_NOT_OK;
    uint8 ConfigId;

    for(ConfigId = 0; ConfigId < CANTP_NO_OF_CANTPCONFIGSETS; ConfigId++)
    {
        if(CanTp_CfgPtrs[ConfigId] == CfgPtr)
        {
            retval = E_OK;
            break;
        }
    }

    return retval;
}
#endif

#endif  /* CANTP_PRV_H */
