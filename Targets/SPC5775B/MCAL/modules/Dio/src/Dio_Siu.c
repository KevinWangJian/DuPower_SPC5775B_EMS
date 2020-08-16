/**
*   @file    Dio_Siu.c
*   @implements        DIO_SIU_unit
*   @version 1.0.1
*
*   @brief   AUTOSAR Dio SIU source file support for DIO driver.
*   @details This file is the SIU DIO low level driver code.
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
===================================================================================================*/

#ifdef __cplusplus
extern "C" {
#endif

/**
* @file    Dio_SIU.c
* */

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section Dio_Siu_C_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file,
* Precautions shall be taken in order to prevent the contents of a header file
* being included twice. This violation is not fixed since the inclusion of MemMap.h 
* is as per Autosar requirement MEMMAP003.
*
* @section Dio_Siu_C_REF_2
* Violates MISRA 2004 Required Rule 11.1, cast from unsigned long to pointer.
* This macro computes the address of any register by using the hardware offset of the controller. 
* The address calculated as an unsigned int is passed to a macro for initializing the pointer with that address.
*
* @section Dio_Siu_C_REF_3
* Violates MISRA 2004 Required Rule 1.4, Identifier clash
* The used compilers/linkers allow more than 31 characters significance for external identifiers.
*
* @section Dio_Siu_C_REF_4
* Violates MISRA 2004 Advisory Rule 19.7, Function-like macro defined
* This violation is due to function like macros defined for register operations.
* Function like macros are used to reduce code complexity.
*
* @section Dio_Siu_C_REF_5
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments
* before '#include'. MemMap.h is included after each section define in order to set the current memory section 
* as defined by AUTOSAR.
*
* @section Dio_Siu_C_REF_6
* Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between a pointer type and 
* an integral type. The cast is used to access memory mapped registers.
*
* @section Dio_Siu_C_REF_7
* Violates MISRA 2004 Required Rule 10.5 , If the bitwise operators ~ and << are applied to an operand
* of underlying type unsigned char or unsigned shot, the result shall be immediately cast to the underlying type
* of the operand
* This violation is due to the operator << was used.
*
*/


/*=================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
=================================================================================================*/

#include "Dio_Cfg.h"
#include "Dio_Ipw.h"
#include "Dio_Siu.h"
#define USER_MODE_REG_PROT_ENABLED (DIO_USER_MODE_SOFT_LOCKING)
#include "SilRegMacros.h"
#include "Dio_Reg_eSys_Siu.h"
#include "SchM_Dio.h"

/*=================================================================================================
                               SOURCE FILE VERSION INFORMATION
=================================================================================================*/

#define DIO_SIU_VENDOR_ID_C                    43
/* @violates @ref Dio_Siu_C_REF_3 MISRA 2004 Required Rule 1.4, Identifier clash */
#define DIO_SIU_AR_RELEASE_MAJOR_VERSION_C     4
/* @violates @ref Dio_Siu_C_REF_3 MISRA 2004 Required Rule 1.4, Identifier clash */
#define DIO_SIU_AR_RELEASE_MINOR_VERSION_C     0
/* @violates @ref Dio_Siu_C_REF_3 MISRA 2004 Required Rule 1.4, Identifier clash */
#define DIO_SIU_AR_RELEASE_REVISION_VERSION_C  3
#define DIO_SIU_SW_MAJOR_VERSION_C             1
#define DIO_SIU_SW_MINOR_VERSION_C             0
#define DIO_SIU_SW_PATCH_VERSION_C             1

/*=================================================================================================
*                                     FILE VERSION CHECKS
=================================================================================================*/

/* Dio_Ipw.h version check start */
#if ((DIO_SIU_AR_RELEASE_MAJOR_VERSION_C != DIO_AR_RELEASE_MAJOR_VERSION_IPW) || \
     (DIO_SIU_AR_RELEASE_MINOR_VERSION_C != DIO_AR_RELEASE_MINOR_VERSION_IPW) || \
     (DIO_SIU_AR_RELEASE_REVISION_VERSION_C != DIO_AR_RELEASE_REVISION_VERSION_IPW) \
    )
    #error "AUTOSAR Version Numbers of Dio.c and Dio_Ipw.h are different"
#endif

#if ((DIO_SIU_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION_IPW) || \
     (DIO_SIU_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION_IPW) || \
     (DIO_SIU_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION_IPW) \
    )
    #error "Software Version Numbers of Dio.c and Dio_Ipw.h are different"
#endif

#if (DIO_SIU_VENDOR_ID_C != DIO_VENDOR_ID_IPW)
    #error "VENDOR ID for Dio.c and Dio_Ipw.h is different"
