

#ifndef ECUM_TYPES_H
#define ECUM_TYPES_H
/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "EcuM_Cfg.h"
#include "EcuM_RunTime.h" /*For run time measurement*/

#if(ECUM_CFG_ECUC_RB_RTE_IN_USE != FALSE)
#include "Rte_EcuM_Type.h" /*Rule BSW_ServiceRTE_002 for rte generated EcuM types*/
#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE
/*
**************************************************************************************************
* Generated type declarations
**************************************************************************************************
*/
#if(ECUM_CFG_ECUC_RB_RTE_IN_USE == FALSE)
/*Integrator can extend this list of Shutdown causes by manually adding the #define.
 * Range for additional shutdown causes is 4 - 255*/

#define ECUM_CAUSE_UNKNOWN                       0
#define ECUM_CAUSE_ECU_STATE                     1
#define ECUM_CAUSE_WDGM                          2
#define ECUM_CAUSE_DCM                           3

/*****EcuM statndard Boot targets ***********/
#define ECUM_BOOT_TARGET_APP                     0
#define ECUM_BOOT_TARGET_OEM_BOOTLOADER          1
#define ECUM_BOOT_TARGET_SYS_BOOTLOADER          2

#ifndef RTE_MODE_EcuM_Mode_POST_RUN
#define RTE_MODE_EcuM_Mode_POST_RUN              0U
#endif /*RTE_MODE_EcuM_Mode_POST_RUN*/
#ifndef RTE_MODE_EcuM_Mode_RUN
#define RTE_MODE_EcuM_Mode_RUN                   1U
#endif /*RTE_MODE_EcuM_Mode_RUN*/
#ifndef RTE_MODE_EcuM_Mode_SHUTDOWN
#define RTE_MODE_EcuM_Mode_SHUTDOWN              2U
#endif /*RTE_MODE_EcuM_Mode_SHUTDOWN*/
#ifndef RTE_MODE_EcuM_Mode_SLEEP
#define RTE_MODE_EcuM_Mode_SLEEP                 3U
#endif /*RTE_MODE_EcuM_Mode_SLEEP*/
#ifndef RTE_MODE_EcuM_Mode_STARTUP
#define RTE_MODE_EcuM_Mode_STARTUP               4U
#endif /*RTE_MODE_EcuM_Mode_STARTUP*/

/*****EcuM Shutdown targets ***********/
#ifndef ECUM_SHUTDOWN_TARGET_SLEEP
#define ECUM_SHUTDOWN_TARGET_SLEEP               0U
#endif /*ECUM_SHUTDOWN_TARGET_SLEEP*/
#ifndef ECUM_SHUTDOWN_TARGET_RESET
#define ECUM_SHUTDOWN_TARGET_RESET               1U
#endif /*ECUM_SHUTDOWN_TARGET_RESET*/
#ifndef ECUM_SHUTDOWN_TARGET_OFF
#define ECUM_SHUTDOWN_TARGET_OFF                 2U
#endif /*ECUM_SHUTDOWN_TARGET_OFF*/

typedef uint8 EcuM_BootTargetType;

typedef uint16 EcuM_ShutdownModeType;

typedef uint8 EcuM_ShutdownCauseType;

typedef uint8 EcuM_ShutdownTargetType;

typedef uint32 EcuM_TimeType;

typedef uint16  EcuM_UserType;

#if (ECUM_CFG_MODE_HANDLING == STD_ON)
typedef uint8 Rte_ModeType_EcuM_Mode;
#endif

#endif//ECUM_CFG_ECUC_RB_RTE_IN_USE

typedef uint32      EcuM_WakeupSourceType;

typedef uint8       EcuM_ResetType;

typedef uint8       EcuM_WakeupStatusType;

typedef uint8       EcuM_RunStatusType;

typedef uint8       EcuM_StateType;

typedef struct
{
    EcuM_ShutdownCauseType  ShutdownCause;
#if (ECUM_STARTUP_DURATION == TRUE)
    uint32   TimeMeasured;
#endif//ECUM_STARTUP_DURATION
} EcuM_ShutdownInfoType;

typedef struct
{
    EcuM_ShutdownTargetType  ShutdownTarget;
    EcuM_ShutdownModeType   mode;
    EcuM_ShutdownInfoType ShutdownInfo;

} EcuM_ShutdownTargetInfoType;


#endif /*ECUM_TYPES_H*/

