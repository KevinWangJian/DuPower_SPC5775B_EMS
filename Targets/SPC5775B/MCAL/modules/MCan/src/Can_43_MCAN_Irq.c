/**
*   @file    Can_43_MCAN_Irq.c
*   @implements Can_43_MCAN_Irq.c_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR MCan - module interface
*   @details Interrupt routines for Can driver.
*
*   @addtogroup CAN_DRIVER
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MCAN
*   Dependencies         : 
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_HF1_ASR_REL_4_0_REV_0003_20170606
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
* @section Can_43_MCAN_Irq_c_REF_1
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Can_43_MCAN_Irq_c_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
* There are different kinds of execution code sections
*
* @section Can_43_MCAN_Irq_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This macro compute the address of any register by using the hardware ofsset of the controller. The address calculated as an unsigned int
* is passed to  a macro for initializing the pointer with that address. (ex: see REG_WRITE32 macro).
*
* @section Can_43_MCAN_Irq_c_REF_5
* Violates MISRA 2004 Advisory Rule 19.1,#include preceded by non preproc directives.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section Can_43_MCAN_Irq_c_REF_9
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the significance
* of more than 31 characters.
* The long identifiers are maintained for better readability.
*
* @section Can_43_MCAN_Irq_c_REF_11
* Violates MISRA 2004 Required Rule 8.10, This function is used for interrupt routine, but tools report that this was use
* only in this function. This is not an error.
*
* @section Can_43_MCAN_Irq_c_REF_12
* Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between a pointer type and an integral type.
*
*
*/

/*
(CAN035) The module Can_43_MCAN_Irq.c contains the implementation of interrupt frames.The implementation of the interrupt service routine shall be in Can.c
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/*
* @file           Can_43_MCAN_Irq.c
*/
#include "Can_43_MCAN.h"
#include "Can_43_MCAN_IPW.h"
#include "Reg_eSys_MCan.h"
#include "CanIf_Cbk.h"
#include "Mcal.h"
#if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
  #include "Det.h"
#endif

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/* The integration of incompatible files shall be avoided. */
#define CAN_43_MCAN_VENDOR_ID_IRQ_C                      43
/* @violates @ref Can_43_MCAN_Irq_c_REF_9 Violates MISRA 2004 Required Rule 5.1, The long identifiers are maintained for better readability. */
#define CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_IRQ_C       4
/* @violates @ref Can_43_MCAN_Irq_c_REF_9 Violates MISRA 2004 Required Rule 5.1, The long identifiers are maintained for better readability. */
#define CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_IRQ_C       0
/* @violates @ref Can_43_MCAN_Irq_c_REF_9 Violates MISRA 2004 Required Rule 5.1, The long identifiers are maintained for better readability. */
#define CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_IRQ_C    3
#define CAN_43_MCAN_SW_MAJOR_VERSION_IRQ_C               1
#define CAN_43_MCAN_SW_MINOR_VERSION_IRQ_C               0
#define CAN_43_MCAN_SW_PATCH_VERSION_IRQ_C               1


/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CAN header file are of the same vendor */
#if (CAN_43_MCAN_VENDOR_ID_IRQ_C != CAN_43_MCAN_VENDOR_ID)
    #error "Can_43_MCAN_Irq.c and Can_43_MCAN.h have different vendor ids"
