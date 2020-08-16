/**
*   @file    Port_Igf.c
*
*   @version 1.0.1
*
*   @brief   AUTOSAR Port - IGF Low level driver implementation.
*   @details Implementation of the IGF low level driver.
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
#ifdef __cplusplus
extern "C" {
#endif

/**
*  @page misra_violations MISRA-C:2004 violations
*
*  @section Port_Igf_C_REF_1
*  Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
*  '#include'. MemMap.h is included after each section define in order to set the current memory section as defined by AUTOSAR.
*
*  @section Port_Igf_C_REF_2
*  Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h
*  This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
*  @section Port_Igf_C_REF_3
*  Violates MISRA 2004 Required Rule 1.4, Identifier clash. The used compilers/linkers allow more than 31 characters 
*  significance for external identifiers.
*
*  @section Port_Igf_C_REF_4
*  Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
*  This macro compute the address of any register by using the hardware offset of the controller.
*  The address calculated as an unsigned int is passed to  a macro for initializing the pointer
*  with that address. (ex: see REG_WRITE32 macro).
*
*  @section Port_Igf_C_REF_5
*  Violates MISRA 2004 Required Rule 17.4, pointer arithmetic other than array indexing used.
*  This violation is due to the use of pointer arithmetic, to access the channel parameters,
*  the indexing of the pointer is taken care and hence the unintended memory location will not
*  be accessed.
*
*  @section Port_Igf_C_REF_6
*  Violates MISRA 2004 Required Rule 8.10,
*  All declarations and definitions of objects or functions at file scope shall
*  have internal linkage unless external linkage is required.
*  This warning appears when defining functions or objects that will be used by the upper layers.
*
*  @section Port_Igf_C_REF_7
*  Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between a pointer type and 
*  an integral type. The cast is used to access memory mapped registers.
*
*  @section [global]
*  Violates MISRA 2004 Required Rule 5.1, Identifiers(internal and external) shall not rely 
*  on the significance of more than 31 characters.The used compilers use more than 31 chars
*  for identifiers.
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/
#include "Std_Types.h"
#include "StdRegMacros.h"
#include "Port_Reg_eSys_Igf.h"
#include "Port_Igf.h"

/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/*
* @brief Parameters that shall be published within the driver header file and also in the
* module's description file
*/
#define PORT_IGF_VENDOR_ID_C                     43
/* @violates @ref Port_Igf_C_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define PORT_IGF_AR_RELEASE_MAJOR_VERSION_C      4
/* @violates @ref Port_Igf_C_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define PORT_IGF_AR_RELEASE_MINOR_VERSION_C      0
/* @violates @ref Port_Igf_C_REF_3 Violates MISRA 2004 Required Rule 1.4 */
#define PORT_IGF_AR_RELEASE_REVISION_VERSION_C   3
#define PORT_IGF_SW_MAJOR_VERSION_C              1
#define PORT_IGF_SW_MINOR_VERSION_C              0
#define PORT_IGF_SW_PATCH_VERSION_C              1

/*=================================================================================================
*                                      FILE VERSION CHECKS
=================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if the files Port_Igf.c and Std_Types.h are of the same version */
   #if ((PORT_IGF_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
        (PORT_IGF_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION)    \
       )
       #error "AutoSar Version Numbers of Port_Igf.c and Std_Types.h are different"
   #endif
    /* Check if the files Port_Igf.c and StdRegMacros.h are of the same version */
   #if ((PORT_IGF_AR_RELEASE_MAJOR_VERSION_C != STDREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
        (PORT_IGF_AR_RELEASE_MINOR_VERSION_C != STDREGMACROS_AR_RELEASE_MINOR_VERSION)    \
       )
       #error "AutoSar Version Numbers of Port_Igf.c and StdRegMacros.h are different"
   #endif
#endif


/* Check if Port_Igf.c and Port_Igf.h are of the same vendor */
#if (PORT_IGF_VENDOR_ID_C != PORT_IGF_VENDOR_ID_H)
    #error "Port_Igf.c and Port_Igf.h have different vendor ids"
#endif
/* Check if Port_Igf.c and Port_Igf.h are of the same Autosar version */
#if ((PORT_IGF_AR_RELEASE_MAJOR_VERSION_C    != PORT_IGF_AR_RELEASE_MAJOR_VERSION_H) || \
     (PORT_IGF_AR_RELEASE_MINOR_VERSION_C    != PORT_IGF_AR_RELEASE_MINOR_VERSION_H) || \
     (PORT_IGF_AR_RELEASE_REVISION_VERSION_C != PORT_IGF_AR_RELEASE_REVISION_VERSION_H) \
    )
  #error "AutoSar Version Numbers of Port_Igf.c and Port_Igf.h are different"
