

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "WdgM_Prv.h"

/*
 ***************************************************************************************************
 * Variables
 ***************************************************************************************************
 */
#define WDGM_START_SEC_VAR_FAST_INIT_8
#include "WdgM_Cfg_MemMap.h"

/* TRACE[WDGM213] Only one global supervision Status for the whole WdgM */
/*WDGM_DBG_TST_ENA macro can be defined only for testing purpose.
 *It is used to change the scope of the variable from static to extern.
 *If we define it as global(extern) variable then, there is a chance that it is written outside WdgM module,
 *which can lead to unexpected behavior.
 *Hence, caution: WDGM_DBG_TST_ENA macro should not be defined for Production software.*/
#ifdef WDGM_DBG_TST_ENA
VAR(WdgM_GlobalStatusType, WDGM_VAR_FAST_INIT_8)  WdgM_GlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
#else
    static VAR(WdgM_GlobalStatusType, WDGM_VAR_FAST_INIT_8)  WdgM_GlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
#endif
static VAR(WdgM_GlobalStatusType, WDGM_VAR_FAST_INIT_8)  WdgM_Prv_SetMode_GlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;

#define WDGM_STOP_SEC_VAR_FAST_INIT_8
#include "WdgM_Cfg_MemMap.h"

#define WDGM_START_SEC_CODE_SLOW
#include "WdgM_Cfg_MemMap.h"
/*
 ***************************************************************************************************
 * Public Function Definations
 ***************************************************************************************************
 */


/****************************************************************************************
* Name                :    WdgM_Init
* Description        :    Intilize the Watchdog Manager as per Configurations
* Parameters[in]    :   ConfigPtr
* Limitations        :    Care has to be taken while calling this function as it is not reentrant.
* ReturnType        :    Void
*****************************************************************************************/
/* TRACE[WDGM151] Implementation of WdgM_Init*/






FUNC(void, WDGM_CODE_SLOW) WdgM_Init(P2CONST(WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST)ConfigPtr)
{
#if((WDGM_OFF_MODE_ENABLED)  == (STD_OFF))
    VAR(uint8, AUTOMATIC) TriggerIdx;
    P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_APPL_CONST) TriggerPtr;
#endif /*((WDGM_OFF_MODE_ENABLED)  == (STD_OFF))*/
    VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SEID;
#if ((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO))
    VAR(uint16, AUTOMATIC) DeadlineSupervisionIdx;
#endif /*((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO)) */
    VAR(Std_ReturnType, AUTOMATIC) ReturnStatus;
#if((WDGM_RTE_DISABLED) == (STD_OFF))
    VAR(Rte_PortHandle_WdgM_IndividualMode_P,AUTOMATIC) PortHandle = Rte_Ports_WdgM_IndividualMode_P();
#endif /*(WDGM_RTE_DISABLED == STD_OFF)*/

    


#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    WdgM_MainFunction_Cnt_u32 = WDGM_PRV_C_ZERO;
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/

    /*
     * WdgM_ConfigSetPtr is assigned according to the variants
     * If WdgM_ConfigSet is configured at precompile then the sanity checks are done via the script.
     * Hence in this case no more sanity checking
     */
#if (defined(WDGM_VARIANT_PRE_COMPILE))
    /* The parameter "ConfigPtr" is void casted, as it is unused during Precompile*/
        (void)ConfigPtr;
        WdgM_ConfigSetPtr = &WdgM_Config;
    /* Else if not Precompile ie POST build hence perform sanity check on ConfigSet*/
