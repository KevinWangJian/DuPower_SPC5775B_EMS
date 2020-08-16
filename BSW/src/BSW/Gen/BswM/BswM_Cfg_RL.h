#ifndef BSWM_CFG_RL_H
#define BSWM_CFG_RL_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "Std_Types.h"
#include "BswM_Cfg_General.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
 */

#define BSWM_MAX_NO_OF_RULES 30 

/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
 */

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
 */

#define BSWM_START_SEC_VAR_INIT_BOOLEAN
#include "BswM_Cfg_MemMap.h"

/* Valiable declaration to hold the status of actoin list*/
extern VAR(boolean, BSWM_VAR) BswM_isMultipleActionListTriggered_ab[BSWM_TOTAL_NO_OF_ACTIONLIST];

#define BSWM_STOP_SEC_VAR_INIT_BOOLEAN
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_VAR_INIT_8
#include "BswM_Cfg_MemMap.h"

/* Valiable declaration to hold the Rule State during runtime */
extern VAR(BswM_RuleStateType_ten, BSWM_VAR) BswM_Prv_RuleState_aen[BSWM_MAX_NO_OF_RULES];

#define BSWM_STOP_SEC_VAR_INIT_8
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"

/* Valiable declaration to hold the Deferred Rule Evaluation status */
extern VAR(boolean, BSWM_VAR) BswM_Prv_DeferredRuleEvaluation_b[BSWM_MAX_NO_OF_RULES];

#define BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
 */
#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif  /* BSWM_CFG_RL_H */
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
