

#ifndef XCP_COMMANDS_H
#define XCP_COMMANDS_H

/***************************************************************************************************/
/** \defgroup CMDS Commands                                                                        */
/***************************************************************************************************/

/***************************************************************************************************/
/** \defgroup STD_CMDS Standard commands                                                           *
 ** \ingroup CMDS                                                                                  */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup CMD_CONNECT CONNECT
 *  \ingroup  STD_CMDS
 *  \brief    Set up connection with the slave
 *  \sa       Xcp_CmdConnect
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \{
 */

#define XCP_CMD_CONNECT_ID                        0xFF
#define XCP_CMD_CONNECT_LENGTH                    2u
#define XCP_RES_CONNECT_LENGTH                    8u

/** \brief CONNECT command structure */
typedef struct
{
  uint8  CommandCode_u8;                          /**< 0xFF */
  uint8  Mode_u8;                                 /**< Mode - 00 -> Normal; 01 -> User defined */
}Xcp_CmdConnect_t;

/** \brief CONNECT response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Resource_u8;                             /**< Resource */
  uint8  CommModeBasic_u8;                        /**< Communication Mode Basic */
  uint8  MaxCto_u8;                               /**< Maximum CTO */
  uint16 MaxDto_u16;                              /**< Maximum DTO */
  uint8  XcpProtocolLayerVersion_u8;              /**< Xcp Protocol Layer Version */
  uint8  XcpTransportLayerVersion_u8;             /**< Xcp Transport Layer Version */
}Xcp_ResConnect_t;
/** \} */

/**************************************************************************************************/
/** \defgroup CMD_DISCONNECT DISCONNECT
 *  \ingroup  STD_CMDS
 *  \brief    Disconnect from slave
 *  \sa       Xcp_CmdDisconnect
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \{
 */

#define XCP_CMD_DISCONNECT_ID                     0xFE
#define XCP_CMD_DISCONNECT_LENGTH                 1u
#define XCP_RES_DISCONNECT_LENGTH                 1u

/** \brief DISCONNECT command structure */
typedef struct
{
  uint8  CommandCode_u8;                          /**< 0xFE */
}Xcp_CmdDisconnect_t;

/** \brief DISCONNECT response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResDisconnect_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_STATUS GET_STATUS
 *  \ingroup  STD_CMDS
 *  \brief    Get current session status from slave
 *  \sa       Xcp_CmdGetStatus
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \{
 */

#define XCP_CMD_GET_STATUS_ID                     0xFD
#define XCP_CMD_GET_STATUS_LENGTH                 1u
#define XCP_RES_GET_STATUS_LENGTH                 6u

/** \brief GET_STATUS command structure */
typedef struct
{
  uint8  CommandCode_u8;                          /**< 0xFD */
}Xcp_CmdGetStatus_t;

/** \brief GET_STATUS response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Status_u8;                               /**< Current session status */
  uint8  ProtectionStatus_u8;                     /**< Current resource protection status */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 SessionConfigID_u16;                     /**< Session configuration id */
}Xcp_ResGetStatus_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_SYNCH SYNCH
 *  \ingroup  STD_CMDS
 *  \brief    Synchronize command execution after timeout
 *  \sa       Xcp_CmdSynch
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \note     SYNCH doesn't have an positive response, only negative response
 *  \{
 */

#define XCP_CMD_SYNCH_ID                          0xFC
#define XCP_CMD_SYNCH_LENGTH                      1u

/** \brief SYNCH command structure */
typedef struct
{
  uint8  CommandCode_u8;                          /**< 0xFC */
}Xcp_CmdSynch_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_COMM_MODE_INFO GET_COMM_MODE_INFO
 *  \ingroup  STD_CMDS
 *  \brief    Get communication mode info
 *  \sa       Xcp_CmdGetCommModeInfo
 *  \{
 */

#define XCP_CMD_GET_COMM_MODE_INFO_AVAILABLE      (XCP_COMMAND_GET_COMM_MODE_INFO)

#define XCP_CMD_GET_COMM_MODE_INFO_ID             0xFB
#define XCP_CMD_GET_COMM_MODE_INFO_LENGTH         1u
#define XCP_RES_GET_COMM_MODE_INFO_LENGTH         8u

/** \brief GET_COMM_MODE_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xFB */
}Xcp_CmdGetCommModeInfo_t;

/** \brief GET_COMM_MODE_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint8  CommModeOptional_u8;                     /**< COMM_MODE_OPTIONAL */
  uint8  Reserved2_u8;                            /**< Reserved */
  uint8  MaxBs_u8;                                /**< MAX_BS */
  uint8  MinSt_u8;                                /**< MIN_ST */
  uint8  QueueSize_u8;                            /**< QUEUE_SIZE */
  uint8  XcpDriverVerNum_u8;                      /**< Xcp Driver Version Number */
}Xcp_ResGetCommModeInfo_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_ID GET_ID
 *  \ingroup  STD_CMDS
 *  \brief    Get identification from slave
 *  \sa       Xcp_CmdGetId
 *  \{
 */

#define XCP_CMD_GET_ID_AVAILABLE                  (XCP_COMMAND_GET_ID)

#define XCP_CMD_GET_ID_ID                         0xFA
#define XCP_CMD_GET_ID_LENGTH                     2u
#define XCP_RES_GET_ID_LENGTH                     XCP_LENGTH_UNDEFINED
#define XCP_RES_GET_ID_LENGTH_MIN                 8u

/** \brief GET_ID command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xFA */
  uint8  ReqIdentificationType_u8;                /**< Requested Identification Type */
}Xcp_CmdGetId_t;

/** \brief GET_ID response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Mode_u8;                                 /**< Mode */
  uint16 Reserved_u16;                            /**< Reserved */
  uint32 Length_u32;                              /**< Length in Bytes */
#if (XCP_MAX_CTO>8)
  uint8  IdentificationByte_au8[XCP_MAX_CTO-8u];  /**< Position 8..MAX_CTO-1 */
#endif
}Xcp_ResGetId_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_SET_REQUEST SET_REQUEST
 *  \ingroup  STD_CMDS
 *  \brief    Request to save to Non-Volatile-Memory (NvM)
 *  \sa       Xcp_CmdSetRequest
 *  \note     This command is directly controlled with the switch XCP_RESUME_MODE.
 *            It is not useful to enable XCP_RESUME_MODE but not enable the respective CMD, therefore no switching-defines are generated

 *  \{
 */

#define XCP_CMD_SET_REQUEST_ID                    0xF9
#define XCP_CMD_SET_REQUEST_LENGTH                4u
#define XCP_RES_SET_REQUEST_LENGTH                1u

/** \brief SET_REQUEST command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF9 */
  uint8  Mode_u8;                                 /**< Mode */
  uint16 SessionConfigID_u16;                     /**< Session configuration ID */
}Xcp_CmdSetRequest_t;

/** \brief SET_REQUEST response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResSetRequest_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_SEED GET_SEED
 *  \ingroup  STD_CMDS
 *  \brief    Get Seed for unlocking a protected resource
 *  \sa       Xcp_CmdGetSeed
 *  \{
 */

#define XCP_CMD_GET_SEED_AVAILABLE                (XCP_SEED_AND_KEY)

#define XCP_CMD_GET_SEED_ID                       0xF8
#define XCP_CMD_GET_SEED_LENGTH                   3u
#define XCP_RES_GET_SEED_LENGTH                   XCP_LENGTH_UNDEFINED

/** \brief GET_SEED command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF8 */
  uint8  Mode_u8;                                 /**< 0 = (first part of) seed; 1 = remaining part of seed */
  uint8  Resource_u8;                             /**< if Mode=0 -> Resource ; Mode = 1 -> Do not care */
}Xcp_CmdGetSeed_t;

