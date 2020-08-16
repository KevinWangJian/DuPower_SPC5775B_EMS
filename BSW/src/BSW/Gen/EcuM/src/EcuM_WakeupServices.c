

#include "EcuM.h" /*BSW_HeaderInc_002*/



#include "EcuM_Cfg_SchM.h"

/*Extern module Headers*/
#include "BswM_EcuM.h"
#if (!defined(BSWM_AR_RELEASE_MAJOR_VERSION) || (BSWM_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(BSWM_AR_RELEASE_MINOR_VERSION) || (BSWM_AR_RELEASE_MINOR_VERSION != 2))
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

  Function name :   void EcuM_SetWakeupEvent( EcuM_WakeupSourceType sources )
  Description   :   It sets the wakeup event.
  Parameter in  :   source
  Parameter out :   None
  Return value  :   None
  Remarks       :
 ************************************************************************************/
FUNC( void, ECUM_CODE ) EcuM_SetWakeupEvent( VAR(EcuM_WakeupSourceType, AUTOMATIC) sources )
{
    /*Local variable declaration*/
    // Variable used to hold the split wakeup events(which is not in pending or in validated wakeup) from the passed sources
    VAR(uint32, AUTOMATIC) EcuM_newWkupEvents_u32 = 0;

    // internal variable used to hold the wakeup validation timeout
    VAR(uint16, AUTOMATIC) EcuM_WkpSrcValidationTimeoutCtr_u16 = 0;

    // internal variable used to hold the wakeup events with no validation timeout
    VAR(uint32, AUTOMATIC) EcuM_dataValidatedWakeupEvents_u32 = 0;

    // internal variable used to hold the wakeup events with validation timeout
    VAR(uint32, AUTOMATIC) EcuM_dataPendingWakeupEvents_u32 = 0;

    VAR(uint8, AUTOMATIC) ctrLoop_u8 = 0;
#if ECUM_SLEEP_SUPPORT_ENABLE
    VAR(EcuM_Prv_SleepType_Enum_ten, AUTOMATIC)     id_RequestedSleepType_en;
    /*Local variable to hold sleep mode and initialized with invalid value*/
    VAR(EcuM_ShutdownModeType, AUTOMATIC) dataSleepModeHandle_u16 = 0xFF;
#endif//ECUM_SLEEP_SUPPORT_ENABLE
    /* DET raised for invalid wakeupsource*/
    if( EcuM_Prv_hasCheckWakeupSourceGetHandle_b( sources ) == FALSE )
    {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_SET_WKEVENT_APIID, ECUM_E_UNKNOWN_WAKEUP_SOURCE );
#endif//ECUM_DEV_ERROR_DETECT

    }
    else
    {

        /* Splitting the received wakeup source to filter out from the wakeup events which already in pending or validated
            or expired*/
        /* EcuM2712:If EcuM_SetWakeupEvent is called subsequently for the same wakeup source, the ECU Manager module
         * will not restart the wakeup validation timeout */
        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/

#if ECUM_SLEEP_SUPPORT_ENABLE
        /*Getting the Sleep type in critical region*/
        id_RequestedSleepType_en = EcuM_Prv_SleepReqType_en;

        if(ECUM_PRV_GOHALT_E == id_RequestedSleepType_en)
        {
        /*sleep mode for which EcuM_GoHalt was called*/
        dataSleepModeHandle_u16 = EcuM_Prv_SleepMode_u16;

       /* [SWS_EcuM_04138] EcuM_SetWakeupEvent shall ignore all events passed in the sources parameter that are not
        * associated to the selected sleep mode.*/
        sources = (sources & EcuM_Cfg_idxSleepModes_au32[dataSleepModeHandle_u16].WakeupSourceMask);
        }
#endif//ECUM_SLEEP_SUPPORT_ENABLE

        EcuM_newWkupEvents_u32 = ( sources & ( ~EcuM_Prv_dataPendingWakeupEvents_u32 ) & ( ~EcuM_Prv_dataValidatedWakeupEvents_u32 )
                & ( ~EcuM_Prv_dataExpiredWakeupEvents_u32 ) );
        SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA ); /*leave Critical Sectiont*/

        if ( EcuM_newWkupEvents_u32 != ECUM_NO_WKUP_SRC )
        {

            // Splitting the received wakeup source to filter out the wakeup sources which are not having validation timeout to validated wakeup
            EcuM_dataValidatedWakeupEvents_u32 = ( EcuM_newWkupEvents_u32 & ECUM_WAKEUP_SOURCES_WITHOUT_VALIDATION );

            // Splitting the received wakeup source to filter out the wakeup sources which having validation timeout to pending wakeup
            EcuM_dataPendingWakeupEvents_u32   = ( EcuM_newWkupEvents_u32 & ECUM_WAKEUP_SOURCES_WITH_VALIDATION );

        }
        /*When single timer used for all the wakeups then wakeup event having Validation timeout timer with the
         *  greatest validation timeout value to be updated*/
        if ( EcuM_dataPendingWakeupEvents_u32 != ECUM_NO_WKUP_SRC )
        {

            for( ctrLoop_u8 = 0;ctrLoop_u8 < ECUM_NUM_OF_WKP_SOURCES;ctrLoop_u8++ )
            {

                /* Update the Validation timeout timer with the greatest validation timeout value */
                if ( ( ( EcuM_dataPendingWakeupEvents_u32 & EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].WakeupSourceId ) != ECUM_NO_WKUP_SRC ) \
                        && ( EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].ValidationTimeout > EcuM_WkpSrcValidationTimeoutCtr_u16 ) )
                {

                    EcuM_WkpSrcValidationTimeoutCtr_u16 = EcuM_Cfg_idxWakeupSourcesPC_au32[ctrLoop_u8].ValidationTimeout;

                }


            }
        }

        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/

        /*Update the Global variable EcuM_Prv_dataValidatedWakeupEvents_u32 wrt the new event reported*/
        EcuM_Prv_dataValidatedWakeupEvents_u32 |= EcuM_dataValidatedWakeupEvents_u32;

        /*Update the Global variable EcuM_Prv_dataValWkpEventsInd_u32 with the new event reported*/
        EcuM_Prv_dataValWkpEventsInd_u32 |= EcuM_dataValidatedWakeupEvents_u32;

        /*Update the Global variable EcuM_Prv_dataPendingWakeupEvents_u32 with the new event reported*/
        EcuM_Prv_dataPendingWakeupEvents_u32 |=EcuM_dataPendingWakeupEvents_u32;

        /*Update the Global variable EcuM_Prv_dataPndWkpEventsInd_u32 with the new event reported*/
        EcuM_Prv_dataPndWkpEventsInd_u32 |=EcuM_dataPendingWakeupEvents_u32;

        /*Prolong the EcuM_WkpSrcValidationTimeoutCtr_u16 when a wakeup event Validation counter value is greater than the
         * current value */
        if( EcuM_WkpSrcValidationTimeoutCtr_u16 > EcuM_Prv_WkpSrcValidationTimeoutCtr_u16 )
        {

            EcuM_Prv_WkpSrcValidationTimeoutCtr_u16 = EcuM_WkpSrcValidationTimeoutCtr_u16;

        }
        SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA ); /*leave Critical Sectiont*/


    }


}

