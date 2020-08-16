

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp.h"
#include "Xcp_Priv.h"
#if ((XCP_RESUME_MODE == STD_ON) && (XCP_SYNCHRONOUS_DATA_ACQUISITION_DAQ == STD_ON))
#include "NvM.h"

/***************************************************************************************************
* Type definitions
***************************************************************************************************/
/** XCP DAQ total counters and state for Resume Mode */
/* MR12 RULE 5.6 VIOLATION: Type declaration is needed only for Xcp Resume Mode to simplify the copy procedure. */
typedef struct
{
  uint16          DaqListCnt_u16;
  uint16          OdtCnt_u16;
  uint16          OdtEntryCnt_u16;
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
  uint16          OdtStimCnt_u16;
# endif
  Xcp_DaqState_t  DaqState_en;
} Xcp_DaqResumeData_t;


/***************************************************************************************************
* Macros
***************************************************************************************************/
#define XCP_BLOCK_INFO_INDEX 0u
#define XCP_BLOCK_DATA_INDEX 1u


/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"
static void Xcp_EvResumeMode(uint8 protLayerId);
static void Xcp_EvClearDaq(uint8 protLayerId);
static void Xcp_EvStoreDaq(uint8 protLayerId);
static Xcp_ErrorCode Xcp_PrepareNVMBlock(uint8 protLayerId);
static void Xcp_RestoreDaqConfig(uint8 protLayerId);
static void Xcp_ConnectTransportLayer(uint8 protLayerId, uint8 XcpTransportLayerId);
static void Xcp_DaqSetResumeMode(uint8 protLayerId);
static Std_ReturnType Xcp_NvMReadBlock(uint8 BlockNo, void* AddrDataPtr);
static void Xcp_EvStoreClearTrigger(void);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"


/***************************************************************************************************
* Functions
***************************************************************************************************/

#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h"

/**
****************************************************************************************************
This service handles the entering RESUME mode or clearing the saved DAQ configuration
\param[in]  XcpPacket     Pointer to the received command packet
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
void Xcp_CmdSetRequest(const PduInfoType* XcpPacket, uint8 protLayerId)
{
  /*Start of run time measurement*/
  XCP_RTM_TIMETRACK_START()

  /* Command variables */
  /* MR12 RULE 11.5, 1.1 VIOLATION: This function is called with data (a PDU) from the CanIf/FrIf/EthIf which ensure 4-Byte-Alignment.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  const Xcp_CmdSetRequest_t* const CmdPtr = (const Xcp_CmdSetRequest_t*) (void*) XcpPacket->SduDataPtr;

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Initialization */
  Error = XCP_NO_ERROR;

  /* If the SetRequest command is received for Protocol Layer 1 return ERR_GENERIC */
  /* because saving from PL 1 is not possible in NvM due to access to protected memory area */
  if (protLayerId >= 1u)
  {
    Error = XCP_ERR_GENERIC;
  }
  else if (Xcp_GlobalNoInit.SetRequestData.StorageMode != XCP_STORE_IDLE)
  {
    /* If any SET_REQUEST is in progress reject the new received request */
    Error = XCP_ERR_CMD_BUSY;
  }
  else if (CmdPtr->Mode_u8 == XCP_SET_REQUEST_STORE_CAL_REQ)
  {
    /* STORE_CAL_REQ not supported now */
    Error = XCP_ERR_OUT_OF_RANGE;
  }
  else
  {
    /* Branch for MISRA compliance */
  }

  if (Error == XCP_NO_ERROR)
  {
    if (CmdPtr->Mode_u8 == XCP_SET_REQUEST_STORE_DAQ_REQ_RESUME)
    {
      /* Set the session information to XCP_STORE_DAQ_REQ */
      XCP_RESUME_SESSION_STATUS(protLayerId) = XCP_STORE_DAQ_REQ;
      /* Store Session Configuration ID from the received command */
      Xcp_NoInit[protLayerId].Session.SessionConfId_u16 = CmdPtr->SessionConfigID_u16;
      /* Set requested storing mode to write so that the data is written to NvM */
      Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_MODE_WRITE;
      /* Check if any DAQ list is selected - only selected lists should be saved in NvM */
      Xcp_DaqSetResumeMode(protLayerId);
      /* Pack the data to be copied in the NvM blocks */
      Error = Xcp_PrepareNVMBlock(protLayerId);

      if (Error != XCP_NO_ERROR)
      {
        /* Reset the session information to XCP_STORE_DAQ_REQ */
        XCP_RESUME_SESSION_STATUS(protLayerId) &= (uint8)(~XCP_STORE_DAQ_REQ);
      }
    }
    else if (CmdPtr->Mode_u8 == XCP_SET_REQUEST_CLEAR_DAQ_REQ)
    {
      /* Set the session information to XCP_CLEAR_DAQ_REQ */
      XCP_RESUME_SESSION_STATUS(protLayerId) = XCP_CLEAR_DAQ_REQ;
      /* Clear the SessionConfId */
      Xcp_NoInit[protLayerId].Session.SessionConfId_u16 = 0;
      /* Set requested storing mode to clear so that the data is cleared from NvM */
      Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_MODE_CLEAR;
    }
    else
    {
      /* The requested mode is not a valid mode */
      Error = XCP_ERR_OUT_OF_RANGE;
    }
  }

  if (Error == XCP_NO_ERROR)
  {
    /* Prepare and send positive response */
    Xcp_SendPosRes(protLayerId);
  }
  else
  {
    /* Reset storage mode */
    Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_IDLE;
    /* Send negative response */
    Xcp_SendErrRes(Error, protLayerId);
  }

  /*End of run time measurement*/
  XCP_RTM_TIMETRACK_FINISH()
}


