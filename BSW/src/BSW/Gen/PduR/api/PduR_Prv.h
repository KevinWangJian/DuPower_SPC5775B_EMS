

#ifndef PDUR_PRV_H
#define PDUR_PRV_H

#include "PduR.h"
#include "PduR_Cfg_Internal.h"
#include "PduR_Cfg_SchM.h"
#if (!defined(SCHM_AR_RELEASE_MAJOR_VERSION) || (SCHM_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(SCHM_AR_RELEASE_MINOR_VERSION) || (SCHM_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
#include "Det.h"   /* For Det_ReportError() */   /* Inter Modular Check */
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != PDUR_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != PDUR_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif

#include "PduR_Types.h"

#if defined(PDUR_ZERO_COST_OPERATION) && (PDUR_ZERO_COST_OPERATION != STD_OFF)
#include "PduR_ZeroCost_Cfg.h"
#endif

/**
 * @ingroup PDUR_H
 *
 * magic number - Required only for configuration\n
 */
#define PDUR_CONFIGTYPE_MAGIC      (0x025fe8a7uL)

/* ------------------------------------------------------------------------ */


/* PduR_LayerType */
/* Allocate each layer a separate bit, so that a PduR_LayerType
 * can be treated as a collection of flags. */
/**
 * @ingroup PDUR_H
 *
 * Allocate CanTp layer a separate bit, so that a PduR_LayerType_CanTp can be treated as flag.
 */
#define PDUR_LAYER_CANTP           ((uint8)0x01)
/**
 * @ingroup PDUR_H
 *
 * Allocate FrTp layer a separate bit, so that a PduR_LayerType_FrTp can be treated as flag.
 */
#define PDUR_LAYER_FRTP            ((uint8)0x02)
/**
 * @ingroup PDUR_H
 *
 * Allocate LinTp layer a separate bit, so that a PduR_LayerType_LinTp can be treated as flag.
 */
#define PDUR_LAYER_LINTP           ((uint8)0x04)
/**
 * @ingroup PDUR_H
 *
 * Allocate CanIf layer a separate bit, so that a PduR_LayerType_CanIf can be treated as flag.
 */
#define PDUR_LAYER_CANIF           ((uint8)0x10)
/**
 * @ingroup PDUR_H
 *
 * Allocate FrIf layer a separate bit, so that a PduR_LayerType_FrIf can be treated as flag.
 */
#define PDUR_LAYER_FRIF            ((uint8)0x20)
/**
 * @ingroup PDUR_H
 *
 * Allocate LinIf layer a separate bit, so that a PduR_LayerType_LinIf can be treated as flag.
 */
#define PDUR_LAYER_LINIF           ((uint8)0x40)
/**
 * @ingroup PDUR_H
 *
 * Allocate a separate bit, so that a PduR_Multicast can be treated as flag.Only used for TP/FIFO routes
 */
#define PDUR_MULTICAST             ((uint8)0x80)    /* Only used for TP/FIFO routes */
/**
 * @ingroup PDUR_H
 *
 * Allocate IpduM Lo layer a separate bit, so that a PduR_LayerType_IpduMLo can be treated as flag.
 */
#define PDUR_LAYER_IPDUMLO         ((uint8)0x08)
/**
 * @ingroup PDUR_H
 *
 * Allocate J1939Tp layer a separate bit, so that a PduR_LayerType_J1939Tp can be treated as flag.
 */
#define PDUR_LAYER_J1939TP         ((uint8)0x08)

/* ------------------------------------------------------------------------ */

/**
 * @ingroup PDUR_H
 *
 * Event IDs
 * typedef enum {
 *    PDUR_EVENT_RXINDICATION = 0x01,
 *   PDUR_EVENT_TRANSMITCONFIRMATION ,
 *   PDUR_EVENT_COPYTXDATA,
 *   PDUR_EVENT_COPYRXDATA ,
 *   PDUR_EVENT_TRANSMIT,
 *   PDUR_EVENT_CANCELTRANSMIT,
 *   PDUR_EVENT_TRIGGERTRANSMIT
 *    } PduR_EventType;
 */
typedef enum {
    PDUR_EVENT_RXINDICATION = 0x01,
    PDUR_EVENT_TRANSMITCONFIRMATION ,
    PDUR_EVENT_COPYTXDATA,
    PDUR_EVENT_COPYRXDATA ,
    PDUR_EVENT_TRANSMIT,
    PDUR_EVENT_CANCELTRANSMIT,
    PDUR_EVENT_TRIGGERTRANSMIT
} PduR_EventType;

