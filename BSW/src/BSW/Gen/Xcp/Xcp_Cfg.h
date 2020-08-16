
/*<VersionHead>
****************************************************************************************************
* This Configuration File is generated using versions (automatically filled in) as listed below.
*
* $Generator__: Xcp / AR42.4.0.1                 Module Package Version
* $Editor_____: 9.0             Tool Version
****************************************************************************************************
</VersionHead>*/

#ifndef  XCP_CFG_H
#define  XCP_CFG_H

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Symbolic_Names_Cfg.h"  /* For symbolic values */

/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/

/* Software Version Information */
#define XCP_SW_MAJOR_VERSION                      4u
#define XCP_SW_MINOR_VERSION                      0u
#define XCP_SW_PATCH_VERSION                      1u

#define XCP_VENDOR_ID                             6u
#define XCP_MODULE_ID                             212u
#define XCP_INSTANCE_ID                           0u

/* AUTOSAR Specification Version */
#define XCP_AR_RELEASE_MAJOR_VERSION              4u
#define XCP_AR_RELEASE_MINOR_VERSION              2u
#define XCP_AR_RELEASE_REVISION_VERSION           2u

/* ASAM Specification Version */
#define XCP_ASAM_MAJOR_VERSION                    1u            /**< Major Version of the ASAM standard that is implemented */
#define XCP_ASAM_MINOR_VERSION                    2u            /**< Minor Version of the ASAM standard that is implemented */

/* Transport Layers */
#define XCP_ON_CAN_ENABLED                        STD_ON        /**< Switch to En/Disable the transport layer CAN (XcpOnCan) */
#define XCP_ON_ETHERNET_ENABLED                   STD_OFF       /**< Switch to En/Disable the transport layer Eth (XcpOnEth) */
#define XCP_ON_FLEXRAY_ENABLED                    STD_OFF       /**< Switch to En/Disable the transport layer Flexray (XcpOnFr) */
#define XCP_CAN_DIRECT_TRANSMIT                   STD_OFF       /**< Switch to En/Disable the CAN complex device driver for CAN Direct Transmit */
#define XCP_TL_TRANSMIT_BUFFER                    STD_OFF       /**< Switch to En/Disable buffering in Transport Layer */
#define XCP_CONNECT_TRANSPORT_LAYER_CALLOUT       STD_OFF       /**< Switch to En/Disable the call of user function XcpAppl_ConnectTransportLayer() */

/* Resource parameter (Main XCP-Features) */
#define XCP_CALIBRATION_CAL                       STD_ON        /**< Calibration (CAL) Resource */
#define XCP_PAGE_SWITCHING_PAG                    STD_OFF       /**< Paging (PAG) Resource */
#define XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ      STD_ON        /**< Synchronous Data Acquisition (DAQ) Resource */
#define XCP_SYNCHRONOUS_DATA_STIMULATION_STIM     STD_OFF       /**< Synchronous Data Stimulation (STIM) Resource */
#define XCP_FLASH_PROGRAMMING                     STD_OFF       /**< Flash Programming (PGM) Resource */

#define XCP_RESOURCE_ENABLED                      (XCP_RESOURCE_NONE \
                                                  | XCP_RESOURCE_CALPAG \
                                                  | XCP_RESOURCE_DAQ \
                                                  | XCP_RESOURCE_NONE)  /**< Complete Resource parameter depending on configuration */

/* Synchronous Data Acquisition (DAQ) */
#define XCP_EDRAM_CONFIGURED                      STD_OFF
#define XCP_MAX_DAQRAMSECTIONS                    1u
#define XCP_DAQRAM_LIMIT                          8192u         /**< Total memory for DAQ configuration for ALL protocol layers */
#define XCP_DAQRAM_LIMIT_ED                       0u         /**< Total memory for DAQ configuration for ALL protocol layers in ED-RAM */

#define XCP_DAQRAM_SHIFTING                       STD_OFF       /**< Switch to En/Disable the shifting of dynamic DAQ memory */

#define XCP_OM_ODT_OPTIMIZATION_ENABLED           STD_OFF       /**< ODT copy-routine optimization enabled? */
#define XCP_OM_ODT_OPTIMIZATION_ERR_REACTION      XCP_OM_ODT_OPTIMIZATION_ERR_FALLBACK_TO_OM_DEFAULT /**< Error reaction for the optimized copy-routine */

#define XCP_TIMESTAMP                             STD_ON        /**< Switch to En/Disable the support for timestamps */
#define XCP_TIMESTAMP_TICKS                       1u            /**< Xcp TimeStamp Ticks */
#define XCP_TIMESTAMP_UNIT                        1000000000u      /**< Xcp TimeStamp Units */
#define XCP_TIMESTAMP_MODE_UNIT                   6u            /**< Xcp TimeStamp Mode Unit */

