/**
*   @file CDD_Mcl_Cfg.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcl - contains the configuration data of the MCL driver
*   @details Contains the configuration data of the MCL driver
*
*   @addtogroup MCL_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : eDMA
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_HF4_ASR_REL_4_0_REV_0003_20180627
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/


#ifndef CDD_MCL_CFG_H
#define CDD_MCL_CFG_H

#ifdef __cplusplus
extern "C"{
#endif 
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcl_Cfg_h_REF_1
*          Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
*          contents of a header file being included twice
*          This is not a violation since all header files are protected against multiple inclusions
*
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
*          on the significance of more than 31 characters. The used compilers use more than 31 chars 
*          for identifiers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcl_Cfg_h_REF_3
*          Violates MISRA 2004 Required Rule 19.4, C macros shall only expand to a braced initialiser, 
*          a constant, a parenthesised expression, a type qualifier, a storage class specifier, or a
*          do-while-zero construct. 
*          This is used to abstract the export of configuration sets or for a function define.
*
*/

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
/*
* @violates @ref Mcl_Cfg_h_REF_1 MISRA 2004 Required Rule 19.15 precautions to prevent the
*            contents of a header file being included twice
*/
#include "Mcl_EnvCfg.h"
#include "Mcal.h"

#include "Dem.h"
    
    
/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCL_VENDOR_ID_CFG                       43

#define MCL_AR_RELEASE_MAJOR_VERSION_CFG        4
#define MCL_AR_RELEASE_MINOR_VERSION_CFG        0
#define MCL_AR_RELEASE_REVISION_VERSION_CFG     3

#define MCL_SW_MAJOR_VERSION_CFG                1
#define MCL_SW_MINOR_VERSION_CFG                0
#define MCL_SW_PATCH_VERSION_CFG                1
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCL_AR_RELEASE_MAJOR_VERSION_CFG != MCAL_AR_RELEASE_MAJOR_VERSION) || \
        (MCL_AR_RELEASE_MINOR_VERSION_CFG != MCAL_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of CDD_Mcl_Cfg.h and Mcal.h are different"
    #endif
#endif

/* Check if header file and Dem.h file are of the same Autosar version */
 #ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
     /* Check if source file and Dem header file are of the same Autosar version */
     #if (( MCL_AR_RELEASE_MAJOR_VERSION_CFG != DEM_AR_RELEASE_MAJOR_VERSION) || \
          ( MCL_AR_RELEASE_MINOR_VERSION_CFG != DEM_AR_RELEASE_MINOR_VERSION))
         #error "AutoSar Version Numbers of CDD_Mcl_Cfg.h and Dem.h are different"
     #endif
 #endif

#if (MCL_VENDOR_ID_CFG != MCL_ENVCFG_VENDOR_ID)
    #error "CDD_Mcl_Cfg.h and Mcl_EnvCfg.h have different vendor ids"
#endif
/* Check if current file and Mcl_CfgEnv header file are of the same Autosar version */
#if (( MCL_AR_RELEASE_MAJOR_VERSION_CFG != MCL_ENVCFG_AR_RELEASE_MAJOR_VERSION) || \
     ( MCL_AR_RELEASE_MINOR_VERSION_CFG != MCL_ENVCFG_AR_RELEASE_MINOR_VERSION) || \
     ( MCL_AR_RELEASE_REVISION_VERSION_CFG !=  MCL_ENVCFG_AR_RELEASE_REVISION_VERSION))
     #error "AutoSar Version Numbers of CDD_Mcl_Cfg.h and Mcl_EnvCfg.h are different"
#endif
/* Check if current file and Mcl_CfgEnv header file are of the same software version */
#if ((MCL_SW_MAJOR_VERSION_CFG != MCL_ENVCFG_SW_MAJOR_VERSION) || \
     (MCL_SW_MINOR_VERSION_CFG != MCL_ENVCFG_SW_MINOR_VERSION) || \
     (MCL_SW_PATCH_VERSION_CFG != MCL_ENVCFG_SW_PATCH_VERSION))
     #error "Software Version Numbers of CDD_Mcl_Cfg.h and Mcl_EnvCfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
    