/* ------------------------------------------------------------------- */
/**
 * @ingroup PDUR_PRV_H
 *
 * Checking for PDUR init state
 * */
#define  PDUR_CHECK_STATE_VOID(sid)                     \
   if ( PduR_State == PDUR_UNINIT )                     \
   {                                                    \
      PDUR_REPORT_ERROR((sid), PDUR_E_INVALID_REQUEST); \
      return;                                           \
   }

/**
 * @ingroup PDUR_PRV_H
 *
 * Returns the state and if the PDU Router has not been initialized (PDUR_UNINIT state) all services except PduR_Init() will
 * report the error PDUR_E_INVALID_REQUEST through the Development Error Tracer (DET) when called
 */

#define  PDUR_CHECK_STATE_RET(sid,ret)                  \
   if ( PduR_State == PDUR_UNINIT )                     \
   {                                                    \
      PDUR_REPORT_ERROR((sid), PDUR_E_INVALID_REQUEST); \
      return (ret);                                       \
   }

/**
 * @ingroup PDUR_PRV_H
 *
 * Checks for invalid pointer.If the pointer is invalid, PDUR_E_NULL_POINTER is reported via DET
 */
#define  PDUR_CHECK_PTR_RET(sid, ptr, ret)                      \
   if ( !(ptr) )                                                \
   {                                                            \
      PDUR_REPORT_ERROR((sid), PDUR_E_NULL_POINTER);        \
      return (ret);                                               \
   }

/**
 * @ingroup PDUR_PRV_H
 *
 * checking for NULL or void pointer
 * */

#define  PDUR_CHECK_PTR_VOID(sid, ptr)                          \
   if ( !(ptr) )                                                \
   {                                                            \
      PDUR_REPORT_ERROR((sid), PDUR_E_NULL_POINTER);        \
      return;                                                   \
   }


#if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
/**
 * @ingroup PDUR_PRV_H
 *
 * Instance id is added - Autosar Release2.1
 */
#define PDUR_REPORT_ERROR(serviceId, errorId) (void)Det_ReportError(PDUR_MODULE_ID, PDUR_INSTANCE_ID /*InstanceID*/ , serviceId, errorId)  
#else
/**
 * @ingroup PDUR_PRV_H
 *
 * To remove MISRA warning
 */
#define PDUR_REPORT_ERROR(serviceId, errorId) do {} while(0) /* To remove MISRA warning */
#endif

/* ------------------------------------------------------------------------ */
/* Begin a set of variable definitions */


#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern VAR(PduR_DsmReInitType, PDUR_VAR) PduR_DsmReInitStruct;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"


/**
 * @ingroup PDUR_H
 *
 * PduR_Base: Access to configuration  \n
 *
 */
/* ------------------------------------------------------------------------ */
/* Begin a set of variable definitions */

#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern P2CONST( PduR_PBConfigType, PDUR_CONST, PDUR_APPL_CONST ) PduR_Base;

/* ------------------------------------------------------------------------ */
/* End section for variable */

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

#if(PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)

/* ------------------------------------------------------------------------ */
/* Begin section for variables */
# define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
# include "PduR_MemMap.h"

extern P2CONST( PduR_RPTablesType, PDUR_CONST, PDUR_APPL_CONST ) PduR_FunctionPtrs;

/* ------------------------------------------------------------------------ */
/* End section for variables */
# define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
# include "PduR_MemMap.h"

#endif

/*
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

extern P2CONST(PduR_GwTp_SessionListType,AUTOMATIC, PDUR_CONST) PduR_GwTp_SessionListPtr;

#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"
*/


#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

extern CONST( PduR_PBConfigType, PDUR_CONST ) PduR_GlobalPBConfig;

extern CONST( PduR_RPTablesType, PDUR_CONST ) PduR_RoutingPathTables;

#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"
/**
 * @ingroup PDUR_H
 *
 * This Macro is used to point to that particular structure which is generated in PduR_PBConfigType structure
 */
#define PDUR_BASE(s)          (PduR_Base->s)
/**
 * @ingroup PDUR_H
 *
 *
 * This Macro is used to point to that any Lower Transport protocol structure which is generated in PduR_PBConfigType structure
 */
#define PDUR_BASE_LOTP(n,s)       (PduR_Base->LoTpConf[n].s)
/**
 * @ingroup PDUR_H
 *
 * This Macro is used to point to that any Lower Communication Interface which is direct as data provision
 *  structure which is generated in PduR_PBConfigType structure
 */
#define PDUR_BASE_LOIFD(n,s)      (PduR_Base->LoIfDConf[n].s)
/**
 * @ingroup PDUR_H
 *
 * This Macro is used to point to that any Lower Communication Interface which is trigger transmit as data provision
 *  structure which is generated in PduR_PBConfigType structure
 */
