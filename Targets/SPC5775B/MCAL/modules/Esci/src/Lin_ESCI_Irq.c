/**
*   @file    Lin_ESCI_Irq.c
*   @implements Lin_Esci_Irq.c_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Lin - File used by LIN that contain the ISRs.
*   @details This file contains the ISR functions used to serve the LIN interrupts.
*
*   @addtogroup LIN
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : ESCI
*   Dependencies         : 
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
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Lin_ESCI_Irq_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,
* Precautions shall be taken in order to prevent the contents of a header file
* being included twice This is not a violation since all header files are
* protected against multiple inclusions
*
*
* @section Lin_ESCI_Irq_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include' MemMap.h included after each section define in order to set
* the current memory section
*
* @section Lin_ESCI_Irq_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, Casting operation to a pointer.
* This violation is due to the Casting pointers to other types used in macros
* for Reading or writing data from address location of controller register
*
* section Lin_ESCI_Irq_c_REF_4
* Violates MISRA 2004 Required Rule 8.1, Functions defined without a prototype in scope.
*
* @section Lin_ESCI_Irq_c_REF_5
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* This violation is due to the requirement that request to have a file version check.
*
* @section Lin_ESCI_Irq_c_REF_6
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal
* and external) shall not rely on the significance of more
* than 31 characters.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Lin.h"
#include "Lin_ESCI.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define Lin_ESCI_Irq_VENDOR_ID_C                    43
/*
* @violates @ref Lin_ESCI_Irq_c_REF_5 The compiler/linker shall be checked to
* ensure that 31 character signifiance and case sensitivity are supported for
* external identifiers.
*/
/* @violates @ref Lin_ESCI_Irq_c_REF_6 This is required as per Autosar Requirement. */
#define LIN_AR_RELEASE_MAJOR_VERSION_IRQ_C     4
/*
* @violates @ref Lin_ESCI_Irq_c_REF_5 The compiler/linker shall be checked to
* ensure that 31 character signifiance and case sensitivity are supported for
* external identifiers.
*/
/* @violates @ref Lin_ESCI_Irq_c_REF_6 This is required as per Autosar Requirement. */
#define LIN_AR_RELEASE_MINOR_VERSION_IRQ_C     0
/*
* @violates @ref Lin_ESCI_Irq_c_REF_5 The compiler/linker shall be checked to
* ensure that 31 character signifiance and case sensitivity are supported for
* external identifiers.
*/
/* @violates @ref Lin_ESCI_Irq_c_REF_6 This is required as per Autosar Requirement. */
#define LIN_AR_RELEASE_REVISION_VERSION_IRQ_C  3
#define LIN_SW_MAJOR_VERSION_IRQ_C             1
#define LIN_SW_MINOR_VERSION_IRQ_C             0
#define LIN_SW_PATCH_VERSION_IRQ_C             1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Lin header file are of the same vendor */
#if (Lin_ESCI_Irq_VENDOR_ID_C != LIN_VENDOR_ID)
    #error "Lin_ESCI_Irq.c and Lin.h have different vendor ids"
#endif
/* Check if current file and Lin.h header file are of the same Autosar version */
#if (((LIN_AR_RELEASE_MAJOR_VERSION_IRQ_C   != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_AR_RELEASE_MINOR_VERSION_IRQ_C    != LIN_AR_RELEASE_MINOR_VERSION)) || \
     (LIN_AR_RELEASE_REVISION_VERSION_IRQ_C != LIN_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Lin_ESCI_Irq.c and Lin.h are different"
#endif
/* Check if current file and Lin.h header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_IRQ_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_IRQ_C != LIN_SW_MINOR_VERSION) || \
     (LIN_SW_PATCH_VERSION_IRQ_C != LIN_SW_PATCH_VERSION))
    #error "Software Version Numbers of Lin_ESCI_Irq.c and Lin.h are different"
#endif
/* Check if current file and Lin_ESCI header file are of the same vendor */
#if (Lin_ESCI_Irq_VENDOR_ID_C != LIN_VENDOR_ID_ESCI)
    #error "Lin_ESCI_Irq.c and Lin_ESCI.h have different vendor ids"
#endif
/* Check if current file and Lin_ESCI header file are of the same Autosar version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_IRQ_C    != LIN_AR_RELEASE_MAJOR_VERSION_ESCI) || \
     (LIN_AR_RELEASE_MINOR_VERSION_IRQ_C    != LIN_AR_RELEASE_MINOR_VERSION_ESCI) || \
     (LIN_AR_RELEASE_REVISION_VERSION_IRQ_C != LIN_AR_RELEASE_REVISION_VERSION_ESCI))
    #error "AutoSar Version Numbers of Lin_ESCI_Irq.c and Lin_ESCI.h are different"
#endif
/* Check if current file and Lin_ESCI header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_IRQ_C != LIN_SW_MAJOR_VERSION_ESCI) || \
     (LIN_SW_MINOR_VERSION_IRQ_C != LIN_SW_MINOR_VERSION_ESCI) || \
     (LIN_SW_PATCH_VERSION_IRQ_C != LIN_SW_PATCH_VERSION_ESCI))
    #error "Software Version Numbers of Lin_ESCI_Irq.c and Lin_ESCI.h are different"
#endif
/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
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


/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
/**
* @brief          LIN controller interrupts
* @details        LIN controller interrupts
*
*
*
*/
#define LIN_START_SEC_CODE
/*
* @violates @ref Lin_ESCI_Irq_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
/*
* @violates @ref Lin_ESCI_Irq_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
#if defined(eSCI_0)
  ISR(Lin_eSCI_Isr_ESCI_0);
#endif /* defined(eSCI_0) */

#if defined(eSCI_1)
  ISR(Lin_eSCI_Isr_ESCI_1);
#endif /* defined(eSCI_1) */

#if defined(eSCI_2)
  ISR(Lin_eSCI_Isr_ESCI_2);
#endif /* defined(eSCI_2) */

#if defined(eSCI_3)
  ISR(Lin_eSCI_Isr_ESCI_3);
#endif /* defined(eSCI_3) */

#if defined(eSCI_4)
  ISR(Lin_eSCI_Isr_ESCI_4);
#endif /* defined(eSCI_4) */

#if defined(eSCI_5)
  ISR(Lin_eSCI_Isr_ESCI_5);
#endif /* defined(eSCI_5) */

#if defined(eSCI_6)
  ISR(Lin_eSCI_Isr_ESCI_6);
#endif /* defined(eSCI_6) */

#if defined(eSCI_7)
  ISR(Lin_eSCI_Isr_ESCI_7);
#endif /* defined(eSCI_7) */

#if defined(eSCI_8)
  ISR(Lin_eSCI_Isr_ESCI_8);
#endif /* defined(eSCI_8) */

#if defined(eSCI_9)
  ISR(Lin_eSCI_Isr_ESCI_9);
#endif /* defined(eSCI_9) */

#if defined(eSCI_10)
  ISR(Lin_eSCI_Isr_ESCI_10);
#endif /* defined(eSCI_10) */

#if defined(eSCI_11)
  ISR(Lin_eSCI_Isr_ESCI_11);
#endif /* defined(eSCI_11) */

#if defined(LIN_HWCh_0_USE_DMA)
#if (LIN_HWCh_0_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_0);
  ISR(Lin_eSCI_IsrRx_ESCI_0);
#endif /* defined(eSCI_0) */
#endif /* defined(eSCI_0) */

#if defined(LIN_HWCh_1_USE_DMA)
#if (LIN_HWCh_1_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_1);
  ISR(Lin_eSCI_IsrRx_ESCI_1);
#endif /* defined(eSCI_1) */
#endif /* defined(eSCI_1) */

#if defined(LIN_HWCh_2_USE_DMA)
#if (LIN_HWCh_2_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_2);
  ISR(Lin_eSCI_IsrRx_ESCI_2);
#endif /* defined(eSCI_2) */
#endif /* defined(eSCI_2) */

#if defined(LIN_HWCh_3_USE_DMA)
#if (LIN_HWCh_3_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_3);
  ISR(Lin_eSCI_IsrRx_ESCI_3);
#endif /* defined(eSCI_3) */
#endif /* defined(eSCI_3) */

#if defined(LIN_HWCh_4_USE_DMA)
#if (LIN_HWCh_4_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_4);
  ISR(Lin_eSCI_IsrRx_ESCI_4);
#endif /* defined(eSCI_4) */
#endif /* defined(eSCI_4) */

#if defined(LIN_HWCh_5_USE_DMA)
#if (LIN_HWCh_5_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_5);
  ISR(Lin_eSCI_IsrRx_ESCI_5);
#endif /* defined(eSCI_5) */
#endif /* defined(eSCI_5) */

#if defined(LIN_HWCh_6_USE_DMA)
#if (LIN_HWCh_6_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_6);
  ISR(Lin_eSCI_IsrRx_ESCI_6);
#endif /* defined(eSCI_6) */
#endif /* defined(eSCI_6) */

#if defined(LIN_HWCh_7_USE_DMA)
#if (LIN_HWCh_7_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_7);
  ISR(Lin_eSCI_IsrRx_ESCI_7);
#endif /* defined(eSCI_7) */
#endif /* defined(eSCI_7) */

#if defined(LIN_HWCh_8_USE_DMA)
#if (LIN_HWCh_8_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_8);
  ISR(Lin_eSCI_IsrRx_ESCI_8);
#endif /* defined(eSCI_8) */
#endif /* defined(eSCI_8) */

#if defined(LIN_HWCh_9_USE_DMA)
#if (LIN_HWCh_9_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_9);
  ISR(Lin_eSCI_IsrRx_ESCI_9);
#endif /* defined(eSCI_9) */
#endif /* defined(eSCI_9) */

#if defined(LIN_HWCh_10_USE_DMA)
#if (LIN_HWCh_10_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_10);
  ISR(Lin_eSCI_IsrRx_ESCI_10);
#endif /* defined(eSCI_10) */
#endif /* defined(eSCI_10) */

#if defined(LIN_HWCh_11_USE_DMA)
#if (LIN_HWCh_11_USE_DMA == STD_ON)
  ISR(Lin_eSCI_IsrTx_ESCI_11);
  ISR(Lin_eSCI_IsrRx_ESCI_11);
#endif /* defined(eSCI_11) */
#endif /* defined(eSCI_11) */

#define LIN_STOP_SEC_CODE
/*
* @violates @ref Lin_ESCI_Irq_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
/*
* @violates @ref Lin_ESCI_Irq_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 /*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

#define LIN_START_SEC_CODE
/*
* @violates @ref Lin_ESCI_Irq_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
/*
* @violates @ref Lin_ESCI_Irq_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
#if defined(eSCI_0)

    /**
    * @brief   Interrupt handler on ESCI_0.
    * @details This function implements the ISR occurring on ESCI_0.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 0 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_0)
    {
        Lin_ESCI_InterruptHandler(eSCI_0);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_0) */

#if defined(eSCI_1)

    /**
    * @brief   Interrupt handler on ESCI_1.
    * @details This function implements the ISR occurring on ESCI_1.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 1 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_1)
    {
        Lin_ESCI_InterruptHandler(eSCI_1);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_1) */

#if defined(eSCI_2)

    /**
    * @brief   Interrupt handler on ESCI_2.
    * @details This function implements the ISR occurring on ESCI_2.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 2 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_2)
    {
        Lin_ESCI_InterruptHandler(eSCI_2);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_2) */

#if defined(eSCI_3)

    /**
    * @brief   Interrupt handler on ESCI_3.
    * @details This function implements the ISR occurring on ESCI_3.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 3 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_3)
    {
        Lin_ESCI_InterruptHandler(eSCI_3);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_3) */

#if defined(eSCI_4)

    /**
    * @brief   Interrupt handler on ESCI_4.
    * @details This function implements the ISR occurring on ESCI_4.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 4 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_4)
    {
        Lin_ESCI_InterruptHandler(eSCI_4);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_4) */

#if defined(eSCI_5)

    /**
    * @brief   Interrupt handler on ESCI_5.
    * @details This function implements the ISR occurring on ESCI_5.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 5 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_5)
    {
        Lin_ESCI_InterruptHandler(eSCI_5);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_5) */

#if defined(eSCI_6)

    /**
    * @brief   Interrupt handler on ESCI_6.
    * @details This function implements the ISR occurring on ESCI_6.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 6 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_6)
    {
        Lin_ESCI_InterruptHandler(eSCI_6);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_6) */

#if defined(eSCI_7)

    /**
    * @brief   Interrupt handler on ESCI_7.
    * @details This function implements the ISR occurring on ESCI_7.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 7 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_7)
    {
        Lin_ESCI_InterruptHandler(eSCI_7);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_7) */

#if defined(eSCI_8)

    /**
    * @brief   Interrupt handler on ESCI_8.
    * @details This function implements the ISR occurring on ESCI_8.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 8 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_8)
    {
        Lin_ESCI_InterruptHandler(eSCI_8);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_8) */

#if defined(eSCI_9)

    /**
    * @brief   Interrupt handler on ESCI_9.
    * @details This function implements the ISR occurring on ESCI_9.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 9 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_9)
    {
        Lin_ESCI_InterruptHandler(eSCI_9);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_9) */

#if defined(eSCI_10)

    /**
    * @brief   Interrupt handler on ESCI_10.
    * @details This function implements the ISR occurring on ESCI_10.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 10 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_10)
    {
        Lin_ESCI_InterruptHandler(eSCI_10);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_10) */

#if defined(eSCI_11)

    /**
    * @brief   Interrupt handler on ESCI_11.
    * @details This function implements the ISR occurring on ESCI_11.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 11 is used and DMA is not used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_Isr_ESCI_11)
    {
        Lin_ESCI_InterruptHandler(eSCI_11);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* defined(eSCI_11) */

#if defined(LIN_HWCh_0_USE_DMA)
#if (LIN_HWCh_0_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_0.
    * @details This function implements the ISR occurring on ESCI_0.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 0 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_0)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_0);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_0.
    * @details This function implements the ISR occurring on ESCI_0.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 0 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_0)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_0);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_0_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_0_USE_DMA) */

