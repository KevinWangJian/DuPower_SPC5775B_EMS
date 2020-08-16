/**
*   @file    Can_43_MCAN_IPW.h
*   @implements Can_43_MCAN_IPW.h_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR MCan - module interface
*   @details Main header file - can include different IPV models.
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

#ifndef CAN_43_MCAN_IPW_H
#define CAN_43_MCAN_IPW_H

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
* @section [global]
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* The defines are validated.
*
* @section CAN_43_MCAN_IPW_h_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file, 
* Precautions shall be taken in order to prevent the contents of a header file 
* being included twice This is not a violation since all header files are 
* protected against multiple inclusions
*
* @section CAN_43_MCAN_IPW_h_REF_3
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined.
* Middle layer between AUTOSAR and hardware needs a way to map HLD
* functions to LLD functions.
*
* @section CAN_43_MCAN_IPW_h_REF_4
* Violates MISRA 2004 Required Rule 19.10 , In the definition of a function-like macro each instance of 
* a parameter shall be enclosed in parantheses UNLESS it is used as the operand of # or ##.
*
* @section CAN_43_MCAN_IPW_h_REF_5
* Violates MISRA 2004 Required Rule 19.4 , C macros shall only expand to a braced initialiser, a constant, 
* a parenthesised expression, a type qualifier, a storage class specifier, or a do-while-zero construct.
* This violation due to expand expression of funtion macro in BASE when using user mode. This could be skipped. 
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Can_MCan.h"
#include "Can_43_MCAN_Cfg.h"
#include "Reg_eSys.h"
#include "Mcal.h"
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
/**
* @{
* @file           Can_IPW.h
*/
#define CAN_43_MCAN_IPW_VENDOR_ID_H                    43
#define CAN_43_MCAN_IPW_MODULE_ID_H                    80
#define CAN_43_MCAN_IPW_AR_RELEASE_MAJOR_VERSION_H     4
#define CAN_43_MCAN_IPW_AR_RELEASE_MINOR_VERSION_H     0
#define CAN_43_MCAN_IPW_AR_RELEASE_REVISION_VERSION_H  3
#define CAN_43_MCAN_IPW_SW_MAJOR_VERSION_H             1
#define CAN_43_MCAN_IPW_SW_MINOR_VERSION_H             0
#define CAN_43_MCAN_IPW_SW_PATCH_VERSION_H             1
/**@}*/

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and CAN configuration header file are of the same vendor */
#if (CAN_43_MCAN_IPW_VENDOR_ID_H != CAN_43_MCAN_VENDOR_ID_CFG)
#error "Can_43_MCAN_IPW.h and Can_43_MCAN_Cfg.h have different vendor ids"
#endif
/* Check if current file and CAN configuration header file are of the same Autosar version */
#if ((CAN_43_MCAN_IPW_AR_RELEASE_MAJOR_VERSION_H    != CAN_43_MCAN_AR_RELEASE_MAJOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_IPW_AR_RELEASE_MINOR_VERSION_H    != CAN_43_MCAN_AR_RELEASE_MINOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_IPW_AR_RELEASE_REVISION_VERSION_H != CAN_43_MCAN_AR_RELEASE_REVISION_VERSION_CFG_H))
#error "AutoSar Version Numbers of Can_43_MCAN_IPW.h and Can_43_MCAN_Cfg.h are different"
#endif
/* Check if current file and CAN configuration header file are of the same software version */
#if ((CAN_43_MCAN_IPW_SW_MAJOR_VERSION_H != CAN_43_MCAN_SW_MAJOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_IPW_SW_MINOR_VERSION_H != CAN_43_MCAN_SW_MINOR_VERSION_CFG_H) || \
     (CAN_43_MCAN_IPW_SW_PATCH_VERSION_H != CAN_43_MCAN_SW_PATCH_VERSION_CFG_H))
