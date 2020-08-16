
/*PDU Router type definitions */

/*PDU Router type definitions */

/**
\defgroup PDUR_TYPES_H    PDUR - Protocol Data Unit Router
*/

#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

#include "PduR.h"
#include "PduR_Cfg_Internal.h"
#include "ComStack_Types.h"

/* ------------------------------------------------------------------------ */


/**
 * @ingroup PDUR_TYPES_H
 * this enum is used for PduR state type \n
 *
 *  typedef enum  { \n
 *   PDUR_UNINIT,               PduR uninitialized state\n
 *   PDUR_REDUCED,              PduR reduced state \n
 *   PDUR_ONLINE                PduR Online state \n
 *  }PduR_StateType;
 */

typedef enum {
   PDUR_UNINIT,
   PDUR_REDUCED,
   PDUR_ONLINE
} PduR_StateType;                                    /**/
/* PDUR_RTA-BSW_end 174 */


/* PduR_CancelReasonType
    CancelReasonType requires to have prefix of module names to avoid redefinition of this type in other modules */

/**
 * @ingroup PDUR_TYPES_H
 *
 * PduR cancel resaon type
 */
#define PDU_CNLDO   0x00u
/**
 * @ingroup PDUR_TYPES_H
 *
 * PduR cancel resaon type
 */

#define PDU_CNLNB   0x01u
/**
 * @ingroup PDUR_TYPES_H
 *
 * PduR cancel resaon type
 */

#define PDU_CNLOR   0x02u


/* Routing Path Group */
/**
 * @ingroup PDUR_TYPES_H
 *
 * Routing path group for IF path type
 */
#define PDUR_FIFO_IF    0u

/**
 * @ingroup PDUR_TYPES_H
 *
 * Routing path group for Unicast FIFO TP Path Type
 */
#define PDUR_UCFIFO_TP  1u

/**
 * @ingroup PDUR_TYPES_H
 *
 * Routing path group for Unicast SingleEntryBuffer Path Type
 */
#define PDUR_UCSEB_TP   2u

/**
 * @ingroup PDUR_TYPES_H
 *
 * Multicast SingleEntryBuffer Path Type
 */
#define PDUR_MCSEB_TP   3u

/**
 * @ingroup PDUR_TYPES_H
 *
 * Invalid PDU id handlers
 */

#define PduR_IH_CancelTransmit_Func    PduR_invId_UpCancelTransmit

/**
 * @ingroup PDUR_TYPES_H
 *
 * Invalid PDU id handlers for Cancel Receive API
 */

#define PduR_IH_CancelReceive_Func    PduR_invId_UpCancelReceive

/**
 * @ingroup PDUR_TYPES_H
 *
 * Invalid PDU id handlers for TriggerTransmit API
 */

#define PduR_IH_TriggerTransmit_Func    PduR_invId_IfTriggerTransmit

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used for Invoking Cancel Transmit Request
 */
typedef uint8 PduR_CancelReasonType;                 /* Reason for Invoking Cancel Transmit Request */

/* ------------------------------------------------------------------------ */

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate PduR_LayerType
 */

typedef uint8 PduR_LayerType;       /* to hold one of PDUR_LAYER_xxx */

/* Corresponding defines PDUR_LAYER_xxx can be found in pdur.h file */

/* ------------------------------------------------------------------------ */

/**
 * @ingroup PDUR_TYPES_H
 * This structure is used for Routing Path Group feature related definitions \n
 * typedef struct \n
 *  { \n
 *      uint8  bufferLock;          this variable is used for buffer lock \n
 *      uint8  lowerLayers;         this variable is used for loweer layers \n
 * } PduR_LockType ;
 */

typedef struct
{
   uint8    bufferLock;
   uint8    lowerLayers;
}PduR_LockType;
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR Buffer lock type.\n
 */
typedef PduR_LockType   PduR_BuffLockType;
#else
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR Buffer lock type.\n
 */
typedef uint8           PduR_BuffLockType;
#endif /* #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0) */

/* ------------------------------------------------------------------------ */
/* Routing table data structures */

/***
 Below functions can assignde to function pointer PduR_loTransmitFunc:
PduR_MF_Com_Transmit_Func
PduR_MF_Dcm_Transmit_Func
PduR_MF_IpdumUp_Transmit_Func
PduR_MF_"+uplModName+"_Transmit_Func

PduR_RF_CanIf_Transmit_Func
PduR_RF_FrNm_Transmit_Func
PduR_RF_FrIf_Transmit_Func
PduR_RF_LinIf_Transmit_Func
PduR_RF_IpdumLo_Transmit_Func
PduR_RF_CanTp_Transmit_Func
PduR_RF_FrTp_Transmit_Func
PduR_RF_LinTp_Transmit_Func

PDUR_IH_Com_Transmit_Func

PDUR_IH_Dcm_Transmit_Func
PDUR_IH_IpdumUp_Transmit_Func
PDUR_IH_"+uplModName+"_Transmit_Func

PduR_GF_TTIf_FIFO_Transmit_Func
PduR_GF_DDIf_FIFO_Transmit_Func
PduR_GF_TTIf_Buf_Transmit_Func
PduR_GF_DDIf_Buf_Transmit_Func
PduR_GF_Com_Transmit_Func
PduR_GF_Dcm_Transmit_Func
PduR_GF_IpdumUp_Transmit_Func
PduR_GF_"+uplIfNameOfRefRxPdu(dst)+"_Transmit_Func
PduR_GF_"+uplTpNameOfRefRxPdu(dst)+"_Transmit_Func

PduR_GwMcTx_Transmit_Func

NULL_PTR_LOTRANSMIT
***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR lower layer transmit function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( Std_ReturnType,  PDUR_APPL_CODE, PduR_loTransmitFunc )         ( PduIdType, PduR_TxPduInfoPtr );\n
 *}PduR_loTransmitFuncType;\n
 */
typedef struct
{
   P2FUNC( Std_ReturnType,  PDUR_APPL_CODE, PduR_loTransmitFunc )         ( PduIdType, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) );
}PduR_loTransmitFuncType;


/***
 Below functions can assignde to function pointer PduR_loCancelTransmitFunc
PDUR_IH_CancelTransmit_Func

PduR_MF_CancelTransmit_Func

PduR_RF_CanTp_CancelTransmit_Func
PduR_RF_FrTp_CancelTransmit_Func
***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR lower layer cancel transmit function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( Std_ReturnType,  PDUR_APPL_CODE, PduR_loCancelTransmitFunc )   ( PduIdType );\n
 *}PduR_loCancelTransmitFuncType;\n
 */
typedef struct
{
   P2FUNC( Std_ReturnType,  PDUR_APPL_CODE, PduR_loCancelTransmitFunc )   ( PduIdType );
}PduR_loCancelTransmitFuncType;


/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR lower layer cancel receive function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( Std_ReturnType,  PDUR_APPL_CODE, PduR_loCancelReceiveFunc )   ( PduIdType );\n
 *}PduR_loCancelReceiveFuncType;\n
 */
typedef struct
{
   P2FUNC( Std_ReturnType,  PDUR_APPL_CODE, PduR_loCancelReceiveFunc )   ( PduIdType );
}PduR_loCancelReceiveFuncType;


