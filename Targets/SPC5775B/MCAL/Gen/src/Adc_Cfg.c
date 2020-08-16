/**
*   @file    Adc_Cfg.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - Pre-Compile configurations for ADC driver.
*   @details Pre-Compile configuration file for ADC driver.
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

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_Cfg_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
* This is an Autosar memory management requirement.
*
* @section Adc_Cfg_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h.
* This violation  is not  fixed since  the inclusion  of MemMap.h
* is as  per Autosar  requirement MEMMAP003.
*
* @section Adc_Cfg_c_REF_3
* Violates MISRA 2004 Required Rule 1.4,
* The compiler/linker shall be checked to ensure that 31 character significance and case
* sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Adc_Cfg_c_REF_4
* Violates MISRA 2004 Required Rule 8.10, all declarations and definitions of objects or functions 
* at file scope shall have internal linkage unless external linkage is required.
* This violation is due to Autosar files and structures definitions.
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
#include "Adc.h"
/** @violates @ref Adc_Cfg_c_REF_2 Repeated include file */
#include "Adc_Reg_eSys_Eqadc.h"

#ifdef ADC_PRECOMPILE_SUPPORT


/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_CFG_C                    43
/**
* @violates @ref Adc_Cfg_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_MAJOR_VERSION_CFG_C     4
/**
* @violates @ref Adc_Cfg_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_ERLEASE_MINOR_VERSION_CFG_C     0
/**
* @violates @ref Adc_Cfg_c_REF_3 The compiler/linker shall be checked to ensure that 31 character
* significance and case sensitivity are supported for external identifiers
*/
#define ADC_AR_RELEASE_REVISION_VERSION_CFG_C  3
#define ADC_SW_MAJOR_VERSION_CFG_C             1
#define ADC_SW_MINOR_VERSION_CFG_C             0
#define ADC_SW_PATCH_VERSION_CFG_C             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and ADC header file are of the same vendor */
#if (ADC_VENDOR_ID_CFG_C != ADC_VENDOR_ID)
    #error "Adc_Cfg.c and Adc.h have different vendor ids"
#endif

/* Check if source file and ADC header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_CFG_C != ADC_AR_RELEASE_MAJOR_VERSION) || \
     (ADC_AR_ERLEASE_MINOR_VERSION_CFG_C != ADC_AR_RELEASE_MINOR_VERSION) || \
     (ADC_AR_RELEASE_REVISION_VERSION_CFG_C != ADC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Adc_Cfg.c and Adc.h are different"
#endif

/* Check if source file and ADC header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_CFG_C != ADC_SW_MAJOR_VERSION) || \
     (ADC_SW_MINOR_VERSION_CFG_C != ADC_SW_MINOR_VERSION) || \
     (ADC_SW_PATCH_VERSION_CFG_C != ADC_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Adc_Cfg.c and Adc.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Eqadc header file are of the same vendor */
#if (ADC_VENDOR_ID_CFG_C != ADC_VENDOR_ID_REG)
    #error "Adc_Cfg.c and Adc_Reg_eSys_Eqadc.h have different vendor ids"
#endif

/* Check if source file and Adc_Reg_eSys_Eqadc header file are of the same Autosar version */
#if ((ADC_AR_RELEASE_MAJOR_VERSION_CFG_C != ADC_AR_RELEASE_MAJOR_VERSION_REG) || \
     (ADC_AR_ERLEASE_MINOR_VERSION_CFG_C != ADC_AR_RELEASE_MINOR_VERSION_REG) || \
     (ADC_AR_RELEASE_REVISION_VERSION_CFG_C != ADC_AR_RELEASE_REVISION_VERSION_REG) \
    )
    #error "AutoSar Version Numbers of Adc_Cfg.c and Adc_Reg_eSys_Eqadc.h are different"
#endif

/* Check if source file and Adc_Reg_eSys_Eqadc header file are of the same Software version */
#if ((ADC_SW_MAJOR_VERSION_CFG_C != ADC_SW_MAJOR_VERSION_REG) || \
     (ADC_SW_MINOR_VERSION_CFG_C != ADC_SW_MINOR_VERSION_REG) || \
     (ADC_SW_PATCH_VERSION_CFG_C != ADC_SW_PATCH_VERSION_REG) \
    )
    #error "Software Version Numbers of Adc_Cfg.c and Adc_Reg_eSys_Eqadc.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/
/**
* @brief          Total number of groups in Config.
*
*/

