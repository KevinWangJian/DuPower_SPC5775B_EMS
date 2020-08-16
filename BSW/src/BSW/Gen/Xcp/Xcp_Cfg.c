
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
#include "Xcp_Priv.h"

#if ((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_EDRAM_CONFIGURED == STD_ON))
# include "rba_Memlay.h" /* for ED RAM #define RBA_MEMLAY_EDRAM_START */
#endif


/***************************************************************************************************
* Variables
***************************************************************************************************/

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
# if (XCP_DAQRAM_LIMIT > 0u)
#  define XCP_START_SEC_VAR_DAQRAM_POWER_ON_CLEARED_32
#  include "Xcp_MemMap.h"
static uint32 Xcp_PLDaqRam_au32[XCP_DAQRAM_LIMIT/4u];         /** DAQ RAM Production Device Memory */
#  define XCP_STOP_SEC_VAR_DAQRAM_POWER_ON_CLEARED_32
#  include "Xcp_MemMap.h"
# endif

# if (XCP_DAQRAM_LIMIT_ED > 0u)
#  ifdef RBA_MEMLAY_EDRAM_START
#   define XCP_START_SEC_VAR_DAQRAM_ED_POWER_ON_CLEARED_32
#   include "Xcp_MemMap.h"
static uint32 Xcp_PLDaqRamEd_au32[XCP_DAQRAM_LIMIT_ED/4u];    /** DAQ RAM Emulation Device Memory */
#   define XCP_STOP_SEC_VAR_DAQRAM_ED_POWER_ON_CLEARED_32
#   include "Xcp_MemMap.h"
#  endif
# endif
#endif

/************************ START CONST UNSPECIFIED ***********************************/
#define XCP_START_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"

