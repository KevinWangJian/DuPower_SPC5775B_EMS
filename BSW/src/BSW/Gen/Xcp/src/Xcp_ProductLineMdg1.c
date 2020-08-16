

/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"

#if (XCP_PRODUCT_LINE == XCP_PRODUCT_LINE_MDG1)
#include "Xcp_Cfg_SchM.h"
#include "rba_Dme.h"
#include "rba_MemLay.h"
#include "rba_EcuSecu.h"
#if (XCP_CMD_RECEIVED_NOTIFICATION == STD_ON)
#include "rba_CalWup.h"
#endif
#if (XCP_TIMESTAMP == STD_ON)
#include "Mcu_Rb_SystemTimer.h"
#endif
#include "Xcp_Priv.h" /* Not really wished but only solution to set the enabledResources without getting recursion */


/***************************************************************************************************
* Variables
***************************************************************************************************/

/************************** START POWER_ON_CLEARED UNSPECIFIED  **********************************/
#define XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

typedef struct
{
  uint8 CalPage_u8;
}XcpAppl_Data_t;

/* XcpAppl_Data also needed for BuildChecksum and Up-/Download, when XCP_PAGE_SWITCHING_PAG off */
static XcpAppl_Data_t XcpAppl_Data[XCP_PL_IDS];

#if (XCP_TIMESTAMP == STD_ON)
static uint32 XcpAppl_Timestamp_u32;
static uint32 XcpAppl_ModuloCounter_u32;
static uint32 XcpAppl_LastCounter_u32;
#endif /* (XCP_TIMESTAMP == STD_ON) */

#define XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
/************************** STOP POWER_ON_CLEARED UNSPECIFIED  ***********************************/


/************************** START CONST UINT32 *****************************************/
#define XCP_START_SEC_CONST_32
#include "Xcp_MemMap.h"

#if(XCP_PL_IDS == 2)
static const uint32 XcpAppl_DmeUser[XCP_PL_IDS] = {RBA_DME_USER_XCP_0, RBA_DME_USER_XCP_1};
#else
static const uint32 XcpAppl_DmeUser[XCP_PL_IDS] = {RBA_DME_USER_XCP_0};
#endif

#define XCP_STOP_SEC_CONST_32
#include "Xcp_MemMap.h"
/************************** STOP CONST UINT32 *******************************************/


/************************** START CLEARED UNSPECIFIED  *********************************/
#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
/** Checksum global data structure */
typedef struct
{
  uint32 BlockSize_u32;
  uint32 ChecksumValue;
  Xcp_AdrPtrConst AddrPtr;
}XcpAppl_BuildChecksum_t;
static XcpAppl_BuildChecksum_t XcpAppl_BuildChecksumData[XCP_PL_IDS];
#endif /* (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) */


#define XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"
/************************** STOP CLEARED UNSPECIFIED  **********************************/


/***************************************************************************************************
* Local function declarations
***************************************************************************************************/
static void XcpAppl_EcuSecuDisableCalStim(void);


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

/***************************************************************************************************
* Xcp_BuildChecksum.c_tpl filled out for MDG1
***************************************************************************************************/
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function triggers checksum calculation
\param[in]  AddrPtr           start address of memory block
\param[in]  BlockSize         size of memory block from which the checksum should be calculated
\param[in]  ProtocolLayerId   protocol layer id
\return     ErrorCode
\retval     XCP_NO_ERROR      calculation started
\retval     XCP_ERR_CMD_BUSY  another calculation in progress
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_BuildChecksumTrigger(Xcp_AdrPtrConst AddrPtr, uint32 BlockSize, uint8 ProtocolLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check if not another calculation in progress */
  if (XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 == 0u)
  {
    /* Store data for background checksum calculation */
    XcpAppl_BuildChecksumData[ProtocolLayerId].AddrPtr = AddrPtr;
    /* Shall be at the end, because BlockSize > 0 is trigger for checksum calculation */
    XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 = BlockSize;

    /* Set return value */
    Error = XCP_NO_ERROR;
  }
  else
  {
    /* Set return value */
    Error = XCP_ERR_CMD_BUSY;
  }
  return (Error);
}


