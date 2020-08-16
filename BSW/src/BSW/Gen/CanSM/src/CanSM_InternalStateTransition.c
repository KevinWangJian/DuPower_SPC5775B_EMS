
/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
 */
#include "CanSM_Priv.h"

/**
***************************************************************************************************
** Function Name      : CanSM_GetHandle
**
** Service ID         : None
**
** Description        : This function is required to get the corresponding CanSM network Index for a given ComM channelId
**
** Sync/Async         : Asynchronous
**
** Re-entrancy        : None
**
** Input Parameters   : ComMChannelId: The ComM Channel passed.
**
** InOut parameter    : None
**
** Output Parameters  : None
**
** Return parameter   : CanSM_NetworkIdx_u8

***************************************************************************************************
**/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(NetworkHandleType, CANSM_CODE) CanSM_GetHandle(VAR(NetworkHandleType, AUTOMATIC) ComMChannelId)
{
    /*Loop variable*/
	VAR(uint8, AUTOMATIC) loop_uo;

    /* Local variable to hold network index */
    VAR(uint8, AUTOMATIC) CanSM_NetworkIdx_u8 = CANSM_ZERO;

    /* Loop through the networks */
	for(loop_uo =0; loop_uo < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; loop_uo++)
    {
        /*Check if the 'ComMChannelId' matches the configured network */
		if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[loop_uo].ComM_channelId_uo == ComMChannelId)
        {
            /*Get the network Index which matches with the ComMChannelId*/
		    CanSM_NetworkIdx_u8 = (NetworkHandleType)loop_uo;
            break;
        }
        else
        {
            /*Increment the size of network by 1 and store in the local variable*/
            CanSM_NetworkIdx_u8 = CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 + (uint8)1;
        }
    }
    return CanSM_NetworkIdx_u8;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_StopCtrl
**
** Service ID           : None
**
** Description          : This internal function is used to set the CAN controllers in the network to STOPPED mode.This funtion is called as an effect of E_PRE_NOCOM in CanSM_Mainfunction()
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_StopCtrl(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
	/*To hold the controller Id*/
	VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
	/*Used in FOR loop to access CAN controllers of the corresponding network*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
	/*Variable to hold the return status of CanIf_SetControllerMode()*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_Status_u8[CANSM_NUM_CAN_CONTROLLERS];
    #if((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
    /*To hold the ComM status*/
    VAR(ComM_ModeType, AUTOMATIC) CanSM_ComM_Mode_uo;
    #endif

	/*To keep a track of current network mode*/
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;

    /*Hold the counter number to know that all the controllers are stopped*/
    VAR(uint8, AUTOMATIC) CanSM_Controller_Counter_u8 = 0;


	/*Hold the address of the configured network*/
	CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];
	/*Make a local copy of current network mode */
	CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

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
			         /*CanIf_SetControllerMode() return value */
					CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_FALSE;

					/*If atleast one unsuccessful attempt to stop the controller occured for the corresponding network then increment the unsuccessful attempt*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;

					break;

			    }
			else
			    {
                      /*CanIf_SetControllerMode() return value */
					 CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
			    }
		}
		else
		{
			 /*CanIf_SetControllerMode() return value */
			CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
		}
	}

    /* Loop for All the Controllers in the network*/
    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
    {
	     /*If for all controllers the api CanIf_SetControllerMode() has returned E_OK */
        if(CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] == CANSM_TRUE)
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

				CanSM_Controller_Counter_u8 = CANSM_ZERO;


            #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			    if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_STOPPED))
					{
						/*Make direct transition to CANSM_S_TRCV_NORMAL*/
						CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_NORMAL;
					}
				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_S_CC_SLEEP*/
						CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP;
					}
			#else
				if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_S_CC_SLEEP*/
						CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP;
					}
			#endif

                #if((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_CHANGE_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STOPPED ))
					{
						/*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_NOCOM i.e COMM_NO_COMMUNICATION*/
						CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_NOCOM;
						/*Notify ComM*/
						CanSM_ComM_Mode_uo = COMM_NO_COMMUNICATION;
						/*Update the ComM with current communication mode*/
						ComM_BusSM_ModeIndication(CanSM_NetworkConf_ps->ComM_channelId_uo, &CanSM_ComM_Mode_uo);
						/* Loop for All the Controllers in the network and Set them to STOPPED Mode*/
						for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
							{
								/*Store the CAN controller ID belonging to the network*/
								CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                                    #if(CANSM_CHANGE_BAUDRATE_API == STD_ON)
								   /*If E_NOT_OK is returned for any of the controller, increment the T_REPEAT_MAX counter and break*/
									if(E_NOT_OK == CanIf_ChangeBaudrate(CanSM_ControllerId_u8,CanSM_ChangeBaudRate_Value_au32[network]))
                                    #else
									/*If E_NOT_OK is returned for any of the controller, increment the T_REPEAT_MAX counter and break*/
									if(E_NOT_OK == CanIf_SetBaudrate(CanSM_ControllerId_u8,CanSM_BaudRateConfigID_Value_au16[network]))
									#endif
									{
											 /*Baudrate api return value return value */
											CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_FALSE;

											/*If atleast one unsuccessful attempt to stop the controller occured for the corresponding network then increment the unsuccessful attempt*/
											CanSM_Num_Unsuccessful_ModeReq_au8[network]++;

											break;

										}
									else
										{
											  /*Baudrate api return value */
											 CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
										}

							}
						/* Loop for All the Controllers in the network*/
						for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
							{
								/*If for all controllers the api has returned E_OK */
								if(CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] == CANSM_TRUE)
								{
									CanSM_Controller_Counter_u8++;
								}
							}

						if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
							{
								/*Make direct transition to CANSM_BR_S_CC_STARTED */
								CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STARTED;
							}

					}
			#endif

				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STOPPED))
					{
						CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STARTED;
					}

				else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED))
					{
						CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STARTED;
					}

				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STOPPED))
					{
						CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STARTED;
					}

				else{
					    /*else do nothing*/
					}

        }
        /*If no mode indication was received*/
        else
        {
            /*Enter Critical section*/
			SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
			#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			    if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_STOPPED))
					{
						/*Make direct transition to CANSM_S_PN_CC_STOPPED_WAIT*/
			        CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CC_STOPPED_WAIT;
					}
			    else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_S_CC_STOPPED_WAIT*/
						CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED_WAIT;
					}
            #else
				if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_S_CC_STOPPED_WAIT*/
						CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED_WAIT;
					}
		    #endif

            #if((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_CHANGE_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STOPPED ))
					{
						/*Make direct transition to CANSM_BR_S_CC_STOPPED_WAIT */
						CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STOPPED_WAIT;
					}
			#endif

				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT */
						CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT;
					}

				else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT */
						CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT;
					}

				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_TxTimeoutException_S_CC_STOPPED_WAIT */
						CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STOPPED_WAIT;
					}

				else{
					    /*else do nothing*/
					}
			/*Exit Critical section*/
			SchM_Exit_CanSM_BOR_Nw_ModesNoNest();

			/*Start the Wait state Timer */
            CanSM_StartTimer(network);
        }
    }

    else
    {
		/*Check if the T_REPEAT_MAX has exceeded*/
        if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
        {
            /*Reset the T_REPEAT_MAX counter*/
            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
		    #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			  if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_STOPPED))
			    {
				  /*Make transition to CANSM_S_PN_CLEAR_WUF*/
				  CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
				}
			  else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
				{
				  /*Make transition to CANSM_S_CC_STOPPED*/
				  CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
				}
		    #else
				if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_STOPPED))
				{
					/*Make transition to CANSM_S_CC_STOPPED*/
					CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
				}
			#endif

            #if((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_CHANGE_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STOPPED ))
					{
				       CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;                              /*No substates to be traversed in Change Baudrate main state*/

                        /*Reset T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                        /*Request for NO_COMM*/
                        CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;
                        /*Exit with NO_COM*/
                        CanSM_ChangeBR_Exit(network);
                        }
                #endif

				else if((CanSM_CurrNwMode_en== CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STOPPED))
					{
				        CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;
                       /*Reset T_REPEAT_MAX counter*/
                       CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                       /*The present state of the network [during initialisation]*/
                       CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                       /*Request for NO_COMM*/
                       CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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

				else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED))
					{
                    CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;
                   /*Reset T_REPEAT_MAX counter*/
                   CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                   /*The present state of the network [during initialisation]*/
                   CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                   /*Request for NO_COMM*/
                   CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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

				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STOPPED))
					{
						/*Make direct transition to CANSM_TxTimeoutException_S_CC_STOPPED as a result of T_REPEAT_MAX */
						CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STOPPED;
					}

				else{
					    /*else do nothing*/
					}

            /*Report DET about exceeding of T_REPEAT_MAX counter*/
            CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED, (uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
        }
        else
        {
            /*else remain in previous state */
        }
    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"