#endif
/* Check if Port_Igf.c and Port_Igf.h are of the same software version */
#if ((PORT_IGF_SW_MAJOR_VERSION_C != PORT_IGF_SW_MAJOR_VERSION_H) || \
     (PORT_IGF_SW_MINOR_VERSION_C != PORT_IGF_SW_MINOR_VERSION_H) || \
     (PORT_IGF_SW_PATCH_VERSION_C != PORT_IGF_SW_PATCH_VERSION_H)    \
    )
  #error "Software Version Numbers of Port_Igf.c and Port_Igf.h are different"
#endif

/* Check if Port_Igf.c and Port_Reg_eSys_Igf.h are of the same vendor */
#if (PORT_IGF_VENDOR_ID_C != PORT_REGESYS_IGF_VENDOR_ID)
    #error "Port_Igf.c and Port_Reg_eSys_Igf.h have different vendor ids"
#endif
/* Check if Port_Igf.c and Port_Reg_eSys_Igf.h are of the same Autosar version */
#if ((PORT_IGF_AR_RELEASE_MAJOR_VERSION_C    != PORT_REGESYS_IGF_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_IGF_AR_RELEASE_MINOR_VERSION_C    != PORT_REGESYS_IGF_AR_RELEASE_MINOR_VERSION) || \
     (PORT_IGF_AR_RELEASE_REVISION_VERSION_C != PORT_REGESYS_IGF_AR_RELEASE_REVISION_VERSION) \
    )
   #error "AutoSar Version Numbers of Port_Igf.c and Port_Reg_eSys_Igf.h are different"
#endif
/* Check if Port_Igf.c and Port_Reg_eSys_Igf.h are of the same software version */
#if ((PORT_IGF_SW_MAJOR_VERSION_C != PORT_REGESYS_IGF_SW_MAJOR_VERSION) || \
     (PORT_IGF_SW_MINOR_VERSION_C != PORT_REGESYS_IGF_SW_MINOR_VERSION) || \
     (PORT_IGF_SW_PATCH_VERSION_C != PORT_REGESYS_IGF_SW_PATCH_VERSION)    \
    )
  #error "Software Version Numbers of Port_Igf.c and Port_Reg_eSys_Igf.h are different"
#endif

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      LOCAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                      GLOBAL CONSTANTS
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL VARIABLES
=================================================================================================*/
#define PORT_START_SEC_CONST_32
/**
* @violates @ref Port_Igf_C_REF_2 Violates MISRA 2004 Required Rule 19.15
*/
#include "MemMap.h"

/**
* @brief EMIOS base address array
*/
/**
* @violates @ref Port_Igf_C_REF_6 Violates MISRA 2004 Required Rule 8.10
*/
CONST(uint32, PORT_CONST) IGF_BASE_ADDR32[] = 
{
#ifdef  IGF0_BASEADDR
    /** @brief check if first IGF is available on the platform */
    IGF0_BASEADDR,
#endif

#ifdef  IGF_1_BASEADDR
    /** @brief check if second IGF is available on the platform */
    IGF_1_BASEADDR,
#endif
};

#define PORT_STOP_SEC_CONST_32
/**
* @violates @ref Port_Igf_C_REF_1 Violates MISRA 2004 Advisory Rule 19.1
* @violates @ref Port_Igf_C_REF_2 Violates MISRA 2004 Required Rule 19.15
*/
#include "MemMap.h"

/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
                                       LOCAL FUNCTIONS
=================================================================================================*/


/*=================================================================================================
                                       GLOBAL FUNCTIONS
=================================================================================================*/
#define PORT_START_SEC_CODE
/**
* @violates @ref Port_Igf_C_REF_1 Violates MISRA 2004 Advisory Rule 19.1
* @violates @ref Port_Igf_C_REF_2 Violates MISRA 2004 Required Rule 19.15
*/
#include "MemMap.h"

