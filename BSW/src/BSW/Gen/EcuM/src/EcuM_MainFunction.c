

/****************************************************************************************************/
/* Preprocessor includes                                                                            */
/****************************************************************************************************/

#include "EcuM.h" /*BSW_HeaderInc_002*/

#include "EcuM_Callout.h"



#include "EcuM_Cfg_SchM.h"

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE != FALSE)
#include "SchM_EcuM.h"
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE

/*Extern module Headers*/
#include "BswM_EcuM.h"
#if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Rte_Main.h" /*For SchM_DeInit*/

#if(ECUM_DEV_ERROR_DETECT == STD_ON)/*Det included when Det is enabled in EcuM*/
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif/*ECUM_DEV_ERROR_DETECT*/

#include "Os.h"
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*EcuM Private headers*/
#include "EcuM_Prv.h"
/****************************************************************************************************/
/* Type definitions
 ***************************************************************************************************
 */
/****************************************************************************************************/
/* Variables                                                                                        */
/****************************************************************************************************/

#if (ECUM_CFG_MULTICORE_ENABLED == STD_ON)

#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"

 static VAR(boolean, ECUM_VAR) EcuM_Prv_ShutDownflgCoresStopped;
 static VAR(boolean, ECUM_VAR) EcuM_Prv_ShutDownflgCoresTimeout;

#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"

#endif //ECUM_CFG_MULTICORE_ENABLED


#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

static FUNC( void, ECUM_CODE ) EcuM_Prv_ProceedShutdown( void );
static FUNC( void, ECUM_CODE ) EcuM_Prv_WakeupValidation(void);
static FUNC( Std_ReturnType, ECUM_CODE ) EcuM_Prv_ShutdownSynchronization( void );

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
static FUNC(void, ECUM_CODE) EcuM_Prv_ProceedSleep( VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16 );
#endif//ECUM_SLEEP_SUPPORT_ENABLE

#if(ECUM_CFG_MODE_HANDLING == STD_ON)

static FUNC( void,ECUM_CODE ) EcuM_Prv_RunHandling( void );
static FUNC( void, ECUM_CODE ) EcuM_Prv_PostRunArbitration( void );
static FUNC( void, ECUM_CODE ) EcuM_Prv_RunArbitration( void );

#endif//ECUM_CFG_MODE_HANDLING
/***************************************************************************************************
 Function name    : void EcuM_MainFunction(void)
 Syntax           : void void EcuM_MainFunction(void)
 Description      : EcuM sheduled functions which is called by the BSW sheduler in a cyclic interval defined by the
                    configuration parameter EcuM_MainFunctionPeriod.Carries out all the functionality of the
                    EcuM when the OS is running.
 Parameter        : None
 Return value     : None
 ***************************************************************************************************/

FUNC(void, ECUM_CODE) EcuM_MainFunction(void)
{

    if (FALSE ==  EcuM_Prv_flgIsModuleInitialised_b)
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
        /*DET raised for service called before EcuM Initialised */
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID, ECUM_E_UNINIT);
#endif//ECUM_DEV_ERROR_DETECT
    }
    else if (E_NOT_OK ==  EcuM_Prv_ShutdownSynchronization())
    {
        /*update the phase variable to ECUM_PRV_PHASE_UP - EcuM is now in Up phase*/
        EcuM_Prv_dataPresentPhase_u8 = ECUM_PRV_PHASE_UP;

        /*RUN and POST_RUN requests and releases has to be arbitrated in EcuM MainFunction when ECUM_CFG_MODE_HANDLING
         * enabled in the system(Run Handling Protocol).*/

#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
 /* MR12 RULE 8.4 VIOLATION: The declaration of GetCoreID is expected from Os */
 if(GetCoreID() == ECUM_CFG_STARTUP_CORE)
 {
#endif//ECUM_CFG_MULTICORE_ENABLED

#if( ECUM_CFG_MODE_HANDLING == STD_ON)
            EcuM_Prv_RunHandling();
#endif//ECUM_CFG_MODE_HANDLING

        /*If shutdown flag is not set, proceed to the wakeup source validations*/
        EcuM_Prv_WakeupValidation();
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
            /*If shutdown flag is not set, proceed to the wakeup source validations*/
        }
#endif//ECUM_CFG_MULTICORE_ENABLED


    }
    else
    {
        //nothing to be executed here
    }
    return;
}

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
/**********************************************************************************************************************
  Function name :   EcuM_Prv_ProceedSleep
  Description   :   In Multicore Environment, Core synchronization is done and Sleep request is proceed to Go sleep
                    sequence.
  Parameter in  :   dataSleepModeHandle_u16 - the index of the selected sleep mode in EcuM_Cfg_idxSleepModes_au32 array
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *********************************************************************************************************************/

