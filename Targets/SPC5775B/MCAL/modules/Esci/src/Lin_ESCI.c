/**
*   @file    Lin_ESCI.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Lin - ESCI.
*   @details File containing the low level driver of the ESCI IP.
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
/*=================================================================================================
=================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Lin_ESCI_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,
* Precautions shall be taken in order to prevent the contents of a header file being included twice.
* This comes from the order of includes in the .c file and from include dependencies.
*
* @section Lin_ESCI_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before '#include'
* This is an Autosar memory management requirement.
*
* @section Lin_ESCI_c_REF_3
* Violates MISRA 2004 Required Rule 11.1, Casting operation to a pointer.
* This violation is due to the Casting pointers to other types used in macros
* for Reading or writing data from address location of controller register
*
* @section Lin_ESCI_c_REF_4
* Violates MISRA 2004 Advisory Rule 12.6, boolean expression required for operator:
* '&&'.
* Booleans operands are not used for logical operators '&&', '||' and '!'
*
* @section Lin_ESCI_c_REF_5
* Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than
* array indexing used.
* This violation is due to the structure of the types used.
*
* @section Lin_ESCI_c_REF_6
* Violates MISRA 2004 Required Rule 8.10, External ... could be made static.
* Not required from Autosar specification.
*
* @section Lin_ESCI_c_REF_7
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* The compiler/linker shall be checked to ensure that 31 character significance and
* case sensitivity are supported for external identifiers.
* This violation is due to the requirement that requests to have a file version check.
*
* @section Lin_ESCI_c_REF_8
* Violates MISRA 2004 Required Rule 15.2, An unconditional break statement shall
* terminate every non-empty switch clause
* This violation is due to optimize code
*
* @section Lin_ESCI_c_REF_9
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not
* rely on the significance of more than 31 characters.
*
* @section Lin_ESCI_c_REF_10
* Violates MISRA 2004 Required Rule 20.2, Re-use of C90 reserved identifier
* This violation is due to the use of "_" which is required as per Autosar.
*
* @section Lin_ESCI_c_REF_11
* Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between
* a pointer type and an integral type
*
* @section Lin_ESCI_c_REF_12
* Violates MISRA 2004 Required Rule 8.7, Objects shall be defined at block scope if they are only
* accessed from within a single function
*/

/*=================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Lin.h"
#include "Lin_ESCI.h"

#ifdef LIN_USE_DMA
#include "CDD_Mcl.h"
#endif  /* LIN_USE_DMA */

#include "StdRegMacros.h"
#include "Reg_eSys.h"
#include "Reg_eSys_ESCI.h"
#include "SchM_Lin.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define LIN_VENDOR_ID_ESCI_C                    43
/**
* @violates @ref Lin_ESCI_c_REF_7 The compiler/linker shall be checked to
* ensure that 31 character signifiance and case sensitivity are supported for
* external identifiers.
*/
/* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
#define LIN_AR_RELEASE_MAJOR_VERSION_ESCI_C     4
/**
* @violates @ref Lin_ESCI_c_REF_7 The compiler/linker shall be checked to
* ensure that 31 character signifiance and case sensitivity are supported for
* external identifiers.
*/
/* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
#define LIN_AR_RELEASE_MINOR_VERSION_ESCI_C     0
/**
* @violates @ref Lin_ESCI_c_REF_7 The compiler/linker shall be checked to
* ensure that 31 character signifiance and case sensitivity are supported for
* external identifiers.
*/
/* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
#define LIN_AR_RELEASE_REVISION_VERSION_ESCI_C  3
#define LIN_SW_MAJOR_VERSION_ESCI_C             1
#define LIN_SW_MINOR_VERSION_ESCI_C             0
#define LIN_SW_PATCH_VERSION_ESCI_C             1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if current file and Lin header file are of the same vendor */
#if (LIN_VENDOR_ID_ESCI_C != LIN_VENDOR_ID)
    #error "Lin_ESCI.c and Lin.h have different vendor ids"
#endif
/* Check if current file and Lin_ESCI header file are of the same vendor */
#if (LIN_VENDOR_ID_ESCI_C != LIN_VENDOR_ID_ESCI)
    #error "Lin_ESCI.c and Lin_ESCI.h have different vendor ids"
#endif
/* Check if current file and Lin_ESCI header file are of the same vendor */
#if (LIN_VENDOR_ID_ESCI_C != LIN_VENDOR_ID_REGESCI)
    #error "Lin_ESCI.c and Reg_eSys_ESCI.h have different vendor ids"
#endif
/* Check if current file and Lin.h header file are of the same Autosar version */
#if ((LIN_AR_RELEASE_MAJOR_VERSION_ESCI_C    != LIN_AR_RELEASE_MAJOR_VERSION) || \
     (LIN_AR_RELEASE_MINOR_VERSION_ESCI_C    != LIN_AR_RELEASE_MINOR_VERSION) || \
     (LIN_AR_RELEASE_REVISION_VERSION_ESCI_C != LIN_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Lin_ESCI.c and Lin.h are different"
#endif
/* Check if current file and Lin.h header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_ESCI_C != LIN_SW_MAJOR_VERSION) || \
     (LIN_SW_MINOR_VERSION_ESCI_C != LIN_SW_MINOR_VERSION) || \
     (LIN_SW_PATCH_VERSION_ESCI_C != LIN_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Lin_ESCI.c and Lin.h are different"
#endif

/* Check if current file and Lin_ESCI.h header file are of the same Autosar version */
#if (((LIN_AR_RELEASE_MAJOR_VERSION_ESCI_C    != LIN_AR_RELEASE_MAJOR_VERSION_ESCI) || \
      (LIN_AR_RELEASE_MINOR_VERSION_ESCI_C    != LIN_AR_RELEASE_MINOR_VERSION_ESCI)) || \
      (LIN_AR_RELEASE_REVISION_VERSION_ESCI_C != LIN_AR_RELEASE_REVISION_VERSION_ESCI) \
     )
    #error "AutoSar Version Numbers of Lin_ESCI.c and Lin_ESCI.h are different"
#endif
/* Check if current file and Lin_ESCI.h header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_ESCI_C != LIN_SW_MAJOR_VERSION_ESCI) || \
     (LIN_SW_MINOR_VERSION_ESCI_C != LIN_SW_MINOR_VERSION_ESCI) || \
     (LIN_SW_PATCH_VERSION_ESCI_C != LIN_SW_PATCH_VERSION_ESCI) \
    )
    #error "Software Version Numbers of Lin_ESCI.c and Lin_ESCI.h are different"
#endif

/* Check if current file and Reg_eSys_ESCI.h header file are of the same Autosar version */
#if (((LIN_AR_RELEASE_MAJOR_VERSION_ESCI_C    != LIN_AR_RELEASE_MAJOR_VERSION_REGESCI) || \
      (LIN_AR_RELEASE_MINOR_VERSION_ESCI_C    != LIN_AR_RELEASE_MINOR_VERSION_REGESCI)) || \
      (LIN_AR_RELEASE_REVISION_VERSION_ESCI_C != LIN_AR_RELEASE_REVISION_VERSION_REGESCI) \
    )
    #error "AutoSar Version Numbers of Lin_ESCI.c and Reg_eSys_ESCI.h are different"
#endif
/* Check if current file and Reg_eSys_ESCI.h header file are of the same Software version */
#if ((LIN_SW_MAJOR_VERSION_ESCI_C != LIN_SW_MAJOR_VERSION_REGESCI) || \
     (LIN_SW_MINOR_VERSION_ESCI_C != LIN_SW_MINOR_VERSION_REGESCI) || \
     (LIN_SW_PATCH_VERSION_ESCI_C != LIN_SW_PATCH_VERSION_REGESCI) \
    )
    #error "Software Version Numbers of Lin_ESCI.c and Reg_eSys_ESCI.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  /* Check if the source file and StdRegMacros header file are of the same version */
  #if ((LIN_AR_RELEASE_MAJOR_VERSION_ESCI_C != STDREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_AR_RELEASE_MINOR_VERSION_ESCI_C != STDREGMACROS_AR_RELEASE_MINOR_VERSION) \
      )
      #error "AutoSar Version Numbers of Lin_ESCI.c and StdRegMacros.h are different"
  #endif
  /* Check if the source file and Reg_eSys header file are of the same version */
  #if ((LIN_AR_RELEASE_MAJOR_VERSION_ESCI_C != REG_ESYS_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_AR_RELEASE_MINOR_VERSION_ESCI_C != REG_ESYS_AR_RELEASE_MINOR_VERSION) \
      )
      #error "AutoSar Version Numbers of Lin_ESCI.c and Reg_eSys.h are different"
  #endif
  #ifdef LIN_USE_DMA
    /* Check if the source file and CDD_Mcl header file are of the same version */
  #if ((LIN_AR_RELEASE_MAJOR_VERSION_ESCI_C != MCL_AR_RELEASE_MAJOR_VERSION) || \
       (LIN_AR_RELEASE_MINOR_VERSION_ESCI_C != MCL_AR_RELEASE_MINOR_VERSION) \
      )
      #error "AutoSar Version Numbers of Lin_NonASR.c and CDD_Mcl.h are different"
  #endif
  #endif  /* LIN_USE_DMA */
#endif

/*=================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
                                       LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       LOCAL VARIABLES
=================================================================================================*/
#define LIN_START_SEC_VAR_NO_INIT_8
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
/**
* @brief        LIN channel buffer counter.
*
* @details      Counter indicating how many steps have been done
*               before to send the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(uint8,LIN_VAR)Lin_ESCI_au8BufferCounter[LIN_HW_MAX_AVAILABLE_MODULES];

/**
* @brief        LIN channel buffer counter max.
*
* @details      Counter indicating the maximum number of steps to
*               do before to send the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(uint8,LIN_VAR)Lin_ESCI_au8BufferCounterMax[LIN_HW_MAX_AVAILABLE_MODULES];

#define LIN_STOP_SEC_VAR_NO_INIT_8
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
#ifdef LIN_USE_DMA
    /**
    * @violates @ref Lin_ESCI_c_REF_7 The compiler/linker shall be checked to ensure that 31
    * character significance and case sensitivity are supported for external identifiers.
    *
    * @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than
    * 31 characters.
    */
    #define LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
#else
    /* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
    #define LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED
#endif  /* LIN_USE_DMA */
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 

#ifdef  ESCI0_BASEADDR
/**
* @brief        Shadow buffer for eSCI_0 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_0;
#endif /* ESCI0_BASEADDR */

#ifdef  ESCI1_BASEADDR
/**
* @brief        Shadow buffer for eSCI_1 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_1;
#endif /* ESCI1_BASEADDR */

#ifdef  ESCI2_BASEADDR
/**
* @brief        Shadow buffer for eSCI_2 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_2;
#endif /* ESCI2_BASEADDR */

#ifdef  ESCI3_BASEADDR
/**
* @brief        Shadow buffer for eSCI_3 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_3;
#endif /* ESCI3_BASEADDR */

#ifdef  ESCI4_BASEADDR
/**
* @brief        Shadow buffer for eSCI_4 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_4;
#endif  /* ESCI4_BASEADDR */

#ifdef  ESCI5_BASEADDR
/**
* @brief        Shadow buffer for eSCI_5 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_5;
#endif /* ESCI5_BASEADDR */

#ifdef  ESCI6_BASEADDR
/**
* @brief        Shadow buffer for eSCI_6 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_6;
#endif /* ESCI6_BASEADDR */

#ifdef  ESCI7_BASEADDR
/**
* @brief        Shadow buffer for eSCI_7 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_7;
#endif /* ESCI7_BASEADDR */

#ifdef  ESCI8_BASEADDR
/**
* @brief        Shadow buffer for eSCI_8 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_8;
#endif /* ESCI8_BASEADDR */

#ifdef  ESCI9_BASEADDR
/**
* @brief        Shadow buffer for eSCI_9 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_9;
#endif /* ESCI9_BASEADDR */

#ifdef  ESCI10_BASEADDR
/**
* @brief        Shadow buffer for eSCI_10 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_10;
#endif /* ESCI10_BASEADDR */

