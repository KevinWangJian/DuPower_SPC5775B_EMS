

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

#if (XCP_CMD_GET_SEED_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command is to get seed from application and it to master for unlocking a protected resource
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetSeed(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdGetSeed_t* const CmdPtr = (const Xcp_CmdGetSeed_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetSeed_t* ResPtr  = (Xcp_ResGetSeed_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_AdrPtr SeedPtr;
  uint8 SeedLengthToTransmit;
  Xcp_ErrorCode Error;

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* Check if first part of seed is requested */
  if(CmdPtr->Mode_u8 == 0x00)
  {
    /* Check if valid and single resource type */
    if((CmdPtr->Resource_u8 == XCP_RESOURCE_CALPAG)
    || (CmdPtr->Resource_u8 == XCP_RESOURCE_DAQ)
    || (CmdPtr->Resource_u8 == XCP_RESOURCE_STIM)
    || (CmdPtr->Resource_u8 == XCP_RESOURCE_PGM))
    {
      /* Check if resource is locked */
      if((Xcp_NoInit[protLayerId].Session.ResourceProtStatus_u8 & CmdPtr->Resource_u8) != 0)
      {
        /* Get seed from Application specific function */
        Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8 = XcpAppl_GetSeed(&SeedPtr, CmdPtr->Resource_u8, protLayerId);
      }
      else
      {
        /* Resource is unprotected and no unlock necessary - answer with seed 0 length and SeedPtr = NULL_PTR to have this variable initialized for MISRA */
        Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8 = 0;
        SeedPtr = NULL_PTR;
      }
    }
    else
    {
      /* More than one resource requested or resource unknown */
      /* Set error response 0x22 */
      Error = XCP_ERR_OUT_OF_RANGE;
    }
  }
  /* Remaining part of the seed */
  else if(CmdPtr->Mode_u8 == 0x01)
  {
    /* Check if there is remaining part of the seed to be sent */
    if (Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8 > 0u)
    {
      /* Restore Seed pointer from MTA */
      SeedPtr = XCP_MTA(protLayerId);
    }
    else
    {
      /* Set error response 0x29 */
      Error = XCP_ERR_SEQUENCE;
    }
  }
  /* Mode not supported */
  else
  {
    /* Set error response 0x21 */
    Error = XCP_ERR_CMD_SYNTAX;
  }

  /* Check if no error and positive response should be sent */
  if (Error == XCP_NO_ERROR)
  {
    /* Fill response data */
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    ResPtr->LengthOfSeed_u8 = Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8;

    /* Compute length of the seed which shall be transmitted in one packet */
    SeedLengthToTransmit = XCP_MIN(Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8, XCP_MAXCTO(protLayerId) - 2);

    /* Copy Seed part into response - SeedPtr may be NULL_PTR but this is no problem as in this case the length is also 0 */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(ResPtr->Seed_au8, SeedPtr, SeedLengthToTransmit);

    /* Update pointer to seed (which will be used in next part) */
    SeedPtr += SeedLengthToTransmit;

    /* Decrease remaining length of seed by number of sent bytes */
    Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8 -= SeedLengthToTransmit;

    /* Check if whole seed is "sent" */
    if((Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8 == 0u) && (SeedLengthToTransmit > 0u))
    {
      /* Set flag that seed is generated */
      Xcp_Cleared[protLayerId].SeedAndKey.SeedWaitingKey_b = TRUE;
    }

    /* Set length of response packet (number of sent seed bytes + "seed header") */
    XCP_RES_BUFFER_LENGTH(protLayerId) = SeedLengthToTransmit + 2;

    /* Send positive response */
    Xcp_SendRes(protLayerId);

    /* Store Seed pointer in MTA */
    XCP_MTA(protLayerId) = SeedPtr;
  }
  else
  {
    /* Prepare error response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* The command is not enabled */
#endif

#if (XCP_SEED_AND_KEY == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service initializes all parameters used by GET_SEED command
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_InitSeedKey(uint8 protLayerId)
{
  /* Lock all available resources */
  Xcp_NoInit[protLayerId].Session.ResourceProtStatus_u8 = XCP_RESOURCE_CALPAG|XCP_RESOURCE_DAQ|XCP_RESOURCE_STIM|XCP_RESOURCE_PGM;

  /* Initialize command parameters */
  Xcp_Cleared[protLayerId].SeedAndKey.SeedWaitingKey_b = FALSE;
  Xcp_Cleared[protLayerId].SeedAndKey.SeedRemaingSize_u8 = 0;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetSeed.c: XCP_SEED_AND_KEY is not enabled - no data is needed in this file */
#endif



