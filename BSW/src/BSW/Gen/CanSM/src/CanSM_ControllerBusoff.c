
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"
/**
***************************************************************************************************
** Function Name        : CanSM_ControllerBusOff
**
** Service ID           : 0x04
**
** Description          : This callback function notifies the CanSM about a bus-off event on a certain CAN controller,
**                        which needs to be considered with the specified bus-off recovery handling for the impacted
**                        CAN network.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant (only for different CanControllers)
**
** Input Parameters     : ControllerId-CAN controller, which detected a bus-off event
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"

FUNC(void, CANSM_CODE) CanSM_ControllerBusOff(VAR(uint8, AUTOMATIC) ControllerId )
{
    /*To track the ComM mode status*/
    VAR(ComM_ModeType, AUTOMATIC) CanSM_ComM_ModeType_uo;
    /*Variable to track the status of BSWM*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
    /*To keep a track of current BOR state */
    VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORState_en;
    /*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
    /*Variable to hold the network index for the given controller*/
    VAR(uint8, AUTOMATIC) network_indx_u8;
    /*To track the Pending Bus Off status for the network to which the CAN Controller belongs*/
    VAR(boolean, AUTOMATIC) BusoffISRPend_Temp_b;
    /*To keep a track of current BOR mode Enable/Disable */
    VAR(uint8, AUTOMATIC) CanSM_BORMode_u8;
    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;
    /* Report DET : Development Error for Invalid  Controller ID */
    CANSM_REPORT_ERROR((ControllerId >= CANSM_NUM_CAN_CONTROLLERS),
                                                 (uint8)CANSM_CONTROLLERBUSOFF_SID,
                                                 (uint8)CANSM_E_PARAM_CONTROLLER)

    /* Notify DET if CanSM module is not initialized */
    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_CONTROLLERBUSOFF_SID),
                           ((uint8)CANSM_E_UNINIT)
                           )


   /*If the given controller id is valid, get the associated network*/
   network_indx_u8 = (uint8)CanSM_ConfigSet_pcst->CanSM_NetworktoCtrlConf_pcu8[ControllerId];

    /*Hold the address of the configured network*/
    CanSM_NetworkConf_ps = &CanSM_Network_pcst[network_indx_u8];
   /*Make a local copy of CanSM_stBusOffISRPend_a[network_indx_u8]*/
   BusoffISRPend_Temp_b = CanSM_BusOffISRPend_ab[network_indx_u8];

   /*Make a local copy of BOR Mode[network_indx_u8]*/
   CanSM_BORMode_u8 = CanSM_BORMode_au8[network_indx_u8];
   /* Get the Current BOR State only after the Mutex is accquired */
   CanSM_CurrBORState_en = CanSM_currBOR_State_en[network_indx_u8];

   if(CanSM_CurrNw_Mode_en[network_indx_u8] == CANSM_BSM_S_SILENTCOM)
       {
           /*Update the global array for the network as TRUE to indicate that the network has bus off */
           if((CanSM_BusOff_Indicated_ab[network_indx_u8] == TRUE) || (BusoffISRPend_Temp_b == TRUE))
               {
                   CanSM_BusOff_Indicated_ab[network_indx_u8] = FALSE;
                   CanSM_BusOffISRPend_ab[network_indx_u8] = FALSE;
                   CanSM_BOR_SilentCom_ab[network_indx_u8] = TRUE;

               }
           /*Change the current BOR state to CANSM_S_RESTART_CC*/
           CanSM_currBOR_State_en[network_indx_u8] = CANSM_S_RESTART_CC;

       /*Report the DEM event status  to DEM*/
       Dem_ReportErrorStatus(CanSM_Network_pcst[network_indx_u8].BusOffEventId_uo,DEM_EVENT_STATUS_PREFAILED);

       /* FC_VariationPoint_START */
       /*Update the intended network variable with latest DEM event status to be used to provide status to DEM module on request*/
       #if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
       CanSM_NetworkDem_pst[network_indx_u8].CanSM_DEM_Eventstatus_u8 = DEM_EVENT_STATUS_PREFAILED;
       #endif
       /* FC_VariationPoint_END */
       CanSM_StartTimer(network_indx_u8);
       }
   else
       {
   /* Set Tx-Pdu Mode to OFFLINE */
   /*This will not be required to be done again in RESTART_CC or RESTART_CC_WAIT*/
   /* Loop for All the Controllers in the Network*/
   for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network_indx_u8].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
       {
            CanSM_ControllerId_u8 = CanSM_Network_pcst[network_indx_u8].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
            /* Set PDU Mode to OFFLINE as per SWS */
            /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_SET_TX_OFFLINE));

        }
   /*Update the global array for the network as TRUE to indicate that the network has bus off */
   CanSM_BusOff_Indicated_ab[network_indx_u8] = TRUE;

    /* Check if the BOR State Machine is updated to CANSM_RECOVERY_ENABLED*/
    if( CanSM_BORMode_u8 == (uint8)CANSM_RECOVERY_ENABLED)
        {
            /* Check if the mutex is available*/
            if(E_OK == CanSM_GetMutex(network_indx_u8))
                {

                /* Check if current BOR state is BUS_OFF_CHECK OR NO_BUSOFF */
                    if((CanSM_CurrBORState_en == CANSM_S_BUS_OFF_CHECK) || (CanSM_CurrBORState_en == CANSM_S_NO_BUS_OFF))
                        {
                            /*Update the state of Network for BswM*/
                            CanSM_BswM_Mode_en = CANSM_BSWM_BUS_OFF;

                            /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                            BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                            /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_SILENTCOM i.e COMM_SILENT_COMMUNICATION*/
                            CanSM_BusSMMode_au8[network_indx_u8] = (ComM_ModeType)CANSM_BSM_S_SILENTCOM;
                            /*Check if multiple CAN controllers are mapped to the network*/
                            if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network_indx_u8].SizeofController_u8 > 1u)
                                {
                                CanSM_BOR_Controller_Stopped_state_en[network_indx_u8] = CANSM_BOR_CONTROLLER_STOPPED_REQUEST;
                                }
                            else
                                {
                                    /*Change the current BOR state to CANSM_S_RESTART_CC*/
                                    CanSM_currBOR_State_en[network_indx_u8] = CANSM_S_RESTART_CC;
                                    /*Start the Wait state Timer if only single controller is mapped to the CanSM network */
                                     CanSM_StartTimer(network_indx_u8);

                                }

                            /*update the local variable*/
                            CanSM_CurrBORState_en = CanSM_currBOR_State_en[network_indx_u8];
                            /*Notify ComM about CanSM state changes*/
                            CanSM_ComM_ModeType_uo = COMM_SILENT_COMMUNICATION;
                            ComM_BusSM_ModeIndication(CanSM_Network_pcst[network_indx_u8].ComM_channelId_uo,&CanSM_ComM_ModeType_uo);
                            /*Report the DEM event status  to DEM*/
                            Dem_ReportErrorStatus(CanSM_Network_pcst[network_indx_u8].BusOffEventId_uo,DEM_EVENT_STATUS_PREFAILED);

                            /* FC_VariationPoint_START */
                            /*Update the intended network variable with latest DEM event status to be used to provide status to DEM module on request*/
                            #if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
                            CanSM_NetworkDem_pst[network_indx_u8].CanSM_DEM_Eventstatus_u8 = DEM_EVENT_STATUS_PREFAILED;
                            #endif
                            /* FC_VariationPoint_END */
                        }

                    /*Release the mutex*/
                    CanSM_ReleaseMutex(network_indx_u8);
                 }

                /*If the mutex was busy and no pending bus off*/
            else if(BusoffISRPend_Temp_b == FALSE)
                {
                    /*update the pending bus off as TRUE*/
                    CanSM_BusOffISRPend_ab[network_indx_u8]= TRUE;
                    /* Check if current BOR state is BUS_OFF_CHECK OR NO_BUSOFF */
                        if((CanSM_CurrBORState_en == CANSM_S_BUS_OFF_CHECK) || (CanSM_CurrBORState_en == CANSM_S_NO_BUS_OFF))
                            {
                                /*Update the state of Network for BswM*/
                                CanSM_BswM_Mode_en = CANSM_BSWM_BUS_OFF;

                                /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                                BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                                /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_SILENTCOM i.e COMM_SILENT_COMMUNICATION*/
                                CanSM_BusSMMode_au8[network_indx_u8] = (ComM_ModeType)CANSM_BSM_S_SILENTCOM;
                                /*Check if multiple CAN controllers are mapped to the network*/
                                if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network_indx_u8].SizeofController_u8 > 1u)
                                    {
                                    CanSM_BOR_Controller_Stopped_state_en[network_indx_u8] = CANSM_BOR_CONTROLLER_STOPPED_REQUEST;
                                    }
                                else
                                    {
                                        /*Change the current BOR state to CANSM_S_RESTART_CC*/
                                        CanSM_currBOR_State_en[network_indx_u8] = CANSM_S_RESTART_CC;
                                        /*Start the Wait state Timer if only single controller is mapped to the CanSM network */
                                         CanSM_StartTimer(network_indx_u8);

                                    }

                                /*update the local variable*/
                                CanSM_CurrBORState_en = CanSM_currBOR_State_en[network_indx_u8];
                                /*Notify ComM about CanSM state changes*/
                                CanSM_ComM_ModeType_uo = COMM_SILENT_COMMUNICATION;
                                ComM_BusSM_ModeIndication(CanSM_Network_pcst[network_indx_u8].ComM_channelId_uo,&CanSM_ComM_ModeType_uo);
                                /*Report the DEM event status  to DEM*/
                                Dem_ReportErrorStatus(CanSM_Network_pcst[network_indx_u8].BusOffEventId_uo,DEM_EVENT_STATUS_PREFAILED);

                                /* FC_VariationPoint_START */
                                /*Update the intended network variable with latest DEM event status to be used to provide status to DEM module on request*/
                                #if(CANSM_DSM_REINIT_ENABLED != STD_OFF)
                                CanSM_NetworkDem_pst[network_indx_u8].CanSM_DEM_Eventstatus_u8 = DEM_EVENT_STATUS_PREFAILED;
                                #endif
                                /* FC_VariationPoint_END */
                            }

                }
            else
                {
                    /*do nothing*/
                }

        }
       }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_BusOffTransitions
