

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

#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command starts the checksum calculation. \n
Checksum calculation is performed in the background
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdBuildChecksum(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdBuildChecksum_t* const CmdPtr = (const Xcp_CmdBuildChecksum_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResBuildChecksum_t* ResPtr = (Xcp_ResBuildChecksum_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;
  Xcp_AdrPtr LocalMta;

  /* Store address in local variable */
  LocalMta = XCP_MTA(protLayerId);

  /* Check if another background process is running */
  if (Xcp_Cleared[protLayerId].BgActivityState != XCP_BG_IDLE)
  {
    Error = XCP_ERR_CMD_BUSY;
  }
#if (XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON)
  else
  {
    /* Call Address-transformation-function */
    Error = XcpAppl_StaticAddressTransformation(&LocalMta, CmdPtr->BlockSize_u32, XCP_EVENT_CHANNEL_NOT_USED, XCP_CONTEXT_CHECKSUM);
  }

  if (Error != XCP_NO_ERROR)
  {
    /* There is an error stored in Error, do nothing more */
  }
#endif
  /* Check if valid block size */
  else if ( (CmdPtr->BlockSize_u32 <= XCP_CHECKSUM_MAX_BLOCK_SIZE)
            /* MR12 RULE 11.4 VIOLATION: Cast from pointer to uint32 is OK as the addresses are 32bit long */
            && (((uint32)LocalMta % XCP_MTA_BLOCK_SIZE_ALIGN) == 0u)
            && ((CmdPtr->BlockSize_u32 % XCP_MTA_BLOCK_SIZE_ALIGN) == 0u)
          )
  {
    if (LocalMta != NULL_PTR)
    {
# if (XCP_MEMORY_READ_PROTECTION == STD_ON)
      /* Check if valid memory area to calculate the checksum value */
      Error = XcpAppl_ChecksumProtection(LocalMta, CmdPtr->BlockSize_u32);

      /* Checksum shall hide real value? */
      if (Error == XCP_NO_ACCESS_HIDE)
      {
        Xcp_Cleared[protLayerId].Checksum.FakeChecksum_b = TRUE;
      }
      else
      {
        Xcp_Cleared[protLayerId].Checksum.FakeChecksum_b = FALSE;
      }

      /* XCP_NO_ERROR and XCP_NO_ACCESS_HIDE are acceptable */
      if (Error != XCP_ERR_ACCESS_DENIED)
# endif /* (XCP_MEMORY_READ_PROTECTION == STD_ON) */
      {
        /* Trigger checksum calculation */
        Error = XcpAppl_BuildChecksumTrigger(LocalMta, CmdPtr->BlockSize_u32, protLayerId);
      }
    }
    else /* LocalMta != NULL_PTR */
    {
      Error = XCP_ERR_ACCESS_DENIED;
    }
  }
  else
  {
    /* Set Status to Out of range */
    Error = XCP_ERR_OUT_OF_RANGE;
  }

  /* Check if no error */
  if (Error == XCP_NO_ERROR)
  {
    /* Store block size */
    Xcp_Cleared[protLayerId].Checksum.BlockSize_u32 = CmdPtr->BlockSize_u32;

    /* Set state for background activity -> trigger for Xcp_BuildChecksumMainFunction to start calculation */
    /* Important!! Must be called after XcpAppl_BuildChecksumTrigger() */
    Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_CHKSUM;

    /* No response - Checksum will be calculated in Xcp_BuildChecksumMainFunction */
  }
  /* Error */
  else
  {
    /* Error with no extra parameter? */
    if (Error == XCP_ERR_OUT_OF_RANGE)
    {
      /* Fill response data (using positive response structure, because structure entries are matching) */
      XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_BUILD_CHECKSUM_LENGTH;
      ResPtr->PacketId_u8 = XCP_PACKET_ID_ERR;
      ResPtr->ChecksumType_u8 = (uint8) Error;
      ResPtr->Reserved_u16 = XCP_MTA_BLOCK_SIZE_ALIGN;
      ResPtr->Checksum_u32 = XCP_CHECKSUM_MAX_BLOCK_SIZE;

      /* Send error packet */
      Xcp_SendRes(protLayerId);
    }
    else
    {
      /* Send error packet */
      Xcp_SendErrRes(Error, protLayerId);
    }
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This function initializes all parameters used by Checksum command
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_InitChecksum(uint8 protLayerId)
{
  /* Initialize command parameters */
  Xcp_Cleared[protLayerId].Checksum.BlockSize_u32 = 0;
# if (XCP_MEMORY_READ_PROTECTION == STD_ON)
  Xcp_Cleared[protLayerId].Checksum.FakeChecksum_b = FALSE;
# endif
}

/**
****************************************************************************************************
Main function for background checksum calculation
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_BuildChecksumMainFunction(uint8 protLayerId)
{
  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResBuildChecksum_t* ResPtr = (Xcp_ResBuildChecksum_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Checksum background calculation */
  Error = XcpAppl_BuildChecksumMainFunction(&ResPtr->Checksum_u32, &ResPtr->ChecksumType_u8, protLayerId);

# if (XCP_MEMORY_READ_PROTECTION == STD_ON)
  /* Checksum shall hide real value? */
  if (Xcp_Cleared[protLayerId].Checksum.FakeChecksum_b == TRUE)
  {
    /* Response shall be send? */
    if (Error != XCP_NO_RESPONSE)
    {
      /* Set fake value of the checksum and send positive response */
      ResPtr->Checksum_u32 = 0;
      Error = XCP_NO_ERROR;
    }
  }
# endif

  /* Check if no error */
  if (Error == XCP_NO_ERROR)
  {
    /* Update MTA - BlockSize was set in Xcp_CmdBuildChecksum*/
    XCP_MTA(protLayerId) +=  Xcp_Cleared[protLayerId].Checksum.BlockSize_u32;

    /* Fill response data */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_BUILD_CHECKSUM_LENGTH;
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    /* ResPtr->ChecksumType_u8 - already set in XcpAppl_BuildChecksumMainFunction */
    ResPtr->Reserved_u16 = 0;
    /* ResPtr->Checksum_u32 - already set in XcpAppl_BuildChecksumMainFunction */

    /* Clear flag that calculation in progress */
    Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_IDLE;

    /* Send positive response */
    Xcp_SendRes(protLayerId);
  }
  else if (Error == XCP_NO_RESPONSE)
  {
    /* Still waiting for calculation finished - no response */
    /* Nothing to do here, EV_CMD_PENDING event will be sent from Xcp_Background_Tasks function*/
  }
  else
  {/* Error */
    /* Clear flag that calculation in progress */
    Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_IDLE;

    /* Send error packet */
    Xcp_SendErrRes(Error, protLayerId);
  }
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
/* HIS METRIC COMF VIOLATION IN Xcp_CmdBuildChecksum.c: Checksum disabled - no code is needed in this file */
#endif



