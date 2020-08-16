/**
*   @file Dio_Reg_eSys_Siu.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Dio - SIU low level driver register defines.
*   @details The description of the registers of the SIU module.
*
*   @addtogroup DIO_REG_ESYS_SIU
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

#ifndef DIO_REG_ESYS_SIU_H
#define DIO_REG_ESYS_SIU_H
#ifdef __cplusplus
extern "C"{
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Dio_Reg_eSys_Siu_H_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.

*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Reg_eSys.h"

/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_REGESYS_SIU_VENDOR_ID_REG                    43
#define DIO_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION_REG     4
#define DIO_REGESYS_SIU_AR_RELEASE_MINOR_VERSION_REG     0
#define DIO_REGESYS_SIU_AR_RELEASE_REVISION_VERSION_REG  3
#define DIO_REGESYS_SIU_SW_MAJOR_VERSION_REG             1
#define DIO_REGESYS_SIU_SW_MINOR_VERSION_REG             0
#define DIO_REGESYS_SIU_SW_PATCH_VERSION_REG             1


/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/* Reg_eSys.h version check start */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((DIO_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION_REG != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (DIO_REGESYS_SIU_AR_RELEASE_MINOR_VERSION_REG != REG_ESYS_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Dio_Reg_eSys_Siu.h and Reg_eSys.h are different"
    #endif
#endif
/* Reg_eSys.h version check end */


/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/


/*=================================================================================================
*                               DEFINES AND MACROS
=================================================================================================*/

/* @brief Offset of GPDO Pad Data Output Registers from SIU_BASEADDR*/
#define  SIU_GPDO_OFFSET_U32          ((uint32)0x00000600UL)

/* @brief Offset of GPDI Pad Data Output Registers from SIU_BASEADDR*/
#define  SIU_GPDI_OFFSET_U32          ((uint32)0x00000E00UL)

/* @brief Offset of PGPDO Parallel GPIO Pad Data Output Registers from SIU_BASEADDR*/
#define  SIU_PGPDO_OFFSET_U32         ((uint32)0x00000C00UL)

/* @brief Offset of PGPDI Parallel GPIO Pad Data Input Registers from SIU_BASEADDR*/
#define  SIU_PGPDI_OFFSET_U32         ((uint32)0x00000C40UL)

/* @brief Offset of MPGPDO Masked Parallel GPIO Pad Data Output Registers from SIU_BASEADDR*/
#define  SIU_MPGPDO_OFFSET_U32        ((uint32)0x00000C80UL)

/* @brief GPIO Pad Data Output Register address */
/* @violates @ref Dio_Reg_eSys_Siu_H_REF_1 Function-like macro defined */
#define SIU_GPDO_ADDR8(PIN)  (SIU_BASEADDR + SIU_GPDO_OFFSET_U32 + (PIN))

/* @brief GPIO Pad Data Output Register 0 */
#define SIU_GPDO_PDO_U32           ((uint32)0x01000000UL)

/* @brief GPIO Pad Data Input Register address */
/* @violates @ref Dio_Reg_eSys_Siu_H_REF_1 Function-like macro defined */
#define SIU_GPDI_ADDR8(PIN)  (SIU_BASEADDR + SIU_GPDI_OFFSET_U32 + (PIN))

/* @brief GPIO Pad Data Input Register 0 */
#define SIU_GPDI_PDI_U32           ((uint32)0x01000000UL)

/* @brief Parallel GPIO Pad Data Output Register address */
/* @violates @ref Dio_Reg_eSys_Siu_H_REF_1 Function-like macro defined. */
#define SIU_PGPDO_ADDR32(PGPDO_INDEX)  (SIU_BASEADDR + SIU_PGPDO_OFFSET_U32 + ((uint32)((PGPDO_INDEX) << 1U)))

/* @brief Parallel GPIO Pad Data Input Register address */
/* @violates @ref Dio_Reg_eSys_Siu_H_REF_1 Function-like macro defined. */
#define SIU_PGPDI_ADDR32(PGPDI_INDEX) (SIU_BASEADDR + SIU_PGPDI_OFFSET_U32 + ((uint32)((PGPDI_INDEX) << 1U)))

/* @brief  Masked Parallel GPIO Pad Data Output Register address */
/* @violates @ref Dio_Reg_eSys_Siu_H_REF_1 Function-like macro defined */
#define SIU_MPGPDO_ADDR32(MPGPDO_INDEX)   (SIU_BASEADDR + SIU_MPGPDO_OFFSET_U32 + (MPGPDO_INDEX))

/* @brief  Masked Parallel GPIO Pad Data Output Register(Mask Field) */
#define SIU_MPGPDO_MASK_U32               ((uint32)0xFFFF0000UL)

/* @brief  Masked Parallel Pad Data Out */
#define SIU_MPGPDO_MPPDO_U32              ((uint32)0x0000FFFFUL)


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
/* DIO_REG_ESYS_SIU_H */
#endif
/** @} */