/**
***************************************************************************************************
** Function Name        : CanSM_StartCtrl
**
** Service ID           : None
**
** Description          : This internal function is used to set the CAN controllers in the network to STARTED mode.
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_StartCtrl(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
	/*To hold the controller Id*/
	VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
	/*Used in FOR loop to access CAN controllers of the corresponding network*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
	/*Variable to hold the return status of CanIf_SetControllerMode()*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_Status_u8[CANSM_NUM_CAN_CONTROLLERS];

	/*To keep a track of current network mode*/
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;

    /*Hold the counter number to know that all the controllers are stopped*/
    VAR(uint8, AUTOMATIC) CanSM_Controller_Counter_u8 = 0;

	/*Hold the address of the configured network*/
	CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];
	/*Make a local copy of current network mode */
	CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

    /* Loop for All the Controllers in the network and Set them to STOPPED Mode*/
    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
    {
        /*Store the CAN controller ID belonging to the network*/
		CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
		/*Check that the CAN controller is not already STARTED*/
		if(CanSM_ControllerState_en[CanSM_ControllerId_u8] != CANSM_ControllerState_STARTED)
        {
           /*If E_NOT_OK is returned for any of the controller, increment the T_REPEAT_MAX counter and break*/
            if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_STARTED))
			    {
			         /*CanIf_SetControllerMode() return value */
					CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_FALSE;

					/*If atleast one unsuccessful attempt to start the controller occured for the corresponding network then increment the unsuccessful attempt*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;

					break;

			    }
			else
			    {
                      /*CanIf_SetControllerMode() return value */
					 CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
			    }
		}
		else
		{
			 /*CanIf_SetControllerMode() return value */
			CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
		}
	}

    /* Loop for All the Controllers in the network*/
    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
    {
	     /*If for all controllers the api CanIf_SetControllerMode() has returned E_OK */
        if(CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] == CANSM_TRUE)
        {
		    /*Increment the CAN controller counter*/
			CanSM_Controller_Counter_u8++;
		}
	}

        if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
		{
			/*Check if in the meantime, controller mode indication was received and update the substate if so*/
			if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
			{
				/*Enter Critical section*/
				SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
				/*Reset the controller mode indication flag to FALSE*/
				CanSM_Ctrl_ModeInd_ab[network] = FALSE;

				/*Reset T_REPEAT_MAX counter*/
				CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

				if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STARTED))
                    {
                        /*Make direct transition to CANSM_PRE_FULLCOM_DEFAULT */
                        CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;
                    }

                #if((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
				else if(CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STARTED )
					{
						/*Make direct transition to CANSM_BR_DEFAULT */
						CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;
						/*The exit can happen via FULL COM or SILENT COM*/
						CanSM_ChangeBR_Exit(network);
					}
			    #endif

				else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STARTED))
					{
						/*Make direct transition to CANSM_WAKEUP_VALIDATION_DEFAULT */
						CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;
					}

				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STARTED))
					{
						/*Make direct transition to CANSM_TxTimeoutException_DEFAULT */
						CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_DEFAULT;
					}

				else{
					    /*else do nothing*/
					}

			/*Exit Critical section*/
			SchM_Exit_CanSM_BOR_Nw_ModesNoNest();
        }
        /*If no mode indication was received*/
        else
        {
            /*Enter Critical section*/
			SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
            if((CanSM_CurrNwMode_en== CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STARTED))
                {
                    /*Make direct transition to CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT */
                    CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STARTED_WAIT;
                }

            #if((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
            else if(CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STARTED )
					{
						/*Make direct transition to CANSM_BR_S_CC_STARTED_WAIT */
						CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STARTED_WAIT;
					}
			#endif

				else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STARTED))
					{
						/*Make direct transition to CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT */
						CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STARTED_WAIT;
					}

				else if((CanSM_CurrNwMode_en == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STARTED))
					{
						/*Make direct transition to CANSM_TxTimeoutException_S_CC_STOPPED_WAIT */
						CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STARTED_WAIT;
					}

				else{
					    /*else do nothing*/
					}
			/*Exit Critical section*/
			SchM_Exit_CanSM_BOR_Nw_ModesNoNest();

			/*Start the Wait state Timer */
            CanSM_StartTimer(network);
        }
    }

    else
    {
		/*Check if the T_REPEAT_MAX has exceeded*/
        if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
        {
            /*Reset the T_REPEAT_MAX counter*/
            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
           if((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_CC_STARTED))
                {
                   CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;
                   /*Reset T_REPEAT_MAX counter*/
                   CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                   /*The present state of the network [during initialisation]*/
                   CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                   /*Request for NO_COMM*/
                   CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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
                #if((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
                else if((CanSM_CurrNwMode_en == CANSM_BSM_S_CHANGE_BAUDRATE) && (CanSM_ChangeBR_Substates_en[network] == CANSM_BR_S_CC_STARTED ))
                    {
                       CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;                              /*No substates to be traversed in Change Baudrate main state*/

                        /*Reset T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                        /*Request for NO_COMM*/
                        CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;
                        /*The exit will happen with NO COM*/
                        CanSM_ChangeBR_Exit(network);
                        }
                #endif

				else if((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_CC_STARTED))
					{
				        CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;
                       /*Reset T_REPEAT_MAX counter*/
                       CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                       /*The present state of the network [during initialisation]*/
                       CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                       /*Request for NO_COMM*/
                       CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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

				else if((CanSM_CurrNw_Mode_en[network] == CANSM_BSM_S_TX_TIMEOUT_EXCEPTION) && (CanSM_TxTimeoutexception_Substates_en[network] == CANSM_TxTimeoutException_S_CC_STARTED))
					{
						/*Make direct transition to CANSM_TxTimeoutException_S_CC_STOPPED as a result of T_REPEAT_MAX */
						CanSM_TxTimeoutexception_Substates_en[network] = CANSM_TxTimeoutException_S_CC_STOPPED;
					}

				else{
					    /*else do nothing*/
					}

            /*Report DET about exceeding of T_REPEAT_MAX counter*/
            CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED, (uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
        }
        else
        {
            /*else remain in previous state */
        }
    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_SleepCtrl
**
** Service ID           : None
**
** Description          : This internal function is used to set the CAN controllers in the network to SLEEP mode.This funtion is called as an effect of E_PRE_NOCOM in CanSM_Mainfunction()
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_SleepCtrl(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
	/*To hold the controller Id*/
	VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
	/*Used in FOR loop to access CAN controllers of the corresponding network*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
	/*Variable to hold the return status of CanIf_SetControllerMode()*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_Status_u8[CANSM_NUM_CAN_CONTROLLERS];

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
		if(CanSM_ControllerState_en[CanSM_ControllerId_u8] != CANSM_ControllerState_SLEEP)
        {
           /*If E_NOT_OK is returned for any of the controller, increment the T_REPEAT_MAX counter and break*/
            if(E_NOT_OK == CanIf_SetControllerMode(CanSM_ControllerId_u8,CANIF_CS_SLEEP))
			    {
			        /*CanIf_SetControllerMode() return value */
					CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_FALSE;
					/*If atleast one unsuccessful attempt to sleep the controller occured for the corresponding network then increment the unsuccessful attempt*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
					break;
			    }
			else
			    {
                      /*CanIf_SetControllerMode() return value */
					 CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
			    }
		}
		else
		{
			 /*CanIf_SetControllerMode() return value */
			CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
		}
	}

    /* Loop for All the Controllers in the network*/
    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
    {
	     /*If for all controllers the api CanIf_SetControllerMode() has returned E_OK */
        if(CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] == CANSM_TRUE)
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

            #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			    if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_SLEEP)
			      {
					/*Make direct transition to CANSM_S_TRCV_NORMAL*/
					CanSM_PreNoCom_Substates_en[network]=  CANSM_S_CHECK_WFLAG_IN_CC_SLEEP;
			      }
				else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_SLEEP)
				  {
				    /*Make direct transition to CANSM_S_CC_SLEEP*/
                    CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;
				  }
			    else
			      {
				    /*No action required*/
			      }
            #else
			   /*Make direct transition to CANSM_S_CC_SLEEP*/
               CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL;
			#endif

            /*Reset the T_REPEAT_MAX counter*/
            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
        }
        /*If no mode indication was received*/
        else
        {
            #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			    if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_SLEEP)
			      {
			      /*Make direct transition to CANSM_S_PN_CC_SLEEP_WAIT*/
			        CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CC_SLEEP_WAIT;
			      }
			    else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_SLEEP)
			      {
				  /*Make direct transition to CANSM_S_CC_SLEEP_WAIT*/
                  CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP_WAIT;
			      }
			    else
			      {
				  /*No action required*/
			      }
            #else
			   /*Make direct transition to CANSM_S_CC_SLEEP_WAIT*/
               CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_SLEEP_WAIT;
		    #endif
            /*Start the Wait state Timer */
            CanSM_StartTimer(network);
        }
    }

    else
    {
        if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
        {
            /*Reset the T_REPEAT_MAX counter*/
            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
		    #if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			  if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CC_SLEEP)
			    {
				  /*Make transition to CANSM_S_PN_CLEAR_WUF*/
				  CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
				}
			  else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CC_SLEEP)
				{
				  /*Make transition to CANSM_S_CC_STOPPED*/
				  CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
				}
			  else
				{
				  /*No action required*/
				}
		    #else
		     /*Make transition to CANSM_S_CC_STOPPED*/
		     CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
		    #endif
             /*Report DET about exceeding of T_REPEAT_MAX counter*/
             CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,(uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
        }
        else
        {
            /*else remain in previous state */
        }
    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"


/**
***************************************************************************************************
** Function Name        : CanSM_NormalTrcv
**
** Service ID           : None
**
** Description          : This internal function is used to set the CAN Transceivers in the network to NORMAL mode.This funtion is called as an effect of E_PRE_NOCOM in CanSM_Mainfunction()
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE)CanSM_NormalTrcv(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*To keep a track of current network mode*/
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;
    /*Make a local copy of current network mode */
    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

	/* Set the transceiver of the network to NORMAL Mode*/
    if(E_OK == CanIf_SetTrcvMode(CanSM_Network_pcst[network].Trcv_hndle_u8,CANTRCV_TRCVMODE_NORMAL))
		{
            /*Check if in the meantime, transceiver mode indication was received and update the substate if so*/
            if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
				{
					/*Enter Critical section*/
					SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
					/*Reset the transceiver mode indication flag to FALSE only if transceiver is configured for the network if*/
					CanSM_Trcv_ModeInd_ab[network]=FALSE;

					#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
					if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) &&(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_NORMAL))
						{
							/*Make direct transition to CANSM_S_PN_TRCV_STANDBY*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_STANDBY;
						}
					else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) &&(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
						{
							/*Make direct transition to CANSM_S_TRCV_STANDBY*/
							CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY;
						}
					#else
						if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
							{
								/*Make direct transition to CANSM_S_TRCV_STANDBY*/
								CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY;
							}
					#endif

					else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_TRCV_NORMAL))
						{
							/*Make direct transition to CANSM_PRE_FULLCOM_S_CC_STOPPED*/
							CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STOPPED;
						}
					else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL))
						{
							/*Make direct transition to CANSM_WAKEUP_VALIDATION_S_CC_STOPPED*/
							CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;
						}
					else
						{
							/*else do nothing*/
						}
					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
					/* Critical section Exit*/
					SchM_Exit_CanSM_BOR_Nw_ModesNoNest();
				}
            /*If no mode indication was received*/
			else
				{
					/*Enter Critical section*/
					SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
					#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
						if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) &&(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_NORMAL))
							{
								/*Make direct transition to CANSM_S_PN_TRCV_NORMAL_WAIT*/
								CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_NORMAL_WAIT;
							}
						else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
							{
								/*Make direct transition to CANSM_S_TRCV_NORMAL_WAIT*/
								CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL_WAIT;
							}
					#else
						if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
							{
								/*Make direct transition to CANSM_S_TRCV_NORMAL_WAIT*/
								CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_NORMAL_WAIT;
							}
					#endif
						else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_TRCV_NORMAL))
							{
								/*Make direct transition to CANSM_PRE_FULLCOM_S_TRCV_NORMAL_WAIT */
								CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_TRCV_NORMAL_WAIT;
							}

						else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL))
							{
								/*Make direct transition to CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL_WAIT */
								CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL_WAIT;
							}
						else
							{
								/*else do nothing*/
							}
					/* Critical section Exit*/
					SchM_Exit_CanSM_BOR_Nw_ModesNoNest();
					/*Start the Wait state Timer */
					CanSM_StartTimer(network);
				}
		}

    /*If it returns E_NOT_OK, stay in the same sub-state. Increment error count of the network*/
    else
		{
			if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
				{
					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
					#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
						if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_NORMAL))
							{
								/*Make transition to CANSM_S_PN_CLEAR_WUF*/
								CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
							}
						else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
							{
								/*Make transition to CANSM_S_CC_STOPPED*/
								CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
							}
					#else
						if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_NOCOM) && (CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL))
							{
								/*Make transition to CANSM_S_CC_STOPPED*/
								CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
							}
					#endif
						else if((CanSM_CurrNwMode_en == CANSM_BSM_S_PRE_FULLCOM) && (CanSM_PreFullCom_Substates_en[network] == CANSM_PRE_FULLCOM_S_TRCV_NORMAL))
							{
	                            CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;
	                            /*Reset T_REPEAT_MAX counter*/
	                            CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
	                            /*The present state of the network [during initialisation]*/
	                            CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
	                            /*Request for NO_COMM*/
	                            CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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
						else if((CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL))
							{
						        CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;
                               /*Reset T_REPEAT_MAX counter*/
                               CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                               /*The present state of the network [during initialisation]*/
                               CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
                               /*Request for NO_COMM*/
                               CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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
								/* do nothing */
							}

					/*Report DET about exceeding of T_REPEAT_MAX counter*/
					CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED, (uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
				}
			else
				{
					/*Increment the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
				}
		}
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"



/**
***************************************************************************************************
** Function Name        : CanSM_StandbyTrcv
**
** Service ID           : None
**
** Description          : This internal function is used to set the CAN Transceivers in the network to STANDBY mode.This funtion is called as an effect of E_PRE_NOCOM in CanSM_Mainfunction()
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE)CanSM_StandbyTrcv(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*Local variabe to hold the BSWM mode*/
	VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;

	/* Set the transceiver of the network to NORMAL Mode*/
    if(E_OK == CanIf_SetTrcvMode(CanSM_Network_pcst[network].Trcv_hndle_u8,CANTRCV_TRCVMODE_STANDBY))
		{
            /*Check if in the meantime, transceiver mode indication was received and update the substate if so*/
            if(CanSM_Trcv_ModeInd_ab[network] == TRUE)
				{
					/*Reset the transceiver mode indication flag to FALSE only if transceiver is configured for the network if*/
					CanSM_Trcv_ModeInd_ab[network]=FALSE;
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

					#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_STANDBY)
						{
							/*Make direct transition to CANSM_S_PN_CC_SLEEP*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CC_SLEEP;
						}
					else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_STANDBY)
						{
							/*Make direct transition to CANSM_DEFAULT*/
							CanSM_PreNoCom_Substates_en[network]= CANSM_DEFAULT;

		                    /*The network is now initialized*/
		                    CanSM_Network_Init_ab[network] = TRUE;

		                    /*Update the state of Network for BswM*/
		                    CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;

		                    /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
		                    BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

                            /* Loop for All the Controllers in the Network and put the pdu mode to OFFLINE*/
                            for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                            {
                                CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                                /* set PDU to OFFLINE Mode */
                                /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                                (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_OFFLINE));

                            }

		                    /*The state machine can move to NOCOM or WUVALIDATION depending upon the trigger */
		                    if(CanSM_Wuvalidation_Start_ab[network] == TRUE)
		                        {
		                            /*Update the current network mode to CANSM_BSM_WUVALIDATION*/
		                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;
		                            /*Update the array state to CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL */
		                            CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

		                        }
		                    else
		                        {
		                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_S_NOCOM;

		                        }
						}
					else
						{
							/* do nothing */
						}
					#else
					/*Make direct transition to CANSM_DEFAULT*/
					CanSM_PreNoCom_Substates_en[network]= CANSM_DEFAULT;

                    /*The network is now initialized*/
                    CanSM_Network_Init_ab[network] = TRUE;

                    /*Update the state of Network for BswM*/
                    CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;

                    /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                    BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

                    /* Loop for All the Controllers in the Network and put the pdu mode to OFFLINE*/
                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                        /* set PDU to OFFLINE Mode */
                        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_OFFLINE));

                    }

                    /*The state machine can move to NOCOM or WUVALIDATION depending upon the trigger */
                    if(CanSM_Wuvalidation_Start_ab[network] == TRUE)
                        {
                            /*Update the current network mode to CANSM_BSM_WUVALIDATION*/
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;
                            /*Update the array state to CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL */
                            CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

                        }
                    else
                        {
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_S_NOCOM;

                        }
					#endif


				}
            /*If no mode indication was received*/
			else
				{
					#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_STANDBY)
						{
							/*Make direct transition to CANSM_S_PN_TRCV_STANDBY_WAIT*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_TRCV_STANDBY_WAIT;
						}
					else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_STANDBY)
						{
							/*Make direct transition to CANSM_S_TRCV_STANDBY_WAIT*/
							CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY_WAIT;
						}
					else
						{
							/*No action required*/
						}
					#else
					/*Make transition to CANSM_S_TRCV_STANDBY_WAIT*/
					CanSM_PreNoCom_Substates_en[network]= CANSM_S_TRCV_STANDBY_WAIT;
					#endif
					/*Start the Wait state Timer */
					CanSM_StartTimer(network);
				}
		}

    /*If it returns E_NOT_OK, stay in the same sub-state. Increment error count of the network*/
    else
		{
			if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
				{
					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

					#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_TRCV_STANDBY)
						{
							/*Make transition to CANSM_S_PN_CLEAR_WUF*/
							CanSM_PreNoCom_Substates_en[network]= CANSM_S_PN_CLEAR_WUF;
						}
					else if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_TRCV_NORMAL)
						{
							/*Make transition to CANSM_S_CC_STOPPED*/
							CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
						}
					else
						{
							/*No action required*/
						}
					#else
				    /*Make transition to CANSM_S_CC_STOPPED*/
					CanSM_PreNoCom_Substates_en[network]= CANSM_S_CC_STOPPED;
					#endif
					/*Report DET about exceeding of T_REPEAT_MAX counter*/
					CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED, (uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
				}
			else
				{
					/*Increment the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
				}
		}
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_PN_ClearWufTrcv
**
** Service ID           : None
**
** Description          : This internal function is used to check if the Transceiver WUF is cleared
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE)CanSM_PN_ClearWufTrcv(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /* Check if the call to CanIf_ClearTrcvWufFlag is successful*/
    if(E_OK == CanIf_ClearTrcvWufFlag(CanSM_Network_pcst[network].Trcv_hndle_u8))
		{
            /*Check if in the meantime, PN-indication was received*/
            if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
				{
					/*Enter Critical section*/
					SchM_Enter_CanSM_BOR_Nw_ModesNoNest();
					/*Reset the PN-indication */
					CanSM_PN_Substate_Ind_ab[network]=FALSE;

					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CLEAR_WUF)
						{
							/*Make direct transition to CANSM_S_PN_CC_STOPPED*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CC_STOPPED;
						}

					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
					/* Critical section Exit*/
					SchM_Exit_CanSM_BOR_Nw_ModesNoNest();
				}
            /*If no PN indication was received*/
			else
				{

					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CLEAR_WUF)
						{
							/*Make direct transition to CANSM_S_PN_CLEAR_WUF_WAIT*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CLEAR_WUF_WAIT;
						}

					/*Start the Wait state Timer */
					CanSM_StartTimer(network);
				}
		}

    /*If it returns E_NOT_OK and T_REPEAT_MAX exceeds go to starting of the state machine. Increment error count of the network*/
    else
		{
			if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
				{
					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
					/*Make transition to CANSM_S_PN_CLEAR_WUF*/
					CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
					/*Report DET about exceeding of T_REPEAT_MAX counter*/
					CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED, (uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
				}
			else
				{
					/*Increment the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;

				}
		}
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

/**
***************************************************************************************************
** Function Name        : CanSM_CheckWakeUpFlagInSleep
**
** Service ID           : None
**
** Description          : This internal function is used to check if the WUF flag was set by calling CanIf_CheckTrcvWakeFlag()
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE)CanSM_CheckWakeUpFlagInSleep(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*Local variabe to hold the BSWM mode*/
	VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

	/*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;

    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;
    /* Check if the call to CanIf_ClearTrcvWufFlag is successful*/
    if(E_OK == CanIf_CheckTrcvWakeFlag(CanSM_Network_pcst[network].Trcv_hndle_u8))
		{
            /*Check if in the meantime, PN-indication was received*/
            if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
				{
					/*Enter Critical section*/
					SchM_Enter_CanSM_BOR_Nw_ModesNoNest();

                    /*Reset all the mode indication flags*/
                    CanSM_PN_Substate_Ind_ab[network]   = FALSE;
                    CanSM_Ctrl_ModeInd_ab[network]      = FALSE;
                    CanSM_Trcv_ModeInd_ab[network]      = FALSE;
                    /*The corresponding CanSM network is now initilaised*/
                    CanSM_Network_Init_ab[network] = TRUE;

					/*Check if the previous state was CANSM_S_CHECK_WFLAG_IN_CC_SLEEP*/
					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_CC_SLEEP)
						{
							/*Make direct transition to CANSM_DEFAULT*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_DEFAULT;
						}

					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    /* Loop for All the Controllers in the Network and put the pdu mode to OFFLINE*/
                    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                        /* set PDU to OFFLINE Mode */
                        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_OFFLINE));

                    }
                    /*Update the state of Network for BswM*/
                    CanSM_BswM_Mode_en = CANSM_BSWM_NO_COMMUNICATION;

                    /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                    BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);

                    /*The state machine can move to NOCOM or WUVALIDATION depending upon the trigger */
                    if(CanSM_Wuvalidation_Start_ab[network] == TRUE) /* updated in CanSM_StartWakeUpSource() api called by Ecum*/
                        {
                            /*Update the current network mode to CANSM_BSM_WUVALIDATION*/
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_WUVALIDATION;
                            /*Update the array state to CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL */
                            CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

                        }
                    else
                        {
                            CanSM_CurrNw_Mode_en[network]= CANSM_BSM_S_NOCOM;
                        }
					/* Critical section Exit*/
					SchM_Exit_CanSM_BOR_Nw_ModesNoNest();
				}
            /*If no PN indication was received*/
			else
				{
					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_CC_SLEEP)
						{
							/*Make direct transition to CANSM_S_CHECK_WFLAG_IN_CC_SLEEP_WAIT*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_CHECK_WFLAG_IN_CC_SLEEP_WAIT;
						}

					/*Start the Wait state Timer */
					CanSM_StartTimer(network);
				}
		}

    /*If it returns E_NOT_OK and T_REPEAT_MAX exceeds go to starting of the state machine. Increment error count of the network*/
    else
		{
			if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
				{
					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
					/*Make transition to CANSM_S_PN_CLEAR_WUF*/
					CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
					/*Report DET about exceeding of T_REPEAT_MAX counter*/
					CANSM_REPORT_ERROR(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CLEAR_WUF, (uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
				}
			else
				{
					/*Increment the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
				}
		}
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

/**
***************************************************************************************************
** Function Name        : CanSM_CheckWakeUpFlagNotInSleep
**
** Service ID           : None
**
** Description          : This internal function is called to restart the PN_PRE_NOCOM process
**
** Sync/Async           :
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************
**/
#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE)CanSM_CheckWakeUpFlagNotInSleep(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /* Check if the call to CanIf_ClearTrcvWufFlag is successful*/
    if(E_OK == CanIf_CheckTrcvWakeFlag(CanSM_Network_pcst[network].Trcv_hndle_u8))
		{
            /*Check if in the meantime, PN-indication was received*/
            if(CanSM_PN_Substate_Ind_ab[network] == TRUE)
				{
					/*Enter Critical section*/
					SchM_Enter_CanSM_BOR_Nw_ModesNoNest();

					/*Reset the PN-indication */
					CanSM_PN_Substate_Ind_ab[network]=FALSE;

					/*Set the Timer to Elapsed Mode */
					CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

					/*Check if the previous state was CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP*/
					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP)
						{
							/*Make direct transition to CANSM_S_PN_CLEAR_WUF*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_PN_CLEAR_WUF;
						}

					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

					/* Critical section Exit*/
					SchM_Exit_CanSM_BOR_Nw_ModesNoNest();
				}
            /*If no PN indication was received*/
			else
				{
					if(CanSM_PreNoCom_Substates_en[network] == CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP)
						{
							/*Make direct transition to CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP_WAIT*/
							CanSM_PreNoCom_Substates_en[network]=  CANSM_S_CHECK_WFLAG_IN_NOT_CC_SLEEP_WAIT;
						}

					/*Start the Wait state Timer */
					CanSM_StartTimer(network);
				}
		}

    /*If it returns E_NOT_OK and T_REPEAT_MAX exceeds go to starting of the state machine. Increment error count of the network*/
    else
		{
			if(CanSM_Num_Unsuccessful_ModeReq_au8[network] >= CanSM_ModeRepeatReq_Max_u8)
				{
					/*Reset the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
					/*Make transition to CANSM_S_PN_CLEAR_WUF*/
					CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
					/*Report DET about exceeding of T_REPEAT_MAX counter*/
					CANSM_REPORT_ERROR(CanSM_PreNoCom_Substates_en[network] == CANSM_S_PN_CLEAR_WUF, (uint8)CANSM_MAINFUNCTION_SID,(uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
				}
			else
				{
					/*Increment the T_REPEAT_MAX counter*/
					CanSM_Num_Unsuccessful_ModeReq_au8[network]++;
				}
		}
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

/**
***************************************************************************************************
** Function Name        : CanSM_SetBaudrate_StateMachine
**
** Service ID           : None
**
** Description          : This function takes care of executing the state machhine for the Baudrate Change.
**						  Both the wait and no wait states are implemented here.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/

#if(CANSM_SET_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_SetBaudrate_StateMachine(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*To keep the track of Change baudrate substates*/
    VAR(CanSM_ChangeBR_Substates_ten, AUTOMATIC) CanSM_ChangeBaudrate_Substates;
	/*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
	/*To hold the controller Id*/
	VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
	/*Used in FOR loop to access CAN controllers of the corresponding network*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
	/*Variable to hold the return status of CanIf_SetBaudrate()*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_Status_u8[CANSM_NUM_CAN_CONTROLLERS];

    /*To keep a track of current Baudrate conig id */
    VAR(uint16, AUTOMATIC) CanSM_BaudConfigID_u16;

    /*Hold the counter number to know that all the controllers are stopped*/
    VAR(uint8, AUTOMATIC) CanSM_Controller_Counter_u8 = 0;
	/*Hold the address of the configured network*/
	CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];


    /*Make local copy CanSM_ChangeBR_Substates_en[network]*/
    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

    /*Make local copy of global array CanSM_BaudRateConfigID_Value_au16[network]*/
    CanSM_BaudConfigID_u16 = CanSM_BaudRateConfigID_Value_au16[network];

    /*If T_REPEAT_MAX counter has not exceeded*/
    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
    {
    switch(CanSM_ChangeBaudrate_Substates)
    {
        case CANSM_BR_S_CC_STOPPED_WAIT:
        {
            /*Check if a controller indication was received that all the CAN controllers are stopped*/
            if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
            {
                /*Set the Timer to Elapsed Mode */
                CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                /*Reset the controller mode indication flag for the network*/
                CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                /*Move to next substate of the CANSM_BR_S_CC_STARTED */
                CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STARTED;

                CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                /*Reset the T_REPEAT_MAX counter*/
                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

           }

            /*Check if timeout has occurred and so proceed accordingly*/
            else
            {
                if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Move to previous substate ie CANSM_BR_S_CC_STOPPED*/
                    CanSM_ChangeBR_Substates_en[network]=CANSM_BR_S_CC_STOPPED;

                    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
                }
            }
        }
        break;

        case CANSM_BR_S_CC_STARTED_WAIT:
        {
            /*Check if a controller indication was received...*/
            if(CanSM_Ctrl_ModeInd_ab[network]==TRUE)
            {
                /*Reset the controller mode indication flag for the network*/
                CanSM_Ctrl_ModeInd_ab[network]=FALSE;

                /*Set the Timer to Elapsed Mode */
                CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                /*move to next state CANSM_BR_S_CC_STARTED*/
                CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;

                CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                /*Reset the T_REPEAT_MAX counter*/
                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                /*Exit with FULL COM or SILENT COM*/
                CanSM_ChangeBR_Exit(network);

            }

            /*check if timeout has occurred and proceed accordingly.*/
            else
            {
                if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Move to previous substate ie CANSM_BR_S_CC_STARTED*/
                    CanSM_ChangeBR_Substates_en[network]=CANSM_BR_S_CC_STARTED;

                    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                }
            }

        }
        break;

        default:
            /*do nothing*/
        break;

    }/*switch ends*/
}
else
{
    /*Start prepare to NOCOM again*/
    CanSM_ChangeBR_Substates_en[network]=CANSM_BR_DEFAULT;

    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

    /*Reset the T_REPEAT_MAX counter*/
    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

    /*Request for NO_COMM*/
    CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

    /*Exit with NO COM*/
    CanSM_ChangeBR_Exit(network);

    /*Report to DET that T_REPEAT_MAX counter has exceeded CANSM_MODEREQ_MAX*/
    CANSM_REPORT_ERROR(CanSM_ChangeBR_Substates_en[network]==CANSM_BR_S_CC_STOPPED,((uint8)CANSM_MAINFUNCTION_SID),(CANSM_E_MODE_REQUEST_TIMEOUT))

}/*else(near switch) ends*/
	/*Check if the baudrate changes directly*/
	if(CanSM_ChangeBaudrate_Substates == CANSM_BSM_CHANGE_BR_SYNC)
		{
			/* Loop for All the Controllers in the network and Set them to STOPPED Mode*/
			for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
				{
					/*Store the CAN controller ID belonging to the network*/
					CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];

				   /*Check if call of CanIf_SetBaudrate() provides direct baudrate change*/
					if(E_NOT_OK == CanIf_SetBaudrate(CanSM_ControllerId_u8,CanSM_BaudConfigID_u16))
						{
							/*CanIf_SetBaudrate() return value */
							CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_FALSE;
							break;
						}
					else
						{
							 /*CanIf_SetBaudrate() return value */
							 CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] = CANSM_TRUE;
						}
				}

			/* Loop for All the Controllers in the network*/
			for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
			{
				 /*If for all controllers the api has returned E_OK */
				if(CanSM_Ctrl_Status_u8[CanSM_Ctrl_index_u8] == CANSM_TRUE)
				{
					CanSM_Controller_Counter_u8++;
				}
			}

		if(CanSM_Controller_Counter_u8 == CanSM_NetworkConf_ps->SizeofController_u8 )
			{
				CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;
				/*keep a copy of the current substate */
				CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
				/*Exit Criteria*/
                /*Exit with FULL COM or SILENT_COM*/
                CanSM_ChangeBR_Exit(network);
			}
		}
		else
			{
				/*Move to the next substate CANSM_BR_S_CC_STOPPED*/
				CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STOPPED;
				/*keep a copy of the current substate */
				CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
			}

        /* Check if ChangeBaudrate Substate is equal to CANSM_BR_S_CC_STOPPED*/
        if(CanSM_ChangeBaudrate_Substates == CANSM_BR_S_CC_STOPPED)
        {
            /*Put all the CAN controllers of the intended network to Stop mode*/
            CanSM_StopCtrl(network);
            CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
        }

        /* Check if ChangeBaudrate Substate is equal to CANSM_BR_S_CC_STARTED*/
        if(CanSM_ChangeBaudrate_Substates == CANSM_BR_S_CC_STARTED)
        {
            /*Put all the CAN controllers of the intended network to Start mode*/
            CanSM_StartCtrl(network);
            CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
        }


}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

/**
***************************************************************************************************
** Function Name        : CanSM_ChangeBaudrate_StateMachine
**
** Service ID           : None
**
** Description          : This function takes care of executing the state machhine for the Baudrate Change.
**						  Both the wait and no wait states are implemented here.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/

#if(CANSM_CHANGE_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ChangeBaudrate_StateMachine(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*To keep the track of Change baudrate substates*/
    VAR(CanSM_ChangeBR_Substates_ten, AUTOMATIC) CanSM_ChangeBaudrate_Substates;

    /*Make local copy CanSM_ChangeBR_Substates_en[network]*/
    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

    /*If T_REPEAT_MAX counter has not exceeded*/
    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
    {
        switch(CanSM_ChangeBaudrate_Substates)
        {
            case CANSM_BR_S_CC_STOPPED_WAIT:
            {
                /*Check if a controller indication was received that all the CAN controllers are stopped*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the controller mode indication flag for the network*/
                    CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                    /*Reset the T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    /*Move to next substate of the CANSM_BR_S_CC_STARTED */
                    CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STARTED;

                    /*Make local copy CanSM_ChangeBR_Substates_en[network]*/
                    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
               }

                /*Check if timeout has occurred and so proceed accordingly*/
                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie CANSM_BR_S_CC_STOPPED*/
                        CanSM_ChangeBR_Substates_en[network]=CANSM_BR_S_CC_STOPPED;

                        /*Make local copy CanSM_ChangeBR_Substates_en[network]*/
                        CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
                    }
                }
            }
            break;

            case CANSM_BR_S_CC_STARTED_WAIT:
            {
                /*Check if a controller indication was received...*/
                if(CanSM_Ctrl_ModeInd_ab[network]==TRUE)
                {
                    /*Set the Timer to Elapsed Mode */
                    CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                    /*Reset the controller mode indication flag for the network*/
                    CanSM_Ctrl_ModeInd_ab[network]=FALSE;

                    /*move to next state CANSM_S_TRCV_NORMAL*/
                    CanSM_ChangeBR_Substates_en[network]=CANSM_BR_DEFAULT;

                    /*Make local copy CanSM_ChangeBR_Substates_en[network]*/
                    CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                    /*Reset the T_REPEAT_MAX counter*/
                    CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    /*Exit with FULL or SILENT COM*/
                    CanSM_ChangeBR_Exit(network);

                }

                /*check if timeout has occurred and proceed accordingly.*/
                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie CANSM_BR_S_CC_STARTED*/
                        CanSM_ChangeBR_Substates_en[network]=CANSM_BR_S_CC_STARTED;

                        /*Make local copy CanSM_ChangeBR_Substates_en[network]*/
                        CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

                    }
                }

            }
            break;

            default:
            /* Intentionally Empty */
            break;

        }/*switch ends*/
    }
    else
    {
        /*Start prepare to NOCOM again*/
        CanSM_ChangeBR_Substates_en[network] = CANSM_BR_DEFAULT;

        /*Make local copy CanSM_ChangeBR_Substates_en[network]*/
        CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

        /*Reset the T_REPEAT_MAX counter*/
        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

        /*Request for NO_COMM*/
        CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

        /*Exit with NO COM*/
        CanSM_ChangeBR_Exit(network);

        /*Report to DET that T_REPEAT_MAX counter has exceeded CANSM_MODEREQ_MAX*/
        CANSM_REPORT_ERROR(CanSM_PreNoCom_Substates_en[network]==CANSM_S_CC_STOPPED,(uint8)CANSM_MAINFUNCTION_SID,(uint8)(CANSM_E_MODE_REQUEST_TIMEOUT))

    }/*else(near switch) ends*/

    /* Check if ChangeBaudrate Substate is equal to CANSM_BR_S_CC_STOPPED*/
    if(CanSM_ChangeBaudrate_Substates == CANSM_BR_S_CC_STOPPED)
    {
        /*Put all the CAN controllers of the intended network to Stop mode*/
        CanSM_StopCtrl(network);
		/*keep a copy of the current substate */
		CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];
    }

    /* Check if ChangeBaudrate Substate is equal to CANSM_BR_S_CC_STARTED*/
    if(CanSM_ChangeBaudrate_Substates == CANSM_BR_S_CC_STARTED)
    {
        /*Put all the CAN controllers of the intended network to Start mode*/
        CanSM_StartCtrl(network);
		/*keep a copy of the current substate */
		CanSM_ChangeBaudrate_Substates = CanSM_ChangeBR_Substates_en[network];

    }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