/**
****************************************************************************************************
Function to process checksum calculation
\param[out] ChecksumPtr       pointer to where calculated checksum should be stored
\param[out] ChecksumType      type of the checksum calculated by the process
\param[in]  ProtocolLayerId   Protocol Layer Id
\return     ErorCode
\retval     XCP_NO_ERROR            calculation finished
\retval     XCP_ERR_ACCESS_DENIED   wrong calpage, addr, etc
\retval     XCP_ERR_CMD_BUSY        another calculation in progress
\retval     XCP_NO_RESPONSE         nothing to do
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_BuildChecksumMainFunction(uint32* ChecksumPtr, uint8* ChecksumType, uint8 ProtocolLayerId)
{
  /* Local variables */
  uint32 DmeStatus;
  Xcp_ErrorCode Error;

  /* Check if calculation in progress - also checked in Xcp_BuildChecksumMainFunction */
  if (XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 > 0u)
  {
    /* Check if triggering calculation */
    if (XcpAppl_BuildChecksumData[ProtocolLayerId].AddrPtr != NULL_PTR)
    {
      /* Call external checksum calculation routine with stored parameters */
      /* MR12 RULE 11.4 VIOLATION: The cast from pointer to uint32 (address) is required as the function expects an uint32 as first argument */
      DmeStatus = rba_Dme_BuildChecksumCrc32((uint32)XcpAppl_BuildChecksumData[ProtocolLayerId].AddrPtr,
                                              XcpAppl_Data[ProtocolLayerId].CalPage_u8,
                                              XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32,
                                              &XcpAppl_BuildChecksumData[ProtocolLayerId].ChecksumValue,
                                              XcpAppl_DmeUser[ProtocolLayerId]);

      /* Clear given address to mark, that calculation is started */
      XcpAppl_BuildChecksumData[ProtocolLayerId].AddrPtr = NULL_PTR;
    }
    /* Or checking if calculation if ready */
    else
    {
      /* Check status of calculation */
      DmeStatus = rba_Dme_GetState(XcpAppl_DmeUser[ProtocolLayerId]);
    }

    /* Set type of checksum to return parameter */
    *ChecksumType = XCP_CHECKSUM_TYPE_CRC_32;

    /* Check status */
    switch (DmeStatus)
    {
      case (uint32) RBA_DME_ST_FINISHED:
      {
        /* Set value of checksum to return parameter */
        *ChecksumPtr = XcpAppl_BuildChecksumData[ProtocolLayerId].ChecksumValue;

        /* Clear flag that checksum is being calculated */
        XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 = 0;

        /* Calculation done */
        Error = XCP_NO_ERROR;

        break;
      }
      case (uint32) RBA_DME_ST_BUSY:
      {
        /* Continue calculation */
        Error = XCP_NO_RESPONSE;
        break;
      }
      case (uint32) RBA_DME_ST_REJECTED:
      {
        /* Clear flag that checksum is being calculated */
        XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 = 0;

        /* Set Error code */
        Error = XCP_ERR_CMD_BUSY;
        break;
      }
      case (uint32) RBA_DME_ST_PAGE_NOT_VALID:
      {
        /* Clear flag that checksum is being calculated */
        XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 = 0;

        /* Set Error code. This error code is not available in ASAM for BUILD_CHECKSUM! */
        Error = XCP_ERR_PAGE_NOT_VALID;
        break;
      }
      case (uint32) RBA_DME_ST_IDLE:
      {
        /* Clear flag that checksum is being calculated */
        XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 = 0;

        /* Set Error code */
        Error = XCP_ERR_RES_TEMP_NOT_ACCESS;
        break;
      }
      default:
      {
        /* Clear flag that checksum is being calculated */
        XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 = 0;

        /* unknown return value from DME, set generic error */
        Error = XCP_ERR_GENERIC;
        break;
      }
    }
  }
  else
  {
    Error = XCP_ERR_RES_TEMP_NOT_ACCESS;
  }
  return(Error);
}
#endif /* (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) */



