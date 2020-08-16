

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)

#if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
/** Map: OdtOptimizationType to CopyRoutine */
static const uint8 Map_OdtOptimizationType_to_CopyRoutine[] = {
    XCP_ODT_COPY_SAFE,  /* XCP_ODT_OPTIMIZATION_OM_DEFAULT            */
    XCP_ODT_COPY_16,    /* XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_16        */
    XCP_ODT_COPY_32,    /* XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_32        */
    XCP_ODT_COPY_32,    /* XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_64        - not supported */
    XCP_ODT_COPY_SAFE,  /* XCP_ODT_OPTIMIZATION_OM_ODT_TYPE_ALIGNMENT - not supported */
    XCP_ODT_COPY_SAFE,  /* XCP_ODT_OPTIMIZATION_OM_MAX_ENTRY_SIZE     - not supported */
};
#endif


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static void Xcp_DaqListStopDaqList(uint16 daqListNo, uint8 protLayerId);
static Std_ReturnType Xcp_DaqSetOdtLength(uint16 daqListNo_u16, uint8 protLayerId);
#if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
static uint8 Xcp_DaqCalcCopyRoutine(uint32 value);
#endif
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Function prepares the start of DaqList
\param[in]  daqListNo     DAQ to start
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_DaqListStart(uint16 daqListNo, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_DaqList_t*  DaqListPtr;

  /* initialization */
  DaqListPtr = &XCP_DAQ(daqListNo, protLayerId);

  /* allowed to change write pointer without spinlock because DaqList is not started -> EventChannel processing of this DAQ is disabled */
  Xcp_InitDaqQueue(daqListNo, protLayerId);


#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  if ((DaqListPtr->Mode_u8 & XCP_DAQLISTMODE_DIRECTION_STIM) != 0u)
  {
    /* enter lock around buffer access */
    SchM_Enter_Xcp_BufferAccessActiveNoNest();
    /* set status flag for STIM */
    DaqListPtr->BufferInfo.Status_u8 |= XCP_STATUSBIT_STIM_STARTED;
    /* exit lock around buffer access */
    SchM_Exit_Xcp_BufferAccessActiveNoNest();
  }
  else
  {
    /* set status flag for DAQ */
    DaqListPtr->BufferInfo.Status_u8 |= XCP_STATUSBIT_DAQ_STARTED;
  }
#endif

  /* Start DaqList without delay */
  DaqListPtr->CycleCnt_u8 = DaqListPtr->Prescaler_u8;

  /* Set DaqList running flag */
  DaqListPtr->Mode_u8 |= XCP_DAQLISTMODE_RUNNING;

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Function prepares the start of selected DaqList
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_DaqListStartSelected(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint16  daqListNo;
  boolean DaqListStarted;

  /* initialization */
  DaqListStarted = FALSE;

  /* Loop all DaqList */
  for (daqListNo = 0; daqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; daqListNo++)
  {
    /* Start selected and not running DaqList and reset selected flag */
    if ( (XCP_DAQ_MODE(daqListNo, protLayerId) & (XCP_DAQLISTMODE_RUNNING|XCP_DAQLISTMODE_SELECTED)) == XCP_DAQLISTMODE_SELECTED )
    {
      Xcp_DaqListStart(daqListNo, protLayerId);
      XCP_DAQ_MODE(daqListNo, protLayerId) &= (uint8)(~XCP_DAQLISTMODE_SELECTED);
      DaqListStarted = TRUE;
    }
  }

  if (DaqListStarted == TRUE)
  {
    /* Recalculate PriorityList to add started DaqList */
    Xcp_DaqCalculatePriorityList(protLayerId);
    /* Set DAQ-state to running */
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_RUNNING;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This function stops the DaqList
\param[in]  daqListNo     requested DaqList number
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DaqListStop(uint16 daqListNo, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  SchM_Enter_Xcp_BufferAccessActiveNoNest();
  Xcp_DaqListStopDaqList(daqListNo, protLayerId);
  SchM_Exit_Xcp_BufferAccessActiveNoNest();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This function stops selected DaqList
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DaqListStopSelected(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint16 daqListNo;
  boolean DaqListStopped;

  /* initialization */
  DaqListStopped = FALSE;

#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* enter lock to change buffers */
  SchM_Enter_Xcp_BufferAccessActiveNoNest();
#endif

  /* Loop all DaqList */
  for (daqListNo = 0; daqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; daqListNo++)
  {
    /* Stop selected DaqList */
    if ( (XCP_DAQ_MODE(daqListNo, protLayerId) & XCP_DAQLISTMODE_SELECTED) == XCP_DAQLISTMODE_SELECTED )
    {
      Xcp_DaqListStopDaqList(daqListNo, protLayerId);
      DaqListStopped = TRUE;
    }
  }

#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* exit lock around buffer access */
  SchM_Exit_Xcp_BufferAccessActiveNoNest();
#endif

  if (DaqListStopped == TRUE)
  {
    /* Recalculate PriorityList to remove stopped DaqList */
    Xcp_DaqCalculatePriorityList(protLayerId);
    /* Process DAQ running flag */
    Xcp_DaqProcessRunningFlag(protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This function stops all DaqList.
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DaqListStopAll(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint16 daqListNo;

  /* Set DAQ-state from running to ready-to-run */
  Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_READY_TO_RUN;

#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* enter lock to change buffers */
  SchM_Enter_Xcp_BufferAccessActiveNoNest();
#endif

  /* Loop all DaqList */
  for (daqListNo = 0; daqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; daqListNo++)
  {
    Xcp_DaqListStopDaqList(daqListNo, protLayerId);
  }

#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* exit lock around buffer access */
  SchM_Exit_Xcp_BufferAccessActiveNoNest();
#endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This function processes the global DaqList running flag
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DaqProcessRunningFlag(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint16_least  DaqListNo;
  boolean DaqRunning;

  /* initialization */
  DaqRunning = FALSE;

  /* Loop through all DaqList */
  for (DaqListNo = 0; DaqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; DaqListNo++)
  {
    /* If a running DaqList is found return TRUE */
    if ( (XCP_DAQ_MODE(DaqListNo, protLayerId) & XCP_DAQLISTMODE_RUNNING) == XCP_DAQLISTMODE_RUNNING )
    {
      DaqRunning = TRUE;
      break;
    }
  }

  if (DaqRunning == TRUE)
  {
    /* Set DAQ-state to running */
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_RUNNING;
  }
  else
  {
    /* Set DAQ-state from running to ready-to-run */
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_READY_TO_RUN;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This function calculates the priority list.
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DaqCalculatePriorityList(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint16* PriorityList;
  uint16  daqListNo;
  uint16  DaqListSendingCnt;
  uint16_least  i;
  uint16_least  j;
  uint16  daqListNoTemp;


  /* initialization */
  PriorityList = Xcp_NoInit[protLayerId].DaqConfig.PriorityList_p;
  DaqListSendingCnt = 0;

  /* Spin lock around reorganizing PriorityList */
  SchM_Enter_Xcp_SendingLong();
  SchM_Enter_Xcp_SendingShort();

  /* Loop all DaqList */
  for (daqListNo = 0; daqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; daqListNo++)
  {
    /* only running DaqList with direction DAQ */
    if ((XCP_DAQ_MODE(daqListNo, protLayerId) & (XCP_DAQLISTMODE_RUNNING|XCP_DAQLISTMODE_DIRECTION_STIM)) == XCP_DAQLISTMODE_RUNNING)
    {
      PriorityList[DaqListSendingCnt] = daqListNo;
      DaqListSendingCnt++;
    }
  }

  /* save number of sending DaqList globally */
  Xcp_NoInit[protLayerId].DaqConfig.DaqListSendingCnt_u16 = DaqListSendingCnt;

  /* Insertion sort: Sorting by DaqList Priority (high value first)*/
  for (i = 1u; i < DaqListSendingCnt; i++)
  {
    j = i;
    while ( (j > 0u) && (XCP_DAQ_PRIO(PriorityList[j-1u], protLayerId) < XCP_DAQ_PRIO(PriorityList[j], protLayerId)) )
    {
      XCP_SWAP(PriorityList[j-1u], PriorityList[j], daqListNoTemp);
      j--;
    }
  }

  /* Spin lock around reorganizing PriorityList */
  SchM_Exit_Xcp_SendingLong();
  SchM_Exit_Xcp_SendingShort();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Function prepares the start of DaqList
\param[in]  XcpPacket     Xcp Packet Pointer to command
\param[in]  protLayerId   protocol layer id
\return     ErrorCode
\retval     XCP_NO_ERROR           ok to start
\retval     XCP_NO_RESPONSE        DaqRam shifting in progress, don't send response
\retval     XCP_ERR_ACCESS_DENIED  requested address is protected
\retval     XCP_ERR_DAQ_CONFIG     DaqList is not correctly configured
\retval     XCP_ERR_SEQUENCE       SetDaqListMode has not been sent
***************************************************************************************************/
Xcp_ErrorCode Xcp_DaqTriggerStateStartStop(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  Xcp_ErrorCode Error;

  /* initialization */
  Error = XCP_NO_ERROR;

  /* Check for state XCP_DAQ_STATE_PREPARE_START */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_PREPARE_START)
  {
    uint16 DaqList = 0;

    /* check, if all DaqList are completed */
    while ( (Error == XCP_NO_ERROR) && (DaqList < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16) )
    {
      Error = Xcp_DaqListFinalize(DaqList, protLayerId);
      DaqList++;
    }
    if (Error == XCP_NO_ERROR)
    {
#if (XCP_DAQRAM_SHIFTING == STD_ON)
      if (Xcp_DaqRamTriggerMovePL(XcpPacket, protLayerId) == TRUE)
      {
        /* protocol layer now busy moving */
        Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_SHIFTING;
        Error = XCP_NO_RESPONSE;
      }
      else
#else
      XCP_PARAM_UNUSED(XcpPacket);
#endif
      {
        /* set queue pointers */
        (void) Xcp_DaqQueRamCalc(0, TRUE, protLayerId);
        /* Set final DaqState to start DAQ and STIM */
        Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_READY_TO_RUN;
      }
    }
  } /* Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_PREPARE_START */
#if (XCP_DAQRAM_SHIFTING == STD_ON)
  /* Check for state XCP_DAQ_STATE_SHIFTING */
  else if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_SHIFTING)
  {
    /* shifting is active, no further commands possible */
    Error = XCP_ERR_CMD_BUSY;
  }
#endif
  /* Check for not allowed states */
  else if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en < XCP_DAQ_STATE_READY_TO_RUN)
  {
    Error = XCP_ERR_SEQUENCE;
  }
  /* State is XCP_DAQ_STATE_SHIFTING */
  else
  {
    /* Error = XCP_NO_ERROR; already set before */
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return Error;
}


/**
****************************************************************************************************
This function performs various checks for a given address (access protection, OdtEntry NULL/Size)
and calculates needed values for the containing DaqList (e. g. AddressTransformation, OdtOptimization).
\param[inout] Address         Pointer to the Adress that has to be processed
\param[in]    Size            Size of the data Address points to
\param[in]    daqListNo_u16   DaqList number
\param[in]    protLayerId     Protocol Layer Id
\return     Xcp_ErrorCode
\retval     XCP_NO_ERROR            all checks passed successfully
\retval     XCP_ERR_ACCESS_DENIED   requested address is protected
\retval     XCP_ERR_DAQ_CONFIG      DaqList is not correctly configured
***************************************************************************************************/
/* MR12 RULE 8.13 VIOLATION: The pointer Address may be changed if XCP_STATIC_ADDRESS_TRANSFORMATION is enabled - therefore it cannot be const. */
Xcp_ErrorCode Xcp_DaqTransformAndCheckOdtEntry(Xcp_AdrPtr* Address, uint8 Size, uint16 daqListNo_u16, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Initialize variables */
  Error = XCP_NO_ERROR;

#if (XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON)
  /* Do the Address Transformation */
  Error = XcpAppl_StaticAddressTransformation(Address,
                                              Size,
                                              XCP_DAQ(daqListNo_u16, protLayerId).EventChannelNum_u16,
                                              ((XCP_DAQ_MODE(daqListNo_u16, protLayerId) & XCP_DAQLISTMODE_DIRECTION_STIM) == 0u) ? XCP_CONTEXT_DAQ : XCP_CONTEXT_STIM);

  /* Only do the remaining checks if we have successfully done the Address-Transformation
   * otherwise we have to do the checks lateron
   */
  if (Error != XCP_NO_ERROR)
  {
    /* Nothing more to do - there is an error */
  }
  else
#endif
  {
    if ((XCP_DAQ_MODE(daqListNo_u16, protLayerId)  & XCP_DAQLISTMODE_DIRECTION_STIM) == 0u)
    { /* Direction is DAQ */
      /* If Read Protect is detected for the address then set error */
      if(Xcp_MemReadProtectionCheck(*Address, Size, protLayerId) != XCP_NO_ERROR)
      {
        XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) = XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) | XCP_DAQFLAG_READ_PROTECTED;
        Error = XCP_ERR_ACCESS_DENIED;
      }
    }
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
    else
    { /* Direction is STIM */
      /* If Write Protect is detected for the received address then set the Flag */
      if (Xcp_MemWriteProtectionCheck(*Address, Size)!= XCP_NO_ERROR)
      {
        XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) = XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) | XCP_DAQFLAG_WRITE_PROTECTED;
        Error = XCP_ERR_ACCESS_DENIED;
      }
    }
# endif /* (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON) */

# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
    if (Error == XCP_NO_ERROR)
    {
      /* Check if the copy routine for this OdtEntry matches the one for the Odt (Set copy routine for the Odt if first OdtEntry or error) */
      Error = Xcp_DaqSetOdtCopyRoutine(*Address, Size, Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.AbsOdtNum_u16, protLayerId);
    }
# endif
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return Error;
}


/**
****************************************************************************************************
This function performs various checks for a DaqList (access protection, OdtEntry NULL/Size)
and calculates needed values for the DaqList (e. g. AddressTransformation, OdtOptimization).
\param[in]  daqListNo_u16   DaqList number
\param[in]  protLayerId     Protocol Layer Id
\return     Xcp_ErrorCode
\retval     XCP_NO_ERROR            required memory is allocated
\retval     XCP_ERR_SEQUENCE        DaqListMode not received
\retval     XCP_ERR_ACCESS_DENIED   requested address is protected
\retval     XCP_ERR_DAQ_CONFIG      DaqList is not correctly configured
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_DaqListFinalize: Function contains very simple "else if" statements. HIS metric compliance would decrease readability and maintainability. */
Xcp_ErrorCode Xcp_DaqListFinalize(uint16 daqListNo_u16, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_ErrorCode Error;
#if (XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON)
  Xcp_AdrPtr    LocalAddress;
  uint8         LocalSize;
  uint16_least  OdtNo;
  uint16_least  AbsOdtEntryNo;
#endif

  /* Check if DaqList already checked */
  if ((XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) & XCP_DAQFLAG_CONFIG_COMPLETED) != 0u)
  {
    /* DaqList already checked, all other checks can be skipped */
    Error = XCP_NO_ERROR;
  }
  /* Check if SetDaqListMode has been received */
  else if ((XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) & XCP_DAQFLAG_RECEIVED_DAQ_LIST_MODE) == 0u)
  {
    Error = XCP_ERR_SEQUENCE;
  }
#if (XCP_STATIC_ADDRESS_TRANSFORMATION == STD_ON)
  /* Check if Address-Transformation was already done */
  else if ((XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) & XCP_DAQFLAG_ADDR_TRANSFORMATION_DONE) == 0u)
  { /* No, transformation was not yet done */
    Error = XCP_NO_ERROR;
    /* Loop through all the ODTs of this DaqList */
    for (OdtNo = XCP_DAQ_ODTFIRST(daqListNo_u16, protLayerId); (OdtNo < XCP_DAQ_ODTMAX(daqListNo_u16, protLayerId)) && (Error == XCP_NO_ERROR); OdtNo++)
    {
      /* Loop through all OdtEntries of this ODT */
      for (AbsOdtEntryNo = XCP_ODT_ODTENTRYFIRST(OdtNo, protLayerId); (AbsOdtEntryNo < XCP_ODT_ENTRYMAX(OdtNo, protLayerId)) && (Error == XCP_NO_ERROR); AbsOdtEntryNo++)
      {
        /* Get address and Size */
        LocalAddress  = XCP_ODTENTRY_ADR(AbsOdtEntryNo, protLayerId);
        LocalSize     = XCP_ODTENTRY_SIZE(AbsOdtEntryNo, protLayerId);

        Error = Xcp_DaqTransformAndCheckOdtEntry((Xcp_AdrPtr*)&LocalAddress, LocalSize, daqListNo_u16, protLayerId);
        XCP_ODTENTRY_ADR(AbsOdtEntryNo, protLayerId) = LocalAddress;
      }
    }
  }
  else
  {
    /* Nothing more to do */
    Error = XCP_NO_ERROR;
  }

  if (Error != XCP_NO_ERROR)
  {
    /* Nothing to do - error already set */
  }
#endif
#if (XCP_MEMORY_READ_PROTECTION == STD_ON)
  /* Check if read protected */
  else if( ((XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) & XCP_DAQFLAG_READ_PROTECTED) != 0u)
        && ((XCP_DAQ_MODE(daqListNo_u16, protLayerId) & XCP_DAQLISTMODE_DIRECTION_STIM) == 0u)
         )
  {
    Error = XCP_ERR_ACCESS_DENIED;
  }
#endif
#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* Check if write protected */
  else if( ((XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) & XCP_DAQFLAG_WRITE_PROTECTED) != 0u)
        && ((XCP_DAQ_MODE(daqListNo_u16, protLayerId) & XCP_DAQLISTMODE_DIRECTION_STIM) != 0u)
         )
  {
    Error = XCP_ERR_ACCESS_DENIED;
  }
#endif /*(XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)*/
  /* Check for correct OdtLength and wrong OdtEntries */
  else if (Xcp_DaqSetOdtLength(daqListNo_u16, protLayerId) == E_NOT_OK)
  {
    Error = XCP_ERR_DAQ_CONFIG;
  }
  /* All checks passed, DaqList OK */
  else
  {
    /* If all the checks passed the DaqList is completed. */
    XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) = XCP_DAQ_FLAGS(daqListNo_u16, protLayerId) | XCP_DAQFLAG_CONFIG_COMPLETED;
    Error = XCP_NO_ERROR;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return Error;
}


# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
/**
****************************************************************************************************
This function checks whether the copy routine for this ODT is also valid for this OdtEntry.
The copy optimization is set if it is the first OdtEntry of the Odt or an error was detected.
\param[in]  Address       OdtEntry address
\param[in]  Size          OdtEntry size
\param[in]  protLayerId   Protocol Layer Id
\param[in]  AbsOdtNum     Number of the Odt
\return     returns an error code in case that the conditions are not fulfilled
***************************************************************************************************/
Xcp_ErrorCode Xcp_DaqSetOdtCopyRoutine(Xcp_AdrPtrConst Address, uint8 Size, uint16 AbsOdtNum, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_ErrorCode Error;

  uint8 CopyRoutine_Size;          /* Holds the copy routine determined analyzing the size */
  uint8 CopyRoutine_Address;       /* Holds the copy routine determined analyzing the address */
  uint8 CopyRoutine_MaxSupported;  /* Holds the copy routine given by the configuration */
  uint8 CopyRoutine;               /* Holds the copy routine to be used for the given OdtEntry */

  /* Initialize variables */
  Error = XCP_NO_ERROR;

  /* Check if the copy-routine for this Odt is Safe-copy: Nothing more has to be done */
  if (XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId) == XCP_ODT_COPY_SAFE)
  {
    /* Safe copy to be used - nothing to do */
  }
  else
  {
    /* Determine the copy routine to be used according to configuration */
    CopyRoutine_MaxSupported = Map_OdtOptimizationType_to_CopyRoutine[Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].OdtOptimizationType_en];

    /* Check if Optimization for this TL is active */
    if (CopyRoutine_MaxSupported == XCP_ODT_COPY_SAFE)
    { /* XCP_ODT_COPY_SAFE = no optimization -> Use the safe-copy routine */
      XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId) = XCP_ODT_COPY_SAFE;
    }
    else
    { /* Optimization requested */

      /* Check which copy routine can be used according to the size*/
      CopyRoutine_Size = Xcp_DaqCalcCopyRoutine((uint32)Size);

      /* Check which copy routine can be used according to the alignment*/
      /* MR12 RULE 11.4 VIOLATION: Cast from pointer to uint32 is OK as the addresses are 32bit long */
      CopyRoutine_Address = Xcp_DaqCalcCopyRoutine((uint32)Address);

      /* Get the smaller copy routine - as it can also copy larger sizes */
      CopyRoutine = XCP_MIN(CopyRoutine_Size, CopyRoutine_Address);

      /* Limit to the configured max copy routine */
      CopyRoutine = XCP_MIN(CopyRoutine, CopyRoutine_MaxSupported);

      /* Check if the determined copy routine is the same for the Odt */
      if (CopyRoutine != XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId))
      { /* Copy routine mismatch */

        /* Check if there is a copy routine stored for this Odt.
         * This is done within the check whether the routines are equal,
         * as otherwise this check has to be done for each OdtEntry. */
        if (XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId) == XCP_ODT_COPY_UNKNOWN)
        { /* No copy routine -> use the copy routine for this OdtEntry as the one for the Odt */
          XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId) = CopyRoutine;
        }
        else
        { /* Copy routine for Odt was stored and does not match the one for this OdtEntry */

          /* Fallback to safe copy */
          XCP_ODT_COPYROUTINE(AbsOdtNum, protLayerId) = XCP_ODT_COPY_SAFE;

#  if (XCP_OM_ODT_OPTIMIZATION_ERR_REACTION == XCP_OM_ODT_OPTIMIZATION_ERR_FALLBACK_TO_OM_DEFAULT)
          

#  else
          /* Return error */
          Error = XCP_ERR_DAQ_CONFIG;

          

#  endif
        }
      }
      else
      {
        /* Copy routines identical - nothing to do */
      }
    }
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return Error;
}
# endif


