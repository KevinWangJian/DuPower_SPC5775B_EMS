/**
*   @file    Adc_CfgDefines.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Adc - Module configuration interface for Adc driver.
*   @details Contains the module configuration interface for Adc driver.
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

#ifndef ADC_CFG_DEFINES_H
#define ADC_CFG_DEFINES_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Adc_CfgDefines_h_REF_1
* Violates MISRA 2004 Advisory Rule 19.7,
* A function shall be used in preference to a function-like macro.
* Middle layer between AUTOSAR and hardware needs a way to map HLD
* functions to IPV functions.
*
* @section Adc_CfgDefines_h_REF_2
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated. 
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

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define ADC_VENDOR_ID_CFG_DEFINES                       43
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_AR_RELEASE_MAJOR_VERSION_CFG_DEFINES        4
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_AR_RELEASE_MINOR_VERSION_CFG_DEFINES        0
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define ADC_AR_RELEASE_REVISION_VERSION_CFG_DEFINES     3
#define ADC_SW_MAJOR_VERSION_CFG_DEFINES                1
#define ADC_SW_MINOR_VERSION_CFG_DEFINES                0
#define ADC_SW_PATCH_VERSION_CFG_DEFINES                1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/**
* @brief          ADC unit 0 available
*/
#define ADC_UNIT_0  0U

/**
* @brief          ADC unit 1 available
*/
#define ADC_UNIT_1  1U

/**
* @brief          ADC unit 2 available
*/
#define ADC_UNIT_2  2U

/**
* @brief          ADC unit 3 available
*/
#define ADC_UNIT_3  3U


/**
* @brief          MHT functionality not activated.
*/
#define ADC_MULTIPLE_HARDWARE_TRIGGERS      (STD_OFF)

/** 
* @brief           Adds/removes ((STD_ON)/(STD_OFF)) the services Adc_EnableHardwareTrigger() and Adc_DisableHardwareTrigger() from the code.
*/
#define ADC_HW_TRIGGER_API                  (STD_OFF)

/** 
* @brief           Set mode api enabled/disabled ((STD_ON)/(STD_OFF)).
*/
#define ADC_SET_MODE_API                    (STD_OFF)

/** 
* @brief           Enables or disables limit checking feature in the ADC driver.
*/
#define ADC_ENABLE_LIMIT_CHECK              (STD_OFF)

/** 
* @brief           Group notification mechanism is/isn't ((STD_ON)/(STD_OFF)) available at runtime.
*/
#define ADC_GRP_NOTIF_CAPABILITY            (STD_ON)

/** 
* @brief           Type of prioritization mechanism ADC_PRIORITY_HW, ADC_PRIORITY_HW_SW and ADC_PRIORITY_NONE.
*/
#define ADC_PRIORITY_HW                     0U
#define ADC_PRIORITY_HW_SW                  1U
#define ADC_PRIORITY_NONE                   2U

/** 
* @brief           Priority implementation.
*/
#define ADC_PRIORITY_IMPLEMENTATION         (ADC_PRIORITY_NONE)

/** 
* @brief           Type of alignment mechanism ADC_ALIGN_RIGHT, ADC_ALIGN_LEFT.
*/
#define ADC_ALIGN_RIGHT                     0U
#define ADC_ALIGN_LEFT                      1U

/** 
* @brief           Result Alignment.
*/
#define ADC_RESULT_ALIGNMENT                (ADC_ALIGN_RIGHT)

/** 
* @brief           Adc transfer type.
*/
#define ADC_DMA                             0U
#define ADC_INTERRUPT                       1U

/** 
* @brief         This is a timeout value which is used to wait till
*                  - the conversion is not aborted.
*                  - ADC hardware is not entered in power down state.
*                  - ADC hardware is not entered in idle state.
*/
#define ADC_TIMEOUT_COUNTER                 (0x0000ffffUL)

/** 
* @brief          Add/Remove One time setting of Conversion time regsisters from Init() function.
*/
#define ADC_SET_ADC_CONV_TIME_ONCE          (STD_OFF)

/** 
* @brief          CMR Register is not supported by hardware
*/
#define ADC_CMR_REGISTER_NOT_SUPPORTED

/**
* @brief           This is a timeout value which is used to wait till the
*                  conversions pending in the CBuffer are not completed.
*/
#define ADC_CFG_CONV_TIMEOUT                 (0xffffUL)


