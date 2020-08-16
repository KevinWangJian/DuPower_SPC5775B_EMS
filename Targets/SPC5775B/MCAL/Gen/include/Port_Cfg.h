/**
* @file    Port_Cfg.h
* @implements Port_Cfg.h_Artifact
*
* @version 1.0.1
* @brief   AUTOSAR Port - PORT driver configuration.
* @details This file contains the PORT driver precompile configuration.
*
* @addtogroup Port
* @{
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


#ifndef PORT_CFG_H
#define PORT_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section PORT_CFG_H_REF_1
* Violates MISRA 2004 Required Rule 1.4, The compiler/linkershall be checked to ensure 
* that 31 character significance and case sensitivity are supported for external 
* identifiers. The used compilers/linkers allow more than 31 characters significance for external identifiers.
*
* @section PORT_CFG_H_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section PORT_CFG_H_REF_3
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section PORT_CFG_H_REF_4
* Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are only
* accessed from within a single function.
* These objects are used in various parts of the code.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Port_EnvCfg.h"
#include "Port_Siu_Types.h"
#include "Port_Igf_Types.h"


/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
* @details The integration of incompatible files shall be avoided.
*/
#define PORT_VENDOR_ID_CFG_H                       43
#define PORT_AR_RELEASE_MAJOR_VERSION_CFG_H        4
#define PORT_AR_RELEASE_MINOR_VERSION_CFG_H        0
#define PORT_AR_RELEASE_REVISION_VERSION_CFG_H     3
#define PORT_SW_MAJOR_VERSION_CFG_H                1
#define PORT_SW_MINOR_VERSION_CFG_H                0
#define PORT_SW_PATCH_VERSION_CFG_H                1

/*=================================================================================================
*                               FILE VERSION CHECKS
=================================================================================================*/

/* Check if Port_Cfg.h and Port_SIU_Types.h file are of the same vendor */
#if (PORT_VENDOR_ID_CFG_H != PORT_SIU_VENDOR_ID_TYPES_H)
    #error "Port_Cfg.h and Port_Siu_Types.h have different vendor ids"
#endif
/* Check if Port_Cfg.h and Port_Siu_Types.h file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_H != PORT_SIU_AR_RELEASE_MAJOR_VERSION_TYPES_H)   ||  \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_H != PORT_SIU_AR_RELEASE_MINOR_VERSION_TYPES_H)   ||  \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_H != PORT_SIU_AR_RELEASE_REVISION_VERSION_TYPES_H) \
    )
    #error "AutoSar Version Numbers of Port_Cfg.h and Port_Siu_Types.h are different"
#endif
/* Check if Port_Cfg.h and Port_Siu_Types.h file are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_H != PORT_SIU_SW_MAJOR_VERSION_TYPES_H) || \
     (PORT_SW_MINOR_VERSION_CFG_H != PORT_SIU_SW_MINOR_VERSION_TYPES_H) || \
     (PORT_SW_PATCH_VERSION_CFG_H != PORT_SIU_SW_PATCH_VERSION_TYPES_H)    \
    )
    #error "Software Version Numbers of Port_Cfg.h and Port_Siu_Types.h are different"
#endif

/* Check if Port_Cfg.h and Port_Igf_Types.h file are of the same vendor */
#if (PORT_VENDOR_ID_CFG_H != PORT_IGF_VENDOR_ID_TYPES_H)
    #error "Port_Cfg.h and Port_Igf_Types.h have different vendor ids"
#endif
/* Check if Port_Cfg.h and Port_Igf_Types.h file are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_H != PORT_IGF_AR_RELEASE_MAJOR_VERSION_TYPES_H)   ||  \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_H != PORT_IGF_AR_RELEASE_MINOR_VERSION_TYPES_H)   ||  \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_H != PORT_IGF_AR_RELEASE_REVISION_VERSION_TYPES_H) \
    )
    #error "AutoSar Version Numbers of Port_Cfg.h and Port_Igf_Types.h are different"
#endif
/* Check if Port_Cfg.h and Port_Igf_Types.h file are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_H != PORT_IGF_SW_MAJOR_VERSION_TYPES_H) || \
     (PORT_SW_MINOR_VERSION_CFG_H != PORT_IGF_SW_MINOR_VERSION_TYPES_H) || \
     (PORT_SW_PATCH_VERSION_CFG_H != PORT_IGF_SW_PATCH_VERSION_TYPES_H)    \
    )
    #error "Software Version Numbers of Port_Cfg.h and Port_Igf_Types.h are different"
#endif

/* Check if Port_Cfg.h file and Port_EnvCfg header file are of the same vendor */
#if (PORT_VENDOR_ID_CFG_H != PORT_ENVCFG_VENDOR_ID)
    #error "Port_Cfg.h and Port_EnvCfg.h have different vendor IDs"
#endif

#if ((PORT_AR_RELEASE_MAJOR_VERSION_CFG_H != PORT_ENVCFG_AR_RELEASE_MAJOR_VERSION)      || \
     (PORT_AR_RELEASE_MINOR_VERSION_CFG_H != PORT_ENVCFG_AR_RELEASE_MINOR_VERSION)      || \
     (PORT_AR_RELEASE_REVISION_VERSION_CFG_H != PORT_ENVCFG_AR_RELEASE_REVISION_VERSION)   \
    )
    #error "AutoSar Version Numbers of Port_Cfg.h and Port_EnvCfg.h are different"
#endif
/* Check if Port_Cfg.h and PORT header file are of the same Software version */
#if ((PORT_SW_MAJOR_VERSION_CFG_H != PORT_ENVCFG_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_CFG_H != PORT_ENVCFG_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_CFG_H != PORT_ENVCFG_SW_PATCH_VERSION)    \
    )
#error "Software Version Numbers of Port_Cfg.h and Port_EnvCfg.h are different"
#endif


/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/**
* @brief       Ensure better readability of the configuration
* @note 
*
* @violates @ref PORT_CFG_H_REF_3 Function-like macro defined.
*/
#define SHL_PAD_U16(x)                      ((uint16)(((uint16)1) << (x)))

/**
* @brief Inmux setting not available
* @note The current platform does not implement pad selection for multiplexed input for current pin.
*       Used for better readability of Inmux settings.
*
*/
#define NO_INPUTMUX_U16                     ((uint16)0xFFFFU)

/**
* @brief Muxsel in the Inmux register not available
* @note The current platform does not implement pad selection for multiplexed input for current pin.
*       Used for better readability of Inmux Muxsel settings.
*
*/
#define MUXSEL_RESERVED_U8                  ((uint8)0xFF)

/**
* @brief Show the Platform used.
* @note This define can be used by test phase.  
*
*/
#define PLATFORM_COBRA55
/**
* @brief Shows the IPV used.
* @note This define can be used by test phase.
*
*/
#define IPV_SIU_USED

/**
* @brief Shows the IPV used.
* @note This define can be used by test phase.
*
*/
#define IPV_IGF_USED


/** @brief Port GPIO Mode */
#define PORT_GPIO_MODE                  ((Port_PinModeType)0)
/** @brief Port Alternate 1 Mode */
#define PORT_ALT1_FUNC_MODE             ((Port_PinModeType)1)
/** @brief Port Alternate 2 Mode */
#define PORT_ALT2_FUNC_MODE             ((Port_PinModeType)2)
/** @brief Port Alternate 3 Mode */
#define PORT_ALT3_FUNC_MODE             ((Port_PinModeType)3)
/** @brief Port Alternate 4 Mode */
#define PORT_ALT4_FUNC_MODE             ((Port_PinModeType)4)
/** @brief Port Input 1 Mode */
#define PORT_INPUT1_MODE                ((Port_PinModeType)5)
/** @brief Port Input 2 Mode */
#define PORT_INPUT2_MODE                ((Port_PinModeType)6)
/** @brief Port Input 3 Mode */
#define PORT_INPUT3_MODE                ((Port_PinModeType)7)
/** @brief Port Input 4 Mode */
#define PORT_INPUT4_MODE                ((Port_PinModeType)8)
/** @brief Port ADC Mode */
#define PORT_ANALOG_INPUT_MODE          ((Port_PinModeType)9)

/** @brief Port Abstraction Modes */