#ifdef  ESCI11_BASEADDR
/**
* @brief        Shadow buffer for eSCI_11 IP.
*
* @details      Buffer used to prepare and send or receive the frame.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
VAR(Lin_BuffType,LIN_VAR)Lin_ESCI_ChShadowBuff_11;
#endif /* ESCI11_BASEADDR */

#ifdef LIN_USE_DMA
    /**
    * @violates @ref Lin_ESCI_c_REF_7 The compiler/linker shall be checked to ensure that 31
    * character significance and case sensitivity are supported for external identifiers.
    *
    * @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than
    * 31 characters.
    */
    #define LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED_NO_CACHEABLE
    /**
    * @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
    *        of a header file being included twice.
    */
    /**
    * @violates @ref Lin_ESCI_c_REF_2 only preprocessor statements and comments before '#include'
    */
     #include "MemMap.h"
 
    /* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
    #define LIN_START_SEC_VAR_NO_INIT_UNSPECIFIED
    /**
    * @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
    *        of a header file being included twice.
    */
    /**
    * @violates @ref Lin_ESCI_c_REF_2 only preprocessor statements and comments before '#include'
    */
     #include "MemMap.h"
 
    static VAR(Mcl_DmaTcdAttributesType, LIN_VAR) Lin_eSCI_DmaConfigDescriptor;
#endif  /* LIN_USE_DMA */

/* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
#define LIN_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor statements and comments before '#include'
*/
 #include "MemMap.h"
 
/*=================================================================================================
                                       GLOBAL CONSTANTS
=================================================================================================*/
#define LIN_START_SEC_CONST_32
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
/**
* @brief        eSCI IPs base addresses.
*
* @details      Array containing the base address of all the eSCI IPs.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
CONST(uint32, LIN_CONST) ESCI_au32BaseAddrs[] =
{
    #ifdef  ESCI0_BASEADDR
        ESCI0_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI0_BASEADDR */
    #ifdef  ESCI1_BASEADDR
        ESCI1_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI1_BASEADDR */
    #ifdef  ESCI2_BASEADDR
        ESCI2_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI2_BASEADDR */
    #ifdef  ESCI3_BASEADDR
        ESCI3_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI3_BASEADDR */
    #ifdef  ESCI4_BASEADDR
        ESCI4_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI4_BASEADDR */
    #ifdef  ESCI5_BASEADDR
        ESCI5_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI5_BASEADDR */
    #ifdef  ESCI6_BASEADDR
        ESCI6_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI6_BASEADDR */
    #ifdef  ESCI7_BASEADDR
        ESCI7_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI7_BASEADDR */
    #ifdef  ESCI8_BASEADDR
        ESCI8_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI8_BASEADDR */
    #ifdef  ESCI9_BASEADDR
        ESCI9_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI9_BASEADDR */
    #ifdef  ESCI10_BASEADDR
        ESCI10_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI10_BASEADDR */
    #ifdef  ESCI11_BASEADDR
        ESCI11_BASEADDR
    #else
        ((uint32)0x00000000UL),
    #endif /* ESCI11_BASEADDR */
};

#define LIN_STOP_SEC_CONST_32
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
#define LIN_START_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
/**
* @brief        Shadow buffer pointer array.
*
* @details      Array containing the Shadow buffer pointer of all the eSCI IPs.
*
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
CONSTP2VAR(Lin_BuffType, LIN_CONST, LIN_APPL_DATA) Lin_ESCI_pChShadowBuffPtr[]=
{
    #ifdef  ESCI0_BASEADDR
        &Lin_ESCI_ChShadowBuff_0,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI0_BASEADDR */
    #ifdef  ESCI1_BASEADDR
        &Lin_ESCI_ChShadowBuff_1,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI1_BASEADDR */
    #ifdef  ESCI2_BASEADDR
        &Lin_ESCI_ChShadowBuff_2,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI2_BASEADDR */
    #ifdef  ESCI3_BASEADDR
        &Lin_ESCI_ChShadowBuff_3,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI3_BASEADDR */
    #ifdef  ESCI4_BASEADDR
        &Lin_ESCI_ChShadowBuff_4,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI4_BASEADDR */
    #ifdef  ESCI5_BASEADDR
        &Lin_ESCI_ChShadowBuff_5,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI5_BASEADDR */
    #ifdef  ESCI6_BASEADDR
        &Lin_ESCI_ChShadowBuff_6,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI6_BASEADDR */
    #ifdef  ESCI7_BASEADDR
        &Lin_ESCI_ChShadowBuff_7,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI7_BASEADDR */
    #ifdef ESCI8_BASEADDR
        &Lin_ESCI_ChShadowBuff_8,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI8_BASEADDR */
    #ifdef  ESCI9_BASEADDR
        &Lin_ESCI_ChShadowBuff_9,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI9_BASEADDR */
    #ifdef  ESCI10_BASEADDR
        &Lin_ESCI_ChShadowBuff_10,
    #else
        ((Lin_BuffType *)0x00000000UL),
    #endif /* ESCI10_BASEADDR */
    #ifdef ESCI11_BASEADDR
        &Lin_ESCI_ChShadowBuff_11
    #else
        ((Lin_BuffType *)0x00000000UL)
    #endif /* ESCI11_BASEADDR */
};

#define LIN_STOP_SEC_CONST_UNSPECIFIED
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
#define LIN_START_SEC_CONST_8
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
/**
* @brief        Slave timeout values array.
*
* @details      Array containing the timeout values for the slave.
*
*/
/**
*
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*
* @violates @ref Lin_ESCI_c_REF_12 Objects shall be defined at block scope if they are only
*                                    accessed from within a single function
*/
CONST (uint8,LIN_CONST) Lin_ESCI_aTimeoutValue [(LIN_MAX_DATA_LENGTH + 1U)]=
{
    ESCI_TIMEOUT_DATABYTE_ZERO_U8,        /*= (10*0+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_ONE_U8,         /*= (10*1+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_TWO_U8,         /*= (10*2+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_THREE_U8,       /*= (10*3+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_FOUR_U8,        /*= (10*4+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_FIVE_U8,        /*= (10*5+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_SIX_U8,         /*= (10*6+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_SEVEN_U8,       /*= (10*7+45)*1.4 */
    ESCI_TIMEOUT_DATABYTE_EIGHT_U8        /*= (10*8+45)*1.4 */
};

#define LIN_STOP_SEC_CONST_8
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
/*=================================================================================================
                                       GLOBAL VARIABLES
=================================================================================================*/
/*=================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/

/*=================================================================================================
                                       LOCAL FUNCTIONS
=================================================================================================*/

/*=================================================================================================
                                       GLOBAL FUNCTIONS
=================================================================================================*/
#define LIN_START_SEC_CODE
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
/*===============================================================================================*/

/**
* @brief   Check if a LIN channel has been waked-up.
* @details This function identifies if the addressed LIN channel
*          has been woken up by the LIN bus transceiver. This API
*          is used when the LIN channel wake up functionality is
*          disabled (wake up interrupt is disabled). It checks
*          the wake up flag from the addressed LIN channel which
*          must be in sleep mode and have the wake up
*          functionality disabled.
*
* @param[in] Channel LIN channel to be waked-up.
*
* @return            Std_ReturnType.
* @retval E_OK       If the LIN Channel has the wake
*                    up flag set and the wake up ISR disabled
* @retval E_NOT_OK   Otherwise.
*
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(Std_ReturnType, LIN_CODE) Lin_ESCI_CheckWakeup(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(Std_ReturnType, AUTOMATIC) tempReturn = (uint8)FALSE;
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;
    VAR(uint16, AUTOMATIC) u16Temp;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    /* Check whether wake up flag has been set and wake up ISR is disabled */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    u16Temp = REG_READ16(ESCI_IFSR2_ADDR32(u8Lin_ESCI)) & ESCI_IFSR2_LWAKE_MASK_U16;
    if ( ESCI_IFSR2_LWAKE_MASK_U16 == u16Temp)
    {
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        if ( ESCI_LCR1_WUIE_MASK_U16 == ( REG_READ16(ESCI_LCR1_ADDR32(u8Lin_ESCI)) & ESCI_LCR1_WUIE_MASK_U16) )
        {
            /* Set the returned value to FALSE */
            tempReturn = (uint8)FALSE;
        }
        else
        {
            /* LIN channel with wake up support disabled has been woken up
            * Clear Wake-Up flag
            * @Note: all flags have to be cleared by writing a 1 to the flags -> writing 0 has no effect
            */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_WRITE16( ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_LWAKE_MASK_U16 );

            /* Set the returned value to TRUE */
            tempReturn = (uint8)TRUE;
        }
    }
    else
    {
        tempReturn = (uint8)FALSE;
    }

    return tempReturn;
}

/**
* @brief   Initialize a LIN channel.
* @details This function initializes all hardware registers needed to
*          start the LIN functionality on the selected channel.
*
* @param[in] Channel LIN channel to be initialized.
*
* @return            void.
*
*
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(void, LIN_CODE) Lin_ESCI_InitChannel(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;
    VAR(uint8, AUTOMATIC) u8BuffLoop;
    VAR(uint8, AUTOMATIC) u8Lin_ChLoopCount;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    /* Check whether wake up detection is enabled */
     if ((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u16LinChannelWakeupSupport)
     {
        /* Wake up flag set */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        if ( ESCI_IFSR2_LWAKE_MASK_U16 == (REG_READ16(ESCI_IFSR2_ADDR32(u8Lin_ESCI)) & ESCI_IFSR2_LWAKE_MASK_U16) )
        {
            /* The wake-up shall directly be reported to the EcuM */
            /* via EcuM_SetWakeupEvent call-back function. */
             EcuM_SetWakeupEvent(Lin_pChannelConfigPtr[u8Channel]->LinChannelEcuMWakeupSource);
         }
    }
    /* Enable eSCI module */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_MDIS_MASK_U16);

    /* Enable LIN mode */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LIN_MASK_U16);

    /* Set LRES bit of LCR1 register to reset the LIN state machine */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

    /* Set baud rate value for low power mode */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_WRITE16(ESCI_BRR_ADDR32(u8Lin_ESCI), (uint16)((Lin_pChannelConfigPtr[u8Channel]->u32Lin_BaudRate_RegValue) & ESCI_BRR_SBR_MASK_U16));

    /* Enable Transmitter */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);

    /* Enable Receiver */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

#if defined (ERR_IPV_ESCI_0001)
    #if (ERR_IPV_ESCI_0001 == STD_ON)
    /* Enable Fast Bit Error Detection */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FBR_MASK_U16);
    #endif
#endif

#ifdef LIN_USE_DMA
    /* Enable DMA Stop on Bit Error or Physical Bus Error */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    */
    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_BSTP_MASK_U16);
#endif  /* LIN_USE_DMA */
    /* Enable Bit Error Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_BERRIE_MASK_U16);

    /* Select break character length of 13 bit as required by LIN 2.0 */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_BRCL_MASK_U16);

    /* Enable Fast Bit Error Detection Sample Mode */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_BESM_MASK_U16);

    /* Enable Transmit Stop on Bit Error */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_BESTP_MASK_U16);

    /* Enable Frame Error Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FEIE_MASK_U16);

    /* Clear LRES bit of LCR1 register to reset the LIN state machine */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_LRES_MASK_U16);

    /* Enable Parity Flag Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_PRTY_MASK_U16);

#if (LIN_DISABLE_FRAME_TIMEOUT == STD_OFF)
    /* Enable Slave Timeout Flag Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_STIE_MASK_U16);
#else
    /* Disable Slave Timeout Flag Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_STIE_MASK_U16);
#endif

    /* Enable Physical Bus Error Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_PBIE_MASK_U16);

    /* Enable Checksum Error Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_CKIE_MASK_U16);

    /* Disable CRC Error Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_CIE_MASK_U16);

    /* Enable Overflow Flag Interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_SET16(ESCI_LCR2_ADDR32(u8Lin_ESCI), ESCI_LCR2_OFIE_MASK_U16);

    /* Disable wake up interrupt */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    *
    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
    */
    REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_WUIE_MASK_U16);

    /* Clear the contents of shadow buffer */
    for(u8Lin_ChLoopCount=(uint8)ESCI_ZERO_U8;u8Lin_ChLoopCount<LIN_HW_MAX_MODULES;u8Lin_ChLoopCount++)
    {
        for(u8BuffLoop=ESCI_ZERO_U8;u8BuffLoop < LIN_MAX_DATA_LENGTH;u8BuffLoop++)
        {
            Lin_ESCI_pChShadowBuffPtr[u8Lin_ChLoopCount]->au8Lin_DATA[u8BuffLoop] = ESCI_ZERO_U8;
        }
    }
}

