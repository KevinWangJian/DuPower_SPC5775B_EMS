

/**
\defgroup COMM_DCM_H    COMM - AUTOSAR interfaces Upper Layer
*/

#ifndef COMM_DCM_H
#define COMM_DCM_H
/*
 ***************************************************************************************************
 * Include
 ***************************************************************************************************
 */
#include "ComM_Cfg.h"
#include "ComStack_Types.h"
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
 * @ingroup COMM_DCM_H
 *
 * This function Indicates active diagnostic by the DCM  \n
 *
 *  @param  In:      Channel - This parameter indicates Channel needed for Diagnostic communication \n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel);

/**
 * @ingroup COMM_DCM_H
 *
 * This function Indicates Inactive diagnostic by the DCM  \n
 *
 *  @param  In:      Channel - This parameter indicates Channel no longer needed for Diagnostic communication \n
 *
 *  @return None \n
 */
extern FUNC(void,COMM_CODE) ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel);

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /*COMM_DCM_H*/