/***
 Below functions can assignde to function pointer PduR_upIfRxIndicationFunc
PduR_RF_Com_RxIndication_Func
PduR_RF_IpdumUp_RxIndication_Func
PduR_RF_"+uplIfNameOfRefRxPdu(routingPath.destPdu())+"_RxIndication_Func

PduR_GF_If_RxIndication_Func

PDUR_IH_CanIfRx_RxIndication_Func
PDUR_IH_FrIfRx_RxIndication_Func
PDUR_IH_IpdumLoRx_RxIndication_Func
PDUR_IH_LinIfRx_RxIndication_Func
***/
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer interface receive indication function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( void,            PDUR_APPL_CODE, PduR_upIfRxIndicationFunc )   ( PduIdType, PduR_IfRxSduPtr );\n
 *}PduR_upIfRxIndicationFuncType;\n
 */
typedef struct
{
   P2FUNC( void,            PDUR_APPL_CODE, PduR_upIfRxIndicationFunc )   ( PduIdType, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) );
}PduR_upIfRxIndicationFuncType;


/***
 Below functions can assignde to function pointer PduR_upIfTxConfirmationFunc
PduR_RF_Com_TxConfirmation_Func
PduR_RF_IpdumUp_TxConfirmation_Func
PduR_RF_"+canifdest.uplNameFromDestPdu()+"_TxConfirmation_Func
PduR_RF_"+frifdest.uplNameFromDestPdu()+"_TxConfirmation_Func
PduR_RF_"+getTheUpLIfName(destPdu)+"_TxConfirmation_Func
PduR_RF_"+linifdest.uplNameFromDestPdu()+"_TxConfirmation_Func

PduR_null_ComTxConfirmation_Func
PduR_null_IpdumUpTxConfirmation_Func
PduR_null_"+canifdest.uplNameFromDestPdu()+"TxConfirmation_Func

PduR_GF_DDIf_NoBuf_TxConfirmation_Func
PduR_GF_DDIf_Buf_TxConfirmation_Func
PduR_GF_DDIf_FIFO_TxConfirmation_Func
PduR_GF_TTIf_Buf_TxConfirmation_Func
PduR_GF_TTIf_FIFO_TxConfirmation_Func


PDUR_IH_CanIfTx_TxConfirmation_Func
PDUR_IH_FrIfTx_TxConfirmation_Func
PDUR_IH_LinIfTx_TxConfirmation_Func
PDUR_IH_IpdumLoTx_TxConfirmation_Func
***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer interface transmit confirmation function type.\n
 *typedef struct \n
 *{\n
 *    P2FUNC( void,            PDUR_APPL_CODE, PduR_upIfTxConfirmationFunc ) ( PduIdType );\n
 *}PduR_upIfTxConfirmationFuncType;\n
 */
typedef struct
{
    P2FUNC( void,            PDUR_APPL_CODE, PduR_upIfTxConfirmationFunc ) ( PduIdType );
}PduR_upIfTxConfirmationFuncType;


/***
 Below functions can assignde to function pointer PduR_upIfTriggerTxFunc
PduR_RF_Com_TriggerTransmit_Func
PduR_RF_IpdumUp_TriggerTransmit_Func
PduR_RF_"+frifdest.uplNameFromDestPdu()+"_TriggerTransmit_Func
PduR_RF_"+linifdest.uplNameFromDestPdu()+"_TriggerTransmit_Func

PduR_NF_TriggerTransmit_Func

PduR_GF_TTIf_Buf_TriggerTransmit_Func
PduR_GF_TTIf_FIFO_TriggerTransmit_Func

PDUR_IH_FrIfTx_TriggerTransmit_Func
PDUR_IH_LinIfTx_TriggerTransmit_Func
***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer interface trigger transmit function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( Std_ReturnType,            PDUR_APPL_CODE, PduR_upIfTriggerTxFunc )      ( PduIdType, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) );\n
 *}PduR_upIfTriggerTxFuncType;\n
 */
typedef struct
{
   P2FUNC( Std_ReturnType,            PDUR_APPL_CODE, PduR_upIfTriggerTxFunc )      ( PduIdType, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) );
}PduR_upIfTriggerTxFuncType;


/***
 Below functions can assignde to function pointer PduR_upTpProvideRxBufFunc
PduR_RF_Dcm_ProvideRxBuffer_Func
PduR_RF_"+uplTpNameOfRefRxPdu(routingPath.destPdu())+"_ProvideRxBuffer_Func

PduR_GF_CanTp_FIFO_ProvideRxBuffer_Func
PduR_GF_CanTp_Buf_ProvideRxBuffer_Func
PduR_GF_FrTp_FIFO_ProvideRxBuffer_Func
PduR_GF_FrTp_Buf_ProvideRxBuffer_Func
PduR_GF_LinTp_FIFO_ProvideRxBuffer_Func
PduR_GF_LinTp_Buf_ProvideRxBuffer_Func

PDUR_IH_CanTpRx_ProvideRxBuffer_Func
PDUR_IH_FrTpRx_ProvideRxBuffer_Func
PDUR_IH_LinTpRx_ProvideRxBuffer_Func
***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer copy receive data function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpCopyRxDataFunc )  ( PduIdType, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), PduLengthType* );\n
 *}PduR_upTpCopyRxDataFuncType;\n
 */
typedef struct
{
/* P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpProvideRxBufFunc )  ( PduIdType, PduLengthType, P2VAR( P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), TYPEDEF, PDUR_APPL_DATA ) );*/
   P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpCopyRxDataFunc )  ( PduIdType, P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), PduLengthType* );
}PduR_upTpCopyRxDataFuncType;

/***
 Below functions can assignde to function pointer PduR_upTpProvideRxBufFunc
PduR_RF_Dcm_StartOfReception_Func
PduR_RF_"+uplTpNameOfRefRxPdu(routingPath.destPdu())+"_StartOfReception_Func

PDUR_IH_CanTpRx_StartOfReception_Func
PDUR_IH_FrTpRx_StartOfReception_Func
PDUR_IH_LinTpRx_StartOfReception_Func
***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer Start of reception function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpStartOfReceptionFunc )  ( PduIdType, const PduInfoType*, PduLengthType, PduLengthType* );\n
 *}PduR_upTpStartOfReceptionFuncType;\n
 */
typedef struct
{
   P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpStartOfReceptionFunc )  ( PduIdType, const PduInfoType*, PduLengthType, PduLengthType* );
}PduR_upTpStartOfReceptionFuncType;


/***
 Below functions can assignde to function pointer PduR_upTpRxIndicationFunc
PduR_RF_Dcm_RxIndication_Func
PduR_RF_"+uplTpNameOfRefRxPdu(routingPath.destPdu())+"_RxIndication_Func

PduR_GF_CanTp_FIFO_RxIndication_Func
PduR_GF_CanTp_Buf_RxIndication_Func
PduR_GF_FrTp_FIFO_RxIndication_Func
PduR_GF_FrTp_Buf_RxIndication_Func
PduR_GF_LinTp_FIFO_RxIndication_Func
PduR_GF_LinTp_Buf_RxIndication_Func

PDUR_IH_CanTpRx_RxIndication_Func
PDUR_IH_FrTpRx_RxIndication_Func
PDUR_IH_LinTpRx_RxIndication_Func
***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer receive indication function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( void,            PDUR_APPL_CODE, PduR_upTpRxIndicationFunc )   ( PduIdType, Std_ReturnType );\n
 *}PduR_upTpRxIndicationFuncType;\n
 */