/**
* @brief   Sends the header part of the LIN frame.
* @details Initiates the transmission of the header
*          part of the LIN frame on Channel using information
*          stored on PduInfoPtr pointer.
*          If response type is MASTER_RESPONSE then nothing is sent over the bus
*          the entire frame (including header) is sent with the ESCI_LLD_SendResponse
*
* @param[in]   Channel LIN channel to be addressed.
* @param[in]   PduInfoPtr pointer to PDU containing the PID, Checksum model,
*              Response type, Dl and SDU data pointer.
*
* @return            Std_ReturnType.
* @retval E_NOT_OK   In case of a timeout situation only.
* @retval E_OK       Otherwise.
*
*
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(Std_ReturnType, LIN_CODE) Lin_ESCI_SendHeader(CONST(uint8, AUTOMATIC) u8Channel, \
                          P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) pcPduInfoPtr)
{
    VAR(uint8, AUTOMATIC)u8Lin_Temp;
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;
    VAR(uint32, AUTOMATIC) volatile u32counter = ESCI_ZERO_U8;
    VAR(uint8, AUTOMATIC) u8tmpReturn = (uint8)E_NOT_OK;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_00();
    {
        /* Stop any ongoing transmission */

        /* Disable Transmitter */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);

        /* Disable Receiver */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

        /* Disable Receive Data Ready Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_RXIE_MASK_U16);

        /* Disable Transmit Data Ready Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);

#ifdef LIN_USE_DMA
        /* Transmit DMA disabled */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_TXDMA_MASK_U16);

        /* Receive DMA disabled */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);
#endif  /* LIN_USE_DMA */
        /* Disable Frame Control Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_FCIE_MASK_U16);
    }
    SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_00();

    MCAL_FAULT_INJECTION_POINT(ESCI_FIP_1_T_TIME_OUT_1);
    /* Wait till cancellation of current frame */
    while(u32counter < (LIN_TIMEOUT_LOOPS+1U))
    {
    #ifdef LIN_USE_DMA
        #if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
        /* eSCI V.8 specific code*/
        /* Is there a a transmit or receive DMA request pending ? */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        if(ESCI_IFSR1_DACT_MASK_U16 != ( REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_DACT_MASK_U16))
        {
            u8tmpReturn = (uint8)E_OK;
            break;
        }
        u32counter++;
        #else
        u8tmpReturn = (uint8)E_OK;
        break;
        #endif
    #else
        /* Is there a a transmit or receive interrupt request pending ? */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        if(ESCI_IFSR1_TACT_MASK_U16 != ( REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_TACT_MASK_U16))
        {
            u8tmpReturn = (uint8)E_OK;
            break;
        }
        u32counter++;
    #endif  /* LIN_USE_DMA */
    }

    if((uint8)E_OK == u8tmpReturn)
    {
        /* Reset error status global flag */
        Lin_au8LinChFrameErrorStatus[u8Channel] = LIN_NO_ERROR;

        /* Set header status to TRUE if master wants to send the response frame */
        if (LIN_MASTER_RESPONSE == pcPduInfoPtr->Drc)
        {
            Lin_au8TransmitHeaderCommand[u8Channel] = LIN_TX_MASTER_RES_COMMAND;
            /* Update LIN channel frame operation status to LIN_CH_READY_STATE */
            Lin_au8LinChFrameStatus[u8Channel] = LIN_CH_READY_STATE;
        }
        else
        {
            Lin_au8TransmitHeaderCommand[u8Channel] = LIN_TX_SLAVE_RES_COMMAND;
            Lin_au8LinChFrameStatus[u8Channel] = LIN_CH_RECEIVE_NOTHING_STATE;
        }

        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_01();
        {
            /* Set LRES bit of LCR1 register to reset the LIN state machine */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /* These redundant lines are required since LIN state machine gets RESET correctly after
            setting LRES bit three times and then clear it */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);
        }
        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_01();

        /* Clear the Noise Flag of Interrupt Flag and Status Register 1 (eSCI_IFSR1) */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

        /* Copy the Identifier into a local variable */
        u8Lin_Temp = (pcPduInfoPtr->Pid & ESCI_LTR_ID_MASK_U8);

        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        if (ESCI_LCR1_PRTY_MASK_U16 != ( REG_READ16(ESCI_LCR1_ADDR32(u8Lin_ESCI)) & ESCI_LCR1_PRTY_MASK_U16))
        {
            /* Recalculate the parity */
            u8Lin_Temp  = ((u8Lin_Temp) & (uint8)(~((ESCI_ID_BIT_SIX_MASK_U8)|(ESCI_ID_BIT_SEVEN_MASK_U8))))^
                        (((uint8)(u8Lin_Temp  << ESCI_ID_BIT_SHIFT_BY_TWO_U8) ^
                        ((uint8)(u8Lin_Temp << ESCI_ID_BIT_SHIFT_BY_THREE_U8) & ESCI_ID_BIT_SEVEN_MASK_U8)^
                        (uint8)(u8Lin_Temp << ESCI_ID_BIT_SHIFT_BY_FOUR_U8) ^
                        ((uint8)(u8Lin_Temp << ESCI_ID_BIT_SHIFT_BY_FIVE_U8) & ESCI_ID_BIT_SIX_MASK_U8) ^
                        (uint8)(u8Lin_Temp << ESCI_ID_BIT_SHIFT_BY_SIX_U8)) &
                        ESCI_ID_BIT_SIX_SEVEN_MASK_U8);
        }
        else
        {
            /* Hardware parity is enabled, just assign the PID value to go to next ELSE statement */
            u8Lin_Temp = pcPduInfoPtr->Pid;
        }
        /* Prepare header */
        /* First step is to configure ID */
        Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ZERO_U8] = u8Lin_Temp ;


        /* Second step data length */
        Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8] = pcPduInfoPtr->Dl;

        /* Third step is to configure Checksum, CRC and Transfer direction */
        if(LIN_MASTER_RESPONSE == pcPduInfoPtr->Drc)
        {
            /* Tx */
            if(LIN_ENHANCED_CS == pcPduInfoPtr->Cs)
            {
                /* Use enhanced checksum and set Transfer direction bit as Transmit */
                Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_TWO_U8] = ( ESCI_LTR_CSM_MASK_U8 |
                                                ESCI_LTR_TD_MASK_U8  |
                                                ESCI_LTR_CSE_MASK_U8);
            }
            else
            {
                /* Use Classic checksum and set Transfer direction bit as Transmit */
                Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_TWO_U8] = ( ESCI_LTR_TD_MASK_U8 |
                                                ESCI_LTR_CSE_MASK_U8);
            }
            /* Set master response msg type */
            Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE = (uint8)LIN_MASTER_RESPONSE;
        }
        else
        {
            /* Rx */
            if(LIN_ENHANCED_CS == pcPduInfoPtr->Cs)
            {
                /* Use enhanced checksum */
                /* Third step */
                /* HDCHK|CSUM|RX */
                Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_TWO_U8] = (ESCI_LTR_CSM_MASK_U8 |
                                            ESCI_LTR_CSE_MASK_U8);
            }
            else
            {
                /* Use classic checksum */
                /* Third step */
                /* CSUM|RX */
                Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_TWO_U8] = (ESCI_LTR_CSE_MASK_U8);
            }
            /* Fourth step timeout */
            Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_THREE_U8] =
                                    Lin_ESCI_aTimeoutValue[pcPduInfoPtr->Dl];
            /* Set slave response msg type */
            Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE = (uint8)LIN_SLAVE_RESPONSE;
        }

        /* Prepare for transmission */

        /* Clear Receive Data Register Full Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_RDRF_MASK_U16);

        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_02();
        {
            /* Enable Receiver Full Interrupt */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RIE_MASK_U16);

            /* Clear LRES bit of LCR1 register to reset the LIN state machine */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_LRES_MASK_U16);

            /* Enable Receiver */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

            /* Enable Transmitter */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);
        }
        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_02();

        /* Initiate transmission of the header depending on DMA or interrupt driven */
    #ifdef LIN_USE_DMA
         if((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u8Lin_DMAEnabled)
         {
            if(LIN_SLAVE_RESPONSE == pcPduInfoPtr->Drc)
            {
                /* Configure TX DMA channel*/
                #if (IPV_ESCI == IPV_ESCI_07_02_01_01)
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    Lin_eSCI_DmaConfigDescriptor.saddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER;
                    Lin_eSCI_DmaConfigDescriptor.daddr = ESCI_LTR_ADDR32(u8Lin_ESCI);
                    Lin_eSCI_DmaConfigDescriptor.ssize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.dsize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.soff = 1U;
                    Lin_eSCI_DmaConfigDescriptor.doff = 0U;
                    Lin_eSCI_DmaConfigDescriptor.smod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.dmod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.num_bytes = 1U;
                    Lin_eSCI_DmaConfigDescriptor.iter = 4U;
                #else
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    Lin_eSCI_DmaConfigDescriptor.u32saddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER;
                    Lin_eSCI_DmaConfigDescriptor.u32daddr = ESCI_LTR_ADDR32(u8Lin_ESCI);
                    Lin_eSCI_DmaConfigDescriptor.u32ssize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32dsize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32soff = 1U;
                    Lin_eSCI_DmaConfigDescriptor.u32doff = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32smod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32dmod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32num_bytes = 1U;
                    Lin_eSCI_DmaConfigDescriptor.u32iter = 4U;
                #endif
                 Mcl_DmaConfigChannel(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel, &Lin_eSCI_DmaConfigDescriptor);
                  Mcl_DmaEnableHwRequest(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel);
                 /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                 Mcl_DmaTcdSetIntMaj((uint32 *)Mcl_DmaGetChannelTcdAddress(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel));
 
                /* Clear Receive Data Ready Interrupt Flag */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                *
                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                */
                REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_RXRDY_MASK_U16);

                SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_03();
                {
                    /* Enable Receive Data Ready Interrupt */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_RXIE_MASK_U16);

                    /* Transmit DMA enabled and start a DMA transfer */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_TXDMA_MASK_U16);
                }
                SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_03();

            }
        }
        else
        {
    #endif  /* LIN_USE_DMA */
            /* ISR driven */
            if((uint8)LIN_MASTER_RESPONSE != Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE)
            {
                /* Clear Receive Data Ready Interrupt Flag */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                *
                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                */
                REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_RXRDY_MASK_U16);

                SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_04();
                {
                    /* Enable Receive Data Ready Interrupt */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_RXIE_MASK_U16);
                }
                SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_04();
            }

            if(LIN_SLAVE_RESPONSE == pcPduInfoPtr->Drc)
            {
                /* Reset buffer counter */
                Lin_ESCI_au8BufferCounter[u8Lin_ESCI] = ESCI_ZERO_U8;

                /* Rx requires 4 steps to initiate the header transmission */
                Lin_ESCI_au8BufferCounterMax[u8Lin_ESCI] = SLAVE_RESPONSE_HEADER_WRITE_COUNT_U8;

                SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_05();
                {
                    /* Enable Transmit Data Ready Interrupt */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);
                }
                SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_05();
            }
    #ifdef LIN_USE_DMA
        }
    #endif  /* LIN_USE_DMA */

        /* Clear the Noise Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

        /* Framing Error flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

        /* Clear Bit Error Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_BERR_MASK_U16);

        /* Clear Slave Timeout Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_STO_MASK_U16);

        /* Clear Physical Bus Error Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_PBERR_MASK_U16);

        /* Clear Checksum Error Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_CKERR_MASK_U16);

        /* Clear Overflow Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_OVFL_MASK_U16);

        /* Clear Unrequested Data Received Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_UREQ_MASK_U16);

        /* Clear Frame Complete Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_FRC_MASK_U16);

        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_06();
        {
            /* Enable end of frame interrupt */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_FCIE_MASK_U16);
        }
        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_06();
    }

    return u8tmpReturn;
}