static FUNC(void, ECUM_CODE) EcuM_Prv_ProceedSleep( uint16 dataSleepModeHandle_u16 )
                {
    /*Local variable declaration*/
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
    VAR(uint16, AUTOMATIC) cntrLoopOsCore_u16 = 0;
    EcuM_Prv_CoreStatus_st.CurrentCoreID = GetCoreID();
    if(FALSE == EcuM_Prv_flgSleepReady_ab[EcuM_Prv_CoreStatus_st.CurrentCoreID])
    {
#endif//ECUM_CFG_MULTICORE_ENABLED
        /*GoSleep sequence*/

        /*Clear the wakeup sources */
        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );   /*Enter Critical Section*/

        /*Clear the enabled wakeup source from internal pending variable*/
        EcuM_Prv_dataPendingWakeupEvents_u32  ^= (EcuM_Prv_dataPendingWakeupEvents_u32
                & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);

        /*Clear the enabled wakeup source from internal validated variable*/
        EcuM_Prv_dataValidatedWakeupEvents_u32  ^= (EcuM_Prv_dataValidatedWakeupEvents_u32
                & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);

        /*Clear the enabled wakeup source from internal expired variable*/
        EcuM_Prv_dataExpiredWakeupEvents_u32  ^= (EcuM_Prv_dataExpiredWakeupEvents_u32
                & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);

        SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);      /*leave Critical Section*/

        /*Inidicate the wakeup status (NONE) to BswM*/
        BswM_EcuM_CurrentWakeup(EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask,
                                                                                                   ECUM_WKSTATUS_NONE);


        /*Enable the wakeup sources configured in Wakeupsourcemask of the selected sleep mode*/
        EcuM_EnableWakeupSources (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);


        #if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
    }
    /*MISRA RULE 8.1 VIOLATION: The declaration is expected from Os */

    if( EcuM_Prv_CoreStatus_st.CurrentCoreID == ECUM_CFG_STARTUP_CORE)
    {
        EcuM_Prv_CoreStatus_st.CurrentCore = ECUM_MASTER_CORE;

        EcuM_Prv_flgSleepReady_ab[ECUM_CFG_STARTUP_CORE] = TRUE;

        /*Loop to check core ready flag for all cores. If one core is not ready don't proceed with sleep */
        for(cntrLoopOsCore_u16 = 0; cntrLoopOsCore_u16 < ECUM_CFG_NUM_OS_CORES ; cntrLoopOsCore_u16++)
        {
            if ( FALSE == EcuM_Prv_flgSleepReady_ab[cntrLoopOsCore_u16])
            {
                /*Set the flag to FALSE if any of the cores are not ready and stopped*/
                EcuM_Prv_AllCoreSleepReady_b = FALSE;
                break;
            }
            else
            {
                /*Set the flag to TRUE if all the cores are ready and stopped */
                EcuM_Prv_AllCoreSleepReady_b = TRUE;
            }
        }
    }
    else
    {
        EcuM_Prv_CoreStatus_st.CurrentCore= ECUM_SLAVE_CORE;
    }


#else//ECUM_CFG_MULTICORE_ENABLED

    EcuM_Prv_CoreStatus_st.CurrentCore= ECUM_SINGLE_CORE;
    EcuM_Prv_CoreStatus_st.CurrentCoreID=0xFF;//initialise with invalid value
#endif//ECUM_CFG_MULTICORE_ENABLED
#if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
if(EcuM_Prv_flgSleepReady_ab[ECUM_CFG_STARTUP_CORE] == TRUE)
{
#endif//ECUM_CFG_MULTICORE_ENABLED
    EcuM_Prv_GoSleepSequence(dataSleepModeHandle_u16);
#if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
}
#endif//ECUM_CFG_MULTICORE_ENABLED
                }

