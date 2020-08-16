

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"

/***************************************************************************************************
* Macros
***************************************************************************************************/

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)

/***************************************************************************************************
* Variables
***************************************************************************************************/

/* ------------------------------------------------------------------------ */
/* Begin section for code */
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#if (XCP_DAQRAM_SHIFTING == STD_ON)
static void Xcp_DaqRamReturn(void);
#endif
static uint8 Xcp_DaqRamFindRamSection(boolean EdRamRequested, uint8 protLayerId);

/***************************************************************************************************
* Functions
***************************************************************************************************/

/**
****************************************************************************************************
This function allocates daq ram memory for a protocol layer, when a free daq command is received
\param[in]  protLayerId   Protocol Layer Id
\return     Xcp_ErrorCode
\retval     XCP_NO_ERROR              required memory is allocated \n
\retval     XCP_ERR_MEMORY_OVERFLOW   required memory not available \n
\retval     XCP_ERR_CMD_BUSY          another protocol layer is in daq config phase, no allocation possible
***************************************************************************************************/
Xcp_ErrorCode Xcp_DaqRamSetRam(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  uint8 NumRamSection;
  Xcp_ErrorCode Error;
  boolean EdRamRequested;

  /* initialization */
  EdRamRequested = FALSE;
  NumRamSection = 0xFFu;

  SchM_Enter_Xcp_DaqRam();

#if (XCP_DAQRAM_SHIFTING == STD_ON)
  /* make sure, no other protocol layer is in DAQ config now */
  if (  (Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 == protLayerId)
     || (Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 == XCP_INVALID_PROTLAYER_ID)
     )
  {
    Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 = protLayerId;
    Error = XCP_NO_ERROR;
  }
  else
  {
    /* other protocol layer is configuring at this moment */
    Error = XCP_ERR_CMD_BUSY;
  }

  /* if no other protocol layer is configuring now */
  if (Error == XCP_NO_ERROR)
#endif /* (XCP_DAQRAM_SHIFTING == STD_ON) */
  {
    /* assume error case */
    Error = XCP_ERR_MEMORY_OVERFLOW;

#if (XCP_DAQRAM_SHIFTING == STD_ON)
    /* find biggest ram section */
    NumRamSection = Xcp_DaqRamFindRamSection(EdRamRequested, protLayerId);
    if (NumRamSection < XCP_MAX_DAQRAMSECTIONS)
    {
      /* reserve all memory for this protocol layer */
      Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32 = Xcp_GlobalNoInit.DaqRamSections[NumRamSection].DaqRamFreeSize_u32;
      Error = XCP_NO_ERROR;
    }
#else /* (XCP_DAQRAM_SHIFTING == STD_ON) */

#  if (XCP_EDRAM_CONFIGURED == STD_ON)
    /* if TL has ED_RAM configured, it is assumed, XCP master wants ED RAM memory */
    if (Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].EdRam_u32 > 0u)
    {
      EdRamRequested = TRUE;
      NumRamSection = Xcp_DaqRamFindRamSection(EdRamRequested, protLayerId);
    }
#  endif /* (XCP_EDRAM_CONFIGURED == STD_ON) */

    /* if no section has been found yet, look for PD RAM */
    if ( (NumRamSection >= XCP_MAX_DAQRAMSECTIONS)
      && (Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].PdRam_u32 > 0u)
       )
    {
      EdRamRequested = FALSE;
      NumRamSection = Xcp_DaqRamFindRamSection(EdRamRequested, protLayerId);
    }

    /* if ram section found */
    if (NumRamSection < XCP_MAX_DAQRAMSECTIONS)
    {
      /* valid ram section found, reset error */
      Error = XCP_NO_ERROR;
#  if (XCP_EDRAM_CONFIGURED == STD_ON)
      if(EdRamRequested == TRUE)
      {
        /* use ED ram size */
        Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32 = Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].EdRam_u32;
      }
      else
#  endif /* (XCP_EDRAM_CONFIGURED == STD_ON) */
      {
        /* use PD ram size */
        Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32 = Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].PdRam_u32;
      }
    }