#endif
/* Dio_Ipw.h version check end */

/* Dio_Siu.h version check start */
#if ((DIO_SIU_AR_RELEASE_MAJOR_VERSION_C != DIO_SIU_AR_RELEASE_MAJOR_VERSION) || \
     (DIO_SIU_AR_RELEASE_MINOR_VERSION_C != DIO_SIU_AR_RELEASE_MINOR_VERSION) || \
     (DIO_SIU_AR_RELEASE_REVISION_VERSION_C != DIO_SIU_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AUTOSAR Version Numbers of Dio_Siu.c and Dio_Siu.h are different"
#endif

#if ((DIO_SIU_SW_MAJOR_VERSION_C != DIO_SIU_SW_MAJOR_VERSION) || \
     (DIO_SIU_SW_MINOR_VERSION_C != DIO_SIU_SW_MINOR_VERSION) || \
     (DIO_SIU_SW_PATCH_VERSION_C != DIO_SIU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Dio_Siu.c and Dio_Siu.h are different"
#endif

#if (DIO_SIU_VENDOR_ID_C != DIO_SIU_VENDOR_ID)
    #error "VENDOR ID for Dio_Siu.c and Dio_Siu.h is different"
#endif
/* Dio_Siu.h version check end */

/* SilRegMacros.h version check start */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
  #if ((DIO_SIU_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
       (DIO_SIU_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
      )
      #error "AUTOSAR Version Numbers of Dio_Siu.c and SilRegMacros.h are different"
  #endif
#endif
/* SilRegMacros.h version check end */

/* Dio_Reg_eSys_Siu.h version check start */
#if ((DIO_SIU_AR_RELEASE_MAJOR_VERSION_C != DIO_REGESYS_SIU_AR_RELEASE_MAJOR_VERSION_REG) || \
     (DIO_SIU_AR_RELEASE_MINOR_VERSION_C != DIO_REGESYS_SIU_AR_RELEASE_MINOR_VERSION_REG) || \
     (DIO_SIU_AR_RELEASE_REVISION_VERSION_C != DIO_REGESYS_SIU_AR_RELEASE_REVISION_VERSION_REG) \
    )
    #error "AUTOSAR Version Numbers of Dio_Siu.c and Dio_Reg_eSys_Siu.h are different"
#endif

#if ((DIO_SIU_SW_MAJOR_VERSION_C != DIO_REGESYS_SIU_SW_MAJOR_VERSION_REG) || \
     (DIO_SIU_SW_MINOR_VERSION_C != DIO_REGESYS_SIU_SW_MINOR_VERSION_REG) ||\
     (DIO_SIU_SW_PATCH_VERSION_C != DIO_REGESYS_SIU_SW_PATCH_VERSION_REG) \
    )
    #error "Software Version Numbers of Dio_Siu.c and Dio_Reg_eSys_Siu.h are different"
#endif

#if (DIO_SIU_VENDOR_ID_C != DIO_REGESYS_SIU_VENDOR_ID_REG)
    #error "VENDOR ID for Dio_Siu.c and Dio_Reg_eSys_Siu.h is different"
#endif
/* Dio_Reg_eSys_Siu.h version check end */

/* Dio_Cfg.h version check start */
#if ((DIO_SIU_AR_RELEASE_MAJOR_VERSION_C != DIO_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (DIO_SIU_AR_RELEASE_MINOR_VERSION_C != DIO_AR_RELEASE_MINOR_VERSION_CFG) || \
     (DIO_SIU_AR_RELEASE_REVISION_VERSION_C != DIO_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AUTOSAR Version Numbers of Dio_Siu.c and Dio_Cfg.h are different"
#endif

#if ((DIO_SIU_SW_MAJOR_VERSION_C != DIO_SW_MAJOR_VERSION_CFG) || \
     (DIO_SIU_SW_MINOR_VERSION_C != DIO_SW_MINOR_VERSION_CFG) ||\
     (DIO_SIU_SW_PATCH_VERSION_C != DIO_SW_PATCH_VERSION_CFG) \
    )
    #error "Software Version Numbers of Dio_Siu.c and Dio_Cfg.h are different"
#endif

#if (DIO_SIU_VENDOR_ID_C != DIO_VENDOR_ID_CFG)
    #error "VENDOR ID for Dio_Siu.c and Dio_Cfg.h is different"
#endif
/* Dio_Cfg.h version check end */

/*=================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
=================================================================================================*/


/*=================================================================================================
*                                       LOCAL MACROS
=================================================================================================*/

