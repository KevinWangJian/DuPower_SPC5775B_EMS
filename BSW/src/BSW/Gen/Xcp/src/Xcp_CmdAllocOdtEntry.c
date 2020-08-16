

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


#if (XCP_CMD_ALLOC_ODT_ENTRY_AVAILABLE == STD_ON)

/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static boolean  Xcp_DaqCheckOdtInAllDaqList(uint8 protLayerId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles ODT entries allocation required by the DAQ.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdAllocOdtEntry(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdAllocOdtEntry_t* const CmdPtr = (const Xcp_CmdAllocOdtEntry_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  uint16 AbsOdtNum;
  Xcp_ErrorCode Error;

  /* Check if the previous state is correct */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_ALLOC_ODT)
  {
    if (Xcp_DaqCheckOdtInAllDaqList(protLayerId) != FALSE)
    {
      Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_ALLOC_ODT_ENTRY;
    }
  }

  /* Check if the command was received in the correct sequence order. */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en != XCP_DAQ_STATE_ALLOC_ODT_ENTRY)
  {
    /* Return Sequence Error */
    Error = XCP_ERR_SEQUENCE;
  }
  /* Check if the command parameters are valid  */
  /* In first ODT there can be 0 ODT Entries in case of 4 Bytes Timestamp and 4 Bytes ID Field (MAX_DTO == 8) */
  /* Required DAQ list must be already defined. */
  /* Required ODT number must be defined for this list. */
  else if(  ( (CmdPtr->OdtEntriesCount_u8 == 0) && (CmdPtr->OdtNum_u8 != 0) )
         || (CmdPtr->DaqListNum_u16 >= Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16)
         || (CmdPtr->OdtNum_u8 >= XCP_DAQ_ODTCNT(CmdPtr->DaqListNum_u16, protLayerId))
         )
  {
    /* Return ERR_OUT_OF_RANGE. */
    Error = XCP_ERR_OUT_OF_RANGE;
  }
  /* Check if ALLOC_ODT_ENTRY was already receive for this Odt */
  else if (XCP_ODT_ODTENTRYCNT(Xcp_Daq_GetAbsOdtNum(CmdPtr->DaqListNum_u16, CmdPtr->OdtNum_u8, protLayerId), protLayerId) != 0)
  {
    /* Send error response ERR_SEQUENCE. */
    Error = XCP_ERR_SEQUENCE;
  }
  /* Check if there is sufficient memory for the required configuration. */
  else if (Xcp_DaqRamCheck(0, 0, CmdPtr->OdtEntriesCount_u8, protLayerId) == FALSE)
  {
    /* If there is not enough memory to allocate this list, send negative response ERR_MEMORY_OVERFLOW. */
    Error = XCP_ERR_MEMORY_OVERFLOW;
  }
  else
  {
    AbsOdtNum = Xcp_Daq_GetAbsOdtNum(CmdPtr->DaqListNum_u16, CmdPtr->OdtNum_u8, protLayerId);
    /* Store data to Odt */
    /* Memory was set to zero in Xcp_CmdAllocOdt so no initialisation of variables with value 0 is necessary here */
    XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId) = Xcp_NoInit[protLayerId].DaqConfig.OdtEntryCnt_u16;
    XCP_ODT_ODTENTRYCNT(AbsOdtNum, protLayerId) = CmdPtr->OdtEntriesCount_u8;

    /* Add OdtEntriesCount to global OdtEntryCnt */
    Xcp_NoInit[protLayerId].DaqConfig.OdtEntryCnt_u16 += CmdPtr->OdtEntriesCount_u8;
    /* Prepare positive response. */
    Error = XCP_NO_ERROR;
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


/***************************************************************************************************
* Local functions
***************************************************************************************************/

/**
****************************************************************************************************
This function checks whether for each DaqList at least one ODT exist.
\param[in]  protLayerId   Protocol Layer Id
\return     the status of ODT allocation in all DAQs
\retval     TRUE  all ODTs are allocated
\retval     FALSE  not all DAQs have ODTs allocated
***************************************************************************************************/
static boolean Xcp_DaqCheckOdtInAllDaqList(uint8 protLayerId)
{
  /* Local variables */
  uint32 DaqListNo;
  boolean ret_val;

  /* Initial values */
  ret_val = TRUE;

  for (DaqListNo = 0; DaqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; DaqListNo++)
  {
    /* if ODTs are not allocated to at least one DAQ then return FALSE */
    if (XCP_DAQ_ODTCNT(DaqListNo, protLayerId) == 0)
    {
      ret_val = FALSE;
      break;
    }
  }
  return ret_val;
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdAllocOdtEntry.c: The command is not enabled - no code is needed in this file */
#endif