**
** Description          : This functon is either called in the Main Function regularly(also if Mutex was BUSY)
**                        This function inititaes and Controls Bus Off transitions in Bus-Off recovery
**                        state Machine.
**
** Re-entrancy          : Reentrant (only for different networks)
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_BusOffTransitions(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*Variable to track the status of BSWM*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
    /*To keep a track of current BOR state */
    VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORState_en;
    /*To keep a track of Controller stopped state when bus off is notified and the network has multiple CAN controllers */
    VAR(CanSM_BOR_Controller_Stopped_stateType_ten, AUTOMATIC) CanSM_BOR_Controller_Stopped_states_en;
    /*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To track the ComM mode status*/
    VAR(ComM_ModeType, AUTOMATIC) CanSM_reqComM_Mode_uo;

    /*Hold the address of the configured network*/
    CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];
    /* Get the Current BOR State only after the Mutex is accquired */
    CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];
    /* Get the controller state during bus off  transition*/
    CanSM_BOR_Controller_Stopped_states_en =  CanSM_BOR_Controller_Stopped_state_en[network];

    /*Check if multiple CAN controllers are mapped to the network*/
    if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].SizeofController_u8 > 1u)
        {
            if(CanSM_BOR_Controller_Stopped_states_en == CANSM_BOR_CONTROLLER_STOPPED_REQUEST)
            {
                /*Stop all the other CAN controllers of the affected CanSM network which are not stopped*/
                CanSM_BOR_MultipleCtrlsStop(network);
                /* Get the controller state during bus off  transition*/
                CanSM_BOR_Controller_Stopped_states_en =  CanSM_BOR_Controller_Stopped_state_en[network];
                if(CanSM_BOR_Controller_Stopped_states_en == CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED)
                {

                        /*Change the current BOR state to CANSM_S_RESTART_CC*/
                        CanSM_currBOR_State_en[network] = CANSM_S_RESTART_CC;
                        CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];
                        /*Start the Wait state Timer for L1 */
                        CanSM_StartTimer(network);

                }
            }
        }

    /*Check if multiple CAN controllers are mapped to the network*/
    if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].SizeofController_u8 > 1u)
        {
            /*If T_REPEAT_MAX counter has not exceeded*/
            if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
                {
                    if(CanSM_BOR_Controller_Stopped_states_en == CANSM_BOR_CONTROLLER_STOPPED_WAIT)
                        {
                            /*Check if a controller indication was received that all the CAN controllers are stopped*/
                            if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                                {
                                    /*Set the Timer to Elapsed Mode */
                                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                                    /*Reset the controller mode indication flag for the network*/
                                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                                    /*Move to next substate of the CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED */
                                    CanSM_BOR_Controller_Stopped_state_en[network] = CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED;

                                    /*Reset the T_REPEAT_MAX counter*/
                                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                                    /*Change the current BOR state to CANSM_S_RESTART_CC*/
                                    CanSM_currBOR_State_en[network] = CANSM_S_RESTART_CC;

                                    CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];

                                    /*Start the Wait state Timer for L1 */
                                    CanSM_StartTimer(network);
                                }

                            /*Check if timeout has occurred and so proceed accordingly*/
                            else
                                {
                                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                                        {
                                            /*Set the Timer to Elapsed Mode */
                                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                                            /*Move to previous substate*/
                                            CanSM_BOR_Controller_Stopped_state_en[network]=CANSM_BOR_CONTROLLER_STOPPED_REQUEST;

                                            CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];
                                        }
                                }
                        }
                }
             else
                {
                    /*The present state of the network [during initialisation]*/
                    CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                    CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;
                    /*Reset T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                    /*Update the global array for the network as FALSE */
                    CanSM_BusOff_Indicated_ab[network] = FALSE;
                    /*When transceiver is configured, also check if PN is supported*/
                    if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                        {
                            #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
                            /*Pn checking includes that transceiver is also configured */
                            if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
                                {
                                    /*Initiate the substate machine for De-initilization with PN support*/
                                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                                }
                            else
                                {
                                    /*Initiate the substate machine for De-initilization without PN*/
                                    CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                }
                            #else
                            /*Initiate the substate machine for De-initilization without PN*/
                            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                            #endif
                        }
                    else
                        {
                            /*Initiate the substate machine for De-initilization without PN*/
                            CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                        }

                         /*No more sub-states in BOR*/
                        CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;

                        CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];

                        /*Update the state of Network for BswM*/
                        CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;

                        /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                        BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);
                        /*Report to DET that T_REPEAT_MAX counter has exceeded CanSM_ModeReq_Max_u8*/
                        CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,((uint8)CANSM_MAINFUNCTION_SID),(CANSM_E_MODE_REQUEST_TIMEOUT))
                }
        }

    /* Check whether current BOR state is CANSM_S_RESTART_CC */
    else if(CanSM_CurrBORState_en == CANSM_S_RESTART_CC)
        {
            /*Start all the CAN controllers*/
            CanSM_BOR_CtrlsStart(network);
        }
    else if(CanSM_CurrBORState_en == CANSM_S_RESTART_CC_WAIT)
        {
            /*Check if a controller indication was received that all the CAN controllers are stopped*/
            if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {
                    /*Reset the controller mode indication flag to FALSE*/
                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    /*Reset the T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    if(CanSM_BusOff_Cntr_au8[network] < CanSM_Network_pcst[network].BorCntL1L2_u8)
                    {
                        /*Change the current BOR state to CANSM_S_BUS_OFF_RECOVERY_L1*/
                        CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_RECOVERY_L1;
                    }
                    else
                    {
                        /*Change the current BOR state to CANSM_S_BUS_OFF_RECOVERY_L2*/
                        CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_RECOVERY_L2;
                    }

                }
            else
                {
                if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                   {
                       /*Move to previous substate ie CANSM_S_RESTART_CC*/
                       CanSM_currBOR_State_en[network]=CANSM_S_RESTART_CC;
                   }
                }

            }
           /*Checking for the guarding condition G_TX_ON*/
    else if((CanSM_CurrBORState_en == CANSM_S_BUS_OFF_RECOVERY_L1) ||(CanSM_CurrBORState_en == CANSM_S_BUS_OFF_RECOVERY_L2))
            {
               #if (CANSM_CALIBRATION != STD_ON)
                /* MR12 RULE 13.5 VIOLATION: Warning is "Not Critical": The comparison is required*/
                if((( CanSM_BusOff_Cntr_au8[network] < CanSM_Network_pcst[network].BorCntL1L2_u8)&&(CanSM_TimerConfig_ast[network].cntTick_u16 >=(CanSM_Network_pcst[network].BorTimeL1_u16 + CanSM_GetBusOffDelay_Value_u8[network]) ))||
                    ((CanSM_BusOff_Cntr_au8[network] >= CanSM_Network_pcst[network].BorCntL1L2_u8)&&(CanSM_TimerConfig_ast[network].cntTick_u16 >= (CanSM_Network_pcst[network].BorTimeL2_u16 + CanSM_GetBusOffDelay_Value_u8[network]))))

               #else
               /* MR12 RULE 13.5 VIOLATION: Warning is "Not Critical": The comparison is required*/
                if((( CanSM_BusOff_Cntr_au8[network] < CanSM_Network_pcst[network].BorCntL1L2_u8)&&(CanSM_TimerConfig_ast[network].cntTick_u16 >= (CanSM_Network_pcst[network].pBorTimeL1_pfct() + CanSM_GetBusOffDelay_Value_u8[network])))||
                                            ((CanSM_BusOff_Cntr_au8[network] >= CanSM_Network_pcst[network].BorCntL1L2_u8)&&(CanSM_TimerConfig_ast[network].cntTick_u16 >= (CanSM_Network_pcst[network].pBorTimeL2_pfct() + CanSM_GetBusOffDelay_Value_u8[network]))))
               #endif
                {
                   /* Increment the Bus Off counter only when the current BOR state is CANSM_S_BUS_OFF_RECOVERY_L1 and
                       the bus off counter is less than 255 */
                    if((CanSM_CurrBORState_en == CANSM_S_BUS_OFF_RECOVERY_L1) &&  (CanSM_BusOff_Cntr_au8[network] < 255u))
                        {
                            /* Increment Bus Off counter */
                            CanSM_BusOff_Cntr_au8[network]++;
                        }
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /* Set Pdu Mode to ONLINE */
                    /* Loop for All the Controllers in the Network*/
                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                        {
                             CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                            #if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
                             if(CanSM_Passive_b == TRUE)
                             {
                             /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                             (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_SET_TX_OFFLINE_ACTIVE));
                             }
                             else
                             {
                                 /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                                 (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_SET_ONLINE));
                             }
                            #else
                             /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                             (void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_SET_ONLINE));
                            #endif

                         }

                    /*Notify the BswM*/
                    CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

                    BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

                    /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_FULLCOM i.e COMM_FULL_COMMUNICATION*/
                    CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

                    /*Update the BOR state*/
                    CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

                    /*Notify to ComM about CanSM state Transition*/
                    CanSM_reqComM_Mode_uo = COMM_FULL_COMMUNICATION;
                    ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_reqComM_Mode_uo);
                    /*Start the timer to check for message confirmtion either by Tx time Ensured or confirmation polling*/
                    CanSM_StartTimer(network);
              }
            }

    /*For busoffs occurring during the recovery, just restart the controller*/
    else
        {
            /* Loop for All the Controllers in the network and Set them to STOPPED Mode*/
            for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                {
                    /*Store the CAN controller ID belonging to the network*/
                    CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                    /*Check that the CAN controller is not already STARTED*/
                    if(CanSM_ControllerState_en[CanSM_ControllerId_u8] != CANSM_ControllerState_STARTED)
                    {
                       /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                        (void)CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_STARTED);
                    }
                }
        }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