/**
****************************************************************************************************
This service activates the RESUME mode at init and sets DAQ list in mode RUNNING
\param[in]  -
\return     -
***************************************************************************************************/
void Xcp_ResumeModeActivate(void)
{
  /* local variables */
  uint8 protLayerId;
  uint8 transLayerId;

  /* Trigger read of the NVM block that contains the basic information: TransLayerId, ProtLayerId, DAQ configuration size, SessionConfigurationId */
  /* MR12 DIR 1.1 VIOLATION: The input parameters of Xcp_NvMReadBlock() are declared as (void*) so we have to cast. */
  if (Xcp_NvMReadBlock(XCP_BLOCK_INFO_INDEX, (void*)&Xcp_GlobalNoInit.SetRequestData.TLData_t) == E_OK)
  {
    /* Extract the transport layer id and check the validity */
    transLayerId = Xcp_GlobalNoInit.SetRequestData.TLData_t.ConnectedTlId_u8;
    if (transLayerId != 0xFF)
    {
      protLayerId = 0u;
      /* The connected Transport Layer Id must be set because is used in the RAM setting function to retrieve the RAM size for DAQ */
      Xcp_NoInit[protLayerId].Session.ConnectedTlId_u8 = transLayerId;
      /* Connect always with the first Protocol Layer after reset to avoid wrong memory access */
      (void)Xcp_DaqRamSetRam(protLayerId);
      /* Set back the connected TL to 0xFF because in case Resume Mode is not requested no connection should be done */
      Xcp_NoInit[protLayerId].Session.ConnectedTlId_u8 = 0xFF;
      /* Check if the DaqRamPtr was set by the Xcp_DaqRamSetRam */
      if (Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8 != NULL_PTR)
      {
        /* MR12 DIR 1.1 VIOLATION: The input parameters of Xcp_NvMReadBlock() are declared as (void*) so we have to cast. */
        if (Xcp_NvMReadBlock(XCP_BLOCK_DATA_INDEX, (void*)Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8) == E_OK)
        {
          /* If the read was successful restore DAQ configuration and set RESUME mode if required */
          Xcp_RestoreDaqConfig(protLayerId);
        }
      }
      else
      {
        /* Read ended with error - call DET to signal that no DAQ configuration is restored because of pointer initialization issues */
        XCP_DET_REPORT_ERROR_NO_RET(XCP_INITIALIZE_SID, XCP_E_INV_POINTER);
      }
    }
    else
    {
      /* Read ended with error - call DET to signal that no valid data was restored */
      XCP_DET_REPORT_ERROR_NO_RET(XCP_INITIALIZE_SID, XCP_E_INV_POINTER);
    }
  }
  else
  {
    /* Read ended with error - nothing to be done */
    /* This can happen after a previous CLEAR_DAQ_REQ as well since this is invalidating the NvM block for a next read */
  }
}


