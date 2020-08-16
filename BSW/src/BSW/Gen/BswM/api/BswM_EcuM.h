
#ifndef BSWM_ECUM_H
#define BSWM_ECUM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "BswM_Cfg_General.h"


#if (defined(BSWM_ECUM_ENABLED) && (BSWM_ECUM_ENABLED == TRUE))

#include "EcuM.h"
#if (!defined(ECUM_AR_RELEASE_MAJOR_VERSION) || (ECUM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ECUM_AR_RELEASE_MINOR_VERSION) || (ECUM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"
/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/
extern FUNC(void, BSWM_CODE) BswM_EcuM_CurrentState(VAR(EcuM_StateType, AUTOMATIC) CurrentState);
extern FUNC(void, BSWM_CODE) BswM_EcuM_CurrentWakeup(VAR(EcuM_WakeupSourceType, AUTOMATIC) source, VAR(EcuM_WakeupStatusType, AUTOMATIC) state);
extern FUNC(void, BSWM_CODE) BswM_EcuM_RequestedState(VAR(EcuM_StateType, AUTOMATIC) State, VAR(EcuM_RunStatusType, AUTOMATIC) CurrentStatus);


#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_ECUM_ENABLED */


#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
