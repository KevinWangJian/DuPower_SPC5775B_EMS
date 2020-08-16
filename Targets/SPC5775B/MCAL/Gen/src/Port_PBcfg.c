/**
* @file    Port_PBcfg.c
* @implements Port_PBcfg.c_Artifact
*
* @version 1.0.1
* @brief   AUTOSAR Port - PORT driver configuration.
* @details This file contains the PORT driver postbuild configuration.
*
* @addtogroup  Port
* @{
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
==================================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section PORT_PBCFG_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* #include'. MemMap.h is included after each section define in order to set the current memory section 
* as defined by AUTOSAR.
*
* @section PORT_PBCFG_REF_2
* Violates MISRA 2004 Required Rule 19.15, Precautions shall be taken in order to prevent the
* contents of a header being included twice.
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section PORT_PBCFG_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers. 
* The used compilers/linkers allow more than 31 characters significance for external identifiers.
*
* @section PORT_PBCFG_REF_4
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or 
* functions at file scope shall have internal linkage unless external linkage is required.
* This warning appears when defining functions or objects that will be used by the upper layers.
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
#include "Port.h"

#if (STD_OFF == PORT_PRECOMPILE_SUPPORT)
    
/*=================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
/**
* @brief Parameters that shall be published within the Port driver header file and also in the
*        module's description file
* @details The integration of incompatible files shall be avoided.
*
*/
#define PORT_VENDOR_ID_PBCFG_C                       43
/*
* @violates @ref PORT_PBCFG_REF_3 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*/
#define PORT_AR_RELEASE_MAJOR_VERSION_PBCFG_C        4
/*
* @violates @ref PORT_PBCFG_REF_3 The compiler/linker shall be checked to ensure that 31 character
* signifiance and case sensitivity are supported for external identifiers.
*/
#define PORT_AR_RELEASE_MINOR_VERSION_PBCFG_C        0

/** @violates @ref PORT_PBCFG_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to
*   ensure that 31 character significance and case sensitivity are supported for external
*   identifiers.
*/
#define PORT_AR_RELEASE_REVISION_VERSION_PBCFG_C     3
#define PORT_SW_MAJOR_VERSION_PBCFG_C                1
#define PORT_SW_MINOR_VERSION_PBCFG_C                0
#define PORT_SW_PATCH_VERSION_PBCFG_C                1

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/* Check if Port_PBcfg.c and Port.h are of the same vendor */
#if (PORT_VENDOR_ID_PBCFG_C != PORT_VENDOR_ID)
    #error "Port_PBcfg.c and Port.h have different vendor ids"
#endif
/* Check if Port_PBcfg.c and Port.h are of the same Autosar version */
#if ((PORT_AR_RELEASE_MAJOR_VERSION_PBCFG_C    != PORT_AR_RELEASE_MAJOR_VERSION) || \
     (PORT_AR_RELEASE_MINOR_VERSION_PBCFG_C    != PORT_AR_RELEASE_MINOR_VERSION) || \
     (PORT_AR_RELEASE_REVISION_VERSION_PBCFG_C != PORT_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Port_PBcfg.c and Port.h are different"
#endif

/* Check if Port_PBcfg.c and Port.h are of the same software version */
#if ((PORT_SW_MAJOR_VERSION_PBCFG_C != PORT_SW_MAJOR_VERSION) || \
     (PORT_SW_MINOR_VERSION_PBCFG_C != PORT_SW_MINOR_VERSION) || \
     (PORT_SW_PATCH_VERSION_PBCFG_C != PORT_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Port_PBcfg.c and Port.h are different"
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
#define PORT_START_SEC_CONFIG_DATA_16
/**
* @violates @ref PORT_PBCFG_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"


#if (PORT_MAX_UNUSED_PADS_0_U16 != 0U)
/**
* @brief NoDefaultPadsArray is an array containing Unimplemented pads and User pads
*/
static CONST(uint16, PORT_CONST) Port_au16NoUnUsedPadsArrayDefault_0[PORT_MAX_UNUSED_PADS_0_U16]=
{
(uint16)91,
(uint16)92,
(uint16)108,
(uint16)113,
(uint16)136,
(uint16)141,
(uint16)142,
(uint16)143,
(uint16)208,
(uint16)209,
(uint16)210,
(uint16)211,
(uint16)212,
(uint16)213,
(uint16)214,
(uint16)219,
(uint16)220,
(uint16)221,
(uint16)224,
(uint16)225,
(uint16)226,
(uint16)227,
(uint16)228,
(uint16)229,
(uint16)230,
(uint16)234,
(uint16)256,
(uint16)257,
(uint16)258,
(uint16)259,
(uint16)260,
(uint16)261,
(uint16)262,
(uint16)263,
(uint16)264,
(uint16)265,
(uint16)266,
(uint16)267,
(uint16)268,
(uint16)269,
(uint16)270,
(uint16)271,
(uint16)272,
(uint16)273,
(uint16)274,
(uint16)275,
(uint16)276,
(uint16)277,
(uint16)278,
(uint16)279,
(uint16)280,
(uint16)281,
(uint16)282,
(uint16)283,
(uint16)284,
(uint16)285,
(uint16)286,
(uint16)287,
(uint16)288,
(uint16)289,
(uint16)290,
(uint16)291,
(uint16)292,
(uint16)293,
(uint16)294,
(uint16)295,
(uint16)296,
(uint16)297,
(uint16)298,
(uint16)299,
(uint16)300,
(uint16)301,
(uint16)302,
(uint16)303,
(uint16)304,
(uint16)305,
(uint16)306,
(uint16)307,
(uint16)433,
(uint16)475,
(uint16)477,
(uint16)482,
(uint16)483,
(uint16)484,
(uint16)485,
(uint16)486,
(uint16)487,
(uint16)488,
(uint16)489,
(uint16)490,
(uint16)491
};
#endif

#define PORT_STOP_SEC_CONFIG_DATA_16
/**
* @violates @ref PORT_PBCFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_PBCFG_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref PORT_PBCFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_PBCFG_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"


/**
 * @brief Default Configuration for Pins not initialized
 */
static CONST(Port_Siu_UnUsedPinConfigType, PORT_CONST) Port_UnUsedPin_0 =
{
    /**
    * @note: Configuration of Default pin
    */
        (uint16)0x0100, (uint8)0
    
};

/**
* @brief Pin default configuration data for configPB_0
*/
static CONST(Port_Siu_PinConfigType, PORT_CONST) Port_aPinConfigDefaultPB_0[PORT_MAX_CONFIGURED_PADS_0_U16]=
{
    {(Port_InternalPinIdType)114, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)115, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)116, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)118, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)119, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)120, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)121, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)122, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)123, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)124, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)126, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)127, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)128, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)129, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)130, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)131, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)132, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)133, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)134, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)135, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)137, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)138, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)139, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)140, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)144, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)145, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)146, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)147, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)148, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)149, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)150, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)151, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)152, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)153, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)154, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)155, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)156, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)157, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)158, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)159, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)160, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)161, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)162, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)163, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)164, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)165, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)166, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)167, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)168, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)169, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)170, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)171, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)172, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)173, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)174, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)175, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)176, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)177, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)178, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)441, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)442, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)443, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)444, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)445, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)446, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)447, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)448, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)449, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)450, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)451, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)452, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)453, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)454, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)455, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)456, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)457, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)460, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)461, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)464, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)465, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)466, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)467, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)468, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)179, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)180, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)181, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)186, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)191, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)193, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)197, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)198, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)199, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)200, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)201, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)202, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)203, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)204, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)432, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)434, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)435, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)436, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)437, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)97, (uint16)0x0100, (uint8)1, (uint8)0, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)106, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)240, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)241, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)222, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)223, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)75, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)76, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)77, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)TRUE, (boolean)TRUE},
    {(Port_InternalPinIdType)78, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)79, (uint16)0x0110, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)80, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)81, (uint16)0x0110, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)82, (uint16)0x0110, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)231, (uint16)0x0200, (uint8)1, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)232, (uint16)0x0100, (uint8)0, (uint8)0, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)233, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)440, (uint16)0x0900, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)458, (uint16)0x0b00, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)459, (uint16)0x0910, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)462, (uint16)0x0b00, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)463, (uint16)0x0910, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)89, (uint16)0x0700, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)90, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)244, (uint16)0x0700, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)245, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)469, (uint16)0x0a00, (uint8)1, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)470, (uint16)0x0a00, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)471, (uint16)0x0a00, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)472, (uint16)0x0910, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)93, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)94, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)95, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)96, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)102, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)103, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)104, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)105, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)235, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)236, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)237, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)238, (uint16)0x0200, (uint8)0, (uint8)1, (boolean)TRUE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)239, (uint16)0x0600, (uint8)1, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)182, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)183, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)184, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)185, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)187, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)188, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)189, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)190, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)192, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)194, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)476, (uint16)0x0d00, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)478, (uint16)0x0d00, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)479, (uint16)0x0d00, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)480, (uint16)0x0d00, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)481, (uint16)0x0d00, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)195, (uint16)0x0e00, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)196, (uint16)0x0d00, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)242, (uint16)0x0a00, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)243, (uint16)0x0900, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)474, (uint16)0x0580, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)248, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)249, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)250, (uint16)0x050c, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)251, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)252, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)253, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)98, (uint16)0x0e00, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)99, (uint16)0x0f00, (uint8)0, (uint8)2, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)100, (uint16)0x1100, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)101, (uint16)0x1200, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)107, (uint16)0x1100, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)109, (uint16)0x1200, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)110, (uint16)0x1100, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)83, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)84, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)85, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)86, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)87, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)88, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)246, (uint16)0x0600, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)247, (uint16)0x0500, (uint8)0, (uint8)0, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)117, (uint16)0x1300, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE},
    {(Port_InternalPinIdType)125, (uint16)0x1300, (uint8)0, (uint8)1, (boolean)FALSE, (boolean)FALSE, (boolean)FALSE}
};

/**
* @brief Pad selection default configuration for configPB_0
*/
static CONST(Port_Siu_PadSelConfigType, PORT_CONST) Port_aPadSelConfigDefaultPB_0[PORT_NMBR_INMUX_REGS_U16]=
{
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x03,
    (uint8)0x02,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x01,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x01,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x01,
    (uint8)0x01,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x01,
    (uint8)0x00,
    (uint8)0x01,
    (uint8)0x01,
    (uint8)0x01,
    (uint8)0x01,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    (uint8)0x00,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    MUXSEL_RESERVED_U8,
    (uint8)0x00
};

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                
#if (PORT_MAX_CONFIGURED_IGF_CHANNELS_0_U16 != 0U)
/**
* @brief IGF Channels configuration data for configPB_0
*/
static CONST(Port_Igf_ChannelConfigType, PORT_CONST) Port_aIgfChannelConfigPB_0[PORT_MAX_CONFIGURED_IGF_CHANNELS_0_U16]=
{
    /* Instance, channel, MCR Register,      Prescaler Register, RTH Register,       FTH Register */
    {(uint8)0, (uint8)24, (uint32)0x00000100U, (uint32)0xffffffffU, (uint32)0x00000000U, (uint32)0xffffffffU},
    {(uint8)0, (uint8)25, (uint32)0x00000100U, (uint32)0xffffffffU, (uint32)0x00000000U, (uint32)0xffffffffU},
    {(uint8)0, (uint8)26, (uint32)0x00000100U, (uint32)0xffffffffU, (uint32)0x00000000U, (uint32)0xffffffffU},
    {(uint8)0, (uint8)27, (uint32)0x00000100U, (uint32)0xffffffffU, (uint32)0x00000000U, (uint32)0xffffffffU}

};
#endif /* (PORT_MAX_CONFIGURED_IGF_CHANNELS_0_U16 != 0U) */

/**
* @brief This table contains all the Configured Port Pin parameters and the
*        number of Port Pins configured by the tool for the post-build mode PortConfigSet_0
* @violates @ref PORT_PBCFG_REF_4 Violates MISRA 2004 Required Rule 8.10
*/
CONST(Port_ConfigType, PORT_CONST) PortConfigSet_0 =
{
    PORT_MAX_CONFIGURED_PADS_0_U16,
    PORT_MAX_UNUSED_PADS_0_U16,

#if (PORT_MAX_UNUSED_PADS_0_U16 != 0U)
    Port_au16NoUnUsedPadsArrayDefault_0,
#else
    NULL_PTR,
#endif
    &Port_UnUsedPin_0,
    Port_aPinConfigDefaultPB_0,
    Port_aPadSelConfigDefaultPB_0,
    {
    PORT_MAX_CONFIGURED_IGF_CHANNELS_0_U16,
#if (PORT_MAX_CONFIGURED_IGF_CHANNELS_0_U16 != 0U)
    Port_aIgfChannelConfigPB_0
#else
    NULL_PTR
#endif
    }
};
#if (STD_ON == PORT_SET_PIN_MODE_API)

/** @brief Port Mux settings data (for pads that do not require setting of Inmux register) */
CONST(Port_PinDirectionType,  PORT_CONST) Port_aPadFunctMuxSettings[423] =
{

  /* Mux settings for pad PORT83:       {Direction} */
  /* FlexCAN_A_CNTXA functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* MCAN_0_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT84:       {Direction} */
  /* FlexCAN_A_CNRXA functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT85:       {Direction} */
  /* FlexCAN_B_CNTXB functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT86:       {Direction} */
  /* FlexCAN_B_CNRXB functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_C_PCSC4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT87:       {Direction} */
  /* FlexCAN_C_CNTXC functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_PCSD3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT88:       {Direction} */
  /* FlexCAN_C_CNRXC functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eSCI_E_RXDE functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT91:       {Direction} */
  /* DSPI_D_PCSD1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT92:       {Direction} */
  /* DSPI_D_PCSD5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT93:       {Direction} */
  /* DSPI_A_SCKA_INOUT functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* DSPI_C_PCSC1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* MCAN_0_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT94:       {Direction} */
  /* DSPI_A_SINA functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_C_PCSC2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT95:       {Direction} */
  /* DSPI_A_SOUTA functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT96:       {Direction} */
  /* DSPI_A_PCSA0_INOUT functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* DSPI_D_PCSD2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT97:       {Direction} */
  /* DSPI_A_PCSA1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_PCSE0_INOUT functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* Mux settings for pad PORT98:       {Direction} */
  /* DSPI_A_PCSA2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_SOUTE functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FEC_FEC_TXD2_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FEC_FEC_RXER_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT99:       {Direction} */
  /* DSPI_A_PCSA3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_SINE functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* FEC_FEC_MDIO functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* eSCI_D_TXDD functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT100:      {Direction} */
  /* DSPI_A_PCSA4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_SCKE_INOUT functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* FEC_FEC_RXCLK_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT101:      {Direction} */
  /* DSPI_A_PCSA5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_A_eQADC_B_ETRIG1 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eSCI_D_RXDD functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* FEC_FEC_TXD3_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT102:      {Direction} */
  /* DSPI_B_SCKB_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT103:      {Direction} */
  /* DSPI_B_SINB functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT104:      {Direction} */
  /* DSPI_B_SOUTB functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT105:      {Direction} */
  /* DSPI_B_PCSB0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_PCSD2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT106:      {Direction} */
  /* DSPI_B_PCSB1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_PCSD0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT107:      {Direction} */
  /* DSPI_B_PCSB2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_SOUTC functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FEC_FEC_RXD3_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT108:      {Direction} */
  /* DSPI_B_PCSB3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT109:      {Direction} */
  /* DSPI_B_PCSB4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_SCKC_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FEC_FEC_MDC_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT110:      {Direction} */
  /* DSPI_B_PCSB5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FEC_FEC_RXD2_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT113:      {Direction} */
  /* eTPU_A_TCRCLKA functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* SIU_A_IRQ7 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT114:      {Direction} */
  /* eTPU_A_ETPUA0_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA12 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT115:      {Direction} */
  /* eTPU_A_ETPUA1_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA13 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT116:      {Direction} */
  /* eTPU_A_ETPUA2_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA14 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH0_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT117:      {Direction} */
  /* eTPU_A_ETPUA3_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA15 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH1_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FCCU_ERROR0 functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* Mux settings for pad PORT118:      {Direction} */
  /* eTPU_A_ETPUA4_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA16 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH2_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT119:      {Direction} */
  /* eTPU_A_ETPUA5_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA17 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH3_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT120:      {Direction} */
  /* eTPU_A_ETPUA6_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA18 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH4_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT121:      {Direction} */
  /* eTPU_A_ETPUA7_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA19 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH5_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT122:      {Direction} */
  /* eTPU_A_ETPUA8_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA20 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH6_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT123:      {Direction} */
  /* eTPU_A_ETPUA9_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA21 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH7_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT124:      {Direction} */
  /* eTPU_A_ETPUA10_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA22 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH8_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FCCU_ERRORIN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT125:      {Direction} */
  /* eTPU_A_ETPUA11_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA23 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH9_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FCCU_ERROR1 functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* Mux settings for pad PORT126:      {Direction} */
  /* eTPU_A_ETPUA12_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_B_PCSB1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT127:      {Direction} */
  /* eTPU_A_ETPUA13_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_B_PCSB3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT128:      {Direction} */
  /* eTPU_A_ETPUA14_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_B_PCSB4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT129:      {Direction} */
  /* eTPU_A_ETPUA15_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_B_PCSB5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* MCAN_0_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT130:      {Direction} */
  /* eTPU_A_ETPUA16_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT131:      {Direction} */
  /* eTPU_A_ETPUA17_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT132:      {Direction} */
  /* eTPU_A_ETPUA18_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT133:      {Direction} */
  /* eTPU_A_ETPUA19_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT134:      {Direction} */
  /* eTPU_A_ETPUA20_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* SIU_A_IRQ8 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT135:      {Direction} */
  /* eTPU_A_ETPUA21_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* SIU_A_IRQ9 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT136:      {Direction} */
  /* eTPU_A_ETPUA22_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* SIU_A_IRQ10 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH0_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT137:      {Direction} */
  /* eTPU_A_ETPUA23_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* SIU_A_IRQ11 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH1_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT138:      {Direction} */
  /* eTPU_A_ETPUA24_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIU_A_IRQ12 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH2_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT139:      {Direction} */
  /* eTPU_A_ETPUA25_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIU_A_IRQ13 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH3_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT140:      {Direction} */
  /* eTPU_A_ETPUA26_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIU_A_IRQ14 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH4_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT141:      {Direction} */
  /* eTPU_A_ETPUA27_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIU_A_IRQ15 functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH5_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT142:      {Direction} */
  /* eTPU_A_ETPUA28_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH6_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT143:      {Direction} */
  /* eTPU_A_ETPUA29_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH7_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT144:      {Direction} */
  /* eTPU_A_ETPUA30_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH8_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT145:      {Direction} */
  /* eTPU_A_ETPUA31_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH9_A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT146:      {Direction} */
  /* eTPU_B_TCRCLKB functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT147:      {Direction} */
  /* eTPU_B_ETPUB0_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB16 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT148:      {Direction} */
  /* eTPU_B_ETPUB1_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB17 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT149:      {Direction} */
  /* eTPU_B_ETPUB2_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB18 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT150:      {Direction} */
  /* eTPU_B_ETPUB3_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB19 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT151:      {Direction} */
  /* eTPU_B_ETPUB4_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB20 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT152:      {Direction} */
  /* eTPU_B_ETPUB5_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB21 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT153:      {Direction} */
  /* eTPU_B_ETPUB6_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB22 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT154:      {Direction} */
  /* eTPU_B_ETPUB7_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB23 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT155:      {Direction} */
  /* eTPU_B_ETPUB8_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB24 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT156:      {Direction} */
  /* eTPU_B_ETPUB9_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB25 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT157:      {Direction} */
  /* eTPU_B_ETPUB10_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB26 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT158:      {Direction} */
  /* eTPU_B_ETPUB11_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB27 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT159:      {Direction} */
  /* eTPU_B_ETPUB12_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB28 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT160:      {Direction} */
  /* eTPU_B_ETPUB13_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB29 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT161:      {Direction} */
  /* eTPU_B_ETPUB14_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB30 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT162:      {Direction} */
  /* eTPU_B_ETPUB15_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_B_ETPUB31 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT163:      {Direction} */
  /* eTPU_B_ETPUB16_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_A_PCSA1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT164:      {Direction} */
  /* eTPU_B_ETPUB17_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_A_PCSA2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT165:      {Direction} */
  /* eTPU_B_ETPUB18_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_A_PCSA3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT166:      {Direction} */
  /* eTPU_B_ETPUB19_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_A_PCSA4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT167:      {Direction} */
  /* eTPU_B_ETPUB20_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT168:      {Direction} */
  /* eTPU_B_ETPUB21_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT169:      {Direction} */
  /* eTPU_B_ETPUB22_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH0_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT170:      {Direction} */
  /* eTPU_B_ETPUB23_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH1_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT171:      {Direction} */
  /* eTPU_B_ETPUB24_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH2_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT172:      {Direction} */
  /* eTPU_B_ETPUB25_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH3_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT173:      {Direction} */
  /* eTPU_B_ETPUB26_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH4_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT174:      {Direction} */
  /* eTPU_B_ETPUB27_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH5_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT175:      {Direction} */
  /* eTPU_B_ETPUB28_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH6_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT176:      {Direction} */
  /* eTPU_B_ETPUB29_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH7_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT177:      {Direction} */
  /* eTPU_B_ETPUB30_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH8_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT178:      {Direction} */
  /* eTPU_B_ETPUB31_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH9_B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT179:      {Direction} */
  /* eMIOS_A_EMIOS0_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA0 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH0_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT180:      {Direction} */
  /* eMIOS_A_EMIOS1_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH1_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_PCSE2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT181:      {Direction} */
  /* eMIOS_A_EMIOS2_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH2_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_PCSE3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT182:      {Direction} */
  /* eMIOS_A_EMIOS3_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH3_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_PCSE4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT183:      {Direction} */
  /* eMIOS_A_EMIOS4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_A_ETPUA4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH4_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_PCSE5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT184:      {Direction} */
  /* eMIOS_A_EMIOS5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_A_ETPUA5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH5_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT185:      {Direction} */
  /* eMIOS_A_EMIOS6_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA6 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH6_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT186:      {Direction} */
  /* eMIOS_A_EMIOS7_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA7 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH7_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT187:      {Direction} */
  /* eMIOS_B_EMIOS0_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA8 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH8_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT188:      {Direction} */
  /* eMIOS_B_EMIOS1_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_A_ETPUA9 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH9_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT189:      {Direction} */
  /* eMIOS_B_EMIOS2_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_SCKD_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT190:      {Direction} */
  /* eMIOS_B_EMIOS3_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT191:      {Direction} */
  /* eMIOS_B_EMIOS4_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_C_SOUTC functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT192:      {Direction} */
  /* eMIOS_B_EMIOS5_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_SOUTD functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT193:      {Direction} */
  /* eMIOS_B_EMIOS6 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* FlexCAN_D_CNTXD functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH0_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT194:      {Direction} */
  /* eMIOS_B_EMIOS7 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH1_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT195:      {Direction} */
  /* eMIOS_A_EMIOS16_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB0 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* MCAN_1_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH2_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT196:      {Direction} */
  /* eMIOS_A_EMIOS17_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH3_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT197:      {Direction} */
  /* eMIOS_A_EMIOS18_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH4_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT198:      {Direction} */
  /* eMIOS_A_EMIOS19_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH5_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT199:      {Direction} */
  /* eMIOS_A_EMIOS20_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH6_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT200:      {Direction} */
  /* eMIOS_A_EMIOS21_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH7_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT201:      {Direction} */
  /* eMIOS_A_EMIOS22_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB6 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH8_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT202:      {Direction} */
  /* eMIOS_A_EMIOS23_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eTPU_B_ETPUB7 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH9_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT203:      {Direction} */
  /* eMIOS_B_EMIOS16_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_B_PCSB0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT204:      {Direction} */
  /* eMIOS_B_EMIOS17_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_B_PCSB1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT208:      {Direction} */
  /* SoC_PLLCFG0_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_C_ETPUC9_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIPI_TXN functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT209:      {Direction} */
  /* SoC_PLLCFG1_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_SOUTD functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIPI_TXP functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT210:      {Direction} */
  /* SoC_PLLCFG2_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_C_ETPUC3_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_PCSE1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIPI_REFCLK_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT212:      {Direction} */
  /* SoC_BOOTCFG1_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_C_ETPUC0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIPI_RXP functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT213:      {Direction} */
  /* SoC_WKPCFG_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* SIU_A_NMI_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eTPU_C_ETPUC1_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* SIPI_RXN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT214:      {Direction} */
  /* ENGCLK functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT219:      {Direction} */
  /* MCKO functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT224:      {Direction} */
  /* MSEO0 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT225:      {Direction} */
  /* MSEO1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT226:      {Direction} */
  /* RDY functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT227:      {Direction} */
  /* EVTO functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT228:      {Direction} */
  /* TDO functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT229:      {Direction} */
  /* D_CLKOUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT230:      {Direction} */
  /* RSTOUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT235:      {Direction} */
  /* DSPI_C_SCKC_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_SCK_C_LVDS_P functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT236:      {Direction} */
  /* DSPI_C_SCK_C_LVDS_N_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT237:      {Direction} */
  /* DSPI_C_SOUTC functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_SOUT_C_LVDS_P functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT238:      {Direction} */
  /* DSPI_C_PCSC0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_SOUT_C_LVDS_N_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT239:      {Direction} */
  /* DSPI_C_PCSC1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eSCI_D_TXDD functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* Mux settings for pad PORT240:      {Direction} */
  /* DSPI_C_PCSC2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_SCK_D_LVDS_P functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_SCKD_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT241:      {Direction} */
  /* DSPI_C_PCSC3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_SCK_D_LVDS_N_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT242:      {Direction} */
  /* DSPI_C_PCSC4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* MCAN_0_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_SOUT_D_LVDS_P functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_SOUTD functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT243:      {Direction} */
  /* DSPI_C_PCSC5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_SOUT_D_LVDS_N_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_D_PCSD0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT244:      {Direction} */
  /* eSCI_C_TXDC functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* eQADC_A_eQADC_B_ETRIG0_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT245:      {Direction} */
  /* eSCI_C_RXDC_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT246:      {Direction} */
  /* FlexCAN_D_CNTXD functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* MCAN_1_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT248:      {Direction} */
  /* FEC_FEC_TXD0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT249:      {Direction} */
  /* FEC_FEC_RX_DV_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT250:      {Direction} */
  /* FEC_FEC_RXD0_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT251:      {Direction} */
  /* FEC_FEC_TXD1_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT252:      {Direction} */
  /* FEC_FEC_TXEN_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT253:      {Direction} */
  /* FEC_FEC_RXD1_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT432:      {Direction} */
  /* eMIOS_B_EMIOS18_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_B_PCSB2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT433:      {Direction} */
  /* eMIOS_B_EMIOS19_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_B_PCSB3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT434:      {Direction} */
  /* eMIOS_B_EMIOS20_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT435:      {Direction} */
  /* eMIOS_B_EMIOS21_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT436:      {Direction} */
  /* eMIOS_B_EMIOS22_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT437:      {Direction} */
  /* eMIOS_B_EMIOS23_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_C_PCSC5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT443:      {Direction} */
  /* eTPU_C_ETPUC2_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT445:      {Direction} */
  /* eTPU_C_ETPUC4_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT446:      {Direction} */
  /* eTPU_C_ETPUC5_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_E_PCSE2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT447:      {Direction} */
  /* eTPU_C_ETPUC6_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_E_PCSE3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT448:      {Direction} */
  /* eTPU_C_ETPUC7_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_E_PCSE4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT449:      {Direction} */
  /* eTPU_C_ETPUC8_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* DSPI_E_PCSE5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT451:      {Direction} */
  /* eTPU_C_ETPUC10_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT452:      {Direction} */
  /* eTPU_C_ETPUC11_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT453:      {Direction} */
  /* eTPU_C_ETPUC12_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* MCAN_1_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT454:      {Direction} */
  /* eTPU_C_ETPUC13_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* PSI5A_SDOUT0_PSI5A_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH0_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT455:      {Direction} */
  /* eTPU_C_ETPUC14_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* PSI5A_SDIN0_PSI5A_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH1_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT456:      {Direction} */
  /* eTPU_C_ETPUC15_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH2_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT457:      {Direction} */
  /* eTPU_C_ETPUC16_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* MCAN_1_TX_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH3_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT458:      {Direction} */
  /* eTPU_C_ETPUC17_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eSCI_F_TXDF functionality */
  (Port_PinDirectionType)PORT_PIN_INOUT, 
  /* REACM_RCH4_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT459:      {Direction} */
  /* eTPU_C_ETPUC18_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* eSCI_F_RXDF_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT460:      {Direction} */
  /* eTPU_C_ETPUC19_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* PSI5A_SDOUT0_PSI5B_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT461:      {Direction} */
  /* eTPU_C_ETPUC20_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* PSI5A_SDIN0_PSI5B_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT462:      {Direction} */
  /* eTPU_C_ETPUC21_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT463:      {Direction} */
  /* eTPU_C_ETPUC22_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* Mux settings for pad PORT464:      {Direction} */
  /* eTPU_C_ETPUC23_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD5 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_A_MAA0 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_B_MAB0 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT465:      {Direction} */
  /* eTPU_C_ETPUC24_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD4 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_A_MAA1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_B_MAB1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT466:      {Direction} */
  /* eTPU_C_ETPUC25_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD3 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_A_MAA2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_B_MAB2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT467:      {Direction} */
  /* eTPU_C_ETPUC26_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_B_MAB0 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT468:      {Direction} */
  /* eTPU_C_ETPUC27_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH5_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_B_MAB1 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT469:      {Direction} */
  /* eTPU_C_ETPUC28_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_PCSD0_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH6_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* eQADC_B_MAB2 functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT470:      {Direction} */
  /* eTPU_C_ETPUC29_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_SCKD_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH7_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT471:      {Direction} */
  /* eTPU_C_ETPUC30_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* DSPI_D_SOUTD functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* REACM_RCH8_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT472:      {Direction} */
  /* eTPU_C_ETPUC31_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN, 
  /* REACM_RCH9_C_OUT functionality */
  (Port_PinDirectionType)PORT_PIN_OUT, 
  /* Mux settings for pad PORT474:      {Direction} */
  /* FEC_FEC_TXCLK_REFCLK_IN functionality */
  (Port_PinDirectionType)PORT_PIN_IN

};