/**
****************************************************************************************************
This service treats the resume mode store request - saving in NVM and must be called
from Xcp_MainFunction
\param[in]  -
\return     -
***************************************************************************************************/
/* HIS METRIC v(G) VIOLATION IN Xcp_ResumeModeStorage: Function contains very simple "else if" statements and "switch-cases". HIS metric compliance would decrease readability and maintainability. */
void Xcp_ResumeModeStorage(void)
{
  /* local variables */
  Std_ReturnType NvM_GetErrorStatusResult;
  NvM_RequestResultType BlockStatus;
  Std_ReturnType ErrorState;
  uint8 protLayerId;

  /* Initialization */
  NvM_GetErrorStatusResult = E_NOT_OK;
  ErrorState = E_OK;
  protLayerId = 0u;

  /* State machine for the processing of a STORE or CLEAR in NvM */
  switch (Xcp_GlobalNoInit.SetRequestData.ReqProcessingState)
  {
    case XCP_NVM_NO_JOB:
    {
      /* State machine for processing the requested mode in SET_REQUEST */
      switch (Xcp_GlobalNoInit.SetRequestData.StorageMode)
      {
        case XCP_STORE_MODE_WRITE:
        {
          /* First NvM block is processed - erase first the TranspLayer information and DAQ size */
          ErrorState = NvM_EraseNvBlock(Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_INFO_INDEX].BlockId);
          /* Next state will be to write the NVM DATA block with DAQ configuration */
          Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_MODE_BLOCK_DATA_WRITE;
          /* Request received by NvM - set processing status to XCP_NVM_JOB_RUNNING */
          Xcp_GlobalNoInit.SetRequestData.ReqProcessingState = XCP_NVM_JOB_RUNNING;
        }
        break;

        case XCP_STORE_MODE_BLOCK_INFO_WRITE:
        {
          /* Request the writing to NvM for the TransportLayer information and DAQ size block */
          /* MR12 DIR 1.1 VIOLATION: The input parameters of NvM_WriteBlock() are declared as (void*) so we have to cast. */
          ErrorState = NvM_WriteBlock(Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_INFO_INDEX].BlockId, (void*)&Xcp_GlobalNoInit.SetRequestData.TLData_t);
          /* Next state is set to XCP_STORE_MODE_WRITE to send the EV_STORE_DAQ */
          Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_MODE_WRITE;
          /* Request received by NvM - set processing status to XCP_NVM_JOB_RUNNING */
          Xcp_GlobalNoInit.SetRequestData.ReqProcessingState = XCP_NVM_JOB_RUNNING;
        }
        break;

        case XCP_STORE_MODE_BLOCK_DATA_WRITE:
        {
          /* Request the writing to NvM for the DAQ configuration block */
          /* MR12 DIR 1.1 VIOLATION: The input parameters of NvM_WriteBlock() are declared as (void*) so we have to cast. */
          ErrorState = NvM_WriteBlock(Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_DATA_INDEX].BlockId, (void*)Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8);
          /* Next state will be writing the INFO block */
          Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_MODE_BLOCK_INFO_WRITE;
          /* Request received by NvM - set processing status to XCP_NVM_JOB_RUNNING */
          Xcp_GlobalNoInit.SetRequestData.ReqProcessingState = XCP_NVM_JOB_RUNNING;
        }
        break;

        case XCP_STORE_MODE_CLEAR:
        {
          /* Request the erase of TransportLayer information and DAQ size block from NvM */
          ErrorState = NvM_EraseNvBlock(Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_INFO_INDEX].BlockId);
          /* Next state will trigger erase of the DAQ configuration block */
          Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_MODE_BLOCK_DATA_CLEAR;
          /* Request received by NvM - set processing status to XCP_NVM_JOB_RUNNING */
          Xcp_GlobalNoInit.SetRequestData.ReqProcessingState = XCP_NVM_JOB_RUNNING;
        }
        break;

        case XCP_STORE_MODE_BLOCK_DATA_CLEAR:
        {
          /* Request the erase of DAQ configuration block from NvM */
          ErrorState = NvM_EraseNvBlock(Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_DATA_INDEX].BlockId);
          /* Next state is XCP_STORE_MODE_CLEAR to trigger the sending of EV_CLEAR_DAQ */
          Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_MODE_CLEAR;
          /* Request received by NvM - set processing status to XCP_NVM_JOB_RUNNING */
          Xcp_GlobalNoInit.SetRequestData.ReqProcessingState = XCP_NVM_JOB_RUNNING;
        }
        break;

        default:
          /* The default is empty, as we are handling all elements of the enum in the cases of this switch, but we shall have a default-case */
        break;
      }
    }
    break;

    case XCP_NVM_JOB_RUNNING:
    {
      if ((Xcp_GlobalNoInit.SetRequestData.StorageMode == XCP_STORE_MODE_WRITE)
         || (Xcp_GlobalNoInit.SetRequestData.StorageMode == XCP_STORE_MODE_BLOCK_DATA_WRITE)
         || (Xcp_GlobalNoInit.SetRequestData.StorageMode == XCP_STORE_MODE_BLOCK_DATA_CLEAR))
      {
        /* Ask the status of the NvM operation for the INFO block */
        NvM_GetErrorStatusResult = NvM_GetErrorStatus(Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_INFO_INDEX].BlockId, &BlockStatus);
      }
      else
      {
        /* Ask the status of the NvM operation for the DATA block */
        NvM_GetErrorStatusResult = NvM_GetErrorStatus(Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_DATA_INDEX].BlockId, &BlockStatus);
      }

      if (NvM_GetErrorStatusResult == E_OK)
      {
        if (BlockStatus == NVM_REQ_OK)
        {
          /* Set back the processing state to XCP_NVM_NO_JOB to start processing the next block if any available */
          Xcp_GlobalNoInit.SetRequestData.ReqProcessingState = XCP_NVM_NO_JOB;
          Xcp_EvStoreClearTrigger();
        }
        else if (BlockStatus != NVM_REQ_PENDING)
        {
          /* Request is rejected by NvM - set error status */
          ErrorState = E_NOT_OK;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      {
        /* Request is rejected by NvM - set error status */
        ErrorState = E_NOT_OK;
      }
    }
    break;

    default:
      /* The default is empty, as we are handling all elements of the enum in the cases of this switch, but we shall have a default-case */
    break;
  }

  /* Check if any of the requests returned error */
  if (ErrorState == E_NOT_OK)
  {
    /* In case the configuration could not be saved in NvM set the SessionConfId back to 0 to signal that no NvM data is available */
    Xcp_NoInit[protLayerId].Session.SessionConfId_u16 = 0;
    /* Set back also the session status bit to avoid wrong information as response from GET_STATUS */
    XCP_RESUME_SESSION_STATUS(protLayerId) &= ((uint8)(~XCP_STORE_DAQ_REQ) & (uint8)(~XCP_CLEAR_DAQ_REQ));
    /* Set the request processing state to no request to be able to process a new request from Master */
    Xcp_GlobalNoInit.SetRequestData.ReqProcessingState = XCP_NVM_NO_JOB;
    /* If any of the block writing or clearing failed then stop further processing */
    Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_IDLE;
  }
}


