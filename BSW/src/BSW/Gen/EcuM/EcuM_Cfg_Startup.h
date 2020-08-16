


#ifndef ECUM_CFG_STARTUP_H
#define ECUM_CFG_STARTUP_H

/**************************************************************************************************/
/* Preprocessor includes                                                                          */
/**************************************************************************************************/
#include "Os.h" /* this is specified by Coding guideline as <ExtModule>.h. required for AppModeType */
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
	#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
	#error "AUTOSAR minor version undefined or mismatched"
#endif


#if (ECUM_INCLUDE_DET == STD_ON)
#include "Det.h"
#endif
#include "Mcu.h"
#include "Mcl.h"
#include "Port.h"
#include "Gpt.h"
//#include "Wdg.h"
#include "WdgM.h"
#include "BswM.h" /*Required for BswM init pointer used inside EcuM_Cfg_adrModuleInitRef_t*/
/***************************************************************************************************
* Generated type declarations
***************************************************************************************************/

typedef struct
{
//    const Det_ConfigType *DetInitConfigPtr_cpst;
    const Mcu_ConfigType *McuInitConfigPtr_cpst;
    const Mcl_ConfigType *MclInitConfigPtr_cpst;
    const Port_ConfigType *PortInitConfigPtr_cpst;
    const Gpt_ConfigType *GptInitConfigPtr_cpst;
//    const Wdg_ConfigType *WdgInitConfigPtr_cpst;
//    const WdgM_ConfigType *WdgMInitConfigPtr_cpst;
    const BswM_ConfigType *BswM_InitConfigPtr_cpst; /* BswM_Init pointer*/
} EcuM_Cfg_adrModuleInitRef_t;

/* Structure holds the pointers passed to the Module Init Function */
typedef struct
{
    AppModeType DefaultAppMode;
    EcuM_ShutdownTargetInfoType DefaultShutdownTarget; /*Structure to hold the Default Shutdown Target*/
    EcuM_Cfg_adrModuleInitRef_t ModuleInitPtrPB; /*Structure to hold the post build configuration pointer of the modules*/
    const EcuM_Cfg_dataWkupPNCRefStruct_tst *adrWkupPNCRefs; /* Pointer to the PNC references associated with Wakeups */
    uint8 PostBuildHash[ECUM_CFG_LENGTH_OF_HASH];
} EcuM_ConfigType;

#define ECUM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"


extern CONST( EcuM_ConfigType, ECUM_CONST ) EcuM_Config;


#define ECUM_NO_OF_ECUMCONFIGSETS 1

extern CONSTP2CONST(EcuM_ConfigType,AUTOMATIC,ECUM_CONST) EcuM_EcuMConfigurations_cpcast[ECUM_NO_OF_ECUMCONFIGSETS];

#define ECUM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"

#endif /*ECUM_CFG_STARTUP_H*/


