

#ifndef XCP_TYPES_H
#define XCP_TYPES_H

/***************************************************************************************************
* Includes
***************************************************************************************************/


/***************************************************************************************************
* Protocol parameters
***************************************************************************************************/
/** \name Current Session Status parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- STORE_CAL_REQ
 *   | | | | | | +--- reserved
 *   | | | | | +----- STORE_DAQ_REQ
 *   | | | | +------- CLEAR_DAQ_REQ
 *   | | | +--------- reserved
 *   | | +----------- reserved
 *   | +------------- DAQ_RUNNING
 *   +--------------- RESUME
 * ```
 * \{ */
#define XCP_STORE_CAL_REQ         0x01u /**< REQuest to STORE CALibration data */
#define XCP_STORE_DAQ_REQ         0x04u /**< REQuest to STORE DAQ list */
#define XCP_CLEAR_DAQ_REQ         0x08u /**< REQuest to CLEAR DAQ configuration */
#define XCP_DAQ_RUNNING           0x40u /**< Data Transfer is running */
#define XCP_RESUME                0x80u /**< RESUME Mode is enabled */
/** \} */

/** \name DAQ_LIST_MODE Flags
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- SELECTED (GET_DAQ_LIST_MODE) / ALTERNATING (SET_DAQ_LIST_MODE)
 *   | | | | | | +--- DIRECTION
 *   | | | | | +----- reserved
 *   | | | | +------- reserved
 *   | | | +--------- TIMESTAMP
 *   | | +----------- PID_OFF
 *   | +------------- RUNNING
 *   +--------------- RESUME
 * ```
 * \{ */
#define XCP_DAQLISTMODE_RESUME          0x80u /**< DAQ list is part of configuration used in RESUME mode */
#define XCP_DAQLISTMODE_RUNNING         0x40u /**< DAQ list is active */
#define XCP_DAQLISTMODE_PID_OFF         0x20u /**< DTO is transmitted with Identification field */
#define XCP_DAQLISTMODE_TIMESTAMP       0x10u /**< Timestamp is enabled */
#define XCP_DAQLISTMODE_DIRECTION       0x02u /**< If this flag is not set the direction is DAQ Data Acquisition Mode (Slave -> Master)\n
                                               *   If this flag is set the direction is STIM Data Stimulation Mode (Master -> Slave) */
#define XCP_DAQLISTMODE_SELECTED        0x01u /**< DAQ list is selected (Only for GET_DAQ_LIST_MODE) */
#define XCP_DAQLISTMODE_ALTERNATING     0x01u /**< DAQ list is running in alternating mode (Only for SET_DAQ_LIST_MODE) */
/** \} */

/** \name RESOURCE parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- calibration/paging available(1) or not (0)
 *   | | | | | | +--- reserved
 *   | | | | | +----- DAQ lists available (1) or not (0)
 *   | | | | +------- stimulation available (1) or not (0)
 *   | | | +--------- Flash programming available (1) or not (0)
 *   | | +----------- reserved
 *   | +------------- reserved
 *   +--------------- reserved
 * ```
 * \{ */
#define XCP_RESOURCE_CALPAG       0x01u /**< Calibration/Paging available */
#define XCP_RESOURCE_DAQ          0x04u /**< DAQ lists supported */
#define XCP_RESOURCE_STIM         0x08u /**< Data stimulation mode of a DAQ list available */
#define XCP_RESOURCE_PGM          0x10u /**< Flash programming available */
#define XCP_RESOURCE_NONE         0x00u /**< None of the XCP resources are enabled */
/** \} */

/** \name COMM_MODE_BASIC parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- BYTE_ORDER Motorola(1) or Intel (0)
 *   | | | | | | +--- ADDRESS_GRANULARITY_0 indicates the size of an element contained at a single addr.
 *   | | | | | +----- ADDRESS_GRANULARITY_1 BYTE:00, WORD:01, DWORD:10, reserved:11
 *   | | | | +------- reserved
 *   | | | +--------- reserved
 *   | | +----------- reserved
 *   | +------------- SLAVE_BLOCK_MODE indicates if the block mode is available
 *   +--------------- OPTIONAL indicates whether additional info is available
 * ```
 * \{ */
#define XCP_BYTE_ORDER_MASK       0x01u /**< Byte order used for transferring multi-byte parameter (1=Motorola, 0=Intel) */
#define XCP_SLAVE_BLOCK_MASK      0x40u /**< Block mode is available */
#define XCP_OPTIONAL_MASK         0x80u /**< Additional info is available */
/** \} */