/**
* @brief        Initializes the IGF IP Driver
* @details      The function Port_Igf_Init will initialize ALL IGF channels with the
*               configuration set pointed to by the parameter pIgfConfigPtr.
*
* @param[in]    pIgfConfigPtr  A pointer to the structure which contains initialization parameters
*
* @return none
*
* @pre    none
*
*
*/
FUNC(void, PORT_CODE) Port_Igf_Init
(
    P2CONST(Port_IgfConfigType, AUTOMATIC, PORT_APPL_CONST) pIgfConfigPtr
)
{
    VAR(uint8,  AUTOMATIC) u8ChannelIndex;
    VAR(uint8,  AUTOMATIC) u8NumConfigChannels = (uint8)(pIgfConfigPtr->u8NumChannels);
    VAR(uint32, AUTOMATIC) u32RegValue;
    VAR(uint8,  AUTOMATIC) u8IfgInstance;
    VAR(uint8,  AUTOMATIC) u8IgfChannel;
    
    
    /* Initialize all IGF channels present in the configuration */
    for (u8ChannelIndex = (uint8)0U; u8ChannelIndex < u8NumConfigChannels; u8ChannelIndex++)
    {
        /**
        * @violates @ref Port_Igf_C_REF_5 Violates MISRA 2004 Required Rule 17.4
        */
        u8IfgInstance = (uint8)pIgfConfigPtr->pChannelConfig[u8ChannelIndex].u8IgfInstance;

        /**
        * @violates @ref Port_Igf_C_REF_5 Violates MISRA 2004 Required Rule 17.4
        */
        u8IgfChannel = (uint8)pIgfConfigPtr->pChannelConfig[u8ChannelIndex].u8IgfChannel;

        /* Make sure that the IGF channel is disabled so we can update it with the configuration params */
        /**
        * @violates @ref Port_Igf_C_REF_4 Cast from unsigned long to pointer
        * @violates @ref Port_Igf_C_REF_7 A cast should not be performed between a pointer type and an integral type.
        */
        REG_BIT_CLEAR32(IGF_MCR_ADDR32(u8IfgInstance,u8IgfChannel), IGF_MCR_FGEN_ON_U32);

        /* Prepare and write the MCR register */
        /**
        * @violates @ref Port_Igf_C_REF_5 Violates MISRA 2004 Required Rule 17.4
        */
        u32RegValue = (uint32)pIgfConfigPtr->pChannelConfig[u8ChannelIndex].u32IgfMCR;
        /**
        * @violates @ref Port_Igf_C_REF_4 Cast from unsigned long to pointer
        * @violates @ref Port_Igf_C_REF_7 A cast should not be performed between a pointer type and an integral type.
        */
        REG_WRITE32(IGF_MCR_ADDR32(u8IfgInstance,u8IgfChannel), u32RegValue);
        
        /* Prepare and write the PRESR register, only if the register should be configured */
        /**
        * @violates @ref Port_Igf_C_REF_5 Violates MISRA 2004 Required Rule 17.4
        */
        u32RegValue = (uint32)pIgfConfigPtr->pChannelConfig[u8ChannelIndex].u32IgfPRESR;
        if(PORT_IGF_REG_NOT_CONFIGURED_U32 != u32RegValue)
        {
            /**
            * @violates @ref Port_Igf_C_REF_4 Cast from unsigned long to pointer
            * @violates @ref Port_Igf_C_REF_7 A cast should not be performed between a pointer type and an integral type.
            */
            REG_WRITE32(IGF_PRESR_ADDR32(u8IfgInstance,u8IgfChannel), u32RegValue);
        }

        /* Prepare and write the RTH register, only if the register should be configured */
        /**
        * @violates @ref Port_Igf_C_REF_5 Violates MISRA 2004 Required Rule 17.4
        */
        u32RegValue = (uint32)pIgfConfigPtr->pChannelConfig[u8ChannelIndex].u32IgfRTH;
        if(PORT_IGF_REG_NOT_CONFIGURED_U32 != u32RegValue)
        {
            /**
            * @violates @ref Port_Igf_C_REF_4 Cast from unsigned long to pointer
            * @violates @ref Port_Igf_C_REF_7 A cast should not be performed between a pointer type and an integral type.
            */
            REG_WRITE32(IGF_RTH_ADDR32(u8IfgInstance,u8IgfChannel), u32RegValue);
        }
        
        /* Prepare and write the FTH register, only if the register should be configured */
        /**
        * @violates @ref Port_Igf_C_REF_5 Violates MISRA 2004 Required Rule 17.4
        */
        u32RegValue = (uint32)pIgfConfigPtr->pChannelConfig[u8ChannelIndex].u32IgfFTH;
        if(PORT_IGF_REG_NOT_CONFIGURED_U32 != u32RegValue)
        {
            /**
            * @violates @ref Port_Igf_C_REF_4 Cast from unsigned long to pointer
            * @violates @ref Port_Igf_C_REF_7 A cast should not be performed between a pointer type and an integral type.
            */
            REG_WRITE32(IGF_FTH_ADDR32(u8IfgInstance,u8IgfChannel), u32RegValue);
        }

        /* Enable the IGF Channel by setting the FGEN bit */
        /**
        * @violates @ref Port_Igf_C_REF_4 Cast from unsigned long to pointer
        * @violates @ref Port_Igf_C_REF_7 A cast should not be performed between a pointer type and an integral type.
        */
        REG_BIT_SET32(IGF_MCR_ADDR32(u8IfgInstance,u8IgfChannel), IGF_MCR_FGEN_ON_U32);
    }
}


#define PORT_STOP_SEC_CODE
/**
* @violates @ref Port_Igf_C_REF_1 Violates MISRA 2004 Advisory Rule 19.1, only preprocessor
* statements and comments before '#include'
* @violates @ref Port_Igf_C_REF_2 Violates MISRA 2004 Advisory Rule 19.15, Repeated include
* file MemMap.h
*/
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
