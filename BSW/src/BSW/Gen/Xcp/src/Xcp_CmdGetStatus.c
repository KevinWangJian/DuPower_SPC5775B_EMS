

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
This command is to get current session status from slave and handles response processing
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdGetStatus(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResGetStatus_t* ResPtr = (Xcp_ResGetStatus_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  XCP_PARAM_UNUSED(XcpPacket);

  /* prepare response */
  /* set length of response */
  XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_GET_STATUS_LENGTH;

  /* set response PID */
  ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
  /* store current session status */
  ResPtr->Status_u8 =  XCP_RESUME_SESSION_STATUS(protLayerId);
  #if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)
  {
    ResPtr->Status_u8 |= XCP_DAQ_RUNNING;
  }
  #endif
  /* store current resource protection status */
  ResPtr->ProtectionStatus_u8 = Xcp_NoInit[protLayerId].Session.ResourceProtStatus_u8;
  ResPtr->Reserved_u8 = 0;
  /* Send the correct SessionConfigID_u16 in case RESUME mode is STD_ON. */
#if (XCP_RESUME_MODE == STD_ON)
  ResPtr->SessionConfigID_u16 = Xcp_NoInit[protLayerId].Session.SessionConfId_u16;
#else
  /* session config ID is reset to 0 */
  ResPtr->SessionConfigID_u16 = 0;
#endif

  /* prepare positive response and copy it in the Queue */
  Xcp_SendRes(protLayerId);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



