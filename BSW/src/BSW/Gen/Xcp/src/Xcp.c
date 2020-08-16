

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/

#define XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
Xcp_NoInit_t         Xcp_NoInit[XCP_PL_IDS];
Xcp_GlobalNoInit_t   Xcp_GlobalNoInit;
#define XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
Xcp_Cleared_t        Xcp_Cleared[XCP_PL_IDS];
#define XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static void Xcp_Background_Tasks(uint8 ProtocolLayerId);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
Scheduled function of the XCP module
\param[in]  -
\return     -
***************************************************************************************************/
/* HIS METRIC CALLS VIOLATION IN Xcp_MainFunction: Long and short SchM locks are still needed. It is planned combine the calls -> metric no longer violated */
void Xcp_MainFunction(void)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint8 ProtocolLayerId;
  uint8 TransportLayerId;
  boolean connected;

  /* initilization */
  connected = FALSE;

  /* Do for all protocol layers */
  for (ProtocolLayerId = 0; ProtocolLayerId < XCP_PL_IDS; ProtocolLayerId++)
  {
    if (Xcp_NoInit[ProtocolLayerId].Session.XcpState_en == XCP_STATE_CONNECTED)
    {
      connected = TRUE;

      Xcp_Background_Tasks(ProtocolLayerId);

      /* Retrigger transmit in case previous transmit was E_NOT_OK */
      /* Xcp_RetriggerTransmit(ProtocolLayerId); */
    }

    if (  (Xcp_NoInit[ProtocolLayerId].Session.XcpState_en == XCP_STATE_CONNECTED)
       || (Xcp_NoInit[ProtocolLayerId].Session.XcpState_en == XCP_STATE_DISCONNECTING)
       )
    {
      /* Xcp_TxConfirmation() is expected shortly after call to Xcp_Transmit(). */
      /* If TxConfirmation is lost in lower layer, Wait4TxConfCtr must be reset to prevent endless waiting. */
      SchM_Enter_Xcp_SendingLong();
      SchM_Enter_Xcp_SendingShort();
      if (Xcp_Cleared[ProtocolLayerId].Wait4TxConfCtr_u8 > 0)
      {
        Xcp_Cleared[ProtocolLayerId].Wait4TxConfCtr_u8--;
      }
      SchM_Exit_Xcp_SendingShort();
      SchM_Exit_Xcp_SendingLong();
    }

    /* Disconnect the transport layers with active disconnect request. */
    if (Xcp_NoInit[ProtocolLayerId].Session.XcpState_en == XCP_STATE_DISCONNECTING)
    {
      /* If the response buffer empty or due to a lost TxConfirmation from the lower layer the XCP_WAIT4TXCONFCTR was waited */
      /* the Disconnect can be performed. */
      if ((XCP_RES_BUFFER_LENGTH(ProtocolLayerId) == 0u) || (Xcp_Cleared[ProtocolLayerId].Wait4TxConfCtr_u8 == 0u))
      {
        /* Call TL disconnect function. */
        TransportLayerId = XCP_ACTIVE_TL_ID(ProtocolLayerId);
        if (TransportLayerId < XCP_TL_IDS)
        {
          if (Xcp_PlCfgConst.TlCfg[TransportLayerId].TLDisconnect_pfct(TransportLayerId) == E_OK)
          {
  #if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
            /* remove protocol layer from ram section */
            Xcp_InitDaqConfig(ProtocolLayerId);
  #endif
            /* reset connection TL -> PL in exactly the same order as below */
            /* First the TL from PL, then set invalid TL Id, then XCP state to DISCONNECT or DISABLED. */
            Xcp_GlobalNoInit.Tl2PlRef_au8[TransportLayerId] = XCP_INVALID_PROTLAYER_ID;
            XCP_ACTIVE_TL_ID(ProtocolLayerId) = 0xFF;
            if (Xcp_GlobalNoInit.EnabledResources_u8 == 0u)
            {
              /* A Xcp_SetControlMode request was received and resources are 0 so the XCP state must be DISABLED */
              Xcp_NoInit[ProtocolLayerId].Session.XcpState_en = XCP_STATE_DISABLED;
            }
            else
            {
              Xcp_NoInit[ProtocolLayerId].Session.XcpState_en = XCP_STATE_DISCONNECTED; 
            }
          }
        }
        else /* not a valid TL ID */
        {
  #if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
          /* remove protocol layer from ram section */
          Xcp_InitDaqConfig(ProtocolLayerId);
  #endif
          /* Set XcpState_en to DISCONNECTED to avoid cyclic call of the TL disconnect functions. */
          /* The disconnect order has to be always: first set the invalid TL Id then the state DISCONNECT or DISABLED */
          XCP_ACTIVE_TL_ID(ProtocolLayerId) = 0xFF;
          if (Xcp_GlobalNoInit.EnabledResources_u8 == 0u)
          {
            /* A Xcp_SetControlMode request was received and resources are 0 so the XCP state must be DISABLED */
            Xcp_NoInit[ProtocolLayerId].Session.XcpState_en = XCP_STATE_DISABLED;
          }
          else
          {
            Xcp_NoInit[ProtocolLayerId].Session.XcpState_en = XCP_STATE_DISCONNECTED; 
          }
        }
      }
    }
  }