#endif
/* Check if current file and CAN header file are of the same Autosar version */
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_IRQ_C    != CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_IRQ_C    != CAN_43_MCAN_AR_RELEASE_MINOR_VERSION) || \
     (CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_IRQ_C != CAN_43_MCAN_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Can_43_MCAN_Irq.c and Can_43_MCAN.h are different"
#endif
/* Check if current file and CAN header file are of the same Software version */
#if ((CAN_43_MCAN_SW_MAJOR_VERSION_IRQ_C != CAN_43_MCAN_SW_MAJOR_VERSION) || \
     (CAN_43_MCAN_SW_MINOR_VERSION_IRQ_C != CAN_43_MCAN_SW_MINOR_VERSION) || \
     (CAN_43_MCAN_SW_PATCH_VERSION_IRQ_C != CAN_43_MCAN_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Can_43_MCAN_Irq.c and Can_43_MCAN.h are different"
#endif

/* Check if current file and CAN_IPW header file are of the same vendor */
#if (CAN_43_MCAN_VENDOR_ID_IRQ_C != CAN_43_MCAN_IPW_VENDOR_ID_H)
    #error "Can_43_MCAN_Irq.c and Can_43_MCAN_IPW.h have different vendor ids"
#endif
/* Check if current file and CAN_IPW header file are of the same Autosar version */
#if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_IRQ_C    != CAN_43_MCAN_IPW_AR_RELEASE_MAJOR_VERSION_H) || \
     (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_IRQ_C    != CAN_43_MCAN_IPW_AR_RELEASE_MINOR_VERSION_H) || \
     (CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_IRQ_C != CAN_43_MCAN_IPW_AR_RELEASE_REVISION_VERSION_H) \
    )
    #error "AutoSar Version Numbers of Can_43_MCAN_Irq.c and Can_43_MCAN_IPW.h are different"
#endif
/* Check if current file and CAN_IPW header file are of the same Software version */
#if ((CAN_43_MCAN_SW_MAJOR_VERSION_IRQ_C != CAN_43_MCAN_IPW_SW_MAJOR_VERSION_H) || \
     (CAN_43_MCAN_SW_MINOR_VERSION_IRQ_C != CAN_43_MCAN_IPW_SW_MINOR_VERSION_H) || \
     (CAN_43_MCAN_SW_PATCH_VERSION_IRQ_C != CAN_43_MCAN_IPW_SW_PATCH_VERSION_H) \
    )
    #error "Software Version Numbers of Can_43_MCAN_Irq.c and Can_43_MCAN_IPW.h are different"
#endif
/* Check if current file and DET header file are of the same version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
/* DET */
  #if (CAN_43_MCAN_DEV_ERROR_DETECT == STD_ON)
    #if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_IRQ_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_IRQ_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Can_43_MCAN_Irq.c and Det.h are different"
    #endif
  #endif
/* CanIf_Cbk */
  #if ( (CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_IRQ_C != CANIF_CBK_AR_RELEASE_MAJOR_VERSION) || \
        (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_IRQ_C != CANIF_CBK_AR_RELEASE_MINOR_VERSION) \
      )
        #error "AutoSar Version Numbers of Can_43_MCAN_Irq.c and CanIf_Cbk.h are different"
  #endif
/* Mcal.h */
  #if ((CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
       (CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_IRQ_C != MCAL_AR_RELEASE_MINOR_VERSION) \
      )
        #error "Software Version Numbers of Can_43_MCAN_Irq.c and Mcal.h are different"
  #endif
/* Ecum */
#endif

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

#define CAN_43_MCAN_START_SEC_CODE

/* @violates @ref Can_43_MCAN_Irq_c_REF_5 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_43_MCAN_Irq_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h  */
#include "MemMap.h"


/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef CAN_43_MCAN_INTERRUPT_SUPPORTED
#if (STD_ON == CAN_43_MCAN_INTERRUPT_SUPPORTED)

#ifdef CAN_43_MCAN_COMBINED_INTERRUPT
    #if (STD_ON == CAN_43_MCAN_COMBINED_INTERRUPT)
        #if ((CAN_43_MCAN_IRQ_MCAN1_LINE_0_ENABLE == STD_ON) || (CAN_43_MCAN_IRQ_MCAN2_LINE_0_ENABLE == STD_ON))
            ISR(Can_IsrCombined_IL0);
        #endif
        #if ((CAN_43_MCAN_IRQ_MCAN1_LINE_1_ENABLE == STD_ON) || (CAN_43_MCAN_IRQ_MCAN2_LINE_1_ENABLE == STD_ON))
            ISR(Can_IsrCombined_IL1);
        #endif
    #endif
