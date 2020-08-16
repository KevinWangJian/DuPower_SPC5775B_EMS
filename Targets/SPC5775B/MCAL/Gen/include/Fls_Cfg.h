/**
*   @file    Fls_Cfg.h 
*   @implements Fls_Cfg.h_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Fls - AUTOSAR Module Flash Driver.
*   @details Definitions of all pre-compile configuration parameters.
*
*   @addtogroup FLS
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : Flash_Memory
*   Dependencies         : 
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_ASR_REL_4_0_REV_0003_20170519
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef FLS_CFG_H
#define FLS_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Fls_Cfg_H_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice.
* Because of Autosar requirement MEMMAP003 of memory mapping
* 
* @section Fls_Cfg_H_REF_2
* Violates MISRA 2004 Required Rule 8.7, could define variable at block scope.
* The data structure of type Fls_ConfigType shall be defined as external according to FLS352.
* 
* @section [global]
* Violates MISRA 2004 Required Rule 5.1,
* Identifiers (internal and external) shall not rely on the significance of more than 31 characters. 
* The used compilers use more than 31 chars for identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Fls_Types.h"
#include "Mcal.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define FLS_VENDOR_ID_CFG                    43
#define FLS_MODULE_ID_CFG                    92
#define FLS_AR_RELEASE_MAJOR_VERSION_CFG     4
#define FLS_AR_RELEASE_MINOR_VERSION_CFG     0
#define FLS_AR_RELEASE_REVISION_VERSION_CFG  3
#define FLS_SW_MAJOR_VERSION_CFG             1
#define FLS_SW_MINOR_VERSION_CFG             0
#define FLS_SW_PATCH_VERSION_CFG             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Fls configuration header file are of the same vendor */
#if (FLS_TYPES_VENDOR_ID != FLS_VENDOR_ID_CFG)
#error "Fls_Types.h and Fls_Cfg.h have different vendor ids"
#endif
/* Check if current file and Fls configuration header file are of the same Autosar version */
#if ((FLS_TYPES_AR_RELEASE_MAJOR_VERSION    != FLS_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (FLS_TYPES_AR_RELEASE_MINOR_VERSION    != FLS_AR_RELEASE_MINOR_VERSION_CFG) || \
     (FLS_TYPES_AR_RELEASE_REVISION_VERSION != FLS_AR_RELEASE_REVISION_VERSION_CFG) \
    )
#error "AutoSar Version Numbers of Fls_Types.h and Fls_Cfg.h are different"
#endif
/* Check if current file and Fls configuration header file are of the same software version */
#if ((FLS_TYPES_SW_MAJOR_VERSION != FLS_SW_MAJOR_VERSION_CFG) || \
     (FLS_TYPES_SW_MINOR_VERSION != FLS_SW_MINOR_VERSION_CFG) || \
     (FLS_TYPES_SW_PATCH_VERSION != FLS_SW_PATCH_VERSION_CFG) \
    )
#error "Software Version Numbers of Fls_Types.h and Fls_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if current file and Std_Types header file are of the same version */
    #if ((FLS_AR_RELEASE_MAJOR_VERSION_CFG != MCAL_AR_RELEASE_MAJOR_VERSION) || \
         (FLS_AR_RELEASE_MINOR_VERSION_CFG != MCAL_AR_RELEASE_MINOR_VERSION)\
        )
        #error "AutoSar Version Numbers of Fls_Types.h and Mcal.h are different"
    #endif
#endif



/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/

/* STD_ON: Flash access code loaded on job start / unloaded on job end or error */
#define FLS_AC_LOAD_ON_JOB_START    (STD_ON)

/* Compile switch to enable and disable the Fls_Cancel function */
#define FLS_CANCEL_API              (STD_ON)

/* Compile switch to enable and disable the Fls_Compare function */
#define FLS_COMPARE_API             (STD_ON)

/* Pre-processor switch to enable and disable development error detection */
#define FLS_DEV_ERROR_DETECT        (STD_ON)

/* Compile switch to enable and disable the Fls_GetJobResult function */
#define FLS_GET_JOB_RESULT_API      (STD_ON)

/* Compile switch to enable and disable the Fls_GetStatus function */
#define FLS_GET_STATUS_API          (STD_ON)

