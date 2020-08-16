/**
*   @file    Adc_Eqadc_CfgEx.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - EQADC configuration header file.
*   @details EQADC Configuration extern low level driver API.
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

#ifndef ADC_EQADC_CFGEX_H
#define ADC_EQADC_CFGEX_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Eqadc_CfgEx_h_REF_1
* Violates MISRA 2004 Required Rule 1.4, Compiler shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers. This check has
* been done against the used compilers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers shall not more than 31 characters
* Violation is needed because of Autosar restrictions for naming File version check macros.
*
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcal.h"
#include "Adc_Types.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_EQADC_CFGEX                        43
#define ADC_AR_RELEASE_MAJOR_VERSION_EQADC_CFGEX         4
#define ADC_AR_RELEASE_MINOR_VERSION_EQADC_CFGEX         0
/** @violates @ref Adc_Eqadc_CfgEx_h_REF_1 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_AR_RELEASE_REVISION_VERSION_EQADC_CFGEX      3
#define ADC_SW_MAJOR_VERSION_EQADC_CFGEX                 1
#define ADC_SW_MINOR_VERSION_EQADC_CFGEX                 0
#define ADC_SW_PATCH_VERSION_EQADC_CFGEX                 1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_CFGEX != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (ADC_AR_RELEASE_MINOR_VERSION_EQADC_CFGEX != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of Adc_Eqadc_CfgEx.h and Mcal.h are different"
 #endif 
#endif

/* Check if source file and ADC configuration header file are of the same vendor */
#if (ADC_VENDOR_ID_EQADC_CFGEX != ADC_VENDOR_ID_TYPES)
#error "Adc_Eqadc_CfgEx.h and Adc_Types.h have different vendor ids"
#endif

/* Check if source file and ADC configuration header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC_CFGEX != ADC_AR_RELEASE_MAJOR_VERSION_TYPES) || \
     (ADC_AR_RELEASE_MINOR_VERSION_EQADC_CFGEX != ADC_AR_RELEASE_MINOR_VERSION_TYPES) || \
     (ADC_AR_RELEASE_REVISION_VERSION_EQADC_CFGEX != ADC_AR_RELEASE_REVISION_VERSION_TYPES) \
    )
#error "AutoSar Version Numbers of Adc_Eqadc_CfgEx.h and Adc_Types.h are different"
#endif

/* Check if source file and ADC configuration header file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION_EQADC_CFGEX != ADC_SW_MAJOR_VERSION_TYPES) || \
     (ADC_SW_MINOR_VERSION_EQADC_CFGEX != ADC_SW_MINOR_VERSION_TYPES) || \
     (ADC_SW_PATCH_VERSION_EQADC_CFGEX != ADC_SW_PATCH_VERSION_TYPES) \
    )
#error "Software Version Numbers of Adc_Eqadc_CfgEx.h and Adc_Types.h are different"
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
/**
* @brief          ADC group ISR alignment samples type.
* @details        Used to indicate if the group is right aligned or not.
*
*/
typedef enum
{
    ADC_ISR_RIGHT_ALIGH = 0U, /**< @brief Right alignment of samples group */
    ADC_ISR_NOT_RIGHT_ALIGH   /**< @brief Samples of group not aligned */
} Adc_Eqadc_GroupIsrAlignSamplesType;

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**< @brief Adc_Eqadc_FifoDmaChannelType configured dma channels for the eQADC_A and eQADC_B */
typedef uint8 Adc_Eqadc_FifoDmaChannelType;

/**
* @brief          Adc_Eqadc_ChannelConfigurationType.
*
*/
typedef struct
{
    CONST(uint32, ADC_CONST) u32Msg;                            /**< @brief Conversion command message */
    CONST(Adc_ResolutionType, ADC_CONST) Res;                   /**< @brief ADC HW Resolution (8/10/12 bits) */
} Adc_Eqadc_ChannelConfigurationType;

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON) || defined(__DOXYGEN__)
typedef struct
{ 
 CONST(boolean, ADC_CONST) bChannelLimitCheck;                /**< @brief Channel limit checking feature */
    CONST(Adc_ChannelRangeSelectType, ADC_CONST) eChannelRange;  /**< @brief  Range conversion */
    CONST(Adc_ValueGroupType, ADC_CONST) ChannelHighLimit;      /**< @brief High limit channel conversion value */
    CONST(Adc_ValueGroupType, ADC_CONST) ChannelLowLimit;       /**< @brief Low limit channel conversion value */
} Adc_Eqadc_ChannelLimitCheckingType;
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) || defined(__DOXYGEN__) */
/**
* @brief          Structure for Adc hardware unit configuration.
*
*/
typedef struct
{
    CONST(Adc_HwUnitType, ADC_CONST) AdcHardwareUnitId; /**< @brief Adc hardware unit id */
    CONST(uint32, ADC_CONST) u32AdcControlConfig;       /**< @brief Configuration of ADC hardware control register */
#if (ADC_CALIBRATION == STD_ON) || defined(__DOXYGEN__)
    CONST(boolean, ADC_CONST) bCalibration;             /**< @brief Calibration is/isn't performed  */
#endif /* (ADC_CALIBRATION == STD_ON) */
#if (ADC_DUAL_CLOCK_MODE == STD_ON)
    /**< @brief Prescaler of alternate mode */
    CONST(uint32, ADC_CONST) u32AdcAltPrescale;
#endif
} Adc_Eqadc_HwUnitConfigurationType;