/** \name COMM MODE OPTIONAL parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- MASTER_BLOCK_MODE indicates whether the master block mode is available
 *   | | | | | | +--- INTERLEAVED_MODE indicates whether the interleaved mode is available
 *   | | | | | +----- reserved
 *   | | | | +------- reserved
 *   | | | +--------- reserved
 *   | | +----------- reserved
 *   | +------------- reserved
 *   +--------------- reserved
 * ```
 * \{ */
#define XCP_COMM_MODE_OPTIONAL_MASTER_BLOCK_MODE    0x01u /**< Master Block Mode is available */
#define XCP_COMM_MODE_OPTIONAL_INTERLEAVED_MODE     0x02u /**< Interleaved Mode is available */
/** \} */

/** \name GET_ID MODE parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- TRANSFER_MODE 1: the identification is transferred in the remaining bytes of the response
 *   | | | | | | |                  0: the slave device sets the Memory Transfer Address (upload request)
 *   | | | | | | +--- COMPRESSED_ENCRYPTED not supported must be 0
 *   | | | | | +----- reserved
 *   | | | | +------- reserved
 *   | | | +--------- reserved
 *   | | +----------- reserved
 *   | +------------- reserved
 *   +--------------- reserved
 * ```
 * \{ */
#define XCP_GETID_TRANSFER_MODE0      0x00u /**< Slave device sets the Memory Transfer Address (UPLOAD request) */
#define XCP_GETID_TRANSFER_MODE1      0x01u /**< Identification is transferred in the remaining bytes of the response */
/** \} */

/** \name GET_DAQ_PROCESSOR_INFO: DAQ_PROPERTIES parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- DAQ_CONFIG_TYPE     0: static DAQ list configuration
 *   | | | | | | |                        1: dynamic DAQ list configuration (supported only Dynamic and must be 1)
 *   | | | | | | +--- PRESCALER_SUPPORTED prescaler supported and must be 1
 *   | | | | | +----- RESUME_SUPPORTED    0: DAQ lists can not be set to RESUME mode
 *   | | | | |                            1: DAQ lists can be set to RESUME mode
 *   | | | | +------- BIT_STIM_SUPPORTED (not supported and must be 0)
 *   | | | +--------- TIMESTAMP_SUPPORTED 0: time-stamped mode not supported
 *   | | |                                1: time-stamped mode supported
 *   | | +----------- PID_OFF_SUPPORTED (not supported and must be 0)
 *   | |              (bit6 and bit7)
 *   | +------------- OVERLOAD_MSB     - 00: No overload indication,              01: overload indication in MSB of PID,
 *   +--------------- OVERLOAD_EVENT   - 10: overload indication by Event Packet, 11: not allowed
 * ```
 * \{ */
#define XCP_DAQ_PROPERTIES_DAQ_CONFIG_TYPE      0x01u /**< DAQ list configuration: dynamic=1, static=0 */
#define XCP_DAQ_PROPERTIES_PRESCALER_SUPPORTED  0x02u /**< Prescaler supported */
#define XCP_DAQ_PROPERTIES_RESUME_SUPPORTED     0x04u /**< DAQ lists can be set to RESUME mode */
#define XCP_DAQ_PROPERTIES_TIMESTAMP_SUPPORTED  0x10u /**< Time-stamped mode supported */
/** \} */

#define XCP_GET_DAQ_PROCESSOR_INFO_MIN_DAQ      0x00u /**< Total number of predefined DAQ lists. Must be 0 */

/** \name GET_DAQ_PROCESSOR_INFO: DAQ_KEY_BYTE parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- Optimisation_Type_0
 *   | | | | | | +--- Optimisation_Type_1
 *   | | | | | +----- Optimisation_Type_2
 *   | | | | +------- Optimisation_Type_3
 *   | | | +--------- Address_Extension_ODT (bit4 and bit5 -Not supported - ADDRESS_EXTENSION_FREE and must be 01)
 *   | | +----------- Address_Extension_DAQ
 *   | |              (bit6 and bit7)
 *   | +------------- Identification_Field_Type_0  - 00:Absolute ODT number,                                   01: Relative ODT number absolute DAQ list number (BYTE)
 *   +--------------- Identification_Field_Type_1  - 10: Relative ODT number, absolute DAQ list number (WORD), 11: Relative ODT number, absolute DAQ list number (WORD, aligned)
 * ```
 * \{ */
#define XCP_DAQ_KEY_BYTE_ADDRESS_EXTENSION_FREE 0x20u /**< Address extension is not allowed */
/** \} */

