

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#if (XCP_CMD_START_STOP_DAQ_LIST_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

static Xcp_ErrorCode Xcp_DaqStartStopDaqList(const PduInfoType* XcpPacket, uint8 protLayerId);


/***************************************************************************************************
* Functions
***************************************************************************************************/
/**
****************************************************************************************************
This service handles the start, stop and select of DaqList.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdStartStopDaqList(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdStartStopDaqList_t* const CmdPtr = (const Xcp_CmdStartStopDaqList_t*) (void*) XcpPacket->SduDataPtr;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResStartStopDaqList_t* ResPtr = (Xcp_ResStartStopDaqList_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode  Error;

  /* initialization */
  Error = XCP_NO_ERROR;

  /* Check if the previous state is correct */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_WRITE_DAQ)
  {
    /* proceed to next state */
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_PREPARE_START;
  }

  /* Check if mode parameter is valid otherwise send error response ERR_MODE_NOT_VALID */
  if (CmdPtr->Mode_u8 > XCP_DAQLIST_SELECT)
  {
    /* Prepare error response XCP_ERR_MODE_NOT_VALID */
    Error = XCP_ERR_MODE_NOT_VALID;
  }
  /* Check if the DaqList is available */
  else if (CmdPtr->DaqListNum_u16 >= Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16)
  {
    /* Prepare error response ERR_OUT_OF_RANGE */
    Error = XCP_ERR_OUT_OF_RANGE;
  }
  /* Is the command sequence correct? This check is placed at latest possible point, because ERR_SEQUENCE is not specified in ASAM. */
  /* Other errors should be sent with higher priority */
  else if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en < XCP_DAQ_STATE_PREPARE_START)
  {
    /* Prepare error response ERR_SEQUENCE */
    Error = XCP_ERR_SEQUENCE;
  }
  else
  {
    /* execute command */
    Error = Xcp_DaqStartStopDaqList(XcpPacket, protLayerId);
  }

  if (Error == XCP_NO_ERROR)
  {
    /* Prepare positive response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_START_STOP_DAQ_LIST_LENGTH;
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
# if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
    if (Xcp_NoInit[protLayerId].Session.IdFieldType_en != XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE)
    {
      /* ID Field Type is relative, starts always with 0 */
      ResPtr->FirstPid_u8 = 0;
    }
    else
# endif
    {
      /* ID Field Type is absolute and should be less than 255 */
      ResPtr->FirstPid_u8 = (uint8) XCP_DAQ_ODTFIRST(CmdPtr->DaqListNum_u16, protLayerId);
    }
    /* Send positive response */
    Xcp_SendRes(protLayerId);
  }
  else if (Error == XCP_NO_RESPONSE)
  {
    /* do not send anything, response is generated later */
  }
  else
  {
    /* Send negative response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/***************************************************************************************************
* Local functions
***************************************************************************************************/
/**
****************************************************************************************************
This subfunction processes the StartStopDaqList Command
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     ErrorCode
\retval     XCP_NO_ERROR            processed successfully
\retval     XCP_NO_RESPONSE         DaqRam shifting in progress, don't send response
\retval     XCP_ERR_ACCESS_DENIED   requested address is protected
\retval     XCP_ERR_DAQ_CONFIG      DaqList is not correctly configured
\retval     XCP_ERR_SEQUENCE        SetDaqListMode has not been sent
***************************************************************************************************/
static Xcp_ErrorCode Xcp_DaqStartStopDaqList (const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdStartStopDaqList_t* const CmdPtr = (const Xcp_CmdStartStopDaqList_t*) (void*) XcpPacket->SduDataPtr;
  Xcp_ErrorCode Error;

  /* initialization */
  Error = XCP_NO_ERROR;

  /*--------------------------------------------------------------------------------------------------
    if mode == stop
  --------------------------------------------------------------------------------------------------*/
  if (CmdPtr->Mode_u8 == XCP_DAQLIST_STOP)
  {
    /* Stop this DaqList */
    Xcp_DaqListStop(CmdPtr->DaqListNum_u16, protLayerId);
    /* Recalculate PriorityList to remove stopped DaqList */
    Xcp_DaqCalculatePriorityList(protLayerId);
    /* Process DAQ running flag */
    Xcp_DaqProcessRunningFlag(protLayerId);
  }
  /*--------------------------------------------------------------------------------------------------
    if mode == start
  --------------------------------------------------------------------------------------------------*/
  else if (CmdPtr->Mode_u8 == XCP_DAQLIST_START)
  {
    Error = Xcp_DaqTriggerStateStartStop(XcpPacket, protLayerId);

    if (Error == XCP_NO_ERROR)
    {
      /* Start DaqList if not running */
      if( (XCP_DAQ_MODE(CmdPtr->DaqListNum_u16, protLayerId) & XCP_DAQLISTMODE_RUNNING) != XCP_DAQLISTMODE_RUNNING )
      {
        /* Start this DaqList */
        Xcp_DaqListStart(CmdPtr->DaqListNum_u16, protLayerId);
        /* Recalculate PriorityList to add started DaqList */
        Xcp_DaqCalculatePriorityList(protLayerId);
        /* Set DAQ-state to running */
        Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_RUNNING;
      }
    }
  }
  /*--------------------------------------------------------------------------------------------------
    if mode == select
  --------------------------------------------------------------------------------------------------*/
  else
  {
    Error = Xcp_DaqListFinalize(CmdPtr->DaqListNum_u16, protLayerId);
    if (Error == XCP_NO_ERROR)
    {
      /* Set the selected flag */
      XCP_DAQ_MODE(CmdPtr->DaqListNum_u16, protLayerId) |= XCP_DAQLISTMODE_SELECTED;
    }
  }

  return Error;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdStartStopDaqList.c: The command is not enabled - no code is needed in this file */
#endif