#define PDUR_BASE_LOIFTT(n,s)     (PduR_Base->LoIfTTConf[n].s)
/**
 * @ingroup PDUR_H
 *
 * PduR_DcmTransmit: Access to dcmToLo configuration  \n
 */
#define PDUR_BASE_UPTP(n,s)        (PduR_Base->UpTpConf[n].s)       /* PduR_DcmTransmit */

/**
 * @ingroup PDUR_H
 *
 * PduR_<UpIfModule>Transmit: Access to <UpIf>ToLo configuration  \n
 */
#define PDUR_BASE_UPIF(n,s)        (PduR_Base->UpIfConf[n].s)       /* PduR_<UpIfModule>Transmit */

/**
 * @ingroup PDUR_H
 *
 * PduR_<UpTp>CancelReceive: Access to <UpTp>ToLoRx configuration  \n
 */
#define PDUR_BASE_UPTPCANCELRX(n,s)        (PduR_Base->PduR_UpTpToLoTpRxCfg[n].s)       /* PduR_<UpTp>CancelReceive */

/**
 * @ingroup PDUR_H
 *
 * This macro is used to point to any table in PduR_RoutingPathTables \n
 */
/* MR12 RULE 20.7 VIOLATION: Putting 's' in (), throws compilation error. So cannot remove MISRA warning. */
#define PDUR_BASE_RPTBL(s)        (PduR_FunctionPtrs->s)

/**
 * @ingroup PDUR_H
 *
 * PduR_GF_IFTx: Access to gwToLoMc configuration  \n
 */
#define PDUR_GW_MC_TX_BASE      PDUR_BASE(gwToLoMc)      /* Gateway multicast (If) */

/**
 * @ingroup PDUR_H
 *
 * Gateway multicast If: Access to Gateway multicast If(loIfTxToUpMc) configuration  \n
 */
#define PDUR_LOIF_TX_MC_BASE    PDUR_BASE(loIfTxToUpMc)  /* Gateway multicast If */
/**
 * @ingroup PDUR_H
 *
 * PduR_<Lo>TpCopyTxData, PduR_<Lo>TpTxConfirmation: multicast table \n
 */
#define PDUR_LOTP_TX_MC_BASE    PDUR_BASE(loTpTxToUpMc)  /* PduR_<Lo>TpCopyTxData, PduR_<Lo>TpTxConfirmation: multicast table */
/**
 * @ingroup PDUR_H
 *
 * PduR_<Lo>TpCopyTxData, PduR_<Lo>TpTxConfirmation: multicast state\n
 */
#define PDUR_LOTP_TX_STATE_BASE PDUR_BASE(loTpTxToUpMs)  /* PduR_<Lo>TpCopyTxData, PduR_<Lo>TpTxConfirmation: multicast state */
/**
 * @ingroup PDUR_H
 *
 * PduR_GF_If_RxIndication: Access to Gateway Interface Rx Indication configuration  \n
 */
#define PDUR_GW_IF_TX_BASE      PDUR_BASE(gwIfTx)        /* PduR_GF_If_RxIndication */
/**
 * @ingroup PDUR_H
 *
 * IF Gateway transmission support\n
 */
#define PDUR_GW_IF_BASE         PDUR_BASE(gwIf)          /* IF Gateway transmission support */
/**
 * @ingroup PDUR_H
 *
 * TP Gateway transmission support\n
 */
#define PDUR_GW_TP_BASE         PDUR_BASE(gwTp)          /* TP Gateway transmission support */

#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
/**
 * @ingroup PDUR_H
 *
 * Routing Path Group support\n
 */
#define PDUR_RPG_CONFIG_INFO    PDUR_BASE(rpg_ConfigInfo)       /* RPG Support */

/**
 * @ingroup PDUR_H
 *
 * Enable\Disable Routing Path depending on RPG config\n
 */
#define PDUR_RPG_ENROUTING_INFO(index)  PduR_Base->pduR_Rpg_Status[index]    /* RPG Support */
#endif /*#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)*/

/**
 * @ingroup PDUR_H
 *
 * Change Parameter Support\n
 */
#define PDUR_CHANGEPARAM_SUPPORT PDUR_BASE(DcmRxToLoTp)    /* Change Parameter Support */
/**
 * @ingroup PDUR_H
 *
 * Valid No. Of Entries\n
 */
#define PDUR_NR_VALID_IDS(rt)   PDUR_BASE(rt##_NrEntries)