/**
* @brief   Sends the response part of the LIN frame.
* @details Initiates the transmission of the data
*          part of the LIN frame on Channel using information
*          stored on PduInfoPtr pointer.
*
* @param[in]   Channel LIN channel to be addressed.
* @param[in]   PduInfoPtr pointer to PDU containing the PID, Checksum model,
*              Response type, Dl and SDU data pointer.
*
* @return            void.
*
*
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(void, LIN_CODE) Lin_ESCI_SendResponse(CONST(uint8, AUTOMATIC) u8Channel, \
                      P2CONST(Lin_PduType, AUTOMATIC, LIN_APPL_CONST) pcPduInfoPtr)
{
    VAR(uint8, AUTOMATIC) u8Lin_Temp;
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    /* Check that no error is occurred during sending the header */
    if (LIN_CH_SEND_HEADER_ERROR == Lin_au8LinChFrameStatus[u8Channel])
    {
        /* There was an error during header transmission */

        /* Update LIN channel frame operation status to LIN_CH_SEND_DATA_ERROR */

        Lin_au8LinChFrameStatus[u8Channel] = LIN_CH_SEND_DATA_ERROR;
    }
    else
    {
        /* Check whether data length is valid or not */
        if(ESCI_ZERO_U8 != pcPduInfoPtr->Dl)
        {
            /* Send data */
            /* Copy 1 to 8 data bytes from Pdu to shadow buffer */
        #ifdef LIN_USE_DMA
             if((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u8Lin_DMAEnabled)
             {
                /* @violates @ref Lin_ESCI_c_REF_5 pointer arithmetic other than array indexing used */
                /* HEADER[3] will be used as first data byte */
                Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[3] = pcPduInfoPtr->SduPtr[ESCI_ZERO_U8];

                for(u8Lin_Temp=ESCI_ZERO_U8; \
                    u8Lin_Temp < (Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8] - ESCI_ONE_U8); \
                      u8Lin_Temp++ \
                   )
                {
                    /* Since first datbyte [0] is updated in HEADER[3], now update remaining databytes [1..7] */
                    /* @violates @ref Lin_ESCI_c_REF_5 pointer arithmetic other than array indexing used */
                    Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[u8Lin_Temp] =
                    /* @violates @ref Lin_ESCI_c_REF_5 pointer arithmetic other than array indexing used */
                                      pcPduInfoPtr->SduPtr[u8Lin_Temp + ESCI_ONE_U8];
                }
            }
            else
            {
        #endif  /* LIN_USE_DMA */
                for(u8Lin_Temp=ESCI_ZERO_U8;
                    u8Lin_Temp<Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8];
                      u8Lin_Temp++)
                {
                    /**
                    * @violates @ref Lin_ESCI_c_REF_5 pointer arithmetic other
                    *                                     than array indexing used
                    */
                    Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[u8Lin_Temp] = pcPduInfoPtr->SduPtr[u8Lin_Temp];

                }
        #ifdef LIN_USE_DMA
            }
        #endif  /* LIN_USE_DMA */
            /* Initiate transmission of the response depending on DMA or interrupt driven */
        #ifdef LIN_USE_DMA
             if((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u8Lin_DMAEnabled)
             {
                /* Update LIN channel frame status to LIN_CH_SEND_HEADER */
                Lin_au8LinChFrameStatus[u8Channel] = LIN_CH_SEND_HEADER;

                /* Configure TX DMA channel */
                #if (IPV_ESCI == IPV_ESCI_07_02_01_01)
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    Lin_eSCI_DmaConfigDescriptor.saddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER;
                    Lin_eSCI_DmaConfigDescriptor.daddr = ESCI_LTR_ADDR32(u8Lin_ESCI);
                    Lin_eSCI_DmaConfigDescriptor.ssize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.dsize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.soff = 1U;
                    Lin_eSCI_DmaConfigDescriptor.doff = 0U;
                    Lin_eSCI_DmaConfigDescriptor.smod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.dmod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.num_bytes = 1U;
                    Lin_eSCI_DmaConfigDescriptor.iter = (uint32)Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[1] + 3U;
                #else
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    Lin_eSCI_DmaConfigDescriptor.u32saddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER;
                    Lin_eSCI_DmaConfigDescriptor.u32daddr = ESCI_LTR_ADDR32(u8Lin_ESCI);
                    Lin_eSCI_DmaConfigDescriptor.u32ssize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32dsize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32soff = 1U;
                    Lin_eSCI_DmaConfigDescriptor.u32doff = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32smod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32dmod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32num_bytes = 1U;
                    Lin_eSCI_DmaConfigDescriptor.u32iter = (uint32)Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[1] + 3U;
                #endif
                 Mcl_DmaConfigChannel(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel, &Lin_eSCI_DmaConfigDescriptor);
                  Mcl_DmaEnableHwRequest(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel);
                 /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                 Mcl_DmaTcdSetIntMaj((uint32 *)Mcl_DmaGetChannelTcdAddress(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel));
 
                SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_07();
                {
                    /* Transmit DMA enabled and start a DMA transfer*/
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_TXDMA_MASK_U16);
                }
                SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_07();

            }
            else
            {
        #endif  /* LIN_USE_DMA */
                /* ISR driven */
                /* Reset buffer counter */
                Lin_ESCI_au8BufferCounter[u8Lin_ESCI] = ESCI_ZERO_U8;

                /* Max ISR count */
                Lin_ESCI_au8BufferCounterMax[u8Lin_ESCI] =
                            Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8] +
                              MASTER_RESPONSE_HEADER_WRITE_COUNT_U8;

                SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_08();
                {
                    /* Enable Transmit Data Ready Interrupt */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);
                }
                SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_08();

        #ifdef LIN_USE_DMA
            }
        #endif  /* LIN_USE_DMA */
        }
    }
}

/**
* @brief   Prepares and send a go-to-sleep-command
*          frame on Channel.
* @details This function stops any ongoing transmission and initiates
*          the transmission of the sleep command (master command frame with
*          ID = 0x3C and data = (0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF).
*
* @param[in] Channel LIN channel to be addressed.
*
* @return            Std_ReturnType.
* @retval E_NOT_OK   In case of a timeout situation only.
* @retval E_OK       Otherwise.
*
*
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(Std_ReturnType, LIN_CODE) Lin_ESCI_GoToSleep(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;
    VAR(uint8, AUTOMATIC) u8Lin_Temp;
    VAR(uint32, AUTOMATIC) volatile u32counter = ESCI_ZERO_U8;
    VAR(uint8, AUTOMATIC) u8tmpReturn = (uint8)E_NOT_OK;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_09();
    {
        /* Stop any ongoing transmission */

        /* Disable Transmitter */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);

        /* Disable Receiver */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

        /* Disable Receive Data Ready Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_RXIE_MASK_U16);

        /* Disable Transmit Data Ready Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);

#ifdef LIN_USE_DMA
        /* Transmit DMA disabled */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_TXDMA_MASK_U16);

        /* Receive DMA disabled */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);
#endif  /* LIN_USE_DMA */
        /* Disable Frame Control Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_FCIE_MASK_U16);
    }
    SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_09();

    MCAL_FAULT_INJECTION_POINT(ESCI_FIP_2_T_TIME_OUT_2);
    /* Wait till cancellation of current frame */
    /**
    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
    */
    while(u32counter < (LIN_TIMEOUT_LOOPS+1U))
    {
    #ifdef LIN_USE_DMA
        #if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
        /* eSCI V.8 specific code*/
        /* Is there a a transmit or receive DMA request pending ? */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        if(ESCI_IFSR1_DACT_MASK_U16 != ( REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_DACT_MASK_U16))
        {
            u8tmpReturn = (uint8)E_OK;
            break;
        }
        u32counter++;
        #else
        u8tmpReturn = (uint8)E_OK;
        break;
        #endif
    #else
        /* Is there a a transmit or receive interrupt request pending ? */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        if(ESCI_IFSR1_TACT_MASK_U16 != ( REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_TACT_MASK_U16))
        {
            u8tmpReturn = (uint8)E_OK;
            break;
        }
        u32counter++;
    #endif  /* LIN_USE_DMA */
    }

    if(u8tmpReturn == (uint8)E_OK)
    {
        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_10();
        {
            /* Set LRES bit of LCR1 register to reset the LIN state machine */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /* These redundant line are required since LIN state machine gets RESET correctly after
            setting LRES bit three times and then clear it */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /* Clear LRES bit of LCR1 register to reset the LIN state machine */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_LRES_MASK_U16);

            /* Enable Transmitter */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);

            /* Enable Receiver */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);
        }
        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_10();

        /* Prepare buffer for sleep mode command */
        /* Prepare header */
        /* First step ID */
        /* Includes the parity */
        Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ZERO_U8] = SLEEP_IDENTIFIER_VALUE_U8 ;

        /* Second step data length */
        /* Standard length for master request command */
        Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8] = ESCI_MAX_DATA_LENGTH_U8;

        /* Third step use classic checksum */
        /* CSUM|TX */
        Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_TWO_U8] = (ESCI_LTR_CSE_MASK_U8 |
                                    ESCI_LTR_TD_MASK_U8);

    #ifdef LIN_USE_DMA
         if((uint8)STD_OFF == Lin_pChannelConfigPtr[u8Channel]->u8Lin_DMAEnabled)
         {
    #endif  /* LIN_USE_DMA */
            /* Prepare data */
            /* The data of the shadow buffer to 0 -> Byte0=0 is sleep command */
            Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[ESCI_ZERO_U8] = SLEEP_DATABYTE_ONE_VALUE_U8;

            /* Just 1-7 bytes of the DATA will be send since HEADER[3] is the first data byte */
            for(u8Lin_Temp=ESCI_ONE_U8;
                u8Lin_Temp<Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8];
                  u8Lin_Temp++)
            {
                Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[u8Lin_Temp] = SLEEP_DATABYTE_TWO_TO_EIGHT_VALUE_U8;
            }
    #ifdef LIN_USE_DMA
        }
        else
        {
            /* Fourth step use sleep mode command -> will be used as first data byte */
            Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_THREE_U8] = ESCI_ZERO_U8;

            /* Just 1-7 bytes of the DATA will be send since HEADER[3] is the first data byte */
            for(u8Lin_Temp=ESCI_ZERO_U8;
                u8Lin_Temp<Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8];
                  u8Lin_Temp++)
            {
                Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[u8Lin_Temp] = SLEEP_DATABYTE_TWO_TO_EIGHT_VALUE_U8;
            }
        }
    #endif  /* LIN_USE_DMA */
        /* Set sleep cmd msg type */
        Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE = SLEEP_CMD_TYPE_U8;

        /* Initiate transmission of the header depending on DMA or interrupt driven */
    #ifdef LIN_USE_DMA
         if((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u8Lin_DMAEnabled)
         {
            /* Configure TX DMA channel*/
            #if (IPV_ESCI == IPV_ESCI_07_02_01_01)
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                Lin_eSCI_DmaConfigDescriptor.saddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER;
                Lin_eSCI_DmaConfigDescriptor.daddr = ESCI_LTR_ADDR32(u8Lin_ESCI);
                Lin_eSCI_DmaConfigDescriptor.ssize = 0U;
                Lin_eSCI_DmaConfigDescriptor.dsize = 0U;
                Lin_eSCI_DmaConfigDescriptor.soff = 1U;
                Lin_eSCI_DmaConfigDescriptor.doff = 0U;
                Lin_eSCI_DmaConfigDescriptor.smod = 0U;
                Lin_eSCI_DmaConfigDescriptor.dmod = 0U;
                Lin_eSCI_DmaConfigDescriptor.num_bytes = 1U;
                Lin_eSCI_DmaConfigDescriptor.iter = 11U;
            #else
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                Lin_eSCI_DmaConfigDescriptor.u32saddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER;
                Lin_eSCI_DmaConfigDescriptor.u32daddr = ESCI_LTR_ADDR32(u8Lin_ESCI);
                Lin_eSCI_DmaConfigDescriptor.u32ssize = 0U;
                Lin_eSCI_DmaConfigDescriptor.u32dsize = 0U;
                Lin_eSCI_DmaConfigDescriptor.u32soff = 1U;
                Lin_eSCI_DmaConfigDescriptor.u32doff = 0U;
                Lin_eSCI_DmaConfigDescriptor.u32smod = 0U;
                Lin_eSCI_DmaConfigDescriptor.u32dmod = 0U;
                Lin_eSCI_DmaConfigDescriptor.u32num_bytes = 1U;
                Lin_eSCI_DmaConfigDescriptor.u32iter = 11U;
            #endif
             Mcl_DmaConfigChannel(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel, &Lin_eSCI_DmaConfigDescriptor);
              Mcl_DmaEnableHwRequest(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel);
             /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            */
             Mcl_DmaTcdSetIntMaj((uint32 *)Mcl_DmaGetChannelTcdAddress(Lin_pChannelConfigPtr[u8Channel]->u8Lin_TxDMAChannel));
 
            /* Set header status to LIN_TX_SLEEP_COMMAND if master wants to send the sleep-command */
            Lin_au8TransmitHeaderCommand[u8Channel] = LIN_TX_SLEEP_COMMAND;

            SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_11();
            {
                /* Transmit DMA enabled and start a DMA transfer */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_TXDMA_MASK_U16);
            }
            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_11();

        }
        else
        {
    #endif  /* LIN_USE_DMA */
            /* ISR driven */
            /* Reset buffer counter */
            Lin_ESCI_au8BufferCounter[u8Lin_ESCI] = ESCI_ZERO_U8;

            /* Max ISR count */
            Lin_ESCI_au8BufferCounterMax[u8Lin_ESCI] = LIN_HEADER_DATA_WRITE_COUNT_U8;

            /* Set header status to LIN_TX_SLEEP_COMMAND if master wants to send the sleep-command */
            Lin_au8TransmitHeaderCommand[u8Channel] = LIN_TX_SLEEP_COMMAND;

            SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_12();
            {
                /* Enable Transmit Data Ready Interrupt */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                *
                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                */
                REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);
            }
            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_12();

    #ifdef LIN_USE_DMA
        }
    #endif  /* LIN_USE_DMA */
        /* Clear Frame Complete Interrupt Flag */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_FRC_MASK_U16);

        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_13();
        {
            /* Enable end of frame interrupt */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_FCIE_MASK_U16);
        }
        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_13();

    }

    return u8tmpReturn;
}

