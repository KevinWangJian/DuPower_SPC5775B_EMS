/**
*   @file    Dio_Siu.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Dio SIU low level SIU header.
*   @details This file is the SIU DIO low level driver header.
*
*   @addtogroup DIO_SIU
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

#ifndef DIO_SIU_H
#define DIO_SIU_H

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Dio_Siu_h_REF_1
*     Violates MISRA 2004 Required Rule 19.15, Repeated include files, Precautions shall be taken in
*     order to prevent the contents of a header file being included twice. This violation is not fixed 
*     since the inclusion of MemMap.h is as per Autosar requirement MEMMAP003.
*
* @section [global]
*     Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
*     on the significance of more than 31 characters. The used compilers use more than 31 chars for
*     identifiers.
*/

/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

/*=================================================================================================
*                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_SIU_VENDOR_ID                     43
#define DIO_SIU_AR_RELEASE_MAJOR_VERSION      4
#define DIO_SIU_AR_RELEASE_MINOR_VERSION      0
#define DIO_SIU_AR_RELEASE_REVISION_VERSION   3
#define DIO_SIU_SW_MAJOR_VERSION              1
#define DIO_SIU_SW_MINOR_VERSION              0
#define DIO_SIU_SW_PATCH_VERSION              1

/*=================================================================================================
                                      FILE VERSION CHECKS
=================================================================================================*/


/*=================================================================================================
*                                          CONSTANTS
=================================================================================================*/

#define DIO_PORTID_SHIFT_U8                     ((uint8)0x4U)
#define DIO_CHANNELGRP_OFFSET_PINS_U32          ((uint32)0x0000FFFFUL)
#define DIO_CHANNELGRP_MASK_PINS_U32            ((uint32)0x16UL)

/*=================================================================================================
*                                      DEFINES AND MACROS
=================================================================================================*/


/*=================================================================================================
*                                             ENUMS
=================================================================================================*/


/*=================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
=================================================================================================*/


/*=================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
=================================================================================================*/


/*=================================================================================================
*                                    FUNCTION PROTOTYPES
=================================================================================================*/

#define DIO_START_SEC_CODE
/* @violates @ref Dio_Siu_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"

/**
* @brief   Read the channel level
*/
FUNC(Dio_LevelType, DIO_CODE) Dio_Siu_ReadChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId
);

/**
* @brief   Write the level to the channel
*/
FUNC(void, DIO_CODE) Dio_Siu_WriteChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId,
    CONST(Dio_LevelType,   AUTOMATIC) Level
);

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/**
* @brief   Flip the level of the channel
*/
FUNC(Dio_LevelType, DIO_CODE) Dio_Siu_FlipChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId
);
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

/**
* @brief   Read the port level
*/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_Siu_ReadPort
(
    CONST(Dio_PortType, AUTOMATIC) PortId
);

/**
* @brief   Write the port level
*/
FUNC(void, DIO_CODE) Dio_Siu_WritePort
(
    CONST(Dio_PortType,      AUTOMATIC) PortId,
    CONST(Dio_PortLevelType, AUTOMATIC) Level
);

/**
* @brief   Read the level of the channels group
*/
FUNC(Dio_PortLevelType, DIO_CODE) Dio_Siu_ReadChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupIdPtr
);

/**
* @brief   Write the level of the channels group
*/
FUNC(void, DIO_CODE) Dio_Siu_WriteChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupIdPtr,
    CONST  (Dio_PortLevelType,    AUTOMATIC)                 Level
);

#if (STD_ON == DIO_MASKEDWRITEPORT_API)
/**
@brief   DIO Mask write port using mask
*/
FUNC(void, DIO_CODE) Dio_Siu_MaskedWritePort
(
    CONST(Dio_PortType,      AUTOMATIC) PortId,
    CONST(Dio_PortLevelType, AUTOMATIC) Level,
    CONST(Dio_PortLevelType, AUTOMATIC) Mask
);
#endif /* (STD_ON == DIO_MASKEDWRITEPORT_API) */

#define DIO_STOP_SEC_CODE
/** @violates @ref Dio_Siu_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

#endif /* DIO_SIU_H */
/** @} */
