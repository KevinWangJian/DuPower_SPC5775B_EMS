

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
#if (XCP_CMD_GET_PAG_PROCESSOR_INFO_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command returns general information on paging
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetPagProcessorInfo(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetPagProcessorInfo_t* ResPtr = (Xcp_ResGetPagProcessorInfo_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;

  XCP_PARAM_UNUSED(XcpPacket);

  /* Call application function to get MAX_SEGMENT */
  Error = XcpAppl_GetPagProcessorInfo(&ResPtr->MaxSegment_u8, protLayerId);

  if (Error == XCP_NO_ERROR)
  {
    /* Length of the response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_PAG_PROCESSOR_INFO_LENGTH;

    /* Prepare response to send */
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    /* ResPtr->MaxSegment_u8 - already set in XcpAppl_GetPagProcessorInfo */
    /* SEGMENTS can or cannot be set to FREEZE mode, currently FREEZE_SUPPORTED is not supported */
    ResPtr->PagProperties_u8 = 0u;

    /* Send positive response */
    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Send negative response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetPagProcessorInfo.c: The command is not enabled - no code is needed in this file */
#endif