#define XCP_DAQ_SIZE                              24u           /**< Size of a  DAQ-Structure */
#define XCP_ODT_SIZE                              6u            /**< Size of an ODT-Structure */
#define XCP_ODT_ENTRY_SIZE                        5u            /**< Size of an OdtEntry-Structure */
#define XCP_ODT_DAQ_BUFFER_ELEMENT_SIZE           2.0f          /**< Factor for the calculation of the DAQ-Queue-Size */
#define XCP_ODT_STIM_BUFFER_ELEMENT_SIZE          0u            /**< Factor for the calculation of the STIM-Queue-Size */

#define XCP_COMMAND_GET_DAQ_LIST_MODE             STD_OFF       /**< Switch to En/Disable the command GET_DAQ_LIST_MODE which returns the information on the current mode of the specified DAQ list */
#define XCP_COMMAND_READ_DAQ                      STD_ON        /**< Switch to En/Disable command READ_DAQ which reads one ODT entry of a DAQ list defined by the DAQ list pointer */
#define XCP_COMMANDS_GET_DAQ_INFO                 STD_ON        /**< Switch to En/Disable the commands GetDaqProcessorInfo, GetDaqResolutionInfo, GetDaqEventInfo */

#define XCP_MAX_DAQ                               0xFFFFu       /**< Maximum number of allowed DAQs */
#define XCP_MAX_ODT                               0xFFFFu       /**< Maximum number of allowed ODTs */
#define XCP_MAX_ODTENTRY                          0xFFFFu       /**< Maximum number of allowed OdtEntries */
#define XCP_MAX_EVENT_CHANNEL                     5u            /**< Maximum number of available event channels */

#define XCP_DAQ_OVERLOAD_INDICATION_PID_ENABLED   STD_OFF       /**< Switch to En/Disable the support for overload indication type PID  */
#define XCP_DAQ_OVERLOAD_DEBUG_EVENT              STD_OFF       /**< Switch to En/Disable Debug Overload Event: DAQ List Number inside event message, not ASAM compliant */
#define XCP_IDFIELD_OTHER_THAN_ABSOLUTE           STD_OFF       /**< Switch to En/Disable the support of other ID Field Types than XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE */

/* Synchronous Data Stimulation (STIM) */
#define XCP_EV_STIM_TIMEOUT_ENABLED               STD_OFF       /**< Switch to En/Disable the Event Stim Timeout */

/* Calibration (CAL) */
#define XCP_COMMAND_MODIFY_BITS                   STD_ON        /**< Switch to En/Disable the command MODIFY_BITS which allows to modify bits in an atomic way*/

/* Page Switching (PAG) */
#define XCP_COMMANDS_GET_PAG_INFO                 STD_OFF       /**< Switch to En/Disable the commands GetPagProcessorInfo, GetPageInfo, GetSegmentInfo */

/* Resume Mode */
#define XCP_RESUME_MODE                           STD_OFF       /**< Switch to En/Disable the Resume Mode */

/* Block Transfer */
#define XCP_BLOCK_TRANSFER_UPLOAD                 STD_ON        /**< Switch to En/Disable the ASAM XCP feature SLAVE_BLOCK_MODE (block transfer from slave to master) */
#define XCP_BLOCK_TRANSFER_DOWNLOAD               STD_ON        /**< Switch to En/Disable the ASAM XCP feature MASTER_BLOCK_MODE (block transfer from master to slave) */
#define XCP_BLOCK_TRANSFER_MAX_BS                 255u          /**< Maximum number of bytes for block transfer */
#define XCP_BLOCK_TRANSFER_MIN_ST                 0u            /**< minimum separation time */

/* Optional Standard Commands */
#define XCP_COMMAND_GET_COMM_MODE_INFO            STD_OFF       /**< Switch to En/Disable the command GetCommModeInfo to get supported communication information */
#define XCP_COMMAND_GET_ID                        STD_OFF       /**< Switch to En/Disable the command GET_ID to get the Identification from slave */
#define XCP_COMMAND_USER_CMD                      STD_OFF       /**< Switch to En/Disable the User Defined Command USER_CMD */

/* Seed And Key */
#define XCP_SEED_AND_KEY                          STD_ON        /**< Switch to En/Disable the Seed and Key mechanism */

/* Checksum */
#define XCP_COMMAND_CHECKSUM                      STD_ON         /**< Switch to En/Disable Checksum commands */
#define XCP_CHECKSUM_MAX_BLOCK_SIZE               0xFFFFFFFFu   /**< Maximum block size for Checksum */
#define XCP_MTA_BLOCK_SIZE_ALIGN                  1u            /**< Checksum Mta BlockSize Alignment */