#endif /* (XCP_DAQRAM_SHIFTING == STD_ON) */

  }

  /* if ram section found */
  if (Error == XCP_NO_ERROR)
  {

    /* calculate remaining memory */
    Xcp_GlobalNoInit.DaqRamSections[NumRamSection].DaqRamFreeSize_u32 = Xcp_GlobalNoInit.DaqRamSections[NumRamSection].DaqRamFreeSize_u32 - Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32;

    /* check whether other protocol layer is in this section */
#if (XCP_PL_IDS == 2)
    if (Xcp_GlobalNoInit.DaqRamSections[NumRamSection].PLConnected_ab[( (protLayerId + 1) % 2 )] == FALSE)
    {
      /* set pointer to beginning of RAM */
      Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 = Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8;
    }
    else /* already another protocol layer connected */
    {
#  if (XCP_DAQRAM_SHIFTING == STD_ON)
      /* is this found protocol layer beginning at the beginning of free ram ?*/
      if (Xcp_NoInit[(protLayerId + 1) % 2].DaqConfig.DaqRamPtr_pu8 == Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8)
      {
        /* set the beginning of the new protocol layer at the end of the last */
        Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 = &(Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8[Xcp_NoInit[( (protLayerId + 1) % 2 )].DaqConfig.DaqRamSize_u32]);
      }
      else
      {
        /* set pointer to beginning of RAM, other protocol layer is at the end */
        Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 = Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8;
      }
#  else /* -> XCP_DAQRAM_SHIFTING is disabled */
      uint32 pos;

      /* set the beginning of this protocol layer to the end minus requested size. This is only possible, if ensured, that the 2 biggest transport layer requirements fit into one RAM section */
      pos = Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamTotalSize_u32 - Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32;
      Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 = &(Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8[pos]);
#  endif /*  (XCP_DAQRAM_SHIFTING == STD_ON) */
    }
#else /* (XCP_PL_IDS == 2) */
    /* set pointer to beginning of RAM, no other PL is configured */
    Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 = Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8;
#endif /* (XCP_PL_IDS == 2) */

    /* mark this ram section to have this protocol layer */
    Xcp_GlobalNoInit.DaqRamSections[NumRamSection].PLConnected_ab[protLayerId] = TRUE;
    /* Set DaqList array start pointer */
    /* MR12 RULE 11.5, 1.1 VIOLATION: 4-Byte-Alignment is ensured by other functions.
                                      Casting over void* is necessary as otherwise some compilers complain */
    Xcp_NoInit[protLayerId].DaqConfig.DaqList_p = (Xcp_DaqList_t*) ((void*)Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8);

    if (Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 == NULL_PTR)
    {
      XCP_DET_REPORT_ERROR_NO_RET(XCP_DAQRAM_SID, XCP_E_DAQRAM_ALLOCATION);
    }
  }
  SchM_Exit_Xcp_DaqRam();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return Error;
}


