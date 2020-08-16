
#ifndef  CANSM_CBK_H
#define  CANSM_CBK_H

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */

#include "CanSM_Cfg.h"
#include "CanIf.h"
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"

extern FUNC(void, CANSM_CODE) CanSM_ControllerBusOff(VAR(uint8, AUTOMATIC) ControllerId );

extern FUNC(void, CANSM_CODE) CanSM_ControllerModeIndication(VAR(uint8, AUTOMATIC) ControllerId,VAR(CanIf_ControllerModeType,AUTOMATIC) ControllerMode);

extern FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(VAR(uint8, AUTOMATIC) TransceiverId,VAR(CanTrcv_TrcvModeType,AUTOMATIC) TransceiverMode);

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
extern FUNC(void, CANSM_CODE) CanSM_ClearTrcvWufFlagIndication(VAR(uint8, AUTOMATIC) Transceiver);

extern FUNC(void, CANSM_CODE) CanSM_CheckTransceiverWakeFlagIndication(VAR(uint8, AUTOMATIC) Transceiver);

extern FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(VAR(uint8, AUTOMATIC) TransceiverId);
#endif

#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

#endif /*CANSM_CBK_H*/

