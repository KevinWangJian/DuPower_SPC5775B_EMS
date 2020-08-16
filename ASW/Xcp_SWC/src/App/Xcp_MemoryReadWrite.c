
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"
#include "Xcp_Priv.h"
#include "Xcp_Integration.h"

/***************************************************************************************************
* Variables
***************************************************************************************************/


/***************************************************************************************************
* Functions
***************************************************************************************************/
/* ------------------------------------------------------------------------ */
/* Begin section for code */

#define XCP_START_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

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
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Remove when parameter used */
  //XCP_PARAM_UNUSED(AddrPtrDst);
  //XCP_PARAM_UNUSED(AddrPtrSrc);
  //XCP_PARAM_UNUSED(Length);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  Xcp_MemCopy(AddrPtrDst, AddrPtrSrc, Length);

  /* Return error code */
  return(XCP_NO_ERROR);
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
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Remove when parameter used */
  //XCP_PARAM_UNUSED(AddrPtrDst);
  //XCP_PARAM_UNUSED(AddrPtrSrc);
  //XCP_PARAM_UNUSED(Length);
  XCP_PARAM_UNUSED(ProtocolLayerId);

  Xcp_MemCopy(AddrPtrDst, AddrPtrSrc, Length);

  /* Return error code */
  return(XCP_NO_ERROR);
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
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(ProtocolLayerId);

  /* Return error code */
  return(XCP_NO_ERROR);
}
# endif /* (XCP_CALIBRATION_CAL == STD_ON) */
#endif /* (XCP_UPLOAD_DOWNLOAD_MEMORY_ACCESS_BY_APPL == STD_ON) */

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"


