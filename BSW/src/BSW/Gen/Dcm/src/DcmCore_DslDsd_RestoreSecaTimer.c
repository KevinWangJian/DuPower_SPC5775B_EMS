

#include "DcmCore_DslDsd_Inf.h"


#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)

	static VAR(uint8,AUTOMATIC)   Dcm_Prv_idxSec_qu8;              /* Loop index for Security table */
	static VAR(uint32,AUTOMATIC)  Dcm_Prv_dataSecaGlobaltimer_u32; /* Local variable to calculate the elapsed time */

#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP == DCM_CFG_OFF))
	static VAR(uint32,AUTOMATIC)  Dcm_Prv_nrPowerOnDelay_u32;      /* Local variable to store the power on delay time */
#endif

/**
 ***********************************************************************************************************************
 Function name    : Dcm_Prv_SecaPowerOnDelayExpired
 Syntax           : Dcm_Prv_SecaPowerOnDelayExpired(void)
 Description      : Function updates the residual delay time when seca power on delay timer is expired
 Parameter        : None
 Return value     : None
 ***********************************************************************************************************************
 */
#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_ON))
static FUNC(void,DCM_CODE) Dcm_Prv_SecaPowerOnDelayExpired(void)
{
	VAR(uint32,AUTOMATIC)       nrDelay_u32;/* Local variable to store the residual time */

	/* if power on delay is expired, then check if the failed attempt count has reached the configured attempt count */
	if(Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].FailedAtm_cnt_u8 >= Dcm_Dsp_Security[Dcm_Prv_idxSec_qu8].NumAttDelay_u8)
	{
        if(Dcm_Dsp_Security[Dcm_Prv_idxSec_qu8].DelayTime_u32 > 0x00u)
		{
		nrDelay_u32 = (Dcm_Dsp_Security[Dcm_Prv_idxSec_qu8].DelayTime_u32 * DCM_CFG_TASK_TIME_MS);
        /* DcmAppl_DcmGetUpdatedDelayTime should return Residual Delay time in milliseconds */
        nrDelay_u32 = DcmAppl_DcmGetUpdatedDelayTime( Dcm_Dsp_Security[Dcm_Prv_idxSec_qu8].Security_level_u8,
        Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].FailedAtm_cnt_u8,nrDelay_u32);
        nrDelay_u32 = (nrDelay_u32 / DCM_CFG_TASK_TIME_MS);
           if(nrDelay_u32 > Dcm_Prv_dataSecaGlobaltimer_u32)
            {
            /* load the delay as the failed attempt count has reached the max value configured */
            Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].Residual_delay_u32 = (nrDelay_u32 - Dcm_Prv_dataSecaGlobaltimer_u32);
            }
			else
			{
			/* Updated Delay if less than the elapsed time in SecaGlobalTimer or failed attempt count
			has not reached the max configured value , reset the residual delay to zero */
			Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].Residual_delay_u32 = 0;
			}
        }
        else
        {
 		Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].Residual_delay_u32 = 0;
        }
    }
    else
    {
    /* Updated Delay if less than the elapsed time in SecaGlobalTimer or failed attempt count has
	not reached the max configured value , reset the residual delay to zero */
    Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].Residual_delay_u32 = 0;
    }
}
/**
 ***********************************************************************************************************************
 Function name    : Dcm_Prv_SecaPowerOnDelayNotExpired
 Syntax           : Dcm_Prv_SecaPowerOnDelayNotExpired(void)
 Description      : Function updates the residual delay time when seca power on delay timer is not expired
 Parameter        : None
 Return value     : None
 ***********************************************************************************************************************
 */
static FUNC(void,DCM_CODE) Dcm_Prv_SecaPowerOnDelayNotExpired(void)
{
	Dcm_Prv_nrPowerOnDelay_u32 = (Dcm_Prv_nrPowerOnDelay_u32 * DCM_CFG_TASK_TIME_MS);
    /* DcmAppl_DcmGetUpdatedDelayTime should return power on Residual Delay time in milliseconds */
    Dcm_Prv_nrPowerOnDelay_u32 = DcmAppl_DcmGetUpdatedDelayTime( Dcm_Dsp_Security[Dcm_Prv_idxSec_qu8].Security_level_u8,
    Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].FailedAtm_cnt_u8,Dcm_Prv_nrPowerOnDelay_u32);
    Dcm_Prv_nrPowerOnDelay_u32 = (Dcm_Prv_nrPowerOnDelay_u32 / DCM_CFG_TASK_TIME_MS);

    if(Dcm_Prv_nrPowerOnDelay_u32 > Dcm_Prv_dataSecaGlobaltimer_u32)
    {
    /* loading the power on Delay */
    Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].Residual_delay_u32 = Dcm_Prv_nrPowerOnDelay_u32 - Dcm_Prv_dataSecaGlobaltimer_u32;
    }
    else
    {
    /* load the residual delay as zero, as it has been already elapsed in BOOT */
    Dcm_Dsp_Seca[Dcm_Prv_idxSec_qu8].Residual_delay_u32 = 0;
    }
}
#endif

