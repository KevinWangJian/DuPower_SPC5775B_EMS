
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

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

/* UNSPECIFIED variable definitions */

VAR(ComM_GlobalVarType,COMM_VAR) ComM_GlobalStruct;
VAR(ComM_UserVarType,COMM_VAR)  ComM_UserStruct[COMM_NO_OF_USERS];
VAR(ComM_ChannelVarType,COMM_VAR)  ComM_ChannelStruct[COMM_NO_OF_CHANNELS];

#if (COMM_PNC_ENABLED != STD_OFF)

VAR(ComM_PncRamStructType,COMM_VAR) ComM_PncRamStruct[COMM_NO_OF_PNCS];
VAR(boolean,COMM_VAR) ComM_EIRA_RxSigVal[COMM_NO_OF_POSSIBLE_BUSTYPECH_WITH_EIRA][COMM_NO_OF_PNCS];

#if (COMM_PNC_GW_ENABLED != STD_OFF)
VAR(boolean,COMM_VAR) ComM_ERA_RxSigVal[COMM_NO_OF_CH_WITH_ERA][COMM_NO_OF_PNCS];
#endif      /* (COMM_PNC_GW_ENABLED != STD_OFF) */

#endif        /* (COMM_PNC_ENABLED != STD_OFF) */

#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "ComM_Cfg_MemMap.h"

#if(COMM_INHIBITION_ENABLED)
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LTranslateInhibitionToUser
                                            (
                                            P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Users_p,
                                            uint8 numUsers,
                                            ComM_InhibitionType InhibitionType,
                                            boolean Status
                                            );
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateInhibitionCounter
                                            (
                                            P2VAR(uint16, AUTOMATIC,COMM_APPL_DATA) InhibitionCounter_u8,
                                            boolean Status
                                            );
#endif/*  (COMM_INHIBITION_ENABLED)  */

#if (COMM_PNC_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/* ComM_LPncToChannelInterface */
/**************************************************************************************
 * Function name    : ComM_LPncToChannelInterface
 * Syntax           : ComM_LPncToChannelInterface
 *                    (
 *                    VAR(PNCHandleType PncIndex,ComM_PncModeType PncState,ComM_PncModeType PncPreviousState
 *                    )
 * Description      : Interface between PNC and channel state machines.
 * Parameters       : PncIndex : PNC Id
 *                       PncState : Current State of PNC
 *                       PncPreviousState : Previous PNC state
 * Return value     : void
 **************************************************************************************/

FUNC(void,COMM_CODE) ComM_LPncToChannelInterface
                                (
                                    PNCHandleType PncIndex,ComM_PncModeType PncState,ComM_PncModeType PncPreviousState
                                )

{
    /* Local variable declaration */
    VAR(uint8,AUTOMATIC) loopCtr_u8;
    VAR(uint8,AUTOMATIC) ChannelId;
    VAR(uint8,AUTOMATIC) numChannels;

    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    /* Local variable initialization */
    pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[PncIndex]);
    numChannels = pncConfigPtr_pcs->NumChannels;

    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {

    /* Protect this area, so that multiple PNC's should not interfere with each other */
    SchM_Enter_ComM_PNCNoNest();
    /* For all channels of this PNC, evaluate the number of PNC's requested or released */
    for(loopCtr_u8 = 0; loopCtr_u8 < numChannels ;loopCtr_u8++)
    {
        ChannelId = (pncConfigPtr_pcs->Channels[loopCtr_u8]);

        channelRamPtr_ps = &ComM_ChannelStruct[ChannelId];

        channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[ChannelId]);

        /* As the PNC state is PNC_REQUESTED, increment the counter */
        if (PncState == PNC_REQUESTED)
        {
            ++(channelRamPtr_ps->PncRequestCtr_u8);

            /* If PncNmRequest is enabled, for this channel, set NmNetworkRequestStatus so that
             * Network is requested in the channel main function   */
            if(channelConfigPtr_pcs->PncNmRequest != FALSE)
            {
                /* This variable need not be locked with channel lock, as in the channel main function,
                 * this is cleared only if it is set and processed. Hence there cannot be any inconsistencies */
                channelRamPtr_ps->NmNetworkRequestStatus_b = TRUE;
            }
        }

        /* As the PNC has changed from PNC_REQUESTED to PNC_READY_SLEEP state, decrement the counter */
        else if((PncState == PNC_READY_SLEEP) && (PncPreviousState == PNC_REQUESTED))
        {
            if(channelRamPtr_ps->PncRequestCtr_u8 != C_ZERO)
            {
                --(channelRamPtr_ps->PncRequestCtr_u8);
            }
            else
            {
                /* Control shouldn't come here.If at all happens, report to DET */
                #if (COMM_DEV_ERROR_DETECT != STD_OFF)
                (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_PNC_MAINFNC_APIID,COMM_E_CNTR_UNDERFLW);
                #endif  /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */
            }
        }
        else
        {
            /* No affect on the channel state machine */
        }
    }
    SchM_Exit_ComM_PNCNoNest();
    }
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif        /* (COMM_PNC_ENABLED != STD_OFF) */


