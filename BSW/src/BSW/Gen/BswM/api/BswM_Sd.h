
#ifndef BSWM_SD_H
#define BSWM_SD_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "Std_Types.h"
#include "BswM_Cfg_General.h"

#ifdef BSWM_SD_ENABLED
#if (BSWM_SD_ENABLED == TRUE)

#include "Sd.h"
#if (!defined(SD_AR_RELEASE_MAJOR_VERSION) || (SD_AR_RELEASE_MAJOR_VERSION != BSWM_AR_RELEASE_MAJOR_VERSION))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(SD_AR_RELEASE_MINOR_VERSION) || (SD_AR_RELEASE_MINOR_VERSION != BSWM_AR_RELEASE_MINOR_VERSION))
#error "AUTOSAR minor version undefined or mismatched"
#endif


/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/
extern FUNC(void, BSWM_CODE) BswM_Sd_EventHandlerCurrentState(VAR(uint16, AUTOMATIC) SdEventHandlerHandleId, VAR(Sd_EventHandlerCurrentStateType, AUTOMATIC) EventHandlerStatus);
extern FUNC(void, BSWM_CODE) BswM_Sd_ClientServiceCurrentState(VAR(uint16, AUTOMATIC) SdClientServiceHandleId, VAR(Sd_ClientServiceCurrentStateType, AUTOMATIC) CurrentClientState);
extern FUNC(void, BSWM_CODE) BswM_Sd_ConsumedEventGroupCurrentState(VAR(uint16, AUTOMATIC) SdConsumedEventGroupHandleId, VAR(Sd_ConsumedEventGroupCurrentStateType, AUTOMATIC) ConsumedEventGroupState);


#endif //BSWM_SD_ENABLED == TRUE
#endif //BSWM_SD_ENABLED


#endif
/**********************************************************************************************************************
 * End of header file
 **********************************************************************************************************************/
