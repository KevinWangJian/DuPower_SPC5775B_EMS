
#ifndef BSWM_PRV_AC_H
#define BSWM_PRV_AC_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

#define BSWM_NO_RET_VALUE                          0x03
/*
 **********************************************************************************************************************
 * Type definitions
 **********************************************************************************************************************
*/
typedef FUNC(void, BSWM_CODE) (*BswM_Action_FuncPtr_t) ( P2VAR(Std_ReturnType, AUTOMATIC, BSWM_VAR)action_RetVal_pu8 , P2CONST(void, AUTOMATIC, BSWM_APPL_CONST)dataActionParameter_pv);

/*
 **********************************************************************************************************************
 * Variables
 **********************************************************************************************************************
*/
#define BSWM_START_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

#if (defined(BSWM_NO_OF_AC_DEADLINE_MONITOR_CNTRL) && (BSWM_NO_OF_AC_DEADLINE_MONITOR_CNTRL > 0))

extern VAR(boolean, BSWM_VAR) BswM_AC_DeadlineMonitoring_ExecFlag_b;
extern VAR(Com_IpduGroupVector, BSWM_VAR) BswM_AC_DeadlineMonitoring_IpduGroup;

#endif

#define BSWM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "BswM_Cfg_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

extern FUNC(Std_ReturnType, BSWM_CODE) BswM_Prv_Evaluate_Action(P2CONST(void, AUTOMATIC, BSWM_APPL_CONST) dataActionParameter_pv, VAR(BswM_ActionListItemType_ten, AUTOMATIC) isActionType_en);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_H */
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
