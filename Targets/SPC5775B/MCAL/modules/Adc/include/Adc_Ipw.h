/**
*   @file    Adc_Ipw.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - Separation header layer of high-low level drivers.
*   @details Header interface between common and low level driver.
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

#ifndef ADC_IPW_H
#define ADC_IPW_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Ipw_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Use of function like macro. 
* Function like macros are used to reduce code complexity.
*
* @section Adc_Ipw_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections.
*
* @section Adc_Ipw_h_REF_3
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
* 
* @section Adc_Ipw_h_REF_4
* Violates MISRA 2004 Required Rule 8.8, An external object or function shall be declared
* in one and only one file.
* These objects are used in several files in the code
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. All compilers used support more than 31 chars for
* identifiers.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Adc_Types.h"
#include "Adc_Eqadc.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_IPW_H                       43
#define ADC_AR_RELEASE_MAJOR_VERSION_IPW_H        4
#define ADC_AR_RELEASE_MINOR_VERSION_IPW_H        0
/**
* @violates @ref Adc_Ipw_h_REF_3 The compiler/linker shall be checked to ensure that 31 character
*/
#define ADC_AR_RELEASE_REVISION_VERSION_IPW_H     3
#define ADC_SW_MAJOR_VERSION_IPW_H                1
#define ADC_SW_MINOR_VERSION_IPW_H                0
#define ADC_SW_PATCH_VERSION_IPW_H                1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Adc_Types header file are of the same vendor */
#if (ADC_VENDOR_ID_IPW_H != ADC_VENDOR_ID_TYPES)
    #error "Adc_Ipw.c and Adc_Types.h have different vendor ids"
#endif

/* Check if source file and Adc_Types header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_IPW_H != ADC_AR_RELEASE_MAJOR_VERSION_TYPES) || \
     (ADC_AR_RELEASE_MINOR_VERSION_IPW_H != ADC_AR_RELEASE_MINOR_VERSION_TYPES) || \
     (ADC_AR_RELEASE_REVISION_VERSION_IPW_H != ADC_AR_RELEASE_REVISION_VERSION_TYPES) \
    )
#error "AutoSar Version Numbers of Adc_Ipw.h and Adc_Types.h are different"
#endif

/* Check if source file and ADC Adc_Types header file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION_IPW_H != ADC_SW_MAJOR_VERSION_TYPES) || \
     (ADC_SW_MINOR_VERSION_IPW_H != ADC_SW_MINOR_VERSION_TYPES) || \
     (ADC_SW_PATCH_VERSION_IPW_H != ADC_SW_PATCH_VERSION_TYPES) \
    )
#error "Software Version Numbers of Adc_Ipw.h and Adc_Types.h are different"
#endif

/* Check if source file and Adc_ADCDig header file are of the same vendor */
#if (ADC_VENDOR_ID_IPW_H != ADC_VENDOR_ID_EQADC)
    #error "Adc_Ipw.c and Adc_Eqadc.h have different vendor ids"
#endif

/* Check if source file and Adc_ADCDig header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_IPW_H != ADC_AR_RELEASE_MAJOR_VERSION_EQADC) || \
     (ADC_AR_RELEASE_MINOR_VERSION_IPW_H != ADC_AR_RELEASE_MINOR_VERSION_EQADC) || \
     (ADC_AR_RELEASE_REVISION_VERSION_IPW_H != ADC_AR_RELEASE_REVISION_VERSION_EQADC) \
    )
#error "AutoSar Version Numbers of Adc_Ipw.h and Adc_Eqadc.h are different"
#endif

/* Check if source file and ADC Adc_ADCDig header file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION_IPW_H != ADC_SW_MAJOR_VERSION_EQADC) || \
     (ADC_SW_MINOR_VERSION_IPW_H != ADC_SW_MINOR_VERSION_EQADC) || \
     (ADC_SW_PATCH_VERSION_IPW_H != ADC_SW_PATCH_VERSION_EQADC) \
    )
#error "Software Version Numbers of Adc_Ipw.h and Adc_Eqadc.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief          Access to the channel index of a group.
* @details        Helper macro to ease access to the channel index of a group.
*
* @violates @ref Adc_Ipw_h_REF_1 Use of function like macro.
*/
#define Adc_GroupChannelIndex(group,Channel)  (Adc_pCfgPtr->pGroups[(group)].pAssignment[(Channel)])

/**
* @brief          Functions mapping.
* @details        Middle layer versus Low layer functions mapping
*
*/
#define Adc_Ipw_Init                                        (Adc_Eqadc_Init)

#if (ADC_DEINIT_API == STD_ON)
  #define Adc_Ipw_DeInit                                    (Adc_Eqadc_DeInit)
#endif /* ADC_DEINIT_API == STD_ON */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
  #define Adc_Ipw_StartNormalConversion                     (Adc_Eqadc_StartNormalConversion)
  #define Adc_Ipw_StopCurrentConversion                     (Adc_Eqadc_StopCurrentConversion)
#endif /* ADC_ENABLE_START_STOP_GROUP_API == STD_ON */

#if (ADC_HW_TRIGGER_API == STD_ON)
  #define Adc_Ipw_EnableHardwareTrigger                     (Adc_Eqadc_EnableHardwareTrigger)
  #define Adc_Ipw_DisableHardwareTrigger                    (Adc_Eqadc_DisableHardwareTrigger)
#endif /* ADC_HW_TRIGGER_API == STD_ON */

#if (ADC_READ_GROUP_API == STD_ON)
  #define Adc_Ipw_ReadGroup                                 (Adc_Eqadc_ReadGroup)
#endif /* ADC_HW_TRIGGER_API == STD_ON */

#if (ADC_CALIBRATION == STD_ON)
  #define Adc_Ipw_Calibrate                                 (Adc_Eqadc_Calibrate)
#endif /* ADC_CALIBRATION == STD_ON */

#if (ADC_DUAL_CLOCK_MODE == STD_ON)
#define Adc_Ipw_SetClockMode                                (Adc_Eqadc_SetClockMode)
#endif /* (ADC_DUAL_CLOCK_MODE == STD_ON) */

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
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Ipw_h_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
FUNC(boolean, ADC_CODE) Adc_CheckConversionValuesInRange
(
    VAR(Adc_ValueGroupType, AUTOMATIC) Value,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_ChannelType, AUTOMATIC) Index
);
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */

#if (ADC_ENABLE_QUEUING == STD_ON)
FUNC(void, ADC_CODE) Adc_RemoveFromQueue
(
    CONST(Adc_HwUnitType, AUTOMATIC) Unit,
    CONST(Adc_QueueIndexType, AUTOMATIC) CurQueueIndex
);
#endif /* (ADC_ENABLE_QUEUING == STD_ON) */

#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_Ipw_h_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* ADC_IPW_H */

/** @} */
