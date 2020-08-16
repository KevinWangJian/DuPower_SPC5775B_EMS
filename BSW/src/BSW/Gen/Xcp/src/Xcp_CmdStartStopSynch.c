

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
#if (XCP_CMD_START_STOP_SYNCH_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles a start, stop for selected DaqList or stop all running lists.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdStartStopSynch(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdStartStopSynch_t* const CmdPtr = (const Xcp_CmdStartStopSynch_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* initialization */
  Error = Xcp_DaqTriggerStateStartStop(XcpPacket, protLayerId);

  /* check if mode parameter is valid otherwise send error response ERR_MODE_NOT_VALID */
  /* Do this check also Xcp_DaqTriggerStateStartStop() has an error, because ERR_SEQUENCE is not specified in ASAM. */
  if (CmdPtr->Mode_u8 > XCP_DAQLIST_SYNC_STOPSEL)
  {
    /* Prepare error response XCP_ERR_MODE_NOT_VALID */
    Error = XCP_ERR_MODE_NOT_VALID;
  }
  else if (Error == XCP_NO_ERROR)
  {
    /*--------------------------------------------------------------------------------------------------
      if mode == stop all
    --------------------------------------------------------------------------------------------------*/
    if (CmdPtr->Mode_u8 == XCP_DAQLIST_SYNC_STOPALL)
    {
      Xcp_DaqListStopAll(protLayerId);
    }
    /*--------------------------------------------------------------------------------------------------
      if mode == start selected
    --------------------------------------------------------------------------------------------------*/
    else if (CmdPtr->Mode_u8 == XCP_DAQLIST_SYNC_STARTSEL)
    {
      Xcp_DaqListStartSelected(protLayerId);
    }
    /*--------------------------------------------------------------------------------------------------
      if mode == stop selected
    --------------------------------------------------------------------------------------------------*/
    else
    {
      Xcp_DaqListStopSelected(protLayerId);
    }
  }
  else
  {
    /* error occurred or no response requested */
  }

  if (Error == XCP_NO_ERROR)
  {
    /* Send positive response */
    Xcp_SendPosRes(protLayerId);
  }
  else if (Error == XCP_NO_RESPONSE)
  {
    /* do not send anything */
  }
  else if (Error == XCP_ERR_ACCESS_DENIED)
  {
    /* Function Xcp_DaqTriggerStateStartStop() can set ACCESS_DENIED. Send ERR_DAQ_CONFIG instead as allowed error in ASAM. */
    Xcp_SendErrRes(XCP_ERR_DAQ_CONFIG, protLayerId);
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
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdStartStopSynch.c: The command is not enabled - no code is needed in this file */
#endif



