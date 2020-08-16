

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/


#include "EcuM.h"                    /*BSW_HeaderInc_002*/



#include "EcuM_Cfg_SchM.h"

/*Extern module Headers*/
#include "NvM.h"                    /*for setramblockstatus api*/
#if (!defined(NVM_AR_RELEASE_MAJOR_VERSION) || (NVM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(NVM_AR_RELEASE_MINOR_VERSION) || (NVM_AR_RELEASE_MINOR_VERSION != 2))
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
#endif                             /*ECUM_DEV_ERROR_DETECT*/



/*EcuM Private headers*/
#include "EcuM_Prv.h"



#define ECUM_START_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

/***********************************************************************************

  Function name :   Std_ReturnType EcuM_SelectShutdownCause( EcuM_ShutdownCauseType shutdownCause )
  Description   :   Elects the cause for a shutdown and it is a part of the ECU Manager Module port interface.
  Parameter in  :   shutdownCause
  Parameter out :   None
  Return value  :   Std_ReturnType
  Remarks       :
 ************************************************************************************/

FUNC( Std_ReturnType, ECUM_CODE ) EcuM_SelectShutdownCause( VAR(EcuM_ShutdownCauseType, AUTOMATIC) shutdownCause )
{

    /*local variable declaration*/
    VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;

    /*If the service is called before Init then return E_NOT_OK. This is because during Init ECUM_CAUSE_ECU_STATE is
     assigned */
    if ( TRUE == EcuM_Prv_flgIsModuleInitialised_b  )
    {

        /*The service shall not update the shutdown cause once GoDown,GoPoll,GoHalt is initiated.
         * This is because if any change in shutdown target is allowed, then there will be inconsistencies in the
         * shutdown info which is stored and the actual*/
        if    (FALSE == EcuM_Prv_flgShutdownInfoDoNotUpdate_b )
        {
            /* checking if the parameter passed is a valid shutdown cause*/
            /* update the shutdown cause */
            if(shutdownCause < ECUM_CFG_NUM_SHUTDOWN_CAUSE)
            {

                SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/

                EcuM_Prv_dataSelectedShutdownCause_u8 = shutdownCause;
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)

                /*update the RAM variable in NV memory to the current shutdown target*/
                EcuM_Rb_dataShutdownInfo_st.ShutdownInfo.ShutdownCause =EcuM_Prv_dataSelectedShutdownCause_u8;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

                SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Exit Critical Section*/

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                /*Setting RAM block status for shutdown info block of NvM */
                (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);

#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED


                returnvalue_u8 = E_OK;
            }
            else
            {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                /*Report error to DET if the passed shutdown cause is invalid*/
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID ,
                        ECUM_E_INVALID_PAR);
#endif //ECUM_DEV_ERROR_DETECT

            }
        }
        else
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            /*Report error to DET if select shutdown cause is called after the shutdown info update*/
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID ,
                    ECUM_E_SHUTDOWN_INFO_UPDATED);
#endif //ECUM_DEV_ERROR_DETECT
        }

    }
    else
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        /*Report error to DET if select shutdown cause is called before EcuM Module is initialized*/
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT

    }

    return returnvalue_u8;

}

/***********************************************************************************

  Function name :   Std_ReturnType EcuM_GetShutdownCause( EcuM_ShutdownCauseType * shutdownCause )
  Description   :   Returns the selected shutdown cause as set by EcuM_SelectShutdownCause
                    and it is a part of the ECU Manager Module port interface.
  Parameter in  :   shutdownCause
  Parameter out :   None
  Return value  :   Std_ReturnType
  Remarks       :
 ************************************************************************************/

FUNC( Std_ReturnType, ECUM_CODE ) EcuM_GetShutdownCause(
          P2VAR(EcuM_ShutdownCauseType, AUTOMATIC, ECUM_APPL_DATA) shutdownCause )
        {
    /*
            If the service is called before Init then return E_NOT_OK.
            This is because After Os start only the SchM_Enter_EcuM and
            SchM_Exit_EcuM will be available.As the Os start will be only after EcuM_Init
            the check for EcuM_Prv_flgIsModuleInitialised_b is mandatory.
     */

    VAR(Std_ReturnType, AUTOMATIC) return_value_u8= E_NOT_OK;
    if (FALSE == EcuM_Prv_flgIsModuleInitialised_b)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    else
    {
        /* Parameter Checking */
        if(shutdownCause == NULL_PTR)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_CAUSE_APIID, ECUM_E_NULL_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
        }
        else
        {
            SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
            *shutdownCause = EcuM_Prv_dataSelectedShutdownCause_u8;
            SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Exit Critical Section*/

            return_value_u8 = E_OK;
        }
    }

    return return_value_u8;
        }