#if (XCP_RESUME_MODE == STD_ON)
  Xcp_ResumeModeStorage();
#endif
  /* execute only, if at least one protocol layer is connected */
  if (connected == TRUE)
  {
#if( (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_DAQRAM_SHIFTING == STD_ON) )
    /* call function for moving of protocol layer */
    Xcp_DaqRamMainMovePL();
#endif
#if ((XCP_ON_CAN_ENABLED == STD_ON)&&(XCP_CAN_TL_TRANSMIT_BUFFER == STD_ON))
    /* Main function for XcpOnCan buffered transmission */
    Xcp_CanMainFunction();
#endif
#if (XCP_TIMESTAMP == STD_ON)
    /* call timestamp periodically to prevent time jumps if used timestamp counter wraps around */
    (void)XcpAppl_GetTimestamp();
#endif
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
Function that handles the background activities for one PL
\param[in]  ProtocolLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_Background_Tasks(uint8 ProtocolLayerId)
{
  switch (Xcp_Cleared[ProtocolLayerId].BgActivityState)
  {
#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
 || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)) )
    case XCP_BG_CANCEL_REQ:
    { /* SYNCH-Command received - every background activity must be canceled */
      Xcp_CmdSynch_Cancel(ProtocolLayerId);
    }
    break;
#endif

#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
    case XCP_BG_CHKSUM:
    { /* Checksum calculation background process */
      Xcp_BuildChecksumMainFunction(ProtocolLayerId);
    }
    break;
#endif

#if((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON))
    case XCP_BG_MEM_WRITE:
    { /* Download background process */
      Xcp_MemWriteMainFunction(ProtocolLayerId);
    }
    break;
#endif

    case XCP_BG_IDLE:
    {
      /* Nothing to do */
    }
    break;

    default:
    { /* Something weird happened - set State to IDLE */
      Xcp_Cleared[ProtocolLayerId].BgActivityState = XCP_BG_IDLE;
    }
    break;
  }
  /* Send EV_CMD_PENDING if any of the background task is running */
  /* To avoid the sending event during checksum calculation */
#if 0
  if (Xcp_Cleared[ProtocolLayerId].BgActivityState != XCP_BG_IDLE)
  {
      Xcp_SendEv_Code(XCP_EV_CMD_PENDING, ProtocolLayerId);
  }
#endif
}

/**
****************************************************************************************************
Disconnect XCP protocol layer
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_Disconnect(uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Disconnect Protocol layer */
  /* clear response buffer */
  XCP_RES_BUFFER_LENGTH(protLayerId) = 0;
  /* clear event buffer */
  XCP_EV_BUFFER_LENGTH(protLayerId)  = 0;
  /* reset transmission pending flag */
  Xcp_Cleared[protLayerId].TxPending_b = FALSE;
  /* Reset background activities */
  Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_IDLE;
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  /* Stop all DAQ lists */
  Xcp_DaqListStopAll(protLayerId);
# if (XCP_DAQRAM_SHIFTING == STD_ON)
  Xcp_DaqRamResetShift(protLayerId);
# endif
  /* reset daq command sequence */
  Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_NO_DAQ;
#endif
#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
   || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)) )
  /* Call application function to initialize and cancel background request */
  (void)XcpAppl_Init(Xcp_GlobalNoInit.InitStatus_u8, protLayerId);
#endif
  /* Call command initialization functions */
  Xcp_InitUpload(protLayerId);
