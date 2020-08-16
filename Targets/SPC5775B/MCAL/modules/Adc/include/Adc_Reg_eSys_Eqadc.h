/**
*   @file    Adc_Reg_eSys_Eqadc.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - module register and macro definitions.
*   @details Adc module registers, and macro definitions used to manipulate the module registers.
*
*   @addtogroup ADC
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
==================================================================================================*/

#ifndef ADC_REG_ESYS_EQADC_H
#define ADC_REG_ESYS_EQADC_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Reg_eSys_Eqadc_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7,
* A function shall be used in preference to a function-like macro.
* Middle layer between AUTOSAR and hardware needs a way to map HLD functions to LLD functions.
*
* @section Adc_Reg_eSys_Eqadc_h_REF_2
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and
* functions shall not be reused. Symbols defined are not library macros or objects.
*
* @section Adc_Reg_eSys_Eqadc_h_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 
* 31 character significance and case sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Reg_eSys_Eqadc_h_REF_4
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
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
#include "Reg_eSys.h"
#include "Adc_Cfg.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_REG                      43
#define ADC_AR_RELEASE_MAJOR_VERSION_REG       4
#define ADC_AR_RELEASE_MINOR_VERSION_REG       0
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_3 Identifier clash */
#define ADC_AR_RELEASE_REVISION_VERSION_REG    3
#define ADC_SW_MAJOR_VERSION_REG               1
#define ADC_SW_MINOR_VERSION_REG               0
#define ADC_SW_PATCH_VERSION_REG               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if source file and Reg_eSys.h are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_REG != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_AR_RELEASE_MINOR_VERSION_REG != REG_ESYS_AR_RELEASE_MINOR_VERSION) \
    )
#error "AutoSar Version Numbers of Adc_Reg_eSys_Eqadc.h and Reg_eSys.h are different"
#endif
#endif

/* Check if source file and ADC configuration header file are of the same vendor */
#if (ADC_VENDOR_ID_REG != ADC_VENDOR_ID_CFG)
#error "Adc_Reg_eSys_Eqadc.h and Adc_Cfg.h have different vendor ids"
#endif

/* Check if source file and ADC configuration header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_REG != ADC_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (ADC_AR_RELEASE_MINOR_VERSION_REG != ADC_AR_RELEASE_MINOR_VERSION_CFG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_REG != ADC_AR_RELEASE_REVISION_VERSION_CFG) \
    )
#error "AutoSar Version Numbers of Adc_Reg_eSys_Eqadc.h and Adc_Cfg.h are different"
#endif

/* Check if source file and ADC configuration header file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION_REG != ADC_SW_MAJOR_VERSION_CFG) || \
     (ADC_SW_MINOR_VERSION_REG != ADC_SW_MINOR_VERSION_CFG) || \
     (ADC_SW_PATCH_VERSION_REG != ADC_SW_PATCH_VERSION_CFG) \
    )
#error "Software Version Numbers of Adc_Reg_eSys_Eqadc.h and Adc_Cfg.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ADC_START_SEC_CONST_32
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_4 Repeated include file MemMap.h */
#include "MemMap.h"
/**
* @brief base address array for EQADC
*
* @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
*/
extern CONST(uint32, ADC_CONST) EQADC_BASE_ADDR[ADC_EQADC_MAX_U8];

#define ADC_STOP_SEC_CONST_32
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_4 Repeated include file MemMap.h */
#include "MemMap.h"

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief          EQADC Base address definition.
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_ADDR32(Eqadc)                     (EQADC_BASE_ADDR[(Eqadc)])

