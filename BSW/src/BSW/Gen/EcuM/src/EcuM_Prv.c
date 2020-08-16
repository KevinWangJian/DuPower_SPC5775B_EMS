



/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "EcuM.h" /*BSW_HeaderInc_002*/



#include "EcuM_Cfg_SchM.h"
/*For run time measurement*/
#include "EcuM_Runtime.h"

/*Extern module Headers*/
#include "BswM_EcuM.h"
#if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Mcu.h"
#if (!defined(MCU_AR_RELEASE_MAJOR_VERSION) || (MCU_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(MCU_AR_RELEASE_MINOR_VERSION) || (MCU_AR_RELEASE_MINOR_VERSION != 2))
//#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "ComM_EcuMBswM.h"
#if (!defined(COMM_AR_RELEASE_MAJOR_VERSION) || (COMM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(COMM_AR_RELEASE_MINOR_VERSION) || (COMM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Os.h"
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

#if(ECUM_DEV_ERROR_DETECT == STD_ON)/*Det included when Det is enabled in EcuM*/
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif/*ECUM_DEV_ERROR_DETECT*/

/*EcuM Private headers*/
#include "EcuM_Callout.h"
#include "EcuM_Prv.h"
/*************************************************************************************************
 Variables
*************************************************************************************************
*/
#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_Cfg_MemMap.h"

 /* Variable to store the Selected Boot target*/
VAR(EcuM_BootTargetType,ECUM_VAR_POWER_ON_CLEARED_8)  EcuM_Prv_dataSelectedBootTarget_u8;

/* Variable which stores the informaition if EcuM_Prv_dataSelectedBootTarget_u8 has been set with EcuM_SelectBootTarget
 * This is needed because ECUM_START_SEC_VAR_POWER_ON_INIT_8 does not exist */
VAR(uint8,ECUM_VAR_POWER_ON_CLEARED_8)  EcuM_Prv_dataSelectedBootTargetInit_u8;

#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_VAR_CLEARED_8
#include "EcuM_Cfg_MemMap.h"

/*Tells the present Phase of the EcuM*/
VAR(uint8, ECUM_VAR_CLEARED_8)  EcuM_Prv_dataPresentPhase_u8;

/* Slave core timeout counter for shutdown synchronization*/
VAR( uint8, ECUM_VAR_CLEARED_8 )  EcuM_Prv_SlaveCoreTimeoutCtr_u8;
/* Variable to store the selected Shutdown cause*/
VAR( EcuM_ShutdownCauseType, ECUM_VAR_CLEARED_8 )  EcuM_Prv_dataSelectedShutdownCause_u8 = 0;

#if( ECUM_CFG_MODE_HANDLING == STD_ON)
/*Variable used to hold the status of Run Request/Release to notify the BswM as per Run handling protocol*/
VAR(uint8, ECUM_VAR_CLEARED_8) EcuM_Prv_RunRequested_u8;
/*Variable used to hold the status of Post_Run Request/Release to notify the BswM as per Run handling protocol*/
VAR(uint8, ECUM_VAR_CLEARED_8) EcuM_Prv_Post_Run_Requested_u8;
#endif //ECUM_CFG_MODE_HANDLING

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
/*variable holds the info whether Gopoll called or not*/
VAR(EcuM_Prv_SleepType_Enum_ten, ECUM_VAR_CLEARED_8) EcuM_Prv_SleepReqType_en;
/*variable holds the Wakeup Restart Reason*/
VAR(EcuM_Prv_WakeupRestartReason_Enum_ten, ECUM_VAR_CLEARED_8) EcuM_Prv_WakeupRestartReason_en;
/*variable used to indicate the wakeup restart event*/
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_8
#include "EcuM_Cfg_MemMap.h"



#define ECUM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
/* Variable to store the selected Shutdown target*/
VAR(EcuM_ShutdownTargetInfoType, ECUM_VAR_CLEARED_UNSPECIFIED)   EcuM_Prv_dataSelectedShutdownTarget_st;
#if( ECUM_SLEEP_SUPPORT_ENABLE == TRUE )
VAR( EcuM_CurrentCoreInfoType, ECUM_VAR_CLEARED_UNSPECIFIED ) EcuM_Prv_CoreStatus_st;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"
/* Variable to store the Old Pending Wakeup Events*/
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataOldPendingWakeupEvents_u32;

/* Variable to store the Pending Wakeup Events*/
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataPendingWakeupEvents_u32;

/* Variable to store the Validated Wakeup Events*/
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataValidatedWakeupEvents_u32;

/* Variable to store the Expired Wakeup Events*/
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataExpiredWakeupEvents_u32;

/* Variable to store the Cleared Wakeup Events*/
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataClrWkpEventsInd_u32;

/* Variable to store the Pending Wakeup Events used for BswM indication in main function for current cycle*/
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataPndWkpEventsInd_u32;

/* Variable to store the Validated Wakeup Events used for BswM indication in main function for current cycle*/
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 ) EcuM_Prv_dataValWkpEventsInd_u32;

/* Variable to store the Clear Wakeup Events */
VAR( EcuM_WakeupSourceType, ECUM_VAR_CLEARED_32 )EcuM_Prv_dataExpWkpEventsInd_u32;


#define ECUM_STOP_SEC_VAR_CLEARED_32
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_CLEARED_16
#include "EcuM_Cfg_MemMap.h"
/* Variable to store the wake up validation Timeout Timer counter */
VAR( uint16, ECUM_VAR_CLEARED_16 )  EcuM_Prv_WkpSrcValidationTimeoutCtr_u16;