#define    PORT75_GPIO        (PORT_GPIO_MODE)
#define    PORT76_GPIO        (PORT_GPIO_MODE)
#define    PORT77_GPIO        (PORT_GPIO_MODE)
#define    PORT78_GPIO        (PORT_GPIO_MODE)
#define    PORT79_GPIO        (PORT_GPIO_MODE)
#define    PORT80_GPIO        (PORT_GPIO_MODE)
#define    PORT81_GPIO        (PORT_GPIO_MODE)
#define    PORT82_GPIO        (PORT_GPIO_MODE)
#define    PORT83_GPIO        (PORT_GPIO_MODE)
#define    PORT83_FlexCAN_A_CNTXA        (PORT_ALT1_FUNC_MODE)
#define    PORT83_eSCI_A_TXDA        (PORT_INPUT2_MODE)
#define    PORT83_MCAN_0_TX_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT84_GPIO        (PORT_GPIO_MODE)
#define    PORT84_FlexCAN_A_CNRXA        (PORT_ALT1_FUNC_MODE)
#define    PORT84_eSCI_A_RXDA        (PORT_INPUT2_MODE)
#define    PORT84_MCAN_0_RX_IN        (PORT_INPUT3_MODE)
#define    PORT85_GPIO        (PORT_GPIO_MODE)
#define    PORT85_FlexCAN_B_CNTXB        (PORT_ALT1_FUNC_MODE)
#define    PORT85_DSPI_C_PCSC3        (PORT_ALT2_FUNC_MODE)
#define    PORT86_GPIO        (PORT_GPIO_MODE)
#define    PORT86_FlexCAN_B_CNRXB        (PORT_ALT1_FUNC_MODE)
#define    PORT86_DSPI_C_PCSC4        (PORT_ALT2_FUNC_MODE)
#define    PORT87_GPIO        (PORT_GPIO_MODE)
#define    PORT87_FlexCAN_C_CNTXC        (PORT_ALT1_FUNC_MODE)
#define    PORT87_DSPI_D_PCSD3        (PORT_ALT2_FUNC_MODE)
#define    PORT88_GPIO        (PORT_GPIO_MODE)
#define    PORT88_FlexCAN_C_CNRXC        (PORT_ALT1_FUNC_MODE)
#define    PORT88_DSPI_D_PCSD4        (PORT_ALT2_FUNC_MODE)
#define    PORT88_eSCI_E_RXDE        (PORT_ALT3_FUNC_MODE)
#define    PORT89_GPIO        (PORT_GPIO_MODE)
#define    PORT89_eSCI_A_TXDA        (PORT_INPUT1_MODE)
#define    PORT90_GPIO        (PORT_GPIO_MODE)
#define    PORT90_eSCI_A_RXDA_IN        (PORT_INPUT1_MODE)
#define    PORT91_GPIO        (PORT_GPIO_MODE)
#define    PORT91_eSCI_B_TXDB        (PORT_INPUT1_MODE)
#define    PORT91_DSPI_D_PCSD1        (PORT_ALT2_FUNC_MODE)
#define    PORT91_MCAN_0_RX_IN        (PORT_INPUT3_MODE)
#define    PORT92_GPIO        (PORT_GPIO_MODE)
#define    PORT92_eSCI_B_RXDB        (PORT_INPUT1_MODE)
#define    PORT92_DSPI_D_PCSD5        (PORT_ALT2_FUNC_MODE)
#define    PORT93_GPIO        (PORT_GPIO_MODE)
#define    PORT93_DSPI_A_SCKA_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT93_DSPI_A_SCKA_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT93_DSPI_A_SCKA_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT93_DSPI_C_PCSC1        (PORT_ALT2_FUNC_MODE)
#define    PORT93_MCAN_0_TX_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT93_SENT_B_SENT1_B_IN        (PORT_INPUT4_MODE)
#define    PORT94_GPIO        (PORT_GPIO_MODE)
#define    PORT94_DSPI_A_SINA        (PORT_ALT1_FUNC_MODE)
#define    PORT94_DSPI_C_PCSC2        (PORT_ALT2_FUNC_MODE)
#define    PORT95_GPIO        (PORT_GPIO_MODE)
#define    PORT95_DSPI_A_SOUTA        (PORT_ALT1_FUNC_MODE)
#define    PORT95_DSPI_C_PCSC5        (PORT_ALT2_FUNC_MODE)
#define    PORT96_GPIO        (PORT_GPIO_MODE)
#define    PORT96_DSPI_A_PCSA0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT96_DSPI_A_PCSA0_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT96_DSPI_A_PCSA0_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT96_DSPI_D_PCSD2        (PORT_ALT2_FUNC_MODE)
#define    PORT97_GPIO        (PORT_GPIO_MODE)
#define    PORT97_DSPI_A_PCSA1        (PORT_ALT1_FUNC_MODE)
#define    PORT97_DSPI_E_PCSE0_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT97_DSPI_E_PCSE0_IN        (PORT_ALT2_FUNC_MODE)
#define    PORT97_DSPI_E_PCSE0_INOUT        (PORT_ALT2_FUNC_MODE)
#define    PORT98_GPIO        (PORT_GPIO_MODE)
#define    PORT98_DSPI_A_PCSA2        (PORT_ALT1_FUNC_MODE)
#define    PORT98_DSPI_E_SOUTE        (PORT_ALT2_FUNC_MODE)
#define    PORT98_FEC_FEC_TXD2_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT98_FEC_FEC_RXER_IN        (PORT_ALT4_FUNC_MODE)
#define    PORT99_GPIO        (PORT_GPIO_MODE)
#define    PORT99_DSPI_A_PCSA3        (PORT_ALT1_FUNC_MODE)
#define    PORT99_DSPI_E_SINE        (PORT_ALT2_FUNC_MODE)
#define    PORT99_FEC_FEC_MDIO        (PORT_ALT3_FUNC_MODE)
#define    PORT99_eSCI_D_TXDD        (PORT_ALT4_FUNC_MODE)
#define    PORT100_GPIO        (PORT_GPIO_MODE)
#define    PORT100_DSPI_A_PCSA4        (PORT_ALT1_FUNC_MODE)
#define    PORT100_DSPI_E_SCKE_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT100_DSPI_E_SCKE_IN        (PORT_ALT2_FUNC_MODE)
#define    PORT100_DSPI_E_SCKE_INOUT        (PORT_ALT2_FUNC_MODE)
#define    PORT100_eSCI_E_TXDE        (PORT_INPUT3_MODE)
#define    PORT100_FEC_FEC_RXCLK_IN        (PORT_ALT4_FUNC_MODE)
#define    PORT101_GPIO        (PORT_GPIO_MODE)
#define    PORT101_DSPI_A_PCSA5        (PORT_ALT1_FUNC_MODE)
#define    PORT101_eQADC_A_eQADC_B_ETRIG1        (PORT_ALT2_FUNC_MODE)
#define    PORT101_eSCI_D_RXDD        (PORT_ALT3_FUNC_MODE)
#define    PORT101_FEC_FEC_TXD3_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT102_GPIO        (PORT_GPIO_MODE)
#define    PORT102_DSPI_B_SCKB_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT102_DSPI_B_SCKB_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT102_DSPI_B_SCKB_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT103_GPIO        (PORT_GPIO_MODE)
#define    PORT103_DSPI_B_SINB        (PORT_ALT1_FUNC_MODE)
#define    PORT104_GPIO        (PORT_GPIO_MODE)
#define    PORT104_DSPI_B_SOUTB        (PORT_ALT1_FUNC_MODE)
#define    PORT105_GPIO        (PORT_GPIO_MODE)
#define    PORT105_DSPI_B_PCSB0_INOUT        (PORT_INPUT1_MODE)
#define    PORT105_DSPI_D_PCSD2        (PORT_ALT2_FUNC_MODE)
#define    PORT105_DSPI_B_PCSB0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT105_DSPI_B_PCSB0_IN        (PORT_INPUT1_MODE)
#define    PORT106_GPIO        (PORT_GPIO_MODE)
#define    PORT106_DSPI_B_PCSB1        (PORT_ALT1_FUNC_MODE)
#define    PORT106_DSPI_D_PCSD0_INOUT        (PORT_INPUT2_MODE)
#define    PORT106_DSPI_D_PCSD0_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT106_DSPI_D_PCSD0_IN        (PORT_INPUT2_MODE)
#define    PORT107_GPIO        (PORT_GPIO_MODE)
#define    PORT107_DSPI_B_PCSB2        (PORT_ALT1_FUNC_MODE)
#define    PORT107_DSPI_C_SOUTC        (PORT_ALT2_FUNC_MODE)
#define    PORT107_SENT_B_SENT2_B_IN        (PORT_INPUT3_MODE)
#define    PORT107_FEC_FEC_RXD3_IN        (PORT_ALT4_FUNC_MODE)
#define    PORT108_GPIO        (PORT_GPIO_MODE)
#define    PORT108_DSPI_B_PCSB3        (PORT_ALT1_FUNC_MODE)
#define    PORT108_DSPI_C_SINC        (PORT_INPUT2_MODE)
#define    PORT108_SENT_B_SENT3_B_IN        (PORT_INPUT3_MODE)
#define    PORT109_GPIO        (PORT_GPIO_MODE)
#define    PORT109_DSPI_B_PCSB4        (PORT_ALT1_FUNC_MODE)
#define    PORT109_DSPI_C_SCKC_INOUT        (PORT_INPUT2_MODE)
#define    PORT109_SENT_B_SENT4_B_IN        (PORT_INPUT3_MODE)
#define    PORT109_FEC_FEC_MDC_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT109_DSPI_C_SCKC_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT109_DSPI_C_SCKC_IN        (PORT_INPUT2_MODE)
#define    PORT110_GPIO        (PORT_GPIO_MODE)
#define    PORT110_DSPI_B_PCSB5        (PORT_ALT1_FUNC_MODE)
#define    PORT110_DSPI_C_PCSC0_INOUT        (PORT_INPUT2_MODE)
#define    PORT110_SENT_B_SENT5_B_IN        (PORT_INPUT3_MODE)
#define    PORT110_FEC_FEC_RXD2_IN        (PORT_ALT4_FUNC_MODE)
#define    PORT110_DSPI_C_PCSC0_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT110_DSPI_C_PCSC0_IN        (PORT_INPUT2_MODE)
#define    PORT113_GPIO        (PORT_GPIO_MODE)
#define    PORT113_eTPU_A_TCRCLKA        (PORT_ALT1_FUNC_MODE)
#define    PORT113_SIU_A_IRQ7        (PORT_ALT2_FUNC_MODE)
#define    PORT114_GPIO        (PORT_GPIO_MODE)
#define    PORT114_eTPU_A_ETPUA0_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT114_eTPU_A_ETPUA12        (PORT_ALT2_FUNC_MODE)
#define    PORT114_eTPU_A_ETPUA0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT114_eTPU_A_ETPUA0_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT115_GPIO        (PORT_GPIO_MODE)
#define    PORT115_eTPU_A_ETPUA1_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT115_eTPU_A_ETPUA13        (PORT_ALT2_FUNC_MODE)
#define    PORT115_eTPU_A_ETPUA1_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT115_eTPU_A_ETPUA1_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT116_GPIO        (PORT_GPIO_MODE)
#define    PORT116_eTPU_A_ETPUA2_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT116_eTPU_A_ETPUA14        (PORT_ALT2_FUNC_MODE)
#define    PORT116_REACM_RCH0_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT116_eTPU_A_ETPUA2_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT116_eTPU_A_ETPUA2_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT117_GPIO        (PORT_GPIO_MODE)
#define    PORT117_eTPU_A_ETPUA3_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT117_eTPU_A_ETPUA15        (PORT_ALT2_FUNC_MODE)
#define    PORT117_REACM_RCH1_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT117_FCCU_ERROR0        (PORT_ALT4_FUNC_MODE)
#define    PORT117_eTPU_A_ETPUA3_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT117_eTPU_A_ETPUA3_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT118_GPIO        (PORT_GPIO_MODE)
#define    PORT118_eTPU_A_ETPUA4_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT118_eTPU_A_ETPUA16        (PORT_ALT2_FUNC_MODE)
#define    PORT118_REACM_RCH2_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT118_eTPU_A_ETPUA4_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT118_eTPU_A_ETPUA4_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT119_GPIO        (PORT_GPIO_MODE)
#define    PORT119_eTPU_A_ETPUA5_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT119_eTPU_A_ETPUA17        (PORT_ALT2_FUNC_MODE)
#define    PORT119_REACM_RCH3_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT119_eTPU_A_ETPUA5_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT119_eTPU_A_ETPUA5_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT120_GPIO        (PORT_GPIO_MODE)
#define    PORT120_eTPU_A_ETPUA6_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT120_eTPU_A_ETPUA18        (PORT_ALT2_FUNC_MODE)
#define    PORT120_REACM_RCH4_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT120_eTPU_A_ETPUA6_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT120_eTPU_A_ETPUA6_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT121_GPIO        (PORT_GPIO_MODE)
#define    PORT121_eTPU_A_ETPUA7_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT121_eTPU_A_ETPUA19        (PORT_ALT2_FUNC_MODE)
#define    PORT121_REACM_RCH5_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT121_eTPU_A_ETPUA7_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT121_eTPU_A_ETPUA7_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT122_GPIO        (PORT_GPIO_MODE)
#define    PORT122_eTPU_A_ETPUA8_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT122_eTPU_A_ETPUA20        (PORT_ALT2_FUNC_MODE)
#define    PORT122_REACM_RCH6_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT122_eTPU_A_ETPUA8_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT122_eTPU_A_ETPUA8_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT123_GPIO        (PORT_GPIO_MODE)
#define    PORT123_eTPU_A_ETPUA9_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT123_eTPU_A_ETPUA21        (PORT_ALT2_FUNC_MODE)
#define    PORT123_REACM_RCH7_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT123_eTPU_A_ETPUA9_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT123_eTPU_A_ETPUA9_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT124_GPIO        (PORT_GPIO_MODE)
#define    PORT124_eTPU_A_ETPUA10_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT124_eTPU_A_ETPUA22        (PORT_ALT2_FUNC_MODE)
#define    PORT124_REACM_RCH8_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT124_FCCU_ERRORIN        (PORT_ALT4_FUNC_MODE)
#define    PORT124_eTPU_A_ETPUA10_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT124_eTPU_A_ETPUA10_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT125_GPIO        (PORT_GPIO_MODE)
#define    PORT125_eTPU_A_ETPUA11_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT125_eTPU_A_ETPUA23        (PORT_ALT2_FUNC_MODE)
#define    PORT125_REACM_RCH9_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT125_FCCU_ERROR1        (PORT_ALT4_FUNC_MODE)
#define    PORT125_eTPU_A_ETPUA11_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT125_eTPU_A_ETPUA11_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT126_GPIO        (PORT_GPIO_MODE)
#define    PORT126_eTPU_A_ETPUA12_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT126_DSPI_B_PCSB1        (PORT_ALT2_FUNC_MODE)
#define    PORT126_eTPU_A_ETPUA12_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT126_eTPU_A_ETPUA12_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT127_GPIO        (PORT_GPIO_MODE)
#define    PORT127_eTPU_A_ETPUA13_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT127_DSPI_B_PCSB3        (PORT_ALT2_FUNC_MODE)
#define    PORT127_eTPU_A_ETPUA13_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT127_eTPU_A_ETPUA13_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT128_GPIO        (PORT_GPIO_MODE)
#define    PORT128_eTPU_A_ETPUA14_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT128_DSPI_B_PCSB4        (PORT_ALT2_FUNC_MODE)
#define    PORT128_eTPU_A_ETPUA14_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT128_eTPU_A_ETPUA14_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT129_GPIO        (PORT_GPIO_MODE)
#define    PORT129_eTPU_A_ETPUA15_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT129_DSPI_B_PCSB5        (PORT_ALT2_FUNC_MODE)
#define    PORT129_MCAN_0_TX_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT129_eTPU_A_ETPUA15_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT129_eTPU_A_ETPUA15_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT130_GPIO        (PORT_GPIO_MODE)
#define    PORT130_eTPU_A_ETPUA16_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT130_DSPI_D_PCSD1        (PORT_ALT2_FUNC_MODE)
#define    PORT130_eTPU_A_ETPUA16_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT130_eTPU_A_ETPUA16_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT131_GPIO        (PORT_GPIO_MODE)
#define    PORT131_eTPU_A_ETPUA17_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT131_DSPI_D_PCSD2        (PORT_ALT2_FUNC_MODE)
#define    PORT131_eTPU_A_ETPUA17_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT131_eTPU_A_ETPUA17_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT132_GPIO        (PORT_GPIO_MODE)
#define    PORT132_eTPU_A_ETPUA18_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT132_DSPI_D_PCSD3        (PORT_ALT2_FUNC_MODE)
#define    PORT132_eTPU_A_ETPUA18_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT132_eTPU_A_ETPUA18_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT133_GPIO        (PORT_GPIO_MODE)
#define    PORT133_eTPU_A_ETPUA19_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT133_DSPI_D_PCSD4        (PORT_ALT2_FUNC_MODE)
#define    PORT133_MCAN_0_RX_IN        (PORT_INPUT3_MODE)
#define    PORT133_eTPU_A_ETPUA19_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT133_eTPU_A_ETPUA19_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT134_GPIO        (PORT_GPIO_MODE)
#define    PORT134_eTPU_A_ETPUA20_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT134_SIU_A_IRQ8        (PORT_ALT2_FUNC_MODE)
#define    PORT134_eTPU_A_ETPUA20_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT134_eTPU_A_ETPUA20_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT135_GPIO        (PORT_GPIO_MODE)
#define    PORT135_eTPU_A_ETPUA21_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT135_SIU_A_IRQ9        (PORT_ALT2_FUNC_MODE)
#define    PORT135_eTPU_A_ETPUA21_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT135_eTPU_A_ETPUA21_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT136_GPIO        (PORT_GPIO_MODE)
#define    PORT136_eTPU_A_ETPUA22_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT136_SIU_A_IRQ10        (PORT_ALT2_FUNC_MODE)
#define    PORT136_REACM_RCH0_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT136_eTPU_A_ETPUA22_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT136_eTPU_A_ETPUA22_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT137_GPIO        (PORT_GPIO_MODE)
#define    PORT137_eTPU_A_ETPUA23_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT137_SIU_A_IRQ11        (PORT_ALT2_FUNC_MODE)
#define    PORT137_REACM_RCH1_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT137_eTPU_A_ETPUA23_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT137_eTPU_A_ETPUA23_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT138_GPIO        (PORT_GPIO_MODE)
#define    PORT138_eTPU_A_ETPUA24_INOUT        (PORT_INPUT1_MODE)
#define    PORT138_SIU_A_IRQ12        (PORT_ALT2_FUNC_MODE)
#define    PORT138_REACM_RCH2_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT138_eTPU_A_ETPUA24_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT138_eTPU_A_ETPUA24_IN        (PORT_INPUT1_MODE)
#define    PORT139_GPIO        (PORT_GPIO_MODE)
#define    PORT139_eTPU_A_ETPUA25_INOUT        (PORT_INPUT1_MODE)
#define    PORT139_SIU_A_IRQ13        (PORT_ALT2_FUNC_MODE)
#define    PORT139_REACM_RCH3_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT139_eTPU_A_ETPUA25_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT139_eTPU_A_ETPUA25_IN        (PORT_INPUT1_MODE)
#define    PORT140_GPIO        (PORT_GPIO_MODE)
#define    PORT140_eTPU_A_ETPUA26_INOUT        (PORT_INPUT1_MODE)
#define    PORT140_SIU_A_IRQ14        (PORT_ALT2_FUNC_MODE)
#define    PORT140_REACM_RCH4_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT140_eTPU_A_ETPUA26_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT140_eTPU_A_ETPUA26_IN        (PORT_INPUT1_MODE)
#define    PORT141_GPIO        (PORT_GPIO_MODE)
#define    PORT141_eTPU_A_ETPUA27_INOUT        (PORT_INPUT1_MODE)
#define    PORT141_SIU_A_IRQ15        (PORT_ALT2_FUNC_MODE)
#define    PORT141_REACM_RCH5_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT141_eTPU_A_ETPUA27_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT141_eTPU_A_ETPUA27_IN        (PORT_INPUT1_MODE)
#define    PORT142_GPIO        (PORT_GPIO_MODE)
#define    PORT142_eTPU_A_ETPUA28_INOUT        (PORT_INPUT1_MODE)
#define    PORT142_DSPI_C_PCSC1        (PORT_ALT2_FUNC_MODE)
#define    PORT142_REACM_RCH6_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT142_eTPU_A_ETPUA28_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT142_eTPU_A_ETPUA28_IN        (PORT_INPUT1_MODE)
#define    PORT143_GPIO        (PORT_GPIO_MODE)
#define    PORT143_eTPU_A_ETPUA29_INOUT        (PORT_INPUT1_MODE)
#define    PORT143_DSPI_C_PCSC2        (PORT_ALT2_FUNC_MODE)
#define    PORT143_REACM_RCH7_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT143_eTPU_A_ETPUA29_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT143_eTPU_A_ETPUA29_IN        (PORT_INPUT1_MODE)
#define    PORT144_GPIO        (PORT_GPIO_MODE)
#define    PORT144_eTPU_A_ETPUA30_INOUT        (PORT_INPUT1_MODE)
#define    PORT144_DSPI_C_PCSC3        (PORT_ALT2_FUNC_MODE)
#define    PORT144_REACM_RCH8_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT144_eTPU_A_ETPUA30_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT144_eTPU_A_ETPUA30_IN        (PORT_INPUT1_MODE)
#define    PORT145_GPIO        (PORT_GPIO_MODE)
#define    PORT145_eTPU_A_ETPUA31_INOUT        (PORT_INPUT1_MODE)
#define    PORT145_DSPI_C_PCSC4        (PORT_ALT2_FUNC_MODE)
#define    PORT145_REACM_RCH9_A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT145_eTPU_A_ETPUA31_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT145_eTPU_A_ETPUA31_IN        (PORT_INPUT1_MODE)
#define    PORT146_GPIO        (PORT_GPIO_MODE)
#define    PORT146_eTPU_B_TCRCLKB        (PORT_ALT1_FUNC_MODE)
#define    PORT146_SIU_A_IRQ6        (PORT_INPUT2_MODE)
#define    PORT147_GPIO        (PORT_GPIO_MODE)
#define    PORT147_eTPU_B_ETPUB0_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT147_eTPU_B_ETPUB16        (PORT_ALT2_FUNC_MODE)
#define    PORT147_eTPU_B_ETPUB0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT147_eTPU_B_ETPUB0_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT148_GPIO        (PORT_GPIO_MODE)
#define    PORT148_eTPU_B_ETPUB1_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT148_eTPU_B_ETPUB17        (PORT_ALT2_FUNC_MODE)
#define    PORT148_eTPU_B_ETPUB1_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT148_eTPU_B_ETPUB1_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT149_GPIO        (PORT_GPIO_MODE)
#define    PORT149_eTPU_B_ETPUB2_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT149_eTPU_B_ETPUB18        (PORT_ALT2_FUNC_MODE)
#define    PORT149_eTPU_B_ETPUB2_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT149_eTPU_B_ETPUB2_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT150_GPIO        (PORT_GPIO_MODE)
#define    PORT150_eTPU_B_ETPUB3_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT150_eTPU_B_ETPUB19        (PORT_ALT2_FUNC_MODE)
#define    PORT150_eTPU_B_ETPUB3_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT150_eTPU_B_ETPUB3_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT151_GPIO        (PORT_GPIO_MODE)
#define    PORT151_eTPU_B_ETPUB4_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT151_eTPU_B_ETPUB20        (PORT_ALT2_FUNC_MODE)
#define    PORT151_eTPU_B_ETPUB4_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT151_eTPU_B_ETPUB4_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT152_GPIO        (PORT_GPIO_MODE)
#define    PORT152_eTPU_B_ETPUB5_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT152_eTPU_B_ETPUB21        (PORT_ALT2_FUNC_MODE)
#define    PORT152_eTPU_B_ETPUB5_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT152_eTPU_B_ETPUB5_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT153_GPIO        (PORT_GPIO_MODE)
#define    PORT153_eTPU_B_ETPUB6_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT153_eTPU_B_ETPUB22        (PORT_ALT2_FUNC_MODE)
#define    PORT153_eTPU_B_ETPUB6_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT153_eTPU_B_ETPUB6_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT154_GPIO        (PORT_GPIO_MODE)
#define    PORT154_eTPU_B_ETPUB7_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT154_eTPU_B_ETPUB23        (PORT_ALT2_FUNC_MODE)
#define    PORT154_eTPU_B_ETPUB7_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT154_eTPU_B_ETPUB7_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT155_GPIO        (PORT_GPIO_MODE)
#define    PORT155_eTPU_B_ETPUB8_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT155_eTPU_B_ETPUB24        (PORT_ALT2_FUNC_MODE)
#define    PORT155_eTPU_B_ETPUB8_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT155_eTPU_B_ETPUB8_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT156_GPIO        (PORT_GPIO_MODE)
#define    PORT156_eTPU_B_ETPUB9_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT156_eTPU_B_ETPUB25        (PORT_ALT2_FUNC_MODE)
#define    PORT156_eTPU_B_ETPUB9_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT156_eTPU_B_ETPUB9_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT157_GPIO        (PORT_GPIO_MODE)
#define    PORT157_eTPU_B_ETPUB10_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT157_eTPU_B_ETPUB26        (PORT_ALT2_FUNC_MODE)
#define    PORT157_eTPU_B_ETPUB10_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT157_eTPU_B_ETPUB10_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT158_GPIO        (PORT_GPIO_MODE)
#define    PORT158_eTPU_B_ETPUB11_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT158_eTPU_B_ETPUB27        (PORT_ALT2_FUNC_MODE)
#define    PORT158_eTPU_B_ETPUB11_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT158_eTPU_B_ETPUB11_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT159_GPIO        (PORT_GPIO_MODE)
#define    PORT159_eTPU_B_ETPUB12_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT159_eTPU_B_ETPUB28        (PORT_ALT2_FUNC_MODE)
#define    PORT159_eTPU_B_ETPUB12_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT159_eTPU_B_ETPUB12_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT160_GPIO        (PORT_GPIO_MODE)
#define    PORT160_eTPU_B_ETPUB13_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT160_eTPU_B_ETPUB29        (PORT_ALT2_FUNC_MODE)
#define    PORT160_eTPU_B_ETPUB13_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT160_eTPU_B_ETPUB13_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT161_GPIO        (PORT_GPIO_MODE)
#define    PORT161_eTPU_B_ETPUB14_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT161_eTPU_B_ETPUB30        (PORT_ALT2_FUNC_MODE)
#define    PORT161_eTPU_B_ETPUB14_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT161_eTPU_B_ETPUB14_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT162_GPIO        (PORT_GPIO_MODE)
#define    PORT162_eTPU_B_ETPUB15_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT162_eTPU_B_ETPUB31        (PORT_ALT2_FUNC_MODE)
#define    PORT162_eTPU_B_ETPUB15_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT162_eTPU_B_ETPUB15_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT163_GPIO        (PORT_GPIO_MODE)
#define    PORT163_eTPU_B_ETPUB16_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT163_DSPI_A_PCSA1        (PORT_ALT2_FUNC_MODE)
#define    PORT163_eTPU_B_ETPUB16_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT163_eTPU_B_ETPUB16_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT164_GPIO        (PORT_GPIO_MODE)
#define    PORT164_eTPU_B_ETPUB17_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT164_DSPI_A_PCSA2        (PORT_ALT2_FUNC_MODE)
#define    PORT164_eTPU_B_ETPUB17_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT164_eTPU_B_ETPUB17_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT165_GPIO        (PORT_GPIO_MODE)
#define    PORT165_eTPU_B_ETPUB18_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT165_DSPI_A_PCSA3        (PORT_ALT2_FUNC_MODE)
#define    PORT165_eTPU_B_ETPUB18_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT165_eTPU_B_ETPUB18_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT166_GPIO        (PORT_GPIO_MODE)
#define    PORT166_eTPU_B_ETPUB19_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT166_DSPI_A_PCSA4        (PORT_ALT2_FUNC_MODE)
#define    PORT166_eTPU_B_ETPUB19_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT166_eTPU_B_ETPUB19_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT167_GPIO        (PORT_GPIO_MODE)
#define    PORT167_eTPU_B_ETPUB20_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT167_eTPU_B_ETPUB20_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT167_eTPU_B_ETPUB20_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT168_GPIO        (PORT_GPIO_MODE)
#define    PORT168_eTPU_B_ETPUB21_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT168_eTPU_B_ETPUB21_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT168_eTPU_B_ETPUB21_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT169_GPIO        (PORT_GPIO_MODE)
#define    PORT169_eTPU_B_ETPUB22_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT169_REACM_RCH0_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT169_eTPU_B_ETPUB22_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT169_eTPU_B_ETPUB22_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT170_GPIO        (PORT_GPIO_MODE)
#define    PORT170_eTPU_B_ETPUB23_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT170_REACM_RCH1_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT170_eTPU_B_ETPUB23_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT170_eTPU_B_ETPUB23_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT171_GPIO        (PORT_GPIO_MODE)
#define    PORT171_eTPU_B_ETPUB24_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT171_REACM_RCH2_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT171_eTPU_B_ETPUB24_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT171_eTPU_B_ETPUB24_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT172_GPIO        (PORT_GPIO_MODE)
#define    PORT172_eTPU_B_ETPUB25_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT172_REACM_RCH3_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT172_eTPU_B_ETPUB25_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT172_eTPU_B_ETPUB25_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT173_GPIO        (PORT_GPIO_MODE)
#define    PORT173_eTPU_B_ETPUB26_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT173_REACM_RCH4_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT173_eTPU_B_ETPUB26_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT173_eTPU_B_ETPUB26_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT174_GPIO        (PORT_GPIO_MODE)
#define    PORT174_eTPU_B_ETPUB27_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT174_REACM_RCH5_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT174_eTPU_B_ETPUB27_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT174_eTPU_B_ETPUB27_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT175_GPIO        (PORT_GPIO_MODE)
#define    PORT175_eTPU_B_ETPUB28_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT175_REACM_RCH6_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT175_eTPU_B_ETPUB28_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT175_eTPU_B_ETPUB28_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT176_GPIO        (PORT_GPIO_MODE)
#define    PORT176_eTPU_B_ETPUB29_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT176_REACM_RCH7_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT176_eTPU_B_ETPUB29_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT176_eTPU_B_ETPUB29_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT177_GPIO        (PORT_GPIO_MODE)
#define    PORT177_eTPU_B_ETPUB30_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT177_REACM_RCH8_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT177_eTPU_B_ETPUB30_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT177_eTPU_B_ETPUB30_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT178_GPIO        (PORT_GPIO_MODE)
#define    PORT178_eTPU_B_ETPUB31_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT178_REACM_RCH9_B_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT178_eTPU_B_ETPUB31_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT178_eTPU_B_ETPUB31_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT179_GPIO        (PORT_GPIO_MODE)
#define    PORT179_eMIOS_A_EMIOS0_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT179_eTPU_A_ETPUA0        (PORT_ALT2_FUNC_MODE)
#define    PORT179_REACM_RCH0_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT179_eMIOS_A_EMIOS0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT179_eMIOS_A_EMIOS0_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT180_GPIO        (PORT_GPIO_MODE)
#define    PORT180_eMIOS_A_EMIOS1_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT180_eTPU_A_ETPUA1        (PORT_ALT2_FUNC_MODE)
#define    PORT180_REACM_RCH1_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT180_DSPI_E_PCSE2        (PORT_ALT4_FUNC_MODE)
#define    PORT180_eMIOS_A_EMIOS1_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT180_eMIOS_A_EMIOS1_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT181_GPIO        (PORT_GPIO_MODE)
#define    PORT181_eMIOS_A_EMIOS2_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT181_eTPU_A_ETPUA2        (PORT_ALT2_FUNC_MODE)
#define    PORT181_REACM_RCH2_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT181_DSPI_E_PCSE3        (PORT_ALT4_FUNC_MODE)
#define    PORT181_eMIOS_A_EMIOS2_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT181_eMIOS_A_EMIOS2_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT182_GPIO        (PORT_GPIO_MODE)
#define    PORT182_eMIOS_A_EMIOS3_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT182_eTPU_A_ETPUA3        (PORT_ALT2_FUNC_MODE)
#define    PORT182_REACM_RCH3_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT182_DSPI_E_PCSE4        (PORT_ALT4_FUNC_MODE)
#define    PORT182_eMIOS_A_EMIOS3_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT182_eMIOS_A_EMIOS3_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT183_GPIO        (PORT_GPIO_MODE)
#define    PORT183_eMIOS_A_EMIOS4        (PORT_ALT1_FUNC_MODE)
#define    PORT183_eTPU_A_ETPUA4        (PORT_ALT2_FUNC_MODE)
#define    PORT183_REACM_RCH4_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT183_DSPI_E_PCSE5        (PORT_ALT4_FUNC_MODE)
#define    PORT184_GPIO        (PORT_GPIO_MODE)
#define    PORT184_eMIOS_A_EMIOS5        (PORT_ALT1_FUNC_MODE)
#define    PORT184_eTPU_A_ETPUA5        (PORT_ALT2_FUNC_MODE)
#define    PORT184_REACM_RCH5_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT185_GPIO        (PORT_GPIO_MODE)
#define    PORT185_eMIOS_A_EMIOS6_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT185_eTPU_A_ETPUA6        (PORT_ALT2_FUNC_MODE)
#define    PORT185_REACM_RCH6_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT185_eMIOS_A_EMIOS6_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT185_eMIOS_A_EMIOS6_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT186_GPIO        (PORT_GPIO_MODE)
#define    PORT186_eMIOS_A_EMIOS7_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT186_eTPU_A_ETPUA7        (PORT_ALT2_FUNC_MODE)
#define    PORT186_REACM_RCH7_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT186_eMIOS_A_EMIOS7_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT186_eMIOS_A_EMIOS7_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT187_GPIO        (PORT_GPIO_MODE)
#define    PORT187_eMIOS_B_EMIOS0_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT187_eTPU_A_ETPUA8        (PORT_ALT2_FUNC_MODE)
#define    PORT187_REACM_RCH8_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT187_eMIOS_B_EMIOS0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT187_eMIOS_B_EMIOS0_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT188_GPIO        (PORT_GPIO_MODE)
#define    PORT188_eMIOS_B_EMIOS1_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT188_eTPU_A_ETPUA9        (PORT_ALT2_FUNC_MODE)
#define    PORT188_REACM_RCH9_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT188_eMIOS_B_EMIOS1_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT188_eMIOS_B_EMIOS1_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT189_GPIO        (PORT_GPIO_MODE)
#define    PORT189_eMIOS_B_EMIOS2_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT189_DSPI_D_SCKD_INOUT        (PORT_INPUT2_MODE)
#define    PORT189_eMIOS_B_EMIOS2_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT189_DSPI_D_SCKD_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT189_eMIOS_B_EMIOS2_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT189_DSPI_D_SCKD_IN        (PORT_INPUT2_MODE)
#define    PORT190_GPIO        (PORT_GPIO_MODE)
#define    PORT190_eMIOS_B_EMIOS3_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT190_DSPI_D_SIND        (PORT_INPUT2_MODE)
#define    PORT190_eMIOS_B_EMIOS3_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT190_eMIOS_B_EMIOS3_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT191_GPIO        (PORT_GPIO_MODE)
#define    PORT191_eMIOS_B_EMIOS4_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT191_DSPI_C_SOUTC        (PORT_ALT2_FUNC_MODE)
#define    PORT191_eMIOS_B_EMIOS4_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT191_eMIOS_B_EMIOS4_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT192_GPIO        (PORT_GPIO_MODE)
#define    PORT192_eMIOS_B_EMIOS5_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT192_DSPI_D_SOUTD        (PORT_ALT2_FUNC_MODE)
#define    PORT192_eMIOS_B_EMIOS5_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT192_eMIOS_B_EMIOS5_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT193_GPIO        (PORT_GPIO_MODE)
#define    PORT193_eMIOS_B_EMIOS6        (PORT_ALT1_FUNC_MODE)
#define    PORT193_SIU_A_IRQ0        (PORT_INPUT2_MODE)
#define    PORT193_FlexCAN_D_CNTXD        (PORT_ALT3_FUNC_MODE)
#define    PORT193_REACM_RCH0_C_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT194_GPIO        (PORT_GPIO_MODE)
#define    PORT194_eMIOS_B_EMIOS7        (PORT_ALT1_FUNC_MODE)
#define    PORT194_SIU_A_IRQ1_IN        (PORT_INPUT2_MODE)
#define    PORT194_FlexCAN_D_CNRXD_IN        (PORT_INPUT3_MODE)
#define    PORT194_REACM_RCH1_C_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT195_GPIO        (PORT_GPIO_MODE)
#define    PORT195_eMIOS_A_EMIOS16_INOUT        (PORT_INPUT1_MODE)
#define    PORT195_eTPU_B_ETPUB0        (PORT_ALT2_FUNC_MODE)
#define    PORT195_MCAN_1_TX_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT195_REACM_RCH2_C_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT195_eMIOS_A_EMIOS16_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT195_eMIOS_A_EMIOS16_IN        (PORT_INPUT1_MODE)
#define    PORT196_GPIO        (PORT_GPIO_MODE)
#define    PORT196_eMIOS_A_EMIOS17_INOUT        (PORT_INPUT1_MODE)
#define    PORT196_eTPU_B_ETPUB1        (PORT_ALT2_FUNC_MODE)
#define    PORT196_MCAN_1_RX_IN        (PORT_INPUT3_MODE)
#define    PORT196_REACM_RCH3_C_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT196_eMIOS_A_EMIOS17_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT196_eMIOS_A_EMIOS17_IN        (PORT_INPUT1_MODE)
#define    PORT197_GPIO        (PORT_GPIO_MODE)
#define    PORT197_eMIOS_A_EMIOS18_INOUT        (PORT_INPUT1_MODE)
#define    PORT197_eTPU_B_ETPUB2        (PORT_ALT2_FUNC_MODE)
#define    PORT197_REACM_RCH4_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT197_eMIOS_A_EMIOS18_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT197_eMIOS_A_EMIOS18_IN        (PORT_INPUT1_MODE)
#define    PORT198_GPIO        (PORT_GPIO_MODE)
#define    PORT198_eMIOS_A_EMIOS19_INOUT        (PORT_INPUT1_MODE)
#define    PORT198_eTPU_B_ETPUB3        (PORT_ALT2_FUNC_MODE)
#define    PORT198_REACM_RCH5_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT198_eMIOS_A_EMIOS19_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT198_eMIOS_A_EMIOS19_IN        (PORT_INPUT1_MODE)
#define    PORT199_GPIO        (PORT_GPIO_MODE)
#define    PORT199_eMIOS_A_EMIOS20_INOUT        (PORT_INPUT1_MODE)
#define    PORT199_eTPU_B_ETPUB4        (PORT_ALT2_FUNC_MODE)
#define    PORT199_REACM_RCH6_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT199_eMIOS_A_EMIOS20_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT199_eMIOS_A_EMIOS20_IN        (PORT_INPUT1_MODE)
#define    PORT200_GPIO        (PORT_GPIO_MODE)
#define    PORT200_eMIOS_A_EMIOS21_INOUT        (PORT_INPUT1_MODE)
#define    PORT200_eTPU_B_ETPUB5        (PORT_ALT2_FUNC_MODE)
#define    PORT200_REACM_RCH7_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT200_eMIOS_A_EMIOS21_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT200_eMIOS_A_EMIOS21_IN        (PORT_INPUT1_MODE)
#define    PORT201_GPIO        (PORT_GPIO_MODE)
#define    PORT201_eMIOS_A_EMIOS22_INOUT        (PORT_INPUT1_MODE)
#define    PORT201_eTPU_B_ETPUB6        (PORT_ALT2_FUNC_MODE)
#define    PORT201_REACM_RCH8_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT201_eMIOS_A_EMIOS22_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT201_eMIOS_A_EMIOS22_IN        (PORT_INPUT1_MODE)
#define    PORT202_GPIO        (PORT_GPIO_MODE)
#define    PORT202_eMIOS_A_EMIOS23_INOUT        (PORT_INPUT1_MODE)
#define    PORT202_eTPU_B_ETPUB7        (PORT_ALT2_FUNC_MODE)
#define    PORT202_REACM_RCH9_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT202_eMIOS_A_EMIOS23_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT202_eMIOS_A_EMIOS23_IN        (PORT_INPUT1_MODE)
#define    PORT203_GPIO        (PORT_GPIO_MODE)
#define    PORT203_eMIOS_B_EMIOS16_INOUT        (PORT_INPUT1_MODE)
#define    PORT203_DSPI_B_PCSB0_INOUT        (PORT_INPUT2_MODE)
#define    PORT203_eMIOS_B_EMIOS16_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT203_DSPI_B_PCSB0_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT203_eMIOS_B_EMIOS16_IN        (PORT_INPUT1_MODE)
#define    PORT203_DSPI_B_PCSB0_IN        (PORT_INPUT2_MODE)
#define    PORT204_GPIO        (PORT_GPIO_MODE)
#define    PORT204_eMIOS_B_EMIOS17_INOUT        (PORT_INPUT1_MODE)
#define    PORT204_DSPI_B_PCSB1        (PORT_ALT2_FUNC_MODE)
#define    PORT204_eMIOS_B_EMIOS17_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT204_eMIOS_B_EMIOS17_IN        (PORT_INPUT1_MODE)
#define    PORT208_GPIO        (PORT_GPIO_MODE)
#define    PORT208_SoC_PLLCFG0_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT208_SIU_A_IRQ4_IN        (PORT_INPUT2_MODE)
#define    PORT208_eTPU_C_ETPUC9_INOUT        (PORT_INPUT3_MODE)
#define    PORT208_SIPI_TXN        (PORT_ALT4_FUNC_MODE)
#define    PORT208_eTPU_C_ETPUC9_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT208_eTPU_C_ETPUC9_IN        (PORT_INPUT3_MODE)
#define    PORT209_GPIO        (PORT_GPIO_MODE)
#define    PORT209_SoC_PLLCFG1_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT209_SIU_A_IRQ5_IN        (PORT_INPUT2_MODE)
#define    PORT209_DSPI_D_SOUTD        (PORT_ALT3_FUNC_MODE)
#define    PORT209_SIPI_TXP        (PORT_ALT4_FUNC_MODE)
#define    PORT210_GPIO        (PORT_GPIO_MODE)
#define    PORT210_SoC_PLLCFG2_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT210_eTPU_C_ETPUC3_INOUT        (PORT_INPUT2_MODE)
#define    PORT210_DSPI_E_PCSE1        (PORT_ALT3_FUNC_MODE)
#define    PORT210_SIPI_REFCLK_INOUT        (PORT_ALT4_FUNC_MODE)
#define    PORT210_eTPU_C_ETPUC3_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT210_SIPI_REFCLK_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT210_eTPU_C_ETPUC3_IN        (PORT_INPUT2_MODE)
#define    PORT210_SIPI_REFCLK_IN        (PORT_ALT4_FUNC_MODE)
#define    PORT212_GPIO        (PORT_GPIO_MODE)
#define    PORT212_SoC_BOOTCFG1_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT212_SIU_A_IRQ3_IN        (PORT_INPUT2_MODE)
#define    PORT212_eTPU_C_ETPUC0_INOUT        (PORT_INPUT3_MODE)
#define    PORT212_SIPI_RXP        (PORT_ALT4_FUNC_MODE)
#define    PORT212_eTPU_C_ETPUC0_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT212_eTPU_C_ETPUC0_IN        (PORT_INPUT3_MODE)
#define    PORT213_GPIO        (PORT_GPIO_MODE)
#define    PORT213_SoC_WKPCFG_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT213_SIU_A_NMI_IN        (PORT_ALT2_FUNC_MODE)
#define    PORT213_eTPU_C_ETPUC1_INOUT        (PORT_INPUT3_MODE)
#define    PORT213_SIPI_RXN        (PORT_ALT4_FUNC_MODE)
#define    PORT213_eTPU_C_ETPUC1_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT213_eTPU_C_ETPUC1_IN        (PORT_INPUT3_MODE)
#define    PORT214_GPIO        (PORT_GPIO_MODE)
#define    PORT214_ENGCLK        (PORT_ALT1_FUNC_MODE)
#define    PORT219_GPIO        (PORT_GPIO_MODE)
#define    PORT219_MCKO        (PORT_ALT1_FUNC_MODE)
#define    PORT220_GPIO        (PORT_GPIO_MODE)
#define    PORT221_GPIO        (PORT_GPIO_MODE)
#define    PORT222_GPIO        (PORT_GPIO_MODE)
#define    PORT223_GPIO        (PORT_GPIO_MODE)
#define    PORT223_eSCI_E_TXDE        (PORT_INPUT2_MODE)
#define    PORT224_GPIO        (PORT_GPIO_MODE)
#define    PORT224_MSEO0        (PORT_ALT1_FUNC_MODE)
#define    PORT225_GPIO        (PORT_GPIO_MODE)
#define    PORT225_MSEO1        (PORT_ALT1_FUNC_MODE)
#define    PORT226_GPIO        (PORT_GPIO_MODE)
#define    PORT226_RDY        (PORT_ALT1_FUNC_MODE)
#define    PORT227_GPIO        (PORT_GPIO_MODE)
#define    PORT227_EVTO        (PORT_ALT1_FUNC_MODE)
#define    PORT228_GPIO        (PORT_GPIO_MODE)
#define    PORT228_TDO        (PORT_ALT1_FUNC_MODE)
#define    PORT229_GPIO        (PORT_GPIO_MODE)
#define    PORT229_D_CLKOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT230_GPIO        (PORT_GPIO_MODE)
#define    PORT230_RSTOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT231_GPIO        (PORT_GPIO_MODE)
#define    PORT232_GPIO        (PORT_GPIO_MODE)
#define    PORT233_GPIO        (PORT_GPIO_MODE)
#define    PORT234_GPIO        (PORT_GPIO_MODE)
#define    PORT235_GPIO        (PORT_GPIO_MODE)
#define    PORT235_DSPI_C_SCKC_INOUT        (PORT_INPUT1_MODE)
#define    PORT235_DSPI_C_SCK_C_LVDS_P        (PORT_ALT2_FUNC_MODE)
#define    PORT235_DSPI_C_SCKC_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT235_DSPI_C_SCKC_IN        (PORT_INPUT1_MODE)
#define    PORT236_GPIO        (PORT_GPIO_MODE)
#define    PORT236_DSPI_C_SINC_IN        (PORT_INPUT1_MODE)
#define    PORT236_DSPI_C_SCK_C_LVDS_N_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT237_GPIO        (PORT_GPIO_MODE)
#define    PORT237_DSPI_C_SOUTC        (PORT_ALT1_FUNC_MODE)
#define    PORT237_DSPI_C_SOUT_C_LVDS_P        (PORT_ALT2_FUNC_MODE)
#define    PORT238_GPIO        (PORT_GPIO_MODE)
#define    PORT238_DSPI_C_PCSC0_INOUT        (PORT_INPUT1_MODE)
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define    PORT238_DSPI_C_SOUT_C_LVDS_N_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT238_DSPI_C_PCSC0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT238_DSPI_C_PCSC0_IN        (PORT_INPUT1_MODE)
#define    PORT239_GPIO        (PORT_GPIO_MODE)
#define    PORT239_DSPI_C_PCSC1        (PORT_ALT1_FUNC_MODE)
#define    PORT239_eSCI_D_TXDD        (PORT_ALT2_FUNC_MODE)
#define    PORT240_GPIO        (PORT_GPIO_MODE)
#define    PORT240_DSPI_C_PCSC2        (PORT_ALT1_FUNC_MODE)
#define    PORT240_DSPI_D_SCK_D_LVDS_P        (PORT_ALT2_FUNC_MODE)
#define    PORT240_DSPI_D_SCKD_INOUT        (PORT_INPUT3_MODE)
#define    PORT240_DSPI_D_SCKD_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT240_DSPI_D_SCKD_IN        (PORT_INPUT3_MODE)
#define    PORT241_GPIO        (PORT_GPIO_MODE)
#define    PORT241_DSPI_C_PCSC3        (PORT_ALT1_FUNC_MODE)
#define    PORT241_DSPI_D_SCK_D_LVDS_N_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT241_DSPI_D_SIND_IN        (PORT_INPUT3_MODE)
#define    PORT242_GPIO        (PORT_GPIO_MODE)
#define    PORT242_DSPI_C_PCSC4        (PORT_ALT1_FUNC_MODE)
#define    PORT242_MCAN_0_TX_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT242_DSPI_D_SOUT_D_LVDS_P        (PORT_ALT3_FUNC_MODE)
#define    PORT242_DSPI_D_SOUTD        (PORT_ALT4_FUNC_MODE)
#define    PORT243_GPIO        (PORT_GPIO_MODE)
#define    PORT243_DSPI_C_PCSC5        (PORT_ALT1_FUNC_MODE)
#define    PORT243_MCAN_0_RX_IN        (PORT_INPUT2_MODE)
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define    PORT243_DSPI_D_SOUT_D_LVDS_N_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT243_DSPI_D_PCSD0_INOUT        (PORT_INPUT4_MODE)
#define    PORT243_DSPI_D_PCSD0_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT243_DSPI_D_PCSD0_IN        (PORT_INPUT4_MODE)
#define    PORT244_GPIO        (PORT_GPIO_MODE)
#define    PORT244_eSCI_C_TXDC        (PORT_ALT1_FUNC_MODE)
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define    PORT244_eQADC_A_eQADC_B_ETRIG0_IN        (PORT_ALT2_FUNC_MODE)
#define    PORT245_GPIO        (PORT_GPIO_MODE)
#define    PORT245_eSCI_C_RXDC_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT246_GPIO        (PORT_GPIO_MODE)
#define    PORT246_FlexCAN_D_CNTXD        (PORT_ALT1_FUNC_MODE)
#define    PORT246_MCAN_1_TX_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT247_GPIO        (PORT_GPIO_MODE)
#define    PORT247_FlexCAN_D_CNRXD_IN        (PORT_INPUT1_MODE)
#define    PORT247_MCAN_1_RX_IN        (PORT_INPUT3_MODE)
#define    PORT248_GPIO        (PORT_GPIO_MODE)
#define    PORT248_FEC_FEC_TXD0_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT248_SENT_A_SENT0_A_IN        (PORT_INPUT2_MODE)
#define    PORT249_GPIO        (PORT_GPIO_MODE)
#define    PORT249_FEC_FEC_RX_DV_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT249_SENT_A_SENT1_A_IN        (PORT_INPUT2_MODE)
#define    PORT250_GPIO        (PORT_GPIO_MODE)
#define    PORT250_FEC_FEC_RXD0_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT250_SENT_A_SENT2_A_IN        (PORT_INPUT2_MODE)
#define    PORT251_GPIO        (PORT_GPIO_MODE)
#define    PORT251_FEC_FEC_TXD1_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT251_SENT_A_SENT3_A_IN        (PORT_INPUT2_MODE)
#define    PORT252_GPIO        (PORT_GPIO_MODE)
#define    PORT252_FEC_FEC_TXEN_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT252_SENT_A_SENT4_A_IN        (PORT_INPUT2_MODE)
#define    PORT253_GPIO        (PORT_GPIO_MODE)
#define    PORT253_FEC_FEC_RXD1_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT253_SENT_A_SENT5_A_IN        (PORT_INPUT2_MODE)
#define    PORT432_GPIO        (PORT_GPIO_MODE)
#define    PORT432_eMIOS_B_EMIOS18_INOUT        (PORT_INPUT1_MODE)
#define    PORT432_DSPI_B_PCSB2        (PORT_ALT2_FUNC_MODE)
#define    PORT432_eMIOS_B_EMIOS18_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT432_eMIOS_B_EMIOS18_IN        (PORT_INPUT1_MODE)
#define    PORT433_GPIO        (PORT_GPIO_MODE)
#define    PORT433_eMIOS_B_EMIOS19_INOUT        (PORT_INPUT1_MODE)
#define    PORT433_DSPI_B_PCSB3        (PORT_ALT2_FUNC_MODE)
#define    PORT433_eMIOS_B_EMIOS19_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT433_eMIOS_B_EMIOS19_IN        (PORT_INPUT1_MODE)
#define    PORT434_GPIO        (PORT_GPIO_MODE)
#define    PORT434_eMIOS_B_EMIOS20_INOUT        (PORT_INPUT1_MODE)
#define    PORT434_DSPI_C_PCSC0_INOUT        (PORT_INPUT2_MODE)
#define    PORT434_eMIOS_B_EMIOS20_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT434_DSPI_C_PCSC0_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT434_eMIOS_B_EMIOS20_IN        (PORT_INPUT1_MODE)
#define    PORT434_DSPI_C_PCSC0_IN        (PORT_INPUT2_MODE)
#define    PORT435_GPIO        (PORT_GPIO_MODE)
#define    PORT435_eMIOS_B_EMIOS21_INOUT        (PORT_INPUT1_MODE)
#define    PORT435_DSPI_C_PCSC1        (PORT_ALT2_FUNC_MODE)
#define    PORT435_eMIOS_B_EMIOS21_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT435_eMIOS_B_EMIOS21_IN        (PORT_INPUT1_MODE)
#define    PORT436_GPIO        (PORT_GPIO_MODE)
#define    PORT436_eMIOS_B_EMIOS22_INOUT        (PORT_INPUT1_MODE)
#define    PORT436_DSPI_C_PCSC2        (PORT_ALT2_FUNC_MODE)
#define    PORT436_eMIOS_B_EMIOS22_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT436_eMIOS_B_EMIOS22_IN        (PORT_INPUT1_MODE)
#define    PORT437_GPIO        (PORT_GPIO_MODE)
#define    PORT437_eMIOS_B_EMIOS23_INOUT        (PORT_INPUT1_MODE)
#define    PORT437_DSPI_C_PCSC5        (PORT_ALT2_FUNC_MODE)
#define    PORT437_eMIOS_B_EMIOS23_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT437_eMIOS_B_EMIOS23_IN        (PORT_INPUT1_MODE)
#define    PORT440_GPI        (PORT_GPIO_MODE)
#define    PORT440_eTPU_C_TCRCLKC_IN        (PORT_INPUT1_MODE)
#define    PORT440_SIU_A_IRQ6_IN        (PORT_INPUT2_MODE)
#define    PORT440_eQADC_B_ANB40_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT441_GPI        (PORT_GPIO_MODE)
#define    PORT441_eTPU_C_ETPUC0_IN        (PORT_INPUT1_MODE)
#define    PORT441_SENT_A_SENT0_A_IN        (PORT_INPUT2_MODE)
#define    PORT441_eQADC_B_ANB41_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT442_GPI        (PORT_GPIO_MODE)
#define    PORT442_eTPU_C_ETPUC1_IN        (PORT_INPUT1_MODE)
#define    PORT442_SENT_A_SENT1_A_IN        (PORT_INPUT2_MODE)
#define    PORT442_eQADC_B_ANB42_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT443_GPIO        (PORT_GPIO_MODE)
#define    PORT443_eTPU_C_ETPUC2_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT443_SENT_A_SENT3_A_IN        (PORT_INPUT2_MODE)
#define    PORT443_eTPU_C_ETPUC2_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT443_eTPU_C_ETPUC2_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT444_GPI        (PORT_GPIO_MODE)
#define    PORT444_eTPU_C_ETPUC3_IN        (PORT_INPUT1_MODE)
#define    PORT444_SENT_A_SENT4_A_IN        (PORT_INPUT2_MODE)
#define    PORT444_eQADC_B_ANB45_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT445_GPIO        (PORT_GPIO_MODE)
#define    PORT445_eTPU_C_ETPUC4_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT445_SENT_A_SENT5_A_IN        (PORT_INPUT2_MODE)
#define    PORT445_eTPU_C_TCRCLKC_IN        (PORT_INPUT3_MODE)
#define    PORT445_eTPU_C_ETPUC4_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT445_eTPU_C_ETPUC4_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT446_GPIO        (PORT_GPIO_MODE)
#define    PORT446_eTPU_C_ETPUC5_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT446_DSPI_E_PCSE2        (PORT_ALT2_FUNC_MODE)
#define    PORT446_SENT_B_SENT0_B_IN        (PORT_INPUT3_MODE)
#define    PORT446_eTPU_C_ETPUC5_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT446_eTPU_C_ETPUC5_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT447_GPIO        (PORT_GPIO_MODE)
#define    PORT447_eTPU_C_ETPUC6_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT447_DSPI_E_PCSE3        (PORT_ALT2_FUNC_MODE)
#define    PORT447_SENT_B_SENT1_B_IN        (PORT_INPUT3_MODE)
#define    PORT447_eTPU_C_ETPUC6_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT447_eTPU_C_ETPUC6_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT448_GPIO        (PORT_GPIO_MODE)
#define    PORT448_eTPU_C_ETPUC7_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT448_DSPI_E_PCSE4        (PORT_ALT2_FUNC_MODE)
#define    PORT448_SENT_B_SENT2_B_IN        (PORT_INPUT3_MODE)
#define    PORT448_eTPU_C_ETPUC7_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT448_eTPU_C_ETPUC7_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT449_GPIO        (PORT_GPIO_MODE)
#define    PORT449_eTPU_C_ETPUC8_INOUT        (PORT_INPUT1_MODE)
#define    PORT449_DSPI_E_PCSE5        (PORT_ALT2_FUNC_MODE)
#define    PORT449_SENT_B_SENT3_B_IN        (PORT_INPUT3_MODE)
#define    PORT449_eTPU_C_ETPUC8_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT449_eTPU_C_ETPUC8_IN        (PORT_INPUT1_MODE)
#define    PORT450_GPI        (PORT_GPIO_MODE)
#define    PORT450_eTPU_C_ETPUC9_IN        (PORT_INPUT1_MODE)
#define    PORT450_SIU_A_IRQ0_IN        (PORT_INPUT2_MODE)
#define    PORT450_SENT_B_SENT4_B_IN        (PORT_INPUT3_MODE)
#define    PORT450_eQADC_B_ANB44_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT451_GPIO        (PORT_GPIO_MODE)
#define    PORT451_eTPU_C_ETPUC10_INOUT        (PORT_INPUT1_MODE)
#define    PORT451_SIU_A_IRQ1_IN        (PORT_INPUT2_MODE)
#define    PORT451_SENT_B_SENT5_B_IN        (PORT_INPUT3_MODE)
#define    PORT451_eTPU_C_ETPUC10_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT451_eTPU_C_ETPUC10_IN        (PORT_INPUT1_MODE)
#define    PORT452_GPIO        (PORT_GPIO_MODE)
#define    PORT452_eTPU_C_ETPUC11_INOUT        (PORT_INPUT1_MODE)
#define    PORT452_SIU_A_IRQ2_IN        (PORT_INPUT2_MODE)
#define    PORT452_eTPU_C_ETPUC11_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT452_eTPU_C_ETPUC11_IN        (PORT_INPUT1_MODE)
#define    PORT453_GPIO        (PORT_GPIO_MODE)
#define    PORT453_eTPU_C_ETPUC12_INOUT        (PORT_INPUT1_MODE)
#define    PORT453_SIU_A_IRQ3_IN        (PORT_INPUT2_MODE)
#define    PORT453_MCAN_1_TX_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT453_eTPU_C_ETPUC12_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT453_eTPU_C_ETPUC12_IN        (PORT_INPUT1_MODE)
#define    PORT454_GPIO        (PORT_GPIO_MODE)
#define    PORT454_eTPU_C_ETPUC13_INOUT        (PORT_INPUT1_MODE)
#define    PORT454_SIU_A_IRQ4_IN        (PORT_INPUT2_MODE)
#define    PORT454_PSI5A_SDOUT0_PSI5A_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT454_REACM_RCH0_C_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT454_eTPU_C_ETPUC13_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT454_eTPU_C_ETPUC13_IN        (PORT_INPUT1_MODE)
#define    PORT455_GPIO        (PORT_GPIO_MODE)
#define    PORT455_eTPU_C_ETPUC14_INOUT        (PORT_INPUT1_MODE)
#define    PORT455_SIU_A_IRQ5_IN        (PORT_INPUT2_MODE)
#define    PORT455_PSI5A_SDIN0_PSI5A_IN        (PORT_ALT3_FUNC_MODE)
#define    PORT455_REACM_RCH1_C_OUT        (PORT_ALT4_FUNC_MODE)
#define    PORT455_eTPU_C_ETPUC14_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT455_eTPU_C_ETPUC14_IN        (PORT_INPUT1_MODE)
#define    PORT456_GPIO        (PORT_GPIO_MODE)
#define    PORT456_eTPU_C_ETPUC15_INOUT        (PORT_INPUT1_MODE)
#define    PORT456_MCAN_1_RX_IN        (PORT_INPUT2_MODE)
#define    PORT456_REACM_RCH2_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT456_eTPU_C_ETPUC15_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT456_eTPU_C_ETPUC15_IN        (PORT_INPUT1_MODE)
#define    PORT457_GPIO        (PORT_GPIO_MODE)
#define    PORT457_eTPU_C_ETPUC16_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT457_MCAN_1_TX_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT457_REACM_RCH3_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT457_eTPU_C_ETPUC16_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT457_eTPU_C_ETPUC16_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT458_GPIO        (PORT_GPIO_MODE)
#define    PORT458_eTPU_C_ETPUC17_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT458_eSCI_F_TXDF        (PORT_ALT2_FUNC_MODE)
#define    PORT458_REACM_RCH4_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT458_eTPU_C_ETPUC17_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT458_eTPU_C_ETPUC17_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT459_GPIO        (PORT_GPIO_MODE)
#define    PORT459_eTPU_C_ETPUC18_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT459_eSCI_F_RXDF_IN        (PORT_ALT2_FUNC_MODE)
#define    PORT459_eTPU_C_ETPUC18_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT459_eTPU_C_ETPUC18_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT460_GPIO        (PORT_GPIO_MODE)
#define    PORT460_eTPU_C_ETPUC19_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT460_eSCI_A_TXDA        (PORT_INPUT2_MODE)
#define    PORT460_PSI5A_SDOUT0_PSI5B_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT460_eTPU_C_ETPUC19_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT460_eTPU_C_ETPUC19_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT461_GPIO        (PORT_GPIO_MODE)
#define    PORT461_eTPU_C_ETPUC20_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT461_eSCI_A_RXDA_IN        (PORT_INPUT2_MODE)
#define    PORT461_PSI5A_SDIN0_PSI5B_IN        (PORT_ALT3_FUNC_MODE)
#define    PORT461_eTPU_C_ETPUC20_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT461_eTPU_C_ETPUC20_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT462_GPIO        (PORT_GPIO_MODE)
#define    PORT462_eTPU_C_ETPUC21_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT462_eSCI_B_TXDB        (PORT_INPUT2_MODE)
#define    PORT462_eTPU_C_ETPUC21_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT462_eTPU_C_ETPUC21_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT463_GPIO        (PORT_GPIO_MODE)
#define    PORT463_eTPU_C_ETPUC22_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT463_eSCI_B_RXDB_IN        (PORT_INPUT2_MODE)
#define    PORT463_eTPU_C_ETPUC22_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT463_eTPU_C_ETPUC22_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT464_GPIO        (PORT_GPIO_MODE)
#define    PORT464_eTPU_C_ETPUC23_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT464_DSPI_D_PCSD5        (PORT_ALT2_FUNC_MODE)
#define    PORT464_eQADC_A_MAA0        (PORT_ALT3_FUNC_MODE)
#define    PORT464_eQADC_B_MAB0        (PORT_ALT4_FUNC_MODE)
#define    PORT464_eTPU_C_ETPUC23_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT464_eTPU_C_ETPUC23_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT465_GPIO        (PORT_GPIO_MODE)
#define    PORT465_eTPU_C_ETPUC24_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT465_DSPI_D_PCSD4        (PORT_ALT2_FUNC_MODE)
#define    PORT465_eQADC_A_MAA1        (PORT_ALT3_FUNC_MODE)
#define    PORT465_eQADC_B_MAB1        (PORT_ALT4_FUNC_MODE)
#define    PORT465_eTPU_C_ETPUC24_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT465_eTPU_C_ETPUC24_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT466_GPIO        (PORT_GPIO_MODE)
#define    PORT466_eTPU_C_ETPUC25_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT466_DSPI_D_PCSD3        (PORT_ALT2_FUNC_MODE)
#define    PORT466_eQADC_A_MAA2        (PORT_ALT3_FUNC_MODE)
#define    PORT466_eQADC_B_MAB2        (PORT_ALT4_FUNC_MODE)
#define    PORT466_eTPU_C_ETPUC25_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT466_eTPU_C_ETPUC25_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT467_GPIO        (PORT_GPIO_MODE)
#define    PORT467_eTPU_C_ETPUC26_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT467_DSPI_D_PCSD2        (PORT_ALT2_FUNC_MODE)
#define    PORT467_eQADC_B_MAB0        (PORT_ALT3_FUNC_MODE)
#define    PORT467_eTPU_C_ETPUC26_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT467_eTPU_C_ETPUC26_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT468_GPIO        (PORT_GPIO_MODE)
#define    PORT468_eTPU_C_ETPUC27_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT468_DSPI_D_PCSD1        (PORT_ALT2_FUNC_MODE)
#define    PORT468_REACM_RCH5_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT468_eQADC_B_MAB1        (PORT_ALT4_FUNC_MODE)
#define    PORT468_eTPU_C_ETPUC27_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT468_eTPU_C_ETPUC27_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT469_GPIO        (PORT_GPIO_MODE)
#define    PORT469_eTPU_C_ETPUC28_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT469_DSPI_D_PCSD0_INOUT        (PORT_INPUT2_MODE)
#define    PORT469_REACM_RCH6_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT469_eQADC_B_MAB2        (PORT_ALT4_FUNC_MODE)
#define    PORT469_eTPU_C_ETPUC28_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT469_DSPI_D_PCSD0_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT469_eTPU_C_ETPUC28_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT469_DSPI_D_PCSD0_IN        (PORT_INPUT2_MODE)
#define    PORT470_GPIO        (PORT_GPIO_MODE)
#define    PORT470_eTPU_C_ETPUC29_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT470_DSPI_D_SCKD_INOUT        (PORT_INPUT2_MODE)
#define    PORT470_REACM_RCH7_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT470_eTPU_C_ETPUC29_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT470_DSPI_D_SCKD_OUT        (PORT_ALT2_FUNC_MODE)
#define    PORT470_eTPU_C_ETPUC29_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT470_DSPI_D_SCKD_IN        (PORT_INPUT2_MODE)
#define    PORT471_GPIO        (PORT_GPIO_MODE)
#define    PORT471_eTPU_C_ETPUC30_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT471_DSPI_D_SOUTD        (PORT_ALT2_FUNC_MODE)
#define    PORT471_REACM_RCH8_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT471_eTPU_C_ETPUC30_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT471_eTPU_C_ETPUC30_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT472_GPIO        (PORT_GPIO_MODE)
#define    PORT472_eTPU_C_ETPUC31_INOUT        (PORT_ALT1_FUNC_MODE)
#define    PORT472_DSPI_D_SIND_IN        (PORT_INPUT2_MODE)
#define    PORT472_REACM_RCH9_C_OUT        (PORT_ALT3_FUNC_MODE)
#define    PORT472_eTPU_C_ETPUC31_OUT        (PORT_ALT1_FUNC_MODE)
#define    PORT472_eTPU_C_ETPUC31_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT474_GPI        (PORT_GPIO_MODE)
#define    PORT474_FEC_FEC_TXCLK_REFCLK_IN        (PORT_ALT1_FUNC_MODE)
#define    PORT474_SENT_B_SENT0_B_IN        (PORT_INPUT2_MODE)
#define    PORT475_GPI        (PORT_GPIO_MODE)
#define    PORT475_SENT_A_SENT2_A_IN        (PORT_INPUT1_MODE)
#define    PORT475_eQADC_B_ANB43_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT476_GPI        (PORT_GPIO_MODE)
#define    PORT476_eQADC_B_ANB8_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT476_eTPU_A_ETPUA31_IN        (PORT_INPUT2_MODE)
#define    PORT476_eMIOS_A_EMIOS16_IN        (PORT_INPUT3_MODE)
#define    PORT477_GPI        (PORT_GPIO_MODE)
#define    PORT477_eQADC_B_ANB9_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT477_eTPU_A_ETPUA30_IN        (PORT_INPUT2_MODE)
#define    PORT477_eMIOS_A_EMIOS17_IN        (PORT_INPUT3_MODE)
#define    PORT478_GPI        (PORT_GPIO_MODE)
#define    PORT478_eQADC_B_ANB10_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT478_eTPU_A_ETPUA29_IN        (PORT_INPUT2_MODE)
#define    PORT478_eMIOS_A_EMIOS18_IN        (PORT_INPUT3_MODE)
#define    PORT479_GPI        (PORT_GPIO_MODE)
#define    PORT479_eQADC_B_ANB11_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT479_eTPU_A_ETPUA28_IN        (PORT_INPUT2_MODE)
#define    PORT479_eMIOS_A_EMIOS19_IN        (PORT_INPUT3_MODE)
#define    PORT480_GPI        (PORT_GPIO_MODE)
#define    PORT480_eQADC_B_ANB12_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT480_eTPU_A_ETPUA27_IN        (PORT_INPUT2_MODE)
#define    PORT480_eMIOS_A_EMIOS20_IN        (PORT_INPUT3_MODE)
#define    PORT481_GPI        (PORT_GPIO_MODE)
#define    PORT481_eQADC_B_ANB13_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT481_eTPU_A_ETPUA26_IN        (PORT_INPUT2_MODE)
#define    PORT481_eMIOS_A_EMIOS21_IN        (PORT_INPUT3_MODE)
#define    PORT482_GPI        (PORT_GPIO_MODE)
#define    PORT482_eQADC_B_ANB14_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT482_eTPU_A_ETPUA25_IN        (PORT_INPUT2_MODE)
#define    PORT482_eMIOS_A_EMIOS22_IN        (PORT_INPUT3_MODE)
#define    PORT483_GPI        (PORT_GPIO_MODE)
#define    PORT483_eQADC_B_ANB15_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT483_eTPU_A_ETPUA24_IN        (PORT_INPUT2_MODE)
#define    PORT483_eMIOS_A_EMIOS23_IN        (PORT_INPUT3_MODE)
#define    PORT484_GPI        (PORT_GPIO_MODE)
#define    PORT484_eQADC_B_ANB16_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT484_eTPU_C_ETPUC15_IN        (PORT_INPUT2_MODE)
#define    PORT484_eMIOS_B_EMIOS16_IN        (PORT_INPUT3_MODE)
#define    PORT485_GPI        (PORT_GPIO_MODE)
#define    PORT485_eQADC_B_ANB17_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT485_eTPU_C_ETPUC14_IN        (PORT_INPUT2_MODE)
#define    PORT485_eMIOS_B_EMIOS17_IN        (PORT_INPUT3_MODE)
#define    PORT486_GPI        (PORT_GPIO_MODE)
#define    PORT486_eQADC_B_ANB18_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT486_eTPU_C_ETPUC13_IN        (PORT_INPUT2_MODE)
#define    PORT486_eMIOS_B_EMIOS18_IN        (PORT_INPUT3_MODE)
#define    PORT487_GPI        (PORT_GPIO_MODE)
#define    PORT487_eQADC_B_ANB19_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT487_eTPU_C_ETPUC12_IN        (PORT_INPUT2_MODE)
#define    PORT487_eMIOS_B_EMIOS19_IN        (PORT_INPUT3_MODE)
#define    PORT488_GPI        (PORT_GPIO_MODE)
#define    PORT488_eQADC_B_ANB20_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT488_eTPU_C_ETPUC11_IN        (PORT_INPUT2_MODE)
#define    PORT488_eMIOS_B_EMIOS20_IN        (PORT_INPUT3_MODE)
#define    PORT489_GPI        (PORT_GPIO_MODE)
#define    PORT489_eQADC_B_ANB21_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT489_eTPU_C_ETPUC10_IN        (PORT_INPUT2_MODE)
#define    PORT489_eMIOS_B_EMIOS21_IN        (PORT_INPUT3_MODE)
#define    PORT490_GPI        (PORT_GPIO_MODE)
#define    PORT490_eQADC_B_ANB22_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT490_eTPU_C_ETPUC9_IN        (PORT_INPUT2_MODE)
#define    PORT490_eMIOS_B_EMIOS22_IN        (PORT_INPUT3_MODE)
#define    PORT491_GPI        (PORT_GPIO_MODE)
#define    PORT491_eQADC_B_ANB23_IN        (PORT_ANALOG_INPUT_MODE)
#define    PORT491_eTPU_C_ETPUC8_IN        (PORT_INPUT2_MODE)
#define    PORT491_eMIOS_B_EMIOS23_IN        (PORT_INPUT3_MODE)


