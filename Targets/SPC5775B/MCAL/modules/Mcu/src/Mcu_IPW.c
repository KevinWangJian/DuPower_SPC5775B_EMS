/**
*   @file    Mcu_IPW.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Middle layer implementation.
*   @details Layer that implements the wrapper for routing data from/to external interface
*            to IP layer.
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


#ifdef __cplusplus
extern "C"
{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_IPW_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation
* since all header files are protected against multiple inclusions
*
* @section Mcu_IPW_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set the current memory
* section
*
* @section Mcu_IPW_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Mcu_IPW_c_REF_5
* Violates MISRA 2004 Advisory Rule 11.4, Conversion from object to pointer.
* A cast should not be performed between a pointer to
* object type and a different pointer to object type
*
* @section Mcu_IPW_c_REF_6
* Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are only
* accessed from within a single function
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/* Header file with prototype functions defines in this layer. */
#include "Mcu_IPW.h"
#include "Mcu_IPW_Irq.h"

/* Header files that are called from IPW layer. */
#include "Mcu_PMC.h"
#include "Mcu_STCU.h"
#include "Mcu_SSCM.h"
#if (MCU_SRAMC_SUPPORT == STD_ON)
    #include "Mcu_PRAM.h"
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */
#include "Mcu_FLASH.h"
#include "Mcu_PLLDIG.h"
#include "Mcu_SIU.h"
#include "Mcu_CMU.h"
#include "Mcu_eMios.h"

/**
* @brief    Detected development errors shall be reported to the Det_ReportError service of the
*           Development Error Tracer (DET) if the pre-processor switch McuDevErrorDetect is set
*           The detection of development errors is configurable (ON / OFF) at precompile time.
*           The switch McuDevErrorDetect (see chapter 10) shall activate or deactivate the detection
*           of all development errors.
*           Det_ReportError - Service to report development errors.
*
*/
#if (MCU_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define MCU_IPW_VENDOR_ID_C                     43
/** @violates @ref Mcu_IPW_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_IPW_AR_RELEASE_MAJOR_VERSION_C      4
/** @violates @ref Mcu_IPW_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_IPW_AR_RELEASE_MINOR_VERSION_C      0
/** @violates @ref Mcu_IPW_c_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define MCU_IPW_AR_RELEASE_REVISION_VERSION_C   3
#define MCU_IPW_SW_MAJOR_VERSION_C              1
#define MCU_IPW_SW_MINOR_VERSION_C              0
#define MCU_IPW_SW_PATCH_VERSION_C              1


/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Mcu_IPW header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_IPW_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_IPW.h have different vendor ids"
#endif
/* Check if current file and Mcu_IPW header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_IPW_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_IPW.h are different"
#endif
/* Check if current file and Mcu_IPW header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_IPW_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_IPW_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_IPW_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_IPW.h are different"
#endif

/* Check if current file and Mcu_IPW_Irq header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_IPW_IRQ_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_IPW_Irq.h have different vendor ids"
#endif
/* Check if current file and Mcu_IPW_Irq header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_IPW_IRQ_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_IPW_IRQ_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_IPW_IRQ_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_IPW_Irq.h are different"
#endif
/* Check if current file and Mcu_IPW_Irq header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_IPW_IRQ_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_IPW_IRQ_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_IPW_IRQ_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_IPW_Irq.h are different"
#endif

/* Check if current file and Mcu_PMC header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_PMC_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_PMC.h have different vendor ids"
#endif
/* Check if current file and Mcu_PMC header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_PMC_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_PMC_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_PMC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_PMC.h are different"
#endif
/* Check if current file and Mcu_PMC header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_PMC_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_PMC_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_PMC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_PMC.h are different"
#endif

/* Check if current file and Mcu_STCU header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_STCU_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_STCU.h have different vendor ids"
#endif
/* Check if current file and Mcu_STCU header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_STCU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_STCU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_STCU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_STCU.h are different"
#endif
/* Check if current file and Mcu_STCU header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_STCU_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_STCU_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_STCU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_STCU.h are different"
#endif

/* Check if current file and Mcu_SSCM header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_SSCM_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_SSCM.h have different vendor ids"
#endif
/* Check if current file and Mcu_SSCM header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_SSCM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_SSCM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_SSCM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_SSCM.h are different"
#endif
/* Check if current file and Mcu_SSCM header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_SSCM_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_SSCM_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_SSCM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_SSCM.h are different"
#endif

#if (MCU_SRAMC_SUPPORT == STD_ON)
/* Check if current file and Mcu_PRAM header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_PRAM_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_PRAM.h have different vendor ids"
#endif
/* Check if current file and Mcu_PRAM header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_PRAM_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_PRAM_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_PRAM_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_PRAM.h are different"
#endif
/* Check if current file and Mcu_PRAM header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_PRAM_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_PRAM_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_PRAM_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_PRAM.h are different"
#endif
#endif

/* Check if current file and Mcu_FLASH header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_FLASH_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_FLASH.h have different vendor ids"
#endif
/* Check if current file and Mcu_FLASH header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_FLASH_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_FLASH_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_FLASH_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_FLASH.h are different"
#endif
/* Check if current file and Mcu_FLASH header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_FLASH_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_FLASH_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_FLASH_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_FLASH.h are different"
#endif

/* Check if current file and Mcu_PLLDIG header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_PLLDIG_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_PLLDIG.h have different vendor ids"
#endif
/* Check if current file and Mcu_PLLDIG header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_PLLDIG_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_PLLDIG_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_PLLDIG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_PLLDIG.h are different"
#endif
/* Check if current file and Mcu_PLLDIG header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_PLLDIG_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_PLLDIG_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_PLLDIG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_PLLDIG.h are different"
#endif

/* Check if current file and Mcu_SIU header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_SIU_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_SIU.h have different vendor ids"
#endif
/* Check if current file and Mcu_SIU header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_SIU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_SIU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_SIU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_SIU.h are different"
#endif
/* Check if current file and Mcu_SIU header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_SIU_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_SIU_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_SIU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_SIU.h are different"
#endif

/* Check if current file and Mcu_CMU header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_CMU_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_CMU.h have different vendor ids"
#endif
/* Check if current file and Mcu_CMU header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_CMU_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_CMU_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_CMU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_CMU.h are different"
#endif
/* Check if current file and Mcu_CMU header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_CMU_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_CMU_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_CMU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_CMU.h are different"
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_IPW_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_IPW.c and Det.h are different"
    #endif
#endif
#endif

/* Check if current file and Mcu_eMios header file are of the same vendor */
#if (MCU_IPW_VENDOR_ID_C != MCU_EMIOS_H_VENDOR_ID)
    #error "Mcu_IPW.c and Mcu_eMios.h have different vendor ids"
