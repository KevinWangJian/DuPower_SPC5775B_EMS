

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 *******************************************************************************
 * Dcm_DslDsd_ConfirmRespPend : This function is called from DSD after getting 
 *                              confirmation for the triggered force response
 *                               pending from the service.
 *
 * \param           dataSid_u8: Service Identifier for which the confirmation 
 *								is received
 *                  status_u8: status of the transmitted response pending
 *
 * \retval          None
 * \seealso
 *
 *******************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_DslDsdConfirmRespPend(
	VAR(uint8,AUTOMATIC) dataSid_u8,
	VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status_u8
											  )
{
	#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
	if(status_u8 == DCM_RES_NEG_OK)
	{
		/* Waiting for confirm results for the triggered response pending? */
		if(Dcm_BootLoaderState_en == DCM_BOOT_WAIT)
		{
			if(Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE)
			{
				/* Move the state to Store Protocol Information */
				Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMREQ;
			}
			else if(Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE)
			{
				/* Move the state to Store Protocol Information */
				Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMRESP;
			}
			else
			{
				/* Move the state to Store Protocol Information */
				Dcm_BootLoaderState_en = DCM_BOOT_STORE_WARMINIT;
			}
		}
		else if(Dcm_BootLoaderState_en ==DCM_BOOT_WAIT_FOR_RESET)
		{
		    if((Dcm_ProgConditions_st.StoreType == DCM_WARMREQUEST_TYPE)||
					(Dcm_ProgConditions_st.StoreType == DCM_WARMRESPONSE_TYPE))
		    {
                /* Move the state to Store Protocol Information */
                Dcm_BootLoaderState_en = DCM_BOOT_PERFORM_RESET;
		    }
		}
		else
		{
		    /* Do nothing */
		}
	}
	else
	{   /* Boot Loader is activated */
		if((Dcm_BootLoaderState_en == DCM_BOOT_WAIT) || 
							(Dcm_BootLoaderState_en ==DCM_BOOT_WAIT_FOR_RESET))
		{
			/* Reset Boot loader state */
			Dcm_BootLoaderState_en = DCM_BOOT_ERROR;
		}
	}
	(void)dataSid_u8;
	#else
	(void)dataSid_u8;
	(void)status_u8;
	#endif
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