/***************************************************************************************************
* Local functions
***************************************************************************************************/


# if (XCP_OM_ODT_OPTIMIZATION_ENABLED == STD_ON)
/**
****************************************************************************************************
This function returns the largest copy function that can be used for the given parameter
\param[in]  value   value for which the copy routine shall be returned
\return     returns the largest possible copy function for the given parameter
***************************************************************************************************/
static uint8 Xcp_DaqCalcCopyRoutine(uint32 value)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint8 CopyRoutine;

  if ((value % 8u) == 0u)
  { /* 64 bit */
    CopyRoutine = XCP_ODT_COPY_64;
  }
  else
  if ((value % 4u) == 0u)
  { /* 32 bit */
    CopyRoutine = XCP_ODT_COPY_32;
  }
  else
  if ((value % 2u) == 0u)
  { /* 16 bit */
    CopyRoutine = XCP_ODT_COPY_16;
  }
  else
  /* if ((value % 1u) == 0u) */
  { /* 8 bit */
    CopyRoutine = XCP_ODT_COPY_8;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return CopyRoutine;
}
# endif


/**
****************************************************************************************************
This function stops the given DAQ-List
\param[in]  daqListNo     requested DaqList number
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_DaqListStopDaqList(uint16 daqListNo, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* enter lock to change buffers */
  /* Reset running flag */
  XCP_DAQ_BUFFERINFO(daqListNo, protLayerId).Status_u8 = XCP_STATUSBIT_STIM_ERR_NO_DATA_AVAILABLE;
  /* exit lock around buffer access */
