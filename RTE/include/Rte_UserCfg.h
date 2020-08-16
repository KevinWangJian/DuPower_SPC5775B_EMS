/** \file         Rte_UserCfg.h
  *
  * \brief        RTE user configuration header file
  *
  * [$crn:2007:dox 
  * \copyright Copyright 2007 - 2008 ETAS Engineering Tools Application and Services Ltd.
  *            Copyright 2008 ETAS GmbH.
  * $]
  *
  * \note         Implemented SWS: N/A
  *
  * \note         PLATFORM DEPENDANT [yes/no]: no
  *
  * \note         TO BE CHANGED BY USER [yes/no]: yes
  *
  * $Id: Rte_UserCfg.h 13 2017-12-07 10:38:02Z CIX2SGH $
  */

#ifndef RTE_USERCFG_H
#define RTE_USERCFG_H

//#include "Fls.h"
#include "Compiler.h"
//#define Fls_MainFunction(a)	Fls_17_Pmu_MainFunction(a)
#define RTE_START_SEC_CODE
#include "Rte_MemMap.h"
extern FUNC(void, RTE_CODE) SchM_IModeInit(void);	/*fix MISRA C:2012 Rule-17.3; REFERENCE - ISO:C90-6.3.2.2 Function Calls - Semantics */
#define RTE_STOP_SEC_CODE
#include "Rte_MemMap.h"
#endif /* RTE_USERCFG_H */
