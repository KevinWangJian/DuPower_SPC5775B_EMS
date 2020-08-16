

#ifndef XCP_PRIV_H
#define XCP_PRIV_H

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cfg_SchM.h"
#include "Xcp_Cbk.h"

/* Errors during development will be reported to DET module */
#if (XCP_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif


#ifdef XCP_RUNTIME_MEASUREMENT_AVAILABLE
#include "Mcu.h"
#endif

/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/
/* Det makros */
#if (XCP_DEV_ERROR_DETECT == STD_ON)

  /** Macro for functions with return type as void */
  #define XCP_DET_REPORT_ERROR(CONDITION, API, ERROR)                                             \
    do                                                                                            \
    {                                                                                             \
      if (CONDITION)                                                                              \
      {                                                                                           \
        (void)Det_ReportError((XCP_MODULE_ID), (XCP_INSTANCE_ID), (uint8)(API), (uint8)(ERROR));  \
        return;                                                                                   \
      }                                                                                           \
    } while (0)

  /** Macro for functions with existing return value */
  #define XCP_DET_REPORT_ERROR_RET(CONDITION, API, ERROR, RETVAL)                                 \
  do                                                                                              \
  {                                                                                               \
    if (CONDITION)                                                                                \
    {                                                                                             \
      (void)Det_ReportError((XCP_MODULE_ID), (XCP_INSTANCE_ID), (uint8)(API), (uint8)(ERROR));    \
      return (RETVAL);                                                                            \
    }                                                                                             \
  } while (0)

  /** Macro for not returning from function (e.g. else paths) */
  #define XCP_DET_REPORT_ERROR_NO_RET(API, ERROR)                                                 \
    do                                                                                            \
    {                                                                                             \
      (void)Det_ReportError((XCP_MODULE_ID), (XCP_INSTANCE_ID), (uint8)(API), (uint8)(ERROR));    \
    } while (0)

  /** Macro for incrementing debug counters */
  #define XCP_DEBUG_CTR_INC(counter)    (counter)++

#else
  #define XCP_DET_REPORT_ERROR(CONDITION, API, ERROR)
  #define XCP_DET_REPORT_ERROR_RET(CONDITION, API, ERROR, RETVAL)
  #define XCP_DET_REPORT_ERROR_NO_RET(API, ERROR)
  #define XCP_DEBUG_CTR_INC(counter)
#endif

#ifndef XCP_RUNTIME_MEASUREMENT_AVAILABLE
  #define XCP_RTM_TIMETRACK_START()
  #define XCP_RTM_TIMETRACK_FINISH()
#else
  #define XCP_RTM_TIMETRACK_START() volatile uint32 Xcp_startTicks_u32 = Mcu_Rb_GetSysTicks();
  #define XCP_RTM_TIMETRACK_FINISH() volatile uint32 Xcp_stopTicks_u32 = MCU_RB_TIM0TICKS_TO_US(Mcu_Rb_GetSysTicks() - Xcp_startTicks_u32);
#endif

#define XCP_RTM(LOCKSTATUS)

/** \name Macro for byte alignment
 *  \{ */
#define XCP_4BYTE_ALIGN(var)      ((((var) + 3u) /4u) * 4u)
#define XCP_2BYTE_ALIGN(var)      ((((var) + 1u) /2u) * 2u)
/** \} */

/** \name Macro for min, max calculation and swapping
 *  \{ */
#define XCP_MIN(a, b)             (((a) < (b)) ? (a) : (b))
#define XCP_MAX(a, b)             (((a) > (b)) ? (a) : (b))
#define XCP_SWAP(a, b, temp)      do { (temp) = (a); (a) = (b); (b) = (temp); } while (0)
/** \} */

/** \name Macro for accessing global response buffer
 *  \{ */
#define XCP_RES_BUFFER_PTR(a)     Xcp_Cleared[a].ResBuffer.Buffer_au8
#define XCP_RES_BUFFER_LENGTH(a)  Xcp_Cleared[a].ResBuffer.Length_u32
/** \} */

/** \name Macro for accessing global event buffer
 *  \{ */
#define XCP_EV_BUFFER_PTR(a)      Xcp_Cleared[a].EvBuffer.Buffer_au8
#define XCP_EV_BUFFER_LENGTH(a)   Xcp_Cleared[a].EvBuffer.Length_u32
/** \} */

/** \name parameters required for calculating memory consumption
 *  \{ */
#define XCP_SIZEOF_DAQ            sizeof(Xcp_DaqList_t)
#define XCP_SIZEOF_ODT            sizeof(Xcp_Odt_t)
#define XCP_SIZEOF_ODT_ENTRY      5u
/** \} */

/** for dynamic DAQ config only */
#define XCP_ODT_COUNT_DAQ         0xFCu

/** Start value for Wait4TxConfCtr. Number of Xcp_MainFunction() calls until new transmit can be triggered without TxConfirmation. */
#define XCP_WAIT4TXCONFCTR        5

/** \name Optimized Copy-routines available for an ODT
 *  \{ */
#define XCP_ODT_COPY_UNKNOWN      0u
#define XCP_ODT_COPY_SAFE         1u
#define XCP_ODT_COPY_8            2u
#define XCP_ODT_COPY_16           3u
#define XCP_ODT_COPY_32           4u
#define XCP_ODT_COPY_64           5u
/** \} */


/*--------------------------------------------------------------------------------------------------
  Macros for accessing protocol layer variables
--------------------------------------------------------------------------------------------------*/

/** \name Xcp_Session_t
 *  \{ */
#define XCP_ACTIVE_TL_ID(a)                                 Xcp_NoInit[a].Session.ConnectedTlId_u8
#if (XCP_RESUME_MODE == STD_ON)
#define XCP_RESUME_SESSION_STATUS(a)                        Xcp_NoInit[a].Session.ResumeSessionStatus_u8
#else
#define XCP_RESUME_SESSION_STATUS(a)                        0u
#endif
#define XCP_MTA(a)                                          Xcp_NoInit[a].Session.Mta
#define XCP_MAXCTO(a)                                       Xcp_NoInit[a].Session.MaxCto_u8
#define XCP_MAXDTO(a)                                       Xcp_NoInit[a].Session.MaxDto_u16
#define XCP_MAXDTO_4ALIGNED(a)                              Xcp_NoInit[a].Session.MaxDto4Aligned_u16
/** \} */

/** \name Daq
 *  \{ */