#endif//ECUM_SLEEP_SUPPORT_ENABLE
/***********************************************************************************************
  Function name :   EcuM_Prv_Shutdown
  Description   :   Contains the shutdown functionalities for Multicore Shutdown Synchronization
  Parameter in  :   None
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *************************************************************************************************/
static FUNC(void, ECUM_CODE) EcuM_Prv_ProceedShutdown(void)
{

#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)

    /*Local variable declaration*/
       VAR(uint16, AUTOMATIC) cntrLoopOsCore_u16;
       VAR(CoreIdType, AUTOMATIC) EcuM_activeCoreid;

    EcuM_Prv_ShutDownflgCoresStopped = FALSE;
    EcuM_Prv_ShutDownflgCoresTimeout = FALSE;
    /* MR12 RULE 8.4 VIOLATION: The declaration of GetCoreID is expected from Os */
       EcuM_activeCoreid = GetCoreID();

    if(EcuM_activeCoreid == ECUM_CFG_STARTUP_CORE)
    {

        /*Increment the core ready timeout for slave cores*/
        EcuM_Prv_SlaveCoreTimeoutCtr_u8++;

        /* Set MasterCore also to finished in case ECUM_CFG_STARTUP_CORE is unequal to zero */
        EcuM_Prv_flgCoreReady_ab[ECUM_CFG_STARTUP_CORE] = TRUE;


         /*Loop to check core ready flag for all cores. If one core is not ready don't proceed with shutdown */
        for(cntrLoopOsCore_u16 = 0; cntrLoopOsCore_u16 < ECUM_CFG_NUM_OS_CORES ; cntrLoopOsCore_u16++)
        {
            if (EcuM_Prv_flgCoreReady_ab[cntrLoopOsCore_u16] == FALSE )
            {
                /*Set the flag to FALSE if any of the cores are not ready and stopp */
                EcuM_Prv_ShutDownflgCoresStopped = FALSE;
                break;
            }
            else
            {
                EcuM_Prv_ShutDownflgCoresStopped = TRUE;
            }
        }

        /*Check for timeout of Slave core readiness*/
        if(EcuM_Prv_SlaveCoreTimeoutCtr_u8 > ECUM_CFG_SLAVE_CORE_TIMEOUT)
        {
            EcuM_Prv_ShutDownflgCoresTimeout = TRUE;

#if(ECUM_DEV_ERROR_DETECT == STD_ON)

            /*Call to Det_ReportError for CoreReady timeout error*/
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID, ECUM_E_COREREADY_TIMEOUT_EXPIRED);

#endif /* ECUM_DEV_ERROR_DETECT */

        }

        /*Call ShutdownAllCores if all cores have stopped or a timeout has occured  */
        if ((EcuM_Prv_ShutDownflgCoresStopped == TRUE) || (EcuM_Prv_ShutDownflgCoresTimeout == TRUE))
        {
            EcuM_OnGoOffOne();

            /* De-Initialization of BSW Mode Manager*/
            BswM_Deinit();

            /* De-Initialization of Schedule Manager*/
            SchM_Deinit();

            /*Unsetting the Shutdown Flag is specified by AUTOSAR*/
            EcuM_Prv_flgGoDown_b =   FALSE;

            /*Call ShutdownAllCores*/
            ShutdownAllCores(E_OS_SYS_NO_RESTART);
        }
    }
        else
        {

        /* Check if EcuM_GoDown is called and CoreReady Flag is not set for the Specific core */
        if((FALSE == EcuM_Prv_flgCoreReady_ab[EcuM_activeCoreid]) && (EcuM_Prv_flgGoDown_b  == TRUE))
        {

            EcuM_OnGoOffOne();

            /* De-Initialization of Schedule Manager*/
            SchM_Deinit();

            /*Set the core ready flag*/
            EcuM_Prv_flgCoreReady_ab[EcuM_activeCoreid] = TRUE;

            return;
        }

    }
#else//ECUM_CFG_MULTICORE_ENABLED

             EcuM_OnGoOffOne();

              /* De-Initialization of BSW Mode Manager*/
              BswM_Deinit();

              /* De-Initialization of Schedule Manager*/
              SchM_Deinit();

              /*Call of ShutdownOS function for Single core system*/
               ShutdownOS(E_OS_SYS_NO_RESTART);

#endif//ECUM_CFG_MULTICORE_ENABLED

}