/** \brief GET_SEED response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  LengthOfSeed_u8;                         /**< Length of Seed */
  uint8  Seed_au8[XCP_MAX_CTO-2u];                /**< Position 2..MAX_CTO-1 */
}Xcp_ResGetSeed_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_UNLOCK UNLOCK
 *  \ingroup  STD_CMDS
 *  \brief    Send key for unlocking a protected resource
 *  \sa       Xcp_CmdUnlock
 *  \{
 */

#define XCP_CMD_UNLOCK_AVAILABLE                  (XCP_SEED_AND_KEY)

#define XCP_CMD_UNLOCK_ID                         0xF7
#define XCP_CMD_UNLOCK_LENGTH                     XCP_LENGTH_UNDEFINED
#define XCP_CMD_UNLOCK_LENGTH_MIN                 3u
#define XCP_RES_UNLOCK_LENGTH                     2u

/** \brief UNLOCK command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF7 */
  uint8  LengthOfKey_u8;                          /**< Length of Key */
  uint8  Key_au8[XCP_MAX_CTO-2u];                 /**< Position 2..MAX_CTO-1 */
}Xcp_CmdUnlock_t;

/** \brief UNLOCK response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  ProtectionStatus_u8;                     /**< Current resource protection status */
}Xcp_ResUnlock_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_SET_MTA SET_MTA
 *  \ingroup  STD_CMDS
 *  \brief    Set memory transfer address in slave
 *  \sa       Xcp_CmdSetMta
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \{
 */

#define XCP_CMD_SET_MTA_ID                        0xF6
#define XCP_CMD_SET_MTA_LENGTH                    8u
#define XCP_RES_SET_MTA_LENGTH                    1u

/** \brief SET_MTA command structure */
typedef struct {
  uint8       CommandCode_u8;                     /**< 0xF6 */
  uint8       Reserved_u8;                        /**< Reserved */
  uint8       Reserved2_u8;                       /**< Reserved */
  uint8       AddrExtension_u8;                   /**< Address Extension */
  Xcp_AdrPtr  Address_Ptr;                        /**< Address Pointer */
}Xcp_CmdSetMta_t;

/** \brief SET_MTA response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResSetMta_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_UPLOAD UPLOAD
 *  \ingroup  STD_CMDS
 *  \brief    Upload from slave to master
 *  \sa       Xcp_CmdUpload
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \{
 */

#define XCP_CMD_UPLOAD_ID                         0xF5
#define XCP_CMD_UPLOAD_LENGTH                     2u
#define XCP_RES_UPLOAD_LENGTH                     XCP_LENGTH_UNDEFINED

/** \brief UPLOAD command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF5 */
  uint8  NumOfDataElements_u8;                    /**< Number of Data Elements */
}Xcp_CmdUpload_t;

/** \brief UPLOAD response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  DataElement_au8[XCP_MAX_CTO-1u];         /**< Position 1..MAX_CTO-1 */
}Xcp_ResUpload_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_SHORT_UPLOAD SHORT_UPLOAD
 *  \ingroup  STD_CMDS
 *  \brief    Upload from slave to master (Short version)
 *  \sa       Xcp_CmdShortUpload
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \{
 */

#define XCP_CMD_SHORT_UPLOAD_ID                   0xF4
#define XCP_CMD_SHORT_UPLOAD_LENGTH               8u
#define XCP_RES_SHORT_UPLOAD_LENGTH               XCP_LENGTH_UNDEFINED

/** \brief SHORT_UPLOAD command structure */
typedef struct {
  uint8       CommandCode_u8;                     /**< 0xF4 */
  uint8       NumOfDataElements_u8;               /**< Number of Data Elements */
  uint8       Reserved_u8;                        /**< Reserved */
  uint8       AddrExtension_u8;                   /**< Address Extension */
  Xcp_AdrPtr  Address_Ptr;                        /**< Address Pointer */
}Xcp_CmdShortUpload_t;

/** \brief SHORT_UPLOAD response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  DataElement_au8[XCP_MAX_CTO-1u];         /**< Position 1..MAX_CTO-1 */
}Xcp_ResShortUpload_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_BUILD_CHECKSUM BUILD_CHECKSUM
 *  \ingroup  STD_CMDS
 *  \brief    Build checksum over memory range
 *  \sa       Xcp_CmdBuildChecksum
 *  \{
 */

#define XCP_CMD_BUILD_CHECKSUM_AVAILABLE          (XCP_COMMAND_CHECKSUM)

#define XCP_CMD_BUILD_CHECKSUM_ID                 0xF3
#define XCP_CMD_BUILD_CHECKSUM_LENGTH             8u
#define XCP_RES_BUILD_CHECKSUM_LENGTH             8u

/** \brief BUILD_CHECKSUM command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF3 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 Reserved_u16;                            /**< Reserved */
  uint32 BlockSize_u32;                           /**< Size of block from which Checksum should be calculated */
}Xcp_CmdBuildChecksum_t;

/** \brief BUILD_CHECKSUM response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  ChecksumType_u8;                         /**< Type of checksum */
  uint16 Reserved_u16;                            /**< Reserved */
  uint32 Checksum_u32;                            /**< Calculated checksum */
}Xcp_ResBuildChecksum_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_TRANSPORT_LAYER_CMD TRANSPORT_LAYER_CMD
 *  \ingroup  STD_CMDS
 *  \brief    Refer to Transport Layer specific command
 *  \sa       Xcp_CmdTransportLayerCmd
 *  \note     This command cannot be switched off. Therefore no switching-defines are generated
 *  \{
 */

#define XCP_CMD_TRANSPORT_LAYER_CMD_ID            0xF2
#define XCP_CMD_TRANSPORT_LAYER_CMD_LENGTH        XCP_LENGTH_UNDEFINED
#define XCP_CMD_TRANSPORT_LAYER_CMD_LENGTH_MIN    2u
#define XCP_RES_TRANSPORT_LAYER_CMD_LENGTH        8u

/** \brief TRANSPORT_LAYER_CMD command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF2 */
  uint8  SubCmdcode_u8;                           /**< Sub command code */
  uint8  Parameters_au8[XCP_MAX_CTO-2u];          /**< Position 2..MAX_CTO-1 */
}Xcp_CmdTransportLayerCmd_t;

/** \brief TRANSPORT_LAYER_CMD response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Data_au8[XCP_MAX_CTO-1u];                /**< Position 1..MAX_CTO-1 */
}Xcp_ResTransportLayerCmd_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_USER_CMD USER_CMD
 *  \ingroup  STD_CMDS
 *  \brief    Refer to user-defined command
 *  \sa       Xcp_CmdUserCmd
 *  \{
 */

#define XCP_CMD_USER_CMD_AVAILABLE                (XCP_COMMAND_USER_CMD)

#define XCP_CMD_USER_CMD_ID                       0xF1
#define XCP_CMD_USER_CMD_LENGTH                   XCP_LENGTH_UNDEFINED
#define XCP_CMD_USER_CMD_LENGTH_MIN               2u
#define XCP_RES_USER_CMD_LENGTH                   XCP_LENGTH_UNDEFINED

/** \brief USER_CMD command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF1 */
  uint8  SubCommandCode_u8;                       /**< Sub Command Code */
  uint8  Parameters_au8[XCP_MAX_CTO-2u];          /**< Position 2..MAX_CTO-1 */
}Xcp_CmdUserCmd_t;

/** \brief USER_CMD response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  DataElement_au8[XCP_MAX_CTO-1u];         /**< Position 1..MAX_CTO-1 */
}Xcp_ResUserCmd_t;
/** \} */


/***************************************************************************************************/
/** \defgroup CAL_CMDS Calibration commands                                                        *
 ** \ingroup CMDS                                                                                  */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup CMD_DOWNLOAD DOWNLOAD
 *  \ingroup  CAL_CMDS
 *  \brief    Download from master to slave
 *  \sa       Xcp_CmdDownload
 *  \{
 */

#define XCP_CMD_DOWNLOAD_AVAILABLE                (XCP_CALIBRATION_CAL)

#define XCP_CMD_DOWNLOAD_ID                       0xF0
#define XCP_CMD_DOWNLOAD_LENGTH                   XCP_LENGTH_UNDEFINED
#define XCP_CMD_DOWNLOAD_LENGTH_MIN               3u
#define XCP_RES_DOWNLOAD_LENGTH                   1u

/** \brief DOWNLOAD command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xF0 */
  uint8  NumOfDataElements_u8;                    /**< Number of data elements */
  uint8  DataElement_au8[XCP_MAX_CTO-2u];         /**< Position 2..MAX_CTO-1 */
}Xcp_CmdDownload_t;

