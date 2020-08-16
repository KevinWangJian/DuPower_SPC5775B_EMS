

#include "DcmCore_DslDsd_Inf.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/*
***********************************************************************************************************
*  Dcm_DsldSetsessionTiming
*  Function to set the new timings of sessions (this function is called by the DSC service).
*  Inputs:   None
*  Output:   None
*  Return:   None
***********************************************************************************************************/
FUNC(void,DCM_CODE) Dcm_DsldSetsessionTiming(
                                               VAR(uint32, AUTOMATIC) nrP2StarMax_u32,
                                               VAR(uint32, AUTOMATIC) nrP2Max_u32
                                             )
{
    /* Lock required here to maintain consistency between P2Max, P2StarMax */
    SchM_Enter_Dcm_DsldTimer_NoNest();
#if(DCM_CFG_KWP_ENABLED == DCM_CFG_OFF)
    /* set the P2 max and P2 star max timings of new session */
    Dcm_DsldTimer_st.dataTimeoutP2max_u32 = nrP2Max_u32;
    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = nrP2StarMax_u32;
#else
    /*Check if the KWP type return value is FALSE*/
   if(DCM_IS_KWPPROT_ACTIVE() == FALSE)
    {
      /* set the P2 max and P2 star max timings of new session */
      Dcm_DsldTimer_st.dataTimeoutP2max_u32 = nrP2Max_u32;
      Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = nrP2StarMax_u32;
    }
#endif
   SchM_Exit_Dcm_DsldTimer_NoNest();
}



/**
 **************************************************************************************************
 * Dcm_DsldGetActiveSecurityMask_u32 : API to get the active security mask
 * \param           None
 *
 *
 * \retval          active security mask
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSecurityMask_u32 (void)
{
    return (uint32)(0x01uL<<Dcm_DsldGlobal_st.idxActiveSecurity_u8);
}



/**
 **************************************************************************************************
 * Dcm_DsldGetActiveSessionMask_u32 : API to get the active session mask
 * \param           None
 *
 *
 * \retval          active session mask
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSessionMask_u32 (void)
{
    return (uint32)(0x01uL<<Dcm_DsldGlobal_st.idxActiveSession_u8);
}



/**
 **************************************************************************************************
 * Dcm_ForceRespPend : API used to trigger wait pend response by the Service
 *
 * \param           None
 *
 *
 * \retval          Std_ReturnType
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_ForceRespPend(void)
{
    VAR(Std_ReturnType,AUTOMATIC) dataRetValue_u8;

    dataRetValue_u8 = E_NOT_OK;
    /*Do not Proceed further if the call is triggered by ROE/RDPI ,or if the call is from application and none of the Dcm service is active */
    if((Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_ROE_SOURCE) && (Dcm_DsldMsgContext_st.msgAddInfo.sourceofRequest != DCM_RDPI_SOURCE) && (DSD_CALL_SERVICE  == Dcm_DsldGlobal_st.stDsdState_en))
    {
        /* If DCM is already sending response pend then this API returns E_NOT_OK */

        if(Dcm_DsldTransmit_st.flgApplWaitPend_b == FALSE)
        {
            /* This application triggered wait pend */

            Dcm_DsldTransmit_st.flgApplWaitPend_b = TRUE;

            /* no need to frame the response. It is done in separate function */
            Dcm_DsldTransmit_st.adrTxBuffer_tpu8 = NULL_PTR;

            /* while framing the response proper length info is filled */
            Dcm_DsldTransmit_st.dataTxDataLength_u32 = 0x00;

            /* trigger the Tx in DSL */
            Dcm_Dsld_triggerTransmit();

            /* Update return value */
            dataRetValue_u8 = E_OK;

        }
    }
    return(dataRetValue_u8);
}

/**
 **************************************************************************************************
 * Dcm_IsInfrastructureErrorPresent_b : API to check for infrastructure error
 * \param           dataInfrastrutureCode_u8 : Parameter to be checked for infrastructure Error
 *
 *
 * \retval          TRUE : if infrastructure error is present
 * 					FALSE : if infrastructure error is not present
 * \seealso
 * \usedresources
 **************************************************************************************************
 */

FUNC(boolean,DCM_CODE) Dcm_IsInfrastructureErrorPresent_b(VAR(uint8,AUTOMATIC) dataInfrastrutureCode_u8)
{
	VAR(boolean,AUTOMATIC) stInfrastructStatus_b;
	if((dataInfrastrutureCode_u8 & 0x80u) != (0x00u))
	{
	    /*Infrastructure Error status is set to TRUE*/
		stInfrastructStatus_b= TRUE;
	}
	else
	{
	    /*Infrastructure Error status is set to FALSE*/
		stInfrastructStatus_b= FALSE;
	}
	return(stInfrastructStatus_b);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

