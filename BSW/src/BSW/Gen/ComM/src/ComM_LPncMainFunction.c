


/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "ComM_Priv.h"

#if (COMM_PNC_ENABLED != STD_OFF)

/*
 ***************************************************************************************************
 * Variables
 ***************************************************************************************************
 */


/*
 ***************************************************************************************************
 * Inline functions declarations
 ***************************************************************************************************
 */
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncNoCommunication_StateHandling
                                                        (
                                                             VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                             P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                             P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                             VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncRequested_StateHandling
                                                        (
                                                             VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                             P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                             P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                             P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                                                             VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncPrepareSleep_StateHandling
                                                        (
                                                            VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                            P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                            P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                            P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                                                            VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );

LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncReadySleep_StateHandling
                                                        (
                                                            VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                            P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                            P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                            P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                                                            VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                        );




/* ComM_LPncMainFunction */
/**************************************************************************************
 * Function name    : ComM_LPncMainFunction
 * Syntax           : ComM_LPncMainFunction
 *                    (
 *                    VAR(PNCHandleType,AUTOMATIC) PncIndex
 *                    )
 * Description      : Function which contains different states and happening in various stages.
 * Parameters       : PncIndex
 * Return value     : void
 **************************************************************************************/

#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
FUNC( void, COMM_CODE) ComM_LPncMainFunction
                                        (
                                            VAR(PNCHandleType,AUTOMATIC) PncIndex
                                        )
{
    /* Local variable declaration */
    VAR(ComM_PncModeType,AUTOMATIC)  pncStateOnEntry_e;
    P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps;
    P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs;
    VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e;
    VAR(ComM_PncEventStructType,COMM_VAR) PncEventStruct;
    P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps;
    boolean stateChangePossible_b;
    boolean userRequestState_b;

    #if(COMM_INHIBITION_ENABLED)
    P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
    #endif  /*  #if (COMM_INHIBITION_ENABLED)  */
    /* Initialization of locals */

    PncEventStruct_ps = &PncEventStruct;
    stateChangePossible_b = FALSE;
    PncEventStruct_ps->wakeupRequestState_b = FALSE;
    pncRamPtr_ps = &ComM_PncRamStruct[PncIndex];
    pncConfigPtr_pcs = &(COMM_GET_PNC_LIST[PncIndex]);
    #if(COMM_INHIBITION_ENABLED)
    globalRamPtr_ps = &ComM_GlobalStruct;
    #endif  /*  #if (COMM_INHIBITION_ENABLED)  */
    /***********************SNAPSHOT OF REQUESTS STARTS here*********************/
    /* Evaluate if user request is present */
    userRequestState_b = ((pncRamPtr_ps->UserRequestCnt_u8) > C_ZERO);
    /* If any of the inhibition is enabled, then user request has to be ignored depending on inhibition type and PNC state */

    #if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)

    /* Ignore user request if,
     * 1. wake up inhibition is enabled in ECU group classification
     * 2. wakeup inhibition counter translated to this PNC is > C_ZERO and
     * 3. PNC is in No communication or prepare sleep state
     (PNC prepare sleep state is identical to channel's Silent communication state) */
    if((COMM_GET_PREVENT_WAKEUP((globalRamPtr_ps->ComM_EcuGroupClassification_u8))) &&
       ((pncRamPtr_ps->WakeUpInhibitionCtr_u16) > C_ZERO) &&
       (((pncRamPtr_ps->PncState_e) == PNC_NO_COMMUNICATION) || ((pncRamPtr_ps->PncState_e) == PNC_PREPARE_SLEEP)))
    {
        userRequestState_b = FALSE;
    }
    #endif  /*  (COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)  */

    #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)

    /* Ignore user request if
     * 1. limit to no com is enabled in ECU group classification
     * 2. limit to no com counter translated to this PNC is > C_ZERO
     * irrespective of PNC state, so as to ensure that PNC as well as channel goes to no com*/

    if ((COMM_GET_LIMIT_TO_NO_COM(globalRamPtr_ps->ComM_EcuGroupClassification_u8)) &&
            ((pncRamPtr_ps->LimitToNoComCtr_u16) != C_ZERO))
    {
        userRequestState_b = FALSE;
    }
    #endif  /*  (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)  */

    #if (COMM_PNC_GW_ENABLED != STD_OFF)

    


    /* Evaluate activeERAState_b, that is, either if user request is present or any active ERA == 1 */
    PncEventStruct_ps->activeERAState_b = ((pncRamPtr_ps->ActiveERACnt_u8 > C_ZERO) || (userRequestState_b));

    /* Evaluate if channel is requested actively, that is, either by User or ERACnt > C_ZERO */
    PncEventStruct_ps->activeRequestState_b = ((userRequestState_b)||((pncRamPtr_ps->ERACnt_u8) > C_ZERO));

    #else
    /* Evaluate activeERAState_b, that is, either if user request is present */
    PncEventStruct_ps->activeRequestState_b = ((pncRamPtr_ps->UserRequestCnt_u8) > C_ZERO);
    #endif  /*  (COMM_PNC_GW_ENABLED != STD_OFF)  */

    /* Evaluate passive request state of channel, ie., EIRACnt > C_ZERO */
    PncEventStruct_ps->passiveRequestState_b = ((pncRamPtr_ps->EIRACnt_u8) > C_ZERO);

    /* Evaluate if  wake up is indicated on the PN */
    PncEventStruct_ps->wakeupRequestState_b = pncRamPtr_ps->WakeUpStatus_b;

    pncStateOnEntry_e = pncRamPtr_ps->PncState_e;

    previousPncState_e = pncStateOnEntry_e;

    /*************************SNAPSHOT OF REQUESTS ENDS here***********************/

    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED)
    {

        /***********************PNC state machine handling starts here****************/
        do
        {
            switch (pncRamPtr_ps->PncState_e)
            {
                case PNC_NO_COMMUNICATION:
                {
                    ComM_PncNoCommunication_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps,
                                                                        previousPncState_e);
                }
                break;

                case PNC_REQUESTED:
                {
                    ComM_PncRequested_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps,
                                                            pncConfigPtr_pcs, previousPncState_e);
                }
                break;

                case PNC_READY_SLEEP:
                {
                    ComM_PncReadySleep_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps,
                                                               pncConfigPtr_pcs, previousPncState_e);
                }
                break;

                case PNC_PREPARE_SLEEP:
                {
                    ComM_PncPrepareSleep_StateHandling(PncIndex, PncEventStruct_ps, pncRamPtr_ps,
                                                                    pncConfigPtr_pcs, previousPncState_e);
                }
                break;

                default:
                    /* Intentionally Empty */
                break;
            }

            if(pncStateOnEntry_e != pncRamPtr_ps->PncState_e)
            {
                stateChangePossible_b = TRUE;
                /* Evaluate previous state of PNC */
                previousPncState_e = pncStateOnEntry_e;
                /* Update local copy of pnc state */
                pncStateOnEntry_e = pncRamPtr_ps->PncState_e;
            }
            else
            {
                stateChangePossible_b = FALSE;
            }

        } while (stateChangePossible_b != FALSE);

        /************************PNC state machine handling ends here****************/
    }

}


