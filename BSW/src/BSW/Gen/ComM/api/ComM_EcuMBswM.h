

/**
\defgroup COMM_ECUMBSWM_H    COMM - AUTOSAR interfaces Upper Layer
*/
#ifndef COMM_ECUMBSWM_H
#define COMM_ECUMBSWM_H

#include "ComStack_Types.h"
#include "ComM_Cfg.h"

/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/*
 ***************************************************************************************************
 * Extern declarations
 ***************************************************************************************************
 */

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/**
 * @ingroup COMM_ECUMBSWM_H
 *
 * This function indicates the Notification of a wake up on the corresponding channel. \n
 *
 *  @param  In:      Channel- This parameter indicates Channel needed for wakeup indication   \n
 *
 *  @return None \n
 */
extern FUNC (void,COMM_CODE) ComM_EcuM_WakeUpIndication
(
        VAR(NetworkHandleType,AUTOMATIC) Channel
);


/**
 * @ingroup COMM_ECUMBSWM_H
 *
 * This function indicates the Notification of a wake up on the corresponding channel. \n
 *
 *  @param  In:      PNCid- This parameter indicates PNC needed for wakeup indication   \n
 *
 *  @return None \n
 */
extern FUNC (void,COMM_CODE) ComM_EcuM_PNCWakeUpIndication
                                            (
                                            VAR(PNCHandleType,AUTOMATIC) PNCid
                                            );
/**
 * @ingroup COMM_ECUMBSWM_H
 *
 * EcuM or BswM shall indicate to ComM when communication is allowed. \n
 *
 *  @param  In:      Channel- This parameter indicates Channel needed for CommunicationAllowed   \n
 *  @param  In:      Allowed- TRUE: Communication is allowed \n
 *                            FALSE: Communication is not allowed \n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_CommunicationAllowed
(
        VAR(NetworkHandleType,AUTOMATIC) Channel,
        VAR(boolean,AUTOMATIC) Allowed
);

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /*COMM_ECUMBSWM_H*/

