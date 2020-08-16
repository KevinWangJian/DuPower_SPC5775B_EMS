/**
*   @file       Pwm_PBcfg.c
*   @implements Pwm_PBcfg.c_Artifact
*   @version    1.0.1
*
*   @brief      AUTOSAR Pwm - Pwm post-build configuration file.
*   @details    Post-build configuration structure instances.
*
*   @addtogroup PWM_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : eMios
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
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Pwm_PBcfg_C_REF_1
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to
* prevent the contents of a header file being included twice. All header files are
* protected against multiple inclusions.
*
* @section Pwm_PBcfg_C_REF_2
* Violates MISRA 2004 Required Rule 8.10, external ... could be made static
* The respective code could not be made static because of layers architecture design of the driver.
* 
* @section Pwm_PBcfg_C_REF_3
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before "#include". This violation  is not  fixed since  the inclusion  of MemMap.h
* is as  per Autosar  requirement MEMMAP003.
* 
* @section Pwm_PBcfg_C_REF_4
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not 
* rely on the significance of more than 31 characters.
* This is not a violation since all the compilers used interpret the identifiers correctly.*
*
* @section Pwm_PBcfg_C_REF_5
* Violates MISRA 2004 Required Rule 16.9, A function identifier shall only be used with either 
* preceing &, or with a paranhesised parameter list which may be empty.
*
* @section Pwm_PBcfg_C_REF_6
* Violates MISRA 2004 Required Rule 12.8, The right-hand operand of a shift operator shall lie 
* between zero and one less than the width in bits of the underlying type of the left-hand operand.
*
*
*/

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Pwm.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @{
* @file           Pwm_PBcfg.c
*/

#define PWM_PB_CFG_VENDOR_ID_C                      43
#define PWM_PB_CFG_MODULE_ID_C                      121
/* @violates @ref Pwm_PBcfg_C_REF_4 Identifier exceeds 31 chars. */
#define PWM_PB_CFG_AR_RELEASE_MAJOR_VERSION_C       4
/* @violates @ref Pwm_PBcfg_C_REF_4 Identifier exceeds 31 chars. */
#define PWM_PB_CFG_AR_RELEASE_MINOR_VERSION_C       0
/* @violates @ref Pwm_PBcfg_C_REF_4 Identifier exceeds 31 chars. */
#define PWM_PB_CFG_AR_RELEASE_REVISION_VERSION_C    3

#define PWM_PB_CFG_SW_MAJOR_VERSION_C               1
#define PWM_PB_CFG_SW_MINOR_VERSION_C               0
#define PWM_PB_CFG_SW_PATCH_VERSION_C               1
/**@}*/

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#if (PWM_PB_CFG_VENDOR_ID_C != PWM_VENDOR_ID)
    #error "Pwm_PBcfg.c and Pwm.h have different vendor ids"
#endif

#if ((PWM_PB_CFG_AR_RELEASE_MAJOR_VERSION_C != PWM_AR_RELEASE_MAJOR_VERSION) || \
        (PWM_PB_CFG_AR_RELEASE_MINOR_VERSION_C != PWM_AR_RELEASE_MINOR_VERSION) || \
        (PWM_PB_CFG_AR_RELEASE_REVISION_VERSION_C != PWM_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Pwm_PBcfg.c and Pwm.h are different"
#endif

#if ((PWM_PB_CFG_SW_MAJOR_VERSION_C != PWM_SW_MAJOR_VERSION) || \
        (PWM_PB_CFG_SW_MINOR_VERSION_C != PWM_SW_MINOR_VERSION)  || \
        (PWM_PB_CFG_SW_PATCH_VERSION_C != PWM_SW_PATCH_VERSION))
    #error "Software Version Numbers of Pwm_PBcfg.c and Pwm.h are different"
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/
#if ( PWM_PRECOMPILE_SUPPORT == STD_OFF )

/* @violates @ref Pwm_PBcfg_C_REF_4 Identifier exceeds 31 chars. */
#define PWM_START_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Pwm_PBcfg_C_REF_1 MISRA 2004 Required Rule 19.15, precautions to prevent the 
*   contents of a header file being included twice.*/
#include "MemMap.h"


/** 
* @brief Number of configured Pwm channels 
*/
#define PWM_CONF_CHANNELS_PB_0            10

/** 
* @brief Number of configured EMIOS channels
*/
#define PWM_EMIOS_CONF_CHANNELS_PB_0      10


/* @brief Configurations for Pwm channels using EMIOS */
static CONST(Pwm_eMios_ChannelConfigType, PWM_CONST) Pwm_eMios_ChannelConfigPb0[PWM_EMIOS_CONF_CHANNELS_PB_0] =
{
    /* @brief PwmChannel_FAN4_CONTROL */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M0_C3,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_FAN3_CONTROL */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M0_C4,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_FAN2_CONTROL */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M0_C5,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_FAN1_CONTROL */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M0_C6,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_LED2_PWM_EN */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M1_C0,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_LED3_PWM_EN */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M1_C1,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_LED4_PWM_EN */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M1_C2,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_LED1_PWM_EN */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M1_C3,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_LED5_PWM_EN */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M1_C5,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    },
    /* @brief PwmChannel_LED6_PWM_EN */
    {
        /** @brief Pwm channel polarity */
        PWM_HIGH,
        /** @brief Pwm channel idle state */
        PWM_LOW,
        /** @brief Default duty cycle value */
        (uint16)0x4000,
        /** @brief Default period value500.0 */
        (Pwm_PeriodType)500.0,
        /** @brief EMIOS HW Module and Channel used by the Pwm channel */
        PWM_EMIOS_M1_C7,
        /* @brief EMIOS channel configuration parameters */
        /* @violates @ref Pwm_PBcfg_C_REF_6 The right-hand operand of a shift operator shall. */
        (Pwm_eMios_ControlType)(PWM_BUS_INTERNAL_COUNTER_U32 | PWM_MODE_OPWFMB_U32  | (PWM_PRES_4_U32)),
        (Pwm_PeriodType)0,/* leading edge of the PWM output pulse in OPWMB, OPWMT modes */
        (uint8)0,
        #if (PWM_FEATURE_DAOC == STD_ON)
        (Pwm_PeriodType)0,/* only use for DAOC mode */
        #endif
        #if (PWM_FEATURE_OPWMT == STD_ON)
        (Pwm_PeriodType)0,/* delay for generating the trigger event in OPWMT mode */
        #endif
        #if (PWM_FEATURE_OPWMCB == STD_ON)
        (uint16)0,/*deadtime parameter */
        #endif
        (boolean)FALSE/* Pwm_Offset and Pwm_TriggerDelay adjusted during runtime */
    }
};

