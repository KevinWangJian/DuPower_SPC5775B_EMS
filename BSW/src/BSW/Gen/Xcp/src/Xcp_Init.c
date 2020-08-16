
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"

#if ((XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON) && (XCP_EDRAM_CONFIGURED == STD_ON))
# include "rba_Memlay.h" /* for ED RAM #define RBA_MEMLAY_EDRAM_START */
# ifdef RBA_MEMLAY_EDRAM_START
#  include "rba_Eec.h"
# endif
#endif


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
LOCAL_INLINE void Xcp_InitRam(void);
#endif


/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service initializes interfaces and variables of the XCP layer
\param[in]  Xcp_ConfigPtr   pointer to the xcp config structure
\return     -
***************************************************************************************************/
void Xcp_Init(const Xcp_ConfigType* Xcp_ConfigPtr)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Local variables */
  uint8 protLayerId;
  uint8 l_transportlayer_u8;

  XCP_PARAM_UNUSED(Xcp_ConfigPtr);

#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  /* check whether sizeof(DAQ), sizeof(ODT) and sizeof(ODTENTRY) match calculation for A2L (see Xcp_CodeFileConstants.ext) */
  XCP_DET_REPORT_ERROR((XCP_SIZEOF_DAQ != XCP_DAQ_SIZE), XCP_INITIALIZE_SID, XCP_E_DAQ_SIZE_MISMATCH);
  XCP_DET_REPORT_ERROR((XCP_SIZEOF_ODT != XCP_ODT_SIZE), XCP_INITIALIZE_SID, XCP_E_ODT_SIZE_MISMATCH);
  XCP_DET_REPORT_ERROR((XCP_SIZEOF_ODT_ENTRY != XCP_ODT_ENTRY_SIZE), XCP_INITIALIZE_SID, XCP_E_ODTENTRY_SIZE_MISMATCH);
#endif

  /* NOINIT section not used (most cases): Initialisation is always done */
  /* NOINIT section used (special cases):  Initialisation is done for first startup */
  if (Xcp_GlobalNoInit.InitStatus_u8 == XCP_UNINIT)
  {
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
    /* initialize ram pointer and size */
    Xcp_InitRam();
# if(XCP_DAQRAM_SHIFTING == STD_ON)
    Xcp_GlobalNoInit.DaqConfigActiveOnPl_u8 = XCP_INVALID_PROTLAYER_ID;
# endif
#endif
    /* Turn on XCP by default, can be disabled at a later time */
    Xcp_GlobalNoInit.EnabledResources_u8 = XCP_RESOURCE_ENABLED;

    /* initialize protocol layers for first connect */
    for (protLayerId = 0; protLayerId < XCP_PL_IDS; protLayerId++)
    {
      /* set TransportId to 0xFF */
      XCP_ACTIVE_TL_ID(protLayerId) = 0xFFu;
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
      Xcp_NoInit[protLayerId].DaqConfig.DaqListSending_u16 = XCP_DAQLIST_UNDEF;
#endif
#if(XCP_SEED_AND_KEY == STD_ON)
      Xcp_InitSeedKey(protLayerId);
#endif
    }
    /* reset all transportlayer -> protocol layer references */
    for (l_transportlayer_u8 = 0; l_transportlayer_u8 < XCP_TL_IDS; l_transportlayer_u8++)
    {
      Xcp_GlobalNoInit.Tl2PlRef_au8[l_transportlayer_u8] = XCP_INVALID_PROTLAYER_ID;
    }
#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
  Xcp_GlobalNoInit.DaqTransmissionStopped_b = TRUE;
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  Xcp_GlobalNoInit.StimTransmissionStopped_b = TRUE;
# endif
#endif
  }

  /* Initializations after every reset */
  /* Init for all protocol layers */
  for (protLayerId = 0; protLayerId < XCP_PL_IDS; protLayerId++)
  {
    /* Clear all available queues */
    Xcp_QueClearAll(protLayerId);
    /* nothing to send, clear Wait4TxConfCtr */
    Xcp_Cleared[protLayerId].Wait4TxConfCtr_u8 = 0;
    /* Set background activities to none */
    Xcp_Cleared[protLayerId].BgActivityState = XCP_BG_IDLE;

    /* Call init functions */
#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
   || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)) )
    /* Call application function to initialize and cancel application background activities */
    (void)XcpAppl_Init(Xcp_GlobalNoInit.InitStatus_u8, protLayerId);
#endif
    Xcp_InitUpload(protLayerId);
#if(XCP_CALIBRATION_CAL == STD_ON)
    Xcp_InitDownload(protLayerId);
#endif
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
    Xcp_InitChecksum(protLayerId);
#endif

#if (XCP_DEV_ERROR_DETECT == STD_ON)
    /* Debug counter reset */
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_TransmitOkCtr = 0;
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_TransmitNotOkCtr = 0;
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendResTxConfCtr = 0;
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendResCtr = 0;
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendEvTxConfCtr = 0;
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendEvCtr = 0;
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_TxConfCtr = 0;
# if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendDaqTxConfCtr = 0;
    Xcp_Cleared[protLayerId].Debug.Xcp_Debug_SendDaqCtr = 0;
# endif
#endif
  }

  /* call all transportlayer init functions */
  for (l_transportlayer_u8 = 0; l_transportlayer_u8 < XCP_TL_IDS; l_transportlayer_u8++)
  {
    Xcp_PlCfgConst.TlCfg[l_transportlayer_u8].TLInit_pfct(l_transportlayer_u8, Xcp_GlobalNoInit.InitStatus_u8);
  }


  /* XCP initialisation finished */
  Xcp_GlobalNoInit.InitStatus_u8 = XCP_INIT;

#if (XCP_RESUME_MODE == STD_ON)
  Xcp_ResumeModeActivate();
#endif

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


#if (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON)
/**
****************************************************************************************************
Xcp_InitRam initializes the DAQ dynamic memory,
so the protocol layers will have access to the memory sections in PD and ED (if available).
\param[in]  -
\return     -
***************************************************************************************************/
LOCAL_INLINE void Xcp_InitRam(void)
{
# if (XCP_DAQRAM_LIMIT_ED > 0u)
#  ifdef RBA_MEMLAY_EDRAM_START
  /* DAQ RAM Emulation Device */
  if (rba_Eec_EdRamAvailable() != 0u)
  {
    /* overwrite only, when ED RAM is available */
    Xcp_GlobalNoInit.DaqRamSections[0].DaqRamFreeSize_u32  = XCP_DAQRAM_LIMIT_ED;
  }
#  endif
# endif

# if (XCP_DAQRAM_LIMIT > 0u)
  /* DAQ RAM Production Device */
  Xcp_GlobalNoInit.DaqRamSections[XCP_MAX_DAQRAMSECTIONS - 1u].DaqRamFreeSize_u32  = XCP_DAQRAM_LIMIT;
# endif
}
#endif

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"



