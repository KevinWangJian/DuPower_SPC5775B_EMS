

/*
 **********************************************************************************************************************
 * Includes
 **********************************************************************************************************************
*/
#include "WdgM.h"
#include "Os.h"
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error “AUTOSAR major version undefined or mismatched?
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error “AUTOSAR minor version undefined or mismatched?
#endif
#include "WdgM_Prv.h"

/*
 ***************************************************************************************************
 * Variables
 ***************************************************************************************************
 */


/* There is no deadline Supervision configured in valid WdgMMode so corresponding Variables, data types are not defined....!!! */



/*
 ***************************************************************************************************
 * Dynamic Variables
 ***************************************************************************************************
 */
#define WDGM_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"
/* TRACE[WDGM200] Values of local supervsion should be described in WdgM_LocalStatusType */
VAR(WdgM_SupervisedEntityDynType, WDGM_VAR_FAST_CLEARED_UNSPECIFIED) WdgM_SupervisedEntityDyn[7];  /* WDGM242 */
static VAR(WdgM_CheckpointDynType, WDGM_VAR_FAST_CLEARED_UNSPECIFIED) WdgM_CheckpointDyn[7];
#define WDGM_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"

/*
 **********************************************************************************************************************
 * Defines/Macros
 **********************************************************************************************************************
*/

#define WDGM_START_SEC_CONFIG_DATA_FAST_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"