#define MCL_PRECOMPILE_SUPPORT (STD_OFF)

/**
*   @brief  Switches the Development Error Detection and Notification on or off.
*        STD_ON: Enabled. STD_OFF: Disabled.
*   
*/
#define MCL_DEV_ERROR_DETECT                  (STD_ON)

/**
* @{
*   @brief Configuration of Optional API's
*/
/**
*   @brief  Adds or removes the service Mcl_GetVersionInfo() from the code.
*        STD_ON: Mcl_GetVersionInfo() can be used. STD_OFF: Mcl_GetVersionInfo() can not be used.
*   
*/
#define MCL_GET_VERSION_INFO_API              (STD_ON)

/**
* @{
*   @brief Configuration of Optional API's
*/
/**
*   @brief  Adds or removes the service Mcl_DeInit() from the code.
*        STD_ON: Mcl_DeInit() can be used. STD_OFF: Mcl_DeInit() can not be used.
*   
*/
#define MCL_DEINIT_API                        (STD_OFF)

/**
*   @brief   Switches DMA features initialization on or off.
*        STD_ON: Enabled. STD_OFF: Disabled.
*
*/
#define MCL_ENABLE_DMA              (STD_ON)



/**
*   @brief   Switches the Crossbar support on or off.
*        STD_ON: Enabled. STD_OFF: Disabled.
*
*/
#define MCL_CROSSBAR_NUM_INSTANCES        (0x1U)

#define MCL_ENABLE_CROSSBAR              (STD_OFF)  

#define MCL_CROSSBAR_PRS_READONLY        (STD_OFF)

#define MCL_CROSSBAR0_PRS_RESET_VALUE_U32     (0x76543210U)   

#define MCL_CROSSBAR0_CRS_RESET_VALUE_U32     (0x00FF0000U) 



 
/**
* @brief      This define specifies enable or disable initialization of DCHMID register in DMA
*
*/
#define MCL_DMA_ENABLE_INIT_DCHMID (STD_OFF) 
/**
* @brief      This define specifies the number of eDma Channels available for one eDma instance
*
*/
#define MCL_DMA_NB_CHANNELS                      (0x40U)
/**
* @brief      This define specifies the number of eDma instances
*
*/
#define MCL_DMA_NB_CONTROLLERS                   (0x2U)
/**
* @{
*   @brief Configuration of Optional API's
*/
/**
*   @brief  Adds or removes the service Mcl_DmaGetChannelErrorStatus() from the code.
*        STD_ON: Mcl_DmaGetChannelErrorStatusApi() can be used. STD_OFF: Mcl_DmaGetChannelErrorStatusApi() can not be used.
*   
*/
#define MCL_DMA_GET_CH_ERR_STATUS_API            (STD_OFF)

/**
*   @brief  Adds or removes the service Mcl_DmaGetGlobalErrorStatusApi() from the code.
*        STD_ON: Mcl_DmaGetGlobalErrorStatusApi() can be used. STD_OFF: Mcl_DmaGetGlobalErrorStatusApi() can not be used.
*   
*/
#define MCL_DMA_GET_GLOBAL_ERR_STATUS_API            (STD_OFF)

/**
* @brief      This define specifies the number of eTimer channels available
*             on the current platform
*
*/
#define MCL_EDMA_CHANNELS_NO            (128U)

/**
* @brief      This define specifies the number of eTimer channels in a group of channels available
*             on the current platform
*
*/
#define MCL_EDMA_CHANNELS_IN_GROUP            (16U)

/**
* @brief      This define specifies the number of eTimer channels in a group of channels available
*             on the current platform
*
*/
#define MCL_DMA_ERROR_INTERRUPTS_USED            (STD_ON)