/**
* @brief   Same function as Lin_LLD_GoToSleep() but
*          without sending a go-to-sleep-command on the bus.
* @details This function stops any ongoing transmission and put the
*          Channel in sleep mode (then LIN hardware enters a
*          reduced power operation mode).
*
* @param[in] Channel LIN channel to be addressed.
*
* @return            Std_ReturnType.
* @retval E_NOT_OK   In case of a timeout situation only.
* @retval E_OK       Otherwise.
*
*
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(Std_ReturnType, LIN_CODE) Lin_ESCI_GoToSleepInternal(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;
    VAR(uint32, AUTOMATIC) volatile u32counter = ESCI_ZERO_U8;
    VAR(uint8, AUTOMATIC) u8tmpReturn = (uint8)E_NOT_OK;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_14();
    {
        /* Stop any ongoing transmission */

        /* Disable Transmitter */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);

        /* Disable Receiver */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

        /* Disable Receive Data Ready Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_RXIE_MASK_U16);

        /* Disable Transmit Data Ready Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);
#ifdef LIN_USE_DMA
        /* Transmit DMA disabled */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_TXDMA_MASK_U16);

        /* Receive DMA disabled */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);
#endif  /* LIN_USE_DMA */
        /* Disable Frame Control Interrupt */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_FCIE_MASK_U16);
    }
    SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_14();

    MCAL_FAULT_INJECTION_POINT(ESCI_FIP_3_T_TIME_OUT_3);
    /* Wait till cancellation of current frame */
    while(u32counter < (LIN_TIMEOUT_LOOPS+1U))
    {
    #ifdef LIN_USE_DMA
        #if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
        /* eSCI V.8 specific code*/
        /* Is there a a transmit or receive DMA request pending ? */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        */
        if(ESCI_IFSR1_DACT_MASK_U16 != ( REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_DACT_MASK_U16))
        {
            u8tmpReturn = (uint8)E_OK;
            break;
        }
        u32counter++;
        #else
        u8tmpReturn = (uint8)E_OK;
        break;
        #endif
    #else
        /* Is there a a transmit or receive interrupt request pending ? */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        if(ESCI_IFSR1_TACT_MASK_U16 != ( REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI)) & ESCI_IFSR1_TACT_MASK_U16))
        {
            u8tmpReturn = (uint8)E_OK;
            break;
        }
        u32counter++;
    #endif  /* LIN_USE_DMA */
    }
    if((uint8)E_OK == u8tmpReturn)
    {
        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_15();
        {
            /* Enter Sleep mode */
            /* Set LRES bit of LCR1 register to reset the LIN state machine */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /* These redundant line are required since LIN state machine gets RESET correctly after
               setting LRES bit three times and then clear it */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

            /* Clear LRES bit of LCR1 register to reset the LIN state machine */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_LRES_MASK_U16);

            /* Enable Receiver*/
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

            /* Clear TX Ready Interrupt Flag */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_TXRDY_MASK_U16);

            /* Disable TX interrupt */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);

            /* Clear Framing Error Interrupt Flag */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

            /* Disable Frame Error Interrupt */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FEIE_MASK_U16);

            /* Clear Noise Interrupt Flag */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

            /* Disable Noise Interrupt */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_NFIE_MASK_U16);
        }
        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_15();

        /* Check whether wake up detection is enabled */
         if ((uint8)STD_ON == Lin_pChannelConfigPtr[u8Channel]->u16LinChannelWakeupSupport)
         {
            /* Wake up detection is enabled */

            /* Clear Wake-Up flag */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_LWAKE_MASK_U16);

            SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_16();
            {
                /* Enable wake up interrupt */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                *
                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                */
                REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_WUIE_MASK_U16);
            }
            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_16();

        }
    }

    return u8tmpReturn;
}

/**
* @brief   Sends a wake up signal to the LIN bus.
* @details This function shall sent a wake up signal to the LIN bus
*          and put the LIN channel in LIN_CH_OPERATIONAL_STATE state.
*
* @param[in]   Channel LIN channel to be addressed.
*
* @return            void.
*
*
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(void, LIN_CODE) Lin_ESCI_Wakeup(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_17();
    {
        /* Send Wake up request */
        /**
        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
        *
        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
        */
        REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_WU_MASK_U16);
    }
    SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_17();
}

  
/**
 * @brief   Gets the status of the LIN driver when Channel is operating.
 * @details This function returns the state of the current
 *          transmission, reception or operation status.
 *          If the reception of a Slave response was successful then
 *          this service provides a pointer to the buffer where the
 *          data is stored.
 *
 * @param[in]   Channel LIN channel to be addressed
 * @param[out]  LinSduPtr pointer to pointer to a shadow buffer or memory
 *              mapped LIN Hardware receive buffer where the current SDU is
 *              stored
 * @return                  Lin_StatusType.
 * @retval LIN_NOT_OK       Development or production error rised
 *                          none of the below conditions.
 * @retval LIN_TX_OK        Successful transmission.
 * @retval LIN_TX_BUSY      Ongoing transmission of header or response.
 * @retval LIN_TX_HEADER_ERROR Error occurred during header
 *                          transmission.
 * @retval LIN_TX_ERROR     Error occurred during response
 *                          transmission.
 * @retval LIN_RX_OK        Reception of correct response.
 * @retval LIN_RX_BUSY      Ongoing reception where at least one byte
 *                          has been received.
 * @retval LIN_RX_ERROR     Error occurred during reception.
 * @retval LIN_RX_NO_REPONSE No data byte has been received yet.
 * @retval LIN_OPERATIONAL  Channel is ready for next header.
 *                          transmission and no data are available.
 * @retval LIN_CH_SLEEP     Channel is in sleep mode.
 *
 *
 */
 /* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(Lin_StatusType, LIN_CODE) Lin_ESCI_HardwareGetStatus(CONST(uint8, AUTOMATIC) u8Channel,
                             P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) pLinSduPtr)
{
    VAR(Lin_StatusType,AUTOMATIC) TempReturn = LIN_NOT_OK;
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;
    VAR(uint8, AUTOMATIC) u8Temp1;
    VAR(uint8, AUTOMATIC) u8Temp2;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    /* Check error status */
    switch(Lin_au8LinChFrameErrorStatus[u8Channel])
    {
        /* Tx data error conditions */
        case LIN_BIT_ERROR:
            u8Temp1 = Lin_au8TransmitHeaderCommand[u8Channel];
            u8Temp2 = Lin_au8LinChFrameStatus[u8Channel];

            switch(u8Temp1)
            {
                case LIN_TX_SLEEP_COMMAND:
                    /* Update Lin_au8TransmitHeaderCommand value to LIN_TX_NO_COMMAND */
                    Lin_au8TransmitHeaderCommand[u8Channel] = LIN_TX_NO_COMMAND;
                    /* Update LIN channel frame operation status to LIN_CH_NOT_READY_STATE */
                    Lin_au8LinChFrameStatus[u8Channel] = LIN_CH_NOT_READY_STATE;
                    /**
                    * @violates @ref Lin_ESCI_c_REF_8 An unconditional break statement shall
                    * terminate every non-empty switch clause
                    */
                case LIN_TX_MASTER_RES_COMMAND:
                    if(LIN_CH_SEND_HEADER_ERROR == u8Temp2)
                    {
                        TempReturn = LIN_TX_HEADER_ERROR;
                    }
                    else if(LIN_CH_SEND_DATA_ERROR == u8Temp2)
                    {
                        TempReturn = LIN_TX_ERROR;
                    }
                    else
                    {
                        TempReturn = LIN_NOT_OK;
                    }
                    break;
                case LIN_TX_SLAVE_RES_COMMAND:
                    if(LIN_CH_SEND_HEADER_ERROR == u8Temp2)
                    {
                        TempReturn = LIN_TX_HEADER_ERROR;
                    }
                    else
                    {
                        TempReturn = LIN_NOT_OK;
                    }
                    break;
                default:
                    TempReturn = LIN_NOT_OK;
                    break;
            }
            break;
        /* Rx error conditions */
        case LIN_NOISE_ERROR:
        case LIN_CHECKSUM_ERROR:
        case LIN_FRAMING_ERROR:
        case OVERFLOW_ERROR:
        case SLAVE_TIMEOUT_ERROR:
            /* this check that there's no data to be recived before. */
            if(ESCI_ZERO_U8 == Lin_ESCI_au8BufferCounter[u8Lin_ESCI])
            {
                TempReturn = LIN_RX_NO_RESPONSE;
                break;
            }
            /**
            * @violates @ref Lin_ESCI_c_REF_8 An unconditional break statement shall
            * terminate every non-empty switch clause
            */
        case UNREQUESTED_DATA_ERROR:
            TempReturn = LIN_RX_ERROR;
            break;
        case PHYSICAL_BUS_ERROR:
            u8Temp1 = Lin_au8TransmitHeaderCommand[u8Channel];
            u8Temp2 = Lin_au8LinChFrameStatus[u8Channel];

            switch(u8Temp1)
            {
                case LIN_TX_SLEEP_COMMAND:
                    /* Update Lin_au8TransmitHeaderCommand value to LIN_TX_NO_COMMAND */
                    Lin_au8TransmitHeaderCommand[u8Channel] = LIN_TX_NO_COMMAND;
                    /* Update LIN channel frame operation status to LIN_CH_NOT_READY_STATE */
                    Lin_au8LinChFrameStatus[u8Channel] = LIN_CH_NOT_READY_STATE;
                    /**
                    * @violates @ref Lin_ESCI_c_REF_8 An unconditional break statement shall
                    * terminate every non-empty switch clause
                    */
                case LIN_TX_MASTER_RES_COMMAND:
                    if(LIN_CH_SEND_HEADER_ERROR == u8Temp2)
                    {
                        TempReturn = LIN_TX_HEADER_ERROR;
                    }
                    else if(LIN_CH_SEND_DATA_ERROR == u8Temp2)
                    {
                        TempReturn = LIN_TX_ERROR;
                    }
                    else
                    {
                        TempReturn = LIN_NOT_OK;
                    }
                    break;
                case LIN_TX_SLAVE_RES_COMMAND:
                    if(LIN_CH_SEND_HEADER_ERROR == u8Temp2)
                    {
                        TempReturn = LIN_TX_HEADER_ERROR;
                    }
                    else
                    {
                        TempReturn = LIN_RX_ERROR;
                    }
                    break;
                default:
                    TempReturn = LIN_NOT_OK;
                    break;
            }

            break;
        case LIN_NO_ERROR :
            /* Check Lin frame status variable */
            switch(Lin_au8LinChFrameStatus[u8Channel])
            {

                case LIN_CH_SEND_HEADER:
                case LIN_CH_SEND_DATA:
                    TempReturn =  LIN_TX_BUSY;
                break;
                case LIN_CH_RECEIVE_DATA:
                    TempReturn =  LIN_RX_BUSY;
                break;
                /* Tx completed - Status Updated in ISR */
                case LIN_TX_COMPLETE_STATE:
                    TempReturn = LIN_TX_OK;
                break;
                /* Rx completed - Status Updated in ISR */
                case LIN_RX_COMPLETE_STATE:
                    /* Copy the data from hardware buffer */
                    Lin_ESCI_CopyData(u8Channel, pLinSduPtr);
                    TempReturn =  LIN_RX_OK;
                break;
                /* Tx completed - But master not received any data */
                case LIN_CH_RECEIVE_NOTHING_STATE:
                    TempReturn = LIN_RX_NO_RESPONSE;
                break;
                /* Channel Initialized or wakeup or all activity completed and ready to
                send next header */
                case LIN_CH_READY_STATE:
                    TempReturn = LIN_OPERATIONAL;
                break;
                /* Channel not ready */
                case LIN_CH_NOT_READY_STATE:
                    TempReturn = LIN_NOT_OK;
                break;
                default :
                    TempReturn = LIN_NOT_OK;
                break;
            }
        break;
        default:
            TempReturn = LIN_NOT_OK;
        break;
    }

    return TempReturn;
}

