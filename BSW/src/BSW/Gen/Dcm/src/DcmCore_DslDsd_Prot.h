

#ifndef DCMCORE_DSLDSD_PROT_H
#define DCMCORE_DSLDSD_PROT_H


/**************************************************************************************************/
/* Included  header files                                                                         */
/**************************************************************************************************/

#if (DCM_CFG_DSP_NVRAM_ENABLED != DCM_CFG_OFF)
#include "NvM.h"
#endif
 #if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#include "Det.h"
#endif
/*
 ***************************************************************************************************
 *    Internal  definitions
 ***************************************************************************************************
 */
/* Endianness conversion for UINT16/SINT16 data */

#define DCM_ENDIANNESSCONVERSION16(data) ((data) = rba_BswSrv_ByteOrderSwap16((uint16)(data)))
/* Endianness conversion for UINT32/SINT32 data */

#define DCM_ENDIANNESSCONVERSION32(data) ((data) = rba_BswSrv_ByteOrderSwap32(data))

/* Abstraction to the MemSet and MemCopy Library function */
#define DCM_MEMCOPY(xDest_pv,xSrc_pcv,numBytes_u32)         (void)rba_BswSrv_MemCopy((xDest_pv),(xSrc_pcv),(uint32)(numBytes_u32))
#define DCM_MEMSET(xDest_pv,xPattern_u32,numBytes_u32)              (void)rba_BswSrv_MemSet((xDest_pv),(xPattern_u32),(uint32)(numBytes_u32))
#define DCM_UNUSED_PARAM(P)   ((void)(P))

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
/* Types of storing used for Jump to Boot */
#define DCM_NOTVALID_TYPE     0x00u  /* Boot Loader is not active */
#define DCM_WARMREQUEST_TYPE  0x01u  /* Warm Request Type */
#define DCM_WARMINIT_TYPE     0x02u  /* Warm Init Type */
#define DCM_WARMRESPONSE_TYPE 0x03u  /* Warm Response Type */
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_ProgConditionsType,  DCM_VAR) Dcm_ProgConditions_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)
typedef enum
{
    DCM_BOOT_IDLE = 0,           /* IDLE state */
    DCM_BOOT_PROCESS_RESET,      /* Process the Store Type and Trigger Force Response Pend */
    DCM_BOOT_SENDFORCEDRESPPEND, /* State where ForcedRespPend can be triggered */
    DCM_BOOT_WAIT,               /* Wait for confirmation of Response Pend */
    DCM_BOOT_STORE_WARMREQ,      /* Store Request for Warm Request type */
    DCM_BOOT_STORE_WARMINIT,     /* Store protocol information for Warm Init Type */
    DCM_BOOT_STORE_WARMRESP,     /* Store Response for Warm Response Type */
    DCM_BOOT_ERROR,              /* Process the error happened before the jump */
    DCM_BOOT_WAIT_FOR_RESET,     /* Wait till the reset happens*/
    DCM_BOOT_PERFORM_RESET,       /* State to do reset in case of Warm Request/Response */
    DCM_BOOT_PREPARE_RESET       /* State to check for conditions to send Forced RespPend before reset for  Warm Request/Response */
}Dcm_BootLoaderStates_ten;

#define DCM_JUMPTOOEMBOOTLOADER            0x00u
#define DCM_JUMPTOSYSSUPPLIERBOOTLOADER 0x01u
#define DCM_JUMPDRIVETODRIVE            0x02u
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_BootLoaderStates_ten,  DCM_VAR) Dcm_BootLoaderState_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_JumpToBootLoader(VAR(uint8,AUTOMATIC) dataBootType_u8,P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA) dataNegRespCode_u8);
extern FUNC(void,DCM_CODE) Dcm_ResetBootLoader(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/* FC_VariationPoint_START */
/* API ID for OBD services in order to report development errors to DET module */
#define DCM_OBDMODE01_ID    0x81u
#define DCM_OBDMODE02_ID    0x82u
#define DCM_OBDMODE37A_ID   0x83u
#define DCM_OBDMODE04_ID    0x84u
#define DCM_OBDMODE06_ID    0x86u
#define DCM_OBDMODE08_ID    0x88u
#define DCM_OBDMODE09_ID    0x89u
/* FC_VariationPoint_END */

/* API ID for read did in order to report development errors to DET module */
#define DCM_RDBI_ID         0x8Au

#define DCM_WARMSTART_ID        0x8Bu
#define DCM_BOOTLOADER_ID       0x8Cu
#define DCM_COPYRXDATA_ID       0x8Du
#define DCM_KWPTIMING_ID        0x8Eu
#define DCM_PAGEDBUFFER_ID      0x8Fu
#define DCM_RDPI_ID             0x90u
#define DCM_ROE_ID              0x91u
#define DCM_ROEPROCESS_ID       0x92u
#define DCM_TPRXIND_ID          0x93u
#define DCM_SETSRVTABLE_ID      0x94u
#define DCM_SETSESSION_ID       0x95u
#define DCM_PROCESSINGDONE_ID   0x96u
#define DCM_CC_ID               0x97u
#define DCM_CDTCS_ID            0x98u
#define DCM_DDDI_ID             0x99u
#define DCM_DSC_ID              0x9Au
#define DCM_GETP2TIMINGS_ID     0x9Bu
#define DCM_ER_ID               0x9Cu
#define DCM_IOCBI_ID            0x9Du
#define DCM_WDBI_ID             0x9Eu
#define DCM_COPYTXDATA_ID       0x9Fu
#define DCM_CHKUSEDCOREMAIN_ID  0xA0u
#define DCM_TRANSFERDATA_ID     0xA1u
#define DCM_TRANSFEREXIT_ID     0xA2u
#define DCM_STARTOFRECEPTION_ID 0xA3u
#define DCM_TPTXCONFIRMATION_ID 0xA4u
#define DCM_TPRXINDICATION_ID   0xA5u
#define DCM_SETSECURITYLEVEL    0xA6u
#define DCM_SETSESSIONLEVEL     0xA7u
#define DCM_RDTC_ID             0xA8u
/* error ids for DET API interfaces, OBD services report the development errors to DET module */
#define DCM_E_INTERFACE_TIMEOUT                   0x01u
#define DCM_E_INTERFACE_RETURN_VALUE              0x02u
#define DCM_E_INTERFACE_BUFFER_OVERFLOW           0x03u
#define DCM_E_UNINIT                              0x05u
#define DCM_E_PARAM                               0x06u
#define DCM_E_PARAM_POINTER                       0x07u
#define DCM_E_INIT_FAILED                         0x08u
#define DCM_E_SET_PROG_CONDITIONS_FAIL            0x09u
#define DCM_E_MIXED_MODE                          0x0Au
#define DCM_E_WRONG_STATUSVALUE                   0x0Bu
#define DCM_E_PROTOCOL_NOT_FOUND                  0x0Cu
#define DCM_E_NVM_UPDATION_NOT_OK                 0x0Du
#define DCM_E_FULLCOMM_DISABLED                   0x0Eu
#define DCM_E_PROTOCOL_NOT_STARTED                0x10u
#define DCM_E_PSUEDO_RECEPTION                    0x11u
#define DCM_E_SERVICE_TABLE_NOT_SET               0x12u
#define DCM_E_SESSION_NOT_CONFIGURED              0x13u
#define DCM_E_SUBNET_NOT_SUPPORTED                0x14u
#define DCM_E_DDDI_NOT_CONFIGURED                 0x15u
#define DCM_E_EXCEEDED_MAX_RECORDS                0x16u
#define DCM_E_NOT_SUPPORTED_IN_CURRENT_SESSION    0x17u
#define DCM_E_INVALID_ADDRLENGTH_FORMAT           0x18u
#define DCM_E_CONTROL_FUNC_NOT_CONFIGURED         0x19u
#define DCM_E_INVALID_CONTROL_PARAM               0x1Au
#define DCM_E_NO_WRITE_ACCESS                     0x1Bu
#define DCM_E_RET_E_INFRASTRUCTURE_ERROR          0x1Cu
#define DCM_E_INVALID_CONTROL_DATA                0x1Du
/* error Ids for DET API interfaces, Rdbi service report the development errors to DET module */
#define DCM_E_RET_E_NOT_OK                        0x1Eu
/*Error ID for reporting parallel processing of main,co-op main functions*/
#define DCM_E_PARALLEL_PROCESSING_ID              0x1Fu
#define DCM_E_DCMRXPDUID_RANGE_EXCEED             0x20u
#define DCM_E_DCMTXPDUID_RANGE_EXCEED             0x21u
#define DCM_E_NO_READ_ACCESS                      0x22u
#define DCM_E_SERVICE_TABLE_OUTOFBOUNDS           0x23u
#define DCM_E_SECURITYLEVEL_OUTOFBOUNDS           0x24u
#define DCM_E_RET_E_PENDING                       0x25u
#define DCM_E_INVALID_LENGTH                      0x26u
#define DCM_E_FORCE_RCRRP_IN_SILENT_COMM          0x27u
typedef uint8  Dcm_ReturnClearDTCType_tu8;

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Std_ReturnType,DCM_VAR) Dcm_retVal_u8;

