

#include "DcmCore_Main_Inf.h"
#include  "DcmDspUds_Seca_Priv.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* definition of pointers */
P2CONST(Dcm_Dsld_connType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldConnTable_pcst;
P2CONST(Dcm_Dsld_protocol_tableType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldProtocol_pcst;
P2CONST(uint8, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldRxTable_pcu8;
P2CONST(uint8, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldSessionTable_pcu8;



#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
P2CONST(Dcm_ConfigType, DCM_VAR, DCM_INTERN_CONST) Dcm_ActiveConfigSet_Ptr;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/* definition of structure containing the global variables */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_DsldInternalStructureType_tst,DCM_VAR) Dcm_DsldGlobal_st;


/* definition of structure used for cooperative scheduler */
#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
VAR(Dcm_DsldProcessCoOpScheduleType_tst,DCM_VAR) Dcm_DsldProcessCoOpSchedule_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/* Global variables to handle timer using OS Timer */
#if (DCM_CFG_OSTIMER_USE != FALSE)
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( uint32, DCM_VAR )     Dcm_P2OrS3StartTick_u32;    /* Value of ticks when request is received */
VAR( uint32, DCM_VAR )     Dcm_CurrTick_u32;    /* Current CPU ticks value */
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
VAR( uint32, DCM_VAR )     Dcm_PagedBufferStartTick_u32;    /* Starting tick value for paged buffer timer */
#endif
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
VAR( uint32, DCM_VAR )     Dcm_RoerdpiStartTick_u32;    /* Starting tick value for Roe timer */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
VAR( uint32, DCM_VAR )     Dcm_Roe2StartTick_u32;             /* Starting tick value for Roe timer */
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
VAR( uint32, DCM_VAR )     Dcm_Rdpi2StartTick_u32;            /* Starting tick value for Rdpi timer */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if ((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( uint32, DCM_VAR ) Dcm_SysPrevTick_u32;  /* Previous tick value */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR( uint32, DCM_VAR ) Dcm_SysCurrTick_u32;  /* Current tick value */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#endif

#if(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint32, DCM_VAR) Dcm_Dsp_SecaGlobaltimer_u32;
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if (DCM_CFG_POSTBUILD_SUPPORT != DCM_CFG_OFF )
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8, DCM_VAR) Dcm_ActiveConfiguration_u8;       /*GLobal variable which will hold the current active configuration*/

#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(uint8,DCM_VAR) Dcm_CurProtocol_u8;   /* Variable to Indicate the currently active protocol- used for StopProtocol in DslStateMachine */
VAR(Dcm_SesCtrlType,DCM_VAR) Dcm_CC_ActiveSession_u8; /* Global Varible to hold CC Acctivesession*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(Dcm_Dsld_activediagnostic_ten, DCM_VAR) Dcm_ActiveDiagnosticState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(boolean,DCM_VAR) Dcm_ReadyForBoot_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
VAR(boolean,DCM_VAR) Dcm_isInitialised_b;
VAR(boolean,DCM_VAR) Dcm_acceptRequests_b;
VAR(boolean,DCM_VAR) Dcm_flgCancelTransmit_b; /* Variable used for checking cancel transmit status */
VAR(boolean,DCM_VAR) Dcm_StopProtocolflag_b; /* Flag used to check invocation of StopProtocol */
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
static VAR(uint8,DCM_VAR) s_VinWaitPendingCounter_u8 = 0;   /*Indicate pending response is returned while reading VIN DID */
static VAR(Std_ReturnType, AUTOMATIC) s_VinBufferInitStatus_u8 = E_OK; /*Indicate return status for reading VIN DID  */
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/**
 **************************************************************************************************
 * Dcm_MainFunction :  DCM cyclic function called by the OS
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
FUNC(void,DCM_CODE) Dcm_MainFunction(void)
{

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
VAR(Std_ReturnType, AUTOMATIC) stGetPermTxWarmResp_u8; /* Variable to get return from DcmAppl API */
VAR(boolean,AUTOMATIC) isCallApplFunc_b; /* Variable which decides calling of DcmmAppl function */
#endif

    /*Check if DCM is initialized?*/

    if(Dcm_acceptRequests_b != FALSE)
    {
#if ((DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF))
       Dcm_MainFunctionsCheckUsedCore();
#endif

#if (DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_SECURITYACCESS_ENABLED != DCM_CFG_OFF)
    if(Dcm_Dsp_SecaGlobaltimer_u32 < 0xFFFFFFFFu)
    {
        /* If the SECA service is present in DSP */
        Dcm_Dsp_SecaGlobaltimer_u32++;
    }

#if(DCM_CFG_DSP_SECA_ATTEMPT_COUNTER!=DCM_CFG_OFF)
    if(Dcm_GetattemptCounterWaitCycle_u8 <= DCM_DSP_SECURITY_MAX_ATTEMPT_COUNTER_READOUT_TIME)
    {
            /* Call DSP function to load the Delay count values of Security levels */
            Dcm_Dsp_RestoreDelayCount();
    }
#endif

#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
        /* Check for No Communication mode in DCM */

        if(Dcm_ReadyForBoot_b != FALSE)
        {
            if(Dcm_ProgConditions_st.StoreType != DCM_NOTVALID_TYPE)
            {
                /* Set the variable to TRUE to call DcmAppl_DcmGetPermTxWarmResp API */

                isCallApplFunc_b = TRUE;

                if(Dcm_ProgConditions_st.StoreType == DCM_WARMINIT_TYPE)
                {
                    /* Set the variable to FALSE to avoid calling DcmAppl_DcmGetPermTxWarmResp API */

                    isCallApplFunc_b = FALSE;
                    /* No warm response needs to be transmitted, move to FULL COMM mode */
                    Dcm_DslDsdWarmStart();

                    /* To remove compiler warning in CC environment */
                    stGetPermTxWarmResp_u8 = E_OK;
                    (void)stGetPermTxWarmResp_u8;
                    /* Reset the variable to FALSE */

                    Dcm_ReadyForBoot_b = FALSE;
                }

                /* Application API needs to be called to get permission */

                if(isCallApplFunc_b != FALSE)
                {
                    if(DCM_CHKFULLCOMM_MODE(Dcm_DsldConnTable_pcst[Dcm_GetActiveConnectionIdx_u8()].channel_idx_u8))
                    {
                        /* Call the application API to get the permissions for transmission */
                        stGetPermTxWarmResp_u8 = DcmAppl_DcmGetPermTxWarmResp();

                        /* If the permission is given by application to transmit the warm response */
                        if(stGetPermTxWarmResp_u8 == E_OK)
                        {
                            Dcm_DslDsdWarmStart();
                            /* Reset the variable to FALSE to prevent re-entry to the loop as permission is received for transmitting response */\

                            Dcm_ReadyForBoot_b = FALSE;
                        }
                        else if(stGetPermTxWarmResp_u8 == DCM_E_PENDING)
                        {
                        /* Nothing to be done */
                        }
                        else /* E_NOT_OK */
                        {
                            /* Move to FULL COMM mode as the warm response cannot be sent */
                            /* Reset the Programming table contents */
                            Dcm_ProgConditions_st.StoreType = DCM_NOTVALID_TYPE;
                            /* Reset the variable to FALSE to prevent re-entry to the loop as permission is not received for transmitting response */

                            Dcm_ReadyForBoot_b = FALSE;
                        }
                    }
                }
            }
            else
            {
                /* State transition to FULL-COMM will happen via Dcm call-back to ComM. Nothing to be done here */
                /* Reset the variable to FALSE as the StoreType is invalid */

                Dcm_ReadyForBoot_b = FALSE;
            }
        }
        /*Check for No Communication mode in DCM*/
        if(Dcm_ReadyForBoot_b == FALSE)
        {
            /*Dcm is initialized*/
            Dcm_isInitialised_b = TRUE;
        }
#else
        /*initialized the variable*/
        Dcm_isInitialised_b = TRUE;
#endif
        /* Check if the application has requested for switching to the default session */
        Dcm_DslDsdProcessResetToDefault();

        /* check DSD is in DSD_TX_CONFIRMATION state */
        if(Dcm_DsldGlobal_st.stDsdState_en == DSD_TX_CONFIRMATION )
        {
            /* call DSD state machine to give confirmation to Application */
            Dcm_DsldDsdStateMachine();
        }
#if(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF)
        Dcm_RdpiMainFunction();
#endif
              /* call DSL state machine */
              Dcm_DsldDslStateMachine();


            /* call DSD state machine */
            Dcm_DsldDsdStateMachine();
#if(((DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF)) || (( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF )))
            /* Call state machine for CC and CDTCS related mode check*/
            Dcm_DsldDspModeStateMachine();
#endif

#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )
              /* Call CC Mainfunction*/
              Dcm_Prv_CC_Mainfunction();
#endif

#if((DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF) && (DCM_ROE_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
        if(Dcm_DsdRoe2State_en != DSD_IDLE)
        {
            /* Roe type 2 handling */
            Dcm_DsldRoe2StateMachine();
        }
        else
        {
            Dcm_DsldProcessRoeQueue();
        }
#else
        if((Dcm_DsldGlobal_st.stDslState_en == DSL_READY_FOR_RECEPTION)&& (Dcm_DsldGlobal_st.stDsdState_en == DSD_IDLE) )
        {

            Dcm_DsldProcessRoeQueue();
        }

#endif
#endif

#if((DCM_CFG_VIN_SUPPORTED != DCM_CFG_OFF) && (DCM_CFG_DIDSUPPORT != DCM_CFG_OFF))
          /* Read VIN DID During Startup */
        /* Check if VIN DID is already read */
        if(Dcm_VinReceived_b != TRUE)
        {
              /*Check if Dcm_VinBuffer_Init return status is E_OK or DCM_E_PENDING */
            if((s_VinBufferInitStatus_u8 == E_OK) || ((s_VinBufferInitStatus_u8 == DCM_E_PENDING) && ( s_VinWaitPendingCounter_u8 < DCM_CFG_MAX_WAITPEND)))
            {
                s_VinBufferInitStatus_u8 = Dcm_VinBuffer_Init();
                 /*Increament counter value if server needs more time to read */
                if(s_VinBufferInitStatus_u8 == DCM_E_PENDING)
                {
                    s_VinWaitPendingCounter_u8++;
                }
            }
        }

#endif
    }
}


/**
 **************************************************************************************************
 * Dcm_CoOpr_MainFunction()  :  DCM cyclic function called by the OS.This function is cooperative
   compared to the context of Dcm_MainFunction i.e. it will not interrupt Dcm_MainFunction().
   But Dcm_MainFunction() can interrupt this function
 * \param           None
 *
 *
 * \retval          None
 * \seealso
 * \usedresources
 **************************************************************************************************
 */
#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)

FUNC(void,DCM_CODE) Dcm_CoOpr_MainFunction(void)
{
    VAR(Dcm_DsldProcessCoOpScheduleType_tst,DCM_VAR) dataProcessCoOpSchedule_st;
    /* Pointer to service table */
    P2CONST(Dcm_Dsld_ServiceType,AUTOMATIC,DCM_INTERN_CONST) adrServiceTable_pcst;
    /* index for loop */
    VAR(uint8_least,AUTOMATIC) idxIndex_qu8;
    /* number of services in Service table */
    VAR(uint8,AUTOMATIC) nrServices_u8;
    VAR(Dcm_DsldDsdStatesType_ten,AUTOMATIC) stDsdState_en;
    VAR(Dcm_NegativeResponseCodeType,AUTOMATIC) dataNegRespcode_u8;

    /*Check if DCM is initialized?*/

    if(Dcm_acceptRequests_b != FALSE)
    {
    #if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
        Dcm_MainFunctionsCheckUsedCore();
    #endif
        /* Read current state of DSD */
        stDsdState_en = Dcm_DsldGlobal_st.stDsdState_en;
        dataProcessCoOpSchedule_st = Dcm_DsldProcessCoOpSchedule_st;
        Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8 = 0x00;

        /* Service initialisation function called because of General Reject */
         if ((dataProcessCoOpSchedule_st.flgPendingRequest_u8 & DCM_DSLD_COOPSCHEDULER_SERVICE_INI) != 0x00u)
        {
            (void)(*dataProcessCoOpSchedule_st.adrServiceHandler_pfct)(DCM_CANCEL,&Dcm_DsldMsgContext_st,&dataNegRespcode_u8);
        }
        /* service initialisation functions should be called */
        /*MR12 RULE 14.4 VIOLATION: Controlling expression is not 'essentially Boolean' expression. MISRA C:2012 Rule-14.4 */
        if ((dataProcessCoOpSchedule_st.flgPendingRequest_u8 & DCM_DSLD_COOPSCHEDULER_INI) != 0x00u)
        {
            adrServiceTable_pcst = \
                Dcm_Dsld_Conf_cs.sid_table_pcs[dataProcessCoOpSchedule_st.idxServiceTableIndex_u8].ptr_service_table_pcs;
            /* get the number of services in the service table */
            nrServices_u8 = \
                Dcm_Dsld_Conf_cs.sid_table_pcs[dataProcessCoOpSchedule_st.idxServiceTableIndex_u8].num_services_u8;
            /* call the ini's of all services that uses cooperative scheduler, in service table */
            for(idxIndex_qu8 = nrServices_u8; idxIndex_qu8 !=0u ; idxIndex_qu8--)
            {
                /* Call the corresponding service initialisation function from here only if mainscheduler_b is FALSE */

                if((adrServiceTable_pcst->Service_init_fp != NULL_PTR) &&  (adrServiceTable_pcst->mainscheduler_b == FALSE))
                {
                    /* Call the corresponding service initialisation function */
                    (*(adrServiceTable_pcst->Service_init_fp))();
                }

                adrServiceTable_pcst++;
            }

        }

        if ((stDsdState_en == DSD_CALL_SERVICE) &&
        ((dataProcessCoOpSchedule_st.flgPendingRequest_u8 & DCM_DSLD_COOPSCHEDULER_SERVICE) == DCM_DSLD_COOPSCHEDULER_SERVICE))
        {
            (void)(*dataProcessCoOpSchedule_st.adrServiceHandler_pfct)(DCM_INITIAL,&Dcm_DsldMsgContext_st,&dataNegRespcode_u8);
        }
    }
}

#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