#define ADC_GROUPS           33


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#define ADC_START_SEC_CODE
/**
 * @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include"
 * @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h
 */
#include "MemMap.h"

/**
* @brief         ADC Notification functions.
* @details       ADC Nofification functions defined inside the Plugin.
*
*/


#define ADC_STOP_SEC_CODE
/**
 * @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include"
 * @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h
 */
#include "MemMap.h"

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/
#define ADC_START_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"

/**
* @brief          Group Assignments on ADC Hardware unit 0.
*
*/
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group0_AssignmentPC_0[ADC_CFGSET1_GROUP_0_CHANNELS] =
{
    0U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group1_AssignmentPC_0[ADC_CFGSET1_GROUP_1_CHANNELS] =
{
    1U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group2_AssignmentPC_0[ADC_CFGSET1_GROUP_2_CHANNELS] =
{
    2U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group3_AssignmentPC_0[ADC_CFGSET1_GROUP_3_CHANNELS] =
{
    3U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group4_AssignmentPC_0[ADC_CFGSET1_GROUP_4_CHANNELS] =
{
    4U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group5_AssignmentPC_0[ADC_CFGSET1_GROUP_5_CHANNELS] =
{
    5U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group6_AssignmentPC_0[ADC_CFGSET1_GROUP_6_CHANNELS] =
{
    6U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group7_AssignmentPC_0[ADC_CFGSET1_GROUP_7_CHANNELS] =
{
    7U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group8_AssignmentPC_0[ADC_CFGSET1_GROUP_8_CHANNELS] =
{
    8U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group9_AssignmentPC_0[ADC_CFGSET1_GROUP_9_CHANNELS] =
{
    9U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group10_AssignmentPC_0[ADC_CFGSET1_GROUP_10_CHANNELS] =
{
    10U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group11_AssignmentPC_0[ADC_CFGSET1_GROUP_11_CHANNELS] =
{
    11U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group12_AssignmentPC_0[ADC_CFGSET1_GROUP_12_CHANNELS] =
{
    12U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group13_AssignmentPC_0[ADC_CFGSET1_GROUP_13_CHANNELS] =
{
    13U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group14_AssignmentPC_0[ADC_CFGSET1_GROUP_14_CHANNELS] =
{
    14U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group15_AssignmentPC_0[ADC_CFGSET1_GROUP_15_CHANNELS] =
{
    15U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group16_AssignmentPC_0[ADC_CFGSET1_GROUP_16_CHANNELS] =
{
    16U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group17_AssignmentPC_0[ADC_CFGSET1_GROUP_17_CHANNELS] =
{
    17U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group18_AssignmentPC_0[ADC_CFGSET1_GROUP_18_CHANNELS] =
{
    18U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group19_AssignmentPC_0[ADC_CFGSET1_GROUP_19_CHANNELS] =
{
    19U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group20_AssignmentPC_0[ADC_CFGSET1_GROUP_20_CHANNELS] =
{
    20U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group21_AssignmentPC_0[ADC_CFGSET1_GROUP_21_CHANNELS] =
{
    21U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group22_AssignmentPC_0[ADC_CFGSET1_GROUP_22_CHANNELS] =
{
    22U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group23_AssignmentPC_0[ADC_CFGSET1_GROUP_23_CHANNELS] =
{
    23U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group30_AssignmentPC_0[ADC_CFGSET1_GROUP_30_CHANNELS] =
{
    24U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group31_AssignmentPC_0[ADC_CFGSET1_GROUP_31_CHANNELS] =
{
    25U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group32_AssignmentPC_0[ADC_CFGSET1_GROUP_32_CHANNELS] =
{
    26U
};
/**
* @brief          Group Assignments on ADC Hardware unit 1.
*
*/
/**
* @brief          Group Assignments on ADC Hardware unit 2.
*
*/
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group24_AssignmentPC_2[ADC_CFGSET1_GROUP_24_CHANNELS] =
{
    4U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group25_AssignmentPC_2[ADC_CFGSET1_GROUP_25_CHANNELS] =
{
    1U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group26_AssignmentPC_2[ADC_CFGSET1_GROUP_26_CHANNELS] =
{
    2U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group27_AssignmentPC_2[ADC_CFGSET1_GROUP_27_CHANNELS] =
{
    3U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group28_AssignmentPC_2[ADC_CFGSET1_GROUP_28_CHANNELS] =
{
    4U
};
static CONST(Adc_ChannelType, ADC_CONST) Adc_Group29_AssignmentPC_2[ADC_CFGSET1_GROUP_29_CHANNELS] =
{
    5U
};
/**
* @brief          Group Assignments on ADC Hardware unit 3.
*
*/


/**
* @brief          Definition of ADC hardware units .
*/
static CONST(Adc_Eqadc_HwUnitConfigurationType, ADC_CONST) Adc_HwUnitCfgPC[] =
{
    /**< @brief Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit id */
        (Adc_HwUnitType)0,
        (EQADC_ADC_EN_U16| EQADC_ADC_CLK_PS_2_U8)
#if (ADC_CALIBRATION == STD_ON)
        ,
        (boolean)FALSE /**< @brief calibration is/isn't performed  */
#endif /* (ADC_CALIBRATION == STD_ON) */
#if (ADC_DUAL_CLOCK_MODE == STD_ON)
        ,
        (EQADC_ADC_EN_U16| EQADC_ADC_CLK_PS_31_U8)
#endif /* (ADC_DUAL_CLOCK_MODE == STD_ON) */

    },
    /**< @brief Hardware Unit ADC2 */
    {
        /**< @brief Hardware unit id */
        (Adc_HwUnitType)2,
        (EQADC_ADC_EN_U16 | EQADC_ADC_CLK_SEL_U8)
#if (ADC_CALIBRATION == STD_ON)
        ,
        (boolean)FALSE /**< @brief calibration is/isn't performed  */
#endif /* (ADC_CALIBRATION == STD_ON) */
#if (ADC_DUAL_CLOCK_MODE == STD_ON)
        ,
        (EQADC_ADC_EN_U16 | EQADC_ADC_CLK_SEL_U8)
#endif /* (ADC_DUAL_CLOCK_MODE == STD_ON) */

    }
};


/**
* @brief          Definition of channels on ADC Hardware unit 0 .
* @details        Array of conversion command messages
*/
static CONST(Adc_Eqadc_ChannelConfigurationType, ADC_CONST) Adc_ChannelsCfgPC_0[] =
{

    /**< @brief Hardware Unit ADC0  --  AN_0 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(0)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_2 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(2)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_3 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(3)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_5 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(5)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_6 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(6)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_8 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(8)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_9 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(9)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_10 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(10)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_11 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(11)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_12 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(12)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_13 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(13)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_14 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(14)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_15 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(15)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_16 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(16)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_17 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(17)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_22 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(22)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_23 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(23)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_24 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(24)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_26 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(26)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_27 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(27)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_28 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(28)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_37 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(37)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_38 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(38)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_39 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(39)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_1 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(1)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_7 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(7)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC0  --  AN_4 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(4)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    }
};
/**
* @brief          Definition of channels on ADC Hardware unit 2 .
* @details        Array of conversion command messages
*/
static CONST(Adc_Eqadc_ChannelConfigurationType, ADC_CONST) Adc_ChannelsCfgPC_2[] =
{

    /**< @brief Hardware Unit ADC2  --  AN_17 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(17)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC2  --  AN_18 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(18)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC2  --  AN_19 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(19)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC2  --  AN_21 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(21)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC2  --  AN_22 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(22)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    },
    /**< @brief Hardware Unit ADC2  --  AN_23 */
    {
        /**< @brief Adc channel's command */
        (uint32)(EQADC_ADC_CONV_COM_BN0_U32  | EQADC_ADC_128_CLOCK_CYCLES_U32| EQADC_ADC_CONV_COM_FMT_RJU_U32 | ((uint32)ADC_ID_CHANNEL_U8(23)<<8U) | (uint32)EQADC_12BIT_RES_CONFIG_SEL_U16),
        /**< @brief Adc resolution */
        (Adc_ResolutionType)ADC_BITS_RESOLUTION_12_U8
    }
};


#define ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
#define ADC_START_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"
/**
* @brief          Adc Result Buffer RAM initializations.
* @details        Array for all ADC group result ram buffers.
*/
static P2VAR(Adc_ValueGroupType, ADC_VAR, ADC_APPL_DATA) Adc_ResultsBufferPtr[] =
{
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR,
    NULL_PTR
};


/**
* @brief          Definition of channels's pointer structure .
*
*/
static P2CONST(Adc_Eqadc_ChannelConfigurationType, ADC_VAR, ADC_APPL_CONST) Adc_ChannelsCfgPC[] =
{
    Adc_ChannelsCfgPC_0,
    NULL_PTR,
    Adc_ChannelsCfgPC_2,
    NULL_PTR
};


#define ADC_STOP_SEC_VAR_INIT_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"
/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/
#define ADC_START_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/** @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"


/**
* @brief          Definition of all ADC groups .
*/
static CONST(Adc_GroupConfigurationType, ADC_CONST) Adc_GroupsCfgPC[] =
{
    /**< @brief Group0 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group0_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_0_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group1 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group1_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_1_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group2 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group2_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_2_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group3 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group3_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_3_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group4 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group4_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_4_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group5 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group5_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_5_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group6 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group6_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_6_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group7 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group7_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_7_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group8 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group8_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_8_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group9 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group9_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_9_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group10 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group10_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_10_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group11 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group11_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_11_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group12 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group12_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_12_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group13 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group13_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_13_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group14 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group14_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_14_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group15 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group15_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_15_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group16 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group16_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_16_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group17 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group17_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_17_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group18 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group18_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_18_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group19 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group19_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_19_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group20 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group20_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_20_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group21 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group21_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_21_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group22 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group22_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_22_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group23 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group23_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_23_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group24 -- Hardware Unit ADC2 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)2,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group24_AssignmentPC_2,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_24_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group25 -- Hardware Unit ADC2 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)2,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group25_AssignmentPC_2,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_25_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group26 -- Hardware Unit ADC2 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)2,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group26_AssignmentPC_2,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_26_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group27 -- Hardware Unit ADC2 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)2,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group27_AssignmentPC_2,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_27_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group28 -- Hardware Unit ADC2 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)2,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group28_AssignmentPC_2,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_28_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group29 -- Hardware Unit ADC2 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)2,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group29_AssignmentPC_2,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_29_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group30 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group30_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_30_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group31 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group31_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_31_CHANNELS,
        (uint8)STD_ON
    },
    /**< @brief Group32 -- Hardware Unit ADC0 */
    {
        /**< @brief Hardware unit configured */
        (Adc_HwUnitType)0,
        /**< @brief Access mode */
        ADC_ACCESS_MODE_SINGLE,
        /**< @brief Conversion mode */
        ADC_CONV_MODE_ONESHOT,
        /**< @brief Conversion type */
        ADC_CONV_TYPE_NORMAL,
#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
        /**< @brief  Priority configured */
        ADC_GROUP_PRIORITY(0U),
#endif /* (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE) */
        /**< @brief Replacement mode */
        ADC_GROUP_REPL_ABORT_RESTART,
        /**< @brief Trigger source configured */
        ADC_TRIGG_SRC_SW,
#if (STD_ON==ADC_HW_TRIGGER_API)
        /**< @brief Hardware trigger signal */
        ADC_HW_TRIG_RISING_EDGE,
        /**< @brief Hardware resource for the group */
        0U,
#endif /* (STD_ON==ADC_HW_TRIGGER_API) */
#if (STD_ON==ADC_GRP_NOTIF_CAPABILITY)
        /**< @brief Notification function */

        NULL_PTR,
#endif /* (STD_ON==ADC_GRP_NOTIF_CAPABILITY) */
        /**< @brief CFIFO used for group */
        0U,
        /**< @brief ADC Group Result Buffers RAM array */
        Adc_ResultsBufferPtr,
        /**< @brief Group Streaming Buffer Mode */
        ADC_STREAM_BUFFER_LINEAR,
        /**< @brief Number of streaming samples */
        ADC_STREAMING_NUM_SAMPLES(1),
        /**< @brief Channels assigned to the group */
        Adc_Group32_AssignmentPC_0,
        /**< @brief Number of channels in the group */
        (Adc_ChannelIndexType)ADC_CFGSET1_GROUP_32_CHANNELS,
        (uint8)STD_ON
    }
};


/**
* @brief          ADC driver Configuration structure .
*/
/** @violates @ref Adc_Cfg_c_REF_4 MISRA-C:2004 Rule 8.10: External linkage.*/
CONST(Adc_ConfigType, ADC_CONST) Adc_ConfigPC =
{
    /**< @brief pointer to Hw unit configurations */
    Adc_HwUnitCfgPC,
    /**< @brief pointer to group configurations */
    Adc_GroupsCfgPC,
    /**< @brief pointer to channel configurations */
    Adc_ChannelsCfgPC,
    /**< @brief total number of groups */
    (Adc_GroupType)ADC_GROUPS,
    /**< @brief Miscellaneous configuration parameters. - Adc_Eqadc_MultiConfigType */
    {
        {
            ADC_INTERRUPT,
            ADC_INTERRUPT,
            ADC_INTERRUPT,
            ADC_INTERRUPT

        },
        /**< @brief number of the maximum groups in the current configuration */
        33U,
        /**< @brief number of the maximum hardware units in the current configuration */
        2U,
#if(ADC_HW_TRIGGER_API == STD_ON)
        {
            /**< @brief low 8 bits of EQADC_ETDFR for EQADCA */
            0x5U,
            /**< @brief low 8 bits of EQADC_ETDFR for EQADCB */
            0x5U
        },
#endif
        {
            /**< @brief number of channels of the ADC Hardware unit 0 */
            27U,
            /**< @brief number of channels of the ADC Hardware unit 1 */
            0U,
            /**< @brief number of channels of the ADC Hardware unit 2 */
            6U,
            /**< @brief number of channels of the ADC Hardware unit 3 */
            0U
        },
        {
            /**< @brief ADC0 - ON/OFF */
            (uint8)STD_ON,
            /**< @brief ADC1 - ON/OFF */
            (uint8)STD_OFF,
            /**< @brief ADC2 - ON/OFF */
            (uint8)STD_ON,
            /**< @brief ADC3 - ON/OFF */
            (uint8)STD_OFF
        },
        {
            /**< @brief First fifo of ADC0 */
            (uint8)0U,
            /**< @brief First fifo of ADC1 */
            (uint8)0U,
            /**< @brief First fifo of ADC2 */
            (uint8)0U,
            /**< @brief First fifo of ADC3 */
            (uint8)0U
        },
        {
            0U,
            255U,
            1U,
            255U
        }
    }
};


#define ADC_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/**  @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"

#define ADC_START_SEC_CONST_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/**  @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/**
* @brief          Definition of channels limit checking on ADC Hardware unit 0.
*/
static CONST(Adc_Eqadc_ChannelLimitCheckingType, ADC_CONST) Adc_ChannelsLimitCheckingCfg_0[] =
{
    /**< @brief Hardware Unit ADC0  --  AN_0 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_2 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_3 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_5 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_6 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_8 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_9 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_10 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_11 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_12 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_13 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_14 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_15 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_16 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_17 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_22 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_23 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_24 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_26 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_27 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_28 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_37 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_38 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_39 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_1 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_7 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC0  --  AN_4 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    }
};
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */
#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/**
* @brief          Definition of channels limit checking on ADC Hardware unit 2.
*/
static CONST(Adc_Eqadc_ChannelLimitCheckingType, ADC_CONST) Adc_ChannelsLimitCheckingCfg_2[] =
{
    /**< @brief Hardware Unit ADC2  --  AN_17 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC2  --  AN_18 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC2  --  AN_19 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC2  --  AN_21 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC2  --  AN_22 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    },
    /**< @brief Hardware Unit ADC2  --  AN_23 */
    {
        /**< @brief limit check disabled */
        (boolean)FALSE,
        /**< @brief range for limit check */
        (Adc_ChannelRangeSelectType)ADC_RANGE_ALWAYS,
        /**< @brief high limit value */
        (Adc_ValueGroupType)0,
        /**< @brief low limit value */
        (Adc_ValueGroupType)0

    }
};
#endif /* (ADC_ENABLE_LIMIT_CHECK == STD_ON) */



#define ADC_STOP_SEC_CONST_UNSPECIFIED
/** @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include" */
/**  @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h*/
#include "MemMap.h"

/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

#define ADC_START_SEC_VAR_INIT_UNSPECIFIED
/**
 * @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include"
 * @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h
 */
#include "MemMap.h"

#if (ADC_ENABLE_LIMIT_CHECK == STD_ON)
/**
* @brief          Definition of channels' limit checking pointer structure.
*
*/
P2CONST(Adc_Eqadc_ChannelLimitCheckingType, ADC_VAR, ADC_APPL_CONST) Adc_ChannelsLimitCheckingCfg[]=
{
    Adc_ChannelsLimitCheckingCfg_0,
    NULL_PTR,
    Adc_ChannelsLimitCheckingCfg_2,
    NULL_PTR
};
#endif


#define ADC_STOP_SEC_VAR_INIT_UNSPECIFIED
/**
 * @violates @ref Adc_Cfg_c_REF_1 only preprocessor statements and comments before "#include"
 * @violates @ref Adc_Cfg_c_REF_2 Repeated include file Memmap.h
 */
#include "MemMap.h"

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

#endif  /* ADC_PRECOMPILE_SUPPORT */

#ifdef __cplusplus
}
#endif

/** @} */