#else /*defined(WDGM_VARIANT_PRE_COMPILE)*/
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM255] Check for NULL_PTR*/
    if (ConfigPtr == NULL_PTR)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_INIT_APIID, WDGM_E_INV_POINTER);
        return;
    }
    else
    {
        /* TRACE[WDGM010] Perform Sanity Check fo the ConfigData and load the values */
        ReturnStatus = WdgM_Prv_PbCfgCheck_tu8_Inl(ConfigPtr);
        if(ReturnStatus != E_OK)
        {
            /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
            (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_INIT_APIID, WDGM_E_PARAM_CONFIG);
            return;
        }
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
    WdgM_ConfigSetPtr = ConfigPtr;
#endif /*defined(WDGM_VARIANT_PRE_COMPILE)*/
#if((WDGM_OFF_MODE_ENABLED)  == (STD_OFF))
    TriggerPtr = WdgM_ConfigSetPtr->PtrToMode[WdgM_ConfigSetPtr->InitialMode].PtrToTrigger;
    for(TriggerIdx = WDGM_PRV_C_ZERO;
            TriggerIdx < WdgM_ConfigSetPtr->PtrToMode[WdgM_ConfigSetPtr->InitialMode].NoOfTrigger;
            TriggerIdx++)
    {
        if (TriggerPtr[TriggerIdx].WdgMode == WDGIF_OFF_MODE)
        {
            /* TRACE[WDGM030] Since WdgM Mode is in Off Mode Do not intilize the WdgM*/
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
            /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
            (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_INIT_APIID, WDGM_E_DISABLE_NOT_ALLOWED);
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
            return;
        }
    }
#endif
    /*TRACE[WDGM269]: Transition: 11: Initally all local SE are DEACTIVATED */
    for(SEID = WDGM_PRV_C_ZERO; SEID < WDGM_NO_OF_SUPERVISED_ENTITIES; SEID++)
    {
        WdgM_SupervisedEntityDyn[SEID].OldLocalStatus = WDGM_LOCAL_STATUS_DEACTIVATED;
        WdgM_SupervisedEntityDyn[SEID].NewLocalStatus = WDGM_LOCAL_STATUS_DEACTIVATED;
        /* TRACE[SWS_WdgM_00296] Init flgActivity to FALSE and idLastReachedCheckpoint to zero
         * for all WdgM_SupervisedEntityDyn Entries of Internal Graph*/
#if (WDGM_INTERNAL_GRAPH_CONFIGURED == STD_ON)
        WdgM_SupervisedEntityDyn[SEID].flgActivity = FALSE;
        WdgM_SupervisedEntityDyn[SEID].idLastReachedCheckpoint = WDGM_PRV_C_ZERO;
#endif
#if((WDGM_RTE_DISABLED) == (STD_OFF))
        PortHandle[SEID].Switch_currentMode(RTE_MODE_WdgM_Mode_SUPERVISION_DEACTIVATED);
#endif/*(WDGM_RTE_DISABLED == STD_OFF)*/
    }
    WdgM_Prv_SetMode_GlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
    /* User sets many modes via WdgMMode[].
     * He will configure one of the Modes as the Initial Mode fro WdgM.
     * Here the user set user set Initial Mode is as WdgM Inital Mode*/
    /* TRACE[WDGM135] Set the Initial Mode of the WdgM*/
    ReturnStatus = WdgM_SetMode(WdgM_ConfigSetPtr->InitialMode, WDGM_MODULE_ID);
    /* Configure the Supervision ENtities to be used its LOCAL_STATUS to ACTIVE*/
    if(ReturnStatus == E_OK)
    {
        /* TRACE [WDGM350] Clear the Complementary Entries of SEID at Init*/
        WdgM_FirstExpiredSupervisedEntityId = WDGM_PRV_C_ZERO;
        /* Wrong complement is given to detect first expired Supervision */
        WdgM_FirstExpiredSupervisedEntityId_Comp = WDGM_PRV_C_ZERO;
        WdgM_ExpiredSupervisionCycleCtr = WDGM_PRV_C_ZERO;

#if((WDGM_RB_DEBUG_OPTION_ENABLED) == (STD_ON))
        if(WdgM_Rb_FirstExpiredEntity_Cnt_u8 == WDGM_PRV_C_ZERO)
        {
            WdgM_Rb_DebugVariables_Init_v_Inl();
        }
#endif/*(WDGM_RB_DEBUG_OPTION_ENABLED == STD_ON)*/

        /* Alive supervision */
        /* Nothing to do. Already values are set in WdgM_SetMode */
#if ((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO))
        /* Deadline supervision */
        /* TRACE[WDGM298] All Deadline Start Checkpoints set their timestamps to 0  */
        for(DeadlineSupervisionIdx = WDGM_PRV_C_ZERO;
                DeadlineSupervisionIdx < WDGM_MAX_DEADLINE_SUPERVISIONS;
                DeadlineSupervisionIdx++)
        {
            if(WdgM_ConfigSetPtr->PtrToRunningCounterValue != NULL_PTR)
            {
                WdgM_ConfigSetPtr->PtrToRunningCounterValue[DeadlineSupervisionIdx] = WDGM_PRV_C_ZERO;
            }
        }
#endif /*((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO)) */
        /* TRACE[WDGM285] Init Complete Set GLobal Status To OK  */
        WdgM_GlobalStatus = WDGM_GLOBAL_STATUS_OK;

    }
    else
    {
        /*TRACE[WDGM139] WdgIf_SetMode is being called from WdgM_SetMode
         *If SetMode fails then set the GlobalStatus to STOPPED */
        WdgM_GlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
    }

    return;
}


/*******************************************************************************************
* Name              :   WdgM_DeInit
* Description       :   DeIntilize the Watchdog Manager.
* Parameters[in]    :   None
* Limitations       :   Care has to be taken while calling this function as it is not reentrant.
* ReturnType        :   Void
*******************************************************************************************/
/* TRACE[WDGM261] Implementation of WdgM_DeInit*/
FUNC(void, WDGM_CODE_SLOW) WdgM_DeInit(void)
{

#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM288] To check if WdgM is Initilized if not then log error in Det. */
    if (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_DEACTIVATED)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_DE_INIT_APIID , WDGM_E_NO_INIT);
        return;
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/

    if(WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_OK)
    {
        SchM_Enter_WdgM(WDGM_SCHM_EXCLSV_AREA);
        /* TRACE[WDGM286] Set global status to Deactivated, if Wdg global status is OK*/
        WdgM_GlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
        SchM_Exit_WdgM(WDGM_SCHM_EXCLSV_AREA);
    }
    return;
}

#if( (WDGM_VERSION_INFO_API) == (STD_ON) )
/*******************************************************************************************
* Name              :   WdgM_GetVersionInfo
* Description       :   Returns the version information of this module.
* Parameters[out]   :   VersionInfo
* Limitations       :   Care has to be taken while calling this function as it is not reentrant.
* ReturnType        :   Void
*******************************************************************************************/
/* TRACE[WDGM110] Implementation of WDGM_GetVersionInfo whcih can be disabled at preCompile time*/
FUNC(void, WDGM_CODE_SLOW) WdgM_GetVersionInfo (P2VAR(Std_VersionInfoType, AUTOMATIC, WDGM_APPL_DATA)VersionInfo)
{
#if ((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM256]  Perform sanity checks on VersionInfo*/
    if (VersionInfo == NULL_PTR)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_VERSION_INFO_APIID, WDGM_E_INV_POINTER);
        return;
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/

    VersionInfo->vendorID   = WDGM_VENDOR_ID;
    VersionInfo->moduleID   = WDGM_MODULE_ID;
    VersionInfo->sw_major_version = WDGM_SW_MAJOR_VERSION;
    VersionInfo->sw_minor_version = WDGM_SW_MINOR_VERSION;
    VersionInfo->sw_patch_version = WDGM_SW_PATCH_VERSION;
    return;
}
#endif

#define WDGM_STOP_SEC_CODE_SLOW
#include "WdgM_Cfg_MemMap.h"

