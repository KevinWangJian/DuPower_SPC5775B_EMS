/**
*   @file    Mcu_SIU.c
*   @version 1.0.1
*
*   @brief   AUTOSAR Mcu - Power Control Unit module functions implementation.
*   @details Specific functions for SIU configuration and control.
*
*   @addtogroup MCU
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MC
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_HF5_ASR_REL_4_0_REV_0003_20190514
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/


#ifdef __cplusplus
extern "C"
{
#endif


/**
* @page misra_violations MISRA-C:2004 violations
*
* @section Mcu_SIU_c_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file MemMap.h,  Precautions shall be
* taken in order to prevent the contents of a header file being included twice This is not a
* violation since all header files are protected against multiple inclusions
*
* @section Mcu_SIU_c_REF_2
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before
* '#include' MemMap.h included after each section define in order to set the current memory section
*
* @section Mcu_SIU_c_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure that 31
* character significance and case sensitivity are supported for external identifiers. The defines
* are validated.
*
* @section Mcu_SIU_c_REF_4
* Violates MISRA 2004 Required Rule 11.1, Conversions shall not be performed between a pointer to a
* function and any type other than an integral type. Appears when accessing memory-mapped registers.
*
* @section Mcu_SIU_c_REF_5
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects or functions
* at file scope shall have internal linkage unless external linkage is required.
*
* @section Mcu_SIU_c_REF_6
* Violates MISRA 2004 Advisory Rule 11.3, A cast should not be performed between
* a pointer type and an integral type.
* The cast can not be avoided as it is used to access memory mapped registers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
* on the significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*/


/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Mcu_SIU.h"

#if (MCU_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (MCU_DEV_ERROR_DETECT == STD_ON) */

#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#include "Dem.h"
#endif /* (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF) */

#define USER_MODE_REG_PROT_ENABLED ( MCU_USER_MODE_REG_PROT_ENABLED )
#include "SilRegMacros.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=================================================================================================*/
#define MCU_SIU_VENDOR_ID_C                      43
/** @violates @ref Mcu_SIU_c_REF_3 The compiler/linker shall be checked ... */
#define MCU_SIU_AR_RELEASE_MAJOR_VERSION_C       4
/** @violates @ref Mcu_SIU_c_REF_3 The compiler/linker shall be checked ... */
#define MCU_SIU_AR_RELEASE_MINOR_VERSION_C       0
/** @violates @ref Mcu_SIU_c_REF_3 The compiler/linker shall be checked ... */
#define MCU_SIU_AR_RELEASE_REVISION_VERSION_C    3
#define MCU_SIU_SW_MAJOR_VERSION_C               1
#define MCU_SIU_SW_MINOR_VERSION_C               0
#define MCU_SIU_SW_PATCH_VERSION_C               1


/*==================================================================================================
                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if source file and Mcu_SIU header file are of the same vendor. */
#if (MCU_SIU_VENDOR_ID_C != MCU_SIU_VENDOR_ID)
    #error "Mcu_SIU.c and Mcu_SIU.h have different Vendor IDs."
#endif
#ifdef CHECK_AUTOSAR_VERSION
  /* Check if source file and Mcu_SIU header file are of the same Autosar version. */
  #if ( (MCU_SIU_AR_RELEASE_MAJOR_VERSION_C != MCU_SIU_AR_RELEASE_MAJOR_VERSION) || \
        (MCU_SIU_AR_RELEASE_MINOR_VERSION_C != MCU_SIU_AR_RELEASE_MINOR_VERSION) || \
        (MCU_SIU_AR_RELEASE_REVISION_VERSION_C != MCU_SIU_AR_RELEASE_REVISION_VERSION) \
      )
        #error "AutoSar Version Numbers of Mcu_SIU.c and Mcu_SIU.h are different."
  #endif