/**
***************************************************************************************************
** Function Name        : CanSM_NO2FULL_COM
**
** Service ID           : None
**
** Description          :  This function does all the  necessary tasks when there is a Network Mode Transition from NO_COM
**                         to FULL_COM. This is an Internal Function
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          :
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
FUNC(void, CANSM_CODE) CanSM_NO2FULL_COM(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*To keep the track of CanSM_PreFullCom_Substates*/
    VAR(CanSM_PreFullCom_Substates_ten, CANSM_VAR) CanSM_PreFullCom_Substates;

    /*Local variabe to hold the BSWM mode*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

    /*Temporary pointer to CanSM_Network_pcst[]*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_APPL_DATA ) NetworkConf_ps;

    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;

    VAR(ComM_ModeType, AUTOMATIC) CanSM_reqComM_Mode_uo;

    /*Hold the address of the passed network*/
    NetworkConf_ps = &CanSM_Network_pcst[network];

    /*Make local copy CanSM_PreNoCom_Substates_en[network]*/
    CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

    /*If T_REPEAT_MAX counter has not exceeded*/
    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
        {
            switch(CanSM_PreFullCom_Substates)
            {
                case CANSM_PRE_FULLCOM_S_TRCV_NORMAL_WAIT:
                {
                    /*Check if a transceiver indication was received...*/
                    if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                    {
                        /*Check if the transceiver is configured*/
                        if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
                            {
                                /*Reset the transceiver mode indication flag to FALSE only if transceiver is configured */
                                CanSM_Trcv_ModeInd_ab[network] = FALSE;
                            }

                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*move to next state*/
                        CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_CC_STOPPED;

                        /*Make local copy CanSM_PreNoCom_Substates_en[network]*/
                        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    }
                    else
                    {
                        /*check if timeout has occurred and proceed accordingly.*/
                        if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {
                            /*Set the Timer to Elapsed Mode */
                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                            /*Move to previous substate ie CANSM_PRE_FULLCOM_S_TRCV_NORMAL*/
                            CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_TRCV_NORMAL;

                            /*keep a copy of the current substate */
                            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
                        }
                    }
                }
                break;
            case CANSM_PRE_FULLCOM_S_CC_STOPPED_WAIT:
                {
                    /*Check if a controller indication was received that all the CAN controllers are stopped*/
                    if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Reset the controller mode indication flag for the network*/
                        CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                        /*Move to next substate of the CANSM_PRE_FULLCOM_S_CC_STARTED */
                        CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STARTED;

                        /*keep a copy of the current substate */
                        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                   }

                    /*Check if timeout has occurred and so proceed accordingly*/
                    else
                    {
                        if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {
                            /*Set the Timer to Elapsed Mode */
                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                            /*Move to previous substate ie CANSM_PRE_FULLCOM_S_CC_STOPPED*/
                            CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_CC_STOPPED;

                            /*keep a copy of the current substate */
                            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
                        }
                    }
                }
                break;
            case CANSM_PRE_FULLCOM_S_CC_STARTED_WAIT:
            {
                /*Check if a controller indication was received that all the CAN controllers are stopped*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {
                        CanSM_Ctrl_ModeInd_ab[network] = FALSE;
                        CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_DEFAULT;

                        /*keep a copy of the current substate */
                        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                        /*Update the state of Network for BswM*/
                        CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

                        /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                        BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                        /*Current mode is FULL_COM*/
                        CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_FULLCOM;

                        /*Reset T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;

                        /* Reset Bus-Off Counter */
                        CanSM_BusOff_Cntr_au8[network] = CANSM_ZERO;

                        /* Change the BOR State */
                        CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

                        /* Change the Bus-Off Recovery Mode to Recovery enabled */
                        CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_ENABLED;

                        /*Update CanSM_BusSMMode_t_a_u8[] to CANSM_BSM_S_FULLCOM i.e COMM_FULL_COMMUNICATION*/
                        CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

                        for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                            {
                                CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                                #if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
                                if(CanSM_Passive_b == TRUE)
                                    {
                                        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                                        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_TX_OFFLINE_ACTIVE));
                                    }
                                else
                                    {
                                        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                                        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_ONLINE));
                                    }
                                    #else
                                    /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                                    (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_ONLINE));
                                #endif
                            }

                        /*Notify to ComM about CanSM state Transition*/
                        CanSM_reqComM_Mode_uo = COMM_FULL_COMMUNICATION;
                        ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_reqComM_Mode_uo);
                    }

                /*Check if timeout has occurred and so proceed accordingly*/
                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie CANSM_PRE_FULLCOM_S_CC_STOPPED*/
                        CanSM_PreFullCom_Substates_en[network]= CANSM_PRE_FULLCOM_S_CC_STARTED;

                        /*keep a copy of the current substate */
                        CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
                    }
                }
            }
            break;
            default:
            /* Intentionally Empty */
            break;

        }
    }
    else
        {
           CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_DEFAULT;
           /*keep a copy of the current substate */
           CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
          /*Reset T_REPEAT_MAX counter*/
          CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
          /*The present state of the network [during initialisation]*/
          CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
          /*Request for NO_COMM*/
          CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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
    /*Check the first substate of PRE_NOCOM is CANSM_PRE_FULLCOM_S_TRCV_NORMAL*/
    if(CanSM_PreFullCom_Substates == CANSM_PRE_FULLCOM_S_TRCV_NORMAL)
        {
            if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255u)
                {
                    /*Tranceiver mode indication is considered to be received*/
                    CanSM_Trcv_ModeInd_ab[network] = TRUE;
                    /*If no CanSMTransceiverId is configured for a CAN Network, then the CanSM module shall bypass all specified
                    CanIf_SetTrcvMode  calls for the CAN Network and proceed in the different state transitions as if it has got the supposed
                    CanSM_TransceiverModeIndication already*/
                    CanSM_PreFullCom_Substates_en[network] = CANSM_PRE_FULLCOM_S_CC_STOPPED;
                    /*keep a copy of the current substate */
                    CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
                }
                else
                {
                    /*Put the transceiver to Normal mode*/
                    /*Depending on the mode indication received / not received, the next substate can be CANSM_S_TRCV_STANDBY / CANSM_S_TRCV_NORMAL_WAIT*/
                    CanSM_NormalTrcv(network);
                    /*keep a copy of the current substate */
                    CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
                }
        }
    if(CanSM_PreFullCom_Substates == CANSM_PRE_FULLCOM_S_CC_STOPPED)
        {
            /*Stop the CAN controllers*/
            CanSM_StopCtrl(network);
            /*keep a copy of the current substate */
            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
        }
    if(CanSM_PreFullCom_Substates == CANSM_PRE_FULLCOM_S_CC_STARTED)
        {
            /*Start the CAN controllers*/
            CanSM_StartCtrl(network);
            /*keep a copy of the current substate */
            CanSM_PreFullCom_Substates = CanSM_PreFullCom_Substates_en[network];
            /*Check the current state*/
            if(CanSM_PreFullCom_Substates== CANSM_PRE_FULLCOM_DEFAULT)
            {
                /*Reset the T_REPEAT_MAX counter*/
                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
                /*Update the state of Network for BswM*/
                CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

                /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
                BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

                /*Current mode is FULL_COM*/
                CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_FULLCOM;

                /* Reset Bus-Off Counter */
                CanSM_BusOff_Cntr_au8[network] = CANSM_ZERO;

                /* Start the Timer */
                CanSM_StartTimer(network);

                /* Change the BOR State */
                CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

                /* Change the Bus-Off Recovery Mode to Recovery enabled */
                CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_ENABLED;

                /*Update CanSM_BusSMMode_t_a_u8[] to CANSM_BSM_S_FULLCOM i.e COMM_FULL_COMMUNICATION*/
                CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

                for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                    {
                        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                        #if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
                        if(CanSM_Passive_b == TRUE)
                            {
                                /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                                (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_TX_OFFLINE_ACTIVE));
                            }
                        else
                            {
                                /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                                (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_ONLINE));
                            }
                            #else
                            /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_ONLINE));
                        #endif
                    }

                /*Notify to ComM about CanSM state Transition*/
                CanSM_reqComM_Mode_uo = COMM_FULL_COMMUNICATION;
                ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_reqComM_Mode_uo);

            }
        }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
