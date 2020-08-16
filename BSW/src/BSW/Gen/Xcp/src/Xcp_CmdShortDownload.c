

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
#if(XCP_CMD_SHORT_DOWNLOAD_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command write data into memory (download from master to slave) and
does not support block transfer mode
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdShortDownload(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  if (XCP_MAXCTO(protLayerId) > 8)
  {
    /* Command variables */
    /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                      The cast allows easier (= safer) access to the data in the PDU.
                                      Casting over void* is necessary as otherwise some compilers complain */
    const Xcp_CmdShortDownload_t* const CmdPtr = (const Xcp_CmdShortDownload_t*) (void*) XcpPacket->SduDataPtr;

    /* Local variables */
    Xcp_ErrorCode Error;

    /* Check if any elements in packet and the packet is big enough to contain them */
    if ((CmdPtr->NumOfDataElements_u8 > 0u) && (CmdPtr->NumOfDataElements_u8 <= (XcpPacket->SduLength - 8u)))
    {
      /* Check if valid number of elements */
      if((CmdPtr->NumOfDataElements_u8) <= (XCP_MAXCTO(protLayerId) - 8))
      {
        /* Set the address */
        XCP_MTA(protLayerId) = CmdPtr->Address_Ptr;

        /* Start write process */
        Error = Xcp_MemWrite(CmdPtr->DataElement_au8, CmdPtr->NumOfDataElements_u8, protLayerId);
      }
      else
      {
        Error = XCP_ERR_OUT_OF_RANGE;
      }
    }
    else
    {
      /* Invalid command syntax */
      Error = XCP_ERR_CMD_SYNTAX;
    }
    /* Send response */
    Xcp_DownloadRes(Error, protLayerId);
  }
  else
  {
    /* Send error message */
    Xcp_SendErrRes(XCP_ERR_CMD_UNKNOWN, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdShortDownload.c: The command is not enabled - no code is needed in this file */
#endif