#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_SrvOpStatusType ,DCM_VAR) Dcm_SrvOpstatus_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/*Service handler uses below mentioned DET API interface function to report the development error to DET Module */
#if (DCM_CFG_DET_SUPPORT_ENABLED != DCM_CFG_OFF)
#define     DCM_DET_ERROR(DCM_ApiId, DCM_ErrorId)                                 \
                                        (void)Det_ReportError(DCM_MODULE_ID, DCM_INSTANCE_ID, DCM_ApiId, DCM_ErrorId);
#else
#define     DCM_DET_ERROR(DCM_ApiId, DCM_ErrorId)
#endif


/*
 ***************************************************************************************************
 *    Function prototypes (APIs of DCM which is used only in DSP)
 ***************************************************************************************************
 */
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSecurityMask_u32 (void);
extern FUNC(uint32, DCM_CODE) Dcm_DsldGetActiveSessionMask_u32 (void);

extern FUNC(void,DCM_CODE) Dcm_DslDsdConfirmRespPend(
		VAR(uint8,AUTOMATIC) dataSid_u8,
		VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status_u8
													);

extern FUNC(void,DCM_CODE) Dcm_DsldSetsessionTiming(
                                                      VAR(uint32, AUTOMATIC) nrP2StarMax_u32,
                                                      VAR(uint32, AUTOMATIC) nrP2Max_u32
                                                    );

extern FUNC(void,DCM_CODE) Dcm_SetSesCtrlType ( VAR(Dcm_SesCtrlType, AUTOMATIC) dataSesCtrlType_u8);
extern FUNC(void,DCM_CODE) Dcm_SetSecurityLevel (VAR(Dcm_SecLevelType, AUTOMATIC) dataSecurityLevel_u8);
extern FUNC(void,DCM_CODE) Dcm_DslDsdProcessResetToDefault(void);
extern FUNC(void,DCM_CODE) Dcm_DslDsdResetRTDRequestFlag(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/* macros to handle the time monitoring */


#define DCM_TimerStop(timer)            ((timer)=0xFFFFFFFFu)

#define DCM_TimerElapsed(timer)         ((timer)==0u)

#define DCM_TimerStopped(timer)         ((timer)==0xFFFFFFFFu)
#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROE_QUEUE_ENABLED != DCM_CFG_OFF))
/* Timers for ROE inter message timer monitoring */

#define DCM_RoeTimerStart(timer,time)      ((timer) = (time));
#define DCM_RoeTimerProcess(timer)          do  /*Do while, to remove MISRA Warning 3458*/ \
                                            {   \
                                            if( ((timer)!=0u) && ((timer)!=0xFFFFFFFFuL) ) \
                                            { \
                                                (timer)--; \
                                            } \
                                            }\
                                            while(0);
#endif

/* OS Timer usage for Timer handling */
#if ( DCM_CFG_OSTIMER_USE != FALSE )
#define DCM_TimerStart(timer,time,starttime,timerStatus) do                      /*Do while, to remove MISRA Warning 3458*/ \
                                            { \
                                            (timerStatus = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&(starttime)))); \
                                            SchM_Enter_Dcm_DsldTimer_NoNest();\
                                            if( timerStatus == E_OK ) \
                                            { \
                                                ((timer) = (time)); \
                                            } \
                                            else \
                                            { \
                                                ((timer) = ((time) / DCM_CFG_TASK_TIME_US)); \
                                            } \
                                            SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            }while(0);

#define DCM_TimerProcess(timer,starttime,timerStatus)   do                    /*Do while, to remove MISRA Warning 3458*/ \
                                            { \
                                            if ( timerStatus == E_OK ) \
                                            { \
                                                timerStatus = Dcm_GetCounterValue(DCM_CFG_COUNTERID, (&Dcm_CurrTick_u32)); \
                                                SchM_Enter_Dcm_DsldTimer_NoNest();\
                                                if ( timerStatus == E_OK ) \
                                                { \
                                                    if ( (DCM_CFG_TICKS2US_COUNTER(Dcm_CurrTick_u32 - (starttime))) >= (timer) ) \
                                                    { \
                                                        ((timer) = 0u); \
                                                    } \
                                                } \
                                                else \
                                                { \
                                                    /* This else part is added for future use */ \
                                                } \
                                                SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            } \
                                            else  \
                                            { \
                                                SchM_Enter_Dcm_DsldTimer_NoNest();\
                                                if( ((timer)!=0u) && ((timer)!=0xFFFFFFFFu) ) \
                                                { \
                                                    (timer)--; \
                                                } \
                                                SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            } \
                                            }while(0);
