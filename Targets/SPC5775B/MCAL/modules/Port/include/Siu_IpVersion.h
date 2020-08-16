/**
*   @file Siu_IpVersion.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Port - SIU low level driver register defines.
*   @details The description of the registers of the SIU module.
*
*   @addtogroup SIU
*   @{
*/
/*==================================================================================================
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
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef Siu_IpVersion_H
#define Siu_IpVersion_H
#ifdef __cplusplus
extern "C"{
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on
* the significance of more than 31 characters. The used compilers use more than 31 chars for  identifiers.
*
*/


/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/

#include "Soc_Ips.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define SIU_IPVERSION_VENDOR_ID_REG                    43
#define SIU_IPVERSION_AR_RELEASE_MAJOR_VERSION_REG     4
#define SIU_IPVERSION_AR_RELEASE_MINOR_VERSION_REG     0
#define SIU_IPVERSION_AR_RELEASE_REVISION_VERSION_REG  3
#define SIU_IPVERSION_SW_MAJOR_VERSION_REG             1
#define SIU_IPVERSION_SW_MINOR_VERSION_REG             0
#define SIU_IPVERSION_SW_PATCH_VERSION_REG             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((SIU_IPVERSION_AR_RELEASE_MAJOR_VERSION_REG != SOC_IPS_AR_RELEASE_MAJOR_VERSION) || \
         (SIU_IPVERSION_AR_RELEASE_MINOR_VERSION_REG != SOC_IPS_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Siu_IpVersion.h and Soc_Ips.h are different"
    #endif
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

#ifdef IPV_SIU 
/* @brief SIU IP Version: siu_ipi.00.02.09.00  - Mamba */
    #define IPV_SIU_00_02_09_00    (0x00020900UL)
/* @brief SIU IP Version: siu_ipi.00.01.23.45  - Cobra55 */
    #define IPV_SIU_00_01_23_45    (0x00012345UL)
#endif

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
/* Siu_IpVersion_H */
#endif
/** @} */