/**
* @brief Enable/Disable Development Error Detection
*
* @implements   PORT_DEV_ERROR_DETECT_define
*/
#define PORT_DEV_ERROR_DETECT           (STD_OFF)

/**
* @brief Use/remove Port_SetPinDirection function from the compiled driver
*
* @implements   PORT_SET_PIN_DIRECTION_API_define
*/

#define PORT_SET_PIN_DIRECTION_API      (STD_ON)


/**
* @brief Use/remove Port_SetPinMode function from the compiled driver
*
* @implements   PORT_SET_PIN_MODE_API_define
*/

#define PORT_SET_PIN_MODE_API           (STD_ON)


/**
* @brief Enable/Disable Port_SetPinMode function updating the output level of the pins configured at runtime as GPIO
*/
#define PORT_SETPINMODE_DOES_NOT_TOUCH_GPIO_LEVEL           (STD_OFF)

/**
* @brief Support for User mode.
*        If this parameter has been configured to 'STD_ON', the Port driver code can be executed from both supervisor and user mode.
*
*/
#define PORT_ENABLE_USER_MODE_SUPPORT   (STD_OFF)


/**
* @brief Use/remove Port_GetVersionInfo function from the compiled driver
*
* @implements   PORT_VERSION_INFO_API_define
*/
#define PORT_VERSION_INFO_API           (STD_ON)

