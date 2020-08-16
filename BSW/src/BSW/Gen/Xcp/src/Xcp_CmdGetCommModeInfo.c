

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
#if (XCP_CMD_GET_COMM_MODE_INFO_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command returns optional information on different Communication Modes supported by the slave.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetCommModeInfo(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetCommModeInfo_t* ResPtr  = (Xcp_ResGetCommModeInfo_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  XCP_PARAM_UNUSED(XcpPacket);

  /* Length of the response */
  XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_COMM_MODE_INFO_LENGTH;

  /* Send the Response */
  ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
  /* Reserved byte */
  ResPtr->Reserved_u8 = 0;
  ResPtr->Reserved2_u8 = 0;

# if (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON)
  /* Master Block mode is available and Xcp does not support Interleaved mode */
  ResPtr->CommModeOptional_u8 = XCP_COMM_MODE_OPTIONAL_MASTER_BLOCK_MODE;
  /* Maximum allowed Block Size  */
  ResPtr->MaxBs_u8 = XCP_BLOCK_TRANSFER_MAX_BS;
  /* Required minimum Separation time */
  ResPtr->MinSt_u8 = XCP_BLOCK_TRANSFER_MIN_ST;
# else
  /* Master Block mode and Interleaved mode is not available */
  ResPtr->CommModeOptional_u8 = 0;
  /* Maximum allowed Block Size  */
  ResPtr->MaxBs_u8 = 0;
  /* Required minimum Separation time */
  ResPtr->MinSt_u8 = 0;
# endif
  /* Interleaved mode is not supported */
  ResPtr->QueueSize_u8 = 0;

  /* Xcp driver version */
  ResPtr->XcpDriverVerNum_u8 = (uint8)(((uint8) (XCP_SW_MAJOR_VERSION << 4u))|(XCP_SW_MINOR_VERSION & 0x0Fu));

  /* Send positive response */
  Xcp_SendRes(protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetCommModeInfo.c: The command is not enabled - no code is needed in this file */
#endif