#if (ECUM_SLEEP_SUPPORT_ENABLE== TRUE)
/*Holds the sleep mode for which the EcuM_GoPoll/EcuM_GoHalt called*/
VAR( EcuM_ShutdownModeType, ECUM_VAR_CLEARED_16 ) EcuM_Prv_SleepMode_u16;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_16
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"

/*The ptr to the EcuM whole config pb structure*/
P2CONST(EcuM_ConfigType, ECUM_VAR_POWER_ON_CLEARED_UNSPECIFIED, ECUM_APPL_CONST) EcuM_Rb_adrConfigPtr_st; /*Pointer to EcuM config Type*/

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
/* variable to hold the previous shutdown information */
VAR( EcuM_ShutdownTargetInfoType, ECUM_VAR_POWER_ON_CLEARED_UNSPECIFIED ) EcuM_Prv_dataShutdownInfo_st;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#define ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_VAR_INIT_16
#include "EcuM_Cfg_MemMap.h"

#if(ECUM_CFG_MODE_HANDLING == STD_ON)
VAR( uint16, ECUM_VAR_INIT_16 ) EcuM_Prv_RunMinDuration_u16 = ECUM_CFG_RUN_SELF_REQUEST_PERIOD;
#endif//ECUM_CFG_MODE_HANDLING

#define  ECUM_STOP_SEC_VAR_INIT_16
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"
/*holds the status of EcuM_Init is called or not*/
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_flgIsModuleInitialised_b;
/*array used to hold the initalization status of startupTwo*/
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_flgIsStartupTwoCalled_ab[ECUM_CFG_NUM_OS_CORES];
/* array used to hold the core status to proceed with shutdown*/
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_flgCoreReady_ab[ECUM_CFG_NUM_OS_CORES];
/*Flag to indicate the updatability of shutdown info*/
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgShutdownInfoDoNotUpdate_b;
#if(ECUM_CFG_MODE_HANDLING == STD_ON)
/*Array of flag to maintain the RUN reuqest status of each user */
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_userRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];

/*Array of flag to maintain the POST_RUN reuqest status of each user */
VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_userPostRUNReqStatus_ab[ECUM_CFG_NUM_FLEX_USERS];

/*Variable used to hold the status of EcuM_KillAllRUNRequests*/
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_KillAllRUNRequests_b = FALSE;

/*Variable used to hold the status of EcuM_KillAllPostRUNRequests*/
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_KillAllPostRUNRequests_b = FALSE;

#endif//ECUM_CFG_MODE_HANDLING

/*Flag to  validate shutdown from EcuM_GoDown */
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgGoDown_b;

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
/*flag to determine whether the previous shutdown information has been copied successfully from NV RAM to EcuM
 * prv variable*/
VAR(boolean,ECUM_VAR_CLEARED_BOOLEAN)  EcuM_Prv_flgNvMReadStatus_b;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
/*variable used to indicate the wakeup restart event*/
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgwakeupRestart_b;
/*Flag to enable clearing the wakeup restart flag*/
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_flgClearWakeupRestart_b;
/*variable holds the core synchronization info to proceed with polling*/
VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_AllCoreSleepReady_b;
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
/*array used to hold the sleep status of individual */
volatile VAR( boolean, ECUM_VAR_CLEARED_BOOLEAN ) EcuM_Prv_flgSleepReady_ab[ECUM_CFG_NUM_OS_CORES];
/*variable result of RAM Integerity check which acts as flag for slave to come out of Halt*/
volatile VAR(boolean, ECUM_VAR_CLEARED_BOOLEAN) EcuM_Prv_RAMCheckPassed_b;
#endif //ECUM_CFG_MULTICORE_ENABLED
#endif//ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "EcuM_Cfg_MemMap.h"


#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"
#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
static FUNC(void, ECUM_CODE) EcuM_Prv_HaltingSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16);
static FUNC( void, ECUM_CODE)EcuM_Prv_McuSetMode( VAR(uint8, AUTOMATIC) Mode, VAR(EcuM_Prv_OperationType_Enum_ten, AUTOMATIC) flgOperation_en);
#endif //ECUM_SLEEP_SUPPORT_ENABLE


#if(ECUM_CFG_MODE_HANDLING == STD_ON)
/***********************************************************************************
  Function name :   EcuM_Prv_IsUserHandlingPossible
  Description   :   EcuM user handling is possible only after the module initialization and the user parameter is valid.
                    This function checks for possiblity of user handling and return TRUE if user handling is possible.
                    This function is called in the following mode handling interfaces EcuM_RequestRUN, EcuM_ReleaseRUN,
                    EcuM_RequestPOST_RUN, EcuM_ReleasePOST_RUN
  Parameter in  :   user , apiid
  Parameter out :   user
  Return value  :   boolean
  Remarks       :
 ************************************************************************************/