/**
***************************************************************************************************
** Function Name        : CanSM_BOR_MultipleCtrlsStop
**
** Description          : This api will stop all the CAN controllers of the network during bus off.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant (only for different network)
**
** Input Parameters     : network-The passed CanSM network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_BOR_MultipleCtrlsStop(VAR(NetworkHandleType, AUTOMATIC) network)
{
        /*Temporary pointer to hold the adress of configured network*/
        P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
        /*Variable to track the status of BSWM*/
        VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
        /*To hold the controller Id*/
        VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
        /*Used in FOR loop to access CAN controllers of the corresponding network*/
        VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
        /*Variable to hold the return status of CanIf_SetControllerMode()*/
        VAR(boolean, AUTOMATIC) CanSM_Ctrl_return_val_b[CANSM_NUM_CAN_CONTROLLERS];
        /*Hold the counter number to know that all the controllers are stopped*/
        VAR(uint8, AUTOMATIC) CanSM_Controller_Counter_u8 = 0;

        /*Hold the address of the configured network*/
        CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

        /* Loop for All the Controllers in the network and Set them to STOPPED Mode*/
        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
        {
            /*Store the CAN controller ID belonging to the network*/
            CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
            /*Check that the CAN controller is not already STOPPED*/
            if(CanSM_ControllerState_en[CanSM_ControllerId_u8] != CANSM_ControllerState_STOPPED)
            {
               /*If E_NOT_OK is returned for any of the controller, increment the T_REPEAT_MAX counter and break*/
                if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_STOPPED))
                    {
                         /*Call to CanIf_SetControllerMode() returns E_NOT_OK  */
                        CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = FALSE;

                        /*If atleast one unsuccessful attempt to stop the controller occured for the corresponding network then increment the unsuccessful attempt*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
                        break;
                    }
                else
                    {
                        /*CanIf_SetControllerMode() return value */
                        CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = TRUE;
                    }
            }
            else
            {
                 /*CanIf_SetControllerMode() return value */
                CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = TRUE;
            }
        }

        /* Loop for All the Controllers in the network to check if the mode indications are received*/
        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
        {
             /*If for all controllers the api CanIf_SetControllerMode() has returned E_OK */
            if(CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] == TRUE)
            {
                CanSM_Controller_Counter_u8++;
            }
        }

        if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
            {
                /*Check if in the meantime, controller mode indication was received and update the substate if so*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {
                        /*Reset the controller mode indication flag to FALSE*/
                        CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                        /*Move to next substate of the CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED */
                        CanSM_BOR_Controller_Stopped_state_en[network] = CANSM_BOR_CONTROLLER_STOPPED_REQUEST_COMPLETED;

                    }
                else
                    {
                        /*Move to next substate of the CANSM_BOR_CONTROLLER_STOPPED_WAIT */
                    CanSM_BOR_Controller_Stopped_state_en[network] = CANSM_BOR_CONTROLLER_STOPPED_WAIT;
                        /*Start the Wait state Timer */
                        CanSM_StartTimer(network);


                    }
            }
        else
            {
                /*Check if the T_REPEAT_MAX has exceeded*/
                if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
                    {
                        /*The present state of the network [during initialisation]*/
                        CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                        /*Request for NO_COMM*/
                        CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;
                        /*Reset T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                        /*Update the global array for the network as TRUE to indicate that the network has bus off */
                        CanSM_BusOff_Indicated_ab[network] = FALSE;
                        /*When transceiver is configured, also check if PN is supported*/
                        if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                            {
                                #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
                                /*Pn checking includes that transceiver is also configured */
                                if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
                                    {
                                        /*Initiate the substate machine for De-initilization with PN support*/
                                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                                    }
                                else
                                    {
                                        /*Initiate the substate machine for De-initilization without PN*/
                                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                    }
                                #else
                                /*Initiate the substate machine for De-initilization without PN*/
                                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                #endif
                            }
                        else
                            {
                                /*Initiate the substate machine for De-initilization without PN*/
                                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                            }

                             /*No more sub-states in BOR*/
                            CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;
                            /*Update the state of Network for BswM*/
                            CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;
                            /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                            BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);
                            /*Report to DET that T_REPEAT_MAX counter has exceeded CanSM_ModeRepeatReq_Max_u8*/
                            CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,((uint8)CANSM_MAINFUNCTION_SID),(CANSM_E_MODE_REQUEST_TIMEOUT))

                    }

            }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_BOR_CtrlsStart
