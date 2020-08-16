/*
***********************************************************************************************************************
* 
* Product Info
* Isolar version: ISOLAR-AB 4.0.1
* Product release version: RTA-BSW 3.1.0
* 
***********************************************************************************************************************
*/



#ifndef WDGM_CFG_H
#define WDGM_CFG_H

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/

/*[WDGMFCK] The module shall include SchM_WdgM_Type.h*/
#include "SchM_WdgM_Type.h"
#include "Os.h"
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error 揂UTOSAR major version undefined or mismatched�
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error 揂UTOSAR minor version undefined or mismatched�
#endif

#include "Std_Types.h"
#if (!defined(STD_TYPES_AR_RELEASE_MAJOR_VERSION) || (STD_TYPES_AR_RELEASE_MAJOR_VERSION != 4))
//#error 揂UTOSAR major version undefined or mismatched�
#endif
#if (!defined(STD_TYPES_AR_RELEASE_MINOR_VERSION) || (STD_TYPES_AR_RELEASE_MINOR_VERSION != 2))
//#error 揂UTOSAR minor version undefined or mismatched�
#endif


#include "Det.h"
#if (!defined(DET_AR_RELEASE_MAJOR_VERSION) || (DET_AR_RELEASE_MAJOR_VERSION != 4))
#error 揂UTOSAR major version undefined or mismatched�
#endif
#if (!defined(DET_AR_RELEASE_MINOR_VERSION) || (DET_AR_RELEASE_MINOR_VERSION != 2))
#error 揂UTOSAR minor version undefined or mismatched�
#endif




#include "WdgIf.h"
#if (!defined(WDGIF_AR_RELEASE_MAJOR_VERSION) || (WDGIF_AR_RELEASE_MAJOR_VERSION != 4))
#error 揂UTOSAR major version undefined or mismatched�
#endif
#if (!defined(WDGIF_AR_RELEASE_MINOR_VERSION) || (WDGIF_AR_RELEASE_MINOR_VERSION != 2))
#error 揂UTOSAR minor version undefined or mismatched�
#endif

/*
 *********************************************************************************************************
 * Defines/Macros
 *********************************************************************************************************
*/

#define WDGM_VARIANT_PRE_COMPILE                                     (1)
#define WDGM_DEADLINE_TIMEOUT_DETECT                                 (STD_OFF)
#define WDGM_DEV_ERROR_DETECT                                        (STD_ON)
#define WDGM_RTE_DISABLED                                            (STD_OFF)
#define WDGM_RB_DEBUG_OPTION_ENABLED                                 (STD_OFF)
#define WDGM_DEFENSIVE_BEHAVIOR                                      (STD_OFF)
#define WDGM_DEM_ALIVE_SUPERVISION_REPORT                            (STD_OFF)
#define WDGM_IMMEDIATE_RESET                                         (STD_OFF)
#define WDGM_OFF_MODE_ENABLED                                        (STD_OFF)
#define WDGM_VERSION_INFO_API                                        (STD_ON)
#define WDGM_PRV_C_ZERO                                              (0)
#define WDGM_PRV_C_ONE                                               (1)
#define WDGM_PRV_C_TWO                                               (2)
#define WDGM_INVALID_WDGIF_DEVICE_INDEX                              (1)
#define WDGM_INVALID_DEM_EVENT_ID                                    (0)
#define WDGM_INVALID_TIMER_ID                                        ((CounterType)(0))

#define WDGM_NO_OF_WATCHDOGS                                         (1)
#define WDGM_NO_OF_EXTERNAL_CALLER_IDENTIFIERS                       (1)
#define WDGM_NO_OF_SUPERVISED_ENTITIES                               ((WdgM_SupervisedEntityIdType)(7))
#define WDGM_NO_OF_CHECKPOINTS                                       ((WdgM_CheckpointIdType)(7))
#define WDGM_NO_OF_DISTINCT_CHECKPOINTS                              ((WdgM_CheckpointIdType)(1))
#define WDGM_MAX_DEADLINE_SUPERVISIONS                               (0)


/*Enable this to STD_ON if your use case does not involve WdgM_MainFunction being pre-empted by WdgM_SetMode vice versa.*/
#define WDGM_LOCK_DISABLE_FOR_DGS                                    (STD_ON)