/***********************************************************************************

  Function name :   void EcuM_ValidateWakeupEvent( EcuM_WakeupSourceType sources )
  Description   :   After wakeup, the ECU State Manager will stop the process during the WAKEUP VALIDATION state/sequence
                    to wait for validation of the wakeup event.This API service is used to indicate to the ECU Manager module
                    that the wakeup events indicated in the sources parameter have been validated.
  Parameter in  :   source
  Parameter out :   None
  Return value  :   None
  Remarks       :
 ************************************************************************************/
FUNC( void, ECUM_CODE ) EcuM_ValidateWakeupEvent( VAR(EcuM_WakeupSourceType, AUTOMATIC) sources )
{
    /*Local variable declaration*/
    // Variable used to hold only the wakeup sources with Comm channel reference from the passed sources
    VAR(uint32, AUTOMATIC) EcuM_CommchlWkupEvents_u32 = 0;

    // Variable used to hold only the wakeup sources with Comm channel reference from the passed sources
    VAR( EcuM_WakeupSourceType,AUTOMATIC )  dataPendingWakeupEvents_u32 = 0;

    /*DET raised for service called before EcuM Initialised */
    if ( EcuM_Prv_flgIsModuleInitialised_b == FALSE )
    {

#if ( ECUM_DEV_ERROR_DETECT == STD_ON )
        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_VAL_WKEVENT_APIID, ECUM_E_UNINIT );
#endif//ECUM_DEV_ERROR_DETECT

    }
    /* DET raised for invalid wakeupsource*/
    else if( EcuM_Prv_hasCheckWakeupSourceGetHandle_b( sources ) == FALSE )
    {

#if( ECUM_DEV_ERROR_DETECT == STD_ON )
        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_VAL_WKEVENT_APIID,
                ECUM_E_UNKNOWN_WAKEUP_SOURCE );
