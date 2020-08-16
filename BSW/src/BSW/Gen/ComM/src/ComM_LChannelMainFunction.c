

/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "ComM_Priv.h"

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

LOCAL_INLINE FUNC( void, COMM_CODE) ComM_ModeHandling
                                                    (
                                                         P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                         P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                         VAR(ComM_ModeType,AUTOMATIC) channelMode_e,
                                                         boolean entryToMode_b
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComNoPending_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                        ComM_StateType previousstate_e
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComPending_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                        P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                        ComM_StateType previousstate_e
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComReadySleep_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                        P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                        P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                        ComM_StateType previousstate_e,
                                                        uint8 numStateChanges_u8
                                                    );

LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComNetworkReq_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                        P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                        P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                        ComM_StateType previousstate_e
                                                    );

#if (COMM_NM_SUPPORT != STD_OFF)
LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_SilentCom_StateHandling
                                                    (
                                                            P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                            P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                            P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                            ComM_StateType previousstate_e
                                                    );

#endif

LOCAL_INLINE FUNC(ComM_ModeType,AUTOMATIC) ComM_getMode (VAR(ComM_StateType,AUTOMATIC) channelState_e);

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LNotifyChannelMode (VAR(NetworkHandleType,AUTOMATIC) ChannelIndex);

/* ComM_LChannelMainFunction */
/**************************************************************************************
 * Function name    : ComM_LChannelMainFunction
 * Syntax           : ComM_LChannelMainFunction
 *                    (
 *                    VAR(NetworkHandleType,AUTOMATIC) ChannelIndex
 *                    )
 * Description      : Function which contains different states and happening in various stages.
 * Parameters       : ChannelIndex
 * Return value     : void
 **************************************************************************************/
