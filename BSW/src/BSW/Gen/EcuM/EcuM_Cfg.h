


#ifndef ECUM_CFG_H
#define ECUM_CFG_H

/*****************************************************************************************************
* 									Includes
*****************************************************************************************************/

#include "Mcu.h" /* specified in SWS. required for Mcu_ResetType */
#if (!defined(MCU_AR_RELEASE_MAJOR_VERSION) || (MCU_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(MCU_AR_RELEASE_MINOR_VERSION) || (MCU_AR_RELEASE_MINOR_VERSION != 2))
//#error "AUTOSAR minor version undefined or mismatched"
#endif


#include "Os.h"
#if (!defined(OS_AR_RELEASE_MAJOR_VERSION) || (OS_AR_RELEASE_MAJOR_VERSION != 4))
#error "AUTOSAR major version undefined or mismatched"
#endif
#if (!defined(OS_AR_RELEASE_MINOR_VERSION) || (OS_AR_RELEASE_MINOR_VERSION != 2))
#error "AUTOSAR minor version undefined or mismatched"
#endif

/*****************************************************************************************************
 *                                   CONFIGURATION PARAMETERS
 ****************************************************************************************************/

#define	ECUM_VERSION_INFO_API	(STD_ON)


#define ECUM_DEV_ERROR_DETECT 	(STD_ON) 


#define ECUM_INCLUDE_DET (STD_ON)


#define ECUM_CFG_MULTICORE_ENABLED	(STD_OFF)


/* If ECUM_CFG_MODE_HANDLING is STD_ON then All the Mode management APi's and Run handling protocol will be enabled*/
#define ECUM_CFG_MODE_HANDLING  (STD_OFF)



#define ECUM_CFG_SLAVECORE_EARLIER_START  (STD_OFF)


/* The Configured OS core is generated and it behaves as the Master Core, where all the Startup,Wakeup and Shutdown sequences are carried out in that Configured Core */
#define ECUM_CFG_STARTUP_CORE    OS_CORE_ID_MASTER 

/*If ECUM_SLEEP_SUPPORT_ENABLE is true all the api's related to sleep will be active else disabled */
#define ECUM_SLEEP_SUPPORT_ENABLE  FALSE 



/* Number of Sleep modes */

#define ECUM_CFG_NUM_SLEEP_MODES  ((uint16)0)



/* Parameter to indicate whether RTE is enabled or disabled*/
#define ECUM_CFG_ECUC_RB_RTE_IN_USE  TRUE 

/* Number of OS cores */
#define ECUM_CFG_NUM_OS_CORES	((uint16)1)
    

/* Number of Reset modes */
#define ECUM_CFG_NUM_RESET_MODES	(3U)

/* Number of configured go down caller */
#define ECUM_CFG_GODOWN_CALLER_ARR_LEN	(1U)

/* Number of configured wakeup sources */
#define ECUM_NUM_OF_WKP_SOURCES (5U)



/* The total number of shutdown causes configured */
#define ECUM_CFG_NUM_SHUTDOWN_CAUSE 4
/* As per current implementation this is a fixed value and does not depend upon configuration */
#define ECUM_CFG_LENGTH_OF_HASH		(16)

#if ECUM_SLEEP_SUPPORT_ENABLE
#define ECUM_NORMAL_MCU_MODE ((Mcu_ModeType))
typedef struct 
{
    boolean IsCPUSuspend;                       /*Tells whether CPU is halted in this sleepMode*/
    Mcu_ModeType  EquivalentMcuMode;            /*to store the selected MCU mode*/
    uint32   WakeupSourceMask;   /*Store the OR-ed value of all the Wkup Soure masks Selected*/
}EcuM_Cfg_dataSleepModeStruct_tst;
#endif/*ECUM_SLEEP_SUPPORT_ENABLE*/

typedef struct
{
    boolean IsComChannelPresent	;			 /*For checking whether the com channel referance is given or not*/
    uint8 ComChannelReferance;				 /* For Mapping Comm channel as Wakeupsource*/
    Mcu_ResetType   ResetReason;             /*For Mapping the actual reset reason from Mcu Driver to the Wakeup Source*/
    uint16  ValidationTimeout;               /*in multiples of no of mainfunction cycles*/
    boolean IsWakeupSourcePolling;           /*Boolean variable holds whether wakeup source needs polling or not */
    uint32   WakeupSourceId;  /*uint32 each bit defines a wkp source */
}EcuM_Cfg_dataWkupSrcStruct_tst;

typedef struct
{
    uint8 nbrOfComMPNCRef;                   /*uint8 variable to specify the number of PNC references*/                      
    const uint8 * ListOfPNCRefs;                   /*uint8 pointer to specify the array of PNC references*/
}EcuM_Cfg_dataWkupPNCRefStruct_tst;

#define ECUM_START_SEC_CONFIG_DATA_8
#include "EcuM_Cfg_MemMap.h"
extern CONST( uint8, ECUM_CONST ) EcuM_Cfg_dataPreCompileHash_au8[ECUM_CFG_LENGTH_OF_HASH];
#define ECUM_STOP_SEC_CONFIG_DATA_8
#include "EcuM_Cfg_MemMap.h"

