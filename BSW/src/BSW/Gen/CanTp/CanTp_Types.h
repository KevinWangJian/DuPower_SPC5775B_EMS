

#ifndef CANTP_TYPES_H
#define CANTP_TYPES_H

#include "Std_Types.h"
#if (!defined(STD_TYPES_AR_RELEASE_MAJOR_VERSION) || (STD_TYPES_AR_RELEASE_MAJOR_VERSION != 4))
//#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(STD_TYPES_AR_RELEASE_MINOR_VERSION) || (STD_TYPES_AR_RELEASE_MINOR_VERSION != 2))
//#error "AUTOSAR minor version undefined or mismatched"
#endif
#include "ComStack_Types.h"
#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif


typedef uint16 CanTp_TickType;
typedef uint8 CanTp_SduIdType;
typedef uint8 CanTp_ChannelIdType;
typedef void (*CanTp_GetSduPairType)(CanTp_SduIdType *TxSduId, CanTp_SduIdType *RxSduId, uint8 Address);



struct CanTp_RxPduStructType               /* Rx N-PDU to Connection Configuration Mapping Structure */
{
    const CanTp_SduIdType RxSduId;         /* RxSdu for combination of N-PDU and N-Ta */
    const CanTp_SduIdType TxSduId;         /* TxSdu for combination of N-PDU and N-Sa */
    const CanTp_GetSduPairType GetSduPair;
};

struct CanTp_TxSduStructType               /* TxConnection Configuration Structure */
{
    
    const uint8 BitFields;                 /* 4:IsTcDisabled|3:IsPadingOn|2:IsFunctional|1:IsFcDisabled|0:IsFdEnabled */
    const uint8 Address;                   /* Extended/Mixed Address to be used during transmission */
    const uint8 AddressFormatId;           /* Addressing Format Identifier */
    const uint8 TimeOutId;                 /* Timeout Index for this Connection in CanTp_TimeOut */
    const CanTp_ChannelIdType ChannelId;   /* Index of RAM Channel used by this connection */
    const PduIdType TxConfirmationId;      /* Transmit Confirmation Id for SF/FF/CF Frame */
    const PduIdType TxPduId;               /* Transmit N-PDU Id for this Connection */
    const PduIdType PduRPduHandleId;       /* Identifier to be used for PduR Api calls */
};

struct CanTp_RxSduStructType               /* RxConnection Configuration Structure */
{
    const uint8 BitFields;                 /* 3:IsPadingOn|2:IsFunctional|1:IsFcDisabled|0:IsFdEnabled */
    const uint8 Address;                   /* Extended/Mixed Address to be used during reception */
    const uint8 AddressFormatId;           /* Addressing Format Identifier */
    const uint8 TimeOutId;                 /* Timeout Index for this Connection in CanTp_TimeOut */
    const uint8 ParamId;                   /* Rx Conn. STmin/BS/FcWaitMax Index for this connection. */
    const CanTp_ChannelIdType ChannelId;   /* Index of RAM Channel used by this connection */
    const PduIdType TxConfirmationId;      /* Transmit Confirmation Id for FC Frame */
    const PduIdType TxPduId;               /* Transmit FC relevant N-PDU Id for this Connection */
    const PduIdType PduRPduHandleId;       /* Identifier to be used for PduR Api calls */
};
 
struct CanTp_TimeOutStructType             /* TimeOut Configuration Structure */
{
    const CanTp_TickType AsArTicks;
    const CanTp_TickType BsBrTicks;
    const CanTp_TickType CsCrTicks;
};

struct CanTp_ParamStructType               /* RxConnection Specific left overs Configuration Structure */
{
    const uint8 Param[2];                  /* Param[0] is for STMin and Param[1] is for BS */
    const uint16 FcWaitMax;
};

struct CanTp_ConfigStructType
{
    
    const CanTp_ChannelIdType NumberOfChannels;
    const CanTp_SduIdType NumberOfRxPdus;
    const CanTp_SduIdType NumberOfTxPdus;
    const CanTp_SduIdType NumberOfRxSdus;
    const CanTp_SduIdType NumberOfTxSdus;
    
    const struct CanTp_RxPduStructType *RxPdu;
    const struct CanTp_TxSduStructType *TxSdu;
    const struct CanTp_RxSduStructType *RxSdu;
    const struct CanTp_TimeOutStructType *TimeOut;
    const struct CanTp_ParamStructType *Param;
};

typedef struct CanTp_SduPairStructType CanTp_SduPairType;
typedef struct CanTp_RxPduStructType CanTp_RxPduType;
typedef struct CanTp_TxSduStructType CanTp_TxSduType;
typedef struct CanTp_RxSduStructType CanTp_RxSduType;
typedef struct CanTp_TimeOutStructType CanTp_TimeOutType;
typedef struct CanTp_ParamStructType CanTp_ParamType;
typedef struct CanTp_SharedFcStructType CanTp_SharedFcType;

#endif /* CANTP_TYPES_H */
