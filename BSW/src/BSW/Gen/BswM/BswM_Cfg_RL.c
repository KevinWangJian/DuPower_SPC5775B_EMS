
/*---------------------------------------------------------------------------------------*/
/*- Include files                                                                       -*/
/*---------------------------------------------------------------------------------------*/
#include "BswM.h"
#include "BswM_Prv.h"

#define BSWM_START_SEC_VAR_INIT_BOOLEAN
#include "BswM_Cfg_MemMap.h"

VAR(boolean, BSWM_VAR) BswM_isMultipleActionListTriggered_ab[BSWM_TOTAL_NO_OF_ACTIONLIST] =
{
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE
};

#define BSWM_STOP_SEC_VAR_INIT_BOOLEAN
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_VAR_INIT_8
#include "BswM_Cfg_MemMap.h"

/* Valiable declaration to hold the Rule State during runtime */
VAR(BswM_RuleStateType_ten, BSWM_VAR) BswM_Prv_RuleState_aen[BSWM_MAX_NO_OF_RULES]=
{
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED,
	BSWM_UNDEFINED
};

#define BSWM_STOP_SEC_VAR_INIT_8
#include "BswM_Cfg_MemMap.h"

#define BSWM_START_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"

/* Valiable declaration to hold the Deferred Rule Evaluation status */
VAR(boolean, BSWM_VAR) BswM_Prv_DeferredRuleEvaluation_b[BSWM_MAX_NO_OF_RULES]=
{
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE,
	FALSE
};

#define BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "BswM_Cfg_MemMap.h"

/**********************************************************************************************************************
 *																										
 **********************************************************************************************************************/
