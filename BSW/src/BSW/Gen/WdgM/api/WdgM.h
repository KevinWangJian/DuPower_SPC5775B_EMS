

#ifndef WDGM_H
#define WDGM_H


/*TRACE[WDGM014] Follow predefined file inculde structure*/
/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

#include "WdgM_Cfg.h"
#if(defined(WDGM_VARIANT_POST_BUILD))
#include "WdgM_PBcfg.h"
#endif

#if((WDGM_RTE_DISABLED) == (STD_OFF))
/* TRACE[WDGMFCK] The module header file WdgM.h shall include Rte_WdgM_Type.h */
#include "Rte_WdgM_Type.h"
#endif /*(WDGM_RTE_DISABLED == STD_OFF)*/

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

#define WDGM_AR_RELEASE_MAJOR_VERSION               (4)
#define WDGM_AR_RELEASE_MINOR_VERSION               (2)
#define WDGM_AR_RELEASE_REVISION_VERSION            (2)

#define WDGM_SW_MAJOR_VERSION                       (3)
#define WDGM_SW_MINOR_VERSION                       (0)
#define WDGM_SW_PATCH_VERSION                       (0)

#define WDGM_MODULE_ID                              (13)
#define WDGM_VENDOR_ID                              (6)

/* Interface API IDs for DET interface */
#define  WDGM_INSTANCE_ID                           ((uint8)(0))
#define  WDGM_INIT_APIID                            ((uint8)0x00)
#define  WDGM_DE_INIT_APIID                         ((uint8)0x01)
#define  WDGM_GET_VERSION_INFO_APIID                ((uint8)0x02)
#define  WDGM_SET_MODE_APIID                        ((uint8)0x03)
#define  WDGM_UPDATE_ALIVE_COUNTER_APIID            ((uint8)0x04)
#define  WDGM_CHECKPOINT_REACHED_APIID              ((uint8)0x0e)
#define  WDGM_MAIN_FUNCTION_APIID                   ((uint8)0x08)
#define  WDGM_GET_MODE_APIID                        ((uint8)0x0b)
#define  WDGM_GET_LOCAL_STATUS_APIID                ((uint8)0x0c)
#define  WDGM_GET_GLOBAL_STATUS_APIID               ((uint8)0x0d)
#define  WDGM_PERFORM_RESET_APIID                   ((uint8)0x0f)
#define  WDGM_GET_FIRST_EXPIRED_SEID_APIID          ((uint8)0x10)

/* Det error Ids */
#define  WDGM_E_NO_INIT                             ((uint8)(0x10))
#define  WDGM_E_PARAM_CONFIG                        ((uint8)(0x11))
#define  WDGM_E_PARAM_MODE                          ((uint8)(0x12))
#define  WDGM_E_PARAM_SEID                          ((uint8)(0x13))
#define  WDGM_E_INV_POINTER                         ((uint8)(0x14))
#define  WDGM_E_DISABLE_NOT_ALLOWED                 ((uint8)(0x15))
#define  WDGM_E_CPID                                ((uint8)(0x16))
#define  WDGM_E_SEDEACTIVATED                       ((uint8)(0x19))

#define  WDGM_E_OS_COUNTER                          ((uint8)(0x80))

/* Global Status */
#define WDGM_GLOBAL_STATUS_OK                       ((WdgM_GlobalStatusType)(0))
#define WDGM_GLOBAL_STATUS_FAILED                   ((WdgM_GlobalStatusType)(1))
#define WDGM_GLOBAL_STATUS_EXPIRED                  ((WdgM_GlobalStatusType)(2))
#define WDGM_GLOBAL_STATUS_STOPPED                  ((WdgM_GlobalStatusType)(3))
#define WDGM_GLOBAL_STATUS_DEACTIVATED              ((WdgM_GlobalStatusType)(4))