/* This Macro used to set the new timing value of running timer */
/* Eg: After sending the response new value of P2 and P3 max is set */
/* Setting new P3 time is done in Dsp_DcmTxconfirm() function, before that */
/* old P3 max is set to the monitoring variable. from this Macro new time is set */
#define DCM_TimerSetNew(timer,time)   SchM_Enter_Dcm_DsldTimer_NoNest();\
                                    if((timer)!=0u)           \
                                    {                         \
                                        (timer) = (time);     \
                                    }\
                                      SchM_Exit_Dcm_DsldTimer_NoNest();


#else
/* Usage of Raster timer for timer monitoring */
#define DCM_TimerStart(timer,time,unused,timerStatus)  ((void)(timerStatus));\
                                                       SchM_Enter_Dcm_DsldTimer_NoNest();\
                                                      ((timer) = (uint32)((time) / DCM_CFG_TASK_TIME_US));\
                                                      SchM_Exit_Dcm_DsldTimer_NoNest();
#define DCM_TimerProcess(timer,unused,timerStatus)          \
                                            do                       /*Do while, to remove MISRA Warning 3458*/ \
                                            {   \
                                                ((void)(timerStatus));\
                                                SchM_Enter_Dcm_DsldTimer_NoNest();\
                                            if( ((timer)!=0u) && ((timer)!=0xFFFFFFFFuL) ) \
                                            { \
                                                (timer)--; \
                                            } \
                                            SchM_Exit_Dcm_DsldTimer_NoNest();\
                                            }\
                                            while(0);

/* This Macro used to set the new timing value of running timer */
/* Eg: After sending the response new value of P2 and P3 max is set */
/* Setting new P3 time is done in Dsp_DcmTxconfirm() function, before that */
/* old P3 max is set to the monitoring variable. from this Macro new time is set */
#define DCM_TimerSetNew(timer,time)        SchM_Enter_Dcm_DsldTimer_NoNest();\
                                            ((timer) = ((time) / DCM_CFG_TASK_TIME_US));\
                                            SchM_Exit_Dcm_DsldTimer_NoNest();
#endif



#define DCM_NEGRESPONSE_INDICATOR       0x7Fu         /* Indication byte of negative response */


/* Location of default session ID in session array table */
#define DCM_DEFAULT_SESSION_IDX                        0x00u

/* Parallel Tpr  bytes */
#define DCM_DSLD_PARALLEL_TPR_BYTE1                    0x3eu
#define DCM_DSLD_PARALLEL_TPR_BYTE2                    0x80u
#define DCM_DSLD_PARALLEL_DCM_TPR_REQ_LENGTH           0x02u

/* NRC for wait pend negative response */
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING 0x78u

/* Bitmasks for co operative scheduler */
#define DCM_DSLD_COOPSCHEDULER_INI      0x01u
#define DCM_DSLD_COOPSCHEDULER_SERVICE  0x02u
#define DCM_DSLD_COOPSCHEDULER_SERVICE_INI  0x04u
#define DCM_DSLD_COOPSCHEDULER_RESET_FLAG       (uint8)(~(DCM_DSLD_COOPSCHEDULER_INI | DCM_DSLD_COOPSCHEDULER_SERVICE))



#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    #define DCM_DSLD_COOPSCHEDULER_RESET() \
            Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8 &= DCM_DSLD_COOPSCHEDULER_RESET_FLAG;
#else
    #define DCM_DSLD_COOPSCHEDULER_RESET()
#endif

#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    #define DCM_DSLD_COOPSCHEDULER_SHIFTINI(ActiveServiceTable_u8) \
        Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8 |= DCM_DSLD_COOPSCHEDULER_INI; \
        Dcm_DsldProcessCoOpSchedule_st.idxServiceTableIndex_u8 = (ActiveServiceTable_u8);
#else
    #define DCM_DSLD_COOPSCHEDULER_SHIFTINI(ActiveServiceTable_u8)
#endif

#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    #define DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE(Opstatus, adrService_pcst, dataNegrespcode_u8)                                                    \
                    if ((adrService_pcst)->mainscheduler_b != FALSE)                                                    \
                    {                                                                                           \
                       Dcm_retVal_u8= (*(adrService_pcst)->service_handler_fp)(Opstatus, &Dcm_DsldMsgContext_st, dataNegrespcode_u8);                         \
                    }                                                                                           \
                    else                                                                                        \
                    {                                                                                           \
                        Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8 |= DCM_DSLD_COOPSCHEDULER_SERVICE;  \
                    }
#else
    #define DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE(Opstatus, adrService_pcst, dataNegrespcode_u8)                                                    \
           Dcm_retVal_u8 =  (*(adrService_pcst)->service_handler_fp)(Opstatus, & Dcm_DsldMsgContext_st,dataNegrespcode_u8);
#endif

#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    #define DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE_FIRSTCALL(Opstatus, adrService_pcst, dataNegrespcode_u8)                                                    \
                    if ((adrService_pcst)->mainscheduler_b != FALSE)                                                    \
                    {                                                                                           \
                        Dcm_retVal_u8 =  (*(adrService_pcst)->service_handler_fp)(Opstatus, &Dcm_DsldMsgContext_st, dataNegrespcode_u8);                         \
                    }                                                                                           \
                    else                                                                                        \
                    {                                                                                           \
                        Dcm_DsldProcessCoOpSchedule_st.adrServiceHandler_pfct = (adrService_pcst)->service_handler_fp;  \
                        Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8 |= DCM_DSLD_COOPSCHEDULER_SERVICE; \
                    }
#else
    #define DCM_DSLD_COOPSCHEDULER_SHIFTSERVICE_FIRSTCALL(Opstatus, adrService_pcst, dataNegrespcode_u8)    \
            Dcm_retVal_u8 = (*(adrService_pcst)->service_handler_fp)(Opstatus, &Dcm_DsldMsgContext_st, dataNegrespcode_u8);
#endif

#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    #define DCM_DSLD_COOPSCHEDULER_SHIFTSERVICEINI(adrService_pcst,dataNegrespcode_u8)                                             \
                    if ((adrService_pcst)->mainscheduler_b != FALSE)                                                \
                    {                                                                                       \
                        (void)(*(adrService_pcst)->service_handler_fp)(DCM_CANCEL, &Dcm_DsldMsgContext_st, dataNegrespcode_u8);                                                \
                    }                                                                                       \
                    else                                                                                    \
                    {                                                                                       \
                        Dcm_DsldProcessCoOpSchedule_st.adrServiceHandler_pfct = (adrService_pcst)->service_handler_fp;    \
                        Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8 |= DCM_DSLD_COOPSCHEDULER_SERVICE_INI; \
                    }
