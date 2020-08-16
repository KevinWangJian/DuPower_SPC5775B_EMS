
/*<VersionHead>
****************************************************************************************************
* This Configuration File is generated using versions (automatically filled in) as listed below.
*
* $Generator__: Xcp / AR42.4.0.1                 Module Package Version
* $Editor_____: 9.0             Tool Version
****************************************************************************************************
</VersionHead>*/

#ifndef  XCPONCAN_CFG_H
#define  XCPONCAN_CFG_H

/***************************************************************************************************
* Includes
***************************************************************************************************/


/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/
/* Common Transport Layer parameter */
#define XCP_CAN_NUMBER_OF_TRANSPORT_LAYERS    1u                            /**< Number of CAN channels */
#define XCP_CAN_TRANSPORT_LAYER_INDEX_OFFSET  0u                            /**< Index offset for CAN TransportLayer, because every Transport Layer Type indexes start from 0 */
#define XCP_CAN_NUMBER_OF_RX_PDUS             1u                            /**< Number of RxPdu for CAN Transport Layers */
#define XCP_CAN_NUMBER_OF_TX_PDUS             1u                           /**< Number of TxPdu for CAN Transport Layers */
#define XCP_CAN_TX_PDU_LEN_MAX                8u                            /**< Maximum length of Tx Pdus from different transport layers (for transmit buffer) */
#define XCP_CAN_FRAME_CONCATENATION           STD_OFF                       /**< Frame concatenation enabled or disabled */

#define XCP_CAN_TL_ONLY_ONE_TX_PDU            STD_ON                        /**< Flag if more than one TxPdu configured in every CAN TL */


/***************************************************************************************************
* Type definitions
***************************************************************************************************/
/** Structure for buffering CAN messages for transmission in XcpOnCan */
typedef struct
{
  PduIdType   CanIfTxPduId;                                             /**< CanIfTxPduId to send data */
  PduInfoType XcpPacket;                                                /**< Data packet to be sent */
  boolean     DataInBuffer_b;                                           /**< Flag if data inside is ready to be sent */
  boolean     Locked_b;                                                 /**< Flag if buffer is used - filled in */
  uint8       DataBuffer_au8[XCP_CAN_TX_PDU_LEN_MAX];                   /**< Data buffer where the XcpPacket->DataPtr will be addressed */
}Xcp_CanTxBuffer_t;

/** Configuration structure for TxPdu for TransportLayer*/
typedef struct
{
  PduIdType         CanIfTxPduId;                                       /**< CanIfTxPduId */
  uint16            EventChannelNr_u16;                                 /**< Event Channel Number (valid only for FrameType=DAQ) */
}Xcp_CanPduCfgConst_t;

/** Configuration structure for CAN channels */
typedef struct
{
  uint8 TxPduCfgOffset_u8;                                              /**< Offset where this CAN transport layer starts in TxPduConfigTable table */
  uint8 TxPduCfgCount_u8;                                               /**< Number of elements of this CAN transport layer in TxPduConfigTable table */
#if (XCP_DEV_ERROR_DETECT == STD_ON)
  uint8   Max_Cto_u8;                                                   /**< MAX_CTO - Maximum length of command packet */
  uint16  Max_Dto_u16;                                                  /**< MAX_DTO - Maximum length of data packet */
#endif
}Xcp_CanTlCfgConst_t;

/** Configuration structure for CAN Transport Layer */
typedef struct
{
  Xcp_CanTlCfgConst_t   CanTlCfg[XCP_CAN_NUMBER_OF_TRANSPORT_LAYERS];   /**< Configuration table for CAN channels */
  Xcp_CanPduCfgConst_t  CanTxPduCfg[XCP_CAN_NUMBER_OF_TX_PDUS];         /**< Configuration table for TxPdus */
  uint8                 RxPduId2TlId_u8[XCP_CAN_NUMBER_OF_RX_PDUS];     /**< Routing table where index is RxPduId and value is corresponding TransportLayerId from global table */
  uint8                 TxPduId2TlId_u8[XCP_CAN_NUMBER_OF_TX_PDUS];     /**< Routing table where index is TxPduId and value is corresponding TransportLayerId from global table  */
}Xcp_CanCfgConst_t;


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"

/** Main CAN Transport Layer configuration structure */
extern const Xcp_CanCfgConst_t Xcp_CanCfgConst;

#define XCP_STOP_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#if (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON)
/** Table for buffering CAN messages for transmission for every CAN transport layer */
extern Xcp_CanTxBuffer_t Xcp_CanTxBuffer[XCP_CAN_NUMBER_OF_TRANSPORT_LAYERS];
#endif /* (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON) */

#define XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

/***************************************************************************************************
* Function prototypes
***************************************************************************************************/


#endif   /* #ifndef XCPONCAN_CFG_H */