#define XCP_DAQ(AbsDaqNum, protLayerId)                     (Xcp_NoInit[(protLayerId)].DaqConfig.DaqList_p[(AbsDaqNum)])
#define XCP_DAQ_ODTFIRST(AbsDaqNum, protLayerId)            (XCP_DAQ(AbsDaqNum, protLayerId).OdtFirst_u16)
#define XCP_DAQ_ODTCNT(AbsDaqNum, protLayerId)              (XCP_DAQ(AbsDaqNum, protLayerId).OdtCnt_u8)
#define XCP_DAQ_BUFFERINFO(AbsDaqNum, protLayerId)          (XCP_DAQ(AbsDaqNum, protLayerId).BufferInfo)
#define XCP_DAQ_MODE(AbsDaqNum, protLayerId)                (XCP_DAQ(AbsDaqNum, protLayerId).Mode_u8)
#define XCP_DAQ_PRIO(AbsDaqNum, protLayerId)                (XCP_DAQ(AbsDaqNum, protLayerId).Priority_u8)
#define XCP_DAQ_FLAGS(AbsDaqNum, protLayerId)               (XCP_DAQ(AbsDaqNum, protLayerId).Flags_u8)
#define XCP_DAQ_ODTMAX(AbsDaqNum, protLayerId)              (XCP_DAQ_ODTFIRST(AbsDaqNum, protLayerId) + XCP_DAQ_ODTCNT(AbsDaqNum, protLayerId))
/** \} */

/** \name Odt
 *  \{ */
#define XCP_ODT(AbsOdtNum, protLayerId)                     (Xcp_NoInit[(protLayerId)].DaqConfig.Odt_p[(AbsOdtNum)])
#define XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId)       (XCP_ODT(AbsOdtNum, protLayerId).OdtEntryFirst_u16)
#define XCP_ODT_ODTENTRYCNT(AbsOdtNum, protLayerId)         (XCP_ODT(AbsOdtNum, protLayerId).OdtEntryCnt_u8)
#define XCP_ODT_LENGTH(AbsOdtNum, protLayerId)              (XCP_ODT(AbsOdtNum, protLayerId).Length_u16)
#define XCP_ODT_ENTRYMAX(AbsOdtNum, protLayerId)            (XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId) + XCP_ODT_ODTENTRYCNT(AbsOdtNum, protLayerId))
#define XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId)         (XCP_ODT(AbsOdtNum, protLayerId).CopyRoutine_u8)
/** \} */

/** \name OdtEntry
 *  \{ */
#define XCP_ODTENTRY_ADR(AbsOdtEntryNum, protLayerId)       (Xcp_NoInit[(protLayerId)].DaqConfig.OdtEntryAdr_p[(AbsOdtEntryNum)])
#define XCP_ODTENTRY_SIZE(AbsOdtEntryNum, protLayerId)      (Xcp_NoInit[(protLayerId)].DaqConfig.OdtEntrySize_p[(AbsOdtEntryNum)])
/** \} */

/** \name Other calculations
 *  \{ */
#define Xcp_Daq_GetAbsOdtNum(AbsDaqNum, RelOdtNum, protLayerId) ((RelOdtNum) + XCP_DAQ_ODTFIRST(AbsDaqNum, protLayerId))
#define Xcp_Daq_GetRelOdtNum(AbsDaqNum, AbsOdtNum, protLayerId) ((AbsOdtNum) - XCP_DAQ_ODTFIRST(AbsDaqNum, protLayerId))
#define Xcp_Daq_OdtElementsInDaqQue(OdtCnt)                 ((((OdtCnt) * (uint32)((XCP_ODT_DAQ_BUFFER_ELEMENT_SIZE * 65536.0f) + 0.5f)) / 65536u) + 1u)
/** \} */


/***************************************************************************************************
* Type definitions
***************************************************************************************************/

/*--------------------------------------------------------------------------------------------------
  enum definitions
--------------------------------------------------------------------------------------------------*/
/** States for the PL background activities statemachine */
typedef enum
{
  XCP_BG_IDLE,                                              /**< No background activity running  */
  XCP_BG_CHKSUM,                                            /**< Background activity BUILD_CHECKSUM is running  */
  XCP_BG_MEM_WRITE,                                         /**< Background activity DOWNLOAD is running  */
  XCP_BG_CANCEL_REQ                                         /**< Running background activity is cancelled  */
} Xcp_BgActivity_t;

/*--------------------------------------------------------------------------------------------------
  structure definitions
--------------------------------------------------------------------------------------------------*/
/** Command function pointer */
typedef void (*Xcp_CmdFunctionPtr)(const PduInfoType* XcpPacket, uint8 protLayerId);

/** Command table */
typedef struct
{
  Xcp_CmdFunctionPtr Command_pfct;                          /**< Pointer to command handler function */
  uint8 ResourceMask_u8;                                    /**< BitMask of resources, which have to unlocked to run the command */
  uint8 CmdMinLength_u8;                                    /**< Minimum length of the command packet */
}Xcp_CmdTable_t;

/** daq queue position structure */
typedef struct
{
  uint16 WritePos_u16;                                      /**< Write position in the Queue */
  uint16 ReadPos_u16;                                       /**< Read position in the Queue */
  uint16 ReadPos_OdtNum_u16;                                /**< Odt Number of the ODT at the read position */
  uint16 QueSize_u16;                                       /**< Size of the Queue */
} Xcp_Que_t;

/** Running XCP session variables */
typedef struct
{
  Xcp_State_t     XcpState_en;                              /**< ASAM: state machine, additional states are added */
  uint8           ConnectedTlId_u8;                         /**< Connected transport layer Id */
  uint8           ResourceProtStatus_u8;                    /**< ASAM: Current resource protection status */
  Xcp_AdrPtr      Mta;                                      /**< ASAM: MTA (Memory Transfer Address) */
  uint16          MaxDto_u16;                               /**< ASAM: MAX_DTO, copy from const */
  uint16          MaxDto4Aligned_u16;                       /**< MAX_DTO aligned to 4 byte */
  uint8           MaxCto_u8;                                /**< ASAM: MAX_CTO, copy from const */
#if (XCP_RESUME_MODE == STD_ON)
  uint16          SessionConfId_u16;                        /**< ASAM: Session Configuration Id for resume mode */
  uint8           ResumeSessionStatus_u8;                   /**< Current SessionStatus bits in GET_STATUS for RESUME */
#endif
#if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
  Xcp_IdField_t   IdFieldType_en;                           /**< ASAM: Identification field type, copy from const */
#endif
}Xcp_Session_t;