#else
    #define DCM_DSLD_COOPSCHEDULER_SHIFTSERVICEINI(adrService_pcst,dataNegrespcode_u8) \
        (void)(*(adrService_pcst)->service_handler_fp)(DCM_CANCEL, &Dcm_DsldMsgContext_st, dataNegrespcode_u8);
#endif

#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
    #define DCM_DSLD_COOPSCHEDULER_INIT() \
    Dcm_DsldProcessCoOpSchedule_st.adrServiceInit_pfct = NULL_PTR;          \
    Dcm_DsldProcessCoOpSchedule_st.adrServiceHandler_pfct = NULL_PTR;   \
    Dcm_DsldProcessCoOpSchedule_st.flgPendingRequest_u8 = 0x00u;
#else
    #define DCM_DSLD_COOPSCHEDULER_INIT()
#endif

/* Macro to check running protocol is KWP type  */
/* If KWP is disabled this macro returns FALSE  */
#if( DCM_CFG_KWP_ENABLED != DCM_CFG_OFF )
    #define DCM_IS_KWPPROT_ACTIVE() \
    (((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) & 0xF0u) == 0x80u)
#else
#define DCM_IS_KWPPROT_ACTIVE()    FALSE
#endif

/* Macro to check running protocol is KLINE type  */
/* If KLINE is disabled this macro returns FALSE  */
#if( DCM_CFG_KLINE_ENABLED != DCM_CFG_OFF )
    #define DCM_IS_KLINEPROT_ACTIVE() \
    (((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) == DCM_CARB_ON_KLINE)\
/* FC_VariationPoint_START */\
    ||((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) == DCM_OBD_ON_KLINE)\
/* FC_VariationPoint_END */\
    ||((Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].protocolid_u8) == DCM_KWP_ON_KLINE))
#else
#define DCM_IS_KLINEPROT_ACTIVE()    FALSE
#endif
/* Macro to check whether the ComM is in full communication mode for Drive and boot software */

#define DCM_CHKFULLCOMM_MODE(idx)  (Dcm_active_commode_e[idx].ComMState == DCM_DSLD_FULL_COM_MODE)

/* Macro to check whether the ComM is not in No communication mode for Drive and boot software */

#define DCM_CHKNOCOMM_MODE(idx) (Dcm_active_commode_e[idx].ComMState != DCM_DSLD_NO_COM_MODE)

#define DCM_PROTOCOL_ENDIANNESS (Dcm_DsldProtocol_pcst[Dcm_DsldGlobal_st.idxCurrentProtocol_u8].Endianness_ConvEnabled_b)

/*
 ***************************************************************************************************
 *    Internal DCM Type definitions
 ***************************************************************************************************
 */
typedef enum
{
    DSL_READY_FOR_RECEPTION,                         /* Ready for receving the request */
    DSL_ROETYPE1_RECIEVED,                           /* ROE type1 request by application */
    DSL_RECEIVING,                                   /* Reception started */
    DSL_STOP_PROTOCOL,                               /* State to stop or reset running protocol */
    DSL_STOP_PROTOCOL_RECEIVING,                     /* State to indicate a probable protocol pre-emption, that is a
                                                        higer priority requests StartOfReception is received,
                                                        pre-emption is confirmed when the Positive Rxindication is received
                                                        During which pre-emption state is updated to DSL_STOP_PROTOCOL*/
    DSL_STOP_ROE,                                    /* State to stop the low priority ROE service under processing */
    DSL_REQUEST_RECEIVED,                            /* Request received fully */
    DSL_WAIT_FOR_P2MAX,                              /* Service is called, and DSL waiting for P2 max */
    DSL_SEND_WAITPEND,                               /* Send wait pend */
    DSL_SEND_GENERAL_REJECT,                         /* Send general reject */
    DSL_SEND_FINAL_RESPONSE,                         /* Trigger the response transmission */
    DSL_WAIT_FOR_CONFIRMATION,                       /* Transmission is going on in TP */
    DSL_WAIT_FOR_DATA,                               /* DSL waiting for next page from service  */
    DSL_DATA_READY,                                  /* DSL has data (service given the page) */
    DSL_WAIT_PAGE_TXCONFIRM                          /* TP is sending the Page, DSL waiting for confirmation */
}Dcm_DsldDslStatesType_ten;



typedef enum
{
    DSD_IDLE,                                        /* Default state of DSD state machine */
    DSD_VERIFY_DIAGNOSTIC_DATA,                      /* State does the partial verification of Diagnostic data */
#if ((DCM_CFG_SUPPLIER_NOTIFICATION_ENABLED != DCM_CFG_OFF)||(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF))
    DSD_VERIFY_DATA_PENDING,                         /* Verification of diagnostic data in case of pending response from supplier notification function*/
#endif
    DSD_CALL_SERVICE,                                /* Consecutive call of the service */
    DSD_SEND,                                        /* Service is called, and DSL waiting for P2 max */
    DSD_TX_CONFIRMATION                              /* Tx confirmation state */
}Dcm_DsldDsdStatesType_ten;


