
#ifndef BSWM_NVM_H
#define BSWM_NVM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "BswM_Cfg_General.h"

#ifdef BSWM_NVM_ENABLED
#if ( BSWM_NVM_ENABLED == TRUE )

#include "NvM.h"
#if (!defined(NVM_AR_RELEASE_MAJOR_VERSION) || (NVM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(NVM_AR_RELEASE_MINOR_VERSION) || (NVM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/
extern FUNC(void, BSWM_CODE) BswM_NvM_CurrentBlockMode(VAR(NvM_BlockIdType, AUTOMATIC) Block, VAR(NvM_RequestResultType, AUTOMATIC) CurrentBlockMode);
extern FUNC(void, BSWM_CODE) BswM_NvM_CurrentJobMode(VAR(uint8, AUTOMATIC) ServiceId, VAR(NvM_RequestResultType, AUTOMATIC) CurrentJobMode);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_NVM_ENABLED == TRUE ) */
#endif /* BSWM_NVM_ENABLED */

#endif /* BSWM_NVM_H */
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