typedef struct
{
   P2FUNC( void,            PDUR_APPL_CODE, PduR_upTpRxIndicationFunc )   ( PduIdType, Std_ReturnType );
}PduR_upTpRxIndicationFuncType;


/***
 Below functions can assignde to function pointer PduR_upTpProvideTxBufFunc
PduR_RF_Dcm_ProvideTxBuffer_Func
PduR_RF_"+uplTpNameOfRefTxPdu(routingPath.destPdu())+"_ProvideTxBuffer_Func

PduR_GF_CanTp_FIFO_ProvideTxBuffer_Func
PduR_GF_CanTp_Buf_ProvideTxBuffer_Func
PduR_GF_FrTp_FIFO_ProvideTxBuffer_Func
PduR_GF_FrTp_Buf_ProvideTxBuffer_Func
PduR_GF_LinTp_FIFO_ProvideTxBuffer_Func
PduR_GF_LinTp_Buf_ProvideTxBuffer_Func

PDUR_IH_CanTpTx_ProvideTxBuffer_Func
PDUR_IH_FrTpTx_ProvideTxBuffer_Func
PDUR_IH_LinTpTx_ProvideTxBuffer_Func

***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer copy transmit data function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpCopyTxDataFunc )  ( PduIdType, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), RetryInfoType*,PduLengthType*);\n
 *}PduR_upTpCopyTxDataFuncType;\n
 */
typedef struct
{
/*   P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpProvideTxBufFunc )  ( PduIdType, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), RetryInfoType*,PduLengthType*);*/
    P2FUNC( BufReq_ReturnType,PDUR_APPL_CODE, PduR_upTpCopyTxDataFunc )  ( PduIdType, P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ), RetryInfoType*,PduLengthType*);
}PduR_upTpCopyTxDataFuncType;


/***
 Below functions can assignde to function pointer PduR_upTpTxConfirmationFunc
PduR_RF_Dcm_TxConfirmation_Func
PduR_RF_"+uplTpNameOfRefTxPdu(routingPath.destPdu())+"_TxConfirmation_Func

PduR_GF_CanTp_FIFO_TxConfirmation_Func
PduR_GF_CanTp_Buf_TxConfirmation_Func
PduR_GF_FrTp_FIFO_TxConfirmation_Func
PduR_GF_FrTp_Buf_TxConfirmation_Func
PduR_GF_LinTp_FIFO_TxConfirmation_Func
PduR_GF_LinTp_Buf_TxConfirmation_Func

PDUR_IH_CanTpRx_TxConfirmation_Func
PDUR_IH_FrTpRx_TxConfirmation_Func
PDUR_IH_LinTpRx_TxConfirmation_Func

***/

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is used to indicate the PduR upper layer transmit confirmation function type.\n
 *typedef struct \n
 *{\n
 *  P2FUNC( void,            PDUR_APPL_CODE, PduR_upTpTxConfirmationFunc ) ( PduIdType, Std_ReturnType );\n
 *}PduR_upTpTxConfirmationFuncType;\n
 */
typedef struct
{
   P2FUNC( void,            PDUR_APPL_CODE, PduR_upTpTxConfirmationFunc ) ( PduIdType, Std_ReturnType );
}PduR_upTpTxConfirmationFuncType;


/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR lower layer transmit function pointer.\n
 */
typedef uint8 PduR_loTransmitFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR lower layer cancel transmit function pointer.\n
 */
typedef uint8 PduR_loCancelTransmitFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR upper interface layer receive indication function pointer.\n
 */
typedef uint8 PduR_upIfRxIndicationFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR upper interface layer transmit confirmation function pointer.\n
 */
typedef uint8 PduR_upIfTxConfirmationFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR upper interface layer trigger transmit function pointer.\n
 */
typedef uint8 PduR_upIfTriggerTxFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR upper transport layer start of reception function pointer.\n
 */
typedef uint8 PduR_upTpStartOfReceptionFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR upper transport layer provide receive buffer function pointer.\n
 */
typedef uint8 PduR_upTpProvideRxBufFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is upper transport layer receive indication function pointer.\n
 */
typedef uint8 PduR_upTpRxIndicationFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR upper transport layer provide transmit buffer function pointer.\n
 */
typedef uint8 PduR_upTpProvideTxBufFP;
/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR upper transport layer transmit confirmation function pointer.\n
 */
typedef uint8 PduR_upTpTxConfirmationFP;


/**
 * @ingroup PDUR_TYPES_H
 * This structure represents ID of the lower layer ot transmit data. \n
 * typedef struct \n
 *  { \n
 *      PduIdType                    loId;                      lower layer ID \n
 *      PduR_loTransmitFP            loTransmitID;              lower layer transmit ID \n
 *      PduR_loCancelTransmitFP      loCancelTransmitID;        lower layer cancel transmit ID\n
 * } PduR_RT_UpToLo ;
 */
typedef struct
{
    PduIdType                    loId;
    PduR_loTransmitFP            loTransmitID;
    PduR_loCancelTransmitFP      loCancelTransmitID;
} PduR_RT_UpToLo;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents ID of the upper layer to give receive indication. \n
 * typedef struct \n
 *  { \n
 *      PduIdType                    upId;                      upper layer ID\n
 *      PduR_upIfRxIndicationFP      upRxIndicationID;          upper layer receive indication ID \n
 * } PduR_RT_LoIfRxToUp ;
 */
typedef struct
{
    PduIdType                    upId;
    PduR_upIfRxIndicationFP      upRxIndicationID;
} PduR_RT_LoIfRxToUp;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents ID of the upper layer to give transmit confirmation. \n
 * typedef struct \n
 *  { \n
 *      PduIdType                    upId;                      upper layer ID\n
 *      PduR_upIfTxConfirmationFP    upTxConfirmationID;        upper layer transmit confirmation ID \n
 * } PduR_RT_LoIfTxToUp ;
 */
typedef struct
{
    PduIdType                    upId;
    PduR_upIfTxConfirmationFP    upTxConfirmationID;
} PduR_RT_LoIfTxToUp;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents ID of the upper layer to give trigger transmit confirmation. \n
 * typedef struct \n
 *  { \n
 *      PduIdType                    upId;                      upper layer ID\n
 *      PduR_upIfTriggerTxFP         upTriggerTxID;             upper layer trigger transmit ID \n
 *      PduR_upIfTxConfirmationFP    upTxConfirmationID;        upper layer transmit confirmation ID \n
 * } PduR_RT_LoTtIfTxToUp ;
 */
typedef struct
{
    PduIdType                    upId;
    PduR_upIfTriggerTxFP         upTriggerTxID;
    PduR_upIfTxConfirmationFP    upTxConfirmationID;
 } PduR_RT_LoTtIfTxToUp;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents ID of the upper layer to give receive indication. \n
 * typedef struct \n
 *  { \n
 *      PduIdType                    upId;                  upper layer ID\n
 *      PduR_upTpStartOfReceptionFP  upStartOfReceptionID;  upper layer start of reception node ID \n
 *      PduR_upTpProvideRxBufFP      upProvideRxBufID;      upper layer receive buffer ID \n
 *      PduR_upTpRxIndicationFP      upRxIndicationID;      upper layer receive indication ID\n
 * } PduR_RT_LoTpRxToUp ;
 */