/* ComM_PncNoCommunication_StateHandling */
/**************************************************************************************
 * Function name    : ComM_PncNoCommunication_StateHandling
 * Syntax           : ComM_PncNoCommunication_StateHandling
 *                    (
 *                    VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                      P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) comM_PncEventStruct,
                      P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                      VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
 *                    )
 * Description      : Internal function for handling PNC_NO_COMMUNICATION state
 * Parameters       : PncIndex, comM_PncEventStruct, pncRamPtr_ps,previousPncState_e
 * Return value     : ComM_PncModeType
 **************************************************************************************/

/*MR12 RULE 8.13 VIOLATION: The PncEventStruct_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncNoCommunication_StateHandling(
                                                                     VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                                     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                                     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                                     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                                    )
{
    ComM_PncModeType   pncState_e;

    pncState_e = PNC_NO_COMMUNICATION;

    /* Entry to state PNC_NO_COMMUNICATION */
    if(previousPncState_e !=  PNC_NO_COMMUNICATION)
    {
        /* Notify BswM regarding state change */
        BswM_ComM_CurrentPNCMode(PncIndex,PNC_NO_COMMUNICATION);
    }
    /* Cyclic part of PNC_NO_COMMUNICATION state */
    else
    {
        /* Process the requests in PNC_NO_COMMUNICATION state as per below priority
         * 1. Active request ((User request) or (any ERA == 1 if Gateway is enabled))
         * 2. Passive request (External request from other ECU's through EIRA)
         * 3. WakeUp indication, if synchronous wake up is enabled */

        if(PncEventStruct_ps->activeRequestState_b != FALSE)
        {
            pncState_e = PNC_REQUESTED;
        }
        else if (PncEventStruct_ps->passiveRequestState_b != FALSE)
        {
            pncState_e = PNC_READY_SLEEP;
        }
        else if (PncEventStruct_ps->wakeupRequestState_b != FALSE)
        {
            pncState_e = PNC_PREPARE_SLEEP;
        }
        else
        {
            /* PNC is not requested so,remain in PNC_NO_COMMUNICATION state */
        }
    }

    /* Exit of PNC_NO_COMMUNICATION state */
    if(pncState_e != PNC_NO_COMMUNICATION)
    {
        SchM_Enter_ComM_PNCWakeUpNoNest();
        /* Update PN state to the RAM structure */
        pncRamPtr_ps->PncState_e = pncState_e;
        /* Clear synchronous wake up as, if at all present,it is already processed */
        pncRamPtr_ps->WakeUpStatus_b = FALSE;

        SchM_Exit_ComM_PNCWakeUpNoNest();
    }

}