/***************************************************************************************************
* Xcp_CalPage.c_tpl filled out for MDG1
***************************************************************************************************/
#if (XCP_CMD_SET_CAL_PAGE_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function sets active calibration page
\param[in]  Mode              mode given from the command (ECU, XCP, All)
\param[in]  SegNum            segment number
\param[in]  PageNum           calibration data page
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_PAGE_NOT_VALID      Page not valid
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_SetCalPage(uint8 Mode, uint8 SegNum, uint8 PageNum, uint8 ProtocolLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(SegNum);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Initial values */
  Error = XCP_NO_ERROR;

  /* Check if valid page number */
  if(PageNum < RBA_DME_NUM_PAGE)
  {
    /* Check if ECU mode request */
    if((Mode & XCP_CAL_PAGE_MODE_ECU) != 0u)
    {
      /* Local variables */
      uint32 DmeStatus;

      /* Call external function */
      DmeStatus = rba_Dme_SetCalPage(PageNum);

      /* Check return value */
      switch (DmeStatus)
      {
        case (uint32) RBA_DME_ST_FINISHED:
        {
          /* set Error Code */
          Error = XCP_NO_ERROR;
          break;
        }
        case (uint32) RBA_DME_ST_PAGE_NOT_VALID:
        {
          /* set Error Code */
          Error = XCP_ERR_PAGE_NOT_VALID;
          break;
        }
        default:
        {
          /* unknown return value from DME, set generic Error */
          Error = XCP_ERR_GENERIC;
          break;
        }
      }
    }

    /* Check if XCP mode request */
    if((Mode & XCP_CAL_PAGE_MODE_XCP) != 0u)
    {
      /* Store Calibration Page number */
      XcpAppl_Data[ProtocolLayerId].CalPage_u8 = PageNum;
    }
  }
  else
  {
    /* set Error Code */
    Error = XCP_ERR_PAGE_NOT_VALID;
  }

  /* return Error Code */
  return(Error);
}
#endif


#if (XCP_CMD_GET_CAL_PAGE_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function gets active calibration page
\param[in]  Mode              mode given from the command (ECU, XCP, All)
\param[in]  SegNum            segment number
\param[out] PageNum           calibration data page
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_GetCalPage(uint8 Mode, uint8 SegNum, uint8* PageNum, uint8 ProtocolLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(SegNum);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  if(Mode == XCP_CAL_PAGE_MODE_ECU)
  {
    /* Call external function */
    *PageNum = rba_Dme_GetCalPage();
    Error = XCP_NO_ERROR;
  }
  /* Check if XCP mode request */
  else if(Mode == XCP_CAL_PAGE_MODE_XCP)
  {
    /* Get locally stored CalPage Number */
    *PageNum = XcpAppl_Data[ProtocolLayerId].CalPage_u8;
    Error = XCP_NO_ERROR;
  }
  /* All other possibilities are invalid */
  else
  {
    /* Mode is not supported */
    Error = XCP_ERR_MODE_NOT_VALID;
  }

  /* Return currently active calibration page  */
  return(Error);
}
#endif


#if (XCP_CMD_COPY_CAL_PAGE_AVAILABLE == STD_ON)
/**
****************************************************************************************************
Function copies calibration page
\param[in]  SegNumSrc         Source Segment
\param[in]  PageNumSrc        Source Page
\param[in]  SegNumDst         Destination Segment
\param[in]  PageNumDst        Destination Page
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR                sucess
\retval     XCP_ERR_PAGE_NOT_VALID      Page not valid
\retval     XCP_ERR_SEGMENT_NOT_VALID   Segment not valid
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_CopyCalPage(uint8 SegNumSrc, uint8 PageNumSrc, uint8 SegNumDst, uint8 PageNumDst, uint8 ProtocolLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(SegNumSrc);
  XCP_PARAM_UNUSED(SegNumDst);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Only copy from page 0 to page 1 is supported */
  if ((PageNumSrc==0) && (PageNumDst == 1))
  {
    rba_Dme_Reset();
    Error = XCP_NO_ERROR;
  }
  else
  {
    Error = XCP_ERR_PAGE_NOT_VALID;
  }

  /* return Error Code */
  return(Error);
}
#endif



