

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
#if (XCP_CMD_DOWNLOAD_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command writes data into memory (download data from master to slave)
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdDownload(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdDownload_t* const CmdPtr = (const Xcp_CmdDownload_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

# if (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON)
  /* Clear remaining size because new Download sequence is started */
  Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 = 0;
# endif

  /* Check if block download shall be used */
  if(CmdPtr->NumOfDataElements_u8 > (XCP_MAXCTO(protLayerId) - 2))
  {
    /* Check if Block Download is supported */
# if (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON)
    /* Check if length of the XcpPacket is valid */
    if (XcpPacket->SduLength >= XCP_MAXCTO(protLayerId))
    {
      /* Copy data to global buffer */
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(Xcp_Cleared[protLayerId].Mem.DownloadBuffer_au8, CmdPtr->DataElement_au8, XCP_MAXCTO(protLayerId) - 2);

      /* set requested size to write to maximum */
      Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 = CmdPtr->NumOfDataElements_u8 - (XCP_MAXCTO(protLayerId) - 2);
      Xcp_Cleared[protLayerId].Mem.ReceivedSize_u8 = XCP_MAXCTO(protLayerId) - 2;

      /* No response, waiting for the rest of data */
      Error = XCP_NO_RESPONSE;
    }
    else
    {
      /* Command Syntax error - Xcp Packet too short */
      Error = XCP_ERR_CMD_SYNTAX;
    }
# else
    /* Set error code */
    Error = XCP_ERR_OUT_OF_RANGE;
# endif /* XCP_BLOCK_TRANSFER_DOWNLOAD */
  }
  else
  {
    /* Check if any elements in packet and the packet is big enough to contain them */
    if ((CmdPtr->NumOfDataElements_u8 > 0u) && (CmdPtr->NumOfDataElements_u8 <= (XcpPacket->SduLength - 2u)))
    {
      /* Start write process */
      Error = Xcp_MemWrite(CmdPtr->DataElement_au8, CmdPtr->NumOfDataElements_u8, protLayerId);
    }
    else
    {
      /* Invalid command syntax */
      Error = XCP_ERR_CMD_SYNTAX;
    }
  }

  /* Send response */
  Xcp_DownloadRes(Error, protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* The command is not enabled */
#endif

#if (XCP_CALIBRATION_CAL == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function initializes all parameters used by Download command
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_InitDownload(uint8 protLayerId)
{
  /* Initialize command parameters */
# if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
  Xcp_Cleared[protLayerId].Mem.DownloadSize_u8 = 0;
# endif
# if (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON)
  Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 = 0;
  Xcp_Cleared[protLayerId].Mem.ReceivedSize_u8 = 0;
# endif
# if ( (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_OFF) && (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_OFF) )
  XCP_PARAM_UNUSED(protLayerId);
# endif
}

/**
****************************************************************************************************
This function sends response of download commands
\param[in]  Error         Errors if any, else XCP_NO_ERROR
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DownloadRes(Xcp_ErrorCode Error, uint8 protLayerId)
{
  /* Check if all OK */
  if (Error == XCP_NO_ERROR)
  {
    /* Send positive response */
    Xcp_SendPosRes(protLayerId);
  }
  else if (Error == XCP_NO_RESPONSE)
  {
    /* Nothing to do. Just waiting for background process to be finished */
  }
  /* Check if Block Download is supported */
# if (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON)
  else if (Error == XCP_ERR_SEQUENCE)
  {
    /* Command variables */
    /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                      The cast allows easier (= safer) access to the data in the PDU.
                                      Casting over void* is necessary as otherwise some compilers complain */
    Xcp_ErrResDownloadNext_t* ResPtr = (Xcp_ErrResDownloadNext_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

    /* Prepare data for response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_ERR_SEQ_DOWNLOAD_NEXT_LENGTH;
    ResPtr->PacketId_u8 = XCP_PACKET_ID_ERR;
    ResPtr->ErrCode_u8 = (uint8) Error;
    ResPtr->NumOfDataElements_u8 = Xcp_Cleared[protLayerId].Mem.RemainingSize_u8;

    /* Send response */
    Xcp_SendRes(protLayerId);
  }
# endif /* #if (XCP_BLOCK_TRANSFER_DOWNLOAD == STD_ON) */
  else
  {
    /* Reset download parameters */
    Xcp_InitDownload(protLayerId);

    /* Send error */
    Xcp_SendErrRes(Error, protLayerId);
  }
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdDownload.c: The code is not needed as the respective feature is disabled */
#endif



