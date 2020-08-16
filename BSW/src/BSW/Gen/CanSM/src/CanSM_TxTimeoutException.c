
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"

/**
***************************************************************************************************
** Function Name        : CanSM_TxTimeoutException
**
** Service ID           : 0x0b
**
** Description          : This function shall notify the CanSM module, that the CanNm has detected for the affected
**                        partial CAN network a tx timeout exception, which shall be recovered within the respective
**                        network state machine of the CanSM module.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant
**
** Input Parameters     : Channel-Affected CAN network
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
FUNC(void, CANSM_CODE) CanSM_TxTimeoutException(VAR(NetworkHandleType, AUTOMATIC) Channel)
{
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;

    VAR(CanSM_BusOffRecoveryStateType_ten, AUTOMATIC) CanSM_CurrBORMode_en;

	/*Notify DET if CanSM is not initialized and return*/
    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_TXTIMEOUTEXCEPTION_SID),
                           ((uint8)CANSM_E_UNINIT))

    /*Get the CanSM network Index value corresponding to the ComM channel Id received */
    Channel = CanSM_GetHandle(Channel);

    /*Notify DET if network handle is invalid and return*/
    CANSM_REPORT_ERROR(((uint8)Channel >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                            ((uint8)CANSM_TXTIMEOUTEXCEPTION_SID),
                            ((uint8)CANSM_E_INVALID_NETWORK_HANDLE))

    /*Make a local copy of current network mode and current BOR state for the network*/
    CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[Channel];
    CanSM_CurrBORMode_en = CanSM_currBOR_State_en[Channel];

    /*Accept the change only if module is initialised and network is in CANSM_BSM_S_FULLCOM and BOR mode is CANSM_S_NO_BUS_OFF*/
    if((CanSM_CurrNwMode_en==CANSM_BSM_S_FULLCOM) &&(CanSM_CurrBORMode_en==CANSM_S_NO_BUS_OFF))
    {
        CanSM_CurrNw_Mode_en[Channel] = CANSM_BSM_S_TX_TIMEOUT_EXCEPTION;
		/*First substate for the TxTimeoutException state machine is CANSM_TxTimeoutException_S_CC_STOPPED*/
		CanSM_TxTimeoutexception_Substates_en[Channel] = CANSM_TxTimeoutException_S_CC_STOPPED;
    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"

