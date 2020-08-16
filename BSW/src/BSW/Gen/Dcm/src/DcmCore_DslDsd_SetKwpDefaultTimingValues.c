

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 **************************************************************************************************
 * Dcm_SetKwpDefaultTimingValues : API to Set the default timings
 * \param           None
 *
 * \retval          None
 *
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_SetKwpDefaultTimingValues(void)
{
    VAR(uint8,AUTOMATIC) idxDefaultTmg_u8;

    /* This API is allowed only for KWP */
    /*Check if the return value is TRUE*/
    if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
    {
		/* Get the index of the default of timing structure */
		idxDefaultTmg_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_idx_u8;

	    /* To maintain consistency between P2MAX, P3MAX and P2StarMax */
	    SchM_Enter_Dcm_DsldTimer_NoNest();

		/* Set the default timings from configured default time */
		Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_Dsld_default_timings_acs[idxDefaultTmg_u8].P2_max_u32;
		Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_Dsld_default_timings_acs[idxDefaultTmg_u8].P3_max_u32;
		/* For KWP P2* max is equal to P3 max */
		Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;

		/* Old P3 max is getting monitored now. Change this to new P3 max */
		DCM_TimerSetNew(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_DsldTimer_st.dataTimeoutP3max_u32)
	    SchM_Exit_Dcm_DsldTimer_NoNest();
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