/**
* @brief      This define specifies if there is only one transfer completion ISR for all DMA channels within a DMA instance
*             or if there is a transfer completion ISR for each channel
*
*/
#define MCL_DMA_COMBINED_TR_COMPLETION_ISR (STD_OFF)

/**
* @brief      This define specifies if there is only one error ISR for all DMA instances
*             or if there is an error ISR for each DMA instance
*
*/
#define MCL_DMA_COMBINED_ERROR_ISR (STD_OFF)
/**
* @brief      This define specifies if there is Ecc error reporting available          
*
*/
#define MCL_DMA_ECC_REPORTING_ENABLED (STD_ON)

/** 
* @brief  Switch to globaly enable/disable the production error reporting.
*/
#define MCL_DISABLE_DEM_REPORT_ERROR_STATUS  (STD_OFF)



/**
* @brief      This define specifies if there is only one transfer completion ISR for a DMA channel within a DMA instance
*             or if there is a transfer completion ISR for each channel
*
*/
#define MCL_DMA_TR_SEPARATED_ISR (STD_OFF)

/**
* @brief      This define specifies if inside a DMA instance some channels have the same transfer completion ISR assigned,
*             and other channels have their own transfer completion ISR.
*
*/
#define MCL_DMA_TR_COMPLETION_MIXED_ISR (STD_OFF)

/** Define to specify if least one transfer completion interrupt and notification is used, 
*      needed for removing at precompile time the code for ISR handling for the transfer 
*      completion notification processing. This define is needed in both combined transfer
*      completion interrupt and single channel mode. */
#define MCL_DMA_NOTIFICATION_SUPPORTED              (STD_OFF)

/* Transfer size options available */
#define MCL_TRANSFER_SIZE_1_BYTE 
#define MCL_TRANSFER_SIZE_2_BYTE 
#define MCL_TRANSFER_SIZE_4_BYTE 
#define MCL_TRANSFER_SIZE_8_BYTE 
#define MCL_TRANSFER_SIZE_32_BYTE 



/**
* @brief            Support for User mode.
*                   STD_ON: the Mcl driver can be executed from both supervisor and user mode. 
*                   STD_OFF: the Mcl driver can be executed only from supervisor mode. 
*/
#define MCL_ENABLE_USER_MODE_SUPPORT     (STD_OFF)

#define MCL_LOGICAL_ADDRESS_USED     (STD_OFF)



/** @brief Declaration of config sets for PB configuration */

#if (MCL_PRECOMPILE_SUPPORT == STD_OFF )
 /* @violates @ref Mcl_Cfg_h_REF_3 MISRA 2004 Required Rule 19.4 C macros shall only expand to...
 */  
    #define MCL_INIT_CONFIG_PB_DEFINES \
    extern CONST(Mcl_ConfigType, MCL_CONST) MclConfigSet_0;


#endif /* MCL_PRECOMPILE_SUPPORT */

/*==================================================================================================
                                             ENUMS
==================================================================================================*/
#if (MCL_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
/**
* @brief            DEM error reporting configuration.
* @details          This structure contains information DEM error reporting
*/
typedef struct
{
    VAR( Mcal_DemErrorType, MCL_VAR) Mcl_E_Dma_Bus;
    VAR( Mcal_DemErrorType, MCL_VAR) Mcl_E_Dma_Descriptor;
    VAR( Mcal_DemErrorType, MCL_VAR) Mcl_E_Dma_Ecc;
    VAR( Mcal_DemErrorType, MCL_VAR) Mcl_E_Dma_Priority;
    VAR( Mcal_DemErrorType, MCL_VAR) Mcl_E_Dma_Unrecognized;
    VAR( Mcal_DemErrorType, MCL_VAR) Mcl_E_Dma_Inconsistency;
} Mcl_DemConfigType;


#endif


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/



#ifdef __cplusplus
}
#endif

#endif    /* CDD_MCL_CFG_H */
/**@}*/