#if(XCP_CALIBRATION_CAL == STD_ON)
  Xcp_InitDownload(protLayerId);
#endif
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
  Xcp_InitChecksum(protLayerId);
#endif
#if(XCP_SEED_AND_KEY == STD_ON)
  Xcp_InitSeedKey(protLayerId);
#endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

/**
****************************************************************************************************
This function will return the actual status of XCP:
- connected if any protocol layer is connected
- daq state
- stim state
\param[in]  -
\return     Status of Xcp
\retval     XcpState_en
            - XCP_STATE_DISCONNECTED
            - XCP_STATE_CONNECTED
\retval     DaqState_u8
            - 0x01 XCP_STATE_DAQ_HAS_STOPPED: daq transmission has been stopped (changed since last call)
\retval     StimState_u8
            - 0x01 XCP_STATE_DAQ_HAS_STOPPED: stim transmission has been stopped (changed since last call)
            - 0x02 XCP_STATE_ALL_STIM_DATA_RECEIVED: all stim daq lists have a complete data set
\retval     reserved_u8  for future use, no viable output
***************************************************************************************************/
/* HIS METRIC PATH VIOLATION IN Xcp_GetState: Function has to check and set multiple attributes that require separate checks. HIS metric compliance would decrease readability and maintainability. */
Xcp_GetState_t Xcp_GetState(void)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  Xcp_GetState_t retVal;
  uint8_least  protLayerId;


  /* initialization */
  retVal.XcpState_en  = XCP_STATE_DISCONNECTED;
  retVal.DaqState_u8  = 0;
  retVal.StimState_u8 = XCP_STATE_ALL_STIM_DATA_RECEIVED;
  retVal.reserved_u8  = 0;

  /* loop through all protocol layers */
  for (protLayerId = 0; protLayerId < XCP_PL_IDS; protLayerId++)
  {
    if ( (Xcp_NoInit[protLayerId].Session.XcpState_en == XCP_STATE_CONNECTED)
      || (Xcp_NoInit[protLayerId].Session.XcpState_en == XCP_STATE_RESUME)
       )
    {
      /* at least one protocol layer is connected */
      retVal.XcpState_en = Xcp_NoInit[protLayerId].Session.XcpState_en;
      break;
    }
  }

#if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  {
    Xcp_DaqList_t* daqListPtr;
    uint16_least  daqNum;
    uint16 stimCtr;

    stimCtr = 0;

    while ((protLayerId < XCP_PL_IDS) && ((retVal.StimState_u8 & XCP_STATE_ALL_STIM_DATA_RECEIVED) == XCP_STATE_ALL_STIM_DATA_RECEIVED) )
    {
      daqNum = 0;
      /* loop through all daq lists */
      while ( daqNum < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16 )
      {
        daqListPtr = &(Xcp_NoInit[protLayerId].DaqConfig.DaqList_p[daqNum]);

        /* is daq direction STIM */
        if ( (daqListPtr->Mode_u8 & XCP_DAQLISTMODE_DIRECTION_STIM) != 0u)
        {
          /* increment Stim Counter */
          stimCtr++;

          if( (daqListPtr->BufferInfo.Status_u8 & XCP_STATUSBIT_STIM_ERR_NO_DATA_AVAILABLE) == XCP_STATUSBIT_STIM_ERR_NO_DATA_AVAILABLE )
          {
            /* this stim has never received a complete dataset */
            retVal.StimState_u8 = (retVal.StimState_u8 & (uint8)(~XCP_STATE_ALL_STIM_DATA_RECEIVED));
            break /* from daq loop */;
          }
        }
        /* next daq loop */
        daqNum++;
      }
      /* next protocol layer loop */
      protLayerId++;
    }

    if (stimCtr == 0)
    {
      /* reset XCP_STATE_ALL_STIM_DATA_RECEIVED, because no STIM was found */
      retVal.StimState_u8 = 0;
    }
  }
#endif /* XCP_SYNCHRONOUS_DATA_STIMULATION_STIM */

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  /* check whether DAQ transmission changed / stopped */
  if (Xcp_GlobalNoInit.DaqTransmissionStopped_b == TRUE)
  {
    /* reset global flag */
    Xcp_GlobalNoInit.DaqTransmissionStopped_b = FALSE;
    /* set status bits */
    retVal.DaqState_u8 |= XCP_STATE_DAQ_HAS_STOPPED;
  }

# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  /* check whether DAQ transmission changed / stopped */
  if (Xcp_GlobalNoInit.StimTransmissionStopped_b == TRUE)
  {
    /* reset global flag */
    Xcp_GlobalNoInit.StimTransmissionStopped_b = FALSE;
    /* set status bits */
    retVal.StimState_u8 |= XCP_STATE_DAQ_HAS_STOPPED;
  }
# endif
#endif /* XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON */

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
  return retVal;
}

/**
****************************************************************************************************
This service enables or disables XCP resources
\param[in]  Xcp_CtlMode_u8  Control mode to enable or to disable the below resource
                            - Bit 0: calibration/paging activated (1) or not (0) -> \ref XCP_RESOURCE_CALPAG
                            - Bit 1: reserved
                            - Bit 2: DAQ lists activated (1) or not (0)          -> \ref XCP_RESOURCE_DAQ
                            - Bit 3: stimulation activated (1) or not (0)        -> \ref XCP_RESOURCE_STIM
                            - Bit 4: Flash programming activated (1) or not (0)  -> \ref XCP_RESOURCE_PGM
                            - Bit 5: reserved
                            - Bit 6: reserved
                            - Bit 7: reserved
\return     -
***************************************************************************************************/
void Xcp_SetControlMode(uint8 Xcp_CtlMode_u8)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  uint8 ProtocolLayerId;
  uint8 Resources;

  /* filter available resources */
  Resources = Xcp_CtlMode_u8 & XCP_RESOURCE_ENABLED;

  if (Resources == 0)
  {
    /* disconnect all protocol layers */
    for (ProtocolLayerId = 0; ProtocolLayerId < XCP_PL_IDS; ProtocolLayerId++)
    {
      Xcp_Disconnect(ProtocolLayerId);
      if (Xcp_NoInit[ProtocolLayerId].Session.XcpState_en != XCP_STATE_DISCONNECTED)
      {
        /* Set disconnect request to disconnect the transport layer. */
        Xcp_NoInit[ProtocolLayerId].Session.XcpState_en = XCP_STATE_DISCONNECTING;
      }
      else
      {
        /* disable protocol layer */
        Xcp_NoInit[ProtocolLayerId].Session.XcpState_en = XCP_STATE_DISABLED;
      }
    }
  }
  else /* Resources are to  be enabled */
  {
    /* is XCP in state XCP_STATE_DISABLED now ? */
    if (Xcp_GlobalNoInit.EnabledResources_u8 == 0)
    {
      for (ProtocolLayerId = 0; ProtocolLayerId < XCP_PL_IDS; ProtocolLayerId++)
      {
        /* set protocol layers to disconnected */
        Xcp_NoInit[ProtocolLayerId].Session.XcpState_en = XCP_STATE_DISCONNECTED;
      }
    }
  }

  /* Set global ControlMode */
  Xcp_GlobalNoInit.EnabledResources_u8 = Resources;

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}

/**
****************************************************************************************************
This service returns the actual control mode or enabled resource from Xcp
\param[in]  -
\return     Returns enabled resource from Xcp \n
\retval     Control mode to enable or to disable the below resource
            - Bit 0: calibration/paging activated (1) or not (0) -> \ref XCP_RESOURCE_CALPAG
            - Bit 1: reserved
            - Bit 2: DAQ lists activated (1) or not (0)          -> \ref XCP_RESOURCE_DAQ
            - Bit 3: stimulation activated (1) or not (0)        -> \ref XCP_RESOURCE_STIM
            - Bit 4: Flash programming activated (1) or not (0)  -> \ref XCP_RESOURCE_PGM
            - Bit 5: reserved
            - Bit 6: reserved
            - Bit 7: reserved
***************************************************************************************************/
uint8 Xcp_GetControlMode(void)
{
  return(Xcp_GlobalNoInit.EnabledResources_u8);
}

/**
****************************************************************************************************
This service returns the connected transport layer id to a given protocol layer
\param[in]  ProtocolLayerId - Protocol layer Id \n
\return     Connected transport layer id
***************************************************************************************************/
uint8 Xcp_GetConnectedTransportLayerId(uint8 ProtocolLayerId)
{
  return(Xcp_NoInit[ProtocolLayerId].Session.ConnectedTlId_u8);
}

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