/***********************************************************************************

  Function name :   Std_ReturnType EcuM_SelectShutdownTarget( EcuM_ShutdownTargetType shutdownTarget,
                                                              EcuM_ShutdownModeType shutdownMode )
  Description   :   Selects the shutdown target and it is part of the ECU Manager Module port interface.
  Parameter in  :   shutdownTarget, shutdownMode
  Parameter out :   None
  Return value  :   Std_ReturnType
  Remarks       :
 ************************************************************************************/

FUNC(Std_ReturnType, ECUM_CODE) EcuM_SelectShutdownTarget(
        VAR(EcuM_ShutdownTargetType, AUTOMATIC) shutdownTarget,
        VAR(EcuM_ShutdownModeType, AUTOMATIC) shutdownMode )
        {
    /*local variable declaration*/
    VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;

    /* If the service is called before Init then return E_NOT_OK. This is because during Startup operation, the
     * shutdown target will be updated with default shutdown target, if the service called before Init then the
     * selected shutdown target will be over written with the default shutdown target.
     */
    if (TRUE == EcuM_Prv_flgIsModuleInitialised_b)
    {
        /* Check if Shutdown target could be updated or not*/
        if(FALSE == EcuM_Prv_flgShutdownInfoDoNotUpdate_b)
        {
#if ECUM_SLEEP_SUPPORT_ENABLE
            /*check if the requested target is sleep with correct sleep mode*/
            if ((shutdownTarget == ECUM_SHUTDOWN_TARGET_SLEEP)&& (shutdownMode < ECUM_CFG_NUM_SLEEP_MODES))
            {
                returnvalue_u8   =   E_OK;
            }
            /*check if the requested target is Off/Reset with correct reset mode*/
            else
            {
#endif/*ECUM_SLEEP_SUPPORT_ENABLE */
            if( ((shutdownTarget == ECUM_SHUTDOWN_TARGET_RESET) && ( shutdownMode < ECUM_CFG_NUM_RESET_MODES)) ||
                    (shutdownTarget == ECUM_SHUTDOWN_TARGET_OFF))
            {
                returnvalue_u8   =   E_OK;
            }
            else
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                /*Report to DET if the requested target/mode does not match with the configured targets/modes*/
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID ,
                                                                        ECUM_E_STATE_PAR_OUT_OF_RANGE);
#endif //ECUM_DEV_ERROR_DETECT
            }
#if ECUM_SLEEP_SUPPORT_ENABLE
        }
#endif/*ECUM_SLEEP_SUPPORT_ENABLE */
            if (E_OK == returnvalue_u8)
            {
                SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
                EcuM_Prv_dataSelectedShutdownTarget_st.ShutdownTarget = shutdownTarget;
                if ((shutdownTarget == ECUM_SHUTDOWN_TARGET_RESET)||
                        (shutdownTarget == ECUM_SHUTDOWN_TARGET_SLEEP))
                {
                    EcuM_Prv_dataSelectedShutdownTarget_st.mode = shutdownMode;
                }
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                /*update the RAM variable in NV memory to the current shutdown target*/
                EcuM_Rb_dataShutdownInfo_st.ShutdownTarget=EcuM_Prv_dataSelectedShutdownTarget_st.ShutdownTarget;
                EcuM_Rb_dataShutdownInfo_st.mode=EcuM_Prv_dataSelectedShutdownTarget_st.mode;
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
                SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Exit Critical Section*/
#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
                /*Setting RAM block status for shutdown info block of NvM */
                /*The return value of NvM_SetRamBlockStatus is not considered with the assumption that failed cases
                 * are taken care in NvM. The sevice can be failed in cases like NvM not initialized or passed Id
                 * already in Queue or passed id is out of range. In all these cases corresponding DET will be raised
                 * directly from NvM module.*/
                (void)NvM_SetRamBlockStatus(NvMConf_NvMBlockDescriptor_ECUM_CFG_NVM_BLOCK,TRUE);
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED
            }
            else
            {
                //nothing to be executed here
            }


        }


        else
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            /*Report error to DET if select shutdown target is called after the shutdown info update*/
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID ,
                                                                    ECUM_E_SHUTDOWN_INFO_UPDATED);