/**
* @brief   Copy the data received from the ESCI data registers to LinSduPtr.
* @details This function shall copy the received data in the provided buffer
*          addressed by the LinSduPtr pointer parameter.
*
* @param[in]   Channel LIN channel to be addressed.
* @param[out]  LinSduPtr pointer to pointer to a shadow buffer or memory
*              mapped LIN Hardware receive buffer where the current SDU is stored
*
* @return       void.
*
*
*
* @note         Internal driver function.
*/
/**
* @violates @ref Lin_ESCI_c_REF_6 External ... could be made static.
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
FUNC(void, LIN_CODE) Lin_ESCI_CopyData(CONST(uint8, AUTOMATIC) u8Channel,
                    P2VAR(uint8, AUTOMATIC, LIN_APPL_DATA) pLinSduPtr)
{
    VAR(uint8, AUTOMATIC) u8Loop;
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    /* Get the hardware Lin channel from logical channel */
     u8Lin_ESCI = Lin_pChannelConfigPtr[u8Channel]->u8LinHwChannel;
 
    for (u8Loop=ESCI_ZERO_U8;u8Loop<LIN_MAX_DATA_LENGTH;u8Loop++)
    {
        /* Copy LSB data received in LinSduPtr[] buffer */
        /**
        * @violates @ref Lin_ESCI_c_REF_5 pointer arithmetic other
        *                                     than array indexing used
        */
        pLinSduPtr[u8Loop]  = (Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[u8Loop]);
    }
}

