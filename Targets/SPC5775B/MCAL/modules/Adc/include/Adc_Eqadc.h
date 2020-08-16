/**
*   @file    Adc_Eqadc.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - EQADC IP header file.
*   @details EQADC low level driver API.
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

#ifndef ADC_EQADC_H
#define ADC_EQADC_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Eqadc_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h.
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section Adc_Eqadc_h_REF_2
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Eqadc_h_REF_3
* Violates MISRA 2004 Required Rule 8.8, An external object or function shall be declared
* in one and only one file.
* These objects are used in several files in the code.
*
* @section Adc_Eqadc_h_REF_4
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and
* functions shall not be reused. Symbols defined are not library macros or objects.
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

#include "Adc_Reg_eSys_Eqadc.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_EQADC                      43
/**
* @violates @ref Adc_Eqadc_h_REF_2 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_MAJOR_VERSION_EQADC       4
/**
* @violates @ref Adc_Eqadc_h_REF_2 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_MINOR_VERSION_EQADC       0
/**
* @violates @ref Adc_Eqadc_h_REF_2 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_REVISION_VERSION_EQADC    3
#define ADC_SW_MAJOR_VERSION_EQADC               1
#define ADC_SW_MINOR_VERSION_EQADC               0
#define ADC_SW_PATCH_VERSION_EQADC               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Reg_eSys_ADCDig header file are of the same vendor */
#if (ADC_VENDOR_ID_EQADC != ADC_VENDOR_ID_REG)
    #error "Adc_Eqadc.h and Adc_Reg_eSys_Eqadc.h have different vendor ids"
#endif

/* Check if source file and Reg_eSys_ADCDig header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_EQADC != ADC_AR_RELEASE_MAJOR_VERSION_REG) || \
     (ADC_AR_RELEASE_MINOR_VERSION_EQADC != ADC_AR_RELEASE_MINOR_VERSION_REG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_EQADC != ADC_AR_RELEASE_REVISION_VERSION_REG) \
    )
    #error "AutoSar Version Numbers of Adc_Eqadc.h and Adc_Reg_eSys_Eqadc.h are different"
#endif

/* Check if source file and ADC Reg_eSys_ADCDig header file are of the same software version */
#if ((ADC_SW_MAJOR_VERSION_EQADC != ADC_SW_MAJOR_VERSION_REG) || \
     (ADC_SW_MINOR_VERSION_EQADC != ADC_SW_MINOR_VERSION_REG) || \
     (ADC_SW_PATCH_VERSION_EQADC != ADC_SW_PATCH_VERSION_REG) \
    )
#error "Software Version Numbers of Adc_Eqadc.h and Adc_Reg_eSys_Eqadc.h are different"
#endif

/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief          Calibration defines
*/
#define ADC_CAL_GCC_U8                          (0x08000000UL)
#define ADC_IDEAL_RES75_2_U8                    (12286UL)
#define ADC_CAL_CONST_U8                        (0x80000000UL)
#define ADC_CAL_25VREF_U8                       (0x00002C00UL)
#define ADC_CAL_75VREF_U8                       (0x00002B00UL)
#define ADC_OCC_REG_U8                          (0x0000FFFFUL)
#define ADC_CFPR0_GCCR_U8                       (0x4000UL)
#define ADC_CFPR0_OCCR_U8                       (0x4000UL)
#define ADC_CFPR0_CR_U8                         (0x001FUL)
#define ADC_CFPR1_CR_U8                         (0x001FUL)
#define ADC_CFPR2_CR_U8                         (0x001FUL)
#define ADC_CFPR3_CR_U8                         (0x001FUL)
#define ADC_CFPR4_CR_U8                         (0x001FUL)
#define ADC_CFPR5_CR_U8                         (0x001FUL)

/**
* @brief          eQADC resolution 8/10/12 bits
*/
/** @violates @ref Adc_Eqadc_h_REF_4 Reuse of C90 identifier pattern */
#define EQADC_BITS_RESOLUTION_8_U8              (0x08U)
/** @violates @ref Adc_Eqadc_h_REF_4 Reuse of C90 identifier pattern */
#define EQADC_BITS_RESOLUTION_10_U8             (0x0AU)
/** @violates @ref Adc_Eqadc_h_REF_4 Reuse of C90 identifier pattern */
#define EQADC_BITS_RESOLUTION_12_U8             (0x0CU)
/** @violates @ref Adc_Eqadc_h_REF_4 Reuse of C90 identifier pattern */
#define ADC_ACR2_RESSEL_8BIT_U8                 (0x80U)
/** @violates @ref Adc_Eqadc_h_REF_4 Reuse of C90 identifier pattern */
#define ADC_ACR1_RESSEL_10BIT_U8                (0x40U)
/** @violates @ref Adc_Eqadc_h_REF_4 Reuse of C90 identifier pattern */
#define ADC_CONVERSION_TIMEOUT_U8               (0x1000U)
/** @violates @ref Adc_Eqadc_h_REF_4 Reuse of C90 identifier pattern */
#define EQADC_DATA_MASK_U32                     (0x3FFCUL)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
#define ADC_START_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_Eqadc_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"
/**
* @brief          Used to point the configuration structure.
*
* @violates @ref Adc_Eqadc_h_REF_3  External object declared more than once
*/
extern P2CONST(Adc_ConfigType, ADC_VAR, ADC_APPL_CONST) Adc_pCfgPtr;