#endif

#if ((!defined (CAN_43_MCAN_COMBINED_INTERRUPT)) || (CAN_43_MCAN_COMBINED_INTERRUPT == STD_OFF))
#ifdef CAN_43_MCAN_FCA_INDEX
    #if (CAN_43_MCAN_IRQ_MCAN1_LINE_0_ENABLE == STD_ON)
        ISR(Can_IsrFCA_IL0);
    #endif

    #if (CAN_43_MCAN_IRQ_MCAN1_LINE_1_ENABLE == STD_ON)
        ISR(Can_IsrFCA_IL1);
    #endif

#endif

#ifdef CAN_43_MCAN_FCB_INDEX

   #if (CAN_43_MCAN_IRQ_MCAN2_LINE_0_ENABLE == STD_ON)
        ISR(Can_IsrFCB_IL0);
    #endif

   #if (CAN_43_MCAN_IRQ_MCAN2_LINE_1_ENABLE == STD_ON)
        ISR(Can_IsrFCB_IL1);
    #endif

#endif


#ifdef CAN_43_MCAN_FCC_INDEX

   #if (CAN_43_MCAN_IRQ_MCAN3_LINE_0_ENABLE == STD_ON)
        ISR(Can_IsrFCC_IL0);
    #endif

    #if (CAN_43_MCAN_IRQ_MCAN3_LINE_1_ENABLE == STD_ON)
        ISR(Can_IsrFCC_IL1);
    #endif

#endif


#ifdef CAN_43_MCAN_FCD_INDEX 

   #if (CAN_43_MCAN_IRQ_MCAN4_LINE_0_ENABLE == STD_ON)
        ISR(Can_IsrFCD_IL0);
    #endif

    #if (CAN_43_MCAN_IRQ_MCAN4_LINE_1_ENABLE == STD_ON)
        ISR(Can_IsrFCD_IL1);
    #endif

#endif

#ifdef CAN_43_MCAN_FCE_INDEX

   #if (CAN_43_MCAN_IRQ_MTTCAN_0_LINE_0_ENABLE == STD_ON)
        ISR(Can_IsrFCE_IL0);
    #endif

    #if (CAN_43_MCAN_IRQ_MTTCAN_0_LINE_1_ENABLE == STD_ON)
        ISR(Can_IsrFCE_IL1);
    #endif
    
#endif
#endif
/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR COMBINED INTERRUPT
==================================================================================================*/
#ifdef CAN_43_MCAN_COMBINED_INTERRUPT
#if(CAN_43_MCAN_COMBINED_INTERRUPT == STD_ON)
#if ((CAN_43_MCAN_IRQ_MCAN1_LINE_0_ENABLE == STD_ON) || (CAN_43_MCAN_IRQ_MCAN2_LINE_0_ENABLE == STD_ON))
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrCombined_IL0)
        {
#ifdef MCAN_1_OFFSET
            /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
            if ((uint32)0UL != ((REG_READ32( MCAN_IR(MCAN_1_OFFSET))) & (MCAN_INTERRUPT_MASK_U32)))
            {
                /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
                Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCA_INDEX);
            }
#endif
#ifdef MCAN_2_OFFSET
            /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
            if ((uint32)0UL != ((REG_READ32( MCAN_IR(MCAN_2_OFFSET))) & (MCAN_INTERRUPT_MASK_U32)))
            {
                /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
                Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCB_INDEX);
            }
#endif
            EXIT_INTERRUPT();
        }
#endif
#if ((CAN_43_MCAN_IRQ_MCAN1_LINE_1_ENABLE == STD_ON) || (CAN_43_MCAN_IRQ_MCAN2_LINE_1_ENABLE == STD_ON))
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrCombined_IL1)
        {
#ifdef MCAN_1_OFFSET
            /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
            if ((uint32)0UL != ((REG_READ32( MCAN_IR(MCAN_1_OFFSET))) & (MCAN_INTERRUPT_MASK_U32)))
            {
                /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
                Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCA_INDEX);
            }