typedef struct
{
   PduIdType                    upId;
   PduR_upTpStartOfReceptionFP  upStartOfReceptionID;
   PduR_upTpProvideRxBufFP      upProvideRxBufID;
   PduR_upTpRxIndicationFP      upRxIndicationID;
} PduR_RT_LoTpRxToUp;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents ID of the upper layer to give transmit confirmation. \n
 * typedef struct \n
 *  { \n
 *      PduIdType                    upId;                      upper layer ID\n
 *      PduR_upTpProvideTxBufFP      upProvideTxBufID;          upper layer transmit buffer ID \n
 *      PduR_upTpTxConfirmationFP    upTxConfirmationID;        upper layer transmit confirmation ID \n
 * } PduR_RT_LoTtIfTxToUp ;
 */
typedef struct
{
    PduIdType                    upId;
    PduR_upTpProvideTxBufFP      upProvideTxBufID;
    PduR_upTpTxConfirmationFP    upTxConfirmationID;
} PduR_RT_LoTpTxToUp;

/* ------------------------------------------------------------------------ */
/* Multicast routing table data structures */
/**
 * @ingroup PDUR_TYPES_H
 *  This structure represents multicatsing from upper layer to lower layer.\n
 * typedef struct\n
 *  {\n
 *  PduIdType                    upId;      upper layer ID \n
 *  PduR_RT_UpToLo               upToLo;    lower layer name \n
 *  #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0) \n
 *  PduR_RoutingPathGroupIdType  routingCntrl_Idx;      Index to routing enable/disable status flag of RPG \n
 *  #endif \n
 *  } PduR_MT_UpToLo;
 */
typedef struct
{
   PduR_RT_UpToLo               upToLo;
    #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
   /* Index to routing enable/disable status flag of RPG */
   PduR_RoutingPathGroupIdType  routingCntrl_Idx;
   #endif /* #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0) */
   PduIdType                    upId;
   PduIdType                    upLayerSymName;
   uint8                        upSrcLayerName;
} PduR_MT_UpToLo;
/**
 * @ingroup PDUR_TYPES_H
 *  This structure represents multicatsing from lower layer interface to upper layer.\n
 * typedef struct\n
 *  {\n
 *  PduR_RT_LoTtIfTxToUp            toUp;                   upper layer name \n
 *  uint8                           destLowerLayers;        lower layer \n
 *  } PduR_MT_LoIfTxToUp;
 */

typedef struct
{
    PduR_RT_LoTtIfTxToUp         toUp;
    uint8                        destLowerLayers;
} PduR_MT_LoIfTxToUp;
/**
 * @ingroup PDUR_TYPES_H
 *  This structure represents multicatsing from lower layer TP to upper layer.\n
 * typedef struct\n
 *  {\n
 *  P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) pduPtr;   PDU info pointer  \n
 *  BufReq_ReturnType            allocError;                Error confirmation \n
 *  Std_ReturnType              txFailure;                 Tx Failure confirmation \n
 *  PduR_LayerType               txConf;                    Transmission conf  \n
 *  } PduR_MS_LoTpTxToUp;
 */
typedef struct
{
   P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) pduPtr;
   BufReq_ReturnType            allocError;
   Std_ReturnType              txFailure;
   PduR_LayerType               txConf;
  } PduR_MS_LoTpTxToUp;
/**
 * @ingroup PDUR_TYPES_H
 *  This structure represents multicatsing from lower layer TP to upper layer.\n
 * typedef struct\n
 *  {\n
 *  PduR_RT_LoTpTxToUp              toUp;                   upper layer name \n
 *  uint8                           destLowerLayers;        lower layer \n
 *  } PduR_MT_LoTpTxToUp;
 */
typedef struct
{
    PduR_RT_LoTpTxToUp           toUp;
    uint8                        destLowerLayers;
} PduR_MT_LoTpTxToUp;

/* ------------------------------------------------------------------------ */
/* Gateway routing table data structures */
/**
 * @ingroup PDUR_TYPES_H
 * This structure represents gateway transmission. \n
 * typedef struct \n
 *  { \n
 *      PduLengthType                length;            Data length \n
 *      PduIdType                    loId;              lower layer ID\n
 *      PduR_loTransmitFP            transmitID;        Transmit ID \n
 * } PduR_GT_IfTx ;
 */
typedef struct
{
   PduLengthType                length;
   PduIdType                    loId;
   PduR_loTransmitFP            transmitID;
} PduR_GT_IfTx;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents gateway interface. \n
 * typedef struct \n
 *  { \n
 *      P2CONST( void, TYPEDEF, PDUR_CONST ) buffer;    Points to either a PduInfoType (for a single entry buffer) or
                                                        a PduR_Buf_If_dynamic (for IF Single Buffer) or
                                                        a PduR_FIFO_fixed  \n
 *      PduIdType                    loId;              lower layer ID \n
 *      PduR_loTransmitFP            transmitID;        Transmit ID \n
 *      boolean                        isFifoType;        Fifo or Non-Fifo type \n
 * } PduR_GT_If ;
 */
typedef struct
{
   P2CONST( void, TYPEDEF, PDUR_CONST ) buffer;
   PduIdType                    loId;
   PduR_loTransmitFP            transmitID;
   boolean                      isFifoType;
} PduR_GT_If;


/**
 * @ingroup PDUR_TYPES_H
 * This structure represents fifo buffer \n
 * typedef struct \n
 *  { \n
 *   P2VAR( uint8, TYPEDEF, PDUR_VAR )    bufferPtr;    Start address of the buffer, will not be modified \n
 *   P2VAR( uint8, TYPEDEF, PDUR_VAR )    readPtr;      Start address of read pointer  \n
 *  P2VAR( uint8, TYPEDEF, PDUR_VAR )    writePtr;      Start address of write pointer  \n
 *  #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0) \n
 *  P2VAR( uint8, TYPEDEF, PDUR_VAR )    fifoBegin;     Start address of FIFO Begin, this is used only in PduR_DisableRouting \n Remove as we are not RPG on Tp
 *  #endif  \n
 * PduLengthType            numRxLength;                Number of bytes recieved                \n  Number of bytes received from source TP
 * PduLengthType            numTxLength;                Number of bytes transmitted             \n  NUmber of bytes transmitted to Des TP
 *  PduLengthType           SduLength;                  Contains the number of bytes valid in the read tp buffer \n
 *  PduLengthType           remainingBuffLength;      Calculate the length of buffer remaining  (total buffer allocated - Number of Bytes Received)     \n
 * } PduR_TpSession_Dynamic ;
 */
typedef struct
{
   P2VAR( uint8, TYPEDEF, PDUR_VAR )    bufferPtr;
   P2VAR( uint8, TYPEDEF, PDUR_VAR )    readPtr;
   P2VAR( uint8, TYPEDEF, PDUR_VAR )    writePtr;
   PduLengthType                          numRxLength;
   PduLengthType                          numTxLength;
   PduLengthType                          SduLength;
   PduLengthType                          bufferLength;
   uint8                                Rx_Status;
   uint8                                Tx_Status;
} PduR_TpSession_Dynamic;

/**
 * @ingroup PDUR_TYPES_H
 *
 * pointer to structure PduR_TpSession_Dynamic
 */
typedef P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) PduR_TpSessDynPtr;


