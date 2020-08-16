
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"
/**
***************************************************************************************************
** Function Name        : CanSM_SetEcuPassive
**
** Service ID           : 0x13
**
** Description          : This function can be used to set all CanSM channels of the ECU to a receive only mode.
**                        This mode will be kept either until it is set back, or the ECU is reset..
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Non-Reentrant
**
** Input Parameters     : CanSM_Passive- TRUE: set all CanSM channels to passive, i.e. receive only
**                                       FALSE: set all CanSM channels back to non-passive
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : Std_ReturnType- E_OK: Request accepted, E_NOT_OK: Request not accepted

***************************************************************************************************
**/

#if(CANSM_TX_OFFLINE_ACTIVE_SUPPORT == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetEcuPassive(VAR(boolean, AUTOMATIC) CanSM_Passive)
{
	/*Variable to hold the return value*/
	VAR(Std_ReturnType, AUTOMATIC) stFuncVal;

	/* Local variable to hold network index */
	VAR(uint8, AUTOMATIC) CanSM_NetworkIdx_u8;
	/*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
	/*To hold the controller Id*/
	VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8 = 0;
	/*Used in FOR loop to access CAN controllers of the corresponding network*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
	/*Assign the current network configuration*/
	CanSM_Network_pcst = CanSM_ConfigSet_pcst->CanSM_NetworkConf_pcst;

	stFuncVal = E_NOT_OK;

    CanSM_Passive_b =  CanSM_Passive;

	/*Notify DET if CanSM is not initialized and return E_NOT_OK*/
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab == (boolean)CANSM_UNINITED),((uint8)CANSM_ECUPASSIVE_SID),((uint8)CANSM_E_UNINIT))

	/* Loop through the networks */
	for(CanSM_NetworkIdx_u8 =0; CanSM_NetworkIdx_u8 < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; CanSM_NetworkIdx_u8++)
		{
			if(CanSM_Network_Init_ab[CanSM_NetworkIdx_u8] == TRUE)
				{
					/*Hold the address of the configured network*/
					CanSM_NetworkConf_ps = &CanSM_Network_pcst[CanSM_NetworkIdx_u8];
					/* Loop for All the Controllers in the network */
					for(CanSM_Ctrl_index_u8 =0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ; CanSM_Ctrl_index_u8++)
						{
							/*Store the CAN controller ID belonging to the network*/
							CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
							/*Check the input CanSM_Passive_b and execute accordingly for PDU mode*/
							if(CanSM_Passive_b == TRUE)
								{
									/*Put the PDU mode to CANIF_SET_TX_OFFLINE_ACTIVE */
									(void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_SET_TX_OFFLINE_ACTIVE));
								}
							else
								{
									/*Put the PDU mode to CANIF_SET_ONLINE */
									(void)(CanIf_SetPduMode(CanSM_ControllerId_u8, CANIF_SET_ONLINE));
								}
								/*Update the return value*/
							stFuncVal = E_OK;
						}
				}
			else
				{
					break;
				}
		}

    return stFuncVal;
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
