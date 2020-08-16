
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"
/**
***************************************************************************************************
** Function Name        : CanSM_ChangeBaudrate
**
** Service ID           : 0x0e
**
** Description          : This service shall start an asynchronous process to change the baudrate for
**                        the configured CAN controllers of a certain CAN network
**
** Sync/Async           : Asynchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : network - index of the Network Configuration structure
**                        Baudrate - BaudRate in bps.
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : E_OK/E_NOT_OK

***************************************************************************************************/
#if (CANSM_CHANGE_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_ChangeBaudrate(VAR(NetworkHandleType, AUTOMATIC) network,CONST(uint32,AUTOMATIC) Baudrate)
{
    /*To keep a track of Return value*/
    VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;
    /*To keep a track of the BSWM mode*/
	VAR(CanSM_BswMCurrentStateType, AUTOMATIC) CanSM_BswM_Mode_en;
	/*To keep a track of requested baudrate value */
    VAR(uint32, AUTOMATIC) CanSM_ReqBaudRateVal_u32;
	/*To keep a track of Check baudrate status  */
    VAR(boolean, AUTOMATIC) CanSM_CheckBRStatus_b;
	/*To keep a track of current network mode */
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;
	/*To keep a track of current BOR state */
    VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORState_en;

    CanSM_FuncVal_uo = E_NOT_OK;

	/*Notify DET if CanSM is not initialized and return E_NOT_OK*/
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_CHANGEBAUDRATE_SID),
                           ((uint8)CANSM_E_UNINIT))

    /*Get the CanSM network Index value corresponding to the ComM channel Id received */
    network = CanSM_GetHandle(network);

    /*Notify DET if network handle is invalid and return E_NOT_OK*/
    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                            ((uint8)CANSM_CHANGEBAUDRATE_SID),
                            ((uint8)CANSM_E_INVALID_NETWORK_HANDLE))

	/*Make local copy of CanSM_ChangeBaudRate_Value_au32[network](This value was updated in CanSM_CheckBaudrate()), CanSM_CheckBR_Status_ab[network]*/
	CanSM_ReqBaudRateVal_u32 = CanSM_ChangeBaudRate_Value_au32[network];
	CanSM_CheckBRStatus_b = CanSM_CheckBR_Status_ab[network];

    /*Notify DET if
     *  - CanSM_CheckBaudrate() was not called before the call of CanSM_ChangeBaudrate() or
     *  - CanSM_CheckBaudrate() returned E_NOT_OK
     *  - Invalid baudrate is requested or baudrate requested is other than the one for which CanSM_CheckBaudrate() returned E_OK*/
    CANSM_REPORT_ERROR_NOK(((CanSM_ReqBaudRateVal_u32 == (uint32)0xFFFFFFFFu) || (CanSM_CheckBRStatus_b==FALSE)||(CanSM_ReqBaudRateVal_u32!= Baudrate)),
                            ((uint8)CANSM_CHANGEBAUDRATE_SID),
                            ((uint8)CANSM_E_PARAM_INVALID_BAUDRATE))


	/*Make a local copy of current network mode and current BOR state for the network*/
    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];
    CanSM_CurrBORState_en = CanSM_currBOR_State_en[network];

    /*Accept the change only if network is initialised and network is in CANSM_BSM_S_FULLCOM and BOR mode is CANSM_S_NO_BUS_OFF*/
    if((CanSM_Network_Init_ab[network] == TRUE)&& (CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM) &&
       (CanSM_CurrBORState_en==CANSM_S_NO_BUS_OFF)&&(CanSM_CheckBRStatus_b == TRUE)&&(CanSM_ReqBaudRateVal_u32 == Baudrate))
        {
            /*Return E_OK*/
            CanSM_FuncVal_uo = E_OK;

            /*Set current network mode to CANSM_BSM_S_CHANGE_BAUDRATE*/
            CanSM_CurrNw_Mode_en[network]=CANSM_BSM_S_CHANGE_BAUDRATE;

            /*Disable the bus off recovery mode during baudrate change*/
            CanSM_BORMode_au8[network] = (uint8)CANSM_RECOVERY_DISABLED;

            /*Change the Bus off recovery state to IDLE*/
            CanSM_currBOR_State_en[network] = CANSM_BOR_IDLE;

            /*First substate in Change Baudrate main state*/
            CanSM_ChangeBR_Substates_en[network] = CANSM_BR_S_CC_STOPPED;

            /*Notify BswM about the baudrate change*/
             CanSM_BswM_Mode_en = CANSM_BSWM_CHANGE_BAUDRATE;

             /* Give notification to the BswM about the current mode*/
             BswM_CanSM_CurrentState(CanSM_Network_pcst[network].ComM_channelId_uo,CanSM_BswM_Mode_en);
        }
    return (CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif


