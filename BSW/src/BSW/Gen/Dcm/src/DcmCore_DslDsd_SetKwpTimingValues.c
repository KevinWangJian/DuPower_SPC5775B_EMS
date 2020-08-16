

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/**
 **************************************************************************************************
 * Dcm_SetKwpTimingValues : API to Set the given set of timings
 * \param           None
 *
 * \retval          None
 *
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_SetKwpTimingValues (void)
{
    /* This API is allowed only for KWP */
    /*If the return value is TRUE*/
    if(DCM_IS_KWPPROT_ACTIVE() != FALSE)
    {
    /* Set the previously stored timings */
    /* Dcm_PrepareKwpTimingValues can update these values in parallel */
    SchM_Enter_Dcm_DsldTimer_NoNest();

    Dcm_DsldTimer_st.dataTimeoutP2max_u32 = Dcm_DsldKwpReqTiming_st.P2_max_u32;
    Dcm_DsldTimer_st.dataTimeoutP3max_u32 = Dcm_DsldKwpReqTiming_st.P3_max_u32;
    /* for KWP P2* max is equal to P3 max */
    Dcm_DsldTimer_st.dataTimeoutP2StrMax_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;

    /* Old P3 max is getting monitored now. Change this to new P3 max */
    DCM_TimerSetNew(Dcm_DsldGlobal_st.dataTimeoutMonitor_u32,Dcm_DsldTimer_st.dataTimeoutP3max_u32)
    SchM_Exit_Dcm_DsldTimer_NoNest();
    }
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