typedef enum
{
    DCM_DSLD_POS_RESPONSE,                          /* POS response */
    DCM_DSLD_NEG_RESPONSE                           /* NEG response */
}Dcm_DsldResponseType_ten;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
typedef enum
{
    DCM_QUEUE_IDLE,                          /* Queue is idle */
    DCM_QUEUE_RUNNING,                       /* QUeuing is taking place */
    DCM_QUEUE_COMPLETED                      /* QUeuing is completed, i.e. the second request is received */
}Dcm_DsldQueHandling_ten;
#endif
typedef struct
{
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_MsgType  adrBufferPtr_pu8;                      /* pointer to hold the address of the processing request buffer */
#endif
    PduIdType dataActiveRxPduId_u8;                     /* Rx PDU Id on which request received  */
    uint8 nrActiveConn_u8;                            /* Active Connection number  */
    uint8 idxActiveSession_u8;                     /* Active sessions index in session lookup table  */
    boolean flgMonitorP3timer_b;                       /* Bit to indicate P3 timer monitoring required  */
    Dcm_DsldDslStatesType_ten stDslState_en;             /* State variable of DSL */
    Dcm_DsldDsdStatesType_ten stDsdState_en;             /* State variable of DSD */
    uint8 idxCurrentProtocol_u8;                       /* Active protocol index */
    PduIdType dataActiveTxPduId_u8;                     /* Tx PDU Id on which request received  */
    uint8 datActiveSrvtable_u8;                        /* Active service table */
    boolean flgCommActive_b;                           /* Is communication or protocol active? */
    uint8 cntrWaitpendCounter_u8;                       /* Wait pend counter */
    Dcm_DsldResponseType_ten stResponseType_en;           /* Type of response (POS/NEG) */
    uint8 idxActiveSecurity_u8;                    /* Active security index in security lookup table */
    Std_ReturnType dataResult_u8;                       /* Confirmation result */
    uint8 idxService_u8;                            /* Active services index in active service table */
    boolean dataResponseByDsd_b;                        /* Response given by DSD                         */
    uint8 dataSid_u8;                                    /* Requested Sid  */
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    uint8  dataOldSrvtable_u8;                          /* Service table which is running when event response */
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    boolean flgPagedBufferTxOn_b;                      /* Bit to indicate Paged buffer Tx in progress         */
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    PduIdType dataNewRxPduId_u8;                        /* High protocols Rx PDU id */
    Dcm_DsldDslStatesType_ten stDslPreemptionState_en;    /* DSL state to start new protocol during preemption */
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
    PduIdType dataPassRxPduId_u8;                       /* Active Roe's Rx PDU id */
#endif
#endif
    PduLengthType dataRequestLength_u16;                /* Length of request */
    PduIdType dataOldtxPduId_u8;                         /* Copy of the old active Tx PDU in DCM */
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    Dcm_MsgLenType dataCurrentPageRespLength_u32;          /* Amount of data filled by the service       */
#endif
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    PduLengthType dataNewdataRequestLength_u16;             /* Request length of high priority protocols request */
#endif
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)
    PduLengthType dataPassdataRequestLength_u16;            /* Request length of bypassing ROE request */
#endif
    uint32 dataRoeRdpiTimeout_u32;                      /* If ROE requested service unable to send */
#endif
    Dcm_MsgType adrActiveTxBuffer_tpu8;                /* Active Tx buffer pointer */
    uint32 dataTimeoutMonitor_u32;                      /* It holds the timeout time */
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
    uint32 datRoeType2Timeout_u32;                    /* Roe timer for type2 */
#endif
#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
    uint32 dataRdpiType2Timeout_u32;                   /* Rdpi timer for type2 */
#endif
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
    uint32 dataPagedBufferTimeout_u32;                 /* Paged buffer timer                                  */
#endif
    uint8  PreviousSessionIndex;                     /*sessions index for old Session   */

}Dcm_DsldInternalStructureType_tst;

#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
/* structure for queue handling */
typedef struct
{
    Dcm_DsldQueHandling_ten Dcm_QueHandling_en;         /* State handler for queue */
    Dcm_MsgType  adrBufferPtr_pu8;                      /* pointer to hold the address of the queuing buffer */
    PduLengthType dataQueueReqLength_u16;                /* Length of request */
    PduIdType dataQueueRxPduId_u8;                     /* Rx PDU Id on which request received  */
    uint8 idxBufferIndex_u8;                          /* index to point to the buffer */
}Dcm_QueueStructure_tst;
#endif

typedef struct
{
    PduInfoType Dcm_DsldRxPduBuffer_st;
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
    Dcm_MsgType  adrBufferPtr_pu8;                      /* pointer to hold the address of the normal buffer(non-queue) */
#endif
    uint16      Dcm_DsldSId_u16;
    boolean     Dcm_DsldFuncTp_b;
    boolean     Dcm_DsldCopyRxData_b;
}Dcm_DslDsdRxPduArray_tst;

typedef struct
{
    uint32 dataTimeoutP2StrMax_u32;                     /* P2* max time in us */
    uint32 dataTimeoutP2max_u32;                        /* P2 max time in us */
#if(DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
    uint32 dataTimeoutP3max_u32;                        /* P3 max time in us */
#endif
}Dcm_DsldTimingsType_tst;

typedef struct
{
    Dcm_MsgType adrTxBuffer_tpu8;                        /* Pointer to Tx buffer */
    Dcm_MsgLenType dataTxDataLength_u32 ;                       /* Length of response including Sid */
    boolean  flgApplWaitPend_b;                        /* Application triggered wait pend */
    Dcm_DsldDslStatesType_ten stDslNextState_en;          /* State of the DSL after getting the confirmation */
}Dcm_DsldTxType_tst;

#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
typedef struct
{
    P2FUNC(Std_ReturnType,TYPEDEF,adrServiceHandler_pfct) (VAR(Dcm_SrvOpStatusType,AUTOMATIC),P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_INTERN_DATA),P2VAR(Dcm_NegativeResponseCodeType,AUTOMATIC,DCM_INTERN_DATA));/* Service handler */
    P2FUNC(void,TYPEDEF,adrServiceInit_pfct) (void);                     /* Init function of service */
    uint8 flgPendingRequest_u8;                        /* Pending requests to be processed in cooperative scheduler */
    uint8 idxServiceTableIndex_u8 ;                       /* Index of the service table , that should be initialised */

}Dcm_DsldProcessCoOpScheduleType_tst;
#endif

#if((DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_ROE_QUEUE_ENABLED != DCM_CFG_OFF))
typedef struct
{
    uint8 dataEventSID_u8;                             /* ROE event SID */
    PduIdType dataRoeRxPduId_u8;                       /* RxPdu on which ROE event was registered */
    Dcm_MsgLenType dataEventRespLen_u32;            /* Roe Event Request/Response length */
    Dcm_ConfirmationStatusType stEventConfStatus_u8; /* The confirmation status of the event */
    #if(DCM_CFG_ROE_EVENTCOMPARE_ENABLED != DCM_CFG_OFF)
    boolean flgEventActive_b;                      /* Indication of ROE final response */
    #endif
}Dcm_DsldRoeQueueType_tst;

/* ROE Queue state machine */
typedef enum
{
    DCM_ROE_QUEUE_INIT,                /* ROE Queue Initialisation state */
    DCM_ROE_QUEUE_WAITFORCONFIRMATION  /* ROE Queue confirmation state */
}Dcm_DsldstRoeQueueState_ten;

