
#ifndef  CANSM_TXTIMEOUTEXCEPTION_H
#define  CANSM_TXTIMEOUTEXCEPTION_H

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Cfg.h"
#include "ComM.h"
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
extern FUNC(void, CANSM_CODE) CanSM_TxTimeoutException(VAR(NetworkHandleType, AUTOMATIC) Channel);
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

#endif /*CANSM_TXTIMEOUTEXCEPTION_H*/