#define COMM_START_SEC_CODE
#include "ComM_Cfg_MemMap.h"
FUNC(void, COMM_CODE) ComM_LChannelMainFunction
                                                (
                                                    VAR(NetworkHandleType,AUTOMATIC) ChannelIndex
                                                )
{
    /* Local Variables Declaration */
    VAR(ComM_StateType,AUTOMATIC)  channelState_e;
    VAR(ComM_StateType,AUTOMATIC) previousstate_e;
    VAR(ComM_ModeType,AUTOMATIC) channelMode_e;
    VAR(ComM_ModeType,AUTOMATIC) busSmMode_e;
    VAR(ComM_RequestStructType,COMM_VAR) ComM_RequestStruct;

    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs;
    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps;
    uint8 numStateChanges_u8;
    boolean stateChangePossible_b;
    boolean entryToMode_b;
    boolean userRequestState_b;
    boolean diagnosticRequestState_b;
    #if(COMM_PNC_ENABLED != STD_OFF)
    boolean pncRequestState_b;
    #endif

    #if(COMM_INHIBITION_ENABLED)
    P2VAR(ComM_GlobalVarType, AUTOMATIC, COMM_APPL_DATA) globalRamPtr_ps;
    #endif

    /* Local Variables Initialization */
    stateChangePossible_b = FALSE;
    entryToMode_b = FALSE;
    numStateChanges_u8 = C_ZERO;
    #if(COMM_PNC_ENABLED != STD_OFF)
    pncRequestState_b = FALSE;
    #endif

    channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];
    channelConfigPtr_pcs = &(COMM_GET_CHANNEL_LIST[ChannelIndex]);

    requestStructPtr_ps = &ComM_RequestStruct;

    #if(COMM_INHIBITION_ENABLED)
    globalRamPtr_ps = &ComM_GlobalStruct;
    #endif  /*  (COMM_INHIBITION_ENABLED)  */
    /* DET Check for ComM initialization */
    #if (COMM_DEV_ERROR_DETECT != STD_OFF)
    if (ComM_GlobalStruct.ComM_InitStatus != COMM_INIT)
    {
        /* Report DET with ComM not initialized status */
        (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_MAINFNC_APIID,COMM_E_NOT_INITED);
        return;
    }
    #endif /*  #if (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    /* COMM_DEV_ERROR_DETECT */

    /***************************SNAP SHOT OF EVENTS STARTS********************************/

    /* Evaluate if User request is present or not */
    userRequestState_b = (((channelRamPtr_ps->UserRequestCtr_u8) > C_ZERO));
    /* If inhibition is active, then depending on inhibition type and channel state,
     * reevaluate userRequestState_b */
    #if(COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)
    /* Ignore user request, if
     * 1. wake up inhibition is enabled in ECU group classification,
     * 2. Wake up inhibition is requested for channel, and
     * 3. channel is in NO COMMUNICATION or SILENT_COMMUNICATION mode */
    if((COMM_GET_PREVENT_WAKEUP(globalRamPtr_ps->ComM_EcuGroupClassification_u8)))
    {
        if((COMM_GET_PREVENT_WAKEUP(channelRamPtr_ps->InhibitionReqStatus_u8)) &&
                ((channelRamPtr_ps->ChannelMode_u8 == COMM_NO_COMMUNICATION)|| (channelRamPtr_ps->ChannelMode_u8 == COMM_SILENT_COMMUNICATION)))
        {
            userRequestState_b = FALSE;
        }
    }
    #endif  /*  (COMM_PREVENT_WAKEUP_ENABLED != STD_OFF)  */
    #if(COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF)
    /* Ignore user request if
     * 1. limit to no com is enabled in ECU group classification
     * 2. limit to no com is requested for the channel
     * irrespective of the channel state,
     * so as to ensure that the channel goes to NO_COMMUNICATION mode */
    if(COMM_GET_LIMIT_TO_NO_COM((globalRamPtr_ps->ComM_EcuGroupClassification_u8)))
    {
        if(COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8)))
        {
            userRequestState_b = FALSE;
        }
    }
    #endif

    /* Get the status of diagnostics request(DCM) */
    diagnosticRequestState_b = channelRamPtr_ps->DiagnosticRequestState_b;

    /* Requests from Nm and EcuM are considered as Passive requests */
    /* Passive request status is evaluated here */
    requestStructPtr_ps->PassiveRequest_b = ((channelRamPtr_ps->PassiveRequestState_u8) > C_ZERO);

    /* Request from User and DCM are considered as Active requests  */
    requestStructPtr_ps->ActiveRequest_b = (userRequestState_b || diagnosticRequestState_b);

    #if(COMM_PNC_ENABLED != STD_OFF)

    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
    if(COMM_GET_FEATURE_PNC_ENABLED)
    {
        pncRequestState_b = (channelRamPtr_ps->PncRequestCtr_u8 > C_ZERO);

        /* If PN is enabled, then request from PNC should also be considered to evaluate
         * active request */
        requestStructPtr_ps->ActiveRequest_b = (requestStructPtr_ps->ActiveRequest_b) || (pncRequestState_b);
    }
    #endif  /*  (COMM_PNC_ENABLED != STD_OFF)  */


    /* Snap shot of all requests till the execution of this main function ends here.
     * Any change in the requests beyond this point will be processed in the next main function*/
    /*******************************SNAP SHOT OF EVENTS ENDS***********************************/

    /* Reading the status from channel RAM structure */

    channelState_e = channelRamPtr_ps->ChannelState_e ;

    channelMode_e = channelRamPtr_ps->ChannelMode_u8 ;

    busSmMode_e = channelRamPtr_ps->BusSmMode_u8;

    previousstate_e = channelState_e;

    /* Reading the status from channel configuration structure */

    /*********************************************STATE MACHINE STARTS HERE********************************************/
    /* Channel State machine handling considering only the snap shot of requests */
    /* All the possible state changes are done in this loop*/
    do
    {
        /* Call mode handling function, to
        * 1. Perform mode related events
        * 2. Poll and Retry : Check BusSm state and Request BusSm to go to respective mode */

        ComM_ModeHandling(channelRamPtr_ps,channelConfigPtr_pcs, channelMode_e, entryToMode_b);

        switch (channelState_e)
        {
            case COMM_NO_COM_NO_PENDING_REQUEST:
            {
                channelState_e = ComM_NoComNoPending_StateHandling(requestStructPtr_ps, previousstate_e);
            }
            break;
            case COMM_NO_COM_REQUEST_PENDING:
            {
                channelState_e = ComM_NoComPending_StateHandling(requestStructPtr_ps, channelRamPtr_ps, previousstate_e);
            }
            break;
            case COMM_FULL_COM_NETWORK_REQUESTED:
            {
                channelState_e = ComM_FullComNetworkReq_StateHandling(requestStructPtr_ps, channelRamPtr_ps,
                                                                                 channelConfigPtr_pcs, previousstate_e);
            }
            break;
            case COMM_FULL_COM_READY_SLEEP:
            {
                channelState_e = ComM_FullComReadySleep_StateHandling(requestStructPtr_ps, channelRamPtr_ps,
                                        channelConfigPtr_pcs, previousstate_e, numStateChanges_u8);
            }
            break;
            #if (COMM_NM_SUPPORT != STD_OFF)
            case COMM_SILENT_COM:
            {
                channelState_e = ComM_SilentCom_StateHandling(requestStructPtr_ps, channelRamPtr_ps, channelConfigPtr_pcs, previousstate_e);
            }
            break;
            #endif  /*  (COMM_NM_SUPPORT != STD_OFF)  */
            default:
                /* Intentionally Empty */
            break;
        }

        /* Check if state change is possible */
        if(channelRamPtr_ps->ChannelState_e != channelState_e)
        {
            SchM_Enter_ComM_ChannelNoNest();
            /* update the channel state to global structure*/
            previousstate_e = channelRamPtr_ps->ChannelState_e;
            channelRamPtr_ps->ChannelState_e = channelState_e;

            stateChangePossible_b = TRUE;
            numStateChanges_u8++;

            /* Translate state to mode */
            channelMode_e = ComM_getMode (channelState_e);

            /*Check if this state change leads to mode change*/
            if(channelMode_e != channelRamPtr_ps->ChannelMode_u8)
            {
                /* As state change leads to mode change, set entryToMode_b flag and update channel mode */
                entryToMode_b = TRUE;
                channelRamPtr_ps->ChannelMode_u8 = channelMode_e;
            }
            else
            {
                /* State change doesnt lead to mode change. Hence clear the entryToMode flag */
                entryToMode_b = FALSE;
            }
            SchM_Exit_ComM_ChannelNoNest();
        }
        else
        {
            entryToMode_b = FALSE;
            stateChangePossible_b = FALSE;
        }

    } while (stateChangePossible_b != FALSE);

    /*********************************************STATE MACHINE ENDS HERE*********************************************/

    /* If there is a change in BusSm mode,
     * 1. Notify the change in the mode to BSWM and DCM
     * 2. Reevaluate channel state counters for all users of the channel
     * 3. Evaluate if there is a change in leastBusSmMode for any user and
     * if there is a change, notify it to RTE
     */

    /* busSmMode_e contains the mode of BusSm on entry to state machine and
     * channelRamPtr_ps->BusSmMode_u8 contains latest BusSm mode on exit of state machine */

    if(busSmMode_e != channelRamPtr_ps->BusSmMode_u8)
    {

        /* Notify the change to BswM,DCM (per channel) */
        ComM_LNotifyChannelMode(ChannelIndex);

        /* Reevaluate counters for all users of channel and notify the change in least com mode to RTE*/
        ComM_LUpdateChannelModes(ChannelIndex,busSmMode_e,channelRamPtr_ps->BusSmMode_u8);

    }

}