#endif //ECUM_DEV_ERROR_DETECT

        }


    }

    else
    {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        /*Report error to DET if select shutdown target is called before EcuM Module is initialized*/
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SELECT_SHUT_TAR_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT

    }

    return returnvalue_u8;
        }

/***********************************************************************************

  Function name :   Std_ReturnType EcuM_GetShutdownTarget( EcuM_ShutdownTargetType * shutdownTarget,
                                                           EcuM_ShutdownModeType * shutdownMode )
  Description   :   Returns the currently selected shutdown target as set by EcuM_SelectShutdownTarget
                    and it is part of the ECU Manager Module port interface.
  Parameter in  :   shutdownTarget, shutdownMode
  Parameter out :   None
  Return value  :   Std_ReturnType
  Remarks       :
 ************************************************************************************/

FUNC( Std_ReturnType, ECUM_CODE ) EcuM_GetShutdownTarget(
          P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
          P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode)
                        {
    /* Local Variable Declaration */
    VAR(EcuM_ShutdownTargetType, AUTOMATIC) dataShutdownTarget_u8;
    VAR(EcuM_ShutdownModeType, AUTOMATIC) dataMode_u16;

    VAR(Std_ReturnType, AUTOMATIC) return_value_u8 = E_NOT_OK;
    /*check if module is initialized.
          This will ensure that at least the default shutdown target is set*/
    if(FALSE == EcuM_Prv_flgIsModuleInitialised_b)
    {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_UNINIT);
#endif //ECUM_DEV_ERROR_DETECT

    }
    else
    {
        /*parameter checking for target*/
        if (shutdownTarget == NULL_PTR)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_NULL_POINTER);
#endif//ECUM_DEV_ERROR_DETECT
        }
        else
        {
            /*Initialization of Local Variables*/
            SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/
            dataShutdownTarget_u8   =   EcuM_Prv_dataSelectedShutdownTarget_st.ShutdownTarget;
            dataMode_u16         =   EcuM_Prv_dataSelectedShutdownTarget_st.mode;
            SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA );      /*Exit Critical Section*/

            /* The shutdown targetparameter is given as OUT parameter*/
            *shutdownTarget   =   dataShutdownTarget_u8;

            /*[SWS_EcuM_02788] If the pointer to the shutdownMode parameter is NULL, EcuM_GetShutdownTarget shall simply
             * ignore the shutdownMode parameter. If Default Error Detection is activated, EcuM_GetShutdownTarget
             *  shall send the ECUM_E_PARAM_POINTER development error to the DET module.*/
            if (shutdownMode == NULL_PTR)
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_SHUT_TAR_APIID, ECUM_E_PARAM_POINTER);
#endif //ECUM_DEV_ERROR_DETECT
            }

            else if((dataShutdownTarget_u8 == ECUM_SHUTDOWN_TARGET_RESET)||
                    (dataShutdownTarget_u8 == ECUM_SHUTDOWN_TARGET_SLEEP))
            {
                /* The shutdown mode parameter is given as OUT parameter*/
                *shutdownMode = dataMode_u16;
            }
            else
            {
              //nothing to be executed here
            }

            return_value_u8 = E_OK;
        }
    }

    return return_value_u8;
}


/***********************************************************************************

  Function name :   Std_ReturnType EcuM_GetLastShutdownTarget( EcuM_ShutdownTargetType* shutdownTarget,
                    EcuM_ShutdownModeType* shutdownMode )
  Description   :   Returns the shutdown target of the previous shutdown process
                    and it is part of the ECU Manager Module port interface.
  Parameter in  :   None
  Parameter out :   shutdownTarget, shutdownMode
  Return value  :   Std_ReturnType
  Remarks       :
 ************************************************************************************/
