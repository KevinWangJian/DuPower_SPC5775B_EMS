

#include "DcmDspUds_Seca_Inf.h"

#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF ) )
#include "DcmDspUds_Seca_Priv.h"
#define DCM_START_SEC_VAR_CLEARED_8									/* Adding this for memory mapping   */
#include "Dcm_Cfg_MemMap.h"
VAR(uint8, DCM_VAR)  Dcm_DspSecTabIdx_u8;       					/* Security table index */
VAR(uint8, DCM_VAR)  Dcm_DspSecAccType_u8;      					/* Security Access type requested   */
static VAR(uint8, DCM_VAR)	 Dcm_Prv_stCmpKey_u8;   				/* Status of comparison of Key      */
static VAR(Dcm_SecLevelType, DCM_VAR)    Dcm_Prv_dataSecLevel_u8;   /* variable to store Security level */
#define DCM_STOP_SEC_VAR_CLEARED_8									/* Adding this for memory mapping   */
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED 						/* Adding this for memory mapping   */
#include "Dcm_Cfg_MemMap.h"
static VAR(uint8_least, DCM_VAR)  Dcm_Prv_idxSecTab_qu8;    		/* variable to store table index    */

static P2CONST(Dcm_Dsp_Security_t,AUTOMATIC,DCM_INTERN_DATA) Dcm_Prv_ptrSecurityConfig_p;
static P2VAR(void,AUTOMATIC, DCM_INTERN_DATA) 	Dcm_Prv_ptrSecaFnc_p;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
#endif
static VAR(uint8,AUTOMATIC)              		Dcm_Prv_dataSecAccType_u8;   /* Local variable to store Access type */
static VAR(uint8,AUTOMATIC)              		Dcm_Prv_dataSubFunc_u8;      /* Local variable to store sub-function*/
static VAR(uint8,AUTOMATIC)              		Dcm_Prv_nrSeedLen_u8;        /* Local variable to store Seed Length */
static VAR(Dcm_Dsp_SecaStates_ten,AUTOMATIC) 	Dcm_Prv_substSeca_en;        /* Seca sub status in CHECKDATA state  */
static VAR(Std_ReturnType,AUTOMATIC)     		Dcm_Prv_dataRetGetSeed_u8;   /* Return type of XXX_GetSeed API  */
/* return value of API used for storing security attempt counter in NVM */
static VAR(Std_ReturnType,AUTOMATIC)     		Dcm_Prv_dataRetValue_u8;
static VAR(Std_ReturnType,AUTOMATIC)     		Dcm_Prv_secaServRetValue_u8; /* SECA service return variable */
/* DelayTimer variable for Updated DelayTime */
static VAR(uint32,AUTOMATIC)             		Dcm_Prv_nrDelay_u32;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
static VAR(boolean,AUTOMATIC)            		Dcm_Prv_stBuffer_b;          /* Status Of the Seed Buffer */
#endif

#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED 								 /* Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_BOOLEAN 									 /* Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* This is set if DcmAppl_StoreDelayCount is called in the pending state*/
static VAR(boolean, DCM_VAR)      Dcm_Prv_flgApplFuncCall_b;
#if( DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
/* For ASynchronous server call point handling */
static VAR(boolean, DCM_VAR)      Dcm_Prv_Dcm_SecaRteCallPlaced_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN 									/* Adding this for memory mapping */
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_CODE 													/* Adding this for memory mapping */
#include "Dcm_Cfg_MemMap.h"

#if( DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
/**
 ***********************************************************************************************************************
 *Function name    : Dcm_ResetAsynchSecaFlags
 *Syntax           : Dcm_ResetAsynchSecaFlag(void)
 *Description      : Reset all the Flags for Asynchronous server call point handling
 *					 This API is invoked by Rdbi_Ini to reset Flags in case of Protocol Preemption
 *Parameter        : None
 *Return value     : None
 ***********************************************************************************************************************
 */
FUNC (void,DCM_CODE) Dcm_ResetAsynchSecaFlag(void)
{
     /* Reset the Flags defined for Asynchronous server call point handling */
     Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
}
#endif
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_NewSecurityLevelToUnlock
*Syntax           : Dcm_Prv_NewSecurityLevelToUnlock(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType pMsgContext)
*Description      : Function to Unlock the requested New security level
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType  pMsgContext
*Return value     : None
************************************************************************************************************************
*/
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_NewSecurityLevelToUnlock
							(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
							  P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
#else
static FUNC(void,DCM_CODE) Dcm_Prv_NewSecurityLevelToUnlock
							(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                              P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
#endif
{
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)

    /* Local Loop variable for Seed index  */
    VAR(uint8_least,AUTOMATIC)      l_idxSeed_qu8;
    /* Copy seed length to local variable */
    Dcm_Prv_nrSeedLen_u8 = Dcm_Prv_ptrSecurityConfig_p->Seed_size_u8;

    /* Fill the seed stored in Request Seed state */
    for(l_idxSeed_qu8 =0; (l_idxSeed_qu8 < Dcm_Prv_nrSeedLen_u8); l_idxSeed_qu8++)
    {
    /* Check if SeedBuffer is valid */
        if(Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].SeedBuff[l_idxSeed_qu8] != 0x0)
        {
        /* SeedBuffer has Valid Data Proceed Restoration */
        Dcm_Prv_stBuffer_b = TRUE;
        break;
        }
    }
    /* Check for Valid BuffState for Seed Restoration */
    if(Dcm_Prv_stBuffer_b != FALSE)
    {
    /* Fill the seed stored in Request Seed state */
        for(l_idxSeed_qu8 =0; (l_idxSeed_qu8 < Dcm_Prv_nrSeedLen_u8); l_idxSeed_qu8++)
        {
        /* Store the seed in the response buffer */
        pMsgContext->resData[l_idxSeed_qu8 + 0x1u] = Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].SeedBuff[l_idxSeed_qu8];
        }
        /* Fill the Access Type in the response buffer */
        pMsgContext->resData[0] = Dcm_Prv_dataSubFunc_u8;
        /* Update response data length */
        pMsgContext->resDataLen = (Dcm_MsgLenType)(l_idxSeed_qu8 + 1u);
        Dcm_Prv_secaServRetValue_u8=E_OK;
    }
    else
#endif
    {
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u)
    /* Copy Security Access Data Record into Buffer */
        if( Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8 != 0x00u)
        {
			/*MR12 DIR 1.1 VIOLATION:This is required for implememtaion as DCM_MEMCOPY takes void pointer as input and object type pointer is converted to void pointer*/
            DCM_MEMCOPY(&(Dcm_InParameterBuf_au8[0]), &(pMsgContext->reqData[1]),
            Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8);
        }