/* ComM_NoComNoPending_StateHandling */
/**************************************************************************************
 * Function name    : ComM_NoComNoPending_StateHandling
 * Syntax           : ComM_NoComNoPending_StateHandling
 *                    (
 *                    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                      ComM_StateType previousstate_e
 *                    )
 * Description      : Internal function for handling COMM_NO_COM_NO_PENDING_REQUEST state
 * Parameters       : requestStructPtr_ps,previousstate_e
 * Return value     : ComM_StateType
 **************************************************************************************/
/*MR12 RULE 8.13 VIOLATION: The requestStructPtr_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComNoPending_StateHandling
                                                    (
                                                        P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                        ComM_StateType previousstate_e
                                                    )
{
    VAR(ComM_StateType,AUTOMATIC) channelState_e;

    channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;

    if (previousstate_e != COMM_NO_COM_NO_PENDING_REQUEST )
    {
        /* HALT STATE : entry to the state is not evaluated here */
    }

    /* Cyclic part of state COMM_NO_COM_NO_PENDING_REQUEST */
    /*For NO_com_No_Pending state Prioritiy of requests is
    *1. Active Request or Passive Request*/
    /* Evaluate if any request (Active or Passive) is present*/
    else
    {
        if ((requestStructPtr_ps->ActiveRequest_b != FALSE) || (requestStructPtr_ps->PassiveRequest_b != FALSE))
        {
            /* Update the channel state to the global structure*/
            channelState_e = COMM_NO_COM_REQUEST_PENDING;
        }
        else
        {
            /* State change is not possible, as there is no request.
             * Channel continues to be in COMM_NO_COM_NO_PENDING_REQUEST state */
        }
    }
    /* Exit of state COMM_NO_COM_NO_PENDING_REQUEST*/
    /*There is no dependent flags which has to be cleared as this is default state. Hence there is nothing to be taken care in this state */
    return channelState_e;

}


/* ComM_NoComPending_StateHandling */
/**************************************************************************************
 * Function name    : ComM_NoComPending_StateHandling
 * Syntax           : ComM_NoComPending_StateHandling
 *                    (
 *                    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                      P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
                      ComM_StateType previousstate_e
 *                    )
 * Description      : Internal function for handling COMM_NO_COM_PENDING_REQUEST state
 * Parameters       : requestStructPtr_ps, channelRamPtr_ps, previousstate_e
 * Return value     : ComM_StateType
 **************************************************************************************/

/*MR12 RULE 8.13 VIOLATION: The requestStructPtr_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_NoComPending_StateHandling
                                                        (
                                                            P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                            P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                            ComM_StateType previousstate_e
                                                        )
{

    VAR(ComM_StateType,AUTOMATIC) channelState_e;

    channelState_e = COMM_NO_COM_REQUEST_PENDING;

    /* Entry to state COMM_NO_COM_REQUEST_PENDING */
    if (previousstate_e != COMM_NO_COM_REQUEST_PENDING )
    {
        /*Evaluate Communication allowed flag and decide if state change is possible */
        if (channelRamPtr_ps->CommunicationAllowed_b != FALSE)
        {
            /* Communication Allowed is set, so proceed to COMM_FULL_COM_NETWORK_REQUESTED */
            /* As transition from COMM_NO_COM_REQUEST_PENDING to COMM_FULL_COM_NETWORK_REQUESTED*/
            channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
        }
    }
    /* Cyclic part of state COMM_NO_COM_REQUEST_PENDING */
    else
    {
        /*Check if request for Full_Communication (active or passive request) still exists */
        if ((requestStructPtr_ps->ActiveRequest_b || requestStructPtr_ps->PassiveRequest_b))
        {
            if ((channelRamPtr_ps->CommunicationAllowed_b) != FALSE)
            {
                /* Request for Full_Com is still present and CommunicationAllowed is also set,
                 * so proceed to COMM_FULL_COM_NETWORK_REQUESTED state*/
                channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
            }
            else
            {
                /* Wait for communication allowed to be set to True */
            }
        }
        else
        {
            channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
        }
    }

    /* Exit of state COMM_NO_COM_REQUEST_PENDING*/

    /* As passiveRequest is processed, clear the flag */
    if(channelState_e != COMM_NO_COM_REQUEST_PENDING)
    {
        /*As Passive requests are already processed, clear the flags */
        channelRamPtr_ps->PassiveRequestState_u8 = C_ZERO;
    }
    return channelState_e;

}

