

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
#if (XCP_CMD_SET_CAL_PAGE_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command sets the access mode for a calibration data segment,
if the slave device supports calibration data page switching
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdSetCalPage(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdSetCalPage_t* const CmdPtr = (const Xcp_CmdSetCalPage_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check mode if undefined bits are not set */
  if ( (CmdPtr->Mode_u8 & ((uint8)(~(XCP_CAL_PAGE_MODE_ALL|XCP_CAL_PAGE_MODE_ECU|XCP_CAL_PAGE_MODE_XCP))) ) == 0u)
  {
    /* Check mode if ECU or XCP is set */
    if ((CmdPtr->Mode_u8 & (XCP_CAL_PAGE_MODE_ECU|XCP_CAL_PAGE_MODE_XCP) ) != 0u)
    {
      /* Set application CalPage */
      Error = XcpAppl_SetCalPage(CmdPtr->Mode_u8, CmdPtr->LogicalDataSegNum_u8, CmdPtr->LogicalDataPgNum_u8, protLayerId);
    }
    else
    {
      Error = XCP_ERR_MODE_NOT_VALID;
    }
  }
  else
  {
    Error = XCP_ERR_MODE_NOT_VALID;
  }

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
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdSetCalPage.c: The command is not enabled - no code is needed in this file */
#endif