/** GetId position for upload */
#if (XCP_CMD_GET_ID_AVAILABLE == STD_ON && XCP_MEMORY_READ_PROTECTION == STD_ON)
typedef struct
{
  Xcp_AdrPtr      GetIdPtr;                                 /**< GetId Pointer*/
  uint32          GetIdLen_u32;                             /**< GetId Length*/
}Xcp_GetId_t;
#endif

typedef struct
{
  uint8           Buffer_au8[XCP_MAX_CTO];                  /**< Data buffer with length of MAX_CTO */
  uint32          Length_u32;                               /**< Length, must be uint32 to align Buffer_au8 */
}Xcp_CtoMax_t;

/** Memory access variables */
#if (XCP_BLOCK_TRANSFER_UPLOAD == STD_ON || XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON || XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
typedef struct
{
# if (XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
  boolean         UploadRunning_b;                          /**< Indicates block upload is running */
# endif
# if ((XCP_BLOCK_TRANSFER_UPLOAD == STD_ON) || (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON))
  uint8           RemainingSize_u8;                         /**< Used for download and upload block transfer */
# endif
# if (XCP_CALIBRATION_CAL == STD_ON)
#  if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
  uint8           DownloadSize_u8;                          /**< Trigger for Xcp_MemWriteMainFunction() */
#  endif
#  if (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON)
  uint8           ReceivedSize_u8;                          /**< Holds the size to write in block transfer download */
  uint8           DownloadBuffer_au8[XCP_DOWNLOAD_NEXT_BUFFER_SIZE]; /**< Array holds the download data*/
#  else
#   if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
  uint8           DownloadBuffer_au8[XCP_MAX_CTO];          /**< In non-block transfer the buffer size is MAX_CTO */
#   endif
#  endif
# endif
}Xcp_Mem_t;
#endif

/** Seed and Key variables */
#if (XCP_SEED_AND_KEY == STD_ON)
typedef struct
{
  boolean         SeedWaitingKey_b;                         /**< Flag indicating that Key is expected */
  uint8           SeedRemaingSize_u8;                       /**< Remaining size of the seed to be sent */
}Xcp_SeedAndKey_t;
#endif

/** BuildChecksum variables */
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
typedef struct
{
  uint32          BlockSize_u32;                            /**< Size for checksum calculation */
# if (XCP_MEMORY_READ_PROTECTION == STD_ON)
  boolean         FakeChecksum_b;
# endif
}Xcp_Checksum_t;
#endif

/** Debug counter */
#if (XCP_DEV_ERROR_DETECT == STD_ON)
typedef struct
{
  uint16          Xcp_Debug_TransmitOkCtr;
  uint16          Xcp_Debug_TransmitNotOkCtr;
  uint16          Xcp_Debug_SendResTxConfCtr;
  uint16          Xcp_Debug_SendResCtr;
  uint16          Xcp_Debug_SendEvTxConfCtr;
  uint16          Xcp_Debug_SendEvCtr;
# if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  uint16          Xcp_Debug_SendDaqTxConfCtr;
  uint16          Xcp_Debug_SendDaqCtr;
# endif
  uint16          Xcp_Debug_TxConfCtr;
}Xcp_Debug_t;
#endif

/*--------------------------------------------------------------------------------------------------
  Daq configuration
--------------------------------------------------------------------------------------------------*/
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)

/** Structure for holding the data of currently selected OdtEntry (selected by SET_DAQ_PTR) */
typedef struct
{
  uint16          OdtEntryPos_u16;                          /**< Pointing to absolute OdtEntry */
  uint16          OdtEntryMax_u16;                          /**< Maximum allowed absolute OdtEntry (security reason) */
  uint16          DaqListNum_u16;                           /**< DaqList that contains the OdtEntry */
  uint16          AbsOdtNum_u16;                            /**< Absolute Odt-number that contains the OdtEntry */
}Xcp_SelectedOdtEntry_t;

/** Odt structure (for Daq and Stim) */
typedef struct
{
  uint16          OdtEntryFirst_u16;                        /**< Absolute OdtEntry number */
  uint8           OdtEntryCnt_u8;                           /**< OdtEntry count for this Odt */
  uint8           CopyRoutine_u8;                           /**< Copy routine that shall be used for this Odt (No enum is used here, as its size is compiler dependant!) */
  uint16          Length_u16;                               /**< Odt length */
}Xcp_Odt_t;

/** Stim buffer handling per Daq */
typedef struct
{
  uint8           OdtReceiveCtr_u8;                         /**< Odt receive counter */
  uint8           BufferNumReadActive_u8;                   /**< read active Buffer */
  uint8           BufferNumReadNext_u8;                     /**< buffer to read for next eventchannel*/
  uint8           BufferNumWriteActive_u8;
  uint8           CntStimReceived_u8;                       /**< number of stim buffers received */
  uint8           Status_u8;                                /**< status bits for stim */
}Xcp_BufferInfo_t;

/** Daq structure */
typedef struct
{
  uint8*          DaqListQue_p;                             /**< DaqListQue start pointer (aligned to uint32) */
  Xcp_Que_t       DaqListQuePos;
  uint16          OdtFirst_u16;                             /**< Absolute Odt number = First PID */
  uint8           OdtCnt_u8;                                /**< Odt count for this DaqList */
  uint16          EventChannelNum_u16;
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  Xcp_BufferInfo_t  BufferInfo;                             /**< Buffer information for stim */
# endif
  Xcp_PduIdType   XcpTxPduId;
  uint8           Prescaler_u8;                             /**< Prescaler for reducing the transmission period */
  uint8           CycleCnt_u8;
  uint8           Mode_u8;                                  /**< Daq list mode */
  uint8           Priority_u8;                              /**< 0xFF = highest */
  uint8           Flags_u8;                                 /**< Flags */
}Xcp_DaqList_t;

