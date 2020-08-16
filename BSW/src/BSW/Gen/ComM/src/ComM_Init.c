

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "ComM_Priv.h"
/*
 ***************************************************************************************************
 * Defines
 ***************************************************************************************************
 */
/*
 ***************************************************************************************************
 * Type definitions
 ***************************************************************************************************
 */

/*
 ***************************************************************************************************
 * Variables
 ***************************************************************************************************
 */

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
LOCAL_INLINE uint32 ComM_CompareVersionInfo(P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) srcVersionInfo,
                                            P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) destVersionInfo);
#endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)
P2CONST(ComM_GlobalConfigType,AUTOMATIC,COMM_APPL_CONST) ComM_GlobalConfigPtr_pgcs;
#endif


#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"


/***************************************************************************************************
 Function name    : ComM_Init
 Syntax           : void ComM_Init(void)
 Description      : Initializes the AUTOSAR Communication Manager.
 Parameters       : void
 Return value     : void
 ***************************************************************************************************/
FUNC(void,COMM_CODE) ComM_Init
                            (
                             P2CONST(ComM_ConfigType,AUTOMATIC,COMM_APPL_CONST) config
                            )

{
    /* Local Variables Declaration */
    VAR(uint8,AUTOMATIC) ChannelIndex;
    VAR(ComM_UserHandleType,AUTOMATIC) UserIndex;
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

    P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
    P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userConfigPtr_pcs;
    #if(COMM_INHIBITION_ENABLED)
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
    #endif  /*  (COMM_INHIBITION_ENABLED)  */

    #if (COMM_PNC_ENABLED != STD_OFF)
    VAR(uint8,AUTOMATIC) PncIndex;
    P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
    #endif

#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

    Std_VersionInfoType versionInfo;

    /*****************************************DET START************************************************/
    #if (COMM_DEV_ERROR_DETECT == STD_ON)
    /* Check if pointer passed is valid */
    if (config == NULL_PTR)
    {
        /* Report DET with ComM not initialized*/
        (void) Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_INIT_APIID,COMM_E_WRONG_PARAMETERS);
        return;
    }
    #endif
    /*********************************************DET END************************************************/

    /* Read the pre-compile version info  */
    ComM_GetVersionInfo(&versionInfo);
    /* Compare pre-compile & post-build version info  */
    if (ComM_CompareVersionInfo(&versionInfo, config->versionInfo) != C_ZERO)
    {
        /* versionInfo doesnt match .. Inform application */
        ComMAppl_IncompatibleGenerator();
        /* Abort further initialisation ..CanNm will remain in NM_STATE_UNINIT state */
        return;
    }

    /* Get Pointer to Global config structure through the Module Base pointer */
    /* MR12 RULE 11.5 VIOLATION:void pointer is been converted to pointer to ComM_GlobalConfigType before using*/
    ComM_GlobalConfigPtr_pgcs = (P2CONST(ComM_GlobalConfigType,AUTOMATIC,COMM_APPL_CONST))(config->ComM_GlobalConfigData_pcs);

#else
    /* If config variant is Pre compile, then config is unused */
    (void)config;
