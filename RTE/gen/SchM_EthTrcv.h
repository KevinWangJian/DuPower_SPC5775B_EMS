/*
 * SchM_EthTrcv.h
 *
 *  Created on: 2019Äê12ÔÂ9ÈÕ
 *      Author: TC
 */

#ifndef SCHM_ETHTRCV_H_
#define SCHM_ETHTRCV_H_

//#include "SchM_CanSM_Type.h"
#include "Rte_Intl.h"
#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#if defined(RTE_RUNNABLEAPI_BSWSE_MainFunction)
   /* Do nothing for this and all elif clauses below (rte_sws_2751) */
#else
   /* None of above defined so define value including all APIs (rte_sws_2751) */
   #define RTE_PRV_ALL_API
#endif

/* API Mapping Macros */
#ifndef RTE_CORE

#endif /* RTE_CORE */

/*******************************************************
 ***
 *** Schedulable Entity Prototypes
 ***
 *******************************************************/

#define ETHTRCV_START_SEC_CODE
#include "EthTrcv_MemMap.h" /*lint !e537 permit multiple inclusion */
FUNC(void, ETHTRCV_CODE) EthTrcv_MainFunction(void);
#define ETHTRCV_STOP_SEC_CODE
#include "EthTrcv_MemMap.h" /*lint !e537 permit multiple inclusion */

#ifdef __cplusplus
} /* extern C */
#endif /* __cplusplus */


#endif /* RTE_GEN_SCHM_ETHTRCV_H_ */