#endif
/* Check if source file and Mcu_SIU header file are of the same Software version. */
#if ( (MCU_SIU_SW_MAJOR_VERSION_C != MCU_SIU_SW_MAJOR_VERSION) || \
      (MCU_SIU_SW_MINOR_VERSION_C != MCU_SIU_SW_MINOR_VERSION) || \
      (MCU_SIU_SW_PATCH_VERSION_C != MCU_SIU_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of Mcu_SIU.c and Mcu_SIU.h are different."
#endif

/* Check if current file and DET header file are of the same version */
#if (MCU_DEV_ERROR_DETECT == STD_ON)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SIU_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SIU_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SIU.c and Det.h are different"
    #endif
#endif
#endif

/* Check if current file and DEM header file are of the same version */
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SIU_AR_RELEASE_MAJOR_VERSION_C != DEM_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SIU_AR_RELEASE_MINOR_VERSION_C != DEM_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SIU.c and Dem.h are different"
    #endif
#endif
#endif

/* Check if current file and SilRegMacros header file are of the same Autosar version */
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    #if ((MCU_SIU_AR_RELEASE_MAJOR_VERSION_C != SILREGMACROS_AR_RELEASE_MAJOR_VERSION) || \
         (MCU_SIU_AR_RELEASE_MINOR_VERSION_C != SILREGMACROS_AR_RELEASE_MINOR_VERSION) \
        )
        #error "AutoSar Version Numbers of Mcu_SIU.c and SilRegMacros.h are different"
    #endif
#endif

/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#define MCU_START_SEC_VAR_INIT_32
/**
 * @violates @ref Mcu_SIU_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
 * @violates @ref Mcu_SIU_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
 * statements and comments before '#include'
 */
#include "MemMap.h"

static VAR(uint32, MCU_VAR) Mcu_u32ResetStatus = 0x00U;

#define MCU_STOP_SEC_VAR_INIT_32
/**
 * @violates @ref Mcu_SIU_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
 * @violates @ref Mcu_SIU_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor
 * statements and comments before '#include'
 */
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
#define MCU_START_SEC_CODE
/**
* @violates @ref Mcu_SIU_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_SIU_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor statements and
* comments before '#include'
*/
#include "MemMap.h"

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

#if (MCU_GET_MIDR_API == STD_ON)
/**
* @brief            This function gets the value from MIDR
*/
FUNC( void, MCU_CODE) Mcu_SIU_GetMidrStructure(P2VAR(Mcu_MidrReturnType, AUTOMATIC, MCU_APPL_DATA) pMidr)
{
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from pointer to integer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    pMidr->u32Midr = REG_READ32( SIU_MIDR_ADDR32 );
}
#endif /* (MCU_GET_MIDR_API == STD_ON) */

#if (MCU_INIT_CLOCK == STD_ON)
/**
* @brief            This function will configure the system clock tree writing SIU_SYSDIV
*
* @details          This function will configure the system clock switch(es) and dividers
*
*/
FUNC( void, MCU_CODE) Mcu_SIU_SystemClockConfig(VAR( uint32, AUTOMATIC) u32SystemClockConfig)
{   
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from pointer to integer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32(SIU_SYSDIV_ADDR32, u32SystemClockConfig); 
}