/* @violates @ref Dio_Siu_C_REF_4 MISRA 2004 Advisory Rule 19.7, Function-like macro defined. */
#define SIU_MPGPDO_MULTIPLIER_U32(port)   ((uint32)((port) << 0x2U))
#define SIU_MPGPDO_MASK_SHIFT_U8          ((uint8)16)
#define SIU_MPGPDO_MPPDO_MASK_U32         ((uint32)0x0000FFFFU)
#define SIU_REVERSE_BITS_SHIFT            ((Dio_PortLevelType)1U)
#define SIU_REVERSE_BITS_MASK             ((Dio_PortLevelType)0x1U)
#define SIU_REVERSE_BITS_NUMBER           ((Dio_PortLevelType)((sizeof(Dio_PortLevelType) << 0x3U) - 1U))

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
*                                      GLOBAL VARIABLES
=================================================================================================*/


/*=================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
=================================================================================================*/

#define DIO_START_SEC_CODE
/* @violates @ref Dio_Siu_C_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file */
#include "MemMap.h"

#if (STD_ON == DIO_REVERSEPORTBITS)
static FUNC(Dio_PortLevelType, DIO_CODE) Dio_Siu_ReverseBits
(
    VAR(Dio_PortLevelType, AUTOMATIC) Level
);
#endif /* (STD_ON == DIO_REVERSEPORTBITS) */

/*=================================================================================================
*                                       LOCAL FUNCTIONS
=================================================================================================*/

/*================================================================================================*/

#if (STD_ON == DIO_REVERSEPORTBITS)
/*================================================================================================*/
/**
* @brief          Reverses bits.
*
* @param[in]      Level       Bits to be reversed.
*
* @return         The reversed bits.
*
* @pre            This function can be used only if @p DIO_REVERSEPORTBITS is
*                 enabled.
*/
static FUNC(Dio_PortLevelType, DIO_CODE) Dio_Siu_ReverseBits
(
    VAR(Dio_PortLevelType, AUTOMATIC) Level
)
{
    /* RevLevel will be reversed bits of Level */
    VAR(Dio_PortLevelType, AUTOMATIC) RevLevel = Level;
    VAR(Dio_PortLevelType, AUTOMATIC) NumShifts = SIU_REVERSE_BITS_NUMBER; /* number of shifts needed due to trailing 0s */

    Level = (Dio_PortLevelType)(Level >> SIU_REVERSE_BITS_SHIFT);

    for (; (Dio_PortLevelType)STD_LOW != Level; Level = (Dio_PortLevelType)(Level >> SIU_REVERSE_BITS_SHIFT))
    {
        RevLevel = (Dio_PortLevelType)(RevLevel << SIU_REVERSE_BITS_SHIFT);
        RevLevel = (Dio_PortLevelType)(RevLevel | ((Dio_PortLevelType)(Level & SIU_REVERSE_BITS_MASK)));
        NumShifts--;
    }
    RevLevel = (Dio_PortLevelType)((uint32)RevLevel << NumShifts); /* Remaining shifts when Level's highest bits are zero */

    return RevLevel;
}
#endif /* (STD_ON == DIO_REVERSEPORTBITS) */

/*=================================================================================================
*                                       GLOBAL FUNCTIONS
=================================================================================================*/

/*===============================================================================================*/
/**
* @brief          Returns the value of the specified DIO channel.
* @details        This function returns the value of the specified DIO channel.
*
* @param[in]      ChannelId   Specifies the required channel id.
*
* @return                     Returns the level of the corresponding pin as
*                             @p STD_HIGH or @p STD_LOW.
* @retval STD_HIGH            The logical level of the corresponding pin is 1.
* @retval STD_LOW             The logical level of the corresponding Pin is 0.
*/
FUNC (Dio_LevelType, DIO_CODE) Dio_Siu_ReadChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId
)
{
    VAR(Dio_LevelType, AUTOMATIC) ChannelLevel = (Dio_LevelType) STD_LOW;

    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    ChannelLevel = (Dio_LevelType)(REG_READ8(SIU_GPDI_ADDR8(ChannelId)));

    return ChannelLevel;
}

/*===============================================================================================*/
/**
* @brief          Sets the level of a channel.
* @details        If the specified channel is configured as an output channel,
*                 this function shall set the specified level on the
*                 specified channel. If the specified channel is configured
*                 as an input channel, this function shall have no influence
*                 on the physical output and on the result of the next read
*                 service.
*
* @param[in]      ChannelId   Specifies the required channel id.
* @param[in]      Level       Specifies the channel desired level.
*/
FUNC (void, DIO_CODE) Dio_Siu_WriteChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId,
    CONST(Dio_LevelType,   AUTOMATIC) Level
)
{
    SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_01();
    
    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    REG_WRITE8(SIU_GPDO_ADDR8(ChannelId), Level);
    
    SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_01();
 }

#if (STD_ON == DIO_FLIP_CHANNEL_API)
/*===============================================================================================*/
/**
* @brief          Inverts the level of a channel.
* @details        If the specified channel is configured as an output channel,
*                 this function shall invert the level of the specified
*                 channel. If the specified channel is configured as an
*                 input channel, this function shall have no influence
*                 on the physical output and on the result of the next
*                 read service.
*
* @param[in]      ChannelId   Specifies the required channel id.
*
* @return                     Returns the level of the corresponding pin as
*                             @p STD_HIGH or @p STD_LOW.
* @retval STD_HIGH            The logical level of the corresponding pin is 1.
* @retval STD_LOW             The logical level of the corresponding Pin is 0.
*
* @pre            This function can be used only if @p DIO_FLIP_CHANNEL_API
*                 has been enabled.

*/
FUNC(Dio_LevelType, DIO_CODE) Dio_Siu_FlipChannel
(
    CONST(Dio_ChannelType, AUTOMATIC) ChannelId
)
{
    VAR(Dio_LevelType, AUTOMATIC) ChannelLevel = (Dio_LevelType)STD_LOW;

    SchM_Enter_Dio_DIO_EXCLUSIVE_AREA_00();

    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    if ((Dio_LevelType)STD_LOW == (Dio_LevelType)(REG_READ8(SIU_GPDO_ADDR8(ChannelId))))
    {
        ChannelLevel = (Dio_LevelType)STD_HIGH;
    }
    else
    {
        ChannelLevel = (Dio_LevelType)STD_LOW;
    }

    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    REG_WRITE8(SIU_GPDO_ADDR8(ChannelId), ChannelLevel);

    SchM_Exit_Dio_DIO_EXCLUSIVE_AREA_00();

    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    ChannelLevel = (Dio_LevelType)(REG_READ8(SIU_GPDI_ADDR8(ChannelId)));
   return ChannelLevel;
}
#endif /* (STD_ON == DIO_FLIP_CHANNEL_API) */

/*===============================================================================================*/
/**
* @brief          Returns the level of all channels of specified port.
* @details        This function will return the level of all channels
*                 belonging to the specified port.
*
* @param[in]      PortId      Specifies the required port id.
*
* @return                     Levels of all channels of specified port.
*/
FUNC (Dio_PortLevelType, DIO_CODE) Dio_Siu_ReadPort
(
    CONST(Dio_PortType, AUTOMATIC) PortId
)
{
    VAR(Dio_PortLevelType, AUTOMATIC) PortLevel = (Dio_PortLevelType)STD_LOW;

    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    PortLevel = (Dio_PortLevelType)(REG_READ16(SIU_PGPDI_ADDR32((uint32)PortId)));
#if (STD_ON == DIO_READZERO_UNDEFINEDPORTS)
    PortLevel = (Dio_PortLevelType)(PortLevel & Dio_aAvailablePinsForRead[PortId]);
#endif
#if (STD_ON == DIO_REVERSEPORTBITS)
    PortLevel = (Dio_PortLevelType)(Dio_Siu_ReverseBits(PortLevel));
#endif
     return PortLevel;
}

/*===============================================================================================*/
/**
* @brief          Sets the value of a port.
* @details        This function will set the specified value on the specified
*                 port.
*
* @param[in]      PortId      Specifies the required port id.
* @param[in]      Level       Specifies the required levels for the port pins.
*/
FUNC (void, DIO_CODE) Dio_Siu_WritePort
(
    CONST(Dio_PortType,      AUTOMATIC) PortId,
    CONST(Dio_PortLevelType, AUTOMATIC) Level
)
{
    VAR(Dio_PortLevelType, AUTOMATIC) CrtLevel = Level;

#if (STD_ON == DIO_REVERSEPORTBITS)
    CrtLevel = (Dio_PortLevelType)(Dio_Siu_ReverseBits(CrtLevel));
#endif

    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    REG_WRITE16(SIU_PGPDO_ADDR32((uint32)PortId), CrtLevel);
 }