const Xcp_PlCfgConst_t Xcp_PlCfgConst =
{
  /* START Xcp_PL_TL_Cfg_t         TlCfg[XCP_TL_IDS] */
  {
    {
      /* XcpTransportLayer */
      (Std_ReturnType (*) (const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId, Xcp_PduIdType XcpTxPduId))         (&Xcp_CanTransmit),           /**< TL transmit function */
      (void           (*) (uint8 XcpTransportLayerId, uint8 XcpInitStatus))                                               (&Xcp_CanInit),               /**< TL init function */
      (void           (*) (uint8 XcpTransportLayerId))                                                                    (&Xcp_CanConnect),            /**< TL connect function */
      (Std_ReturnType (*) (uint8 XcpTransportLayerId))                                                                    (&Xcp_CanDisconnect),         /**< TL disconnect function */
      (void           (*) (const PduInfoType* XcpCmdPacketPtr, PduInfoType* XcpResPacketPtr, uint8 XcpTransportLayerId))  (&Xcp_CanTransportLayerCmd),  /**< TL Special Commands function */
      (Xcp_PduIdType  (*) (uint8 XcpPacketId, uint16 XcpEventChannelNumber, uint8 XcpTransportLayerId))                   (&Xcp_CanGetTxPduId),         /**< TL function to get the XcpTxPduId of TxPdus */
#if (XCP_RESUME_MODE == STD_ON)
      (Xcp_ErrorCode  (*) (Xcp_AdrPtr DaqRamPtr, Xcp_AdrPtrConst XcpDaqRamEndPtr, uint8 XcpTransportLayerId))             (&Xcp_CanResumeModeData),     /**< TL function to handle Resume Mode */
#endif
      8u, /**< TL Max CTO */
      8u, /**< TL Max DTO */
      XCP_TIMESTAMP_TYPE_TWO_BYTE, /**< TL Timestamp Type */
      XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE, /**< TL ID Field Type */
      XCP_DAQ_NO_OVERLOAD_INDICATION, /**< TL Overload Indication */
      XCP_ODT_OPTIMIZATION_OM_DEFAULT, /**< ODT-Optimization */
      XCP_CONSISTENCY_ODT, /**< CONSISTENCY */
      8192u,  /**< DAQ PD Memory */
      0u  /**< DAQ ED Memory */
    }
  /* END Xcp_PL_TL_Cfg_t         TlCfg[XCP_TL_IDS] */
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  },

  /* START Xcp_DaqRamSection_Cfg_t DaqRamCfg[XCP_MAX_DAQRAMSECTIONS] */
  {
# if (XCP_DAQRAM_LIMIT_ED > 0u)
    /* ED RAM */
    {
#  ifdef RBA_MEMLAY_EDRAM_START
      (uint8*) Xcp_PLDaqRamEd_au32,   /**< Pointer to ED RAM variable */
      XCP_DAQRAM_LIMIT_ED,            /**< DaqRamTotalSize_u32 */
      XCP_RAMSECTION_ED               /**< RAM Section */
#  else
      (uint8*) NULL_PTR,              /**< no ED RAM available */
      0u,                             /**< DaqRamTotalSize_u32 */
      XCP_RAMSECTION_INVALID          /**< RAM Section */
#  endif
#  if (XCP_DAQRAM_LIMIT > 0u)
    },
#  else
    }
#  endif
# endif

# if (XCP_DAQRAM_LIMIT > 0u)
    /* PD RAM */
    {
      (uint8*) Xcp_PLDaqRam_au32,     /**< Pointer to PD RAM variable */
      XCP_DAQRAM_LIMIT,               /**< DaqRamTotalSize_u32 */
      XCP_RAMSECTION_PD               /**< RAM Section */
    }
# endif
  /* END Xcp_DaqRamSection_Cfg_t DaqRamCfg[XCP_MAX_DAQRAMSECTIONS] */
# if (XCP_RESUME_MODE == STD_ON)
  },

  /* Start Xcp_NvMBlockInfo_t Xcp_NvMBlockInfo[XCP_RESUME_MODE_NVM_BLOCK_COUNT] */
  {
# endif
#endif
#if (XCP_COMMANDS_GET_DAQ_INFO == STD_ON)
  },

  /* START EventChannelCfg[XCP_MAX_EVENT_CHANNEL] */
  {
    { /* Event Channel 0: XcpEvent_10ms_Raster */
      XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_DAQ,   /**< Event channel direction    */
      1u,                                          /**< Event channel time cycle   */
      7u,                                          /**< Event channel time unit    */
      5u                                           /**< Event channel priority     */
    },
  
    { /* Event Channel 1: XcpEvent_20ms_Raster */
      XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_DAQ,   /**< Event channel direction    */
      2u,                                          /**< Event channel time cycle   */
      7u,                                          /**< Event channel time unit    */
      4u                                           /**< Event channel priority     */
    },
  
    { /* Event Channel 2: XcpEvent_50ms_Raster */
      XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_DAQ,   /**< Event channel direction    */
      5u,                                          /**< Event channel time cycle   */
      7u,                                          /**< Event channel time unit    */
      3u                                           /**< Event channel priority     */
    },
  
    { /* Event Channel 3: XcpEvent_100ms_Raster */
      XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_DAQ,   /**< Event channel direction    */
      10u,                                          /**< Event channel time cycle   */
      7u,                                          /**< Event channel time unit    */
      2u                                           /**< Event channel priority     */
    },
  
    { /* Event Channel 4: XcpEvent_1000ms_Raster */
      XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_DAQ,   /**< Event channel direction    */
      10u,                                          /**< Event channel time cycle   */
      8u,                                          /**< Event channel time unit    */
      1u                                           /**< Event channel priority     */
    }
  /* END EventChannelCfg[XCP_MAX_EVENT_CHANNEL] */
#endif
  }
};


/** Configuration variable for Xcp_Init */
const Xcp_ConfigType Xcp_Config = {0u};


#define XCP_STOP_SEC_CONST_UNSPECIFIED
#include "Xcp_MemMap.h"
/************************* STOP CONST UNSPECIFIED ***********************************/

/***************************************************************************************************
* Functions
***************************************************************************************************/
#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

/** \name Functions to trigger the specified EventChannel
 *  These can be used instead of the Xcp_EventChannel() function that needs an ID */
/** \{ */
/** Xcp_EventChannel_* is to be invoked by the respective OS task to enable XCP measurement/stimulation in this task. */
void Xcp_EventChannel_10msRstr(void) { (void) Xcp_EventChannel(0u); }
void Xcp_EventChannel_20msRstr(void) { (void) Xcp_EventChannel(1u); }
void Xcp_EventChannel_50msRstr(void) { (void) Xcp_EventChannel(2u); }
void Xcp_EventChannel_100msRstr(void) { (void) Xcp_EventChannel(3u); }
void Xcp_EventChannel_1sRstr(void) { (void) Xcp_EventChannel(4u); }
  
/** \} */

#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

