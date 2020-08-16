

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


/***************************************************************************************************
* Functions
***************************************************************************************************/
#if (XCP_CMD_WRITE_DAQ_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles to write one ODT entry to a DAQ list defined by DAQ list pointer.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdWriteDaq(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdWriteDaq_t* const CmdPtr = (const Xcp_CmdWriteDaq_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check if the DAQ list is running at this time. In this case negative response ERR_DAQ_ACTIVE must be sent. */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)
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
    /* Call same function as for WRITE_DAQ_MULTIPLE */
    Error = Xcp_DaqWriteDaq(CmdPtr->Address_Ptr, CmdPtr->Size_u8, protLayerId);
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
  /* The command is not enabled */
#endif

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function performs the write of an ODT entry into a DAQ list.
\param[in]  Address       ODT entry address
\param[in]  Size          ODT entry size
\param[in]  protLayerId   Protocol Layer Id
\return     returns the error code in case the conditions are not fulfilled
\retval     XCP_NO_ERROR  write DAQ was possible
***************************************************************************************************/
Xcp_ErrorCode Xcp_DaqWriteDaq(Xcp_AdrPtr Address, uint8 Size, uint8 protLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;
  uint16 CurrentDaqListNum;
  Xcp_AdrPtr LocalAddress;

  /* Initialize variables */
  Error = XCP_NO_ERROR;
  LocalAddress = Address;

  /* assign current DAQ list number to local variable */
  CurrentDaqListNum = Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.DaqListNum_u16;

  /* Check if DAQ list pointer is out of range */
  if (Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16 >= Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryMax_u16)
  {
    Error = XCP_ERR_WRITE_PROTECTED;
  }
  else
  {
#if (XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON)

    /* Check if this is the first WriteDaq for this DAQ-list and DaqListMode has already been received
     * -> If yes, we can do the Address-Transformation right now
     */
    if ((XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) & XCP_DAQFLAG_FOLLOWING_WRITE_DAQ) == 0u)
    {
      XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) = XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) | XCP_DAQFLAG_FOLLOWING_WRITE_DAQ;

      if ((XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) & XCP_DAQFLAG_RECEIVED_DAQ_LIST_MODE) != 0u)
      { /* Mark in this DAQ that the Address Transformation was already done during WriteDaq and must not be done lateron */
        XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) = XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) | XCP_DAQFLAG_ADDR_TRANSFORMATION_DONE;
      }
    }

    if (((XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) & XCP_DAQFLAG_ADDR_TRANSFORMATION_DONE) != 0u))
    { /* Address-Transformation for the complete DAQ has to be done here */
      Error = Xcp_DaqTransformAndCheckOdtEntry((Xcp_AdrPtr*)&LocalAddress, Size, CurrentDaqListNum, protLayerId);
    }
#else /* XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON */
    /* If Read Protect is detected for the received address then set the Flag */
    if(Xcp_MemReadProtectionCheck(LocalAddress, Size, protLayerId) != XCP_NO_ERROR)
    {
      XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) = XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) | XCP_DAQFLAG_READ_PROTECTED;
      /* Set Error as Access Denied if SetDaqListMode command already received before Write DAQ Command && DAQ direction is DAQ  */
      if ( ((XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) & XCP_DAQFLAG_RECEIVED_DAQ_LIST_MODE) != 0u)
        && ((XCP_DAQ_MODE(CurrentDaqListNum, protLayerId)  & XCP_DAQLISTMODE_DIRECTION_STIM) == 0u)
         )
      {
        Error = XCP_ERR_ACCESS_DENIED;
      }
    }

# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
    /* If Write Protect is detected for the received address then set the Flag */
    if (Xcp_MemWriteProtectionCheck(LocalAddress, Size)!= XCP_NO_ERROR)
    {
      XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) = XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) | XCP_DAQFLAG_WRITE_PROTECTED;
      /* Set Error as Access Denied if SetDaqListMode command already received before Write DAQ Command && DAQ direction is STIM */
      if ( ((XCP_DAQ_FLAGS(CurrentDaqListNum, protLayerId) & XCP_DAQFLAG_RECEIVED_DAQ_LIST_MODE) != 0u)
        && ((XCP_DAQ_MODE(CurrentDaqListNum, protLayerId)  & XCP_DAQLISTMODE_DIRECTION_STIM) != 0u)
         )
      {
        Error = XCP_ERR_ACCESS_DENIED;
      }
    }
# endif /*(XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)*/

# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
    if (Error == XCP_NO_ERROR)
    {
      /* Check if the copy routine for this OdtEntry matches the one for the Odt (Set copy routine for the Odt if first OdtEntry or error) */
      Error = Xcp_DaqSetOdtCopyRoutine(LocalAddress, Size, Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.AbsOdtNum_u16, protLayerId);
    }
# endif /* XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON */
#endif /* XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON */

    /* If no error write new address & size to the location pointed by Daq list pointer */
    if (Error == XCP_NO_ERROR)
    {
      XCP_ODTENTRY_ADR(Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16, protLayerId)  = LocalAddress;
      XCP_ODTENTRY_SIZE(Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16, protLayerId) = Size;
      /* Increment Daq list pointer */
      Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16++;
    }
  }

  return Error;
}


#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
/* HIS METRIC COMF VIOLATION IN Xcp_CmdWriteDaq.c: XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ is not enabled - no data is needed in this file */
#endif