FUNC( boolean, ECUM_CODE ) EcuM_Prv_IsUserHandlingPossible_b(
        P2VAR(EcuM_UserType, AUTOMATIC, ECUM_APPL_DATA)user,
        VAR(uint8, AUTOMATIC) apiid)
{

    /* Local Variables */
    VAR(boolean, AUTOMATIC ) return_value = FALSE;
    VAR(EcuM_UserType, AUTOMATIC) cntrLoop_u16;
    VAR(boolean,AUTOMATIC) is_validuser_b = FALSE;

    /* Check if the EcuM module is initialised */
    if(FALSE != EcuM_Prv_flgIsModuleInitialised_b)
    {
        for(cntrLoop_u16 = 0;cntrLoop_u16 < ECUM_CFG_NUM_FLEX_USERS;cntrLoop_u16++)
            {
                if(EcuM_Cfg_flexUsers_au16[cntrLoop_u16] == *user)
                {
                    *user = cntrLoop_u16;
                    is_validuser_b = TRUE;
                    break;
                }
            }

        /* Check if the parameter is a valid user */
        if(FALSE != is_validuser_b)
        {
            if (((ECUM_REQUESTRUN_APIID == apiid) && (EcuM_Prv_KillAllRUNRequests_b != FALSE)) ||
                            ((ECUM_REQUESTPOST_RUN_APIID == apiid) && (EcuM_Prv_KillAllPostRUNRequests_b != FALSE)))
            {
                #if (ECUM_DEV_ERROR_DETECT == STD_ON)
                /*DET raised for service called after EcuM_KillAllRUNRequests or EcuM_KillAllPostRUNRequests is called */
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_RB_E_ALL_RUN_REQUESTS_KILLED);
                #endif/*ECUM_DEV_ERROR_DETECT*/
            }
            else
            {
                return_value = TRUE;
            }
        }
        else
        {
            #if (ECUM_DEV_ERROR_DETECT == STD_ON)
            /*DET raised for service called with invalid user ID */
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_E_INVALID_PAR);
            #endif /*ECUM_DEV_ERROR_DETECT*/
        }
    }
    else
    {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)
        /*DET raised for service called before EcuM Initialised */
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, apiid, ECUM_E_UNINIT);
        #endif/*ECUM_DEV_ERROR_DETECT*/
    }

    return return_value;

}
#endif /*ECUM_CFG_MODE_HANDLING*/


/***********************************************************************************

  Function name :   EcuM_Prv_WakeupIndication
  Description   :   Check for pending, expired and validated wakeup events and indicates BswM and ComM accordingly
  Parameter in  :   dataPendingWakeupEvents_u32
  Parameter out :
  Return value  :   void
  Remarks       :
 ************************************************************************************/
FUNC( void, ECUM_CODE ) EcuM_Prv_WakeupIndication( VAR(EcuM_WakeupSourceType, AUTOMATIC) dataPendingWakeupEvents_u32 )
{

    /*Local variable declaration*/
    VAR(uint8, AUTOMATIC) cntrLoopCtr_u8;
    VAR(uint8, AUTOMATIC) ctrLoopPNCNotify_u8;

    /* check for sending Bswm indication for the wakeup sources which is set to pending during set wakeup event */
    if (EcuM_Prv_dataPndWkpEventsInd_u32 != ECUM_NO_WKUP_SRC)
    {
        BswM_EcuM_CurrentWakeup (EcuM_Prv_dataPndWkpEventsInd_u32, ECUM_WKSTATUS_PENDING);
    }

    /* check for sending Bswm indication for the wakeup sources which is set to validated during set wakeup event */
    if (EcuM_Prv_dataValWkpEventsInd_u32 !=ECUM_NO_WKUP_SRC)
    {
        BswM_EcuM_CurrentWakeup (EcuM_Prv_dataValWkpEventsInd_u32, ECUM_WKSTATUS_VALIDATED);
        for(cntrLoopCtr_u8 = 0;cntrLoopCtr_u8 < ECUM_NUM_OF_WKP_SOURCES ; cntrLoopCtr_u8++)
        {
            if (((EcuM_Cfg_idxWakeupSourcesPC_au32 [cntrLoopCtr_u8].WakeupSourceId & EcuM_Prv_dataValWkpEventsInd_u32)
                    != ECUM_NO_WKUP_SRC) &&
                    (EcuM_Cfg_idxWakeupSourcesPC_au32 [cntrLoopCtr_u8].IsComChannelPresent == TRUE))
            {
                /*Give ComM Indication*/
                ComM_EcuM_WakeUpIndication (EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].ComChannelReferance);
            }

            /* indicate to ComM module if ComMPNC Channel Reference is associated with the wakeup source */
            if ( ( ( EcuM_Prv_dataValWkpEventsInd_u32 & EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId ) != ECUM_NO_WKUP_SRC ) \
                    && ( EcuM_Rb_adrConfigPtr_st->adrWkupPNCRefs[cntrLoopCtr_u8].nbrOfComMPNCRef > 0 ) )
            {

                for ( ctrLoopPNCNotify_u8 = 0; ctrLoopPNCNotify_u8 <  (EcuM_Rb_adrConfigPtr_st->adrWkupPNCRefs[cntrLoopCtr_u8].nbrOfComMPNCRef); ctrLoopPNCNotify_u8++)
                {
                    ComM_EcuM_PNCWakeUpIndication(EcuM_Rb_adrConfigPtr_st->adrWkupPNCRefs[cntrLoopCtr_u8].ListOfPNCRefs[ctrLoopPNCNotify_u8]);
                }

            }
        }
    }

    /* check for sending Bswm indication for the wakeup sources which is cleared  during clear wakeup event */
    if((EcuM_Prv_dataClrWkpEventsInd_u32 != ECUM_NO_WKUP_SRC) && ((EcuM_Prv_dataClrWkpEventsInd_u32 &
            (EcuM_Prv_dataPndWkpEventsInd_u32 | EcuM_Prv_dataValWkpEventsInd_u32|EcuM_Prv_dataExpWkpEventsInd_u32)) ==
                    ECUM_NO_WKUP_SRC))
    {
        BswM_EcuM_CurrentWakeup (EcuM_Prv_dataClrWkpEventsInd_u32, ECUM_WKSTATUS_NONE);
    }

    SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
    EcuM_Prv_dataPndWkpEventsInd_u32 = ECUM_NO_WKUP_SRC;
    EcuM_Prv_dataValWkpEventsInd_u32 = ECUM_NO_WKUP_SRC;
    EcuM_Prv_dataClrWkpEventsInd_u32 = ECUM_NO_WKUP_SRC;
    EcuM_Prv_dataExpWkpEventsInd_u32 = ECUM_NO_WKUP_SRC;
    SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*leave Critical Sectiont*/

    /* Check whether any new wakeup event has occured. If so start the new wakeupsource using EcuM_StartWakeupSource api */
    if (dataPendingWakeupEvents_u32 != (EcuM_Prv_dataOldPendingWakeupEvents_u32&dataPendingWakeupEvents_u32))
    {
        EcuM_StartWakeupSources (EcuM_Prv_dataOldPendingWakeupEvents_u32 ^ dataPendingWakeupEvents_u32);
    }

    /*Update the EcuM_Prv_dataOldPendingWakeupEvents_u32 with the latest pending wakeup events, so that with
     * the next main cycle these sources are not getting started again*/
    EcuM_Prv_dataOldPendingWakeupEvents_u32 = dataPendingWakeupEvents_u32;

    }