/** Single Daq config structure */
typedef struct
{
  /* Array start pointers */
  Xcp_DaqList_t*  DaqList_p;                                /**< DaqList array start pointer */
  Xcp_Odt_t*      Odt_p;                                    /**< Odt array start pointer */
  Xcp_AdrPtr*     OdtEntryAdr_p;                            /**< OdtEntryAdr array start pointer */
  uint8*          OdtEntrySize_p;                           /**< OdtEntrySize array start pointer */
  uint16*         PriorityList_p;                           /**< PriorityList array start pointer */
  uint8*          DaqQue_p;                                 /**< DaqQue start pointer (aligned to uint32) */

  /* Total counters */
  uint16          DaqListCnt_u16;                           /**< Number of Daqlist */
  uint16          OdtCnt_u16;                               /**< Number of Odt */
  uint16          OdtEntryCnt_u16;                          /**< Number of OdtEntry */
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  uint16          OdtStimCnt_u16;                           /**< Number of stim */
# endif

  Xcp_SelectedOdtEntry_t  SelectedOdtEntry;                 /**< Data of currently selected OdtEntry (using SET_DAQ_PTR) */

  /* Daq ram variables */
  uint8*          DaqRamPtr_pu8;                            /**< Start of Daq ram (aligned to uint32), same as DaqList_p */
  uint32          DaqRamSize_u32;                           /**< Size of Daq ram */

  /* Mixed variables */
  uint16          DaqListSendingCnt_u16;                    /**< Counter for running DaqList with direction DAQ (needed for PriorityList) */
  uint16          DaqListSending_u16;                       /**< Absolute sending DaqList number */
# if (XCP_DAQ_OVERLOAD_INDICATION_PID_ENABLED == STD_ON)
  boolean         OverloadOccurred_b;                       /**< Overload occurred in any DaqList */
# endif
  Xcp_DaqState_t  DaqState_en;                              /**< Daq state machine */
}Xcp_DaqConfig_t;

#endif  /* #if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) */

#if (XCP_RESUME_MODE == STD_ON)
/** Data structure for the small NvM Block ******************************************************/
typedef struct
{
  uint32          DaqConfigSize_u32;                        /**< Size of the saved DAQ configuration */
  uint16          SessionConfId_u16;                        /**< Session Configuration Id */
  uint8           ConnectedTlId_u8;                         /**< Connected Transport Layer Id */
}Xcp_SmallBlockData_t;

/** NVM request processing status ***************************************************************/
typedef enum
{
  XCP_NVM_NO_JOB = 0u,                                      /**< No Write or Clear is processed */
  XCP_NVM_JOB_RUNNING                                       /**< NvM Write or Clear request is processed */
}Xcp_NvMState_t;

/** Resume mode request status  *****************************************************************/
typedef enum
{
  XCP_STORE_IDLE = 0u,                                      /**< No SET_REQUEST was received */
  XCP_STORE_MODE_WRITE,                                     /**< XCP_STORE_DAQ_REQ was requested and TLData block is cleared */
  XCP_STORE_MODE_BLOCK_INFO_WRITE,                          /**< XCP_STORE_DAQ_REQ was requested and TLData block is written */
  XCP_STORE_MODE_BLOCK_DATA_WRITE,                          /**< XCP_STORE_DAQ_REQ was requested and DAQ config block is written */
  XCP_STORE_MODE_CLEAR,                                     /**< XCP_CLEAR_DAQ_REQ was requested and TLData block is cleared */
  XCP_STORE_MODE_BLOCK_DATA_CLEAR                           /**< XCP_CLEAR_DAQ_REQ was requested and DAQ config block is cleared */
}Xcp_SetRequestState_t;

/** Holds the information of processing status for the NVM memory ********************************/
typedef struct
{
  Xcp_NvMState_t        ReqProcessingState;                 /**< SET_REQUEST processing state */
  Xcp_SetRequestState_t StorageMode;                        /**< Requested mode by SET_REQUEST */
  Xcp_SmallBlockData_t  TLData_t;                           /**< Information for the small NvM block */
}Xcp_SetRequestData_t;
#endif

/*--------------------------------------------------------------------------------------------------
  Main structures
--------------------------------------------------------------------------------------------------*/

/** No-init configuration for protocol layer *****************************************************/
typedef struct
{
  Xcp_Session_t   Session;                                  /**< Running XCP session variables */
#if (XCP_CMD_GET_ID_AVAILABLE == STD_ON && XCP_MEMORY_READ_PROTECTION == STD_ON)
  Xcp_GetId_t     GetId;                                    /**< GetId position for upload */
#endif
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  Xcp_DaqConfig_t DaqConfig;                                /**< Daq config (static ram) */
#endif
}Xcp_NoInit_t;

typedef struct
{
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  Xcp_DaqRamSections_t DaqRamSections[XCP_MAX_DAQRAMSECTIONS]; /**< Ram section main variables (PD and/or ED) */
# if(XCP_DAQRAM_SHIFTING == STD_ON)
  Xcp_DaqRamMove_t DaqRamMove;                              /**< DaqRamShifting variables */
  uint8           DaqConfigActiveOnPl_u8;                   /**< Holds the PL on which the DAQ configuration is active */
# endif
  boolean         DaqTransmissionStopped_b;                 /**< DAQ  stopped in any protocol layer */
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  boolean         StimTransmissionStopped_b;                /**< STIM stopped in any protocol layer */
# endif
#endif
  uint8           Tl2PlRef_au8[XCP_TL_IDS];                 /**< dynamic Tl2Pl table */
  uint8           EnabledResources_u8;                      /**< globally enabled/disabled resources by external API */
  uint8           InitStatus_u8;                            /**< Initialization status */
#if (XCP_RESUME_MODE == STD_ON)
  Xcp_SetRequestData_t SetRequestData;                      /**< Set Request data */
#endif
}Xcp_GlobalNoInit_t;

/** Cleared configuration for protocol layer *****************************************************/
typedef struct
{
  uint8             Wait4TxConfCtr_u8;                      /**< Wait for TxConfirmation (>0), don't wait (0) */
  boolean           TxPending_b;                            /**< Transmit didn't work, transmission must be retriggered */
  Xcp_BgActivity_t  BgActivityState;                        /**< State of the background-activities statemachine */
  Xcp_CtoMax_t      ResBuffer;                              /**< Response data buffer of size MAX_CTO with response length */
  Xcp_Cto8_t        EvBuffer;                               /**< Event buffer of size 8 with response length */
#if (XCP_BLOCK_TRANSFER_UPLOAD == STD_ON || XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON || XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
  Xcp_Mem_t         Mem;                                    /**< Memory access variables */
#endif
#if (XCP_SEED_AND_KEY == STD_ON)
  Xcp_SeedAndKey_t  SeedAndKey;                             /**< Seed an Key variables */
#endif
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
  Xcp_Checksum_t    Checksum;                               /**< Checksum variables */
#endif
#if (XCP_DEV_ERROR_DETECT == STD_ON)
  Xcp_Debug_t       Debug;                                  /**< Debug counter */
#endif
}Xcp_Cleared_t;


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
extern Xcp_NoInit_t         Xcp_NoInit[XCP_PL_IDS];
extern Xcp_GlobalNoInit_t   Xcp_GlobalNoInit;
#define XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
extern Xcp_Cleared_t        Xcp_Cleared[XCP_PL_IDS];
#define XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Function prototypes
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/** \name XCP Transmit related functions
 *  \{ */