#if (IPV_SIU == IPV_SIU_00_02_09_00)
/**
* @brief            This function will configure the external clock
*
* @details          This function will configure the external clock switch(es) and dividers
*
*/
FUNC( void, MCU_CODE) Mcu_SIU_ExternalClockConfig(VAR( uint32, AUTOMATIC) u32ExternalClockConfig)
{   
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from pointer to integer */
    REG_WRITE32(SIU_ECCR_ADDR32, u32ExternalClockConfig); 
}
#else
/**
* @brief            This function will configure progressive clock switching
*/
FUNC( void, MCU_CODE) Mcu_SIU_ProgClockSwitchConfig(P2CONST( Mcu_SIU_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) pClockConfigPtr)
{
    /* local vars */
    VAR(uint32, AUTOMATIC) u32Counter;

    /* this register is always here, so no need to add it to the array */
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from pointer to integer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32( PCS_SDUR_ADDR32, pClockConfigPtr->u32ProgClkSwitch );

    /* now write the available PCS registers */
    for ( u32Counter = (uint32)0x00U; u32Counter < (uint32)(pClockConfigPtr->u8NoOfProgSwitchUnderMcuControl); u32Counter++)
    {
        /* for all pairs write them to harware */
        /** @violates @ref Mcu_SIU_c_REF_4 Conversion from pointer to integer */
        /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
        REG_WRITE32 \
        ( \
            (*pClockConfigPtr->apPcsClockConfig)[u32Counter].u32RegisterAddr,\
            (*pClockConfigPtr->apPcsClockConfig)[u32Counter].u32RegisterData \
        );
    }
}

/**
* @brief            This function will configure the peripheral clock tree
*
* @details          This function will configure the peripheral clock switches and dividers
*
*/
FUNC( void, MCU_CODE) Mcu_SIU_AuxClockConfig(P2CONST( Mcu_SIU_ClockConfigType, AUTOMATIC, MCU_APPL_DATA) pClockConfigPtr)
{
    /* local vars */
    VAR(uint32, AUTOMATIC) u32Counter;
    
    /* now write the available registers */
    for ( u32Counter = (uint32)0x00U; u32Counter < (uint32)(pClockConfigPtr->u8NoAuxClockUnderMcuControl); u32Counter++)
    {       
        /** @violates @ref Mcu_SIU_c_REF_4 Conversion from pointer to integer */
        /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
        REG_WRITE32 \
        ( \
            (*pClockConfigPtr->apAuxClockConfig)[u32Counter].u32RegisterAddr,\
            (*pClockConfigPtr->apAuxClockConfig)[u32Counter].u32RegisterData \
        );
    }
}
#endif /* (IPV_SIU == IPV_SIU_00_02_09_00) */
#endif /* (MCU_INIT_CLOCK == STD_ON) */


/**
* @brief            This function initializes the Reset parameters.
* @details          Conigures the threshold reset value.
*                   Called by:
*                       - Mcu_IPW_Init() from IPW.
*
* @param[in]        pConfigPtr   Pointer to the Mcu_SIU configuration structure.
*
* @return           void
*
*/
/** @violates @ref Mcu_SIU_c_REF_5 Violates MISRA 2004 Required Rule 8.10, global declaration of
  * function */
FUNC( void, MCU_CODE) Mcu_SIU_ResetInit(P2CONST( Mcu_SIU_ResetConfigType, AUTOMATIC, MCU_APPL_DATA) pConfigPtr)
{
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32(SIU_RCR_ADDR32, (uint32)(pConfigPtr->u8ThresholdReset & SIU_RCR_RET_MASK32));
}