/**
****************************************************************************************************
This function searches for a daq ram memory section
\param[in]  EdRamRequested  TRUE: ED memory section is requested
\param[in]  protLayerId     Protocol Layer Id
\return     Number of the RAM section
\retval     0xFF no valid section found
***************************************************************************************************/
static uint8 Xcp_DaqRamFindRamSection(boolean EdRamRequested, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  uint8 NumRamSection;
  uint8 i;

  /* initialization */
  NumRamSection = 0xFFu;
#if (XCP_DAQRAM_SHIFTING == STD_ON)
  {
    /* local variables */
    uint32 biggest_size;

    /* initialization */
    biggest_size = 0;

    XCP_PARAM_UNUSED(EdRamRequested);
    XCP_PARAM_UNUSED(protLayerId);
    /* find biggest section in memory */
    for (i = 0; i < XCP_MAX_DAQRAMSECTIONS; i++)
    {
      if (Xcp_GlobalNoInit.DaqRamSections[i].DaqRamFreeSize_u32 > biggest_size)
      {
        /* found a bigger section */
        biggest_size = Xcp_GlobalNoInit.DaqRamSections[i].DaqRamFreeSize_u32;
        NumRamSection = i;
      }
    } /* end of for loop */
  }
#else /* (XCP_DAQRAM_SHIFTING == STD_ON) */
  /* loop through all available ram sections */
  for (i = 0; i < XCP_MAX_DAQRAMSECTIONS; i++)
  {
    /* find section with enough space */
    if ( (   (EdRamRequested == FALSE)
          && (Xcp_PlCfgConst.DaqRamCfg[i].RamSectionType_en == XCP_RAMSECTION_PD)
          && (Xcp_GlobalNoInit.DaqRamSections[i].DaqRamFreeSize_u32 >= Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].PdRam_u32)
         )
#  if (XCP_EDRAM_CONFIGURED == STD_ON)
     ||  (    (EdRamRequested == TRUE)
          && (Xcp_PlCfgConst.DaqRamCfg[i].RamSectionType_en == XCP_RAMSECTION_ED)
          && (Xcp_GlobalNoInit.DaqRamSections[i].DaqRamFreeSize_u32 >= Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].EdRam_u32)
         )
#  endif
       )
    {
      /* section found */
      NumRamSection = i;
      break;
    }
  } /* end of for loop */
#endif /* (XCP_DAQRAM_SHIFTING == STD_ON) */

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return NumRamSection;
}


