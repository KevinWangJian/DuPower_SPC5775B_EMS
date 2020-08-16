

#ifndef BSWM_ETHIF_H
#define BSWM_ETHIF_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "BswM_Cfg_General.h"

#if (defined(BSWM_ETHIF_ENABLED) && (BSWM_ETHIF_ENABLED == TRUE))

#include "EthIf.h"
#if (!defined(ETHIF_AR_RELEASE_MAJOR_VERSION) || (ETHIF_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(ETHIF_AR_RELEASE_MINOR_VERSION) || (ETHIF_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#define BSWM_START_SEC_CODE
#include "BswM_Cfg_MemMap.h"
/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/
extern FUNC(void, BSWM_CODE) BswM_EthIf_PortGroupLinkStateChg( VAR (EthIf_SwitchPortGroupIdxType, AUTOMATIC )PortGroupIdx, VAR (EthTrcv_LinkStateType, AUTOMATIC) PortGroupState);

#define BSWM_STOP_SEC_CODE
#include "BswM_Cfg_MemMap.h"

#endif /* BSWM_ETHIF_ENABLED */

#endif /* BSWM_ETHIF_H */
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