/** \name DAQ_EVENT_PROPERTIES parameters
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- reserved
 *   | | | | | | +--- reserved
 *   | | | | | +----- DAQ   Bit2, 3 are for Event Channel Type (Direction)
 *   | | | | +------- STIM  00: Not Allowed, 01: Daq Direction, 10: Stim Direction, 11: Both Directions.
 *   | | | +--------- reserved
 *   | | +----------- reserved
 *   | +------------- CONSISTENCY_DAQ   Bit6, 7 are for Consistency parameter bits. 00: ODT consistency (default)
 *   +--------------- CONSISTENCY_EVENT 01: DAQ consistency, 10: Event consistency
 * ```
 * \{ */
#define XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_DAQ       0x04u /**< event channel type is DAQ direction */
#define XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_STIM      0x08u /**< event channel type is STIM direction */
#define XCP_DAQ_EVENT_PROPERTIES_CHANNEL_TYPE_DAQ_STIM  0x0Cu /**< event channel type is both DAQ and STIM direction */
/** \} */

/** \name SET_REQUEST MODE parameter
 * ```
 *   7 6 5 4 3 2 1 0
 *   | | | | | | | |
 *   | | | | | | | +- STORE_CAL_REQ             REQuest to STORE CALibration data (1) or (0)
 *   | | | | | | +--- STORE_DAQ_REQ_NO_RESUME   REQuest to STORE DAQ list, no RESUME
 *   | | | | | +----- STORE_DAQ_REQ_RESUME      REQuest to STORE DAQ list, RESUME enabled
 *   | | | | +------- CLEAR_DAQ_REQ             REQuest to CLEAR DAQ configuration
 *   | | | +--------- reserved
 *   | | +----------- reserved
 *   | +------------- reserved
 *   +--------------- reserved
 * ```
 * \{ */
#define XCP_SET_REQUEST_STORE_CAL_REQ               0x01u  /**< Calibration data shall be stored in NVM */
#define XCP_SET_REQUEST_STORE_DAQ_REQ_NO_RESUME     0x02u  /**< Selected DAQ lists shall be stored in NVM */
#define XCP_SET_REQUEST_STORE_DAQ_REQ_RESUME        0x04u  /**< Selected DAQ lists shall be stored in NVM and next start RESUME mode shall be active */
#define XCP_SET_REQUEST_CLEAR_DAQ_REQ               0x08u  /**< Data shall be deleted from NVM */
/** \} */


/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/
/** XCP Communication States */
typedef enum{
  XCP_STATE_DISCONNECTED  = 0x00u, /**< XCP is disconnected */
  XCP_STATE_DISCONNECTING = 0x01u, /**< Non ASAM state - XCP has received a DISCONNECT request and is processing it */
  XCP_STATE_CONNECTED     = 0x02u, /**< XCP is connected */
  XCP_STATE_RESUME        = 0x03u, /**< XCP is in RESUME mode - only CONNECT and DAQ is possible */
  XCP_STATE_DISABLED      = 0xF0u  /**< Non ASAM state - XCP is disabled, no connection is possible */
}Xcp_State_t;


/** \name Initialisation status of XCP
 *  \{ */
#define XCP_UNINIT  0x00u /**< XCP Uninitialized */
#define XCP_INIT    0x01u /**< XCP Initialized   */
/** \} */

/** \name DAQ List start stop mode parameter options
 *  \{ */
#define XCP_DAQLIST_UNDEF               0xFFFFu /**< XCP Undefined DAQ List */
#define XCP_DAQLIST_START               0x01u   /**< XCP Start DAQ list */
#define XCP_DAQLIST_STOP                0x00u   /**< XCP Stop DAQ list */
#define XCP_DAQLIST_SELECT              0x02u   /**< XCP Select DAQ list */
#define XCP_DAQLIST_SYNC_STOPALL        0x00u   /**< XCP Stop All for DAQ list */
#define XCP_DAQLIST_SYNC_STARTSEL       0x01u   /**< XCP Start Selected DAQ list */
#define XCP_DAQLIST_SYNC_STOPSEL        0x02u   /**< XCP Stop Selected DAQ list */
#define XCP_DAQLISTMODE_DIRECTION_DAQ   0x00u   /**< XCP Direction for DAQ */
#define XCP_DAQLISTMODE_DIRECTION_STIM  0x02u   /**< XCP Direction for STIM */
#define XCP_DOWNLOAD_NEXT_BUFFER_SIZE   255u    /**< XCP Buffer size for DOWNLOAD_NEXT command */
/** \} */

/** \name Event Codes
 *  \{ */
