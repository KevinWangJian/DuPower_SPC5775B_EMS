/**
*   @file    Adc_Siu.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc SIU source file support for ADC driver.
*   @details This file is the SIU ADC low level driver code.
*
*   @addtogroup ADC_SIU
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : EQADC
*   Dependencies         : none
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
===================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Siu_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include".
* The usage of the MemMap.h file violates this rule, but this mechanism is used to properly
* place into their sections the code and variables.
*
* @section Adc_Siu_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file
* This violation  is not  fixed since  the inclusion  of MemMap.h  is as  per Autosar  requirement
* MEMMAP003.
*
* @section Adc_Siu_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, Casting operation to a pointer.
* This violation is due to the Casting pointers to other types used in macros
* for Reading or writing data from address location of controller register

* @section Adc_Siu_c_REF_4
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Adc_Siu_REF_5
* Violates MISRA 2004 Required Rule 8.10,
* All declarations and definitions of objects or functions at file scope shall
* have internal linkage unless external linkage is required.
* State variables may be used by IPV layer.
*
* @section Adc_Siu_c_REF_6
* Violates MISRA 2004 Advisory Rule 11.3,
* A cast should not be performed between a pointer type and an integral type.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers shall not more than 31 characters
* Violation is needed because of Autosar restrictions for naming File version check macros.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Adc_Siu.h"
#define USER_MODE_REG_PROT_ENABLED      (ADC_USER_MODE_REG_PROT_ENABLED)
#include "SilRegMacros.h"
#include "Adc_Reg_eSys_Siu.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_SIU_VENDOR_ID_C                    43
/** @violates @ref Adc_Siu_c_REF_4 Identifier clash.*/
#define ADC_SIU_AR_RELEASE_MAJOR_VERSION_C     4
/** @violates @ref Adc_Siu_c_REF_4 Identifier clash.*/
#define ADC_SIU_AR_RELEASE_MINOR_VERSION_C     0
/** @violates @ref Adc_Siu_c_REF_4 Identifier clash.*/
#define ADC_SIU_AR_RELEASE_REVISION_VERSION_C  3
#define ADC_SIU_SW_MAJOR_VERSION_C             1
#define ADC_SIU_SW_MINOR_VERSION_C             0
#define ADC_SIU_SW_PATCH_VERSION_C             1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Adc_Siu.h version check start */
#if ((ADC_SIU_AR_RELEASE_MAJOR_VERSION_C != ADC_SIU_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_SIU_AR_RELEASE_MINOR_VERSION_C != ADC_SIU_AR_RELEASE_MINOR_VERSION) || \
     (ADC_SIU_AR_RELEASE_REVISION_VERSION_C != ADC_SIU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Adc_Siu.c and Adc_Siu.h are different"
#endif

#if ((ADC_SIU_SW_MAJOR_VERSION_C != ADC_SIU_SW_MAJOR_VERSION) || \
     (ADC_SIU_SW_MINOR_VERSION_C != ADC_SIU_SW_MINOR_VERSION) || \
     (ADC_SIU_SW_PATCH_VERSION_C != ADC_SIU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Adc_Siu.c and Adc_Siu.h are different"
#endif

#if (ADC_SIU_VENDOR_ID_C != ADC_SIU_VENDOR_ID)
    #error "VENDOR ID for Adc_Siu.c and Adc_Siu.h is different"
#endif
/* Adc_Siu.h version check end */

/* SilRegMacros.h version check start */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if ((ADC_SIU_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
       (ADC_SIU_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
      )
      #error "AUTOSAR Version Numbers of Adc_Siu.c and SilRegMacros.h are different"
  #endif
#endif
/* SilRegMacros.h version check end */

/* Adc_Reg_eSys_Siu.h version check start */
#if ((ADC_SIU_AR_RELEASE_MAJOR_VERSION_C != ADC_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION_REG) || \
     (ADC_SIU_AR_RELEASE_MINOR_VERSION_C != ADC_REGESYS_SIU_AR_RELEASE_MINOR_VERSION_REG) || \
     (ADC_SIU_AR_RELEASE_REVISION_VERSION_C != ADC_REGESYS_SIU_AR_RELEASE_REVISION_VERSION_REG) \
    )
    #error "AUTOSAR Version Numbers of Adc_Siu.c and Adc_Reg_eSys_Siu.h are different"
#endif

#if ((ADC_SIU_SW_MAJOR_VERSION_C != ADC_REGESYS_SIU_SW_MAJOR_VERSION_REG) || \
     (ADC_SIU_SW_MINOR_VERSION_C != ADC_REGESYS_SIU_SW_MINOR_VERSION_REG) ||\
     (ADC_SIU_SW_PATCH_VERSION_C != ADC_REGESYS_SIU_SW_PATCH_VERSION_REG) \
    )
    #error "Software Version Numbers of Adc_Siu.c and Adc_Reg_eSys_Siu.h are different"
#endif

#if (ADC_SIU_VENDOR_ID_C != ADC_REGESYS_SIU_VENDOR_ID_REG)
    #error "VENDOR ID for Adc_Siu.c and Adc_Reg_eSys_Siu.h is different"
#endif
/* Adc_Reg_eSys_Siu.h version check end */

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
#if (STD_ON == ADC_HW_TRIGGER_API)
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Siu_c_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief          This function reset all HW triggers.
* @details        This function reset all HW triggers.
*
* @return         void
* @violates @ref Adc_Siu_REF_5 internal linkage vs external linkage.
*/
FUNC(void, ADC_CODE) Adc_Siu_ResetAllHwTrigger(void)
{
    /* set SIU_ISEL(4-7) default reset value */
    /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
    /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/
    REG_WRITE32(SIU_ISEL4_REG_ADDR32, EQADC_REG32_RESET_VALUE_U32);
    /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
    /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/
    REG_WRITE32(SIU_ISEL5_REG_ADDR32, EQADC_REG32_RESET_VALUE_U32);
    /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
    /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/
    REG_WRITE32(SIU_ISEL6_REG_ADDR32, EQADC_REG32_RESET_VALUE_U32);
    /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
    /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/
    REG_WRITE32(SIU_ISEL7_REG_ADDR32, EQADC_REG32_RESET_VALUE_U32);
}

/**
* @brief          This function enable an HW trigger.
* @details        This function enable an HW trigger.
*
* @param[in]      u16HwResource - Pointer to group configuration
* @param[in]      u8EqadcIdx - eQADCA or eQADCB
* @param[in]      u8Fifo - Fifo number
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Siu_EnableHwTrigger
(
    VAR(uint16, AUTOMATIC) u16HwResource,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8Fifo
)
{
    if (u8EqadcIdx == (uint8)ADC_EQADC_A)
    {
        /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
        /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/
        REG_WRITE8((SIU_ISEL4_REG_ADDR32 + (uint32)(5UL - (uint32)u8Fifo)), (uint8)u16HwResource);
    }
    else
    {
        /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
        /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/
        REG_WRITE8((SIU_ISEL6_REG_ADDR32 + (uint32)(5UL - (uint32)u8Fifo)), (uint8)u16HwResource);
    }
}

/**
* @brief          This function disable an HW trigger.
* @details        This function disable an HW trigger.
*
* @param[in]      u8EqadcIdx - eQADCA or eQADCB
* @param[in]      u8Fifo - Fifo number
*
* @return         void
*
*/
FUNC(void, ADC_CODE) Adc_Siu_DisableHwTrigger
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8Fifo
)
{
    /* Reset the trigger source */
    if (u8EqadcIdx == (uint8)ADC_EQADC_A)
    {
        /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
        /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/       
        REG_WRITE8((SIU_ISEL4_REG_ADDR32 + (uint32)(5UL - (uint32)u8Fifo)), SIU_REG8_RESET_VALUE_U8);
    }
    else
    {
        /** @violates @ref Adc_Siu_c_REF_3 Casting operation to a pointer.*/
        /** @violates @ref Adc_Siu_c_REF_6 A cast should not be performed between a pointer type and an integral type.*/
        REG_WRITE8((SIU_ISEL6_REG_ADDR32 + (uint32)(5UL - (uint32)u8Fifo)), SIU_REG8_RESET_VALUE_U8);
    }
}

#define ADC_STOP_SEC_CODE
/**
 * @violates @ref Adc_Siu_c_REF_1 Only preprocessor statements and comments before "#include"
 * @violates @ref Adc_Siu_c_REF_2 Repeated include file MemMap.h
 */
#include "MemMap.h"
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */

#ifdef __cplusplus
}
#endif

/** @} */
