

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
#if (XCP_CMD_GET_DAQ_CLOCK_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service prepares the receive timestamp.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetDaqClock(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetDaqClock_t* ResPtr = (Xcp_ResGetDaqClock_t *) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_Timestamp_t TimestampType;

  XCP_PARAM_UNUSED(XcpPacket);

  /* Get TimestampType for actual connected transport layer */
  TimestampType = Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TimestampType_en;

  /* Command only supported in case timestamp is configured for this transport layer */
  if (TimestampType != XCP_TIMESTAMP_TYPE_NO_TIME_STAMP)
  {
    /* Reduce internal 4 byte timestamp to needed number of bytes for this transport layer */
    uint32 NumShiftBits = (4-(uint8)TimestampType) * 8;
    uint32 Timestamp = (XcpAppl_GetTimestamp()<<NumShiftBits)>>NumShiftBits;

    /* Send positive response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_DAQ_CLOCK_LENGTH;
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    ResPtr->Reserved_u8 = 0;
    ResPtr->Reserved_u16 = 0;
    ResPtr->Timestamp_u32 = Timestamp;

    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Send error */
    Xcp_SendErrRes(XCP_ERR_CMD_UNKNOWN, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetDaqClock.c: The command is not enabled - no code is needed in this file */
#endif



