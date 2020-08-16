

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
#if (XCP_CMD_WRITE_DAQ_MULTIPLE_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to write multiple ODT entry to a DAQ list defined by DAQ list pointer.
\param[in]  XcpPacket     received XcpPacket
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_CmdWriteDaqMultiple: Function contains very simple "else if" statements. HIS metric compliance would decrease readability and maintainability. */
void Xcp_CmdWriteDaqMultiple(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdWriteDaqMultiple_t* const CmdPtr = (const Xcp_CmdWriteDaqMultiple_t*) (void*) XcpPacket->SduDataPtr;
  const Xcp_CmdWriteDaqMultiple_SingleElement_t* SingleElement;

  /* Local variables */
  Xcp_ErrorCode Error;
  uint8 i;

  /* Initialize variables */
  Error = XCP_NO_ERROR;

  /* Check if possible to handle command in this Protocol Layer */
  if (XCP_MAXCTO(protLayerId) < 10)
  {
    /* Error - Command unknown */
    Error = XCP_ERR_CMD_UNKNOWN;
  }
  /* Check if length of the received packet is valid */
  else if ((2u + (CmdPtr->NumDaq_u8 * 8u)) > XcpPacket->SduLength)
  {
    /* Command syntax error */
    Error = XCP_ERR_CMD_SYNTAX;
  }
  /* Check if the DAQ list is running at this time. In this case negative response ERR_DAQ_ACTIVE must be sent. */
  else if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)
  {
    Error = XCP_ERR_DAQ_ACTIVE;
  }
  /* Check if DAQ list pointer is out of range */
  else if (Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16 >= Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryMax_u16)
  {
    Error = XCP_ERR_WRITE_PROTECTED;
  }
  /* Is the command sequence correct? This check is placed at latest possible point, because ERR_SEQUENCE is not specified in ASAM. */
  /* Other errors should be sent with higher priority */
  else if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en != XCP_DAQ_STATE_WRITE_DAQ)
  {
    /* Set Error code - ERR_SEQUENCE */
    Error = XCP_ERR_SEQUENCE;
  }
  else
  {
    /* empty, required for MISRA */
  }

  /* Initialize loop variable */
  i = 0;

  /* Store all the received DAQs */
  while ( (Error == XCP_NO_ERROR) && (i < CmdPtr->NumDaq_u8) )
  {
    /* MR12 RULE 11.5, 1.1 VIOLATION: 4-Byte-Alignment is ensured as SduDataPtr is aligned and we go i * 8 forward.
                                      This cast allows easier (= safer) access to the data in the buffer
                                      Casting over void* is necessary as otherwise some compilers complain */
    SingleElement = (const Xcp_CmdWriteDaqMultiple_SingleElement_t*) (void*) (XcpPacket->SduDataPtr + (i * 8));

    /* Call same function as for WRITE_DAQ */
    Error = Xcp_DaqWriteDaq(SingleElement->Address_Ptr, SingleElement->Size_u8, protLayerId);

    /* increase loop index */
    i++;
  }

  if (Error == XCP_NO_ERROR)
  {
    /* Send positive response */
    Xcp_SendPosRes(protLayerId);
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
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdWriteDaqMultiple.c: The command is not enabled - no code is needed in this file */
#endif



