


#ifndef ECUM_CALLOUT_H
#define ECUM_CALLOUT_H

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "EcuM_Cfg_Startup.h" /* Required for EcuM post build structures */

/**************************************************************************************************/
/* ALL DECLARATIONS NECESSARY TO INTERACT WITH CALLBACKS AND CALLOUTS OF ECUM MODULE                                                                          */
/**************************************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.h"

/*************************************************************************************************
 CALLOUT FUNCTION PROTOTYPES
*************************************************************************************************/

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_ErrorHook( VAR(uint16, AUTOMATIC) reason );

extern FUNC( void , ECUM_CALLOUT_CODE ) EcuM_AL_SetProgrammableInterrupts( void );

extern FUNC( void , ECUM_CALLOUT_CODE ) EcuM_AL_DriverInitZero( void );

extern FUNC( void , ECUM_CALLOUT_CODE ) EcuM_AL_DriverInitOne(
                                        P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_APPL_CONST) ConfigPtr );


#if ECUM_SLEEP_SUPPORT_ENABLE

extern FUNC (void , ECUM_CALLOUT_CODE ) EcuM_AL_DriverRestart ( 
                                        P2CONST(EcuM_ConfigType, AUTOMATIC, ECUM_APPL_CONST) ConfigPtr );

#endif//ECUM_SLEEP_SUPPORT_ENABLE

extern FUNC_P2CONST( EcuM_ConfigType , AUTOMATIC, ECUM_CALLOUT_CODE ) EcuM_DeterminePbConfiguration( void );

extern FUNC( void , ECUM_CALLOUT_CODE ) EcuM_OnGoOffOne( void );

extern FUNC( void , ECUM_CALLOUT_CODE ) EcuM_OnGoOffTwo( void );

extern FUNC( void , ECUM_CALLOUT_CODE ) EcuM_AL_SwitchOff( void );

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_AL_Reset( VAR(EcuM_ResetType, AUTOMATIC) reset );

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_StartWakeupSources( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource );

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_StopWakeupSources( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource );

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_CheckValidation( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource );

extern FUNC( void , ECUM_CALLOUT_CODE ) EcuM_SwitchOsAppMode( void );

#if ECUM_SLEEP_SUPPORT_ENABLE

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_EnableWakeupSources ( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource );

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_DisableWakeupSources ( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource );

extern FUNC( uint8, ECUM_CALLOUT_CODE )EcuM_CheckRamHash (void);

extern FUNC( void, ECUM_CALLOUT_CODE ) EcuM_GenerateRamHash(void);

#endif//ECUM_SLEEP_SUPPORT_ENABLE

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.h"

#endif /*ECUM_CALLOUT_H*/