#if (PDUR_CONFIGURATION_VARIANT != PDUR_VARIANT_PRE_COMPILE)
/**
 * @ingroup PDUR_H
 *
 * Access macro to get max RPG Id when post build variant is selected
 */
#define PDUR_GET_RPGID_MAX     (PduR_Base->rpg_NrEntries)
#else
/**
 * @ingroup PDUR_H
 *
 * Access macro to get max RPG Id when pre-compile variant is selected
 */
#if defined(PDUR_MODE_DEPENDENT_ROUTING) && (PDUR_MODE_DEPENDENT_ROUTING != 0)
#define PDUR_GET_RPGID_MAX     (PDUR_RPGID_MAX)
#endif
#endif

/**
 * @ingroup PDUR_PRV_H
 *
 * FIFO routines
 */
#define PDUR_FIFO_INC_AND_WRAP(fifo, val)                         \
   do {                                                           \
      (val) = (val) + (fifo)->eltSize;                              \
      if ((val) >= ((fifo)->begin + ((fifo)->eltSize * (fifo)->nrElts))) {  \
         (val) = (fifo)->begin;                                     \
      }                                                           \
   } while (0)


/* Section code start
*/
#define PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"
/* ------------------------------------------------------------------------ */
/**
 * @ingroup PDUR_H
 *
 * State information \n
 */
extern VAR( PduR_StateType, PDUR_VAR ) PduR_State;

/* ------------------------------------------------------------------------ */
/* End the set of variable definitions */

 /**
  * @ingroup PDUR_H
  *
  * Section code stop
  */
#define PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "PduR_MemMap.h"

 /* ------------------------------------------------------------------------ */
 /* Error detection functions */


 #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)    
  /**
   * @ingroup PDUR_H
   *
   * If any developemnt error is reported, and DevErrorDetect switch is set to off, the below macro points to NULL_PTR
   */
  #define PDUR_DET_API(name)                      (NULL_PTR)
 #else
  /**
   * @ingroup PDUR_H
   *
   *  If any developemnt error is reported, and DevErrorDetect switch is set to off, the below macro points to actual API
   */
  #define PDUR_DET_API(name)                      (name)
 #endif /* PDUR_DEV_ERROR_DETECT */

 /**
 * @ingroup PDUR_PRV_H
 *
 *  This function is to Initialize a multicast state variable to default value. \n
 *
 *  @param  In:      state - This parameter is used to identify the state of multicast state variable. \n
 *
 *  @return None \n
 */
 extern FUNC( void, PDUR_CODE ) PduR_iInit_multicast(P2VAR( PduR_MS_LoTpTxToUp, AUTOMATIC, PDUR_VAR_NOINIT) state);

 /**
  * @ingroup PDUR_PRV_H
  *
  *  This function is to handle TxConfirmation for TP gatewaying, when a single entry buffer
  *  decrements the lock pointer counter for destination PDUs \n
  *
  *  @param  In:      layer - This parameter is used to indicate the PduR layer. \n
  *  @param  In:      gwId  - This parameter is used to indicate the gateway ID. \n
  *  @param  In:      result- This parameter is used to notify the result. \n
  *
  *  @return None \n
  */

 extern FUNC( void, PDUR_CODE ) PduR_GF_Tp_Buf_TxConfirmation( VAR(PduR_LayerType,AUTOMATIC) layer,
                                                               VAR(PduIdType,AUTOMATIC) gwId,
                                                               VAR(Std_ReturnType,AUTOMATIC) result );
 /**
  * @ingroup PDUR_PRV_H
  *
  *  PduR_GF_Tp_FIFO_TxConfirmation is used to handle TxConfirmation for TP gatewaying, when a FIFO is being used \n
  *
  *  @param  In:      layer - This parameter is used to indicate the PduR layer \n
  *  @param  In:      gwId  - This parameter is used to indicate the gateway ID \n
  *  @param  In:      result- This parameter is used to notify the result \n
  *
  *  @return None \n
  */
 extern FUNC( void, PDUR_CODE ) PduR_GF_Tp_FIFO_TxConfirmation( VAR(PduR_LayerType, AUTOMATIC) layer,
                                                                VAR(PduIdType, AUTOMATIC) gwId,
                                                                VAR(Std_ReturnType, AUTOMATIC) result);

 /* ------------------------------------------------------------------------ */
 /* PduR_Init */

  /**
   * @ingroup PDUR_H
   * This API initializes the PDU Router.\n
   *
   * @param in         ConfigPtr :    Pointer to post build configuration.\n
   *
   * @return None \n
   */
 extern FUNC( void, PDUR_CODE ) PduR_iInit( P2CONST( PduR_ConfigType, AUTOMATIC, PDUR_APPL_CONST ) ConfigPtr );

 #if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)
 /**
  * @ingroup PDUR_H
  * This API initializes the PDU Router.\n
  *
  * @param in       ConfigPtr :   Pointer to post build configuration.\n
  *
  * @return None \n
  */
 extern FUNC( void, PDUR_CODE ) PduR_dInit( P2CONST( PduR_ConfigType, AUTOMATIC, PDUR_APPL_CONST ) ConfigPtr );

 /* ------------------------------------------------------------------------ */
 /**
  * @ingroup PDUR_H
  *
  * PduR_GetConfigurationId
  * */
 extern FUNC( uint16, PDUR_CODE ) PduR_dGetConfigurationId( void );