/** 
* @brief           Max number of hw units - is 4 on Cobra.
*/
#define ADC_MAX_HW_UNITS                          (4U)

/**
 * @brief   Define the number of maximum channels
 */
/* #define ADC_MAXIMUM_HW_CHANNELS                   (255U) */

/** 
* @brief           Add/Remove non autosar Adc_EnableChannel() and Adc_DisableChannel() api.
*/
#define ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API      (STD_OFF)

/** 
* @brief           Get injected conversion status api enabled/disabled (STD_ON/STD_OFF).
*/
#define ADC_GET_INJECTED_CONVERSION_STATUS_API    (STD_OFF)

/** 
* @brief          Add/remove ((STD_ON)/(STD_OFF)) the service Adc_SetChannel() from the code.
*/
#define ADC_SETCHANNEL_API                        (STD_OFF)

/** 
* @brief          Add/Remove non autosar Adc_SetClockMode().
*/
#define ADC_DUAL_CLOCK_MODE   (STD_OFF)

/**
 * @brief           Add/Remove non autosar Adc_ConfigureThreshold() api.
 */
#define ADC_ENABLE_CONFIGURE_THRESHOLD_NONAUTO_API      (STD_OFF)

/** 
* @brief          Add/remove ((STD_ON)/(STD_OFF)) the service Adc_Calibration() from the code.
*/
#define ADC_CALIBRATION         (STD_OFF)

/** 
* @brief          Add/remove ((STD_ON)/(STD_OFF)) the service Adc_SelfTest() from the code.
*/
#define ADC_SELF_TEST           (STD_OFF)

/**
* @brief  Switch to enable/disable the API for the PR-MCAL-3312, PR-MCAL-3313, PR-MCAL-3314, PR-MCAL-3315 and PR-MCAL-3316.
*/
#define ADC_CTUV2_ENABLE_TRIGGER_CONFIGURATION_APIS     (STD_OFF)

/** 
* @brief  Switch to enable/disable the API for the CPR-MCAL-726, CPR-MCAL-727, CPR-MCAL-728.
*/
#define ADC_ENABLE_CTU_CONTROL_MODE_API                 (STD_OFF)

/** 
* @brief  Switch to enable/disable the production error reporting.
*/
#define ADC_DISABLE_DEM_REPORT_ERROR_STATUS           (STD_ON)

#define ADC_USER_MODE_REG_PROT_ENABLED      (STD_OFF)

   
/** 
* @brief          Development error detection enabled/disabled ((STD_ON)/(STD_OFF)).
*/
#define ADC_DEV_ERROR_DETECT                (STD_OFF)

/** 
* @brief          Add/remove ((STD_ON)/(STD_OFF)) the service Adc_GetVersionInfo() from the code.
*/
#define ADC_VERSION_INFO_API                (STD_ON)

/** 
* @brief          Add/remove ((STD_ON)/(STD_OFF)) the service Adc_DeInit() from the code.
*/
#define ADC_DEINIT_API                      (STD_ON)

/** 
* @brief          Add/remove ((STD_ON)/(STD_OFF)) the services Adc_StartGroupConversion()and Adc_StopGroupConversion() from the code.
*/
#define ADC_ENABLE_START_STOP_GROUP_API     (STD_ON)

/** 
* @brief          Add/Remove the services Adc_ReadGroup() from the code.
*/
#define ADC_READ_GROUP_API                  (STD_ON)

/** 
* @brief          This switch is used to enable the hardware trigger non autosar API.
*/
#define ADC_ENABLE_CTUTRIG_NONAUTO_API       (STD_OFF)

/** 
* @brief           This switch is used to enable the queue.
*/
#define ADC_ENABLE_QUEUING                  (STD_ON)


/** 
* @brief           Maximum number of channels across all hardware units.
*/
#define ADC_MAX_CHANNEL_PER_HW_UNIT         27

/** 
* @brief           EQADC A symbolic name definition
*/
#define ADC_EQADC_A     (0U)

/** 
* @brief           EQADC B symbolic name definition.
*/
#define ADC_EQADC_B     (1U)

/**
* @brief          Maximum eQADC.
*/
#define ADC_EQADC_MAX_U8                     (2U)

/**
* @brief          max number of FIFO available on ADC.
*/
#define ADC_EQADC_MAX_FIFO_U8                (6U)