#define WDGM_START_SEC_CODE_FAST
#include "WdgM_Cfg_MemMap.h"

/*******************************************************************************************
* Name              :   WdgM_SetMode
* Description       :   Sets the current mode of Watchdog Manager.
* Parameters[in]    :   Mode, CallerID
* Limitations       :   Care has to be taken while calling this function as it is not reentrant.
* ReturnType        :   void
*******************************************************************************************/
FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_SetMode(VAR(WdgM_ModeType,AUTOMATIC) Mode, VAR(uint16,AUTOMATIC) CallerID)
/*TRACE[WDGM154] Implementation of WdgM_SetMode*/


{
/*Generated only when one or more Caller Id is configured or WDGM_OFF_MODE is disabled*/
/* Variable is not needed if DET is ON, Defensive Behavior is ON and No of Caller ID is 0 */
#if (((WDGM_DEV_ERROR_DETECT == STD_ON) && (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) && (WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS == WDGM_PRV_C_ZERO)) == FALSE)
#if(((WDGM_DEV_ERROR_DETECT == STD_ON) && (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) && (WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS > WDGM_PRV_C_ZERO)) || (WDGM_OFF_MODE_ENABLED  == STD_OFF))
    VAR(uint8, AUTOMATIC) ctr;
#endif
#endif

    VAR(Std_ReturnType, AUTOMATIC) ReturnStatus;

/*Generated only when WDGM_OFF_MODE is disabled*/
/* Variable is not needed if DET is ON, Defensive Behavior is ON and No of Caller ID is 0 */
#if (((WDGM_DEV_ERROR_DETECT == STD_ON) && (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) && (WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS == WDGM_PRV_C_ZERO)) == FALSE)
#if((WDGM_OFF_MODE_ENABLED)  == (STD_OFF))
    P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_APPL_CONST) TriggerPtr;
#endif /*(WDGM_OFF_MODE_ENABLED)  == (STD_OFF)*/
#endif

    /*If non configured modules are accessing the SetMode then Error*/
    ReturnStatus = E_NOT_OK;
    /* TRACE[WDGM338] Watchdog Manager Service*/
    /* Enter here for Set Mode access from a Non WatchDog functions*/
    if(CallerID != (uint16)WDGM_MODULE_ID)
    {/* CallerID check is required to allow WdgM_SetMode to be called from WdgM_Init even when WdgM is not initialized */
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
#if((WDGM_DEFENSIVE_BEHAVIOR) == (STD_ON))
#if((WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS > WDGM_PRV_C_ZERO)) /* When one or more called Id is configured */
        /*IF match found within the allowed limit then break */
        for(ctr= WDGM_PRV_C_ZERO; ctr<WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS; ctr++)
        {
            if (WdgM_CallerIds[ctr] == CallerID)
            {
                break;
            }
        }
        /*TRACE [WDGM245] Check if the caller Id is from the given list of caller Id's*/
        if(ctr == WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS) /* It means CallerID not found */
        {
#if((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))
            Dem_ReportErrorStatus(WdgM_ConfigSetPtr->ErrorImproperCaller, DEM_EVENT_STATUS_FAILED);
#endif /*((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))*/
                return E_NOT_OK;
        }
#endif

#if(WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS == WDGM_PRV_C_ZERO) /* When no called Id is configured */
#if((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))
             Dem_ReportErrorStatus(WdgM_ConfigSetPtr->ErrorImproperCaller, DEM_EVENT_STATUS_FAILED);
#endif /*((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))*/
             return E_NOT_OK;
#endif
#endif /*WDGM_DEFENSIVE_BEHAVIOR == STD_ON*/

/* Below checks are not needed in case DET is ON, Defensive Behavior is ON and No of Caller ID is 0,
 * as in this case unconditionally return statement is invoked above */

#if ( ((WDGM_DEFENSIVE_BEHAVIOR == STD_ON) && (WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS == WDGM_PRV_C_ZERO)) == FALSE)
        /* TRACE[WDGM021] Check if WdgM is initilized if not then log DET */
        if (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_DEACTIVATED)
        {
            /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
            (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_SET_MODE_APIID , WDGM_E_NO_INIT);
            return E_NOT_OK;
        }
        /* TRACE[WDGM020] If the mode is not a valid Mode*/
        if (Mode >= WdgM_ConfigSetPtr->NoOfMode)
        {
            /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
            (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_SET_MODE_APIID, WDGM_E_PARAM_MODE);
            return E_NOT_OK;
        }
#endif
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/

/* Below checks are not needed in case DET is ON, Defensive Behavior is ON and No of Caller ID is 0,
 * as in this case unconditionally return statement is invoked above */

#if (((WDGM_DEV_ERROR_DETECT == STD_ON) && (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) && (WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS == WDGM_PRV_C_ZERO)) == FALSE)
        /* TRACE [WDGM031] WdgM Disable Mode is not enabled and if off_Mode has been requested then log error */
#if((WDGM_OFF_MODE_ENABLED)  == (STD_OFF))
        TriggerPtr = WdgM_ConfigSetPtr->PtrToMode[Mode].PtrToTrigger;
        for(ctr= WDGM_PRV_C_ZERO; ctr < WdgM_ConfigSetPtr->PtrToMode[Mode].NoOfTrigger; ctr++)
        {
            if (TriggerPtr[ctr].WdgMode == WDGIF_OFF_MODE)
            {
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
                /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
                (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_SET_MODE_APIID , WDGM_E_DISABLE_NOT_ALLOWED);
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
                return E_NOT_OK;
            }
        }
#endif /*((WDGM_OFF_MODE_ENABLED)  == (STD_OFF))*/
#endif
    }

    /* Enter here for Set Mode access from WatchDog functions*/
    /*TRACE[WDGM145] perform SetMode only if the Global status is OK or FAILED*/
    #if ((WDGM_DEV_ERROR_DETECT == STD_ON) && (WDGM_DEFENSIVE_BEHAVIOR == STD_ON) && (WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS == WDGM_PRV_C_ZERO))
    /* Under this condition, code execution can reach here only if CallerID = WDGM_MODULE_ID. i.e, WdgM_SetMode() is called by WdgM_Init */
    if(Mode < WdgM_ConfigSetPtr->NoOfMode)
    #else
    if((Mode < WdgM_ConfigSetPtr->NoOfMode)&&((WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_OK)||
    (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_FAILED)||(CallerID == WDGM_MODULE_ID)))
    #endif
    {
        /* Trigger Condition */
        WdgM_Prv_UpdateTriggerDyn_v_Inl(Mode, &ReturnStatus);
        if(ReturnStatus == E_OK)
        {
            /* Deadline supervision */
            /* Lock introduced:
            * 1. If Mode change is a relevent request we perform update of deadline timings information,
            * which is mode dependent. Hence placed under a lock. so that no CPR occurs here.
            * 2. Update of Global mode shoule be a one time continous activity when set mode operation is valid.
            * 3. The Supervised information is updated in WdgM_Prv_UpdateSupervisedEntityDyn_v_Inl hence in lock
            * 3. Flag update for SetMode indication if not in a lock will
            * cause a problem at End of WdgM_MainFunction. This will cause missing of TRUE to FALSE change and not reset
            */
            SchM_Enter_WdgM(WDGM_SCHM_EXCLSV_AREA);
            /* Alive supervision */
            WdgM_Prv_UpdateAliveSupervisionDyn_v_Inl();
#if ((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO))
            WdgM_Prv_UpdateDeadlineSupervisionDyn_v_Inl(Mode);
#endif
            /* WDGM317:RFC request in AutoSAR bugzilla Id : 55705 */
            WdgM_Prv_UpdateSupervisedEntityDyn_v_Inl(Mode);
            WdgM_Mode = Mode;
            SchM_Exit_WdgM(WDGM_SCHM_EXCLSV_AREA);
            /* LocalStatusParams */
#if((WDGM_RTE_DISABLED) == (STD_OFF))
            if(SchM_Mode_WdgM_Current_WdgMSupervisionCycle() != WdgM_ConfigSetPtr->PtrToMode[Mode].SchMWdgMSupervisionCycle)
            {
                SchM_Switch_WdgM_WdgMSupervisionCycle(WdgM_ConfigSetPtr->PtrToMode[Mode].SchMWdgMSupervisionCycle);
            }
#endif /*(WDGM_RTE_DISABLED == STD_OFF)*/
        }
    }
    /*If non configured modules are accessing the SetMode then Error*/
    /* Return E_OK if trying to change from same mode to same mode */
    if(ReturnStatus == E_NOT_OK)
    {   /* TRACE[WDGM142] Watchdog Manager shall report to the Diagnostic Event Manager an error with the value WDGM_E_SET_MODE */
        SchM_Enter_WdgM(WDGM_SCHM_EXCLSV_AREA);
        /* WDGM317: RFC request in AutoSAR bugzilla Id : 55705 */
        WdgM_Prv_SetMode_GlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        SchM_Exit_WdgM(WDGM_SCHM_EXCLSV_AREA);
#if((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))
        Dem_ReportErrorStatus(WdgM_ConfigSetPtr->ErrorSetMode, DEM_EVENT_STATUS_FAILED);
#endif /*((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))*/
    }
    return (ReturnStatus);
}