extern void Xcp_SendRes(uint8 protLayerId);
extern void Xcp_SendPosRes(uint8 protLayerId);
extern void Xcp_SendErrRes(Xcp_ErrorCode ErrorCode, uint8 protLayerId);
extern void Xcp_SendEv(const Xcp_Cto8_t* XcpPacketCtoPtr, uint8 protLayerId);
extern void Xcp_SendEv_Code(uint8 EventCode_u8, uint8 protLayerId);
extern void Xcp_RetriggerTransmit(uint8 protLayerId);
/** \} */

/** \name DAQ functions
 *  \{ */
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
extern boolean Xcp_DaqRamCheck(uint16 AddDaqList, uint8 AddOdt, uint8 AddOdtEntry, uint8 protLayerId);
extern uint32  Xcp_DaqRamCalc(uint16 AddDaqList, uint8 AddOdt, uint8 AddOdtEntry, uint8 protLayerId);
extern uint32  Xcp_DaqQueRamCalc(uint8 AddOdt, boolean setQuePointers, uint8 protLayerId);
extern void    Xcp_DaqListStart(uint16 daqListNo, uint8 protLayerId);
extern void    Xcp_DaqListStartSelected(uint8 protLayerId);
extern void    Xcp_DaqListStop(uint16 daqListNo, uint8 protLayerId);
extern void    Xcp_DaqListStopSelected(uint8 protLayerId);
extern void    Xcp_DaqListStopAll(uint8 protLayerId);
extern void    Xcp_DaqProcessRunningFlag(uint8 protLayerId);
extern void    Xcp_DaqCalculatePriorityList(uint8 protLayerId);
extern Xcp_ErrorCode  Xcp_DaqTriggerStateStartStop(const PduInfoType* XcpPacket, uint8 protLayerId);
extern Xcp_ErrorCode  Xcp_DaqTransformAndCheckOdtEntry(Xcp_AdrPtr* Address, uint8 Size, uint16 daqListNo_u16, uint8 protLayerId);
extern Xcp_ErrorCode  Xcp_DaqListFinalize(uint16 daqListNo_u16, uint8 protLayerId);
extern Xcp_ErrorCode  Xcp_DaqWriteDaq(Xcp_AdrPtr Address, uint8 Size, uint8 protLayerId);
# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
extern Xcp_ErrorCode  Xcp_DaqSetOdtCopyRoutine(Xcp_AdrPtrConst Address, uint8 Size, uint16 AbsOdtNum, uint8 protLayerId);
# endif
extern void    Xcp_InitDaqConfig(uint8 protLayerId);
extern void    Xcp_DaqRamRemove(uint8 protLayerId);
extern Xcp_ErrorCode  Xcp_DaqRamSetRam(uint8 protLayerId);
# if (XCP_DAQRAM_SHIFTING == STD_ON)
extern void    Xcp_DaqRamMainMovePL(void);
extern boolean Xcp_DaqRamTriggerMovePL(const PduInfoType* XcpPacket, uint8 protLayerId);
extern void    Xcp_DaqRamResetShift(uint8 protLayerId);
# endif
#endif
/** \} */

#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
   || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)))
extern void Xcp_CmdSynch_Cancel(uint8 protLayerId);
#endif

#if (XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
extern void Xcp_BlockUpload(uint8 protLayerId);
#endif
#if (XCP_CALIBRATION_CAL == STD_ON)
extern void Xcp_DownloadRes(Xcp_ErrorCode Error, uint8 protLayerId);
#endif

/* Disconnect Xcp protocol layer */
extern void Xcp_Disconnect(uint8 protLayerId);

#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
extern void Xcp_BuildChecksumMainFunction(uint8 protLayerId);
#endif

/** \name Init functions
 *  \{ */
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
extern void Xcp_InitChecksum(uint8 protLayerId);
#endif
#if (XCP_SEED_AND_KEY == STD_ON)
extern void Xcp_InitSeedKey(uint8 protLayerId);
#endif
extern void Xcp_InitUpload(uint8 protLayerId);
#if (XCP_CALIBRATION_CAL == STD_ON)
extern void Xcp_InitDownload(uint8 protLayerId);
#endif
/** \} */

/** \name Receive command
 *  \{ */
extern void   Xcp_ReceiveCommand(const PduInfoType* XcpPacketPtr, uint8 protLayerId);
extern void   Xcp_Receive(const PduInfoType* XcpPacketPtr, uint8 XcpTransportLayerId);

#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
extern void   Xcp_ReceiveStim(const PduInfoType* XcpPacketPtr, uint8 protLayerId);
#endif
/** \} */

/** \name Memory access functions
 *  \{ */
#define Xcp_MemCopy32(xDest_pu32, xSrc_pcu32,   numBytes_u32)       rba_BswSrv_MemCopy32((xDest_pu32),  (xSrc_pcu32),   (numBytes_u32))
#define Xcp_MemCopy16(xDest_pu16, xSrc_pcu16,   numBytes_u32)       rba_BswSrv_MemCopy16((xDest_pu16),  (xSrc_pcu16),   (numBytes_u32))
#define Xcp_MemCopy8( xDest_pu8,  xSrc_pcu8,    numBytes_u32)       rba_BswSrv_MemCopy8( (xDest_pu8),   (xSrc_pcu8),    (numBytes_u32))
#define Xcp_MemCopy(  xDest_pv,   xSrc_pcv,     numBytes_u32) (void)rba_BswSrv_MemCopy(  (xDest_pv),    (xSrc_pcv),     (numBytes_u32))
#define Xcp_MemSet32( xDest_pu32, xPattern_u32, numBytes_u32)       rba_BswSrv_MemSet32( (xDest_pu32),  (xPattern_u32), (numBytes_u32))
#define Xcp_MemSet16( xDest_pu16, xPattern_u32, numBytes_u32)       rba_BswSrv_MemSet16( (xDest_pu16),  (xPattern_u32), (numBytes_u32))
#define Xcp_MemSet8(  xDest_pu8,  xPattern_u32, numBytes_u32)       rba_BswSrv_MemSet8(  (xDest_pu8),   (xPattern_u32), (numBytes_u32))
#define Xcp_MemSet(   xDest_pv,   xPattern_s32, numBytes_u32) (void)rba_BswSrv_MemSet(   (xDest_pv),    (xPattern_s32), (numBytes_u32))
extern Xcp_ErrorCode Xcp_MemRead(Xcp_AdrPtr AddrPtrDst, uint8 Length, uint8 protLayerId);
#if(XCP_CALIBRATION_CAL == STD_ON)
extern Xcp_ErrorCode Xcp_MemWrite(Xcp_AdrPtrConst AddrPtrSrc, uint8 Length, uint8 protLayerId);
extern void Xcp_MemWriteMainFunction(uint8 protLayerId);
#endif /*XCP_CALIBRATION_CAL == STD_ON*/