/***********************************************************************************************
  Function name :   EcuM_Prv_WakeupValidation
  Description   :   Contains the Wakeup validation functionality for the wakeup sources
  Parameter in  :   None
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *************************************************************************************************/
static FUNC( void, ECUM_CODE ) EcuM_Prv_WakeupValidation(void)
        {
    /*Local variable declaration*/
    VAR(uint8, AUTOMATIC) cntrLoopCtr_u8;
    VAR(EcuM_WakeupSourceType,AUTOMATIC) dataPendingWakeupEvents_u32;
    VAR( uint16, ECUM_VAR ) datawkpSrcValidationTimeoutCtr_u16;

        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
        /*Get the latest PENDING events list*/
        dataPendingWakeupEvents_u32 = EcuM_Prv_dataPendingWakeupEvents_u32;
        /*Get the Validation timeout value with the current main cycle*/
        datawkpSrcValidationTimeoutCtr_u16 = EcuM_Prv_WkpSrcValidationTimeoutCtr_u16;
        SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*leave Critical Sectiont*/

        EcuM_Prv_WakeupIndication(dataPendingWakeupEvents_u32);

        if (EcuM_Prv_dataOldPendingWakeupEvents_u32 != ECUM_NO_WKUP_SRC )
        {
            /*Iterate the configured wakeup sources*/
            for (cntrLoopCtr_u8 = 0;cntrLoopCtr_u8 < ECUM_NUM_OF_WKP_SOURCES ; cntrLoopCtr_u8++)
            {
                if ((EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId & EcuM_Prv_dataOldPendingWakeupEvents_u32) != ECUM_NO_WKUP_SRC)
                {
                    /* if configured wakeup source state is EcuM wakeupsource pending (or not validated) and the validation timeout is not expired */
                    /*call EcuM_CheckValidation with the wakeup source as the parameter */
                    EcuM_CheckValidation (EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId);
                }

                /*if any wakeup is validated in between the corresponding pending wakeup event will get cleared.
                 * if so update the Pending wakeup event variable corresponding to this main cycle with the latest pending wakeup event */
                if ((EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId &
                        EcuM_Prv_dataValidatedWakeupEvents_u32) != ECUM_NO_WKUP_SRC)
                {
                    SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
                    EcuM_Prv_dataOldPendingWakeupEvents_u32 = EcuM_Prv_dataPendingWakeupEvents_u32;
                     SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*leave Critical Sectiont*/
                }
            }
        }


    /* Check whether validation timeout counter is expired AND is there still any Pending Wakeup events
     * that is evaluated in the current main cycle, then make the wakeupsource state as Expired */
    if ((datawkpSrcValidationTimeoutCtr_u16 == 0) &&
            ( (EcuM_Prv_dataOldPendingWakeupEvents_u32 & dataPendingWakeupEvents_u32) != ECUM_NO_WKUP_SRC))
    {
        /*Update the Expired wakeup event variable */
        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
        EcuM_Prv_dataExpiredWakeupEvents_u32 ^= EcuM_Prv_dataOldPendingWakeupEvents_u32 ;
        EcuM_Prv_dataPendingWakeupEvents_u32 ^= EcuM_Prv_dataOldPendingWakeupEvents_u32;
        /*Update the EcuM_Prv_dataOldPendingWakeupEvents_u32 to Zero so that with the next cycle new sources
         * will be evaluated for Validation*/
        EcuM_Prv_dataOldPendingWakeupEvents_u32 = ECUM_NO_WKUP_SRC;
        SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*leave Critical Sectiont*/

        /* Give wakeup state indication to BswM*/
        BswM_EcuM_CurrentWakeup ( EcuM_Prv_dataExpiredWakeupEvents_u32 , ECUM_WKSTATUS_EXPIRED);

        /*Stop the validation of all sources that got expired with the current main cycle*/
        EcuM_StopWakeupSources (EcuM_Prv_dataExpiredWakeupEvents_u32 );
    }

    EcuM_Prv_DecValidationCtr();

    return;

}
#if( ECUM_CFG_MODE_HANDLING == STD_ON)
/***********************************************************************************************
  Function name :   EcuM_Prv_RunHandling
  Description   :   Contains the activities of EcuM Run Handling Protocol
  Parameter in  :   None
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *************************************************************************************************/
static FUNC( void, ECUM_CODE ) EcuM_Prv_RunHandling(void)
{

    /*To ensure  the warm-up time to prepare the RTE and application software users as well as  the proper termination after
     * a idle time The Minimum RUN duration feature has been provided. It is a configurable value.*/
    if( EcuM_Prv_RunMinDuration_u16 > 0 )
    {
        EcuM_Prv_RunMinDuration_u16 = EcuM_Prv_RunMinDuration_u16 - 1;
    }
     else
    {

    }
    /* Fixed Mode Handling Arbitration for All the EcuM-Flex User Run Request will be handled from EcuM_Prv_RunArbitration and RUN Status
     * Requested/Released will be notified to BswM through BswM_EcuM_RequestedState Api.*/
    EcuM_Prv_RunArbitration( );

    /* Fixed Mode Handling Arbitration for All the EcuM-Flex User Post_Run Request will be handled from EcuM_Prv_RunArbitration and POSTRUN Status
      * Requested/Released will be notified to BswM through BswM_EcuM_RequestedState Api.*/
    EcuM_Prv_PostRunArbitration( );

    return;
}