#endif/*if defined(PDUR_DEV_ERROR_DETECT) && (PDUR_DEV_ERROR_DETECT != STD_OFF)*/

 extern FUNC( uint16, PDUR_CODE ) PduR_iGetConfigurationId( void );

 /* ------------------------------------------------------------------------ */
 /**
  * @ingroup PDUR_H
  *      Null function to handle unwanted PduR_xxxIfTriggerTransmit
  *
  * @param in           Id      : ID of N-PDU that shall be received
  * @param in           data    : Data pointer for transmit buffer
  *
  * @return None \n
  */
 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_NF_TriggerTransmit_Func( VAR(PduIdType, AUTOMATIC ) id, P2VAR( PduInfoType, AUTOMATIC, PDUR_APPL_DATA ) data);

 /* Invalid PDU id handlers ------------------------------------------ */

 /**
  * @ingroup PDUR_H
  *     This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in        Id              :     ID of L-PDU that has been received.\n
  * @param in        bufferSizePtr   :     length identifies the overall number of bytes to be received.\n
  * @param out       ptr             :     Pointer to pointer to PduInfoStructure containing SDU data pointer and SDU length of a receive buffer.\n
  */
 extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyRxData( VAR(PduIdType, AUTOMATIC) id,
                                                                     P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr,
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);
 /**
  * @ingroup PDUR_H
  *     This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in        Id              :   ID of L-PDU that has been received.\n
  * @param in        TpSduLength     :   length identifies the overall number of bytes to be received.\n
  * @param in        bufferSizePtr   :   Pointer to pointer to PduInfoStructure containing SDU data pointer and SDU length of a receive buffer.\n
  */
 extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpStartOfReception(VAR(PduIdType, AUTOMATIC) id,
                                                                     VAR(PduLengthType, AUTOMATIC) TpSduLength,
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) bufferSizePtr);
 /**
  * @ingroup PDUR_H
  *           This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in       Id      :    ID of L-PDU that has been received.\n
  * @param in       result  :     Result of the TP reception.\n
  *
  * @return None \n
  */
 extern FUNC( void, PDUR_CODE )              PduR_invId_TpRxIndication( VAR(PduIdType, AUTOMATIC ) id,   \
                                                                        VAR(Std_ReturnType, AUTOMATIC) result);
 /**
  * @ingroup PDUR_H
  *      This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in        id          :ID of CAN N-PDU to be transmitted.\n
  *                  ptr         :Pointer to PduInfoStructure containing SDU data pointer and SDU length of a transmit buffer.\n
  *                  retry       :This parameter is used to retransmit data because problems occurred in transmitting it the last time.\n
  * @param out       availableDataPtr    :Indicates the remaining number of bytes that are available in the PduR Tx buffer.\n
  *
  */
 extern FUNC( BufReq_ReturnType, PDUR_CODE ) PduR_invId_TpCopyTxData( VAR(PduIdType, AUTOMATIC) id, \
                                                                     P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr, \
                                                                     P2VAR(RetryInfoType, TYPEDEF, PDUR_APPL_DATA) retry, \
                                                                     P2VAR(PduLengthType, TYPEDEF, PDUR_APPL_DATA) availableDataPtr );
 /**
  * @ingroup PDUR_H
  *      This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in        id            : ID of I-PDU to be transmitted.\n
  * @param in        result        : Result of the TP reception.\n
  *
  * @return None \n
  */
 extern FUNC( void, PDUR_CODE ) PduR_invId_TpTxConfirmation( VAR(PduIdType, AUTOMATIC ) id,      \
                                                             VAR(Std_ReturnType, AUTOMATIC) result);
 /**
  * @ingroup PDUR_H
  *       This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in         Id   : ID of L-PDU that has been received.\n
  *                   ptr  : Pointer to L-SDU (buffer of received payload).\n
  *
  * @return None \n
  */
 extern FUNC( void, PDUR_CODE ) PduR_invId_IfRxIndication( VAR(PduIdType, AUTOMATIC ) id,  \
                                                           P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr );
 /**
  * @ingroup PDUR_H
  *        This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in          id -  ID of FlexRay L-PDU that has been transmitted.
  *
  * @return None \n
  */
 extern FUNC( void, PDUR_CODE ) PduR_invId_IfTxConfirmation( VAR(PduIdType, AUTOMATIC ) id );

 /**
  * @ingroup PDUR_H
  *    This functions to be invoked when an invalid ID is encountered.\n
  *
  *
  * @param in        id      :   ID of L-PDU that is requested to be transmitted.\n
  *                  data    :   Pointer to place inside the transmit buffer of the L-PDU where data shall be copied to.\n
  */
 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_IfTriggerTransmit( VAR(PduIdType, AUTOMATIC ) id,  \
                                                              P2VAR( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) data );
 /**
  * @ingroup PDUR_H
  *      This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in         id     :   ID of I-PDU to be transmitted.\n
  *                   ptr    :   Pointer to pointer to PduInfoStructure containing SDU data pointer and SDU length of a transmit buffer.\n
  */
 extern FUNC( Std_ReturnType, PDUR_CODE )   PduR_invId_UpTransmit( VAR(PduIdType, AUTOMATIC ) id, \
                                                                   P2CONST( PduInfoType, TYPEDEF, PDUR_APPL_DATA ) ptr);
 /**
  * @ingroup PDUR_H
  *     This functions to be invoked when an invalid ID is encountered.\n
  *
  * @param in           id: ID of DCM I-PDU to be cancelled the transmission.\n
  */
 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpCancelTransmit( VAR(PduIdType, AUTOMATIC ) id);

 /**
 * @ingroup PDUR_H
 *     This functions to be invoked when an invalid ID is encountered.\n
 *
 * @param in           id: ID of UpTp I-PDU to be cancelled the reception.\n
 */
 extern FUNC( Std_ReturnType, PDUR_CODE ) PduR_invId_UpCancelReceive( VAR(PduIdType, AUTOMATIC ) id);

 /**
  * @ingroup PDUR_H
  *   The following extern declarations irrespective of whether the tables exist in the PduR_Cfg.c file.
  */

 /* ------------------------------------------------------------------------ */
 /* Begin section for extern constant */


