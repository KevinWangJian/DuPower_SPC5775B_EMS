/**
*   @file    Mcu_PRAM.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Function prototypes.
*   @details Interface available for IPW layer only.
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


#ifndef MCU_PRAM_H
#define MCU_PRAM_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_PRAM_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_PRAM_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
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
#include "Mcu_PRAM_Types.h"
#include "Mcu_EnvCfg.h"

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_PRAM_VENDOR_ID                        43
#define MCU_PRAM_AR_RELEASE_MAJOR_VERSION         4
#define MCU_PRAM_AR_RELEASE_MINOR_VERSION         0
#define MCU_PRAM_AR_RELEASE_REVISION_VERSION      3
#define MCU_PRAM_SW_MAJOR_VERSION                 1
#define MCU_PRAM_SW_MINOR_VERSION                 0
#define MCU_PRAM_SW_PATCH_VERSION                 1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and PLLDIG header file are from the same vendor */
#if (MCU_PRAM_VENDOR_ID != MCU_PRAM_TYPES_VENDOR_ID)
    #error "Mcu_PRAM.h and Mcu_PRAM_Types.h have different vendor ids"
#endif
/* Check if source file and PLLDIG header file are of the same Autosar version */
#if ((MCU_PRAM_AR_RELEASE_MAJOR_VERSION != MCU_PRAM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_PRAM_AR_RELEASE_MINOR_VERSION != MCU_PRAM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_PRAM_AR_RELEASE_REVISION_VERSION != MCU_PRAM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_PRAM.h and Mcu_PRAM_Types.h are different"
#endif
/* Check if source file and PLLDIG header file are of the same Software version */
#if ((MCU_PRAM_SW_MAJOR_VERSION != MCU_PRAM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_PRAM_SW_MINOR_VERSION != MCU_PRAM_TYPES_SW_MINOR_VERSION) || \
     (MCU_PRAM_SW_PATCH_VERSION != MCU_PRAM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_PRAM.h and Mcu_PRAM_Types.h are different"
#endif

/* Check if source file and PLLDIG header file are from the same vendor */
#if (MCU_PRAM_VENDOR_ID != MCU_SCFG_VENDOR_ID)
    #error "Mcu_PRAM.h and Mcu_EnvCfg.h have different vendor ids"
#endif
/* Check if source file and PLLDIG header file are of the same Autosar version */
#if ((MCU_PRAM_AR_RELEASE_MAJOR_VERSION != MCU_SCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_PRAM_AR_RELEASE_MINOR_VERSION != MCU_SCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_PRAM_AR_RELEASE_REVISION_VERSION != MCU_SCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_PRAM.h and Mcu_EnvCfg.h are different"
#endif
/* Check if source file and PLLDIG header file are of the same Software version */
#if ((MCU_PRAM_SW_MAJOR_VERSION != MCU_SCFG_SW_MAJOR_VERSION) || \
     (MCU_PRAM_SW_MINOR_VERSION != MCU_SCFG_SW_MINOR_VERSION) || \
     (MCU_PRAM_SW_PATCH_VERSION != MCU_SCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_PRAM.h and Mcu_EnvCfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                             ENUMS
==================================================================================================*/


/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
                                     FUNCTION PROTOTYPES
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_PRAM_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files
*/
#include "MemMap.h"


#if (MCU_INIT_CLOCK == STD_ON)

#if defined(MCU_ENABLE_USER_MODE_SUPPORT) \
    && (STD_ON == MCU_ENABLE_USER_MODE_SUPPORT) \
    && defined(MCAL_ENABLE_USER_MODE_SUPPORT) 
/** @violates @ref Mcu_PRAM_h_REF_2 Function-like macro defined.*/
#define  Call_Mcu_PRAM_SetRamWS(PRAM_pClockConfigPtr) \
do\
{ \
        Mcal_Trusted_Call(Mcu_PRAM_SetRamWS,(PRAM_pClockConfigPtr)); \
}\
while(0)
#else
/** @violates @ref Mcu_PRAM_h_REF_2 Function-like macro defined.*/
#define  Call_Mcu_PRAM_SetRamWS( PRAM_pClockConfigPtr) \
do\
{ \
        Mcu_PRAM_SetRamWS(PRAM_pClockConfigPtr); \
}\
while(0)
#endif /* MCU_ENABLE_USER_MODE_SUPPORT && MCAL_ENABLE_USER_MODE_SUPPORT */


FUNC(void, MCU_CODE) Mcu_PRAM_SetRamWS(P2CONST( Mcu_PRAM_ClockConfigType, AUTOMATIC, MCU_APPL_CONST) PRAM_pClockConfigPtr);
#endif /* (MCU_INIT_CLOCK == STD_ON) */


#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_PRAM_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include files
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* MCU_PRAM_H */

/** @} */