/** \brief DOWNLOAD response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResDownload_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_DOWNLOAD_NEXT DOWNLOAD_NEXT
 *  \ingroup  CAL_CMDS
 *  \brief    Download from master to slave (Block mode)
 *  \sa       Xcp_CmdDownloadNext
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_DOWNLOAD_NEXT_AVAILABLE           (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_DOWNLOAD_NEXT_ID                  0xEF
#define XCP_CMD_DOWNLOAD_NEXT_LENGTH              XCP_LENGTH_UNDEFINED
#define XCP_CMD_DOWNLOAD_NEXT_LENGTH_MIN          3u
#define XCP_RES_DOWNLOAD_NEXT_LENGTH              1u
#define XCP_ERR_SEQ_DOWNLOAD_NEXT_LENGTH          3u

/** \brief DOWNLOAD_NEXT command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xEF */
  uint8  NumOfDataElements_u8;                    /**< Number of data elements */
  uint8  DataElement_au8[XCP_MAX_CTO-2u];         /**< Position 2..MAX_CTO-1 */
}Xcp_CmdDownloadNext_t;

/** \brief DOWNLOAD_NEXT positive response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResDownloadNext_t;

/** \brief DOWNLOAD_NEXT error response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFE */
  uint8  ErrCode_u8;                              /**< ERR_SEQUENCE 0x29 */
  uint8  NumOfDataElements_u8;                    /**< Number of expected data elements */
}Xcp_ErrResDownloadNext_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_DOWNLOAD_MAX DOWNLOAD_MAX
 *  \ingroup  CAL_CMDS
 *  \brief    Download from master to slave (Fixed size)
 *  \sa       Xcp_CmdDownloadMax
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_DOWNLOAD_MAX_AVAILABLE            (XCP_CALIBRATION_CAL)

#define XCP_CMD_DOWNLOAD_MAX_ID                   0xEE
#define XCP_CMD_DOWNLOAD_MAX_LENGTH               XCP_LENGTH_UNDEFINED
#define XCP_CMD_DOWNLOAD_MAX_LENGTH_MIN           8u    /**< It is not possible that transport layer has smaller MAX_CTO than 8 */
#define XCP_RES_DOWNLOAD_MAX_LENGTH               1u

/** \brief DOWNLOAD_MAX command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xEE */
  uint8  DataElement_au8[XCP_MAX_CTO-1u];         /**< Position 1..MAX_CTO-1 */
}Xcp_CmdDownloadMax_t;

/** \brief DOWNLOAD_MAX response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResDownloadMax_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_SHORT_DOWNLOAD SHORT_DOWNLOAD
 *  \ingroup  CAL_CMDS
 *  \brief    Download from master to slave (Short version)
 *  \sa       Xcp_CmdShortDownload
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_SHORT_DOWNLOAD_AVAILABLE          (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_MAX_CTO > 8)) ? STD_ON : STD_OFF)

#define XCP_CMD_SHORT_DOWNLOAD_ID                 0xED
#define XCP_CMD_SHORT_DOWNLOAD_LENGTH             XCP_LENGTH_UNDEFINED
/* Min length of command ShortDownload is set to 8 instead of 9, because ERR_CMD_UNKNOWN must be send when MAX_CTO is 8
   If min length would be set to 9, XCP_ERR_CMD_SYNTAX would be sent.*/
#define XCP_CMD_SHORT_DOWNLOAD_LENGTH_MIN         8u
#define XCP_RES_SHORT_DOWNLOAD_LENGTH             1u

/** \brief SHORT_DOWNLOAD command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xED */
  uint8  NumOfDataElements_u8;                    /**< Number of Data Elements */
  uint8  Reserved_u8;                             /**< Reserved */
  uint8  AddrExtension_u8;                        /**< Address Extension */
  Xcp_AdrPtr  Address_Ptr;                        /**< Address Pointer */
#if (XCP_MAX_CTO>8)
  uint8  DataElement_au8[XCP_MAX_CTO-8u];         /**< Position 8..MAX_CTO-1 */
#endif
}Xcp_CmdShortDownload_t;

/** \brief SHORT_DOWNLOAD response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResShortDownload_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_MODIFY_BITS MODIFY_BITS
 *  \ingroup  CAL_CMDS
 *  \brief    Modify Bits
 *  \sa       Xcp_CmdModifyBits
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_MODIFY_BITS_AVAILABLE             (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_COMMAND_MODIFY_BITS == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_MODIFY_BITS_ID                    0xEC
#define XCP_CMD_MODIFY_BITS_LENGTH                6u
#define XCP_RES_MODIFY_BITS_LENGTH                1u

/** \brief MODIFY_BITS command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xEC */
  uint8  ShiftValue_u8;                           /**< Shift value (s) */
  uint16 ANDmask_u16;                             /**< AND Mask(MA) */
  uint16 XORmask_u16;                             /**< XOR Mask(MX) */
}Xcp_CmdModifyBits_t;

/** \brief MODIFY_BITS response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResModifyBits_t;
/** \} */


/***************************************************************************************************/
/** \defgroup PAG_CMDS Page switching commands                                                     *
 ** \ingroup CMDS                                                                                  */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup CMD_SET_CAL_PAGE SET_CAL_PAGE
 *  \ingroup  PAG_CMDS
 *  \brief    Set calibration page
 *  \sa       Xcp_CmdSetCalPage
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_SET_CAL_PAGE_AVAILABLE            (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_PAGE_SWITCHING_PAG == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_SET_CAL_PAGE_ID                   0xEB
#define XCP_CMD_SET_CAL_PAGE_LENGTH               4u
#define XCP_RES_SET_CAL_PAGE_LENGTH               1u

/** \brief SET_CAL_PAGE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xEB */
  uint8  Mode_u8;                                 /**< Mode */
  uint8  LogicalDataSegNum_u8;                    /**< Logical data segment number */
  uint8  LogicalDataPgNum_u8;                     /**< Logical data page number */
}Xcp_CmdSetCalPage_t;

/** \brief SET_CAL_PAGE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResSetCalPage_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_CAL_PAGE GET_CAL_PAGE
 *  \ingroup  PAG_CMDS
 *  \brief    Get calibration page
 *  \sa       Xcp_CmdGetCalPage
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_CAL_PAGE_AVAILABLE            (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_PAGE_SWITCHING_PAG == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_CAL_PAGE_ID                   0xEA
#define XCP_CMD_GET_CAL_PAGE_LENGTH               3u
#define XCP_RES_GET_CAL_PAGE_LENGTH               4u

/** \brief GET_CAL_PAGE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xEA */
  uint8  AccessMode_u8;                           /**< Access Mode */
  uint8  LogicalDataSegNum_u8;                    /**< Logical data segment number */
}Xcp_CmdGetCalPage_t;