/*===============================================================================================*/
/**
* @brief          This service reads a subset of the adjoining bits of a port.
* @details        This function will read a subset of adjoining bits of a
*                 port (channel group).
*
* @param[in]      pChannelGroupIdPtr Pointer to the channel group.
* @return                     The channel group levels.
*/
FUNC (Dio_PortLevelType, DIO_CODE) Dio_Siu_ReadChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupIdPtr
)
{
    VAR(Dio_PortLevelType, AUTOMATIC) PortLevel = (Dio_PortLevelType)STD_LOW;

#if (STD_ON == DIO_REVERSEPORTBITS)
    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    * @violates @ref Dio_Siu_C_REF_7 The operator << was used.
    */
    PortLevel = (Dio_PortLevelType)((REG_READ16(SIU_PGPDI_ADDR32((uint32)(pChannelGroupIdPtr->port))) & (pChannelGroupIdPtr->mask)) << (pChannelGroupIdPtr->offset));
    PortLevel = (Dio_PortLevelType)(Dio_Siu_ReverseBits(PortLevel));
#else
    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    PortLevel = (Dio_PortLevelType)((REG_READ16(SIU_PGPDI_ADDR32((uint32)(pChannelGroupIdPtr->port))) & (pChannelGroupIdPtr->mask)) >> (pChannelGroupIdPtr->offset));
#endif
    return PortLevel;
}

/*===============================================================================================*/
/**
* @brief          Sets a subset of the adjoining bits of a port to the
*                 specified levels.
* @details        This function will set a subset of adjoining bits of a port
*                 (channel group) to the specified levels without changing
*                 the remaining channels of the port and channels that
*                 are configured as input.
*                 This function will do the masking of the channels and will
*                 do the shifting so that the values written by the function
*                 are aligned to the LSB.
*
* @param[in]      pChannelGroupIdPtr Pointer to the channel group.
* @param[in]      Level       Desired levels for the channel group.
*/
FUNC (void, DIO_CODE) Dio_Siu_WriteChannelGroup
(
    P2CONST(Dio_ChannelGroupType, AUTOMATIC, DIO_APPL_CONST) pChannelGroupIdPtr,
    CONST  (Dio_PortLevelType,    AUTOMATIC)                 Level
)
{
    VAR(uint32, AUTOMATIC) u32Value;

#if (STD_ON == DIO_REVERSEPORTBITS)
    u32Value = ((((uint32)(Dio_Siu_ReverseBits(Level)) >> (pChannelGroupIdPtr->offset)) & (SIU_MPGPDO_MPPDO_MASK_U32)) | (((uint32)(pChannelGroupIdPtr->mask) << (SIU_MPGPDO_MASK_SHIFT_U8))));
#else
    u32Value = ((((uint32)(Level) << (pChannelGroupIdPtr->offset)) & (SIU_MPGPDO_MPPDO_MASK_U32)) | (((uint32)(pChannelGroupIdPtr->mask) << (SIU_MPGPDO_MASK_SHIFT_U8))));
#endif

    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    REG_WRITE32(SIU_MPGPDO_ADDR32(SIU_MPGPDO_MULTIPLIER_U32((uint32)pChannelGroupIdPtr->port)), u32Value);
}

#if ((STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__))
/*===============================================================================================*/
/**
* @brief          DIO Mask write port using mask.
* @details        Writes a DIO port with masked value.
*
* @param[in]      PortId      Specifies the required port id.
* @param[in]      Level       Specifies the required levels for the port pins.
* @param[in]      Mask        Specifies the Mask value of the port.
*
* @pre            This function can be used only if @p DIO_MASKEDWRITEPORT_API
*                 has been enabled.
*/

FUNC (void, DIO_CODE) Dio_Siu_MaskedWritePort
(
    CONST(Dio_PortType,      AUTOMATIC) PortId,
    CONST(Dio_PortLevelType, AUTOMATIC) Level,
    CONST(Dio_PortLevelType, AUTOMATIC) Mask
)
{
    VAR(uint32, AUTOMATIC) u32Value;

    u32Value = (((uint32) Mask << (SIU_MPGPDO_MASK_SHIFT_U8)) | (uint32)Level);
    /** 
    * @violates @ref Dio_Siu_C_REF_2 Cast from unsigned long to pointer.
    * @violates @ref Dio_Siu_C_REF_6 A cast should not be performed between a pointer type and an integral type.
    */
    REG_WRITE32(SIU_MPGPDO_ADDR32(SIU_MPGPDO_MULTIPLIER_U32((uint32)PortId)), u32Value);
}
#endif /* (STD_ON == DIO_MASKEDWRITEPORT_API) || defined(__DOXYGEN__) */

#define DIO_STOP_SEC_CODE
/* @violates @ref Dio_Siu_C_REF_5 Only preprocessor statements and comments before '#include' */
/* @violates @ref Dio_Siu_C_REF_1 Repeated include file */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif
/** @} */
