/**
*   @file    Mcu_IPW_Types.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Exported data outside of the Mcu from IPW.
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


#ifndef MCU_IPW_TYPES_H
#define MCU_IPW_TYPES_H


#ifdef __cplusplus
extern "C"{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_IPW_Types_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, : Repeated include files, Precautions shall be taken in
* order to prevent the contents of a header file being included twice This is not a violation since
* all header files are protected against multiple inclusions
*
* @section Mcu_IPW_Types_h_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory
* section
*
* @section Mcu_IPW_Types_h_REF_3
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and functions
* shall not be reused
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
#include "Mcu_PMC_Types.h"
#include "Mcu_STCU_Types.h"
#if (MCU_SRAMC_SUPPORT == STD_ON)
  #include "Mcu_PRAM_Types.h"
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */
#include "Mcu_FLASH_Types.h"
#include "Mcu_PLLDIG_Types.h"
#include "Mcu_SSCM_Types.h"
#include "Mcu_CMU_Types.h"
#include "Mcu_SIU_Types.h"
#if (MCU_EMIOS_SUPPORT == STD_ON)
#include "Mcu_eMios_Types.h"
#endif

/*==================================================================================================
                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define MCU_IPW_TYPES_VENDOR_ID                       43
#define MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION        4
#define MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION        0
#define MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION     3
#define MCU_IPW_TYPES_SW_MAJOR_VERSION                1
#define MCU_IPW_TYPES_SW_MINOR_VERSION                0
#define MCU_IPW_TYPES_SW_PATCH_VERSION                1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/**
* @brief            The MCU module's implementer shall avoid the integration of incompatible files.
*/

/* Check if current file and Mcu_PMC_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_PMC_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_PMC_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_PMC_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_PMC_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_PMC_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_PMC_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_PMC_Types.h are different"
#endif

/* Check if current file and Mcu_PMC_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_PMC_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_PMC_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_PMC_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_PMC_Types.h are different"
#endif

/* Check if current file and Mcu_CMU_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_CMU_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_CMU_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_CMU_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_CMU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_CMU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_CMU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_CMU_Types.h are different"
#endif

/* Check if current file and Mcu_CMU_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_CMU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_CMU_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_CMU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_CMU_Types.h are different"
#endif

/* Check if current file and Mcu_STCU_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_STCU_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_STCU_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_STCU_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_STCU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_STCU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_STCU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_STCU_Types.h are different"
#endif

/* Check if current file and Mcu_STCU_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_STCU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_STCU_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_STCU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_STCU_Types.h are different"
#endif

#if (MCU_SRAMC_SUPPORT == STD_ON)
/* Check if current file and Mcu_PRAM_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_PRAM_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_PRAM_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_PRAM_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_PRAM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_PRAM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_PRAM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_PRAM_Types.h are different"
#endif

/* Check if current file and Mcu_PRAM_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_PRAM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_PRAM_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_PRAM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_PRAM_Types.h are different"
#endif
#endif

/* Check if current file and Mcu_FLASH_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_FLASH_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_FLASH_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_FLASH_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_FLASH_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_FLASH_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_FLASH_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_FLASH_Types.h are different"
#endif

/* Check if current file and Mcu_FLASH_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_FLASH_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_FLASH_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_FLASH_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_FLASH_Types.h are different"
#endif

/* Check if current file and Mcu_PLLDIG_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_PLLDIG_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_PLLDIG_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_PLLDIG_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_PLLDIG_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_PLLDIG_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_PLLDIG_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_PLLDIG_Types.h are different"
#endif

/* Check if current file and Mcu_PLLDIG_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_PLLDIG_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_PLLDIG_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_PLLDIG_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_PLLDIG_Types.h are different"
#endif

/* Check if current file and Mcu_SSCM_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_SSCM_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_SSCM_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_SSCM_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_SSCM_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_SSCM_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_SSCM_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_SSCM_Types.h are different"
#endif

/* Check if current file and Mcu_SSCM_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_SSCM_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_SSCM_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_SSCM_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_SSCM_Types.h are different"
#endif

/* Check if current file and Mcu_SIU_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_SIU_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_SIU_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_SIU_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_SIU_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_SIU_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_SIU_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_SIU_Types.h are different"
#endif

/* Check if current file and Mcu_SIU_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_SIU_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_SIU_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_SIU_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_SIU_Types.h are different"
#endif

#if (MCU_EMIOS_SUPPORT == STD_ON)
/* Check if current file and Mcu_eMios_Types header file are of the same vendor */
#if (MCU_IPW_TYPES_VENDOR_ID != MCU_EMIOS_TYPES_VENDOR_ID)
    #error "Mcu_IPW_Types.h and Mcu_eMios_Types.h have different vendor ids"
#endif

/* Check if current file and Mcu_eMios_Types header file are of the same Autosar version */
#if ((MCU_IPW_TYPES_AR_RELEASE_MAJOR_VERSION    != MCU_EMIOS_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_MINOR_VERSION    != MCU_EMIOS_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_TYPES_AR_RELEASE_REVISION_VERSION != MCU_EMIOS_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW_Types.h and Mcu_eMios_Types.h are different"
#endif