/**
* @brief          FIFOs in ADC.
*/
#define ADC_FIFO_0                           (0U)
#define ADC_FIFO_1                           (1U)
#define ADC_FIFO_2                           (2U)
#define ADC_FIFO_3                           (3U)
#define ADC_FIFO_4                           (4U)
#define ADC_FIFO_5                           (5U)

/**
* @brief          max number of command FIFOs available on ADC.
*/
#define ADC_MAX_COMMAND_FIFO_U8              (6U)

/**
* @brief          max number of result FIFOs available on ADC.
*/
#define ADC_MAX_RESULT_FIFO_U8               (6U)



/** 
* @brief           Enable/Disable the eQADC_A FIFO0.
*/
#define ADC_EQADC_A_FIFO0_ENABLED   (STD_ON)
/** 
* @brief           Enable/Disable the eQADC_A FIFO1.
*/
#define ADC_EQADC_A_FIFO1_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_A FIFO2.
*/
#define ADC_EQADC_A_FIFO2_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_A FIFO3.
*/
#define ADC_EQADC_A_FIFO3_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_A FIFO4.
*/
#define ADC_EQADC_A_FIFO4_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_A FIFO5.
*/
#define ADC_EQADC_A_FIFO5_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the CFIFO and RFIFO.
*/

#define ADC_EQADC_A_CFIFO_ENABLED   (STD_ON)
#define ADC_EQADC_A_RFIFO_ENABLED   (STD_ON)

/** 
* @brief           Enable/Disable the eQADC_B FIFO0.
*/
#define ADC_EQADC_B_FIFO0_ENABLED   (STD_ON)
/** 
* @brief           Enable/Disable the eQADC_B FIFO1.
*/
#define ADC_EQADC_B_FIFO1_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_B FIFO2.
*/
#define ADC_EQADC_B_FIFO2_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_B FIFO3.
*/
#define ADC_EQADC_B_FIFO3_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_B FIFO4.
*/
#define ADC_EQADC_B_FIFO4_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the eQADC_B FIFO5.
*/
#define ADC_EQADC_B_FIFO5_ENABLED   (STD_OFF)
/** 
* @brief           Enable/Disable the CFIFO and RFIFO.
*/

#define ADC_EQADC_B_CFIFO_ENABLED   (STD_ON)
#define ADC_EQADC_B_RFIFO_ENABLED   (STD_ON)

/** 
* @brief           Symbolic names of ADC Hardware units.
*/
#define  AdcHwUnit_0                      (0)
#define  AdcHwUnit_1                      (1)

/** 
* @brief           Software injected conversion use
*/
#define ADC_SOFTWARE_INJECTED_CONVERSIONS_USED          (STD_OFF)

/** 
* @brief           Hardware normal conversion use
*/
#define ADC_HARDWARE_NORMAL_CONVERSIONS_USED            (STD_OFF)

/** 
* @brief           ADC Hardware unit macro for register access.
*
* @violates @ref Adc_CfgDefines_h_REF_1 Use of function like macro.
*/
#define ADC_HW_UNITS(unit)                  (Adc_pCfgPtr->Misc.au8Adc_HwUnit[(unit)])

/**
* @brief          Adc channel id.
* @violates @ref Adc_CfgDefines_h_REF_1 Use of function like macro.
*/
#define ADC_ID_CHANNEL_U8(Id)            ((uint8)(Id))

/**
* @brief          macros to simplify access to structures.
* @details        Streaming number of samples
* @violates @ref Adc_CfgDefines_h_REF_1 Function-like macro defined
*/
#define ADC_STREAMING_NUM_SAMPLES(num)      ((Adc_StreamNumSampleType)(num))

/**
* @brief          Configured hardware unit of the group.
*/
#if (ADC_MAX_HW_UNITS == 1U)
/** @violates @ref Adc_CfgDefines_h_REF_1 Function-like macro defined */
  #define Adc_GroupUnit(group)              0U
#else
/** @violates @ref Adc_CfgDefines_h_REF_1 Function-like macro defined */
  #define Adc_GroupUnit(group)              (Adc_pCfgPtr->pGroups[(group)].HwUnit)
#endif /* (ADC_MAX_HW_UNITS == 1U) */

/**
* @brief          Adc group priority.
* @violates @ref Adc_CfgDefines_h_REF_1 Function-like macro defined
*/
#define ADC_GROUP_PRIORITY(Priority)        ((Adc_GroupPriorityType)(Priority))

