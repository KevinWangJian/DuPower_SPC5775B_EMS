

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
#if (XCP_CMD_GET_PAGE_INFO_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command returns information on a specific page
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetPageInfo(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdGetPageInfo_t* const CmdPtr = (const Xcp_CmdGetPageInfo_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetPageInfo_t* ResPtr  = (Xcp_ResGetPageInfo_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Call application function to get PAGE_PROPERTIES and INIT_SEGMENT */
  Error = XcpAppl_GetPageInfo(CmdPtr->SegmentNum_u8, CmdPtr->PageNumber_u8, &ResPtr->PageProperties_u8, &ResPtr->InitSegment_u8, protLayerId);

  if (Error == XCP_NO_ERROR)
  {
    /* Length of the response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_PAGE_INFO_LENGTH;

    /* Prepare response to send */
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    /* ResPtr->PageProperties_u8 - already set in XcpAppl_GetPageInfo */
    /* ResPtr->InitSegment_u8 - already set in XcpAppl_GetPageInfo */

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
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetPageInfo.c: The command is not enabled - no code is needed in this file */
#endif