#define XCP_EV_RESUME_MODE              0x00u /**< Slave starting in RESUME mode */
#define XCP_EV_CLEAR_DAQ                0x01u /**< The DAQ configuration in nonvolatile memory has been cleared */
#define XCP_EV_STORE_DAQ                0x02u /**< The DAQ configuration has been stored into non-volatile memory */
#define XCP_EV_STORE_CAL                0x03u /**< The calibration data has been stored into non-volatile memory */
#define XCP_EV_CMD_PENDING              0x05u /**< Slave requesting to restart timeout */
#define XCP_EV_DAQ_OVERLOAD             0x06u /**< DAQ processor overload */
#define XCP_EV_SESSION_TERMINATED       0x07u /**< Session terminated by slave device */
#define XCP_EV_TIME_SYNC                0x08u /**< Transfer of externally triggered timestamp */
#define XCP_EV_STIM_TIMEOUT             0x09u /**< Indication of a STIM timeout */
#define XCP_EV_SLEEP                    0x0Au /**< Slave entering SLEEP mode */
#define XCP_EV_WAKE_UP                  0x0Bu /**< Slave leaving SLEEP mode */
#define XCP_EV_USER                     0xFEu /**< User-defined event */
#define XCP_EV_TRANSPORT                0xFFu /**< Transport layer specific event */
/** \} */

/** \name Checksum types
 *  \{ */
#define XCP_CHECKSUM_TYPE_NO_CHECKSUM   0x00u /**< No checksum used */
#define XCP_CHECKSUM_TYPE_ADD_11        0x01u /**< Add BYTE into a BYTE checksum, ignore overflows */
#define XCP_CHECKSUM_TYPE_ADD_12        0x02u /**< Add BYTE into a WORD checksum, ignore overflows */
#define XCP_CHECKSUM_TYPE_ADD_14        0x03u /**< Add BYTE into a DWORD checksum, ignore overflows */
#define XCP_CHECKSUM_TYPE_ADD_22        0x04u /**< Add WORD into a WORD checksum, ignore overflows, block size must be modulo 2 */
#define XCP_CHECKSUM_TYPE_ADD_24        0x05u /**< Add WORD into a DWORD checksum, ignore overflows, block size must be modulo 2 */
#define XCP_CHECKSUM_TYPE_ADD_44        0x06u /**< Add DWORD into DWORD, ignore overflows, block size must be modulo 4 */
#define XCP_CHECKSUM_TYPE_CRC_16        0x07u /**< Checksum method calculation for CRC 16 */
#define XCP_CHECKSUM_TYPE_CRC_16_CITT   0x08u /**< Checksum method calculation for CRC 16 with CITT */
#define XCP_CHECKSUM_TYPE_CRC_32        0x09u /**< Checksum method calculation for CRC 32 */
#define XCP_CHECKSUM_TYPE_USER_DEFINED  0xFFu /**< User defined algorithm, in externally calculated function */
/** \} */

/** \name DAQ Flags
 *  \{ */
#define XCP_DAQFLAG_RECEIVED_DAQ_LIST_MODE    0x01u /**< set, when SetDaqListMode has been received for this DAQ */
#define XCP_DAQFLAG_CONFIG_COMPLETED          0x02u /**< set, when the DAQ Config has been completed */
#define XCP_DAQFLAG_FOLLOWING_WRITE_DAQ       0x04u /**< set, when SetDaqListMode has been received before the first WriteDaq was received */
#define XCP_DAQFLAG_ADDR_TRANSFORMATION_DONE  0x08u /**< set, when the Address-Transformation was done */
#define XCP_DAQFLAG_READ_PROTECTED            0x10u /**< set, when at least one address in DAQ is read protected */
#define XCP_DAQFLAG_WRITE_PROTECTED           0x20u /**< set, when at least one address in DAQ is write protected */
/** \} */

/** \name Calibration page related parameters and definitions
 *  \{ */
#define XCP_CAL_PAGE_MODE_ECU   0x01u   /**< The given page will be used by the slave device application. */
#define XCP_CAL_PAGE_MODE_XCP   0x02u   /**< The slave device XCP driver will access the given page. */
#define XCP_CAL_PAGE_MODE_ALL   0x80u   /**< The logical segment number is ignored. The command applies to all segments */
/** \} */

/** \name XCP packet Identifiers - defined by ASAM
 *  \{ */