/* Check if current file and Mcu_eMios_Types header file are of the same Software version */
#if ((MCU_IPW_TYPES_SW_MAJOR_VERSION != MCU_EMIOS_TYPES_SW_MAJOR_VERSION) || \
     (MCU_IPW_TYPES_SW_MINOR_VERSION != MCU_EMIOS_TYPES_SW_MINOR_VERSION) || \
     (MCU_IPW_TYPES_SW_PATCH_VERSION != MCU_EMIOS_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW_Types.h and Mcu_eMios_Types.h are different"
#endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       DEFINES AND MACROS
==================================================================================================*/
#define MCU_IPW_PLL0_UNDER_MCU_CONTROL              ((uint8)0x10U)
#define MCU_IPW_PLL0_NOT_UNDER_MCU_CONTROL          ((uint8)0x00U)
#define MCU_IPW_PLL1_UNDER_MCU_CONTROL              ((uint8)0x20U)
#define MCU_IPW_PLL1_NOT_UNDER_MCU_CONTROL          ((uint8)0x00U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief        Mcu_ClockNotificationType
* @details      Clock failure notification.
*               Enable/disable clock failure interrupt generated by the MCU.
*/
typedef enum
{
    MCU_CLK_NOTIF_DIS = 0x5AU,   /**< @brief Disable clock notification. */
    MCU_CLK_NOTIF_EN = 0xA5U  /**< @brief Enable clock notification. */

} Mcu_ClockNotificationType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief            Mcu driver configuration structure.
* @details          Configuration for SIU reset configuration module.
*                   Configuration for power management and SSCM.
*                   Configuration for FLASH controller.
*                   Used by "Mcu_ConfigType" structure.
*
*/
typedef struct
{
    /**< @brief Configuration for MC_RGM (Reset Generation Module) hardware IP. */
    P2CONST( Mcu_SIU_ResetConfigType, MCU_VAR, MCU_APPL_CONST) SIU_pResetConfig;
    /**< @brief Configuration for MC_PCU/PMU (Power Management Unit) hardware IP, part of PCU. */
    P2CONST( Mcu_PMC_ConfigType, MCU_VAR, MCU_APPL_CONST) PMC_pConfig;
    /**< @brief Configuration for FLASH (Flash Memory) hardware IP. */
    P2CONST( Mcu_FLASH_ConfigType, MCU_VAR, MCU_APPL_CONST) FLASH_pConfig;
    /**< @brief Configuration for SSCM module */
    P2CONST( Mcu_SSCM_ConfigType, MCU_VAR, MCU_APPL_CONST) SSCM_pConfig ;
} Mcu_HwIPsConfigType;


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            Definition of a Clock configuration.
* @details          This configuration is transmitted as parameter to Mcu_Ipw_InitClock() API.
*                   Used by "Mcu_ConfigType" structure.
*
* @note             The structure Mcu_ConfigType shall provide a configurable (enable/ disable)
*                   clock failure notification if the MCU provides an interrupt for such detection.
*
*/
typedef struct
{
    /**< @brief The ID for Clock configuration. */
    VAR( Mcu_ClockType, MCU_VAR) Mcu_ClkConfigId;
    /**< @brief Clock error notification enable configuration. */
    VAR( Mcu_ClockNotificationType, MCU_VAR) Mcu_ClkNotification;
    /**< @brief SIU IP Clock settings. */
    P2CONST( Mcu_SIU_ClockConfigType, MCU_VAR, MCU_APPL_CONST) SIU_pClockConfig;
    /**< @brief PLLDIG IP Clock settings. */
    P2CONST( Mcu_PLLDIG_ConfigType, MCU_VAR, MCU_APPL_CONST) MC_PLLDIG_pClockConfig;
#if (MCU_EMIOS_SUPPORT == STD_ON)
    /**< @brief EMIOS Clock settings. */
    /** @violates @ref Mcu_IPW_Types_h_REF_3 This is not a standard library macro. */
    P2CONST( Mcu_eMios_ConfigType, MCU_VAR, MCU_APPL_CONST) EMIOS_pClockConfig;
#endif
    /**< @brief CMU IP Clock settings. */
    P2CONST( Mcu_CMU_ConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_CMU_pConfig;
#if (MCU_SRAMC_SUPPORT == STD_ON)
    /**< @brief SRAMC IP Clock settings. */
    P2CONST( Mcu_PRAM_ClockConfigType, MCU_VAR, MCU_APPL_CONST) SRAMC_pClockConfig;
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */
    /**< @brief FLASH IP Clock settings. */
    P2CONST( Mcu_FLASH_ClockConfigType, MCU_VAR, MCU_APPL_CONST) FLASH_pClockConfig;
    /**< @brief Clock sources and PLLs under mcu control. */
    VAR( uint8, MCU_VAR) u8ClockSourcesControl;
} Mcu_ClockConfigType;
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* MCU_IPW_TYPES_H */


/** @} */