#endif

  /* Reset DaqList running flag */
  XCP_DAQ_MODE(daqListNo, protLayerId) &= (uint8)(~(XCP_DAQLISTMODE_RUNNING|XCP_DAQLISTMODE_SELECTED));

  /* mark DAQ/STIM configuration to be stopped */
#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  if ((XCP_DAQ_MODE(daqListNo, protLayerId) & XCP_DAQLISTMODE_DIRECTION_STIM) != 0u)
  { /* DAQ-List with direction STIM */
    Xcp_GlobalNoInit.StimTransmissionStopped_b = TRUE;
  }
  else
#endif
  { /* DAQ-List with direction DAQ */
    Xcp_GlobalNoInit.DaqTransmissionStopped_b = TRUE;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This function set Odt length for given DaqList
\param[in]  daqListNo_u16   DaqList number
\param[in]  protLayerId     Protocol Layer Id
\return     was set successful
***************************************************************************************************/
static Std_ReturnType Xcp_DaqSetOdtLength(uint16 daqListNo_u16, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Std_ReturnType RetValue;
  uint32 OdtLength;
  uint16 OdtFirst;
  uint16 OdtMax;
  uint16_least OdtNo;
  uint16_least AbsOdtEntryNo;

  /* Initial values */
  RetValue = E_OK;
  OdtFirst = XCP_DAQ_ODTFIRST(daqListNo_u16, protLayerId);
  OdtMax = XCP_DAQ_ODTMAX(daqListNo_u16, protLayerId);

  /* Loop through all the ODTs of this DaqList */
  for (OdtNo = OdtFirst; OdtNo < OdtMax; OdtNo++)
  {
    /* header size */
#if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
    OdtLength = (uint8) (Xcp_NoInit[protLayerId].Session.IdFieldType_en);  /* DAQ header size */
#else
    OdtLength = (uint8) (XCP_IDENTIFICATION_FIELD_TYPE_ABSOLUTE);  /* DAQ header size absolute = 1 Byte */
#endif
#if (XCP_TIMESTAMP == STD_ON)
    /* If ODT with timestamp, Add number of bytes required for timestamp */
    if ( (OdtNo == OdtFirst)
      && ((XCP_DAQ_MODE(daqListNo_u16, protLayerId) & XCP_DAQLISTMODE_TIMESTAMP) != 0u)
       )
    {
      /* bytes for timestamp according TL config*/
      OdtLength = OdtLength + (uint8) (Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TimestampType_en);
    }
#endif

    /* Loop through all OdtEntries of this ODT */
    for (AbsOdtEntryNo = XCP_ODT_ODTENTRYFIRST(OdtNo, protLayerId); AbsOdtEntryNo < XCP_ODT_ENTRYMAX(OdtNo, protLayerId); AbsOdtEntryNo++)
    {
      if ( (XCP_ODTENTRY_ADR(AbsOdtEntryNo, protLayerId)  == NULL_PTR)
        || (XCP_ODTENTRY_SIZE(AbsOdtEntryNo, protLayerId) == 0)
         )
      {
        /* DaqList is not correctly configured. */
        RetValue = E_NOT_OK;
        OdtLength = 0xFFFFFFFFu;
        break;
      }
      else
      {
        OdtLength += XCP_ODTENTRY_SIZE(AbsOdtEntryNo, protLayerId);
      }
    }

    /* Check if OdtLength <= MaxDto */
    if (OdtLength <= XCP_MAXDTO(protLayerId))
    {
      /* store OdtLength */
      XCP_ODT_LENGTH(OdtNo, protLayerId) = (uint16) OdtLength;
    }
    else
    {
      /* OdtLength too big */
      RetValue = E_NOT_OK;
      break;
    }
  } /* end of loop through ODTs */

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return RetValue;
}


#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#endif