/* Read/Write access */
#define XCP_MEMORY_READ_PROTECTION                STD_ON        /**< Switch to En/Disable the protection for reading memory (XcpAppl_MemoryReadProtection()) */
#define XCP_MEMORY_WRITE_PROTECTION               STD_ON        /**< Switch to En/Disable the protection for writing memory (XcpAppl_MemoryWriteProtection()) */
#define XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL STD_ON        /**< If enabled the Memory access shall be done by application (XcpAppl_MemRead(), XcpAppl_MemWrite()) */
#define XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL        STD_OFF       /**< If enabled the Memory access shall be done by application (XcpAppl_OdtEntryRead(), XcpAppl_OdtEntryWrite()) */
#define XCP_STATIC_ADDRESS_TRANSFORMATION         STD_OFF       /**< If enabled all address are initially passed to the function XcpAppl_StaticAddressTransformation to allow an address transformation before usage */

/* General */
#define XCP_PRODUCT_LINE                          XCP_PRODUCT_LINE_CSMOSAR   /**< Macro to specify the product line and enable the specific APIs */
#define XCP_CMD_RECEIVED_NOTIFICATION             STD_OFF       /**< Switch to En/Disable the call of user function XcpAppl_CmdReceived() */
#define XCP_DEV_ERROR_DETECT                      STD_ON        /**< Switch to En/Disable the development error detection (DET) */
#define XCP_VERSION_INFO_API                      STD_ON        /**< Switch to En/Disable the the VersionInfo-Api (Xcp_GetVersionInfo()) */
#define XCP_PL_IDS                                1u            /**< Number of protocol layer instances */
#define XCP_TL_IDS                                1u            /**< Number of transport layers  */
#define XCP_MAX_CTO                               8u           /**< Maximum number of bytes for data and command transmissions */
#define XCP_MAX_CTO_PGM                           XCP_MAX_CTO   /**< Macro to replace XCP_MAX_CTO_PGM with XCP_MAX_CTO */


/***************************    Obsolete   ********************************/
/**************************************************************************/
/*******       Event Channel number definition          *******************/
/**************************************************************************/
#define XCP_EVENT_CHANNEL_NUMBER_10MSRSTR            XcpConf_XcpEventChannel_XcpEventChannel_10ms
#define XCP_EVENT_CHANNEL_NUMBER_20MSRSTR            XcpConf_XcpEventChannel_XcpEventChannel_20ms
#define XCP_EVENT_CHANNEL_NUMBER_50MSRSTR            XcpConf_XcpEventChannel_XcpEventChannel_50ms
#define XCP_EVENT_CHANNEL_NUMBER_100MSRSTR            XcpConf_XcpEventChannel_XcpEventChannel_100ms
#define XCP_EVENT_CHANNEL_NUMBER_1SRSTR            XcpConf_XcpEventChannel_XcpEventChannel_1000ms

/***************************    Obsolete   ********************************/
/**************************************************************************/
/*******       Transport Layer Number definition        *******************/
/**************************************************************************/
#define XCP_TRANSPORT_LAYER_ID_XCPTRANSPORTLAYER            XcpConf_XcpTransportLayer_XcpTransportLayer


/***************************************************************************************************
* Type definitions
***************************************************************************************************/
/** const Protocol layer's configuration structure for different transport layers */
typedef struct
{
  Std_ReturnType  (*TLTransmit_pfct)          (const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId, Xcp_PduIdType XcpTxPduId);
  void            (*TLInit_pfct)              (uint8 XcpTransportLayerId, uint8 XcpInitStatus);
  void            (*TLConnect_pfct)           (uint8 XcpTransportLayerId);
  Std_ReturnType  (*TLDisconnect_pfct)        (uint8 XcpTransportLayerId);
  void            (*TLTransportLayerCmd_pfct) (const PduInfoType* XcpCmdPacketPtr, PduInfoType* XcpResPacketPtr, uint8 XcpTransportLayerId);
  Xcp_PduIdType   (*TLGetTxPduId_pfct)        (uint8 XcpPacketId, uint16 XcpEventChannelNumber, uint8 XcpTransportLayerId);
#if (XCP_RESUME_MODE == STD_ON)
  Xcp_ErrorCode   (*TLResumeModeData_pfct)    (Xcp_AdrPtr DaqRamPtr, Xcp_AdrPtrConst XcpDaqRamEndPtr, uint8 XcpTransportLayerId);
#endif
  uint8  MaxCto_u8;
  uint16 MaxDto_u16;
  Xcp_Timestamp_t TimestampType_en;
  Xcp_IdField_t   IdFieldType_en;
  Xcp_Overload_t  OverloadType_en;
  Xcp_OdtOptimizationType_t OdtOptimizationType_en;
  Xcp_Consistency_t Consistency_en;
  uint32 PdRam_u32;
  uint32 EdRam_u32;
}Xcp_PL_TL_Cfg_t;


