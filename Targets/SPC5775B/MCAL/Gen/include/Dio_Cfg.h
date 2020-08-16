/**
*   @file    Dio_Cfg.h
*   @implements Dio_Cfg.h_Artifact
*
*   @version 1.0.1
*
*   @brief   AUTOSAR Dio configuration header.
*   @details This file is the Autosar DIO driver configuration header. This
*            file is automatically generated, do not modify manually.
*
*   @addtogroup DIO_CFG
*   @{
*/
/*=================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : SIU
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
=================================================================================================*/
/*=================================================================================================
=================================================================================================*/

#ifndef DIO_CFG_H
#define DIO_CFG_H

#ifdef __cplusplus
extern "C" {
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Dio_Cfg_H_REF_1
*          Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
*          that 31 character significance and case sensitivity are supported for external identifiers. 
*          The used compilers/linkers allow more than 31 characters significance for external identifiers. 
* 
* @section Dio_Cfg_H_REF_2
*          Violates MISRA 2004 Required Rule 19.15, Repeated include file, 
*          Precautions shall be taken in order to prevent the contents of a header file 
*          being included twice. This violation is not fixed since the inclusion of MemMap.h is as per 
*          Autosar requirement MEMMAP003.
*
* @section Dio_Cfg_H_REF_3
*          Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope 
*          if they are only accessed from within a single function. 
*          These objects are used in various parts of the code.
*
* @section [global]
*          Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not
*          rely on the significance of more than 31 characters. The used compilers use more than
*          31 chars for identifiers.
**/


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Dio_EnvCfg.h"


/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_VENDOR_ID_CFG                   43
#define DIO_AR_RELEASE_MAJOR_VERSION_CFG    4
#define DIO_AR_RELEASE_MINOR_VERSION_CFG    0
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define DIO_AR_RELEASE_REVISION_VERSION_CFG 3
#define DIO_SW_MAJOR_VERSION_CFG            1
#define DIO_SW_MINOR_VERSION_CFG            0
#define DIO_SW_PATCH_VERSION_CFG            1

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/* Dio_EnvCfg.h version check start */
#if ((DIO_AR_RELEASE_MAJOR_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_MAJOR_VERSION) ||   \
     (DIO_AR_RELEASE_MINOR_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_MINOR_VERSION) ||   \
     (DIO_AR_RELEASE_REVISION_VERSION_CFG != DIO_ENVCFG_AR_RELEASE_REVISION_VERSION)\
    )
    #error "AUTOSAR Version Numbers of Dio_Cfg.h and Dio_EnvCfg.h are different"
#endif