#endif//ECUM_DEV_ERROR_DETECT

    }
    else
    {

        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/

        dataPendingWakeupEvents_u32 = EcuM_Prv_dataPendingWakeupEvents_u32;

        SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA ); /*Exit Critical Sectiont*/

        /*get only the wakeup sources passed in the function parameter and which are currently in pending state
         * to proceed for Wakeup validation*/
        dataPendingWakeupEvents_u32 = dataPendingWakeupEvents_u32 & sources;
    }
    if ( dataPendingWakeupEvents_u32 != ECUM_NO_WKUP_SRC )
    {

        /*call EcuM_Prv_ComMWakeupHandling service for ComM related indications*/
        EcuM_CommchlWkupEvents_u32 = EcuM_Prv_ComMWakeupHandling(dataPendingWakeupEvents_u32);

        /*If the current phase is UP phase no other wakeup sources except wakeupsource with ComM channel reference
         * should not be validated*/

        if ( EcuM_Prv_dataPresentPhase_u8 == ECUM_PRV_PHASE_UP )
        {

            dataPendingWakeupEvents_u32 = EcuM_CommchlWkupEvents_u32;

        }
        SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/

        /*Update the validated events*/
        EcuM_Prv_dataValidatedWakeupEvents_u32 |= dataPendingWakeupEvents_u32;

        /*Update the Pending events with the sources passed removed*/
        EcuM_Prv_dataPendingWakeupEvents_u32 &= ( ~dataPendingWakeupEvents_u32 );

        EcuM_Prv_dataPndWkpEventsInd_u32 &= ( ~dataPendingWakeupEvents_u32 );
        SchM_Exit_EcuM( ECUM_SCHM_EXCLSV_AREA ); /*Exit Critical Section*/

    }

    if(dataPendingWakeupEvents_u32 != ECUM_NO_WKUP_SRC)
           {
               /* indicate BswM module with the current state of a Wakeup source*/
               BswM_EcuM_CurrentWakeup( dataPendingWakeupEvents_u32, ECUM_WKSTATUS_VALIDATED );

           }


    return;
}


/***********************************************************************************

  Function name:    void EcuM_ClearWakeupEvent(EcuM_WakeupSourceType sources )
  Description   :   Clears wakeup events.It will clear the source bit from all the internal wakeup source state variables.
  Parameter in  :   source
  Parameter out :   None
  Return value  :   None
  Remarks       :
 ************************************************************************************/
