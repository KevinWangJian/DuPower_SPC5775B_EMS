
/*<VersionHead>
****************************************************************************************************
* This Configuration File is generated using versions (automatically filled in) as listed below.
*
* $Generator__: Xcp / AR42.4.0.1                 Module Package Version
* $Editor_____: 9.0             Tool Version
****************************************************************************************************
</VersionHead>*/

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "XcpOnCan_Cfg.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#if (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON)
/** Table for buffering CAN messages for transmission for every CAN transport layer */
Xcp_CanTxBuffer_t Xcp_CanTxBuffer[XCP_CAN_NUMBER_OF_TRANSPORT_LAYERS];
#endif /* (XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON) */

#define XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"

const Xcp_CanCfgConst_t Xcp_CanCfgConst =
{
  /* ------------------------ TransportLayerCanConfig - Configuration table for CAN channels ----------------------------------------------------------------------------------------- */
  {
    {
       0u  /* Offset where this CAN transport layer starts in TxPduConfigTable table */
      ,1u  /* Number of elements of this CAN transport layer in TxPduConfigTable table */
#if (XCP_DEV_ERROR_DETECT == STD_ON)
      ,8u  /* MAX_CTO - Maximum length of command packet */
      ,8u  /* MAX_DTO - Maximum length of data packet */
#endif
    }
  },

  /* ------------------------ TxPduConfigTable - Configuration table for TxPdus ------------------------------------------------------------------------------------------------------ */
  {
    {
      22u,  /* Tx PduId */
      XCP_EVENT_CHANNEL_NOT_USED  /* Event Channel Number */
    }
  },

  /* ------------------------ RxPduId2TransportLayerId - Routing table where index is RxPduId and value is corresponding TransportLayerId used by RxIndication ----------------------- */
  {
    0u   /* TranportLayerId */
  },

  /* ------------------------ TxPduId2TransportLayerId - Routing table where index is TxPduId and value is corresponding TransportLayerId used by TxConfirmation --------------------- */
  {
    0u   /* TranportLayerId */
  }
};

#define XCP_STOP_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"

/***************************************************************************************************
* Functions
***************************************************************************************************/