/** DaqRam typedefs */
typedef enum
{
  XCP_RAMSECTION_INVALID = 0,
  XCP_RAMSECTION_PD = 1,
  XCP_RAMSECTION_ED = 2
}Xcp_RamSectionType_t;

typedef struct
{
  uint8*  DaqRamPtr_pu8;
  uint32  DaqRamTotalSize_u32;
  Xcp_RamSectionType_t RamSectionType_en;
}Xcp_DaqRamSection_Cfg_t;

/** Protocol layer's ram structure for different transport layers */
typedef struct{
  uint32  DaqRamFreeSize_u32;
  /* MR12 RULE 1.2 VIOLATION: Array is not used as flexible array member. The array length is well defined. */
  boolean PLConnected_ab[XCP_PL_IDS];
}Xcp_DaqRamSections_t;

#if (XCP_DAQRAM_SHIFTING == STD_ON)
typedef struct{
  uint32* source_pu32;
  uint32* destination_pu32;
  uint32  totalSize_u32;
  uint32  moveSize_u32;
  uint32  remainingSize_u32;
  Xcp_Cto8_t XcpPacket;
}Xcp_DaqRamMove_t;
#endif

#if (XCP_RESUME_MODE == STD_ON)
/** Holds NvM Block identification and length used in Resume Mode ********************************/
typedef struct{
  NvM_BlockIdType  BlockId;   /**< NvM descriptor block ID */
  uint16  BlockLength;        /**< NvM descriptor block length */
}Xcp_NvMBlockInfo_t;
#endif

#if (XCP_COMMANDS_GET_DAQ_INFO == STD_ON)
/* Event channel typedefs */
typedef struct
{
 uint8 EventChannelDirection_u8;
 uint8 EventChannelTimeCycle_u8;
 uint8 EventChannelTimeUnit_u8;
 uint8 EventChannelPriority_u8;
}Xcp_EventChannel_Cfg_t;
#endif

/** Const configuration for protocol layer *******************************************************/
typedef struct
{
  /* MR12 RULE 1.2 VIOLATION: Array is not used as flexible array member. The array length is well defined. 
                              This violation is raised only when: XCP_COMMANDS_GET_DAQ_INFO == STD_OFF and XCP_RESUME_MODE == STD_OFF 
                                                                  and XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_OFF and XCP_TL_IDS == 1*/
  Xcp_PL_TL_Cfg_t          TlCfg[XCP_TL_IDS];                        /**< Transport layer config */
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  /* MR12 RULE 1.2 VIOLATION: Array is not used as flexible array member. The array length is well defined. 
                              This violation is raised only when: XCP_COMMANDS_GET_DAQ_INFO == STD_OFF and XCP_RESUME_MODE == STD_OFF and XCP_MAX_DAQRAMSECTIONS == 1 */
  Xcp_DaqRamSection_Cfg_t  DaqRamCfg[XCP_MAX_DAQRAMSECTIONS];        /**< DaqRam config          */
#endif
#if (XCP_RESUME_MODE == STD_ON)
  Xcp_NvMBlockInfo_t      NvMBlockInfo[XCP_RESUME_MODE_NVM_BLOCK_COUNT]; /**< NvM Block identification and length used in Resume Mode */
#endif
#if (XCP_COMMANDS_GET_DAQ_INFO == STD_ON)
  /* MR12 RULE 1.2 VIOLATION: Array is not used as flexible array member. The array length is well defined. 
                              This violation is raised only when: XCP_MAX_EVENT_CHANNEL == 1 */
  Xcp_EventChannel_Cfg_t   EventChannelCfg[XCP_MAX_EVENT_CHANNEL];   /**< Event channel config   */
#endif
}Xcp_PlCfgConst_t;


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"

extern const Xcp_PlCfgConst_t Xcp_PlCfgConst;

extern const Xcp_ConfigType Xcp_Config;

#define XCP_STOP_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Function prototypes
***************************************************************************************************/
#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

extern void Xcp_EventChannel_10msRstr(void);
extern void Xcp_EventChannel_20msRstr(void);
extern void Xcp_EventChannel_50msRstr(void);
extern void Xcp_EventChannel_100msRstr(void);
extern void Xcp_EventChannel_1sRstr(void);

#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"


#endif   /* #ifndef XCP_CFG_H */