/**
****************************************************************************************************
This function frees the protocol layer's allocated daq ram memory
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DaqRamRemove(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  uint8_least NumRamSection;

  /* search for ram section of protocol layer */
  for (NumRamSection = 0; NumRamSection < XCP_MAX_DAQRAMSECTIONS; NumRamSection++)
  {
    if (Xcp_GlobalNoInit.DaqRamSections[NumRamSection].PLConnected_ab[protLayerId] == TRUE)
    {
      /* ram section found */
      break;
    }
  }

  /* ensure ram section exists */
  if (NumRamSection < XCP_MAX_DAQRAMSECTIONS)
  {
    SchM_Enter_Xcp_DaqRam();
#if (XCP_DAQRAM_SHIFTING == STD_ON)

    if (Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 == protLayerId)
    {
      Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 = XCP_INVALID_PROTLAYER_ID;
    }
#endif
    /* is this protocol layer still marked active in this section */
    if ( Xcp_GlobalNoInit.DaqRamSections[NumRamSection].PLConnected_ab[protLayerId] == TRUE )
    {
      /* Free section memory */
      Xcp_GlobalNoInit.DaqRamSections[NumRamSection].DaqRamFreeSize_u32 = Xcp_GlobalNoInit.DaqRamSections[NumRamSection].DaqRamFreeSize_u32 + Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32;
      /* reset protocol layer */
      Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 = NULL_PTR;
      Xcp_NoInit[protLayerId].DaqConfig.DaqList_p = NULL_PTR;
      Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32 = 0;
      /* delete connection marker from section */
      Xcp_GlobalNoInit.DaqRamSections[NumRamSection].PLConnected_ab[protLayerId] = FALSE;
    }
    else
    {
      XCP_DET_REPORT_ERROR_NO_RET(XCP_DAQRAM_SID, XCP_E_DAQRAM_INCONSISTENCY);
    }

    SchM_Exit_Xcp_DaqRam();
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#if (XCP_DAQRAM_SHIFTING == STD_ON)
/**
****************************************************************************************************
This trigger function decides, whether a protocol layer's daq ram has to be shifted.
\param[in]  XcpPacket     pointer to Xcp Cmd Packet copied for later response
\param[in]  protLayerId   Protocol Layer Id
\return     TRUE: daq ram will be shifted
***************************************************************************************************/
boolean Xcp_DaqRamTriggerMovePL(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  uint32  PLsize;
  uint32  FreedSize;
  uint8_least  NumRamSection;
  boolean shifting;


  PLsize = Xcp_DaqRamCalc(0, 0, 0, protLayerId);
  /* FreedSize unsigned, because dynamic RAM must be greater or same size as PL, otherwise ERR_MEM_OVERFLOW during DAQ configuration */
  FreedSize = Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32 - PLsize;

  for (NumRamSection = 0; NumRamSection < XCP_MAX_DAQRAMSECTIONS; NumRamSection++)
  {
    if (Xcp_GlobalNoInit.DaqRamSections[NumRamSection].PLConnected_ab[protLayerId] == TRUE)
    {
      /* ram section found */
      break;
    }
  }

  XCP_DET_REPORT_ERROR_RET((NumRamSection >= XCP_MAX_DAQRAMSECTIONS), XCP_DAQRAM_SID, XCP_E_DAQRAM_INCONSISTENCY, FALSE);

  XCP_DET_REPORT_ERROR_RET((Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 != protLayerId), XCP_DAQRAM_SID, XCP_E_DAQRAM_INCONSISTENCY, FALSE);
  SchM_Enter_Xcp_DaqRam();

  /* only one shifting is allowed at a time, shall be ensured by setting the PlInDaqConfig to this PL */
  if(   (Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8 != Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8)
     && (FreedSize != 0u)
    )
  {
    shifting = TRUE;

    /* store the length of Cmd Packet */
    Xcp_GlobalNoInit.DaqRamMove.XcpPacket.Length_u32 = XcpPacket->SduLength;
    /* Copy the command packet to trigger response later */
    /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemCopy() are declared as (void*) for generic implementation of MemCopy. */
    Xcp_MemCopy(Xcp_GlobalNoInit.DaqRamMove.XcpPacket.Buffer_au8, XcpPacket->SduDataPtr, XCP_MIN(XcpPacket->SduLength, 8u));
    /* store necessary data for the move routine */
    /* MR12 RULE 11.5, 1.1 VIOLATION: 4-Byte-Alignment is ensured for DaqRamPtr_pu8.
                                      Casting over void* is necessary as otherwise some compilers complain */
    Xcp_GlobalNoInit.DaqRamMove.source_pu32 = (uint32*) ((void*) Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8);
    /* MR12 RULE 11.5, 1.1 VIOLATION: 4-Byte-Alignment is ensured by other functions.
                                      Casting over void* is necessary as otherwise some compilers complain */
    Xcp_GlobalNoInit.DaqRamMove.destination_pu32 = (uint32*) ((void*)&(Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamPtr_pu8[Xcp_PlCfgConst.DaqRamCfg[NumRamSection].DaqRamTotalSize_u32 - PLsize]));
    Xcp_GlobalNoInit.DaqRamMove.totalSize_u32 = PLsize;
    /* prio list and queue memory does not need to be moved, prio list is not 4 byte aligned */
    /* MR12 RULE 11.4 VIOLATION: moveSize is determined of the two pointers - as addresses are uint32 the cast is OK */
    Xcp_GlobalNoInit.DaqRamMove.moveSize_u32 = XCP_4BYTE_ALIGN((uint32) Xcp_NoInit[protLayerId].DaqConfig.PriorityList_p) - (uint32) Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8;

    /* remaining size must be set at last, this is trigger for MainFunction */
    Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32 = Xcp_GlobalNoInit.DaqRamMove.moveSize_u32;
  }
  else
  {
    /* no shift required */
    shifting = FALSE;
    /* daq config complete. enable other protocol layers to start daq configuration */
    Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 = XCP_INVALID_PROTLAYER_ID;
  }

  /* shrink the protocol layer to the smallest size, can only be done under lock */
  Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32 = PLsize;
  Xcp_GlobalNoInit.DaqRamSections[NumRamSection].DaqRamFreeSize_u32 = Xcp_GlobalNoInit.DaqRamSections[NumRamSection].DaqRamFreeSize_u32 + FreedSize;
  SchM_Exit_Xcp_DaqRam();

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return shifting;
}

/**
****************************************************************************************************
This function shifts the daq memory piece by piece (slices). It determines the protocol layer to \n
shift by the global structure Xcp_GlobalNoInit.DaqRamMove
\param[in]  -
\return     -
***************************************************************************************************/
void Xcp_DaqRamMainMovePL(void)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* checking the trigger */
  if (Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32 > 0u)
  {
    /* local variables */
    uint32 slice_size;
    uint32 slice_pos;
    uint32 i;

    XCP_DET_REPORT_ERROR( (Xcp_GlobalNoInit.DaqRamMove.destination_pu32 <= Xcp_GlobalNoInit.DaqRamMove.source_pu32), XCP_DAQRAM_SID, XCP_E_DAQRAM_SHIFTING );

    slice_size = Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32;

    /* reduce size to be shifted this call to the configured max */
    if(slice_size > XCP_DAQRAM_MAX_SHIFT_SIZE)
    {
      slice_size = XCP_DAQRAM_MAX_SHIFT_SIZE;
    }

    /* DaqRam is shifted forward.
     * This means the whole memory area is moved to a higher address.
     *
     * The moving is started at the end of the memory area and then continues until it reaches the start of the area.
     * It is important to do it this way as it is not known if the two areas are distinct.
     * If they overlap and the move is started at the beginning of the area, the move would overwrite data.
     *
     * Moving areas backward is currently not supported, as there is no usecase for it.
     * Hint: In this case, the movement has to begin at the start of the area - otherwise it is again possible to overwrite data
     */
    /* start shifting with the last bytes */
    slice_pos = (Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32)/4u;

    for (i = 1; i <= (slice_size/4u); i++)
    { /* move 4 byte wise */
      Xcp_GlobalNoInit.DaqRamMove.destination_pu32[slice_pos - i] = Xcp_GlobalNoInit.DaqRamMove.source_pu32[slice_pos - i];
    }

    /* adjust bytes to be moved */
    Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32 = Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32 - slice_size;

    if (Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32 == 0u)
    {
      /* moving finished */
      Xcp_DaqRamReturn();
    }
    else if(Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 != XCP_INVALID_PROTLAYER_ID)
    {
      /* send EV_CMD_PENDING event */
      Xcp_SendEv_Code(XCP_EV_CMD_PENDING, Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8);
    }
    else
    {
       /* do nothing, only to remove misra warning */
    }

  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

/**
****************************************************************************************************
This function cancels the daq ram shifting, leaving an invalid daq config
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_DaqRamResetShift(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  if ( (Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 == protLayerId)
     &&
       (  (Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32 > 0u)
       || (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_SHIFTING)
       )
     )
  {
  Xcp_GlobalNoInit.DaqRamMove.remainingSize_u32 = 0;
  Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_NO_DAQ;
  Xcp_DaqRamRemove(protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/***************************************************************************************************
* Local functions
***************************************************************************************************/

/**
****************************************************************************************************
This function triggers another StartStopDaqList command to create a response after the daq
shifting is completely finished
\param[in]  -
\return     -
***************************************************************************************************/
static void Xcp_DaqRamReturn(void)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* local variables */
  PduInfoType XcpPacket;
  uint8 protLayerId;

  /* initialization */
  protLayerId = Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8;

  /* move protocol layer pointer */
  Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 = (uint8*) Xcp_GlobalNoInit.DaqRamMove.destination_pu32;

  /* calling Xcp_DaqRamCalc to reset daq, odt and odtentry pointers, return value not needed */
  (void)Xcp_DaqRamCalc(0, 0, 0, protLayerId);

  /* prepare command packet to stimulate response */
  XcpPacket.SduDataPtr = Xcp_GlobalNoInit.DaqRamMove.XcpPacket.Buffer_au8;
  XcpPacket.SduLength  = Xcp_GlobalNoInit.DaqRamMove.XcpPacket.Length_u32;
  Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_PREPARE_START;

  /* Trigger command again, now shifting is finished */
  Xcp_ReceiveCommand(&XcpPacket, protLayerId);

  /* daq config shifting complete. enable other protocol layers to start daq configuration */
  Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 = XCP_INVALID_PROTLAYER_ID;

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

#endif

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#endif