#define XCP_PACKET_ID_CMD_MIN   0xC0u   /**< Command Packet */
#define XCP_PACKET_ID_STIM_MAX  0xBFu   /**< Stimulation Packet */
#define XCP_PACKET_ID_DAQ_MAX   0xFBu   /**< DAQ Packet */
#define XCP_PACKET_ID_SERV      0xFCu   /**< Service Packet */
#define XCP_PACKET_ID_EV        0xFDu   /**< Event Packet */
#define XCP_PACKET_ID_ERR       0xFEu   /**< Error Packet */
#define XCP_PACKET_ID_RES       0xFFu   /**< Response Packet */
/** \} */

/** \name Xcp_EventChannel_Status
 *  \{ */
#define XCP_STATUSBIT_DAQ_STARTED                  0x01u
#define XCP_STATUSBIT_DAQ_ERR_OVERLOAD             0x02u
#define XCP_STATUSBIT_STIM_STARTED                 0x10u
#define XCP_STATUSBIT_STIM_ERR_NO_DATA_AVAILABLE   0x20u
/** \} */

/** \name Xcp_GetState
 *  \{ */
#define XCP_STATE_DAQ_HAS_STOPPED             0x01u
#define XCP_STATE_ALL_STIM_DATA_RECEIVED      0x02u
/** \} */

/** \name Indication of time out Infotype at STIM
 *  \{ */
#define XCP_EV_STIM_TIMEOUT_INFOTYPE_EVENTCHANNEL  0u  /**< Event channel number */
#define XCP_EV_STIM_TIMEOUT_INFOTYPE_DAQLISTNO     1u  /**< Daq list number */
/** \} */

/** \name Listing of all Frame Types in combined mode
 *  \{ */
#define XCP_PACKET_TYPE_NONE                  0x00u                                                             /**< None */
#define XCP_PACKET_TYPE_VARIABLE              0x80u                                                             /**< Frame is variable - allowed types are set additionally */
/** \} */

/** \name RX-Frames
 *  \{ */
#define XCP_PACKET_TYPE_CMD                   0x01u                                                             /**< Command */
#define XCP_PACKET_TYPE_STIM                  0x02u                                                             /**< STIM */
#define XCP_PACKET_TYPE_CMD_STIM              (XCP_PACKET_TYPE_CMD | XCP_PACKET_TYPE_STIM)                      /**< Command, STIM */
#define XCP_PACKET_TYPE_VARIABLE_RX           (XCP_PACKET_TYPE_VARIABLE | XCP_PACKET_TYPE_CMD_STIM)             /**< Variable RX-frame */
/** \} */

/** \name TX-Frames
 *  \{ */
#define XCP_PACKET_TYPE_RES_ERR               0x04u                                                             /**< Response, Error */
#define XCP_PACKET_TYPE_EV_SERV               0x08u                                                             /**< Event, Service */
#define XCP_PACKET_TYPE_DAQ                   0x10u                                                             /**< DAQ */
#define XCP_PACKET_TYPE_RES_ERR_EV_SERV       (XCP_PACKET_TYPE_RES_ERR | XCP_PACKET_TYPE_EV_SERV)               /**< Response, Error, Event, Service */
#define XCP_PACKET_TYPE_RES_ERR_DAQ           (XCP_PACKET_TYPE_RES_ERR | XCP_PACKET_TYPE_DAQ)                   /**< Response, Error, DAQ */
#define XCP_PACKET_TYPE_EV_SERV_DAQ           (XCP_PACKET_TYPE_EV_SERV | XCP_PACKET_TYPE_DAQ)                   /**< Event, Service, DAQ */
#define XCP_PACKET_TYPE_RES_ERR_EV_SERV_DAQ   (XCP_PACKET_TYPE_RES_ERR_EV_SERV | XCP_PACKET_TYPE_DAQ)           /**< Response, Error, Event, Service, DAQ */
#define XCP_PACKET_TYPE_VARIABLE_TX           (XCP_PACKET_TYPE_VARIABLE | XCP_PACKET_TYPE_RES_ERR_EV_SERV_DAQ)  /**< Variable TX-frame */
/** \} */

/* --- Unused / reserved values ------------------------------------------------------ */


#define XCP_EVENT_CHANNEL_NOT_USED  0xFFFFu     /**< Id of empty / not used Event Channel */
#define XCP_PDU_ID_UNKNOWN          0xFFu       /**< Default XcpPduId of not recognized data packet */
#define XCP_INVALID_PROTLAYER_ID    0xFFu       /**< Invalid Protocol Layer Id */

/** \name Product lines
 *  \{ */