#endif

/* Check if current file and Mcu_eMios header file are of the same Autosar version */
#if ((MCU_IPW_AR_RELEASE_MAJOR_VERSION_C    != MCU_EMIOS_H_AR_RELEASE_MAJOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_MINOR_VERSION_C    != MCU_EMIOS_H_AR_RELEASE_MINOR_VERSION) || \
     (MCU_IPW_AR_RELEASE_REVISION_VERSION_C != MCU_EMIOS_H_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Mcu_IPW.c and Mcu_eMios.h are different"
#endif

/* Check if current file and Mcu_eMios header file are of the same Software version */
#if ((MCU_IPW_SW_MAJOR_VERSION_C != MCU_EMIOS_H_SW_MAJOR_VERSION) || \
     (MCU_IPW_SW_MINOR_VERSION_C != MCU_EMIOS_H_SW_MINOR_VERSION) || \
     (MCU_IPW_SW_PATCH_VERSION_C != MCU_EMIOS_H_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_IPW.c and Mcu_eMios.h are different"
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
/* Mcu clock configuration structure used at a moment by the MCU driver.
   When the Mcu_InitClock() API is called this pointer will be different from NULL_PTR - used as a
    check trigger by Mcu_DistributePllClock() API.
*/
#if (MCU_INIT_CLOCK == STD_ON)
#define MCU_START_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"
/** @violates @ref Mcu_IPW_c_REF_6 MISRA 2004 Advisory Rule 8.7 */
static P2CONST( Mcu_ClockConfigType, MCU_VAR, MCU_APPL_CONST) Mcu_pClockConfig = NULL_PTR;

#define MCU_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


/**
* @brief            This function initializes the MCU module.
* @details          The function initializes the CGM, ME, RGM, PCU modules, specific parameters for
*                   DMAMUX and DMAv2 modules and global parameters from FLASH module.
*                   Called by:
*                       - Mcu_Init() from HLD.
*
* @param[in]        Mcu_pHwIPsConfigPtr   Pointer to IPW configuration structure.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_Ipw_Init( P2CONST( Mcu_HwIPsConfigType, AUTOMATIC, MCU_APPL_CONST) Mcu_pHwIPsConfigPtr )
{


    /* init the SSCM module */
    Mcu_SSCM_Init(Mcu_pHwIPsConfigPtr->SSCM_pConfig);

    /* Init MCU MC_RGM part of the registers: MC_RGM_FERD, MC_RGM_FEAR, MC_RGM_FESS, MC_RGM_FBRE,
    clear FES & DES status registers. */
    Mcu_SIU_ResetInit( Mcu_pHwIPsConfigPtr->SIU_pResetConfig );

    /* Configure the Power Management Unit. */
    Mcu_PMC_PowerInit( Mcu_pHwIPsConfigPtr->PMC_pConfig);

#ifdef MCU_PREPARE_MEMORY_CONFIG
    /* The entry point of the flash controller configuration. */
    MCU_PREPARE_MEMORY_CONFIG(MCU_MEMORY_CONFIG_ENTRY_POINT);
#endif    
    
    /* Flash initialization. */
    Call_Mcu_FLASH_Init( Mcu_pHwIPsConfigPtr->FLASH_pConfig);
    
#ifdef MCU_PREPARE_MEMORY_CONFIG
    /* The exit point of the flash controller configuration. */
    MCU_PREPARE_MEMORY_CONFIG(MCU_MEMORY_CONFIG_EXIT_POINT);
#endif    
}


#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            This function initializes the clock structure.
* @details          This function intializes the clock structure by configuring the SIU module.
*                   Called by:
*                       - Mcu_InitClock() from HLD.
*
* @param[in]        Mcu_pClockConfigPtr   Pointer to clock configuration structure
*                   (member of 'Mcu_ConfigType' struct).
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_Ipw_InitClock( P2CONST( Mcu_ClockConfigType, AUTOMATIC, MCU_APPL_CONST) Mcu_pClockConfigPtr)
{
#if (MCU_EMIOS_SUPPORT == STD_ON)
    VAR (uint8, AUTOMATIC)   u8Index = 0U;
#endif

    /* Clear all the settings for CMU0/1/2. */
    /* In case one clock configuration has the CMU disabled, then need to make the transition to
    reset state of CMU modules. */
    if (NULL_PTR != Mcu_pClockConfig)
    {
        if (MCU_CLK_NOTIF_EN == Mcu_pClockConfig->Mcu_ClkNotification)
        {
            Call_Mcu_CMU_DeInit();
        }
    }
    
    Mcu_pClockConfig = Mcu_pClockConfigPtr;
    
    /* set system clock to IRC */
    if(0xFFFFFFFFU != Mcu_pClockConfigPtr->SIU_pClockConfig->u32SystemClockConfig)
    {
        Mcu_SIU_SystemClockConfig(Mcu_pClockConfigPtr->SIU_pClockConfig->u32SystemClockConfig & ~SIU_SYSDIV_SYSCLKSEL_MASK32);
    }
    
    /* set up the clock distribution tree */
    Mcu_SIU_ProgClockSwitchConfig( Mcu_pClockConfigPtr->SIU_pClockConfig ) ;

    /* aux clock tree */
    if( NULL_PTR != Mcu_pClockConfigPtr->SIU_pClockConfig->apAuxClockConfig )
    {
        Mcu_SIU_AuxClockConfig( Mcu_pClockConfigPtr->SIU_pClockConfig );
    }

    /* configure PLLDIG clock generators */
    Mcu_PLLDIG_PllConfig( Mcu_pClockConfigPtr->MC_PLLDIG_pClockConfig );

#ifdef MCU_PREPARE_MEMORY_CONFIG
    /* The entry point of the flash and RAM controllers configuration. */
    MCU_PREPARE_MEMORY_CONFIG(MCU_MEMORY_CONFIG_ENTRY_POINT);
#endif
    
#if (STD_OFF == MCU_ENABLE_USER_MODE_SUPPORT)
    /* Every Clock configuration need to adjust the wait-states for RAM and Flash. */
    /* Set the wait-states for Flash. */
    Call_Mcu_FLASH_SetWS( Mcu_pClockConfigPtr->FLASH_pClockConfig);
#endif

#if (MCU_SRAMC_SUPPORT == STD_ON)
    /* Set the wait-states for Ram (PRCR1 register of RAM controller). */
    Call_Mcu_PRAM_SetRamWS( Mcu_pClockConfigPtr->SRAMC_pClockConfig);
#endif /* (MCU_SRAMC_SUPPORT == STD_ON) */

#ifdef MCU_PREPARE_MEMORY_CONFIG
    /* The exit point of the flash and RAM controllers configuration. */
    MCU_PREPARE_MEMORY_CONFIG(MCU_MEMORY_CONFIG_EXIT_POINT);
#endif
    
    /* if system clock is IRC or XOSC configure system clock else the system clock will be configured in Mcu_DistributePllClock */
    if ( (SIU_SYSDIV_SYSCLKSEL_SOURCE_IRC_U32 == (Mcu_pClockConfigPtr->SIU_pClockConfig->u32SystemClockConfig & SIU_SYSDIV_SYSCLKSEL_MASK32)) ||
         (SIU_SYSDIV_SYSCLKSEL_SOURCE_XOSC_U32 == (Mcu_pClockConfigPtr->SIU_pClockConfig->u32SystemClockConfig & SIU_SYSDIV_SYSCLKSEL_MASK32))
       )
    {
        /* if system clock tree is under MCU control */
        if(0xFFFFFFFFU != Mcu_pClockConfigPtr->SIU_pClockConfig->u32SystemClockConfig)
        {
            /* configure the SYSDIV register */
            Mcu_SIU_SystemClockConfig(Mcu_pClockConfigPtr->SIU_pClockConfig->u32SystemClockConfig);
        }
        
#if (MCU_EMIOS_SUPPORT == STD_ON)
        /* configure for eMios modules */
        for (u8Index = 0U; u8Index < MCU_EMIOS_NB_MODULES; u8Index++)
        {
            Mcu_eMios_Init(u8Index, Mcu_pClockConfigPtr->EMIOS_pClockConfig);
        }
#endif
        
        /* Set the Clock Monitoring Units ( CMU0 .. n ). */
        if ( MCU_CLK_NOTIF_EN == Mcu_pClockConfigPtr->Mcu_ClkNotification)
        {
            Call_Mcu_CMU_Init( Mcu_pClockConfigPtr->Mcu_CMU_pConfig);
        }
    }
}
#endif /* (MCU_INIT_CLOCK == STD_ON) */


#if (MCU_INIT_CLOCK == STD_ON)
#if (MCU_NO_PLL == STD_OFF)
/**
* @brief              This function activates the main PLL as the system clock source.
* @details            This function sets the PLL as the system clock and also enables monitoring.
*                     Called by:
*                       - Mcu_DistributePllClock() from HLD.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_Ipw_DistributePllClock( VAR( void, AUTOMATIC) )
{
#if (MCU_EMIOS_SUPPORT == STD_ON)
    VAR (uint8, AUTOMATIC)   u8Index = 0U;
#endif

    if ( NULL_PTR != Mcu_pClockConfig)
    {
        /* if system clock tree is under MCU control */
        if(0xFFFFFFFFU != Mcu_pClockConfig->SIU_pClockConfig->u32SystemClockConfig)
        {
            /* configure the SYSDIV register */
            Mcu_SIU_SystemClockConfig(Mcu_pClockConfig->SIU_pClockConfig->u32SystemClockConfig);
        }
        
    #if (MCU_EMIOS_SUPPORT == STD_ON)
        /* configure for eMios modules */
        for (u8Index = 0U; u8Index < MCU_EMIOS_NB_MODULES; u8Index++)
        {
            Mcu_eMios_Init(u8Index, Mcu_pClockConfig->EMIOS_pClockConfig);
        }
    #endif
        
        /* Set the Clock Monitoring Units ( CMU0 .. n ). */
        if ( MCU_CLK_NOTIF_EN == Mcu_pClockConfig->Mcu_ClkNotification)
        {
            Mcu_CMU_Init( Mcu_pClockConfig->Mcu_CMU_pConfig);
        }
    }
}
#endif /* (MCU_NO_PLL == STD_OFF) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */

#if (MCU_NO_PLL == STD_OFF)
/**
* @brief            This function returns the lock status of the PLL.
* @details          The user takes care that the PLL is locked by executing Mcu_GetPllStatus.
*                   If the MCU_NO_PLL is TRUE the MCU_GetPllStatus has to return
*                   MCU_PLL_STATUS_UNDEFINED.
*                   Called by:
*                       - Mcu_GetPllStatus() from HLD.
*
* @return           Provides the lock status of the PLL.
* @retval           MCU_PLL_STATUS_UNDEFINED   PLL Status is unknown.
* @retval           MCU_PLL_LOCKED   PLL is locked.
* @retval           MCU_PLL_UNLOCKED    PLL is unlocked.
*
*/
FUNC( Mcu_PllStatusType, MCU_CODE) Mcu_Ipw_GetPllStatus( VAR( void, AUTOMATIC))
{
    /* Pll status variable. */
    VAR( Mcu_PllStatusType, AUTOMATIC)   ePllStatus = MCU_PLL_STATUS_UNDEFINED;
    VAR( Mcu_PLLDIG_PllStatusType, AUTOMATIC) ePllDigStatus ;

    /* get the status from each peripheral */
    ePllDigStatus = Mcu_PLLDIG_GetPLLStatus();

    /* if a pll is unlocked return MCU_PLL_UNLOCKED */
    if ( MCU_PLLDIG_PLL_LOCKED == ePllDigStatus )
    {
        ePllStatus = MCU_PLL_LOCKED ;
    }
    else
    {
        ePllStatus = MCU_PLL_UNLOCKED ;
    }

    /* Return the PLL status. */
    return (Mcu_PllStatusType)ePllStatus;
}
#endif /* (MCU_NO_PLL == STD_OFF) */