/**
* @brief Port Pin symbolic names
* @details Get All Symbolic Names from configuration tool
*
*
*/
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_QF2_AUX_IN  0
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_K5_K6_AUX_IN  1
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_K11_K12_AUX_IN  2
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_QF1_AUX_IN  3
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_CB5_AUX_IN  4
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_K9_K10_AUX_IN  5
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AC_CP_EN  6
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_Door_CON_AUX_IN  7
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_QF3_AUX_IN  8
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_KM2_AUX_IN  9
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_Water_TS_AUX_IN  10
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_KM1_AUX_IN  11
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_RES1_AUX_IN  12
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_FVC1_CB1_IN  13
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_RES3_AUX_IN  14
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_RES2_AUX_IN  15
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_Smoke_Alarm_AUX_IN  16
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_LED1_DRIVE_EN  17
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_LED2_DRIVE_EN  18
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_EMG_STOP_AUX_IN  19
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Chasis_GND_EN  20
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_ISO_SAMPLE_P_EN  21
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_ISO_SAMPLE_N_EN  22
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_ISO_SAMPLE_EN  23
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_BAT_24V_EN  24
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_SN6501_2_EN  25
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K16_LSD_EN  26
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K14_LSD_EN  27
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K15_LSD_EN  28
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K13_LSD_EN  29
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_IN_MUX_2  30
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_IN_MUX_1  31
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_OUT_MUX1_A  32
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_OUT_MUX1_B  33
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_OUT_MUX2_C  34
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_OUT_MUX2_B  35
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_OUT_MUX2_A  36
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_OUT_MUX1_C  37
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_2_EN  38
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_1_EN  39
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_4_EN  40
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_5_EN  41
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_3_EN  42
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K24_LSD_EN  43
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_RES1_LSD_EN  44
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K11_K12_LSD_EN  45
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K23_LSD_EN  46
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K9_K10_LSD_EN  47
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K5_K6_LSD_EN  48
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_CB5_IN_EN  49
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K21_LSD_EN  50
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_QF1_IN_EN  51
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_QF2_IN_EN  52
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K7_K8_LSD_EN  53
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K22_LSD_EN  54
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_QF3_IN_EN  55
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TBOX_Wake_Up_IN  56
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_RES2_Wake_Up_IN  57
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_EEPROM_WP  58
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_RES1_LSD_N  59
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_2_FR  60
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_1_FR  61
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_4_FR  62
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_3_FR  63
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_Global_H_5_FR  64
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K22_LSD_STATUS_IN  65
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K21_LSD_STATUS_IN  66
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_QF3_LSD_STATUS_IN  67
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_QF1_LSD_STATUS_IN  68
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_QF2_LSD_STATUS_IN  69
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K7_K8_STATUS_IN  70
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_CB5_LSD_STATUS_IN  71
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K5_K6_STATUS_IN  72
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K9_K10_STATUS_IN  73
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K23_LSD_STATUS_IN  74
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K11_K12_STATUS_IN  75
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K24_LSD_STATUS_IN  76
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_RES1_LSD_STATUS_IN  77
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K14_LSD_STATUS_IN  78
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K15_LSD_STATUS_IN  79
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K16_LSD_STATUS_IN  80
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_MCU_eSCI_B_EN  81
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_K13_LSD_STATUS_IN  82
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_K7_K8_AUX_IN  83
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_CB6_IN  84
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AD_FVC2_CB2_IN  85
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_LED_HSD_SENSE_EN  86
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_CCU_Wake_Up_EN  87
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_HSD1_12V_SENSE_EN  88
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_BMS_Wake_Up_EN  89
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_HSD2_12V_SENSE_EN  90
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_RES1_HSD2_EN  91
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_RES4_HSD2_EN  92
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_RES2_HSD2_EN  93
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_RES3_HSD2_EN  94
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_HSD_SENSE_SEL0  95
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_HSD_SENSE_SEL1  96
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_HSD_SENSE_SEL2  97
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1044_STB  98
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1042_1_STB  99
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1042_2_STB  100
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1042_3_STB  101
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_SJA1105_RESET  102
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_SN6501_1_EN  103
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_MCU_eSCI_C_EN  104
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_EEPROM_HOLD  105
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_VCC_3V3_EN  106
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_CAN_5V0_EN  107
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_DCDC_11V5_DISABLE  108
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_AUX_EN  109
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1101_EN  110
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1101_RESET  111
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1101_WAKEUP  112
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_DP83822HF_1_RESET  113
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_DP83822HF_1_INT  114
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_TJA1101_INT  115
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_DP83822HF_2_RESET  116
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_DP83822HF_2_INT  117
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_GPIO_VCC_1V2_EN  118
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EXT_INT_SBC_INT  119
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_F_TxD  120
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_F_RxD  121
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_B_TxD  122
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_B_RxD  123
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_A_TxD  124
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_A_RxD  125
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_C_TxD  126
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ESCI_MCU_eSCI_C_RxD  127
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_D_SBC_CS  128
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_D_SCK  129
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_D_SDO  130
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_D_SDI  131
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_A_SCK  132
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_A_SDI  133
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_A_SDO  134
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_A_ADS7951_CS  135
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_B_SCK  136
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_B_SDI  137
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_B_SDO  138
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_B_SJA1105_CS  139
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_C_SCK  140
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_C_SDI  141
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_C_SDO  142
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_C_PCA21125_CS  143
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_DSPI_MCU_DSPI_C_EEPROM_CS  144
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN4_PWM_CONTROL  145
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN3_PWM_CONTROL  146
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN2_PWM_CONTROL  147
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN1_PWM_CONTROL  148
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_LED2_PWM_EN  149
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_LED3_PWM_EN  150
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_LED4_PWM_EN  151
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_LED1_PWM_EN  152
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_LED5_PWM_EN  153
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_LED6_PWM_EN  154
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_AC_CP_PWM  155
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN2_PWM_FEEDBACK  156
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN1_PWM_FEEDBACK  157
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN3_PWM_FEEDBACK  158
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_EMIOS_FAN4_PWM_FEEDBACK  159
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_MCAN_MCU_MCAN_1_TxD  160
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_MCAN_MCU_MCAN_1_RxD  161
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_MCAN_MCU_MCAN_0_TxD  162
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_MCAN_MCU_MCAN_0_RxD  163
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SMI_MDC  176
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SMI_MDIO  172
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_RXCLK  173
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_TXCLK  164
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_RxD0  167
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_RxD1  170
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_RxD2  177
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_RxD3  175
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_RX_DV  166
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_TxD0  165
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_TxD1  168
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_TxD2  171
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_TxD3  174
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_ETHERENT_MCU_SJA1105_MII4_TX_EN  169
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_A_TxD  178
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_A_RxD  179
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_B_TxD  180
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_B_RxD  181
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_C_TxD  182
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_C_RxD  183
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_D_TxD  184
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FLEXCAN_MCU_FlexCAN_D_RxD  185
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FCCU_FCCU_0_OUTPUT  186
/**
* @violates @ref PORT_CFG_H_REF_1 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*  ensure that 31 character significance and case sensitivity are supported for external ids
*/
#define PortConfigSet_0_FCCU_FCCU_1_OUTPUT  187