/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
/**
* @brief   Interrupt handler for TX and RX on ESCI.
* @details This function shall manage all the RX and TX ISRs on the
*          addressed channel.
*
* @param[in]   Channel LIN channel to be addressed.
*
* @return       void.
*
* @implements   Lin_ESCI_InterruptHandler_Activity
*
* @note         Internal driver function.
*/
FUNC(void, LIN_CODE) Lin_ESCI_InterruptHandler(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;
    VAR(uint8, AUTOMATIC) u8LogicalChannel = (uint8)0U;
    VAR(boolean, AUTOMATIC) bIsTxErrorOnSleepCmd = (boolean)FALSE;
    VAR(uint16, AUTOMATIC) u16ESCI_status;
    VAR(uint16, AUTOMATIC) u16ESCI_control;
    VAR(uint16, AUTOMATIC) u16Lin_status;
    VAR(uint16, AUTOMATIC) u16Lin_control;
    VAR(uint16, AUTOMATIC) u16Lin_control2;
    VAR(boolean, AUTOMATIC) bESCI_reset = (boolean)FALSE;

    /* Check if driver is initialized */
    if( NULL_PTR != Lin_pcConfigPtr )
    {
        /* Store hardware channel of ESCI module in which the interrupt arose */
        u8Lin_ESCI = (uint8)u8Channel;

        while(LIN_HW_MAX_AVAILABLE_MODULES > u8LogicalChannel)
        {
             if((sint32)u8Lin_ESCI == Lin_as8ChannelHardwareMap[Lin_pChannelConfigPtr[u8LogicalChannel]->u8LinChannelID])
             {
                break;
            }
            else
            {
                u8LogicalChannel++;
            }
        }

        if(LIN_HW_MAX_AVAILABLE_MODULES > u8LogicalChannel)
        {
            /* Get the logical channel index from physical channel */
             u8LogicalChannel = Lin_pChannelConfigPtr[u8LogicalChannel]->u8LinChannelID;
             /* Get the status of ESCI_IFSR1 interrupt flags */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            u16ESCI_status = REG_READ16(ESCI_IFSR1_ADDR32(u8Lin_ESCI));

            /* Get the status of control register ESCI_CR2 */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            u16ESCI_control = REG_READ16(ESCI_CR2_ADDR32(u8Lin_ESCI));

            /* Get the status of ESCI_IFSR2 interrupt flags */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            u16Lin_status = REG_READ16(ESCI_IFSR2_ADDR32(u8Lin_ESCI));

            /* Get the status of control register ESCI_LCR1 */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            u16Lin_control = REG_READ16(ESCI_LCR1_ADDR32(u8Lin_ESCI));

            /* Get the status of control register ESCI_LCR2 */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            *
            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
            */
            u16Lin_control2 = REG_READ16(ESCI_LCR2_ADDR32(u8Lin_ESCI));

            #ifdef LIN_USE_MSC
             if ((uint8)STD_ON == Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_MscEnabled)
             {
                /* If something was received and there are no errors */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                if((0U == (u16ESCI_status & ESCI_IFSR1_RDRF_MASK_U16)) && \
                   (0U == (u16ESCI_status & ESCI_IFSR1_OR_MASK_U16)) && \
                   (0U == (u16ESCI_status & ESCI_IFSR1_FE_MASK_U16)) && \
                   (0U == (u16ESCI_status & ESCI_IFSR1_NF_MASK_U16)) && \
                   (0U == (u16ESCI_status & ESCI_IFSR1_PF_MASK_U16)) \
                  )
                {
                    /* Update MSC channel frame operation status to MSC_RUN */
                    MscBuffer[u8LogicalChannel].State = MSC_RUN;

                    /* No errors occurred on RX. */
                    MscBuffer[u8LogicalChannel].Errors = 0U;

                    /* Read the data from Data Register and store into the addressed channel's MscBuffer */
                    MscBuffer[u8LogicalChannel].Data = (uint8)(REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_RD_TD_7_0_MASK_U16);

                    /* Which is the MSC frame format ? */
                     if (Lin_pChannelConfigPtr[u8LogicalChannel]->Lin_MscFrameFormat == MSC_16_BITS)
                     {
                        /* Use 16-bit format (1 start bit, 12 data bits, 1 parity bit, 2 stop bits) */
                        /* The frame contains 4-bit address field and 8 data bits. */
                        /* LSB is received first. */
                        MscBuffer[u8LogicalChannel].Address = (uint8)(REG_READ16(ESCI_SDR_ADDR32(u8Lin_ESCI)) & ESCI_SDR_RD_11_8_MASK_U16);
                    }
                    else
                    {
                        /* Use 12-bit format (1 start bit, 8 data bits, 1 parity bit, 2 stop bits) */
                        /* The frame contains only 8 data bits. */
                        /* LSB is received first. */
                        MscBuffer[u8LogicalChannel].Address = 0U;
                    }
                }
                /* If there is an error set the corresponding flag in the MSC buffer */
                else
                {
                    /* An error occurred on RX: it can be an Overrun, Framing, Noise or Parity error. */
                    MscBuffer[u8LogicalChannel].Errors = 1U;

                    /* Check if OR Flag is set */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    if (0U != (u16ESCI_status & ESCI_IFSR1_OR_MASK_U16))
                    {
                        /* Overrun Error flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_OR_MASK_U16);

                        MscBuffer[u8LogicalChannel].State = MSC_OVERRUN_ERROR;
                    }
                    /* Check if FE Flag is set */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    if (0U != (u16ESCI_status & ESCI_IFSR1_FE_MASK_U16))
                    {
                        /* Framing Error flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                        MscBuffer[u8LogicalChannel].State = MSC_FRAMING_ERROR;
                    }
                    /* Check if NF Flag is set */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    if (0U != (u16ESCI_status & ESCI_IFSR1_NF_MASK_U16))
                    {
                        /* Noise Error flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

                        MscBuffer[u8LogicalChannel].State = MSC_NOISE_ERROR;
                    }
                    /* Check if PF Flag is set */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    if (0U != (u16ESCI_status & ESCI_IFSR1_PF_MASK_U16))
                    {
                        /* Parity Error flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_PF_MASK_U16);

                        MscBuffer[u8LogicalChannel].State = MSC_PARITY_ERROR;
                    }
                }
                /* Clear Receive Data Register Full Interrupt Flag as error occured */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                *
                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                */
                REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_RDRF_MASK_U16);
            }
            else
            {
            #endif /* LIN_USE_MSC */

                /* Check if Noise Interrupt Flag is set */
                if ((0U != (u16ESCI_status & ESCI_IFSR1_NF_MASK_U16)) && \
                    /**
                    * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                    * '&&'.
                    */
                    (0U != (u16ESCI_control & ESCI_CR2_NFIE_MASK_U16)))
                {
                    /* Clear the Noise Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);
                    /* Set LIN channel frame error status to LIN_NOISE_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = LIN_NOISE_ERROR;
                    if (Lin_au8LinChFrameStatus[u8LogicalChannel] == LIN_CH_SEND_HEADER)
                    {
                        /* LIN_CH_SEND_HEADER */
                        /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_HEADER_ERROR;
                    }
                    else
                    {
                        /* LIN_CH_SEND_DATA */
                        /* Update LIN channel frame operation status to LIN_CH_SEND_DATA_ERROR */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_DATA_ERROR;
                    }

                    /* The ESCI hardware should be reset */
                    bESCI_reset = (boolean)TRUE;

                }
                /* Check if Frame error Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16ESCI_status & ESCI_IFSR1_FE_MASK_U16)) && \
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                  (0U != (u16ESCI_control & ESCI_CR2_FEIE_MASK_U16)))
                {
                    /* Framing Error flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                    /* Set LIN channel frame error status to LIN_FRAMING_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = LIN_FRAMING_ERROR;

                    /* The ESCI hardware should be reset */
                    bESCI_reset = (boolean)TRUE;

                }
                /* Check if Bit Error Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16ESCI_status & ESCI_IFSR1_BERR_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16ESCI_control & ESCI_CR2_BERRIE_MASK_U16)))
                {
                    /* Clear Bit Error Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_BERR_MASK_U16);
                    /* Set LIN channel frame error status to LIN_BIT_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = LIN_BIT_ERROR;
                    /* Check if error was on sleep frame transmitting */
                    if (LIN_TX_SLEEP_COMMAND == Lin_au8TransmitHeaderCommand[u8LogicalChannel])
                    {
                        bIsTxErrorOnSleepCmd = (boolean)TRUE;
                    }
                    if (LIN_CH_SEND_HEADER == Lin_au8LinChFrameStatus[u8LogicalChannel])
                    {
                        /* LIN_CH_SEND_HEADER */
                        /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_HEADER_ERROR;
                    }
                    else
                    {
                        /* LIN_CH_SEND_DATA */
                        /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_DATA_ERROR;
                    }

                    /* The ESCI hardware should be reset */
                    bESCI_reset = (boolean)TRUE;

                }
                /* Check if Slave Timeout Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16Lin_status & ESCI_IFSR2_STO_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16Lin_control & ESCI_LCR1_STIE_MASK_U16)))
                {
                    /* Clear Slave Timeout Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_STO_MASK_U16);
#if (LIN_DISABLE_FRAME_TIMEOUT == STD_OFF)
                    /* Set LIN channel frame error status to SLAVE_TIMEOUT_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = SLAVE_TIMEOUT_ERROR;

                    /* The ESCI hardware should be reset */
                    bESCI_reset = (boolean)TRUE;

#endif  /* LIN_DISABLE_FRAME_TIMEOUT */
                }
                /* Check if Physical Bus Error Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16Lin_status & ESCI_IFSR2_PBERR_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16Lin_control & ESCI_LCR1_PBIE_MASK_U16)))
                {
                    /* Clear Physical Bus Error Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_PBERR_MASK_U16);
                    /* Set LIN channel frame error status to PHYSICAL_BUS_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = PHYSICAL_BUS_ERROR;

                    /* Check if error was on sleep frame transmitting */
                    if (LIN_TX_SLEEP_COMMAND == Lin_au8TransmitHeaderCommand[u8LogicalChannel])
                    {
                        bIsTxErrorOnSleepCmd = (boolean)TRUE;
                    }

                    if (LIN_CH_SEND_HEADER == Lin_au8LinChFrameStatus[u8LogicalChannel])
                    {
                        /* LIN_CH_SEND_HEADER */
                        /* Update LIN channel frame operation status to LIN_CH_SEND_HEADER_ERROR */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_HEADER_ERROR;
                    }
                    else
                    {
                        /* LIN_CH_SEND_DATA */
                        /* Update LIN channel frame operation status to LIN_CH_SEND_DATA_ERROR */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_DATA_ERROR;
                    }

                    /* The ESCI hardware should be reset */
                    bESCI_reset = (boolean)TRUE;

                }
                /* Check if Checksum Error Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16Lin_status & ESCI_IFSR2_CKERR_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16Lin_control & ESCI_LCR1_CKIE_MASK_U16)))
                {
                    /* Clear Checksum Error Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_CKERR_MASK_U16);

                    /* Set LIN channel frame error status to LIN_CHECKSUM_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = LIN_CHECKSUM_ERROR;

                    /* The ESCI hardware should be reset */
                    bESCI_reset = (boolean)TRUE;

                }
                /* Check if Overflow Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16Lin_status & ESCI_IFSR2_OVFL_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16Lin_control2 & ESCI_LCR2_OFIE_MASK_U16)))
                {
                    /* Clear Overflow Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_OVFL_MASK_U16);

                    /* Set LIN channel frame error status to OVERFLOW_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = OVERFLOW_ERROR;

                    /* The ESCI hardware should be reset */
                    bESCI_reset = (boolean)TRUE;

                }
                /* Check if Unrequested Data Received Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                else if (0U != (u16Lin_status & ESCI_IFSR2_UREQ_MASK_U16))
                {
                    /* Clear Unrequested Data Received Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_UREQ_MASK_U16);
                    /* Set LIN channel frame error status to UNREQUESTED_DATA_ERROR */
                    Lin_au8LinChFrameErrorStatus[u8LogicalChannel] = UNREQUESTED_DATA_ERROR;
                }
                /* Check if Frame Complete Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                else if (0U != (u16Lin_status & ESCI_IFSR2_FRC_MASK_U16))
                {
                    /* Clear Frame Complete Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_FRC_MASK_U16);
                    /* Check if error was on sleep frame transmitting */
                    if (LIN_TX_SLEEP_COMMAND == Lin_au8TransmitHeaderCommand[u8LogicalChannel])
                    {
                         if ((uint8)STD_ON == Lin_pChannelConfigPtr[u8LogicalChannel]->u16LinChannelWakeupSupport)
                         {
                            SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_19();
                            {
                                /* Clear Wake-Up flag */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_LWAKE_MASK_U16);

                                /* Enable wake up interrupt */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_WUIE_MASK_U16);

                                /* Enable Receiver*/
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

                                /* Clear TX Ready Interrupt Flag */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_TXRDY_MASK_U16);

                                /* Disable TX interrupt */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);

                                /* Clear Framing Error Interrupt Flag */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                                /* Disable Frame Error Interrupt */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FEIE_MASK_U16);

                                /* Clear Noise Interrupt Flag */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

                                /* Disable Noise Interrupt */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_NFIE_MASK_U16);
                            }
                            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_19();

                        }
                         /* Set Channel state to SLEEP state */
                        Lin_au8LinChStatus[u8LogicalChannel] = LIN_CH_SLEEP_STATE;
 
                        /* Update LIN channel frame operation status to LIN_CH_NOT_READY_STATE */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_NOT_READY_STATE;
                    }
                    else
                    {
                        /* Check the Type of Response */
                        if((uint8)LIN_MASTER_RESPONSE == Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE)
                        {
                            /* Master response */
                            /* Update LIN channel frame operation status to LIN_TX_COMPLETE_STATE */
                                Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_TX_COMPLETE_STATE;
                        }
                        else
                        {
                            /* Slave response */
                            /* Update LIN channel frame operation status to LIN_RX_COMPLETE_STATE */
                            Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_RX_COMPLETE_STATE;
                        }
                    }

                    SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_20();
                    {
                        /* Disable Frame Complete Interrupt */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_FCIE_MASK_U16);
                    }
                    SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_20();
                }

                /* Check if Receive Data Ready Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16Lin_status & ESCI_IFSR2_RXRDY_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16Lin_control & ESCI_LCR1_RXIE_MASK_U16)))
                {
                    /* First byte received ? */
                    if( Lin_ESCI_au8BufferCounter[u8Lin_ESCI] == ESCI_ZERO_U8)
                    {
                        /* First byte received */
                        /* Update LIN channel frame operation status to LIN_CH_RECEIVE_DATA */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_RECEIVE_DATA;
                    }
                    /* Store data in buffer */
                    Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[Lin_ESCI_au8BufferCounter[u8Lin_ESCI]] =\
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                                (REG_READ8(ESCI_LRR_ADDR32(u8Lin_ESCI)) & ESCI_LRR_D_MASK_U8);

                    /* Increment counter by 1 */
                    Lin_ESCI_au8BufferCounter[u8Lin_ESCI]++;
                    /* Is this the last byte ? */
                    if(Lin_ESCI_au8BufferCounter[u8Lin_ESCI] >= Lin_ESCI_au8BufferCounterMax[u8Lin_ESCI])
                    {
                        /* Last byte has been received */
                        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_21();
                        {
                            /* Disable Receive Data Ready Interrupt */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_RXIE_MASK_U16);
                        }
                        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_21();

                        /* Clear Receive Data Ready Interrupt flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_RXRDY_MASK_U16);

                    }
                    else
                    {
                    #ifdef LIN_USE_DMA
                        /* Is DMA enabled in the configuration for this Lin channel */
                         if((uint8)STD_ON == Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_DMAEnabled)
                         {
                            SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_22();
                            {
                                /* Disable Receive Data Ready Interrupt */
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                *
                                * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                                */
                                REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_RXIE_MASK_U16);
                            }
                            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_22();

                            /* Clear Receive Data Ready Interrupt Flag */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_RXRDY_MASK_U16);

                            /* Receive DMA enabled and start a DMA transfer */
                             Mcl_DmaEnableHwRequest(Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_RxDMAChannel);
                             /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            */
                             Mcl_DmaTcdSetIntMaj((uint32 *)Mcl_DmaGetChannelTcdAddress(Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_RxDMAChannel));
 
                            SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_23();
                            {
                                /**
                                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                                */
                                REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);
                            }
                            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_23();

                        }
                        else
                        {
                    #endif  /* LIN_USE_DMA */
                            /* ISR driven */
                            /* Clear Receive Data Ready Interrupt flag */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_RXRDY_MASK_U16);
                #ifdef LIN_USE_DMA
                        }
                #endif  /* LIN_USE_DMA */
                    }
                }
                /* Check if Transmit Data Ready Interrupt Flag is set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16Lin_status & ESCI_IFSR2_TXRDY_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16Lin_control & ESCI_LCR1_TXIE_MASK_U16)))
                {
                    /* Clear Transmit Data Ready Interrupt Flag */
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    *
                    * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                    */
                    REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_TXRDY_MASK_U16);


                    if(((Lin_ESCI_au8BufferCounter[u8Lin_ESCI] < MASTER_RESPONSE_HEADER_WRITE_COUNT_U8) &&
                    (((uint8)LIN_MASTER_RESPONSE == Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE)||
                    (SLEEP_CMD_TYPE_U8 == Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE)))
                        ||  ((Lin_ESCI_au8BufferCounter[u8Lin_ESCI] < SLAVE_RESPONSE_HEADER_WRITE_COUNT_U8)
                        && ((uint8)LIN_SLAVE_RESPONSE == Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE)))
                    {
                        /* Send header */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE8(ESCI_LTR_ADDR32(u8Lin_ESCI), (Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[Lin_ESCI_au8BufferCounter[u8Lin_ESCI]]));

                        /* Update LIN channel frame status to LIN_CH_SEND_HEADER */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_HEADER;
                    }
                    else
                    {
                        if(((uint8)LIN_MASTER_RESPONSE == Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE)||
                        (SLEEP_CMD_TYPE_U8 == Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE))
                        {
                            /* Send data */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_WRITE8(ESCI_LTR_ADDR32(u8Lin_ESCI), (Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[(Lin_ESCI_au8BufferCounter[u8Lin_ESCI]) \
                                        - MASTER_RESPONSE_HEADER_WRITE_COUNT_U8]));
                            if((uint8)LIN_MASTER_RESPONSE == Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE)
                            {
                                /* Update LIN channel frame operation status to LIN_CH_SEND_DATA */
                                Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_SEND_DATA;
                            }
                        }
                    }
                    /* Increment counter by 1 */
                    Lin_ESCI_au8BufferCounter[u8Lin_ESCI]++;

                    /* Is this the last byte ? */
                    if(Lin_ESCI_au8BufferCounter[u8Lin_ESCI] >= Lin_ESCI_au8BufferCounterMax[u8Lin_ESCI])
                    {
                        /* Last byte has been transmitted */
                        if((LIN_CH_SEND_HEADER == Lin_au8LinChFrameStatus[u8LogicalChannel]) &&
                       ((uint8)LIN_MASTER_RESPONSE != Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE))
                        {
                            /* Set max count */
                            Lin_ESCI_au8BufferCounterMax[u8Lin_ESCI] =
                                    Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[ESCI_HEADER_ONE_U8];
                            /* reset counter */
                            Lin_ESCI_au8BufferCounter[u8Lin_ESCI] = ESCI_ZERO_U8;
                        }
                        /* Last write of the header, clear all error flags and RXRDY */
                        /* Clear the Noise Interrupt Flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

                        /* Framing Error flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                        /* Clear Bit Error Interrupt Flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_BERR_MASK_U16);

                        /* Clear Slave Timeout Interrupt Flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_STO_MASK_U16);

                        /* Clear Physical Bus Error Interrupt Flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_PBERR_MASK_U16);

                        /* Clear Checksum Error Interrupt Flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_CKERR_MASK_U16);

                        /* Clear Overflow Interrupt Flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_OVFL_MASK_U16);

                        /* Clear Unrequested Data Received Interrupt Flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_UREQ_MASK_U16);

                        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_24();
                        {
                            /* Disable Transmit Data Ready Interrupt */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);
                        }
                        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_24();

                    }
                }
                /* Wake up interrupt */
                /* Wake up flag set */
                /**
                * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                * '&&'.
                */
                else if ((0U != (u16Lin_status & ESCI_IFSR2_LWAKE_MASK_U16)) && \
                        /**
                        * @violates @ref Lin_ESCI_c_REF_4 boolean expression required for operator:
                        * '&&'.
                        */
                        (0U != (u16Lin_control & ESCI_LCR1_WUIE_MASK_U16)))
                {
                    SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_25();
                    {
                        /* Disable wake up interrupt */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_WUIE_MASK_U16);
                        /* Clear Wake-Up flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_LWAKE_MASK_U16);
                    #if (IPV_ESCI >= IPV_ESCI_08_00_00_00)
                    /* eSCI V.8 specific code*/
                        /* Clear Framing Error flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                        /* The ESCI hardware should be reset */
                        bESCI_reset = (boolean)TRUE;

                        /* Enable Frame Error Interrupt */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_SET16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FEIE_MASK_U16);
                    #endif
                    }
                    SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_25();

                    /* Check whether the Lin channel status is in LIN_CH_SLEEP_STATE */
                    if (LIN_CH_SLEEP_STATE == Lin_au8LinChStatus[u8LogicalChannel])
                    {
                        /* Check whether wake up detection is enabled */
                         if ((uint8)STD_ON == Lin_pChannelConfigPtr[u8LogicalChannel]->u16LinChannelWakeupSupport)
                         {
                            /* Indicates a valid timer wakeup event to ECU State Manager */
                             EcuM_CheckWakeup(Lin_pChannelConfigPtr[u8LogicalChannel]->LinChannelEcuMWakeupSource);
                         }
                        /* Set Channel state Operational */
                        Lin_au8LinChStatus[u8LogicalChannel] = LIN_CH_OPERATIONAL;
                        /* Update LIN channel frame operation status to LIN_CH_READY_STATE */
                        Lin_au8LinChFrameStatus[u8LogicalChannel] = LIN_CH_READY_STATE;
                    }
                }
                else
                {
                    /* Do nothing */
                }

                if((boolean)TRUE == bESCI_reset)
                {
                    SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_26();
                    {
                        /* Set LRES bit of LCR1 register to reset the LIN state machine */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

                        /* These redundant line are required since LIN state machine gets RESET correctly after
                            setting LRES bit three times and  then clear it */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_LRES_MASK_U16);

                        /* Disable Transmitter */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);

                        /* Disable Receiver */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_CLEAR16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

                        /* Clear LRES bit of LCR1 register to reset the LIN state machine */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI),ESCI_LCR1_LRES_MASK_U16);

                        /* Enable Transmitter */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_TE_MASK_U16);

                        /* Enable Receiver */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);
                    }
                    SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_26();

                }

                /* Check if error was on sleep frame transmitting */
                if ((boolean)TRUE == bIsTxErrorOnSleepCmd) /* Error was on sleep frame transmitting */
                {
                    /* Check whether wake up detection is enabled */
                     if ((uint8)STD_ON == Lin_pChannelConfigPtr[u8LogicalChannel]->u16LinChannelWakeupSupport)
                     {
                        /* Wake up detection enabled */
                        /* Clear Wake-Up flag */
                        /**
                        * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                        *
                        * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                        */
                        REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_LWAKE_MASK_U16);

                        SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_27();
                        {
                            /* Enable wake up interrupt */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_BIT_SET16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_WUIE_MASK_U16);

                            /* Enable Receiver*/
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_BIT_SET16(ESCI_CR1_ADDR32(u8Lin_ESCI), ESCI_CR1_RE_MASK_U16);

                            /* Clear TX Ready Interrupt Flag */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_WRITE16(ESCI_IFSR2_ADDR32(u8Lin_ESCI), ESCI_IFSR2_TXRDY_MASK_U16);

                            /* Disable TX interrupt */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_BIT_CLEAR16(ESCI_LCR1_ADDR32(u8Lin_ESCI), ESCI_LCR1_TXIE_MASK_U16);

                            /* Clear Framing Error Interrupt Flag */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI), ESCI_IFSR1_FE_MASK_U16);

                            /* Disable Frame Error Interrupt */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_FEIE_MASK_U16);

                            /* Clear Noise Interrupt Flag */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_WRITE16(ESCI_IFSR1_ADDR32(u8Lin_ESCI),ESCI_IFSR1_NF_MASK_U16);

                            /* Disable Noise Interrupt */
                            /**
                            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                            *
                            * @violates @ref Lin_ESCI_c_REF_11 cast should not be performed
                            */
                            REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_NFIE_MASK_U16);
                        }
                        SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_27();
                    }
                     /* Set Channel state Sleep */
                    Lin_au8LinChStatus[u8LogicalChannel] = LIN_CH_SLEEP_STATE;
 
                    /* Reset IsTxErrorOnSleepCmd flag */
                    bIsTxErrorOnSleepCmd = (boolean)FALSE;
                }
        #ifdef LIN_USE_MSC
            }
        #endif  /* LIN_USE_MSC */
        }
    }

    return; /* exit function with no return */
}