/***************************************************************************************************
* Xcp_CmdReceived.c_tpl filled out for MDG1
***************************************************************************************************/
#if (XCP_CMD_RECEIVED_NOTIFICATION == STD_ON)
/**
****************************************************************************************************
Function is called when a XCP CMD is received
\param[in]  XcpCmd            Command pointer
\param[in]  Length            Command Length
\param[in]  ProtocolLayerId   Protocol layer id
\return     -
***************************************************************************************************/
void XcpAppl_CmdReceived(const uint8* XcpCmd, uint8 Length, uint8 ProtocolLayerId)
{
  XCP_PARAM_UNUSED(XcpCmd);
  XCP_PARAM_UNUSED(Length);
  XCP_PARAM_UNUSED(ProtocolLayerId);
  /* Indicate received command to rba_CalWup to reset timer */
  rba_CalWup_PendingRequest();
}
#endif /* (XCP_CMD_RECEIVED_NOTIFICATION == STD_ON) */



/***************************************************************************************************
* Xcp_Appl_Init.c_tpl filled out for MDG1
***************************************************************************************************/
#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
   || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)) )
/**
****************************************************************************************************
Function to do specific initialization or cancel pending background process
\param[in]  XcpInitStatus     Xcp Initialization status: XCP_INIT or XCP_UNINIT
\param[in]  ProtocolLayerId   protocol layer id
\return     Was initialization successful
\retval     E_OK              Initialization is finished
\retval     E_NOT_OK          Initialization is not finished, this function will be called
                              in next Xcp_MainFunction() again until it returns E_OK
***************************************************************************************************/
Std_ReturnType XcpAppl_Init(uint8 XcpInitStatus, uint8 ProtocolLayerId)
{
  /* Local variables */
  Std_ReturnType status;

  XCP_PARAM_UNUSED(XcpInitStatus);

  /* Disable CAL and STIM depending of EcuSecu EcuMode */
  XcpAppl_EcuSecuDisableCalStim();

  /* Call cancel function to cancel background action */
  if (rba_Dme_CancelBackgroundAction(XcpAppl_DmeUser[ProtocolLayerId]) == (uint32)RBA_DME_ST_FINISHED)
  {
    /* Assign as E_OK if cancelled successfully */
    status = E_OK;
  }
  else
  {
    /* Assign as E_NOT_OK if cancellation is still ongoing or busy */
    status = E_NOT_OK;
  }
#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
  /* Reset necessary variable */
  XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 = 0;
#endif

  return(status);
}
#endif



/***************************************************************************************************
* Xcp_MemoryReadWrite.c_tpl filled out for MDG1
***************************************************************************************************/
#if (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)
/**
****************************************************************************************************
Read data from source to destination
\param[in]  AddrPtrDst        destination address
\param[in]  AddrPtrSrc        source address
\param[in]  Length            length of the data to read
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR              All Ok, process finished successfully
\retval     XCP_NO_RESPONSE           Process started, but not finished
\retval     XCP_ERR_MEMORY_OVERFLOW   Memory overflow
\retval     XCP_ERR_ACCESS_DENIED     Access denied
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_MemRead(Xcp_AdrPtr AddrPtrDst, Xcp_AdrPtrConst AddrPtrSrc, uint8 Length, uint8 ProtocolLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;
  uint32 DmeStatus;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Read data by external function */
  /* MR12 RULE 11.4 VIOLATION: rba_Dme_Read wants as first param an uint32 (address) but not a pointer, so we have to cast, which is not a problem as addresses are also uint32 */
  DmeStatus = rba_Dme_Read((uint32)AddrPtrSrc, XcpAppl_Data[ProtocolLayerId].CalPage_u8, Length, AddrPtrDst, XcpAppl_DmeUser[ProtocolLayerId]);

  /* Check read operation status and convert to Xcp_ErrorCode */
  switch(DmeStatus)
  {
    case (uint32) RBA_DME_ST_FINISHED:
    {
      Error = XCP_NO_ERROR;
      break;
    }
    case (uint32) RBA_DME_ST_PAGE_NOT_VALID:
    {
      /* Set Error code. This error code is not available in ASAM for UPLOAD! */
      Error = XCP_ERR_PAGE_NOT_VALID;
      break;
    }
    case (uint32) RBA_DME_ST_REJECTED:
    {
      Error = XCP_ERR_CMD_BUSY;
      break;
    }
    case (uint32) RBA_DME_ST_BUSY:
    {
      Error = XCP_ERR_RES_TEMP_NOT_ACCESS;
      break;
    }
    default:
    {
      /* unknown return value from DME, set generic Error */
      Error = XCP_ERR_GENERIC;
      break;
    }
  }
  return(Error);
}