#define XCP_PRODUCT_LINE_OTHER      0u         /**< Macro supports product line OTHER */
#define XCP_PRODUCT_LINE_CSMOSAR    1u         /**< Macro supports product line CSMOSAR */
#define XCP_PRODUCT_LINE_MDG1       2u         /**< Macro supports product line MDG1 */
/** \} */

/** \name Possible error reactions for OM_OPTIMIZATION
 *  \{ */
#define XCP_OM_ODT_OPTIMIZATION_ERR_FALLBACK_TO_OM_DEFAULT  0u
#define XCP_OM_ODT_OPTIMIZATION_ERR_ABORT_CONFIGURATION     1u
/** \} */


/***************************************************************************************************
* Type definitions
***************************************************************************************************/
typedef struct
{
  uint8 Dummy_u8;
}Xcp_ConfigType;

typedef uint8 Xcp_PacketType_t;         /**< Transmit Frame Type */

/* Address pointers */
typedef const uint8* Xcp_AdrPtrConst;   /**< Address-Pointer to data of an unknown type. Shall be used in XCP if addresses are used */
typedef uint8* Xcp_AdrPtr;              /**< Const address-pointer to data of an unknown type. Shall be used in XCP if addresses for const data are used */
typedef uint8 Xcp_PduIdType;            /**< Xcp_PduIdType is used for internal PduIds, it is always uint8 */

/** Error codes */
typedef enum
{
  XCP_ERR_CMD_SYNCH                     = 0x00u,  /**< Command processor synchronization */
  XCP_ERR_CMD_BUSY                      = 0x10u,  /**< Command was not executed */
  XCP_ERR_DAQ_ACTIVE                    = 0x11u,  /**< Command rejected because DAQ is running */
  XCP_ERR_PGM_ACTIVE                    = 0x12u,  /**< Command rejected because PGM is running */
  XCP_ERR_CMD_UNKNOWN                   = 0x20u,  /**< Unknown command or not implemented optional command */
  XCP_ERR_CMD_SYNTAX                    = 0x21u,  /**< Command syntax invalid */
  XCP_ERR_OUT_OF_RANGE                  = 0x22u,  /**< Command syntax valid but command parameter(s) out of range */
  XCP_ERR_WRITE_PROTECTED               = 0x23u,  /**< The memory location is write protected */
  XCP_ERR_ACCESS_DENIED                 = 0x24u,  /**< The memory location is not accessible */
  XCP_ERR_ACCESS_LOCKED                 = 0x25u,  /**< Access denied, Seed & Key is required */
  XCP_ERR_PAGE_NOT_VALID                = 0x26u,  /**< Selected page not available */
  XCP_ERR_MODE_NOT_VALID                = 0x27u,  /**< Selected page mode not available */
  XCP_ERR_SEGMENT_NOT_VALID             = 0x28u,  /**< Selected segment not valid */
  XCP_ERR_SEQUENCE                      = 0x29u,  /**< Sequence error */
  XCP_ERR_DAQ_CONFIG                    = 0x2Au,  /**< DAQ configuration not valid */
  XCP_ERR_MEMORY_OVERFLOW               = 0x30u,  /**< Memory overflow error */
  XCP_ERR_GENERIC                       = 0x31u,  /**< Generic error */
  XCP_ERR_VERIFY                        = 0x32u,  /**< The slave internal program verify routine detects an error */
  XCP_ERR_RES_TEMP_NOT_ACCESS           = 0x33u,  /**< Access to the requested resource is temporary not possible */
  XCP_ERR_SUBCMD_UNKNOWN                = 0x34u,  /**< Unknown sub command or not implemented optional sub command */
  /* Following Error Codes are additional to ASAM and not sent to XCP master */
  XCP_NO_ACCESS_HIDE                    = 0xFDu,  /**< Internal usage - ACCESS_DENIED, but hidden to XCP master by sending zero or random values */
  XCP_NO_RESPONSE                       = 0xFEu,  /**< Internal usage - All OK, but don't send any response */
  XCP_NO_ERROR                          = 0xFFu   /**< Internal usage - All OK, send positive response */
}Xcp_ErrorCode;

/** Dynamic DAQ command sequence */
typedef enum
{
  XCP_DAQ_STATE_NO_DAQ = 0u,
  XCP_DAQ_STATE_FREE_DAQ,
  XCP_DAQ_STATE_ALLOC_DAQ,
  XCP_DAQ_STATE_ALLOC_ODT,
  XCP_DAQ_STATE_ALLOC_ODT_ENTRY,
  XCP_DAQ_STATE_WRITE_DAQ,
  XCP_DAQ_STATE_PREPARE_START,
  XCP_DAQ_STATE_SHIFTING,
  XCP_DAQ_STATE_READY_TO_RUN,
  XCP_DAQ_STATE_RUNNING
}Xcp_DaqState_t;