/***********************************************************************************

  Function name :   EcuM_Prv_DecValidationCtr
  Description   :   Decrements the validation timeout counter value by 1 if it is greater than zero
  Parameter in  :   None
  Parameter out :
  Return value  :   void
  Remarks       :
 ************************************************************************************/
FUNC( void, ECUM_CODE ) EcuM_Prv_DecValidationCtr( void )
{

    /*This check is to perform to avoid sub zero value for wakeup validation timeout*/
    if (EcuM_Prv_WkpSrcValidationTimeoutCtr_u16 > 0)
    {
        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
        /*Decrement the validation timeout counter value*/
        EcuM_Prv_WkpSrcValidationTimeoutCtr_u16--;
        SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*leave Critical Sectiont*/
    }

}

/***********************************************************************************
  Function name :   EcuM_Prv_PBPointerConsistencyCheck
  Description   :   Function to check the consistency of the Post Build pointer. For this
                    purpose the pointer is checked against NULL Pointer, Invalid Pointer
                    and Pre Compile hash, subsequently Error hooks are thrown accordingly.
  Parameter in  :   void
  Parameter out :
  Return value  :   void
  Remarks       :
 ************************************************************************************/

FUNC( void, ECUM_CODE ) EcuM_Prv_PBPointerConsistencyCheck(void)
{
        /*local variables*/
        VAR (boolean,AUTOMATIC) flgupdateValid = FALSE;
        VAR(uint8, AUTOMATIC) cntrLoopCtr_u8;
        P2CONST(uint8, AUTOMATIC, ECUM_APPL_CONST) adrTempPBHashPtr_u8;

        if(EcuM_Rb_adrConfigPtr_st == NULL_PTR)
            {
                EcuM_ErrorHook( ECUM_E_NULL_PTR_RETURNED );
            }

            /*Check the selected post build pointer EcuM_Rb_adrConfigPtr_st, if it is a invalid pointer
             * ie.) a pointer which is not generated from configured EcuM Configsets*/
        for(cntrLoopCtr_u8 = 0;cntrLoopCtr_u8 < ECUM_NO_OF_ECUMCONFIGSETS; cntrLoopCtr_u8++)
        {
            if(EcuM_Rb_adrConfigPtr_st == EcuM_EcuMConfigurations_cpcast[cntrLoopCtr_u8])
            {
                flgupdateValid = TRUE;
                break;
            }

        }
        /*if the selected post build pointer is a invalid then call EcuM_ErrorHook() with ECUM_E_INVALID_PTR_RETURNED as
         * parameter*/
        if(flgupdateValid != TRUE)
        {
            EcuM_ErrorHook( ECUM_E_INVALID_PTR_RETURNED );
        }
        /*
         Checking consistency of configuration data
         The array of Hash values generated at the time of PB ,it's base address is moved to a local ptr
         */
        adrTempPBHashPtr_u8 = &(EcuM_Rb_adrConfigPtr_st->PostBuildHash[0]);
        for (cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 < ECUM_CFG_LENGTH_OF_HASH; cntrLoopCtr_u8++)
        {
            if( EcuM_Cfg_dataPreCompileHash_au8[cntrLoopCtr_u8] != adrTempPBHashPtr_u8[cntrLoopCtr_u8] )
            {
                /*Configuration check is failed and error hook is called here. It is up the
                system integrator to react accordingly.
                This function will never returns.*/
                EcuM_ErrorHook( ECUM_E_CONFIGURATION_DATA_INCONSISTENT );

            }
        }

}

/***********************************************************************************
  Function name :   EcuM_Prv_SetDefinedMcuWakeupSource
  Description   :   The reset reason is obtained from MCU and if it is a defined reset reason
                    the same reason is set as WakeupEvent in this method.
  Parameter in  :   void
  Parameter out :
  Return value  :   void
  Remarks       :
 ************************************************************************************/

FUNC( void, ECUM_CODE ) EcuM_Prv_SetDefinedMcuWakeupSource( void )
{

    VAR(Mcu_ResetType, AUTOMATIC) dataMcuResetReason_e = MCU_RESET_UNDEFINED;
    VAR(uint8, AUTOMATIC) cntrLoopCtr_u8;

    dataMcuResetReason_e = Mcu_GetResetReason();

    if (dataMcuResetReason_e != MCU_RESET_UNDEFINED)
    {
        /*loop through all the configured wkup source and find which one is the cause
                for reset by mapping the reset reason that is obtained from the MCU driver*/
        for ( cntrLoopCtr_u8 = 0; cntrLoopCtr_u8 < ECUM_NUM_OF_WKP_SOURCES; cntrLoopCtr_u8++ )
        {
            if ( EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].ResetReason == dataMcuResetReason_e )
            {
                /*Set the wakeup event for  wakeup sources which is mapped to the reset reason which
                 * matches with the Mcu reset reason*/
                EcuM_SetWakeupEvent( EcuM_Cfg_idxWakeupSourcesPC_au32[cntrLoopCtr_u8].WakeupSourceId );

            }

        }
    }
}
#if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
/***********************************************************************************
  Function name :   EcuM_Prv_StartSlaveCores
  Description   :   For Multicore configuration, the slave cores are started by the master core, if the core
                    starting failed ErrorHook is called with ECUM_E_START_CORE_FAILED .
  Parameter in  :   void
  Parameter out :
  Return value  :   void
  Remarks       :
 ************************************************************************************/