/**
@brief EMIOS IP configuration
*/
static CONST(Pwm_eMios_IpConfigType, PWM_CONST) Pwm_eMios_IpConfigPb0 =
{
    /** @brief Number of EMIOS channels in the Pwm configuration */
    (uint8)10,
    /** @brief Pointer to the array of EMIOS enabled Pwm channel configurations */
    &Pwm_eMios_ChannelConfigPb0
};


/* @brief Array of configured Pwm channels */
static CONST(Pwm_ChannelConfigType, PWM_CONST) Pwm_ChannelsPb0[PWM_CONF_CHANNELS_PB_0] =
{
    /* @brief PwmChannel_FAN4_CONTROL */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_FAN3_CONTROL */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_FAN2_CONTROL */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_FAN1_CONTROL */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_LED2_PWM_EN */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_LED3_PWM_EN */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_LED4_PWM_EN */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_LED1_PWM_EN */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_LED5_PWM_EN */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    },
    /* @brief PwmChannel_LED6_PWM_EN */
    {
        /* @brief Channel class: Variable/Fixed/Fixed_Shifted period */
        PWM_FIXED_PERIOD,
#if (PWM_NOTIFICATION_SUPPORTED == STD_ON)
        /** @brief Pwm notification function */
        NULL_PTR
#endif
    }
};

/**
@brief   Pwm channels IP related configuration array
*/
static CONST(Pwm_IpChannelConfigType, PWM_CONST) Pwm_IpChannelConfigPb0[PWM_CONF_CHANNELS_PB_0] =
{
    /** @brief PwmChannel_FAN4_CONTROL */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)0,
    },
    /** @brief PwmChannel_FAN3_CONTROL */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)1,
    },
    /** @brief PwmChannel_FAN2_CONTROL */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)2,
    },
    /** @brief PwmChannel_FAN1_CONTROL */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)3,
    },
    /** @brief PwmChannel_LED2_PWM_EN */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)4,
    },
    /** @brief PwmChannel_LED3_PWM_EN */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)5,
    },
    /** @brief PwmChannel_LED4_PWM_EN */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)6,
    },
    /** @brief PwmChannel_LED1_PWM_EN */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)7,
    },
    /** @brief PwmChannel_LED5_PWM_EN */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)8,
    },
    /** @brief PwmChannel_LED6_PWM_EN */
    {
        /* @brief Index in the configuration table of the EMIOS channels */
        (uint8)9,
    }
};

/**
@brief   Pwm high level configuration structure
*/
/*
* @violates @ref Pwm_PBcfg_C_REF_2 external ... could be made static
*/
CONST(Pwm_ConfigType, PWM_CONST) PwmChannelConfigSet_0 =
{
    /** @brief Number of configured Pwm channels */
    (Pwm_ChannelType)PWM_CONF_CHANNELS_PB_0,
    /** @brief Pointer to array of Pwm channels */
    &Pwm_ChannelsPb0,
    /** @brief IP specific configuration */
    {
        /* @brief Pointer to the structure containing EMIOS configuration */
        &Pwm_eMios_IpConfigPb0,
        /* @brief Pointer to Array containing channe IP related information */
        &Pwm_IpChannelConfigPb0
    }
#if ((PWM_NOTIFICATION_SUPPORTED == STD_ON) || (PWM_FEATURE_DAOC == STD_ON))
    ,
    /** @brief Hw to logic channel map. Array containing a number of elements
    equal to total number of available channels on EMIOS IPV */
    {
        /* Idx of channels 0-31 of eMios Module 0 in the array of logic Pwm channels */
        (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)0, (Pwm_ChannelType)1, (Pwm_ChannelType)2, (Pwm_ChannelType)3, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255,
        /* Idx of channels 0-31 of eMios Module 1 in the array of logic Pwm channels */
        (Pwm_ChannelType)4, (Pwm_ChannelType)5, (Pwm_ChannelType)6, (Pwm_ChannelType)7, (Pwm_ChannelType)255, (Pwm_ChannelType)8, (Pwm_ChannelType)255, (Pwm_ChannelType)9, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255, (Pwm_ChannelType)255
    }
#endif /* (PWM_NOTIFICATION_SUPPORTED == STD_ON) */  
};

/* @violates @ref Pwm_PBcfg_C_REF_4 Identifier exceeds 31 chars. */
#define PWM_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/** @violates @ref Pwm_PBcfg_C_REF_1 MISRA 2004 Required Rule 19.15, precautions to prevent the 
*   contents of a header file being included twice.*/
/*
* @violates @ref Pwm_PBcfg_C_REF_3 #include statements in a file should
* only be preceded by other preprocessor directives or comments.
*/
#include "MemMap.h"

#endif  /* PWM_PRECOMPILE_SUPPORT*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                        LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/


#ifdef __cplusplus
}
#endif

/** @} */