/* MR12 RULE 8.13 VIOLATION: The pointer parameter will only be modified for an EcuM configuration with NvM enabled */
FUNC(Std_ReturnType, ECUM_CODE) EcuM_GetLastShutdownTarget(
          P2VAR(EcuM_ShutdownTargetType, AUTOMATIC, ECUM_APPL_DATA) shutdownTarget,
          P2VAR(EcuM_ShutdownModeType, AUTOMATIC, ECUM_APPL_DATA) shutdownMode )
                                        {
    /*Local Variable Declaration*/
    VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
    /* If the service is called before Init then return E_NOT_OK.
          This is because NvM read operation cannot be done before Init. */
    if (FALSE== EcuM_Prv_flgIsModuleInitialised_b )
    {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    /*parameter checking for target*/
    else if (shutdownTarget == NULL_PTR)
    {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
    }

    else
    {
        returnvalue_u8 = E_OK;
    }

    if (returnvalue_u8 == E_OK)
    {
        if(FALSE!=EcuM_Prv_flgNvMReadStatus_b)                         /*check if read operation was successful*/
        {
            /* The shutdown target parameter is given as OUT parameter*/
            *shutdownTarget = EcuM_Prv_dataShutdownInfo_st.ShutdownTarget;

            /*[SWS_EcuM_02337] If the pointer to the shutdownMode parameter is NULL, EcuM_GetLastShutdownTarget shall
             * simply ignore the shutdownMode parameter and return the last shutdown target regardless of whether it
             * was SLEEP or not. If Default Error Detection is activated, EcuM_GetShutdownTarget shall send the
             * ECUM_E_PARAM_POINTER development error to the DET module.*/
            if(shutdownMode == NULL_PTR)
            {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
                (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID,
                        ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
            }
            else if ((EcuM_Prv_dataShutdownInfo_st.ShutdownTarget == ECUM_SHUTDOWN_TARGET_SLEEP) ||
                    (EcuM_Prv_dataShutdownInfo_st.ShutdownTarget == ECUM_SHUTDOWN_TARGET_RESET))
            {
                /* The shutdown mode parameter is given as OUT parameter*/
                *shutdownMode = EcuM_Prv_dataShutdownInfo_st.mode;
            }
            else
            {
                //nothing to be executed here
            }
        }

        else
        {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_NVM_READ_FAILED);
#endif //ECUM_DEV_ERROR_DETECT
            returnvalue_u8 = E_NOT_OK;
        }
    }



#else //ECUM_CFG_NVM_BLOCK_CONFIGURED == FALSE
    /* The following code is there only to avoid compiler warning (Un-used variable) if  no NvM Block is configured. */
    (void)shutdownTarget;
    (void)shutdownMode;


#if(ECUM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_TAR_APIID, ECUM_E_SERVICE_DISABLED );
#endif //ECUM_DEV_ERROR_DETECT
 //If NvM is not enabled E_NOT_OK will be returned as last shutdown info cant be retrieved

#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED


    return returnvalue_u8;
}

#if (ECUM_CFG_NVM_BLOCK_CONFIGURED == TRUE)
/***********************************************************************************

  Function name :   Std_ReturnType EcuM_Rb_GetLastShutdownInfo( EcuM_ShutdownInfoType  )
  Description   :   Returns the shutdown cause as well as time taken for the previous shutdown process if time
                    measurement is enabled.
  Parameter in  :   none
  Parameter out :   shutdownCauseInfo
  Return value  :   Std_ReturnType
  Remarks       :
 ************************************************************************************/
FUNC( Std_ReturnType, ECUM_CODE ) EcuM_Rb_GetLastShutdownInfo(
        P2VAR(EcuM_ShutdownInfoType, AUTOMATIC, ECUM_APPL_DATA) shutdownCauseInfo)
{
    /*Local Variable Declaration*/
    VAR(Std_ReturnType, AUTOMATIC) returnvalue_u8 = E_NOT_OK;

    /* If the service is called before Init then return E_NOT_OK.
          This is because NvM read operation cannot be done before Init. */
    if (( FALSE== EcuM_Prv_flgIsModuleInitialised_b ))
    {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_UNINIT );
#endif //ECUM_DEV_ERROR_DETECT
    }
    /*parameter checking for */
    else if (( shutdownCauseInfo == NULL_PTR))
    {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_PARAM_POINTER );
#endif //ECUM_DEV_ERROR_DETECT
    }

    else
    {
        returnvalue_u8 = E_OK;
    }

    if (returnvalue_u8 == E_OK)
    {
        if(FALSE!=EcuM_Prv_flgNvMReadStatus_b)                         /*check if read operation was successful*/
        {

            shutdownCauseInfo->ShutdownCause = EcuM_Prv_dataShutdownInfo_st.ShutdownInfo.ShutdownCause;
#if (ECUM_STARTUP_DURATION == TRUE)
            shutdownCauseInfo->TimeMeasured = EcuM_Prv_dataShutdownInfo_st.ShutdownInfo.TimeMeasured;
#endif//ECUM_STARTUP_DURATION
        }

        else
        {

#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_LAST_SHUT_CAUSE_APIID, ECUM_E_NVM_READ_FAILED);
#endif //ECUM_DEV_ERROR_DETECT
            returnvalue_u8 = E_NOT_OK;
        }
    }
    return returnvalue_u8;
}
#endif//ECUM_CFG_NVM_BLOCK_CONFIGURED

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"