typedef struct
{
    boolean flgTxQueueActive_b;                /* Indication status for ROE active/inactive */
    uint8   idxTxResponse_u8;               /* ROE response index in ROE queue */
    uint8   idxTxQueue_u8 ;                 /* ROE Queue index in ROE queue */
    Dcm_DsldstRoeQueueState_ten  stRoeQueueState_st;  /* ROE queue state machine */
    uint32  dataInterMsgTimer_u32;              /* ROE timer variable */
    #if(DCM_CFG_ROE_NUMRETRY_ATTEMPTS != 0)
    uint8   cntrTxRetryAtt_u8;                  /* Counter for transmission retry */
    #endif
}Dcm_DsldRoeIntenalType_tst;
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,DCM_VAR)  Dcm_RoeTransmitQueue_au8[DCM_CFG_DSP_ROE_MAX_QUEUELEN][DCM_CFG_DSP_ROE_MAX_EVENTLEN];
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DsldRoeIntenalType_tst,DCM_VAR) Dcm_DsldRoeScheduler_st;
extern VAR(Dcm_DsldRoeQueueType_tst  ,DCM_VAR) Dcm_DsldRoeQueue_ast[DCM_CFG_DSP_ROE_MAX_QUEUELEN];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeEventConfirmation(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) dataConfirmResult_u8);
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeEventProcess(void);
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeProcessConfirm(VAR(Std_ReturnType,AUTOMATIC) dataResult_u8);
extern FUNC(void,DCM_CODE) Dcm_DslDsdRoeQueueResponse(void);
extern FUNC(void,DCM_CODE) Dcm_DslDsd_ResetROEScheduler(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#if(DCM_ROE_ENABLED != DCM_CFG_OFF)

/**
 * @ingroup DCMDSP_UDS_EXTENDED
 * ROE structure for logging the info related to the postponement of the ROE event .\n
 * Member elements/n
  * uint8  EventId_u8;
   * boolean Is_EventTrigerred;
*/
typedef struct
{
    uint8   EventId_u8;/*Event Id reported from the apllication*/
    boolean Is_Queued;/*Will indocate whether the event is waiting to trigger the service to respond to*/
    boolean Is_Processed;/*Will indocate whether the event is waiting to trigger the service to respond to*/
    PduIdType   RxPduId_u8;/*protocol id tobe used for the reported event*/

} Dcm_DcmDspEventWaitlist_t;

#if( (DCM_CFG_DSP_RESPONSEONEVENT_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_ROEEVENT_ENABLED != DCM_CFG_OFF) )
#define DCM_START_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DcmDspEventWaitlist_t,AUTOMATIC) Dcm_DcmDspEventQueue [DCM_MAX_SETUPROEEVENTS];
#define DCM_STOP_SEC_VAR_INIT_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR (uint8, DCM_VAR) DcmRoeQueueIndex_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern CONST(Dcm_Dsld_RoeRxToTestSrcMappingType, DCM_CONST) Dcm_Dsld_RoeRxToTestSrcMappingTable[DCM_CFG_NUM_RX_PDUID];
#define DCM_STOP_SEC_CONST_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_CheckActiveDiagnosticStatus(VAR(uint8,AUTOMATIC) dataNetworkId);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

/*
***************************************************************************************************
*    Variables prototypes
***************************************************************************************************
*/
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,DCM_VAR) Dcm_DsldWaitPendBuffer_au8[8];
extern VAR(uint8,DCM_VAR) Dcm_CurProtocol_u8;
extern VAR(Dcm_SesCtrlType,DCM_VAR) Dcm_CC_ActiveSession_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(Dcm_Dsld_protocol_tableType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldProtocol_pcst;
extern P2CONST(uint8, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldRxTable_pcu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DslDsdRxPduArray_tst,DCM_VAR) Dcm_DslDsdRxPduArray_ast[DCM_CFG_NUM_RX_PDUID];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(boolean,DCM_VAR)Dcm_Prv_IsFuncTPOnOtherConnection_b;
extern VAR(boolean,DCM_VAR) Dcm_isInitialised_b;
extern VAR(boolean,DCM_VAR) Dcm_acceptRequests_b;
extern VAR(boolean,DCM_VAR) Dcm_flgCancelTransmit_b;
extern VAR(boolean,DCM_VAR) Dcm_StopProtocolflag_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(boolean,DCM_VAR) Dcm_ReadyForBoot_b;
extern VAR(boolean,DCM_VAR) Dcm_SesChgOnWarmResp_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(Dcm_Dsld_connType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldConnTable_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DsldInternalStructureType_tst,DCM_VAR) Dcm_DsldGlobal_st;
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
extern VAR(Dcm_QueueStructure_tst,DCM_VAR) Dcm_QueueStructure_st;
#endif
/* definition of structure used for cooperative scheduler */
#if (DCM_COOPERATIVE_SCHEDULER != DCM_CFG_OFF)
extern VAR(Dcm_DsldProcessCoOpScheduleType_tst,DCM_VAR) Dcm_DsldProcessCoOpSchedule_st;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DsldTimingsType_tst,DCM_VAR) Dcm_DsldTimer_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(boolean,DCM_VAR) Dcm_DsldGenRejectSent_b;
extern VAR(boolean,DCM_VAR) Dcm_DsldSessionflag_b;
#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
extern VAR(boolean,DCM_VAR) Dcm_isFirstReponseSent_b;
#endif
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(PduInfoType,DCM_VAR) Dcm_DsldPduInfo_st ;
extern VAR(Dcm_DsldTxType_tst,DCM_VAR) Dcm_DsldTransmit_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(Dcm_Dsld_ServiceType, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldSrvTable_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_MsgContextType,DCM_VAR) Dcm_DsldMsgContext_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(uint8, DCM_VAR, DCM_INTERN_CONST) Dcm_DsldSessionTable_pcu8;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(Dcm_RoeRdpiInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoeRdpi_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DsldDsdStatesType_ten,DCM_VAR) Dcm_DsdRoe2State_en;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_DsldResponseType_ten,DCM_VAR) Dcm_Roe2ResponseType_en;
extern VAR(PduInfoType,DCM_VAR) Dcm_DsldRoe2PduInfo_st;
extern VAR(Dcm_MsgContextType,DCM_VAR) Dcm_Roe2MesContext_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,DCM_VAR) Dcm_DsldSrvIndex_u8;
extern VAR(Std_ReturnType,DCM_VAR) Dcm_Roe2TxResult_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(Dcm_RoeRdpiInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRoe2_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_MsgContextType,DCM_VAR) Dcm_Rdpi2MesContext_st;
extern VAR(Dcm_DsldResponseType_ten,DCM_VAR) Dcm_Rdpi2ResponseType_en;
extern VAR(PduInfoType,DCM_VAR) Dcm_DsldRdpi2pduinfo_ast[DCM_CFG_NUM_RDPITYPE2_TXPDU];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern P2CONST(Dcm_RoeRdpiInfo_type,DCM_VAR,DCM_INTERN_CONST) Dcm_DsldRdpi2_pcst;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if (DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_Dsld_KwpTimerServerType,DCM_VAR) Dcm_DsldKwpReqTiming_st;
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED/*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if (DCM_CFG_OSTIMER_USE != FALSE)
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR( uint32, DCM_VAR )     Dcm_P2OrS3StartTick_u32;
extern VAR( uint32, DCM_VAR )     Dcm_CurrTick_u32;
#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
extern VAR( uint32, DCM_VAR )     Dcm_PagedBufferStartTick_u32;     /* Starting tick value for paged buffer timer */
#endif
#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
extern VAR( uint32, DCM_VAR )     Dcm_RoerdpiStartTick_u32;             /* Starting tick value for Roe timer */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
extern VAR( uint32, DCM_VAR )     Dcm_Roe2StartTick_u32;             /* Starting tick value for Roe timer */
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
extern VAR( uint32, DCM_VAR )     Dcm_Rdpi2StartTick_u32;            /* Starting tick value for Rdpi timer */
#endif
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if ((DCM_CFG_STORING_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR( uint32, DCM_VAR ) Dcm_SysPrevTick_u32;   /* Previous tick value */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR( uint32, DCM_VAR ) Dcm_SysCurrTick_u32;   /* Current tick value */
#define DCM_STOP_SEC_VAR_CLEARED_32 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#endif


/* FC_VariationPoint_START */
#if(DCM_CFG_RXPDU_SHARING_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR (boolean,DCM_VAR) Dcm_DsldObdReqIndn_b;
#define DCM_STOP_SEC_VAR_CLEARED_BOOLEAN /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
/* FC_VariationPoint_END */

#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(StatusType,DCM_VAR) Dcm_P2OrS3TimerStatus_uchr; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(StatusType,DCM_VAR) Dcm_PagedBufferTimerStatus_uchr; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(StatusType,DCM_VAR) Dcm_RoeRdpiType1TimerStatus_uchr; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(StatusType,DCM_VAR) Dcm_RoeType2TimerStatus_uchr ; /* global variable to get the return value of GetCounterValue for Timer related funtions*/
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

/*
 ***************************************************************************************************
 *    Function prototypes
 ***************************************************************************************************
*/
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_Dsld_triggerTransmit(void);
extern FUNC(void,DCM_CODE) Dcm_DsldCallServiceIni (VAR(uint8, AUTOMATIC) idxSrvTable_u8);
extern FUNC(void,DCM_CODE) Dcm_DsldDataConfirmation(void);
extern FUNC(void,DCM_CODE) Dcm_DsldDslStateMachine(void);
extern FUNC(void,DCM_CODE) Dcm_DsldDsdStateMachine(void);
#if ( ( DCM_CFG_DSPUDSSUPPORT_ENABLED != DCM_CFG_OFF ) && ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ) )
extern FUNC(void,DCM_CODE) Dcm_Prv_CC_Mainfunction (void);
#endif
extern FUNC(void,DCM_CODE) Dcm_Prv_CC_TxConfirmation (void);

#if((DCM_CFG_DSP_CONTROLDTCSETTING_ENABLED != DCM_CFG_OFF) || ( DCM_CFG_DSP_COMMUNICATIONCONTROL_ENABLED != DCM_CFG_OFF ))
extern FUNC(void,DCM_CODE) Dcm_DsldDspModeStateMachine(void);
#endif

#if (DCM_CFG_RTESUPPORT_ENABLED != DCM_CFG_OFF)
extern FUNC(void,DCM_CODE) Dcm_CallRTEConfirmation(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) stConfirm_u8);
#endif
extern FUNC(void,DCM_CODE) Dcm_DsldSendResponse(P2CONST(PduInfoType,AUTOMATIC,DCM_INTERN_DATA) adrPduStrucutre_pcst);
extern FUNC(void,DCM_CODE) Dcm_DsldFrameIntermediateResponse(VAR(uint8,AUTOMATIC) dataNegativeResponse_u8);
extern FUNC(void,DCM_CODE) Dcm_DslDsdRestoreSecaTimer(void);
#if(DCM_BUFQUEUE_ENABLED != DCM_CFG_OFF)
extern FUNC(P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA),DCM_CODE) Dcm_GetActiveBuffer(void);
extern FUNC(P2VAR(Dcm_MsgItemType,AUTOMATIC,DCM_INTERN_DATA),DCM_CODE) Dcm_ProvideFreeBuffer(VAR(uint8,AUTOMATIC) idxProtocolIndex_u8,VAR(boolean,AUTOMATIC) isQueuedReq_b);
#endif

