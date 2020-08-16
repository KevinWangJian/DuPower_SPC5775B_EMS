

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
#if (XCP_CMD_GET_CAL_PAGE_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command returns the calibration data page that is currently activated for the specified
access mode and data segment.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetCalPage(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdGetCalPage_t* const CmdPtr = (const Xcp_CmdGetCalPage_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetCalPage_t* ResPtr  = (Xcp_ResGetCalPage_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check for correct Access Mode */
  if((CmdPtr->AccessMode_u8 == XCP_CAL_PAGE_MODE_ECU) || (CmdPtr->AccessMode_u8 == XCP_CAL_PAGE_MODE_XCP))
  {
    /* Get calibration page number from user function */
    Error = XcpAppl_GetCalPage(CmdPtr->AccessMode_u8, CmdPtr->LogicalDataSegNum_u8, &ResPtr->LogicalDataPgNum_u8, protLayerId);
  }
  /* All other possibilities are invalid */
  else
  {
    /* Mode is not supported */
    Error = XCP_ERR_MODE_NOT_VALID;
  }

  /* Check if OK */
  if (Error == XCP_NO_ERROR)
  {
    /* Prepare and send response for ECU mode */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_CAL_PAGE_LENGTH;
    ResPtr->PacketId_u8  = XCP_PACKET_ID_RES;
    ResPtr->Reserved_u8  = 0;
    ResPtr->Reserved2_u8 = 0;
    /* ResPtr->LogicalDataPgNum_u8 already set before */
    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Send error response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetCalPage.c: The command is not enabled - no code is needed in this file */
#endif