/* ComM_PncRequested_StateHandling */
/**************************************************************************************
* Function name    : ComM_PncRequested_StateHandling
* Syntax           : ComM_PncRequested_StateHandling
*                    (
*                    VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) comM_PncEventStruct,
                     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e,
*                    )
* Description      : Internal function for handling PNC_REQUESTED  state
* Parameters       : PncIndex, comM_PncEventStruct, pncRamPtr_ps, previousPncState_e, pncConfigPtr_pcs
* Return value     : void
**************************************************************************************/
/*MR12 RULE 8.13 VIOLATION: The PncEventStruct_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncRequested_StateHandling
                                                    (
                                                         VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                         P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                         P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                         P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                                                         VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                    )
{
    ComM_PncModeType   pncState_e;
    boolean comSigVal_b;
    uint8 channelId_u8;
    uint8 loopCtr_u8;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    pncState_e = PNC_REQUESTED;
    comSigVal_b = FALSE;

    /* First entry to PNC_REQUESTED state */
    if(previousPncState_e != PNC_REQUESTED)
    {

        /* Notify BswM regarding state change */
        BswM_ComM_CurrentPNCMode(PncIndex,PNC_REQUESTED);

        /* Invoke PN to channel interface function, so as to REQUEST channel */
        ComM_LPncToChannelInterface(PncIndex,PNC_REQUESTED,previousPncState_e);

        /* Loop through all channels of this PN and depending on
        * 1. Gateway enabled or disabled,
        * 2. Gateway type and
        * 3. the kind of request(active or passive),
        * evaluate comSigVal_b for the channel  */

        /* For a passively coordinated channel,comSigVal_b is set only if there is a user request or
        * ERA of any actively coordinated channel is 1 */

        for (loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcs->NumChannels; loopCtr_u8++)
        {
            channelId_u8 = (pncConfigPtr_pcs->Channels[loopCtr_u8]);

            channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
            /* Check and proceed only if there is any Tx signal configured */
            if(channelConfigPtr_pcs->TxSigIdList_p != NULL_PTR)
            {
                if((channelConfigPtr_pcs->TxSigIdList_p[PncIndex])!= COMM_COMSIGNAL_INVALID_ID)
                {
                    #if (COMM_PNC_GW_ENABLED != STD_OFF)
                    if ((channelConfigPtr_pcs->PncGwType == COMM_GATEWAY_TYPE_ACTIVE)||
                            ((channelConfigPtr_pcs->PncGwType == COMM_GATEWAY_TYPE_PASSIVE)&&(PncEventStruct_ps->activeERAState_b)))
                    {
                        comSigVal_b = TRUE;
                        /* MR12 DIR 1.1 VIOLATION: Com_SendSignal's SignalDataPtr return value should be void as per Autosar guidelines. */
                        (void)Com_SendSignal(channelConfigPtr_pcs->TxSigIdList_p[PncIndex],&comSigVal_b);
                    }
                    else
                    {
                        comSigVal_b = FALSE;
                        /* MR12 DIR 1.1 VIOLATION: Com_SendSignal's SignalDataPtr return value should be void as per Autosar guidelines. */
                        (void)Com_SendSignal(channelConfigPtr_pcs->TxSigIdList_p[PncIndex],&comSigVal_b);
                    }

                    /* Update the value of activeERAState_b to activeERAStateOld_b */
                    pncRamPtr_ps->ActiveERAStateOld_b = PncEventStruct_ps->activeERAState_b;
                    #else
                    comSigVal_b = TRUE;
                    (void)Com_SendSignal(channelConfigPtr_pcs->TxSigIdList_p[PncIndex],&comSigVal_b);
                    #endif  /*  (COMM_PNC_GW_ENABLED != STD_OFF)  */
                }
            }
        }
    }
    /* Cyclic part of PNC_REQUESTED state */
    else
    {
        /* Continue in PNC_REQUESTED state till active request is present */
        if(PncEventStruct_ps->activeRequestState_b != FALSE)
        {
            /* Remain in PNC_REQUESTED state as the PNC is being requested actively */
            #if (COMM_PNC_GW_ENABLED != STD_OFF)

            /* Transmit comSigVal_b for Passive channel only if the previously indicated value changes */
            if(pncRamPtr_ps->ActiveERAStateOld_b != PncEventStruct_ps->activeERAState_b)
            {
                for (loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcs->NumChannels; loopCtr_u8++)
                {
                    channelId_u8 = pncConfigPtr_pcs->Channels[loopCtr_u8];
                    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[channelId_u8]);

                    if ((channelConfigPtr_pcs->PncGwType == COMM_GATEWAY_TYPE_PASSIVE))
                    {
                        /* Check and proceed only if there is any Tx signal configured */
                        if(channelConfigPtr_pcs->TxSigIdList_p != NULL_PTR)
                        {
                            if((channelConfigPtr_pcs->TxSigIdList_p[PncIndex])!= COMM_COMSIGNAL_INVALID_ID)
                            {
                                if(PncEventStruct_ps->activeERAState_b != FALSE)
                                {
                                    comSigVal_b = TRUE;
                                    /* MR12 DIR 1.1 VIOLATION: Com_SendSignal's SignalDataPtr return value should be void as per Autosar guidelines. */
                                    (void)Com_SendSignal(channelConfigPtr_pcs->TxSigIdList_p[PncIndex],&comSigVal_b);
                                }
                                else
                                {
                                    comSigVal_b = FALSE;
                                    /* MR12 DIR 1.1 VIOLATION: Com_SendSignal's SignalDataPtr return value should be void as per Autosar guidelines. */
                                    (void)Com_SendSignal(channelConfigPtr_pcs->TxSigIdList_p[PncIndex],&comSigVal_b);
                                }
                            }
                        }
                    }
                }
                /* As the value of activeERAState_b has changed, update it to activeERAStateOld_b */
                pncRamPtr_ps->ActiveERAStateOld_b = PncEventStruct_ps->activeERAState_b;
            }
            #endif  /*  (COMM_PNC_GW_ENABLED != STD_OFF )  */
        }
        else
        {
            /* As PNC is not being requested actively, go to PNC_READY_SLEEP state */
            pncState_e = PNC_READY_SLEEP;
        }
    }
    /* Exit of PNC_REQUESTED state */
    if(pncState_e != PNC_REQUESTED)
    {
        /* Update PN state to the RAM structure */
        pncRamPtr_ps->PncState_e = pncState_e;
    }
}


