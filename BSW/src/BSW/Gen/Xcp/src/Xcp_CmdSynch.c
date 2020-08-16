

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

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles the synch request and its response processing
\param[in]  XcpPacket     pointer to the received XcpPacket
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_CmdSynch(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* No command parameters to extract */
  XCP_PARAM_UNUSED(XcpPacket);

  /* Call command initialization functions */
  Xcp_InitUpload(protLayerId);
#if (XCP_CALIBRATION_CAL == STD_ON)
  Xcp_InitDownload(protLayerId);
#endif
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
  Xcp_InitChecksum(protLayerId);
#endif
#if ( (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_DAQRAM_SHIFTING == STD_ON))
  Xcp_DaqRamResetShift(protLayerId);
#endif

#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
   || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)))
  Xcp_CmdSynch_Cancel(protLayerId);
#else
  /* Send Synch response */
  Xcp_SendErrRes(XCP_ERR_CMD_SYNCH, protLayerId);
#endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
   || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)))
/**
****************************************************************************************************
This function handles the cancellation of commands after a synch was received
\param[in]  protLayerId   protocol layer id
\return     -
***************************************************************************************************/
void Xcp_CmdSynch_Cancel(uint8 protLayerId)
{
  /* Call application function to initialize and cancel pending request and check if canceled successfully */
  if (XcpAppl_Init(Xcp_GlobalNoInit.InitStatus_u8, protLayerId) == E_OK)
  {
    /* Cancel done - reset background activities */
    Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_IDLE;
    /* Send Synch response */
    Xcp_SendErrRes(XCP_ERR_CMD_SYNCH, protLayerId);
  }
  else
  {
    /* Wait to finish cancellation from Xcp_MainFunction -> set background activity according */
    Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_CANCEL_REQ;
  }
}
#endif

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