#endif
		/* set state to CHECKDATA */
		*OpStatus = DCM_CHECKDATA;
		/* Set substate to GENSEED */
		Dcm_Prv_substSeca_en = DCM_DSP_SECA_GENSEED;
    }
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_ReqSecIsCurrentSecurityLevel
*Syntax           : Dcm_Prv_ReqSecIsCurrentSecurityLevel(Dcm_SrvOpStatusType OpStatus,Dcm_MsgContextType pMsgContext)
*Description      : Function to be performed in case of SEED request, requested security level matches with the current
*     			    security level
*Parameter        : Dm_SrvOpStatusType OpStatus, Dcm_MsgContextType  pMsgContext
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_ReqSecIsCurrentSecurityLevel
						   (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                            P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext)
{
    VAR(uint8_least,AUTOMATIC)  idxLoopSeed_qu8;    /* Local variable to traverse the loop   */
    /* Fill the response buffer */
    pMsgContext->resData[0] = Dcm_Prv_dataSecAccType_u8;

    /* Fill 0x00 for all bytes of Seed size */
    for(idxLoopSeed_qu8=1;(idxLoopSeed_qu8 <=Dcm_Prv_ptrSecurityConfig_p->Seed_size_u8);idxLoopSeed_qu8++)
    {
        pMsgContext->resData[idxLoopSeed_qu8] = 0x00;
    }
    /* Update Response Data Length */
    pMsgContext->resDataLen = (uint8)idxLoopSeed_qu8;

    /* Move back to Request seed state */
    /* stSeca_en =  DCM_DSP_SECA_REQUEST; */
    *OpStatus = DCM_INITIAL;
    /* Resetting Stored AccessType */
    Dcm_DspSecAccType_u8 = 0x0;
    /* Resetting Security Index */
    Dcm_DspSecTabIdx_u8  = 0x0;
    Dcm_Prv_secaServRetValue_u8=E_OK;
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_CurrentSecurityLevel
*Syntax           : Dcm_Prv_CurrentSecurityLevel
*					(Dcm_MsgContextType pMsgContext,Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to check current security level in case of a new security request
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_CurrentSecurityLevel
							(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
								P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    VAR(Dcm_SecLevelType,AUTOMATIC)   dataGetSecurityLevel_u8;  /* Variable for current active security level */
	VAR(Std_ReturnType,AUTOMATIC)     dataRetGetSecLevel_u8;    /* return for Dcm_GetSecurityLevel */

    /* Get the current active security level */
    dataRetGetSecLevel_u8 = Dcm_GetSecurityLevel(&dataGetSecurityLevel_u8);

    /* if the current security was read without any errors */
    if(dataRetGetSecLevel_u8 == E_OK)
    {
        Dcm_DspSecTabIdx_u8  = (uint8)(Dcm_Prv_idxSecTab_qu8); 	 /* Update Security table index */
        Dcm_DspSecAccType_u8 = Dcm_Prv_dataSecAccType_u8;        /* Store the Access Type       */

        /* Check if the request security is the current active security */
        if(dataGetSecurityLevel_u8 == Dcm_Prv_dataSecLevel_u8)
        {
        Dcm_Prv_ReqSecIsCurrentSecurityLevel(&Dcm_SrvOpstatus_u8,pMsgContext);
        }
        /* New security level is requested to unlock */
        else
        {
        Dcm_Prv_NewSecurityLevelToUnlock(&Dcm_SrvOpstatus_u8,pMsgContext);
        }
    }
    else
    {
    /* Set the negative response */
    *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
    }
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecurityLevelConfigured
*Syntax           : Dcm_Prv_SecurityLevelConfigured
* 					(Dcm_MsgContextType pMsgContext,Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : In DCM_INITIAL state for a given SEED request, following checks to be done if requested
*					Seecurity level is configured
*                       a. Check for correct request length
*                       b. Check if number of attempts exceeds the configured value
*                       c. Check if time monitoring is required for Seed Request and Delay time is active
*Parameter        : Dcm_MsgContextType pMsgContext
*  	                Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecurityLevelConfigured
						   (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                           P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Prv_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Prv_idxSecTab_qu8];
    /* Check for the request length */
    if(pMsgContext->reqDataLen != (0x01u + Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8))
    {
		/* Set the negative response as request length is incorrect ($13) */
		*dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
    /* Check if number of attempts exceeds the configured value */
    else if((Dcm_Prv_ptrSecurityConfig_p->NumAttLock_u8 > 0) &&
	(Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8 >= Dcm_Prv_ptrSecurityConfig_p->NumAttLock_u8))
    {
		*dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
    }
#if (DCM_CFG_DSP_DELAYTIMERMONITORING == DCM_PRV_REQUEST_SEED)
    /* Check if time monitoring is required for Seed Request and Delay time is active */
    else if(Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].Residual_delay_u32 > Dcm_Dsp_SecaGlobaltimer_u32)
    {
        *dataNegRespCode_u8 = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
    }
#endif
    else
    {
        Dcm_Prv_CurrentSecurityLevel(pMsgContext,dataNegRespCode_u8);
    }
/**
    else
    {
		* Requested security level is not allowed in the current session *
		* It is assumed, this subfunction has been allowed in any one other sessions at least *
        * Configuration tool should have taken care of this point *
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION;
    }
**/
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaSeedRequest
*Syntax           : Dcm_Prv_SecaSeedRequest
* 					(Dcm_MsgContextType pMsgContext,Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : In DCM_INITIAL state checks to be done in case of a new SEED request
*                           a. Whether the requested security level is configured in ECU
*                           b. If the wait cycle counter for Get attempt counter is exhausted
*Parameter        : Dcm_MsgContextType pMsgContext
*  	                Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaSeedRequest (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /* Local variable to store table index */
    VAR(uint8_least, DCM_VAR)  l_idxSecTab_qu8;

    /* Request is Valid Seed Request.Get requested Access Type */
    Dcm_Prv_dataSecAccType_u8 = Dcm_Prv_dataSubFunc_u8;

    /* Evaluate the Security Level requested */
    Dcm_Prv_dataSecLevel_u8 = ((Dcm_Prv_dataSecAccType_u8 + 1u)>>1u);

    /* Check whether the requested security level is configured in ECU */
    for(l_idxSecTab_qu8=0; (l_idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY) &&
	(Dcm_Dsp_Security[l_idxSecTab_qu8].Security_level_u8 != Dcm_Prv_dataSecLevel_u8); l_idxSecTab_qu8++)
       {
        /* Do Nothing */
       }
    /* Update variable to store table index */
    Dcm_Prv_idxSecTab_qu8 = l_idxSecTab_qu8;

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
    /*Check if the wait cycle counter for Get attempt counter is exhausted*/
    if(Dcm_GetattemptCounterWaitCycle_u8 > DCM_DSP_SECURITY_MAX_ATTEMPT_COUNTER_READOUT_TIME)
    {
#endif
		/* Security level is configured */
		if(l_idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY)
		{
		Dcm_Prv_SecurityLevelConfigured (pMsgContext,dataNegRespCode_u8);
		}
		else
		{
        /* Security level is not configured */
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
		}
#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
    }
    else
    {
        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
    }
#endif
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_ReqSecaLvlConfigured
*Syntax           : Dcm_Prv_ReqSecaLvlConfigured (Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : In DCM_INITIAL state for a given SEED request
*                        a. Check if the seed was sent for the same Security Level
*                        b. Check whether the length of the key sent by tester is correct
*                        c. Check if the Delay timer monitoring is required and Delay timer is running
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*  	                Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_ReqSecaLvlConfigured
							(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                              P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Prv_ptrSecurityConfig_p =&Dcm_Dsp_Security[Dcm_Prv_idxSecTab_qu8];
    /* Calculate the security level from the stored AccessType received in Request Seed*/
    Dcm_Prv_dataSecLevel_u8   = ((Dcm_DspSecAccType_u8+1)>>1u);
    /* Check if the seed was sent for the same Security Level */
    if(Dcm_Prv_dataSubFunc_u8 != (Dcm_DspSecAccType_u8+1u))
    {
        /* Set the negative response as request length is incorrect ($24) */
        *dataNegRespCode_u8 = DCM_E_REQUESTSEQUENCEERROR;
    }
    /* Check whether the length of the key sent by tester is correct */
    else if(pMsgContext->reqDataLen != (Dcm_Prv_ptrSecurityConfig_p->Key_size_u8 + 1u))
    {
        /* Set the negative response as request length is incorrect ($13) */
        *dataNegRespCode_u8 = DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT;
    }
#if (DCM_CFG_DSP_DELAYTIMERMONITORING == DCM_PRV_SEND_KEY)
    /* Check if the Delay timer monitoring is required and Delay timer is running */
    else if(Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].Residual_delay_u32 > Dcm_Dsp_SecaGlobaltimer_u32)
    {
        /* Set the negative response as REQUIREDTIMEDELAYNOTEXPIRED */
		*dataNegRespCode_u8 = DCM_E_REQUIREDTIMEDELAYNOTEXPIRED;
    }
#endif
    else
    {
        /* set status to CHECKDATA */
        *OpStatus = DCM_CHECKDATA;
        /* Move the state to DCM_DSP_SECA_COMPAREKEY */
        Dcm_Prv_substSeca_en = DCM_DSP_SECA_COMPAREKEY;
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_ChkForReqSecaLvl
*Syntax           : Dcm_Prv_ChkForReqSecaLvl(Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : In DCM_INITIAL state for a given SECA request this function Checks if requested security level
*					is configured in ECU
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_ChkForReqSecaLvl
						   (P2CONST(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                            P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /* Local variable to store table index  */
    VAR(uint8_least, DCM_VAR)  l_idxSecTab_qu8;

    /* Calculate Security level from Sub function sent */
    Dcm_Prv_dataSecLevel_u8 = (Dcm_Prv_dataSubFunc_u8 >> 1u);

    /* Check whether the sent Access Type (security level) is configured in ECU */
    for(l_idxSecTab_qu8=0; (l_idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY) &&
	(Dcm_Dsp_Security[l_idxSecTab_qu8].Security_level_u8 != Dcm_Prv_dataSecLevel_u8); l_idxSecTab_qu8++)
    {
        /* Do Nothing */
    }
    /* Update the variable to store table index       */
    Dcm_Prv_idxSecTab_qu8 = l_idxSecTab_qu8;
    /* Security level is configured */
    if(l_idxSecTab_qu8 >= DCM_CFG_DSP_NUMSECURITY)
    {
        /* Set the Negative response as security level is not configured */
        *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
    }
    else
    {
        Dcm_Prv_ReqSecaLvlConfigured(&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaRequestState
*Syntax           : Dcm_Prv_SecaRequestState(Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : For a given seca request in Dcm state DCM_INITIAL to Check the type of seca request(SEED or KEY)
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaRequestState(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
							  P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	/* Copy the subfunction to local variable*/
    Dcm_Prv_dataSubFunc_u8    = pMsgContext->reqData[0];

    /* If this is a seed request */
    if((Dcm_Prv_dataSubFunc_u8 & 0x01u) > 0u)
    {
        Dcm_Prv_SecaSeedRequest(pMsgContext,dataNegRespCode_u8);
    }
    else
    {
        if(Dcm_Prv_dataSubFunc_u8 != 0x0)
        {
			Dcm_Prv_ChkForReqSecaLvl(pMsgContext,dataNegRespCode_u8);
        }
        else
        {
            /* Security level is not configured */
            *dataNegRespCode_u8 = DCM_E_SUBFUNCTIONNOTSUPPORTED;
        }
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCmpKeyPnding
*Syntax           : Dcm_Prv_SecaCmpKeyPnding(Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to update the seca status to PENDING in case compare key status is pending
*Parameter        : Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCmpKeyPnding
						   (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	*dataNegRespCode_u8 =0x00u;
	Dcm_DspSecaOpStatus_u8 = DCM_PENDING;
	Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaAsyncServerPt
*Syntax           : Dcm_Prv_SecaAsyncServerPt(Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to handle Asynchronous server point for comaprekey
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_SecaAsyncServerPt(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	/* Check whether the Rte_Read is already invoked */
    if (!Dcm_Prv_Dcm_SecaRteCallPlaced_b)
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_stCmpKey_u8 =
		(*(Dcm_CompareKey_ptr4)(Dcm_Prv_ptrSecaFnc_p))(&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8);

        if (Dcm_Prv_stCmpKey_u8 == RTE_E_OK)
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = TRUE;
            Dcm_Prv_stCmpKey_u8 = DCM_E_PENDING;
        }
        else
        {
            /* IF the return value is other than E_OK then set the return value to E_NOT_OK */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_stCmpKey_u8))
            {
                Dcm_Prv_stCmpKey_u8= E_NOT_OK;
            }
        }
    }
    else
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_stCmpKey_u8 =
		(*(Dcm_CompareKey_ptr5)(Dcm_Prv_ptrSecurityConfig_p->Dsp_CompareKey_ResultFp))(dataNegRespCode_u8);

		if ((Dcm_Prv_stCmpKey_u8 == RTE_E_OK) || (Dcm_Prv_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED))
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Prv_stCmpKey_u8 == RTE_E_NO_DATA)
        {
            Dcm_Prv_stCmpKey_u8 = DCM_E_PENDING;
        }
        else
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
            /* Set the return value to E_NOT_OK for return values other than E_OK or RTE_E_NO_DATA */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_stCmpKey_u8))
               {
                    Dcm_Prv_stCmpKey_u8= E_NOT_OK;
               }
        }
    }
}
#endif
#endif

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCheckdataStValidKeyChk
*Syntax           : Dcm_Prv_SecaCheckdataStValidKeyChk(Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to check whether the received key is Valid Key
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCheckdataStValidKeyChk
						   (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                           P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
    if(Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER)
    {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        /* Check whether Asynchronous server point handling is requested for the current security row */
        if (Dcm_Prv_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Prv_SecaAsyncServerPt(pMsgContext,dataNegRespCode_u8);
        }
        else
#endif
        {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
			Required for efficient RAM usage by using single void function pointer */
            Dcm_Prv_stCmpKey_u8 = (*(Dcm_CompareKey_ptr1)(Dcm_Prv_ptrSecaFnc_p))(&(pMsgContext->reqData[1]),\
									 Dcm_DspSecaOpStatus_u8, dataNegRespCode_u8);
        }
    }
#endif
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    if(Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_FNC)
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_stCmpKey_u8 = (*(Dcm_CompareKey_ptr3)(Dcm_Prv_ptrSecaFnc_p))
	    (Dcm_Prv_ptrSecurityConfig_p->Key_size_u8,&(pMsgContext->reqData[1]),Dcm_DspSecaOpStatus_u8,dataNegRespCode_u8);
    }
#endif
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaUseAsynchronousServerCallPoint
*Syntax           : Dcm_Prv_SecaUseAsynchronousServerCallPoint(void)
*Description      : Function to store the security Attempt counter value in NVM by application through RTE
*Parameter        : None
*Return value     : None
************************************************************************************************************************
*/
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_SecaUseAsynchronousServerCallPoint (void)
{
    /* Check whether the Rte_Read is already invoked */
    if (!Dcm_Prv_Dcm_SecaRteCallPlaced_b)
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
								 (Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
								 (Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8);

        if (Dcm_Prv_dataRetValue_u8 == RTE_E_OK)
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = TRUE;
            Dcm_Prv_dataRetValue_u8 = DCM_E_PENDING;
        }
        else
        {
            /* Set the return value to E_NOT_OK */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetValue_u8))
            {
                Dcm_Prv_dataRetValue_u8= E_NOT_OK;
            }
        }
    }
    else
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct1)
								 (Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_Resultfp))();
        if (Dcm_Prv_dataRetValue_u8 == RTE_E_OK)
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Prv_dataRetValue_u8 == RTE_E_NO_DATA)
        {
            Dcm_Prv_dataRetValue_u8 = DCM_E_PENDING;
        }
        else
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
            /* Set the return value to E_NOT_OK */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetValue_u8))
            {
                Dcm_Prv_dataRetValue_u8= E_NOT_OK;
            }
        }
    }
}
#endif
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaValidKeyNotificationToAppIsOk
*Syntax           : Dcm_Prv_SecaValidKeyNotificationToAppIsOk(Dcm_SrvOpStatusType OpStatus,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Notify OK to Application that received KEY is valid while Unlocking the security level
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
#if ((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
static FUNC(void,DCM_CODE) Dcm_Prv_SecaValidKeyNotificationToAppIsOk
						   (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                           P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
#else
static FUNC(void,DCM_CODE) Dcm_Prv_SecaValidKeyNotificationToAppIsOk
						   (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#endif
{
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
    if ((Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
    {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if (Dcm_Prv_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
			Dcm_Prv_SecaUseAsynchronousServerCallPoint();
        }
        else
#endif
       {
			/* Call the DcmAppl API to store Delay count for this security level in NVM */
			/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
			Required for efficient RAM usage by using single void function pointer */
			Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
									(Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
									(Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8);
       }
    }
#if (DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
    /* Check for infrastructure errors in case of rte*/
    if((Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR) &&
	(Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER) &&
	(Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetValue_u8) != FALSE))
    {
        /* Set the negative response */
        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
    }
    else
#endif
#endif
    {
		if(DCM_E_PENDING == Dcm_Prv_dataRetValue_u8)
		{
			Dcm_Prv_flgApplFuncCall_b = TRUE;
			Dcm_Prv_substSeca_en = DCM_DSP_SECA_PENDING;
			Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
		}
		else
		{
			/* Change operating state to PROCESSSERVICE */
			*OpStatus = DCM_PROCESSSERVICE;
		}
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaUnlockSecurityLvl
*Syntax           : Dcm_Prv_SecaUnlockSecurityLvl(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to unlock new security level as per the tester request
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaUnlockSecurityLvl(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                       P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    *dataNegRespCode_u8 =0x00;
    Dcm_Prv_secaServRetValue_u8=E_OK;
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
    /* Reset Failed Attempt Counter */
    Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8 = 0;
    /* Give Notification to DcmAppl that KEY is VALID */

    /* Fill response bytes */
    pMsgContext->resData[0] = (Dcm_DspSecAccType_u8+1);
    pMsgContext->resDataLen = 0x1;
    /* Give Notification to DcmAppl that KEY is VALID  The appl API supports only E_OK and E_PENDING*/
    if(DCM_E_PENDING == DcmAppl_DcmSecaValidKey((uint8)Dcm_Prv_idxSecTab_qu8) )
    {
        Dcm_Prv_substSeca_en = DCM_DSP_SECA_PENDING;
    }
    else
    {
#if ((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
        Dcm_Prv_SecaValidKeyNotificationToAppIsOk(OpStatus,dataNegRespCode_u8);
#else
        Dcm_Prv_SecaValidKeyNotificationToAppIsOk(OpStatus);
#endif
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCmpKeyFailed
*Syntax           : Dcm_Prv_SecaCmpKeyFailed(Dcm_SrvOpStatusType OpStatus,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function perform following operation when comparison of key from tester with ECU internal key failed
*					a. Increment failed attempts counter in case the counter is not yet exhausted
*					b. store Delay count for this security level in NVM
*				    c. set NRC, generalreject incase of RTE infrastructure error
*.                  d. Otherwise change state to pending or processservice as per NVM store return value
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
#if ((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCmpKeyFailed (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
								P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
#else
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCmpKeyFailed (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#endif
{
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
	/* Check if failed attempt counter is not exhausted */
    if(Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8 < 0xFF)
    {
        /* Increment failed attempts counters */
        Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8++;
    }

	/* Give Notification to DcmAppl that KEY is INVALID The appl API supports only E_OK and E_PENDING*/
    if( DCM_E_PENDING == DcmAppl_DcmSecaInvalidKey((uint8)Dcm_Prv_idxSecTab_qu8))
    {
        Dcm_Prv_substSeca_en =DCM_DSP_SECA_PENDING;
    }
    else
    {
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        if ((Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if (Dcm_Prv_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
            {
                Dcm_Prv_SecaUseAsynchronousServerCallPoint();
            }
			else
#endif
			{
                /* Call the DcmAppl API to store Delay count for this security level in NVM */
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
				Required for efficient RAM usage by using single void function pointer */
                Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
										(Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
										(Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8);
            }
        }
#if (DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
        /* Check for infrastructure errors in case of rte*/
        if((Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR) &&
		(Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER) &&
		(Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetValue_u8) != FALSE))
        {
            /* Set the negative response */
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
            Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
        }
        else
#endif
#endif
        {
            if(DCM_E_PENDING==Dcm_Prv_dataRetValue_u8 )
            {
                Dcm_Prv_flgApplFuncCall_b = TRUE;
                Dcm_Prv_substSeca_en = DCM_DSP_SECA_PENDING;
                Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
            }
            else
            {
				/* Change state to PROCESSSERVICE */
				*OpStatus = DCM_PROCESSSERVICE;
            }
        }
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCmpKeyNotOk
*Syntax           : Dcm_Prv_SecaCmpKeyNotOk(Dcm_SrvOpStatusType OpStatus)
*Description      : This function is called when tester key comparison with internal key is not OK.
*					Function changes Dcm state to processservice.
*Parameter        : Dcm_SrvOpStatusType OpStatus
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCmpKeyNotOk (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
{
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
    *OpStatus = DCM_PROCESSSERVICE;
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCmpKeyNegResp
*Syntax           : Dcm_Prv_SecaCmpKeyNegResp(Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function updates the NRC CONDITIONSNOTCORRECT and set Dcm state to INITIAL
*					in case compare key returns invalid
*Parameter        : Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCmpKeyNegResp
						   (P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    if(*dataNegRespCode_u8 == 0x00u)
    {
     /* Set the negative response */
       *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
    }
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCmpKeyStatusChk
*Syntax           : Dcm_Prv_SecaCmpKeyStatusChk(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function checks the status of comparekey and invoke relevant functions
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCmpKeyStatusChk (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
													P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
									   P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	/* If the Key is valid then Unlock security level */
	if (Dcm_Prv_stCmpKey_u8 ==E_OK)
	{
		Dcm_Prv_SecaUnlockSecurityLvl(OpStatus,pMsgContext,dataNegRespCode_u8);
	}
	else if (Dcm_Prv_stCmpKey_u8 ==DCM_E_PENDING)
	{
		Dcm_Prv_SecaCmpKeyPnding(dataNegRespCode_u8);
	}
	else if (Dcm_Prv_stCmpKey_u8 ==E_NOT_OK)
	{
		Dcm_Prv_SecaCmpKeyNotOk(OpStatus);
	}
	else if (Dcm_Prv_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED)
	{
#if ((DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF) && (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF))
        Dcm_Prv_SecaCmpKeyFailed(OpStatus,dataNegRespCode_u8);
#else
        Dcm_Prv_SecaCmpKeyFailed(OpStatus);
#endif
	}
	else
	{
	    Dcm_Prv_SecaCmpKeyNegResp(dataNegRespCode_u8);
	}
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCmpKey
*Syntax           : Dcm_Prv_SecaCmpKey(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function peforms following operation in Seca substate CompareKey under checkdata state of Dcm
*                       a. To check whether the received key is Valid Key
*                       b. Check status of comapre key
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaCmpKey (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
										   P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                              P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /* Calculate the security level */
    Dcm_Prv_dataSecLevel_u8  = ((Dcm_DspSecAccType_u8+1)>>1u);

    /* Copy the security table index */
    Dcm_Prv_idxSecTab_qu8 = Dcm_DspSecTabIdx_u8;

    Dcm_Prv_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Prv_idxSecTab_qu8];

    Dcm_Prv_ptrSecaFnc_p= Dcm_Prv_ptrSecurityConfig_p->Dsp_CompareKey_fp;

    /*Set the Dcm_Prv_flgApplFuncCall_b to FALSE*/
    Dcm_Prv_flgApplFuncCall_b = FALSE;

    /* Call the function to check whether the received key is Valid Key */
    Dcm_Prv_SecaCheckdataStValidKeyChk(pMsgContext,dataNegRespCode_u8);

    /* Check for infrastructure errors in case of rte*/
    if(  (Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_stCmpKey_u8) != FALSE) &&
	((Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER) ))
    {
        /* Set the negative response */
        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
    }
	else
	{
		/* status check for compare key */
		Dcm_Prv_SecaCmpKeyStatusChk(OpStatus,pMsgContext,dataNegRespCode_u8);
	}
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaAsyncServerCallPointChkForGetSeed
*Syntax           : Dcm_Prv_SecaAsyncServerCallPointChkForGetSeed
*					(Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to Check if Asynchronous server point handling is requested for the current security row
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_SecaAsyncServerCallPointChkForGetSeed
							(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                             P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /* Check whether the Rte_Read is already invoked */
    if (!Dcm_Prv_Dcm_SecaRteCallPlaced_b)
    {
        if(Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8!=0)
        {
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u)
            /* Call the Rte_Call API configured for this security level */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
			Required for efficient RAM usage by using single void function pointer */
            Dcm_Prv_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr5)(Dcm_Prv_ptrSecaFnc_p))(&(Dcm_InParameterBuf_au8[0]),
										Dcm_DspSecaOpStatus_u8);
#endif
        }
        else
        {
            /* Call the Rte_Call API configured for this security level */
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
			Required for efficient RAM usage by using single void function pointer */
            Dcm_Prv_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr6)(Dcm_Prv_ptrSecaFnc_p))(Dcm_DspSecaOpStatus_u8);
        }

        if (Dcm_Prv_dataRetGetSeed_u8 == RTE_E_OK)
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = TRUE;
            Dcm_Prv_dataRetGetSeed_u8 = DCM_E_PENDING;
        }
        else
        {
            /* IF the return value is other than E_OK then set NRC to General Reject */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetGetSeed_u8))
            {
                Dcm_Prv_dataRetGetSeed_u8= E_NOT_OK;
            }
        }
    }
    else
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr7)(Dcm_Prv_ptrSecurityConfig_p->Dsp_GetSeed_ResultFp))
									(&(pMsgContext->resData[1]),dataNegRespCode_u8);
        if (Dcm_Prv_dataRetGetSeed_u8 == RTE_E_OK)
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Prv_dataRetGetSeed_u8 == RTE_E_NO_DATA)
        {
            Dcm_Prv_dataRetGetSeed_u8 = DCM_E_PENDING;
        }
        else
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
            /* Set the NRC to General Reject for any other Return value */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetGetSeed_u8))
            {
                Dcm_Prv_dataRetGetSeed_u8= E_NOT_OK;
            }
        }
    }
}
#endif
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_GenerateSeedAsynchClientServer
*Syntax           : Dcm_Prv_GenerateSeedAsynchClientServer
*					(Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to Generate seed in checkdata state for RTE ASYNCH_CLIENT_SERVER configuration
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_GenerateSeedAsynchClientServer
						   (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                            P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    if(Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER)
    {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        /* Check whether Asynchronous server point handling is requested for the current security row */
        if (Dcm_Prv_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Prv_SecaAsyncServerCallPointChkForGetSeed(pMsgContext,dataNegRespCode_u8);
        }
        else
#endif
        {
            if(Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8!=0)
            {
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u)
                /* Call the RTE port configured for this security level */
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
				Required for efficient RAM usage by using single void function pointer */
                Dcm_Prv_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr)(Dcm_Prv_ptrSecaFnc_p))( &(Dcm_InParameterBuf_au8[0]),
                            Dcm_DspSecaOpStatus_u8,&(pMsgContext->resData[1]),dataNegRespCode_u8);
#endif
            }
            else
            {
                /* Call the RTE port configured for this security level */
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
				Required for efficient RAM usage by using single void function pointer */
                Dcm_Prv_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr3)(Dcm_Prv_ptrSecaFnc_p))(Dcm_DspSecaOpStatus_u8,
                            &(pMsgContext->resData[1]),dataNegRespCode_u8);
            }
        }
    }
}
#endif
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_GenerateSeedAsynchFnc
*Syntax           : Dcm_Prv_GenerateSeedAsynchFnc
*					(Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to Generate seed in checkdata state for RTE configuration USE_ASYNCH_FNC
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_GenerateSeedAsynchFnc
							(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    if(Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_FNC)
    {
        if(Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8!=0)
        {
#if (DCM_CFG_IN_PARAM_MAXLEN > 0u)
         /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
			Required for efficient RAM usage by using single void function pointer */
            Dcm_Prv_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr4)(Dcm_Prv_ptrSecurityConfig_p->Dsp_GetSeed_fp))(
                Dcm_Prv_dataSecLevel_u8,               			/* Security Level */
                Dcm_Prv_nrSeedLen_u8, 							/* Seed size */
                Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8, /* ADR size */
                &(Dcm_InParameterBuf_au8[0]),				    /* Security Access Data Record */
                &(pMsgContext->resData[1]), 					/* Buffer for Seed */
                Dcm_DspSecaOpStatus_u8,
                dataNegRespCode_u8);
#endif
        }
        else
        {
            /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
			Required for efficient RAM usage by using single void function pointer */
            Dcm_Prv_dataRetGetSeed_u8 = (*(Dcm_GetSeed_ptr4)(Dcm_Prv_ptrSecaFnc_p))(
                Dcm_Prv_dataSecLevel_u8,               			/* Security Level */
                Dcm_Prv_nrSeedLen_u8, 							/* Seed size */
                Dcm_Prv_ptrSecurityConfig_p->AccDataRecsize_u8,	/* ADR size */
                NULL_PTR,										/* Security Access Data Record */
                &(pMsgContext->resData[1]), 					/* Buffer for Seed */
                Dcm_DspSecaOpStatus_u8,
                dataNegRespCode_u8);
        }
	}
}
#endif
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_GetSeedReturnedWoError
*Syntax           : Dcm_Prv_GetSeedReturnedWoError(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
*					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to Generate seed in checkdata state for RTE configuration ASYNCH_CLIENT_SERVER
*					and seed was returned without any error.
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE)Dcm_Prv_GetSeedReturnedWoError(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                       P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                       P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    /* Local Loop variable for Seed index  */
    VAR(uint8_least,AUTOMATIC)      l_idxSeed_qu8;
#endif
    *dataNegRespCode_u8 = 0x00;
    Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;

    /* Update the response data */
    pMsgContext->resData[0] = Dcm_DspSecAccType_u8;
    pMsgContext->resDataLen = (uint32)((uint32)Dcm_Prv_nrSeedLen_u8 + 1u);

    /* Check if the Seed has to be stored for use in Request key state */
    /* If enabled and seed is requested for same Access Type in Key state,stored seed will be sent */
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    /* Loop for the seed size for this Access Type */
    for(l_idxSeed_qu8=0x0; (l_idxSeed_qu8 < Dcm_Prv_nrSeedLen_u8); l_idxSeed_qu8++)
    {
        /* Store the seed for use in Request KEY state */
        Dcm_Dsp_Seca[Dcm_DspSecTabIdx_u8].SeedBuff[l_idxSeed_qu8] = pMsgContext->resData[l_idxSeed_qu8 + 0x1u];
    }
#endif
    /* Move to Request Key state */
    *OpStatus = DCM_INITIAL;
    Dcm_Prv_secaServRetValue_u8=E_OK;
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaGenSeed
*Syntax           : Dcm_Prv_SecaGenSeed(Dcm_MsgContextType pMsgContext,Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : Function to Generate seed in checkdata state
*Parameter        : Dcm_MsgContextType pMsgContext, Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaGenSeed (P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                               P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Prv_ptrSecurityConfig_p= &Dcm_Dsp_Security[Dcm_DspSecTabIdx_u8];
    Dcm_Prv_ptrSecaFnc_p = Dcm_Prv_ptrSecurityConfig_p->Dsp_GetSeed_fp;
    /* State to calculate and send the seed value */
    Dcm_Prv_dataRetGetSeed_u8 = E_NOT_OK;
    /* Copy the seed length to local variable */
    Dcm_Prv_nrSeedLen_u8  = Dcm_Prv_ptrSecurityConfig_p->Seed_size_u8;
#if(DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
    Dcm_Prv_GenerateSeedAsynchClientServer(pMsgContext,dataNegRespCode_u8);
#endif

#if(DCM_CFG_DSP_USE_ASYNCH_FNC != DCM_CFG_OFF)
    Dcm_Prv_GenerateSeedAsynchFnc (pMsgContext,dataNegRespCode_u8);
#endif
#if (DCM_CFG_DSP_USE_ASYNCH_CLIENT_SERVER != DCM_CFG_OFF)
    /* Check for infrastructural errors, in case of RTE */
    if((Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetGetSeed_u8)  != FALSE)\
	    &&((Dcm_Prv_ptrSecurityConfig_p->usePort == USE_ASYNCH_CLIENT_SERVER)))
    {
        Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
        /* Set the negative response */
        *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
    }
#endif
    /* Check if the Negative response is not set by the application */
    /* Check if the seed was returned with out any errors */
    if(Dcm_Prv_dataRetGetSeed_u8 == E_OK)
    {
        Dcm_Prv_GetSeedReturnedWoError (&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);
    }
    else if(Dcm_Prv_dataRetGetSeed_u8 == DCM_E_PENDING)
    {
        *dataNegRespCode_u8 = 0x00u;
        Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
        Dcm_DspSecaOpStatus_u8 = DCM_PENDING;
    }
    else
    {
        if(*dataNegRespCode_u8 == 0x00u)
        {
            /* Set the negative response */
            *dataNegRespCode_u8 = DCM_E_GENERALREJECT;
        }
            Dcm_DspSecaOpStatus_u8 = DCM_INITIAL;
    }
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaUseAsyncServerCallPointForSetSecaAttptCntr
*Syntax           : Dcm_Prv_SecaUseAsyncServerCallPointForSetSecaAttptCntr(void)
*Description      : For AsynchronousServerCallPoint, Store security attempt counter in NVM using application function
*Parameter        : None
*Return value     : None
************************************************************************************************************************
*/
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_SecaUseAsyncServerCallPointForSetSecaAttptCntr(void)
{
	/* Check whether the Rte_Read is already invoked */
    if (!Dcm_Prv_Dcm_SecaRteCallPlaced_b)
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
									(Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
									(Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8);
		if (Dcm_Prv_dataRetValue_u8 == RTE_E_OK)
		{
			Dcm_Prv_Dcm_SecaRteCallPlaced_b = TRUE;
			Dcm_Prv_dataRetValue_u8 = DCM_E_PENDING;
        }
        else
        {
            /* Set the return value to E_NOT_OK */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetValue_u8))
            {
				Dcm_Prv_dataRetValue_u8= E_NOT_OK;
            }
        }
    }
    else
    {
        /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
		Required for efficient RAM usage by using single void function pointer */
        Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct1)
									(Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_Resultfp))();
        if (Dcm_Prv_dataRetValue_u8 == RTE_E_OK)
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
        }
        else if(Dcm_Prv_dataRetValue_u8 == RTE_E_NO_DATA)
        {
            Dcm_Prv_dataRetValue_u8 = DCM_E_PENDING;
        }
        else
        {
            Dcm_Prv_Dcm_SecaRteCallPlaced_b = FALSE;
            /* Set the return value to E_NOT_OK */
            if(!Dcm_IsInfrastructureErrorPresent_b(Dcm_Prv_dataRetValue_u8))
            {
                Dcm_Prv_dataRetValue_u8= E_NOT_OK;
            }
        }
    }
}
#endif
#endif

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaStoreDelayCountTrue
*Syntax           : Dcm_Prv_SecaStoreDelayCountTrue(Dcm_SrvOpStatusType OpStatus)
*Description      : Invoked in case DcmAppl_StoreDelayCount called in seca pending state returned TRUE
*                   and Call the application  API to store Delay count for this security level in NVM
*Parameter        : Dcm_SrvOpStatusType OpStatus
*Return value     : None
************************************************************************************************************************
*/
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
static FUNC(void,DCM_CODE) Dcm_Prv_SecaStoreDelayCountTrue(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA)OpStatus)
{
	Dcm_Prv_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Prv_idxSecTab_qu8];
    if ((Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
    {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
        if (Dcm_Prv_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
        {
            Dcm_Prv_SecaUseAsyncServerCallPointForSetSecaAttptCntr();
        }
        else
#endif
        {
			/* Call the application  API to store Delay count for this security level in NVM */
			/* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
			Required for efficient RAM usage by using single void function pointer */
			Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
			(Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
			(Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8);
        }
    }
    if((Dcm_Prv_dataRetValue_u8 == E_OK)||(Dcm_Prv_dataRetValue_u8 == E_NOT_OK))
    {
        Dcm_Prv_flgApplFuncCall_b = FALSE;
        *OpStatus = DCM_PROCESSSERVICE;
    }
    else
    {
        Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
    }
}
#endif
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaStoreDelayCountFalseCmpKeyOk
*Syntax           : Dcm_Prv_SecaStoreDelayCountFalseCmpKeyOk(Dcm_SrvOpStatusType OpStatus)
*Description      : Call the application  API to store Delay count for the selected
*                   security level in NVM as per the return value of API DcmAppl_DcmSecaValidKey()
*Parameter        : Dcm_SrvOpStatusType OpStatus
*Return value     : None
************************************************************************************************************************
*/
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
	static FUNC(void,DCM_CODE) Dcm_Prv_SecaStoreDelayCountFalseCmpKeyOk
							(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
	static FUNC(void,DCM_CODE) Dcm_Prv_SecaStoreDelayCountFalseCmpKeyOk (void)
#endif
{
	/*The appl API supports only E_OK and E_PENDING*/
    Dcm_Prv_dataRetValue_u8 = DcmAppl_DcmSecaValidKey((uint8)Dcm_Prv_idxSecTab_qu8);
    if((Dcm_Prv_dataRetValue_u8 == E_OK)||(Dcm_Prv_dataRetValue_u8 == E_NOT_OK))
    {
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
		if ((Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if (Dcm_Prv_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
            {
                Dcm_Prv_SecaUseAsyncServerCallPointForSetSecaAttptCntr();
            }
            else
#endif
            {
				/* Call the application  API to store Delay count for this security level in NVM */
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
				Required for efficient RAM usage by using single void function pointer */
                Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
				(Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
				(Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8);
            }
        }
        if(DCM_E_PENDING == Dcm_Prv_dataRetValue_u8)
        {
            Dcm_Prv_flgApplFuncCall_b = TRUE;
            Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
            Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
			/*Do nothing -remain in the same state*/
        }
        else
        {
            Dcm_Prv_flgApplFuncCall_b = FALSE;
            *OpStatus = DCM_PROCESSSERVICE;
        }
#endif
    }
    else
    {
        Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
    }
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaStoreDelayCountFalseCmpKeyFailed
*Syntax           : Dcm_Prv_SecaStoreDelayCountFalseCmpKeyFailed(Dcm_SrvOpStatusType OpStatus)
*Description      : Function to store security attempt counter to NVM using application
*                   as per the return value of API DcmAppl_DcmSecaInvalidKey in case compkey failed
*Parameter        : Dcm_SrvOpStatusType OpStatus
*Return value     : None
************************************************************************************************************************
*/
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
	static FUNC(void,DCM_CODE) Dcm_Prv_SecaStoreDelayCountFalseCmpKeyFailed
							(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
	static FUNC(void,DCM_CODE) Dcm_Prv_SecaStoreDelayCountFalseCmpKeyFailed (void)
#endif
{
    /*The appl API supports only E_OK and E_PENDING*/
    Dcm_Prv_dataRetValue_u8 = DcmAppl_DcmSecaInvalidKey((uint8)Dcm_Prv_idxSecTab_qu8);
    if((Dcm_Prv_dataRetValue_u8 == E_OK)||(Dcm_Prv_dataRetValue_u8 == E_NOT_OK))
    {
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        if ((Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp!=NULL_PTR))
        {
#if(DCM_CFG_DSP_SECA_ASP_ENABLED != DCM_CFG_OFF)
            if (Dcm_Prv_ptrSecurityConfig_p->UseAsynchronousServerCallPoint_b)
            {
                Dcm_Prv_SecaUseAsyncServerCallPointForSetSecaAttptCntr();
            }
            else
#endif
            {
                /* Call the application  API to store Delay count for this security level in NVM */
                /* MR12 RULE 11.1 VIOLATION: Typecast to function pointer required for implementation -
				Required for efficient RAM usage by using single void function pointer */
                Dcm_Prv_dataRetValue_u8 =(*(Dcm_SetSecurityAttemptCounter_pfct)
				(Dcm_Prv_ptrSecurityConfig_p->Dsp_SetAttempCounter_fp))
				(Dcm_DspSecaOpStatus_u8, Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8);
            }
        }
        if(DCM_E_PENDING == Dcm_Prv_dataRetValue_u8)
        {
            Dcm_Prv_flgApplFuncCall_b = TRUE;
            Dcm_DspSecaOpStatus_u8 =DCM_PENDING;
            Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
            /*Do nothing -remain in the same state*/
        }
        else
        {
            Dcm_Prv_flgApplFuncCall_b = FALSE;
            *OpStatus = DCM_PROCESSSERVICE;
        }
#endif
    }
    else
    {
        Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaStoreDelayCountFalse
*Syntax           : Dcm_Prv_SecaStoreDelayCountFalse(Dcm_SrvOpStatusType OpStatus)
*Description      : Invoked incase DcmAppl_StoreDelayCount called in pending state returned FALSE
*                   based on return value of compare key relevant functions are called to store the
*                   delay count in NVM using application function
*Parameter        : Dcm_SrvOpStatusType OpStatus
*Return value     : None
************************************************************************************************************************
*/
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
	static FUNC(void,DCM_CODE) Dcm_Prv_SecaStoreDelayCountFalse
								(P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
	static FUNC(void,DCM_CODE) Dcm_Prv_SecaStoreDelayCountFalse (void)
#endif
{
    if(Dcm_Prv_stCmpKey_u8 == E_OK)
    {
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
		Dcm_Prv_SecaStoreDelayCountFalseCmpKeyOk(OpStatus);
#else
		Dcm_Prv_SecaStoreDelayCountFalseCmpKeyOk();
#endif
    }
    if(Dcm_Prv_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED)
    {
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
    Dcm_Prv_SecaStoreDelayCountFalseCmpKeyFailed(OpStatus);
#else
	Dcm_Prv_SecaStoreDelayCountFalseCmpKeyFailed();
#endif
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaPending
*Syntax           : Dcm_Prv_SecaPending(Dcm_SrvOpStatusType OpStatus)
*Description      : Seca pending substate under Dcm checkdata state store delay count in NVM using application
*					function as per the return value of DcmAppl_StoreDelayCount()
*Parameter        : Dcm_SrvOpStatusType OpStatus
*Return value     : None
************************************************************************************************************************
*/
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
	static FUNC(void,DCM_CODE)  Dcm_Prv_SecaPending (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
#else
	static FUNC(void,DCM_CODE)  Dcm_Prv_SecaPending (void)
#endif
{
    Dcm_Prv_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Prv_idxSecTab_qu8];
    if(FALSE != Dcm_Prv_flgApplFuncCall_b)
    {
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        Dcm_Prv_SecaStoreDelayCountTrue(OpStatus);
#endif
    }
    else
    {
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        Dcm_Prv_SecaStoreDelayCountFalse(OpStatus);
#else
		Dcm_Prv_SecaStoreDelayCountFalse();
#endif
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaCheckData
*Syntax           : Dcm_Prv_SecaCheckData(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : This function is invoked when Dcm state is DCM_CHECKDATA
*                   Seca has substates - COMPAREKEY, GENSEED, PENDING in DCM_CHECKDATA state
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Return value     : None
************************************************************************************************************************
*/
	static FUNC(void,DCM_CODE) Dcm_Prv_SecaCheckData (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{

    if (Dcm_Prv_substSeca_en == DCM_DSP_SECA_COMPAREKEY)
    {
        /* Compare Key subState of CHECKDATA state */
        Dcm_Prv_SecaCmpKey(OpStatus,pMsgContext,dataNegRespCode_u8);
    }

    if (Dcm_Prv_substSeca_en == DCM_DSP_SECA_GENSEED)
    {
        /* Generate Seed State of CHECKDATA state*/
        Dcm_Prv_SecaGenSeed(pMsgContext,dataNegRespCode_u8);
    }

    if (Dcm_Prv_substSeca_en == DCM_DSP_SECA_PENDING)
    {
        /* Pending  substate of CHECKDATA State */
#if (DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
        Dcm_Prv_SecaPending(OpStatus);
#else
		Dcm_Prv_SecaPending();
#endif
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaProcessStCmpKeyOk
*Syntax           : Dcm_Prv_SecaProcessStCmpKeyOk(Dcm_SrvOpStatusType OpStatus)
*Description      : This function is invoked in state DCM_PROCESSSERVICE when return value of application
*                   API for compare key is E_OK
*Parameter        : Dcm_SrvOpStatusType OpStatus
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaProcessStCmpKeyOk (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus)
{
#if (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    /* Local Loop variable for Seed index */
    VAR(uint8_least,AUTOMATIC)  l_idxSeed_qu8;
#endif
    /* Change state back to Request Seed state */
    *OpStatus = DCM_INITIAL;
    /* Set the Change Security Level */
    Dcm_DspChgSecLevel_b = TRUE;
    Dcm_Prv_secaServRetValue_u8=E_OK;
#if (DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    /* Clearing Stored Seed For the Security level */
    for(l_idxSeed_qu8=0x0; (l_idxSeed_qu8 < Dcm_Dsp_Security[Dcm_Prv_idxSecTab_qu8].Seed_size_u8); l_idxSeed_qu8++)
    {
        /* Store the seed for use in Request KEY state */
        Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].SeedBuff[l_idxSeed_qu8] = 0x0;
    }
#endif
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaProcessStCmpKeyFailed
*Syntax           : Dcm_Prv_SecaProcessStCmpKeyFailed(Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : This function is invoked in state DCM_PROCESSSERVICE when return
*                   value of application API for compare key is Failed
*Parameter        : Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaProcessStCmpKeyFailed
							(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    Dcm_Prv_ptrSecurityConfig_p = &Dcm_Dsp_Security[Dcm_Prv_idxSecTab_qu8];
    *dataNegRespCode_u8 = DCM_E_INVALIDKEY; /* Invalid key is received */
    /* Check if the Delay Counter value has reached the max limit */
    if((Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8) < Dcm_Prv_ptrSecurityConfig_p->NumAttDelay_u8)
    {
        *dataNegRespCode_u8 = DCM_E_INVALIDKEY; /* Invalid key is received */
    }
    if((Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8) >= Dcm_Prv_ptrSecurityConfig_p->NumAttDelay_u8)
    {
		/* Check whether DelayTime_u32 is configured with value 0 */
        if(Dcm_Prv_ptrSecurityConfig_p->DelayTime_u32 > 0x00u)
        {
			Dcm_Prv_nrDelay_u32 = ((Dcm_Prv_ptrSecurityConfig_p->DelayTime_u32) * DCM_CFG_TASK_TIME_MS);
			/* DcmAppl_DcmGetUpdatedDelayTime should return Residual Delay time in Counts of DcmTaskTime */
			Dcm_Prv_nrDelay_u32 = DcmAppl_DcmGetUpdatedDelayTime( Dcm_Prv_ptrSecurityConfig_p->Security_level_u8,
											Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8,Dcm_Prv_nrDelay_u32);
			Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].Residual_delay_u32 =
			(Dcm_Dsp_SecaGlobaltimer_u32 + (Dcm_Prv_nrDelay_u32 / DCM_CFG_TASK_TIME_MS));
		}
		else
        {
            /* Assign Residual_delay_u32 with the value 0,so that there will not be any delay effect
			and ecu will not be locked */
            Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].Residual_delay_u32 = 0x00u;
        }
#if (DCM_CFG_DSP_NRC0x36MAXDELAYCOUNT != DCM_CFG_OFF)
        *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
#else
        *dataNegRespCode_u8 = DCM_E_INVALIDKEY;
#endif
    }
    /* If Configured value for Lock count is nonzero */
    if(Dcm_Prv_ptrSecurityConfig_p->NumAttLock_u8 > 0)
    {
        /* If FailedAtm_cnt_u8 exceeds maximum count */
        if(Dcm_Dsp_Seca[Dcm_Prv_idxSecTab_qu8].FailedAtm_cnt_u8 == Dcm_Prv_ptrSecurityConfig_p->NumAttLock_u8)
        {
            /* Provide Notification to DcmAppl that Lock counter is exceeded */
            DcmAppl_DcmSecurityLevelLocked((uint8)Dcm_Prv_idxSecTab_qu8);
            *dataNegRespCode_u8 = DCM_E_EXCEEDNUMBEROFATTEMPTS;
        }
    }
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaProcesStCmpKeyNotOk
*Syntax           : Dcm_Prv_SecaProcesStCmpKeyNotOk(Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : This function is invoked in state DCM_PROCESSSERVICE when return
*                   value of application API to compare key is NOT_OK
*Parameter        : Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaProcesStCmpKeyNotOk
							(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	if(*dataNegRespCode_u8 == 0x00u)
    {
        /* Set the negative response */
        *dataNegRespCode_u8 = DCM_E_CONDITIONSNOTCORRECT;
    }
    else
    {
		/*do nothing*/
    }
}

/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaProcessService
*Syntax           : Dcm_Prv_SecaProcessService(Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : This function is invoked in Dcm state DCM_PROCESSSERVICE in case of SECA request
*                   Based on application API return value to compare key, respective function is invoked
*Parameter        : Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaProcessService
							(P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	if(Dcm_Prv_stCmpKey_u8 == E_OK)
    {
	    Dcm_Prv_SecaProcessStCmpKeyOk(&Dcm_SrvOpstatus_u8);
    }
	else if(Dcm_Prv_stCmpKey_u8 == E_NOT_OK)
	{
		Dcm_Prv_SecaProcesStCmpKeyNotOk(dataNegRespCode_u8);
	}
	else if(Dcm_Prv_stCmpKey_u8 == DCM_E_COMPARE_KEY_FAILED)
	{
	    Dcm_Prv_SecaProcessStCmpKeyFailed(dataNegRespCode_u8);
	}
	else
	{
		Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;
	}
}
/**
************************************************************************************************************************
*Function name    : Dcm_Prv_SecaStateProcessing
*Syntax           : Dcm_Prv_SecaStateProcessing(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : This function checks for Dcm states while processing the seca service
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
					Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : None
************************************************************************************************************************
*/
static FUNC(void,DCM_CODE) Dcm_Prv_SecaStateProcessing (P2VAR(Dcm_SrvOpStatusType,AUTOMATIC,DCM_INTERN_DATA) OpStatus,\
                                    P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_CONST) pMsgContext,\
                                    P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
    /* Seed / key Request state */
    if ((*OpStatus)==(DCM_INITIAL))
    {
        Dcm_Prv_SecaRequestState(pMsgContext,dataNegRespCode_u8);
    }
    /* comprises of substate Compare Key / Generate Seed /Pending  State */
    if ((*OpStatus)==(DCM_CHECKDATA))
    {
        Dcm_Prv_SecaCheckData(OpStatus,pMsgContext,dataNegRespCode_u8);
    }
    /* process the seca service */
    if ((*OpStatus)==(DCM_PROCESSSERVICE))
    {
        Dcm_Prv_SecaProcessService(dataNegRespCode_u8);
    }
}
/**
************************************************************************************************************************
*Function name    : Dcm_DcmSecurityAccess
*Syntax           : Dcm_DcmSecurityAccess(Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
					Dcm_NegativeResponseCodeType dataNegRespCode_u8)
*Description      : This function is called by DSD, when SID is set to 0x27, this service is provided in DSP module
* 					and configured in DCM identifier table. Security Access service is used to unlock a particular
*					security level when needed to process a specific service active only in certain security level.
* 					Tester will request for a seed with the security level to be unlocked, ECU will send the Seed
*					and when it gets the request key request compares the key with the internally stored key and
*					unlocks the security level if keys are same.
*Parameter        : Dcm_SrvOpStatusType OpStatus, Dcm_MsgContextType pMsgContext,
					Dcm_NegativeResponseCodeType dataNegRespCode_u8
*Return value     : Std_ReturnType
************************************************************************************************************************
 */
FUNC(Std_ReturnType,DCM_CODE) Dcm_DcmSecurityAccess (VAR(Dcm_SrvOpStatusType,AUTOMATIC) OpStatus,\
									P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA) pMsgContext,\
									P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8)
{
	VAR(Std_ReturnType,AUTOMATIC)     localdataServRetValue_u8;
#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
    Dcm_Prv_stBuffer_b = FALSE;                         /* Setting Seed Buffer State to False */
#endif
    *dataNegRespCode_u8  = 0x0;                         /* Initialise NRC to 0      */
	Dcm_Prv_substSeca_en = Dcm_DspSecaStatus_en;        /* Get the SECA sub status for Dcm state CHECKDATA  */
    Dcm_Prv_dataRetValue_u8 =E_OK;
	localdataServRetValue_u8 = DCM_E_PENDING;
    Dcm_Prv_secaServRetValue_u8=DCM_E_PENDING;

    /* If OpStatus is set to DCM_CANCEL then call the ini function for resetting */
    if (OpStatus == DCM_CANCEL)
    {
        /* Call the Ini Function */
        Dcm_Dsp_SecaIni();
        /* Set the return value to E_OK as the Ini function will always be serviced  */
        Dcm_Prv_secaServRetValue_u8 = E_OK;
    }
    else
    {
        Dcm_Prv_SecaStateProcessing(&Dcm_SrvOpstatus_u8,pMsgContext,dataNegRespCode_u8);
        /* Check if the Negative Response Code is set */
        if(*dataNegRespCode_u8 != 0x0u)
        {
            /* Move back to Request seed state */
            Dcm_SrvOpstatus_u8 = DCM_INITIAL;
			/* Reset the globals to avoid Invalid Unlock Sequence */
            Dcm_DspSecAccType_u8 = 0x0;   /* Reset Access Type Stored */
            Dcm_DspSecTabIdx_u8  = 0x0;    /* Reset the Security table index Stored */
            Dcm_Prv_secaServRetValue_u8=E_NOT_OK;
        }
		/* Update the SECA sub Status to RAM variable */
		Dcm_DspSecaStatus_en = Dcm_Prv_substSeca_en;
    }

	localdataServRetValue_u8 = Dcm_Prv_secaServRetValue_u8;
	return localdataServRetValue_u8;
}
/**
************************************************************************************************************************
*Function name    : Dcm_ResetAccessType
*Syntax           : Dcm_ResetAccessType(void)
*Description      : To Reset the stored AccessType when the NRC is returned for Seca Service(0x27) from DsdStateMachine
*Parameter        : None
*Return value     : None
************************************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_ResetAccessType (void)
{
    Dcm_DspSecAccType_u8=0;
}

#if(DCM_CFG_DSP_SECA_STORESEED != DCM_CFG_OFF)
/**
 ***********************************************************************************************************************
*Function name    : Dcm_Dsp_SecaClearSeed
*Syntax           : Dcm_Dsp_SecaClearSeed(void)
*Description      : This function clears the stored seed for all security levels.
*Parameter        : None
*Return value     : None
************************************************************************************************************************
 */
FUNC (void,DCM_CODE) Dcm_Dsp_SecaClearSeed (void)
{
    VAR (uint8_least,AUTOMATIC) idxSecTab_qu8;  /* Local variable to iterate through the security table */
    VAR (uint8_least,AUTOMATIC) SeedIdx_u8;  /* Local variable to iterate through the seed buffer */
    VAR (uint8_least,AUTOMATIC) Seedlen_u8;  /* Local variable to iterate through the seed buffer */
    for (idxSecTab_qu8=0;idxSecTab_qu8 < DCM_CFG_DSP_NUMSECURITY; idxSecTab_qu8++)
    {
        /* Obtain the seed length from the security level configuration */
        Seedlen_u8 = Dcm_Dsp_Security[idxSecTab_qu8].Seed_size_u8;
        /* Loop for the seed size for this Access Type */
        for (SeedIdx_u8=0x0; (SeedIdx_u8 < Seedlen_u8); SeedIdx_u8++)
        {
            /* Store the seed for use in Request KEY state */
            Dcm_Dsp_Seca[idxSecTab_qu8].SeedBuff[SeedIdx_u8] = 0x0;
        }
    }
}

#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#endif /*( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF )*/

