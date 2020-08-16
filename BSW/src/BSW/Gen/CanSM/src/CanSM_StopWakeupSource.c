
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"


/**
***************************************************************************************************
** Function Name        : CanSM_StopWakeupSource
**
** Service ID           : 0x12
**
** Description          : This function shall be called by EcuM when a wakeup source shall be stopped.
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
** Return parameter     : Std_ReturnType

***************************************************************************************************
**/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_StopWakeupSource(VAR(NetworkHandleType, AUTOMATIC) network)
{
	/*To keep a track of return value*/
	VAR(Std_ReturnType, AUTOMATIC) stFuncVal;
	/*To keep a track of current network mode*/
	VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CanSM_CurrNwMode_en;

    stFuncVal = E_NOT_OK;

	/*Notify DET if CanSM module is not initialized and return E_NOT_OK*/
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),
                           ((uint8)CANSM_STOPWAKEUPVALIDATION_SID),
                           ((uint8)CANSM_E_UNINIT))

	/* Get the CanSM network Index value corresponding to the ComM channel Id received */
    network = CanSM_GetHandle(network);

	/* Notify DET for Invalid network handle.*/
    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                           (uint8)CANSM_STOPWAKEUPVALIDATION_SID,
                           (uint8)CANSM_E_INVALID_NETWORK_HANDLE)

	CanSM_CurrNwMode_en = CanSM_CurrNw_Mode_en[network];

	/*Check if the network is initialised and current network is CANSM_BSM_WUVALIDATION */
    if(( CanSM_CurrNwMode_en == CANSM_BSM_WUVALIDATION) && (CanSM_Network_Init_ab[network] == TRUE))
		{
			stFuncVal = E_OK;
			/*Update the current network mode to CANSM_BSM_S_PRE_NOCOM*/
			CanSM_CurrNw_Mode_en[network] = CANSM_BSM_S_PRE_NOCOM;
			/*Request for NO_COMM*/
			CanSM_ReqComM_Mode_en[network] = COMM_NO_COMMUNICATION;

			/*When transceiver is configured, also check if PN is supported*/
	if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].Trcv_hndle_u8 != 255)
		{
			#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
			if(CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst[network].TrcvPnConfig_b == TRUE) /*Pn checking includes that transceiver is also configured */
				{
					/*Make direct transition to CANSM_PN_S_CLEAR_WUF*/
					CanSM_PreNoCom_Substates_en[network] = CANSM_S_PN_CLEAR_WUF;
				}
			else
				{
					/*Make direct transition to CANSM_S_CC_STOPPED*/
					CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
				}
			#else
			/*Make direct transition to CANSM_S_CC_STOPPED*/
			CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
			#endif
		}
	else
		{
			/*Make direct transition to CANSM_S_CC_STOPPED*/
			CanSM_PreNoCom_Substates_en[network] = CANSM_S_CC_STOPPED;
		}
	}

    return stFuncVal;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