/**
***************************************************************************************************
** Function Name        : CanSM_FULL2SILENT_COM
**
** Service ID           : None
**
** Description          : This function carries out all the  necessary tasks when there is a Network Mode Transition from
**                        FULL_COM to SILENT_COM. This is an Internal Function
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          :
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
FUNC(void, CANSM_CODE) CanSM_FULL2SILENT_COM(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*Local variabe to hold the BSWM mode*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

    /*Temporary pointer to CanSM_Network_pcst[]*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_APPL_DATA ) NetworkConf_ps;

    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;

    VAR(ComM_ModeType, AUTOMATIC) CanSM_reqComM_Mode_uo;

    /*Hold the address of the passed network*/
    NetworkConf_ps = &CanSM_Network_pcst[network];

    /* The BOR Mode is Disabled first, because if this Function is pre-empted by the CanSM_ControllerBusOff
       the change in the BOR Mode will not allow any Processing in the Function CanSM_ControllerBusOff */

    /* Change the BOR Mode  */
    CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_DISABLED;

    /* Change the BOR State */
    CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;

    /*Reset T_REPEAT_MAX counter*/
    CanSM_Num_Unsuccessful_ModeReq_au8[network]= CANSM_ZERO;


    /*Set the Current Mode of CAN State Machine */
    CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_SILENTCOM;

    /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_SILENTCOM i.e COMM_SILENT_COMMUNICATION*/
    CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_SILENTCOM;

    /*Notify BswM */
    CanSM_BswM_Mode_en = CANSM_BSWM_SILENT_COMMUNICATION;
    BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

    /* Loop for All the Controllers in the Network */
    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
    {
        CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
        /* set TX PDU to OFFLINE Mode */
        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_TX_OFFLINE));
    }

    /*Notify to ComM about CanSM state Transition*/
    CanSM_reqComM_Mode_uo = COMM_SILENT_COMMUNICATION ;
    ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo, &CanSM_reqComM_Mode_uo);

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
/**
***************************************************************************************************
** Function Name        : CanSM_SILENT2FULL_COM
**
** Service ID           : None
**
** Description          : This function carries out all the  necessary tasks when there is a Network Mode Transition from
**                        SILENT_COM to FULL_COM. This is an Internal Function
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          :
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
FUNC(void, CANSM_CODE) CanSM_SILENT2FULL_COM(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*Local variabe to hold the BSWM mode*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

    /*Temporary pointer to CanSM_Network_pcst[]*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_APPL_DATA ) NetworkConf_ps;

    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;

    VAR(ComM_ModeType, AUTOMATIC) CanSM_reqComM_Mode_uo;

    /*Hold the address of the passed network*/
    NetworkConf_ps = &CanSM_Network_pcst[network];


            for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_Network_pcst[network].SizeofController_u8 ;CanSM_Ctrl_index_u8++)
                {
                    CanSM_ControllerId_u8 = CanSM_Network_pcst[network].Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
                    #if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
                    if(CanSM_Passive_b == TRUE)
                        {
                            /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_TX_OFFLINE_ACTIVE));
                        }
                    else
                        {
                            /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                            (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_ONLINE));
                        }
                        #else
                        /*Return Value not checked, as this transition is not expected to return E_NOT_OK */
                        (void)(CanIf_SetPduMode(CanSM_ControllerId_u8,CANIF_SET_ONLINE));
                    #endif
                }
    /*Current mode is FULL_COM*/
    CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_FULLCOM;

    /* Reset Bus-Off Counter */
    CanSM_BusOff_Cntr_au8[network] = CANSM_ZERO;

    /* Start the Timer */
    CanSM_StartTimer(network);

    /* Change the BOR State */
    CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

    /* Change the Bus-Off Recovery Mode to Recovery enabled */
    CanSM_BORMode_au8[network] =  (uint8)CANSM_RECOVERY_ENABLED;

    /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_FULLCOM i.e COMM_FULL_COMMUNICATION*/
    CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

    /*Notify to ComM about CanSM state Transition*/
    CanSM_reqComM_Mode_uo = COMM_FULL_COMMUNICATION;
    ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_reqComM_Mode_uo);

    /*Update the state of Network for BswM*/
    CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;

    /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
    BswM_CanSM_CurrentState(NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_TxTimeoutException_StateMachine
**
** Service ID           : None
**
** Description          : This function carries out all the  necessary tasks for the Tx Timeout Exception state machine.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          :
**
** Input Parameters     : Channel
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TxTimeoutException_StateMachine(VAR(NetworkHandleType, AUTOMATIC) Channel)
{

    VAR(CanSM_TxTimeoutException_Substates_ten, AUTOMATIC) CanSM_TxTimeoutException_en;

    /*Make local copy CanSM_TxTimeoutexception_Substates_en[Channel]*/
    CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];

    /* Check If T_REPEAT_MAX counter reaches maximum value */
        if (CanSM_Num_Unsuccessful_ModeReq_au8[Channel] < CanSM_ModeRepeatReq_Max_u8)
        {
            switch(CanSM_TxTimeoutException_en)
            {
                case CANSM_TxTimeoutException_S_CC_STOPPED_WAIT :
                {

                    /*Check if a controller indication was received that all the CAN controllers are stopped*/
                    if(CanSM_Ctrl_ModeInd_ab[Channel] == TRUE)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                        /*Reset the controller mode indication flag for the network*/
                        CanSM_Ctrl_ModeInd_ab[Channel] = FALSE;

                        /*Move to next substate of the CANSM_TxTimeoutException_S_CC_STARTED */
                        CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STARTED;

                        /*Make local copy CanSM_TxTimeoutexception_Substates_en[Channel]*/
                        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[Channel] = CANSM_ZERO;
                   }
                    /*check if timeout has occurred and proceed accordingly.*/
                    else
                    {
                        if (CanSM_TimerConfig_ast[Channel].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {

                            /*Set the Timer to Elapsed Mode */
                            CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                            /*Move to previous substate ie CANSM_TxTimeoutException_S_CC_STOPPED*/
                            CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STOPPED;

                            /*Make local copy CanSM_TxTimeoutexception_Substates_en[Channel]*/
                            CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
                        }

                    }
                }
                break;

                case  CANSM_TxTimeoutException_S_CC_STARTED_WAIT:
                {

                    /*Check if a controller indication was received that all the CAN controllers are stopped*/
                    if(CanSM_Ctrl_ModeInd_ab[Channel] == TRUE)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                        /*Reset the controller mode indication flag for the network*/
                        CanSM_Ctrl_ModeInd_ab[Channel] = FALSE;

                        /*Move to next substate of the CANSM_TxTimeoutException_DEFAULT */
                        CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_DEFAULT;

                        /*Make local copy CanSM_TxTimeoutexception_Substates_en[Channel]*/
                        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[Channel] = CANSM_ZERO;

                        /* Change the BOR State */
                        CanSM_currBOR_State_en[Channel] = CANSM_S_NO_BUS_OFF;
                        /* Change the current network mode to FULL COM */
                        CanSM_CurrNw_Mode_en[Channel] = CANSM_BSM_S_FULLCOM;

                   }
                    /*check if timeout has occurred and proceed accordingly.*/
                    else
                    {
                        if (CanSM_TimerConfig_ast[Channel].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {

                            /*Set the Timer to Elapsed Mode */
                            CanSM_TimerConfig_ast[Channel].stTimer = CANSM_TIMER_ELAPSED;

                            /*Move to previous substate ie CANSM_TxTimeoutException_S_CC_STOPPED*/
                            CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STARTED;

                            /*Make local copy CanSM_TxTimeoutexception_Substates_en[Channel]*/
                            CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
                        }

                    }
                }
                break;
                default:
                /* Intentionally Empty */
                break;

            }/*end of switch*/
        }
        else
        {
            /*Reset the T_REPEAT_MAX counter*/
            CanSM_Num_Unsuccessful_ModeReq_au8[Channel] = CANSM_ZERO;
            /*Go to entry point with CANSM_TxTimeoutException_S_CC_STOPPED since T_REPEAT_MAX counter has exceeded.*/
            CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STOPPED;
            /*Make local copy CanSM_TxTimeoutexception_Substates_en[Channel]*/
            CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
            /*Report DET since T_REPEAT_MAX counter had exceeded*/
            CANSM_REPORT_ERROR(CanSM_TxTimeoutexception_Substates_en[Channel] == CANSM_TxTimeoutException_S_CC_STOPPED, (uint8)CANSM_MAINFUNCTION_SID, (uint8)CANSM_E_MODE_REQUEST_TIMEOUT)
       }

    /* Check if CanSM_TxTimeoutException_en Substate is equal to CANSM_TxTimeoutException_S_CC_STOPPED */
    if(CanSM_TxTimeoutException_en == CANSM_TxTimeoutException_S_CC_STOPPED)
    {
        /* Put all the CAN controllers of the intended network to stop mode */
        CanSM_StopCtrl(Channel);
        /*keep a copy of the current substate */
        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
    }
    /* Check if CanSM_TxTimeoutException_en Substate is equal to CANSM_TxTimeoutException_S_CC_STARTED */
    if(CanSM_TxTimeoutException_en == CANSM_TxTimeoutException_S_CC_STARTED)
    {
        /* Put all the CAN controllers of the intended network to start mode */
        CanSM_StartCtrl(Channel);
        /*keep a copy of the current substate */
        CanSM_TxTimeoutException_en = CanSM_TxTimeoutexception_Substates_en[Channel];
        if(CanSM_TxTimeoutException_en == CANSM_TxTimeoutException_DEFAULT)
            {
                /* Change the BOR State */
                CanSM_currBOR_State_en[Channel] = CANSM_S_NO_BUS_OFF;
                /* Change the current network mode to FULL COM */
                CanSM_CurrNw_Mode_en[Channel] = CANSM_BSM_S_FULLCOM;
            }
    }


}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