#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
extern FUNC(boolean,DCM_CODE) Dcm_Dsld_CheckTotalResponseLength(VAR(Dcm_MsgLenType,AUTOMATIC) TotalResLen_u32 );
#endif

#if (DCM_CFG_RESTORING_ENABLED != DCM_CFG_OFF)
extern FUNC(uint8,DCM_CODE) Dcm_GetActiveConnectionIdx_u8 (void);
extern FUNC(void,DCM_CODE) Dcm_DslDsdWarmStart(void);
#endif


#if(DCM_PAGEDBUFFER_ENABLED != DCM_CFG_OFF)
extern FUNC(void, DCM_CODE) Dcm_DsldPagedBufferTimeout(void);
#endif

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))
extern FUNC(void,DCM_CODE) Dcm_DsldRoeRdpiTimeOut(void);

#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
FUNC(void,DCM_CODE) Dcm_DsldRoe2StateMachine(void);
#endif


#if(DCM_CFG_RDPITYPE2_ENABLED != DCM_CFG_OFF)
FUNC(void,DCM_CODE) Dcm_DsldRdpi2StateMachine(void);
#endif

#if((DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF) || (RBA_DCMPMA_CFG_PLANTMODEACTIVATION_ENABLED !=  DCM_CFG_OFF))
FUNC(Std_ReturnType,DCM_CODE) Dcm_CancelTransmit_u8(void);
#endif

#if (DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF )
extern FUNC(void,DCM_CODE) Dcm_DsldResetRDPI(void);
#endif

extern FUNC(void, DCM_CODE) Dcm_DsldResetCopyRxDataStatus ( VAR(PduIdType,AUTOMATIC) dataRxPduId_u8 );

#if(DCM_CFG_PROTOCOL_PREMPTION_ENABLED != DCM_CFG_OFF)

extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_DsldPremptionHandling_u8
                                                    (
                                         P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrArrivedProt_pcst,
                                         VAR(PduLengthType,AUTOMATIC) nrTpSduLength_u16,
                                         VAR(PduIdType,AUTOMATIC) dataRxpduId_u8
                                                     );

#if((DCM_ROE_ENABLED != DCM_CFG_OFF)||(DCM_CFG_RDPI_ENABLED != DCM_CFG_OFF))

