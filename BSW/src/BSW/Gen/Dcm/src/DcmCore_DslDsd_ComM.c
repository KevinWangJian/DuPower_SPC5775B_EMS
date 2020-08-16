


#include "DcmCore_DslDsd_Inf.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **********************************************************************************************************************
 * Dcm_ComM_FullComModeEntered - All kind of transmissions shall be enabled immediately. This means that
 * the ResponseOnEvent and PeriodicId. It will be a dummy function in boot as ComM is not available in boot
 * \param           NetworkId
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **********************************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ComM_FullComModeEntered(VAR(uint8, AUTOMATIC) NetworkId)
{
	VAR(uint8,AUTOMATIC)idxNetwork_u8;
	/*  Communication mode of the corresponding to  network is set to FULL Communication mode */
	for(idxNetwork_u8 = 0;idxNetwork_u8<DCM_NUM_COMM_CHANNEL;idxNetwork_u8++)
	{
		if(Dcm_active_commode_e[idxNetwork_u8].ComMChannelId == NetworkId)
		{
			break;
		}
	}
	if (idxNetwork_u8<DCM_NUM_COMM_CHANNEL)
	{
		Dcm_active_commode_e[idxNetwork_u8].ComMState= DCM_DSLD_FULL_COM_MODE;

	}
}




/**
 **************************************************************************************************
 * All kind of transmissions (receive and transmit) shall be stopped . This means that the ResponseOnEvent
 * and PeriodicId and also the transmission of the normal communication (PduR_DcmTransmit) shall be disabled.
 * It will be a dummy function in boot as ComM is not available in boot
 * \param           NetworkId
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ComM_NoComModeEntered(VAR(uint8, AUTOMATIC) NetworkId)
{
	VAR(uint8,AUTOMATIC)idxNetwork_u8;
	/*  Communication mode of the corresponding to  network is set to NO Communication mode */
	for(idxNetwork_u8 = 0;idxNetwork_u8<DCM_NUM_COMM_CHANNEL;idxNetwork_u8++)
	{
		if(Dcm_active_commode_e[idxNetwork_u8].ComMChannelId == NetworkId)
		{
			break;
		}
	}
	if (idxNetwork_u8<DCM_NUM_COMM_CHANNEL)
	{
		Dcm_active_commode_e[idxNetwork_u8].ComMState = DCM_DSLD_NO_COM_MODE;
	}
}




/**
 **************************************************************************************************
 * Dcm_ComM_SilentComModeEntered: All outgoing transmissions shall be stopped immediately. This means that the
 * ResponseOnEvent and PeriodicId and also the transmission of the normal communication (PduR_DcmTransmit)
 * shall be disabled.
 * It will be a dummy function in boot as ComM is not available in boot
 * \param           NetworkId
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ComM_SilentComModeEntered(VAR(uint8, AUTOMATIC) NetworkId)
{
	/*  Communication mode of the corresponding to  network is set to silent  Communication mode */
	VAR(uint8,AUTOMATIC)idxNetwork_u8;
	for(idxNetwork_u8 = 0;idxNetwork_u8<DCM_NUM_COMM_CHANNEL;idxNetwork_u8++)
	{
		if(Dcm_active_commode_e[idxNetwork_u8].ComMChannelId == NetworkId)
		{
			break;
		}
	}
	if (idxNetwork_u8<DCM_NUM_COMM_CHANNEL)
	{
		Dcm_active_commode_e[idxNetwork_u8].ComMState = DCM_DSLD_SILENT_COM_MODE;
	}
}

/*
***********************************************************************************************************
*  Dcm_SetActiveDiagnostic: The call of this function allows to activate and deactivate the call of ComM_DCM_ActiveDiagnostic() function
*  \param    dataactive_b:  True Dcm will call ComM_DCM_ActiveDiagnostic() \n
*                           False Dcm shall not call ComM_DCM_ActiveDiagnostic()
*  \retval   E_OK : this value is always returned.
*  \seealso
*************************************************************************************************************
*/

FUNC(Std_ReturnType,DCM_CODE) Dcm_SetActiveDiagnostic(VAR(boolean, AUTOMATIC) dataactive_b)
{
    /* Multicore: No lock necessary as its an atomic operation .
     * Also, the application has to take care of calling Dcm_SetActiveDiagnostic() before Dcm calls CheckActiveDiagnostics from RxIndication. */
    /*Check if the data active parameter is set to True to call ComM_DCM_ActiveDiagnostic()*/
   if(dataactive_b != FALSE)
   {
	   Dcm_ActiveDiagnosticState_en = DCM_COMM_ACTIVE;
   }
   else
   {
	   Dcm_ActiveDiagnosticState_en = DCM_COMM_NOT_ACTIVE;
   }
   return(E_OK);
}

/*
***********************************************************************************************************
*  Dcm_CheckActiveDiagnosticStatus: The function checks whether ComM_DCM_ActiveDiagnostic()function needs to be called or not
*  \param    dataNetworkId:  Communication channel network id
*  \retval
*  \seealso
*************************************************************************************************************
*/
FUNC(void,DCM_CODE) Dcm_CheckActiveDiagnosticStatus(VAR(uint8,AUTOMATIC) dataNetworkId)
{
	/* Check the diagnostic state is active, then call the ComM_DCM_ActiveDiagnostic*/
	if(Dcm_ActiveDiagnosticState_en == DCM_COMM_ACTIVE)
	{
		ComM_DCM_ActiveDiagnostic(dataNetworkId);
	}
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