#endif
#ifdef MCAN_2_OFFSET
            /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
            /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
            if ((uint32)0UL != ((REG_READ32( MCAN_IR(MCAN_2_OFFSET))) & (MCAN_INTERRUPT_MASK_U32)))
            {
                /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
                /* @violates @ref Can_43_MCAN_Irq_c_REF_12 Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed */
                Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCB_INDEX);
            }
#endif
            EXIT_INTERRUPT();
        }
#endif
#endif
#endif
/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR MCAN 1
==================================================================================================*/
#if ((!defined (CAN_43_MCAN_COMBINED_INTERRUPT)) || (CAN_43_MCAN_COMBINED_INTERRUPT == STD_OFF))
#ifdef CAN_43_MCAN_FCA_INDEX

    #if (CAN_43_MCAN_IRQ_MCAN1_LINE_0_ENABLE == STD_ON)       
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCA_IL0) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCA_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

     #if (CAN_43_MCAN_IRQ_MCAN1_LINE_1_ENABLE == STD_ON)        
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCA_IL1) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCA_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

#endif

/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR MCAN 2
==================================================================================================*/

#ifdef CAN_43_MCAN_FCB_INDEX

   #if (CAN_43_MCAN_IRQ_MCAN2_LINE_0_ENABLE == STD_ON)        
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCB_IL0) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCB_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

   #if (CAN_43_MCAN_IRQ_MCAN2_LINE_1_ENABLE == STD_ON)      
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCB_IL1) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCB_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

#endif

/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR MCAN 3
==================================================================================================*/

#ifdef CAN_43_MCAN_FCC_INDEX

  #if (CAN_43_MCAN_IRQ_MCAN3_LINE_0_ENABLE == STD_ON)        
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCC_IL0) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCC_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

    #if (CAN_43_MCAN_IRQ_MCAN3_LINE_1_ENABLE == STD_ON)        
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCC_IL1) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCC_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

#endif

/*==================================================================================================
    INTERRUPT SERVICE ROUTINES FOR MCAN 4
==================================================================================================*/

#ifdef CAN_43_MCAN_FCD_INDEX

   #if (CAN_43_MCAN_IRQ_MCAN4_LINE_0_ENABLE == STD_ON)        
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCD_IL0) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCD_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

   #if (CAN_43_MCAN_IRQ_MCAN4_LINE_1_ENABLE == STD_ON)        
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCD_IL1) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCD_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

#endif

#ifdef CAN_43_MCAN_FCE_INDEX

   #if (CAN_43_MCAN_IRQ_MTTCAN_0_LINE_0_ENABLE == STD_ON)
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCE_IL0) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCE_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

   #if (CAN_43_MCAN_IRQ_MTTCAN_0_LINE_1_ENABLE == STD_ON)
        /* @violates @ref Can_43_MCAN_Irq_c_REF_3 Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer. */
        /* @violates @ref Can_43_MCAN_Irq_c_REF_11 Violates MISRA 2004 Required Rule 8.10, global function for interrupt routine. */
        ISR(Can_IsrFCE_IL0) 
        {
            Can_43_MCAN_IPW_Isr_common_process_interrupt(CAN_43_MCAN_FCE_INDEX);
            EXIT_INTERRUPT(); 
        }
    #endif

#endif

#endif
#endif
#endif

#define CAN_STOP_SEC_CODE
/* @violates @ref Can_43_MCAN_Irq_c_REF_5 Violates MISRA 2004 Advisory Rule 19.1, #include preceded by non preproc directives. */
/* @violates @ref Can_43_MCAN_Irq_c_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h */
#include "MemMap.h"

ISR(Can_IsrCombined_IL0_IL1)
{
	Os_Entry_Can_IsrCombined_IL0();
//	Os_Entry_Can_IsrCombined_IL1();
}

#ifdef __cplusplus
}
#endif
/** @} */