**
** Service ID           :
**
** Description          : This api will start all the CAN controllers of the network during bus off recovery.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant (only for different network)
**
** Input Parameters     : network-The passed CanSM network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_BOR_CtrlsStart(VAR(NetworkHandleType, AUTOMATIC) network)
{
        /*Temporary pointer to hold the adress of configured network*/
        P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
        /*Variable to track the status of BSWM*/
        VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
        /*To hold the controller Id*/
        VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
        /*Used in FOR loop to access CAN controllers of the corresponding network*/
        VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
        /*Variable to hold the return status of CanIf_SetControllerMode()*/
        VAR(boolean, AUTOMATIC) CanSM_Ctrl_return_val_b[CANSM_NUM_CAN_CONTROLLERS];
        /*Hold the counter number to know that all the controllers are stopped*/
        VAR(uint8, AUTOMATIC) CanSM_Controller_Counter_u8 = 0;


        /*Hold the address of the configured network*/
        CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

        /* Loop for All the Controllers in the network and Set them to STOPPED Mode*/
        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
        {
            /*Store the CAN controller ID belonging to the network*/
            CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
            /*Check that the CAN controller is not already STOPPED*/
            if(CanSM_ControllerState_en[CanSM_ControllerId_u8] != CANSM_ControllerState_STARTED)
            {
               /*If E_NOT_OK is returned for any of the controller, increment the T_REPEAT_MAX counter and break*/
                if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_STARTED))
                    {
                         /*Call to CanIf_SetControllerMode() returns E_NOT_OK  */
                        CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = FALSE;

                        /*If atleast one unsuccessful attempt to stop the controller occured for the corresponding network then increment the unsuccessful attempt*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
                        break;
                    }
                else
                    {
                        /*CanIf_SetControllerMode() return value */
                        CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = TRUE;
                    }
            }
            else
            {
                 /*CanIf_SetControllerMode() return value */
                CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = TRUE;
            }
        }

        /* Loop for All the Controllers in the network to check if the mode indications are received*/
        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
        {
             /*If for all controllers the api CanIf_SetControllerMode() has returned E_OK */
            if(CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] == TRUE)
            {
                CanSM_Controller_Counter_u8++;
            }
        }

        if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
            {
                /*Check if in the meantime, controller mode indication was received and update the substate if so*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {
                        /*Reset the controller mode indication flag to FALSE*/
                        CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                        if(CanSM_BusOff_Cntr_au8[network] < CanSM_Network_pcst[network].BorCntL1L2_u8)
                        {
                            /*Change the current BOR state to CANSM_S_BUS_OFF_RECOVERY_L1*/
                            CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_RECOVERY_L1;
                        }
                        else
                        {
                            /*Change the current BOR state to CANSM_S_BUS_OFF_RECOVERY_L2*/
                            CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_RECOVERY_L2;
                        }

                    }
                else
                    {
                        /*Move to next substate of the CANSM_S_RESTART_CC_WAIT */
                        CanSM_currBOR_State_en[network] = CANSM_S_RESTART_CC_WAIT;

                    }
            }
        else
            {
                /*Check if the T_REPEAT_MAX has exceeded*/
                if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
                    {
                        /*The present state of the network [during initialisation]*/
                        CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                        /*Request for NO_COMM*/
                        CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;
                        /*Reset T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                        /*When transceiver is configured, also check if PN is supported*/
                        if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                            {
                                #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
                                /*Pn checking includes that transceiver is also configured */
                                if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
                                    {
                                        /*Initiate the substate machine for De-initilization with PN support*/
                                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                                    }
                                else
                                    {
                                        /*Initiate the substate machine for De-initilization without PN*/
                                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                    }
                                #else
                                /*Initiate the substate machine for De-initilization without PN*/
                                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                #endif
                            }
                        else
                            {
                                /*Initiate the substate machine for De-initilization without PN*/
                                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                            }

                             /*No more sub-states in BOR*/
                            CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;
                            /*Update the state of Network for BswM*/
                            CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;
                            /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                            BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);
                            /*Report to DET that T_REPEAT_MAX counter has exceeded CanSM_ModeRepeatReq_Max_u8*/
                            CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,((uint8)CANSM_MAINFUNCTION_SID),(uint8)(CANSM_E_MODE_REQUEST_TIMEOUT))

                    }

            }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/* FC_VariationPoint_START */