# if (XCP_CALIBRATION_CAL == STD_ON)
/**
****************************************************************************************************
Write data from source to destination
\param[in]  AddrPtrDst        destination address
\param[in]  AddrPtrSrc        source address
\param[in]  Length            length of the data to read
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR              All Ok, process finished successfully
\retval     XCP_NO_RESPONSE           Process started, but not finished
\retval     XCP_ERR_MEMORY_OVERFLOW   Memory overflow
\retval     XCP_ERR_ACCESS_DENIED     Access denied
***************************************************************************************************/
/* MR12 RULE 8.13 VIOLATION: AddrPtrDst cannot be const as the data is modified in rba_Dme_Write */
Xcp_ErrorCode XcpAppl_MemWrite(Xcp_AdrPtr AddrPtrDst, Xcp_AdrPtrConst AddrPtrSrc, uint8 Length, uint8 ProtocolLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;
  uint32 DmeStatus;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Write data by external function */
  /* MR12 RULE 11.4 VIOLATION: rba_Dme_Write wants as first param an uint32 (address) but not a pointer, so we have to cast, which is not a problem as addresses are also uint32;
                               the third argument needs to be a uint8-pointer, AddrPtrSrc is const - to avoid compiler-warning we cast to uint32 first */
  DmeStatus = rba_Dme_Write((uint32)AddrPtrDst, XcpAppl_Data[ProtocolLayerId].CalPage_u8, Length, (uint8*)((uint32)AddrPtrSrc), XcpAppl_DmeUser[ProtocolLayerId]);

  /* Check write operation status and convert to Xcp_ErrorCode */
  switch(DmeStatus)
  {
    case (uint32) RBA_DME_ST_FINISHED:
    {
      Error = XCP_NO_ERROR;
      break;
    }
    case (uint32) RBA_DME_ST_BUSY:
    {
      /* Request accepted, will be processed in background, do not send any response */
      Error = XCP_NO_RESPONSE;
      break;
    }
    case (uint32) RBA_DME_ST_OUT_OF_RAM:
    {
      Error = XCP_ERR_MEMORY_OVERFLOW;
      break;
    }
    case (uint32) RBA_DME_ST_PAGE_NOT_VALID:
    {
      /* Set Error code. This error code is not available in ASAM for DOWNLOAD! */
      Error = XCP_ERR_PAGE_NOT_VALID;
      break;
    }
    case (uint32) RBA_DME_ST_REJECTED:
    {
      Error = XCP_ERR_CMD_BUSY;
      break;
    }
    default:
    {
      Error = XCP_ERR_GENERIC;
      break;
    }
  }
  return(Error);
}


