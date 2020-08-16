
#ifndef BSWM_LINTP_H
#define BSWM_LINTP_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "ComStack_Types.h"
#include "BswM_Cfg_General.h"

#ifdef BSWM_LINTP_ENABLED
#if ( BSWM_LINTP_ENABLED == TRUE )

#include "LinIf.h"
#if (!defined(LINIF_AR_RELEASE_MAJOR_VERSION) || (LINIF_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(LINIF_AR_RELEASE_MINOR_VERSION) || (LINIF_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/
extern FUNC(void, BSWM_CODE) BswM_LinTp_RequestMode(VAR(NetworkHandleType, AUTOMATIC) Network, VAR(LinTp_Mode, AUTOMATIC) LinTpRequestedMode);

#endif /* ( BSWM_LINTP_ENABLED == TRUE )*/
#endif /* BSWM_LINTP_ENABLED */

#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