/**
* @brief          EQADC Module Configuration Register.
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_MCR_REG_ADDR32(Eqadc)             (EQADC_ADDR32(Eqadc) + 0x0000UL)

/**
* @brief          EQADC Test Register.
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_TST_REG_ADDR32(Eqadc)             (EQADC_ADDR32(Eqadc) + 0x0004UL)

/**
* @brief          EQADC External Trigger Digital Filter Register
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_ETDFR_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x000CUL)

/**
* @brief          EQADC CFIFO Push Register (0-5)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFPR_REG_ADDR32(Eqadc, Fifo)      (EQADC_ADDR32(Eqadc) + 0x0010UL + ((Fifo) << 2U))

/**
* @brief          EQADC Result FIFO Pop Register (0-5)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_RFPR_REG_ADDR32(Eqadc, Fifo)      (EQADC_ADDR32(Eqadc) + 0x0030UL + ((Fifo) << 2U))

/**
* @brief          EQADC CFIFO Control Register
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFCR_REG_ADDR16(Eqadc, Fifo)      (EQADC_ADDR32(Eqadc) + 0x0050UL + ((Fifo) << 1U))
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFCR0_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x0050UL)
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFCR1_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x0054UL)
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFCR2_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x0058UL)

/**
* @brief          EQADC Interrupt and DMA Control Register
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_IDCR_REG_ADDR16(Eqadc, Fifo)           (EQADC_ADDR32(Eqadc) + 0x0060UL + ((Fifo) << 1U))
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_IDCR0_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x0060UL)
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_IDCR1_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x0064UL)
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_IDCR2_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x0068UL)

/**
* @brief          EQADC FIFO and Interrupt Status Register (0-5)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_FISR_REG_ADDR32(Eqadc, Fifo)      (EQADC_ADDR32(Eqadc) + 0x0070UL + ((Fifo) << 2U))

/**
* @brief            EQADC CFIFO Transfer Counter Register (0-2)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFTCR_REG_ADDR16(Eqadc, Fifo)     (EQADC_ADDR32(Eqadc) + 0x0090UL + ((Fifo) << 1U))

/**
* @brief          EQADC CFIFO Status Snapshot Register (0-1)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFSSR_REG_ADDR32(Eqadc, Fifo)     (EQADC_ADDR32(Eqadc) + 0x00A0UL + ((Fifo) << 2U))

/**
* @brief          EQADC CFIFO Status Register
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CFSR_REG_ADDR32(Eqadc)           (EQADC_ADDR32(Eqadc) + 0x00ACUL)

/**
* @brief EQADC STAC Client Configuration Register
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_REDLCCR_REG_ADDR32(Eqadc)        (EQADC_ADDR32(Eqadc) + 0x00D0UL)

/**
* @brief          EQADC CFIFO0 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CF0R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0100UL + ((Index) << 2U)

/**
* @brief          EQADC CFIFO0 Extension Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CF0ER_REG_ADDR32(Eqadc, Index)   (EQADC_ADDR32(Eqadc) + 0x0110UL + ((Index) << 2U)

/**
* @brief          EQADC CFIFO1 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CF1R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0140UL + ((Index) << 2U)

/**
* @brief          EQADC CFIFO2 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CF2R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0180UL + ((Index) << 2U)

/**
* @brief          EQADC CFIFO3 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CF3R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x01C0UL + ((Index) << 2U)

/**
* @brief          EQADC CFIFO4 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CF4R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0200UL + ((Index) << 2U)

/**
* @brief          EQADC CFIFO5 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_CF5R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0240UL + ((Index) << 2U)

/**
* @brief          EQADC RFIFO0 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_RF0R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0300UL + ((Index) << 2U)

/**
* @brief          EQADC RFIFO1 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_RF1R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0340UL + ((Index) << 2U)

/**
* @brief          EQADC RFIFO2 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_RF2R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0380UL + ((Index) << 2U)

/**
* @brief          EQADC RFIFO3 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_RF3R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x03C0UL + ((Index) << 2U)

/**
* @brief          EQADC RFIFO4 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_RF4R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0400UL + ((Index) << 2U)

/**
* @brief          EQADC RFIFO5 Registers (0-3)
*/
/**
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined
 * @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern
 */
#define EQADC_RF5R_REG_ADDR32(Eqadc, Index)    (EQADC_ADDR32(Eqadc) + 0x0440UL + ((Index) << 2U)