/** \brief GET_CAL_PAGE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint8  Reserved2_u8;                            /**< Reserved */
  uint8  LogicalDataPgNum_u8;                     /**< Logical Data page number */
}Xcp_ResGetCalPage_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_PAG_PROCESSOR_INFO GET_PAG_PROCESSOR_INFO
 *  \ingroup  PAG_CMDS
 *  \brief    Get general information on PAG processor
 *  \sa       Xcp_CmdGetPagProcessorInfo
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_PAG_PROCESSOR_INFO_AVAILABLE  (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_PAGE_SWITCHING_PAG == STD_ON) && (XCP_COMMANDS_GET_PAG_INFO == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_PAG_PROCESSOR_INFO_ID         0xE9
#define XCP_CMD_GET_PAG_PROCESSOR_INFO_LENGTH     1u
#define XCP_RES_GET_PAG_PROCESSOR_INFO_LENGTH     3u

/** \brief GET_PAG_PROCESSOR_INFO command structure */
typedef struct
{
  uint8  CommandCode_u8;                          /**< 0xE9 */
}Xcp_CmdGetPagProcessorInfo_t;

/** \brief GET_PAG_PROCESSOR_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  MaxSegment_u8;                           /**< MAX_SEGMENT */
  uint8  PagProperties_u8;                        /**< PAG_PROPERTIES */
}Xcp_ResGetPagProcessorInfo_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_SEGMENT_INFO GET_SEGMENT_INFO
 *  \ingroup  PAG_CMDS
 *  \brief    Get specific information for a SEGMENT
 *  \sa       Xcp_CmdGetSegmentInfo
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_SEGMENT_INFO_AVAILABLE        (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_PAGE_SWITCHING_PAG == STD_ON) && (XCP_COMMANDS_GET_PAG_INFO == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_SEGMENT_INFO_ID               0xE8
#define XCP_CMD_GET_SEGMENT_INFO_LENGTH           5u
#define XCP_RES_GET_SEGMENT_INFO_MODE0_LENGTH     8u
#define XCP_RES_GET_SEGMENT_INFO_MODE1_LENGTH     6u
#define XCP_RES_GET_SEGMENT_INFO_MODE2_LENGTH     8u
#define XCP_RES_GET_SEGMENT_INFO_MODE0_MODE2_LEN  8u

/** \brief GET_SEGMENT_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE8 */
  uint8  Mode_u8;                                 /**< Mode */
  uint8  SegmentNum_u8;                           /**< SEGMENT_NUMBER */
  uint8  SegmentInfo_u8;                          /**< SEGMENT_INFO */
  uint8  MappingIndex_u8;                         /**< MAPPING_INDEX */
}Xcp_CmdGetSegmentInfo_t;

/** \brief GET_SEGMENT_INFO response structure for Mode0 */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 Reserved_u16;                            /**< Reserved */
  uint32 BasicInfo_u32;                           /**< BASIC_INFO */
}Xcp_ResGetSegmentInfo_Mode0_t;

/** \brief GET_SEGMENT_INFO response structure for Mode1 */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  MaxPages_u8;                             /**< MAX_PAGES */
  uint8  AddrExtension_u8;                        /**< Address Extension */
  uint8  MaxMapping_u8;                           /**< MAX_MAPPING (number of mapped address ranges within this SEGMENT) */
  uint8  CompressionMethod_u8;                    /**< Compression method */
  uint8  EncryptionMethod_u8;                     /**< Encryption method */
}Xcp_ResGetSegmentInfo_Mode1_t;

/** \brief GET_SEGMENT_INFO response structure for Mode2 */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 Reserved_u16;                            /**< Reserved */
  uint32 MappingInfo_u32;                         /**< MAPPING_INFO */
}Xcp_ResGetSegmentInfo_Mode2_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_PAGE_INFO GET_PAGE_INFO
 *  \ingroup  PAG_CMDS
 *  \brief    Get specific information for a PAGE
 *  \sa       Xcp_CmdGetPageInfo
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_PAGE_INFO_AVAILABLE           (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_PAGE_SWITCHING_PAG == STD_ON) && (XCP_COMMANDS_GET_PAG_INFO == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_PAGE_INFO_ID                  0xE7
#define XCP_CMD_GET_PAGE_INFO_LENGTH              4u
#define XCP_RES_GET_PAGE_INFO_LENGTH              3u

/** \brief GET_PAGE_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE7 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint8  SegmentNum_u8;                           /**< SEGMENT_NUMBER */
  uint8  PageNumber_u8;                           /**< PAGE_NUMBER */
}Xcp_CmdGetPageInfo_t;

/** \brief GET_PAGE_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  PageProperties_u8;                       /**< PAGE_PROPERTIES */
  uint8  InitSegment_u8;                          /**< INIT_SEGMENT */
}Xcp_ResGetPageInfo_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_SET_SEGMENT_MODE SET_SEGMENT_MODE
 *  \ingroup  PAG_CMDS
 *  \brief    Set mode for a SEGMENT
 *  \attention The command SET_SEGMENT_MODE (0xE6) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_SET_SEGMENT_MODE_AVAILABLE        (STD_OFF)

#define XCP_CMD_SET_SEGMENT_MODE_ID               0xE6
#define XCP_CMD_SET_SEGMENT_MODE_LENGTH           3u
#define XCP_RES_SET_SEGMENT_MODE_LENGTH           1u

/** \brief SET_SEGMENT_MODE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE6 */
  uint8  Mode_u8;                                 /**< Mode */
  uint8  SegmentNum_u8;                           /**< SEGMENT_NUMBER */
}Xcp_CmdSetSegmentMode_t;

/** \brief SET_SEGMENT_MODE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResSetSegmentMode_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_SEGMENT_MODE GET_SEGMENT_MODE
 *  \ingroup  PAG_CMDS
 *  \brief    Get mode for a SEGMENT
 *  \attention The command GET_SEGMENT_MODE (0xE5) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_SEGMENT_MODE_AVAILABLE        (STD_OFF)

#define XCP_CMD_GET_SEGMENT_MODE_ID               0xE5
#define XCP_CMD_GET_SEGMENT_MODE_LENGTH           3u
#define XCP_RES_GET_SEGMENT_MODE_LENGTH           3u

/** \brief GET_SEGMENT_MODE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE5 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint8  SegmentNum_u8;                           /**< SEGMENT_NUMBER */
}Xcp_CmdGetSegmentMode_t;

/** \brief GET_SEGMENT_MODE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint8  Mode_u8;                                 /**< Mode */
}Xcp_ResGetSegmentMode_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_COPY_CAL_PAGE COPY_CAL_PAGE
 *  \ingroup  PAG_CMDS
 *  \brief    Copy PAGE
 *  \sa       Xcp_CmdCopyCalPage
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_COPY_CAL_PAGE_AVAILABLE           (((XCP_CALIBRATION_CAL == STD_ON) && (XCP_PAGE_SWITCHING_PAG == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_COPY_CAL_PAGE_ID                  0xE4
#define XCP_CMD_COPY_CAL_PAGE_LENGTH              5u
#define XCP_RES_COPY_CAL_PAGE_LENGTH              1u

/** \brief COPY_CAL_PAGE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE4 */
  uint8  LogicalDataSegNumSource_u8;              /**< Logical data segment number source */
  uint8  LogicalDataSegPageNumSource_u8;          /**< Logical data page number source */
  uint8  LogicalDataSegNumDest_u8;                /**< Logical data segment number destination */
  uint8  LogicalDataSegPageNumDest_u8;            /**< Logical data page number destination */
}Xcp_CmdCopyCalPage_t;

/** \brief COPY_CAL_PAGE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResCopyCalPage_t;
/** \} */


/***************************************************************************************************/
/** \defgroup BDAQ_CMDS Basic data acquisition and stimulation commands                            *
 ** \ingroup CMDS                                                                                  */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup CMD_SET_DAQ_PTR SET_DAQ_PTR
 *  \ingroup  BDAQ_CMDS
 *  \brief    Set pointer to ODT Entry
 *  \sa       Xcp_CmdSetDaqPtr
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_SET_DAQ_PTR_AVAILABLE             (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_SET_DAQ_PTR_ID                    0xE2
#define XCP_CMD_SET_DAQ_PTR_LENGTH                6u
#define XCP_RES_SET_DAQ_PTR_LENGTH                1u

/** \brief SET_DAQ_PTR command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE2 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 DaqListNum_u16;                          /**< Daq List Number */
  uint8  OdtNum_u8;                               /**< ODT Number*/
  uint8  OdtEntryNum_u8;                          /**< ODT Entry number */
}Xcp_CmdSetDaqPtr_t;

/** \brief SET_DAQ_PTR response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResSetDaqPtr_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_WRITE_DAQ WRITE_DAQ
 *  \ingroup  BDAQ_CMDS
 *  \brief    Write element in ODT Entry
 *  \sa       Xcp_CmdWriteDaq
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_WRITE_DAQ_AVAILABLE               (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_WRITE_DAQ_ID                      0xE1
#define XCP_CMD_WRITE_DAQ_LENGTH                  8u
#define XCP_RES_WRITE_DAQ_LENGTH                  1u

/** \brief WRITE_DAQ command structure */
typedef struct {
  uint8       CommandCode_u8;                     /**< 0xE1 */
  uint8       BitOffset_u8;                       /**< Bit offset position */
  uint8       Size_u8;                            /**< Size of DAQ element */
  uint8       AddrExtension_u8;                   /**< Address Extension */
  Xcp_AdrPtr  Address_Ptr;                        /**< Address Pointer */
}Xcp_CmdWriteDaq_t;

/** \brief WRITE_DAQ response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResWriteDaq_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_SET_DAQ_LIST_MODE SET_DAQ_LIST_MODE
 *  \ingroup  BDAQ_CMDS
 *  \brief    Set mode for DAQ list
 *  \sa       Xcp_CmdSetDaqListMode
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_SET_DAQ_LIST_MODE_AVAILABLE       (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_SET_DAQ_LIST_MODE_ID              0xE0
#define XCP_CMD_SET_DAQ_LIST_MODE_LENGTH          8u
#define XCP_RES_SET_DAQ_LIST_MODE_LENGTH          1u

/** \brief SET_DAQ_LIST_MODE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE0 */
  uint8  Mode_u8;                                 /**< Mode */
  uint16 DaqListNum_u16;                          /**< DAQ list number */
  uint16 EventChannelNum_u16;                     /**< Event Channel Number */
  uint8  TransmissionRatePrescaler_u8;            /**< Transmission rate prescaler (=>1) */
  uint8  DaqListPriority_u8;                      /**< DAQ list priority (0xFF = highest) */
}Xcp_CmdSetDaqListMode_t;

/** \brief SET_DAQ_LIST_MODE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResSetDaqListMode_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_START_STOP_DAQ_LIST START_STOP_DAQ_LIST
 *  \ingroup  BDAQ_CMDS
 *  \brief    Start/Stop/Select DAQ list
 *  \sa       Xcp_CmdStartStopDaqList
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_START_STOP_DAQ_LIST_AVAILABLE     (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_START_STOP_DAQ_LIST_ID            0xDE
#define XCP_CMD_START_STOP_DAQ_LIST_LENGTH        4u
#define XCP_RES_START_STOP_DAQ_LIST_LENGTH        2u

/** \brief START_STOP_DAQ_LIST command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xDE */
  uint8  Mode_u8;                                 /**< Mode */
  uint16 DaqListNum_u16;                          /**< DAQ list number */
}Xcp_CmdStartStopDaqList_t;

