

#include "DcmDspUds_Seca_Inf.h"

#if(DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)
#include "DcmDspUds_Seca_Priv.h"


#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* Array for all the security levels in the SECA configuration */
VAR (Dcm_Dsp_SecaType,  DCM_VAR) Dcm_Dsp_Seca[DCM_CFG_DSP_NUMSECURITY];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (Dcm_Dsp_SecaStates_ten,DCM_VAR) Dcm_DspSecaStatus_en; /* Status of SECA state machine */
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (boolean, DCM_VAR) Dcm_DspChgSecLevel_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR (Dcm_OpStatusType, DCM_VAR) Dcm_DspSecaOpStatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/**
 ***********************************************************************************************************************
 * Dcm_Dsp_SecaIni : Initialization function for SECA Service
 *
 * \param           None
 *
 * \retval          None
 ***********************************************************************************************************************
*/
FUNC (void,DCM_CODE) Dcm_Dsp_SecaIni (void)
{

#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
    P2CONST(void,AUTOMATIC, DCM_INTERN_DATA) ptrSecaFnc;
    P2CONST(Dcm_Dsp_Security_t,AUTOMATIC,DCM_INTERN_DATA) ptrSecurityConfig;
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegRespCode_u8; /* Local variable to store the NRC */
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    VAR(Dcm_SecLevelType,AUTOMATIC)   dataSecLevel_u8;     /* Local variable to store Security level */
#endif

#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)|| (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
    dataNegRespCode_u8 = 0x0; /* Initialise the local variable */
#endif

    /* If there is a PENDING operation */
    if(Dcm_DspSecaOpStatus_u8 == DCM_PENDING)
    {   /* Pending Get Seed operation ?*/
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
    	ptrSecurityConfig =&Dcm_Dsp_Security[Dcm_DspSecTabIdx_u8];
#endif
    	if(Dcm_DspSecaStatus_en == DCM_DSP_SECA_GENSEED)
    	{
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
    		ptrSecaFnc = ptrSecurityConfig->Dsp_GetSeed_fp;
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
    		if(ptrSecurityConfig->usePort == USE_ASYNCH_CLIENT_SERVER)
    		{
#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
    		    /* Is Asynchronous server call point handling is requested */
    		    if(ptrSecurityConfig->UseAsynchronousServerCallPoint_b)
    		    {
    		        /* Call the Rte_Call API with In and InOut parameters to cancel the ongoing operation */
                    if(ptrSecurityConfig->AccDataRecsize_u8!=0)
                       {
                           /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
						   Required for efficient RAM usage by using single void function pointer */
                           (void)(*(Dcm_GetSeed_ptr5)(ptrSecaFnc))(NULL_PTR,DCM_CANCEL);
                       }
                       else
                       {
                           /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
						   Required for efficient RAM usage by using single void function pointer */
                           (void)(*(Dcm_GetSeed_ptr6)(ptrSecaFnc))(DCM_CANCEL);
                       }
    		    }
    		    else
#endif
    		    {
    		        if(ptrSecurityConfig->AccDataRecsize_u8!=0)
    		        {
    		            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
						Required for efficient RAM usage by using single void function pointer */
    		            (void)(*(Dcm_GetSeed_ptr)(ptrSecaFnc))(NULL_PTR,DCM_CANCEL,NULL_PTR,&dataNegRespCode_u8);
    		        }
    		        else
    		        {
    		            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
						Required for efficient RAM usage by using single void function pointer */
    		            (void)(*(Dcm_GetSeed_ptr3)(ptrSecaFnc))(DCM_CANCEL,NULL_PTR,&dataNegRespCode_u8);
    		        }
    		    }
				(void)dataNegRespCode_u8;
    		}
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    		if(ptrSecurityConfig->usePort == USE_ASYNCH_FNC)
    		{
    			/* Calculate the security level */
    			dataSecLevel_u8  = ((Dcm_DspSecAccType_u8+1u)>>1u);
    			/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
				Required for efficient RAM usage by using single void function pointer */
    			(void)(*(Dcm_GetSeed_ptr4)(ptrSecaFnc))(
											dataSecLevel_u8,
											ptrSecurityConfig->Seed_size_u8,
											ptrSecurityConfig->AccDataRecsize_u8,
											NULL_PTR,NULL_PTR,DCM_CANCEL,&dataNegRespCode_u8);
				(void)dataNegRespCode_u8;
    		}
#endif
    	}
    	if(Dcm_DspSecaStatus_en == DCM_DSP_SECA_COMPAREKEY)
    	{
#if((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) || (DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF))
    		ptrSecaFnc = ptrSecurityConfig->Dsp_CompareKey_fp;
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
    		if(ptrSecurityConfig->usePort == USE_ASYNCH_CLIENT_SERVER)
    		{
#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
                /* Is ASynchronous server call point handling is requested */
                if(ptrSecurityConfig->UseAsynchronousServerCallPoint_b)
                {
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
					Required for efficient RAM usage by using single void function pointer */
                    (void)(*(Dcm_CompareKey_ptr4)(ptrSecaFnc))(NULL_PTR, DCM_CANCEL);
                }
                else
#endif
                {
                    /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
					Required for efficient RAM usage by using single void function pointer */
                    (void)(*(Dcm_CompareKey_ptr1)(ptrSecaFnc))(NULL_PTR, DCM_CANCEL,&dataNegRespCode_u8);
                }
    		}
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    		if(ptrSecurityConfig->usePort == USE_ASYNCH_FNC)
    		{
    			/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation - 
				Required for efficient RAM usage by using single void function pointer */
    			(void)(*(Dcm_CompareKey_ptr3)(ptrSecaFnc))(ptrSecurityConfig->Key_size_u8,NULL_PTR, 
				DCM_CANCEL,&dataNegRespCode_u8);
    		}
#endif
    	}
    }

    /* Reset the flags defined for Asynchonous Server point handling */
#if (DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
    Dcm_ResetAsynchSecaFlag();
#endif
    /* Reset the Seca Opstatus */
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;

    /* Re-Initialisation of Security Access State and Global parameters */
    Dcm_Dsp_SecaSessIni();

}

