
#ifndef BSWM_NM_H
#define BSWM_NM_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "ComStack_Types.h"
#include "BswM_Cfg_General.h"

#ifdef BSWM_NM_ENABLED
#if ( BSWM_NM_ENABLED == TRUE )

#include "Nm.h"
#if (!defined(NM_AR_RELEASE_MAJOR_VERSION) || (NM_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(NM_AR_RELEASE_MINOR_VERSION) || (NM_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"

/* Function called by NmIf to indicate a CarWakeup. */
extern FUNC(void, BSWM_CODE) BswM_NmIf_CarWakeUpIndication( VAR(NetworkHandleType, AUTOMATIC) Network );

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* ( BSWM_NM_ENABLED == TRUE ) */
#endif /* BSWM_NM_ENABLED */

#endif /* BSWM_NM_H */

/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/

