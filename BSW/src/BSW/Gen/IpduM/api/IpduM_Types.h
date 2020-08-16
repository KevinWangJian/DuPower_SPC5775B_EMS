
/**
 *********************************************************************
 * \moduledescription
 *
 *
 * \scope           [INTERN]
 *********************************************************************
 */
#ifndef IPDUM_TYPES_H
#define IPDUM_TYPES_H
/**
 * \defgroup IPDUM_TYPES_H    IPDUM - AUTOSAR interfaces to PduR and COM Module.
 * To use this interface include the header <b>IpduM_Types.h</b>
 */
/*
 *********************************************************************
 * Includes
 *********************************************************************
 */
#include "ComStack_Types.h"
#if (!defined(COMTYPE_AR_RELEASE_MAJOR_VERSION) || (COMTYPE_AR_RELEASE_MAJOR_VERSION != IPDUM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMTYPE_AR_RELEASE_MINOR_VERSION) || (COMTYPE_AR_RELEASE_MINOR_VERSION != IPDUM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */
#define IPDUM_PDUTYPE_STATIC        0
#define IPDUM_PDUTYPE_DYNAMIC       1

#define IPDUM_PROCESSING_DEFERRED   0
#define IPDUM_PROCESSING_IMMEDIATE  1

#define IPDUM_HEADERTYPE_SHORT_SIZE    4
#define IPDUM_HEADERTYPE_LONG_SIZE     8

#define IPDUM_FOUR_BYTES    4
/**
 * @ingroup IPDUM_TYPES_H
 *  This enum represents the Trigger type mode \n
 *
 * typedef enum { \n
 *   IPDUM_STATIC_PART_TRIGGER = 0,             Get Confirmation only for Static part    \n
 *   IPDUM_DYNAMIC_PART_TRIGGER,                Get Confirmation only for Dynamic part   \n
 *   IPDUM_STATIC_OR_DYNAMIC_PART_TRIGGER,      Get Both Confirmation, Static and Dynamic    \n
 *   IPDUM_NONE                                 No Confirmation \n
 * }IpduM_TriggType;
 */
typedef enum
{
    IPDUM_STATIC_PART_TRIGGER = 0,
    IPDUM_DYNAMIC_PART_TRIGGER,
    IPDUM_STATIC_OR_DYNAMIC_PART_TRIGGER,
    IPDUM_NONE

} IpduM_TriggType;

/**
 * @ingroup IPDUM_TYPES_H
 *  This enum represents the state \n
 *
 * typedef enum { \n
 *   IPDUM_TX_READY = 0,                Transmission is Ready    \n
 *   IPDUM_TX_REQUESTED                 Transmission Requested   \n
 * }IpduM_StateType;
 */
typedef enum
{
    IPDUM_TX_READY = 0,
    IPDUM_TX_REQUESTED

} IpduM_StateType;

/**
 * @ingroup IPDUM_TYPES_H
 *  This enum represents status of IpduM Module\n
 *
 * typedef enum { \n
 *   IPDUM_UNINIT,              IpduM Module Uninitialized   \n
 *   IPDUM_INIT                 IpduM Module Initialized  \n
 * }IpduM_StatusType;
 */
typedef enum
{
    IPDUM_UNINIT,
    IPDUM_INIT
}IpduM_StatusType;

/**
 * @ingroup IPDUM_TYPES_H
 * subparts of all parts - dynamic and static\n
 * This structure is used for getting the bitfield position from I-pdu to M-Pdu\n
 *
 * typedef struct \n
 *  { \n
 *      uint16  SegmentPos; 	Starting segment position both in source and destination            \n
 *      uint16  SegmentLen;   	Segment Length              \n
 *  } IpduM_SubPartType ;
 */
typedef struct
{
    uint16  SegmentPos;
    uint16  SegmentLen;

} IpduM_SubPartType;

/**
 * @ingroup IPDUM_TYPES_H
 * This structure represents Transmission Request type \n
 *
 * typedef struct \n
 *  { \n
 *      P2CONST(IpduM_SubPartType, TYPEDEF, IPDUM_APPL_CONST)   TxBaseSubPart; Pointer to Transmission subpart \n
 *      PduIdType           MPduId;     M-Pdu-Id                                                               \n
 *      uint8               NumOfSubParts; Total No. of subarts                                                \n
 *      uint8               IPduType; Type of I-Pdu                                                            \n
 *  } IpduM_TxRequestType ;
 */
typedef struct
{
    P2CONST(IpduM_SubPartType, TYPEDEF, IPDUM_APPL_CONST)   TxBaseSubPart;
    PduIdType           MPduId;
    uint8               NumOfSubParts;
    uint8               IPduType;
    boolean				ipduMJITUpdate;

} IpduM_TxRequestType;