/**
* @brief          Structure for group configuration.
*
*/
typedef struct
{
    CONST(Adc_HwUnitType, ADC_CONST) HwUnit; /**< @brief Hw unit to which the group belongs to */
    CONST(Adc_GroupAccessModeType , ADC_CONST) eAccessMode; /**< @brief ADC_ACCESS_MODE_SINGLE, ADC_ACCESS_MODE_STREAMING */
    CONST(Adc_GroupConvModeType , ADC_CONST) eMode; /**< @brief conversion mode (OneShot/Continuous) */
    CONST(Adc_GroupConvType , ADC_CONST) eType;                             /**< @brief Conversion type (Normal/Injected) */
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) || defined(__DOXYGEN__)
    CONST(Adc_GroupPriorityType , ADC_CONST) Priority; /**< @brief Priority of the group */
#endif /* #if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) || defined(__DOXYGEN__) */
    CONST(Adc_GroupReplacementType , ADC_CONST) eReplacementMode; /**< @brief Replacement mode of group */
    CONST(Adc_TriggerSourceType , ADC_CONST) eTriggerSource; /**< @brief Trigger source (Hw/Sw trigger) of group */
#if (STD_ON==ADC_HW_TRIGGER_API) || defined(__DOXYGEN__)
    CONST(Adc_HwTriggerSignalType , ADC_CONST) eTriggerEdge; /**< @brief Trigger Edge (Rising or falling) for hw trig groups */
    P2CONST(Adc_HwTriggerTimerType, ADC_VAR, ADC_APPL_CONST) pHwResource; /**< @brief Resource of the selected hw trigger */
#endif /* #if (STD_ON==ADC_HW_TRIGGER_API) || defined(__DOXYGEN__) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY) || defined(__DOXYGEN__)
    CONST(Adc_NotifyType , ADC_CONST) Notification; /**< @brief Pointer to notification function */
#endif /* #if (STD_ON==ADC_GRP_NOTIF_CAPABILITY) || defined(__DOXYGEN__) */
    CONST(uint8, ADC_CONST) u8AdcGroupFifo; /**< @brief Fifo used for this group */
    P2P2VAR(Adc_ValueGroupType, ADC_VAR, ADC_APPL_DATA) pResultsBufferPtr; /**< @brief Pointer to user defined result buffer */
    CONST(Adc_StreamBufferModeType , ADC_CONST) eBufferMode; /**< @brief ADC_STREAM_BUFFER_LINEAR, ADC_STREAM_BUFFER_CIRCULAR */
    CONST(Adc_StreamNumSampleType , ADC_CONST) NumSamples; /**< @brief Number of samples in streaming access mode */
    P2CONST(Adc_GroupDefType , ADC_VAR, ADC_APPL_CONST) pAssignment; /**< @brief Pointer to assigned channels in the group */
    CONST(Adc_ChannelIndexType , ADC_CONST) AssignedChannelCount; /**< @brief Number of channels configured in the group */
    CONST(uint8 , ADC_CONST) u8AdcWithoutInterrupt;                         /**< @brief Enables or Disables the ADC and DMA interrupts */
} Adc_GroupConfigurationType;

/**
* @brief          Miscellaneous configuration structure.
*
*/
typedef struct
{
    CONST(uint8, ADC_CONST) u8Adc_DmaInterruptSoftware[ADC_MAX_HW_UNITS]; /**< @brief Dma or interrupt driven */
    CONST(Adc_GroupType, ADC_CONST) Adc_MaxGroups; /**< @brief Number of the maximum groups in the current configuration */
    CONST(Adc_HwUnitType, ADC_CONST) Adc_MaxHwCfg; /**< @brief number of the maximum number of ADC hw units configured in the configset */
#if (ADC_HW_TRIGGER_API == STD_ON)
    /**< @brief low 8 bits of  EQADC_ETDFR*/
    VAR(uint8, ADC_VAR) au8ETriggerDigitalFilter[ADC_EQADC_MAX_U8];
#endif /* #if (ADC_HW_TRIGGER_API == STD_ON) */
    CONST(Adc_ChannelType, ADC_CONST) aAdc_Channels[ADC_MAX_HW_UNITS]; /**< @brief Number of channels of the hw unit x */
#ifdef ADC_DMA_SUPPORTED
    CONST(Adc_Eqadc_FifoDmaChannelType, ADC_CONST) aDmaChannel[ADC_EQADC_MAX_U8][(ADC_MAX_COMMAND_FIFO_U8+ADC_MAX_RESULT_FIFO_U8)]; /**< @brief Dma channel number for HW UNITS 0 and 1 */
#endif /* ADC_DMA_SUPPORTED */
    CONST(uint8, ADC_CONST) au8Adc_HwUnit[ADC_MAX_HW_UNITS];  /**< @brief Indicate if unit x is active (configured) STD_ON/STD_OFF */
    CONST(uint8, ADC_CONST) au8FirstFifo[ADC_MAX_HW_UNITS];  /**< @brief Fifo number of first group */
    CONST(Adc_HwUnitType, ADC_CONST) aHwLogicalId[ADC_MAX_HW_UNITS];  /**< Hardware index in the structure */
} Adc_Eqadc_MultiConfigType;

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* ADC_EQADC_CFGEX_H */

/** @} */