/* ComM_FullComNetworkReq_StateHandling */
/**************************************************************************************
 * Function name    : ComM_FullComNetworkReq_StateHandling
 * Syntax           : ComM_FullComNetworkReq_StateHandling
 *                    (
 *                      P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                        P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                        P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                        ComM_StateType previousstate_e
 *                    )
 * Description      : Internal function for handling COMM_FULL_COM_NETWORK_REQUESTED state
 * Parameters       : requestStructPtr_ps, channelRamPtr_ps, channelConfigPtr_pcs, previousstate_e
 * Return value     : ComM_StateType
 **************************************************************************************/

/*MR12 RULE 8.13 VIOLATION: The requestStructPtr_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComNetworkReq_StateHandling
                                                        (
                                                            P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                            P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                            P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                            ComM_StateType previousstate_e
                                                        )
{

    VAR(ComM_StateType,AUTOMATIC) channelState_e;

    channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;

    /* Entry to state COMM_FULL_COM_NETWORK_REQUESTED */
    if (previousstate_e != COMM_FULL_COM_NETWORK_REQUESTED )
    {
        /* Depending on NmVariant perform the entry actions */
        switch (channelConfigPtr_pcs->ComMNmVariant_e)
        {
            /* ComMNmVariant : FULL || PASSIVE -> Depending on request type (Active or Passive) and ComMNmVariant
            (FULL or PASSIVE) either Network request has to be called or state change to ready sleep has to be done */

            #if(COMM_NM_SUPPORT != STD_OFF)
			#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
            /* ComMNmVariant : FULL, if active request exists, then NetworkRequest has to be called
             * otherwise, transition to ready sleep has to be made */
            case (FULL):
            {
                if(requestStructPtr_ps->ActiveRequest_b)
                {
                    /* Active request is present, hence request network */
                    (void)Nm_NetworkRequest(channelConfigPtr_pcs->ComMChannelId_u8);
                    #if(COMM_PNC_ENABLED != STD_OFF)

                    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
                    if(COMM_GET_FEATURE_PNC_ENABLED)
                    {
                        /* Nm frame containing pn info will be transmitted before the nm message cycle time elapses.ComM_LPncToChannelInterface() will set
                         * channelRamPtr_ps ->NmNetworkRequestStatus_b if ComMPncNmRequest is set to TRUE*/
                        

                        channelRamPtr_ps ->NmNetworkRequestStatus_b = FALSE;
                    }
                    #endif  /*  (COMM_PNC_ENABLED != STD_OFF)  */
                }
                else
                {
                    /* As there is no active request,proceed directly to Ready sleep as there is no active request present */
                    channelState_e = COMM_FULL_COM_READY_SLEEP;
                }
            }
            break;
			#elif(COMM_NM_VARIANT == COMM_NM_VARIANT_PASSIVE)

            /* For ComMNmVariant : PASSIVE, there cannot be active request, hence change to Ready sleep directly */
            case (PASSIVE):
            {
                /* As the Nm variant is passive, proceed directly to Ready sleep state */
                channelState_e = COMM_FULL_COM_READY_SLEEP;
            }
            break;
			#endif/*#if(COMM_NM_VARIANT)*/
            #endif  /*  #if (COMM_NM_SUPPORT != STD_OFF)  */

            /* ComMNmVariant : LIGHT || NONE -> minimum full com duration timer has to be started */
            case LIGHT:
            case NONE:
            {
                /*Start MinFullComDuration timer*/
                (channelRamPtr_ps->MinFullComTimeoutCtr_u16) = (channelConfigPtr_pcs->TMinFullComModeDuration_u16) ;
            }
            break;

            default :
                /* Intentionally Empty */
            break;

        }
    }
    /* Cyclic part of state COMM_FULL_COM_NETWORK_REQUESTED */
    else
    {
        switch (channelConfigPtr_pcs->ComMNmVariant_e)
        {
            /* If ComM Nm variant PASSIVE, control never comes to cyclic part of COMM_FULL_COM_NETWORK_REQUESTED
             * state.State immediately changes to Ready sleep state from entry of COMM_FULL_COM_NETWORK_REQUESTED
             * state
             * */
            #if ((COMM_NM_SUPPORT != STD_OFF) && (COMM_NM_VARIANT == COMM_NM_VARIANT_FULL))
            case (FULL):
            {
                /* For nmVariant FULL , priority of requests is
                 *             1. Bus sleep indication
                 *             2. Active request
                 *             proceeed to  ready sleep
                 * Process these requests according to above priority */
                /* If bus sleep indication has occurred, proceed to COMM_NO_COM_NO_PENDING_REQUEST state */
                if((channelRamPtr_ps->NmBusSleepIndicationStatus_b) != FALSE)
                {
                    channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(requestStructPtr_ps->ActiveRequest_b != FALSE)
                {
                    #if(COMM_PNC_ENABLED != STD_OFF)

                    /* MR12 RULE 14.3 VIOLATION: The value of COMM_GET_FEATURE_PNC_ENABLED depends on the configuration therefore it will not always be true. */
                    if(COMM_GET_FEATURE_PNC_ENABLED)
                    {
                        if((channelRamPtr_ps->NmNetworkRequestStatus_b) != FALSE)
                        {
                            (void)Nm_NetworkRequest(channelConfigPtr_pcs->ComMChannelId_u8);
                            /* Lock is not required here as the variable is set in pnc main function and comm mainfunction
                             * clears it and it is scheduled after pnc */
                            channelRamPtr_ps ->NmNetworkRequestStatus_b = FALSE;
                        }
                    }
                    #endif /* #if(COMM_PNC_ENABLED != STD_OFF)  */
                    /* Remain in COMM_FULL_COM_NETWORK_REQUESTED state as long as active request is present */
                }
                else
                {
                    /* As there is no active request, proceed to Ready sleep state */
                    channelState_e = COMM_FULL_COM_READY_SLEEP;
                }
            }
            break;
            #endif  /*  (COMM_NM_SUPPORT != STD_OFF) && (COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)  */

            case LIGHT:
            case NONE :
            {
                /*This check is to ensure we do not decrement the timer when it is zero */
                /*Priority is given to active request when timer expires and there is an active request*/
                if((channelRamPtr_ps->MinFullComTimeoutCtr_u16) != C_ZERO)
                {
                    /* Decrement Minimum full com duration timer*/
                    -- (channelRamPtr_ps->MinFullComTimeoutCtr_u16) ;
                }

                if((channelRamPtr_ps->MinFullComTimeoutCtr_u16) == C_ZERO)
                {
                    if(requestStructPtr_ps->ActiveRequest_b != FALSE)
                    {
                        /* Even though timer expired,as there is active request,COMM_FULL_COM_NETWORK_REQUESTED
                         * state has to be retained  */
                    }
                    else
                    {
                        /* Timer expired and there is no active request, so proceed to Ready sleep state */
                        channelState_e = COMM_FULL_COM_READY_SLEEP;
                    }
                }
            }
            break;

            default :
                /* Intentionally Empty */
            break;
        }
    }

    /* Exit of state COMM_FULL_COM_NETWORK_REQUESTED*/
    if(channelState_e == COMM_NO_COM_NO_PENDING_REQUEST)
    {
        /* Clear the bus sleep indication flag as it is already processed.
		   If NmBusSleepIndicationStatus_b is set and processed, then channelState_e will be COMM_NO_COM_NO_PENDING_REQUEST.
		   Hence the flag is cleared only in this condition */
        #if(COMM_NM_SUPPORT != STD_OFF)
        channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE ;
        #endif  /*  (COMM_NM_SUPPORT != STD_OFF)  */
    }

    return channelState_e;
}