/***********************************************************************************************
  Function name :   EcuM_Prv_RunArbitration
  Description   :   Contains the activities Arbitrating and notifying the User Run Request status
                    of EcuM Run Handling Protocol
  Parameter in  :   None
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *************************************************************************************************/
static FUNC( void, ECUM_CODE ) EcuM_Prv_RunArbitration( void )
{
    /*iterator variable for the users*/
    VAR( uint8, AUTOMATIC ) cntrLoopCtr_u8;
    /*Local value used to ensure either RUN Request is in progress or not*/
    VAR( boolean, AUTOMATIC ) UserRUNReqPending_b = FALSE;

    /*Loop for handling the RUN requests from the Users*/
        for( cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 <ECUM_CFG_NUM_FLEX_USERS;cntrLoopCtr_u8++ )
        {
            /*Check for the Presence of a particular user request for RUN state*/
            if( EcuM_Prv_userRUNReqStatus_ab[ cntrLoopCtr_u8 ] == TRUE )
            {
                /*If it is the first user request then notify the BswM about the status ECUM_RUNSTATUS_REQUESTED*/
                if( ( EcuM_Prv_RunRequested_u8 == ECUM_RUNSTATUS_RELEASED ) || ( EcuM_Prv_RunRequested_u8 == ECUM_RUNSTATUS_UNKNOWN ) )
                {
                    BswM_EcuM_RequestedState( ECUM_STATE_APP_RUN,ECUM_RUNSTATUS_REQUESTED );
                    EcuM_Prv_RunRequested_u8 = ECUM_RUNSTATUS_REQUESTED;

                }
                /*If atleast one user request is pending update the given local variable else donot update.
                 * based on that status ECUM_RUNSTATUS_RELEASED notification to BswM will be decided */
                else
                {

                }
                UserRUNReqPending_b = TRUE;
                break;
            }
            else
            {

            }
        }
        /*BswM Notification Status Released to be triggered, when all the user requests are released. Run minimum duration check
            is to ensure the idle time as well as warm-up time to prepare the RTE and application software users.*/
        if( ( EcuM_Prv_RunMinDuration_u16 == 0 ) && ( UserRUNReqPending_b == FALSE )
                && ( ( EcuM_Prv_RunRequested_u8 == ECUM_RUNSTATUS_REQUESTED ) ||  ( EcuM_Prv_RunRequested_u8 == ECUM_RUNSTATUS_UNKNOWN ) ) )
        {
            BswM_EcuM_RequestedState( ECUM_STATE_APP_RUN,ECUM_RUNSTATUS_RELEASED );
            EcuM_Prv_RunRequested_u8 = ECUM_RUNSTATUS_RELEASED;
        }
        else
        {

        }

        return;
}
/***********************************************************************************************
  Function name :   EcuM_Prv_PostRunArbitration
  Description   :   Contains the activities Arbitrating and notifying the User PostRun Request status
                    of EcuM Run Handling Protocol
  Parameter in  :   None
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *************************************************************************************************/
static FUNC( void, ECUM_CODE ) EcuM_Prv_PostRunArbitration( void )
{
    /*iterator variable for the users*/
    VAR( uint8, AUTOMATIC ) cntrLoopCtr_u8;
    /*Local value used to ensure either POSTRUN Request is in progress or not*/
    VAR( boolean, AUTOMATIC ) UserPostRUNReqPending_b = FALSE;

    /*Loop for handling the POSTRUN requests from the Users*/
        for( cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 < ECUM_CFG_NUM_FLEX_USERS;cntrLoopCtr_u8++ )
        {
            /*Check for the Presence of a particular user request for POSTRUN state*/
            if( EcuM_Prv_userPostRUNReqStatus_ab[ cntrLoopCtr_u8 ] == TRUE )
            {
                /*If it is the first user request then notify the BswM about the status ECUM_RUNSTATUS_REQUESTED for POSTRUN*/
                if( ( EcuM_Prv_Post_Run_Requested_u8 == ECUM_RUNSTATUS_RELEASED ) || ( EcuM_Prv_Post_Run_Requested_u8 == ECUM_RUNSTATUS_UNKNOWN ) )
                {
                    BswM_EcuM_RequestedState( ECUM_STATE_APP_POST_RUN,ECUM_RUNSTATUS_REQUESTED  );
                    EcuM_Prv_Post_Run_Requested_u8 = ECUM_RUNSTATUS_REQUESTED;
                }
                /*If atleast one user request is pending update the given local variable else donot update.
                 * based on that status ECUM_RUNSTATUS_RELEASED notification to BswM will be decided */
                else
                {

                }
                UserPostRUNReqPending_b = TRUE;
                break;
            }
            else
            {

            }
        }
        /*BswM Notification Status Released to be triggered, when all the user requests are released. Run minimum duration check
        is to ensure the idle time as well as warm-up time to prepare the RTE and application software users.*/
        if( ( EcuM_Prv_RunMinDuration_u16 == 0 ) && ( UserPostRUNReqPending_b == FALSE )
                && ( ( EcuM_Prv_Post_Run_Requested_u8 == ECUM_RUNSTATUS_REQUESTED ) || ( EcuM_Prv_Post_Run_Requested_u8 == ECUM_RUNSTATUS_UNKNOWN ) ) )
        {
            BswM_EcuM_RequestedState( ECUM_STATE_APP_POST_RUN,ECUM_RUNSTATUS_RELEASED );
            EcuM_Prv_Post_Run_Requested_u8 = ECUM_RUNSTATUS_RELEASED;
        }
        else
        {

        }

        return;
}
#endif//ECUM_CFG_MODE_HANDLING

