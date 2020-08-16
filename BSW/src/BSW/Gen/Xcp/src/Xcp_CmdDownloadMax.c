

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
#if (XCP_CMD_DOWNLOAD_MAX_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command writes data into memory (download data from master to slave) and
does not support block transfer sequence
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdDownloadMax(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdDownloadMax_t* const CmdPtr = (const Xcp_CmdDownloadMax_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check if valid size of the packet */
  if (XcpPacket->SduLength >= XCP_MAXCTO(protLayerId))
  {
    /* Start write process */
    Error = Xcp_MemWrite(CmdPtr->DataElement_au8, XCP_MAXCTO(protLayerId) - 1, protLayerId);
  }
  else
  {
    /* Invalid command syntax */
    Error = XCP_ERR_CMD_SYNTAX;
  }

  /* Send response */
  Xcp_DownloadRes(Error, protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdDownloadMax.c: The command is not enabled - no code is needed in this file */
#endif



