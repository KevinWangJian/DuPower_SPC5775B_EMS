

#ifndef CANTP_CFG_H
#define CANTP_CFG_H


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

/* Defines */

/* TRACE[SWS_CanTp_00267] CanTp Module/Version Information */
#define CANTP_VENDOR_ID                     (6u)
#define CANTP_MODULE_ID                     (35u)
#define CANTP_INSTANCE_ID                   (0u)

#define CANTP_AR_RELEASE_MAJOR_VERSION      (4u)
#define CANTP_AR_RELEASE_MINOR_VERSION      (2u)
#define CANTP_AR_RELEASE_REVISION_VERSION   (2u)
#define CANTP_SW_MAJOR_VERSION              (3u)
#define CANTP_SW_MINOR_VERSION              (0u)
#define CANTP_SW_PATCH_VERSION              (0u)

#define CANTP_ON                            (1u)
#define CANTP_OFF                           (0u)
#define CANTP_DEV_ERROR_DETECT              CANTP_ON
#define CANTP_VERSION_INFO_API 				CANTP_ON
#define CANTP_READ_PARAMETER_API     	   	CANTP_OFF
#define CANTP_CHANGE_PARAMETER_API          CANTP_OFF
#define CANTP_TRIGGER_TRANSMIT_API          CANTP_OFF
#define CANTP_TX_BURST_MODE                 CANTP_OFF
#define CANTP_STRICT_BSCRTIMEOUT_CHECK      CANTP_OFF
#define CANTP_STRICTDLCCHECK				CANTP_OFF
#define CANTP_LEGACY_SHARED_FC_SUPPORT      CANTP_OFF
#define CANTP_FD_CALLOUT_SUPPORT            CANTP_OFF
#define CANTP_CANFD_SUPPORT                 CANTP_OFF
#define CANTP_SCHM_SUPPORT                  CANTP_ON
#define CANTP_FC_DISABLE_SUPPORT            CANTP_OFF
#define CANTP_CANTPLITE_SUPPORT             CANTP_OFF
#define CANTP_DYNAMIC_FC_SUPPORT            CANTP_ON
#define CANTP_CYCLE_COUNTER                 CANTP_ON
#define CanTp_FdCallOut                     
#define CANTP_PRE_COMPILE                   (0u)
#define CANTP_POST_BUILD_SELECTABLE         (1u)
#define CANTP_POST_BUILD_LOADABLE           (2u)
#define CANTP_VARIANT                       CANTP_PRE_COMPILE
#define CANTP_NO_OF_CANTPCONFIGSETS         (1u)
#define CANTP_BURST_QUEUE_SIZE              (1u)
#define CANTP_MAX_RX_CONNECTION_SIZE        (2u)
#define CANTP_MAX_TX_CONNECTION_SIZE        (1u)
#define CANTP_MAX_TX_NPDU_SIZE              (8u)
#define CANTP_MAX_CHANNEL_SIZE              (2u)
#define CANTP_MAX_NPDU_LENGTH               (8u)
#define CANTP_DEFAULT_STMIN_TICKS           (0u)
#define CANTP_INVALID_STMIN_TICKS           (14u)
#define CANTP_PADDING_BYTE                  (0x0u)


/* Symbolic names for PduR */

/* To be used as CanTpTxSduId in CanTp_Transmit and CanTp_CancelTransmit Api */

#define CanTpConf_CanTpTxNSdu_CanTpTxNSdu                                       ((PduIdType)0)

/* To be used as id in CanTp_ChangeParameter and CanTp_ReadParameter Api */

#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_Phys                                  ((PduIdType)0)
#define CanTpConf_CanTpRxNSdu_CanTpRxNSdu_Func                                  ((PduIdType)1)

/* Symbolic names for CanIf */

/* To be used as RxPduId in CanTp_RxIndication Api */

#define CanTpConf_CanTpRxNPdu_CanTpRxNPdu                                       ((PduIdType)0)
#define CanTpConf_CanTpRxNPdu_CanTpRxNPdu_0                                     ((PduIdType)1)

#define CanTpConf_CanTpRxFcNPdu_CanTpRxFcNPdu                                   ((PduIdType)1)

/* To be used as TxPduId in CanTp_TxConfirmation Api */

#define CanTpConf_CanTpTxNPdu_CanTpTxNPdu_0                                     ((PduIdType)0)

#define CanTpConf_CanTpTxFcNPdu_CanTpTxFcNPdu                                   ((PduIdType)0)

/* Forward incomplete declaration for EcuM */

struct CanTp_ConfigStructType;
typedef struct CanTp_ConfigStructType CanTp_ConfigType;

extern const CanTp_ConfigType CanTp_Config;

/* Function like Macro definitions */
#define CanTp_Cfg_DlcCheck(SduLength, ExpectedLength) (((SduLength) >= (ExpectedLength)) ? (E_OK) : (E_NOT_OK))
#define CanTp_Cfg_GetUsToTicks(Us)                    (((Us) * 100u)/1000000u)


#endif /* CANTP_CFG_H */
