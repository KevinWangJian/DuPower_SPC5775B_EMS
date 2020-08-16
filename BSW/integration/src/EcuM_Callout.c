/*
 * This is a template file. It defines integration functions necessary to complete RTA-BSW.
 * The integrator must complete the templates before deploying software containing functions defined in this file.
 * Once templates have been completed, the integrator should delete the #error line.
 * Note: The integrator is responsible for updates made to this file.
 *
 * To remove the following error define the macro NOT_READY_FOR_TESTING_OR_DEPLOYMENT with a compiler option (e.g. -D NOT_READY_FOR_TESTING_OR_DEPLOYMENT)
 * The removal of the error only allows the user to proceed with the building phase
 */


/**********************************************************************************************************************
* CONTAINS THE STUBS OF THE CALLOUTS REALIZED IN THE IMPLEMENTATION
*********************************************************************************************************************/

/*
 **************************************************************************************************
 * Includes
 **************************************************************************************************
 */

#include "EcuM.h" /*BSW_HeaderInc_002*/

#include "EcuM_Callout.h"

#include "EcuM_RunTime.h" /*For init callout duration measurement*/

#include "EcuM_Prv.h"

#include "Integration.h"

/* External Header Include */
#include "Os.h"
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
#include "NvM.h"                    /*for setramblockstatus api*/
#if (!defined(NVM_AR_RELEASE_MAJOR_VERSION) || (NVM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(NVM_AR_RELEASE_MINOR_VERSION) || (NVM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED


#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"

/*If EcuM_OnGoOffOne() is not added via configuration then
 * hard coded callout stub will be enabled */
#ifndef ECUM_CFG_ON_GOOFFONE
/*Variable used to check,whether the execution reached the EcuM_OnGoOffOne() callout.*/
static volatile boolean EcuM_IsOnGoOffOneReached_b;
#endif

/*If EcuM_OnGoOffTwo() is not added via configuration then
 * hard coded callout stub will be enabled */
#ifndef ECUM_CFG_ON_GOOFFTWO
/*Variable used to check,whether the execution reached the EcuM_OnGoOffTwo() callout.*/
static volatile boolean EcuM_IsOnGoOffTwoReached_b;
#endif

/*If EcuM_AL_SwitchOff() is not added via configuration then
 * hard coded callout stub will be enabled */
#ifndef ECUM_CFG_AL_SWITCHOFF
/*Variable used to check,whether the execution reached the EcuM_AL_SwitchOff() callout.*/
static volatile boolean EcuM_IsALSwitchOffReached_b;
#endif

#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"

#ifndef ECUM_CFG_ON_GOOFFTWO
#if (ECUM_STARTUP_DURATION == TRUE) /*will activate the Run time measurement*/

#define ECUM_START_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"
/*To store the time taken for shutdown / reset*/
VAR( uint32, ECUM_VAR_CLEARED_32 ) EcuM_Shutdown_delta_us_u32;
#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
VAR( EcuM_TimeTicks_tu64, ECUM_VAR_CLEARED_UNSPECIFIED ) EcuM_Shutdown_begin_ticks_u64;
VAR( EcuM_TimeTicks_tu64, ECUM_VAR_CLEARED_UNSPECIFIED ) EcuM_Shutdown_end_ticks_u64;
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"



#endif//ECUM_STARTUP_DURATION
#endif//ifdef

#define ECUM_MAINFUNCTION_TIMEOUT   20u

/*************************************************************************************************
							CALLOUTS
*************************************************************************************************/

#define ECUM_START_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.h"

/*************************************************************************************************
  Function name     :   EcuM_ErrorHook

  Description       :   In case of serious error conditions like consistancy check failure or
                        Ram check failure, ecuM will initiate this call. In such situations it is not possible to
                        continue processing and Ecu has to be stopped.
  Parameter         :   Std_ReturnType reason
  Return value      :   none

************************************************************************************/

FUNC(void , ECUM_CALLOUT_CODE) EcuM_ErrorHook(VAR(uint16, AUTOMATIC) reason )
{
    while(1);
}

/*************************************************************************************************
  Function name     :   EcuM_AL_SetProgrammableInterrupts

  Description       :   EcuM_AL_SetProgrammableInterrupts shall set the interrupts on ECUs with programmable
                        interrupts.
  Parameter         :   none
  Return value      :   none

************************************************************************************/
FUNC(void , ECUM_CALLOUT_CODE) EcuM_AL_SetProgrammableInterrupts(void)
{

}