/**
 * @ingroup IPDUM_TYPES_H
 * This structure represents Transmission M-Pdu type \n
 *
 * typedef struct \n
 *  { \n
 *      P2VAR(uint8, TYPEDEF, IPDUM_APPL_DATA)  MPduBuffPtr; Pointer to M-Pdu Buffer \n
 *      IpduM_TriggType TxTriggMode; Type of Trigger                                 \n
 *      uint32          TxConfirmTimeout; Confirmation Timeout                       \n
 *      PduLengthType   TxMPduLen;  Length of M-Pdu                                  \n
 *      boolean         byteOrder;  Specifies the ByteOrder for all IpduMSegments    \n
 *  } IpduM_TxMPduType ;
 */
typedef struct
{
    P2VAR(uint8, TYPEDEF, IPDUM_APPL_DATA)  MPduBuffPtr;
    IpduM_TriggType TxTriggMode;
    uint32          TxConfirmTimeout;
    PduIdType       InitialDynPduId;
    PduIdType       StaticPduId;
    PduIdType       TargetPduId;
    PduLengthType   TxMPduLen;
    boolean         byteOrder;

} IpduM_TxMPduType;

/**
 * @ingroup IPDUM_TYPES_H
 * This structure represents the Received I-Pdu Type \n
 *
 * typedef struct \n
 *  { \n
 *      P2CONST(IpduM_SubPartType, TYPEDEF, IPDUM_APPL_CONST)   RxBaseSubPart; Pointer to Received Subpart  \n
 *      P2VAR(uint8, TYPEDEF, IPDUM_APPL_DATA)  RxBuffPtr; Pointer to Rx Buffer                             \n
 *      PduLengthType       RxIPduLen;      Length of Received I-Pdu                                        \n
 *      PduIdType           RxUpHandleId;   Handle-Id                                                       \n
 *      uint16              NumOfSubParts;  Total no. of subparts                                           \n
 *      uint16              SelectorValue;  Selector Byte Value                                             \n

 *  } IpduM_RxUpPduType ;
 */
typedef struct
{
    P2CONST(IpduM_SubPartType, TYPEDEF, IPDUM_APPL_CONST)   RxBaseSubPart;
    P2VAR(uint8, TYPEDEF, IPDUM_APPL_DATA)  RxBuffPtr;
    PduLengthType       RxIPduLen;
    PduIdType           RxUpHandleId;
    uint16              NumOfSubParts;
    uint16              SelectorValue;  /* 0xFFFF=>invalid */


} IpduM_RxUpPduType;

/**
 * @ingroup IPDUM_TYPES_H
 * This structure represents the type of Received M-Pdu \n
 *
 * typedef struct \n
 *  { \n
 *      P2CONST(IpduM_RxUpPduType, TYPEDEF, IPDUM_APPL_CONST)   RxUpPduBaseAddr; \n
 *      PduLengthType   RxMPduLen;        Received M-Pdu Length                  \n
 *      PduIdType       TotalNumOfIPdus;  Number Of I-Pdu's                      \n
 *      uint16          SelectorByte;     Selector Byte Value                    \n
 *      uint8           SelectorMask;     Selector Byte for Masking              \n
 *      boolean         byteOrder;  Specifies the ByteOrder for all IpduMSegments    \n

 *  } IpduM_RxMPduType ;
 */
typedef struct
{
    P2CONST(IpduM_RxUpPduType, TYPEDEF, IPDUM_APPL_CONST)   RxUpPduBaseAddr;
    PduLengthType   RxMPduLen;                  /* RxMPduLen:= SduLen from PduRef in RxIndication container */
    PduIdType       TotalNumOfIPdus;
    uint16          SelectorByte;               /* gives the ByteIdx in the Rx data */
    uint8           SelectorMask;
    boolean         byteOrder;


} IpduM_RxMPduType;

/**
 * @ingroup IPDUM_TYPES_H
 *  This enum specifies which contained pdus to be extracted \n
 *
 * typedef enum { \n
 *   IPDUM_ACCEPT_ALL = 0,               \n Accept all contained pdus inside container\n
 *   IPDUM_ACCEPT_CONFIGURED             \n Accept only configured contained Pdus\n
 * }RxAcceptContainedPduType;
 */
typedef enum
{
    IPDUM_ACCEPT_ALL = 0,
    IPDUM_ACCEPT_CONFIGURED
} RxAcceptContainedPduType;

/*typedef struct
*{
*    RxAcceptContainedPduType       RxAcceptContainedPdu;    \n Enum to check the type RxContainedPdu
*    P2VAR( uint8, TYPEDEF, IPDUM_VAR )    BufferPtr;         \n pointer to Rx Buffer
*    PduLengthType RxContainerPduLen;        \n Length of Rx Container
*    uint8      InstancesInQueue;         \n Total Queue size configured
*    uint8      HeaderSize;        \n Header type either Large or Small
*    PduIdType  ContainerRxPduId;  \n Container Rx Handle ID
*    boolean    PduProcessing;     \n Flag to check the status of the Received Pdu
*}IpduM_RxContainerPduType ;
*/