/**
****************************************************************************************************
Copy data from source to destination - background process
\param[in]  ProtocolLayerId   Protocol Layer Id
\retval     XCP_NO_ERROR              All Ok, process finished successfully
\retval     XCP_NO_RESPONSE           Process started, but not finished
\retval     XCP_ERR_MEMORY_OVERFLOW   Memory overflow
\retval     XCP_ERR_ACCESS_DENIED     Access denied
***************************************************************************************************/
Xcp_ErrorCode XcpAppl_MemWriteMainFunction(uint8 ProtocolLayerId)
{
  /* Local variables */
  Xcp_ErrorCode Error;
  uint32 DmeStatus;

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* command triggered to write */
  DmeStatus = rba_Dme_GetState(XcpAppl_DmeUser[ProtocolLayerId]);

  /* Check write operation status and convert to Xcp_ErrorCode */
  switch(DmeStatus)
  {
    case (uint32) RBA_DME_ST_FINISHED:
    {
      Error = XCP_NO_ERROR;
      break;
    }
    case (uint32) RBA_DME_ST_BUSY:
    {
      /* Request accepted, will be processed in background, do not send any response */
      Error = XCP_NO_RESPONSE;
      break;
    }
    case (uint32) RBA_DME_ST_OUT_OF_RAM:
    {
      Error = XCP_ERR_MEMORY_OVERFLOW;
      break;
    }
    case (uint32) RBA_DME_ST_IDLE:
    {
      Error = XCP_ERR_RES_TEMP_NOT_ACCESS;
      break;
    }
    default:
    {
      Error = XCP_ERR_GENERIC;
      break;
    }
  }
  return(Error);
}
# endif /* (XCP_CALIBRATION_CAL == STD_ON) */
#endif /* (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON) */



/***************************************************************************************************
* Xcp_Timestamp.c_tpl filled out for MDG1
***************************************************************************************************/
#if (XCP_TIMESTAMP == STD_ON)
/**
****************************************************************************************************
Function returns the current value of the synchronous data transfer clock (timestamp). The data
transfer clock is a free running counter, which is never reset or modified and wraps around if an
overflow occurs. Behaviour of timestamp shall be according to configured "Timestamp Ticks" and
"Timestamp Unit".
\param[in]  -
\return     Timestamp
***************************************************************************************************/

/* define the number of system timer ticks per configured timestamp tick */
/* system timer must have a time tick of less than 1us                   */
#if ((XCP_TIMESTAMP_TICKS * XCP_TIMESTAMP_UNIT) >= 1000000)
#define XCP_SYSTEMTIMER_TICKS            (MCU_RB_US_TO_TIM1TICKS((XCP_TIMESTAMP_TICKS * XCP_TIMESTAMP_UNIT)/1000000))
#else
#error "XCP timestamps below 1us are not supported by this implementation. Please change the XCP timestamp configuration"
#endif

uint32 XcpAppl_GetTimestamp(void)
{
  uint32 ctCurrentTicks_u32;
  uint32 ctModuloTicks_u32;

  /* Disable interrupts */
  SchM_Enter_Xcp_GetTimestamp();

  /* Get current timer value */
  ctCurrentTicks_u32 = Mcu_Rb_GetSysTimePart(TIM1);

  /* get the actual modulo counter */
  ctModuloTicks_u32  = XcpAppl_ModuloCounter_u32;

  /* add the difference to last timer value to the modulo counter */
  ctModuloTicks_u32 += (ctCurrentTicks_u32 - XcpAppl_LastCounter_u32);

  /* check if a new timestamp tick is counted */
  /* MR12 RULE 10.4, 14.3 VIOLATION: Rule 10.4 Casting from signed to unsigned here is not a problem as XCP_SYSTEMTIMER_TICKS > 0
                                     Rule 14.3 Macro contains the ternary operator raising this violation, it also depends on other config-parameters,
                                               so there are situations where the compare is required, thus it is left as it is */
  if(ctModuloTicks_u32 >= XCP_SYSTEMTIMER_TICKS)
  {
    /* add the number of timestamp ticks to the timestamp */
    /* MR12 RULE 10.4, 14.3 VIOLATION: Rule 10.4 Casting from signed to unsigned here is not a problem as XCP_SYSTEMTIMER_TICKS > 0
                                       Rule 14.3 Macro contains the ternary operator raising this violation, it also depends on other config-parameters,
                                                 so there are situations where the compare is required, thus it is left as it is */
    XcpAppl_Timestamp_u32  += (ctModuloTicks_u32 / XCP_SYSTEMTIMER_TICKS);

    /* calculate the new modulo */
    /* MR12 RULE 10.4, 14.3 VIOLATION: Rule 10.4 Casting from signed to unsigned here is not a problem as XCP_SYSTEMTIMER_TICKS > 0
                                       Rule 14.3 Macro contains the ternary operator raising this violation, it also depends on other config-parameters,
                                                 so there are situations where the compare is required, thus it is left as it is */
    ctModuloTicks_u32       = (ctModuloTicks_u32 % XCP_SYSTEMTIMER_TICKS);
  }

  /* Save current system timer value for next calculation */
  XcpAppl_LastCounter_u32   = ctCurrentTicks_u32;
  /* Save current modulo value for next calculation */
  XcpAppl_ModuloCounter_u32 = ctModuloTicks_u32;

  /* Enable interrupts */
  SchM_Exit_Xcp_GetTimestamp();

  return XcpAppl_Timestamp_u32;
}
#endif /* (XCP_TIMESTAMP == STD_ON) */