/**
***************************************************************************************************
** Function Name        : CanSM_SetBaudrate_StateMachine
**
** Service ID           : None
**
** Description          : This function takes care of executing the state machhine for the Baudrate Change.
**                        Both the wait and no wait states are implemented here.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          :
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/
#if ((CANSM_CHANGE_BAUDRATE_API == STD_ON) || (CANSM_SET_BAUDRATE_API == STD_ON))
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ChangeBR_Exit(VAR(NetworkHandleType, AUTOMATIC) network)
{
    /*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;

    /*Used in FOR loop to access CAN controllers of the corresponding network*/
    VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
    /*To hold the controller Id*/
    VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;

    /*Variable to track the status of BSWM*/
    VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;

    /*To track the ComM mode status*/
    VAR(ComM_ModeType, AUTOMATIC) CanSM_ComM_ModeType_uo;

    /*Hold the address of the configured network*/
    CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

    #if (CANSM_CHANGE_BAUDRATE_API == STD_ON)
    /* Initilalize CanSM_ChangeBaudRate_Value_au32 with an invalid value */
    CanSM_ChangeBaudRate_Value_au32[network] =0xFFFFFFFFu;
    #endif


    #if(CANSM_SET_BAUDRATE_API == STD_ON)
    /*Initilalize CanSM_BaudRateConfigID_Value_au16 with a default/invalid value*/
    CanSM_BaudRateConfigID_Value_au16[network] = 0xFFFFu;
    #endif
    /*If the recently requested network mode was FULLCOM or no request was made...*/
    if(CanSM_ReqComM_Mode_en[network]==COMM_FULL_COMMUNICATION)
    {
        /*Change the current network mode back to FULLCOM*/
        CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_FULLCOM;

        /* Start the Timer */
        CanSM_StartTimer(network);

        /*Change the BOR State */
        CanSM_currBOR_State_en[network] = CANSM_S_BUS_OFF_CHECK;

        /* Enable the BOR Mode  */
        CanSM_BORMode_au8[network] = (uint8)CANSM_RECOVERY_ENABLED;

        /*Update CanSM_BusSMMode_au8[] to CANSM_BSM_S_FULLCOM i.e COMM_FULL_COMMUNICATION*/
        CanSM_BusSMMode_au8[network] = (ComM_ModeType)CANSM_BSM_S_FULLCOM;

        /*Notify the BswM*/
        CanSM_BswM_Mode_en = CANSM_BSWM_FULL_COMMUNICATION;
        /*Notify BswM with CANSM_BSWM_NO_COMMUNICATION as part of E_PRE_NOCOM*/
        BswM_CanSM_CurrentState(CanSM_NetworkConf_ps->ComM_channelId_uo,CanSM_BswM_Mode_en);

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

        /*Notify to ComM about CanSM state Transition*/
        CanSM_ComM_ModeType_uo = COMM_FULL_COMMUNICATION;
        ComM_BusSM_ModeIndication(CanSM_Network_pcst[network].ComM_channelId_uo,&CanSM_ComM_ModeType_uo);
    }

    /*If the recently requested network mode was NOCOM...*/
    else if(CanSM_ReqComM_Mode_en[network]==COMM_NO_COMMUNICATION)
    {
        /*Change the current network mode to PRE_NO_COM, since NOCOM is via PRE_NO_COM*/
        CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

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

    /*If the recently requested network mode was SILENTCOM...*/
    else if(CanSM_ReqComM_Mode_en[network]==COMM_SILENT_COMMUNICATION)
    {
        /*Change the network mode to SILENTCOM*/
        CanSM_FULL2SILENT_COM(network);
    }

    else
    {
        /*Dummy*/
    }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

/**
***************************************************************************************************
** Function Name        : CanSM_WakeUpValidation_StateMachine
****
** Description          : This function shall handles the internal state machine for WakeUpValidation.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non Reentrant
**
** Input Parameters     : network
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : void

***************************************************************************************************
**/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"

FUNC(void, CANSM_CODE) CanSM_WakeUpValidation_StateMachine(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*To keep the track of CanSM_PreFullCom_Substates*/
    VAR(CanSM_WakeUpValidation_Substates_ten, CANSM_VAR) CanSM_WakeUpValidation_Substates;

    /*Make local copy CanSM_WakeUpValidation_Substates_en[network]*/
    CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

    /*If T_REPEAT_MAX counter has not exceeded*/
    if(CanSM_Num_Unsuccessful_ModeReq_au8[network] < CanSM_ModeRepeatReq_Max_u8)
        {
            switch(CanSM_WakeUpValidation_Substates)
            {
                case CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL_WAIT:
                {
                    /*Check if a transceiver indication was received...*/
                    if(CanSM_Trcv_ModeInd_ab[network]==TRUE)
                    {
                        /*Check if the transceiver is configured*/
                        if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
                            {
                                /*Reset the transceiver mode indication flag to FALSE only if transceiver is configured */
                                CanSM_Trcv_ModeInd_ab[network] = FALSE;
                            }

                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*move to next state*/
                        CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;

                        /*Make local copy CanSM_WakeUpValidation_Substates_en[network]*/
                        CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    }
                    else
                    {
                        /*check if timeout has occurred and proceed accordingly.*/
                        if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {
                            /*Set the Timer to Elapsed Mode */
                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                            /*Move to previous substate ie CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL*/
                            CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL;

                            /*keep a copy of the current substate */
                            CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
                        }
                    }
                }
                break;
            case CANSM_WAKEUP_VALIDATION_S_CC_STOPPED_WAIT:
                {
                    /*Check if a controller indication was received that all the CAN controllers are stopped*/
                    if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Reset the controller mode indication flag for the network*/
                        CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                        /*Move to next substate of the CANSM_WAKEUP_VALIDATION_S_CC_STARTED */
                        CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STARTED;

                        /*keep a copy of the current substate */
                        CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                   }

                    /*Check if timeout has occurred and so proceed accordingly*/
                    else
                    {
                        if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                        {
                            /*Set the Timer to Elapsed Mode */
                            CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                            /*Move to previous substate ie CANSM_WAKEUP_VALIDATION_S_CC_STOPPED*/
                            CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;

                            /*keep a copy of the current substate */
                            CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
                        }
                    }
                }
                break;
            case CANSM_WAKEUP_VALIDATION_S_CC_STARTED_WAIT:
            {
                /*Check if a controller indication was received that all the CAN controllers are stopped*/
                if(CanSM_Ctrl_ModeInd_ab[network] == TRUE)
                    {
                        CanSM_Ctrl_ModeInd_ab[network] = FALSE;

                        CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_DEFAULT;

                        /*Reset the CanSM_Wuvalidation_Start_ab */
                        CanSM_Wuvalidation_Start_ab[network] = FALSE;

                        /*keep a copy of the current substate */
                        CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];

                        /*Reset the T_REPEAT_MAX counter*/
                        CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                    }

                /*Check if timeout has occurred and so proceed accordingly*/
                else
                {
                    if(CanSM_TimerConfig_ast[network].cntTick_u16 >= CanSM_ModeRepeatReq_Time_u16)
                    {
                        /*Set the Timer to Elapsed Mode */
                        CanSM_TimerConfig_ast[network].stTimer = CANSM_TIMER_ELAPSED;

                        /*Move to previous substate ie CANSM_WAKEUP_VALIDATION_S_CC_STARTED*/
                        CanSM_WakeUpValidation_Substates_en[network]= CANSM_WAKEUP_VALIDATION_S_CC_STARTED;

                        /*keep a copy of the current substate */
                        CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
                    }
                }
            }
            break;
            default:
            /* Intentionally Empty */
            break;

        }
    }
    else
        {
        CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_DEFAULT;

        /*Reset the CanSM_Wuvalidation_Start_ab */
        CanSM_Wuvalidation_Start_ab[network] = FALSE;

           /*keep a copy of the current substate */
        CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
          /*Reset T_REPEAT_MAX counter*/
          CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;
          /*The present state of the network [during initialisation]*/
          CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
          /*Request for NO_COMM*/
          CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

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
    /*Check the first substate of PRE_NOCOM is CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL*/
    if(CanSM_WakeUpValidation_Substates == CANSM_WAKEUP_VALIDATION_S_TRCV_NORMAL)
        {
            if(CanSM_Network_pcst[network].Trcv_hndle_u8 == 255u)
                {
                    /*Tranceiver mode indication is considered to be received*/
                    CanSM_Trcv_ModeInd_ab[network] = TRUE;
                    /*If no CanSMTransceiverId is configured for a CAN Network, then the CanSM module shall bypass all specified
                    CanIf_SetTrcvMode  calls for the CAN Network and proceed in the different state transitions as if it has got the supposed
                    CanSM_TransceiverModeIndication already*/
                    CanSM_WakeUpValidation_Substates_en[network] = CANSM_WAKEUP_VALIDATION_S_CC_STOPPED;
                    /*keep a copy of the current substate */
                    CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
                }
                else
                {
                    /*Put the transceiver to Normal mode*/
                    /*Depending on the mode indication received / not received, the next substate can be CANSM_S_TRCV_STANDBY / CANSM_S_TRCV_NORMAL_WAIT*/
                    CanSM_NormalTrcv(network);
                    /*keep a copy of the current substate */
                    CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
                }
        }
    if(CanSM_WakeUpValidation_Substates == CANSM_WAKEUP_VALIDATION_S_CC_STOPPED)
        {
            /*Stop the CAN controllers*/
            CanSM_StopCtrl(network);
            /*keep a copy of the current substate */
            CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
        }
    if(CanSM_WakeUpValidation_Substates == CANSM_WAKEUP_VALIDATION_S_CC_STARTED)
        {
            /*Start the CAN controllers*/
            CanSM_StartCtrl(network);
            /*keep a copy of the current substate */
            CanSM_WakeUpValidation_Substates = CanSM_WakeUpValidation_Substates_en[network];
            /*Check the current state*/
            if(CanSM_WakeUpValidation_Substates== CANSM_WAKEUP_VALIDATION_DEFAULT)
            {
                /*Reset the T_REPEAT_MAX counter*/
                CanSM_Num_Unsuccessful_ModeReq_au8[network] = CANSM_ZERO;

                /*Reset the CanSM_Wuvalidation_Start_ab */
                CanSM_Wuvalidation_Start_ab[network] = FALSE;

            }
        }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"