/* Compile switch to enable and disable the Fls_SetMode function */
#define FLS_SET_MODE_API            (STD_ON)

/* Pre-processor switch to enable / disable the API to use interrupts for erase and write jobs */
#define FLS_USE_INTERRUPTS          (STD_OFF)

/* Pre-processor switch to enable / disable the API to read out the modules version information */
#define FLS_VERSION_INFO_API        (STD_ON)

/* Pre-processor switch to enable / disable the API to report data storage (ECC) errors to the flash driver */
#define FLS_DSI_HANDLER_API         (STD_OFF)

/* Pre-processor switch to enable / disable the API to report data storage (ECC) errors to the flash driver */
#define FLS_ECC_WITH_NO_EXCEPTION   (STD_OFF)

/* Pre-processor switch to enable / disable the erase blank check */
#define FLS_ERASE_BLANK_CHECK       (STD_ON)

/* Pre-processor switch to enable / disable the write blank check */
#define FLS_WRITE_BLANK_CHECK       (STD_ON)

/* Pre-processor switch to enable / disable the write verify check */
#define FLS_WRITE_VERIFY_CHECK      (STD_ON)

/* The maximum number of bytes to blank check in one cycle of the flash driver's job processing function */
#define FLS_MAX_ERASE_BLANK_CHECK   256U

/* Timeout handling enabled */
#define FLS_TIMEOUT_HANDLING       (STD_OFF)

/* Timeout value for Erase and Write operation */
#define FLS_ASYNC_WRITE_TIMEOUT_VALUE     0U
#define FLS_ASYNC_ERASE_TIMEOUT_VALUE     0U
#define FLS_SYNC_WRITE_TIMEOUT_VALUE      0U
#define FLS_SYNC_ERASE_TIMEOUT_VALUE      0U

/* Timeout value for Abort operation */
#define FLS_ABT_TIMEOUT_VALUE        0U

/* Number of bytes in RAM needed for the erase flash access code */
#define FLS_AC_SIZE_ERASE           0U

/* Number of bytes in RAM needed for the write flash access code */
#define FLS_AC_SIZE_WRITE           0U

/* The contents of an erased flash memory cell */
#define FLS_ERASED_VALUE            0xffffffffU

/* Fls Driver Index */
#define FLS_DRIVER_INDEX            0U

/**
* @brief   Switches the Production Error Detection and Notification OFF
*/
#define FLS_DISABLE_DEM_REPORT_ERROR_STATUS        (STD_ON)


/* Flash operation abort supported in hardware */
#define FLS_HW_OPERATION_ABORT_SUPPORTED        (STD_ON)    

/* Flash enable redundant read error check */
#define FLS_EXTENDED_READ_ERROR_CHECK           (STD_OFF)

/* Flash page size in bytes */
#define FLS_PAGE_SIZE               8U

/* User mode support */
#define FLS_ENABLE_USER_MODE_SUPPORT         (STD_OFF) 
#define FLS_USER_MODE_REG_PROT_ENABLED      (STD_OFF)  

#ifdef MCAL_CACHE_RUNTIME_MNGMNT
    #if (STD_ON == MCAL_CACHE_RUNTIME_MNGMNT)  
        /* Enable the use of cache invalidate */
                #define FLS_SYNCRONIZE_CACHE        (STD_OFF)
            #else /* MCAL_CACHE_RUNTIME_MNGMNT */     
        #define FLS_SYNCRONIZE_CACHE        (STD_OFF)         
    #endif /* MCAL_CACHE_RUNTIME_MNGMNT */     
#else /* MCAL_CACHE_RUNTIME_MNGMNT */    
    #define FLS_SYNCRONIZE_CACHE        (STD_OFF)    
#endif /* MCAL_CACHE_RUNTIME_MNGMNT */ 

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/* Map access routine type according to the timeout handling setting */
#if FLS_TIMEOUT_HANDLING == STD_ON
    /* access routine with timeout parameters */
    typedef Fls_Flash_AcErasePtrTOType Fls_Flash_AcErasePtrType;
    typedef Fls_Flash_AcWritePtrTOType Fls_Flash_AcWritePtrType;
#else
    /* access routine without timeout parameters */
    typedef Fls_Flash_AcErasePtrNoTOType Fls_Flash_AcErasePtrType;
    typedef Fls_Flash_AcWritePtrNoTOType Fls_Flash_AcWritePtrType;