/**
 ***********************************************************************************************************************
 Function name    : Dcm_Prv_SecaWarmStart
 Syntax           : Dcm_Prv_SecaWarmStart(void)
 Description      : Function gets executed because of seca warm start
 Parameter        : None
 Return value     : None
 ***********************************************************************************************************************
 */
static FUNC(void,DCM_CODE)Dcm_Prv_SecaWarmStart(void)
{
    VAR(uint8,AUTOMATIC)  dataNumBootSeclev_u8;			/* Local variable for number of security levels in Boot */
	VAR(uint8,AUTOMATIC)  l_idxSec_qu8;                 /* Local Loop index for Security table */
#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF))
    VAR(uint8,AUTOMATIC)  idxDcmSeclevel_u8;
    dataNumBootSeclev_u8=Dcm_ProgConditions_st.NumOfSecurityLevels;
#else
    dataNumBootSeclev_u8 = DCM_CFG_DSP_NUMSECURITY;
#endif
	/* Restore Security Timers */
    Dcm_Prv_dataSecaGlobaltimer_u32 = ((Dcm_ProgConditions_st.ElapsedTime * 1000uL)/DCM_CFG_TASK_TIME_US);

    if(Dcm_Dsp_SecaGlobaltimer_u32 != 0xFFFFFFFFuL)
    {
        /* Loop for all the security levels configured in Boot software */
        for(l_idxSec_qu8=0; l_idxSec_qu8 < dataNumBootSeclev_u8; l_idxSec_qu8++)
        {
			Dcm_Prv_idxSec_qu8 = l_idxSec_qu8;
#if((DCM_CFG_SECURITY_STOREDELAYCOUNTANDTIMERONJUMP != DCM_CFG_OFF))
            for(idxDcmSeclevel_u8=0;idxDcmSeclevel_u8<DCM_CFG_DSP_NUMSECURITY;idxDcmSeclevel_u8++)
            {
				if(Dcm_Dsp_Security[idxDcmSeclevel_u8].Security_level_u8==
				   Dcm_ProgConditions_st.SecurityInformation[l_idxSec_qu8].SecurityLevel)
                {
                 break;
                }
            }
#else
			Dcm_Prv_nrPowerOnDelay_u32 = (Dcm_Dsp_Security[l_idxSec_qu8].PowerOnDelay_u32);
			/* if the power on delay is expired */
            if(Dcm_Prv_nrPowerOnDelay_u32 <= Dcm_Prv_dataSecaGlobaltimer_u32)
            {
				Dcm_Prv_SecaPowerOnDelayExpired();
            }
            /* power on delay has not expired. */
            else
            {
				Dcm_Prv_SecaPowerOnDelayNotExpired();
            }
#endif
		}
    }
}
#endif
#endif

/**
 ***********************************************************************************************************************
 Function name    : Dcm_DslDsdRestoreSecaTimer
 Syntax           : Dcm_DslDsdRestoreSecaTimer(void)
 Description      : Function Restores the SECA Timers values
 Parameter        : None
 Return value     : None
 ***********************************************************************************************************************
 */
FUNC(void,DCM_CODE)Dcm_DslDsdRestoreSecaTimer(void)
{
#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#if(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
    /* Check if the function is called because of WARM START */
    if(Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE)
    {
        Dcm_Prv_SecaWarmStart();
    }
    else
    {
        /* Normal initialization in boot */
        /* Power on delay in case of boot has to be started only if it is normal initialization */
        /* If the SECA service is configured and valid power on delay function is configured */
        Dcm_Dsp_SecaPowerOnDelayIni();
    }
#else
    /* If the SECA service is configured and valid power on delay function is configured */
    Dcm_Dsp_SecaPowerOnDelayIni();
#endif
#endif
}
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