#if (COMM_PNC_ENABLED != STD_OFF)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
/* ComM_EIRA_CallBack */
/**************************************************************************************
 * Function name    : ComM_EIRA_CallBack
 * Syntax           : ComM_EIRA_CallBack
 *                    (
 *                    uint8 PncIndex,Com_SignalIdType SignalId
 *                    )
 * Description      : EIRA call back, whenever the value of signal changes
 * Parameters       : PncIndex : PNC Id
 *                       SignalId : Signal Id of EIRA signal
 * Return value     : void
 **************************************************************************************/

FUNC(void,COMM_CODE) ComM_EIRA_CallBack
                            (
                            uint8 PnBusId
                            )
{
    /*Local variable declaration*/
    uint8 PncIndex;
    const uint16* row;
    uint16 ComSigId_u16;
    boolean SigValue_b;
    P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
    /* Local variable initialization */

    SchM_Enter_ComM_EIRANoNest();
    row = COMM_GET_EIRASIG_TABLE[PnBusId];


    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {

      /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
       * Hence it is an incorrect warning reported by Misra */
        for (PncIndex = 0, pncRamPtr_ps = &ComM_PncRamStruct[0]; PncIndex < COMM_NO_OF_PNCS ; PncIndex++,pncRamPtr_ps++)
        {
            ComSigId_u16 = row[PncIndex];

            if(ComSigId_u16 != COMM_COMSIGNAL_INVALID_ID)
            {

              /* MR12 DIR 1.1 VIOLATION: Com_ReceiveSignal's SignalDataPtr return value should be void as per Autosar guidelines. */
               (void)Com_ReceiveSignal(ComSigId_u16,&SigValue_b);

                if(ComM_EIRA_RxSigVal[PnBusId][PncIndex]!= SigValue_b)
                {
                    ComM_EIRA_RxSigVal[PnBusId][PncIndex] = SigValue_b;

                    if(SigValue_b != FALSE)
                    {
                        ++pncRamPtr_ps->EIRACnt_u8;
                    }
                    else
                    {
                        --pncRamPtr_ps->EIRACnt_u8;
                    }
                }
            }
        }
    }
    SchM_Exit_ComM_EIRANoNest();

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif        /* (COMM_PNC_ENABLED != STD_OFF)  */


#if (COMM_PNC_ENABLED != STD_OFF)

#if (COMM_PNC_GW_ENABLED != STD_OFF)

/* ComM_ERA_CallBack */
/**************************************************************************************
 * Function name    : ComM_ERA_CallBack
 * Syntax           : ComM_ERA_CallBack
 *                    (
 *                    uint8 PncIndex,Com_SignalIdType SignalId,uint8 ChannelId
 *                    )
 * Description      : ERA call back, whenever the signal value changes
 * Parameters       : PncIndex : PNC Id
 *                       SignalId : Signal ID of ERA signal
 *                       ChannelId : Id of channel whose ERA value has changed
 * Return value     : void
 **************************************************************************************/

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(void,COMM_CODE) ComM_ERA_CallBack
                            (
                            uint8 PnBusId,ComM_PncGatewayType channelGwType
                            )
{
    /*Local variable declaration*/
    uint8 PncIndex;
    boolean SigValue_b;
    uint16 ComSigId_u16;
    const uint16* row;
    P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
    /*Local variable initialization*/

    SchM_Enter_ComM_ERANoNest();

    row = COMM_GET_ERASIG_TABLE[PnBusId];

    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {
        /* MR12 RULE 14.2 VIOLATION: The variable incremented in the third expression of this 'for' statement is actually the variable identified as the 'loop control variable.
               * Hence it is an incorrect warning reported by Misra */
        for(PncIndex=0, pncRamPtr_ps = &ComM_PncRamStruct[0]; PncIndex < COMM_NO_OF_PNCS; PncIndex++,pncRamPtr_ps++)
        {
            ComSigId_u16 = row[PncIndex];

            if(ComSigId_u16 != COMM_COMSIGNAL_INVALID_ID)
            {
               /* MR12 DIR 1.1 VIOLATION: Com_ReceiveSignal's SignalDataPtr return value should be void as per Autosar guidelines. */
                (void)Com_ReceiveSignal(ComSigId_u16,&SigValue_b);

                if(ComM_ERA_RxSigVal[PnBusId][PncIndex] != SigValue_b)
                {
                    ComM_ERA_RxSigVal[PnBusId][PncIndex] = SigValue_b;

                    if(SigValue_b != FALSE)
                    {
                        /* ActiveERACnt_u8 and ERACnt_u8 has to be updated and read consistently. But with the below order of implementation,
                         * locks are not required  in the Pnc main function */
                        /* If ActiveERACnt_u8 is updated before ERACnt_u8,then
                         * even though main function interrupts this function, when ActiveERACnt_u8 is updated but ERACnt_u8 is not updated,
                         * state change will not happen and both these updated counters are considered only in the next Pnc main function.
                         * Thus avoiding locks.*/

                        /* If the channel is coordinated actively, then increment the ActiveERACnt_u8 counter */
                        if (channelGwType == COMM_GATEWAY_TYPE_ACTIVE)
                        {
                            ++pncRamPtr_ps->ActiveERACnt_u8;
                        }
                        ++(pncRamPtr_ps->ERACnt_u8);
                    }
                    else
                    {
                        /* ActiveERACnt_u8 and ERACnt_u8 has to be updated and read consistently. But with the below order of implementation,
                         * locks are not required  in the Pnc main function */
                        /* If ActiveERACnt_u8 is updated before ERACnt_u8,then
                         * even though main function interrupts this function, when ActiveERACnt_u8 is updated but ERACnt_u8 is not updated,
                         * state change will not happen and both these updated counters are considered only in the next Pnc main function.
                         * Thus avoiding locks.*/
                        /* If the channel is coordinated actively, then increment the ActiveERACnt_u8 counter */
                        if (channelGwType == COMM_GATEWAY_TYPE_ACTIVE)
                        {
                            --pncRamPtr_ps->ActiveERACnt_u8;
                        }
                        --(pncRamPtr_ps->ERACnt_u8);
                    }
                }
            }
        }
    }

    SchM_Exit_ComM_ERANoNest();

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif      /* (COMM_PNC_GW_ENABLED != STD_OFF)  */
#endif      /* (COMM_PNC_ENABLED != STD_OFF)  */


#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/* ComM_LgetLeastComMode */
/**************************************************************************************
 * Function name    : ComM_LgetLeastBusSmMode
 * Syntax           : ComM_LgetLeastBusSmMode
 *                    (
 *                    ComM_UserHandleType UserIndex
 *                    )
 * Description      : Internal function to get the least BusSM mode among all channels
 * Parameters       : UserIndex : User Id
 * Return value     : ComM_ModeType : Least busSm mode of all channels
 **************************************************************************************/

FUNC(ComM_ModeType, COMM_CODE) ComM_LgetLeastBusSmMode(ComM_UserHandleType UserIndex)

{

    /* Local variables declaration */

    VAR(ComM_ModeType,AUTOMATIC) leastModeAmongChannels_e;
    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

    userRamPtr_ps = &ComM_UserStruct[UserIndex];

    if(userRamPtr_ps->numChannelsInNoCom_u8 != C_ZERO)
    {
        leastModeAmongChannels_e = COMM_NO_COMMUNICATION;
    }
    else if(userRamPtr_ps->numChannelsInSilentCom_u8 != C_ZERO)
    {
            leastModeAmongChannels_e = COMM_SILENT_COMMUNICATION;
    }
    else
    {
        leastModeAmongChannels_e = COMM_FULL_COMMUNICATION;
    }
    return leastModeAmongChannels_e;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

/***************************************************************************************************
 * Function name    : ComM_LTranslateInhibitionStatus
 * Syntax           : ComM_LTranslateInhibitionStatus
 *                    (
 *                     NetworkHandleType Channel,ComM_InhibitionType InhibitionType, boolean Status
 *                    )
 * Description      : Local function to translate channels inhibition status to users and PNC's.
 *                    To be called only if the change in inhibition status is valid, as this check is not present
 *                    in the API
 * Parameters       : Channel -> Handle to identify a communication channel
 *                    InhibitionType -> prevent wake up or limit to no com
 *                    Status -> Inhibition requested or released status
 * Return value     : void
 **************************************************************************************************/

#if(COMM_INHIBITION_ENABLED)

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
FUNC(void, COMM_CODE) ComM_LTranslateInhibitionStatus
                                            (
                                            NetworkHandleType Channel,
                                            ComM_InhibitionType InhibitionType,
                                            boolean Status
                                            )
{
    /* Local variable declaration */

    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    #if (COMM_PNC_ENABLED != STD_OFF)
    uint8 numPnc_u8;
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) pncs_p;
    #endif

    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);

    #if (COMM_PNC_ENABLED != STD_OFF)
    pncs_p = channelConfigPtr_pcs->Pncs_p;
    #endif /*  (COMM_PNC_ENABLED != STD_OFF)  */
    /* For all users and PNC's of channel update inhibition counter depending on the inhibition type and requested status */

    /* IMP : API is called only if the change in inhibition status is valid */

    /* Depending on the inhibition type and requested status update inhibition counter
     * 1. For all direct users of channel
     * 2. For all PNC's of channel
     * 3. For all users assigned to PNC of channel */

    /* 1. For all direct users of the channel */
    ComM_LTranslateInhibitionToUser(channelConfigPtr_pcs->DirectUsers_p,channelConfigPtr_pcs->numDirectUsers_u8, InhibitionType,Status);

    #if(COMM_PNC_ENABLED != STD_OFF)
    /* If PNC is enabled, 2. For all PNC's of channel */

    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {
        for(numPnc_u8 = C_ZERO; numPnc_u8 < channelConfigPtr_pcs->numPncs_u8; ++numPnc_u8)
        {
            uint8 pncId_u8;
            P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
            P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;

            pncId_u8 = pncs_p[numPnc_u8];
            pncRamPtr_ps = &ComM_PncRamStruct[pncId_u8];
            pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[pncId_u8]);

            if(InhibitionType == COMM_PREVENTWAKEUP)
            {
                ComM_LUpdateInhibitionCounter(&(pncRamPtr_ps->WakeUpInhibitionCtr_u16),Status);
            }
            else
            {
                ComM_LUpdateInhibitionCounter(&(pncRamPtr_ps->LimitToNoComCtr_u16),Status);
            }

            /* 3. For all users assigned to PNC of channel  */
            ComM_LTranslateInhibitionToUser(pncConfigPtr_pcs->Users_p,pncConfigPtr_pcs->NumUsers_u8,InhibitionType,Status);

        }
    }
    #endif  /*  if(COMM_PNC_ENABLED != STD_OFF)  */
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /*  (COMM_INHIBITION_ENABLED)  */

#if(COMM_INHIBITION_ENABLED)

/****************************************************************************************************************
 * Function name    : ComM_LTranslateInhibitionToUser
 * Syntax           : ComM_LTranslateInhibitionToUser
 *                    (
 *                     P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Users_p,ComM_InhibitionType InhibitionType,
 *                     boolean Status,uint8 numUsers
 *                    )
 * Description      : Local function to translate channel's inhibition status to users.
 * Parameters       : Users_p -> Pointer to users of channel or PNC to which inhibition status has to be translated
 *                    numUsers -> Number of users of channel or PNC to which inhibition status has to be translated
 *                    InhibitionType -> prevent wake up or limit to no com
 *                    Status -> Inhibition requested or released status
 * Return value     : void
 ****************************************************************************************************************/
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LTranslateInhibitionToUser
                                            (
                                            P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) Users_p,
                                            uint8 numUsers,
                                            ComM_InhibitionType InhibitionType,
                                            boolean Status
                                            )
    {
    uint8 loopCounter_u8;
    uint8 userId_u8;
    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;
    for(loopCounter_u8 = C_ZERO; loopCounter_u8 < numUsers; ++loopCounter_u8)
        {
        userId_u8 = Users_p[loopCounter_u8];
            userRamPtr_ps = &ComM_UserStruct[userId_u8];
            if(InhibitionType == COMM_PREVENTWAKEUP)
            {
            ComM_LUpdateInhibitionCounter(&(userRamPtr_ps->WakeUpInhibitionCtr_u16),Status);
            }
            else
            {
            ComM_LUpdateInhibitionCounter(&(userRamPtr_ps->LimitToNoComCtr_u16),Status);
            }
        }

            }
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif /*  (COMM_INHIBITION_ENABLED)  */


