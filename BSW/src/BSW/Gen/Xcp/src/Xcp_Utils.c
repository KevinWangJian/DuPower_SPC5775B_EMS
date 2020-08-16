

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
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function reads data at the requested address with requested length based on the Protocol layer
\param[in]  AddrPtrDst    destination pointer
\param[in]  Length        length of the data to read
\param[in]  protLayerId   Protocol Layer Id
\return     ErrorCode
\retval     XCP_NO_ERROR            Reading successful
\retval     XCP_ERR_ACCESS_DENIED   Source or destination is in restricted memory area
\retval     XCP_ERR_PAGE_NOT_VALID  Calibration page is not valid
***************************************************************************************************/
Xcp_ErrorCode Xcp_MemRead(Xcp_AdrPtr AddrPtrDst, uint8 Length, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_ErrorCode Error;
  Xcp_AdrPtr LocalMta;

  /* Store address in local variable */
  LocalMta = XCP_MTA(protLayerId);

  if (LocalMta == NULL_PTR)
  {
    Error = XCP_ERR_WRITE_PROTECTED;
  }
  else if (Xcp_Cleared[protLayerId].BgActivityState != XCP_BG_IDLE)
  { /* Another background activity is running -> report BUSY */
    Error = XCP_ERR_CMD_BUSY;
  }
  else
#if (XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON)
  {
    /* Call Address-transformation-function */
    Error = XcpAppl_StaticAddressTransformation(&LocalMta, Length, XCP_EVENT_CHANNEL_NOT_USED, XCP_CONTEXT_UPLOAD);
  }

  if (Error == XCP_NO_ERROR)
#endif
  {
    /* Check source memory protection */
    Error = Xcp_MemReadProtectionCheck(LocalMta, Length, protLayerId);
  }

  /*  XCP_NO_ACCESS_HIDE */
  if (Error == XCP_NO_ACCESS_HIDE)
  {
    /* Fill destination buffer with zeroes */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemSet() are declared as (void*) for generic implementation of MemSet. */
    Xcp_MemSet(AddrPtrDst, 0, Length);

    /* Set error code to OK */
    Error = XCP_NO_ERROR;
  }
  else if (Error == XCP_NO_ERROR)
  {

#if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
    /* Copy data with application function */
    Error = XcpAppl_MemRead(AddrPtrDst, LocalMta, Length, protLayerId);
#else
    /* Copy data with internal function */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(AddrPtrDst, LocalMta, Length);
    Error = XCP_NO_ERROR;
#endif

    /* Check if success */
    if (Error == XCP_NO_ERROR)
    {
      /* Update MTA pointer */
      XCP_MTA(protLayerId) += Length;
    }
  }
  else
  {
    /* other errors are sent out directly */
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return(Error);
}

#if(XCP_CALIBRATION_CAL == STD_ON)

/**
****************************************************************************************************
Function writes data at the requested address with requested length based on the Protocol layer
\param[in]  AddrPtrSrc    source pointer
\param[in]  Length        length of the data to write
\param[in]  protLayerId   Protocol Layer Id
\return     ErrorCode
\retval     XCP_NO_ERROR              Writing successful
\retval     XCP_ERR_ACCESS_DENIED     Source or destination is in restricted memory area
\retval     XCP_ERR_PAGE_NOT_VALID    Calibration page is not valid
\retval     XCP_ERR_WRITE_PROTECTED   Destination is write protected
***************************************************************************************************/
Xcp_ErrorCode Xcp_MemWrite(Xcp_AdrPtrConst AddrPtrSrc, uint8 Length, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_ErrorCode Error;
  Xcp_AdrPtr LocalMta;

  /* Store address in local variable */
  LocalMta = XCP_MTA(protLayerId);

  if (LocalMta == NULL_PTR)
  {
    Error = XCP_ERR_WRITE_PROTECTED;
  }
  else if (Xcp_Cleared[protLayerId].BgActivityState != XCP_BG_IDLE)
  { /* Another background activity is running -> report BUSY */
    Error = XCP_ERR_CMD_BUSY;
  }
  else
#if (XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON)
  {
    /* Call Address-transformation-function */
    Error = XcpAppl_StaticAddressTransformation(&LocalMta, Length, XCP_EVENT_CHANNEL_NOT_USED, XCP_CONTEXT_DOWNLOAD);
  }

  if (Error == XCP_NO_ERROR)
#endif
  {
    /* Check dest memory protection */
    Error = Xcp_MemWriteProtectionCheck(LocalMta, Length);
  }


  if (Error == XCP_NO_ERROR)
  {
#if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
    /* Check if data should be copied to global buffer */
    if (Xcp_Cleared[protLayerId].Mem.DownloadBuffer_au8 != AddrPtrSrc)
    {
      /* Copy data to global buffer. XcpAppl_MemWrite might not work with local variable. */
      /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
      Xcp_MemCopy(Xcp_Cleared[protLayerId].Mem.DownloadBuffer_au8, AddrPtrSrc, Length);
    }
    /* Write data with application function */
    Error = XcpAppl_MemWrite(LocalMta, Xcp_Cleared[protLayerId].Mem.DownloadBuffer_au8, Length, protLayerId);

    /* Check if success */
    if (Error == XCP_NO_ERROR)
    {
      /* Update MTA pointer */
      XCP_MTA(protLayerId) += Length;
    }
    else if (Error == XCP_NO_RESPONSE)
    {
      /* Set Download size to trigger Xcp_MemWriteMainFunction */
      Xcp_Cleared[protLayerId].Mem.DownloadSize_u8 = Length;
      Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_MEM_WRITE;
    }
    else
    {
      /* other errors are sent out directly */
    }
#else
    /* Lock interrupts */
    SchM_Enter_Xcp_DownloadNoNest();

    /* Copy data with internal function */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(LocalMta, AddrPtrSrc, Length);

    /* Unlock interrupts */
    SchM_Exit_Xcp_DownloadNoNest();

    /* Update MTA pointer */
    XCP_MTA(protLayerId) += Length;

    Error = XCP_NO_ERROR;
#endif
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return(Error);
}

/**
****************************************************************************************************
Background process of WriteMTA for the requested Protocol layer
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_MemWriteMainFunction(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

#if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
  /* Local variables */
  Xcp_ErrorCode Error;

  /* Call application function */
  Error = XcpAppl_MemWriteMainFunction(protLayerId);

  if (Error == XCP_NO_ERROR)
  {
    /* Update MTA pointer */
    XCP_MTA(protLayerId) += Xcp_Cleared[protLayerId].Mem.DownloadSize_u8;

    /* Clear background activity */
    Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_IDLE;
  }

  /* Send response */
  Xcp_DownloadRes(Error, protLayerId);
#else
  XCP_PARAM_UNUSED(protLayerId);
#endif /* #if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON) */

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#endif /* #if(XCP_CALIBRATION_CAL == STD_ON) */


#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
/**
****************************************************************************************************
This function calculates the memory consumption of the daq config and sets the required pointers accordingly.
\param[in]  AddDaqList    number of DaqList to add for memory calculation
\param[in]  AddOdt        number of Odt to add for memory calculation
\param[in]  AddOdtEntry   number of OdtEntry to add for memory calculation
\param[in]  protLayerId   Protocol Layer Id
\return     bytes required for daq configuration
***************************************************************************************************/
uint32 Xcp_DaqRamCalc(uint16 AddDaqList, uint8 AddOdt, uint8 AddOdtEntry, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_DaqConfig_t* DaqConfig;
  uint32  memReq;
  uint32  DaqListCntNew_u32;
  uint32  OdtCntNew_u32;
  uint32  OdtEntryCntNew_u32;

  /* initialization */
  DaqConfig = &Xcp_NoInit[protLayerId].DaqConfig;

  DaqListCntNew_u32  = DaqConfig->DaqListCnt_u16  + AddDaqList;
  OdtCntNew_u32      = DaqConfig->OdtCnt_u16      + AddOdt;
  OdtEntryCntNew_u32 = DaqConfig->OdtEntryCnt_u16 + AddOdtEntry;

  /* check if all (new) values are within limits */
  if ( (DaqListCntNew_u32  > XCP_MAX_DAQ)
    || (OdtCntNew_u32      > XCP_MAX_ODT)
    || (OdtEntryCntNew_u32 > XCP_MAX_ODTENTRY)
    || (DaqConfig->DaqRamPtr_pu8 == NULL_PTR)
     )
  {
    /* to prevent counter overflow, force memory overflow error */
    memReq = 0xFFFFFFFFu;
  }
  else
  {
    /* --------------------------------------------------------------------------------------------------
     * DAQ pointer
     * ----------------------
     * Start:        Take over dynamic ram pointer
     * Mem required: DaqListCntNew_u32 * XCP_SIZEOF_DAQ
     * --------------------------------------------------------------------------------------------------
     */
    /* MR12 RULE 11.5, 1.1 VIOLATION: The calling layers ensure 4-Byte-Alignment. No other possibility to assign the pointer to the other pointer
                                      Casting over void* is necessary as otherwise some compilers complain */
    DaqConfig->DaqList_p = (Xcp_DaqList_t*) (void*) DaqConfig->DaqRamPtr_pu8;

    /* --------------------------------------------------------------------------------------------------
     * ODT pointer
     * ----------------------
     * Start:        After DAQ-Lists - 2-byte-aligned
     * Mem required: OdtCntNew_u32 * XCP_SIZEOF_ODT
     * --------------------------------------------------------------------------------------------------
     */
    /* MR12 RULE 11.4, 11.5, 11.6 VIOLATION: We want to have a pointer to a 2-byte-aligned address at/after the given element (address), hence casting is necessary */
    DaqConfig->Odt_p = (Xcp_Odt_t*) (void*)(XCP_2BYTE_ALIGN((uint32)&DaqConfig->DaqList_p[DaqListCntNew_u32]));

    /* --------------------------------------------------------------------------------------------------
     * OdtEntryAddress-Pointer
     * ----------------------
     * Start:        After ODTs - 4-byte-aligned
     * Mem required: OdtEntryCntNew_u32 * 4 (Address is 32-bit)
     * --------------------------------------------------------------------------------------------------
     */
    /* MR12 RULE 11.4, 11.5, 11.6 VIOLATION: We want to have a pointer to a 4-byte-aligned address at/after the given element (address), hence casting is necessary */
    DaqConfig->OdtEntryAdr_p  = (Xcp_AdrPtr*) (void*)(XCP_4BYTE_ALIGN((uint32)&DaqConfig->Odt_p[OdtCntNew_u32]));

    /* --------------------------------------------------------------------------------------------------
     * OdtEntrySize-Pointer
     * ----------------------
     * Start:        After OdtEntryAddresses (automatically 4-byte-aligned)
     * Mem required: OdtEntryCntNew_u32 * 1 (Size is 8-bit)
     * --------------------------------------------------------------------------------------------------
     */
    /* MR12 RULE 11.5, 1.1 VIOLATION: No problem with alignment as an OdtEntry is 1 byte */
    DaqConfig->OdtEntrySize_p = (uint8*) (void*)(&DaqConfig->OdtEntryAdr_p[OdtEntryCntNew_u32]);

    /* --------------------------------------------------------------------------------------------------
     * PriorityList-Pointer
     * ----------------------
     * Start:        After OdtEntrySizes - 2-byte-aligned
     * Mem required: DaqListCntNew_u32 * sizeof(DaqConfig->DaqListCnt_u16) - 2 Bytes per configured DaqList (although STIM DAQs do not need an entry)
     * --------------------------------------------------------------------------------------------------
     */
    /* MR12 RULE 11.4, 11.5, 11.6 VIOLATION: We want to have a pointer to a 2-byte-aligned address at/after the given element (address), hence casting is necessary */
    DaqConfig->PriorityList_p = (uint16*) (void*)(XCP_2BYTE_ALIGN((uint32)&DaqConfig->OdtEntrySize_p[OdtEntryCntNew_u32]));

    /* --------------------------------------------------------------------------------------------------
     * Queue-Pointer
     * ----------------------
     * Start:        After PriorityList - 4-byte-aligned
     * Mem required: Xcp_DaqQueRamCalc(AddOdt, FALSE, protLayerId)
     * --------------------------------------------------------------------------------------------------
     */
    /* MR12 RULE 11.4, 11.5, 11.6 VIOLATION: We want to have a pointer to a 4-byte-aligned address at/after the given element (address), hence casting is necessary */
    DaqConfig->DaqQue_p = (uint8*) (void*)(XCP_4BYTE_ALIGN((uint32)&DaqConfig->PriorityList_p[DaqListCntNew_u32]));

    /* Calculate required memory for everything (last pointer + size required for last data - start pointer) */
    /* MR12 RULE 11.4 VIOLATION: We are calculating the required memory by subtracting the two pointers. As addresses are always uint32, cast is no problem */
    memReq = ((uint32)DaqConfig->DaqQue_p + Xcp_DaqQueRamCalc(AddOdt, FALSE, protLayerId)) - (uint32)DaqConfig->DaqList_p;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return memReq;
}


/**
****************************************************************************************************
This function calculates the memory consumption of the daq queue and initializes the queue pointers.
\param[in]  AddOdt          number of Odt to add for memory calculation
\param[in]  setQuePointers  TRUE: Queue pointers are set, FALSE: only memory calculation
\param[in]  protLayerId     Protocol Layer Id
\return     bytes required for daqlist queue
***************************************************************************************************/
uint32 Xcp_DaqQueRamCalc(uint8 AddOdt, boolean setQuePointers, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

    /* Local variables */
    Xcp_DaqList_t *daqListPtr;
    uint32 MemReq;
    uint16_least DAQListNo;
    uint16 OdtElementsInQue;
    uint8  Odts;

    /* initialization */
    MemReq = 0;

    /* Loop through all DaqList */
    for (DAQListNo = 0; DAQListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; DAQListNo++)
    {
      daqListPtr = &(XCP_DAQ(DAQListNo, protLayerId));
      if (setQuePointers == TRUE)
      {
        /* alloc Buffer */
        daqListPtr->DaqListQue_p = &(Xcp_NoInit[protLayerId].DaqConfig.DaqQue_p[MemReq]);
      }

      /* fetch the numbers of ODTs in this daqlist */
      Odts = daqListPtr->OdtCnt_u8;

      if (Odts == 0)
      {
        /* first daqlist with no odts, assume odts are added to this daqlist */
        Odts = AddOdt;
        /* reset AddOdt to avoid multiple counting */
        AddOdt = 0;
      }
      /* calc the memory needed */
  #if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
      if ( (daqListPtr->Mode_u8 & XCP_DAQLISTMODE_DIRECTION_STIM) != 0u)
      {
        MemReq += (Odts * XCP_MAXDTO_4ALIGNED(protLayerId) * XCP_ODT_STIM_BUFFER_ELEMENT_SIZE);
      }
      else
  #endif
      {
        OdtElementsInQue = (uint16) Xcp_Daq_OdtElementsInDaqQue(Odts); /*PRQA S 4119*/ /* Cast from float to uint32: rounding is intended */
        MemReq += (OdtElementsInQue * XCP_MAXDTO_4ALIGNED(protLayerId));

        if (setQuePointers == TRUE)
        {
          /* Initialize the DAQ Queue */
          Xcp_CreateQue(daqListPtr, OdtElementsInQue);
        }
      }
      /* alignment for next item */
      MemReq = XCP_4BYTE_ALIGN(MemReq);

    } /* end of loop through DAQs */

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
    return MemReq;
}


/**
****************************************************************************************************
This function checks the memory consumption of the daq config. If it fits into the reserved
memory, it will give a positive return value.
\param[in]  AddDaqList    number of DaqList to add for memory calculation
\param[in]  AddOdt        number of Odt to add for memory calculation
\param[in]  AddOdtEntry   number of OdtEntry to add for memory calculation
\param[in]  protLayerId   Protocol Layer Id
\return     TRUE: memory is sufficient
***************************************************************************************************/
boolean Xcp_DaqRamCheck(uint16 AddDaqList, uint8 AddOdt, uint8 AddOdtEntry, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  boolean retval;

  /* initialization */
  retval = FALSE;

  if (Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32 >= Xcp_DaqRamCalc(AddDaqList, AddOdt, AddOdtEntry, protLayerId))
  {
    retval = TRUE;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return retval;
}
#endif

#if (XCP_CALIBRATION_CAL == STD_ON || XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)

/**
****************************************************************************************************
Function checks the write destination lies within xcp boundaries or not
\param[in]  Address   destination pointer
\param[in]  Length    length of the data to check write access
\return     ErrorCode
\retval     XCP_NO_ERROR            Reading successful
\retval     XCP_ERR_ACCESS_DENIED   Source or destination is in restricted memory area
\retval     XCP_ERR_PAGE_NOT_VALID  Calibration page is not valid
***************************************************************************************************/
Xcp_ErrorCode Xcp_MemWriteProtectionCheck(Xcp_AdrPtrConst Address, uint8 Length)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  Xcp_ErrorCode Error;
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  uint8_least i;
#endif

  /* initialization */
  Error = XCP_NO_ERROR;

  /* If address lies with in static xcp memory return Access denied error */
  /* MR12 RULE 18.3 VIOLATION: The pointer cast is required to be able to compare the addresses of the pointers - no problem when casting to uint8* and then comparing */
  if ( (((Address + Length) > (Xcp_AdrPtr)&Xcp_NoInit[0])    && (Address < ((Xcp_AdrPtr)&Xcp_NoInit[0]      + (sizeof(Xcp_NoInit_t) * XCP_PL_IDS))))
    /* MR12 RULE 18.3 VIOLATION: The pointer cast is required to be able to compare the addresses of the pointers - no problem when casting to uint8* and then comparing */
    || (((Address + Length) > (Xcp_AdrPtr)&Xcp_GlobalNoInit) && (Address < ((Xcp_AdrPtr)&Xcp_GlobalNoInit   + (sizeof(Xcp_GlobalNoInit_t)))))
    /* MR12 RULE 18.3 VIOLATION: The pointer cast is required to be able to compare the addresses of the pointers - no problem when casting to uint8* and then comparing */
    || (((Address + Length) > (Xcp_AdrPtr)&Xcp_Cleared[0])   && (Address < ((Xcp_AdrPtr)&Xcp_Cleared[0]     + (sizeof(Xcp_Cleared_t) * XCP_PL_IDS))))
    )
  {
    Error = XCP_ERR_ACCESS_DENIED;
  }
  else
  {
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
    for (i = 0; i < XCP_PL_IDS; i++)
    {
      /* check if address lies within the dynamic memory of any protocol layer */
      if ( ((Address + Length) > (Xcp_AdrPtr)Xcp_NoInit[i].DaqConfig.DaqRamPtr_pu8)
        && (Address < ((Xcp_AdrPtr)Xcp_NoInit[i].DaqConfig.DaqRamPtr_pu8 + Xcp_NoInit[i].DaqConfig.DaqRamSize_u32)) )
      {
        Error = XCP_ERR_ACCESS_DENIED;
        break;
      }
    }
#endif
  }

#if(XCP_MEMORY_WRITE_PROTECTION == STD_ON)
  if (Error == XCP_NO_ERROR)
  {
    Error = XcpAppl_MemWriteProtection(Address, Length);
  }
#endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return(Error);
}
#endif


/**
****************************************************************************************************
Function checks the read destination lies within protect area or not, if it lies within GetID
boundaries then avoid read protect.
\param[in]  Address       destination pointer
\param[in]  Length        length of the data to check read access
\param[in]  protLayerId   Protocol Layer Id
\return     ErrorCode
\retval     XCP_NO_ERROR            Reading successful
\retval     XCP_ERR_ACCESS_DENIED   Source or destination is in restricted memory area
\retval     XCP_ERR_PAGE_NOT_VALID  Calibration page is not valid
***************************************************************************************************/
Xcp_ErrorCode Xcp_MemReadProtectionCheck(Xcp_AdrPtrConst Address, uint8 Length, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  Xcp_ErrorCode Error;

#if (XCP_MEMORY_READ_PROTECTION == STD_ON)
  #if (XCP_CMD_GET_ID_AVAILABLE == STD_ON)
  /* If address lies in Xcp GET_ID boundaries then no error */
  if ( ((Xcp_NoInit[protLayerId].GetId.GetIdLen_u32 != 0u)
    && ((Address) >= Xcp_NoInit[protLayerId].GetId.GetIdPtr))
    && ((Address + Length) <= (Xcp_NoInit[protLayerId].GetId.GetIdPtr + Xcp_NoInit[protLayerId].GetId.GetIdLen_u32)) )
  {
    Error = XCP_NO_ERROR;
  }
  else
  #endif /*(XCP_CMD_GET_ID_AVAILABLE == STD_ON)*/
  {
    Error = XcpAppl_MemReadProtection(Address, Length);
    XCP_PARAM_UNUSED(protLayerId);
  }
#else
  Error = XCP_NO_ERROR;
  XCP_PARAM_UNUSED(Address);
  XCP_PARAM_UNUSED(Length);
  XCP_PARAM_UNUSED(protLayerId);
#endif /*(XCP_MEMORY_READ_PROTECTION == STD_ON)*/

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return(Error);
}


#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"