/**
***************************************************************************************************
** Function Name        : CanSm_Rb_DisableBusOffRecovery
**
** Description          : This api shall be called by Upper layer and it will update a global array .The api does the
**                        following operations in Main_Function()
**                         1. The api shall stop the busoff recovery
**                         2. As busoff is not recovered within the intended time, stop the CAN controllers: This is
**                         to make sure that after the API is called there is no further communication
**                         (Tx or Rx by this ECU on the affected network).
**                         3. Put all the TX and Rx pdu to OFFLINE mode for the intended CAN controller mapped to the
**                         CanSM network
**
** Re-entrancy          : Reentrant for different networks
**
** Input Parameters     : network - index of the Network Configuration structure
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : Void

**********************************************************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_Rb_DisableBusOffRecovery(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /* Get the CanSM Network Index value corresponding to the ComM channel Id received */
    network = CanSM_GetHandle(network);
    /* Update the array for the network to TRUE for disabling the BOR operation for the intended network*/
    CanSM_Rb_DisableBusOffRecovery_ab[network] = TRUE;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/* FC_VariationPoint_END */

/**
***************************************************************************************************
** Function Name        : CanSM_GetMutex
**
** Service ID           : None
**
** Description          : This function attempts to to aqquire the Mutex for function execution in pre-emptive environment.
**                        If Mutex is available, this Function returns E_OK else it returns E_NOT_OK.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant for different network
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : E_OK(Mutex FREE)/E_NOT_OK(Mutex BUSY)

***************************************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetMutex(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*To keep a track of Return value*/
    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;

    /*Initialization of Local Variables*/
    CanSM_FuncVal_uo = E_NOT_OK;

    /* Critical section Enter*/
    SchM_Enter_CanSM_GetMutexNoNest();

    /* Check if Mutex is available */
    if(CanSM_MutexMode_au8[network] == CANSM_MUTEX_FREE)
    {
        /* Set Mutex to BUSY */
        CanSM_MutexMode_au8[network] = CANSM_MUTEX_BUSY;

        CanSM_FuncVal_uo = E_OK;
    }
    /* Check if Mutex is BUSY */
    else
    {
        /* FC_VariationPoint_START */
        CanSM_FuncVal_uo = E_NOT_OK;
        /* FC_VariationPoint_END */
    }

    /* Critical section Exit*/
    SchM_Exit_CanSM_GetMutexNoNest();

    return(CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_GetBusoff_Substate
**
** Service ID           : 0x0Fu
**
** Description          : This API provides the current BusOff-state of a given CanController
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant(only for other different Can Controllers)
**
** Input Parameters     :  ControllerId - Id of the controller
**                         BORStatePtr - Data pointer to store the BusoffStatus
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : E_OK/E_NOT_OK

***************************************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
/* HIS METRIC RETURN VIOLATION IN CanSM_GetBusoff_Substate: Return is  more than one because DET is enabled. */
FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetBusoff_Substate(uint8 ControllerId, CanSM_BusOffRecoveryStateType_ten* BORStatePtr)
{
    /*Variable to hold the network index for the given controller*/
    VAR(uint8, AUTOMATIC) network_indx_u8;

    /*To keep a track of Return value*/
    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;

    /*Initialization of Local Variables*/
    CanSM_FuncVal_uo = E_NOT_OK;

    /* Report DET : Development Error Handling for CANSM is Uninitialized */
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                                (uint8)CANSM_GETBUSOFFSUBSTATE_SID,
                                (uint8)CANSM_E_UNINIT)

    /* Report DET : Development Error for Invalid  Controller ID */
    /* Controllers are assumed to have 0 based ID*/
    CANSM_REPORT_ERROR_NOK((ControllerId >= CANSM_NUM_CAN_CONTROLLERS),
                       (uint8)CANSM_GETBUSOFFSUBSTATE_SID,
                       (uint8)CANSM_E_PARAM_CONTROLLER)

    /* Report DET : Development Error for Invalid data pointer */
    CANSM_REPORT_ERROR_NOK((BORStatePtr == NULL_PTR),
                       (uint8)CANSM_GETBUSOFFSUBSTATE_SID,
                       (uint8)CANSM_E_PARAM_POINTER)


    /*If the given controller id is valid, get the associated network*/
    network_indx_u8 = (uint8)CanSM_ConfigSet_pcst->CanSM_NetworktoCtrlConf_pcu8[ControllerId];

    /* Get the Current BOR State  only after the Mutex is acquired */
    *BORStatePtr = CanSM_currBOR_State_en[network_indx_u8];
    CanSM_FuncVal_uo = E_OK;

    return(CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
 ***************************************************************************************************
 * \moduledescription
 * This functon is an internal non-Autosar function to check if a TxConfirmation is received for any of the controllers
 * in the network.This function calls CanIf_GetTxConfirmationState(ControllerId) to check if a TxConfirmation was
 * received for the Controller.
 *
 * \param   uint8
 * \arg     Indx_Network - index of the Network Configuration structure
 * \return  Std_ReturnType
 * \retval  -
 *
 *
 ***************************************************************************************************
 */
#if (CANSM_BOR_TX_CONFIRMATION_POLLING != STD_OFF)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckTxRxNotification(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*To keep a track of Return value*/
    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;

    /*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;
    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;

    /*Hold the address of the configured network*/
    CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

    /*Initialise the local variable as E_NOT_OK*/
    CanSM_FuncVal_uo = E_NOT_OK;

    /* Loop for All the Controllers in the network*/
    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
    {
        /*Store the CAN controller ID belonging to the network*/
        CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
        /*Check if a TxConfirmation was received for the Controller*/
        if(CANIF_TX_RX_NOTIFICATION == CanIf_GetTxConfirmationState(CanSM_ControllerId_u8))
        {
            /*Update the return value as E_OK*/
            CanSM_FuncVal_uo = E_OK;

            break;
        }
    }
    return(CanSM_FuncVal_uo);

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

/**
***************************************************************************************************
** Function Name        : CanSM_BOR_CtrlsStart_SilentCom
**
** Service ID           :
**
** Description          : This api will start all the CAN controllers of the network during bus off recovery.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant (only for different network)
**
** Input Parameters     : network-The passed CanSM network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_BOR_CtrlsStart_SilentCom(VAR(NetworkHandleType, AUTOMATIC) network)
{
        /*Temporary pointer to hold the adress of configured network*/
        P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
        /*Variable to track the status of BSWM*/
        VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
        /*To hold the controller Id*/
        VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
        /*Used in FOR loop to access CAN controllers of the corresponding network*/
        VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
        /*Variable to hold the return status of CanIf_SetControllerMode()*/
        VAR(boolean, AUTOMATIC) CanSM_Ctrl_return_val_b[CANSM_NUM_CAN_CONTROLLERS];
        /*Hold the counter number to know that all the controllers are stopped*/
        VAR(uint8, AUTOMATIC) CanSM_Controller_Counter_u8 = 0;
        VAR(ComM_ModeType, AUTOMATIC) CanSM_ComM_Mode_uo;
        /*To keep a track of current BOR state */
        VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORState_en;

        /*Hold the address of the configured network*/
        CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];
        /* Get the Current BOR State only after the Mutex is accquired */
        CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];
        /*If T_REPEAT_MAX counter has not exceeded*/
        if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
        {
            switch(CanSM_CurrBORState_en)
            {
                case CANSM_S_RESTART_CC_WAIT:
                {
                    /*Check if a controller indication was received that all the CAN controllers are stopped*/
                    if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {
                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                        CanSM_BOR_SilentCom_ab[network] = FALSE;

                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        if(CanSM_ReqComM_Mode_en[network] == COMM_NO_COMMUNICATION)
                        {
                            /*The present state of the network [during initialisation]*/
                           CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

                           /* Change the BOR State */
                           CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;

                           /*When transceiver is configured, also check if PN is supported*/
                           if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                               {
                                   #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
                                   /*Pn checking includes that transceiver is also configured */
                                   if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
                                       {
                                           /*Initiate the substate machine for De-initilization with PN support*/
                                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                                       }
                                   else
                                       {
                                           /*Initiate the substate machine for De-initilization without PN*/
                                           CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                       }
                                   #else
                                   /*Initiate the substate machine for De-initilization without PN*/
                                   CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                   #endif
                               }
                           else
                               {
                                   /*Initiate the substate machine for De-initilization without PN*/
                                   CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                               }

                        }
                        else
                        {
                            /*Update the state of Network for BswM*/
                           CanSM_BswM_Mode_en = CANSM_BSWM_SILENT_COMMUNICATION;

                           /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                           BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                           /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_SILENTCOM i.e COMM_SILENT_COMMUNICATION*/
                           CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_SILENTCOM;

                           /*Notify ComM about CanSM state changes*/
                           CanSM_ComM_Mode_uo = COMM_SILENT_COMMUNICATION;
                           ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_ComM_Mode_uo);

                        }

                   }

                    /*Check if timeout has occurred and so proceed accordingly*/
                    else
                    {
                        if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {
                            /*Set the Timer to Elapsed Mode */
                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                            /*Move to previous substate ie CANSM_S_RESTART_CC*/
                            CanSM_currBOR_State_en[network]= CANSM_S_RESTART_CC;
                        }
                    }
                }
                break;
                case CANSM_S_RESTART_CC:
                {
                    /* Loop for All the Controllers in the network and Set them to STOPPED Mode*/
                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                        /*Store the CAN controller ID belonging to the network*/
                        CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                        /*Check that the CAN controller is not already STOPPED*/
                        if(CanSM_ControllerState_en[CanSM_ControllerId_u8] != CANSM_ControllerState_STARTED)
                        {
                           /*If E_NOT_OK is returned for any of the controller, increment the T_REPEAT_MAX counter and break*/
                            if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_STARTED))
                                {
                                     /*Call to CanIf_SetControllerMode() returns E_NOT_OK  */
                                    CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = FALSE;

                                    /*If atleast one unsuccessful attempt to stop the controller occured for the corresponding network then increment the unsuccessful attempt*/
                                    CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
                                    break;
                                }
                            else
                                {
                                    /*CanIf_SetControllerMode() return value */
                                    CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = TRUE;
                                }
                        }
                        else
                        {
                             /*CanIf_SetControllerMode() return value */
                            CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] = TRUE;
                        }
                    }

                    /* Loop for All the Controllers in the network to check if the mode indications are received*/
                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                         /*If for all controllers the api CanIf_SetControllerMode() has returned E_OK */
                        if(CanSM_Ctrl_return_val_b[CanSM_Ctrl_index_u8] == TRUE)
                        {
                            CanSM_Controller_Counter_u8++;
                        }
                    }

                    if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
                        {
                            /*Check if in the meantime, controller mode indication was received and update the substate if so*/
                            if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                                {
                                    /*Reset the controller mode indication flag to FALSE*/
                                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                                    /*Reset the T_REPEAT_MAX counter*/
                                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                                    CanSM_BOR_SilentCom_ab[network] = FALSE;

                                    /*Set the Timer to Elapsed Mode */
                                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                                    if(CanSM_ReqComM_Mode_en[network] == COMM_NO_COMMUNICATION)
                                    {
                                        /*The present state of the network [during initialisation]*/
                                       CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

                                       /* Change the BOR State */
                                       CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;

                                       /*When transceiver is configured, also check if PN is supported*/
                                       if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                                           {
                                               #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
                                               /*Pn checking includes that transceiver is also configured */
                                               if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
                                                   {
                                                       /*Initiate the substate machine for De-initilization with PN support*/
                                                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                                                   }
                                               else
                                                   {
                                                       /*Initiate the substate machine for De-initilization without PN*/
                                                       CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                                   }
                                               #else
                                               /*Initiate the substate machine for De-initilization without PN*/
                                               CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                               #endif
                                           }
                                       else
                                           {
                                               /*Initiate the substate machine for De-initilization without PN*/
                                               CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                                           }

                                    }
                                    else
                                    {
                                        /*Update the state of Network for BswM*/
                                       CanSM_BswM_Mode_en = CANSM_BSWM_SILENT_COMMUNICATION;

                                       /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                                       BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                                       /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_SILENTCOM i.e COMM_SILENT_COMMUNICATION*/
                                       CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_SILENTCOM;

                                       /*Notify ComM about CanSM state changes*/
                                       CanSM_ComM_Mode_uo = COMM_SILENT_COMMUNICATION;
                                       ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_ComM_Mode_uo);

                                    }

                                }
                            else
                                {   /*Move to next substate of the CANSM_S_RESTART_CC_WAIT */
                                    CanSM_currBOR_State_en[network] = CANSM_S_RESTART_CC_WAIT;

                                    /*Start the Wait state Timer */
                                    CanSM_StartTimer(network);
                                }
                        }
                }
                break;
                default:
                    /*do nothing*/
                break;
            }
        }

        else
            {
                /* Exit condition to No communication for T_Reeat_Max */

                /*The present state of the network [during initialisation]*/
                CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                /*Request for NO_COMM*/
                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;
                /*Reset T_REPEAT_MAX counter*/
                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                CanSM_BOR_SilentCom_ab[network] = FALSE;

                /*Set the Timer to Elapsed Mode */
                CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                /*When transceiver is configured, also check if PN is supported*/
                if(CanSM_Network_pcst[network].Trcv_hndle_u8 != 255u)
                    {
                        #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
                        /*Pn checking includes that transceiver is also configured */
                        if(CanSM_Network_pcst[network].TrcvPnConfig_b == TRUE)
                            {
                                /*Initiate the substate machine for De-initilization with PN support*/
                                CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
                            }
                        else
                            {
                                /*Initiate the substate machine for De-initilization without PN*/
                                CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                            }
                        #else
                        /*Initiate the substate machine for De-initilization without PN*/
                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                        #endif
                    }
                else
                    {
                        /*Initiate the substate machine for De-initilization without PN*/
                        CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
                    }

                     /*No more sub-states in BOR*/
                    CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;
                    /*Update the state of Network for BswM*/
                    CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;
                    /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                    BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);
                    /*Report to DET that T_REPEAT_MAX counter has exceeded CanSM_ModeRepeatReq_Max_u8*/
                    CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,((uint8)CANSM_MAINFUNCTION_SID),(uint8)(CANSM_E_MODE_REQUEST_TIMEOUT))

            }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