/* Symbolic names for Supervised Entities */
#define WdgMConf_WdgMSupervisedEntity_WdgMAliveSupervisedEntity_Asw_5ms  ((WdgM_SupervisedEntityIdType)(0))
#define WdgMConf_WdgMSupervisedEntity_WdgMAliveSupervisedEntity_Bsw_1000ms  ((WdgM_SupervisedEntityIdType)(1))
#define WdgMConf_WdgMSupervisedEntity_WdgMAliveSupervisedEntity_Bsw_100ms  ((WdgM_SupervisedEntityIdType)(2))
#define WdgMConf_WdgMSupervisedEntity_WdgMAliveSupervisedEntity_Bsw_10ms  ((WdgM_SupervisedEntityIdType)(3))
#define WdgMConf_WdgMSupervisedEntity_WdgMAliveSupervisedEntity_Bsw_20ms  ((WdgM_SupervisedEntityIdType)(4))
#define WdgMConf_WdgMSupervisedEntity_WdgMAliveSupervisedEntity_Bsw_50ms  ((WdgM_SupervisedEntityIdType)(5))
#define WdgMConf_WdgMSupervisedEntity_WdgMAliveSupervisedEntity_Bsw_5ms  ((WdgM_SupervisedEntityIdType)(6))

/* Symbolic names for CheckPoint Identifiers */
#define WdgMConf_WdgMCheckpoint_WdgMCheckpoint_Asw_5ms               ((WdgM_CheckpointIdType)(0))

#define WdgMConf_WdgMCheckpoint_WdgMCheckpoint_Bsw_1000ms            ((WdgM_CheckpointIdType)(0))

#define WdgMConf_WdgMCheckpoint_WdgMCheckpoint_Bsw_100ms             ((WdgM_CheckpointIdType)(0))

#define WdgMConf_WdgMCheckpoint_WdgMCheckpoint_Bsw_10ms              ((WdgM_CheckpointIdType)(0))

#define WdgMConf_WdgMCheckpoint_WdgMCheckpoint_Bsw_20ms              ((WdgM_CheckpointIdType)(0))

#define WdgMConf_WdgMCheckpoint_WdgMCheckpoint_Bsw_50ms              ((WdgM_CheckpointIdType)(0))

#define WdgMConf_WdgMCheckpoint_WdgMCheckpoint_Bsw_5ms               ((WdgM_CheckpointIdType)(0))


/* Symbolic names for Watchdog instances */
#define WdgMConf_WdgMWatchdog_WdgMWatchdog_Internal                  (WdgIfConf_WdgIfDevice_WdgIfDevice)

/* WdgMSupervisionCycle Definitions [ms] */
#define WDGM_INVALID_SUPERVISION_CYCLE                               ((uint32)(0))
#define WDGM_SUPERVISION_CYCLE_0                                     ((uint32)(10))

/* Timer interface selection for Deadline supervision */
#define     WDGM_RB_DEADLINE_TIMER_SELECTION_NONE     (0)
#define     WDGM_RB_DEADLINE_TIMER_SELECTION_MCU      (1)
#define     WDGM_RB_DEADLINE_TIMER_SELECTION_OS       (2)

/* No WdgMDeadlineSupervision configured so no timer selection is done*/
#define WDGM_RB_DEADLINE_TIMER_SELECTION WDGM_RB_DEADLINE_TIMER_SELECTION_NONE


#define WDGM_INTERNAL_GRAPH_CONFIGURED  STD_OFF

#define WdgMConf_WdgMMode_WdgMMode_Fast                             	((WdgM_ModeType)(0))
#define WDGM_INVALID_MODE_INDEX                                     	((WdgM_ModeType)(1))
/*
***************************************************************************************************
* Type definitions
***************************************************************************************************
*/

typedef uint8 WdgM_ModeType;
typedef uint8 WdgM_LocalStatusType;
typedef uint8 WdgM_GlobalStatusType;


typedef struct
{
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)  NoOfDeadlineSupervision;
    P2VAR(uint16,WDGM_VAR_FAST_CLEARED_16,WDGM_APPL_DATA)PtrToDeadlineIndices;
}WdgM_CheckpointDynType;

typedef struct
{
	CONSTP2VAR(WdgM_CheckpointDynType, WDGM_VAR_FAST_CLEARED_UNSPECIFIED, WDGM_APPL_DATA)PtrToCheckpointDyn;
}WdgM_CheckpointType;

typedef struct
{
    VAR(uint8,WDGM_VAR_FAST_CLEARED_8)					FailedAliveSupervisionRefCycleCtr; 				/* To track the failed reference cycles of SE*/
    VAR(uint8,WDGM_VAR_FAST_CLEARED_8)					FailedAliveSupervisionRefCycleTol;   /* Configuration Value to be copied at Mode change of WdgM from WdgM_LocalStatusParams. */
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)			        IndividualSupervisionCycleCtr;        /* To track the supervision cycles of SE*/
    VAR(uint32,WDGM_VAR_FAST_CLEARED_32)				IndividualAliveUpdateCtr;    /* To track the alivecounter of SE*/
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)				AliveSupervisionIdx;
    VAR(WdgM_LocalStatusType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)  	NewLocalStatus;
    VAR(WdgM_LocalStatusType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)  	OldLocalStatus;			 /* Only to be updated in WdgM_MainFunction after current Monitoring Status is reported to RTE */
