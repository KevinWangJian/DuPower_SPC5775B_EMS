/**
*   @file    Mcu_SSCM.h
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


#ifndef MCU_SSCM_H
#define MCU_SSCM_H


#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_SSCM_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
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
#include "Mcu_SSCM_Types.h"
#include "Mcu_EnvCfg.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_SSCM_VENDOR_ID                          43
#define MCU_SSCM_AR_RELEASE_MAJOR_VERSION           4
#define MCU_SSCM_AR_RELEASE_MINOR_VERSION           0
#define MCU_SSCM_AR_RELEASE_REVISION_VERSION        3
#define MCU_SSCM_SW_MAJOR_VERSION                   1
#define MCU_SSCM_SW_MINOR_VERSION                   0
#define MCU_SSCM_SW_PATCH_VERSION                   1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and PLLDIG header file are from the same vendor */
#if (MCU_SSCM_VENDOR_ID != MCU_SSCM_TYPES_VENDOR_ID)
    #error "Mcu_SSCM.h and Mcu_SSCM_Types.h have different vendor ids"
#endif
/* Check if source file and PLLDIG header file are of the same Autosar version */
#if ((MCU_SSCM_AR_RELEASE_MAJOR_VERSION != MCU_SSCM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_SSCM_AR_RELEASE_MINOR_VERSION != MCU_SSCM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_SSCM_AR_RELEASE_REVISION_VERSION != MCU_SSCM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_SSCM.h and Mcu_SSCM_Types.h are different"
#endif
/* Check if source file and PLLDIG header file are of the same Software version */
#if ((MCU_SSCM_SW_MAJOR_VERSION != MCU_SSCM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_SSCM_SW_MINOR_VERSION != MCU_SSCM_TYPES_SW_MINOR_VERSION) || \
     (MCU_SSCM_SW_PATCH_VERSION != MCU_SSCM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SSCM.h and Mcu_SSCM_Types.h are different"
#endif

/* Check if source file and PLLDIG header file are from the same vendor */
#if (MCU_SSCM_VENDOR_ID != MCU_SCFG_VENDOR_ID)
    #error "Mcu_SSCM.h and Mcu_EnvCfg.h have different vendor ids"
#endif
/* Check if source file and PLLDIG header file are of the same Autosar version */
#if ((MCU_SSCM_AR_RELEASE_MAJOR_VERSION != MCU_SCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_SSCM_AR_RELEASE_MINOR_VERSION != MCU_SCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_SSCM_AR_RELEASE_REVISION_VERSION != MCU_SCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_SSCM.h and Mcu_EnvCfg.h are different"
#endif
/* Check if source file and PLLDIG header file are of the same Software version */
#if ((MCU_SSCM_SW_MAJOR_VERSION != MCU_SCFG_SW_MAJOR_VERSION) || \
     (MCU_SSCM_SW_MINOR_VERSION != MCU_SCFG_SW_MINOR_VERSION) || \
     (MCU_SSCM_SW_PATCH_VERSION != MCU_SCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SSCM.h and Mcu_EnvCfg.h are different"
#endif

/*==================================================================================================
                                           CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
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
* @violates @ref Mcu_SSCM_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "MemMap.h"

#ifdef MCU_ENABLE_USER_MODE_SUPPORT
#if (STD_ON == MCU_ENABLE_USER_MODE_SUPPORT)
    FUNC( void, MCU_CODE) Mcu_SSCM_SetUserAccessAllowed(void);
#endif
#endif

FUNC( void, MCU_CODE) Mcu_SSCM_Init(P2CONST( Mcu_SSCM_ConfigType, AUTOMATIC, MCU_APPL_CONST) SSCM_pConfigPtr);

#if (MCU_GET_SYSTEM_STATE_API == STD_ON)
FUNC( uint32, MCU_CODE) Mcu_SSCM_GetSystemState ( VAR( void, AUTOMATIC));
#endif /* (MCU_GET_SYSTEM_STATE_API == STD_ON) */

#if (MCU_GET_MEM_CONFIG_API == STD_ON)
FUNC( Mcu_SSCM_MemConfigType, MCU_CODE) Mcu_SSCM_GetMemConfig( VAR( void, AUTOMATIC) );
#endif /* (MCU_GET_MEM_CONFIG_API == STD_ON) */

#if (MCU_SSCM_GET_STATUS_API == STD_ON)
FUNC (Mcu_SSCM_StatusType, MCU_CODE) Mcu_SSCM_GetStatus(VAR( void, AUTOMATIC));
#endif /* MCU_SSCM_GET_STATUS_API == STD_ON */

#ifdef MCU_SSCM_GET_UOPS_API
#if (MCU_SSCM_GET_UOPS_API == STD_ON)
FUNC (Mcu_SSCM_UopsType, MCU_CODE) Mcu_SSCM_GetUops(VAR( void, AUTOMATIC));
#endif /* MCU_SSCM_GET_UOPS_API == STD_ON */
#endif /* MCU_SSCM_GET_UOPS_API */

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_SSCM_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* MCU_SSCM_H */

/** @} */