#if defined(LIN_HWCh_1_USE_DMA)
#if (LIN_HWCh_1_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_1.
    * @details This function implements the ISR occurring on ESCI_1.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 1 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_1)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_1);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_1.
    * @details This function implements the ISR occurring on ESCI_1.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 1 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_1)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_1);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_1_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_1_USE_DMA) */

#if defined(LIN_HWCh_2_USE_DMA)
#if (LIN_HWCh_2_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_2.
    * @details This function implements the ISR occurring on ESCI_2.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 2 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_2)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_2);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_2.
    * @details This function implements the ISR occurring on ESCI_2.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 2 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_2)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_2);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_2_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_2_USE_DMA) */

#if defined(LIN_HWCh_3_USE_DMA)
#if (LIN_HWCh_3_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_3.
    * @details This function implements the ISR occurring on ESCI_3.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 3 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_3)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_3);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_3.
    * @details This function implements the ISR occurring on ESCI_3.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 3 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_3)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_3);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_3_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_3_USE_DMA) */

#if defined(LIN_HWCh_4_USE_DMA)
#if (LIN_HWCh_4_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_4.
    * @details This function implements the ISR occurring on ESCI_4.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 4 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_4)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_4);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_4.
    * @details This function implements the ISR occurring on ESCI_4.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 4 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_4)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_4);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_4_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_4_USE_DMA) */

