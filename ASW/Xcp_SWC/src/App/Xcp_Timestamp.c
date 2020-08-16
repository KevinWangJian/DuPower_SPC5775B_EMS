
/***************************************************************************************************
* Includes
***************************************************************************************************/
#include "Xcp_Cbk.h"
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
uint32 XcpAppl_GetTimestamp(void)
{
  /*-----------------------------------------------------------------*/
  /* This function is project specific and shall be totally reworked */
  /* Example for calculating the timestamp                           */
  /*-----------------------------------------------------------------*/

  static uint32 XcpAppl_Timestamp_u32;
  static uint32 XcpAppl_PreviousTime_u32;
  uint32 XcpAppl_CurrentTime_u32;

  /* Disable interrupts */
  /* Call function here... */

  /* Get current timer value */
  XcpAppl_CurrentTime_u32 = Xcp_GetTimeStamp();   /* Call function to get time */

  /* Calculate time elapsed since last read of timer value and add it to actual timestamp */
  XcpAppl_Timestamp_u32 += (XcpAppl_CurrentTime_u32 - XcpAppl_PreviousTime_u32);    /* Multiply or divide to fit configured "Timestamp Ticks" and "Timestamp Unit" */

  /* Save current timer value */
  XcpAppl_PreviousTime_u32 = XcpAppl_CurrentTime_u32;

  /* Enable interrupts */
  /* Call function here... */

  return XcpAppl_Timestamp_u32;
}
#endif /* (XCP_TIMESTAMP == STD_ON) */

/* ------------------------------------------------------------------------ */
/* End section for code */

#define XCP_STOP_SEC_CALLOUT_CODE
#include "Xcp_MemMap.h"


