/**
*   @file    Mcu_SIU.h
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


#ifndef MCU_SIU_H
#define MCU_SIU_H


#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_SIU_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
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
/** @violates @ref Mcu_SIU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_SIU_Types.h"
/** @violates @ref Mcu_SIU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "Mcu_EnvCfg.h"


/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_SIU_VENDOR_ID                        43
#define MCU_SIU_AR_RELEASE_MAJOR_VERSION         4
#define MCU_SIU_AR_RELEASE_MINOR_VERSION         0
#define MCU_SIU_AR_RELEASE_REVISION_VERSION      3
#define MCU_SIU_SW_MAJOR_VERSION                 1
#define MCU_SIU_SW_MINOR_VERSION                 0
#define MCU_SIU_SW_PATCH_VERSION                 1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and SIU header file are from the same vendor */
#if (MCU_SIU_VENDOR_ID != MCU_SIU_TYPES_VENDOR_ID)
    #error "Mcu_SIU.h and Mcu_SIU_Types.h have different vendor ids"
#endif
/* Check if source file and SIU header file are of the same Autosar version */
#if ((MCU_SIU_AR_RELEASE_MAJOR_VERSION != MCU_SIU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_SIU_AR_RELEASE_MINOR_VERSION != MCU_SIU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_SIU_AR_RELEASE_REVISION_VERSION != MCU_SIU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_SIU.h and Mcu_SIU_Types.h are different"
#endif
/* Check if source file and SIU header file are of the same Software version */
#if ((MCU_SIU_SW_MAJOR_VERSION != MCU_SIU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_SIU_SW_MINOR_VERSION != MCU_SIU_TYPES_SW_MINOR_VERSION) || \
     (MCU_SIU_SW_PATCH_VERSION != MCU_SIU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SIU.h and Mcu_SIU_Types.h are different"
#endif

/* Check if source file and SIU header file are from the same vendor */
#if (MCU_SIU_VENDOR_ID != MCU_SCFG_VENDOR_ID)
    #error "Mcu_SIU.h and Mcu_EnvCfg.h have different vendor ids"
#endif
/* Check if source file and SIU header file are of the same Autosar version */
#if ((MCU_SIU_AR_RELEASE_MAJOR_VERSION != MCU_SCFG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_SIU_AR_RELEASE_MINOR_VERSION != MCU_SCFG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_SIU_AR_RELEASE_REVISION_VERSION != MCU_SCFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_SIU.h and Mcu_EnvCfg.h are different"
#endif
/* Check if source file and SIU header file are of the same Software version */
#if ((MCU_SIU_SW_MAJOR_VERSION != MCU_SCFG_SW_MAJOR_VERSION) || \
     (MCU_SIU_SW_MINOR_VERSION != MCU_SCFG_SW_MINOR_VERSION) || \
     (MCU_SIU_SW_PATCH_VERSION != MCU_SCFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SIU.h and Mcu_EnvCfg.h are different"
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
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_SIU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "MemMap.h"

#if (MCU_GET_MIDR_API == STD_ON)
FUNC( void, MCU_CODE) Mcu_SIU_GetMidrStructure(P2VAR( Mcu_MidrReturnType, AUTOMATIC, MCU_APPL_DATA) pMidr);
#endif /* (MCU_GET_MIDR_API == STD_ON) */

#if (MCU_INIT_CLOCK == STD_ON)
FUNC( void, MCU_CODE) Mcu_SIU_SystemClockConfig(VAR( uint32, AUTOMATIC) u32SystemClockConfig);
#if (IPV_SIU == IPV_SIU_00_02_09_00)
FUNC( void, MCU_CODE) Mcu_SIU_ExternalClockConfig(VAR( uint32, AUTOMATIC) u32ExternalClockConfig);
#else
FUNC( void, MCU_CODE) Mcu_SIU_ProgClockSwitchConfig(P2CONST( Mcu_SIU_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) pClockConfigPtr);
FUNC( void, MCU_CODE) Mcu_SIU_AuxClockConfig(P2CONST( Mcu_SIU_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) pClockConfigPtr);
#endif
#endif /* (MCU_INIT_CLOCK == STD_ON) */

FUNC( void, MCU_CODE) Mcu_SIU_ResetInit(P2CONST( Mcu_SIU_ResetConfigType, AUTOMATIC, MCU_APPL_DATA) pConfigPtr);
FUNC( Mcu_ResetType, MCU_CODE) Mcu_SIU_GetResetReason( VAR( void, AUTOMATIC));
FUNC( Mcu_RawResetType, MCU_CODE) Mcu_SIU_GetResetRawValue( VAR( void, AUTOMATIC));

#if (MCU_PERFORM_RESET_API == STD_ON)
FUNC( void, MCU_CODE) Mcu_SIU_PerformReset(P2CONST( Mcu_SIU_ResetConfigType, AUTOMATIC, MCU_APPL_DATA) pConfigPtr);
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

FUNC( void, MCU_CODE) Mcu_SIU_ModeConfig(P2CONST( Mcu_ModeConfigType, AUTOMATIC, MCU_APPL_DATA) pModeConfigPtr);

#if (IPV_SIU == IPV_SIU_00_02_09_00)
#if ((MCU_GET_PERIPH_STATE_API == STD_ON) || (defined MCU_GET_INTERNAL_STATE))
FUNC(Std_ReturnType, MCU_CODE) Mcu_SIU_GetPeripheralState(VAR(Mcu_PeripheralId, AUTOMATIC) Mcu_PeriphId);
#endif /* ((MCU_GET_PERIPH_STATE_API == STD_ON) || (defined MCU_GET_INTERNAL_STATE)) */
#endif

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_SIU_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif /* MCU_SIU_H */

/** @} */