FUNC( void, ECUM_CODE ) EcuM_Prv_StartSlaveCores( void )
{
/*local variables*/
    VAR (StatusType,AUTOMATIC) dataStatus_chr = E_NOT_OK;
    VAR(uint16, AUTOMATIC) cntrLoopCtr_u16;
 /*Starting all the OS Cores in a loop*/


        for( cntrLoopCtr_u16=0; cntrLoopCtr_u16<ECUM_CFG_NUM_OS_CORES ; cntrLoopCtr_u16++ )
        {
            StartCore( cntrLoopCtr_u16, &dataStatus_chr);
            if(dataStatus_chr != E_OK)
            {
                /* StartCore Failed*/

                EcuM_ErrorHook(ECUM_E_START_CORE_FAILED);

            }
        }

}
#endif//ECUM_CFG_MULTICORE_ENABLE

/***********************************************************************************
  Function name :   EcuM_Prv_StartOS
  Description   :   After initialization the control is handed over to OS by the StartOS Macro with
                    the Default AppMode from the PB pointer.
  Parameter in  :   void
  Parameter out :
  Return value  :   void
  Remarks       :
 ************************************************************************************/
FUNC( void, ECUM_CODE ) EcuM_Prv_StartOS(void)
{
    StartOS( EcuM_Rb_adrConfigPtr_st->DefaultAppMode )
}

/***********************************************************************************
  Function name :   EcuM_Prv_hasCheckWakeupSourceGetHandle_b
  Description   :   To check whether the source is a configured known WakeupSource
                    to EcuM. If yes returns the ValidityFlag as TRUE.
  Parameter in  :   wakeup sources
  Parameter out :   None
  Return value  :   boolean
  Remarks       :
 ************************************************************************************/
FUNC(boolean, ECUM_CODE) EcuM_Prv_hasCheckWakeupSourceGetHandle_b( VAR(EcuM_WakeupSourceType, AUTOMATIC)datasource_u32 )
{
    /*Local variable declaration*/
    VAR(boolean, AUTOMATIC) flgValidity_b = FALSE;

    /* check all the configured wakeup sources with the passed wkup sources */
    if((datasource_u32 != ECUM_NO_WKUP_SRC) && ((ECUM_KNOWN_WAKEUP_SOURCES & datasource_u32) == datasource_u32) )
	{
	   flgValidity_b = TRUE;

	}
	else
	{
	   /*If any of the passed wakeup source(s) is not valid then the flgValidity_b value is ratained as FALSE*/
	}
    return flgValidity_b;
}

#if (ECUM_SLEEP_SUPPORT_ENABLE == TRUE)
/**********************************************************************************************************************
  Function name :   EcuM_Prv_GoSleepSequence
  Description   :   This api is common to EcuM_GoHalt and EcuM_GoPoll.In GoSleep sequence the ECU Manager module
                    configures hardware for the upcoming sleep phase and sets the ECU up for the next wakeup event.
  Parameter in  :   dataSleepModeHandle_u16 which has the index of the selected sleep mode in
                    EcuM_Cfg_idxSleepModes_au32 array
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *********************************************************************************************************************/
FUNC(void, ECUM_CODE) EcuM_Prv_GoSleepSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16)
                {

    /*Local variable declaration*/
    StatusType Os_api_returnvalue = E_NOT_OK;
    VAR( EcuM_WakeupSourceType, AUTOMATIC )  EcuM_dataPendingWakeupEvents_u32 = 0;
    VAR( EcuM_WakeupSourceType, AUTOMATIC )  EcuM_dataValidatedWakeupEvents_u32 = 0;
    VAR(EcuM_Prv_SleepType_Enum_ten, AUTOMATIC) RequestedSleepType_en;
    VAR( uint16, AUTOMATIC )  Core_ID = EcuM_Prv_CoreStatus_st.CurrentCoreID;

    if(((EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) && (FALSE != EcuM_Prv_AllCoreSleepReady_b)) ||
            (EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE))
    {
        /*Get a resource for EcuM so that it cannot be interrupted by other Os tasks*/
        Os_api_returnvalue = EcuM_Prv_GetResource (Core_ID);
    }
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
    else if((EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_SLAVE_CORE) && (FALSE == EcuM_Prv_flgSleepReady_ab[Core_ID]) &&
            (FALSE != EcuM_Prv_flgSleepReady_ab[ECUM_CFG_STARTUP_CORE]))
    {
        /*Get a resource for EcuM so that it cannot be interrupted by other Os tasks*/
        Os_api_returnvalue = EcuM_Prv_GetResource (Core_ID);
        /*update the core status that gosleep sequence executed successfully*/
         EcuM_Prv_flgSleepReady_ab[Core_ID] = TRUE;
    }
#endif//ECUM_CFG_MULTICORE_ENABLED
    else
    {

    }

    if(((Os_api_returnvalue == E_OK) && (EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE) &&
            (FALSE != EcuM_Prv_AllCoreSleepReady_b))||
            ((Os_api_returnvalue == E_OK) && (EcuM_Prv_CoreStatus_st.CurrentCore != ECUM_MASTER_CORE)))

    {
        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );             /*Enter Critical Section*/
        EcuM_dataPendingWakeupEvents_u32 = EcuM_Prv_dataPendingWakeupEvents_u32;
        EcuM_dataValidatedWakeupEvents_u32 = EcuM_Prv_dataValidatedWakeupEvents_u32;
        SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);                /*Leave Critical Section*/
        if((ECUM_NO_WKUP_SRC == EcuM_dataPendingWakeupEvents_u32) &&
                (ECUM_NO_WKUP_SRC == EcuM_dataValidatedWakeupEvents_u32))
        {
            /*Proceed with halting sequence in case of successful resource acquiring*/
            /*Getting Sleep Type in critical region*/
            SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );            /*Enter Critical Section*/
            RequestedSleepType_en = EcuM_Prv_SleepReqType_en;
            SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);               /*Leave Critical Section*/

            if(ECUM_PRV_GOHALT_E == RequestedSleepType_en)
            {
                EcuM_Prv_HaltingSequence(dataSleepModeHandle_u16);

            }
            else
            {
                //Should Not happen at all
            }

        }
        else
        {
            EcuM_Prv_WakeupRestartReason_en = ECUM_PRV_WAKEUP_REQUEST_E;

        }
    }

    else
    {
        EcuM_Prv_WakeupRestartReason_en = ECUM_PRV_RESOURCE_NOT_ACQUIRED_E;
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        /*report error for unsuccessful resource acquiring*/
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID, ECUM_E_OS_GET_RESOURCE_FAILED );
#endif//ECUM_DEV_ERROR_DETECT
    }

    /*if resource acquiring failed then quit from sleep sequence and
     * execute wakeup restart sequence for the cores where Gosleep sequence executed*/
    if((Os_api_returnvalue != E_OK)||(ECUM_PRV_NORMAL_E != EcuM_Prv_WakeupRestartReason_en ))
    {
        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );          /*Enter Critical Section*/
        /*signal for wakeup restart*/
        EcuM_Prv_flgwakeupRestart_b = TRUE;
        /*signal to quit sleep mode*/
        EcuM_Prv_SleepReqType_en = ECUM_PRV_NO_SLEEP_E;

        SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);             /*Leave Critical Section*/
    }
    return;
}