/***************************************************************************************************
* Local functions
***************************************************************************************************/

/**
****************************************************************************************************
This service copies the needed data for the RESUME mode
\param[in]  protLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR              Prepare successful
\retval     XCP_ERR_DAQ_ACTIVE        daq running
\retval     XCP_ERR_MEMORY_OVERFLOW   no place to save DAQ config
***************************************************************************************************/
static Xcp_ErrorCode Xcp_PrepareNVMBlock(uint8 protLayerId)
{
  /* local variables */
  Xcp_ErrorCode Error;

  /* Initialization */
  Error = XCP_NO_ERROR;

  /* If DAQ runs when SET_REQUEST is received respond with error XCP_ERR_DAQ_ACTIVE */
  if (Xcp_NoInit[protLayerId].DaqConfig.DaqState_en == XCP_DAQ_STATE_RUNNING)
  {
    Error = XCP_ERR_DAQ_ACTIVE;
  }
  else
  {
    /* local variables */
    uint32 BlockSize;
    uint32 WriteRamPos;
    uint32 MaxRamCopySize;
    Xcp_DaqResumeData_t* Xcp_DaqResumeData;

    /* MR12 RULE 11.4 VIOLATION: We want to have a pointer to a 4-byte-aligned address at/after the given element (address), hence casting is necessary */
    WriteRamPos = XCP_4BYTE_ALIGN((uint32) Xcp_NoInit[protLayerId].DaqConfig.PriorityList_p) - (uint32) Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8;
    /* Calculate needed block size for all DAQ configuration */
    BlockSize = WriteRamPos + sizeof(Xcp_DaqResumeData_t);
    /* Calculate the maximum position in the DAQ RAM pointer where the transport layer information can be saved */
    MaxRamCopySize = XCP_MIN(Xcp_NoInit[protLayerId].DaqConfig.DaqRamSize_u32, Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_DATA_INDEX].BlockLength);

    /* Check if enough space to copy in the NvM INFO block */
    if (sizeof(Xcp_SmallBlockData_t) <= Xcp_PlCfgConst.NvMBlockInfo[XCP_BLOCK_INFO_INDEX].BlockLength)
    {
      /* In the NvM INFO block the saved data is: Connected Transport Layer Id, Protocol Layer Id, DAQ configuration size and SessionConfigurationId */
      Xcp_GlobalNoInit.SetRequestData.TLData_t.ConnectedTlId_u8 = Xcp_NoInit[protLayerId].Session.ConnectedTlId_u8;
      Xcp_GlobalNoInit.SetRequestData.TLData_t.DaqConfigSize_u32 = WriteRamPos;
      Xcp_GlobalNoInit.SetRequestData.TLData_t.SessionConfId_u16 = Xcp_NoInit[protLayerId].Session.SessionConfId_u16;
      /* Call TransportLayer function to copy the data specific for this TranspLayer */
      Error = Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TLResumeModeData_pfct(&Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8[BlockSize], &Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8[MaxRamCopySize], XCP_ACTIVE_TL_ID(protLayerId));

      if (Error == XCP_NO_ERROR)
      {
        /* Check if it is enough space in NVM DATA block for the DAQ configuration */
        if ((BlockSize > 0u) && (BlockSize <= MaxRamCopySize))
        {
          /* MR12 RULE 11.5, 1.1 VIOLATION: The pointer cast is required for copying the data from the Daq pointer to local structure */
          Xcp_DaqResumeData = (Xcp_DaqResumeData_t*)((void*)&Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8[WriteRamPos]);
          /* Copy at the end of DAQ configuration the overall information for the DAQ lists */
          Xcp_DaqResumeData->DaqListCnt_u16 = Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16;
          Xcp_DaqResumeData->OdtCnt_u16 = Xcp_NoInit[protLayerId].DaqConfig.OdtCnt_u16;
          Xcp_DaqResumeData->OdtEntryCnt_u16 = Xcp_NoInit[protLayerId].DaqConfig.OdtEntryCnt_u16;
        #if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
          Xcp_DaqResumeData->OdtStimCnt_u16 = Xcp_NoInit[protLayerId].DaqConfig.OdtStimCnt_u16;
        #endif
          Xcp_DaqResumeData->DaqState_en = Xcp_NoInit[protLayerId].DaqConfig.DaqState_en;
        }
        else
        {
          /* not enough space in NvM block */
          Error = XCP_ERR_MEMORY_OVERFLOW;
        }
      }
    }
    else
    {
      /* not enough space in NvM block */
      Error = XCP_ERR_MEMORY_OVERFLOW;
    }
  }

  return Error;
}


