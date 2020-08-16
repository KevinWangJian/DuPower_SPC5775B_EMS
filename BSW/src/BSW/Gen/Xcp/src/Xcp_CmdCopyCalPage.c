

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
#if (XCP_CMD_COPY_CAL_PAGE_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command copies one calibration page to another in Xcp slave
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdCopyCalPage(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdCopyCalPage_t* const CmdPtr = (const Xcp_CmdCopyCalPage_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Call application copy routine */
  Error = XcpAppl_CopyCalPage(CmdPtr->LogicalDataSegNumSource_u8, CmdPtr->LogicalDataSegPageNumSource_u8, CmdPtr->LogicalDataSegNumDest_u8, CmdPtr->LogicalDataSegPageNumDest_u8, protLayerId);

  /* Check if OK */
  if (Error == XCP_NO_ERROR)
  {
    /* Prepare and send positive response */
    Xcp_SendPosRes(protLayerId);
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
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdCopyCalPage.c: The command is not enabled - no code is needed in this file */
#endif



