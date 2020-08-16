

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/


#if (XCP_CMD_SET_DAQ_PTR_AVAILABLE == STD_ON)

/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static boolean Xcp_DaqCheckOdtEntryInAllOdt(uint8 protLayerId);
static void    Xcp_InitDaqOdtEntry(uint8 protLayerId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles DAQ List pointer setting for each ODT.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdSetDaqPtr(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdSetDaqPtr_t* const CmdPtr = (const Xcp_CmdSetDaqPtr_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;
  uint16 AbsOdtNum;

  /* Check if the previous state is correct */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_ALLOC_ODT_ENTRY)
  {
    /* Check if ODT entries are allocated for all ODTs of the defined DAQ lists. */
    if (Xcp_DaqCheckOdtEntryInAllOdt(protLayerId) == TRUE )
    {
      /* Init Odt Entries and set next state */
      Xcp_InitDaqOdtEntry(protLayerId);
      Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_WRITE_DAQ;
    }
  }

  /* Is the DaqList, Odt and OdtEntry available */
  if(  (CmdPtr->DaqListNum_u16 >= Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16)
         || (CmdPtr->OdtNum_u8      >= XCP_DAQ_ODTCNT(CmdPtr->DaqListNum_u16, protLayerId))
         || (CmdPtr->OdtEntryNum_u8 >= XCP_ODT_ODTENTRYCNT(Xcp_Daq_GetAbsOdtNum(CmdPtr->DaqListNum_u16, CmdPtr->OdtNum_u8, protLayerId), protLayerId))
         )
  {
    /* if not available, Prepare error response ERR_OUT_OF_RANGE */
    Error = XCP_ERR_OUT_OF_RANGE;
  }
  /* Is the command sequence correct? This check is placed at latest possible point, because ERR_SEQUENCE is not specified in ASAM. */
  /* Other errors should be sent with higher priority */
  else if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en < XCP_DAQ_STATE_WRITE_DAQ)
  {
    /* Prepare error response ERR_SEQUENCE */
    Error = XCP_ERR_SEQUENCE;
  }
  else
  {
    AbsOdtNum = Xcp_Daq_GetAbsOdtNum(CmdPtr->DaqListNum_u16, CmdPtr->OdtNum_u8, protLayerId);
    /* Set Daq list pointer */
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16 = XCP_ODT_ODTENTRYFIRST(AbsOdtNum, protLayerId) + CmdPtr->OdtEntryNum_u8;
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryMax_u16 = XCP_ODT_ENTRYMAX(AbsOdtNum, protLayerId);
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.AbsOdtNum_u16   = AbsOdtNum;
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.DaqListNum_u16  = CmdPtr->DaqListNum_u16;
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
    /* Error, reset Daq list pointer */
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16 = 0;
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryMax_u16 = 0;
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.AbsOdtNum_u16   = 0;
    Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.DaqListNum_u16  = 0;
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
This service checks if all ODTs have defined ODT entries.
\param[in]  protLayerId   Protocol Layer Id
\retval     TRUE          all ODTs have ODT entries allocated
\retval     FALSE         some ODTs don't have ODT entries allocated
***************************************************************************************************/
static boolean Xcp_DaqCheckOdtEntryInAllOdt(uint8 protLayerId)
{
  /* Local variables */
  uint32 OdtNo;
  boolean retVal ;

  /* Initial values */
  retVal = TRUE ;

  for (OdtNo = 0; OdtNo < Xcp_NoInit[protLayerId].DaqConfig.OdtCnt_u16; OdtNo++)
  {
    /* if ODT Entries are not allocated to at least one ODT then return FALSE */
    if (XCP_ODT_ODTENTRYCNT(OdtNo, protLayerId) == 0)
    {
      retVal = FALSE ;
    }
  }
  return retVal;
}


/**
****************************************************************************************************
This service allocates memory for all defined ODTs.
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_InitDaqOdtEntry(uint8 protLayerId)
{
  /* Init Odt Entries - address and size */
  /* MR12 DIR 1.1 VIOLATION: The input parameters of rba_BswSrv_MemSet() are declared as (void*) for generic implementation of MemSet. */
  Xcp_MemSet(&XCP_ODTENTRY_ADR(0, protLayerId), 0, (Xcp_NoInit[protLayerId].DaqConfig.OdtEntryCnt_u16 * XCP_SIZEOF_ODT_ENTRY));
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdSetDaqPtr.c: The command is not enabled - no code is needed in this file */
#endif