/**
* @brief            This function initializes the mode structure.
* @details          This function intializes the mode structure by configuring the SIU module.
*                   Called by:
*                       - Mcu_SetMode() from HLD.
*
* @param[in]        Mcu_pModeConfigPtr   Pointer to mode configuration structure.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_Ipw_SetMode(  P2CONST( Mcu_ModeConfigType, AUTOMATIC, MCU_APPL_CONST) Mcu_pModeConfigPtr)
{
    /* Request new mode transition to MC_ME. */
    Mcu_SIU_ModeConfig( Mcu_pModeConfigPtr);
}


#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller.
*                   Called by:
*                       - Mcu_PerformReset() from HLD.
*
* @param[in]        Mcu_pHwIPsConfigPtr  Pointer to LLD configuration structure (member of
*                   'Mcu_ConfigType' struct).
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_Ipw_PerformReset( P2CONST( Mcu_HwIPsConfigType, AUTOMATIC, MCU_APPL_CONST) Mcu_pHwIPsConfigPtr )
{
    /* Performs a microcontroller reset. */
    Mcu_SIU_PerformReset( Mcu_pHwIPsConfigPtr->SIU_pResetConfig );
}
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */



/**
* @brief            This function returns the reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_GetResetReason() from HLD.
*
* @param[in]        None
*
* @return           void
*
*/
FUNC( Mcu_ResetType, MCU_CODE) Mcu_Ipw_GetResetReason( VAR( void, AUTOMATIC))
{
    VAR( Mcu_ResetType, AUTOMATIC)   eResetReason = MCU_RESET_UNDEFINED;

    eResetReason = Mcu_SIU_GetResetReason();
    return (Mcu_ResetType) eResetReason;
}