#if(COMM_INHIBITION_ENABLED)

/****************************************************************************************************************
 * Function name    : ComM_LUpdateInhibitionCounter
 * Syntax           : ComM_LUpdateInhibitionCounter
 *                    (
 *                     P2VAR(uint8, AUTOMATIC,COMM_APPL_DATA) InhibitionCounter_u8,
 *                     boolean Status
 *                    )
 * Description      : Local function to update inhibition counter depending on status.
 * Parameters       : InhibitionCounter_u8 -> Pointer to inhibition counter to be updated
 *                    Status -> Inhibition requested or released status
 * Return value     : void
 ****************************************************************************************************************/
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_LUpdateInhibitionCounter
                                            (
                                            P2VAR(uint16, AUTOMATIC,COMM_APPL_DATA) InhibitionCounter_u8,
                                            boolean Status
                                            )
{
    if(Status != FALSE)
    {
        ++(*InhibitionCounter_u8);
    }
    else
    {
        --(*InhibitionCounter_u8);
    }
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"
#endif/*  (COMM_INHIBITION_ENABLED)  */


/***************************************************************************************************
 * Function name    : ComM_LUpdateChannelModes
 * Syntax           : ComM_LUpdateChannelModes
 *                    (
 *                     NetworkHandleType Channel,ComM_ModeType PreviousMode, ComM_ModeType CurrentMode
 *                    )
 * Description      : Internal function to update channel mode counters for a user
 *                    This function is called within channel lock, so consistency is taken care
 * Parameters       : Channel -> Handle to identify a communication channel
 *                    PreviousMode -> Previous mode of the channel
 *                    CurrentMode -> Changed mode of the channel
 * Return value     : void
 **************************************************************************************************/
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(void, COMM_CODE) ComM_LUpdateChannelModes(NetworkHandleType Channel,
                                ComM_ModeType PreviousMode, ComM_ModeType CurrentMode)
{
    /* Local variable declaration */
    uint8 numUsers_u8;
    uint8 userId_u8;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;
    P2CONST(uint8,COMM_CONST,COMM_APPL_CONST) allUsers_p;

    #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
    P2CONST(ComM_UsersType,AUTOMATIC,COMM_APPL_CONST) userConfigPtr_pcs;
    #endif

    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[Channel]);
    allUsers_p = channelConfigPtr_pcs->AllUsers_p;

    if(PreviousMode != CurrentMode)
    {
        for(numUsers_u8= C_ZERO; numUsers_u8 < channelConfigPtr_pcs->numAllUsers_u8; ++numUsers_u8)
        {
            SchM_Enter_ComM_Channel();
            userId_u8 = allUsers_p[numUsers_u8];
            userRamPtr_ps = &ComM_UserStruct[userId_u8];

            #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
            userConfigPtr_pcs = &(COMM_GET_USER_LIST[userId_u8]);
            #endif  /*  if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */

            /* Depending on previous mode, decrement respective counter */
            switch(PreviousMode)
            {
                case COMM_NO_COMMUNICATION : --(userRamPtr_ps->numChannelsInNoCom_u8);
                    break;
                case COMM_FULL_COMMUNICATION: --(userRamPtr_ps->numChannelsInFullCom_u8);
                    break;
                case COMM_SILENT_COMMUNICATION: --(userRamPtr_ps->numChannelsInSilentCom_u8);
                    break;
                default:
                    /* Intentionally Empty */
                    break;
            }

            /* Depending on current mode, increment respective counter */
            switch(CurrentMode)
            {
                case COMM_NO_COMMUNICATION : ++(userRamPtr_ps->numChannelsInNoCom_u8);
                    break;
                case COMM_FULL_COMMUNICATION: ++(userRamPtr_ps->numChannelsInFullCom_u8);
                    break;
                case COMM_SILENT_COMMUNICATION: ++(userRamPtr_ps->numChannelsInSilentCom_u8);
                    break;
                default:
                    /* Intentionally Empty */
                    break;
            }

            #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
            /* If limit to no com is enabled and all channels of the user are in NO_COMMUNICATION,
             * clear the user request */
            if((userRamPtr_ps->LimitToNoComCtr_u16 > C_ZERO) &&
                    ((userRamPtr_ps->numChannelsInNoCom_u8) == (userConfigPtr_pcs->NumAllChannels_u8)))
            {
                (void)ComM_RequestComMode(userId_u8,COMM_NO_COMMUNICATION);
            }
            #endif /*  if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */

            #if(COMM_RTE_SUPPORT != STD_OFF)
            /* Notify RTE if the least ComMode of the user changes  */
            ComM_LRteNotifyLowestComMode(userId_u8);
            #endif  /*  if(COMM_RTE_SUPPORT != STD_OFF)  */
            SchM_Exit_ComM_Channel();
        }
    }
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"


#if (COMM_RTE_SUPPORT != STD_OFF)

/* ComM_LRteNotifyLowestComMode */
/**************************************************************************************
 * Function name    : ComM_LRteNotifyLowestComMode
 * Syntax           : ComM_LRteNotifyLowestComMode
 *                    (
 *                     ComM_UserHandleType UserIndex
 *                    )
 * Description      : Internal function to notify the lowest com mode of user to RTE
 * Parameters       : UserIndex : User Id
 * Return value     : void
 **************************************************************************************/
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC( void, COMM_CODE) ComM_LRteNotifyLowestComMode
                                                (
                                                    ComM_UserHandleType UserIndex
                                                )
{

    ComM_ModeType lowestUserMode;
    P2VAR(ComM_UserVarType, AUTOMATIC, COMM_APPL_DATA) userRamPtr_ps;

    userRamPtr_ps = &ComM_UserStruct[UserIndex];

    lowestUserMode = ComM_LgetLeastBusSmMode(UserIndex);

    /* Notify the lowest mode to RTE only if there is a change in the mode w.r.t the
     * previously indicated mode */

    if(userRamPtr_ps->IndicatedUserMode_t != lowestUserMode)
    {
        userRamPtr_ps->IndicatedUserMode_t = lowestUserMode;
        ComM_Rte_Switch_UM_currentMode (UserIndex,lowestUserMode);
    }

}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"
#endif  /*  if(COMM_RTE_SUPPORT != STD_OFF)  */



#if (COMM_SYNCHRONOUS_WAKE_UP != STD_OFF )

/* ComM_LSyncWakeUpIndication */
/**************************************************************************************
 * Function name    : ComM_LSyncWakeUpIndication
 * Syntax           : ComM_LSyncWakeUpIndication
 *                    (
 *                     void
 *                    )
 * Description      : Internal function to set wakeup indication for all channels and PNC's
 *                    Used Only when synchronous wake up feature is enabled.
 * Parameters       : void
 * Return value     : void
 **************************************************************************************/

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"

FUNC(void, COMM_CODE) ComM_LSyncWakeUpIndication(void)
{
    VAR(uint8,AUTOMATIC) loopCtr_u8;

    SchM_Enter_ComM_ChannelNoNest();

    for (loopCtr_u8 = C_ZERO; loopCtr_u8 < COMM_NO_OF_CHANNELS ;loopCtr_u8++)
    {
        P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
        channelRamPtr_ps = &ComM_ChannelStruct[loopCtr_u8];

        if(channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)
        {
            COMM_SET_BIT((channelRamPtr_ps -> PassiveRequestState_u8),(0x01));
        }

    }
    SchM_Exit_ComM_ChannelNoNest();

    #if (COMM_PNC_ENABLED != STD_OFF)
    /* Check for PNC enabled */

    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED != FALSE)
    {
        P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
        SchM_Enter_ComM_PNCWakeUpNoNest();

        for (loopCtr_u8 = C_ZERO; loopCtr_u8 < COMM_NO_OF_PNCS ;loopCtr_u8++)
        {
            pncRamPtr_ps = &ComM_PncRamStruct[loopCtr_u8];

            if(pncRamPtr_ps->PncState_e == PNC_NO_COMMUNICATION)
            {
                pncRamPtr_ps->WakeUpStatus_b = TRUE;
            }
        }
        SchM_Exit_ComM_PNCWakeUpNoNest();
    }

    #endif  /*   (COMM_PNC_ENABLED != STD_OFF)  */
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif


/***************************************************************************************************
 * Function name    : ComM_Nm_TransmissionFailure
 * Syntax           : ComM_Nm_TransmissionFailure
 *                    (
 *                     NetworkHandleType Channel
 *                    )
 * Description      : Indicates that NM message transmission has failed
 * Parameters       : Channel -> Handle to identify a communication channel
 * Return value     : void
 **************************************************************************************************/

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
FUNC(void, COMM_CODE) ComM_Nm_TransmissionFailure
(
  VAR(NetworkHandleType,AUTOMATIC) Channel
)
{
    (void)(Channel);
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"


/*****************************************************************************************************
 * Function name    : ComM_Nm_NetworkTimeoutException
 * Syntax           : ComM_Nm_NetworkTimeoutException
 *                    (
 *                    NetworkHandleType Channel
 *                    )
 * Description      : Indicates that NM-Timeout time has expired when Network is still not released
 * Parameters       : Channel -> Handle to identify a communication channel
 * Return value     : void
 ****************************************************************************************************/

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
FUNC(void, COMM_CODE) ComM_Nm_NetworkTimeoutException
(
  VAR(NetworkHandleType,AUTOMATIC) Channel
)
{
    (void)(Channel);
}
#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

