/**
*   @file    Mcu_STCU_Types.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Exported data outside of the Mcu from STCU.
*   @details Public data types exported outside of the Mcu driver.
*
*   @addtogroup MCU
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MC
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_HF5_ASR_REL_4_0_REV_0003_20190514
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/


#ifndef MCU_STCU_TYPES_H
#define MCU_STCU_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu_Cfg.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_STCU_TYPES_VENDOR_ID                     43
#define MCU_STCU_TYPES_AR_RELEASE_MAJOR_VERSION      4
#define MCU_STCU_TYPES_AR_RELEASE_MINOR_VERSION      0
#define MCU_STCU_TYPES_AR_RELEASE_REVISION_VERSION   3
#define MCU_STCU_TYPES_SW_MAJOR_VERSION              1
#define MCU_STCU_TYPES_SW_MINOR_VERSION              0
#define MCU_STCU_TYPES_SW_PATCH_VERSION              1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and STCU header file are from the same vendor */
#if (MCU_STCU_TYPES_VENDOR_ID != MCU_CFG_VENDOR_ID)
    #error "Mcu_STCU_Types.h and Mcu_Cfg.h have different vendor ids"
#endif
/* Check if source file and STCU header file are of the same Autosar version */
#if ((MCU_STCU_TYPES_AR_RELEASE_MAJOR_VERSION != MCU_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_STCU_TYPES_AR_RELEASE_MINOR_VERSION != MCU_CFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_STCU_TYPES_AR_RELEASE_REVISION_VERSION != MCU_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_STCU_Types.h and Mcu_Cfg.h are different"
#endif
/* Check if source file and STCU header file are of the same Software version */
#if ((MCU_STCU_TYPES_SW_MAJOR_VERSION != MCU_CFG_SW_MAJOR_VERSION) || \
     (MCU_STCU_TYPES_SW_MINOR_VERSION != MCU_CFG_SW_MINOR_VERSION) || \
     (MCU_STCU_TYPES_SW_PATCH_VERSION != MCU_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_STCU_Types.h and Mcu_Cfg.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/


/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* MCU_STCU_TYPES_H */

/** @} */
