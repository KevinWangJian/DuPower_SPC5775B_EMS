

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
#if (XCP_CMD_GET_DAQ_RESOLUTION_INFO_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to get the DAQ Resolution Info.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetDaqResolutionInfo(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetDaqResolutionInfo_t* ResPtr = (Xcp_ResGetDaqResolutionInfo_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Set response length */
  XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_DAQ_RESOLUTION_INFO_LENGTH;

  /* Set response data */
  ResPtr->PacketId_u8                    = XCP_PACKET_ID_RES;
  ResPtr->GranularityOdtEntrySizeDaq_u8  = 0x01u;
  ResPtr->MaxOdtEntrySizeDaq_u8          = 0xFFu;
  ResPtr->GranularityOdtEntrySizeStim_u8 = 0x01u;
  ResPtr->MaxOdtEntrySizeStim_u8         = 0xFFu;
  /* Timestamp info (last three bytes) is updated only when timestamp is enabled else filled with zero*/
# if (XCP_TIMESTAMP == STD_ON)
  ResPtr->TimeStampMode_u8    = (((uint8)(XCP_TIMESTAMP_MODE_UNIT << 4u)) | (((uint8) Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TimestampType_en) & 0x07u));
  ResPtr->TimeStampTicks_u16  = XCP_TIMESTAMP_TICKS;
# else /* (XCP_TIMESTAMP == STD_OFF) */
  ResPtr->TimeStampMode_u8    = 0x00u;
  ResPtr->TimeStampTicks_u16  = 0x00u;
# endif /* (XCP_TIMESTAMP == STD_OFF) */

  /* Send positive response */
  Xcp_SendRes(protLayerId);
  XCP_PARAM_UNUSED(XcpPacket);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetDaqResolutionInfo.c: The command is not enabled - no code is needed in this file */
#endif