/* ComM_FullComReadySleep_StateHandling */
/**************************************************************************************
 * Function name    : ComM_FullComReadySleep_StateHandling
 * Syntax           : ComM_FullComReadySleep_StateHandling
 *                    (
 *                      P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                        P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                        P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                        ComM_StateType previousstate_e,
                        uint8 numStateChanges_u8
 *                    )
 * Description      : Internal function for handling COMM_FULL_COM_READY_SLEEP state
 * Parameters       : requestStructPtr_ps, channelRamPtr_ps,,previousState_e,numStateChanges_u8, previousstate_e
 * Return value     : ComM_StateType
 **************************************************************************************/

/*MR12 RULE 8.13 VIOLATION: The requestStructPtr_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_FullComReadySleep_StateHandling
                                                (
                                                    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                    P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                    ComM_StateType previousstate_e,
                                                    uint8 numStateChanges_u8
                                                )

{
    VAR(ComM_StateType,AUTOMATIC) channelState_e;

    channelState_e = COMM_FULL_COM_READY_SLEEP;


    /* Entry to state COMM_FULL_COM_READY_SLEEP */
    if (previousstate_e != COMM_FULL_COM_READY_SLEEP )
    {
        /* Entry to state COMM_FULL_COM_READY_SLEEP */
        if(previousstate_e == COMM_FULL_COM_NETWORK_REQUESTED)
        {
            switch(channelConfigPtr_pcs->ComMNmVariant_e)
            {
                #if(COMM_NM_SUPPORT != STD_OFF)
                /* Entry to ready sleep state from Network Requested and from Silent Communication has to be differentiated
                 * On Entry to Ready sleep from Network requested, Nm api's needs to be called if Nm is present
                 * but on entry to Ready sleep from Silent Com, No Nm api's needs to be called, as silent com ->
                 * Ready sleep is only triggered by Nm (Nm_NetworkMode) */
				#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
                case FULL :
                {
                    /* Check if Network request was already called, If so, network released has to be called
                    Otherwise, PassiveStartUp has to be called */

                    /* Whether NetworkRequested was called or not is determined by using numStateChanges_u8
                     * If NetworkRequested was called, state change from Network requested to ready sleep doesn't
                     * happen immediately. If it was not called, it happens immediately and hence the numStateChanges_u8
                     * will be >= 2*/
                    /* There is two state transitions from no com to full com in the same main function when it is passive request for full_com*/
                    if(numStateChanges_u8 >=2)
                    {
                        /* As the entry is because of Passive request, call Nm_PassiveStartUp() */
                        (void)Nm_PassiveStartUp(channelConfigPtr_pcs->ComMChannelId_u8);
                    }
                    else
                    {
                        /* As NetworkRequest was already called, call Nm_NetworkRelease() */
                        (void)Nm_NetworkRelease(channelConfigPtr_pcs->ComMChannelId_u8);
                    }
                }
                break;
				#endif/*  #if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)  */
                #if(COMM_NM_VARIANT == COMM_NM_VARIANT_PASSIVE)
                case PASSIVE :
                {
                    /* As Nm variant is passive, always Nm_PassiveStartUp() has to be called */
                    (void)Nm_PassiveStartUp(channelConfigPtr_pcs->ComMChannelId_u8);
                }
                break;
				#endif /*  #if(COMM_NM_VARIANT == "PASSIVE")  */
                #endif  /*  (COMM_NM_SUPPORT != STD_OFF)  */

                /* For other Nm variants (Light and None), silent Com state doesn't exist and
                 * hence entry need not be differentiated*/
                case LIGHT:
                {
                    /* Start NmLightTimeOut timer */
                    channelRamPtr_ps->LightTimeoutCtr_u32 = channelConfigPtr_pcs->NmLightTimeout_u32;
                    /* Check if NmLightTimeOut timer expired i.e. check if value configured for NmLightTimeout timer is zero,
                     * then proceed directly to no_com_no_pending state*/
                    if(channelRamPtr_ps->LightTimeoutCtr_u32 == C_ZERO)
                    {
                        /* As NmLightTimeOut timer has expired,change to COMM_NO_COM_NO_PENDING_REQUEST state */
                        channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                    }
                }
                break;

                case NONE:
                {
                    if(channelConfigPtr_pcs->BusType_e == COMM_BUS_TYPE_INTERNAL)
                    {
                        /* For bus type internal, immediate transition to COMM_NO_COM_NO_PENDING_REQUEST state */
                        channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                    }
                    else
                    {
                        /*For Bus types other than internal,if NM variant is NONE channel will remain in Ready sleep state.
                         * It goes to No Com state only on power off */
                    }
                }
                break;

                default:
                    /* Intentionally Empty */
                break;
            }
        }
    }

    /* Cyclic part of state COMM_FULL_COM_READY_SLEEP */
    else
    {
        switch (channelConfigPtr_pcs->ComMNmVariant_e)
        {
            #if(COMM_NM_SUPPORT != STD_OFF)
            /* For nmVariant FULL, priority of requests is
             *             1. Bus sleep indication
             *             2. Active request
             *             3. Prepare bus sleep indication
             * Process these requests according to above priority */
			#if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
            case FULL :
            {
                if (channelRamPtr_ps->NmBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if(requestStructPtr_ps->ActiveRequest_b)
                {
                    /* For nmVariant Passive, active request will not affect the state,
                     * channel continues in Ready sleep state * */
                    channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
                }
                else if (channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_SILENT_COM;
                }
                else
                {
                    /* Do nothing */
                }
            }
            break;
			#endif /* #if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL) */

            /* For nmVariant PASSIVE, priority of requests is
             *             1. Bus sleep indication
             *             2. Prepare bus sleep indication
             * Process these requests according to above priority */
			#if(COMM_NM_VARIANT == COMM_NM_VARIANT_PASSIVE)
            case PASSIVE :
            {
                if (channelRamPtr_ps->NmBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                }
                else if (channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b != FALSE)
                {
                    channelState_e = COMM_SILENT_COM;
                }
                else
                {
                    /* Do nothing */
                }
            }
            break;
			#endif /*  #if(COMM_NM_VARIANT == "PASSIVE")  */
            #endif  /*  (COMM_NM_SUPPORT != STD_OFF)  */

            /* For nmVariant Light, priority of requests is
             *             1. Active request
             *             2. Expire of LightTimeOutTimer
             * These requests are processed according to above priority*/
            case LIGHT :
            {
                if(requestStructPtr_ps->ActiveRequest_b != FALSE)
                {
                    channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
                }
                else
                {
                    if((channelRamPtr_ps->LightTimeoutCtr_u32) != C_ZERO )
                    {
                        --channelRamPtr_ps->LightTimeoutCtr_u32;
                        if((channelRamPtr_ps->LightTimeoutCtr_u32) == C_ZERO )
                        {
                            channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
                        }
                        else
                        {
                            /* Wait till Light time out time expires */
                        }
                    }
                }
            }
            break;

            case NONE :
            {
                /* If Nm variant is None, nothing needs to be done in "continuous" state of COMM_FULL_COM_READY_SLEEP state,
                 * as NmVariant NONE for channel other than internal, leaves the channel is FULL_COM for ever */
            }
            break;

            default:
                /* Intentionally Empty */
            break;

        }
    }

    /* Exit of state COMM_FULL_COM_READY_SLEEP*/
    if(channelState_e != COMM_FULL_COM_READY_SLEEP)
    {
        SchM_Enter_ComM_ChannelNoNest();
        /* Since the flag NmPrepareBusSleepIndicationStatus can be set in COMM_FULL_COM_READY_SLEEP, clear as the state is exited  */
        /*If this flag is not cleared then if the next state is n/w requested, later channel  should switch to silent_com*/
        #if(COMM_NM_SUPPORT != STD_OFF)
        channelRamPtr_ps->NmPrepareBusSleepIndicationStatus_b = FALSE ;

        if(channelState_e == COMM_NO_COM_NO_PENDING_REQUEST)
        {
            /* Clear the bus sleep indication flag as it is already processed.
		       If NmBusSleepIndicationStatus_b is set and processed, then channelState_e will be COMM_NO_COM_NO_PENDING_REQUEST.
		       Hence the flag is cleared only in this condition  */
            channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE ;
        }

        #endif  /*  (COMM_NM_SUPPORT != STD_OFF)  */
        SchM_Exit_ComM_ChannelNoNest();
    }

    return channelState_e;

}