/**
* @brief          Defines for RFIFO channel numbers for DMA
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCA_FISR0_RFDF0_U8        (0x01U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCA_FISR1_RFDF1_U8        (0x03U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCA_FISR2_RFDF2_U8        (0x05U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCA_FISR3_RFDF3_U8        (0x07U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCA_FISR4_RFDF4_U8        (0x09U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCA_FISR5_RFDF5_U8        (0x0BU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCB_FISR6_RFDF0_U8        (0x01U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCB_FISR7_RFDF1_U8        (0x03U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCB_FISR8_RFDF2_U8        (0x05U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCB_FISR9_RFDF3_U8        (0x07U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCB_FISR10_RFDF4_U8       (0x09U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_DMA_EQADCB_FISR11_RFDF5_U8       (0x0BU)

/**
* @brief          EQADC REGISTERS BITS
*/

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC Module Configuration Register (EQADC_MCR)                       */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_MCR_ICEA0_U32                     (0x00000080UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_MCR_ICEA1_U32                     (0x00000040UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_MCR_DBG_U32                       (0x00000003UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_MCR_DSM_U32                       (0x00000020UL)

/*---------------------------------------------------------------------------------------------------*/
/*                    EQADC External Trigger Digital Filter Register (EQADC_ETDFR)                   */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ETDFR_DFL_U32                     (0x0000000FUL)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Push Register x (EQADC_CFPRx)                             */
/*---------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC RFIFO Pop Register x (EQADC_RFPRx)                              */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RFPR_RF_POP_U32          (0x0001FFFFUL)

/*----------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Control Register 0 (EQADC_CFCR0)                           */
/*----------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Control Register 1 (EQADC_CFCR1)                           */
/*----------------------------------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Control Register 2 (EQADC_CFCR2)                           */
/*----------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR0_CFEE0_U16              (0x1000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR0_STRME0_U16             (0x0800U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR0_AMODE0_U16             (0x000FU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_SSE_U16                 (0x0400U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_CFINV_U16               (0x0200U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_U16                (0x00F0U)

/**< @brief 0b0000 - Disabled */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_DISABLED_U16       (0x0000U)
/**< @brief 0b0001 - Software trigger, single scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_SWSS_U16           (0x0010U)
/**< @brief 0b0010 - Low level gated external trigger, single scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWSS_LOL_U16       (0x0020U)
/**< @brief 0b0011 - High level gated external trigger, single scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWSS_HIL_U16       (0x0030U)
/**< @brief 0b0100 - Falling edge external trigger, single scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWSS_FED_U16       (0x0040U)
/**< @brief 0b0101 - Rising edge external trigger, single scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWSS_RED_U16       (0x0050U)
/**< @brief 0b0110 - Falling or rising edge external trigger, single scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWSS_BED_U16       (0x0060U)
/**< @brief 0b1001 - Software trigger, continuous scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_SWCS_U16           (0x0090U)
/**< @brief 0b1010 - Low level gated external trigger, continuous scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWCS_LOL_U16       (0x00A0U)
/**< @brief 0b1011 - High level gated external trigger, continuous scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWCS_HIL_U16       (0x00B0U)
/**< @brief 0b1100 - Falling edge external trigger, continuous scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWCS_FED_U16       (0x00C0U)
/**< @brief 0b1101 - Rising edge external trigger, continuous scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWCS_RED_U16       (0x00D0U)
/**< @brief 0b1110 - Falling or rising edge external trigger, continuous scan */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFCR_MODE_HWCS_BED_U16       (0x00E0U)

/*-------------------------------------------------------------------------------------------------------*/
/*                             EQADC Interrupt and DMA Control Register x (EQADC_IDCRx)                  */
/*-------------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_NCIE_U16                 (0x8000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_TORIE_U16                (0x4000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_PIE_U16                  (0x2000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_EOQIE_U16                (0x1000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_CFUIE_U16                (0x0800U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_CFFE_U16                 (0x0200U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_CFFS_U16                 (0x0100U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_RFOIE_U16                (0x0008U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_RFDE_U16                 (0x0002U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_RFDS_U16                 (0x0001U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_IDCR_CLEAR_U16                (0x0000U)
/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC FIFO and Interrupt Status Register x (EQADC_FISRx)              */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_CLEAR_MASK_U32             (0xF80A0000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_NCF_U32                    (0x80000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_TORF_U32                   (0x40000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_PF_U32                     (0x20000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_EOQF_U32                   (0x10000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_CFUF_U32                   (0x08000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_SSS_U32                    (0x04000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_CFFF_U32                   (0x02000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_RFOF_U32                   (0x00080000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_RFDF_U32                   (0x00020000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_CFCTR_U32                  (0x0000F000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_TNXTPTR_U32                (0x00000F00UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_RFCTR_U32                  (0x000000F0UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_RFCTR_EMPTY_U32            (0x00000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FISR_POPNXTPTR_U32              (0x0000000FUL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_REG32_RESET_VALUE_U32           (0x00000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_REG16_RESET_VALUE_U16           (0x0000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_REG8_RESET_VALUE_U8             (0x00U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR_CLEAR_MASK_U32            (0x00007800UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RESULT_FIFO_0_U32               (0x00000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RESULT_FIFO_1_U32               (0x00100000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RESULT_FIFO_2_U32               (0x00200000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RESULT_FIFO_3_U32               (0x00300000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RESULT_FIFO_4_U32               (0x00400000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RESULT_FIFO_5_U32               (0x00500000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_RESULT_FIFO_OFFSET_U32          (0x00100000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_EQADCB_DMACH_START_U8           (0x40U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_FIFO_MAX_DEPTH_U8               (0x04U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CBUFFER_DEPTH_U8                (0x02U)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Transfer Counter Register 0 (EQADC_CFTCR0)                */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFTCR_CLEAR_U16                (0x0000U)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Transfer Counter Register 1 (EQADC_CFTCR1)                */
/*---------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Transfer Counter Register 2 (EQADC_CFTCR2)                */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFTCR0_TC_CF0_U32                    (0x07FF0000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFTCR0_TC_CF1_U32                    (0x000007FFUL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFTCR1_TC_CF2_U32                    (0x07FF0000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFTCR1_TC_CF3_U32                    (0x000007FFUL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFTCR2_TC_CF4_U32                    (0x07FF0000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFTCR2_TC_CF5_U32                    (0x000007FFUL)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Status Snapshot Register 0 (EQADC_CFSSR0)                 */
/*---------------------------------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Status Snapshot Register 1 (EQADC_CFSSR1)                 */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_CFS0_TCB0_U32               (0xC0000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_CFS1_TCB0_U32               (0x30000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_CFS2_TCB0_U32               (0x0C000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_CFS3_TCB0_U32               (0x03000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_CFS4_TCB0_U32               (0x00C00000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_CFS5_TCB0_U32               (0x00300000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_LCFTCB0_U32                 (0x00007800UL)
/**< @brief - 0b0000 - Last command was transferred from CFIFO0 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_LCFTCB00_U32                (0x00000000UL)
/**< @brief - 0b0001 - Last command was transferred from CFIFO1 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_LCFTCB01_U32                (0x00000800UL)
/**< @brief - 0b0010 - Last command was transferred from CFIFO2 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_LCFTCB02_U32                (0x00001000UL)
/**< @brief - 0b0011 - Last command was transferred from CFIFO3 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_LCFTCB03_U32                (0x00001800UL)
/**< @brief - 0b0100 - Last command was transferred from CFIFO4 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_LCFTCB04_U32                (0x00002000UL)
/**< @brief - 0b0101 - Last command was transferred from CFIFO5 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_LCFTCB05_U32                (0x00002800UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR0_TC_LCFTCB0_U32              (0x000007FFUL)

/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_CFS0_TCB1_U32               (0xC0000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_CFS1_TCB1_U32               (0x30000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_CFS2_TCB1_U32               (0x0C000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_CFS3_TCB1_U32               (0x03000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_CFS4_TCB1_U32               (0x00C00000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_CFS5_TCB1_U32               (0x00300000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_LCFTCB1_U32                 (0x00007800UL)
/**< @brief - 0b0000 - Last command was transferred from CFIFO0 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_LCFTCB10_U32                (0x00000000UL)
/**< @brief - 0b0001 - Last command was transferred from CFIFO1 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_LCFTCB11_U32                (0x00000800UL)
/**< @brief - 0b0010 - Last command was transferred from CFIFO2 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_LCFTCB12_U32                (0x00001000UL)
/**< @brief - 0b0011 - Last command was transferred from CFIFO3 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_LCFTCB13_U32                (0x00001800UL)
/**< @brief - 0b0100 - Last command was transferred from CFIFO4 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_LCFTCB14_U32                (0x00002000UL)
/**< @brief - 0b0101 - Last command was transferred from CFIFO5 */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_LCFTCB15_U32                (0x00002800UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSSR1_TC_LCFTCB1_U32              (0x000007FFUL)

/*---------------------------------------------------------------------------------------------------*/
/*                             EQADC CFIFO Status Register (EQADC_CFSR)                              */
/*---------------------------------------------------------------------------------------------------*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSR_CFS0_U32                      (0xC0000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSR_CFS1_U32                      (0x30000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSR_CFS2_U32                      (0x0C000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSR_CFS3_U32                      (0x03000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSR_CFS4_U32                      (0x00C00000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSR_CFS5_U32                      (0x00300000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_1 Function-like macro defined */
#define EQADC_CFSR_FIFO_STATUS_U32(Fifo)         (0xC0000000UL >> ((Fifo)*2U))
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_CFSR_FIFO_STATUS_IDLE_U32          (0x00000000UL)


/**
* @brief          End Of Queue Bit. The EOQ bit is asserted in the last command of a CQueue to indicate to the EQADC
*                 that a scan of the CQueue is completed. EOQ instructs the EQADC to reset its current CFIFO transfer
*                 counter value (TC_CF) to zero. Depending on the CFIFO mode of operation, the CFIFO status will also
*                 change upon the detection of an asserted EOQ bit on the last transferred command - see Section 26.7.4.6,
*                 "CFIFO Scan Trigger Modes", for details.
*                 0 - Not the last entry of the CQueue.
*                 1 - Last entry of the CQueue.
*                 Note: If both the PAUSE and EOQ bits are asserted in the same command message the respective flags
*                 are set, but the CFIFO status changes as if only the EOQ bit were asserted.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_WRITE_CONFIG_EOQ_U32  (0x80000000UL)

/**
* @brief          BN Buffer Number Bit. BN indicates which buffer the message will be stored in.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_BN_U32       (0x02000000UL)

/**
* @brief          Message stored in buffer 1.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_BN1_U32      (0x02000000UL)
/**
* @brief          Message stored in buffer 0.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_BN0_U32      (0x00000000UL)

/**
* @brief          Read Write bit. An asserted R/W means a read command.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_READ_CONFIG_R_U32     (0x01000000UL)

/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_EN_U16                (0x8000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_STATUS_U16            (0xC000U)

/**
* @brief          ADC0/ADC1 Configuration Control Register (ADC0_CR, ADC1_CR) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CR_U8                 (0x01U)
/**
* @brief          ADC0/ADC1 Configuration Control Register (ADC0_CR, ADC1_CR) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_ACR1_U8               (0x30U)
/**
* @brief          ADC0/ADC1 Configuration Control Register (ADC0_CR, ADC1_CR) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_ACR2_U8               (0x34U)
/**
* @brief          Time Stamp Control Register (EQADC_ADC_TSCR_U8) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_TSCR_U8               (0x02U)
/**
* @brief          Time Base Counter Register (EQADC_ADC_TBCR_U8) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_TBCR_U8               (0x03U)
/**
* @brief          ADC0/ADC1 Gain Calibration Constant Register (ADC0_GCCR, ADC1_GCCR) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_GCCR_U8               (0x04U)
/**
* @brief          ADC0/ADC1 Offset Calibration Constant Register (ADC0_OCCR, ADC1_OCCR)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_OCCR_U8               (0x05U)
/**
* @brief          ADC0/ADC1 Alternate Gain 1 Register (ADC0_AGR1, ADC1_AGR1) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_AG1R_U8               (0x31U)
/**
* @brief          ADC0/ADC1 Alternate Offset 1 Register (ADC0_AOR1, ADC1_AOR1)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_AO1R_U8               (0x32U)
/**
* @brief          ADC0/ADC1 Alternate Gain 2 Register (ADC0_AGR2, ADC1_AGR2) Write/Read
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_AG2R_U8               (0x35U)
/**
* @brief          ADC0/ADC1 Alternate Offset 2 Register (ADC0_AOR2, ADC1_AOR2)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_AO2R_U8               (0x36U)
/**
* @brief          EQADC_ADC_CLK_SEL_U8 : Used for clock selection
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_SEL_U8            (0x20U)

/**
* @brief          ADCn_EN: ADCn enable. Enables ADCn to perform A/D conversions.
*                 0 - ADC is disabled. Clock supply to ADC0/1 is stopped.
*                 1 - ADC is enabled and ready to perform A/D conversions.
*                 NOTE: The bias generator circuit inside the ADC ceases functioning
*                 when both ADC0_EN and ADC1_EN bits are cleared.
*                 Conversion commands sent to a disabled ADC are ignored by
*                 the ADC control hardware.
*                 When the ADCn_EN status is changed from asserted to cleared,
*                 the ADC clock will not stop until it reaches its low phase.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_EN_U16                (0x8000U)

/**
* @brief          ADCn_EMUX: ADCn external multiplexer enable. When ADCn_EMUX is asserted,
*                 the MA pins will output digital values according to the number
*                 of the external channel being converted for selecting external
*                 multiplexer inputs.
*                 0 - External multiplexer disabled; no external multiplexer channels
*                 can be selected.
*                 1 - External multiplexer enabled; external multiplexer channels can be
*                 selected.
*                 NOTE: Both ADCn_EMUX bits must not be asserted at the same time.
*                 The ADCn_EMUX bit must only be written when the ADCn_EN bit is
*                 cleared (ADC disabled). ADCn_EMUX can be set during the same write
*                 cycle used to set ADCn_EN.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_EMUX_U16              (0x0800U)

/**
* @brief          System Clock Divide Factor for ADC Clock
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_0_U8           (0x00U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_1_U8           (0x01U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_2_U8           (0x02U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_3_U8           (0x03U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_4_U8           (0x04U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_5_U8           (0x05U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_6_U8           (0x06U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_7_U8           (0x07U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_8_U8           (0x08U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_9_U8           (0x09U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_10_U8          (0x0AU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_11_U8          (0x0BU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_12_U8          (0x0CU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_13_U8          (0x0DU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_14_U8          (0x0EU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_15_U8          (0x0FU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_16_U8          (0x10U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_17_U8          (0x11U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_18_U8          (0x12U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_19_U8          (0x13U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_20_U8          (0x14U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_21_U8          (0x15U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_22_U8          (0x16U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_23_U8          (0x17U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_24_U8          (0x18U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_25_U8          (0x19U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_26_U8          (0x1AU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_27_U8          (0x1BU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_28_U8          (0x1CU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_29_U8          (0x1DU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_30_U8          (0x1EU)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CLK_PS_31_U8          (0x1FU)

/**
* @brief          CAL: Calibration. Indicates if the returning conversion
*                 result must be calibrated.
*                 0 - Do not calibrate conversion result.
*                 1 - Calibrate conversion result.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_CAL_U32                  (0x01000000UL)

/**
* @brief          eQADC Calibration References
*/

/**
* @brief          75% VREF IDEAL (CAL=1)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_IDEAL_RES75_U32                 (0x00003000UL)
/**
* @brief          25% VREF IDEAL (CAL=1)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_IDEAL_RES25_U16                 (0x1000U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_COMMAND_CAL_CHANNEL25_U32           (0x00082C00UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_COMMAND_CAL_CHANNEL75_U32           (0x00002B00UL)

/**
* @brief          FMT: Conversion data format. FMT specifies to the eQADC how to format
*                 the 12-bit conversion data returned by the ADCs into the 16-bit
*                 format which is sent to the RFIFOs.
*                 0 - Right justified unsigned.
*                 1 - Right justified signed.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_FMT_U32                  (0x00010000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_FMT_RJU_U32              (0x00000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_FMT_RJS_U32              (0x00010000UL)

/**
* @brief          LST: Long sampling time. These two bits determine the duration of
*                 the sampling time in ADC clock cycles.
*                 NOTE: For external mux mode, 64 or 128 sampling cycles is recommended.
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_LST_U32                  (0x000C0000UL)
/**
* @brief          2 Sampling cycles (ADC Clock Cycles)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_LST_2_U32                (0x00000000UL)
/**
* @brief          8 Sampling cycles (ADC Clock Cycles)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_LST_8_U32                (0x00040000UL)
/**
* @brief          64 Sampling cycles (ADC Clock Cycles)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_LST_64_U32               (0x00080000UL)
/**
* @brief          128 Sampling cycles (ADC Clock Cycles)
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_CONV_COM_LST_128_U32              (0x000C0000UL)

/**
* @brief          EQADC clock cycle values
*/
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_2_CLOCK_CYCLES_U32                (0x000000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_8_CLOCK_CYCLES_U32                (0x040000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_64_CLOCK_CYCLES_U32               (0x080000UL)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_ADC_128_CLOCK_CYCLES_U32              (0x0C0000UL)

/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_8BIT_RES_CONFIG_SEL_U16               (0x80U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_10BIT_RES_CONFIG_SEL_U16              (0x40U)
/** @violates @ref Adc_Reg_eSys_Eqadc_h_REF_2 Reuse of C90 identifier pattern */
#define EQADC_12BIT_RES_CONFIG_SEL_U16              (0x0U)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /* ADC_REG_ESYS_EQADC_H */

/** @} */

