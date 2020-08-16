/**
*   @file Port_Reg_eSys_Siu.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Port - SIU low level driver register defines.
*   @details The description of the registers of the SIU module.
*
*   @addtogroup Siu
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

#ifndef PORT_REG_ESYS_SIU_H
#define PORT_REG_ESYS_SIU_H
#ifdef __cplusplus
extern "C"{
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Port_Reg_eSys_Siu_H_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers(internal and external) shall not rely 
* on the significance of more than 31 characters.The used compilers use more than 31 chars
* for identifiers.
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Reg_eSys.h"
#include "Siu_IpVersion.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define PORT_REGESYS_SIU_VENDOR_ID                    43
#define PORT_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION     4
#define PORT_REGESYS_SIU_AR_RELEASE_MINOR_VERSION     0
#define PORT_REGESYS_SIU_AR_RELEASE_REVISION_VERSION  3
#define PORT_REGESYS_SIU_SW_MAJOR_VERSION             1
#define PORT_REGESYS_SIU_SW_MINOR_VERSION             0
#define PORT_REGESYS_SIU_SW_PATCH_VERSION             1

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((PORT_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (PORT_REGESYS_SIU_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Port_Reg_eSys_Siu.h and Reg_eSys.h are different"
    #endif
#endif

/* Check if the files Port_Reg_eSys_Siu.h and Siu_IpVersion.h are of the same vendor */
#if (PORT_REGESYS_SIU_VENDOR_ID != SIU_IPVERSION_VENDOR_ID_REG)
    #error "Port_Reg_eSys_Siu.h and Siu_IpVersion.h have different vendor ids"
#endif
/* Check if the files Port_Reg_eSys_Siu.h and Siu_IpVersion.h are of the same Autosar version */
#if ((PORT_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION    != SIU_IPVERSION_AR_RELEASE_MAJOR_VERSION_REG) || \
     (PORT_REGESYS_SIU_AR_RELEASE_MINOR_VERSION    != SIU_IPVERSION_AR_RELEASE_MINOR_VERSION_REG) || \
     (PORT_REGESYS_SIU_AR_RELEASE_REVISION_VERSION != SIU_IPVERSION_AR_RELEASE_REVISION_VERSION_REG) \
    )
  #error "AutoSar Version Numbers of Port_Reg_eSys_Siu.h and Siu_IpVersion.h are different"
#endif
/* Check if the files Port_Reg_eSys_Siu.h and Siu_IpVersion.h are of the same software version */
#if ((PORT_REGESYS_SIU_SW_MAJOR_VERSION != SIU_IPVERSION_SW_MAJOR_VERSION_REG) || \
     (PORT_REGESYS_SIU_SW_MINOR_VERSION != SIU_IPVERSION_SW_MINOR_VERSION_REG) || \
     (PORT_REGESYS_SIU_SW_PATCH_VERSION != SIU_IPVERSION_SW_PATCH_VERSION_REG)    \
    )
  #error "Software Version Numbers of Port_Reg_eSys_Siu.h and Siu_IpVersion.h are different"
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                       DEFINES AND MACROS
=================================================================================================*/


/* @brief Port Control Register (PCR) address for a specific pin. */
/** @violates @ref Port_Reg_eSys_Siu_H_REF_1 Function-like macro defined.*/
#define SIU_PCR_ADDR32(PIN)   ((uint32)SIU_BASEADDR + (uint32)0x40UL + (uint32)((PIN)<<1))

/* @brief Inmux address for a specific pin. */
/** @violates @ref Port_Reg_eSys_Siu_H_REF_1 Function-like macro defined.*/
#define SIU_INMUX_ADDR32(PIN) ((uint32)SIU_BASEADDR + (uint32)0x1200UL + (uint32)((PIN)<<2))

/* @brief GPIO Pad Data Output Register address */
/** @violates @ref Port_Reg_eSys_Siu_H_REF_1 Function-like macro defined.*/
#define SIU_GPDO_ADDR32(PIN)  ((uint32)SIU_BASEADDR + (uint32)0x600UL + (PIN))


/* @brief Mask definitions for PCR bit field OBE and IBE */
#define SIU_PCR_OBE_U16           ((uint16)0x0200)
#define SIU_PCR_OBE_ON_U16        ((uint16)0x0200)

#define SIU_PCR_IBE_U16           ((uint16)0x0100)
#define SIU_PCR_IBE_ON_U16        ((uint16)0x0100)

/* @brief PA bits offset */
#define SIU_PCR_PA_U16            ((uint16)0x1C00)
#define SIU_PCR_PA_OFFSET_U16     ((uint16)10)

/* @brief Muxsel field mask */
#define SIU_INMUX_MUXSEL_MASK_U32 ((uint32)0x00000003)


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/


/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif
/* PORT_REG_ESYS_SIU_H */
#endif
/** @} */