/**
* @brief            This function returns the Reset reason.
* @details          This routine returns the Reset reason that is read from the hardware.
*                   Called by:
*                       - Mcu_IPW_GetResetReason() from IPW.
*
* @return           Reason of the Reset event.
*
* @note             The User should ensure that the reset reason is cleared once it has been read
*                   out to avoid multiple reset reasons. The function Mcu_GetResetReason shall
*                   return MCU_RESET_UNDEFINED if this function is called prior to calling of the
*                   function Mcu_Init, and if supported by the hardware.
*/
FUNC( Mcu_ResetType, MCU_CODE) Mcu_SIU_GetResetReason( VAR( void, AUTOMATIC))
{
    /* Code for the Reset event returned by this function. */
    VAR( Mcu_ResetType, AUTOMATIC) eResetReason = MCU_NO_RESET_REASON;
    /* Temporary variable for SIU_RSR register value. */
    VAR( uint32, AUTOMATIC) u32RegValue;
    VAR( uint32, AUTOMATIC) u32ActiveValue;
    VAR( uint32, AUTOMATIC) u32Index;
    VAR( uint32, AUTOMATIC) u32DynamicMask;
    VAR( uint32, AUTOMATIC) u32Position = (uint32)0x00U;
    VAR( uint32, AUTOMATIC) u32NumberOfFlags = 0U;
    
    /* Check "Destructive Reset Reason" from DES Status Register. */
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    u32RegValue = (uint32)REG_READ32(SIU_RSR_ADDR32) & SIU_RSR_RESET_STATUS_MASK32;
    
    /* store the content of RSR */
    if ((uint32)0x00U != u32RegValue)
    {
        Mcu_u32ResetStatus = u32RegValue;        
    }
    
    u32ActiveValue = Mcu_u32ResetStatus;
    
    if((uint32)0x00 != u32ActiveValue)
    {
        for (u32Index = 0x00U; u32Index < 0x20U; u32Index++)
        {
            u32DynamicMask = ((uint32)0x01U << u32Index);
            if ((uint32)0x00U != (u32DynamicMask & SIU_RSR_RESET_STATUS_MASK32))
            {
                if ((uint32)0x00U != (u32DynamicMask & u32ActiveValue))
                {
                    eResetReason = (Mcu_ResetType)u32Position;
                    u32NumberOfFlags++;
                    /* 
                      MCU_MULTIPLE_RESET_REASON returned if more than one reset reason 
                      in this case use function Mcu_GetRawValue to determine. 
                    */
                    if (u32NumberOfFlags >= (uint32)2)
                    {
                        eResetReason = MCU_MULTIPLE_RESET_REASON;
                        break;
                    }

                }
                u32Position++;
            }
        }
         /* clear all reset reason bits after reading out */
        /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
        /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
        REG_WRITE32(SIU_RSR_ADDR32, (uint32)(u32RegValue & SIU_RSR_RESET_STATUS_MASK32));
    }
    
    return (Mcu_ResetType)eResetReason;
}

/**
* @brief            This function returns the Raw Reset value.
* @details          This routine returns the Raw Reset value that is read from the hardware.
*                   Called by:
*                       - Mcu_IPW_GetResetRawValue() from IPW.
*
* @return           Register value with the Reset status.
* @retval           uint32   Code of the Raw reset value.
*
* @note             The User should ensure that the reset reason is cleared once it has been read
*                   out to avoid multiple reset reasons.
*
*/
FUNC( Mcu_RawResetType, MCU_CODE) Mcu_SIU_GetResetRawValue( VAR( void, AUTOMATIC))
{
   /* Temporary variable for DES and FES registers value. */
    VAR( uint32, AUTOMATIC) u32RawReset;
    VAR( uint32, AUTOMATIC) u32RegValue;

    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    u32RegValue = REG_READ32(SIU_RSR_ADDR32) & SIU_RSR_RESET_STATUS_MASK32;
    
    if ((uint32)0x00U != u32RegValue)
    {
        Mcu_u32ResetStatus = u32RegValue;
    }
    
    u32RawReset = Mcu_u32ResetStatus;
    
    /* clear all reset reason bits after reading out */
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32(SIU_RSR_ADDR32, (uint32)(u32RegValue));
    
    return (Mcu_RawResetType)u32RawReset;
}

