
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"

/***************************************************************************************************
** Function Name        : CanSM_CheckBaudrate
**
** Service ID           : 0x0c
**
** Description          : This service shall check, if a certain baudrate is supported by the configured CAN controllers
**                        of a certain CAN network.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Rentrant
**
** Input Parameters     : network- Handle of the addressed CAN network to check if a baudrate is supported
**                        Baudrate - Baudrate to check in kbps.
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : E_OK: Baudrate supported by all configured CAN controllers of the network
**                        E_NOT_OK: Baudrate not supported / invalid network

***************************************************************************************************/
#if (CANSM_CHANGE_BAUDRATE_API == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(Std_ReturnType, CANSM_CODE) CanSM_CheckBaudrate(VAR(NetworkHandleType, AUTOMATIC) network, CONST(uint32,AUTOMATIC) Baudrate)
{
     /*To hold the Return value*/
	VAR(Std_ReturnType, AUTOMATIC) CanSM_FuncVal_uo;
	/*Temporary pointer to hold the adress of configured network*/
    P2CONST(CanSM_NetworkConf_tst, AUTOMATIC, CANSM_CONST) CanSM_NetworkConf_ps;
	/*To hold the controller Id*/
	VAR(uint8, AUTOMATIC) CanSM_ControllerId_u8;
	/*Used in FOR loop to access CAN controllers of the corresponding network*/
	VAR(uint8, AUTOMATIC) CanSM_Ctrl_index_u8;
	CanSM_FuncVal_uo = E_NOT_OK;

	/*Notify DET if the CanSM module is not initialized and return E_NOT_OK*/
    CANSM_REPORT_ERROR_NOK((CanSM_Init_ab ==(boolean)CANSM_UNINITED),
                           ((uint8)CANSM_CHECKBAUDRATE_SID),
                           ((uint8)CANSM_E_UNINIT))

	/* Get the CanSM Network Index value corresponding to the ComM channel Id received */
    network = CanSM_GetHandle(network);

	/* Notify DET for Invalid network handle.*/
    CANSM_REPORT_ERROR_NOK(((uint8)network >= (CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8)),
                           (uint8)CANSM_CHECKBAUDRATE_SID,
                           (uint8)CANSM_E_INVALID_NETWORK_HANDLE)

	/*To get the address of the intended network*/
	CanSM_NetworkConf_ps = &CanSM_Network_pcst[network];

    /* Loop for All the Controllers in the Network */
    for(CanSM_Ctrl_index_u8 = 0; CanSM_Ctrl_index_u8 < CanSM_NetworkConf_ps->SizeofController_u8 ;CanSM_Ctrl_index_u8++)
    {
        /*Store the CAN controller ID belonging to the network*/
		CanSM_ControllerId_u8 = CanSM_NetworkConf_ps->Cntrl_startidx_pu8[CanSM_Ctrl_index_u8];
        /*Check if the baud rate is configured for the particular CanController(Node)
         * Also there must be no pending baudrate change request*/
        if(E_OK == CanIf_CheckBaudrate(CanSM_ControllerId_u8,Baudrate))
			{
            CanSM_FuncVal_uo = E_OK;
			}
        else
			{
            CanSM_FuncVal_uo = E_NOT_OK;
				break;
			}

    }

   	/*Return E_NOT_OK if the intended CanSM network is not initialised*/
    if(CanSM_Network_Init_ab[network] == TRUE)
		{
			/*Store the baudrate if NO baudrate change is already in progress*/
			/*If a baudrate change is already in progress, then irrespective of the value of 'stFuncVal',
			* just return the appropriate value without making any changes to CanSM_CheckBR_Status_ab[] and  CanSM_ChangeBaudRate_Value_au32[]*/
			if((CanSM_CurrNw_Mode_en[network] != CANSM_BSM_S_CHANGE_BAUDRATE))
				{
					if(CanSM_FuncVal_uo == E_OK)
						{
							/*Allow Baudrate change*/
							CanSM_CheckBR_Status_ab[network] = TRUE;
							/*Store baudrate value*/
							CanSM_ChangeBaudRate_Value_au32[network] = Baudrate;
						}

					else
						{
							/*Reset the flag*/
							CanSM_CheckBR_Status_ab[network] = FALSE;
							/*Store the default baudrate value*/
							CanSM_ChangeBaudRate_Value_au32[network] = 0xFFFFFFFFu;
						}
				}
		}
	else
		{
	        CanSM_FuncVal_uo = E_NOT_OK;
		}
    return (CanSM_FuncVal_uo);
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif

