/**
*   @file Adc_Reg_eSys_Siu.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - SIU low level driver register defines.
*   @details The description of the registers of the SIU module.
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
==================================================================================================*/

#ifndef ADC_REG_ESYS_SIU_H
#define ADC_REG_ESYS_SIU_H
#ifdef __cplusplus
extern "C"{
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Reg_eSys_Siu_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Adc_Reg_eSys_Siu_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header file being included twice
* This is not a violation since all header files are protected against multiple inclusions
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.

*/


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

/**
* @violates @ref Adc_Reg_eSys_Siu_h_REF_2 MISRA 2004 Required Rule 19.15, 
*           Precautions to prevent the contents of a header file being included twice.
*/

#include "Reg_eSys.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define ADC_REGESYS_SIU_VENDOR_ID_REG                    43
#define ADC_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION_REG     4
#define ADC_REGESYS_SIU_AR_RELEASE_MINOR_VERSION_REG     0
#define ADC_REGESYS_SIU_AR_RELEASE_REVISION_VERSION_REG  3
#define ADC_REGESYS_SIU_SW_MAJOR_VERSION_REG             1
#define ADC_REGESYS_SIU_SW_MINOR_VERSION_REG             0
#define ADC_REGESYS_SIU_SW_PATCH_VERSION_REG             1


/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
/* Reg_eSys.h version check start */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if ((ADC_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION_REG != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
       (ADC_REGESYS_SIU_AR_RELEASE_MINOR_VERSION_REG != REG_ESYS_AR_RELEASE_MINOR_VERSION)    \
      )
      #error "AutoSar Version Numbers of Adc_Reg_eSys_Siu.h and Reg_eSys.h are different"
  #endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*=================================================================================================
*                               DEFINES AND MACROS
=================================================================================================*/
/**
* @brief eQADC Command FIFO Trigger Source Registers
*/
#define SIU_ISEL4_REG_ADDR32                (SIU_BASEADDR + 0x0910UL)
#define SIU_ISEL5_REG_ADDR32                (SIU_BASEADDR + 0x0914UL)
#define SIU_ISEL6_REG_ADDR32                (SIU_BASEADDR + 0x0918UL)
#define SIU_ISEL7_REG_ADDR32                (SIU_BASEADDR + 0x091CUL)
#define SIU_ISEL8_REG_ADDR32                (SIU_BASEADDR + 0x0920UL)
#define SIU_ISEL9_REG_ADDR32                (SIU_BASEADDR + 0x0924UL)

/**
* @brief The reset value for 32 bits registers
*/
#define SIU_REG8_RESET_VALUE_U8             (0x0U)
#define SIU_REG16_RESET_VALUE_U16           (0x0U)
#define SIU_REG32_RESET_VALUE_U32           (0x0UL)

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
/* ADC_REG_ESYS_SIU_H */
#endif
/** @} */