/** XCP_DAQ_OVERLOAD_INDICATION */
typedef enum
{
  XCP_DAQ_NO_OVERLOAD_INDICATION = 0u,
  XCP_DAQ_OVERLOAD_INDICATION_PID,
  XCP_DAQ_OVERLOAD_INDICATION_EVENT
}Xcp_Overload_t;

#define XCP_OVERLOAD_INDICATION_PID_BIT    0x80u

/** XCP_IDENTIFICATION_FIELD_TYPE */
typedef enum
{
  XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE = 1u,
  XCP_IDENTIFICATION_FIELD_TYPE_RELATIVE_BYTE = 2u,
  XCP_IDENTIFICATION_FIELD_TYPE_RELATIVE_WORD = 3u,
  XCP_IDENTIFICATION_FIELD_TYPE_RELATIVE_WORD_ALIGNED = 4u
}Xcp_IdField_t;

/** XCP_OPTIMISATION_TYPE */
typedef enum
{
  XCP_ODT_OPTIMIZATION_OM_DEFAULT             = 0u,
  XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_16         = 1u,
  XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_32         = 2u,
  XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_64         = 3u,
  XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_ALIGNMENT  = 4u, /* Also named OM_ODT_ALIGNMENT in v1.3, but with _TYPE it appears in the AML */
  XCP_ODT_OPTIMIZATION_OM_MAX_ENTRY_SIZE      = 5u
}Xcp_OdtOptimizationType_t;

/** XCP_CONSISTENCY_TYPE */
typedef enum
{
  XCP_CONSISTENCY_ODT       = 0u,
  XCP_CONSISTENCY_DAQ       = 1u,
  XCP_CONSISTENCY_EVENT     = 2u,
  XCP_CONSISTENCY_NONE      = 3u
}Xcp_Consistency_t;

/** XCP_TIMESTAMP_TYPE */
typedef enum
{
  XCP_TIMESTAMP_TYPE_NO_TIME_STAMP = 0u,
  XCP_TIMESTAMP_TYPE_ONE_BYTE = 1u,
  XCP_TIMESTAMP_TYPE_TWO_BYTE = 2u,
  XCP_TIMESTAMP_TYPE_FOUR_BYTE = 4u
}Xcp_Timestamp_t;

typedef enum
{
  XCP_CONTEXT_DAQ,
  XCP_CONTEXT_STIM,
  XCP_CONTEXT_DOWNLOAD,
  XCP_CONTEXT_UPLOAD,
  XCP_CONTEXT_CHECKSUM
}Xcp_ContextType_t;

typedef struct
{
  uint8  status_u8;
  uint8  numOfReceivedStimdata_u8;
  uint16 reserved_u16;
}Xcp_EventChannelStatus_t;

typedef struct
{
  Xcp_State_t XcpState_en;
  uint8       DaqState_u8;
  uint8       StimState_u8;
  uint8       reserved_u8;
}Xcp_GetState_t;

typedef struct
{
  uint8  Buffer_au8[8];                           /**< Data buffer with length of 8 */
  uint32 Length_u32;                              /**< Length, must be uint32 to align Buffer_au8 */
}Xcp_Cto8_t;

/** DET service IDs */
typedef enum
{
  /* Autosar */
  XCP_INITIALIZE_SID                    = 0x00u,  /**< Service Id for Xcp_Init */
  XCP_GET_VERSION_INFO_SID              = 0x01u,  /**< Service Id for Xcp_GetVersionInfo */
  XCP_TX_CONFIRMATION_SID               = 0x02u,  /**< Service Id for Xcp_<module>TxConfirmation */
  XCP_RX_INDICATION_SID                 = 0x03u,  /**< Service Id for Xcp_<module>RxIndication */
  XCP_MAINFUNCTION_SID                  = 0x04u,  /**< Service Id for Xcp_MainFunction */
  XCP_SET_TRANSMISSION_MODE_SID         = 0x05u,  /**< Service Id for Xcp_SetTransmissionMode */
  XCP_TRIGGER_TRANSMIT_SID              = 0x41u,  /**< Service Id for Xcp_<module>TriggerTransmit */
  /* RB */
  XCP_RECEIVE_SID                       = 0x50u,  /**< Service Id for Xcp_Receive */
  XCP_TRANSMIT_SID                      = 0x51u,  /**< Service Id for Xcp_<module>Transmit */
  XCP_CMD_SID                           = 0x52u,  /**< Service Id for Xcp_Cmd Functions */
  XCP_CONNECT_SID                       = 0x53u,  /**< Service Id for Xcp_<module>Connect */
  XCP_DISCONNECT_SID                    = 0x54u,  /**< Service Id for Xcp_<module>Disconnect */
  XCP_TRANSPORT_LAYER_CMD_SID           = 0x55u,  /**< Service Id for Xcp_<module>TransportLayerCmd */
  XCP_STIM_SID                          = 0x56u,  /**< Service Id for Xcp_Stim */
  XCP_DAQRAM_SID                        = 0x57u,  /**< Service Id for Xcp_DaqRam */
  XCP_PRODUCTLINE_SID                   = 0x60u   /**< Service Id for Product Line specific functions */
}Xcp_DetServiceId_t;