#endif

    globalRamPtr_ps = &ComM_GlobalStruct;

    #if(COMM_INHIBITION_ENABLED)
    globalRamPtr_ps->ComM_EcuGroupClassification_u8 = ComM_EcuGroupClassification_Init;
    globalRamPtr_ps->ComM_InhibitCounter_u16 = C_ZERO;
    #endif  /*  (COMM_INHIBITION_ENABLED)  */

    #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
        /* Default values are set to ComM_ChannelStruct */
    globalRamPtr_ps->ComM_LimitECUToNoCom_b = FALSE;
    #endif  /*  (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */

    /* IMP : initialization of User and PNC ram structures needs to be done before channel structure,
     * so as to ensure correct values for inhibition counters */


    /* Default value for all user related variables */
    for (UserIndex = C_ZERO ; UserIndex < COMM_NO_OF_USERS ; UserIndex++)
    {
        userRamPtr_ps = &ComM_UserStruct[UserIndex];
        userConfigPtr_pcs = &(COMM_GET_USER_LIST[UserIndex]);
        userRamPtr_ps->RequestedUserMode_t = COMM_NO_COMMUNICATION;
        userRamPtr_ps->numChannelsInFullCom_u8 = C_ZERO;
        userRamPtr_ps->numChannelsInSilentCom_u8 = C_ZERO;
        userRamPtr_ps->numChannelsInNoCom_u8 = userConfigPtr_pcs->NumAllChannels_u8;

        /* Initialise the indicated mode for all users as NO_COMMUNICATION */
        userRamPtr_ps->LimitToNoComCtr_u16 = C_ZERO;
        userRamPtr_ps->WakeUpInhibitionCtr_u16 = C_ZERO;

        userRamPtr_ps->IndicatedUserMode_t = COMM_NO_COMMUNICATION;
    }

    #if (COMM_PNC_ENABLED != STD_OFF)
    /* Initialize all the PNC ram structures */
    for (PncIndex = C_ZERO; PncIndex < COMM_NO_OF_PNCS ;PncIndex++)
    {
        pncRamPtr_ps = &ComM_PncRamStruct[PncIndex];
        #if (COMM_PNC_GW_ENABLED != STD_OFF)
        pncRamPtr_ps->ActiveERACnt_u8 = C_ZERO;
        pncRamPtr_ps->ERACnt_u8 = C_ZERO;
        pncRamPtr_ps->ActiveERAStateOld_b = FALSE;
        #endif  /*  (COMM_PNC_GW_ENABLED != STD_OFF)  */
        pncRamPtr_ps->EIRACnt_u8 = C_ZERO;
        pncRamPtr_ps->PncState_e = PNC_NO_COMMUNICATION;
        pncRamPtr_ps->PrepareSleepTimer_u16 = C_ZERO;
        pncRamPtr_ps->UserRequestCnt_u8 = C_ZERO;
        pncRamPtr_ps->WakeUpStatus_b = FALSE;
        #if(COMM_INHIBITION_ENABLED)
        /* Initialize inhibition counters to C_ZERO, this will be later intialized in the channel structure
         * depending on inhibition value */
        pncRamPtr_ps->LimitToNoComCtr_u16 = C_ZERO;
        pncRamPtr_ps->WakeUpInhibitionCtr_u16 = C_ZERO;
        #endif  /* (COMM_INHIBITION_ENABLED)  */
    }
    #endif  /*  (COMM_PNC_ENABLED != STD_OFF)  */

    /* Default value for all channel related variables */
    for (ChannelIndex = C_ZERO ; ChannelIndex < COMM_NO_OF_CHANNELS ; ChannelIndex++)
    {
        channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];
        #if(COMM_INHIBITION_ENABLED)
        channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[ChannelIndex]);
        #endif  /* (COMM_INHIBITION_ENABLED)  */
        /* Default values are set to ComM_ChannelStruct */
        channelRamPtr_ps->CommunicationAllowed_b = FALSE;
        channelRamPtr_ps->ChannelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
        channelRamPtr_ps->ChannelMode_u8 = COMM_NO_COMMUNICATION;
        channelRamPtr_ps->BusSmMode_u8 = COMM_NO_COMMUNICATION;
        channelRamPtr_ps->PassiveRequestState_u8 = C_ZERO;
        channelRamPtr_ps->UserRequestCtr_u8 = C_ZERO;
        channelRamPtr_ps->PncRequestCtr_u8 = C_ZERO;
        #if(COMM_INHIBITION_ENABLED)
        channelRamPtr_ps->InhibitionReqStatus_u8 = channelConfigPtr_pcs->InhibitionInitValue_u8;
        #else
        channelRamPtr_ps->InhibitionReqStatus_u8 = C_ZERO;
        #endif  /* (COMM_INHIBITION_ENABLED)  */
        #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
        if(COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8)) != FALSE)
        {
            ComM_LTranslateInhibitionStatus(ChannelIndex,COMM_LIMITTONOCOM,TRUE);
        }
        #endif  /* (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */
        #if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)
        if(COMM_GET_PREVENT_WAKEUP((channelRamPtr_ps->InhibitionReqStatus_u8)) != FALSE)
        {
            ComM_LTranslateInhibitionStatus(ChannelIndex,COMM_PREVENTWAKEUP,TRUE);
        }
        #endif  /* (COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)  */
        channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE;
        channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b = FALSE;
        channelRamPtr_ps->DiagnosticRequestState_b = COMM_INACTIVE_DIAGNOSTICS;
        channelRamPtr_ps->NmNetworkModeStatus_b = FALSE;
        channelRamPtr_ps->NmNetworkRequestStatus_b = FALSE;
        channelRamPtr_ps->MinFullComTimeoutCtr_u16 = C_ZERO;
    }
    /*  Assign the status of ComM as Initialized*/
    globalRamPtr_ps->ComM_InitStatus = COMM_INIT;

}


/**
 ***************************************************************************************************
 * ComM_CompareVersionInfo - compare version info structures ie of type Std_VersionInfoType
 *
 * compare version info structures ie of type Std_VersionInfoType.
 *
 * \param   srcVersionInfo      pointer to first Std_VersionInfoType structure
 * \param   destVersionInfo     pointer to second Std_VersionInfoType structure
 * \return  stEqual_u32         result of comparison
 * \retval  0                   memory area contents are equal
 * \retval  1                   memory area contents differ
  ***************************************************************************************************
 */
#if(COMM_CONFIGURATION_VARIANT != COMM_VARIANT_PRECOMPILE)

LOCAL_INLINE uint32 ComM_CompareVersionInfo(P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) srcVersionInfo,
                                            P2CONST(Std_VersionInfoType, AUTOMATIC, COMM_APPL_CONST) destVersionInfo)
{
    uint32 stEqual_u32;
    stEqual_u32 = 1;
    if ((srcVersionInfo->vendorID == destVersionInfo->vendorID) &&
        (srcVersionInfo->moduleID == destVersionInfo->moduleID) &&
        (srcVersionInfo->sw_major_version == destVersionInfo->sw_major_version) &&
        (srcVersionInfo->sw_minor_version == destVersionInfo->sw_minor_version) &&
        (srcVersionInfo->sw_patch_version == destVersionInfo->sw_patch_version)
    )
    {
        stEqual_u32 = 0;
    }
    return stEqual_u32;
}

#endif

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

