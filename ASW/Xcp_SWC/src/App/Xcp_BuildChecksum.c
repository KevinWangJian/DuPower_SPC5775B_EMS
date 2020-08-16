
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"
#include "Xcp_Integration.h"


/***************************************************************************************************
* Variables
***************************************************************************************************/
#define XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Xcp_MemMap.h"

#if (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON)
/*-------------------------------------------------------------*/
/* This part is project specific and shall be totally reworked */
/*-------------------------------------------------------------*/

/** Maximum size of block which can be used for checksum calculation at once.
    If the requested block size is bigger it will be splitted into parts with defined size */
#define XCPAPPL_CHECKSUM_BLOCKSIZE_SPLIT (uint32)1024

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


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

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
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /* In case of no use of CalPage this code template can be used.    */
  /* This is fully working CRC32 example without CalPage.            */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  Xcp_ErrorCode Error;

  /* Check if not another calculation in progress */
  if (XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 == 0u)
  {
    /* Initial value for checksum calculation */
    XcpAppl_BuildChecksumData[ProtocolLayerId].ChecksumValue = 0;

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
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /* In case of no use of CalPage this code template can be used.    */
  /* This is fully working ADD_14 example without CalPage.            */
  /*-----------------------------------------------------------------*/

  /* Local variables */
  Xcp_ErrorCode Error;
  uint32 CalcLength;
  uint32 CalcChecksum;
  uint32 byteidx;
  const uint8* byteptr;

  /* Check if calculation in progress - also checked in Xcp_BuildChecksumMainFunction */
  if (XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 > 0u)
  {
    /* Check if requested size is bigger than maximum block size which can be calculated at once */
    if (XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 > XCPAPPL_CHECKSUM_BLOCKSIZE_SPLIT)
    {
      /* Set block length for actual calculation */
      CalcLength = XCPAPPL_CHECKSUM_BLOCKSIZE_SPLIT;

      /* Calculation in progress */
      Error = XCP_NO_RESPONSE;
    }
    else
    {
      /* Set block length for actual calculation */
      CalcLength = XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32;

      /* Calculation done */
      Error = XCP_NO_ERROR;
    }

    CalcChecksum = 0;
    byteptr =  XcpAppl_BuildChecksumData[ProtocolLayerId].AddrPtr;

    for (byteidx = 0; byteidx < CalcLength; byteidx++)
    {
      CalcChecksum += byteptr[byteidx];
    }

    /* Calculate ADD_14 checksum */
    XcpAppl_BuildChecksumData[ProtocolLayerId].ChecksumValue = CalcChecksum;

    /* Update address and block size */
    XcpAppl_BuildChecksumData[ProtocolLayerId].BlockSize_u32 -= CalcLength;
    XcpAppl_BuildChecksumData[ProtocolLayerId].AddrPtr += CalcLength;

    /* Set type of checksum to return parameter */
    *ChecksumType = XCP_CHECKSUM_TYPE_ADD_14;

    /* Set value of checksum to return parameter */
    *ChecksumPtr = XcpAppl_BuildChecksumData[ProtocolLayerId].ChecksumValue;
  }
  else
  {
    Error = XCP_ERR_RES_TEMP_NOT_ACCESS;
  }
  return(Error);
}
#endif /* (XCP_CMD_BUILD_CHECKSUM_AVAILABLE == STD_ON) */

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"