/**********************************************************************************
  Function name     :   EcuM_DeterminePbConfiguration
  Description       :   This callout should evaluate some condition, like port pin or
                        NVRAM value, to determine which post-build configuration shall
                        be used in the remainder of the startup process. It shall load
                        this configuration data into a piece of memory that is accessible
                        by all BSW modules and shall return a pointer to the EcuM post-build
                        configuration as a base for all BSW module post-build configrations.
  Parameter (in)    :   None
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   EcuM_ConfigType*
  Remarks           :
***********************************************************************************/
FUNC_P2CONST( EcuM_ConfigType , AUTOMATIC, ECUM_CALLOUT_CODE ) EcuM_DeterminePbConfiguration( void )
{
#if ECUM_STARTUP_DURATION == TRUE /*will activate the Run time measurement*/
    EcuM_DeterminePbConfiguration_begin_ticks_u64    =   EcuM_GetTicks();
#endif /*ECUM_STARTUP_DURATION*/
    /* Function definition can be added here , that is in between EcuM_DeterminePbConfiguration_begin_ticks_u64
     * and EcuM_DeterminePbConfiguration_end_ticks_u64. By this if project can measure the time duration
     * of this function*/

#if ECUM_STARTUP_DURATION == TRUE /*will activate the Run time measurement*/
    EcuM_DeterminePbConfiguration_end_ticks_u64    =   EcuM_GetTicks();
#endif /*ECUM_STARTUP_DURATION*/

    return(EcuM_EcuMConfigurations_cpcast[0]);
}

#ifndef ECUM_CFG_ON_GOOFFONE
/**********************************************************************************
  Function name     :   EcuM_OnGoOffOne
  Description       :   This call allows the system designer to notify that the GO OFF I
                        state is about to be entered.
  Parameter (in)    :   None
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/
FUNC(void , ECUM_CALLOUT_CODE) EcuM_OnGoOffOne(void )
{
    /*Update Flag variable to indicate that the execution reached the particular APi call.
     * Variable provided only for Debug purpose*/
    EcuM_IsOnGoOffOneReached_b = TRUE;

}
#endif

#ifndef ECUM_CFG_ON_GOOFFTWO
/**********************************************************************************
  Function name     :   EcuM_OnGoOffTwo
  Description       :   This call allows the system designer to notify that the GO OFF II
                        state is about to be entered.
  Parameter (in)    :   None
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/
FUNC(void , ECUM_CALLOUT_CODE) EcuM_OnGoOffTwo(void )
{
    /*Update Flag variable to indicate that the execution reached the particular APi call.
     * Variable provided only for Debug purpose*/
    EcuM_IsOnGoOffTwoReached_b = TRUE;
#if (ECUM_STARTUP_DURATION == TRUE) /*will activate the Run time measurement*/
    EcuM_Shutdown_end_ticks_u64 = EcuM_GetTicks();
    EcuM_Shutdown_delta_us_u32 = EcuM_GetDuration(EcuM_Shutdown_end_ticks_u64,EcuM_Shutdown_begin_ticks_u64);

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
    /*update the RAM variable in NV memory to the current shutdown target*/
    EcuM_Rb_dataShutdownInfo_st.ShutdownInfo.TimeMeasured = EcuM_Shutdown_delta_us_u32;
    (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#endif//ECUM_STARTUP_DURATION

/*NOTE to integrator: place the shutdown callouts below*/




}
#endif

#ifndef ECUM_CFG_AL_SWITCHOFF
/**********************************************************************************
  Function name     :   EcuM_AL_SwitchOff
  Description       :   This callout shall take the code for shutting off the power
                        supply of the ECU. If the ECU cannot unpower itself, a reset
                        may be an adequate reaction.
  Parameter (in)    :   None
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/
FUNC(void , ECUM_CALLOUT_CODE) EcuM_AL_SwitchOff(void )
{
    /*Update Flag variable to indicate that the execution reached the particular APi call.
     * Variable provided only for Debug purpose*/
    EcuM_IsALSwitchOffReached_b = TRUE;

}
#endif