/**
* @brief Number of INMUX registers
* @details Platform constant
*/
#define PORT_NMBR_INMUX_REGS_U16    ((uint16)195)
/**
* @brief Number of available pad modes options
* @details Platform constant
*/
#define PAD_MODE_OPTIONS_U8         ((uint8)10)
/**
* @brief Number of pad 16 blocks
* @details Platform constant
*/
#define PAD_16BLOCK_NO_U8           ((uint8)31)


#define PORT_PRECOMPILE_SUPPORT     (STD_OFF)

/**
* @brief Declaration of config sets for PostBuild configuration
*/
#define PORT_CONFIG_PB
/**
* @brief Number of UnUsed pin array
*/
#define PORT_MAX_UNUSED_PADS_0_U16    (91U)

#define PORT_MAX_UNUSED_PADS_U16   (91U)

/**
* @brief The maximum number of configured pins
*/

#define PORT_MAX_CONFIGURED_PADS_0_U16   ((uint16)188)


#define PORT_MAX_CONFIGURED_PADS_U16   ((uint16)188)

/**
 * @brief Number of IGF configured channels
*/
#define PORT_MAX_CONFIGURED_IGF_CHANNELS_0_U16   (4U)



#if (STD_ON == PORT_SET_PIN_MODE_API)
#define  PORT_INDEX_TABLE_NUM_ENTRIES_U16  ((uint16)(572))
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/
/**
* @brief   Structure needed by @p Port_Init().
* @details The structure @p Port_IgfConfigType is a type for the external data
*          structure containing the initialization data for the IGF IP.
* @note    The user must use the symbolic names defined in the configuration
*          tool.
*
*
* @api
*/
typedef struct
{
    VAR(uint8, AUTOMATIC) u8NumChannels;                                                 /**< @brief Number of used IGF channels (to be configured) */
    P2CONST(Port_Igf_ChannelConfigType, AUTOMATIC, PORT_APPL_CONST) pChannelConfig;      /**< @brief Used IGF channels data configuration */
} Port_IgfConfigType;