#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"

 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upIfRxIndicationTable[]
  * */
 extern CONST(PduR_upIfRxIndicationFuncType, PDUR_CONST) PduR_upIfRxIndicationTable[];
 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upIfTxConfirmationTable[]
  * */
 extern CONST(PduR_upIfTxConfirmationFuncType, PDUR_CONST) PduR_upIfTxConfirmationTable[];
 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upTpCopyRxDataTable[]
  * */
 extern CONST(PduR_upTpCopyRxDataFuncType, PDUR_CONST) PduR_upTpCopyRxDataTable[];
 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upTpStartOfReceptionTable[]
  * */
 extern CONST(PduR_upTpStartOfReceptionFuncType, PDUR_CONST) PduR_upTpStartOfReceptionTable[];
 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upTpRxIndicationTable[]
  * */
 extern CONST(PduR_upTpRxIndicationFuncType, PDUR_CONST) PduR_upTpRxIndicationTable[];
 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upTpCopyTxDataTable[]
  * */
 extern CONST(PduR_upTpCopyTxDataFuncType, PDUR_CONST) PduR_upTpCopyTxDataTable[];
 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upTpTxConfirmationTable[]
  * */
 extern CONST(PduR_upTpTxConfirmationFuncType, PDUR_CONST) PduR_upTpTxConfirmationTable[];

 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_upIfTriggerTxTable[]
  * */
 extern CONST(PduR_upIfTriggerTxFuncType, PDUR_CONST) PduR_upIfTriggerTxTable[];

 /**
  * @ingroup PDUR_H
  * extern declaration of PduR_loTransmitTable[]
  * */
 extern CONST(PduR_loTransmitFuncType, PDUR_CONST) PduR_loTransmitTable[];

  /**
  * @ingroup PDUR_H
  * extern declaration of PduR_loCancelTransmitTable[]
  * */
 extern CONST(PduR_loCancelTransmitFuncType, PDUR_CONST) PduR_loCancelTransmitTable[];
 /**
 * @ingroup PDUR_H
 * extern declaration of PduR_loCancelRxTable[]
 * */
 extern CONST(PduR_loCancelReceiveFuncType, PDUR_CONST) PduR_loCancelRxTable[];

 /* ------------------------------------------------------------------------ */
 /* End section for extern constant */