/*******************************************************************************************
* Name              :   WdgM_GetMode
* Description       :   Returns the current mode of the Watchdog Manager.
* Parameters[out]   :   Mode
* Limitations       :   None
* ReturnType        :   Std_ReturnType
*******************************************************************************************/
/*[WDGM168] Implementation of WdgM_GetMode*/


FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_GetMode (P2VAR(WdgM_ModeType,AUTOMATIC,WDGM_APPL_DATA)Mode)
{
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /*TRACE[WDGM253] If WdgM is not intilized GetMode should not be service anymore*/
    if (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_DEACTIVATED) /*WDGM253*/
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_MODE_APIID , WDGM_E_NO_INIT);
        return E_NOT_OK;
    }
    /*TRACE[WDGM254] Check for null parameters*/
    if (Mode == NULL_PTR)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_MODE_APIID, WDGM_E_INV_POINTER);
        return E_NOT_OK;
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
    *Mode = WdgM_Mode;
    return E_OK;
}

/*******************************************************************************************
* Name              :   WdgM_GetLocalStatus
* Description       :   Returns the supervision status of an individual Supervised Entity.
* Parameters[in]    :   SEID
* Parameters[out]   :   Status
* Limitations       :   None
* ReturnType        :   Std_ReturnType
*******************************************************************************************/
/* TRACE[WDGM169] Implementation of WdgM_GetLocalStatus*/
FUNC(Std_ReturnType, WDGM_CODE_FAST)  WdgM_GetLocalStatus(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) SEID,
    P2VAR(WdgM_LocalStatusType,AUTOMATIC,WDGM_APPL_DATA)Status)
{
    /* TRACE[WDGM171] Exclude some checks based on the flags set*/
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM257] Check if WdgM is initilized*/
    if (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_DEACTIVATED)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_LOCAL_STATUS_APIID , WDGM_E_NO_INIT);
        return E_NOT_OK;
    }
    /* TRACE[WDGM172] Check for valid SEID*/
    if (SEID >= WDGM_NO_OF_SUPERVISED_ENTITIES)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_LOCAL_STATUS_APIID , WDGM_E_PARAM_SEID);
        return E_NOT_OK;
    }
    /* TRACE[WDGM257] Check for valid pointer*/
    if (Status == NULL_PTR)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_LOCAL_STATUS_APIID, WDGM_E_INV_POINTER);
        return E_NOT_OK;
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
	/*Interrupt lock: The fetch from a structure could be a non atomic operation*/
    SchM_Enter_WdgM(WDGM_SCHM_EXCLSV_AREA);
    *Status = WdgM_SupervisedEntityDyn[SEID].OldLocalStatus;
    SchM_Exit_WdgM(WDGM_SCHM_EXCLSV_AREA);
    return E_OK;
}