#endif /* FLS_TIMEOUT_HANDLING == STD_ON */

/**
* @brief          Fls Config Type
* @details        Fls module initialization data structure
* @implements     Fls_ConfigType_typedef
*/
typedef struct 
{
    /** 
    * @brief pointer to erase access code function in RAM or ROM
    */
    Fls_Flash_AcErasePtrType acErasePtr; 
    /** 
    * @brief pointer to write access code function in RAM or ROM 
    */
    Fls_Flash_AcWritePtrType acWritePtr; 
    /** 
    * @brief pointer to ac callback function 
    */  
    Fls_ACCallbackPtrType acCallBackPtr;
    /** 
    * @brief pointer to job end notification function 
    */
    Fls_JobEndNotificationPtrType jobEndNotificationPtr; 
    /** 
    * @brief pointer to job error notification function 
    */
    Fls_JobErrorNotificationPtrType jobErrorNotificationPtr; 
    /** 
    * @brief pointer to start flash access notification 
    */
    Fls_StartFlashAccessNotifPtrType startFlashAccessNotifPtr; 
    /** 
    * @brief pointer to finished flash access notification
    */
    Fls_FinishedFlashAccessNotifPtrType finishedFlashAccessNotifPtr; 
    /** 
    * @brief default FLS device mode after initialization (MEMIF_MODE_FAST, MEMIF_MODE_SLOW) 
    */
    MemIf_ModeType eDefaultMode; 
    /** 
    * @brief max number of bytes to read in one cycle of Fls_MainFunction (fast mode) 
    */
    Fls_LengthType u32MaxReadFastMode; 
    /** 
    * @brief max number of bytes to read in one cycle of  Fls_MainFunction (normal mode) 
    */
    Fls_LengthType u32MaxReadNormalMode; 
    /** 
    * @brief max number of bytes to write in one cycle of Fls_MainFunction (fast mode) 
    */
    Fls_LengthType u32MaxWriteFastMode; 
    /** 
    * @brief max number of bytes to write in one cycle of  Fls_MainFunction (normal mode) 
    */
    Fls_LengthType u32MaxWriteNormalMode; 
    /** 
    * @brief number of configured logical sectors 
    */
    Fls_SectorCountType u32SectorCount;
    /** 
    * @brief pointer to array containing last logical address of each configured sector 
    */
    CONST( Fls_AddressType, FLS_CONST) (*pSectorEndAddr)[]; 
    /**
    * @brief pointer to array containing physical sector ID of each configured sector 
    */
    CONST( Fls_Flash_PhysicalSectorType, FLS_CONST) (*pPhysicalSector)[]; 
    /**
    * @brief pointer to array containing flags set of each configured sector 
    */
    CONST( uint8, FLS_CONST) (*pSectorFlags)[]; 
    /**
    * @brief pointer to array containing page size of each configured sector 
    */
    CONST( Fls_LengthType, FLS_CONST) (*pSectorProgSize)[]; 
    /**
    * @brief pointer to array containing Unlock information of each configured sector 
    */
    CONST( uint8, FLS_CONST) (*pSectorUnlock)[];
    
    /** 
     * @brief FLS Config Set CRC checksum     
     */    
    Fls_CrcType u16ConfigCrc;
     
} Fls_ConfigType;

/*==================================================================================================
                                 GLOBAL CONSTANT DECLARATIONS
==================================================================================================*/

#define FLS_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Fls_Cfg_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "MemMap.h"


/* Precompile Support OFF */
/* FLS_PRECOMPILE_SUPPORT must be defined only for Pre-Compile version. */

#ifdef FLS_PRECOMPILE_SUPPORT
/* Declaration of pre-compile structure */ 
/* @violates @ref Fls_Cfg_H_REF_2 Could define variable at block scope */
extern CONST(Fls_ConfigType, FLS_CONST) Fls_ConfigSetPC; 
#else    
/* Declaration of post-build structure (FlsConfigSet_0)*/
/* @violates @ref Fls_Cfg_H_REF_2 Could define variable at block scope */
extern CONST(Fls_ConfigType, FLS_CONST) FlsConfigSet_0;     
#endif

#define FLS_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Fls_Cfg_H_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* FLS_CFG_H */