#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "PduR_MemMap.h"


 /* ----------------------------------------------------------------------
  * Minimal routing support */ /**/

 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for CanIf
  */
 #define PDUR_MIN_ROUTING_CANIF_ENABLED (0x01)
 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for CanTp
  */
 #define PDUR_MIN_ROUTING_CANTP_ENABLED (0x02)
 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for CanIf
  */
 #define PDUR_MIN_ROUTING_FRIF_ENABLED  (0x04)
 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for FrTp
  */
 #define PDUR_MIN_ROUTING_FRTP_ENABLED  (0x08)
 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for LinIf
  */
 #define PDUR_MIN_ROUTING_LINIF_ENABLED (0x10)
 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for LinTp
  */
 #define PDUR_MIN_ROUTING_LINTP_ENABLED (0x20)
 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for Com
  */
 #define PDUR_MIN_ROUTING_COM_ENABLED   (0x40)
 /**
  * @ingroup PDUR_H
  * Macro for Minimum Routing for Dcm
  */
 #define PDUR_MIN_ROUTING_DCM_ENABLED   (0x80)



 /*
  * These macros will be used to implement each PDU router routing API (e.g. PduR_CanIfRxIndication())
  * if support for minimum routing is required.
  *
  * The marcos accept these arguments:
  *    srcLayer    The name of the source layer for this route, in the form CANIF, COM, FRTP, etc.
  *    fromUpOrLo  Either UP or LO, depending on whether the route begins at an upper layer or a lower layer.
  *    toUpOrLo    Either UP or LO, depending on whether the route ends at an upper layer or a lower layer.
  *    txOrRx      Either TX or RX, depending on whether the PDU is being transmitted or received.
  *    operation   The API operation being performed expressed as one of:
  *                      TRANSMIT
  *                      PROVIDE_RX_BUFFER
  *                      PROVIDE_TX_BUFFER
  *                      TRIGGER_TRANSMIT
  *                      TP_RX_INDICATION
  *                      TP_TX_CONFIRMATION
  *                      IF_RX_INDICATION
  *                      IF_TX_CONFIRMATION
  *    fullRouteFn The name of the function which will perform the full routing, if minimum routing is not
  *                appropriate for the PDU.
  *    srcId       The source ID of the PDU.
  *
  * Once expanded, the macros will make use of these further macros, which will be defined in code generated
  * by the config tool. The values of these generated macros vary depending on whether minimum routing is
  * being configured at link-time or pre-build time:
  *
  *    #define PDUR_MIN_ROUTING_LINKTIME_CANIF   ( PduR_LConfig.minRoutingConfig.enabledLayers &
  *     PDUR_MIN_ROUTING_CANIF_ENABLED ) (link-time) or
  *    the literal value 1 or 0 depending on whether CanIf minimum routing is configured (pre-build)
  *    #define PDUR_MIN_ROUTING_LINKTIME_CANTP   similar to above
  *    #define PDUR_MIN_ROUTING_LINKTIME_FRIF    similar to above
  *    #define PDUR_MIN_ROUTING_LINKTIME_FRTP    similar to above
  *    #define PDUR_MIN_ROUTING_LINKTIME_LINIF   similar to above
  *    #define PDUR_MIN_ROUTING_LINKTIME_LINTP   similar to above
  *    #define PDUR_MIN_ROUTING_LINKTIME_COM     similar to above
  *    #define PDUR_MIN_ROUTING_LINKTIME_DCM     similar to above
  *
  *    #define PDUR_MIN_ROUTING_UP_RXPDUID       PduR_LConfig.minRoutingConfig.upRxPduId (link-time) or
  *                                              numeric value (pre-build)
  *    #define PDUR_MIN_ROUTING_LO_RXPDUID       similar to above
  *    #define PDUR_MIN_ROUTING_UP_TXPDUID       similar to above
  *    #define PDUR_MIN_ROUTING_LO_TXPDUID       similar to above
  *
  *    #define PDUR_MIN_ROUTING_LO_TRANSMIT            PduR_LConfig.minRoutingConfig.ptrLo_Transmit (link-time) or (e.g.)
  *                                                    CanIf_Transmit (pre-build)
  *    The following macro is fixed by its context: there is no variation
  *    #define PDUR_MIN_ROUTING_UP_PROVIDE_RX_BUFFER   Dcm_ProvideRxBuffer
  *    #define PDUR_MIN_ROUTING_UP_PROVIDE_TX_BUFFER   Dcm_CopyTxData      This macro is fixed by its context:
  *    #define PDUR_MIN_ROUTING_UP_TRIGGER_TRANSMIT    Com_TriggerTransmit      This macro is fixed by its context:
  *    #define PDUR_MIN_ROUTING_UP_TP_RX_INDICATION    Dcm_RxIndication         This macro is fixed by its context:
  *    #define PDUR_MIN_ROUTING_UP_TP_TX_CONFIRMATION  Dcm_TxConfirmation       This macro is fixed by its context:
  *    #define PDUR_MIN_ROUTING_UP_IF_RX_INDICATION    Com_RxIndication         This macro is fixed by its context:
  *    #define PDUR_MIN_ROUTING_UP_IF_TX_CONFIRMATION  Com_TxConfirmation       This macro is fixed by its context:
  */
 #define PDUR_ROUTINGFN_0ARG( srcLayer, fromUpOrLo, toUpOrLo, txOrRx, operation, fullRouteFn, srcId )  \
    /* Is srcId to be routed via minimum routing? */                                 \
    ( ( ( PDUR_MIN_ROUTING_LINKTIME_ ## srcLayer ) &&                         \
    ( (srcId) == PDUR_MIN_ROUTING_ ## fromUpOrLo ## _ ## txOrRx ## PDUID ) ) ?   \
       /* Route the PDU via minimum routing. */                                                        \
       ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## operation ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## txOrRx ## PDUID ) ) :  \
       /* Route the PDU via full routing. */                                                          \
       /* MR12 RULE 20.7 VIOLATION: The Type Conversion is Required */                                                          \
      ( fullRouteFn( (srcId) ) )                                                                         \
    )

 #define PDUR_ROUTINGFN_1ARG( srcLayer, fromUpOrLo, toUpOrLo, txOrRx, operation, fullRouteFn, srcId, arg1 )  \
    /* Is srcId to be routed via minimum routing? */                                       \
   ( ( ( PDUR_MIN_ROUTING_LINKTIME_ ## srcLayer ) &&                         \
   ( (srcId) == PDUR_MIN_ROUTING_ ## fromUpOrLo ## _ ## txOrRx ## PDUID ) ) ?   \
       /* Route the PDU via minimum routing. */                                                              \
   ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## operation ( PDUR_MIN_ROUTING_ ## toUpOrLo ## _ ## txOrRx ## PDUID, arg1 ) ): \
       /* Route the PDU via full routing. */                                                           \
       /* MR12 RULE 20.7 VIOLATION: The Type Conversion is Required */                                                                \
      ( fullRouteFn( (srcId), (arg1) ) )                                                                         \
    )

 #define PDUR_ROUTINGFN_2ARG( srcLayer, fromUpOrLo, toUpOrLo, txOrRx, operation, fullRouteFn, srcId, arg1, arg2 )  \
    /* Is srcId to be routed via minimum routing? */                                           \
    ( ( ( PDUR_MIN_ROUTING_LINKTIME_ ## srcLayer ) && ( (srcId) == PDUR_MIN_ROUTING_##fromUpOrLo## _ ##txOrRx## PDUID)) ? \
       /* Route the PDU via minimum routing. */                                                                    \
   (PDUR_MIN_ROUTING_ ##toUpOrLo##_##operation( PDUR_MIN_ROUTING_ ##toUpOrLo ## _ ## txOrRx ## PDUID, arg1, arg2 ) ) : \
       /* Route the PDU via full routing. */                                                          \
       /* MR12 RULE 20.7 VIOLATION: The Type Conversion is Required */                                                                      \
      ( fullRouteFn( (srcId), (arg1), (arg2) ) )                                                                          \
    )
/* Internal APIs & Interfaces required for COM module */
extern FUNC( void, PDUR_CODE ) PduRAppl_IncompatibleGenerator(void);

/* Flags */

/* These flags share a byte with the count of the number of lower layers which we are gatewaying
 * to, therefore they should have large values. */
/**
 * @ingroup PDUR_PRV_H
 *
 * This flag share a byte with the count of the number of lower layers which we are gatewaying
 * to, therefore they should have large values. This is used for the need of Tx \n
 */
#define PDUR_GW_TP_NEED_TX    ((uint8)0x40)
/**
 * @ingroup PDUR_PRV_H
 *
 * This flag share a byte with the count of the number of lower layers which we are gatewaying
 * to, therefore they should have large values. This is used when transmit is called \n
 */
#define PDUR_GW_TP_TX_CALLED  ((uint8)0x20)
/**
 * @ingroup PDUR_PRV_H
 *
 * This flag share a byte with the count of the number of lower layers which we are gatewaying
 * to, therefore they should have large values. This is used when transmit is failed \n
 */
#define PDUR_GW_TP_TX_FAILED  ((uint8)0x80)

#endif /* PDUR_PRIV_H */

