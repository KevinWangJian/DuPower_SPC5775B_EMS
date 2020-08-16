
#ifndef BSWM_DCM_H
#define BSWM_DCM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "BswM_Cfg_General.h"

#if (defined(BSWM_DCM_ENABLED) && (BSWM_DCM_ENABLED == TRUE))

#include "Dcm.h"
#if (!defined(DCM_AR_RELEASE_MAJOR_VERSION) || (DCM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DCM_AR_RELEASE_MINOR_VERSION) || (DCM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif
/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

extern FUNC(void, BSWM_CODE) BswM_Dcm_ApplicationUpdated(void);
extern FUNC(void, BSWM_CODE) BswM_Dcm_CommunicationMode_CurrentState(VAR(NetworkHandleType, AUTOMATIC) Network, VAR(Dcm_CommunicationModeType, AUTOMATIC) RequestedMode);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_DCM_ENABLED */

#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
