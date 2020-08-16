


#include "EcuM.h" /*BSW_HeaderInc_002*/


#if (ECUM_SLEEP_SUPPORT_ENABLE != FALSE)

/*Headers generated from EcuM SWCD or BSWMD file*/
#include "SchM_EcuM.h"


#include "EcuM_Cfg_SchM.h"

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

/*********************************************************************************************************************
  Function name :   EcuM_GoHalt
  Description   :   Instructs the ECU State Manager module to go into a sleep mode where the micro controller is halted,
                    depending on the selected shutdown target.
  Parameter in  :   None
  Parameter out :   None
  Return value  :   Std_ReturnType.
  Remarks       :   This call is NOT Synchronous call. It is implemented as asysnchronous call.
 *********************************************************************************************************************/
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GoHalt(void)
{

    /*Local variable declaration*/
    #if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
    VAR(uint16, AUTOMATIC) cntrLoopOsCore_u16=0;
    #endif//ECUM_CFG_MULTICORE_ENABLED

    VAR(boolean, AUTOMATIC) FlagGoHaltCalledAgain_b = FALSE;
    VAR(Std_ReturnType, AUTOMATIC) return_value = E_NOT_OK;

    /*Internal Variable to hold the sleep mode and intiliaze with invalid value of 0xFF */
    VAR(EcuM_ShutdownModeType, AUTOMATIC) SleepMode_u16 =0xFF;

    /*Internal Variable to hold the shutdown target and intiliaze with invalid value*/
    VAR(EcuM_ShutdownTargetType, AUTOMATIC) shutdownTarget_u8 = ECUM_SHUTDOWN_TARGET_RESET;

    /*DET raised for service called before EcuM Initialised */
    if (FALSE != EcuM_Prv_flgIsModuleInitialised_b)
    {
        /*Check for completion of wakeup restart, incase ECU is restart phase*/
        if(FALSE == EcuM_Prv_flgwakeupRestart_b)
        {
                SchM_Enter_EcuM(ECUM_SCHM_EXCLSV_AREA); /*Enter Critical Section*/
                /*Check for the EcuM_GoPoll or EcuM_GoHalt has not been called*/
                if(ECUM_PRV_NO_SLEEP_E == EcuM_Prv_SleepReqType_en)
                {
                    /*Get the selected shutdown target and mode*/
                    shutdownTarget_u8 = EcuM_Prv_dataSelectedShutdownTarget_st.ShutdownTarget;
                    SleepMode_u16 = EcuM_Prv_dataSelectedShutdownTarget_st.mode;

                        if ((ECUM_SHUTDOWN_TARGET_SLEEP == shutdownTarget_u8 ) && (SleepMode_u16 <
                                ECUM_CFG_NUM_SLEEP_MODES) &&
                                (TRUE == EcuM_Cfg_idxSleepModes_au32[SleepMode_u16].IsCPUSuspend) &&
                                    (ECUM_NO_WKUP_SRC != EcuM_Cfg_idxSleepModes_au32[SleepMode_u16].WakeupSourceMask ))
                        {
                            EcuM_Prv_SleepReqType_en = ECUM_PRV_GOHALT_E;
                            EcuM_Prv_WakeupRestartReason_en = ECUM_PRV_NORMAL_E;
                            /*Disable the possiblity of updating the shutdown target*/
                            EcuM_Prv_flgShutdownInfoDoNotUpdate_b = TRUE;
                            return_value= E_OK;
                        }
                }//if(ECUM_PRV_NO_SLEEP_E == EcuM_Prv_SleepReqType_en)
                else
                {
                    /*Check for the repeated Call of EcuM_GoHalt*/
                    if(ECUM_PRV_GOHALT_E == EcuM_Prv_SleepReqType_en)
                    {

                        FlagGoHaltCalledAgain_b= TRUE;
                        return_value= E_OK;

                    }//if(ECUM_PRV_GOHALT_E == EcuM_Prv_SleepReqType_en)
                    else
                    {
                        /*EcuM_GoPoll has been called already, Hence EucM_GoHalt cann't be processed*/
                    }
                }
                SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*leave Critical Section*/
        }//if(FALSE == EcuM_Prv_flgwakeupRestart_b)
        else
        {

        }

    }//if (TRUE == EcuM_Prv_flgIsModuleInitialised_b)
    else
    {
        #if (ECUM_DEV_ERROR_DETECT == STD_ON)
          (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GOHALT_APIID, ECUM_E_UNINIT);
        #endif//ECUM_DEV_ERROR_DETECT

    }
    if((FALSE == FlagGoHaltCalledAgain_b) && (E_OK == return_value  ))
    {

          #if(ECUM_CFG_MULTICORE_ENABLED == STD_ON)
            for(cntrLoopOsCore_u16 = 0;cntrLoopOsCore_u16 < ECUM_CFG_NUM_OS_CORES ; cntrLoopOsCore_u16++)
            {
                EcuM_Prv_flgSleepReady_ab[cntrLoopOsCore_u16] = FALSE;
            }
          #endif//ECUM_CFG_MULTICORE_ENABLED

          SchM_Enter_EcuM(ECUM_SCHM_EXCLSV_AREA); /*Enter Critical Section*/

          /*update the Sleep Mode*/
          EcuM_Prv_SleepMode_u16 = SleepMode_u16;

          SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*leave Critical Section*/

    }

    return return_value;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

#endif//ECUM_SLEEP_SUPPORT_ENABLE