#if WDGM_INTERNAL_GRAPH_CONFIGURED == STD_ON
    VAR(boolean,WDGM_VAR_FAST_CLEARED_BOOLEAN)                      flgActivity;    // True � graph active, False � graph inactive
    VAR(WdgM_CheckpointIdType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)    idLastReachedCheckpoint;    
#endif 
}WdgM_SupervisedEntityDynType;

typedef struct
{
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)                      NoOfCheckpoint;
    VAR(boolean,WDGM_VAR_FAST_CLEARED_BOOLEAN)   	      PartionEnabled;
    VAR(CounterType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)	      TimerId;
    VAR(ApplicationType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)    OsApplicationId;
    P2CONST( WdgM_CheckpointType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED,WDGM_APPL_DATA)PtrToCheckpoint;
    CONSTP2VAR(WdgM_SupervisedEntityDynType, WDGM_VAR_FAST_CLEARED_UNSPECIFIED, WDGM_APPL_DATA)PtrToSupervisedEntityDyn;
#if WDGM_INTERNAL_GRAPH_CONFIGURED == STD_ON
    VAR(boolean,WDGM_VAR_FAST_CLEARED_BOOLEAN)            hasInternalGraph;    /* True � has Internal Graph, False � does not have Internal Graph*/
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)                  idxInternalGraphCPProperty;
#endif    
}WdgM_SupervisedEntityType;

/*TRACE[WDGM085] All the resources required for Alive Monitoring */
typedef struct
{
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)                                   MinMargin;
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)                                   MaxMargin;
    VAR(WdgM_CheckpointIdType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)           AliveSupervisionCheckpointId;
    VAR(WdgM_SupervisedEntityIdType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)     SupervisedEntityId;
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)                                   ExpectedAliveIndications;
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)                                   SupervisionReferenceCycle;
}WdgM_AliveSupervisionType;

/*TRACE[WDGM293] All the resources required for Deadline Monitoring */
typedef struct
{
    VAR(WdgM_CheckpointIdType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)       StartCheckpointId;
    VAR(WdgM_CheckpointIdType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)       StopCheckpointId;
    VAR(WdgM_SupervisedEntityIdType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED) SupervisedEntityId;
    VAR(TickType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)                    DeadlineMin;
    VAR(TickType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)                    DeadlineMax;
}WdgM_DeadlineSupervisionType;

typedef struct
{
    VAR(uint8,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)                       FailedAliveSupervisionRefCycleTol;
    VAR(WdgM_SupervisedEntityIdType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED) SupervisedEntityId;
}WdgM_LocalStatusParamsType;

typedef struct
{
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)                   TriggerConditionValue;
    VAR(uint8,WDGM_VAR_FAST_CLEARED_8)                     DeviceIdx;
    VAR(WdgIf_ModeType,WDGM_VAR_FAST_CLEARED_UNSPECIFIED)  WdgMode;
}WdgM_TriggerType;

typedef struct
{
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)  ExpiredSupervisionCycleTol;
    VAR(Rte_ModeType_WdgMSupervisionCycle,WDGM_VAR_FAST_CLEARED_UNSPECIFIED) SchMWdgMSupervisionCycle;
    VAR(uint32,WDGM_VAR_FAST_CLEARED_32) SupervisionCycle;
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)  NoOfAliveSupervision;
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)  NoOfDeadlineSupervision;
    VAR(uint16,WDGM_VAR_FAST_CLEARED_16)  NoOfLocalStatusParams;
    VAR(uint8,WDGM_VAR_FAST_CLEARED_8)    NoOfTrigger;
    P2CONST(WdgM_AliveSupervisionType,WDGM_VAR_FAST_UNSPECIFIED,WDGM_APPL_CONST)PtrToAliveSupervision;
    P2CONST(WdgM_DeadlineSupervisionType,WDGM_VAR_FAST_UNSPECIFIED,WDGM_APPL_CONST)PtrToDeadlineSupervision;
    P2CONST(WdgM_LocalStatusParamsType,WDGM_VAR_FAST_UNSPECIFIED,WDGM_APPL_CONST)PtrToLocalStatusParams;
    P2CONST(WdgM_TriggerType,WDGM_VAR_FAST_UNSPECIFIED,WDGM_APPL_CONST)PtrToTrigger;
}WdgM_PrvModeType;

