/**
*   @file    Gpt_Ipw.c
*   @implements    Gpt_Ipw.c_Artifact
*   @version 1.0.1
*
*   @brief   AUTOSAR Gpt - GPT driver source file.
*   @details GPT driver source file, containing the C implementation of functions prototypes that:
*            - are Autosar independent.
*            - are platform dependent.
*
*   @addtogroup GPT_MODULE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : eMios_Stm_Pit
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
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

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
* @section GPT_IPW_C_REF_1
* Violates MISRA 2004 Advisory Rule 19.1, only preprocessor statements and comments before "#include"
* This violation is not fixed since the inclusion of MemMap.h is as per Autosar requirement.
*
* @section GPT_IPW_C_REF_2
* Violates MISRA 2004 Required Rule 19.15, Repeated include file
* This comes from the order of includes in the .c file and from include dependencies. As a safe
* approach, any file must include all its dependencies. Header files are already protected against
* double inclusions.
*
* @section GPT_IPW_C_REF_3
* Violates MISRA 2004 Required Rule 1.4, The compiler/linker shall be checked to ensure
* that 31 character significance and case sensitivity are supported for external identifiers.
* Compilers and linkers checked. Feature is supported
*
* @section GPT_IPW_C_REF_4
* Violates MISRA 2004 Required Rule 1.2, In order receive data from a callee function, it needs
* that a pointer to a local variable shall be passed as parameter to that function.
*
* @section GPT_IPW_C_REF_5
* Violates MISRA 2004 Required Rule 8.10, All declarations and definitions of objects orfunctions
* at file scope shall have internal linkage unless external linkage is required.
*/

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Gpt.h"
#include "Gpt_Ipw.h"
#include "Gpt_eMios.h"
#include "Gpt_Stm.h"
#include "Gpt_Pit.h"

/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define GPT_IPW_VENDOR_ID_C                    43
/** @violates @ref GPT_IPW_C_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define GPT_IPW_AR_RELEASE_MAJOR_VERSION_C     4
/** @violates @ref GPT_IPW_C_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define GPT_IPW_AR_RELEASE_MINOR_VERSION_C     0
/** @violates @ref GPT_IPW_C_REF_3 MISRA 2004 Rule 1.4, The compiler/linker shall be checked to ensure that 31 character
*   significance and case sensitivity are supported for external identifiers. */
#define GPT_IPW_AR_RELEASE_REVISION_VERSION_C  3
#define GPT_IPW_SW_MAJOR_VERSION_C             1
#define GPT_IPW_SW_MINOR_VERSION_C             0
#define GPT_IPW_SW_PATCH_VERSION_C             1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
#if (GPT_IPW_VENDOR_ID_C != GPT_VENDOR_ID)
    #error "Gpt_Ipw.c and Gpt.h have different vendor ids"