/**
* @brief            This function returns the reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_GetResetReason() from HLD.
*
* @param[in]        None
*
* @return           void
*
*/
FUNC( Mcu_RawResetType, MCU_CODE) Mcu_Ipw_GetResetRawValue( VAR( void, AUTOMATIC))
{
    VAR( Mcu_RawResetType, AUTOMATIC) ResetReason;

    ResetReason = Mcu_SIU_GetResetRawValue();
    return (Mcu_RawResetType) ResetReason;
}


#if (MCU_GET_RAM_STATE_API == STD_ON)
FUNC (Mcu_RamStateType, MCU_CODE) Mcu_Ipw_GetRamState( VAR( void, AUTOMATIC))
{
    VAR( Mcu_RamStateType, AUTOMATIC) eRamState;

    eRamState = Mcu_STCU_GetRamState();
    return (Mcu_RamStateType) eRamState;
}
#endif /* (MCU_GET_RAM_STATE_API == STD_ON) */


#if (MCU_GET_PERIPH_STATE_API == STD_ON)
FUNC( Std_ReturnType, MCU_CODE) Mcu_Ipw_GetPeripheralState ( VAR( Mcu_PeripheralIdType, AUTOMATIC) Mcu_PeriphId)
{
    /* nothing to do on this platform */
}
#endif /* (MCU_GET_PERIPH_STATE_API == STD_ON) */


