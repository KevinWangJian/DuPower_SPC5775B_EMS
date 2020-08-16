

#include "DcmCore_DslDsd_Inf.h"

#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"


/**
 **************************************************************************************************
 * Dcm_PrepareKwpTimingValues : API to validate the given set of timings
 * \param           TimerServerNew (in): Pointer to structure which timings to be validated.
 *
 * \retval          DCM_E_OK: preparation successful,
 *                  DCM_E_TI_PREPARE_LIMITS: requested values are not within the defined limits
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(Dcm_StatusType,DCM_CODE) Dcm_PrepareKwpTimingValues(
                                        P2CONST(Dcm_Dsld_KwpTimerServerType,AUTOMATIC,DCM_APPL_CONST) TimerServerNew
                                                        )
{
    VAR(uint8,AUTOMATIC) idxLimitTmg_u8;
    VAR(Dcm_StatusType,AUTOMATIC) dataReturnValue_u8;

    /* By default made return value as out of limit */
    dataReturnValue_u8 = DCM_E_TI_PREPARE_LIMITS;

    if(TimerServerNew != NULL_PTR)
    {
        /* Get the index of the default timing structure */
        idxLimitTmg_u8 = Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].timings_limit_idx_u8;

        /* Validate the timings. Given P2 max should be less than configured limit P2 max and Given P3 max */
        /* should be less than configured limit P3 max                                                    */
        if( (TimerServerNew->P2_max_u32 <= Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P2_max_u32)
             && (TimerServerNew->P3_max_u32 <= Dcm_Dsld_Limit_timings_acs[idxLimitTmg_u8].P3_max_u32))
        {
            /* Store the given validated timings in RAM variable */
            /* Dcm_SetKwpTimingValues can read these values, it may be required to read both P2, P3 without any data inconsistency */
            SchM_Enter_Dcm_DsldTimer_NoNest();
            Dcm_DsldKwpReqTiming_st.P2_max_u32 = TimerServerNew-> P2_max_u32;
            Dcm_DsldKwpReqTiming_st.P3_max_u32 = TimerServerNew-> P3_max_u32;
            SchM_Exit_Dcm_DsldTimer_NoNest();

            /* validation successfully completed */
            dataReturnValue_u8 = E_OK;
        }
    }
    return(dataReturnValue_u8);
}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

