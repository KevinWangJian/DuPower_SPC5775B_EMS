/**
*    @file    Gpt_eMios_Irq.h
*    @version 1.0.1
* 
*    @brief   AUTOSAR Gpt - eMIOS header file support for GPT driver.
*    @details eMIOS header file, containing the variables and functions that are exported by the IP driver.
*   
*    @addtogroup GPT_MODULE
*    @{
*/
/*==================================================================================================
*    Project               : AUTOSAR 4.0 MCAL
*    Platform              : PA
*    Peripheral            : eMios_Stm_Pit
*    Dependencies          : none
* 
*    Autosar Version       : 4.0.3
*    Autosar Revision      : ASR_REL_4_0_REV_0003
*    Autosar Conf.Variant  : 
*    SWVersion             : 1.0.1
*    BuildVersion          : MPC5777C_MCAL_1_0_1_RTM_ASR_REL_4_0_REV_0003_20170519
* 
*    (c) Copyright 2006-2016 Freescale Semiconductor, Inc. Freescale Semiconductor Inc. & STMicroelectronics
*    All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef GPT_EMIOS_IRQ_H
#define GPT_EMIOS_IRQ_H

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely 
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section GPT_EMIOS_IRQ_H_REF_1
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header file being included twice
* This is not a violation since all header files are protected against multiple inclusions
* 
*/

/*==================================================================================================
*                                          INCLUDE FILES
*  1) system and project includes
*  2) needed interfaces from external units
*  3) internal and external interfaces from this unit
==================================================================================================*/
#include "Gpt_eMios_Types.h"

/*==================================================================================================
*                                SOURCE FILE VERSION INFORMATION
==================================================================================================*/


#define GPT_EMIOS_IRQ_VENDOR_ID                       43
#define GPT_EMIOS_IRQ_AR_RELEASE_MAJOR_VERSION        4
#define GPT_EMIOS_IRQ_AR_RELEASE_MINOR_VERSION        0
#define GPT_EMIOS_IRQ_AR_RELEASE_REVISION_VERSION     3
#define GPT_EMIOS_IRQ_SW_MAJOR_VERSION                1
#define GPT_EMIOS_IRQ_SW_MINOR_VERSION                0
#define GPT_EMIOS_IRQ_SW_PATCH_VERSION                1
/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if Gpt_eMios_Irq.h file and  Gpt_eMios_Types header file are of the same vendor */
#if (GPT_EMIOS_IRQ_VENDOR_ID != GPT_EMIOS_TYPES_VENDOR_ID)
    #error "Gpt_eMios_Irq.h and Gpt_eMios_Types.h have different vendor IDs"
#endif

#if ((GPT_EMIOS_IRQ_AR_RELEASE_MAJOR_VERSION != GPT_EMIOS_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_EMIOS_IRQ_AR_RELEASE_MINOR_VERSION != GPT_EMIOS_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (GPT_EMIOS_IRQ_AR_RELEASE_REVISION_VERSION != GPT_EMIOS_TYPES_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_eMios_Irq.h and Gpt_eMios_Types.h are different"
#endif

/*Check if Gpt_eMios_Irq.h file and Gpt_eMios_Types header file are of the same Software version*/
#if ((GPT_EMIOS_IRQ_SW_MAJOR_VERSION != GPT_EMIOS_TYPES_SW_MAJOR_VERSION) || \
     (GPT_EMIOS_IRQ_SW_MINOR_VERSION != GPT_EMIOS_TYPES_SW_MINOR_VERSION) || \
     (GPT_EMIOS_IRQ_SW_PATCH_VERSION != GPT_EMIOS_TYPES_SW_PATCH_VERSION))
#error "Software Version Numbers of Gpt_eMios_Irq.h and Gpt_eMios_Types.h are different"
#endif

/*==================================================================================================
*                                            CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                        DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                              ENUMS
==================================================================================================*/

/*==================================================================================================
*                                  STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                  GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/


/*==================================================================================================
*                                      FUNCTION PROTOTYPES
==================================================================================================*/
#define GPT_START_SEC_CODE
/*
* @violates @ref GPT_EMIOS_IRQ_H_REF_1 precautions to prevent the
*       contents of a header file being included twice  */
#include "MemMap.h"


#if (GPT_EMIOS_USED == STD_ON)
FUNC (void, GPT_CODE) Gpt_eMios_ProcessCommonInterrupt(VAR(uint8, AUTOMATIC) u8HwChannel);
#endif /*GPT_EMIOS_USED == STD_ON*/

#define GPT_STOP_SEC_CODE
/*
* @violates @ref GPT_EMIOS_IRQ_H_REF_1 precautions to prevent the
*       contents of a header file being included twice
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif

#endif  /* GPT_EMIOS_IRQ_H */

/** @} */
