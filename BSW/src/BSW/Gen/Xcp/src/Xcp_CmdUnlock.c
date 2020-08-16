

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
#if(XCP_CMD_UNLOCK_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service unlock protected resource (only if Key is matching)
\param[in]  XcpPacket     pointer to the received XcpPacket
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_CmdUnlock(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdUnlock_t* const CmdPtr = (const Xcp_CmdUnlock_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResUnlock_t* ResPtr = (Xcp_ResUnlock_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  uint8 UnlockedResource;
  Xcp_ErrorCode Error;

  /* Initial values */
  Error = XCP_NO_ERROR;
  UnlockedResource = 0;

  if (CmdPtr->LengthOfKey_u8 > 0u)
  {
    /* Check if seed was already requested */
    if(Xcp_Cleared[protLayerId].SeedAndKey.SeedWaitingKey_b == TRUE)
    {
      /* Get unlocked resource */
      Error = XcpAppl_Unlock(CmdPtr->Key_au8, ((uint8)XCP_MIN(XcpPacket->SduLength - 2u, CmdPtr->LengthOfKey_u8)), CmdPtr->LengthOfKey_u8, &UnlockedResource, protLayerId);
    }
    else
    {
      /* Set error response 0x29 */
      Error = XCP_ERR_SEQUENCE;
    }
  }
  else
  {
    /* No Key data */
    Error = XCP_ERR_CMD_SYNTAX;
  }

  /* Check if no error */
  if (Error == XCP_NO_ERROR)
  {
    /* Check if resource shall be unlocked with this key */
    if(UnlockedResource > 0u)
    {
      /* Unlock the resource */
      Xcp_NoInit[protLayerId].Session.ResourceProtStatus_u8 &= (uint8)~UnlockedResource;

      /* Reset seed and key procedure */
      Xcp_Cleared[protLayerId].SeedAndKey.SeedWaitingKey_b = FALSE;
    }

    /* Fill response data */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_UNLOCK_LENGTH;
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    ResPtr->ProtectionStatus_u8 = Xcp_NoInit[protLayerId].Session.ResourceProtStatus_u8;

    /* Send positive response */
    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Reset seed and key procedure */
    Xcp_Cleared[protLayerId].SeedAndKey.SeedWaitingKey_b = FALSE;

    /* Invalid Key? */
    if (Error == XCP_ERR_ACCESS_LOCKED)
    {
      /* Disconnect Protocol layer */
      Xcp_Disconnect(protLayerId);
      /* Send negative response */
      Xcp_SendErrRes(XCP_ERR_ACCESS_LOCKED, protLayerId);
      /* Set XCP state to disconnecting to start the disconnection */
      /* The DISCONNECTING state is set at the end after sending the response to avoid disconnecting the TL(in MainFunction) before sending. */
      Xcp_NoInit[protLayerId].Session.XcpState_en = XCP_STATE_DISCONNECTING;
    }
    else
    {
      /* Send negative response */
      Xcp_SendErrRes(Error, protLayerId);
    }
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdUnlock.c: The command is not enabled - no code is needed in this file */
#endif