/* ComM_PncReadySleep_StateHandling */
/**************************************************************************************
* Function name    : ComM_PncReadySleep_StateHandling
* Syntax           : ComM_PncReadySleep_StateHandling
*                    (
*                    VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) comM_PncEventStruct,
                     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
*                    )
* Description      : Internal function for handling PNC_READY_SLEEP  state
* Parameters       : PncIndex, comM_PncEventStruct, pncRamPtr_ps, previousPncState_e, pncConfigPtr_pcs
* Return value     : void
**************************************************************************************/

/*MR12 RULE 8.13 VIOLATION: The PncEventStruct_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncReadySleep_StateHandling
                                                    (
                                                        VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                        P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                        P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                        P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                                                        VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                    )
{
    ComM_PncModeType   pncState_e;
    boolean comSigVal_b;
    uint8 channelId_u8;
    uint8 loopCtr_u8;

    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;

    pncState_e = PNC_READY_SLEEP;

    comSigVal_b = FALSE;

    /* First entry to PNC_READY_SLEEP state */
    if(previousPncState_e != PNC_READY_SLEEP)
    {
        /* Notify BswM regarding state change */
        BswM_ComM_CurrentPNCMode(PncIndex,PNC_READY_SLEEP);

        /* Invoke PN to channel interface function, so as to RELEASE channel */
        ComM_LPncToChannelInterface(PncIndex,PNC_READY_SLEEP,previousPncState_e);

        /* On transition from PNC_REQUESTED -> PNC_READY_SLEEP state,
         * call Com_SendSignal() with '0' for all Com signals assigned to this PN */
        if(previousPncState_e == PNC_REQUESTED)
        {
            comSigVal_b = FALSE;
            /* For all ComM channels of this PNC,call Com_SendSignal() with '0' as this PN is not requested actively anymore  */
            for(loopCtr_u8=0; loopCtr_u8 < pncConfigPtr_pcs->NumChannels; loopCtr_u8++)
            {
                channelId_u8 = pncConfigPtr_pcs->Channels[loopCtr_u8];
                channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[channelId_u8]);
                /* Check and proceed only if there is any Tx signal configured */
                if(channelConfigPtr_pcs->TxSigIdList_p != NULL_PTR)
                {
                    if((channelConfigPtr_pcs->TxSigIdList_p[PncIndex])!= COMM_COMSIGNAL_INVALID_ID)
                    {
                        /* MR12 DIR 1.1 VIOLATION: Com_SendSignal's SignalDataPtr return value should be void as per Autosar guidelines. */
                        (void)Com_SendSignal(channelConfigPtr_pcs->TxSigIdList_p[PncIndex],&comSigVal_b);
                    }
                }
            }
        }
    }
    /* Cyclic part of PNC_READY_SLEEP state */
    else
    {
        /* Process the requests as per below priority
         * 1.Active request ((User request) or (any ERA == 1 if Gateway is enabled))
         * 2.Passive request (External request from other ECU's through EIRA)*/
        if((PncEventStruct_ps->activeRequestState_b) != FALSE)
        {
            pncState_e = PNC_REQUESTED;
        }
        else if((PncEventStruct_ps->passiveRequestState_b) != FALSE)
        {
            /* PNC is being requested passively, hence remain in PNC_READY_SLEEP */
        }
        else
        {
            pncState_e = PNC_PREPARE_SLEEP;
        }
    }
    /* Exit of PNC_READY_SLEEP state  */
    if(pncState_e != PNC_READY_SLEEP)
    {
        /* Update PN state to the RAM structure */
        pncRamPtr_ps->PncState_e = pncState_e;
    }

}

