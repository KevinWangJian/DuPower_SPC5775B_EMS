

/*
**********************************************************************************************************************
* Includes
**********************************************************************************************************************
*/

#include "EcuM.h" /*BSW_HeaderInc_002*/



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

#include "BswM_EcuM.h"
#if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif


/*EcuM Private headers*/
#include "EcuM_Prv.h"
#include "EcuM_Prv_RteActions.h"

//FUNC(void, BSWM_CODE) BswM_EcuM_CurrentState(VAR(uint8, AUTOMATIC) CurrentState);

#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"


/*******************************************************************************************************************
  Function name :   EcuM_RbCurrentState
  Description   :   Function called by RTE mode switch acknowledgement event.
                    It reads the current RTE mode and provides a mapping between mode to state and notify the BswM about current state.
                    (To To prevent, that the mode machine instance of ECU Mode lags behind and the states EcuM and the
                     RTE get out of phase, the EcuM uses acknowledgement feedback for the mode switch notification.EcuM_RbCurrentState
                     configured as a Runnable in the Acknowledgement event of RTE mode switch.)
  Parameter in  :   void
  Parameter out :   None
  Return value  :   void
  Remarks       :  None
 *********************************************************************************************************************/

FUNC(void , ECUM_CODE) EcuM_Rb_CurrentState(void)
{

    VAR(uint8, AUTOMATIC) return_value;

    /*When the service is called before the EcuM module initialized then DET has to be reported with error ECUM_E_UNINIT*/
    if ( TRUE != EcuM_Prv_flgIsModuleInitialised_b )
    {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )

        ( void )Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_RB_CURRENTSTATE_APIID, ECUM_E_UNINIT );

#endif

    }
    else
    {

        /* Getting the RTE mode information after the mode switch from EcuM_Currentmode P-Port*/

        return_value = EcuM_Prv_GetRteMode();

        switch( return_value )
        {
            /*When RTE mode is STRATUP - BswM will be notified with State ECUM_STATE_STARTUP*/
            case RTE_MODE_EcuM_Mode_STARTUP:
                BswM_EcuM_CurrentState( ECUM_STATE_STARTUP );
                break;
                /*When RTE mode is RUN - BswM will be notified with State ECUM_STATE_APP_RUN*/
            case RTE_MODE_EcuM_Mode_RUN:
                BswM_EcuM_CurrentState( ECUM_STATE_APP_RUN );
                break;
                /*When RTE mode is POST_RUN - BswM will be notified with State ECUM_STATE_APP_POST_RUN*/
            case RTE_MODE_EcuM_Mode_POST_RUN:
                BswM_EcuM_CurrentState( ECUM_STATE_APP_POST_RUN );
                break;
                /*When RTE mode is SHUTDOWN - BswM will be notified with State ECUM_STATE_STARTUP*/
            case RTE_MODE_EcuM_Mode_SHUTDOWN:
                BswM_EcuM_CurrentState( ECUM_STATE_SHUTDOWN );
                break;
                /*When RTE mode is SLEEP - BswM will be notified with State ECUM_STATE_SLEEP*/
            case RTE_MODE_EcuM_Mode_SLEEP:
                BswM_EcuM_CurrentState( ECUM_STATE_SLEEP );
                break;


            default :
                //nothing to be executed here
                break;

        }
    }

    return;

}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"


#else
/*This file is disabled because EcuM Mode handling feature is disabled */
#endif//ECUM_CFG_MODE_HANDLING





