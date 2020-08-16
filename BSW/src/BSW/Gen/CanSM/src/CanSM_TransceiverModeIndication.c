
/*
 ***************************************************************************************************
 * Includes
 ***************************************************************************************************
 */
#include "CanSM_Priv.h"

/***************************************************************************************************
** Function Name        : CanSM_TransceiverModeIndication
**
** Service ID           : 0x09
**
** Description          : This callback shall notify the CanSM module about a CAN transceiver mode change.
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Reentrant for different CAN Transceivers
**
** Input Parameters     : TransceiverId - CAN transceiver, whose mode has changed
**                        TransceiverMode- Notified CAN transceiver mode
**
** InOut parameter      : None
**
** Output Parameters    : None
**
** Return parameter     : None

***************************************************************************************************/

#define CANSM_START_SEC_CODE
#include "CanSM_MemMap.h"
FUNC(void, CANSM_CODE) CanSM_TransceiverModeIndication(VAR(uint8, AUTOMATIC) TransceiverId,VAR(CanTrcv_TrcvModeType,AUTOMATIC) TransceiverMode)
{

    /*Variable to hold the network index for the given controller*/
	VAR(uint8_least, AUTOMATIC)  network_indx_uo;

	/*Variable to keep track if the TransceiverId is valid */
    VAR(boolean, AUTOMATIC)  CanSM_TrcvConfigd_b;

    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)
    /*Variable to hold current network mode*/
    VAR(CanSM_NetworkModeStateType_ten, AUTOMATIC) CurNwMode_Temp_uo;
    #endif

    /*Initialise the flag used to keep track if the TransceiverId is valid*/
	CanSM_TrcvConfigd_b = FALSE;

	/* This input parameter is not used in the api*/
	(void)TransceiverMode;

    /*Report a DET if the module is not initialised*/
    CANSM_REPORT_ERROR((CanSM_Init_ab == (boolean)CANSM_UNINITED ),
                           ((uint8)CANSM_TRCVMODEINDICATION_SID),
                           ((uint8)CANSM_E_UNINIT)
                          )

    /* Loop through the networks to which the transceiver belongs to, and update the CanSM_Trcv_ModeInd_ab[] */
	for(network_indx_uo =0; network_indx_uo < CanSM_ConfigSet_pcst->CanSM_SizeOfCanSMNetworks_u8 ; network_indx_uo++)
        {
            /*Check if the 'TransceiverId' matches the transceiver's id of a network*/
            if(CanSM_Network_pcst[network_indx_uo].Trcv_hndle_u8==TransceiverId)
                {
                    #if (CANSM_DEV_ERROR_DETECT != STD_OFF)
                    /*Make local copy of Current Network Mode*/
                    CurNwMode_Temp_uo = CanSM_CurrNw_Mode_en[network_indx_uo];
                    #endif

                    /*Notify DET if CanSM network is not initialized.*/
                    CANSM_REPORT_ERROR((CANSM_BSM_S_NOT_INITIALIZED == CurNwMode_Temp_uo),
                                       ((uint8)CANSM_TRCVMODEINDICATION_SID),
                                       ((uint8)CANSM_E_UNINIT))

                    /*Set the Transceiver Mode Indication of the network to TRUE*/
                    CanSM_Trcv_ModeInd_ab[network_indx_uo] = TRUE;

                    CanSM_TrcvConfigd_b = TRUE;
                    break;
                }
        }

    /*If the TransceiverId was not configured for any of the networks, then report to DET*/
    if(CanSM_TrcvConfigd_b == FALSE)
    {
        /* Notify DET for Invalid Transceiver ID.
         * Condition is TRUE, since the validity for the TransceiverId is checked in the preceding 'for' loop */
        CANSM_REPORT_ERROR(CanSM_Init_ab == (boolean)CANSM_INITED,
                           (uint8)CANSM_TRCVMODEINDICATION_SID,
                           (uint8)CANSM_E_PARAM_TRANSCEIVER
                           )

    }
}
#define CANSM_STOP_SEC_CODE
#include "CanSM_MemMap.h"