/**
****************************************************************************************************
This service restores in DAQ config the NVM data, sends Ev_ResumeMode and sets RESUME DAQ lists to
running mode if requested mode is RESUME
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_RestoreDaqConfig(uint8 protLayerId)
{
  /* local variables */
  uint16 daqListNo;
  uint32 DaqSize;
  boolean ResumeReq;
  Xcp_DaqResumeData_t* Xcp_DaqResumeData;

  /* Initialization */
  ResumeReq = FALSE;

  /* Restore the DAQ size */
  DaqSize = Xcp_GlobalNoInit.SetRequestData.TLData_t.DaqConfigSize_u32;
  /* MR12 RULE 11.5, 1.1 VIOLATION: The pointer cast is required for copying the data from local structure to Daq pointer */
  /* Copy back to DAQ config the saved configuration: number of DAQ list, ODTs, ODT entries and DAQ state */
  Xcp_DaqResumeData = (Xcp_DaqResumeData_t*)((void*)&Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8[DaqSize]);
  /* Check if the resume was requested and if read back data is valid before restoring it in the structures. */
  if (Xcp_DaqResumeData->DaqListCnt_u16 > 0u)
  {
    /* Restore Session Configuration Id */
    Xcp_NoInit[protLayerId].Session.SessionConfId_u16 = Xcp_GlobalNoInit.SetRequestData.TLData_t.SessionConfId_u16;
    /* Copy the DAQ info in case PL is valid and DAQ info read from NvM is not empty */
    Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16 = Xcp_DaqResumeData->DaqListCnt_u16;
    Xcp_NoInit[protLayerId].DaqConfig.OdtCnt_u16 = Xcp_DaqResumeData->OdtCnt_u16;
    Xcp_NoInit[protLayerId].DaqConfig.OdtEntryCnt_u16 = Xcp_DaqResumeData->OdtEntryCnt_u16;
# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
    Xcp_NoInit[protLayerId].DaqConfig.OdtStimCnt_u16 = Xcp_DaqResumeData->OdtStimCnt_u16;
# endif
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = Xcp_DaqResumeData->DaqState_en;
    /* Check if any of the DAQ lists was marked for start in RESUME and set ResumeReq flag */
    for (daqListNo = 0; daqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; daqListNo++)
    {
      if ((XCP_DAQ_MODE(daqListNo, protLayerId) & XCP_DAQLISTMODE_RESUME) == XCP_DAQLISTMODE_RESUME )
      {
        ResumeReq = TRUE;
        break; /* Break to exit the loop once a DAQ list with resume is found */
      }
    }
  }
  /* If any DAQ list was selected for resume mode send EV_RESUME_MODE, set session status to resume and DAQ running */
  if (ResumeReq == TRUE)
  {
    uint32 BlockSize;

    /* Call this function to set necessary transport layer parameters to the required protocol layer */
    Xcp_ConnectTransportLayer(protLayerId, Xcp_GlobalNoInit.SetRequestData.TLData_t.ConnectedTlId_u8);
    /* Calculate the position were Transport Layer data is saved */
    BlockSize = DaqSize + sizeof(Xcp_DaqResumeData_t);
    /* Call Transport Layer function to set back the communication parameters */
    (void)Xcp_PlCfgConst.TlCfg[XCP_ACTIVE_TL_ID(protLayerId)].TLResumeModeData_pfct(&Xcp_NoInit[protLayerId].DaqConfig.DaqRamPtr_pu8[BlockSize], NULL_PTR, XCP_ACTIVE_TL_ID(protLayerId));
    /* Call Xcp_DaqRamCalc to calculate the needed memory for DAQ configuration and set the pointers to Daq, Odt, Odt entry information from DaqConfig */
    (void)Xcp_DaqRamCalc(0, 0, 0, protLayerId);
    /* Call Xcp_DaqQueRamCalc to calculate needed memory for DAQ queue and initialize corresponding pointers */
    (void)Xcp_DaqQueRamCalc(0, TRUE, protLayerId);
    /* Now EV_RESUME_MODE can be sent */
    Xcp_EvResumeMode(protLayerId);

    for (daqListNo = 0; daqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; daqListNo++)
    {
      if ((XCP_DAQ_MODE(daqListNo, protLayerId) & XCP_DAQLISTMODE_RESUME) == XCP_DAQLISTMODE_RESUME)
      {
        Xcp_DaqListStart(daqListNo, protLayerId);
      }
    }
    /* Recalculate PriorityList to prioritize the started DAQ lists for RESUME mode */
    Xcp_DaqCalculatePriorityList(protLayerId);
    /* Set RESUME mode flag - is returned in GET_STATUS response */
    XCP_RESUME_SESSION_STATUS(protLayerId) = XCP_RESUME;
    /* Set DAQ-state to running */
    Xcp_NoInit[protLayerId].DaqConfig.DaqState_en = XCP_DAQ_STATE_RUNNING;
    /* Set XCP in state RESUME */
    Xcp_NoInit[protLayerId].Session.XcpState_en = XCP_STATE_RESUME;
  }
}