extern FUNC(BufReq_ReturnType, DCM_CODE) Dcm_DsldPersistentRoeHandling_en(
                                         P2CONST(Dcm_Dsld_protocol_tableType,AUTOMATIC,DCM_INTERN_CONST) adrArrivedProt_pcst,
                                         VAR(PduLengthType,AUTOMATIC) nrTpSduLength_u16,
                                         VAR(PduIdType,AUTOMATIC) dataRxpduId_u8
                                                     );
#endif
#endif
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
/****************************************************************************************************
*        APPLICATION API DECLARATIONS
****************************************************************************************************/
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"

#if (((DCM_CFG_DSP_WRITEDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_WRITE_SR_ENABLED != DCM_CFG_OFF ))   ||     \
     (DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF) && (DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF))
extern FUNC(uint32,DCM_CODE) Dcm_GetSignal_u32(VAR(uint8,AUTOMATIC) xDataType_u8,
                                           VAR(uint16,AUTOMATIC) posnStart_u16,
                                           P2CONST(uint8, AUTOMATIC, DCM_INTERN_DATA) adrReqBuffer_u8,
                                           VAR(uint8,AUTOMATIC) dataEndianness_u8);
#endif


#if ( \
/* FC_VariationPoint_START */\
((DCM_CFG_DSPOBDSUPPORT_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_DSP_OBDMODE1_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_DSP_OBDMODE1_SR_ENABLED!=DCM_CFG_OFF)) ||            \
/* FC_VariationPoint_END */ \
     ((DCM_CFG_DSP_READDATABYIDENTIFIER_ENABLED != DCM_CFG_OFF) && (DCM_CFG_DSP_READ_SR_ENABLED != DCM_CFG_OFF)) ||     \
     ((DCM_CFG_DSP_ROUTINECONTROL_ENABLED != DCM_CFG_OFF)&& (DCM_CFG_ROUTINEVARLENGTH==DCM_CFG_OFF)))
extern FUNC(void,DCM_CODE) Dcm_StoreSignal(VAR(uint8,AUTOMATIC) xDataType_u8,
                                           VAR(uint16,AUTOMATIC) posnStart_u16,
                                           P2VAR(uint8, AUTOMATIC, DCM_INTERN_DATA) adrRespBuffer_u8,
                                           VAR(uint32,AUTOMATIC) dataSignalValue_u32,
                                           VAR(uint8,AUTOMATIC) dataEndianness_u8);
#endif

#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#if(DCM_CFG_RDPI_ENABLED!=DCM_CFG_OFF)
typedef enum
{
    DCM_RDPI_NO_TRANMISSION,
    DCM_RDPI_SLOW_RATE,
    DCM_RDPI_MEDIUM_RATE,
    DCM_RDPI_FAST_RATE
}Dcm_RdpiTxModeType_ten;


typedef struct
{
  uint32 cntrTime_u32;         /* Increment in each time raster if the overflowValue > 0 */
  uint16 dataId_u16;             /* periodicId */ /*---dataRdpiId_u16 */
  uint16 idxPeriodicId_u16;          /* Index of the periodic ID in Dcm_DIDConfig Table */
  Dcm_RdpiTxModeType_ten dataOverflowValue_en;  /* Off: -1, SlowRate, MediumRate, FastRate */
  boolean dataRange_b;          /*Flag to indicate if the did is a range did or not*/

} Dcm_PeriodicInfoType_tst;


#if(DCM_CFG_MAX_DID_SCHEDULER>0)
#define DCM_START_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(Dcm_PeriodicInfoType_tst,DCM_CODE) Dcm_PeriodicInfo_st[DCM_CFG_MAX_DID_SCHEDULER];
#define DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
#define DCM_START_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern VAR(uint8,       DCM_VAR)      Dcm_NumOfActivePeriodicId_u8;
#define DCM_STOP_SEC_VAR_CLEARED_8 /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_DsldPeriodicScheduler(void);
extern FUNC(void,DCM_CODE) Dcm_RdpiMainFunction(void);
extern FUNC(void,DCM_CODE) Dcm_DsldPeriodicSchedulerIni(void);
extern FUNC(void,DCM_CODE) Dcm_GetRdpiType2Index(P2VAR(uint8,AUTOMATIC, DCM_INTERN_DATA) idxRdpi2TxPduId_u8);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif

#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
FUNC(boolean,DCM_CODE) Dcm_ChkIfDidServiceIsActive(VAR(uint8, AUTOMATIC) TesterReqSid_u8, VAR(uint8, AUTOMATIC) RoeType2Sid_u8);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


#if((DCM_CFG_KWP_ENABLED != DCM_CFG_OFF)&&(DCM_CFG_SPLITRESPSUPPORTEDFORKWP != DCM_CFG_OFF))
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_KWPConfirmationForSplitResp(VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif


#if (DCM_ROE_ENABLED != DCM_CFG_OFF)
#define DCM_START_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
extern FUNC(void,DCM_CODE) Dcm_DsldProcessRoeQueue(void);
extern FUNC(void,DCM_CODE) Dcm_RestoreROEEvents(void);
extern FUNC(void,DCM_CODE) Dcm_ResetROEEvents(void);
#define DCM_STOP_SEC_CODE /*Adding this for memory mapping*/
#include "Dcm_Cfg_MemMap.h"
#endif
LOCAL_INLINE FUNC(void,DCM_CODE) Dcm_DspConfirmation
                                       (
                             VAR(Dcm_IdContextType,AUTOMATIC) dataIdContext_u8,
                             VAR(PduIdType,AUTOMATIC) dataRxPduId_u8,
                             VAR(uint16,AUTOMATIC)dataSourceAddress_u16,
                             VAR(Dcm_ConfirmationStatusType,AUTOMATIC) status_u8
                                       )

{    if(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].Dcm_ConfirmationService !=NULL_PTR)
	{
		(Dcm_DsldSrvTable_pcst[Dcm_DsldGlobal_st.idxService_u8].Dcm_ConfirmationService)(dataIdContext_u8,dataRxPduId_u8,dataSourceAddress_u16,status_u8);
	}
}

LOCAL_INLINE FUNC(boolean,DCM_CODE) DCM_DSLD_SERVICEBUSY(void)
{
    VAR(boolean,AUTOMATIC)  flgStatus_b;
#if(DCM_CFG_ROETYPE2_ENABLED != DCM_CFG_OFF)
/* If ROE Type 2 event is being processed */
    flgStatus_b  =   ((Dcm_DsdRoe2State_en != DSD_IDLE) && (Dcm_Roe2MesContext_st.idContext == Dcm_DsldGlobal_st.dataSid_u8));
#else
    flgStatus_b =  FALSE;
#endif

 return flgStatus_b;
}
#endif /* _DCMCORE_DSLDSD_PROT_H */