#endif
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_C != GPT_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_C != GPT_AR_RELEASE_MINOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_C != GPT_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_Ipw.c and Gpt.h are different"
#endif
#if ((GPT_IPW_SW_MAJOR_VERSION_C != GPT_SW_MAJOR_VERSION) || \
     (GPT_IPW_SW_MINOR_VERSION_C != GPT_SW_MINOR_VERSION) || \
     (GPT_IPW_SW_PATCH_VERSION_C != GPT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt_Ipw.c and Gpt.h are different"
#endif

#if (GPT_IPW_VENDOR_ID_C != GPT_IPW_VENDOR_ID)
    #error "Gpt_Ipw.c and Gpt_Ipw.h have different vendor ids"
#endif
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_C != GPT_IPW_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_C != GPT_IPW_AR_RELEASE_MINOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_C != GPT_IPW_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_Ipw.c and Gpt_Ipw.h are different"
#endif
#if ((GPT_IPW_SW_MAJOR_VERSION_C != GPT_IPW_SW_MAJOR_VERSION) || \
     (GPT_IPW_SW_MINOR_VERSION_C != GPT_IPW_SW_MINOR_VERSION) || \
     (GPT_IPW_SW_PATCH_VERSION_C != GPT_IPW_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt_Ipw.c and Gpt_Ipw.h are different"
#endif

#if (GPT_IPW_VENDOR_ID_C != GPT_EMIOS_VENDOR_ID)
    #error "Gpt_Ipw.c and Gpt_eMios.h have different vendor ids"
#endif
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_C != GPT_EMIOS_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_C != GPT_EMIOS_AR_RELEASE_MINOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_C != GPT_EMIOS_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_Ipw.c and Gpt_eMios.h are different"
#endif
#if ((GPT_IPW_SW_MAJOR_VERSION_C != GPT_EMIOS_SW_MAJOR_VERSION) || \
     (GPT_IPW_SW_MINOR_VERSION_C != GPT_EMIOS_SW_MINOR_VERSION) || \
     (GPT_IPW_SW_PATCH_VERSION_C != GPT_EMIOS_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt_Ipw.c and Gpt_eMios.h are different"
#endif

#if (GPT_IPW_VENDOR_ID_C != GPT_STM_VENDOR_ID)
    #error "Gpt_Ipw.c and Gpt_Stm.h have different vendor ids"
#endif
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_C != GPT_STM_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_C != GPT_STM_AR_RELEASE_MINOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_C != GPT_STM_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_Ipw.c and Gpt_Stm.h are different"
#endif
#if ((GPT_IPW_SW_MAJOR_VERSION_C != GPT_STM_SW_MAJOR_VERSION) || \
     (GPT_IPW_SW_MINOR_VERSION_C != GPT_STM_SW_MINOR_VERSION) || \
     (GPT_IPW_SW_PATCH_VERSION_C != GPT_STM_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt_Ipw.c and Gpt_Stm.h are different"
#endif

#if (GPT_IPW_VENDOR_ID_C != GPT_PIT_VENDOR_ID)
    #error "Gpt_Ipw.c and Gpt_Pit.h have different vendor ids"
#endif
#if ((GPT_IPW_AR_RELEASE_MAJOR_VERSION_C != GPT_PIT_AR_RELEASE_MAJOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_MINOR_VERSION_C != GPT_PIT_AR_RELEASE_MINOR_VERSION) || \
     (GPT_IPW_AR_RELEASE_REVISION_VERSION_C != GPT_PIT_AR_RELEASE_REVISION_VERSION))
    #error "AutoSar Version Numbers of Gpt_Ipw.c and Gpt_Pit.h are different"
#endif
#if ((GPT_IPW_SW_MAJOR_VERSION_C != GPT_PIT_SW_MAJOR_VERSION) || \
     (GPT_IPW_SW_MINOR_VERSION_C != GPT_PIT_SW_MINOR_VERSION) || \
     (GPT_IPW_SW_PATCH_VERSION_C != GPT_PIT_SW_PATCH_VERSION))
    #error "Software Version Numbers of Gpt_Ipw.c and Gpt_Pit.h are different"
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
#define GPT_START_SEC_CODE
/** @violates @ref GPT_IPW_C_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*================================================================================================*/
/**
* @brief   Gpt driver Autosar independent and IP dependent initialization function.
* @details This function is called once for each channel in the used configuration.
*          It determines the type of the HW channel (e.g. eMios, STM,etc...) and calls the
*          appropriate IP function in order to initializes the hardware timer.
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
*/
FUNC (void, GPT_CODE) Gpt_Ipw_Init(P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig)
{
    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            Gpt_eMios_Init(pHwChannelConfig->Gpt_u8HwChannel,pHwChannelConfig->Gpt_uPrescaler,pHwChannelConfig->Gpt_bFreezeEnable);
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
        {
            Gpt_Pit_Init(pHwChannelConfig->Gpt_u8HwChannel,pHwChannelConfig->Gpt_bFreezeEnable);
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
        {
            Gpt_Stm_Init(pHwChannelConfig->Gpt_u8HwChannel,pHwChannelConfig->Gpt_uPrescaler,pHwChannelConfig->Gpt_bFreezeEnable);
        }
        break;
#endif
        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour*/
        break;
    }

    return;
}

/*================================================================================================*/
#if (GPT_CHANGE_NEXT_TIMEOUT_VALUE == STD_ON)
/**
* @brief            Gpt driver Autosar independent and IP dependent function to change Emios
*                   compare register value.
* @details          Calls the Emios function to change the Emios compare register value
*                   at the next match.
*
* @param[in]        pHwChannelConfig    Pointer to the channel configuration structure dependent
*                                       by platform
* @param[in]        value               New Timeout period (in ticks) after which a notification
*                                       shall occur (if enabled).
*
*
* @implements GPT_IPW_ChangeNextTimeoutValue_Activity
* @violates @ref GPT_IPW_C_REF_5 Violates MISRA 2004 Required Rule 8.10 could be made static
*/
FUNC (Std_ReturnType, GPT_CODE) Gpt_Ipw_ChangeNextTimeoutValue
(
    P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig,
    VAR(Gpt_ValueType, AUTOMATIC) value
)
{
    VAR(Std_ReturnType,AUTOMATIC) returnValue = (Std_ReturnType)E_NOT_OK;

#if (GPT_EMIOS_USED == STD_ON)
    if((uint8)GPT_EMIOS_MODULE == pHwChannelConfig->Gpt_u8HwModule)
    {
        Gpt_eMios_ChangeNextTimeoutValue(pHwChannelConfig->Gpt_u8HwChannel, (uint16)value);
        returnValue =(Std_ReturnType)E_OK;
    }
#endif /*GPT_EMIOS_USED == STD_ON*/

#if (GPT_PIT_USED == STD_ON)
    if((uint8)GPT_PIT_MODULE == pHwChannelConfig->Gpt_u8HwModule)
    {
        Gpt_Pit_ChangeNextTimeoutValue(pHwChannelConfig->Gpt_u8HwChannel, (uint32)value);
        returnValue =(Std_ReturnType)E_OK;
    }
#endif
    return returnValue;
}
#endif /* GPT_CHANGE_NEXT_TIMEOUT_VALUE == STD_ON */
/*================================================================================================*/
/**
* @brief   Gpt driver Autosar independent and IP dependent function for fetching the elapsed timer value.
* @details It determines the type of the HW channel (e.g. eMios, STM,etc...) and calls the
*          appropriate IP function for reading the elapsed timer value from the HW.
*
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
* @param[in]     uTargetTime         Target time value
* @param[out]  pbReturnChannelOverflow  Rollover status flag value of the hardware timer channel
*
*/
FUNC (Gpt_ValueType, GPT_CODE) Gpt_Ipw_GetTimeElapsed(P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig,
                                                      P2VAR(Gpt_HwChannelInfoType, AUTOMATIC,GPT_APPL_DATA) pReturnHwChannelInfo
                                                      )
{
    VAR(uint32, AUTOMATIC) u32ReturnValue = 0U;

    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            u32ReturnValue=Gpt_eMios_GetTimeElapsed(pHwChannelConfig->Gpt_u8HwChannel, &(pReturnHwChannelInfo->bChannelRollover), &(pReturnHwChannelInfo->uTargetTime));
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
        {
            u32ReturnValue=Gpt_Pit_GetTimeElapsed(pHwChannelConfig->Gpt_u8HwChannel, &(pReturnHwChannelInfo->bChannelRollover), &(pReturnHwChannelInfo->uTargetTime));
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
        {
            u32ReturnValue=Gpt_Stm_GetTimeElapsed(pHwChannelConfig->Gpt_u8HwChannel, &(pReturnHwChannelInfo->bChannelRollover),&(pReturnHwChannelInfo->uTargetTime));
        }
        break;
#endif
        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour*/
        break;
    }

    return((Gpt_ValueType)u32ReturnValue);
}

/*================================================================================================*/
/**
* @brief   Gpt driver Autosar independent and platform dependent function for starting the timer channel.
* @details It checks the type of the HW module (e.g. eMios, STM,etc...), and calls the appropriate
*          IP function for starting the timer channel.
*
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
* @param[in]     uValue         Timeout period (in ticks) after which a notification shall occur (if
*                               enabled).
*/
FUNC (void, GPT_CODE) Gpt_Ipw_StartTimer(P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig,
                                                   VAR(Gpt_ValueType, AUTOMATIC) uValue
                                                   )
{
    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            Gpt_eMios_StartTimer(pHwChannelConfig->Gpt_u8HwChannel, (uint32)uValue);
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
        {
            Gpt_Pit_StartTimer(pHwChannelConfig->Gpt_u8HwChannel, (uint32)uValue);
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
        {
            Gpt_Stm_StartTimer(pHwChannelConfig->Gpt_u8HwChannel, (uint32)uValue);
        }
        break;
#endif
        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour*/
        break;
    }

    return;
}
/*================================================================================================*/
/**
* @brief   Gpt driver Autosar independent and platform dependent function for stopping the timer channel.
* @details It checks the type of the HW module (e.g. eMios, STM,etc...), and calls the appropriate
*          IP function for stopping the timer channel.
*
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
*/
FUNC (void, GPT_CODE) Gpt_Ipw_StopTimer(P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig)
{
    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            Gpt_eMios_StopTimer(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
        {
            Gpt_Pit_StopTimer(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
        {
            Gpt_Stm_StopTimer(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour*/
        break;
    }

    return;
}

/*================================================================================================*/
/**
* @brief   Gpt driver Autosar independent and platform dependent function for enabling hardware timer interrupts.
* @details It checks the type of the HW module (e.g. eMios, STM,etc...), and calls the appropriate
*          IP function for enabling hardware timer interrupts.
*
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
*/
FUNC (void, GPT_CODE) Gpt_Ipw_EnableInterrupt(P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig)
{
    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            Gpt_eMios_EnableInterrupt(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
        {
            Gpt_Pit_EnableInterrupt(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
            /*For a STM enabled channel the interrupts are allways activated*/
        break;
#endif

        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour */
        break;
    }

    return;
}

/*================================================================================================*/
#if (GPT_DEINIT_API == STD_ON)
/**
* @brief   Gpt driver Autosar independent and IP dependent de-initialization function.
* @details This function is called for each  channel from the current configuration.
*          It determines the type of the HW channel (e.g. eMios, STM,etc...) and calls the
*          appropriate IP function in order to de-initializes the hardware timer.
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
*
* @pre     On/Off by the configuration parameter: GPT_DEINIT_API
*/
FUNC (void, GPT_CODE) Gpt_Ipw_DeInit(P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig)
{
    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            Gpt_eMios_DeInit(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
        {
            Gpt_Pit_DeInit(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
        {
            Gpt_Stm_DeInit(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour */
        break;
    }

    return;
}
#endif

/*================================================================================================*/
#if ((GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)|| (GPT_WAKEUP_FUNCTIONALITY_API == STD_ON))
/**
* @brief   Gpt driver Autosar independent and platform dependent function for disabling hardware timer interrupts.
* @details It checks the type of the HW module (e.g. eMios, STM,etc...), and calls the appropriate
*          IP function for disabling hardware timer interrupts.
*
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
*
* @pre     On/Off by the configuration parameter: GPT_ENABLE_DISABLE_NOTIFICATION_API
* @violates @ref GPT_IPW_C_REF_5 declarations and definitions of objects orfunctions at file scope...
*/
FUNC (void, GPT_CODE) Gpt_Ipw_DisableInterrupt(P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig)
{
    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            Gpt_eMios_DisableInterrupt(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
        {
            Gpt_Pit_DisableInterrupt(pHwChannelConfig->Gpt_u8HwChannel);
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
            /*For a STM enabled channel the interrupts are allways activated*/
        break;
#endif
        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour */
        break;
    }

    return;
}
#endif

/*================================================================================================*/

/*================================================================================================*/
/**
* @brief   Gpt driver Autosar independent and IP dependent function to change eMios compare register value.
* @details Calls the eMios function to change the eMios compare register value at the next match.
*
* @param[in]     pHwChannelConfig    Pointer to the channel configuration structure dependent by platform
* @param[in]     clkMode         Clock mode for configuration channel
*
*
* @implements Gpt_IPW_SetClockMode_Activity
*/
#if (GPT_SET_CLOCK_MODE == STD_ON)
FUNC (void, GPT_CODE) Gpt_Ipw_SetClockMode(
                                            P2CONST(Gpt_HwChannelConfigType, AUTOMATIC,GPT_APPL_CONST) pHwChannelConfig,
                                            VAR(Gpt_ClockModeType, AUTOMATIC) clkMode
                                          )
{
#if (GPT_EMIOS_USED == STD_ON)
    VAR(Gpt_PrescalerType, AUTOMATIC) eEmiosPrescaler;
#endif
#if (GPT_STM_USED == STD_ON)
    VAR(Gpt_PrescalerType, AUTOMATIC) eStmPrescaler;
#endif
    switch(pHwChannelConfig->Gpt_u8HwModule)
    {
#if (GPT_EMIOS_USED == STD_ON)
        case GPT_EMIOS_MODULE:
        {
            if(GPT_CLOCKMODE_NORMAL == clkMode)
            {
                eEmiosPrescaler = pHwChannelConfig->Gpt_uPrescaler;
            }
            else
            {
                eEmiosPrescaler = pHwChannelConfig->Gpt_uPrescaler_Alternate;
            }

            Gpt_eMios_SetClockMode(pHwChannelConfig->Gpt_u8HwChannel, eEmiosPrescaler);
        }
        break;
#endif

#if (GPT_STM_USED == STD_ON)
        case GPT_STM_MODULE:
        {
            if(GPT_CLOCKMODE_NORMAL == clkMode)
            {
                eStmPrescaler = pHwChannelConfig->Gpt_uPrescaler;
            }
            else
            {
                eStmPrescaler =  pHwChannelConfig->Gpt_uPrescaler_Alternate;
            }

            Gpt_Stm_SetClockMode(pHwChannelConfig->Gpt_u8HwChannel, eStmPrescaler);
        }
        break;
#endif

#if (GPT_PIT_USED == STD_ON)
        case GPT_PIT_MODULE:
            /* PIT has not prescaler */
        break;
#endif
        default:
            /*This switch branch is empty because it shall not be executed for normal behaviour*/
            break;
    }
}
#endif /* GPT_SET_CLOCK_MODE == STD_ON */


#define GPT_STOP_SEC_CODE
/** @violates @ref GPT_IPW_C_REF_1 Only preprocessor statements and comments before "#include" */
/** @violates @ref GPT_IPW_C_REF_2 Repeated include file MemMap.h */
#include "MemMap.h"

#ifdef __cplusplus
}
#endif

/** @} */
