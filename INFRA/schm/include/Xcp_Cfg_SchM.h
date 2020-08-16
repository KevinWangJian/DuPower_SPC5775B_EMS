/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */



#ifndef XCP_CFG_SCHM_H
#define XCP_CFG_SCHM_H

// ---- Includes --------------------------------------------------------------
#include "SchM.h"
#include "SchM_Default.h"

/* If the RTE code generation is Involved please include the below file */
//#include "SchM_Xcp.h"

#ifndef XCP_CODE
  #define XCP_CODE
#endif

// The integrator shall implement the particular services SchM_Enter and SchM_Exit.

// Since there is currently only one resource used (XCP_RESOURCE), there is no need to consider the resource name


//      standard handling is required here
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_SendingShort(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_SendingShort(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_SendingLong(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_SendingLong(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_DownloadNoNest(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_DownloadNoNest(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_BufferAccessActiveNoNest(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_BufferAccessActiveNoNest(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_EthMainFunc(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_EthMainFunc(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_CanBuffering(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_CanBuffering(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_FrTransmit(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_FrTransmit(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_GetTimestamp(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_GetTimestamp(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_DaqRam(void);
LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_DaqRam(void);

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_SendingShort(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
  /* either fill Xcp_SendingShort OR Xcp_SendingLong */
  /* Xcp_SendingShort is for systems where only very short locks are allowed */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_SendingShort(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
  /* either fill Xcp_SendingShort OR Xcp_SendingLong*/
  /* Xcp_SendingShort is for systems where only very short locks are allowed */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_SendingLong(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
  /* either fill Xcp_SendingShort OR Xcp_SendingLong */
  /* Xcp_SendingLong is for systems where longer locks are allowed */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_SendingLong(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
  /* either fill Xcp_SendingShort OR Xcp_SendingLong */
  /* Xcp_SendingLong is for systems where longer locks are allowed */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_DownloadNoNest(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_DownloadNoNest(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_BufferAccessActiveNoNest(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_BufferAccessActiveNoNest(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_EthMainFunc(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_EthMainFunc(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_CanBuffering(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_CanBuffering(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_FrTransmit(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_FrTransmit(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_GetTimestamp(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_GetTimestamp(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Enter_Xcp_DaqRam(void)
{
  SCHM_ENTER_DEFAULT();
  /* integrator shall place his code for locking/disabling the interrupt */
}

LOCAL_INLINE FUNC(void, XCP_CODE) SchM_Exit_Xcp_DaqRam(void)
{
  SCHM_EXIT_DEFAULT();
  /* integrator shall place his code for unlocking/enabling the interrupt */
}


#endif /* XCP_CFG_SCHM_H */

// -------- END OF FILE -------------------------------------------------------