/* ComM_SilentCom_StateHandling */
/**************************************************************************************
 * Function name    : ComM_SilentCom_StateHandling
 * Syntax           : ComM_SilentCom_StateHandling
 *                    (
 *                    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                      P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps
                      ComM_StateType previousstate_e previousstate_e
 *                    )
 * Description      : Internal function for handling COMM_SILENT_COM state
 * Parameters       : requestStructPtr_ps, channelRamPtr_ps,  previousstate_e
 * Return value     : ComM_StateType
 **************************************************************************************/

/*MR12 RULE 8.13 VIOLATION: The requestStructPtr_ps pointer variables are modified in main function. Hence it cant be P2CONST type*/
LOCAL_INLINE FUNC(ComM_StateType,COMM_CODE) ComM_SilentCom_StateHandling
                                                (
                                                    P2VAR(ComM_RequestStructType, AUTOMATIC, COMM_APPL_DATA) requestStructPtr_ps,
                                                    P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                    P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                    ComM_StateType previousstate_e
                                                )
{
    VAR(ComM_StateType,AUTOMATIC) channelState_e;


    channelState_e = COMM_SILENT_COM;

    /* Entry to state COMM_FULL_COM_NETWORK_REQUESTED */
    if (previousstate_e != COMM_SILENT_COM )
    {
        /* HALT STATE : entry to the state is not evaluated here */
    }
    /* Cyclic part of COMM_SILENT_COM mode*/
    else
    {
        /* BusSleepIndication is given priority over Full_Com request, Full Com request if any will be processed in the
         * next main function call */
        /* Priority for comMNmVariant "FULL"
         *             1. BusSleepIndication
         *             2. Active request
         *             3. Network Mode indication */

        /* Priority for comMNmVariant "PASSIVE"
         *             1. BusSleepIndication
         *             2. Network Mode indication */
        if ((channelRamPtr_ps->NmBusSleepIndicationStatus_b) != FALSE)
        {
            channelState_e = COMM_NO_COM_NO_PENDING_REQUEST;
        }
        /* Active request in Silent com state is handled only in case of comMNmVariant "FULL".
         * For comMNmVariant "PASSIVE", active request is ignored, as network cannot be requested actively
         * for a passive channel*/
        else if ((channelConfigPtr_pcs->ComMNmVariant_e == FULL) && (requestStructPtr_ps->ActiveRequest_b != FALSE))
        {
            channelState_e = COMM_FULL_COM_NETWORK_REQUESTED;
        }
        else if ((channelRamPtr_ps->NmNetworkModeStatus_b) != FALSE)
        {
            channelState_e = COMM_FULL_COM_READY_SLEEP;
        }
        else
        {
            /* Continue in Silent Communication state as there is no new request */
        }
    }

    /* Exit of state COMM_SILENT_COM */
    if(channelState_e != COMM_SILENT_COM)
    {
        SchM_Enter_ComM_ChannelNoNest();
        channelRamPtr_ps->NmNetworkModeStatus_b = FALSE;
        channelRamPtr_ps->NmBusSleepIndicationStatus_b = FALSE;
        SchM_Exit_ComM_ChannelNoNest();
    }

    return channelState_e;
}


