
#ifndef BSWM_COMM_H
#define BSWM_COMM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "BswM_Cfg_General.h"

#if (defined(BSWM_COMM_ENABLED) && (BSWM_COMM_ENABLED == TRUE))

#include "ComM.h"
#if (!defined(COMM_AR_RELEASE_MAJOR_VERSION) || (COMM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMM_AR_RELEASE_MINOR_VERSION) || (COMM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif


/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

extern FUNC(void, BSWM_CODE) BswM_ComM_InitiateReset(void);
extern FUNC(void, BSWM_CODE) BswM_ComM_CurrentMode (VAR(NetworkHandleType, AUTOMATIC) Network, VAR(ComM_ModeType, AUTOMATIC) RequestedMode);
extern FUNC(void, BSWM_CODE) BswM_ComM_CurrentPNCMode(VAR(PNCHandleType, AUTOMATIC) PNC, VAR(ComM_PncModeType, AUTOMATIC) CurrentPncMode);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_COMM_ENABLED */

#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