#if (MCU_PERFORM_RESET_API == STD_ON)
/**
* @brief            This function performs a microcontroller reset.
* @details          This function performs a microcontroller reset by using the hardware feature of
*                   the microcontroller.
*                   Called by:
*                       - Mcu_IPW_PerformReset() from IPW.
*
* @param[in]        pConfigPtr  Pointer to the SIU reset configuration structure.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_SIU_PerformReset(P2CONST( Mcu_SIU_ResetConfigType, AUTOMATIC, MCU_APPL_DATA) pConfigPtr)
{

    switch (pConfigPtr->Mcu_eResetType)
    {
        case (MCU_SOFT_SYSTEM_RESET):
        {
            /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
            /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
            REG_WRITE32(SIU_SRCR_ADDR32, SIU_SRCR_SOFTWARE_SYSTEM_RESET_U32);
            break;
        }
        case (MCU_SOFT_EXTERNAL_RESET):
        {
            /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
            /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
            REG_WRITE32(SIU_SRCR_ADDR32, SIU_SRCR_SOFTWARE_EXTERNAL_RESET_U32);
            break;
        }
        default:
        {
            /* Default case - should never enter here. */
            break;
        }
    }
}
#endif /* (MCU_PERFORM_RESET_API == STD_ON) */

/**
* @brief            This function initializes the mode structure.
* @details          This function initializes the mode structure by configuring the 
*                   SIU_HLT1 and SIU_HLT2 registers.
*
*                   Called by:
*                       - Mcu_IPW_SetMode() from IPW.
*
* @param[in]        pModeConfigPtr   Pointer to mode configuration structure.
*
* @return           void
*
*/
FUNC( void, MCU_CODE) Mcu_SIU_ModeConfig(P2CONST( Mcu_ModeConfigType, AUTOMATIC, MCU_APPL_DATA) pModeConfigPtr)
{
    /* Time out value for specific wait operations. */
    VAR( uint32, AUTOMATIC) u32TimeOut = MCU_TIMEOUT_LOOPS;
#if (MCU_ENTER_LOW_POWER_MODE == STD_ON)
    VAR( uint32, AUTOMATIC) u32CoresToHalt;
#endif
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    VAR( uint32, AUTOMATIC) u32PeripheralsToHalt;
    VAR( uint32, AUTOMATIC) u32PeripheralsHalted;
#else
    VAR( uint32, AUTOMATIC) u32PeripheralsToHalt1;
    VAR( uint32, AUTOMATIC) u32PeripheralsHalted1;
    VAR( uint32, AUTOMATIC) u32PeripheralsHalted2;
#endif

#if (IPV_SIU == IPV_SIU_00_02_09_00)
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    REG_WRITE32(SIU_HLT_ADDR32, (uint32)(pModeConfigPtr->Mcu_HaltRegisterValue));
    
    u32PeripheralsToHalt = pModeConfigPtr->Mcu_HaltRegisterValue & ~(SIU_HLT_CORE_MASK32);
    
    do
    {
        u32TimeOut--;

        /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
        u32PeripheralsHalted = (uint32)REG_READ32(SIU_HLTACK_ADDR32) & ~(SIU_HLT_CORE_MASK32);

    } while ((u32TimeOut > (uint32)0x0U) && (u32PeripheralsHalted != u32PeripheralsToHalt));

#else
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32(SIU_RSTVEC0_ADDR32, (uint32)(pModeConfigPtr->Mcu_Core0ResetVectorRegisterValue));    
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32(SIU_RSTVEC1_ADDR32, (uint32)(pModeConfigPtr->Mcu_Core1ResetVectorRegisterValue));

    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32(SIU_HLT1_ADDR32, (uint32)(pModeConfigPtr->Mcu_Halt1RegisterValue));
    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
    /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
    REG_WRITE32(SIU_HLT2_ADDR32, (uint32)(pModeConfigPtr->Mcu_Halt2RegisterValue));
    
    u32PeripheralsToHalt1 = pModeConfigPtr->Mcu_Halt1RegisterValue & ~(SIU_HLT1_CORE0_MASK32 | SIU_HLT1_CORE1_MASK32);
    
    do
    {
        u32TimeOut--;
        
        /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
        /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
        u32PeripheralsHalted1 = (uint32)REG_READ32(SIU_HLTACK1_ADDR32) & ~(SIU_HLTACK1_CORE0_MASK32 | SIU_HLTACK1_CORE1_MASK32);
    
        /** @violates @ref Mcu_SIU_c_REF_4 Conversion from int to pointer */
        /** @violates @ref Mcu_SIU_c_REF_6 A cast should not be performed between */
        u32PeripheralsHalted2 = (uint32)REG_READ32(SIU_HLTACK2_ADDR32);
        
    } while ((u32TimeOut > (uint32)0x0U) && 
             ((u32PeripheralsHalted1 != u32PeripheralsToHalt1) || (u32PeripheralsHalted2 != pModeConfigPtr->Mcu_Halt2RegisterValue))
            );
#endif /* (IPV_SIU == IPV_SIU_00_02_09_00) */


    if ((uint32)0x0U == u32TimeOut)
    {
        /* there is at least one peripheral not halted yet */
#if (MCU_DISABLE_DEM_REPORT_ERROR_STATUS == STD_OFF)
        if ((uint32)STD_ON == Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.state)
        {
            Dem_ReportErrorStatus((Dem_EventIdType)Mcu_pDemCfgPtr->Mcu_E_TimeoutFailureCfg.id, DEM_EVENT_STATUS_FAILED);
        }
#endif
    }
    
#if (MCU_ENTER_LOW_POWER_MODE == STD_ON)
#if (IPV_SIU == IPV_SIU_00_02_09_00)
    u32CoresToHalt = pModeConfigPtr->Mcu_HaltRegisterValue & (SIU_HLT_CORE_MASK32);
#else
    u32CoresToHalt = pModeConfigPtr->Mcu_Halt1RegisterValue & (SIU_HLT1_CORE0_MASK32 | SIU_HLT1_CORE1_MASK32);
#endif

    if (0x00U != u32CoresToHalt)
    {
        /* Enter Wait or Stop mode */
        EXECUTE_WAIT();
    }
#endif
}