#define ADC_STOP_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_Eqadc_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

#define ADC_START_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_Eqadc_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"
/** @violates @ref Adc_Eqadc_h_REF_3  External object declared more than once */
extern VAR(Adc_ChannelIndexType, ADC_VAR) Adc_Eqadc_CFifoChannelCount[ADC_EQADC_MAX_U8][ADC_EQADC_MAX_FIFO_U8];
/** @violates @ref Adc_Eqadc_h_REF_3  External object declared more than once */
extern VAR(Adc_ChannelIndexType, ADC_VAR) Adc_Eqadc_RFifoChannelCount[ADC_EQADC_MAX_U8][ADC_EQADC_MAX_FIFO_U8];
/** @violates @ref Adc_Eqadc_h_REF_3  External object declared more than once*/
extern VAR(Adc_GroupStatusType, ADC_VAR) Adc_aGroupStatus[ADC_MAX_GROUPS];
/** @violates @ref Adc_Eqadc_h_REF_3  External object declared more than once*/
extern VAR(Adc_UnitStatusType , ADC_VAR) Adc_aUnitStatus[ADC_MAX_HW_UNITS];
/**
* @brief          EQADCA/EQADCB Fifo ongoing group array
* @violates @ref Adc_Eqadc_h_REF_3  External object declared more than once
*/
extern VAR(Adc_GroupType, ADC_VAR) Adc_Eqadc_FifoOngoingGroup[ADC_EQADC_MAX_U8][ADC_EQADC_MAX_FIFO_U8];

#define ADC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/** @violates @ref Adc_Eqadc_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define ADC_START_SEC_CODE
/** @violates @ref Adc_Eqadc_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

FUNC(void, ADC_CODE) Adc_Eqadc_Init
(
    P2CONST(Adc_ConfigType, AUTOMATIC, ADC_APPL_CONST) pCfgPtr
);

#if (ADC_DEINIT_API == STD_ON)
FUNC(void, ADC_CODE) Adc_Eqadc_DeInit(void);
#endif /* (ADC_DEINIT_API == STD_ON) */

#if (ADC_ENABLE_START_STOP_GROUP_API == STD_ON)
FUNC(void, ADC_CODE) Adc_Eqadc_StartNormalConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);

FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_StopCurrentConversion
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(boolean, AUTOMATIC) bStartApi
);
#endif /* (ADC_ENABLE_START_STOP_GROUP_API == STD_ON) */

#if (ADC_HW_TRIGGER_API == STD_ON)
FUNC(void, ADC_CODE) Adc_Eqadc_EnableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
FUNC(void, ADC_CODE) Adc_Eqadc_DisableHardwareTrigger
(
    VAR(Adc_GroupType, AUTOMATIC) Group,
    VAR(Adc_HwUnitType, AUTOMATIC) Unit
);
#endif /* (ADC_HW_TRIGGER_API == STD_ON) */

#if (ADC_READ_GROUP_API == STD_ON)
FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_ReadGroup
(
    CONST(Adc_GroupType, AUTOMATIC) Group,
    P2VAR(Adc_ValueGroupType, AUTOMATIC, ADC_APPL_DATA) pDataPtr,
    P2VAR(boolean, AUTOMATIC, ADC_APPL_DATA) pFlag
);
#endif /* (ADC_READ_GROUP_API == STD_ON) */

#if (ADC_CALIBRATION == STD_ON)
FUNC(void, ADC_CODE) Adc_Eqadc_Calibrate
(
    VAR(Adc_HwUnitType, AUTOMATIC) Unit,
    P2VAR(Adc_CalibrationStatusType , AUTOMATIC, ADC_APPL_DATA) pStatus
);
#endif /* ADC_CALIBRATION == STD_ON */

#if (ADC_DUAL_CLOCK_MODE == STD_ON)
FUNC(Std_ReturnType, ADC_CODE) Adc_Eqadc_SetClockMode
(
    VAR(Adc_DualClockModeType, AUTOMATIC) eClockMode
);
#endif /* (ADC_DUAL_CLOCK_MODE == STD_ON) */


FUNC(void, ADC_CODE) Adc_Eqadc_ClearRFifo
(
    VAR(uint8, AUTOMATIC) u8EqadcIdx,
    VAR(uint8, AUTOMATIC) u8FifoIdx
);

#define ADC_STOP_SEC_CODE
/** @violates @ref Adc_Eqadc_h_REF_1 Repeated include file MemMap.h */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* ADC_EQADC_H */

/** @} */