#define ECUM_START_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
extern CONST( EcuM_Cfg_dataWkupSrcStruct_tst,  ECUM_CONST)  EcuM_Cfg_idxWakeupSourcesPC_au32[ECUM_NUM_OF_WKP_SOURCES];


extern CONST( EcuM_Cfg_dataWkupPNCRefStruct_tst,  ECUM_CONST)  EcuM_Cfg_dataWkupPNCRef_cast[ECUM_NUM_OF_WKP_SOURCES];


#if ECUM_SLEEP_SUPPORT_ENABLE
extern CONST( EcuM_Cfg_dataSleepModeStruct_tst  ,  ECUM_CONST)  EcuM_Cfg_idxSleepModes_au32[ECUM_CFG_NUM_SLEEP_MODES];
#endif/*ECUM_SLEEP_SUPPORT_ENABLE*/


#define ECUM_STOP_SEC_CONST_UNSPECIFIED
#include "EcuM_Cfg_MemMap.h"
#define ECUM_START_SEC_CONST_16
#include "EcuM_Cfg_MemMap.h"
	extern CONST( uint16, ECUM_CONST) EcuM_Cfg_idxGoDownValidCallerArr_au16[ECUM_CFG_GODOWN_CALLER_ARR_LEN];
	

#define ECUM_STOP_SEC_CONST_16
#include "EcuM_Cfg_MemMap.h"

/*
If NvM module is present it will set the ECUM_CFG_NVM_BLOCK_CONFIGURED to TRUE
other wise it set the flag to FALSE
*/

#define ECUM_CFG_NVM_BLOCK_CONFIGURED TRUE
 

/* All Configured Sleep Modes */
/*  Macros for EcuM Wakeup source type */
#define  ECUM_NO_WKUP_SRC               ((uint32)0)

#define  ECUM_WKUP_SRC_START_BIT_MASK   ((uint32)0x00000001)


/* Unconfigured Wakeup Sources*/
#define  ECUM_UNCONFIGURED_WKP_SOURCES  (~ECUM_KNOWN_WAKEUP_SOURCES)

/* Basic wakeup sources */
#define  ECUM_UNINTENDED_RESET_MSK      (uint32) (  EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET | \
                                                    EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG | \
                                                    EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG | \
                                                    EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER | \
                                                    EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET \
                                         )

/* All configured wakeup sources */
#define  ECUM_KNOWN_WAKEUP_SOURCES      (uint32) (EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER | \
		EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET | \
		EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET | \
		EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG | \
		EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG \
		)

/* All configured wakeup sources with validation timeout */

#define  ECUM_WAKEUP_SOURCES_WITH_VALIDATION     (uint32)(0x00u)


/* All configured wakeup sources without validation timeout */

#define  ECUM_WAKEUP_SOURCES_WITHOUT_VALIDATION     (uint32)(EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER| \
               EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET| \
               EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET| \
               EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG| \
               EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG \
               )


/*Wakeup Source id in Hex*/
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_POWER ((EcuM_WakeupSourceType) 0x1u)
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_RESET ((EcuM_WakeupSourceType) 0x2u)
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_RESET ((EcuM_WakeupSourceType) 0x4u)
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_INTERNAL_WDG ((EcuM_WakeupSourceType) 0x8u)
#define EcuMConf_EcuMWakeupSource_ECUM_WKSOURCE_EXTERNAL_WDG ((EcuM_WakeupSourceType) 0x10u)

/*Among the known configured Wakeup mask filtering out the basic five unintended wakeups --> Used in StartupTwo*/
#define  ECUM_NON_BASIC_WKUPS_MSK       ((ECUM_KNOWN_WAKEUP_SOURCES^ECUM_UNINTENDED_RESET_MSK))


/* All configured EcuMFlexUser--> Symbolic name is generated for EcuMFlexUser*/
#define	EcuMConf_EcuMFlexUserConfig_EcuMFlexUserConfig	((uint16)42)


/* All configured Reset Modes--> Symbolic name is generated for EcuMResetModeId*/
#define	EcuMConf_EcuMResetMode_ECUM_RESET_MCU	((EcuM_ResetType)0)
#define	EcuMConf_EcuMResetMode_ECUM_RESET_WDGM	((EcuM_ResetType)1)
#define	EcuMConf_EcuMResetMode_ECUM_RESET_IO	((EcuM_ResetType)2)


/* All configured EcuMShutdownCauses--> Symbolic name is generated for EcuMShutdownCauseId*/
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_UNKNOWN    ((EcuM_ShutdownCauseType)0)
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_ECU_STATE    ((EcuM_ShutdownCauseType)1)
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_WDGM    ((EcuM_ShutdownCauseType)2)
#define EcuMConf_EcuMShutdownCause_ECUM_CAUSE_DCM    ((EcuM_ShutdownCauseType)3)

#endif /*ECUM_CFG_H*/