#if (IPV_SIU == IPV_SIU_00_02_09_00)
#if ((MCU_GET_PERIPH_STATE_API == STD_ON) || (defined MCU_GET_INTERNAL_STATE))
/**
* @brief            This function returns the peripheral clock state.
* @details          This function returns one peripheral is frozen or active from SIU hw IP.
*                   Called by:
*                       - Mcu_IPW_GetPeripheral_State() from IPW.
*
* @param[in]        Mcu_PeriphId   Peripheral ID based SIU_HLTACK registers.
*
* @return           Status of the peripheral clock.
* @retval           E_OK   Peripheral is active (clocked).
* @retval           E_NOT_OK   Peripheral is not active (not clocked).
*
*/
FUNC(Std_ReturnType, MCU_CODE) Mcu_SIU_GetPeripheralState(VAR(Mcu_PeripheralId, AUTOMATIC) Mcu_PeriphId)
{
    VAR(uint32, AUTOMATIC) u32RegVal;
    VAR(Std_ReturnType, AUTOMATIC) PeripheralStatus = (Std_ReturnType)E_NOT_OK;

    /** @violates @ref Mcu_SIU_c_REF_4 Conversion from integer to pointer */
    u32RegVal = REG_READ32(SIU_HLTACK_ADDR32);
    
    if ((uint32)0x00U == (uint32)(u32RegVal & ((uint32)0x01U << (uint32)Mcu_PeriphId)))
    {
        PeripheralStatus = (Std_ReturnType)E_OK;
    }

    return (Std_ReturnType)PeripheralStatus;
}
#endif /* ((MCU_GET_PERIPH_STATE_API == STD_ON) || (defined MCU_GET_INTERNAL_STATE)) */
#endif /* (IPV_SIU == IPV_SIU_00_02_09_00) */

#define MCU_STOP_SEC_CODE
/**
* @violates @ref Mcu_SIU_c_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
* @violates @ref Mcu_SIU_c_REF_2 MISRA 2004 Advisory Rule 19.1, only preprocessor statements and
* comments before '#include'
*/
#include "MemMap.h"


#ifdef __cplusplus
}
#endif
/** @} */