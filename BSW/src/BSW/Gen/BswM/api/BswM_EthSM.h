
#ifndef BSWM_ETHSM_H
#define BSWM_ETHSM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "BswM_Cfg_General.h"

#if (defined(BSWM_ETHSM_ENABLED) && (BSWM_ETHSM_ENABLED == TRUE))

#include "EthSM.h"
#if (!defined(ETHSM_AR_RELEASE_MAJOR_VERSION) || (ETHSM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ETHSM_AR_RELEASE_MINOR_VERSION) || (ETHSM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

extern FUNC(void, BSWM_CODE) BswM_EthSM_CurrentState(VAR(NetworkHandleType, AUTOMATIC) Network, VAR(EthSM_NetworkModeStateType, AUTOMATIC) CurrentState);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif

#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
