
#ifndef BSWM_CANSM_H
#define BSWM_CANSM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "BswM_Cfg_General.h"

#if (defined(BSWM_CANSM_ENABLED) && (BSWM_CANSM_ENABLED == TRUE))

#include "CanSM_BswM.h"
#if (!defined(CANSM_AR_RELEASE_MAJOR_VERSION) || (CANSM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(CANSM_AR_RELEASE_MINOR_VERSION) || (CANSM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

extern FUNC(void, BSWM_CODE) BswM_CanSM_CurrentState(VAR(NetworkHandleType, AUTOMATIC) Network, VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CurrentState);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_CANSM_ENABLED */

#endif /* BSWM_CANSM_H */
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