/**
* @brief   Structure needed by @p Port_Init().
* @details The structure @p Port_ConfigType is a type for the external data
*          structure containing the initialization data for the PORT Driver.
* @note    The user must use the symbolic names defined in the configuration
*          tool.
*
* @implements Port_ConfigType_struct
*
* @api
*/
typedef struct
{
    VAR(uint16, AUTOMATIC) u16NumPins;                                                   /**< @brief Number of used pads (to be configured) */
    VAR(uint16, AUTOMATIC) u16NumUnusedPins;                                             /**< @brief Number of unused pads */
    P2CONST(uint16, AUTOMATIC, PORT_APPL_CONST) au16UnusedPads;                          /**< @brief Unused pad id's array */
    P2CONST(Port_Siu_UnUsedPinConfigType, AUTOMATIC, PORT_APPL_CONST) pUnusedPadConfig;  /**< @brief Unused pad configuration */
    P2CONST(Port_Siu_PinConfigType, AUTOMATIC, PORT_APPL_CONST) pUsedPadConfig;          /**< @brief Used pads data configuration */
    P2CONST(Port_Siu_PadSelConfigType, AUTOMATIC, PORT_APPL_CONST) pPadSelConfig;        /**< @brief Used pads INMUX configuration */
    VAR(Port_IgfConfigType, AUTOMATIC) IgfConfig;                                        /**< @brief IGF IP configuration structure */
} Port_ConfigType;


