
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"

/***************************************************************************************************
** Function Name        : CanSM_ConfirmPnAvailability
**
** Service ID           : 0x06
**
** Description          : This callback function indicates that the transceiver is running in PN communication mode.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different CAN Transceivers
**
** Input Parameters     : TransceiverId - CAN transceiver, which was checked for PN availability
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/

#if(CANSM_PN_SUPPORT_CONFIGD == STD_ON)
#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_ConfirmPnAvailability(VAR(uint8, AUTOMATIC) TransceiverId)
{

    /*Counter variable*/
	VAR(uint8_least, AUTOMATIC) network_indx_uo;
    VAR(boolean, AUTOMATIC) CanSM_TrcvConfigd_b;
	VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurrNwMode_Temp_uo;
	VAR(uint8, AUTOMATIC) CanSM_networkHandle_u8;

    /*Initialise the flag used to keep track if there is TransceiverId is valid one*/
	CanSM_TrcvConfigd_b = FALSE;

	/*Notify DET if CanSM is not initialized.*/
    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED),((uint8)CANSM_CONFIRMPNAVAILABILITY_SID),((uint8)CANSM_E_UNINIT))

   /* Loop through the networks to find the corresponding network for the 'Transceiver' */
	for(network_indx_uo =0; network_indx_uo < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; network_indx_uo++)
    {
	    CurrNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_uo];
		/*If the input 'TransceiverId' matches the transceiver's id of a network*/
        if(CanSM_Network_pcst[network_indx_uo].Trcv_hndle_u8 == TransceiverId)
        {
            /*Notify DET if CanSM is not initialized.
             * Cannot be checked for CanSM_stInit_a[] since in case of PRE_NOCOM, the network is
             * still considered to be uninitialised but mode indications are required to proceed*/
            CANSM_REPORT_ERROR((CANSM_BSM_S_NOT_INITIALIZED == CurrNwMode_Temp_uo),
                               ((uint8)CANSM_CONFIRMPNAVAILABILITY_SID),
                               ((uint8)CANSM_E_UNINIT)
                               )

        CanSM_TrcvConfigd_b = TRUE;

            /*Get the network handle*/
            CanSM_networkHandle_u8 = CanSM_Network_pcst[network_indx_uo].ComM_channelId_uo;

            /*Inform CanNm about PN availability*/
            CanNm_ConfirmPnAvailability((NetworkHandleType)CanSM_networkHandle_u8);

            break;
        }

    }

    if(CanSM_TrcvConfigd_b == FALSE)
    {
        /*Report to DET for invalid transceiver Id*/
        CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,(uint8)CANSM_CONFIRMPNAVAILABILITY_SID, (uint8)CANSM_E_PARAM_TRANSCEIVER)

    }

}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
#endif
