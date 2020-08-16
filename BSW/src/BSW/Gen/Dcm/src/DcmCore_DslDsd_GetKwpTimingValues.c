

#include "DcmCore_DslDsd_Inf.h"


#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 **************************************************************************************************
 * Dcm_GetKwpTimingValues : API to get the different set of timings
 * \param           TimerMode (in): Mode of timing
 *                  TimerServerCurrent (out) : Pointer to structure where timings are written by DCM
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_GetKwpTimingValues(
                                           VAR(Dcm_TimerModeType,AUTOMATIC) TimerMode,
                                           P2VAR(Dcm_Dsld_KwpTimerServerType,AUTOMATIC,DCM_APPL_DATA) TimerServerCurrent
                                          )
{
    VAR(uint8,AUTOMATIC) idxLimitTmg_u8;

    if(TimerServerCurrent != NULL_PTR)
    {
        /* Get the index of the limit of timing structure */
        idxLimitTmg_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_limit_idx_u8;

        if(TimerMode == DCM_CURRENT)
        {
            /* Fill the running P2 max and P3 max time */
            SchM_Enter_Dcm_DsldTimer_NoNest();
            TimerServerCurrent-> P2_max_u32 = Dcm_DsldTimer_st.dataTimeoutP2max_u32;
            TimerServerCurrent-> P3_max_u32 = Dcm_DsldTimer_st.dataTimeoutP3max_u32;
            SchM_Exit_Dcm_DsldTimer_NoNest();
        }
        else
        {
            /* Fill the limit P2 max and limit P3 max time */
            TimerServerCurrent-> P2_max_u32 = Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P2_max_u32;
            TimerServerCurrent-> P3_max_u32 = Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P3_max_u32;
        }
    }
	else
	{
		/* Report development error "DCM_E_PARAM_POINTER " to DET module if the DET module is enabled */
		DCM_DET_ERROR(DCM_KWPTIMING_ID , DCM_E_PARAM_POINTER )
	}
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif
