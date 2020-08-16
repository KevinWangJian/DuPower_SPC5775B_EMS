

#include "EcuM.h" /*BSW_HeaderInc_002*/

#include "EcuM_Callout.h"



#include "EcuM_Cfg_SchM.h"

#include "EcuM_RunTime.h" /*For run time measurement*/

/*Extern module Headers*/
#include "Mcu.h" 		/* specified in SWS.*/
#if (!defined(MCU_AR_RELEASE_MAJOR_VERSION) || (MCU_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(MCU_AR_RELEASE_MINOR_VERSION) || (MCU_AR_RELEASE_MINOR_VERSION != 2))
//#error "AUTOSAR minor version undefined or mismatched"
#endif

#include "Os.h" 		/* specified in SWS.*/
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
#include "EcuM_Prv.h"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

/***********************************************************************************

  Function name :   Std_ReturnType EcuM_GoDown( caller )
  Description   :   Instructs the ECU State Manager module to perform a power off or a reset
                    depending on the selected shutdown target.
  Parameter in  :   Caller
  Parameter out :   None
  Return value  :   Std_ReturnType
  Remarks       :
 ************************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoDown( VAR(uint16, AUTOMATIC) caller)
{
    /*Local Variables*/
    VAR(boolean, AUTOMATIC) flgModuleValid_b = FALSE;
    VAR(uint8, AUTOMATIC) cntrLoop_u8;

    VAR(Std_ReturnType, AUTOMATIC) return_value;

    /*EcuM_GoDown should not be called before init*/
    if ( EcuM_Prv_flgIsModuleInitialised_b == FALSE )
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GODOWN_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT

        return_value = E_NOT_OK;
    }
    else
    {
        /*Check for the repeated Call of EcuM_GoDown*/
        if(EcuM_Prv_flgGoDown_b != FALSE)
        {
            /*If GoDown is already in process, no action should be taken*/
            return_value = E_OK;
        }
        else
        {
            /* The validity of the module needs to be checked as only configured modules are allowed to call this function*/
            for (cntrLoop_u8 = 0; cntrLoop_u8 < ECUM_CFG_GODOWN_CALLER_ARR_LEN; cntrLoop_u8++)
            {
                if (EcuM_Cfg_idxGoDownValidCallerArr_au16[cntrLoop_u8] == caller)
                {
                    flgModuleValid_b = TRUE;
                    break;
                }
            }

            /* If the module not valid to call this function, return E_NOT_OK */
            if( flgModuleValid_b == FALSE)
            {

                return_value =  E_NOT_OK;
            }
            else
            {

                /* check if the selected shutdown target and mode is proper or not */
                /*getting the shutdown target and mode*/
                SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
                if( !(((EcuM_Prv_dataSelectedShutdownTarget_st.ShutdownTarget) == ECUM_SHUTDOWN_TARGET_OFF)
                        || (((EcuM_Prv_dataSelectedShutdownTarget_st.ShutdownTarget) == ECUM_SHUTDOWN_TARGET_RESET)))) /* check for selected shutdown target */
                {
                    return_value = E_NOT_OK;
                }
                else
                {

                    /*Set the flag to make the GoDown valid. This flag will be read in EcuM_MainFunction to proceed to shutdown*/
                    EcuM_Prv_flgGoDown_b   =   TRUE;
                    /*The shutdown Info should not be changed once GoDown initiated.*/
                    EcuM_Prv_flgShutdownInfoDoNotUpdate_b = TRUE;

                    EcuM_Prv_dataPresentPhase_u8 = ECUM_PRV_PHASE_OFF_PREOS;
                    return_value = E_OK;
#if (ECUM_STARTUP_DURATION == TRUE) /*will activate the Run time measurement*/
EcuM_Shutdown_begin_ticks_u64 =  EcuM_GetTicks();
#endif
                }
                SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Exit Critical Section*/

        }

    }
    }
    return return_value;

}

/***********************************************************************************

 Function name	:	void EcuM_Shutdown (void)
 Description	:	The final steps to reach the shutdown target after the OS has been
					shutdown is taken care by this function.
 Parameter in	:	None
 Parameter out	:   None
 return    		:	void
 ************************************************************************************/

FUNC(void , ECUM_CODE) EcuM_Shutdown(void )
{
    #if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
    /* MR12 RULE 8.4 VIOLATION: The declaration of GetCoreID is expected from Os */
    if(GetCoreID() == ECUM_CFG_STARTUP_CORE)
    {
    #endif//ECUM_CFG_MULTICORE_ENABLED
	      /*Check if module was initialized*/
	    if ( EcuM_Prv_flgIsModuleInitialised_b == FALSE )
        {
            #if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SHUTDOWN_APIID, ECUM_E_UNINIT );
            #endif  /* ECUM_DEV_ERROR_DETECT */
			return; /*EcuM_Shutdown function cannot return*/
        }
	    EcuM_Prv_dataPresentPhase_u8 = ECUM_PRV_PHASE_OFF_POSTOS;
       /*This call allows the system designer to notify that the GO OFF II state is about to be entered.*/
        EcuM_OnGoOffTwo();
        /* For ShutdownTarget selected as RESET*/
        if(EcuM_Prv_dataSelectedShutdownTarget_st.ShutdownTarget == ECUM_SHUTDOWN_TARGET_RESET)
        {
            /* Callout for resetting the ECU*/
            EcuM_AL_Reset( (EcuM_ResetType) EcuM_Prv_dataSelectedShutdownTarget_st.mode);
        }
        else
        {
            EcuM_AL_SwitchOff();/* Callout for switching OFF the ECU*/
        }
    #if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
    }
    #endif//ECUM_CFG_MULTICORE_ENABLED
}


#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