/**
* @brief          Adc hardware trigger source configured for the group.
* @violates @ref Adc_CfgDefines_h_REF_1 Function-like macro defined
*/
#define Adc_GroupTriggerSource(group,pos)   (Adc_pCfgPtr->pGroups[(group)].pHwResource[(pos)])

#if (ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)
/**
* @brief          Adc priority assigned to the group.
* @violates @ref Adc_CfgDefines_h_REF_1 Function-like macro defined
*/
#define Adc_GroupPriority(group)          (Adc_pCfgPtr->pGroups[(group)].Priority)
#endif /* ((ADC_PRIORITY_IMPLEMENTATION != ADC_PRIORITY_NONE)) */

/**
* @brief          Maximum boundary for the Adc_QueueIndexType.
*/
#define ADC_QUEUE_INDEX_TYPE_MAXIMUM          (65535U)

/**
* @brief          Check for continuous channels in group is not needed
*/
#define ADC_SKIP_DMA_CONTINUOUS_CHECK

/**
 * @brief       Invalid EXT/TST <-> INT CH mapping
 */
#define ADC_NO_EXT_TEST_CH_MAPPING            (255U)

/** 
* @brief           CTU is not supported by hardware.
*/
#define ADC_ENABLE_CTU_CONTROL_MODE_API    (STD_OFF)


/** 
* @brief           max queue depth configured across all configset.
*/
#define ADC_QUEUE_MAX_DEPTH_MAX             (1U)

/** 
* @brief           max number of channels in one group across all configset.
*/
#define ADC_MAX_GROUP_CHANNELS              1U

/** 
* @brief           max number of groups configured across all configset.
*/
#define ADC_MAX_GROUPS                      33U

/** 
* @brief           Invalid group Id definition.
*/
#define ADC_INVALID_GROUPS_ID               (0xFFFFU)

/** 
* @brief           Defined to check the hardware triggered groups available in Hw Queue.
* @details         Defined to check the hardware triggered groups available in Hw Queue.
*/
#define ADC_HW_QUEUE                        (1U)

/** 
* @brief           AUTOSAR Symbolic names of channels on all HW units.
*/

#define AD_BAT_24_IN                       0
#define AD_Global_H_4_CS                       0
#define AD_V_K22_IN                       1
#define AD_Global_H_3_CS                       1
#define AD_V_KA5_IN                       2
#define AD_Global_H_2_CS                       2
#define IA_TEMP_2                       3
#define AD_Global_H_5_CS                       3
#define IA_TEMP_3                       4
#define AD_Global_H_1_CS                       4
#define IA_TEMP_1                       5
#define SBC_MUX_OUT                       5
#define IA_TEMP_6                       6
#define IA_TEMP_5                       7
#define IA_TEMP_4                       8
#define AD_AC_CP                       9
#define IA_TEMP_10                       10
#define IA_TEMP_9                       11
#define IA_TEMP_8                       12
#define AC_CC_IN                       13
#define HV_ISO_AD                       14
#define IA_RES_AD3                       15
#define IA_RES_AD2                       16
#define IA_RES_AD1                       17
#define IA_RES_AD4                       18
#define IA_RES_AD5                       19
#define IA_RES_AD6                       20
#define HSD1_12V_Multisense                       21
#define HSD2_12V_Multisense                       22
#define LED_OUTPUT_Multisense                       23
#define AD_Power_12V_IN                       24
#define IA_TEMP_7                       25
#define AD_Power_24V_IN                       26


/** 
* @brief           Symbolic names of groups.
*/

/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_BAT_24V_IN                       0
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_V_K22_IN                       1
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_V_KA5_IN                       2
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_2                       3
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_3                       4
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_1                       5
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_6                       6
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_5                       7
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_4                       8
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_AC_CP                       9
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_10                       10
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_9                       11
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_8                       12
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AC_CC_IN                       13
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_HV_ISO_AD                       14
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_RES_AD3                       15
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_RES_AD2                       16
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_RES_AD1                       17
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_RES_AD4                       18
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_RES_AD5                       19
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_RES_AD6                       20
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_HSD1_12V_Multisense                       21
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_HSD2_12V_Multisense                       22
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_LED_OUTPUT_Multisense                       23
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_Global_H_4_CS                       24
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_Global_H_3_CS                       25
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_Global_H_2_CS                       26
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_Global_H_5_CS                       27
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_Global_H_1_CS                       28
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_SBC_MUX_OUT                       29
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_Power_12V_IN                       30
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_IA_TEMP_7                       31
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcGroup_AD_Power_24V_IN                       32

