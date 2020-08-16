

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
#if (XCP_CMD_DOWNLOAD_NEXT_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command writes data into memory (download data from master to slave) in block transfer mode
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdDownloadNext(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdDownloadNext_t* const CmdPtr = (const Xcp_CmdDownloadNext_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* check if requested size is equal the remaining size */
  if(CmdPtr->NumOfDataElements_u8 == Xcp_Cleared[protLayerId].Mem.RemainingSize_u8)
  {
    uint8 Size;

    /* Get what size should be copied to the buffer */
    Size = XCP_MIN(XCP_MAXCTO(protLayerId) - 2, CmdPtr->NumOfDataElements_u8);

    /* Check size is valid */
    if ((Size > 0u) && (Size <= (XcpPacket->SduLength - 2u)))
    {
      /* Copy data to global buffer */
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(Xcp_Cleared[protLayerId].Mem.DownloadBuffer_au8 + Xcp_Cleared[protLayerId].Mem.ReceivedSize_u8, CmdPtr->DataElement_au8, Size);

      /* Update received and remaining sizes */
      Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 -= Size;
      Xcp_Cleared[protLayerId].Mem.ReceivedSize_u8 += Size;

      /* Check if all is already received */
      if (Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 == 0u)
      {
        /* Start write process */
        Error = Xcp_MemWrite(Xcp_Cleared[protLayerId].Mem.DownloadBuffer_au8, Xcp_Cleared[protLayerId].Mem.ReceivedSize_u8, protLayerId);
      }
      else
      {
        /* Not everything received yet */
        Error = XCP_NO_RESPONSE;
      }
    }
    else
    {
      /* Invalid command syntax */
      Error = XCP_ERR_CMD_SYNTAX;
    }
  }
  else
  {
    Error = XCP_ERR_SEQUENCE;
  }

  /* Send response */
  Xcp_DownloadRes(Error, protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdDownloadNext.c: The command is not enabled - no code is needed in this file */
#endif



