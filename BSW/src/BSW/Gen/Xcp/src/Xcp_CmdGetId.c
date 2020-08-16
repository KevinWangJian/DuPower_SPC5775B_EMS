

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
#if (XCP_CMD_GET_ID_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This command returns identification of the slave to master
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetId(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdGetId_t* const CmdPtr = (const Xcp_CmdGetId_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetId_t* ResPtr = (Xcp_ResGetId_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variable */
  Xcp_AdrPtr GetIdPtr;

  /* Following ranges are allowed by ASAM:
   * V1.0 - V1.3: 0..4 and 128..255
   * V1.4 +     : 0..7 and 128..255
   */
# if ((XCP_ASAM_MAJOR_VERSION <= 1u) && (XCP_ASAM_MINOR_VERSION <= 3u))
  if ((CmdPtr->ReqIdentificationType_u8 > 4) && (CmdPtr->ReqIdentificationType_u8 < 128))
# else
  if ((CmdPtr->ReqIdentificationType_u8 > 7) && (CmdPtr->ReqIdentificationType_u8 < 128))
# endif
  { /* ID-Type not allowed */
    /* Send error message */
    Xcp_SendErrRes(XCP_ERR_CMD_SYNTAX, protLayerId);
  }
  else
  { /* Valid ID-Type */
    /* Initialize length with XCP_RES_GET_ID_LENGTH_MIN and response mode with XCP_GETID_TRANSFER_MODE0 */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_ID_LENGTH_MIN;
    ResPtr->Mode_u8 = XCP_GETID_TRANSFER_MODE0;

    /* Call application function to get length and pointer of the identification type requested by master */
    ResPtr->Length_u32 = XcpAppl_GetIdSlave(CmdPtr->ReqIdentificationType_u8, &GetIdPtr, protLayerId);

    if(ResPtr->Length_u32 != 0u)
    {
      /* assign length to global variable */

# if(XCP_MAX_CTO > 8)
      /* Length of the (Identification + XCP_RES_GET_ID_LENGTH_MIN) <= MAX_CTO, then directly send ID in response */
      if(((ResPtr->Length_u32) + XCP_RES_GET_ID_LENGTH_MIN) <= XCP_MAXCTO(protLayerId))
      {
        /* Fill complete GET_ID response length */
        XCP_RES_BUFFER_LENGTH(protLayerId) = ((ResPtr->Length_u32) + XCP_RES_GET_ID_LENGTH_MIN);
        /* Set mode as one */
        ResPtr->Mode_u8 = XCP_GETID_TRANSFER_MODE1;
        /* Copy the identification to the response */
        /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
        Xcp_MemCopy(ResPtr->IdentificationByte_au8, GetIdPtr, ResPtr->Length_u32);
      }
      else
# endif
      /* Length of the (Identification + XCP_RES_GET_ID_LENGTH_MIN) > MAX_CTO, then MTA must be set to GetId string for upload */
      {
# if (XCP_MEMORY_READ_PROTECTION == STD_ON)
        /* save GetIdPtr and Length so ReadAccessProtection will allow access to this area */
        Xcp_NoInit[protLayerId].GetId.GetIdPtr = GetIdPtr;
        Xcp_NoInit[protLayerId].GetId.GetIdLen_u32 = ResPtr->Length_u32;
# endif

        /* Set the MTA with the address of the identification */
        XCP_MTA(protLayerId) = GetIdPtr;
      }
    }
    else
    {
      /* Project doesn't support his Id type. Response with length 0. */
    }

    /* Fill response data */
    /* XCP_RES_BUFFER_LENGTH(protLayerId) set before */
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    /* ResPtr->Mode_u8 set before */
    ResPtr->Reserved_u16 = 0;
    /* ResPtr->Length_u32 set before */
    Xcp_SendRes(protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetId.c: The command is not enabled - no code is needed in this file */
#endif