#if defined(LIN_HWCh_5_USE_DMA)
#if (LIN_HWCh_5_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_5.
    * @details This function implements the ISR occurring on ESCI_5.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 5 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_5)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_5);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_5.
    * @details This function implements the ISR occurring on ESCI_5.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 5 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_5)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_5);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_5_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_5_USE_DMA) */

#if defined(LIN_HWCh_6_USE_DMA)
#if (LIN_HWCh_6_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_6.
    * @details This function implements the ISR occurring on ESCI_6.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 6 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_6)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_6);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_6.
    * @details This function implements the ISR occurring on ESCI_6.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 6 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_6)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_6);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_6_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_6_USE_DMA) */

#if defined(LIN_HWCh_7_USE_DMA)
#if (LIN_HWCh_7_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_7.
    * @details This function implements the ISR occurring on ESCI_7.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 7 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_7)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_7);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_7.
    * @details This function implements the ISR occurring on ESCI_7.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 7 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_7)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_7);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_7_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_7_USE_DMA) */

#if defined(LIN_HWCh_8_USE_DMA)
#if (LIN_HWCh_8_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_8.
    * @details This function implements the ISR occurring on ESCI_8.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 8 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_8)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_8);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_8.
    * @details This function implements the ISR occurring on ESCI_8.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 8 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_8)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_8);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_8_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_8_USE_DMA) */