CONST(WdgM_CheckpointType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_Checkpoint[7] =
{	
	/* PtrToCheckpointDyn                          Comment */ 
	
	{   &WdgM_CheckpointDyn[0]                       /* WdgMSupervisedEntityId: 0, WdgMCheckpointId: 0 */        },	
	{   &WdgM_CheckpointDyn[1]                       /* WdgMSupervisedEntityId: 1, WdgMCheckpointId: 0 */        },	
	{   &WdgM_CheckpointDyn[2]                       /* WdgMSupervisedEntityId: 2, WdgMCheckpointId: 0 */        },	
	{   &WdgM_CheckpointDyn[3]                       /* WdgMSupervisedEntityId: 3, WdgMCheckpointId: 0 */        },	
	{   &WdgM_CheckpointDyn[4]                       /* WdgMSupervisedEntityId: 4, WdgMCheckpointId: 0 */        },	
	{   &WdgM_CheckpointDyn[5]                       /* WdgMSupervisedEntityId: 5, WdgMCheckpointId: 0 */        },	
	{   &WdgM_CheckpointDyn[6]                       /* WdgMSupervisedEntityId: 6, WdgMCheckpointId: 0 */        }
};


CONST(WdgM_SupervisedEntityType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_SupervisedEntity[7]=
{	
    /* NoOfCheckpoint             PartionEnabled             TimerId                                        OsApplicationId                                PtrToCheckpoint                                PtrToSupervisedEntityDyn                         Comment */         
    
    {  1                        ,  FALSE                    ,  Rte_TickCounter                              ,  INVALID_OSAPPLICATION                        ,  &WdgM_Checkpoint[0]                          ,    &WdgM_SupervisedEntityDyn[0]                     /* WdgMSupervisedEntityId: 0 */              },
    {  1                        ,  FALSE                    ,  Rte_TickCounter                              ,  INVALID_OSAPPLICATION                        ,  &WdgM_Checkpoint[1]                          ,    &WdgM_SupervisedEntityDyn[1]                     /* WdgMSupervisedEntityId: 1 */              },
    {  1                        ,  FALSE                    ,  Rte_TickCounter                              ,  INVALID_OSAPPLICATION                        ,  &WdgM_Checkpoint[2]                          ,    &WdgM_SupervisedEntityDyn[2]                     /* WdgMSupervisedEntityId: 2 */              },
    {  1                        ,  FALSE                    ,  Rte_TickCounter                              ,  INVALID_OSAPPLICATION                        ,  &WdgM_Checkpoint[3]                          ,    &WdgM_SupervisedEntityDyn[3]                     /* WdgMSupervisedEntityId: 3 */              },
    {  1                        ,  FALSE                    ,  Rte_TickCounter                              ,  INVALID_OSAPPLICATION                        ,  &WdgM_Checkpoint[4]                          ,    &WdgM_SupervisedEntityDyn[4]                     /* WdgMSupervisedEntityId: 4 */              },
    {  1                        ,  FALSE                    ,  Rte_TickCounter                              ,  INVALID_OSAPPLICATION                        ,  &WdgM_Checkpoint[5]                          ,    &WdgM_SupervisedEntityDyn[5]                     /* WdgMSupervisedEntityId: 5 */              },
    {  1                        ,  FALSE                    ,  Rte_TickCounter                              ,  INVALID_OSAPPLICATION                        ,  &WdgM_Checkpoint[6]                          ,    &WdgM_SupervisedEntityDyn[6]                     /* WdgMSupervisedEntityId: 6 */              }
};
/* No WdgMInternalTransition configured for Internal Graph so corresponding code is not generated. */
/* No WdgMInternalTransitionDestRef configured for Internal Graph so corresponding code is not generated. */

CONST(WdgM_AliveSupervisionType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_AliveSupervision[7] =
{
    /* MinMargin          MaxMargin                  AliveSupervisionCheckpointId     SupervisedEntityId              ExpectedAliveIndications   SupervisionReferenceCycle   Comment */ 
   
    {   2                   ,  2                   ,  0                              ,  0                             ,  10                      ,  5                        /* WdgMMode: 0  AliveSuperVision: WdgMAliveSupervision_Asw_5ms */               },
    {   2                   ,  2                   ,  0                              ,  1                             ,  10                      ,  1000                     /* WdgMMode: 0  AliveSuperVision: WdgMAliveSupervision_Bsw_1000ms */            },
    {   2                   ,  2                   ,  0                              ,  2                             ,  10                      ,  100                      /* WdgMMode: 0  AliveSuperVision: WdgMAliveSupervision_Bsw_100ms */             },
    {   2                   ,  2                   ,  0                              ,  3                             ,  10                      ,  10                       /* WdgMMode: 0  AliveSuperVision: WdgMAliveSupervision_Bsw_10ms */              },
    {   2                   ,  2                   ,  0                              ,  4                             ,  10                      ,  20                       /* WdgMMode: 0  AliveSuperVision: WdgMAliveSupervision_Bsw_20ms */              },
    {   2                   ,  2                   ,  0                              ,  5                             ,  10                      ,  50                       /* WdgMMode: 0  AliveSuperVision: WdgMAliveSupervision_Bsw_50ms */              },
    {   2                   ,  2                   ,  0                              ,  6                             ,  10                      ,  5                        /* WdgMMode: 0  AliveSuperVision: WdgMAliveSupervision_Bsw_5ms */               }
};

/* No WdgMDeadlineSupervision configured so corresponding code is not generated. */


CONST(WdgM_LocalStatusParamsType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_LocalStatusParams[7] =
{
    /* FailedAliveSupervisionRefCycleTol               SupervisedEntityId                              Comment */                                    
    
    {   1                                            ,  0                                              /* WdgMMode: 0  WdgMLocalStatusParams: WdgMLocalStatusParams_Asw_5ms */         },
    {   1                                            ,  1                                              /* WdgMMode: 0  WdgMLocalStatusParams: WdgMLocalStatusParams_Bsw_1000ms */      },
    {   1                                            ,  2                                              /* WdgMMode: 0  WdgMLocalStatusParams: WdgMLocalStatusParams_Bsw_100ms */       },
    {   1                                            ,  3                                              /* WdgMMode: 0  WdgMLocalStatusParams: WdgMLocalStatusParams_Bsw_10ms */        },
    {   1                                            ,  4                                              /* WdgMMode: 0  WdgMLocalStatusParams: WdgMLocalStatusParams_Bsw_20ms */        },
    {   1                                            ,  5                                              /* WdgMMode: 0  WdgMLocalStatusParams: WdgMLocalStatusParams_Bsw_50ms */        },
    {   1                                            ,  6                                              /* WdgMMode: 0  WdgMLocalStatusParams: WdgMLocalStatusParams_Bsw_5ms */         }  
};


CONST(WdgM_TriggerType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_Trigger[1] =
{
    /* TriggerConditionValue(in mili seconds)          DeviceIdx                                       TriggerModeType             Comment */                                    
    
    {   50                                           ,  WdgIfConf_WdgIfDevice_WdgIfDevice            ,  WDGIF_FAST_MODE            /* WdgMMode: 0  WdgMTrigger: WdgMTrigger_Fast */                                } 
};


CONST(WdgM_PrvModeType, WDGM_CONST_FAST_UNSPECIFIED) WdgM_PrvMode[1] =
{	    /* ExpiredSupervisionCycleTol                  SchMWdgMSupervisionCycle                                 SupervisionCycle(in mili seconds)               NoOfAliveSupervision                            NoOfDeadlineSupervision                         NoOfLocalStatusParams                           NoOfTrigger                                     PtrToAliveSupervision                           PtrToDeadlineSupervision                        PtrToLocalStatusParams                          PtrToTrigger                                    Comment */                                    
    
    {   0                                            ,  RTE_MODE_WdgMSupervisionCycle_SUPERVISION_CYCLE_0      ,  WDGM_SUPERVISION_CYCLE_0                     ,  7                                            ,  0                                            ,  7                                            ,  1                                            ,  &WdgM_AliveSupervision[0]                    ,  NULL_PTR                                     ,  &WdgM_LocalStatusParams[0]                   ,  &WdgM_Trigger[0]                               /* WdgMMode: WdgMMode_Fast */                }
};

CONST(WdgM_ConfigType, WDGM_CONST_FAST_UNSPECIFIED)  WdgM_Config =
{
    0                                                           , /* InitialMode */
    1                                                           , /* NoOfMode */
    WDGM_INVALID_DEM_EVENT_ID                                   , /* ErrorImproperCaller */
    WDGM_INVALID_DEM_EVENT_ID                                   , /* ErrorSupervision */
    WDGM_INVALID_DEM_EVENT_ID                                   , /* ErrorSetMode */
    NULL_PTR                                                    , /* PtrToRunningCounterValue */
    NULL_PTR                                                    , /* PtrToDeadlineIndices */
    &WdgM_PrvMode[0]                                              /* PtrToMode */
};


#define      WDGM_STOP_SEC_CONFIG_DATA_FAST_UNSPECIFIED
#include "WdgM_Cfg_MemMap.h"

