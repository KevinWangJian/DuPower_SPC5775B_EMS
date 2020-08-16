

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
#if (XCP_CMD_GET_DAQ_LIST_MODE_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to get the information on the current mode of the specified DAQ list
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetDaqListMode(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdGetDaqListMode_t* const CmdPtr = (const Xcp_CmdGetDaqListMode_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetDaqListMode_t* ResPtr = (Xcp_ResGetDaqListMode_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  if (CmdPtr->DaqListNum_u16 >= Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16)
  {
    /* Send negative response */
    Xcp_SendErrRes(XCP_ERR_OUT_OF_RANGE, protLayerId);
  }
  else
  {
    /* set length response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_DAQ_LIST_MODE_LENGTH;
    /* Set Pid */
    ResPtr->PacketId_u8         = XCP_PACKET_ID_RES;
    ResPtr->Mode_u8             = XCP_DAQ_MODE(CmdPtr->DaqListNum_u16, protLayerId);
    ResPtr->Reserved_u16        = 0;
    ResPtr->EventChannelNum_u16 = XCP_DAQ(CmdPtr->DaqListNum_u16, protLayerId).EventChannelNum_u16;
    ResPtr->Prescaler_u8        = XCP_DAQ(CmdPtr->DaqListNum_u16, protLayerId).Prescaler_u8;
    ResPtr->DaqListPriority_u8  = XCP_DAQ_PRIO(CmdPtr->DaqListNum_u16, protLayerId);

    /* Send positive response */
    Xcp_SendRes(protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdGetDaqListMode.c: The command is not enabled - no code is needed in this file */
#endif



