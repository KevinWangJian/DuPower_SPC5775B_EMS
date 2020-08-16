

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

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service initializes all parameters used by Upload commands
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_InitUpload(uint8 protLayerId)
{
  /* Initialize command parameters */
#if(XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
  Xcp_Cleared[protLayerId].Mem.UploadRunning_b = FALSE;
  Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 = 0;
#else
  XCP_PARAM_UNUSED(protLayerId);
#endif
}

/**
****************************************************************************************************
This service sends data block from address(SetMTA) of requested length
\param[in]  XcpPacket     pointer to the received XcpPacket
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_CmdUpload(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdUpload_t* const CmdPtr = (const Xcp_CmdUpload_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResUpload_t* ResPtr = (Xcp_ResUpload_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  uint8 CurrentPacketSize;
  Xcp_ErrorCode Error;

  /* Check if block upload should be used */
  if (CmdPtr->NumOfDataElements_u8 > (XCP_MAXCTO(protLayerId) - 1) )
  {
#if(XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
    /* Send first block with MAX_CTO-1 */
    CurrentPacketSize = (XCP_MAXCTO(protLayerId) - 1) ;
    /* store remain data */
    Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 = CmdPtr->NumOfDataElements_u8 - CurrentPacketSize;

    /* Read Data from current MTA */
    Error =  Xcp_MemRead(ResPtr->DataElement_au8, CurrentPacketSize, protLayerId);
#else
    Error = XCP_ERR_OUT_OF_RANGE;
#endif /* end of XCP_BLOCK_UPLOAD_ENABLED */
  }
  else
  {
    /* Set packet size */
    CurrentPacketSize = CmdPtr->NumOfDataElements_u8;

#if(XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
    /* reset remaining size */
    Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 = 0;
#endif

    /* Read Data from current MTA */
    Error =  Xcp_MemRead(ResPtr->DataElement_au8, CurrentPacketSize, protLayerId);
  }

  /* Check response */
  if (Error == XCP_NO_ERROR)
  {
    /* Prepare and send positive response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = 1 + CurrentPacketSize;
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    /* ResPtr->DataElement_au8 is set before */
    Xcp_SendRes(protLayerId);

#if(XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)
    /* Check if remaining data to be sent */
    if(Xcp_Cleared[protLayerId].Mem.RemainingSize_u8 != 0)
    {
      Xcp_Cleared[protLayerId].Mem.UploadRunning_b = TRUE;
    }
    else
    {
      Xcp_Cleared[protLayerId].Mem.UploadRunning_b = FALSE;
    }
#endif
  }
  else
  {
    /* Reset Upload params */
    Xcp_InitUpload(protLayerId);

    /* Send error */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#if(XCP_BLOCK_TRANSFER_UPLOAD == STD_ON)

/**
****************************************************************************************************
This service allows block transfer upload
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_BlockUpload(uint8 protLayerId)
{
  /* Command variables */
  PduInfoType XcpPacket;
  Xcp_Cto8_t CmdPacket; /* Data structure */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_CmdUpload_t* const CmdPtr = (Xcp_CmdUpload_t*) (void*) CmdPacket.Buffer_au8;

  /* Initialise SduDataPtr */
  XcpPacket.SduDataPtr = CmdPacket.Buffer_au8;
  XcpPacket.SduLength = XCP_CMD_UPLOAD_LENGTH;

  /* Upload is in progress */
  /* command request for upload */
  CmdPtr->NumOfDataElements_u8 = Xcp_Cleared[protLayerId].Mem.RemainingSize_u8;
  /* setting command code not necessary, Xcp_CmdUpload is called directly */
  Xcp_CmdUpload(&XcpPacket, protLayerId);
}
#endif

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