#ifdef LIN_USE_DMA
/**
* @brief   Interrupt handler for DMA's TX ESCI.
* @details This function shall manage all the DMA TX ISRs on the
*          addressed channel.
*
* @param[in]   Channel LIN channel to be addressed.
*
* @return       void.
*
*
* @note         Internal driver function for DMA functionality.
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
/* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
FUNC(void, LIN_CODE) Lin_ESCI_TxInterruptHandler_eDma(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8LogicalChannel = (uint8)0U;
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

    /* Check if driver is initialized */
    if( NULL_PTR != Lin_pcConfigPtr )
    {
        /* Store hardware channel of ESCI module in which the interrupt arose */
        u8Lin_ESCI = (uint8)u8Channel;

        while(LIN_HW_MAX_AVAILABLE_MODULES > u8LogicalChannel)
        {
             if((sint32)u8Lin_ESCI == Lin_as8ChannelHardwareMap[Lin_pChannelConfigPtr[u8LogicalChannel]->u8LinChannelID])
             {
                break;
            }
            else
            {
                u8LogicalChannel++;
            }
        }

        if(LIN_HW_MAX_AVAILABLE_MODULES > u8LogicalChannel)
        {
            /* Get the logical channel index from physical channel */
             u8LogicalChannel = Lin_pChannelConfigPtr[u8LogicalChannel]->u8LinChannelID;
 
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            */
             Mcl_DmaAcknowledgeInterrupt(Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_TxDMAChannel);
             SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_28();
            {
                /* Transmit DMA disabled */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_TXDMA_MASK_U16);
            }
            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_28();

            /* Sent Header && SLAVE_RESPONSE ? */
            if((uint8)LIN_MASTER_RESPONSE != (Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_TYPE))
            {
                /* Destination address -> address of channel shadow buffer second byte ->
                first byte will be received with ISR */
                /* DMA_RX  */
                #if (IPV_ESCI == IPV_ESCI_07_02_01_01)
                    Lin_eSCI_DmaConfigDescriptor.saddr = ESCI_LRR_ADDR32(u8Lin_ESCI);
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    Lin_eSCI_DmaConfigDescriptor.daddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[1];
                    Lin_eSCI_DmaConfigDescriptor.ssize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.dsize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.soff = 0U;
                    Lin_eSCI_DmaConfigDescriptor.doff = 1U;
                    Lin_eSCI_DmaConfigDescriptor.smod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.dmod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.num_bytes = 1U;
                    Lin_eSCI_DmaConfigDescriptor.iter = (uint32)Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[1] - 1U;
                #else
                    Lin_eSCI_DmaConfigDescriptor.u32saddr = ESCI_LRR_ADDR32(u8Lin_ESCI);
                    /**
                    * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                    */
                    Lin_eSCI_DmaConfigDescriptor.u32daddr = (uint32)&Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->au8Lin_DATA[1];
                    Lin_eSCI_DmaConfigDescriptor.u32ssize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32dsize = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32soff = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32doff = 1U;
                    Lin_eSCI_DmaConfigDescriptor.u32smod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32dmod = 0U;
                    Lin_eSCI_DmaConfigDescriptor.u32num_bytes = 1U;
                    Lin_eSCI_DmaConfigDescriptor.u32iter = (uint32)Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[1] - 1U;
                #endif
                 Mcl_DmaConfigChannel(Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_RxDMAChannel, &Lin_eSCI_DmaConfigDescriptor);
 
                Lin_ESCI_au8BufferCounterMax[u8Lin_ESCI] = Lin_ESCI_pChShadowBuffPtr[u8Lin_ESCI]->u8Lin_HEADER[1];
                /* reset counter */
                Lin_ESCI_au8BufferCounter[u8Lin_ESCI] = 0U;
            }
            /* Clear DMA interrupt request */
            /* Disable the interrupt for RX DMA channel */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            */
             Mcl_DmaDisableNotification(Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_TxDMAChannel);
         }
    }
}

/**
* @brief   Interrupt handler for DMA's RX ESCI.
* @details This function shall manage all the DMA RX ISRs on the
*          addressed channel.
*
* @param[in]   Channel LIN channel to be addressed.
*
* @return       void.
*
*
* @note         Internal driver function for DMA functionality.
*/
/* @violates @ref Lin_ESCI_c_REF_10 Re-use of C90 reserved identifier */
/* @violates @ref Lin_ESCI_c_REF_9 Identifiers shall not rely on the significance of more than 31 characters.*/
FUNC(void, LIN_CODE) Lin_ESCI_RxInterruptHandler_eDma(CONST(uint8, AUTOMATIC) u8Channel)
{
    VAR(uint8, AUTOMATIC) u8LogicalChannel = (uint8)0U;
    VAR(uint8, AUTOMATIC) u8Lin_ESCI;

        /* Check if driver is initialized */
    if( NULL_PTR != Lin_pcConfigPtr )
    {
        /* Store hardware channel of ESCI module in which the interrupt arose */
        u8Lin_ESCI = (uint8)u8Channel;

        while(LIN_HW_MAX_AVAILABLE_MODULES > u8LogicalChannel)
        {
             if((sint32)u8Lin_ESCI == Lin_as8ChannelHardwareMap[Lin_pChannelConfigPtr[u8LogicalChannel]->u8LinChannelID])
             {
                break;
            }
            else
            {
                u8LogicalChannel++;
            }
        }

        if(LIN_HW_MAX_AVAILABLE_MODULES > u8LogicalChannel)
        {
            /* Get the logical channel index from physical channel */
             u8LogicalChannel = Lin_pChannelConfigPtr[u8LogicalChannel]->u8LinChannelID;
 
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            */
             Mcl_DmaAcknowledgeInterrupt(Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_RxDMAChannel);
 
            SchM_Enter_Lin_LIN_EXCLUSIVE_AREA_29();
            {
                /* Receive DMA disabled */
                /**
                * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
                */
                REG_BIT_CLEAR16(ESCI_CR2_ADDR32(u8Lin_ESCI), ESCI_CR2_RXDMA_MASK_U16);
            }
            SchM_Exit_Lin_LIN_EXCLUSIVE_AREA_29();

            /* Clear DMA interrupt request */
            /* Disable the interrupt for RX DMA channel */
            /**
            * @violates @ref Lin_ESCI_c_REF_3 cast from unsigned int to pointer
            */
             Mcl_DmaDisableNotification(Lin_pChannelConfigPtr[u8LogicalChannel]->u8Lin_RxDMAChannel);
         }
    }
}

#endif  /* LIN_USE_DMA */

#define LIN_STOP_SEC_CODE
/**
* @violates @ref Lin_ESCI_c_REF_1 Precautions shall be taken in order to prevent the contents
*        of a header file being included twice.
*/
/**
* @violates @ref Lin_ESCI_c_REF_2 only preprocessor
*                            statements and comments before '#include'
*/
 #include "MemMap.h"
 
#ifdef __cplusplus
}
#endif

/** @} */
