

/**
\defgroup COMM_BUSSM_H    COMM - AUTOSAR interfaces Upper Layer
*/
#ifndef COMM_BUSSM_H
#define COMM_BUSSM_H
/*
 ***************************************************************************************************
 * Include
 ***************************************************************************************************
 */
#include "ComStack_Types.h"
#include "Rte_ComM_Type.h"
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
/**
 * @ingroup COMM_BUSSM_H
 *
 *  This function is used to Indicate the actual bus mode by the corresponding Bus State Manager. \n
 *
 *  @param  In:      Channel- Handle to identify a communication channel \n
 *  @param  In:      ComMode - communication mode\n
 *
 *  @return None \n
 */

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

extern FUNC(void,COMM_CODE) ComM_BusSM_ModeIndication
                                        (
                                            VAR(NetworkHandleType,AUTOMATIC ) Channel,
                                            P2VAR(ComM_ModeType,AUTOMATIC,COMM_APPL_DATA) ComMode
                                        );

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /*COMM_BUSSM_H*/