/**
* @brief Settings for a INMUX register
* @details The structure @p Port_InMuxSettingType manages ExtraFunctions PinMode.
*
* @api
*/
typedef struct
{
    VAR(uint16,                AUTOMATIC) u16InMuxId;   /**< @brief The id of the INMUX register to be configured */
    VAR(uint8,                 AUTOMATIC) u8InMuxCode;  /**< @brief The value of the INMUX reg for signal allocation */
    VAR(Port_PinDirectionType, AUTOMATIC) eDirection;   /**< @brief The direction of the signal (In, Out, Inout) */
} Port_InMuxSettingType;


/**
* @brief Strucure of an entry in the index table that directs the setting of a pad 
*        functionality to either a Mux or Inmux entry
*
* @api
*/
typedef struct
{
    VAR(uint16, AUTOMATIC) u16PCR;                /**< @brief The PCR number of the register to be configured */
    VAR(uint8,  AUTOMATIC) u8Mode;                /**< @brief The mode value of the pad functionality */
    VAR(uint16, AUTOMATIC) u16IdxMuxOrInmuxTable; /**< @brief Depending on the u8Mode variable, this is the index in Mux or Inmux settings table */
} Port_SettingsIndexType;

/*=================================================================================================
                                 GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"



/**
* @brief External declaration of the Port configuration structures for post-build mode
*/
extern CONST(Port_ConfigType, PORT_CONST) PortConfigSet_0;