/** \brief START_STOP_DAQ_LIST response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  FirstPid_u8;                             /**< FIRST_PID */
}Xcp_ResStartStopDaqList_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_START_STOP_SYNCH START_STOP_SYNCH
 *  \ingroup  BDAQ_CMDS
 *  \brief    Start/Stop DAQ lists (Synchronously)
 *  \sa       Xcp_CmdStartStopSynch
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_START_STOP_SYNCH_AVAILABLE        (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_START_STOP_SYNCH_ID               0xDD
#define XCP_CMD_START_STOP_SYNCH_LENGTH           2u
#define XCP_RES_START_STOP_SYNCH_LENGTH           1u

/** \brief START_STOP_SYNCH command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xDD */
  uint8  Mode_u8;                                 /**< Mode */
}Xcp_CmdStartStopSynch_t;

/** \brief START_STOP_SYNCH response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResStartStopSynch_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_WRITE_DAQ_MULTIPLE WRITE_DAQ_MULTIPLE
 *  \ingroup  BDAQ_CMDS
 *  \brief    Write multiple elements in ODT
 *  \sa       Xcp_CmdWriteDaqMultiple
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_WRITE_DAQ_MULTIPLE_AVAILABLE      (((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_MAX_CTO >= 10) && (XCP_CMD_WRITE_DAQ_AVAILABLE == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_WRITE_DAQ_MULTIPLE_ID             0xC7
#define XCP_CMD_WRITE_DAQ_MULTIPLE_LENGTH         XCP_LENGTH_UNDEFINED
/* Min length of command WriteDaqMultiple is set to 8 instead of 10,
   because ERR_CMD_UNKNOWN must be send when MAX_CTO is < 10,
   this is provided in WriteDaqMultiple function, not in ReceiveCommand
   to avoid checking this for every command.*/
#define XCP_CMD_WRITE_DAQ_MULTIPLE_LENGTH_MIN     8u
#define XCP_RES_WRITE_DAQ_MULTIPLE_LENGTH         1u

/** \brief WRITE_DAQ_MULTIPLE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xC7 */
  uint8  NumDaq_u8;
  uint8  Data_au8[XCP_MAX_CTO-2u];                /**< Use Xcp_CmdWriteDaqMultiple_SingleElement_t to access data*/
}Xcp_CmdWriteDaqMultiple_t;

/** \brief Data structure to ease the access to the data from the command structure (located in Xcp_CmdWriteDaqMultiple_t::Data_au8) */
typedef struct {
  uint16      DummySelfDefined_u16;               /**< Dummy, not defined by ASAM! */
  uint8       BitOffset_u8;                       /**< Bit offset position */
  uint8       Size_u8;                            /**< Size of DAQ element */
  Xcp_AdrPtr  Address_Ptr;                        /**< Address Pointer */
  uint8       AddrExtension_u8;                   /**< Address Extension */
  uint8       Dummy_u8;                           /**< Dummy for alignment of the next element */
}Xcp_CmdWriteDaqMultiple_SingleElement_t;

/** \brief WRITE_DAQ_MULTIPLE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResWriteDaqMultiple_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_READ_DAQ READ_DAQ
 *  \ingroup  BDAQ_CMDS
 *  \brief    Read element from ODT Entry
 *  \sa       Xcp_CmdReadDaq
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_READ_DAQ_AVAILABLE                (((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_COMMAND_READ_DAQ == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_READ_DAQ_ID                       0xDB
#define XCP_CMD_READ_DAQ_LENGTH                   1u
#define XCP_RES_READ_DAQ_LENGTH                   8u

/** \brief READ_DAQ command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xDB */
}Xcp_CmdReadDaq_t;

