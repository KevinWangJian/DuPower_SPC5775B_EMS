
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

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This function looks for daq lists in all protocol layers, that are configured for this eventchannel.\n
Depending on the direction of the DAQ, it will call Xcp_DaqEvent or Xcp_StimEvent, collecting the
status bits to return them to the caller
\param[in]  XcpEventChannelNumber_u16   eventchannel number to process
\return     Status of the requested Eventchannel
\retval     status_u8   May contain the following status-bits
                        - 0x01: XCP_STATUSBIT_DAQ_STARTED: set, when DAQ is being processed
                        - 0x02: XCP_STATUSBIT_DAQ_ERR_OVERLOAD: set, when an overload occurs
                        - 0x10: XCP_STATUSBIT_STIM_STARTED: set, when STIM is being processed
                        - 0x20: XCP_STATUSBIT_STIM_ERR_NO_DATA_AVAILABLE: set, when STIM does not have a complete set of data
\retval     numOfReceivedStimdata_u8  counter, how many complete sets of STIM data have been received. \n
                                      lowest counter will be taken, when there are several DAQ lists in this eventchannel
***************************************************************************************************/
/* HIS METRIC LEVEL VIOLATION IN Xcp_EventChannel: Function contains several necessary if statements. HIS metric compliance would decrease readability and maintainability. */
Xcp_EventChannelStatus_t Xcp_EventChannel(uint16 XcpEventChannelNumber_u16)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_DaqList_t* daqListPtr;
#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  Xcp_EventChannelStatus_t StimEventChannelStatus;
#endif
  Xcp_EventChannelStatus_t retStatus;
  uint16 daqListNo;
  uint8  protLayerId;

  /* Initialization */
  retStatus.status_u8 = 0;
  retStatus.reserved_u16 = 0;
  retStatus.numOfReceivedStimdata_u8 = 0xFFu;

  for (protLayerId = 0; protLayerId < XCP_PL_IDS; protLayerId++)
  {
    /* check if global DAQ running */
    if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)
    {

      for (daqListNo = 0; daqListNo < (Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16); daqListNo++)
      {
        daqListPtr = &(XCP_DAQ(daqListNo, protLayerId));
        /** Start of DAQ Runtime measurement **/
        /* check if right DaqList and if DAQ running */
        if ( (daqListPtr->EventChannelNum_u16 == XcpEventChannelNumber_u16)
          && ((daqListPtr->Mode_u8 & XCP_DAQLISTMODE_RUNNING) == XCP_DAQLISTMODE_RUNNING)
           )
        {
          /* found EventChannel for processing */
#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
          if (((daqListPtr->Mode_u8) & XCP_DAQLISTMODE_DIRECTION_STIM) == 0u)
          {
#endif
            /* process Daq event, collect status bits */
            retStatus.status_u8 |= Xcp_DaqEvent(daqListNo, protLayerId);
        /** End of DAQ Runtime measurement **/
#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
          }
          else /* STIM */
          {
            StimEventChannelStatus = Xcp_StimEvent(daqListNo, protLayerId);
            /* collect status bits and call STIM event*/
            retStatus.status_u8 |= StimEventChannelStatus.status_u8;

            /* save the minimum of the received STIM data for returning to caller */
            retStatus.numOfReceivedStimdata_u8 = XCP_MIN(retStatus.numOfReceivedStimdata_u8, StimEventChannelStatus.numOfReceivedStimdata_u8);
          }
#endif
          /* only one Daq per protocol layer and EventChannel */
          break;
        }
      } /* end of for each Daq loop */

    } /*end of if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)*/
  } /* end of for each protocol layer loop */

  if (retStatus.numOfReceivedStimdata_u8 == 0xFFu)
  {
    /* value is unchanged, set to zero */
    retStatus.numOfReceivedStimdata_u8 = 0;
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return retStatus;
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE_EVENTCHANNEL
#include "Xcp_MemMap.h"

#endif