/* ComM_PncPrepareSleep_StateHandling */
/**************************************************************************************
* Function name    : ComM_PncPrepareSleep_StateHandling
* Syntax           : ComM_PncPrepareSleep_StateHandling
*                    (
*                    VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                     P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) comM_PncEventStruct,
                     P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                     P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                     VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
*                    )
* Description      : Internal function for handling PNC_READY_SLEEP  state
* Parameters       : PncIndex, comM_PncEventStruct, pncRamPtr_ps, previousPncState_e, pncConfigPtr_pcs
* Return value     : void
**************************************************************************************/

/*MR12 RULE 8.13 VIOLATION: The PncEventStruct_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(void,COMM_CODE) ComM_PncPrepareSleep_StateHandling
                                                    (
                                                        VAR(NetworkHandleType,AUTOMATIC) PncIndex,
                                                        P2VAR(ComM_PncEventStructType, AUTOMATIC, COMM_APPL_DATA) PncEventStruct_ps,
                                                        P2VAR(ComM_PncRamStructType, AUTOMATIC, COMM_APPL_DATA) pncRamPtr_ps,
                                                        P2CONST(ComM_PncConfigStruct_t,AUTOMATIC,COMM_APPL_CONST) pncConfigPtr_pcs,
                                                        VAR(ComM_PncModeType,AUTOMATIC)  previousPncState_e
                                                    )
{
    ComM_PncModeType   pncState_e;

    pncState_e = PNC_PREPARE_SLEEP;

    /* First entry to PNC_PREPARE_SLEEP state */
    if(previousPncState_e != PNC_PREPARE_SLEEP)
    {
        /* Notify BswM regarding state change */
        BswM_ComM_CurrentPNCMode(PncIndex,PNC_PREPARE_SLEEP);

        /* Start Prepare sleep timer */
        

        pncRamPtr_ps->PrepareSleepTimer_u16 = pncConfigPtr_pcs->PrepareSleepTimer ;
    }
    /* Cyclic part of PNC_PREPARE_SLEEP state */
    else
    {
        /* If the prepare sleep timer has not already expired, decrement the timer*/
        if((pncRamPtr_ps->PrepareSleepTimer_u16)!= C_ZERO)
        {
            --pncRamPtr_ps->PrepareSleepTimer_u16;
        }
        /* Process the requests as per below priority
         * 1.Active request ((User request) or (any ERA == 1 if Gateway is enabled))
         * 2.Passive request (External request from other ECU's through EIRA)
         * 3.Prepare sleep timer has expired*/
        if(PncEventStruct_ps->activeRequestState_b != FALSE)
        {
            pncState_e = PNC_REQUESTED;
        }
        else if(PncEventStruct_ps->passiveRequestState_b != FALSE)
        {
            pncState_e = PNC_READY_SLEEP;
        }
        else if(pncRamPtr_ps->PrepareSleepTimer_u16 == C_ZERO)
        {
            pncState_e = PNC_NO_COMMUNICATION;
        }
        else
        {
            /* As there are no requests, remain in PNC_PREPARE_SLEEP state itself till timer expires */
        }
    }
    /* Exit of PNC_PREPARE_SLEEP state  */
    if(pncState_e != PNC_PREPARE_SLEEP)
    {
        /* Update PN state to the RAM structure */
        pncRamPtr_ps->PncState_e = pncState_e;
    }

}


#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

#endif  /*   (COMM_PNC_ENABLED != STD_OFF)  */