/** 
* @brief           Symbolic names of groups - ecuc 2108 compliant.
*/

/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_BAT_24V_IN                       0
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_V_K22_IN                       1
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_V_KA5_IN                       2
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_2                       3
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_3                       4
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_1                       5
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_6                       6
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_5                       7
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_4                       8
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_AC_CP                       9
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_10                       10
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_9                       11
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_8                       12
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AC_CC_IN                       13
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_HV_ISO_AD                       14
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_RES_AD3                       15
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_RES_AD2                       16
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_RES_AD1                       17
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_RES_AD4                       18
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_RES_AD5                       19
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_RES_AD6                       20
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_HSD1_12V_Multisense                       21
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_HSD2_12V_Multisense                       22
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_LED_OUTPUT_Multisense                       23
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_Global_H_4_CS                       24
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_Global_H_3_CS                       25
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_Global_H_2_CS                       26
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_Global_H_5_CS                       27
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_Global_H_1_CS                       28
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_SBC_MUX_OUT                       29
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_Power_12V_IN                       30
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_IA_TEMP_7                       31
/** @violates @ref Adc_CfgDefines_h_REF_2 MISRA-C:2004 Rule 1.4: Identifier clash.*/
#define AdcConf_AdcGroup_AdcGroup_AD_Power_24V_IN                       32

/** 
* @brief           Number of channels in respective groups.
*/

#define ADC_CFGSET1_GROUP_0_CHANNELS      1
#define ADC_CFGSET1_GROUP_1_CHANNELS      1
#define ADC_CFGSET1_GROUP_2_CHANNELS      1
#define ADC_CFGSET1_GROUP_3_CHANNELS      1
#define ADC_CFGSET1_GROUP_4_CHANNELS      1
#define ADC_CFGSET1_GROUP_5_CHANNELS      1
#define ADC_CFGSET1_GROUP_6_CHANNELS      1
#define ADC_CFGSET1_GROUP_7_CHANNELS      1
#define ADC_CFGSET1_GROUP_8_CHANNELS      1
#define ADC_CFGSET1_GROUP_9_CHANNELS      1
#define ADC_CFGSET1_GROUP_10_CHANNELS      1
#define ADC_CFGSET1_GROUP_11_CHANNELS      1
#define ADC_CFGSET1_GROUP_12_CHANNELS      1
#define ADC_CFGSET1_GROUP_13_CHANNELS      1
#define ADC_CFGSET1_GROUP_14_CHANNELS      1
#define ADC_CFGSET1_GROUP_15_CHANNELS      1
#define ADC_CFGSET1_GROUP_16_CHANNELS      1
#define ADC_CFGSET1_GROUP_17_CHANNELS      1
#define ADC_CFGSET1_GROUP_18_CHANNELS      1
#define ADC_CFGSET1_GROUP_19_CHANNELS      1
#define ADC_CFGSET1_GROUP_20_CHANNELS      1
#define ADC_CFGSET1_GROUP_21_CHANNELS      1
#define ADC_CFGSET1_GROUP_22_CHANNELS      1
#define ADC_CFGSET1_GROUP_23_CHANNELS      1
#define ADC_CFGSET1_GROUP_24_CHANNELS      1
#define ADC_CFGSET1_GROUP_25_CHANNELS      1
#define ADC_CFGSET1_GROUP_26_CHANNELS      1
#define ADC_CFGSET1_GROUP_27_CHANNELS      1
#define ADC_CFGSET1_GROUP_28_CHANNELS      1
#define ADC_CFGSET1_GROUP_29_CHANNELS      1
#define ADC_CFGSET1_GROUP_30_CHANNELS      1
#define ADC_CFGSET1_GROUP_31_CHANNELS      1
#define ADC_CFGSET1_GROUP_32_CHANNELS      1

/** 
* @brief           Adc non autosar Enable/Disable invalid group index.
*/
#if (ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON)
#define ADC_ENABLE_CH_DISABLE_CH_INVALID_GROUP_INDEX   ((Adc_GroupType)0xFFFF)
#endif /* ADC_ENABLE_CH_DISABLE_CH_NONAUTO_API == STD_ON */

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

#endif /* ADC_CFG_DEFINES_H */

/** @} */