/* Local Status */
#define WDGM_LOCAL_STATUS_OK                        ((WdgM_LocalStatusType)(0))
#define WDGM_LOCAL_STATUS_FAILED                    ((WdgM_LocalStatusType)(1))
#define WDGM_LOCAL_STATUS_EXPIRED                   ((WdgM_LocalStatusType)(2))
#define WDGM_LOCAL_STATUS_DEACTIVATED               ((WdgM_LocalStatusType)(4))

/*
 **********************************************************************************************************************
 * Extern declarations
 **********************************************************************************************************************
*/
#ifdef WDGM_DBG_TST_ENA
#define WDGM_START_SEC_VAR_FAST_INIT_8
#include "WdgM_Cfg_MemMap.h"

/* TRACE[WDGM239] Global supervsion status should be available for debugging */
extern VAR(WdgM_GlobalStatusType, WDGM_VAR_FAST_INIT_8)  WdgM_GlobalStatus;

#define WDGM_STOP_SEC_VAR_FAST_INIT_8
#include "WdgM_Cfg_MemMap.h"
#endif

/* API-Functions Prototype Declaration */
#if(((defined(WDGM_PRV_AVOID_RTE_PROVIDED_FUNC_DECLARATION)) && ((WDGM_RTE_DISABLED) == (STD_ON))) || (!defined(WDGM_PRV_AVOID_RTE_PROVIDED_FUNC_DECLARATION)))
#define WDGM_START_SEC_CODE
#include "WdgM_Cfg_MemMap.h"

extern FUNC(void, WDGM_CODE) WdgM_MainFunction(void);

#if((WDGM_RTE_DISABLED) == (STD_OFF))
extern FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_CheckpointReached(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) Rte_PDAV0, VAR(WdgM_CheckpointIdType,AUTOMATIC) CheckpointID);
#else
extern FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_CheckpointReached(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) SEID, VAR(WdgM_CheckpointIdType,AUTOMATIC) CheckpointID);
#endif

#define WDGM_STOP_SEC_CODE
#include "WdgM_Cfg_MemMap.h"
#endif

#define WDGM_START_SEC_CODE_FAST
#include "WdgM_Cfg_MemMap.h"

extern FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_SetMode(VAR(WdgM_ModeType,AUTOMATIC) Mode, VAR(uint16,AUTOMATIC) CallerID);
extern FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_GetMode (P2VAR(WdgM_ModeType,AUTOMATIC,WDGM_APPL_DATA)Mode);
extern FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_GetLocalStatus(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) SEID, P2VAR(WdgM_LocalStatusType,AUTOMATIC,WDGM_APPL_DATA)Status);
extern FUNC(Std_ReturnType, WDGM_CODE_FAST) WdgM_GetGlobalStatus(P2VAR(WdgM_GlobalStatusType,AUTOMATIC,WDGM_APPL_DATA)Status);
extern FUNC(void, WDGM_CODE_FAST) WdgM_PerformReset(void);

#define WDGM_STOP_SEC_CODE_FAST
#include "WdgM_Cfg_MemMap.h"

#define WDGM_START_SEC_CODE_SLOW
#include "WdgM_Cfg_MemMap.h"

extern FUNC(void, WDGM_CODE_SLOW) WdgM_Init(P2CONST(WdgM_ConfigType, AUTOMATIC, WDGM_APPL_CONST)ConfigPtr);
extern FUNC(void, WDGM_CODE_SLOW) WdgM_DeInit(void);
#if ( (WDGM_VERSION_INFO_API) == (STD_ON) )
extern FUNC(void, WDGM_CODE_SLOW) WdgM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,WDGM_APPL_DATA)VersionInfo);
#endif /*(WDGM_VERSION_INFO_API) == (STD_ON)*/
extern FUNC(Std_ReturnType, WDGM_CODE_SLOW) WdgM_GetFirstExpiredSEID(P2VAR(WdgM_SupervisedEntityIdType,AUTOMATIC,WDGM_APPL_DATA)SEID);

#define WDGM_STOP_SEC_CODE_SLOW
#include "WdgM_Cfg_MemMap.h"

#endif /*WDGM_H*/
