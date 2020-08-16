
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"
/**
***************************************************************************************************
** Function Name        : CanSM_RequestComMode
**
** Service ID           : 0x02
**
** Description          : This service shall change the communication mode of a CAN network to the requested one.
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant (only for different network handles)
**
** Input Parameters     : network: Handle of destined communication network for request
**                        ComM_Mode : Requested communication mode
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : Std_ReturnType : E_OK: Service accepted, E_NOT_OK: Service denied

***************************************************************************************************
**/
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComMode( VAR(NetworkHandleType, AUTOMATIC) network,VAR(ComM_ModeType, AUTOMATIC) ComM_Mode )
{
    /*To keep a track of return value*/
    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;
    /*To keep a track of current network mode*/
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;
    /*To keep a track of current BOR state */
    VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORState_en;

    #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
    /*To keep the track of change baudrate state*/
    VAR(CanSM_ChangeBR_Substates_ten, AUTOMATIC) CanSM_ChangeBR_State_en;
    #endif
    /*To keep the track of Tx Timeout Exception state*/
    VAR(CanSM_TxTimeoutException_Substates_ten, CANSM_VAR) CanSM_TxToutException_state_en;
    /*keep the return status as E_NOT_OK*/
    CanSM_FuncVal_uo = E_OK;

    /*Notify DET if the CanSM module is not initialized and return E_NOT_OK*/
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_REQUESTCOMMODE_SID),
                           ((uint8)CANSM_E_UNINIT))

    /* Get the CanSM network Index value corresponding to the ComM channel Id received */
    network = CanSM_GetHandle(network);

    /* Notify DET for Invalid network handle.*/
    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                           (uint8)CANSM_REQUESTCOMMODE_SID,
                           (uint8)CANSM_E_INVALID_NETWORK_HANDLE)

    /*Make a local copy of current network mode */
    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

    /* Get the Current BOR State only after the Mutex is accquired */
    CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];

    #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
    /*Get the current Change Baudrate state*/
    CanSM_ChangeBR_State_en = CanSM_ChangeBR_Substates_en[network];
    #endif

    /*Get the current Tx Timeout Exception state */
    CanSM_TxToutException_state_en = CanSM_TxTimeoutexception_Substates_en[network];

    /*When request to NO COM is made during FULL COM, the transition takes place via Pre_no_com*/
    if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM)&&(ComM_Mode == COMM_NO_COMMUNICATION )&&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
          #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
          (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
          #endif
          (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
         )
            {
               /* Transition to NO_COM */
                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION ;
                /*Update the current network state to Pre No Com*/
                CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;

            }

    /*When request to SILENT COM COM is made during FULL COM*/
    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM)&&
          (ComM_Mode == COMM_SILENT_COMMUNICATION )&&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
            #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
          (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
         )
            {
                /* Transition to COMM_SILENT_COMMUNICATION */
                CanSM_ReqComM_Mode_en[network] = COMM_SILENT_COMMUNICATION ;

            }
    /*When request to NO COM is made during SILENT COM*/
    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_SILENTCOM)&&
          (ComM_Mode == COMM_NO_COMMUNICATION )&&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
          (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
          (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
            #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
          (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
         )
            {
                /* Transition to COMM_NO_COMMUNICATION */
                CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION ;
                /*Update the current network state to Pre No Com*/
                CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
            }
    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en== CANSM_BSM_S_SILENTCOM)&&
            (ComM_Mode == COMM_FULL_COMMUNICATION )&&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
            #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
            (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
           )
                {
                    /* Transition to COMM_FULL_COMMUNICATION */
                    CanSM_ReqComM_Mode_en[network] = COMM_FULL_COMMUNICATION ;
                    /*Update the current network state to CANSM_BSM_S_PRE_FULLCOM*/
                    CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_FULLCOM;
                }
    else if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en== CANSM_BSM_S_NOCOM)&&
            (ComM_Mode == COMM_FULL_COMMUNICATION )&&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
            (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
            (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
            #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
            (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
           )
                {
                    /* Transition to COMM_FULL_COMMUNICATION */
                    CanSM_ReqComM_Mode_en[network] = COMM_FULL_COMMUNICATION ;
                    /*Update the current network state to CANSM_BSM_S_PRE_FULLCOM*/
                    CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_FULLCOM;
                }

            /*Store the request only if it is not in transitional state and also not in bus-off nd change baudrate and no Tx Time out Exception*/
    else if((CanSM_Network_Init_ab[network] == TRUE)&&(CanSM_CurrNwMode_en!=CANSM_BSM_S_PRE_FULLCOM) &&
             (CanSM_CurrNwMode_en!=CANSM_BSM_S_PRE_NOCOM)&&
             (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L1) &&
             (CanSM_CurrBORState_en!=CANSM_S_BUS_OFF_RECOVERY_L2) &&
             (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC) &&
             (CanSM_CurrBORState_en!=CANSM_S_RESTART_CC_WAIT)&&
            #if((CANSM_SET_BAUDRATE_API == STD_ON) || (CANSM_CHANGE_BAUDRATE_API == STD_ON))
            (CanSM_ChangeBR_State_en == CANSM_BR_DEFAULT)&&
            #endif
                         (CanSM_TxToutException_state_en==CANSM_TxTimeoutException_DEFAULT)
            )
                {
                    /*Store the mode request if no transition is happening*/
                    CanSM_ReqComM_Mode_en[network] = ComM_Mode ;
                }
    else if((CanSM_Network_Init_ab[network] == TRUE) && (CanSM_CurrNwMode_en==CANSM_BSM_WUVALIDATION) && (CanSM_WakeUpValidation_Substates_en[network] == CANSM_WAKEUP_VALIDATION_DEFAULT) &&
            (ComM_Mode == COMM_FULL_COMMUNICATION ))
    {
        /* Transition to COMM_FULL_COMMUNICATION */
        CanSM_ReqComM_Mode_en[network] = COMM_FULL_COMMUNICATION ;
        /*Update the current network state to CANSM_BSM_S_PRE_FULLCOM*/
        CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_FULLCOM;

    }
    else
        {
            /*Valid transition is not possible. Return E_NOT_OK*/
            CanSM_FuncVal_uo = E_NOT_OK;

            /*Notify DET when CanSM is waiting for a mode indication i.e if it is in PRE_NOCOM, PRE_FULLCOM or Bus-off Recovery.
             * DET cannot be reported if in CANSM_BSM_S_CHANGE_BAUDRATE since the recently requested mode must be considered.*/
            CANSM_REPORT_ERROR_NOK(CanSM_Init_ab == (boolean)CANSM_INITED,((uint8)CANSM_REQUESTCOMMODE_SID),(uint8)(CANSM_E_WAIT_MODE_INDICATION))

        }

    return (CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

