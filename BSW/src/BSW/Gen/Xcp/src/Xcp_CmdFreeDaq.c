

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
#if (XCP_CMD_FREE_DAQ_AVAILABLE == STD_ON)

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles the connect request and his response processing.
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdFreeDaq(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  XCP_PARAM_UNUSED(XcpPacket);

  /* Stop all DAQ lists */
  Xcp_DaqListStopAll(protLayerId);

  /* Reset the DAQ configuration parameters. */
  Xcp_InitDaqConfig(protLayerId);
  /* DaqState is FREE_DAQ */
  Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_FREE_DAQ;

  /* Send positive response */
  Xcp_SendPosRes(protLayerId);

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
This function initialises the DAQ configuration for the given protocol layer.
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_InitDaqConfig(uint8 protLayerId)
{
  /* DaqState is NO_DAQ */
  Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_NO_DAQ;

  /* remove this protocol layer's ram to start from scratch */
  Xcp_DaqRamRemove(protLayerId);

  /* Do not initialize array start pointers! They are used in Xcp_EventChannel() */

  /* Initialize total counters */
  Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16              = 0;
  Xcp_NoInit[protLayerId].DaqConfig.OdtCnt_u16                  = 0;
  Xcp_NoInit[protLayerId].DaqConfig.OdtEntryCnt_u16             = 0;
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  Xcp_NoInit[protLayerId].DaqConfig.OdtStimCnt_u16              = 0;
# endif

  /* Initialize Daq list pointer for SET_DAQ_PTR */
  Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryPos_u16   = 0;
  Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.OdtEntryMax_u16   = 0;
  Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.AbsOdtNum_u16     = 0;
  Xcp_NoInit[protLayerId].DaqConfig.SelectedOdtEntry.DaqListNum_u16    = 0;

  /* Initialize Daq ram variables */
  Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8               = NULL_PTR;
  Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32              = 0;

  /* Initialize mixed variables */
  Xcp_NoInit[protLayerId].DaqConfig.DaqListSendingCnt_u16       = 0;
  Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16          = 0;
# if (XCP_DAQ_OVERLOAD_INDICATION_PID_ENABLED == STD_ON)
  Xcp_NoInit[protLayerId].DaqConfig.OverloadOccurred_b          = FALSE;
# endif
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdFreeDaq.c: XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ is not enabled - no data is needed in this file*/
#endif