/*******************************************************************************************
* Name              :   WdgM_GetGlobalStatus
* Description       :   Returns the global supervision status of the Watchdog Manager.
* Parameters[out]   :   Status
* Limitations       :   None
* ReturnType        :   Std_ReturnType
*******************************************************************************************/
/* TRACE[WDGM175] Implementation of WdgM_GetGlobalStatus*/


FUNC(Std_ReturnType, WDGM_CODE_FAST)  WdgM_GetGlobalStatus(P2VAR(WdgM_GlobalStatusType,AUTOMATIC,WDGM_APPL_DATA)Status)
{
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM176] Check if WdgM is Initilized*/
    if (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_DEACTIVATED)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_GLOBAL_STATUS_APIID , WDGM_E_NO_INIT);
        return E_NOT_OK;
    }
    /* TRACE[WDGM344] Check if status is a Null Pointer*/
    if (Status == NULL_PTR)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_GLOBAL_STATUS_APIID, WDGM_E_INV_POINTER);
        return E_NOT_OK;
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
	/* No Lock: 8 bit access is assumed to be atomic*/
    *Status = WdgM_GlobalStatus;
    return E_OK;
}

/*******************************************************************************************
* Name              :   WdgM_PerformReset
* Description       :   Instructs the Watchdog Manager to cause a watchdog reset.
* Parameters[in]    :   void
* Limitations       :   None
* ReturnType        :   void
*******************************************************************************************/
/* TRACE[WDGM264] Implementation of WdgM_PerformReset*/


FUNC(void, WDGM_CODE_FAST) WdgM_PerformReset(void)
{
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM270] Check for WdgM is initilized*/
    if (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_DEACTIVATED)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_PERFORM_RESET_APIID , WDGM_E_NO_INIT);
        return;
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
    /* TRACE[WDGM232] Set trigger for all configured to zero */
    /* Deactived so that WdgM Main Function in the next cycle will set value to Zero*/
    WdgM_GlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
    WdgM_Prv_SetTriggerCondition(WDGM_GLOBAL_STATUS_DEACTIVATED);
    return;
}

#define WDGM_STOP_SEC_CODE_FAST
#include "WdgM_Cfg_MemMap.h"

#define WDGM_START_SEC_CODE_SLOW
#include "WdgM_Cfg_MemMap.h"

/*******************************************************************************************
* Name              :   WdgM_GetFirstExpiredSEID
* Description       :   Returns SEID that first reached the state WDGM_LOCAL_STATUS_EXPIRED.
* Parameters[out]   :   SEID
* Limitations       :   None
* ReturnType        :   Std_ReturnType
* NOTE: Source is WdgM specification version 4.0.3 (Its done for future compatibility)
*******************************************************************************************/
/* TRACE[WDGM346] Implementation of WdgM_GetFirstExpiredSEID*/


FUNC(Std_ReturnType, WDGM_CODE_SLOW)  WdgM_GetFirstExpiredSEID(P2VAR(WdgM_SupervisedEntityIdType,AUTOMATIC,WDGM_APPL_DATA)SEID)
{
    VAR(Std_ReturnType, AUTOMATIC) ReturnStatus = E_NOT_OK;
    VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) FirstExpiredSupervisedEntityIdTemp;

#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM347] Check for NULL pointer*/
    if (SEID == NULL_PTR)
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_GET_FIRST_EXPIRED_SEID_APIID, WDGM_E_INV_POINTER);
        return E_NOT_OK;
    }
#endif /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
    /*As per rules a correct entry is one copy of the  FirstExpiredSupervisedEntityId and second copy is
     *the complement of the FirstExpiredSupervisedEntityId both should match whne either one is inverted*/
    /*TRACE[WDGM349] implement the specific format as defined in the specifcations for SEID*/

    FirstExpiredSupervisedEntityIdTemp = WdgM_Prv_ComplementSeId_to_Inl(WdgM_FirstExpiredSupervisedEntityId_Comp);
    if(WdgM_FirstExpiredSupervisedEntityId == FirstExpiredSupervisedEntityIdTemp)
    {
        *SEID = WdgM_FirstExpiredSupervisedEntityId;
        ReturnStatus = E_OK;
    }/*If no correct entry saved in the LOG. This also takes care of corrupt entry case*/
    else
    {
        *SEID = WDGM_PRV_C_ZERO;
    }
    return ReturnStatus;
}

#define WDGM_STOP_SEC_CODE_SLOW
#include "WdgM_Cfg_MemMap.h"

#define WDGM_START_SEC_CODE
#include "WdgM_Cfg_MemMap.h"


/*******************************************************************************************
* Name              :   WdgM_CheckpointReached
* Description       :   Indicates to the Watchdog Manager that a Checkpoint within a Supervised
*                       Entity has been reached.
* Parameters[in]    :   SEID, CheckpointID
* Limitations       :   None
* ReturnType        :   Std_ReturnType
*******************************************************************************************/
/*TRACE[WDGM263] Implementation of WdgM_CheckpointReached*/
/*TRACE[WDGM200] The local supervision status is monitored via WdgM_CheckpointReached */


/* Port defined argument value has been replaced with a macro as the generated variable could not have a user defined name */

