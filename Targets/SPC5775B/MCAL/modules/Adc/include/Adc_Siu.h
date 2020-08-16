/**
*   @file    Adc_Siu.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc SIU low level SIU header.
*   @details This file is the SIU ADC low level driver header.
*
*   @addtogroup ADC_SIU
*   @{
*/
/*=================================================================================================
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

#ifndef ADC_SIU_H
#define ADC_SIU_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Siu_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file, 
* Precautions shall be taken in order to prevent the contents of a header file 
* being included twice This is not a violation since all header files are 
* protected against multiple inclusions
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
#include "Std_Types.h"
#include "Adc_Ipw.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define ADC_SIU_VENDOR_ID                     43
#define ADC_SIU_AR_RELEASE_MAJOR_VERSION      4
#define ADC_SIU_AR_RELEASE_MINOR_VERSION      0
#define ADC_SIU_AR_RELEASE_REVISION_VERSION   3
#define ADC_SIU_SW_MAJOR_VERSION              1
#define ADC_SIU_SW_MINOR_VERSION              0
#define ADC_SIU_SW_PATCH_VERSION              1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
#if (ADC_SIU_VENDOR_ID != ADC_VENDOR_ID_IPW_H)
    #error "VENDOR ID for Adc_Siu.h and Adc_Ipw.h is different"
#endif

#if ((ADC_SIU_AR_RELEASE_MAJOR_VERSION != ADC_AR_RELEASE_MAJOR_VERSION_IPW_H) || \
     (ADC_SIU_AR_RELEASE_MINOR_VERSION != ADC_AR_RELEASE_MINOR_VERSION_IPW_H) || \
     (ADC_SIU_AR_RELEASE_REVISION_VERSION != ADC_AR_RELEASE_REVISION_VERSION_IPW_H) \
    )
    #error "AUTOSAR Version Numbers of Adc_Siu.h and Adc_Ipw.h are different"
#endif

#if ((ADC_SIU_SW_MAJOR_VERSION != ADC_SW_MAJOR_VERSION_IPW_H) || \
     (ADC_SIU_SW_MINOR_VERSION != ADC_SW_MINOR_VERSION_IPW_H) || \
     (ADC_SIU_SW_PATCH_VERSION != ADC_SW_PATCH_VERSION_IPW_H) \
    )
    #error "Software Version Numbers of Adc_Siu.h and Adc_Ipw.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* Check if header file and Std_Types.h file are of the same Autosar version */
#if ((ADC_SIU_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_SIU_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) \
    )
    #error "AutoSar Version Numbers of Adc_Siu.h and Std_Types.h are different"
#endif
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
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
#if (STD_ON == ADC_HW_TRIGGER_API)
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Siu_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

FUNC (void, ADC_CODE) Adc_Siu_ResetAllHwTrigger(void);

FUNC (void, ADC_CODE) Adc_Siu_EnableHwTrigger
(
    VAR(uint16, AUTOMATIC) u16HwResource,
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8Fifo
);

FUNC (void, ADC_CODE) Adc_Siu_DisableHwTrigger
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8Fifo
);

#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_Siu_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"
#endif /* (STD_ON == ADC_HW_TRIGGER_API) */

#ifdef __cplusplus
}
#endif

#endif /* ADC_SIU_H */

/** @} */
