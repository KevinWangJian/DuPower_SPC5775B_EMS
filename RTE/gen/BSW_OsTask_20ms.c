/** @file     BSW_OsTask_20ms.c
  *
  * @brief    Task BSW_OsTask_20ms body
  *
  * @note     AUTOMATICALLY GENERATED FILE! DO NOT EDIT!
  *
  * @note     Generated by ETAS RTA-RTE
  * @note     Version 6.4.1 
  */

#define RTE_CORE

#include "Rte_Const.h"
#if !defined(RTE_VENDOR_MODE)
#pragma message "Compiling an individual task file but RTE_VENDOR_MODE not defined. Compiling a stale file?"
#endif /* !defined(RTE_VENDOR_MODE) */
#if defined(RTE_USE_TASK_HEADER)
#include "BSW_OsTask_20ms.h"
#else /* !defined(RTE_USE_TASK_HEADER) */
#include "Os.h"
#endif /* !defined(RTE_USE_TASK_HEADER) */
#if defined(RTE_REQUIRES_IOC)
#include "Ioc.h"
#endif /* defined(RTE_REQUIRES_IOC) */
#include "Rte.h"
#include "Rte_Intl.h"
#include "Rte_Type.h"
#include "Rte_DataHandleType.h"

/* Runnable entity prototypes */
#define WdgM_SWC_START_SEC_CODE
#include "WdgM_SWC_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(void, WdgM_SWC_CODE) WdgMSwc_CheckpointReached_Bsw_20ms(void);
#define WdgM_SWC_STOP_SEC_CODE
#include "WdgM_SWC_MemMap.h" /*lint !e537 permit multiple inclusion */
#define XCP_START_SEC_CODE
#include "Xcp_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(void, XCP_CODE) Xcp_EventChannel_20msRstr(void);
#define XCP_STOP_SEC_CODE
#include "Xcp_MemMap.h" /*lint !e537 permit multiple inclusion */

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */
TASK(BSW_OsTask_20ms)
{
   /* Box: Implicit Buffer Initialization begin */
   /* Box: Implicit Buffer Initialization end */
   /* Box: Implicit Buffer Fill begin */
   /* Box: Implicit Buffer Fill end */
   {
      /* Box: CPT_WdgM_SWC begin */
//      WdgMSwc_CheckpointReached_Bsw_20ms();
      /* Box: CPT_WdgM_SWC end */
   }
   {
      /* Box: BSWImpl8_Xcp begin */
      Xcp_EventChannel_20msRstr();
      /* Box: BSWImpl8_Xcp end */
   }
   /* Box: Implicit Buffer Flush begin */
   /* Box: Implicit Buffer Flush end */
   TerminateTask();
} /* BSW_OsTask_20ms */
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