#if((WDGM_RTE_DISABLED) == (STD_OFF))
FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_CheckpointReached(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) Rte_PDAV0,
VAR(WdgM_CheckpointIdType,AUTOMATIC) CheckpointID)
#else
FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_CheckpointReached(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) SEID,
VAR(WdgM_CheckpointIdType,AUTOMATIC) CheckpointID)
#endif
{
    #if((WDGM_RTE_DISABLED) == (STD_OFF))
        #define SEID Rte_PDAV0
    #endif
    VAR(uint16,AUTOMATIC) SvIdx;
    VAR(Std_ReturnType,AUTOMATIC) ReturnStatus = E_OK;

#if ((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO))
    VAR(Std_ReturnType,AUTOMATIC) DeadlineReturnStatus;
#endif

#if (WDGM_INTERNAL_GRAPH_CONFIGURED == STD_ON)
    VAR(Std_ReturnType,AUTOMATIC) LogicalReturnStatus;
#endif
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    /* TRACE[WDGM279] Check if WdgM is initilized  */
    if (WdgM_GlobalStatus != WDGM_GLOBAL_STATUS_DEACTIVATED)
    {
        /* TRACE[WDGM278] Check for vaild SEID */
        if (SEID < WDGM_NO_OF_SUPERVISED_ENTITIES)
        {
            /* TRACE[WDGM319] Check if for the given SE ,the checkpoint ID belongs to is set to Active in current mode*/
            /* TRACE[WDGM284] Check for checkpointID is within the associated CheckpointID's for a SE*/
            if(CheckpointID < WdgM_SupervisedEntity[SEID].NoOfCheckpoint)
            {
#endif /* ((WDGM_DEV_ERROR_DETECT) == (STD_ON)) */
                SchM_Enter_WdgM(WDGM_SCHM_EXCLSV_AREA);
                /* Lock introduced:
                 * 1.In WdgM_SupervisedEntityDyn we check for Local status deactivated,
                 * if mode changes here then for newely active or deactive mode we will peform unncessary operation.
                 */
                /*TRACE[WDGM208] Since SEActive is False for DEACTIVATED, no supervision process is performed*/
                if ((WdgM_SupervisedEntityDyn[SEID].NewLocalStatus & WDGM_LOCAL_STATUS_DEACTIVATED) != WDGM_LOCAL_STATUS_DEACTIVATED)
                {
                    /* Alive Supervision */
                    /* Lock introduced:
                     * 1. In WdgM_SupervisedEntityDyn we check for AliveSupervisionIdx,
                     *  which could be corrupted if Mode chage occurs and  WdgM_SupervisedEntityDyn is modified.
                     */
                    SvIdx = WdgM_SupervisedEntityDyn[SEID].AliveSupervisionIdx;
                    /*TRACE[WDGM321] Increment the alive indication counter of reported Checkpoint*/
                    if((SvIdx != WdgM_ConfigSetPtr->PtrToMode[WdgM_Mode].NoOfAliveSupervision)&&
                            (WdgM_ConfigSetPtr->PtrToMode[WdgM_Mode].PtrToAliveSupervision[SvIdx].AliveSupervisionCheckpointId == CheckpointID))
                    {
                        /* Lock introduced:
                         * 1. the ++ is a read modify write operation ,
                         * read: old value
                         * preempt: WdgM_MainFunction: modify source value to 0
                         * modify : old value + 1
                         * write : old value +1 (source has been made 0 hence final should be 0+1)
                         */
                        WdgM_SupervisedEntityDyn[SEID].IndividualAliveUpdateCtr++;
                    }
                    SchM_Exit_WdgM(WDGM_SCHM_EXCLSV_AREA);
                }
                else
                {
                    /*Lock Disable: On failure to enter if case release lock*/
                    SchM_Exit_WdgM(WDGM_SCHM_EXCLSV_AREA);
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
                    /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
                    (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_CHECKPOINT_REACHED_APIID, WDGM_E_SEDEACTIVATED);
                    /*When CPR are reported which do not belong to the current mode no action should be taken hence return E_OK */
                    /*only when DET is enabled should reporting be enabled and E_NOT_OK */
                    ReturnStatus = E_NOT_OK;
#endif /* ((WDGM_DEV_ERROR_DETECT) == (STD_ON)) */
                }
                /* Deadline Supervision */
                /* TRACE[WDGM322] Perform Deadline supervision*/
                /* Lock introduced:
                 * 1. During Deadline Checkpoint Reached we refer the WdgM_Mode which has to be atomic.
                 * 2. Local status is modified here hence to prevent
                 */
#if ((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO))
                WdgM_Prv_DeadlineSupervisionCheckpointReached_v_Inl(SEID, CheckpointID, &DeadlineReturnStatus);
                if (DeadlineReturnStatus != E_OK)
                {
                    ReturnStatus = E_NOT_OK;
                }
#endif
                /* Logical Supervision for Internal Graph*/
#if (WDGM_INTERNAL_GRAPH_CONFIGURED == STD_ON)
                LogicalReturnStatus = WdgM_Prv_LogicalSupervisionCheckpointReached_v_Inl(SEID, CheckpointID);
                if (LogicalReturnStatus != E_OK)
                {
                    ReturnStatus = E_NOT_OK;
                }
#endif

#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
            }
            else
            {
                /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
                (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_CHECKPOINT_REACHED_APIID , WDGM_E_CPID);
                ReturnStatus = E_NOT_OK;
            }
        }
        else
        {
            /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
            (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_CHECKPOINT_REACHED_APIID , WDGM_E_PARAM_SEID);
            ReturnStatus = E_NOT_OK;
        }
    }
    else
    {
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_CHECKPOINT_REACHED_APIID , WDGM_E_NO_INIT);
        ReturnStatus = E_NOT_OK;
    }