FUNC( void, ECUM_CODE )EcuM_ClearWakeupEvent ( VAR(EcuM_WakeupSourceType, AUTOMATIC) sources )
{

    /*DET raised for service called before EcuM Initialised */
    if ( EcuM_Prv_flgIsModuleInitialised_b == FALSE )
    {
#if (ECUM_DEV_ERROR_DETECT == STD_ON)
        (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_CLEAR_WKEVENT_APIID, ECUM_E_UNINIT);
#endif//ECUM_DEV_ERROR_DETECT
    }

    else
    {

       /* DET raised for invalid wakeupsource*/
        if(EcuM_Prv_hasCheckWakeupSourceGetHandle_b(sources) == FALSE)
        {
#if(ECUM_DEV_ERROR_DETECT == STD_ON)
            (void)Det_ReportError(ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_CLEAR_WKEVENT_APIID,
                                                                    ECUM_E_UNKNOWN_WAKEUP_SOURCE);
#endif//ECUM_DEV_ERROR_DETECT
        }

        else
        {
                SchM_Enter_EcuM( ECUM_SCHM_EXCLSV_AREA );  /*Enter Critical Section*/

                /* while doing Xor operation 0 XOR 0 will be 1 and that will lead to wrong updation of internal wakeup
                 * variables. instead of clearing the bitmask it will give a false value hence the following checks
                 * are used */
                if ((sources &(EcuM_Prv_dataPendingWakeupEvents_u32 | EcuM_Prv_dataValidatedWakeupEvents_u32 |
                        EcuM_Prv_dataExpiredWakeupEvents_u32 )) == ECUM_NO_WKUP_SRC)
                {
                    /* EcuM Global flags will not be updated and return without doing anything */
                }

                else
                {
                    /*This is an indication variable and it is used to send BswM and ComM wakeup inductions in EcuM
                     * main function for the wakeup sources
          which are set to cleared in EcuM_ClearWakeupEvent for the current main function cycle*/
                    EcuM_Prv_dataClrWkpEventsInd_u32 |= (sources &(EcuM_Prv_dataPendingWakeupEvents_u32 |
                            EcuM_Prv_dataValidatedWakeupEvents_u32 | EcuM_Prv_dataExpiredWakeupEvents_u32 ));

                    /*Check whether the wakeup source state is pending. if so clear the bitmask from Pending wakeup
                     * sources*/
                    if  ((EcuM_Prv_dataPendingWakeupEvents_u32 & sources)!= ECUM_NO_WKUP_SRC )
                    {
                        EcuM_Prv_dataPendingWakeupEvents_u32  ^= (EcuM_Prv_dataPendingWakeupEvents_u32 & sources);

                        /*Updated the pending wakeup status indication variable for BswM wakeup indication in
                         * mainfunction */
                        EcuM_Prv_dataPndWkpEventsInd_u32 ^= (EcuM_Prv_dataPndWkpEventsInd_u32 & sources);
                    }

                    /*Check whether the wakeup source state is Validated. if so clear the bitmask from Pending
                     * wakeup sources*/
                    if ((EcuM_Prv_dataValidatedWakeupEvents_u32 & sources)!= ECUM_NO_WKUP_SRC)
                    {
                        EcuM_Prv_dataValidatedWakeupEvents_u32^=(EcuM_Prv_dataValidatedWakeupEvents_u32 & sources);

                        /*Updated the Validated wakeup status indication variable for BswM wakeup indication in
                         * mainfunction */
                        EcuM_Prv_dataValWkpEventsInd_u32 ^= (EcuM_Prv_dataValWkpEventsInd_u32 & sources);
                    }

                    /*Check whether the wakeup source state is Expired. if so clear the bitmask from Expired wakeup
                     * sources*/
                    if ((EcuM_Prv_dataExpiredWakeupEvents_u32 & sources)!= ECUM_NO_WKUP_SRC)
                    {
                        EcuM_Prv_dataExpiredWakeupEvents_u32 ^=(EcuM_Prv_dataExpiredWakeupEvents_u32 & sources);

                        /*Updated the Expired wakeup status indication variable*/
                        EcuM_Prv_dataExpWkpEventsInd_u32 ^=(EcuM_Prv_dataExpWkpEventsInd_u32 & sources);
                    }
                }

                SchM_Exit_EcuM(ECUM_SCHM_EXCLSV_AREA); /*Exit Critical Sectiont*/

        }
    }
}
/***********************************************************************************

  Function name :   EcuM_WakeupSourceType EcuM_GetPendingWakeupEvents( void )
  Description   :   EcuM_GetPendingWakeupEvents will return wakeup events which have been set to pending but not yet
  validated
                    as bits set in a EcuM_WakeupSourceType bitmask.
  Parameter in  :   None
  Parameter out :   None
  Return value  :   EcuM_WakeupSourceType
  Remarks       :
 ************************************************************************************/

