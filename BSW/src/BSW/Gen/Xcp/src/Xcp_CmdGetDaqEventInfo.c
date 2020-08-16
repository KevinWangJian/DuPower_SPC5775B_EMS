

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
#if (XCP_CMD_GET_DAQ_EVENT_INFO_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to get the DAQ Event Channel Info.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetDaqEventInfo(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdGetDaqEventInfo_t* const CmdPtr = (const Xcp_CmdGetDaqEventInfo_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetDaqEventInfo_t* ResPtr = (Xcp_ResGetDaqEventInfo_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Initialize variables */
  Error = XCP_NO_ERROR;

  /* Specified event channel number is available? */
  if(CmdPtr->EventChannelNum_u16 >= XCP_MAX_EVENT_CHANNEL)
  {
    Error = XCP_ERR_OUT_OF_RANGE;
  }

  if (Error == XCP_NO_ERROR)
  {
    /* Set response length */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_DAQ_EVENT_INFO_LENGTH;

    /* Prepare response to send */
    ResPtr->PacketId_u8                = XCP_PACKET_ID_RES;

    /* Get consistency-information (stored per PL) & Event channel direction */
    ResPtr->DaqEventProperties_u8       = (uint8)((uint32)Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].Consistency_en << 6) | Xcp_PlCfgConst.EventChannelCfg[CmdPtr->EventChannelNum_u16].EventChannelDirection_u8;
    ResPtr->MaxDaqList_u8               = 0x01u;
    ResPtr->EventChannelNameLength_u8   = 0x00u;
    ResPtr->EventChannelTimeCycle_u8    = Xcp_PlCfgConst.EventChannelCfg[CmdPtr->EventChannelNum_u16].EventChannelTimeCycle_u8;
    ResPtr->EventChannelTimeUnit_u8     = Xcp_PlCfgConst.EventChannelCfg[CmdPtr->EventChannelNum_u16].EventChannelTimeUnit_u8;
    ResPtr->EventChannelPriority_u8     = Xcp_PlCfgConst.EventChannelCfg[CmdPtr->EventChannelNum_u16].EventChannelPriority_u8;

    /* Send positive response */
    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Send negative response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetDaqEventInfo.c: The command is not enabled - no code is needed in this file */
#endif