#if ((DIO_SW_MAJOR_VERSION_CFG != DIO_ENVCFG_SW_MAJOR_VERSION) || \
     (DIO_SW_MINOR_VERSION_CFG != DIO_ENVCFG_SW_MINOR_VERSION) || \
     (DIO_SW_PATCH_VERSION_CFG != DIO_ENVCFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Dio_Cfg.h and Dio_EnvCfg.h are different"
#endif

#if ((DIO_VENDOR_ID_CFG != DIO_ENVCFG_VENDOR_ID))
    #error "VENDOR ID for Dio_Cfg.h and Dio_EnvCfg.h is different"
#endif
/* Dio_EnvCfg.h version check end */
/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

/**
* @brief          Enable or Disable Development Error Detection.
*
* @implements     DIO_DEV_ERROR_DETECT_define
* @api
*/
#define DIO_DEV_ERROR_DETECT    (STD_ON)

/**
* @brief          Function @p Dio_GetVersionInfo() enable switch.
*
* @implements DIO_VERSION_INFO_API_define
* @api
*/
#define DIO_VERSION_INFO_API    (STD_ON)

/**
* @brief          Function @p Dio_FlipChannel() enable switch.
*
* @api
*/
#define DIO_FLIP_CHANNEL_API    (STD_ON)

/**
* @brief          Function @p Dio_MaskedWritePort() enable switch.
*
* @api
*/
#define DIO_MASKEDWRITEPORT_API (STD_OFF)

/**
* @brief          Reversed port functionality enable switch.
*
* @implements DIO_REVERSEPORTBITS_define
* @api
*/
#define DIO_REVERSEPORTBITS     (STD_OFF)

/**
* @brief          Undefined pins masking enable switch.
*
* @api
*/
#define DIO_READZERO_UNDEFINEDPORTS (STD_OFF)


/**
* @brief          Number of implemented ports.
*
* @note           Used for channel, port and channel group validation.
*
* @api
*/
#define DIO_NUM_PORTS_U16               ((uint16)0x1f)

/**
* @brief          Number of channels in a port.
*
* @note           Used for channel, port and channel group validation.
*
* @api
*/
#define DIO_NUM_CHANNELS_PER_PORT_U16   ((uint16)(sizeof(Dio_PortLevelType) * 0x8U))

/**
* @brief          Number of channels available on the implemented ports.
*
* @note           Used for channel validation.
*
* @api
*/
#define DIO_NUM_CHANNELS_U16            ((uint16)(DIO_NUM_PORTS_U16 * DIO_NUM_CHANNELS_PER_PORT_U16))

/**
* @brief          Mask representing no available channels on a port.
*
* @note           Used for channel validation.
*
* @api
*/
#define DIO_NO_AVAILABLE_CHANNELS_U16   ((Dio_PortLevelType)0x0U)

/**
* @brief          Mask representing the maximum valid offset for a channel group.
*
* @note           Used for channel group validation.
*
* @api
*/
#define DIO_MAX_VALID_OFFSET_U8 ((uint8)0xFU)

/**
*   @brief   Enables or disables the access to a hardware register from user mode
*            USER_MODE_SOFT_LOCKING:        All reads to hw registers will be done via REG_PROT, user mode access
*            SUPERVISOR_MODE_SOFT_LOCKING:  Locks the access to the registers only for supervisor mode
*
*   @note    Currently, no register protection mechanism is used for Dio driver.
*/
#define DIO_USER_MODE_SOFT_LOCKING      (STD_OFF)

/**
* @brief          Dio driver Pre-Compile configuration switch.
*
* @api
*/
#define DIO_PRECOMPILE_SUPPORT


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/**
* @brief          Symbolic name for the configuration Dio_ConfigPC.
*
*/
#define Dio_ConfigPC    (DioConfig_0)  

/* ========== DioConfig_0 ========== */

/* ---------- PORTC_L ---------- */

/**
* @brief          Symbolic name for the port PORTC_L.
*
*/
#define DioConf_DioPort_PORTC_L  ((uint8)0x04U)

/**
* @brief          Symbolic name for the channel DCDC_11V5_DISABLE.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_DCDC_11V5_DISABLE ((uint16)0x004bU)

/**
* @brief          Symbolic name for the channel AUX_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AUX_EN ((uint16)0x004cU)

/**
* @brief          Symbolic name for the channel TJA1101_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1101_EN ((uint16)0x004dU)

/**
* @brief          Symbolic name for the channel TJA1101_RESET.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1101_RESET ((uint16)0x004eU)

/**
* @brief          Symbolic name for the channel TJA1101_WAKEUP.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1101_WAKEUP ((uint16)0x004fU)

/* ---------- PORTC_H ---------- */

/**
* @brief          Symbolic name for the port PORTC_H.
*
*/
#define DioConf_DioPort_PORTC_H  ((uint8)0x05U)

/**
* @brief          Symbolic name for the channel DP83822HF_1_RESET.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_DP83822HF_1_RESET ((uint16)0x0050U)

/**
* @brief          Symbolic name for the channel DP83822HF_1_INT.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_DP83822HF_1_INT ((uint16)0x0051U)

/**
* @brief          Symbolic name for the channel TJA1101_INT.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1101_INT ((uint16)0x0052U)

/* ---------- PORTD_L ---------- */

/**
* @brief          Symbolic name for the port PORTD_L.
*
*/
#define DioConf_DioPort_PORTD_L  ((uint8)0x06U)

/**
* @brief          Symbolic name for the channel SJA1105_RESET.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SJA1105_RESET ((uint16)0x0061U)

/**
* @brief          Symbolic name for the channel SN6501_1_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SN6501_1_EN ((uint16)0x006aU)

/* ---------- PORTD_H ---------- */

/**
* @brief          Symbolic name for the port PORTD_H.
*
*/
#define DioConf_DioPort_PORTD_H  ((uint8)0x07U)

/**
* @brief          Symbolic name for the channel AD_QF2_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_QF2_AUX_IN ((uint16)0x0072U)

/**
* @brief          Symbolic name for the channel AD_K5_K6_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_K5_K6_AUX_IN ((uint16)0x0073U)

/**
* @brief          Symbolic name for the channel AD_K11_K12_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_K11_K12_AUX_IN ((uint16)0x0074U)

/**
* @brief          Symbolic name for the channel AD_QF1_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_QF1_AUX_IN ((uint16)0x0076U)

/**
* @brief          Symbolic name for the channel AD_CB5_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_CB5_AUX_IN ((uint16)0x0077U)

/**
* @brief          Symbolic name for the channel AD_K9_K10_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_K9_K10_AUX_IN ((uint16)0x0078U)

/**
* @brief          Symbolic name for the channel AC_CP_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AC_CP_EN ((uint16)0x0079U)

/**
* @brief          Symbolic name for the channel AD_Door_CON_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_Door_CON_AUX_IN ((uint16)0x007aU)

/**
* @brief          Symbolic name for the channel AD_QF3_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_QF3_AUX_IN ((uint16)0x007bU)

/**
* @brief          Symbolic name for the channel AD_KM2_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_KM2_AUX_IN ((uint16)0x007cU)

/**
* @brief          Symbolic name for the channel AD_Water_TS_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_Water_TS_AUX_IN ((uint16)0x007eU)

/**
* @brief          Symbolic name for the channel AD_KM1_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_KM1_AUX_IN ((uint16)0x007fU)

/* ---------- PORTE_L ---------- */

/**
* @brief          Symbolic name for the port PORTE_L.
*
*/
#define DioConf_DioPort_PORTE_L  ((uint8)0x08U)

/**
* @brief          Symbolic name for the channel AD_RES1_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_RES1_AUX_IN ((uint16)0x0080U)

/**
* @brief          Symbolic name for the channel AD_FVC1_CB1_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_FVC1_CB1_IN ((uint16)0x0081U)

/**
* @brief          Symbolic name for the channel AD_RES3_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_RES3_AUX_IN ((uint16)0x0082U)

/**
* @brief          Symbolic name for the channel AD_RES2_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_RES2_AUX_IN ((uint16)0x0083U)

/**
* @brief          Symbolic name for the channel AD_Smoke_Alarm_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_Smoke_Alarm_AUX_IN ((uint16)0x0084U)

/**
* @brief          Symbolic name for the channel LED1_DRIVE_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_LED1_DRIVE_EN ((uint16)0x0085U)

/**
* @brief          Symbolic name for the channel LED2_DRIVE_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_LED2_DRIVE_EN ((uint16)0x0086U)

/**
* @brief          Symbolic name for the channel AD_EMG_STOP_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_EMG_STOP_AUX_IN ((uint16)0x0087U)

/**
* @brief          Symbolic name for the channel Chasis_GND_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Chasis_GND_EN ((uint16)0x0089U)

/**
* @brief          Symbolic name for the channel ISO_SAMPLE_P_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ISO_SAMPLE_P_EN ((uint16)0x008aU)

/**
* @brief          Symbolic name for the channel ISO_SAMPLE_N_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ISO_SAMPLE_N_EN ((uint16)0x008bU)

/**
* @brief          Symbolic name for the channel ISO_SAMPLE_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_ISO_SAMPLE_EN ((uint16)0x008cU)

/* ---------- PORTE_H ---------- */

/**
* @brief          Symbolic name for the port PORTE_H.
*
*/
#define DioConf_DioPort_PORTE_H  ((uint8)0x09U)

/**
* @brief          Symbolic name for the channel AD_BAT_24V_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_BAT_24V_EN ((uint16)0x0090U)

/**
* @brief          Symbolic name for the channel SN6501_2_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_SN6501_2_EN ((uint16)0x0091U)

/**
* @brief          Symbolic name for the channel K16_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K16_LSD_EN ((uint16)0x0092U)

/**
* @brief          Symbolic name for the channel K14_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K14_LSD_EN ((uint16)0x0093U)

/**
* @brief          Symbolic name for the channel K15_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K15_LSD_EN ((uint16)0x0094U)

/**
* @brief          Symbolic name for the channel K13_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K13_LSD_EN ((uint16)0x0095U)

/**
* @brief          Symbolic name for the channel IN_MUX_2.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_IN_MUX_2 ((uint16)0x0096U)

/**
* @brief          Symbolic name for the channel IN_MUX_1.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_IN_MUX_1 ((uint16)0x0097U)

/**
* @brief          Symbolic name for the channel OUT_MUX1_A.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_OUT_MUX1_A ((uint16)0x0098U)

/**
* @brief          Symbolic name for the channel OUT_MUX1_B.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_OUT_MUX1_B ((uint16)0x0099U)

/**
* @brief          Symbolic name for the channel OUT_MUX2_C.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_OUT_MUX2_C ((uint16)0x009aU)

/**
* @brief          Symbolic name for the channel OUT_MUX2_B.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_OUT_MUX2_B ((uint16)0x009bU)

/**
* @brief          Symbolic name for the channel OUT_MUX2_A.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_OUT_MUX2_A ((uint16)0x009cU)

/**
* @brief          Symbolic name for the channel OUT_MUX1_C.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_OUT_MUX1_C ((uint16)0x009dU)

/**
* @brief          Symbolic name for the channel Global_H_2_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_2_EN ((uint16)0x009eU)

/**
* @brief          Symbolic name for the channel Global_H_1_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_1_EN ((uint16)0x009fU)

/* ---------- PORTF_L ---------- */

/**
* @brief          Symbolic name for the port PORTF_L.
*
*/
#define DioConf_DioPort_PORTF_L  ((uint8)0x0aU)

/**
* @brief          Symbolic name for the channel Global_H_4_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_4_EN ((uint16)0x00a0U)

/**
* @brief          Symbolic name for the channel Global_H_5_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_5_EN ((uint16)0x00a1U)

/**
* @brief          Symbolic name for the channel Global_H_3_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_3_EN ((uint16)0x00a2U)

/**
* @brief          Symbolic name for the channel K24_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K24_LSD_EN ((uint16)0x00a3U)

/**
* @brief          Symbolic name for the channel RES1_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RES1_LSD_EN ((uint16)0x00a4U)

/**
* @brief          Symbolic name for the channel K11_K12_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K11_K12_LSD_EN ((uint16)0x00a5U)

/**
* @brief          Symbolic name for the channel K23_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K23_LSD_EN ((uint16)0x00a6U)

/**
* @brief          Symbolic name for the channel K9_K10_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K9_K10_LSD_EN ((uint16)0x00a7U)

/**
* @brief          Symbolic name for the channel K5_K6_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K5_K6_LSD_EN ((uint16)0x00a8U)

/**
* @brief          Symbolic name for the channel CB5_IN_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CB5_IN_EN ((uint16)0x00a9U)

/**
* @brief          Symbolic name for the channel K21_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K21_LSD_EN ((uint16)0x00aaU)

/**
* @brief          Symbolic name for the channel QF1_IN_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_QF1_IN_EN ((uint16)0x00abU)

/**
* @brief          Symbolic name for the channel QF2_IN_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_QF2_IN_EN ((uint16)0x00acU)

/**
* @brief          Symbolic name for the channel K7_K8_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K7_K8_LSD_EN ((uint16)0x00adU)

/**
* @brief          Symbolic name for the channel K22_LSD_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K22_LSD_EN ((uint16)0x00aeU)

/**
* @brief          Symbolic name for the channel QF3_IN_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_QF3_IN_EN ((uint16)0x00afU)

/* ---------- PORTF_H ---------- */

/**
* @brief          Symbolic name for the port PORTF_H.
*
*/
#define DioConf_DioPort_PORTF_H  ((uint8)0x0bU)

/**
* @brief          Symbolic name for the channel TBOX_Wake_Up_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TBOX_Wake_Up_IN ((uint16)0x00b0U)

/**
* @brief          Symbolic name for the channel RES2_Wake_Up_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RES2_Wake_Up_IN ((uint16)0x00b1U)

/**
* @brief          Symbolic name for the channel EEPROM_WP.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_EEPROM_WP ((uint16)0x00b2U)

/**
* @brief          Symbolic name for the channel AD_K7_K8_AUX_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_K7_K8_AUX_IN ((uint16)0x00b3U)

/**
* @brief          Symbolic name for the channel AD_CB6_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_CB6_IN ((uint16)0x00b4U)

/**
* @brief          Symbolic name for the channel AD_FVC2_CB2_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_FVC2_CB2_IN ((uint16)0x00b5U)

/**
* @brief          Symbolic name for the channel LED_HSD_SENSE_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_LED_HSD_SENSE_EN ((uint16)0x00baU)

/**
* @brief          Symbolic name for the channel CCU_Wake_Up_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CCU_Wake_Up_EN ((uint16)0x00bfU)

/* ---------- PORTG_L ---------- */

/**
* @brief          Symbolic name for the port PORTG_L.
*
*/
#define DioConf_DioPort_PORTG_L  ((uint8)0x0cU)

/**
* @brief          Symbolic name for the channel HSD1_12V_SENSE_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_HSD1_12V_SENSE_EN ((uint16)0x00c1U)

/**
* @brief          Symbolic name for the channel BMS_Wake_Up_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_BMS_Wake_Up_EN ((uint16)0x00c5U)

/**
* @brief          Symbolic name for the channel HSD2_12V_SENSE_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_HSD2_12V_SENSE_EN ((uint16)0x00c6U)

/**
* @brief          Symbolic name for the channel RES1_HSD2_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RES1_HSD2_EN ((uint16)0x00c7U)

/**
* @brief          Symbolic name for the channel RES4_HSD2_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RES4_HSD2_EN ((uint16)0x00c8U)

/**
* @brief          Symbolic name for the channel RES2_HSD2_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RES2_HSD2_EN ((uint16)0x00c9U)

/**
* @brief          Symbolic name for the channel RES3_HSD2_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RES3_HSD2_EN ((uint16)0x00caU)

/**
* @brief          Symbolic name for the channel HSD_SENSE_SEL0.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_HSD_SENSE_SEL0 ((uint16)0x00cbU)

/**
* @brief          Symbolic name for the channel HSD_SENSE_SEL1.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_HSD_SENSE_SEL1 ((uint16)0x00ccU)

/* ---------- PORTG_H ---------- */

/**
* @brief          Symbolic name for the port PORTG_H.
*
*/
#define DioConf_DioPort_PORTG_H  ((uint8)0x0dU)

/**
* @brief          Symbolic name for the channel VCC_3V3_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_VCC_3V3_EN ((uint16)0x00deU)

/**
* @brief          Symbolic name for the channel CAN_5V0_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CAN_5V0_EN ((uint16)0x00dfU)

/* ---------- PORTH_L ---------- */

/**
* @brief          Symbolic name for the port PORTH_L.
*
*/
#define DioConf_DioPort_PORTH_L  ((uint8)0x0eU)

/**
* @brief          Symbolic name for the channel DP83822HF_2_RESET.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_DP83822HF_2_RESET ((uint16)0x00e7U)

/**
* @brief          Symbolic name for the channel DP83822HF_2_INT.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_DP83822HF_2_INT ((uint16)0x00e8U)

/**
* @brief          Symbolic name for the channel VCC_1V2_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_VCC_1V2_EN ((uint16)0x00e9U)

/**
* @brief          Symbolic name for the channel MCU_DSPI_C_PCA21125_CS.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MCU_DSPI_C_PCA21125_CS ((uint16)0x00eeU)

/**
* @brief          Symbolic name for the channel MCU_DSPI_C_EEPROM_CS.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MCU_DSPI_C_EEPROM_CS ((uint16)0x00efU)

/* ---------- PORTH_H ---------- */

/**
* @brief          Symbolic name for the port PORTH_H.
*
*/
#define DioConf_DioPort_PORTH_H  ((uint8)0x0fU)

/**
* @brief          Symbolic name for the channel MCU_eSCI_C_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MCU_eSCI_C_EN ((uint16)0x00f0U)

/**
* @brief          Symbolic name for the channel EEPROM_HOLD.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_EEPROM_HOLD ((uint16)0x00f1U)

/* ---------- PORTN_H ---------- */

/**
* @brief          Symbolic name for the port PORTN_H.
*
*/
#define DioConf_DioPort_PORTN_H  ((uint8)0x1bU)

/**
* @brief          Symbolic name for the channel AD_RES1_LSD_N.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_AD_RES1_LSD_N ((uint16)0x01b9U)

/**
* @brief          Symbolic name for the channel Global_H_2_FR.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_2_FR ((uint16)0x01baU)

/**
* @brief          Symbolic name for the channel Global_H_1_FR.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_1_FR ((uint16)0x01bbU)

/**
* @brief          Symbolic name for the channel Global_H_4_FR.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_4_FR ((uint16)0x01bcU)

/**
* @brief          Symbolic name for the channel Global_H_3_FR.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_3_FR ((uint16)0x01bdU)

/**
* @brief          Symbolic name for the channel Global_H_5_FR.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_Global_H_5_FR ((uint16)0x01beU)

/**
* @brief          Symbolic name for the channel K22_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K22_LSD_STATUS_IN ((uint16)0x01bfU)

/**
* @brief          Symbolic name for the channel HSD_SENSE_SEL2.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_HSD_SENSE_SEL2 ((uint16)0x01b0U)

/**
* @brief          Symbolic name for the channel TJA1044_STB.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1044_STB ((uint16)0x01b2U)

/**
* @brief          Symbolic name for the channel TJA1042_1_STB.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1042_1_STB ((uint16)0x01b3U)

/**
* @brief          Symbolic name for the channel TJA1042_2_STB.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1042_2_STB ((uint16)0x01b4U)

/**
* @brief          Symbolic name for the channel TJA1042_3_STB.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_TJA1042_3_STB ((uint16)0x01b5U)

/* ---------- PORTO_L ---------- */

/**
* @brief          Symbolic name for the port PORTO_L.
*
*/
#define DioConf_DioPort_PORTO_L  ((uint8)0x1cU)

/**
* @brief          Symbolic name for the channel K21_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K21_LSD_STATUS_IN ((uint16)0x01c0U)

/**
* @brief          Symbolic name for the channel QF3_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_QF3_LSD_STATUS_IN ((uint16)0x01c1U)

/**
* @brief          Symbolic name for the channel QF1_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_QF1_LSD_STATUS_IN ((uint16)0x01c2U)

/**
* @brief          Symbolic name for the channel QF2_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_QF2_LSD_STATUS_IN ((uint16)0x01c3U)

/**
* @brief          Symbolic name for the channel K7_K8_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K7_K8_STATUS_IN ((uint16)0x01c4U)

/**
* @brief          Symbolic name for the channel CB5_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_CB5_LSD_STATUS_IN ((uint16)0x01c5U)

/**
* @brief          Symbolic name for the channel K5_K6_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K5_K6_STATUS_IN ((uint16)0x01c6U)

/**
* @brief          Symbolic name for the channel K9_K10_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K9_K10_STATUS_IN ((uint16)0x01c7U)

/**
* @brief          Symbolic name for the channel K23_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K23_LSD_STATUS_IN ((uint16)0x01c8U)

/**
* @brief          Symbolic name for the channel K11_K12_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K11_K12_STATUS_IN ((uint16)0x01c9U)

/**
* @brief          Symbolic name for the channel K24_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K24_LSD_STATUS_IN ((uint16)0x01ccU)

/**
* @brief          Symbolic name for the channel RES1_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_RES1_LSD_STATUS_IN ((uint16)0x01cdU)

/* ---------- PORTO_H ---------- */

/**
* @brief          Symbolic name for the port PORTO_H.
*
*/
#define DioConf_DioPort_PORTO_H  ((uint8)0x1dU)

/**
* @brief          Symbolic name for the channel K14_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K14_LSD_STATUS_IN ((uint16)0x01d0U)

/**
* @brief          Symbolic name for the channel K15_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K15_LSD_STATUS_IN ((uint16)0x01d1U)

/**
* @brief          Symbolic name for the channel K16_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K16_LSD_STATUS_IN ((uint16)0x01d2U)

/**
* @brief          Symbolic name for the channel MCU_eSCI_B_EN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_MCU_eSCI_B_EN ((uint16)0x01d3U)

/**
* @brief          Symbolic name for the channel K13_LSD_STATUS_IN.
*
*/
/** @violates @ref Dio_Cfg_H_REF_1 The compiler/linker shall be checked to ensure that 31
    character significance and case sensitivity are supported for external identifiers. */
#define  DioConf_DioChannel_K13_LSD_STATUS_IN ((uint16)0x01d4U)

/*=================================================================================================
*                                             ENUMS
=================================================================================================*/

/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/**
* @brief          Type of a DIO port representation.
*
* @implements     Dio_PortType_typedef
*
* @api
*/
typedef uint8 Dio_PortType;

/**
* @brief          Type of a DIO channel representation.
*
* @implements     Dio_ChannelType_typedef
*
* @api
*/
typedef uint16 Dio_ChannelType;

/**
* @brief          Type of a DIO port levels representation.
*
* @implements     Dio_PortLevelType_typedef
*
* @api
*/
typedef uint16 Dio_PortLevelType;

/**
* @brief          Type of a DIO channel levels representation.
*
* @implements     Dio_LevelType_typedef
*
* @api
*/
typedef uint8 Dio_LevelType;

/**
* @brief          Type of a DIO channel group representation.
*
* @implements     Dio_ChannelGroupType_struct
*
* @api
*/
typedef struct
{
    VAR(Dio_PortType, AUTOMATIC)      port;      /**< @brief Port identifier.  */
    VAR(uint8, AUTOMATIC)             offset;    /**< @brief Bit offset within the port. */
    VAR(Dio_PortLevelType, AUTOMATIC) mask;      /**< @brief Group mask. */
} Dio_ChannelGroupType;

/**
* @brief          Type of a DIO configuration structure.
*
* @note           In this implementation there is no need for a configuration
*                 structure there is only a dummy field, it is recommended
*                 to initialize this field to zero.
*
* @implements     Dio_ConfigType_struct
*
* @api
*/
typedef struct
{                                                                       
    VAR(uint8, AUTOMATIC) u8NumChannelGroups; /**< @brief Number of channel groups in configuration */
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupList;  /**< @brief 
                                               Pointer to list of channel groups in configuration */
} Dio_ConfigType;

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/

#define DIO_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Dio_Cfg_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

/**
* @brief Array of bitmaps of output pins available per port
*/
/** @violates @ref Dio_Cfg_H_REF_3 Objects shall be defined at block scope if they are only accessed
    from within a single function. */
extern CONST(Dio_PortLevelType, DIO_CONST) Dio_aAvailablePinsForWrite[DIO_NUM_PORTS_U16];

/**
* @brief Array of bitmaps of input pins available per port
*/
/** @violates @ref Dio_Cfg_H_REF_3 Objects shall be defined at block scope if they are only accessed
    from within a single function. */
extern CONST(Dio_PortLevelType, DIO_CONST) Dio_aAvailablePinsForRead[DIO_NUM_PORTS_U16];

/**
* @brief          List of channel groups in configuration DioConfig_0.
*/


#define DIO_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref Dio_Cfg_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif  /* DIO_CFG_H */

/** @} */