/**********************************************************************************************************************
  Function name :   EcuM_Prv_HaltingSequence
  Description   :   In Halting sequence, The ECU Manager module shall generate RAM content
                    Hash (callout) and enters into MCU halt mode.
                    In case Multicore, slave cores signals the master just before entering MCU halt mode.
                    Master core waits for all slave core to sleep and generates the Hash for RAM content
                    (system designer has to implement corresponding code for Hash computation).
  Parameter in  :   dataSleepModeHandle_u16 - the index of the selected sleep mode in EcuM_Cfg_idxSleepModes_au32 array
  Parameter out :   None
  Return value  :   None
  Remarks       :
 *********************************************************************************************************************/
static FUNC(void, ECUM_CODE) EcuM_Prv_HaltingSequence(VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16)
        {
    VAR( EcuM_Prv_OperationType_Enum_ten, AUTOMATIC )  flgOperation_en = ECUM_PRV_HALT_SEQUENCE_E;
    /*Internal variable which holds the bit mask of wakeup events that are in pending state*/
    EcuM_WakeupSourceType dataPendingWakeupEvents_u32 = ECUM_NO_WKUP_SRC;
    /*Internal variable which holds the bit mask of wakeup events that are in validated state*/
    EcuM_WakeupSourceType dataValidatedWakeupEvents_u32 = ECUM_NO_WKUP_SRC;

    /*update phase variable to indicate sleep mode*/
    EcuM_Prv_dataPresentPhase_u8 = ECUM_PRV_PHASE_SLEEP;

    EcuM_Prv_McuSetMode(EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].EquivalentMcuMode, flgOperation_en);

    if( (EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE)||
            (EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE))
    {
        if( (uint8)0 == EcuM_CheckRamHash())
        {
            /*Call the EcuM Error Hook, Because the RAM integrity check has failed.*/
            EcuM_ErrorHook(ECUM_E_RAM_CHECK_FAILED);
        }
    }

    /*Check for the occurence of wakeup events*/
    SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );        /*Enter Critical Section*/
    /*Get the latest PENDING events list*/
    dataPendingWakeupEvents_u32 = EcuM_Prv_dataPendingWakeupEvents_u32;
    /*Get the latest VALIDATED events list*/
    dataValidatedWakeupEvents_u32 = EcuM_Prv_dataValidatedWakeupEvents_u32;
    SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);           /*Leave Critical Section*/

    if (ECUM_NO_WKUP_SRC != (dataPendingWakeupEvents_u32 &
            EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask))
    {
        /*Indicate wake up status change to BswM as ECUM_WKSTATUS_PENDING*/
        BswM_EcuM_CurrentWakeup((dataPendingWakeupEvents_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_PENDING);

        /*Indication variable may get modified if any pending wakeup event associated with the current sleep mode
         * occurs. If so clear the variable to avoid multiple wakeup status indication to BswM*/
        EcuM_Prv_dataPndWkpEventsInd_u32 ^= (EcuM_Prv_dataPndWkpEventsInd_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
    }

    if(ECUM_NO_WKUP_SRC != (dataValidatedWakeupEvents_u32 &
                                                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask))
    {
        /*Indicate wake up status change to BswM as ECUM_WKSTATUS_VALIDATED*/
        BswM_EcuM_CurrentWakeup((dataValidatedWakeupEvents_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask),ECUM_WKSTATUS_VALIDATED);

        /*Indication variable may get modified if any wakeup source associated with the current sleep mode is validated.
         * If so clear the variable to avoid multiple wakeup status indication to BswM*/
        EcuM_Prv_dataValWkpEventsInd_u32 ^= (EcuM_Prv_dataValWkpEventsInd_u32 &
                EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask) ;

    }

#if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
    if(EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE)
    {
        /*Signal the slave to come out of Halt*/
        EcuM_Prv_RAMCheckPassed_b = TRUE;
    }
    else//if slave core
    {
        /*Waiting for the master core to continue*/
        while(FALSE == EcuM_Prv_RAMCheckPassed_b )
        {
            /*Looping here until master core checks for RAM Integerity*/
        }
    }

#endif//ECUM_CFG_MULTICORE_ENABLED

    /*Proceeding for Wakeup Restart Sequence*/
    EcuM_Prv_WakeupRestartSequence(dataSleepModeHandle_u16);
        }

/***********************************************************************************
  Function name :   EcuM_Prv_WakeupRestartSequence
  Description   :   It will perform the following operations. Restore Mcu to normal mode,
                    Initialize drivers that needs a restart and release the Os resource so that the other Os task
                    starts running.
  Parameter in  :   dataSleepModeHandle_u16 - the index of the selected sleep mode in EcuM_Cfg_idxSleepModes_au32 array
  Parameter out :   None
  Return value  :   none
  Remarks       :
 ************************************************************************************/
FUNC(void, ECUM_CODE)EcuM_Prv_WakeupRestartSequence ( VAR(uint16, AUTOMATIC) dataSleepModeHandle_u16 )
      {
    VAR(EcuM_WakeupSourceType, AUTOMATIC) dataWakeupSrcMask_u32 = ECUM_NO_WKUP_SRC;
    /*Local variable for storing the return value of os_GetResource()*/
    VAR(StatusType, AUTOMATIC) Os_api_returnvalue = E_NOT_OK;
    VAR(EcuM_Prv_OperationType_Enum_ten, AUTOMATIC) flgOperation_en = ECUM_PRV_RESTART_SEQUENCE_E;
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
    VAR(uint16, AUTOMATIC) cntrLoopOsCore_u16;

    if(FALSE != EcuM_Prv_flgSleepReady_ab[EcuM_Prv_CoreStatus_st.CurrentCoreID])
    {

#endif//ECUM_CFG_MULTICORE_ENABLED

        if (ECUM_PRV_NORMAL_E == EcuM_Prv_WakeupRestartReason_en)
        {
            EcuM_Prv_McuSetMode (ECUM_NORMAL_MCU_MODE, flgOperation_en);
        }

        dataWakeupSrcMask_u32 = EcuM_GetPendingWakeupEvents();
        /*[SWS_EcuM_04084] The ECU Manager module shall derive the wakeup sources to be disabled (and used as the
         *  wakeupSource parameter) from the internal pending events variable (NOT operation). The integration code
         * used for this callout must determine which wakeup sources must be disabled.*/
        dataWakeupSrcMask_u32 = (EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask &
                (~dataWakeupSrcMask_u32));

        EcuM_DisableWakeupSources(dataWakeupSrcMask_u32);

        if (ECUM_PRV_RESOURCE_NOT_ACQUIRED_E != EcuM_Prv_WakeupRestartReason_en)
        {
            if((EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE) ||
                    (EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE))
            {
                /*Re initialize the Drivers configured in Driver init restartlist in EcuM*/
                EcuM_AL_DriverRestart (EcuM_Rb_adrConfigPtr_st);
            }
            /*Release the resource for EcuM so that it cannot be interrupted by other Os tasks*/
            Os_api_returnvalue = EcuM_Prv_ReleaseResource (EcuM_Prv_CoreStatus_st.CurrentCoreID);
        }
        /*Enable the possibility of updating the shutdown target*/
        EcuM_Prv_flgShutdownInfoDoNotUpdate_b = FALSE;
        flgOperation_en = ECUM_PRV_CLEAR_SLEEP_E;
        EcuM_Prv_McuSetMode( (uint8) 0, flgOperation_en);


        if(Os_api_returnvalue != E_OK)
        {
            /*Report error if release resource failed*/
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_MAIN_FUNC_APIID,
                    ECUM_E_OS_RELEASE_RESOURCE_FAILED);
#endif//ECUM_DEV_ERROR_DETECT

        }
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
        /*clear the sleep ready flag after wakeup restart sequence executed*/
        EcuM_Prv_flgSleepReady_ab[EcuM_Prv_CoreStatus_st.CurrentCoreID] = FALSE;

    }
    /*clear wakeup restart flag once wakeup restart sequence executed for all the cores */
    for(cntrLoopOsCore_u16 = 0; cntrLoopOsCore_u16 < ECUM_CFG_NUM_OS_CORES ; cntrLoopOsCore_u16++)
    {
        if (FALSE != EcuM_Prv_flgSleepReady_ab[cntrLoopOsCore_u16])
        {
            EcuM_Prv_flgClearWakeupRestart_b = FALSE;
            break;
        }
        else
        {
#endif//ECUM_CFG_MULTICORE_ENABLED

            EcuM_Prv_flgClearWakeupRestart_b = TRUE;

#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
        }
    }
    if(TRUE == EcuM_Prv_flgClearWakeupRestart_b)
    {
#endif//ECUM_CFG_MULTICORE_ENABLED
        /*clear wakeup restart flag once wakeup restart sequence executed for all the cores */
        EcuM_Prv_flgwakeupRestart_b = FALSE;

        /*Set the wakeup Restart reason to Normal for next gopoll or gohalt request*/
        EcuM_Prv_WakeupRestartReason_en = ECUM_PRV_NORMAL_E;

        EcuM_Prv_flgClearWakeupRestart_b = FALSE;


#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
    }
#endif//ECUM_CFG_MULTICORE_ENABLED
      }

