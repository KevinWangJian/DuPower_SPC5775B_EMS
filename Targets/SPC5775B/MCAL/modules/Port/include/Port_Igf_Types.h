/**
*   @file    Port_Igf_Types.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Port - Igf low level IP driver exported structures.
*   @details Interface between the high level driver (Autosar dependent) and the low level driver(platform dependent).
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

#ifndef PORT_IGF_TYPES_H
#define PORT_IGF_TYPES_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
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


/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/*
* @brief current file vendor, Autosar and API version numbers
*       The integration of incompatible files shall be avoided.
*/
#define PORT_IGF_VENDOR_ID_TYPES_H                     43
#define PORT_IGF_AR_RELEASE_MAJOR_VERSION_TYPES_H      4
#define PORT_IGF_AR_RELEASE_MINOR_VERSION_TYPES_H      0
#define PORT_IGF_AR_RELEASE_REVISION_VERSION_TYPES_H   3
#define PORT_IGF_SW_MAJOR_VERSION_TYPES_H              1
#define PORT_IGF_SW_MINOR_VERSION_TYPES_H              0
#define PORT_IGF_SW_PATCH_VERSION_TYPES_H              1

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/


/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/

/* Define used to signal that a register should not be configured with any value */
#define PORT_IGF_REG_NOT_CONFIGURED_U32     ((uint32)0xFFFFFFFFU)

/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                               STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/

/**
* @brief   Single Igf channel configuration.
* @details This structure contains all configuration parameters of a single IGF channel
*          identified by u8IgfInstance and u8IgfChannel.
* 
* @api
*/
typedef struct
{
    VAR(uint8,  PORT_VAR) u8IgfInstance; 
    VAR(uint8,  PORT_VAR) u8IgfChannel; 
    VAR(uint32, PORT_VAR) u32IgfMCR;
    VAR(uint32, PORT_VAR) u32IgfPRESR;
    VAR(uint32, PORT_VAR) u32IgfRTH;
    VAR(uint32, PORT_VAR) u32IgfFTH;
} Port_Igf_ChannelConfigType;

/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/


#ifdef __cplusplus
}
#endif
/* PORT_IGF_TYPES_H */
#endif
/** @} */