/** \brief READ_DAQ response structure */
typedef struct {
  uint8       PacketId_u8;                        /**< 0xFF */
  uint8       BitOffset_u8;                       /**< Bit offset position */
  uint8       SizeOfDaqElement_u8;                /**< Size of DAQ element */
  uint8       AddrExtension_u8;                   /**< Address Extension */
  Xcp_AdrPtr  Address_Ptr;                        /**< Address Pointer */
}Xcp_ResReadDaq_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_DAQ_CLOCK GET_DAQ_CLOCK
 *  \ingroup  BDAQ_CMDS
 *  \brief    Get DAQ Clock from slave
 *  \sa       Xcp_CmdGetDaqClock
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_DAQ_CLOCK_AVAILABLE           (((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_TIMESTAMP == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_DAQ_CLOCK_ID                  0xDC
#define XCP_CMD_GET_DAQ_CLOCK_LENGTH              1u
#define XCP_RES_GET_DAQ_CLOCK_LENGTH              8u

/** \brief GET_DAQ_CLOCK command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xDC */
}Xcp_CmdGetDaqClock_t;

/** \brief GET_DAQ_CLOCK response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 Reserved_u16;                            /**< Reserved */
  uint32 Timestamp_u32;                           /**< Receive Timestamp */
}Xcp_ResGetDaqClock_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_DAQ_PROCESSOR_INFO GET_DAQ_PROCESSOR_INFO
 *  \ingroup  BDAQ_CMDS
 *  \brief    Get general information on DAQ processor
 *  \sa       Xcp_CmdGetDaqProcessorInfo
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_DAQ_PROCESSOR_INFO_AVAILABLE  (((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_COMMANDS_GET_DAQ_INFO == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_DAQ_PROCESSOR_INFO_ID         0xDA
#define XCP_CMD_GET_DAQ_PROCESSOR_INFO_LENGTH     1u
#define XCP_RES_GET_DAQ_PROCESSOR_INFO_LENGTH     8u

/** \brief GET_DAQ_PROCESSOR_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xDA */
}Xcp_CmdGetDaqProcInfo_t;

/** \brief GET_DAQ_PROCESSOR_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  DaqProperties_u8;                        /**< Daq Properties */
  uint16 MaxDaq_u16;                              /**< Max Daq */
  uint16 MaxEventChannel_u16;                     /**< Max Event Channel */
  uint8  MinDaq_u8;                               /**< Min Daq */
  uint8  DaqKeyByte_u8;                           /**< Daq key byte */
}Xcp_ResGetDaqProcInfo_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_DAQ_RESOLUTION_INFO GET_DAQ_RESOLUTION_INFO
 *  \ingroup  BDAQ_CMDS
 *  \brief    Get gerneral information on DAQ processing resolution
 *  \sa       Xcp_CmdGetDaqResolutionInfo
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_DAQ_RESOLUTION_INFO_AVAILABLE (((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_COMMANDS_GET_DAQ_INFO == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_DAQ_RESOLUTION_INFO_ID        0xD9
#define XCP_CMD_GET_DAQ_RESOLUTION_INFO_LENGTH    1u
#define XCP_RES_GET_DAQ_RESOLUTION_INFO_LENGTH    8u

/** \brief GET_DAQ_RESOLUTION_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD9 */
}Xcp_CmdGetDaqResolutionInfo_t;

/** \brief GET_DAQ_RESOLUTION_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  GranularityOdtEntrySizeDaq_u8;           /**< Granularity ODT Entry Size DAQ direction */
  uint8  MaxOdtEntrySizeDaq_u8;                   /**< Max ODT Entry Size for DAQ */
  uint8  GranularityOdtEntrySizeStim_u8;          /**< Granularity ODT Entry Size STIM direction */
  uint8  MaxOdtEntrySizeStim_u8;                  /**< Max ODT Entry Size for STIM */
  uint8  TimeStampMode_u8;                        /**< Timestamp mode */
  uint16 TimeStampTicks_u16;                      /**< Timestamp ticks per unit */
}Xcp_ResGetDaqResolutionInfo_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_DAQ_LIST_MODE GET_DAQ_LIST_MODE
 *  \ingroup  BDAQ_CMDS
 *  \brief    Get mode from DAQ list
 *  \sa       Xcp_CmdGetDaqListMode
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_DAQ_LIST_MODE_AVAILABLE       (((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_COMMAND_GET_DAQ_LIST_MODE == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_DAQ_LIST_MODE_ID              0xDF
#define XCP_CMD_GET_DAQ_LIST_MODE_LENGTH          4u
#define XCP_RES_GET_DAQ_LIST_MODE_LENGTH          8u

/** \brief GET_DAQ_LIST_MODE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xDF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 DaqListNum_u16;                          /**< Daq list number */
}Xcp_CmdGetDaqListMode_t;

/** \brief GET_DAQ_LIST_MODE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Mode_u8;                                 /**< Current Mode */
  uint16 Reserved_u16;                            /**< Reserved */
  uint16 EventChannelNum_u16;                     /**< Current Event Channel Number */
  uint8  Prescaler_u8;                            /**< Current Prescaler */
  uint8  DaqListPriority_u8;                      /**< Current DAQ list priority (0xFF = highest) */
}Xcp_ResGetDaqListMode_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_DAQ_EVENT_INFO GET_DAQ_EVENT_INFO
 *  \ingroup  BDAQ_CMDS
 *  \brief    Get specific information for an Event Channel
 *  \sa       Xcp_CmdGetDaqEventInfo
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_DAQ_EVENT_INFO_AVAILABLE      (((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_COMMANDS_GET_DAQ_INFO == STD_ON)) ? STD_ON : STD_OFF)

#define XCP_CMD_GET_DAQ_EVENT_INFO_ID             0xD7
#define XCP_CMD_GET_DAQ_EVENT_INFO_LENGTH         4u
#define XCP_RES_GET_DAQ_EVENT_INFO_LENGTH         7u

/** \brief GET_DAQ_EVENT_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD7 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 EventChannelNum_u16;                     /**< Event Channel Number */
}Xcp_CmdGetDaqEventInfo_t;

/** \brief GET_DAQ_EVENT_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  DaqEventProperties_u8;                   /**< Daq Event Properties */
  uint8  MaxDaqList_u8;                           /**< Max Daq list */
  uint8  EventChannelNameLength_u8;               /**< Event Channel Name length */
  uint8  EventChannelTimeCycle_u8;                /**< Event Channel Time Cycle */
  uint8  EventChannelTimeUnit_u8;                 /**< Event Channel Time Unit */
  uint8  EventChannelPriority_u8;                 /**< Event Channel Priority (0xFF = highest) */
}Xcp_ResGetDaqEventInfo_t;
/** \} */


/***************************************************************************************************/
/** \defgroup SDAQ_CMDS Static data acquisition and stimulation commands                           *
 ** \ingroup CMDS                                                                                  */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup CMD_CLEAR_DAQ_LIST CLEAR_DAQ_LIST
 *  \ingroup  SDAQ_CMDS
 *  \brief    Clear DAQ list configuration
 *  \sa       Xcp_CmdClearDaqList
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_CLEAR_DAQ_LIST_AVAILABLE          (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_CLEAR_DAQ_LIST_ID                 0xE3
#define XCP_CMD_CLEAR_DAQ_LIST_LENGTH             4u
#define XCP_RES_CLEAR_DAQ_LIST_LENGTH             1u

/** \brief CLEAR_DAQ_LIST command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xE3 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 DaqListNum_u16;                          /**< Daq list number */
}Xcp_CmdClrDaqList_t;

/** \brief CLEAR_DAQ_LIST response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResClrDaqList_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_DAQ_LIST_INFO GET_DAQ_LIST_INFO
 *  \ingroup  SDAQ_CMDS
 *  \brief    Get specific information for a DAQ list
 *  \attention The command GET_DAQ_LIST_INFO (0xD8) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_DAQ_LIST_INFO_AVAILABLE       (STD_OFF)

#define XCP_CMD_GET_DAQ_LIST_INFO_ID              0xD8
#define XCP_CMD_GET_DAQ_LIST_INFO_LENGTH          4u
#define XCP_RES_GET_DAQ_LIST_INFO_LENGTH          6u

/** \brief GET_DAQ_LIST_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD8 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 DaqListNum_u16;                          /**< DAQ list number */
}Xcp_CmdGetDaqListInfo_t;

/** \brief GET_DAQ_LIST_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  DaqListProperties_u8;                    /**< Daq List Priorty */
  uint8  MaxOdt_u8;                               /**< Max ODT */
  uint8  MaxOdtEntries_u8;                        /**< Max ODT Entries */
  uint16 FixedEvent_u16;                          /**< Fixed Event */
}Xcp_ResGetDaqListInfo_t;
/** \} */


/***************************************************************************************************/
/** \defgroup DDAQ_CMDS Dynamic data acquisition and stimulation commands                          *
 ** \ingroup CMDS                                                                                  */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup CMD_FREE_DAQ FREE_DAQ
 *  \ingroup  DDAQ_CMDS
 *  \brief    Clear dynamic DAQ configuration
 *  \sa       Xcp_CmdFreeDaq
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_FREE_DAQ_AVAILABLE                (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_FREE_DAQ_ID                       0xD6
#define XCP_CMD_FREE_DAQ_LENGTH                   1u
#define XCP_RES_FREE_DAQ_LENGTH                   1u

/** \brief FREE_DAQ command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD6 */
}Xcp_CmdFreeDaq_t;

/** \brief FREE_DAQ response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResFreeDaq_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_ALLOC_DAQ ALLOC_DAQ
 *  \ingroup  DDAQ_CMDS
 *  \brief    Allocate DAQ lists
 *  \sa       Xcp_CmdAlloqDaq
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_ALLOC_DAQ_AVAILABLE               (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_ALLOC_DAQ_ID                      0xD5
#define XCP_CMD_ALLOC_DAQ_LENGTH                  4u
#define XCP_RES_ALLOC_DAQ_LENGTH                  1u

/** \brief ALLOC_DAQ command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD5 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 DaqCount_u16;                            /**< DAQ Count */
}Xcp_CmdAllocDaq_t;