/* ComM_LBusSm */
/**************************************************************************************
 * Function name    : ComM_ModeHandling
 * Syntax           : ComM_ModeHandling
 *                    (
*                        P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                         P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                         VAR(ComM_ModeType,AUTOMATIC) channelMode_e ,
                         boolean entryToMode_b
*                     )
 * Description      : Internal function to request <Bus>Sm
 * Parameters       :P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA)
                     channelRamPtr_ps, boolean entryToMode_b,
                     P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                     VAR(ComM_ModeType,AUTOMATIC) channelMode_e
 * Return value     : void
 **************************************************************************************/

LOCAL_INLINE FUNC( void, COMM_CODE) ComM_ModeHandling
                                            (
                                                 P2VAR(ComM_ChannelVarType, AUTOMATIC,COMM_APPL_DATA) channelRamPtr_ps,
                                                 P2CONST(ComM_ChannelType,AUTOMATIC,COMM_APPL_CONST) channelConfigPtr_pcs,
                                                 VAR(ComM_ModeType,AUTOMATIC) channelMode_e ,
                                                 boolean entryToMode_b
                                            )
{
    boolean requestBusSm_b;
    VAR(ComM_ModeType,AUTOMATIC) busSmMode_e;
    P2CONST(ComM_BusSmApiType,AUTOMATIC,COMM_APPL_CONST) busSm_funcPtr;

    busSmMode_e = channelRamPtr_ps->BusSmMode_u8;
    busSm_funcPtr = &ComM_BusSmApi[channelConfigPtr_pcs->BusType_e];
    requestBusSm_b = FALSE;

    if (entryToMode_b != FALSE)
    {
        requestBusSm_b = TRUE;

        /* If Nm variant is FULL, Call Nm_NetworkRelease */

        if(channelMode_e == COMM_NO_COMMUNICATION)
        {
            #if (COMM_NM_SUPPORT != STD_OFF)
            #if(COMM_NM_VARIANT == COMM_NM_VARIANT_FULL)
            if (channelConfigPtr_pcs->ComMNmVariant_e == FULL)
            {
                (void)Nm_NetworkRelease(channelConfigPtr_pcs->ComMChannelId_u8);
            }
            #endif/* #if(COMM_NM_VARIANT ==COMM_NM_VARIANT_FULL)*/
            #endif/*#if (COMM_NM_SUPPORT != STD_OFF)*/
        }
    }
    /* Cyclic part of mode COMM_NO_COMMUNICATION */
    else
    {
        /* POLL and RETRY mechanism : BusSm is requested for same mode as that of ComM, if it is not already in
         * the same mode. Continuous polling of BusSm mode is done */

        /* POLLING : Poll for the latest mode of BusSm */
        (void)(*busSm_funcPtr->BusSm_GetCurrentComMode)(channelConfigPtr_pcs->ComMChannelId_u8, &busSmMode_e);

        /* Update the latest busSm mode to the global variable  */
        channelRamPtr_ps->BusSmMode_u8 = busSmMode_e ;

        /* RETRY : request BusSm for the same mode as that of ComM  */
        if(busSmMode_e != channelMode_e)
        {
            requestBusSm_b = TRUE;
        }

        if(channelMode_e == COMM_NO_COMMUNICATION)
        {
            /* If Reset after forcing to No Com is enabled, then once the busSm enters NO_COMMUNICATION mode
             * reset has to be triggered by calling BswM */
            #if((COMM_RESET_AFTER_NO_COM != STD_OFF) && (COMM_LIMIT_TO_NOCOM_ENABLED != STD_OFF))
            if((COMM_GET_LIMIT_TO_NO_COM((channelRamPtr_ps->InhibitionReqStatus_u8)) != FALSE) &&
               (channelRamPtr_ps->BusSmMode_u8 == channelMode_e))
            {
                BswM_ComM_InitiateReset();
            }
            #endif
        }
    }

    /* Request BusSm */
    if(requestBusSm_b)
    {
        Std_ReturnType RetValue;

        /* RequestBusSm for mode change depending on Bus type*/
        RetValue = (*busSm_funcPtr->BusSm_RequestComMode)(channelConfigPtr_pcs->ComMChannelId_u8,channelMode_e);

        #if (COMM_DEV_ERROR_DETECT != STD_OFF)
        if(RetValue == E_NOT_OK)
        {
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_MAINFNC_APIID,COMM_E_ERROR_IN_PROV_SERVICE);
        }
        #else
        (void)(RetValue);
        #endif  /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
    }

}

