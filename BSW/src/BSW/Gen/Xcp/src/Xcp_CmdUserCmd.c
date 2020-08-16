

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
#if (XCP_CMD_USER_CMD_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command is user defined command
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdUserCmd(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_ErrorCode Error;
  uint8 ResLength;

  /* Call application function to get complete response */
  Error = XcpAppl_UserCmd(XcpPacket->SduDataPtr, (uint8)XCP_MIN(XcpPacket->SduLength,255u), XCP_RES_BUFFER_PTR(protLayerId), &ResLength, protLayerId);

  if (Error == XCP_NO_ERROR)
  {
    /* Updated response data already in XcpAppl_UserCmd */
    /* Update Response length */
    XCP_RES_BUFFER_LENGTH(protLayerId) = ResLength;
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
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdUserCmd.c: The command is not enabled - no code is needed in this file */
#endif