#if (STD_ON == PORT_SET_PIN_MODE_API)


/** @brief Port Mux settings data (for pads that do not require setting of Inmux register) */
/*  @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(Port_PinDirectionType,  PORT_CONST) Port_aPadFunctMuxSettings[423];

/** @brief Port Inmux settings data (for pads that do require setting of Inmux register) */
/*  @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(Port_InMuxSettingType,  PORT_CONST) Port_aPadFunctInMuxSettings[149];

/** @brief Pad index data to either Mux settings table or Inmux settings table */
/*  @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(Port_SettingsIndexType, PORT_CONST) Port_aPadFunctIndex[PORT_INDEX_TABLE_NUM_ENTRIES_U16];


#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_16
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#if (STD_ON == PORT_SET_PIN_MODE_API)
/**
* @brief External declaration of the Port pin description array
*
* @violates @ref PORT_CFG_H_REF_4 Objects shall be defined at block scope if they are only accessed
* from within a single function.
*/
extern CONST(uint16, PORT_CONST) Port_au16PinDescription[10][31];
#endif /* (STD_ON == PORT_SET_PIN_MODE_API) */

#define PORT_STOP_SEC_CONFIG_DATA_16
/**
* @violates @ref PORT_CFG_H_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/


#ifdef __cplusplus
}
#endif

#endif /* PORT_CFG_H */

/** @} */

/* End of File */
