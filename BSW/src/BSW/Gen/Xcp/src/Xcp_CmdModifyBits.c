

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
#if (XCP_CMD_MODIFY_BITS_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles the modify bits request and its response processing
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdModifyBits(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdModifyBits_t* const CmdPtr = (const Xcp_CmdModifyBits_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;
  uint8 Length;
  uint32 A;
  uint16 MA;
  uint16 MX;
  uint8 S;

  /* Initial values */
  Length = sizeof(A);

  /* Read Data from current MTA */
  Error = Xcp_MemRead((Xcp_AdrPtr)&A, Length, protLayerId);

  if (Error == XCP_NO_ERROR)
  {
    XCP_MTA(protLayerId) -= Length;

    MA = CmdPtr->ANDmask_u16;
    MX = CmdPtr->XORmask_u16;
    S  = CmdPtr->ShiftValue_u8;

    /* Algorithm from ASAM specification - parenthesis adapted to satisfy MISRA*/
    A = ( ( A & (~(((uint32)((uint16)~MA))<<S)) ) ^ (((uint32)MX)<<S) );

    /* Start write process */
    Error = Xcp_MemWrite((Xcp_AdrPtrConst)&A, Length, protLayerId);

    /* Xcp_MemWrite modifies MTA if return value is XCP_NO_ERROR or XCP_NO_RESPONSE. So MTA must be reduced to old value. */
    if ((Error == XCP_NO_ERROR) || (Error == XCP_NO_RESPONSE))
    {
      XCP_MTA(protLayerId) -= Length;
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
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdModifyBits.c: The command is not enabled - no data is needed in this file */
#endif