/**********************************************************************************
  Function name     :   EcuM_AL_Reset
  Description       :   This callout shall take the code for resetting the ECU.
  Parameter (in)    :   reset - Type of reset to be performed.
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_AL_Reset( VAR(EcuM_ResetType, AUTOMATIC) reset )
{

}



/**********************************************************************************
  Function name     :   EcuM_CheckWakeup
  Description       :   this will be called from the corresponding driver when a wakeup is detected .
  Parameter (in)    :   wakeupSource.
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_CheckWakeup( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource )
{

}




/**********************************************************************************
  Function name     :   EcuM_StartWakeupSources
  Description       :   This callout shall start the given wakeup source(s) so that they are ready to perform wakeup validation.
  Parameter (in)    :   wakeupSource.
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_StartWakeupSources( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource )
{

}


/**********************************************************************************
  Function name     :   EcuM_StopWakeupSources
  Description       :   This callout shall stop the given wakeup source(s) after unsucessful wakeup validation..
  Parameter (in)    :   wakeupSource.
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_StopWakeupSources( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource )
{

}


/**********************************************************************************
  Function name     :   EcuM_CheckValidation
  Description       :   This callout is called by EcuM to validate Wakeup source. if a valid wakeup is detected it shall send report to EcuM via EcuM_ValidateWakeupEvent.
  Parameter (in)    :   wakeupSource.
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC( void, ECUM_CALLOUT_CODE ) EcuM_CheckValidation( VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource )
{

}

/**********************************************************************************
  Function name     :   EcuM_SwitchOsAppMode
  Description       :   This will be called from Master and Slave core Init api's. This is required for CalWup functionality.
                        In Master core this will be started after starting all cores
                        In Master and Slave core this will be called just before OS Start.
  Parameter (in)    :   None
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC(void, ECUM_CALLOUT_CODE) EcuM_SwitchOsAppMode(void)
{

}

#if ECUM_SLEEP_SUPPORT_ENABLE
/**********************************************************************************
  Function name     :   EcuM_EnableWakeupSources
  Description       :   The ECU Manager Module calls EcuM_EnableWakeupSource to allow the system designer to notify
                        wakeup sources defined in the wakeupSource bitfield that SLEEP will be entered
                        and to adjust their source accordingly.
  Parameter (in)    :   wakeupSource
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC(void, ECUM_CALLOUT_CODE) EcuM_EnableWakeupSources(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource)
{

}

/**********************************************************************************
  Function name     :   EcuM_DisableWakeupSources
  Description       :   The ECU Manager Module calls EcuM_DisableWakeupSources to set the wakeup source(s) defined
                        in the wakeupSource bitfield so that they are not able to wake the ECU up.
  Parameter (in)    :   wakeupSource
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   None
  Remarks           :
***********************************************************************************/

FUNC(void, ECUM_CALLOUT_CODE) EcuM_DisableWakeupSources(VAR(EcuM_WakeupSourceType, AUTOMATIC) wakeupSource)
{

}

/**********************************************************************************
  Function name     :   EcuM_CheckRamHash
  Description       :   This callout is intended to provide a RAM integrity test. The goal of this test is to ensure
                        that after a long SLEEP duration, RAM contents is still consistent.
  Parameter (in)    :   none
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   uint8
  Remarks           :
***********************************************************************************/

FUNC(uint8, ECUM_CALLOUT_CODE) EcuM_CheckRamHash(void)
{

}

/**********************************************************************************
  Function name     :   EcuM_GenerateRamHash
  Description       :
  Parameter (in)    :   none
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   none
  Remarks           :
***********************************************************************************/

FUNC(void, ECUM_CALLOUT_CODE) EcuM_GenerateRamHash(void)
{

}
#endif//ECUM_SLEEP_SUPPORT_ENABLE

/**********************************************************************************
  Function name     :   Loop_EcuM_MainFunction
  Description       :
  Parameter (in)    :   none
  Parameter (inout) :   None
  Parameter (out)   :   None
  Return value      :   none
  Remarks           :
***********************************************************************************/
FUNC( void, ECUM_CALLOUT_CODE ) Loop_EcuM_MainFunction(void)
{
	uint8 timeout = 0;

//	IC_Reset_Wdgs();

	while (timeout < ECUM_MAINFUNCTION_TIMEOUT)
	{
		EcuM_MainFunction();
		timeout++;
	}
}

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "EcuM_Cfg_MemMap.h"