/** \brief ALLOC_DAQ response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResAllocDaq_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_ALLOC_ODT ALLOC_ODT
 *  \ingroup  DDAQ_CMDS
 *  \brief    Allocate ODTs to a DAQ list
 *  \sa       Xcp_CmdAllocOdt
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_ALLOC_ODT_AVAILABLE               (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ)

#define XCP_CMD_ALLOC_ODT_ID                      0xD4
#define XCP_CMD_ALLOC_ODT_LENGTH                  5u
#define XCP_RES_ALLOC_ODT_LENGTH                  1u

/** \brief ALLOC_ODT command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD4 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 DaqListNum_u16;                          /**< DAQ List number */
  uint8  OdtCount_u8;                             /**< ODT count */
}Xcp_CmdAllocOdt_t;

/** \brief ALLOC_ODT response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResAllocOdt_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_ALLOC_ODT_ENTRY ALLOC_ODT_ENTRY
 *  \ingroup  DDAQ_CMDS
 *  \brief    Allocate ODT Entries to an ODT
 *  \sa       Xcp_CmdAllocOdtEntry
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_ALLOC_ODT_ENTRY_AVAILABLE         ((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) ? STD_ON : STD_OFF)

#define XCP_CMD_ALLOC_ODT_ENTRY_ID                0xD3
#define XCP_CMD_ALLOC_ODT_ENTRY_LENGTH            6u
#define XCP_RES_ALLOC_ODT_ENTRY_LENGTH            1u

/** \brief ALLOC_ODT_ENTRY command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD3 */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 DaqListNum_u16;                          /**< DAQ List number */
  uint8  OdtNum_u8;                               /**< ODT number */
  uint8  OdtEntriesCount_u8;                      /**< ODT Entries count */
}Xcp_CmdAllocOdtEntry_t;

/** \brief ALLOC_ODT_ENTRY response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResAllocOdtEntry_t;
/** \} */


/***************************************************************************************************/
/** \defgroup NVM_CMDS Non-volatile Memory programming Commands                                    *
 ** \ingroup CMDS                                                                                  */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_START PROGRAM_START
 *  \ingroup  NVM_CMDS
 *  \brief    Indicate the beginning of a programming sequence
 *  \attention The command PROGRAM_START (0xD2) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_START_AVAILABLE           (STD_OFF)

#define XCP_CMD_PROGRAM_START_ID                  0xD2
#define XCP_CMD_PROGRAM_START_LENGTH              1u
#define XCP_RES_PROGRAM_START_LENGTH              7u

/** \brief PROGRAM_START command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD2 */
}Xcp_CmdProgramStart_t;

/** \brief PROGRAM_START response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  Reserved_u8;                             /**< Reserved */
  uint8  CommModePgm_u8;                          /**< COMM_MODE_PGM */
  uint8  MaxCtoPgm_u8;                            /**< Maximum CTO size for PGM */
  uint8  MaxBsPgm_u8;                             /**< MAX_BS_PGM */
  uint8  MinStPgm_u8;                             /**< MIN_ST_PGM */
  uint8  QueSizePgm_u8;                           /**< Queue size PGM */
}Xcp_ResProgramStart_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_CLEAR PROGRAM_CLEAR
 *  \ingroup  NVM_CMDS
 *  \brief    Clear a part of Non-volatile Memory
 *  \attention The command PROGRAM_CLEAR (0xD1) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_CLEAR_AVAILABLE           (STD_OFF)

#define XCP_CMD_PROGRAM_CLEAR_ID                  0xD1
#define XCP_CMD_PROGRAM_CLEAR_LENGTH              8u
#define XCP_RES_PROGRAM_CLEAR_LENGTH              1u

/** \brief PROGRAM_CLEAR command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD1 */
  uint8  Mode_u8;                                 /**< Mode */
  uint16 Reserved_u16;                            /**< Reserved */
  uint32 ClearRange_u32;                          /**< Clear Range */
}Xcp_CmdProgramClear_t;

/** \brief PROGRAM_CLEAR response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgramClear_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM PROGRAM
 *  \ingroup  NVM_CMDS
 *  \brief    Program a part of Non-volatile Memory
 *  \attention The command PROGRAM (0xD0) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_AVAILABLE                 (STD_OFF)

#define XCP_CMD_PROGRAM_ID                        0xD1
#define XCP_CMD_PROGRAM_LENGTH                    XCP_LENGTH_UNDEFINED
#define XCP_CMD_PROGRAM_LENGTH_MIN                3u
#define XCP_RES_PROGRAM_LENGTH                    1u

/** \brief PROGRAM command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xD0 */
  uint8  NumOfDataElements_u8;                    /**< Number of data elements */
  uint8  DataElement_au8[XCP_MAX_CTO_PGM-2u];     /**< Position 2..MAX_CTO_PGM-1 */
}Xcp_CmdProgram_t;

/** \brief PROGRAM response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgram_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_RESET PROGRAM_RESET
 *  \ingroup  NVM_CMDS
 *  \brief    Indicate the end of a programming sequence
 *  \attention The command PROGRAM_RESET (0xCF) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_RESET_AVAILABLE           (STD_OFF)

#define XCP_CMD_PROGRAM_RESET_ID                  0xCF
#define XCP_CMD_PROGRAM_RESET_LENGTH              1u
#define XCP_RES_PROGRAM_RESET_LENGTH              1u

/** \brief PROGRAM_RESET command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xCF */
}Xcp_CmdProgramReset_t;

/** \brief PROGRAM_RESET response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgramReset_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_PGM_PROCESSOR_INFO GET_PGM_PROCESSOR_INFO
 *  \ingroup  NVM_CMDS
 *  \brief    Get general information on PGM processor
 *  \attention The command GET_PGM_PROCESSOR_INFO (0xCE) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_PGM_PROCESSOR_INFO_AVAILABLE  (STD_OFF)

#define XCP_CMD_GET_PGM_PROCESSOR_INFO_ID         0xCE
#define XCP_CMD_PGM_PROCESSOR_INFO_LENGTH         1u
#define XCP_RES_PGM_PROCESSOR_INFO_LENGTH         3u

/** \brief GET_PGM_PROCESSOR_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xCE */
}Xcp_CmdGetProgramProcessorInfo_t;

/** \brief GET_PGM_PROCESSOR_INFO response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  PgmProperties_u8;                        /**< PGM_PROPERTIES */
  uint8  MaxSector_u8;                            /**< MAX_SECTOR */
}Xcp_ResGetProgramProcessorInfo_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_GET_SECTOR_INFO GET_SECTOR_INFO
 *  \ingroup  NVM_CMDS
 *  \brief    Get specific information for a SECTOR
 *  \attention The command GET_SECTOR_INFO (0xCD) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_GET_SECTOR_INFO_AVAILABLE         (STD_OFF)

#define XCP_CMD_GET_SECTOR_INFO_ID                0xCD

/* Response packet is based on mode0, mode1 and mode2 */
#define XCP_CMD_GET_SECTOR_INFO_LENGTH            3u
#define XCP_RES_GET_SECTOR_MODE0_INFO_LENGTH      8u
#define XCP_RES_GET_SECTOR_MODE1_INFO_LENGTH      8u
#define XCP_RES_GET_SECTOR_MODE2_INFO_LENGTH      2u

/** \brief GET_SECTOR_INFO command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xCD */
  uint8  Mode_u8;                                 /**< Mode */
  uint8  SectorNum_u8;                            /**< Sector Number */
}Xcp_CmdGetSectorInfo_t;

/** \brief GET_SECTOR_INFO response structure for Mode0*/
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  ClrSequenceNum_u8;                       /**< Clear Sequence number */
  uint8  PgmSequenceNum_u8;                       /**< Program Sequence number */
  uint8  PgmMethod_u8;                            /**< Program Method */
  uint32 SectorInfo_u32;                          /**< Sector Info: Start address for this SECTOR */
}Xcp_ResGetSectorInfo_Mode0_t;

/** \brief GET_SECTOR_INFO response structure for Mode1 */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  ClrSequenceNum_u8;                       /**< Clear Sequence number */
  uint8  PgmSequenceNum_u8;                       /**< Program Sequence number */
  uint8  PgmMethod_u8;                            /**< Program Method */
  uint32 SectorInfo_u32;                          /**< Sector Info: Length of this SECTOR */
}Xcp_ResGetSectorInfo_Mode1_t;

