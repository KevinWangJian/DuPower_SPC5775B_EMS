

#ifndef ECUM_CBK_H
#define ECUM_CBK_H

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/

#include "Std_Types.h" /*Rule BSW_HeaderInc_004:*/

#include "EcuM_Types.h" /* Required for EcuM exported data types */

#include "EcuM_Generated_Types.h" /* specified in SWS. */

#include "EcuM_Cfg_Version.h" /*Version details for the implementation*/

/**************************************************************************************************/
/* ALL DECLARATIONS NECESSARY TO INTERACT WITH CALLBACKS AND CALLOUTS OF ECUM MODULE                                                                          */
/**************************************************************************************************/

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

/*************************************************************************************************
 CALLBACK FUNCTION PROTOTYPES
*************************************************************************************************/

extern FUNC( void, ECUM_CODE ) EcuM_SetWakeupEvent( VAR(EcuM_WakeupSourceType, AUTOMATIC) sources );

extern FUNC( void, ECUM_CODE ) EcuM_ValidateWakeupEvent( VAR(EcuM_WakeupSourceType, AUTOMATIC) sources );

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_CheckWakeup( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource );

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

#endif /*ECUM_CBK_H*/