/**
****************************************************************************************************
This service sends the event EV_RESUME_MODE
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_EvResumeMode(uint8 protLayerId)
{
  /* local variables */
  Xcp_Cto8_t XcpEvPacket;
  Xcp_EvResumeMode_t* EvPtr;

  /* initialize event packet */
  XcpEvPacket.Length_u32 = XCP_EV_RESUME_MODE_LENGTH;
  /* MR12 RULE 11.5, 1.1 VIOLATION: Compiler ensures the correct alignment in the datastructure, thus casting is no problem.
                                    The cast allows easier (= safer) access to the data in the PDU.
                                    Casting over void* is necessary as otherwise some compilers complain */
  EvPtr = (Xcp_EvResumeMode_t*) (void*) XcpEvPacket.Buffer_au8;

  /* prepare Resume Mode event */
  EvPtr->PacketId_u8  = XCP_PACKET_ID_EV;
  EvPtr->EventCode_u8 = XCP_EV_RESUME_MODE;
  EvPtr->SessionConfigID_u16 = Xcp_NoInit[protLayerId].Session.SessionConfId_u16;
  /* Depending on the timestamp support send the calculated timestamp or 0 */
# if (XCP_TIMESTAMP == STD_ON)
  EvPtr->Timestamp_u32 = XcpAppl_GetTimestamp();
