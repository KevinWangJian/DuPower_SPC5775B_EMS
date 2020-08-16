/**
*   @file    Soc_Ips.h
*   @version 1.0.1
*
*   @brief   AUTOSAR Base - IP module versions.
*   @details The IP modules versions used on PA hardware platform and 
*            IP specific defines
*
*   @addtogroup BASE_COMPONENT
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.0 MCAL
*   Platform             : PA
*   Peripheral           : MPC5777C
*   Dependencies         : none
*
*   Autosar Version      : 4.0.3
*   Autosar Revision     : ASR_REL_4_0_REV_0003
*   Autosar Conf.Variant :
*   SW Version           : 1.0.1
*   Build Version        : MPC5777C_MCAL_1_0_1_RTM_HF2_ASR_REL_4_0_REV_0003_20171115
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/
/**
* @file        Soc_Ips.h
* 
*/

/** 
* @page misra_violations MISRA-C:2004 violations
* 
* @section Soc_Ips_h_REF_1
* Violates MISRA 2004 Required Rule 19.15, Repeated include file 
* This comes from the order of includes in the .c file and from include dependencies. As a safe 
* approach, any file must include all its dependencies. Header files are already protected against 
* double inclusions.
*
* @section [global]
* Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely on the
* significance of more than 31 characters. The used compilers use more than 31 chars for
* identifiers.
*
* @section [global]
* Violates MISRA 2004 Required Rule 20.2, The names of standard library macros, objects and functions
* shall not be reused. The driver needs to use defines starting with letter E.
*/

#ifndef SOC_IPS_H
#define SOC_IPS_H

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/** 
* @file        Soc_Ips.h
* @brief Include platform types
* @violates @ref Soc_Ips_h_REF_1 MISRA 2004 Required Rule 19.15, Repeated include file
*/
#include "Platform_Types.h"

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SOC_IPS_VENDOR_ID                    43
#define SOC_IPS_MODULE_ID                    0
#define SOC_IPS_AR_RELEASE_MAJOR_VERSION     4
#define SOC_IPS_AR_RELEASE_MINOR_VERSION     0
#define SOC_IPS_AR_RELEASE_REVISION_VERSION  3
#define SOC_IPS_SW_MAJOR_VERSION             1
#define SOC_IPS_SW_MINOR_VERSION             0
#define SOC_IPS_SW_PATCH_VERSION             1

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/
#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
    /* Check if source file and Platform_Types.h header file are of the same Autosar version */
    #if ((SOC_IPS_AR_RELEASE_MAJOR_VERSION != PLATFORM_AR_RELEASE_MAJOR_VERSION) || \
         (SOC_IPS_AR_RELEASE_MINOR_VERSION != PLATFORM_AR_RELEASE_MINOR_VERSION))
        #error "AutoSar Version Numbers of Soc_Ips.h and Platform_Types.h are different"
    #endif
#endif

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/**
* @brief EQADC IP Version: eqadc_ipi.01.00.19.00
* @details MPC5777C IP Versions

*/
#define IPV_EQADC               (0x01001900UL)

/**
* @brief DMA IP Version: DMA v02.00.00.10
* @details MPC5777C IP Versions
*/
#define IPV_DMA               (0x02000010UL)

/**
* @brief DSPI IP Version: DSPI v06.01.08.02
* @details MPC5777C IP Versions

*/
#define IPV_DSPI                 (0x06010802UL)

/**
* @brief PIT_RTI IP Version: PIT_RTI v05.00.06.09
* @details MPC5777C IP Versions
*/
#define IPV_PIT                  (0x05000609UL)

/**
* @brief MCAN IP Version: MCAN v00.00.00.21
* @details MPC5777C IP Versions
*/
#define IPV_MCAN                 (0x00000021UL)

/**
* @brief STCU IP Version:  v1.0.a
* @details MPC5777C IP Versions
*/
#define IPV_STCU2                (0x01006100UL)

/**
* @brief PLLDIG IP Version: PLLDIG 1.8.a.20130827.0
* @details MPC5777C IP Versions
*/
#define IPV_PLLDIG               (0x01086100UL)

/**
* @brief FLASHv2 IP Version: M_IP_c55fmc_8480_32_002_200_200_010 [c55fmc_8480_32_002_200_200_build2_6_1_6_22aug2014]
* @details MPC5777C IP Versions

*/
#define IPV_FLASHV2              (0x84803202UL) 

/**
* @brief eSCI IP Version:  esci.08.01.04.00
* @details MPC5777C IP Versions
*/
#define IPV_ESCI                 (0x08010400UL) 

/**
* @brief SSCM IP Version: SSCM v05.03.00.00
* @details MPC5777C IP Versions
*/
#define IPV_SSCM                 (0x05030000UL)

/**
* @brief PMC IP Version: PMC v000.00.00.15
* @details MPC5777C IP Versions
*/
#define IPV_PMC                 (0x00000015UL)

/**
* @brief MC IP Version: MC v04.00.15.02
* @details MPC5777C IP Versions
*/
#define IPV_MC                  (0x04001502UL)

/**
* @brief SIU IP Version: siu_ipi.00.01.23.45 - dummy version for 2N45H 
* @details MPC5777C IP Versions
*/
#define IPV_SIU                (0x00012345UL)

/*==================================================================================================
*                              Software Erratas for Hardware Erratas
==================================================================================================*/
/**
* @brief Hardware errata for FLASH (e7422)
* @details FLASH: Pipeline should not be enabled on the flash
*/
#define ERR_IPV_FLASH_0015          (STD_ON)

/**
* @brief Hardware errata for FLEXCAN (e8341)
* @details FlexCAN: Entering Freeze Mode or Low Power Mode from Normal Mode can cause the FlexCAN module to stop operating.
*/
#define ERR_IPV_FLEXCAN_0014         (STD_ON)

/**
* @brief Hardware errata for FLEXCAN (e9527)
* @details FlexCAN: FlexCAN: The transmission abort mechanism may not work properly.
*/
#define ERR_IPV_FLEXCAN_0015         (STD_ON)

/**
* @brief Hardware errata for IPV_ESCI (e9001)
* @details IPV_ESCI: Incorrect behaviour while in LIN Standard Bit error detection mode
*/
#define ERR_IPV_ESCI_0001          (STD_ON) 

/**
* @brief Hardware errata for IPV_EMIOS (e9978)
* @details IPV_EMIOS: Unexpected channel flag assertion during GPIO to MCB mode transition 
*/
#define ERR_IPV_EMIOS_0001          (STD_ON)


/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief EMIOS interrupts are handled by common ISRs
* @details MPC5777C Platform specific Defines/Configurations for EMIOS
*/
#define EMIOS_COMMON_ISR_HANDLER     (STD_OFF)
/**
* @brief EMIOS UCDIS register is available
* @details MPC5777C Platform specific Defines/Configurations for EMIOS
*/
#define EMIOS_UCDIS_AVAILABLE        (STD_OFF)
/**
* @brief Enable CACHE management feature
* @details Global define to enable CACHE management at runtime
*/
#define MCAL_CACHE_RUNTIME_MNGMNT (STD_OFF)

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/**
* @brief User Mode feature is enabled
* @details User Mode feature - MCAL is configured to run in supervisor mode, by default.
*/

#ifdef MCAL_ENABLE_SUPERVISOR_MODE
    #undef MCAL_ENABLE_USER_MODE_SUPPORT
#endif
#undef USER_MODE_REG_PROT_ENABLED
/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif


#endif /* #ifndef SOC_IPS_H*/

/** @} */