#if defined(LIN_HWCh_9_USE_DMA)
#if (LIN_HWCh_9_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_9.
    * @details This function implements the ISR occurring on ESCI_9.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 9 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_9)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_9);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_9.
    * @details This function implements the ISR occurring on ESCI_9.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 9 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_9)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_9);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_9_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_9_USE_DMA) */

#if defined(LIN_HWCh_10_USE_DMA)
#if (LIN_HWCh_10_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_10.
    * @details This function implements the ISR occurring on ESCI_10.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 10 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_10)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_10);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_10.
    * @details This function implements the ISR occurring on ESCI_10.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 10 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_10)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_10);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_10_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_10_USE_DMA) */

#if defined(LIN_HWCh_11_USE_DMA)
#if (LIN_HWCh_11_USE_DMA == STD_ON)

    /**
    * @brief   Tx interrupt handler on ESCI_11.
    * @details This function implements the ISR occurring on ESCI_11.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 11 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrTx_ESCI_11)
    {
        Lin_ESCI_TxInterruptHandler_eDma(eSCI_11);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

    /**
    * @brief   Rx interrupt handler on ESCI_11.
    * @details This function implements the ISR occurring on ESCI_11.
    * @note    This interrupt handlers is only present if Hardware
    *          Channel 11 is used and DMA is used.
    * @isr
    *
    *
    */
    /*
    * @violates @ref Lin_ESCI_Irq_c_REF_4 Required Rule 8.1, Functions defined without a prototype in scope
    */
    ISR(Lin_eSCI_IsrRx_ESCI_11)
    {
        Lin_ESCI_RxInterruptHandler_eDma(eSCI_11);
        /*
        * @violates @ref Lin_ESCI_Irq_c_REF_3 Cast from unsigned long to pointer
        */
        EXIT_INTERRUPT();
    }

#endif /* (LIN_HWCh_11_USE_DMA == STD_ON) */
#endif /* defined(LIN_HWCh_11_USE_DMA) */

#define LIN_STOP_SEC_CODE
/*
* @violates @ref Lin_ESCI_Irq_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
/*
* @violates @ref Lin_ESCI_Irq_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
#ifdef __cplusplus
}
#endif
/** @} */