# else
  EvPtr->Timestamp_u32 = 0;
# endif
  /* send out event */
  Xcp_SendEv(&XcpEvPacket, protLayerId);
}


/**
****************************************************************************************************
This service sends the event EV_CLEAR_DAQ
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_EvClearDaq(uint8 protLayerId)
{
  /* Clear the CLEAR_DAQ_REQ bit that is received by the GET_STATUS */
  XCP_RESUME_SESSION_STATUS(protLayerId) = XCP_RESUME_SESSION_STATUS(protLayerId) & (uint8)(~XCP_CLEAR_DAQ_REQ);
  /* send out XCP_EV_CLEAR_DAQ event */
  Xcp_SendEv_Code(XCP_EV_CLEAR_DAQ, protLayerId);
}


/**
****************************************************************************************************
This service sends the event EV_STORE_DAQ
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_EvStoreDaq(uint8 protLayerId)
{
  /* Clear the STORE_DAQ_REQ bit that is received by the GET_STATUS */
  XCP_RESUME_SESSION_STATUS(protLayerId) = XCP_RESUME_SESSION_STATUS(protLayerId) & (uint8)(~XCP_STORE_DAQ_REQ);
  /* send out XCP_EV_STORE_DAQ event */
  Xcp_SendEv_Code(XCP_EV_STORE_DAQ, protLayerId);
}


/**
****************************************************************************************************
This service sets necessary information for the transport layer in the corresponding protocol layer
\param[in]  protLayerId           Protocol Layer Id
\param[in]  XcpTransportLayerId   Transport Layer Id
\return     -
***************************************************************************************************/
static void Xcp_ConnectTransportLayer(uint8 protLayerId, uint8 XcpTransportLayerId)
{
  /* save transport layer id in protocol layer */
  XCP_ACTIVE_TL_ID(protLayerId) = XcpTransportLayerId;
  /* save protocol layer id in lookup table */
  Xcp_GlobalNoInit.Tl2PlRef_au8[XcpTransportLayerId] = protLayerId;
  /* save TransportLayerId and transport layer specific parameters */
  Xcp_NoInit[protLayerId].Session.MaxCto_u8 = Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].MaxCto_u8;
  Xcp_NoInit[protLayerId].Session.MaxDto_u16 = Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].MaxDto_u16;
  Xcp_NoInit[protLayerId].Session.MaxDto4Aligned_u16 = XCP_4BYTE_ALIGN(Xcp_NoInit[protLayerId].Session.MaxDto_u16);
# if (XCP_IDFIELD_OTHER_THAN_ABSOLUTE == STD_ON)
  Xcp_NoInit[protLayerId].Session.IdFieldType_en = Xcp_PlCfgConst.TlCfg[XcpTransportLayerId].IdFieldType_en;