/***********************************************************************************************
  Function name :   EcuM_Prv_ShutdownSynchronization
  Description   :   Handles the phase transitions for sleep and shutdown phases
  Parameter in  :   None
  Parameter out :   None
  Return value  :   Std_ReturnType
  Remarks       :
 *************************************************************************************************/
static FUNC( Std_ReturnType , ECUM_CODE ) EcuM_Prv_ShutdownSynchronization( void )
 {

    VAR(Std_ReturnType, AUTOMATIC) return_value = E_NOT_OK;
#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
    VAR(EcuM_Prv_SleepType_Enum_ten, AUTOMATIC)     id_RequestedSleepType_en;
    VAR(boolean, AUTOMATIC) flgWakeRestartStatus_b;
    /*Local variable to hold sleep mode and intiliazed with invalid value*/
    VAR(EcuM_ShutdownModeType, AUTOMATIC) dataSleepModeHandle_u16 = 0xFF;


    SchM_Enter_EcuM(ECUM_SCHM_EXCLSV_AREA);           /*Enter Critical Section*/

    /*sleep mode for which EcuM_GoPoll/EcuM_GoHalt was called*/
    dataSleepModeHandle_u16 = EcuM_Prv_SleepMode_u16;
    /*Getting the Sleep type in critical region*/
    id_RequestedSleepType_en = EcuM_Prv_SleepReqType_en;

    SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);            /*Exit Critical Section*/

    if(ECUM_PRV_GOHALT_E == id_RequestedSleepType_en)
    {
        EcuM_Prv_ProceedSleep(dataSleepModeHandle_u16);
    }
    else
    {

    }

    /*Getting the WakeupRestart flag in critical region*/
    SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );         /*Enter Critical Section*/

    flgWakeRestartStatus_b  = EcuM_Prv_flgwakeupRestart_b;

    SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);            /*leave Critical Section*/

    if ( FALSE != flgWakeRestartStatus_b)
    {
        EcuM_Prv_WakeupRestartSequence(dataSleepModeHandle_u16);
    }

    if((((ECUM_PRV_GOPOLL_E != id_RequestedSleepType_en) &&
            (ECUM_PRV_GOHALT_E != id_RequestedSleepType_en)) && (TRUE != flgWakeRestartStatus_b)))
    {
#endif//ECUM_SLEEP_SUPPORT_ENABLE

        /*Check for GoDown flag is set from EcuM_GoDown*/
        if(FALSE != EcuM_Prv_flgGoDown_b)
        {
            /*Call to Shutdown operations if GoDown flag is set*/
            EcuM_Prv_ProceedShutdown();
            return_value = E_OK;
        }
        else
        {

        }
#if ECUM_SLEEP_SUPPORT_ENABLE
    }
#endif//ECUM_SLEEP_SUPPORT_ENABLE
    return return_value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"