/** @brief Port Inmux settings data (for pads that do require setting of Inmux register) */
CONST(Port_InMuxSettingType,  PORT_CONST) Port_aPadFunctInMuxSettings[149] = 
{

  /* Inmux settings for pad PORT83:     {Inmux reg, Inmux value, Direction} */
  /* eSCI_A_TXDA input func */
  {(uint16)64, (uint8)1, (Port_PinDirectionType)PORT_PIN_INOUT}, 
  /* Inmux settings for pad PORT84:     {Inmux reg, Inmux value, Direction} */
  /* eSCI_A_RXDA input func */
  {(uint16)65, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* MCAN_0_RX_IN input func */
  {(uint16)16, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT89:     {Inmux reg, Inmux value, Direction} */
  /* eSCI_A_TXDA input func */
  {(uint16)64, (uint8)0, (Port_PinDirectionType)PORT_PIN_INOUT}, 
  /* Inmux settings for pad PORT90:     {Inmux reg, Inmux value, Direction} */
  /* eSCI_A_RXDA_IN input func */
  {(uint16)65, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT91:     {Inmux reg, Inmux value, Direction} */
  /* eSCI_B_TXDB input func */
  {(uint16)67, (uint8)0, (Port_PinDirectionType)PORT_PIN_INOUT}, 
  /* MCAN_0_RX_IN input func */
  {(uint16)16, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT92:     {Inmux reg, Inmux value, Direction} */
  /* eSCI_B_RXDB input func */
  {(uint16)66, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT93:     {Inmux reg, Inmux value, Direction} */
  /* SENT_B_SENT1_B_IN input func */
  {(uint16)7, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT100:    {Inmux reg, Inmux value, Direction} */
  /* eSCI_E_TXDE input func */
  {(uint16)72, (uint8)0, (Port_PinDirectionType)PORT_PIN_INOUT}, 
  /* Inmux settings for pad PORT105:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_B_PCSB0_IN input func */
  {(uint16)37, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT106:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_PCSD0_IN input func */
  {(uint16)43, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT107:    {Inmux reg, Inmux value, Direction} */
  /* SENT_B_SENT2_B_IN input func */
  {(uint16)8, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT108:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_C_SINC input func */
  {(uint16)39, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_B_SENT3_B_IN input func */
  {(uint16)9, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT109:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_C_SCKC_IN input func */
  {(uint16)38, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_B_SENT4_B_IN input func */
  {(uint16)10, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT110:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_C_PCSC0_IN input func */
  {(uint16)40, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_B_SENT5_B_IN input func */
  {(uint16)11, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT133:    {Inmux reg, Inmux value, Direction} */
  /* MCAN_0_RX_IN input func */
  {(uint16)16, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT138:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA24_IN input func */
  {(uint16)120, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT139:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA25_IN input func */
  {(uint16)121, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT140:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA26_IN input func */
  {(uint16)122, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT141:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA27_IN input func */
  {(uint16)123, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT142:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA28_IN input func */
  {(uint16)124, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT143:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA29_IN input func */
  {(uint16)125, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT144:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA30_IN input func */
  {(uint16)126, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT145:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA31_IN input func */
  {(uint16)127, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT146:    {Inmux reg, Inmux value, Direction} */
  /* SIU_A_IRQ6 input func */
  {(uint16)54, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT189:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_SCKD_IN input func */
  {(uint16)41, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT190:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_SIND input func */
  {(uint16)42, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT193:    {Inmux reg, Inmux value, Direction} */
  /* SIU_A_IRQ0 input func */
  {(uint16)48, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT194:    {Inmux reg, Inmux value, Direction} */
  /* SIU_A_IRQ1_IN input func */
  {(uint16)49, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* FlexCAN_D_CNRXD_IN input func */
  {(uint16)21, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT195:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS16_IN input func */
  {(uint16)80, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT196:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS17_IN input func */
  {(uint16)81, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* MCAN_1_RX_IN input func */
  {(uint16)17, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT197:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS18_IN input func */
  {(uint16)82, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT198:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS19_IN input func */
  {(uint16)83, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT199:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS20_IN input func */
  {(uint16)84, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT200:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS21_IN input func */
  {(uint16)85, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT201:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS22_IN input func */
  {(uint16)86, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT202:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_A_EMIOS23_IN input func */
  {(uint16)87, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT203:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS16_IN input func */
  {(uint16)88, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* DSPI_B_PCSB0_IN input func */
  {(uint16)37, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT204:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS17_IN input func */
  {(uint16)89, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT208:    {Inmux reg, Inmux value, Direction} */
  /* SIU_A_IRQ4_IN input func */
  {(uint16)52, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eTPU_C_ETPUC9_IN input func */
  {(uint16)169, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT209:    {Inmux reg, Inmux value, Direction} */
  /* SIU_A_IRQ5_IN input func */
  {(uint16)53, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT210:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC3_IN input func */
  {(uint16)163, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT212:    {Inmux reg, Inmux value, Direction} */
  /* SIU_A_IRQ3_IN input func */
  {(uint16)51, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eTPU_C_ETPUC0_IN input func */
  {(uint16)160, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT213:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC1_IN input func */
  {(uint16)161, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT223:    {Inmux reg, Inmux value, Direction} */
  /* eSCI_E_TXDE input func */
  {(uint16)72, (uint8)1, (Port_PinDirectionType)PORT_PIN_INOUT}, 
  /* Inmux settings for pad PORT235:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_C_SCKC_IN input func */
  {(uint16)38, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT236:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_C_SINC_IN input func */
  {(uint16)39, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT238:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_C_PCSC0_IN input func */
  {(uint16)40, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT240:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_SCKD_IN input func */
  {(uint16)41, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT241:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_SIND_IN input func */
  {(uint16)42, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT243:    {Inmux reg, Inmux value, Direction} */
  /* MCAN_0_RX_IN input func */
  {(uint16)16, (uint8)3, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* DSPI_D_PCSD0_IN input func */
  {(uint16)43, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT247:    {Inmux reg, Inmux value, Direction} */
  /* FlexCAN_D_CNRXD_IN input func */
  {(uint16)21, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* MCAN_1_RX_IN input func */
  {(uint16)17, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT248:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT0_A_IN input func */
  {(uint16)0, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT249:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT1_A_IN input func */
  {(uint16)1, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT250:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT2_A_IN input func */
  {(uint16)2, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT251:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT3_A_IN input func */
  {(uint16)3, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT252:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT4_A_IN input func */
  {(uint16)4, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT253:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT5_A_IN input func */
  {(uint16)5, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT432:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS18_IN input func */
  {(uint16)90, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT433:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS19_IN input func */
  {(uint16)91, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT434:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS20_IN input func */
  {(uint16)92, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* DSPI_C_PCSC0_IN input func */
  {(uint16)40, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT435:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS21_IN input func */
  {(uint16)93, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT436:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS22_IN input func */
  {(uint16)94, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT437:    {Inmux reg, Inmux value, Direction} */
  /* eMIOS_B_EMIOS23_IN input func */
  {(uint16)95, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT440:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_TCRCLKC_IN input func */
  {(uint16)194, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SIU_A_IRQ6_IN input func */
  {(uint16)54, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT441:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC0_IN input func */
  {(uint16)160, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_A_SENT0_A_IN input func */
  {(uint16)0, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT442:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC1_IN input func */
  {(uint16)161, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_A_SENT1_A_IN input func */
  {(uint16)1, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT443:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT3_A_IN input func */
  {(uint16)3, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT444:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC3_IN input func */
  {(uint16)163, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_A_SENT4_A_IN input func */
  {(uint16)4, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT445:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT5_A_IN input func */
  {(uint16)5, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eTPU_C_TCRCLKC_IN input func */
  {(uint16)194, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT446:    {Inmux reg, Inmux value, Direction} */
  /* SENT_B_SENT0_B_IN input func */
  {(uint16)6, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT447:    {Inmux reg, Inmux value, Direction} */
  /* SENT_B_SENT1_B_IN input func */
  {(uint16)7, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT448:    {Inmux reg, Inmux value, Direction} */
  /* SENT_B_SENT2_B_IN input func */
  {(uint16)8, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT449:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC8_IN input func */
  {(uint16)168, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_B_SENT3_B_IN input func */
  {(uint16)9, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT450:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC9_IN input func */
  {(uint16)169, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SIU_A_IRQ0_IN input func */
  {(uint16)48, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_B_SENT4_B_IN input func */
  {(uint16)10, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT451:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC10_IN input func */
  {(uint16)170, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SIU_A_IRQ1_IN input func */
  {(uint16)49, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SENT_B_SENT5_B_IN input func */
  {(uint16)11, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT452:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC11_IN input func */
  {(uint16)171, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SIU_A_IRQ2_IN input func */
  {(uint16)50, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT453:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC12_IN input func */
  {(uint16)172, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SIU_A_IRQ3_IN input func */
  {(uint16)51, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT454:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC13_IN input func */
  {(uint16)173, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SIU_A_IRQ4_IN input func */
  {(uint16)52, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT455:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC14_IN input func */
  {(uint16)174, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* SIU_A_IRQ5_IN input func */
  {(uint16)53, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT456:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC15_IN input func */
  {(uint16)175, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* MCAN_1_RX_IN input func */
  {(uint16)17, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT460:    {Inmux reg, Inmux value, Direction} */
  /* eSCI_A_TXDA input func */
  {(uint16)64, (uint8)2, (Port_PinDirectionType)PORT_PIN_INOUT}, 
  /* Inmux settings for pad PORT461:    {Inmux reg, Inmux value, Direction} */
  /* eSCI_A_RXDA_IN input func */
  {(uint16)65, (uint8)2, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT462:    {Inmux reg, Inmux value, Direction} */
  /* eSCI_B_TXDB input func */
  {(uint16)67, (uint8)1, (Port_PinDirectionType)PORT_PIN_INOUT}, 
  /* Inmux settings for pad PORT463:    {Inmux reg, Inmux value, Direction} */
  /* eSCI_B_RXDB_IN input func */
  {(uint16)66, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT469:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_PCSD0_IN input func */
  {(uint16)43, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT470:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_SCKD_IN input func */
  {(uint16)41, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT472:    {Inmux reg, Inmux value, Direction} */
  /* DSPI_D_SIND_IN input func */
  {(uint16)42, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT474:    {Inmux reg, Inmux value, Direction} */
  /* SENT_B_SENT0_B_IN input func */
  {(uint16)6, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT475:    {Inmux reg, Inmux value, Direction} */
  /* SENT_A_SENT2_A_IN input func */
  {(uint16)2, (uint8)0, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT476:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA31_IN input func */
  {(uint16)127, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS16_IN input func */
  {(uint16)80, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT477:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA30_IN input func */
  {(uint16)126, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS17_IN input func */
  {(uint16)81, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT478:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA29_IN input func */
  {(uint16)125, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS18_IN input func */
  {(uint16)82, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT479:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA28_IN input func */
  {(uint16)124, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS19_IN input func */
  {(uint16)83, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT480:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA27_IN input func */
  {(uint16)123, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS20_IN input func */
  {(uint16)84, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT481:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA26_IN input func */
  {(uint16)122, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS21_IN input func */
  {(uint16)85, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT482:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA25_IN input func */
  {(uint16)121, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS22_IN input func */
  {(uint16)86, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT483:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_A_ETPUA24_IN input func */
  {(uint16)120, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_A_EMIOS23_IN input func */
  {(uint16)87, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT484:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC15_IN input func */
  {(uint16)175, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS16_IN input func */
  {(uint16)88, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT485:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC14_IN input func */
  {(uint16)174, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS17_IN input func */
  {(uint16)89, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT486:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC13_IN input func */
  {(uint16)173, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS18_IN input func */
  {(uint16)90, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT487:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC12_IN input func */
  {(uint16)172, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS19_IN input func */
  {(uint16)91, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT488:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC11_IN input func */
  {(uint16)171, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS20_IN input func */
  {(uint16)92, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT489:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC10_IN input func */
  {(uint16)170, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS21_IN input func */
  {(uint16)93, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT490:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC9_IN input func */
  {(uint16)169, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS22_IN input func */
  {(uint16)94, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* Inmux settings for pad PORT491:    {Inmux reg, Inmux value, Direction} */
  /* eTPU_C_ETPUC8_IN input func */
  {(uint16)168, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}, 
  /* eMIOS_B_EMIOS23_IN input func */
  {(uint16)95, (uint8)1, (Port_PinDirectionType)PORT_PIN_IN}

};

/** @brief Pad index data to either Mux settings table or Inmux settings table */
CONST(Port_SettingsIndexType, PORT_CONST) Port_aPadFunctIndex[PORT_INDEX_TABLE_NUM_ENTRIES_U16] =
{

  /* Settings information for pad 0 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 1 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 2 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 3 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 4 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 5 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 6 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 7 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 8 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 9 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 10 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 11 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 12 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 13 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 14 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 15 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 16 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 17 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 18 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 19 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 20 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 21 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 22 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 23 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 24 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 25 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 26 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 27 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 28 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 29 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 30 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 31 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 32 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 33 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 34 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 35 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 36 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 37 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 38 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 39 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 40 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 41 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 42 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 43 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 44 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 45 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 46 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 47 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 48 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 49 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 50 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 51 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 52 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 53 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 54 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 55 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 56 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 57 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 58 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 59 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 60 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 61 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 62 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 63 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 64 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 65 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 66 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 67 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 68 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 69 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 70 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 71 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 72 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 73 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 74 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 75 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 76 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 77 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 78 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 79 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 80 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 81 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 82 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 83 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_A_CNTXA functionality */
  {(uint16)83, (uint8)1, (uint16)0}
  /* MCAN_0_TX_OUT functionality */,
  {(uint16)83, (uint8)3, (uint16)1}
  /* eSCI_A_TXDA functionality */,
  {(uint16)83, (uint8)6, (uint16)0}
  /* Settings information for pad 84 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_A_CNRXA functionality */,
  {(uint16)84, (uint8)1, (uint16)2}
  /* eSCI_A_RXDA functionality */,
  {(uint16)84, (uint8)6, (uint16)1}
  /* MCAN_0_RX_IN functionality */,
  {(uint16)84, (uint8)7, (uint16)2}
  /* Settings information for pad 85 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_B_CNTXB functionality */,
  {(uint16)85, (uint8)1, (uint16)3}
  /* DSPI_C_PCSC3 functionality */,
  {(uint16)85, (uint8)2, (uint16)4}
  /* Settings information for pad 86 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_B_CNRXB functionality */,
  {(uint16)86, (uint8)1, (uint16)5}
  /* DSPI_C_PCSC4 functionality */,
  {(uint16)86, (uint8)2, (uint16)6}
  /* Settings information for pad 87 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_C_CNTXC functionality */,
  {(uint16)87, (uint8)1, (uint16)7}
  /* DSPI_D_PCSD3 functionality */,
  {(uint16)87, (uint8)2, (uint16)8}
  /* Settings information for pad 88 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_C_CNRXC functionality */,
  {(uint16)88, (uint8)1, (uint16)9}
  /* DSPI_D_PCSD4 functionality */,
  {(uint16)88, (uint8)2, (uint16)10}
  /* eSCI_E_RXDE functionality */,
  {(uint16)88, (uint8)3, (uint16)11}
  /* Settings information for pad 89 {PCR, Mode, Index to Mux or Inmux table} */
  /* eSCI_A_TXDA functionality */,
  {(uint16)89, (uint8)5, (uint16)3}
  /* Settings information for pad 90 {PCR, Mode, Index to Mux or Inmux table} */
  /* eSCI_A_RXDA_IN functionality */,
  {(uint16)90, (uint8)5, (uint16)4}
  /* Settings information for pad 91 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_D_PCSD1 functionality */,
  {(uint16)91, (uint8)2, (uint16)12}
  /* eSCI_B_TXDB functionality */,
  {(uint16)91, (uint8)5, (uint16)5}
  /* MCAN_0_RX_IN functionality */,
  {(uint16)91, (uint8)7, (uint16)6}
  /* Settings information for pad 92 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_D_PCSD5 functionality */,
  {(uint16)92, (uint8)2, (uint16)13}
  /* eSCI_B_RXDB functionality */,
  {(uint16)92, (uint8)5, (uint16)7}
  /* Settings information for pad 93 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_SCKA_INOUT functionality */,
  {(uint16)93, (uint8)1, (uint16)14}
  /* DSPI_C_PCSC1 functionality */,
  {(uint16)93, (uint8)2, (uint16)15}
  /* MCAN_0_TX_OUT functionality */,
  {(uint16)93, (uint8)3, (uint16)16}
  /* SENT_B_SENT1_B_IN functionality */,
  {(uint16)93, (uint8)8, (uint16)8}
  /* Settings information for pad 94 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_SINA functionality */,
  {(uint16)94, (uint8)1, (uint16)17}
  /* DSPI_C_PCSC2 functionality */,
  {(uint16)94, (uint8)2, (uint16)18}
  /* Settings information for pad 95 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_SOUTA functionality */,
  {(uint16)95, (uint8)1, (uint16)19}
  /* DSPI_C_PCSC5 functionality */,
  {(uint16)95, (uint8)2, (uint16)20}
  /* Settings information for pad 96 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_PCSA0_INOUT functionality */,
  {(uint16)96, (uint8)1, (uint16)21}
  /* DSPI_D_PCSD2 functionality */,
  {(uint16)96, (uint8)2, (uint16)22}
  /* Settings information for pad 97 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_PCSA1 functionality */,
  {(uint16)97, (uint8)1, (uint16)23}
  /* DSPI_E_PCSE0_INOUT functionality */,
  {(uint16)97, (uint8)2, (uint16)24}
  /* Settings information for pad 98 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_PCSA2 functionality */,
  {(uint16)98, (uint8)1, (uint16)25}
  /* DSPI_E_SOUTE functionality */,
  {(uint16)98, (uint8)2, (uint16)26}
  /* FEC_FEC_TXD2_OUT functionality */,
  {(uint16)98, (uint8)3, (uint16)27}
  /* FEC_FEC_RXER_IN functionality */,
  {(uint16)98, (uint8)4, (uint16)28}
  /* Settings information for pad 99 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_PCSA3 functionality */,
  {(uint16)99, (uint8)1, (uint16)29}
  /* DSPI_E_SINE functionality */,
  {(uint16)99, (uint8)2, (uint16)30}
  /* FEC_FEC_MDIO functionality */,
  {(uint16)99, (uint8)3, (uint16)31}
  /* eSCI_D_TXDD functionality */,
  {(uint16)99, (uint8)4, (uint16)32}
  /* Settings information for pad 100 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_PCSA4 functionality */,
  {(uint16)100, (uint8)1, (uint16)33}
  /* DSPI_E_SCKE_INOUT functionality */,
  {(uint16)100, (uint8)2, (uint16)34}
  /* FEC_FEC_RXCLK_IN functionality */,
  {(uint16)100, (uint8)4, (uint16)35}
  /* eSCI_E_TXDE functionality */,
  {(uint16)100, (uint8)7, (uint16)9}
  /* Settings information for pad 101 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_A_PCSA5 functionality */,
  {(uint16)101, (uint8)1, (uint16)36}
  /* eQADC_A_eQADC_B_ETRIG1 functionality */,
  {(uint16)101, (uint8)2, (uint16)37}
  /* eSCI_D_RXDD functionality */,
  {(uint16)101, (uint8)3, (uint16)38}
  /* FEC_FEC_TXD3_OUT functionality */,
  {(uint16)101, (uint8)4, (uint16)39}
  /* Settings information for pad 102 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_SCKB_IN functionality */,
  {(uint16)102, (uint8)1, (uint16)40}
  /* Settings information for pad 103 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_SINB functionality */,
  {(uint16)103, (uint8)1, (uint16)41}
  /* Settings information for pad 104 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_SOUTB functionality */,
  {(uint16)104, (uint8)1, (uint16)42}
  /* Settings information for pad 105 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_PCSB0_OUT functionality */,
  {(uint16)105, (uint8)1, (uint16)43}
  /* DSPI_D_PCSD2 functionality */,
  {(uint16)105, (uint8)2, (uint16)44}
  /* DSPI_B_PCSB0_IN functionality */,
  {(uint16)105, (uint8)5, (uint16)10}
  /* Settings information for pad 106 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_PCSB1 functionality */,
  {(uint16)106, (uint8)1, (uint16)45}
  /* DSPI_D_PCSD0_OUT functionality */,
  {(uint16)106, (uint8)2, (uint16)46}
  /* DSPI_D_PCSD0_IN functionality */,
  {(uint16)106, (uint8)6, (uint16)11}
  /* Settings information for pad 107 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_PCSB2 functionality */,
  {(uint16)107, (uint8)1, (uint16)47}
  /* DSPI_C_SOUTC functionality */,
  {(uint16)107, (uint8)2, (uint16)48}
  /* FEC_FEC_RXD3_IN functionality */,
  {(uint16)107, (uint8)4, (uint16)49}
  /* SENT_B_SENT2_B_IN functionality */,
  {(uint16)107, (uint8)7, (uint16)12}
  /* Settings information for pad 108 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_PCSB3 functionality */,
  {(uint16)108, (uint8)1, (uint16)50}
  /* DSPI_C_SINC functionality */,
  {(uint16)108, (uint8)6, (uint16)13}
  /* SENT_B_SENT3_B_IN functionality */,
  {(uint16)108, (uint8)7, (uint16)14}
  /* Settings information for pad 109 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_PCSB4 functionality */,
  {(uint16)109, (uint8)1, (uint16)51}
  /* DSPI_C_SCKC_OUT functionality */,
  {(uint16)109, (uint8)2, (uint16)52}
  /* FEC_FEC_MDC_OUT functionality */,
  {(uint16)109, (uint8)4, (uint16)53}
  /* DSPI_C_SCKC_IN functionality */,
  {(uint16)109, (uint8)6, (uint16)15}
  /* SENT_B_SENT4_B_IN functionality */,
  {(uint16)109, (uint8)7, (uint16)16}
  /* Settings information for pad 110 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_B_PCSB5 functionality */,
  {(uint16)110, (uint8)1, (uint16)54}
  /* DSPI_C_PCSC0_OUT functionality */,
  {(uint16)110, (uint8)2, (uint16)55}
  /* FEC_FEC_RXD2_IN functionality */,
  {(uint16)110, (uint8)4, (uint16)56}
  /* DSPI_C_PCSC0_IN functionality */,
  {(uint16)110, (uint8)6, (uint16)17}
  /* SENT_B_SENT5_B_IN functionality */,
  {(uint16)110, (uint8)7, (uint16)18}
  /* Settings information for pad 111 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 112 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 113 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_TCRCLKA functionality */,
  {(uint16)113, (uint8)1, (uint16)57}
  /* SIU_A_IRQ7 functionality */,
  {(uint16)113, (uint8)2, (uint16)58}
  /* Settings information for pad 114 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA0_IN functionality */,
  {(uint16)114, (uint8)1, (uint16)59}
  /* eTPU_A_ETPUA12 functionality */,
  {(uint16)114, (uint8)2, (uint16)60}
  /* Settings information for pad 115 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA1_IN functionality */,
  {(uint16)115, (uint8)1, (uint16)61}
  /* eTPU_A_ETPUA13 functionality */,
  {(uint16)115, (uint8)2, (uint16)62}
  /* Settings information for pad 116 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA2_IN functionality */,
  {(uint16)116, (uint8)1, (uint16)63}
  /* eTPU_A_ETPUA14 functionality */,
  {(uint16)116, (uint8)2, (uint16)64}
  /* REACM_RCH0_A_OUT functionality */,
  {(uint16)116, (uint8)3, (uint16)65}
  /* Settings information for pad 117 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA3_IN functionality */,
  {(uint16)117, (uint8)1, (uint16)66}
  /* eTPU_A_ETPUA15 functionality */,
  {(uint16)117, (uint8)2, (uint16)67}
  /* REACM_RCH1_A_OUT functionality */,
  {(uint16)117, (uint8)3, (uint16)68}
  /* FCCU_ERROR0 functionality */,
  {(uint16)117, (uint8)4, (uint16)69}
  /* Settings information for pad 118 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA4_IN functionality */,
  {(uint16)118, (uint8)1, (uint16)70}
  /* eTPU_A_ETPUA16 functionality */,
  {(uint16)118, (uint8)2, (uint16)71}
  /* REACM_RCH2_A_OUT functionality */,
  {(uint16)118, (uint8)3, (uint16)72}
  /* Settings information for pad 119 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA5_IN functionality */,
  {(uint16)119, (uint8)1, (uint16)73}
  /* eTPU_A_ETPUA17 functionality */,
  {(uint16)119, (uint8)2, (uint16)74}
  /* REACM_RCH3_A_OUT functionality */,
  {(uint16)119, (uint8)3, (uint16)75}
  /* Settings information for pad 120 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA6_IN functionality */,
  {(uint16)120, (uint8)1, (uint16)76}
  /* eTPU_A_ETPUA18 functionality */,
  {(uint16)120, (uint8)2, (uint16)77}
  /* REACM_RCH4_A_OUT functionality */,
  {(uint16)120, (uint8)3, (uint16)78}
  /* Settings information for pad 121 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA7_IN functionality */,
  {(uint16)121, (uint8)1, (uint16)79}
  /* eTPU_A_ETPUA19 functionality */,
  {(uint16)121, (uint8)2, (uint16)80}
  /* REACM_RCH5_A_OUT functionality */,
  {(uint16)121, (uint8)3, (uint16)81}
  /* Settings information for pad 122 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA8_IN functionality */,
  {(uint16)122, (uint8)1, (uint16)82}
  /* eTPU_A_ETPUA20 functionality */,
  {(uint16)122, (uint8)2, (uint16)83}
  /* REACM_RCH6_A_OUT functionality */,
  {(uint16)122, (uint8)3, (uint16)84}
  /* Settings information for pad 123 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA9_IN functionality */,
  {(uint16)123, (uint8)1, (uint16)85}
  /* eTPU_A_ETPUA21 functionality */,
  {(uint16)123, (uint8)2, (uint16)86}
  /* REACM_RCH7_A_OUT functionality */,
  {(uint16)123, (uint8)3, (uint16)87}
  /* Settings information for pad 124 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA10_IN functionality */,
  {(uint16)124, (uint8)1, (uint16)88}
  /* eTPU_A_ETPUA22 functionality */,
  {(uint16)124, (uint8)2, (uint16)89}
  /* REACM_RCH8_A_OUT functionality */,
  {(uint16)124, (uint8)3, (uint16)90}
  /* FCCU_ERRORIN functionality */,
  {(uint16)124, (uint8)4, (uint16)91}
  /* Settings information for pad 125 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA11_IN functionality */,
  {(uint16)125, (uint8)1, (uint16)92}
  /* eTPU_A_ETPUA23 functionality */,
  {(uint16)125, (uint8)2, (uint16)93}
  /* REACM_RCH9_A_OUT functionality */,
  {(uint16)125, (uint8)3, (uint16)94}
  /* FCCU_ERROR1 functionality */,
  {(uint16)125, (uint8)4, (uint16)95}
  /* Settings information for pad 126 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA12_IN functionality */,
  {(uint16)126, (uint8)1, (uint16)96}
  /* DSPI_B_PCSB1 functionality */,
  {(uint16)126, (uint8)2, (uint16)97}
  /* Settings information for pad 127 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA13_IN functionality */,
  {(uint16)127, (uint8)1, (uint16)98}
  /* DSPI_B_PCSB3 functionality */,
  {(uint16)127, (uint8)2, (uint16)99}
  /* Settings information for pad 128 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA14_IN functionality */,
  {(uint16)128, (uint8)1, (uint16)100}
  /* DSPI_B_PCSB4 functionality */,
  {(uint16)128, (uint8)2, (uint16)101}
  /* Settings information for pad 129 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA15_IN functionality */,
  {(uint16)129, (uint8)1, (uint16)102}
  /* DSPI_B_PCSB5 functionality */,
  {(uint16)129, (uint8)2, (uint16)103}
  /* MCAN_0_TX_OUT functionality */,
  {(uint16)129, (uint8)3, (uint16)104}
  /* Settings information for pad 130 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA16_IN functionality */,
  {(uint16)130, (uint8)1, (uint16)105}
  /* DSPI_D_PCSD1 functionality */,
  {(uint16)130, (uint8)2, (uint16)106}
  /* Settings information for pad 131 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA17_IN functionality */,
  {(uint16)131, (uint8)1, (uint16)107}
  /* DSPI_D_PCSD2 functionality */,
  {(uint16)131, (uint8)2, (uint16)108}
  /* Settings information for pad 132 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA18_IN functionality */,
  {(uint16)132, (uint8)1, (uint16)109}
  /* DSPI_D_PCSD3 functionality */,
  {(uint16)132, (uint8)2, (uint16)110}
  /* Settings information for pad 133 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA19_IN functionality */,
  {(uint16)133, (uint8)1, (uint16)111}
  /* DSPI_D_PCSD4 functionality */,
  {(uint16)133, (uint8)2, (uint16)112}
  /* MCAN_0_RX_IN functionality */,
  {(uint16)133, (uint8)7, (uint16)19}
  /* Settings information for pad 134 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA20_IN functionality */,
  {(uint16)134, (uint8)1, (uint16)113}
  /* SIU_A_IRQ8 functionality */,
  {(uint16)134, (uint8)2, (uint16)114}
  /* Settings information for pad 135 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA21_IN functionality */,
  {(uint16)135, (uint8)1, (uint16)115}
  /* SIU_A_IRQ9 functionality */,
  {(uint16)135, (uint8)2, (uint16)116}
  /* Settings information for pad 136 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA22_IN functionality */,
  {(uint16)136, (uint8)1, (uint16)117}
  /* SIU_A_IRQ10 functionality */,
  {(uint16)136, (uint8)2, (uint16)118}
  /* REACM_RCH0_A_OUT functionality */,
  {(uint16)136, (uint8)3, (uint16)119}
  /* Settings information for pad 137 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA23_IN functionality */,
  {(uint16)137, (uint8)1, (uint16)120}
  /* SIU_A_IRQ11 functionality */,
  {(uint16)137, (uint8)2, (uint16)121}
  /* REACM_RCH1_A_OUT functionality */,
  {(uint16)137, (uint8)3, (uint16)122}
  /* Settings information for pad 138 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA24_OUT functionality */,
  {(uint16)138, (uint8)1, (uint16)123}
  /* SIU_A_IRQ12 functionality */,
  {(uint16)138, (uint8)2, (uint16)124}
  /* REACM_RCH2_A_OUT functionality */,
  {(uint16)138, (uint8)3, (uint16)125}
  /* eTPU_A_ETPUA24_IN functionality */,
  {(uint16)138, (uint8)5, (uint16)20}
  /* Settings information for pad 139 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA25_OUT functionality */,
  {(uint16)139, (uint8)1, (uint16)126}
  /* SIU_A_IRQ13 functionality */,
  {(uint16)139, (uint8)2, (uint16)127}
  /* REACM_RCH3_A_OUT functionality */,
  {(uint16)139, (uint8)3, (uint16)128}
  /* eTPU_A_ETPUA25_IN functionality */,
  {(uint16)139, (uint8)5, (uint16)21}
  /* Settings information for pad 140 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA26_OUT functionality */,
  {(uint16)140, (uint8)1, (uint16)129}
  /* SIU_A_IRQ14 functionality */,
  {(uint16)140, (uint8)2, (uint16)130}
  /* REACM_RCH4_A_OUT functionality */,
  {(uint16)140, (uint8)3, (uint16)131}
  /* eTPU_A_ETPUA26_IN functionality */,
  {(uint16)140, (uint8)5, (uint16)22}
  /* Settings information for pad 141 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA27_OUT functionality */,
  {(uint16)141, (uint8)1, (uint16)132}
  /* SIU_A_IRQ15 functionality */,
  {(uint16)141, (uint8)2, (uint16)133}
  /* REACM_RCH5_A_OUT functionality */,
  {(uint16)141, (uint8)3, (uint16)134}
  /* eTPU_A_ETPUA27_IN functionality */,
  {(uint16)141, (uint8)5, (uint16)23}
  /* Settings information for pad 142 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA28_OUT functionality */,
  {(uint16)142, (uint8)1, (uint16)135}
  /* DSPI_C_PCSC1 functionality */,
  {(uint16)142, (uint8)2, (uint16)136}
  /* REACM_RCH6_A_OUT functionality */,
  {(uint16)142, (uint8)3, (uint16)137}
  /* eTPU_A_ETPUA28_IN functionality */,
  {(uint16)142, (uint8)5, (uint16)24}
  /* Settings information for pad 143 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA29_OUT functionality */,
  {(uint16)143, (uint8)1, (uint16)138}
  /* DSPI_C_PCSC2 functionality */,
  {(uint16)143, (uint8)2, (uint16)139}
  /* REACM_RCH7_A_OUT functionality */,
  {(uint16)143, (uint8)3, (uint16)140}
  /* eTPU_A_ETPUA29_IN functionality */,
  {(uint16)143, (uint8)5, (uint16)25}
  /* Settings information for pad 144 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA30_OUT functionality */,
  {(uint16)144, (uint8)1, (uint16)141}
  /* DSPI_C_PCSC3 functionality */,
  {(uint16)144, (uint8)2, (uint16)142}
  /* REACM_RCH8_A_OUT functionality */,
  {(uint16)144, (uint8)3, (uint16)143}
  /* eTPU_A_ETPUA30_IN functionality */,
  {(uint16)144, (uint8)5, (uint16)26}
  /* Settings information for pad 145 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA31_OUT functionality */,
  {(uint16)145, (uint8)1, (uint16)144}
  /* DSPI_C_PCSC4 functionality */,
  {(uint16)145, (uint8)2, (uint16)145}
  /* REACM_RCH9_A_OUT functionality */,
  {(uint16)145, (uint8)3, (uint16)146}
  /* eTPU_A_ETPUA31_IN functionality */,
  {(uint16)145, (uint8)5, (uint16)27}
  /* Settings information for pad 146 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_TCRCLKB functionality */,
  {(uint16)146, (uint8)1, (uint16)147}
  /* SIU_A_IRQ6 functionality */,
  {(uint16)146, (uint8)6, (uint16)28}
  /* Settings information for pad 147 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB0_IN functionality */,
  {(uint16)147, (uint8)1, (uint16)148}
  /* eTPU_B_ETPUB16 functionality */,
  {(uint16)147, (uint8)2, (uint16)149}
  /* Settings information for pad 148 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB1_IN functionality */,
  {(uint16)148, (uint8)1, (uint16)150}
  /* eTPU_B_ETPUB17 functionality */,
  {(uint16)148, (uint8)2, (uint16)151}
  /* Settings information for pad 149 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB2_IN functionality */,
  {(uint16)149, (uint8)1, (uint16)152}
  /* eTPU_B_ETPUB18 functionality */,
  {(uint16)149, (uint8)2, (uint16)153}
  /* Settings information for pad 150 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB3_IN functionality */,
  {(uint16)150, (uint8)1, (uint16)154}
  /* eTPU_B_ETPUB19 functionality */,
  {(uint16)150, (uint8)2, (uint16)155}
  /* Settings information for pad 151 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB4_IN functionality */,
  {(uint16)151, (uint8)1, (uint16)156}
  /* eTPU_B_ETPUB20 functionality */,
  {(uint16)151, (uint8)2, (uint16)157}
  /* Settings information for pad 152 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB5_IN functionality */,
  {(uint16)152, (uint8)1, (uint16)158}
  /* eTPU_B_ETPUB21 functionality */,
  {(uint16)152, (uint8)2, (uint16)159}
  /* Settings information for pad 153 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB6_IN functionality */,
  {(uint16)153, (uint8)1, (uint16)160}
  /* eTPU_B_ETPUB22 functionality */,
  {(uint16)153, (uint8)2, (uint16)161}
  /* Settings information for pad 154 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB7_IN functionality */,
  {(uint16)154, (uint8)1, (uint16)162}
  /* eTPU_B_ETPUB23 functionality */,
  {(uint16)154, (uint8)2, (uint16)163}
  /* Settings information for pad 155 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB8_IN functionality */,
  {(uint16)155, (uint8)1, (uint16)164}
  /* eTPU_B_ETPUB24 functionality */,
  {(uint16)155, (uint8)2, (uint16)165}
  /* Settings information for pad 156 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB9_IN functionality */,
  {(uint16)156, (uint8)1, (uint16)166}
  /* eTPU_B_ETPUB25 functionality */,
  {(uint16)156, (uint8)2, (uint16)167}
  /* Settings information for pad 157 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB10_IN functionality */,
  {(uint16)157, (uint8)1, (uint16)168}
  /* eTPU_B_ETPUB26 functionality */,
  {(uint16)157, (uint8)2, (uint16)169}
  /* Settings information for pad 158 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB11_IN functionality */,
  {(uint16)158, (uint8)1, (uint16)170}
  /* eTPU_B_ETPUB27 functionality */,
  {(uint16)158, (uint8)2, (uint16)171}
  /* Settings information for pad 159 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB12_IN functionality */,
  {(uint16)159, (uint8)1, (uint16)172}
  /* eTPU_B_ETPUB28 functionality */,
  {(uint16)159, (uint8)2, (uint16)173}
  /* Settings information for pad 160 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB13_IN functionality */,
  {(uint16)160, (uint8)1, (uint16)174}
  /* eTPU_B_ETPUB29 functionality */,
  {(uint16)160, (uint8)2, (uint16)175}
  /* Settings information for pad 161 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB14_IN functionality */,
  {(uint16)161, (uint8)1, (uint16)176}
  /* eTPU_B_ETPUB30 functionality */,
  {(uint16)161, (uint8)2, (uint16)177}
  /* Settings information for pad 162 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB15_IN functionality */,
  {(uint16)162, (uint8)1, (uint16)178}
  /* eTPU_B_ETPUB31 functionality */,
  {(uint16)162, (uint8)2, (uint16)179}
  /* Settings information for pad 163 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB16_IN functionality */,
  {(uint16)163, (uint8)1, (uint16)180}
  /* DSPI_A_PCSA1 functionality */,
  {(uint16)163, (uint8)2, (uint16)181}
  /* Settings information for pad 164 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB17_IN functionality */,
  {(uint16)164, (uint8)1, (uint16)182}
  /* DSPI_A_PCSA2 functionality */,
  {(uint16)164, (uint8)2, (uint16)183}
  /* Settings information for pad 165 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB18_IN functionality */,
  {(uint16)165, (uint8)1, (uint16)184}
  /* DSPI_A_PCSA3 functionality */,
  {(uint16)165, (uint8)2, (uint16)185}
  /* Settings information for pad 166 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB19_IN functionality */,
  {(uint16)166, (uint8)1, (uint16)186}
  /* DSPI_A_PCSA4 functionality */,
  {(uint16)166, (uint8)2, (uint16)187}
  /* Settings information for pad 167 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB20_IN functionality */,
  {(uint16)167, (uint8)1, (uint16)188}
  /* Settings information for pad 168 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB21_IN functionality */,
  {(uint16)168, (uint8)1, (uint16)189}
  /* Settings information for pad 169 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB22_IN functionality */,
  {(uint16)169, (uint8)1, (uint16)190}
  /* REACM_RCH0_B_OUT functionality */,
  {(uint16)169, (uint8)2, (uint16)191}
  /* Settings information for pad 170 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB23_IN functionality */,
  {(uint16)170, (uint8)1, (uint16)192}
  /* REACM_RCH1_B_OUT functionality */,
  {(uint16)170, (uint8)2, (uint16)193}
  /* Settings information for pad 171 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB24_IN functionality */,
  {(uint16)171, (uint8)1, (uint16)194}
  /* REACM_RCH2_B_OUT functionality */,
  {(uint16)171, (uint8)2, (uint16)195}
  /* Settings information for pad 172 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB25_IN functionality */,
  {(uint16)172, (uint8)1, (uint16)196}
  /* REACM_RCH3_B_OUT functionality */,
  {(uint16)172, (uint8)2, (uint16)197}
  /* Settings information for pad 173 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB26_IN functionality */,
  {(uint16)173, (uint8)1, (uint16)198}
  /* REACM_RCH4_B_OUT functionality */,
  {(uint16)173, (uint8)2, (uint16)199}
  /* Settings information for pad 174 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB27_IN functionality */,
  {(uint16)174, (uint8)1, (uint16)200}
  /* REACM_RCH5_B_OUT functionality */,
  {(uint16)174, (uint8)2, (uint16)201}
  /* Settings information for pad 175 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB28_IN functionality */,
  {(uint16)175, (uint8)1, (uint16)202}
  /* REACM_RCH6_B_OUT functionality */,
  {(uint16)175, (uint8)2, (uint16)203}
  /* Settings information for pad 176 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB29_IN functionality */,
  {(uint16)176, (uint8)1, (uint16)204}
  /* REACM_RCH7_B_OUT functionality */,
  {(uint16)176, (uint8)2, (uint16)205}
  /* Settings information for pad 177 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB30_IN functionality */,
  {(uint16)177, (uint8)1, (uint16)206}
  /* REACM_RCH8_B_OUT functionality */,
  {(uint16)177, (uint8)2, (uint16)207}
  /* Settings information for pad 178 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_B_ETPUB31_IN functionality */,
  {(uint16)178, (uint8)1, (uint16)208}
  /* REACM_RCH9_B_OUT functionality */,
  {(uint16)178, (uint8)2, (uint16)209}
  /* Settings information for pad 179 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS0_IN functionality */,
  {(uint16)179, (uint8)1, (uint16)210}
  /* eTPU_A_ETPUA0 functionality */,
  {(uint16)179, (uint8)2, (uint16)211}
  /* REACM_RCH0_C_OUT functionality */,
  {(uint16)179, (uint8)3, (uint16)212}
  /* Settings information for pad 180 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS1_IN functionality */,
  {(uint16)180, (uint8)1, (uint16)213}
  /* eTPU_A_ETPUA1 functionality */,
  {(uint16)180, (uint8)2, (uint16)214}
  /* REACM_RCH1_C_OUT functionality */,
  {(uint16)180, (uint8)3, (uint16)215}
  /* DSPI_E_PCSE2 functionality */,
  {(uint16)180, (uint8)4, (uint16)216}
  /* Settings information for pad 181 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS2_IN functionality */,
  {(uint16)181, (uint8)1, (uint16)217}
  /* eTPU_A_ETPUA2 functionality */,
  {(uint16)181, (uint8)2, (uint16)218}
  /* REACM_RCH2_C_OUT functionality */,
  {(uint16)181, (uint8)3, (uint16)219}
  /* DSPI_E_PCSE3 functionality */,
  {(uint16)181, (uint8)4, (uint16)220}
  /* Settings information for pad 182 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS3_IN functionality */,
  {(uint16)182, (uint8)1, (uint16)221}
  /* eTPU_A_ETPUA3 functionality */,
  {(uint16)182, (uint8)2, (uint16)222}
  /* REACM_RCH3_C_OUT functionality */,
  {(uint16)182, (uint8)3, (uint16)223}
  /* DSPI_E_PCSE4 functionality */,
  {(uint16)182, (uint8)4, (uint16)224}
  /* Settings information for pad 183 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS4 functionality */,
  {(uint16)183, (uint8)1, (uint16)225}
  /* eTPU_A_ETPUA4 functionality */,
  {(uint16)183, (uint8)2, (uint16)226}
  /* REACM_RCH4_C_OUT functionality */,
  {(uint16)183, (uint8)3, (uint16)227}
  /* DSPI_E_PCSE5 functionality */,
  {(uint16)183, (uint8)4, (uint16)228}
  /* Settings information for pad 184 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS5 functionality */,
  {(uint16)184, (uint8)1, (uint16)229}
  /* eTPU_A_ETPUA5 functionality */,
  {(uint16)184, (uint8)2, (uint16)230}
  /* REACM_RCH5_C_OUT functionality */,
  {(uint16)184, (uint8)3, (uint16)231}
  /* Settings information for pad 185 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS6_IN functionality */,
  {(uint16)185, (uint8)1, (uint16)232}
  /* eTPU_A_ETPUA6 functionality */,
  {(uint16)185, (uint8)2, (uint16)233}
  /* REACM_RCH6_C_OUT functionality */,
  {(uint16)185, (uint8)3, (uint16)234}
  /* Settings information for pad 186 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS7_IN functionality */,
  {(uint16)186, (uint8)1, (uint16)235}
  /* eTPU_A_ETPUA7 functionality */,
  {(uint16)186, (uint8)2, (uint16)236}
  /* REACM_RCH7_C_OUT functionality */,
  {(uint16)186, (uint8)3, (uint16)237}
  /* Settings information for pad 187 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS0_IN functionality */,
  {(uint16)187, (uint8)1, (uint16)238}
  /* eTPU_A_ETPUA8 functionality */,
  {(uint16)187, (uint8)2, (uint16)239}
  /* REACM_RCH8_C_OUT functionality */,
  {(uint16)187, (uint8)3, (uint16)240}
  /* Settings information for pad 188 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS1_IN functionality */,
  {(uint16)188, (uint8)1, (uint16)241}
  /* eTPU_A_ETPUA9 functionality */,
  {(uint16)188, (uint8)2, (uint16)242}
  /* REACM_RCH9_C_OUT functionality */,
  {(uint16)188, (uint8)3, (uint16)243}
  /* Settings information for pad 189 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS2_IN functionality */,
  {(uint16)189, (uint8)1, (uint16)244}
  /* DSPI_D_SCKD_OUT functionality */,
  {(uint16)189, (uint8)2, (uint16)245}
  /* DSPI_D_SCKD_IN functionality */,
  {(uint16)189, (uint8)6, (uint16)29}
  /* Settings information for pad 190 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS3_IN functionality */,
  {(uint16)190, (uint8)1, (uint16)246}
  /* DSPI_D_SIND functionality */,
  {(uint16)190, (uint8)6, (uint16)30}
  /* Settings information for pad 191 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS4_IN functionality */,
  {(uint16)191, (uint8)1, (uint16)247}
  /* DSPI_C_SOUTC functionality */,
  {(uint16)191, (uint8)2, (uint16)248}
  /* Settings information for pad 192 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS5_IN functionality */,
  {(uint16)192, (uint8)1, (uint16)249}
  /* DSPI_D_SOUTD functionality */,
  {(uint16)192, (uint8)2, (uint16)250}
  /* Settings information for pad 193 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS6 functionality */,
  {(uint16)193, (uint8)1, (uint16)251}
  /* FlexCAN_D_CNTXD functionality */,
  {(uint16)193, (uint8)3, (uint16)252}
  /* REACM_RCH0_C_OUT functionality */,
  {(uint16)193, (uint8)4, (uint16)253}
  /* SIU_A_IRQ0 functionality */,
  {(uint16)193, (uint8)6, (uint16)31}
  /* Settings information for pad 194 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS7 functionality */,
  {(uint16)194, (uint8)1, (uint16)254}
  /* REACM_RCH1_C_OUT functionality */,
  {(uint16)194, (uint8)4, (uint16)255}
  /* SIU_A_IRQ1_IN functionality */,
  {(uint16)194, (uint8)6, (uint16)32}
  /* FlexCAN_D_CNRXD_IN functionality */,
  {(uint16)194, (uint8)7, (uint16)33}
  /* Settings information for pad 195 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS16_OUT functionality */,
  {(uint16)195, (uint8)1, (uint16)256}
  /* eTPU_B_ETPUB0 functionality */,
  {(uint16)195, (uint8)2, (uint16)257}
  /* MCAN_1_TX_OUT functionality */,
  {(uint16)195, (uint8)3, (uint16)258}
  /* REACM_RCH2_C_OUT functionality */,
  {(uint16)195, (uint8)4, (uint16)259}
  /* eMIOS_A_EMIOS16_IN functionality */,
  {(uint16)195, (uint8)5, (uint16)34}
  /* Settings information for pad 196 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS17_OUT functionality */,
  {(uint16)196, (uint8)1, (uint16)260}
  /* eTPU_B_ETPUB1 functionality */,
  {(uint16)196, (uint8)2, (uint16)261}
  /* REACM_RCH3_C_OUT functionality */,
  {(uint16)196, (uint8)4, (uint16)262}
  /* eMIOS_A_EMIOS17_IN functionality */,
  {(uint16)196, (uint8)5, (uint16)35}
  /* MCAN_1_RX_IN functionality */,
  {(uint16)196, (uint8)7, (uint16)36}
  /* Settings information for pad 197 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS18_OUT functionality */,
  {(uint16)197, (uint8)1, (uint16)263}
  /* eTPU_B_ETPUB2 functionality */,
  {(uint16)197, (uint8)2, (uint16)264}
  /* REACM_RCH4_C_OUT functionality */,
  {(uint16)197, (uint8)3, (uint16)265}
  /* eMIOS_A_EMIOS18_IN functionality */,
  {(uint16)197, (uint8)5, (uint16)37}
  /* Settings information for pad 198 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS19_OUT functionality */,
  {(uint16)198, (uint8)1, (uint16)266}
  /* eTPU_B_ETPUB3 functionality */,
  {(uint16)198, (uint8)2, (uint16)267}
  /* REACM_RCH5_C_OUT functionality */,
  {(uint16)198, (uint8)3, (uint16)268}
  /* eMIOS_A_EMIOS19_IN functionality */,
  {(uint16)198, (uint8)5, (uint16)38}
  /* Settings information for pad 199 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS20_OUT functionality */,
  {(uint16)199, (uint8)1, (uint16)269}
  /* eTPU_B_ETPUB4 functionality */,
  {(uint16)199, (uint8)2, (uint16)270}
  /* REACM_RCH6_C_OUT functionality */,
  {(uint16)199, (uint8)3, (uint16)271}
  /* eMIOS_A_EMIOS20_IN functionality */,
  {(uint16)199, (uint8)5, (uint16)39}
  /* Settings information for pad 200 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS21_OUT functionality */,
  {(uint16)200, (uint8)1, (uint16)272}
  /* eTPU_B_ETPUB5 functionality */,
  {(uint16)200, (uint8)2, (uint16)273}
  /* REACM_RCH7_C_OUT functionality */,
  {(uint16)200, (uint8)3, (uint16)274}
  /* eMIOS_A_EMIOS21_IN functionality */,
  {(uint16)200, (uint8)5, (uint16)40}
  /* Settings information for pad 201 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS22_OUT functionality */,
  {(uint16)201, (uint8)1, (uint16)275}
  /* eTPU_B_ETPUB6 functionality */,
  {(uint16)201, (uint8)2, (uint16)276}
  /* REACM_RCH8_C_OUT functionality */,
  {(uint16)201, (uint8)3, (uint16)277}
  /* eMIOS_A_EMIOS22_IN functionality */,
  {(uint16)201, (uint8)5, (uint16)41}
  /* Settings information for pad 202 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_A_EMIOS23_OUT functionality */,
  {(uint16)202, (uint8)1, (uint16)278}
  /* eTPU_B_ETPUB7 functionality */,
  {(uint16)202, (uint8)2, (uint16)279}
  /* REACM_RCH9_C_OUT functionality */,
  {(uint16)202, (uint8)3, (uint16)280}
  /* eMIOS_A_EMIOS23_IN functionality */,
  {(uint16)202, (uint8)5, (uint16)42}
  /* Settings information for pad 203 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS16_OUT functionality */,
  {(uint16)203, (uint8)1, (uint16)281}
  /* DSPI_B_PCSB0_OUT functionality */,
  {(uint16)203, (uint8)2, (uint16)282}
  /* eMIOS_B_EMIOS16_IN functionality */,
  {(uint16)203, (uint8)5, (uint16)43}
  /* DSPI_B_PCSB0_IN functionality */,
  {(uint16)203, (uint8)6, (uint16)44}
  /* Settings information for pad 204 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS17_OUT functionality */,
  {(uint16)204, (uint8)1, (uint16)283}
  /* DSPI_B_PCSB1 functionality */,
  {(uint16)204, (uint8)2, (uint16)284}
  /* eMIOS_B_EMIOS17_IN functionality */,
  {(uint16)204, (uint8)5, (uint16)45}
  /* Settings information for pad 205 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 206 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 207 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 208 {PCR, Mode, Index to Mux or Inmux table} */
  /* SoC_PLLCFG0_IN functionality */,
  {(uint16)208, (uint8)1, (uint16)285}
  /* eTPU_C_ETPUC9_OUT functionality */,
  {(uint16)208, (uint8)3, (uint16)286}
  /* SIPI_TXN functionality */,
  {(uint16)208, (uint8)4, (uint16)287}
  /* SIU_A_IRQ4_IN functionality */,
  {(uint16)208, (uint8)6, (uint16)46}
  /* eTPU_C_ETPUC9_IN functionality */,
  {(uint16)208, (uint8)7, (uint16)47}
  /* Settings information for pad 209 {PCR, Mode, Index to Mux or Inmux table} */
  /* SoC_PLLCFG1_IN functionality */,
  {(uint16)209, (uint8)1, (uint16)288}
  /* DSPI_D_SOUTD functionality */,
  {(uint16)209, (uint8)3, (uint16)289}
  /* SIPI_TXP functionality */,
  {(uint16)209, (uint8)4, (uint16)290}
  /* SIU_A_IRQ5_IN functionality */,
  {(uint16)209, (uint8)6, (uint16)48}
  /* Settings information for pad 210 {PCR, Mode, Index to Mux or Inmux table} */
  /* SoC_PLLCFG2_IN functionality */,
  {(uint16)210, (uint8)1, (uint16)291}
  /* eTPU_C_ETPUC3_OUT functionality */,
  {(uint16)210, (uint8)2, (uint16)292}
  /* DSPI_E_PCSE1 functionality */,
  {(uint16)210, (uint8)3, (uint16)293}
  /* SIPI_REFCLK_IN functionality */,
  {(uint16)210, (uint8)4, (uint16)294}
  /* eTPU_C_ETPUC3_IN functionality */,
  {(uint16)210, (uint8)6, (uint16)49}
  /* Settings information for pad 211 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 212 {PCR, Mode, Index to Mux or Inmux table} */
  /* SoC_BOOTCFG1_IN functionality */,
  {(uint16)212, (uint8)1, (uint16)295}
  /* eTPU_C_ETPUC0_OUT functionality */,
  {(uint16)212, (uint8)3, (uint16)296}
  /* SIPI_RXP functionality */,
  {(uint16)212, (uint8)4, (uint16)297}
  /* SIU_A_IRQ3_IN functionality */,
  {(uint16)212, (uint8)6, (uint16)50}
  /* eTPU_C_ETPUC0_IN functionality */,
  {(uint16)212, (uint8)7, (uint16)51}
  /* Settings information for pad 213 {PCR, Mode, Index to Mux or Inmux table} */
  /* SoC_WKPCFG_IN functionality */,
  {(uint16)213, (uint8)1, (uint16)298}
  /* SIU_A_NMI_IN functionality */,
  {(uint16)213, (uint8)2, (uint16)299}
  /* eTPU_C_ETPUC1_OUT functionality */,
  {(uint16)213, (uint8)3, (uint16)300}
  /* SIPI_RXN functionality */,
  {(uint16)213, (uint8)4, (uint16)301}
  /* eTPU_C_ETPUC1_IN functionality */,
  {(uint16)213, (uint8)7, (uint16)52}
  /* Settings information for pad 214 {PCR, Mode, Index to Mux or Inmux table} */
  /* ENGCLK functionality */,
  {(uint16)214, (uint8)1, (uint16)302}
  /* Settings information for pad 215 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 216 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 217 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 218 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 219 {PCR, Mode, Index to Mux or Inmux table} */
  /* MCKO functionality */,
  {(uint16)219, (uint8)1, (uint16)303}
  /* Settings information for pad 220 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 221 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 222 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 223 {PCR, Mode, Index to Mux or Inmux table} */
  /* eSCI_E_TXDE functionality */,
  {(uint16)223, (uint8)6, (uint16)53}
  /* Settings information for pad 224 {PCR, Mode, Index to Mux or Inmux table} */
  /* MSEO0 functionality */,
  {(uint16)224, (uint8)1, (uint16)304}
  /* Settings information for pad 225 {PCR, Mode, Index to Mux or Inmux table} */
  /* MSEO1 functionality */,
  {(uint16)225, (uint8)1, (uint16)305}
  /* Settings information for pad 226 {PCR, Mode, Index to Mux or Inmux table} */
  /* RDY functionality */,
  {(uint16)226, (uint8)1, (uint16)306}
  /* Settings information for pad 227 {PCR, Mode, Index to Mux or Inmux table} */
  /* EVTO functionality */,
  {(uint16)227, (uint8)1, (uint16)307}
  /* Settings information for pad 228 {PCR, Mode, Index to Mux or Inmux table} */
  /* TDO functionality */,
  {(uint16)228, (uint8)1, (uint16)308}
  /* Settings information for pad 229 {PCR, Mode, Index to Mux or Inmux table} */
  /* D_CLKOUT functionality */,
  {(uint16)229, (uint8)1, (uint16)309}
  /* Settings information for pad 230 {PCR, Mode, Index to Mux or Inmux table} */
  /* RSTOUT functionality */,
  {(uint16)230, (uint8)1, (uint16)310}
  /* Settings information for pad 231 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 232 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 233 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 234 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 235 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_SCKC_OUT functionality */,
  {(uint16)235, (uint8)1, (uint16)311}
  /* DSPI_C_SCK_C_LVDS_P functionality */,
  {(uint16)235, (uint8)2, (uint16)312}
  /* DSPI_C_SCKC_IN functionality */,
  {(uint16)235, (uint8)5, (uint16)54}
  /* Settings information for pad 236 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_SCK_C_LVDS_N_OUT functionality */,
  {(uint16)236, (uint8)2, (uint16)313}
  /* DSPI_C_SINC_IN functionality */,
  {(uint16)236, (uint8)5, (uint16)55}
  /* Settings information for pad 237 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_SOUTC functionality */,
  {(uint16)237, (uint8)1, (uint16)314}
  /* DSPI_C_SOUT_C_LVDS_P functionality */,
  {(uint16)237, (uint8)2, (uint16)315}
  /* Settings information for pad 238 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_PCSC0_OUT functionality */,
  {(uint16)238, (uint8)1, (uint16)316}
  /* DSPI_C_SOUT_C_LVDS_N_OUT functionality */,
  {(uint16)238, (uint8)2, (uint16)317}
  /* DSPI_C_PCSC0_IN functionality */,
  {(uint16)238, (uint8)5, (uint16)56}
  /* Settings information for pad 239 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_PCSC1 functionality */,
  {(uint16)239, (uint8)1, (uint16)318}
  /* eSCI_D_TXDD functionality */,
  {(uint16)239, (uint8)2, (uint16)319}
  /* Settings information for pad 240 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_PCSC2 functionality */,
  {(uint16)240, (uint8)1, (uint16)320}
  /* DSPI_D_SCK_D_LVDS_P functionality */,
  {(uint16)240, (uint8)2, (uint16)321}
  /* DSPI_D_SCKD_OUT functionality */,
  {(uint16)240, (uint8)3, (uint16)322}
  /* DSPI_D_SCKD_IN functionality */,
  {(uint16)240, (uint8)7, (uint16)57}
  /* Settings information for pad 241 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_PCSC3 functionality */,
  {(uint16)241, (uint8)1, (uint16)323}
  /* DSPI_D_SCK_D_LVDS_N_OUT functionality */,
  {(uint16)241, (uint8)2, (uint16)324}
  /* DSPI_D_SIND_IN functionality */,
  {(uint16)241, (uint8)7, (uint16)58}
  /* Settings information for pad 242 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_PCSC4 functionality */,
  {(uint16)242, (uint8)1, (uint16)325}
  /* MCAN_0_TX_OUT functionality */,
  {(uint16)242, (uint8)2, (uint16)326}
  /* DSPI_D_SOUT_D_LVDS_P functionality */,
  {(uint16)242, (uint8)3, (uint16)327}
  /* DSPI_D_SOUTD functionality */,
  {(uint16)242, (uint8)4, (uint16)328}
  /* Settings information for pad 243 {PCR, Mode, Index to Mux or Inmux table} */
  /* DSPI_C_PCSC5 functionality */,
  {(uint16)243, (uint8)1, (uint16)329}
  /* DSPI_D_SOUT_D_LVDS_N_OUT functionality */,
  {(uint16)243, (uint8)3, (uint16)330}
  /* DSPI_D_PCSD0_OUT functionality */,
  {(uint16)243, (uint8)4, (uint16)331}
  /* MCAN_0_RX_IN functionality */,
  {(uint16)243, (uint8)6, (uint16)59}
  /* DSPI_D_PCSD0_IN functionality */,
  {(uint16)243, (uint8)8, (uint16)60}
  /* Settings information for pad 244 {PCR, Mode, Index to Mux or Inmux table} */
  /* eSCI_C_TXDC functionality */,
  {(uint16)244, (uint8)1, (uint16)332}
  /* eQADC_A_eQADC_B_ETRIG0_IN functionality */,
  {(uint16)244, (uint8)2, (uint16)333}
  /* Settings information for pad 245 {PCR, Mode, Index to Mux or Inmux table} */
  /* eSCI_C_RXDC_IN functionality */,
  {(uint16)245, (uint8)1, (uint16)334}
  /* Settings information for pad 246 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_D_CNTXD functionality */,
  {(uint16)246, (uint8)1, (uint16)335}
  /* MCAN_1_TX_OUT functionality */,
  {(uint16)246, (uint8)3, (uint16)336}
  /* Settings information for pad 247 {PCR, Mode, Index to Mux or Inmux table} */
  /* FlexCAN_D_CNRXD_IN functionality */,
  {(uint16)247, (uint8)5, (uint16)61}
  /* MCAN_1_RX_IN functionality */,
  {(uint16)247, (uint8)7, (uint16)62}
  /* Settings information for pad 248 {PCR, Mode, Index to Mux or Inmux table} */
  /* FEC_FEC_TXD0_OUT functionality */,
  {(uint16)248, (uint8)1, (uint16)337}
  /* SENT_A_SENT0_A_IN functionality */,
  {(uint16)248, (uint8)6, (uint16)63}
  /* Settings information for pad 249 {PCR, Mode, Index to Mux or Inmux table} */
  /* FEC_FEC_RX_DV_IN functionality */,
  {(uint16)249, (uint8)1, (uint16)338}
  /* SENT_A_SENT1_A_IN functionality */,
  {(uint16)249, (uint8)6, (uint16)64}
  /* Settings information for pad 250 {PCR, Mode, Index to Mux or Inmux table} */
  /* FEC_FEC_RXD0_IN functionality */,
  {(uint16)250, (uint8)1, (uint16)339}
  /* SENT_A_SENT2_A_IN functionality */,
  {(uint16)250, (uint8)6, (uint16)65}
  /* Settings information for pad 251 {PCR, Mode, Index to Mux or Inmux table} */
  /* FEC_FEC_TXD1_OUT functionality */,
  {(uint16)251, (uint8)1, (uint16)340}
  /* SENT_A_SENT3_A_IN functionality */,
  {(uint16)251, (uint8)6, (uint16)66}
  /* Settings information for pad 252 {PCR, Mode, Index to Mux or Inmux table} */
  /* FEC_FEC_TXEN_OUT functionality */,
  {(uint16)252, (uint8)1, (uint16)341}
  /* SENT_A_SENT4_A_IN functionality */,
  {(uint16)252, (uint8)6, (uint16)67}
  /* Settings information for pad 253 {PCR, Mode, Index to Mux or Inmux table} */
  /* FEC_FEC_RXD1_IN functionality */,
  {(uint16)253, (uint8)1, (uint16)342}
  /* SENT_A_SENT5_A_IN functionality */,
  {(uint16)253, (uint8)6, (uint16)68}
  /* Settings information for pad 254 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 255 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 256 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 257 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 258 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 259 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 260 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 261 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 262 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 263 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 264 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 265 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 266 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 267 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 268 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 269 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 270 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 271 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 272 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 273 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 274 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 275 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 276 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 277 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 278 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 279 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 280 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 281 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 282 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 283 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 284 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 285 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 286 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 287 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 288 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 289 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 290 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 291 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 292 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 293 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 294 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 295 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 296 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 297 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 298 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 299 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 300 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 301 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 302 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 303 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 304 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 305 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 306 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 307 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 308 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 309 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 310 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 311 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 312 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 313 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 314 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 315 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 316 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 317 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 318 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 319 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 320 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 321 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 322 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 323 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 324 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 325 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 326 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 327 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 328 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 329 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 330 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 331 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 332 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 333 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 334 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 335 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 336 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 337 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 338 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 339 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 340 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 341 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 342 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 343 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 344 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 345 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 346 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 347 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 348 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 349 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 350 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 351 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 352 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 353 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 354 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 355 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 356 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 357 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 358 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 359 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 360 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 361 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 362 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 363 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 364 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 365 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 366 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 367 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 368 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 369 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 370 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 371 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 372 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 373 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 374 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 375 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 376 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 377 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 378 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 379 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 380 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 381 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 382 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 383 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 384 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 385 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 386 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 387 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 388 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 389 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 390 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 391 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 392 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 393 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 394 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 395 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 396 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 397 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 398 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 399 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 400 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 401 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 402 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 403 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 404 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 405 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 406 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 407 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 408 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 409 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 410 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 411 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 412 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 413 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 414 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 415 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 416 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 417 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 418 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 419 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 420 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 421 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 422 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 423 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 424 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 425 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 426 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 427 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 428 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 429 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 430 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 431 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 432 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS18_OUT functionality */,
  {(uint16)432, (uint8)1, (uint16)343}
  /* DSPI_B_PCSB2 functionality */,
  {(uint16)432, (uint8)2, (uint16)344}
  /* eMIOS_B_EMIOS18_IN functionality */,
  {(uint16)432, (uint8)5, (uint16)69}
  /* Settings information for pad 433 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS19_OUT functionality */,
  {(uint16)433, (uint8)1, (uint16)345}
  /* DSPI_B_PCSB3 functionality */,
  {(uint16)433, (uint8)2, (uint16)346}
  /* eMIOS_B_EMIOS19_IN functionality */,
  {(uint16)433, (uint8)5, (uint16)70}
  /* Settings information for pad 434 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS20_OUT functionality */,
  {(uint16)434, (uint8)1, (uint16)347}
  /* DSPI_C_PCSC0_OUT functionality */,
  {(uint16)434, (uint8)2, (uint16)348}
  /* eMIOS_B_EMIOS20_IN functionality */,
  {(uint16)434, (uint8)5, (uint16)71}
  /* DSPI_C_PCSC0_IN functionality */,
  {(uint16)434, (uint8)6, (uint16)72}
  /* Settings information for pad 435 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS21_OUT functionality */,
  {(uint16)435, (uint8)1, (uint16)349}
  /* DSPI_C_PCSC1 functionality */,
  {(uint16)435, (uint8)2, (uint16)350}
  /* eMIOS_B_EMIOS21_IN functionality */,
  {(uint16)435, (uint8)5, (uint16)73}
  /* Settings information for pad 436 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS22_OUT functionality */,
  {(uint16)436, (uint8)1, (uint16)351}
  /* DSPI_C_PCSC2 functionality */,
  {(uint16)436, (uint8)2, (uint16)352}
  /* eMIOS_B_EMIOS22_IN functionality */,
  {(uint16)436, (uint8)5, (uint16)74}
  /* Settings information for pad 437 {PCR, Mode, Index to Mux or Inmux table} */
  /* eMIOS_B_EMIOS23_OUT functionality */,
  {(uint16)437, (uint8)1, (uint16)353}
  /* DSPI_C_PCSC5 functionality */,
  {(uint16)437, (uint8)2, (uint16)354}
  /* eMIOS_B_EMIOS23_IN functionality */,
  {(uint16)437, (uint8)5, (uint16)75}
  /* Settings information for pad 438 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 439 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 440 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_TCRCLKC_IN functionality */,
  {(uint16)440, (uint8)5, (uint16)76}
  /* SIU_A_IRQ6_IN functionality */,
  {(uint16)440, (uint8)6, (uint16)77}
  /* Settings information for pad 441 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC0_IN functionality */,
  {(uint16)441, (uint8)5, (uint16)78}
  /* SENT_A_SENT0_A_IN functionality */,
  {(uint16)441, (uint8)6, (uint16)79}
  /* Settings information for pad 442 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC1_IN functionality */,
  {(uint16)442, (uint8)5, (uint16)80}
  /* SENT_A_SENT1_A_IN functionality */,
  {(uint16)442, (uint8)6, (uint16)81}
  /* Settings information for pad 443 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC2_IN functionality */,
  {(uint16)443, (uint8)1, (uint16)355}
  /* SENT_A_SENT3_A_IN functionality */,
  {(uint16)443, (uint8)6, (uint16)82}
  /* Settings information for pad 444 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC3_IN functionality */,
  {(uint16)444, (uint8)5, (uint16)83}
  /* SENT_A_SENT4_A_IN functionality */,
  {(uint16)444, (uint8)6, (uint16)84}
  /* Settings information for pad 445 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC4_IN functionality */,
  {(uint16)445, (uint8)1, (uint16)356}
  /* SENT_A_SENT5_A_IN functionality */,
  {(uint16)445, (uint8)6, (uint16)85}
  /* eTPU_C_TCRCLKC_IN functionality */,
  {(uint16)445, (uint8)7, (uint16)86}
  /* Settings information for pad 446 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC5_IN functionality */,
  {(uint16)446, (uint8)1, (uint16)357}
  /* DSPI_E_PCSE2 functionality */,
  {(uint16)446, (uint8)2, (uint16)358}
  /* SENT_B_SENT0_B_IN functionality */,
  {(uint16)446, (uint8)7, (uint16)87}
  /* Settings information for pad 447 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC6_IN functionality */,
  {(uint16)447, (uint8)1, (uint16)359}
  /* DSPI_E_PCSE3 functionality */,
  {(uint16)447, (uint8)2, (uint16)360}
  /* SENT_B_SENT1_B_IN functionality */,
  {(uint16)447, (uint8)7, (uint16)88}
  /* Settings information for pad 448 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC7_IN functionality */,
  {(uint16)448, (uint8)1, (uint16)361}
  /* DSPI_E_PCSE4 functionality */,
  {(uint16)448, (uint8)2, (uint16)362}
  /* SENT_B_SENT2_B_IN functionality */,
  {(uint16)448, (uint8)7, (uint16)89}
  /* Settings information for pad 449 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC8_OUT functionality */,
  {(uint16)449, (uint8)1, (uint16)363}
  /* DSPI_E_PCSE5 functionality */,
  {(uint16)449, (uint8)2, (uint16)364}
  /* eTPU_C_ETPUC8_IN functionality */,
  {(uint16)449, (uint8)5, (uint16)90}
  /* SENT_B_SENT3_B_IN functionality */,
  {(uint16)449, (uint8)7, (uint16)91}
  /* Settings information for pad 450 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC9_IN functionality */,
  {(uint16)450, (uint8)5, (uint16)92}
  /* SIU_A_IRQ0_IN functionality */,
  {(uint16)450, (uint8)6, (uint16)93}
  /* SENT_B_SENT4_B_IN functionality */,
  {(uint16)450, (uint8)7, (uint16)94}
  /* Settings information for pad 451 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC10_OUT functionality */,
  {(uint16)451, (uint8)1, (uint16)365}
  /* eTPU_C_ETPUC10_IN functionality */,
  {(uint16)451, (uint8)5, (uint16)95}
  /* SIU_A_IRQ1_IN functionality */,
  {(uint16)451, (uint8)6, (uint16)96}
  /* SENT_B_SENT5_B_IN functionality */,
  {(uint16)451, (uint8)7, (uint16)97}
  /* Settings information for pad 452 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC11_OUT functionality */,
  {(uint16)452, (uint8)1, (uint16)366}
  /* eTPU_C_ETPUC11_IN functionality */,
  {(uint16)452, (uint8)5, (uint16)98}
  /* SIU_A_IRQ2_IN functionality */,
  {(uint16)452, (uint8)6, (uint16)99}
  /* Settings information for pad 453 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC12_OUT functionality */,
  {(uint16)453, (uint8)1, (uint16)367}
  /* MCAN_1_TX_OUT functionality */,
  {(uint16)453, (uint8)3, (uint16)368}
  /* eTPU_C_ETPUC12_IN functionality */,
  {(uint16)453, (uint8)5, (uint16)100}
  /* SIU_A_IRQ3_IN functionality */,
  {(uint16)453, (uint8)6, (uint16)101}
  /* Settings information for pad 454 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC13_OUT functionality */,
  {(uint16)454, (uint8)1, (uint16)369}
  /* PSI5A_SDOUT0_PSI5A_OUT functionality */,
  {(uint16)454, (uint8)3, (uint16)370}
  /* REACM_RCH0_C_OUT functionality */,
  {(uint16)454, (uint8)4, (uint16)371}
  /* eTPU_C_ETPUC13_IN functionality */,
  {(uint16)454, (uint8)5, (uint16)102}
  /* SIU_A_IRQ4_IN functionality */,
  {(uint16)454, (uint8)6, (uint16)103}
  /* Settings information for pad 455 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC14_OUT functionality */,
  {(uint16)455, (uint8)1, (uint16)372}
  /* PSI5A_SDIN0_PSI5A_IN functionality */,
  {(uint16)455, (uint8)3, (uint16)373}
  /* REACM_RCH1_C_OUT functionality */,
  {(uint16)455, (uint8)4, (uint16)374}
  /* eTPU_C_ETPUC14_IN functionality */,
  {(uint16)455, (uint8)5, (uint16)104}
  /* SIU_A_IRQ5_IN functionality */,
  {(uint16)455, (uint8)6, (uint16)105}
  /* Settings information for pad 456 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC15_OUT functionality */,
  {(uint16)456, (uint8)1, (uint16)375}
  /* REACM_RCH2_C_OUT functionality */,
  {(uint16)456, (uint8)3, (uint16)376}
  /* eTPU_C_ETPUC15_IN functionality */,
  {(uint16)456, (uint8)5, (uint16)106}
  /* MCAN_1_RX_IN functionality */,
  {(uint16)456, (uint8)6, (uint16)107}
  /* Settings information for pad 457 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC16_IN functionality */,
  {(uint16)457, (uint8)1, (uint16)377}
  /* MCAN_1_TX_OUT functionality */,
  {(uint16)457, (uint8)2, (uint16)378}
  /* REACM_RCH3_C_OUT functionality */,
  {(uint16)457, (uint8)3, (uint16)379}
  /* Settings information for pad 458 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC17_IN functionality */,
  {(uint16)458, (uint8)1, (uint16)380}
  /* eSCI_F_TXDF functionality */,
  {(uint16)458, (uint8)2, (uint16)381}
  /* REACM_RCH4_C_OUT functionality */,
  {(uint16)458, (uint8)3, (uint16)382}
  /* Settings information for pad 459 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC18_IN functionality */,
  {(uint16)459, (uint8)1, (uint16)383}
  /* eSCI_F_RXDF_IN functionality */,
  {(uint16)459, (uint8)2, (uint16)384}
  /* Settings information for pad 460 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC19_IN functionality */,
  {(uint16)460, (uint8)1, (uint16)385}
  /* PSI5A_SDOUT0_PSI5B_OUT functionality */,
  {(uint16)460, (uint8)3, (uint16)386}
  /* eSCI_A_TXDA functionality */,
  {(uint16)460, (uint8)6, (uint16)108}
  /* Settings information for pad 461 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC20_IN functionality */,
  {(uint16)461, (uint8)1, (uint16)387}
  /* PSI5A_SDIN0_PSI5B_IN functionality */,
  {(uint16)461, (uint8)3, (uint16)388}
  /* eSCI_A_RXDA_IN functionality */,
  {(uint16)461, (uint8)6, (uint16)109}
  /* Settings information for pad 462 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC21_IN functionality */,
  {(uint16)462, (uint8)1, (uint16)389}
  /* eSCI_B_TXDB functionality */,
  {(uint16)462, (uint8)6, (uint16)110}
  /* Settings information for pad 463 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC22_IN functionality */,
  {(uint16)463, (uint8)1, (uint16)390}
  /* eSCI_B_RXDB_IN functionality */,
  {(uint16)463, (uint8)6, (uint16)111}
  /* Settings information for pad 464 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC23_IN functionality */,
  {(uint16)464, (uint8)1, (uint16)391}
  /* DSPI_D_PCSD5 functionality */,
  {(uint16)464, (uint8)2, (uint16)392}
  /* eQADC_A_MAA0 functionality */,
  {(uint16)464, (uint8)3, (uint16)393}
  /* eQADC_B_MAB0 functionality */,
  {(uint16)464, (uint8)4, (uint16)394}
  /* Settings information for pad 465 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC24_IN functionality */,
  {(uint16)465, (uint8)1, (uint16)395}
  /* DSPI_D_PCSD4 functionality */,
  {(uint16)465, (uint8)2, (uint16)396}
  /* eQADC_A_MAA1 functionality */,
  {(uint16)465, (uint8)3, (uint16)397}
  /* eQADC_B_MAB1 functionality */,
  {(uint16)465, (uint8)4, (uint16)398}
  /* Settings information for pad 466 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC25_IN functionality */,
  {(uint16)466, (uint8)1, (uint16)399}
  /* DSPI_D_PCSD3 functionality */,
  {(uint16)466, (uint8)2, (uint16)400}
  /* eQADC_A_MAA2 functionality */,
  {(uint16)466, (uint8)3, (uint16)401}
  /* eQADC_B_MAB2 functionality */,
  {(uint16)466, (uint8)4, (uint16)402}
  /* Settings information for pad 467 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC26_IN functionality */,
  {(uint16)467, (uint8)1, (uint16)403}
  /* DSPI_D_PCSD2 functionality */,
  {(uint16)467, (uint8)2, (uint16)404}
  /* eQADC_B_MAB0 functionality */,
  {(uint16)467, (uint8)3, (uint16)405}
  /* Settings information for pad 468 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC27_IN functionality */,
  {(uint16)468, (uint8)1, (uint16)406}
  /* DSPI_D_PCSD1 functionality */,
  {(uint16)468, (uint8)2, (uint16)407}
  /* REACM_RCH5_C_OUT functionality */,
  {(uint16)468, (uint8)3, (uint16)408}
  /* eQADC_B_MAB1 functionality */,
  {(uint16)468, (uint8)4, (uint16)409}
  /* Settings information for pad 469 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC28_IN functionality */,
  {(uint16)469, (uint8)1, (uint16)410}
  /* DSPI_D_PCSD0_OUT functionality */,
  {(uint16)469, (uint8)2, (uint16)411}
  /* REACM_RCH6_C_OUT functionality */,
  {(uint16)469, (uint8)3, (uint16)412}
  /* eQADC_B_MAB2 functionality */,
  {(uint16)469, (uint8)4, (uint16)413}
  /* DSPI_D_PCSD0_IN functionality */,
  {(uint16)469, (uint8)6, (uint16)112}
  /* Settings information for pad 470 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC29_IN functionality */,
  {(uint16)470, (uint8)1, (uint16)414}
  /* DSPI_D_SCKD_OUT functionality */,
  {(uint16)470, (uint8)2, (uint16)415}
  /* REACM_RCH7_C_OUT functionality */,
  {(uint16)470, (uint8)3, (uint16)416}
  /* DSPI_D_SCKD_IN functionality */,
  {(uint16)470, (uint8)6, (uint16)113}
  /* Settings information for pad 471 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC30_IN functionality */,
  {(uint16)471, (uint8)1, (uint16)417}
  /* DSPI_D_SOUTD functionality */,
  {(uint16)471, (uint8)2, (uint16)418}
  /* REACM_RCH8_C_OUT functionality */,
  {(uint16)471, (uint8)3, (uint16)419}
  /* Settings information for pad 472 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC31_IN functionality */,
  {(uint16)472, (uint8)1, (uint16)420}
  /* REACM_RCH9_C_OUT functionality */,
  {(uint16)472, (uint8)3, (uint16)421}
  /* DSPI_D_SIND_IN functionality */,
  {(uint16)472, (uint8)6, (uint16)114}
  /* Settings information for pad 473 {PCR, Mode, Index to Mux or Inmux table} */
  /* Settings information for pad 474 {PCR, Mode, Index to Mux or Inmux table} */
  /* FEC_FEC_TXCLK_REFCLK_IN functionality */,
  {(uint16)474, (uint8)1, (uint16)422}
  /* SENT_B_SENT0_B_IN functionality */,
  {(uint16)474, (uint8)6, (uint16)115}
  /* Settings information for pad 475 {PCR, Mode, Index to Mux or Inmux table} */
  /* SENT_A_SENT2_A_IN functionality */,
  {(uint16)475, (uint8)5, (uint16)116}
  /* Settings information for pad 476 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA31_IN functionality */,
  {(uint16)476, (uint8)6, (uint16)117}
  /* eMIOS_A_EMIOS16_IN functionality */,
  {(uint16)476, (uint8)7, (uint16)118}
  /* Settings information for pad 477 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA30_IN functionality */,
  {(uint16)477, (uint8)6, (uint16)119}
  /* eMIOS_A_EMIOS17_IN functionality */,
  {(uint16)477, (uint8)7, (uint16)120}
  /* Settings information for pad 478 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA29_IN functionality */,
  {(uint16)478, (uint8)6, (uint16)121}
  /* eMIOS_A_EMIOS18_IN functionality */,
  {(uint16)478, (uint8)7, (uint16)122}
  /* Settings information for pad 479 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA28_IN functionality */,
  {(uint16)479, (uint8)6, (uint16)123}
  /* eMIOS_A_EMIOS19_IN functionality */,
  {(uint16)479, (uint8)7, (uint16)124}
  /* Settings information for pad 480 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA27_IN functionality */,
  {(uint16)480, (uint8)6, (uint16)125}
  /* eMIOS_A_EMIOS20_IN functionality */,
  {(uint16)480, (uint8)7, (uint16)126}
  /* Settings information for pad 481 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA26_IN functionality */,
  {(uint16)481, (uint8)6, (uint16)127}
  /* eMIOS_A_EMIOS21_IN functionality */,
  {(uint16)481, (uint8)7, (uint16)128}
  /* Settings information for pad 482 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA25_IN functionality */,
  {(uint16)482, (uint8)6, (uint16)129}
  /* eMIOS_A_EMIOS22_IN functionality */,
  {(uint16)482, (uint8)7, (uint16)130}
  /* Settings information for pad 483 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_A_ETPUA24_IN functionality */,
  {(uint16)483, (uint8)6, (uint16)131}
  /* eMIOS_A_EMIOS23_IN functionality */,
  {(uint16)483, (uint8)7, (uint16)132}
  /* Settings information for pad 484 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC15_IN functionality */,
  {(uint16)484, (uint8)6, (uint16)133}
  /* eMIOS_B_EMIOS16_IN functionality */,
  {(uint16)484, (uint8)7, (uint16)134}
  /* Settings information for pad 485 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC14_IN functionality */,
  {(uint16)485, (uint8)6, (uint16)135}
  /* eMIOS_B_EMIOS17_IN functionality */,
  {(uint16)485, (uint8)7, (uint16)136}
  /* Settings information for pad 486 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC13_IN functionality */,
  {(uint16)486, (uint8)6, (uint16)137}
  /* eMIOS_B_EMIOS18_IN functionality */,
  {(uint16)486, (uint8)7, (uint16)138}
  /* Settings information for pad 487 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC12_IN functionality */,
  {(uint16)487, (uint8)6, (uint16)139}
  /* eMIOS_B_EMIOS19_IN functionality */,
  {(uint16)487, (uint8)7, (uint16)140}
  /* Settings information for pad 488 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC11_IN functionality */,
  {(uint16)488, (uint8)6, (uint16)141}
  /* eMIOS_B_EMIOS20_IN functionality */,
  {(uint16)488, (uint8)7, (uint16)142}
  /* Settings information for pad 489 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC10_IN functionality */,
  {(uint16)489, (uint8)6, (uint16)143}
  /* eMIOS_B_EMIOS21_IN functionality */,
  {(uint16)489, (uint8)7, (uint16)144}
  /* Settings information for pad 490 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC9_IN functionality */,
  {(uint16)490, (uint8)6, (uint16)145}
  /* eMIOS_B_EMIOS22_IN functionality */,
  {(uint16)490, (uint8)7, (uint16)146}
  /* Settings information for pad 491 {PCR, Mode, Index to Mux or Inmux table} */
  /* eTPU_C_ETPUC8_IN functionality */,
  {(uint16)491, (uint8)6, (uint16)147}
  /* eMIOS_B_EMIOS23_IN functionality */,
  {(uint16)491, (uint8)7, (uint16)148}

};

#endif

#define PORT_STOP_SEC_CONFIG_DATA_UNSPECIFIED
/**
* @violates @ref PORT_PBCFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_PBCFG_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#define PORT_START_SEC_CONFIG_DATA_16
/**
* @violates @ref PORT_PBCFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_PBCFG_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

#if (STD_ON == PORT_SET_PIN_MODE_API)

/** @brief Port Pin description data */
CONST (uint16, PORT_CONST) Port_au16PinDescription[10][31] =
{


/*  Mode PORT_GPIO_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads  64 ...  79 : PORT75_GPIO | 
PORT76_GPIO | 
PORT77_GPIO | 
PORT78_GPIO | 
PORT79_GPIO */
  (uint16)( SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads  80 ...  95 : PORT80_GPIO | 
PORT81_GPIO | 
PORT82_GPIO | 
PORT83_GPIO | 
PORT84_GPIO | 
PORT85_GPIO | 
PORT86_GPIO | 
PORT87_GPIO | 
PORT88_GPIO | 
PORT89_GPIO | 
PORT90_GPIO | 
PORT91_GPIO | 
PORT92_GPIO | 
PORT93_GPIO | 
PORT94_GPIO | 
PORT95_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads  96 ... 111 : PORT96_GPIO | 
PORT97_GPIO | 
PORT98_GPIO | 
PORT99_GPIO | 
PORT100_GPIO | 
PORT101_GPIO | 
PORT102_GPIO | 
PORT103_GPIO | 
PORT104_GPIO | 
PORT105_GPIO | 
PORT106_GPIO | 
PORT107_GPIO | 
PORT108_GPIO | 
PORT109_GPIO | 
PORT110_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14)
          ),
/* Pads 112 ... 127 : PORT113_GPIO | 
PORT114_GPIO | 
PORT115_GPIO | 
PORT116_GPIO | 
PORT117_GPIO | 
PORT118_GPIO | 
PORT119_GPIO | 
PORT120_GPIO | 
PORT121_GPIO | 
PORT122_GPIO | 
PORT123_GPIO | 
PORT124_GPIO | 
PORT125_GPIO | 
PORT126_GPIO | 
PORT127_GPIO */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 128 ... 143 : PORT128_GPIO | 
PORT129_GPIO | 
PORT130_GPIO | 
PORT131_GPIO | 
PORT132_GPIO | 
PORT133_GPIO | 
PORT134_GPIO | 
PORT135_GPIO | 
PORT136_GPIO | 
PORT137_GPIO | 
PORT138_GPIO | 
PORT139_GPIO | 
PORT140_GPIO | 
PORT141_GPIO | 
PORT142_GPIO | 
PORT143_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 144 ... 159 : PORT144_GPIO | 
PORT145_GPIO | 
PORT146_GPIO | 
PORT147_GPIO | 
PORT148_GPIO | 
PORT149_GPIO | 
PORT150_GPIO | 
PORT151_GPIO | 
PORT152_GPIO | 
PORT153_GPIO | 
PORT154_GPIO | 
PORT155_GPIO | 
PORT156_GPIO | 
PORT157_GPIO | 
PORT158_GPIO | 
PORT159_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 160 ... 175 : PORT160_GPIO | 
PORT161_GPIO | 
PORT162_GPIO | 
PORT163_GPIO | 
PORT164_GPIO | 
PORT165_GPIO | 
PORT166_GPIO | 
PORT167_GPIO | 
PORT168_GPIO | 
PORT169_GPIO | 
PORT170_GPIO | 
PORT171_GPIO | 
PORT172_GPIO | 
PORT173_GPIO | 
PORT174_GPIO | 
PORT175_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 176 ... 191 : PORT176_GPIO | 
PORT177_GPIO | 
PORT178_GPIO | 
PORT179_GPIO | 
PORT180_GPIO | 
PORT181_GPIO | 
PORT182_GPIO | 
PORT183_GPIO | 
PORT184_GPIO | 
PORT185_GPIO | 
PORT186_GPIO | 
PORT187_GPIO | 
PORT188_GPIO | 
PORT189_GPIO | 
PORT190_GPIO | 
PORT191_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 192 ... 207 : PORT192_GPIO | 
PORT193_GPIO | 
PORT194_GPIO | 
PORT195_GPIO | 
PORT196_GPIO | 
PORT197_GPIO | 
PORT198_GPIO | 
PORT199_GPIO | 
PORT200_GPIO | 
PORT201_GPIO | 
PORT202_GPIO | 
PORT203_GPIO | 
PORT204_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12)
          ),
/* Pads 208 ... 223 : PORT208_GPIO | 
PORT209_GPIO | 
PORT210_GPIO | 
PORT212_GPIO | 
PORT213_GPIO | 
PORT214_GPIO | 
PORT219_GPIO | 
PORT220_GPIO | 
PORT221_GPIO | 
PORT222_GPIO | 
PORT223_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 224 ... 239 : PORT224_GPIO | 
PORT225_GPIO | 
PORT226_GPIO | 
PORT227_GPIO | 
PORT228_GPIO | 
PORT229_GPIO | 
PORT230_GPIO | 
PORT231_GPIO | 
PORT232_GPIO | 
PORT233_GPIO | 
PORT234_GPIO | 
PORT235_GPIO | 
PORT236_GPIO | 
PORT237_GPIO | 
PORT238_GPIO | 
PORT239_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 240 ... 255 : PORT240_GPIO | 
PORT241_GPIO | 
PORT242_GPIO | 
PORT243_GPIO | 
PORT244_GPIO | 
PORT245_GPIO | 
PORT246_GPIO | 
PORT247_GPIO | 
PORT248_GPIO | 
PORT249_GPIO | 
PORT250_GPIO | 
PORT251_GPIO | 
PORT252_GPIO | 
PORT253_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 : PORT432_GPIO | 
PORT433_GPIO | 
PORT434_GPIO | 
PORT435_GPIO | 
PORT436_GPIO | 
PORT437_GPIO | 
PORT440_GPI | 
PORT441_GPI | 
PORT442_GPI | 
PORT443_GPIO | 
PORT444_GPI | 
PORT445_GPIO | 
PORT446_GPIO | 
PORT447_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 448 ... 463 : PORT448_GPIO | 
PORT449_GPIO | 
PORT450_GPI | 
PORT451_GPIO | 
PORT452_GPIO | 
PORT453_GPIO | 
PORT454_GPIO | 
PORT455_GPIO | 
PORT456_GPIO | 
PORT457_GPIO | 
PORT458_GPIO | 
PORT459_GPIO | 
PORT460_GPIO | 
PORT461_GPIO | 
PORT462_GPIO | 
PORT463_GPIO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 464 ... 479 : PORT464_GPIO | 
PORT465_GPIO | 
PORT466_GPIO | 
PORT467_GPIO | 
PORT468_GPIO | 
PORT469_GPIO | 
PORT470_GPIO | 
PORT471_GPIO | 
PORT472_GPIO | 
PORT474_GPI | 
PORT475_GPI | 
PORT476_GPI | 
PORT477_GPI | 
PORT478_GPI | 
PORT479_GPI */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 480 ... 495 : PORT480_GPI | 
PORT481_GPI | 
PORT482_GPI | 
PORT483_GPI | 
PORT484_GPI | 
PORT485_GPI | 
PORT486_GPI | 
PORT487_GPI | 
PORT488_GPI | 
PORT489_GPI | 
PORT490_GPI | 
PORT491_GPI */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11)
          )
}
,
/*  Mode PORT_ALT1_FUNC_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads  80 ...  95 : PORT83_FlexCAN_A_CNTXA | 
PORT84_FlexCAN_A_CNRXA | 
PORT85_FlexCAN_B_CNTXB | 
PORT86_FlexCAN_B_CNRXB | 
PORT87_FlexCAN_C_CNTXC | 
PORT88_FlexCAN_C_CNRXC | 
PORT93_DSPI_A_SCKA_OUT | 
PORT93_DSPI_A_SCKA_IN | 
PORT93_DSPI_A_SCKA_INOUT | 
PORT94_DSPI_A_SINA | 
PORT95_DSPI_A_SOUTA */
  (uint16)( SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads  96 ... 111 : PORT96_DSPI_A_PCSA0_OUT | 
PORT96_DSPI_A_PCSA0_IN | 
PORT96_DSPI_A_PCSA0_INOUT | 
PORT97_DSPI_A_PCSA1 | 
PORT98_DSPI_A_PCSA2 | 
PORT99_DSPI_A_PCSA3 | 
PORT100_DSPI_A_PCSA4 | 
PORT101_DSPI_A_PCSA5 | 
PORT102_DSPI_B_SCKB_INOUT | 
PORT102_DSPI_B_SCKB_OUT | 
PORT102_DSPI_B_SCKB_IN | 
PORT103_DSPI_B_SINB | 
PORT104_DSPI_B_SOUTB | 
PORT105_DSPI_B_PCSB0_OUT | 
PORT106_DSPI_B_PCSB1 | 
PORT107_DSPI_B_PCSB2 | 
PORT108_DSPI_B_PCSB3 | 
PORT109_DSPI_B_PCSB4 | 
PORT110_DSPI_B_PCSB5 */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14)
          ),
/* Pads 112 ... 127 : PORT113_eTPU_A_TCRCLKA | 
PORT114_eTPU_A_ETPUA0_INOUT | 
PORT114_eTPU_A_ETPUA0_OUT | 
PORT114_eTPU_A_ETPUA0_IN | 
PORT115_eTPU_A_ETPUA1_INOUT | 
PORT115_eTPU_A_ETPUA1_OUT | 
PORT115_eTPU_A_ETPUA1_IN | 
PORT116_eTPU_A_ETPUA2_INOUT | 
PORT116_eTPU_A_ETPUA2_OUT | 
PORT116_eTPU_A_ETPUA2_IN | 
PORT117_eTPU_A_ETPUA3_INOUT | 
PORT117_eTPU_A_ETPUA3_OUT | 
PORT117_eTPU_A_ETPUA3_IN | 
PORT118_eTPU_A_ETPUA4_INOUT | 
PORT118_eTPU_A_ETPUA4_OUT | 
PORT118_eTPU_A_ETPUA4_IN | 
PORT119_eTPU_A_ETPUA5_INOUT | 
PORT119_eTPU_A_ETPUA5_OUT | 
PORT119_eTPU_A_ETPUA5_IN | 
PORT120_eTPU_A_ETPUA6_INOUT | 
PORT120_eTPU_A_ETPUA6_OUT | 
PORT120_eTPU_A_ETPUA6_IN | 
PORT121_eTPU_A_ETPUA7_INOUT | 
PORT121_eTPU_A_ETPUA7_OUT | 
PORT121_eTPU_A_ETPUA7_IN | 
PORT122_eTPU_A_ETPUA8_INOUT | 
PORT122_eTPU_A_ETPUA8_OUT | 
PORT122_eTPU_A_ETPUA8_IN | 
PORT123_eTPU_A_ETPUA9_INOUT | 
PORT123_eTPU_A_ETPUA9_OUT | 
PORT123_eTPU_A_ETPUA9_IN | 
PORT124_eTPU_A_ETPUA10_INOUT | 
PORT124_eTPU_A_ETPUA10_OUT | 
PORT124_eTPU_A_ETPUA10_IN | 
PORT125_eTPU_A_ETPUA11_INOUT | 
PORT125_eTPU_A_ETPUA11_OUT | 
PORT125_eTPU_A_ETPUA11_IN | 
PORT126_eTPU_A_ETPUA12_INOUT | 
PORT126_eTPU_A_ETPUA12_OUT | 
PORT126_eTPU_A_ETPUA12_IN | 
PORT127_eTPU_A_ETPUA13_INOUT | 
PORT127_eTPU_A_ETPUA13_OUT | 
PORT127_eTPU_A_ETPUA13_IN */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15)
          ),
/* Pads 128 ... 143 : PORT128_eTPU_A_ETPUA14_INOUT | 
PORT128_eTPU_A_ETPUA14_OUT | 
PORT128_eTPU_A_ETPUA14_IN | 
PORT129_eTPU_A_ETPUA15_INOUT | 
PORT129_eTPU_A_ETPUA15_OUT | 
PORT129_eTPU_A_ETPUA15_IN | 
PORT130_eTPU_A_ETPUA16_INOUT | 
PORT130_eTPU_A_ETPUA16_OUT | 
PORT130_eTPU_A_ETPUA16_IN | 
PORT131_eTPU_A_ETPUA17_INOUT | 
PORT131_eTPU_A_ETPUA17_OUT | 
PORT131_eTPU_A_ETPUA17_IN | 
PORT132_eTPU_A_ETPUA18_INOUT | 
PORT132_eTPU_A_ETPUA18_OUT | 
PORT132_eTPU_A_ETPUA18_IN | 
PORT133_eTPU_A_ETPUA19_INOUT | 
PORT133_eTPU_A_ETPUA19_OUT | 
PORT133_eTPU_A_ETPUA19_IN | 
PORT134_eTPU_A_ETPUA20_INOUT | 
PORT134_eTPU_A_ETPUA20_OUT | 
PORT134_eTPU_A_ETPUA20_IN | 
PORT135_eTPU_A_ETPUA21_INOUT | 
PORT135_eTPU_A_ETPUA21_OUT | 
PORT135_eTPU_A_ETPUA21_IN | 
PORT136_eTPU_A_ETPUA22_INOUT | 
PORT136_eTPU_A_ETPUA22_OUT | 
PORT136_eTPU_A_ETPUA22_IN | 
PORT137_eTPU_A_ETPUA23_INOUT | 
PORT137_eTPU_A_ETPUA23_OUT | 
PORT137_eTPU_A_ETPUA23_IN | 
PORT138_eTPU_A_ETPUA24_OUT | 
PORT139_eTPU_A_ETPUA25_OUT | 
PORT140_eTPU_A_ETPUA26_OUT | 
PORT141_eTPU_A_ETPUA27_OUT | 
PORT142_eTPU_A_ETPUA28_OUT | 
PORT143_eTPU_A_ETPUA29_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 144 ... 159 : PORT144_eTPU_A_ETPUA30_OUT | 
PORT145_eTPU_A_ETPUA31_OUT | 
PORT146_eTPU_B_TCRCLKB | 
PORT147_eTPU_B_ETPUB0_INOUT | 
PORT147_eTPU_B_ETPUB0_OUT | 
PORT147_eTPU_B_ETPUB0_IN | 
PORT148_eTPU_B_ETPUB1_INOUT | 
PORT148_eTPU_B_ETPUB1_OUT | 
PORT148_eTPU_B_ETPUB1_IN | 
PORT149_eTPU_B_ETPUB2_INOUT | 
PORT149_eTPU_B_ETPUB2_OUT | 
PORT149_eTPU_B_ETPUB2_IN | 
PORT150_eTPU_B_ETPUB3_INOUT | 
PORT150_eTPU_B_ETPUB3_OUT | 
PORT150_eTPU_B_ETPUB3_IN | 
PORT151_eTPU_B_ETPUB4_INOUT | 
PORT151_eTPU_B_ETPUB4_OUT | 
PORT151_eTPU_B_ETPUB4_IN | 
PORT152_eTPU_B_ETPUB5_INOUT | 
PORT152_eTPU_B_ETPUB5_OUT | 
PORT152_eTPU_B_ETPUB5_IN | 
PORT153_eTPU_B_ETPUB6_INOUT | 
PORT153_eTPU_B_ETPUB6_OUT | 
PORT153_eTPU_B_ETPUB6_IN | 
PORT154_eTPU_B_ETPUB7_INOUT | 
PORT154_eTPU_B_ETPUB7_OUT | 
PORT154_eTPU_B_ETPUB7_IN | 
PORT155_eTPU_B_ETPUB8_INOUT | 
PORT155_eTPU_B_ETPUB8_OUT | 
PORT155_eTPU_B_ETPUB8_IN | 
PORT156_eTPU_B_ETPUB9_INOUT | 
PORT156_eTPU_B_ETPUB9_OUT | 
PORT156_eTPU_B_ETPUB9_IN | 
PORT157_eTPU_B_ETPUB10_INOUT | 
PORT157_eTPU_B_ETPUB10_OUT | 
PORT157_eTPU_B_ETPUB10_IN | 
PORT158_eTPU_B_ETPUB11_INOUT | 
PORT158_eTPU_B_ETPUB11_OUT | 
PORT158_eTPU_B_ETPUB11_IN | 
PORT159_eTPU_B_ETPUB12_INOUT | 
PORT159_eTPU_B_ETPUB12_OUT | 
PORT159_eTPU_B_ETPUB12_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15)
          ),
/* Pads 160 ... 175 : PORT160_eTPU_B_ETPUB13_INOUT | 
PORT160_eTPU_B_ETPUB13_OUT | 
PORT160_eTPU_B_ETPUB13_IN | 
PORT161_eTPU_B_ETPUB14_INOUT | 
PORT161_eTPU_B_ETPUB14_OUT | 
PORT161_eTPU_B_ETPUB14_IN | 
PORT162_eTPU_B_ETPUB15_INOUT | 
PORT162_eTPU_B_ETPUB15_OUT | 
PORT162_eTPU_B_ETPUB15_IN | 
PORT163_eTPU_B_ETPUB16_INOUT | 
PORT163_eTPU_B_ETPUB16_OUT | 
PORT163_eTPU_B_ETPUB16_IN | 
PORT164_eTPU_B_ETPUB17_INOUT | 
PORT164_eTPU_B_ETPUB17_OUT | 
PORT164_eTPU_B_ETPUB17_IN | 
PORT165_eTPU_B_ETPUB18_INOUT | 
PORT165_eTPU_B_ETPUB18_OUT | 
PORT165_eTPU_B_ETPUB18_IN | 
PORT166_eTPU_B_ETPUB19_INOUT | 
PORT166_eTPU_B_ETPUB19_OUT | 
PORT166_eTPU_B_ETPUB19_IN | 
PORT167_eTPU_B_ETPUB20_INOUT | 
PORT167_eTPU_B_ETPUB20_OUT | 
PORT167_eTPU_B_ETPUB20_IN | 
PORT168_eTPU_B_ETPUB21_INOUT | 
PORT168_eTPU_B_ETPUB21_OUT | 
PORT168_eTPU_B_ETPUB21_IN | 
PORT169_eTPU_B_ETPUB22_INOUT | 
PORT169_eTPU_B_ETPUB22_OUT | 
PORT169_eTPU_B_ETPUB22_IN | 
PORT170_eTPU_B_ETPUB23_INOUT | 
PORT170_eTPU_B_ETPUB23_OUT | 
PORT170_eTPU_B_ETPUB23_IN | 
PORT171_eTPU_B_ETPUB24_INOUT | 
PORT171_eTPU_B_ETPUB24_OUT | 
PORT171_eTPU_B_ETPUB24_IN | 
PORT172_eTPU_B_ETPUB25_INOUT | 
PORT172_eTPU_B_ETPUB25_OUT | 
PORT172_eTPU_B_ETPUB25_IN | 
PORT173_eTPU_B_ETPUB26_INOUT | 
PORT173_eTPU_B_ETPUB26_OUT | 
PORT173_eTPU_B_ETPUB26_IN | 
PORT174_eTPU_B_ETPUB27_INOUT | 
PORT174_eTPU_B_ETPUB27_OUT | 
PORT174_eTPU_B_ETPUB27_IN | 
PORT175_eTPU_B_ETPUB28_INOUT | 
PORT175_eTPU_B_ETPUB28_OUT | 
PORT175_eTPU_B_ETPUB28_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15)
          ),
/* Pads 176 ... 191 : PORT176_eTPU_B_ETPUB29_INOUT | 
PORT176_eTPU_B_ETPUB29_OUT | 
PORT176_eTPU_B_ETPUB29_IN | 
PORT177_eTPU_B_ETPUB30_INOUT | 
PORT177_eTPU_B_ETPUB30_OUT | 
PORT177_eTPU_B_ETPUB30_IN | 
PORT178_eTPU_B_ETPUB31_INOUT | 
PORT178_eTPU_B_ETPUB31_OUT | 
PORT178_eTPU_B_ETPUB31_IN | 
PORT179_eMIOS_A_EMIOS0_INOUT | 
PORT179_eMIOS_A_EMIOS0_OUT | 
PORT179_eMIOS_A_EMIOS0_IN | 
PORT180_eMIOS_A_EMIOS1_INOUT | 
PORT180_eMIOS_A_EMIOS1_OUT | 
PORT180_eMIOS_A_EMIOS1_IN | 
PORT181_eMIOS_A_EMIOS2_INOUT | 
PORT181_eMIOS_A_EMIOS2_OUT | 
PORT181_eMIOS_A_EMIOS2_IN | 
PORT182_eMIOS_A_EMIOS3_INOUT | 
PORT182_eMIOS_A_EMIOS3_OUT | 
PORT182_eMIOS_A_EMIOS3_IN | 
PORT183_eMIOS_A_EMIOS4 | 
PORT184_eMIOS_A_EMIOS5 | 
PORT185_eMIOS_A_EMIOS6_INOUT | 
PORT185_eMIOS_A_EMIOS6_OUT | 
PORT185_eMIOS_A_EMIOS6_IN | 
PORT186_eMIOS_A_EMIOS7_INOUT | 
PORT186_eMIOS_A_EMIOS7_OUT | 
PORT186_eMIOS_A_EMIOS7_IN | 
PORT187_eMIOS_B_EMIOS0_INOUT | 
PORT187_eMIOS_B_EMIOS0_OUT | 
PORT187_eMIOS_B_EMIOS0_IN | 
PORT188_eMIOS_B_EMIOS1_INOUT | 
PORT188_eMIOS_B_EMIOS1_OUT | 
PORT188_eMIOS_B_EMIOS1_IN | 
PORT189_eMIOS_B_EMIOS2_INOUT | 
PORT189_eMIOS_B_EMIOS2_OUT | 
PORT189_eMIOS_B_EMIOS2_IN | 
PORT190_eMIOS_B_EMIOS3_INOUT | 
PORT190_eMIOS_B_EMIOS3_OUT | 
PORT190_eMIOS_B_EMIOS3_IN | 
PORT191_eMIOS_B_EMIOS4_INOUT | 
PORT191_eMIOS_B_EMIOS4_OUT | 
PORT191_eMIOS_B_EMIOS4_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15)
          ),
/* Pads 192 ... 207 : PORT192_eMIOS_B_EMIOS5_INOUT | 
PORT192_eMIOS_B_EMIOS5_OUT | 
PORT192_eMIOS_B_EMIOS5_IN | 
PORT193_eMIOS_B_EMIOS6 | 
PORT194_eMIOS_B_EMIOS7 | 
PORT195_eMIOS_A_EMIOS16_OUT | 
PORT196_eMIOS_A_EMIOS17_OUT | 
PORT197_eMIOS_A_EMIOS18_OUT | 
PORT198_eMIOS_A_EMIOS19_OUT | 
PORT199_eMIOS_A_EMIOS20_OUT | 
PORT200_eMIOS_A_EMIOS21_OUT | 
PORT201_eMIOS_A_EMIOS22_OUT | 
PORT202_eMIOS_A_EMIOS23_OUT | 
PORT203_eMIOS_B_EMIOS16_OUT | 
PORT204_eMIOS_B_EMIOS17_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12)
          ),
/* Pads 208 ... 223 : PORT208_SoC_PLLCFG0_IN | 
PORT209_SoC_PLLCFG1_IN | 
PORT210_SoC_PLLCFG2_IN | 
PORT212_SoC_BOOTCFG1_IN | 
PORT213_SoC_WKPCFG_IN | 
PORT214_ENGCLK | 
PORT219_MCKO */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(11)
          ),
/* Pads 224 ... 239 : PORT224_MSEO0 | 
PORT225_MSEO1 | 
PORT226_RDY | 
PORT227_EVTO | 
PORT228_TDO | 
PORT229_D_CLKOUT | 
PORT230_RSTOUT | 
PORT235_DSPI_C_SCKC_OUT | 
PORT237_DSPI_C_SOUTC | 
PORT238_DSPI_C_PCSC0_OUT | 
PORT239_DSPI_C_PCSC1 */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 240 ... 255 : PORT240_DSPI_C_PCSC2 | 
PORT241_DSPI_C_PCSC3 | 
PORT242_DSPI_C_PCSC4 | 
PORT243_DSPI_C_PCSC5 | 
PORT244_eSCI_C_TXDC | 
PORT245_eSCI_C_RXDC_IN | 
PORT246_FlexCAN_D_CNTXD | 
PORT248_FEC_FEC_TXD0_OUT | 
PORT249_FEC_FEC_RX_DV_IN | 
PORT250_FEC_FEC_RXD0_IN | 
PORT251_FEC_FEC_TXD1_OUT | 
PORT252_FEC_FEC_TXEN_OUT | 
PORT253_FEC_FEC_RXD1_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 : PORT432_eMIOS_B_EMIOS18_OUT | 
PORT433_eMIOS_B_EMIOS19_OUT | 
PORT434_eMIOS_B_EMIOS20_OUT | 
PORT435_eMIOS_B_EMIOS21_OUT | 
PORT436_eMIOS_B_EMIOS22_OUT | 
PORT437_eMIOS_B_EMIOS23_OUT | 
PORT443_eTPU_C_ETPUC2_INOUT | 
PORT443_eTPU_C_ETPUC2_OUT | 
PORT443_eTPU_C_ETPUC2_IN | 
PORT445_eTPU_C_ETPUC4_INOUT | 
PORT445_eTPU_C_ETPUC4_OUT | 
PORT445_eTPU_C_ETPUC4_IN | 
PORT446_eTPU_C_ETPUC5_INOUT | 
PORT446_eTPU_C_ETPUC5_OUT | 
PORT446_eTPU_C_ETPUC5_IN | 
PORT447_eTPU_C_ETPUC6_INOUT | 
PORT447_eTPU_C_ETPUC6_OUT | 
PORT447_eTPU_C_ETPUC6_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15)
          ),
/* Pads 448 ... 463 : PORT448_eTPU_C_ETPUC7_INOUT | 
PORT448_eTPU_C_ETPUC7_OUT | 
PORT448_eTPU_C_ETPUC7_IN | 
PORT449_eTPU_C_ETPUC8_OUT | 
PORT451_eTPU_C_ETPUC10_OUT | 
PORT452_eTPU_C_ETPUC11_OUT | 
PORT453_eTPU_C_ETPUC12_OUT | 
PORT454_eTPU_C_ETPUC13_OUT | 
PORT455_eTPU_C_ETPUC14_OUT | 
PORT456_eTPU_C_ETPUC15_OUT | 
PORT457_eTPU_C_ETPUC16_INOUT | 
PORT457_eTPU_C_ETPUC16_OUT | 
PORT457_eTPU_C_ETPUC16_IN | 
PORT458_eTPU_C_ETPUC17_INOUT | 
PORT458_eTPU_C_ETPUC17_OUT | 
PORT458_eTPU_C_ETPUC17_IN | 
PORT459_eTPU_C_ETPUC18_INOUT | 
PORT459_eTPU_C_ETPUC18_OUT | 
PORT459_eTPU_C_ETPUC18_IN | 
PORT460_eTPU_C_ETPUC19_INOUT | 
PORT460_eTPU_C_ETPUC19_OUT | 
PORT460_eTPU_C_ETPUC19_IN | 
PORT461_eTPU_C_ETPUC20_INOUT | 
PORT461_eTPU_C_ETPUC20_OUT | 
PORT461_eTPU_C_ETPUC20_IN | 
PORT462_eTPU_C_ETPUC21_INOUT | 
PORT462_eTPU_C_ETPUC21_OUT | 
PORT462_eTPU_C_ETPUC21_IN | 
PORT463_eTPU_C_ETPUC22_INOUT | 
PORT463_eTPU_C_ETPUC22_OUT | 
PORT463_eTPU_C_ETPUC22_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15)
          ),
/* Pads 464 ... 479 : PORT464_eTPU_C_ETPUC23_INOUT | 
PORT464_eTPU_C_ETPUC23_OUT | 
PORT464_eTPU_C_ETPUC23_IN | 
PORT465_eTPU_C_ETPUC24_INOUT | 
PORT465_eTPU_C_ETPUC24_OUT | 
PORT465_eTPU_C_ETPUC24_IN | 
PORT466_eTPU_C_ETPUC25_INOUT | 
PORT466_eTPU_C_ETPUC25_OUT | 
PORT466_eTPU_C_ETPUC25_IN | 
PORT467_eTPU_C_ETPUC26_INOUT | 
PORT467_eTPU_C_ETPUC26_OUT | 
PORT467_eTPU_C_ETPUC26_IN | 
PORT468_eTPU_C_ETPUC27_INOUT | 
PORT468_eTPU_C_ETPUC27_OUT | 
PORT468_eTPU_C_ETPUC27_IN | 
PORT469_eTPU_C_ETPUC28_INOUT | 
PORT469_eTPU_C_ETPUC28_OUT | 
PORT469_eTPU_C_ETPUC28_IN | 
PORT470_eTPU_C_ETPUC29_INOUT | 
PORT470_eTPU_C_ETPUC29_OUT | 
PORT470_eTPU_C_ETPUC29_IN | 
PORT471_eTPU_C_ETPUC30_INOUT | 
PORT471_eTPU_C_ETPUC30_OUT | 
PORT471_eTPU_C_ETPUC30_IN | 
PORT472_eTPU_C_ETPUC31_INOUT | 
PORT472_eTPU_C_ETPUC31_OUT | 
PORT472_eTPU_C_ETPUC31_IN | 
PORT474_FEC_FEC_TXCLK_REFCLK_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(10)
          ),
/* Pads 480 ... 495 */
  (uint16)0x0000
}
,
/*  Mode PORT_ALT2_FUNC_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads  80 ...  95 : PORT85_DSPI_C_PCSC3 | 
PORT86_DSPI_C_PCSC4 | 
PORT87_DSPI_D_PCSD3 | 
PORT88_DSPI_D_PCSD4 | 
PORT91_DSPI_D_PCSD1 | 
PORT92_DSPI_D_PCSD5 | 
PORT93_DSPI_C_PCSC1 | 
PORT94_DSPI_C_PCSC2 | 
PORT95_DSPI_C_PCSC5 */
  (uint16)( SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads  96 ... 111 : PORT96_DSPI_D_PCSD2 | 
PORT97_DSPI_E_PCSE0_OUT | 
PORT97_DSPI_E_PCSE0_IN | 
PORT97_DSPI_E_PCSE0_INOUT | 
PORT98_DSPI_E_SOUTE | 
PORT99_DSPI_E_SINE | 
PORT100_DSPI_E_SCKE_OUT | 
PORT100_DSPI_E_SCKE_IN | 
PORT100_DSPI_E_SCKE_INOUT | 
PORT101_eQADC_A_eQADC_B_ETRIG1 | 
PORT105_DSPI_D_PCSD2 | 
PORT106_DSPI_D_PCSD0_OUT | 
PORT107_DSPI_C_SOUTC | 
PORT109_DSPI_C_SCKC_OUT | 
PORT110_DSPI_C_PCSC0_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14)
          ),
/* Pads 112 ... 127 : PORT113_SIU_A_IRQ7 | 
PORT114_eTPU_A_ETPUA12 | 
PORT115_eTPU_A_ETPUA13 | 
PORT116_eTPU_A_ETPUA14 | 
PORT117_eTPU_A_ETPUA15 | 
PORT118_eTPU_A_ETPUA16 | 
PORT119_eTPU_A_ETPUA17 | 
PORT120_eTPU_A_ETPUA18 | 
PORT121_eTPU_A_ETPUA19 | 
PORT122_eTPU_A_ETPUA20 | 
PORT123_eTPU_A_ETPUA21 | 
PORT124_eTPU_A_ETPUA22 | 
PORT125_eTPU_A_ETPUA23 | 
PORT126_DSPI_B_PCSB1 | 
PORT127_DSPI_B_PCSB3 */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 128 ... 143 : PORT128_DSPI_B_PCSB4 | 
PORT129_DSPI_B_PCSB5 | 
PORT130_DSPI_D_PCSD1 | 
PORT131_DSPI_D_PCSD2 | 
PORT132_DSPI_D_PCSD3 | 
PORT133_DSPI_D_PCSD4 | 
PORT134_SIU_A_IRQ8 | 
PORT135_SIU_A_IRQ9 | 
PORT136_SIU_A_IRQ10 | 
PORT137_SIU_A_IRQ11 | 
PORT138_SIU_A_IRQ12 | 
PORT139_SIU_A_IRQ13 | 
PORT140_SIU_A_IRQ14 | 
PORT141_SIU_A_IRQ15 | 
PORT142_DSPI_C_PCSC1 | 
PORT143_DSPI_C_PCSC2 */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 144 ... 159 : PORT144_DSPI_C_PCSC3 | 
PORT145_DSPI_C_PCSC4 | 
PORT147_eTPU_B_ETPUB16 | 
PORT148_eTPU_B_ETPUB17 | 
PORT149_eTPU_B_ETPUB18 | 
PORT150_eTPU_B_ETPUB19 | 
PORT151_eTPU_B_ETPUB20 | 
PORT152_eTPU_B_ETPUB21 | 
PORT153_eTPU_B_ETPUB22 | 
PORT154_eTPU_B_ETPUB23 | 
PORT155_eTPU_B_ETPUB24 | 
PORT156_eTPU_B_ETPUB25 | 
PORT157_eTPU_B_ETPUB26 | 
PORT158_eTPU_B_ETPUB27 | 
PORT159_eTPU_B_ETPUB28 */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 160 ... 175 : PORT160_eTPU_B_ETPUB29 | 
PORT161_eTPU_B_ETPUB30 | 
PORT162_eTPU_B_ETPUB31 | 
PORT163_DSPI_A_PCSA1 | 
PORT164_DSPI_A_PCSA2 | 
PORT165_DSPI_A_PCSA3 | 
PORT166_DSPI_A_PCSA4 | 
PORT169_REACM_RCH0_B_OUT | 
PORT170_REACM_RCH1_B_OUT | 
PORT171_REACM_RCH2_B_OUT | 
PORT172_REACM_RCH3_B_OUT | 
PORT173_REACM_RCH4_B_OUT | 
PORT174_REACM_RCH5_B_OUT | 
PORT175_REACM_RCH6_B_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 176 ... 191 : PORT176_REACM_RCH7_B_OUT | 
PORT177_REACM_RCH8_B_OUT | 
PORT178_REACM_RCH9_B_OUT | 
PORT179_eTPU_A_ETPUA0 | 
PORT180_eTPU_A_ETPUA1 | 
PORT181_eTPU_A_ETPUA2 | 
PORT182_eTPU_A_ETPUA3 | 
PORT183_eTPU_A_ETPUA4 | 
PORT184_eTPU_A_ETPUA5 | 
PORT185_eTPU_A_ETPUA6 | 
PORT186_eTPU_A_ETPUA7 | 
PORT187_eTPU_A_ETPUA8 | 
PORT188_eTPU_A_ETPUA9 | 
PORT189_DSPI_D_SCKD_OUT | 
PORT191_DSPI_C_SOUTC */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(15)
          ),
/* Pads 192 ... 207 : PORT192_DSPI_D_SOUTD | 
PORT195_eTPU_B_ETPUB0 | 
PORT196_eTPU_B_ETPUB1 | 
PORT197_eTPU_B_ETPUB2 | 
PORT198_eTPU_B_ETPUB3 | 
PORT199_eTPU_B_ETPUB4 | 
PORT200_eTPU_B_ETPUB5 | 
PORT201_eTPU_B_ETPUB6 | 
PORT202_eTPU_B_ETPUB7 | 
PORT203_DSPI_B_PCSB0_OUT | 
PORT204_DSPI_B_PCSB1 */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12)
          ),
/* Pads 208 ... 223 : PORT210_eTPU_C_ETPUC3_OUT | 
PORT213_SIU_A_NMI_IN */
  (uint16)( SHL_PAD_U16(2) |
            SHL_PAD_U16(5)
          ),
/* Pads 224 ... 239 : PORT235_DSPI_C_SCK_C_LVDS_P | 
PORT236_DSPI_C_SCK_C_LVDS_N_OUT | 
PORT237_DSPI_C_SOUT_C_LVDS_P | 
PORT238_DSPI_C_SOUT_C_LVDS_N_OUT | 
PORT239_eSCI_D_TXDD */
  (uint16)( SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 240 ... 255 : PORT240_DSPI_D_SCK_D_LVDS_P | 
PORT241_DSPI_D_SCK_D_LVDS_N_OUT | 
PORT242_MCAN_0_TX_OUT | 
PORT244_eQADC_A_eQADC_B_ETRIG0_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(4)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 : PORT432_DSPI_B_PCSB2 | 
PORT433_DSPI_B_PCSB3 | 
PORT434_DSPI_C_PCSC0_OUT | 
PORT435_DSPI_C_PCSC1 | 
PORT436_DSPI_C_PCSC2 | 
PORT437_DSPI_C_PCSC5 | 
PORT446_DSPI_E_PCSE2 | 
PORT447_DSPI_E_PCSE3 */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 448 ... 463 : PORT448_DSPI_E_PCSE4 | 
PORT449_DSPI_E_PCSE5 | 
PORT457_MCAN_1_TX_OUT | 
PORT458_eSCI_F_TXDF | 
PORT459_eSCI_F_RXDF_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11)
          ),
/* Pads 464 ... 479 : PORT464_DSPI_D_PCSD5 | 
PORT465_DSPI_D_PCSD4 | 
PORT466_DSPI_D_PCSD3 | 
PORT467_DSPI_D_PCSD2 | 
PORT468_DSPI_D_PCSD1 | 
PORT469_DSPI_D_PCSD0_OUT | 
PORT470_DSPI_D_SCKD_OUT | 
PORT471_DSPI_D_SOUTD */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7)
          ),
/* Pads 480 ... 495 */
  (uint16)0x0000
}
,
/*  Mode PORT_ALT3_FUNC_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads  80 ...  95 : PORT83_MCAN_0_TX_OUT | 
PORT88_eSCI_E_RXDE | 
PORT93_MCAN_0_TX_OUT */
  (uint16)( SHL_PAD_U16(3) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(13)
          ),
/* Pads  96 ... 111 : PORT98_FEC_FEC_TXD2_OUT | 
PORT99_FEC_FEC_MDIO | 
PORT101_eSCI_D_RXDD */
  (uint16)( SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(5)
          ),
/* Pads 112 ... 127 : PORT116_REACM_RCH0_A_OUT | 
PORT117_REACM_RCH1_A_OUT | 
PORT118_REACM_RCH2_A_OUT | 
PORT119_REACM_RCH3_A_OUT | 
PORT120_REACM_RCH4_A_OUT | 
PORT121_REACM_RCH5_A_OUT | 
PORT122_REACM_RCH6_A_OUT | 
PORT123_REACM_RCH7_A_OUT | 
PORT124_REACM_RCH8_A_OUT | 
PORT125_REACM_RCH9_A_OUT */
  (uint16)( SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13)
          ),
/* Pads 128 ... 143 : PORT129_MCAN_0_TX_OUT | 
PORT136_REACM_RCH0_A_OUT | 
PORT137_REACM_RCH1_A_OUT | 
PORT138_REACM_RCH2_A_OUT | 
PORT139_REACM_RCH3_A_OUT | 
PORT140_REACM_RCH4_A_OUT | 
PORT141_REACM_RCH5_A_OUT | 
PORT142_REACM_RCH6_A_OUT | 
PORT143_REACM_RCH7_A_OUT */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 144 ... 159 : PORT144_REACM_RCH8_A_OUT | 
PORT145_REACM_RCH9_A_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1)
          ),
/* Pads 160 ... 175 */
  (uint16)0x0000,
/* Pads 176 ... 191 : PORT179_REACM_RCH0_C_OUT | 
PORT180_REACM_RCH1_C_OUT | 
PORT181_REACM_RCH2_C_OUT | 
PORT182_REACM_RCH3_C_OUT | 
PORT183_REACM_RCH4_C_OUT | 
PORT184_REACM_RCH5_C_OUT | 
PORT185_REACM_RCH6_C_OUT | 
PORT186_REACM_RCH7_C_OUT | 
PORT187_REACM_RCH8_C_OUT | 
PORT188_REACM_RCH9_C_OUT */
  (uint16)( SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12)
          ),
/* Pads 192 ... 207 : PORT193_FlexCAN_D_CNTXD | 
PORT195_MCAN_1_TX_OUT | 
PORT197_REACM_RCH4_C_OUT | 
PORT198_REACM_RCH5_C_OUT | 
PORT199_REACM_RCH6_C_OUT | 
PORT200_REACM_RCH7_C_OUT | 
PORT201_REACM_RCH8_C_OUT | 
PORT202_REACM_RCH9_C_OUT */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10)
          ),
/* Pads 208 ... 223 : PORT208_eTPU_C_ETPUC9_OUT | 
PORT209_DSPI_D_SOUTD | 
PORT210_DSPI_E_PCSE1 | 
PORT212_eTPU_C_ETPUC0_OUT | 
PORT213_eTPU_C_ETPUC1_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5)
          ),
/* Pads 224 ... 239 */
  (uint16)0x0000,
/* Pads 240 ... 255 : PORT240_DSPI_D_SCKD_OUT | 
PORT242_DSPI_D_SOUT_D_LVDS_P | 
PORT243_DSPI_D_SOUT_D_LVDS_N_OUT | 
PORT246_MCAN_1_TX_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(6)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 */
  (uint16)0x0000,
/* Pads 448 ... 463 : PORT453_MCAN_1_TX_OUT | 
PORT454_PSI5A_SDOUT0_PSI5A_OUT | 
PORT455_PSI5A_SDIN0_PSI5A_IN | 
PORT456_REACM_RCH2_C_OUT | 
PORT457_REACM_RCH3_C_OUT | 
PORT458_REACM_RCH4_C_OUT | 
PORT460_PSI5A_SDOUT0_PSI5B_OUT | 
PORT461_PSI5A_SDIN0_PSI5B_IN */
  (uint16)( SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13)
          ),
/* Pads 464 ... 479 : PORT464_eQADC_A_MAA0 | 
PORT465_eQADC_A_MAA1 | 
PORT466_eQADC_A_MAA2 | 
PORT467_eQADC_B_MAB0 | 
PORT468_REACM_RCH5_C_OUT | 
PORT469_REACM_RCH6_C_OUT | 
PORT470_REACM_RCH7_C_OUT | 
PORT471_REACM_RCH8_C_OUT | 
PORT472_REACM_RCH9_C_OUT */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8)
          ),
/* Pads 480 ... 495 */
  (uint16)0x0000
}
,
/*  Mode PORT_ALT4_FUNC_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads 80 ... 95 */
  (uint16)0x0000,
/* Pads  96 ... 111 : PORT98_FEC_FEC_RXER_IN | 
PORT99_eSCI_D_TXDD | 
PORT100_FEC_FEC_RXCLK_IN | 
PORT101_FEC_FEC_TXD3_OUT | 
PORT107_FEC_FEC_RXD3_IN | 
PORT109_FEC_FEC_MDC_OUT | 
PORT110_FEC_FEC_RXD2_IN */
  (uint16)( SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14)
          ),
/* Pads 112 ... 127 : PORT117_FCCU_ERROR0 | 
PORT124_FCCU_ERRORIN | 
PORT125_FCCU_ERROR1 */
  (uint16)( SHL_PAD_U16(5) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13)
          ),
/* Pads 128 ... 143 */
  (uint16)0x0000,
/* Pads 144 ... 159 */
  (uint16)0x0000,
/* Pads 160 ... 175 */
  (uint16)0x0000,
/* Pads 176 ... 191 : PORT180_DSPI_E_PCSE2 | 
PORT181_DSPI_E_PCSE3 | 
PORT182_DSPI_E_PCSE4 | 
PORT183_DSPI_E_PCSE5 */
  (uint16)( SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7)
          ),
/* Pads 192 ... 207 : PORT193_REACM_RCH0_C_OUT | 
PORT194_REACM_RCH1_C_OUT | 
PORT195_REACM_RCH2_C_OUT | 
PORT196_REACM_RCH3_C_OUT */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4)
          ),
/* Pads 208 ... 223 : PORT208_SIPI_TXN | 
PORT209_SIPI_TXP | 
PORT210_SIPI_REFCLK_INOUT | 
PORT210_SIPI_REFCLK_OUT | 
PORT210_SIPI_REFCLK_IN | 
PORT212_SIPI_RXP | 
PORT213_SIPI_RXN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5)
          ),
/* Pads 224 ... 239 */
  (uint16)0x0000,
/* Pads 240 ... 255 : PORT242_DSPI_D_SOUTD | 
PORT243_DSPI_D_PCSD0_OUT */
  (uint16)( SHL_PAD_U16(2) |
            SHL_PAD_U16(3)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 */
  (uint16)0x0000,
/* Pads 448 ... 463 : PORT454_REACM_RCH0_C_OUT | 
PORT455_REACM_RCH1_C_OUT */
  (uint16)( SHL_PAD_U16(6) |
            SHL_PAD_U16(7)
          ),
/* Pads 464 ... 479 : PORT464_eQADC_B_MAB0 | 
PORT465_eQADC_B_MAB1 | 
PORT466_eQADC_B_MAB2 | 
PORT468_eQADC_B_MAB1 | 
PORT469_eQADC_B_MAB2 */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5)
          ),
/* Pads 480 ... 495 */
  (uint16)0x0000
}
,
/*  Mode PORT_INPUT1_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads  80 ...  95 : PORT89_eSCI_A_TXDA | 
PORT90_eSCI_A_RXDA_IN | 
PORT91_eSCI_B_TXDB | 
PORT92_eSCI_B_RXDB */
  (uint16)( SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12)
          ),
/* Pads  96 ... 111 : PORT105_DSPI_B_PCSB0_INOUT | 
PORT105_DSPI_B_PCSB0_IN */
  (uint16)( SHL_PAD_U16(9) |
            SHL_PAD_U16(9)
          ),
/* Pads 112 ... 127 */
  (uint16)0x0000,
/* Pads 128 ... 143 : PORT138_eTPU_A_ETPUA24_INOUT | 
PORT138_eTPU_A_ETPUA24_IN | 
PORT139_eTPU_A_ETPUA25_INOUT | 
PORT139_eTPU_A_ETPUA25_IN | 
PORT140_eTPU_A_ETPUA26_INOUT | 
PORT140_eTPU_A_ETPUA26_IN | 
PORT141_eTPU_A_ETPUA27_INOUT | 
PORT141_eTPU_A_ETPUA27_IN | 
PORT142_eTPU_A_ETPUA28_INOUT | 
PORT142_eTPU_A_ETPUA28_IN | 
PORT143_eTPU_A_ETPUA29_INOUT | 
PORT143_eTPU_A_ETPUA29_IN */
  (uint16)( SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15) |
            SHL_PAD_U16(15)
          ),
/* Pads 144 ... 159 : PORT144_eTPU_A_ETPUA30_INOUT | 
PORT144_eTPU_A_ETPUA30_IN | 
PORT145_eTPU_A_ETPUA31_INOUT | 
PORT145_eTPU_A_ETPUA31_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1)
          ),
/* Pads 160 ... 175 */
  (uint16)0x0000,
/* Pads 176 ... 191 */
  (uint16)0x0000,
/* Pads 192 ... 207 : PORT195_eMIOS_A_EMIOS16_INOUT | 
PORT195_eMIOS_A_EMIOS16_IN | 
PORT196_eMIOS_A_EMIOS17_INOUT | 
PORT196_eMIOS_A_EMIOS17_IN | 
PORT197_eMIOS_A_EMIOS18_INOUT | 
PORT197_eMIOS_A_EMIOS18_IN | 
PORT198_eMIOS_A_EMIOS19_INOUT | 
PORT198_eMIOS_A_EMIOS19_IN | 
PORT199_eMIOS_A_EMIOS20_INOUT | 
PORT199_eMIOS_A_EMIOS20_IN | 
PORT200_eMIOS_A_EMIOS21_INOUT | 
PORT200_eMIOS_A_EMIOS21_IN | 
PORT201_eMIOS_A_EMIOS22_INOUT | 
PORT201_eMIOS_A_EMIOS22_IN | 
PORT202_eMIOS_A_EMIOS23_INOUT | 
PORT202_eMIOS_A_EMIOS23_IN | 
PORT203_eMIOS_B_EMIOS16_INOUT | 
PORT203_eMIOS_B_EMIOS16_IN | 
PORT204_eMIOS_B_EMIOS17_INOUT | 
PORT204_eMIOS_B_EMIOS17_IN */
  (uint16)( SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(12)
          ),
/* Pads 208 ... 223 */
  (uint16)0x0000,
/* Pads 224 ... 239 : PORT235_DSPI_C_SCKC_INOUT | 
PORT235_DSPI_C_SCKC_IN | 
PORT236_DSPI_C_SINC_IN | 
PORT238_DSPI_C_PCSC0_INOUT | 
PORT238_DSPI_C_PCSC0_IN */
  (uint16)( SHL_PAD_U16(11) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14)
          ),
/* Pads 240 ... 255 : PORT247_FlexCAN_D_CNRXD_IN */
  (uint16)( SHL_PAD_U16(7)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 : PORT432_eMIOS_B_EMIOS18_INOUT | 
PORT432_eMIOS_B_EMIOS18_IN | 
PORT433_eMIOS_B_EMIOS19_INOUT | 
PORT433_eMIOS_B_EMIOS19_IN | 
PORT434_eMIOS_B_EMIOS20_INOUT | 
PORT434_eMIOS_B_EMIOS20_IN | 
PORT435_eMIOS_B_EMIOS21_INOUT | 
PORT435_eMIOS_B_EMIOS21_IN | 
PORT436_eMIOS_B_EMIOS22_INOUT | 
PORT436_eMIOS_B_EMIOS22_IN | 
PORT437_eMIOS_B_EMIOS23_INOUT | 
PORT437_eMIOS_B_EMIOS23_IN | 
PORT440_eTPU_C_TCRCLKC_IN | 
PORT441_eTPU_C_ETPUC0_IN | 
PORT442_eTPU_C_ETPUC1_IN | 
PORT444_eTPU_C_ETPUC3_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(12)
          ),
/* Pads 448 ... 463 : PORT449_eTPU_C_ETPUC8_INOUT | 
PORT449_eTPU_C_ETPUC8_IN | 
PORT450_eTPU_C_ETPUC9_IN | 
PORT451_eTPU_C_ETPUC10_INOUT | 
PORT451_eTPU_C_ETPUC10_IN | 
PORT452_eTPU_C_ETPUC11_INOUT | 
PORT452_eTPU_C_ETPUC11_IN | 
PORT453_eTPU_C_ETPUC12_INOUT | 
PORT453_eTPU_C_ETPUC12_IN | 
PORT454_eTPU_C_ETPUC13_INOUT | 
PORT454_eTPU_C_ETPUC13_IN | 
PORT455_eTPU_C_ETPUC14_INOUT | 
PORT455_eTPU_C_ETPUC14_IN | 
PORT456_eTPU_C_ETPUC15_INOUT | 
PORT456_eTPU_C_ETPUC15_IN */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(8)
          ),
/* Pads 464 ... 479 : PORT475_SENT_A_SENT2_A_IN */
  (uint16)( SHL_PAD_U16(11)
          ),
/* Pads 480 ... 495 */
  (uint16)0x0000
}
,
/*  Mode PORT_INPUT2_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads  80 ...  95 : PORT83_eSCI_A_TXDA | 
PORT84_eSCI_A_RXDA */
  (uint16)( SHL_PAD_U16(3) |
            SHL_PAD_U16(4)
          ),
/* Pads  96 ... 111 : PORT106_DSPI_D_PCSD0_INOUT | 
PORT106_DSPI_D_PCSD0_IN | 
PORT108_DSPI_C_SINC | 
PORT109_DSPI_C_SCKC_INOUT | 
PORT109_DSPI_C_SCKC_IN | 
PORT110_DSPI_C_PCSC0_INOUT | 
PORT110_DSPI_C_PCSC0_IN */
  (uint16)( SHL_PAD_U16(10) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(14)
          ),
/* Pads 112 ... 127 */
  (uint16)0x0000,
/* Pads 128 ... 143 */
  (uint16)0x0000,
/* Pads 144 ... 159 : PORT146_SIU_A_IRQ6 */
  (uint16)( SHL_PAD_U16(2)
          ),
/* Pads 160 ... 175 */
  (uint16)0x0000,
/* Pads 176 ... 191 : PORT189_DSPI_D_SCKD_INOUT | 
PORT189_DSPI_D_SCKD_IN | 
PORT190_DSPI_D_SIND */
  (uint16)( SHL_PAD_U16(13) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14)
          ),
/* Pads 192 ... 207 : PORT193_SIU_A_IRQ0 | 
PORT194_SIU_A_IRQ1_IN | 
PORT203_DSPI_B_PCSB0_INOUT | 
PORT203_DSPI_B_PCSB0_IN */
  (uint16)( SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(11)
          ),
/* Pads 208 ... 223 : PORT208_SIU_A_IRQ4_IN | 
PORT209_SIU_A_IRQ5_IN | 
PORT210_eTPU_C_ETPUC3_INOUT | 
PORT210_eTPU_C_ETPUC3_IN | 
PORT212_SIU_A_IRQ3_IN | 
PORT223_eSCI_E_TXDE */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(15)
          ),
/* Pads 224 ... 239 */
  (uint16)0x0000,
/* Pads 240 ... 255 : PORT243_MCAN_0_RX_IN | 
PORT248_SENT_A_SENT0_A_IN | 
PORT249_SENT_A_SENT1_A_IN | 
PORT250_SENT_A_SENT2_A_IN | 
PORT251_SENT_A_SENT3_A_IN | 
PORT252_SENT_A_SENT4_A_IN | 
PORT253_SENT_A_SENT5_A_IN */
  (uint16)( SHL_PAD_U16(3) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 : PORT434_DSPI_C_PCSC0_INOUT | 
PORT434_DSPI_C_PCSC0_IN | 
PORT440_SIU_A_IRQ6_IN | 
PORT441_SENT_A_SENT0_A_IN | 
PORT442_SENT_A_SENT1_A_IN | 
PORT443_SENT_A_SENT3_A_IN | 
PORT444_SENT_A_SENT4_A_IN | 
PORT445_SENT_A_SENT5_A_IN */
  (uint16)( SHL_PAD_U16(2) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13)
          ),
/* Pads 448 ... 463 : PORT450_SIU_A_IRQ0_IN | 
PORT451_SIU_A_IRQ1_IN | 
PORT452_SIU_A_IRQ2_IN | 
PORT453_SIU_A_IRQ3_IN | 
PORT454_SIU_A_IRQ4_IN | 
PORT455_SIU_A_IRQ5_IN | 
PORT456_MCAN_1_RX_IN | 
PORT460_eSCI_A_TXDA | 
PORT461_eSCI_A_RXDA_IN | 
PORT462_eSCI_B_TXDB | 
PORT463_eSCI_B_RXDB_IN */
  (uint16)( SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 464 ... 479 : PORT469_DSPI_D_PCSD0_INOUT | 
PORT469_DSPI_D_PCSD0_IN | 
PORT470_DSPI_D_SCKD_INOUT | 
PORT470_DSPI_D_SCKD_IN | 
PORT472_DSPI_D_SIND_IN | 
PORT474_SENT_B_SENT0_B_IN | 
PORT476_eTPU_A_ETPUA31_IN | 
PORT477_eTPU_A_ETPUA30_IN | 
PORT478_eTPU_A_ETPUA29_IN | 
PORT479_eTPU_A_ETPUA28_IN */
  (uint16)( SHL_PAD_U16(5) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 480 ... 495 : PORT480_eTPU_A_ETPUA27_IN | 
PORT481_eTPU_A_ETPUA26_IN | 
PORT482_eTPU_A_ETPUA25_IN | 
PORT483_eTPU_A_ETPUA24_IN | 
PORT484_eTPU_C_ETPUC15_IN | 
PORT485_eTPU_C_ETPUC14_IN | 
PORT486_eTPU_C_ETPUC13_IN | 
PORT487_eTPU_C_ETPUC12_IN | 
PORT488_eTPU_C_ETPUC11_IN | 
PORT489_eTPU_C_ETPUC10_IN | 
PORT490_eTPU_C_ETPUC9_IN | 
PORT491_eTPU_C_ETPUC8_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11)
          )
}
,
/*  Mode PORT_INPUT3_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads  80 ...  95 : PORT84_MCAN_0_RX_IN | 
PORT91_MCAN_0_RX_IN */
  (uint16)( SHL_PAD_U16(4) |
            SHL_PAD_U16(11)
          ),
/* Pads  96 ... 111 : PORT100_eSCI_E_TXDE | 
PORT107_SENT_B_SENT2_B_IN | 
PORT108_SENT_B_SENT3_B_IN | 
PORT109_SENT_B_SENT4_B_IN | 
PORT110_SENT_B_SENT5_B_IN */
  (uint16)( SHL_PAD_U16(4) |
            SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14)
          ),
/* Pads 112 ... 127 */
  (uint16)0x0000,
/* Pads 128 ... 143 : PORT133_MCAN_0_RX_IN */
  (uint16)( SHL_PAD_U16(5)
          ),
/* Pads 144 ... 159 */
  (uint16)0x0000,
/* Pads 160 ... 175 */
  (uint16)0x0000,
/* Pads 176 ... 191 */
  (uint16)0x0000,
/* Pads 192 ... 207 : PORT194_FlexCAN_D_CNRXD_IN | 
PORT196_MCAN_1_RX_IN */
  (uint16)( SHL_PAD_U16(2) |
            SHL_PAD_U16(4)
          ),
/* Pads 208 ... 223 : PORT208_eTPU_C_ETPUC9_INOUT | 
PORT208_eTPU_C_ETPUC9_IN | 
PORT212_eTPU_C_ETPUC0_INOUT | 
PORT212_eTPU_C_ETPUC0_IN | 
PORT213_eTPU_C_ETPUC1_INOUT | 
PORT213_eTPU_C_ETPUC1_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(5)
          ),
/* Pads 224 ... 239 */
  (uint16)0x0000,
/* Pads 240 ... 255 : PORT240_DSPI_D_SCKD_INOUT | 
PORT240_DSPI_D_SCKD_IN | 
PORT241_DSPI_D_SIND_IN | 
PORT247_MCAN_1_RX_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(7)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 : PORT445_eTPU_C_TCRCLKC_IN | 
PORT446_SENT_B_SENT0_B_IN | 
PORT447_SENT_B_SENT1_B_IN */
  (uint16)( SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 448 ... 463 : PORT448_SENT_B_SENT2_B_IN | 
PORT449_SENT_B_SENT3_B_IN | 
PORT450_SENT_B_SENT4_B_IN | 
PORT451_SENT_B_SENT5_B_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3)
          ),
/* Pads 464 ... 479 : PORT476_eMIOS_A_EMIOS16_IN | 
PORT477_eMIOS_A_EMIOS17_IN | 
PORT478_eMIOS_A_EMIOS18_IN | 
PORT479_eMIOS_A_EMIOS19_IN */
  (uint16)( SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 480 ... 495 : PORT480_eMIOS_A_EMIOS20_IN | 
PORT481_eMIOS_A_EMIOS21_IN | 
PORT482_eMIOS_A_EMIOS22_IN | 
PORT483_eMIOS_A_EMIOS23_IN | 
PORT484_eMIOS_B_EMIOS16_IN | 
PORT485_eMIOS_B_EMIOS17_IN | 
PORT486_eMIOS_B_EMIOS18_IN | 
PORT487_eMIOS_B_EMIOS19_IN | 
PORT488_eMIOS_B_EMIOS20_IN | 
PORT489_eMIOS_B_EMIOS21_IN | 
PORT490_eMIOS_B_EMIOS22_IN | 
PORT491_eMIOS_B_EMIOS23_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11)
          )
}
,
/*  Mode PORT_INPUT4_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads  80 ...  95 : PORT93_SENT_B_SENT1_B_IN */
  (uint16)( SHL_PAD_U16(13)
          ),
/* Pads 96 ... 111 */
  (uint16)0x0000,
/* Pads 112 ... 127 */
  (uint16)0x0000,
/* Pads 128 ... 143 */
  (uint16)0x0000,
/* Pads 144 ... 159 */
  (uint16)0x0000,
/* Pads 160 ... 175 */
  (uint16)0x0000,
/* Pads 176 ... 191 */
  (uint16)0x0000,
/* Pads 192 ... 207 */
  (uint16)0x0000,
/* Pads 208 ... 223 */
  (uint16)0x0000,
/* Pads 224 ... 239 */
  (uint16)0x0000,
/* Pads 240 ... 255 : PORT243_DSPI_D_PCSD0_INOUT | 
PORT243_DSPI_D_PCSD0_IN */
  (uint16)( SHL_PAD_U16(3) |
            SHL_PAD_U16(3)
          ),
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 */
  (uint16)0x0000,
/* Pads 448 ... 463 */
  (uint16)0x0000,
/* Pads 464 ... 479 */
  (uint16)0x0000,
/* Pads 480 ... 495 */
  (uint16)0x0000
}
,
/*  Mode PORT_ANALOG_INPUT_MODE: */
{
/* Pads 0 ... 15 */
  (uint16)0x0000,
/* Pads 16 ... 31 */
  (uint16)0x0000,
/* Pads 32 ... 47 */
  (uint16)0x0000,
/* Pads 48 ... 63 */
  (uint16)0x0000,
/* Pads 64 ... 79 */
  (uint16)0x0000,
/* Pads 80 ... 95 */
  (uint16)0x0000,
/* Pads 96 ... 111 */
  (uint16)0x0000,
/* Pads 112 ... 127 */
  (uint16)0x0000,
/* Pads 128 ... 143 */
  (uint16)0x0000,
/* Pads 144 ... 159 */
  (uint16)0x0000,
/* Pads 160 ... 175 */
  (uint16)0x0000,
/* Pads 176 ... 191 */
  (uint16)0x0000,
/* Pads 192 ... 207 */
  (uint16)0x0000,
/* Pads 208 ... 223 */
  (uint16)0x0000,
/* Pads 224 ... 239 */
  (uint16)0x0000,
/* Pads 240 ... 255 */
  (uint16)0x0000,
/* Pads 256 ... 271 */
  (uint16)0x0000,
/* Pads 272 ... 287 */
  (uint16)0x0000,
/* Pads 288 ... 303 */
  (uint16)0x0000,
/* Pads 304 ... 319 */
  (uint16)0x0000,
/* Pads 320 ... 335 */
  (uint16)0x0000,
/* Pads 336 ... 351 */
  (uint16)0x0000,
/* Pads 352 ... 367 */
  (uint16)0x0000,
/* Pads 368 ... 383 */
  (uint16)0x0000,
/* Pads 384 ... 399 */
  (uint16)0x0000,
/* Pads 400 ... 415 */
  (uint16)0x0000,
/* Pads 416 ... 431 */
  (uint16)0x0000,
/* Pads 432 ... 447 : PORT440_eQADC_B_ANB40_IN | 
PORT441_eQADC_B_ANB41_IN | 
PORT442_eQADC_B_ANB42_IN | 
PORT444_eQADC_B_ANB45_IN */
  (uint16)( SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(12)
          ),
/* Pads 448 ... 463 : PORT450_eQADC_B_ANB44_IN */
  (uint16)( SHL_PAD_U16(2)
          ),
/* Pads 464 ... 479 : PORT475_eQADC_B_ANB43_IN | 
PORT476_eQADC_B_ANB8_IN | 
PORT477_eQADC_B_ANB9_IN | 
PORT478_eQADC_B_ANB10_IN | 
PORT479_eQADC_B_ANB11_IN */
  (uint16)( SHL_PAD_U16(11) |
            SHL_PAD_U16(12) |
            SHL_PAD_U16(13) |
            SHL_PAD_U16(14) |
            SHL_PAD_U16(15)
          ),
/* Pads 480 ... 495 : PORT480_eQADC_B_ANB12_IN | 
PORT481_eQADC_B_ANB13_IN | 
PORT482_eQADC_B_ANB14_IN | 
PORT483_eQADC_B_ANB15_IN | 
PORT484_eQADC_B_ANB16_IN | 
PORT485_eQADC_B_ANB17_IN | 
PORT486_eQADC_B_ANB18_IN | 
PORT487_eQADC_B_ANB19_IN | 
PORT488_eQADC_B_ANB20_IN | 
PORT489_eQADC_B_ANB21_IN | 
PORT490_eQADC_B_ANB22_IN | 
PORT491_eQADC_B_ANB23_IN */
  (uint16)( SHL_PAD_U16(0) |
            SHL_PAD_U16(1) |
            SHL_PAD_U16(2) |
            SHL_PAD_U16(3) |
            SHL_PAD_U16(4) |
            SHL_PAD_U16(5) |
            SHL_PAD_U16(6) |
            SHL_PAD_U16(7) |
            SHL_PAD_U16(8) |
            SHL_PAD_U16(9) |
            SHL_PAD_U16(10) |
            SHL_PAD_U16(11)
          )
}


};

#endif 

#define PORT_STOP_SEC_CONFIG_DATA_16
/**
* @violates @ref PORT_PBCFG_REF_1 only preprocessor statements and comments before '#include'
* @violates @ref PORT_PBCFG_REF_2 Precautions shall be taken in order to prevent
* the contents of a header file being included twice
*/
#include "MemMap.h"

/*=================================================================================================
*                                      GLOBAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/


/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

#endif    /* PORT_PRECOMPILE_SUPPORT*/

#ifdef __cplusplus
}
#endif
/** @} */

/* End of File */