/*@ingroup PDUR_TYPES_H
 * This structure holds list of all sessions \n
 * typedef struct
 *{
 *P2VAR(PduR_TpSession_Dynamic,AUTOMATIC, PDUR_VAR) GwTpSessionPtr;
 *}PduR_GwTp_SessionListType;*/

typedef struct
{
    P2VAR(PduR_TpSession_Dynamic,AUTOMATIC, PDUR_VAR) GwTpSessionPtr;
}PduR_GwTp_SessionListType;

/**
 * @ingroup PDUR_TYPES_H
 *
 * pointer to PduR_TpSession_Dynamic structure.
 */
typedef P2CONST(PduR_GwTp_SessionListType,TYPEDEF, PDUR_CONST) PduR_GwTp_SessionListPtr;

/*@ingroup PDUR_TYPES_H
 * typedef struct
*{
*    P2VAR(uint8,AUTOMATIC, PDUR_VAR) PduR_UpIfTxConf_ConfigPtr;
*}PduR_UpIfTxConf_Config;*/

typedef struct
{
    P2VAR(uint8,AUTOMATIC, PDUR_VAR) PduR_UpIfTxConf_ConfigPtr;
}PduR_UpIfTxConf_Config;
/**
 * @ingroup PDUR_TYPES_H
 * This is RAM structure representing TP Queueing .\n
 * typedef struct \n
 *  { \n
 *  P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR ) primarySession;              Points to either a PduR_FIFO_If_dynamic or a PduR_TpSession_Dynamic \n
 *  P2VAR( PduR_TpSession_Dynamic,  TYPEDEF, PDUR_VAR ) secondarySession;          Pdu length \n
 *  uint8                             activeSessionCount;       activeSessionCount \n
 * } PduR_TpConnection_Dynamic ;
 */
typedef struct
{
   P2VAR( PduR_TpSession_Dynamic, TYPEDEF, PDUR_VAR )     primarySession;
   /* FC_VariationPoint_START */
#ifdef PDUR_QUEUEING_SUPPORT
   P2VAR( PduR_TpSession_Dynamic,  TYPEDEF, PDUR_VAR )     secondarySession;
   uint8                                                 activeSessionCount;
#endif
   /* FC_VariationPoint_END */
} PduR_TpConnection_Dynamic;

typedef P2VAR( PduR_TpConnection_Dynamic, TYPEDEF, PDUR_VAR ) PduR_TpConnDynPtr;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents fixed fifo data frames.\n
 * typedef struct \n
 *  { \n
 *  P2VAR( uint8, TYPEDEF, PDUR_VAR ) begin;            starting address \n
 *  P2VAR( PduR_TpConnection_Dynamic,  TYPEDEF, PDUR_VAR ) connectionTable \n             Points to PduR_TpConnection_Dynamic \n
 *  PduLengthType                     eltSize;          Pdu length \n
 *  uint16                         buffPoolId;       Buffer Pool id \n
 * } PduR_FIFO_Tp_fixed ;
 */
typedef struct
{
   P2VAR( uint8, TYPEDEF, PDUR_VAR ) begin;
   P2VAR( PduR_TpConnection_Dynamic,  TYPEDEF, PDUR_VAR ) connectionTable;
   PduLengthType                     eltSize;
   uint16                            buffPoolId;
} PduR_FIFO_Tp_fixed;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents gateway transport. \n
 * typedef struct \n
 *  { \n
 *      P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) buffer;    Points to either a PduR_SingleEntryBuffer or a PduR_FIFO_fixed \n
 *      PduLengthType                TpThreshold;        PduR TpThreshold \n
 *      PduLengthType                numOfLowerLayers;         No.Of lower layers configured(To Check if its 1:n gateway multicast)
 *       FC_VariationPoint_START
 *      PduLengthType                TpGwQueueSize;        Size of the Queue for a TP gateway if it is referring to a buffer pool\n
 *      FC_VariationPoint_END
 *      PduIdType                    loId;              lower layer ID \n
 *      PduR_loTransmitFP            loTransmitID;        Transmit ID \n
 * } PduR_GT_Tp ;
 */
typedef struct
{
   P2CONST( PduR_FIFO_Tp_fixed, TYPEDEF, PDUR_CONST ) buffer;
          PduLengthType               TpThreshold;
          PduLengthType               numOfLowerLayers;
       /* FC_VariationPoint_START */
          PduLengthType               TpGwQueueSize;
       /* FC_VariationPoint_END */
          PduIdType                   loId;
          PduR_loTransmitFP           loTransmitID;
} PduR_GT_Tp;

/**
 * @ingroup PDUR_TYPES_H
 *
 * pointer to PduR_GT_Tp structure.
 */
typedef P2CONST( PduR_GT_Tp, TYPEDEF, PDUR_CONST ) PduR_GT_TpPtr;

/* ------------------------------------------------------------------------ */
/**
 * @ingroup PDUR_TYPES_H
 *
 * Change Parameter Request/Confirmation
 */
typedef uint8 PduR_LowerTpModuleName;

/**
 * @ingroup PDUR_TYPES_H
 *
 * This typedef is PduR lower layer Cancel Receive function pointer.\n
 */
typedef uint8 PduR_loCancelReceiveFP;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents the lower layer TP Pdu to call cancel receive request. \n
 * typedef struct \n
 *  { \n
 *      PduIdType                    LoTpRxId;     lower layer ID. As LoTp do not have any Rx Id, PduRSrcPduHandleId is used here \n
 *      PduR_loCancelReceiveFP       CancelRxFP;   Function Pointer for lower layer Cancel Rx API \n
 * } PduR_RT_UpTpRxToLoTp ;
 */
typedef struct
{
   PduIdType                    LoTpRxId;
/*#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
   PduR_RoutingPathGroupIdType  RpgIdx;
#endif*/
   PduR_loCancelReceiveFP       CancelRxFP;
/*   PduR_LowerTpModuleName       loTp;      Use this element of the structure for change parameter API support. Uncomment this element when Change Parameter is supported*/
} PduR_RT_UpTpRxToLoTp;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents the lower layer TP Pdu to call cancel receive request. \n
 * typedef struct \n
 *  { \n
 *      P2CONST( PduR_RT_UpTpRxToLoTp, TYPEDEF, PDUR_CONST )      UpTpToLoTp;             Pointer to PduR_RT_UpTpRxToLoTp structure \n
 *      PduIdType                                                 UpTpToLoTp_NrEntries;   No. of Routing paths per upper module \n
 * } PduR_UpTpToLoTpRxConfig;
 */
typedef struct
{
   P2CONST( PduR_RT_UpTpRxToLoTp, TYPEDEF, PDUR_CONST )      UpTpToLoTp;
   PduIdType                                                 UpTpToLoTp_NrEntries;
} PduR_UpTpToLoTpRxConfig;

/* PDUR480 */
/**
 * @ingroup PDUR_TYPES_H
 *
 */
typedef uint8 PduR_ParameterValueType;  /* Range: 0x00 - 0x7F and 0xF1 - 0xF9 */

/* ------------------------------------------------------------------------ */
/* Buffer types */
/**
 * @ingroup PDUR_TYPES_H
 * This structure represents single entry buffer type \n
 * typedef struct \n
 *  { \n
 *  PduInfoType                                     info;               Info pointer for pdu length \n
 *  P2VAR( PduR_BuffLockType, TYPEDEF, PDUR_VAR )   lockPtr;            To lock the info pointer \n
 *  P2VAR( PduInfoType, TYPEDEF, PDUR_VAR )         readerPduInfo;      To store and forward the pduinfo pointer per routing path \n
 * } PduR_SingleEntryBuffer ;
 */