#endif /* ((WDGM_DEV_ERROR_DETECT) == (STD_ON)) */
    return ReturnStatus;
}

/*******************************************************************************************
* Name              :   WdgM_MainFunction
* Description       :   Performs the processing of the cyclic Watchdog Manager jobs.
* Parameters[in]    :   void
* Limitations       :   None
* ReturnType        :   void
*******************************************************************************************/
/* TRACE[WDGM159] Implementation of WdgM_MainFunction*/
FUNC(void, WDGM_CODE) WdgM_MainFunction(void)
{  /* AUTOSAR_SRS_BSWGeneral.pdf: WDGM345: BSW00433, BSW00429 allows to be called before OS starts. */
    VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SEID;
    VAR(WdgM_GlobalStatusType, AUTOMATIC) NewGlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
    /*Introduce GlobalStatusCached:
    *1. If RTE update required we store the WdgM_GlobalStatus and compare with NewGlobalStatus.
    */
#if(((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))||((WDGM_RTE_DISABLED) == (STD_OFF))||((WDGM_IMMEDIATE_RESET) == (STD_ON)))
    VAR(WdgM_GlobalStatusType, AUTOMATIC) GlobalStatusCached ;
#endif
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
    WdgM_MainFunction_Cnt_u32++;
#endif  /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/

    /*TRACE[WDGM039] If defensive behaviour is enabeled and WdgM is not Initilized */
    /*TRACE[WDGM292] If global status if DEACTIVATED then return hence do not call Trigger*/
#if(WDGM_DEFENSIVE_BEHAVIOR == STD_ON)
    if (WdgM_GlobalStatus == WDGM_GLOBAL_STATUS_DEACTIVATED)
    {
#if((WDGM_DEV_ERROR_DETECT) == (STD_ON))
        /* As per AUTOSAR spec of DET, the function 'Det_ReportError' always returns E_OK. So the return value can be ignored, and hence it is type casted to type void.*/
        (void)Det_ReportError(WDGM_MODULE_ID, WDGM_INSTANCE_ID, WDGM_MAIN_FUNCTION_APIID , WDGM_E_NO_INIT);
#endif  /*((WDGM_DEV_ERROR_DETECT) == (STD_ON))*/
        return;
    }
#endif /*(WDGM_DEFENSIVE_BEHAVIOR == STD_ON)*/
#if((WDGM_LOCK_DISABLE_FOR_DGS) == (STD_ON))
#else /*(WDGM_LOCK_DISABLE_FOR_DGS == STD_OFF)*/
    SchM_Enter_WdgM(WDGM_SCHM_EXCLSV_AREA);
#endif/*((WDGM_LOCK_DISABLE_FOR_DGS) == (STD_ON))*/
#if(((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))||((WDGM_RTE_DISABLED) == (STD_OFF))||((WDGM_IMMEDIATE_RESET) == (STD_ON)))
    GlobalStatusCached = WdgM_GlobalStatus;
#endif
    if((WdgM_GlobalStatus != WDGM_GLOBAL_STATUS_DEACTIVATED)&&(WdgM_GlobalStatus != WDGM_GLOBAL_STATUS_STOPPED)&&(WdgM_Prv_SetMode_GlobalStatus != WDGM_GLOBAL_STATUS_STOPPED))
    {   /*Enter here if global mode is OK or FAILED*/
        if (WdgM_GlobalStatus != WDGM_GLOBAL_STATUS_EXPIRED)
        {
            /* Update Alive Supervision for All the SupervisedEntity */
            WdgM_Prv_AliveSupervisionMainFunction_v_Inl();
            /* Update Deadline Supervision for All the SupervisedEntity */
            /* Feature enhancement as per comment 11 of Bugzilla Id : 56735 */
#if((WDGM_DEADLINE_TIMEOUT_DETECT == STD_ON) && ((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO)))
            WdgM_Prv_DeadlineSupervisionMainFunction_v_Inl();
#endif /*((WDGM_DEADLINE_TIMEOUT_DETECT == STD_ON) && ((WDGM_MAX_DEADLINE_SUPERVISIONS) > (WDGM_PRV_C_ZERO)))*/
            /* Local State Machine:  */
            WdgM_Prv_LocalStatusMainFunction();
            /* Global State Machine:  */
            /* TRACE[WDGM214] Global State Machine should run after Local State Machine*/
            /* TRACE[WDGM218] If global is OK or FAILED and if local is DEACTIVATE or OK then global state is set to OK*/
            /* TRACE[WDGM078] If global is OK and if local is DEACTIVATE then global state is set to OK*/
            NewGlobalStatus = WDGM_GLOBAL_STATUS_OK;
            for(SEID = WDGM_PRV_C_ZERO; SEID < WDGM_NO_OF_SUPERVISED_ENTITIES; SEID++)
            {
                /* Check for all SE if any local status is EXPIRED, if yes the change gloabal status to STOPPED*/
                /* No lock for Local status as if previous is ok or expired then we work on old value and finally we change to expired*/
                if ((WdgM_SupervisedEntityDyn[SEID].NewLocalStatus & WDGM_LOCAL_STATUS_EXPIRED) == WDGM_LOCAL_STATUS_EXPIRED)
                {
                    /* TRACE[WDGM215] If Global status is OK an any local
                     * status is EXPIRED  then global status is EXPIRED */
                    /* TRACE[WDGM077] If Global status is FAILED an any local
                     *  status is EXPIRED  then global status is EXPIRED */
                    NewGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;
                    /* TRACE[WDGM216] Check if global status is OK, any SEID's
                     * local status is EXPIRED? if yes then global status is EXPIRED
                     * further if expired tolerance is zero change global status to STOPPED */
                    /* TRACE[WDGM117]  Check if global status is FAILED any SEID's
                     * local status is EXPIRED? if yes then global status is EXPIRED
                     * further if expired tolerance is zero change global status to STOPPED */
                    if (WdgM_ConfigSetPtr->PtrToMode[WdgM_Mode].ExpiredSupervisionCycleTol == WDGM_PRV_C_ZERO)
                    {
                        NewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
                    }
                    break;
                }
                /* TRACE[WDGM217] if global and local status is FAILED
                 * and no local STATUS is EXPIRED the global status will remain FAILED*/
                /* TRACE[WDGM076] if global status is OK and any local status is FAILED
                 * and no local is EXPIRED the global status will remain FAILED*/
                /* No lock for Local status as if previous is ok or expired then we work on old local status*/
                else if ((WdgM_SupervisedEntityDyn[SEID].NewLocalStatus & WDGM_LOCAL_STATUS_FAILED)==WDGM_LOCAL_STATUS_FAILED)
                {
                    NewGlobalStatus = WDGM_GLOBAL_STATUS_FAILED;
                }
                else
                {
                    /* Code should not come here this else is for MISRA warning*/
                }
            }
        }
        else
        {
            NewGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;
            /* TRACE[WDGM219] If global is EXPIRED and local status atleast one is
             * EXPIRED and counter less than or equal to tolerance keep global
             * EXPIRED and increment counter*/
            WdgM_ExpiredSupervisionCycleCtr++;
            if (WdgM_ExpiredSupervisionCycleCtr > WdgM_ConfigSetPtr->PtrToMode[WdgM_Mode].ExpiredSupervisionCycleTol)
            {
                /*Interrupt Lock: Disabled
                 *1. Global Status is changed to STOPPED, outside the lock
                 *   only SetMode can change to STOPPED , so no need for lock hence forth.
                 */
                /* TRACE[WDGM220] If global is EXPIRED and local status atleast one is
                 * EXPIRED and counter greater than tolerance make global STOPPED */
                NewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
                /* TRACE[WDGM129] When global status changed to STOPPED inform DEM*/
            }

        } /* TRACE[WDGM221] Since no check for global state STOPPED hence the global status will remain STOPPED */
    }
    else
    {
        if(WdgM_Prv_SetMode_GlobalStatus == WDGM_GLOBAL_STATUS_STOPPED)
        {
            NewGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        }
        else
        {
            NewGlobalStatus = WdgM_GlobalStatus;
        }
    }
#if((WDGM_LOCK_DISABLE_FOR_DGS) == (STD_ON))
#else /*(WDGM_LOCK_DISABLE_FOR_DGS == STD_OFF)*/
	SchM_Exit_WdgM(WDGM_SCHM_EXCLSV_AREA);
#endif/*((WDGM_LOCK_DISABLE_FOR_DGS) == (STD_ON))*/
	/*Move DEM outside the interrupt lock */
#if((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))
	if((NewGlobalStatus == WDGM_GLOBAL_STATUS_STOPPED) && (GlobalStatusCached != WDGM_GLOBAL_STATUS_STOPPED))
	{
        Dem_ReportErrorStatus(WdgM_ConfigSetPtr->ErrorSupervision, DEM_EVENT_STATUS_FAILED);
	}
#endif /*((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))*/
#if((WDGM_RTE_DISABLED) == (STD_OFF))
	/* TRACE[WDGM198] */
	if((GlobalStatusCached!= WDGM_GLOBAL_STATUS_DEACTIVATED) && (GlobalStatusCached!=WDGM_GLOBAL_STATUS_STOPPED))
	{
		if (NewGlobalStatus != GlobalStatusCached)
		{
			switch (NewGlobalStatus)
			{
				case WDGM_GLOBAL_STATUS_OK:
					Rte_Switch_WdgM_globalMode_currentMode(RTE_MODE_WdgM_Mode_SUPERVISION_OK);
					break;
				case WDGM_GLOBAL_STATUS_FAILED:
					Rte_Switch_WdgM_globalMode_currentMode(RTE_MODE_WdgM_Mode_SUPERVISION_FAILED);
					break;
				case WDGM_GLOBAL_STATUS_EXPIRED:
					Rte_Switch_WdgM_globalMode_currentMode(RTE_MODE_WdgM_Mode_SUPERVISION_EXPIRED);
					break;
				case WDGM_GLOBAL_STATUS_STOPPED:
					/* TRACE[WDGM133] Perform MCU Reset*/
#if((WDGM_IMMEDIATE_RESET) == (STD_ON))
					Mcu_PerformReset();
					/* TRACE[WDGM134] Incase of a MCU reset do not inform RTE*/
#else/*(WDGM_IMMEDIATE_RESET == STD_OFF)*/
					Rte_Switch_WdgM_globalMode_currentMode(RTE_MODE_WdgM_Mode_SUPERVISION_STOPPED);
#endif /*((WDGM_IMMEDIATE_RESET) == (STD_ON))*/
					break;
				default: /* WDGM_GLOBAL_STATUS_DEACTIVATED: Reset is pending...!!! */
					break;
			}
        }
	}
#elif((WDGM_IMMEDIATE_RESET) == (STD_ON))
	if((NewGlobalStatus == WDGM_GLOBAL_STATUS_STOPPED)&& (GlobalStatusCached != WDGM_GLOBAL_STATUS_STOPPED))
	{
		Mcu_PerformReset();
	}
#endif /*(WDGM_RTE_DISABLED == STD_OFF)*/
    /* TRACE[WDGM223] Based on global ststua the trigger conditions are set */
    /*Send trigger values the Watchdog*/
    WdgM_Prv_SetTriggerCondition(NewGlobalStatus);
    WdgM_GlobalStatus = NewGlobalStatus;
    return;
}

#define WDGM_STOP_SEC_CODE
#include "WdgM_Cfg_MemMap.h"



