/***********************************************************************************
  Function name :   EcuM_Prv_McuSetMode
  Description   :   It will set the MCU mode to the one mapped with selected sleep mode
  Parameter in  :   Mode, flgOperation_en
  Parameter out :   None
  Return value  :   void
  Remarks       :
 ************************************************************************************/

static FUNC( void, ECUM_CODE)EcuM_Prv_McuSetMode( VAR(uint8, AUTOMATIC) Mode, VAR(EcuM_Prv_OperationType_Enum_ten, AUTOMATIC) flgOperation_en)
{
    /*Local variable declaration*/
    /*if halting sequence operation for Master core or Single core*/
    if((flgOperation_en == ECUM_PRV_HALT_SEQUENCE_E) &&
            ((EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_SINGLE_CORE) ||
                    (EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_MASTER_CORE)))
    {
        /* Disable all interrupts before changing the Mcu Mode*/
        DisableAllInterrupts ();
        /*Callout (to be implemented by System designer) which calculates the Hash/checksum of RAM contents*/
        EcuM_GenerateRamHash();
        /*Change Mcu mode with the Mcu mode mapped with the selected sleep mode.*/
        Mcu_SetMode(Mode);
        /* Enable all interrupts after changing the Mcu Mode*/
        EnableAllInterrupts();

    }
#if(ECUM_CFG_MULTICORE_ENABLED  ==  STD_ON)
    else if( (flgOperation_en == ECUM_PRV_HALT_SEQUENCE_E) &&  (EcuM_Prv_CoreStatus_st.CurrentCore == ECUM_SLAVE_CORE))
    {
        /* Disable all interrupts before changing the Mcu Mode*/
        DisableAllInterrupts();
        /*Restore Mcu functioning to normal Mcu mode.*/
        Mcu_SetMode(Mode);
        /*Enable All the interrupts*/
        EnableAllInterrupts();
    }
#endif//ECUM_CFG_MULTICORE_ENABLED
    else
    {

    }
 if(flgOperation_en == ECUM_PRV_RESTART_SEQUENCE_E)
    {
        /*Disable all interrupts before changing the Mcu Mode*/
        DisableAllInterrupts ();
        /*Change Mcu mode with the Mcu mode mapped with the selected sleep mode.*/
        Mcu_SetMode(Mode);
        /* Enable all interrupts after changing the Mcu Mode*/
        EnableAllInterrupts();
    }
    else if ((flgOperation_en == ECUM_PRV_CLEAR_SLEEP_E))
    {
        /*wakeup restart signal to slave cores */
        EcuM_Prv_flgwakeupRestart_b = TRUE;
        SchM_Enter_EcuM(ECUM_SCHM_EXCLSV_AREA);       /*enter Critical Section*/
        /*clear Sleep type flag to quit sleep mode*/
        EcuM_Prv_SleepReqType_en        = ECUM_PRV_NO_SLEEP_E;
        SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA);        /*Leave Critical Section*/
    }
    else
    {
        //nothing to be executed here
    }
    return ;
}
#endif//ECUM_SLEEP_SUPPORT_ENABLE


