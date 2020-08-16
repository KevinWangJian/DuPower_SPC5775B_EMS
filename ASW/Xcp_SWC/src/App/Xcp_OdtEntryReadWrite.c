
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"


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

#if (XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL == STD_ON)
/**
****************************************************************************************************
Copy the DAQ data from ecu memory to the destination buffer
\param[in]  AddrPtrDst  destination address
\param[in]  AddrPtrSrc  source address
\param[in]  Length      length of the data to read
\return     -
***************************************************************************************************/
void XcpAppl_OdtEntryRead(Xcp_AdrPtr AddrPtrDst, Xcp_AdrPtrConst AddrPtrSrc, uint8 Length)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(AddrPtrDst);
  XCP_PARAM_UNUSED(AddrPtrSrc);
  XCP_PARAM_UNUSED(Length);
}


# if (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON)
/**
****************************************************************************************************
Copy the STIM data from internal buffer to ecu memory
\param[in]  AddrPtrDst  destination address
\param[in]  AddrPtrSrc  source address
\param[in]  Length      length of the data to read
\return     -
***************************************************************************************************/
/* MR12 RULE 8.13 VIOLATION: AddrPtrDst cannot be const as the data is modified */
void XcpAppl_OdtEntryWrite(Xcp_AdrPtr AddrPtrDst, Xcp_AdrPtrConst AddrPtrSrc, uint8 Length)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /*-----------------------------------------------------------------*/

  /* Remove when parameter used */
  XCP_PARAM_UNUSED(AddrPtrDst);
  XCP_PARAM_UNUSED(AddrPtrSrc);
  XCP_PARAM_UNUSED(Length);
}

# endif /* (XCP_SYNCHRONOUS_DATA_STIMULATION_STIM == STD_ON) */
#endif /* (XCP_DAQ_STIM_MEMORY_ACCESS_BY_APPL == STD_ON) */

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"

