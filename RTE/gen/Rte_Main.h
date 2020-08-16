/** @file         Rte_Main.h
  *
  * @brief        RTE/BSW Scheduler lifecycle definitions
  *
  * @copyright    Copyright 2007-2008 ETAS Engineering Tools Application and Services Ltd.
  *               Copyright 2008-2016 ETAS GmbH.
  *
  * @note         PLATFORM DEPENDENT [yes/no]: no
  *
  * @note         TO BE CHANGED BY USER [yes/no]: no
  *
  * Template:     Id: Rte_Main_h.template 54608 2016-06-01 16:39:45Z ren1yok
  */

#ifndef RTEMAIN_H
#define RTEMAIN_H

#include "Rte.h"  /* [$Satisfies $SWS 1159] */

#define RTE_START_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */

/* BEGIN: RTE Lifecycle API */

extern FUNC(Std_ReturnType, RTE_CODE) Rte_Start(void);
extern FUNC(Std_ReturnType, RTE_CODE) Rte_Stop(void);

extern FUNC(void, RTE_CODE) Rte_MainFunction(void);

/* END: RTE Lifecycle API */

/* BEGIN: BSW Scheduler Lifecycle API */

/* [$Satisfies $SWS40 7270] [$Satisfies $SWS40 6544] [$Satisfies $SWS40 6545] */
extern FUNC(void, RTE_CODE) SchM_Init( void );

/* [$Satisfies $SWS40 7274] */
extern FUNC(void, RTE_CODE) SchM_Deinit(void);

/* END: BSW Scheduler Lifecycle API */

#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h" /*lint !e537 permit multiple inclusion */


#endif /* RTEMAIN_H */

