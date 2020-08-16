

#ifndef XCPONFR_TYPES_H
#define XCPONFR_TYPES_H

/***************************************************************************************************
* Includes
***************************************************************************************************/


/***************************************************************************************************
* Defines/Macros
***************************************************************************************************/
/**
 * \name Data alignment for FlexRay
 * \{
 */
#define XCP_FR_PACKET_ALIGNMENT_UNKNOWN       0u
#define XCP_FR_PACKET_ALIGNMENT_8             1u
#define XCP_FR_PACKET_ALIGNMENT_16            2u
#define XCP_FR_PACKET_ALIGNMENT_32            3u
/** \} */

/**
 * \name Command codes for FlexRay TransportLayer
 * \{
 */
#define XCP_FR_TLCMD_FLX_ASSIGN               0xFFu
#define XCP_FR_TLCMD_FLX_ACTIVATE             0xFEu
#define XCP_FR_TLCMD_FLX_DEACTIVATE           0xFDu
#define XCP_FR_TLCMD_GET_DAQ_FLX_BUF          0xFCu
#define XCP_FR_TLCMD_SET_DAQ_FLX_BUF          0xFBu
/** \} */

/***************************************************************************************************
* Type definitions
***************************************************************************************************/
/*--------------------------------------------------------------------------------------------------
  FR TransportLayer commands structures
--------------------------------------------------------------------------------------------------*/
/* FLX_ASSIGN */

#define XCP_CMD_FR_ASSIGN_LENGTH                  12u
typedef struct
{
  uint8   CommandCode_u8;                         /**< 0xF2 */
  uint8   TLCommandCode_u8;                       /**< 0xFF */
  uint8   FlxBuf_u8;                              /**< FlexRay Buffer Id */
  uint8   PacketType_u8;                          /**< Type of the packet assigned to the buffer */
  uint16  FlxSlotId_u16;                          /**< FlexRay slot Id */
  uint8   Offset_u8;                              /**< Offset */
  uint8   CycleRepetition_u8;                     /**< Cycle repetition */
  uint8   FlxChannel_u8;                          /**< 0 - channel A, 1 - channel B */
  uint8   MaxFlxLenBuf_u8;                        /**< Maximum length of the buffer */
  uint16  HeaderCrc_u16;                          /**< Header CRC */
}Xcp_CmdFrAssign_t;


/* FLX_ACTIVATE */

#define XCP_CMD_FR_ACTIVATE_LENGTH                3u
typedef struct
{
  uint8   CommandCode_u8;                         /**< 0xF2 */
  uint8   TLCommandCode_u8;                       /**< 0xFE */
  uint8   FlxBuf_u8;                              /**< FlexRay Buffer Id */
}Xcp_CmdFrActivate_t;


/* FLX_DEACTIVATE */

#define XCP_CMD_FR_DEACTIVATE_LENGTH              3u
typedef struct
{
  uint8   CommandCode_u8;                         /**< 0xF2 */
  uint8   TLCommandCode_u8;                       /**< 0xFD */
  uint8   FlxBuf_u8;                              /**< FlexRay Buffer Id */
}Xcp_CmdFrDeactivate_t;


/* GET_DAQ_FLX_BUF */

#define XCP_CMD_FR_GET_DAQ_FLX_BUF_LENGTH         4u
typedef struct
{
  uint8   CommandCode_u8;                         /**< 0xF2 */
  uint8   TLCommandCode_u8;                       /**< 0xFC */
  uint16  DaqListNum_u16;                         /**< DAQ list number */
}Xcp_CmdFrGetDaqFlxBuf_t;

#define XCP_RES_FR_GET_DAQ_FLX_BUF_LENGTH         XCP_LENGTH_UNDEFINED
#define XCP_RES_FR_GET_DAQ_FLX_BUF_LENGTH_MIN     3u
typedef struct
{
  uint8   PacketId_u8;                            /**< 0xFF */
  uint8   FlxBufFixed_u8;                         /**< 0 - Buffer can be configured, 1 - buffer is fixed */
  uint8   MaxBuf_u8;                              /**< Maximum number of buffers */
  uint8   FlxBuf_au8[XCP_MAX_CTO-3u];             /**< FlexRay buffer which is assigned to this DAQ List */
}Xcp_ResFrGetDaqFlxBuf_t;


/* SET_DAQ_FLX_BUF */

#define XCP_CMD_FR_SET_DAQ_FLX_BUF_LENGTH         XCP_LENGTH_UNDEFINED
#define XCP_CMD_FR_SET_DAQ_FLX_BUF_LENGTH_MIN     4u
typedef struct
{
  uint8   CommandCode_u8;                         /**< 0xF2 */
  uint8   TLCommandCode_u8;                       /**< 0xFB */
  uint16  DaqListNum_u16;                         /**< DAQ list number */
  uint8   NumOfBuf_u8;                            /**< Number of buffers to be assigned */
  uint8   FlxBuf_au8[XCP_MAX_CTO-5u];             /**< FlexRay buffer which shall be assigned to this DAQ List */
}Xcp_CmdFrSetDaqFlxBuf_t;


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Function prototypes
***************************************************************************************************/


#endif   /* #ifndef XCPONFR_TYPES_H */