/* WDGM029 */
typedef struct
{
    VAR(WdgM_ModeType,WDGM_VAR_FAST_UNSPECIFIED)               InitialMode;
    VAR(uint8,WDGM_VAR_FAST_8)                                 NoOfMode;
#if((WDGM_DEM_ALIVE_SUPERVISION_REPORT) == (STD_ON))
    VAR(Dem_EventIdType,WDGM_VAR_FAST_UNSPECIFIED)             ErrorImproperCaller;
    VAR(Dem_EventIdType,WDGM_VAR_FAST_UNSPECIFIED)             ErrorSupervision;
    VAR(Dem_EventIdType,WDGM_VAR_FAST_UNSPECIFIED)             ErrorSetMode;
#else /*WDGM_DEM_ALIVE_SUPERVISION_REPORT*/
    VAR(uint16,WDGM_VAR_FAST_16)				    ErrorImproperCaller;
    VAR(uint16,WDGM_VAR_FAST_16)			            ErrorSupervision;
    VAR(uint16,WDGM_VAR_FAST_16)			            ErrorSetMode;
#endif /*WDGM_DEM_ALIVE_SUPERVISION_REPORT*/
	CONSTP2VAR(TickType, WDGM_VAR_FAST_UNSPECIFIED, WDGM_APPL_DATA)PtrToRunningCounterValue;
	CONSTP2VAR(uint16, WDGM_VAR_FAST_UNSPECIFIED, WDGM_APPL_DATA)PtrToDeadlineIndices;
    P2CONST(WdgM_PrvModeType,WDGM_VAR_FAST_UNSPECIFIED,WDGM_APPL_CONST)PtrToMode;
}WdgM_ConfigType;

#if WDGM_INTERNAL_GRAPH_CONFIGURED == STD_ON
typedef enum
{
    WDGM_POSNGRAPH_NONE_E = 0,                 // Does not belong to Internal graph (value 0)
    WDGM_POSNGRAPH_INITIAL_E,               // Initial checkpoint (value 1)
    WDGM_POSNGRAPH_FINAL_E,                 // Final checkpoint (value 2)
    WDGM_POSNGRAPH_INTERMEDIATE_E // Intermediate checkpoint (value 3)
} WdgM_PositionInGraph_ten;

typedef struct
{
    WdgM_PositionInGraph_ten    posnInGraph_en;             
    uint16                      nrDestCheckpoints; 
    uint16                      idxDestCheckpoints;
} WdgM_InternalGraph_CPPropertyType;
#endif 

/*
***************************************************************************************************
* External declaration
***************************************************************************************************
*/

#define WDGM_START_SEC_CONFIG_DATA_FAST_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"


extern CONST(WdgM_CheckpointType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_Checkpoint[7];
extern CONST(WdgM_SupervisedEntityType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_SupervisedEntity[7];
/*No Internal Graph Configured for Logical Supervision....!!! */ 
#define WDGM_STOP_SEC_CONFIG_DATA_FAST_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"





#define WDGM_START_SEC_CONFIG_DATA_FAST_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"
/* Variable declarations from WdgMConfigSet */
extern CONST(WdgM_AliveSupervisionType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_AliveSupervision[7];
/* No WdgMDeadlineSupervision is configured....!!! */
extern CONST(WdgM_LocalStatusParamsType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_LocalStatusParams[7];
extern CONST(WdgM_TriggerType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_Trigger[1];
extern CONST(WdgM_PrvModeType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_PrvMode[1];
extern CONST(WdgM_ConfigType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_Config;
#define WDGM_STOP_SEC_CONFIG_DATA_FAST_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"





#define WDGM_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"

/*TRACE[WDGM240] The Alive Counters of each Checkpoint shall be available for debugging */
/*TRACE[WDGM241] The Alive Counters of each Checkpoint shall be available for debugging */
/*TRACE[WDGM242] The Alive Counters of each Checkpoint shall be available for debugging */
/*TRACE[WDGM238] The local supervision status of each SE is available for debugging*/

extern VAR(WdgM_SupervisedEntityDynType, WDGM_VAR_FAST_CLEARED_UNSPECIFIED) WdgM_SupervisedEntityDyn[7];

#define WDGM_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"

LOCAL_INLINE WdgM_SupervisedEntityIdType WdgM_Prv_ComplementSeId_to_Inl(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) SEID);


/************************************************************************************************************************
* Name              :   WdgM_Prv_ComplementSeId_to_Inl
* Description       :   returns 1's complement of the SEID passed as argument.
* Parameters[in]    :   SEID
* Limitations       :   None
* Return Value      :   WdgM_SupervisedEntityIdType
************************************************************************************************************************/
LOCAL_INLINE WdgM_SupervisedEntityIdType WdgM_Prv_ComplementSeId_to_Inl(VAR(WdgM_SupervisedEntityIdType,AUTOMATIC) SEID)
{
    return (((WdgM_SupervisedEntityIdType)(0xFF)) - SEID);
}



#endif /* WDGM_CFG_H */