/** DET error IDs */
typedef enum
{
  /* Autosar */
  XCP_E_INV_POINTER                     = 0x01u,  /**< Error for invalid pointer */
  XCP_E_NOT_INITIALIZED                 = 0x02u,  /**< Error when module not initialized */
  XCP_E_INVALID_PDUID                   = 0x03u,  /**< Error when api call with wrong PDU ID */
  XCP_E_INIT_FAILED                     = 0x04u,  /**< Error when initialization of XCP failed */
  XCP_E_NULL_POINTER                    = 0x12u,  /**< Error when null pointer has been passed as an argument */
  /* RB: Init error */
  XCP_E_DAQ_SIZE_MISMATCH               = 0x30u,  /**< Error when sizeof(DAQ) is mismatched  */
  XCP_E_ODT_SIZE_MISMATCH               = 0x31u,  /**< Error when sizeof(ODT) is mismatched */
  XCP_E_ODTENTRY_SIZE_MISMATCH          = 0x32u,  /**< Error when sizeof(ODT_ENTRY) is mismatched */
  /* RB: ID checks */
  XCP_E_INVALID_TRANSPORT_LAYER_ID      = 0x40u,  /**< Error for Invalid transport layer id */
  XCP_E_INVALID_PROTOCOL_LAYER_ID       = 0x41u,  /**< Error for Invalid protocol layer id */
  /* RB: Connection checks */
  XCP_E_ALREADY_CONNECTED               = 0x50u,  /**< Error already connected and not available */
  XCP_E_DISCONNECT_FAILED               = 0x51u,  /**< Error disconnect failed */
  XCP_E_RESOURCE_DISABLED               = 0x52u,  /**< Error no resource are enabled and Xcp disabled */
  XCP_E_CONNECT_FAILED                  = 0x53u,  /**< Error not connected and invalid connect command */
  /* RB: Packet checks */
  XCP_E_DATA_PACKET_EMPTY               = 0x60u,  /**< Error data packet length is empty */
  XCP_E_DATA_PACKET_TOO_LONG            = 0x61u,  /**< Error packet length is too long */
  XCP_E_DATA_PACKET_NOK                 = 0x62u,  /**< Error when data length is bigger than 0 and not bigger than the buffer length */
  /* RB: DAQ checks*/
  /* XCP_E_DAQ_PLACEHOLDER              = 0x70u, */
  /* RB: STIM checks */
  XCP_E_RX_STIM_DISABLED                = 0x80u,  /**< Error for stim packet when STIM resource is disabled */
  XCP_E_STIM_PACKET_NOK                 = 0x81u,  /**< Error when received STIM packets for DAQ not in STIM mode, not started yet, or pdu length is wrong */
  XCP_E_NO_BUF_AVAIL                    = 0x82u,  /**< Error for stim when buffer is not available */
  /* RB: DAQRAM checks */
  XCP_E_DAQRAM_SHIFTING                 = 0x90u,  /**< Error for ram shifting when dest pointer is less than source pointer */
  XCP_E_DAQRAM_INCONSISTENCY            = 0x91u,  /**< Error when no active protocol layer or ram section is greater than max. section  */
  XCP_E_DAQRAM_ALLOCATION               = 0x92u,  /**< Error if daqram ptr is equal to NULL_PTR */
  /* RB: General checks */
  XCP_E_UNEXPECTED_FUNCTION_CALL        = 0xA0u,  /**< Error when unexpected function is called before expected */
  /* RB: Product Line specific checks */
  XCP_E_ECUSECU_NOK                     = 0xB0u   /**< Error for product line specific check */
}Xcp_DetErrorId_t;


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Function prototypes
***************************************************************************************************/


#endif   /* #ifndef XCP_TYPES_H */