# endif
}


/**
****************************************************************************************************
This service sets DAQ list mode to Resume for selected DAQ lists
\param[in]  protLayerId   Protocol Layer Id
\return     -
***************************************************************************************************/
static void Xcp_DaqSetResumeMode(uint8 protLayerId)
{
  uint16 daqListNo;

  for (daqListNo = 0; daqListNo < Xcp_NoInit[protLayerId].DaqConfig.DaqListCnt_u16; daqListNo++)
  {
    /* Check if any DAQ list is selected */
    if ((XCP_DAQ_MODE(daqListNo, protLayerId) & XCP_DAQLISTMODE_SELECTED) == XCP_DAQLISTMODE_SELECTED)
    {
      /* Reset SELECTED flag and set RESUME flag for previously selected lists */
      XCP_DAQ_MODE(daqListNo, protLayerId) = (XCP_DAQ_MODE(daqListNo, protLayerId) & (uint8)(~XCP_DAQLISTMODE_SELECTED)) | XCP_DAQLISTMODE_RESUME;
    }
  }
}


/**
****************************************************************************************************
Read out the NvM-Block specified by BlockNo
\param[in]  BlockNo       NvM Block number in generated structure
\param[in]  AddrDataPtr   Pointer to location where the data shall be stored
\return     Read successful
***************************************************************************************************/
static Std_ReturnType Xcp_NvMReadBlock(uint8 BlockNo, void* AddrDataPtr)
{
  NvM_RequestResultType ReadResult;
  Std_ReturnType NvM_GetErrStatusResult;
  Std_ReturnType ReturnStatus;

  /* Call NvM_ReadBlock to read the TransportLayer, DAQ size or DAQ configuration */
  if (NvM_ReadBlock(Xcp_PlCfgConst.NvMBlockInfo[BlockNo].BlockId, AddrDataPtr) == E_OK)
  {
    do
    {
      /* Call NvM_MainFunction and MemIf_Rb_MainFunction to process the request */
      NvM_MainFunction();
      MemIf_Rb_MainFunction();
      NvM_GetErrStatusResult = NvM_GetErrorStatus(Xcp_PlCfgConst.NvMBlockInfo[BlockNo].BlockId, &ReadResult);
    }while((NvM_GetErrStatusResult == E_OK) && (ReadResult == NVM_REQ_PENDING));
    /* Check if the read from NvM was successfully done */
    if (ReadResult == NVM_REQ_OK)
    {
      ReturnStatus = E_OK;
    }
    else
    {
      ReturnStatus = E_NOT_OK;
    }
  }
  else
  {
    /* If the NvM_ReadBlock request was not accepted by NvM return E_NOT_OK */
    ReturnStatus = E_NOT_OK;
  }

  return ReturnStatus;
}


/**
****************************************************************************************************
This service triggers the sending of EV_STORE_DAQ or EV_CLEAR_DAQ
\param[in]  -
\return     -
***************************************************************************************************/
static void Xcp_EvStoreClearTrigger(void)
{
  uint8 protLayerId;

  protLayerId = 0u;

  if (Xcp_GlobalNoInit.SetRequestData.StorageMode == XCP_STORE_MODE_CLEAR)
  {
    /* Clearing of NvM DAQ configuration is finished - send the EV_CLEAR_DAQ */
    Xcp_EvClearDaq(protLayerId);
    /* Set the request processing state to XCP_STORE_IDLE to be able to process a new request */
    Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_IDLE;
  }
  else if (Xcp_GlobalNoInit.SetRequestData.StorageMode == XCP_STORE_MODE_WRITE)
  {
    /* Storing of NvM DAQ configuration is finished - send the EV_STORE_DAQ */
    Xcp_EvStoreDaq(protLayerId);
    /* Set the request processing state to XCP_STORE_IDLE to be able to process a new request */
    Xcp_GlobalNoInit.SetRequestData.StorageMode = XCP_STORE_IDLE;
  }
  else
  {
    /* Nothing to do */
  }
}

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h"

#else
  /* HIS METRIC COMF VIOLATION IN Xcp_CmdSetRequest.c: The feature is not enabled - no code is needed in this file */
#endif



