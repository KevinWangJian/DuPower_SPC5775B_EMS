/**
*   @file Port_Reg_eSys_Igf.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Port - IGF low level driver register defines.
*   @details The description of the registers of the IGF module.
*
*   @addtogroup Igf
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

#ifndef PORT_REG_ESYS_IGF_H
#define PORT_REG_ESYS_IGF_H
#ifdef __cplusplus
extern "C"{
#endif
/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Port_Reg_eSys_IGF_H_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Port_Reg_eSys_IGF_H_REF_2
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* The used compilers/linkers allow more than 31 characters significance for external identifiers.
*
* @section Port_Reg_eSys_IGF_H_REF_3
* Violates MISRA 2004 Required Rule 8.12, When an array is declared with external linkage, its size 
* shall be stated explicitly or defined implicitly by initialisation.
* This violation is needed because the array sizes are decided by configuration but care
* is taken in code to respect the array bounds.
*
* @section Port_Reg_eSys_IGF_H_REF_4
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section Port_Reg_eSys_IGF_H_REF_5
* Violates MISRA 2004 Required Rule 8.7,
* Objects shall be defined at block scope if they are only accessed from within a single function.
* These objects are used in various parts of the code.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers(internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars
* for identifiers.
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

#define PORT_REGESYS_IGF_VENDOR_ID                    43
#define PORT_REGESYS_IGF_AR_RELEASE_MAJOR_VERSION     4
/* @violates @ref Port_Reg_eSys_IGF_H_REF_2 Violates MISRA 2004 Required Rule 1.4 */
#define PORT_REGESYS_IGF_AR_RELEASE_MINOR_VERSION     0
#define PORT_REGESYS_IGF_AR_RELEASE_REVISION_VERSION  3
#define PORT_REGESYS_IGF_SW_MAJOR_VERSION             1
#define PORT_REGESYS_IGF_SW_MINOR_VERSION             0
#define PORT_REGESYS_IGF_SW_PATCH_VERSION             1

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((PORT_REGESYS_IGF_AR_RELEASE_MAJOR_VERSION != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
         (PORT_REGESYS_IGF_AR_RELEASE_MINOR_VERSION != REG_ESYS_AR_RELEASE_MINOR_VERSION)    \
        )
        #error "AutoSar Version Numbers of Port_Reg_eSys_Igf.h and Reg_eSys.h are different"
    #endif
#endif

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                       DEFINES AND MACROS
=================================================================================================*/

/* @violates @ref Port_Reg_eSys_IGF_H_REF_1 Function-like macro defined.*/
#define IGF_MCR_ADDR32(mIdx, chIdx)     (IGF_BASE_ADDR32[(mIdx)] +(uint32)((uint32)(chIdx)<<(6UL)) + 0x00UL)

/* @violates @ref Port_Reg_eSys_IGF_H_REF_1 Function-like macro defined.*/
#define IGF_MSR_ADDR32(mIdx, chIdx)     (IGF_BASE_ADDR32[(mIdx)] +(uint32)((uint32)(chIdx)<<(6UL)) + 0x04UL)

/* @violates @ref Port_Reg_eSys_IGF_H_REF_1 Function-like macro defined.*/
#define IGF_PRESR_ADDR32(mIdx, chIdx)   (IGF_BASE_ADDR32[(mIdx)] +(uint32)((uint32)(chIdx)<<(6UL)) + 0x10UL)

/* @violates @ref Port_Reg_eSys_IGF_H_REF_1 Function-like macro defined.*/
#define IGF_RTH_ADDR32(mIdx, chIdx)     (IGF_BASE_ADDR32[(mIdx)] +(uint32)((uint32)(chIdx)<<(6UL)) + 0x1CUL)

/* @violates @ref Port_Reg_eSys_IGF_H_REF_1 Function-like macro defined.*/
#define IGF_FTH_ADDR32(mIdx, chIdx)     (IGF_BASE_ADDR32[(mIdx)] +(uint32)((uint32)(chIdx)<<(6UL)) + 0x20UL)


/* @brief Mask definitions for MCR bit field FGEN */
#define IGF_MCR_FGEN_U32                ((uint32)0x00000040)
#define IGF_MCR_FGEN_ON_U32             ((uint32)0x00000040)

/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/


/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/
#define PORT_START_SEC_CONST_32
/**
@violates @ref Port_Reg_eSys_IGF_H_REF_4 Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"
/**
* @brief IGF base address array declaration
*/
/**
@violates @ref Port_Reg_eSys_IGF_H_REF_3 Array size shall be stated explicitly
@violates @ref Port_Reg_eSys_IGF_H_REF_5 Objects shall be defined at block scope if they are only accessed from within a single function.
*/
extern CONST(uint32, IGF_CONST) IGF_BASE_ADDR32[];
#define PORT_STOP_SEC_CONST_32
/**
@violates @ref Port_Reg_eSys_IGF_H_REF_4 Violates MISRA 2004 Advisory Rule 19.15, Repeated include file MemMap.h
*/
#include "MemMap.h"

/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#ifdef __cplusplus
}
#endif
/* PORT_REG_ESYS_IGF_H */
#endif
/** @} */
