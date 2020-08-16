

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
This command reads data from slave's memory (reads from slave to master) and
does not support block transfer mode
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdShortUpload(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdShortUpload_t* const CmdPtr = (const Xcp_CmdShortUpload_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResShortUpload_t* ResPtr = (Xcp_ResShortUpload_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check request upload size */
  if (CmdPtr->NumOfDataElements_u8 > (XCP_MAXCTO(protLayerId) - 1) )
  {
    Error = XCP_ERR_OUT_OF_RANGE;
  }
  else
  {
    /* Store MTA */
    XCP_MTA(protLayerId) = CmdPtr->Address_Ptr;

    /* Read Data from current MTA */
    Error = Xcp_MemRead(ResPtr->DataElement_au8, CmdPtr->NumOfDataElements_u8, protLayerId);
  }

  /* Check response */
  if (Error == XCP_NO_ERROR)
  {
    /* Prepare and send positive response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = 1 + CmdPtr->NumOfDataElements_u8;
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    /* ResPtr->DataElement_au8 is set before */
    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Send error */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