/** \brief GET_SECTOR_INFO response structure for Mode2*/
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
  uint8  SectorNameLength_u8;                     /**< Sector name length */
}Xcp_ResGetSectorInfo_Mode2_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_PREPARE PROGRAM_PREPARE
 *  \ingroup  NVM_CMDS
 *  \brief    Prepare Non-volatile Memory programming
 *  \attention The command PROGRAM_PREPARE (0xCC) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_PREPARE_AVAILABLE         (STD_OFF)

#define XCP_CMD_PROGRAM_PREPARE_ID                0xCC
#define XCP_CMD_PROGRAM_PREPARE_LENGTH            3u
#define XCP_RES_PROGRAM_PREPARE_LENGTH            1u

/** \brief PROGRAM_PREPARE command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xCC */
  uint8  NotUsed_u8;                              /**< Not used */
  uint8  CodeSize_u16;                            /**< Code Size */
}Xcp_CmdProgramPrepare_t;

/** \brief PROGRAM_PREPARE response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgramPrepare_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_FORMAT PROGRAM_FORMAT
 *  \ingroup  NVM_CMDS
 *  \brief    Set data format before programming
 *  \attention The command PROGRAM_FORMAT (0xCB) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_FORMAT_AVAILABLE          (STD_OFF)

#define XCP_CMD_PROGRAM_FORMAT_ID                 0xCB
#define XCP_CMD_PROGRAM_FORMAT_LENGTH             5u
#define XCP_RES_PROGRAM_FORMAT_LENGTH             1u

/** \brief PROGRAM_FORMAT command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xCB */
  uint8  CompressionMethod_u8;                    /**< Compression Method */
  uint8  EncryptionMethod_u8;                     /**< Encryption Method */
  uint8  PgmMethod_u8;                            /**< Programming Method */
  uint8  AccessMethod_u8;                         /**< Access Method */
}Xcp_CmdProgramFormat_t;

/** \brief PROGRAM_FORMAT response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgramFormat_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_NEXT PROGRAM_NEXT
 *  \ingroup  NVM_CMDS
 *  \brief    Program a Non-volatile Memory segment (Block mode)
 *  \attention The command PROGRAM_NEXT (0xCA) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_NEXT_AVAILABLE            (STD_OFF)

#define XCP_CMD_PROGRAM_NEXT_ID                   0xCA
#define XCP_CMD_PROGRAM_NEXT_LENGTH               XCP_LENGTH_UNDEFINED
#define XCP_CMD_PROGRAM_NEXT_LENGTH_MIN           3u
#define XCP_RES_PROGRAM_NEXT_LENGTH               1u

/** \brief PROGRAM_NEXT command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xCA */
  uint8  NumOfDataElements_u8;                    /**< Number of data elements*/
  uint8  DataElement_au8[XCP_MAX_CTO_PGM-2u];     /**< Position 2..MAX_CTO_PGM-1 */
}Xcp_CmdProgramNext_t;

/** \brief PROGRAM_NEXT response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgramNext_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_MAX PROGRAM_MAX
 *  \ingroup  NVM_CMDS
 *  \brief    Program a Non-volatile Memory segment (fixed size)
 *  \attention The command PROGRAM_MAX (0xC9) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_MAX_AVAILABLE             (STD_OFF)

#define XCP_CMD_PROGRAM_MAX_ID                    0xC9
#define XCP_CMD_PROGRAM_MAX_LENGTH                XCP_LENGTH_UNDEFINED
#define XCP_CMD_PROGRAM_MAX_LENGTH_MIN            8u    /**< It is not possible that transport layer has smaller MAX_CTO than 8 */
#define XCP_RES_PROGRAM_MAX_LENGTH                1u

/** \brief PROGRAM_MAX command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xC9 */
  uint8  DataElement_au8[XCP_MAX_CTO_PGM-2u];     /**< Position 1..MAX_CTO_PGM-1 */
}Xcp_CmdProgramMax_t;

/** \brief PROGRAM_MAX response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgramMax_t;
/** \} */


/**************************************************************************************************/
/** \defgroup CMD_PROGRAM_VERIFY PROGRAM_VERIFY
 *  \ingroup  NVM_CMDS
 *  \brief    Program verify
 *  \attention The command PROGRAM_VERIFY (0xC8) is currently not supported
 *  \{
 */
/**************************************************************************************************/

#define XCP_CMD_PROGRAM_VERIFY_AVAILABLE          (STD_OFF)

#define XCP_CMD_PROGRAM_VERIFY_ID                 0xC8
#define XCP_CMD_PROGRAM_VERIFY_LENGTH             8u
#define XCP_RES_PROGRAM_VERIFY_LENGTH             1u

/** \brief PROGRAM_VERIFY command structure */
typedef struct {
  uint8  CommandCode_u8;                          /**< 0xC8 */
  uint8  VerficationMode_u8;                      /**< Verification Mode*/
  uint16 VerficationType_u16;                     /**< Verification type*/
  uint32 VerficationValue_u32;                    /**< Verification Value*/
}Xcp_CmdProgramVerify_t;

/** \brief PROGRAM_VERIFY response structure */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFF */
}Xcp_ResProgramVerify_t;
/** \} */


/***************************************************************************************************/
/** \defgroup EVENTS Events */
/***************************************************************************************************/

/**************************************************************************************************/
/** \defgroup EV_GENERAL General Event
 *  \ingroup  EVENTS
 *  \brief    Basic definitions for events
 *  \{
 */
/**************************************************************************************************/
#define XCP_EV_LENGTH                             2u
/** \brief Generic packet structure for Events */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFD */
  uint8  EventCode_u8;
}Xcp_Ev_t;
/** \} */


/**************************************************************************************************/
/** \defgroup EV_RESUME_MODE EV_RESUME_MODE
 *  \ingroup  EVENTS
 *  \brief    Start in Resume Mode
 *  \{
 */
/**************************************************************************************************/
#if ((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_RESUME_MODE == STD_ON))
#define XCP_EV_RESUME_MODE_LENGTH                 8u
/** \brief Packet structure for Event EV_RESUME_MODE */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFD */
  uint8  EventCode_u8;                            /**< 0x00 */
  uint16 SessionConfigID_u16;                     /**< SessionConfigurationId from Slave */
  uint32 Timestamp_u32;                           /**< current slave Timestamp */
}Xcp_EvResumeMode_t;
#endif
/** \} */


/**************************************************************************************************/
/** \defgroup EV_DAQ_OVERLOAD EV_DAQ_OVERLOAD
 *  \ingroup  EVENTS
 *  \brief    Indication of DAQ overload
 *  \attention If XCP_DAQ_OVERLOAD_DEBUG_EVENT is STD_ON, DAQ List Number is also send inside event message. This is not ASAM compliant
 *  \{
 */
/**************************************************************************************************/
#if (XCP_DAQ_OVERLOAD_DEBUG_EVENT == STD_ON)
#define XCP_EV_DEBUG_OVERLOAD_LENGTH              3u
/** \brief Packet structure for Event EV_DAQ_OVERLOAD */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFD */
  uint8  EventCode_u8;                            /**< XCP_EV_DAQ_OVERLOAD */
  uint16 DaqListNum_u16;                          /**< DAQ List number */
}Xcp_EvDebugOverload_t;
#endif
/** \} */


/**************************************************************************************************/
/** \defgroup EV_STIM_TIMEOUT EV_STIM_TIMEOUT
 *  \ingroup  EVENTS
 *  \brief    Indication of timeout at STIM
 *  \{
 */
/**************************************************************************************************/
#define XCP_EV_STIM_TIMEOUT_LENGTH                6u
/** \brief Packet structure for Event EV_STIM_TIMEOUT */
typedef struct {
  uint8  PacketId_u8;                             /**< 0xFD */
  uint8  EventCode_u8;                            /**< 0x09 */
  uint8  InfoType_u8;                             /**< 0: Eventchannel, 1: DAQ number */
  uint8  Reserved_u8;                             /**< Reserved */
  uint16 Number_u16;                              /**< either Eventchannel or DAQ number */
}Xcp_EvStimTimeout_t;
/** \} */


#endif   /* #ifndef XCP_COMMANDS_H */