FUNC( EcuM_WakeupSourceType, ECUM_CODE ) EcuM_GetPendingWakeupEvents( void )
{
    /*Local variable in the type of EcuM_WakeupSourceType to hold and return the Pending wakeup event*/
    uint32 PendingWakeupEvents = ECUM_NO_WKUP_SRC;

    /*DET raised for service called before EcuM Initialised */
    if ( EcuM_Prv_flgIsModuleInitialised_b == FALSE )
    {

      #if ( ECUM_DEV_ERROR_DETECT == STD_ON )
        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_PEND_APIID, ECUM_E_UNINIT );
      #endif//ECUM_DEV_ERROR_DETECT

        PendingWakeupEvents =  ECUM_NO_WKUP_SRC;

    }
    else
    {

        PendingWakeupEvents = EcuM_Prv_dataPendingWakeupEvents_u32;

    }

    return PendingWakeupEvents;

}

/***********************************************************************************

  Function name :   EcuM_WakeupSourceType EcuM_GetValidatedWakeupEvents( void  )
  Description   :   EcuM_GetValidatedWakeupEvents will return wakeup events which have been set to validated in the
                    internal validated
                    events variable as bits set in a EcuM_WakeupSourceType bitmask.
  Parameter in  :   None
  Parameter out :   None
  Return value  :   EcuM_WakeupSourceType
  Remarks       :
 ************************************************************************************/

FUNC( EcuM_WakeupSourceType, ECUM_CODE ) EcuM_GetValidatedWakeupEvents( void )
{
    /*Local variable in the type of EcuM_WakeupSourceType to hold and return the Validated wakeup event*/
   uint32 ValidatedWakeupEvents = ECUM_NO_WKUP_SRC;

    /*DET raised for service called before EcuM Initialised */
    if ( EcuM_Prv_flgIsModuleInitialised_b == FALSE )
    {

      #if ( ECUM_DEV_ERROR_DETECT == STD_ON )
        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_VALIDATE_APIID, ECUM_E_UNINIT );
      #endif//ECUM_DEV_ERROR_DETECT

        ValidatedWakeupEvents = ECUM_NO_WKUP_SRC;

    }
    else
    {

        ValidatedWakeupEvents = EcuM_Prv_dataValidatedWakeupEvents_u32;

    }

    return ValidatedWakeupEvents;

}

/***********************************************************************************

  Function name :   EcuM_WakeupSourceType EcuM_GetExpiredWakeupEvents( void  )
  Description   :   Returns all events for which validation has failed. Events which do not need validation must never
                    be reported by this function.
  Parameter in  :   None
  Parameter out :   None
  Return value  :   EcuM_WakeupSourceType
  Remarks       :
 ************************************************************************************/

FUNC( EcuM_WakeupSourceType, ECUM_CODE ) EcuM_GetExpiredWakeupEvents( void )
{
    /*Local variable in the type of EcuM_WakeupSourceType to hold and return the Expired wakeup event*/
       uint32 ExpiredWakeupEvents = ECUM_NO_WKUP_SRC;

    /*DET raised for service called before EcuM Initialised */
    if ( EcuM_Prv_flgIsModuleInitialised_b == FALSE )
    {

      #if ( ECUM_DEV_ERROR_DETECT == STD_ON )
        ( void ) Det_ReportError( ECUM_MODULE_ID, ECUM_INSTANCE_ID, ECUM_GET_EXPIRED_APIID, ECUM_E_UNINIT );
      #endif//ECUM_DEV_ERROR_DETECT

       ExpiredWakeupEvents = ECUM_NO_WKUP_SRC;

    }
    else
    {

     ExpiredWakeupEvents = EcuM_Prv_dataExpiredWakeupEvents_u32;

    }

    return ExpiredWakeupEvents;
}

#define ECUM_STOP_SEC_CODE
#include "EcuM_Cfg_MemMap.h"

