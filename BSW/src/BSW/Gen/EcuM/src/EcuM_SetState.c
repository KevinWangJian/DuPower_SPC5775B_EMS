

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/



#include "EcuM.h"

#if (ECUM_CFG_MODE_HANDLING == STD_ON)



#include "EcuM_Cfg_SchM.h"

/*Extern module Headers*/
#if(ECUM_DEV_ERROR_DETECT == STD_ON)/*Det included when Det is enabled in EcuM*/
#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif
#endif/*ECUM_DEV_ERROR_DETECT*/

#include "EcuM_Prv.h"

/*EcuM Private headers*/
#include "EcuM_Prv_RteActions.h"

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

/*******************************************************************************************************************
  Function name :   EcuM_SetState
  Description   :   Function called by BswM to notify about State Switch.
  Parameter in  :   EcuM_StateType state
  Parameter out :   None
  Return value  :   void
  Remarks       :  None
 *********************************************************************************************************************/
FUNC(void , ECUM_CODE) EcuM_SetState( VAR(EcuM_StateType, AUTOMATIC) state)
{


    /*When the service is called before the EcuM module initialized then DET has to be reported with error ECUM_E_UNINIT*/
    if (TRUE != EcuM_Prv_flgIsModuleInitialised_b)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SETSTATE_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT
    }
    else
    {
        /*As per SWS_EcuM_04116 - EcuM should indicate the corresponding mode to the RTE with respect to the given State */


        switch(state)
        {
            /*Mode STARTUP to be notified when State ECUM_STATE_STARTUP is set*/
            case ECUM_STATE_STARTUP:

                (void)EcuM_Prv_RteModeSwitch(RTE_MODE_EcuM_Mode_STARTUP);
                break;
            /*Mode RUN to be notified when State ECUM_STATE_APP_RUN is set*/
            case ECUM_STATE_APP_RUN:

                (void)EcuM_Prv_RteModeSwitch(RTE_MODE_EcuM_Mode_RUN);
                break;
            /*Mode POST_RUN to be notified when State ECUM_STATE_APP_POST_RUN is set*/
            case ECUM_STATE_APP_POST_RUN:

                (void)EcuM_Prv_RteModeSwitch(RTE_MODE_EcuM_Mode_POST_RUN);
                break;
           /*Mode SHUTDOWN to be notified when State ECUM_STATE_SHUTDOWN is set*/
            case ECUM_STATE_SHUTDOWN:

                (void)EcuM_Prv_RteModeSwitch(RTE_MODE_EcuM_Mode_SHUTDOWN);
                break;

           /*Mode SLEEP to be notified when State ECUM_STATE_SLEEP is set*/
           case ECUM_STATE_SLEEP:

                (void)EcuM_Prv_RteModeSwitch(RTE_MODE_EcuM_Mode_SLEEP);
                 break;
                /*When the State parameter is unkown or invalid then error ECUM_E_STATE_PAR_OUT_OF_RANGE to be
                 * reported to DET*/
            default :
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                   (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SETSTATE_APIID, ECUM_E_STATE_PAR_OUT_OF_RANGE );
#endif//ECUM_DEV_ERROR_DETECT
                   break;


        }

   }

    return;

}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"


#else
/*This file is disabled because EcuM Mode handling feature is disabled */
#endif