typedef struct
{
    PduInfoType                       info;
    P2VAR( PduR_BuffLockType, TYPEDEF, PDUR_VAR ) lockPtr;
    P2VAR( PduInfoType, TYPEDEF, PDUR_VAR ) readerPduInfo;
} PduR_SingleEntryBuffer;

/**
 * @ingroup PDUR_TYPES_H
 *
 * pointer to PduR_SingleEntryBuffer structure.
 */
typedef P2CONST( PduR_SingleEntryBuffer, TYPEDEF, PDUR_CONST ) PduR_SingleEntryBufferPtr;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents fifo buffer \n
 * typedef struct \n
 *  { \n
 *  P2VAR( uint8, TYPEDEF, PDUR_VAR ) readPtr;           Start address of read pointer \n
 *  P2VAR( uint8, TYPEDEF, PDUR_VAR ) writePtr;          Start address of write pointer  \n
 *  PduLengthType                     actLen;            Length of data which needs to be transmitted \n
 *  uint8                             used;              Number of Fifo elements used \n
 *  uint8                             txConfPending;     Transmit pending \n
 * } PduR_FIFO_If_dynamic ;
 */
typedef struct
{
   P2VAR( uint8, TYPEDEF, PDUR_VAR ) readPtr;       /*: note that TxIdx (requested by the spec) is
                                                         logically equivalent to our readPtr */
   P2VAR( uint8, TYPEDEF, PDUR_VAR ) writePtr;
   PduLengthType                     actLen;
   uint8                             used;
   uint8                             txConfPending; /**/
} PduR_FIFO_If_dynamic;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents configured buffer \n
 * typedef struct \n
 *  { \n
 * P2VAR( PduInfoType, TYPEDEF, PDUR_VAR ) gwBuf;       Points to PduInfoType \n
 * P2VAR( uint8, TYPEDEF, PDUR_VAR ) begin;             starting address \n
 * uint8                                   confLen;     Configured Buffer Length \n
 * } PduR_Buf_If_dynamic ;
 */
typedef struct
{
   P2VAR( PduInfoType, TYPEDEF, PDUR_VAR ) gwBuf;
   P2VAR( uint8, TYPEDEF, PDUR_VAR )       begin;
   uint8                                   confLen;
} PduR_Buf_If_dynamic;

/**
 * @ingroup PDUR_TYPES_H
 *
 * pointer to structure  PduR_Buf_If_dynamic
 */
typedef P2VAR( PduR_FIFO_If_dynamic, TYPEDEF, PDUR_VAR ) PduR_FifoDynIfPtr;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents fixed fifo data frames.\n
 * typedef struct \n
 *  { \n
 *  P2VAR( uint8, TYPEDEF, PDUR_VAR ) begin;    starting address \n
 *  P2VAR( void,  TYPEDEF, PDUR_VAR ) dyn;      Points to either a PduR_FIFO_If_dynamic or a PduR_TpSession_Dynamic \n
 *  PduLengthType                     eltSize;  Pdu length \n
 *  uint8                             nrElts;   size \n
 * } PduR_FIFO_fixed ;
 */
typedef struct
{
   P2VAR( uint8, TYPEDEF, PDUR_VAR ) begin;
   P2VAR( void,  TYPEDEF, PDUR_VAR ) dyn;
   PduLengthType                     eltSize;
   uint8                             nrElts;
} PduR_FIFO_fixed;


/**
 * @ingroup PDUR_TYPES_H
 *
 * pointer to PduR_FIFO_fixed structure.
 */
typedef P2CONST( PduR_FIFO_fixed, TYPEDEF, PDUR_CONST ) PduR_FifoType;



/**
 * @ingroup PDUR_TYPES_H
 * This structure represents configured cdd data frames.\n
 * typedef struct \n
 *  { \n
 *  P2CONST( PduR_RT_UpToLo, TYPEDEF, PDUR_CONST )        CddToLo;       lower layer address \n
 *  P2CONST( PduR_MT_UpToLo, TYPEDEF, PDUR_CONST )        CddToLoMc;     multicast lower layer address \n
 *  PduIdType                                             CddToLo_NrEntries;  number of entries \n
 * } PduR_CddConfig ;
 */
typedef struct
{
   P2CONST( PduR_RT_UpToLo, TYPEDEF, PDUR_CONST )        CddToLo;
   P2CONST( PduR_MT_UpToLo, TYPEDEF, PDUR_CONST )        CddToLoMc;
   PduIdType                                             CddToLo_NrEntries;
} PduR_CddConfig;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents configured lower TP data frames.\n
 * typedef struct \n
 *  { \n
   P2CONST( PduR_RT_LoTpRxToUp, TYPEDEF, PDUR_CONST )        LoTpRxToUp;            lower Tp receive address \n
   P2CONST( PduR_RT_LoTpTxToUp, TYPEDEF, PDUR_CONST )        LoTpTxToUp;            lower Tp transmit address \n
   PduIdType                                                 LoTpRxToUp_NrEntries;  number of receive entries \n
   PduIdType                                                 LoTpTxToUp_NrEntries;  number of transmit entries \n
 * } PduR_LoTpConfig ;
 */
typedef struct
{
   P2CONST( PduR_RT_LoTpRxToUp, TYPEDEF, PDUR_CONST )        LoTpRxToUp;
   P2CONST( PduR_RT_LoTpTxToUp, TYPEDEF, PDUR_CONST )        LoTpTxToUp;
   PduIdType                                                 LoTpRxToUp_NrEntries;
   PduIdType                                                 LoTpTxToUp_NrEntries;
} PduR_LoTpConfig;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents configured Upper TP data frames.\n
 * typedef struct\n
 * { \n
 *  P2CONST( PduR_RT_UpToLo, TYPEDEF, PDUR_CONST )            UpToLo; \n
 *  P2CONST( PduR_MT_UpToLo, TYPEDEF, PDUR_CONST )            UpToLoMc; \n
 *  PduIdType                                                 UpToLo_NrEntries; \n
 *  } PduR_UpConfig; \n
 */
typedef struct
{
   P2CONST( PduR_RT_UpToLo, TYPEDEF, PDUR_CONST )            UpToLo;
   P2CONST( PduR_MT_UpToLo, TYPEDEF, PDUR_CONST )            UpToLoMc;
   PduIdType                                                 UpToLo_NrEntries;
} PduR_UpConfig;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents configured lower If data frames.\n
 * typedef struct \n
 *  { \n
   P2CONST( PduR_RT_LoIfRxToUp, TYPEDEF, PDUR_CONST )        LoIfRxToUp;            lower If receive address \n
   P2CONST( PduR_RT_LoIfTxToUp, TYPEDEF, PDUR_CONST )        LoIfTxToUp;            lower If transmit address \n
   PduIdType                                                 LoIfRxToUp_NrEntries;  number of receive entries \n
   PduIdType                                                 LoIfTxToUp_NrEntries;  number of transmit entries \n
 * } PduR_LoIfDConfig ;
 */
