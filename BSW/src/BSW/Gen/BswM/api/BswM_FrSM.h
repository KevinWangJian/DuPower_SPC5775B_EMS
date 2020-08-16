
#ifndef BSWM_FRSM_H
#define BSWM_FRSM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "BswM_Cfg_General.h"

#if (defined(BSWM_FRSM_ENABLED) && (BSWM_FRSM_ENABLED == TRUE))

#include "FrSM.h"
#if (!defined(FRSM_AR_RELEASE_MAJOR_VERSION) || (FRSM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(FRSM_AR_RELEASE_MINOR_VERSION) || (FRSM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

extern FUNC(void, BSWM_CODE) BswM_FrSM_CurrentState(VAR(NetworkHandleType, AUTOMATIC) Network, VAR(FrSM_BswM_StateType, AUTOMATIC) CurrentState);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_FRSM_ENABLED */

#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
