

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
#if (XCP_CMD_READ_DAQ_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to read one ODT entry to a DAQ list defined by DAQ list pointer.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdReadDaq(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  Xcp_ResReadDaq_t* ResPtr = (Xcp_ResReadDaq_t*) (void*) XCP_RES_BUFFER_PTR(protLayerId);

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Initialize variables */
  Error = XCP_NO_ERROR;

  /* Check if DAQ list pointer is out of range */
  if (Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16 >= Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryMax_u16)
  {
    Error = XCP_ERR_WRITE_PROTECTED;
  }
  /* Is the command sequence correct? This check is placed at latest possible point, because ERR_SEQUENCE is not specified in ASAM. */
  /* Other errors should be sent with higher priority */
  else if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en < XCP_DAQ_STATE_WRITE_DAQ)
  {
    /* Set Error code - ERR_SEQUENCE */
    Error = XCP_ERR_SEQUENCE;
  }
  else
  {
    /* to remove MISRA warning */
  }

  if (Error == XCP_NO_ERROR)
  {
    /* prepare response */
    /* set length of response */
    XCP_RES_BUFFER_LENGTH(protLayerId) = XCP_RES_READ_DAQ_LENGTH;

    /* set response PID */
    ResPtr->PacketId_u8 = XCP_PACKET_ID_RES;
    /* store bit offset */
    ResPtr->BitOffset_u8 = 0xFFu;
    /* size of DAQ element */
    ResPtr->SizeOfDaqElement_u8 = XCP_ODTENTRY_SIZE(Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16, protLayerId);
    /* address extension of DAQ element */
    ResPtr->AddrExtension_u8 = 0x00u;
    /* address of DAQ element */
    ResPtr->Address_Ptr = XCP_ODTENTRY_ADR(Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16, protLayerId);

    /* Increment Daq list pointer */
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16++;

    /* prepare positive response and copy it in the Queue */
    Xcp_SendRes(protLayerId);
  }
  else
  {
    /* Send negative response */
    Xcp_SendErrRes(Error, protLayerId);
  }
  XCP_PARAM_UNUSED(XcpPacket);

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdReadDaq.c: The command is not enabled - no code is needed in this file */
#endif