/***************************************************************************************************
* Local functions
***************************************************************************************************/
#if ( (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) \
   || ((XCP_CALIBRATION_CAL == STD_ON) && (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON)) )
/**
****************************************************************************************************
Function disables Cal and Stim feature depending of EcuSecu EcuMode
\param[in]  -
\return     -
***************************************************************************************************/
static void XcpAppl_EcuSecuDisableCalStim(void)
{
  /* Local variables */
  boolean DisableCalStim = TRUE;
  /* function pointer to GetEcuMode function of EcuSecu */
  rba_EcuSecu_EcuMode_GetEcuMode_tfct *getEcuMode_pfn = NULL_PTR;
  /* pointer to MemLay info tab entry */
  rba_MemLay_InfoTable_tst *infoTable_ptr = NULL_PTR;


  /* get info table pointer from Memlay to determine ECU state application resp. series */
  if (rba_MemLay_GetInfTabEntry(RBA_MEMLAY_IB_ECUSECUSRV0_SUBID, RBA_MEMLAY_ECUSECU_GETECUMODE, &infoTable_ptr) == (uint32)E_OK)
  {
    /* Get function pointer to GetEcuMode function of EcuSecu - cast between a pointer to function is needed */
    /* MR12 RULE 11.1 VIOLATION: Cast between a pointer to function is needed (CDG-MemLay-Demand) */
    getEcuMode_pfn = (rba_EcuSecu_EcuMode_GetEcuMode_tfct*) rba_MemLay_GetAddresPtrFromInfotableEntry(infoTable_ptr);

    if (getEcuMode_pfn != NULL_PTR)
    {
      /* call GetEcuMode function to determine ECU state application resp. series */
      /* NULL_PTR is used on purpose, according to EcuSecu doku this is supported */
      if (getEcuMode_pfn(NULL_PTR) == (uint32)RBA_ECUSECU_ECUMODE_APPLICATION_E)
      {
        /* ECU is in development mode -> nothing to do as XCP is per default active */
        DisableCalStim = FALSE;
      }
      else
      {
        /* ECU is in series mode -> CAL and STIM to be disabled if not already done */
        /* DisableCalStim = TRUE is set in beginning */
      }
    }
    else
    {
      /* Something went wrong, GetEcuMode function pointer could not be retrieved */
      /* DisableCalStim = TRUE is set in beginning */
    }
  }
  else
  {
    /* Something went wrong, pointer to memlay info table could not be retrieved */
    /* DisableCalStim = TRUE is set in beginning */
  }

  if (DisableCalStim != FALSE)
  {
    /* Disable CAL and STIM */

    /* Use of Xcp_SetControlMode not possible as we would get a recursion with the following path:
     * XcpAppl_Init -> XcpAppl_EcuSecuDisableCalStim.c -> Xcp_SetControlMode -> Xcp_Disconnect -> XcpAppl_Init */
    Xcp_GlobalNoInit.EnabledResources_u8 = (Xcp_GetControlMode() & ((uint8)~(XCP_RESOURCE_CALPAG|XCP_RESOURCE_STIM))) & XCP_RESOURCE_ENABLED;
  }
}
#endif

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

#endif  /* #if (XCP_PRODUCT_LINE == XCP_PRODUCT_LINE_MDG1) */