#error "Software Version Numbers of Can_43_MCAN_IPW.h and Can_43_MCAN_Cfg.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
#if (STD_ON == CAN_43_MCAN_ENABLE_USER_MODE_SUPPORT)
    /* Check if current file and Reg_eSys.h file are of the same Software version */
    #if ((CAN_43_MCAN_IPW_AR_RELEASE_MAJOR_VERSION_H != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
        (CAN_43_MCAN_IPW_AR_RELEASE_MINOR_VERSION_H != REG_ESYS_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Can_43_MCAN_IPW.h and Reg_eSys.h are different"
    #endif
#endif
#endif
/*==================================================================================================
*                                          CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
    #define     CAN_43_MCAN_NULL_OFFSET      (MCAN_NULL_OFFSET_U8)
    #define     CAN_43_MCAN_MB_DATABYTES     (MCAN_MB_DATABYTES_U8)
    #define     CAN_43_MCAN_FD_ENABLE_U32    (MCAN_CCCR_CME_FDN_U32)
/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    #define Can_43_MCAN_IPW_ProcessRx( controller, mbindex_start, mbindex_end )                       (Can_MCan_ProcessRx( (controller), (mbindex_start), (mbindex_end))) 
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    #define Can_43_MCAN_IPW_ProcessTx(controller, mbindex_start, mbindex_end)                           (Can_MCan_ProcessTx( (controller), (mbindex_start), (mbindex_end)))


/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define Can_43_MCAN_IPW_ProcessBusOff(controller)                                                 (Can_MCan_ProcessBusOff( controller))
/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define         Can_43_MCAN_IPW_InitVariables()                                            (Can_MCan_InitVariables())

#if (STD_ON == CAN_43_MCAN_ENABLE_USER_MODE_SUPPORT)
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_5 Violates MISRA 2004 Required Rule 19.4, expand c macro to use stub for support user mode. */
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    #define         Can_43_MCAN_IPW_SetUserAccessAllowed()          Mcal_Trusted_Call(Can_Mcan_SetUserAccessAllowed,(MCAN_BASEADDR))
#endif

    /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define         Can_43_MCAN_IPW_Init(Controller)                            (Can_MCan_Init(Controller))

        /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define         Can_43_MCAN_IPW_ResetController(Controller)                 (Can_MCan_ResetController(Controller))

    /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define         Can_43_MCAN_IPW_ChangeBaudrate(Controller)                  (Can_MCan_ChangeBaudrate(Controller))

    /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define         Can_43_MCAN_IPW_SetControllerMode(Controller, pCanControlerDescriptor, Transition, canif_notification_required) \
                        (Can_MCan_SetControllerMode((Controller), (pCanControlerDescriptor),(Transition), (canif_notification_required)))


        /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
        /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_DisableControllerInterrupts(Controller) \
                        (Can_MCan_DisableControllerInterrupts(Controller))

        /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
        #define         Can_43_MCAN_IPW_EnableControllerInterrupts(Controller, pCanControlerDescriptor) \
                        (Can_MCan_EnableControllerInterrupts((Controller), (pCanControlerDescriptor)))

    #if (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON)   
/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_Cancel(controller, mbindex)                                (Can_MCan_Cancel((controller), (mbindex)))
    #endif /* (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON) */
    
    #if ((CAN_43_MCAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON))

/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_AbortMb(Hth)                                              (Can_MCan_AbortMb(Hth))
    #endif /* (CAN_43_MCAN_API_ENABLE_ABORT_MB == STD_ON) && (CAN_43_MCAN_HW_TRANSMIT_CANCELLATION == STD_ON) */


/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        /* @violates @ref CAN_43_MCAN_IPW_h_REF_5 Violates MISRA 2004 Required Rule 19.4, expand c macro to use stub for support user mode. */
        /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
        #define         Can_43_MCAN_IPW_Write(Hth, PduInfo)                                       (Can_MCan_Write((Hth), (PduInfo)))

#if ((CAN_43_MCAN_TXPOLL_SUPPORTED == STD_ON))
/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_MainFunctionWrite()                                       (Can_MCan_MainFunctionWrite())
/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_MainFunctionMultipleWritePoll(writepoll)            (Can_MCan_MainFunctionMultipleWritePoll(writepoll))
#endif
    
#if (CAN_43_MCAN_RXPOLL_SUPPORTED == STD_ON)
/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_MainFunctionRead()                                        (Can_MCan_MainFunctionRead())
/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_MainFunctionMultipleReadPoll(readpoll)                    (Can_MCan_MainFunctionMultipleReadPoll(readpoll))
    #endif

    /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
    #define         Can_43_MCAN_IPW_MainFunctionMode()  (Can_MCan_MainFunctionMode())



/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_CheckBusOff(controller)                                   (Can_MCan_CheckBusOff(controller))
    #if (CAN_43_MCAN_DUAL_CLOCK_MODE == STD_ON)

/* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
/* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
        #define         Can_43_MCAN_IPW_SetClockMode(u8Controller, can_clk_mode)                (Can_MCan_SetClockMode((u8Controller), (can_clk_mode)))
    #endif

#ifdef ERR_IPV_MCAN_0002 
  #if (ERR_IPV_MCAN_0002 == STD_ON)
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
    /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */  
    #define Can_43_MCAN_IPW_DummyRead(u8Controller) (Can_MCan_DummyRead(u8Controller))
  #endif
#endif
    
#if (STD_ON == CAN_43_MCAN_INTERRUPT_SUPPORTED)
   /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
   /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */      
  #define Can_43_MCAN_IPW_Isr_common_process_interrupt(u8Controller)    (Can_MCan_Isr_common_process_interrupt(u8Controller))
#endif

#ifdef CAN_43_MCAN_SUPPORT_MRAF_EVENT
    #if (CAN_43_MCAN_SUPPORT_MRAF_EVENT == STD_ON)
        #if (CAN_43_MCAN_MRAFPOLL_SUPPORTED == STD_ON)
            /* @violates @ref CAN_43_MCAN_IPW_h_REF_3 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
            /* @violates @ref CAN_43_MCAN_IPW_h_REF_4 Violates MISRA 2004 Required Rule 19.10, Parantheses not used for parameters due to ##. */
            #define  Can_43_MCAN_IPW_MainFunction_CheckMRAF()        Can_MCan_MainFunction_CheckMRAF()
        #endif
    #endif
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

#if (CAN_43_MCAN_PRECOMPILE_SUPPORT == STD_OFF)
#define CAN_43_MCAN_START_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref  CAN_43_MCAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"

#define CAN_43_MCAN_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/* @violates @ref  CAN_43_MCAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"
#endif

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#define CAN_43_MCAN_START_SEC_CODE
/* @violates @ref  CAN_43_MCAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"
#define CAN_43_MCAN_STOP_SEC_CODE
/* @violates @ref  CAN_43_MCAN_IPW_h_REF_2 Violates MISRA 2004 Required Rule 19.15, Repeated include files */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /*TEMPLATE_H*/

/** @} */