typedef struct
{
   P2CONST( PduR_RT_LoIfRxToUp, TYPEDEF, PDUR_CONST )        LoIfRxToUp;
   P2CONST( PduR_RT_LoIfTxToUp, TYPEDEF, PDUR_CONST )        LoIfTxToUp;
   PduIdType                                                 LoIfRxToUp_NrEntries;
   PduIdType                                                 LoIfTxToUp_NrEntries;
} PduR_LoIfDConfig;
/**
 * @ingroup PDUR_TYPES_H
 * This structure represents configured trigger transmit data frames.\n
 * typedef struct \n
 *  { \n
   P2CONST( PduR_RT_LoIfRxToUp, TYPEDEF, PDUR_CONST )        LoIfRxToUp;            lower If receive address \n
   P2CONST( PduR_RT_LoIfTxToUp, TYPEDEF, PDUR_CONST )        LoIfTxToUp;            lower If transmit address \n
   PduIdType                                                 LoIfRxToUp_NrEntries;  number of receive entries \n
   PduIdType                                                 LoIfTxToUp_NrEntries;  number of transmit entries \n
 * } PduR_LoIfTTConfig ;
 */
typedef struct
{
    P2CONST( PduR_RT_LoIfRxToUp, TYPEDEF, PDUR_CONST )        LoIfRxToUp;
    P2CONST( PduR_RT_LoTtIfTxToUp, TYPEDEF, PDUR_CONST )      LoIfTxToUp;
   PduIdType                                                 LoIfRxToUp_NrEntries;
   PduIdType                                                 LoIfTxToUp_NrEntries;
} PduR_LoIfTTConfig;


/* ------------------------------------------------------------------------ */

/* Routing Path Group feature related definitions. */

/**
 * @ingroup PDUR_TYPES_H
 *
 * Void pointer used in RPG PduR_TargetInfoType structure \n
 */
typedef P2VAR( void, TYPEDEF, PDUR_VAR ) PduR_RPGVoidPtr;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents target type.  \n
 * typedef struct \n
 *  { \n
 *      PduR_RPGVoidPtr                             destInfo;           Pointer to Dest info table within the RPG  \n
 *      uint8                                       pathType;           For which PathType this Dest belongs to \n
 * } PduR_TargetInfoType ;
 */
typedef struct
{
    PduR_RPGVoidPtr             destInfo;
    uint8                       pathType;
} PduR_TargetInfoType;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents routing path group type.  \n
 * typedef struct \n
 *  { \n
 *      P2CONST( PduR_TargetInfoType, TYPEDEF, PDUR_CONST )     targetInfo;      Pointer to target info table for this RPG \n
 *      PduR_RoutingPathGroupIdType                             rpg_Idx;        Index to routing enable/disable status flag of RPG  \n
 *      uint8                                                   cntDest;        Number of DestPdus \n
 * } PduR_RPGInfoType ;
 */
typedef struct
{
    P2CONST( PduR_TargetInfoType, TYPEDEF, PDUR_CONST ) targetInfo;
    PduR_RoutingPathGroupIdType                         rpg_Idx;
    uint8                                               cntDest;
} PduR_RPGInfoType;

/**
 * @ingroup PDUR_TYPES_H
 * This structure holds pointer various function pointer tables defined above. \n
 * typedef struct\n
 *  {\n
 *  P2CONST( PduR_loTransmitFuncType, TYPEDEF, PDUR_CONST )             loTxTablePtr;           Pointer to PduR_loTransmitTable which points to various <Lo>_Transmit API. \n
 *  P2CONST( PduR_loCancelTransmitFuncType, TYPEDEF, PDUR_CONST )       loCnclTxTablePtr;       Pointer to PduR_loCancelTransmitTable which points to various <Lo>_CancelTransmit API. \n
 *  P2CONST( PduR_upIfRxIndicationFuncType, TYPEDEF, PDUR_CONST )       upIfRxIndTablePtr;      Pointer to PduR_upIfRxIndicationTable which points to various <UpIf>_RxIndication API. \n
 *  P2CONST( PduR_upIfTxConfirmationFuncType, TYPEDEF, PDUR_CONST )     upIfTxConfTablePtr;     Pointer to PduR_upIfTxConfirmationTable which points to various <UpIf>_TxConfirmation API. \n
 *  P2CONST( PduR_upTpCopyRxDataFuncType, TYPEDEF, PDUR_CONST )         upTpRxDataTablePtr;     Pointer to PduR_upTpCopyRxDataTable which points to various <UpTp>_CopyRxData API. \n
 *  P2CONST( PduR_upTpStartOfReceptionFuncType, TYPEDEF, PDUR_CONST )   upTpStartRxTablePtr;    Pointer to PduR_upTpStartOfReceptionTable which points to various <UpTp>_StartOfReception API. \n
 *  P2CONST( PduR_upTpRxIndicationFuncType, TYPEDEF, PDUR_CONST )       upTpRxIndTablePtr;      Pointer to PduR_upTpRxIndicationTable which points to various <UpTp>_RxIndication API. \n
 *  P2CONST( PduR_upTpCopyTxDataFuncType, TYPEDEF, PDUR_CONST )         upTpTxDataTablePtr;     Pointer to PduR_upTpCopyTxDataTable which points to various <UpTp>_CopyTxData API. \n
 *  P2CONST( PduR_upTpTxConfirmationFuncType, TYPEDEF, PDUR_CONST )     upTpTxConfTablePtr;     Pointer to PduR_upTpTxConfirmationTable which points to various <UpTp>_TxConfirmation API. \n
 *  P2CONST( PduR_upIfTriggerTxFuncType, TYPEDEF, PDUR_CONST )          upIfTrigTxTablePtr;     Pointer to PduR_upIfTriggerTxTable which points to various <UpIf>_TriggerTransmit API. \n
 * } PduR_RPTablesType; \n
*/
typedef struct 
{
    P2CONST( PduR_loTransmitFuncType, TYPEDEF, PDUR_CONST )             loTxTablePtr;
    P2CONST( PduR_loCancelReceiveFuncType, TYPEDEF,  PDUR_CONST)        loCancelRxTable;
    P2CONST( PduR_loCancelTransmitFuncType, TYPEDEF, PDUR_CONST )       loCnclTxTablePtr;
    P2CONST( PduR_upIfRxIndicationFuncType, TYPEDEF, PDUR_CONST )       upIfRxIndTablePtr;
    P2CONST( PduR_upIfTxConfirmationFuncType, TYPEDEF, PDUR_CONST )     upIfTxConfTablePtr;
    P2CONST( PduR_upTpCopyRxDataFuncType, TYPEDEF, PDUR_CONST )         upTpRxDataTablePtr;
    P2CONST( PduR_upTpStartOfReceptionFuncType, TYPEDEF, PDUR_CONST )   upTpStartRxTablePtr;
    P2CONST( PduR_upTpRxIndicationFuncType, TYPEDEF, PDUR_CONST )       upTpRxIndTablePtr;
    P2CONST( PduR_upTpCopyTxDataFuncType, TYPEDEF, PDUR_CONST )         upTpTxDataTablePtr;
    P2CONST( PduR_upTpTxConfirmationFuncType, TYPEDEF, PDUR_CONST )     upTpTxConfTablePtr;
    P2CONST( PduR_upIfTriggerTxFuncType, TYPEDEF, PDUR_CONST )          upIfTrigTxTablePtr;
} PduR_RPTablesType;