#if (MCU_GET_SYSTEM_STATE_API == STD_ON)
FUNC( uint32, MCU_CODE) Mcu_Ipw_GetSystemState ( VAR( void, AUTOMATIC))
{
    /* nothing to do on this platform */
}
#endif /* (MCU_GET_SYSTEM_STATE_API == STD_ON) */


#if (MCU_POWERMODE_STATE_API == STD_ON)
FUNC( Mcu_PowerModeStateType, MCU_CODE) Mcu_Ipw_GetPowerModeState( VAR( void, AUTOMATIC))
{
    /* nothing to do on this platform */
}
#endif /*(MCU_POWERMODE_STATE_API == STD_ON)*/


#if (MCU_GET_POWER_DOMAIN_API == STD_ON)
FUNC( Std_ReturnType, MCU_CODE) Mcu_Ipw_GetPowerDomainState( VAR( void, AUTOMATIC))
{
    /* nothing to do on this platform */
}
#endif /*(MCU_GET_POWER_DOMAIN_API == STD_ON)*/


#if (MCU_GET_MEM_CONFIG_API == STD_ON)
FUNC( Mcu_SSCM_MemConfigType, MCU_CODE ) Mcu_Ipw_SscmGetMemConfig( VAR( void, AUTOMATIC) )
{
    /* nothing to do on this platform */
}
#endif /* (MCU_GET_MEM_CONFIG_API == STD_ON) */

#if (MCU_SSCM_GET_STATUS_API == STD_ON)
FUNC( Mcu_SSCM_StatusType, MCU_CODE ) Mcu_Ipw_SscmGetStatus( VAR( void, AUTOMATIC) )
{
    VAR( Mcu_SSCM_StatusType, AUTOMATIC)   Status ;

    Status = Mcu_SSCM_GetStatus();
    return (Mcu_SSCM_StatusType) Status;
}
#endif /* (MCU_SSCM_GET_STATUS_API == STD_ON) */


#if (MCU_GET_MIDR_API == STD_ON)
FUNC( void, MCU_CODE) Mcu_Ipw_GetMidrStructure( P2VAR( Mcu_MidrReturnType, AUTOMATIC, MCU_APPL_DATA) pMidr)
{
    /* just call low level API */
    Mcu_SIU_GetMidrStructure( pMidr );
}
#endif /*(MCU_GET_MIDR_API == STD_ON)*/


#ifdef MCU_DISABLE_CMU_API
#if (MCU_DISABLE_CMU_API == STD_ON)
FUNC( void, MCU_CODE ) Mcu_Ipw_DisableCmu(VAR(uint8, AUTOMATIC) u8IndexCmu)
{
    Call_Mcu_CMU_Disable_CMU(u8IndexCmu);
}
#endif
#endif

#if (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON)
FUNC( void, MCU_CODE ) Mcu_IPW_EmiosConfigureGpren(VAR (uint8, AUTOMATIC) u8Module, VAR (uint8, AUTOMATIC) u8Value)
{
    Mcu_eMios_ConfigureGpren(u8Module, u8Value);
}
#endif /* (MCU_EMIOS_CONFIGURE_GPREN_API == STD_ON) */


#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_IPW_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_IPW_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

/** @} */