#if (XCP_CALIBRATION_CAL == STD_ON || XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
extern Xcp_ErrorCode Xcp_MemWriteProtectionCheck(Xcp_AdrPtrConst Address, uint8 Length);
#endif
extern Xcp_ErrorCode Xcp_MemReadProtectionCheck(Xcp_AdrPtrConst Address, uint8 Length, uint8 protLayerId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
/** \} */

#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"
extern void   Xcp_TxConfirmation(uint8 XcpTransportLayerId);
#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"

#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"
#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
extern Xcp_EventChannelStatus_t Xcp_StimEvent(uint16 daqNo, uint8 protLayerId);
#endif
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
extern void  Xcp_SendDaq(uint16 daqListNo_u16, uint8 protLayerId);
extern uint8 Xcp_DaqEvent(uint16 daqListNo_u16, uint8 protLayerId);
#endif
#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

/** \name Queue specific functions
 *  \{ */
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
extern void Xcp_CreateQue(Xcp_DaqList_t* DaqListPtr, uint16 Size_u16);
extern void Xcp_InitDaqQueue(uint16 daqListNo_u16, uint8 protLayerId);
#endif
extern void Xcp_QueClearAll(uint8 protLayerId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
#define XCP_START_SEC_CODE_FAST
#include "Xcp_MemMap.h"
extern void Xcp_QueReadNext(Xcp_DaqList_t* DaqListPtr);
#define XCP_STOP_SEC_CODE_FAST
#include "Xcp_MemMap.h"


#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"
extern void Xcp_QueSetBack(Xcp_DaqList_t* DaqListPtr);
#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"
#endif /* (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) */
/** \} */


#if (XCP_RESUME_MODE == STD_ON)
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
extern void Xcp_ResumeModeActivate(void);
extern void Xcp_ResumeModeStorage(void);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"
#endif

/***************************************************************************************************
* Command function prototypes & definitions
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/** \name Command functions
 *  \{ */
extern void Xcp_CmdConnect                  (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_CONNECT_PFCT                (Xcp_CmdFunctionPtr)(&Xcp_CmdConnect)

extern void Xcp_CmdDisconnect               (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_DISCONNECT_PFCT             (Xcp_CmdFunctionPtr)(&Xcp_CmdDisconnect)

extern void Xcp_CmdGetStatus                (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_GET_STATUS_PFCT             (Xcp_CmdFunctionPtr)(&Xcp_CmdGetStatus)

extern void Xcp_CmdSynch                    (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_SYNCH_PFCT                  (Xcp_CmdFunctionPtr)(&Xcp_CmdSynch)

#if (XCP_CMD_GET_COMM_MODE_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetCommModeInfo          (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_COMM_MODE_INFO_PFCT     (Xcp_CmdFunctionPtr)(&Xcp_CmdGetCommModeInfo)
#else
#define XCP_CMD_GET_COMM_MODE_INFO_PFCT     (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_ID_AVAILABLE == STD_ON)
extern void Xcp_CmdGetId                    (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_ID_PFCT                 (Xcp_CmdFunctionPtr)(&Xcp_CmdGetId)
#else
#define XCP_CMD_GET_ID_PFCT                 (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_RESUME_MODE == STD_ON)
extern void Xcp_CmdSetRequest               (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_SET_REQUEST_PFCT            (Xcp_CmdFunctionPtr)(&Xcp_CmdSetRequest)
#else
#define XCP_CMD_SET_REQUEST_PFCT            (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_SEED_AVAILABLE == STD_ON)
extern void Xcp_CmdGetSeed                  (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_SEED_PFCT               (Xcp_CmdFunctionPtr)(&Xcp_CmdGetSeed)
#else
#define XCP_CMD_GET_SEED_PFCT               (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_UNLOCK_AVAILABLE == STD_ON)
extern void Xcp_CmdUnlock                   (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_UNLOCK_PFCT                 (Xcp_CmdFunctionPtr)(&Xcp_CmdUnlock)
#else
#define XCP_CMD_UNLOCK_PFCT                 (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

extern void Xcp_CmdSetMta                   (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_SET_MTA_PFCT                (Xcp_CmdFunctionPtr)(&Xcp_CmdSetMta)

extern void Xcp_CmdUpload                   (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_UPLOAD_PFCT                 (Xcp_CmdFunctionPtr)(&Xcp_CmdUpload)

extern void Xcp_CmdShortUpload              (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_SHORT_UPLOAD_PFCT           (Xcp_CmdFunctionPtr)(&Xcp_CmdShortUpload)

#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
extern void Xcp_CmdBuildChecksum            (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_BUILD_CHECKSUM_PFCT         (Xcp_CmdFunctionPtr)(&Xcp_CmdBuildChecksum)
#else
#define XCP_CMD_BUILD_CHECKSUM_PFCT         (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

extern void Xcp_CmdTransportLayerCmd        (const PduInfoType* XcpPacket, uint8 protLayerId); /* This command cannot be switched off! */
#define XCP_CMD_TRANSPORT_LAYER_CMD_PFCT    (Xcp_CmdFunctionPtr)(&Xcp_CmdTransportLayerCmd)

#if (XCP_CMD_USER_CMD_AVAILABLE == STD_ON)
extern void Xcp_CmdUserCmd                  (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_USER_CMD_PFCT               (Xcp_CmdFunctionPtr)(&Xcp_CmdUserCmd)
#else
#define XCP_CMD_USER_CMD_PFCT               (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_DOWNLOAD_AVAILABLE == STD_ON)
extern void Xcp_CmdDownload                 (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_DOWNLOAD_PFCT               (Xcp_CmdFunctionPtr)(&Xcp_CmdDownload)
#else
#define XCP_CMD_DOWNLOAD_PFCT               (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_DOWNLOAD_NEXT_AVAILABLE == STD_ON)
extern void Xcp_CmdDownloadNext             (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_DOWNLOAD_NEXT_PFCT          (Xcp_CmdFunctionPtr)(&Xcp_CmdDownloadNext)
#else
#define XCP_CMD_DOWNLOAD_NEXT_PFCT          (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_DOWNLOAD_MAX_AVAILABLE == STD_ON)
extern void Xcp_CmdDownloadMax              (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_DOWNLOAD_MAX_PFCT           (Xcp_CmdFunctionPtr)(&Xcp_CmdDownloadMax)
#else
#define XCP_CMD_DOWNLOAD_MAX_PFCT           (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_SHORT_DOWNLOAD_AVAILABLE == STD_ON)
extern void Xcp_CmdShortDownload            (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_SHORT_DOWNLOAD_PFCT         (Xcp_CmdFunctionPtr)(&Xcp_CmdShortDownload)
#else
#define XCP_CMD_SHORT_DOWNLOAD_PFCT         (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_MODIFY_BITS_AVAILABLE == STD_ON)
extern void Xcp_CmdModifyBits               (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_MODIFY_BITS_PFCT            (Xcp_CmdFunctionPtr)(&Xcp_CmdModifyBits)
#else
#define XCP_CMD_MODIFY_BITS_PFCT            (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_SET_CAL_PAGE_AVAILABLE == STD_ON)
extern void Xcp_CmdSetCalPage               (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_SET_CAL_PAGE_PFCT           (Xcp_CmdFunctionPtr)(&Xcp_CmdSetCalPage)
#else
#define XCP_CMD_SET_CAL_PAGE_PFCT           (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_CAL_PAGE_AVAILABLE == STD_ON)
extern void Xcp_CmdGetCalPage               (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_CAL_PAGE_PFCT           (Xcp_CmdFunctionPtr)(&Xcp_CmdGetCalPage)
#else
#define XCP_CMD_GET_CAL_PAGE_PFCT           (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_PAG_PROCESSOR_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetPagProcessorInfo      (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_PAG_PROCESSOR_INFO_PFCT (Xcp_CmdFunctionPtr)(&Xcp_CmdGetPagProcessorInfo)
#else
#define XCP_CMD_GET_PAG_PROCESSOR_INFO_PFCT (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_SEGMENT_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetSegmentInfo           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_SEGMENT_INFO_PFCT       (Xcp_CmdFunctionPtr)(&Xcp_CmdGetSegmentInfo)
#else
#define XCP_CMD_GET_SEGMENT_INFO_PFCT       (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_PAGE_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetPageInfo              (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_PAGE_INFO_PFCT          (Xcp_CmdFunctionPtr)(&Xcp_CmdGetPageInfo)
#else
#define XCP_CMD_GET_PAGE_INFO_PFCT          (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_SET_SEGMENT_MODE_AVAILABLE == STD_ON)
extern void Xcp_CmdSetSegmentMode           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_SET_SEGMENT_MODE_PFCT       (Xcp_CmdFunctionPtr)(&Xcp_CmdSetSegmentMode)
#else
#define XCP_CMD_SET_SEGMENT_MODE_PFCT       (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_SEGMENT_MODE_AVAILABLE == STD_ON)
extern void Xcp_CmdGetSegmentMode           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_SEGMENT_MODE_PFCT       (Xcp_CmdFunctionPtr)(&Xcp_CmdGetSegmentMode)
#else
#define XCP_CMD_GET_SEGMENT_MODE_PFCT       (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_COPY_CAL_PAGE_AVAILABLE == STD_ON)
extern void Xcp_CmdCopyCalPage              (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_COPY_CAL_PAGE_PFCT          (Xcp_CmdFunctionPtr)(&Xcp_CmdCopyCalPage)
#else
#define XCP_CMD_COPY_CAL_PAGE_PFCT          (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_SET_DAQ_PTR_AVAILABLE == STD_ON)
extern void Xcp_CmdSetDaqPtr                (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_SET_DAQ_PTR_PFCT            (Xcp_CmdFunctionPtr)(&Xcp_CmdSetDaqPtr)
#else
#define XCP_CMD_SET_DAQ_PTR_PFCT            (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_WRITE_DAQ_AVAILABLE == STD_ON)
extern void Xcp_CmdWriteDaq                 (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_WRITE_DAQ_PFCT              (Xcp_CmdFunctionPtr)(&Xcp_CmdWriteDaq)
#else
#define XCP_CMD_WRITE_DAQ_PFCT              (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_SET_DAQ_LIST_MODE_AVAILABLE == STD_ON)
extern void Xcp_CmdSetDaqListMode           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_SET_DAQ_LIST_MODE_PFCT      (Xcp_CmdFunctionPtr)(&Xcp_CmdSetDaqListMode)
#else
#define XCP_CMD_SET_DAQ_LIST_MODE_PFCT      (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_START_STOP_DAQ_LIST_AVAILABLE == STD_ON)
extern void Xcp_CmdStartStopDaqList         (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_START_STOP_DAQ_LIST_PFCT    (Xcp_CmdFunctionPtr)(&Xcp_CmdStartStopDaqList)
#else
#define XCP_CMD_START_STOP_DAQ_LIST_PFCT    (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_START_STOP_SYNCH_AVAILABLE == STD_ON)
extern void Xcp_CmdStartStopSynch           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_START_STOP_SYNCH_PFCT       (Xcp_CmdFunctionPtr)(&Xcp_CmdStartStopSynch)
#else
#define XCP_CMD_START_STOP_SYNCH_PFCT       (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_WRITE_DAQ_MULTIPLE_AVAILABLE == STD_ON)
extern void Xcp_CmdWriteDaqMultiple         (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_WRITE_DAQ_MULTIPLE_PFCT     (Xcp_CmdFunctionPtr)(&Xcp_CmdWriteDaqMultiple)
#else
#define XCP_CMD_WRITE_DAQ_MULTIPLE_PFCT     (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_READ_DAQ_AVAILABLE == STD_ON)
extern void Xcp_CmdReadDaq                  (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_READ_DAQ_PFCT               (Xcp_CmdFunctionPtr)(&Xcp_CmdReadDaq)
#else
#define XCP_CMD_READ_DAQ_PFCT               (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_DAQ_CLOCK_AVAILABLE == STD_ON)
extern void Xcp_CmdGetDaqClock              (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_DAQ_CLOCK_PFCT          (Xcp_CmdFunctionPtr)(&Xcp_CmdGetDaqClock)
#else
#define XCP_CMD_GET_DAQ_CLOCK_PFCT          (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_DAQ_PROCESSOR_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetDaqProcessorInfo      (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_DAQ_PROCESSOR_INFO_PFCT (Xcp_CmdFunctionPtr)(&Xcp_CmdGetDaqProcessorInfo)
#else
#define XCP_CMD_GET_DAQ_PROCESSOR_INFO_PFCT (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_DAQ_RESOLUTION_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetDaqResolutionInfo       (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_DAQ_RESOLUTION_INFO_PFCT  (Xcp_CmdFunctionPtr)(&Xcp_CmdGetDaqResolutionInfo)
#else
#define XCP_CMD_GET_DAQ_RESOLUTION_INFO_PFCT  (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_DAQ_LIST_MODE_AVAILABLE == STD_ON)
extern void Xcp_CmdGetDaqListMode           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_DAQ_LIST_MODE_PFCT      (Xcp_CmdFunctionPtr)(&Xcp_CmdGetDaqListMode)
#else
#define XCP_CMD_GET_DAQ_LIST_MODE_PFCT      (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_DAQ_EVENT_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetDaqEventInfo          (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_DAQ_EVENT_INFO_PFCT     (Xcp_CmdFunctionPtr)(&Xcp_CmdGetDaqEventInfo)
#else
#define XCP_CMD_GET_DAQ_EVENT_INFO_PFCT     (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_CLEAR_DAQ_LIST_AVAILABLE == STD_ON)
extern void Xcp_CmdClearDaqList             (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_CLEAR_DAQ_LIST_PFCT         (Xcp_CmdFunctionPtr)(&Xcp_CmdClearDaqList)
#else
#define XCP_CMD_CLEAR_DAQ_LIST_PFCT         (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_DAQ_LIST_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetDaqListInfo           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_DAQ_LIST_INFO_PFCT      (Xcp_CmdFunctionPtr)(&Xcp_CmdGetDaqListInfo)
#else
#define XCP_CMD_GET_DAQ_LIST_INFO_PFCT      (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_FREE_DAQ_AVAILABLE == STD_ON)
extern void Xcp_CmdFreeDaq                  (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_FREE_DAQ_PFCT               (Xcp_CmdFunctionPtr)(&Xcp_CmdFreeDaq)
#else
#define XCP_CMD_FREE_DAQ_PFCT               (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_ALLOC_DAQ_AVAILABLE == STD_ON)
extern void Xcp_CmdAllocDaq                 (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_ALLOC_DAQ_PFCT              (Xcp_CmdFunctionPtr)(&Xcp_CmdAllocDaq)
#else
#define XCP_CMD_ALLOC_DAQ_PFCT              (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_ALLOC_ODT_AVAILABLE == STD_ON)
extern void Xcp_CmdAllocOdt                 (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_ALLOC_ODT_PFCT              (Xcp_CmdFunctionPtr)(&Xcp_CmdAllocOdt)
#else
#define XCP_CMD_ALLOC_ODT_PFCT              (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_ALLOC_ODT_ENTRY_AVAILABLE == STD_ON)
extern void Xcp_CmdAllocOdtEntry            (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_ALLOC_ODT_ENTRY_PFCT        (Xcp_CmdFunctionPtr)(&Xcp_CmdAllocOdtEntry)
#else
#define XCP_CMD_ALLOC_ODT_ENTRY_PFCT        (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_START_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramStart             (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_START_PFCT          (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramStart)
#else
#define XCP_CMD_PROGRAM_START_PFCT          (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_CLEAR_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramClear             (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_CLEAR_PFCT          (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramClear)
#else
#define XCP_CMD_PROGRAM_CLEAR_PFCT          (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_AVAILABLE == STD_ON)
extern void Xcp_CmdProgram                  (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_PFCT                (Xcp_CmdFunctionPtr)(&Xcp_CmdProgram)
#else
#define XCP_CMD_PROGRAM_PFCT                (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_RESET_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramReset             (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_RESET_PFCT          (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramReset)
#else
#define XCP_CMD_PROGRAM_RESET_PFCT          (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_PGM_PROCESSOR_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetPgmProcessorInfo      (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_PGM_PROCESSOR_INFO_PFCT (Xcp_CmdFunctionPtr)(&Xcp_CmdGetPgmProcessorInfo)
#else
#define XCP_CMD_GET_PGM_PROCESSOR_INFO_PFCT (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_GET_SECTOR_INFO_AVAILABLE == STD_ON)
extern void Xcp_CmdGetSectorInfo            (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_GET_SECTOR_INFO_PFCT        (Xcp_CmdFunctionPtr)(&Xcp_CmdGetSectorInfo)
#else
#define XCP_CMD_GET_SECTOR_INFO_PFCT        (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_PREPARE_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramPrepare           (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_PREPARE_PFCT        (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramPrepare)
#else
#define XCP_CMD_PROGRAM_PREPARE_PFCT        (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_FORMAT_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramFormat            (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_FORMAT_PFCT         (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramFormat)
#else
#define XCP_CMD_PROGRAM_FORMAT_PFCT         (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_NEXT_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramNext              (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_NEXT_PFCT           (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramNext)
#else
#define XCP_CMD_PROGRAM_NEXT_PFCT           (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_MAX_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramMax               (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_MAX_PFCT            (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramMax)
#else
#define XCP_CMD_PROGRAM_MAX_PFCT            (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif

#if (XCP_CMD_PROGRAM_VERIFY_AVAILABLE == STD_ON)
extern void Xcp_CmdProgramVerify            (const PduInfoType* XcpPacket, uint8 protLayerId);
#define XCP_CMD_PROGRAM_VERIFY_PFCT         (Xcp_CmdFunctionPtr)(&Xcp_CmdProgramVerify)
#else
#define XCP_CMD_PROGRAM_VERIFY_PFCT         (Xcp_CmdFunctionPtr)(NULL_PTR)
#endif
/** \} */


#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


#endif   /* #ifndef XCP_PRIV_H */