/**
 * @ingroup PDUR_TYPES_H
 * This structure represents Post build config types. \n
 * typedef struct\n
 *  {\n
 *   P2CONST( PduR_CddConfig,        TYPEDEF, PDUR_CONST )  cddConf;        CDD config \n
 *   P2CONST( PduR_LoTpConfig,       TYPEDEF, PDUR_CONST )  LoTpConf;       Lower Tp config \n
 *   P2CONST( PduR_LoIfDConfig,      TYPEDEF, PDUR_CONST )  LoIfDConf;      Lower If config \n
 *   P2CONST( PduR_LoIfTTConfig,     TYPEDEF, PDUR_CONST )  LoIfTTConf;     Lower if trigger transmit config \n
 *   P2CONST( PduR_UpConfig,         TYPEDEF, PDUR_CONST )  UpIfConf;       Upper layer If config
 *   P2CONST( PduR_UpConfig,         TYPEDEF, PDUR_CONST )  UpTpConf;;      Upper layer Tp config \n
 *   P2CONST( PduR_MT_UpToLo,        TYPEDEF, PDUR_CONST )  gwToLoMc;       gateway to lower layer multicasting \n
 *   P2CONST( PduR_MT_LoIfTxToUp,    TYPEDEF, PDUR_CONST )  loIfTxToUpMc;   lower If transmission to upper layer multicasting \n
 *   P2CONST( PduR_MT_LoTpTxToUp,    TYPEDEF, PDUR_CONST )  loTpTxToUpMc;   lower Tp transmission to upper layer multicasting \n
 *   P2VAR(   PduR_MS_LoTpTxToUp,    TYPEDEF, PDUR_VAR )    loTpTxToUpMs;   lower If transmission to upper layer \n
 *   P2CONST( PduR_GT_IfTx,          TYPEDEF, PDUR_CONST )  gwIfTx;         gateway if transmission \n
 *   P2CONST( PduR_GT_If,            TYPEDEF, PDUR_CONST )  gwIf;           gateway If \n
 *   P2CONST( PduR_GT_Tp,            TYPEDEF, PDUR_CONST )  gwTp;           gateway Tp \n
 *   P2CONST( PduR_RPTablesType,     TYPEDEF, PDUR_CONST )  PduR_RPTablesPtr   \n
 *
 *  #if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)\n
 *   P2CONST (PduR_RPGInfoType,      TYPEDEF, PDUR_CONST)   rpg_ConfigInfo;     config info \n
 *   P2VAR (boolean, TYPEDEF, PDUR_CONST)   rpg_EnRoutingInfo; \n
 *   PduR_RoutingPathGroupIdType                            rpg_NrEntries;          Number of RPGs\n
 *  #endif \n
 *   P2CONST (PduR_UpTpToLoTpRxConfig, TYPEDEF, PDUR_CONST) PduR_UpTpToLoTpRxCfg;   To Support Cancel Receive API \n
 *   uint16                                                 configId;       config ID \n
 *   PduIdType                                              loTpTxToUpMc_NrEntries; number of entries from lower layer to upper layer multicasting \n
 * } PduR_PBConfigType;
*/
typedef struct 
{
    P2CONST( PduR_CddConfig,        TYPEDEF, PDUR_CONST )  cddConf;
    P2CONST( PduR_LoTpConfig,       TYPEDEF, PDUR_CONST )  LoTpConf;
    P2CONST( PduR_LoIfDConfig,      TYPEDEF, PDUR_CONST )  LoIfDConf;
    P2CONST( PduR_LoIfTTConfig,     TYPEDEF, PDUR_CONST )  LoIfTTConf;
    P2CONST( PduR_UpConfig,         TYPEDEF, PDUR_CONST )  UpIfConf;
    P2CONST( PduR_UpConfig,         TYPEDEF, PDUR_CONST )  UpTpConf;
    P2CONST( PduR_MT_UpToLo,        TYPEDEF, PDUR_CONST )  gwToLoMc;
    P2CONST( PduR_MT_LoIfTxToUp,    TYPEDEF, PDUR_CONST )  loIfTxToUpMc;
    P2CONST( PduR_MT_LoTpTxToUp,    TYPEDEF, PDUR_CONST )  loTpTxToUpMc;
    P2VAR(   PduR_MS_LoTpTxToUp,    TYPEDEF, PDUR_VAR )    loTpTxToUpMs;

    P2CONST( PduR_GT_IfTx,          TYPEDEF, PDUR_CONST )  gwIfTx;
    P2CONST( PduR_GT_If,            TYPEDEF, PDUR_CONST )  gwIf;
    P2CONST( PduR_GT_Tp,            TYPEDEF, PDUR_CONST )  gwTp;
    P2CONST( PduR_RPTablesType,     TYPEDEF, PDUR_CONST )  PduR_RPTablesPtr;
#if defined(PDUR_TPGATEWAY_SUPPORT) && (PDUR_TPGATEWAY_SUPPORT != STD_OFF)
    P2CONST(PduR_GwTp_SessionListType, TYPEDEF, PDUR_CONST )  gwTp_SessionListPtr;
#endif
#if defined(PDUR_MULTICAST_TO_IF_SUPPORT) && (PDUR_MULTICAST_TO_IF_SUPPORT != 0)
    P2CONST(PduR_UpIfTxConf_Config, TYPEDEF, P2CONST) UpIfTxConf_Config;
#endif
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
    P2CONST (PduR_RPGInfoType,      TYPEDEF, PDUR_CONST)   rpg_ConfigInfo;
    P2CONST (boolean, TYPEDEF, PDUR_CONST)   rpg_EnRoutingInfo;
    P2VAR(boolean , TYPEDEF , PDUR_VAR)   pduR_Rpg_Status;
    PduR_RoutingPathGroupIdType                            rpg_NrEntries; /* Number of RPGs.*/
#endif
    P2CONST (PduR_UpTpToLoTpRxConfig, TYPEDEF, PDUR_CONST) PduR_UpTpToLoTpRxCfg; /*To Support Cancel Receive API*/
    uint16                                                 configId;
    uint16                                                 totalNoOfGwTpRps; /*Total no of GwTp routingPaths*/
    uint16                                                 totalNoOfGwIfRps; /*Total no of GwIf routingPaths*/
    PduIdType                                              loTpTxToUpMc_NrEntries;
} PduR_PBConfigType;


typedef struct
{
    VAR(Dem_EventStatusType, PDUR_VAR) initFailedErrorStatus;
    VAR(Dem_EventStatusType, PDUR_VAR) instanceLostErrorStatus;
    VAR(boolean, PDUR_VAR) initFailedErrorFlag;
    VAR(boolean, PDUR_VAR) instanceLostErrorFlag;
}PduR_DsmReInitType;


/**
 * @ingroup PDUR_TYPES_H
 *
 * PduR internal return type,typedef to Uint8
 */
typedef uint8 PduR_ReturnType;

/**
 * @ingroup PDUR_TYPES_H
 *
 * PduR internal Gw If buffer Type,Defined to Boolean value
 */
#define PduR_GwIfBufType_FIFO TRUE

/**
 * @ingroup PDUR_TYPES_H
 *
 * PduR internal Gw If buffer Type,Defined to Boolean value
 */
#define PduR_GwIfBufType_NonFIFO FALSE


#endif /* PDUR_TYPES_H */