/* ComM_NotifyChannelMode */
/**************************************************************************************
 * Function name    : ComM_LNotifyChannelMode
 * Syntax           : ComM_LNotifyChannelMode
 *                    (
 *                     VAR(NetworkHandleType,AUTOMATIC) ChannelIndex
 *                    )
 * Description      : Internal function to notify change in the channel mode to DCM and BSWM
 * Parameters       : ChannelIndex : Channel Id
 * Return value     : void
 **************************************************************************************/

LOCAL_INLINE FUNC(void, COMM_CODE) ComM_LNotifyChannelMode(VAR(NetworkHandleType,AUTOMATIC) ChannelIndex)
{

    /* Local variable declaration */
    P2VAR(ComM_ChannelVarType, AUTOMATIC, COMM_APPL_DATA) channelRamPtr_ps;
    VAR(ComM_ModeType,AUTOMATIC) channelMode_e;

    channelRamPtr_ps = &ComM_ChannelStruct[ChannelIndex];

    channelMode_e = channelRamPtr_ps->ChannelMode_u8;

    /* Notify BswM and DCM regarding Mode change  */
    BswM_ComM_CurrentMode(ChannelIndex,channelMode_e);

    #if (COMM_DCM_SUPPORT != STD_OFF)

    /* Depending on the channel mode, call respective DCM function to notify the mode change  */

    switch(channelMode_e)
    {
        case COMM_NO_COMMUNICATION : Dcm_ComM_NoComModeEntered(ChannelIndex);
            break;
        case COMM_FULL_COMMUNICATION : Dcm_ComM_FullComModeEntered(ChannelIndex);
            break;
        case COMM_SILENT_COMMUNICATION : Dcm_ComM_SilentComModeEntered(ChannelIndex);
            break;
        default:
            /* Intentionally Empty */
            break;
    }

    #endif   /*  (COMM_DEV_ERROR_DETECT != STD_OFF)  */
}


/* ComM_getMode */
/**************************************************************************************
 * Function name    : ComM_getMode
 * Syntax           : ComM_getMode
 *                    (
 *                    VAR(ComM_StateType,AUTOMATIC) ChannelState_e
 *                    )
 * Description      : Function to give mode corresponding to a state
 * Parameters       : ChannelState_e
 * Return value     : ComM_ModeType
 **************************************************************************************/

LOCAL_INLINE FUNC(ComM_ModeType,AUTOMATIC) ComM_getMode (VAR(ComM_StateType,AUTOMATIC) channelState_e)
{
    VAR(ComM_ModeType,AUTOMATIC) channelMode_e;
    channelMode_e = COMM_NO_COMMUNICATION;

    switch(channelState_e)
    {
        case COMM_NO_COM_NO_PENDING_REQUEST :
        case COMM_NO_COM_REQUEST_PENDING :
        {
            channelMode_e = COMM_NO_COMMUNICATION;
        }
        break;

        case COMM_FULL_COM_NETWORK_REQUESTED :
        case COMM_FULL_COM_READY_SLEEP :
        {
            channelMode_e = COMM_FULL_COMMUNICATION;
        }
        break;

        case COMM_SILENT_COM :
        {
            channelMode_e = COMM_SILENT_COMMUNICATION;
        }
        break;

        default:
        {
            #if (COMM_DEV_ERROR_DETECT != STD_OFF)
            (void)Det_ReportError(COMM_MODULE_ID,COMM_INSTANCE_ID,COMM_MAINFNC_APIID,COMM_E_WRONG_PARAMETERS);
            #endif
        }
        break;
    }

    return channelMode_e;
}

#define COMM_STOP_SEC_CODE
#include "ComM_Cfg_MemMap.h"