/***********************************************************************************
  Function name :   EcuM_Prv_ComMWakeupHandling
  Description   :   This service will indicate to ComM module if for a particular wakeup Communication Channel is
                    configured and  Validation is off and whether if ComMPNC Channel Reference is associated with the wakeup source
  Parameter in  :   dataPendingWakeupEvents
  Parameter out :   None
  Return value  :   uint32
  Remarks       :
 ************************************************************************************/
FUNC(uint32, ECUM_CODE)EcuM_Prv_ComMWakeupHandling (VAR( EcuM_WakeupSourceType,AUTOMATIC )  dataPendingWakeupEvents)
        {
    // Variable used to hold only the wakeup sources with Comm channel reference from the passed sources
    VAR(uint32, AUTOMATIC) EcuM_CommchlWkupEvents_u32 = 0;
    VAR(uint8, AUTOMATIC) ctrLoop_u8 = 0;
    VAR(uint8, AUTOMATIC) ctrLoopPNCNotify_u8 = 0;
    /* splitting the wakeup events which are having comm channel reference */
    for( ctrLoop_u8 = 0;ctrLoop_u8 < ECUM_NUM_OF_WKP_SOURCES;ctrLoop_u8++ )
    {

        /* indicate to ComM module if Communication Channel is configured and  Validation is off */
        if ( ( ( dataPendingWakeupEvents & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != ECUM_NO_WKUP_SRC ) \
                && ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].IsComChannelPresent == TRUE ) )
        {

            ComM_EcuM_WakeUpIndication ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].ComChannelReferance );
            EcuM_CommchlWkupEvents_u32 |= EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId;

        }

        /* indicate to ComM module if ComMPNC Channel Reference is associated with the wakeup source */
        if ( ( ( dataPendingWakeupEvents & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != ECUM_NO_WKUP_SRC ) \
                && ( EcuM_Rb_adrConfigPtr_st->adrWkupPNCRefs[ctrLoop_u8].nbrOfComMPNCRef > 0 ) )
        {

            for ( ctrLoopPNCNotify_u8 = 0; ctrLoopPNCNotify_u8 <  (EcuM_Rb_adrConfigPtr_st->adrWkupPNCRefs[ctrLoop_u8].nbrOfComMPNCRef); ctrLoopPNCNotify_u8++)
            {
                ComM_EcuM_PNCWakeUpIndication(EcuM_Rb_adrConfigPtr_st->adrWkupPNCRefs[ctrLoop_u8].ListOfPNCRefs[ctrLoopPNCNotify_u8]);
            }

        }

    }

    return EcuM_CommchlWkupEvents_u32;
        }
#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