typedef struct
{
    RxAcceptContainedPduType       RxAcceptContainedPdu;
    P2VAR( uint8, TYPEDEF, IPDUM_VAR )    BufferPtr;
    PduLengthType RxContainerPduLen;
    uint8      InstancesInQueue;
    uint8      HeaderSize;
    PduIdType  ContainerRxPduId;
    boolean    PduProcessing;
}IpduM_RxContainerPduType;

/*typedef struct
*{
*    uint32       PduHeaderId;         \n
*    PduIdType    TargetPduId;         \n
*    PduIdType    ContainerRxPduId;    \n
*}IpduM_RxContainedPduType;
*/

typedef struct
{
    uint32       PduHeaderId;
    PduIdType    TargetPduId;
    PduIdType    ContainerRxPduId;
}IpduM_RxContainedPduType;

/**
 * @ingroup IPDUM_TYPES_H
 *  This enum specifies which type of trigger mode does Container PDU holds \n
 *
 * typedef enum { \n
 *   IPDUM_DIRECT = 0,                Transmits the Container Pdu when it is triggered  \n
 *   IPDUM_TRIGGERTRANSMIT            Tranmsits the Container Pdu only if trigger transmit is called\n
 * }TxTriggerModeType;
 */
typedef enum
{
    IPDUM_DIRECT = 0,
    IPDUM_TRIGGERTRANSMIT
} ContainerTxTriggerModeType;

/*
*typedef struct
*{
*    ContainerTxTriggerModeType    ContainerTxTriggerMode;    \n Used to identify either direct or TT
*    P2VAR( uint8, TYPEDEF, IPDUM_VAR )    BufferPtr;    \n  Pointer to Tx Buffer
*    PduLengthType TxContainerPduLen;    \n Length of Tx Container Pdu.
*    uint32     TxThresholdSize;    \n Holds the threshold size of the container Pdu
*    PduIdType     TargetPduId;        \n Holds the PduR_IpduMTransmit Target PduId
*    uint16     TxSendTimeOut;      \n Timeout for triggering the transmission
*    uint16     TxConfConstTicks;    \n Timeout for Tx Confirmation
*    uint8      InstancesInQueue;    \n Holds the Configured Queue Size
*    uint8      HeaderSize;    \n Holds the header type either small or large
*    boolean    TxFirstContainedpduTrigger;   \n  Holds the IpduMContainerTxFirstContainedPduTrigger value
*}IpduM_TxContainerPduType;   \n
*/

typedef struct
{
    ContainerTxTriggerModeType    ContainerTxTriggerMode;
    P2VAR(uint8, TYPEDEF, IPDUM_VAR)    BufferPtr;
    PduLengthType TxContainerPduLen;
    uint32     TxThresholdSize;
    PduIdType     TargetPduId;
    uint16     TxSendTimeOut;
    uint16     TxConfConstTicks;
    uint8      InstancesInQueue;
    uint8      HeaderSize;
    boolean    TxFirstContainedpduTrigger;
}IpduM_TxContainerPduType;

/**
* @ingroup IPDUM_TYPES_H
* This enum represents the Tx Contained Pdu semantics type mode \n
*
* typedef enum
* {
*    IPDUM_COLLECT_LAST_IS_BEST = 0,
*    IPDUM_COLLECT_QUEUED
* }ContainedTxPduSemanticsType;
*/
typedef enum
{
    IPDUM_COLLECT_LAST_IS_BEST = 0,
    IPDUM_COLLECT_QUEUED
}ContainedTxPduSemanticsType;

/**
* @ingroup IPDUM_TYPES_H
* This enum represents the Contained pdu Trigger type \n
* typedef enum
* {
*    IPDUM_TRIGGER_ALWAYS = 0,
*    IPDUM_TRIGGER_NEVER
* }ContainedTxPduTriggerType;
*/
typedef enum
{
    IPDUM_TRIGGER_ALWAYS = 0,
    IPDUM_TRIGGER_NEVER
}ContainedTxPduTriggerType;

/*
* typedef struct
*{
*    ContainedTxPduSemanticsType    ContainedTxPduSemantics;
*   ContainedTxPduTriggerType    ContainedTxPduTrigger;
*    uint32    PduHeaderId;
*    PduIdType   TxConfirmationTargetPduId;
*    uint16    TxPduSendTimeOut;
*    PduIdType    ContainerTxPduId;
*    boolean    TxPduConfirmation;
*}IpduM_TxContainedPduType;
*/
typedef struct
{
    ContainedTxPduSemanticsType    ContainedTxPduSemantics;
    ContainedTxPduTriggerType      ContainedTxPduTrigger;
    uint32                         PduHeaderId;
    PduIdType                      TxConfirmationTargetPduId;
    uint16                         TxPduSendTimeOut;
    PduIdType                      ContainerTxPduId;
    boolean                        TxPduConfirmation;
}IpduM_TxContainedPduType;



#endif /* IPDUM_TYPES_H */