/**
 **************************************************************************************************
 * Dcm_Dsp_SecaPowerOnDelayIni : Initialization of PowerOn delay timer for all security levels configured
 *
 * \param           None
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
*/
FUNC (void,DCM_CODE) Dcm_Dsp_SecaPowerOnDelayIni (void)
{
    VAR (uint8_least,AUTOMATIC) idxSecTab_qu8;  /* Local variable to iterate through the security table */
    VAR (uint32,AUTOMATIC) dataDelayOnPowerOn_u32;

    for (idxSecTab_qu8=0;idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY;idxSecTab_qu8++)
    {
        if(Dcm_Dsp_Seca[idxSecTab_qu8].FailedAtm_cnt_u8 >= Dcm_Dsp_Security[idxSecTab_qu8].NumAttDelay_u8)
        {
            dataDelayOnPowerOn_u32 =  
			(Dcm_Dsp_Security[idxSecTab_qu8].DelayTime_u32 > Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32) ? 
			Dcm_Dsp_Security[idxSecTab_qu8].DelayTime_u32 : Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32;
            if(dataDelayOnPowerOn_u32 > 0x00u)
            {
                dataDelayOnPowerOn_u32 = dataDelayOnPowerOn_u32 * DCM_CFG_TASK_TIME_MS;
                /* DcmAppl_DcmGetUpdatedDelayTime should return Residual Delay time in Counts of DcmTaskTime */
                dataDelayOnPowerOn_u32 = 
				DcmAppl_DcmGetUpdatedDelayTime(Dcm_Dsp_Security[idxSecTab_qu8].Security_level_u8,
				Dcm_Dsp_Seca[idxSecTab_qu8].FailedAtm_cnt_u8,dataDelayOnPowerOn_u32);
                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 = 
				(Dcm_Dsp_SecaGlobaltimer_u32 + (dataDelayOnPowerOn_u32 / DCM_CFG_TASK_TIME_MS));
            }
            else
            {
            /*if both PowerOnDelay_u32 and DelayTime_u32 are initialized with 0 then assign Residual_delay_u32 with 0*/
                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 = 0x00u;
            }
        }
        else
        {
            if(Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32 > 0x00u)
            {
                dataDelayOnPowerOn_u32 =  
				DcmAppl_DcmGetUpdatedDelayForPowerOn(Dcm_Dsp_Security[idxSecTab_qu8].Security_level_u8,
				Dcm_Dsp_Seca[idxSecTab_qu8].FailedAtm_cnt_u8,
				(Dcm_Dsp_Security[idxSecTab_qu8].PowerOnDelay_u32 * DCM_CFG_TASK_TIME_MS));
                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 = (dataDelayOnPowerOn_u32/DCM_CFG_TASK_TIME_MS);
            }
            else
            {
                Dcm_Dsp_Seca[idxSecTab_qu8].Residual_delay_u32 = 0x00u;
            }
        }
    }
    return;
}
/**
 ***********************************************************************************************************************
 * Dcm_Dsp_SecaSesIni : Re-Initialization of all security parameters due to session timeout or change in session.
 *
 * \param           None
 *
 * \retval          None
 ***********************************************************************************************************************
*/
FUNC (void,DCM_CODE) Dcm_Dsp_SecaSessIni (void)
{
    /* Initialise SECA state machine */
	Dcm_SrvOpstatus_u8 = DCM_INITIAL;
    //Dcm_DspSecaStatus_en = DCM_DSP_SECA_REQUEST;
	/* Initialise change security level */
    Dcm_DspChgSecLevel_b = FALSE;
    /* Resetting Stored AccessType */
    Dcm_DspSecAccType_u8 = 0x0;
    /* Resetting Security Index */
    Dcm_DspSecTabIdx_u8  = 0x0;

}

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#endif
